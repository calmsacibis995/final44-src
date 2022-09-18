h18203
s 00002/00002/00084
d D 8.1 93/06/10 23:19:58 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00085
d D 7.9 93/06/04 17:02:40 sklower 9 8
c fix #endif something to #endif /* something */
e
s 00009/00001/00077
d D 7.8 91/05/06 19:24:11 bostic 8 7
c new copyright; att/bsd/shared
e
s 00002/00001/00076
d D 7.7 90/06/22 15:39:45 sklower 7 6
c merge in UW isis changes; my merge is untested, but SCCS id's
c must be assigned before I leave today :-(
e
s 00002/00022/00075
d D 7.6 90/06/20 19:03:04 sklower 6 5
c changed esis to make use of routing table; mostly works;
c checkpoint before UW merge
e
s 00020/00000/00077
d D 7.5 90/06/09 17:39:20 sklower 5 4
c change snpa cache to fold in to routing table; this doesn't work yet;
c but checkpoint anyhow
e
s 00005/00000/00072
d D 7.4 90/04/05 11:25:00 sklower 4 3
c move snpacache ioctls to this file (will eventually disappear)
e
s 00001/00000/00071
d D 7.3 89/08/29 13:44:40 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00006/00002/00065
d D 7.2 89/04/22 11:54:30 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00067/00000/00000
d D 7.1 88/12/14 15:29:50 sklower 1 0
c date and time created 88/12/14 15:29:50 by sklower
e
u
U
t
T
I 8
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 8
I 1
/***********************************************************
		Copyright IBM Corporation 1987

                      All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of IBM not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * ARGO Project, Computer Sciences Dept., University of Wisconsin - Madison
 */
I 3
D 8
/*	%W% (Berkeley) %G% */
E 8
I 6

E 6
E 3
#define	MAX_SNPALEN		8			/* curiously equal to sizeof x.121 (
										plus 1 for nibble len) addr */
struct snpa_req {
	struct iso_addr	sr_isoa;		/* nsap address */
	u_char			sr_len;			/* length of snpa */
	u_char			sr_snpa[MAX_SNPALEN];	/* snpa associated 
												with nsap address */
	u_char			sr_flags;		/* true if entry is valid */
D 2
	short			sr_ht;			/* holding time */
E 2
I 2
	u_short			sr_ht;			/* holding time */
E 2
};

D 6
/*
 *	Structure of the SNPA cache
 */
struct snpa_cache {
	struct snpa_req	sc_sr;
#define	sc_nsap		sc_sr.sr_isoa		/* this could be a NET if entry is
											for an IS */
#define sc_len		sc_sr.sr_len
#define sc_snpa		sc_sr.sr_snpa
#define sc_ht		sc_sr.sr_ht
#define sc_flags	sc_sr.sr_flags
	struct ifnet	*sc_ifp;
E 6
#define	SNPA_VALID		0x01
#define	SNPA_ES			0x02
#define SNPA_IS			0x04
#define	SNPA_PERM		0x10

D 6
	/* redirects only */
D 2
	struct iso_addr	sc_da;		/* DA from RD */
E 2
I 2
	struct iso_addr sc_da;		/* DA from RD */
	struct rtentry *sc_rt;
E 2
};

E 6
struct systype_req {
	short	sr_holdt;		/* holding timer */
	short	sr_configt;		/* configuration timer */
I 7
	short	sr_esconfigt;	/* suggested ES configuration timer */
E 7
	char	sr_type;		/* SNPA_ES or SNPA_IS */
};
I 2

I 5
struct esis_req {
	short	er_ht;			/* holding time */
	u_char	er_flags;		/* type and validity */
};
/*
 * Space for this structure gets added onto the end of a route
 * going to an ethernet or other 802.[45x] device.
 */

struct llinfo_llc {
	struct	llinfo_llc *lc_next;	/* keep all llc routes linked */
	struct	llinfo_llc *lc_prev;	/* keep all llc routes linked */
	struct	rtentry *lc_rt;			/* backpointer to route */
D 6
	struct	rtentry *lc_rtgate;		/* route to (RTF_GATEWAY ? ll : iface) */ 
E 6
	struct	esis_req lc_er;			/* holding time, etc */
#define lc_ht		lc_er.er_ht
#define lc_flags	lc_er.er_flags
};

I 6

E 6
E 5
I 4
/* ISO arp IOCTL data structures */

D 6
#define	SIOCSISOMAP	_IOW('a',30, struct snpa_req)	/* set arp entry */
#define	SIOCGISOMAP	_IOWR('a',38, struct snpa_req)/* get arp entry */
#define	SIOCDISOMAP	_IOW('a',31, struct snpa_req)	/* delete arp entry */
E 6
E 4
#define	SIOCSSTYPE 	_IOW('a', 39, struct systype_req) /* set system type */
D 7
#define	SIOCGSTYPE 	_IOW('a', 40, struct systype_req) /* set system type */
E 7
I 7
#define	SIOCGSTYPE 	_IOR('a', 40, struct systype_req) /* get system type */
E 7
E 2

#ifdef	KERNEL
D 6
struct snpa_cache *snpac_look(/* struct iso_addr *isoa */);
E 6
I 5
struct llinfo_llc llinfo_llc;	/* head for linked lists */
E 5
D 9
#endif	KERNEL
E 9
I 9
#endif	/* KERNEL */
E 9
E 1
