h09623
s 00003/00000/00051
d D 7.9 93/05/07 16:04:52 mckusick 10 9
c protect against multiple inclusion
e
s 00018/00020/00033
d D 7.8 91/04/03 17:45:11 bostic 9 8
c one version for i386 and vax; miscellaneous cleanups
e
s 00012/00002/00041
d D 7.7 91/02/22 09:44:06 donn 8 6
c Prototype declarations.
e
s 00010/00002/00041
d R 7.7 91/02/22 09:39:28 donn 7 6
c Prototype declarations.
e
s 00001/00011/00042
d D 7.6 90/06/28 22:32:12 bostic 6 5
c new copyright notice
e
s 00004/00004/00049
d D 7.5 90/04/05 14:43:30 sklower 5 4
c redo NTOHS (etc.) macros since they are needed with casts.
e
s 00012/00000/00041
d D 7.4 90/03/23 11:56:11 karels 4 3
c add NTOHL, etc. to convert in place
e
s 00010/00005/00031
d D 7.3 88/06/29 17:52:17 bostic 3 2
c install approved copyright notice
e
s 00001/00001/00035
d D 7.2 88/01/21 16:34:16 karels 2 1
c remove endian!
e
s 00036/00000/00000
d D 7.1 88/01/07 11:10:47 bostic 1 0
c date and time created 88/01/07 11:10:47 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1987 Regents of the University of California.
E 9
I 9
 * Copyright (c) 1987, 1991 Regents of the University of California.
E 9
 * All rights reserved.
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 3
 *
 *	%W% (Berkeley) %G%
 */

I 10
#ifndef _ENDIAN_H_
#define	_ENDIAN_H_

E 10
/*
D 9
 * Definitions for byte order,
 * according to byte significance from low address to high.
E 9
I 9
 * Definitions for byte order, according to byte significance from low
 * address to high.
E 9
 */
D 9
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */
E 9
I 9
#define	LITTLE_ENDIAN	1234	/* LSB first: i386, vax */
#define	BIG_ENDIAN	4321	/* MSB first: 68000, ibm, net */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long */
E 9

D 9
#define	BYTE_ORDER	LITTLE_ENDIAN	/* byte order on vax */
E 9
I 9
#define	BYTE_ORDER	LITTLE_ENDIAN
E 9

I 9
#ifndef KERNEL
#include <sys/cdefs.h>
#endif

__BEGIN_DECLS
unsigned long	htonl __P((unsigned long));
unsigned short	htons __P((unsigned short));
unsigned long	ntohl __P((unsigned long));
unsigned short	ntohs __P((unsigned short));
__END_DECLS

E 9
/*
 * Macros for network/external number representation conversion.
 */
D 2
#if ENDIAN == BIG && !defined(lint)
E 2
I 2
#if BYTE_ORDER == BIG_ENDIAN && !defined(lint)
E 2
#define	ntohl(x)	(x)
#define	ntohs(x)	(x)
#define	htonl(x)	(x)
#define	htons(x)	(x)
I 4

#define	NTOHL(x)	(x)
#define	NTOHS(x)	(x)
#define	HTONL(x)	(x)
#define	HTONS(x)	(x)

E 4
#else
I 4
D 9

E 4
D 8
unsigned short	ntohs(), htons();
unsigned long	ntohl(), htonl();
E 8
I 8
#ifdef KERNEL
#include "cdefs.h"
#else
#include <sys/cdefs.h>
#endif

__BEGIN_DECLS
unsigned long	htonl __P((unsigned long));
unsigned short	htons __P((unsigned short));
unsigned long	ntohl __P((unsigned long));
unsigned short	ntohs __P((unsigned short));
__END_DECLS
E 9
E 8
I 4

D 5
#define	NTOHL(x)	(x) = ntohl(x)
#define	NTOHS(x)	(x) = ntohs(x)
#define	HTONL(x)	(x) = htonl(x)
#define	HTONS(x)	(x) = htons(x)
E 5
I 5
#define	NTOHL(x)	(x) = ntohl((u_long)x)
#define	NTOHS(x)	(x) = ntohs((u_short)x)
#define	HTONL(x)	(x) = htonl((u_long)x)
#define	HTONS(x)	(x) = htons((u_short)x)
E 5
E 4
#endif
E 1
