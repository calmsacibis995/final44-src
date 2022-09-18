h32035
s 00002/00002/00062
d D 8.1 93/06/05 10:47:35 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00063
d D 5.5 90/06/01 16:14:30 bostic 6 5
c new copyright notice
e
s 00015/00004/00059
d D 5.4 88/09/19 21:00:45 bostic 5 4
c add Berkeley specific copyright notice
e
s 00014/00003/00049
d D 5.3 85/08/16 22:35:08 sklower 4 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00017/00003/00049
d R 5.3 85/08/16 21:49:04 sklower 3 2
c This version Aug 16th -- source directory moved to /usr/src/etc/XNSrouted;
c includes fix to response to request for specific net, and adds copyright notices
e
s 00000/00001/00052
d D 5.2 85/08/16 20:43:46 sklower 2 1
c status as of 4.3 alpha tape
e
s 00053/00000/00000
d D 5.1 85/08/16 20:22:39 sklower 1 0
c date and time created 85/08/16 20:22:39 by sklower
e
u
U
t
T
I 1
D 4
/*	interface.h	4.2	84/04/09	*/
E 4
I 4
/*
D 5
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 7
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
E 5
 *
D 5
 *	%W% (Berkeley) %G%";
E 5
I 5
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
E 5
 */
E 4

/*
 * Routing table management daemon.
 */

/*
 * An ``interface'' is similar to an ifnet structure,
 * except it doesn't contain q'ing info, and it also
 * handles ``logical'' interfaces (remote gateways
 * that we want to keep polling even if they go down).
 * The list of interfaces which we maintain is used
 * in supplying the gratuitous routing table updates.
 * We list only one address for  each interface, the AF_XNS one.
 */
#define NIFADDR 3
struct interface {
	struct	interface *int_next;
	struct	sockaddr int_addr;		/* address on this host */
	union {
		struct	sockaddr intu_broadaddr;
		struct	sockaddr intu_dstaddr;
	} int_intu;
#define	int_broadaddr	int_intu.intu_broadaddr	/* broadcast address */
#define	int_dstaddr	int_intu.intu_dstaddr	/* other end of p-to-p link */
	int	int_metric;			/* init's routing entry */
	int	int_flags;			/* see below */
	struct	ifdebug int_input, int_output;	/* packet tracing stuff */
	int	int_ipackets;			/* input packets received */
	int	int_opackets;			/* output packets sent */
	char	*int_name;			/* from kernel if structure */
	u_short	int_transitions;		/* times gone up-down */
I 4
/*XNS Specific entry */
	struct	sameq {
		struct sameq *n;		/* q of other pt-to-pt links */
		struct sameq *p;		/* with same net # */
	}	int_sq;
E 4
D 2
	int	int_ripsock[2];			/* socket to listen for RIP packets on */
E 2
};

/*
D 4
 * 0x1 to 0x100 are reused from the kernel's ifnet definitions,
E 4
I 4
 * 0x1 to 0x10 are reused from the kernel's ifnet definitions,
E 4
 * the others agree with the RTS_ flags defined elsewhere.
 */
#define	IFF_UP		0x1		/* interface is up */
#define	IFF_BROADCAST	0x2		/* broadcast address valid */
#define	IFF_DEBUG	0x4		/* turn on debugging */
#define	IFF_ROUTE	0x8		/* routing entry installed */
#define	IFF_POINTOPOINT	0x10		/* interface is point-to-point link */
D 4
#define	IFF_LOCAL	0x100		/* local network, host part encoded */
E 4

#define	IFF_PASSIVE	0x2000		/* can't tell if up/down */
#define	IFF_INTERFACE	0x4000		/* hardware interface */
#define	IFF_REMOTE	0x8000		/* interface isn't on this machine */

struct	interface *if_ifwithaddr();
I 4
struct	interface *if_ifwithdstaddr();
E 4
struct	interface *if_ifwithnet();
struct	interface *if_iflookup();
E 1
