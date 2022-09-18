h53404
s 00002/00002/00109
d D 8.2 95/01/09 17:50:26 cgd 6 5
c KNF, and 64-bit safety.
e
s 00002/00002/00109
d D 8.1 93/06/11 16:38:43 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00103
d D 7.4 92/07/10 19:11:50 torek 4 3
c ANSIfy syscall args
e
s 00008/00005/00101
d D 7.3 92/05/04 17:24:55 bostic 3 2
c new include format; lint
e
s 00021/00018/00085
d D 7.2 91/04/20 10:50:23 karels 2 1
c fix includes; new proc struct; rm *_NULL
e
s 00103/00000/00000
d D 7.1 90/12/05 18:13:42 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: vm_unix.c 1.1 89/11/07$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Traditional sbrk/grow interface to VM
 */
D 3
#include "param.h"
#include "systm.h"
D 2
#include "user.h"
E 2
#include "proc.h"
I 2
#include "resourcevar.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/resourcevar.h>
E 3
E 2

D 2
#include "../vm/vm_param.h"
#include "machine/vmparam.h"
E 2
I 2
D 3
#include "vm.h"
E 3
I 3
#include <vm/vm.h>
E 3
E 2

I 4
struct obreak_args {
	char	*nsiz;
};
E 4
/* ARGSUSED */
I 3
int
E 3
obreak(p, uap, retval)
	struct proc *p;
D 4
	struct args {
		char	*nsiz;
	} *uap;
E 4
I 4
	struct obreak_args *uap;
E 4
	int *retval;
{
I 2
	register struct vmspace *vm = p->p_vmspace;
E 2
	vm_offset_t new, old;
	int rv;
	register int diff;

D 2
	old = (vm_offset_t)u.u_daddr;
E 2
I 2
	old = (vm_offset_t)vm->vm_daddr;
E 2
	new = round_page(uap->nsiz);
D 2
	if ((int)(new - old) > u.u_rlimit[RLIMIT_DATA].rlim_cur)
E 2
I 2
	if ((int)(new - old) > p->p_rlimit[RLIMIT_DATA].rlim_cur)
E 2
		return(ENOMEM);
D 2
	old = round_page(old + ctob(u.u_dsize));
E 2
I 2
	old = round_page(old + ctob(vm->vm_dsize));
E 2
	diff = new - old;
	if (diff > 0) {
D 2
		rv = vm_allocate(p->p_map, &old, diff, FALSE);
E 2
I 2
		rv = vm_allocate(&vm->vm_map, &old, diff, FALSE);
E 2
		if (rv != KERN_SUCCESS) {
			uprintf("sbrk: grow failed, return = %d\n", rv);
			return(ENOMEM);
		}
D 2
		u.u_dsize += btoc(diff);
E 2
I 2
		vm->vm_dsize += btoc(diff);
E 2
	} else if (diff < 0) {
		diff = -diff;
D 2
		rv = vm_deallocate(p->p_map, new, diff);
E 2
I 2
		rv = vm_deallocate(&vm->vm_map, new, diff);
E 2
		if (rv != KERN_SUCCESS) {
			uprintf("sbrk: shrink failed, return = %d\n", rv);
			return(ENOMEM);
		}
D 2
		u.u_dsize -= btoc(diff);
E 2
I 2
		vm->vm_dsize -= btoc(diff);
E 2
	}
	return(0);
}

/*
D 2
 * grow the stack to include the SP
 * true return if successful.
E 2
I 2
 * Enlarge the "stack segment" to include the specified
 * stack pointer for the process.
E 2
 */
I 3
int
E 3
D 2
grow(sp)
E 2
I 2
grow(p, sp)
	struct proc *p;
E 2
D 6
	unsigned sp;
E 6
I 6
	vm_offset_t sp;
E 6
{
I 2
	register struct vmspace *vm = p->p_vmspace;
E 2
	register int si;

	/*
	 * For user defined stacks (from sendsig).
	 */
D 2
	if (sp < (unsigned)u.u_maxsaddr)
E 2
I 2
D 6
	if (sp < (unsigned)vm->vm_maxsaddr)
E 6
I 6
	if (sp < (vm_offset_t)vm->vm_maxsaddr)
E 6
E 2
		return (0);
	/*
	 * For common case of already allocated (from trap).
	 */
D 2
	if (sp >= USRSTACK-ctob(u.u_ssize))
E 2
I 2
	if (sp >= USRSTACK - ctob(vm->vm_ssize))
E 2
		return (1);
	/*
	 * Really need to check vs limit and increment stack size if ok.
	 */
D 2
	si = clrnd(btoc(USRSTACK-sp) - u.u_ssize);
	if (u.u_ssize+si > btoc(u.u_rlimit[RLIMIT_STACK].rlim_cur))
E 2
I 2
	si = clrnd(btoc(USRSTACK-sp) - vm->vm_ssize);
	if (vm->vm_ssize + si > btoc(p->p_rlimit[RLIMIT_STACK].rlim_cur))
E 2
		return (0);
D 2
	u.u_ssize += si;
E 2
I 2
	vm->vm_ssize += si;
E 2
	return (1);
}

I 4
struct ovadvise_args {
	int	anom;
};
E 4
/* ARGSUSED */
I 3
int
E 3
ovadvise(p, uap, retval)
	struct proc *p;
D 4
	struct args {
		int	anom;
	} *uap;
E 4
I 4
	struct ovadvise_args *uap;
E 4
	int *retval;
{

I 2
	return (EINVAL);
E 2
}
E 1
