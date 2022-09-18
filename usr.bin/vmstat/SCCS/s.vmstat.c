h03040
s 00003/00000/00847
d D 8.2 95/03/01 15:06:16 mckusick 65 64
c add more paging statistics to -s option
e
s 00005/00005/00842
d D 8.1 93/06/06 22:22:29 bostic 64 63
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00846
d D 5.44 93/05/08 18:46:47 mckusick 63 62
c ignore ourselves in the run queue
e
s 00003/00004/00844
d D 5.43 93/04/05 21:49:47 ralph 62 61
c fix idle time display (used wrong entry in arrary).
e
s 00005/00003/00843
d D 5.42 93/03/31 17:21:56 mckusick 61 60
c convert from kinfo to sysctl
e
s 00007/00002/00839
d D 5.41 93/03/27 16:49:17 ralph 60 59
c added mips code. Fixed error printf's to fprintf(stderr.
e
s 00004/00001/00837
d D 5.40 93/02/26 11:01:24 mckusick 59 58
c worry about overflow when computing percentages
e
s 00048/00005/00790
d D 5.39 92/10/22 22:51:18 mckusick 58 57
c add size distribution printout for -m option
e
s 00014/00012/00781
d D 5.38 92/10/17 13:14:23 bostic 57 56
c nl is an exported curses function
e
s 00001/00001/00792
d D 5.37 92/09/02 11:58:13 bostic 56 55
c add luna68k
e
s 00001/00001/00792
d D 5.36 92/08/31 13:16:50 bostic 55 54
c typo, only displayed diskops/second for the first drive
c from Jeff Forys
e
s 00002/00001/00791
d D 5.35 92/07/24 12:44:39 bostic 54 53
c make names.c useable by systat; read_names now returns a value instead
c of exiting, add support (completely untested) for Sun's
e
s 00015/00010/00777
d D 5.34 92/06/23 10:47:25 mccanne 53 52
c port to new kvm; use stathz instead of phz
e
s 00014/00008/00773
d D 5.33 92/01/27 12:16:12 bostic 52 51
c don't let users create their own symbol table for the running kernel
e
s 00062/00076/00719
d D 5.32 91/10/10 22:01:38 mckusick 51 50
c clean up to reflect new statistics gathering model
e
s 00000/00001/00795
d D 5.31 91/07/02 09:45:57 karels 50 49
c rm leftover debugging code, get 1X memory use instead of 2X
e
s 00047/00106/00749
d D 5.30 91/06/20 12:17:33 karels 49 48
c back to per-second stats, with rounding; start removing oldvm; rm -z
e
s 00107/00060/00748
d D 5.29 91/06/04 22:39:27 karels 48 47
c add new VM statistics, to be merged later; always separate the columns!
e
s 00124/00048/00684
d D 5.28 91/06/04 20:36:15 karels 47 46
c make compile under nwe VM system, add memory totals, little cleanups
e
s 00001/00001/00731
d D 5.27 91/05/29 18:26:45 bostic 46 45
c no automatic aggregate initialization with PCC
e
s 00059/00060/00673
d D 5.26 91/04/24 12:26:40 bostic 45 44
c make default interval 1, make "iostat -w 3" repeat indefinitely
c "in" now includes clock interrupts; redo routines derived from iostat
c from scratch for cleanliness and guarantee no AT&T code left
e
s 00374/00491/00359
d D 5.25 91/04/23 17:17:15 bostic 44 43
c general cleanup and consistency time; ANSI/lint, -M, -N, -c, -w
e
s 00005/00003/00845
d D 5.24 91/03/02 13:20:01 bostic 43 42
c ANSI
e
s 00443/00312/00405
d D 5.23 90/12/18 11:06:49 bostic 42 41
c make vmstat work on crash dumps (use kvm lib); vmstat -t doesn't work
c any more; make multiple options work; an incredible amount of lint.
c From Chris Torek
e
s 00002/00039/00715
d D 5.22 90/08/29 14:05:24 mckusick 41 40
c list of names moves to <sys/malloc.h>
e
s 00055/00007/00699
d D 5.21 90/06/06 20:31:38 bostic 40 39
c fixes for HP300, from Mike Hibler
e
s 00001/00011/00705
d D 5.20 90/06/01 18:33:49 bostic 39 38
c new copyright notice
e
s 00003/00004/00713
d D 5.19 90/05/02 19:48:13 mckusick 38 37
c add M_DQUOT and M_UFSMNT; delete unneeded header files
e
s 00003/00001/00714
d D 5.18 90/04/10 20:45:45 mckusick 37 36
c add M_VNODE and M_CACHE entries
e
s 00000/00001/00715
d D 5.17 90/02/20 16:15:30 bostic 36 35
c don't need dir.h anymore
e
s 00011/00007/00705
d D 5.16 89/08/26 00:35:44 mckusick 35 34
c print out negative name cacheing statistics
e
s 00003/00001/00709
d D 5.15 89/06/08 13:38:16 mckusick 34 33
c new header file locations
e
s 00004/00001/00706
d D 5.14 89/06/08 13:31:43 mckusick 33 32
c add new malloc types
e
s 00009/00009/00698
d D 5.13 89/05/11 13:33:56 bostic 32 31
c file reorg, pathnames.h, paths.h
e
s 00017/00006/00690
d D 5.12 89/01/19 10:01:27 bostic 31 30
c original Berkeley code; add Berkeley copyright notice
e
s 00002/00001/00694
d D 5.11 89/01/05 19:32:56 marc 30 29
c add iov to domem() (vmstat -m)
e
s 00026/00020/00669
d D 5.10 89/01/05 16:25:47 marc 29 28
c add pgrps and sessions to vmstat -m
e
s 00077/00003/00612
d D 5.9 88/02/27 15:04:30 mckusick 28 27
c add -m flag to print out memory usage statistics
e
s 00001/00001/00614
d D 5.8 86/12/09 13:43:04 bostic 27 26
c typo in the nlist sanity checking; bug report 4.3BSD/ucb/50
e
s 00004/00000/00611
d D 5.7 86/11/15 11:27:08 sam 26 25
c must include cpu.h for tahoe keystat structure
e
s 00026/00062/00585
d D 5.6 86/07/25 23:26:28 sam 25 24
c 4.3 update; send errors to stderr; cleanup code; widen memory field
e
s 00026/00001/00621
d D 5.5 86/01/24 02:25:39 sam 24 23
c add code and data cache key stats under -s
e
s 00076/00025/00546
d D 5.4 86/01/06 19:50:45 sam 23 22
c add tahoe
e
s 00031/00002/00540
d D 5.3 85/11/20 20:56:39 sam 22 21
c add text cache stats to -s report
e
s 00001/00001/00541
d D 5.2 85/08/26 10:20:17 mckusick 21 20
c spelling
e
s 00014/00002/00528
d D 5.1 85/05/31 09:36:39 dist 20 19
c Add copyright
e
s 00005/00010/00525
d D 4.18 85/04/25 21:25:23 sam 19 18
c when printing header after SIGCONT, reset count to next header
e
s 00149/00067/00386
d D 4.17 85/04/24 23:39:21 sam 18 17
c handle arbitrary number of disk drives; allow drive selection from command line
e
s 00000/00034/00453
d D 4.16 85/04/01 14:37:12 karels 17 16
c rm sun
e
s 00064/00017/00423
d D 4.15 84/10/17 13:50:05 mckusick 16 15
c add -i flag to summarize interrupts
e
s 00006/00003/00434
d D 4.14 84/06/09 13:14:22 sam 15 14
c update for changes to namei cache & and add other stats
e
s 00017/00003/00420
d D 4.13 84/01/04 16:24:57 mckusick 14 13
c add statistical line for namei in -s option
e
s 00023/00029/00400
d D 4.12 83/10/19 20:00:27 sam 13 12
c take into account alternate line clock -- both in defining hz 
c for disk i/o stats and in adjusting interrupt rate; also purge sun swap 
c stats flag -- they page now
e
s 00001/00001/00428
d D 4.11 83/09/25 12:42:58 sam 12 11
c 60 no, hz yes
e
s 00002/00001/00427
d D 4.10 83/05/30 18:41:30 sam 11 9
c show percent of fast reclaims
e
s 00002/00001/00427
d R 4.10 83/05/30 16:54:30 sam 10 9
c show fast reclaim percentage
e
s 00090/00022/00338
d D 4.9 83/02/09 15:22:21 sam 9 8
c from sun
e
s 00008/00008/00352
d D 4.8 82/11/15 11:32:44 sam 8 7
c conversion to 4.1c
e
s 00010/00011/00350
d D 4.7 81/04/28 00:46:52 root 7 6
c new format for output (pages all over), -s prints pgpg*, seqfree
e
s 00003/00006/00358
d D 4.6 81/04/08 18:44:56 root 6 5
c fix to work with no mba's
e
s 00005/00005/00359
d D 4.5 81/03/11 18:50:19 wnj 5 4
c print ``disk'' on top line, names (1 char and 1 number)
e
s 00002/00002/00362
d D 4.4 81/03/10 07:02:09 wnj 4 3
c miscellaneous minor fixups
e
s 00077/00038/00287
d D 4.3 81/03/09 20:51:50 toy 3 2
c Made it know about device names
e
s 00035/00051/00290
d D 4.2 80/10/16 01:08:05 bill 2 1
c new iostat information format
e
s 00341/00000/00000
d D 4.1 80/10/01 17:29:22 bill 1 0
c date and time created 80/10/01 17:29:22 by bill
e
u
U
t
T
I 20
/*
D 31
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 31
I 31
D 44
 * Copyright (c) 1980 The Regents of the University of California.
E 44
I 44
D 64
 * Copyright (c) 1980, 1986, 1991 The Regents of the University of California.
E 44
 * All rights reserved.
E 64
I 64
 * Copyright (c) 1980, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 64
 *
D 39
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
E 39
I 39
 * %sccs.include.redist.c%
E 39
E 31
 */

E 20
I 9
#ifndef lint
E 9
I 1
D 5
static char *sccsid = "%W% (Berkeley) %G%";
E 5
I 5
D 20
static	char *sccsid = "%W% (Berkeley) %G%";
I 9
#endif
E 20
I 20
D 64
char copyright[] =
D 31
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 31
I 31
D 44
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 44
I 44
"%Z% Copyright (c) 1980, 1986, 1991 The Regents of the University of California.\n\
E 44
E 31
 All rights reserved.\n";
E 64
I 64
static char copyright[] =
"%Z% Copyright (c) 1980, 1986, 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 64
D 31
#endif not lint
E 31
I 31
#endif /* not lint */
E 31

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 31
#endif not lint
E 31
I 31
#endif /* not lint */
E 31
E 20

E 9
E 5
D 32
#include <stdio.h>
I 18
#include <ctype.h>
#include <nlist.h>

E 32
E 18
#include <sys/param.h>
I 18
D 44
#include <sys/file.h>
E 44
E 18
D 47
#include <sys/vm.h>
E 47
I 47
#include <sys/time.h>
#include <sys/proc.h>
E 47
I 43
#include <sys/user.h>
E 43
D 25
#include <sys/dk.h>
E 25
I 25
#include <sys/dkstat.h>
E 25
D 18
#include <nlist.h>
E 18
I 3
#include <sys/buf.h>
I 14
D 36
#include <sys/dir.h>
E 36
I 18
D 34
#include <sys/inode.h>
E 34
I 34
D 38
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 38
E 34
E 18
D 16
#include <sys/nami.h>
E 16
I 16
#include <sys/namei.h>
I 23
D 47
#include <sys/text.h>
E 47
I 28
#include <sys/malloc.h>
I 32
D 42
#include <stdio.h>
E 42
D 44
#include <ctype.h>
I 42
#include <errno.h>
#include <kvm.h>
E 44
I 44
D 47
#include <signal.h>
#include <fcntl.h>
E 47
I 47
#include <sys/signal.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
I 49
D 51
#include <sys/vmmeter.h>
E 51
I 51
D 61
#include <sys/kinfo.h>
E 61
I 61
#include <sys/sysctl.h>
E 61
E 51
#include <vm/vm.h>
D 51
#include <vm/vm_statistics.h>
E 51
E 49
E 47
#include <time.h>
E 44
E 42
#include <nlist.h>
I 44
#include <kvm.h>
#include <errno.h>
#include <unistd.h>
E 44
I 42
#include <stdio.h>
I 44
#include <ctype.h>
E 44
#include <stdlib.h>
#include <string.h>
E 42
#include <paths.h>
I 53
#include <limits.h>
E 53
E 32
E 28
E 23
E 16
E 14
I 9
D 18
#ifdef vax
E 9
D 8
#include <sys/ubavar.h>
#include <sys/mbavar.h>
E 8
I 8
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
I 9
#endif
E 18
D 17
#ifdef sun
#include <sundev/mbvar.h>
#endif
E 17
E 9
E 8
E 3

I 47
D 49
#ifdef SPPWAIT
#define NEWVM
#endif
D 48
#ifndef NEWVM
E 48
I 48
#ifdef NEWVM
#include <sys/vmmeter.h>
#include <vm/vm.h>
#include <vm/vm_statistics.h>
#else
E 48
#include <sys/vm.h>
#include <sys/text.h>
D 48
#else
#include <sys/vmmeter.h>
E 48
#endif

E 49
I 49
#define NEWVM			/* XXX till old has been updated or purged */
E 49
E 47
D 57
struct nlist nl[] = {
E 57
I 57
struct nlist namelist[] = {
E 57
D 2
#define	X_DKBUSY 0
	{ "_dk_busy" },
#define	X_DKTIME 1
	{ "_dk_time" },
#define	X_DKNUMB 2
	{ "_dk_numb" },
#define	X_RATE 3
E 2
I 2
#define	X_CPTIME	0
	{ "_cp_time" },
D 48
#define	X_RATE		1
E 2
	{ "_rate" },
D 2
#define X_TOTAL 4
E 2
I 2
#define X_TOTAL		2
E 48
I 48
D 51
#define X_TOTAL		1
E 48
E 2
	{ "_total" },
E 51
I 51
#define	X_DK_NDRIVE	1
	{ "_dk_ndrive" },
E 51
D 2
#define	X_DEFICIT 5
E 2
I 2
D 47
#define	X_DEFICIT	3
E 2
	{ "_deficit" },
D 2
#define	X_FORKSTAT 6
E 2
I 2
#define	X_FORKSTAT	4
E 2
	{ "_forkstat" },
D 2
#define X_SUM 7
E 2
I 2
#define X_SUM		5
E 2
	{ "_sum" },
D 2
#define	X_FIRSTFREE 8
E 2
I 2
D 44
#define	X_FIRSTFREE	6
E 2
	{ "_firstfree" },
D 2
#define	X_MAXFREE 9
E 2
I 2
#define	X_MAXFREE	7
E 2
	{ "_maxfree" },
D 2
#define	X_BOOTIME 10
E 2
I 2
D 8
#define	X_BOOTIME	8
E 2
	{ "_bootime" },
E 8
I 8
#define	X_BOOTTIME	8
E 44
I 44
#define	X_BOOTTIME	6
E 47
I 47
D 48
#define X_SUM		3
	{ "_cnt" },
#define	X_BOOTTIME	4
E 48
I 48
#define X_SUM		2
D 49
#define	SUM	"_cnt"			/* XXX for now that's where it is */
	{ SUM },
E 49
I 49
D 51
	{ "_cnt" },		/* XXX for now that's where it is */
E 51
I 51
	{ "_cnt" },
E 51
E 49
#define	X_BOOTTIME	3
E 48
E 47
E 44
	{ "_boottime" },
E 8
I 2
D 44
#define	X_DKXFER	9
E 44
I 44
D 47
#define	X_DKXFER	7
E 47
I 47
D 48
#define	X_DKXFER	5
E 48
I 48
#define	X_DKXFER	4
E 48
E 47
E 44
	{ "_dk_xfer" },
E 2
D 3
#ifdef ERNIE
D 2
#define X_REC 10
E 2
I 2
#define X_REC		10
E 3
I 3
D 9
#define X_MBDINIT	10
	{ "_mbdinit" },
#define X_UBDINIT	11
	{ "_ubdinit" },
#define X_REC		12
E 9
I 9
D 44
#define X_REC		10
E 44
I 44
D 47
#define X_REC		8
E 44
E 9
E 3
E 2
	{ "_rectime" },
D 2
#define X_PGIN 11
E 2
I 2
D 3
#define X_PGIN		11
E 3
I 3
D 9
#define X_PGIN		13
E 9
I 9
D 44
#define X_PGIN		11
E 44
I 44
#define X_PGIN		9
E 44
E 9
E 3
E 2
	{ "_pgintime" },
D 3
#endif
E 3
I 3
D 9
#define X_HZ		14
E 9
I 9
D 44
#define X_HZ		12
E 44
I 44
#define X_HZ		10
E 47
I 47
D 48
#define X_HZ		6
E 48
I 48
#define X_HZ		5
E 48
E 47
E 44
E 9
	{ "_hz" },
I 13
D 18
#define	X_PHZ		13
E 18
I 18
D 44
#define X_PHZ		13
E 44
I 44
D 47
#define X_PHZ		11
E 47
I 47
D 48
#define X_PHZ		7
E 48
I 48
D 53
#define X_PHZ		6
E 48
E 47
E 44
E 18
	{ "_phz" },
E 53
I 53
#define X_STATHZ	6
	{ "_stathz" },
E 53
I 14
D 44
#define X_NCHSTATS	14
E 44
I 44
D 47
#define X_NCHSTATS	12
E 47
I 47
D 48
#define X_NCHSTATS	8
E 48
I 48
#define X_NCHSTATS	7
E 48
E 47
E 44
	{ "_nchstats" },
I 16
D 44
#define	X_INTRNAMES	15
E 44
I 44
D 47
#define	X_INTRNAMES	13
E 47
I 47
D 48
#define	X_INTRNAMES	9
E 48
I 48
#define	X_INTRNAMES	8
E 48
E 47
E 44
	{ "_intrnames" },
D 44
#define	X_EINTRNAMES	16
E 44
I 44
D 47
#define	X_EINTRNAMES	14
E 47
I 47
D 48
#define	X_EINTRNAMES	10
E 48
I 48
#define	X_EINTRNAMES	9
E 48
E 47
E 44
	{ "_eintrnames" },
D 44
#define	X_INTRCNT	17
E 44
I 44
D 47
#define	X_INTRCNT	15
E 47
I 47
D 48
#define	X_INTRCNT	11
E 48
I 48
#define	X_INTRCNT	10
E 48
E 47
E 44
	{ "_intrcnt" },
D 44
#define	X_EINTRCNT	18
E 44
I 44
D 47
#define	X_EINTRCNT	16
E 47
I 47
D 48
#define	X_EINTRCNT	12
E 48
I 48
#define	X_EINTRCNT	11
E 48
E 47
E 44
	{ "_eintrcnt" },
I 18
D 44
#define	X_DK_NDRIVE	19
E 44
I 44
D 47
#define	X_DK_NDRIVE	17
E 47
I 47
D 48
#define	X_DK_NDRIVE	13
E 48
I 48
D 51
#define	X_DK_NDRIVE	12
E 48
E 47
E 44
	{ "_dk_ndrive" },
I 22
D 44
#define	X_XSTATS	20
E 44
I 44
D 47
#define	X_XSTATS	18
E 44
	{ "_xstats" },
I 28
D 44
#define	X_KMEMSTAT	21
E 44
I 44
#define	X_KMEMSTAT	19
E 47
I 47
D 48
#define	X_KMEMSTAT	14
E 48
I 48
#define	X_KMEMSTAT	13
E 51
I 51
#define	X_KMEMSTAT	12
E 51
E 48
E 47
E 44
	{ "_kmemstats" },
D 44
#define	X_KMEMBUCKETS	22
E 44
I 44
D 47
#define	X_KMEMBUCKETS	20
E 47
I 47
D 48
#define	X_KMEMBUCKETS	15
E 48
I 48
D 51
#define	X_KMEMBUCKETS	14
E 51
I 51
#define	X_KMEMBUCKETS	13
E 51
E 48
E 47
E 44
	{ "_bucket" },
I 47
D 49
#ifdef NEWVM
E 49
I 48
D 51
#define	X_VMSTAT	15
	{ "_vm_stat" },
E 51
E 48
D 49
#define X_END		15
#else
E 49
I 49
#ifdef notdef
E 49
D 48
#define	X_DEFICIT	16
E 48
I 48
D 51
#define	X_DEFICIT	15
E 51
I 51
#define	X_DEFICIT	14
E 51
E 48
	{ "_deficit" },
D 48
#define	X_FORKSTAT	17
E 48
I 48
D 51
#define	X_FORKSTAT	16
E 51
I 51
#define	X_FORKSTAT	15
E 51
E 48
	{ "_forkstat" },
D 48
#define X_REC		18
E 48
I 48
D 51
#define X_REC		17
E 51
I 51
#define X_REC		16
E 51
E 48
	{ "_rectime" },
D 48
#define X_PGIN		19
E 48
I 48
D 51
#define X_PGIN		18
E 51
I 51
#define X_PGIN		17
E 51
E 48
	{ "_pgintime" },
D 48
#define	X_XSTATS	20
E 48
I 48
D 51
#define	X_XSTATS	19
E 51
I 51
#define	X_XSTATS	18
E 51
E 48
	{ "_xstats" },
E 47
I 40
D 44
#define X_END		22
E 40
E 28
E 22
E 18
E 16
E 14
E 13
E 3
D 9
	{ 0 },
E 9
I 9
#ifdef vax
D 13
#define X_MBDINIT	13
E 13
I 13
D 14
#define X_MBDINIT	14
E 14
I 14
D 16
#define X_MBDINIT	15
E 16
I 16
D 18
#define X_MBDINIT	19
E 18
I 18
D 22
#define X_MBDINIT	20
E 22
I 22
D 23
#define X_MBDINIT	21
E 23
I 23
D 40
#define X_MBDINIT	(X_XSTATS+1)
E 40
I 40
#define X_MBDINIT	(X_END+1)
E 40
E 23
E 22
E 18
E 16
E 14
E 13
	{ "_mbdinit" },
D 13
#define X_UBDINIT	14
E 13
I 13
D 14
#define X_UBDINIT	15
E 14
I 14
D 16
#define X_UBDINIT	16
E 16
I 16
D 18
#define X_UBDINIT	20
E 18
I 18
D 22
#define X_UBDINIT	21
E 22
I 22
D 23
#define X_UBDINIT	22
E 23
I 23
D 40
#define X_UBDINIT	(X_XSTATS+2)
E 40
I 40
#define X_UBDINIT	(X_END+2)
E 40
E 23
E 22
E 18
E 16
E 14
E 13
	{ "_ubdinit" },
E 44
I 44
D 48
#define X_END		20
E 48
I 48
D 51
#define X_END		19
E 51
I 51
#define X_END		18
E 51
I 49
#else
D 51
#define X_END		15
E 51
I 51
#define X_END		14
E 51
E 49
E 48
I 47
#endif
E 47
D 56
#ifdef hp300
E 56
I 56
#if defined(hp300) || defined(luna68k)
E 56
D 51
#define	X_HPDINIT	(X_END+1)
E 51
I 51
#define	X_HPDINIT	(X_END)
E 51
	{ "_hp_dinit" },
E 44
#endif
I 60
#ifdef mips
#define	X_SCSI_DINIT	(X_END)
	{ "_scsi_dinit" },
#endif
E 60
I 23
D 25
#ifdef sun
#define X_MBDINIT	(X_XSTATS+1)
	{ "_mbdinit" },
#endif
E 25
#ifdef tahoe
D 40
#define	X_VBDINIT	(X_XSTATS+1)
E 40
I 40
D 51
#define	X_VBDINIT	(X_END+1)
E 51
I 51
#define	X_VBDINIT	(X_END)
E 51
E 40
	{ "_vbdinit" },
I 24
D 40
#define	X_CKEYSTATS	(X_XSTATS+2)
E 40
I 40
D 51
#define	X_CKEYSTATS	(X_END+2)
E 51
I 51
#define	X_CKEYSTATS	(X_END+1)
E 51
E 40
	{ "_ckeystats" },
D 40
#define	X_DKEYSTATS	(X_XSTATS+3)
E 40
I 40
D 51
#define	X_DKEYSTATS	(X_END+3)
E 51
I 51
#define	X_DKEYSTATS	(X_END+2)
E 51
E 40
	{ "_dkeystats" },
E 24
#endif
I 40
D 44
#ifdef hp300
#define	X_HPDINIT	(X_END+1)
	{ "_hp_dinit" },
E 44
I 44
#ifdef vax
D 51
#define X_MBDINIT	(X_END+1)
E 51
I 51
#define X_MBDINIT	(X_END)
E 51
	{ "_mbdinit" },
D 51
#define X_UBDINIT	(X_END+2)
E 51
I 51
#define X_UBDINIT	(X_END+1)
E 51
	{ "_ubdinit" },
E 44
#endif
E 40
E 23
D 16
#ifdef sun
D 13
#define X_MBDINIT	13
E 13
I 13
D 14
#define X_MBDINIT	14
E 14
I 14
#define X_MBDINIT	15
E 14
E 13
	{ "_mbdinit" },
#endif
E 16
	{ "" },
E 9
};

I 42
D 44
char	*vmunix = _PATH_UNIX;
char	*kmem = NULL;
E 42
I 3
D 18
char dr_name[DK_NDRIVE][10];
char dr_unit[DK_NDRIVE];
E 18
I 18
char	**dr_name;
int	*dr_select;
int	dk_ndrive;
int	ndrives = 0;
#ifdef vax
char	*defdrives[] = { "hp0", "hp1", "hp2",  0 };
#else
I 40
#ifdef hp300
char	*defdrives[] = { "rd0", "rd1", "rd2",  0 };
#else
E 40
char	*defdrives[] = { 0 };
#endif
I 40
#endif
E 40
E 18
E 3
double	stat1();
int	firstfree, maxfree;
I 3
int	hz;
I 13
int	phz;
int	HZ;
E 44
I 44
struct _disk {
	long time[CPUSTATES];
	long *xfer;
} cur, last;
E 44
I 18

E 18
D 17
#ifdef sun
#define	INTS(x)	(x)
#endif
E 17
D 23
#ifdef vax
#define	INTS(x)	((x) - (hz + phz))
#endif

E 23
E 13
E 3
D 18
struct
{
E 18
I 18
D 44
struct {
E 18
	int	busy;
D 2
	long	etime[CPUSTATES][DK_NSTATES];
	long	numb[DK_NDRIVE];
E 2
I 2
	long	time[CPUSTATES];
D 18
	long	xfer[DK_NDRIVE];
E 18
I 18
	long	*xfer;
E 18
E 2
	struct	vmmeter Rate;
	struct	vmtotal	Total;
	struct	vmmeter Sum;
	struct	forkstat Forkstat;
D 3
#ifdef ERNIE
E 3
	unsigned rectime;
	unsigned pgintime;
D 3
#endif
E 3
D 42
} s, s1, z;
E 42
I 42
} s, s1;
E 42
#define	rate		s.Rate
#define	total		s.Total
#define	sum		s.Sum
#define	forkstat	s.Forkstat
E 44
I 44
D 47
struct vmmeter sum;
D 45
double etime, stat1();
E 45
char *vmunix = _PATH_UNIX;
char **dr_name;
int *dr_select, dk_ndrive, ndrives;
E 47
I 47
D 48
struct	vmmeter sum;
E 48
I 48
D 49
#ifdef NEWVM
E 49
D 51
struct	vm_statistics vm_stat, ostat;
E 51
D 49
#endif
E 49
struct	vmmeter sum, osum;
E 48
D 52
char	*vmunix = _PATH_UNIX;
E 52
char	**dr_name;
int	*dr_select, dk_ndrive, ndrives;
E 47
E 44

I 47
int	winlines = 20;

I 53
kvm_t *kd;

E 53
E 47
I 9
D 44
struct	vmmeter osum;
E 9
D 3
int	iflag = 1;
E 3
D 25
int	zero;
E 25
int	deficit;
double	etime;
D 42
int 	mf;
E 42
I 16
time_t	now, boottime;
D 42
int	printhdr();
E 42
I 19
int	lines = 1;
I 42
void	printhdr();
long	lseek();
E 42
E 19
E 16
I 9
D 13
int	swflag;
E 13
E 9

I 25
#define	INTS(x)	((x) - (hz + phz))

E 44
I 42
#define	FORKSTAT	0x01
#define	INTRSTAT	0x02
#define	MEMSTAT		0x04
#define	SUMSTAT		0x08
#define	TIMESTAT	0x10
#define	VMSTAT		0x20
D 49
#define	ZEROOUT		0x40
E 49

I 44
D 45
void kread();

E 45
#include "names.c"			/* disk names -- machine dependent */

D 45
void doforkst(), dointr(), domem(), dosum(), dotimes(), dovmstat();
void stats(), usage(), zero();
E 45
I 45
D 47
void cpustats(), dkstats(), doforkst(), dointr(), domem(), dosum();
void dotimes(), dovmstat(), kread(), usage(), zero();
E 47
I 47
void	cpustats(), dkstats(), dointr(), domem(), dosum();
D 49
void	dovmstat(), kread(), usage(), zero();
#ifndef NEWVM
E 49
I 49
void	dovmstat(), kread(), usage();
#ifdef notdef
E 49
void	dotimes(), doforkst();
#endif
E 47
E 45

E 44
E 42
E 25
main(argc, argv)
D 9
char **argv;
E 9
I 9
D 42
	int argc;
	char **argv;
E 42
I 42
	register int argc;
	register char **argv;
E 42
E 9
{
D 16
	time_t now;
E 16
D 19
	int lines;
E 19
D 42
	extern char *ctime();
D 25
	register i,j;
E 25
I 25
	register i;
E 25
D 16
	int iter, nintv;
D 8
	time_t bootime;
E 8
I 8
	time_t boottime;
E 16
I 16
	int iter, nintv, iflag = 0;
E 16
E 8
D 25
	double f1, f2;
E 25
	long t;
I 18
D 25
	char *arg, **cp, name[6], buf[BUFSIZ];
E 25
I 25
	char *arg, **cp, buf[BUFSIZ];
E 42
I 42
D 44
	register int c, i, todo = 0;
E 44
	extern int optind;
	extern char *optarg;
I 44
	register int c, todo;
	u_int interval;
	int reps;
D 52
	char *kmem;
E 52
I 52
	char *memf, *nlistf;
I 53
        char errbuf[_POSIX2_LINE_MAX];
E 53
E 52
E 44
E 42
E 25
E 18
D 16
	extern char _sobuf[];
E 16

I 9
D 13
#ifdef sun
	swflag = 1;
#endif
E 13
E 9
D 16
	setbuf(stdout, _sobuf);
E 16
D 32
	nlist("/vmunix", nl);
E 32
I 32
D 42
	nlist(_PATH_UNIX, nl);
E 32
	if(nl[0].n_type == 0) {
D 25
		printf("no /vmunix namelist\n");
E 25
I 25
D 32
		fprintf(stderr, "no /vmunix namelist\n");
E 32
I 32
		fprintf(stderr, "vmstat: no %s namelist\n", _PATH_UNIX);
E 32
E 25
		exit(1);
	}
D 32
	mf = open("/dev/kmem", 0);
E 32
I 32
	mf = open(_PATH_KMEM, 0);
E 32
	if(mf < 0) {
D 25
		printf("cannot open /dev/kmem\n");
E 25
I 25
D 32
		fprintf(stderr, "cannot open /dev/kmem\n");
E 32
I 32
		fprintf(stderr, "vmstat: cannot open %s\n", _PATH_KMEM);
E 32
E 25
		exit(1);
	}
	iter = 0;
	argc--, argv++;
	while (argc>0 && argv[0][0]=='-') {
		char *cp = *argv++;
		argc--;
		while (*++cp) switch (*cp) {

I 9
D 13
		case 'S':
			swflag = 1 - swflag;
			break;


E 13
E 9
D 3
#ifdef ERNIE
E 3
		case 't':
			dotimes();
			exit(0);
I 9

E 9
D 3
#endif
E 3
		case 'z':
			close(mf);
D 32
			mf = open("/dev/kmem", 2);
E 32
I 32
			mf = open(_PATH_KMEM, 2);
E 32
D 18
			lseek(mf, (long)nl[X_SUM].n_value, 0);
E 18
I 18
			lseek(mf, (long)nl[X_SUM].n_value, L_SET);
E 18
			write(mf, &z.Sum, sizeof z.Sum);
			exit(0);

E 42
I 42
D 44
	while ((c = getopt(argc, argv, "fik:mstu:z")) != EOF) {
E 44
I 44
D 52
	kmem = NULL;
E 52
I 52
	memf = nlistf = NULL;
E 52
	interval = reps = todo = 0;
D 49
	while ((c = getopt(argc, argv, "c:fiM:mN:stw:z")) != EOF) {
E 49
I 49
	while ((c = getopt(argc, argv, "c:fiM:mN:stw:")) != EOF) {
E 49
E 44
		switch (c) {
I 44
		case 'c':
			reps = atoi(optarg);
			break;
I 47
D 49
#ifndef NEWVM
E 49
I 49
#ifndef notdef
E 49
E 47
E 44
E 42
		case 'f':
D 42
			doforkst();
			exit(0);
		
E 42
I 42
			todo |= FORKSTAT;
			break;
I 47
#endif
E 47
		case 'i':
			todo |= INTRSTAT;
			break;
D 44
		case 'k':
E 44
I 44
		case 'M':
E 44
D 52
			kmem = optarg;
E 52
I 52
			memf = optarg;
E 52
			break;
E 42
I 28
		case 'm':
D 42
			domem();
			exit(0);

E 42
I 42
			todo |= MEMSTAT;
			break;
I 44
		case 'N':
D 52
			vmunix = optarg;
E 52
I 52
			nlistf = optarg;
E 52
			break;
E 44
E 42
E 28
		case 's':
D 42
			dosum();
			exit(0);

I 16
		case 'i':
			iflag++;
E 42
I 42
			todo |= SUMSTAT;
E 42
			break;
I 47
D 49
#ifndef NEWVM
E 49
I 49
#ifndef notdef
E 49
E 47
D 42

E 42
I 42
		case 't':
			todo |= TIMESTAT;
			break;
I 47
#endif
E 47
D 44
		case 'u':
			vmunix = optarg;
E 44
I 44
		case 'w':
			interval = atoi(optarg);
E 44
			break;
D 49
		case 'z':
			todo |= ZEROOUT;
			break;
E 49
		case '?':
D 44
			usage();
			/* NOTREACHED */
E 44
E 42
E 16
D 3
		case 'i':
			iflag = 0;
			break;

E 3
		default:
D 16
			fprintf(stderr, "usage: vmstat [ -fs ] [ interval ] [ count]\n");
E 16
I 16
D 18
			fprintf(stderr, "usage: vmstat [ -fsi ] [ interval ] [ count]\n");
E 18
I 18
D 42
			fprintf(stderr,
D 28
			    "usage: vmstat [ -fsi ] [ interval ] [ count]\n");
E 28
I 28
			    "usage: vmstat [ -fsim ] [ interval ] [ count]\n");
E 42
I 42
D 44
			(void) fprintf(stderr,
			    "vmstat: internal error in options\n");
E 42
E 28
E 18
E 16
			exit(1);
I 42
			/* NOTREACHED */
E 44
I 44
			usage();
E 44
E 42
		}
	}
I 44
	argc -= optind;
	argv += optind;
E 44
D 18
	if(argc > 1)
		iter = atoi(argv[1]);
	lseek(mf, (long)nl[X_FIRSTFREE].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_FIRSTFREE].n_value, L_SET);
E 18
	read(mf, &firstfree, sizeof firstfree);
D 18
	lseek(mf, (long)nl[X_MAXFREE].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_MAXFREE].n_value, L_SET);
E 18
	read(mf, &maxfree, sizeof maxfree);
D 8
	lseek(mf, (long)nl[X_BOOTIME].n_value, 0);
	read(mf, &bootime, sizeof bootime);
E 8
I 8
D 18
	lseek(mf, (long)nl[X_BOOTTIME].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_BOOTTIME].n_value, L_SET);
E 18
	read(mf, &boottime, sizeof boottime);
E 8
I 3
D 18
	lseek(mf, (long)nl[X_HZ].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_HZ].n_value, L_SET);
E 18
	read(mf, &hz, sizeof hz);
I 13
D 18
	lseek(mf, (long)nl[X_PHZ].n_value, 0);
	read(mf, &phz, sizeof phz);
E 18
I 18
	if (nl[X_PHZ].n_value != 0) {
		lseek(mf, (long)nl[X_PHZ].n_value, L_SET);
		read(mf, &phz, sizeof phz);
E 42
I 42

D 44
	/*
	 * Zeroing the statistics is fundamentally different
	 * (and really belongs in a separate program).
	 */
E 44
D 49
	if (todo & ZEROOUT) {
		if (todo & ~ZEROOUT || kmem)
			usage();
D 44
		nl[0].n_name = nl[X_SUM].n_name;
		nl[1].n_name = 0;
		if (nlist(vmunix, nl) || nl[0].n_type == 0) {
			(void) fprintf(stderr,
			    "vmstat: cannot get symbol %s from %s\n",
			    nl[0].n_name, vmunix);
			exit(1);
		}
		if ((i = open(kmem = _PATH_KMEM, 2)) < 0) {
			(void) fprintf(stderr, "vmstat: cannot write %s: %s\n",
			    kmem, strerror(errno));
			exit(1);
		}
		(void) lseek(i, (long)nl[0].n_value, L_SET);
		if (write(i, (char *)&s.Sum, sizeof s.Sum) != sizeof s.Sum) {
			(void) fprintf(stderr, "vmstat: write(%s): %s\n",
			    kmem, strerror(errno));
			exit(1);
		}
E 44
I 44
		zero();
E 44
		exit(0);
E 42
	}
E 18
D 42
	HZ = phz ? phz : hz;
E 13
D 7
	for (i = 0; i < DK_NDRIVE; i++)
	{
E 7
I 7
D 18
	for (i = 0; i < DK_NDRIVE; i++) {
E 7
D 5
		strcpy(dr_name[i], "DK");
E 5
I 5
		strcpy(dr_name[i], "xx");
E 5
		dr_unit[i] = i;
E 18
I 18
D 27
	if (nl[DK_NDRIVE].n_value == 0) {
E 27
I 27
	if (nl[X_DK_NDRIVE].n_value == 0) {
E 27
D 25
		printf("dk_ndrive undefined in system\n");
E 25
I 25
		fprintf(stderr, "dk_ndrive undefined in system\n");
E 42
I 42

E 49
	if (todo == 0)
		todo = VMSTAT;

D 44
	if (kvm_openfiles(vmunix, kmem, (char *)NULL) < 0) {
		(void) fprintf(stderr,
		    "vmstat: kvm_openfiles(%s, %s, NULL): %s\n",
		    vmunix, kmem ? kmem : "NULL", kvm_geterr());
E 44
I 44
D 52
	if (kvm_openfiles(vmunix, kmem, NULL) < 0) {
E 52
I 52
	/*
	 * Discard setgid privileges if not the running kernel so that bad
	 * guys can't print interesting stuff from kernel memory.
	 */
	if (nlistf != NULL || memf != NULL)
		setgid(getgid());

D 53
	if (kvm_openfiles(nlistf, memf, NULL) < 0) {
E 53
I 53
        kd = kvm_openfiles(nlistf, memf, NULL, O_RDONLY, errbuf);
	if (kd == 0) {
E 53
E 52
		(void)fprintf(stderr,
D 53
		    "vmstat: kvm_openfiles: %s\n", kvm_geterr());
E 53
I 53
		    "vmstat: kvm_openfiles: %s\n", errbuf);
E 53
E 44
E 42
E 25
		exit(1);
E 18
	}
I 18
D 42
	lseek(mf, nl[X_DK_NDRIVE].n_value, L_SET);
	read(mf, &dk_ndrive, sizeof (dk_ndrive));
	if (dk_ndrive <= 0) {
D 25
		printf("dk_ndrive %d\n", dk_ndrive);
E 25
I 25
		fprintf(stderr, "dk_ndrive %d\n", dk_ndrive);
E 42
I 42

D 44
	(void) kvm_nlist(nl);
E 44
I 44
D 47
	(void)kvm_nlist(nl);
E 44
	if (nl[0].n_type == 0) {
D 44
		(void) fprintf(stderr, "vmstat: %s: no namelist\n",
		    vmunix);
E 44
I 44
		(void)fprintf(stderr,
		    "vmstat: %s: no namelist\n", vmunix);
E 47
I 47
D 53
	if ((c = kvm_nlist(nl)) != 0) {
E 53
I 53
D 57
	if ((c = kvm_nlist(kd, nl)) != 0) {
E 57
I 57
	if ((c = kvm_nlist(kd, namelist)) != 0) {
E 57
E 53
		if (c > 0) {
			(void)fprintf(stderr,
D 52
			    "vmstat: undefined symbols in %s:", vmunix);
E 52
I 52
D 60
			    "vmstat: undefined symbols: ");
E 60
I 60
			    "vmstat: undefined symbols:");
E 60
E 52
D 57
			for (c = 0; c < sizeof(nl)/sizeof(nl[0]); c++)
				if (nl[c].n_type == 0)
					printf(" %s", nl[c].n_name);
E 57
I 57
			for (c = 0;
			    c < sizeof(namelist)/sizeof(namelist[0]); c++)
				if (namelist[c].n_type == 0)
D 60
					printf(" %s", namelist[c].n_name);
E 60
I 60
					fprintf(stderr, " %s",
					    namelist[c].n_name);
E 60
E 57
			(void)fputc('\n', stderr);
		} else
			(void)fprintf(stderr, "vmstat: kvm_nlist: %s\n",
D 53
			    kvm_geterr());
E 53
I 53
			    kvm_geterr(kd));
E 53
E 47
E 44
E 42
E 25
		exit(1);
	}
D 42
	dr_select = (int *)calloc(dk_ndrive, sizeof (int));
	dr_name = (char **)calloc(dk_ndrive, sizeof (char *));
#define	allocate(e, t) \
    s./**/e = (t *)calloc(dk_ndrive, sizeof (t)); \
    s1./**/e = (t *)calloc(dk_ndrive, sizeof (t));
	allocate(xfer, long);
	for (arg = buf, i = 0; i < dk_ndrive; i++) {
		dr_name[i] = arg;
		sprintf(dr_name[i], "dk%d", i);
		arg += strlen(dr_name[i]) + 1;
E 42
I 42

D 44
	/*
	 * Fork, memory, sum, and time statistics do not need everything.
	 */
E 44
I 44
	if (todo & VMSTAT) {
		char **getdrivedata();
I 47
		struct winsize winsize;
E 47

		argv = getdrivedata(argv);
I 47
		winsize.ws_row = 0;
		(void) ioctl(STDOUT_FILENO, TIOCGWINSZ, (char *)&winsize);
		if (winsize.ws_row > 0)
			winlines = winsize.ws_row;

E 47
	}

#define	BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		interval = atoi(*argv);
		if (*++argv)
			reps = atoi(*argv);
	}
#endif

I 45
	if (interval) {
		if (!reps)
			reps = -1;
D 49
	} else
		if (reps)
			interval = 1;
E 49
I 49
	} else if (reps)
		interval = 1;
E 49

I 47
D 49
#ifndef NEWVM
E 49
I 49
#ifdef notdef
E 49
E 47
E 45
E 44
	if (todo & FORKSTAT)
		doforkst();
I 47
#endif
E 47
	if (todo & MEMSTAT)
		domem();
	if (todo & SUMSTAT)
		dosum();
I 47
D 49
#ifndef NEWVM
E 49
I 49
#ifdef notdef
E 49
E 47
	if (todo & TIMESTAT)
		dotimes();
I 47
#endif
E 47
	if (todo & INTRSTAT)
		dointr();
D 44
	if (todo & VMSTAT) {
		/*
		 * Read drive names, decide which drives to report, etc.
		 */
		argc -= optind;
		argv += optind;
		i = getdrivedata(argc, argv);
		argc -= i;
		argv += i;
		dovmstat(argc > 0 ? atoi(argv[0]) : 0,
			 argc > 1 ? atoi(argv[1]) : 0);
E 42
	}
E 44
I 44
	if (todo & VMSTAT)
		dovmstat(interval, reps);
E 44
E 18
D 42
	read_names();
E 3
	time(&now);
D 8
	nintv = now - bootime;
E 8
I 8
	nintv = now - boottime;
E 8
	if (nintv <= 0 || nintv > 60*60*24*365*10) {
D 25
		printf("Time makes no sense... namelist must be wrong.\n");
E 25
I 25
		fprintf(stderr,
		    "Time makes no sense... namelist must be wrong.\n");
E 42
I 42
	exit(0);
}

D 44
usage()
{

	(void) fprintf(stderr,
"usage: vmstat [-fimst]\n\tvmstat [drive-list] [interval [count]]\n\tvmstat -z\n");
	exit(1);
}

/*
 * kread reads something from the kernel, given its nlist index.
 */
void
kread(nlx, addr, size)
	int nlx;
	char *addr;
	size_t size;
{
	char *sym;

	if (nl[nlx].n_type == 0 || nl[nlx].n_value == 0) {
		sym = nl[nlx].n_name;
		if (*sym == '_')
			sym++;
		(void) fprintf(stderr,
		    "vmstat: symbol `%s' not defined in %s\n", sym, vmunix);
E 42
E 25
		exit(1);
	}
I 16
D 42
	if (iflag) {
		dointr(nintv);
		exit(0);
E 42
I 42
	if (kvm_read(nl[nlx].n_value, addr, size) != size) {
		sym = nl[nlx].n_name;
		if (*sym == '_')
			sym++;
		(void) fprintf(stderr,
		    "vmstat: error reading `%s': %s\n", sym, kvm_geterr());
		exit(1);
E 42
	}
I 42
}

getdrivedata(argc, argv)
	int argc;
E 44
I 44
char **
getdrivedata(argv)
E 44
	char **argv;
{
	register int i;
	register char **cp;
D 44
	int ret;
E 44
	char buf[30];

D 44
	kread(X_FIRSTFREE, (char *)&firstfree, sizeof firstfree);
	kread(X_MAXFREE, (char *)&maxfree, sizeof maxfree);
	kread(X_HZ, (char *)&hz, sizeof hz);
	if (nl[X_PHZ].n_type != 0 && nl[X_PHZ].n_value != 0)
		kread(X_PHZ, (char *)&phz, sizeof phz);
	HZ = phz ? phz : hz;
	kread(X_DK_NDRIVE, (char *)&dk_ndrive, sizeof dk_ndrive);
E 44
I 44
	kread(X_DK_NDRIVE, &dk_ndrive, sizeof(dk_ndrive));
E 44
	if (dk_ndrive <= 0) {
D 44
		(void) fprintf(stderr, "vmstat: dk_ndrive %d\n", dk_ndrive);
E 44
I 44
		(void)fprintf(stderr, "vmstat: dk_ndrive %d\n", dk_ndrive);
E 44
		exit(1);
	}
D 44
	dr_select = (int *)calloc((size_t)dk_ndrive, sizeof (int));
	dr_name = (char **)malloc((size_t)dk_ndrive * sizeof (char *));
E 44
I 44
	dr_select = calloc((size_t)dk_ndrive, sizeof(int));
	dr_name = calloc((size_t)dk_ndrive, sizeof(char *));
E 44
	for (i = 0; i < dk_ndrive; i++)
		dr_name[i] = NULL;
D 44
	s.xfer = (long *)calloc((size_t)dk_ndrive, sizeof (long));
	s1.xfer = (long *)calloc((size_t)dk_ndrive, sizeof (long));
E 44
I 44
	cur.xfer = calloc((size_t)dk_ndrive, sizeof(long));
	last.xfer = calloc((size_t)dk_ndrive, sizeof(long));
E 44
D 54
	read_names();
E 54
I 54
	if (!read_names())
		exit (1);
E 54
D 44
	for (i = 0; i < dk_ndrive; i++) {
E 44
I 44
	for (i = 0; i < dk_ndrive; i++)
E 44
		if (dr_name[i] == NULL) {
D 44
			(void) sprintf(buf, "??%d", i);
E 44
I 44
			(void)sprintf(buf, "??%d", i);
E 44
			dr_name[i] = strdup(buf);
		}
D 44
	}
E 44

E 42
I 18
	/*
D 44
	 * Choose drives to be displayed.  Priority
	 * goes to (in order) drives supplied as arguments,
	 * default drives.  If everything isn't filled
	 * in and there are drives not taken care of,
	 * display the first few that fit.
E 44
I 44
	 * Choose drives to be displayed.  Priority goes to (in order) drives
	 * supplied as arguments, default drives.  If everything isn't filled
	 * in and there are drives not taken care of, display the first few
	 * that fit.
E 44
	 */
I 42
D 44
	ret = 0;
E 42
	ndrives = 0;
	while (argc > 0 && !isdigit(argv[0][0])) {
E 44
I 44
#define BACKWARD_COMPATIBILITY
	for (ndrives = 0; *argv; ++argv) {
#ifdef	BACKWARD_COMPATIBILITY
		if (isdigit(**argv))
			break;
#endif
E 44
		for (i = 0; i < dk_ndrive; i++) {
D 44
			if (strcmp(dr_name[i], argv[0]))
E 44
I 44
			if (strcmp(dr_name[i], *argv))
E 44
				continue;
			dr_select[i] = 1;
D 44
			ndrives++;
E 44
I 44
			++ndrives;
E 44
I 42
			break;
E 42
		}
I 42
D 44
		ret++;
E 42
		argc--, argv++;
E 44
	}
	for (i = 0; i < dk_ndrive && ndrives < 4; i++) {
		if (dr_select[i])
			continue;
		for (cp = defdrives; *cp; cp++)
			if (strcmp(dr_name[i], *cp) == 0) {
				dr_select[i] = 1;
D 44
				ndrives++;
E 44
I 44
				++ndrives;
E 44
				break;
			}
	}
	for (i = 0; i < dk_ndrive && ndrives < 4; i++) {
		if (dr_select[i])
			continue;
		dr_select[i] = 1;
D 44
		ndrives++;
E 44
I 44
		++ndrives;
E 44
	}
D 42
	if (argc > 1)
		iter = atoi(argv[1]);
E 18
	signal(SIGCONT, printhdr);
E 42
I 42
D 44
	return (ret);
E 44
I 44
	return(argv);
E 44
}

long
getuptime()
{
D 44
	time_t time();
	long uptime;
E 44
I 44
	static time_t now, boottime;
	time_t uptime;
E 44

	if (boottime == 0)
D 44
		kread(X_BOOTTIME, (char *)&boottime, sizeof boottime);
	(void) time(&now);
E 44
I 44
		kread(X_BOOTTIME, &boottime, sizeof(boottime));
	(void)time(&now);
E 44
	uptime = now - boottime;
	if (uptime <= 0 || uptime > 60*60*24*365*10) {
D 44
		(void) fprintf(stderr,
E 44
I 44
		(void)fprintf(stderr,
E 44
		    "vmstat: time makes no sense; namelist must be wrong.\n");
		exit(1);
	}
D 44
	return (uptime);
E 44
I 44
	return(uptime);
E 44
}

I 45
D 47
int hz;
E 47
I 47
D 48
int hz, hdrcnt;
E 48
I 48
int	hz, hdrcnt;
E 48
E 47

E 45
D 44
dovmstat(sleeptime, iter)
	int sleeptime, iter;
E 44
I 44
void
dovmstat(interval, reps)
	u_int interval;
	int reps;
E 44
{
I 44
D 48
	struct vmmeter rate;
E 48
	struct vmtotal total;
E 44
D 45
	register int i;
E 45
D 44
	long interval, t;
E 44
I 44
D 49
	time_t uptime;
E 49
I 49
	time_t uptime, halfuptime;
E 49
D 45
	long tmp;
	int deficit, hdrcnt, HZ, hz, phz;
E 45
I 45
D 47
	int deficit, hdrcnt;
E 45
	void printhdr();
E 47
I 47
D 48
	int deficit = 0;
E 48
	void needhdr();
I 48
D 49
#ifndef NEWVM
E 49
I 49
D 51
#ifndef notdef
E 49
	int deficit;
#endif
E 51
I 51
D 61
	int size;
E 61
I 61
	int mib[2], size;
E 61
E 51
E 48
E 47
E 44

D 44
	interval = getuptime();
	(void) signal(SIGCONT, printhdr);
E 42
E 16
D 19
reprint:
	lines = 20;
	/* s1 = z; */
D 3
	if (iflag==0)
E 3
D 16
printf("\
D 3
      Procs  Virtual Real         Page        Swap         Disk             Cpu\n\
RQ DW PW SW   AVM TX  FRE  RE AT PI PO FR  DE  SR I O  D0 D1 D2 D3  CS US SY ID\n\
");
	else
printf("\
 Procs     Memory            Page        Swap         Disk  Faults          Cpu\n\
 R B W   AVM  FRE  RE AT PI PO FR  DE  SR I O  D0 D1 D2 D3  IN  SY  CS US SY ID\n\
");
E 3
I 3
D 4
 Procs     Memory            Page        Swap  %s %s %s %s  Faults          Cpu\n\
 R B W   AVM  FRE  RE AT PI PO FR  DE  SR I O  %-2d %-2d %-2d %-2d  IN  SY  CS US SY ID\n\
E 4
I 4
D 5
 procs     memory            page        swap  %s %s %s %s  faults          cpu\n\
 r b w   avm  fre  re at pi po fr  de  sr i o  %-2d %-2d %-2d %-2d  in  sy  cs us sy id\n\
E 4
", dr_name[0], dr_name[1], dr_name[2], dr_name[3], dr_unit[0], dr_unit[1], dr_unit[2], dr_unit[3]);
E 5
I 5
D 7
 procs     memory            page        swap         disk  faults          cpu\n\
 r b w   avm  fre  re at pi po fr  de  sr i o  %c%d %c%d %c%d %c%d  in  sy  cs us sy id\n\
E 7
I 7
 procs     memory                       page      disk  faults          cpu\n\
D 9
 r b w   avm  fre  re at  pi  po  fr  de  sr %c%d %c%d %c%d %c%d  in  sy  cs us sy id\n\
E 7
", dr_name[0][0], dr_unit[0], dr_name[1][0], dr_unit[1], dr_name[2][0], dr_unit[2], dr_name[3][0], dr_unit[3]);
E 9
I 9
D 13
 r b w   avm  fre  %5s  pi  po  fr  de  sr %c%d %c%d %c%d %c%d  in  sy  cs us sy id\n\
", swflag ? "si so" : "re at",
E 13
I 13
 r b w   avm  fre  re at  pi  po  fr  de  sr %c%d %c%d %c%d %c%d  in  sy  cs us sy id\n",
E 13
 dr_name[0][0], dr_unit[0], dr_name[1][0], dr_unit[1], dr_name[2][0], dr_unit[2], dr_name[3][0], dr_unit[3]);
E 16
I 16
	printhdr();
E 19
E 16
E 9
E 5
E 3
loop:
I 19
	if (--lines == 0)
		printhdr();
E 19
D 2
	lseek(mf, (long)nl[X_DKBUSY].n_value, 0);
 	read(mf, &s.busy, sizeof s.busy);
 	lseek(mf, (long)nl[X_DKTIME].n_value, 0);
 	read(mf, s.etime, sizeof s.etime);
 	lseek(mf, (long)nl[X_DKNUMB].n_value, 0);
 	read(mf, s.numb, sizeof s.numb);
E 2
I 2
D 18
	lseek(mf, (long)nl[X_CPTIME].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_CPTIME].n_value, L_SET);
E 18
 	read(mf, s.time, sizeof s.time);
D 18
	lseek(mf, (long)nl[X_DKXFER].n_value, 0);
	read(mf, s.xfer, sizeof s.xfer);
E 2
	if (nintv != 1) {
		lseek(mf, (long)nl[X_SUM].n_value, 0);
		read(mf, &rate, sizeof rate);
	} else {
		lseek(mf, (long)nl[X_RATE].n_value, 0);
		read(mf, &rate, sizeof rate);
	}
	lseek(mf, (long)nl[X_TOTAL].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_DKXFER].n_value, L_SET);
	read(mf, s.xfer, dk_ndrive * sizeof (long));
	if (nintv != 1)
		lseek(mf, (long)nl[X_SUM].n_value, L_SET);
E 42
I 42
	kread(X_CPTIME, (char *)s.time, sizeof s.time);
	kread(X_DKXFER, (char *)s.xfer, sizeof *s.xfer * dk_ndrive);
	if (interval != 1)
		kread(X_SUM, (char *)&rate, sizeof rate);
E 42
	else
D 42
		lseek(mf, (long)nl[X_RATE].n_value, L_SET);
	read(mf, &rate, sizeof rate);
	lseek(mf, (long)nl[X_TOTAL].n_value, L_SET);
E 18
	read(mf, &total, sizeof total);
E 42
I 42
		kread(X_RATE, (char *)&rate, sizeof rate);
	kread(X_TOTAL, (char *)&total, sizeof total);
E 42
I 9
	osum = sum;
D 18
	lseek(mf, (long)nl[X_SUM].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_SUM].n_value, L_SET);
E 18
	read(mf, &sum, sizeof sum);
E 9
D 18
	lseek(mf, (long)nl[X_DEFICIT].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_DEFICIT].n_value, L_SET);
E 18
	read(mf, &deficit, sizeof deficit);
E 42
I 42
	kread(X_SUM, (char *)&sum, sizeof sum);
	kread(X_DEFICIT, (char *)&deficit, sizeof deficit);
E 42
I 2
	etime = 0;
E 2
D 18
	for (i=0; i < DK_NDRIVE; i++) {
E 18
I 18
D 42
	for (i=0; i < dk_ndrive; i++) {
E 42
I 42
	for (i = 0; i < dk_ndrive; i++) {
E 42
E 18
D 2
		t = s.numb[i];
		s.numb[i] -= s1.numb[i];
		s1.numb[i] = t;
E 2
I 2
		t = s.xfer[i];
		s.xfer[i] -= s1.xfer[i];
		s1.xfer[i] = t;
E 2
	}
D 42
	for (i=0; i < CPUSTATES; i++) {
E 42
I 42
	for (i = 0; i < CPUSTATES; i++) {
E 42
D 2
		for (j=0; j < DK_NSTATES; j++) {
			t = s.etime[i][j];
			s.etime[i][j] -= s1.etime[i][j];
			s1.etime[i][j] = t;
		}
E 2
I 2
		t = s.time[i];
		s.time[i] -= s1.time[i];
		s1.time[i] = t;
		etime += s.time[i];
E 2
	}
D 2
	t = 0;
	for (i=0; i < CPUSTATES; i++)
		for (j=0; j < DK_NSTATES; j++)
			t += s.etime[i][j];
	etime = t;
E 2
D 42
	if(etime == 0.)
E 42
I 42
	if (etime == 0.)
E 42
		etime = 1.;
D 3
	if (iflag)
		printf("%2d%2d%2d", total.t_rq, total.t_dw+total.t_pw,
		    total.t_sw);
	else
		printf("%2d%3d%3d%3d%3d", total.t_rq, total.t_dw, total.t_pw,
		    total.t_sw);
	if (iflag)
		printf("%6d%5d", total.t_avm/2, total.t_free/2);
	else
		printf("%6d%3d%5d", total.t_avm/2,
		    pct(total.t_avmtxt, total.t_avm), total.t_free/2);
E 3
I 3
D 42
	printf("%2d%2d%2d", total.t_rq, total.t_dw+total.t_pw, total.t_sw);
D 9
	printf("%6d%5d", total.t_avm/2, total.t_free/2);
E 3
D 7
	printf("%4d%3d%3d",
E 7
I 7
	printf("%4d%3d%4d",
E 7
	    (rate.v_pgrec - (rate.v_xsfrec+rate.v_xifrec))/nintv,
D 7
	    (rate.v_xsfrec+rate.v_xifrec)/nintv, rate.v_pgin/nintv);
	printf("%3d%3d%4d%4.1f%2d%2d", rate.v_pgout/nintv,
	    rate.v_dfree/nintv, deficit/2,
	    (60.0 * rate.v_scan) / (LOOPSIZ*nintv),
	    rate.v_swpin/nintv, rate.v_swpout/nintv);
E 7
I 7
	    (rate.v_xsfrec+rate.v_xifrec)/nintv, rate.v_pgpgin/2/nintv);
	printf("%4d%4d%4d%4d", rate.v_pgpgout/2/nintv,
	    rate.v_dfree/2/nintv, deficit/2, rate.v_scan/nintv);
E 9
I 9
#define pgtok(a) ((a)*NBPG/1024)
D 25
	printf("%6d%5d", pgtok(total.t_avm), pgtok(total.t_free));
E 25
I 25
	printf("%6d%6d", pgtok(total.t_avm), pgtok(total.t_free));
E 25
D 13
	printf("%4d%3d",
	    swflag ?
	        sum.v_swpin-osum.v_swpin :
	        (rate.v_pgrec - (rate.v_xsfrec+rate.v_xifrec))/nintv,
	    swflag ?
		sum.v_swpout-osum.v_swpout :
	        (rate.v_xsfrec+rate.v_xifrec)/nintv);
E 13
I 13
	printf("%4d%3d", (rate.v_pgrec - (rate.v_xsfrec+rate.v_xifrec))/nintv,
	    (rate.v_xsfrec+rate.v_xifrec)/nintv);
E 13
	printf("%4d", pgtok(rate.v_pgpgin)/nintv);
	printf("%4d%4d%4d%4d", pgtok(rate.v_pgpgout)/nintv,
	    pgtok(rate.v_dfree)/nintv, pgtok(deficit), rate.v_scan/nintv);
E 42
I 42
	(void) printf("%2d%2d%2d",
	    total.t_rq, total.t_dw + total.t_pw, total.t_sw);
E 44
I 44
	uptime = getuptime();
I 49
	halfuptime = uptime / 2;
E 49
D 47
	(void)signal(SIGCONT, printhdr);
E 47
I 47
	(void)signal(SIGCONT, needhdr);
E 47

D 45
	kread(X_HZ, &hz, sizeof(hz));
E 45
D 53
	if (nl[X_PHZ].n_type != 0 && nl[X_PHZ].n_value != 0)
D 45
		kread(X_PHZ, &phz, sizeof(phz));
	HZ = phz ? phz : hz;
E 45
I 45
		kread(X_PHZ, &hz, sizeof(hz));
E 53
I 53
D 57
	if (nl[X_STATHZ].n_type != 0 && nl[X_STATHZ].n_value != 0)
E 57
I 57
	if (namelist[X_STATHZ].n_type != 0 && namelist[X_STATHZ].n_value != 0)
E 57
		kread(X_STATHZ, &hz, sizeof(hz));
E 53
	if (!hz)
		kread(X_HZ, &hz, sizeof(hz));
E 45

	for (hdrcnt = 1;;) {
D 47
		if (!--hdrcnt) {
E 47
I 47
		if (!--hdrcnt)
E 47
			printhdr();
D 47
			hdrcnt = 20;
		}
E 47
		kread(X_CPTIME, cur.time, sizeof(cur.time));
D 55
		kread(X_DKXFER, cur.xfer, sizeof(*cur.xfer * dk_ndrive));
E 55
I 55
		kread(X_DKXFER, cur.xfer, sizeof(*cur.xfer) * dk_ndrive);
E 55
D 48
		if (uptime != 1)
			kread(X_SUM, &rate, sizeof(rate));
		else
			kread(X_RATE, &rate, sizeof(rate));
		kread(X_TOTAL, &total, sizeof(total));
E 48
		kread(X_SUM, &sum, sizeof(sum));
I 47
D 48
#ifndef NEWVM
E 48
I 48
D 51
		kread(X_TOTAL, &total, sizeof(total));
D 49
#ifdef NEWVM
E 49
		kread(X_VMSTAT, &vm_stat, sizeof(vm_stat));
D 49
#else
E 49
I 49
#ifdef notdef
E 49
E 48
E 47
		kread(X_DEFICIT, &deficit, sizeof(deficit));
I 47
#endif
E 47
D 45
		etime = 0;
		for (i = 0; i < dk_ndrive; i++) {
			tmp = cur.xfer[i];
			cur.xfer[i] -= last.xfer[i];
			last.xfer[i] = tmp;
		}
		for (i = 0; i < CPUSTATES; i++) {
			tmp = cur.time[i];
			cur.time[i] -= last.time[i];
			last.time[i] = tmp;
			etime += cur.time[i];
		}
		if (etime == 0.)
			etime = 1.;
E 45
D 48
		(void)printf("%2d%2d%2d",
E 48
I 48
		(void)printf("%2d %1d %1d ",
E 51
I 51
		size = sizeof(total);
D 61
		if (getkerninfo(KINFO_METER, &total, &size, 0) < 0) {
E 61
I 61
		mib[0] = CTL_VM;
		mib[1] = VM_METER;
		if (sysctl(mib, 2, &total, &size, NULL, 0) < 0) {
E 61
			printf("Can't get kerninfo: %s\n", strerror(errno));
			bzero(&total, sizeof(total));
		}
		(void)printf("%2d%2d%2d",
E 51
E 48
D 63
		    total.t_rq, total.t_dw + total.t_pw, total.t_sw);
E 63
I 63
		    total.t_rq - 1, total.t_dw + total.t_pw, total.t_sw);
E 63
E 44
D 51
#define pgtok(a) ((a)*NBPG >> 10)
E 51
I 51
#define pgtok(a) ((a) * sum.v_page_size >> 10)
E 51
I 49
#define	rate(x)	(((x) + halfuptime) / uptime)	/* round */
E 49
D 44
	(void) printf("%6ld%6ld", pgtok(total.t_avm), pgtok(total.t_free));
	(void) printf("%4lu%3lu",
	    (rate.v_pgrec - (rate.v_xsfrec+rate.v_xifrec)) / interval,
	    (rate.v_xsfrec+rate.v_xifrec) / interval);
	(void) printf("%4lu", pgtok(rate.v_pgpgin) / interval);
	(void) printf("%4lu%4lu%4d%4lu", pgtok(rate.v_pgpgout) / interval,
	    pgtok(rate.v_dfree) / interval,
	    pgtok(deficit), rate.v_scan / interval);
E 42
E 9
E 7
D 12
	etime /= 60.;
E 12
I 12
D 13
	etime /= (float) hz;
E 13
I 13
D 18
	etime /= (float) HZ;
E 13
E 12
D 7
	printf(" ");
E 7
	for(i=0; i<4; i++)
		stats(i);
E 18
I 18
	etime /= (float)HZ;
	for (i = 0; i < dk_ndrive; i++)
		if (dr_select[i])
			stats(i);
I 23
D 25
#define	INTS(x)	((x) - (hz + phz))
E 25
E 23
E 18
I 9
D 13
#ifdef sun
	printf("%4d%4d", (rate.v_intr/nintv), rate.v_syscall/nintv);
#endif
#ifdef vax
E 9
D 3
	if (iflag)
		printf("%4d%4d", (rate.v_intr/nintv) - HZ,
		    rate.v_syscall/nintv);
E 3
I 3
	printf("%4d%4d", (rate.v_intr/nintv) - hz, rate.v_syscall/nintv);
I 9
#endif
E 9
E 3
	printf("%4d", rate.v_swtch/nintv);
E 13
I 13
D 42
	printf("%4d%4d%4d", INTS(rate.v_intr/nintv), rate.v_syscall/nintv,
	    rate.v_swtch/nintv);
E 13
	for(i=0; i<CPUSTATES; i++) {
E 42
I 42
	(void) printf("%4lu%4lu%4lu", INTS(rate.v_intr / interval),
	    rate.v_syscall / interval, rate.v_swtch / interval);
	for(i = 0; i < CPUSTATES; i++) {
E 42
		float f = stat1(i);
		if (i == 0) {		/* US+NI */
			i++;
			f += stat1(i);
E 44
I 44
D 48
		(void)printf("%6ld%6ld",
E 48
I 48
D 51
		(void)printf("%5ld %5ld ",
E 51
I 51
		(void)printf("%6ld%6ld ",
E 51
E 48
		    pgtok(total.t_avm), pgtok(total.t_free));
D 48
		(void)printf("%4lu%3lu",
		    (rate.v_pgrec - (rate.v_xsfrec+rate.v_xifrec)) / uptime,
		    (rate.v_xsfrec+rate.v_xifrec) / uptime);
		(void)printf("%4lu", pgtok(rate.v_pgpgin) / uptime);
		(void)printf("%4lu%4lu%4d%4lu", pgtok(rate.v_pgpgout) / uptime,
		    pgtok(rate.v_dfree) / uptime,
		    pgtok(deficit), rate.v_scan / uptime);
E 48
I 48
#ifdef NEWVM
D 49
		(void)printf("%4lu ",
		    (vm_stat.faults - ostat.faults) / uptime);
E 49
I 49
D 51
		(void)printf("%4lu ", rate(vm_stat.faults - ostat.faults));
E 51
I 51
		(void)printf("%4lu ", rate(sum.v_faults - osum.v_faults));
E 51
E 49
		(void)printf("%3lu ",
D 49
		    (vm_stat.reactivations - ostat.reactivations) / uptime);
		(void)printf("%3lu ",
		    (vm_stat.pageins - ostat.pageins) / uptime);
E 49
I 49
D 51
		    rate(vm_stat.reactivations - ostat.reactivations));
		(void)printf("%3lu ", rate(vm_stat.pageins - ostat.pageins));
E 51
I 51
		    rate(sum.v_reactivated - osum.v_reactivated));
		(void)printf("%3lu ", rate(sum.v_pageins - osum.v_pageins));
E 51
E 49
		(void)printf("%3lu %3lu ",
D 49
		    (vm_stat.pageouts - ostat.pageouts) / uptime, 0);
E 49
I 49
D 51
		    rate(vm_stat.pageouts - ostat.pageouts), 0);
E 51
I 51
		    rate(sum.v_pageouts - osum.v_pageouts), 0);
E 51
E 49
#else
		(void)printf("%3lu %2lu ",
D 49
		    (sum.v_pgrec - (sum.v_xsfrec+sum.v_xifrec) -
		    (osum.v_pgrec - (osum.v_xsfrec+osum.v_xifrec))) / uptime,
		    (sum.v_xsfrec + sum.v_xifrec -
		    osum.v_xsfrec - osum.v_xifrec) / uptime);
E 49
I 49
		    rate(sum.v_pgrec - (sum.v_xsfrec+sum.v_xifrec) -
		    (osum.v_pgrec - (osum.v_xsfrec+osum.v_xifrec))),
		    rate(sum.v_xsfrec + sum.v_xifrec -
		    osum.v_xsfrec - osum.v_xifrec));
E 49
		(void)printf("%3lu ",
D 49
		    pgtok(sum.v_pgpgin - osum.v_pgpgin) / uptime);
E 49
I 49
		    rate(pgtok(sum.v_pgpgin - osum.v_pgpgin)));
E 49
		(void)printf("%3lu %3lu ",
D 49
		    pgtok(sum.v_pgpgout - osum.v_pgpgout) / uptime,
		    pgtok(sum.v_dfree - osum.v_dfree) / uptime);
E 49
I 49
		    rate(pgtok(sum.v_pgpgout - osum.v_pgpgout)),
		    rate(pgtok(sum.v_dfree - osum.v_dfree)));
E 49
		(void)printf("%3d ", pgtok(deficit));
#endif
D 49
		(void)printf("%3lu ", (sum.v_scan - osum.v_scan) / uptime);
E 49
I 49
		(void)printf("%3lu ", rate(sum.v_scan - osum.v_scan));
E 49
E 48
D 45
		etime /= (float)HZ;
		for (i = 0; i < dk_ndrive; i++)
			if (dr_select[i])
				stats(i);
#define	INTS(x)	((x) - (hz + phz))
		(void)printf("%4lu%4lu%4lu", INTS(rate.v_intr / uptime),
E 45
I 45
		dkstats();
D 48
		(void)printf("%4lu%4lu%4lu", rate.v_intr / uptime,
E 45
		    rate.v_syscall / uptime, rate.v_swtch / uptime);
E 48
I 48
		(void)printf("%4lu %4lu %3lu ",
D 49
		    (sum.v_intr - osum.v_intr) / uptime,
		    (sum.v_syscall - osum.v_syscall) / uptime,
		    (sum.v_swtch - osum.v_swtch ) / uptime);
E 49
I 49
		    rate(sum.v_intr - osum.v_intr),
		    rate(sum.v_syscall - osum.v_syscall),
		    rate(sum.v_swtch - osum.v_swtch));
E 49
E 48
D 45
		for (i = 0; i < CPUSTATES; i++) {
			double f;

			f = stat1(i);
			if (i == 0) {		/* US+NI */
				i++;
				f += stat1(i);
			}
			(void)printf("%3.0f", f);
E 44
		}
E 45
I 45
		cpustats();
E 45
D 42
		printf("%3.0f", f);
E 42
I 42
D 44
		(void) printf("%3.0f", f);
E 44
I 44
		(void)printf("\n");
		(void)fflush(stdout);
D 49
		uptime = 1;
E 49
D 45
		if (--reps <= 0)
E 45
I 45
		if (reps >= 0 && --reps <= 0)
E 45
			break;
I 48
		osum = sum;
D 51
		ostat = vm_stat;
E 51
I 49
		uptime = interval;
		/*
		 * We round upward to avoid losing low-frequency events
		 * (i.e., >= 1 per interval but < 1 per second).
		 */
		halfuptime = (uptime + 1) / 2;
E 49
E 48
D 45
		if (interval)
			sleep(interval);
E 45
I 45
		(void)sleep(interval);
E 45
E 44
E 42
	}
D 42
	printf("\n");
	fflush(stdout);
D 25
contin:
E 25
	nintv = 1;
D 19
	--iter;
	if(iter)
	if(argc > 0) {
E 19
I 19
	if (--iter &&argc > 0) {
E 19
		sleep(atoi(argv[0]));
E 42
I 42
D 44
	(void) printf("\n");
	(void) fflush(stdout);
	interval = 1;
	if (iter && --iter == 0)
		return;
	if (sleeptime) {
		sleep((unsigned)sleeptime);
E 42
D 19
		if (--lines <= 0)
			goto reprint;
E 19
		goto loop;
	}
E 44
}

I 42
D 47
void
E 47
E 42
I 16
printhdr()
{
D 18
printf("\
 procs     memory                       page      disk  faults          cpu\n\
 r b w   avm  fre  re at  pi  po  fr  de  sr %c%d %c%d %c%d %c%d  in  sy  cs us sy id\n",
 dr_name[0][0], dr_unit[0], dr_name[1][0], dr_unit[1], dr_name[2][0], dr_unit[2], dr_name[3][0], dr_unit[3]);
E 18
I 18
D 44
	register int i, j;
E 44
I 44
	register int i;
E 44

D 25
	printf(" procs    memory              page           ");
E 25
I 25
D 42
	printf(" procs     memory              page           ");
E 42
I 42
D 44
	(void) printf(" procs     memory              page           ");
E 42
E 25
	i = (ndrives * 3 - 6) / 2;
	if (i < 0)
		i = 0;
	for (j = 0; j < i; j++)
D 42
		putchar(' ');
	printf("faults");
E 42
I 42
		(void) putchar(' ');
	(void) printf("faults");
E 42
	i = ndrives * 3 - 6 - i;
	for (j = 0; j < i; j++)
D 42
		putchar(' ');
	printf("               cpu\n");
D 25
	printf(" r b w   avm  fre  re at  pi  po  fr  de  sr ");
E 25
I 25
	printf(" r b w   avm   fre  re at  pi  po  fr  de  sr ");
E 42
I 42
		(void) putchar(' ');
	(void) printf("               cpu\n");
	(void) printf(" r b w   avm   fre  re at  pi  po  fr  de  sr ");
E 44
I 44
D 48
	(void)printf(" procs   memory     page%*s", 22, "");
E 48
I 48
	(void)printf(" procs   memory     page%*s", 20, "");
E 48
	if (ndrives > 1)
D 48
		(void)printf("disks %*s faults     cpu\n",
E 48
I 48
		(void)printf("disks %*s  faults      cpu\n",
E 48
		   ndrives * 3 - 6, "");
	else
D 48
		(void)printf("%*s faults     cpu\n", ndrives * 3, "");
E 48
I 48
		(void)printf("%*s  faults      cpu\n", ndrives * 3, "");
#ifndef NEWVM
E 48
	(void)printf(" r b w   avm   fre  re at  pi  po  fr  de  sr ");
I 48
#else
	(void)printf(" r b w   avm   fre  flt  re  pi  po  fr  sr ");
#endif
E 48
E 44
E 42
E 25
	for (i = 0; i < dk_ndrive; i++)
		if (dr_select[i])
D 42
			printf("%c%c ", dr_name[i][0], dr_name[i][2]);	
	printf(" in  sy  cs us sy id\n");
E 42
I 42
D 44
			(void) printf("%c%c ", dr_name[i][0],
E 44
I 44
			(void)printf("%c%c ", dr_name[i][0],
E 44
			    dr_name[i][strlen(dr_name[i]) - 1]);
D 44
	(void) printf(" in  sy  cs us sy id\n");
E 42
I 19
	lines = 19;
E 44
I 44
D 48
	(void)printf(" in  sy  cs us sy id\n");
E 48
I 48
	(void)printf("  in   sy  cs us sy id\n");
E 48
I 47
	hdrcnt = winlines - 2;
E 47
E 44
E 19
E 18
}

I 47
/*
 * Force a header to be prepended to the next output.
 */
E 47
I 44
void
I 47
needhdr()
{

	hdrcnt = 1;
}

D 49
#ifndef NEWVM
E 49
I 49
#ifdef notdef
E 49
void
E 47
E 44
E 16
D 3
#ifdef ERNIE
E 3
dotimes()
{
I 44
	u_int pgintime, rectime;
E 44

D 18
	lseek(mf, (long)nl[X_REC].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_REC].n_value, L_SET);
E 18
	read(mf, &s.rectime, sizeof s.rectime);
D 18
	lseek(mf, (long)nl[X_PGIN].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_PGIN].n_value, L_SET);
E 18
	read(mf, &s.pgintime, sizeof s.pgintime);
D 18
	lseek(mf, (long)nl[X_SUM].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_SUM].n_value, L_SET);
E 18
	read(mf, &sum, sizeof sum);
	printf("%d reclaims, %d total time (usec)\n", sum.v_pgrec, s.rectime);
	printf("average: %d usec / reclaim\n", s.rectime/sum.v_pgrec);
	printf("\n");
	printf("%d page ins, %d total time (msec)\n",sum.v_pgin, s.pgintime/10);
	printf("average: %8.1f msec / page in\n", s.pgintime/(sum.v_pgin*10.0));
E 42
I 42
D 44
	kread(X_REC, (char *)&s.rectime, sizeof s.rectime);
	kread(X_PGIN, (char *)&s.pgintime, sizeof s.pgintime);
	kread(X_SUM, (char *)&sum, sizeof sum);
	(void) printf("%u reclaims, %u total time (usec)\n",
	    sum.v_pgrec, s.rectime);
	(void) printf("average: %u usec / reclaim\n", s.rectime / sum.v_pgrec);
	(void) printf("\n");
	(void) printf("%u page ins, %u total time (msec)\n",
	    sum.v_pgin, s.pgintime / 10);
	(void) printf("average: %8.1f msec / page in\n",
	    s.pgintime / (sum.v_pgin * 10.0));
E 44
I 44
	kread(X_REC, &rectime, sizeof(rectime));
	kread(X_PGIN, &pgintime, sizeof(pgintime));
	kread(X_SUM, &sum, sizeof(sum));
	(void)printf("%u reclaims, %u total time (usec)\n",
	    sum.v_pgrec, rectime);
	(void)printf("average: %u usec / reclaim\n", rectime / sum.v_pgrec);
	(void)printf("\n");
	(void)printf("%u page ins, %u total time (msec)\n",
	    sum.v_pgin, pgintime / 10);
	(void)printf("average: %8.1f msec / page in\n",
	    pgintime / (sum.v_pgin * 10.0));
E 44
E 42
}
I 47
#endif
E 47
D 3
#endif
E 3

I 42
pct(top, bot)
	long top, bot;
{
I 59
	long ans;

E 59
D 44

E 44
	if (bot == 0)
D 44
		return (0);
	return ((top * 100) / bot);
E 44
I 44
		return(0);
D 59
	return((top * 100) / bot);
E 59
I 59
	ans = (quad_t)top * 100 / bot;
	return (ans);
E 59
E 44
}

#define	PCT(top, bot) pct((long)(top), (long)(bot))

E 42
I 26
#if defined(tahoe)
D 42
#include <tahoe/cpu.h>
E 42
I 42
#include <machine/cpu.h>
E 42
#endif

I 44
void
E 44
E 26
I 22
D 23
/* SHOULD BE AVAILABLE IN <sys/text.h> */
/*
 * Statistics
 */
struct xstats {
	u_long	alloc;			/* calls to xalloc */
	u_long	alloc_inuse;		/*	found in use/sticky */
	u_long	alloc_cachehit;		/*	found in cache */
	u_long	alloc_cacheflush;	/*	flushed cached text */
	u_long	alloc_unused;		/*	flushed unused cached text */
	u_long	free;			/* calls to xfree */
	u_long	free_inuse;		/*	still in use/sticky */
	u_long	free_cache;		/*	placed in cache */
	u_long	free_cacheswap;		/*	swapped out to place in cache */
};
/* END SHOULD BE AVAILABLE... */

E 23
E 22
dosum()
{
I 14
D 18
	struct nchstats statbuf;
E 18
I 18
	struct nchstats nchstats;
I 47
#ifndef NEWVM
E 47
I 22
D 24
	struct xstats  xstats;
E 24
I 24
	struct xstats xstats;
I 47
#endif
E 47
E 24
E 22
E 18
	long nchtotal;
I 24
#if defined(tahoe)
	struct keystats keystats;
#endif
E 24
E 14

D 18
	lseek(mf, (long)nl[X_SUM].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_SUM].n_value, L_SET);
E 18
	read(mf, &sum, sizeof sum);
	printf("%9d swap ins\n", sum.v_swpin);
	printf("%9d swap outs\n", sum.v_swpout);
	printf("%9d pages swapped in\n", sum.v_pswpin / CLSIZE);
	printf("%9d pages swapped out\n", sum.v_pswpout / CLSIZE);
	printf("%9d total address trans. faults taken\n", sum.v_faults);
	printf("%9d page ins\n", sum.v_pgin);
	printf("%9d page outs\n", sum.v_pgout);
I 7
	printf("%9d pages paged in\n", sum.v_pgpgin);
	printf("%9d pages paged out\n", sum.v_pgpgout);
	printf("%9d sequential process pages freed\n", sum.v_seqfree);
I 23
D 25
#define	nz(x)	((x) ? (x) : 1)
E 25
E 23
E 7
D 11
	printf("%9d total reclaims\n", sum.v_pgrec);
E 11
I 11
	printf("%9d total reclaims (%d%% fast)\n", sum.v_pgrec,
D 23
	    (sum.v_fastpgrec * 100) / (sum.v_pgrec == 0 ? 1 : sum.v_pgrec));
E 23
I 23
D 25
	    (sum.v_fastpgrec * 100) / nz(sum.v_pgrec));
E 25
I 25
	    pct(sum.v_fastpgrec, sum.v_pgrec));
E 25
E 23
E 11
	printf("%9d reclaims from free list\n", sum.v_pgfrec);
	printf("%9d intransit blocking page faults\n", sum.v_intrans);
	printf("%9d zero fill pages created\n", sum.v_nzfod / CLSIZE);
	printf("%9d zero fill page faults\n", sum.v_zfod / CLSIZE);
	printf("%9d executable fill pages created\n", sum.v_nexfod / CLSIZE);
	printf("%9d executable fill page faults\n", sum.v_exfod / CLSIZE);
	printf("%9d swap text pages found in free list\n", sum.v_xsfrec);
	printf("%9d inode text pages found in free list\n", sum.v_xifrec);
	printf("%9d file fill pages created\n", sum.v_nvrfod / CLSIZE);
	printf("%9d file fill page faults\n", sum.v_vrfod / CLSIZE);
	printf("%9d pages examined by the clock daemon\n", sum.v_scan);
	printf("%9d revolutions of the clock hand\n", sum.v_rev);
	printf("%9d pages freed by the clock daemon\n", sum.v_dfree / CLSIZE);
	printf("%9d cpu context switches\n", sum.v_swtch);
	printf("%9d device interrupts\n", sum.v_intr);
I 16
	printf("%9d software interrupts\n", sum.v_soft);
E 42
I 42
D 44
	kread(X_SUM, (char *)&sum, sizeof sum);
	(void) printf("%9u swap ins\n", sum.v_swpin);
	(void) printf("%9u swap outs\n", sum.v_swpout);
	(void) printf("%9u pages swapped in\n", sum.v_pswpin / CLSIZE);
	(void) printf("%9u pages swapped out\n", sum.v_pswpout / CLSIZE);
	(void) printf("%9u total address trans. faults taken\n", sum.v_faults);
	(void) printf("%9u page ins\n", sum.v_pgin);
	(void) printf("%9u page outs\n", sum.v_pgout);
	(void) printf("%9u pages paged in\n", sum.v_pgpgin);
	(void) printf("%9u pages paged out\n", sum.v_pgpgout);
	(void) printf("%9u sequential process pages freed\n", sum.v_seqfree);
	(void) printf("%9u total reclaims (%d%% fast)\n", sum.v_pgrec,
E 44
I 44
	kread(X_SUM, &sum, sizeof(sum));
I 48
D 51
#ifdef NEWVM
	kread(X_VMSTAT, &vm_stat, sizeof(vm_stat));
#else
E 51
I 51
	(void)printf("%9u cpu context switches\n", sum.v_swtch);
	(void)printf("%9u device interrupts\n", sum.v_intr);
	(void)printf("%9u software interrupts\n", sum.v_soft);
#ifdef vax
	(void)printf("%9u pseudo-dma dz interrupts\n", sum.v_pdma);
#endif
	(void)printf("%9u traps\n", sum.v_trap);
	(void)printf("%9u system calls\n", sum.v_syscall);
	(void)printf("%9u total faults taken\n", sum.v_faults);
E 51
E 48
	(void)printf("%9u swap ins\n", sum.v_swpin);
	(void)printf("%9u swap outs\n", sum.v_swpout);
	(void)printf("%9u pages swapped in\n", sum.v_pswpin / CLSIZE);
	(void)printf("%9u pages swapped out\n", sum.v_pswpout / CLSIZE);
D 51
	(void)printf("%9u total address trans. faults taken\n", sum.v_faults);
	(void)printf("%9u page ins\n", sum.v_pgin);
	(void)printf("%9u page outs\n", sum.v_pgout);
E 51
I 51
	(void)printf("%9u page ins\n", sum.v_pageins);
	(void)printf("%9u page outs\n", sum.v_pageouts);
E 51
	(void)printf("%9u pages paged in\n", sum.v_pgpgin);
	(void)printf("%9u pages paged out\n", sum.v_pgpgout);
I 51
	(void)printf("%9u pages reactivated\n", sum.v_reactivated);
	(void)printf("%9u intransit blocking page faults\n", sum.v_intrans);
	(void)printf("%9u zero fill pages created\n", sum.v_nzfod / CLSIZE);
	(void)printf("%9u zero fill page faults\n", sum.v_zfod / CLSIZE);
	(void)printf("%9u pages examined by the clock daemon\n", sum.v_scan);
	(void)printf("%9u revolutions of the clock hand\n", sum.v_rev);
#ifdef NEWVM
	(void)printf("%9u VM object cache lookups\n", sum.v_lookups);
	(void)printf("%9u VM object hits\n", sum.v_hits);
	(void)printf("%9u total VM faults taken\n", sum.v_vm_faults);
	(void)printf("%9u copy-on-write faults\n", sum.v_cow_faults);
	(void)printf("%9u pages freed by daemon\n", sum.v_dfree);
	(void)printf("%9u pages freed by exiting processes\n", sum.v_pfree);
	(void)printf("%9u pages free\n", sum.v_free_count);
	(void)printf("%9u pages wired down\n", sum.v_wire_count);
	(void)printf("%9u pages active\n", sum.v_active_count);
	(void)printf("%9u pages inactive\n", sum.v_inactive_count);
	(void)printf("%9u bytes per page\n", sum.v_page_size);
I 65
	(void)printf("%9u target inactive pages\n", sum.v_inactive_target);
	(void)printf("%9u target free pages\n", sum.v_free_target);
	(void)printf("%9u minimum free pages\n", sum.v_free_min);
E 65
#else
E 51
	(void)printf("%9u sequential process pages freed\n", sum.v_seqfree);
	(void)printf("%9u total reclaims (%d%% fast)\n", sum.v_pgrec,
E 44
	    PCT(sum.v_fastpgrec, sum.v_pgrec));
D 44
	(void) printf("%9u reclaims from free list\n", sum.v_pgfrec);
	(void) printf("%9u intransit blocking page faults\n", sum.v_intrans);
	(void) printf("%9u zero fill pages created\n", sum.v_nzfod / CLSIZE);
	(void) printf("%9u zero fill page faults\n", sum.v_zfod / CLSIZE);
	(void) printf("%9u executable fill pages created\n",
E 44
I 44
	(void)printf("%9u reclaims from free list\n", sum.v_pgfrec);
D 51
	(void)printf("%9u intransit blocking page faults\n", sum.v_intrans);
	(void)printf("%9u zero fill pages created\n", sum.v_nzfod / CLSIZE);
	(void)printf("%9u zero fill page faults\n", sum.v_zfod / CLSIZE);
E 51
	(void)printf("%9u executable fill pages created\n",
E 44
	    sum.v_nexfod / CLSIZE);
D 44
	(void) printf("%9u executable fill page faults\n",
E 44
I 44
	(void)printf("%9u executable fill page faults\n",
E 44
	    sum.v_exfod / CLSIZE);
D 44
	(void) printf("%9u swap text pages found in free list\n",
E 44
I 44
	(void)printf("%9u swap text pages found in free list\n",
E 44
	    sum.v_xsfrec);
D 44
	(void) printf("%9u inode text pages found in free list\n",
E 44
I 44
	(void)printf("%9u inode text pages found in free list\n",
E 44
	    sum.v_xifrec);
D 44
	(void) printf("%9u file fill pages created\n", sum.v_nvrfod / CLSIZE);
	(void) printf("%9u file fill page faults\n", sum.v_vrfod / CLSIZE);
	(void) printf("%9u pages examined by the clock daemon\n", sum.v_scan);
	(void) printf("%9u revolutions of the clock hand\n", sum.v_rev);
	(void) printf("%9u pages freed by the clock daemon\n",
E 44
I 44
	(void)printf("%9u file fill pages created\n", sum.v_nvrfod / CLSIZE);
	(void)printf("%9u file fill page faults\n", sum.v_vrfod / CLSIZE);
D 51
	(void)printf("%9u pages examined by the clock daemon\n", sum.v_scan);
	(void)printf("%9u revolutions of the clock hand\n", sum.v_rev);
E 51
	(void)printf("%9u pages freed by the clock daemon\n",
E 44
	    sum.v_dfree / CLSIZE);
I 48
#endif
E 48
D 44
	(void) printf("%9u cpu context switches\n", sum.v_swtch);
	(void) printf("%9u device interrupts\n", sum.v_intr);
	(void) printf("%9u software interrupts\n", sum.v_soft);
E 44
I 44
D 51
	(void)printf("%9u cpu context switches\n", sum.v_swtch);
	(void)printf("%9u device interrupts\n", sum.v_intr);
	(void)printf("%9u software interrupts\n", sum.v_soft);
E 44
E 42
I 18
#ifdef vax
E 18
E 16
D 21
	printf("%9d pseduo-dma dz interrupts\n", sum.v_pdma);
E 21
I 21
D 42
	printf("%9d pseudo-dma dz interrupts\n", sum.v_pdma);
E 42
I 42
D 44
	(void) printf("%9u pseudo-dma dz interrupts\n", sum.v_pdma);
E 44
I 44
	(void)printf("%9u pseudo-dma dz interrupts\n", sum.v_pdma);
E 44
E 42
E 21
I 18
#endif
E 18
D 42
	printf("%9d traps\n", sum.v_trap);
	printf("%9d system calls\n", sum.v_syscall);
I 14
	lseek(mf, (long)nl[X_NCHSTATS].n_value, 0);
D 18
	read(mf, &statbuf, sizeof statbuf);
	nchtotal = statbuf.ncs_goodhits + statbuf.ncs_badhits +
D 15
		statbuf.ncs_miss + statbuf.ncs_long;
E 15
I 15
	    statbuf.ncs_falsehits + statbuf.ncs_miss + statbuf.ncs_long;
E 18
I 18
	read(mf, &nchstats, sizeof nchstats);
E 42
I 42
D 44
	(void) printf("%9u traps\n", sum.v_trap);
	(void) printf("%9u system calls\n", sum.v_syscall);
	kread(X_NCHSTATS, (char *)&nchstats, sizeof nchstats);
E 44
I 44
	(void)printf("%9u traps\n", sum.v_trap);
	(void)printf("%9u system calls\n", sum.v_syscall);
I 48
#ifdef NEWVM
	(void)printf("%9u bytes per page\n", vm_stat.pagesize);
	(void)printf("%9u pages free\n", vm_stat.free_count);
	(void)printf("%9u pages active\n", vm_stat.active_count);
	(void)printf("%9u pages inactive\n", vm_stat.inactive_count);
	(void)printf("%9u pages wired down\n", vm_stat.wire_count);
	(void)printf("%9u zero-fill pages\n", vm_stat.zero_fill_count);
	(void)printf("%9u pages reactivated\n", vm_stat.reactivations);
	(void)printf("%9u pageins\n", vm_stat.pageins);
	(void)printf("%9u pageouts\n", vm_stat.pageouts);
	(void)printf("%9u VM faults\n", vm_stat.faults);
	(void)printf("%9u copy-on-write faults\n", vm_stat.cow_faults);
	(void)printf("%9u VM object cache lookups\n", vm_stat.lookups);
	(void)printf("%9u VM object hits\n", vm_stat.hits);
#endif

E 51
E 48
	kread(X_NCHSTATS, &nchstats, sizeof(nchstats));
E 44
E 42
D 35
	nchtotal = nchstats.ncs_goodhits + nchstats.ncs_badhits +
	    nchstats.ncs_falsehits + nchstats.ncs_miss + nchstats.ncs_long;
E 18
E 15
	printf("%9d total name lookups", nchtotal);
I 15
D 23
#define	nz(x)	((x) ? (x) : 1)
E 23
E 15
	printf(" (cache hits %d%% system %d%% per-process)\n",
D 15
		statbuf.ncs_goodhits * 100 / nchtotal,
		statbuf.ncs_pass2 * 100 / nchtotal);
E 15
I 15
D 18
	    statbuf.ncs_goodhits * 100 / nz(nchtotal),
	    statbuf.ncs_pass2 * 100 / nz(nchtotal));
E 18
I 18
D 25
	    nchstats.ncs_goodhits * 100 / nz(nchtotal),
	    nchstats.ncs_pass2 * 100 / nz(nchtotal));
E 25
I 25
	    pct(nchstats.ncs_goodhits, nchtotal),
E 35
I 35
	nchtotal = nchstats.ncs_goodhits + nchstats.ncs_neghits +
	    nchstats.ncs_badhits + nchstats.ncs_falsehits +
	    nchstats.ncs_miss + nchstats.ncs_long;
D 42
	printf("%9d total name lookups\n", nchtotal);
	printf("%9s cache hits (%d%% pos + %d%% neg) system %d%% per-process\n",
	    "", pct(nchstats.ncs_goodhits, nchtotal),
	    pct(nchstats.ncs_neghits, nchtotal),
E 35
	    pct(nchstats.ncs_pass2, nchtotal));
E 25
E 18
D 35
	printf("%9s badhits %d, falsehits %d, toolong %d\n", "",
D 18
	    statbuf.ncs_badhits, statbuf.ncs_falsehits, statbuf.ncs_long);
E 18
I 18
	    nchstats.ncs_badhits, nchstats.ncs_falsehits, nchstats.ncs_long);
E 35
I 35
	printf("%9s deletions %d%%, falsehits %d%%, toolong %d%%\n", "",
	    pct(nchstats.ncs_badhits, nchtotal),
	    pct(nchstats.ncs_falsehits, nchtotal),
	    pct(nchstats.ncs_long, nchtotal));
E 35
I 22
	lseek(mf, (long)nl[X_XSTATS].n_value, 0);
	read(mf, &xstats, sizeof xstats);
	printf("%9d total calls to xalloc (cache hits %d%%)\n",
D 25
	    xstats.alloc, xstats.alloc_cachehit * 100 / nz(xstats.alloc));
E 25
I 25
	    xstats.alloc, pct(xstats.alloc_cachehit, xstats.alloc));
E 25
	printf("%9s sticky %d flushed %d unused %d\n", "",
E 42
I 42
D 44
	(void) printf("%9ld total name lookups\n", nchtotal);
	(void) printf(
E 44
I 44
	(void)printf("%9ld total name lookups\n", nchtotal);
	(void)printf(
E 44
	    "%9s cache hits (%d%% pos + %d%% neg) system %d%% per-process\n",
	    "", PCT(nchstats.ncs_goodhits, nchtotal),
	    PCT(nchstats.ncs_neghits, nchtotal),
	    PCT(nchstats.ncs_pass2, nchtotal));
D 44
	(void) printf("%9s deletions %d%%, falsehits %d%%, toolong %d%%\n", "",
E 44
I 44
	(void)printf("%9s deletions %d%%, falsehits %d%%, toolong %d%%\n", "",
E 44
	    PCT(nchstats.ncs_badhits, nchtotal),
	    PCT(nchstats.ncs_falsehits, nchtotal),
	    PCT(nchstats.ncs_long, nchtotal));
I 47
#ifndef NEWVM
E 47
D 44
	kread(X_XSTATS, (char *)&xstats, sizeof xstats);
	(void) printf("%9lu total calls to xalloc (cache hits %d%%)\n",
E 44
I 44
	kread(X_XSTATS, &xstats, sizeof(xstats));
	(void)printf("%9lu total calls to xalloc (cache hits %d%%)\n",
E 44
	    xstats.alloc, PCT(xstats.alloc_cachehit, xstats.alloc));
D 44
	(void) printf("%9s sticky %lu flushed %lu unused %lu\n", "",
E 44
I 44
	(void)printf("%9s sticky %lu flushed %lu unused %lu\n", "",
E 44
E 42
	    xstats.alloc_inuse, xstats.alloc_cacheflush, xstats.alloc_unused);
D 42
	printf("%9d total calls to xfree", xstats.free);
	printf(" (sticky %d cached %d swapped %d)\n",
E 42
I 42
D 44
	(void) printf("%9lu total calls to xfree", xstats.free);
	(void) printf(" (sticky %lu cached %lu swapped %lu)\n",
E 44
I 44
	(void)printf("%9lu total calls to xfree", xstats.free);
	(void)printf(" (sticky %lu cached %lu swapped %lu)\n",
E 44
E 42
	    xstats.free_inuse, xstats.free_cache, xstats.free_cacheswap);
I 47
#endif
E 47
I 24
#if defined(tahoe)
D 42
	lseek(mf, (long)nl[X_CKEYSTATS].n_value, 0);
	read(mf, &keystats, sizeof keystats);
	printf("%9d %s (free %d%% norefs %d%% taken %d%% shared %d%%)\n",
E 42
I 42
D 44
	kread(X_CKEYSTATS, (char *)&keystats, sizeof keystats);
	(void) printf("%9d %s (free %d%% norefs %d%% taken %d%% shared %d%%)\n",
E 44
I 44
	kread(X_CKEYSTATS, &keystats, sizeof(keystats));
	(void)printf("%9d %s (free %d%% norefs %d%% taken %d%% shared %d%%)\n",
E 44
E 42
	    keystats.ks_allocs, "code cache keys allocated",
D 25
	    keystats.ks_free * 100 / nz(keystats.ks_allocs),
	    keystats.ks_norefs * 100 / nz(keystats.ks_allocs),
	    keystats.ks_taken * 100 / nz(keystats.ks_allocs),
	    keystats.ks_shared * 100 / nz(keystats.ks_allocs));
E 25
I 25
D 28
	    pct(keystats.ks_free, keystats.ks_allocs),
E 28
I 28
D 42
	    pct(keystats.ks_allocfree, keystats.ks_allocs),
E 28
	    pct(keystats.ks_norefs, keystats.ks_allocs),
	    pct(keystats.ks_taken, keystats.ks_allocs),
	    pct(keystats.ks_shared, keystats.ks_allocs));
E 25
	lseek(mf, (long)nl[X_DKEYSTATS].n_value, 0);
	read(mf, &keystats, sizeof keystats);
	printf("%9d %s (free %d%% norefs %d%% taken %d%% shared %d%%)\n",
E 42
I 42
	    PCT(keystats.ks_allocfree, keystats.ks_allocs),
	    PCT(keystats.ks_norefs, keystats.ks_allocs),
	    PCT(keystats.ks_taken, keystats.ks_allocs),
	    PCT(keystats.ks_shared, keystats.ks_allocs));
D 44
	kread(X_DKEYSTATS, (char *)&keystats, sizeof keystats);
	(void) printf("%9d %s (free %d%% norefs %d%% taken %d%% shared %d%%)\n",
E 44
I 44
	kread(X_DKEYSTATS, &keystats, sizeof(keystats));
	(void)printf("%9d %s (free %d%% norefs %d%% taken %d%% shared %d%%)\n",
E 44
E 42
	    keystats.ks_allocs, "data cache keys allocated",
D 25
	    keystats.ks_free * 100 / nz(keystats.ks_allocs),
	    keystats.ks_norefs * 100 / nz(keystats.ks_allocs),
	    keystats.ks_taken * 100 / nz(keystats.ks_allocs),
	    keystats.ks_shared * 100 / nz(keystats.ks_allocs));
E 25
I 25
D 28
	    pct(keystats.ks_free, keystats.ks_allocs),
E 28
I 28
D 42
	    pct(keystats.ks_allocfree, keystats.ks_allocs),
E 28
	    pct(keystats.ks_norefs, keystats.ks_allocs),
	    pct(keystats.ks_taken, keystats.ks_allocs),
	    pct(keystats.ks_shared, keystats.ks_allocs));
E 42
I 42
	    PCT(keystats.ks_allocfree, keystats.ks_allocs),
	    PCT(keystats.ks_norefs, keystats.ks_allocs),
	    PCT(keystats.ks_taken, keystats.ks_allocs),
	    PCT(keystats.ks_shared, keystats.ks_allocs));
E 42
E 25
#endif
E 24
E 22
E 18
E 15
E 14
}

I 47
D 49
#ifndef NEWVM
E 49
I 49
#ifdef notdef
E 49
E 47
I 44
void
E 44
D 9

E 9
doforkst()
{
I 44
	struct forkstat fks;
E 44

D 18
	lseek(mf, (long)nl[X_FORKSTAT].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_FORKSTAT].n_value, L_SET);
E 18
	read(mf, &forkstat, sizeof forkstat);
	printf("%d forks, %d pages, average=%.2f\n",
E 42
I 42
D 44
	kread(X_FORKSTAT, (char *)&forkstat, sizeof forkstat);
	(void) printf("%d forks, %d pages, average=%.2f\n",
E 42
		forkstat.cntfork, forkstat.sizfork,
		(float) forkstat.sizfork / forkstat.cntfork);
D 42
	printf("%d vforks, %d pages, average=%.2f\n",
E 42
I 42
	(void) printf("%d vforks, %d pages, average=%.2f\n",
E 42
		forkstat.cntvfork, forkstat.sizvfork,
		(float)forkstat.sizvfork / forkstat.cntvfork);
E 44
I 44
	kread(X_FORKSTAT, &fks, sizeof(struct forkstat));
	(void)printf("%d forks, %d pages, average %.2f\n",
	    fks.cntfork, fks.sizfork, (double)fks.sizfork / fks.cntfork);
	(void)printf("%d vforks, %d pages, average %.2f\n",
	    fks.cntvfork, fks.sizvfork, (double)fks.sizvfork / fks.cntvfork);
E 44
}
I 47
#endif
E 47

I 44
void
E 44
D 45
stats(dn)
I 44
	int dn;
E 45
I 45
dkstats()
E 45
E 44
{
D 44

D 18
	if (dn >= DK_NDRIVE) {
E 18
I 18
	if (dn >= dk_ndrive) {
E 18
D 42
		printf("  0");
E 42
I 42
		(void) printf("  0");
E 42
		return;
	}
D 2
	printf("%3.0f", s.numb[dn]/etime);
E 2
I 2
D 42
	printf("%3.0f", s.xfer[dn]/etime);
E 42
I 42
	(void) printf("%3.0f", s.xfer[dn]/etime);
E 44
I 44
D 45
	if (dn >= dk_ndrive)
		(void)printf("  0");
	else
E 45
I 45
	register int dn, state;
	double etime;
	long tmp;

	for (dn = 0; dn < dk_ndrive; ++dn) {
		tmp = cur.xfer[dn];
		cur.xfer[dn] -= last.xfer[dn];
		last.xfer[dn] = tmp;
	}
	etime = 0;
	for (state = 0; state < CPUSTATES; ++state) {
		tmp = cur.time[state];
		cur.time[state] -= last.time[state];
		last.time[state] = tmp;
		etime += cur.time[state];
	}
	if (etime == 0)
		etime = 1;
	etime /= hz;
	for (dn = 0; dn < dk_ndrive; ++dn) {
		if (!dr_select[dn])
			continue;
E 45
D 48
		(void)printf("%3.0f", cur.xfer[dn] / etime);
E 48
I 48
		(void)printf("%2.0f ", cur.xfer[dn] / etime);
E 48
I 45
	}
E 45
E 44
E 42
E 2
}

D 45
double
stat1(row)
I 44
	int row;
E 45
I 45
void
cpustats()
E 45
E 44
{
I 44
D 45
	register int i;
E 44
D 2
	register i, j;
	long t;
	double f1, f2;
E 2
I 2
	double t;
E 45
I 45
	register int state;
	double pct, total;
E 45
D 44
	register i;
E 44
E 2

D 45
	t = 0;
D 44
	for(i=0; i<CPUSTATES; i++)
D 2
		for(j=0; j<DK_NSTATES; j++)
			t += s.etime[i][j];
	f1 = t;
	if(f1 == 0.)
		f1 = 1.;
	t = 0;
	for(j=0; j<DK_NSTATES; j++)
		t += s.etime[row][j];
	f2 = t;
	return(f2*100./f1);
E 2
I 2
		t += s.time[i];
	if(t == 0.)
E 44
I 44
	for (i = 0; i < CPUSTATES; i++)
		t += cur.time[i];
	if (t == 0.)
E 44
		t = 1.;
D 44
	return(s.time[row]*100./t);
E 44
I 44
	return(cur.time[row]*100./t);
E 45
I 45
	total = 0;
	for (state = 0; state < CPUSTATES; ++state)
		total += cur.time[state];
	if (total)
		pct = 100 / total;
	else
		pct = 0;
D 48
	(void)printf("%3.0f",				/* user + nice */
E 48
I 48
D 62
	(void)printf("%2.0f ",				/* user + nice */
E 48
	    (cur.time[0] + cur.time[1]) * pct);
D 48
	(void)printf("%3.0f", cur.time[2] * pct);	/* system */
	(void)printf("%3.0f", cur.time[3] * pct);	/* idle */
E 48
I 48
	(void)printf("%2.0f ", cur.time[2] * pct);	/* system */
	(void)printf("%2.0f", cur.time[3] * pct);	/* idle */
E 62
I 62
	(void)printf("%2.0f ", (cur.time[CP_USER] + cur.time[CP_NICE]) * pct);
	(void)printf("%2.0f ", (cur.time[CP_SYS] + cur.time[CP_INTR]) * pct);
	(void)printf("%2.0f", cur.time[CP_IDLE] * pct);
E 62
E 48
E 45
E 44
E 2
}

I 44
void
E 44
D 42
pct(top, bot)
E 42
I 42
dointr()
E 42
{
I 44
	register long *intrcnt, inttotal, uptime;
E 44
I 42
	register int nintr, inamlen;
D 44
	register long *intrcnt, inttotal, uptime = getuptime();
E 44
	register char *intrname;
E 42

I 44
	uptime = getuptime();
E 44
D 42
	if (bot == 0)
		return (0);
	return ((top * 100) / bot);
I 16
}

dointr(nintv)
{
	int nintr, inttotal;
	long *intrcnt;
	char *intrname, *malloc();

	nintr = (nl[X_EINTRCNT].n_value - nl[X_INTRCNT].n_value) / sizeof(long);
	intrcnt = (long *) malloc(nl[X_EINTRCNT].n_value -
		nl[X_INTRCNT].n_value);
	intrname = malloc(nl[X_EINTRNAMES].n_value - nl[X_INTRNAMES].n_value);
E 42
I 42
D 57
	nintr = nl[X_EINTRCNT].n_value - nl[X_INTRCNT].n_value;
	inamlen = nl[X_EINTRNAMES].n_value - nl[X_INTRNAMES].n_value;
E 57
I 57
	nintr = namelist[X_EINTRCNT].n_value - namelist[X_INTRCNT].n_value;
	inamlen =
	    namelist[X_EINTRNAMES].n_value - namelist[X_INTRNAMES].n_value;
E 57
D 44
	intrcnt = (long *)malloc((size_t)nintr);
E 44
I 44
	intrcnt = malloc((size_t)nintr);
E 44
	intrname = malloc((size_t)inamlen);
E 42
	if (intrcnt == NULL || intrname == NULL) {
D 42
		fprintf(stderr, "vmstat: out of memory\n");
E 42
I 42
D 44
		(void) fprintf(stderr, "vmstat: %s.\n", strerror(errno));
E 42
		exit(9);
E 44
I 44
		(void)fprintf(stderr, "vmstat: %s.\n", strerror(errno));
		exit(1);
E 44
	}
D 18
	lseek(mf, (long)nl[X_INTRCNT].n_value, 0);
E 18
I 18
D 42
	lseek(mf, (long)nl[X_INTRCNT].n_value, L_SET);
E 18
	read(mf, intrcnt, nintr * sizeof (long));
D 18
	lseek(mf, (long)nl[X_INTRNAMES].n_value, 0);
E 18
I 18
	lseek(mf, (long)nl[X_INTRNAMES].n_value, L_SET);
E 18
	read(mf, intrname, nl[X_EINTRNAMES].n_value - nl[X_INTRNAMES].n_value);
	printf("interrupt      total      rate\n");
E 42
I 42
D 44
	kread(X_INTRCNT, (char *)intrcnt, (size_t)nintr);
E 44
I 44
	kread(X_INTRCNT, intrcnt, (size_t)nintr);
E 44
	kread(X_INTRNAMES, intrname, (size_t)inamlen);
D 44
	(void) printf("interrupt      total      rate\n");
E 44
I 44
	(void)printf("interrupt      total      rate\n");
E 44
E 42
	inttotal = 0;
D 42
	while (nintr--) {
E 42
I 42
	nintr /= sizeof(long);
	while (--nintr >= 0) {
E 42
		if (*intrcnt)
D 42
			printf("%-12s %8ld %8ld\n", intrname,
			    *intrcnt, *intrcnt / nintv);
E 42
I 42
D 44
			(void) printf("%-12s %8ld %8ld\n", intrname,
E 44
I 44
			(void)printf("%-12s %8ld %8ld\n", intrname,
E 44
			    *intrcnt, *intrcnt / uptime);
E 42
		intrname += strlen(intrname) + 1;
		inttotal += *intrcnt++;
	}
D 42
	printf("Total        %8ld %8ld\n", inttotal, inttotal / nintv);
E 42
I 42
D 44
	(void) printf("Total        %8ld %8ld\n", inttotal, inttotal / uptime);
E 44
I 44
	(void)printf("Total        %8ld %8ld\n", inttotal, inttotal / uptime);
E 44
E 42
I 28
}

/*
D 41
 * These names must be kept in sync with
 * the types defined in <sys/malloc.h>.
E 41
I 41
 * These names are defined in <sys/malloc.h>.
E 41
 */
D 41
char *kmemnames[] = {
D 29
	"free",		/* M_FREE */
	"mbuf",		/* M_MBUF */
	"devbuf",	/* M_DEVBUF */
	"socket",	/* M_SOCKET */
	"pcb",		/* M_PCB */
	"routetbl",	/* M_RTABLE */
	"hosttbl",	/* M_HTABLE */
	"fragtbl",	/* M_FTABLE */
	"zombie",	/* M_ZOMBIE */
	"ifaddr",	/* M_IFADDR */
	"soopts",	/* M_SOOPTS */
	"soname",	/* M_SONAME */
	"namei",	/* M_NAMEI */
	"gprof",	/* M_GPROF */
	"ioctlops",	/* M_IOCTLOPS */
	"superblk",	/* M_SUPERBLK */
	"cred",		/* M_CRED */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	"temp",		/* M_TEMP */
E 29
I 29
	"free",		/* 0 M_FREE */
	"mbuf",		/* 1 M_MBUF */
	"devbuf",	/* 2 M_DEVBUF */
	"socket",	/* 3 M_SOCKET */
	"pcb",		/* 4 M_PCB */
	"routetbl",	/* 5 M_RTABLE */
	"hosttbl",	/* 6 M_HTABLE */
	"fragtbl",	/* 7 M_FTABLE */
	"zombie",	/* 8 M_ZOMBIE */
	"ifaddr",	/* 9 M_IFADDR */
	"soopts",	/* 10 M_SOOPTS */
	"soname",	/* 11 M_SONAME */
	"namei",	/* 12 M_NAMEI */
	"gprof",	/* 13 M_GPROF */
	"ioctlops",	/* 14 M_IOCTLOPS */
	"superblk",	/* 15 M_SUPERBLK */
	"cred",		/* 16 M_CRED */
	"pgrp",		/* 17 M_PGRP */
	"session",	/* 18 M_SESSION */
I 30
	"iov",		/* 19 M_IOV */
I 33
	"mount",	/* 20 M_MOUNT */
	"fhandle",	/* 21 M_FHANDLE */
	"NFS req",	/* 22 M_NFSREQ */
	"NFS mount",	/* 23 M_NFSMNT */
E 33
E 30
D 37
	0, 0, 0, 0, 0,
E 37
I 37
	"vnodes",	/* 24 M_VNODE */
	"namecache",	/* 25 M_CACHE */
D 38
	0, 0, 0,
E 38
I 38
	"UFS quota",	/* 26 M_DQUOT */
	"UFS mount",	/* 27 M_UFSMNT */
D 40
	0,
E 40
I 40
	"mapmem",	/* 28 M_MAPMEM */
	"shm",		/* 29 M_SHM */
	0, 0, 0, 0,
E 40
E 38
E 37
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 0, 0,
D 40
	0, 0, 0, 0, 0,
E 40
D 30
	0, 0, 0, 0, 0,
E 30
I 30
D 33
	0, 0, 0, 0,
E 33
E 30
	"temp",		/* 49 M_TEMP */
E 29
};
E 41
I 41
char *kmemnames[] = INITKMEMNAMES;
E 41

I 44
void
E 44
domem()
{
D 42
	struct kmemstats kmemstats[M_LAST];
	struct kmembuckets buckets[MINBUCKET + 16];
E 42
	register struct kmembuckets *kp;
	register struct kmemstats *ks;
D 42
	int i;
E 42
I 42
D 58
	register int i;
I 47
	int size;
E 58
I 58
	register int i, j;
	int len, size, first;
E 58
	long totuse = 0, totfree = 0, totreq = 0;
I 58
	char *name;
E 58
E 47
	struct kmemstats kmemstats[M_LAST];
	struct kmembuckets buckets[MINBUCKET + 16];
E 42

D 42
	lseek(mf, (long)nl[X_KMEMBUCKETS].n_value, L_SET);
	read(mf, buckets, sizeof buckets);
	printf("Memory statistics by bucket size\n");
	printf("    Size   In Use   Free   Requests  HighWater  Couldfree\n");
E 42
I 42
D 44
	kread(X_KMEMBUCKETS, (char *)buckets, sizeof buckets);
	(void) printf("Memory statistics by bucket size\n");
	(void) printf(
E 44
I 44
	kread(X_KMEMBUCKETS, buckets, sizeof(buckets));
	(void)printf("Memory statistics by bucket size\n");
	(void)printf(
E 44
	    "    Size   In Use   Free   Requests  HighWater  Couldfree\n");
E 42
	for (i = MINBUCKET, kp = &buckets[i]; i < MINBUCKET + 16; i++, kp++) {
		if (kp->kb_calls == 0)
			continue;
D 42
		printf("%8d%9d%7d%11d%8d%11d\n", 1 << i, 
E 42
I 42
D 44
		(void) printf("%8d%9ld%7ld%11ld%8ld%11ld\n", 1 << i, 
E 44
I 44
D 47
		(void)printf("%8d%9ld%7ld%11ld%8ld%11ld\n", 1 << i, 
E 47
I 47
		size = 1 << i;
D 48
		(void)printf("%8d%9ld%7ld%11ld%8ld%11ld\n", size, 
E 48
I 48
		(void)printf("%8d %8ld %6ld %10ld %7ld %10ld\n", size, 
E 48
E 47
E 44
E 42
			kp->kb_total - kp->kb_totalfree,
			kp->kb_totalfree, kp->kb_calls,
			kp->kb_highwat, kp->kb_couldfree);
D 47
		
E 47
I 47
		totfree += size * kp->kb_totalfree;
D 50
		totuse += size * (kp->kb_total - kp->kb_totalfree);
E 50
E 47
	}
I 47
D 48
printf("%d\n", totuse);
totuse = 0;
E 48

E 47
D 42
	lseek(mf, (long)nl[X_KMEMSTAT].n_value, L_SET);
	read(mf, kmemstats, sizeof kmemstats);
	printf("Memory statistics by type\n");
	printf("     Type   In Use  MemUse   HighUse  Limit  Requests %s\n",
		"TypeLimit KernLimit");
E 42
I 42
D 44
	kread(X_KMEMSTAT, (char *)kmemstats, sizeof kmemstats);
	(void) printf("Memory statistics by type\n");
	(void) printf("\
     Type   In Use  MemUse   HighUse  Limit  Requests TypeLimit KernLimit\n");
E 44
I 44
	kread(X_KMEMSTAT, kmemstats, sizeof(kmemstats));
D 58
	(void)printf("\nMemory statistics by type\n");
E 58
I 58
	(void)printf("\nMemory usage type by bucket size\n");
	(void)printf("    Size  Type(s)\n");
	kp = &buckets[MINBUCKET];
	for (j =  1 << MINBUCKET; j < 1 << (MINBUCKET + 16); j <<= 1, kp++) {
		if (kp->kb_calls == 0)
			continue;
		first = 1;
		len = 8;
		for (i = 0, ks = &kmemstats[0]; i < M_LAST; i++, ks++) {
			if (ks->ks_calls == 0)
				continue;
			if ((ks->ks_size & j) == 0)
				continue;
			name = kmemnames[i] ? kmemnames[i] : "undefined";
			len += 2 + strlen(name);
			if (first)
				printf("%8d  %s", j, name);
			else
				printf(",");
			if (len >= 80) {
				printf("\n\t ");
				len = 10 + strlen(name);
			}
			if (!first)
				printf(" %s", name);
			first = 0;
		}
		printf("\n");
	}

E 58
	(void)printf(
D 58
"      Type  In Use  MemUse   HighUse  Limit Requests  TypeLimit KernLimit\n");
E 58
I 58
	    "\nMemory statistics by type                        Type  Kern\n");
	(void)printf(
"      Type  InUse MemUse HighUse  Limit Requests Limit Limit Size(s)\n");
E 58
E 44
E 42
	for (i = 0, ks = &kmemstats[0]; i < M_LAST; i++, ks++) {
		if (ks->ks_calls == 0)
			continue;
D 42
		printf("%10s%7d%8dK%9dK%6dK%9d%7d%10d\n",
E 42
I 42
D 44
		(void) printf("%10s%7ld%8ldK%9ldK%6ldK%9ld%7u%10u\n",
E 42
			kmemnames[i] ? kmemnames[i] : "undefined",
			ks->ks_inuse, (ks->ks_memuse + 1023) / 1024,
			(ks->ks_maxused + 1023) / 1024,
			(ks->ks_limit + 1023) / 1024, ks->ks_calls,
			ks->ks_limblocks, ks->ks_mapblocks);
E 44
I 44
D 48
		(void)printf("%10s%7ld%8ldK%9ldK%6ldK%9ld%7u%10u\n",
E 48
I 48
D 58
		(void)printf("%10s %6ld %7ldK %8ldK %5ldK %8ld %6u %9u\n",
E 58
I 58
		(void)printf("%11s%6ld%6ldK%7ldK%6ldK%9ld%5u%6u",
E 58
E 48
		    kmemnames[i] ? kmemnames[i] : "undefined",
		    ks->ks_inuse, (ks->ks_memuse + 1023) / 1024,
		    (ks->ks_maxused + 1023) / 1024,
		    (ks->ks_limit + 1023) / 1024, ks->ks_calls,
		    ks->ks_limblocks, ks->ks_mapblocks);
I 58
		first = 1;
		for (j =  1 << MINBUCKET; j < 1 << (MINBUCKET + 16); j <<= 1) {
			if ((ks->ks_size & j) == 0)
				continue;
			if (first)
				printf("  %d", j);
			else
				printf(",%d", j);
			first = 0;
		}
		printf("\n");
E 58
I 47
		totuse += ks->ks_memuse;
		totreq += ks->ks_calls;
E 47
E 44
	}
I 47
	(void)printf("\nMemory Totals:  In Use    Free    Requests\n");
	(void)printf("              %7ldK %6ldK    %8ld\n",
	     (totuse + 1023) / 1024, (totfree + 1023) / 1024, totreq);
E 47
E 28
E 16
I 3
}

I 9
D 18
#define steal(where, var) lseek(mf, where, 0); read(mf, &var, sizeof var);
E 18
I 18
D 42
#define steal(where, var) \
	lseek(mf, where, L_SET); read(mf, &var, sizeof var);
E 42
E 18
E 9
D 44
/*
 * Read the drive names out of kmem.
D 9
 * ARGH ARGH ARGH ARGH !!!!!!!!!!!!
E 9
 */
D 9

#define steal(where, var) lseek(mf, where, 0); read(mf, &var, sizeof var);
E 9
I 9
#ifdef vax
I 18
D 42
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
E 42
I 42
#include <uba/ubavar.h>
#include <mba/mbavar.h>
E 42

E 18
E 9
read_names()
E 44
I 44
D 49
void
zero()
E 44
{
I 42
D 44
	register char *p;
	unsigned long mp, up;
E 42
	struct mba_device mdev;
D 42
	register struct mba_device *mp;
E 42
	struct mba_driver mdrv;
D 42
	short two_char;
	char *cp = (char *) &two_char;
	struct uba_device udev, *up;
E 42
I 42
	struct uba_device udev;
E 42
	struct uba_driver udrv;
I 42
	char name[10];
	static char buf[BUFSIZ];
E 44
I 44
D 46
	struct nlist znl[] = {
E 46
I 46
	static struct nlist znl[] = {
E 46
#undef	X_SUM
#define X_SUM		0
D 48
		{ "_sum" },
E 48
I 48
		{ SUM },
E 48
		{ "" },
	};
	int fd;
	char *kmem;
E 44
E 42

D 42
	mp = (struct mba_device *) nl[X_MBDINIT].n_value;
	up = (struct uba_device *) nl[X_UBDINIT].n_value;
D 6
	if (mp == 0 || up == 0)
	{
E 6
I 6
	if (up == 0) {
E 6
D 9
		fprintf(stderr, "iostat: Disk init info not in namelist\n");
E 9
I 9
		fprintf(stderr, "vmstat: Disk init info not in namelist\n");
E 42
I 42
D 44
	mp = nl[X_MBDINIT].n_value;
	up = nl[X_UBDINIT].n_value;
	if (mp == 0 && up == 0) {
		(void) fprintf(stderr,
		    "vmstat: disk init info not in namelist\n");
E 44
I 44
	if (geteuid()) {
		(void)fprintf(stderr, "vmstat: %s\n", strerror(EPERM));
E 44
E 42
E 9
		exit(1);
	}
D 6
	while(1)
	{
E 6
I 6
D 42
	if (mp) for (;;) {
E 6
		steal(mp++, mdev);
E 42
I 42
D 44
	p = buf;
	if (mp) for (;; mp += sizeof mdev) {
		(void) kvm_read((u_long)mp, (char *)&mdev, sizeof mdev);
E 42
		if (mdev.mi_driver == 0)
			break;
		if (mdev.mi_dk < 0 || mdev.mi_alive == 0)
			continue;
D 42
		steal(mdev.mi_driver, mdrv);
		steal(mdrv.md_dname, two_char);
D 18
		sprintf(dr_name[mdev.mi_dk], "%c%c", cp[0], cp[1]);
		dr_unit[mdev.mi_dk] = mdev.mi_unit;
E 18
I 18
		sprintf(dr_name[mdev.mi_dk], "%c%c%d",
		    cp[0], cp[1], mdev.mi_unit);
E 42
I 42
		(void) kvm_read((u_long)mdev.mi_driver,
		    (char *)&mdrv, sizeof mdrv);
		(void) kvm_read((u_long)mdrv.md_dname, name, sizeof name);
		dr_name[mdev.mi_dk] = p;
		p += sprintf(p, "%s%d", name, mdev.mi_unit);
E 44
I 44
	/*
	 * Zeroing the statistics is fundamentally different
	 * (and really belongs in a separate program).
	 */
	if (nlist(vmunix, znl) || nl[0].n_type == 0) {
		(void)fprintf(stderr, "vmstat: %s: symbol %s not found\n",
		    vmunix, nl[0].n_name);
		exit(1);
E 44
E 42
E 18
	}
D 6
	while(1)
	{
E 6
I 6
D 42
	for (;;) {
E 6
		steal(up++, udev);
E 42
I 42
D 44
	if (up) for (;; up += sizeof udev) {
		(void) kvm_read(up, (char *)&udev, sizeof udev);
E 42
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
D 42
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
D 18
		sprintf(dr_name[udev.ui_dk], "%c%c", cp[0], cp[1]);
		dr_unit[udev.ui_dk] = udev.ui_unit;
E 18
I 18
		sprintf(dr_name[udev.ui_dk], "%c%c%d",
		    cp[0], cp[1], udev.ui_unit);
E 42
I 42
		(void) kvm_read((u_long)udev.ui_driver,
		    (char *)&udrv, sizeof udrv);
		(void) kvm_read((u_long)udrv.ud_dname, name, sizeof name);
		dr_name[udev.ui_dk] = p;
		p += sprintf(p, "%s%d", name, udev.ui_unit);
E 44
I 44

	kmem = _PATH_KMEM;
	if ((fd = open(kmem, O_RDWR)) < 0) {
		(void)fprintf(stderr,
		    "vmstat: %s: %s\n", kmem, strerror(errno));
		exit(1);
E 44
E 42
I 23
D 25
	}
}
#endif

#ifdef sun
#include <sundev/mbvar.h>

read_names()
{
	struct mb_device mdev;
	register struct mb_device *mp;
	struct mb_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;

	mp = (struct mb_device *) nl[X_MBDINIT].n_value;
	if (mp == 0) {
		fprintf(stderr, "vmstat: Disk init info not in namelist\n");
		exit(1);
	}
	for (;;) {
		steal(mp++, mdev);
		if (mdev.md_driver == 0)
			break;
		if (mdev.md_dk < 0 || mdev.md_alive == 0)
			continue;
		steal(mdev.md_driver, mdrv);
		steal(mdrv.mdr_dname, two_char);
		sprintf(dr_name[mdev.md_dk], "%c%c%d",
		     cp[0], cp[1], mdev.md_unit);
E 25
	}
I 44
	if (lseek(fd, (long)nl[0].n_value, L_SET) == -1 ||
	    write(fd, &sum, sizeof(sum)) != sizeof(sum)) {
		(void)fprintf(stderr,
		    "vmstat: %s: %s\n", kmem, strerror(errno));
		exit(1);
	}
E 44
}
D 44
#endif
E 44

E 49
D 44
#ifdef tahoe
D 42
#include <tahoevba/vbavar.h>
E 42
I 42
D 43
#include <vba/vbavar.h>
E 43
I 43
#include <tahoe/vba/vbavar.h>
E 43
E 42

E 44
/*
D 44
 * Read the drive names out of kmem.
E 44
I 44
 * kread reads something from the kernel, given its nlist index.
E 44
 */
D 44
read_names()
E 44
I 44
void
kread(nlx, addr, size)
	int nlx;
	void *addr;
	size_t size;
E 44
{
I 42
D 44
	register char *p;
E 42
	struct vba_device udev, *up;
	struct vba_driver udrv;
D 42
	short two_char;
	char *cp = (char *)&two_char;
E 42
I 42
	char name[10];
	static char buf[BUFSIZ];
E 44
I 44
	char *sym;
E 44
E 42

D 44
	up = (struct vba_device *) nl[X_VBDINIT].n_value;
	if (up == 0) {
D 42
		fprintf(stderr, "vmstat: Disk init info not in namelist\n");
E 42
I 42
		(void) fprintf(stderr,
		    "vmstat: disk init info not in namelist\n");
E 44
I 44
D 57
	if (nl[nlx].n_type == 0 || nl[nlx].n_value == 0) {
		sym = nl[nlx].n_name;
E 57
I 57
	if (namelist[nlx].n_type == 0 || namelist[nlx].n_value == 0) {
		sym = namelist[nlx].n_name;
E 57
		if (*sym == '_')
			++sym;
		(void)fprintf(stderr,
D 52
		    "vmstat: %s: symbol %s not defined\n", vmunix, sym);
E 52
I 52
		    "vmstat: symbol %s not defined\n", sym);
E 52
E 44
E 42
		exit(1);
	}
D 42
	for (;;) {
		steal(up++, udev);
E 42
I 42
D 44
	p = buf;
	for (;; up += sizeof udev) {
		(void) kvm_read(up, (char *)&udev, sizeof udev);
E 42
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
D 42
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
		sprintf(dr_name[udev.ui_dk], "%c%c%d",
		     cp[0], cp[1], udev.ui_unit);
E 42
I 42
		(void) kvm_read((u_long)udev.ui_driver,
		    (char *)&udrv, sizeof udrv);
		(void) kvm_read((u_long)udrv.ud_dname, name, sizeof name);
		dr_name[udev.ui_dk] = p;
		p += sprintf(p, "%s%d", name, udev.ui_unit);
E 44
I 44
D 53
	if (kvm_read((void *)nl[nlx].n_value, addr, size) != size) {
E 53
I 53
D 57
	if (kvm_read(kd, nl[nlx].n_value, addr, size) != size) {
E 53
		sym = nl[nlx].n_name;
E 57
I 57
	if (kvm_read(kd, namelist[nlx].n_value, addr, size) != size) {
		sym = namelist[nlx].n_name;
E 57
		if (*sym == '_')
			++sym;
D 53
		(void)fprintf(stderr, "vmstat: %s: %s\n", sym, kvm_geterr());
E 53
I 53
		(void)fprintf(stderr, "vmstat: %s: %s\n", sym, kvm_geterr(kd));
E 53
		exit(1);
E 44
E 42
I 40
	}
}
D 44
#endif
E 44

D 44
#ifdef hp300
D 43
#include <hpdev/device.h>
E 43
I 43
#include <hp300/dev/device.h>
E 43

D 42
#define validdisk(cp)	((cp)[1] == 'd' && ((cp)[0] == 'r' || (cp)[0] == 's'))

E 42
read_names()
E 44
I 44
void
usage()
E 44
{
I 42
D 44
	register char *p;
	register u_long hp;
I 43
	static char buf[BUFSIZ];
E 43
E 42
	struct hp_device hdev;
D 42
	register struct hp_device *hp;
E 42
	struct driver hdrv;
D 42
	short two_char;
	char *cp = (char *) &two_char;
	register char *dp;
E 42
I 42
D 43
	static char buf[BUFSIZ];
E 43
I 43
	char name[10];
E 43
E 42

D 42
	hp = (struct hp_device *) nl[X_HPDINIT].n_value;
E 42
I 42
	hp = nl[X_HPDINIT].n_value;
E 42
	if (hp == 0) {
D 42
		fprintf(stderr, "vmstat: Disk init info not in namelist\n");
E 42
I 42
		(void) fprintf(stderr,
		    "vmstat: disk init info not in namelist\n");
E 42
		exit(1);
	}
D 42
	for (;;) {
		steal(hp++, hdev);
E 42
I 42
	p = buf;
	for (;; hp += sizeof hdev) {
		(void) kvm_read(hp, (char *)&hdev, sizeof hdev);
E 42
		if (hdev.hp_driver == 0)
			break;
D 42
		steal(hdev.hp_driver, hdrv);
		steal(hdrv.d_name, two_char);
		/*
		 * hp_dk is meaningless if the device isn't a disk
		 * (d_name not valid) or the disk was not found when
		 * booting (hp_alive == 0).
		 */
		if (!validdisk(cp) || hdev.hp_alive == 0)
E 42
I 42
		if (hdev.hp_dk < 0 || hdev.hp_alive == 0)
E 42
			continue;
D 42
		dp = dr_name[hdev.hp_dk];
		sprintf(dp, "%c%c%d", cp[0], cp[1], hdev.hp_unit);
E 42
I 42
		(void) kvm_read((u_long)hdev.hp_driver,
		    (char *)&hdrv, sizeof hdrv);
		(void) kvm_read((u_long)hdrv.d_name, name, sizeof name);
		dr_name[hdev.hp_dk] = p;
		p += sprintf(p, "%s%d", name, hdev.hp_unit);
E 42
E 40
E 23
E 18
D 17
	}
E 3
}
I 9
#endif

#ifdef sun
read_names()
{
	struct mb_device mdev;
	register struct mb_device *mp;
	struct mb_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;

	mp = (struct mb_device *) nl[X_MBDINIT].n_value;
	if (mp == 0) {
		fprintf(stderr, "iostat: Disk init info not in namelist\n");
		exit(1);
	}
	for (;;) {
		steal(mp++, mdev);
		if (mdev.md_driver == 0)
			break;
		if (mdev.md_dk < 0 || mdev.md_alive == 0)
			continue;
		steal(mdev.md_driver, mdrv);
		steal(mdrv.mdr_dname, two_char);
		sprintf(dr_name[mdev.md_dk], "%c%c%d", cp[0], cp[1]);
		dr_unit[mdev.md_dk] = mdev.md_unit;
E 17
	}
E 44
I 44
	(void)fprintf(stderr,
I 47
#ifndef NEWVM
E 47
	    "usage: vmstat [-fimst] [-c count] [-M core] \
D 49
[-N system] [-w wait] [disks]\n       vmstat -z\n");
E 49
I 49
[-N system] [-w wait] [disks]\n");
E 49
I 47
#else
	    "usage: vmstat [-ims] [-c count] [-M core] \
D 49
[-N system] [-w wait] [disks]\n       vmstat -z\n");
E 49
I 49
[-N system] [-w wait] [disks]\n");
E 49
#endif
E 47
	exit(1);
E 44
}
D 44
#endif
E 44
E 9
E 1
