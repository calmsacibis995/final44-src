h13455
s 00001/00001/00146
d D 8.2 95/04/28 16:53:21 sklower 5 4
c add a statistic that netBSD keeps
e
s 00002/00002/00145
d D 8.1 93/06/10 23:05:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00146
d D 7.3 93/06/04 17:23:35 bostic 3 2
c prototype everything
e
s 00000/00008/00147
d D 7.2 92/07/08 23:17:54 sklower 2 1
c remove duplicate copyright crap
e
s 00155/00000/00000
d D 7.1 92/07/08 23:16:03 sklower 1 0
c date and time created 92/07/08 23:16:03 by sklower
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 Stephen Deering.
D 4
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Definitions for the kernel part of DVMRP,
 * a Distance-Vector Multicast Routing Protocol.
 * (See RFC-1075.)
 *
 * Written by David Waitzman, BBN Labs, August 1988.
 * Modified by Steve Deering, Stanford, February 1989.
 *
 * MROUTING 1.0
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

/*
 * DVMRP-specific setsockopt commands.
 */
#define	DVMRP_INIT	100
#define	DVMRP_DONE	101
#define	DVMRP_ADD_VIF	102
#define	DVMRP_DEL_VIF	103
#define	DVMRP_ADD_LGRP	104
#define	DVMRP_DEL_LGRP	105
#define	DVMRP_ADD_MRT	106
#define	DVMRP_DEL_MRT	107


/*
 * Types and macros for handling bitmaps with one bit per virtual interface.
 */
#define	MAXVIFS 32
typedef u_long vifbitmap_t;
typedef u_short vifi_t;		/* type of a vif index */

#define	VIFM_SET(n, m)		((m) |= (1 << (n)))
#define	VIFM_CLR(n, m)		((m) &= ~(1 << (n)))
#define	VIFM_ISSET(n, m)	((m) & (1 << (n)))
#define	VIFM_CLRALL(m)		((m) = 0x00000000)
#define	VIFM_COPY(mfrom, mto)	((mto) = (mfrom))
#define	VIFM_SAME(m1, m2)	((m1) == (m2))


/*
 * Agument structure for DVMRP_ADD_VIF.
 * (DVMRP_DEL_VIF takes a single vifi_t argument.)
 */
struct vifctl {
	vifi_t	    vifc_vifi;	    	/* the index of the vif to be added */
	u_char	    vifc_flags;     	/* VIFF_ flags defined below */
	u_char	    vifc_threshold; 	/* min ttl required to forward on vif */
	struct	in_addr vifc_lcl_addr;	/* local interface address */
	struct	in_addr vifc_rmt_addr;	/* remote address (tunnels only) */
};

#define	VIFF_TUNNEL	0x1		/* vif represents a tunnel end-point */


/*
 * Argument structure for DVMRP_ADD_LGRP and DVMRP_DEL_LGRP.
 */
struct lgrplctl {
	vifi_t	lgc_vifi;
	struct	in_addr lgc_gaddr;
};


/*
 * Argument structure for DVMRP_ADD_MRT.
 * (DVMRP_DEL_MRT takes a single struct in_addr argument, containing origin.)
 */
struct mrtctl {
	struct	in_addr mrtc_origin;	/* subnet origin of multicasts */
	struct	in_addr mrtc_originmask; /* subnet mask for origin */
	vifi_t	mrtc_parent;    	/* incoming vif */
	vifbitmap_t mrtc_children;	/* outgoing children vifs */
	vifbitmap_t mrtc_leaves;	/* subset of outgoing children vifs */
};


#ifdef KERNEL

/*
 * The kernel's virtual-interface structure.
 */
struct vif {
	u_char	v_flags;		/* VIFF_ flags defined above */
	u_char	v_threshold;		/* min ttl required to forward on vif */
	struct	in_addr v_lcl_addr;	/* local interface address */
	struct	in_addr v_rmt_addr;	/* remote address (tunnels only) */
	struct	ifnet  *v_ifp;		/* pointer to interface */
	struct	in_addr *v_lcl_grps;	/* list of local grps (phyints only) */
	int	v_lcl_grps_max;		/* malloc'ed number of v_lcl_grps */
	int	v_lcl_grps_n;		/* used number of v_lcl_grps */
	u_long	v_cached_group;		/* last grp looked-up (phyints only) */
	int	v_cached_result;	/* last look-up result (phyints only) */
};

/*
 * The kernel's multicast route structure.
 */
struct mrt {
	struct	in_addr mrt_origin;	/* subnet origin of multicasts */
	struct	in_addr mrt_originmask;	/* subnet mask for origin */
	vifi_t	mrt_parent;    		/* incoming vif */
	vifbitmap_t mrt_children;	/* outgoing children vifs */
	vifbitmap_t mrt_leaves;		/* subset of outgoing children vifs */
	struct	mrt *mrt_next;		/* forward link */
};


#define	MRTHASHSIZ	64
#if (MRTHASHSIZ & (MRTHASHSIZ - 1)) == 0	  /* from sys:route.h */
#define	MRTHASHMOD(h)	((h) & (MRTHASHSIZ - 1))
#else
#define	MRTHASHMOD(h)	((h) % MRTHASHSIZ)
#endif

/*
 * The kernel's multicast routing statistics.
 */
struct mrtstat {
	u_long	mrts_mrt_lookups;	/* # multicast route lookups */
	u_long	mrts_mrt_misses;	/* # multicast route cache misses */
	u_long	mrts_grp_lookups;	/* # group address lookups */
	u_long	mrts_grp_misses;	/* # group address cache misses */
	u_long	mrts_no_route;		/* no route for packet's origin */
	u_long	mrts_bad_tunnel;	/* malformed tunnel options */
	u_long	mrts_cant_tunnel;	/* no room for tunnel options */
I 5
	u_long	mrts_wrong_if;		/* arrived on the wrong interface */
E 5
};


int	ip_mrouter_cmd __P((int, struct socket *, struct mbuf *));
D 3
int	ip_mrouter_done __P(());
E 3
I 3
int	ip_mrouter_done __P((void));
E 3

#endif /* KERNEL */
D 5

E 5
E 1
