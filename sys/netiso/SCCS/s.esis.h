h64145
s 00002/00002/00107
d D 8.1 93/06/10 23:19:13 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00107
d D 7.5 93/05/25 11:51:32 bostic 5 4
c trailing comment after #else or #endif
e
s 00009/00001/00100
d D 7.4 91/05/06 19:23:56 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00000/00100
d D 7.3 89/08/29 13:44:13 sklower 3 2
c checkpoint for ``alpha tape''; tp is still a little broken.
e
s 00009/00015/00091
d D 7.2 89/04/22 11:53:48 sklower 2 1
c Checkpoint as of first successful tp connection, before posix, &
c before mckusick starts incorporating gnodes
e
s 00106/00000/00000
d D 7.1 88/12/14 15:29:34 sklower 1 0
c date and time created 88/12/14 15:29:34 by sklower
e
u
U
t
T
I 4
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

E 4
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
/*
 *	$Header: esis.h,v 4.7 88/09/15 11:24:18 hagens Exp $
 *	$Source: /usr/argo/sys/netiso/RCS/esis.h,v $
I 3
D 4
 *	%W% (Berkeley) %G% *
E 4
E 3
 */

#ifndef BYTE_ORDER
/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

#ifdef vax
#define	BYTE_ORDER	LITTLE_ENDIAN
#else
#define	BYTE_ORDER	BIG_ENDIAN	/* mc68000, tahoe, most others */
#endif
D 5
#endif BYTE_ORDER
E 5
I 5
#endif /* BYTE_ORDER */
E 5

#define	SNPAC_AGE		60			/* seconds */
#define	ESIS_CONFIG		60			/* seconds */
#define	ESIS_HT			(ESIS_CONFIG * 2)

/*
 *	Fixed part of an ESIS header
 */
struct esis_fixed {
	u_char	esis_proto_id;		/* network layer protocol identifier */
	u_char	esis_hdr_len;		/* length indicator (octets) */
	u_char	esis_vers;			/* version/protocol identifier extension */
	u_char	esis_res1;			/* reserved */
D 2
#if BYTE_ORDER == LITTLE_ENDIAN
	u_char		esis_type:5,		/* type code */
			esis_res4:1,		/* reserved */
			esis_res3:1,		/* reserved */
			esis_res2:1;		/* reserved */
E 2
I 2
	u_char	esis_type;			/* type code */
/* technically, type should be &='d 0x1f */
E 2
#define ESIS_ESH	0x02		/* End System Hello */
#define ESIS_ISH	0x04		/* Intermediate System Hello */
#define ESIS_RD		0x06		/* Redirect */
D 2
#endif
#if BYTE_ORDER == BIG_ENDIAN
	u_char	esis_res2:1,		/* reserved */
			esis_res3:1,		/* reserved */
			esis_res4:1,		/* reserved */
			esis_type:5;		/* type code */
#define ESIS_ESH	0x02		/* End System Hello */
#define ESIS_ISH	0x04		/* Intermediate System Hello */
#define ESIS_RD		0x06		/* Redirect */
#endif
E 2
	u_char	esis_ht_msb;		/* holding time (seconds) high byte */
	u_char	esis_ht_lsb;		/* holding time (seconds) low byte */
	u_char	esis_cksum_msb;		/* checksum high byte */
	u_char	esis_cksum_lsb;		/* checksum low byte */
};
I 2
/*
 * Values for ESIS datagram options
 */
#define ESISOVAL_NETMASK	0xe1	/* address mask option, RD PDU only */
#define ESISOVAL_SNPAMASK	0xe2	/* snpa mask option, RD PDU only */
#define ESISOVAL_ESCT		0xc6	/* end system conf. timer, ISH PDU only */

E 2

#define	ESIS_CKSUM_OFF		0x07
#define ESIS_CKSUM_REQUIRED(pdu)\
	((pdu->esis_cksum_msb != 0) || (pdu->esis_cksum_lsb != 0))

#define	ESIS_VERSION	1

struct esis_stat {
	u_short		es_nomem;			/* insufficient memory to send hello */
	u_short		es_badcsum;			/* incorrect checksum */
	u_short		es_badvers;			/* incorrect version number */
	u_short		es_badtype;			/* unknown pdu type field */
	u_short		es_toosmall;		/* packet too small */
	u_short		es_eshsent;			/* ESH sent */
	u_short		es_eshrcvd;			/* ESH rcvd */
	u_short		es_ishsent;			/* ISH sent */
	u_short		es_ishrcvd;			/* ISH rcvd */
	u_short		es_rdsent;			/* RD sent */
	u_short		es_rdrcvd;			/* RD rcvd */
};

#ifdef	KERNEL
struct esis_stat esis_stat;
D 5
#endif	KERNEL
E 5
I 5
#endif	/* KERNEL */
E 5
E 1
