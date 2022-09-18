h23790
s 00002/00002/00059
d D 8.1 93/06/10 21:44:36 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00057
d D 7.10 93/05/07 14:49:05 mckusick 10 9
c make safe for multiple includes
e
s 00000/00005/00057
d D 7.9 92/06/19 23:13:31 mckusick 9 8
c get rid of the fiction of NOQUAD
e
s 00013/00002/00049
d D 7.8 91/12/19 12:26:48 mckusick 8 7
c reorg for quad support
e
s 00021/00013/00030
d D 7.7 91/04/03 17:46:09 bostic 7 6
c one version for tahoe, hp300; miscellaneous cleanups
e
s 00001/00001/00042
d D 7.6 91/04/03 17:14:28 bostic 6 5
c don't make machine type specific
e
s 00001/00011/00042
d D 7.5 90/06/28 22:07:11 bostic 5 4
c new copyright notice
e
s 00012/00000/00041
d D 7.4 90/03/23 11:56:23 karels 4 3
c add NTOHL, etc. to convert in place
e
s 00010/00005/00031
d D 7.3 88/06/29 17:34:31 bostic 3 2
c install approved copyright notice
e
s 00001/00001/00035
d D 7.2 88/01/21 16:33:37 karels 2 1
c remove ENDIAN!
e
s 00036/00000/00000
d D 7.1 88/01/07 10:56:23 bostic 1 0
c date and time created 88/01/07 10:56:23 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1987 Regents of the University of California.
E 7
I 7
D 11
 * Copyright (c) 1987, 1991 Regents of the University of California.
E 7
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1987, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 3
 *
 *	%W% (Berkeley) %G%
 */

I 10
#ifndef _ENDIAN_H_
#define	_ENDIAN_H_

E 10
/*
I 8
D 9
 * Define _NOQUAD if the compiler does NOT support 64-bit integers.
 */
/* #define _NOQUAD */

/*
E 9
 * Define the order of 32-bit words in 64-bit words.
 */
#define _QUAD_HIGHWORD 0
#define _QUAD_LOWWORD 1

#ifndef _POSIX_SOURCE
/*
E 8
D 7
 * Definitions for byte order,
 * according to byte significance from low address to high.
E 7
I 7
 * Definitions for byte order, according to byte significance from low
 * address to high.
E 7
 */
D 7
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax) */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net) */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */
E 7
I 7
#define	LITTLE_ENDIAN	1234	/* LSB first: i386, vax */
#define	BIG_ENDIAN	4321	/* MSB first: 68000, ibm, net */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long */
E 7

D 6
#define	BYTE_ORDER	BIG_ENDIAN	/* byte order on tahoe */
E 6
I 6
#define	BYTE_ORDER	BIG_ENDIAN
E 6

I 7
D 8
#ifndef KERNEL
E 8
#include <sys/cdefs.h>
D 8
#endif
E 8

__BEGIN_DECLS
unsigned long	htonl __P((unsigned long));
unsigned short	htons __P((unsigned short));
unsigned long	ntohl __P((unsigned long));
unsigned short	ntohs __P((unsigned short));
__END_DECLS

E 7
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

E 4
D 7
unsigned short	ntohs(), htons();
unsigned long	ntohl(), htonl();
I 4

#define	NTOHL(x)	(x) = ntohl(x)
#define	NTOHS(x)	(x) = ntohs(x)
#define	HTONL(x)	(x) = htonl(x)
#define	HTONS(x)	(x) = htons(x)
E 7
I 7
#define	NTOHL(x)	(x) = ntohl((u_long)x)
#define	NTOHS(x)	(x) = ntohs((u_short)x)
#define	HTONL(x)	(x) = htonl((u_long)x)
#define	HTONS(x)	(x) = htons((u_short)x)
E 7
E 4
#endif
I 8
#endif /* !_POSIX_SOURCE */
I 10
#endif /* !_ENDIAN_H_ */
E 10
E 8
E 1
