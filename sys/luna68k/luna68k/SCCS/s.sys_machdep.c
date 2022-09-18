h64087
s 00002/00002/00214
d D 8.1 93/06/10 22:26:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00091/00000/00125
d D 7.4 93/05/12 04:13:04 akito 4 3
c LUNA-II (68040 based LUNA) support
e
s 00007/00007/00118
d D 7.3 93/01/03 12:50:18 akito 3 2
c sync up to hp300/hp300/sys_machdep.c    7.11
e
s 00013/00013/00112
d D 7.2 92/10/11 11:07:55 bostic 2 1
c make kernel includes standard
e
s 00125/00000/00000
d D 7.1 92/06/15 06:38:50 fujita 1 0
c date and time created 92/06/15 06:38:50 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 5
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
D 3
 *	OMRON:$Id: sys_machdep.c,v 1.2 92/06/14 06:22:55 moti Exp $
E 3
I 3
 * from: hp300/hp300/sys_machdep.c	7.11 (Berkeley) 12/27/92
E 3
 *
D 3
 * from: hp300/hp300/sys_machdep.c	7.8 (Berkeley) 6/5/92
 *
E 3
 *	%W% (Berkeley) %G%
 */

D 2
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
#include "vm/vm.h"
E 2
I 2
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
I 3

E 3
#include <vm/vm.h>
E 2

#ifdef TRACE
int	nvualarm;

I 3
struct vtrace_args {
	int	request;
	int	value;
};
E 3
vtrace(p, uap, retval)
	struct proc *p;
D 3
	register struct args {
		int	request;
		int	value;
	} *uap;
E 3
I 3
	register struct vtrace_args *uap;
E 3
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

D 2
#include "../include/cpu.h"
E 2
I 2
#include <machine/cpu.h>
E 2

/* XXX should be in an include file somewhere */
#define CC_PURGE	1
#define CC_FLUSH	2
#define CC_IPURGE	4
#define CC_EXTPURGE	0x80000000
/* XXX end should be */

/*
 * Note that what we do here for a 68040 is different than HP-UX.
 *
 * In 'pux they either act on a line (len == 16), a page (len == NBPG)
 * or the whole cache (len == anything else).
 *
 * In BSD we attempt to be more optimal when acting on "odd" sizes.
 * For lengths up to 1024 we do all affected lines, up to 2*NBPG we
 * do pages, above that we do the entire cache.
 */
/*ARGSUSED1*/
cachectl(req, addr, len)
	int req;
	caddr_t	addr;
	int len;
{
	int error = 0;

I 4
#if defined(LUNA2)
	if (mmutype == MMU_68040) {
		register int inc;
		int pa = 0, doall = 0;
		caddr_t end;

		if (addr == 0 ||
		    (req & ~CC_EXTPURGE) != CC_PURGE && len > 2*NBPG)
			doall = 1;
#ifdef HPUXCOMPAT
		if ((curproc->p_md.md_flags & MDP_HPUX) &&
		    len != 16 && len != NBPG)
			doall = 1;
#endif
		if (!doall) {
			end = addr + len;
			if (len <= 1024) {
				addr = (caddr_t)((int)addr & ~0xF);
				inc = 16;
			} else {
				addr = (caddr_t)((int)addr & ~PGOFSET);
				inc = NBPG;
			}
		}
		do {
			/*
			 * Convert to physical address if needed.
			 * If translation fails, we perform operation on
			 * entire cache (XXX is this a rational thing to do?)
			 */
			if (!doall &&
			    (pa == 0 || ((int)addr & PGOFSET) == 0)) {
				pa = pmap_extract(&curproc->p_vmspace->vm_pmap,
						  (vm_offset_t)addr);
				if (pa == 0)
					doall = 1;
			}
			switch (req) {
			case CC_EXTPURGE|CC_IPURGE:
			case CC_IPURGE:
				if (doall) {
					DCFA();
					ICPA();
				} else if (inc == 16) {
					DCFL(pa);
					ICPL(pa);
				} else if (inc == NBPG) {
					DCFP(pa);
					ICPP(pa);
				}
				break;
			
			case CC_EXTPURGE|CC_PURGE:
			case CC_PURGE:
				if (doall)
					DCFA();	/* note: flush not purge */
				else if (inc == 16)
					DCPL(pa);
				else if (inc == NBPG)
					DCPP(pa);
				break;

			case CC_EXTPURGE|CC_FLUSH:
			case CC_FLUSH:
				if (doall)
					DCFA();
				else if (inc == 16)
					DCFL(pa);
				else if (inc == NBPG)
					DCFP(pa);
				break;
				
			default:
				error = EINVAL;
				break;
			}
			if (doall)
				break;
			pa += inc;
			addr += inc;
		} while (addr < end);
		return(error);
	}
#endif
E 4
	switch (req) {
	case CC_EXTPURGE|CC_PURGE:
	case CC_EXTPURGE|CC_FLUSH:
	case CC_PURGE:
	case CC_FLUSH:
I 4
#if defined(LUNA2)
		DCIU();
#endif
E 4
		break;
	case CC_EXTPURGE|CC_IPURGE:
I 4
#if defined(LUNA2)
		DCIU();
		/* fall into... */
#endif
E 4
	case CC_IPURGE:
		ICIA();
		break;
	default:
		error = EINVAL;
		break;
	}
	return(error);
}
E 1
