h36569
s 00002/00002/00077
d D 8.1 93/06/11 15:35:09 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/00068
d D 5.7 92/10/11 10:11:06 bostic 8 7
c make kernel includes standard
e
s 00005/00005/00074
d D 5.6 92/07/10 18:00:11 torek 7 6
c ANSIfy syscall arguments
e
s 00020/00083/00059
d D 5.5 91/01/19 13:16:22 william 6 5
c track TRACE changes
e
s 00000/00000/00142
d D 5.4 91/01/15 12:22:04 bill 5 4
c reno changes
e
s 00013/00014/00129
d D 5.3 90/11/14 16:22:42 bill 4 3
c conventions
e
s 00012/00001/00131
d D 5.2 90/04/24 19:19:32 william 3 2
c 1st Berkeley Release
e
s 00000/00000/00132
d D 5.1 90/04/24 18:52:40 william 2 1
c 1st Berkeley Release
e
s 00132/00000/00000
d D 1.1 90/03/12 15:48:24 bill 1 0
c date and time created 90/03/12 15:48:24 by bill
e
u
U
t
T
I 6
D 7

E 7
E 6
I 1
D 3
/*	sys_machdep.c	1.1	86/01/05	*/
E 3
I 3
D 4

E 4
/*-
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 6
 * %sccs.include.noredist.c%
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
 *	%W% (Berkeley) %G%
 */
E 3

D 4
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
E 4
I 4
D 8
#include "param.h"
#include "systm.h"
D 6
#include "dir.h"
#include "user.h"
E 6
#include "ioctl.h"
#include "file.h"
I 6
#include "time.h"
E 6
#include "proc.h"
#include "uio.h"
#include "kernel.h"
#include "mtio.h"
#include "buf.h"
I 6
#include "trace.h"
E 8
I 8
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/mtio.h>
#include <sys/buf.h>
#include <sys/trace.h>
E 8
E 6
E 4

D 4
#include "../machine/dkio.h"
#include "../machine/pte.h"
E 4
I 4
D 6
#include "machine/dkio.h"
#include "machine/pte.h"
E 4

E 6
#ifdef TRACE
int	nvualarm;

I 7
struct vtrace_args {
	int	request;
	int	value;
};
E 7
D 6
vtrace()
{
	register struct a {
E 6
I 6
vtrace(p, uap, retval)
	struct proc *p;
D 7
	register struct args {
E 6
		int	request;
		int	value;
	} *uap;
E 7
I 7
	register struct args *uap;
E 7
I 6
	int *retval;
{
E 6
	int vdoualarm();

D 6
	uap = (struct a *)u.u_ap;
E 6
	switch (uap->request) {

	case VTR_DISABLE:		/* disable a trace point */
	case VTR_ENABLE:		/* enable a trace point */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 6
			u.u_error = EINVAL;
		else {
			u.u_r.r_val1 = traceflags[uap->value];
			traceflags[uap->value] = uap->request;
		}
E 6
I 6
			return (EINVAL);
		*retval = traceflags[uap->value];
		traceflags[uap->value] = uap->request;
E 6
		break;

	case VTR_VALUE:		/* return a trace point setting */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 6
			u.u_error = EINVAL;
		else
			u.u_r.r_val1 = traceflags[uap->value];
E 6
I 6
			return (EINVAL);
		*retval = traceflags[uap->value];
E 6
		break;

	case VTR_UALARM:	/* set a real-time ualarm, less than 1 min */
D 6
		if (uap->value <= 0 || uap->value > 60 * hz ||
		    nvualarm > 5)
			u.u_error = EINVAL;
		else {
			nvualarm++;
			timeout(vdoualarm, (caddr_t)u.u_procp->p_pid,
			    uap->value);
		}
E 6
I 6
		if (uap->value <= 0 || uap->value > 60 * hz || nvualarm > 5)
			return (EINVAL);
		nvualarm++;
		timeout(vdoualarm, (caddr_t)p->p_pid, uap->value);
E 6
		break;

	case VTR_STAMP:
D 6
		trace(TR_STAMP, uap->value, u.u_procp->p_pid);
E 6
I 6
		trace(TR_STAMP, uap->value, p->p_pid);
E 6
		break;
	}
I 6
	return (0);
E 6
}

vdoualarm(arg)
	int arg;
{
	register struct proc *p;

	p = pfind(arg);
	if (p)
		psignal(p, 16);
	nvualarm--;
D 6
}
#endif

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
E 6
}
#endif
E 1
