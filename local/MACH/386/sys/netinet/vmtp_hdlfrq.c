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
 * $Log:	vmtp_hdlfrq.c,v $
 * Revision 2.3  89/03/09  20:48:45  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:52  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_hdlfrq.c,v 2.1 87/08/14 15:43:29 mrt Exp $
 */

/*
 * 	vmtp_hdlfrq.c		3/17/87
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
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_send.h"
#include "esp.h"
#include "esp_cache.h"
#include "vmtp_ether.h"

/*
 * MACRO
 */
#define vmtp_firstgroupser(group) vmtp_maptoserver(vmtp_firstgroupmember(group))

/*
 * Called by vmtp_input() when a forward request packet is received.
 */
vmtp_hdlfrq(vi)
	register struct vmtpiphdr *vi;
{
	register struct vmtpcsr *csr;
	struct mbuf	*m = dtom(vi);
	struct vmtpser *ser;
	int error;
	int s = splimp();	/* to ensure that the csr isn't freed from the
				 *  mapping is done 'til it's dequeued.	*/	

#ifdef	FORWARD_DEBUG
	printf("vmtp_hdlfrq(): vi = 0x%x\n", vi);
#endif

	/*
	 * Check if there are any members if multicast.
	 * Locate the server entity record.
	 */
	ser = vmtp_maptoserver(vi->vi_server);
       	if (ser == NULL) 
		if (vmtp_groupeid(vi->vi_server)) {
		    	if ((ser = vmtp_firstgroupser(vi->vi_server)) == NULL){
				/*
				 * No group members 
				 */
#ifdef	FORWARD_DEBUG
				printf("vmtp_hdlfrq(): no group members\n");
		    vmtp_dumpeid(&vi->vi_server, "vi_server", "vmtp_hdlfrq");
			vi->vi_server = vmtp_firstgroupmember(vi->vi_server);
		    vmtp_dumpeid(&vi->vi_server, "first member", "vmtp_hdlfrq");
#endif
				m_freem(m);
				return;
			}
		} else if (vi->vi_multicast) {
#ifdef	FORWARD_DEBUG
				printf("vmtp_hdlfrq(): multicast- discarded\n");
#endif
				m_freem(m);
				return;

		} else {
			/* 
			 * Server entity does not exist.
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrq(): VMTP_NONEXIST\n");
#endif
			vmtp_sendrqa(NULL, vi, VMTP_NONEXIST);
			return;
       	 	}

	csr = vmtp_maptocsr(vi->vi_client, vlocalcsrmap);
	if (csr && !vmtp_groupeid(vi->vi_server)) {
		/*
		 * New server coresident with client. Handle as a
		 * forward response
		 */
		splx(s);
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrq(): local case!!\n");
#endif
		setvi_fnctcode(vi, VMTP_FWDRESP);
		vmtp_hdlfrp(vi);
		return;
	}

	csr = vmtp_maptocsr(vi->vi_client, vremotecsrmap);
	if (!csr) {
		/*
		 * Get a default/newest value for the clients host address
		 */
		struct vmtpsce *sc;

		splx(s);
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrq(): no csr\n");
#endif
         	if (vmtp_securityreq(ser) && !vmtp_securepacket(vi->vi_type)) {
			/* 
			 * Server requires security but transaction isn't 
			 * secure.
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrq(): VMTP_SECUREREQ\n");
#endif
			vmtp_sendrqa(NULL, vi, VMTP_SECUREREQ);
			return;
         	}

		if (vmtp_notfirstpg(getvi_control(vi)) ||
		    vmtp_notlastpg(getvi_control(vi))) {
			/*
			 * Streaming not supported.
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrq(): VMTP_NOSTREAMING\n");
#endif
			vmtp_sendrqa(NULL, vi, VMTP_NOSTREAMING);
			return;
		}

         	/*
		 * Allocate and initialize a new remote csr.
		 * Insert the csr into the map. 
		 */
		if ((csr = vmtp_newcsr(vi->vi_client, vremotecsrmap)) == NULL) {
			/*
			 * No csr is available.
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrq(): VMTP_BUSY\n");
#endif
			vmtp_sendrqa(NULL, vi, VMTP_BUSY);
			return;
		}

		/*
		 * Set some initial/default values. 
		 */
		csr->vc_inpktgap = VMTP_INPKTGAP;
		csr->vc_mtu = VMTP_MAXBLKPACKET;
		csr->vc_roundtrip = VTS_ROUNDTRIP * 20; 	/* in ms */
		csr->vc_encryptqual = ENCRYPT_NONE;
		csr->vc_hdltimeo = vmtp_hdlrcsrtimeo;

		/* vi_src is the host address of the forwarder! */
		if ((sc = esp_findentry(csr->vc_client)) != NULL) {
			csr->vc_hostaddr = sc->ve_hostaddr;
			csr->vc_ifp = sc->ve_ifp;
		} else {
			csr->vc_hostaddr.va_type = VAT_INET;
			csr->vc_hostaddr.va_inet = 
					vmtp_eidtoinaddr(csr->vc_client);
		}

		*csr->vc_vihdr = *vi;
		csr->vc_state = VC_RECVREQ;
		csr->vc_dlvrmsk = 0;
		vmtp_starttimer(csr, vts_discardcsr(csr));
	} else {
		/*
		 * Check if this server has already forwarded a request for
		 * this (client,transid). If so refuse to break possible 
		 * cycles. Note that this restricts forwarding to use forward
		 * request for re-forwarding since retransmissions would
		 * be detected as cycles by this test!
		 */
		if (csr->vc_transid == vi->vi_transid && 
		    csr->vc_state == VC_RESPONDED &&
		    vcf_forwarding(csr)) {
			/*
			 * Must refuse this forward request
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrq(): FORWARD_REFUSED\n");
#endif
			splx(s);
			vmtp_sendrqa(NULL, vi, VMTP_FREQRFSD);
			return;
		}
	}

	/*
	 * Save the host address of the client since this packet comes
	 * from the forwardserver and not the client.
	 */
	if (!vcf_recvforward(csr)) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrq(): first forward request!\n");
#endif
		if (!vmtp_localaddr(vi->vi_src)) {
			csr->vc_clienthost = csr->vc_hostaddr;
			csr->vc_clientifp = csr->vc_ifp;
		}
		csr->vc_hostaddr = vi->vi_src;
		csr->vc_ifp = vi->vi_ifp;
		csr->vc_flags |= VCF_RECVFORWARD;
	}
	splx(s);
	vmtp_hdlrq(vi);

} /* vmtp_hdlfrq */

#endif	MACH_VMTP
