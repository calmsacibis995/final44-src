h45404
s 00001/00001/00173
d D 8.2 95/01/09 18:19:38 cgd 16 15
c ioctl cmd arg is u_long
e
s 00002/00002/00172
d D 8.1 93/06/10 23:04:41 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00170
d D 7.9 93/06/04 17:08:24 bostic 14 13
c prototype everything
e
s 00008/00005/00162
d D 7.8 93/04/07 19:27:59 sklower 13 12
c Mostly changes recommended by jch for variable subnets & multiple
c IP addresses per physical interface. May require further work.
e
s 00117/00000/00050
d D 7.7 92/07/06 15:08:14 sklower 12 11
c multicast changes from lbl
e
s 00001/00011/00049
d D 7.6 90/06/28 21:37:36 bostic 11 10
c new copyright notice
e
s 00002/00006/00058
d D 7.5 90/04/05 11:50:19 sklower 10 9
c IFA_ROUTE now moved to protocol independent part of ifaddr
e
s 00016/00006/00048
d D 7.4 89/04/22 12:05:55 sklower 9 8
c checkpoint at first working tp4 connection; & before gnodes
e
s 00010/00005/00044
d D 7.3 88/06/29 17:06:45 bostic 8 7
c install approved copyright notice
e
s 00008/00002/00041
d D 7.2 87/12/07 17:45:31 bostic 7 6
c use Berkeley specific header
e
s 00001/00001/00042
d D 7.1 86/06/05 00:26:46 mckusick 6 5
c 4.3BSD release version
e
s 00006/00005/00037
d D 6.5 86/06/02 14:30:19 karels 5 4
c lint
e
s 00002/00002/00040
d D 6.4 86/02/23 23:23:48 karels 4 3
c lint
e
s 00001/00000/00041
d D 6.3 85/10/14 17:20:03 karels 3 2
c recognize other attempts to broadcast
e
s 00007/00001/00034
d D 6.2 85/06/08 12:39:16 mckusick 2 1
c Add copyright
e
s 00035/00000/00000
d D 6.1 85/03/18 15:31:17 karels 1 0
c separate internet addressing from interface layer
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
D 5
 * Copyright (c) 1982 Regents of the University of California.
E 5
I 5
D 6
 * Copyright (c) 1985 Regents of the University of California.
E 6
I 6
D 15
 * Copyright (c) 1985, 1986 Regents of the University of California.
E 6
E 5
D 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1985, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 11
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 8
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
D 5
 * Interface address, internet version.  One of these structures
 * is allocated for each interface with an internet address.
E 5
I 5
 * Interface address, Internet version.  One of these structures
 * is allocated for each interface with an Internet address.
E 5
 * The ifaddr structure contains the protocol-independent part
 * of the structure and is assumed to be first.
 */
struct in_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
D 9
#define	ia_addr	ia_ifa.ifa_addr
#define	ia_broadaddr	ia_ifa.ifa_broadaddr
#define	ia_dstaddr	ia_ifa.ifa_dstaddr
E 9
#define	ia_ifp		ia_ifa.ifa_ifp
I 10
#define ia_flags	ia_ifa.ifa_flags
E 10
I 9
					/* ia_{,sub}net{,mask} in host order */
E 9
	u_long	ia_net;			/* network number of interface */
	u_long	ia_netmask;		/* mask of net part */
	u_long	ia_subnet;		/* subnet number, including net */
D 9
	u_long	ia_subnetmask;		/* mask of net + subnet */
I 3
	struct	in_addr ia_netbroadcast; /* broadcast addr for (logical) net */
E 9
I 9
	u_long	ia_subnetmask;		/* mask of subnet part */
E 9
E 3
D 10
	int	ia_flags;
E 10
I 9
	struct	in_addr ia_netbroadcast; /* to recognize net broadcasts */
E 9
	struct	in_ifaddr *ia_next;	/* next in list of internet addresses */
I 9
	struct	sockaddr_in ia_addr;	/* reserve space for interface name */
	struct	sockaddr_in ia_dstaddr; /* reserve space for broadcast addr */
#define	ia_broadaddr	ia_dstaddr
	struct	sockaddr_in ia_sockmask; /* reserve space for general netmask */
I 12
	struct	in_multi *ia_multiaddrs; /* list of multicast addresses */
E 12
E 9
};
I 9

struct	in_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in ifra_addr;
	struct	sockaddr_in ifra_broadaddr;
#define ifra_dstaddr ifra_broadaddr
	struct	sockaddr_in ifra_mask;
};
E 9
/*
 * Given a pointer to an in_ifaddr (ifaddr),
D 10
 * return a pointer to the addr as a sockadd_in.
E 10
I 10
 * return a pointer to the addr as a sockaddr_in.
E 10
 */
D 9
#define	IA_SIN(ia) ((struct sockaddr_in *)(&((struct in_ifaddr *)ia)->ia_addr))
E 9
I 9
#define	IA_SIN(ia) (&(((struct in_ifaddr *)(ia))->ia_addr))
E 9
D 10
/*
 * ia_flags
 */
#define	IFA_ROUTE	0x01		/* routing entry installed */
E 10

I 13
#define IN_LNAOF(in, ifa) \
	((ntohl((in).s_addr) & ~((struct in_ifaddr *)(ifa)->ia_subnetmask))
			

E 13
#ifdef	KERNEL
D 4
extern	struct in_ifaddr *in_ifaddr;
extern	struct in_ifaddr *in_iaonnetof();
E 4
I 4
D 5
struct in_ifaddr *in_ifaddr;
struct in_ifaddr *in_iaonnetof();
E 5
I 5
D 13
struct	in_ifaddr *in_ifaddr;
struct	in_ifaddr *in_iaonnetof();
struct	ifqueue	ipintrq;		/* ip packet input queue */
I 12
#endif
E 13
I 13
extern	struct	in_ifaddr *in_ifaddr;
extern	struct	ifqueue	ipintrq;		/* ip packet input queue */
void	in_socktrim __P((struct sockaddr_in *));
E 13

D 13
#ifdef KERNEL
E 13
I 13

E 13
/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IP addresses.
 */
#define INADDR_TO_IFP(addr, ifp) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
{ \
	register struct in_ifaddr *ia; \
\
	for (ia = in_ifaddr; \
	    ia != NULL && IA_SIN(ia)->sin_addr.s_addr != (addr).s_addr; \
	    ia = ia->ia_next) \
		 continue; \
	(ifp) = (ia == NULL) ? NULL : ia->ia_ifp; \
}

/*
 * Macro for finding the internet address structure (in_ifaddr) corresponding
 * to a given interface (ifnet structure).
 */
#define IFP_TO_IA(ifp, ia) \
	/* struct ifnet *ifp; */ \
	/* struct in_ifaddr *ia; */ \
{ \
	for ((ia) = in_ifaddr; \
	    (ia) != NULL && (ia)->ia_ifp != (ifp); \
	    (ia) = (ia)->ia_next) \
		continue; \
}
#endif

/*
 * Internet multicast address structure.  There is one of these for each IP
 * multicast group to which this host belongs on a given network interface.
 * They are kept in a linked list, rooted in the interface's in_ifaddr
 * structure.
 */
struct in_multi {
	struct	in_addr inm_addr;	/* IP multicast address */
	struct	ifnet *inm_ifp;		/* back pointer to ifnet */
	struct	in_ifaddr *inm_ia;	/* back pointer to in_ifaddr */
	u_int	inm_refcount;		/* no. membership claims by sockets */
	u_int	inm_timer;		/* IGMP membership report timer */
	struct	in_multi *inm_next;	/* ptr to next multicast address */
};

#ifdef KERNEL
/*
 * Structure used by macros below to remember position when stepping through
 * all of the in_multi records.
 */
struct in_multistep {
	struct in_ifaddr *i_ia;
	struct in_multi *i_inm;
};

/*
 * Macro for looking up the in_multi record for a given IP multicast address
 * on a given interface.  If no matching record is found, "inm" returns NULL.
 */
#define IN_LOOKUP_MULTI(addr, ifp, inm) \
	/* struct in_addr addr; */ \
	/* struct ifnet *ifp; */ \
	/* struct in_multi *inm; */ \
{ \
	register struct in_ifaddr *ia; \
\
	IFP_TO_IA((ifp), ia); \
	if (ia == NULL) \
		(inm) = NULL; \
	else \
		for ((inm) = ia->ia_multiaddrs; \
		    (inm) != NULL && (inm)->inm_addr.s_addr != (addr).s_addr; \
		     (inm) = inm->inm_next) \
			 continue; \
}

/*
 * Macro to step through all of the in_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IN_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "inm" when there
 * are no remaining records.
 */
#define IN_NEXT_MULTI(step, inm) \
	/* struct in_multistep  step; */ \
	/* struct in_multi *inm; */ \
{ \
	if (((inm) = (step).i_inm) != NULL) \
		(step).i_inm = (inm)->inm_next; \
	else \
		while ((step).i_ia != NULL) { \
			(inm) = (step).i_ia->ia_multiaddrs; \
			(step).i_ia = (step).i_ia->ia_next; \
			if ((inm) != NULL) { \
				(step).i_inm = (inm)->inm_next; \
				break; \
			} \
		} \
}

#define IN_FIRST_MULTI(step, inm) \
	/* struct in_multistep step; */ \
	/* struct in_multi *inm; */ \
{ \
	(step).i_ia = in_ifaddr; \
	(step).i_inm = NULL; \
	IN_NEXT_MULTI((step), (inm)); \
}

I 14
int	in_ifinit __P((struct ifnet *,
	    struct in_ifaddr *, struct sockaddr_in *, int));
E 14
struct	in_multi *in_addmulti __P((struct in_addr *, struct ifnet *));
int	in_delmulti __P((struct in_multi *));
I 14
void	in_ifscrub __P((struct ifnet *, struct in_ifaddr *));
D 16
int	in_control __P((struct socket *, int, caddr_t, struct ifnet *));
E 16
I 16
int	in_control __P((struct socket *, u_long, caddr_t, struct ifnet *));
E 16
E 14
E 12
E 5
E 4
#endif
E 1
