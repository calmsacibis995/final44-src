h38590
s 00002/00002/00084
d D 8.1 93/06/11 15:17:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00084
d D 7.4 93/04/20 23:42:49 torek 4 3
c spelling
e
s 00011/00011/00075
d D 7.3 92/10/11 12:57:26 bostic 3 2
c make kernel includes standard
e
s 00005/00000/00081
d D 7.2 92/07/21 16:54:40 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00081/00000/00000
d D 7.1 92/07/13 00:44:42 torek 1 0
c date and time created 92/07/13 00:44:42 by torek
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: sys_machdep.c,v 1.5 92/07/10 00:29:56 torek Exp $ (LBL)
E 4
I 4
 * from: $Header: sys_machdep.c,v 1.6 92/11/26 03:05:08 torek Exp $ (LBL)
E 4
 */

#ifdef TRACE
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

int	nvualarm;

struct vtrace_args {
	int	request;
	int	value;
};
vtrace(p, uap, retval)
	struct proc *p;
	register struct vtrace_args *uap;
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
	register struct proc *p = pfind(arg);

	if (p != NULL)
		psignal(p, 16);
	nvualarm--;
}
#endif
E 1
