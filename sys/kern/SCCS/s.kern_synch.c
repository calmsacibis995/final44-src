h63979
s 00004/00000/00641
d D 8.9 95/05/19 15:06:09 pendry 88 87
c accounting for simple locks and unlocks
e
s 00002/00001/00639
d D 8.8 95/02/14 10:31:53 cgd 87 86
c new argument passing conventions.  minor type size cleanup.
e
s 00001/00001/00639
d D 8.7 94/08/22 10:20:07 mckusick 86 85
c use new queue.h data structures
e
s 00005/00001/00635
d D 8.6 94/01/21 17:17:50 bostic 85 84
c add USL's copyright notice
e
s 00007/00002/00629
d D 8.5 93/09/23 18:03:17 bostic 84 83
c put back in the shift, don't use the bottom bits for hashing
e
s 00058/00057/00573
d D 8.4 93/09/23 15:41:26 bostic 83 82
c changes for 4.4BSD-Lite requested by USL
e
s 00007/00010/00623
d D 8.3 93/09/21 07:33:05 bostic 82 81
c changes for 4.4BSD-Lite requested by USL
e
s 00052/00056/00581
d D 8.2 93/09/05 09:38:45 bostic 81 80
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00635
d D 8.1 93/06/10 21:58:01 bostic 80 79
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00636
d D 7.26 92/11/18 17:52:35 torek 79 78
c p_cpticks is modified by statclock intr; must prevent state changes
c slightly sooner.  can use splstatclock instead of splhigh to do this.
e
s 00010/00010/00627
d D 7.25 92/10/11 10:38:12 bostic 78 77
c make kernel includes standard
e
s 00086/00011/00551
d D 7.24 92/07/08 00:53:12 torek 77 76
c lint; volatile poison; new C-language swtch for generic operations
e
s 00006/00006/00556
d D 7.23 92/02/28 17:24:15 bostic 76 75
c sleep, tsleep and wakeup really take void *'s, not caddr_t's.
e
s 00001/00000/00561
d D 7.22 92/02/28 16:36:13 sklower 75 74
c declare "int lbolt" here (by TK for Keith)
e
s 00002/00002/00559
d D 7.21 92/02/25 17:15:08 mckusick 74 73
c averunnable now a structure
e
s 00003/00002/00558
d D 7.20 92/02/14 17:38:04 torek 73 72
c always set sig, no need to test catch, makes gcc happy
e
s 00029/00001/00531
d D 7.19 92/02/14 17:23:53 marc 72 71
c trace context switches
e
s 00000/00002/00532
d D 7.18 91/06/27 17:27:44 karels 71 70
c sleep doesn't need spl0 (idle does it)
e
s 00006/00004/00528
d D 7.17 91/05/09 21:21:28 bostic 70 69
c new copyright; att/bsd/shared
e
s 00002/00000/00530
d D 7.16 91/05/06 12:53:41 karels 69 68
c define curpri
e
s 00006/00005/00524
d D 7.15 91/05/04 16:19:12 karels 68 67
c noproc => !curproc; don't need user.h for aston now
e
s 00103/00123/00426
d D 7.14 91/03/17 15:42:09 karels 67 66
c more-or-less working with new proc & user structs
c lots of cleanup & clarification; runrun/aston => need_resched
e
s 00003/00007/00546
d D 7.13 90/12/05 17:35:08 mckusick 66 65
c update for new VM
e
s 00030/00018/00523
d D 7.12 90/12/01 14:17:47 karels 65 64
c ready to use "safepri" from machdep
e
s 00057/00104/00484
d D 7.11 90/04/03 21:42:36 karels 64 63
c tsleep II, as it was meant to be
e
s 00135/00002/00453
d D 7.10 90/04/03 21:41:04 marc 63 62
c tsleep I (checked in for marc)
e
s 00035/00011/00420
d D 7.9 89/05/29 12:54:00 mckusick 62 61
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00000/00001/00431
d D 7.8 89/05/05 00:06:44 mckusick 61 60
c delete unneeded include of dir.h
e
s 00003/00003/00429
d D 7.7 89/04/25 10:51:08 mckusick 60 59
c ../machine => machine
e
s 00063/00001/00369
d D 7.6 87/12/11 00:13:44 mckusick 59 58
c comment decribing how p_cpu decay is computed (with help from shannon)
e
s 00000/00002/00370
d D 7.5 87/07/21 13:07:28 mckusick 58 57
c get rid of unneeded header files
e
s 00006/00005/00366
d D 7.4 87/02/19 17:29:23 karels 57 56
c make sleep spin-wait during autoconfiguration
e
s 00003/00004/00368
d D 7.3 86/11/30 18:07:57 karels 56 55
c clear slptime after stop; don't have to updatepri at high ipl
e
s 00002/00003/00370
d D 7.2 86/11/03 11:59:57 karels 55 54
c merge in tahoe support
e
s 00001/00001/00372
d D 7.1 86/06/05 00:04:49 mckusick 54 53
c 4.3BSD release version
e
s 00007/00001/00366
d D 6.10 85/06/08 14:38:24 mckusick 53 52
c Add copyright
e
s 00002/00001/00365
d D 6.9 85/06/07 15:33:15 karels 52 51
c ordering problem in wakeup, can't zero slptime before updatepri
e
s 00006/00002/00360
d D 6.8 85/06/02 22:58:32 karels 51 50
c if the change won't work, at least explain the obscurity happening;
c minor cleanup
e
s 00023/00010/00339
d D 6.7 85/05/27 19:12:50 mckusick 50 48
c round robin sleep queue (from edward@ucbmonet)
e
s 00026/00016/00333
d R 6.7 85/05/22 11:53:08 mckusick 49 48
c round robin sleep queue (from edward@monet)
e
s 00015/00002/00334
d D 6.6 85/03/18 15:20:04 karels 48 47
c sleep just drops priority briefly, then returns after a panic
c (no panic sleep, no rescheduling)
e
s 00049/00016/00287
d D 6.5 84/12/20 14:35:12 karels 47 46
c don't recalc pri of sleepers until awakened; no "panic sleep" after panics
e
s 00010/00010/00293
d D 6.4 84/08/29 20:20:29 bloom 46 45
c Change to includes.  no more ../h
e
s 00011/00007/00292
d D 6.3 84/07/31 17:29:55 karels 45 44
c move loop invariants in schedcpu; try to make curpri reflect
c the current process (still not right); curpri is always a usrpri
e
s 00001/00001/00298
d D 6.2 84/05/22 11:45:17 karels 44 43
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00000/00000/00299
d D 6.1 83/07/29 06:34:24 sam 43 42
c 4.2 distribution
e
s 00000/00014/00299
d D 4.26 83/05/21 15:35:05 sam 42 41
c no more mush
e
s 00005/00002/00308
d D 4.25 82/12/17 11:45:08 sam 41 40
c sun merge
e
s 00000/00001/00310
d D 4.24 82/10/21 20:57:27 root 40 39
c lint
e
s 00002/00002/00309
d D 4.23 82/10/17 21:49:18 root 39 38
c more lint
e
s 00001/00002/00310
d D 4.22 82/10/10 15:08:16 root 38 37
c split header files over to vax directories
e
s 00003/00091/00309
d D 4.21 82/09/08 07:57:28 root 37 36
c timeouts used for all timers now
e
s 00138/00170/00262
d D 4.20 82/09/06 22:49:31 root 36 35
c 
e
s 00029/00050/00403
d D 4.19 82/09/04 09:13:37 root 35 34
c new timer stuff and untested tsleep()
e
s 00011/00003/00442
d D 4.18 82/08/10 17:41:38 sam 34 33
c file locking
e
s 00022/00003/00423
d D 4.17 82/07/22 13:09:44 kre 33 32
c disc quotas / mush;
c father/son/brother proc pointers;
c fixed tsleep so it works with pri < PZERO
e
s 00001/00001/00425
d D 4.16 82/01/24 22:01:58 wnj 32 31
c clean up SDETACH
e
s 00062/00048/00364
d D 4.15 81/11/08 17:02:43 wnj 31 30
c cleanup and remove vrpages references
e
s 00001/00001/00411
d D 4.14 81/06/11 15:00:32 wnj 30 29
c fix to priority computation (|| with changes to clock.c)
e
s 00012/00006/00400
d D 4.13 81/04/17 17:54:32 wnj 29 28
c remove spurious high ipl's
e
s 00002/00000/00404
d D 4.12 81/04/15 12:36:40 wnj 28 27
c if running over limit in tight core situation, lower priority
e
s 00001/00000/00403
d D 4.11 81/04/13 20:34:47 root 27 26
c copy maxrss at fork time
e
s 00001/00001/00402
d D 4.10 81/03/09 01:48:55 wnj 26 25
c lint and a few minor fixed
e
s 00003/00011/00400
d D 4.9 81/03/06 11:38:36 wnj 25 24
c get rid of UCBIPC stuff
e
s 00001/00001/00410
d D 4.8 81/02/26 23:40:06 wnj 24 23
c rid of NPROC
e
s 00001/00009/00410
d D 4.7 81/02/26 04:24:56 wnj 23 22
c FASTVAX xxx or -> UNFAST
e
s 00003/00005/00416
d D 4.6 81/02/16 20:50:51 wnj 22 21
c eliminate wasteful wakeup of runin; aston() missing added
e
s 00007/00003/00414
d D 4.5 81/02/15 20:24:21 wnj 21 20
c new ast stuff
e
s 00011/00003/00406
d D 4.4 81/02/01 18:01:33 wnj 20 19
c UCBIPC crud
e
s 00001/00001/00408
d D 4.3 80/11/10 00:31:35 bill 19 18
c minor lint
e
s 00001/00001/00408
d D 4.2 80/11/09 23:35:04 bill 18 17
c function results (void)'ed for minor lint
e
s 00000/00000/00409
d D 4.1 80/11/09 17:32:37 bill 17 16
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00001/00001/00408
d D 3.16 80/10/19 01:50:30 bill 16 15
c double slope of nice
e
s 00002/00002/00407
d D 3.15 80/10/11 21:32:11 bill 15 14
c %cpu
e
s 00001/00001/00408
d D 3.14 80/09/25 21:31:42 bill 14 13
c keep NUSIG on fork
e
s 00001/00001/00408
d D 3.13 80/07/13 14:13:33 bill 13 12
c inherit SDETACH on fork(), vfork()
e
s 00000/00001/00409
d D 3.12 80/06/24 19:28:50 bill 12 11
c no swplo
e
s 00001/00001/00409
d D 3.11 80/06/07 02:47:23 bill 11 10
c %H%->%G%
e
s 00004/00004/00406
d D 3.10 80/05/24 19:45:23 bill 10 9
c new signal stuff
e
s 00017/00021/00393
d D 3.9 80/05/18 11:34:40 bill 9 8
c first stab + revised sleep, wakeup
e
s 00044/00021/00370
d D 3.8 80/05/18 10:55:34 bill 8 7
c first attempt at new slp.c
e
s 00003/00003/00388
d D 3.7 80/05/08 10:22:56 bill 7 6
c VOID=>void
e
s 00005/00003/00386
d D 3.6 80/04/16 18:02:17 bill 6 5
c tsleep fixes per dmr
e
s 00001/00001/00388
d D 3.5 80/04/14 22:59:01 bill 5 4
c ick
e
s 00044/00000/00345
d D 3.4 80/04/14 19:19:53 bill 4 3
c added tsleep()
e
s 00000/00012/00345
d D 3.3 80/04/14 18:34:28 bill 3 2
c cleanup for reasonable setjmp(), longjmp()
e
s 00001/00001/00356
d D 3.2 80/04/12 17:24:26 bill 2 1
c fix comment about SSWAP
e
s 00357/00000/00000
d D 3.1 80/04/09 16:04:11 bill 1 0
c date and time created 80/04/09 16:04:11 by bill
e
u
U
t
T
I 1
D 11
/*	%M%	%I%	%H%	*/
E 11
I 11
D 26
/*	%M%	%I%	%G%	*/
E 26
I 26
D 53
/*	%M%	%I%	%E%	*/
E 53
I 53
D 70
/*
D 54
 * Copyright (c) 1982 Regents of the University of California.
E 54
I 54
D 64
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 64
I 64
D 68
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
E 68
I 68
 * Copyright (c) 1982, 1986, 1990, 1991 Regents of the University of California.
E 68
E 64
E 54
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 70
I 70
/*-
D 80
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * Copyright (c) 1991 The Regents of the University of California.
E 80
I 80
 * Copyright (c) 1982, 1986, 1990, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 80
D 85
 * All rights reserved.
E 85
I 85
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 85
 *
 * %sccs.include.redist.c%
E 70
 *
 *	%W% (Berkeley) %G%
 */
E 53
E 26
E 11

I 41
D 60
#include "../machine/pte.h"
I 55
#include "../machine/psl.h"
#include "../machine/mtpr.h"
E 60
I 60
D 66
#include "machine/pte.h"
#include "machine/psl.h"
#include "machine/mtpr.h"
E 60
E 55

E 66
E 41
D 46
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/file.h"
#include "../h/inode.h"
#include "../h/vm.h"
D 41
#include "../h/pte.h"
E 41
I 8
D 38
#include "../h/inline.h"
I 21
#include "../h/mtpr.h"
E 38
I 36
D 42
#ifdef MUSH
E 36
I 33
#include "../h/quota.h"
I 36
#include "../h/share.h"
#endif
E 42
#include "../h/kernel.h"
#include "../h/buf.h"
E 46
I 46
D 78
#include "param.h"
#include "systm.h"
D 61
#include "dir.h"
E 61
D 68
#include "user.h"
E 68
#include "proc.h"
D 58
#include "file.h"
#include "inode.h"
E 58
D 66
#include "vm.h"
E 66
#include "kernel.h"
#include "buf.h"
I 68
#include "signalvar.h"
#include "resourcevar.h"
I 77
#include "vmmeter.h"
E 78
I 78
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/signalvar.h>
#include <sys/resourcevar.h>
#include <sys/vmmeter.h>
E 78
E 77
I 72
#ifdef KTRACE
D 78
#include "ktrace.h"
E 78
I 78
#include <sys/ktrace.h>
E 78
#endif
E 72
E 68
I 63
D 64
#include "tsleep.h"
E 64
E 63
E 46
I 38
D 41
#include "../vax/mtpr.h"	/* XXX */
E 41
E 38
E 36
E 33
E 21
E 8

I 66
D 67
#include "machine/psl.h"
#include "machine/mtpr.h"
E 67
I 67
D 78
#include "machine/cpu.h"
E 78
I 78
#include <machine/cpu.h>
E 78
E 67

I 69
D 81
u_char	curpri;			/* usrpri of curproc */
E 81
I 81
u_char	curpriority;		/* usrpri of curproc */
E 81
I 75
int	lbolt;			/* once a second sleep address */
E 75

E 69
E 66
I 41
D 55
#ifdef vax
#include "../vax/mtpr.h"	/* XXX */
#endif
E 55
E 41
I 36
/*
 * Force switch among equal priority processes every 100ms.
 */
D 77
roundrobin()
E 77
I 77
/* ARGSUSED */
void
roundrobin(arg)
	void *arg;
E 77
{

D 67
	runrun++;
	aston();
E 67
I 67
	need_resched();
E 67
D 39
	timeout(roundrobin, 0, hz / 10);
E 39
I 39
D 77
	timeout(roundrobin, (caddr_t)0, hz / 10);
E 77
I 77
D 81
	timeout(roundrobin, (void *)0, hz / 10);
E 81
I 81
	timeout(roundrobin, NULL, hz / 10);
E 81
E 77
E 39
}

D 37
/*
 * The digital decay cpu usage priority assignment is scaled to run in
 * time as expanded by the 1 minute load average.  Each second we
 * multiply the the previous cpu usage estimate by
 *		nrscale*avenrun[0]
 * The following relates the load average to the period over which
 * cpu usage is 90% forgotten:
 *	loadav 1	 5 seconds
 *	loadav 5	24 seconds
 *	loadav 10	47 seconds
 *	loadav 20	93 seconds
 * This is a great improvement on the previous algorithm which
 * decayed the priorities by a constant, and decayed away all knowledge
 * of previous activity in about 20 seconds.  Under heavy load,
 * the previous algorithm degenerated to round-robin with poor response
 * time when there was a high load average.
 */
E 37
I 37
D 47
/* constants to digital decay and forget 90% of usage in 5*loadav time */
E 37
#undef ave
#define	ave(a,b) ((int)(((int)(a*b))/(b+1)))
int	nrscale = 2;
E 47
I 47
D 59
/* fraction for digital decay to forget 90% of usage in 5*loadav sec */
E 59
I 59
/*
D 83
 * constants for digital decay and forget
 *	90% of (p_cpu) usage in 5*loadav time
E 83
I 83
 * Constants for digital decay and forget:
 *	90% of (p_estcpu) usage in 5 * loadav time
E 83
 *	95% of (p_pctcpu) usage in 60 seconds (load insensitive)
 *          Note that, as ps(1) mentions, this can let percentages
 *          total over 100% (I've seen 137.9% for 3 processes).
 *
D 83
 * Note that hardclock updates p_cpu and p_cpticks independently.
E 83
I 83
 * Note that hardclock updates p_estcpu and p_cpticks independently.
E 83
 *
D 83
 * We wish to decay away 90% of p_cpu in (5 * loadavg) seconds.
E 83
I 83
 * We wish to decay away 90% of p_estcpu in (5 * loadavg) seconds.
E 83
 * That is, the system wants to compute a value of decay such
 * that the following for loop:
 * 	for (i = 0; i < (5 * loadavg); i++)
D 83
 * 		p_cpu *= decay;
E 83
I 83
 * 		p_estcpu *= decay;
E 83
 * will compute
D 83
 * 	p_cpu *= 0.1;
E 83
I 83
 * 	p_estcpu *= 0.1;
E 83
 * for all values of loadavg:
 *
 * Mathematically this loop can be expressed by saying:
 * 	decay ** (5 * loadavg) ~= .1
 *
 * The system computes decay as:
 * 	decay = (2 * loadavg) / (2 * loadavg + 1)
 *
 * We wish to prove that the system's computation of decay
 * will always fulfill the equation:
 * 	decay ** (5 * loadavg) ~= .1
 *
 * If we compute b as:
 * 	b = 2 * loadavg
 * then
 * 	decay = b / (b + 1)
 *
 * We now need to prove two things:
 *	1) Given factor ** (5 * loadavg) ~= .1, prove factor == b/(b+1)
 *	2) Given b/(b+1) ** power ~= .1, prove power == (5 * loadavg)
 *	
 * Facts:
 *         For x close to zero, exp(x) =~ 1 + x, since
 *              exp(x) = 0! + x**1/1! + x**2/2! + ... .
 *              therefore exp(-1/b) =~ 1 - (1/b) = (b-1)/b.
 *         For x close to zero, ln(1+x) =~ x, since
 *              ln(1+x) = x - x**2/2 + x**3/3 - ...     -1 < x < 1
 *              therefore ln(b/(b+1)) = ln(1 - 1/(b+1)) =~ -1/(b+1).
 *         ln(.1) =~ -2.30
 *
 * Proof of (1):
 *    Solve (factor)**(power) =~ .1 given power (5*loadav):
 *	solving for factor,
 *      ln(factor) =~ (-2.30/5*loadav), or
D 67
 *      factor =~ exp(-1/((5/2.30)*loadav) =~ exp(-1/(2*loadav)) =
E 67
I 67
 *      factor =~ exp(-1/((5/2.30)*loadav)) =~ exp(-1/(2*loadav)) =
E 67
 *          exp(-1/b) =~ (b-1)/b =~ b/(b+1).                    QED
 *
 * Proof of (2):
 *    Solve (factor)**(power) =~ .1 given factor == (b/(b+1)):
 *	solving for power,
 *      power*ln(b/(b+1)) =~ -2.30, or
 *      power =~ 2.3 * (b + 1) = 4.6*loadav + 2.3 =~ 5*loadav.  QED
 *
 * Actual power values for the implemented algorithm are as follows:
 *      loadav: 1       2       3       4
 *      power:  5.68    10.32   14.94   19.55
 */
E 59
D 62
#define	filter(loadav) ((2 * (loadav)) / (2 * (loadav) + 1))
E 62

E 47
D 40
double	avenrun[];
E 40
D 37

/*
 * Constant for decay filter for cpu usage field
 * in process table (used by ps au).
 */
E 37
D 62
double	ccpu = 0.95122942450071400909;		/* exp(-1/20) */
E 62
I 62
/* calculations for digital decay to forget 90% of usage in 5*loadav sec */
D 67
#define	get_b(loadav)		(2 * (loadav))
#define	get_pcpu(b, cpu)	(((b) * ((cpu) & 0377)) / ((b) + FSCALE))
E 67
I 67
#define	loadfactor(loadav)	(2 * (loadav))
#define	decay_cpu(loadfac, cpu)	(((loadfac) * (cpu)) / ((loadfac) + FSCALE))
E 67
E 62

I 62
/* decay 95% of `p_pctcpu' in 60 seconds; see CCPU_SHIFT before changing */
fixpt_t	ccpu = 0.95122942450071400909 * FSCALE;		/* exp(-1/20) */

E 62
D 37
#ifdef MELB
E 37
/*
I 62
 * If `ccpu' is not equal to `exp(-1/20)' and you still want to use the
 * faster/more-accurate formula, you'll have to estimate CCPU_SHIFT below
 * and possibly adjust FSHIFT in "param.h" so that (FSHIFT >= CCPU_SHIFT).
 *
 * To estimate CCPU_SHIFT for exp(-1/20), the following formula was used:
 *	1 - exp(-1/20) ~= 0.0487 ~= 0.0488 == 1 (fixed pt, *11* bits).
 *
 * If you dont want to bother with the faster/more-accurate formula, you
 * can set CCPU_SHIFT to (FSHIFT + 1) which will use a slower/less-accurate
 * (more general) method of calculating the %age of CPU used by a process.
 */
#define	CCPU_SHIFT	11

/*
E 62
D 37
 * Automatic niceness rate & max constants
 */
#define	MAXNICE	(8 + NZERO)	/* maximum auto nice value */
#define	NFACT	(40 * hz)	/* nice++ every 40 secs cpu+sys time */
#endif

/*
E 37
D 81
 * Recompute process priorities, once a second
E 81
I 81
 * Recompute process priorities, every hz ticks.
E 81
 */
D 77
schedcpu()
E 77
I 77
/* ARGSUSED */
void
schedcpu(arg)
	void *arg;
E 77
{
I 45
D 62
	register double ccpu1 = (1.0 - ccpu) / (double)hz;
E 62
I 62
D 67
	register fixpt_t b = get_b(averunnable[0]);
E 67
I 67
D 74
	register fixpt_t loadfac = loadfactor(averunnable[0]);
E 74
I 74
	register fixpt_t loadfac = loadfactor(averunnable.ldavg[0]);
E 74
E 67
E 62
E 45
	register struct proc *p;
D 67
	register int s, a;
E 67
I 67
	register int s;
	register unsigned int newcpu;
E 67
I 47
D 62
	float scale = filter(avenrun[0]);
E 62
E 47

D 37
	s = spl6(); time.tv_sec += lbolt / hz; lbolt %= hz; splx(s);
E 37
	wakeup((caddr_t)&lbolt);
D 37

E 37
D 44
	for (p = proc; p < procNPROC; p++) if (p->p_stat && p->p_stat!=SZOMB) {
E 44
I 44
D 77
	for (p = allproc; p != NULL; p = p->p_nxt) {
E 77
I 77
D 83
	for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 83
I 83
D 86
	for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 86
I 86
	for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 86
E 83
E 77
E 44
D 42
#ifdef MUSH
D 37
		/*
		 * Charge process for memory in use
		 */
E 37
		if (p->p_quota->q_uid)
			p->p_quota->q_cost +=
			    shconsts.sc_click * p->p_rssize;
#endif
E 42
D 67
		if (p->p_time != 127)
			p->p_time++;
D 37
		if (timerisset(&p->p_seltimer) &&
		     --p->p_seltimer.tv_sec <= 0) {
			timerclear(&p->p_seltimer);
			s = spl6();
			switch (p->p_stat) {

			case SSLEEP:
				setrun(p);
				break;

			case SSTOP:
				unsleep(p);
				break;
			}
			splx(s);
		}
		if (timerisset(&p->p_realtimer.it_value) &&
		    itimerdecr(&p->p_realtimer, 1000000) == 0)
			psignal(p, SIGALRM);
E 37
		if (p->p_stat==SSLEEP || p->p_stat==SSTOP)
			if (p->p_slptime != 127)
				p->p_slptime++;
E 67
I 67
		/*
		 * Increment time in/out of memory and sleep time
		 * (if sleeping).  We ignore overflow; with 16-bit int's
		 * (remember them?) overflow takes 45 days.
		 */
D 83
		p->p_time++;
E 83
I 83
		p->p_swtime++;
E 83
		if (p->p_stat == SSLEEP || p->p_stat == SSTOP)
			p->p_slptime++;
E 67
I 62
		p->p_pctcpu = (p->p_pctcpu * ccpu) >> FSHIFT;
E 62
D 47
		if (p->p_flag&SLOAD)
D 45
			p->p_pctcpu = ccpu * p->p_pctcpu +
			    (1.0 - ccpu) * (p->p_cpticks/(float)hz);
E 45
I 45
			p->p_pctcpu = ccpu * p->p_pctcpu + ccpu1 * p->p_cpticks;
E 47
I 47
		/*
		 * If the process has slept the entire second,
		 * stop recalculating its priority until it wakes up.
		 */
D 62
		if (p->p_slptime > 1) {
			p->p_pctcpu *= ccpu;
E 62
I 62
		if (p->p_slptime > 1)
E 62
			continue;
I 79
		s = splstatclock();	/* prevent state changes */
E 79
D 62
		}
E 62
		/*
		 * p_pctcpu is only for ps.
		 */
D 62
		p->p_pctcpu = ccpu * p->p_pctcpu + ccpu1 * p->p_cpticks;
E 62
I 62
#if	(FSHIFT >= CCPU_SHIFT)
		p->p_pctcpu += (hz == 100)?
			((fixpt_t) p->p_cpticks) << (FSHIFT - CCPU_SHIFT):
                	100 * (((fixpt_t) p->p_cpticks)
				<< (FSHIFT - CCPU_SHIFT)) / hz;
#else
		p->p_pctcpu += ((FSCALE - ccpu) *
			(p->p_cpticks * FSCALE / hz)) >> FSHIFT;
#endif
E 62
E 47
E 45
		p->p_cpticks = 0;
D 42
#ifdef MUSH
E 42
D 47
		a = ave((p->p_cpu & 0377), avenrun[0]*nrscale) +
D 42
		     p->p_nice - NZERO + p->p_quota->q_nice;
#else
		a = ave((p->p_cpu & 0377), avenrun[0]*nrscale) +
E 42
		     p->p_nice - NZERO;
E 47
I 47
D 62
		a = (int) (scale * (p->p_cpu & 0377)) + p->p_nice;
E 62
I 62
D 67
		a = (int) get_pcpu(b, p->p_cpu) + p->p_nice;
E 62
E 47
D 42
#endif
E 42
		if (a < 0)
			a = 0;
		if (a > 255)
			a = 255;
		p->p_cpu = a;
		(void) setpri(p);
E 67
I 67
D 83
		newcpu = (u_int) decay_cpu(loadfac, p->p_cpu) + p->p_nice;
		p->p_cpu = min(newcpu, UCHAR_MAX);
E 83
I 83
		newcpu = (u_int) decay_cpu(loadfac, p->p_estcpu) + p->p_nice;
		p->p_estcpu = min(newcpu, UCHAR_MAX);
E 83
D 81
		setpri(p);
E 81
I 81
		resetpriority(p);
E 81
E 67
D 47
		s = spl6();	/* prevent state changes */
E 47
I 47
D 79
		s = splhigh();	/* prevent state changes */
E 79
E 47
D 83
		if (p->p_pri >= PUSER) {
E 83
I 83
		if (p->p_priority >= PUSER) {
E 83
I 45
D 67
#define	PPQ	(128 / NQS)
E 45
			if ((p != u.u_procp || noproc) &&
E 67
I 67
#define	PPQ	(128 / NQS)		/* priorities per queue */
D 68
			if ((p != curproc || noproc) &&
E 68
I 68
			if ((p != curproc) &&
E 68
E 67
			    p->p_stat == SRUN &&
D 83
			    (p->p_flag & SLOAD) &&
D 45
			    p->p_pri != p->p_usrpri) {
E 45
I 45
			    (p->p_pri / PPQ) != (p->p_usrpri / PPQ)) {
E 83
I 83
			    (p->p_flag & P_INMEM) &&
			    (p->p_priority / PPQ) != (p->p_usrpri / PPQ)) {
E 83
E 45
				remrq(p);
D 83
				p->p_pri = p->p_usrpri;
E 83
I 83
				p->p_priority = p->p_usrpri;
E 83
D 82
				setrq(p);
E 82
I 82
				setrunqueue(p);
E 82
			} else
D 83
				p->p_pri = p->p_usrpri;
E 83
I 83
				p->p_priority = p->p_usrpri;
E 83
		}
		splx(s);
	}
	vmmeter();
D 67
	if (runin!=0) {
		runin = 0;
		wakeup((caddr_t)&runin);
	}
E 67
	if (bclnlist != NULL)
D 67
		wakeup((caddr_t)&proc[2]);
E 67
I 67
		wakeup((caddr_t)pageproc);
E 67
D 39
	timeout(schedcpu, 0, hz);
E 39
I 39
D 77
	timeout(schedcpu, (caddr_t)0, hz);
E 77
I 77
	timeout(schedcpu, (void *)0, hz);
E 77
E 39
}

I 47
/*
 * Recalculate the priority of a process after it has slept for a while.
I 67
D 83
 * For all load averages >= 1 and max p_cpu of 255, sleeping for at least
 * six times the loadfactor will decay p_cpu to zero.
E 83
I 83
 * For all load averages >= 1 and max p_estcpu of 255, sleeping for at
 * least six times the loadfactor will decay p_estcpu to zero.
E 83
E 67
 */
I 77
void
E 77
updatepri(p)
	register struct proc *p;
{
D 67
	register int a = p->p_cpu & 0377;
D 62
	float scale = filter(avenrun[0]);
E 62
I 62
	register fixpt_t b = get_b(averunnable[0]);
E 67
I 67
D 83
	register unsigned int newcpu = p->p_cpu;
E 83
I 83
	register unsigned int newcpu = p->p_estcpu;
E 83
D 74
	register fixpt_t loadfac = loadfactor(averunnable[0]);
E 74
I 74
	register fixpt_t loadfac = loadfactor(averunnable.ldavg[0]);
E 74
E 67
E 62

D 67
	p->p_slptime--;		/* the first time was done in schedcpu */
	while (a && --p->p_slptime)
D 62
		a = (int) (scale * a) /* + p->p_nice */;
E 62
I 62
		a = (int) get_pcpu(b, a) /* + p->p_nice */;
E 62
I 56
	p->p_slptime = 0;
E 56
	if (a < 0)
		a = 0;
	if (a > 255)
		a = 255;
	p->p_cpu = a;
	(void) setpri(p);
E 67
I 67
	if (p->p_slptime > 5 * loadfac)
D 83
		p->p_cpu = 0;
E 83
I 83
		p->p_estcpu = 0;
E 83
	else {
		p->p_slptime--;	/* the first time was done in schedcpu */
		while (newcpu && --p->p_slptime)
			newcpu = (int) decay_cpu(loadfac, newcpu);
D 83
		p->p_cpu = min(newcpu, UCHAR_MAX);
E 83
I 83
		p->p_estcpu = min(newcpu, UCHAR_MAX);
E 83
	}
D 81
	setpri(p);
E 81
I 81
	resetpriority(p);
E 81
E 67
}

E 47
E 36
D 3
#ifdef FASTVAX
asm(" .globl _eintr");
#endif
E 3
D 21

E 21
D 83
#define SQSIZE 0100	/* Must be power of 2 */
#define HASH(x)	(( (int) x >> 5) & (SQSIZE-1))
E 83
I 83
D 84
#define TABLESIZE	64		/* Must be power of 2. */
#define LOOKUP(x)	((int)x & (TABLESIZE - 1))
E 84
I 84
/*
 * We're only looking at 7 bits of the address; everything is
 * aligned to 4, lots of things are aligned to greater powers
 * of 2.  Shift right by 8, i.e. drop the bottom 256 worth.
 */
#define TABLESIZE	128
D 87
#define LOOKUP(x)	(((int)(x) >> 8) & (TABLESIZE - 1))
E 87
I 87
#define LOOKUP(x)	(((long)(x) >> 8) & (TABLESIZE - 1))
E 87
E 84
E 83
D 50
struct proc *slpque[SQSIZE];
E 50
I 50
struct slpque {
	struct proc *sq_head;
	struct proc **sq_tailp;
D 83
} slpque[SQSIZE];
E 83
I 83
} slpque[TABLESIZE];
E 83
E 50

/*
I 65
 * During autoconfiguration or after a panic, a sleep will simply
 * lower the priority briefly to allow interrupts, then return.
 * The priority to be used (safepri) is machine-dependent, thus this
 * value is initialized and maintained in the machine-dependent layers.
 * This priority will typically be 0, or the lowest priority
 * that is safe for use on the interrupt stack; it can be made
 * higher to block network software interrupts after panics.
 */
int safepri;

/*
E 65
I 63
D 64
 * XXX - redo comments once interface is set
 * 
E 63
 * Give up the processor till a wakeup occurs
 * on chan, at which time the process
 * enters the scheduling queue at priority pri.
 * The most important effect of pri is that when
 * pri<=PZERO a signal cannot disturb the sleep;
 * if pri>PZERO signals will be processed.
 * Callers of this routine must be prepared for
 * premature return, and check that the reason for
 * sleeping has gone away.
E 64
I 64
D 81
 * General sleep call.
 * Suspends current process until a wakeup is made on chan.
 * The process will then be made runnable with priority pri.
 * Sleeps at most timo/hz seconds (0 means no timeout).
 * If pri includes PCATCH flag, signals are checked
 * before and after sleeping, else signals are not checked.
 * Returns 0 if awakened, EWOULDBLOCK if the timeout expires.
 * If PCATCH is set and a signal needs to be delivered,
 * ERESTART is returned if the current system call should be restarted
 * if possible, and EINTR is returned if the system call should
 * be interrupted by the signal (return EINTR).
E 81
I 81
 * General sleep call.  Suspends the current process until a wakeup is
 * performed on the specified identifier.  The process will then be made
 * runnable with the specified priority.  Sleeps at most timo/hz seconds
 * (0 means no timeout).  If pri includes PCATCH flag, signals are checked
 * before and after sleeping, else signals are not checked.  Returns 0 if
 * awakened, EWOULDBLOCK if the timeout expires.  If PCATCH is set and a
 * signal needs to be delivered, ERESTART is returned if the current system
 * call should be restarted if possible, and EINTR is returned if the system
 * call should be interrupted by the signal (return EINTR).
E 81
E 64
 */
I 77
int
E 77
I 63
D 64

/*
 * interruptable sleep with longjmp processing.
 * TEMPORARY UNTIL ALL CALLERS ARE TAUGHT TO UNWIND
 */
tsleep(chan, pri, wmesg, timeout)
E 64
I 64
D 81
tsleep(chan, pri, wmesg, timo)
E 64
D 76
	caddr_t chan;
E 76
I 76
	void *chan;
E 76
	int pri;
E 81
I 81
tsleep(ident, priority, wmesg, timo)
	void *ident;
	int priority, timo;
E 81
	char *wmesg;
D 64
	int timeout;
{
	if (pri <= PZERO) 
		panic("tsleep: pri <= PZERO");
	if (isleep(chan, pri, wmesg, timeout) == EINTR)
		longjmp(&u.u_qsave);
}

/*
 * Interruptable sleep.
 * Sleeps on chan for time of at most timo/hz seconds (0 means no timeout).
 * Returns 0 if awakened, EINTR if a signal needs to be delivered,
 * or EWOULDBLOCK if the timeout expires.
 */
isleep(chan, pri, wmesg, timo)
	caddr_t chan;
	int pri;
	char *wmesg;
E 64
D 81
	int timo;
E 81
{
D 67
	register struct proc *rp;
E 67
I 67
D 68
	register struct proc *p = curproc;		/* XXX */
E 68
I 68
	register struct proc *p = curproc;
E 68
E 67
	register struct slpque *qp;
	register s;
I 64
D 81
	int sig, catch = pri & PCATCH;
E 81
I 81
	int sig, catch = priority & PCATCH;
E 81
E 64
	extern int cold;
D 77
	int endtsleep();
E 77
I 77
	void endtsleep __P((void *));
E 77

I 72
#ifdef KTRACE
	if (KTRPOINT(p, KTR_CSW))
		ktrcsw(p->p_tracep, 1, 0);
#endif
E 72
D 67
	rp = u.u_procp;
E 67
	s = splhigh();
	if (cold || panicstr) {
		/*
		 * After a panic, or during autoconfiguration,
		 * just give interrupts a chance, then just return;
		 * don't run any other procs or panic below,
		 * in case this is the idle process and already asleep.
D 64
		 * The splnet should be spl0 if the network was being used
		 * by the filesystem, but for now avoid network interrupts
		 * that might cause another panic.
E 64
		 */
D 64
		(void) splnet();
E 64
I 64
D 65
		(void) spl0();
E 65
I 65
		splx(safepri);
E 65
E 64
		splx(s);
		return (0);
	}
#ifdef DIAGNOSTIC
D 64
	if (chan==0 || rp->p_stat != SRUN || rp->p_rlink)
		panic("isleep");
E 64
I 64
D 67
	if (chan == 0 || rp->p_stat != SRUN || rp->p_rlink)
E 67
I 67
D 76
	if (chan == 0 || p->p_stat != SRUN || p->p_rlink)
E 76
I 76
D 81
	if (chan == NULL || p->p_stat != SRUN || p->p_rlink)
E 81
I 81
D 83
	if (ident == NULL || p->p_stat != SRUN || p->p_rlink)
E 83
I 83
	if (ident == NULL || p->p_stat != SRUN || p->p_back)
E 83
E 81
E 76
E 67
		panic("tsleep");
E 64
#endif
D 67
	rp->p_wchan = chan;
	rp->p_wmesg = wmesg;
	rp->p_slptime = 0;
D 64
	rp->p_pri = pri;
E 64
I 64
	rp->p_pri = pri & PRIMASK;
E 67
I 67
D 81
	p->p_wchan = chan;
E 81
I 81
	p->p_wchan = ident;
E 81
	p->p_wmesg = wmesg;
	p->p_slptime = 0;
D 81
	p->p_pri = pri & PRIMASK;
E 67
E 64
	qp = &slpque[HASH(chan)];
E 81
I 81
D 83
	p->p_pri = priority & PRIMASK;
	qp = &slpque[HASH(ident)];
E 83
I 83
	p->p_priority = priority & PRIMASK;
	qp = &slpque[LOOKUP(ident)];
E 83
E 81
	if (qp->sq_head == 0)
D 67
		qp->sq_head = rp;
E 67
I 67
		qp->sq_head = p;
E 67
	else
D 67
		*qp->sq_tailp = rp;
	*(qp->sq_tailp = &rp->p_link) = 0;
E 67
I 67
		*qp->sq_tailp = p;
D 83
	*(qp->sq_tailp = &p->p_link) = 0;
E 83
I 83
	*(qp->sq_tailp = &p->p_forw) = 0;
E 83
E 67
I 65
	if (timo)
D 67
		timeout(endtsleep, (caddr_t)rp, timo);
E 67
I 67
D 77
		timeout(endtsleep, (caddr_t)p, timo);
E 77
I 77
		timeout(endtsleep, (void *)p, timo);
E 77
E 67
E 65
	/*
D 64
	 * If we stop in issig(), wakeup may already have happened
	 * when we return (rp->p_wchan will then be 0).
E 64
I 64
D 65
	 * If we stop in CURSIG/issig(), wakeup may already
	 * have happened when we return.
	 * rp->p_wchan will then be 0.
E 65
I 65
D 67
	 * If we stop in CURSIG/issig(), a wakeup or a SIGCONT
	 * (or both) could occur while we were stopped.
E 67
I 67
	 * We put ourselves on the sleep queue and start our timeout
	 * before calling CURSIG, as we could stop there, and a wakeup
	 * or a SIGCONT (or both) could occur while we were stopped.
E 67
	 * A SIGCONT would cause us to be marked as SSLEEP
	 * without resuming us, thus we must be ready for sleep
	 * when CURSIG is called.  If the wakeup happens while we're
D 67
	 * stopped, rp->p_wchan will be 0 upon return from CURSIG.
E 67
I 67
	 * stopped, p->p_wchan will be 0 upon return from CURSIG.
E 67
E 65
E 64
	 */
D 64
	if (CURSIG(rp)) {
		if (rp->p_wchan)
			unsleep(rp);
		rp->p_stat = SRUN;
		splx(s);
		return (EINTR);
E 64
I 64
	if (catch) {
I 65
D 67
		rp->p_flag |= SSINTR;
E 65
		if (sig = CURSIG(rp)) {
			if (rp->p_wchan)
				unsleep(rp);
			rp->p_stat = SRUN;
E 67
I 67
D 83
		p->p_flag |= SSINTR;
E 83
I 83
		p->p_flag |= P_SINTR;
E 83
		if (sig = CURSIG(p)) {
			if (p->p_wchan)
				unsleep(p);
			p->p_stat = SRUN;
E 67
D 65
			splx(s);
			if (u.u_sigintr & sigmask(sig))
				return (EINTR);
			return (ERESTART);
E 65
I 65
			goto resume;
E 65
		}
D 67
		if (rp->p_wchan == 0) {
E 67
I 67
		if (p->p_wchan == 0) {
E 67
D 65
			splx(s);
			return (0);
E 65
I 65
			catch = 0;
			goto resume;
E 65
		}
D 65
		rp->p_flag |= SSINTR;
E 65
E 64
D 73
	}
E 73
I 73
	} else
		sig = 0;
E 73
D 64
	if (rp->p_wchan == 0) {
		splx(s);
		return (0);
	}
E 64
D 67
	rp->p_stat = SSLEEP;
E 67
I 67
	p->p_stat = SSLEEP;
E 67
D 65
	if (timo)
		timeout(endtsleep, (caddr_t)rp, timo);
E 65
D 71
	(void) spl0();
E 71
D 67
	u.u_ru.ru_nvcsw++;
E 67
I 67
	p->p_stats->p_ru.ru_nvcsw++;
E 67
D 83
	swtch();
E 83
I 83
	mi_switch();
E 83
I 65
resume:
E 65
D 67
	curpri = rp->p_usrpri;
E 67
I 67
D 81
	curpri = p->p_usrpri;
E 81
I 81
	curpriority = p->p_usrpri;
E 81
E 67
	splx(s);
I 64
D 67
	rp->p_flag &= ~SSINTR;
E 64
	if (rp->p_flag & STIMO) {
		rp->p_flag &= ~STIMO;
E 67
I 67
D 83
	p->p_flag &= ~SSINTR;
	if (p->p_flag & STIMO) {
		p->p_flag &= ~STIMO;
E 83
I 83
	p->p_flag &= ~P_SINTR;
	if (p->p_flag & P_TIMEOUT) {
		p->p_flag &= ~P_TIMEOUT;
E 83
E 67
D 65
		return (EWOULDBLOCK);
	}
	if (timo)
E 65
I 65
D 72
		if (catch == 0 || sig == 0)
E 72
I 72
D 73
		if (catch == 0 || sig == 0) {
E 73
I 73
		if (sig == 0) {
E 73
#ifdef KTRACE
			if (KTRPOINT(p, KTR_CSW))
				ktrcsw(p->p_tracep, 0, 0);
#endif
E 72
			return (EWOULDBLOCK);
I 72
		}
E 72
	} else if (timo)
E 65
D 67
		untimeout(endtsleep, (caddr_t)rp);
D 64
	if (CURSIG(rp))
		return (EINTR);
E 64
I 64
D 65
	if (catch && (sig = CURSIG(rp))) {
E 65
I 65
	if (catch && (sig != 0 || (sig = CURSIG(rp)))) {
E 65
		if (u.u_sigintr & sigmask(sig))
E 67
I 67
D 77
		untimeout(endtsleep, (caddr_t)p);
E 77
I 77
		untimeout(endtsleep, (void *)p);
E 77
	if (catch && (sig != 0 || (sig = CURSIG(p)))) {
I 72
#ifdef KTRACE
		if (KTRPOINT(p, KTR_CSW))
			ktrcsw(p->p_tracep, 0, 0);
#endif
E 72
		if (p->p_sigacts->ps_sigintr & sigmask(sig))
E 67
			return (EINTR);
		return (ERESTART);
	}
I 72
#ifdef KTRACE
	if (KTRPOINT(p, KTR_CSW))
		ktrcsw(p->p_tracep, 0, 0);
#endif
E 72
E 64
	return (0);
}

/*
 * Implement timeout for tsleep.
 * If process hasn't been awakened (wchan non-zero),
 * set timeout flag and undo the sleep.  If proc
 * is stopped, just unsleep so it will remain stopped.
 */
D 77
endtsleep(p)
	register struct proc *p;
E 77
I 77
void
endtsleep(arg)
	void *arg;
E 77
{
D 77
	int s = splhigh();
E 77
I 77
	register struct proc *p;
	int s;
E 77

I 77
	p = (struct proc *)arg;
	s = splhigh();
E 77
	if (p->p_wchan) {
		if (p->p_stat == SSLEEP)
D 82
			setrun(p);
E 82
I 82
			setrunnable(p);
E 82
		else
			unsleep(p);
D 83
		p->p_flag |= STIMO;
E 83
I 83
		p->p_flag |= P_TIMEOUT;
E 83
	}
	splx(s);
}

D 64
int sleepdebug = 1;	/* XXX */

E 64
I 64
/*
 * Short-term, non-interruptable sleep.
 */
I 77
void
E 77
E 64
E 63
D 81
sleep(chan, pri)
D 35
caddr_t chan;
E 35
I 35
D 76
	caddr_t chan;
E 76
I 76
	void *chan;
E 76
	int pri;
E 81
I 81
sleep(ident, priority)
	void *ident;
	int priority;
E 81
E 35
{
D 9
	register struct proc *rp;
E 9
I 9
D 50
	register struct proc *rp, **hp;
E 50
I 50
D 67
	register struct proc *rp;
E 67
I 67
D 68
	register struct proc *p = curproc;		/* XXX */
E 68
I 68
	register struct proc *p = curproc;
E 68
E 67
	register struct slpque *qp;
E 50
E 9
D 10
	register s, h;
E 10
I 10
	register s;
I 57
	extern int cold;
E 57
E 10

I 64
#ifdef DIAGNOSTIC
D 81
	if (pri > PZERO) {
		printf("sleep called with pri %d > PZERO, wchan: %x\n",
D 76
			pri, chan);
E 76
I 76
		    pri, chan);
E 81
I 81
	if (priority > PZERO) {
		printf("sleep called with priority %d > PZERO, wchan: %x\n",
		    priority, ident);
E 81
E 76
		panic("old sleep");
	}
#endif
E 64
D 67
	rp = u.u_procp;
E 67
D 47
	s = spl6();
	if (chan==0 || rp->p_stat != SRUN || rp->p_rlink)
E 47
I 47
	s = splhigh();
D 48
	if ((chan==0 || rp->p_stat != SRUN || rp->p_rlink) &&
	    panicstr == (char *) NULL)
E 48
I 48
D 57
	if (panicstr) {
E 57
I 57
	if (cold || panicstr) {
E 57
		/*
D 57
		 * After a panic, just give interrupts a chance,
		 * then just return; don't run any other procs 
		 * or panic below, in case this is the idle process
		 * and already asleep.
E 57
I 57
		 * After a panic, or during autoconfiguration,
		 * just give interrupts a chance, then just return;
		 * don't run any other procs or panic below,
		 * in case this is the idle process and already asleep.
E 57
D 64
		 * The splnet should be spl0 if the network was being used
		 * by the filesystem, but for now avoid network interrupts
		 * that might cause another panic.
E 64
		 */
D 64
		(void) splnet();
E 64
I 64
D 65
		(void) spl0();
E 65
I 65
		splx(safepri);
E 65
E 64
		splx(s);
		return;
	}
I 63
#ifdef DIAGNOSTIC
E 63
D 67
	if (chan==0 || rp->p_stat != SRUN || rp->p_rlink)
E 67
I 67
D 76
	if (chan==0 || p->p_stat != SRUN || p->p_rlink)
E 76
I 76
D 81
	if (chan == NULL || p->p_stat != SRUN || p->p_rlink)
E 81
I 81
D 83
	if (ident == NULL || p->p_stat != SRUN || p->p_rlink)
E 83
I 83
	if (ident == NULL || p->p_stat != SRUN || p->p_back)
E 83
E 81
E 76
E 67
E 48
E 47
		panic("sleep");
I 63
#endif
E 63
D 9
	rp->p_stat = SSLEEP;
E 9
D 67
	rp->p_wchan = chan;
I 63
	rp->p_wmesg = NULL;
E 63
	rp->p_slptime = 0;
	rp->p_pri = pri;
E 67
I 67
D 81
	p->p_wchan = chan;
E 81
I 81
	p->p_wchan = ident;
E 81
	p->p_wmesg = NULL;
	p->p_slptime = 0;
D 81
	p->p_pri = pri;
E 67
D 9
	h = HASH(chan);
	rp->p_link = slpque[h];
	slpque[h] = rp;
E 9
I 9
D 50
	hp = &slpque[HASH(chan)];
	rp->p_link = *hp;
	*hp = rp;
E 50
I 50
	qp = &slpque[HASH(chan)];
E 81
I 81
D 83
	p->p_pri = priority;
	qp = &slpque[HASH(ident)];
E 83
I 83
	p->p_priority = priority;
	qp = &slpque[LOOKUP(ident)];
E 83
E 81
	if (qp->sq_head == 0)
D 67
		qp->sq_head = rp;
E 67
I 67
		qp->sq_head = p;
E 67
	else
D 67
		*qp->sq_tailp = rp;
	*(qp->sq_tailp = &rp->p_link) = 0;
E 50
E 9
D 31
	if(pri > PZERO) {
D 8
		if(rp->p_sig && issig()) {
E 8
I 8
		if(ISSIG(rp)) {
E 31
I 31
D 64
	if (pri > PZERO) {
I 63
		if (sleepdebug)
			printf("sleep called with pri > PZERO, wchan: %x\n",
				chan);
E 63
I 51
		/*
		 * If we stop in issig(), wakeup may already have happened
		 * when we return (rp->p_wchan will then be 0).
		 */
E 51
D 63
		if (ISSIG(rp)) {
E 63
I 63
		if (CURSIG(rp)) {
E 63
E 31
E 8
D 9
			rp->p_wchan = 0;
E 9
I 9
			if (rp->p_wchan)
				unsleep(rp);
E 9
			rp->p_stat = SRUN;
D 9
			slpque[h] = rp->p_link;
E 9
D 7
			VOID spl0();
E 7
I 7
			(void) spl0();
E 7
			goto psig;
		}
I 9
		if (rp->p_wchan == 0)
			goto out;
		rp->p_stat = SSLEEP;
E 9
D 7
		VOID spl0();
E 7
I 7
		(void) spl0();
I 35
		u.u_ru.ru_nvcsw++;
E 35
E 7
D 22
		if(runin != 0) {
			runin = 0;
			wakeup((caddr_t)&runin);
		}
E 22
		swtch();
D 8
		if(rp->p_sig && issig())
E 8
I 8
D 31
		if(ISSIG(rp))
E 31
I 31
D 63
		if (ISSIG(rp))
E 63
I 63
		if (CURSIG(rp))
E 63
E 31
E 8
			goto psig;
	} else {
I 10
		rp->p_stat = SSLEEP;
E 10
D 7
		VOID spl0();
E 7
I 7
		(void) spl0();
I 35
		u.u_ru.ru_nvcsw++;
E 35
E 7
		swtch();
	}
E 64
I 64
	rp->p_stat = SSLEEP;
E 67
I 67
		*qp->sq_tailp = p;
D 83
	*(qp->sq_tailp = &p->p_link) = 0;
E 83
I 83
	*(qp->sq_tailp = &p->p_forw) = 0;
E 83
	p->p_stat = SSLEEP;
E 67
D 71
	(void) spl0();
E 71
D 67
	u.u_ru.ru_nvcsw++;
E 67
I 67
	p->p_stats->p_ru.ru_nvcsw++;
I 72
#ifdef KTRACE
	if (KTRPOINT(p, KTR_CSW))
		ktrcsw(p->p_tracep, 1, 0);
#endif
E 72
E 67
D 83
	swtch();
E 83
I 83
	mi_switch();
E 83
I 72
#ifdef KTRACE
	if (KTRPOINT(p, KTR_CSW))
		ktrcsw(p->p_tracep, 0, 0);
#endif
E 72
E 64
I 45
D 67
	curpri = rp->p_usrpri;
E 67
I 67
D 81
	curpri = p->p_usrpri;
E 81
I 81
	curpriority = p->p_usrpri;
E 81
E 67
E 45
I 9
D 64
out:
E 64
E 9
	splx(s);
D 64
	return;

	/*
	 * If priority was low (>PZERO) and
D 31
	 * there has been a signal,
	 * execute non-local goto to
	 * the qsav location.
	 * (see trap1/trap.c)
E 31
I 31
	 * there has been a signal, execute non-local goto through
D 37
	 * u.u_qsav, aborting the system call in progress (see trap.c)
E 37
I 37
	 * u.u_qsave, aborting the system call in progress (see trap.c)
E 37
D 47
	 * (or finishing a tsleep, see below)
E 47
E 31
	 */
psig:
D 3
#ifndef FASTVAX
E 3
D 37
	longjmp(u.u_qsav);
E 37
I 37
	longjmp(&u.u_qsave);
E 37
D 3
#else
	asm(".set U_SSAV,140");
	asm("movl _u+U_SSAV,fp");
	asm("movl _u+U_SSAV+4,sp");
	asm("movl _u+U_SSAV+8,r11");
	u.u_error = EINTR;
	asm("jmp _eintr");
#endif
E 3
	/*NOTREACHED*/
E 64
D 37
}

/*
I 4
D 35
 * Sleep on chan at pri.
 * Return in no more than the indicated number of seconds.
 * (If seconds==0, no timeout implied)
 * Return	TS_OK if chan was awakened normally
 *		TS_TIME if timeout occurred
 *		TS_SIG if asynchronous signal occurred
I 31
 *
 * SHOULD HAVE OPTION TO SLEEP TO ABSOLUTE TIME OR AN
 * INCREMENT IN MILLISECONDS!
E 35
I 35
 * Sleep on chan at pri for at most a specified amount of time.
 * Return (TS_OK,TS_TIME,TS_SIG) on (normal,timeout,signal) condition.
E 35
E 31
 */
D 35
tsleep(chan, pri, seconds)
E 35
I 35
tsleep(chan, pri, tvp)
E 35
D 31
caddr_t chan;
E 31
I 31
	caddr_t chan;
D 35
	int pri, seconds;
E 35
I 35
	int pri;
	struct timeval *tvp;
E 35
E 31
{
D 35
	label_t lqsav;
	register struct proc *pp;
D 33
	register sec, n, rval;
E 33
I 33
	register sec, n, rval, sov;
E 35
I 35
	register struct proc *p = u.u_procp;
	int s, rval;
E 35
E 33

D 35
	pp = u.u_procp;
I 5
	n = spl7();
E 5
	sec = 0;
	rval = 0;
I 33
	sov = 0;
E 33
D 5
	n = spl7();
E 5
	if (pp->p_clktim && pp->p_clktim<seconds)
D 33
		seconds = 0;
E 33
I 33
		if (pri > PZERO)
			seconds = 0;
		else
			sov++;
E 33
	if (seconds) {
		pp->p_flag |= STIMO;
D 6
		if ((sec = pp->p_clktim-seconds) < 0)
			sec = 0;
E 6
I 6
		sec = pp->p_clktim-seconds;
E 6
		pp->p_clktim = seconds;
	}
	bcopy((caddr_t)u.u_qsav, (caddr_t)lqsav, sizeof (label_t));
	if (setjmp(u.u_qsav))
		rval = TS_SIG;
	else {
E 35
I 35
	s = spl7();
D 36
	if (timercmp(tvp, &p->p_realtimer.itimer_value, >)) {
E 36
I 36
	if (timercmp(tvp, &p->p_realtimer.it_value, >)) {
E 36
		/* alarm will occur first! */
E 35
		sleep(chan, pri);
D 35
		if ((pp->p_flag&STIMO)==0 && seconds)
			rval = TS_TIME;
		else
E 35
I 35
		rval = TS_OK;		/* almost NOTREACHED modulo fuzz */
	} else {
		label_t lqsav;

		bcopy((caddr_t)u.u_qsav, (caddr_t)lqsav, sizeof (label_t));
		p->p_seltimer = *tvp;
		if (setjmp(u.u_qsav))
			rval = TS_SIG;
		else {
			sleep(chan, pri);
E 35
			rval = TS_OK;
D 35
	}
	pp->p_flag &= ~STIMO;
	bcopy((caddr_t)lqsav, (caddr_t)u.u_qsav, sizeof (label_t));
D 6
	pp->p_clktim += sec;
E 6
I 6
	if (sec > 0)
		pp->p_clktim += sec;
D 33
	else
E 33
I 33
	else if (sov) {
		if ((pp->p_clktim += sec) <= 0) {
			pp->p_clktim = 0;
			psignal(pp, SIGALRM);
E 35
		}
D 35
	} else
E 33
		pp->p_clktim = 0;
E 6
	splx(n);
E 35
I 35
		timerclear(&p->p_seltimer);
		bcopy((caddr_t)lqsav, (caddr_t)u.u_qsav, sizeof (label_t));
	}
	splx(s);
E 35
D 31
	return(rval);
E 31
I 31
	return (rval);
E 37
E 31
}

/*
I 8
 * Remove a process from its wait queue
 */
I 77
void
E 77
unsleep(p)
D 31
register struct proc *p;
E 31
I 31
	register struct proc *p;
E 31
{
I 50
	register struct slpque *qp;
E 50
	register struct proc **hp;
D 50
	register s;
E 50
I 50
	int s;
E 50

D 47
	s = spl6();
E 47
I 47
	s = splhigh();
E 47
	if (p->p_wchan) {
D 50
		hp = &slpque[HASH(p->p_wchan)];
E 50
I 50
D 83
		hp = &(qp = &slpque[HASH(p->p_wchan)])->sq_head;
E 83
I 83
		hp = &(qp = &slpque[LOOKUP(p->p_wchan)])->sq_head;
E 83
E 50
		while (*hp != p)
D 83
			hp = &(*hp)->p_link;
		*hp = p->p_link;
I 50
		if (qp->sq_tailp == &p->p_link)
E 83
I 83
			hp = &(*hp)->p_forw;
		*hp = p->p_forw;
		if (qp->sq_tailp == &p->p_forw)
E 83
			qp->sq_tailp = hp;
E 50
		p->p_wchan = 0;
	}
	splx(s);
}

/*
E 8
E 4
D 67
 * Wake up all processes sleeping on chan.
E 67
I 67
D 81
 * Wakeup on "chan"; set all processes
 * sleeping on chan to run state.
E 81
I 81
 * Make all processes sleeping on the specified identifier runnable.
E 81
E 67
 */
I 77
void
E 77
D 81
wakeup(chan)
D 31
register caddr_t chan;
E 31
I 31
D 76
	register caddr_t chan;
E 76
I 76
	register void *chan;
E 81
I 81
wakeup(ident)
	register void *ident;
E 81
E 76
E 31
{
D 9
	register struct proc *p, *q;
	register i;
E 9
I 9
D 50
	register struct proc *p, **q, **h;
E 50
I 50
	register struct slpque *qp;
	register struct proc *p, **q;
E 50
E 9
	int s;

D 47
	s = spl6();
E 47
I 47
	s = splhigh();
E 47
D 9
	i = HASH(chan);
E 9
I 9
D 50
	h = &slpque[HASH(chan)];
E 50
I 50
D 81
	qp = &slpque[HASH(chan)];
E 81
I 81
D 83
	qp = &slpque[HASH(ident)];
E 83
I 83
	qp = &slpque[LOOKUP(ident)];
E 83
E 81
E 50
E 9
restart:
D 9
	p = slpque[i];
	q = NULL;
	while(p != NULL) {
E 9
I 9
D 50
	for (q = h; p = *q; ) {
E 50
I 50
	for (q = &qp->sq_head; p = *q; ) {
I 63
#ifdef DIAGNOSTIC
E 63
E 50
E 9
D 8
		if (p->p_rlink || p->p_stat != SSLEEP)
E 8
I 8
D 83
		if (p->p_rlink || p->p_stat != SSLEEP && p->p_stat != SSTOP)
E 83
I 83
		if (p->p_back || p->p_stat != SSLEEP && p->p_stat != SSTOP)
E 83
E 8
			panic("wakeup");
I 63
#endif
E 63
D 10
		if (p->p_wchan==chan && p->p_stat!=SZOMB) {
E 10
I 10
D 67
		if (p->p_wchan==chan) {
E 67
I 67
D 81
		if (p->p_wchan == chan) {
E 81
I 81
		if (p->p_wchan == ident) {
E 81
E 67
E 10
D 9
			if (q == NULL)
				slpque[i] = p->p_link;
			else
				q->p_link = p->p_link;
E 9
			p->p_wchan = 0;
I 9
D 83
			*q = p->p_link;
I 47
D 51
			if (p->p_slptime > 1)
				updatepri(p);
E 51
I 50
			if (qp->sq_tailp == &p->p_link)
E 83
I 83
			*q = p->p_forw;
			if (qp->sq_tailp == &p->p_forw)
E 83
				qp->sq_tailp = q;
E 50
E 47
E 9
D 52
			p->p_slptime = 0;
E 52
D 8
			/* OPTIMIZED INLINE EXPANSION OF setrun(p) */
			p->p_stat = SRUN;
			if (p->p_flag & SLOAD) {
E 8
I 8
			if (p->p_stat == SSLEEP) {
D 82
				/* OPTIMIZED INLINE EXPANSION OF setrun(p) */
E 82
I 82
				/* OPTIMIZED EXPANSION OF setrunnable(p); */
E 82
I 51
				if (p->p_slptime > 1)
					updatepri(p);
I 67
				p->p_slptime = 0;
E 67
I 52
D 56
				p->p_slptime = 0;
E 56
E 52
E 51
				p->p_stat = SRUN;
D 23
				if (p->p_flag & SLOAD) {
E 8
#ifndef FASTVAX
D 8
				p->p_link = runq;
				runq = p->p_link;
E 8
I 8
					p->p_link = runq;
					runq = p->p_link;
E 8
#else
E 23
I 23
D 83
				if (p->p_flag & SLOAD)
E 83
I 83
				if (p->p_flag & P_INMEM)
E 83
E 23
D 8
				setrq(p);
E 8
I 8
D 82
					setrq(p);
E 82
I 82
					setrunqueue(p);
E 82
E 8
D 23
#endif
I 8
				}
E 23
D 21
				if(p->p_pri < curpri)
E 21
I 21
D 31
				if(p->p_pri < curpri) {
E 31
I 31
D 45
				if (p->p_pri < curpri) {
E 31
E 21
					runrun++;
I 21
					aston();
				}
E 45
I 45
				/*
D 81
				 * Since curpri is a usrpri,
				 * p->p_pri is always better than curpri.
E 81
I 81
				 * Since curpriority is a user priority,
D 83
				 * p->p_pri is always better than curpriority.
E 83
I 83
				 * p->p_priority is always better than
				 * curpriority.
E 83
E 81
				 */
D 67
				runrun++;
				aston();
E 45
E 21
D 29
				if(runout != 0 && (p->p_flag&SLOAD) == 0) {
					runout = 0;
					wakeup((caddr_t)&runout);
E 29
I 29
				if ((p->p_flag&SLOAD) == 0) {
					if (runout != 0) {
						runout = 0;
						wakeup((caddr_t)&runout);
					}
					wantin++;
E 29
				}
E 67
I 67
D 83
				if ((p->p_flag&SLOAD) == 0)
E 83
I 83
				if ((p->p_flag & P_INMEM) == 0)
E 83
					wakeup((caddr_t)&proc0);
				else
					need_resched();
E 67
				/* END INLINE EXPANSION */
I 9
				goto restart;
E 9
E 8
			}
I 52
D 56
			p->p_slptime = 0;
E 56
E 52
D 8
			if(p->p_pri < curpri)
				runrun++;
			if(runout != 0 && (p->p_flag&SLOAD) == 0) {
				runout = 0;
				wakeup((caddr_t)&runout);
			}
			/* END INLINE EXPANSION */
E 8
D 9
			goto restart;
		}
		q = p;
		p = p->p_link;
E 9
I 9
		} else
D 83
			q = &p->p_link;
E 83
I 83
			q = &p->p_forw;
E 83
E 9
	}
	splx(s);
}

D 23
#ifdef FASTVAX
E 23
/*
I 77
D 83
 * The machine independent parts of swtch().
E 83
I 83
 * The machine independent parts of mi_switch().
E 83
 * Must be called at splstatclock() or higher.
 */
void
D 83
swtch()
E 83
I 83
mi_switch()
E 83
{
	register struct proc *p = curproc;	/* XXX */
	register struct rlimit *rlim;
	register long s, u;
	struct timeval tv;

I 88
#ifdef DEBUG
	if (p->p_simple_locks)
		panic("sleep: holding simple lock");
#endif
E 88
	/*
	 * Compute the amount of time during which the current
	 * process was running, and add that to its total so far.
	 */
	microtime(&tv);
	u = p->p_rtime.tv_usec + (tv.tv_usec - runtime.tv_usec);
	s = p->p_rtime.tv_sec + (tv.tv_sec - runtime.tv_sec);
	if (u < 0) {
		u += 1000000;
		s--;
	} else if (u >= 1000000) {
		u -= 1000000;
		s++;
	}
	p->p_rtime.tv_usec = u;
	p->p_rtime.tv_sec = s;

	/*
	 * Check if the process exceeds its cpu resource allocation.
	 * If over max, kill it.  In any case, if it has run for more
	 * than 10 minutes, reduce priority to give others a chance.
	 */
	rlim = &p->p_rlimit[RLIMIT_CPU];
	if (s >= rlim->rlim_cur) {
		if (s >= rlim->rlim_max)
			psignal(p, SIGKILL);
		else {
			psignal(p, SIGXCPU);
			if (rlim->rlim_cur < rlim->rlim_max)
				rlim->rlim_cur += 5;
		}
	}
	if (s > 10 * 60 && p->p_ucred->cr_uid && p->p_nice == NZERO) {
		p->p_nice = NZERO + 4;
D 81
		setpri(p);
E 81
I 81
		resetpriority(p);
E 81
	}

	/*
	 * Pick a new current process and record its start time.
	 */
	cnt.v_swtch++;
D 83
	cpu_swtch(p);
E 83
I 83
	cpu_switch(p);
E 83
	microtime(&runtime);
}

/*
E 77
 * Initialize the (doubly-linked) run queues
 * to be empty.
 */
I 87
void
E 87
rqinit()
{
	register int i;

	for (i = 0; i < NQS; i++)
		qs[i].ph_link = qs[i].ph_rlink = (struct proc *)&qs[i];
}
D 23
#endif
E 23

/*
D 67
 * Set the process running;
 * arrange for it to be swapped in if necessary.
E 67
I 67
 * Change process state to be runnable,
 * placing it on the run queue if it is in memory,
 * and awakening the swapper if it isn't in memory.
E 67
 */
I 77
void
E 77
D 82
setrun(p)
E 82
I 82
setrunnable(p)
E 82
D 31
register struct proc *p;
E 31
I 31
	register struct proc *p;
E 31
{
D 10
	register caddr_t w;
E 10
D 31
	register s;
E 31
I 31
	register int s;
E 31

D 47
	s = spl6();
E 47
I 47
	s = splhigh();
E 47
	switch (p->p_stat) {
D 82

E 82
	case 0:
D 82
	case SWAIT:
E 82
	case SRUN:
	case SZOMB:
	default:
D 82
		panic("setrun");

E 82
I 82
		panic("setrunnable");
E 82
I 10
	case SSTOP:
E 10
	case SSLEEP:
D 8
		if (w = p->p_wchan) {
			wakeup(w);
			splx(s);
			return;
		}
E 8
I 8
		unsleep(p);		/* e.g. when sending signals */
E 8
		break;

	case SIDL:
D 10
	case SSTOP:
E 10
		break;
	}
I 47
D 56
	if (p->p_slptime > 1)
		updatepri(p);
E 56
E 47
	p->p_stat = SRUN;
D 83
	if (p->p_flag & SLOAD)
E 83
I 83
	if (p->p_flag & P_INMEM)
E 83
D 82
		setrq(p);
E 82
I 82
		setrunqueue(p);
E 82
	splx(s);
I 56
	if (p->p_slptime > 1)
		updatepri(p);
E 56
D 21
	if(p->p_pri < curpri)
E 21
I 21
D 31
	if(p->p_pri < curpri) {
E 31
I 31
D 67
	if (p->p_pri < curpri) {
E 31
E 21
		runrun++;
I 21
		aston();
	}
E 21
D 29
	if(runout != 0 && (p->p_flag&SLOAD) == 0) {
		runout = 0;
		wakeup((caddr_t)&runout);
E 29
I 29
	if ((p->p_flag&SLOAD) == 0) {
D 31
		if(runout != 0) {
E 31
I 31
		if (runout != 0) {
E 31
			runout = 0;
			wakeup((caddr_t)&runout);
		}
		wantin++;
E 29
	}
E 67
I 67
	p->p_slptime = 0;
D 83
	if ((p->p_flag&SLOAD) == 0)
E 83
I 83
	if ((p->p_flag & P_INMEM) == 0)
E 83
		wakeup((caddr_t)&proc0);
D 81
	else if (p->p_pri < curpri)
E 81
I 81
D 83
	else if (p->p_pri < curpriority)
E 83
I 83
	else if (p->p_priority < curpriority)
E 83
E 81
		need_resched();
E 67
}

/*
D 67
 * Set user priority.
 * The rescheduling flag (runrun)
 * is set if the priority is better
 * than the currently running process.
E 67
I 67
D 81
 * Compute priority of process when running in user mode.
 * Arrange to reschedule if the resulting priority
 * is better than that of the current process.
E 81
I 81
 * Compute the priority of a process when running in user mode.
 * Arrange to reschedule if the resulting priority is better
 * than that of the current process.
E 81
E 67
 */
I 77
void
E 77
D 67
setpri(pp)
D 31
register struct proc *pp;
E 31
I 31
	register struct proc *pp;
E 67
I 67
D 81
setpri(p)
E 81
I 81
resetpriority(p)
E 81
	register struct proc *p;
E 67
E 31
{
D 31
	register p;
E 31
I 31
D 67
	register int p;
E 67
I 67
D 81
	register unsigned int newpri;
E 81
I 81
	register unsigned int newpriority;
E 81
E 67
E 31

D 30
	p = (pp->p_cpu & 0377)/16;
E 30
I 30
D 67
	p = (pp->p_cpu & 0377)/4;
E 30
D 16
	p += PUSER + pp->p_nice - NZERO;
E 16
I 16
D 47
	p += PUSER + 2*(pp->p_nice - NZERO);
E 47
I 47
	p += PUSER + 2 * pp->p_nice;
E 47
I 28
D 66
	if (pp->p_rssize > pp->p_maxrss && freemem < desfree)
		p += 2*4;	/* effectively, nice(4) */
E 66
E 28
E 16
D 31
	if(p > 127)
E 31
I 31
	if (p > 127)
E 31
		p = 127;
D 22
	if(p < curpri)
E 22
I 22
D 31
	if(p < curpri) {
E 31
I 31
	if (p < curpri) {
E 31
E 22
		runrun++;
I 22
		aston();
	}
E 22
	pp->p_usrpri = p;
D 31
	return(p);
E 31
I 31
	return (p);
E 67
I 67
D 81
	newpri = PUSER + p->p_cpu / 4 + 2 * p->p_nice;
	newpri = min(newpri, MAXPRI);
	p->p_usrpri = newpri;
	if (newpri < curpri)
E 81
I 81
D 83
	newpriority = PUSER + p->p_cpu / 4 + 2 * p->p_nice;
E 83
I 83
	newpriority = PUSER + p->p_estcpu / 4 + 2 * p->p_nice;
E 83
	newpriority = min(newpriority, MAXPRI);
	p->p_usrpri = newpriority;
	if (newpriority < curpriority)
E 81
		need_resched();
E 67
E 31
D 36
}

/*
 * Create a new process-- the internal version of
 * sys fork.
 * It returns 1 in the new process, 0 in the old.
 */
newproc(isvfork)
I 31
	int isvfork;
E 31
{
	register struct proc *p;
	register struct proc *rpp, *rip;
	register int n;
I 34
	register struct file *fp;
E 34

	p = NULL;
	/*
	 * First, just locate a slot for a process
	 * and copy the useful info from this process into it.
	 * The panic "cannot happen" because fork has already
	 * checked for the existence of a slot.
	 */
retry:
	mpid++;
D 31
	if(mpid >= 30000) {
E 31
I 31
	if (mpid >= 30000) {
E 31
		mpid = 0;
		goto retry;
	}
D 24
	for(rpp = &proc[0]; rpp < &proc[NPROC]; rpp++) {
E 24
I 24
D 31
	for(rpp = proc; rpp < procNPROC; rpp++) {
E 24
		if(rpp->p_stat == NULL && p==NULL)
E 31
I 31
	for (rpp = proc; rpp < procNPROC; rpp++) {
		if (rpp->p_stat == NULL && p==NULL)
E 31
			p = rpp;
		if (rpp->p_pid==mpid || rpp->p_pgrp==mpid)
			goto retry;
	}
D 31
	if ((rpp = p)==NULL)
E 31
I 31
	if ((rpp = p) == NULL)
E 31
		panic("no procs");

	/*
D 31
	 * make proc entry for new proc
E 31
I 31
	 * Make a proc table entry for the new process.
E 31
	 */
D 31

E 31
	rip = u.u_procp;
I 33
#ifdef QUOTA
	(rpp->p_quota = rip->p_quota)->q_cnt++;
#endif
E 33
	rpp->p_stat = SIDL;
D 35
	rpp->p_clktim = 0;
E 35
I 35
	timerclear(&rpp->p_realtimer.itimer_value);
E 35
D 13
	rpp->p_flag = SLOAD | (rip->p_flag & SPAGI);
E 13
I 13
D 14
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGI|SDETACH));
E 14
I 14
D 32
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGI|SDETACH|SNUSIG));
E 32
I 32
	rpp->p_flag = SLOAD | (rip->p_flag & (SPAGI|SNUSIG));
E 32
E 14
E 13
	if (isvfork) {
		rpp->p_flag |= SVFORK;
		rpp->p_ndx = rip->p_ndx;
	} else
		rpp->p_ndx = rpp - proc;
	rpp->p_uid = rip->p_uid;
	rpp->p_pgrp = rip->p_pgrp;
	rpp->p_nice = rip->p_nice;
	rpp->p_textp = isvfork ? 0 : rip->p_textp;
	rpp->p_pid = mpid;
	rpp->p_ppid = rip->p_pid;
I 8
	rpp->p_pptr = rip;
I 33
	rpp->p_osptr = rip->p_cptr;
	if (rip->p_cptr)
		rip->p_cptr->p_ysptr = rpp;
	rpp->p_ysptr = NULL;
	rpp->p_cptr = NULL;
	rip->p_cptr = rpp;
E 33
E 8
	rpp->p_time = 0;
	rpp->p_cpu = 0;
I 8
	rpp->p_siga0 = rip->p_siga0;
	rpp->p_siga1 = rip->p_siga1;
	/* take along any pending signals, like stops? */
E 8
	if (isvfork) {
		rpp->p_tsize = rpp->p_dsize = rpp->p_ssize = 0;
		rpp->p_szpt = clrnd(ctopt(UPAGES));
		forkstat.cntvfork++;
		forkstat.sizvfork += rip->p_dsize + rip->p_ssize;
	} else {
		rpp->p_tsize = rip->p_tsize;
		rpp->p_dsize = rip->p_dsize;
		rpp->p_ssize = rip->p_ssize;
		rpp->p_szpt = rip->p_szpt;
		forkstat.cntfork++;
		forkstat.sizfork += rip->p_dsize + rip->p_ssize;
	}
	rpp->p_rssize = 0;
I 27
	rpp->p_maxrss = rip->p_maxrss;
E 27
	rpp->p_wchan = 0;
	rpp->p_slptime = 0;
D 15
	rpp->p_aveflt = rip->p_aveflt;
D 12
	rate.v_pgin += rip->p_aveflt;
E 12
	rpp->p_faults = 0;
E 15
I 15
	rpp->p_pctcpu = 0;
	rpp->p_cpticks = 0;
E 15
	n = PIDHASH(rpp->p_pid);
	p->p_idhash = pidhash[n];
	pidhash[n] = rpp - proc;
I 31
	multprog++;
E 31

	/*
D 31
	 * make duplicate entries
	 * where needed
E 31
I 31
	 * Increase reference counts on shared objects.
E 31
	 */
D 31

	multprog++;

E 31
D 34
	for(n=0; n<NOFILE; n++)
D 31
		if(u.u_ofile[n] != NULL) {
E 31
I 31
		if (u.u_ofile[n] != NULL)
E 31
D 20
			u.u_ofile[n]->f_count++;
			if(!isvfork && u.u_vrpages[n])
				u.u_ofile[n]->f_inode->i_vfdcnt++;
E 20
I 20
D 25
#ifdef UCBIPC
			if (u.u_pofile[n] & ISPORT)
				u.u_oport[n]->pt_count++;
			else {
#endif
				u.u_ofile[n]->f_count++;
				if(!isvfork && u.u_vrpages[n])
					u.u_ofile[n]->f_inode->i_vfdcnt++;
#ifdef UCBIPC
			}
#endif UCBIPC
E 25
I 25
			u.u_ofile[n]->f_count++;
E 34
I 34
	for (n = 0; n < NOFILE; n++) {
		fp = u.u_ofile[n];
		if (fp == NULL)
			continue;
		fp->f_count++;
		if (u.u_pofile[n]&RDLOCK)
			fp->f_inode->i_rdlockc++;
		if (u.u_pofile[n]&WRLOCK)
			fp->f_inode->i_wrlockc++;
	}
E 34
D 31
			if(!isvfork && u.u_vrpages[n])
				u.u_ofile[n]->f_inode->i_vfdcnt++;
E 25
E 20
		}

E 31
	u.u_cdir->i_count++;
	if (u.u_rdir)
		u.u_rdir->i_count++;
I 31

E 31
	/*
	 * Partially simulate the environment
	 * of the new process so that when it is actually
	 * created (by copying) it will look right.
I 31
	 * This begins the section where we must prevent the parent
	 * from being swapped.
E 31
	 */
D 31

	rip->p_flag |= SKEEP;	/* prevent parent from being swapped */

E 31
I 31
	rip->p_flag |= SKEEP;
E 31
	if (procdup(rpp, isvfork))
		return (1);

I 31
	/*
	 * Make child runnable and add to run queue.
	 */
E 31
D 18
	spl6();
E 18
I 18
	(void) spl6();
E 18
	rpp->p_stat = SRUN;
	setrq(rpp);
D 19
	spl0();
E 19
I 19
	(void) spl0();
E 19
D 2
	/* THE SSWAP BIT IS REPLACED BY u.u_pcb.pcb_sswap SEE procdup */
E 2
I 2
D 31
	/* SSWAP NOT NEEDED IN THIS CASE AS u.u_pcb.pcb_sswap SUFFICES */
E 31
I 31

	/*
	 * Cause child to take a non-local goto as soon as it runs.
	 * On older systems this was done with SSWAP bit in proc
	 * table; on VAX we use u.u_pcb.pcb_sswap so don't need
	 * to do rpp->p_flag |= SSWAP.  Actually do nothing here.
	 */
E 31
E 2
	/* rpp->p_flag |= SSWAP; */
I 31

	/*
	 * Now can be swapped.
	 */
E 31
	rip->p_flag &= ~SKEEP;
I 31

	/*
	 * If vfork make chain from parent process to child
	 * (where virtal memory is temporarily).  Wait for
	 * child to finish, steal virtual memory back,
	 * and wakeup child to let it die.
	 */
E 31
	if (isvfork) {
		u.u_procp->p_xlink = rpp;
		u.u_procp->p_flag |= SNOVM;
		while (rpp->p_flag & SVFORK)
			sleep((caddr_t)rpp, PZERO - 1);
		if ((rpp->p_flag & SLOAD) == 0)
			panic("newproc vfork");
		uaccess(rpp, Vfmap, &vfutl);
		u.u_procp->p_xlink = 0;
		vpassvm(rpp, u.u_procp, &vfutl, &u, Vfmap);
D 31
		for (n = 0; n < NOFILE; n++)
			if (vfutl.u_vrpages[n]) {
				if ((u.u_vrpages[n] = vfutl.u_vrpages[n] - 1) == 0)
					if (--u.u_ofile[n]->f_inode->i_vfdcnt < 0)
						panic("newproc i_vfdcnt");
				vfutl.u_vrpages[n] = 0;
			}
E 31
		u.u_procp->p_flag &= ~SNOVM;
		rpp->p_ndx = rpp - proc;
		rpp->p_flag |= SVFDONE;
		wakeup((caddr_t)rpp);
	}
I 31

	/*
	 * 0 return means parent.
	 */
E 31
	return (0);
E 36
}
E 1
