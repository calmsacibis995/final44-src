h19309
s 00002/00002/00142
d D 8.1 93/06/10 23:19:06 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00001/00135
d D 7.5 91/05/06 19:23:53 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00000/00135
d D 7.4 90/05/24 17:39:27 sklower 4 3
c try to keep up with Dave Katz and his prefix table . . .
e
s 00015/00000/00120
d D 7.3 90/04/05 11:20:19 sklower 3 2
c rewrite if_eon.c to allow arbitrary nsaps routed via IP; use new rt_change mechnism to maintain list of routes\;
e
s 00024/00011/00096
d D 7.2 89/04/22 11:53:43 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00107/00000/00000
d D 7.1 88/12/14 15:29:32 sklower 1 0
c date and time created 88/12/14 15:29:32 by sklower
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 5
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
I 2
D 5
 *	%W% (Berkeley) %G%
E 5
E 2
 */

#define EON_986_VERSION 0x3
#define EON_VERSION 0x1

#define EON_CACHESIZE 30

#define E_FREE 	1
#define E_LINK	2
#define E_ES 	3
#define E_IS 	4
 

/* 
 * this overlays a sockaddr_iso
 */

struct sockaddr_eon {
D 2
	short 			seon_family;	/* AF_ISO */
	u_short			seon_status;	/* overlays transport suffix */
E 2
I 2
	u_char 			seon_len;	/* Length */
	u_char 			seon_family;	/* AF_ISO */
	u_char			seon_status;	/* overlays session suffixlen */
E 2
#define EON_ESLINK_UP		0x1
#define EON_ESLINK_DOWN		0x2
#define EON_ISLINK_UP		0x10
#define EON_ISLINK_DOWN		0x20
/* no change is neither up or down */
D 2

E 2
I 2
	u_char			seon_pad1;	/* 0, overlays tsfxlen */
	u_char			seon_adrlen;
E 2
	u_char			seon_afi;		/* 47 */
	u_char			seon_idi[2];	/* 0006 */
	u_char			seon_vers;		/* 03 */
I 2
	u_char			seon_glbnum[2];	/* see RFC 1069 */
	u_char			seon_RDN[2];	/* see RFC 1070 */
	u_char			seon_pad2[3];	/* see RFC 1070 */
	u_char			seon_LAREA[2];	/* see RFC 1070 */
	u_char			seon_pad3[2];	/* see RFC 1070 */
E 2
		/* right now ip addr is  aligned  -- be careful --
		 * future revisions may have it u_char[4]
		 */
	u_int			seon_ipaddr;	/* a.b.c.d */
D 2
	u_char			seon_protoid[1]; /* */
	u_char			seon_adrlen;
	u_short			seon_netype[2];
E 2
I 2
	u_char			seon_protoid;	/* NSEL */
E 2
};

I 2
#ifdef EON_TEMPLATE
E 2
struct sockaddr_eon eon_template = {
D 2
	AF_ISO, 0, 0x47, 0x0, 0x6, 0x3,
	0,
	0,
	0xa,
	0
E 2
I 2
	sizeof (eon_template), AF_ISO, 0, 0, 0x14,
	0x47, 0x0, 0x6, 0x3, 0
E 2
};
I 2
#endif
E 2

#define DOWNBITS ( EON_ESLINK_DOWN | EON_ISLINK_DOWN )
#define UPBITS ( EON_ESLINK_UP | EON_ISLINK_UP )

I 2
#define	SIOCSEONCORE _IOWR('i',10, struct iso_ifreq) /* EON core member */
#define	SIOCGEONCORE _IOWR('i',11, struct iso_ifreq) /* EON core member */

E 2
struct eon_hdr {
	u_char 	eonh_vers; /* value 1 */
	u_char 	eonh_class;  /* address multicast class, below */
#define		EON_NORMAL_ADDR		0x0
#define		EON_MULTICAST_ES	0x1
#define		EON_MULTICAST_IS	0x2
#define		EON_BROADCAST		0x3
	u_short eonh_csum;  /* osi checksum (choke)*/
};
I 3
struct eon_iphdr {
	struct	ip	ei_ip;
	struct	eon_hdr	ei_eh;
};
E 3
I 2
#define EONIPLEN (sizeof(struct eon_hdr) + sizeof(struct ip))
E 2

/* stole these 2 fields of the flags for I-am-ES and I-am-IS */
#define	IFF_ES	0x400
#define	IFF_IS	0x800

struct eon_stat {
	int	es_in_multi_es;
	int	es_in_multi_is;
	int	es_in_broad;
	int	es_in_normal;
	int	es_out_multi_es;
	int	es_out_multi_is;
	int	es_out_broad;
	int	es_out_normal;
	int	es_ipout;

	int	es_icmp[PRC_NCMDS];
	/* errors */
	int	es_badcsum;
	int	es_badhdr;
} eonstat;

#undef IncStat
#define IncStat(xxx) eonstat.xxx++
I 2

typedef struct qhdr {
	struct qhdr *link, *rlink;
} *queue_t;
I 3

struct eon_llinfo {
	struct	qhdr el_qhdr;		/* keep all in a list */
	int	el_flags;		/* cache valid ? */
I 4
	int	el_snpaoffset;		/* IP address contained in dst nsap */
E 4
	struct	rtentry *el_rt;		/* back pointer to parent route */
	struct	eon_iphdr el_ei;	/* precomputed portion of hdr */
	struct	route el_iproute;	/* if direct route cache IP info */
					/* if gateway, cache secondary route */
};
#define el_iphdr el_ei.ei_ip
#define el_eonhdr el_ei.ei_eh
E 3
E 2
E 1
