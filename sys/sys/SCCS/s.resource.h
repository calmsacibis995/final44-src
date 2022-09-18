h49774
s 00001/00001/00098
d D 8.4 95/01/09 18:16:15 cgd 18 17
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00004/00004/00095
d D 8.3 94/07/10 22:54:42 bostic 17 16
c changes for 64-bit machines
e
s 00003/00003/00096
d D 8.2 94/01/04 16:16:44 bostic 16 15
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00097
d D 8.1 93/06/14 15:48:49 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00098
d D 7.10 93/06/14 15:48:23 bostic 14 12
c from Ralph, lint
e
s 00002/00002/00097
d R 8.1 93/06/02 19:55:02 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00099
d D 7.9 93/05/25 17:48:44 bostic 12 11
c __{get,set}rlimit => {get,set}rlimit
e
s 00011/00002/00090
d D 7.8 93/04/27 12:26:05 bostic 11 10
c move struct loadavg and averunnable variable from kernel.h to resource.h
e
s 00001/00001/00091
d D 7.7 92/12/01 13:42:17 mckusick 10 9
c RLIMIT_OFILE => RLIMIT_NOFILE for compatibility with other UNIX's
e
s 00009/00002/00083
d D 7.6 92/05/31 21:20:30 mckusick 9 8
c resource limts now take quads; 
c use new entry points for programs that use include this file with the prototypes
e
s 00016/00001/00069
d D 7.5 91/03/17 15:34:08 karels 8 7
c more-or-less working with new proc & user structs
e
s 00005/00000/00065
d D 7.4 91/02/05 17:03:58 bostic 7 6
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00064
d D 7.3 90/06/28 22:00:23 bostic 6 5
c new copyright notice
e
s 00016/00005/00059
d D 7.2 89/02/20 10:57:02 bostic 5 4
c int->long (lint complains if you assign RLIM_INFINITY);
c add Berkeley copyright notice
e
s 00001/00001/00063
d D 7.1 86/06/04 23:27:23 mckusick 4 3
c 4.3BSD release version
e
s 00007/00001/00057
d D 6.2 85/06/08 15:06:30 mckusick 3 2
c Add copyright
e
s 00000/00000/00058
d D 6.1 83/07/29 06:13:50 sam 2 1
c 4.2 distribution
e
s 00058/00000/00000
d D 4.1 83/02/10 21:42:10 sam 1 0
c date and time created 83/02/10 21:42:10 by sam
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
/*
D 4
 * Copyright (c) 1982 Regents of the University of California.
E 4
I 4
D 5
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 15
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
E 5
 *
I 5
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
E 5
 *	%W% (Berkeley) %G%
 */
E 3

I 7
D 16
#ifndef _RESOURCE_H_
#define	_RESOURCE_H_
E 16
I 16
#ifndef _SYS_RESOURCE_H_
#define	_SYS_RESOURCE_H_
E 16

E 7
/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	-20
#define	PRIO_MAX	20

#define	PRIO_PROCESS	0
#define	PRIO_PGRP	1
#define	PRIO_USER	2

/*
 * Resource utilization information.
 */

#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1

struct	rusage {
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
	long	ru_maxrss;		/* max resident set size */
#define	ru_first	ru_ixrss
	long	ru_ixrss;		/* integral shared memory size */
	long	ru_idrss;		/* integral unshared data " */
	long	ru_isrss;		/* integral unshared stack " */
	long	ru_minflt;		/* page reclaims */
	long	ru_majflt;		/* page faults */
	long	ru_nswap;		/* swaps */
	long	ru_inblock;		/* block input operations */
	long	ru_oublock;		/* block output operations */
	long	ru_msgsnd;		/* messages sent */
	long	ru_msgrcv;		/* messages received */
	long	ru_nsignals;		/* signals received */
	long	ru_nvcsw;		/* voluntary context switches */
	long	ru_nivcsw;		/* involuntary " */
#define	ru_last		ru_nivcsw
};

/*
 * Resource limits
 */
#define	RLIMIT_CPU	0		/* cpu time in milliseconds */
#define	RLIMIT_FSIZE	1		/* maximum file size */
#define	RLIMIT_DATA	2		/* data size */
#define	RLIMIT_STACK	3		/* stack size */
#define	RLIMIT_CORE	4		/* core file size */
#define	RLIMIT_RSS	5		/* resident set size */
I 8
#define	RLIMIT_MEMLOCK	6		/* locked-in-memory address space */
#define	RLIMIT_NPROC	7		/* number of processes */
D 10
#define	RLIMIT_OFILE	8		/* number of open files */
E 10
I 10
#define	RLIMIT_NOFILE	8		/* number of open files */
E 10
E 8

D 8
#define	RLIM_NLIMITS	6		/* number of resource limits */
E 8
I 8
#define	RLIM_NLIMITS	9		/* number of resource limits */
E 8

D 9
#define	RLIM_INFINITY	0x7fffffff
E 9
I 9
D 14
#define	RLIM_INFINITY	(((quad_t)1 << 63) - 1)
E 14
I 14
#define	RLIM_INFINITY	(((u_quad_t)1 << 63) - 1)
E 14
E 9

D 9
struct rlimit {
E 9
I 9
struct orlimit {
E 9
D 5
	int	rlim_cur;		/* current (soft) limit */
	int	rlim_max;		/* maximum value for rlim_cur */
E 5
I 5
D 17
	long	rlim_cur;		/* current (soft) limit */
	long	rlim_max;		/* maximum value for rlim_cur */
E 17
I 17
	int32_t	rlim_cur;		/* current (soft) limit */
	int32_t	rlim_max;		/* maximum value for rlim_cur */
E 17
E 5
};
I 7

I 9
struct rlimit {
	quad_t	rlim_cur;		/* current (soft) limit */
	quad_t	rlim_max;		/* maximum value for rlim_cur */
};

E 9
I 8
D 11
#ifndef KERNEL
E 11
I 11
/* Load average structure. */
struct loadavg {
D 17
	fixpt_t ldavg[3];
	long fscale;
E 17
I 17
	fixpt_t	ldavg[3];
D 18
	int32_t fscale;
E 18
I 18
	long	fscale;
E 18
E 17
};

#ifdef KERNEL
extern struct loadavg averunnable;

#else
E 11
#include <sys/cdefs.h>

__BEGIN_DECLS
int	getpriority __P((int, int));
I 9
D 12
#define getrlimit __getrlimit
E 12
E 9
int	getrlimit __P((int, struct rlimit *));
int	getrusage __P((int, struct rusage *));
int	setpriority __P((int, int, int));
I 9
D 12
#define setrlimit __setrlimit
E 12
E 9
int	setrlimit __P((int, const struct rlimit *));
__END_DECLS

D 11
#endif	/* !KERNEL */
E 11
I 11
#endif	/* KERNEL */
E 11
E 8
D 16
#endif	/* !_RESOURCE_H_ */
E 16
I 16
#endif	/* !_SYS_RESOURCE_H_ */
E 16
E 7
E 1
