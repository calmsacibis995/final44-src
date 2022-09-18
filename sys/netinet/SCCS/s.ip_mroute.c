h22782
s 00000/00001/00808
d D 8.2 93/11/15 13:34:11 sklower 7 6
c af.h has been retire
e
s 00002/00002/00807
d D 8.1 93/06/10 23:05:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00017/00791
d D 7.5 93/01/08 18:42:54 andrew 5 4
c (By Sklower) checkpoint the current state of Cherenson's work.
e
s 00004/00005/00804
d D 7.4 92/11/19 19:23:01 torek 4 3
c fix infinite loop as pointed out by gcc2
e
s 00022/00022/00787
d D 7.3 92/10/11 12:01:59 bostic 3 2
c make kernel includes standard
e
s 00000/00008/00809
d D 7.2 92/07/08 23:17:52 sklower 2 1
c remove duplicate copyright crap
e
s 00817/00000/00000
d D 7.1 92/07/08 23:16:02 sklower 1 0
c date and time created 92/07/08 23:16:02 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 Stephen Deering
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Procedures for the kernel part of DVMRP,
 * a Distance-Vector Multicast Routing Protocol.
 * (See RFC-1075.)
 *
 * Written by David Waitzman, BBN Labs, August 1988.
 * Modified by Steve Deering, Stanford, February 1989.
 *
 * MROUTING 1.1
 */

D 2
/*
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */
E 2
#ifndef MROUTING
int	ip_mrtproto;				/* for netstat only */
#else

D 3
#include "param.h"
#include "errno.h"
#include "ioctl.h"
#include "malloc.h"
#include "mbuf.h"
#include "protosw.h"
#include "socket.h"
#include "socketvar.h"
#include "time.h"
E 3
I 3
#include <sys/param.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/time.h>
E 3

D 3
#include "../net/af.h"
#include "../net/if.h"
#include "../net/route.h"
#include "../net/raw_cb.h"
E 3
I 3
D 7
#include <net/af.h>
E 7
#include <net/if.h>
#include <net/route.h>
#include <net/raw_cb.h>
E 3

D 3
#include "in.h"
#include "in_systm.h"
#include "ip.h"
#include "in_pcb.h"
#include "in_var.h"
#include "ip_var.h"
E 3
I 3
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/in_pcb.h>
#include <netinet/in_var.h>
#include <netinet/ip_var.h>
E 3

D 3
#include "igmp.h"
#include "igmp_var.h"
#include "ip_mroute.h"
E 3
I 3
#include <netinet/igmp.h>
#include <netinet/igmp_var.h>
#include <netinet/ip_mroute.h>
E 3

/* Static forwards */
static	int ip_mrouter_init __P((struct socket *));
static	int add_vif __P((struct vifctl *));
static	int del_vif __P((vifi_t *vifip));
static	int add_lgrp __P((struct lgrplctl *));
static	int del_lgrp __P((struct lgrplctl *));
static	int grplst_member __P((struct vif *, struct in_addr));
static	u_long nethash __P((struct in_addr in));
static	int add_mrt __P((struct mrtctl *));
static	int del_mrt __P((struct in_addr *));
static	struct mrt *mrtfind __P((struct in_addr));
static	void phyint_send __P((struct mbuf *, struct vif *));
static	void tunnel_send __P((struct mbuf *, struct vif *));

#define INSIZ sizeof(struct in_addr)
#define	same(a1, a2) (bcmp((caddr_t)(a1), (caddr_t)(a2), INSIZ) == 0)
#define	satosin(sa)	((struct sockaddr_in *)(sa))

/*
 * Globals.  All but ip_mrouter and ip_mrtproto could be static,
 * except for netstat or debugging purposes.
 */
struct	socket *ip_mrouter = NULL;
int	ip_mrtproto = IGMP_DVMRP;		/* for netstat only */

struct	mrt *mrttable[MRTHASHSIZ];
struct	vif viftable[MAXVIFS];
struct	mrtstat	mrtstat;

/*
 * Private variables.
 */
static	vifi_t numvifs = 0;
static	struct mrt *cached_mrt = NULL;
static	u_long cached_origin;
static	u_long cached_originmask;

/*
 * Handle DVMRP setsockopt commands to modify the multicast routing tables.
 */
int
ip_mrouter_cmd(cmd, so, m)
	register int cmd;
	register struct socket *so;
	register struct mbuf *m;
{
	register int error = 0;

	if (cmd != DVMRP_INIT && so != ip_mrouter)
		error = EACCES;
	else switch (cmd) {

	case DVMRP_INIT:
		error = ip_mrouter_init(so);
		break;

	case DVMRP_DONE:
		error = ip_mrouter_done();
		break;

	case DVMRP_ADD_VIF:
		if (m == NULL || m->m_len < sizeof(struct vifctl))
			error = EINVAL;
		else
			error = add_vif(mtod(m, struct vifctl *));
		break;

	case DVMRP_DEL_VIF:
		if (m == NULL || m->m_len < sizeof(short))
			error = EINVAL;
		else
			error = del_vif(mtod(m, vifi_t *));
		break;

	case DVMRP_ADD_LGRP:
		if (m == NULL || m->m_len < sizeof(struct lgrplctl))
			error = EINVAL;
		else
			error = add_lgrp(mtod(m, struct lgrplctl *));
		break;

	case DVMRP_DEL_LGRP:
		if (m == NULL || m->m_len < sizeof(struct lgrplctl))
			error = EINVAL;
		else
			error = del_lgrp(mtod(m, struct lgrplctl *));
		break;

	case DVMRP_ADD_MRT:
		if (m == NULL || m->m_len < sizeof(struct mrtctl))
			error = EINVAL;
		else
			error = add_mrt(mtod(m, struct mrtctl *));
		break;

	case DVMRP_DEL_MRT:
		if (m == NULL || m->m_len < sizeof(struct in_addr))
			error = EINVAL;
		else
			error = del_mrt(mtod(m, struct in_addr *));
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}
	return (error);
}

/*
 * Enable multicast routing
 */
static int
ip_mrouter_init(so)
	register struct socket *so;
{
	if (so->so_type != SOCK_RAW ||
	    so->so_proto->pr_protocol != IPPROTO_IGMP)
		return (EOPNOTSUPP);

	if (ip_mrouter != NULL)
		return (EADDRINUSE);

	ip_mrouter = so;

	return (0);
}

/*
 * Disable multicast routing
 */
int
ip_mrouter_done()
{
	register vifi_t vifi;
	register int i;
	register struct ifnet *ifp;
	register int s;
	struct ifreq ifr;

	s = splnet();

	/*
	 * For each phyint in use, free its local group list and
	 * disable promiscuous reception of all IP multicasts.
	 */
	for (vifi = 0; vifi < numvifs; vifi++) {
		if (viftable[vifi].v_lcl_addr.s_addr != 0 &&
		    !(viftable[vifi].v_flags & VIFF_TUNNEL)) {
			if (viftable[vifi].v_lcl_grps)
				free(viftable[vifi].v_lcl_grps, M_MRTABLE);
			satosin(&ifr.ifr_addr)->sin_family = AF_INET;
			satosin(&ifr.ifr_addr)->sin_addr.s_addr = INADDR_ANY;
			ifp = viftable[vifi].v_ifp;
			(*ifp->if_ioctl)(ifp, SIOCDELMULTI, (caddr_t)&ifr);
		}
	}
	bzero((caddr_t)viftable, sizeof(viftable));
	numvifs = 0;

	/*
	 * Free any multicast route entries.
	 */
	for (i = 0; i < MRTHASHSIZ; i++)
		if (mrttable[i])
			free(mrttable[i], M_MRTABLE);
	bzero((caddr_t)mrttable, sizeof(mrttable));
	cached_mrt = NULL;

	ip_mrouter = NULL;

	splx(s);
	return (0);
}

/*
 * Add a vif to the vif table
 */
static int
add_vif(vifcp)
	register struct vifctl *vifcp;
{
	register struct vif *vifp = viftable + vifcp->vifc_vifi;
	register struct ifaddr *ifa;
	register struct ifnet *ifp;
	struct ifreq ifr;
	register int error, s;
	static struct sockaddr_in sin = { sizeof(sin), AF_INET };

	if (vifcp->vifc_vifi >= MAXVIFS)
		return (EINVAL);
	if (vifp->v_lcl_addr.s_addr != 0)
		return (EADDRINUSE);

	/* Find the interface with an address in AF_INET family */
	sin.sin_addr = vifcp->vifc_lcl_addr;
	ifa = ifa_ifwithaddr((struct sockaddr *)&sin);
	if (ifa == 0)
		return (EADDRNOTAVAIL);

	s = splnet();

	if (vifcp->vifc_flags & VIFF_TUNNEL)
		vifp->v_rmt_addr = vifcp->vifc_rmt_addr;
	else {
		/* Make sure the interface supports multicast */
		ifp = ifa->ifa_ifp;
		if ((ifp->if_flags & IFF_MULTICAST) == 0) {
			splx(s);
			return (EOPNOTSUPP);
		}
		/*
		 * Enable promiscuous reception of all IP multicasts
		 * from the interface.
		 */
		satosin(&ifr.ifr_addr)->sin_family = AF_INET;
		satosin(&ifr.ifr_addr)->sin_addr.s_addr = INADDR_ANY;
		error = (*ifp->if_ioctl)(ifp, SIOCADDMULTI, (caddr_t)&ifr);
		if (error) {
			splx(s);
			return (error);
		}
	}

	vifp->v_flags = vifcp->vifc_flags;
	vifp->v_threshold = vifcp->vifc_threshold;
	vifp->v_lcl_addr = vifcp->vifc_lcl_addr;
	vifp->v_ifp = ifa->ifa_ifp;

	/* Adjust numvifs up if the vifi is higher than numvifs */
	if (numvifs <= vifcp->vifc_vifi)
		numvifs = vifcp->vifc_vifi + 1;

	splx(s);
	return (0);
}

/*
 * Delete a vif from the vif table
 */
static int
del_vif(vifip)
	register vifi_t *vifip;
{
	register struct vif *vifp = viftable + *vifip;
D 4
	register vifi_t vifi;
E 4
	register struct ifnet *ifp;
D 4
	register int s;
E 4
I 4
	register int i, s;
E 4
	struct ifreq ifr;

	if (*vifip >= numvifs)
		return (EINVAL);
	if (vifp->v_lcl_addr.s_addr == 0)
		return (EADDRNOTAVAIL);

	s = splnet();

	if (!(vifp->v_flags & VIFF_TUNNEL)) {
		if (vifp->v_lcl_grps)
			free(vifp->v_lcl_grps, M_MRTABLE);
		satosin(&ifr.ifr_addr)->sin_family = AF_INET;
		satosin(&ifr.ifr_addr)->sin_addr.s_addr = INADDR_ANY;
		ifp = vifp->v_ifp;
		(*ifp->if_ioctl)(ifp, SIOCDELMULTI, (caddr_t)&ifr);
	}

	bzero((caddr_t)vifp, sizeof (*vifp));

	/* Adjust numvifs down */
D 4
	for (vifi = numvifs - 1; vifi >= 0; vifi--)
		if (viftable[vifi].v_lcl_addr.s_addr != 0)
E 4
I 4
	for (i = numvifs - 1; i >= 0; i--)
		if (viftable[i].v_lcl_addr.s_addr != 0)
E 4
			break;
D 4
	numvifs = vifi + 1;
E 4
I 4
	numvifs = i + 1;
E 4

	splx(s);
	return (0);
}

/*
 * Add the multicast group in the lgrpctl to the list of local multicast
 * group memberships associated with the vif indexed by gcp->lgc_vifi.
 */
static int
add_lgrp(gcp)
	register struct lgrplctl *gcp;
{
	register struct vif *vifp;
	register int s;

	if (gcp->lgc_vifi >= numvifs)
		return (EINVAL);

	vifp = viftable + gcp->lgc_vifi;
	if (vifp->v_lcl_addr.s_addr == 0 || (vifp->v_flags & VIFF_TUNNEL))
		return (EADDRNOTAVAIL);

	/* If not enough space in existing list, allocate a larger one */
	s = splnet();
	if (vifp->v_lcl_grps_n + 1 >= vifp->v_lcl_grps_max) {
		register int num;
		register struct in_addr *ip;

		num = vifp->v_lcl_grps_max;
		if (num <= 0)
			num = 32;	/* initial number */
		else
			num += num;	/* double last number */
		ip = (struct in_addr *)malloc(num * sizeof(*ip),
		    M_MRTABLE, M_NOWAIT);
		if (ip == NULL) {
			splx(s);
			return (ENOBUFS);
		}

		bzero((caddr_t)ip, num * sizeof(*ip));	/* XXX paranoid */
		bcopy((caddr_t)vifp->v_lcl_grps, (caddr_t)ip,
		    vifp->v_lcl_grps_n * sizeof(*ip));

		vifp->v_lcl_grps_max = num;
		if (vifp->v_lcl_grps)
			free(vifp->v_lcl_grps, M_MRTABLE);
		vifp->v_lcl_grps = ip;

		splx(s);
	}

	vifp->v_lcl_grps[vifp->v_lcl_grps_n++] = gcp->lgc_gaddr;

	if (gcp->lgc_gaddr.s_addr == vifp->v_cached_group)
		vifp->v_cached_result = 1;

	splx(s);
	return (0);
}

/*
 * Delete the the local multicast group associated with the vif
 * indexed by gcp->lgc_vifi.
 */

static int
del_lgrp(gcp)
	register struct lgrplctl *gcp;
{
	register struct vif *vifp;
	register int i, error, s;

	if (gcp->lgc_vifi >= numvifs)
		return (EINVAL);
	vifp = viftable + gcp->lgc_vifi;
	if (vifp->v_lcl_addr.s_addr == 0 || (vifp->v_flags & VIFF_TUNNEL))
		return (EADDRNOTAVAIL);

	s = splnet();

	if (gcp->lgc_gaddr.s_addr == vifp->v_cached_group)
		vifp->v_cached_result = 0;

	error = EADDRNOTAVAIL;
	for (i = 0; i < vifp->v_lcl_grps_n; ++i)
		if (same(&gcp->lgc_gaddr, &vifp->v_lcl_grps[i])) {
			error = 0;
			vifp->v_lcl_grps_n--;
			bcopy((caddr_t)&vifp->v_lcl_grps[i + 1],
			    (caddr_t)&vifp->v_lcl_grps[i],
			    (vifp->v_lcl_grps_n - i) * sizeof(struct in_addr));
			error = 0;
			break;
		}

	splx(s);
	return (error);
}

/*
 * Return 1 if gaddr is a member of the local group list for vifp.
 */
static int
grplst_member(vifp, gaddr)
	register struct vif *vifp;
	struct in_addr gaddr;
{
	register int i, s;
	register u_long addr;

	mrtstat.mrts_grp_lookups++;

	addr = gaddr.s_addr;
	if (addr == vifp->v_cached_group)
		return (vifp->v_cached_result);

	mrtstat.mrts_grp_misses++;

	for (i = 0; i < vifp->v_lcl_grps_n; ++i)
		if (addr == vifp->v_lcl_grps[i].s_addr) {
			s = splnet();
			vifp->v_cached_group = addr;
			vifp->v_cached_result = 1;
			splx(s);
			return (1);
		}
	s = splnet();
	vifp->v_cached_group = addr;
	vifp->v_cached_result = 0;
	splx(s);
	return (0);
}

/*
 * A simple hash function: returns MRTHASHMOD of the low-order octet of
 * the argument's network or subnet number.
 */
static u_long
nethash(in)
	struct in_addr in;
{
	register u_long n;

	n = in_netof(in);
	while ((n & 0xff) == 0)
		n >>= 8;
	return (MRTHASHMOD(n));
}

/*
 * Add an mrt entry
 */
static int
add_mrt(mrtcp)
	register struct mrtctl *mrtcp;
{
	struct mrt *rt;
	u_long hash;
	int s;

	if (rt = mrtfind(mrtcp->mrtc_origin)) {
		/* Just update the route */
		s = splnet();
		rt->mrt_parent = mrtcp->mrtc_parent;
		VIFM_COPY(mrtcp->mrtc_children, rt->mrt_children);
		VIFM_COPY(mrtcp->mrtc_leaves, rt->mrt_leaves);
		splx(s);
		return (0);
	}

	s = splnet();

	rt = (struct mrt *)malloc(sizeof(*rt), M_MRTABLE, M_NOWAIT);
	if (rt == NULL) {
		splx(s);
		return (ENOBUFS);
	}

	/*
	 * insert new entry at head of hash chain
	 */
	rt->mrt_origin = mrtcp->mrtc_origin;
	rt->mrt_originmask = mrtcp->mrtc_originmask;
	rt->mrt_parent = mrtcp->mrtc_parent;
	VIFM_COPY(mrtcp->mrtc_children, rt->mrt_children);
	VIFM_COPY(mrtcp->mrtc_leaves, rt->mrt_leaves);
	/* link into table */
	hash = nethash(mrtcp->mrtc_origin);
	rt->mrt_next = mrttable[hash];
	mrttable[hash] = rt;

	splx(s);
	return (0);
}

/*
 * Delete an mrt entry
 */
static int
del_mrt(origin)
	register struct in_addr *origin;
{
	register struct mrt *rt, *prev_rt;
	register u_long hash = nethash(*origin);
	register int s;

	for (prev_rt = rt = mrttable[hash]; rt; prev_rt = rt, rt = rt->mrt_next)
		if (origin->s_addr == rt->mrt_origin.s_addr)
			break;
	if (!rt)
		return (ESRCH);

	s = splnet();

	if (rt == cached_mrt)
		cached_mrt = NULL;

	if (prev_rt == rt)
		mrttable[hash] = rt->mrt_next;
	else
		prev_rt->mrt_next = rt->mrt_next;
	free(rt, M_MRTABLE);

	splx(s);
	return (0);
}

/*
 * Find a route for a given origin IP address.
 */
static struct mrt *
mrtfind(origin)
	struct in_addr origin;
{
	register struct mrt *rt;
	register u_int hash;
	register int s;

	mrtstat.mrts_mrt_lookups++;

	if (cached_mrt != NULL &&
	    (origin.s_addr & cached_originmask) == cached_origin)
		return (cached_mrt);

	mrtstat.mrts_mrt_misses++;

	hash = nethash(origin);
	for (rt = mrttable[hash]; rt; rt = rt->mrt_next)
		if ((origin.s_addr & rt->mrt_originmask.s_addr) ==
		    rt->mrt_origin.s_addr) {
			s = splnet();
			cached_mrt = rt;
			cached_origin = rt->mrt_origin.s_addr;
			cached_originmask = rt->mrt_originmask.s_addr;
			splx(s);
			return (rt);
		}
	return (NULL);
}

/*
 * IP multicast forwarding function. This function assumes that the packet
 * pointed to by "ip" has arrived on (or is about to be sent to) the interface
 * pointed to by "ifp", and the packet is to be relayed to other networks
 * that have members of the packet's destination IP multicast group.
 *
 * The packet is returned unscathed to the caller, unless it is tunneled
 * or erroneous, in which case a non-zero return value tells the caller to
 * discard it.
 */

#define IP_HDR_LEN  20	/* # bytes of fixed IP header (excluding options) */
#define TUNNEL_LEN  12  /* # bytes of IP option for tunnel encapsulation  */

int
ip_mforward(m, ifp)
	register struct mbuf *m;
	register struct ifnet *ifp;
{
	register struct ip *ip = mtod(m, struct ip *);
	register struct mrt *rt;
	register struct vif *vifp;
	register int vifi;
	register u_char *ipoptions;
	u_long tunnel_src;

	if (ip->ip_hl < (IP_HDR_LEN + TUNNEL_LEN) >> 2 ||
	    (ipoptions = (u_char *)(ip + 1))[1] != IPOPT_LSRR ) {
		/*
		 * Packet arrived via a physical interface.
		 */
		tunnel_src = 0;
	} else {
		/*
		 * Packet arrived through a tunnel.
		 *
		 * A tunneled packet has a single NOP option and a
		 * two-element loose-source-and-record-route (LSRR)
		 * option immediately following the fixed-size part of
		 * the IP header.  At this point in processing, the IP
		 * header should contain the following IP addresses:
		 *
		 * original source          - in the source address field
		 * destination group        - in the destination address field
		 * remote tunnel end-point  - in the first  element of LSRR
		 * one of this host's addrs - in the second element of LSRR
		 *
		 * NOTE: RFC-1075 would have the original source and
		 * remote tunnel end-point addresses swapped.  However,
		 * that could cause delivery of ICMP error messages to
		 * innocent applications on intermediate routing
		 * hosts!  Therefore, we hereby change the spec.
		 */

		/*
		 * Verify that the tunnel options are well-formed.
		 */
		if (ipoptions[0] != IPOPT_NOP ||
		    ipoptions[2] != 11 ||	/* LSRR option length   */
		    ipoptions[3] != 12 ||	/* LSRR address pointer */
		    (tunnel_src = *(u_long *)(&ipoptions[4])) == 0) {
			mrtstat.mrts_bad_tunnel++;
			return (1);
		}

		/*
		 * Delete the tunnel options from the packet.
		 */
		ovbcopy((caddr_t)(ipoptions + TUNNEL_LEN), (caddr_t)ipoptions,
		    (unsigned)(m->m_len - (IP_HDR_LEN + TUNNEL_LEN)));
		m->m_len -= TUNNEL_LEN;
		ip->ip_len -= TUNNEL_LEN;
		ip->ip_hl -= TUNNEL_LEN >> 2;
	}

	/*
	 * Don't forward a packet with time-to-live of zero or one,
	 * or a packet destined to a local-only group.
	 */
	if (ip->ip_ttl <= 1 ||
	    ntohl(ip->ip_dst.s_addr) <= INADDR_MAX_LOCAL_GROUP)
		return ((int)tunnel_src);

	/*
	 * Don't forward if we don't have a route for the packet's origin.
	 */
	if (!(rt = mrtfind(ip->ip_src))) {
		mrtstat.mrts_no_route++;
		return ((int)tunnel_src);
	}

	/*
	 * Don't forward if it didn't arrive from the parent vif for its origin.
	 */
	vifi = rt->mrt_parent;
	if (tunnel_src == 0 ) {
		if ((viftable[vifi].v_flags & VIFF_TUNNEL) ||
		    viftable[vifi].v_ifp != ifp )
			return ((int)tunnel_src);
	} else {
		if (!(viftable[vifi].v_flags & VIFF_TUNNEL) ||
		    viftable[vifi].v_rmt_addr.s_addr != tunnel_src )
			return ((int)tunnel_src);
	}

	/*
	 * For each vif, decide if a copy of the packet should be forwarded.
	 * Forward if:
	 *		- the ttl exceeds the vif's threshold AND
	 *		- the vif is a child in the origin's route AND
	 *		- ( the vif is not a leaf in the origin's route OR
	 *		    the destination group has members on the vif )
	 *
	 * (This might be speeded up with some sort of cache -- someday.)
	 */
	for (vifp = viftable, vifi = 0; vifi < numvifs; vifp++, vifi++) {
		if (ip->ip_ttl > vifp->v_threshold &&
		    VIFM_ISSET(vifi, rt->mrt_children) &&
		    (!VIFM_ISSET(vifi, rt->mrt_leaves) ||
		    grplst_member(vifp, ip->ip_dst))) {
			if (vifp->v_flags & VIFF_TUNNEL)
				tunnel_send(m, vifp);
			else
				phyint_send(m, vifp);
		}
	}

	return ((int)tunnel_src);
}

static void
phyint_send(m, vifp)
	register struct mbuf *m;
	register struct vif *vifp;
{
	register struct ip *ip = mtod(m, struct ip *);
	register struct mbuf *mb_copy;
	register struct ip_moptions *imo;
	register int error;
	struct ip_moptions simo;

	mb_copy = m_copy(m, 0, M_COPYALL);
	if (mb_copy == NULL)
		return;

	imo = &simo;
	imo->imo_multicast_ifp = vifp->v_ifp;
	imo->imo_multicast_ttl = ip->ip_ttl - 1;
	imo->imo_multicast_loop = 1;

	error = ip_output(mb_copy, NULL, NULL, IP_FORWARDING, imo);
}

static void
tunnel_send(m, vifp)
	register struct mbuf *m;
	register struct vif *vifp;
{
	register struct ip *ip = mtod(m, struct ip *);
	register struct mbuf *mb_copy, *mb_opts;
	register struct ip *ip_copy;
	register int error;
	register u_char *cp;

	/*
	 * Make sure that adding the tunnel options won't exceed the
	 * maximum allowed number of option bytes.
	 */
	if (ip->ip_hl > (60 - TUNNEL_LEN) >> 2) {
		mrtstat.mrts_cant_tunnel++;
		return;
	}

D 5
	mb_copy = m_copy(m, 0, M_COPYALL);
E 5
I 5
	/* 
	 * Get a private copy of the IP header so that changes to some 
	 * of the IP fields don't damage the original header, which is
	 * examined later in ip_input.c.
	 */
	mb_copy = m_copy(m, IP_HDR_LEN, M_COPYALL);
E 5
	if (mb_copy == NULL)
		return;
D 5
	ip_copy = mtod(mb_copy, struct ip *);
	ip_copy->ip_ttl--;
	ip_copy->ip_dst = vifp->v_rmt_addr;	/* remote tunnel end-point */
	/*
	 * Adjust the ip header length to account for the tunnel options.
	 */
	ip_copy->ip_hl += TUNNEL_LEN >> 2;
	ip_copy->ip_len += TUNNEL_LEN;
E 5
	MGETHDR(mb_opts, M_DONTWAIT, MT_HEADER);
	if (mb_opts == NULL) {
		m_freem(mb_copy);
		return;
	}
	/*
D 5
	 * 'Delete' the base ip header from the mb_copy chain
	 */
	mb_copy->m_len -= IP_HDR_LEN;
	mb_copy->m_data += IP_HDR_LEN;
	/*
E 5
	 * Make mb_opts be the new head of the packet chain.
	 * Any options of the packet were left in the old packet chain head
	 */
	mb_opts->m_next = mb_copy;
	mb_opts->m_len = IP_HDR_LEN + TUNNEL_LEN;
	mb_opts->m_data += MSIZE - mb_opts->m_len;
I 5

	ip_copy = mtod(mb_opts, struct ip *);
E 5
	/*
D 5
	 * Copy the base ip header from the mb_copy chain to the new head mbuf
E 5
I 5
	 * Copy the base ip header to the new head mbuf.
E 5
	 */
D 5
	bcopy((caddr_t)ip_copy, mtod(mb_opts, caddr_t), IP_HDR_LEN);
E 5
I 5
	*ip_copy = *ip;
	ip_copy->ip_ttl--;
	ip_copy->ip_dst = vifp->v_rmt_addr;	/* remote tunnel end-point */
E 5
	/*
I 5
	 * Adjust the ip header length to account for the tunnel options.
	 */
	ip_copy->ip_hl += TUNNEL_LEN >> 2;
	ip_copy->ip_len += TUNNEL_LEN;
	/*
E 5
	 * Add the NOP and LSRR after the base ip header
	 */
D 5
	cp = mtod(mb_opts, u_char *) + IP_HDR_LEN;
E 5
I 5
	cp = (u_char *)(ip_copy + 1);
E 5
	*cp++ = IPOPT_NOP;
	*cp++ = IPOPT_LSRR;
	*cp++ = 11;		/* LSRR option length */
	*cp++ = 8;		/* LSSR pointer to second element */
	*(u_long*)cp = vifp->v_lcl_addr.s_addr;	/* local tunnel end-point */
	cp += 4;
	*(u_long*)cp = ip->ip_dst.s_addr;		/* destination group */

	error = ip_output(mb_opts, NULL, NULL, IP_FORWARDING, NULL);
}
#endif
E 1
