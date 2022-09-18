h10241
s 00002/00002/00045
d D 8.1 93/06/02 20:05:54 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00042
d D 5.4 91/04/08 08:54:06 bostic 6 5
c new copyright; att/bsd/shared
e
s 00005/00000/00041
d D 5.3 91/04/03 16:14:10 bostic 5 4
c protect all user-level include files against reinclusion
e
s 00001/00001/00040
d D 5.2 90/12/17 16:58:45 william 4 3
c 386 byte sex; really should be ENDIAN et al someday...
e
s 00007/00001/00034
d D 5.1 85/05/30 09:36:53 dist 3 2
c Add copyright
e
s 00001/00001/00034
d D 4.2 83/07/01 04:08:52 sam 2 1
c put stdio where it belongs
e
s 00035/00000/00000
d D 4.1 83/05/03 13:48:05 sam 1 0
c date and time created 83/05/03 13:48:05 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.proprietary.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 3

I 5
#ifndef _MP_H_
#define	_MP_H_

E 5
#define MINT struct mint
MINT
{	int len;
	short *val;
};
#define FREE(x) {if(x.len!=0) {free((char *)x.val); x.len=0;}}
#ifndef DBG
#define shfree(u) free((char *)u)
#else
D 2
#include "stdio.h"
E 2
I 2
#include <stdio.h>
E 2
#define shfree(u) { if(dbg) fprintf(stderr, "free %o\n", u); free((char *)u);}
extern int dbg;
#endif
D 4
#ifndef vax
E 4
I 4
#if !defined(vax) && !defined(i386)
E 4
struct half
{	short high;
	short low;
};
#else
struct half
{	short low;
	short high;
};
#endif
extern MINT *itom();
extern short *xalloc();

#ifdef lint
extern xv_oid;
#define VOID xv_oid =
#else
#define VOID
#endif
I 5

#endif /* !_MP_H_ */
E 5
E 1
