/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	in_var.h,v $
 * Revision 2.5  90/08/30  11:48:32  bohman
 * 	Added missing semicolon.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.4  90/07/03  16:42:45  mrt
 * 	Added rel5 multicast code from Stanford.
 * 	[90/06/28            jjk]
 * 
 * 	Merged mt Xinu 2.6 MSD changes.
 * 	[90/05/17            emg]
 * 
 */
/*
 * Copyright (c) 1985, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
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
 *
 *	@(#)in_var.h	7.3 (Berkeley) 6/29/88
 */

/*
 * Interface address, Internet version.  One of these structures
 * is allocated for each interface with an Internet address.
 * The ifaddr structure contains the protocol-independent part
 * of the structure and is assumed to be first.
 */
struct in_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
#define	ia_addr	ia_ifa.ifa_addr
#define	ia_broadaddr	ia_ifa.ifa_broadaddr
#define	ia_dstaddr	ia_ifa.ifa_dstaddr
#define	ia_ifp		ia_ifa.ifa_ifp
	u_long	ia_net;			/* network number of interface */
	u_long	ia_netmask;		/* mask of net part */
	u_long	ia_subnet;		/* subnet number, including net */
	u_long	ia_subnetmask;		/* mask of net + subnet */
	struct	in_addr ia_netbroadcast; /* broadcast addr for (logical) net */
	int	ia_flags;
	struct	in_ifaddr *ia_next;	/* next in list of internet addresses */
	struct	in_multi *ia_multiaddrs; /* list of multicast addresses */
};
/*
 * Given a pointer to an in_ifaddr (ifaddr),
 * return a pointer to the addr as a sockadd_in.
 */
#define	IA_SIN(ia) ((struct sockaddr_in *)(&((struct in_ifaddr *)ia)->ia_addr))
/*
 * ia_flags
 */
#define	IFA_ROUTE	0x01		/* routing entry installed */

#ifdef	KERNEL
struct	in_ifaddr *in_ifaddr;
struct	in_ifaddr *in_iaonnetof();
struct	ifqueue	ipintrq;		/* ip packet input queue */
#endif

#ifdef KERNEL
/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IP addresses.
 */
#define INADDR_TO_IFP(addr, ifp)					  \
	/* struct in_addr addr; */					  \
	/* struct ifnet  *ifp;  */					  \
{									  \
	register struct in_ifaddr *ia;					  \
									  \
	for (ia = in_ifaddr;						  \
	     ia != NULL && IA_SIN(ia)->sin_addr.s_addr != (addr).s_addr;  \
	     ia = ia->ia_next);						  \
	(ifp) = (ia == NULL) ? NULL : ia->ia_ifp;			  \
}

/*
 * Macro for finding the internet address structure (in_ifaddr) corresponding
 * to a given interface (ifnet structure).
 */
#define IFP_TO_IA(ifp, ia)						  \
	/* struct ifnet     *ifp; */					  \
	/* struct in_ifaddr *ia;  */					  \
{									  \
	for ((ia) = in_ifaddr;						  \
	     (ia) != NULL && (ia)->ia_ifp != (ifp);			  \
	     (ia) = (ia)->ia_next);					  \
}
#endif KERNEL

/*
 * Internet multicast address structure.  There is one of these for each IP
 * multicast group to which this host belongs on a given network interface.
 * They are kept in a linked list, rooted in the interface's in_ifaddr
 * structure.
 */
struct in_multi {
	struct in_addr	  inm_addr;	/* IP multicast address             */
	struct ifnet     *inm_ifp;	/* back pointer to ifnet            */
	struct in_ifaddr *inm_ia;	/* back pointer to in_ifaddr        */
	u_int		  inm_refcount;	/* no. membership claims by sockets */
	u_int		  inm_timer;	/* IGMP membership report timer     */
	struct in_multi  *inm_next;	/* ptr to next multicast address    */
};

#ifdef KERNEL
/*
 * Structure used by macros below to remember position when stepping through
 * all of the in_multi records.
 */
struct in_multistep {
	struct in_ifaddr *i_ia;
	struct in_multi  *i_inm;
};

/*
 * Macro for looking up the in_multi record for a given IP multicast address
 * on a given interface.  If no matching record is found, "inm" returns NULL.
 */
#define IN_LOOKUP_MULTI(addr, ifp, inm)					    \
	/* struct in_addr  addr; */					    \
	/* struct ifnet    *ifp; */					    \
	/* struct in_multi *inm; */					    \
{									    \
	register struct in_ifaddr *ia;					    \
									    \
	IFP_TO_IA((ifp), ia);						    \
	if (ia == NULL)							    \
		(inm) = NULL;						    \
	else								    \
	    for ((inm) = ia->ia_multiaddrs;				    \
		 (inm) != NULL && (inm)->inm_addr.s_addr != (addr).s_addr;  \
		 (inm) = inm->inm_next);				    \
}

/*
 * Macro to step through all of the in_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IN_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "inm" when there
 * are no remaining records.
 */
#define IN_NEXT_MULTI(step, inm)					\
	/* struct in_multistep  step; */				\
	/* struct in_multi     *inm;  */				\
{									\
	if (((inm) = (step).i_inm) != NULL) {				\
		(step).i_inm = (inm)->inm_next;				\
	}								\
	else while ((step).i_ia != NULL) {				\
		(inm) = (step).i_ia->ia_multiaddrs;			\
		(step).i_ia = (step).i_ia->ia_next;			\
		if ((inm) != NULL) {					\
			(step).i_inm = (inm)->inm_next;			\
			break;						\
		}							\
	}								\
}

#define IN_FIRST_MULTI(step, inm)					\
	/* struct in_multistep  step; */				\
	/* struct in_multi     *inm;  */				\
{									\
	(step).i_ia  = in_ifaddr;					\
	(step).i_inm = NULL;						\
	IN_NEXT_MULTI((step), (inm));					\
}

struct in_multi *in_addmulti();
#endif KERNEL
