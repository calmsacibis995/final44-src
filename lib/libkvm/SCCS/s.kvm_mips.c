h01436
s 00002/00002/00179
d D 8.1 93/06/04 16:53:49 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00079/00014/00102
d D 5.2 93/05/15 11:50:14 ralph 3 2
c updated for new improved pmap.c
e
s 00000/00000/00116
d D 5.1 93/02/15 10:01:12 ralph 2 1
c fix SCCS version number.
e
s 00116/00000/00000
d D 1.1 93/02/04 19:06:03 ralph 1 0
c date and time created 93/02/04 19:06:03 by ralph
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1989, 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software developed by the Computer Systems
 * Engineering group at Lawrence Berkeley Laboratory under DARPA contract
 * BG 91-66 and contributed to Berkeley. Modified for MIPS by Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */
/*
 * MIPS machine dependent routines for kvm.  Hopefully, the forthcoming 
 * vm code will one day obsolete this module.
 */

#include <sys/param.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/stat.h>
#include <unistd.h>
#include <nlist.h>
#include <kvm.h>

#include <vm/vm.h>
#include <vm/vm_param.h>

#include <limits.h>
#include <db.h>

#include "kvm_private.h"

#include <machine/machConst.h>
#include <machine/pte.h>
#include <machine/pmap.h>

I 3
struct vmstate {
	pt_entry_t	*Sysmap;
	u_int		Sysmapsize;
};

E 3
#define KREAD(kd, addr, p)\
	(kvm_read(kd, addr, (char *)(p), sizeof(*(p))) != sizeof(*(p)))

void
_kvm_freevtop(kd)
	kvm_t *kd;
{
I 3
	if (kd->vmst != 0)
		free(kd->vmst);
E 3
}

int
_kvm_initvtop(kd)
	kvm_t *kd;
{
I 3
	struct vmstate *vm;
	struct nlist nlist[3];
E 3

I 3
	vm = (struct vmstate *)_kvm_malloc(kd, sizeof(*vm));
	if (vm == 0)
		return (-1);
	kd->vmst = vm;

	nlist[0].n_name = "Sysmap";
	nlist[1].n_name = "Sysmapsize";
	nlist[2].n_name = 0;

	if (kvm_nlist(kd, nlist) != 0) {
		_kvm_err(kd, kd->program, "bad namelist");
		return (-1);
	}
	if (KREAD(kd, (u_long)nlist[0].n_value, &vm->Sysmap)) {
		_kvm_err(kd, kd->program, "cannot read Sysmap");
		return (-1);
	}
	if (KREAD(kd, (u_long)nlist[1].n_value, &vm->Sysmapsize)) {
		_kvm_err(kd, kd->program, "cannot read mmutype");
		return (-1);
	}
E 3
	return (0);
}

/*
 * Translate a kernel virtual address to a physical address.
 */
int
_kvm_kvatop(kd, va, pa)
	kvm_t *kd;
	u_long va;
	u_long *pa;
{
I 3
	register struct vmstate *vm;
E 3
	u_long pte, addr, offset;

I 3
	if (ISALIVE(kd)) {
		_kvm_err(kd, 0, "vatop called in live kernel!");
		return((off_t)0);
	}
	vm = kd->vmst;
	offset = va & PGOFSET;
	/*
	 * If we are initializing (kernel segment table pointer not yet set)
	 * then return pa == va to avoid infinite recursion.
	 */
	if (vm->Sysmap == 0) {
		*pa = va;
		return (NBPG - offset);
	}
E 3
	if (va < KERNBASE ||
D 3
	    va >= VM_MIN_KERNEL_ADDRESS + PMAP_HASH_KPAGES * NPTEPG * NBPG)
E 3
I 3
	    va >= VM_MIN_KERNEL_ADDRESS + vm->Sysmapsize * NBPG)
E 3
		goto invalid;
	if (va < VM_MIN_KERNEL_ADDRESS) {
		*pa = MACH_CACHED_TO_PHYS(va);
D 3
		return (NBPG - (va & PGOFSET));
E 3
I 3
		return (NBPG - offset);
E 3
	}
D 3
	addr = PMAP_HASH_KADDR + ((va - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT);
E 3
I 3
	addr = (u_long)(vm->Sysmap + ((va - VM_MIN_KERNEL_ADDRESS) >> PGSHIFT));
E 3
	/*
	 * Can't use KREAD to read kernel segment table entries.
	 * Fortunately it is 1-to-1 mapped so we don't have to. 
	 */
	if (lseek(kd->pmfd, (off_t)addr, 0) < 0 ||
	    read(kd->pmfd, (char *)&pte, sizeof(pte)) < 0)
		goto invalid;
D 3
	offset = va & PGOFSET;
E 3
I 3
	if (!(pte & PG_V))
		goto invalid;
E 3
	*pa = (pte & PG_FRAME) | offset;
	return (NBPG - offset);

invalid:
	_kvm_err(kd, 0, "invalid address (%x)", va);
	return (0);
}

/*
 * Translate a user virtual address to a physical address.
 */
int
_kvm_uvatop(kd, p, va, pa)
	kvm_t *kd;
	const struct proc *p;
	u_long va;
	u_long *pa;
{
D 3
#if 0
E 3
	register struct vmspace *vms = p->p_vmspace;
D 3
	u_long stab_kva, kva;
E 3
I 3
	u_long kva, offset;
E 3

D 3
	kva = (u_long)&vms->vm_pmap.pm_stab;
	if (kvm_read(kd, kva, (char *)&kva, 4) != 4) {
		_kvm_err(kd, 0, "invalid address (%x)", va);
		return (0);
	}
	return (_kvm_vatop(kd, kva, va, pa));
#else
E 3
I 3
	if (va >= KERNBASE)
		goto invalid;

	/* read the address of the first level table */
	kva = (u_long)&vms->vm_pmap.pm_segtab;
	if (kvm_read(kd, kva, (char *)&kva, sizeof(kva)) != sizeof(kva))
		goto invalid;
	if (kva == 0)
		goto invalid;

	/* read the address of the second level table */
	kva += (va >> SEGSHIFT) * sizeof(caddr_t);
	if (kvm_read(kd, kva, (char *)&kva, sizeof(kva)) != sizeof(kva))
		goto invalid;
	if (kva == 0)
		goto invalid;

	/* read the pte from the second level table */
	kva += (va >> PGSHIFT) & (NPTEPG - 1);
	if (kvm_read(kd, kva, (char *)&kva, sizeof(kva)) != sizeof(kva))
		goto invalid;
	if (!(kva & PG_V))
		goto invalid;
	offset = va & PGOFSET;
	*pa = (kva & PG_FRAME) | offset;
	return (NBPG - offset);

invalid:
E 3
	_kvm_err(kd, 0, "invalid address (%x)", va);
	return (0);
D 3
#endif
E 3
}
E 1
