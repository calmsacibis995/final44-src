h35174
s 00003/00000/00269
d D 8.2 94/02/16 18:15:58 bostic 36 35
c add T_AFSDB/18, T_NSAP/22, T_NSAP_PTR/23
c From: Paul Vixie <vixie@vangogh.CS.Berkeley.EDU>
e
s 00002/00002/00267
d D 8.1 93/06/02 20:01:34 bostic 35 34
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00117/00102/00152
d D 5.28 93/06/02 17:06:58 karels 34 33
c changes from bind 4.9 (most of them); change u_short to u_int16_t
e
s 00001/00001/00253
d D 5.27 92/06/29 18:46:56 bostic 33 32
c shut gcc up
e
s 00074/00046/00180
d D 5.26 92/06/29 18:44:57 karels 32 31
c Check in for Mike Karels by Keith Bostic
c endian cleanup, general cleanup
e
s 00005/00000/00221
d D 5.25 91/04/03 16:06:59 bostic 31 30
c protect all user-level include files against reinclusion
e
s 00001/00011/00220
d D 5.24 90/06/01 14:02:22 bostic 30 29
c new copyright notice
e
s 00002/00002/00229
d D 5.23 89/12/12 15:13:05 bloom 29 28
c add mips defines for byte order
e
s 00004/00003/00227
d D 5.22 89/06/06 13:27:28 karels 28 27
c yet more architectures
e
s 00002/00000/00228
d D 5.21 89/06/02 12:19:59 karels 27 26
c add T_TXT, C_HS
e
s 00009/00002/00219
d D 5.20 88/10/07 17:26:43 karels 26 24
c ah yes, give those strings some meaning
e
s 00003/00002/00219
d R 5.20 88/09/20 12:12:26 karels 25 24
c all sun's aren't big endian!
e
s 00016/00010/00205
d D 5.19 88/08/27 18:08:40 karels 24 23
c add mc68000, allow predefined BYTE_ORDER
e
s 00013/00002/00202
d D 5.18 88/06/27 16:37:43 bostic 23 22
c install approved copyright notice
e
s 00035/00000/00169
d D 5.17 87/11/17 10:05:17 karels 22 21
c add macros get get/put short/long.
e
s 00002/00002/00167
d D 5.16 87/07/15 18:19:05 dpk 21 20
c deleted CQUERY's, added STATUS Query. (dpk&pvm)
e
s 00002/00002/00167
d D 5.15 87/02/12 18:03:33 kjd 20 19
c fix getshort and getlong
e
s 00001/00001/00168
d D 5.14 87/02/11 13:51:02 kjd 19 18
c add support for encore
e
s 00016/00003/00153
d D 5.13 86/11/05 10:34:40 kjd 18 17
c add needed defines for dynamic updateing from Mike schwartz@wally.cs.washington.edu
e
s 00010/00010/00146
d D 5.12 86/07/07 11:01:33 kjd 17 16
c fix opcodes, 100 decimal doesn't fit into 4 bits very well
e
s 00001/00001/00155
d D 5.11 86/02/14 18:16:36 kjd 16 15
c Add define for CCI Power 32 - defined (tahoe)
e
s 00001/00000/00155
d D 5.10 86/02/03 23:09:27 kjd 15 14
c Add class field c_chaos
e
s 00001/00000/00154
d D 5.9 86/01/08 11:28:16 kjd 14 13
c Add MX record
e
s 00009/00009/00145
d D 5.8 86/01/07 13:53:42 kjd 13 12
c make non standard numbers in a range to give standard numbers room to grow
e
s 00001/00001/00153
d D 5.7 85/11/01 11:35:05 kjd 12 11
c change define to defined
e
s 00002/00001/00152
d D 5.6 85/10/31 19:43:44 kjd 11 10
c Add a few more cpu's to define
e
s 00000/00001/00153
d D 5.5 85/10/30 17:27:07 kjd 10 9
c Remove C_CS network class,  NIC said it goes bye bye
e
s 00009/00004/00145
d D 5.4 85/10/29 19:36:49 mckusick 9 8
c force people doing ports to define their machine's bit order
e
s 00016/00000/00133
d D 5.3 85/10/07 20:42:59 kjd 8 5
c add #ifdef BIT_ZERO_ON_LEFT for Gould and other nuxi machines, Thanks to mike@brl
e
s 00002/00002/00131
d R 5.3 85/09/13 18:09:18 bloom 7 5
c use getservbyname instead of compiling in port number
e
s 00002/00002/00131
d R 5.3 85/09/13 17:11:43 bloom 6 5
c don't compile in port numbers
e
s 00000/00006/00133
d D 5.2 85/07/29 17:50:56 kjd 5 4
c Remove HTONS definition, should use system htons()
e
s 00008/00001/00131
d D 5.1 85/05/30 09:37:30 dist 4 3
c Add copyright
e
s 00003/00000/00129
d D 4.3 85/03/27 14:34:40 ralph 3 2
c added getshort() and getlong() for machine independence.
e
s 00005/00000/00124
d D 4.2 85/03/18 14:01:51 ralph 2 1
c define NAMESERVER_PORT for connections
e
s 00124/00000/00000
d D 4.1 85/03/01 10:19:37 ralph 1 0
c date and time created 85/03/01 10:19:37 by ralph
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
D 28
 * Copyright (c) 1983 Regents of the University of California.
E 28
I 28
D 35
 * Copyright (c) 1983, 1989 Regents of the University of California.
E 28
D 23
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 23
I 23
 * All rights reserved.
E 35
I 35
 * Copyright (c) 1983, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 35
 *
D 30
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
E 30
I 30
 * %sccs.include.redist.c%
E 30
E 23
 *
D 34
 *	%W% (Berkeley) %G%
E 34
I 34
 *      %W% (Berkeley) %G%
 * -
 * Portions Copyright (c) 1993 by Digital Equipment Corporation.
 * 
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies, and that
 * the name of Digital Equipment Corporation not be used in advertising or
 * publicity pertaining to distribution of the document or software without
 * specific, written prior permission.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND DIGITAL EQUIPMENT CORP. DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL DIGITAL EQUIPMENT
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 * -
 * --Copyright--
E 34
 */

I 31
#ifndef _NAMESER_H_
#define	_NAMESER_H_

I 32
D 34
#ifndef BYTE_ORDER
E 32
E 31
E 4
/*
I 32
 * BSD gets the byte order definition from <machine/endian.h>.
 * If you don't have this include file, define NO_ENDIAN_H
 * and check that your machine will be guessed correctly below.
 */
#ifndef NO_ENDIAN_H
#include <machine/endian.h>
#else
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */
E 34
I 34
#include <sys/types.h>
E 34

D 34
#if defined(vax) || defined(ns32000) || defined(sun386) || defined(MIPSEL) || \
    defined(i386) || defined(BIT_ZERO_ON_RIGHT)
#define BYTE_ORDER	LITTLE_ENDIAN
#endif

#if defined(sel) || defined(pyr) || defined(mc68000) || defined(sparc) || \
    defined(is68k) || defined(tahoe) || defined(ibm032) || defined(ibm370) || \
    defined(MIPSEB) || defined (BIT_ZERO_ON_LEFT)
#define BYTE_ORDER	BIG_ENDIAN
#endif
#endif /* NO_ENDIAN_H */
#endif /* BYTE_ORDER */

#ifndef BYTE_ORDER
	/* you must determine what the correct bit order is for your compiler */
	Error! UNDEFINED_BIT_ORDER
#endif

E 34
/*
E 32
 * Define constants based on rfc883
 */
#define PACKETSZ	512		/* maximum packet size */
#define MAXDNAME	256		/* maximum domain name */
#define MAXCDNAME	255		/* maximum compressed domain name */
#define MAXLABEL	63		/* maximum length of domain label */
	/* Number of bytes of fixed size data in query structure */
#define QFIXEDSZ	4
	/* number of bytes of fixed size data in resource record */
#define RRFIXEDSZ	10

D 5
#ifdef vax
#define HTONS(s)	(((s >> 8) & 0xff) | ((s & 0xff) << 8))
#else
#define HTONS(s)
#endif

E 5
/*
I 2
 * Internet nameserver port number
 */
#define NAMESERVER_PORT	53

/*
E 2
 * Currently defined opcodes
 */
D 17
#define QUERY		0		/* standard query */
#define IQUERY		1		/* inverse query */
#define CQUERYM		2		/* completion query (multiple) */
#define CQUERYU		3		/* completion query (unique) */
E 17
I 17
#define QUERY		0x0		/* standard query */
#define IQUERY		0x1		/* inverse query */
D 21
#define CQUERYM		0x2		/* completion query (multiple) */
#define CQUERYU		0x3		/* completion query (unique) */
E 21
I 21
#define STATUS		0x2		/* nameserver status query */
D 33
/*#define xxx		0x3		/* 0x3 reserved */
E 33
I 33
D 34
#define __NAMESER_RESV	0x3		/* 0x3 reserved */
E 33
E 21
E 17
	/* non standard */
E 34
I 34
/*#define xxx		0x3		/* 0x3 reserved */
	/* non standard - supports ALLOW_UPDATES stuff from Mike Schwartz */
E 34
D 13
#define UPDATEA		11		/* add resource record */
#define UPDATED		12		/* delete resource record */
#define UPDATEM		13		/* modify resource record */
#define ZONEINIT	14		/* initial zone transfer */
#define ZONEREF		15		/* incremental zone referesh */
E 13
I 13
D 17
#define UPDATEA		100		/* add resource record */
#define UPDATED		101		/* delete resource record */
#define UPDATEM		102		/* modify resource record */
#define ZONEINIT	103		/* initial zone transfer */
#define ZONEREF		104		/* incremental zone referesh */
E 17
I 17
D 18
#define UPDATEA		0xb		/* add resource record */
#define UPDATED		0xc		/* delete resource record */
#define UPDATEM		0xd		/* modify resource record */
E 18
I 18
#define UPDATEA		0x9		/* add resource record */
#define UPDATED		0xa		/* delete a specific resource record */
D 34
#define UPDATEDA	0xb		/* delete all nemed resource record */
E 34
I 34
#define UPDATEDA	0xb		/* delete all named resource record */
E 34
#define UPDATEM		0xc		/* modify a specific resource record */
#define UPDATEMA	0xd		/* modify all named resource record */

E 18
#define ZONEINIT	0xe		/* initial zone transfer */
#define ZONEREF		0xf		/* incremental zone referesh */
E 17
E 13

/*
 * Currently defined response codes
 */
#define NOERROR		0		/* no error */
#define FORMERR		1		/* format error */
#define SERVFAIL	2		/* server failure */
#define NXDOMAIN	3		/* non existent domain */
#define NOTIMP		4		/* not implemented */
#define REFUSED		5		/* query refused */
	/* non standard */
D 13
#define NOCHANGE	15		/* update failed to change db */
E 13
I 13
D 17
#define NOCHANGE	100		/* update failed to change db */
E 17
I 17
#define NOCHANGE	0xf		/* update failed to change db */
E 17
E 13

/*
 * Type values for resources and queries
 */
#define T_A		1		/* host address */
#define T_NS		2		/* authoritative server */
#define T_MD		3		/* mail destination */
#define T_MF		4		/* mail forwarder */
#define T_CNAME		5		/* connonical name */
#define T_SOA		6		/* start of authority zone */
#define T_MB		7		/* mailbox domain name */
#define T_MG		8		/* mail group member */
#define T_MR		9		/* mail rename name */
#define T_NULL		10		/* null resource record */
#define T_WKS		11		/* well known service */
#define T_PTR		12		/* domain name pointer */
#define T_HINFO		13		/* host information */
#define T_MINFO		14		/* mailbox information */
I 14
#define T_MX		15		/* mail routing information */
I 27
#define T_TXT		16		/* text strings */
I 34
#define	T_RP		17		/* responsible person */
I 36
#define	T_AFSDB		18		/* AFS cell database */
#define	T_NSAP		22		/* NSAP address */
#define	T_NSAP_PTR	23		/* reverse lookup for NSAP */
E 36
E 34
E 27
E 14
	/* non standard */
D 13
#define T_UINFO		15		/* user (finger) information */
#define T_UID		16		/* user ID */
#define T_GID		17		/* group ID */
E 13
I 13
#define T_UINFO		100		/* user (finger) information */
#define T_UID		101		/* user ID */
#define T_GID		102		/* group ID */
I 18
#define T_UNSPEC	103		/* Unspecified format (binary data) */
E 18
E 13
	/* Query type values which do not appear in resource records */
#define T_AXFR		252		/* transfer zone of authority */
#define T_MAILB		253		/* transfer mailbox records */
#define T_MAILA		254		/* transfer mail agent records */
#define T_ANY		255		/* wildcard match */

/*
 * Values for class field
 */

#define C_IN		1		/* the arpa internet */
I 15
D 34
#define C_CHAOS		3		/* for chaos net at MIT */
I 27
D 32
#define C_HS		4		/* for Hesiod name server at MIT */
E 32
I 32
#define C_HS		4		/* for Hesiod name server at MIT XXX */
E 34
I 34
#define C_CHAOS		3		/* for chaos net (MIT) */
#define C_HS		4		/* for Hesiod name server (MIT) (XXX) */
E 34
E 32
E 27
E 15
D 10
#define C_CS		2		/* the computer science network */
E 10
	/* Query class values which do not appear in resource records */
#define C_ANY		255		/* wildcard match */
I 18

/*
 * Status return codes for T_UNSPEC conversion routines
 */
#define CONV_SUCCESS 0
#define CONV_OVERFLOW -1
#define CONV_BADFMT -2
#define CONV_BADCKSUM -3
#define CONV_BADBUFLEN -4
E 18

I 34
#ifndef BYTE_ORDER
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax, pc) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp)*/

#if defined(vax) || defined(ns32000) || defined(sun386) || defined(i386) || \
    defined(MIPSEL) || defined(_MIPSEL) || defined(BIT_ZERO_ON_RIGHT) || \
    defined(__alpha__) || defined(__alpha)
#define BYTE_ORDER	LITTLE_ENDIAN
#endif

#if defined(sel) || defined(pyr) || defined(mc68000) || defined(sparc) || \
    defined(is68k) || defined(tahoe) || defined(ibm032) || defined(ibm370) || \
    defined(MIPSEB) || defined(_MIPSEB) || defined(_IBMR2) || \
    defined(apollo) || defined(hp9000) || defined(hp9000s300) || \
    defined (BIT_ZERO_ON_LEFT)
#define BYTE_ORDER	BIG_ENDIAN
#endif
#endif /* BYTE_ORDER */

#if !defined(BYTE_ORDER) || \
    (BYTE_ORDER != BIG_ENDIAN && BYTE_ORDER != LITTLE_ENDIAN && \
    BYTE_ORDER != PDP_ENDIAN)
	/* you must determine what the correct bit order is for
	 * your compiler - the next line is an intentional error
	 * which will force your compiles to bomb until you fix
	 * the above macros.
	 */
  #error "Undefined or invalid BYTE_ORDER";
#endif

E 34
I 24
D 32
#ifndef BYTE_ORDER
D 26
#if defined(vax) || defined(ns32000) || defined(BIT_ZERO_ON_RIGHT)
E 26
I 26
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

D 29
#if defined(vax) || defined(ns32000) || defined(sun386) || \
E 29
I 29
#if defined(vax) || defined(ns32000) || defined(sun386) || defined(MIPSEL) || \
E 29
    defined(BIT_ZERO_ON_RIGHT)
E 26
#define BYTE_ORDER	LITTLE_ENDIAN
I 26

E 26
#endif
D 26
#if defined(sun) || defined(sel) || defined(pyr) || defined(mc68000) || \
E 26
I 26
#if defined(sel) || defined(pyr) || defined(mc68000) || defined(sparc) || \
E 26
D 28
    defined(is68k) || defined (tahoe) || defined (BIT_ZERO_ON_LEFT)
E 28
I 28
    defined(is68k) || defined(tahoe) || defined(ibm032) || defined(ibm370) || \
D 29
    defined (BIT_ZERO_ON_LEFT)
E 29
I 29
    defined(MIPSEB) || defined (BIT_ZERO_ON_LEFT)
E 29
E 28
#define BYTE_ORDER	BIG_ENDIAN
#endif
#endif /* BYTE_ORDER */
I 26

E 26
#ifndef BYTE_ORDER
	/* you must determine what the correct bit order is for your compiler */
	UNDEFINED_BIT_ORDER;
#endif
E 32
E 24
/*
D 32
 * Structure for query header, the order of the fields is machine and
 * compiler dependent, in our case, the bits within a byte are assignd 
 * least significant first, while the order of transmition is most 
 * significant first.  This requires a somewhat confusing rearrangement.
E 32
I 32
 * Structure for query header.  The order of the fields is machine- and
 * compiler-dependent, depending on the byte/bit order and the layout
 * of bit fields.  We use bit fields only in int variables, as this
 * is all ANSI requires.  This requires a somewhat confusing rearrangement.
E 32
 */

typedef struct {
I 34
	u_int16_t id;		/* query identification number */
E 34
D 32
	u_short	id;		/* query identification number */
E 32
I 8
D 9
#ifdef BIT_ZERO_ON_LEFT
E 9
I 9
D 11
#if defined (sun) || defined (gould) || defined (BIT_ZERO_ON_LEFT)
E 11
I 11
D 12
#if defined (sun) || defined (sel) || defined (pyr) || define (is68k) \
E 12
I 12
D 24
#if defined (sun) || defined (sel) || defined (pyr) || defined (is68k) \
E 12
D 16
|| defined (BIT_ZERO_ON_LEFT)
E 16
I 16
|| defined (tahoe) || defined (BIT_ZERO_ON_LEFT)
E 16
E 11
E 9
	/* Bit zero on left:  Gould and similar architectures */
E 24
I 24
#if BYTE_ORDER == BIG_ENDIAN
I 32
D 34
			/* first and second bytes */
	u_int	id:16,		/* query identification number */
E 34
E 32
E 24
E 8
			/* fields in third byte */
I 8
D 32
	u_char	qr:1;		/* response flag */
	u_char	opcode:4;	/* purpose of message */
	u_char	aa:1;		/* authoritive answer */
	u_char	tc:1;		/* truncated message */
E 8
	u_char	rd:1;		/* recursion desired */
E 32
I 32
D 34
		qr:1,		/* response flag */
		opcode:4,	/* purpose of message */
		aa:1,		/* authoritive answer */
		tc:1,		/* truncated message */
		rd:1,		/* recursion desired */
E 34
I 34
	u_int	qr:1;		/* response flag */
	u_int	opcode:4;	/* purpose of message */
	u_int	aa:1;		/* authoritive answer */
	u_int	tc:1;		/* truncated message */
	u_int	rd:1;		/* recursion desired */
E 34
E 32
I 8
D 9
			/* fields in forth byte */
E 9
I 9
			/* fields in fourth byte */
E 9
D 32
	u_char	ra:1;		/* recursion available */
	u_char	pr:1;		/* primary server required (non standard) */
	u_char	unused:2;	/* unused bits */
	u_char	rcode:4;	/* response code */
E 32
I 32
D 34
		ra:1,		/* recursion available */
		pr:1,		/* primary server required (non standard) */
		unused:2,	/* unused bits */
		rcode:4;	/* response code */

E 34
I 34
	u_int	ra:1;		/* recursion available */
	u_int	pr:1;		/* primary server required (non standard) */
	u_int	unused:2;	/* unused bits */
	u_int	rcode:4;	/* response code */
E 34
E 32
D 24
#else
D 9
	/* Bit zero on right:  VAX, PDP-11, etc */
E 9
I 9
D 19
#if defined (vax) || defined (BIT_ZERO_ON_RIGHT)
E 19
I 19
#if defined (vax) || defined(ns32000) || defined (BIT_ZERO_ON_RIGHT)
E 19
	/* Bit zero on right:  VAX */
E 24
I 24
#endif
D 28
#if BYTE_ORDER == LITTLE_ENDIAN
E 28
I 28
D 32
#if BYTE_ORDER == LITTLE_ENDIAN || BYTE_ORDER == PDP_ENDIAN
E 32
I 32
D 34
#if BYTE_ORDER == LITTLE_ENDIAN
			/* first and second bytes */
	u_int	id:16,		/* query identification number */
E 34
I 34
#if BYTE_ORDER == LITTLE_ENDIAN || BYTE_ORDER == PDP_ENDIAN
E 34
E 32
E 28
E 24
E 9
			/* fields in third byte */
D 32
	u_char	rd:1;		/* recursion desired */
E 8
	u_char	tc:1;		/* truncated message */
	u_char	aa:1;		/* authoritive answer */
	u_char	opcode:4;	/* purpose of message */
	u_char	qr:1;		/* response flag */
E 32
I 32
D 34
		rd:1,		/* recursion desired */
		tc:1,		/* truncated message */
		aa:1,		/* authoritive answer */
		opcode:4,	/* purpose of message */
		qr:1,		/* response flag */
E 32
D 9
			/* fields in forth byte */
E 9
I 9
			/* fields in fourth byte */
E 9
D 32
	u_char	rcode:4;	/* response code */
	u_char	unused:2;	/* unused bits */
	u_char	pr:1;		/* primary server required (non standard) */
	u_char	ra:1;		/* recursion available */
E 32
I 32
		rcode:4,	/* response code */
		unused:2,	/* unused bits */
		pr:1,		/* primary server required (non standard) */
		ra:1;		/* recursion available */
#endif
#if BYTE_ORDER == PDP_ENDIAN	/* and assume 16-bit ints... */
	u_short	id;		/* query identification number */
			/* fields in third byte */
E 34
	u_int	rd:1;		/* recursion desired */
D 34
		tc:1,		/* truncated message */
		aa:1,		/* authoritive answer */
		opcode:4,	/* purpose of message */
		qr:1,		/* response flag */
E 34
I 34
	u_int	tc:1;		/* truncated message */
	u_int	aa:1;		/* authoritive answer */
	u_int	opcode:4;	/* purpose of message */
	u_int	qr:1;		/* response flag */
E 34
			/* fields in fourth byte */
D 34
		rcode:4,	/* response code */
		unused:2,	/* unused bits */
		pr:1,		/* primary server required (non standard) */
		ra:1;		/* recursion available */
E 34
I 34
	u_int	rcode:4;	/* response code */
	u_int	unused:2;	/* unused bits */
	u_int	pr:1;		/* primary server required (non standard) */
	u_int	ra:1;		/* recursion available */
E 34
E 32
I 9
D 24
#else
	/* you must determine what the correct bit order is for your compiler */
	UNDEFINED_BIT_ORDER;
#endif
E 24
E 9
I 8
#endif
E 8
			/* remaining bytes */
D 34
	u_short	qdcount;	/* number of question entries */
	u_short	ancount;	/* number of answer entries */
	u_short	nscount;	/* number of authority entries */
	u_short	arcount;	/* number of resource entries */
E 34
I 34
	u_int16_t qdcount;	/* number of question entries */
	u_int16_t ancount;	/* number of answer entries */
	u_int16_t nscount;	/* number of authority entries */
	u_int16_t arcount;	/* number of resource entries */
E 34
} HEADER;

/*
 * Defines for handling compressed domain names
 */
#define INDIR_MASK	0xc0

/*
 * Structure for passing resource records around.
 */
struct rrec {
D 34
	short	r_zone;			/* zone number */
	short	r_class;		/* class number */
	short	r_type;			/* type number */
	u_long	r_ttl;			/* time to live */
E 34
I 34
	int16_t	r_zone;			/* zone number */
	int16_t	r_class;		/* class number */
	int16_t	r_type;			/* type number */
	u_int32_t	r_ttl;			/* time to live */
E 34
	int	r_size;			/* size of data area */
	char	*r_data;		/* pointer to data */
};
I 3

D 20
extern	u_short	getshort();
extern	u_long	getlong();
E 20
I 20
D 34
extern	u_short	_getshort();
extern	u_long	_getlong();
E 34
I 34
extern	u_int16_t	_getshort();
extern	u_int32_t	_getlong();
E 34
I 22

/*
D 34
 * Inline versions of get/put short/long.
 * Pointer is advanced; we assume that both arguments
 * are lvalues and will already be in registers.
 * cp MUST be u_char *.
E 34
I 34
 * Inline versions of get/put short/long.  Pointer is advanced.
 * We also assume that a "u_int16_t" holds 2 "chars"
 * and that a "u_int32_t" holds 4 "chars".
 *
 * These macros demonstrate the property of C whereby it can be
 * portable or it can be elegant but never both.
E 34
 */
#define GETSHORT(s, cp) { \
D 34
	(s) = *(cp)++ << 8; \
	(s) |= *(cp)++; \
E 34
I 34
	register u_char *t_cp = (u_char *)(cp); \
	(s) = ((u_int16_t)t_cp[0] << 8) | (u_int16_t)t_cp[1]; \
	(cp) += 2; \
E 34
}

#define GETLONG(l, cp) { \
D 34
	(l) = *(cp)++ << 8; \
	(l) |= *(cp)++; (l) <<= 8; \
	(l) |= *(cp)++; (l) <<= 8; \
	(l) |= *(cp)++; \
E 34
I 34
	register u_char *t_cp = (u_char *)(cp); \
	(l) = (((u_int32_t)t_cp[0]) << 24) \
	    | (((u_int32_t)t_cp[1]) << 16) \
	    | (((u_int32_t)t_cp[2]) << 8) \
	    | (((u_int32_t)t_cp[3])); \
	(cp) += 4; \
E 34
}

D 34

E 34
#define PUTSHORT(s, cp) { \
D 34
	*(cp)++ = (s) >> 8; \
	*(cp)++ = (s); \
E 34
I 34
	register u_int16_t t_s = (u_int16_t)(s); \
	register u_char *t_cp = (u_char *)(cp); \
	*t_cp++ = t_s >> 8; \
	*t_cp   = t_s; \
	(cp) += 2; \
E 34
}

/*
D 34
 * Warning: PUTLONG destroys its first argument.
E 34
I 34
 * Warning: PUTLONG --no-longer-- destroys its first argument.  if you
 * were depending on this "feature", you will lose.
E 34
 */
#define PUTLONG(l, cp) { \
D 34
	(cp)[3] = l; \
	(cp)[2] = (l >>= 8); \
	(cp)[1] = (l >>= 8); \
	(cp)[0] = l >> 8; \
	(cp) += sizeof(u_long); \
E 34
I 34
	register u_int32_t t_l = (u_int32_t)(l); \
	register u_char *t_cp = (u_char *)(cp); \
	*t_cp++ = t_l >> 24; \
	*t_cp++ = t_l >> 16; \
	*t_cp++ = t_l >> 8; \
	*t_cp   = t_l; \
	(cp) += 4; \
E 34
}
I 31

#endif /* !_NAMESER_H_ */
E 31
E 22
E 20
E 3
E 1
