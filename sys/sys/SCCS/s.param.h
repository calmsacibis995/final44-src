h24809
s 00001/00001/00189
d D 8.3 95/04/04 11:04:43 mckusick 99 98
c update BSD
e
s 00005/00000/00185
d D 8.2 94/01/21 17:25:15 bostic 98 97
c add USL's copyright notice
e
s 00002/00002/00183
d D 8.1 93/06/02 19:54:39 bostic 97 96
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00183
d D 7.28 93/04/29 17:40:06 bostic 96 95
c update to 4.4BSD release values (32 days to go...)
e
s 00001/00001/00184
d D 7.27 92/12/09 14:16:49 margo 95 94
c up MAXBSIZE to MAXPHYS for clustering
e
s 00002/00005/00183
d D 7.26 92/07/12 18:29:53 bostic 94 93
c MIN/MAX only defined for user programs
e
s 00001/00001/00187
d D 7.25 92/06/29 13:46:40 bostic 93 92
c up the BSD #define
e
s 00000/00001/00188
d D 7.24 91/12/19 12:41:20 mckusick 92 91
c endian.h is now included in types.h
e
s 00001/00001/00188
d D 7.23 91/05/06 16:02:16 karels 91 90
c put PZERO between PVFS and PSOCK as it had been
e
s 00057/00071/00132
d D 7.22 91/04/28 12:29:51 bostic 90 89
c minor reorganization, cleanup, delete any AT&T stuff; Berkeley copyright
e
s 00028/00028/00175
d D 7.21 91/04/20 11:19:28 karels 89 88
c bump bsd; rationalize priorities (mod 4 matters); cleanups
e
s 00026/00011/00177
d D 7.20 91/03/17 15:34:04 karels 88 87
c more-or-less working with new proc & user structs
e
s 00004/00014/00184
d D 7.19 90/12/16 16:42:14 bostic 87 86
c kernel reorg
e
s 00001/00000/00197
d D 7.18 90/12/05 15:29:53 mckusick 86 85
c update for new VM
e
s 00001/00001/00196
d D 7.17 90/06/28 14:58:53 karels 85 84
c update BSD date
e
s 00005/00002/00192
d D 7.16 90/06/25 10:31:07 karels 84 83
c move MAXCOMLEN, MAXLOGNAME to param.h from proc.h; delete CANBSIZ
e
s 00000/00001/00194
d D 7.15 90/06/22 17:17:19 karels 83 82
c remove PABORT
e
s 00000/00003/00195
d D 7.14 90/05/02 10:08:26 mckusick 82 81
c NMOUNT is no more
e
s 00015/00014/00181
d D 7.13 90/03/25 12:53:40 karels 81 80
c add PRIMASK, PCATCH for tsleep, PSOCK for socket operations;
c remove unused
e
s 00027/00040/00163
d D 7.12 90/02/22 20:26:24 karels 80 79
c move ISSIG to signal.h (and rename to CURSIG);
c move filesys stuff together under existing heading;
c use inline min/max instead of macros; delete DEV_BSIZE/BLKDEV_IOSIZE
c comments (constants aren't here, and comments are wrong)
e
s 00010/00007/00193
d D 7.11 89/08/26 16:36:48 karels 79 78
c posix signals, new ignored signal treatment
e
s 00014/00000/00186
d D 7.10 89/05/29 12:30:14 mckusick 78 77
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00001/00000/00185
d D 7.9 89/05/09 16:13:53 mckusick 77 76
c merge in vnodes
e
s 00001/00001/00184
d D 7.8 89/04/25 11:01:01 mckusick 76 75
c ../machine => machine
e
s 00007/00005/00178
d D 7.7 89/02/16 14:09:59 bostic 75 74
c add syslimits.h for POSIX 1003.1; included by include/limits.h
e
s 00003/00002/00180
d D 7.6 88/10/18 15:23:49 marc 74 73
c new terminal driver
e
s 00018/00000/00164
d D 7.5 87/06/05 17:52:07 mckusick 73 72
c add basic parameters for kernel malloc
e
s 00001/00000/00163
d D 7.4 87/03/03 22:23:57 bostic 72 71
c added MAXINTERP, max length of interpreter file name
e
s 00019/00048/00144
d D 7.3 87/01/16 17:28:06 karels 71 70
c mv machdep to machparam.h
e
s 00007/00000/00185
d D 7.2 86/11/03 12:04:00 karels 70 68
c tahoe support
e
s 00015/00000/00185
d R 7.2 86/10/13 23:03:00 karels 69 68
c merge in tahoe system; defines for byte order
e
s 00001/00001/00184
d D 7.1 86/06/04 23:25:55 mckusick 68 67
c 4.3BSD release version
e
s 00001/00001/00184
d D 6.16 86/02/19 22:35:38 karels 67 66
c NOGROUP needs to fit in a u_short
e
s 00003/00003/00182
d D 6.15 85/10/25 15:08:14 karels 66 65
c define BSD4_3 as 1, so #if works; define BSD as an integer;
c increase MAXUPRC for window system users
e
s 00004/00002/00181
d D 6.14 85/09/18 20:31:13 karels 65 63
c increase size of clists
e
s 00004/00002/00181
d R 6.14 85/09/18 12:25:36 karels 64 63
c increase size of clists
e
s 00003/00006/00180
d D 6.13 85/09/09 11:02:19 bloom 63 62
c delete interleaved disk macros, add BSD defines
e
s 00010/00012/00176
d D 6.12 85/06/25 14:20:10 karels 62 60
c remove dependency of types.h on param.h
e
s 00012/00014/00174
d R 6.12 85/06/25 13:18:28 karels 61 60
c remove dependency of types.h on param.h; increase CBSIZE
e
s 00010/00010/00178
d D 6.11 85/06/17 21:56:15 karels 60 59
c add macros for select masks; mv param's include of types.h
c after defn. of howmany; allow larger hostnames (domains coming!)
e
s 00007/00001/00181
d D 6.10 85/06/08 15:03:20 mckusick 59 58
c Add copyright
e
s 00005/00000/00177
d D 6.9 85/06/07 15:29:12 bloom 58 57
c add MAXHOSTNAMELEN
e
s 00001/00001/00176
d D 6.8 85/05/05 23:26:57 karels 57 56
c NOFILE -> 64
e
s 00001/00001/00176
d D 6.7 85/02/15 18:51:55 karels 56 55
c increase NGROUPS
e
s 00004/00005/00173
d D 6.6 84/12/20 15:45:17 karels 55 54
c increase NOFILE, NMOUNT, NCARGS
e
s 00002/00002/00176
d D 6.5 84/08/29 09:56:40 karels 54 53
c rename machine/param.h
e
s 00002/00002/00176
d D 6.4 84/08/28 17:29:30 bloom 53 52
c Change include paths.  No more ../h
e
s 00003/00005/00175
d D 6.3 84/07/31 17:49:38 karels 52 51
c umask moved here from login; fix the comments
e
s 00002/00001/00178
d D 6.2 83/09/24 22:35:33 karels 51 50
c MSWAPX is NMOUNT; document limit on NMOUNT
e
s 00000/00000/00179
d D 6.1 83/07/29 06:13:20 sam 50 49
c 4.2 distribution
e
s 00001/00001/00178
d D 4.35 83/06/10 15:21:50 root 49 48
c botched parens on ISSIG
e
s 00008/00005/00171
d D 4.34 83/06/02 15:52:22 sam 48 47
c new signals
e
s 00006/00000/00170
d D 4.33 83/05/21 16:00:21 sam 47 46
c DEV_BSHIFT and friends
e
s 00001/00001/00169
d D 4.32 83/05/18 02:42:06 sam 46 45
c sun changes
e
s 00002/00000/00168
d D 4.31 83/03/31 13:33:46 sam 45 44
c add definition of NOGROUP
e
s 00001/00001/00167
d D 4.30 83/02/21 22:19:57 sam 44 43
c cut down block i/o size so we don't have to round disk partitions
e
s 00001/00001/00167
d D 4.29 83/02/10 17:00:50 sam 43 42
c put it back, not worth it
e
s 00001/00001/00167
d D 4.28 83/02/10 16:11:16 sam 42 41
c group id's are shorts, not ints
e
s 00002/00000/00166
d D 4.27 83/01/17 15:49:29 sam 41 40
c from sun
e
s 00004/00010/00162
d D 4.26 82/12/17 12:11:19 sam 40 39
c sun merge
e
s 00002/00002/00170
d D 4.25 82/10/31 16:43:07 root 39 38
c #ifdef not #if vax|sun
e
s 00000/00000/00172
d D 4.24 82/10/31 16:25:21 root 38 37
c split into machine dependents in ../vax ../sun
e
s 00023/00058/00149
d D 4.23 82/10/31 16:08:58 root 37 36
c split off machine independent parts; fix bdbtofsb macro
e
s 00003/00000/00204
d D 4.22 82/10/10 17:12:38 root 36 35
c header file cleanup while moving vax files to their own directory
e
s 00001/00003/00203
d D 4.21 82/08/24 17:44:59 root 35 34
c NGROUPS -> 8, u.u_groups
e
s 00001/00000/00205
d D 4.20 82/08/08 18:13:49 sam 34 33
c added PLOCK for flock call
e
s 00008/00000/00197
d D 4.19 82/07/15 20:50:22 kre 33 32
c sam: add bdbtofsb() macro "block device block to file system block"
e
s 00007/00000/00190
d D 4.18 82/06/11 23:07:57 mckusick 32 31
c add BLKDEV_IOSIZE for use by character devices
e
s 00054/00055/00136
d D 4.17 82/04/19 19:26:25 mckusic 31 30
c merge in the new file system
e
s 00001/00000/00190
d D 4.16 82/03/30 13:11:00 root 30 29
c add DEV_BSIZE to make ndir.h compile
e
s 00001/00000/00189
d D 4.15 82/02/15 13:28:48 wnj 29 28
c new group stuff
e
s 00005/00001/00184
d D 4.14 81/11/26 11:53:53 wnj 28 27
c before carry to arpavax
e
s 00000/00000/00185
d D 4.13 81/11/18 15:46:55 wnj 27 26
c more cleanup
e
s 00000/00001/00185
d D 4.12 81/06/11 15:41:38 wnj 26 25
c drop spurious CLKTICK
e
s 00000/00001/00186
d D 4.11 81/05/05 15:36:21 root 25 24
c remove spurios MAXNBUF
e
s 00010/00024/00177
d D 4.10 81/03/08 18:35:50 wnj 24 23
c now includes types.h and defines DELAY
e
s 00001/00000/00200
d D 4.9 81/02/27 02:38:20 wnj 23 22
c dynamic alloc kernel version
e
s 00007/00027/00193
d D 4.8 81/02/27 00:04:43 wnj 22 21
c remove constants which are no longer needed (dyn alloc)
e
s 00007/00002/00213
d D 4.7 81/02/23 20:36:07 wnj 21 20
c move stuff from vmparam.h to param.h and UPAGES temporarily 8
e
s 00001/00001/00214
d D 4.6 81/02/19 21:41:40 wnj 20 19
c %G%->%E%
e
s 00001/00001/00214
d D 4.5 81/01/29 09:13:06 kre 19 18
c UPAGES back to 6, that wasn't the problem
e
s 00001/00001/00214
d D 4.4 81/01/28 12:09:17 wnj 18 17
c UPAGES 8
e
s 00001/00001/00214
d D 4.3 80/12/17 11:48:10 wnj 17 16
c restore keywords
e
s 00014/00004/00201
d D 4.2 80/12/17 11:46:23 wnj 16 13
c combined 750/780
e
s 00004/00000/00182
d R 4.3 80/11/09 17:12:00 bill 15 14
c include types.h depending on #ifdef KERNEL
e
s 00001/00024/00181
d R 4.2 80/11/09 17:10:59 bill 14 13
c include <sys/types.h>
e
s 00000/00000/00205
d D 4.1 80/11/09 17:01:20 bill 13 12
c stamp for 4bsd
e
s 00002/00002/00203
d D 3.12 80/10/19 22:09:01 bill 12 11
c NBUF=128
e
s 00001/00001/00204
d D 3.11 80/09/14 22:55:19 bill 11 10
c ncargs -> 10240
e
s 00005/00000/00200
d D 3.10 80/08/08 23:19:28 bill 10 9
c add types u_*
e
s 00001/00001/00199
d D 3.9 80/07/19 20:15:27 bill 9 8
c NBUF->62
e
s 00003/00003/00197
d D 3.8 80/07/18 14:50:15 bill 8 7
c huge NFILE, NINODE, NPROC
e
s 00002/00001/00198
d D 3.7 80/07/11 08:23:21 bill 7 6
c NMOUNT=15, declare MSWAPX
e
s 00001/00001/00198
d D 3.6 80/06/07 02:59:22 bill 6 5
c %H%->%G%
e
s 00003/00020/00196
d D 3.5 80/05/15 17:17:31 bill 5 4
c more signals
e
s 00000/00009/00216
d D 3.4 80/05/08 10:31:07 bill 4 3
c remove VOID crap
e
s 00000/00002/00225
d D 3.3 80/04/30 17:22:23 bill 3 2
c remove BSLOP
e
s 00008/00001/00219
d D 3.2 80/04/14 18:25:05 bill 2 1
c added TS_OK, TS_TIME, TS_SIG
e
s 00220/00000/00000
d D 3.1 80/04/09 16:24:43 bill 1 0
c date and time created 80/04/09 16:24:43 by bill
e
u
U
t
T
I 31
D 35
/* "@(#)param.h 2.1 3/25/82" */

E 35
E 31
I 1
D 6
/*	%M%	%I%	%H%	*/
E 6
I 6
D 16
/*	%M%	%I%	%G%	*/
E 16
I 16
D 17
/*	param.h	4.1	11/9/80	*/
E 17
I 17
D 20
/*	%M%	%I%	%G%	*/
E 20
I 20
D 59
/*	%M%	%I%	%E%	*/
E 59
I 59
D 90
/*
D 68
 * Copyright (c) 1982 Regents of the University of California.
E 68
I 68
D 79
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 79
I 79
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 79
E 68
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 90
I 90
/*-
D 97
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 97
I 97
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 98
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 98
E 97
E 90
 *
I 90
 * %sccs.include.redist.c%
 *
E 90
 *	%W% (Berkeley) %G%
 */
E 59
E 20
E 17
E 16
E 6

I 63
D 66
#define	BSD	4.3
#define BSD4_3
E 66
I 66
D 74
#define	BSD	43		/* 4.3 * 10, as cpp doesn't do floats */
E 74
I 74
D 79
#define	BSD	198810		/* system version  (year & month) */
E 79
I 79
D 80
#define	BSD	198908		/* system version  (year & month) */
E 80
I 80
D 81
#define	BSD	199002		/* system version (year & month) */
E 81
I 81
D 85
#define	BSD	199003		/* system version (year & month) */
E 85
I 85
D 89
#define	BSD	199006		/* June, 1990 system version (year & month) */
E 89
I 89
D 93
#define	BSD	199103		/* March, 1991 system version (year & month) */
E 93
I 93
D 96
#define	BSD	199207		/* System version (year & month). */
E 96
I 96
D 99
#define	BSD	199306		/* System version (year & month). */
E 99
I 99
#define	BSD	199506		/* System version (year & month). */
E 99
E 96
E 93
E 89
E 85
E 81
E 80
E 79
E 74
#define BSD4_3	1
I 81
D 96
#define BSD4_4	0.5
E 96
I 96
#define BSD4_4	1
E 96
E 81
E 66

I 75
D 90
#include <sys/syslimits.h>
E 90
I 90
#ifndef NULL
#define	NULL	0
#endif
E 90

I 89
#ifndef LOCORE
#include <sys/types.h>
#endif

E 89
E 75
E 63
/*
D 22
 * tunable variables
E 22
I 22
D 37
 * Tunable variables which do not usually vary per system.
E 22
 *
D 12
 * NB: NBUF is well known in locore.s
E 12
I 12
D 22
 * NB: NBUF must be less than MAXNBUF in locore.s.
E 22
I 22
 * The sizes of most system tables are configured
 * into each system description.  The file system buffer
 * cache size is assigned based on available memory.
 * The tables whose sizes don't vary often are given here.
E 37
I 37
D 46
 * Macine type dependent parameters.
E 46
I 46
D 71
 * Machine type dependent parameters.
E 46
E 37
E 22
E 12
 */
I 37
D 39
#if vax
E 39
I 39
D 40
#ifdef vax
E 39
#include "../vax/param.h"
E 40
I 40
#ifdef KERNEL
D 54
#include "../machine/param.h"
E 54
I 54
#include "../machine/machparam.h"
E 54
#else
D 54
#include <machine/param.h>
E 54
I 54
#include <machine/machparam.h>
E 54
E 40
#endif
D 39
#if sun
E 39
I 39
D 40
#ifdef sun
E 39
#include "../sun/param.h"
#endif
E 40
E 37

I 37
#define	NPTEPG		(NBPG/(sizeof (struct pte)))

/*
E 71
D 89
 * Machine-independent constants
E 89
I 89
D 90
 * Machine-independent constants (some used in following include files)
E 90
I 90
 * Machine-independent constants (some used in following include files).
 * Redefined constants are from POSIX 1003.1 limits file.
 *
 * MAXCOMLEN should be >= sizeof(ac_comm) (see <acct.h>)
 * MAXLOGNAME should be >= UT_NAMESIZE (see <utmp.h>)
E 90
E 89
 */
E 37
I 23
D 25
#define	MAXNBUF	128
E 25
E 23
I 16
D 22
#ifdef notdef
#define	NBUF	64		/* size of buffer cache */
#define	NINODE	200		/* number of in core inodes */
#define	NFILE	175		/* number of in core file structures */
#define	NMOUNT	7		/* number of mountable file systems */
#define	MSWAPX	7		/* pseudo mount table index for swapdev */
#define	NPROC	125		/* max number of processes */
#define	NTEXT	40		/* max number of pure texts */
#define	NCLIST	250		/* max total clist size */
#endif
E 16
D 9
#define	NBUF	48		/* size of buffer cache */
E 9
I 9
D 12
#define	NBUF	62		/* size of buffer cache */
E 12
I 12
#define	NBUF	128		/* size of buffer cache */
E 12
E 9
D 8
#define	NINODE	250		/* number of in core inodes */
#define	NFILE	225		/* number of in core file structures */
E 8
I 8
#define	NINODE	400		/* number of in core inodes */
#define	NFILE	350		/* number of in core file structures */
E 22
E 8
D 7
#define	NMOUNT	8		/* number of mountable file systems */
E 7
I 7
D 55
#define	NMOUNT	15		/* number of mountable file systems */
E 55
I 55
D 80
#define	NMOUNT	20		/* number of mountable file systems */
E 80
I 80
D 81
#define	NMOUNT	30		/* number of mountable file systems */
E 81
I 81
D 82
#define	NMOUNT		30		/* number of mountable file systems */
E 81
E 80
E 55
D 51
#define	MSWAPX	15		/* pseudo mount table index for swapdev */
E 51
I 51
D 52
/* NMOUNT must be <= 15 unless c_mdev (cmap.h) is expanded */
E 52
I 52
/* NMOUNT must be <= 255 unless c_mdev (cmap.h) is expanded */
E 52
D 81
#define	MSWAPX	NMOUNT		/* pseudo mount table index for swapdev */
E 51
I 16
D 22
#define	NPROC	250		/* max number of processes */
#define	NTEXT	60		/* max number of pure texts */
#define	NCLIST	500		/* max total clist size */
E 22
E 16
E 7
D 66
#define	MAXUPRC	25		/* max processes per user */
E 66
I 66
D 75
#define	MAXUPRC	40		/* max processes per user */
E 66
D 37
#define	SSIZE	4		/* initial stack size (*512 bytes) */
#define	SINCR	4		/* increment of stack (*512 bytes) */
E 37
D 55
#define	NOFILE	20		/* max open files per process */
I 22
/* NOFILE MUST NOT BE >= 31; SEE pte.h */
E 55
I 55
D 57
#define	NOFILE	48		/* max open files per process */
E 57
I 57
#define	NOFILE	64		/* max open files per process */
E 75
I 75
#define	MAXUPRC	CHILD_MAX	/* max processes per user */
#define	NOFILE	OPEN_MAX	/* max open files per process */
E 75
E 57
E 55
E 22
D 80
#define	CANBSIZ	256		/* max size of typewriter line */
E 80
I 80
#define	CANBSIZ	256		/* max size of tty input line */
E 80
D 22
#define	SMAPSIZ	(4*NPROC)	/* size of swap allocation area */
#define	NCALL	40		/* max simultaneous time callouts */
D 8
#define	NPROC	150		/* max number of processes */
E 8
I 8
D 16
#define	NPROC	250		/* max number of processes */
E 8
#define	NTEXT	60		/* max number of pure texts */
#define	NCLIST	500		/* max total clist size */
E 16
#define	HZ	60		/* Ticks/second of the clock */
#define	TIMEZONE (8*60)		/* Minutes westward from Greenwich */
#define	DSTFLAG	1		/* Daylight Saving Time applies in this locality */
#define	MSGBUFS	128		/* Characters saved from error messages */
E 22
D 11
#define	NCARGS	5120		/* # characters in exec arglist */
E 11
I 11
D 55
#define	NCARGS	10240		/* # characters in exec arglist */
E 55
I 55
D 75
#define	NCARGS	20480		/* # characters in exec arglist */
E 75
I 75
#define	NCARGS	ARG_MAX		/* # characters in exec arglist */
E 75
I 72
#define	MAXINTERP	32	/* maximum interpreter file name length */
E 72
E 55
I 37
D 42
#define	NGROUPS	8		/* max number groups */
E 42
I 42
D 43
#define	NGROUPS	16		/* max number groups */
E 43
I 43
D 56
#define	NGROUPS	8		/* max number groups */
E 56
I 56
D 75
#define	NGROUPS	16		/* max number groups */
E 75
I 75
#define	NGROUPS	NGROUPS_MAX	/* max number groups */
E 75
I 71
#define MAXHOSTNAMELEN	64	/* maximum hostname size */
E 81
I 81
#define	MSWAPX		NMOUNT		/* pseudo mount index for swapdev */
E 82
D 90
#define	MAXUPRC		CHILD_MAX	/* max processes per user */
#define	NOFILE		OPEN_MAX	/* max open files per process */
D 84
#define	CANBSIZ		256		/* max size of tty input line */
E 84
#define	NCARGS		ARG_MAX		/* # characters in exec arglist */
E 90
I 90
#include <sys/syslimits.h>

#define	MAXCOMLEN	16		/* max command name remembered */
E 90
#define	MAXINTERP	32		/* max interpreter file name length */
I 90
#define	MAXLOGNAME	12		/* max login name length */
#define	MAXUPRC		CHILD_MAX	/* max simultaneous processes */
#define	NCARGS		ARG_MAX		/* max bytes for an exec function */
E 90
#define	NGROUPS		NGROUPS_MAX	/* max number groups */
D 84
#define MAXHOSTNAMELEN	64		/* maximum hostname size */
E 84
I 84
D 90
#define MAXHOSTNAMELEN	256		/* maximum hostname size */
#define	MAXCOMLEN	16		/* maximum command name remembered */
	/* MAXCOMLEN should be >= sizeof(ac_comm) (acct.h)  */
#define	MAXLOGNAME	12		/* maximum login name length */
	/* MAXLOGNAME must be >= UT_NAMESIZE (<utmp.h>) */
E 84
E 81
E 71
E 56
E 43
E 42
E 37
I 22

E 90
I 90
#define	NOFILE		OPEN_MAX	/* max open files per process */
E 90
I 45
D 67
#define	NOGROUP	-1		/* marker for empty group set member */
E 67
I 67
D 81
#define	NOGROUP	65535		/* marker for empty group set member */
E 81
I 81
#define	NOGROUP		65535		/* marker for empty group set member */
I 90
#define MAXHOSTNAMELEN	256		/* max hostname size */
E 90
E 81
E 67

E 45
E 22
E 11
D 90
/*
D 37
 * priorities
 * probably should not be
 * altered too much
E 37
I 37
D 88
 * Priorities
E 88
I 88
D 89
 * Priorities.  Note that with 32 run queues,
 * differences less than 4 are insignificant.
E 88
E 37
 */
D 37

E 37
#define	PSWP	0
I 86
D 88
#define	PVM	1
E 86
#define	PINOD	10
#define	PRIBIO	20
I 77
#define	PVFS	22
E 77
D 81
#define	PRIUBA	24
E 81
#define	PZERO	25
D 81
#define	PPIPE	26
E 81
I 81
#define	PSOCK	26
E 81
#define	PWAIT	30
I 34
#define	PLOCK	35
E 88
I 88
#define	PVM	4
#define	PINOD	8
#define	PRIBIO	16
#define	PVFS	20
#define	PSOCK	24
#define	PZERO	25		/* No longer magic, shouldn't be here XXX */
#define	PWAIT	32
#define	PLOCK	36
E 88
E 34
D 81
#define	PSLEP	40
E 81
I 81
#define	PPAUSE	40
E 81
#define	PUSER	50
I 88
#define	MAXPRI	127		/* priorities range from 0 through MAXPRI */

E 88
I 81
#define	PRIMASK	0x0ff
#define	PCATCH	0x100		/* or'd with pri for tsleep to check signals */
D 83
#define	PABORT	0x200		/* or'd with pri for tsleep to longjmp XXX */
E 83
E 81

D 55
#define	NZERO	20
E 55
I 55
D 88
#define	NZERO	0
E 88
I 88
#define	NZERO	0		/* default "nice" */
E 88
E 55

I 71
D 87
#ifndef KERNEL
#include	<sys/types.h>
#else
E 87
#ifndef LOCORE
D 87
#include	"types.h"
E 87
I 87
D 88
#include	<sys/types.h>
E 88
I 88
#include <sys/types.h>
#endif

/*
E 89
 * More types and definitions used throughout the kernel
 */
E 90
I 90
/* More types and definitions used throughout the kernel. */
E 90
#ifdef KERNEL
#include <sys/cdefs.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ucred.h>
#include <sys/uio.h>
E 88
E 87
#endif
D 87
#endif
E 87

E 71
D 90
/*
D 37
 * signals
 * dont change
E 37
I 37
 * Signals
E 37
 */
E 90
I 90
/* Signals. */
E 90
D 37

E 37
D 5
#define	NSIG	17
/*
 * No more than 16 signals (1-16) because they are
 * stored in bits in a word.
 */
#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt (rubout) */
#define	SIGQUIT	3	/* quit (FS) */
#define	SIGINS	4	/* illegal instruction */
#define	SIGTRC	5	/* trace or breakpoint */
#define	SIGIOT	6	/* iot */
#define	SIGEMT	7	/* emt */
#define	SIGFPT	8	/* floating exception */
#define	SIGKIL	9	/* kill, uncatchable termination */
#define	SIGBUS	10	/* bus error */
#define	SIGSEG	11	/* segmentation violation */
#define	SIGSYS	12	/* bad system call */
#define	SIGPIPE	13	/* end of pipe */
#define	SIGCLK	14	/* alarm clock */
D 2
#define	SIGTRM	15	/* Catchable termination */
E 2
I 2
#define	SIGTRM	15	/* catchable termination */
E 5
I 5
D 48
#ifndef	NSIG
E 48
I 48
D 87
#ifdef KERNEL
D 53
#include "../h/signal.h"
E 53
I 53
#include "signal.h"
E 53
D 79
#else
E 48
#include <signal.h>
#endif
E 79
E 5
D 80

I 36
D 48
#define	ISSIG(p)	((p)->p_sig && \
	((p)->p_flag&STRC || ((p)->p_sig &~ (p)->p_ignsig)) && issig())
E 48
I 48
#define	ISSIG(p) \
D 79
	((p)->p_sig && ((p)->p_flag&STRC || \
D 49
	 ((p)->p_sig &~ ((p)->p_sigignore | (p)->p_sigmask)) && issig()))
E 49
I 49
	 ((p)->p_sig &~ ((p)->p_sigignore | (p)->p_sigmask))) && issig())
E 79
I 79
	((p)->p_sig && \
	    ((p)->p_flag&STRC || ((p)->p_sig &~ (p)->p_sigmask)) && issig())
E 79
E 49
E 48

E 80
I 79
#else
E 87
#include <sys/signal.h>
D 87
#endif
E 87

E 79
I 71
D 90
/*
 * Machine type dependent parameters.
 */
E 90
I 90
/* Machine type dependent parameters. */
E 90
D 87
#ifdef KERNEL
D 76
#include "../machine/machparam.h"
E 76
I 76
#include "machine/machparam.h"
E 76
#else
#include <machine/machparam.h>
#endif
E 87
I 87
#include <machine/param.h>
D 92
#include <machine/endian.h>
E 92
#include <machine/limits.h>
I 89

/*
D 90
 * Priorities.  Note that with 32 run queues,
 * differences less than 4 are insignificant.
E 90
I 90
 * Priorities.  Note that with 32 run queues, differences less than 4 are
 * insignificant.
E 90
 */
#define	PSWP	0
#define	PVM	4
#define	PINOD	8
#define	PRIBIO	16
#define	PVFS	20
I 91
#define	PZERO	22		/* No longer magic, shouldn't be here.  XXX */
E 91
#define	PSOCK	24
D 90
#define	PZERO	25		/* No longer magic, shouldn't be here XXX */
E 90
I 90
D 91
#define	PZERO	25		/* No longer magic, shouldn't be here.  XXX */
E 91
E 90
#define	PWAIT	32
#define	PLOCK	36
#define	PPAUSE	40
#define	PUSER	50
D 90
#define	MAXPRI	127		/* priorities range from 0 through MAXPRI */
E 90
I 90
#define	MAXPRI	127		/* Priorities range from 0 through MAXPRI. */
E 90

#define	PRIMASK	0x0ff
D 90
#define	PCATCH	0x100		/* or'd with pri for tsleep to check signals */
E 90
I 90
#define	PCATCH	0x100		/* OR'd with pri for tsleep to check signals */
E 90

#define	NZERO	0		/* default "nice" */
E 89
E 87

E 71
E 36
D 62
/*
D 37
 * Return values from tsleep().
E 37
I 37
 * Fundamental constants of the implementation.
E 37
 */
D 37
#define	TS_OK	0	/* normal wakeup */
#define	TS_TIME	1	/* timed-out wakeup */
#define	TS_SIG	2	/* asynchronous signal wakeup */
E 2

/*
 * fundamental constants of the implementation--
 * cannot be changed easily.
D 22
 * note: UPAGES is well known in locore.s
E 22
 */

E 37
D 21
#define	NBPW	sizeof(int)	/* number of bytes in an integer */
E 21
I 21
D 48
#define	NBBY		8		/* number of bits in a byte */
#define	NBPW		sizeof(int)	/* number of bytes in an integer */
E 48
I 48
#define	NBBY	8		/* number of bits in a byte */
E 62
D 90
#define	NBPW	sizeof(int)	/* number of bytes in an integer */
E 90
I 90
#define	NBPW	sizeof(int)	/* number of bytes per word (integer) */
E 90
E 48
D 37
#define	NBPG		512
#define	PGOFSET		(NBPG-1)	/* byte offset into page */
#define	PGSHIFT		9		/* LOG2(NBPG) */
E 37
E 21

I 79
D 90
#ifndef NULL
E 79
D 18
#define	UPAGES	6		/* pages of u-area */
E 18
I 18
D 19
#define	UPAGES	8		/* pages of u-area */
E 19
I 19
D 21
#define	UPAGES	6		/* pages of u-area */
E 21
I 21
D 37
#define	UPAGES	8		/* pages of u-area */
E 37
E 21
E 19
E 18
#define	NULL	0
I 79
#endif
E 79
D 52
#define	CMASK	0		/* default mask for file creation */
E 52
I 52
#define	CMASK	022		/* default mask for file creation */
E 52
#define	NODEV	(dev_t)(-1)
E 90
I 90
#define	CMASK	022		/* default file mask: S_IWGRP|S_IWOTH */
#define	NODEV	(dev_t)(-1)	/* non-existent device */
E 90
D 31
#define	ROOTINO	((ino_t)2)	/* i number of all roots */
#define	SUPERB	((daddr_t)1)	/* block number of the super block */
#define	DIRSIZ	14		/* max characters per directory */
E 31
I 29
D 35
#define	NGRPS	256		/* max number groups */
E 35
I 35
D 37
#define	NGROUPS	8		/* max number groups */
E 37
E 35
E 29

/*
 * Clustering of hardware pages on machines with ridiculously small
 * page sizes is done here.  The paging subsystem deals with units of
D 52
 * CLSIZE pte's describing NBPG (from vm.h) pages each... BSIZE must
 * be CLSIZE*NBPG in the current implementation, that is the paging subsystem
 * deals with the same size blocks that the file system uses.
E 52
I 52
D 71
 * CLSIZE pte's describing NBPG (from vm.h) pages each.
E 71
I 71
 * CLSIZE pte's describing NBPG (from machine/machparam.h) pages each.
E 71
E 52
D 90
 *
 * NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE
E 90
D 22
 *
 * NB: CLSIZE is well known in locore.s.
E 22
 */
D 28
#define	CLSIZE	2
E 28
I 28
D 37
#define	CLSIZE		2
E 37
#define	CLBYTES		(CLSIZE*NBPG)
E 28
I 21
#define	CLOFSET		(CLSIZE*NBPG-1)	/* for clusters, like PGOFSET */
I 28
#define	claligned(x)	((((int)(x))&CLOFSET)==0)
#define	CLOFF		CLOFSET
D 37
#define	CLSHIFT		(PGSHIFT+1)
E 37
I 37
#define	CLSHIFT		(PGSHIFT+CLSIZELOG2)
E 37
E 28
E 21

I 37
#if CLSIZE==1
#define	clbase(i)	(i)
#define	clrnd(i)	(i)
#else
E 37
D 90
/* give the base virtual address (first of CLSIZE) */
E 90
I 90
/* Give the base virtual address (first of CLSIZE). */
E 90
#define	clbase(i)	((i) &~ (CLSIZE-1))
D 37

E 37
D 90
/* round a number of clicks up to a whole cluster */
E 90
I 90
/* Round a number of clicks up to a whole cluster. */
E 90
#define	clrnd(i)	(((i) + (CLSIZE-1)) &~ (CLSIZE-1))
I 37
D 63
#endif
E 37

I 30
D 31
#define DEV_BSIZE 512
E 30
#if CLSIZE==1
#define	BSIZE	512		/* size of secondary block (bytes) */
#define	INOPB	8		/* 8 inodes per block */
#define	BMASK	0777		/* BSIZE-1 */
#define	BSHIFT	9		/* LOG2(BSIZE) */
#define	NMASK	0177		/* NINDIR-1 */
#define	NSHIFT	7		/* LOG2(NINDIR) */
#define	NICINOD	100		/* number of superblock inodes */
#define	NICFREE	50		/* number of superblock free blocks */

#endif

#if CLSIZE==2
#define	BSIZE	1024
#define	INOPB	16
#define	BMASK	01777
#define	BSHIFT	10
#define	NMASK	0377
#define	NSHIFT	8
#define	NICINOD	100
#define	NICFREE	178
#endif

#if CLSIZE==4
#define	BSIZE	2048
#define	INOPB	32
#define	BMASK	03777
#define	BSHIFT	11
#define	NMASK	0777
#define	NSHIFT	9
#define	NICINOD	100
#define	NICFREE	434
#endif

E 31
#ifndef INTRLVE
/* macros replacing interleaving functions */
#define	dkblock(bp)	((bp)->b_blkno)
#define	dkunit(bp)	(minor((bp)->b_dev) >> 3)
E 63
#endif

D 31
/* inumber to disk address and inumber to disk offset */
#define	itod(x)	((daddr_t)((((unsigned)(x)+2*INOPB-1)/INOPB)))
#define	itoo(x)	((int)(((x)+2*INOPB-1)%INOPB))

/* file system blocks to disk blocks and back */
#define	fsbtodb(b)	((b)*CLSIZE)
#define	dbtofsb(b)	((b)/CLSIZE)

D 3
/* BSLOP can be 0 unless you have a TIU/Spider */
#define	BSLOP	0		/* In case some device needs bigger buffers */
E 3
#define	NINDIR	(BSIZE/sizeof(daddr_t))

E 31
D 65
#define	CBSIZE	28		/* number of chars in a clist block */
#define	CROUND	0x1F		/* clist rounding; sizeof(int *) + CBSIZE -1*/
E 65
I 65
D 90
/* CBLOCK is the size of a clist block, must be power of 2 */
#define	CBLOCK	64
D 74
#define	CBSIZE	(CBLOCK - sizeof(struct cblock *))	/* data chars/clist */
E 74
I 74
#define CBQSIZE	(CBLOCK/NBBY)	/* quote bytes/cblock - can do better */
#define	CBSIZE	(CBLOCK - sizeof(struct cblock *) - CBQSIZE) /* data chars/clist */
E 74
#define	CROUND	(CBLOCK - 1)				/* clist rounding */
E 90
I 90
#define	CBLOCK	64		/* Clist block size, must be a power of 2. */
#define CBQSIZE	(CBLOCK/NBBY)	/* Quote bytes/cblock - can do better. */
				/* Data chars/clist. */
#define	CBSIZE	(CBLOCK - sizeof(struct cblock *) - CBQSIZE)
#define	CROUND	(CBLOCK - 1)	/* Clist rounding. */
E 90
E 65
D 26
#define	CLKTICK	(1000000/(HZ))	/* microseconds in a clock tick */
E 26

I 62
D 71
#ifndef KERNEL
#include	<sys/types.h>
#else
#ifndef LOCORE
#include	"types.h"
#endif
#endif

E 71
E 62
D 37
/*
D 31
 * Macros for fast min/max
 */
#define	MIN(a,b) (((a)<(b))?(a):(b))
#define	MAX(a,b) (((a)>(b))?(a):(b))

/*
E 31
 * Some macros for units conversion
 */
/* Core clicks (512 bytes) to segments and vice versa */
#define	ctos(x)	(x)
#define	stoc(x)	(x)

/* Core clicks (512 bytes) to disk blocks */
#define	ctod(x)	(x)

/* clicks to bytes */
#define	ctob(x)	((x)<<9)

/* bytes to clicks */
#define	btoc(x)	((((unsigned)(x)+511)>>9))

E 37
D 24
/* major part of a device */
#define	major(x)	((int)(((unsigned)(x)>>8)&0377))
E 24
I 24
D 60
#ifndef KERNEL
#include	<sys/types.h>
#else
I 41
#ifndef LOCORE
E 41
D 53
#include	"../h/types.h"
E 53
I 53
#include	"types.h"
E 53
I 41
#endif
E 41
#endif
E 24

E 60
D 24
/* minor part of a device */
#define	minor(x)	((int)((x)&0377))

/* make a device number */
#define	makedev(x,y)	((dev_t)(((x)<<8) | (y)))

typedef	struct { int r[1]; } *	physadr;
typedef	int		daddr_t;
typedef	char *		caddr_t;
typedef	unsigned short	ino_t;
typedef	int		swblk_t;
typedef	int		size_t;
typedef	int		time_t;
typedef	int		label_t[14];
typedef	short		dev_t;
typedef	int		off_t;

I 10
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;

E 24
E 10
/*
D 37
 * Machine-dependent bits and macros
 */
#define	UMODE	PSL_CURMOD		/* usermode bits */
#define	USERMODE(ps)	(((ps) & UMODE) == UMODE)

#define	BASEPRI(ps)	(((ps) & PSL_IPL) != 0)
I 24

/*
E 37
D 31
 * Provide about n microseconds of delay
E 31
I 31
 * File system parameters and macros.
 *
D 90
 * The file system is made out of blocks of at most MAXBSIZE units,
 * with smaller units (fragments) only in the last direct block.
 * MAXBSIZE primarily determines the size of buffers in the buffer
 * pool. It may be made larger without any effect on existing
 * file systems; however making it smaller make make some file
 * systems unmountable.
E 90
I 90
 * The file system is made out of blocks of at most MAXBSIZE units, with
 * smaller units (fragments) only in the last direct block.  MAXBSIZE
 * primarily determines the size of buffers in the buffer pool.  It may be
 * made larger without any effect on existing file systems; however making
 * it smaller make make some file systems unmountable.
E 90
D 80
 *
 * Note that the blocked devices are assumed to have DEV_BSIZE
 * "sectors" and that fragments must be some multiple of this size.
I 32
 * Block devices are read in BLKDEV_IOSIZE units. This number must
 * be a power of two and in the range of
 *	DEV_BSIZE <= BLKDEV_IOSIZE <= MAXBSIZE
 * This size has no effect upon the file system, but is usually set
 * to the block size of the root file system, so as to maximize the
 * speed of ``fsck''.
E 80
E 32
 */
D 95
#define	MAXBSIZE	8192
E 95
I 95
#define	MAXBSIZE	MAXPHYS
E 95
I 70
D 71
#if defined(vax) || defined(sun)
E 70
#define	DEV_BSIZE	512
I 47
#define	DEV_BSHIFT	9		/* log2(DEV_BSIZE) */
E 47
I 32
D 44
#define BLKDEV_IOSIZE	4096
E 44
I 44
#define BLKDEV_IOSIZE	2048
I 70
#endif
#if defined(tahoe)
#define	DEV_BSIZE	1024
#define	DEV_BSHIFT	10		/* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE	1024		/* NBPG for physical controllers */
#endif
E 71
E 70
E 44
E 32
#define MAXFRAG 	8
I 47

D 71
#define	btodb(bytes)	 		/* calculates (bytes / DEV_BSIZE) */ \
	((unsigned)(bytes) >> DEV_BSHIFT)
#define	dbtob(db)			/* calculates (db * DEV_BSIZE) */ \
	((unsigned)(db) << DEV_BSHIFT)
E 47

E 71
/*
I 33
D 71
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and will be after we
 * add an entry to cdevsw for that purpose.  For now though
 * just use DEV_BSIZE.
 */
D 37
#define	bdbtofsb(bn)	((bn) / CLSIZE)
E 37
I 37
#define	bdbtofsb(bn)	((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))
E 37

/*
E 71
E 33
D 90
 * MAXPATHLEN defines the longest permissable path length
 * after expanding symbolic links. It is used to allocate
 * a temporary buffer from the buffer pool in which to do the
 * name expansion, hence should be a power of two, and must
 * be less than or equal to MAXBSIZE.
 * MAXSYMLINKS defines the maximum number of symbolic links
 * that may be expanded in a path name. It should be set high
 * enough to allow all legitimate uses, but halt infinite loops
 * reasonably quickly.
E 90
I 90
 * MAXPATHLEN defines the longest permissable path length after expanding
 * symbolic links. It is used to allocate a temporary buffer from the buffer
 * pool in which to do the name expansion, hence should be a power of two,
 * and must be less than or equal to MAXBSIZE.  MAXSYMLINKS defines the
 * maximum number of symbolic links that may be expanded in a path name.
 * It should be set high enough to allow all legitimate uses, but halt
 * infinite loops reasonably quickly.
E 90
 */
D 75
#define MAXPATHLEN	1024
E 75
I 75
#define	MAXPATHLEN	PATH_MAX
E 75
#define MAXSYMLINKS	8

D 90
/*
I 73
D 80
 * Constants for setting the parameters of the kernel memory allocator.
 *
 * 2 ** MINBUCKET is the smallest unit of memory that will be
 * allocated. It must be at least large enough to hold a pointer.
 *
 * Units of memory less or equal to MAXALLOCSAVE will permanently
 * allocate physical memory; requests for these size pieces of
 * memory are quite fast. Allocations greater than MAXALLOCSAVE must
 * always allocate and free physical memory; requests for these
 * size allocations should be done infrequently as they will be slow.
 * Constraints: CLBYTES <= MAXALLOCSAVE <= 2 ** (MINBUCKET + 14)
 * and MAXALLOCSIZE must be a power of two.
 */
#define MINBUCKET	4		/* 4 => min allocation of 16 bytes */
#define MAXALLOCSAVE	(2 * CLBYTES)

/*
E 80
E 73
 * bit map related macros
 */
E 90
I 90
/* Bit map related macros. */
E 90
#define	setbit(a,i)	((a)[(i)/NBBY] |= 1<<((i)%NBBY))
#define	clrbit(a,i)	((a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define	isset(a,i)	((a)[(i)/NBBY] & (1<<((i)%NBBY)))
#define	isclr(a,i)	(((a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)

D 90
/*
D 80
 * Macros for fast min/max.
 */
#define	MIN(a,b) (((a)<(b))?(a):(b))
#define	MAX(a,b) (((a)>(b))?(a):(b))

/*
E 80
 * Macros for counting and rounding.
 */
E 90
I 90
/* Macros for counting and rounding. */
E 90
I 62
#ifndef howmany
E 62
#define	howmany(x, y)	(((x)+((y)-1))/(y))
I 62
#endif
E 62
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))
I 73
#define powerof2(x)	((((x)-1)&(x))==0)
I 80

D 90
/*
 * Macros for fast min/max:
 * with inline expansion, the "function" is faster.
 */
E 90
I 90
D 94
/* Macros for fast min/max: with inline expansion, the "function" is faster. */
E 90
#ifdef KERNEL
#define	MIN(a,b) min((a), (b))
#define	MAX(a,b) max((a), (b))
#else
E 94
I 94
/* Macros for min/max. */
#ifndef KERNEL
E 94
#define	MIN(a,b) (((a)<(b))?(a):(b))
#define	MAX(a,b) (((a)>(b))?(a):(b))
#endif

/*
 * Constants for setting the parameters of the kernel memory allocator.
 *
 * 2 ** MINBUCKET is the smallest unit of memory that will be
 * allocated. It must be at least large enough to hold a pointer.
 *
 * Units of memory less or equal to MAXALLOCSAVE will permanently
 * allocate physical memory; requests for these size pieces of
 * memory are quite fast. Allocations greater than MAXALLOCSAVE must
 * always allocate and free physical memory; requests for these
 * size allocations should be done infrequently as they will be slow.
D 90
 * Constraints: CLBYTES <= MAXALLOCSAVE <= 2 ** (MINBUCKET + 14)
 * and MAXALLOCSIZE must be a power of two.
E 90
I 90
 *
 * Constraints: CLBYTES <= MAXALLOCSAVE <= 2 ** (MINBUCKET + 14), and
 * MAXALLOCSIZE must be a power of two.
E 90
 */
#define MINBUCKET	4		/* 4 => min allocation of 16 bytes */
#define MAXALLOCSAVE	(2 * CLBYTES)
E 80
I 78

/*
 * Scale factor for scaled integers used to count %cpu time and load avgs.
 *
 * The number of CPU `tick's that map to a unique `%age' can be expressed
 * by the formula (1 / (2 ^ (FSHIFT - 11))).  The maximum load average that
 * can be calculated (assuming 32 bits) can be closely approximated using
 * the formula (2 ^ (2 * (16 - FSHIFT))) for (FSHIFT < 15).
 *
 * For the scheduler to maintain a 1:1 mapping of CPU `tick' to `%age',
 * FSHIFT must be at least 11; this gives us a maximum load avg of ~1024.
 */
#define	FSHIFT	11		/* bits to right of fixed binary point */
#define FSCALE	(1<<FSHIFT)
E 78
E 73
I 58
D 71

/*
D 60
 * Maximum size of hostname recognized and stroed in the kernel.
E 60
I 60
 * Maximum size of hostname recognized and stored in the kernel.
E 60
 */
D 60
#define MAXHOSTNAMELEN	32
E 60
I 60
#define MAXHOSTNAMELEN	64
E 71
D 62

#ifndef KERNEL
#include	<sys/types.h>
#else
#ifndef LOCORE
#include	"types.h"
#endif
#endif
E 62
E 60
E 58
D 40

/*
 * Provide about n microseconds of delay.
E 31
 */
#define	DELAY(n)	{ register int N = (n); while (--N > 0); }
E 40
E 24
D 4

#ifdef KERNEL
#ifdef lint
int	__void__;
#define	VOID	__void__ = (int)
#else
#define	VOID
#endif
#endif
E 4
E 1
