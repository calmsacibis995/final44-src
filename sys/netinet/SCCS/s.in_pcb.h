h06039
s 00002/00002/00060
d D 8.1 93/06/10 23:04:31 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00002/00048
d D 7.9 93/06/04 17:23:05 bostic 17 16
c prototype everything
e
s 00002/00001/00048
d D 7.8 93/04/07 19:28:07 sklower 16 15
c Mostly changes recommended by jch for variable subnets & multiple
c IP addresses per physical interface. May require further work.
e
s 00002/00018/00047
d D 7.7 92/07/06 15:08:22 sklower 15 14
c multicast changes from lbl
e
s 00001/00011/00064
d D 7.6 90/06/28 21:37:14 bostic 14 13
c new copyright notice
e
s 00009/00001/00066
d D 7.5 90/06/28 14:10:44 karels 13 12
c add internet-common options in pcb, add ip header prototype for ttl and tos;
c should have room for options and next header (next time, but elsewhere)
e
s 00018/00000/00049
d D 7.4 89/04/22 12:05:49 sklower 12 11
c checkpoint at first working tp4 connection; & before gnodes
e
s 00010/00005/00039
d D 7.3 88/06/29 17:06:41 bostic 11 10
c install approved copyright notice
e
s 00008/00002/00036
d D 7.2 87/12/07 17:45:23 bostic 10 9
c use Berkeley specific header
e
s 00001/00001/00037
d D 7.1 86/06/05 00:26:18 mckusick 9 8
c 4.3BSD release version
e
s 00001/00000/00037
d D 6.3 85/09/16 22:51:58 karels 8 7
c add ip iptions to inpcb
e
s 00007/00001/00030
d D 6.2 85/06/08 12:38:33 mckusick 7 6
c Add copyright
e
s 00000/00000/00031
d D 6.1 83/07/29 07:11:20 sam 6 5
c 4.2 distribution
e
s 00000/00000/00031
d D 4.5 82/10/20 01:22:22 root 5 4
c lint
e
s 00001/00000/00030
d D 4.4 82/03/29 11:32:27 sam 4 3
c first cut (incomplete) at routing
e
s 00003/00000/00027
d D 4.3 82/03/03 11:06:45 root 3 2
c wildcard addresses
e
s 00002/00000/00025
d D 4.2 81/12/03 17:29:38 wnj 2 1
c cleanup
e
s 00025/00000/00000
d D 4.1 81/11/20 00:52:27 wnj 1 0
c date and time created 81/11/20 00:52:27 by wnj
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 13
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
I 13
D 18
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
E 13
E 9
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 14
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 14
I 14
 * %sccs.include.redist.c%
E 14
E 11
E 10
 *
 *	%W% (Berkeley) %G%
 */
E 7

/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
	struct	inpcb *inp_next,*inp_prev;
					/* pointers to other pcb's */
I 2
	struct	inpcb *inp_head;	/* pointer back to chain of inpcb's
					   for this protocol */
E 2
	struct	in_addr inp_faddr;	/* foreign host table entry */
	u_short	inp_fport;		/* foreign port */
	struct	in_addr inp_laddr;	/* local host table entry */
	u_short	inp_lport;		/* local port */
	struct	socket *inp_socket;	/* back pointer to socket */
	caddr_t	inp_ppcb;		/* pointer to per-protocol pcb */
I 4
	struct	route inp_route;	/* placeholder for routing entry */
I 13
	int	inp_flags;		/* generic IP/datagram flags */
	struct	ip inp_ip;		/* header prototype; should have more */
E 13
I 8
	struct	mbuf *inp_options;	/* IP options */
I 15
	struct	ip_moptions *inp_moptions; /* IP multicast options */
E 15
E 8
E 4
};
I 13

/* flags in inp_flags: */
#define	INP_RECVOPTS		0x01	/* receive incoming IP options */
#define	INP_RECVRETOPTS		0x02	/* receive IP options for reply */
#define	INP_RECVDSTADDR		0x04	/* receive IP dst address */
#define	INP_CONTROLOPTS		(INP_RECVOPTS|INP_RECVRETOPTS|INP_RECVDSTADDR)
I 15
#define	INP_HDRINCL		0x08	/* user supplies entire IP header */
E 15
E 13

I 12
D 15
#ifdef sotorawcb
/*
 * Common structure pcb for raw internet protocol access.
 * Here are internet specific extensions to the raw control block,
 * and space is allocated to the necessary sockaddrs.
 */
struct raw_inpcb {
	struct	rawcb rinp_rcb;	/* common control block prefix */
	struct	mbuf *rinp_options;	/* IP options */
	int	rinp_flags;		/* flags, e.g. raw sockopts */
#define	RINPF_HDRINCL	0x1		/* user supplies entire IP header */
	struct	sockaddr_in rinp_faddr;	/* foreign address */
	struct	sockaddr_in rinp_laddr;	/* local address */
	struct	route rinp_route;	/* placeholder for routing entry */
};
#endif

E 15
E 12
I 3
#define	INPLOOKUP_WILDCARD	1
#define	INPLOOKUP_SETLOCAL	2

E 3
#define	sotoinpcb(so)	((struct inpcb *)(so)->so_pcb)
I 12
D 15
#define	sotorawinpcb(so)	((struct raw_inpcb *)(so)->so_pcb)
E 15
E 12

#ifdef KERNEL
D 16
struct	inpcb *in_pcblookup();
E 16
I 16
D 17
struct	inpcb *in_pcblookup __P((struct inpcb *, struct in_addr, int,
				 struct in_addr,  int, int));
E 17
I 17
int	 in_losing __P((struct inpcb *));
int	 in_pcballoc __P((struct socket *, struct inpcb *));
int	 in_pcbbind __P((struct inpcb *, struct mbuf *));
int	 in_pcbconnect __P((struct inpcb *, struct mbuf *));
int	 in_pcbdetach __P((struct inpcb *));
int	 in_pcbdisconnect __P((struct inpcb *));
struct inpcb *
	 in_pcblookup __P((struct inpcb *,
	    struct in_addr, u_int, struct in_addr, u_int, int));
int	 in_pcbnotify __P((struct inpcb *, struct sockaddr *,
	    u_int, struct in_addr, u_int, int, void (*)(struct inpcb *, int)));
void	 in_rtchange __P((struct inpcb *, int));
int	 in_setpeeraddr __P((struct inpcb *, struct mbuf *));
int	 in_setsockaddr __P((struct inpcb *, struct mbuf *));
E 17
E 16
#endif
E 1
