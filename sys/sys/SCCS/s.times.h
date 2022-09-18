h19883
s 00005/00000/00034
d D 8.4 94/01/21 17:25:22 bostic 17 16
c add USL's copyright notice
e
s 00003/00003/00031
d D 8.3 94/01/04 16:16:52 bostic 16 15
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00004/00000/00030
d D 8.2 94/01/04 15:52:42 bostic 15 14
c protect against reinclusion
e
s 00002/00002/00028
d D 8.1 93/06/02 19:55:59 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00027
d D 7.7 92/06/23 00:09:57 bostic 13 12
c prefix all ANSI #define's with BSD_ so don't collide with other vendors
e
s 00001/00001/00029
d D 7.6 91/03/09 17:55:50 bostic 12 11
c create {hp300,i386,tahoe,vax}/include/ansi.h
e
s 00005/00005/00025
d D 7.5 91/02/05 17:03:47 bostic 11 10
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00029
d D 7.4 90/12/16 16:42:18 bostic 10 9
c kernel reorg
e
s 00002/00000/00028
d D 7.3 90/10/31 11:17:17 bostic 9 8
c don't include function prototypes in the kernel
e
s 00022/00011/00006
d D 7.2 90/08/27 17:44:33 bostic 8 7
c bring it back from the dead; POSIX specified it
e
s 00001/00001/00016
d D 7.1 86/06/04 23:29:39 mckusick 7 6
c 4.3BSD release version
e
s 00007/00001/00010
d D 6.2 85/06/08 15:09:51 mckusick 6 5
c Add copyright
e
s 00000/00000/00011
d D 6.1 83/07/29 06:14:25 sam 5 4
c 4.2 distribution
e
s 00001/00001/00010
d D 4.2 81/02/19 21:42:28 wnj 4 3
c %G%->%E%
e
s 00000/00000/00011
d D 4.1 80/11/09 17:01:50 bill 3 2
c stamp for 4bsd
e
s 00001/00001/00010
d D 3.2 80/06/07 03:01:16 bill 2 1
c %H%->%G%
e
s 00011/00000/00000
d D 3.1 80/04/09 16:25:34 bill 1 0
c date and time created 80/04/09 16:25:34 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 4
/*	%M%	%I%	%G%	*/
E 4
I 4
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
D 8
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 7
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 17
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 17
E 14
E 8
 *
I 8
 * %sccs.include.redist.c%
 *
E 8
 *	%W% (Berkeley) %G%
 */
E 6
E 4
E 2

I 15
D 16
#ifndef	_TIMES_H_
#define	_TIMES_H_
E 16
I 16
#ifndef	_SYS_TIMES_H_
#define	_SYS_TIMES_H_
E 16

E 15
D 8
/*
 * Structure returned by times()
 */
E 8
I 8
D 10
#include <machine/machtypes.h>
E 10
I 10
D 12
#include <machine/types.h>
E 12
I 12
#include <machine/ansi.h>
E 12
E 10

D 13
#ifdef	_CLOCK_T_
typedef	_CLOCK_T_	clock_t;
#undef	_CLOCK_T_
E 13
I 13
#ifdef	_BSD_CLOCK_T_
typedef	_BSD_CLOCK_T_	clock_t;
#undef	_BSD_CLOCK_T_
E 13
#endif

E 8
struct tms {
D 8
	time_t	tms_utime;		/* user time */
	time_t	tms_stime;		/* system time */
	time_t	tms_cutime;		/* user time, children */
	time_t	tms_cstime;		/* system time, children */
E 8
I 8
	clock_t tms_utime;	/* User CPU time */
	clock_t tms_stime;	/* System CPU time */
	clock_t tms_cutime;	/* User CPU time of terminated child procs */
	clock_t tms_cstime;	/* System CPU time of terminated child procs */
E 8
};
I 8

I 9
#ifndef KERNEL
E 9
D 11
#if __STDC__ || c_plusplus
clock_t times(struct tms *);
#else
clock_t times();
I 9
#endif
E 11
I 11
#include <sys/cdefs.h>

__BEGIN_DECLS
clock_t	times __P((struct tms *));
__END_DECLS
E 11
E 9
#endif
I 15
D 16
#endif /* !_TIMES_H_ */
E 16
I 16
#endif /* !_SYS_TIMES_H_ */
E 16
E 15
E 8
E 1
