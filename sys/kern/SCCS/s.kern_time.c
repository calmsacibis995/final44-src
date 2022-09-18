h03854
s 00008/00000/00399
d D 8.4 95/05/26 16:00:39 mckusick 51 50
c do not allow time to go backwards when in secure mode
e
s 00061/00054/00338
d D 8.3 95/02/14 10:31:54 cgd 50 49
c new argument passing conventions.  minor type size cleanup.
e
s 00003/00001/00389
d D 8.2 94/08/10 23:13:48 mckusick 49 48
c move in NFS specific call from vnode.h
e
s 00002/00002/00388
d D 8.1 93/06/10 21:58:09 bostic 48 47
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00383
d D 7.20 92/10/11 10:38:14 bostic 47 46
c make kernel includes standard
e
s 00032/00017/00358
d D 7.19 92/07/16 13:37:21 torek 46 45
c set tickdelta negative for slower time; clean up and fix adjtime()
e
s 00025/00020/00350
d D 7.18 92/07/10 21:04:13 torek 45 44
c ANSIfy syscall args
e
s 00032/00015/00338
d D 7.17 92/07/08 00:50:39 torek 44 43
c lint; volatile poison; adjustments to time to support new rusage
e
s 00002/00000/00351
d D 7.16 92/01/14 12:19:01 mckusick 43 42
c handle lease updates when time changes
e
s 00006/00007/00345
d D 7.15 91/03/17 15:41:30 karels 42 41
c more-or-less working with new proc & user structs
e
s 00001/00000/00351
d D 7.14 90/08/24 10:40:35 bostic 41 40
c lint
e
s 00001/00011/00350
d D 7.13 90/06/28 21:21:49 bostic 40 39
c new copyright notice
e
s 00016/00016/00345
d D 7.12 90/06/28 17:11:02 karels 39 38
c RETURN => return, remove syscontext.h
e
s 00074/00070/00287
d D 7.11 90/06/21 21:33:39 karels 38 37
c new syscall convention
e
s 00000/00001/00357
d D 7.10 89/05/05 00:06:47 mckusick 37 36
c delete unneeded include of dir.h
e
s 00001/00005/00357
d D 7.9 89/05/01 23:07:58 mckusick 36 34
i 35
c integrate back branch 7.5.1.1
e
s 00025/00021/00333
d D 7.5.1.1 89/05/01 23:00:43 mckusick 35 31
c merge in vnode changes
e
s 00007/00008/00347
d D 7.8 89/04/26 19:41:38 mckusick 34 33
c use new form of suser()
e
s 00002/00002/00353
d D 7.7 89/04/25 14:42:32 mckusick 33 32
c ../machine => machine
e
s 00012/00011/00343
d D 7.6 89/03/01 12:21:27 bostic 32 31
c make `setitimer(timer_type, &timer, &timer);' work
e
s 00000/00001/00354
d D 7.5 87/07/21 13:10:48 mckusick 31 30
c delete unneeded header files
e
s 00017/00013/00338
d D 7.4 87/03/23 17:46:14 bostic 30 29
c changed set/gettimeofday to set/get timezone alone
e
s 00003/00002/00348
d D 7.3 86/11/03 12:00:01 karels 29 28
c merge in tahoe support
e
s 00000/00001/00350
d D 7.2 86/07/27 20:00:44 karels 28 27
c rm extraneous splx
e
s 00001/00001/00350
d D 7.1 86/06/05 00:05:08 mckusick 27 26
c 4.3BSD release version
e
s 00021/00009/00330
d D 6.10 86/05/27 15:21:56 karels 26 25
c use faster adjustment for larger corrections
e
s 00002/00001/00337
d D 6.9 86/02/23 23:09:18 karels 25 24
c lint
e
s 00005/00006/00333
d D 6.8 86/01/13 17:38:31 karels 24 23
c microsecond times using microtime; spl7 => splclock
e
s 00007/00005/00332
d D 6.7 85/10/17 18:55:07 mckusick 23 22
c return old timer value, even when a new one is not specified (from ralph)
e
s 00006/00001/00331
d D 6.6 85/10/11 16:48:59 karels 22 21
c time adj must be multiple of tickadj for now (avoid oscillation)
e
s 00007/00001/00325
d D 6.5 85/06/08 14:38:53 mckusick 21 20
c Add copyright
e
s 00026/00000/00300
d D 6.4 84/11/14 10:04:52 karels 20 19
c adjtime
e
s 00006/00006/00294
d D 6.3 84/08/29 20:20:37 bloom 19 18
c Change to includes.  no more ../h
e
s 00002/00002/00298
d D 6.2 84/06/06 23:06:18 sam 18 17
c fix bug, wasn't setting timezone
c *** CHANGED *** 84/06/06 23:08:32 sam
c never actually SET timezone
e
s 00000/00000/00300
d D 6.1 83/07/29 06:34:37 sam 17 16
c 4.2 distribution
e
s 00001/00001/00299
d D 5.16 83/06/10 21:24:09 sam 16 15
c fixing wrong, set 0 val to tick
e
s 00000/00070/00300
d D 5.15 83/05/27 12:47:24 sam 15 14
c merge of bill's code plus lint (plus, of course, cleanup of bill's bugs)
e
s 00001/00000/00369
d D 5.14 82/12/30 16:28:21 root 14 13
c fix to computation of integral times in kern_clock and alarm(0) in _time
e
s 00015/00022/00354
d D 5.13 82/12/28 23:47:05 sam 13 12
c copyin & copyout now return EFAULT and all callers uniformly 
c return (or ignore) this value
e
s 00002/00001/00374
d D 5.12 82/12/17 11:45:27 sam 12 11
c sun merge
e
s 00001/00001/00374
d D 5.11 82/11/02 11:30:53 root 11 10
c clock name
e
s 00009/00008/00366
d D 5.10 82/10/17 21:49:29 root 10 9
c more lint
e
s 00000/00002/00374
d D 5.9 82/10/17 14:04:50 root 9 8
c fix lint
e
s 00001/00001/00375
d D 5.8 82/10/10 15:08:28 root 8 7
c split header files over to vax directories
e
s 00122/00048/00254
d D 5.7 82/09/11 13:12:25 root 7 6
c cleanup with comments
e
s 00025/00000/00277
d D 5.6 82/09/08 08:07:36 root 6 5
c oalarm now here
e
s 00046/00010/00231
d D 5.5 82/09/08 07:57:39 root 5 4
c timeouts used for all timers now
e
s 00079/00046/00162
d D 5.4 82/09/06 22:54:16 root 4 3
c  
e
s 00164/00062/00044
d D 5.3 82/09/04 09:15:15 root 3 2
c new timeofday and interval timer stuff; itimers need testing
e
s 00020/00005/00086
d D 5.2 82/07/24 18:10:32 root 2 1
c merge with calder
e
s 00091/00000/00000
d D 5.1 82/07/15 20:20:48 root 1 0
c date and time created 82/07/15 20:20:48 by root
e
u
U
f b 
t
T
I 1
D 21
/*	%M%	%I%	%E%	*/
E 21
I 21
/*
D 27
 * Copyright (c) 1982 Regents of the University of California.
E 27
I 27
D 35
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 27
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 35
I 35
D 48
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 48
I 48
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 48
E 35
 *
I 35
D 40
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
E 40
I 40
 * %sccs.include.redist.c%
E 40
 *
E 35
 *	%W% (Berkeley) %G%
 */
E 21

I 12
D 29
#include "../machine/reg.h"

E 29
E 12
D 19
#include "../h/param.h"
D 3
#include "../h/systm.h"
#include "../h/dir.h"
E 3
I 3
#include "../h/dir.h"		/* XXX */
E 3
#include "../h/user.h"
I 3
#include "../h/kernel.h"
E 3
D 12
#include "../h/reg.h"
E 12
#include "../h/inode.h"
#include "../h/proc.h"
E 19
I 19
D 47
#include "param.h"
D 37
#include "dir.h"		/* XXX */
E 37
D 38
#include "user.h"
E 38
I 38
D 39
#include "syscontext.h"
E 39
I 39
D 42
#include "user.h"
E 42
I 42
#include "resourcevar.h"
E 42
E 39
E 38
#include "kernel.h"
I 44
#include "systm.h"
E 44
D 31
#include "inode.h"
E 31
#include "proc.h"
I 43
#include "vnode.h"
E 47
I 47
#include <sys/param.h>
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/vnode.h>
E 47
E 43
I 29

I 50
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 50
D 33
D 35
#include "../machine/reg.h"
#include "../machine/cpu.h"
E 35
I 35
D 42
#include "machine/reg.h"
E 42
D 47
#include "machine/cpu.h"
E 47
I 47
#include <machine/cpu.h>
E 47
E 35
E 33
I 33
D 36
#include "machine/reg.h"
#include "machine/cpu.h"
E 36
E 33
E 29
E 19
D 3
#include "../h/clock.h"
#include "../h/mtpr.h"
#include "../h/timeb.h"
#include "../h/times.h"
#include "../h/reboot.h"
#include "../h/fs.h"
#include "../h/conf.h"
#include "../h/buf.h"
#include "../h/mount.h"
E 3

I 4
/* 
 * Time of day and interval timer support.
I 7
 *
 * These routines provide the kernel entry points to get and set
 * the time-of-day and per-process interval timers.  Subroutines
 * here provide support for adding and subtracting timeval structures
 * and decrementing interval timers, optionally reloading the interval
 * timers when they expire.
E 7
 */

I 45
D 50
struct gettimeofday_args {
	struct	timeval *tp;
	struct	timezone *tzp;
};
E 50
E 45
E 4
D 2
/*
 * return the current time (old-style entry)
 */
gtime()
E 2
I 2
D 3
rtime()
E 3
I 3
D 38
gettimeofday()
E 3
E 2
{
I 3
	register struct a {
E 38
I 38
/* ARGSUSED */
I 50
int
E 50
gettimeofday(p, uap, retval)
	struct proc *p;
D 45
	register struct args {
E 38
		struct	timeval *tp;
		struct	timezone *tzp;
D 38
	} *uap = (struct a *)u.u_ap;
E 38
I 38
	} *uap;
E 45
I 45
D 50
	register struct gettimeofday_args *uap;
E 45
	int *retval;
E 50
I 50
	register struct gettimeofday_args /* {
		syscallarg(struct timeval *) tp;
		syscallarg(struct timezone *) tzp;
	} */ *uap;
	register_t *retval;
E 50
{
E 38
	struct timeval atv;
I 38
	int error = 0;
E 38
I 4
D 24
	int s;
E 24
E 4
E 3
I 2

I 3
D 4
	microtime(&atv);
E 4
I 4
D 24
	s = spl7(); atv = time; splx(s);
E 24
I 24
D 30
	microtime(&atv);
E 24
E 4
D 13
	if (copyout((caddr_t)&atv, (caddr_t)uap->tp, sizeof (atv))) {
		u.u_error = EFAULT;
E 13
I 13
	u.u_error = copyout((caddr_t)&atv, (caddr_t)uap->tp, sizeof (atv));
	if (u.u_error)
E 13
		return;
D 13
	}
E 13
	if (uap->tzp == 0)
		return;
I 4
	/* SHOULD HAVE PER-PROCESS TIMEZONE */
E 4
D 10
	if (copyout((caddr_t)&tz, uap->tzp, sizeof (tz))) {
E 10
I 10
D 13
	if (copyout((caddr_t)&tz, (caddr_t)uap->tzp, sizeof (tz))) {
E 10
		u.u_error = EFAULT;
		return;
	}
E 13
I 13
	u.u_error = copyout((caddr_t)&tz, (caddr_t)uap->tzp, sizeof (tz));
E 30
I 30
D 50
	if (uap->tp) {
E 50
I 50
	if (SCARG(uap, tp)) {
E 50
		microtime(&atv);
D 38
		u.u_error = copyout((caddr_t)&atv, (caddr_t)uap->tp,
			sizeof (atv));
		if (u.u_error)
			return;
E 38
I 38
D 50
		if (error = copyout((caddr_t)&atv, (caddr_t)uap->tp,
E 50
I 50
		if (error = copyout((caddr_t)&atv, (caddr_t)SCARG(uap, tp),
E 50
		    sizeof (atv)))
D 39
			RETURN (error);
E 39
I 39
			return (error);
E 39
E 38
	}
D 50
	if (uap->tzp)
D 38
		u.u_error = copyout((caddr_t)&tz, (caddr_t)uap->tzp,
			sizeof (tz));
E 38
I 38
		error = copyout((caddr_t)&tz, (caddr_t)uap->tzp,
E 50
I 50
	if (SCARG(uap, tzp))
		error = copyout((caddr_t)&tz, (caddr_t)SCARG(uap, tzp),
E 50
		    sizeof (tz));
D 39
	RETURN (error);
E 39
I 39
	return (error);
E 39
E 38
E 30
E 13
E 3
}

I 45
D 50
struct settimeofday_args {
	struct	timeval *tv;
	struct	timezone *tzp;
};
E 50
E 45
I 41
/* ARGSUSED */
I 50
int
E 50
E 41
D 3
rusage()
E 3
I 3
D 38
settimeofday()
E 3
{
I 3
	register struct a {
E 38
I 38
settimeofday(p, uap, retval)
	struct proc *p;
D 45
	struct args {
E 38
D 4
		struct timeval *tv;
		struct timezone *tzp;
E 4
I 4
		struct	timeval *tv;
		struct	timezone *tzp;
E 4
D 38
	} *uap = (struct a *)u.u_ap;
E 38
I 38
	} *uap;
E 45
I 45
D 50
	struct settimeofday_args *uap;
E 45
	int *retval;
E 50
I 50
	struct settimeofday_args /* {
		syscallarg(struct timeval *) tv;
		syscallarg(struct timezone *) tzp;
	} */ *uap;
	register_t *retval;
E 50
{
E 38
D 44
	struct timeval atv;
E 44
I 44
	struct timeval atv, delta;
E 44
	struct timezone atz;
I 35
D 38
	int s;
E 38
I 38
	int error, s;
E 38
E 35
E 3

I 35
D 38
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
E 38
I 38
D 42
	if (error = suser(u.u_cred, &u.u_acflag))
E 42
I 42
	if (error = suser(p->p_ucred, &p->p_acflag))
E 42
D 39
		RETURN (error);
E 39
I 39
		return (error);
I 44
	/* Verify all parameters before changing time. */
D 50
	if (uap->tv &&
	    (error = copyin((caddr_t)uap->tv, (caddr_t)&atv, sizeof(atv))))
E 50
I 50
	if (SCARG(uap, tv) && (error = copyin((caddr_t)SCARG(uap, tv),
	    (caddr_t)&atv, sizeof(atv))))
E 50
		return (error);
D 50
	if (uap->tzp &&
	    (error = copyin((caddr_t)uap->tzp, (caddr_t)&atz, sizeof(atz))))
E 50
I 50
	if (SCARG(uap, tzp) && (error = copyin((caddr_t)SCARG(uap, tzp),
	    (caddr_t)&atz, sizeof(atz))))
E 50
		return (error);
E 44
E 39
E 38
E 35
I 3
D 13
	if (copyin((caddr_t)uap->tv, (caddr_t)&atv, sizeof (struct timeval))) {
		u.u_error = EFAULT;
E 13
I 13
D 30
	u.u_error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
		sizeof (struct timeval));
	if (u.u_error)
E 13
		return;
D 13
	}
E 13
D 4
	if (suser()) {
		struct timeval tdelta;

		tdelta = atv;

		timevalsub(&tdelta, &time);
		timevaladd(&boottime, &tdelta);
		time = atv;
		clockset();
	}
	if (uap->tzp) {
E 4
I 4
	setthetime(&atv);
E 30
I 30
D 50
	if (uap->tv) {
E 50
I 50
	if (SCARG(uap, tv)) {
I 51
		/*
		 * If the system is secure, we do not allow the time to be 
		 * set to an earlier value (it may be slowed using adjtime,
		 * but not set back). This feature prevent interlopers from
		 * setting arbitrary time stamps on files.
		 */
		if (securelevel > 0 && timercmp(&atv, &time, <))
			return (EPERM);
E 51
E 50
D 38
		u.u_error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
			sizeof (struct timeval));
		if (u.u_error)
			return;
E 38
I 38
D 44
		if (error = copyin((caddr_t)uap->tv, (caddr_t)&atv,
		    sizeof (struct timeval)))
D 39
			RETURN (error);
E 39
I 39
			return (error);
E 44
E 39
E 38
D 35
		setthetime(&atv);
E 35
I 35
		/* WHAT DO WE DO ABOUT PENDING REAL-TIME TIMEOUTS??? */
D 44
		boottime.tv_sec += atv.tv_sec - time.tv_sec;
I 43
		LEASE_UPDATETIME(atv.tv_sec - time.tv_sec);
E 43
		s = splhigh(); time = atv; splx(s);
E 44
I 44
		s = splclock();
		/* nb. delta.tv_usec may be < 0, but this is OK here */
		delta.tv_sec = atv.tv_sec - time.tv_sec;
		delta.tv_usec = atv.tv_usec - time.tv_usec;
		time = atv;
		(void) splsoftclock();
		timevaladd(&boottime, &delta);
		timevalfix(&boottime);
		timevaladd(&runtime, &delta);
		timevalfix(&runtime);
D 49
		LEASE_UPDATETIME(delta.tv_sec);
E 49
I 49
#		ifdef NFS
			lease_updatetime(delta.tv_sec);
#		endif
E 49
		splx(s);
E 44
		resettodr();
E 35
	}
E 30
D 34
D 35
	if (uap->tzp && suser()) {
E 35
I 35
D 36
	if (uap->tzp) {
E 35
E 4
D 13
		if (copyin((caddr_t)uap->tzp, (caddr_t)&atz, sizeof (atz))) {
			u.u_error = EFAULT;
E 13
I 13
		u.u_error = copyin((caddr_t)uap->tzp, (caddr_t)&atz,
			sizeof (atz));
D 18
		if (u.u_error)
E 13
			return;
E 18
I 18
		if (u.u_error == 0)
			tz = atz;
E 18
D 13
		}
E 13
D 4
		/* XXX */
E 4
	}
E 34
I 34
	if (uap->tzp == 0 || (u.u_error = suser(u.u_cred, &u.u_acflag)))
E 36
I 36
D 38
	if (uap->tzp == 0)
E 36
		return;
	u.u_error = copyin((caddr_t)uap->tzp, (caddr_t)&atz, sizeof (atz));
	if (u.u_error == 0)
E 38
I 38
D 44
	if (uap->tzp && (error = copyin((caddr_t)uap->tzp, (caddr_t)&atz,
	    sizeof (atz))) == 0)
E 44
I 44
D 50
	if (uap->tzp)
E 50
I 50
	if (SCARG(uap, tzp))
E 50
E 44
E 38
		tz = atz;
I 38
D 39
	RETURN (error);
E 39
I 39
D 44
	return (error);
E 44
I 44
	return (0);
E 44
E 39
E 38
E 34
E 3
}

I 4
D 35
setthetime(tv)
	struct timeval *tv;
{
D 9
	register int delta;
E 9
	int s;

D 34
	if (!suser())
E 34
I 34
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 34
		return;
I 7
/* WHAT DO WE DO ABOUT PENDING REAL-TIME TIMEOUTS??? */
E 7
	boottime.tv_sec += tv->tv_sec - time.tv_sec;
D 24
	s = spl7(); time = *tv; splx(s);
E 24
I 24
	s = splhigh(); time = *tv; splx(s);
E 24
D 11
	clockset();
E 11
I 11
	resettodr();
E 11
}

E 35
I 20
D 26
int adjtimedelta;
I 22
extern int tickadj;
E 26
I 26
extern	int tickadj;			/* "standard" clock skew, us./tick */
int	tickdelta;			/* current clock skew, us. per tick */
long	timedelta;			/* unapplied time correction, us. */
long	bigadj = 1000000;		/* use 10x skew above bigadj us. */
E 26
E 22

I 45
D 50
struct adjtime_args {
	struct timeval *delta;
	struct timeval *olddelta;
};
E 50
E 45
D 38
adjtime()
{
	register struct a {
E 38
I 38
/* ARGSUSED */
I 50
int
E 50
adjtime(p, uap, retval)
	struct proc *p;
D 45
	register struct args {
E 38
		struct timeval *delta;
		struct timeval *olddelta;
D 38
	} *uap = (struct a *)u.u_ap;
E 38
I 38
	} *uap;
E 45
I 45
D 50
	register struct adjtime_args *uap;
E 45
	int *retval;
E 50
I 50
	register struct adjtime_args /* {
		syscallarg(struct timeval *) delta;
		syscallarg(struct timeval *) olddelta;
	} */ *uap;
	register_t *retval;
E 50
{
E 38
D 22

E 22
D 46
	struct timeval atv, oatv;
I 26
	register long ndelta;
E 46
I 46
	struct timeval atv;
	register long ndelta, ntickdelta, odelta;
E 46
E 26
I 22
D 38
	int s;
E 38
I 38
	int s, error;
E 38
E 22

D 34
D 35
	if (!suser()) 
E 35
I 35
D 36
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 36
E 35
E 34
I 34
D 38
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
E 34
		return;
	u.u_error = copyin((caddr_t)uap->delta, (caddr_t)&atv,
		sizeof (struct timeval));
	if (u.u_error)
		return;
E 38
I 38
D 42
	if (error = suser(u.u_cred, &u.u_acflag))
E 42
I 42
	if (error = suser(p->p_ucred, &p->p_acflag))
E 42
D 39
		RETURN (error);
E 39
I 39
		return (error);
E 39
D 50
	if (error =
D 46
	    copyin((caddr_t)uap->delta, (caddr_t)&atv, sizeof (struct timeval)))
E 46
I 46
	    copyin((caddr_t)uap->delta, (caddr_t)&atv, sizeof(struct timeval)))
E 50
I 50
	if (error = copyin((caddr_t)SCARG(uap, delta), (caddr_t)&atv,
	    sizeof(struct timeval)))
E 50
E 46
D 39
		RETURN (error);
E 39
I 39
		return (error);
I 46

	/*
	 * Compute the total correction and the rate at which to apply it.
	 * Round the adjustment down to a whole multiple of the per-tick
	 * delta, so that after some number of incremental changes in
	 * hardclock(), tickdelta will become zero, lest the correction
	 * overshoot and start taking us away from the desired final time.
	 */
E 46
E 39
E 38
I 26
	ndelta = atv.tv_sec * 1000000 + atv.tv_usec;
D 46
	if (timedelta == 0)
		if (ndelta > bigadj)
			tickdelta = 10 * tickadj;
		else
			tickdelta = tickadj;
	if (ndelta % tickdelta)
		ndelta = ndelta / tickadj * tickadj;
E 46
I 46
	if (ndelta > bigadj)
		ntickdelta = 10 * tickadj;
	else
		ntickdelta = tickadj;
	if (ndelta % ntickdelta)
		ndelta = ndelta / ntickdelta * ntickdelta;
E 46

I 46
	/*
	 * To make hardclock()'s job easier, make the per-tick delta negative
	 * if we want time to run slower; then hardclock can simply compute
	 * tick + tickdelta, and subtract tickdelta from timedelta.
	 */
	if (ndelta < 0)
		ntickdelta = -ntickdelta;
E 46
E 26
I 22
	s = splclock();
E 22
D 46
	if (uap->olddelta) {
D 26
		oatv.tv_sec = adjtimedelta / 1000000;
		oatv.tv_usec = adjtimedelta % 1000000;
		(void) copyout((caddr_t)&oatv, (caddr_t)uap->olddelta,
			sizeof (struct timeval));
E 26
I 26
		oatv.tv_sec = timedelta / 1000000;
		oatv.tv_usec = timedelta % 1000000;
E 26
	}
E 46
I 46
	odelta = timedelta;
E 46
D 26
	adjtimedelta = atv.tv_sec * 1000000 + atv.tv_usec;
I 22
	if (adjtimedelta % tickadj)
		adjtimedelta = adjtimedelta / tickadj * tickadj;
E 26
I 26
	timedelta = ndelta;
I 46
	tickdelta = ntickdelta;
E 46
E 26
	splx(s);
I 26

D 46
	if (uap->olddelta)
		(void) copyout((caddr_t)&oatv, (caddr_t)uap->olddelta,
			sizeof (struct timeval));
E 46
I 46
D 50
	if (uap->olddelta) {
E 50
I 50
	if (SCARG(uap, olddelta)) {
E 50
		atv.tv_sec = odelta / 1000000;
		atv.tv_usec = odelta % 1000000;
D 50
		(void) copyout((caddr_t)&atv, (caddr_t)uap->olddelta,
E 50
I 50
		(void) copyout((caddr_t)&atv, (caddr_t)SCARG(uap, olddelta),
E 50
		    sizeof(struct timeval));
	}
E 46
I 38
D 39
	RETURN (0);
E 39
I 39
	return (0);
E 39
E 38
E 26
E 22
}

E 20
E 4
D 3
itimer()
E 3
I 3
D 7
timevaladd(t1, t2)
	struct timeval *t1, *t2;
E 3
{

I 3
	t1->tv_sec += t2->tv_sec;
D 4
	t1->tv_usec += t2->tv_sec;
E 4
I 4
	t1->tv_usec += t2->tv_usec;
E 4
	timevalfix(t1);
E 3
}

D 3
/* BEGIN DEPRECATED */
ogtime()
E 3
I 3
timevalsub(t1, t2)
	struct timeval *t1, *t2;
E 3
{

E 2
D 3
	u.u_r.r_time = time;
	if (clkwrap())
		clkset();
E 3
I 3
	t1->tv_sec -= t2->tv_sec;
D 4
	t1->tv_usec -= t2->tv_sec;
E 4
I 4
	t1->tv_usec -= t2->tv_usec;
E 4
	timevalfix(t1);
E 3
}

D 3
/*
 * New time entry-- return TOD with milliseconds, timezone,
 * DST flag
 */
D 2
ftime()
E 2
I 2
oftime()
E 3
I 3
timevalfix(t1)
	struct timeval *t1;
E 3
E 2
{
I 3

	if (t1->tv_usec < 0) {
		t1->tv_sec--;
		t1->tv_usec += 1000000;
	}
	if (t1->tv_usec >= 1000000) {
		t1->tv_sec++;
		t1->tv_usec -= 1000000;
	}
}

E 7
I 7
/*
 * Get value of an interval timer.  The process virtual and
D 42
 * profiling virtual time timers are kept in the u. area, since
E 42
I 42
 * profiling virtual time timers are kept in the p_stats area, since
E 42
 * they can be swapped out.  These are kept internally in the
 * way they are specified externally: in time until they expire.
 *
 * The real time interval timer is kept in the process table slot
 * for the process, and its value (it_value) is kept as an
 * absolute time rather than as a delta, so that it is easy to keep
 * periodic real-time signals from drifting.
 *
 * Virtual time timers are processed in the hardclock() routine of
 * kern_clock.c.  The real time timer is processed by a timeout
 * routine, called from the softclock() routine.  Since a callout
 * may be delayed in real time due to interrupt processing in the system,
 * it is possible for the real time timeout routine (realitexpire, given below),
 * to be delayed in real time past when it is supposed to occur.  It
 * does not suffice, therefore, to reload the real timer .it_value from the
 * real time timers .it_interval.  Rather, we compute the next time in
 * absolute time the timer should go off.
 */
I 45
D 50
struct getitimer_args {
	u_int	which;
	struct	itimerval *itv;
};
E 50
E 45
E 7
D 38
getitimer()
{
E 3
	register struct a {
E 38
I 38
/* ARGSUSED */
I 50
int
E 50
getitimer(p, uap, retval)
	struct proc *p;
D 45
	register struct args {
E 38
D 3
		struct	timeb	*tp;
	} *uap;
	struct timeb t;
	register unsigned ms;
E 3
I 3
		u_int	which;
		struct	itimerval *itv;
D 38
	} *uap = (struct a *)u.u_ap;
E 38
I 38
	} *uap;
E 45
I 45
D 50
	register struct getitimer_args *uap;
E 45
	int *retval;
E 50
I 50
	register struct getitimer_args /* {
		syscallarg(u_int) which;
		syscallarg(struct itimerval *) itv;
	} */ *uap;
	register_t *retval;
E 50
{
E 38
D 5
	register struct itimerval *itp;
E 5
I 5
	struct itimerval aitv;
E 5
	int s;
E 3

D 3
	uap = (struct a *)u.u_ap;
	(void) spl7();
	t.time = time;
	ms = lbolt;
	(void) spl0();
	if (ms > hz) {
		ms -= hz;
		t.time++;
E 3
I 3
D 32
	if (uap->which > 2) {
E 32
I 32
D 38
	if (uap->which > ITIMER_PROF) {
E 32
		u.u_error = EINVAL;
		return;
E 3
	}
E 38
I 38
D 50
	if (uap->which > ITIMER_PROF)
E 50
I 50
	if (SCARG(uap, which) > ITIMER_PROF)
E 50
D 39
		RETURN (EINVAL);
E 39
I 39
		return (EINVAL);
E 39
E 38
D 3
	t.millitm = (1000*ms)/hz;
	t.timezone = timezone;
	t.dstflag = dstflag;
	if (copyout((caddr_t)&t, (caddr_t)uap->tp, sizeof(t)) < 0)
E 3
I 3
D 5
	if (uap->which == ITIMER_REAL)
		itp = &u.u_procp->p_realtimer;
	else
		itp = &u.u_timer[uap->which];
E 5
D 24
	s = spl7();
E 24
I 24
	s = splclock();
E 24
D 4
	if (copyout((caddr_t)itp, uap->itv, sizeof (struct itimerval))) {
E 4
I 4
D 5
	if (copyout((caddr_t)itp, uap->itv, sizeof (struct itimerval)))
E 5
I 5
D 50
	if (uap->which == ITIMER_REAL) {
E 50
I 50
	if (SCARG(uap, which) == ITIMER_REAL) {
E 50
I 7
		/*
D 50
		 * Convert from absoulte to relative time in .it_value
E 50
I 50
		 * Convert from absolute to relative time in .it_value
E 50
		 * part of real time timer.  If time for real time timer
		 * has passed return 0, else return difference between
		 * current time and time for the timer to go off.
		 */
E 7
D 38
		aitv = u.u_procp->p_realtimer;
E 38
I 38
		aitv = p->p_realtimer;
E 38
		if (timerisset(&aitv.it_value))
			if (timercmp(&aitv.it_value, &time, <))
				timerclear(&aitv.it_value);
			else
D 44
				timevalsub(&aitv.it_value, &time);
E 44
I 44
				timevalsub(&aitv.it_value,
				    (struct timeval *)&time);
E 44
	} else
D 42
		aitv = u.u_timer[uap->which];
E 42
I 42
D 50
		aitv = p->p_stats->p_timer[uap->which];
E 50
I 50
		aitv = p->p_stats->p_timer[SCARG(uap, which)];
E 50
E 42
	splx(s);
D 10
	if (copyout((caddr_t)&aitv, uap->itv, sizeof (struct itimerval)))
E 10
I 10
D 13
	if (copyout((caddr_t)&aitv, (caddr_t)uap->itv,
	    sizeof (struct itimerval)))
E 10
E 5
E 4
E 3
		u.u_error = EFAULT;
E 13
I 13
D 38
	u.u_error = copyout((caddr_t)&aitv, (caddr_t)uap->itv,
	    sizeof (struct itimerval));
E 38
I 38
D 39
	RETURN (copyout((caddr_t)&aitv, (caddr_t)uap->itv,
E 39
I 39
D 50
	return (copyout((caddr_t)&aitv, (caddr_t)uap->itv,
E 50
I 50
	return (copyout((caddr_t)&aitv, (caddr_t)SCARG(uap, itv),
E 50
E 39
	    sizeof (struct itimerval)));
E 38
E 13
D 3
	if (clkwrap())
		clkset();
E 3
I 3
D 4
		goto bad;
	}
bad:
E 4
D 28
	splx(s);
E 28
E 3
}
I 2
D 3
/* END DEPRECATED */
E 3
E 2

I 45
D 50
struct setitimer_args {
	u_int	which;
	struct	itimerval *itv, *oitv;
};
E 50
E 45
D 3
/*
 * Set the time
 */
stime()
E 3
I 3
D 38
setitimer()
E 3
{
	register struct a {
E 38
I 38
/* ARGSUSED */
I 50
int
E 50
setitimer(p, uap, retval)
	struct proc *p;
D 45
	register struct args {
E 38
D 3
		time_t	time;
	} *uap;
E 3
I 3
		u_int	which;
D 4
		struct	itimerval *itv;
E 4
I 4
		struct	itimerval *itv, *oitv;
E 4
D 38
	} *uap = (struct a *)u.u_ap;
E 38
I 38
	} *uap;
E 45
I 45
D 50
	register struct setitimer_args *uap;
E 45
	int *retval;
E 50
I 50
	register struct setitimer_args /* {
		syscallarg(u_int) which;
		syscallarg(struct itimerval *) itv;
		syscallarg(struct itimerval *) oitv;
	} */ *uap;
	register_t *retval;
E 50
{
E 38
D 23
	struct itimerval aitv;
E 23
I 23
D 32
	struct itimerval aitv, *aitvp;
E 32
I 32
	struct itimerval aitv;
	register struct itimerval *itvp;
E 32
E 23
D 38
	int s;
I 5
	register struct proc *p = u.u_procp;
E 38
I 38
	int s, error;
E 38
E 5
E 3

D 3
	uap = (struct a *)u.u_ap;
	if (suser()) {
		bootime += uap->time - time;
		time = uap->time;
		clkset();
E 3
I 3
D 4
	s = spl7();
E 4
D 32
	if (uap->which > 2) {
E 32
I 32
D 38
	if (uap->which > ITIMER_PROF) {
E 32
		u.u_error = EINVAL;
D 4
		goto bad;
E 4
I 4
		return;
E 4
E 3
	}
E 38
I 38
D 50
	if (uap->which > ITIMER_PROF)
E 50
I 50
	if (SCARG(uap, which) > ITIMER_PROF)
E 50
D 39
		RETURN (EINVAL);
E 39
I 39
		return (EINVAL);
E 39
E 38
I 3
D 13
	if (copyin((caddr_t)uap->itv, (caddr_t)&aitv,
	    sizeof (struct itimerval))) {
		u.u_error = EFAULT;
E 13
I 13
D 23
	u.u_error = copyin((caddr_t)uap->itv, (caddr_t)&aitv,
	    sizeof (struct itimerval));
	if (u.u_error)
E 13
D 4
		goto bad;
E 4
I 4
		return;
E 23
I 23
D 32
	aitvp = uap->itv;
E 23
E 4
D 13
	}
E 13
D 4
	u.u_timer[uap->which] = aitv;
E 4
I 4
	if (uap->oitv) {
		uap->itv = uap->oitv;
E 32
I 32
D 50
	itvp = uap->itv;
E 50
I 50
	itvp = SCARG(uap, itv);
E 50
D 38
	if (itvp && (u.u_error = copyin((caddr_t)itvp, (caddr_t)&aitv,
E 38
I 38
	if (itvp && (error = copyin((caddr_t)itvp, (caddr_t)&aitv,
E 38
	    sizeof(struct itimerval))))
D 38
		return;
	if (uap->itv = uap->oitv) {
E 32
		getitimer();
I 32
		if (u.u_error)
			return;
E 32
	}
E 38
I 38
D 39
		RETURN (error);
E 39
I 39
		return (error);
E 39
D 50
	if ((uap->itv = uap->oitv) && (error = getitimer(p, uap, retval)))
E 50
I 50
	if ((SCARG(uap, itv) = SCARG(uap, oitv)) &&
	    (error = getitimer(p, uap, retval)))
E 50
D 39
		RETURN (error);
E 39
I 39
		return (error);
E 39
E 38
I 23
D 32
	if (aitvp == 0)
		return;
D 25
	u.u_error = copyin(aitvp, (caddr_t)&aitv, sizeof (struct itimerval));
E 25
I 25
	u.u_error = copyin((caddr_t)aitvp, (caddr_t)&aitv,
	    sizeof (struct itimerval));
E 25
	if (u.u_error)
E 32
I 32
	if (itvp == 0)
E 32
D 38
		return;
E 23
	if (itimerfix(&aitv.it_value) || itimerfix(&aitv.it_interval)) {
		u.u_error = EINVAL;
		return;
	}
E 38
I 38
		return (0);
	if (itimerfix(&aitv.it_value) || itimerfix(&aitv.it_interval))
D 39
		RETURN (EINVAL);
E 39
I 39
		return (EINVAL);
E 39
E 38
D 24
	s = spl7();
E 24
I 24
	s = splclock();
E 24
E 4
D 5
	if (uap->which == ITIMER_REAL)
		u.u_procp->p_realtimer = aitv;
D 4
bad:
E 4
I 4
	else
E 5
I 5
D 50
	if (uap->which == ITIMER_REAL) {
E 50
I 50
	if (SCARG(uap, which) == ITIMER_REAL) {
E 50
D 7
		untimeout(unrto, p);
E 7
I 7
D 10
		untimeout(realitexpire, p);
E 10
I 10
		untimeout(realitexpire, (caddr_t)p);
E 10
E 7
		if (timerisset(&aitv.it_value)) {
D 44
			timevaladd(&aitv.it_value, &time);
E 44
I 44
			timevaladd(&aitv.it_value, (struct timeval *)&time);
E 44
D 7
			timeout(unrto, p, hzto(&aitv.it_value));
E 7
I 7
D 10
			timeout(realitexpire, p, hzto(&aitv.it_value));
E 10
I 10
			timeout(realitexpire, (caddr_t)p, hzto(&aitv.it_value));
E 10
E 7
		}
		p->p_realtimer = aitv;
	} else
E 5
D 42
		u.u_timer[uap->which] = aitv;
E 42
I 42
D 50
		p->p_stats->p_timer[uap->which] = aitv;
E 50
I 50
		p->p_stats->p_timer[SCARG(uap, which)] = aitv;
E 50
E 42
E 4
	splx(s);
I 38
D 39
	RETURN (0);
E 39
I 39
	return (0);
E 39
E 38
D 4
	return;
E 4
E 3
}

I 5
D 7
unrto(p)
E 7
I 7
/*
 * Real interval timer expired:
 * send process whose timer expired an alarm signal.
 * If time is not set up to reload, then just return.
 * Else compute next time timer should go off which is > current time.
 * This is where delay in processing this timeout causes multiple
 * SIGALRM calls to be compressed into one.
 */
D 44
realitexpire(p)
E 7
	register struct proc *p;
E 44
I 44
void
realitexpire(arg)
	void *arg;
E 44
{
I 44
	register struct proc *p;
E 44
	int s;

I 44
	p = (struct proc *)arg;
E 44
	psignal(p, SIGALRM);
	if (!timerisset(&p->p_realtimer.it_interval)) {
		timerclear(&p->p_realtimer.it_value);
		return;
	}
	for (;;) {
D 24
		s = spl7();
E 24
I 24
		s = splclock();
E 24
		timevaladd(&p->p_realtimer.it_value,
		    &p->p_realtimer.it_interval);
		if (timercmp(&p->p_realtimer.it_value, &time, >)) {
D 7
			timeout(unrto, p, hzto(&p->p_realtimer.it_value));
E 7
I 7
D 10
			timeout(realitexpire,
			    p, hzto(&p->p_realtimer.it_value));
E 10
I 10
			timeout(realitexpire, (caddr_t)p,
			    hzto(&p->p_realtimer.it_value));
E 10
E 7
			splx(s);
			return;
		}
		splx(s);
	}
}

I 7
/*
 * Check that a proposed value to load into the .it_value or
 * .it_interval part of an interval timer is acceptable, and
 * fix it to have at least minimal value (i.e. if it is less
 * than the resolution of the clock, round it up.)
 */
I 50
int
E 50
E 7
E 5
D 3
times()
E 3
I 3
D 4
getandsetitimer()
E 4
I 4
itimerfix(tv)
	struct timeval *tv;
E 4
E 3
{
I 3
D 4
	int s = spl7();
E 4

D 4
	getitimer();
	if (u.u_error == 0) {
		u.u_ap[1] = u.u_ap[2];
		setitimer();
	}
	splx(s);
E 4
I 4
D 5
	if (tv->tv_sec < 0 || tv->tv_usec < 0)
E 5
I 5
	if (tv->tv_sec < 0 || tv->tv_sec > 100000000 ||
	    tv->tv_usec < 0 || tv->tv_usec >= 1000000)
E 5
		return (EINVAL);
D 16
	if (tv->tv_sec == 0 && tv->tv_usec < tick)
E 16
I 16
	if (tv->tv_sec == 0 && tv->tv_usec != 0 && tv->tv_usec < tick)
E 16
		tv->tv_usec = tick;
	return (0);
E 4
}

I 7
/*
 * Decrement an interval timer by a specified number
 * of microseconds, which must be less than a second,
 * i.e. < 1000000.  If the timer expires, then reload
 * it.  In this case, carry over (usec - old value) to
D 44
 * reducint the value reloaded into the timer so that
E 44
I 44
 * reduce the value reloaded into the timer so that
E 44
 * the timer does not drift.  This routine assumes
 * that it is called in a context where the timers
 * on which it is operating cannot change in value.
 */
I 50
int
E 50
E 7
itimerdecr(itp, usec)
	register struct itimerval *itp;
	int usec;
{

D 4
	while (itp->itimer_value.tv_usec < usec) {
		if (itp->itimer_value.tv_sec == 0)
E 4
I 4
	if (itp->it_value.tv_usec < usec) {
		if (itp->it_value.tv_sec == 0) {
I 7
			/* expired, and already in next interval */
E 7
			usec -= itp->it_value.tv_usec;
E 4
			goto expire;
D 4
		itp->itimer_value.tv_usec += 1000000;
		itp->itimer_value.tv_sec--;
E 4
I 4
		}
		itp->it_value.tv_usec += 1000000;
		itp->it_value.tv_sec--;
E 4
	}
D 4
	itp->itimer_value.tv_usec -= usec;
	if (timerisset(&itp->itimer_value))
E 4
I 4
	itp->it_value.tv_usec -= usec;
	usec = 0;
	if (timerisset(&itp->it_value))
E 4
		return (1);
I 7
	/* expired, exactly at end of interval */
E 7
expire:
D 4
	if (itp->itimer_reload == 0)
		itp->itimer_value.tv_usec = 0;
	else
		itp->itimer_value = itp->itimer_interval;
E 4
I 4
	if (timerisset(&itp->it_interval)) {
		itp->it_value = itp->it_interval;
		itp->it_value.tv_usec -= usec;
		if (itp->it_value.tv_usec < 0) {
			itp->it_value.tv_usec += 1000000;
			itp->it_value.tv_sec--;
		}
	} else
D 7
		itp->it_value.tv_usec = 0;
E 7
I 7
		itp->it_value.tv_usec = 0;		/* sec is already 0 */
E 7
E 4
	return (0);
}

I 7
/*
 * Add and subtract routines for timevals.
 * N.B.: subtract routine doesn't deal with
 * results which are before the beginning,
 * it just gets very confused in this case.
 * Caveat emptor.
 */
timevaladd(t1, t2)
	struct timeval *t1, *t2;
{

	t1->tv_sec += t2->tv_sec;
	t1->tv_usec += t2->tv_usec;
	timevalfix(t1);
}

timevalsub(t1, t2)
	struct timeval *t1, *t2;
{

	t1->tv_sec -= t2->tv_sec;
	t1->tv_usec -= t2->tv_usec;
	timevalfix(t1);
}

timevalfix(t1)
	struct timeval *t1;
{

	if (t1->tv_usec < 0) {
		t1->tv_sec--;
		t1->tv_usec += 1000000;
	}
	if (t1->tv_usec >= 1000000) {
		t1->tv_sec++;
		t1->tv_usec -= 1000000;
	}
}
D 15

E 7
#ifndef NOCOMPAT
otime()
{

	u.u_r.r_time = time.tv_sec;
}

I 4
ostime()
{
	register struct a {
		int	time;
	} *uap = (struct a *)u.u_ap;
	struct timeval tv;

	tv.tv_sec = uap->time;
	tv.tv_usec = 0;
	setthetime(&tv);
}

E 4
D 7
#include "../h/timeb.h"
E 7
I 7
/* from old timeb.h */
struct timeb {
	time_t	time;
	u_short	millitm;
	short	timezone;
	short	dstflag;
};
E 7

oftime()
{
E 3
	register struct a {
D 3
		time_t	(*times)[4];
E 3
I 3
		struct	timeb	*tp;
E 3
	} *uap;
D 3
	struct tms tms;
E 3
I 3
D 7
	struct timeb t;
E 7
I 7
	struct timeb tb;
E 7
E 3

D 3
	tms.tms_utime = u.u_vm.vm_utime;
	tms.tms_stime = u.u_vm.vm_stime;
	tms.tms_cutime = u.u_cvm.vm_utime;
	tms.tms_cstime = u.u_cvm.vm_stime;
E 3
	uap = (struct a *)u.u_ap;
D 3
	if (copyout((caddr_t)&tms, (caddr_t)uap->times, sizeof(struct tms)) < 0)
E 3
I 3
	(void) spl7();
D 7
	t.time = time.tv_sec;
	t.millitm = time.tv_usec / 1000;
E 7
I 7
	tb.time = time.tv_sec;
	tb.millitm = time.tv_usec / 1000;
E 7
	(void) spl0();
D 7
	t.timezone = tz.tz_minuteswest;
	t.dstflag = tz.tz_dsttime;
	if (copyout((caddr_t)&t, (caddr_t)uap->tp, sizeof(t)) < 0)
E 7
I 7
	tb.timezone = tz.tz_minuteswest;
	tb.dstflag = tz.tz_dsttime;
D 8
	if (copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof(t)) < 0)
E 8
I 8
D 13
	if (copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb)) < 0)
E 8
E 7
E 3
		u.u_error = EFAULT;
E 13
I 13
	u.u_error = copyout((caddr_t)&tb, (caddr_t)uap->tp, sizeof (tb));
E 13
}
I 4
D 7
#endif
E 7
I 7

E 7
I 6
oalarm()
{
	register struct a {
		int	deltat;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p = u.u_procp;
D 9
	struct timeval atv;
E 9
	int s = spl7();

D 7
	untimeout(unrto, p);
E 7
I 7
D 10
	untimeout(realitexpire, p);
E 10
I 10
	untimeout(realitexpire, (caddr_t)p);
E 10
E 7
	timerclear(&p->p_realtimer.it_interval);
	u.u_r.r_val1 = 0;
	if (timerisset(&p->p_realtimer.it_value) &&
	    timercmp(&p->p_realtimer.it_value, &time, >))
		u.u_r.r_val1 = p->p_realtimer.it_value.tv_sec - time.tv_sec;
	if (uap->deltat == 0) {
I 14
		timerclear(&p->p_realtimer.it_value);
E 14
		splx(s);
		return;
	}
	p->p_realtimer.it_value = time;
	p->p_realtimer.it_value.tv_sec += uap->deltat;
D 7
	timeout(unrto, p, hzto(&p->p_realtimer.it_value));
E 7
I 7
D 10
	timeout(realitexpire, p, hzto(&p->p_realtimer.it_value));
E 10
I 10
	timeout(realitexpire, (caddr_t)p, hzto(&p->p_realtimer.it_value));
E 10
E 7
	splx(s);
}
D 7

E 7
I 7
#endif
E 15
E 7
E 6
E 4
E 1
