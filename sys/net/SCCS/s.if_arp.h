h33315
s 00002/00002/00057
d D 8.1 93/06/10 22:44:35 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00001/00053
d D 7.6 92/10/14 16:52:06 sklower 7 6
c update possible arp operations
e
s 00006/00004/00048
d D 7.5 92/07/23 16:12:32 bostic 6 5
c keep gcc happy, no real change
e
s 00001/00011/00051
d D 7.4 90/06/28 21:30:27 bostic 5 4
c new copyright notice
e
s 00010/00005/00052
d D 7.3 88/06/27 18:59:32 bostic 4 3
c install approved copyright notice
e
s 00008/00002/00049
d D 7.2 87/12/30 11:57:27 bostic 3 2
c add Berkeley header
e
s 00000/00000/00051
d D 7.1 86/06/04 23:39:59 mckusick 2 1
c 4.3BSD release version
e
s 00051/00000/00000
d D 6.1 86/01/24 18:30:18 karels 1 0
c move arp stuff to if_arp.h
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1986 Regents of the University of California.
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  ARP packets are variable
 * in size; the arphdr structure defines the fixed-length portion.
 * Protocol type values are the same as those for 10 Mb/s Ethernet.
 * It is followed by the variable-sized fields ar_sha, arp_spa,
 * arp_tha and arp_tpa in that order, according to the lengths
 * specified.  Field names used correspond to RFC 826.
 */
struct	arphdr {
	u_short	ar_hrd;		/* format of hardware address */
D 7
#define ARPHRD_ETHER 	1	/* ethernet hardware address */
E 7
I 7
#define ARPHRD_ETHER 	1	/* ethernet hardware format */
#define ARPHRD_FRELAY 	15	/* frame relay hardware format */
E 7
	u_short	ar_pro;		/* format of protocol address */
	u_char	ar_hln;		/* length of hardware address */
	u_char	ar_pln;		/* length of protocol address */
	u_short	ar_op;		/* one of: */
#define	ARPOP_REQUEST	1	/* request to resolve address */
#define	ARPOP_REPLY	2	/* response to previous request */
I 7
#define	ARPOP_REVREQUEST 3	/* request protocol address given hardware */
#define	ARPOP_REVREPLY	4	/* response giving protocol address */
#define ARPOP_INVREQUEST 8 	/* request to identify peer */
#define ARPOP_INVREPLY	9	/* response identifying peer */
E 7
/*
 * The remaining fields are variable in size,
 * according to the sizes above.
 */
D 6
/*	u_char	ar_sha[];	/* sender hardware address */
/*	u_char	ar_spa[];	/* sender protocol address */
/*	u_char	ar_tha[];	/* target hardware address */
/*	u_char	ar_tpa[];	/* target protocol address */
E 6
I 6
#ifdef COMMENT_ONLY
	u_char	ar_sha[];	/* sender hardware address */
	u_char	ar_spa[];	/* sender protocol address */
	u_char	ar_tha[];	/* target hardware address */
	u_char	ar_tpa[];	/* target protocol address */
#endif
E 6
};

/*
 * ARP ioctl request
 */
struct arpreq {
	struct	sockaddr arp_pa;		/* protocol address */
	struct	sockaddr arp_ha;		/* hardware address */
	int	arp_flags;			/* flags */
};
/*  arp_flags and at_flags field values */
#define	ATF_INUSE	0x01	/* entry in use */
#define ATF_COM		0x02	/* completed entry (enaddr valid) */
#define	ATF_PERM	0x04	/* permanent entry */
#define	ATF_PUBL	0x08	/* publish entry (respond for other host) */
#define	ATF_USETRAILERS	0x10	/* has requested trailers */
E 1
