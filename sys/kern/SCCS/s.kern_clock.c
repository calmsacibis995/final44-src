h43453
s 00005/00000/00497
d D 8.5 94/01/21 17:17:33 bostic 132 131
c add USL's copyright notice
e
s 00004/00002/00493
d D 8.4 93/12/14 18:21:01 torek 131 130
c in timeout(), be careful not to subtract negative c_time values
e
s 00021/00023/00474
d D 8.3 93/09/23 15:27:32 bostic 130 129
c changes for 4.4BSD-Lite requested by USL
e
s 00060/00040/00437
d D 8.2 93/09/05 09:44:15 bostic 129 128
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00475
d D 8.1 93/06/10 21:56:49 bostic 128 127
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00473
d D 7.31 93/04/20 17:20:53 mckusick 127 126
c kcount is now part of the gmon structure
e
s 00001/00001/00475
d D 7.30 93/03/04 17:58:17 bostic 126 125
c change buffer lengths of sysctl(2) to be size_t's
e
s 00009/00026/00467
d D 7.29 93/02/04 01:11:57 mckusick 125 124
c kinfo_clock becomes sysctl_clock
e
s 00001/00001/00492
d D 7.28 92/11/16 19:35:01 torek 124 123
c spelling
e
s 00009/00009/00484
d D 7.27 92/10/11 10:37:57 bostic 123 122
c make kernel includes standard
e
s 00002/00000/00491
d D 7.26 92/09/23 16:13:46 sklower 122 121
c want cheap elapsed time (put back chnage from 7.19 to 7.20)
e
s 00002/00001/00489
d D 7.25 92/09/21 21:31:07 hibler 121 120
c make psratio visible: needed to scale tick values in hp300/trap.c
e
s 00010/00017/00480
d D 7.24 92/07/16 13:38:49 torek 120 119
c simplify based on new guarantee that tickdelta has proper sign
e
s 00001/00001/00496
d D 7.23 92/07/10 01:22:32 torek 119 118
c typo in GPROF
e
s 00268/00268/00229
d D 7.22 92/07/08 00:59:15 torek 118 117
c major overhaul for new statistics gathering; lint; prototypes
e
s 00043/00000/00454
d D 7.21 92/06/20 12:01:31 mckusick 117 116
c add startprofclock and stopprofclock to track when profiling clock is needed
e
s 00005/00005/00449
d D 7.20 92/06/20 10:26:08 mckusick 116 115
c phz => stathz
e
s 00010/00002/00444
d D 7.19 92/03/18 18:07:37 sklower 115 114
c define ticks, phz, profhz, time, and mono_time
e
s 00011/00006/00435
d D 7.18 92/03/15 13:21:39 mckusick 114 113
c enforce hard CPU limit with SIGKILL (net2/sys/8)
e
s 00036/00000/00405
d D 7.17 92/02/25 17:17:10 mckusick 113 112
c add kinfo_clockrate so profilers can find out system clock rate
c through getkerninfo
e
s 00005/00004/00400
d D 7.16 91/05/09 21:21:25 bostic 112 111
c new copyright; att/bsd/shared
e
s 00000/00023/00404
d D 7.15 91/05/09 18:34:02 mckusick 111 110
c profil moves from kern_clock.c to sys_process.c
e
s 00003/00000/00424
d D 7.14 91/05/07 09:21:34 hibler 110 109
c added (ifdef'ed) call to initprofclock for high precision 
c profile timer
e
s 00011/00005/00413
d D 7.13 91/05/03 12:13:45 karels 109 108
c user.h no longer needed for ast's; noproc => !curproc
e
s 00055/00120/00363
d D 7.12 91/03/17 15:42:23 karels 108 107
c more-or-less working with new proc & user structs
c clean up machdep code with intrframe, etc
e
s 00000/00015/00483
d D 7.11 90/12/05 16:33:11 mckusick 107 106
c update for new VM
e
s 00049/00000/00449
d D 7.10 90/06/30 19:29:22 william 106 105
c i386 support for kernel addition
e
s 00002/00002/00447
d D 7.9 90/06/28 17:09:59 karels 105 104
c RETURN => return, remove syscontext.h
e
s 00009/00005/00440
d D 7.8 90/06/21 22:35:37 mckusick 104 103
c new system call convention
e
s 00003/00000/00442
d D 7.7 90/05/10 17:49:54 mckusick 103 102
c merge in support for hp300 from Utah
e
s 00011/00012/00431
d D 7.6 90/04/02 18:06:22 marc 102 101
c [us]time moves to proc
e
s 00000/00001/00443
d D 7.5 89/05/05 00:06:32 mckusick 101 100
c delete unneeded include of dir.h
e
s 00004/00004/00440
d D 7.4 89/04/25 10:47:20 mckusick 100 99
c ../machine => machine
e
s 00003/00012/00441
d D 7.3 88/08/27 15:44:51 karels 99 98
c rm 4.1 compat
e
s 00005/00005/00448
d D 7.2 86/11/03 11:59:30 karels 98 97
c merge in tahoe support
e
s 00001/00001/00452
d D 7.1 86/06/05 00:01:35 mckusick 97 96
c 4.3BSD release version
e
s 00002/00001/00451
d D 6.17 86/06/02 14:41:25 karels 96 95
c lint
e
s 00007/00007/00445
d D 6.16 86/05/27 15:21:33 karels 95 94
c use faster adjustment for larger corrections
e
s 00016/00023/00436
d D 6.15 86/02/20 14:47:23 karels 94 93
c spl's, cleanups from Sam
e
s 00011/00020/00448
d D 6.14 85/09/04 13:32:08 bloom 93 92
c lint cleanup
e
s 00007/00001/00461
d D 6.13 85/06/08 14:34:46 mckusick 92 91
c Add copyright
e
s 00001/00001/00461
d D 6.12 85/04/05 16:30:29 karels 91 90
c rm redundant test
e
s 00001/00001/00461
d D 6.11 85/03/08 15:51:16 mckusick 90 89
c fix from sun!shannon
e
s 00015/00001/00447
d D 6.10 84/11/14 10:05:01 karels 89 88
c adjtime
e
s 00011/00011/00437
d D 6.9 84/08/29 20:18:49 bloom 88 87
c Change to includes.  no more ../h
e
s 00028/00018/00420
d D 6.8 84/08/22 19:21:28 mckusick 87 86
c inline expand bumptime
e
s 00011/00002/00427
d D 6.7 84/05/22 11:20:27 karels 86 85
c call softclock directly if hardclock comes from low ipl
e
s 00000/00000/00429
d D 6.6 84/03/27 12:06:34 karels 85 84
x 83
c remove adjtime
e
s 00000/00000/00447
d D 6.5 84/03/13 08:33:39 karels 84 83
x 81
c needsoft returns (no longer call d[zh]timer from locore softclock)
e
s 00018/00000/00424
d D 6.4 84/02/23 18:14:56 karels 83 82
c don't ask
e
s 00001/00000/00423
d D 6.3 83/10/08 14:10:36 sam 82 81
c add dk_ndrive so iostat/pstat/vmstat can be binary portable
e
s 00001/00006/00422
d D 6.2 83/10/01 17:42:56 karels 81 80
c always do softclock for now (need to call dz, dh timers)
e
s 00000/00000/00428
d D 6.1 83/07/29 06:32:16 sam 80 79
c 4.2 distribution
e
s 00000/00026/00428
d D 4.57 83/07/01 02:17:43 sam 79 78
c purge #if sun's
e
s 00022/00004/00432
d D 4.56 83/06/14 23:50:01 sam 78 77
c put back in nice+4
e
s 00000/00012/00436
d D 4.55 83/05/30 17:44:46 sam 77 76
c cleanup
e
s 00072/00033/00376
d D 4.54 83/05/27 12:45:57 sam 76 75
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00000/00009/00409
d D 4.53 83/05/21 15:30:23 sam 75 74
c purge mush
e
s 00084/00028/00334
d D 4.52 83/03/03 14:54:56 sam 74 73
c add ability to have separate statistics gathering clock
e
s 00031/00030/00331
d D 4.51 83/01/17 16:15:16 sam 73 72
c fix time accounting (from shannon@sun)
e
s 00005/00001/00356
d D 4.50 83/01/15 16:51:15 mckusick 72 71
c new austere memory version
e
s 00030/00031/00327
d D 4.49 82/12/30 16:28:00 root 71 70
c fix to computation of integral times in kern_clock and alarm(0) in _time
e
s 00015/00009/00343
d D 4.48 82/12/17 11:43:02 sam 70 69
c sun merge
e
s 00002/00001/00350
d D 4.47 82/12/16 12:15:17 sam 69 68
c don't subtract expired callout entries
e
s 00011/00001/00340
d D 4.46 82/12/09 23:46:17 sam 68 67
c profil returns
e
s 00001/00001/00340
d D 4.45 82/11/13 22:49:28 sam 67 66
c merge of 4.1b and 4.1c
e
s 00004/00004/00337
d D 4.44 82/10/31 14:14:11 root 66 65
c change #if to #ifdef
e
s 00022/00001/00319
d D 4.43 82/10/30 20:43:14 root 65 64
c first version with 68k
e
s 00000/00001/00320
d D 4.42 82/10/21 20:56:11 root 64 63
c lint
e
s 00000/00000/00321
d D 4.42 82/10/19 10:30:32  64 63
c more lint
e
s 00000/00000/00321
d D 4.41 82/10/17 21:48:24 root 63 62
c more lint
e
s 00132/00050/00189
d D 4.40 82/09/08 16:44:51 root 62 61
c clean up with comments
e
s 00017/00007/00222
d D 4.39 82/09/08 07:57:14 root 61 60
c timeouts used for all timers now
e
s 00054/00434/00175
d D 4.38 82/09/06 22:38:42 root 60 59
c more work on timer stuff
e
s 00050/00046/00559
d D 4.37 82/09/04 09:06:17 root 59 58
c new timer style; TIMER_VIRTUAL and TIMER_PROF not yet tested
e
s 00002/00000/00603
d D 4.36 82/08/22 20:30:09 root 58 57
c comment out untimeout() for lint's sake
e
s 00056/00000/00547
d D 4.35 82/07/22 13:32:41 kre 57 56
c mush
e
s 00008/00001/00539
d D 4.34 82/07/21 12:03:17 sam 56 55
c watchdog timer for net interfaces
e
s 00009/00006/00531
d D 4.33 82/07/13 22:12:55 root 55 54
c add GPROF stuff
e
s 00007/00005/00530
d D 4.32 82/06/27 15:10:37 sam 54 53
c 2 bug fixes: attribute system time correctly and handle race 
c condition which loses time
e
s 00034/00000/00501
d D 4.31 82/06/26 22:15:28 sam 53 52
c hook for ps driver and untimeout stuff for lucas drivers
e
s 00007/00003/00494
d D 4.30 81/12/19 12:48:17 wnj 52 51
c fix up proto* handling
e
s 00000/00000/00497
d D 4.29 81/12/12 18:07:28 root 51 50
c delete prints
e
s 00024/00000/00473
d D 4.28 81/12/12 17:49:22 root 50 49
c almost works
e
s 00007/00004/00466
d D 4.27 81/11/20 14:42:42 wnj 49 48
c more lint
e
s 00005/00000/00465
d D 4.26 81/10/16 16:30:11 wnj 48 47
c kernel profiling
e
s 00000/00002/00465
d D 4.25 81/08/31 00:33:37 root 47 46
c always use silos
e
s 00003/00001/00464
d D 4.24 81/08/28 14:37:28 wnj 46 45
c fix ipl high too long when doing callouts
e
s 00001/00000/00464
d D 4.23 81/07/09 04:12:47 root 45 44
c lint
e
s 00032/00011/00432
d D 4.22 81/06/11 15:01:16 wnj 44 43
c fix to priority computation (|| with changes to clock.c)
e
s 00001/00002/00442
d D 4.21 81/04/28 02:51:38 root 43 42
c fixes for lint
e
s 00033/00042/00411
d D 4.20 81/04/17 17:52:45 wnj 42 41
c new timeout structure (linked lists)
e
s 00003/00000/00450
d D 4.19 81/04/13 20:33:08 root 41 40
c #if NBK>0 do silo stuff
e
s 00001/00001/00449
d D 4.18 81/04/03 07:53:47 root 40 39
c change timeout overflow panic message
e
s 00006/00000/00444
d D 4.17 81/04/02 15:16:00 root 39 38
c fishing
e
s 00039/00016/00405
d D 4.16 81/03/09 01:46:50 wnj 38 37
c lint and a few minor fixed
e
s 00119/00033/00302
d D 4.15 81/03/02 22:43:59 wnj 37 36
c panicstr prevents calls to timeout returns
e
s 00013/00013/00322
d D 4.14 81/02/27 17:44:36 wnj 36 35
c dynamic allocation kernel
e
s 00001/00001/00334
d D 4.13 81/02/26 23:55:59 wnj 35 34
c rid of NCALL
e
s 00001/00001/00334
d D 4.12 81/02/26 23:39:52 wnj 34 33
c rid of NPROC
e
s 00003/00002/00332
d D 4.11 81/02/25 23:30:28 wnj 33 32
c get rid of VAX==???
e
s 00002/00002/00332
d D 4.10 81/02/23 23:45:03 wnj 32 31
c s/NDH11/NDH/ etc
e
s 00002/00001/00332
d D 4.9 81/02/21 21:24:56 wnj 31 30
c lint
e
s 00014/00016/00319
d D 4.8 81/02/16 20:45:20 wnj 30 29
c resched on runin... cleanout KPROF
e
s 00105/00108/00230
d D 4.7 81/02/15 19:38:40 wnj 29 28
c new interrupt scheme
e
s 00008/00017/00330
d D 4.6 81/02/15 12:16:53 wnj 28 27
c correct panic in timeout()
e
s 00000/00002/00347
d D 4.5 81/01/20 19:52:03 toy 27 26
c Made nicing piggy processes default.  (MCT)
e
s 00003/00000/00346
d D 4.4 81/01/20 19:51:08 wnj 26 25
c Added conditional call to chaos clock.
e
s 00002/00002/00344
d D 4.3 80/12/19 12:06:35 wnj 25 24
c fixup ../conf/ ../sys/ for new compilation strategy
e
s 00007/00001/00339
d D 4.2 80/12/16 15:57:21 wnj 24 23
c comet changes
e
s 00000/00000/00340
d D 4.1 80/11/09 17:31:12 bill 23 22
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00007/00000/00333
d D 3.22 80/10/19 22:12:55 bill 22 21
c conditional on NDH11 NDZ11
e
s 00006/00003/00327
d D 3.21 80/10/13 09:58:00 bill 21 20
c change %cpu constant; new disk monitoring/cpu scheme
e
s 00010/00005/00320
d D 3.20 80/10/11 21:31:50 bill 20 19
c %cpu
e
s 00001/00001/00324
d D 3.19 80/09/29 09:35:31 bill 19 18
c fix tty driver bug, fix clock not proc stoppeds bug
e
s 00013/00001/00312
d D 3.18 80/09/16 17:06:37 bill 18 17
c decrement hangcnt at lbolt
e
s 00005/00002/00308
d D 3.17 80/07/16 13:43:38 bill 17 16
c limit code
e
s 00001/00001/00309
d D 3.16 80/07/13 00:37:52 bill 16 15
c forgot to divide time by HZ in computing LIM_CPU
e
s 00001/00000/00309
d D 3.15 80/07/12 19:54:58 bill 15 14
c limit.h included
e
s 00004/00002/00305
d D 3.14 80/07/12 18:14:25 bill 14 13
c limit code
e
s 00001/00000/00306
d D 3.13 80/06/28 10:46:00 bill 13 12
c dk.h
e
s 00008/00007/00298
d D 3.12 80/06/24 19:28:11 bill 12 11
c no swplo
e
s 00002/00000/00303
d D 3.11 80/06/22 12:22:40 bill 11 10
c call unhang()
e
s 00001/00001/00302
d D 3.10 80/06/07 02:44:40 bill 10 9
c %H%->%G%
e
s 00009/00001/00294
d D 3.9 80/05/24 19:43:21 bill 9 8
c new signal stuff
e
s 00001/00001/00294
d D 3.8 80/05/15 16:52:27 bill 8 7
c new signal names
e
s 00001/00001/00294
d D 3.7 80/05/09 20:53:54 bill 7 6
c move input interrupt timeouts to always happen, and every tick
e
s 00018/00006/00277
d D 3.6 80/05/09 13:50:14 bill 6 5
c call silo code even when !BASEPRI()... DANGER spl5=>spl6
e
s 00004/00004/00279
d D 3.5 80/05/08 10:20:55 bill 5 4
c VOID=>void
e
s 00013/00000/00270
d D 3.4 80/05/08 10:02:17 bill 4 3
c call dhtimer and dztimer without using timeouts for very fast
e
s 00004/00003/00266
d D 3.3 80/04/17 10:23:34 bill 3 2
c clean up kernel profiling
e
s 00008/00001/00261
d D 3.2 80/04/14 19:20:16 bill 2 1
c changes for tsleep()
e
s 00262/00000/00000
d D 3.1 80/04/09 16:02:59 bill 1 0
c date and time created 80/04/09 16:02:59 by bill
e
u
U
t
T
I 1
D 10
/*	%M%	%I%	%H%	*/
E 10
I 10
D 12
/*	%M%	%I%	%G%	*/
E 12
I 12
D 24
/*	%H%	%I%	%M%	*/
E 24
I 24
D 38
/*	%M%	%I%	%G%	*/
E 38
I 38
D 92
/*	%M%	%I%	%E%	*/
E 92
I 92
D 112
/*
D 97
 * Copyright (c) 1982 Regents of the University of California.
E 97
I 97
D 108
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 108
I 108
 * Copyright (c) 1982, 1986, 1991 Regents of the University of California.
E 108
E 97
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 112
I 112
/*-
D 128
 * Copyright (c) 1982, 1986, 1991 The Regents of the University of California.
 * All rights reserved.
E 128
I 128
 * Copyright (c) 1982, 1986, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 132
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 132
E 128
 *
 * %sccs.include.redist.c%
E 112
 *
 *	%W% (Berkeley) %G%
 */
E 92
E 38
E 24
E 12
E 10

I 70
D 99
#include "../machine/reg.h"
#include "../machine/psl.h"

E 99
E 70
D 88
#include "../h/param.h"
#include "../h/systm.h"
I 13
#include "../h/dk.h"
E 13
D 36
#include "../h/callo.h"
E 36
I 36
#include "../h/callout.h"
E 36
D 60
#include "../h/seg.h"
E 60
#include "../h/dir.h"
#include "../h/user.h"
I 59
#include "../h/kernel.h"
E 59
#include "../h/proc.h"
D 60
#include "../h/reg.h"
E 60
D 70
#include "../h/psl.h"
E 70
#include "../h/vm.h"
D 60
#include "../h/buf.h"
E 60
#include "../h/text.h"
E 88
I 88
D 123
#include "param.h"
#include "systm.h"
D 98
#include "dk.h"
E 98
I 98
#include "dkstat.h"
E 98
#include "callout.h"
D 101
#include "dir.h"
E 101
D 104
#include "user.h"
E 104
I 104
D 105
#include "syscontext.h"
E 105
I 105
D 109
#include "user.h"
E 109
E 105
E 104
#include "kernel.h"
#include "proc.h"
I 109
#include "resourcevar.h"
E 123
I 123
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dkstat.h>
#include <sys/callout.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
E 123
E 109
D 107
#include "vm.h"
#include "text.h"
E 107
E 88
I 68
D 70
#ifdef vax
#include "../vax/mtpr.h"
#endif
E 70
E 68
I 15
D 18
#include "../h/limit.h"
E 18
I 18
D 59
#include "../h/vlimit.h"
E 59
D 60
#include "../h/mtpr.h"
D 59
#include "../h/clock.h"
E 59
I 33
#include "../h/cpu.h"
I 50
#include "../h/protosw.h"
I 56
#include "../h/socket.h"
#include "../net/if.h"
E 60
I 57
D 75
#ifdef MUSH
#include "../h/quota.h"
#include "../h/share.h"
#endif
E 75
E 57
E 56
E 50
E 33
E 18
E 15

I 99
D 100
#include "../machine/reg.h"
#include "../machine/psl.h"
E 100
I 100
D 108
#include "machine/reg.h"
#include "machine/psl.h"
E 108
I 108
D 123
#include "machine/cpu.h"
E 123
I 123
#include <machine/cpu.h>
E 123
E 108
E 100

E 99
I 70
D 94
#ifdef vax
E 94
I 94
D 98
#if defined(vax)
E 94
#include "../vax/mtpr.h"
I 94
#include "../vax/clock.h"
E 98
I 98
D 108
#if defined(vax) || defined(tahoe)
D 100
#include "../machine/mtpr.h"
#include "../machine/clock.h"
E 100
I 100
#include "machine/mtpr.h"
#include "machine/clock.h"
E 100
E 98
E 94
#endif
I 103
#if defined(hp300)
#include "machine/mtpr.h"
#endif
I 106
#ifdef i386
#include "machine/frame.h"
#include "machine/segments.h"
#endif
E 106
E 103

E 108
I 72
#ifdef GPROF
D 88
#include "../h/gprof.h"
E 88
I 88
D 118
#include "gprof.h"
E 118
I 118
D 123
#include "gmon.h"
E 123
I 123
#include <sys/gmon.h>
E 123
D 127
extern u_short *kcount;
E 127
E 118
E 88
#endif

I 83
#define ADJTIME		/* For now... */
#define	ADJ_TICK 1000
int	adjtimedelta;

E 83
E 72
D 74
#
E 74
I 74
D 77
#ifdef KGCLOCK
extern int phz;
#endif

E 77
E 74
E 70
I 41
D 60
#include "bk.h"
E 60
E 41
I 22
D 25
#include "../conf/dh.h"
#include "../conf/dz.h"
E 25
I 25
D 62
#include "dh.h"
#include "dz.h"
I 53
#include "ps.h"
E 62
I 62
/*
 * Clock handling routines.
 *
D 74
 * This code is written for a machine with only one interval timer,
 * and does timing and resource utilization estimation statistically
 * based on the state of the machine hz times a second.  A machine
 * with proper clocks (running separately in user state, system state,
 * interrupt state and idle state) as well as a time-of-day clock
 * would allow a non-approximate implementation.
E 74
I 74
D 118
 * This code is written to operate with two timers which run
 * independently of each other. The main clock, running at hz
 * times per second, is used to do scheduling and timeout calculations.
 * The second timer does resource utilization estimation statistically
D 116
 * based on the state of the machine phz times a second. Both functions
 * can be performed by a single clock (ie hz == phz), however the 
E 116
I 116
 * based on the state of the machine stathz times a second. Both functions
 * can be performed by a single clock (ie hz == stathz), however the 
E 116
 * statistics will be much more prone to errors. Ideally a machine
 * would have separate clocks measuring time spent in user state, system
 * state, interrupt state, and idle state. These clocks would allow a non-
 * approximate measure of resource utilization.
E 118
I 118
 * This code is written to operate with two timers that run independently of
 * each other.  The main clock, running hz times per second, is used to keep
 * track of real time.  The second timer handles kernel and user profiling,
 * and does resource use estimation.  If the second timer is programmable,
 * it is randomized to avoid aliasing between the two clocks.  For example,
 * the randomization prevents an adversary from always giving up the cpu
 * just before its quantum expires.  Otherwise, it would never accumulate
 * cpu ticks.  The mean frequency of the second timer is stathz.
 *
 * If no second timer exists, stathz will be zero; in this case we drive
 * profiling and statistics off the main clock.  This WILL NOT be accurate;
 * do not do it unless absolutely necessary.
 *
 * The statistics clock may (or may not) be run at a higher rate while
 * profiling.  This profile clock runs at profhz.  We require that profhz
 * be an integral multiple of stathz.
 *
 * If the statistics clock is running fast, it must be divided by the ratio
 * profhz/stathz for statistics.  (For profiling, every tick counts.)
E 118
E 74
 */
E 62
E 53
E 25

E 22
D 38
#define	SCHMAG	9/10

I 20
D 29
/*
 * Constant for decay filter for cpu usage.
 */
D 21
double	ccpu = 0.93550698503161773774;		/* exp(-1/15) */
E 21
I 21
double	ccpu = 0.95122942450071400909;		/* exp(-1/20) */
E 29
E 21
E 20

E 38
D 60
/*
D 20
 * clock is called straight from
E 20
I 20
D 29
 * Clock is called straight from
E 29
I 29
 * Hardclock is called straight from
E 29
E 20
 * the real time clock interrupt.
I 29
 * We limit the work we do at real clock interrupt time to:
 *	reloading clock
 *	decrementing time to callouts
 *	recording cpu time usage
D 30
 *	modifying priority of current processing
E 30
I 30
 *	modifying priority of current process
E 30
 *	arrange for soft clock interrupt
 *	kernel pc profiling
E 29
 *
D 29
 * Functions:
E 29
I 29
D 38
 * At softclock interrupt time we:
E 38
I 38
 * At software (softclock) interrupt time we:
E 38
E 29
 *	implement callouts
D 29
 *	maintain user/system times
E 29
 *	maintain date
D 29
 *	profile
E 29
 *	lightning bolt wakeup (every second)
 *	alarm clock signals
 *	jab the scheduler
I 29
 *
 * On the vax softclock interrupts are implemented by
 * software interrupts.  Note that we may have multiple softclock
 * interrupts compressed into one (due to excessive interrupt load),
 * but that hardclock interrupts should never be lost.
E 29
 */
E 60
I 49
D 55
#ifdef KPROF
E 49
I 48
int	kcounts[20000];
E 55
I 55
D 62
#ifdef GPROF
extern	int profiling;
extern	char *s_lowpc;
extern	u_long s_textsize;
extern	u_short *kcount;
E 55
D 49
int	kprof = 1;
E 49
I 49
#endif
E 62
I 62
/*
 * TODO:
D 76
 *	* Keep more accurate statistics by simulating good interval timers.
 *	* Use the time-of-day clock on the VAX to keep more accurate time
 *	  than is possible by repeated use of the interval timer.
 *	* Allocate more timeout table slots when table overflows.
I 74
 *	* Get all resource allocation to use second timer.
E 76
I 76
D 118
 *	time of day, system/user timing, timeouts, profiling on separate timers
E 118
 *	allocate more timeout table slots when table overflows.
E 76
E 74
 */
I 87
D 94
#ifdef notdef
E 94
I 94

E 94
/*
 * Bump a timeval by a small number of usec's.
 */
D 94
bumptime(tp, usec)
	register struct timeval *tp;
	int usec;
{
E 87
E 62
E 49
E 48
D 30
#ifdef KPROF
D 3
short	kcount[20000];
E 3
I 3
unsigned short kcount[20000];
E 3
#endif
E 30

I 87
	tp->tv_usec += usec;
	if (tp->tv_usec >= 1000000) {
		tp->tv_usec -= 1000000;
		tp->tv_sec++;
	}
}
#endif notdef
E 94
#define BUMPTIME(t, usec) { \
D 118
	register struct timeval *tp = (t); \
E 118
I 118
	register volatile struct timeval *tp = (t); \
	register long us; \
E 118
 \
D 118
	tp->tv_usec += (usec); \
	if (tp->tv_usec >= 1000000) { \
		tp->tv_usec -= 1000000; \
E 118
I 118
	tp->tv_usec = us = tp->tv_usec + (usec); \
	if (us >= 1000000) { \
		tp->tv_usec = us - 1000000; \
E 118
		tp->tv_sec++; \
	} \
}

I 115
D 118
int	ticks;
E 118
D 116
int	phz;
E 116
I 116
int	stathz;
E 116
int	profhz;
I 117
int	profprocs;
I 122
int	ticks;
E 122
E 117
D 118
struct	timeval time;
struct	timeval mono_time;
E 118
I 118
D 121
static int psratio, psdiv, pscnt;	/* prof => stat divider */
E 121
I 121
static int psdiv, pscnt;	/* prof => stat divider */
D 124
int	psratio;		/* ratio: prot / stat */
E 124
I 124
int	psratio;		/* ratio: prof / stat */
E 124
E 121

volatile struct	timeval time;
volatile struct	timeval mono_time;

E 118
E 115
E 87
I 50
D 60
/*
 * Protoslow is like lbolt, but for slow protocol timeouts, counting
 * up to (hz/PR_SLOWHZ), then causing a pfslowtimo().
 * Protofast is like lbolt, but for fast protocol timeouts, counting
 * up to (hz/PR_FASTHZ), then causing a pffasttimo().
 */
int	protoslow;
int	protofast;
I 56
int	ifnetslow;
E 60
I 60
D 62
#define	bumptime(tp)	\
	(tp)->tv_usec += tick; \
E 62
I 62
D 76
/* bump a timeval by a small number of usec's */
#define	bumptime(tp, usec) \
	(tp)->tv_usec += usec; \
E 62
	if ((tp)->tv_usec >= 1000000) { \
		(tp)->tv_usec -= 1000000; \
		(tp)->tv_sec++; \
	}
E 60
E 56

E 76
I 62
/*
D 74
 * The (single) hardware interval timer.
 * We update the events relating to real time, and then
 * make a gross assumption: that the system has been in the
 * state it is in (user state, kernel state, interrupt state,
 * or idle state) for the entire last time interval, and
 * update statistics accordingly.
E 74
I 74
D 118
 * The hz hardware interval timer.
 * We update the events relating to real time.
 * If this timer is also being used to gather statistics,
 * we run through the statistics gathering routine as well.
E 118
I 118
 * Initialize clock frequencies and start both clocks running.
E 118
E 74
 */
I 118
void
initclocks()
{
	register int i;

	/*
	 * Set divisors to 1 (normal case) and let the machine-specific
	 * code do its bit.
	 */
	psdiv = pscnt = 1;
	cpu_initclocks();

	/*
	 * Compute profhz/stathz, and fix profhz if needed.
	 */
	i = stathz ? stathz : hz;
	if (profhz == 0)
		profhz = i;
	psratio = profhz / i;
}

/*
 * The real-time timer, interrupting hz times per second.
 */
void
E 118
E 62
E 50
I 31
D 108
/*ARGSUSED*/
I 106
#ifndef i386
E 106
I 65
D 66
#if vax
E 66
I 66
D 79
#ifdef vax
E 79
E 66
E 65
E 31
I 4
D 29
/*
 * We handle regular calls to the dh and dz silo input processors
 * without using timeouts to save a little time.
 */
D 7
int	rintvl = 4;		/* every 1/15'th of sec check receivers */
E 7
I 7
int	rintvl = 0;		/* every 1/60'th of sec check receivers */
E 7
int	rcnt;

E 4
clock(pc, ps)
caddr_t pc;
E 29
I 29
hardclock(pc, ps)
I 30
	caddr_t pc;
I 65
	int ps;
I 106
#else
E 108
hardclock(frame)
D 108
	struct intrframe frame;
#define	pc	frame.if_eip
#endif
E 108
I 108
D 118
	clockframe frame;
E 118
I 118
	register struct clockframe *frame;
E 118
E 108
E 106
E 65
E 30
E 29
{
I 65
D 79
#endif
D 66
#if sun
E 66
I 66
#ifdef sun
E 66
hardclock(regs)
	struct regs regs;
{
D 76
	int ps = regs.r_sr;
	caddr_t pc = (caddr_t)regs.r_pc;
E 76
I 76
#define	ps	regs.r_sr
#define	pc	(caddr_t)regs.r_pc
E 76
#endif
E 79
E 65
D 29
	register struct callo *p1, *p2;
E 29
I 29
D 36
	register struct callo *p1;
E 36
I 36
	register struct callout *p1;
E 36
E 29
D 60
	register struct proc *pp;
E 60
I 60
D 102
	register struct proc *p;
E 102
I 102
D 108
	register struct proc *p = u.u_procp;
E 108
I 108
D 118
	register struct proc *p = curproc;
D 109
	register struct pstats *pstats = p->p_stats;
E 109
I 109
	register struct pstats *pstats;
E 109
E 108
E 102
E 60
D 29
	register int s;
D 12
	int a;
E 12
I 12
D 21
	int a, cpstate;
E 21
I 21
	int a, cpstate, i;
E 29
I 29
D 31
	register long *ip;
E 31
D 93
	register int s, cpstate;
E 93
I 93
	register int s;
E 93
I 76
D 81
	int needsoft = 0;
I 114
	time_t secs;
E 118
I 118
	register struct proc *p;
D 120
	register int needsoft;
E 120
I 120
	register int delta, needsoft;
E 120
E 118
E 114
I 89
D 95
	extern int adjtimedelta, tickadj;
E 95
I 95
D 96
	extern int timedelta, tickdelta;
E 96
I 96
	extern int tickdelta;
	extern long timedelta;
E 96
E 95
E 89
E 81
E 76
I 57
D 64
	extern double avenrun[];
E 64
E 57
E 29
E 21
E 12

I 70
D 76
#ifdef sun
	if (USERMODE(ps))		/* aston needs ar0 */
		u.u_ar0 = &regs.r_r0;
#endif
E 76
E 70
D 60
	/*
	 * reprime clock
	 */
D 59
	clkreld();
E 59

E 60
I 53
D 62
#if NPS > 0
E 53
D 60
	/*
I 53
	 * sync referesh of picture system
	 */
E 60
	psextsync(pc, ps);
#endif

D 60
	/*
E 53
D 29
	 * callouts
	 * else update first non-zero time
E 29
I 29
	 * update callout times
E 29
	 */
E 60
I 60
/* update callout times */
E 62
I 62
	/*
	 * Update real-time timeout queue.
	 * At front of queue are some number of events which are ``due''.
	 * The time to these is <= 0 and if negative represents the
	 * number of ticks which have passed since it was supposed to happen.
	 * The rest of the q elements (times > 0) are events yet to happen,
	 * where the time for each is given as a delta from the previous.
	 * Decrementing just the first of these serves to decrement the time
	 * to all events.
	 */
E 62
E 60
D 29

E 29
D 38
	if(callout[0].c_func == NULL)
E 38
I 38
D 42
	if (callout[0].c_func == NULL)
E 38
		goto out;
D 29
	p2 = &callout[0];
	while(p2->c_time<=0 && p2->c_func!=NULL)
		p2++;
	p2->c_time--;

	/*
	 * if ps is high, just return
	 */
	if (BASEPRI(ps))
		goto out;

	/*
	 * callout
	 */

	if(callout[0].c_time <= 0) {
		p1 = &callout[0];
		while(p1->c_func != 0 && p1->c_time <= 0) {
			(*p1->c_func)(p1->c_arg);
			p1++;
		}
		p2 = &callout[0];
		while(p2->c_func = p1->c_func) {
			p2->c_time = p1->c_time;
			p2->c_arg = p1->c_arg;
			p1++;
			p2++;
		}
	}
I 4
D 6
	if (rcnt >= rintvl) {
		dhtimer();
		dztimer();
		rcnt = -1;
	}
E 6
E 4

	/*
	 * lightning bolt time-out
	 * and time of day
	 */
E 29
I 29
	p1 = &callout[0];
D 38
	while(p1->c_time<=0 && p1->c_func!=NULL)
E 38
I 38
	while (p1->c_time<=0 && p1->c_func!=NULL)
E 38
		p1++;
	p1->c_time--;
E 42
I 42
D 76
	for (p1 = calltodo.c_next; p1 && p1->c_time <= 0; p1 = p1->c_next)
D 61
		;
E 61
I 61
		--p1->c_time;
E 61
	if (p1)
D 61
		p1->c_time--;
E 61
I 61
		--p1->c_time;
E 76
I 76
D 118
	p1 = calltodo.c_next;
	while (p1) {
E 118
I 118
	needsoft = 0;
	for (p1 = calltodo.c_next; p1 != NULL; p1 = p1->c_next) {
E 118
		if (--p1->c_time > 0)
			break;
D 81
		needsoft = 1;
E 81
		if (p1->c_time == 0)
			break;
D 118
		p1 = p1->c_next;
E 118
	}
E 76
E 61
E 42
E 29
D 43
out:
E 43
I 4
D 6
	++rcnt;
E 6
I 6

D 60
	/*
D 29
	 * In order to not take input character interrupts to use
	 * the input silo on DZ's we have to guarantee to echo
	 * characters regularly.  This means that we have to
	 * call the timer routines predictably.  Since blocking
	 * in these routines is at spl5(), we have to make spl5()
	 * really spl6() blocking off the clock to put this code
	 * here.  Note also that it is critical that we run spl5()
	 * (i.e. really spl6()) in the receiver interrupt routines
	 * so we can't enter them recursively and transpose characters.
E 29
I 29
	 * Maintain iostat and per-process cpu statistics
E 29
	 */
E 60
I 60
D 62
/* charge process for resource usage... statistically! */
E 62
I 62
D 118
	/*
I 109
	 * Curproc (now in p) is null if no process is running.
	 * We assume that curproc is set in user mode!
	 */
	if (p)
		pstats = p->p_stats;
	/*
E 109
D 71
	 * If the cpu is currently scheduled to a process, then
	 * charge it with resource utilization for a tick, updating
	 * statistics which run in (user+system) virtual time,
	 * such as the cpu time limit and profiling timers.
	 * This assumes that the current process has been running
	 * the entire last tick.
	 */
E 62
E 60
D 29
	if (rcnt >= rintvl) {
I 22
#if NDH11 > 0
E 22
		dhtimer();
I 22
#endif
#if NDZ11 > 0
E 22
		dztimer();
I 22
#endif
E 22
		rcnt = 0;
	} else
		rcnt++;
I 26
#ifdef CHAOS
	ch_clock();
#endif
E 29
E 26
E 6
E 4
	if (!noproc) {
		s = u.u_procp->p_rssize;
D 59
		u.u_vm.vm_idsrss += s;
E 59
I 59
D 60
		u.u_ru.ru_idrss += s;
		u.u_ru.ru_isrss += 0;		/* XXX */
E 60
I 60
		u.u_ru.ru_idrss += s; u.u_ru.ru_isrss += 0;	/* XXX */
E 60
E 59
		if (u.u_procp->p_textp) {
			register int xrss = u.u_procp->p_textp->x_rssize;

			s += xrss;
D 59
			u.u_vm.vm_ixrss += xrss;
E 59
I 59
			u.u_ru.ru_ixrss += xrss;
E 59
		}
D 59
		if (s > u.u_vm.vm_maxrss)
			u.u_vm.vm_maxrss = s;
I 17
D 36
		if ((u.u_vm.vm_utime+u.u_vm.vm_stime+1)/HZ > u.u_limit[LIM_CPU]) {
E 36
I 36
		if ((u.u_vm.vm_utime+u.u_vm.vm_stime+1)/hz > u.u_limit[LIM_CPU]) {
E 59
I 59
		if (s > u.u_ru.ru_maxrss)
			u.u_ru.ru_maxrss = s;
		if ((u.u_ru.ru_utime.tv_sec+u.u_ru.ru_stime.tv_sec+1) >
		    u.u_rlimit[RLIMIT_CPU].rlim_cur) {
E 59
E 36
			psignal(u.u_procp, SIGXCPU);
D 59
			if (u.u_limit[LIM_CPU] < INFINITY - 5)
				u.u_limit[LIM_CPU] += 5;
E 59
I 59
			if (u.u_rlimit[RLIMIT_CPU].rlim_cur <
			    u.u_rlimit[RLIMIT_CPU].rlim_max)
				u.u_rlimit[RLIMIT_CPU].rlim_cur += 5;
E 59
		}
I 60
		if (timerisset(&u.u_timer[ITIMER_PROF].it_value) &&
		    itimerdecr(&u.u_timer[ITIMER_PROF], tick) == 0)
			psignal(u.u_procp, SIGPROF);
E 60
E 17
	}
I 38
D 60
	/*
	 * Update iostat information.
	 */
E 60
I 60

D 62
/* charge for cpu */
E 62
I 62
	/*
E 71
	 * Charge the time out based on the mode the cpu is in.
	 * Here again we fudge for the lack of proper interval timers
	 * assuming that the current state has been around at least
	 * one tick.
	 */
I 106
D 108
#ifdef i386
	if (ISPL(frame.if_cs) == SEL_UPL) {
#else
E 106
E 62
E 60
E 38
D 12
	a = dk_busy&07;
E 12
	if (USERMODE(ps)) {
I 106
#endif
E 106
I 76
D 79
#ifdef sun
		u.u_ar0 = &regs.r_r0;	/* aston needs ar0 */
#endif
E 79
D 81
		if (u.u_prof.pr_scale)
E 108
I 108
	if (CLKF_USERMODE(&frame)) {
		if (pstats->p_prof.pr_scale)
E 108
			needsoft = 1;
E 118
I 118
	p = curproc;
	if (p) {
		register struct pstats *pstats;

E 118
E 81
E 76
D 59
		u.u_vm.vm_utime++;
		if(u.u_procp->p_nice > NZERO)
E 59
I 59
D 60
		u.u_ru.ru_utime.tv_usec += 1000000/hz;
		if (u.u_ru.ru_utime.tv_usec > 1000000) {
			u.u_ru.ru_utime.tv_sec++;
			u.u_ru.ru_utime.tv_usec -= 1000000;
		}
E 60
I 60
D 62
		bumptime(&u.u_ru.ru_utime);
E 62
I 62
		/*
D 118
		 * CPU was in user state.  Increment
		 * user time counter, and process process-virtual time
D 68
		 * interval timer.
E 68
I 68
		 * interval timer. 
E 118
I 118
		 * Run current process's virtual and profile time, as needed.
E 118
E 68
		 */
D 87
		bumptime(&u.u_ru.ru_utime, tick);
E 87
I 87
D 102
		BUMPTIME(&u.u_ru.ru_utime, tick);
E 102
I 102
D 118
		BUMPTIME(&p->p_utime, tick);
E 102
E 87
E 62
D 108
		if (timerisset(&u.u_timer[ITIMER_VIRTUAL].it_value) &&
		    itimerdecr(&u.u_timer[ITIMER_VIRTUAL], tick) == 0)
E 108
I 108
		if (timerisset(&pstats->p_timer[ITIMER_VIRTUAL].it_value) &&
E 118
I 118
		pstats = p->p_stats;
		if (CLKF_USERMODE(frame) &&
		    timerisset(&pstats->p_timer[ITIMER_VIRTUAL].it_value) &&
E 118
		    itimerdecr(&pstats->p_timer[ITIMER_VIRTUAL], tick) == 0)
E 108
D 102
			psignal(u.u_procp, SIGVTALRM);
E 102
I 102
			psignal(p, SIGVTALRM);
E 102
E 60
D 93
		if (u.u_procp->p_nice > NZERO)
E 59
D 12
			a += 8;
E 12
I 12
			cpstate = CP_NICE;
		else
			cpstate = CP_USER;
E 93
I 71
D 73
		/*
		 * Charge it with resource utilization for a tick, updating
		 * statistics which run in (user+system) virtual time,
		 * such as the cpu time limit and profiling timers.
		 * This assumes that the current process has been running
		 * the entire last tick.
		 */
		if (!noproc) {
			s = u.u_procp->p_rssize;
			u.u_ru.ru_idrss += s; u.u_ru.ru_isrss += 0;	/* XXX */
			if (u.u_procp->p_textp) {
				register int xrss = u.u_procp->p_textp->x_rssize;

				s += xrss;
				u.u_ru.ru_ixrss += xrss;
			}
			if (s > u.u_ru.ru_maxrss)
				u.u_ru.ru_maxrss = s;
			if ((u.u_ru.ru_utime.tv_sec+u.u_ru.ru_stime.tv_sec+1) >
			    u.u_rlimit[RLIMIT_CPU].rlim_cur) {
				psignal(u.u_procp, SIGXCPU);
				if (u.u_rlimit[RLIMIT_CPU].rlim_cur <
				    u.u_rlimit[RLIMIT_CPU].rlim_max)
					u.u_rlimit[RLIMIT_CPU].rlim_cur += 5;
			}
			if (timerisset(&u.u_timer[ITIMER_PROF].it_value) &&
			    itimerdecr(&u.u_timer[ITIMER_PROF], tick) == 0)
				psignal(u.u_procp, SIGPROF);
		}

E 73
E 71
E 12
D 118
	} else {
I 62
		/*
D 93
		 * CPU was in system state.  If profiling kernel
		 * increment a counter.  If no process is running
		 * then this is a system tick if we were running
		 * at a non-zero IPL (in a driver).  If a process is running,
		 * then we charge it with system time even if we were
		 * at a non-zero IPL, since the system often runs
		 * this way during processing of system calls.
		 * This is approximate, but the lack of true interval
		 * timers makes doing anything else difficult.
E 93
I 93
		 * CPU was in system state.
E 93
		 */
E 62
I 48
D 49
int k = ((int)pc & 0x7fffffff) / 8;
if (k < 20000)
	kcounts[k]++;
E 49
I 49
D 55
#ifdef KPROF
	int k = ((int)pc & 0x7fffffff) / 8;
	if (k < 20000)
		kcounts[k]++;
E 55
I 55
D 74
#ifdef GPROF
		int k = pc - s_lowpc;
		if (profiling < 2 && k < s_textsize)
D 72
			kcount[k / sizeof (*kcount)]++;
E 72
I 72
			kcount[k / (HISTFRACTION * sizeof (*kcount))]++;
E 72
E 55
#endif
E 74
E 49
E 48
D 12
		a += 16;
E 12
I 12
D 93
		cpstate = CP_SYS;
E 12
D 54
		if (noproc)
D 12
			a += 8;
E 12
I 12
			cpstate = CP_IDLE;
E 12
		else
E 54
I 54
		if (noproc) {
D 65
			if ((ps&PSL_IPL) != 0)
E 65
I 65
			if (BASEPRI(ps))
E 65
				cpstate = CP_IDLE;
D 59
		} else
E 54
			u.u_vm.vm_stime++;
E 59
I 59
		} else {
E 93
I 93
D 94
		if (! noproc) {
E 94
I 94
D 109
		if (!noproc)
E 109
I 109
		if (p)
E 109
E 94
E 93
D 60
			u.u_ru.ru_stime.tv_usec += 1000000/hz;
			if (u.u_ru.ru_stime.tv_usec > 1000000) {
				u.u_ru.ru_stime.tv_sec++;
				u.u_ru.ru_stime.tv_usec -= 1000000;
			}
E 60
I 60
D 62
			bumptime(&u.u_ru.ru_stime);
E 62
I 62
D 87
			bumptime(&u.u_ru.ru_stime, tick);
E 87
I 87
D 102
			BUMPTIME(&u.u_ru.ru_stime, tick);
E 102
I 102
			BUMPTIME(&p->p_stime, tick);
E 102
E 87
E 62
E 60
D 94
		}
E 94
I 73
	}

	/*
	 * If the cpu is currently scheduled to a process, then
	 * charge it with resource utilization for a tick, updating
	 * statistics which run in (user+system) virtual time,
	 * such as the cpu time limit and profiling timers.
	 * This assumes that the current process has been running
	 * the entire last tick.
	 */
D 91
	if (noproc == 0 && cpstate != CP_IDLE) {
E 91
I 91
D 109
	if (noproc == 0) {
E 109
I 109
	if (p) {
E 109
E 91
D 102
		if ((u.u_ru.ru_utime.tv_sec+u.u_ru.ru_stime.tv_sec+1) >
E 102
I 102
D 114
		if ((p->p_utime.tv_sec+p->p_stime.tv_sec+1) >
E 102
D 108
		    u.u_rlimit[RLIMIT_CPU].rlim_cur) {
E 108
I 108
		    p->p_rlimit[RLIMIT_CPU].rlim_cur) {
E 108
D 102
			psignal(u.u_procp, SIGXCPU);
E 102
I 102
			psignal(p, SIGXCPU);
E 102
D 108
			if (u.u_rlimit[RLIMIT_CPU].rlim_cur <
			    u.u_rlimit[RLIMIT_CPU].rlim_max)
				u.u_rlimit[RLIMIT_CPU].rlim_cur += 5;
E 108
I 108
			if (p->p_rlimit[RLIMIT_CPU].rlim_cur <
			    p->p_rlimit[RLIMIT_CPU].rlim_max)
				p->p_rlimit[RLIMIT_CPU].rlim_cur += 5;
E 114
I 114
		secs = p->p_utime.tv_sec + p->p_stime.tv_sec + 1;
		if (secs > p->p_rlimit[RLIMIT_CPU].rlim_cur) {
			if (secs > p->p_rlimit[RLIMIT_CPU].rlim_max)
				psignal(p, SIGKILL);
			else {
				psignal(p, SIGXCPU);
				if (p->p_rlimit[RLIMIT_CPU].rlim_cur <
				    p->p_rlimit[RLIMIT_CPU].rlim_max)
					p->p_rlimit[RLIMIT_CPU].rlim_cur += 5;
			}
E 114
E 108
		}
E 118
D 108
		if (timerisset(&u.u_timer[ITIMER_PROF].it_value) &&
		    itimerdecr(&u.u_timer[ITIMER_PROF], tick) == 0)
E 108
I 108
		if (timerisset(&pstats->p_timer[ITIMER_PROF].it_value) &&
		    itimerdecr(&pstats->p_timer[ITIMER_PROF], tick) == 0)
E 108
D 102
			psignal(u.u_procp, SIGPROF);
		s = u.u_procp->p_rssize;
E 102
I 102
			psignal(p, SIGPROF);
D 107
		s = p->p_rssize;
E 102
D 94
		u.u_ru.ru_idrss += s; u.u_ru.ru_isrss += 0;	/* XXX */
E 94
I 94
		u.u_ru.ru_idrss += s;
#ifdef notdef
		u.u_ru.ru_isrss += 0;		/* XXX (haven't got this) */
#endif
E 94
D 102
		if (u.u_procp->p_textp) {
			register int xrss = u.u_procp->p_textp->x_rssize;
E 102
I 102
		if (p->p_textp) {
			register int xrss = p->p_textp->x_rssize;
E 102

			s += xrss;
			u.u_ru.ru_ixrss += xrss;
		}
		if (s > u.u_ru.ru_maxrss)
			u.u_ru.ru_maxrss = s;
E 107
E 73
E 59
D 108
	}
E 108
I 60
D 118

D 62
/* iostat statistics */
E 62
I 62
D 108
	/*
D 74
	 * We maintain statistics shown by user-level statistics
	 * programs:  the amount of time in each cpu state, and
	 * the amount of time each of DK_NDRIVE ``drives'' is busy.
	 */
E 62
E 60
D 12
	dk_time[a]++;
E 12
I 12
D 21
	dk_time[cpstate][dk_busy&(DK_NSTATES-1)]++;
E 21
I 21
	cp_time[cpstate]++;
D 29
	for (i = 0; i < DK_NDRIVE; i++)
		if (dk_busy&(1<<i))
			dk_time[i]++;
E 29
I 29
	for (s = 0; s < DK_NDRIVE; s++)
		if (dk_busy&(1<<s))
			dk_time[s]++;
I 38
D 60
	/*
	 * Adjust priority of current process.
	 */
E 60
I 60

D 62
/* adjust priority of current process */
E 62
I 62
	/*
E 74
	 * We adjust the priority of the current process.
	 * The priority of a process gets worse as it accumulates
	 * CPU time.  The cpu usage estimator (p_cpu) is increased here
	 * and the formula for computing priorities (in kern_synch.c)
	 * will compute a different value each time the p_cpu increases
	 * by 4.  The cpu usage estimator ramps up quite quickly when
	 * the process is running (linearly), and decays away exponentially,
	 * at a rate which is proportionally slower when the system is
	 * busy.  The basic principal is that the system will 90% forget
	 * that a process used a lot of CPU time in 5*loadav seconds.
	 * This causes the system to favor processes which haven't run
	 * much recently, and to round-robin among other processes.
	 */
E 62
E 60
E 38
E 29
E 21
E 12
	if (!noproc) {
E 108
I 108
		/*
		 * We adjust the priority of the current process.
		 * The priority of a process gets worse as it accumulates
		 * CPU time.  The cpu usage estimator (p_cpu) is increased here
		 * and the formula for computing priorities (in kern_synch.c)
		 * will compute a different value each time the p_cpu increases
		 * by 4.  The cpu usage estimator ramps up quite quickly when
		 * the process is running (linearly), and decays away
		 * exponentially, * at a rate which is proportionally slower
		 * when the system is busy.  The basic principal is that the
		 * system will 90% forget that a process used a lot of CPU
		 * time in 5*loadav seconds.  This causes the system to favor
		 * processes which haven't run much recently, and to
		 * round-robin among other processes.
		 */
E 108
D 60
		pp = u.u_procp;
I 20
		pp->p_cpticks++;
E 20
		if(++pp->p_cpu == 0)
			pp->p_cpu--;
E 60
I 60
D 102
		p = u.u_procp;
E 102
		p->p_cpticks++;
		if (++p->p_cpu == 0)
			p->p_cpu--;
E 60
I 57
D 75
#ifdef MUSH
D 60
		pp->p_quota->q_cost += (pp->p_nice > NZERO ?
		    (shconsts.sc_tic * ((2*NZERO)-pp->p_nice)) / NZERO :
E 60
I 60
		p->p_quota->q_cost += (p->p_nice > NZERO ?
		    (shconsts.sc_tic * ((2*NZERO)-p->p_nice)) / NZERO :
E 60
		    shconsts.sc_tic) * (((int)avenrun[0]+2)/3);
#endif
E 75
E 57
D 44
		if(pp->p_cpu % 16 == 0) {
E 44
I 44
D 60
		if(pp->p_cpu % 4 == 0) {
E 44
D 5
			VOID setpri(pp);
E 5
I 5
			(void) setpri(pp);
E 5
			if (pp->p_pri >= PUSER)
				pp->p_pri = pp->p_usrpri;
E 60
I 60
D 62
		if (p->p_cpu % 4 == 0) {
E 62
I 62
		if ((p->p_cpu&3) == 0) {
E 62
D 108
			(void) setpri(p);
E 108
I 108
			setpri(p);
E 108
			if (p->p_pri >= PUSER)
				p->p_pri = p->p_usrpri;
E 60
		}
E 118
	}
I 38
D 60
	/*
	 * Time moves on.
	 */
E 38
	++lbolt;
I 50

	/*
	 * Time moves on for protocols.
	 */
D 52
	++protoslow; ++protofast;
E 52
I 52
D 56
	--protoslow; --protofast;
E 56
I 56
	--protoslow; --protofast; --ifnetslow;
E 56
E 52

E 50
I 29
D 30
#ifdef KPROF
	if (!USERMODE(ps) && !noproc) {
		register int indx = ((int)pc & 0x7fffffff) / 4;

		if (indx >= 0 && indx < 20000)
			if (++kcount[indx] == 0)
				--kcount[indx];
	}
#endif
E 30
D 33
#if VAX==780
	if (!BASEPRI(ps))
E 33
I 33
#if VAX780
I 38
	/*
	 * On 780's, impelement a fast UBA watcher,
	 * to make sure uba's don't get stuck.
	 */
E 38
D 37
	if (cpu == VAX_780 && !BASEPRI(ps))
E 37
I 37
	if (cpu == VAX_780 && panicstr == 0 && !BASEPRI(ps))
E 37
E 33
		unhang();
#endif
I 38
	/*
	 * Schedule a software interrupt for the rest
	 * of clock activities.
	 */
E 60
I 60
D 62
	bumptime(&time);
E 62
I 62

	/*
I 74
D 77
	 * If this is the only timer then we have to use it to
	 * gather statistics.
	 */
#ifndef KGCLOCK
	gatherstats(pc, ps);
#else
	/*
E 77
D 118
	 * If the alternate clock has not made itself known then
	 * we must gather the statistics.
E 118
I 118
	 * If no separate statistics clock is available, run it from here.
E 118
	 */
D 116
	if (phz == 0)
E 116
I 116
	if (stathz == 0)
E 116
I 106
D 108
#ifdef i386
		gatherstats(pc, ISPL(frame.if_cs), frame.if_ppl);
#else
E 106
		gatherstats(pc, ps);
I 106
#endif
E 108
I 108
D 118
		gatherstats(&frame);
E 118
I 118
		statclock(frame);
E 118
E 108
E 106
D 77
#endif
E 77

	/*
E 74
D 118
	 * Increment the time-of-day, and schedule
	 * processing of the callouts at a very low cpu priority,
	 * so we don't keep the relatively high clock interrupt
	 * priority any longer than necessary.
E 118
I 118
D 120
	 * Increment the time-of-day.
E 120
I 120
	 * Increment the time-of-day.  The increment is just ``tick'' unless
	 * we are still adjusting the clock; see adjtime().
E 120
E 118
	 */
I 122
	ticks++;
E 122
I 83
#ifdef ADJTIME
	if (adjtimedelta == 0)
		bumptime(&time, tick);
	else {
		if (adjtimedelta < 0) {
			bumptime(&time, tick-ADJ_TICK);
			adjtimedelta++;
		} else {
			bumptime(&time, tick+ADJ_TICK);
			adjtimedelta--;
		}
	}
#else
E 83
D 87
	bumptime(&time, tick);
E 87
I 87
D 89
	BUMPTIME(&time, tick);
E 89
I 89
D 95
	if (adjtimedelta == 0)
E 95
I 95
D 115
	if (timedelta == 0)
E 115
I 115
D 118
	ticks++;
E 118
D 120
	if (timedelta == 0) {
E 115
E 95
D 118
		BUMPTIME(&time, tick)
D 115
	else {
E 115
I 115
		BUMPTIME(&mono_time, tick)
E 118
I 118
		BUMPTIME(&time, tick);
		BUMPTIME(&mono_time, tick);
E 118
	} else {
E 115
D 118
		register delta;
E 118
I 118
		register int delta;
E 118

D 95
		if (adjtimedelta < 0) {
			delta = tick - tickadj;
			adjtimedelta += tickadj;
E 95
I 95
		if (timedelta < 0) {
			delta = tick - tickdelta;
			timedelta += tickdelta;
E 95
		} else {
D 95
			delta = tick + tickadj;
			adjtimedelta -= tickadj;
E 95
I 95
			delta = tick + tickdelta;
			timedelta -= tickdelta;
E 95
		}
		BUMPTIME(&time, delta);
I 115
D 118
		BUMPTIME(&mono_time, delta)
E 118
I 118
		BUMPTIME(&mono_time, delta);
E 120
I 120
	if (timedelta == 0)
		delta = tick;
	else {
		delta = tick + tickdelta;
		timedelta -= tickdelta;
E 120
E 118
E 115
	}
I 120
	BUMPTIME(&time, delta);
	BUMPTIME(&mono_time, delta);
E 120
I 118

	/*
	 * Process callouts at a very low cpu priority, so we don't keep the
	 * relatively high clock interrupt priority any longer than necessary.
	 */
E 118
E 89
E 87
I 83
#endif
E 83
E 62
E 60
E 38
D 76
	setsoftclock();
E 76
I 76
D 81
D 86
	if (needsoft)
		setsoftclock();
E 86
I 86
	if (needsoft) {
I 106
D 108
#ifdef i386
		if (frame.if_ppl == 0) {
#else
E 106
		if (BASEPRI(ps)) {
I 106
#endif
E 108
I 108
D 118
		if (CLKF_BASEPRI(&frame)) {
E 118
I 118
		if (CLKF_BASEPRI(frame)) {
E 118
E 108
E 106
			/*
			 * Save the overhead of a software interrupt;
			 * it will happen as soon as we return, so do it now.
			 */
D 118
			(void) splsoftclock();
I 106
D 108
#ifdef i386
E 108
			softclock(frame);
E 118
I 118
			(void)splsoftclock();
			softclock();
E 118
D 108
#else
E 106
			softclock(pc, ps);
I 106
#endif
E 108
E 106
		} else
			setsoftclock();
	}
E 86
E 81
I 81
	setsoftclock();
E 81
E 76
I 74
}
I 76
D 79
#ifdef sun
#undef pc
#undef ps
#endif
E 79
E 76

I 82
D 118
int	dk_ndrive = DK_NDRIVE;
E 118
E 82
/*
D 118
 * Gather statistics on resource utilization.
 *
 * We make a gross assumption: that the system has been in the
 * state it is in (user state, kernel state, interrupt state,
 * or idle state) for the entire last time interval, and
 * update statistics accordingly.
 */
I 76
D 108
/*ARGSUSED*/
I 106
#ifdef i386
#undef pc
gatherstats(pc, ps, ppl)
#else
E 106
E 76
gatherstats(pc, ps)
I 106
#endif
E 106
	caddr_t pc;
	int ps;
E 108
I 108
gatherstats(framep)
	clockframe *framep;
E 108
{
D 94
	int cpstate, s;
E 94
I 94
	register int cpstate, s;
E 94

	/*
	 * Determine what state the cpu is in.
	 */
I 106
D 108
#ifdef i386
	if (ps == SEL_UPL) {
#else
E 106
	if (USERMODE(ps)) {
I 106
#endif
E 108
I 108
	if (CLKF_USERMODE(framep)) {
E 108
E 106
		/*
		 * CPU was in user state.
		 */
D 108
		if (u.u_procp->p_nice > NZERO)
E 108
I 108
		if (curproc->p_nice > NZERO)
E 108
			cpstate = CP_NICE;
		else
			cpstate = CP_USER;
	} else {
		/*
		 * CPU was in system state.  If profiling kernel
D 93
		 * increment a counter.
E 93
I 93
		 * increment a counter.  If no process is running
		 * then this is a system tick if we were running
		 * at a non-zero IPL (in a driver).  If a process is running,
		 * then we charge it with system time even if we were
		 * at a non-zero IPL, since the system often runs
		 * this way during processing of system calls.
		 * This is approximate, but the lack of true interval
		 * timers makes doing anything else difficult.
E 93
		 */
		cpstate = CP_SYS;
I 106
D 108
#if defined(i386)
		if (noproc && ps == 0)
#else
E 106
		if (noproc && BASEPRI(ps))
I 106
#endif
E 108
I 108
D 109
		if (noproc && CLKF_BASEPRI(framep))
E 109
I 109
		if (curproc == NULL && CLKF_BASEPRI(framep))
E 109
E 108
E 106
			cpstate = CP_IDLE;
#ifdef GPROF
D 108
		s = pc - s_lowpc;
E 108
I 108
		s = CLKF_PC(framep) - s_lowpc;
E 108
		if (profiling < 2 && s < s_textsize)
			kcount[s / (HISTFRACTION * sizeof (*kcount))]++;
#endif
	}
	/*
	 * We maintain statistics shown by user-level statistics
	 * programs:  the amount of time in each cpu state, and
	 * the amount of time each of DK_NDRIVE ``drives'' is busy.
	 */
	cp_time[cpstate]++;
	for (s = 0; s < DK_NDRIVE; s++)
D 94
		if (dk_busy&(1<<s))
E 94
I 94
D 98
		if (dk_busy & (1 << s))
E 98
I 98
		if (dk_busy&(1<<s))
E 98
E 94
			dk_time[s]++;
E 74
}

I 62
/*
 * Software priority level clock interrupt.
E 118
I 118
 * Software (low priority) clock interrupt.
E 118
 * Run periodic events from timeout queue.
 */
E 62
D 60
/*
D 38
 * Constant for decay filter for cpu usage.
E 38
I 38
D 44
 * SCHMAG is the constant in the digital decay cpu
 * usage priority assignment.  Each second we multiply
 * the previous cpu usage estimate by SCHMAG.  At 9/10
 * it tends to decay away all knowledge of previous activity
 * in about 10 seconds.
E 44
I 44
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
E 44
E 38
 */
I 45
#undef ave
E 45
I 38
D 44
#define	SCHMAG	9/10
E 44
I 44
#define	ave(a,b) ((int)(((int)(a*b))/(b+1)))
int	nrscale = 2;
double	avenrun[];
E 44

/*
 * Constant for decay filter for cpu usage field
 * in process table (used by ps au).
 */
E 38
double	ccpu = 0.95122942450071400909;		/* exp(-1/20) */

I 57
#ifdef MELB
E 57
/*
I 57
 * Automatic niceness rate & max constants
 */
#define	MAXNICE	(8 + NZERO)	/* maximum auto nice value */
#define	NFACT	(40 * hz)	/* nice++ every 40 secs cpu+sys time */
#endif

/*
E 57
 * Software clock interrupt.
D 38
 * This routine is blocked by spl1(),
 * which doesn't block device interrupts!
E 38
I 38
 * This routine runs at lower priority than device interrupts.
E 38
 */
E 60
I 31
/*ARGSUSED*/
I 106
D 108
#ifdef i386
E 108
D 118
softclock(frame)
D 108
	struct	intrframe frame;
#define	pc	frame.if_eip
#else
E 106
I 65
D 66
#if vax
E 66
I 66
D 79
#ifdef vax
E 79
E 66
E 65
E 31
softclock(pc, ps)
D 30
caddr_t pc;
E 30
I 30
	caddr_t pc;
I 65
	int ps;
I 106
#endif
E 108
I 108
	clockframe frame;
E 118
I 118
void
softclock()
E 118
E 108
E 106
E 65
E 30
{
I 118
	register struct callout *c;
	register void *arg;
	register void (*func) __P((void *));
	register int s;
E 118
I 65
D 79
#endif
D 66
#if sun
E 66
I 66
#ifdef sun
E 66
D 70
softclock(sirret, regs)
	caddr_t sirreg;
	struct regs regs;
E 70
I 70
softclock()
E 70
{
D 70
	int ps = regs.r_sr;
	caddr_t pc = (caddr_t)regs.r_pc;
E 70
I 70
D 76
	int ps = u.u_ar0[PS];
	caddr_t pc = (caddr_t)u.u_ar0[PC];
E 76
I 76
#define	pc	(caddr_t)u.u_ar0[PC]
#define	ps	u.u_ar0[PS]
E 76
E 70
#endif
E 79
E 65
D 36
	register struct callo *p1, *p2;
E 36
I 36
D 43
	register struct callout *p1, *p2;
E 43
I 43
D 62
	register struct callout *p1;
E 43
E 36
D 60
	register struct proc *pp;
E 60
	register int a, s;
I 42
	caddr_t arg;
	int (*func)();
E 62
E 42

D 60
	/*
D 37
	 * callout
E 37
I 37
	 * Perform callouts (but not after panic's!)
E 37
	 */
D 37
	if(callout[0].c_time <= 0) {
E 37
I 37
D 42
	if (panicstr == 0 && callout[0].c_time <= 0) {
E 37
		p1 = &callout[0];
D 37
		while(p1->c_func != 0 && p1->c_time <= 0) {
E 37
I 37
		while (p1->c_func != 0 && p1->c_time <= 0) {
E 37
			(*p1->c_func)(p1->c_arg);
			p1++;
E 42
I 42
	if (panicstr == 0) {
		for (;;) {
			s = spl7();
D 46
			if ((p1 = calltodo.c_next) == 0 || p1->c_time > 0)
E 46
I 46
			if ((p1 = calltodo.c_next) == 0 || p1->c_time > 0) {
				splx(s);
E 46
				break;
I 46
			}
E 46
			calltodo.c_next = p1->c_next;
			arg = p1->c_arg;
			func = p1->c_func;
			p1->c_next = callfree;
			callfree = p1;
			(void) splx(s);
			(*func)(arg);
E 60
I 60
D 62
	if (panicstr)
		goto nocallout;
E 62
D 118
	for (;;) {
I 62
		register struct callout *p1;
		register caddr_t arg;
		register int (*func)();
		register int a, s;

E 62
D 94
		s = spl7();
E 94
I 94
		s = splhigh();
E 94
		if ((p1 = calltodo.c_next) == 0 || p1->c_time > 0) {
			splx(s);
			break;
E 60
E 42
		}
I 62
		arg = p1->c_arg; func = p1->c_func; a = p1->c_time;
E 62
I 60
		calltodo.c_next = p1->c_next;
D 62
		arg = p1->c_arg;
		func = p1->c_func;
I 61
		a = p1->c_time;
E 62
E 61
		p1->c_next = callfree;
		callfree = p1;
E 118
I 118
	s = splhigh();
	while ((c = calltodo.c_next) != NULL && c->c_time <= 0) {
		func = c->c_func;
		arg = c->c_arg;
		calltodo.c_next = c->c_next;
		c->c_next = callfree;
		callfree = c;
E 118
D 67
		(void) splx(s);
E 67
I 67
		splx(s);
E 67
D 61
		(*func)(arg);
E 61
I 61
D 118
		(*func)(arg, a);
E 118
I 118
		(*func)(arg);
		(void) splhigh();
E 118
I 68
	}
D 118
	/*
D 78
	 * If trapped user-mode, give it a profiling tick.
E 78
I 78
	 * If trapped user-mode and profiling, give it
	 * a profiling tick.
E 78
	 */
I 106
D 108
#ifdef i386
	if (ISPL(frame.if_cs) == SEL_UPL) {
#else
E 106
D 78
	if (USERMODE(ps) && u.u_prof.pr_scale) {
		u.u_procp->p_flag |= SOWEUPC;
		aston();
E 78
I 78
	if (USERMODE(ps)) {
I 106
#endif
E 106
		register struct proc *p = u.u_procp;
E 108
I 108
	if (CLKF_USERMODE(&frame)) {
		register struct proc *p = curproc;
E 108

D 108
		if (u.u_prof.pr_scale) {
			p->p_flag |= SOWEUPC;
			aston();
		}
E 108
I 108
		if (p->p_stats->p_prof.pr_scale)
			profile_tick(p, &frame);
E 108
D 79
#ifdef vax
E 79
		/*
		 * Check to see if process has accumulated
		 * more than 10 minutes of user time.  If so
		 * reduce priority to give others a chance.
		 */
D 108
		if (p->p_uid && p->p_nice == NZERO &&
E 108
I 108
		if (p->p_ucred->cr_uid && p->p_nice == NZERO &&
E 108
D 102
		    u.u_ru.ru_utime.tv_sec > 10 * 60) {
E 102
I 102
		    p->p_utime.tv_sec > 10 * 60) {
E 102
D 108
			p->p_nice = NZERO+4;
			(void) setpri(p);
E 108
I 108
			p->p_nice = NZERO + 4;
			setpri(p);
E 108
			p->p_pri = p->p_usrpri;
		}
D 79
#endif
E 79
E 78
E 68
E 61
E 60
D 42
		p2 = &callout[0];
D 37
		while(p2->c_func = p1->c_func) {
E 37
I 37
		while (p2->c_func = p1->c_func) {
E 37
			p2->c_time = p1->c_time;
			p2->c_arg = p1->c_arg;
			p1++;
			p2++;
		}
E 42
D 87
	}
I 60
D 62
nocallout:
E 60

D 60
	/*
	 * Drain silos.
	 */
E 60
I 41
D 47
#if NBK > 0
E 47
E 41
D 32
#if NDH11 > 0
E 32
I 32
#if NDH > 0
E 32
	s = spl5(); dhtimer(); splx(s);
#endif
D 32
#if NDZ11 > 0
E 32
I 32
#if NDZ > 0
E 32
	s = spl5(); dztimer(); splx(s);
I 41
D 47
#endif
E 47
E 41
#endif

D 60
	/*
I 30
	 * If idling and processes are waiting to swap in,
	 * check on them.
	 */
E 60
I 60
/* if nothing to do, try swapin */
E 60
	if (noproc && runin) {
		runin = 0;
		wakeup((caddr_t)&runin);
	}
E 62
D 60

	/*
E 30
D 44
	 * Run paging daemon and reschedule every 1/4 sec.
E 44
I 44
	 * Run paging daemon every 1/4 sec.
E 44
	 */
E 29
D 36
	if (lbolt % (HZ/4) == 0) {
E 36
I 36
	if (lbolt % (hz/4) == 0) {
E 36
		vmpago();
I 44
	}

	/*
	 * Reschedule every 1/10 sec.
	 */
	if (lbolt % (hz/10) == 0) {
E 44
		runrun++;
I 29
		aston();
E 29
	}
I 50

	/*
	 * Run network slow and fast timeouts.
	 */
D 52
	if (protofast >= hz / PR_FASTHZ)
E 52
I 52
	if (protofast <= 0) {
		protofast = hz / PR_FASTHZ;
E 52
		pffasttimo();
D 52
	if (protofast >= hz / PR_SLOWHZ)
E 52
I 52
	}
	if (protoslow <= 0) {
		protoslow = hz / PR_SLOWHZ;
E 52
		pfslowtimo();
I 56
	}
	if (ifnetslow <= 0) {
		ifnetslow = hz / IFNET_SLOWHZ;
		if_slowtimo();
E 56
I 52
	}
E 52
E 50
I 29

	/*
	 * Lightning bolt every second:
	 *	sleep timeouts
	 *	process priority recomputation
	 *	process %cpu averaging
	 *	virtual memory metering
	 *	kick swapper if processes want in
	 */
E 29
D 36
	if (lbolt >= HZ) {
E 36
I 36
	if (lbolt >= hz) {
I 37
		/*
D 38
		 * This doesn't mean much since we run at
E 38
I 38
		 * This doesn't mean much on VAX since we run at
E 38
		 * software interrupt time... if hardclock()
		 * calls softclock() directly, it prevents
		 * this code from running when the priority
		 * was raised when the clock interrupt occurred.
		 */
E 37
E 36
I 24
D 28
#if VAX==780
E 24
I 18
		extern int hangcnt;
I 24
#endif
E 24

E 28
E 18
		if (BASEPRI(ps))
			return;
D 36
		lbolt -= HZ;
E 36
I 36
D 37
		lbolt -= hz;
E 36
		++time;
E 37
I 37

		/*
		 * If we didn't run a few times because of
		 * long blockage at high ipl, we don't
		 * really want to run this code several times,
		 * so squish out all multiples of hz here.
		 */
D 54
		time += lbolt / hz;
		lbolt %= hz;
E 54
I 54
		s = spl6();
D 59
		time += lbolt / hz; lbolt %= hz;
E 59
I 59
		time.tv_sec += lbolt / hz; lbolt %= hz;
E 59
		splx(s);
E 54

		/*
		 * Wakeup lightning bolt sleepers.
		 * Processes sleep on lbolt to wait
		 * for short amounts of time (e.g. 1 second).
		 */
E 37
D 5
		VOID spl1();
E 5
I 5
D 29
		(void) spl1();
I 24
D 28
#if VAX==780
E 24
I 18
		/*
		 * machdep.c:unhang uses hangcnt to make sure uba
		 * doesn't forget to interrupt (this has been observed).
		 * This prevents an accumulation of < 5 second uba failures
		 * from summing to a uba reset.
		 */
		if (hangcnt)
			hangcnt--;
E 28
I 28
#if VAX780
		ubawatch();		/* should be a timeout */
E 28
I 24
#endif
E 24
E 18
E 5
		runrun++;
E 29
		wakeup((caddr_t)&lbolt);
D 34
		for(pp = &proc[0]; pp < &proc[NPROC]; pp++)
E 34
I 34
D 37
		for(pp = proc; pp < procNPROC; pp++)
E 37
I 37

		/*
		 * Recompute process priority and process
		 * sleep() system calls as well as internal
		 * sleeps with timeouts (tsleep() kernel routine).
		 */
		for (pp = proc; pp < procNPROC; pp++)
E 37
E 34
D 19
		if (pp->p_stat && pp->p_stat<SZOMB) {
E 19
I 19
		if (pp->p_stat && pp->p_stat!=SZOMB) {
I 57
#ifdef MUSH
E 57
E 19
D 37
			if(pp->p_time != 127)
E 37
I 37
			/*
I 57
			 * Charge process for memory in use
			 */
			if (pp->p_quota->q_uid)
				pp->p_quota->q_cost +=
				    shconsts.sc_click * pp->p_rssize;
#endif
			/*
E 57
			 * Increase resident time, to max of 127 seconds
			 * (it is kept in a character.)  For
			 * loaded processes this is time in core; for
			 * swapped processes, this is time on drum.
			 */
			if (pp->p_time != 127)
E 37
				pp->p_time++;
D 37
			if(pp->p_clktim)
				if(--pp->p_clktim == 0)
D 2
					psignal(pp, SIGCLK);
E 2
I 2
					if (pp->p_flag & STIMO) {
						s = spl6();
D 9
						if (pp->p_stat == SSLEEP)
E 9
I 9
						switch (pp->p_stat) {
E 37
I 37
			/*
D 59
			 * If process has clock counting down, and it
			 * expires, set it running (if this is a tsleep()),
			 * or give it an SIGALRM (if the user process
			 * is using alarm signals.
E 59
I 59
			 * Time processes out of select.
E 59
			 */
D 59
			if (pp->p_clktim && --pp->p_clktim == 0)
				if (pp->p_flag & STIMO) {
					s = spl6();
					switch (pp->p_stat) {
E 59
I 59
			if (timerisset(&pp->p_seltimer) &&
			     --pp->p_seltimer.tv_sec <= 0) {
				timerclear(&pp->p_seltimer);
				s = spl6();
				switch (pp->p_stat) {
E 59
E 37

D 37
						case SSLEEP:
E 9
							setrun(pp);
I 9
							break;
E 37
I 37
D 59
					case SSLEEP:
						setrun(pp);
						break;
E 59
I 59
				case SSLEEP:
					setrun(pp);
					break;
E 59
E 37

D 37
						case SSTOP:
							unsleep(pp);
							break;
						}
E 9
						pp->p_flag &= ~STIMO;
						splx(s);
					} else
D 8
						psignal(pp, SIGCLK);
E 8
I 8
						psignal(pp, SIGALRM);
E 8
E 2
			if(pp->p_stat==SSLEEP||pp->p_stat==SSTOP)
E 37
I 37
D 59
					case SSTOP:
						unsleep(pp);
						break;
					}
					pp->p_flag &= ~STIMO;
					splx(s);
				} else
					psignal(pp, SIGALRM);
E 59
I 59
				case SSTOP:
					unsleep(pp);
					break;
				}
				splx(s);
			}
			if (timerisset(&pp->p_realtimer.itimer_value) &&
			    itimerdecr(&pp->p_realtimer, 1000000) == 0)
				psignal(pp, SIGALRM);

E 59
			/*
			 * If process is blocked, increment computed
			 * time blocked.  This is used in swap scheduling.
			 */
			if (pp->p_stat==SSLEEP || pp->p_stat==SSTOP)
E 37
				if (pp->p_slptime != 127)
					pp->p_slptime++;
I 37
			/*
			 * Update digital filter estimation of process
			 * cpu utilization for loaded processes.
			 */
E 37
D 20
			if(pp->p_flag&SLOAD) {
				ave(pp->p_aveflt, pp->p_faults, 5);
				pp->p_faults = 0;
			}
E 20
I 20
			if (pp->p_flag&SLOAD)
				pp->p_pctcpu = ccpu * pp->p_pctcpu +
D 36
				    (1.0 - ccpu) * (pp->p_cpticks/(float)HZ);
E 36
I 36
				    (1.0 - ccpu) * (pp->p_cpticks/(float)hz);
I 37
			/*
			 * Recompute process priority.  The number p_cpu
			 * is a weighted estimate of cpu time consumed.
			 * A process which consumes cpu time has this
			 * increase regularly.  We here decrease it by
D 44
			 * a fraction (SCHMAG is 90%), giving a digital
			 * decay filter which damps out in about 10 seconds.
E 44
I 44
			 * a fraction based on load average giving a digital
			 * decay filter which damps out in about 5 seconds
			 * when seconds are measured in time expanded by the
			 * load average.
E 44
			 *
			 * If a process is niced, then the nice directly
			 * affects the new priority.  The final priority
			 * is in the range 0 to 255, to fit in a character.
			 */
E 37
E 36
			pp->p_cpticks = 0;
I 57
#ifdef MUSH
E 57
E 20
D 44
			a = (pp->p_cpu & 0377)*SCHMAG + pp->p_nice - NZERO;
E 44
I 44
			a = ave((pp->p_cpu & 0377), avenrun[0]*nrscale) +
I 57
			     pp->p_nice - NZERO + pp->p_quota->q_nice;
#else
			a = ave((pp->p_cpu & 0377), avenrun[0]*nrscale) +
E 57
			     pp->p_nice - NZERO;
I 57
#endif
E 57
E 44
D 37
			if(a < 0)
E 37
I 37
			if (a < 0)
E 37
				a = 0;
D 37
			if(a > 255)
E 37
I 37
			if (a > 255)
E 37
				a = 255;
			pp->p_cpu = a;
D 5
			VOID setpri(pp);
E 5
I 5
			(void) setpri(pp);
I 37
			/*
			 * Now have computed new process priority
			 * in p->p_usrpri.  Carefully change p->p_pri.
			 * A process is on a run queue associated with
			 * this priority, so we must block out process
			 * state changes during the transition.
			 */
E 37
E 5
			s = spl6();
D 37
			if(pp->p_pri >= PUSER) {
E 37
I 37
			if (pp->p_pri >= PUSER) {
E 37
				if ((pp != u.u_procp || noproc) &&
				    pp->p_stat == SRUN &&
				    (pp->p_flag & SLOAD) &&
				    pp->p_pri != pp->p_usrpri) {
					remrq(pp);
					pp->p_pri = pp->p_usrpri;
					setrq(pp);
				} else
					pp->p_pri = pp->p_usrpri;
			}
			splx(s);
		}
I 37

		/*
		 * Perform virtual memory metering.
		 */
E 37
		vmmeter();
D 37
		if(runin!=0) {
E 37
I 37

		/*
		 * If the swap process is trying to bring
		 * a process in, have it look again to see
		 * if it is possible now.
		 */
		if (runin!=0) {
E 37
			runin = 0;
			wakeup((caddr_t)&runin);
		}
I 37

E 37
		/*
		 * If there are pages that have been cleaned, 
		 * jolt the pageout daemon to process them.
		 * We do this here so that these pages will be
		 * freed if there is an abundance of memory and the
		 * daemon would not be awakened otherwise.
		 */
		if (bclnlist != NULL)
			wakeup((caddr_t)&proc[2]);
I 37

I 57
#ifdef MELB
E 57
		/*
I 57
		 * If a process was running, see if time to make it nicer
		 */
		if (!noproc) {
			pp = u.u_procp;
			if (pp->p_uid
#ifdef MUSH
				&& !(pp->p_flag & SLOGIN)
#else
				     /* this is definitely not good enough */
				&& (pp->p_pid != pp->p_pgrp || pp->p_ppid != 1)
#endif
D 59
				&& (u.u_vm.vm_utime + u.u_vm.vm_stime) >
E 59
I 59
				&& (u.u_ru.ru_utime + u.u_ru.ru_stime) >
E 59
					(pp->p_nice-NZERO+1)*NFACT
				&& pp->p_nice >= NZERO
				&& pp->p_nice < MAXNICE
			) {
				pp->p_nice++;
				(void) setpri(pp);
				pp->p_pri = pp->p_usrpri;
			}
		}
#else
		/*
E 57
		 * If the trap occurred from usermode,
		 * then check to see if it has now been
		 * running more than 10 minutes of user time
		 * and should thus run with reduced priority
		 * to give other processes a chance.
		 */
E 37
D 14
#ifdef ERNIE
E 14
		if (USERMODE(ps)) {
			pp = u.u_procp;
I 14
D 27
#ifdef ERNIE
E 27
E 14
D 37
			if (pp->p_uid)
D 36
				if (pp->p_nice == NZERO && u.u_vm.vm_utime > 600 * HZ)
E 36
I 36
				if (pp->p_nice == NZERO && u.u_vm.vm_utime > 600 * hz)
E 36
					pp->p_nice = NZERO+4;
E 37
I 37
			if (pp->p_uid && pp->p_nice == NZERO &&
D 59
			    u.u_vm.vm_utime > 600 * hz)
E 59
I 59
			    u.u_ru.ru_utime.tv_sec > 600)
E 59
				pp->p_nice = NZERO+4;
E 37
D 5
			VOID setpri(pp);
E 5
I 5
			(void) setpri(pp);
E 5
			pp->p_pri = pp->p_usrpri;
D 14
		}
E 14
D 27
#endif
E 27
I 14
D 16
			if (u.u_vm.vm_utime+u.u_vm.vm_stime > u.u_limit[LIM_CPU])
E 16
I 16
D 17
			if ((u.u_vm.vm_utime+u.u_vm.vm_stime)/HZ > u.u_limit[LIM_CPU])
E 16
				psignal(pp, SIGXCPU);
E 17
		}
I 57
#endif
E 57
E 14
	}
I 37
	/*
	 * If trapped user-mode, give it a profiling tick.
	 */
E 37
I 24
D 29
#if VAX==780
E 24
I 11
	if (!BASEPRI(ps))
		unhang();
I 24
#endif
E 24
E 11
	if (USERMODE(ps)) {
		/*
		 * We do this last since it
		 * may block on a page fault in user space.
		 */
		if (u.u_prof.pr_scale)
			addupc(pc, &u.u_prof, 1);
E 29
I 29
D 59
	if (USERMODE(ps) && u.u_prof.pr_scale) {
		u.u_procp->p_flag |= SOWEUPC;
		aston();
E 29
	}
E 59
I 59
	if (USERMODE(ps) &&
	    timerisset(&u.u_timer[ITIMER_VIRTUAL].itimer_value) &&
	    itimerdecr(&u.u_timer[ITIMER_VIRTUAL].itimer_value, 1000000/hz) == 0)
		psignal(u.u_procp, SIGPROF);
E 60
E 59
D 29
#ifdef KPROF
	else if (!noproc) {
D 3
		register int indx = ((int)pc & 0x7fffffff) / 8;
E 3
I 3
		register int indx = ((int)pc & 0x7fffffff) / 4;
E 3

		if (indx >= 0 && indx < 20000)
D 3
			kcount[indx]++;
E 3
I 3
			if (++kcount[indx] == 0)
				--kcount[indx];
E 3
	}
#endif
E 29
}

/*
D 38
 * timeout is called to arrange that
E 38
I 38
D 60
 * Timeout is called to arrange that
E 38
D 36
 * fun(arg) is called in tim/HZ seconds.
E 36
I 36
 * fun(arg) is called in tim/hz seconds.
E 36
D 42
 * An entry is sorted into the callout
E 42
I 42
 * An entry is linked into the callout
E 42
D 38
 * structure. The time in each structure
E 38
I 38
 * structure.  The time in each structure
E 38
D 36
 * entry is the number of HZ's more
E 36
I 36
 * entry is the number of hz's more
E 36
 * than the previous entry.
 * In this way, decrementing the
 * first entry has the effect of
 * updating all entries.
 *
 * The panic is there because there is nothing
 * intelligent to be done if an entry won't fit.
E 60
I 60
D 76
 * Arrange that (*fun)(arg) is called in tim/hz seconds.
E 76
I 76
 * Bump a timeval by a small number of usec's.
E 76
E 60
 */
D 76
timeout(fun, arg, tim)
E 76
I 76
bumptime(tp, usec)
	register struct timeval *tp;
	int usec;
{

	tp->tv_usec += usec;
	if (tp->tv_usec >= 1000000) {
		tp->tv_usec -= 1000000;
		tp->tv_sec++;
E 87
	}
E 118
I 118
	splx(s);
E 118
}

/*
I 117
D 118
 * Notification of start of profiling clock
 *
 * Kernel profiling passes proc0 which never exits and hence
 * keeps the profile clock running constantly.
 */
startprofclock(p)
	struct proc *p;
{

	if (p->p_flag & SPROFIL)
		return;
	profprocs++;
	p->p_flag |= SPROFIL;
#ifdef PROFTIMER
	initprofclock(profprocs);
#else
	profhz = hz;
#endif
}

/*
 * Notification of stopping of profile clock
 */
stopprofclock(p)
	struct proc *p;
{

	if ((p->p_flag & SPROFIL) == 0)
		return;
	profprocs--;
	p->p_flag &= ~SPROFIL;
#ifdef PROFTIMER
	initprofclock(profprocs);
#endif
}

/*
E 118
E 117
D 108
 * Arrange that (*fun)(arg) is called in t/hz seconds.
E 108
I 108
D 129
 * Arrange that (*func)(arg) is called in t/hz seconds.
E 129
I 129
 * timeout --
 *	Execute a function after a specified length of time.
 *
 * untimeout --
 *	Cancel previous timeout function call.
 *
 *	See AT&T BCI Driver Reference Manual for specification.  This
 *	implementation differs from that one in that no identification
 *	value is returned from timeout, rather, the original arguments
 *	to timeout are used to identify entries for untimeout.
E 129
E 108
 */
I 118
void
E 118
D 108
timeout(fun, arg, t)
E 76
D 30
int (*fun)();
caddr_t arg;
E 30
I 30
	int (*fun)();
E 108
I 108
D 129
timeout(func, arg, t)
D 118
	int (*func)();
E 108
	caddr_t arg;
E 118
I 118
	void (*func) __P((void *));
E 129
I 129
timeout(ftn, arg, ticks)
	void (*ftn) __P((void *));
E 129
	void *arg;
E 118
I 60
D 76
	int tim;
E 76
I 76
D 129
	register int t;
E 129
I 129
	register int ticks;
E 129
E 76
E 60
E 30
{
D 28
	register struct callo *p1, *p2;
E 28
I 28
D 36
	register struct callo *p1, *p2, *p3;
E 36
I 36
D 42
	register struct callout *p1, *p2, *p3;
E 42
I 42
D 129
	register struct callout *p1, *p2, *pnew;
E 129
I 129
	register struct callout *new, *p, *t;
E 129
E 42
E 36
E 28
D 76
	register int t;
	int s;
E 76
I 76
D 94
	register int s = spl7();
E 94
I 94
D 118
	register int s = splhigh();
E 118
I 118
	register int s;
E 118
E 94
E 76

I 129
	if (ticks <= 0)
		ticks = 1;

	/* Lock out the clock. */
E 129
I 118
	s = splhigh();
E 118
I 39
D 59
/* DEBUGGING CODE */
	int ttrstrt();

	if (fun == ttrstrt && arg == 0)
		panic("timeout ttrstr arg");
/* END DEBUGGING CODE */
E 59
E 39
D 76
	t = tim;
D 42
	p1 = &callout[0];
E 42
	s = spl7();
E 76
I 76
D 90
	if (t == 0)
E 90
I 90
D 129
	if (t <= 0)
E 90
		t = 1;
E 76
D 38
	while(p1->c_func != 0 && p1->c_time <= t) {
E 38
I 38
D 42
	while (p1->c_func != 0 && p1->c_time <= t) {
E 38
		t -= p1->c_time;
		p1++;
	}
D 28
	if (p1 >= &callout[NCALL-1])
		panic("Timeout table overflow");
E 28
	p1->c_time -= t;
	p2 = p1;
D 28
	while(p2->c_func != 0)
E 28
I 28
D 35
	p3 = &callout[NCALL-2];
E 35
I 35
D 36
	p3 = callout+(ncall-2);
E 36
I 36
	p3 = callout+(ncallout-2);
E 36
E 35
D 38
	while(p2->c_func != 0) {
E 38
I 38
	while (p2->c_func != 0) {
E 38
		if (p2 >= p3)
D 29
			panic("Timeout table overflow");
E 29
I 29
D 40
			panic("timeout");
E 40
I 40
			panic("timeout table overflow");
E 40
E 29
E 28
		p2++;
I 28
	}
E 28
D 38
	while(p2 >= p1) {
E 38
I 38
	while (p2 >= p1) {
E 38
		(p2+1)->c_time = p2->c_time;
		(p2+1)->c_func = p2->c_func;
		(p2+1)->c_arg = p2->c_arg;
		p2--;
	}
	p1->c_time = t;
	p1->c_func = fun;
	p1->c_arg = arg;
E 42
I 42
	pnew = callfree;
	if (pnew == NULL)
		panic("timeout table overflow");
	callfree = pnew->c_next;
	pnew->c_arg = arg;
D 108
	pnew->c_func = fun;
E 108
I 108
	pnew->c_func = func;
E 108
	for (p1 = &calltodo; (p2 = p1->c_next) && p2->c_time < t; p1 = p2)
D 69
		t -= p2->c_time;
E 69
I 69
		if (p2->c_time > 0)
			t -= p2->c_time;
E 69
	p1->c_next = pnew;
	pnew->c_next = p2;
	pnew->c_time = t;
	if (p2)
		p2->c_time -= t;
E 129
I 129

	/* Fill in the next free callout structure. */
	if (callfree == NULL)
		panic("timeout table full");
	new = callfree;
	callfree = new->c_next;
	new->c_arg = arg;
	new->c_func = ftn;

	/*
	 * The time for each event is stored as a difference from the time
	 * of the previous event on the queue.  Walk the queue, correcting
	 * the ticks argument for queue entries passed.  Correct the ticks
	 * value for the queue entry immediately after the insertion point
D 131
	 * as well.
E 131
I 131
	 * as well.  Watch out for negative c_time values; these represent
	 * overdue events.
E 131
	 */
	for (p = &calltodo;
	    (t = p->c_next) != NULL && ticks > t->c_time; p = t)
D 131
		ticks -= t->c_time;
E 131
I 131
		if (t->c_time > 0)
			ticks -= t->c_time;
E 131
	new->c_time = ticks;
	if (t != NULL)
		t->c_time -= ticks;

	/* Insert the new entry into the queue. */
	p->c_next = new;
	new->c_next = t;
E 129
I 53
	splx(s);
}

I 58
D 61
#ifdef notdef
E 61
E 58
D 129
/*
 * untimeout is called to remove a function timeout call
 * from the callout structure.
 */
E 129
I 118
void
E 118
D 60
untimeout (fun, arg)
E 60
I 60
D 108
untimeout(fun, arg)
E 60
	int (*fun)();
E 108
I 108
D 129
untimeout(func, arg)
D 118
	int (*func)();
E 108
	caddr_t arg;
E 118
I 118
	void (*func) __P((void *));
E 129
I 129
untimeout(ftn, arg)
	void (*ftn) __P((void *));
E 129
	void *arg;
E 118
{
D 61

E 61
D 129
	register struct callout *p1, *p2;
E 129
I 129
	register struct callout *p, *t;
E 129
	register int s;

D 94
	s = spl7();
E 94
I 94
	s = splhigh();
E 94
D 118
	for (p1 = &calltodo; (p2 = p1->c_next) != 0; p1 = p2) {
E 118
I 118
D 129
	for (p1 = &calltodo; (p2 = p1->c_next) != NULL; p1 = p2) {
E 118
D 108
		if (p2->c_func == fun && p2->c_arg == arg) {
E 108
I 108
		if (p2->c_func == func && p2->c_arg == arg) {
E 108
D 61
			if (p2->c_next)
E 61
I 61
			if (p2->c_next && p2->c_time > 0)
E 61
				p2->c_next->c_time += p2->c_time;
			p1->c_next = p2->c_next;
			p2->c_next = callfree;
			callfree = p2;
E 129
I 129
	for (p = &calltodo; (t = p->c_next) != NULL; p = t)
		if (t->c_func == ftn && t->c_arg == arg) {
			/* Increment next entry's tick count. */
			if (t->c_next && t->c_time > 0)
				t->c_next->c_time += t->c_time;

			/* Move entry from callout queue to callfree queue. */
			p->c_next = t->c_next;
			t->c_next = callfree;
			callfree = t;
E 129
			break;
		}
D 129
	}
E 129
E 53
E 42
	splx(s);
}
I 58
D 61
#endif
E 61
I 61

I 62
/*
D 129
 * Compute number of hz until specified time.
 * Used to compute third argument to timeout() from an
 * absolute time.
E 129
I 129
 * Compute number of hz until specified time.  Used to
 * compute third argument to timeout() from an absolute time.
E 129
 */
I 118
int
E 118
E 62
hzto(tv)
	struct timeval *tv;
{
D 62
	register int ticks;
E 62
I 62
D 118
	register long ticks;
	register long sec;
E 62
D 94
	int s = spl7();
E 94
I 94
	int s = splhigh();
E 118
I 118
	register long ticks, sec;
	int s;
E 118
E 94

D 62
	ticks = ((tv->tv_sec - time.tv_sec) * 1000 +
		(tv->tv_usec - time.tv_usec) / 1000) / (tick / 1000);
E 62
I 62
	/*
	 * If number of milliseconds will fit in 32 bit arithmetic,
	 * then compute number of milliseconds to time and scale to
	 * ticks.  Otherwise just compute number of hz in time, rounding
	 * times greater than representible to maximum value.
	 *
	 * Delta times less than 25 days can be computed ``exactly''.
	 * Maximum value for any timeout in 10ms ticks is 250 days.
	 */
I 118
	s = splhigh();
E 118
	sec = tv->tv_sec - time.tv_sec;
	if (sec <= 0x7fffffff / 1000 - 1000)
		ticks = ((tv->tv_sec - time.tv_sec) * 1000 +
			(tv->tv_usec - time.tv_usec) / 1000) / (tick / 1000);
	else if (sec <= 0x7fffffff / hz)
		ticks = sec * hz;
	else
		ticks = 0x7fffffff;
E 62
	splx(s);
	return (ticks);
I 76
}
I 113

/*
I 118
 * Start profiling on a process.
 *
 * Kernel profiling passes proc0 which never exits and hence
 * keeps the profile clock running constantly.
 */
void
startprofclock(p)
	register struct proc *p;
{
	int s;

D 130
	if ((p->p_flag & SPROFIL) == 0) {
		p->p_flag |= SPROFIL;
E 130
I 130
	if ((p->p_flag & P_PROFIL) == 0) {
		p->p_flag |= P_PROFIL;
E 130
		if (++profprocs == 1 && stathz != 0) {
			s = splstatclock();
			psdiv = pscnt = psratio;
			setstatclockrate(profhz);
			splx(s);
		}
	}
}

/*
 * Stop profiling on a process.
 */
void
stopprofclock(p)
	register struct proc *p;
{
	int s;

D 130
	if (p->p_flag & SPROFIL) {
		p->p_flag &= ~SPROFIL;
E 130
I 130
	if (p->p_flag & P_PROFIL) {
		p->p_flag &= ~P_PROFIL;
E 130
		if (--profprocs == 0 && stathz != 0) {
			s = splstatclock();
			psdiv = pscnt = 1;
			setstatclockrate(stathz);
			splx(s);
		}
	}
}

int	dk_ndrive = DK_NDRIVE;

/*
 * Statistics clock.  Grab profile sample, and if divider reaches 0,
 * do process and kernel statistics.
 */
void
statclock(frame)
	register struct clockframe *frame;
{
#ifdef GPROF
	register struct gmonparam *g;
#endif
	register struct proc *p;
	register int i;

	if (CLKF_USERMODE(frame)) {
		p = curproc;
D 130
		if (p->p_flag & SPROFIL)
E 130
I 130
		if (p->p_flag & P_PROFIL)
E 130
			addupc_intr(p, CLKF_PC(frame), 1);
		if (--pscnt > 0)
			return;
		/*
		 * Came from user mode; CPU was in user state.
		 * If this process is being profiled record the tick.
		 */
		p->p_uticks++;
		if (p->p_nice > NZERO)
			cp_time[CP_NICE]++;
		else
			cp_time[CP_USER]++;
	} else {
#ifdef GPROF
		/*
		 * Kernel statistics are just like addupc_intr, only easier.
		 */
		g = &_gmonparam;
		if (g->state == GMON_PROF_ON) {
			i = CLKF_PC(frame) - g->lowpc;
D 127
			if (i < g->textsize)
D 119
				kcount[s / (HISTFRACTION * sizeof(*kcount))]++;
E 119
I 119
				kcount[i / (HISTFRACTION * sizeof(*kcount))]++;
E 127
I 127
			if (i < g->textsize) {
				i /= HISTFRACTION * sizeof(*g->kcount);
				g->kcount[i]++;
			}
E 127
E 119
		}
#endif
		if (--pscnt > 0)
			return;
		/*
		 * Came from kernel mode, so we were:
		 * - handling an interrupt,
		 * - doing syscall or trap work on behalf of the current
		 *   user process, or
		 * - spinning in the idle loop.
		 * Whichever it is, charge the time as appropriate.
		 * Note that we charge interrupts to the current process,
		 * regardless of whether they are ``for'' that process,
		 * so that we know how much of its real time was spent
		 * in ``non-process'' (i.e., interrupt) work.
		 */
		p = curproc;
		if (CLKF_INTR(frame)) {
			if (p != NULL)
				p->p_iticks++;
			cp_time[CP_INTR]++;
		} else if (p != NULL) {
			p->p_sticks++;
			cp_time[CP_SYS]++;
		} else
			cp_time[CP_IDLE]++;
	}
	pscnt = psdiv;

	/*
	 * We maintain statistics shown by user-level statistics
	 * programs:  the amount of time in each cpu state, and
	 * the amount of time each of DK_NDRIVE ``drives'' is busy.
	 *
	 * XXX	should either run linked list of drives, or (better)
	 *	grab timestamps in the start & done code.
	 */
	for (i = 0; i < DK_NDRIVE; i++)
		if (dk_busy & (1 << i))
			dk_time[i]++;

	/*
D 130
	 * We adjust the priority of the current process.
	 * The priority of a process gets worse as it accumulates
	 * CPU time.  The cpu usage estimator (p_cpu) is increased here
	 * and the formula for computing priorities (in kern_synch.c)
	 * will compute a different value each time the p_cpu increases
	 * by 4.  The cpu usage estimator ramps up quite quickly when
	 * the process is running (linearly), and decays away
	 * exponentially, at a rate which is proportionally slower
	 * when the system is busy.  The basic principal is that the
	 * system will 90% forget that a process used a lot of CPU
	 * time in 5*loadav seconds.  This causes the system to favor
	 * processes which haven't run much recently, and to
	 * round-robin among other processes.
E 130
I 130
	 * We adjust the priority of the current process.  The priority of
	 * a process gets worse as it accumulates CPU time.  The cpu usage
	 * estimator (p_estcpu) is increased here.  The formula for computing
	 * priorities (in kern_synch.c) will compute a different value each
	 * time p_estcpu increases by 4.  The cpu usage estimator ramps up
	 * quite quickly when the process is running (linearly), and decays
	 * away exponentially, at a rate which is proportionally slower when
	 * the system is busy.  The basic principal is that the system will
	 * 90% forget that the process used a lot of CPU time in 5 * loadav
	 * seconds.  This causes the system to favor processes which haven't
	 * run much recently, and to round-robin among other processes.
E 130
	 */
	if (p != NULL) {
		p->p_cpticks++;
D 130
		if (++p->p_cpu == 0)
			p->p_cpu--;
		if ((p->p_cpu & 3) == 0) {
E 130
I 130
		if (++p->p_estcpu == 0)
			p->p_estcpu--;
		if ((p->p_estcpu & 3) == 0) {
E 130
D 129
			setpri(p);
E 129
I 129
			resetpriority(p);
E 129
D 130
			if (p->p_pri >= PUSER)
				p->p_pri = p->p_usrpri;
E 130
I 130
			if (p->p_priority >= PUSER)
				p->p_priority = p->p_usrpri;
E 130
		}
	}
}

/*
E 118
 * Return information about system clocks.
 */
D 125
/* ARGSUSED */
kinfo_clockrate(op, where, acopysize, arg, aneeded)
	int op;
E 125
I 125
sysctl_clockrate(where, sizep)
E 125
	register char *where;
D 125
	int *acopysize, arg, *aneeded;
E 125
I 125
D 126
	int *sizep;
E 126
I 126
	size_t *sizep;
E 126
E 125
{
D 125
	int buflen, error;
	struct clockinfo clockinfo;
E 125
I 125
	struct clockinfo clkinfo;
E 125

D 125
	*aneeded = sizeof(clockinfo);
	if (where == NULL)
		return (0);
E 125
	/*
D 125
	 * Check for enough buffering.
E 125
I 125
	 * Construct clockinfo structure.
E 125
	 */
D 125
	buflen = *acopysize;
	if (buflen < sizeof(clockinfo)) {
		*acopysize = 0;
		return (0);
	}
	/*
	 * Copyout clockinfo structure.
	 */
	clockinfo.hz = hz;
D 116
	clockinfo.phz = phz;
E 116
I 116
D 118
	clockinfo.stathz = stathz;
E 118
E 116
	clockinfo.tick = tick;
I 117
D 118
#ifdef PROFTIMER
	initprofclock(2);
#else
	profhz = hz;
#endif
E 118
E 117
	clockinfo.profhz = profhz;
I 118
	clockinfo.stathz = stathz ? stathz : hz;
E 118
	if (error = copyout((caddr_t)&clockinfo, where, sizeof(clockinfo)))
		return (error);
	*acopysize = sizeof(clockinfo);
	return (0);
E 125
I 125
	clkinfo.hz = hz;
	clkinfo.tick = tick;
	clkinfo.profhz = profhz;
	clkinfo.stathz = stathz ? stathz : hz;
	return (sysctl_rdstruct(where, sizep, NULL, &clkinfo, sizeof(clkinfo)));
E 125
}
E 113
D 111

D 104
profil()
{
	register struct a {
E 104
I 104
/* ARGSUSED */
profil(p, uap, retval)
	struct proc *p;
	register struct args {
E 104
		short	*bufbase;
		unsigned bufsize;
		unsigned pcoffset;
		unsigned pcscale;
D 104
	} *uap = (struct a *)u.u_ap;
E 104
I 104
	} *uap;
	int *retval;
{
E 104
D 108
	register struct uprof *upp = &u.u_prof;
E 108
I 108
	register struct uprof *upp = &p->p_stats->p_prof;
E 108

	upp->pr_base = uap->bufbase;
	upp->pr_size = uap->bufsize;
	upp->pr_off = uap->pcoffset;
	upp->pr_scale = uap->pcscale;
I 110
#ifdef PROFTIMER
	initprofclock();
#endif
E 110
I 104
D 105
	RETURN (0);
E 105
I 105
	return (0);
E 105
E 104
}
E 111
D 99

I 94
#ifdef COMPAT
E 94
opause()
{

	for (;;)
		sleep((caddr_t)&u, PSLEP);
E 76
}
I 94
#endif
E 99
E 94
E 61
E 58
E 1
