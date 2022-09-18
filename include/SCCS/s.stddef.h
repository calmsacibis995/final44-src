h17645
s 00002/00002/00034
d D 8.1 93/06/02 20:06:54 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00033
d D 5.8 93/05/28 12:25:01 bostic 8 7
c don't typedef run_t if _ANSI_SOURCE defined
e
s 00001/00000/00033
d D 5.7 93/05/26 14:01:04 bostic 7 6
c rune support from Paul Borman
e
s 00007/00007/00026
d D 5.6 92/06/22 21:27:41 bostic 6 5
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00000/00032
d D 5.5 91/04/03 16:27:19 bostic 5 4
c protect all user-level include files against reinclusion
e
s 00001/00001/00031
d D 5.4 91/03/09 17:56:53 bostic 4 3
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00001/00001/00031
d D 5.3 90/12/18 10:52:15 bostic 3 2
c kernel reorg
e
s 00001/00001/00031
d D 5.2 90/05/17 16:17:13 bostic 2 1
c mv x3j11.h -> machtypes.h
e
s 00032/00000/00000
d D 5.1 90/05/15 19:17:03 bostic 1 0
c date and time created 90/05/15 19:17:03 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#ifndef _STDDEF_H_
#define _STDDEF_H_
I 5

E 5
D 2
#include <machine/x3j11.h>
E 2
I 2
D 3
#include <machine/machtypes.h>
E 3
I 3
D 4
#include <machine/types.h>
E 4
I 4
#include <machine/ansi.h>
E 4
E 3
E 2

D 6
typedef	_PTRDIFF_T_	ptrdiff_t;
E 6
I 6
typedef	_BSD_PTRDIFF_T_	ptrdiff_t;
E 6

D 6
#ifdef	_SIZE_T_
typedef	_SIZE_T_	size_t;
#undef	_SIZE_T_
E 6
I 6
#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
E 6
#endif

D 6
#ifdef	_WCHAR_T_
typedef	_WCHAR_T_	wchar_t;
#undef	_WCHAR_T_
E 6
I 6
#ifdef	_BSD_WCHAR_T_
D 8
typedef	_BSD_WCHAR_T_	wchar_t;
E 8
I 8
#ifndef _ANSI_SOURCE
E 8
I 7
typedef	_BSD_WCHAR_T_	rune_t;
I 8
#endif
typedef	_BSD_WCHAR_T_	wchar_t;
E 8
E 7
#undef	_BSD_WCHAR_T_
E 6
#endif

#ifndef	NULL
#define	NULL	0
#endif

#define	offsetof(type, member)	((size_t)(&((type *)0)->member))

#endif /* _STDDEF_H_ */
E 1
