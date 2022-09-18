h55272
s 00002/00002/00077
d D 8.1 93/06/10 23:07:53 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/00068
d D 7.3 92/10/11 11:23:23 bostic 3 2
c make kernel includes standard
e
s 00005/00004/00074
d D 7.2 92/07/10 18:10:28 torek 2 1
c ANSIfy syscall args
e
s 00078/00000/00000
d D 7.1 92/01/07 17:29:24 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/ioctl.h"
#include "sys/file.h"
#include "sys/time.h"
#include "sys/proc.h"
#include "sys/uio.h"
#include "sys/kernel.h"
#include "sys/mtio.h"
#include "sys/buf.h"
#include "sys/trace.h"
E 3
I 3
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
E 3

#ifdef TRACE
int	nvualarm;

I 2
struct vtrace_args {
	int	request;
	int	value;
};
E 2
vtrace(p, uap, retval)
	struct proc *p;
D 2
	register struct args {
		int	request;
		int	value;
	} *uap;
E 2
I 2
	register struct vtrace_args *uap;
E 2
	int *retval;
{
	int vdoualarm();

	switch (uap->request) {

	case VTR_DISABLE:		/* disable a trace point */
	case VTR_ENABLE:		/* enable a trace point */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
			return (EINVAL);
		*retval = traceflags[uap->value];
		traceflags[uap->value] = uap->request;
		break;

	case VTR_VALUE:		/* return a trace point setting */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
			return (EINVAL);
		*retval = traceflags[uap->value];
		break;

	case VTR_UALARM:	/* set a real-time ualarm, less than 1 min */
		if (uap->value <= 0 || uap->value > 60 * hz || nvualarm > 5)
			return (EINVAL);
		nvualarm++;
		timeout(vdoualarm, (caddr_t)p->p_pid, uap->value);
		break;

	case VTR_STAMP:
		trace(TR_STAMP, uap->value, p->p_pid);
		break;
	}
	return (0);
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
E 1
