h00493
s 00001/00000/00208
d D 8.7 95/05/10 20:52:50 mckusick 68 67
c missing simple_unlock
e
s 00002/00002/00206
d D 8.6 94/08/20 16:25:49 mckusick 67 66
c use new queue.h data structures
e
s 00013/00003/00195
d D 8.5 94/07/28 14:02:06 hibler 66 65
c attempt to make "average active VM" count more accurate--
c don't count empty shadow objects
e
s 00000/00001/00198
d D 8.4 94/01/04 22:23:28 bostic 65 64
c lint
e
s 00006/00007/00193
d D 8.3 93/12/30 16:01:18 mckusick 64 63
c convert to use new queue structures
e
s 00007/00007/00193
d D 8.2 93/09/23 16:40:50 bostic 63 62
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00198
d D 8.1 93/06/11 16:37:57 bostic 62 61
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00200
d D 7.22 93/05/12 14:43:54 mckusick 61 60
c get rid of old vaxisms
e
s 00001/00002/00203
d D 7.21 93/04/27 15:19:47 mckusick 60 59
c sysctl.h needs vm/vm.h
e
s 00002/00002/00203
d D 7.20 93/03/04 17:59:27 bostic 59 58
c change buffer lengths of sysctl(2) to be size_t's
e
s 00002/00001/00203
d D 7.19 93/03/02 18:22:59 mckusick 58 57
c add proc parameter to vm_sysctl
e
s 00026/00050/00178
d D 7.18 93/02/04 01:25:38 mckusick 57 56
c add vm_sysctl framwork; kinfo_loadavg becomes sysctl_loadavg;
c kinfo_meter becomes sysctl_meter
e
s 00002/00002/00226
d D 7.17 92/07/08 01:01:23 torek 56 55
c volatile poison
e
s 00000/00001/00228
d D 7.16 92/06/03 12:00:11 hibler 55 54
c remove misplaced simple_unlock call
e
s 00011/00006/00218
d D 7.15 92/05/04 17:23:07 bostic 54 53
c new include format; lint
e
s 00002/00001/00222
d D 7.14 92/03/03 16:08:43 hibler 53 52
c avoid NULL object pointer dereference in vmtotal
e
s 00038/00006/00185
d D 7.13 92/02/25 17:11:32 mckusick 52 51
c add kinfo_loadavg to get loadavg through getkerninfo
e
s 00138/00064/00053
d D 7.12 91/09/03 11:15:07 mckusick 51 50
c first cut at new VM statistics gathering
e
s 00009/00008/00108
d D 7.11 91/04/20 10:50:11 karels 50 49
c fix includes; new proc struct; rm *_NULL
e
s 00006/00354/00110
d D 7.10 90/12/05 17:54:26 mckusick 49 48
c formerly vm_sched.c; update for new VM
e
s 00001/00011/00463
d D 7.9 90/06/28 21:28:49 bostic 48 47
c new copyright notice
e
s 00003/00003/00471
d D 7.8 90/05/15 18:41:47 mckusick 47 46
c update for hp300 support from Utah
e
s 00003/00002/00471
d D 7.7 90/05/02 19:07:25 mckusick 46 45
c do not count processes in load average sleeping over one second
e
s 00016/00010/00457
d D 7.6 89/05/29 13:09:36 mckusick 45 44
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00015/00009/00452
d D 7.5 89/05/09 17:03:31 mckusick 44 43
c merge in vnodes
e
s 00004/00005/00457
d D 7.4 87/08/08 17:10:56 karels 43 42
c clean up after wnj
e
s 00004/00002/00458
d D 7.3 87/04/03 16:13:07 bostic 42 41
c bug report 4.1BSD/sys/25
e
s 00001/00001/00459
d D 7.2 86/11/30 18:06:39 karels 41 40
c stopped, neg. nice jobs aren't "load"
e
s 00001/00001/00459
d D 7.1 86/06/05 00:20:43 mckusick 40 39
c 4.3BSD release version
e
s 00004/00002/00456
d D 6.8 85/11/20 10:41:26 karels 39 38
c no swkill in swapout, callers handle failure; move spl for
c blocking memory allocator to last chance and clarify comment
e
s 00007/00001/00451
d D 6.7 85/06/08 15:16:38 mckusick 38 37
c Add copyright
e
s 00003/00007/00449
d D 6.6 85/03/18 12:50:25 karels 37 36
c degenerate test; purge spl6!
e
s 00003/00073/00453
d D 6.5 85/03/03 16:18:03 mckusick 36 35
c setup of paging constants is now done in the paging daemon (pageout);
c scan rate calculation is done independently of memory size
e
s 00005/00002/00521
d D 6.4 85/02/22 15:49:45 mckusick 35 34
c lotsfree is now 512KB but at most 1/4 of memory
e
s 00010/00010/00513
d D 6.3 84/08/29 20:30:15 bloom 34 31
c Change to includes.  no more ../h
e
s 00004/00004/00519
d R 6.3 84/08/22 18:53:37 mckusick 33 31
c use IMIN macro to save call overhead
e
s 00005/00005/00518
d R 6.3 84/08/22 18:50:17 mckusick 32 31
c use IMIN macro to save call overhead
e
s 00003/00005/00520
d D 6.2 84/05/22 11:45:28 karels 31 30
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00000/00000/00525
d D 6.1 83/07/29 06:52:29 sam 30 29
c 4.2 distribution
e
s 00009/00048/00516
d D 4.22 83/06/14 23:32:12 sam 29 27
c cleanup
e
s 00009/00048/00516
d R 4.22 83/06/14 22:57:44 sam 28 27
c cleanup
e
s 00036/00005/00528
d D 4.21 83/05/18 02:06:43 sam 27 26
c sun's need different paramters than vax; fix this on next delta
e
s 00001/00013/00532
d D 4.20 83/04/04 06:12:30 sam 26 25
c no more NOPAGING (yeah)
e
s 00004/00000/00541
d D 4.19 83/01/17 17:21:42 sam 25 24
c sun crap
e
s 00008/00005/00533
d D 4.18 83/01/08 15:14:56 sam 24 23
c lost paging (boo hiss)
e
s 00009/00001/00529
d D 4.17 82/10/31 13:41:49 root 23 22
c fixes from 68k for NOPAGING
e
s 00001/00001/00529
d D 4.16 82/10/17 21:52:35 root 22 21
c more lint
e
s 00013/00017/00517
d D 4.15 82/09/06 22:58:38 root 21 20
c 
e
s 00001/00001/00533
d D 4.14 82/03/31 09:09:45 wnj 20 19
c nswdev >= 2, not == 2
e
s 00001/00001/00533
d D 4.13 81/08/30 20:56:06 root 19 18
c drop print of slowscan, fastscan, etc
e
s 00007/00012/00527
d D 4.12 81/06/07 00:23:15 wnj 18 17
c slow down page replacement to 200 pages/sec
e
s 00002/00003/00537
d D 4.11 81/04/28 02:57:30 root 17 16
c de-lint
e
s 00001/00000/00539
d D 4.10 81/04/26 14:32:40 wnj 16 15
c declare klsdist
e
s 00007/00008/00532
d D 4.9 81/04/24 00:13:16 wnj 15 14
c bigger minfree()
e
s 00013/00024/00527
d D 4.8 81/04/24 00:02:27 wnj 14 13
c now max of 300 scans per second; no funnies with multi swap devs
e
s 00002/00002/00549
d D 4.7 81/04/23 23:40:17 wnj 13 12
c spelling errors and boundary errors
e
s 00119/00014/00432
d D 4.6 81/04/23 03:03:30 wnj 12 11
c add setupclock; also first attempt at fixing swap hysteresis:
c use avenrun[0], not multprog
c use max of 5 and 30 second average free to check shortage
c decay out process priority uses klin as multiplier
c swap in/out give at most lotsfree
c nb: really should switch system to just de-activate processes
e
s 00015/00006/00431
d D 4.5 81/04/17 17:54:50 wnj 11 10
c remove spurious high ipl's
e
s 00001/00001/00436
d D 4.4 81/03/09 01:51:31 wnj 10 9
c lint and a few minor fixed
e
s 00001/00001/00436
d D 4.3 81/02/26 23:42:17 wnj 9 8
c rid of NTEXT
e
s 00003/00003/00434
d D 4.2 81/02/26 23:40:27 wnj 8 7
c rid of NPROC
e
s 00000/00000/00437
d D 4.1 80/11/09 17:33:24 bill 7 6
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00007/00007/00430
d D 3.6 80/11/06 17:59:11 bill 6 5
c spelling of desperate
e
s 00003/00003/00434
d D 3.5 80/07/11 08:14:33 bill 5 4
c fix bug at PZERO boundary.
e
s 00001/00001/00436
d D 3.4 80/06/07 02:49:40 bill 4 3
c %H%->%G%
e
s 00003/00003/00434
d D 3.3 80/06/04 14:37:59 bill 3 2
c reformat
e
s 00005/00005/00432
d D 3.2 80/05/09 13:52:09 bill 2 1
c VOID=>(void)
e
s 00437/00000/00000
d D 3.1 80/04/09 16:05:12 bill 1 0
c date and time created 80/04/09 16:05:12 by bill
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%H%	*/
E 4
I 4
D 10
/*	%M%	%I%	%G%	*/
E 10
I 10
D 38
/*	%M%	%I%	%E%	*/
E 38
I 38
/*
D 40
 * Copyright (c) 1982 Regents of the University of California.
E 40
I 40
D 44
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 40
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 44
I 44
D 62
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 62
I 62
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 62
E 44
 *
I 44
D 48
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
E 48
I 48
 * %sccs.include.redist.c%
E 48
 *
E 44
 *	%W% (Berkeley) %G%
 */
E 38
E 10
E 4

D 34
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/seg.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/text.h"
#include "../h/vm.h"
#include "../h/cmap.h"
I 21
#include "../h/kernel.h"
E 34
I 34
D 54
#include "param.h"
D 50
#include "systm.h"
D 44
#include "seg.h"
#include "dir.h"
E 44
#include "user.h"
E 50
#include "proc.h"
I 50
#include "systm.h"
E 50
D 49
#include "text.h"
#include "vm.h"
E 49
D 44
#include "cmap.h"
E 44
#include "kernel.h"
I 51
#include "vm.h"
E 54
I 54
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/kernel.h>
I 57
D 60
#include <sys/sysctl.h>
E 57
E 54
E 51
I 49
D 50
#include "machine/vmparam.h"
E 50
I 50

E 60
I 54
#include <vm/vm.h>
I 60
#include <sys/sysctl.h>
E 60

E 54
D 51
#include "vm_param.h"
E 50
#include "vmmeter.h"
E 49
E 34
E 21

E 51
I 49
D 52
fixpt_t	averunnable[3];		/* load average, of runnable procs */
E 52
I 52
struct	loadavg averunnable;		/* load average, of runnable procs */
E 52

E 49
I 39
D 44


E 44
E 39
D 12
int	maxpgio = MAXPGIO;
E 12
int	maxslp = MAXSLP;
D 12
int	minfree = MINFREE;
int	desfree = DESFREE;
int	lotsfree = 0;		/* set to LOTSFREE in main unless adbed */
E 12
int	saferss = SAFERSS;
D 12
int	slowscan = SLOWSCAN;
int	fastscan = FASTSCAN;
E 12
I 12

D 49
/*
 * The following parameters control operation of the page replacement
 * algorithm.  They are initialized to 0, and then computed at boot time
 * based on the size of the system.  If they are patched non-zero in
 * a loaded vmunix they are left alone and may thus be changed per system
 * using adb on the loaded system.
 */
int	maxpgio = 0;
int	minfree = 0;
int	desfree = 0;
int	lotsfree = 0;
int	slowscan = 0;
int	fastscan = 0;
E 12
int	klin = KLIN;
I 12
int	klseql = KLSEQL;
I 16
int	klsdist = KLSDIST;
E 16
int	kltxt = KLTXT;
E 12
int	klout = KLOUT;
int	multprog = -1;		/* so we don't count process 2 */
E 49
D 54

E 54
I 54
void
E 54
D 45
double	avenrun[3];		/* load average, of runnable procs */
E 45
I 45
D 49
fixpt_t	averunnable[3];		/* load average, of runnable procs */
E 45

/*
I 12
D 36
 * Setup the paging constants for the clock algorithm.
 * Called after the system is initialized and the amount of memory
 * and number of paging devices is known.
I 29
 *
 * Threshold constants are defined in ../machine/vmparam.h.
E 29
 */
setupclock()
{
D 17
	int nclust, nkb;
E 17

	/*
	 * Setup thresholds for paging:
	 *	lotsfree	is threshold where paging daemon turns on
	 *	desfree		is amount of memory desired free.  if less
	 *			than this for extended period, do swapping
	 *	minfree		is minimal amount of free memory which is
	 *			tolerable.
D 27
	 *
E 27
I 27
	 */
D 29

#ifdef vax
	/*
E 27
	 * Strategy of 4/22/81:
	 *	lotsfree is 1/4 of memory free.
	 *	desfree is 200k bytes, but at most 1/8 of memory
D 15
	 *	minfree is 32k bytes.
E 15
I 15
	 *	minfree is 64k bytes, but at most 1/2 of desfree
E 15
	 */
E 29
D 35
	if (lotsfree == 0)
D 29
		lotsfree = LOOPPAGES / 4;
E 29
I 29
		lotsfree = LOOPPAGES / LOTSFREEFRACT;
E 35
I 35
	if (lotsfree == 0) {
		lotsfree = LOTSFREE / NBPG;
		if (lotsfree > LOOPPAGES / LOTSFREEFRACT)
			lotsfree = LOOPPAGES / LOTSFREEFRACT;
	}
E 35
E 29
	if (desfree == 0) {
I 25
D 26
#ifndef NOPAGING
E 26
E 25
D 29
		desfree = (200*1024) / NBPG;
		if (desfree > LOOPPAGES / 8)
			desfree = LOOPPAGES / 8;
E 29
I 29
		desfree = DESFREE / NBPG;
		if (desfree > LOOPPAGES / DESFREEFRACT)
			desfree = LOOPPAGES / DESFREEFRACT;
E 29
I 25
D 26
#else
		desfree = (32*1024) / NBPG;
#endif
E 26
E 25
	}
D 15
	if (minfree == 0)
		minfree = (32*1024) / NBPG;
E 15
I 15
	if (minfree == 0) {
D 29
		minfree = (64*1024) / NBPG;
		if (minfree > desfree/2)
			minfree = desfree / 2;
E 29
I 29
		minfree = MINFREE / NBPG;
		if (minfree > desfree / MINFREEFRACT)
			minfree = desfree / MINFREEFRACT;
E 29
	}
E 15
D 27

E 27
I 27
D 29
#endif
#ifdef sun
E 29
E 27
	/*
I 27
D 29
	 * Strategy of 3/17/83:
	 *	lotsfree is 1/8 of memory free.
	 *	desfree is 100k bytes, but at most 1/16 of memory
	 *	minfree is 32k bytes, but at most 1/2 of desfree
	 */
	if (lotsfree == 0)
		lotsfree = LOOPPAGES / 8;
	if (desfree == 0) {
		desfree = (100*1024) / NBPG;
		if (desfree > LOOPPAGES / 16)
			desfree = LOOPPAGES / 16;
	}
	if (minfree == 0) {
		minfree = (32*1024) / NBPG;
		if (minfree > desfree/2)
			minfree = desfree / 2;
	}
#endif
	/*
E 29
E 27
	 * Maxpgio thresholds how much paging is acceptable.
	 * This figures that 2/3 busy on an arm is all that is
	 * tolerable for paging.  We assume one operation per disk rev.
	 */
	if (maxpgio == 0)
		maxpgio = (DISKRPM * 2) / 3;

	/*
D 14
	 * Clock to scan using max of 10% of processor time for sampling,
	 *     this estimated to allow maximum of 400 samples per second.
	 * Allow slighly higher angular velocity if 2 or more swap devices,
	 *     allow max of 600 samples per second (but only >= 2m)
	 * Basic scan time for ``fastscan'', the time for a clock rev
	 * with given memory and CLSIZE=2:
	 *	swap ilv	<=1m	2m	3m	4m	6m	8m
	 * 	one-way		4s	5s	7s	XXX	XXX	XXX
	 * 	two-way		4s	4s	5s	6s	10s	13s
	 * XXXs here are situations we should not be in.
E 14
I 14
D 18
	 * Clock to scan using max of ~~15% of processor time for sampling,
	 *     this estimated to allow maximum of 300 samples per second.
E 18
I 18
	 * Clock to scan using max of ~~10% of processor time for sampling,
	 *     this estimated to allow maximum of 200 samples per second.
E 18
	 * This yields a ``fastscan'' of roughly (with CLSIZE=2):
D 18
	 *	<=1m	2m	3m	4m	>=6m
	 * 	5s	6s	7s	13s	20s
E 18
I 18
	 *	<=1m	2m	3m	4m	8m
	 * 	5s	10s	15s	20s	40s
E 18
E 14
	 */
D 14
	if (fastscan == 0) {
		nclust = LOOPPAGES / CLSIZE;
		nkb = (LOOPPAGES * NBPG) / 1024;
D 13
		if (nswdev == 1 && nkb >= 2*1024)
E 13
I 13
		if (nswdev == 1 && physmem*NBPG > 2*1024*(1024-16))
E 13
			printf("WARNING: should run interleaved swap with >= 2Mb\n");
		if (nswdev == 1 || nkb < 2*1024)
			fastscan = nclust / 400;
		else {
			maxpgio = (maxpgio * 3) / 2;
			fastscan = nclust / 600;
		}
	}
	if (fastscan < 4)
		fastscan = 4;
E 14
I 14
D 27
	if (nswdev == 1 && physmem*NBPG > 2*1024*(1024-16))
		printf("WARNING: should run interleaved swap with >= 2Mb\n");
E 27
I 27
D 29
#ifdef vax
#define	LOTSOFMEM	2
#endif
#ifdef sun
#define	LOTSOFMEM	4
#endif
E 29
	if (nswdev == 1 && physmem*NBPG > LOTSOFMEM*1024*(1024-16))
		printf("WARNING: should run interleaved swap with >= %dMb\n",
		    LOTSOFMEM);
E 27
	if (fastscan == 0)
D 18
		fastscan = (LOOPPAGES/CLSIZE) / 300;
E 18
I 18
		fastscan = (LOOPPAGES/CLSIZE) / 200;
E 18
	if (fastscan < 5)
		fastscan = 5;
E 14
D 18
	if (fastscan > maxslp)
		fastscan = maxslp;
E 18
I 14
D 20
	if (nswdev == 2)
E 20
I 20
	if (nswdev >= 2)
E 20
		maxpgio = (maxpgio * 3) / 2;
E 14

	/*
D 18
	 * Set slow scan time to 1/3 the fast scan time but at most
	 * maxslp (a macroscopic slow).
E 18
I 18
	 * Set slow scan time to 1/2 the fast scan time.
E 18
	 */
	if (slowscan == 0)
D 18
		slowscan = 3 * fastscan;
	if (slowscan > maxslp)
		slowscan = maxslp;
E 18
I 18
		slowscan = 2 * fastscan;
E 18
D 13
#ifdef defined(BERT) || defined(ERNIE)
E 13
I 13
D 19
#if defined(BERT) || defined(ERNIE)
E 19
I 19
D 29
#ifdef notdef
E 19
E 13
	printf("slowscan %d, fastscan %d, maxpgio %d\n",
	    slowscan, fastscan, maxpgio);
	printf("lotsfree %d, desfree %d, minfree %d\n",
	    lotsfree, desfree, minfree);
#endif
E 29
}

/*
E 36
E 12
 * The main loop of the scheduling (swapping) process.
 *
 * The basic idea is:
 *	see if anyone wants to be swapped in;
 *	swap out processes until there is room;
 *	swap him in;
 *	repeat.
 * If the paging rate is too high, or the average free memory
 * is very low, then we do not consider swapping anyone in,
 * but rather look for someone to swap out.
 *
 * The runout flag is set whenever someone is swapped out.
 * Sched sleeps on it awaiting work.
 *
 * Sched sleeps on runin whenever it cannot find enough
 * core (by swapping out or otherwise) to fit the
 * selected swapped process.  It is awakened when the
 * core situation changes and in any case once per second.
 *
 * sched DOESN'T ACCOUNT FOR PAGE TABLE SIZE IN CALCULATIONS.
 */

#define	swappable(p) \
	(((p)->p_flag&(SSYS|SLOCK|SULOCK|SLOAD|SPAGE|SKEEP|SWEXIT|SPHYSIO))==SLOAD)

/* insure non-zero */
#define	nz(x)	(x != 0 ? x : 1)

#define	NBIG	4
#define	MAXNBIG	10
int	nbig = NBIG;

struct bigp {
	struct	proc *bp_proc;
	int	bp_pri;
	struct	bigp *bp_link;
} bigp[MAXNBIG], bplist;

sched()
{
	register struct proc *rp, *p, *inp;
	int outpri, inpri, rppri;
D 6
	int sleeper, desparate, deservin, needs, divisor;
E 6
I 6
	int sleeper, desperate, deservin, needs, divisor;
E 6
	register struct bigp *bp, *nbp;
	int biggot, gives;

D 15
	/*
	 * Check if paging rate is too high, or average of
	 * free list very low and if so, adjust multiprogramming
	 * load by swapping someone out.
D 12
	 *
	 * Avoid glitches: don't hard swap the only process,
	 * and don't swap based on paging rate if there is a reasonable
	 * amount of free memory.
E 12
	 */
E 15
loop:
D 2
	VOID spl6();
E 2
I 2
D 11
	(void) spl6();
E 11
I 11
	wantin = 0;
E 11
E 2
	deservin = 0;
	sleeper = 0;
	p = 0;
D 12
	if (kmapwnt || (multprog > 1 && avefree < desfree &&
E 12
I 12
	/*
I 15
	 * See if paging system is overloaded; if so swap someone out.
E 15
	 * Conditions for hard outswap are:
	 *	if need kernel map (mix it up).
	 * or
	 *	1. if there are at least 2 runnable processes (on the average)
	 * and	2. the paging rate is excessive or memory is now VERY low.
	 * and	3. the short (5-second) and longer (30-second) average
	 *	   memory is less than desirable.
	 */
D 17
	if (kmapwnt || (avenrun[0] >= 2 && max(avefree, avefree30) < desfree &&
E 17
I 17
D 23
	if (kmapwnt || (avenrun[0] >= 2 && imax(avefree, avefree30) < desfree &&
E 23
I 23
D 26
	if (
#ifdef NOPAGING
	    freemem == 0 ||
#endif
	    kmapwnt || (avenrun[0] >= 2 && imax(avefree, avefree30) < desfree &&
E 26
I 26
D 27
	if (kmapwnt || (avenrun[0] >= 2 && imax(avefree, avefree30) < desfree &&
E 27
I 27
	if (kmapwnt ||
D 45
	    (avenrun[0] >= 2 && imax(avefree, avefree30) < desfree &&
E 27
E 26
E 23
E 17
E 12
	    (rate.v_pgin + rate.v_pgout > maxpgio || avefree < minfree))) {
E 45
I 45
	    (averunnable[0] >= 2 * FSCALE &&
	     imax(avefree, avefree30) < desfree &&
	     (rate.v_pgin + rate.v_pgout > maxpgio || avefree < minfree))) {
E 45
D 6
		desparate = 1;
E 6
I 6
		desperate = 1;
E 6
		goto hardswap;
	}
D 6
	desparate = 0;
E 6
I 6
	desperate = 0;
E 6
	/*
D 6
	 * Not desparate for core,
E 6
I 6
	 * Not desperate for core,
E 6
	 * look for someone who deserves to be brought in.
	 */
	outpri = -20000;
D 8
	for (rp = &proc[0]; rp < &proc[NPROC]; rp++) switch(rp->p_stat) {
E 8
I 8
D 31
	for (rp = proc; rp < procNPROC; rp++) switch(rp->p_stat) {
E 31
I 31
	for (rp = allproc; rp != NULL; rp = rp->p_nxt) switch(rp->p_stat) {
E 31
E 8

	case SRUN:
		if ((rp->p_flag&SLOAD) == 0) {
D 3
			rppri = rp->p_time - rp->p_swrss / nz((maxpgio/2) * CLSIZE) + rp->p_slptime
			    - (rp->p_nice-NZERO)*8;
E 3
I 3
D 12
			rppri = rp->p_time - rp->p_swrss / nz((maxpgio/2) * CLSIZE) +
E 12
I 12
			rppri = rp->p_time -
			    rp->p_swrss / nz((maxpgio/2) * (klin * CLSIZE)) +
E 12
			    rp->p_slptime - (rp->p_nice-NZERO)*8;
E 3
			if (rppri > outpri) {
				if (rp->p_poip)
					continue;
				if (rp->p_textp && rp->p_textp->x_poip)
					continue;
				p = rp;
				outpri = rppri;
			}
		}
		continue;

	case SSLEEP:
	case SSTOP:
		if ((freemem < desfree || rp->p_rssize == 0) &&
		    rp->p_slptime > maxslp &&
		    (!rp->p_textp || (rp->p_textp->x_flag&XLOCK)==0) &&
		    swappable(rp)) {
			/*
			 * Kick out deadwood.
D 11
			 * FOLLOWING 3 LINES MUST BE AT spl6().
E 11
			 */
I 11
D 37
			(void) spl6();
E 37
E 11
			rp->p_flag &= ~SLOAD;
D 37
			if (rp->p_stat == SRUN)
				remrq(rp);
I 11
			(void) spl0();
E 37
E 11
D 2
			VOID swapout(rp, rp->p_dsize, rp->p_ssize);
E 2
I 2
D 47
			(void) swapout(rp, rp->p_dsize, rp->p_ssize);
E 47
I 47
			(void) swapout(rp, rp->p_dsize, rp->p_mmsize, rp->p_ssize);
E 47
E 2
D 39
			goto loop;
E 39
		}
		continue;
	}

	/*
D 43
	 * No one wants in, so nothing to do.
E 43
I 43
	 * If something came ready after we checked it,
	 * wantin will be set.  Otherwise,
	 * no one wants in, so nothing to do.
E 43
	 */
	if (outpri == -20000) {
D 11
		runout++;
		sleep((caddr_t)&runout, PSWP);
E 11
I 11
D 37
		(void) spl6();
E 37
I 37
		(void) splhigh();
E 37
D 43
		if (wantin) {
			wantin = 0;
			sleep((caddr_t)&lbolt, PSWP);
		} else {
E 43
I 43
		if (wantin == 0) {
E 43
			runout++;
			sleep((caddr_t)&runout, PSWP);
		}
		(void) spl0();
E 11
		goto loop;
	}
D 2
	VOID spl0();
E 2
I 2
D 11
	(void) spl0();
E 11
E 2
	/*
	 * Decide how deserving this guy is.  If he is deserving
	 * we will be willing to work harder to bring him in.
	 * Needs is an estimate of how much core he will need.
	 * If he has been out for a while, then we will
	 * bring him in with 1/2 the core he will need, otherwise
	 * we are conservative.
	 */
	deservin = 0;
	divisor = 1;
	if (outpri > maxslp/2) {
		deservin = 1;
I 23
D 26
#ifdef NOPAGING
		divisor = 1;
#else
E 26
E 23
		divisor = 2;
I 23
D 26
#endif
E 26
E 23
	}
	needs = p->p_swrss;
	if (p->p_textp && p->p_textp->x_ccount == 0)
		needs += p->p_textp->x_swrss;
I 12
	needs = imin(needs, lotsfree);
E 12
	if (freemem - deficit > needs / divisor) {
		deficit += needs;
		if (swapin(p))
			goto loop;
		deficit -= imin(needs, deficit);
	}

hardswap:
	/*
	 * Need resources (kernel map or memory), swap someone out.
	 * Select the nbig largest jobs, then the oldest of these
	 * is ``most likely to get booted.''
	 */
D 2
	VOID spl6();
E 2
I 2
D 11
	(void) spl6();
E 11
E 2
	inp = p;
	sleeper = 0;
	if (nbig > MAXNBIG)
		nbig = MAXNBIG;
	if (nbig < 1)
		nbig = 1;
	biggot = 0;
	bplist.bp_link = 0;
D 8
	for (rp = &proc[0]; rp < &proc[NPROC]; rp++) {
E 8
I 8
D 31
	for (rp = proc; rp < procNPROC; rp++) {
E 31
I 31
	for (rp = allproc; rp != NULL; rp = rp->p_nxt) {
E 31
E 8
		if (!swappable(rp))
			continue;
D 31
		if (rp->p_stat==SZOMB)
			continue;
E 31
		if (rp == inp)
			continue;
		if (rp->p_textp && rp->p_textp->x_flag&XLOCK)
			continue;
		if (rp->p_slptime > maxslp &&
D 5
		    (rp->p_stat==SSLEEP&&rp->p_pri>=PZERO||rp->p_stat==SSTOP)) {
E 5
I 5
		    (rp->p_stat==SSLEEP&&rp->p_pri>PZERO||rp->p_stat==SSTOP)) {
E 5
			if (sleeper < rp->p_slptime) {
				p = rp;
				sleeper = rp->p_slptime;
			}
		} else if (!sleeper && (rp->p_stat==SRUN||rp->p_stat==SSLEEP)) {
			rppri = rp->p_rssize;
			if (rp->p_textp)
D 3
				rppri += rp->p_textp->x_rssize / rp->p_textp->x_ccount;
E 3
I 3
				rppri += rp->p_textp->x_rssize/rp->p_textp->x_ccount;
E 3
			if (biggot < nbig)
				nbp = &bigp[biggot++];
			else {
				nbp = bplist.bp_link;
				if (nbp->bp_pri > rppri)
					continue;
				bplist.bp_link = nbp->bp_link;
			}
			for (bp = &bplist; bp->bp_link; bp = bp->bp_link)
				if (rppri < bp->bp_link->bp_pri)
					break;
			nbp->bp_link = bp->bp_link;
			bp->bp_link = nbp;
			nbp->bp_pri = rppri;
			nbp->bp_proc = rp;
		}
	}
	if (!sleeper) {
		p = NULL;
		inpri = -1000;
		for (bp = bplist.bp_link; bp; bp = bp->bp_link) {
			rp = bp->bp_proc;
			rppri = rp->p_time+rp->p_nice-NZERO;
			if (rppri >= inpri) {
				p = rp;
				inpri = rppri;
			}
		}
	}
	/*
D 6
	 * If we found a long-time sleeper, or we are desparate and
E 6
I 6
	 * If we found a long-time sleeper, or we are desperate and
E 6
	 * found anyone to swap out, or if someone deserves to come
	 * in and we didn't find a sleeper, but found someone who
	 * has been in core for a reasonable length of time, then
	 * we kick the poor luser out.
	 */
D 6
	if (sleeper || desparate && p || deservin && inpri > maxslp) {
E 6
I 6
	if (sleeper || desperate && p || deservin && inpri > maxslp) {
I 11
D 37
		(void) spl6();
E 37
I 37
		(void) splhigh();
E 37
E 11
E 6
		p->p_flag &= ~SLOAD;
		if (p->p_stat == SRUN)
			remrq(p);
I 11
		(void) spl0();
E 11
D 6
		if (desparate) {
E 6
I 6
		if (desperate) {
E 6
			/*
			 * Want to give this space to the rest of
			 * the processes in core so give them a chance
			 * by increasing the deficit.
			 */
			gives = p->p_rssize;
			if (p->p_textp)
				gives += p->p_textp->x_rssize / p->p_textp->x_ccount;
I 12
D 17
			gives = min(gives, lotsfree);
E 17
I 17
			gives = imin(gives, lotsfree);
E 17
E 12
			deficit += gives;
		} else
			gives = 0;	/* someone else taketh away */
D 47
		if (swapout(p, p->p_dsize, p->p_ssize) == 0)
E 47
I 47
		if (swapout(p, p->p_dsize, p->p_mmsize, p->p_ssize) == 0)
E 47
			deficit -= imin(gives, deficit);
D 39
		goto loop;
E 39
I 39
		else
			goto loop;
E 39
	}
	/*
	 * Want to swap someone in, but can't
	 * so wait on runin.
	 */
D 2
	VOID spl6();
E 2
I 2
D 37
	(void) spl6();
E 37
I 37
	(void) splhigh();
E 37
E 2
	runin++;
	sleep((caddr_t)&runin, PSWP);
I 11
	(void) spl0();
E 11
	goto loop;
}

E 49
vmmeter()
{
D 65
	register unsigned *cp, *rp, *sp;
E 65

D 12
	deficit -= imin(deficit, imax(deficit / 10, maxpgio / 2));
E 12
I 12
D 49
	deficit -= imin(deficit,
	    imax(deficit / 10, ((klin * CLSIZE) / 2) * maxpgio / 2));
E 12
	ave(avefree, freemem, 5);
I 12
	ave(avefree30, freemem, 30);
E 12
	/* v_pgin is maintained by clock.c */
	cp = &cnt.v_first; rp = &rate.v_first; sp = &sum.v_first;
	while (cp <= &cnt.v_last) {
		ave(*rp, *cp, 5);
		*sp += *cp;
		*cp = 0;
		rp++, cp++, sp++;
	}
D 21
	if (time % 5 == 0) {
E 21
I 21
	if (time.tv_sec % 5 == 0) {
E 49
I 49
	if (time.tv_sec % 5 == 0)
E 49
E 21
D 51
		vmtotal();
E 51
I 51
D 52
		loadav(averunnable);
E 52
I 52
		loadav(&averunnable);
E 52
E 51
D 49
		rate.v_swpin = cnt.v_swpin;
		sum.v_swpin += cnt.v_swpin;
		cnt.v_swpin = 0;
		rate.v_swpout = cnt.v_swpout;
		sum.v_swpout += cnt.v_swpout;
		cnt.v_swpout = 0;
	}
	if (avefree < minfree && runout || proc[0].p_slptime > maxslp/2) {
E 49
I 49
D 50
	if (proc[0].p_slptime > maxslp/2) {
E 49
		runout = 0;
D 49
		runin = 0;
		wakeup((caddr_t)&runin);
E 49
		wakeup((caddr_t)&runout);
	}
E 50
I 50
	if (proc0.p_slptime > maxslp/2)
		wakeup((caddr_t)&proc0);
E 50
}

D 21
vmpago()
E 21
I 21
D 36
#define	RATETOSCHEDPAGING	4		/* hz that is */

E 36
D 49
/*
 * Schedule rate for paging.
 * Rate is linear interpolation between
 * slowscan with lotsfree and fastscan when out of memory.
 */
schedpaging()
E 21
{
D 21
	register int vavail;
	register int scanrate;
E 21
I 21
D 36
	register int vavail, scanrate;
E 36
I 36
	register int vavail;
E 36
E 21

D 21
	/*
	 * Compute new rate for clock; if
	 * nonzero, restart clock.
	 * Rate ranges linearly from one rev per
	 * slowscan seconds when there is lotsfree memory
	 * available to one rev per fastscan seconds when
	 * there is no memory available.
	 */
E 21
	nscan = desscan = 0;
	vavail = freemem - deficit;
	if (vavail < 0)
		vavail = 0;
D 24
	if (freemem >= lotsfree)
		return;
	scanrate = (slowscan * vavail + fastscan * (lotsfree - vavail)) / nz(lotsfree);
D 12
	desscan = LOOPSIZ / nz(scanrate);
E 12
I 12
D 21
	desscan = (LOOPPAGES / CLSIZE) / nz(scanrate);
E 12
	/*
	 * DIVIDE BY 4 TO ACCOUNT FOR RUNNING 4* A SECOND (see clock.c)
	 */
	desscan /= 4;
E 21
I 21
	desscan = ((LOOPPAGES / CLSIZE) / nz(scanrate)) / RATETOSCHEDPAGING;
E 21
	wakeup((caddr_t)&proc[2]);
E 24
I 24
	if (freemem < lotsfree) {
D 36
		scanrate =
			(slowscan * vavail + fastscan * (lotsfree - vavail)) /
				nz(lotsfree);
		desscan = ((LOOPPAGES / CLSIZE) / nz(scanrate)) /
				RATETOSCHEDPAGING;
E 36
I 36
		desscan = (slowscan * vavail + fastscan * (lotsfree - vavail)) /
			nz(lotsfree) / RATETOSCHEDPAGING;
E 36
		wakeup((caddr_t)&proc[2]);
	}
E 24
I 21
D 22
	timeout(schedpaging, 0, hz / RATETOSCHEDPAGING);
E 22
I 22
	timeout(schedpaging, (caddr_t)0, hz / RATETOSCHEDPAGING);
E 22
E 21
}

E 49
D 51
vmtotal()
{
	register struct proc *p;
D 49
	register struct text *xp;
E 49
	int nrun = 0;

D 49
	total.t_vmtxt = 0;
	total.t_avmtxt = 0;
	total.t_rmtxt = 0;
	total.t_armtxt = 0;
D 9
	for (xp = &text[0]; xp < &text[NTEXT]; xp++)
E 9
I 9
	for (xp = text; xp < textNTEXT; xp++)
E 9
D 44
		if (xp->x_iptr) {
E 44
I 44
		if (xp->x_vptr) {
E 44
			total.t_vmtxt += xp->x_size;
			total.t_rmtxt += xp->x_rssize;
			for (p = xp->x_caddr; p; p = p->p_xlink)
			switch (p->p_stat) {

			case SSTOP:
			case SSLEEP:
				if (p->p_slptime >= maxslp)
					continue;
				/* fall into... */

			case SRUN:
			case SIDL:
				total.t_avmtxt += xp->x_size;
				total.t_armtxt += xp->x_rssize;
				goto next;
			}
next:
			;
		}
E 49
	total.t_vm = 0;
	total.t_avm = 0;
	total.t_rm = 0;
	total.t_arm = 0;
	total.t_rq = 0;
	total.t_dw = 0;
	total.t_pw = 0;
	total.t_sl = 0;
	total.t_sw = 0;
D 8
	for (p = &proc[0]; p < &proc[NPROC]; p++) {
E 8
I 8
D 31
	for (p = proc; p < procNPROC; p++) {
E 31
I 31
	for (p = allproc; p != NULL; p = p->p_nxt) {
E 31
E 8
		if (p->p_flag & SSYS)
			continue;
		if (p->p_stat) {
D 42
			total.t_vm += p->p_dsize + p->p_ssize;
			total.t_rm += p->p_rssize;
E 42
I 42
D 49
			if (p->p_stat != SZOMB) {
				total.t_vm += p->p_dsize + p->p_ssize;
				total.t_rm += p->p_rssize;
			}
E 49
E 42
			switch (p->p_stat) {

			case SSLEEP:
D 46
			case SSTOP:
D 5
				if (p->p_pri < PZERO)
E 5
I 5
D 41
				if (p->p_pri <= PZERO)
E 41
I 41
				if (p->p_pri <= PZERO && p->p_stat == SSLEEP)
E 46
I 46
				if (p->p_pri <= PZERO && p->p_slptime == 0)
E 46
E 41
E 5
					nrun++;
I 46
				/* fall through */
			case SSTOP:
I 50
#ifdef notdef
E 50
E 46
				if (p->p_flag & SPAGE)
					total.t_pw++;
D 50
				else if (p->p_flag & SLOAD) {
E 50
I 50
				else
#endif
				if (p->p_flag & SLOAD) {
E 50
D 5
					if (p->p_pri < PZERO)
E 5
I 5
					if (p->p_pri <= PZERO)
E 5
						total.t_dw++;
					else if (p->p_slptime < maxslp)
						total.t_sl++;
				} else if (p->p_slptime < maxslp)
					total.t_sw++;
				if (p->p_slptime < maxslp)
					goto active;
				break;

			case SRUN:
			case SIDL:
				nrun++;
				if (p->p_flag & SLOAD)
					total.t_rq++;
				else
					total.t_sw++;
active:
D 49
				total.t_avm += p->p_dsize + p->p_ssize;
				total.t_arm += p->p_rssize;
E 49
				break;
			}
		}
	}
D 49
	total.t_vm += total.t_vmtxt;
	total.t_avm += total.t_avmtxt;
	total.t_rm += total.t_rmtxt;
	total.t_arm += total.t_armtxt;
	total.t_free = avefree;
E 49
D 45
	loadav(avenrun, nrun);
E 45
I 45
	loadav(averunnable, nrun);
E 45
}

E 51
/*
 * Constants for averages over 1, 5, and 15 minutes
 * when sampling at 5 second intervals.
 */
D 45
double	cexp[3] = {
	0.9200444146293232,	/* exp(-1/12) */
	0.9834714538216174,	/* exp(-1/60) */
	0.9944598480048967,	/* exp(-1/180) */
E 45
I 45
fixpt_t	cexp[3] = {
	0.9200444146293232 * FSCALE,	/* exp(-1/12) */
	0.9834714538216174 * FSCALE,	/* exp(-1/60) */
	0.9944598480048967 * FSCALE,	/* exp(-1/180) */
E 45
};

/*
 * Compute a tenex style load average of a quantity on
 * 1, 5 and 15 minute intervals.
 */
I 54
void
E 54
D 51
loadav(avg, n)
E 51
I 51
loadav(avg)
E 51
D 45
	register double *avg;
E 45
I 45
D 52
	register fixpt_t *avg;
E 52
I 52
	register struct loadavg *avg;
E 52
E 45
D 51
	int n;
E 51
{
D 51
	register int i;
E 51
I 51
	register int i, nrun;
	register struct proc *p;
E 51

I 51
D 56
	for (nrun = 0, p = allproc; p != NULL; p = p->p_nxt) {
E 56
I 56
D 63
	for (nrun = 0, p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 63
I 63
D 67
	for (nrun = 0, p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 67
I 67
	for (nrun = 0, p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 67
E 63
E 56
		switch (p->p_stat) {
		case SSLEEP:
D 63
			if (p->p_pri > PZERO || p->p_slptime != 0)
E 63
I 63
			if (p->p_priority > PZERO || p->p_slptime != 0)
E 63
				continue;
			/* fall through */
		case SRUN:
		case SIDL:
			nrun++;
		}
	}
E 51
	for (i = 0; i < 3; i++)
D 45
		avg[i] = cexp[i] * avg[i] + n * (1.0 - cexp[i]);
E 45
I 45
D 51
		avg[i] = (cexp[i] * avg[i] + n * FSCALE * (FSCALE - cexp[i]))
E 51
I 51
D 52
		avg[i] = (cexp[i] * avg[i] + nrun * FSCALE * (FSCALE - cexp[i]))
E 51
		         >> FSHIFT;
E 52
I 52
		avg->ldavg[i] = (cexp[i] * avg->ldavg[i] +
			nrun * FSCALE * (FSCALE - cexp[i])) >> FSHIFT;
E 52
D 47
#ifdef COMPAT_43
E 47
I 47
D 61
#if defined(COMPAT_43) && (defined(vax) || defined(tahoe))
E 47
	for (i = 0; i < 3; i++)
D 52
		avenrun[i] = (double) averunnable[i] / FSCALE;
E 52
I 52
		avenrun[i] = (double) avg->ldavg[i] / FSCALE;
E 52
#endif /* COMPAT_43 */
E 61
I 52
}

/*
D 57
 * Load average information
E 57
I 57
 * Attributes associated with virtual memory.
E 57
 */
D 57
/* ARGSUSED */
I 54
int
E 54
kinfo_loadavg(op, where, acopysize, arg, aneeded)
	int op;
	register char *where;
	int *acopysize, arg, *aneeded;
E 57
I 57
D 58
vm_sysctl(name, namelen, oldp, oldlenp, newp, newlen)
E 58
I 58
vm_sysctl(name, namelen, oldp, oldlenp, newp, newlen, p)
E 58
	int *name;
	u_int namelen;
	void *oldp;
D 59
	u_int *oldlenp;
E 59
I 59
	size_t *oldlenp;
E 59
	void *newp;
D 59
	u_int newlen;
E 59
I 59
	size_t newlen;
E 59
I 58
	struct proc *p;
E 58
E 57
{
D 57
	int buflen, error;

	*aneeded = sizeof(averunnable);
	if (where == NULL)
		return (0);
	/*
	 * Check for enough buffering.
	 */
	buflen = *acopysize;
	if (buflen < sizeof(averunnable)) {
		*acopysize = 0;
		return (0);
	}
	/*
	 * Copyout averunnable structure.
	 */
	averunnable.fscale = FSCALE;
	if (error = copyout((caddr_t)&averunnable, where, sizeof(averunnable)))
		return (error);
	*acopysize = sizeof(averunnable);
	return (0);
E 52
I 51
}

/*
 * Calculate and return vmtotals structure.
 */
I 54
int
E 54
kinfo_meter(op, where, acopysize, arg, aneeded)
	int op;
	caddr_t where;
	int *acopysize, arg, *aneeded;
{
E 57
	struct vmtotal vmtotals;
D 57
	int error;
E 57

D 57
	*aneeded = sizeof(struct vmtotal);
	if (where == NULL)
		return (0);
	if (*acopysize < sizeof(struct vmtotal))
		return (EINVAL);
	vmtotal(&vmtotals);
	if (error = copyout((caddr_t)&vmtotals, where, sizeof(struct vmtotal)))
		return (error);
	*acopysize = sizeof(struct vmtotal);
	return (0);
E 57
I 57
	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case VM_LOADAVG:
		averunnable.fscale = FSCALE;
		return (sysctl_rdstruct(oldp, oldlenp, newp, &averunnable,
		    sizeof(averunnable)));
	case VM_METER:
		vmtotal(&vmtotals);
		return (sysctl_rdstruct(oldp, oldlenp, newp, &vmtotals,
		    sizeof(vmtotals)));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
E 57
}

/*
 * Calculate the current state of the system.
 * Done on demand from getkerninfo().
 */
I 54
void
E 54
vmtotal(totalp)
	register struct vmtotal *totalp;
{
	register struct proc *p;
	register vm_map_entry_t	entry;
	register vm_object_t object;
	register vm_map_t map;
	int paging;

	bzero(totalp, sizeof *totalp);
	/*
	 * Mark all objects as inactive.
	 */
D 55
	simple_unlock(&vm_object_list_lock);
E 55
	simple_lock(&vm_object_list_lock);
D 64
	object = (vm_object_t) queue_first(&vm_object_list);
	while (!queue_end(&vm_object_list, (queue_entry_t) object)) {
E 64
I 64
	for (object = vm_object_list.tqh_first;
	     object != NULL;
	     object = object->object_list.tqe_next)
E 64
		object->flags &= ~OBJ_ACTIVE;
D 64
		object = (vm_object_t) queue_next(&object->object_list);
	}
E 64
	simple_unlock(&vm_object_list_lock);
	/*
	 * Calculate process statistics.
	 */
D 56
	for (p = allproc; p != NULL; p = p->p_nxt) {
E 56
I 56
D 63
	for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 56
		if (p->p_flag & SSYS)
E 63
I 63
D 67
	for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 67
I 67
	for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 67
		if (p->p_flag & P_SYSTEM)
E 63
			continue;
		switch (p->p_stat) {
		case 0:
			continue;

		case SSLEEP:
		case SSTOP:
D 63
			if (p->p_flag & SLOAD) {
				if (p->p_pri <= PZERO)
E 63
I 63
			if (p->p_flag & P_INMEM) {
				if (p->p_priority <= PZERO)
E 63
					totalp->t_dw++;
				else if (p->p_slptime < maxslp)
					totalp->t_sl++;
			} else if (p->p_slptime < maxslp)
				totalp->t_sw++;
			if (p->p_slptime >= maxslp)
				continue;
			break;

		case SRUN:
		case SIDL:
D 63
			if (p->p_flag & SLOAD)
E 63
I 63
			if (p->p_flag & P_INMEM)
E 63
				totalp->t_rq++;
			else
				totalp->t_sw++;
			if (p->p_stat == SIDL)
				continue;
			break;
		}
		/*
		 * Note active objects.
I 66
		 *
		 * XXX don't count shadow objects with no resident pages.
		 * This eliminates the forced shadows caused by MAP_PRIVATE.
		 * Right now we require that such an object completely shadow
		 * the original, to catch just those cases.
E 66
		 */
		paging = 0;
		for (map = &p->p_vmspace->vm_map, entry = map->header.next;
		     entry != &map->header; entry = entry->next) {
D 53
			if (entry->is_a_map || entry->is_sub_map)
E 53
I 53
			if (entry->is_a_map || entry->is_sub_map ||
D 66
			    entry->object.vm_object == NULL)
E 66
I 66
			    (object = entry->object.vm_object) == NULL)
E 66
E 53
				continue;
D 66
			entry->object.vm_object->flags |= OBJ_ACTIVE;
			paging |= entry->object.vm_object->paging_in_progress;
E 66
I 66
			while (object->shadow &&
			       object->resident_page_count == 0 &&
			       object->shadow_offset == 0 &&
			       object->size == object->shadow->size)
				object = object->shadow;
			object->flags |= OBJ_ACTIVE;
			paging |= object->paging_in_progress;
E 66
		}
		if (paging)
			totalp->t_pw++;
	}
	/*
	 * Calculate object memory usage statistics.
	 */
	simple_lock(&vm_object_list_lock);
D 64
	object = (vm_object_t) queue_first(&vm_object_list);
	while (!queue_end(&vm_object_list, (queue_entry_t) object)) {
E 64
I 64
	for (object = vm_object_list.tqh_first;
	     object != NULL;
	     object = object->object_list.tqe_next) {
E 64
		totalp->t_vm += num_pages(object->size);
		totalp->t_rm += object->resident_page_count;
		if (object->flags & OBJ_ACTIVE) {
			totalp->t_avm += num_pages(object->size);
			totalp->t_arm += object->resident_page_count;
		}
		if (object->ref_count > 1) {
			/* shared object */
			totalp->t_vmshr += num_pages(object->size);
			totalp->t_rmshr += object->resident_page_count;
			if (object->flags & OBJ_ACTIVE) {
				totalp->t_avmshr += num_pages(object->size);
				totalp->t_armshr += object->resident_page_count;
			}
		}
D 64
		object = (vm_object_t) queue_next(&object->object_list);
E 64
	}
I 68
	simple_unlock(&vm_object_list_lock);
E 68
	totalp->t_free = cnt.v_free_count;
E 51
E 45
}
E 1
