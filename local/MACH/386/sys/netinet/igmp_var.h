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
 * $Log:	igmp_var.h,v $
 * Revision 2.3  89/03/09  20:44:06  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:59:05  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 *	igmp_var.h
 */

#include "igmproto.h"

#if	IGMPROTO

#include "igmp.h"

/*
 * IGMP protocol interface control block.  Used
 * to tie a socket to the generic igmp interface.
 */
struct igmpcb {
	struct	igmpcb *next;	    /* doubly linked list */
	struct	igmpcb *prev;	    /* of existing igmpcbs */
	short   countdown;	    /* slowtimeo countdown */
	u_char  num_rtx;	    /* number of retransmissions */
	u_char	matched;	    /* boolean for matcing req/replies */
	u_char  type;		    /* IGMP request/reply type */
	u_char  code;		    /* IGMP request/reply code */
	u_char  rc;		    /* internal return code from request */
	u_char  loopback;	    /* loopback flag */
	u_long	identifier;	    /* 32 bit unique identifier for IGMP request */
	u_long	key1;		    /* First 32 bits of group access key */
	u_long	key2;		    /* Second 32 bits of group access key */
	struct  in_addr groupaddr;  /* Group IP address of relevant group */
	struct	socket *socket;	    /* back pointer to igmp socket */
	struct	mbuf *options;	    /* protocol specific options */
	struct  mbuf *message;	    /* pointer to mbuf containing copy of request */
	struct  GroupDescriptor *ad;/* back pointer to group descriptor */
	struct	igmpcb *ADnext;	    /* doubly linked list of igmpcbs associated */
	struct	igmpcb *ADprev;	    /* with group corresponding to ad above */
	struct  ifnet *ifp;	    /* pointer to interface we joined on */
};

#define sotoigmpcb(so)		((struct igmpcb *)(so)->so_pcb)

/*
 * Nominal space allocated to a igmp socket.
 */
#define IGMPSNDQ		2048
#define IGMPRCVQ		4096

struct	igmpstat {
 	int	igmps_badcode;		/* igmp_code out of range */
	int	igmps_tooshort;		/* packet < IGMP_MINLEN */
	int	igmps_checksum;		/* bad checksum */
};


#ifdef	KERNEL
struct igmpcb igmpcbhead;			/* head of list */
struct igmpstat igmpstat;
#endif	KERNEL

struct igmpiphdr {
    struct ipovly i;
    struct igmp g;
};

extern u_long unique;


#endif	IGMPROTO
