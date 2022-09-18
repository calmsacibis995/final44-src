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
 * $Log:	vmtp_timer.c,v $
 * Revision 2.4  89/03/09  20:51:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:06:27  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * Revision 2.2  88/08/24  02:08:01  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:10:53  mwyoung]
 * 
 * 16-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: added a call to the kernel netport code when
 *	appropriate.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Updated from new VMTP sources from Stanford (June 87).
 *
 * 02-Jun-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Mark the vihdr to avoid retransmitting a response for a duplicate
 *	request arriving after the server has given up in RECVREQ.
 *	The vihdr is not properly set up in that case, and we end up
 *	sending a message to ourselves!
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
 * $Header: vmtp_timer.c,v 2.4 89/03/09 20:51:21 rpd Exp $
 */

/*
 * 	vmtp_timer.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

/*
 * TODO:
 * 	Does vmtp_hdlgrtimeo have to check if there are any complete responses 
 *	in the response queue? Only possible if the response arrives between
 *	the check in getreply() and the starting of the timer???
 * 
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
#include "vmtp_group.h"
#include "esp.h"
#include "esp_ip.h"
#include "esp_var.h"

#if	VMTP_RETRANS_DEBUG
#define VMTP_DEBUG	1
#define VMTPDEBUG	1
#endif

#if	MACH_NP
extern void		netmsg_input_rp();
#endif	MACH_NP


/*
 * MACRO
 */
#define vmtp_firstgroupser(group) vmtp_maptoserver(vmtp_firstgroupmember(group))


/*
 * Handle timeouts of local clients.
 */
vmtp_hdllcsrtimeo(csr)
	register struct vmtpcsr *csr;
{
	u_long mask;
	int error;

#ifdef	VMTP_DEBUG
	printf("vmtp_hdllcsrtimeo(0x%x)\n", (u_long)csr);
#endif
	if (++csr->vc_rexmtcnt > VMTP_MAXREXMTCNT) {
		if ((csr->vc_state == VC_RECVRESP) && 
		    (vmtp_usrdlvrmskset(csr->vc_code))) {
			/*
			 * Deliver a partial response
			 */
#ifdef	VMTP_DEBUG
		printf("vmtp_hdllcsrtimeo(): delivering a partial response\n");
#endif
			csr->vc_usrdlvrmsk = csr->vc_dlvrmsk;
			csr->vc_state = VC_IDLE;
			csr->vc_action = VCA_DELIVER;
			wakeup(csr);
#if	VMTP_INVOKE
			if (csr->vc_so != NULL) {
				csr->vc_so->so_rcv.sb_cc = 0xc203;
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
		/*
		 * Discard the partial response if any
		 */
		if (!vcf_group(csr) &&
		    esp_findentry(csr->vc_server) == NULL) {
#ifdef	VMTP_DEBUG
printf("vmtp_hdllcsrtimeo(): Timed out and no cache entry\n");
#endif
			csr->vc_code = VMTP_CACHEMISS;
		} else {
#ifdef	VMTP_DEBUG
printf("vmtp_hdllcsrtimeo(): giving up OR discarding a partial response\n");
#endif
			csr->vc_code = VMTP_REXMTTIMEO;
		}
		csr->vc_segsize = 0;
		csr->vc_state = VC_IDLE;
		if (vcf_mbuf(csr)) {
			m_freem(csr->vc_dataseg);
		}
		csr->vc_dataseg = NULL;
#ifdef	VMTPDEBUG
	vmtp_dumpcsr(csr, "csr", "vmtp_hdllcsrtimeo(): retransmission timeout");
#endif
		csr->vc_action = VCA_DELIVER;
		wakeup(csr);
#if	VMTP_INVOKE
		if (csr->vc_so != NULL) {
			csr->vc_so->so_rcv.sb_cc = 0xc203;
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

	if (csr->vc_state == VC_AWAITRESP) {
		/*
		 * Retransmit the last packet in packet group.
		 */
		if (vmtp_segmentdata(csr->vc_code)) {
			csr->vc_txmsk = vmtp_usrdlvrmskset(csr->vc_code) ?
					csr->vc_usrdlvrmsk : 
					vmtp_segsizetomsk(csr->vc_segsize);
			for(mask = ~VMTP_MAXMASK; csr->vc_txmsk & mask; 
			    mask <<= VMTP_MAXBLKPACKET)
				csr->vc_txmsk &= mask;
		} else {
			csr->vc_txmsk = 0;
		}

		setvi_control(csr->vc_vihdr, VCTL_APG);
#ifdef	VMTPDEBUG
	printf("vmtp_hdllcsrtimeo(): retransmit last packet, txmsk = 0x%x\n", 
			csr->vc_txmsk);
#endif
#if	VMTP_INVOKE
		if (vmtp_segmentdata(csr->vc_code) && (!vcf_mbuf(csr))) {
#endif	VMTP_INVOKE
			/*
			 * Cause a retransmission by the blocked client process 
			 */
			csr->vc_action = VCA_RETRANS;
			csr->vc_tleft = vtc_roundtrip(csr); 	/* APG set */
			 	/* the timer will be started using this value */
			wakeup(csr);
#if	VMTP_INVOKE
		} else {
			/*
			 * Retransmit the request ourself.
			 */
#ifdef	VMTP_DEBUG
			printf("vmtp_hdllcsrtimeo(): retransmitting!\n");
#endif
	        	if (vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#ifdef	VMTP_DEBUG
				printf("vmtp_hdllcsrtimeo(): retransmission failed\n");
#endif
			}
			vmtp_starttimer(csr, vtc_roundtrip(csr));
		}
#endif	VMTP_INVOKE
		return;
	}
	
	if (csr->vc_state == VC_RECVRESP) {
		/*
		 * If idempotent return partial response else ask for retry.
		 */
		if (vmtp_datagram(csr->vc_code)) {
		    	if (vmtp_usrdlvrmskset(csr->vc_code)) {
				/*
				 * Deliver a partial response
				 */
#ifdef	VMTP_DEBUG
		printf("vmtp_hdllcsrtimeo(): a partial idempotent response\n");
#endif
				csr->vc_usrdlvrmsk = csr->vc_dlvrmsk;
				csr->vc_state = VC_IDLE;
				csr->vc_action = VCA_DELIVER;
				wakeup(csr);
#if	VMTP_INVOKE
				if (csr->vc_so != NULL) {
					csr->vc_so->so_rcv.sb_cc = 0xc203;
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
			else {
#ifdef	VMTP_DEBUG
			printf("vmtp_hdllcsrtimeo(): Bad Reply Segment\n");
#endif
				csr->vc_code = VMTP_BADREPLY;
				csr->vc_state = VC_IDLE;
				csr->vc_segsize = 0;
				if (vcf_mbuf(csr)) {
					m_freem(csr->vc_dataseg);
				}
				csr->vc_dataseg = NULL;
				csr->vc_action = VCA_DELIVER;
				wakeup(csr);
#if	VMTP_INVOKE
				if (csr->vc_so != NULL) {
					csr->vc_so->so_rcv.sb_cc = 0xc203;
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
		}
		mask = csr->vc_dlvrmsk;
		csr->vc_dlvrmsk = (vmtp_usrdlvrmskset(csr->vc_code)
					 ? csr->vc_usrdlvrmsk 
					 : vmtp_segsizetomsk(csr->vc_segsize))
					 ^ mask;
#ifdef	VMTPDEBUG
		printf("vmtp_hdllcsrtimeo(): ask for retry, mask = 0x%x\n",
			csr->vc_dlvrmsk);
		printf("vmtp_hdllcsrtimeo(): VMTP_RETRY\n");
#endif
		vmtp_sendrpa(csr, csr->vc_vihdr, VMTP_RETRY);
		csr->vc_dlvrmsk = mask;
		vmtp_starttimer(csr, vtc_roundtrip(csr)); 
		return;
	}
	panic("vmtp_hdllcsrtimeo");	
} /* vmtp_hdllcsrtimeo */

/*
 * Handle timeout of a remote client.
 */
vmtp_hdlrcsrtimeo(csr)
	register struct vmtpcsr *csr;
{
	u_long mask;
	struct vmtpser *ser;
	struct vmtpeid group;
	int	error;

#ifdef	VMTP_DEBUG
	printf("vmtp_hdlrcsrtimeo(0x%x)\n", (u_long)csr);
#endif

	switch (csr->vc_state) {

	case VC_AWAITPROBE:
	{
		struct espiphdr *ei = (struct espiphdr *)csr->vc_vihdr;

#ifdef	ESP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): awaiting a probe response\n");
#endif

		if (++csr->vc_rexmtcnt >= ESP_MAXREXMTCNT) {
#ifdef	ESP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): no more retransmissions\n");
#endif
			csr->vc_state = VC_RESPONDED;
#ifdef	MACH
			/*
			 * Avoid ever re-sending a response. (DPJ)
			 */
			csr->vc_code |= VCTL_INVALID;
#endif	MACH
			vmtp_starttimer(csr, vts_discardcsr(csr));
			return;
		}

		esp_time(ei->ei_tmstamp);
		csr->vc_tmstamp = ei->ei_tmstamp;

#ifdef	ESP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): new tmstamp = 0x%x\n", 
			ei->ei_tmstamp);
#endif
		esp_sendprq(csr, ei);
		vmtp_starttimer(csr, ET_RETRANSMIT);
		return;
	}

	case VC_RESPONDED:
		if (!vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)) ||
		    vmtp_respdiscarded(csr->vc_code)) 
			vmtp_freecsr(csr, vremotecsrmap);
		else if (++csr->vc_rexmtcnt > VMTP_MAXREXMTCNT) {
#ifdef	VMTP_DEBUG
	printf("vmtp_hdlrcsrtimeo(): discarding the response segment\n");
#endif
			csr->vc_code = VMTP_RESPDISC;
			andvi_control(csr->vc_vihdr, ~VCTL_APG);
			if (vcf_mbuf(csr)) {
				m_freem(csr->vc_dataseg);
			}
			csr->vc_dataseg = NULL;
			vmtp_starttimer(csr, vts_discardcsr(csr));
		}
		else {
			csr->vc_txmsk = vmtp_usrdlvrmskset(csr->vc_code) ?
					csr->vc_usrdlvrmsk :
					vmtp_segsizetomsk(csr->vc_segsize);
			for(mask = ~VMTP_MAXMASK; csr->vc_txmsk & mask; 
			    mask <<= VMTP_MAXBLKPACKET)
				csr->vc_txmsk &= mask;
		    	setvi_control(csr->vc_vihdr, VCTL_APG);
#ifdef	VMTPDEBUG
	printf("vmtp_hdlrcsrtimeo(): retransmit last packet, txmsk = 0x%x\n",
			csr->vc_txmsk);
#endif
			if (error = vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#ifdef	VMTPDEBUG
		printf("vmtp_hdlrcsrtimeo(): retransmission failed (%d)\n",
			error);
#endif
			}
			vmtp_starttimer(csr, vts_retransmit(csr));
		}				
		return;		
	case VC_RECVREQ:
		/*
		 * Locate the server entity record.
		 */
		ser = vmtp_maptoserver(csr->vc_server);
        	if (ser == NULL) {
			if (!vmtp_groupeid(csr->vc_server) 
			|| !(ser = vmtp_firstgroupser(csr->vc_server))) {
				/* 
				 * Server entity does not exist anymore.
				 */
#ifdef	VMTP_DEBUG
			printf("vmtp_hdlrcsrtimeo(): server doesn't exist\n");
#endif
				csr->vc_state = VC_RESPONDED;
				if (vcf_mbuf(csr)) {
					m_freem(csr->vc_dataseg);
				}
				csr->vc_dataseg = NULL;
				csr->vc_dlvrmsk = 0;
#ifdef	MACH
				/*
				 * Avoid ever re-sending a response. (DPJ)
				 */
				csr->vc_code |= VCTL_INVALID;
#endif	MACH
				vmtp_starttimer(csr, vts_discardcsr(csr));
#ifdef	VMTP_DEBUG
				printf("vmtp_hdlrcsrtimeo(): VMTP_NONEXIST\n");
#endif
            			vmtp_sendrqa(csr, csr->vc_vihdr, VMTP_NONEXIST);
				return;
        	 	}
		}

		if (++csr->vc_rexmtcnt > VMTP_MAXREXMTCNT ||
		    vmtp_datagram(csr->vc_code)) {
		    	if (vmtp_usrdlvrmskset(csr->vc_code)) {
				/*
				 * Deliver a partial request
				 */
#ifdef	VMTP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): deliver a partial request\n");
#endif
				csr->vc_usrdlvrmsk = csr->vc_dlvrmsk;
				csr->vc_state = VC_PROCESSING;
				csr->vc_rexmtcnt = 0;
				if (vmtp_groupeid(csr->vc_server)) {
					vmtp_delivertogroup(csr,csr->vc_server);
					return;
				}

				if (vmtp_conditional(csr->vc_code) && 
				    !vmtp_waiting(ser)) {
					/* discard csr */
#ifdef	VMTP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): Server busy - VMTP_NOTAWAIT\n");	
#endif
					vmtp_sendrqa(csr,csr->vc_vihdr, 
							VMTP_NOTAWAIT);
					vmtp_freecsr(csr, vremotecsrmap);
					return;
				}

			    if (vmtp_acknowledgepg(getvi_control(csr->vc_vihdr))) {
#ifdef	VMTP_DEBUG
			printf("vmtp_hdlrcsrtimeo(): APG set - VMTP_OK\n");	
#endif
					vmtp_sendrqa(csr,csr->vc_vihdr,VMTP_OK);
				}
		
				vmtp_queuerequest(csr, ser);
				wakeup(ser);
				return;
			}
			else {
				/*
				 * Discard the incomplete segment.
				 */
#ifdef	VMTP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): discard a partial request\n");
#endif
				vmtp_freecsr(csr, vremotecsrmap);
				return;
			}
		}
		else {
			/*
			 * Ask for a retry
			 */
			mask = csr->vc_dlvrmsk;
			csr->vc_dlvrmsk = (vmtp_usrdlvrmskset(csr->vc_code)
					 ? csr->vc_usrdlvrmsk 
					 : vmtp_segsizetomsk(csr->vc_segsize))
					 ^ mask;
#ifdef	VMTPDEBUG
		printf("vmtp_hdlrcsrtimeo(): ask for retry, mask = 0x%x\n",
			csr->vc_dlvrmsk);

			printf("vmtp_hdlrcsrtimeo(): VMTP_RETRY\n");
#endif
			/* 
			 * Make sure that request acks from a group will
			 * only cause retransmission to the requesting
			 * host/vmtp module.
			 */
			if (vmtp_groupeid(csr->vc_server)) {
				group = csr->vc_server;
				csr->vc_server = vmtp_firstgroupmember(group);
				vmtp_sendrqa(csr, csr->vc_vihdr, VMTP_RETRY);
				csr->vc_server = group;
			} else			
				vmtp_sendrqa(csr, csr->vc_vihdr, VMTP_RETRY);
			csr->vc_dlvrmsk = mask;
			vmtp_starttimer(csr, vts_retransmit(csr));
		}
		return;	
	case VC_AWAITREQ:
		/*
		 * This state is used when a probe response has been received 
		 * but no data (secure and authenticated communication). 
		 * The timeout will discard the csr.
		 */
#ifdef	VMTP_DEBUG
		printf("vmtp_hdlrcsrtimeo(): no request received after a \
probe response - discarding\n");
#endif
		vmtp_freecsr(csr, vremotecsrmap);
		return;
	default:
		panic("vmtp_hdlrcsrtimeo()");
		break;
	}
} /* vmtp_hdlrcsrtimeo */

/*
 * Timeout during getreply
 */
vmtp_hdlgrtimeo(csr)
	struct vmtpcsr *csr;
{
#ifdef	VMTP_DEBUG
	printf("vmtp_hdlgrtimeo(): csr = 0x%x\n", csr);
#endif	
	csr->vc_action = VCA_DELIVER;
	wakeup(csr);
} /* vmtp_hdlgrtimeo */

#endif	MACH_VMTP
