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
 * $Log:	vmtp_hdlrpa.c,v $
 * Revision 2.3  89/03/09  20:49:00  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:07  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: vmtp_hdlrpa.c,v 2.1 87/08/14 15:43:41 mrt Exp $
 */

/*
 * 	vmtp_hdlrpa.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
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
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_send.h"

/*
 * Called by vmtp_input() when a response acknowledge packet is received.
 * Process the response acknowledge packet.  
 */
vmtp_hdlrpa(vi)
	register struct vmtpiphdr *vi;
{
	register struct vmtpcsr *csr;
	struct mbuf	*m = dtom(vi);
	int error;
	int s;	

#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
	printf("vmtp_hdlrpa(0x%x)\n", (u_long)vi);
#if	VMTP_DEBUG
	vmtp_dumpvi(vi, "vi", "vmtp_hdlrpa(): received a VMTP_RESPACK packet");
#endif
#endif
#if	!VMTP_DEBUG
	printf("%");
#endif
	s = splimp();

	/*
	 * Locate remote client csr.
	 */
	csr = vmtp_maptocsr(vi->vi_client, vremotecsrmap);

	if (csr == NULL) {
		splx(s);
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): no such client!\n");
#endif
		m_freem(m);
		return;
	}

#if	VMTP_DEBUG
	vmtp_dumpcsr(csr, "csr", "vmtp_hdlrpa(): found the remote client csr");
#endif

retry:
	if (!vmtp_sameeid(csr->vc_server, vi->vi_server)) {
		if (vcf_group(csr) && 
		    (csr = vmtp_nextcsr(csr)) != NULL) {
			goto retry;
		}
		/*
		 * Could refer to an earlier response to a group request
		 * or it's a protocol error.
		 */
		splx(s);
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): Wrong server id. Group?\n");
#endif
		m_freem(m);
		return;
	}

	if (csr->vc_transid != vi->vi_transid ||
	    csr->vc_state != VC_RESPONDED) {
		splx(s);
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): old transaction id!\n");
#endif
		m_freem(m);
		return;
	}

	if (!vmtp_stoptimer(csr)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): STOPTIMER FAILED\n");
#endif
		splx(s);
		m_freem(m);
		return;
	}
	splx(s);
		
	if (vmtp_datagram(csr->vc_code)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): idempotent response - do nothing!\n");
#endif
		m_freem(m);
		vmtp_starttimer(csr, vts_discardcsr(csr));
		return;
	}

	/* 
	 * Update the info in the csr. This will be used if retransmitting
	 */
	csr->vc_hostaddr = vi->vi_src;
	csr->vc_ifp = vi->vi_ifp;
	csr->vc_inpktgap = getvi_inpktgap(vi);

	switch (vi->vi_code & 0x00ffffff) {
	case VMTP_OK:
	case VMTP_RESPDISC:
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): VMTP_OK or VMTP_RESPDISC\n");
#endif

		if (csr->vc_dataseg) {
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
			}
			csr->vc_dataseg = NULL;
			andvi_control(csr->vc_vihdr,~VCTL_APG);
			csr->vc_code = VMTP_RESPDISC;
		}

		vmtp_starttimer(csr, vts_discardcsr(csr));
		break;
	case VMTP_RETRY:
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): VMTP_RETRY\n");
#endif

		if (++csr->vc_retrycnt > VMTP_MAXRETRYCNT) {
			if (csr->vc_dataseg) {
				if (vcf_mbuf(csr)) {
					m_freem(csr->vc_dataseg);
				}
				csr->vc_dataseg = NULL;
				csr->vc_code = VMTP_RESPDISC;
			}
			vmtp_starttimer(csr, vts_discardcsr(csr));
			break;
		}

		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk = vi->vi_dlvrmsk;
			csr->vc_txmsk &=  vmtp_usrdlvrmskset(csr->vc_code) 
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}

#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): retry 0x%x\n", csr->vc_txmsk);
#endif
        	if (error = vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
			printf("vmtp_hdlrpa(): retry failed (%d)\n", error);
#endif
		}

		csr->vc_rexmtcnt = 0;
 		vmtp_starttimer(csr, 
			vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)) ?
			vts_retransmit(csr) : vts_discardcsr(csr));
        	break;
	case VMTP_RETRYALL:
      	case VMTP_BUSY:
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): VMTP_RETRYALL or VMTP_BUSY\n");
#endif

		if (++csr->vc_retrycnt > VMTP_MAXRETRYCNT) {
			if (csr->vc_dataseg) {
				if (vcf_mbuf(csr)) {
					m_freem(csr->vc_dataseg);
				}
				csr->vc_dataseg = NULL;
				csr->vc_code = VMTP_RESPDISC;
			}
			vmtp_starttimer(csr, vts_discardcsr(csr));
			break;
		}

		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk =  vmtp_usrdlvrmskset(csr->vc_code) 
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}

#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrpa(): retry all 0x%x\n", csr->vc_txmsk);
#endif
        	if (error = vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
			printf("vmtp_hdlrpa(): retry all failed (%d)\n", error);
#endif
		}
		csr->vc_rexmtcnt = 0;
 		vmtp_starttimer(csr, 
			vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)) ?
			vts_retransmit(csr) : vts_discardcsr(csr));
        	break;
	case VMTP_MIGRATED:
      	default:
		if (csr->vc_dataseg) {
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
			}
			csr->vc_dataseg = NULL;
			csr->vc_code = VMTP_RESPDISC;
		}
		vmtp_starttimer(csr, vts_discardcsr(csr));
		break;
	}

	m_freem(m);
} /* vmtp_hdlrpa */

#endif	MACH_VMTP
