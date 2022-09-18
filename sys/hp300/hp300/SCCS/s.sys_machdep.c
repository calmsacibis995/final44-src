h49642
s 00001/00001/00218
d D 8.2 94/01/13 22:39:36 hibler 13 12
c lint
e
s 00002/00002/00217
d D 8.1 93/06/10 21:41:37 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00217
d D 7.11 92/12/27 09:53:41 hibler 11 10
c SHPUX has moved
e
s 00014/00013/00204
d D 7.10 92/10/11 09:42:49 bostic 10 9
c make kernel includes standard
e
s 00005/00004/00212
d D 7.9 92/07/10 22:02:31 torek 9 8
c ANSIfy syscall args
e
s 00094/00000/00122
d D 7.8 92/06/05 15:37:01 hibler 8 7
c merge latest Utah hp300 code including 68040 support
e
s 00047/00000/00075
d D 7.7 91/05/07 10:01:15 hibler 7 6
c added cachectl syscall
e
s 00011/00011/00064
d D 7.6 90/12/16 16:36:40 bostic 6 5
c kernel reorg
e
s 00000/00002/00075
d D 7.5 90/12/05 18:53:39 mckusick 5 4
c update from Mike Hibler for new VM and other machine support
e
s 00001/00000/00076
d D 7.4 90/06/28 19:22:36 karels 4 3
c need time.h if no user.h
e
s 00004/00005/00072
d D 7.3 90/06/28 17:29:55 karels 3 2
c RETURN => return, remove syscontext.h
e
s 00017/00022/00060
d D 7.2 90/06/21 16:27:34 mckusick 2 1
c new system call convention
e
s 00082/00000/00000
d D 7.1 90/05/08 18:09:13 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 6
#include "param.h"
#include "systm.h"
D 2
#include "user.h"
E 2
I 2
D 3
#include "syscontext.h"
E 3
E 2
#include "ioctl.h"
#include "file.h"
I 4
#include "time.h"
E 4
#include "proc.h"
#include "uio.h"
#include "kernel.h"
#include "mtio.h"
#include "buf.h"
#include "trace.h"
E 6
I 6
D 10
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
I 8
#include "vm/vm.h"
E 10
I 10
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
E 10
E 8
E 6

I 10
#include <vm/vm.h>

E 10
D 5
#include "pte.h"

E 5
#ifdef TRACE
int	nvualarm;

I 9
struct vtrace_args {
	int	request;
	int	value;
};
E 9
D 2
vtrace()
{
	register struct a {
E 2
I 2
vtrace(p, uap, retval)
	struct proc *p;
D 9
	register struct args {
E 2
		int	request;
		int	value;
	} *uap;
E 9
I 9
	register struct vtrace_args *uap;
E 9
I 2
	int *retval;
{
E 2
	int vdoualarm();

D 2
	uap = (struct a *)u.u_ap;
E 2
	switch (uap->request) {

	case VTR_DISABLE:		/* disable a trace point */
	case VTR_ENABLE:		/* enable a trace point */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 2
			u.u_error = EINVAL;
		else {
			u.u_r.r_val1 = traceflags[uap->value];
			traceflags[uap->value] = uap->request;
		}
E 2
I 2
D 3
			RETURN (EINVAL);
E 3
I 3
			return (EINVAL);
E 3
		*retval = traceflags[uap->value];
		traceflags[uap->value] = uap->request;
E 2
		break;

	case VTR_VALUE:		/* return a trace point setting */
		if (uap->value < 0 || uap->value >= TR_NFLAGS)
D 2
			u.u_error = EINVAL;
		else
			u.u_r.r_val1 = traceflags[uap->value];
E 2
I 2
D 3
			RETURN (EINVAL);
E 3
I 3
			return (EINVAL);
E 3
		*retval = traceflags[uap->value];
E 2
		break;

	case VTR_UALARM:	/* set a real-time ualarm, less than 1 min */
D 2
		if (uap->value <= 0 || uap->value > 60 * hz ||
		    nvualarm > 5)
			u.u_error = EINVAL;
		else {
			nvualarm++;
			timeout(vdoualarm, (caddr_t)u.u_procp->p_pid,
			    uap->value);
		}
E 2
I 2
		if (uap->value <= 0 || uap->value > 60 * hz || nvualarm > 5)
D 3
			RETURN (EINVAL);
E 3
I 3
			return (EINVAL);
E 3
		nvualarm++;
		timeout(vdoualarm, (caddr_t)p->p_pid, uap->value);
E 2
		break;

	case VTR_STAMP:
D 2
		trace(TR_STAMP, uap->value, u.u_procp->p_pid);
E 2
I 2
		trace(TR_STAMP, uap->value, p->p_pid);
E 2
		break;
	}
I 2
D 3
	RETURN (0);
E 3
I 3
	return (0);
E 3
E 2
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
I 7

D 10
#include "../include/cpu.h"
E 10
I 10
#include <machine/cpu.h>
E 10

/* XXX should be in an include file somewhere */
#define CC_PURGE	1
#define CC_FLUSH	2
#define CC_IPURGE	4
#define CC_EXTPURGE	0x80000000
/* XXX end should be */

I 8
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
E 8
/*ARGSUSED1*/
cachectl(req, addr, len)
	int req;
	caddr_t	addr;
	int len;
{
	int error = 0;

I 8
#if defined(HP380)
	if (mmutype == MMU_68040) {
D 13
		register int inc;
E 13
I 13
		register int inc = 0;
E 13
		int pa = 0, doall = 0;
		caddr_t end;

		if (addr == 0 ||
		    (req & ~CC_EXTPURGE) != CC_PURGE && len > 2*NBPG)
			doall = 1;
#ifdef HPUXCOMPAT
D 11
		if ((curproc->p_flag & SHPUX) && len != 16 && len != NBPG)
E 11
I 11
		if ((curproc->p_md.md_flags & MDP_HPUX) &&
		    len != 16 && len != NBPG)
E 11
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
E 8
	switch (req) {
	case CC_EXTPURGE|CC_PURGE:
	case CC_EXTPURGE|CC_FLUSH:
#if defined(HP370)
		if (ectype == EC_PHYS)
			PCIA();
		/* fall into... */
#endif
	case CC_PURGE:
	case CC_FLUSH:
		DCIU();
		break;
	case CC_EXTPURGE|CC_IPURGE:
#if defined(HP370)
		if (ectype == EC_PHYS)
			PCIA();
		else
#endif
		DCIU();
		/* fall into... */
	case CC_IPURGE:
		ICIA();
		break;
	default:
		error = EINVAL;
		break;
	}
	return(error);
}
E 7
E 1
