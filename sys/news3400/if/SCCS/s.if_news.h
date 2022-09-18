h34475
s 00002/00002/00038
d D 8.1 93/06/11 14:57:13 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00000/00000
d D 7.1 92/06/04 15:59:13 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: if_news.h,v 4.300 91/06/09 06:26:02 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Structure and routine definitions
 * for NEWS network interfaces.
 */

/*
 * Each interface has one of these structures giving information
 * about NEWS resources held by the interface.
 */
struct ifnews {
	int	ifn_hlen;			/* local net header length */
	caddr_t	ifn_raddr;			/* receive buffer address */
	caddr_t	ifn_waddr;			/* transmit buffer address */
	struct	mbuf *ifn_mbuf;			/* packet being transmitted */
};

struct mbuf_segment {
	u_int	ms_physaddr;
	u_int	ms_size;
};

#ifdef KERNEL
struct mbuf *if_rnewsget();
#endif

#define	LARGE_DATA 	512
E 1
