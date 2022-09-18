h18990
s 00009/00007/00143
d D 7.8 92/07/12 15:42:56 torek 16 15
c ANSIfy syscall args
e
s 00000/00001/00150
d D 7.7 91/04/23 12:05:34 sklower 15 14
c dkio.h defined and obsolete ioctl only of interest to hp
e
s 00013/00013/00138
d D 7.6 90/12/16 17:03:17 bostic 14 13
c kernel reorg
e
s 00007/00007/00144
d D 7.5 90/06/28 17:12:04 karels 13 12
c RETURN => return, remove syscontext.h
e
s 00030/00027/00121
d D 7.4 90/06/21 21:20:25 mckusick 12 10
c new system call convention
e
s 00029/00026/00122
d R 7.4 90/06/21 17:43:53 mckusick 11 10
c new system call convention
e
s 00000/00002/00148
d D 7.3 90/02/17 10:48:25 mckusick 10 9
c get rid of unneeded header files
e
s 00002/00001/00148
d D 7.2 89/04/26 18:43:11 mckusick 9 8
c use new form of suser()
e
s 00001/00001/00148
d D 7.1 86/06/05 00:48:15 mckusick 8 7
c 4.3BSD release version
e
s 00007/00001/00142
d D 6.4 85/06/08 13:46:16 mckusick 7 6
c Add copyright
e
s 00014/00014/00129
d D 6.3 84/08/28 18:10:44 bloom 6 5
c Change to includes.  No more ../h
e
s 00001/00000/00142
d D 6.2 83/11/26 19:01:39 sam 5 4
c must never have been compiled for tracing
e
s 00000/00000/00142
d D 6.1 83/07/29 07:21:19 sam 4 3
c 4.2 distribution
e
s 00001/00001/00141
d D 4.3 83/06/21 20:36:47 sam 3 2
c NOCOMPAT->COMPAT
e
s 00004/00003/00138
d D 4.2 83/06/13 03:01:59 sam 2 1
c a couple that got away
e
s 00141/00000/00000
d D 4.1 83/05/27 13:49:01 sam 1 0
c date and time created 83/05/27 13:49:01 by sam
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
/*
D 8
 * Copyright (c) 1982 Regents of the University of California.
E 8
I 8
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 7

D 6
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/ioctl.h"
#include "../h/file.h"
#include "../h/proc.h"
#include "../h/uio.h"
#include "../h/kernel.h"
#include "../h/mtio.h"
#include "../h/buf.h"
I 5
#include "../h/trace.h"
E 6
I 6
D 14
#include "param.h"
#include "systm.h"
D 10
#include "dir.h"
E 10
D 12
#include "user.h"
E 12
I 12
D 13
#include "syscontext.h"
E 13
I 13
#include "user.h"
E 13
E 12
#include "ioctl.h"
#include "file.h"
#include "proc.h"
D 10
#include "uio.h"
E 10
#include "kernel.h"
#include "mtio.h"
#include "buf.h"
#include "trace.h"
E 14
I 14
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/ioctl.h"
#include "sys/file.h"
#include "sys/proc.h"
#include "sys/kernel.h"
#include "sys/mtio.h"
#include "sys/buf.h"
#include "sys/trace.h"
E 14
E 6
E 5

D 6
#include "../vax/dkio.h"
#include "../vax/pte.h"
E 6
I 6
D 15
#include "dkio.h"
E 15
D 14
#include "pte.h"
E 6
#include "../vaxuba/ubareg.h"
#include "../vaxuba/ubavar.h"
E 14
I 14
#include "../include/pte.h"
#include "../uba/ubareg.h"
#include "../uba/ubavar.h"
E 14

I 16
struct resuba_args {
	int	value;
};
E 16
D 12
resuba()
E 12
I 12
/* ARGSUSED */
resuba(p, uap, retval)
	struct proc *p;
D 16
	struct args {
		int	value;
	} *uap;
E 16
I 16
	struct resuba_args *uap;
E 16
	int *retval;
E 12
{
I 12
	int error;
E 12

D 9
	if (suser())
E 9
I 9
D 12
	if (u.u_error = suser(u.u_cred, &u.u_acflag))
		return;
E 9
	if (u.u_arg[0] < numuba)
		ubareset(u.u_arg[0]);
E 12
I 12
	if (error = suser(u.u_cred, &u.u_acflag))
D 13
		RETURN (error);
E 13
I 13
		return (error);
E 13
	if (uap->value < numuba)
		ubareset(uap->value);
D 13
	RETURN (0);
E 13
I 13
	return (0);
E 13
E 12
}

#ifdef TRACE
int	nvualarm;

I 16
struct vtrace_args {
	int	request;
	int	value;
};
E 16
D 12
vtrace()
{
	register struct a {
E 12
I 12
vtrace(p, uap, retval)
	struct proc *p;
D 16
	register struct args {
E 12
		int	request;
		int	value;
	} *uap;
E 16
I 16
	register struct vtrace_args *uap;
E 16
I 12
	int *retval;
{
E 12
	int vdoualarm();

D 12
	uap = (struct a *)u.u_ap;
E 12
	switch (uap->request) {

	case VTR_DISABLE:		/* disable a trace point */
	case VTR_ENABLE:		/* enable a trace point */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 12
			u.u_error = EINVAL;
		else {
			u.u_r.r_val1 = traceflags[uap->value];
			traceflags[uap->value] = uap->request;
		}
E 12
I 12
D 13
			RETURN (EINVAL);
E 13
I 13
			return (EINVAL);
E 13
		*retval = traceflags[uap->value];
		traceflags[uap->value] = uap->request;
E 12
		break;

	case VTR_VALUE:		/* return a trace point setting */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 12
			u.u_error = EINVAL;
		else
			u.u_r.r_val1 = traceflags[uap->value];
E 12
I 12
D 13
			RETURN (EINVAL);
E 13
I 13
			return (EINVAL);
E 13
		*retval = traceflags[uap->value];
E 12
		break;

	case VTR_UALARM:	/* set a real-time ualarm, less than 1 min */
D 12
		if (uap->value <= 0 || uap->value > 60 * hz ||
		    nvualarm > 5)
			u.u_error = EINVAL;
		else {
			nvualarm++;
			timeout(vdoualarm, (caddr_t)u.u_procp->p_pid,
			    uap->value);
		}
E 12
I 12
		if (uap->value <= 0 || uap->value > 60 * hz || nvualarm > 5)
D 13
			RETURN (EINVAL);
E 13
I 13
			return (EINVAL);
E 13
		nvualarm++;
		timeout(vdoualarm, (caddr_t)p->p_pid, uap->value);
E 12
		break;

	case VTR_STAMP:
D 12
		trace(TR_STAMP, uap->value, u.u_procp->p_pid);
E 12
I 12
		trace(TR_STAMP, uap->value, p->p_pid);
E 12
		break;
	}
I 12
D 13
	RETURN (0);
E 13
I 13
	return (0);
E 13
E 12
}

vdoualarm(arg)
	int arg;
{
	register struct proc *p;

	p = pfind(arg);
	if (p)
		psignal(p, 16);
	nvualarm--;
}
#endif

D 3
#ifndef NOCOMPAT
E 3
I 3
#ifdef COMPAT
E 3
/*
 * Note: these tables are sorted by
 * ioctl "code" (in ascending order).
 */
int dctls[] = { DKIOCHDR, 0 };
int fctls[] = { FIOCLEX, FIONCLEX, FIOASYNC, FIONBIO, FIONREAD, 0 };
int mctls[] = { MTIOCTOP, MTIOCGET, 0 };
int tctls[] = {
	TIOCGETD, TIOCSETD, TIOCHPCL, TIOCMODG, TIOCMODS,
	TIOCGETP, TIOCSETP, TIOCSETN, TIOCEXCL, TIOCNXCL,
	TIOCFLUSH,TIOCSETC, TIOCGETC, TIOCREMOTE,TIOCMGET,
	TIOCMBIC, TIOCMBIS, TIOCMSET, TIOCSTART,TIOCSTOP,
D 2
	TIOCPKT,  TIOCNOTTY,TIOCGLTC, TIOCSLTC, TIOCSPGRP,
	TIOCGPGRP,TIOCCDTR, TIOCSDTR, TIOCCBRK, TIOCSBRK,
	TIOCLGET, TIOCLSET, TIOCLBIC, TIOCLBIS, 0
E 2
I 2
	TIOCPKT,  TIOCNOTTY,TIOCSTI,  TIOCOUTQ, TIOCGLTC,
	TIOCSLTC, TIOCSPGRP,TIOCGPGRP,TIOCCDTR, TIOCSDTR,
	TIOCCBRK, TIOCSBRK, TIOCLGET, TIOCLSET, TIOCLBIC,
	TIOCLBIS, 0
E 2
};

/*
 * Map an old style ioctl command to new.
 */
mapioctl(cmd)
	int cmd;
{
	register int *map, c;

	switch ((cmd >> 8) & 0xff) {

	case 'd':
		map = dctls;
		break;

	case 'f':
		map = fctls;
		break;

	case 'm':
		map = mctls;
		break;

	case 't':
		map = tctls;
		break;

	default:
		return (0);
	}
	while ((c = *map) && (c&0xff) < (cmd&0xff))
		map++;
	if (c && (c&0xff) == (cmd&0xff))
		return (c);
	return (0);
}
#endif
E 1
