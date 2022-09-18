h04254
s 00001/00001/01192
d D 8.14 95/05/14 00:18:02 mckusick 128 127
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK
e
s 00124/00112/01069
d D 8.13 95/02/14 10:38:08 cgd 127 126
c new argument passing conventions.  minor type size cleanup.
e
s 00004/00006/01177
d D 8.12 95/01/09 18:22:17 cgd 126 125
c return types, 64-bit changes: ioctl cmd -> u_long, casts, etc.
e
s 00001/00001/01182
d D 8.11 94/12/05 18:33:03 mckusick 125 124
c return ENOSYS rather than EINVAL for non-existent system call
e
s 00005/00003/01178
d D 8.10 94/08/22 10:19:57 mckusick 124 123
c use new queue.h data structures
e
s 00001/00001/01180
d D 8.9 94/08/11 00:24:15 mckusick 123 122
c LEASE_CHECK => VOP_LEASE
e
s 00019/00009/01162
d D 8.8 94/05/19 21:31:26 hibler 122 121
c correct management of ps_sig field 
c for tracing, clear pending signal before calling trace_req to avoid deadlock
e
s 00008/00002/01163
d D 8.7 94/04/18 23:00:46 mckusick 121 120
c in sendsig, pass ps_code when signum agrees with ps_sig (from Karels and Hibler)
e
s 00003/00003/01162
d D 8.6 94/03/18 06:31:46 bostic 120 119
c typo
e
s 00005/00000/01160
d D 8.5 94/01/21 17:17:46 bostic 119 118
c add USL's copyright notice
e
s 00068/00069/01092
d D 8.4 93/09/23 15:42:47 bostic 118 117
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/01156
d D 8.3 93/09/21 07:32:24 bostic 117 116
c changes for 4.4BSD-Lite requested by USL
e
s 00140/00140/01021
d D 8.2 93/09/05 09:35:47 bostic 116 115
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/01159
d D 8.1 93/06/10 21:57:50 bostic 115 114
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/01161
d D 7.56 93/04/27 15:07:49 mckusick 114 113
c kinfo_proc.h is gone
e
s 00024/00015/01138
d D 7.55 93/03/02 16:21:51 mckusick 113 112
c set priorities correctly after signals (net2/sys/19)
e
s 00002/00001/01151
d D 7.54 93/02/25 16:29:48 mckusick 112 111
c do not return from sigsuspend prematurely
e
s 00001/00001/01151
d D 7.53 93/02/04 19:21:39 ralph 111 110
c changed the name of exit() to exit1() because gcc2 thinks it
c knows that exit() doesn't return.
e
s 00014/00000/01138
d D 7.52 93/01/14 12:19:08 mckusick 110 109
c add and use killproc when cannot exec a new process
e
s 00019/00019/01119
d D 7.51 92/10/11 10:38:09 bostic 109 108
c make kernel includes standard
e
s 00057/00041/01081
d D 7.50 92/07/10 21:03:41 torek 108 107
c ANSIfy syscall args
e
s 00001/00001/01121
d D 7.49 92/07/07 14:47:05 torek 107 106
c volatile poisoning
e
s 00000/00003/01122
d D 7.48 92/07/03 01:37:20 mckusick 106 105
c delete USES
e
s 00003/00002/01122
d D 7.47 92/06/25 16:16:26 mckusick 105 104
c nothing to do in sigaltstack if no new stack given
e
s 00008/00008/01116
d D 7.46 92/06/23 20:26:40 mckusick 104 103
c merge in changes for Sparc
e
s 00003/00000/01121
d D 7.45 92/05/14 17:33:13 heideman 103 94
c vnode interface conversion
e
s 00008/00000/01121
d R 7.45 92/05/14 15:47:36 heideman 102 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/14 14:52:03 heideman 101 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/14 12:56:26 heideman 100 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/14 11:54:01 heideman 99 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/14 10:34:07 heideman 98 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/13 23:12:59 heideman 97 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/13 18:58:34 heideman 96 94
c vnode interface conversion
e
s 00003/00000/01121
d R 7.45 92/05/13 18:30:45 heideman 95 94
c vnode interface conversion
e
s 00059/00012/01062
d D 7.44 92/04/20 23:31:08 mckusick 94 93
c sigstack becomes COMPAT; sigaltstack becomes real
e
s 00001/00013/01073
d D 7.43 92/03/13 17:07:48 mckusick 93 92
c add cpu_coredump for machine dependent coredump state
e
s 00020/00002/01066
d D 7.42 92/02/05 20:15:48 torek 92 91
c SunOS compatibility
e
s 00002/00004/01066
d D 7.41 92/02/03 23:26:55 heideman 91 90
c no longer pass proc to vn_open (now in ndp)
e
s 00001/00000/01069
d D 7.40 92/02/03 22:03:36 mckusick 90 89
c must init proc pointer
e
s 00001/00000/01068
d D 7.39 92/01/14 11:29:11 mckusick 89 88
c have to check NFS lease when writing core image
e
s 00002/00002/01066
d D 7.38 92/01/07 16:21:57 karels 88 87
c fix up comment
e
s 00000/00001/01068
d D 7.37 91/11/19 23:49:04 torek 87 86
c purge seg.h
e
s 00010/00001/01059
d D 7.36 91/09/06 15:53:29 ralph 86 85
c add printf if signal ignored in system process.
e
s 00004/00004/01056
d D 7.35 91/06/28 10:04:49 karels 85 84
c dump core as core.progname (no pid)
e
s 00001/00001/01059
d D 7.34 91/06/25 12:01:35 karels 84 83
c can't kill zombies even by killpg
e
s 00008/00004/01052
d D 7.33 91/06/21 10:40:58 mckusick 83 82
c use vn_close rather than vrele after vn_open
e
s 00005/00004/01051
d D 7.32 91/06/19 20:47:58 mckusick 82 81
c dump core as core.progname.pid rather than just as core
e
s 00001/00002/01054
d D 7.31 91/05/28 17:38:18 mckusick 81 80
c vn_open now returns locked, so must unlock when done
e
s 00012/00010/01044
d D 7.30 91/05/04 16:31:36 karels 80 79
c u. is gone, pcb is at p_addr; aston => signotify
e
s 00008/00006/01046
d D 7.29 91/04/15 23:47:11 mckusick 79 78
c add proc pointers to appropriate VOP and vnode operations
e
s 00035/00027/01017
d D 7.28 91/03/25 11:39:09 karels 78 77
c (in last delta:) use array of signal property flags rather than
c wired-in signal names; noproc is history; move fatal signal code to sigexit,
c so trap can call directly; rm 386 hacks (save frame type in pcb); fake up
c core dump with kinfo_proc
e
s 00218/00214/00826
d D 7.27 91/03/17 15:41:57 karels 77 76
c more-or-less working with new proc & user structs
e
s 00012/00000/01028
d D 7.26 91/01/18 17:37:33 william 76 75
c 386 trap and syscall frame difference passed thru to sendsig()
e
s 00005/00021/01023
d D 7.25 90/12/05 17:30:39 mckusick 75 74
c update for new VM
e
s 00010/00000/01034
d D 7.24 90/12/01 14:22:38 karels 74 73
c tty stop signals shouldn't stop sleeping procs in orphaned pgrps
e
s 00001/00011/01033
d D 7.23 90/06/28 21:21:23 bostic 73 72
c new copyright notice
e
s 00026/00026/01018
d D 7.22 90/06/28 17:10:53 karels 72 71
c RETURN => return, remove syscontext.h
e
s 00007/00009/01037
d D 7.21 90/06/25 10:54:23 karels 71 70
c expunge p_cursig, using p_xstat instead for stop signals;
c expunge u_code
e
s 00009/00005/01037
d D 7.20 90/06/21 14:48:39 mckusick 70 69
c new system call convention
e
s 00007/00005/01035
d D 7.19 90/06/06 00:04:24 mckusick 69 67
c update to new system call convention; expunge more u.u_procp
e
s 00004/00001/01039
d R 7.19 90/06/05 22:02:06 mckusick 68 67
c update to new system call convention; expunge more u.u_error
e
s 00097/00070/00943
d D 7.18 90/06/05 21:00:15 karels 67 66
c new syscall convention, avoid u.u_procp (almost)
e
s 00009/00009/01004
d D 7.17 90/05/29 15:28:38 karels 66 65
c check for tty stop signals on orphaned pgrp in issig rather than psignal
c (action could change while pending)
e
s 00007/00004/01006
d D 7.16 90/05/17 18:02:08 marc 65 63
c add flag to pgsignal to restrict to procs having a ctty
e
s 00007/00004/01006
d R 7.16 90/05/17 15:43:14 marc 64 63
c pgsignal has flag to limit to members having a ctty
e
s 00013/00008/00997
d D 7.15 90/05/15 19:09:04 mckusick 63 62
c update for hp300 support from Utah
e
s 00000/00001/01005
d D 7.14 90/05/04 14:12:41 mckusick 62 61
c delete unneeded headers
e
s 00001/00001/01005
d D 7.13 90/05/03 18:44:58 mckusick 61 60
c vattr_null => VATTR_NULL
e
s 00096/00074/00910
d D 7.12 90/04/05 14:58:43 marc 60 59
c tsleep, unwind, ktrace, ISSIG->CURSIG, expunge cursig
e
s 00427/00282/00557
d D 7.11 89/11/11 10:31:24 karels 59 58
c POSIX changes
e
s 00001/00001/00838
d D 7.10 89/07/03 18:27:43 mckusick 58 57
c use VOP_ACCESS directly
e
s 00010/00011/00829
d D 7.9 89/07/03 11:34:25 mckusick 57 56
c must ensure that the vnode is locked while operating on it
e
s 00008/00009/00832
d D 7.8 89/05/09 17:02:27 mckusick 56 55
c merge in vnodes
e
s 00000/00002/00841
d D 7.7 89/05/05 00:06:39 mckusick 55 54
c delete unneeded include of dir.h
e
s 00000/00004/00843
d D 7.6 89/05/01 22:49:22 mckusick 54 52
i 53
c integrate back branch -r7.3.1.1
e
s 00058/00043/00771
d D 7.3.1.1 89/05/01 22:47:36 mckusick 53 50
c merge in vnode changes
e
s 00005/00005/00823
d D 7.5 89/04/25 14:42:28 mckusick 52 51
c ../machine => machine
e
s 00066/00052/00762
d D 7.4 88/10/18 15:14:40 marc 51 50
c posix style job control - new process groups
e
s 00008/00000/00806
d D 7.3 86/12/14 14:52:28 sam 50 49
c add missing MMAP code from merge
e
s 00001/00001/00805
d D 7.2 86/11/03 11:59:50 karels 49 48
c merge in tahoe support
e
s 00001/00001/00805
d D 7.1 86/06/05 00:04:14 mckusick 48 47
c 4.3BSD release version
e
s 00006/00006/00800
d D 6.21 86/02/23 23:09:06 karels 47 46
c lint
e
s 00004/00006/00802
d D 6.20 86/02/20 15:33:23 karels 46 45
c use sigmask uniformly
e
s 00001/00001/00807
d D 6.19 85/09/18 09:32:47 karels 45 44
c lint
e
s 00001/00001/00807
d D 6.18 85/08/23 15:48:51 karels 44 43
c back to EPERM if killpg (not -1) can't do it
e
s 00007/00001/00801
d D 6.17 85/06/08 14:37:38 mckusick 43 42
c Add copyright
e
s 00002/00000/00800
d D 6.16 85/05/22 20:06:14 mckusick 42 41
c only dump core if user has read permission on the text
e
s 00005/00005/00795
d D 6.15 85/05/22 14:34:08 mckusick 41 40
c make signal semantics more like system V;
c non-super user can do `kill -1 1' to kill all processes run by them,
c return ESRCH instaed of EINVAL for `kill 0 1' when not in a process group
e
s 00000/00001/00800
d D 6.14 85/03/19 20:48:50 mckusick 40 39
c eliminate extraneous include of conf.h
e
s 00049/00034/00752
d D 6.13 85/03/13 20:06:01 mckusick 39 38
c rewritten kill code from sun!shannon
e
s 00005/00007/00781
d D 6.12 85/03/13 19:40:56 karels 38 37
c give SIGCHLD on stop even if traced (once only)
e
s 00012/00002/00776
d D 6.11 85/03/12 13:52:55 mckusick 37 36
c add another bit to sigvec() flags to disable system call restart
e
s 00000/00026/00778
d D 6.10 85/03/12 13:03:21 mckusick 36 35
c eliminate signal() system call interface
e
s 00002/00000/00802
d D 6.9 84/12/31 12:36:16 bloom 35 34
c Added SIGWINCH for windows
e
s 00001/00007/00801
d D 6.8 84/11/20 11:13:46 karels 34 33
c remove unused code
e
s 00039/00042/00769
d D 6.7 84/09/04 14:23:00 bloom 33 32
c mask macro moved to header file and name changed to sigmask
e
s 00017/00017/00794
d D 6.6 84/08/29 20:20:09 bloom 32 31
c Change to includes.  no more ../h
e
s 00029/00000/00782
d D 6.5 84/08/24 16:55:29 mckusick 31 30
c add `signal' as a system call
e
s 00006/00005/00776
d D 6.4 84/07/08 16:13:44 mckusick 30 29
c rework `namei' interface to eliminate global variables
e
s 00002/00004/00779
d D 6.3 84/05/22 11:45:02 karels 29 28
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00003/00001/00780
d D 6.2 83/09/08 10:48:45 mckusick 28 27
c If a process exists but has a different uid than the killer it should return
c EPERM rather than ESRCH. (Bill Shanon)
e
s 00000/00000/00781
d D 6.1 83/08/20 15:38:37 sam 27 26
c 4.2 distribution
e
s 00017/00008/00764
d D 5.24 83/08/20 15:38:13 sam 26 24
c from shannon; can't allow masked signals to be presented; 
c also, beware of ptrace taking child signal, then changing it to something
e
s 00000/00000/00772
d R 6.1 83/07/29 06:33:48 sam 25 24
c 4.2 distribution
e
s 00000/00001/00772
d D 5.23 83/06/24 00:26:21 sam 24 23
c crud from previous interface not deleted
e
s 00004/00001/00769
d D 5.22 83/06/21 20:35:40 sam 23 22
c change NOCOMPAT to COMPAT and make it work
e
s 00006/00005/00764
d D 5.21 83/06/10 21:23:27 sam 22 21
c beware of masked signals with STRC
e
s 00076/00033/00693
d D 5.20 83/06/09 21:59:32 sam 21 20
c "final" sigvec interface?
e
s 00144/00051/00582
d D 5.19 83/06/02 15:56:56 sam 20 18
c new signals
e
s 00000/00000/00633
d R 5.19 83/05/31 01:03:42 sam 19 18
c collect all the compatibility stuff in single files
e
s 00005/00003/00628
d D 5.18 83/05/30 19:28:11 sam 18 17
c kill with signal 0 allows for error checking without sending a signal 
c from shannon@sun.UUCP
e
s 00006/00101/00625
d D 5.17 83/05/27 12:47:09 sam 17 16
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00002/00002/00724
d D 5.16 83/05/21 15:34:33 sam 16 15
c disallow core files on setgid programs; make core files mode 644
e
s 00040/00046/00686
d D 5.15 82/12/28 19:50:39 sam 15 14
c kludge killpg so csh runs again
e
s 00001/00001/00731
d D 5.14 82/12/19 17:51:41 sam 14 13
c checking old value instead of new on signal call when 
c new action is to ignore (from Mike Karels)
e
s 00004/00003/00728
d D 5.13 82/12/17 11:44:41 sam 13 12
c sun merge
e
s 00003/00002/00728
d D 5.12 82/11/13 22:50:19 sam 12 11
c merge of 4.1b and 4.1c
e
s 00009/00005/00721
d D 5.11 82/10/31 14:25:58 root 11 10
c fixes from 68k
e
s 00002/00000/00724
d D 5.10 82/10/21 20:57:07 root 10 9
c lint
e
s 00007/00007/00717
d D 5.9 82/10/17 23:03:31 root 9 8
c lint
e
s 00001/00001/00723
d D 5.8 82/10/10 15:08:01 root 8 7
c split header files over to vax directories
e
s 00001/00030/00723
d D 5.7 82/09/08 08:04:26 root 7 6
c move oalarm, opause to here
e
s 00006/00006/00747
d D 5.6 82/09/06 22:49:21 root 6 5
c 
e
s 00021/00011/00732
d D 5.5 82/09/04 09:12:27 root 5 4
c new timer stuff, to be filled in kill and killpg
e
s 00023/00020/00720
d D 5.4 82/08/22 20:33:33 root 4 3
c use rdwri()
e
s 00001/00001/00739
d D 5.3 82/08/10 17:50:59 sam 3 2
c new itrunc
e
s 00100/00259/00640
d D 5.2 82/07/24 18:10:14 root 2 1
c merge with calder
e
s 00899/00000/00000
d D 5.1 82/07/15 20:12:50 root 1 0
c date and time created 82/07/15 20:12:50 by root
e
u
U
f b 
t
T
I 1
D 43
/*	%M%	%I%	%E%	*/
E 43
I 43
/*
D 48
 * Copyright (c) 1982 Regents of the University of California.
E 48
I 48
D 53
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 48
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 53
I 53
D 77
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 77
I 77
D 115
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 77
 * All rights reserved.
E 115
I 115
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 119
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 119
E 115
E 53
 *
I 53
D 73
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
E 73
I 73
 * %sccs.include.redist.c%
E 73
 *
E 53
 *	%W% (Berkeley) %G%
 */
E 43

I 77
#define	SIGPROP		/* include signal properties table */
E 77
I 13
D 52
D 53
#include "../machine/reg.h"
#include "../machine/pte.h"
#include "../machine/psl.h"
I 49
#include "../machine/mtpr.h"
E 53
I 53
D 54
#include "machine/reg.h"
#include "machine/pte.h"
#include "machine/psl.h"
#include "machine/mtpr.h"
E 54
E 53
E 49

E 52
E 13
D 32
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
D 13
#include "../h/reg.h"
E 13
#include "../h/inode.h"
#include "../h/proc.h"
D 5
#include "../h/clock.h"
E 5
D 8
#include "../h/mtpr.h"
E 8
#include "../h/timeb.h"
#include "../h/times.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/mount.h"
#include "../h/text.h"
#include "../h/seg.h"
D 13
#include "../h/pte.h"
#include "../h/psl.h"
E 13
#include "../h/vm.h"
D 5
#include "../h/vlimit.h"
E 5
#include "../h/acct.h"
I 4
#include "../h/uio.h"
I 7
#include "../h/kernel.h"
E 32
I 32
D 109
#include "param.h"
D 77
#include "systm.h"
D 55
#include "dir.h"
I 53
#include "ucred.h"
E 55
E 53
D 59
#include "user.h"
E 59
I 59
D 72
#include "syscontext.h"	/* XXX */
E 72
I 72
#include "user.h"
E 77
I 77
D 78
/*#include "signalvar.h" */
#include "user.h"		/* XXX */
E 78
I 78
#include "signalvar.h"
#include "resourcevar.h"
I 79
#include "namei.h"
E 79
E 78
E 77
E 72
E 59
D 53
#include "inode.h"
E 53
I 53
#include "vnode.h"
E 53
#include "proc.h"
I 77
D 78
#include "kinfo_proc.h"
E 78
#include "systm.h"
E 77
#include "timeb.h"
#include "times.h"
D 40
#include "conf.h"
E 40
#include "buf.h"
D 62
#include "mount.h"
E 62
D 75
#include "text.h"
E 75
D 87
#include "seg.h"
E 87
D 75
#include "vm.h"
E 75
#include "acct.h"
D 77
#include "uio.h"
E 77
I 53
#include "file.h"
E 53
#include "kernel.h"
I 59
#include "wait.h"
I 60
#include "ktrace.h"
E 109
I 109
#include <sys/param.h>
#include <sys/signalvar.h>
#include <sys/resourcevar.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/buf.h>
#include <sys/acct.h>
#include <sys/file.h>
#include <sys/kernel.h>
#include <sys/wait.h>
#include <sys/ktrace.h>
I 110
#include <sys/syslog.h>
I 116
#include <sys/stat.h>
E 116
E 110
E 109
E 60
E 59
I 52

I 127
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 127
I 80
D 109
#include "machine/cpu.h"
E 109
I 109
#include <machine/cpu.h>
E 109

E 80
D 77
#include "machine/reg.h"
D 75
#include "machine/pte.h"
E 75
#include "machine/psl.h"
#include "machine/mtpr.h"
E 77
I 75
D 78
#include "../vm/vm_param.h"
E 78
I 78
D 109
#include "vm/vm.h"
#include "kinfo_proc.h"
#include "user.h"		/* for coredump */
E 109
I 109
#include <vm/vm.h>
D 114
#include <sys/kinfo_proc.h>
E 114
#include <sys/user.h>		/* for coredump */
E 109
E 78
E 75
E 52
E 32
I 12
D 30
#include "../h/nami.h"
E 30
E 12
E 7
E 4

I 127
void stop __P((struct proc *p));

E 127
I 21
D 33
#define	mask(s)	(1 << ((s)-1))
#define	cantmask	(mask(SIGKILL)|mask(SIGCONT)|mask(SIGSTOP))
E 33
I 33
D 59
#define	cantmask	(sigmask(SIGKILL)|sigmask(SIGCONT)|sigmask(SIGSTOP))
E 59
I 46
D 66
#define	stopsigmask	(sigmask(SIGSTOP)|sigmask(SIGTSTP)| \
			sigmask(SIGTTIN)|sigmask(SIGTTOU))
E 66
I 66
D 77
#define	ttystopsigmask	(sigmask(SIGTSTP)|sigmask(SIGTTIN)|sigmask(SIGTTOU))
#define	stopsigmask	(sigmask(SIGSTOP)|ttystopsigmask)
E 66
I 59
#define defaultignmask	(sigmask(SIGCONT)|sigmask(SIGIO)|sigmask(SIGURG)| \
			sigmask(SIGCHLD)|sigmask(SIGWINCH)|sigmask(SIGINFO))
E 59
E 46
E 33

E 77
I 31
/*
D 36
 * Quick interface to signal handler.
 */
signal()
{
	register struct a {
		int	signo;
		int	(*handler)();	/* signal handler */
	} *uap = (struct a  *)u.u_ap;
	struct sigvec vec;
	register struct sigvec *sv = &vec;
	register int sig;

	sig = uap->signo;
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP ||
	    (sig == SIGCONT && uap->handler == SIG_IGN)) {
		u.u_error = EINVAL;
		return;
	}
	sv->sv_handler = uap->handler;
	sv->sv_mask = 0;
	sv->sv_onstack = 0;
	u.u_r.r_val1 = (int)u.u_signal[sig];
	setsigvec(sig, sv);
}

/*
E 36
D 59
 * Generalized interface signal handler.
E 59
I 59
D 67
 * Can the current process (u.u_procp) send the specified signal
 * to the specified process?
E 67
I 67
D 77
 * Can process p send the signal signo to process q?
E 77
I 77
D 116
 * Can process p, with pcred pc, send the signal signo to process q?
E 116
I 116
 * Can process p, with pcred pc, send the signal signum to process q?
E 116
E 77
E 67
E 59
 */
E 31
E 21
D 2
ssig()
E 2
I 2
D 20
/* KILL CODE SHOULDNT KNOW ABOUT PROCESS INTERNALS !?! */

E 20
D 59
sigvec()
E 59
I 59
D 67
#define CANSIGNAL(p, signo) \
	(u.u_uid == 0 || \
	    u.u_uid == (p)->p_uid || u.u_uid == (p)->p_ruid || \
	    u.u_procp->p_ruid == (p)->p_uid || \
	    u.u_procp->p_ruid == (p)->p_ruid || \
	    ((signo) == SIGCONT && (p)->p_session == u.u_procp->p_session))
E 67
I 67
D 77
#define CANSIGNAL(p, q, signo) \
	((p)->p_uid == 0 || \
	    (p)->p_ruid == (q)->p_ruid || (p)->p_uid == (q)->p_ruid || \
	    (p)->p_ruid == (q)->p_uid || (p)->p_uid == (q)->p_uid || \
E 77
I 77
D 116
#define CANSIGNAL(p, pc, q, signo) \
E 116
I 116
#define CANSIGNAL(p, pc, q, signum) \
E 116
	((pc)->pc_ucred->cr_uid == 0 || \
	    (pc)->p_ruid == (q)->p_cred->p_ruid || \
	    (pc)->pc_ucred->cr_uid == (q)->p_cred->p_ruid || \
	    (pc)->p_ruid == (q)->p_ucred->cr_uid || \
	    (pc)->pc_ucred->cr_uid == (q)->p_ucred->cr_uid || \
E 77
D 116
	    ((signo) == SIGCONT && (q)->p_session == (p)->p_session))
E 116
I 116
	    ((signum) == SIGCONT && (q)->p_session == (p)->p_session))
E 116
E 67

I 108
D 127
struct sigaction_args {
D 116
	int	signo;
E 116
I 116
	int	signum;
E 116
	struct	sigaction *nsa;
	struct	sigaction *osa;
};
E 127
E 108
D 67
sigaction()
E 59
E 2
{
I 20
D 21
	struct a {
E 21
I 21
	register struct a {
E 67
I 67
/* ARGSUSED */
I 127
int
E 127
sigaction(p, uap, retval)
	struct proc *p;
D 108
	register struct args {
E 67
E 21
		int	signo;
D 21
		int	(*sighandler)();
		int	sigmask;
E 21
I 21
D 59
		struct	sigvec *nsv;
		struct	sigvec *osv;
E 59
I 59
		struct	sigaction *nsa;
		struct	sigaction *osa;
E 59
E 21
D 67
	} *uap = (struct a  *)u.u_ap;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	register struct sigaction_args *uap;
E 108
	int *retval;
E 127
I 127
	register struct sigaction_args /* {
		syscallarg(int) signum;
		syscallarg(struct sigaction *) nsa;
		syscallarg(struct sigaction *) osa;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
I 21
D 59
	struct sigvec vec;
	register struct sigvec *sv;
E 59
I 59
	struct sigaction vec;
	register struct sigaction *sa;
I 77
	register struct sigacts *ps = p->p_sigacts;
E 77
E 59
E 21
D 116
	register int sig;
E 116
I 116
	register int signum;
E 116
I 37
D 59
	int bit;
E 59
I 59
	int bit, error;
E 59
E 37
E 20
D 2
	register int (*f)();
	struct a {
		int	signo;
		int	(*fun)();
	} *uap;
	register struct proc *p = u.u_procp;
	register a;
	long sigmask;
E 2

I 20
D 116
	sig = uap->signo;
D 21
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP ||
	    (sig == SIGCONT && uap->sighandler == SIG_IGN)) {
E 21
I 21
D 59
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP) {
E 21
		u.u_error = EINVAL;
		return;
	}
D 21
	setsignal(sig, uap->sighandler, uap->sigmask);
E 21
I 21
	sv = &vec;
	if (uap->osv) {
		sv->sv_handler = u.u_signal[sig];
		sv->sv_mask = u.u_sigmask[sig];
E 59
I 59
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP)
E 116
I 116
D 127
	signum = uap->signum;
E 127
I 127
	signum = SCARG(uap, signum);
E 127
	if (signum <= 0 || signum >= NSIG ||
	    signum == SIGKILL || signum == SIGSTOP)
E 116
D 72
		RETURN (EINVAL);
E 72
I 72
		return (EINVAL);
E 72
	sa = &vec;
D 127
	if (uap->osa) {
E 127
I 127
	if (SCARG(uap, osa)) {
E 127
D 77
		sa->sa_handler = u.u_signal[sig];
		sa->sa_mask = u.u_sigmask[sig];
E 77
I 77
D 116
		sa->sa_handler = ps->ps_sigact[sig];
		sa->sa_mask = ps->ps_catchmask[sig];
E 77
E 59
D 33
		sv->sv_onstack = (u.u_sigonstack & mask(sig)) != 0;
E 33
I 33
D 37
		sv->sv_onstack = (u.u_sigonstack & sigmask(sig)) != 0;
E 37
I 37
		bit = sigmask(sig);
E 116
I 116
		sa->sa_handler = ps->ps_sigact[signum];
		sa->sa_mask = ps->ps_catchmask[signum];
		bit = sigmask(signum);
E 116
D 59
		sv->sv_flags = 0;
E 59
I 59
		sa->sa_flags = 0;
E 59
D 77
		if ((u.u_sigonstack & bit) != 0)
E 77
I 77
		if ((ps->ps_sigonstack & bit) != 0)
E 77
D 59
			sv->sv_flags |= SV_ONSTACK;
		if ((u.u_sigintr & bit) != 0)
			sv->sv_flags |= SV_INTERRUPT;
E 37
E 33
		u.u_error =
		    copyout((caddr_t)sv, (caddr_t)uap->osv, sizeof (vec));
		if (u.u_error)
			return;
E 59
I 59
			sa->sa_flags |= SA_ONSTACK;
D 77
		if ((u.u_sigintr & bit) == 0)
E 77
I 77
		if ((ps->ps_sigintr & bit) == 0)
E 77
			sa->sa_flags |= SA_RESTART;
D 67
		if (u.u_procp->p_flag & SNOCLDSTOP)
E 67
I 67
D 118
		if (p->p_flag & SNOCLDSTOP)
E 118
I 118
		if (p->p_flag & P_NOCLDSTOP)
E 118
E 67
			sa->sa_flags |= SA_NOCLDSTOP;
D 127
		if (error = copyout((caddr_t)sa, (caddr_t)uap->osa,
E 127
I 127
		if (error = copyout((caddr_t)sa, (caddr_t)SCARG(uap, osa),
E 127
		    sizeof (vec)))
D 72
			RETURN (error);
E 72
I 72
			return (error);
E 72
E 59
	}
D 59
	if (uap->nsv) {
		u.u_error =
		    copyin((caddr_t)uap->nsv, (caddr_t)sv, sizeof (vec));
		if (u.u_error)
			return;
		if (sig == SIGCONT && sv->sv_handler == SIG_IGN) {
			u.u_error = EINVAL;
			return;
		}
		setsigvec(sig, sv);
E 59
I 59
D 127
	if (uap->nsa) {
		if (error = copyin((caddr_t)uap->nsa, (caddr_t)sa,
E 127
I 127
	if (SCARG(uap, nsa)) {
		if (error = copyin((caddr_t)SCARG(uap, nsa), (caddr_t)sa,
E 127
		    sizeof (vec)))
D 72
			RETURN (error);
E 72
I 72
			return (error);
E 72
D 67
		setsigvec(sig, sa);
E 67
I 67
D 116
		setsigvec(p, sig, sa);
E 116
I 116
		setsigvec(p, signum, sa);
E 116
E 67
E 59
	}
I 59
D 72
	RETURN (0);
E 72
I 72
	return (0);
E 72
E 59
E 21
E 20
D 2
	uap = (struct a *)u.u_ap;
	a = uap->signo & SIGNUMMASK;
	f = uap->fun;
	if (a<=0 || a>=NSIG || a==SIGKILL || a==SIGSTOP ||
	    a==SIGCONT && (f == SIG_IGN || f == SIG_HOLD)) {
		u.u_error = EINVAL;
		return;
	}
	if ((uap->signo &~ SIGNUMMASK) || (f != SIG_DFL && f != SIG_IGN &&
	    SIGISDEFER(f)))
		u.u_procp->p_flag |= SNUSIG;
	/* 
	 * Don't clobber registers if we are to simulate
	 * a ret+rti.
	 */
	if ((uap->signo&SIGDORTI) == 0)
		u.u_r.r_val1 = (int)u.u_signal[a];
	/*
	 * Change setting atomically.
	 */
	(void) spl6();
	sigmask = 1L << (a-1);
	if (u.u_signal[a] == SIG_IGN)
		p->p_sig &= ~sigmask;		/* never to be seen again */
	u.u_signal[a] = f;
	if (f != SIG_DFL && f != SIG_IGN && f != SIG_HOLD)
		f = SIG_CATCH;
	if ((int)f & 1)
		p->p_siga0 |= sigmask;
	else
		p->p_siga0 &= ~sigmask;
	if ((int)f & 2)
		p->p_siga1 |= sigmask;
	else
		p->p_siga1 &= ~sigmask;
	(void) spl0();
	/*
	 * Now handle options.
	 */
	if (uap->signo & SIGDOPAUSE) {
		/*
		 * Simulate a PDP11 style wait instrution which
		 * atomically lowers priority, enables interrupts
		 * and hangs.
		 */
		pause();
		/*NOTREACHED*/
	}
	if (uap->signo & SIGDORTI)
		u.u_eosys = SIMULATERTI;
E 2
}

I 127
void
E 127
I 20
D 21
setsignal(sig, action, sigmask)
	int sig, (*action)(), sigmask;
E 21
I 21
D 59
setsigvec(sig, sv)
E 59
I 59
D 67
setsigvec(sig, sa)
E 67
I 67
D 116
setsigvec(p, sig, sa)
E 116
I 116
setsigvec(p, signum, sa)
E 116
	register struct proc *p;
E 67
E 59
D 116
	int sig;
E 116
I 116
	int signum;
E 116
D 59
	register struct sigvec *sv;
E 59
I 59
	register struct sigaction *sa;
E 59
E 21
{
I 77
	register struct sigacts *ps = p->p_sigacts;
E 77
D 67
	register struct proc *p;
E 67
D 21
	register int mask;
E 21
I 21
	register int bit;
E 21

D 21
	u.u_r.r_val1 = (int)u.u_signal[sig];
	mask = 1 << (sig - 1);
E 21
I 21
D 33
	bit = mask(sig);
E 33
I 33
D 116
	bit = sigmask(sig);
E 116
I 116
	bit = sigmask(signum);
E 116
E 33
E 21
D 67
	p = u.u_procp;
E 67
	/*
	 * Change setting atomically.
	 */
D 33
	(void) spl6();
E 33
I 33
	(void) splhigh();
E 33
D 21
	u.u_signal[sig] = action;
	u.u_sigmask[sig] = sigmask;
	if (action == SIG_IGN) {
		p->p_sig &= ~mask;		/* never to be seen again */
		p->p_sigignore |= mask;
		p->p_sigcatch &= ~mask;
E 21
I 21
D 59
	u.u_signal[sig] = sv->sv_handler;
	u.u_sigmask[sig] = sv->sv_mask &~ cantmask;
D 37
	if (sv->sv_onstack)
E 37
I 37
	if (sv->sv_flags & SV_INTERRUPT)
E 59
I 59
D 77
	u.u_signal[sig] = sa->sa_handler;
	u.u_sigmask[sig] = sa->sa_mask &~ sigcantmask;
E 77
I 77
D 116
	ps->ps_sigact[sig] = sa->sa_handler;
	ps->ps_catchmask[sig] = sa->sa_mask &~ sigcantmask;
E 116
I 116
	ps->ps_sigact[signum] = sa->sa_handler;
	ps->ps_catchmask[signum] = sa->sa_mask &~ sigcantmask;
E 116
E 77
	if ((sa->sa_flags & SA_RESTART) == 0)
E 59
D 77
		u.u_sigintr |= bit;
E 77
I 77
		ps->ps_sigintr |= bit;
E 77
	else
D 77
		u.u_sigintr &= ~bit;
E 77
I 77
		ps->ps_sigintr &= ~bit;
E 77
D 59
	if (sv->sv_flags & SV_ONSTACK)
E 59
I 59
	if (sa->sa_flags & SA_ONSTACK)
E 59
E 37
D 77
		u.u_sigonstack |= bit;
E 77
I 77
		ps->ps_sigonstack |= bit;
E 77
	else
D 77
		u.u_sigonstack &= ~bit;
E 77
I 77
		ps->ps_sigonstack &= ~bit;
I 92
#ifdef COMPAT_SUNOS
	if (sa->sa_flags & SA_USERTRAMP)
		ps->ps_usertramp |= bit;
	else
		ps->ps_usertramp &= ~bit;
#endif
E 92
E 77
D 59
	if (sv->sv_handler == SIG_IGN) {
E 59
I 59
D 116
	if (sig == SIGCHLD) {
E 116
I 116
	if (signum == SIGCHLD) {
E 116
		if (sa->sa_flags & SA_NOCLDSTOP)
D 118
			p->p_flag |= SNOCLDSTOP;
E 118
I 118
			p->p_flag |= P_NOCLDSTOP;
E 118
		else
D 118
			p->p_flag &= ~SNOCLDSTOP;
E 118
I 118
			p->p_flag &= ~P_NOCLDSTOP;
E 118
	}
	/*
	 * Set bit in p_sigignore for signals that are set to SIG_IGN,
	 * and for signals set to SIG_DFL where the default is to ignore.
	 * However, don't put SIGCONT in p_sigignore,
	 * as we have to restart the process.
	 */
	if (sa->sa_handler == SIG_IGN ||
D 77
	   (bit & defaultignmask && sa->sa_handler == SIG_DFL)) {
E 77
I 77
D 116
	    (sigprop[sig] & SA_IGNORE && sa->sa_handler == SIG_DFL)) {
E 116
I 116
	    (sigprop[signum] & SA_IGNORE && sa->sa_handler == SIG_DFL)) {
E 116
E 77
E 59
D 118
		p->p_sig &= ~bit;		/* never to be seen again */
E 118
I 118
		p->p_siglist &= ~bit;		/* never to be seen again */
E 118
D 59
		p->p_sigignore |= bit;
E 59
I 59
D 116
		if (sig != SIGCONT)
E 116
I 116
		if (signum != SIGCONT)
E 116
			p->p_sigignore |= bit;	/* easier in psignal */
E 59
		p->p_sigcatch &= ~bit;
E 21
	} else {
D 21
		p->p_sigignore &= ~mask;
		if (action == SIG_DFL)
			p->p_sigcatch &= ~mask;
E 21
I 21
		p->p_sigignore &= ~bit;
D 59
		if (sv->sv_handler == SIG_DFL)
E 59
I 59
		if (sa->sa_handler == SIG_DFL)
E 59
			p->p_sigcatch &= ~bit;
E 21
		else
D 21
			p->p_sigcatch |= mask;
E 21
I 21
			p->p_sigcatch |= bit;
E 21
	}
	(void) spl0();
}

E 20
D 2
kill()
E 2
I 2
D 59
sigblock()
E 59
I 59
/*
 * Initialize signal state for process 0;
 * set to ignore signals that are ignored by default.
 */
I 77
void
E 77
siginit(p)
	struct proc *p;
E 59
E 2
{
I 77
	register int i;
E 77
I 59

D 77
	p->p_sigignore = defaultignmask &~ sigmask(SIGCONT);
E 77
I 77
	for (i = 0; i < NSIG; i++)
		if (sigprop[i] & SA_IGNORE && i != SIGCONT)
			p->p_sigignore |= sigmask(i);
E 77
}

/*
 * Reset signals for an exec of the specified process.
 */
I 77
void
E 77
execsigs(p)
	register struct proc *p;
{
I 77
	register struct sigacts *ps = p->p_sigacts;
E 77
	register int nc, mask;

	/*
	 * Reset caught signals.  Held signals remain held
	 * through p_sigmask (unless they were caught,
	 * and are now ignored by default).
	 */
	while (p->p_sigcatch) {
		nc = ffs((long)p->p_sigcatch);
		mask = sigmask(nc);
		p->p_sigcatch &= ~mask;
D 77
		if (mask & defaultignmask) {
E 77
I 77
		if (sigprop[nc] & SA_IGNORE) {
E 77
			if (nc != SIGCONT)
				p->p_sigignore |= mask;
D 118
			p->p_sig &= ~mask;
E 118
I 118
			p->p_siglist &= ~mask;
E 118
		}
D 77
		u.u_signal[nc] = SIG_DFL;
E 77
I 77
		ps->ps_sigact[nc] = SIG_DFL;
E 77
	}
	/*
	 * Reset stack state to the user stack.
	 * Clear set of signals caught on the signal stack.
	 */
D 77
	u.u_onstack = 0;
	u.u_sigsp = 0;
	u.u_sigonstack = 0;
E 77
I 77
D 94
	ps->ps_onstack = 0;
	ps->ps_sigsp = 0;
	ps->ps_sigonstack = 0;
E 94
I 94
	ps->ps_sigstk.ss_flags = SA_DISABLE;
	ps->ps_sigstk.ss_size = 0;
	ps->ps_sigstk.ss_base = 0;
	ps->ps_flags = 0;
E 94
E 77
}

/*
 * Manipulate signal mask.
 * Note that we receive new mask, not pointer,
 * and return old mask as return value;
 * the library stub does the rest.
 */
I 108
D 127
struct sigprocmask_args {
	int	how;
	sigset_t mask;
};
E 127
I 127
int
E 127
E 108
D 67
sigprocmask()
{
E 59
I 20
	struct a {
E 67
I 67
sigprocmask(p, uap, retval)
	register struct proc *p;
D 108
	struct args {
E 67
I 59
		int	how;
		sigset_t mask;
D 67
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	struct sigprocmask_args *uap;
E 108
	int *retval;
E 127
I 127
	struct sigprocmask_args /* {
		syscallarg(int) how;
		syscallarg(sigset_t) mask;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
	int error = 0;

D 67
	u.u_r.r_val1 = p->p_sigmask;
E 67
I 67
	*retval = p->p_sigmask;
E 67
	(void) splhigh();

D 127
	switch (uap->how) {
E 127
I 127
	switch (SCARG(uap, how)) {
E 127
	case SIG_BLOCK:
D 127
		p->p_sigmask |= uap->mask &~ sigcantmask;
E 127
I 127
		p->p_sigmask |= SCARG(uap, mask) &~ sigcantmask;
E 127
		break;

	case SIG_UNBLOCK:
D 127
		p->p_sigmask &= ~uap->mask;
E 127
I 127
		p->p_sigmask &= ~SCARG(uap, mask);
E 127
		break;

	case SIG_SETMASK:
D 127
		p->p_sigmask = uap->mask &~ sigcantmask;
E 127
I 127
		p->p_sigmask = SCARG(uap, mask) &~ sigcantmask;
E 127
		break;
	
	default:
		error = EINVAL;
		break;
	}
	(void) spl0();
D 72
	RETURN (error);
E 72
I 72
	return (error);
E 72
}

I 108
D 127
struct sigpending_args {
	int	dummy;
};
E 127
E 108
D 67
sigpending()
E 67
I 67
/* ARGSUSED */
I 127
int
E 127
sigpending(p, uap, retval)
	struct proc *p;
D 108
	void *uap;
E 108
I 108
D 127
	struct sigpending_args *uap;
E 108
	int *retval;
E 127
I 127
	void *uap;
	register_t *retval;
E 127
E 67
{

D 67
	u.u_r.r_val1 = u.u_procp->p_sig;
E 67
I 67
D 118
	*retval = p->p_sig;
E 118
I 118
	*retval = p->p_siglist;
E 118
E 67
D 72
	RETURN (0);
E 72
I 72
	return (0);
E 72
}

D 92
#ifdef COMPAT_43
E 92
I 92
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 92
/*
 * Generalized interface signal handler, 4.3-compatible.
 */
I 108
D 127
struct osigvec_args {
D 116
	int	signo;
E 116
I 116
	int	signum;
E 116
	struct	sigvec *nsv;
	struct	sigvec *osv;
};
E 127
E 108
D 67
osigvec()
{
	register struct a {
E 67
I 67
/* ARGSUSED */
D 127
osigvec(p, uap, retval)
E 127
I 127
int
compat_43_sigvec(p, uap, retval)
E 127
	struct proc *p;
D 108
	register struct args {
E 67
		int	signo;
		struct	sigvec *nsv;
		struct	sigvec *osv;
D 67
	} *uap = (struct a  *)u.u_ap;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	register struct osigvec_args *uap;
E 108
	int *retval;
E 127
I 127
	register struct compat_43_sigvec_args /* {
		syscallarg(int) signum;
		syscallarg(struct sigvec *) nsv;
		syscallarg(struct sigvec *) osv;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
	struct sigvec vec;
I 77
	register struct sigacts *ps = p->p_sigacts;
E 77
	register struct sigvec *sv;
D 116
	register int sig;
E 116
I 116
	register int signum;
E 116
	int bit, error;

D 116
	sig = uap->signo;
	if (sig <= 0 || sig >= NSIG || sig == SIGKILL || sig == SIGSTOP)
E 116
I 116
D 127
	signum = uap->signum;
E 127
I 127
	signum = SCARG(uap, signum);
E 127
	if (signum <= 0 || signum >= NSIG ||
	    signum == SIGKILL || signum == SIGSTOP)
E 116
D 72
		RETURN (EINVAL);
E 72
I 72
		return (EINVAL);
E 72
	sv = &vec;
D 127
	if (uap->osv) {
E 127
I 127
	if (SCARG(uap, osv)) {
E 127
D 77
		*(sig_t *)&sv->sv_handler = u.u_signal[sig];
		sv->sv_mask = u.u_sigmask[sig];
E 77
I 77
D 116
		*(sig_t *)&sv->sv_handler = ps->ps_sigact[sig];
		sv->sv_mask = ps->ps_catchmask[sig];
E 77
		bit = sigmask(sig);
E 116
I 116
		*(sig_t *)&sv->sv_handler = ps->ps_sigact[signum];
		sv->sv_mask = ps->ps_catchmask[signum];
		bit = sigmask(signum);
E 116
		sv->sv_flags = 0;
D 77
		if ((u.u_sigonstack & bit) != 0)
E 77
I 77
		if ((ps->ps_sigonstack & bit) != 0)
E 77
			sv->sv_flags |= SV_ONSTACK;
D 77
		if ((u.u_sigintr & bit) != 0)
E 77
I 77
		if ((ps->ps_sigintr & bit) != 0)
E 77
			sv->sv_flags |= SV_INTERRUPT;
I 92
#ifndef COMPAT_SUNOS
E 92
D 67
		if (u.u_procp->p_flag & SNOCLDSTOP)
E 67
I 67
D 118
		if (p->p_flag & SNOCLDSTOP)
E 118
I 118
		if (p->p_flag & P_NOCLDSTOP)
E 118
E 67
			sv->sv_flags |= SA_NOCLDSTOP;
I 92
#endif
E 92
D 127
		if (error = copyout((caddr_t)sv, (caddr_t)uap->osv,
E 127
I 127
		if (error = copyout((caddr_t)sv, (caddr_t)SCARG(uap, osv),
E 127
		    sizeof (vec)))
D 72
			RETURN (error);
E 72
I 72
			return (error);
E 72
	}
D 127
	if (uap->nsv) {
		if (error = copyin((caddr_t)uap->nsv, (caddr_t)sv,
E 127
I 127
	if (SCARG(uap, nsv)) {
		if (error = copyin((caddr_t)SCARG(uap, nsv), (caddr_t)sv,
E 127
		    sizeof (vec)))
D 72
			RETURN (error);
E 72
I 72
			return (error);
I 92
#ifdef COMPAT_SUNOS
		/*
D 104
		 * SunOS uses this bit (SA_NOCLDSTOP) as SV_RESETHAND,
		 * `reset to SIG_DFL on delivery'. We have no such
		 * option now or ever!
E 104
I 104
		 * SunOS uses this bit (4, aka SA_DISABLE) as SV_RESETHAND,
		 * `reset to SIG_DFL on delivery'. We have no such option
		 * now or ever!
E 104
		 */
D 104
		if (sv->sv_flags & SA_NOCLDSTOP)
E 104
I 104
		if (sv->sv_flags & SA_DISABLE)
E 104
			return (EINVAL);
		sv->sv_flags |= SA_USERTRAMP;
#endif
E 92
E 72
		sv->sv_flags ^= SA_RESTART;	/* opposite of SV_INTERRUPT */
D 63
		setsigvec(sig, sv);
E 63
I 63
D 67
		setsigvec(sig, (struct sigaction *)sv);
E 67
I 67
D 116
		setsigvec(p, sig, (struct sigaction *)sv);
E 116
I 116
		setsigvec(p, signum, (struct sigaction *)sv);
E 116
E 67
E 63
	}
D 72
	RETURN (0);
E 72
I 72
	return (0);
E 72
}

I 108
D 127
struct osigblock_args {
	int	mask;
};
E 108
D 67
osigblock()
{
	struct a {
E 67
I 67
osigblock(p, uap, retval)
E 127
I 127
int
compat_43_sigblock(p, uap, retval)
E 127
	register struct proc *p;
D 108
	struct args {
E 67
E 59
D 21
		int	mask;
E 21
I 21
D 33
		int	sigmask;
E 33
I 33
		int	mask;
E 33
E 21
D 67
	} *uap = (struct a *)u.u_ap;
D 21
	struct proc *p = u.u_procp;
E 21
I 21
	register struct proc *p = u.u_procp;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	struct osigblock_args *uap;
E 108
	int *retval;
E 127
I 127
	struct compat_43_sigblock_args /* {
		syscallarg(int) mask;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
E 21
E 20
I 2

I 20
D 33
	(void) spl6();
E 33
I 33
	(void) splhigh();
E 33
D 67
	u.u_r.r_val1 = p->p_sigmask;
E 67
I 67
	*retval = p->p_sigmask;
E 67
D 21
	p->p_sigmask |= uap->mask;
E 21
I 21
D 33
	p->p_sigmask |= uap->sigmask &~ cantmask;
E 33
I 33
D 59
	p->p_sigmask |= uap->mask &~ cantmask;
E 59
I 59
D 127
	p->p_sigmask |= uap->mask &~ sigcantmask;
E 127
I 127
	p->p_sigmask |= SCARG(uap, mask) &~ sigcantmask;
E 127
E 59
E 33
E 21
	(void) spl0();
I 59
D 72
	RETURN (0);
E 72
I 72
	return (0);
E 72
E 59
E 20
}

I 108
D 127
struct osigsetmask_args {
	int	mask;
};
E 108
D 59
sigsetmask()
E 59
I 59
D 67
osigsetmask()
E 59
{
I 20
	struct a {
E 67
I 67
osigsetmask(p, uap, retval)
E 127
I 127
int
compat_43_sigsetmask(p, uap, retval)
E 127
	struct proc *p;
D 108
	struct args {
E 67
D 21
		int	mask;
E 21
I 21
D 33
		int	sigmask;
E 33
I 33
		int	mask;
E 33
E 21
D 67
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	struct osigsetmask_args *uap;
E 108
	int *retval;
E 127
I 127
	struct compat_43_sigsetmask_args /* {
		syscallarg(int) mask;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
E 20

I 20
D 33
	(void) spl6();
E 33
I 33
	(void) splhigh();
E 33
D 67
	u.u_r.r_val1 = p->p_sigmask;
E 67
I 67
	*retval = p->p_sigmask;
E 67
D 21
	p->p_sigmask = uap->mask;
E 21
I 21
D 33
	p->p_sigmask = uap->sigmask &~ cantmask;
E 33
I 33
D 59
	p->p_sigmask = uap->mask &~ cantmask;
E 59
I 59
D 127
	p->p_sigmask = uap->mask &~ sigcantmask;
E 127
I 127
	p->p_sigmask = SCARG(uap, mask) &~ sigcantmask;
E 127
E 59
E 33
E 21
	(void) spl0();
I 59
D 72
	RETURN (0);
E 72
I 72
	return (0);
E 72
E 59
E 20
}
I 59
D 104
#endif
E 104
I 104
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 104
E 59

D 59
sigpause()
E 59
I 59
/*
 * Suspend process until signal, providing mask to be set
 * in the meantime.  Note nonstandard calling convention:
 * libc stub passes mask, not pointer, to save a copyin.
 */
I 108
D 127
struct sigsuspend_args {
	sigset_t mask;
};
E 127
E 108
D 67
sigsuspend()
E 59
{
I 20
	struct a {
E 67
I 67
/* ARGSUSED */
I 127
int
E 127
sigsuspend(p, uap, retval)
	register struct proc *p;
D 108
	struct args {
E 67
D 21
		int	mask;
E 21
I 21
D 33
		int	sigmask;
E 33
I 33
D 59
		int	mask;
E 59
I 59
		sigset_t mask;
E 59
E 33
E 21
D 67
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	struct sigsuspend_args *uap;
E 108
	int *retval;
E 127
I 127
	struct sigsuspend_args /* {
		syscallarg(int) mask;
	} */ *uap;
	register_t *retval;
E 127
{
I 77
	register struct sigacts *ps = p->p_sigacts;
E 77
E 67
E 20

I 20
	/*
	 * When returning from sigpause, we want
	 * the old mask to be restored after the
	 * signal handler has finished.  Thus, we
D 88
	 * save it here and mark the proc structure
D 77
	 * to indicate this (should be in u.).
E 77
I 77
	 * to indicate this (should be in sigacts).
E 88
I 88
	 * save it here and mark the sigacts structure
	 * to indicate this.
E 88
E 77
	 */
D 77
	u.u_oldmask = p->p_sigmask;
	p->p_flag |= SOMASK;
E 77
I 77
	ps->ps_oldmask = p->p_sigmask;
D 94
	ps->ps_flags |= SA_OLDMASK;
E 94
I 94
	ps->ps_flags |= SAS_OLDMASK;
E 94
E 77
D 21
	p->p_sigmask = uap->mask;
E 21
I 21
D 33
	p->p_sigmask = uap->sigmask &~ cantmask;
E 33
I 33
D 59
	p->p_sigmask = uap->mask &~ cantmask;
E 59
I 59
D 127
	p->p_sigmask = uap->mask &~ sigcantmask;
E 127
I 127
	p->p_sigmask = SCARG(uap, mask) &~ sigcantmask;
E 127
E 59
E 33
E 21
D 60
	for (;;)
		sleep((caddr_t)&u, PSLEP);
	/*NOTREACHED*/
E 60
I 60
D 77
	(void) tsleep((caddr_t)&u, PPAUSE | PCATCH, "pause", 0);
E 77
I 77
D 112
	(void) tsleep((caddr_t) ps, PPAUSE|PCATCH, "pause", 0);
E 112
I 112
	while (tsleep((caddr_t) ps, PPAUSE|PCATCH, "pause", 0) == 0)
		/* void */;
E 112
E 77
	/* always return EINTR rather than ERESTART... */
D 72
	RETURN (EINTR);
E 72
I 72
	return (EINTR);
E 72
E 60
E 20
}
I 21
D 59
#undef cantmask
E 59
D 33
#undef mask
E 33
E 21

I 94
D 104
#ifdef COMPAT_43
E 104
I 104
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
I 108
D 127
struct osigstack_args {
	struct	sigstack *nss;
	struct	sigstack *oss;
};
E 127
E 108
E 104
E 94
D 67
sigstack()
{
I 20
D 21
	struct a {
E 21
I 21
	register struct a {
E 67
I 67
/* ARGSUSED */
D 94
sigstack(p, uap, retval)
E 94
I 94
D 127
osigstack(p, uap, retval)
E 127
I 127
int
compat_43_sigstack(p, uap, retval)
E 127
E 94
	struct proc *p;
D 108
	register struct args {
E 67
E 21
D 24
		caddr_t	asp;
E 24
D 21
		int	onsigstack;
E 21
I 21
		struct	sigstack *nss;
		struct	sigstack *oss;
E 21
D 67
	} *uap = (struct a *)u.u_ap;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	register struct osigstack_args *uap;
E 108
	int *retval;
E 127
I 127
	register struct compat_43_sigstack_args /* {
		syscallarg(struct sigstack *) nss;
		syscallarg(struct sigstack *) oss;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
I 21
	struct sigstack ss;
I 94
	struct sigacts *psp;
E 94
I 59
	int error = 0;
E 59
E 21
E 20

I 20
D 21
	u.u_sigstack = uap->asp;
	u.u_onsigstack = uap->onsigstack;
E 21
I 21
D 59
	if (uap->oss) {
		u.u_error = copyout((caddr_t)&u.u_sigstack, (caddr_t)uap->oss, 
		    sizeof (struct sigstack));
		if (u.u_error)
			return;
	}
	if (uap->nss) {
		u.u_error =
		    copyin((caddr_t)uap->nss, (caddr_t)&ss, sizeof (ss));
		if (u.u_error == 0)
			u.u_sigstack = ss;
	}
E 59
I 59
D 77
	if (uap->oss && (error = copyout((caddr_t)&u.u_sigstack,
E 77
I 77
D 94
	if (uap->oss && (error = copyout((caddr_t)&p->p_sigacts->ps_sigstack,
E 77
	    (caddr_t)uap->oss, sizeof (struct sigstack))))
E 94
I 94
	psp = p->p_sigacts;
	ss.ss_sp = psp->ps_sigstk.ss_base;
	ss.ss_onstack = psp->ps_sigstk.ss_flags & SA_ONSTACK;
D 127
	if (uap->oss && (error = copyout((caddr_t)&ss, (caddr_t)uap->oss,
	    sizeof (struct sigstack))))
E 127
I 127
	if (SCARG(uap, oss) && (error = copyout((caddr_t)&ss,
	    (caddr_t)SCARG(uap, oss), sizeof (struct sigstack))))
E 127
E 94
D 72
		RETURN (error);
E 72
I 72
		return (error);
E 72
D 127
	if (uap->nss && (error = copyin((caddr_t)uap->nss, (caddr_t)&ss,
D 94
	    sizeof (ss))) == 0)
D 77
		u.u_sigstack = ss;
E 77
I 77
		p->p_sigacts->ps_sigstack = ss;
E 94
I 94
	    sizeof (ss))) == 0) {
E 127
I 127
	if (SCARG(uap, nss) && (error = copyin((caddr_t)SCARG(uap, nss),
	    (caddr_t)&ss, sizeof (ss))) == 0) {
E 127
		psp->ps_sigstk.ss_base = ss.ss_sp;
		psp->ps_sigstk.ss_size = 0;
		psp->ps_sigstk.ss_flags |= ss.ss_onstack & SA_ONSTACK;
		psp->ps_flags |= SAS_ALTSTACK;
	}
E 94
E 77
D 72
	RETURN (error);
E 72
I 72
	return (error);
E 72
E 59
E 21
E 20
}
I 94
D 104
#endif /* COMPAT_43 */
E 104
I 104
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 104
E 94

I 108
D 127
struct sigaltstack_args {
	struct	sigaltstack *nss;
	struct	sigaltstack *oss;
};
E 127
E 108
I 23
D 39
/* KILL SHOULD BE UPDATED */

E 39
E 23
I 10
D 20
#ifdef notdef
E 20
E 10
I 5
D 67
kill()
{
I 20
	register struct a {
E 67
I 67
/* ARGSUSED */
I 127
int
E 127
I 94
sigaltstack(p, uap, retval)
	struct proc *p;
D 108
	register struct args {
		struct	sigaltstack *nss;
		struct	sigaltstack *oss;
	} *uap;
E 108
I 108
D 127
	register struct sigaltstack_args *uap;
E 108
	int *retval;
E 127
I 127
	register struct sigaltstack_args /* {
		syscallarg(struct sigaltstack *) nss;
		syscallarg(struct sigaltstack *) oss;
	} */ *uap;
	register_t *retval;
E 127
{
	struct sigacts *psp;
	struct sigaltstack ss;
	int error;

	psp = p->p_sigacts;
	if ((psp->ps_flags & SAS_ALTSTACK) == 0)
		psp->ps_sigstk.ss_flags |= SA_DISABLE;
D 127
	if (uap->oss && (error = copyout((caddr_t)&psp->ps_sigstk,
	    (caddr_t)uap->oss, sizeof (struct sigaltstack))))
E 127
I 127
	if (SCARG(uap, oss) && (error = copyout((caddr_t)&psp->ps_sigstk,
	    (caddr_t)SCARG(uap, oss), sizeof (struct sigaltstack))))
E 127
		return (error);
D 105
	if (uap->nss && (error = copyin((caddr_t)uap->nss, (caddr_t)&ss,
	    sizeof (ss))))
E 105
I 105
D 127
	if (uap->nss == 0)
E 127
I 127
	if (SCARG(uap, nss) == 0)
E 127
		return (0);
D 127
	if (error = copyin((caddr_t)uap->nss, (caddr_t)&ss, sizeof (ss)))
E 127
I 127
	if (error = copyin((caddr_t)SCARG(uap, nss), (caddr_t)&ss,
	    sizeof (ss)))
E 127
E 105
		return (error);
	if (ss.ss_flags & SA_DISABLE) {
		if (psp->ps_sigstk.ss_flags & SA_ONSTACK)
			return (EINVAL);
		psp->ps_flags &= ~SAS_ALTSTACK;
		psp->ps_sigstk.ss_flags = ss.ss_flags;
		return (0);
	}
	if (ss.ss_size < MINSIGSTKSZ)
		return (ENOMEM);
	psp->ps_flags |= SAS_ALTSTACK;
	psp->ps_sigstk= ss;
	return (0);
}

I 108
D 127
struct kill_args {
	int	pid;
D 116
	int	signo;
E 116
I 116
	int	signum;
E 116
};
E 127
E 108
/* ARGSUSED */
I 127
int
E 127
E 94
kill(cp, uap, retval)
	register struct proc *cp;
D 108
	register struct args {
E 67
		int	pid;
		int	signo;
D 67
	} *uap = (struct a *)u.u_ap;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	register struct kill_args *uap;
E 108
	int *retval;
E 127
I 127
	register struct kill_args /* {
		syscallarg(int) pid;
		syscallarg(int) signum;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
I 39
	register struct proc *p;
I 77
	register struct pcred *pc = cp->p_cred;
E 77
E 39
E 20

I 20
D 23
	u.u_error = kill1(0, uap->signo, uap->pid);
E 23
I 23
D 39
	u.u_error = kill1(uap->signo < 0,
		uap->signo < 0 ? -uap->signo : uap->signo, uap->pid);
E 39
I 39
D 59
	if (uap->signo < 0 || uap->signo > NSIG) {
		u.u_error = EINVAL;
		return;
	}
E 59
I 59
D 116
	if ((unsigned) uap->signo >= NSIG)
E 116
I 116
D 127
	if ((u_int)uap->signum >= NSIG)
E 127
I 127
	if ((u_int)SCARG(uap, signum) >= NSIG)
E 127
E 116
D 72
		RETURN (EINVAL);
E 72
I 72
		return (EINVAL);
E 72
E 59
D 127
	if (uap->pid > 0) {
E 127
I 127
	if (SCARG(uap, pid) > 0) {
E 127
		/* kill single process */
D 116
		p = pfind(uap->pid);
D 59
		if (p == 0) {
			u.u_error = ESRCH;
			return;
		}
		if (u.u_uid && u.u_uid != p->p_uid)
			u.u_error = EPERM;
		else if (uap->signo)
E 59
I 59
		if (p == 0)
E 116
I 116
D 127
		if ((p = pfind(uap->pid)) == NULL)
E 127
I 127
		if ((p = pfind(SCARG(uap, pid))) == NULL)
E 127
E 116
D 72
			RETURN (ESRCH);
E 72
I 72
			return (ESRCH);
E 72
D 67
		if (!CANSIGNAL(p, uap->signo))
E 67
I 67
D 77
		if (!CANSIGNAL(cp, p, uap->signo))
E 77
I 77
D 116
		if (!CANSIGNAL(cp, pc, p, uap->signo))
E 116
I 116
D 127
		if (!CANSIGNAL(cp, pc, p, uap->signum))
E 127
I 127
		if (!CANSIGNAL(cp, pc, p, SCARG(uap, signum)))
E 127
E 116
E 77
E 67
D 72
			RETURN (EPERM);
E 72
I 72
			return (EPERM);
E 72
D 116
		if (uap->signo)
E 59
			psignal(p, uap->signo);
E 116
I 116
D 127
		if (uap->signum)
			psignal(p, uap->signum);
E 127
I 127
		if (SCARG(uap, signum))
			psignal(p, SCARG(uap, signum));
E 127
E 116
D 59
		return;
E 59
I 59
D 72
		RETURN (0);
E 72
I 72
		return (0);
E 72
E 59
	}
D 127
	switch (uap->pid) {
E 127
I 127
	switch (SCARG(uap, pid)) {
E 127
	case -1:		/* broadcast signal */
D 41
		if (suser())
			u.u_error = killpg1(uap->signo, 0, 1);
E 41
I 41
D 59
		u.u_error = killpg1(uap->signo, 0, 1);
E 41
		break;
E 59
I 59
D 67
		RETURN (killpg1(uap->signo, 0, 1));
E 67
I 67
D 72
		RETURN (killpg1(cp, uap->signo, 0, 1));
E 72
I 72
D 116
		return (killpg1(cp, uap->signo, 0, 1));
E 116
I 116
D 127
		return (killpg1(cp, uap->signum, 0, 1));
E 127
I 127
		return (killpg1(cp, SCARG(uap, signum), 0, 1));
E 127
E 116
E 72
E 67
E 59
	case 0:			/* signal own process group */
D 59
		u.u_error = killpg1(uap->signo, 0, 0);
		break;
E 59
I 59
D 67
		RETURN (killpg1(uap->signo, 0, 0));
E 67
I 67
D 72
		RETURN (killpg1(cp, uap->signo, 0, 0));
E 72
I 72
D 116
		return (killpg1(cp, uap->signo, 0, 0));
E 116
I 116
D 127
		return (killpg1(cp, uap->signum, 0, 0));
E 127
I 127
		return (killpg1(cp, SCARG(uap, signum), 0, 0));
E 127
E 116
E 72
E 67
E 59
	default:		/* negative explicit process group */
D 59
		u.u_error = killpg1(uap->signo, -uap->pid, 0);
		break;
E 59
I 59
D 67
		RETURN (killpg1(uap->signo, -uap->pid, 0));
E 67
I 67
D 72
		RETURN (killpg1(cp, uap->signo, -uap->pid, 0));
E 72
I 72
D 116
		return (killpg1(cp, uap->signo, -uap->pid, 0));
E 116
I 116
D 127
		return (killpg1(cp, uap->signum, -uap->pid, 0));
E 127
I 127
		return (killpg1(cp, SCARG(uap, signum), -SCARG(uap, pid), 0));
E 127
E 116
E 72
E 67
E 59
	}
D 59
	return;
E 59
I 59
	/* NOTREACHED */
E 59
E 39
E 23
E 20
}
I 10
D 20
#endif
E 20
E 10

I 15
D 17
/* TEMPORARY */
E 17
E 15
D 59
killpg()
E 59
I 59
D 92
#ifdef COMPAT_43
E 92
I 92
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
I 108
D 127
struct okillpg_args {
	int	pgid;
D 116
	int	signo;
E 116
I 116
	int	signum;
E 116
};
E 127
E 108
E 92
D 67
okillpg()
E 59
{
I 15
	register struct a {
E 67
I 67
/* ARGSUSED */
D 127
okillpg(p, uap, retval)
E 127
I 127
int
compat_43_killpg(p, uap, retval)
E 127
	struct proc *p;
D 108
	register struct args {
E 67
D 51
		int	pgrp;
E 51
I 51
		int	pgid;
E 51
		int	signo;
D 67
	} *uap = (struct a *)u.u_ap;
E 67
I 67
	} *uap;
E 108
I 108
D 127
	register struct okillpg_args *uap;
E 108
	int *retval;
E 127
I 127
	register struct compat_43_killpg_args /* {
		syscallarg(int) pgid;
		syscallarg(int) signum;
	} */ *uap;
	register_t *retval;
E 127
{
E 67
E 15

I 15
D 17
	u.u_error = okill1(1, uap->signo, uap->pgrp);
E 17
I 17
D 39
	u.u_error = kill1(1, uap->signo, uap->pgrp);
E 39
I 39
D 59
	if (uap->signo < 0 || uap->signo > NSIG) {
		u.u_error = EINVAL;
		return;
	}
D 51
	u.u_error = killpg1(uap->signo, uap->pgrp, 0);
E 51
I 51
	u.u_error = killpg1(uap->signo, uap->pgid, 0);
E 59
I 59
D 116
	if ((unsigned) uap->signo >= NSIG)
E 116
I 116
D 127
	if ((u_int)uap->signum >= NSIG)
E 127
I 127
	if ((u_int)SCARG(uap, signum) >= NSIG)
E 127
E 116
D 72
		RETURN (EINVAL);
D 67
	RETURN (killpg1(uap->signo, uap->pgid, 0));
E 67
I 67
	RETURN (killpg1(p, uap->signo, uap->pgid, 0));
E 72
I 72
		return (EINVAL);
D 116
	return (killpg1(p, uap->signo, uap->pgid, 0));
E 116
I 116
D 127
	return (killpg1(p, uap->signum, uap->pgid, 0));
E 127
I 127
	return (killpg1(p, SCARG(uap, signum), SCARG(uap, pgid), 0));
E 127
E 116
E 72
E 67
E 59
E 51
E 39
E 17
E 15
}
I 59
D 104
#endif
E 104
I 104
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 104
E 59

I 20
D 59
/* KILL CODE SHOULDNT KNOW ABOUT PROCESS INTERNALS !?! */

E 59
E 20
E 5
D 17
/* BEGIN DEFUNCT */
okill()
{
E 2
D 15
	register struct proc *p;
	register a, sig;
E 15
	register struct a {
		int	pid;
		int	signo;
D 15
	} *uap;
	int f, priv;
E 15
I 15
	} *uap = (struct a *)u.u_ap;
E 15

D 15
	uap = (struct a *)u.u_ap;
	f = 0;
	a = uap->pid;
	priv = 0;
	sig = uap->signo;
	if (sig < 0)
		/*
		 * A negative signal means send to process group.
		 */
		uap->signo = -uap->signo;
	if (uap->signo == 0 || uap->signo > NSIG) {
		u.u_error = EINVAL;
		return;
E 15
I 15
	u.u_error = okill1(uap->signo < 0,
		uap->signo < 0 ? -uap->signo : uap->signo, uap->pid);
}

okill1(ispgrp, signo, who)
E 17
I 17
D 39
kill1(ispgrp, signo, who)
E 17
	int ispgrp, signo, who;
E 39
I 39
D 51
killpg1(signo, pgrp, all)
	int signo, pgrp, all;
E 51
I 51
D 67
killpg1(signo, pgid, all)
E 67
I 67
/*
 * Common code for kill process group/broadcast kill.
 * cp is calling process.
 */
I 127
int
E 127
D 116
killpg1(cp, signo, pgid, all)
E 116
I 116
killpg1(cp, signum, pgid, all)
E 116
	register struct proc *cp;
E 67
D 116
	int signo, pgid, all;
E 116
I 116
	int signum, pgid, all;
E 116
E 51
E 39
{
	register struct proc *p;
I 77
	register struct pcred *pc = cp->p_cred;
E 77
D 39
	int f, priv = 0;
E 39
I 39
D 51
	int f, error = 0;
E 51
I 51
	struct pgrp *pgrp;
D 59
	int f = 0, error = 0;
E 51
E 39

E 59
I 59
D 70
	int f = 0, error = ESRCH;
E 70
I 70
D 77
	int f = 0;
E 77
I 77
	int nfound = 0;
E 77
E 70
E 59
D 18
	if (signo == 0 || signo > NSIG)
E 18
I 18
D 39
	if (signo < 0 || signo > NSIG)
E 18
		return (EINVAL);
	if (who > 0 && !ispgrp) {
		p = pfind(who);
D 28
		if (p == 0 || u.u_uid && u.u_uid != p->p_uid)
E 28
I 28
		if (p == 0)
E 28
			return (ESRCH);
I 28
		if (u.u_uid && u.u_uid != p->p_uid)
			return (EPERM);
E 28
D 18
		psignal(p, signo);
E 18
I 18
		if (signo)
			psignal(p, signo);
E 18
		return (0);
E 15
	}
D 15
	if (a > 0 && sig > 0) {
		p = pfind(a);
		if (p == 0 || u.u_uid && u.u_uid != p->p_uid) {
			u.u_error = ESRCH;
			return;
		}
		psignal(p, uap->signo);
		return;
	}
	if (a==-1 && u.u_uid==0) {
		priv++;
		a = 0;
		sig = -1;		/* like sending to pgrp */
	} else if (a==0) {
E 15
I 15
	if (who == -1 && u.u_uid == 0)
		priv++, who = 0, ispgrp = 1;	/* like sending to pgrp */
	else if (who == 0) {
E 39
I 39
D 51
	if (!all && pgrp == 0) {
E 39
E 15
		/*
		 * Zero process id means send to my process group.
E 51
I 51
	
	if (all)	
		/* 
		 * broadcast 
E 51
		 */
D 15
		sig = -1;
		a = u.u_procp->p_pgrp;
		if (a == 0) {
			u.u_error = EINVAL;
			return;
		}
E 15
I 15
D 39
		ispgrp = 1;
		who = u.u_procp->p_pgrp;
		if (who == 0)
E 39
I 39
D 51
		pgrp = u.u_procp->p_pgrp;
		if (pgrp == 0)
E 39
D 41
			return (EINVAL);
E 41
I 41
			return (ESRCH);
E 41
E 15
	}
D 15
	for(p = proc; p < procNPROC; p++) {
E 15
I 15
D 29
	for (f = 0, p = proc; p < procNPROC; p++) {
E 15
		if (p->p_stat == NULL)
			continue;
E 29
I 29
	for (f = 0, p = allproc; p != NULL; p = p->p_nxt) {
E 29
D 15
		if (sig > 0) {
			if (p->p_pid != a)
E 15
I 15
D 39
		if (!ispgrp) {
			if (p->p_pid != who)
E 15
				continue;
D 15
		} else if (p->p_pgrp!=a && priv==0 || p->p_ppid==0 ||
		    (p->p_flag&SSYS) || (priv && p==u.u_procp))
E 15
I 15
		} else if (p->p_pgrp != who && priv == 0 || p->p_ppid == 0 ||
		    (p->p_flag&SSYS) || (priv && p == u.u_procp))
E 39
I 39
		if ((p->p_pgrp != pgrp && !all) || p->p_ppid == 0 ||
		    (p->p_flag&SSYS) || (all && p == u.u_procp))
E 39
E 15
			continue;
I 39
D 41
		f++;
E 41
E 39
		if (u.u_uid != 0 && u.u_uid != p->p_uid &&
D 15
		    (uap->signo != SIGCONT || !inferior(p)))
E 15
I 15
D 39
		    (signo != SIGCONT || !inferior(p)))
E 39
I 39
		    (signo != SIGCONT || !inferior(p))) {
D 41
			error = EPERM;
E 41
I 41
			if (!all)
E 51
I 51
D 107
		for (p = allproc; p != NULL; p = p->p_nxt) {
E 107
I 107
D 118
		for (p = (struct proc *)allproc; p != NULL; p = p->p_nxt) {
E 107
D 77
			if (p->p_ppid == 0 || p->p_flag&SSYS || 
D 59
			    p == u.u_procp ||
			   (u.u_uid && u.u_uid != p->p_uid && 
			   !(signo == SIGCONT && inferior(p))))
E 59
I 59
D 67
			    p == u.u_procp || !CANSIGNAL(p, signo))
E 67
I 67
			    p == u.u_procp || !CANSIGNAL(cp, p, signo))
E 77
I 77
D 113
			if (p->p_pid <= 1 || p->p_flag&SSYS || 
E 113
I 113
			if (p->p_pid <= 1 || p->p_flag & SSYS || 
E 118
I 118
D 124
		for (p = (struct proc *)allproc; p != NULL; p = p->p_next) {
E 124
I 124
		for (p = allproc.lh_first; p != 0; p = p->p_list.le_next) {
E 124
			if (p->p_pid <= 1 || p->p_flag & P_SYSTEM || 
E 118
E 113
D 116
			    p == cp || !CANSIGNAL(cp, pc, p, signo))
E 116
I 116
			    p == cp || !CANSIGNAL(cp, pc, p, signum))
E 116
E 77
E 67
E 59
				continue;
D 77
			f++;
E 77
I 77
			nfound++;
E 77
D 116
			if (signo)
				psignal(p, signo);
E 116
I 116
			if (signum)
				psignal(p, signum);
E 116
		}
	else {
		if (pgid == 0)		
			/* 
			 * zero pgid means send to my process group.
			 */
D 77
			pgrp = u.u_procp->p_pgrp;
E 77
I 77
			pgrp = cp->p_pgrp;
E 77
		else {
			pgrp = pgfind(pgid);
			if (pgrp == NULL)
D 59
				return(ESRCH);
E 59
I 59
				return (ESRCH);
E 59
		}
D 59
		if (!(pgrp->pg_jobc) && 
		     (signo==SIGTTIN || signo==SIGTTOU || signo==SIGTSTP))
			return(EPERM);
E 59
D 124
		for (p = pgrp->pg_mem; p != NULL; p = p->p_pgrpnxt) {
E 124
I 124
		for (p = pgrp->pg_members.lh_first; p != 0;
		     p = p->p_pglist.le_next) {
E 124
D 59
			if (p->p_ppid == 0 || p->p_flag&SSYS)
E 59
I 59
D 77
			if (p->p_ppid == 0 || p->p_flag&SSYS ||
D 67
			    !CANSIGNAL(p, signo))
E 67
I 67
			    !CANSIGNAL(cp, p, signo))
E 77
I 77
D 113
			if (p->p_pid <= 1 || p->p_flag&SSYS ||
E 113
I 113
D 118
			if (p->p_pid <= 1 || p->p_flag & SSYS ||
E 118
I 118
			if (p->p_pid <= 1 || p->p_flag & P_SYSTEM ||
E 118
E 113
D 84
			    !CANSIGNAL(cp, pc, p, signo))
E 84
I 84
D 116
			    p->p_stat == SZOMB || !CANSIGNAL(cp, pc, p, signo))
E 116
I 116
			    p->p_stat == SZOMB ||
			    !CANSIGNAL(cp, pc, p, signum))
E 116
E 84
E 77
E 67
E 59
				continue;
D 59
			if (u.u_uid && u.u_uid != p->p_uid && 
			   !(signo == SIGCONT && inferior(p))) {
E 51
				error = EPERM;
E 41
E 39
E 15
D 51
			continue;
E 51
I 51
				continue;
			}
E 59
D 77
			f++;
E 77
I 77
			nfound++;
E 77
D 116
			if (signo)
				psignal(p, signo);
E 116
I 116
			if (signum)
				psignal(p, signum);
E 116
E 51
D 39
		f++;
E 39
I 39
		}
I 41
D 51
		f++;
E 41
E 39
D 15
		psignal(p, uap->signo);
E 15
I 15
D 18
		psignal(p, signo);
E 18
I 18
		if (signo)
			psignal(p, signo);
E 51
E 18
E 15
	}
D 15
	if (f == 0)
		u.u_error = ESRCH;
E 15
I 15
D 17
	return (f == 0? ESRCH : 0);
E 17
I 17
D 39
	return (f == 0 ? ESRCH : 0);
E 39
I 39
D 44
	return (f == 0 ? ESRCH : error);
E 44
I 44
D 59
	return (error ? error : (f == 0 ? ESRCH : 0));
E 59
I 59
D 70
	return (f ? 0 : error);
E 70
I 70
D 77
	return (f ? 0 : ESRCH);
E 77
I 77
	return (nfound ? 0 : ESRCH);
E 77
E 70
E 59
E 44
E 39
E 17
E 15
}

D 2
/*
 * Priority for tracing
 */
#define	IPCPRI	PZERO
E 2
I 2
D 17
ossig()
{
	register int (*f)();
	struct a {
		int	signo;
		int	(*fun)();
	} *uap;
	register struct proc *p = u.u_procp;
	register a;
	long sigmask;
E 2

D 2
/*
 * Tracing variables.
 * Used to pass trace command from
 * parent to child being traced.
 * This data base cannot be
 * shared and is locked
 * per user.
 */
struct {
	int	ip_lock;
	int	ip_req;
	int	*ip_addr;
	int	ip_data;
} ipc;
E 2
I 2
	uap = (struct a *)u.u_ap;
	a = uap->signo & SIGNUMMASK;
	f = uap->fun;
	if (a<=0 || a>=NSIG || a==SIGKILL || a==SIGSTOP ||
	    a==SIGCONT && (f == SIG_IGN || f == SIG_HOLD)) {
		u.u_error = EINVAL;
		return;
	}
	if ((uap->signo &~ SIGNUMMASK) || (f != SIG_DFL && f != SIG_IGN &&
	    SIGISDEFER(f)))
		u.u_procp->p_flag |= SNUSIG;
	/* 
	 * Don't clobber registers if we are to simulate
	 * a ret+rti.
	 */
	if ((uap->signo&SIGDORTI) == 0)
		u.u_r.r_val1 = (int)u.u_signal[a];
	/*
	 * Change setting atomically.
	 */
	(void) spl6();
	sigmask = 1L << (a-1);
D 14
	if (u.u_signal[a] == SIG_IGN)
E 14
I 14
	if (f == SIG_IGN)
E 14
		p->p_sig &= ~sigmask;		/* never to be seen again */
	u.u_signal[a] = f;
	if (f != SIG_DFL && f != SIG_IGN && f != SIG_HOLD)
		f = SIG_CATCH;
	if ((int)f & 1)
		p->p_siga0 |= sigmask;
	else
		p->p_siga0 &= ~sigmask;
	if ((int)f & 2)
		p->p_siga1 |= sigmask;
	else
		p->p_siga1 &= ~sigmask;
	(void) spl0();
	/*
	 * Now handle options.
	 */
	if (uap->signo & SIGDOPAUSE) {
		/*
		 * Simulate a PDP11 style wait instrution which
		 * atomically lowers priority, enables interrupts
		 * and hangs.
		 */
		opause();
		/*NOTREACHED*/
	}
	if (uap->signo & SIGDORTI)
		u.u_eosys = SIMULATERTI;
}
E 2

E 17
D 60
/*
E 60
I 60
D 67
/* XXX - to be removed, as soon as sockets are changed to operate on pgrps
E 67
I 67
/*
E 67
E 60
D 116
 * Send the specified signal to
D 51
 * all processes with 'pgrp' as
E 51
I 51
 * all processes with 'pgid' as
E 51
 * process group.
E 116
I 116
 * Send a signal to a process group.
E 116
D 20
 * Called by tty.c for quits and
 * interrupts.
E 20
 */
I 77
void
E 77
D 51
gsignal(pgrp, sig)
	register int pgrp;
E 51
I 51
D 116
gsignal(pgid, sig)
I 77
	int pgid, sig;
E 116
I 116
gsignal(pgid, signum)
	int pgid, signum;
E 116
E 77
E 51
{
I 51
D 59
	register struct pgrp *pgrp;
E 59
I 59
	struct pgrp *pgrp;
E 59
E 51
D 56
	register struct proc *p;
E 56

D 51
	if (pgrp == 0)
E 51
I 51
D 59
	if (!pgid)
E 51
		return;
D 29
	for(p = proc; p < procNPROC; p++)
E 29
I 29
D 51
	for (p = allproc; p != NULL; p = p->p_nxt)
E 29
		if (p->p_pgrp == pgrp)
			psignal(p, sig);
E 51
I 51
	if ((pgrp = pgfind(pgid)) == NULL)
		return;
	pgsignal(pgrp, sig);
E 59
I 59
	if (pgid && (pgrp = pgfind(pgid)))
D 65
		pgsignal(pgrp, sig);
E 65
I 65
D 116
		pgsignal(pgrp, sig, 0);
E 116
I 116
		pgsignal(pgrp, signum, 0);
E 116
E 65
E 59
E 51
}
I 67

E 67
D 60

E 60
I 60
/*
D 65
 * Send sig to all all members of the process group
E 65
I 65
D 116
 * Send sig to every member of a process group.
 * If checktty is 1, limit to members which have a controlling
 * terminal.
E 116
I 116
D 127
 * Send a signal to a  process group.  If checktty is 1,
E 127
I 127
 * Send a signal to a process group.  If checktty is 1,
E 127
 * limit to members which have a controlling terminal.
E 116
E 65
 */
I 77
void
E 77
E 60
I 51
D 65
pgsignal(pgrp, sig)
E 65
I 65
D 116
pgsignal(pgrp, sig, checkctty)
E 116
I 116
pgsignal(pgrp, signum, checkctty)
E 116
E 65
D 59
	register struct pgrp *pgrp;
E 59
I 59
	struct pgrp *pgrp;
I 77
D 116
	int sig, checkctty;
E 116
I 116
	int signum, checkctty;
E 116
E 77
E 59
{
	register struct proc *p;

D 59
	if (!(pgrp->pg_jobc) && 
	     (sig==SIGTTIN || sig==SIGTTOU || sig==SIGTSTP))
		return;
	for (p = pgrp->pg_mem; p != NULL; p = p->p_pgrpnxt)
E 59
I 59
D 60
	for (p = pgrp->pg_mem; p; p = p->p_pgrpnxt)
E 59
		psignal(p, sig);
E 60
I 60
	if (pgrp)
D 124
		for (p = pgrp->pg_mem; p != NULL; p = p->p_pgrpnxt)
E 124
I 124
		for (p = pgrp->pg_members.lh_first; p != 0;
		     p = p->p_pglist.le_next)
E 124
D 65
			psignal(p, sig);
E 65
I 65
D 113
			if (checkctty == 0 || p->p_flag&SCTTY)
E 113
I 113
D 118
			if (checkctty == 0 || p->p_flag & SCTTY)
E 118
I 118
			if (checkctty == 0 || p->p_flag & P_CONTROLT)
E 118
E 113
D 116
				psignal(p, sig);
E 116
I 116
				psignal(p, signum);
E 116
E 65
E 60
}

E 51
/*
I 59
 * Send a signal caused by a trap to the current process.
 * If it will be caught immediately, deliver it with correct code.
 * Otherwise, post it normally.
 */
D 77
trapsignal(sig, code)
E 77
I 77
void
D 116
trapsignal(p, sig, code)
E 116
I 116
trapsignal(p, signum, code)
E 116
	struct proc *p;
E 77
D 116
	register int sig;
	unsigned code;
E 116
I 116
	register int signum;
D 126
	u_int code;
E 126
I 126
	u_long code;
E 126
E 116
{
D 67
	register struct proc *p = u.u_procp;
E 67
I 67
D 77
	register struct proc *p = u.u_procp;	/* XXX */
E 77
I 77
	register struct sigacts *ps = p->p_sigacts;
E 77
E 67
	int mask;

D 116
	mask = sigmask(sig);
E 116
I 116
	mask = sigmask(signum);
E 116
D 118
	if ((p->p_flag & STRC) == 0 && (p->p_sigcatch & mask) != 0 &&
E 118
I 118
	if ((p->p_flag & P_TRACED) == 0 && (p->p_sigcatch & mask) != 0 &&
E 118
	    (p->p_sigmask & mask) == 0) {
D 77
		u.u_ru.ru_nsignals++;
E 77
I 77
		p->p_stats->p_ru.ru_nsignals++;
E 77
I 60
#ifdef KTRACE
		if (KTRPOINT(p, KTR_PSIG))
D 77
			ktrpsig(p->p_tracep, sig, u.u_signal[sig], 
E 77
I 77
D 116
			ktrpsig(p->p_tracep, sig, ps->ps_sigact[sig], 
E 116
I 116
			ktrpsig(p->p_tracep, signum, ps->ps_sigact[signum], 
E 116
E 77
				p->p_sigmask, code);
#endif
I 76
D 78
#if	defined(i386)
D 77
		sendsig(u.u_signal[sig], sig, p->p_sigmask, code, 0x100);
E 77
I 77
		sendsig(ps->ps_sigact[sig], sig, p->p_sigmask, code, 0x100);
E 77
#else
E 78
E 76
E 60
D 77
		sendsig(u.u_signal[sig], sig, p->p_sigmask, code);
E 77
I 77
D 116
		sendsig(ps->ps_sigact[sig], sig, p->p_sigmask, code);
E 77
I 76
D 78
#endif
E 78
E 76
D 77
		p->p_sigmask |= u.u_sigmask[sig] | mask;
E 77
I 77
		p->p_sigmask |= ps->ps_catchmask[sig] | mask;
E 116
I 116
		sendsig(ps->ps_sigact[signum], signum, p->p_sigmask, code);
		p->p_sigmask |= ps->ps_catchmask[signum] | mask;
E 116
E 77
	} else {
D 71
		u.u_arg[1] = code;	/* XXX for core dump/debugger */
E 71
I 71
D 77
		u.u_code = code;	/* XXX for core dump/debugger */
E 77
I 77
		ps->ps_code = code;	/* XXX for core dump/debugger */
I 122
		ps->ps_sig = signum;	/* XXX to verify code */
E 122
E 77
E 71
D 116
		psignal(p, sig);
E 116
I 116
		psignal(p, signum);
E 116
	}
}

/*
E 59
D 60
 * Send the specified signal to
 * the specified process.
E 60
I 60
D 116
 * Send the specified signal to the specified process.
D 77
 * Most signals do not do anything directly to a process;
 * they set a flag that asks the process to do something to itself.
E 77
I 77
 * If the signal has an action, the action is usually performed
 * by the target process rather than the caller; we simply add
E 116
I 116
 * Send the signal to the process.  If the signal has an action, the action
 * is usually performed by the target process rather than the caller; we add
E 116
 * the signal to the set of pending signals for the process.
I 116
 *
E 116
E 77
 * Exceptions:
D 116
 *   o When a stop signal is sent to a sleeping process that takes the default
 *     action, the process is stopped without awakening it.
E 116
I 116
 *   o When a stop signal is sent to a sleeping process that takes the
 *     default action, the process is stopped without awakening it.
E 116
 *   o SIGCONT restarts stopped processes (or puts them back to sleep)
 *     regardless of the signal action (eg, blocked or ignored).
I 116
 *
E 116
 * Other ignored signals are discarded immediately.
E 60
 */
I 77
void
E 77
D 116
psignal(p, sig)
E 116
I 116
psignal(p, signum)
E 116
	register struct proc *p;
D 116
	register int sig;
E 116
I 116
	register int signum;
E 116
{
D 77
	register int s;
E 77
I 77
	register int s, prop;
E 77
D 59
	register int (*action)();
E 59
I 59
	register sig_t action;
E 59
D 20
	long sigmask;
E 20
I 20
D 33
	int sigmask;
E 33
I 33
	int mask;
E 33
E 20

D 59
	if ((unsigned)sig >= NSIG)
E 59
I 59
D 116
	if ((unsigned)sig >= NSIG || sig == 0)
		panic("psignal sig");
D 60
	if (p->p_pgrp->pg_jobc == 0 && 
	     (sig == SIGTTIN || sig == SIGTTOU || sig == SIGTSTP))
E 59
		return;
E 60
D 20
	sigmask = (1L << (sig-1));
E 20
I 20
D 33
	sigmask = 1 << (sig-1);
E 33
I 33
	mask = sigmask(sig);
I 77
	prop = sigprop[sig];
E 116
I 116
	if ((u_int)signum >= NSIG || signum == 0)
		panic("psignal signal number");
	mask = sigmask(signum);
	prop = sigprop[signum];
E 116
E 77
E 33
E 20

	/*
	 * If proc is traced, always give parent a chance.
D 20
	 * Otherwise get the signal action from the bits in the proc table.
E 20
	 */
D 118
	if (p->p_flag & STRC)
E 118
I 118
	if (p->p_flag & P_TRACED)
E 118
		action = SIG_DFL;
	else {
D 20
		s = (p->p_siga1&sigmask) != 0;
		s <<= 1;
		s |= (p->p_siga0&sigmask) != 0;
		action = (int(*)())s;
E 20
		/*
D 20
		 * If the signal is ignored, we forget about it immediately.
E 20
I 20
		 * If the signal is being ignored,
		 * then we forget about it immediately.
I 59
		 * (Note: we don't set SIGCONT in p_sigignore,
		 * and if it is set to SIG_IGN,
		 * action will be SIG_DFL here.)
E 59
E 20
		 */
D 20
		if (action == SIG_IGN)
E 20
I 20
D 33
		if (p->p_sigignore & sigmask)
E 33
I 33
		if (p->p_sigignore & mask)
E 33
E 20
			return;
I 20
D 33
		if (p->p_sigmask & sigmask)
E 33
I 33
		if (p->p_sigmask & mask)
E 33
			action = SIG_HOLD;
D 33
		else if (p->p_sigcatch & sigmask)
E 33
I 33
		else if (p->p_sigcatch & mask)
E 33
			action = SIG_CATCH;
D 60
		else
E 60
I 60
D 66
		else {
			if (p->p_pgrp->pg_jobc == 0 && (sig == SIGTTIN || 
			    sig == SIGTTOU || sig == SIGTSTP))
				return;
E 66
I 66
		else
E 66
E 60
			action = SIG_DFL;
I 60
D 66
		}
E 66
E 60
E 20
	}
D 33
#define mask(sig)	(1<<(sig-1))
#define	stops	(mask(SIGSTOP)|mask(SIGTSTP)|mask(SIGTTIN)|mask(SIGTTOU))
E 33
I 33
D 46
#define	stops	(sigmask(SIGSTOP)|sigmask(SIGTSTP)| \
			sigmask(SIGTTIN)|sigmask(SIGTTOU))
E 46
E 33
D 59
	if (sig) {
D 33
		p->p_sig |= sigmask;
E 33
I 33
D 51
		p->p_sig |= mask;
E 51
E 33
		switch (sig) {
E 59
I 59
D 77
	switch (sig) {
E 77
E 59

D 59
		case SIGTERM:
D 20
			if ((p->p_flag&STRC) != 0 || action != SIG_DFL)
E 20
I 20
			if ((p->p_flag&STRC) || action != SIG_DFL)
E 20
				break;
			/* fall into ... */

		case SIGKILL:
			if (p->p_nice > NZERO)
				p->p_nice = NZERO;
E 59
I 59
D 77
	case SIGTERM:
		if ((p->p_flag&STRC) || action != SIG_DFL)
E 59
			break;
I 59
		/* FALLTHROUGH */
E 77
I 77
D 113
	if (p->p_nice > NZERO && (sig == SIGKILL ||
	    sig == SIGTERM && (p->p_flag&STRC || action != SIG_DFL)))
E 113
I 113
	if (p->p_nice > NZERO && action == SIG_DFL && (prop & SA_KILL) &&
D 118
	    (p->p_flag & STRC) == 0)
E 118
I 118
	    (p->p_flag & P_TRACED) == 0)
E 118
E 113
		p->p_nice = NZERO;
E 77
E 59

D 59
		case SIGCONT:
D 46
			p->p_sig &= ~stops;
E 46
I 46
			p->p_sig &= ~stopsigmask;
E 46
			break;
E 59
I 59
D 77
	case SIGKILL:
		if (p->p_nice > NZERO)
			p->p_nice = NZERO;
		break;
E 59

D 51
		case SIGSTOP:
E 51
D 59
		case SIGTSTP:
		case SIGTTIN:
		case SIGTTOU:
I 51
			/*FALLTHROUGH*/
		case SIGSTOP:
E 51
D 33
			p->p_sig &= ~mask(SIGCONT);
E 33
I 33
			p->p_sig &= ~sigmask(SIGCONT);
E 33
			break;
		}
I 51
		p->p_sig |= mask;
E 59
I 59
	case SIGCONT:
E 77
I 77
	if (prop & SA_CONT)
E 77
D 118
		p->p_sig &= ~stopsigmask;
E 118
I 118
		p->p_siglist &= ~stopsigmask;
E 118
D 77
		break;
E 77

D 77
	case SIGTSTP:
	case SIGTTIN:
	case SIGTTOU:
E 77
I 77
	if (prop & SA_STOP) {
E 77
I 74
		/*
		 * If sending a tty stop signal to a member of an orphaned
		 * process group, discard the signal here if the action
		 * is default; don't stop the process below if sleeping,
		 * and don't clear any pending SIGCONT.
		 */
D 77
		if (p->p_pgrp->pg_jobc == 0 && action == SIG_DFL)
E 77
I 77
		if (prop & SA_TTYSTOP && p->p_pgrp->pg_jobc == 0 &&
		    action == SIG_DFL)
E 77
D 75
			return;
E 75
I 75
D 127
		        return;
E 127
I 127
			return;
E 127
E 75
D 77
		/* FALLTHROUGH */

E 74
	case SIGSTOP:
		p->p_sig &= ~sigmask(SIGCONT);
		break;
E 77
I 77
D 118
		p->p_sig &= ~contsigmask;
E 118
I 118
		p->p_siglist &= ~contsigmask;
E 118
E 77
E 59
E 51
	}
I 59
D 118
	p->p_sig |= mask;
E 118
I 118
	p->p_siglist |= mask;
E 118

E 59
D 33
#undef mask
E 33
D 46
#undef stops
E 46
	/*
D 59
	 * Defer further processing for signals which are held.
E 59
I 59
	 * Defer further processing for signals which are held,
	 * except that stopped processes must be continued by SIGCONT.
E 59
	 */
D 59
	if (action == SIG_HOLD)
E 59
I 59
D 77
	if (action == SIG_HOLD && (sig != SIGCONT || p->p_stat != SSTOP))
E 77
I 77
	if (action == SIG_HOLD && ((prop & SA_CONT) == 0 || p->p_stat != SSTOP))
E 77
E 59
		return;
D 33
	s = spl6();
E 33
I 33
	s = splhigh();
E 33
	switch (p->p_stat) {

	case SSLEEP:
		/*
D 60
		 * If process is sleeping at negative priority
E 60
I 60
		 * If process is sleeping uninterruptibly
E 60
		 * we can't interrupt the sleep... the signal will
		 * be noticed when the process returns through
		 * trap() or syscall().
		 */
D 60
		if (p->p_pri <= PZERO)
E 60
I 60
D 118
		if ((p->p_flag & SSINTR) == 0)
E 118
I 118
		if ((p->p_flag & P_SINTR) == 0)
E 118
E 60
			goto out;
		/*
		 * Process is sleeping and traced... make it runnable
D 118
		 * so it can discover the signal in issig() and stop
E 118
I 118
		 * so it can discover the signal in issignal() and stop
E 118
		 * for the parent.
		 */
D 113
		if (p->p_flag&STRC)
E 113
I 113
D 118
		if (p->p_flag & STRC)
E 118
I 118
		if (p->p_flag & P_TRACED)
E 118
E 113
			goto run;
D 59
		switch (sig) {

		case SIGSTOP:
		case SIGTSTP:
		case SIGTTIN:
		case SIGTTOU:
			/*
			 * These are the signals which by default
			 * stop a process.
			 */
E 59
I 59
		/*
I 113
		 * If SIGCONT is default (or ignored) and process is
		 * asleep, we are finished; the process should not
		 * be awakened.
		 */
		if ((prop & SA_CONT) && action == SIG_DFL) {
D 118
			p->p_sig &= ~mask;
E 118
I 118
			p->p_siglist &= ~mask;
E 118
			goto out;
		}
		/*
E 113
		 * When a sleeping process receives a stop
		 * signal, process immediately if possible.
		 * All other (caught or default) signals
		 * cause the process to run.
		 */
D 77
		if (mask & stopsigmask) {
E 77
I 77
		if (prop & SA_STOP) {
E 77
E 59
			if (action != SIG_DFL)
D 59
				goto run;
E 59
I 59
				goto runfast;
E 59
			/*
D 51
			 * Don't clog system with children of init
			 * stopped from the keyboard.
			 */
			if (sig != SIGSTOP && p->p_pptr == &proc[1]) {
				psignal(p, SIGKILL);
D 33
				p->p_sig &= ~sigmask;
E 33
I 33
				p->p_sig &= ~mask;
E 33
				splx(s);
				return;
			}
			/*
E 51
D 77
			 * If a child in vfork(), stopping could
			 * cause deadlock.
E 77
I 77
			 * If a child holding parent blocked,
			 * stopping could cause deadlock.
E 77
			 */
D 77
			if (p->p_flag&SVFORK)
E 77
I 77
D 113
			if (p->p_flag&SPPWAIT)
E 113
I 113
D 118
			if (p->p_flag & SPPWAIT)
E 118
I 118
			if (p->p_flag & P_PPWAIT)
E 118
E 113
E 77
				goto out;
D 33
			p->p_sig &= ~sigmask;
E 33
I 33
D 118
			p->p_sig &= ~mask;
E 118
I 118
			p->p_siglist &= ~mask;
E 118
E 33
D 71
			p->p_cursig = sig;
E 71
I 71
D 116
			p->p_xstat = sig;
E 116
I 116
			p->p_xstat = signum;
E 116
E 71
I 38
D 59
			psignal(p->p_pptr, SIGCHLD);
E 59
I 59
D 118
			if ((p->p_pptr->p_flag & SNOCLDSTOP) == 0)
E 118
I 118
			if ((p->p_pptr->p_flag & P_NOCLDSTOP) == 0)
E 118
				psignal(p->p_pptr, SIGCHLD);
E 59
E 38
			stop(p);
			goto out;
D 59

		case SIGIO:
		case SIGURG:
		case SIGCHLD:
I 35
		case SIGWINCH:
E 35
			/*
			 * These signals are special in that they
			 * don't get propogated... if the process
			 * isn't interested, forget it.
			 */
			if (action != SIG_DFL)
				goto run;
D 33
			p->p_sig &= ~sigmask;		/* take it away */
E 33
I 33
			p->p_sig &= ~mask;		/* take it away */
E 33
			goto out;

		default:
			/*
			 * All other signals cause the process to run
			 */
			goto run;
		}
E 59
I 59
		} else
			goto runfast;
E 59
		/*NOTREACHED*/

	case SSTOP:
		/*
		 * If traced process is already stopped,
		 * then no further action is necessary.
		 */
D 113
		if (p->p_flag&STRC)
E 113
I 113
D 118
		if (p->p_flag & STRC)
E 118
I 118
		if (p->p_flag & P_TRACED)
E 118
E 113
			goto out;
D 77
		switch (sig) {
E 77

D 77
		case SIGKILL:
			/*
			 * Kill signal always sets processes running.
			 */
E 77
I 77
		/*
		 * Kill signal always sets processes running.
		 */
D 116
		if (sig == SIGKILL)
E 116
I 116
		if (signum == SIGKILL)
E 116
E 77
D 59
			goto run;
E 59
I 59
			goto runfast;
E 59

D 77
		case SIGCONT:
E 77
I 77
		if (prop & SA_CONT) {
E 77
			/*
I 59
D 118
			 * If SIGCONT is default (or ignored), we continue
			 * the process but don't leave the signal in p_sig,
			 * as it has no further action.  If SIGCONT is held,
			 * continue the process and leave the signal in p_sig.
E 59
			 * If the process catches SIGCONT, let it handle
			 * the signal itself.  If it isn't waiting on
E 118
I 118
			 * If SIGCONT is default (or ignored), we continue the
			 * process but don't leave the signal in p_siglist, as
			 * it has no further action.  If SIGCONT is held, we
			 * continue the process and leave the signal in
			 * p_siglist.  If the process catches SIGCONT, let it
			 * handle the signal itself.  If it isn't waiting on
E 118
			 * an event, then it goes back to run state.
			 * Otherwise, process goes back to sleep state.
			 */
D 59
			if (action != SIG_DFL || p->p_wchan == 0)
E 59
I 59
D 71
			p->p_cursig = 0;	/* ??? XXX */
E 71
			if (action == SIG_DFL)
D 118
				p->p_sig &= ~mask;
E 118
I 118
				p->p_siglist &= ~mask;
E 118
			if (action == SIG_CATCH)
				goto runfast;
			if (p->p_wchan == 0)
E 59
				goto run;
			p->p_stat = SSLEEP;
			goto out;
I 77
		}
E 77

D 77
		case SIGSTOP:
		case SIGTSTP:
		case SIGTTIN:
		case SIGTTOU:
E 77
I 77
		if (prop & SA_STOP) {
E 77
			/*
			 * Already stopped, don't need to stop again.
			 * (If we did the shell could get confused.)
			 */
D 33
			p->p_sig &= ~sigmask;		/* take it away */
E 33
I 33
D 118
			p->p_sig &= ~mask;		/* take it away */
E 118
I 118
			p->p_siglist &= ~mask;		/* take it away */
E 118
E 33
			goto out;
D 77

		default:
			/*
			 * If process is sleeping interruptibly, then
D 60
			 * unstick it so that when it is continued
			 * it can look at the signal.
			 * But don't setrun the process as its not to
			 * be unstopped by the signal alone.
E 60
I 60
			 * simulate a wakeup so that when it is continued,
			 * it will be made runnable and can look at the signal.
			 * But don't setrun the process, leave it stopped.
E 60
			 */
D 60
			if (p->p_wchan && p->p_pri > PZERO)
E 60
I 60
			if (p->p_wchan && p->p_flag & SSINTR)
E 60
				unsleep(p);
			goto out;
E 77
		}
D 77
		/*NOTREACHED*/
E 77

I 77
		/*
D 117
		 * If process is sleeping interruptibly, then
		 * simulate a wakeup so that when it is continued,
		 * it will be made runnable and can look at the signal.
		 * But don't setrun the process, leave it stopped.
E 117
I 117
		 * If process is sleeping interruptibly, then simulate a
		 * wakeup so that when it is continued, it will be made
		 * runnable and can look at the signal.  But don't make
		 * the process runnable, leave it stopped.
E 117
		 */
D 118
		if (p->p_wchan && p->p_flag & SSINTR)
E 118
I 118
		if (p->p_wchan && p->p_flag & P_SINTR)
E 118
			unsleep(p);
		goto out;

E 77
	default:
		/*
		 * SRUN, SIDL, SZOMB do nothing with the signal,
		 * other than kicking ourselves if we are running.
		 * It will either never be noticed, or noticed very soon.
		 */
D 77
		if (p == u.u_procp && !noproc)
E 77
I 77
D 78
		if (p == curproc && !noproc)
E 78
I 78
		if (p == curproc)
E 78
E 77
I 8
D 49
#include "../vax/mtpr.h"
E 49
E 8
D 80
			aston();
E 80
I 80
			signotify(p);
E 80
		goto out;
	}
	/*NOTREACHED*/
D 59
run:
E 59
I 59

runfast:
E 59
	/*
	 * Raise priority to at least PUSER.
	 */
D 118
	if (p->p_pri > PUSER)
D 34
		if ((p != u.u_procp || noproc) && p->p_stat == SRUN &&
		    (p->p_flag & SLOAD)) {
			remrq(p);
			p->p_pri = PUSER;
			setrq(p);
		} else
			p->p_pri = PUSER;
E 34
I 34
		p->p_pri = PUSER;
E 118
I 118
	if (p->p_priority > PUSER)
		p->p_priority = PUSER;
E 118
I 59
run:
E 59
E 34
D 117
	setrun(p);
E 117
I 117
	setrunnable(p);
E 117
out:
	splx(s);
}

/*
D 60
 * Returns true if the current
 * process has a signal to process.
 * The signal to process is put in p_cursig.
E 60
I 60
D 116
 * If the current process has a signal to process (should be caught
 * or cause termination, should interrupt current syscall),
 * return the signal number.  Stop signals with default action
 * are processed immediately, then cleared; they aren't returned.
E 60
D 77
 * This is asked at least once each time a process enters the
 * system (though this can usually be done without actually
 * calling issig by checking the pending signal masks.)
E 77
I 77
 * This is checked after each entry to the system for a syscall
 * or trap (though this can usually be done without actually calling
 * issig by checking the pending signal masks in the CURSIG macro.)
 * The normal call sequence is
E 116
I 116
 * If the current process has received a signal (should be caught or cause
 * termination, should interrupt current syscall), return the signal number.
 * Stop signals with default action are processed immediately, then cleared;
 * they aren't returned.  This is checked after each entry to the system for
D 118
 * a syscall or trap (though this can usually be done without calling issig
E 118
I 118
 * a syscall or trap (though this can usually be done without calling issignal
E 118
 * by checking the pending signal masks in the CURSIG macro.) The normal call
 * sequence is
E 116
 *
D 116
 *	while (sig = CURSIG(curproc))
 *		psig(sig);
E 116
I 116
 *	while (signum = CURSIG(curproc))
D 118
 *		psig(signum);
E 118
I 118
 *		postsig(signum);
E 118
E 116
E 77
D 59
 * A signal does not do anything
 * directly to a process; it sets
E 59
I 59
D 60
 * Most signals do not do anything
 * directly to a process; they set
E 59
 * a flag that asks the process to
 * do something to itself.
E 60
 */
I 127
int
E 127
D 77
issig()
E 77
I 77
D 118
issig(p)
E 118
I 118
issignal(p)
E 118
	register struct proc *p;
E 77
{
D 69
	register struct proc *p;
E 69
I 69
D 77
	register struct proc *p = u.u_procp;		/* XXX */
E 69
D 59
	register int sig;
D 20
	long sigbits;
	long sigmask;
E 20
I 20
D 33
	int sigbits, sigmask;
E 33
I 33
	int sigbits, mask;
E 59
I 59
	register int sig, mask;
E 77
I 77
D 116
	register int sig, mask, prop;
E 116
I 116
	register int signum, mask, prop;
E 116
E 77
E 59
E 33
E 20

D 69
	p = u.u_procp;
E 69
	for (;;) {
D 26
		sigbits = p->p_sig;
E 26
I 26
D 59
		sigbits = p->p_sig &~ p->p_sigmask;
E 26
		if ((p->p_flag&STRC) == 0)
D 20
			sigbits &= ~p->p_ignsig;
E 20
I 20
D 26
			sigbits &= ~(p->p_sigignore | p->p_sigmask);
E 26
I 26
			sigbits &= ~p->p_sigignore;
E 59
I 59
D 118
		mask = p->p_sig &~ p->p_sigmask;
E 59
E 26
E 20
D 77
		if (p->p_flag&SVFORK)
E 77
I 77
D 113
		if (p->p_flag&SPPWAIT)
E 113
I 113
		if (p->p_flag & SPPWAIT)
E 118
I 118
		mask = p->p_siglist & ~p->p_sigmask;
		if (p->p_flag & P_PPWAIT)
E 118
E 113
E 77
D 46
#define bit(a) (1<<(a-1))
			sigbits &= ~(bit(SIGSTOP)|bit(SIGTSTP)|bit(SIGTTIN)|bit(SIGTTOU));
E 46
I 46
D 59
			sigbits &= ~stopsigmask;
E 46
		if (sigbits == 0)
E 59
I 59
			mask &= ~stopsigmask;
D 60
		if (mask == 0)
E 59
			break;
E 60
I 60
		if (mask == 0)	 	/* no signal to send */
			return (0);
E 60
D 20
		sig = ffs((int)sigbits);
		sigmask = 1L << (sig-1);
E 20
I 20
D 47
		sig = ffs(sigbits);
E 47
I 47
D 59
		sig = ffs((long)sigbits);
E 59
I 59
D 116
		sig = ffs((long)mask);
E 59
E 47
D 33
		sigmask = 1 << (sig-1);
E 20
		p->p_sig &= ~sigmask;		/* take the signal! */
E 33
I 33
		mask = sigmask(sig);
I 77
		prop = sigprop[sig];
E 116
I 116
		signum = ffs((long)mask);
		mask = sigmask(signum);
		prop = sigprop[signum];
E 116
E 77
D 60
		p->p_sig &= ~mask;		/* take the signal! */
I 59
		if (mask & p->p_sigignore && (p->p_flag&STRC) == 0)
			continue;	/* only if STRC was on when posted */
E 59
E 33
		p->p_cursig = sig;
E 60
I 60
		/*
		 * We should see pending but ignored signals
D 118
		 * only if STRC was on when they were posted.
E 118
I 118
		 * only if P_TRACED was on when they were posted.
E 118
		 */
D 113
		if (mask & p->p_sigignore && (p->p_flag&STRC) == 0) {
E 113
I 113
D 118
		if (mask & p->p_sigignore && (p->p_flag & STRC) == 0) {
E 113
			p->p_sig &= ~mask;
E 118
I 118
		if (mask & p->p_sigignore && (p->p_flag & P_TRACED) == 0) {
			p->p_siglist &= ~mask;
E 118
			continue;
		}
E 60
D 20
		if (p->p_flag&STRC && (p->p_flag&SVFORK)==0) {
E 20
I 20
D 77
		if (p->p_flag&STRC && (p->p_flag&SVFORK) == 0) {
E 77
I 77
D 113
		if (p->p_flag&STRC && (p->p_flag&SPPWAIT) == 0) {
E 113
I 113
D 118
		if (p->p_flag & STRC && (p->p_flag & SPPWAIT) == 0) {
E 118
I 118
		if (p->p_flag & P_TRACED && (p->p_flag & P_PPWAIT) == 0) {
E 118
E 113
E 77
E 20
			/*
			 * If traced, always stop, and stay
			 * stopped until released by the parent.
I 122
			 *
			 * Note that we must clear the pending signal
			 * before we call trace_req since that routine
			 * might cause a fault, calling tsleep and
			 * leading us back here again with the same signal.
			 * Then we would be deadlocked because the tracer
			 * would still be blocked on the ipc struct from
			 * the initial request.
E 122
			 */
I 60
D 71
			p->p_cursig = sig;
E 71
I 71
D 116
			p->p_xstat = sig;
E 116
I 116
			p->p_xstat = signum;
I 122
			p->p_siglist &= ~mask;
E 122
E 116
E 71
E 60
I 38
			psignal(p->p_pptr, SIGCHLD);
E 38
			do {
				stop(p);
D 118
				swtch();
D 69
			} while (!procxmt() && p->p_flag&STRC);
E 69
I 69
D 113
			} while (!procxmt(p) && p->p_flag&STRC);
E 113
I 113
			} while (!procxmt(p) && p->p_flag & STRC);
E 118
I 118
				mi_switch();
			} while (!trace_req(p) && p->p_flag & P_TRACED);
E 118
E 113
E 69

			/*
D 22
			 * If the traced bit got turned off,
			 * then put the signal taken above back into p_sig
			 * and go back up to the top to rescan signals.
			 * This ensures that siga0 and u_signal are consistent.
E 22
I 22
D 26
			 * If the traced bit got turned off or signal
			 * is being masked, then put the signal taken
			 * above back into p_sig and go back up to the
			 * top to rescan signals.  This ensures that
			 * p_sig* and u_signal are consistent.
E 26
I 26
D 118
			 * If the traced bit got turned off,
D 60
			 * then put the signal taken above back into p_sig
			 * and go back up to the top to rescan signals.
E 60
I 60
			 * go back up to the top to rescan signals.
E 60
D 78
			 * This ensures that p_sig* and u_signal are consistent.
E 78
I 78
			 * This ensures that p_sig* and ps_sigact
			 * are consistent.
E 118
I 118
D 122
			 * If the traced bit got turned off, go back up
			 * to the top to rescan signals.  This ensures
			 * that p_sig* and ps_sigact are consistent.
E 118
E 78
E 26
E 22
			 */
D 22
			if ((p->p_flag&STRC) == 0) {
E 22
I 22
D 26
			if ((p->p_flag&STRC) == 0 || (p->p_sigmask & sigmask)) {
E 26
I 26
D 60
			if ((p->p_flag&STRC) == 0) {
E 26
E 22
D 33
				p->p_sig |= sigmask;
E 33
I 33
				p->p_sig |= mask;
E 60
I 60
D 113
			if ((p->p_flag&STRC) == 0)
E 113
I 113
D 118
			if ((p->p_flag & STRC) == 0)
E 118
I 118
			if ((p->p_flag & P_TRACED) == 0)
E 118
E 113
E 60
E 33
				continue;
D 60
			}
E 60

			/*
E 122
			 * If parent wants us to take the signal,
D 71
			 * then it will leave it in p->p_cursig;
E 71
I 71
			 * then it will leave it in p->p_xstat;
E 71
			 * otherwise we just look for signals again.
			 */
I 60
D 118
			p->p_sig &= ~mask;	/* clear the old signal */
E 118
I 118
D 122
			p->p_siglist &= ~mask;	/* clear the old signal */
E 122
E 118
E 60
D 71
			sig = p->p_cursig;
E 71
I 71
D 116
			sig = p->p_xstat;
E 71
			if (sig == 0)
E 116
I 116
			signum = p->p_xstat;
			if (signum == 0)
E 116
				continue;
I 26

			/*
D 60
			 * If signal is being masked put it back
			 * into p_sig and look for other signals.
E 60
I 60
D 118
			 * Put the new signal into p_sig.
			 * If signal is being masked,
			 * look for other signals.
E 118
I 118
			 * Put the new signal into p_siglist.  If the
			 * signal is being masked, look for other signals.
E 118
E 60
			 */
D 33
			sigmask = 1 << (sig-1);
			if (p->p_sigmask & sigmask) {
				p->p_sig |= sigmask;
E 33
I 33
D 116
			mask = sigmask(sig);
E 116
I 116
			mask = sigmask(signum);
E 116
D 60
			if (p->p_sigmask & mask) {
				p->p_sig |= mask;
E 60
I 60
D 118
			p->p_sig |= mask;
E 118
I 118
			p->p_siglist |= mask;
E 118
			if (p->p_sigmask & mask)
E 60
E 33
				continue;
I 122

			/*
			 * If the traced bit got turned off, go back up
			 * to the top to rescan signals.  This ensures
			 * that p_sig* and ps_sigact are consistent.
			 */
			if ((p->p_flag & P_TRACED) == 0)
				continue;
E 122
D 60
			}
E 60
E 26
		}
I 60

		/*
		 * Decide whether the signal should be returned.
		 * Return the signal's number, or fall through
		 * to clear it from the pending mask.
		 */
E 60
D 45
		switch (u.u_signal[sig]) {
E 45
I 45
D 77
		switch ((int)u.u_signal[sig]) {
E 77
I 77
D 116
		switch ((int)p->p_sigacts->ps_sigact[sig]) {
E 116
I 116
D 127
		switch ((int)p->p_sigacts->ps_sigact[signum]) {
E 127
I 127
		switch ((long)p->p_sigacts->ps_sigact[signum]) {
E 127
E 116
E 77
E 45

D 127
		case SIG_DFL:
E 127
I 127
		case (long)SIG_DFL:
E 127
			/*
			 * Don't take default actions on system processes.
			 */
D 77
			if (p->p_ppid == 0)
E 77
I 77
D 86
			if (p->p_pid <= 1)
E 86
I 86
			if (p->p_pid <= 1) {
#ifdef DIAGNOSTIC
				/*
				 * Are you sure you want to ignore SIGSEGV
				 * in init? XXX
				 */
				printf("Process (pid %d) got signal %d\n",
D 116
					p->p_pid, sig);
E 116
I 116
					p->p_pid, signum);
E 116
#endif
E 86
E 77
D 59
				break;
			switch (sig) {

			case SIGTSTP:
			case SIGTTIN:
			case SIGTTOU:
D 51
				/*
				 * Children of init aren't allowed to stop
				 * on signals from the keyboard.
				 */
				if (p->p_pptr == &proc[1]) {
					psignal(p, SIGKILL);
					continue;
				}
				/* fall into ... */

E 51
			case SIGSTOP:
E 59
I 59
D 60
				continue;
E 60
I 60
				break;		/* == ignore */
I 86
			}
E 86
			/*
			 * If there is a pending stop signal to process
			 * with default action, stop here,
D 66
			 * then clear the signal.
E 66
I 66
			 * then clear the signal.  However,
			 * if process is member of an orphaned
			 * process group, ignore tty stop signals.
E 66
			 */
E 60
D 77
			if (mask & stopsigmask) {
E 77
I 77
			if (prop & SA_STOP) {
E 77
E 59
D 66
				if (p->p_flag&STRC)
E 66
I 66
D 113
				if (p->p_flag&STRC ||
E 113
I 113
D 118
				if (p->p_flag & STRC ||
E 118
I 118
				if (p->p_flag & P_TRACED ||
E 118
E 113
		    		    (p->p_pgrp->pg_jobc == 0 &&
D 77
				    mask & ttystopsigmask))
E 77
I 77
				    prop & SA_TTYSTOP))
E 77
E 66
D 60
					continue;
E 60
I 60
					break;	/* == ignore */
D 71
				p->p_cursig = sig;
E 71
I 71
D 116
				p->p_xstat = sig;
E 116
I 116
				p->p_xstat = signum;
E 116
E 71
E 60
I 38
D 59
				psignal(p->p_pptr, SIGCHLD);
E 59
E 38
				stop(p);
I 59
D 118
				if ((p->p_pptr->p_flag & SNOCLDSTOP) == 0)
E 118
I 118
				if ((p->p_pptr->p_flag & P_NOCLDSTOP) == 0)
E 118
					psignal(p->p_pptr, SIGCHLD);
E 59
D 118
				swtch();
E 118
I 118
				mi_switch();
E 118
D 60
				continue;
E 60
I 60
				break;
E 60
D 59

			case SIGCONT:
			case SIGCHLD:
I 20
			case SIGURG:
I 21
			case SIGIO:
I 35
			case SIGWINCH:
E 59
I 59
D 77
			} else if (mask & defaultignmask) {
E 77
I 77
			} else if (prop & SA_IGNORE) {
E 77
E 59
E 35
E 21
E 20
				/*
D 59
				 * These signals are normally not
				 * sent if the action is the default.
E 59
I 59
				 * Except for SIGCONT, shouldn't get here.
				 * Default action is to ignore; drop it.
E 59
				 */
D 60
				continue;		/* == ignore */
E 60
I 60
				break;		/* == ignore */
E 60
D 59

			default:
E 59
I 59
			} else
E 59
D 60
				goto send;
E 60
I 60
D 116
				return (sig);
E 116
I 116
				return (signum);
E 116
E 60
D 59
			}
E 59
			/*NOTREACHED*/

D 59
		case SIG_HOLD:
E 59
D 127
		case SIG_IGN:
E 127
I 127
		case (long)SIG_IGN:
E 127
			/*
D 59
			 * Masking above should prevent us
			 * ever trying to take action on a held
			 * or ignored signal, unless process is traced.
E 59
I 59
			 * Masking above should prevent us ever trying
			 * to take action on an ignored signal other
			 * than SIGCONT, unless process is traced.
E 59
			 */
D 59
			if ((p->p_flag&STRC) == 0)
E 59
I 59
D 77
			if (sig != SIGCONT && (p->p_flag&STRC) == 0)
E 77
I 77
D 113
			if ((prop & SA_CONT) == 0 && (p->p_flag&STRC) == 0)
E 113
I 113
D 118
			if ((prop & SA_CONT) == 0 && (p->p_flag & STRC) == 0)
E 113
E 77
E 59
				printf("issig\n");
E 118
I 118
			if ((prop & SA_CONT) == 0 &&
			    (p->p_flag & P_TRACED) == 0)
				printf("issignal\n");
E 118
D 60
			continue;
E 60
I 60
			break;		/* == ignore */
E 60

		default:
			/*
			 * This signal has an action, let
D 118
			 * psig process it.
E 118
I 118
			 * postsig() process it.
E 118
			 */
D 60
			goto send;
E 60
I 60
D 116
			return (sig);
E 116
I 116
			return (signum);
E 116
E 60
		}
D 60
		/*NOTREACHED*/
E 60
I 60
D 118
		p->p_sig &= ~mask;		/* take the signal! */
E 118
I 118
		p->p_siglist &= ~mask;		/* take the signal! */
E 118
E 60
	}
D 60
	/*
	 * Didn't find a signal to send.
	 */
	p->p_cursig = 0;
	return (0);

send:
	/*
	 * Let psig process the signal.
	 */
	return (sig);
E 60
I 60
	/* NOTREACHED */
E 60
}

D 2
#ifndef vax
ffs(mask)
	register long mask;
{
	register int i;

	for(i=1; i<NSIG; i++) {
		if (mask & 1)
			return (i);
		mask >>= 1;
	}
	return (0);
}
#endif

E 2
/*
D 116
 * Put the argument process into the stopped
D 38
 * state and notify the parent via wakeup and/or signal.
E 38
I 38
 * state and notify the parent via wakeup.
 * Signals are handled elsewhere.
I 60
 * The process must not be on the run queue.
E 116
I 116
 * Put the argument process into the stopped state and notify the parent
 * via wakeup.  Signals are handled elsewhere.  The process must not be
 * on the run queue.
E 116
E 60
E 38
 */
I 127
void
E 127
stop(p)
	register struct proc *p;
{

	p->p_stat = SSTOP;
D 118
	p->p_flag &= ~SWTED;
E 118
I 118
	p->p_flag &= ~P_WAITED;
E 118
	wakeup((caddr_t)p->p_pptr);
D 38
	/*
	 * Avoid sending signal to parent if process is traced
	 */
	if (p->p_flag&STRC)
		return;
	psignal(p->p_pptr, SIGCHLD);
E 38
}

/*
D 60
 * Perform the action specified by
 * the current signal.
E 60
I 60
D 77
 * Perform the action specified by the current signal.
E 60
 * The usual sequence is:
D 59
 *	if (issig())
E 59
I 59
D 60
 *	if (p->p_cursig || ISSIG(p))
E 59
 *		psig();
 * The signal bit has already been cleared by issig,
 * and the current signal number stored in p->p_cursig.
E 60
I 60
 *	if (sig = CURSIG(p))
 *		psig(sig);
E 77
I 77
 * Take the action for the specified signal
 * from the current set of pending signals.
E 77
E 60
 */
I 77
void
E 77
I 76
D 78
#if defined(i386)
psig(sig, flags)
#else
E 78
E 76
D 60
psig()
E 60
I 60
D 116
psig(sig)
I 76
D 78
#endif
E 78
E 76
	register int sig;
E 116
I 116
D 118
psig(signum)
E 118
I 118
postsig(signum)
E 118
	register int signum;
E 116
E 60
{
D 20
	register struct proc *rp = u.u_procp;
	register int n = rp->p_cursig;
	long sigmask = 1L << (n-1);
E 20
I 20
D 77
	register struct proc *p = u.u_procp;
D 59
	register int sig = p->p_cursig;
D 33
	int sigmask = 1 << (sig - 1), returnmask;
E 33
I 33
	int mask = sigmask(sig), returnmask;
E 33
E 20
	register int (*action)();
E 59
I 59
D 60
	register int sig;
E 60
	int mask, returnmask;
E 77
I 77
	register struct proc *p = curproc;
	register struct sigacts *ps = p->p_sigacts;
E 77
	register sig_t action;
I 77
D 121
	int mask, returnmask;
E 121
I 121
D 127
	int code, mask, returnmask;
E 127
I 127
	u_long code;
	int mask, returnmask;
E 127
E 121
E 77
E 59

D 20
	if (rp->p_cursig == 0)
E 20
I 20
D 59
	if (sig == 0)
E 20
		panic("psig");
D 20
	action = u.u_signal[n];
E 20
I 20
	action = u.u_signal[sig];
E 20
	if (action != SIG_DFL) {
D 20
		if (action == SIG_IGN || action == SIG_HOLD)
E 20
I 20
D 33
		if (action == SIG_IGN || (p->p_sigmask & sigmask))
E 33
I 33
		if (action == SIG_IGN || (p->p_sigmask & mask))
E 33
E 20
			panic("psig action");
		u.u_error = 0;
D 20
		if (n != SIGILL && n != SIGTRAP)
			u.u_signal[n] = 0;
E 20
		/*
D 20
		 * If this catch value indicates automatic holding of
		 * subsequent signals, set the hold value.
E 20
I 20
		 * Set the new mask value and also defer further
		 * occurences of this signal (unless we're simulating
		 * the old signal facilities). 
		 *
		 * Special case: user has done a sigpause.  Here the
		 * current mask is not of interest, but rather the
		 * mask from before the sigpause is what we want restored
		 * after the signal processing is completed.
E 20
		 */
D 20
		if (SIGISDEFER(action)) {
			(void) spl6();
D 17
			if ((int)SIG_HOLD & 1)
				rp->p_siga0 |= sigmask;
			else
				rp->p_siga0 &= ~sigmask;
			if ((int)SIG_HOLD & 2)
				rp->p_siga1 |= sigmask;
			else
				rp->p_siga1 &= ~sigmask;
E 17
I 17
			/* SIG_HOLD known to be 3 */
			rp->p_siga0 |= sigmask;
			rp->p_siga1 |= sigmask;
E 17
			u.u_signal[n] = SIG_HOLD;
			(void) spl0();
			action = SIGUNDEFER(action);
E 20
I 20
D 33
		(void) spl6();
E 33
I 33
		(void) splhigh();
E 33
		if (p->p_flag & SOUSIG) {
			if (sig != SIGILL && sig != SIGTRAP) {
				u.u_signal[sig] = SIG_DFL;
D 33
				p->p_sigcatch &= ~sigmask;
E 33
I 33
				p->p_sigcatch &= ~mask;
E 33
			}
D 33
			sigmask = 0;
E 33
I 33
			mask = 0;
E 59
I 59
D 77
	do {
E 77
D 60
		sig = p->p_cursig;
		mask = sigmask(sig);
E 60
I 60
#ifdef DIAGNOSTIC
E 60
D 77
		if (sig == 0)
			panic("psig");
E 77
I 77
D 116
	if (sig == 0)
E 116
I 116
	if (signum == 0)
E 116
D 118
		panic("psig");
E 118
I 118
		panic("postsig");
E 118
E 77
I 60
#endif
D 77
		mask = sigmask(sig);
		p->p_sig &= ~mask;
E 60
		action = u.u_signal[sig];
E 77
I 77
D 116
	mask = sigmask(sig);
E 116
I 116
	mask = sigmask(signum);
E 116
D 118
	p->p_sig &= ~mask;
E 118
I 118
	p->p_siglist &= ~mask;
E 118
D 116
	action = ps->ps_sigact[sig];
E 116
I 116
	action = ps->ps_sigact[signum];
E 116
E 77
I 60
#ifdef KTRACE
D 77
		if (KTRPOINT(p, KTR_PSIG))
			ktrpsig(p->p_tracep, sig, action, p->p_flag & SOMASK ?
				u.u_oldmask : p->p_sigmask, 0);
E 77
I 77
	if (KTRPOINT(p, KTR_PSIG))
D 94
		ktrpsig(p->p_tracep, sig, action, ps->ps_flags & SA_OLDMASK ?
E 94
I 94
D 116
		ktrpsig(p->p_tracep, sig, action, ps->ps_flags & SAS_OLDMASK ?
E 116
I 116
		ktrpsig(p->p_tracep,
		    signum, action, ps->ps_flags & SAS_OLDMASK ?
E 116
E 94
		    ps->ps_oldmask : p->p_sigmask, 0);
E 77
#endif
E 60
D 77
		if (action != SIG_DFL) {
E 77
I 77
	if (action == SIG_DFL) {
		/*
		 * Default action, where the default is to kill
		 * the process.  (Other cases were ignored above.)
D 78
		 * Mark the accounting record with the signal termination.
		 * If dumping core, save the signal number for the debugger.
E 78
		 */
D 78
		p->p_acflag |= AXSIG;
		if (sigprop[sig] & SA_CORE) {
			ps->ps_sig = sig;
			if (coredump(p) == 0)
				sig |= WCOREFLAG;
		}
		exit(p, W_EXITCODE(0, sig));
E 78
I 78
D 116
		sigexit(p, sig);
E 116
I 116
		sigexit(p, signum);
E 116
E 78
		/* NOTREACHED */
	} else {
		/*
		 * If we get here, the signal must be caught.
		 */
E 77
#ifdef DIAGNOSTIC
D 77
			if (action == SIG_IGN || (p->p_sigmask & mask))
				panic("psig action");
E 77
I 77
		if (action == SIG_IGN || (p->p_sigmask & mask))
D 118
			panic("psig action");
E 118
I 118
			panic("postsig action");
E 118
E 77
#endif
D 71
			u.u_error = 0;
E 71
D 77
			/*
			 * Set the new mask value and also defer further
			 * occurences of this signal.
			 *
			 * Special case: user has done a sigpause.  Here the
			 * current mask is not of interest, but rather the
			 * mask from before the sigpause is what we want
			 * restored after the signal processing is completed.
			 */
			(void) splhigh();
			if (p->p_flag & SOMASK) {
				returnmask = u.u_oldmask;
				p->p_flag &= ~SOMASK;
			} else
				returnmask = p->p_sigmask;
			p->p_sigmask |= u.u_sigmask[sig] | mask;
			(void) spl0();
			u.u_ru.ru_nsignals++;
E 77
I 77
		/*
		 * Set the new mask value and also defer further
		 * occurences of this signal.
		 *
		 * Special case: user has done a sigpause.  Here the
		 * current mask is not of interest, but rather the
		 * mask from before the sigpause is what we want
		 * restored after the signal processing is completed.
		 */
		(void) splhigh();
D 94
		if (ps->ps_flags & SA_OLDMASK) {
E 94
I 94
		if (ps->ps_flags & SAS_OLDMASK) {
E 94
			returnmask = ps->ps_oldmask;
D 94
			ps->ps_flags &= ~SA_OLDMASK;
E 94
I 94
			ps->ps_flags &= ~SAS_OLDMASK;
E 94
		} else
			returnmask = p->p_sigmask;
D 116
		p->p_sigmask |= ps->ps_catchmask[sig] | mask;
E 116
I 116
		p->p_sigmask |= ps->ps_catchmask[signum] | mask;
E 116
		(void) spl0();
		p->p_stats->p_ru.ru_nsignals++;
E 77
I 76
D 78
#if	defined(i386)
D 77
			sendsig(action, sig, returnmask, 0, flags);
E 77
I 77
		sendsig(action, sig, returnmask, 0, flags);
E 77
#else
E 78
E 76
D 77
			sendsig(action, sig, returnmask, 0);
E 77
I 77
D 116
		sendsig(action, sig, returnmask, 0);
E 116
I 116
D 121
		sendsig(action, signum, returnmask, 0);
E 121
I 121
		if (ps->ps_sig != signum) {
			code = 0;
		} else {
			code = ps->ps_code;
			ps->ps_code = 0;
I 122
			ps->ps_sig = 0;
E 122
		}
		sendsig(action, signum, returnmask, code);
E 121
E 116
E 77
I 76
D 78
#endif
E 78
E 76
D 60
			p->p_cursig = 0;
E 60
D 77
			continue;
E 59
E 33
E 20
		}
I 20
D 59
		if (p->p_flag & SOMASK) {
			returnmask = u.u_oldmask;
			p->p_flag &= ~SOMASK;
		} else
			returnmask = p->p_sigmask;
D 21
		p->p_sigmask = u.u_sigmask[sig] | sigmask;
E 21
I 21
D 33
		p->p_sigmask |= u.u_sigmask[sig] | sigmask;
E 33
I 33
		p->p_sigmask |= u.u_sigmask[sig] | mask;
E 33
E 21
		(void) spl0();
E 20
I 5
		u.u_ru.ru_nsignals++;
E 5
D 20
		sendsig(action, n);
		rp->p_cursig = 0;
E 20
I 20
		sendsig(action, sig, returnmask);
		p->p_cursig = 0;
E 20
		return;
	}
	u.u_acflag |= AXSIG;
D 20
	switch (n) {
E 20
I 20
	switch (sig) {
E 59
I 59
		u.u_acflag |= AXSIG;
		switch (sig) {
E 59
E 20

D 59
	case SIGILL:
	case SIGIOT:
	case SIGBUS:
	case SIGQUIT:
	case SIGTRAP:
	case SIGEMT:
	case SIGFPE:
	case SIGSEGV:
	case SIGSYS:
D 20
		u.u_arg[0] = n;
E 20
I 20
		u.u_arg[0] = sig;
E 20
D 53
		if (core())
E 53
I 53
		if (core() == 0)
E 53
D 20
			n += 0200;
E 20
I 20
			sig += 0200;
E 20
	}
D 20
	exit(n);
E 20
I 20
	exit(sig);
E 59
I 59
		case SIGILL:
		case SIGIOT:
		case SIGBUS:
		case SIGQUIT:
		case SIGTRAP:
		case SIGEMT:
		case SIGFPE:
		case SIGSEGV:
		case SIGSYS:
D 71
			u.u_arg[0] = sig;
E 71
I 71
			u.u_sig = sig;
E 71
			if (core() == 0)
				sig |= WCOREFLAG;
		}
D 69
		exit(W_EXITCODE(0, sig));
E 69
I 69
		exit(p, W_EXITCODE(0, sig));
E 69
		/* NOTREACHED */
D 60
	} while (ISSIG(p));
E 60
I 60
	} while (sig = CURSIG(p));
E 77
I 77
	}
I 110
}

/*
 * Kill the current process for stated reason.
 */
I 127
void
E 127
killproc(p, why)
	struct proc *p;
	char *why;
{

	log(LOG_ERR, "pid %d was killed: %s\n", p->p_pid, why);
	uprintf("sorry, pid %d was killed: %s\n", p->p_pid, why);
	psignal(p, SIGKILL);
E 110
E 77
E 60
E 59
E 20
}

D 17
#ifdef unneeded
int	corestop = 0;
#endif
E 17
/*
I 78
D 116
 * Force the current process to exit with the specified
 * signal, dumping core if appropriate.  We bypass the normal
 * tests for masked and caught signals, allowing unrecoverable
 * failures to terminate the process without changing signal state.
 * Mark the accounting record with the signal termination.
 * If dumping core, save the signal number for the debugger.
 * Calls exit and does not return.
E 116
I 116
 * Force the current process to exit with the specified signal, dumping core
 * if appropriate.  We bypass the normal tests for masked and caught signals,
 * allowing unrecoverable failures to terminate the process without changing
 * signal state.  Mark the accounting record with the signal termination.
 * If dumping core, save the signal number for the debugger.  Calls exit and
 * does not return.
E 116
 */
I 127
void
E 127
D 116
sigexit(p, sig)
E 116
I 116
sigexit(p, signum)
E 116
	register struct proc *p;
D 116
	int sig;
E 116
I 116
	int signum;
E 116
{

	p->p_acflag |= AXSIG;
D 116
	if (sigprop[sig] & SA_CORE) {
		p->p_sigacts->ps_sig = sig;
E 116
I 116
	if (sigprop[signum] & SA_CORE) {
		p->p_sigacts->ps_sig = signum;
E 116
		if (coredump(p) == 0)
D 116
			sig |= WCOREFLAG;
E 116
I 116
			signum |= WCOREFLAG;
E 116
	}
D 111
	exit(p, W_EXITCODE(0, sig));
E 111
I 111
D 116
	exit1(p, W_EXITCODE(0, sig));
E 116
I 116
	exit1(p, W_EXITCODE(0, signum));
E 116
E 111
	/* NOTREACHED */
}

/*
E 78
D 59
 * Create a core image on the file "core"
 * If you are looking for protection glitches,
 * there are probably a wealth of them here
 * when this occurs to a suid command.
 *
E 59
I 59
D 77
 * Create a core image on the file "core".
E 59
 * It writes UPAGES block of the
 * user.h area followed by the entire
 * data+stack segments.
E 77
I 77
D 116
 * Create a core dump.
D 82
 * The file name should probably be "core.progname"
 * (or "mos.progname", or "dram.progname", or ...).
 * Core dumps aren't created if the process 
E 82
I 82
D 85
 * The file name is "core.progname.pid".
E 85
I 85
 * The file name is "core.progname".
E 85
 * Core dumps are not created if the process is setuid.
E 116
I 116
D 120
 * Dump core, into a file named "core.progname".
 * Do not drop core if the process was setuid/setgid.
E 120
I 120
 * Dump core, into a file named "progname.core", unless the process was
 * setuid/setgid.
E 120
E 116
E 82
E 77
 */
I 127
int
E 127
D 77
core()
E 77
I 77
coredump(p)
	register struct proc *p;
E 77
{
I 103
D 106
	USES_VOP_GETATTR;
	USES_VOP_SETATTR;
	USES_VOP_UNLOCK;
E 106
E 103
D 53
	register struct inode *ip;
E 53
I 53
D 56
	register struct vnode *vp, *dvp;
E 56
I 56
	register struct vnode *vp;
I 59
D 77
	register struct proc *p = u.u_procp;
E 59
E 56
E 53
D 30
	extern schar();
E 30
I 30
	register struct nameidata *ndp = &u.u_nd;
E 77
I 77
	register struct pcred *pcred = p->p_cred;
	register struct ucred *cred = pcred->pc_ucred;
	register struct vmspace *vm = p->p_vmspace;
I 120
	struct nameidata nd;
E 120
E 77
I 53
	struct vattr vattr;
D 83
	int error;
E 83
I 83
	int error, error1;
E 83
I 77
D 120
	struct nameidata nd;
E 120
I 82
D 85
	char name[MAXCOMLEN+12];	/* core.progname.pid */
E 85
I 85
D 116
	char name[MAXCOMLEN+6];	/* core.progname */
E 116
I 116
	char name[MAXCOMLEN+6];		/* progname.core */
E 116
E 85
E 82
E 77
E 53
E 30

D 17
#ifdef unneeded
	if (corestop) {
		int i;
		for (i = 0; i < 10; i++)
			if (u.u_comm[i])
				putchar(u.u_comm[i], 0);
		printf(", uid %d\n", u.u_uid);
		if (corestop&2)
			asm("halt");
	}
#endif
E 17
D 16
	if (u.u_uid != u.u_ruid)
E 16
I 16
D 59
	if (u.u_uid != u.u_ruid || u.u_gid != u.u_rgid)
E 59
I 59
D 77
	if (p->p_svuid != p->p_ruid || p->p_svgid != p->p_rgid)
E 77
I 77
D 116
	if (pcred->p_svuid != pcred->p_ruid ||
	    pcred->p_svgid != pcred->p_rgid)
E 116
I 116
	if (pcred->p_svuid != pcred->p_ruid || pcred->p_svgid != pcred->p_rgid)
E 116
E 77
E 59
E 16
D 4
		return;
E 4
I 4
D 53
		return (0);
E 4
D 5
	if (ctob(UPAGES+u.u_dsize+u.u_ssize) >= u.u_limit[LIM_CORE])
E 5
I 5
	if (ctob(UPAGES+u.u_dsize+u.u_ssize) >=
E 53
I 53
		return (EFAULT);
D 77
	if (ctob(UPAGES + u.u_dsize + u.u_ssize) >=
E 53
	    u.u_rlimit[RLIMIT_CORE].rlim_cur)
E 77
I 77
	if (ctob(UPAGES + vm->vm_dsize + vm->vm_ssize) >=
	    p->p_rlimit[RLIMIT_CORE].rlim_cur)
E 77
E 5
D 53
		return (0);
I 42
	if (u.u_procp->p_textp && access(u.u_procp->p_textp->x_iptr, IREAD))
		return (0);
E 42
	u.u_error = 0;
D 30
	u.u_dirp = "core";
D 12
	ip = namei(schar, 1, 1);
E 12
I 12
	ip = namei(schar, CREATE, 1);
E 30
I 30
	ndp->ni_nameiop = CREATE | FOLLOW;
E 53
I 53
		return (EFAULT);
I 82
D 85
	sprintf(name, "core.%s.%d", p->p_comm, p->p_pid);
E 85
I 85
D 116
	sprintf(name, "core.%s", p->p_comm);
E 116
I 116
	sprintf(name, "%s.core", p->p_comm);
E 116
E 85
D 91
	nd.ni_dirp = name;
E 82
D 59
	if (u.u_procp->p_textp) {
D 56
		vop_lock(u.u_procp->p_textp->x_vptr);
E 56
I 56
		VOP_LOCK(u.u_procp->p_textp->x_vptr);
E 56
D 58
		error = vn_access(u.u_procp->p_textp->x_vptr, VREAD, u.u_cred);
E 58
I 58
		error = VOP_ACCESS(u.u_procp->p_textp->x_vptr, VREAD, u.u_cred);
E 58
D 56
		vop_unlock(u.u_procp->p_textp->x_vptr);
E 56
I 56
		VOP_UNLOCK(u.u_procp->p_textp->x_vptr);
E 59
I 59
D 75
	if (p->p_textp) {
		VOP_LOCK(p->p_textp->x_vptr);
		error = VOP_ACCESS(p->p_textp->x_vptr, VREAD, u.u_cred);
		VOP_UNLOCK(p->p_textp->x_vptr);
E 59
E 56
		if (error)
			return (EFAULT);
	}
E 75
E 53
D 77
	ndp->ni_segflg = UIO_SYSSPACE;
	ndp->ni_dirp = "core";
D 53
	ip = namei(ndp);
E 30
E 12
	if (ip == NULL) {
		if (u.u_error)
			return (0);
D 16
		ip = maknode(0666);
E 16
I 16
D 30
		ip = maknode(0644);
E 30
I 30
		ip = maknode(0644, ndp);
E 30
E 16
		if (ip==NULL)
			return (0);
	}
D 4
	if (!access(ip, IWRITE) &&
	   (ip->i_mode&IFMT) == IFREG &&
	   ip->i_nlink == 1) {
D 3
		itrunc(ip);
E 3
I 3
		itrunc(ip, 0);
E 3
		u.u_acflag |= ACORE;
		u.u_offset = 0;
		u.u_base = (caddr_t)&u;
		u.u_count = ctob(UPAGES);
		u.u_segflg = 1;
		writei(ip);
		u.u_base = (char *)ctob(u.u_tsize);
		u.u_count = ctob(u.u_dsize);
		u.u_segflg = 0;
		writei(ip);
		u.u_base = (char *)(USRSTACK - ctob(u.u_ssize));
		u.u_count = ctob(u.u_ssize);
		writei(ip);
	} else
E 4
I 4
	if (access(ip, IWRITE) ||
	   (ip->i_mode&IFMT) != IFREG ||
	   ip->i_nlink != 1) {
E 4
		u.u_error = EFAULT;
E 53
I 53
	if (error = vn_open(ndp, FCREAT|FWRITE, 0644))
E 77
I 77
	nd.ni_segflg = UIO_SYSSPACE;
I 90
	nd.ni_cnd.cn_proc = p;
E 90
D 82
	nd.ni_dirp = "core";
E 82
D 81
	if (error = vn_open(&nd, p, FCREAT|FWRITE, 0644))
E 81
I 81
	if (error = vn_open(&nd, p, O_CREAT|FWRITE, 0644))
E 91
I 91
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_SYSSPACE, name, p);
D 116
	if (error = vn_open(&nd, O_CREAT|FWRITE, 0644))
E 116
I 116
	if (error = vn_open(&nd,
	    O_CREAT | FWRITE, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
E 116
E 91
E 81
E 77
		return (error);
D 77
	vp = ndp->ni_vp;
E 77
I 77
	vp = nd.ni_vp;
E 77
I 57
D 81
	VOP_LOCK(vp);
E 81
E 57
D 77
	if (vp->v_type != VREG ||
D 56
	    vop_getattr(vp, &vattr, u.u_cred) ||
E 56
I 56
	    VOP_GETATTR(vp, &vattr, u.u_cred) ||
E 77
I 77
D 79
	if (vp->v_type != VREG || VOP_GETATTR(vp, &vattr, cred) ||
E 79
I 79
D 116
	if (vp->v_type != VREG || VOP_GETATTR(vp, &vattr, cred, p) ||
E 79
E 77
E 56
	    vattr.va_nlink != 1) {
E 116
I 116

	/* Don't dump to non-regular files or files with links. */
	if (vp->v_type != VREG ||
	    VOP_GETATTR(vp, &vattr, cred, p) || vattr.va_nlink != 1) {
E 116
D 57
		error = EFAULT;
E 53
I 4
		goto out;
E 57
I 57
D 83
		vput(vp);
		return (EFAULT);
E 83
I 83
		error = EFAULT;
		goto out;
E 83
E 57
	}
I 50
D 63
#ifdef MMAP
	{ register int fd;
D 57
	/* unmasp funky devices in the user's address space */
E 57
I 57
	/* unmap funky devices in the user's address space */
E 57
	for (fd = 0; fd < u.u_lastfile; fd++)
		if (u.u_ofile[fd] && (u.u_pofile[fd] & UF_MAPPED))
			munmapfd(fd);
	}
E 63
I 63
D 75
#ifdef MAPMEM
D 69
	mmcore();
E 69
I 69
	if (error = mmcore(p)) {
		vput(vp);
		return (error);
	}
E 69
E 63
#endif
E 75
E 50
D 12
	itrunc(ip, 0);
E 12
I 12
D 53
	itrunc(ip, (u_long)0);
E 53
I 53
D 61
	vattr_null(&vattr);
E 61
I 61
	VATTR_NULL(&vattr);
E 61
	vattr.va_size = 0;
I 89
D 123
	LEASE_CHECK(vp, p, cred, LEASE_WRITE);
E 123
I 123
	VOP_LEASE(vp, p, cred, LEASE_WRITE);
E 123
E 89
D 56
	vop_setattr(vp, &vattr, u.u_cred);
E 56
I 56
D 77
	VOP_SETATTR(vp, &vattr, u.u_cred);
E 56
E 53
E 12
	u.u_acflag |= ACORE;
E 77
I 77
D 79
	VOP_SETATTR(vp, &vattr, cred);
E 79
I 79
	VOP_SETATTR(vp, &vattr, cred, p);
E 79
	p->p_acflag |= ACORE;
I 78
D 80
	bcopy(p, &u.u_kproc.kp_proc, sizeof(struct proc));
	fill_eproc(p, &u.u_kproc.kp_eproc);
E 80
I 80
	bcopy(p, &p->p_addr->u_kproc.kp_proc, sizeof(struct proc));
	fill_eproc(p, &p->p_addr->u_kproc.kp_eproc);
E 80
E 78
E 77
I 63
D 93
#ifdef HPUXCOMPAT
	/*
	 * BLETCH!  If we loaded from an HPUX format binary file
	 * we have to dump an HPUX style user struct so that the
	 * HPUX debuggers can grok it.
	 */
D 80
	if (u.u_pcb.pcb_flags & PCB_HPUXBIN)
E 80
I 80
	if (p->p_addr->u_pcb.pcb_flags & PCB_HPUXBIN)
E 80
D 77
		error = hpuxdumpu(vp, ndp->ni_cred);
E 77
I 77
		error = hpuxdumpu(vp, cred);
E 77
	else
#endif
E 63
D 9
	u.u_error =rdwri(UIO_WRITE, ip,
E 9
I 9
D 11
	u.u_error = rdwri(UIO_WRITE, ip,
E 9
	    (caddr_t)&u, ctob(UPAGES),
	    0, 1, (int *)0);
E 11
I 11
D 20
	/* if (u.u_error == 0) */
		u.u_error = rdwri(UIO_WRITE, ip,
		    (caddr_t)&u,
		    ctob(UPAGES),
		    0, 1, (int *)0);
E 20
I 20
D 53
	u.u_error = rdwri(UIO_WRITE, ip,
	    (caddr_t)&u,
	    ctob(UPAGES),
D 47
	    0, 1, (int *)0);
E 47
I 47
	    (off_t)0, 1, (int *)0);
E 47
E 20
E 11
D 6
	if (u.u_error)
E 6
I 6
	if (u.u_error == 0)
E 6
D 9
	rdwri(UIO_WRITE, ip,
	    (caddr_t)ctob(u.u_tsize), ctob(u.u_dsize),
	    ctob(UPAGES), 0, (int *)0);
E 9
I 9
		u.u_error = rdwri(UIO_WRITE, ip,
E 53
I 53
D 79
	error = vn_rdwr(UIO_WRITE, vp, (caddr_t)&u, ctob(UPAGES), (off_t)0,
D 56
	    UIO_SYSSPACE, IO_UNIT, (int *)0);
E 56
I 56
D 57
	    UIO_SYSSPACE, IO_UNIT, ndp->ni_cred, (int *)0);
E 57
I 57
D 77
	    UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, ndp->ni_cred, (int *)0);
E 77
I 77
	    UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *)0);
E 79
I 79
D 80
	error = vn_rdwr(UIO_WRITE, vp, (caddr_t)&p->p_addr, ctob(UPAGES),
	    (off_t)0, UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *)0,
	    (struct proc *)0);
E 80
I 80
	error = vn_rdwr(UIO_WRITE, vp, (caddr_t) p->p_addr, ctob(UPAGES),
	    (off_t)0, UIO_SYSSPACE, IO_NODELOCKED|IO_UNIT, cred, (int *) NULL,
	    p);
E 93
I 93
	error = cpu_coredump(p, vp, cred);
E 93
E 80
E 79
E 77
E 57
E 56
	if (error == 0)
D 75
		error = vn_rdwr(UIO_WRITE, vp,
E 53
D 11
		    (caddr_t)ctob(u.u_tsize), ctob(u.u_dsize),
E 11
I 11
D 59
		    (caddr_t)ctob(dptov(u.u_procp, 0)),
E 59
I 59
		    (caddr_t)ctob(dptov(p, 0)),
E 75
I 75
D 77
		error = vn_rdwr(UIO_WRITE, vp, u.u_daddr,
E 75
E 59
D 47
		    ctob(u.u_dsize),
E 11
		    ctob(UPAGES), 0, (int *)0);
E 47
I 47
D 53
		    (int)ctob(u.u_dsize),
		    (off_t)ctob(UPAGES), 0, (int *)0);
E 47
E 9
D 6
	if (u.u_error)
E 6
I 6
	if (u.u_error == 0)
E 6
D 9
	rdwri(UIO_WRITE, ip,
	    (caddr_t)(USRSTACK-ctob(u.u_ssize)), ctob(u.u_ssize),
	    ctob(UPAGES)+ctob(u.u_dsize), 0, (int *)0);
E 9
I 9
		u.u_error = rdwri(UIO_WRITE, ip,
E 53
I 53
D 57
		    (int)ctob(u.u_dsize), (off_t)ctob(UPAGES),
D 56
		    UIO_USERSPACE, IO_UNIT, (int *)0);
E 56
I 56
		    UIO_USERSPACE, IO_UNIT, ndp->ni_cred, (int *)0);
E 57
I 57
		    (int)ctob(u.u_dsize), (off_t)ctob(UPAGES), UIO_USERSPACE,
		    IO_NODELOCKED|IO_UNIT, ndp->ni_cred, (int *)0);
E 77
I 77
		error = vn_rdwr(UIO_WRITE, vp, vm->vm_daddr,
		    (int)ctob(vm->vm_dsize), (off_t)ctob(UPAGES), UIO_USERSPACE,
D 79
		    IO_NODELOCKED|IO_UNIT, cred, (int *)0);
E 79
I 79
D 80
		    IO_NODELOCKED|IO_UNIT, cred, (int *)0, p);
E 80
I 80
		    IO_NODELOCKED|IO_UNIT, cred, (int *) NULL, p);
E 80
E 79
E 77
E 57
E 56
	if (error == 0)
		error = vn_rdwr(UIO_WRITE, vp,
E 53
D 11
		    (caddr_t)(USRSTACK-ctob(u.u_ssize)), ctob(u.u_ssize),
E 11
I 11
D 59
		    (caddr_t)ctob(sptov(u.u_procp, u.u_ssize - 1)),
E 59
I 59
D 75
		    (caddr_t)ctob(sptov(p, u.u_ssize - 1)),
E 59
D 47
		    ctob(u.u_ssize),
E 11
		    ctob(UPAGES)+ctob(u.u_dsize), 0, (int *)0);
E 47
I 47
		    (int)ctob(u.u_ssize),
E 75
I 75
D 77
		    trunc_page(USRSTACK - ctob(u.u_ssize)),
		    round_page(ctob(u.u_ssize)),
E 75
D 53
		    (off_t)ctob(UPAGES)+ctob(u.u_dsize), 0, (int *)0);
E 53
I 53
D 57
		    (off_t)ctob(UPAGES) + ctob(u.u_dsize),
D 56
		    UIO_USERSPACE, IO_UNIT, (int *)0);
E 56
I 56
		    UIO_USERSPACE, IO_UNIT, ndp->ni_cred, (int *)0);
E 56
E 53
E 47
E 9
out:
E 4
D 53
	iput(ip);
D 4
	return (u.u_error==0);
E 4
I 4
	return (u.u_error == 0);
E 53
I 53
	if (vp)
		vrele(vp);
E 57
I 57
		    (off_t)ctob(UPAGES) + ctob(u.u_dsize), UIO_USERSPACE,
		    IO_NODELOCKED|IO_UNIT, ndp->ni_cred, (int *)0);
E 77
I 77
D 80
		    trunc_page(USRSTACK - ctob(vm->vm_ssize)),
E 80
I 80
		    (caddr_t) trunc_page(USRSTACK - ctob(vm->vm_ssize)),
E 80
		    round_page(ctob(vm->vm_ssize)),
		    (off_t)ctob(UPAGES) + ctob(vm->vm_dsize), UIO_USERSPACE,
D 79
		    IO_NODELOCKED|IO_UNIT, cred, (int *)0);
E 79
I 79
D 80
		    IO_NODELOCKED|IO_UNIT, cred, (int *)0, p);
E 80
I 80
		    IO_NODELOCKED|IO_UNIT, cred, (int *) NULL, p);
E 80
E 79
E 77
D 83
	vput(vp);
E 83
I 83
out:
D 128
	VOP_UNLOCK(vp);
E 128
I 128
	VOP_UNLOCK(vp, 0, p);
E 128
	error1 = vn_close(vp, FWRITE, cred, p);
D 85
	if (!error)
E 85
I 85
	if (error == 0)
E 85
		error = error1;
E 83
E 57
	return (error);
I 59
}

/*
 * Nonexistent system call-- signal process (may want to handle it).
 * Flag error in case process won't see signal immediately (blocked or ignored).
 */
I 108
D 126
struct nosys_args {
	int	dummy;
};
E 126
E 108
D 70
nosys()
E 70
I 70
/* ARGSUSED */
I 126
int
E 126
nosys(p, args, retval)
	struct proc *p;
D 108
	void *args;
E 108
I 108
D 126
	struct nosys_args *args;
E 108
	int *retval;
E 126
I 126
	void *args;
	register_t *retval;
E 126
E 70
{

D 70
	psignal(u.u_procp, SIGSYS);
	u.u_error = EINVAL;
E 70
I 70
	psignal(p, SIGSYS);
D 72
	RETURN (EINVAL);
E 72
I 72
D 125
	return (EINVAL);
E 125
I 125
	return (ENOSYS);
E 125
E 72
E 70
E 59
E 53
E 4
}
I 4
D 7

E 4
D 2

E 2
/*
D 2
 * grow the stack to include the SP
 * true return if successful.
E 2
I 2
 * alarm clock signal
E 2
 */
D 2
grow(sp)
	unsigned sp;
E 2
I 2
oalarm()
E 2
{
D 2
	register si;

	if (sp >= USRSTACK-ctob(u.u_ssize))
		return (0);
	si = clrnd(btoc((USRSTACK-sp)) - u.u_ssize + SINCR);
	if (ctob(u.u_ssize+si) > u.u_limit[LIM_STACK])
		return (0);
	if (chksize(u.u_tsize, u.u_dsize, u.u_ssize+si))
		return (0);
	if (swpexpand(u.u_dsize, u.u_ssize+si, &u.u_dmap, &u.u_smap)==0)
		return (0);
	
	expand(si, P1BR);
	return (1);
}

/*
 * sys-trace system call.
 */
ptrace()
{
E 2
D 5
	register struct proc *p;
I 2
	register c;
E 5
E 2
	register struct a {
D 2
		int	req;
		int	pid;
		int	*addr;
		int	data;
E 2
I 2
		int	deltat;
E 2
D 5
	} *uap;
E 5
I 5
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
	int s = spl7();
E 5

D 5
	uap = (struct a *)u.u_ap;
D 2
	if (uap->req <= 0) {
		u.u_procp->p_flag |= STRC;
		return;
	}
	p = pfind(uap->pid);
	if (p == 0 || p->p_stat != SSTOP || p->p_ppid != u.u_procp->p_pid) {
		u.u_error = ESRCH;
		return;
	}
	while (ipc.ip_lock)
		sleep((caddr_t)&ipc, IPCPRI);
	ipc.ip_lock = p->p_pid;
	ipc.ip_data = uap->data;
	ipc.ip_addr = uap->addr;
	ipc.ip_req = uap->req;
	p->p_flag &= ~SWTED;
	while (ipc.ip_req > 0) {
		if (p->p_stat==SSTOP)
			setrun(p);
		sleep((caddr_t)&ipc, IPCPRI);
	}
	u.u_r.r_val1 = ipc.ip_data;
	if (ipc.ip_req < 0)
		u.u_error = EIO;
	ipc.ip_lock = 0;
	wakeup((caddr_t)&ipc);
E 2
I 2
	p = u.u_procp;
	c = p->p_clktim;
	p->p_clktim = uap->deltat;
	u.u_r.r_val1 = c;
E 5
I 5
D 6
	p->p_realtimer.itimer_reload = 0;
	u.u_r.r_val1 = p->p_realtimer.itimer_value.tv_sec;
	p->p_realtimer.itimer_value.tv_sec = uap->deltat;
	p->p_realtimer.itimer_value.tv_usec = 0;
E 6
I 6
	timerclear(&p->p_realtimer.it_interval);
	u.u_r.r_val1 = p->p_realtimer.it_value.tv_sec;
	p->p_realtimer.it_value.tv_sec = uap->deltat;
	p->p_realtimer.it_value.tv_usec = 0;
E 6
	splx(s);
E 5
E 2
}

D 2
int ipcreg[] = {R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,AP,FP,SP,PC};
E 2
/*
D 2
 * Code that the child process
 * executes to implement the command
 * of the parent process in tracing.
E 2
I 2
 * indefinite wait.
 * no one should wakeup(&u)
E 2
 */
D 2
procxmt()
E 2
I 2
opause()
E 2
{
D 2
	register int i;
	register *p;
	register struct text *xp;
E 2

D 2
	if (ipc.ip_lock != u.u_procp->p_pid)
		return (0);
	u.u_procp->p_slptime = 0;
	i = ipc.ip_req;
	ipc.ip_req = 0;
	switch (i) {

	/* read user I */
	case 1:
		if (!useracc((caddr_t)ipc.ip_addr, 4, B_READ))
			goto error;
		ipc.ip_data = fuiword((caddr_t)ipc.ip_addr);
		break;

	/* read user D */
	case 2:
		if (!useracc((caddr_t)ipc.ip_addr, 4, B_READ))
			goto error;
		ipc.ip_data = fuword((caddr_t)ipc.ip_addr);
		break;

	/* read u */
	case 3:
		i = (int)ipc.ip_addr;
		if (i<0 || i >= ctob(UPAGES))
			goto error;
		ipc.ip_data = ((physadr)&u)->r[i>>2];
		break;

	/* write user I */
	/* Must set up to allow writing */
	case 4:
		/*
		 * If text, must assure exclusive use
		 */
		if (xp = u.u_procp->p_textp) {
			if (xp->x_count!=1 || xp->x_iptr->i_mode&ISVTX)
				goto error;
			xp->x_iptr->i_flag &= ~ITEXT;
		}
		i = -1;
		if (chgprot((caddr_t)ipc.ip_addr, RW) &&
		    chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RW))
			i = suiword((caddr_t)ipc.ip_addr, ipc.ip_data);
		(void) chgprot((caddr_t)ipc.ip_addr, RO);
		(void) chgprot((caddr_t)ipc.ip_addr+(sizeof(int)-1), RO);
		if (i < 0)
			goto error;
		if (xp)
			xp->x_flag |= XWRIT;
		break;

	/* write user D */
	case 5:
		if (suword((caddr_t)ipc.ip_addr, 0) < 0)
			goto error;
		(void) suword((caddr_t)ipc.ip_addr, ipc.ip_data);
		break;

	/* write u */
	case 6:
		i = (int)ipc.ip_addr;
		p = (int *)&((physadr)&u)->r[i>>2];
		for (i=0; i<16; i++)
			if (p == &u.u_ar0[ipcreg[i]])
				goto ok;
		if (p == &u.u_ar0[PS]) {
			ipc.ip_data |= PSL_CURMOD|PSL_PRVMOD;
			ipc.ip_data &=  ~PSL_USERCLR;
			goto ok;
		}
		goto error;

	ok:
		*p = ipc.ip_data;
		break;

	/* set signal and continue */
	/* one version causes a trace-trap */
	case 9:
	case 7:
		if ((int)ipc.ip_addr != 1)
			u.u_ar0[PC] = (int)ipc.ip_addr;
		if ((unsigned)ipc.ip_data > NSIG)
			goto error;
		u.u_procp->p_cursig = ipc.ip_data;	/* see issig */
		if (i == 9)
			u.u_ar0[PS] |= PSL_T;
		wakeup((caddr_t)&ipc);
		return (1);

	/* force exit */
	case 8:
		wakeup((caddr_t)&ipc);
		exit(u.u_procp->p_cursig);

	default:
	error:
		ipc.ip_req = -1;
	}
	wakeup((caddr_t)&ipc);
	return (0);
E 2
I 2
	for (;;)
		sleep((caddr_t)&u, PSLEP);
E 2
}
I 2

E 7
E 2
E 1
