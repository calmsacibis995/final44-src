h21384
s 00005/00004/00071
d D 7.7 92/07/12 15:39:14 torek 8 7
c ANSIfy syscall args
e
s 00010/00010/00065
d D 7.6 90/12/16 16:46:51 bostic 7 6
c kernel reorg
e
s 00004/00004/00071
d D 7.5 90/06/28 17:10:34 karels 6 5
c RETURN => return, remove syscontext.h
e
s 00017/00021/00058
d D 7.4 90/06/21 15:49:47 mckusick 5 4
c new system call convention
e
s 00000/00056/00079
d D 7.3 89/08/14 18:36:30 karels 4 3
c half of it is gone; the other half later
e
s 00000/00002/00135
d D 7.2 89/05/05 00:17:16 mckusick 3 2
c delete unneeded include files
e
s 00019/00014/00118
d D 7.1 88/05/21 18:36:28 karels 2 1
c bring up to revision 7 for tahoe release
e
s 00132/00000/00000
d D 1.1 86/01/05 18:47:46 sam 1 0
c date and time created 86/01/05 18:47:46 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 2

D 2
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
E 2
I 2
D 7
#include "param.h"
#include "systm.h"
D 3
#include "dir.h"
E 3
#include "user.h"
#include "ioctl.h"
#include "file.h"
#include "proc.h"
D 3
#include "uio.h"
E 3
#include "kernel.h"
#include "mtio.h"
#include "buf.h"
E 7
I 7
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/user.h"
#include "sys/ioctl.h"
#include "sys/file.h"
#include "sys/proc.h"
#include "sys/kernel.h"
#include "sys/mtio.h"
#include "sys/buf.h"
E 7
E 2

D 2
#include "../machine/dkio.h"
#include "../machine/pte.h"
E 2
I 2
D 7
#include "pte.h"
E 7
I 7
#include "../include/pte.h"
E 7
E 2

#ifdef TRACE
int	nvualarm;

I 8
struct vtrace_args {
	int	request;
	int	value;
};
E 8
D 5
vtrace()
{
	register struct a {
E 5
I 5
/* ARGSUSED */
vtrace(p, uap, retval)
	register struct proc *p;
D 8
	register struct args {
E 5
		int	request;
		int	value;
	} *uap;
E 8
I 8
	register struct vtrace_args *uap;
E 8
I 5
	int *retval;
{
E 5
	int vdoualarm();

D 5
	uap = (struct a *)u.u_ap;
E 5
	switch (uap->request) {

	case VTR_DISABLE:		/* disable a trace point */
	case VTR_ENABLE:		/* enable a trace point */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 5
			u.u_error = EINVAL;
		else {
			u.u_r.r_val1 = traceflags[uap->value];
			traceflags[uap->value] = uap->request;
		}
E 5
I 5
D 6
			RETURN (EINVAL);
E 6
I 6
			return (EINVAL);
E 6
		*retval = traceflags[uap->value];
		traceflags[uap->value] = uap->request;
E 5
		break;

	case VTR_VALUE:		/* return a trace point setting */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 5
			u.u_error = EINVAL;
		else
			u.u_r.r_val1 = traceflags[uap->value];
E 5
I 5
D 6
			RETURN (EINVAL);
E 6
I 6
			return (EINVAL);
E 6
		*retval = traceflags[uap->value];
E 5
		break;

	case VTR_UALARM:	/* set a real-time ualarm, less than 1 min */
D 5
		if (uap->value <= 0 || uap->value > 60 * hz ||
		    nvualarm > 5)
			u.u_error = EINVAL;
		else {
			nvualarm++;
			timeout(vdoualarm, (caddr_t)u.u_procp->p_pid,
			    uap->value);
		}
E 5
I 5
		if (uap->value <= 0 || uap->value > 60 * hz || nvualarm > 5)
D 6
			RETURN (EINVAL);
E 6
I 6
			return (EINVAL);
E 6
		nvualarm++;
		timeout(vdoualarm, (caddr_t)p->p_pid, uap->value);
E 5
		break;

	case VTR_STAMP:
D 5
		trace(TR_STAMP, uap->value, u.u_procp->p_pid);
E 5
I 5
		trace(TR_STAMP, uap->value, p->p_pid);
E 5
		break;
	}
I 5
D 6
	RETURN (0);
E 6
I 6
	return (0);
E 6
E 5
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
D 4

#ifdef COMPAT
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
	TIOCPKT,  TIOCNOTTY,TIOCSTI,  TIOCOUTQ, TIOCGLTC,
	TIOCSLTC, TIOCSPGRP,TIOCGPGRP,TIOCCDTR, TIOCSDTR,
	TIOCCBRK, TIOCSBRK, TIOCLGET, TIOCLSET, TIOCLBIC,
	TIOCLBIS, 0
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
E 4
E 1
