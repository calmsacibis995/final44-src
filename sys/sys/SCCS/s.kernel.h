h06628
s 00005/00000/00028
d D 8.3 94/01/21 17:25:12 bostic 26 25
c add USL's copyright notice
e
s 00000/00001/00028
d D 8.2 93/11/30 16:25:02 mckusick 25 24
c update for USL
e
s 00002/00002/00027
d D 8.1 93/06/02 19:53:54 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00009/00029
d D 7.11 93/05/12 14:49:03 mckusick 23 22
c get rid of old trash
e
s 00001/00006/00037
d D 7.10 93/04/27 12:26:04 bostic 22 21
c move struct loadavg and averunnable variable from kernel.h to resource.h
e
s 00003/00005/00040
d D 7.9 92/07/08 00:44:46 torek 21 20
c time becomes volatile; move realitexpire to systm.h; lint
e
s 00003/00003/00042
d D 7.8 92/06/19 23:20:31 mckusick 20 19
c phz => stathz
e
s 00000/00007/00045
d D 7.7 92/03/09 16:56:58 mckusick 19 18
c struct clockinfo definition moves from kernel.h to time.h
e
s 00029/00017/00023
d D 7.6 92/02/25 17:19:47 mckusick 18 17
c add lots of extern's; add struct clockinfo and struct loadavg 
c defining the structures returned by getkerninfo for clcok rate and 
c load average respectively
e
s 00001/00000/00039
d D 7.5 91/12/19 12:32:29 mckusick 17 16
c add mono_time for NFS leases
e
s 00023/00024/00016
d D 7.4 91/02/15 14:29:19 bostic 16 15
c add Berkeley specific copyright notice
e
s 00001/00001/00039
d D 7.3 90/05/09 11:01:40 mckusick 15 14
c hp300 does not have to support `double avenrun' for COMPAT_43
e
s 00003/00000/00037
d D 7.2 89/05/29 13:06:23 mckusick 14 12
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00002/00001/00036
d R 7.2 89/05/29 12:27:03 mckusick 13 12
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00001/00001/00036
d D 7.1 86/06/04 23:24:28 mckusick 12 11
c 4.3BSD release version
e
s 00007/00001/00030
d D 6.3 85/06/08 15:00:29 mckusick 11 10
c Add copyright
e
s 00001/00001/00030
d D 6.2 85/06/07 15:35:29 bloom 10 9
c use MAXHOSTNAMELEN
e
s 00000/00000/00031
d D 6.1 83/07/29 06:12:57 sam 9 8
c 4.2 distribution
e
s 00001/00000/00030
d D 4.8 83/05/30 17:44:22 sam 8 7
c put phz where it belongs
e
s 00002/00000/00028
d D 4.7 82/10/21 20:56:56 root 7 6
c lint
e
s 00002/00000/00026
d D 4.6 82/10/21 17:30:35 root 6 5
c lint
e
s 00000/00002/00026
d D 4.5 82/10/20 01:16:13 root 5 4
c lint
e
s 00009/00001/00019
d D 4.4 82/09/12 03:19:27 root 4 3
c 
e
s 00002/00000/00018
d D 4.3 82/09/08 08:11:22 root 3 2
c label_t now a structure; other misc changes
e
s 00003/00000/00015
d D 4.2 82/09/06 23:01:13 root 2 1
c more timer stuff
e
s 00015/00000/00000
d D 4.1 82/09/04 09:27:11 root 1 0
c date and time created 82/09/04 09:27:11 by root
e
u
U
t
T
I 1
D 11
/*	%M%	%I%	%E%	*/
E 11
I 11
D 16
/*
D 12
 * Copyright (c) 1982 Regents of the University of California.
E 12
I 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 12
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
/*-
D 24
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 26
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 26
E 24
E 16
 *
I 16
 * %sccs.include.redist.c%
 *
E 16
 *	%W% (Berkeley) %G%
 */
E 11

D 16
/*
 * Global variables for the kernel
 */
E 16
I 16
/* Global variables for the kernel. */
D 25
long rmalloc();
E 25
E 16

I 6
D 16
long	rmalloc();

E 16
E 6
/* 1.1 */
D 16
long	hostid;
D 10
char	hostname[32];
E 10
I 10
char	hostname[MAXHOSTNAMELEN];
E 10
I 2
int	hostnamelen;
E 16
I 16
D 18
long hostid;
char hostname[MAXHOSTNAMELEN];
int hostnamelen;
E 18
I 18
extern long hostid;
extern char hostname[MAXHOSTNAMELEN];
extern int hostnamelen;
E 18
E 16
E 2
D 5
int	nextpid;
E 5

/* 1.2 */
I 17
D 18
struct timeval mono_time;
E 17
D 16
struct	timeval boottime;
struct	timeval time;
struct	timezone tz;			/* XXX */
I 2
int	hz;
I 8
int	phz;				/* alternate clock's frequency */
E 8
int	tick;
I 3
int	lbolt;				/* awoken once a second */
D 4
int	unsel(),unrto();
E 4
I 4
D 5
int	selitexpire();
E 5
int	realitexpire();
E 16
I 16
struct timeval boottime;
struct timeval time;
struct timezone tz;			/* XXX */
E 18
I 18
D 21
extern struct timeval mono_time;
E 21
I 21
extern volatile struct timeval mono_time;
E 21
extern struct timeval boottime;
D 21
extern struct timeval time;
E 21
I 21
extern struct timeval runtime;
extern volatile struct timeval time;
E 21
extern struct timezone tz;			/* XXX */
E 18
E 16

I 16
D 18
int hz;					/* clock frequency */
int phz;				/* alternate clock's frequency */
int tick;
int lbolt;				/* once a second sleep address */
int realitexpire();
E 18
I 18
D 20
extern int hz;				/* clock frequency */
extern int phz;				/* alternate clock's frequency */
extern int tick;			/* usec per tick */
E 20
I 20
extern int tick;			/* usec per tick (1000000 / hz) */
extern int hz;				/* system clock's frequency */
extern int stathz;			/* statistics clock's frequency */
E 20
extern int profhz;			/* profiling clock's frequency */
extern int lbolt;			/* once a second sleep address */
D 21
extern int realitexpire();
E 21
E 18
D 23

E 16
I 14
D 18
fixpt_t	averunnable[3];
E 18
I 18
D 19
struct clockinfo {
	int hz;		/* clock frequency */
	int tick;	/* micro-seconds per hz tick */
	int phz;	/* alternate clock frequency */
	int profhz;	/* profiling clock frequency */
};

E 19
D 22
struct loadavg {
	fixpt_t ldavg[3];
	long fscale;
};
extern struct loadavg averunnable;
E 22
E 18
D 15
#ifdef COMPAT_43
E 15
I 15
#if defined(COMPAT_43) && (defined(vax) || defined(tahoe))
E 15
E 14
I 7
double	avenrun[3];
I 14
D 22
#endif /* COMPAT_43 */
E 22
I 22
#endif
E 22
E 14

E 7
#ifdef GPROF
D 16
extern	int profiling;
extern	char *s_lowpc;
extern	u_long s_textsize;
extern	u_short *kcount;
E 16
I 16
D 18
u_long s_textsize;
int profiling;
u_short *kcount;
char *s_lowpc;
E 18
I 18
D 21
extern u_long s_textsize;
E 21
extern int profiling;
extern u_short *kcount;
D 21
extern char *s_lowpc;
E 21
E 18
E 16
#endif
E 23
E 4
E 3
E 2
E 1
