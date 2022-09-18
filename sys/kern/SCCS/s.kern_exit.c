h20551
s 00001/00001/00426
d D 8.10 95/02/23 12:08:18 mckusick 93 91
c vgoneall => VOP_REVOKE
e
s 00001/00001/00426
d R 8.10 95/02/22 21:14:38 mckusick 92 91
c vgoneall => VOP_REVOKE
e
s 00001/00001/00426
d D 8.9 95/02/14 10:36:26 cgd 91 90
c hack to make this work, for now.
e
s 00014/00053/00413
d D 8.8 94/08/22 10:20:02 mckusick 90 89
c use new queue.h data structures
e
s 00008/00002/00458
d D 8.7 94/02/12 09:59:36 karels 89 88
c fix race in exit of session leader: if tty is revoked by spec_close
c or other revoke while we wait for output to drain, ttyvp will be released
c and null
e
s 00005/00000/00455
d D 8.6 94/01/21 17:17:38 bostic 88 87
c add USL's copyright notice
e
s 00000/00001/00455
d D 8.5 94/01/04 18:40:43 bostic 87 86
c lint
e
s 00006/00000/00450
d D 8.4 93/12/13 12:21:44 pendry 86 85
c add p_textvp to track vnode of executable (for procfs)
e
s 00016/00016/00434
d D 8.3 93/09/23 15:32:19 bostic 85 84
c changes for 4.4BSD-Lite requested by USL
e
s 00001/00005/00449
d D 8.2 93/09/21 07:35:34 bostic 84 83
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00452
d D 8.1 93/06/14 16:12:57 bostic 83 82
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00449
d D 7.56 93/06/14 16:12:52 bostic 82 80
c make GCC shut up (it's not right, but it's close, I think)
e
s 00002/00002/00448
d R 8.1 93/06/14 15:25:10 bostic 81 80
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00449
d D 7.55 93/06/14 15:25:06 bostic 80 78
c make function call name match system call name
e
s 00002/00002/00448
d R 8.1 93/06/14 15:18:45 bostic 79 78
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00007/00444
d D 7.54 93/06/14 15:18:26 bostic 78 76
c make function call name match system call name
e
s 00002/00002/00449
d R 8.1 93/06/10 21:57:11 bostic 77 76
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00450
d D 7.53 93/05/11 21:01:38 akito 76 75
c add luna68k define
e
s 00002/00002/00449
d D 7.52 93/02/04 19:21:37 ralph 75 74
c changed the name of exit() to exit1() because gcc2 thinks it
c knows that exit() doesn't return.
e
s 00008/00001/00443
d D 7.51 92/12/27 09:02:33 hibler 74 73
c account for differences in hp300 stack alignment (wait)
e
s 00022/00022/00422
d D 7.50 92/10/11 10:38:03 bostic 73 72
c make kernel includes standard
e
s 00009/00000/00435
d D 7.49 92/07/19 23:46:05 mckusick 72 71
c decrement process ownership count on exit
e
s 00020/00029/00415
d D 7.48 92/07/10 20:49:00 torek 71 70
c ANSIfy syscall args
e
s 00001/00006/00443
d D 7.47 92/07/08 20:02:35 torek 70 68
c calcru compensates for recent runtime now
e
s 00001/00005/00444
d R 7.47 92/07/08 19:41:40 torek 69 68
c calcru compensates for recent runtime now
e
s 00009/00005/00440
d D 7.46 92/07/08 00:50:56 torek 68 67
c new rusage
e
s 00050/00003/00395
d D 7.45 92/06/23 19:53:48 mckusick 67 66
c move up init died panic to start of exit; ptrace ATTACH
e
s 00002/00000/00396
d D 7.44 92/06/20 11:57:47 mckusick 66 65
c turn off profiling if on
e
s 00001/00001/00395
d D 7.43 92/02/15 17:32:30 mckusick 65 64
c must include proc before tty.h and socketvar.h
e
s 00005/00003/00391
d D 7.42 92/02/14 16:56:56 mckusick 64 63
c minor improvement from torek
e
s 00015/00009/00379
d D 7.41 92/02/14 11:27:03 mckusick 63 62
c fix for remrq from Mike
e
s 00003/00003/00385
d D 7.40 92/02/13 16:53:57 mckusick 62 60
c p_regs moves to p_md.md_regs
e
s 00000/00010/00378
d R 7.40 92/02/05 17:39:07 mckusick 61 60
c delete PSL_ALLCC in owait
e
s 00001/00000/00387
d D 7.39 92/01/14 16:50:28 marc 60 59
c avoid tracing panics at exit
e
s 00000/00006/00387
d D 7.38 91/09/07 16:07:55 ralph 59 58
c fix to previous changes
e
s 00012/00001/00381
d D 7.37 91/09/06 15:34:47 ralph 58 57
c added ifdef PSL_ALLCC around old wait system call code.
e
s 00008/00003/00374
d D 7.36 91/09/06 15:33:34 karels 57 56
c leave curproc set until last sleep, then clear before state is invalid
c (so clock, etc. don't poke around stuff that's been freed)
e
s 00023/00008/00354
d D 7.35 91/06/27 17:20:52 karels 56 55
c unmap (user) address space early enough to allow sleep (if releasing
c unlinked files); have to keep credentials until wait(); cpu_wait may be needed
c on other architectures (no #ifdef i386)
e
s 00005/00000/00357
d D 7.34 91/05/12 16:38:17 william 55 54
c two minor fixes for 386; others unaffected
e
s 00021/00019/00336
d D 7.33 91/05/04 15:44:56 karels 54 53
c mv vmspace_free and kmem_free of kernel stack to cpu_exit;
c marc's fix to do pgsignal on exit of session leader only if still attached
e
s 00004/00005/00351
d D 7.32 91/04/20 14:39:31 karels 53 52
c rm user.h; rm unneeded proc flags; noproc is now !curproc
e
s 00097/00090/00259
d D 7.31 91/03/17 15:41:32 karels 52 51
c more-or-less working with new proc & user structs
e
s 00002/00016/00347
d D 7.30 91/01/10 23:43:57 mckusick 51 50
c add dynamically allocated file descriptors
e
s 00018/00028/00345
d D 7.29 90/12/05 17:21:06 mckusick 50 49
c update for new VM
e
s 00001/00001/00372
d D 7.28 90/12/01 14:27:04 karels 49 48
c fix jobc adjustments so we increment before decrementing, avoiding spurious
c signals when we join parent's pgrp; move common code into subr (from torek)
e
s 00002/00001/00371
d D 7.27 90/08/29 17:38:35 karels 48 47
c from chris: exit doesn't return
e
s 00001/00011/00371
d D 7.26 90/06/28 21:19:10 bostic 47 46
c new copyright notice
e
s 00012/00013/00370
d D 7.25 90/06/28 17:10:17 karels 46 45
c RETURN => return, remove syscontext.h
e
s 00002/00003/00381
d D 7.24 90/06/25 10:54:30 karels 45 44
c expunge p_cursig, using p_xstat instead for stop signals;
c expunge u_code
e
s 00001/00001/00383
d D 7.23 90/06/21 18:36:53 mckusick 44 43
c pass proc pointer to acct()
e
s 00053/00045/00331
d D 7.22 90/06/06 00:05:11 mckusick 43 41
c update to new system call convention; expunge more u.u_procp
e
s 00001/00001/00375
d R 7.22 90/06/05 22:01:58 mckusick 42 41
c update to new system call convention; expunge more u.u_error
e
s 00001/00001/00375
d D 7.21 90/06/05 17:37:47 marc 41 40
c only HUP processes with ctty on session leader exit
e
s 00016/00021/00360
d D 7.20 90/06/05 16:14:13 marc 40 39
c fix posix semantics for exit of controlling process
e
s 00006/00003/00375
d D 7.19 90/05/10 17:56:42 mckusick 39 38
c merge in support for hp300 from Utah
e
s 00000/00003/00378
d D 7.18 90/04/27 09:56:21 mckusick 38 37
c no longer have per user quota structures
e
s 00008/00001/00373
d D 7.17 90/04/05 15:00:33 marc 37 36
c [us]time's maintained in proc.  copy to rusage as necessary
e
s 00002/00008/00372
d D 7.16 90/04/03 21:36:05 karels 36 35
c remove setjmp; new tsleep
e
s 00008/00014/00372
d D 7.15 90/04/01 14:11:12 karels 35 34
c new proc hashing (pointers, not indices)
e
s 00001/00001/00385
d D 7.14 90/02/07 15:26:01 marc 34 33
c tsleep
e
s 00003/00002/00383
d D 7.13 89/12/19 16:14:45 mckusick 33 32
c initial error code in compat code (from Mike@cs.utah.edu)
e
s 00001/00001/00384
d D 7.12 89/11/25 23:22:03 mckusick 32 31
c get rid of all users of a particular device
e
s 00005/00004/00380
d D 7.11 89/11/20 18:18:12 marc 31 30
c revoke controlling terminal when session leader exits
e
s 00052/00050/00332
d D 7.10 89/10/27 18:07:16 karels 30 29
c new wait macros, return errno instead of setting u.u_error
e
s 00001/00001/00381
d D 7.9 89/10/19 22:56:50 mckusick 29 28
c closef now returns an error code (which we ignore here)
e
s 00008/00006/00374
d D 7.8 89/09/03 18:19:56 karels 28 27
c remove WSIGRESTART; start count from 0 each time in wait
e
s 00021/00010/00359
d D 7.7 89/05/09 17:02:14 mckusick 27 26
c merge in vnodes
e
s 00002/00002/00367
d D 7.6 89/04/25 14:42:22 mckusick 26 25
c ../machine => machine
e
s 00126/00044/00243
d D 7.5 89/04/08 17:41:21 karels 25 24
c cleanups
e
s 00004/00004/00283
d D 7.4 87/08/07 20:21:47 mckusick 24 22
c use malloc/free to hold zombie status
e
s 00004/00004/00283
d R 7.4 87/06/20 14:46:21 mckusick 23 22
c use malloc/free to hold zombie status
e
s 00001/00001/00286
d D 7.3 87/02/23 22:12:52 karels 22 21
c print errno when init can't be executed
e
s 00005/00000/00282
d D 7.2 86/11/03 11:59:40 karels 21 20
c merge in tahoe support
e
s 00001/00001/00281
d D 7.1 86/06/05 00:02:37 mckusick 20 19
c 4.3BSD release version
e
s 00007/00001/00275
d D 6.13 86/03/12 11:00:42 karels 19 18
c need to raise ipl before freeing page tables (done by vrelu);
c might as well free user struct before freeing the page tables that map it.
e
s 00000/00001/00276
d D 6.12 86/02/20 14:49:33 karels 18 17
c spl5 in exit is redundant
e
s 00001/00001/00276
d D 6.11 85/11/04 17:52:35 karels 17 16
c cleanup spgrp, rm unused code (should rm it all)
e
s 00007/00001/00270
d D 6.10 85/06/08 14:35:56 mckusick 16 15
c Add copyright
e
s 00017/00012/00254
d D 6.9 85/05/27 19:58:30 karels 15 14
c implement high-water mark on file descriptors in use;
c printf when init can't be found;
c M_WAIT is implemented!
e
s 00001/00002/00265
d D 6.8 85/05/22 19:50:51 mckusick 14 13
c eliminate double meaning of SOUSIG
e
s 00013/00009/00254
d D 6.7 85/04/14 18:12:58 sam 13 12
c recover from mbuf lossage during exit (logging event)
e
s 00005/00001/00258
d D 6.6 85/03/12 13:53:24 mckusick 12 11
c add another bit to sigvec() flags to disable system call restart
e
s 00001/00000/00258
d D 6.5 84/12/20 14:28:19 karels 11 10
c make spgrp use child pointers instead of linear searches
e
s 00013/00013/00245
d D 6.4 84/08/29 20:19:25 bloom 10 9
c Change to includes.  no more ../h
e
s 00003/00001/00255
d D 6.3 84/06/10 01:10:03 sam 9 8
c don't copyout rusage on wait3 unless user has supplied buffer
e
s 00046/00037/00210
d D 6.2 84/05/22 11:44:15 karels 8 7
c linked lists of active, zombie and free procs; avoid linear proc
c searches wherever possible
e
s 00000/00000/00247
d D 6.1 83/07/29 06:32:57 sam 7 6
c 4.2 distribution
e
s 00000/00003/00247
d D 4.6 83/07/01 02:18:37 sam 6 5
c purge #if sun's
e
s 00000/00002/00250
d D 4.5 83/06/16 15:45:57 sam 5 4
c lint
e
s 00001/00001/00251
d D 4.4 83/06/14 01:37:08 sam 4 3
c revamp locking to be done at the file table level
e
s 00007/00011/00245
d D 4.3 83/06/02 15:56:45 sam 3 2
c new signals
e
s 00000/00021/00256
d D 4.2 83/05/31 01:03:37 sam 2 1
c collect all the compatibility stuff in single files
e
s 00277/00000/00000
d D 4.1 83/05/27 14:02:44 sam 1 0
c date and time created 83/05/27 14:02:44 by sam
e
u
U
t
T
I 1
D 16
/*	%M%	%I%	%E%	*/
E 16
I 16
/*
D 20
 * Copyright (c) 1982 Regents of the University of California.
E 20
I 20
D 25
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 25
I 25
D 27
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 25
E 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 27
I 27
D 52
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 52
I 52
D 83
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
E 52
 * All rights reserved.
E 83
I 83
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
I 88
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 88
E 83
E 27
 *
I 27
D 47
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
E 47
I 47
 * %sccs.include.redist.c%
E 47
 *
E 27
 *	%W% (Berkeley) %G%
 */
E 16

D 25
#include "../machine/reg.h"
#include "../machine/psl.h"

E 25
D 10
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/map.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/kernel.h"
#include "../h/proc.h"
#include "../h/buf.h"
#include "../h/wait.h"
#include "../h/vm.h"
#include "../h/file.h"
#include "../h/mbuf.h"
#include "../h/inode.h"
E 10
I 10
D 73
#include "param.h"
#include "systm.h"
#include "map.h"
D 27
#include "dir.h"
E 27
D 43
#include "user.h"
E 43
I 43
#include "ioctl.h"
I 65
#include "proc.h"
E 65
#include "tty.h"
I 52
#include "time.h"
#include "resource.h"
E 52
D 46
#undef RETURN
#include "syscontext.h"
E 46
I 46
D 53
#include "user.h"
E 53
E 46
E 43
#include "kernel.h"
D 65
#include "proc.h"
E 65
#include "buf.h"
#include "wait.h"
D 50
#include "vm.h"
E 50
#include "file.h"
D 24
#include "mbuf.h"
E 24
D 27
#include "inode.h"
E 27
I 27
#include "vnode.h"
I 30
D 43
#include "ioctl.h"
E 30
E 27
I 25
#include "tty.h"
E 43
E 25
I 13
#include "syslog.h"
I 24
#include "malloc.h"
I 53
#include "resourcevar.h"
I 67
#include "ptrace.h"
E 73
I 73
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/map.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/kernel.h>
#include <sys/buf.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/syslog.h>
#include <sys/malloc.h>
#include <sys/resourcevar.h>
#include <sys/ptrace.h>
E 73
E 67
E 53
E 24
E 13
E 10

I 54
D 73
#include "machine/cpu.h"
E 73
I 73
#include <machine/cpu.h>
E 73
E 54
I 25
D 26
#include "../machine/reg.h"
E 26
I 26
D 52
#include "machine/reg.h"
E 52
E 26
#ifdef COMPAT_43
I 52
D 73
#include "machine/reg.h"
E 52
D 26
#include "../machine/psl.h"
E 26
I 26
#include "machine/psl.h"
E 73
I 73
#include <machine/reg.h>
#include <machine/psl.h>
E 73
E 26
#endif

I 50
D 52
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
E 52
I 52
D 53
#include "vm/vm_param.h"
#include "vm/vm_map.h"
E 53
I 53
D 73
#include "vm/vm.h"
E 53
#include "vm/vm_kern.h"
E 73
I 73
#include <vm/vm.h>
#include <vm/vm_kern.h>
E 73
E 52

I 82
__dead void cpu_exit __P((struct proc *));
__dead void exit1 __P((struct proc *, int));

E 82
E 50
E 25
/*
D 78
 * Exit system call: pass back caller's arg
E 78
I 78
 * exit --
 *	Death of process.
E 78
 */
I 71
struct rexit_args {
	int	rval;
};
I 82
__dead void
E 82
E 71
D 43
rexit()
{
D 30
	register struct a {
E 30
I 30
	struct a {
E 43
I 43
D 78
/* ARGSUSED */
rexit(p, uap, retval)
E 78
I 78
exit(p, uap, retval)
E 78
	struct proc *p;
D 71
	struct args {
E 43
E 30
		int	rval;
	} *uap;
E 71
I 71
	struct rexit_args *uap;
E 71
I 43
	int *retval;
{
E 43
I 25
D 30
	union wait status;
E 30
E 25

D 43
	uap = (struct a *)u.u_ap;
D 25
	exit((uap->rval & 0377) << 8);
E 25
I 25
D 30
	status.w_status = 0;
	status.w_retcode = uap->rval;
	exit(status.w_status);
E 30
I 30
	exit(W_EXITCODE(uap->rval, 0));
E 43
I 43
D 46
	RETURN (exit(p, W_EXITCODE(uap->rval, 0)));
E 46
I 46
D 48
	return (exit(p, W_EXITCODE(uap->rval, 0)));
E 48
I 48
D 75
	exit(p, W_EXITCODE(uap->rval, 0));
E 75
I 75
	exit1(p, W_EXITCODE(uap->rval, 0));
E 75
	/* NOTREACHED */
E 48
E 46
E 43
E 30
E 25
}

/*
D 52
 * Release resources.
 * Save u. area for parent to look at.
 * Enter zombie state.
 * Wake up parent and init processes,
 * and dispose of children.
E 52
I 52
D 78
 * Exit: deallocate address space and other resources,
 * change proc state to zombie, and unlink proc from allproc
 * and parent's lists.  Save exit status and rusage for wait().
 * Check for child processes and orphan them.
E 78
I 78
 * Exit: deallocate address space and other resources, change proc state
 * to zombie, and unlink proc from allproc and parent's lists.  Save exit
 * status and rusage for wait().  Check for child processes and orphan them.
E 78
E 52
 */
I 82
__dead void
E 82
D 43
exit(rv)
E 43
I 43
D 75
exit(p, rv)
E 75
I 75
exit1(p, rv)
E 75
D 52
	struct proc *p;
E 52
I 52
	register struct proc *p;
E 52
E 43
D 25
	int rv;
E 25
I 25
D 28
	int rv;			/* should be union wait (XXX) */
E 28
I 28
	int rv;
E 28
E 25
{
D 52
	register int i;
E 52
D 8
	register struct proc *p, *q;
E 8
I 8
D 43
	register struct proc *p, *q, *nq;
E 43
I 43
	register struct proc *q, *nq;
E 43
E 8
D 35
	register int x;
E 35
I 35
	register struct proc **pp;
I 64
	register struct vmspace *vm;
I 68
D 70
	struct timeval tv;
E 70
E 68
E 64
I 52
D 87
	int s;
E 87
E 52
E 35
D 24
	struct mbuf *m = m_getclr(M_WAIT, MT_ZOMBIE);
E 24

I 67
	if (p->p_pid == 1)
		panic("init died (signal %d, exit %d)",
		    WTERMSIG(rv), WEXITSTATUS(rv));
E 67
#ifdef PGINPROF
	vmsizmon();
#endif
I 66
D 85
	if (p->p_flag & SPROFIL)
E 85
I 85
	if (p->p_flag & P_PROFIL)
E 85
		stopprofclock(p);
E 66
D 43
	p = u.u_procp;
E 43
I 24
	MALLOC(p->p_ru, struct rusage *, sizeof(struct rusage),
		M_ZOMBIE, M_WAITOK);
E 24
D 52
	p->p_flag &= ~(STRC|SULOCK);
E 52
I 52
	/*
	 * If parent is waiting for us to exit or exec,
D 85
	 * SPPWAIT is set; we will wakeup the parent below.
E 85
I 85
	 * P_PPWAIT is set; we will wakeup the parent below.
E 85
	 */
D 53
	p->p_flag &= ~(STRC|SULOCK|SPPWAIT);
E 53
I 53
D 85
	p->p_flag &= ~(STRC|SPPWAIT);
E 53
E 52
	p->p_flag |= SWEXIT;
E 85
I 85
	p->p_flag &= ~(P_TRACED | P_PPWAIT);
	p->p_flag |= P_WEXIT;
E 85
D 3
	(void) spl6();
	/* we know SIG_IGN is 1 */
	p->p_siga0 = ~0;
	p->p_siga1 = 0;
	(void) spl0();
E 3
I 3
	p->p_sigignore = ~0;
I 30
D 85
	p->p_sig = 0;
E 85
I 85
	p->p_siglist = 0;
E 85
E 30
E 3
D 52
	p->p_cpticks = 0;
	p->p_pctcpu = 0;
D 3
	for (i=0; i<NSIG; i++)
E 3
I 3
	for (i = 0; i < NSIG; i++)
E 3
		u.u_signal[i] = SIG_IGN;
E 52
	untimeout(realitexpire, (caddr_t)p);
I 52

	/*
	 * Close open files and release open-file table.
	 * This may block!
	 */
	fdfree(p);
I 56

	/* The next two chunks should probably be moved to vmspace_exit. */
I 64
	vm = p->p_vmspace;
E 64
E 56
D 54
p->p_fd = 0;
E 54
E 52
I 50
#ifdef SYSVSHM
D 52
	if (p->p_shm)
E 52
I 52
D 64
	if (p->p_vmspace->vm_shm)
E 64
I 64
	if (vm->vm_shm)
E 64
E 52
		shmexit(p);
#endif
I 56
	/*
	 * Release user portion of address space.
	 * This releases references to vnodes,
	 * which could cause I/O if the file has been unlinked.
	 * Need to do this early enough that we can still sleep.
	 * Can't free the entire vmspace as the kernel stack
	 * may be mapped within that space also.
	 */
D 64
	if (p->p_vmspace->vm_refcnt == 1)
		(void) vm_map_remove(&p->p_vmspace->vm_map, VM_MIN_ADDRESS,
E 64
I 64
	if (vm->vm_refcnt == 1)
		(void) vm_map_remove(&vm->vm_map, VM_MIN_ADDRESS,
E 64
		    VM_MAXUSER_ADDRESS);
E 56
D 52
	vm_map_deallocate(p->p_map);
	p->p_map = VM_MAP_NULL;
E 50
	/*
D 50
	 * Release virtual memory.  If we resulted from
	 * a vfork(), instead give the resources back to
	 * the parent.
E 50
I 50
	 * XXX preserve synchronization semantics of vfork
E 50
	 */
D 39
	if ((p->p_flag & SVFORK) == 0)
E 39
I 39
D 50
	if ((p->p_flag & SVFORK) == 0) {
#ifdef MAPMEM
		if (u.u_mmap)
D 43
			mmexit();
E 43
I 43
			(void) mmexit(p);
E 43
#endif
E 39
		vrelvm();
D 39
	else {
E 39
I 39
	} else {
E 50
I 50
	if (p->p_flag & SVFORK) {
E 50
E 39
		p->p_flag &= ~SVFORK;
		wakeup((caddr_t)p);
		while ((p->p_flag & SVFDONE) == 0)
			sleep((caddr_t)p, PZERO - 1);
		p->p_flag &= ~SVFDONE;
	}
D 15
	for (i = 0; i < NOFILE; i++) {
E 15
I 15
D 51
	for (i = 0; i <= u.u_lastfile; i++) {
E 15
		struct file *f;
D 5
		int po;
E 5

		f = u.u_ofile[i];
D 15
		u.u_ofile[i] = NULL;
D 5
		po = u.u_pofile[i];
E 5
		u.u_pofile[i] = 0;
D 4
		closef(f, po);
E 4
I 4
		closef(f);
E 15
I 15
		if (f) {
			u.u_ofile[i] = NULL;
			u.u_pofile[i] = 0;
D 29
			closef(f);
E 29
I 29
			(void) closef(f);
E 29
		}
E 15
E 4
	}
E 51
I 51
	fdrele(p->p_fd);
	p->p_fd = (struct filedesc *)0;
E 52
I 52
D 54
	vmspace_free(p->p_vmspace);
p->p_vmspace = 0;
E 54

D 67
	if (p->p_pid == 1)
		panic("init died");
E 67
E 52
E 51
I 25
	if (SESS_LEADER(p)) {
D 40
		p->p_session->s_leader = 0;
D 31
		/* TODO: vhangup(); */
		if (u.u_ttyp) {
			u.u_ttyp->t_session = 0;
			u.u_ttyp->t_pgid = 0;
E 31
I 31
		if (p->p_session->s_ttyvp) {
D 32
			vgone(p->p_session->s_ttyvp);
E 32
I 32
			vgoneall(p->p_session->s_ttyvp);
E 32
			vrele(p->p_session->s_ttyvp);
			p->p_session->s_ttyvp = NULL;
E 40
I 40
		register struct session *sp = p->p_session;

		if (sp->s_ttyvp) {
E 40
D 37
			p->p_session->s_ttyp = NULL;
E 37
I 37
			/*
I 40
			 * Controlling process.
D 54
			 * Signal foreground pgrp and revoke access
			 * to controlling terminal.
E 54
I 54
			 * Signal foreground pgrp,
			 * drain controlling terminal
			 * and revoke access to controlling terminal.
E 54
			 */
D 54
			if (sp->s_ttyp->t_pgrp)
D 41
				pgsignal(sp->s_ttyp->t_pgrp, SIGHUP, 0);
E 41
I 41
				pgsignal(sp->s_ttyp->t_pgrp, SIGHUP, 1);
E 41
			vgoneall(sp->s_ttyvp);
E 54
I 54
			if (sp->s_ttyp->t_session == sp) {
				if (sp->s_ttyp->t_pgrp)
					pgsignal(sp->s_ttyp->t_pgrp, SIGHUP, 1);
				(void) ttywait(sp->s_ttyp);
D 89
				vgoneall(sp->s_ttyvp);
E 89
I 89
				/*
				 * The tty could have been revoked
				 * if we blocked.
				 */
				if (sp->s_ttyvp)
D 93
					vgoneall(sp->s_ttyvp);
E 93
I 93
					VOP_REVOKE(sp->s_ttyvp, REVOKEALL);
E 93
E 89
			}
E 54
D 89
			vrele(sp->s_ttyvp);
E 89
I 89
			if (sp->s_ttyvp)
				vrele(sp->s_ttyvp);
E 89
			sp->s_ttyvp = NULL;
			/*
E 40
			 * s_ttyp is not zero'd; we use this to indicate
			 * that the session once had a controlling terminal.
I 40
			 * (for logging and informational purposes)
E 40
			 */
E 37
E 31
		}
I 40
D 54
		sp->s_leader = 0;
E 54
I 54
		sp->s_leader = NULL;
E 54
E 40
D 51
	}
E 25
D 27
	ilock(u.u_cdir);
	iput(u.u_cdir);
E 27
I 27
	VOP_LOCK(u.u_cdir);
	vput(u.u_cdir);
E 27
	if (u.u_rdir) {
D 27
		ilock(u.u_rdir);
		iput(u.u_rdir);
E 27
I 27
		VOP_LOCK(u.u_rdir);
		vput(u.u_rdir);
E 51
E 27
	}
D 52
	u.u_rlimit[RLIMIT_FSIZE].rlim_cur = RLIM_INFINITY;
E 52
I 52
	fixjobc(p, p->p_pgrp, 0);
	p->p_rlimit[RLIMIT_FSIZE].rlim_cur = RLIM_INFINITY;
E 52
D 44
	acct();
E 44
I 44
D 80
	(void) acct(p);
E 80
I 80
	(void)acct_process(p);
E 80
I 58
D 59
	if (--p->p_limit->p_refcnt == 0)
		FREE(p->p_limit, M_SUBPROC);
	if (--p->p_cred->p_refcnt == 0) {
		crfree(p->p_cred->pc_ucred);
		FREE(p->p_cred, M_SUBPROC);
	}
E 59
E 58
E 44
D 38
#ifdef QUOTA
	qclean();
#endif
E 38
I 27
D 52
	crfree(u.u_cred);
E 52
I 52
D 57
	if (--p->p_limit->p_refcnt == 0)
		FREE(p->p_limit, M_SUBPROC);
E 57
D 56
	if (--p->p_cred->p_refcnt == 0) {
		crfree(p->p_cred->pc_ucred);
		FREE(p->p_cred, M_SUBPROC);
	}
E 56
E 52
E 27
I 25
#ifdef KTRACE
	/* 
	 * release trace file
	 */
I 60
	p->p_traceflag = 0;	/* don't trace the vrele() */
E 60
	if (p->p_tracep)
D 27
		irele(p->p_tracep);
E 27
I 27
		vrele(p->p_tracep);
E 27
#endif
I 57
	/*
D 63
	 * Clear curproc after we've done all operations
	 * that could block, and before tearing down
	 * the rest of the process state.
	 */
	curproc = NULL;
	if (--p->p_limit->p_refcnt == 0)
		FREE(p->p_limit, M_SUBPROC);
E 57
E 25
D 6
#ifdef sun
	ctxfree(u.u_procp);
#endif
E 6
D 19
	vrelpt(u.u_procp);
E 19
I 19
D 39
	/*
E 39
I 25
D 50
	/*
E 25
	 * Freeing the user structure and kernel stack
	 * for the current process: have to run a bit longer
	 * using the pages which are about to be freed...
	 * vrelu will block memory allocation by raising ipl.
	 */
E 19
D 43
	vrelu(u.u_procp, 0);
I 19
	vrelpt(u.u_procp);
E 43
I 43
	vrelu(p, 0);
	vrelpt(p);
E 50
I 50
D 52
	splimp();
	/* I don't think this will cause a sleep/realloc anywhere... */
	kmem_free(kernel_map, (vm_offset_t)p->p_addr,
		  round_page(ctob(UPAGES)));
E 50
E 43
E 19
D 18
	(void) spl5();		/* hack for mem alloc race XXX */
E 18
I 8
	if (*p->p_prev = p->p_nxt)		/* off allproc queue */
E 52
I 52

	/*
E 63
	 * Remove proc from allproc queue and pidhash chain.
	 * Place onto zombproc.  Unlink from parent's child list.
	 */
D 85
	if (*p->p_prev = p->p_nxt)
E 52
		p->p_nxt->p_prev = p->p_prev;
D 52
	if (p->p_nxt = zombproc)		/* onto zombproc */
E 52
I 52
	if (p->p_nxt = zombproc)
E 52
		p->p_nxt->p_prev = &p->p_nxt;
E 85
I 85
D 90
	if (*p->p_prev = p->p_next)
		p->p_next->p_prev = p->p_prev;
	if (p->p_next = zombproc)
		p->p_next->p_prev = &p->p_next;
E 85
	p->p_prev = &zombproc;
	zombproc = p;
E 90
I 90
	LIST_REMOVE(p, p_list);
	LIST_INSERT_HEAD(&zombproc, p, p_list);
E 90
E 8
D 50
	multprog--;
E 50
	p->p_stat = SZOMB;
I 63

E 63
D 53
	noproc = 1;
E 53
I 53
D 57
	curproc = NULL;
E 57
E 53
D 35
	i = PIDHASH(p->p_pid);
	x = p - proc;
	if (pidhash[i] == x)
		pidhash[i] = p->p_idhash;
	else {
		for (i = pidhash[i]; i != 0; i = proc[i].p_idhash)
			if (proc[i].p_idhash == x) {
				proc[i].p_idhash = p->p_idhash;
				goto done;
			}
		panic("exit");
	}
E 35
I 35
D 90
	for (pp = &pidhash[PIDHASH(p->p_pid)]; *pp; pp = &(*pp)->p_hash)
		if (*pp == p) {
			*pp = p->p_hash;
			goto done;
		}
	panic("exit");
done:
E 90
I 90
	LIST_REMOVE(p, p_hash);
E 90
E 35
D 15
	if (p->p_pid == 1)
		panic("init died");
E 15
I 15
D 50
	if (p->p_pid == 1) {
		if (p->p_dsize == 0) {
D 22
			printf("Can't exec /etc/init\n");
E 22
I 22
D 25
			printf("Can't exec /etc/init (errno %d)\n", rv >> 8);
E 25
I 25
D 30
			printf("Can't exec init (errno %d)\n", rv >> 8);
E 30
I 30
			printf("Can't exec init (errno %d)\n", WEXITSTATUS(rv));
E 30
E 25
E 22
			for (;;)
				;
		} else
			panic("init died");
	}
E 50
I 50
D 52
	if (p->p_pid == 1)
		panic("init died");
E 50
E 15
D 35
done:
E 35
	p->p_xstat = rv;
D 13
if (m == 0)
panic("exit: m_getclr");
	p->p_ru = mtod(m, struct rusage *);
	*p->p_ru = u.u_ru;
	ruadd(p->p_ru, &u.u_cru);
E 13
I 13
D 15
	if (m) {
		p->p_ru = mtod(m, struct rusage *);
		*p->p_ru = u.u_ru;
		ruadd(p->p_ru, &u.u_cru);
	} else
		log(KERN_ALERT, "exit: pid %d: no mbuf", p->p_pid);
E 15
I 15
D 24
	p->p_ru = mtod(m, struct rusage *);
E 24
	*p->p_ru = u.u_ru;
I 37
	i = splclock();
	p->p_ru->ru_stime = p->p_stime;
	p->p_ru->ru_utime = p->p_utime;
	splx(i);
E 37
	ruadd(p->p_ru, &u.u_cru);
E 52
I 52

E 52
E 15
E 13
D 8
	for (q = proc; q < procNPROC; q++)
		if (q->p_pptr == p) {
			if (q->p_osptr)
				q->p_osptr->p_ysptr = q->p_ysptr;
			if (q->p_ysptr)
				q->p_ysptr->p_osptr = q->p_osptr;
			if (proc[1].p_cptr)
				proc[1].p_cptr->p_ysptr = q;
			q->p_osptr = proc[1].p_cptr;
			q->p_ysptr = NULL;
			proc[1].p_cptr = q;
E 8
I 8
D 90
	if (p->p_cptr)		/* only need this if any child is S_ZOMB */
E 90
I 90
	q = p->p_children.lh_first;
	if (q)		/* only need this if any child is S_ZOMB */
E 90
D 52
		wakeup((caddr_t)&proc[1]);
I 25
D 40
	if (PGRP_JOBC(p))
		p->p_pgrp->pg_jobc--;
E 40
I 40
D 49
	fixjobc(p, 0);
E 49
I 49
	fixjobc(p, p->p_pgrp, 0);
E 52
I 52
		wakeup((caddr_t) initproc);
E 52
E 49
E 40
E 25
D 90
	for (q = p->p_cptr; q != NULL; q = nq) {
I 25
D 40
		if (PGRP_JOBC(q))
			q->p_pgrp->pg_jobc--;
E 40
E 25
		nq = q->p_osptr;
		if (nq != NULL)
			nq->p_ysptr = NULL;
D 52
		if (proc[1].p_cptr)
			proc[1].p_cptr->p_ysptr = q;
		q->p_osptr = proc[1].p_cptr;
E 52
I 52
		if (initproc->p_cptr)
			initproc->p_cptr->p_ysptr = q;
		q->p_osptr = initproc->p_cptr;
E 52
		q->p_ysptr = NULL;
D 52
		proc[1].p_cptr = q;
E 52
I 52
		initproc->p_cptr = q;
E 52
E 8

E 90
I 90
	for (; q != 0; q = nq) {
		nq = q->p_sibling.le_next;
		LIST_REMOVE(q, p_sibling);
		LIST_INSERT_HEAD(&initproc->p_children, q, p_sibling);
E 90
D 8
			q->p_pptr = &proc[1];
			q->p_ppid = 1;
			wakeup((caddr_t)&proc[1]);
			/*
			 * Traced processes are killed
			 * since their existence means someone is screwing up.
			 * Stopped processes are sent a hangup and a continue.
			 * This is designed to be ``safe'' for setuid
			 * processes since they must be willing to tolerate
			 * hangups anyways.
			 */
			if (q->p_flag&STRC) {
				q->p_flag &= ~STRC;
				psignal(q, SIGKILL);
			} else if (q->p_stat == SSTOP) {
				psignal(q, SIGHUP);
				psignal(q, SIGCONT);
			}
			/*
			 * Protect this process from future
			 * tty signals, clear TSTP/TTIN/TTOU if pending.
			 */
			(void) spgrp(q, -1);
E 8
I 8
D 52
		q->p_pptr = &proc[1];
		q->p_ppid = 1;
E 52
I 52
		q->p_pptr = initproc;
E 52
		/*
		 * Traced processes are killed
		 * since their existence means someone is screwing up.
D 40
		 * Stopped processes are sent a hangup and a continue.
		 * This is designed to be ``safe'' for setuid
		 * processes since they must be willing to tolerate
		 * hangups anyways.
E 40
		 */
D 85
		if (q->p_flag&STRC) {
			q->p_flag &= ~STRC;
E 85
I 85
		if (q->p_flag & P_TRACED) {
			q->p_flag &= ~P_TRACED;
E 85
			psignal(q, SIGKILL);
D 40
		} else if (q->p_stat == SSTOP) {
			psignal(q, SIGHUP);
			psignal(q, SIGCONT);
E 40
E 8
		}
I 8
D 40
		/*
		 * Protect this process from future
		 * tty signals, clear TSTP/TTIN/TTOU if pending.
		 */
D 17
		(void) spgrp(q, -1);
E 17
I 17
		(void) spgrp(q);
E 40
E 17
	}
I 11
D 90
	p->p_cptr = NULL;
E 90
I 52

	/*
D 68
	 * Save exit status and final rusage info,
	 * adding in child rusage info and self times.
E 68
I 68
	 * Save exit status and final rusage info, adding in child rusage
D 70
	 * info and self times.  Add its most recent runtime here; we are
	 * not going to reach the usual code in swtch().
E 70
I 70
	 * info and self times.
E 70
E 68
	 */
	p->p_xstat = rv;
	*p->p_ru = p->p_stats->p_ru;
D 68
	p->p_ru->ru_stime = p->p_stime;
	p->p_ru->ru_utime = p->p_utime;
E 68
I 68
D 70
	microtime(&tv);
	timevalsub(&tv, &runtime);
	timevaladd(&p->p_rtime, &tv);
E 70
	calcru(p, &p->p_ru->ru_utime, &p->p_ru->ru_stime, NULL);
E 68
	ruadd(p->p_ru, &p->p_stats->p_cru);

	/*
	 * Notify parent that we're gone.
	 */
E 52
E 11
E 8
	psignal(p->p_pptr, SIGCHLD);
	wakeup((caddr_t)p->p_pptr);
I 21
#if defined(tahoe)
D 52
	dkeyrelease(p->p_dkey), p->p_dkey = 0;
	ckeyrelease(p->p_ckey), p->p_ckey = 0;
E 52
D 54
	u.u_pcb.pcb_savacc.faddr = (float *)NULL;
E 54
I 54
	/* move this to cpu_exit */
	p->p_addr->u_pcb.pcb_savacc.faddr = (float *)NULL;
E 54
#endif
I 63
	/*
	 * Clear curproc after we've done all operations
	 * that could block, and before tearing down the rest
	 * of the process state that might be used from clock, etc.
	 * Also, can't clear curproc while we're still runnable,
	 * as we're not on a run queue (we are current, just not
	 * a proper proc any longer!).
	 *
	 * Other substructures are freed from wait().
	 */
	curproc = NULL;
	if (--p->p_limit->p_refcnt == 0)
		FREE(p->p_limit, M_SUBPROC);

E 63
I 52
	/*
D 54
	 * Free the memory for the user structure and kernel stack.
	 * As we continue using it until the swtch completes
	 * (or switches to an interrupt stack), we need to block
	 * memory allocation by raising priority until we are gone.
E 54
I 54
	 * Finally, call machine-dependent code to release the remaining
	 * resources including address space, the kernel stack and pcb.
	 * The address space is released by "vmspace_free(p->p_vmspace)";
	 * This is machine-dependent, as we may have to change stacks
	 * or ensure that the current one isn't reallocated before we
D 68
	 * finish.  cpu_exit will end with a call to swtch(), finishing
E 68
I 68
	 * finish.  cpu_exit will end with a call to cpu_swtch(), finishing
E 68
	 * our execution (pun intended).
E 54
	 */
D 54
	(void) splimp();
	/* I don't think this will cause a sleep/realloc anywhere... */
	kmem_free(kernel_map, (vm_offset_t)p->p_addr,
	    round_page(ctob(UPAGES)));
E 52
E 21
	swtch();
E 54
I 54
	cpu_exit(p);
E 54
I 52
D 82
	/* NOTREACHED */
E 82
E 52
}

I 71
struct wait_args {
	int	pid;
	int	*status;
	int	options;
	struct	rusage *rusage;
E 71
D 25
wait()
E 25
I 25
#ifdef COMPAT_43
I 71
	int	compat;		/* pseudo */
#endif
};

#ifdef COMPAT_43
I 74
D 76
#ifdef hp300
E 76
I 76
#if defined(hp300) || defined(luna68k)
E 76
#include <machine/frame.h>
#define GETPS(rp)	((struct frame *)(rp))->f_sr
#else
#define GETPS(rp)	(rp)[PS]
#endif

E 74
E 71
D 43
owait()
E 25
{
D 25
	struct rusage ru, *rup;
E 25
I 25
D 30
	struct a {
E 30
I 30
	register struct a {
E 43
I 43
D 91
owait(p, uap, retval)
E 91
I 91
compat_43_wait(p, uap, retval)
E 91
	struct proc *p;
D 71
	register struct args {
E 43
E 30
		int	pid;
D 30
		union	wait *status;
E 30
I 30
		int	*status;
E 30
		int	options;
		struct	rusage *rusage;
I 30
		int	compat;
E 30
D 43
	} *uap = (struct a *)u.u_ap;
E 43
I 43
	} *uap;
E 71
I 71
	register struct wait_args *uap;
E 71
	int *retval;
{
E 43
E 25

I 58
#ifdef PSL_ALLCC
E 58
D 52
	if ((u.u_ar0[PS] & PSL_ALLCC) != PSL_ALLCC) {
E 52
I 52
D 62
	if ((p->p_regs[PS] & PSL_ALLCC) != PSL_ALLCC) {
E 62
I 62
D 74
	if ((p->p_md.md_regs[PS] & PSL_ALLCC) != PSL_ALLCC) {
E 74
I 74
	if ((GETPS(p->p_md.md_regs) & PSL_ALLCC) != PSL_ALLCC) {
E 74
E 62
E 52
D 25
		u.u_error = wait1(0, (struct rusage *)0);
		return;
E 25
I 25
D 28
		uap->options = WSIGRESTART;
E 28
I 28
		uap->options = 0;
E 28
D 71
		uap->rusage = 0;
E 71
I 71
		uap->rusage = NULL;
E 71
	} else {
D 28
		uap->options = u.u_ar0[R0] | WSIGRESTART;
E 28
I 28
D 52
		uap->options = u.u_ar0[R0];
E 28
		uap->rusage = (struct rusage *)u.u_ar0[R1];
E 52
I 52
D 62
		uap->options = p->p_regs[R0];
		uap->rusage = (struct rusage *)p->p_regs[R1];
E 62
I 62
		uap->options = p->p_md.md_regs[R0];
		uap->rusage = (struct rusage *)p->p_md.md_regs[R1];
E 62
E 52
E 25
	}
I 58
#else
	uap->options = 0;
D 71
	uap->rusage = 0;
E 71
I 71
	uap->rusage = NULL;
E 71
#endif
E 58
D 25
	rup = (struct rusage *)u.u_ar0[R1];
	u.u_error = wait1(u.u_ar0[R0], &ru);
	if (u.u_error)
		return;
D 9
	(void) copyout((caddr_t)&ru, (caddr_t)rup, sizeof (struct rusage));
E 9
I 9
	if (rup != (struct rusage *)0)
		u.u_error = copyout((caddr_t)&ru, (caddr_t)rup,
		    sizeof (struct rusage));
E 25
I 25
	uap->pid = WAIT_ANY;
D 71
	uap->status = 0;
E 71
I 71
	uap->status = NULL;
E 71
D 30
	wait1(1);
E 30
I 30
	uap->compat = 1;
D 43
	u.u_error = wait1();
E 43
I 43
D 46
	RETURN (wait1(p, uap, retval));
E 46
I 46
	return (wait1(p, uap, retval));
E 46
E 43
E 30
E 25
E 9
}

I 25
D 43
wait4()
{
D 30
	wait1(0);
E 30
I 30
	register struct a {
E 43
I 43
wait4(p, uap, retval)
	struct proc *p;
D 71
	struct args {
E 43
		int	pid;
		int	*status;
		int	options;
		struct	rusage *rusage;
		int	compat;
D 43
	} *uap = (struct a *)u.u_ap;
E 43
I 43
	} *uap;
E 71
I 71
	struct wait_args *uap;
E 71
	int *retval;
{
E 43

	uap->compat = 0;
D 43
	u.u_error = wait1();
E 43
I 43
D 46
	RETURN (wait1(p, uap, retval));
E 46
I 46
	return (wait1(p, uap, retval));
E 46
E 43
E 30
}
I 30
#else
#define	wait1	wait4
E 30
#endif

E 25
D 2
#ifndef NOCOMPAT
#include "../h/vtimes.h"

owait()
{
	struct rusage ru;
	struct vtimes *vtp, avt;

	if ((u.u_ar0[PS] & PSL_ALLCC) != PSL_ALLCC) {
		u.u_error = wait1(0, (struct rusage *)0);
		return;
	}
	vtp = (struct vtimes *)u.u_ar0[R1];
	u.u_error = wait1(u.u_ar0[R0], &ru);
	if (u.u_error)
		return;
	getvtimes(&ru, &avt);
	(void) copyout((caddr_t)&avt, (caddr_t)vtp, sizeof (struct vtimes));
}
#endif

E 2
D 84
/*
D 52
 * Wait system call.
 * Search for a terminated (zombie) child,
 * finally lay it to rest, and collect its status.
 * Look also for stopped (traced) children,
 * and pass back status from them.
E 52
I 52
 * Wait: check child processes to see if any have exited,
 * stopped under trace, or (optionally) stopped by a signal.
 * Pass back status and deallocate exited child's proc structure.
E 52
 */
E 84
I 84
int
E 84
D 25
wait1(options, ru)
	register int options;
	struct rusage *ru;
E 25
I 25
D 30
#ifdef COMPAT_43
wait1(compat)
	int compat;
#else
wait4()
#endif
E 30
I 30
D 43
wait1()
E 30
E 25
{
I 25
	register struct a {
E 43
I 43
wait1(q, uap, retval)
	register struct proc *q;
D 71
	register struct args {
E 43
		int	pid;
D 30
		union	wait *status;
E 30
I 30
		int	*status;
E 30
		int	options;
		struct	rusage *rusage;
I 30
#ifdef COMPAT_43
		int compat;
#endif
E 30
D 43
	} *uap = (struct a *)u.u_ap;
E 25
	register f;
	register struct proc *p, *q;
E 43
I 43
	} *uap;
E 71
I 71
	register struct wait_args *uap;
E 71
	int retval[];
{
D 52
	register int f;
E 52
I 52
	register int nfound;
E 52
D 67
	register struct proc *p;
E 67
I 67
	register struct proc *p, *t;
E 67
E 43
I 25
D 30
	union wait status;
E 30
I 30
	int status, error;
E 30
E 25

D 28
	f = 0;
E 28
D 25
loop:
E 25
D 8
	for (p = proc; p < procNPROC; p++)
	if (p->p_pptr == u.u_procp) {
E 8
I 8
D 43
	q = u.u_procp;
E 43
I 25
	if (uap->pid == 0)
		uap->pid = -q->p_pgid;
D 28
	if (uap->options &~ (WUNTRACED|WNOHANG|WSIGRESTART)) {
E 28
I 28
#ifdef notyet
D 30
	if (uap->options &~ (WUNTRACED|WNOHANG)) {
E 28
		u.u_error = EINVAL;
		return;
	}
E 30
I 30
	if (uap->options &~ (WUNTRACED|WNOHANG))
D 43
		return (EINVAL);
E 43
I 43
D 46
		RETURN (EINVAL);
E 46
I 46
		return (EINVAL);
E 46
E 43
E 30
I 28
#endif
E 28
loop:
I 28
D 52
	f = 0;
E 52
I 52
	nfound = 0;
E 52
E 28
E 25
D 90
	for (p = q->p_cptr; p; p = p->p_osptr) {
E 90
I 90
	for (p = q->p_children.lh_first; p != 0; p = p->p_sibling.le_next) {
E 90
I 25
		if (uap->pid != WAIT_ANY &&
		    p->p_pid != uap->pid && p->p_pgid != -uap->pid)
			continue;
E 25
E 8
D 52
		f++;
E 52
I 52
		nfound++;
E 52
		if (p->p_stat == SZOMB) {
I 25
D 30
			pgrm(p);			/* off pgrp */
E 30
E 25
D 43
			u.u_r.r_val1 = p->p_pid;
E 43
I 43
			retval[0] = p->p_pid;
E 43
D 25
			u.u_r.r_val2 = p->p_xstat;
			p->p_xstat = 0;
D 13
			if (ru)
E 13
I 13
			if (ru && p->p_ru)
E 13
				*ru = *p->p_ru;
D 13
			ruadd(&u.u_cru, p->p_ru);
			(void) m_free(dtom(p->p_ru));
			p->p_ru = 0;
E 13
I 13
			if (p->p_ru) {
				ruadd(&u.u_cru, p->p_ru);
D 24
				(void) m_free(dtom(p->p_ru));
E 24
I 24
				FREE(p->p_ru, M_ZOMBIE);
E 24
				p->p_ru = 0;
E 25
I 25
#ifdef COMPAT_43
D 30
			if (compat)
E 30
I 30
			if (uap->compat)
E 30
D 43
				u.u_r.r_val2 = p->p_xstat;
E 43
I 43
				retval[1] = p->p_xstat;
E 43
			else
#endif
			if (uap->status) {
D 30
				status.w_status = p->p_xstat;
				if (u.u_error = copyout((caddr_t)&status,
E 30
I 30
				status = p->p_xstat;	/* convert to int */
				if (error = copyout((caddr_t)&status,
E 30
				    (caddr_t)uap->status, sizeof(status)))
D 30
					return;
E 30
I 30
D 43
					return (error);
E 43
I 43
D 46
					RETURN (error);
E 46
I 46
					return (error);
E 46
E 43
E 30
E 25
			}
I 30
			if (uap->rusage && (error = copyout((caddr_t)p->p_ru,
			    (caddr_t)uap->rusage, sizeof (struct rusage))))
D 43
				return (error);
E 43
I 43
D 46
				RETURN (error);
E 46
I 46
				return (error);
I 67
			/*
			 * If we got the child via a ptrace 'attach',
			 * we need to give it back to the old parent.
			 */
			if (p->p_oppid && (t = pfind(p->p_oppid))) {
				p->p_oppid = 0;
				proc_reparent(p, t);
				psignal(t, SIGCHLD);
				wakeup((caddr_t)t);
				return (0);
			}
E 67
E 46
E 43
D 52
			pgrm(p);			/* off pgrp */
E 52
E 30
I 25
			p->p_xstat = 0;
D 30
			if (uap->rusage)
				u.u_error = copyout((caddr_t)p->p_ru,
				    (caddr_t)uap->rusage,
				    sizeof (struct rusage));
E 30
D 52
			ruadd(&u.u_cru, p->p_ru);
E 52
I 52
			ruadd(&q->p_stats->p_cru, p->p_ru);
E 52
			FREE(p->p_ru, M_ZOMBIE);
I 72

			/*
			 * Decrement the count of procs running with this uid.
			 */
			(void)chgproccnt(p->p_cred->p_ruid, -1);

			/*
			 * Free up credentials.
			 */
E 72
I 56
			if (--p->p_cred->p_refcnt == 0) {
				crfree(p->p_cred->pc_ucred);
				FREE(p->p_cred, M_SUBPROC);
			}
E 56
D 52
			p->p_ru = 0;
E 25
E 13
			p->p_stat = NULL;
			p->p_pid = 0;
			p->p_ppid = 0;
E 52
I 52

			/*
I 86
			 * Release reference to text vnode
			 */
			if (p->p_textvp)
				vrele(p->p_textvp);

			/*
E 86
			 * Finally finished with old proc entry.
			 * Unlink it from its process group and free it.
			 */
			leavepgrp(p);
E 52
I 8
D 85
			if (*p->p_prev = p->p_nxt)	/* off zombproc */
				p->p_nxt->p_prev = p->p_prev;
E 85
I 85
D 90
			if (*p->p_prev = p->p_next)	/* off zombproc */
				p->p_next->p_prev = p->p_prev;
E 85
D 52
			p->p_nxt = freeproc;		/* onto freeproc */
			freeproc = p;
E 52
E 8
			if (q = p->p_ysptr)
				q->p_osptr = p->p_osptr;
			if (q = p->p_osptr)
				q->p_ysptr = p->p_ysptr;
			if ((q = p->p_pptr)->p_cptr == p)
				q->p_cptr = p->p_osptr;
E 90
I 90
			LIST_REMOVE(p, p_list);	/* off zombproc */
			LIST_REMOVE(p, p_sibling);
E 90
I 55

D 56
#ifdef i386
			cpu_wait(p);			/* XXX */
#endif

E 56
I 56
			/*
			 * Give machine-dependent layer a chance
			 * to free anything that cpu_exit couldn't
			 * release while still running in process context.
			 */
			cpu_wait(p);
E 56
E 55
D 52
			p->p_pptr = 0;
			p->p_ysptr = 0;
			p->p_osptr = 0;
			p->p_cptr = 0;
			p->p_sig = 0;
D 3
			p->p_siga0 = 0;
			p->p_siga1 = 0;
E 3
I 3
			p->p_sigcatch = 0;
			p->p_sigignore = 0;
			p->p_sigmask = 0;
E 3
D 25
			p->p_pgrp = 0;
E 25
I 25
			/*p->p_pgrp = 0;*/
E 25
			p->p_flag = 0;
			p->p_wchan = 0;
E 52
I 52
			FREE(p, M_PROC);
			nprocs--;
E 52
D 45
			p->p_cursig = 0;
E 45
D 25
			return (0);
E 25
I 25
D 30
			return;
E 30
I 30
D 43
			return (0);
E 43
I 43
D 46
			RETURN (0);
E 46
I 46
			return (0);
E 46
E 43
E 30
E 25
		}
D 25
		if (p->p_stat == SSTOP && (p->p_flag&SWTED)==0 &&
		    (p->p_flag&STRC || options&WUNTRACED)) {
E 25
I 25
D 85
		if (p->p_stat == SSTOP && (p->p_flag & SWTED) == 0 &&
		    (p->p_flag & STRC || uap->options & WUNTRACED)) {
E 25
			p->p_flag |= SWTED;
E 85
I 85
		if (p->p_stat == SSTOP && (p->p_flag & P_WAITED) == 0 &&
		    (p->p_flag & P_TRACED || uap->options & WUNTRACED)) {
			p->p_flag |= P_WAITED;
E 85
D 43
			u.u_r.r_val1 = p->p_pid;
E 43
I 43
			retval[0] = p->p_pid;
E 43
D 25
			u.u_r.r_val2 = (p->p_cursig<<8) | WSTOPPED;
			return (0);
E 25
I 25
#ifdef COMPAT_43
D 30
			if (compat)
				u.u_r.r_val2 = (p->p_cursig<<8) | WSTOPPED;
E 30
I 30
D 33
			if (uap->compat)
E 33
I 33
			if (uap->compat) {
E 33
D 43
				u.u_r.r_val2 = W_STOPCODE(p->p_cursig);
E 43
I 43
D 45
				retval[1] = W_STOPCODE(p->p_cursig);
E 45
I 45
				retval[1] = W_STOPCODE(p->p_xstat);
E 45
E 43
E 30
D 33
			else
E 33
I 33
				error = 0;
			} else
E 33
#endif
			if (uap->status) {
D 30
				status.w_status = 0;
				status.w_stopval = WSTOPPED;
				status.w_stopsig = p->p_cursig;
				u.u_error = copyout((caddr_t)&status,
E 30
I 30
D 45
				status = W_STOPCODE(p->p_cursig);
E 45
I 45
				status = W_STOPCODE(p->p_xstat);
E 45
				error = copyout((caddr_t)&status,
E 30
D 58
				    (caddr_t)uap->status, sizeof(status));
E 58
I 58
					(caddr_t)uap->status, sizeof(status));
E 58
D 30
			}
			return;
E 30
I 30
			} else
				error = 0;
D 43
			return (error);
E 43
I 43
D 46
			RETURN (error);
E 46
I 46
			return (error);
E 46
E 43
E 30
E 25
		}
	}
D 3
	if (f == 0) {
E 3
I 3
D 25
	if (f == 0)
E 3
		return (ECHILD);
D 3
	}
E 3
	if (options&WNOHANG) {
E 25
I 25
D 30
	if (f == 0) {
		u.u_error = ECHILD;
		return;
	}
E 30
I 30
D 52
	if (f == 0)
E 52
I 52
	if (nfound == 0)
E 52
D 43
		return (ECHILD);
E 43
I 43
D 46
		RETURN (ECHILD);
E 46
I 46
		return (ECHILD);
E 46
E 43
E 30
	if (uap->options & WNOHANG) {
E 25
D 43
		u.u_r.r_val1 = 0;
D 25
		return (0);
E 25
I 25
D 30
		return;
E 30
I 30
		return (0);
E 43
I 43
		retval[0] = 0;
D 46
		RETURN (0);
E 46
I 46
		return (0);
E 46
E 43
E 30
E 25
	}
D 3
	if ((u.u_procp->p_flag&SNUSIG) && setjmp(&u.u_qsave)) {
E 3
I 3
D 12
	if ((u.u_procp->p_flag&SOUSIG) == 0 && setjmp(&u.u_qsave)) {
E 12
I 12
D 25
	if (setjmp(&u.u_qsave)) {
E 25
I 25
D 28
	if (uap->options & WSIGRESTART && setjmp(&u.u_qsave)) {
E 28
I 28
D 36
	if (setjmp(&u.u_qsave)) {
E 28
E 25
		p = u.u_procp;
D 14
		if ((u.u_sigintr & sigmask(p->p_cursig)) != 0 ||
		    (p->p_flag & SOUSIG) != 0)
E 14
I 14
D 25
		if ((u.u_sigintr & sigmask(p->p_cursig)) != 0)
E 14
			return(EINTR);
E 25
I 25
D 30
		if ((u.u_sigintr & sigmask(p->p_cursig)) != 0) {
			u.u_error = EINTR;
			return;
		}
E 30
I 30
		if ((u.u_sigintr & sigmask(p->p_cursig)) != 0)
			return (EINTR);
E 30
E 25
E 12
E 3
		u.u_eosys = RESTARTSYS;
D 25
		return (0);
E 25
I 25
D 30
		return;
E 30
I 30
		return (0);
E 30
E 25
	}
D 34
	sleep((caddr_t)u.u_procp, PWAIT);
E 34
I 34
	tsleep((caddr_t)u.u_procp, PWAIT, SLP_WAIT, 0);
E 36
I 36
D 43
	if (error = tsleep((caddr_t)u.u_procp, PWAIT | PCATCH, "wait", 0))
		return (error);
E 43
I 43
	if (error = tsleep((caddr_t)q, PWAIT | PCATCH, "wait", 0))
D 46
		RETURN (error);
E 46
I 46
		return (error);
E 46
E 43
E 36
E 34
	goto loop;
I 67
}

/*
 * make process 'parent' the new parent of process 'child'.
 */
void
proc_reparent(child, parent)
	register struct proc *child;
	register struct proc *parent;
{
D 90
	register struct proc *o;
	register struct proc *y;
E 90

	if (child->p_pptr == parent)
		return;

D 90
	/* fix up the child linkage for the old parent */
	o = child->p_osptr;
	y = child->p_ysptr;
	if (y)
		y->p_osptr = o;
	if (o)
		o->p_ysptr = y;
	if (child->p_pptr->p_cptr == child)
		child->p_pptr->p_cptr = o;

	/* fix up child linkage for new parent */
	o = parent->p_cptr;
	if (o)
		o->p_ysptr = child;
	child->p_osptr = o;
	child->p_ysptr = NULL;
	parent->p_cptr = child;
E 90
I 90
	LIST_REMOVE(child, p_sibling);
	LIST_INSERT_HEAD(&parent->p_children, child, p_sibling);
E 90
	child->p_pptr = parent;
E 67
}
E 1
