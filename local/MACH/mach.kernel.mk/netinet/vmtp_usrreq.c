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
 * $Log:	vmtp_usrreq.c,v $
 * Revision 2.3  89/03/09  20:51:29  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:06:35  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 16-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	MACH_NP: make sure we do not use the netport with
 *	the socket calls.
 *
 * 07-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_HOSTID: added initialization and use of vmtpp_hostid.
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
 * $ Header: vmtp_usrreq.c,v 2.1 87/08/14 15:45:14 mrt Exp $
 */

/*
 * 	vmtp_usrreq.c	0.1	10/19/86
 *	Written by Joyo Wijaya and Erik Nordmark
 */

/*
 * TODO
 *	
 */
#undef VE_DEBUG


#include <sys/types.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h> 
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>

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
#include "vmtp_send.h"
#include "vmtp_group.h"
#include "esp_cache.h"
#include "esp.h"
#include "vmtp_ether.h"

/*
 * Bind a socket to an entity identifier
 */
vmtp_bind(nam, so)
	struct mbuf *nam;
	struct socket *so;
{
	register struct vmtpser *ser;
	register struct vmtpcsr *csr = vmtp_sotocsr(so);
	struct vmtpeid oldeid, neweid;

#ifdef	VMTP_DEBUG
	printf("\tvmtp_bind() called\n");
#endif

#if	VMTP_HOSTID
	/*
	 * Initialize vmtp_hostid if necessary.
	 * Use the address in the first network interface for
	 * lack of anything better... XXX
	 */
	if (!vmtp_hostid) {
		vmtp_hostid = IA_SIN(in_ifaddr)->sin_addr.s_addr;
	}
#endif	VMTP_HOSTID

	if (nam->m_len != sizeof(struct vmtpeid)) {
#ifdef	VMTP_DEBUG
		printf("\tvmtp_bind(): bad name length!\n");
#endif
		return EINVAL;
	}

	/* Check if already bound */

	neweid = *mtod(nam,struct vmtpeid *);
	if (csr) {
		return EADDRNOTAVAIL;
	} 

	if (vmtp_remotealiasent(neweid) || vmtp_groupeid(neweid)) {
		return EINVAL;
	}
#ifdef	notdef
#ifdef	LITTLE_ENDIAN
	setve_flags(neweid, getve_flags(neweid) | VE_LEE);
#else
	setve_flags(neweid, getve_flags(neweid) & ~VE_LEE);
#endif	LITTLE_ENDIAN
#endif	notdef

	if (vmtp_maptoserver(neweid) != NULL 
	   || vmtp_maptocsr(neweid, vlocalcsrmap) != NULL) {
		return EADDRINUSE;
	}


#ifdef	VMTP_DEBUG
	printf("vmtp_bind(): allocating a csr\n");
#endif
	
	csr = vmtp_newcsr(neweid, vlocalcsrmap);
	if (csr == NULL) {
		return ENOBUFS;
	}

	csr->vc_state = VC_IDLE; 
	csr->vc_hdltimeo = vmtp_hdllcsrtimeo;
	csr->vc_processid.pi_local = u.u_procp->p_pid;
#if	VMTP_HOSTID
	csr->vc_processid.pi_host.s_addr = vmtp_hostid;
#else	VMTP_HOSTID
	csr->vc_processid.pi_host.s_addr = ntohl(hostid);
#endif	VMTP_HOSTID
	csr->vc_principalid.pc_local = u.u_procp->p_uid;
#if	VMTP_HOSTID
	csr->vc_principalid.pc_host.s_addr = vmtp_hostid;
#else	VMTP_HOSTID
	csr->vc_principalid.pc_host.s_addr = ntohl(hostid);
#endif	VMTP_HOSTID
	csr->vc_effprincipalid = csr->vc_principalid;
	csr->vc_timelimit = 0xffffffff;		/* forever */

	so->so_pcb = (caddr_t)csr;

	return 0;
} /* vmtp_bind */


/*
 * Send a request - invoke a message transaction
 */
#if	VMTP_INVOKE
vmtp_invoke(so, func, csr,msg)
	int func;
#else	VMTP_INVOKE
vmtp_invoke(so, csr,msg)
#endif	VMTP_INVOKE
	struct socket *so;
	register struct vmtpcsr *csr;
	register struct vmtpmcb *msg;
{
	register struct mbuf *m = dtom(msg);
	register struct vmtpsce *sc;	/* server cache entry */
	register u_long control = 0;
	struct vmtpeid dest;	/* destination (server or coresident) */
	int error;
	register int s;

	if (vmtp_securepacket(so->so_proto->pr_protocol)) {
	 	if (csr->vc_authenticator == NULL || 
		    !vmtp_sameeid(csr->vc_origserver, msg->vm_eid)) {
#ifdef	ESP_DEBUG
			printf("vmtp_invoke(): secure protocol\n");
#endif
			sc = esp_findentry(msg->vm_eid);
			if (!sc || !entry_principal(sc)) {
#ifdef	KEY_DEBUG
			printf("vmtp_invoke(): NOPRINCIPAL: sc = 0x%x\n", sc);
			if (sc)
				printf("vmtp_invoke(): ve_flags = 0x%x\n", 
					sc->ve_flags);
#endif
				msg->vm_code |= VMTP_NOPRINCIPAL;
				m->m_next = NULL;	/* contains a caddr_t */
				return 0;
			}
			error = esp_getauthenticator(csr, sc->ve_principalid);
			switch (error) {
			case ENOBUFS:
				m->m_next = NULL;	/* contains a caddr_t */
				return ENOBUFS;
			case 0:
				break;
			default:
#ifdef	KEY_DEBUG
				printf("vmtp_invoke(): NOKEY\n");
#endif
				msg->vm_code |= VMTP_NOKEY;
				msg->vm_longdata[0] = 		
					sc->ve_principalid.pc_host.s_addr;
				msg->vm_longdata[1] = 		
					sc->ve_principalid.pc_local;
				m->m_next = NULL; 	/* contains a caddr_t */
				return 0;
			}
		}
	} else
		csr->vc_encryptqual = ENCRYPT_NONE;

	
#if	VMTP_INVOKE
	if (func & INVOKE_REQ) {
#endif	VMTP_INVOKE
	csr->vc_transid++;
		
	csr->vc_rexmtcnt = 0;
	csr->vc_retrycnt = 0;

	if (vmtp_segmentdata(msg->vm_code)) {
		if (msg->vm_segsize < 0 || msg->vm_segsize > VMTP_MAXSEGSIZE) {
			m->m_next = NULL; 	/* contains a caddr_t */
			return EINVAL;
		}
		
		csr->vc_segptr =  (caddr_t)m->m_next;
		m->m_next = NULL;
#if	VMTP_INVOKE
		csr->vc_flags = VCF_MBUF;
#else	VMTP_INVOKE
		csr->vc_flags = VCF_NONE;	/* i.e. not VCF_MBUF */
#endif	VMTP_INVOKE
		if (vmtp_usrdlvrmskset(msg->vm_code))
			csr->vc_txmsk =  msg->vm_dlvrmsk & 
					 vmtp_segsizetomsk(msg->vm_segsize);
		else
			csr->vc_txmsk = vmtp_segsizetomsk(msg->vm_segsize);

	} else {
		csr->vc_segptr =  NULL;
		csr->vc_flags = VCF_NONE;	
		csr->vc_txmsk = 0;
  	}
	
	msg->vm_code |= VU_REQ;

	csr->vc_server = msg->vm_eid;
	csr->vc_origserver = msg->vm_eid;
	csr->vc_ucb = msg->vm_ucb;

	if (vmtp_groupeid(csr->vc_server)) {
		if (vmtp_isgroupmember(csr->vc_client, csr->vc_server))
			control |= VCTL_MDG;
		if (vmtp_coresident(csr->vc_code)) {
			if (vmtp_emptyeid(csr->vc_coresident))
				csr->vc_coresident = csr->vc_client;
			dest = csr->vc_coresident;
		} else {
			dest = csr->vc_server;
		}
		csr->vc_flags |= VCF_GROUP;
		control |= vmtp_multipleresp(msg->vm_code) ? VCTL_DRT : 0;
	} else {
		dest = csr->vc_server;
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
				printf("vmtp_invoke(): client on local net\n");
#endif
				csr->vc_ifp = 
					vmtp_route(csr->vc_hostaddr.va_inet,
					  	   csr->vc_hostaddr.va_ether);
				if (csr->vc_ifp) {
#ifdef	VE_DEBUG
					printf("vmtp_invoke(): got local\n");
#endif
					csr->vc_hostaddr.va_type = VAT_ETHER;
				}
#ifdef	VE_DEBUG
				else
					printf("vmtp_invoke(): NOT local\n");
#endif
			} else if (vmtp_groupeid(dest)) {
#ifdef	VE_DEBUG
				printf("vmtp_invoke(): local & multicast\n");
#endif
				csr->vc_ifp = vmtp_defaultifp;
				vmtp_setmulticastaddr(csr->vc_hostaddr, dest);
			}
		}
#endif	VMTP_ETHER
	
	}
#if	MACH_NP
	csr->vc_netport = 0;
#endif	MACH_NP
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
		
	
#ifdef	GROUP_DEBUG
	printf("vmtp_invoke(): calling sendpg()\n");
#endif
	vmtp_sendpg(csr, VMTP_TRANSMIT, 0);
		
	if (vmtp_datagram(msg->vm_code)) {
#ifdef	GROUP_DEBUG
    	printf("vmtp_invoke(): datagram - done\n");
#endif

		csr->vc_dataseg = NULL;
		csr->vc_state = VC_IDLE;
		return 0;
	}
	
	csr->vc_state = VC_AWAITRESP;
	csr->vc_action = VCA_NOOP;

	vmtp_starttimer(csr, vtc_awaitresp(csr));

#if	VMTP_INVOKE
	}
	if (func & INVOKE_RESP) {
#endif	VMTP_INVOKE

#ifdef	GROUP_DEBUG
	printf("vmtp_invoke(): going to sleep!\n");
#endif

	while (csr->vc_action == VCA_NOOP)
		sleep(csr,PZERO+1);

#ifdef	GROUP_DEBUG
	printf("vmtp_invoke(): awoken!\n");
#endif

	while (csr->vc_action == VCA_RETRANS) {
#ifdef	GROUP_DEBUG
		printf("vmtp_invoke(): retransmitting!\n");
#endif
        	if (vmtp_sendpg(csr, VMTP_RETRANSMIT, 0)) {
#ifdef	GROUP_DEBUG
			printf("vmtp_invoke(): retransmission failed\n");
#endif
		}
		csr->vc_action = VCA_NOOP;
		vmtp_starttimer(csr, csr->vc_tleft);
		while (csr->vc_action == VCA_NOOP)
			sleep(csr,PZERO+1);
	}
		
	msg->vm_eid = csr->vc_server;
	msg->vm_ucb = csr->vc_ucb;

	m->m_next = (vmtp_segmentdata(msg->vm_code))
		? csr->vc_dataseg
		: NULL;
	csr->vc_dataseg = NULL;
#if	VMTP_INVOKE
	csr->vc_so->so_rcv.sb_cc = 0;
	}
#endif	VMTP_INVOKE
	return 0;
} /* vmtp_invoke */

/* 
 * Receive a request
 */
vmtp_recvreq(ser, a_m, timeout)
	register struct vmtpser *ser;
	register struct mbuf **a_m;
	register int timeout;
{
	register struct vmtpcsr *csr;
	register struct vmtpmcb *msg = mtod(*a_m, struct vmtpmcb *);
	register int s;

#ifdef	GROUP_DEBUG
	printf("vmtp_recvreq(): waiting for data\n");
#endif

/* 
 * Maybe set a user specified (in recvreq() call) timeout here! 
 * but can't have timeouts on ser's right now
 */
			
	s = splimp();
	ser->vs_flags |= VS_WAITING;

	while (!vmtp_requestqueued(ser))
		sleep(ser, PZERO+1);
#ifdef	VMTP_DEBUG
       	printf("vmtp_recvreq(): awoken\n");
#endif
	ser->vs_flags &= ~VS_WAITING;

	csr = vmtp_retrievereq(ser);
	splx(s);

	if (csr == NULL) {
#ifdef	VMTP_DEBUG
	       	printf("vmtp_recvreq(): SER INCONSISTENT!\n");
		return EINVAL;	/* Or something!! */
#else
		panic("vmtp_recvreq(): ser inconsistent");
#endif
	}

	msg->vm_eid = csr->vc_client;
	msg->vm_ucb = csr->vc_ucb;

	(*a_m)->m_next = vmtp_segmentdata(msg->vm_code) ? csr->vc_dataseg 
							: NULL;
	csr->vc_dataseg = NULL;
	
	if (vcf_recvforward(csr)) {
		/*
		 * Restore the host address of the client.
		 * Keep the flag (VCF_RECVFORWARD) to do duplicate suppression
		 * of retransmissions of the request from interfering with
		 * the forward request (required if it was idempotent).
		 */
#ifdef	FORWARD_DEBUG
	       	printf("vmtp_recvreq(): forwarded request - reset hostaddr\n");
#endif
		csr->vc_hostaddr = csr->vc_clienthost;
		csr->vc_ifp = csr->vc_clientifp;
	}
	if (vmtp_datagram(csr->vc_code)) {
		/* Ready to receive next */
		csr = vmtp_dequeuereq(ser, csr->vc_client);
		if (csr != NULL) {
			csr->vc_state = VC_RESPONDED;
			vmtp_starttimer(csr, vts_discardcsr(csr));
		}
	}


	return 0;
} /* vmtp_recvreq */

/* 
 * Used to get a delayed response from vmtp_reply and vmtp_forward (latter only
 * when sending a frp).
 */
vmtp_delayedreply(csr)
	struct vmtpcsr *csr;
{
	vmtp_sendpg(csr, VMTP_TRANSMIT, 0);
	csr->vc_state = VC_RESPONDED;

	vmtp_starttimer(csr, vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)) 
				? vts_retransmit(csr) : vts_discardcsr(csr));
} /* vmtp_delayedreply */

/*
 * Send a reply
 */
vmtp_reply(csr, msg, eid)
	register struct vmtpcsr *csr;
	register struct vmtpmcb *msg;
	struct vmtpeid eid;
{
	register struct mbuf *m = dtom(msg);
	register u_long control = getvi_control(csr->vc_vihdr);

	msg->vm_code &= ~VU_REQ;

	if (vcf_nilfwdrq(csr)) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_reply(): NILFWDRQ\n");
#endif
		msg->vm_code &= ~VU_DGM;
	}

	csr->vc_server = eid;		/* needed for multicast requests */
	csr->vc_ucb = msg->vm_ucb;

	if (vmtp_respdiscarded(csr->vc_code)) {
		m->m_next = NULL; 	/* contains a caddr_t */
		m_free(m);
		goto noreply;
	}

	if (vmtp_segmentdata(msg->vm_code)) {
		if (msg->vm_segsize < 0 || msg->vm_segsize > VMTP_MAXSEGSIZE) {
			m->m_next = NULL; 	/* contains a caddr_t */
			return EINVAL;
		}
		csr->vc_segptr =  (caddr_t)m->m_next;
		if (vmtp_usrdlvrmskset(msg->vm_code))
			csr->vc_txmsk =  msg->vm_dlvrmsk & 
					 vmtp_segsizetomsk(msg->vm_segsize);
		else
			csr->vc_txmsk = vmtp_segsizetomsk(msg->vm_segsize);

		if (vmtp_datagram(msg->vm_code))
			csr->vc_flags &= ~VCF_MBUF;
		else
			csr->vc_flags |= VCF_MBUF;
	} else {
		csr->vc_dataseg =  NULL;
		csr->vc_flags &= ~VCF_MBUF;
		csr->vc_txmsk = 0;
  	}

	m_free(m);		/* free the mcb part only */

	csr->vc_rexmtcnt = 0;
	csr->vc_retrycnt = 0;

	csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
	csr->vc_vihdr->vi_ifp = csr->vc_ifp;
	setvi_fnctcode(csr->vc_vihdr, VMTP_RESP);
	setvi_priority(csr->vc_vihdr, VPR_NORMAL);
	setvi_pgcount(csr->vc_vihdr, 0);
	setvi_control(csr->vc_vihdr, 0);

	if (vmtp_delayedresp(control)) {
#ifdef	GROUP_DEBUG
		printf("vmtp_reply(): delayed response\n");
#endif
		timeout(vmtp_delayedreply, csr, 0);
	    	return 0;
	}

#ifdef	GROUP_DEBUG
	printf("vmtp_reply(): calling sendpg()\n");
#endif

	vmtp_sendpg(csr, VMTP_TRANSMIT, 0);

noreply:
	csr->vc_state = VC_RESPONDED;

	vmtp_starttimer(csr, vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)) 
				? vts_retransmit(csr) : vts_discardcsr(csr));
	return 0;
} /* vmtp_reply */



/*
 * Get additional replies for the multicast request within a specified timeout
 * Timeout given in milliseconds
 */
vmtp_getreply(csr, a_m, timeout)
	register struct vmtpcsr *csr;
	register struct mbuf **a_m;
	int timeout;
{
	register struct vmtpcsr *rb;
	register struct vmtpmcb *msg = mtod(*a_m, struct vmtpmcb *);
	int s;

#ifdef	GROUP_DEBUG 
	printf("vmtp_getreply(): called\n");
#endif
	s = splimp();
	rb = vmtp_scanresponses(csr->vc_responses);
	if (rb) {
		/* 
		 * Get the mcb and datasegment from the response buffer.
		 * keep the response buffer for duplicate suppression.
		 */
#ifdef	GROUP_DEBUG
		printf("vmtp_getreply(): found a response\n");
#endif
		rb->vc_state = VC_IDLE;		/* Duplicates will be dropped */
		msg->vm_eid = rb->vc_server;
		msg->vm_ucb = rb->vc_ucb;

		(*a_m)->m_next = vmtp_segmentdata(msg->vm_code) 
							? rb->vc_dataseg 
							: NULL;
		rb->vc_dataseg = NULL;
		splx(s);

		return 0;
	}
	splx(s);

	csr->vc_state = VC_GETREPLY;
	csr->vc_action = VCA_NOOP;
	csr->vc_hdltimeo = vmtp_hdlgrtimeo;
	if (timeout) {
		vmtp_starttimer(csr, timeout*VMTP_TIMEOFREQ/1000+1);
		while (csr->vc_action != VCA_DELIVER)
			sleep(csr, PZERO+1);
	} 

	/* 
	 * If awoken by hdlrp then state is VC_IDLE and there is a response	
	 * in the csr; else there was a timeout.
	 */
	csr->vc_action = VCA_NOOP;
	csr->vc_hdltimeo = vmtp_hdllcsrtimeo;

	msg->vm_eid = csr->vc_server;
	msg->vm_ucb = csr->vc_ucb;
	if (csr->vc_state != VC_IDLE) {
		msg->vm_code = VMTP_USERTIMEO;
		csr->vc_state = VC_IDLE;
	} 

	(*a_m)->m_next = vmtp_segmentdata(msg->vm_code) ? csr->vc_dataseg 
							: NULL;
	csr->vc_dataseg = NULL;

	return 0;
} /* vmtp_getreply */

/*
 * Forward a request
 */
vmtp_forward(csr, msg, server, newserver)
	register struct vmtpcsr *csr;
	register struct vmtpmcb *msg;
	struct vmtpeid server, newserver;
{
	register struct mbuf *m = dtom(msg);
	register struct vmtpsce *sc;
	u_long saved_control = getvi_control(csr->vc_vihdr);
	struct vmtpeid dest;	/* destination (server or coresident) */
	register u_long control;
	int s;

	msg->vm_code |= VU_REQ;

	if (vcf_nilfwdrq(csr)) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_forward(): NILFWDRQ\n");
#endif
		msg->vm_code &= ~VU_DGM;
	}

	csr->vc_ucb = msg->vm_ucb;

	if (vmtp_segmentdata(msg->vm_code)) {
		if (msg->vm_segsize < 0 || msg->vm_segsize > VMTP_MAXSEGSIZE) {
			m->m_next = NULL; 	/* contains a caddr_t */
			return EINVAL;
		}
		csr->vc_segptr =  (caddr_t)m->m_next;
		if (vmtp_usrdlvrmskset(msg->vm_code))
			csr->vc_txmsk =  msg->vm_dlvrmsk & 
					 vmtp_segsizetomsk(msg->vm_segsize);
		else
			csr->vc_txmsk = vmtp_segsizetomsk(msg->vm_segsize);

		if (vmtp_datagram(msg->vm_code))
			csr->vc_flags &= ~VCF_MBUF;
		else 
			csr->vc_flags |= VCF_MBUF;
	} else {
		csr->vc_dataseg =  NULL;
		csr->vc_flags &= ~VCF_MBUF;
		csr->vc_txmsk = 0;
  	}

	m_free(m);		/* free the mcb part only */

	if (vcf_redo(csr)) {
		/*
		 * Rexmtcnt is incremented in hdlrq
		 * Set APG so that if the server is alive he will respond
		 * and rexmtcnt will be reset.
		 */
#ifdef	FORWARD_DEBUG
		printf("vmtp_forward(): VCF_REDO\n");
#endif
		control = VCTL_APG;
	} else {
		csr->vc_rexmtcnt = 0;
		control = 0;
	}
	csr->vc_retrycnt = 0;

	/* 
	 * Can't forward using forward requests when:
	 * -Multicasted request since confusing can arise between the frq's
	 *  and request since they have the same (client, transid) pair.
	 * -Request that was already forwarded since retransmissions of frq's
	 *  would be detected as cyclic forwarding and thus refused. (Accepting
	 *  the first frq and refusing retransmission of it would lead to a
	 *  frp being sent to the client which could lead to the request being 
	 *  done twice at the server: first due to the frq and then once again
	 *  with a higher transid if the frp is accepted and causes a request.)
	 * -If the secure protocol is used since it would cause a probe to be 
	 *  sent to the forwarder and the forwarder wouldn't find a local csr
	 *  for the client.
	 * -If the forward is done to a group, since if at least one refuse
	 *  the frq and at least one accepts it the acceptors will get the
	 *  request twice (2nd time with a new transaction id).
	 */
	if (vcf_group(csr) || vcf_recvforward(csr) ||
	    vmtp_securepacket(csr->vc_vihdr->vi_type)
#ifndef	FRQGROUP
	     || vmtp_groupeid(csr->vc_server)
#endif	!FRQGROUP
						) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_forward(): sending a forward response\n");
#endif
		setvi_fnctcode(csr->vc_vihdr, VMTP_FWDRESP);
		setvi_pgcount(csr->vc_vihdr, 0);
		csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
		csr->vc_vihdr->vi_ifp = csr->vc_ifp;
		csr->vc_server = newserver;
#ifndef	FRQGROUP
		if (vmtp_groupeid(csr->vc_server) &&
		    vmtp_coresident(csr->vc_code) &&
		    vmtp_emptyeid(csr->vc_coresident))
			csr->vc_coresident = server;
#endif	!FRQGROUP		
	} else {
#ifdef	FORWARD_DEBUG
		printf("vmtp_forward(): sending a forward request\n");
#endif
		csr->vc_clienthost = csr->vc_hostaddr; 
		csr->vc_clientifp = csr->vc_ifp;
				/* save hostaddr in case the frq is refused */
		csr->vc_origserver = csr->vc_server;
		csr->vc_server = newserver;
#ifdef	FRQGROUP
		if (vmtp_groupeid(csr->vc_server)) {
			if (vmtp_isgroupmember(csr->vc_client, csr->vc_server))
				control |= VCTL_MDG;
			if (vmtp_coresident(csr->vc_code)) {
				if (vmtp_emptyeid(csr->vc_coresident))
					csr->vc_coresident = server;
				dest = csr->vc_coresident;
			} else {
				dest = csr->vc_server;
			}
			csr->vc_flags |= VCF_GROUP;
			control |= vmtp_multipleresp(msg->vm_code) ?
					VCTL_DRT : 0;
		} else 
#endif	FRQGROUP
		{	
			dest = csr->vc_server;
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
				printf("vmtp_forward(): client on local net\n");
#endif
				csr->vc_ifp = 
					vmtp_route(csr->vc_hostaddr.va_inet,
					  	   csr->vc_hostaddr.va_ether);
				if (csr->vc_ifp) {
#ifdef	VE_DEBUG
					printf("vmtp_forward(): got local\n");
#endif
					csr->vc_hostaddr.va_type = VAT_ETHER;
				}
#ifdef	VE_DEBUG
				else
					printf("vmtp_forward(): NOT local\n");
#endif
			} else if (vmtp_groupeid(dest)) {
#ifdef	VE_DEBUG
				printf("vmtp_forward(): local & multicast\n");
#endif
				csr->vc_ifp = vmtp_defaultifp;
				vmtp_setmulticastaddr(csr->vc_hostaddr, dest);
			}
		}
#endif	VMTP_ETHER
		}
		splx(s);

		csr->vc_flags |= VCF_FORWARDING;
		setvi_fnctcode(csr->vc_vihdr, VMTP_FWDREQ);
		setvi_inpktgap(csr->vc_vihdr, VMTP_INPKTGAP);
		csr->vc_vihdr->vi_addr = csr->vc_hostaddr;
		csr->vc_vihdr->vi_ifp = csr->vc_ifp;
	}

	setvi_priority(csr->vc_vihdr, VPR_NORMAL);
	control |= vmtp_datagram(csr->vc_code) ? 0 : VCTL_APG;
	setvi_control(csr->vc_vihdr, control);

	if (vmtp_delayedresp(saved_control) && 
	    getvi_fnctcode(csr->vc_vihdr) == VMTP_FWDRESP) {
#ifdef	FORWARD_DEBUG
		printf("vmtp_forward(): delayed response\n");
#endif
		timeout(vmtp_delayedreply, csr, 0);
		return 0;
	}
#ifdef	FORWARD_DEBUG
	printf("vmtp_forward(): calling sendpg()\n");
#endif

	vmtp_sendpg(csr, VMTP_TRANSMIT, 0);

	if (vmtp_localaddr(csr->vc_vihdr->vi_addr))
		return 0;

	csr->vc_state = VC_RESPONDED;

	vmtp_starttimer(csr, vmtp_acknowledgepg(getvi_control(csr->vc_vihdr)) 
				? vts_retransmit(csr) : vts_discardcsr(csr));
	return 0;
} /* vmtp_forward */


/*
 * Handle user requests
 */
#if	VMTP_INVOKE
vmtp_usrreq(so, req, m, nam, rights, func)
	int func;
#else	VMTP_INVOKE
vmtp_usrreq(so, req, m, nam, rights)
#endif	VMTP_INVOKE
	struct socket *so;
	int req;
	struct mbuf *m;
	struct mbuf *nam, *rights;
{
	register struct vmtpser *ser;
	register struct vmtpcsr *csr = vmtp_sotocsr(so);
	register struct vmtpmcb *msg; 
	struct vmtpeid eid;
	int error = 0;

#ifdef	VMTP_DEBUG
	printf("vmtp_usrreq(): req = %d\n", req);
#endif

	if (rights && rights->m_len) {
		error = EINVAL;
		goto release;
	}
	switch (req) {

	case PRU_ATTACH:
		/* Space allocation (client and server state) deferred until
		 * PRU_BIND
		 */
		if ((int)nam != IPPROTO_VMTP && (int)nam != IPPROTO_VMTPS) 
			panic("vmtp_usrreq(): not IPPROTO_VMTP(S)\n");
		so->so_pcb = (caddr_t)0;
		break;

	case PRU_DETACH:
		/* Release space for server and client state */
		/* IS THIS REALLY SAFE TO DO ??? */

		if (csr) {
			eid = csr->vc_client;
			error = vmtp_leaveallgroups(eid);
			vmtp_freeserver( vmtp_maptoserver(eid));
			csr = vmtp_maptocsr(eid, vlocalcsrmap);
			{ 
				int s = splimp();

				if (csr->vc_qhead) {
					vmtp_synqdeq(csr);
				}
				splx(s);
			}
			vmtp_freecsr( csr, vlocalcsrmap);
		}
		
#if	VMTP_INVOKE
		/*
		 * Make sure that the socket appears free, otherwise
		 * sbflush will panic.
		 */
		so->so_rcv.sb_cc = 0;
#endif	VMTP_INVOKE

		so->so_pcb = (caddr_t)0;
		break;

	case PRU_BIND:
		/* Bind the socket to an entity identifier */
		if (error = vmtp_bind(nam, so))
			goto release;

		break;


	case PRU_INVOKE:	/* Invoke a message transaction */
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_INVOKE\n");
#endif

		if (!m) {
#ifdef	VMTP_DEBUG
			printf("vmtp_usrreq(): PRU_INVOKE m == NULL\n");
#endif
			error = EINVAL;
			goto release;
		}
		msg = mtod(m,struct vmtpmcb *);

		/* check if sender bound to address */
		if (!csr) {
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_INVOKE: no client address\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			error = EADDRNOTAVAIL;
			goto release;
		}
	

#if	VMTP_INVOKE
		csr->vc_so = so;
		if (error = vmtp_invoke(so, func,  csr, msg))
#else	VMTP_INVOKE
		if (error = vmtp_invoke(so, csr, msg))
#endif	VMTP_INVOKE
			goto release;

#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_INVOKE done!\n");
#endif
		break;


	case PRU_RECVREQ:	/* Receive a request */
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_RECVREQ called\n");
#endif

		if (!m) {
#ifdef	VMTP_DEBUG
			printf("vmtp_usrreq(): PRU_RECVREQ m == NULL\n");
#endif
			error = EINVAL;
			goto release;
		}
		msg = mtod(m,struct vmtpmcb *);
		
		/* check if server bound to address */
		if (!csr) {
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_RECVREQ no server address??\n");
#endif
			error = EADDRNOTAVAIL;
			goto release;
		}

		eid = csr->vc_client;
		ser = vmtp_maptoserver(eid);

		if (ser == NULL) {
#ifdef	VMTP_DEBUG	
			printf("vmtp_usrreq(): PRU_RECVREQ ser = NULL\n");
#endif
			error = EOPNOTSUPP;
			goto release;
		}
		
		if (error = vmtp_recvreq(ser, &m, 0))
			goto release;
	
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_RECVREQ done!\n");
#endif
		break;


	case PRU_REPLY: 	/* Send a reply */
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_REPLY called\n");
#endif

		if (!m) {
#ifdef	VMTP_DEBUG
			printf("vmtp_usrreq(): PRU_REPLY m == NULL\n");
#endif
			error = EINVAL;
			goto release;
		}
		msg = mtod(m,struct vmtpmcb *);
		
		/* check if replier bound to address */
		if (!csr) {
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_REPLY no server address??\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			error = EADDRNOTAVAIL;
			goto release;
		}

		eid = csr->vc_client;

		ser = vmtp_maptoserver(csr->vc_client);

		if (ser == NULL ) {
#ifdef	VMTP_DEBUG
			printf("vmtp_usrreq(): PRU_REPLY - not a server\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			error = EOPNOTSUPP;
			goto release;
		}

		/* get csr to respond to */
		csr = vmtp_dequeuereq(ser, msg->vm_eid);
		if (csr == NULL) {
			/*
			 * Ignore this - just drop the response.
			 * It could have been a multicast request!
			 */
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_REPLY - no csr to reply to\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			m_free(m);
			break;
		}
		
		if (error = vmtp_reply(csr, msg, eid)) 
			goto release;

#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_REPLY done!\n");
#endif

		break;

	case PRU_GETREPLY: 	/* Get next reply (multicast) */
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_GETREPLY called\n");
#endif

		if (!m) {
#ifdef	GROUP_DEBUG
			printf("vmtp_usrreq(): PRU_GETREPLY m == NULL\n");
#endif
			error = EINVAL;
			goto release;
		}
		msg = mtod(m,struct vmtpmcb *);
		
		/* check if client bound to address */
		if (!csr) {
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_GETREPLY no client address??\n");
#endif
			error = EADDRNOTAVAIL;
			goto release;
		}

		if (!vcf_group(csr)) {
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_GETREPLY - not a group request\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			msg->vm_code |= VMTP_NOMULTICAST;
			break;
		}

		if (error = vmtp_getreply(csr, &m, (int)nam))
			goto release;
	
#ifdef	GROUP_DEBUG
		printf("vmtp_usrreq(): PRU_GETREPLY done!\n");
#endif
		break;


	case PRU_FORWARD:	/* Forward a message */
#ifdef	FORWARD_DEBUG
		printf("vmtp_usrreq(): PRU_FORWARD called\n");
#endif

		if (!m || !nam) {
#ifdef	VMTP_DEBUG
			printf("vmtp_usrreq(): PRU_FORWARD m || nam == NULL\n");
#endif
			error = EINVAL;
			goto release;
		}
		msg = mtod(m,struct vmtpmcb *);
		
		/* check if forwarder bound to address */
		if (!csr) {
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_FORWARD no server address??\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			error = EADDRNOTAVAIL;
			goto release;
		}

		eid = csr->vc_client;

		ser = vmtp_maptoserver(csr->vc_client);

		if (ser == NULL ) {
#ifdef	VMTP_DEBUG
			printf("vmtp_usrreq(): PRU_FORWARD - not a server\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			error = EOPNOTSUPP;
			goto release;
		}

		/* get csr to respond to */
		csr = vmtp_dequeuereq(ser, msg->vm_eid);
		if (csr == NULL) {
			/*
			 * Ignore this - just drop the response.
			 * It could have been a multicast request!
			 */
#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): PRU_FORWARD - no csr to reply to\n");
#endif
			m->m_next = NULL; 	/* contains a caddr_t */
			m_free(m);
			break;
		}
		

		if (error = vmtp_forward(csr, msg, eid, 
				*mtod(nam, struct vmtpeid *)))
			goto release;

#ifdef	FORWARD_DEBUG
		printf("vmtp_usrreq(): PRU_FORWARD done!\n");
#endif

		break;

	case PRU_PROBE:	/* Request verification */
		error = esp_probe(csr, m);
		if (error) 
			goto release;
		break;

	case PRU_CONTROL:
	{
		int code = (int) m;
		struct vmtpauth *va;
		struct vmtpsce *sc;
		int s;

#ifdef	CONTROL_DEBUG
		printf("PRU_CONTROL: code = 0x%x\n", code);
#endif	
		if (nam == NULL) {
#ifdef	CONTROL_DEBUG
			printf("PRU_CONTROL: nam == NULL\n");
#endif
			error = EINVAL;
			goto release;
		}
		if (csr == NULL) {
#ifdef	CONTROL_DEBUG
			printf("PRU_CONTROL: no csr\n");
#endif
			error = ENOTCONN;			
			goto release;
		}

		switch (code) {
		case SIOCVMTPGETDEST:	/* get the destination server */
#ifdef	CONTROL_DEBUG
			printf("vmtp_usrreq(): SIOCVMTPGETDEST\n");
#endif
			eid = *(struct vmtpeid *)nam;

			/*
			 * Any csr for this client is good enough (there can be 
			 * more then one if the request was multicast).
			 * Don't bother checking that the csr is in the 
			 * server's queue.
			 */
			csr = vmtp_maptocsr(eid, vremotecsrmap);
			if (csr == NULL) {
#ifdef	CONTROL_DEBUG
				printf("SIOCVMTPGETDEST: no csr\n");
#endif
				error = ENOTCONN;			
				goto release;
			}
			if (vcf_group(csr))
				*(struct vmtpeid *)nam = csr->vc_origserver;
			else
				*(struct vmtpeid *)nam = csr->vc_server;
			break;
		case SIOCVMTPSETKEY:
			/* 
			 * Set/update the principal field in the cache -
			 * security risk?
			 */
			va = (struct vmtpauth *)nam;
			error = esp_setkey(csr->vc_principalid, va);
			if (error)
				break;
			if ((sc = esp_findentry(va->va_server)) == NULL) {
				sc = esp_allocentry(va->va_server);
				sc->ve_gap = VMTP_INPKTGAP;
				sc->ve_roundtrip = VTC_ROUNDTRIP * 20;	
				sc->ve_mtu = VMTP_MAXBLKPACKET;
				sc->ve_hostaddr.va_type = VAT_INET;
				sc->ve_hostaddr.va_inet =
					vmtp_eidtoinaddr(va->va_server);
				sc->ve_ifp = NULL;
				sc->ve_flags &= ~VEF_HOSTADDR;
			}
			sc->ve_principalid = va->va_serverp;
			sc->ve_flags |= VEF_PRINCIPAL;
			break;
		case SIOCVMTPDELKEY:
			va = (struct vmtpauth *)nam;
			esp_remkey(csr->vc_principalid, va->va_serverp);
			break;
		case SIOCVMTPGETORPHAN:
#ifdef	CONTROL_DEBUG
			printf("vmtp_usrreq(): SIOCVMTPGETORPHAN\n");
#endif
			ser = vmtp_maptoserver(csr->vc_client);
			if (ser == NULL) {
#ifdef	CONTROL_DEBUG
				printf("SIOCVMTPGETORPHAN: not server\n");
#endif
				error = EOPNOTSUPP;			
				goto release;
			}
			s = splimp();
			if (vmtp_orphan(ser)) {
#ifdef	CONTROL_DEBUG
				printf("SIOCVMTPGETORPHAN: found orphan!\n");
#endif
				ser->vs_flags &= ~VS_ORPHAN;
				eid = ser->vs_orphan;
			} else {
				eid.ve_fltm = 0;
				eid.ve_inaddr = 0;
			}
			splx(s);
			*(struct vmtpeid *)nam = eid;

			break;
		case SIOCVMTPREQWAITING:
#ifdef	CONTROL_DEBUG
			printf("vmtp_usrreq(): SIOCVMTPREQWAITING\n");
#endif
			ser = vmtp_maptoserver(csr->vc_client);
			if (ser == NULL) {
#ifdef	CONTROL_DEBUG
				printf("SIOCVMTPREQWAITING: not server\n");
#endif
				error = EOPNOTSUPP;			
				goto release;
			}
			if (vmtp_requestqueued(ser)) {
#ifdef	CONTROL_DEBUG
				printf("SIOCVMTPREQWAITING: queued!\n");
#endif
				*(int *)nam = 1;
			} else
				*(int *)nam = 0;
				
			break;
		default:
			error = EOPNOTSUPP;
			break;
		}
#ifdef	CONTROL_DEBUG
		printf("PRU_CONTROL: Done!\n");
#endif
		break;
	}
	case PRU_CONNECT:
		/* Maybe support some sort of connection in the future, so
		   that read and write can be used on the socket???
		 */ 
		error = EOPNOTSUPP;
		break;

	case PRU_DISCONNECT:
		/* Maybe support some sort of connection in the future, so
		   that read and write can be used on the socket???
		 */ 
		error = EOPNOTSUPP;
		break;

	case PRU_LISTEN:
	case PRU_CONNECT2:
	case PRU_ACCEPT:
	case PRU_SEND: 
		error = EOPNOTSUPP;
		break;



	case PRU_ABORT:
		/* Abort the connection? */
		error = EOPNOTSUPP;
		break;

	case PRU_SHUTDOWN:
	case PRU_SOCKADDR:
	case PRU_PEERADDR:
	case PRU_SENSE:

	case PRU_RCVD:
	case PRU_RCVOOB:
	case PRU_SENDOOB:
	case PRU_FASTTIMO:
	case PRU_SLOWTIMO:
	case PRU_PROTORCV:
	case PRU_PROTOSEND:
		error =  EOPNOTSUPP;
		break;

	default:
		panic("vmtp_usrreq");
	}

	if (req == PRU_INVOKE || req == PRU_RECVREQ || req == PRU_REPLY ||
	    req == PRU_GETREPLY || req == PRU_FORWARD || req == PRU_PROBE ||
 	    req == PRU_CONTROL) {

#ifdef	VMTP_DEBUG
		printf("vmtp_usrreq(): done!\n");
#endif
		return (error);
	}
	
release:

	if (m != NULL)
 		m_freem(m);

#ifdef	VMTP_DEBUG
	printf("vmtp_usrreq(): done at release!\n");
#endif
	return (error);

}

/*
 * Handle the IP_TIMETOLIVE and other options.
 */
vmtp_ctloutput(op, so, level, optname, m)
	int op;
	struct socket *so;
	int level, optname;
	struct mbuf **m;
{
	struct vmtpcsr *csr = vmtp_sotocsr(so);
	int error = 0;

#ifdef	CONTROL_DEBUG
	printf("vmtp_ctloutput(): *m = 0x%x, m_len = %d, level = %d\n", *m, 
		(*m) ? (*m)->m_len : 0, level);
#endif

	if (csr == NULL)
		error = ENOTCONN;
	else if (level != IPPROTO_VMTP && level != IPPROTO_VMTPS)
		error = EINVAL;
	else switch (op) {

	case PRCO_SETOPT:
		switch (optname) {
#if	TTLCONTROL
		case IP_TIMETOLIVE:
			if (*m != (struct mbuf *)0 && (*m)->m_len == 1 )
				csr->vc_ipttl = *(mtod(*m, u_char *));
			else error = EINVAL;
			break;
#endif
		case VMTP_ENCRYPTION:
			if (*m != (struct mbuf *)0 && (*m)->m_len == 1) {
				if (*(mtod(*m, u_char *)) == 0)
				    so->so_proto->pr_protocol = IPPROTO_VMTP;
				else 
				    so->so_proto->pr_protocol = IPPROTO_VMTPS;
			} else error = EINVAL;
			break;
		default:
			error = EINVAL;
			break;
		}
		break;

	case PRCO_GETOPT:
		switch (optname) {
#if	TTLCONTROL
		case IP_TIMETOLIVE:
			*m = m_get(M_WAIT, MT_SOOPTS);
			(*m)->m_off = MMINOFF;
			(*m)->m_len = 1;
			(*m)->m_dat[0] = csr->vc_ipttl;
			break;
#endif
		case VMTP_ENCRYPTION:
			*m = m_get(M_WAIT, MT_SOOPTS);
			(*m)->m_off = MMINOFF;
			(*m)->m_len = 1;
			(*m)->m_dat[0] = 
			   vmtp_securepacket(so->so_proto->pr_protocol) ? 1 : 0;
			break;
		default:
			error = EINVAL;
			break;
		}
		break;

	}
	if (op == PRCO_SETOPT)
		(void)m_free(*m);
	return (error);
}

