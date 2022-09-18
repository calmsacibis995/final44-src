/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vmtp_hdlfrp.c,v $
 * Revision 2.3  89/03/09  20:48:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:46  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_hdlfrp.c,v 2.1 87/08/14 15:43:26 mrt Exp $
 */

/*
 * 	vmtp_hdlfrp.c		3/17/87
 *	Written by Erik Nordmark
 */

#if	MACH_VMTP

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_var.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_group.h"
#include "vmtp_send.h"
#include "esp_cache.h"
#include "vmtp_ether.h"

/*
 * Called by vmtp_input() when a forward request packet is received.
 */
vmtp_hdlfrp(vi)
	register struct vmtpiphdr *vi;
{
	register struct vmtpcsr *csr;
	struct mbuf	*m = dtom(vi);
	struct vmtpeid 	server,client;
	u_long 		transid;
	u_long		control;
	struct vmtpeid	dest;	/* being server or coresident */
	struct vmtpsce 	*sc;
	int s;

#ifdef	FORWARD_DEBUG
	printf("vmtp_hdlfrp(): vi = 0x%x\n", vi);
#endif
	client = vi->vi_client;
	server = vi->vi_server;
	transid = vi->vi_transid;

	s = splimp();
	csr = vmtp_maptocsr(client, vlocalcsrmap);
	if (!csr || csr->vc_transid != transid || 	 
	    csr->vc_state != VC_AWAITRESP) {
#ifdef	FORWARD_DEBUG
	       	printf("vmtp_hdlfrp(): old frp or response already received\n");
#endif
		splx(s);
		return;
	}
	csr->vc_flags |= VCF_FORWARDING;	/* receiving packets */
	splx(s);

	if (vmtp_hdlrp(vi)) {
#ifdef	FORWARD_DEBUG
	       	printf("vmtp_hdlfrp(): not ready YET!! (or failed)\n");
#endif
		return;
	}


	csr->vc_transid++;	/* must be before reseting vcf_forwarding */
	
	csr->vc_flags &= ~VCF_FORWARDING;
	csr->vc_code &= ~VU_DGM;
	
	/* setup a new request */
	csr->vc_origserver = csr->vc_server; 	
				/* needed when forwarded to a group */

	csr->vc_rexmtcnt = 0;
	csr->vc_retrycnt = 0;
	control = 0;

	if (vmtp_segmentdata(csr->vc_code)) {
		if (vmtp_usrdlvrmskset(csr->vc_code))
			csr->vc_txmsk =  csr->vc_usrdlvrmsk & 
					 vmtp_segsizetomsk(csr->vc_segsize);
		else
			csr->vc_txmsk = vmtp_segsizetomsk(csr->vc_segsize);
	} else {
		csr->vc_txmsk = 0;
		if (csr->vc_dataseg != NULL)
			m_freem(csr->vc_dataseg);
  	}
	
	csr->vc_code |= VU_REQ;


	if (vmtp_groupeid(csr->vc_server)) {
		if (vmtp_isgroupmember(csr->vc_client, csr->vc_server))
			control |= VCTL_MDG;
		if (vmtp_coresident(csr->vc_code)) {
			dest = csr->vc_coresident;
		} else {
			dest = csr->vc_server;
		}
		csr->vc_flags |= VCF_GROUP;
		control |=  vmtp_multipleresp(csr->vc_code) ? VCTL_DRT : 0;
	} else {
		dest = csr->vc_server;
		csr->vc_flags &= ~VCF_GROUP;
	}

	s = splimp();
	if ((sc = esp_findentry(dest)) != NULL) {
		csr->vc_hostaddr = sc->ve_hostaddr;
		csr->vc_ifp = sc->ve_ifp;
		csr->vc_inpktgap = sc->ve_gap;
		csr->vc_mtu = sc->ve_mtu;
		csr->vc_roundtrip = sc->ve_roundtrip;
	} else {
		csr->vc_hostaddr.va_type = VAT_INET;
		csr->vc_hostaddr.va_inet = vmtp_groupeid(dest) ?
						vmtp_eidtoinaddr(dest) :
						vmtp_groupeidtoinaddr(dest);
		csr->vc_inpktgap = VMTP_INPKTGAP;
		csr->vc_mtu = VMTP_MAXBLKPACKET;
		csr->vc_roundtrip = VTC_ROUNDTRIP * 20;	
#ifdef	VMTP_ETHER
		if (csr->vc_ipttl == 1) {
			if (!vmtp_groupeid(dest) &&
			    vmtp_localnet(csr->vc_hostaddr.va_inet)) {
#ifdef	VE_DEBUG
				printf("vmtp_hdlfrp(): client on local net\n");
#endif
				csr->vc_ifp = 
					vmtp_route(csr->vc_hostaddr.va_inet,
					  	   csr->vc_hostaddr.va_ether);
				if (csr->vc_ifp) {
#ifdef	VE_DEBUG
					printf("vmtp_hdlfrp(): got local\n");
#endif
					csr->vc_hostaddr.va_type = VAT_ETHER;
				}
#ifdef	VE_DEBUG
				else
					printf("vmtp_hdlfrp(): NOT local\n");
#endif
			} else if (vmtp_groupeid(dest)) {
#ifdef	VE_DEBUG
				printf("vmtp_hdlfrp(): local and group\n");
#endif
				csr->vc_ifp = vmtp_defaultifp;
				vmtp_setmulticastaddr(csr->vc_hostaddr, dest);
			}
		}
#endif	VMTP_ETHER
	}
	splx(s);

	csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
	csr->vc_vihdr->vi_ifp = csr->vc_ifp;
	setvi_fnctcode(csr->vc_vihdr, VMTP_REQ);
	setvi_priority(csr->vc_vihdr, VPR_NORMAL);
	setvi_inpktgap(csr->vc_vihdr, VMTP_INPKTGAP);
	setvi_control(csr->vc_vihdr, control);

	if (csr->vc_responses) {
		int s = splimp();
		if (csr->vc_responses) {
			vmtp_freerbqueue(csr->vc_responses);
			vmtp_deallocsynq(csr->vc_responses);
			csr->vc_responses = NULL;
		}
		splx(s);
	}
		
	
#ifdef	FORWARD_DEBUG
printf("vmtp_hdlfrp(): calling sendpg(): txmsk = 0x%x, dlvrmsk = 0x%x\n", 
	csr->vc_txmsk, csr->vc_dlvrmsk);
	printf("\tvc_dataseg = 0x%x\n", csr->vc_dataseg);
#endif
	vmtp_sendpg(csr, VMTP_RETRANSMIT, 0);
		
	csr->vc_state = VC_AWAITRESP;
	csr->vc_action = VCA_NOOP;

	vmtp_starttimer(csr, vtc_awaitresp(csr));

#ifdef	FORWARD_DEBUG
	printf("vmtp_hdlfrp(): done!\n");
#endif

} /* vmtp_hdlfrp */

#endif	MACH_VMTP
