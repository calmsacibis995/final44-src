h35943
s 00001/00001/00492
d D 8.7 95/02/14 10:33:32 cgd 29 28
c hack to make it work with new syscall arg conventions.
e
s 00006/00001/00487
d D 8.6 94/01/21 17:17:57 bostic 28 27
c add USL's copyright notice
e
s 00001/00001/00487
d D 8.5 94/01/12 14:41:57 hibler 27 26
c entries_pageable set TRUE for shm_map (see vm_map.c change).
e
s 00002/00001/00486
d D 8.4 93/11/11 18:31:41 torek 26 25
c fix missing return value in shmdt() (gcc -W, come on guys...)
e
s 00001/00001/00486
d D 8.3 93/09/21 08:09:57 bostic 25 24
c changes for 4.4BSD-Lite requested by USL
e
s 00006/00004/00481
d D 8.2 93/09/04 10:35:05 mckusick 24 23
c use symbolic names for access permissions
e
s 00002/00002/00483
d D 8.1 93/06/10 21:58:55 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00481
d D 7.21 93/03/09 10:56:37 hibler 22 21
c additional parameter to vm_mmap
e
s 00012/00011/00472
d D 7.20 92/10/11 10:38:32 bostic 21 20
c make kernel includes standard
e
s 00026/00021/00457
d D 7.19 92/07/10 21:08:51 torek 20 19
c ANSIfy syscall args
e
s 00001/00017/00477
d D 7.18 92/07/09 15:55:02 hibler 19 18
c move HPUXCOMPAT code to hpux_compat.c
e
s 00001/00001/00493
d D 7.17 92/06/04 17:08:10 hibler 18 17
c change include path for HP code reorg
e
s 00003/00002/00491
d D 7.16 92/05/04 15:50:34 mckusick 17 16
c lint
e
s 00002/00003/00491
d D 7.15 91/05/13 09:36:50 hibler 16 15
c pass address of vm_map not structure itself, got rid of unused var
e
s 00001/00001/00493
d D 7.14 91/05/10 18:03:52 hibler 15 14
c correct argument to vm_deallocate
e
s 00004/00006/00490
d D 7.13 91/04/20 16:15:34 karels 14 13
c rm user.h, fix vm includes
e
s 00016/00016/00480
d D 7.12 91/03/17 15:41:21 karels 13 12
c more-or-less working with new proc & user structs
e
s 00001/00001/00495
d D 7.11 90/12/16 22:03:21 mckusick 12 11
c new pathname for hpux
e
s 00124/00076/00372
d D 7.10 90/12/05 17:13:07 mckusick 11 10
c update for new VM
e
s 00003/00003/00445
d D 7.9 90/06/28 17:11:22 karels 10 9
c RETURN => return, remove syscontext.h
e
s 00003/00001/00445
d D 7.8 90/06/24 14:08:25 karels 9 8
c careful of out-of-range parameters
e
s 00010/00009/00436
d D 7.7 90/06/22 09:01:58 hibler 8 7
c add some missing returns, correct args to ipcaccess, general cleanup
e
s 00004/00003/00441
d D 7.6 90/06/07 16:02:14 mckusick 7 6
c proc pointer is now passed in to shmexit function
e
s 00131/00143/00313
d D 7.5 90/06/07 15:36:57 mckusick 6 4
c convert to new syscall convention
e
s 00001/00001/00455
d R 7.5 90/06/07 15:28:48 mckusick 5 4
c need to return mmexit error correctly
e
s 00026/00014/00430
d D 7.4 90/06/05 22:02:14 mckusick 4 3
c update to new system call convention; expunge more u.u_error
e
s 00002/00002/00442
d D 7.3 90/05/25 15:10:50 mckusick 3 2
c update from Mike Hibler at Utah
e
s 00001/00001/00443
d D 7.2 90/05/15 22:05:19 bostic 2 1
c rename size_t to segsz_t for ANSI C
e
s 00444/00000/00000
d D 7.1 90/05/08 22:54:13 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 23
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
I 28
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 28
E 23
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
D 28
 * Science Department. Originally from University of Wisconsin.
E 28
I 28
 * Science Department.  Originally from the University of Wisconsin.
E 28
 *
D 25
 * %sccs.include.redist.c%
E 25
I 25
 * %sccs.include.proprietary.c%
E 25
 *
D 19
 * from: Utah $Hdr: uipc_shm.c 1.9 89/08/14$
E 19
I 19
 * from: Utah $Hdr: uipc_shm.c 1.11 92/04/23$
E 19
 *
 *	%W% (Berkeley) %G%
 */

/*
 * System V shared memory routines.
I 9
 * TEMPORARY, until mmap is in place;
 * needed now for HP-UX compatibility and X server (yech!).
E 9
 */

#ifdef SYSVSHM

D 11
#include "machine/pte.h"

E 11
D 21
#include "param.h"
#include "systm.h"
D 6
#include "user.h"
E 6
I 6
D 10
#include "syscontext.h"
E 10
I 10
D 14
#include "user.h"
E 14
E 10
E 6
#include "kernel.h"
#include "proc.h"
D 11
#include "vm.h"
E 11
#include "shm.h"
D 11
#include "mapmem.h"
E 11
#include "malloc.h"
I 11
#include "mman.h"
D 14
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_kern.h"
#include "../vm/vm_inherit.h"
#include "../vm/vm_pager.h"
E 14
I 14
#include "vm/vm.h"
#include "vm/vm_kern.h"
#include "vm/vm_inherit.h"
#include "vm/vm_pager.h"
E 21
I 21
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/shm.h>
#include <sys/malloc.h>
#include <sys/mman.h>
I 24
#include <sys/stat.h>
E 24

#include <vm/vm.h>
#include <vm/vm_kern.h>
#include <vm/vm_inherit.h>
#include <vm/vm_pager.h>
E 21
E 14
E 11

D 19
#ifdef HPUXCOMPAT
D 12
#include "../hpux/hpux.h"
E 12
I 12
D 18
#include "hp300/hpux/hpux.h"
E 18
I 18
#include "hp/hpux/hpux.h"
E 18
E 12
#endif

E 19
int	shmat(), shmctl(), shmdt(), shmget();
int	(*shmcalls[])() = { shmat, shmctl, shmdt, shmget };
int	shmtot = 0;

D 11
int	shmfork(), shmexit();
struct	mapmemops shmops = { shmfork, (int (*)())0, shmexit, shmexit };
E 11
I 11
/*
 * Per process internal structure for managing segments.
 * Each process using shm will have an array of ``shmseg'' of these.
 */
struct	shmdesc {
	vm_offset_t	shmd_uva;
	int		shmd_id;
};
E 11

I 11
/*
 * Per segment internal structure (shm_handle).
 */
struct	shmhandle {
	vm_offset_t	shmh_kva;
	caddr_t		shmh_id;
};

vm_map_t shm_map;	/* address space for shared memory segments */

E 11
shminit()
{
	register int i;
I 11
	vm_offset_t whocares1, whocares2;
E 11

I 11
	shm_map = kmem_suballoc(kernel_map, &whocares1, &whocares2,
D 27
				shminfo.shmall * NBPG, FALSE);
E 27
I 27
				shminfo.shmall * NBPG, TRUE);
E 27
E 11
	if (shminfo.shmmni > SHMMMNI)
		shminfo.shmmni = SHMMMNI;
	for (i = 0; i < shminfo.shmmni; i++) {
		shmsegs[i].shm_perm.mode = 0;
		shmsegs[i].shm_perm.seq = 0;
	}
}

D 6
/* entry point for all SHM calls */
shmsys()
{
	struct a {
E 6
I 6
/*
 * Entry point for all SHM calls
 */
I 20
struct shmsys_args {
	u_int which;
};
E 20
D 29
shmsys(p, uap, retval)
E 29
I 29
compat_43_shmsys(p, uap, retval)
E 29
	struct proc *p;
D 20
	struct args {
E 6
D 9
		int which;
E 9
I 9
		u_int which;
E 9
D 6
	} *uap = (struct a *)u.u_ap;
E 6
I 6
	} *uap;
E 20
I 20
	struct shmsys_args *uap;
E 20
	int *retval;
{
E 6

D 6
	if (uap->which >= sizeof(shmcalls)/sizeof(shmcalls[0])) {
		u.u_error = EINVAL;
		return;
	}
	(*shmcalls[uap->which])(u.u_ap+1);
E 6
I 6
	if (uap->which >= sizeof(shmcalls)/sizeof(shmcalls[0]))
D 10
		RETURN (EINVAL);
	RETURN ((*shmcalls[uap->which])(p, &uap[1], retval));
E 10
I 10
		return (EINVAL);
	return ((*shmcalls[uap->which])(p, &uap[1], retval));
E 10
E 6
}

D 6
/* get a shared memory segment */
shmget(ap)
	int *ap;
{
	register struct a {
E 6
I 6
/*
 * Get a shared memory segment
 */
I 20
struct shmget_args {
	key_t key;
	int size;
	int shmflg;
};
E 20
shmget(p, uap, retval)
	struct proc *p;
D 20
	register struct args {
E 6
		key_t key;
		int size;
		int shmflg;
D 6
	} *uap = (struct a *)ap;
I 4
	struct proc *p = u.u_procp;
E 6
I 6
	} *uap;
E 20
I 20
	register struct shmget_args *uap;
E 20
	int *retval;
{
E 6
E 4
	register struct shmid_ds *shp;
I 6
D 13
	register struct ucred *cred = u.u_cred;
E 13
I 13
	register struct ucred *cred = p->p_ucred;
E 13
E 6
	register int i;
D 6
	int rval = 0, size;
E 6
I 6
	int error, size, rval = 0;
E 6
D 11
	caddr_t kva;
E 11
I 11
	register struct shmhandle *shmh;
E 11

	/* look up the specified shm_id */
	if (uap->key != IPC_PRIVATE) {
		for (i = 0; i < shminfo.shmmni; i++)
			if ((shmsegs[i].shm_perm.mode & SHM_ALLOC) &&
			    shmsegs[i].shm_perm.key == uap->key) {
				rval = i;
				break;
			}
	} else
		i = shminfo.shmmni;

	/* create a new shared segment if necessary */
	if (i == shminfo.shmmni) {
D 6
		if ((uap->shmflg & IPC_CREAT) == 0) {
			u.u_error = ENOENT;
			return;
		}
		if (uap->size < shminfo.shmmin || uap->size > shminfo.shmmax) {
			u.u_error = EINVAL;
			return;
		}
E 6
I 6
		if ((uap->shmflg & IPC_CREAT) == 0)
			return (ENOENT);
		if (uap->size < shminfo.shmmin || uap->size > shminfo.shmmax)
			return (EINVAL);
E 6
		for (i = 0; i < shminfo.shmmni; i++)
			if ((shmsegs[i].shm_perm.mode & SHM_ALLOC) == 0) {
				rval = i;
				break;
			}
D 6
		if (i == shminfo.shmmni) {
			u.u_error = ENOSPC;
			return;
		}
E 6
I 6
		if (i == shminfo.shmmni)
			return (ENOSPC);
E 6
		size = clrnd(btoc(uap->size));
D 6
		if (shmtot + size > shminfo.shmall) {
			u.u_error = ENOMEM;
			return;
		}
E 6
I 6
		if (shmtot + size > shminfo.shmall)
			return (ENOMEM);
E 6
		shp = &shmsegs[rval];
		/*
		 * We need to do a couple of things to ensure consistency
		 * in case we sleep in malloc().  We mark segment as
		 * allocated so that other shmgets() will not allocate it.
		 * We mark it as "destroyed" to insure that shmvalid() is
		 * false making most operations fail (XXX).  We set the key,
		 * so that other shmget()s will fail.
		 */
		shp->shm_perm.mode = SHM_ALLOC | SHM_DEST;
		shp->shm_perm.key = uap->key;
D 11
		kva = (caddr_t) malloc((u_long)ctob(size), M_SHM, M_WAITOK);
		if (kva == NULL) {
E 11
I 11
		shmh = (struct shmhandle *)
			malloc(sizeof(struct shmhandle), M_SHM, M_WAITOK);
		shmh->shmh_kva = 0;
		shmh->shmh_id = (caddr_t)(0xc0000000|rval);	/* XXX */
		error = vm_mmap(shm_map, &shmh->shmh_kva, ctob(size),
D 22
				VM_PROT_ALL, MAP_ANON, shmh->shmh_id, 0);
E 22
I 22
				VM_PROT_ALL, VM_PROT_ALL,
				MAP_ANON, shmh->shmh_id, 0);
E 22
		if (error) {
			free((caddr_t)shmh, M_SHM);
E 11
			shp->shm_perm.mode = 0;
D 6
			u.u_error = ENOMEM;
			return;
E 6
I 6
D 11
			return (ENOMEM);
E 11
I 11
			return(ENOMEM);
E 11
E 6
		}
D 11
		if (!claligned(kva))
			panic("shmget: non-aligned memory");
		bzero(kva, (u_int)ctob(size));
E 11
I 11
		shp->shm_handle = (void *) shmh;
E 11
		shmtot += size;
D 6
		shp->shm_perm.cuid = shp->shm_perm.uid = u.u_uid;
		shp->shm_perm.cgid = shp->shm_perm.gid = u.u_gid;
E 6
I 6
		shp->shm_perm.cuid = shp->shm_perm.uid = cred->cr_uid;
		shp->shm_perm.cgid = shp->shm_perm.gid = cred->cr_gid;
E 6
D 24
		shp->shm_perm.mode = SHM_ALLOC | (uap->shmflg&0777);
E 24
I 24
		shp->shm_perm.mode = SHM_ALLOC | (uap->shmflg & ACCESSPERMS);
E 24
D 11
		shp->shm_handle = (void *) kvtopte(kva);
E 11
		shp->shm_segsz = uap->size;
D 4
		shp->shm_cpid = u.u_procp->p_pid;
E 4
I 4
		shp->shm_cpid = p->p_pid;
E 4
		shp->shm_lpid = shp->shm_nattch = 0;
		shp->shm_atime = shp->shm_dtime = 0;
		shp->shm_ctime = time.tv_sec;
	} else {
		shp = &shmsegs[rval];
		/* XXX: probably not the right thing to do */
D 6
		if (shp->shm_perm.mode & SHM_DEST) {
			u.u_error = EBUSY;
			return;
		}
		if (!ipcaccess(&shp->shm_perm, uap->shmflg&0777))
			return;
		if (uap->size && uap->size > shp->shm_segsz) {
			u.u_error = EINVAL;
			return;
		}
		if ((uap->shmflg&IPC_CREAT) && (uap->shmflg&IPC_EXCL)) {
			u.u_error = EEXIST;
			return;
		}
E 6
I 6
		if (shp->shm_perm.mode & SHM_DEST)
			return (EBUSY);
D 8
		if (error = ipcaccess(cred, &shp->shm_perm, uap->shmflg&0777))
E 8
I 8
D 24
		if (error = ipcaccess(&shp->shm_perm, uap->shmflg&0777, cred))
E 24
I 24
		if (error = ipcaccess(&shp->shm_perm, uap->shmflg & ACCESSPERMS,
			    cred))
E 24
E 8
			return (error);
		if (uap->size && uap->size > shp->shm_segsz)
			return (EINVAL);
		if ((uap->shmflg&IPC_CREAT) && (uap->shmflg&IPC_EXCL))
			return (EEXIST);
E 6
	}
D 6
	u.u_r.r_val1 = shp->shm_perm.seq * SHMMMNI + rval;
E 6
I 6
	*retval = shp->shm_perm.seq * SHMMMNI + rval;
I 8
	return (0);
E 8
E 6
}

D 6
/* shared memory control */
shmctl(ap)
	int *ap;
{
	register struct a {
E 6
I 6
/*
 * Shared memory control
 */
I 20
struct shmctl_args {
	int shmid;
	int cmd;
	caddr_t buf;
};
E 20
/* ARGSUSED */
shmctl(p, uap, retval)
	struct proc *p;
D 20
	register struct args {
E 6
		int shmid;
		int cmd;
		caddr_t buf;
D 6
	} *uap = (struct a *)ap;
I 4
	struct proc *p = u.u_procp;
E 6
I 6
	} *uap;
E 20
I 20
	register struct shmctl_args *uap;
E 20
	int *retval;
{
E 6
E 4
	register struct shmid_ds *shp;
I 6
D 13
	register struct ucred *cred = u.u_cred;
E 13
I 13
	register struct ucred *cred = p->p_ucred;
E 13
E 6
	struct shmid_ds sbuf;
I 6
	int error;
E 6

D 6
	if (!shmvalid(uap->shmid))
		return;
E 6
I 6
	if (error = shmvalid(uap->shmid))
		return (error);
E 6
	shp = &shmsegs[uap->shmid % SHMMMNI];
	switch (uap->cmd) {
	case IPC_STAT:
D 6
		if (ipcaccess(&shp->shm_perm, IPC_R))
			u.u_error =
				copyout((caddr_t)shp, uap->buf, sizeof(*shp));
		break;
E 6
I 6
D 8
		if (error = ipcaccess(cred, &shp->shm_perm, IPC_R))
E 8
I 8
		if (error = ipcaccess(&shp->shm_perm, IPC_R, cred))
E 8
			return (error);
		return (copyout((caddr_t)shp, uap->buf, sizeof(*shp)));
E 6

	case IPC_SET:
D 6
		if (u.u_uid && u.u_uid != shp->shm_perm.uid &&
		    u.u_uid != shp->shm_perm.cuid) {
			u.u_error = EPERM;
			break;
		}
		u.u_error = copyin(uap->buf, (caddr_t)&sbuf, sizeof sbuf);
		if (!u.u_error) {
			shp->shm_perm.uid = sbuf.shm_perm.uid;
			shp->shm_perm.gid = sbuf.shm_perm.gid;
			shp->shm_perm.mode = (shp->shm_perm.mode & ~0777)
				| (sbuf.shm_perm.mode & 0777);
			shp->shm_ctime = time.tv_sec;
		}
E 6
I 6
		if (cred->cr_uid && cred->cr_uid != shp->shm_perm.uid &&
		    cred->cr_uid != shp->shm_perm.cuid)
			return (EPERM);
		if (error = copyin(uap->buf, (caddr_t)&sbuf, sizeof sbuf))
			return (error);
		shp->shm_perm.uid = sbuf.shm_perm.uid;
		shp->shm_perm.gid = sbuf.shm_perm.gid;
D 24
		shp->shm_perm.mode = (shp->shm_perm.mode & ~0777)
			| (sbuf.shm_perm.mode & 0777);
E 24
I 24
		shp->shm_perm.mode = (shp->shm_perm.mode & ~ACCESSPERMS)
			| (sbuf.shm_perm.mode & ACCESSPERMS);
E 24
		shp->shm_ctime = time.tv_sec;
E 6
		break;

	case IPC_RMID:
D 6
		if (u.u_uid && u.u_uid != shp->shm_perm.uid &&
		    u.u_uid != shp->shm_perm.cuid) {
			u.u_error = EPERM;
			break;
		}
E 6
I 6
		if (cred->cr_uid && cred->cr_uid != shp->shm_perm.uid &&
		    cred->cr_uid != shp->shm_perm.cuid)
			return (EPERM);
E 6
		/* set ctime? */
		shp->shm_perm.key = IPC_PRIVATE;
		shp->shm_perm.mode |= SHM_DEST;
		if (shp->shm_nattch <= 0)
			shmfree(shp);
		break;
D 19

#ifdef HPUXCOMPAT
	case SHM_LOCK:
	case SHM_UNLOCK:
		/* don't really do anything, but make them think we did */
D 4
		if ((u.u_procp->p_flag & SHPUX) == 0)
E 4
I 4
		if ((p->p_flag & SHPUX) == 0)
E 4
D 6
			u.u_error = EINVAL;
		else if (u.u_uid && u.u_uid != shp->shm_perm.uid &&
			 u.u_uid != shp->shm_perm.cuid)
			u.u_error = EPERM;
E 6
I 6
			return (EINVAL);
		if (cred->cr_uid && cred->cr_uid != shp->shm_perm.uid &&
		    cred->cr_uid != shp->shm_perm.cuid)
			return (EPERM);
E 6
		break;
#endif
E 19

	default:
D 6
		u.u_error = EINVAL;
		break;
E 6
I 6
		return (EINVAL);
E 6
	}
I 6
	return (0);
E 6
}

D 6
shmat(ap)
	int *ap;
{
	struct a {
E 6
I 6
/*
 * Attach to shared memory segment.
 */
I 20
struct shmat_args {
	int	shmid;
	caddr_t	shmaddr;
	int	shmflg;
};
E 20
shmat(p, uap, retval)
	struct proc *p;
D 20
	register struct args {
E 6
		int	shmid;
		caddr_t	shmaddr;
		int	shmflg;
D 6
	} *uap = (struct a *)ap;
I 4
	struct proc *p = u.u_procp;
E 6
I 6
	} *uap;
E 20
I 20
	register struct shmat_args *uap;
E 20
	int *retval;
{
E 6
E 4
	register struct shmid_ds *shp;
	register int size;
D 11
	struct mapmem *mp;
E 11
	caddr_t uva;
D 4
	int prot, shmmapin();
E 4
I 4
D 6
	int error, prot, shmmapin();
E 6
I 6
D 8
	int error, error1, prot, shmmapin();
E 8
I 8
D 11
	int error, prot, shmmapin();
E 11
I 11
	int error;
	int flags;
	vm_prot_t prot;
	struct shmdesc *shmd;
E 11
E 8
E 6
E 4

I 11
	/*
	 * Allocate descriptors now (before validity check)
	 * in case malloc() blocks.
	 */
D 13
	shmd = (struct shmdesc *)p->p_shm;
E 13
I 13
	shmd = (struct shmdesc *)p->p_vmspace->vm_shm;
E 13
	size = shminfo.shmseg * sizeof(struct shmdesc);
	if (shmd == NULL) {
		shmd = (struct shmdesc *)malloc(size, M_SHM, M_WAITOK);
		bzero((caddr_t)shmd, size);
D 13
		p->p_shm = (caddr_t)shmd;
E 13
I 13
		p->p_vmspace->vm_shm = (caddr_t)shmd;
E 13
	}
E 11
D 6
	if (!shmvalid(uap->shmid))
		return;
E 6
I 6
	if (error = shmvalid(uap->shmid))
		return (error);
E 6
	shp = &shmsegs[uap->shmid % SHMMMNI];
	if (shp->shm_handle == NULL)
D 3
		panic("shmat NULL ptbl");
E 3
I 3
		panic("shmat NULL handle");
E 3
D 6
	if (!ipcaccess(&shp->shm_perm,
E 6
I 6
D 8
	if (error = ipcaccess(u.u_cred, &shp->shm_perm,
E 6
		      (uap->shmflg&SHM_RDONLY) ? IPC_R : IPC_R|IPC_W))
E 8
I 8
	if (error = ipcaccess(&shp->shm_perm,
D 13
			(uap->shmflg&SHM_RDONLY) ? IPC_R : IPC_R|IPC_W, u.u_cred))
E 13
I 13
	    (uap->shmflg&SHM_RDONLY) ? IPC_R : IPC_R|IPC_W, p->p_ucred))
E 13
E 8
D 6
		return;
E 6
I 6
		return (error);
E 6
	uva = uap->shmaddr;
	if (uva && ((int)uva & (SHMLBA-1))) {
		if (uap->shmflg & SHM_RND)
			uva = (caddr_t) ((int)uva & ~(SHMLBA-1));
D 6
		else {
			u.u_error = EINVAL;
			return;
		}
E 6
I 6
		else
			return (EINVAL);
E 6
	}
	/*
	 * Make sure user doesn't use more than their fair share
	 */
D 11
	size = 0;
	for (mp = u.u_mmap; mp; mp = mp->mm_next)
		if (mp->mm_ops == &shmops)
			size++;
E 11
I 11
	for (size = 0; size < shminfo.shmseg; size++) {
		if (shmd->shmd_uva == 0)
			break;
		shmd++;
	}
E 11
D 6
	if (size >= shminfo.shmseg) {
		u.u_error = EMFILE;
		return;
	}
E 6
I 6
	if (size >= shminfo.shmseg)
		return (EMFILE);
E 6
D 11
	/*
	 * Allocate a mapped memory region descriptor and
	 * attempt to expand the user page table to allow for region
	 */
	prot = (uap->shmflg & SHM_RDONLY) ? MM_RO : MM_RW;
#if defined(hp300)
	prot |= MM_CI;
#endif
E 11
	size = ctob(clrnd(btoc(shp->shm_segsz)));
D 2
	mp = mmalloc(uap->shmid, &uva, (size_t)size, prot, &shmops);
E 2
I 2
D 4
	mp = mmalloc(uap->shmid, &uva, (segsz_t)size, prot, &shmops);
E 2
	if (mp == MMNIL)
E 4
I 4
D 11
	error = mmalloc(p, uap->shmid, &uva, (segsz_t)size, prot, &shmops, &mp);
E 11
I 11
	prot = VM_PROT_READ;
	if ((uap->shmflg & SHM_RDONLY) == 0)
		prot |= VM_PROT_WRITE;
	flags = MAP_ANON|MAP_SHARED;
	if (uva)
		flags |= MAP_FIXED;
	else
		uva = (caddr_t)0x1000000;	/* XXX */
D 13
	error = vm_mmap(p->p_map, &uva, (vm_size_t)size, prot, flags,
			((struct shmhandle *)shp->shm_handle)->shmh_id, 0);
E 13
I 13
D 16
	error = vm_mmap(p->p_vmspace->vm_map, &uva, (vm_size_t)size, prot,
E 16
I 16
D 17
	error = vm_mmap(&p->p_vmspace->vm_map, &uva, (vm_size_t)size, prot,
E 16
	    flags, ((struct shmhandle *)shp->shm_handle)->shmh_id, 0);
E 17
I 17
	error = vm_mmap(&p->p_vmspace->vm_map, (vm_offset_t *)&uva,
D 22
	    (vm_size_t)size, prot, flags,
	    ((struct shmhandle *)shp->shm_handle)->shmh_id, 0);
E 22
I 22
			(vm_size_t)size, prot, VM_PROT_ALL, flags,
			((struct shmhandle *)shp->shm_handle)->shmh_id, 0);
E 22
E 17
E 13
E 11
D 6
	if (error) {
		u.u_error = error;
E 4
		return;
E 6
I 6
	if (error)
D 11
		return (error);
	if (error = mmmapin(p, mp, shmmapin)) {
D 8
		if (error1 = mmfree(p, mp))
			return (error1);
E 8
I 8
		(void) mmfree(p, mp);
E 8
		return (error);
E 6
D 4
	if (!mmmapin(mp, shmmapin)) {
		mmfree(mp);
E 4
I 4
	}
E 11
I 11
		return(error);
	shmd->shmd_uva = (vm_offset_t)uva;
	shmd->shmd_id = uap->shmid;
E 11
D 6
	if (u.u_error = mmmapin(p, mp, shmmapin)) {
		if (error = mmfree(p, mp))
			u.u_error = error;
E 4
		return;
	}
E 6
	/*
	 * Fill in the remaining fields
	 */
D 4
	shp->shm_lpid = u.u_procp->p_pid;
E 4
I 4
	shp->shm_lpid = p->p_pid;
E 4
	shp->shm_atime = time.tv_sec;
	shp->shm_nattch++;
D 6
	u.u_r.r_val1 = (int) uva;
E 6
I 6
	*retval = (int) uva;
I 8
	return (0);
E 8
E 6
}

D 6
shmdt(ap)
	int *ap;
{
	register struct a {
E 6
I 6
/*
 * Detach from shared memory segment.
 */
I 20
struct shmdt_args {
	caddr_t	shmaddr;
};
E 20
/* ARGSUSED */
shmdt(p, uap, retval)
	struct proc *p;
D 20
	struct args {
E 6
		caddr_t	shmaddr;
D 6
	} *uap = (struct a *)ap;
I 4
	struct proc *p = u.u_procp;
E 6
I 6
	} *uap;
E 20
I 20
	struct shmdt_args *uap;
E 20
	int *retval;
{
E 6
E 4
D 11
	register struct mapmem *mp;
E 11
I 11
	register struct shmdesc *shmd;
	register int i;
E 11

D 11
	for (mp = u.u_mmap; mp; mp = mp->mm_next)
		if (mp->mm_ops == &shmops && mp->mm_uva == uap->shmaddr)
E 11
I 11
D 13
	shmd = (struct shmdesc *)p->p_shm;
E 13
I 13
	shmd = (struct shmdesc *)p->p_vmspace->vm_shm;
E 13
	for (i = 0; i < shminfo.shmseg; i++, shmd++)
		if (shmd->shmd_uva &&
		    shmd->shmd_uva == (vm_offset_t)uap->shmaddr)
E 11
			break;
D 6
	if (mp == MMNIL) {
		u.u_error = EINVAL;
		return;
	}
E 6
I 6
D 11
	if (mp == MMNIL)
		return (EINVAL);
E 6
D 4
	shmsegs[mp->mm_id % SHMMMNI].shm_lpid = u.u_procp->p_pid;
	shmufree(mp);
E 4
I 4
	shmsegs[mp->mm_id % SHMMMNI].shm_lpid = p->p_pid;
D 6
	u.u_error = shmufree(p, mp);
E 6
I 6
	return (shmufree(p, mp));
E 11
I 11
	if (i == shminfo.shmseg)
D 26
		return(EINVAL);
E 26
I 26
		return (EINVAL);
E 26
	shmufree(p, shmd);
	shmsegs[shmd->shmd_id % SHMMMNI].shm_lpid = p->p_pid;
I 26
	return (0);
E 26
E 11
E 6
E 4
}

D 11
shmmapin(mp, off)
	struct mapmem *mp;
E 11
I 11
D 13
shmfork(rip, rpp, isvfork)
	struct proc *rip, *rpp;
E 13
I 13
shmfork(p1, p2, isvfork)
	struct proc *p1, *p2;
E 13
	int isvfork;
E 11
{
D 11
	register struct shmid_ds *shp;
E 11
I 11
	register struct shmdesc *shmd;
	register int size;
E 11

D 11
	shp = &shmsegs[mp->mm_id % SHMMMNI];
	if (off >= ctob(clrnd(btoc(shp->shm_segsz))))
		return(-1);
	return(((struct pte *)shp->shm_handle)[btop(off)].pg_pfnum);
E 11
I 11
	/*
	 * Copy parents descriptive information
	 */
	size = shminfo.shmseg * sizeof(struct shmdesc);
	shmd = (struct shmdesc *)malloc(size, M_SHM, M_WAITOK);
D 13
	bcopy((caddr_t)rip->p_shm, (caddr_t)shmd, size);
	rpp->p_shm = (caddr_t)shmd;
E 13
I 13
	bcopy((caddr_t)p1->p_vmspace->vm_shm, (caddr_t)shmd, size);
	p2->p_vmspace->vm_shm = (caddr_t)shmd;
E 13
	/*
	 * Increment reference counts
	 */
	for (size = 0; size < shminfo.shmseg; size++, shmd++)
		if (shmd->shmd_uva)
			shmsegs[shmd->shmd_id % SHMMMNI].shm_nattch++;
E 11
}

D 11
/*
 * Increment attach count on fork
 */
I 7
/* ARGSUSED */
E 7
shmfork(mp, ischild)
	register struct mapmem *mp;
E 11
I 11
shmexit(p)
	struct proc *p;
E 11
{
D 11
	if (!ischild)
		shmsegs[mp->mm_id % SHMMMNI].shm_nattch++;
}
E 11
I 11
	register struct shmdesc *shmd;
	register int i;
E 11

D 11
/*
 * Detach from shared memory segment on exit (or exec)
 */
D 7
shmexit(mp)
	register struct mapmem *mp;
E 7
I 7
D 8
shmexit(p, mp)
	struct proc *p;
E 8
I 8
shmexit(mp)
E 8
	struct mapmem *mp;
E 7
{
I 8
	struct proc *p = u.u_procp;		/* XXX */
E 8
D 4
	shmufree(mp);
E 4
I 4
D 7
	struct proc *p = u.u_procp;		/* XXX */
E 7

D 6
	u.u_error = shmufree(p, mp);
E 6
I 6
	return (shmufree(p, mp));
E 11
I 11
D 13
	shmd = (struct shmdesc *)p->p_shm;
E 13
I 13
	shmd = (struct shmdesc *)p->p_vmspace->vm_shm;
E 13
	for (i = 0; i < shminfo.shmseg; i++, shmd++)
		if (shmd->shmd_uva)
			shmufree(p, shmd);
D 13
	free((caddr_t)p->p_shm, M_SHM);
	p->p_shm = NULL;
E 13
I 13
	free((caddr_t)p->p_vmspace->vm_shm, M_SHM);
	p->p_vmspace->vm_shm = NULL;
E 13
E 11
E 6
E 4
}

shmvalid(id)
	register int id;
{
	register struct shmid_ds *shp;

	if (id < 0 || (id % SHMMMNI) >= shminfo.shmmni)
D 6
		return(0);
E 6
I 6
		return(EINVAL);
E 6
	shp = &shmsegs[id % SHMMMNI];
	if (shp->shm_perm.seq == (id / SHMMMNI) &&
	    (shp->shm_perm.mode & (SHM_ALLOC|SHM_DEST)) == SHM_ALLOC)
D 6
		return(1);
	u.u_error = EINVAL;
	return(0);
E 6
I 6
		return(0);
	return(EINVAL);
E 6
}

/*
 * Free user resources associated with a shared memory segment
 */
D 4
shmufree(mp)
E 4
I 4
D 11
shmufree(p, mp)
E 11
I 11
shmufree(p, shmd)
E 11
	struct proc *p;
E 4
D 11
	struct mapmem *mp;
E 11
I 11
	struct shmdesc *shmd;
E 11
{
	register struct shmid_ds *shp;
I 4
D 11
	int error;
E 11
E 4

D 11
	shp = &shmsegs[mp->mm_id % SHMMMNI];
D 4
	mmmapout(mp);
	mmfree(mp);
E 4
I 4
	mmmapout(p, mp);
	error = mmfree(p, mp);
E 11
I 11
	shp = &shmsegs[shmd->shmd_id % SHMMMNI];
D 13
	(void) vm_deallocate(p->p_map, shmd->shmd_uva,
E 13
I 13
D 16
	(void) vm_deallocate(p->p_vmspace->vm_map, shmd->shmd_uva,
E 16
I 16
	(void) vm_deallocate(&p->p_vmspace->vm_map, shmd->shmd_uva,
E 16
E 13
			     ctob(clrnd(btoc(shp->shm_segsz))));
	shmd->shmd_id = 0;
	shmd->shmd_uva = 0;
E 11
E 4
	shp->shm_dtime = time.tv_sec;
	if (--shp->shm_nattch <= 0 && (shp->shm_perm.mode & SHM_DEST))
		shmfree(shp);
I 4
D 11
	return (error);
E 11
E 4
}

/*
 * Deallocate resources associated with a shared memory segment
 */
shmfree(shp)
	register struct shmid_ds *shp;
{
D 16
	caddr_t kva;
E 16

	if (shp->shm_handle == NULL)
		panic("shmfree");
D 11
	kva = (caddr_t) ptetokv(shp->shm_handle);
	free(kva, M_SHM);
E 11
I 11
	/*
	 * Lose our lingering object reference by deallocating space
	 * in kernel.  Pager will also be deallocated as a side-effect.
	 */
	vm_deallocate(shm_map,
		      ((struct shmhandle *)shp->shm_handle)->shmh_kva,
D 15
		      clrnd(btoc(shp->shm_segsz)));
E 15
I 15
		      ctob(clrnd(btoc(shp->shm_segsz))));
E 15
	free((caddr_t)shp->shm_handle, M_SHM);
E 11
	shp->shm_handle = NULL;
	shmtot -= clrnd(btoc(shp->shm_segsz));
	shp->shm_perm.mode = 0;
	/*
	 * Increment the sequence number to ensure that outstanding
	 * shmids for this segment will be invalid in the event that
	 * the segment is reallocated.  Note that shmids must be
	 * positive as decreed by SVID.
	 */
	shp->shm_perm.seq++;
	if ((int)(shp->shm_perm.seq * SHMMMNI) < 0)
		shp->shm_perm.seq = 0;
}

/*
 * XXX This routine would be common to all sysV style IPC
 *     (if the others were implemented).
 */
D 6
ipcaccess(ipc, mode)
E 6
I 6
ipcaccess(ipc, mode, cred)
E 6
	register struct ipc_perm *ipc;
I 6
	int mode;
	register struct ucred *cred;
E 6
{
	register int m;

D 6
	if (u.u_uid == 0)
E 6
I 6
	if (cred->cr_uid == 0)
E 6
		return(0);
	/*
	 * Access check is based on only one of owner, group, public.
	 * If not owner, then check group.
	 * If not a member of the group, then check public access.
	 */
	mode &= 0700;
	m = ipc->mode;
D 6
	if (u.u_uid != ipc->uid && u.u_uid != ipc->cuid) {
E 6
I 6
	if (cred->cr_uid != ipc->uid && cred->cr_uid != ipc->cuid) {
E 6
		m <<= 3;
D 6
		if (!groupmember(ipc->gid, u.u_cred) &&
		    !groupmember(ipc->cgid, u.u_cred))
E 6
I 6
		if (!groupmember(ipc->gid, cred) &&
		    !groupmember(ipc->cgid, cred))
E 6
			m <<= 3;
	}
	if ((mode&m) == mode)
D 6
		return (1);
	u.u_error = EACCES;
	return (0);
E 6
I 6
		return (0);
	return (EACCES);
E 6
}
D 11

E 11
#endif /* SYSVSHM */
E 1
