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
 * $Log:	igmp_usrreq.c,v $
 * Revision 2.3  89/03/09  20:44:00  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:59  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 *	igmp_usrreq.c
 */

#include "igmproto.h"
#include "multicast_agent.h"

#if	IGMPROTO

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/systm.h>

#include <net/if.h>
#include <net/route.h>
#include <net/netisr.h>

#include "in_systm.h"
#include "in.h"
#include "ip.h"
#include "ip_var.h"
#include "group.h"
#include "igmp_user.h"
#if	MULTICAST_AGENT
#include "agent_var.h"
#endif	MULTICAST_AGENT

#ifdef	vax
#include <vax/mtpr.h>
#endif	vax

struct GroupDescriptor *FindGroupDescriptor();
u_long unique;
struct socket *getf();
#if	MULTICAST_AGENT
extern struct ifnet loif;
#endif	MULTICAST_AGENT

/*
 * Initialize igmp connection block q.
 */
igmp_init()
{
	igmpcbhead.next = igmpcbhead.prev = &igmpcbhead;
	unique = 0;
	InitGroupDescriptorPool();
}



struct igmpcb *FindMatchingIgmpcb(type,identifier)
u_char type;
u_long identifier;
{
    struct igmpcb *igmpcb;

    for (igmpcb = igmpcbhead.next; igmpcb != &igmpcbhead; igmpcb = igmpcb->next) {
	if ((igmpcb->matched == 0) &&
	    (igmpcb->identifier == identifier) && 
	    ((igmpcb->type + 1) == type)) {
		return(igmpcb);
	}
    }
    return(NULL);
}



/*ARGSUSED*/
igmp_usrreq(so, req, m, nam, rights)
	struct socket *so;
	int req;
	struct mbuf *m, *nam, *rights;
{
	/* Is it safe to assume that (so != NULL) ? */
	register struct igmpcb *igmpcb = sotoigmpcb(so);
	register int error = 0;
	struct igmpreqargs *igmpargs;
	u_char reqrc,rc;
	int s;
	struct GroupDescriptor *ad;
	caddr_t *tmpptr;

	if (req == PRU_CONTROL) {

#define cmdbyte(x)	(((x) >> 8) & 0xff)
	    if (cmdbyte((int) m) == 'g') return(EINVAL);

	    igmpargs = (struct igmpreqargs *) nam;

	    if ((igmpcb->ad) && 
		((igmpargs->type == IGMP_CREATE_GROUP_REQUEST) ||
		(igmpargs->type == IGMP_JOIN_GROUP_REQUEST))) {
		/* Can't create or join on socket already in use */
		igmpargs->code = IGMP_SOCKET_IN_USE;
		return(EACCES);
	    }

	    if (igmpargs->type == IGMP_CONFIRM_GROUP_REQUEST) { 
		igmpargs->code = IGMP_NO_PERMISSION;
		return(EACCES);
	    }
	    
	    if (igmpargs->type == IGMP_LEAVE_GROUP_REQUEST) { 
		igmpargs->groupaddr.s_addr = igmpcb->ad->pcb.groupaddr.s_addr;
		rights = (struct mbuf *)igmpcb->ad->pcb.ifp;
	    }

	    reqrc = igmp_request(so,igmpargs->type,igmpargs->code,
	        igmpargs->groupaddr,igmpargs->key1, igmpargs->key2,
		(struct ifnet *)rights,igmpargs->loopback);

	    s = splnet();

	    if (reqrc != IGMP_REQUEST_SENT) {
		if ((reqrc == IGMP_NOT_A_MEMBER) || 
		    (reqrc == IGMP_REQUEST_GRANTED)) {
		    /* Can only happen from a LEAVE_GROUP_REQUEST */
		    igmpcb_clear(igmpcb);
		}
		igmpargs->code = reqrc;
		splx(s);
		return(0);
	    }
	    splx(s);

	    while (igmpcb->rc == IGMP_RC_UNSET) 
		sleep((caddr_t) &igmpcb->rc,IGMP_SLEEP_PRIORITY); 

	    s = splnet();
	    rc = igmpcb->rc;
	    if (((igmpcb->type == IGMP_CREATE_GROUP_REQUEST) ||
		(igmpcb->type == IGMP_JOIN_GROUP_REQUEST)) && (rc)) {
		igmpcb_clear(igmpcb);
	    }
	    else {
	        if (igmpcb->type == IGMP_LEAVE_GROUP_REQUEST) {
		    if ((rc == IGMP_REQUEST_GRANTED) |
		        (rc == IGMP_NO_RESPONSE)) {

		        ad = FindGroupDescriptor(igmpcb->groupaddr,igmpcb->ifp);
		        if (ad) RemoveGroupDescriptor(ad);
		    }
		}
	    }
	    igmpargs->code = rc;
	    igmpargs->groupaddr.s_addr = igmpcb->groupaddr.s_addr;
	    igmpargs->key1 = igmpcb->key1;
	    igmpargs->key2 = igmpcb->key2;
	    splx(s);
	    return(0);
	}

	s = splnet();
	if (rights && rights->m_len) {
		error = EOPNOTSUPP;
		goto release;
	}
	if (igmpcb == 0 && req != PRU_ATTACH) {
		error = EINVAL;
		goto release;
	}
	switch (req) {

	/*
	 * Allocate a igmp control block and fill in the
	 * necessary info to allow packets to be routed to
	 * the appropriate igmp interface routine.
	 */
	case PRU_ATTACH:
		if (igmpcb) {
			error = EINVAL;
			break;
		}
		error = igmp_attach(so);
		break;

	/*
	 * Destroy state just before socket deallocation.
	 * Flush data or not depending on the options.
	 */
	case PRU_DETACH:
		if (igmpcb == 0) {
			error = ENOTCONN;
			break;
		}
		igmp_detach(igmpcb);
		break;

	case PRU_CONNECT:
		error = EOPNOTSUPP;
		goto release;

	case PRU_CONNECT2:
		error = EOPNOTSUPP;
		goto release;

	case PRU_BIND:
		error = EOPNOTSUPP;
		goto release;

	case PRU_DISCONNECT:
		error = EOPNOTSUPP;
		goto release;

	/*
	 * Mark the connection as being incapable of further input.
	 */
	case PRU_SHUTDOWN:
		socantsendmore(so);
		break;

	/*
	 * Ship a packet out.  The appropriate igmp output
	 * routine handles any massaging necessary.
	 */
	case PRU_SEND:
		error = (*so->so_proto->pr_output)(m, so, nam);
		m = NULL;
		break;

	case PRU_ABORT:
		igmp_free(igmpcb);
		soisdisconnected(so);
		break;

	case PRU_SENSE:
		/*
		 * stat: don't bother with a blocksize.
		 */
	        splx(s);
		return (0);

	/*
	 * Not supported.
	 */
	case PRU_RCVOOB:
	case PRU_RCVD:
	        splx(s);
		return(EOPNOTSUPP);

	case PRU_LISTEN:
	case PRU_ACCEPT:
	case PRU_SENDOOB:
	case PRU_SOCKADDR:
	case PRU_PEERADDR:
		error = EOPNOTSUPP;
		break;


	default:
		panic("igmp_usrreq");
	}
release:
	if (m != NULL)
		m_freem(m);
	splx(s);
	return (error);
}


/*
 * Allocate a control block and a nominal amount
 * of buffer space for the socket.
 */
igmp_attach(so)
register struct socket *so;
{
	struct mbuf *m;
	register struct igmpcb *igmpcb;

	m = m_getclr(M_DONTWAIT, MT_PCB);
	if (m == 0)
		return (ENOBUFS);
	if (sbreserve(&so->so_snd, IGMPSNDQ) == 0)
		goto bad;
	if (sbreserve(&so->so_rcv, IGMPRCVQ) == 0)
		goto bad2;
	igmpcb = mtod(m, struct igmpcb *);
	igmpcb->countdown = IGMP_SLOWTIMEO_COUNTDOWN;
	igmpcb->num_rtx = 0;
	igmpcb->matched = 0;
	igmpcb->type = 0;
	igmpcb->code = IGMP_RC_UNSET;
	igmpcb->identifier = 0;
	igmpcb->key1 = 0;
	igmpcb->key2 = 0;
	igmpcb->groupaddr.s_addr = 0;
	igmpcb->socket = so;
	igmpcb->options = NULL;
	igmpcb->message = NULL;
	igmpcb->ad = NULL;
	igmpcb->ADnext = NULL;
	igmpcb->ADprev = NULL;
	igmpcb->rc = IGMP_RC_UNSET;
	igmpcb->ifp = NULL;
	igmpcb->loopback = 0;
	so->so_pcb = (caddr_t)igmpcb;
	insque(igmpcb, &igmpcbhead);
	return (0);
bad2:
	sbrelease(&so->so_snd);
bad:
	(void) m_free(m);
	return (ENOBUFS);
}

/*
 * Detach the igmp connection block and discard
 * socket resources.
 */
igmp_detach(igmpcb)
register struct igmpcb *igmpcb;
{
	int left;
	struct GroupDescriptor *ad;
	struct in_addr groupaddr;
	u_long key1;
	u_long key2;
	struct ifnet *ifp;

#if	MULTICAST_AGENT
    if(igmpcb->socket == agentsocket) goto freepcb;
#endif	MULTICAST_AGENT
    if (ad = igmpcb->ad) { 
        left = DeleteFromPCBList(igmpcb);
        if ((!left) || (left == -1)) {
	    groupaddr.s_addr = ad->pcb.groupaddr.s_addr;
	    key1 = ad->pcb.key1;
	    key2 = ad->pcb.key2;
	    ifp = ad->pcb.ifp;
	    RemoveGroupDescriptor(ad);
	    igmp_request((struct socket *)0,IGMP_LEAVE_GROUP_REQUEST,
			 0,groupaddr, key1,key2,ifp,0);
	}
    }
freepcb:
    igmp_free(igmpcb);
}


igmp_free(igmpcb)
register struct igmpcb *igmpcb;
{
    struct socket *so;

    if (igmpcb == NULL) return;

    so = igmpcb->socket;
    so->so_pcb = 0;
#if	MULTICAST_AGENT
    if (so == agentsocket) CleanUpAgent();
#endif	MULTICAST_AGENT
    sofree(so);
    remque(igmpcb);
    if (igmpcb->options)
	m_freem(dtom(igmpcb->options));
    if (igmpcb->message)
	m_freem(dtom(igmpcb->message));
    m_freem(dtom(igmpcb));
}

igmpcb_clear(igmpcb)
register struct igmpcb *igmpcb;
{
	igmpcb->countdown = IGMP_SLOWTIMEO_COUNTDOWN;
	igmpcb->num_rtx = 0;
	igmpcb->matched = 0;
	igmpcb->type = 0;
	igmpcb->code = IGMP_RC_UNSET;
	igmpcb->identifier = 0;
	igmpcb->key1 = 0;
	igmpcb->key2 = 0;
	igmpcb->groupaddr.s_addr = 0;
	igmpcb->options = NULL;
	igmpcb->message = NULL;
	igmpcb->ad = NULL;
	igmpcb->ADnext = NULL;
	igmpcb->ADprev = NULL;
	igmpcb->rc = IGMP_RC_UNSET;
	igmpcb->ifp = NULL;
	igmpcb->loopback = 0;
}

#endif	IGMPROTO
