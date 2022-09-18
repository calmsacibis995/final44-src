h56709
s 00002/00002/00015
d D 8.1 93/06/02 19:56:51 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00008/00012
d D 7.4 91/05/05 18:38:37 bostic 15 14
c new copyright; att/bsd/shared
e
s 00000/00002/00020
d D 7.3 91/02/05 17:03:24 bostic 14 13
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00002/00002/00020
d D 7.2 87/12/18 11:35:14 bostic 13 12
c fix for ANSI C
e
s 00001/00001/00021
d D 7.1 86/06/04 23:31:48 mckusick 12 11
c 4.3BSD release version
e
s 00007/00001/00015
d D 6.3 85/06/08 15:12:43 mckusick 11 10
c Add copyright
e
s 00004/00000/00012
d D 6.2 84/08/28 17:29:51 bloom 10 9
c Change include paths.  No more ../h
e
s 00000/00000/00012
d D 6.1 83/07/29 06:15:02 sam 9 8
c 4.2 distribution
e
s 00006/00002/00006
d D 4.4 83/04/05 15:37:12 ralph 8 6
c updated for new ioctl call format.
e
s 00002/00002/00006
d R 4.4 83/03/10 15:44:59 ralph 7 6
c updated for new ioctl parameter passing.
e
s 00000/00000/00008
d D 4.3 81/02/25 23:30:05 wnj 6 5
c functional version with %b printf, etc
e
s 00001/00001/00007
d D 4.2 81/02/19 21:43:07 wnj 5 4
c %G%->%E%
e
s 00000/00000/00008
d D 4.1 80/11/09 17:02:03 bill 4 3
c stamp for 4bsd
e
s 00001/00001/00007
d D 3.3 80/06/07 03:02:09 bill 3 2
c %H%->%G%
e
s 00004/00004/00004
d D 3.2 80/06/04 13:50:36 bill 2 1
c reformat
e
s 00008/00000/00000
d D 3.1 80/04/09 16:25:56 bill 1 0
c date and time created 80/04/09 16:25:56 by bill
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%H%	*/
E 3
I 3
D 5
/*	%M%	%I%	%G%	*/
E 5
I 5
D 11
/*	%M%	%I%	%E%	*/
E 11
I 11
D 15
/*
D 12
 * Copyright (c) 1982 Regents of the University of California.
E 12
I 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
/*-
D 16
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
E 15
 *
I 15
 * %sccs.include.redist.c%
 *
E 15
 *	%W% (Berkeley) %G%
 */
E 11
E 5
E 3

I 8
D 14
#ifndef _IOCTL_
E 14
I 10
D 15
#ifdef KERNEL
#include "ioctl.h"
#else
E 15
E 10
#include <sys/ioctl.h>
I 10
D 14
#endif
E 14
E 10
D 15
#endif
E 15

E 8
D 2
#define VPRINT		0100
E 2
I 2
#define	VPRINT		0100
E 2
#define	VPLOT		0200
D 2
#define VPRINTPLOT	0400
E 2
I 2
#define	VPRINTPLOT	0400
E 2

D 2
#define VGETSTATE	(('v'<<8)|0)
#define VSETSTATE	(('v'<<8)|1)
E 2
I 2
D 8
#define	VGETSTATE	(('v'<<8)|0)
#define	VSETSTATE	(('v'<<8)|1)
E 8
I 8
D 13
#define	VGETSTATE	_IOR(v, 0, int)
#define	VSETSTATE	_IOW(v, 1, int)
E 13
I 13
#define	VGETSTATE	_IOR('v', 0, int)
#define	VSETSTATE	_IOW('v', 1, int)
E 13
E 8
E 2
E 1
