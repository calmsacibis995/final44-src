h13480
s 00001/00003/00067
d D 7.2 92/06/25 18:53:26 utashiro 2 1
c _NOQUAD is not necessary always
e
s 00070/00000/00000
d D 7.1 92/06/04 16:03:05 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell and Kazumasa Utashiro of Software Research
 * Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Define _NOQUAD if the compiler does NOT support 64-bit integers.
 */
D 2
#ifndef USE_QUAD /* for testing */
#define	_NOQUAD
#endif
E 2
I 2
/* #define _NOQUAD */
E 2

/*
 * Define the order of 32-bit words in 64-bit words.
 */
#define	_QUAD_HIGHWORD	0
#define	_QUAD_LOWWORD	1

#ifndef _POSIX_SOURCE
/*
 * Definitions for byte order, according to byte significance from low
 * address to high.
 */
#define	LITTLE_ENDIAN	1234	/* LSB first: i386, vax */
#define	BIG_ENDIAN	4321	/* MSB first: 68000, ibm, net */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long */

#define	BYTE_ORDER	BIG_ENDIAN

#include <sys/cdefs.h>

__BEGIN_DECLS
#if BYTE_ORDER == LITTLE_ENDIAN
unsigned long	htonl __P((unsigned long));
unsigned short	htons __P((unsigned short));
unsigned long	ntohl __P((unsigned long));
unsigned short	ntohs __P((unsigned short));
#endif
__END_DECLS

/*
 * Macros for network/external number representation conversion.
 */
#if BYTE_ORDER == BIG_ENDIAN && !defined(lint)
#define	ntohl(x)	(x)
#define	ntohs(x)	(x)
#define	htonl(x)	(x)
#define	htons(x)	(x)

#define	NTOHL(x)	(x)
#define	NTOHS(x)	(x)
#define	HTONL(x)	(x)
#define	HTONS(x)	(x)

#else

#define	NTOHL(x)	(x) = ntohl((u_long)x)
#define	NTOHS(x)	(x) = ntohs((u_short)x)
#define	HTONL(x)	(x) = htonl((u_long)x)
#define	HTONS(x)	(x) = htons((u_short)x)
#endif
#endif /* !_POSIX_SOURCE */
E 1
