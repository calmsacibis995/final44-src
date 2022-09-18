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
 * $Log:	igmp_input.c,v $
 * Revision 2.3  89/03/09  20:43:35  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:34  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 *	igmp_input.c
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
#include "in_pcb.h"
#include "ip.h"
#include "ip_var.h"
#include "udp.h"
#include "udp_var.h"
#include "tcp.h"
#include "tcp_timer.h"
#include "tcp_var.h"
#include "group.h"

#if	MULTICAST_AGENT
#include "agent_var.h"
#endif	MULTICAST_AGENT

#ifdef	vax
#include <vax/mtpr.h>
#endif	vax

#include "pcbheadsw.h"

extern struct ifnet loif;
struct inpcb *findpcbhead();
struct igmpcb *FindMatchingIgmpcb();
struct GroupDescriptor *FindGroupDescriptor();

 /*
 * IGMP protocol input routine.  
 * Find the socket associated with the packet(s) and move them over.
 * If nothing exists for this packet, drop it.
 */

igmp_input(m,ifp)
struct mbuf *m;
struct ifnet *ifp;
{
	int i;
	u_char type,code;
	u_long identifier,key1,key2;
	struct in_addr groupaddr;
	register struct igmpcb *match;
	register struct ip *ip = mtod(m, struct ip *);
	register struct igmp *igmp;
	int igmplen = ip->ip_len, hlen = ip->ip_hl << 2;
	struct GroupDescriptor *grpad;
	int s;
#if	MULTICAST_AGENT
	struct sockaddr_in igmpsrc;
#endif	MULTICAST_AGENT

	i = hlen + igmplen;
 	if ((m->m_off > MMAXOFF || m->m_len < i) &&
 		(m = m_pullup(m, i)) == 0)  {
		igmpstat.igmps_tooshort++;
		return;
	}
 	ip = mtod(m, struct ip *);
	m->m_len -= hlen;
	m->m_off += hlen;
	igmp = mtod(m, struct igmp *);

	if (in_cksum(m, igmplen)) {
		igmpstat.igmps_checksum++;
		if (m) m_freem(m);
		return;
	}

	type = igmp->igmp_type;
	code = igmp->igmp_code;
	identifier = ntohl(igmp->igmp_ident);
	key1 = ntohl(igmp->igmp_key1);
	key2 = ntohl(igmp->igmp_key2);
	groupaddr.s_addr = ntohl(igmp->igmp_groupaddr.s_addr);

	if(type > IGMP_MAXTYPE) { 
	    if (m) m_freem(m);
	    return;
	}
#if	MULTICAST_AGENT
	if(IGMP_IS_A_REQUEST(type)) { 
	    if (agentsocket == NULL) {
	        if (m) m_freem(m);
	        return;
	    }
	    igmpsrc.sin_family = AF_INET;
	    igmpsrc.sin_addr = ip->ip_src;

	    if ((type == IGMP_MEMBERSHIP_UPDATE) && (ifp == &loif)) {
	        if (m) m_freem(m);
	        return;
	    }

	    if (sbappendaddr(&agentsocket->so_rcv,(struct sockaddr *)&igmpsrc,
	        m, (struct mbuf *) 0) == 0) {
		    if (m) m_freem(m);
	    }
	    else sorwakeup(agentsocket);
	    return;
	}
#else	MULTICAST_AGENT
	if (IGMP_IS_A_REQUEST(type)) {
	    if (m) m_freem(m);
	    return;
	}
#endif	MULTICAST_AGENT

	switch (type) {

	    case IGMP_CREATE_GROUP_REPLY:
	    case IGMP_JOIN_GROUP_REPLY:

		s = splnet();
		match = FindMatchingIgmpcb(type,identifier);
		if (!match) {
		    splx(s);
		    if (code == IGMP_REQUEST_GRANTED) {
			grpad = 
			    FindGroupDescriptor(groupaddr,(struct ifnet *)NULL);
			if(grpad == NULL) {
			    igmp_request((struct socket *)0,
				IGMP_LEAVE_GROUP_REQUEST,0, groupaddr,key1,
				key2,ifp,0);
			}
		    }
		    if (m) m_freem(m);
		    return;
		}
		match->matched = 1;
		splx(s);
		grpad = FindGroupDescriptor(groupaddr,match->ifp);
		if (type == IGMP_CREATE_GROUP_REPLY) {
		    if (code == IGMP_REQUEST_GRANTED &&
		      ((grpad != NULL) || (!(IN_CLASSD(groupaddr.s_addr))) ||
			(match->code == IGMP_PUBLIC_GROUP ^ !(key1 || key2)))) {
		    	    if (m) m_freem(m);
			    match->matched = 0;
		    	    return;
		    }
		}
		else {  /* type == JOIN_GROUP_REQUEST */

		    if (groupaddr.s_addr != match->groupaddr.s_addr ||
		        key1 != match->key1 || key2 != match->key2 ||
			(code == IGMP_REQUEST_GRANTED && ((grpad != NULL) || 
			(!(IN_CLASSD(groupaddr.s_addr)))))) {
		    	    if (m) m_freem(m);
			    match->matched = 0;
		    	    return;
		    }
		}
	    
	        /* Finally, we are satisfied that this is an okay reply */
		if (code > IGMP_MAXCODE) {
		    match->countdown = code * SLOWTIMEO_FREQUENCY;
		    if (m) m_freem(m);
		    match->matched = 0;
		    return;
		}
		if (match->message) m_free(match->message);
		match->message = NULL;	/* Stop retransmission */

		if (code == IGMP_REQUEST_GRANTED) {

		    grpad = InstallGroupDescriptor(groupaddr, key1,key2,
			    match,match->ifp);

		    if (grpad == NULL) {
		        igmp->igmp_code = IGMP_NO_INTERNAL_RESOURCES;
		        break;
		    }
		}
		break;

	    case IGMP_LEAVE_GROUP_REPLY:

		s = splnet();
		match = FindMatchingIgmpcb(type,identifier);
		if (!match) {
		    splx(s);
		    if (m) m_freem(m);
		    return;
		}
		match->matched = 1;
		splx(s);
		if (groupaddr.s_addr != match->groupaddr.s_addr ||
		    key1 != match->key1 || key2 != match->key2 ) {
		        if (m) m_freem(m);
			match->matched = 0;
		        return;
		}
		if (code > IGMP_MAXCODE) {
		    match->countdown = code * SLOWTIMEO_FREQUENCY;
		    if (m) m_freem(m);
		    match->matched = 0;
		    return;
		}

		if (match->message) m_free(match->message);
		match->message = NULL;	/* Stop retransmission */
		break;

	    case IGMP_CONFIRM_GROUP_REPLY:

		/* ifp is the interface pointer this packet arrived with */

		grpad = FindGroupDescriptor(groupaddr,ifp);
		if( grpad == NULL) {
		    if (m) m_freem(m);
		    return;
		}
		if (code == IGMP_REQUEST_GRANTED) {
		    if (((key1 != 0) || (key2 != 0)) &&
		        ((key1 != grpad->pcb.key1) || (key2 != grpad->pcb.key2))) {
		    	    MembershipRevoked(grpad->pcb.groupaddr);
		    	    RemoveGroupDescriptor(grpad);
		    }
		    else {
			    
		        grpad->confirm_timer = 
			    IGMP_RANDOM_CONFIRM_INTERVAL * SLOWTIMEO_FREQUENCY;
		    }
		}
		else if (code <= IGMP_MAXCODE) {
		    MembershipRevoked(grpad->pcb.groupaddr);
		    RemoveGroupDescriptor(grpad);
		}
		else {
		    if (((key1 != 0) || (key2 != 0)) &&
		        ((key1 != grpad->pcb.key1) || (key2 != grpad->pcb.key2))) {
		    	    MembershipRevoked(grpad->pcb.groupaddr);
		    	    RemoveGroupDescriptor(grpad);
		    }
		    else grpad->confirm_timer = code * SLOWTIMEO_FREQUENCY;
		}
		if (m) m_freem(m);
		return;  

	    default:
		if (m) m_freem(m);
		return;
	}
	match->rc = igmp->igmp_code;
	match->groupaddr.s_addr = groupaddr.s_addr;
	match->key1 = key1;
	match->key2 = key2;
	wakeup((caddr_t) &match->rc);
	if (m) m_freem(m);
}

/*ARGSUSED*/
igmp_ctlinput(cmd, arg)
	int cmd;
	struct sockaddr *arg;
{

	if (cmd < 0 || cmd > PRC_NCMDS)
		return;
	/* INCOMPLETE */
}



MembershipRevoked(groupaddr)
struct in_addr groupaddr;
{
    struct inpcb *inp,*pcbhead,*next;
    struct protosw *psw;
  
    while((psw = pffindtype(AF_INET,SOCK_DGRAM)) != 0) {
	pcbhead = findpcbhead(psw->pr_protocol);
	for (inp = pcbhead->inp_next; inp != pcbhead; inp = next) {
	    next = inp->inp_next;
	    if(inp->inp_laddr.s_addr == groupaddr.s_addr)
		in_pcbdetach(inp);
	    if (next == pcbhead) break;
	}
    }
}



struct pcbheadsw headsw[] = {
{IPPROTO_UDP,&udb},
{IPPROTO_TCP,&tcb},
};


struct inpcb *findpcbhead(protocol)
short protocol;
{
    int i;

    for(i = 0; i < (sizeof(headsw)/sizeof(headsw[0])); i++) {
	if(protocol == headsw[i].protocol) {
	    return(headsw[i].head);
	}
    }
    return(NULL);
}
#endif	IGMPROTO
