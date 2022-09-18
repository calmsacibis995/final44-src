h21818
s 00001/00001/00030
d D 8.3 94/03/20 14:35:10 bostic 7 6
c delete UofT; requested change from Henry Spencer <henry@zoo.toronto.edu>
e
s 00011/00006/00020
d D 8.2 94/03/16 12:43:04 bostic 6 5
c alpha3.3
e
s 00002/00002/00024
d D 8.1 93/06/04 12:58:26 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00025
d D 5.4 93/05/30 12:04:46 bostic 4 3
c protect against systems that use negative numbers for CHAR_MIN
e
s 00002/00001/00024
d D 5.3 93/05/21 16:06:57 bostic 3 2
c Henry Spencer's Alpha 3.0 regex release
e
s 00005/00002/00020
d D 5.2 92/09/30 12:58:08 bostic 2 1
c alpha2.1 release from Henry Spencer
e
s 00022/00000/00000
d D 5.1 92/08/06 11:58:13 bostic 1 0
c date and time created 92/08/06 11:58:13 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 Henry Spencer.
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
E 6
I 6
 * Copyright (c) 1992, 1993, 1994 Henry Spencer.
 * Copyright (c) 1992, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
D 7
 * Henry Spencer of the University of Toronto.
E 7
I 7
 * Henry Spencer.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* utility definitions */
#define	DUPMAX		_POSIX2_RE_DUP_MAX	/* xxx is this right? */
D 6
#define	INFINITY	(DUPMAX+1)
D 3
#define	NUC		(UCHAR_MAX+1)
E 3
I 3
D 4
#define	NC		(CHAR_MAX-CHAR_MIN+1)
E 4
I 4
#define	NC		((CHAR_MAX)-(CHAR_MIN)+1)
E 6
I 6
#define	INFINITY	(DUPMAX + 1)
#define	NC		(CHAR_MAX - CHAR_MIN + 1)
typedef unsigned char uch;
E 6
E 4

E 3
D 6
typedef unsigned char uchar;

E 6
I 6
/* switch off assertions (if not already off) if no REDEBUG */
E 6
D 2
#ifndef STATIC
#define	STATIC	static		/* override if cc no like "static int f();" */
E 2
I 2
#ifndef REDEBUG
#ifndef NDEBUG
#define	NDEBUG	/* no assertions please */
E 2
#endif
I 2
#endif
#include <assert.h>
I 6

/* for old systems with bcopy() but no memmove() */
#ifdef USEBCOPY
#define	memmove(d, s, c)	bcopy(s, d, c)
#endif
E 6
E 2
E 1
