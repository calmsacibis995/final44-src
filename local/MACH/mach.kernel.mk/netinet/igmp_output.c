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
 * $Log:	igmp_output.c,v $
 * Revision 2.3  89/03/09  20:43:41  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:58:40  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 *	igmp_output.c
 */

#include "igmproto.h"
#include "multicast_agent.h"

#if	IGMPROTO

#include <sys/param.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/socketvar.h>
#include <sys/errno.h>

#include <net/if.h>
#include <net/route.h>

#include "in_systm.h"
#include "in.h"
#include "in_var.h"
#include "ip.h"
#include "ip_var.h"
#include "group.h"
#if	MULTICAST_AGENT
#include "agent_var.h"
#endif	MULTICAST_AGENT

struct GroupDescriptor *FindGroupDescriptor();
struct socket *gets();
struct mbuf *m_copy();
extern u_long unique;
extern struct ifnet loif;

/*
 * Use this if igmp packet is passed into the kernel from user space.
 */
igmp_output(m0, so, to)
	struct mbuf *m0;
	struct socket *so;
	struct mbuf *to;
{
	register struct mbuf *m;
	register struct ip *ip;
	int len = 0;
	struct sockaddr_in *dst;
#if	MULTICAST_AGENT
	struct igmp *igmp;
	u_char type,code;
	struct sockaddr_in *rtaddr;
	struct route ro;
	struct rtentry rt;
#endif	MULTICAST_AGENT

	/*
	 * Calculate data length and get an mbuf
	 * for IP header.
	 */
	for (m = m0; m; m = m->m_next)
		len += m->m_len;
	m = m_get(M_DONTWAIT, MT_HEADER);
	if (m == 0) return(ENOBUFS);

	dst = mtod(to, struct sockaddr_in *);
	
#if	MULTICAST_AGENT
	if (agentsocket) {
	    igmp = mtod(m0, struct igmp *);
	    type = igmp->igmp_type;
	    code = igmp->igmp_code;
	}
#endif	MULTICAST_AGENT

	/*
	 * Fill in IP header as needed.
	 */
	m->m_off = MMAXOFF - sizeof(struct ip);
	m->m_len = sizeof(struct ip);
	m->m_next = m0;
	ip = mtod(m, struct ip *);
	ip->ip_tos = 0;
	ip->ip_off = 0;
	ip->ip_p = IPPROTO_IGMP; 
	ip->ip_len = sizeof(struct ip) + len;
	ip->ip_src.s_addr = INADDR_ANY; 
	ip->ip_dst.s_addr = dst->sin_addr.s_addr;
#if	MULTICAST_AGENT
	if ((agentsocket) && (type == IGMP_MEMBERSHIP_UPDATE))
	    ip->ip_ttl = UPDATE_TTL;
	else
#endif	MULTICAST_AGENT
	    ip->ip_ttl = 1;
#if	MULTICAST_AGENT

	/* This is an ugly kludge to make GRANTED Confirm Group Replies */
	/* (which will be addressed to a Class D address) go out the    */
	/* interface that was last stuffed into the agentsocket's pcb   */
	/* (in the SIOCCONFIRMGROUP ioctl in agent.c) rather than the   */
	/* default 224 route's ifp.					*/

	if ((agentsocket) && (type == IGMP_CONFIRM_GROUP_REPLY)) {
	    if ((code == IGMP_REQUEST_GRANTED) ||
	        (code > IGMP_MAXCODE)) {
	        rtaddr = (struct sockaddr_in *) &ro.ro_dst;
	        rtaddr->sin_family = AF_INET;
	        rtaddr->sin_addr.s_addr = ip->ip_dst.s_addr;
	        ro.ro_rt = &rt;
	        ro.ro_rt->rt_flags = RTF_UP; 
	        ro.ro_rt->rt_refcnt = 1;
    	        ro.ro_rt->rt_use = 0;
	        ro.ro_rt->rt_ifp = ((struct igmpcb *) (agentsocket->so_pcb))->ifp;
	        return (ip_output(m, (struct mbuf *)0,&ro,IP_NOLOOPBACK)); 
	    }
	    else
	        return (ip_output(m, (struct mbuf *)0, 
		    (struct route *)0, IP_NOLOOPBACK)); 
	}
	else
#endif	MULTICAST_AGENT
	    return (ip_output(m, (struct mbuf *)0, (struct route *)0, 0)); 
}

/*
 * IGMP IP socket option processing.
 */
igmp_ctloutput(op, so, level, optname, m)
	int op;
	struct socket *so;
	int level, optname;
	struct mbuf **m;
{
	int error = 0;
	register struct igmpcb *igmpcb = sotoigmpcb(so);

	if (level != IPPROTO_IP)
		error = EINVAL;
	else switch (op) {

	case PRCO_SETOPT:
		switch (optname) {
		case IP_OPTIONS:
			return (ip_pcbopts(&igmpcb->options, *m));

		default:
			error = EINVAL;
			break;
		}
		break;

	case PRCO_GETOPT:
		switch (optname) {
		case IP_OPTIONS:
			*m = m_get(M_WAIT, MT_SOOPTS);
			if (igmpcb->options) {
				(*m)->m_off = igmpcb->options->m_off;
				(*m)->m_len = igmpcb->options->m_len;
				bcopy(mtod(igmpcb->options, caddr_t),
				    mtod(*m, caddr_t), (unsigned)(*m)->m_len);
			} else
				(*m)->m_len = 0;
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


igmp_request(s,type,code,groupaddr,key1,key2,ifp,loopback)
struct socket *s;
u_char type;
u_char code;
struct in_addr groupaddr;
u_long key1;
u_long key2;
struct ifnet *ifp;
u_char loopback;
{
	struct mbuf *m;
	struct igmpiphdr *g;
	struct igmpcb *pcb = NULL;
	struct GroupDescriptor *grpad;
	int left;
	u_long ident,tmp_off;
	short tmp_len;
	struct sockaddr_in *rtaddr;
	struct route ro,tmproute;
	struct rtentry rt;

	if (!IGMP_IS_A_REQUEST(type)) {
	    return(IGMP_INVALID_TYPE);
	}

	if (ifp == NULL) {
	    tmproute.ro_rt = 0;
	    rtaddr = (struct sockaddr_in *) &tmproute.ro_dst;
	    rtaddr->sin_family = AF_INET;
	    rtaddr->sin_addr.s_addr = htonl(0xe0000000);
	    rtalloc(&tmproute);
	    if (tmproute.ro_rt == 0) return(IGMP_NO_INTERFACE);
	    if ((ifp = tmproute.ro_rt->rt_ifp) == NULL) {
		RTFREE(tmproute.ro_rt);
	        return(IGMP_NO_INTERFACE);
	    }
	    RTFREE(tmproute.ro_rt);
	}

	if (s) pcb = sotoigmpcb(s);

	switch(type) {
	    case IGMP_CREATE_GROUP_REQUEST:
		if (!s) return(IGMP_NO_SOCKET);
		groupaddr.s_addr = 0;
		key1 = 0;
		key2 = 0;
		break;
	    case IGMP_JOIN_GROUP_REQUEST:
		if (!s) return(IGMP_NO_SOCKET);
		grpad = FindGroupDescriptor(groupaddr,ifp);
		if (grpad != NULL) {
		    /* Host is already in the group.   */
		    if ((key1 != grpad->pcb.key1) || (key2 != grpad->pcb.key2))
			return(IGMP_INVALID_ACCESS_KEY);
	    	    pcb->type = type;
	    	    pcb->code = code;
	    	    pcb->groupaddr.s_addr = groupaddr.s_addr;
	    	    pcb->key1 = key1;
	    	    pcb->key2 = key2;
	    	    pcb->ifp = ifp;
	    	    pcb->loopback = loopback;
		    AddToPCBList(grpad,pcb);
		    return(IGMP_ALREADY_A_MEMBER);
		}
		code = 0;
		break;
	    case IGMP_LEAVE_GROUP_REQUEST:

		if (s) {  /* Means this was a user request */

		    if (((struct igmpcb *)s->so_pcb)->ad == NULL) { 
			return(IGMP_NOT_A_MEMBER);
		    }

		    grpad = FindGroupDescriptor(groupaddr,ifp);
		    if (grpad == NULL)  {
		        return(IGMP_NOT_A_MEMBER);
		    }

		    if (key1 != grpad->pcb.key1 || key2 != grpad->pcb.key2) {
		        return(IGMP_INVALID_ACCESS_KEY);
		    }

		    if (((struct igmpcb *)s->so_pcb)->ad == grpad) {

		        if (left = 
			DeleteFromPCBList((struct igmpcb *) s->so_pcb)) {

			    if (left == -1) {
			        return(IGMP_NOT_A_MEMBER);
			    }

			    /* The very last one won't be deleted */
		            return(IGMP_REQUEST_GRANTED);
			}
			/* else send a Leave Group Request out */
			/* igmpcb was not removed by DeleteFromPCBList */
		    }
		    else {
			return(IGMP_NOT_A_MEMBER);
		    }
		}
		code = 0;
		break;
	    case IGMP_CONFIRM_GROUP_REQUEST:
		code = 0;
		break;
	    default:
		return(IGMP_INVALID_TYPE);
	}

	/*
	 * First, formulate igmp message
	 */
	m = m_get(M_DONTWAIT, MT_HEADER);
	if (m == NULL) return(IGMP_NO_INTERNAL_RESOURCES);

	m->m_off = MMAXOFF - sizeof(struct igmpiphdr);
	m->m_len = sizeof(struct igmpiphdr);
	g = mtod(m, struct igmpiphdr *);
	if ((u_int)type > IGMP_MAXTYPE)
		panic("igmp_request");

	/* This is to compute checksum of only the igmp part of igmpiphdr */
	tmp_off = m->m_off;
	tmp_len = m->m_len;
	m->m_off += sizeof(struct ip);
	m->m_len = sizeof(struct igmp); 

	g->g.igmp_type = type;
	g->g.igmp_code = code;
	g->g.igmp_groupaddr.s_addr = htonl(groupaddr.s_addr);
	g->g.igmp_key1 = htonl(key1);
	g->g.igmp_key2 = htonl(key2);

	if (type == IGMP_CONFIRM_GROUP_REQUEST) ident = 0;
	else {
	    ident = unique++;
	}
	g->g.igmp_ident = htonl(ident);
	g->g.igmp_cksum = 0;
	g->g.igmp_cksum = in_cksum(m, sizeof(struct igmp));
	m->m_off = tmp_off; 
	m->m_len = tmp_len; 

	if (s) {
	    pcb->rc = IGMP_RC_UNSET;
	    pcb->countdown = IGMP_SLOWTIMEO_COUNTDOWN;
	    pcb->num_rtx = 0;
	    pcb->matched = 0;
	    pcb->options = NULL;
	    pcb->identifier = ident;
	    pcb->type = type;
	    pcb->code = code;
	    pcb->groupaddr.s_addr = groupaddr.s_addr;
	    pcb->key1 = key1;
	    pcb->key2 = key2;
	    pcb->ifp = ifp;
	    if ((type == IGMP_CREATE_GROUP_REQUEST) || 
		(type == IGMP_JOIN_GROUP_REQUEST))
	    	    pcb->loopback = loopback;
	}

	/* Now for the ip parts */

	g->i.ih_next = g->i.ih_prev = 0;
	g->i.ih_x1 = 0;
	g->i.ih_pr = IPPROTO_IGMP;
	g->i.ih_len = sizeof(struct igmpiphdr); 
	g->i.ih_src.s_addr = (IA_SIN(ifptoia(ifp)))->sin_addr.s_addr;
	g->i.ih_dst.s_addr = htonl(INADDR_MA_GROUP);

	rtaddr = (struct sockaddr_in *) &ro.ro_dst;
	rtaddr->sin_family = AF_INET;
	rtaddr->sin_addr.s_addr = g->i.ih_dst.s_addr;
	ro.ro_rt = &rt;
	ro.ro_rt->rt_flags = RTF_UP; 
	ro.ro_rt->rt_refcnt = 1;
	ro.ro_rt->rt_use = 0;
	ro.ro_rt->rt_ifp = ifp;

	((struct ip *) g)->ip_len = sizeof(struct igmpiphdr);
	((struct ip *) g)->ip_ttl = 1;

	if (s) pcb->message = m_copy(m,0,(int) M_COPYALL);
	(void) ip_output(m, (struct mbuf *)NULL, &ro, 0);
        return(IGMP_REQUEST_SENT);
}

#endif	IGMPROTO
