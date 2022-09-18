h46815
s 00005/00000/00033
d D 8.2 94/01/21 17:25:06 bostic 15 14
c add USL's copyright notice
e
s 00002/00002/00031
d D 8.1 93/06/02 19:53:12 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00030
d D 7.6 92/06/19 22:17:57 mckusick 13 12
c add CP_INTR
e
s 00019/00022/00013
d D 7.5 91/02/15 14:30:11 bostic 12 11
c add Berkeley specific copyright notice
e
s 00001/00001/00034
d D 7.4 89/05/29 12:23:24 mckusick 11 10
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00002/00000/00033
d D 7.3 88/10/18 15:23:56 marc 10 9
c new terminal driver
e
s 00001/00001/00032
d D 7.2 88/05/21 13:52:01 karels 9 8
c increase DK_NDRIVE to 8
e
s 00001/00001/00032
d D 7.1 86/06/04 23:21:23 mckusick 8 7
c 4.3BSD release version
e
s 00007/00001/00026
d D 6.3 85/06/08 14:55:50 mckusick 7 6
c Add copyright
e
s 00001/00000/00026
d D 6.2 83/10/08 14:09:37 sam 6 5
c add dk_ndrive so iostat/pstat/vmstat can be binary portable
e
s 00000/00000/00026
d D 6.1 83/07/29 06:12:03 sam 5 4
c 4.2 distribution
e
s 00001/00001/00025
d D 4.2 81/02/19 21:40:09 wnj 4 3
c %G%->%E%
e
s 00000/00000/00026
d D 4.1 80/11/09 17:02:14 bill 3 2
c stamp for 4bsd
e
s 00007/00003/00019
d D 3.2 80/10/13 09:59:47 bill 2 1
c simpler, cleaner iostat interface
e
s 00022/00000/00000
d D 3.1 80/07/01 08:20:52 bill 1 0
c date and time created 80/07/01 08:20:52 by bill
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%G%	*/
E 4
I 4
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
D 12
/*
D 8
 * Copyright (c) 1982 Regents of the University of California.
E 8
I 8
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
/*-
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 15
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 15
E 14
E 12
 *
I 12
 * %sccs.include.redist.c%
 *
E 12
 *	%W% (Berkeley) %G%
 */
E 7
E 4

D 12
/*
 * Instrumentation
 */
#define	CPUSTATES	4

E 12
#define	CP_USER		0
#define	CP_NICE		1
#define	CP_SYS		2
D 13
#define	CP_IDLE		3
I 12
#define	CPUSTATES	4
E 13
I 13
#define	CP_INTR		3
#define	CP_IDLE		4
#define	CPUSTATES	5
E 13
E 12

D 9
#define	DK_NDRIVE	4
E 9
I 9
#define	DK_NDRIVE	8
E 9
D 2
#define	DK_NSTATES	16		/* 2^DK_NDRIVE */
E 2
D 12

E 12
I 2
#ifdef KERNEL
D 12
long	cp_time[CPUSTATES];
I 6
int	dk_ndrive;
E 6
E 2
int	dk_busy;
D 2
long	dk_time[CPUSTATES][DK_NSTATES];
long	dk_numb[DK_NDRIVE];
E 2
I 2
long	dk_time[DK_NDRIVE];
long	dk_seek[DK_NDRIVE];
long	dk_xfer[DK_NDRIVE];
E 2
long	dk_wds[DK_NDRIVE];
I 2
D 11
float	dk_mspw[DK_NDRIVE];
E 11
I 11
long	dk_wpms[DK_NDRIVE];
E 12
I 12
long cp_time[CPUSTATES];
long dk_seek[DK_NDRIVE];
long dk_time[DK_NDRIVE];
long dk_wds[DK_NDRIVE];
long dk_wpms[DK_NDRIVE];
long dk_xfer[DK_NDRIVE];
E 12
E 11
E 2

D 12
long	tk_nin;
I 10
long	tk_cancc;
long	tk_rawcc;
E 10
long	tk_nout;
E 12
I 12
int dk_busy;
int dk_ndrive;

long tk_cancc;
long tk_nin;
long tk_nout;
long tk_rawcc;
E 12
I 2
#endif
E 2
E 1
