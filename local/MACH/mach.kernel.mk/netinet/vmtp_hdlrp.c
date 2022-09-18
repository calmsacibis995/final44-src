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
 * $Log:	vmtp_hdlrp.c,v $
 * Revision 2.3  89/03/09  20:48:53  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:03:59  gm0w
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
 * $ Header: vmtp_hdlrp.c,v 2.1 87/08/14 15:43:34 mrt Exp $
 */

/*
 * 	vmtp_hdlrp.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

#ifdef	FORWARD_DEBUG
#define VMTP_DEBUG
#endif

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
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "esp_cache.h"


#if	MACH_NP
extern void		netmsg_input_rp();
#endif	MACH_NP


/*
 * Called by vmtp_input() when a response packet is received.
 * Process the response packet. Follow closely the protocol operations
 * specified in VMTP documentation.
 *
 * Returns -1 when it the packet doesn't cause completion of a 
 * response: used by hdlfrp.
 *
 * Running at splimp() from the mapping to the csr until the timer is stopped.
 */
vmtp_hdlrp(vi)
	register struct vmtpiphdr *vi;
{
	register struct vmtpcsr *csr, *rb;
	register u_short control = getvi_control(vi);
	register struct vmtpsce *sc;	/* server cache entry */
	struct mbuf	*m = dtom(vi);
	struct vmtpsynq	*rq;	/* the response queue */
	register int s = splimp();	

#if	VMTP_DEBUG
	printf("vmtp_hdlrp(0x%x)\n", (u_long)vi);
#endif
	/*
	 * Locate local client csr.
	 */
	csr = vmtp_maptocsr(vi->vi_client, vlocalcsrmap);
	
	if (csr == NULL) {
		splx(s);
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
	printf("vmtp_hdlrp(): VMTP_NONEXIST\n");
#endif
		vmtp_sendrpa(NULL, vi, VMTP_NONEXIST);
		return -1;
	}

	if (vmtp_notfirstpg(control) ||
	    vmtp_notlastpg(control)) {
		/*
		 * Streaming not supported.
		 */
		splx(s);
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrp(): VMTP_NOSTREAMING\n");
#endif
		vmtp_sendrpa(NULL, vi, VMTP_NOSTREAMING);
		return -1;
	}

        if (csr->vc_transid != vi->vi_transid) {
		/*
		 * Bad transaction id.
		 */
		splx(s);
		if (vcf_group(csr)) {
			m_freem(m);
			return -1;
		}
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrp(): VMTP_BADTID\n");
#endif
		vmtp_sendrpa(NULL, vi, VMTP_BADTID);
		return -1;
	}

	if (vcf_forwarding(csr) && getvi_fnctcode(vi) == VMTP_RESP) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrp(): committed to forward response!\n");
#endif
		splx(s);
		m_freem(m);
		return -1;
	}

	if (vmtp_sameeid(csr->vc_server, vi->vi_server) || !vcf_group(csr)) {
		/*
		 * Latter if the request has been forwarded
		 */
		rb = csr;
	} else if (csr->vc_state == VC_AWAITRESP) {
#if	VMTP_DEBUG
		printf("vmtp_hdlrp(): first response to multicast\n");
#endif
		rb = csr;
	} else {
		if ((rq = csr->vc_responses) == NULL) {
#if	VMTP_DEBUG
			printf("vmtp_hdlrp(): allocating a response queue\n");
#endif
			/* second response - create a queue */
			if ((csr->vc_responses = vmtp_allocsynq()) == NULL) {
				splx(s);
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
				printf("vmtp_hdlrp(): rq - VMTP_RESPDISC\n");
#endif
				vmtp_sendrpa(NULL, vi, VMTP_RESPDISC);
				return -1;
			}
			rq = csr->vc_responses;
			rq->vq_qhead = NULL;
			rq->vq_type = VQ_RESPONSE;
			rq->vq_chead = rq->vq_ctail = &rq->vq_queue;
			rb = NULL;
		} else  {
			rb = vmtp_findrb(rq, vi->vi_server);
		}
		if (!rb) {
			/* allocate a new response buffer */
#if	VMTP_DEBUG
			printf("vmtp_hdlrp(): allocating an rb\n");
#endif
			splx(s);
			rb = vmtp_newrb();
			if (!rb) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
				printf("vmtp_hdlrp(): rb - VMTP_RESPDISC\n");
#endif
				vmtp_sendrpa(NULL, vi, VMTP_RESPDISC);
				return -1;
			}
			rb->vc_state = VC_AWAITRESP;			
			goto unqueued;
		} 
	} 

	if (rb->vc_state == VC_IDLE || rb->vc_state == VC_GETREPLY) {
		/*
		 * Note: VC_GETREPLY is only used on the main csr, 
		 * the rb's in the queue are in VC_RECVRESP (or VC_IDLE if
		 * the complete segments have already been received)
		 * when doing a getreply(). Since one response has been
		 * received into the main csr before a getreply() can be 
  		 * issued, additional packets from that server are duplicats.
		 */
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrp(): a duplicate response\n");
#endif
		/*
		 * Duplicate response.
		 */
		splx(s);
		if (vmtp_acknowledgepg(control) ||
		    vmtp_notlastpacket(control)) {
			/*
			 * Send a response acknowledge to stop further response.
			 */
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
			printf("vmtp_hdlrp(): VMTP_RESPDISC\n");
#endif
        		vmtp_sendrpa(NULL, vi, VMTP_RESPDISC);
		} else {
			m_freem(m);
		}
        	return -1;
	}

        /*
	 * rb->vc_state is VC_RECVRESP or VC_AWAITRESP.  Proceed to
	 * save data segment into rb.  If the response is complete then
	 * pass the response to invoker and wake up the invoker.
	 */
	if (rb == csr) {
		if (!vmtp_stoptimer(csr)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
			printf("vmtp_hdlrp(): STOPTIMER FAILED\n");
#endif
			splx(s);
			m_freem(m);
			return -1;
		}
		if (rb->vc_state == VC_AWAITRESP) {
			/*
			 * Copy header to rb.
			 */
			*rb->vc_vihdr = *vi;
			rb->vc_dlvrmsk = 0;
			rb->vc_state = VC_RECVRESP;
			if (rb->vc_dataseg) {
				if (vcf_mbuf(rb)) {
					m_freem(rb->vc_dataseg);
				}
				rb->vc_dataseg = NULL;
			}
			/* 
			 * Update info in server cache if not called by hdlfrp!
			 */	
			if (getvi_fnctcode(vi) == VMTP_RESP) {
				sc = esp_findentry(vi->vi_server);
				if (!sc) {
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
				 * the csr.
				 */
				rb->vc_hostaddr = vi->vi_src;
				rb->vc_ifp = vi->vi_ifp;
			}
		}
	} else {
#if	VMTP_DEBUG
		printf("vmtp_hdlrp(): Grabbing the rb out of the queue\n");
#endif
		vmtp_synqdeq(rb);
	}

	splx(s);

unqueued:
	if (rb->vc_state == VC_AWAITRESP) {
		/*
		 * Copy header to rb.
		 */
		*rb->vc_vihdr = *vi;
		rb->vc_dlvrmsk = 0;
		rb->vc_state = VC_RECVRESP;
		if (rb->vc_dataseg) {
			if (vcf_mbuf(rb)) {
				m_freem(rb->vc_dataseg);
			}
			rb->vc_dataseg = NULL;
		}

		/* 
		 * Update info in server cache if not called by hdlfrp!
		 */	
		if (getvi_fnctcode(vi) == VMTP_RESP) {
			sc = esp_findentry(vi->vi_server);
			if (!sc) {
				sc = esp_allocentry(vi->vi_server);
				sc->ve_gap = VMTP_INPKTGAP;
				sc->ve_roundtrip = VTC_ROUNDTRIP * 20;	
				sc->ve_mtu = VMTP_MAXBLKPACKET;
			}
			sc->ve_hostaddr = vi->vi_src;	
			sc->ve_ifp = vi->vi_ifp;
			sc->ve_flags |= VEF_HOSTADDR;
			/*
	 		 * Can't update the information in the rb 
			 * unless this is the same server as the one in
			 * the rb. 
			 */
			rb->vc_hostaddr = vi->vi_src;
			rb->vc_ifp = vi->vi_ifp;
		}
	}


	if (vmtp_segmentdata(rb->vc_code)) {
		rb->vc_flags |= VCF_MBUF;
		vmtp_savesegment(rb, vi);
	}
	else
		m_freem(m);

        if (vmtp_segmentdata(rb->vc_code) && 
		rb->vc_dlvrmsk != (vmtp_usrdlvrmskset(rb->vc_code)
				? rb->vc_usrdlvrmsk 
				: vmtp_segsizetomsk(rb->vc_segsize))) {
		/*
		 * Haven't received everything yet
		 */
		if (rb == csr) {
			csr->vc_rexmtcnt = 0;
			vmtp_starttimer(csr, vtc_receivepg(csr));
			return -1;
		} else {
			s = splimp();
			if (csr->vc_responses) {
				vmtp_synqenq(rb, csr->vc_responses);
				/* restart timeout if possible */
				if (csr->vc_state == VC_RECVRESP && 
				    vmtp_stoptimer(csr)) {
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlrp(): increasing the TIMEOUT!!\n");
#endif
					vmtp_starttimer(csr, vtc_receivepg(csr));
				}
				splx(s);
				return -1;
			} 
			/*
			 * The response queue must have been freed in
			 * vmtp_invoke while we have been running below splimp.
			 * So a new transaction has started -> free this rb
			 * as well as those in the queue already freed.
			 */
#if	VMTP_DEBUG
			printf("vmtp_hdlrp(): ** Freeing rb due to NEW INVOKE\n");
#endif
			splx(s);
			vmtp_freerb(rb);
			return -1;
		}
	}

	/*
	 * We have received last packet in packet group.
	 */

	if (vmtp_conditional(rb->vc_code) && csr->vc_state != VC_AWAITRESP &&
	    csr->vc_state != VC_GETREPLY) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_hdlrp(): CMD set - VMTP_NOTAWAIT\n");
#endif
		vmtp_sendrpa(rb, rb->vc_vihdr, VMTP_NOTAWAIT);
		if (rb != csr) {
#ifdef	FORWARD_DEBUG
			printf("vmtp_hdlrp(): NOTAWAIT: freeing the rb\n");
#endif
			vmtp_freerb(rb);
		}
		return -1;
	}

 	if (vmtp_acknowledgepg(control)) {
#if	VMTP_DEBUG || VMTP_RETRANS_DEBUG
		printf("vmtp_hdlrp(): APG set - VMTP_OK\n");
#endif
		vmtp_sendrpa(rb, rb->vc_vihdr, VMTP_OK);
	}

	if (csr != rb) {
		/* 
		 * Have to swap contents of csr and rb, since the client 
		 * is sleeping on the csr and not on this rb!
		 */
		int s;
#if	VMTP_DEBUG
		printf("vmtp_hdlrp(): ******* MULTIPLE RESPONSES *******\n");
#endif
		s = splimp();
		if ((csr->vc_state == VC_RECVRESP || 
		     csr->vc_state == VC_GETREPLY) && vmtp_stoptimer(csr)) {
#if	VMTP_DEBUG
			printf("vmtp_hdlrp(): SWAPPING\n");
#endif
			vmtp_swapcsr(csr,rb);
			vmtp_synqenq(rb, rq);
			splx(s);
		} else {
			if (csr->vc_responses) {
				/* 
				 * Can't deliver now - the main csr is 
				 * being used. Keep rb in VC_RECVRESP state.
				 */
#if	VMTP_DEBUG
				printf("vmtp_hdlrp(): can't swap: requeue rb\n");
#endif
				vmtp_synqenq(rb, rq);
				splx(s);
				return -1;
			}
			/* see comment above: new invoke called! */
#if	VMTP_DEBUG
			printf("vmtp_hdlrp(): ** Freeing rb due to NEW INVOKE\n");
#endif
			splx(s);
			vmtp_freerb(rb);
			return -1;
		}
	}	

	/*
	 * Deliver response message.
	 */
	csr->vc_state = VC_IDLE;
	if (getvi_fnctcode(vi) != VMTP_FWDRESP) {
		csr->vc_action = VCA_DELIVER;
		wakeup(csr);
#if	VMTP_INVOKE
		if (csr->vc_so != NULL) {
			csr->vc_so->so_rcv.sb_cc = 0xc003;
			sbwakeup(&csr->vc_so->so_rcv);
		}
#endif	VMTP_INVOKE
#if	MACH_NP
		if (csr->vc_netport != 0) {
			netmsg_input_rp(csr->vc_client);
		}
#endif	MACH_NP
	}
	return 0;
} /* vmtp_hdlrp */


/*
 * Swap the client related fields of two csrs. Information about timeouts,
 * queues, principals et.c. is not swapped (and can't be either since these
 * fields can't be used in the rb!!!
 */
vmtp_swapcsr(csr,rb)
	struct vmtpcsr *csr, *rb;
{
	struct vmtpcsr csr1;

	csr1.vc_vihdr = csr->vc_vihdr;
	csr1.vc_state = csr->vc_state;
	csr1.vc_rexmtcnt = csr->vc_rexmtcnt;
	csr1.vc_retrycnt = csr->vc_retrycnt;
	csr1.vc_iproute = csr->vc_iproute;
	csr1.vc_ipttl = csr->vc_ipttl;
	csr1.vc_flags = csr->vc_flags;
	csr1.vc_txmsk = csr->vc_txmsk;
	csr1.vc_dataseg = csr->vc_dataseg;
	csr->vc_vihdr = rb->vc_vihdr;
	csr->vc_state = rb->vc_state;
	csr->vc_rexmtcnt = rb->vc_rexmtcnt;
	csr->vc_retrycnt = rb->vc_retrycnt;
	csr->vc_iproute = rb->vc_iproute;
	csr->vc_ipttl = rb->vc_ipttl;
	csr->vc_flags = rb->vc_flags;
	csr->vc_txmsk = rb->vc_txmsk;
	csr->vc_dataseg = rb->vc_dataseg;
	rb->vc_vihdr = csr1.vc_vihdr;
	rb->vc_state = csr1.vc_state;
	rb->vc_rexmtcnt = csr1.vc_rexmtcnt;
	rb->vc_retrycnt = csr1.vc_retrycnt;
	rb->vc_iproute = csr1.vc_iproute;
	rb->vc_ipttl = csr1.vc_ipttl;
	rb->vc_flags = csr1.vc_flags;
	rb->vc_txmsk = csr1.vc_txmsk;
	rb->vc_dataseg = csr1.vc_dataseg;
} /* vmtp_swapcsr */
	

