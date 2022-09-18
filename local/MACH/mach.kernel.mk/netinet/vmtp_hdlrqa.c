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
 * $Log:	vmtp_hdlrqa.c,v $
 * Revision 2.3  89/03/09  20:49:15  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:04:22  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 16-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: added a call to the kernel netport code when
 *	appropriate.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 31-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_INVOKE: added support for split invoke call.
 *
 * 29-May-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources.
 *
 */
 
#include <mach_vmtp.h>
#include <mach_np.h>

#define VMTP_INVOKE	1

/*
 * $ Header: vmtp_hdlrqa.c,v 2.1 87/08/14 15:43:53 mrt Exp $
 */

/*
 * 	vmtp_hdlrqa.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

/* 
 * TODO:
 * 	User timeout
 */

#if	MACH_VMTP
#ifdef	FORWARD_DEBUG
#define VMTP_DEBUG
#define VMTPDEBUG
#endif

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
#include "esp_cache.h"

#if	MACH_NP
extern void		netmsg_input_rp();
#endif	MACH_NP


/*
 * Called by vmtp_input() when a request acknowledge packet is received.
 * Process the packet according to the VMTP specification of protocol
 * operations.
 */
vmtp_hdlrqa(vi)
	register struct vmtpiphdr *vi;
{
	register struct vmtpcsr *csr;
	struct mbuf	*m = dtom(vi);
	struct vmtpsce *sc;	/* server cache entry */
	int error;
	int s;

#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
	printf("vmtp_hdlrqa(0x%x)\n", (u_long)vi);
#if	VMTP_DEBUG
	vmtp_dumpvi(vi, "v", "vmtp_hdlrqa(): received a VMTP_REQACK packet");
#endif
#endif
	/*
	 * Check if in response to a forward request
	 */
	if (vmtp_clientmapping(getvi_control(vi))) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlrqa(): clientmapping - FWDREQ ack\n");
#endif
		return vmtp_hdlfrqa(vi,m);
	}

#if	!VMTP_DEBUG
	printf("$");
#endif
	s = splimp();	/* to ensure that the csr isn't freed from the
			 * mapping is done 'til it's dequeued.	*/	

	/*
	 * Locate local client csr.
	 */
	csr = vmtp_maptocsr(vi->vi_client, vlocalcsrmap);
	
	if (csr == NULL) {
		splx(s);
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): no such client!\n");
#endif
		m_freem(m);
		return;
	}

	if (csr->vc_transid != vi->vi_transid ||
	    csr->vc_state != VC_AWAITRESP) {
		splx(s);
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): Bad TID or not in VC_AWAITRESP\n");
#endif
		m_freem(m);
		return;
	}

	if (!vmtp_stoptimer(csr)) {
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): STOPTIMER FAILED\n");
#endif
		splx(s);
		m_freem(m);
		return;
	}	
	splx(s);

	/* update info in server cache if not multicasted request */

	if (!vcf_group(csr)) {
		if ((sc = esp_findentry(vi->vi_server)) == NULL) {
			sc = esp_allocentry(vi->vi_server);
			sc->ve_gap = VMTP_INPKTGAP;
			sc->ve_roundtrip = VTC_ROUNDTRIP * 20;	
			sc->ve_mtu = VMTP_MAXBLKPACKET;
		}
		sc->ve_hostaddr = vi->vi_src;	
		sc->ve_ifp = vi->vi_ifp;
		sc->ve_flags |= VEF_HOSTADDR;

		/*
 		 * Can't update the information in the csr 
		 * unless this is the same server as the one in
		 * the csr. (True unless group server or forwarded)
		 */
		if (vmtp_sameeid(csr->vc_server, vi->vi_server)) {
			csr->vc_hostaddr = vi->vi_src;
			csr->vc_ifp = vi->vi_ifp;
		}
	}


	switch (vi->vi_code & 0xffffff) {
	case VMTP_OK:
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): VMTP_OK\n");
#endif
		csr->vc_rexmtcnt = 0;
		vmtp_starttimer(csr, vtc_awaitresp(csr));
		break;
      	case VMTP_RETRY:
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): VMTP_RETRY\n");
#endif
		if (vmtp_datagram(csr->vc_code)) {
			/*
			 * This shouldn't happen - csr shouldn't be in a queue.
			 */
			printf("vmtp_hdlrqa(): VMTP_RETRY on datagram\n");
			break;
		}
		if (++csr->vc_retrycnt > VMTP_MAXRETRYCNT) {
			csr->vc_code = VMTP_MANYRETRIES;
			csr->vc_segsize = 0;
			csr->vc_state = VC_IDLE;
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
			}
			csr->vc_dataseg = NULL;
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
	vmtp_dumpcsr(csr, "csr", "vmtp_hdlrqa(): too many retries\n");
#endif
			csr->vc_action = VCA_DELIVER;
			wakeup(csr);
#if	VMTP_INVOKE
			if (csr->vc_so != NULL ) {
				csr->vc_so->so_rcv.sb_cc = 0xc103;
				sbwakeup(&csr->vc_so->so_rcv);
			}
#endif	VMTP_INVOKE
#if	MACH_NP
			if (csr->vc_netport != 0) {
				netmsg_input_rp(csr->vc_client);
			}
#endif	MACH_NP
			return;
		}

		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk = vi->vi_dlvrmsk;
			csr->vc_txmsk &=  vmtp_usrdlvrmskset(csr->vc_code) 
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}
			
		orvi_control(csr->vc_vihdr, VCTL_APG);
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): retry 0x%x\n", csr->vc_txmsk);
#endif
        	if (vi->vi_lasttrans != vi->vi_transid) {
			/*
			 * Should not happen since streaming not supported.
			 */
			printf("vmtp_hdlrqa(): no streaming and ");
			printf("vi->vi_lasttrans != vi->vi_transid\n");
		}
		csr->vc_rexmtcnt = 0;

#if	VMTP_INVOKE
		if (vmtp_segmentdata(csr->vc_code) && (!vcf_mbuf(csr))) {
#endif	VMTP_INVOKE
			/*
			 * Cause a retransmission by the blocked client process 
			 */
			csr->vc_action = VCA_RETRANS;
			csr->vc_tleft = vtc_awaitresp(csr);
			 	/* the timer will be started using this value */
			wakeup(csr);
#if	VMTP_INVOKE
		} else {
			/*
			 * Retransmit the request ourself.
			 */
#if	VMTP_DEBUG
			printf("vmtp_hdlrqa(): retransmitting!\n");
#endif
	        	if (vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
				printf("vmtp_hdlrqa(): retransmission failed\n");
#endif
			}
			vmtp_starttimer(csr, vtc_awaitresp(csr));
		}
#endif	VMTP_INVOKE

        	break;
	case VMTP_RETRYALL:
      	case VMTP_BUSY:
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): VMTP_RETRYALL or VMTP_BUSY\n");
#endif
		if (vmtp_datagram(csr->vc_code)) {
			/*
			 * This shouldn't happen - csr shouldn't be in a queue.
			 */
			printf("vmtp_hdlrqa(): VMTP_RETRY on datagram\n");
			break;
		}
		if (++csr->vc_retrycnt > VMTP_MAXRETRYCNT) {
			csr->vc_code = VMTP_MANYRETRIES;
			csr->vc_segsize = 0;
			csr->vc_state = VC_IDLE;
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
			}
			csr->vc_dataseg = NULL;
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
	vmtp_dumpcsr(csr, "csr", "vmtp_hdlrqa(): too many retries\n");
#endif
			csr->vc_action = VCA_DELIVER;
			wakeup(csr);
#if	VMTP_INVOKE
			if (csr->vc_so != NULL) {
				csr->vc_so->so_rcv.sb_cc = 0xc103;
				sbwakeup(&csr->vc_so->so_rcv);
			}
#endif	VMTP_INVOKE
#if	MACH_NP
			if (csr->vc_netport != 0) {
				netmsg_input_rp(csr->vc_client);
			}
#endif	MACH_NP
			return;
		}

		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk = vmtp_usrdlvrmskset(csr->vc_code)
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}

		orvi_control(csr->vc_vihdr, VCTL_APG);
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): retry all 0x%x\n", csr->vc_txmsk);
#endif
        	if (vi->vi_lasttrans != vi->vi_transid) {
			/*
			 * Should not happen since streaming not supported.
			 */
			printf("vmtp_hdlrqa(): no streaming and ");
			printf("vi->vi_lasttrans != vi->vi_transid\n");
		}
		csr->vc_rexmtcnt = 0;

#if	VMTP_INVOKE
		if (vmtp_segmentdata(csr->vc_code) && (!vcf_mbuf(csr))) {
#endif	VMTP_INVOKE
			/*
			 * Cause a retransmission by the blocked client process 
			 */
			csr->vc_action = VCA_RETRANS;
			csr->vc_tleft = vtc_awaitresp(csr);
			 	/* the timer will be started using this value */
			wakeup(csr);
#if	VMTP_INVOKE
		} else {
			/*
			 * Retransmit the request ourself.
			 */
#if	VMTP_DEBUG
			printf("vmtp_hdlrqa(): retransmitting!\n");
#endif
	        	if (vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
				printf("vmtp_hdlrqa(): retransmission failed\n");
#endif
			}
			vmtp_starttimer(csr, vtc_awaitresp(csr));
		}
#endif	VMTP_INVOKE
        	break;

	case VMTP_NONEXIST:
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): VMTP_NONEXIST\n");
#endif
		if (esp_findentry(vi->vi_server) == NULL) {
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
			printf("vmtp_hdlrqa(): No cache entry\n");
#endif
			csr->vc_code = VMTP_CACHEMISS;
			goto give_to_user;
		}
	case VMTP_REXMTTIMEO:
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): VMTP_REXMTTIMEO\n");
#endif
		if (sc = esp_findentry(vi->vi_server))
			esp_removeentry(vi->vi_server);
		
      	case VMTP_NOSTREAMING:
      	default:
#if	VMTPDEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrqa(): VMTP_NOSTREAMING et.c.\n");
#endif
		/*
		 * Note: there will never be a partial response when
		 * a rqa is received i.e. don't have to checks for one!
		 */
         	csr->vc_code = vi->vi_code;
give_to_user:
		csr->vc_server = vi->vi_server;		/* forwarded */
		csr->vc_state = VC_IDLE;
		csr->vc_segsize = 0;
		if (csr->vc_dataseg) {
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
			}
			csr->vc_dataseg = NULL;
		}
		if (vmtp_usrdlvrmskset(csr->vc_code))
			csr->vc_usrdlvrmsk = 0;
		csr->vc_action = VCA_DELIVER;
		wakeup(csr);
#if	VMTP_INVOKE
		if (csr->vc_so != NULL) {
			csr->vc_so->so_rcv.sb_cc = 0xc103;
			sbwakeup(&csr->vc_so->so_rcv);
		}
#endif	VMTP_INVOKE
#if	MACH_NP
		if (csr->vc_netport != 0) {
			netmsg_input_rp(csr->vc_client);
		}
#endif	MACH_NP
         	break;
	}

	m_freem(m);
} /* vmtp_hdlrqa */

/*
 * Handle request acks relating to forward requests
 * Called at splimp
 */
vmtp_hdlfrqa(vi, m)
	struct vmtpiphdr *vi;
	struct mbuf *m;
{
	struct vmtpcsr *csr;
	struct vmtpsce *sc;
	int localfl = 0;
	int s;
#ifdef	FORWARD_DEBUG
	printf("vmtp_hdlfrqa(): called\n");
#endif
#ifndef	VMTP_DEBUG
	printf("&");
#endif
	s = splimp();

	csr = vmtp_maptocsr(vi->vi_client, vremotecsrmap);
	
	if (csr == NULL) {
		splx(s);
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): no such (remote) client!\n");
#endif
		m_freem(m);
		return;
	}
	if (csr->vc_state != VC_RESPONDED || !vcf_forwarding(csr) ||
	    csr->vc_transid != vi->vi_transid || 
	    !vmtp_sameeid(csr->vc_server, vi->vi_server)) {
		if (csr->vc_state == VC_PROCESSING &&
		    vcf_forwarding(csr) && 
		    vmtp_localaddr(vi->vi_src)) {
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrqa(): local forwarding\n");
#endif
			localfl = 1;
			goto local;
		}  else {
			splx(s);
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrqa(): haven't forwarded ANYTHING!\n");
#endif
			m_freem(m);
			return;
		}
	}

	if (!vmtp_stoptimer(csr)) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): STOPTIMER FAILED\n");
#endif
		splx(s);
		m_freem(m);
		return;
	}	
local:
	splx(s);

	/* update info in server cache if not multicasted forward request */

	if (!vcf_group(csr)) {
		if ((sc = esp_findentry(vi->vi_server)) == NULL) {
			sc = esp_allocentry(vi->vi_server);
			sc->ve_gap = VMTP_INPKTGAP;
			sc->ve_roundtrip = VTC_ROUNDTRIP * 20;	
			sc->ve_mtu = VMTP_MAXBLKPACKET;
		}
		sc->ve_hostaddr = vi->vi_src;	
		sc->ve_ifp = vi->vi_ifp;
		sc->ve_flags |= VEF_HOSTADDR;

		/*
 		 * Can't update the information in the csr 
		 * unless this is the same server as the one in
		 * the csr. (True unless group server or forwarded)
		 */
		csr->vc_hostaddr = vi->vi_src;
		csr->vc_ifp = vi->vi_ifp;
	}

	switch (vi->vi_code & 0xffffff) {
	case VMTP_OK:
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): VMTP_OK\n");
#endif
		/*
		 * Keep the vc_forwarding flag set!
		 * Else retransmissions from the client could be responded with
		 * PROTOCOL ERROR.
		 * Reset the retransmit count so that retransmitted request and
		 * forward request continue to be sent plus the appropriate
		 * OK rqa'a to the client.
		 */
		csr->vc_rexmtcnt = 0;
		if (!localfl)
			vmtp_starttimer(csr, vts_discardcsr(csr));
		break;
	case VMTP_FREQRFSD:
		/*
		 * What to do if idemptent forward request????
		 * Now: mcb sent in a frp packet.
		 */
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): VMTP_FREQRFSD\n");
		printf("\tvc_hostaddr = 0x%x, vc_clienthost = 0x%x\n",
			csr->vc_hostaddr, csr->vc_clienthost);
#endif
		csr->vc_hostaddr = csr->vc_clienthost;
		csr->vc_ifp = csr->vc_clientifp;
		csr->vc_rexmtcnt = 0;
		csr->vc_retrycnt = 0;

		if (vmtp_segmentdata(csr->vc_code) && vcf_mbuf(csr) &&
		    csr->vc_dataseg) {
			csr->vc_txmsk = vmtp_usrdlvrmskset(csr->vc_code)
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}

		csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
		csr->vc_vihdr->vi_ifp = csr->vc_ifp;
		setvi_fnctcode(csr->vc_vihdr, VMTP_FWDRESP);
		setvi_priority(csr->vc_vihdr, VPR_NORMAL);
		setvi_pgcount(csr->vc_vihdr, 0);
		setvi_control(csr->vc_vihdr, vmtp_datagram(csr->vc_code) 
						? 0 : VCTL_APG);

#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): calling sendpg()\n");
#endif

		vmtp_sendpg(csr, VMTP_RETRANSMIT, 0);

		csr->vc_state = VC_RESPONDED;

		csr->vc_flags &= ~VCF_FORWARDING;
		vmtp_starttimer(csr, 
				vmtp_acknowledgepg(getvi_control(csr->vc_vihdr))
				? vts_retransmit(csr) : vts_discardcsr(csr));
		break;
      	case VMTP_RETRY:
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): VMTP_RETRY\n");
#endif
		if (vmtp_datagram(csr->vc_code)) {
			/*
			 * This shouldn't happen - csr shouldn't be in a queue.
			 */
			printf("vmtp_hdlfrqa(): VMTP_RETRY on datagram\n");
			break;
		}
		if (++csr->vc_retrycnt > VMTP_MAXRETRYCNT) {
			/*
			 * Send a rqa to the client
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrqa(): too many RETRIES\n");
#endif
			csr->vc_hostaddr = csr->vc_clienthost;
			csr->vc_ifp = csr->vc_clientifp;
			vmtp_sendrqa(csr, vi, VMTP_MANYRETRIES);
			csr->vc_state = VC_RESPONDED;
				/* was PROCESSING if local forwarding */
			csr->vc_flags &= ~VCF_FORWARDING;
			m_freem(m);
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
				csr->vc_dataseg = NULL;
			}
			vmtp_starttimer(csr, vts_discardcsr(csr));
			return;
		}

		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk = vi->vi_dlvrmsk;
			csr->vc_txmsk &=  vmtp_usrdlvrmskset(csr->vc_code) 
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}
			
		orvi_control(csr->vc_vihdr, VCTL_APG);
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): retry 0x%x\n", csr->vc_txmsk);
#endif
        	if (vi->vi_lasttrans != vi->vi_transid) {
			/*
			 * Should not happen since streaming not supported.
			 */
			printf("vmtp_hdlfrqa(): no streaming and ");
			printf("vi->vi_lasttrans != vi->vi_transid\n");
		}
		csr->vc_rexmtcnt = 0;
		vmtp_sendpg(csr, VMTP_RETRANSMIT, 0);
		if (!localfl)
			vmtp_starttimer(csr, vtc_awaitresp(csr));
		
      		break;

	case VMTP_RETRYALL:
      	case VMTP_BUSY:
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): VMTP_RETRYALL or VMTP_BUSY\n");
#endif
		if (vmtp_datagram(csr->vc_code)) {
			/*
			 * This shouldn't happen - csr shouldn't be in a queue.
			 */
			printf("vmtp_hdlfrqa(): VMTP_RETRY on datagram\n");
			break;
		}
		if (++csr->vc_retrycnt > VMTP_MAXRETRYCNT) {
			/*
			 * Send a rqa to the client
			 */
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlfrqa(): too many RETRIES\n");
#endif
			csr->vc_hostaddr = csr->vc_clienthost;
			csr->vc_ifp = csr->vc_clientifp;
			vmtp_sendrqa(csr, vi, VMTP_MANYRETRIES);
			csr->vc_state = VC_RESPONDED;
				/* was PROCESSING if local forwarding */
			csr->vc_flags &= ~VCF_FORWARDING;
			m_freem(m);
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
				csr->vc_dataseg = NULL;
			}
			vmtp_starttimer(csr, vts_discardcsr(csr));
			return;
		}

		if (vmtp_segmentdata(csr->vc_code) && csr->vc_dataseg) {
			csr->vc_txmsk = vmtp_usrdlvrmskset(csr->vc_code)
				? csr->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(csr->vc_segsize);
		} else {
			csr->vc_txmsk = 0;
		}

		orvi_control(csr->vc_vihdr, VCTL_APG);
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): retry all 0x%x\n", csr->vc_txmsk);
#endif
        	if (vi->vi_lasttrans != vi->vi_transid) {
			/*
			 * Should not happen since streaming not supported.
			 */
			printf("vmtp_hdlfrqa(): no streaming and ");
			printf("vi->vi_lasttrans != vi->vi_transid\n");
		}
		csr->vc_rexmtcnt = 0;
		vmtp_sendpg(csr, VMTP_RETRANSMIT, 0);
		if (!localfl)
			vmtp_starttimer(csr, vtc_awaitresp(csr));

	       	break;
	case VMTP_NONEXIST:
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): VMTP_NONEXIST\n");
#endif
		if (sc = esp_findentry(vi->vi_server))
			esp_removeentry(vi->vi_server);
      	case VMTP_NOSTREAMING:
      	default:
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlfrqa(): VMTP_NOSTREAMING et.c.\n");
#endif
		csr->vc_hostaddr = csr->vc_clienthost;
		csr->vc_ifp = csr->vc_clientifp;
		vmtp_sendrqa(csr, vi, vi->vi_code);
		csr->vc_state = VC_RESPONDED;
				/* was PROCESSING if local forwarding */
		csr->vc_flags &= ~VCF_FORWARDING;
		m_freem(m);
		if (vcf_mbuf(csr)) {
			m_freem(csr->vc_dataseg);
			csr->vc_dataseg = NULL;
		}
		vmtp_starttimer(csr, vts_discardcsr(csr));
		return;
	}

	m_freem(m);
} /* vmtp_hdlfrqa */



#endif	MACH_VMTP
