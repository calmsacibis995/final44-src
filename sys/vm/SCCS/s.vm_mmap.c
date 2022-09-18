h62221
s 00131/00134/00687
d D 8.10 95/02/19 07:46:59 cgd 45 44
c new syscall arg mechanism
e
s 00004/00003/00817
d D 8.9 95/01/09 17:44:56 cgd 44 43
c fix munmapfd's arguments; it takes a struct proc _then_ an int.
e
s 00001/00001/00819
d D 8.8 94/06/19 20:11:21 hibler 43 42
c msync size 0 case didn't work, incorrect check of a return value
c (from cgd)
e
s 00010/00000/00810
d D 8.7 94/05/27 15:28:11 hibler 42 41
c back out change requiring alignment of "pos"
c also don't require that munmap range be completely allocated
e
s 00002/00001/00808
d D 8.6 94/05/26 20:42:00 hibler 41 40
c after carefully constructing the correct value for "pos",
c I didn't use it...duh!  Also, require that pos be page-aligned for !MAP_ANON
e
s 00008/00005/00801
d D 8.5 94/05/19 21:25:14 hibler 40 39
c two mmap fixes: make sure pos is zero for MAP_ANON 
c if MAP_FIXED is not specified, ensure that addr is outside potential heap
e
s 00059/00226/00747
d D 8.4 94/01/12 15:59:30 hibler 39 38
c massive overhaul of msync, get rid of hack support routines.
e
s 00029/00018/00944
d D 8.3 93/11/14 13:36:14 hibler 38 37
c convert mmaps of /dev/zero to anon memory requests
e
s 00001/00001/00961
d D 8.2 93/11/10 10:58:27 torek 37 36
c finish up new device pager: all pagers get offsets
e
s 00002/00002/00960
d D 8.1 93/06/18 16:14:20 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00959
d D 7.32 93/06/18 16:13:38 mckusick 35 33
c lint
e
s 00002/00002/00960
d R 8.1 93/06/14 15:25:26 bostic 34 33
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00015/00947
d D 7.31 93/06/14 15:23:26 bostic 33 31
c make system call names match function call names
e
s 00002/00002/00960
d R 8.1 93/06/11 16:38:01 bostic 32 31
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00960
d D 7.30 93/06/02 19:25:17 mckusick 31 30
c mlock/munlock lengths are size_t's
e
s 00002/00002/00960
d D 7.29 93/06/02 14:19:32 hibler 30 29
c mlock returns EAGAIN for requests exceeding one of the limits
e
s 00072/00000/00890
d D 7.28 93/06/02 11:10:38 hibler 29 28
c add mlock/munlock calls
e
s 00003/00001/00887
d D 7.27 93/04/05 15:21:17 torek 28 27
c need getpagesize for COMPAT_SUNOS too
e
s 00001/00001/00887
d D 7.26 93/04/04 13:16:44 mckusick 27 26
c getpagesize becomes COMPAT
e
s 00029/00029/00859
d D 7.25 93/03/30 15:14:20 mckusick 26 25
c allow write for private mapping even if file desc open only for reading
e
s 00007/00008/00881
d D 7.24 93/03/27 16:53:13 ralph 25 24
c changed type of 'len' from int to size_t to match syscall definition.
c fix debug printf of uap->pos since kernel printf can't do %qx. remove cast to
c vm_offset_t since foff is already a vm_offset_t.
e
s 00029/00038/00860
d D 7.23 93/03/09 11:01:58 hibler 24 23
c pass maxprot parameter to vm_mmap
e
s 00007/00000/00891
d D 7.22 93/02/26 16:50:31 mckusick 23 22
c check for anonymous objects in the cache (4.4BSD-alpha/sys/4)
e
s 00012/00009/00879
d D 7.21 93/02/26 15:58:00 mckusick 22 21
c do not allow SHARED mappings for non-writable file (yval@CS.HUJI.AC.IL)
e
s 00023/00003/00865
d D 7.20 93/02/20 12:50:18 mckusick 21 19
c make complete bounds checks (from donn@bsdi.com)
e
s 00002/00000/00868
d R 7.20 93/02/20 12:39:42 mckusick 20 19
c avoid inappropriate mappings
e
s 00002/00000/00866
d D 7.19 93/02/10 20:49:17 mckusick 19 18
c do not allow mappings above the top user address
e
s 00015/00015/00851
d D 7.18 93/02/03 17:32:29 mckusick 18 17
c getpagesize becomes COMPAT_43
e
s 00002/00001/00864
d D 7.17 92/07/12 16:19:53 pendry 17 16
c new include location for specdev.h
e
s 00000/00001/00865
d D 7.16 92/07/10 23:51:55 torek 16 15
c lint
e
s 00052/00041/00814
d D 7.15 92/07/10 19:11:46 torek 15 14
c ANSIfy syscall args
e
s 00001/00004/00854
d D 7.14 92/07/09 17:01:33 torek 14 13
c get rid of temporary grot
e
s 00004/00002/00854
d D 7.13 92/06/24 17:34:12 mckusick 13 12
c better heuristic
e
s 00077/00043/00779
d D 7.12 92/06/23 17:21:18 mckusick 12 11
c add compatibility mmap call; make MAP_FILE the default (like Sun)
e
s 00009/00001/00813
d D 7.11 92/06/19 22:07:39 mckusick 11 10
c fix for anonymous objects on hash list when they should not be (from Hibler)
e
s 00025/00012/00789
d D 7.10 92/05/04 17:22:52 bostic 10 9
c new include format; lint
e
s 00002/00002/00799
d D 7.9 91/10/21 13:12:00 hibler 9 8
c reflect change to vm_object_page_clean interface
e
s 00004/00004/00797
d D 7.8 91/08/28 17:07:47 mckusick 8 7
c use PAGE_MASK macro
e
s 00009/00007/00792
d D 7.7 91/08/28 15:41:30 mckusick 7 6
c vm_stat is merged into vmmeter structure;
c internal bit field becomes a flag
e
s 00001/00001/00798
d D 7.6 91/07/30 16:36:40 mckusick 6 5
c return pagesize properly
e
s 00023/00014/00776
d D 7.5 91/06/28 15:31:48 hibler 5 4
c (checked in by karels) chose address for mmap if addr is 0;
c round size to pages here; misc. fixes
e
s 00002/00033/00788
d D 7.4 91/05/07 09:33:39 hibler 4 3
c get rid of vm_object_pmap_force_copy, vm_object_pmap_copy
c now works "right" (i.e. ignores the copy_on_write bit)
e
s 00029/00028/00792
d D 7.3 91/04/20 10:49:52 karels 3 2
c fix includes; new proc struct; rm *_NULL; 
c rm OFILE*
e
s 00007/00005/00813
d D 7.2 91/01/10 23:48:07 mckusick 2 1
c add dynamically allocated file descriptors
e
s 00818/00000/00000
d D 7.1 90/12/05 18:13:33 mckusick 1 0
c adopted from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 36
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 9
 * from: Utah $Hdr: vm_mmap.c 1.3 90/01/21$
E 9
I 9
 * from: Utah $Hdr: vm_mmap.c 1.6 91/10/21$
E 9
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Mapped file (mmap) interface to VM
 */

D 10
#include "param.h"
#include "systm.h"
D 3
#include "user.h"
E 3
I 2
#include "filedesc.h"
E 2
#include "proc.h"
#include "vnode.h"
#include "specdev.h"
#include "file.h"
#include "mman.h"
#include "conf.h"
E 10
I 10
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/filedesc.h>
I 29
#include <sys/resourcevar.h>
E 29
#include <sys/proc.h>
#include <sys/vnode.h>
D 17
#include <sys/specdev.h>
E 17
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/conf.h>
I 17

I 45
#include <sys/mount.h>
#include <sys/syscallargs.h>

E 45
#include <miscfs/specfs/specdev.h>
E 17
E 10

D 3
#include "../vm/vm_param.h"
#include "../vm/vm_map.h"
#include "../vm/vm_pager.h"
#include "../vm/vm_prot.h"
E 3
I 3
D 10
#include "vm.h"
#include "vm_pager.h"
#include "vm_prot.h"
E 10
I 10
#include <vm/vm.h>
#include <vm/vm_pager.h>
#include <vm/vm_prot.h>
E 10
D 7
#include "vm_statistics.h"
E 7
E 3

#ifdef DEBUG
int mmapdebug = 0;
#define MDB_FOLLOW	0x01
#define MDB_SYNC	0x02
#define MDB_MAPIT	0x04
#endif

I 15
D 18
struct getpagesize_args {
	int	dummy;
};
E 15
/* ARGSUSED */
I 10
int
E 10
getpagesize(p, uap, retval)
	struct proc *p;
D 3
	struct args *uap;
E 3
I 3
D 15
	void *uap;
E 15
I 15
	struct getpagesize_args *uap;
E 15
E 3
	int *retval;
{

D 6
	*retval = NBPG * CLSIZE;
E 6
I 6
	*retval = PAGE_SIZE;
E 6
	return (0);
}

E 18
I 15
D 45
struct sbrk_args {
	int	incr;
};
E 45
E 15
/* ARGSUSED */
I 10
int
E 10
sbrk(p, uap, retval)
	struct proc *p;
D 15
	struct args {
		int	incr;
	} *uap;
E 15
I 15
D 45
	struct sbrk_args *uap;
E 15
	int *retval;
E 45
I 45
	struct sbrk_args /* {
		syscallarg(int) incr;
	} */ *uap;
	register_t *retval;
E 45
{

	/* Not yet implemented */
	return (EOPNOTSUPP);
}

I 15
D 45
struct sstk_args {
	int	incr;
};
E 45
E 15
/* ARGSUSED */
I 10
int
E 10
sstk(p, uap, retval)
	struct proc *p;
D 15
	struct args {
		int	incr;
	} *uap;
E 15
I 15
D 45
	struct sstk_args *uap;
E 15
	int *retval;
E 45
I 45
	struct sstk_args /* {
		syscallarg(int) incr;
	} */ *uap;
	register_t *retval;
E 45
{

	/* Not yet implemented */
	return (EOPNOTSUPP);
}

I 12
D 33
struct mmap_args {
	caddr_t	addr;
D 25
	int	len;
E 25
I 25
	size_t	len;
E 25
	int	prot;
	int	flags;
	int	fd;
	long	pad;
	off_t	pos;
};

E 33
D 28
#ifdef COMPAT_43
E 28
I 28
#if defined(COMPAT_43) || defined(COMPAT_SUNOS)
E 28
I 18
D 45
struct getpagesize_args {
	int	dummy;
};
E 45
/* ARGSUSED */
int
D 27
getpagesize(p, uap, retval)
E 27
I 27
D 45
ogetpagesize(p, uap, retval)
E 45
I 45
compat_43_getpagesize(p, uap, retval)
E 45
E 27
	struct proc *p;
D 45
	struct getpagesize_args *uap;
	int *retval;
E 45
I 45
	void *uap;
	register_t *retval;
E 45
{

	*retval = PAGE_SIZE;
	return (0);
}
I 28
#endif /* COMPAT_43 || COMPAT_SUNOS */
E 28

I 33
D 45
struct mmap_args {
	caddr_t	addr;
	size_t	len;
	int	prot;
	int	flags;
	int	fd;
	long	pad;
	off_t	pos;
};

E 45
E 33
I 28
#ifdef COMPAT_43
E 28
E 18
I 15
D 33
struct osmmap_args {
E 33
I 33
D 45
struct ommap_args {
E 33
	caddr_t	addr;
	int	len;
	int	prot;
	int	flags;
	int	fd;
	long	pos;
};
E 45
E 15
E 12
I 10
int
E 10
D 12
smmap(p, uap, retval)
E 12
I 12
D 33
osmmap(p, uap, retval)
E 33
I 33
D 45
ommap(p, uap, retval)
E 45
I 45
compat_43_mmap(p, uap, retval)
E 45
E 33
E 12
D 2
	register struct proc *p;
E 2
I 2
	struct proc *p;
E 2
D 15
	register struct args {
		caddr_t	addr;
		int	len;
		int	prot;
		int	flags;
		int	fd;
D 12
		off_t	pos;
E 12
I 12
D 14
		off_t	pos;		/* XXX becomes long */
E 14
I 14
		long	pos;
E 14
E 12
	} *uap;
E 15
I 15
D 33
	register struct osmmap_args *uap;
E 33
I 33
D 45
	register struct ommap_args *uap;
E 33
E 15
	int *retval;
E 45
I 45
	register struct compat_43_mmap_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(int) len;
		syscallarg(int) prot;
		syscallarg(int) flags;
		syscallarg(int) fd;
		syscallarg(long) pos;
	} */ *uap;
	register_t *retval;
E 45
{
I 13
D 16
	long spos;
E 16
E 13
I 12
D 45
	struct mmap_args nargs;
E 45
I 45
	struct mmap_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(size_t) len;
		syscallarg(int) prot;
		syscallarg(int) flags;
		syscallarg(int) fd;
		syscallarg(long) pad;
		syscallarg(off_t) pos;
	} */ nargs;
E 45
	static const char cvtbsdprot[8] = {
		0,
		PROT_EXEC,
		PROT_WRITE,
		PROT_EXEC|PROT_WRITE,
		PROT_READ,
		PROT_EXEC|PROT_READ,
		PROT_WRITE|PROT_READ,
		PROT_EXEC|PROT_WRITE|PROT_READ,
	};
#define	OMAP_ANON	0x0002
#define	OMAP_COPY	0x0020
#define	OMAP_SHARED	0x0010
#define	OMAP_FIXED	0x0100
#define	OMAP_INHERIT	0x0800

D 45
	nargs.addr = uap->addr;
	nargs.len = uap->len;
	nargs.prot = cvtbsdprot[uap->prot&0x7];
	nargs.flags = 0;
	if (uap->flags & OMAP_ANON)
		nargs.flags |= MAP_ANON;
	if (uap->flags & OMAP_COPY)
		nargs.flags |= MAP_COPY;
	if (uap->flags & OMAP_SHARED)
		nargs.flags |= MAP_SHARED;
E 45
I 45
	SCARG(&nargs, addr) = SCARG(uap, addr);
	SCARG(&nargs, len) = SCARG(uap, len);
	SCARG(&nargs, prot) = cvtbsdprot[SCARG(uap, prot)&0x7];
	SCARG(&nargs, flags) = 0;
	if (SCARG(uap, flags) & OMAP_ANON)
		SCARG(&nargs, flags) |= MAP_ANON;
	if (SCARG(uap, flags) & OMAP_COPY)
		SCARG(&nargs, flags) |= MAP_COPY;
	if (SCARG(uap, flags) & OMAP_SHARED)
		SCARG(&nargs, flags) |= MAP_SHARED;
E 45
	else
D 45
		nargs.flags |= MAP_PRIVATE;
	if (uap->flags & OMAP_FIXED)
		nargs.flags |= MAP_FIXED;
	if (uap->flags & OMAP_INHERIT)
		nargs.flags |= MAP_INHERIT;
	nargs.fd = uap->fd;
D 13
	if ((long)uap->pos == 0)	/* XXX */
		uap->pos >>= 32;	/* XXX */
E 13
I 13
D 14
	spos = uap->pos >> 32;		/* XXX */
	if (spos > 0)			/* XXX */
		uap->pos = spos;	/* XXX */
E 14
E 13
	nargs.pos = uap->pos;
E 45
I 45
		SCARG(&nargs, flags) |= MAP_PRIVATE;
	if (SCARG(uap, flags) & OMAP_FIXED)
		SCARG(&nargs, flags) |= MAP_FIXED;
	if (SCARG(uap, flags) & OMAP_INHERIT)
		SCARG(&nargs, flags) |= MAP_INHERIT;
	SCARG(&nargs, fd) = SCARG(uap, fd);
	SCARG(&nargs, pos) = SCARG(uap, pos);
E 45
D 33
	return (smmap(p, &nargs, retval));
E 33
I 33
	return (mmap(p, &nargs, retval));
E 33
}
#endif

int
D 33
smmap(p, uap, retval)
E 33
I 33
mmap(p, uap, retval)
E 33
	struct proc *p;
D 45
	register struct mmap_args *uap;
	int *retval;
E 45
I 45
	register struct mmap_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(size_t) len;
		syscallarg(int) prot;
		syscallarg(int) flags;
		syscallarg(int) fd;
		syscallarg(long) pad;
		syscallarg(off_t) pos;
	} */ *uap;
	register_t *retval;
E 45
{
E 12
D 2
	struct file *fp;
E 2
I 2
	register struct filedesc *fdp = p->p_fd;
	register struct file *fp;
E 2
	struct vnode *vp;
D 40
	vm_offset_t addr;
E 40
I 40
	vm_offset_t addr, pos;
E 40
	vm_size_t size;
D 24
	vm_prot_t prot;
E 24
I 24
	vm_prot_t prot, maxprot;
E 24
	caddr_t handle;
D 12
	int mtype, error;
E 12
I 12
D 22
	int error;
E 22
I 22
	int flags, error;
E 22
E 12

I 26
D 45
	prot = uap->prot & VM_PROT_ALL;
E 26
I 22
	flags = uap->flags;
I 40
	pos = uap->pos;
E 45
I 45
	prot = SCARG(uap, prot) & VM_PROT_ALL;
	flags = SCARG(uap, flags);
	pos = SCARG(uap, pos);
E 45
E 40
E 22
#ifdef DEBUG
	if (mmapdebug & MDB_FOLLOW)
		printf("mmap(%d): addr %x len %x pro %x flg %x fd %d pos %x\n",
D 26
		       p->p_pid, uap->addr, uap->len, uap->prot,
E 26
I 26
D 45
		       p->p_pid, uap->addr, uap->len, prot,
E 26
D 22
		       uap->flags, uap->fd, uap->pos);
E 22
I 22
D 25
		       flags, uap->fd, uap->pos);
E 25
I 25
D 40
		       flags, uap->fd, (vm_offset_t)uap->pos);
E 40
I 40
		       flags, uap->fd, pos);
E 45
I 45
		       p->p_pid, SCARG(uap, addr), SCARG(uap, len), prot,
		       flags, SCARG(uap, fd), pos);
E 45
E 40
E 25
E 22
#endif
	/*
D 12
	 * Make sure one of the sharing types is specified
	 */
	mtype = uap->flags & MAP_TYPE;
	switch (mtype) {
	case MAP_FILE:
	case MAP_ANON:
		break;
	default:
		return(EINVAL);
	}
	/*
E 12
D 5
	 * Address (if FIXED) and size must be page aligned
E 5
I 5
	 * Address (if FIXED) must be page aligned.
	 * Size is implicitly rounded to a page boundary.
I 42
	 *
	 * XXX most (all?) vendors require that the file offset be
	 * page aligned as well.  However, we already have applications
	 * (e.g. nlist) that rely on unrestricted alignment.  Since we
	 * support it, let it happen.
E 42
E 5
	 */
D 5
	size = (vm_size_t)uap->len;
	addr = (vm_offset_t)uap->addr;
	if ((size & page_mask) ||
	    (uap->flags & MAP_FIXED) && (addr & page_mask))
E 5
I 5
D 45
	addr = (vm_offset_t) uap->addr;
E 45
I 45
	addr = (vm_offset_t) SCARG(uap, addr);
E 45
D 8
	if ((uap->flags & MAP_FIXED) && (addr & page_mask) || uap->len < 0)
E 8
I 8
D 12
	if ((uap->flags & MAP_FIXED) && (addr & PAGE_MASK) || uap->len < 0)
E 8
E 5
		return(EINVAL);
E 12
I 12
D 22
	if (((uap->flags & MAP_FIXED) && (addr & PAGE_MASK)) || uap->len < 0 ||
	    ((uap->flags & MAP_ANON) && uap->fd != -1))
E 22
I 22
D 26
	if (((flags & MAP_FIXED) && (addr & PAGE_MASK)) || uap->len < 0 ||
	    ((flags & MAP_ANON) && uap->fd != -1))
E 26
I 26
	if (((flags & MAP_FIXED) && (addr & PAGE_MASK)) ||
I 42
#if 0
E 42
I 41
	    ((flags & MAP_ANON) == 0 && (pos & PAGE_MASK)) ||
I 42
#endif
E 42
E 41
D 45
	    (ssize_t)uap->len < 0 || ((flags & MAP_ANON) && uap->fd != -1))
E 45
I 45
	    (ssize_t)SCARG(uap, len) < 0 || ((flags & MAP_ANON) && SCARG(uap, fd) != -1))
E 45
E 26
E 22
		return (EINVAL);
E 12
I 5
D 45
	size = (vm_size_t) round_page(uap->len);
E 45
I 45
	size = (vm_size_t) round_page(SCARG(uap, len));
E 45
I 19
D 21
	if ((uap->flags & MAP_FIXED) && (addr + size > VM_MAXUSER_ADDRESS))
		return (EINVAL);
E 21
E 19
E 5
	/*
I 21
	 * Check for illegal addresses.  Watch out for address wrap...
	 * Note that VM_*_ADDRESS are not constants due to casts (argh).
	 */
D 22
	if (uap->flags & MAP_FIXED) {
E 22
I 22
	if (flags & MAP_FIXED) {
E 22
		if (VM_MAXUSER_ADDRESS > 0 && addr + size >= VM_MAXUSER_ADDRESS)
			return (EINVAL);
		if (VM_MIN_ADDRESS > 0 && addr < VM_MIN_ADDRESS)
			return (EINVAL);
		if (addr > addr + size)
			return (EINVAL);
	}
	/*
E 21
I 5
D 40
	 * XXX if no hint provided for a non-fixed mapping place it after
	 * the end of the largest possible heap.
E 40
I 40
	 * XXX for non-fixed mappings where no hint is provided or
	 * the hint would fall in the potential heap space,
	 * place it after the end of the largest possible heap.
E 40
	 *
	 * There should really be a pmap call to determine a reasonable
	 * location.
	 */
D 22
	if (addr == 0 && (uap->flags & MAP_FIXED) == 0)
E 22
I 22
D 40
	if (addr == 0 && (flags & MAP_FIXED) == 0)
E 40
I 40
	else if (addr < round_page(p->p_vmspace->vm_daddr + MAXDSIZ))
E 40
E 22
		addr = round_page(p->p_vmspace->vm_daddr + MAXDSIZ);
D 26
	/*
E 5
D 12
	 * Mapping file or named anonymous, get fp for validation
	 */
	if (mtype == MAP_FILE || uap->fd != -1) {
D 2
		if ((unsigned)uap->fd >= NOFILE ||
		    (fp = u.u_ofile[uap->fd]) == NULL)
E 2
I 2
D 3
		if (((unsigned)uap->fd) >= fdp->fd_maxfiles ||
		    (fp = OFILE(fdp, uap->fd)) == NULL)
E 3
I 3
		if (((unsigned)uap->fd) >= fdp->fd_nfiles ||
		    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 3
E 2
			return(EBADF);
	}
	/*
E 12
	 * If we are mapping a file we need to check various
	 * file/vnode related things.
	 */
E 26
D 12
	if (mtype == MAP_FILE) {
E 12
I 12
D 22
	if (uap->flags & MAP_ANON)
E 22
I 22
D 24
	if (flags & MAP_ANON)
E 24
I 24
	if (flags & MAP_ANON) {
I 26
		/*
		 * Mapping blank space is trivial.
		 */
E 26
E 24
E 22
		handle = NULL;
D 24
	else {
E 24
I 24
		maxprot = VM_PROT_ALL;
I 40
		pos = 0;
E 40
	} else {
E 24
E 12
		/*
I 12
		 * Mapping file, get fp for validation.
E 12
D 26
		 * Obtain vnode and make sure it is of appropriate type
E 26
I 26
		 * Obtain vnode and make sure it is of appropriate type.
E 26
		 */
I 12
D 45
		if (((unsigned)uap->fd) >= fdp->fd_nfiles ||
		    (fp = fdp->fd_ofiles[uap->fd]) == NULL)
E 45
I 45
		if (((unsigned)SCARG(uap, fd)) >= fdp->fd_nfiles ||
		    (fp = fdp->fd_ofiles[SCARG(uap, fd)]) == NULL)
E 45
D 26
			return(EBADF);
E 26
I 26
			return (EBADF);
E 26
E 12
		if (fp->f_type != DTYPE_VNODE)
D 26
			return(EINVAL);
E 26
I 26
			return (EINVAL);
E 26
		vp = (struct vnode *)fp->f_data;
		if (vp->v_type != VREG && vp->v_type != VCHR)
D 26
			return(EINVAL);
E 26
I 26
			return (EINVAL);
E 26
		/*
D 26
		 * Ensure that file protection and desired protection
		 * are compatible.  Note that we only worry about writability
		 * if mapping is shared.
		 */
		if ((uap->prot & PROT_READ) && (fp->f_flag & FREAD) == 0 ||
D 22
		    ((uap->flags & MAP_SHARED) &&
E 22
I 22
		    ((flags & MAP_SHARED) &&
E 22
		     (uap->prot & PROT_WRITE) && (fp->f_flag & FWRITE) == 0))
			return(EACCES);
I 22
D 24
		if ((flags & MAP_SHARED) && (fp->f_flag & FWRITE) == 0)
			flags = (flags & ~MAP_SHARED) | MAP_PRIVATE;
E 24
E 22
		handle = (caddr_t)vp;
I 24
		/*
		 * Set maximum protection as dictated by the open file.
E 26
I 26
D 38
		 * Ensure that file and memory protections are compatible.
		 * Note that we only worry about writability if mapping is
		 * shared; in this case, current and max prot are dictated
		 * by the open file.
E 26
		 * XXX use the vnode instead?  Problem is: what credentials
		 * do we use for determination?  What if proc does a setuid?
E 38
I 38
		 * XXX hack to handle use of /dev/zero to map anon
		 * memory (ala SunOS).
E 38
		 */
D 26
		maxprot = 0;
E 26
I 26
D 38
		maxprot = VM_PROT_EXECUTE;	/* ??? */
E 26
		if (fp->f_flag & FREAD)
D 26
			maxprot |= VM_PROT_READ|VM_PROT_EXECUTE;
		if (fp->f_flag & FWRITE)
E 26
I 26
			maxprot |= VM_PROT_READ;
		else if (prot & PROT_READ)
			return (EACCES);
		if (flags & MAP_SHARED) {
			if (fp->f_flag & FWRITE)
				maxprot |= VM_PROT_WRITE;
			else if (prot & PROT_WRITE)
E 38
I 38
		if (vp->v_type == VCHR && iszerodev(vp->v_rdev)) {
			handle = NULL;
			maxprot = VM_PROT_ALL;
			flags |= MAP_ANON;
		} else {
			/*
			 * Ensure that file and memory protections are
			 * compatible.  Note that we only worry about
			 * writability if mapping is shared; in this case,
			 * current and max prot are dictated by the open file.
			 * XXX use the vnode instead?  Problem is: what
			 * credentials do we use for determination?
			 * What if proc does a setuid?
			 */
			maxprot = VM_PROT_EXECUTE;	/* ??? */
			if (fp->f_flag & FREAD)
				maxprot |= VM_PROT_READ;
			else if (prot & PROT_READ)
E 38
				return (EACCES);
D 38
		} else
E 26
			maxprot |= VM_PROT_WRITE;
I 26
		handle = (caddr_t)vp;
E 38
I 38
			if (flags & MAP_SHARED) {
				if (fp->f_flag & FWRITE)
					maxprot |= VM_PROT_WRITE;
				else if (prot & PROT_WRITE)
					return (EACCES);
			} else
				maxprot |= VM_PROT_WRITE;
			handle = (caddr_t)vp;
		}
E 38
E 26
E 24
D 12
	} else if (uap->fd != -1)
		handle = (caddr_t)fp;
	else
		handle = NULL;
E 12
I 12
	}
E 12
D 24
	/*
	 * Map protections to MACH style
	 */
E 24
D 12
	prot = VM_PROT_NONE;
	if (uap->prot & PROT_READ)
		prot |= VM_PROT_READ;
	if (uap->prot & PROT_WRITE)
		prot |= VM_PROT_WRITE;
	if (uap->prot & PROT_EXEC)
		prot |= VM_PROT_EXECUTE;

E 12
I 12
D 26
	prot = uap->prot & VM_PROT_ALL;
E 26
E 12
D 3
	error = vm_mmap(p->p_map, &addr, size, prot,
E 3
I 3
D 24
	error = vm_mmap(&p->p_vmspace->vm_map, &addr, size, prot,
E 24
I 24
	error = vm_mmap(&p->p_vmspace->vm_map, &addr, size, prot, maxprot,
E 24
E 3
D 22
			uap->flags, handle, (vm_offset_t)uap->pos);
E 22
I 22
D 26
			flags, handle, (vm_offset_t)uap->pos);
E 26
I 26
D 41
	    flags, handle, (vm_offset_t)uap->pos);
E 41
I 41
	    flags, handle, pos);
E 41
E 26
E 22
	if (error == 0)
D 26
		*retval = (int) addr;
	return(error);
E 26
I 26
D 45
		*retval = (int)addr;
E 45
I 45
		*retval = (register_t)addr;
E 45
	return (error);
E 26
}

I 15
D 45
struct msync_args {
	caddr_t	addr;
	int	len;
};
E 45
E 15
I 10
int
E 10
msync(p, uap, retval)
	struct proc *p;
D 15
	struct args {
D 5
		char	*addr;
E 5
I 5
		caddr_t	addr;
E 5
		int	len;
	} *uap;
E 15
I 15
D 45
	struct msync_args *uap;
E 15
	int *retval;
E 45
I 45
	struct msync_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(int) len;
	} */ *uap;
	register_t *retval;
E 45
{
D 39
	vm_offset_t addr, objoff, oaddr;
	vm_size_t size, osize;
	vm_prot_t prot, mprot;
	vm_inherit_t inherit;
	vm_object_t object;
	boolean_t shared;
E 39
I 39
	vm_offset_t addr;
	vm_size_t size;
	vm_map_t map;
E 39
	int rv;
I 39
	boolean_t syncio, invalidate;
E 39

#ifdef DEBUG
	if (mmapdebug & (MDB_FOLLOW|MDB_SYNC))
		printf("msync(%d): addr %x len %x\n",
D 45
		       p->p_pid, uap->addr, uap->len);
E 45
I 45
		       p->p_pid, SCARG(uap, addr), SCARG(uap, len));
E 45
#endif
D 5
	if (((int)uap->addr & page_mask) || (uap->len & page_mask))
E 5
I 5
D 8
	if (((int)uap->addr & page_mask) || uap->len < 0)
E 8
I 8
D 39
	if (((int)uap->addr & PAGE_MASK) || uap->len < 0)
E 8
E 5
		return(EINVAL);
	addr = oaddr = (vm_offset_t)uap->addr;
	osize = (vm_size_t)uap->len;
E 39
I 39
D 45
	if (((int)uap->addr & PAGE_MASK) || uap->addr + uap->len < uap->addr)
E 45
I 45
	if (((vm_offset_t)SCARG(uap, addr) & PAGE_MASK) ||
	    SCARG(uap, addr) + SCARG(uap, len) < SCARG(uap, addr))
E 45
		return (EINVAL);
	map = &p->p_vmspace->vm_map;
D 45
	addr = (vm_offset_t)uap->addr;
	size = (vm_size_t)uap->len;
E 45
I 45
	addr = (vm_offset_t)SCARG(uap, addr);
	size = (vm_size_t)SCARG(uap, len);
E 45
E 39
	/*
D 39
	 * Region must be entirely contained in a single entry
E 39
I 39
	 * XXX Gak!  If size is zero we are supposed to sync "all modified
	 * pages with the region containing addr".  Unfortunately, we
	 * don't really keep track of individual mmaps so we approximate
	 * by flushing the range of the map entry containing addr.
	 * This can be incorrect if the region splits or is coalesced
	 * with a neighbor.
E 39
	 */
D 3
	if (!vm_map_is_allocated(p->p_map, addr, addr+osize, TRUE))
E 3
I 3
D 39
	if (!vm_map_is_allocated(&p->p_vmspace->vm_map, addr, addr+osize,
	    TRUE))
E 3
		return(EINVAL);
	/*
	 * Determine the object associated with that entry
	 * (object is returned locked on KERN_SUCCESS)
	 */
D 3
	rv = vm_region(p->p_map, &addr, &size, &prot, &mprot,
E 3
I 3
	rv = vm_region(&p->p_vmspace->vm_map, &addr, &size, &prot, &mprot,
E 3
		       &inherit, &shared, &object, &objoff);
	if (rv != KERN_SUCCESS)
		return(EINVAL);
E 39
I 39
	if (size == 0) {
		vm_map_entry_t entry;

		vm_map_lock_read(map);
		rv = vm_map_lookup_entry(map, addr, &entry);
		vm_map_unlock_read(map);
D 43
		if (rv)
E 43
I 43
		if (!rv)
E 43
			return (EINVAL);
		addr = entry->start;
		size = entry->end - entry->start;
	}
E 39
#ifdef DEBUG
	if (mmapdebug & MDB_SYNC)
D 39
		printf("msync: region: object %x addr %x size %d objoff %d\n",
		       object, addr, size, objoff);
E 39
I 39
		printf("msync: cleaning/flushing address range [%x-%x)\n",
		       addr, addr+size);
E 39
#endif
	/*
D 39
	 * Do not msync non-vnoded backed objects.
E 39
I 39
	 * Could pass this in as a third flag argument to implement
	 * Sun's MS_ASYNC.
E 39
	 */
D 3
	if (object->internal || object->pager == vm_pager_null ||
E 3
I 3
D 7
	if (object->internal || object->pager == NULL ||
E 7
I 7
D 39
	if ((object->flags & OBJ_INTERNAL) || object->pager == NULL ||
E 7
E 3
	    object->pager->pg_type != PG_VNODE) {
		vm_object_unlock(object);
		return(EINVAL);
	}
	objoff += oaddr - addr;
	if (osize == 0)
		osize = size;
#ifdef DEBUG
	if (mmapdebug & MDB_SYNC)
		printf("msync: cleaning/flushing object range [%x-%x)\n",
		       objoff, objoff+osize);
#endif
	if (prot & VM_PROT_WRITE)
D 9
		vm_object_page_clean(object, objoff, objoff+osize);
E 9
I 9
		vm_object_page_clean(object, objoff, objoff+osize, FALSE);
E 39
I 39
	syncio = TRUE;
E 39
E 9
	/*
D 39
	 * (XXX)
	 * Bummer, gotta flush all cached pages to ensure
	 * consistency with the file system cache.
E 39
I 39
	 * XXX bummer, gotta flush all cached pages to ensure
	 * consistency with the file system cache.  Otherwise, we could
	 * pass this in to implement Sun's MS_INVALIDATE.
E 39
	 */
D 39
	vm_object_page_remove(object, objoff, objoff+osize);
	vm_object_unlock(object);
	return(0);
E 39
I 39
	invalidate = TRUE;
	/*
	 * Clean the pages and interpret the return value.
	 */
	rv = vm_map_clean(map, addr, addr+size, syncio, invalidate);
	switch (rv) {
	case KERN_SUCCESS:
		break;
	case KERN_INVALID_ADDRESS:
		return (EINVAL);	/* Sun returns ENOMEM? */
	case KERN_FAILURE:
		return (EIO);
	default:
		return (EINVAL);
	}
	return (0);
E 39
}

I 15
D 45
struct munmap_args {
	caddr_t	addr;
	int	len;
};
E 45
E 15
I 10
int
E 10
munmap(p, uap, retval)
	register struct proc *p;
D 15
	register struct args {
		caddr_t	addr;
		int	len;
	} *uap;
E 15
I 15
D 45
	register struct munmap_args *uap;
E 15
	int *retval;
E 45
I 45
	register struct munmap_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(int) len;
	} */ *uap;
	register_t *retval;
E 45
{
	vm_offset_t addr;
	vm_size_t size;
I 39
	vm_map_t map;
E 39

#ifdef DEBUG
	if (mmapdebug & MDB_FOLLOW)
		printf("munmap(%d): addr %x len %x\n",
D 45
		       p->p_pid, uap->addr, uap->len);
E 45
I 45
		       p->p_pid, SCARG(uap, addr), SCARG(uap, len));
E 45
#endif

D 45
	addr = (vm_offset_t) uap->addr;
D 5
	size = (vm_size_t) uap->len;
	if ((addr & page_mask) || (size & page_mask))
E 5
I 5
D 8
	if ((addr & page_mask) || uap->len < 0)
E 8
I 8
	if ((addr & PAGE_MASK) || uap->len < 0)
E 45
I 45
	addr = (vm_offset_t) SCARG(uap, addr);
	if ((addr & PAGE_MASK) || SCARG(uap, len) < 0)
E 45
E 8
E 5
		return(EINVAL);
I 5
D 45
	size = (vm_size_t) round_page(uap->len);
E 45
I 45
	size = (vm_size_t) round_page(SCARG(uap, len));
E 45
E 5
	if (size == 0)
		return(0);
D 3
	if (!vm_map_is_allocated(p->p_map, addr, addr+size, FALSE))
E 3
I 3
D 21
	if (!vm_map_is_allocated(&p->p_vmspace->vm_map, addr, addr+size,
E 21
I 21
	/*
	 * Check for illegal addresses.  Watch out for address wrap...
	 * Note that VM_*_ADDRESS are not constants due to casts (argh).
	 */
	if (VM_MAXUSER_ADDRESS > 0 && addr + size >= VM_MAXUSER_ADDRESS)
		return (EINVAL);
	if (VM_MIN_ADDRESS > 0 && addr < VM_MIN_ADDRESS)
		return (EINVAL);
	if (addr > addr + size)
		return (EINVAL);
D 39
	if (!vm_map_is_allocated(&p->p_vmspace->vm_map, addr, addr + size,
E 21
	    FALSE))
E 39
I 39
	map = &p->p_vmspace->vm_map;
	/*
	 * Make sure entire range is allocated.
I 42
	 * XXX this seemed overly restrictive, so we relaxed it.
E 42
	 */
I 42
#if 0
E 42
	if (!vm_map_check_protection(map, addr, addr + size, VM_PROT_NONE))
E 39
E 3
		return(EINVAL);
I 42
#endif
E 42
	/* returns nothing but KERN_SUCCESS anyway */
D 3
	(void) vm_map_remove(p->p_map, addr, addr+size);
E 3
I 3
D 39
	(void) vm_map_remove(&p->p_vmspace->vm_map, addr, addr+size);
E 39
I 39
	(void) vm_map_remove(map, addr, addr+size);
E 39
E 3
	return(0);
}

I 10
void
E 10
D 44
munmapfd(fd)
E 44
I 44
munmapfd(p, fd)
	struct proc *p;
E 44
I 11
	int fd;
E 11
{
#ifdef DEBUG
	if (mmapdebug & MDB_FOLLOW)
D 3
		printf("munmapfd(%d): fd %d\n", u.u_procp->p_pid, fd);
E 3
I 3
D 44
		printf("munmapfd(%d): fd %d\n", curproc->p_pid, fd);
E 44
I 44
		printf("munmapfd(%d): fd %d\n", p->p_pid, fd);
E 44
E 3
#endif

	/*
D 39
	 * XXX -- should vm_deallocate any regions mapped to this file
E 39
I 39
	 * XXX should vm_deallocate any regions mapped to this file
E 39
	 */
D 2
	u.u_pofile[fd] &= ~UF_MAPPED;
E 2
I 2
D 3
	OFILEFLAGS(u.u_procp->p_fd, fd) &= ~UF_MAPPED;
E 3
I 3
D 44
	curproc->p_fd->fd_ofileflags[fd] &= ~UF_MAPPED;
E 44
I 44
	p->p_fd->fd_ofileflags[fd] &= ~UF_MAPPED;
E 44
E 3
E 2
}

I 15
D 45
struct mprotect_args {
	caddr_t	addr;
	int	len;
	int	prot;
};
E 45
E 15
I 10
int
E 10
mprotect(p, uap, retval)
	struct proc *p;
D 15
	struct args {
D 5
		char	*addr;
E 5
I 5
		caddr_t	addr;
E 5
		int	len;
		int	prot;
	} *uap;
E 15
I 15
D 45
	struct mprotect_args *uap;
E 15
	int *retval;
E 45
I 45
	struct mprotect_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(int) len;
		syscallarg(int) prot;
	} */ *uap;
	register_t *retval;
E 45
{
	vm_offset_t addr;
	vm_size_t size;
	register vm_prot_t prot;

#ifdef DEBUG
	if (mmapdebug & MDB_FOLLOW)
		printf("mprotect(%d): addr %x len %x prot %d\n",
D 45
		       p->p_pid, uap->addr, uap->len, uap->prot);
E 45
I 45
		       p->p_pid, SCARG(uap, addr), SCARG(uap, len), SCARG(uap, prot));
E 45
#endif

D 15
	addr = (vm_offset_t) uap->addr;
E 15
I 15
D 45
	addr = (vm_offset_t)uap->addr;
E 15
D 5
	size = (vm_size_t) uap->len;
	if ((addr & page_mask) || (size & page_mask))
E 5
I 5
D 8
	if ((addr & page_mask) || uap->len < 0)
E 8
I 8
	if ((addr & PAGE_MASK) || uap->len < 0)
E 45
I 45
	addr = (vm_offset_t)SCARG(uap, addr);
	if ((addr & PAGE_MASK) || SCARG(uap, len) < 0)
E 45
E 8
E 5
		return(EINVAL);
I 5
D 15
	size = (vm_size_t) uap->len;
E 15
I 15
D 45
	size = (vm_size_t)uap->len;
E 15
E 5
D 24
	/*
	 * Map protections
	 */
	prot = VM_PROT_NONE;
	if (uap->prot & PROT_READ)
		prot |= VM_PROT_READ;
	if (uap->prot & PROT_WRITE)
		prot |= VM_PROT_WRITE;
	if (uap->prot & PROT_EXEC)
		prot |= VM_PROT_EXECUTE;
E 24
I 24
	prot = uap->prot & VM_PROT_ALL;
E 45
I 45
	size = (vm_size_t)SCARG(uap, len);
	prot = SCARG(uap, prot) & VM_PROT_ALL;
E 45
E 24

D 3
	switch (vm_map_protect(p->p_map, addr, addr+size, prot, FALSE)) {
E 3
I 3
	switch (vm_map_protect(&p->p_vmspace->vm_map, addr, addr+size, prot,
	    FALSE)) {
E 3
	case KERN_SUCCESS:
		return (0);
	case KERN_PROTECTION_FAILURE:
		return (EACCES);
	}
	return (EINVAL);
}

I 15
D 45
struct madvise_args {
	caddr_t	addr;
	int	len;
	int	behav;
};
E 45
E 15
/* ARGSUSED */
I 10
int
E 10
madvise(p, uap, retval)
	struct proc *p;
D 15
	struct args {
D 5
		char	*addr;
E 5
I 5
		caddr_t	addr;
E 5
		int	len;
		int	behav;
	} *uap;
E 15
I 15
D 45
	struct madvise_args *uap;
E 15
	int *retval;
E 45
I 45
	struct madvise_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(int) len;
		syscallarg(int) behav;
	} */ *uap;
	register_t *retval;
E 45
{

	/* Not yet implemented */
	return (EOPNOTSUPP);
}

I 15
D 45
struct mincore_args {
	caddr_t	addr;
	int	len;
	char	*vec;
};
E 45
E 15
/* ARGSUSED */
I 10
int
E 10
mincore(p, uap, retval)
	struct proc *p;
D 15
	struct args {
D 5
		char	*addr;
E 5
I 5
		caddr_t	addr;
E 5
		int	len;
		char	*vec;
	} *uap;
E 15
I 15
D 45
	struct mincore_args *uap;
E 15
	int *retval;
E 45
I 45
	struct mincore_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(int) len;
		syscallarg(char *) vec;
	} */ *uap;
	register_t *retval;
E 45
{

	/* Not yet implemented */
	return (EOPNOTSUPP);
I 29
}

D 45
struct mlock_args {
	caddr_t	addr;
D 31
	int	len;
E 31
I 31
	size_t	len;
E 31
};
E 45
int
mlock(p, uap, retval)
	struct proc *p;
D 45
	struct mlock_args *uap;
	int *retval;
E 45
I 45
	struct mlock_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(size_t) len;
	} */ *uap;
	register_t *retval;
E 45
{
	vm_offset_t addr;
	vm_size_t size;
	int error;
	extern int vm_page_max_wired;

#ifdef DEBUG
	if (mmapdebug & MDB_FOLLOW)
		printf("mlock(%d): addr %x len %x\n",
D 45
		       p->p_pid, uap->addr, uap->len);
E 45
I 45
		       p->p_pid, SCARG(uap, addr), SCARG(uap, len));
E 45
#endif
D 45
	addr = (vm_offset_t)uap->addr;
D 35
	if ((addr & PAGE_MASK) || uap->len < 0)
E 35
I 35
	if ((addr & PAGE_MASK) || uap->addr + uap->len < uap->addr)
E 45
I 45
	addr = (vm_offset_t)SCARG(uap, addr);
	if ((addr & PAGE_MASK) || SCARG(uap, addr) + SCARG(uap, len) < SCARG(uap, addr))
E 45
E 35
		return (EINVAL);
D 45
	size = round_page((vm_size_t)uap->len);
E 45
I 45
	size = round_page((vm_size_t)SCARG(uap, len));
E 45
	if (atop(size) + cnt.v_wire_count > vm_page_max_wired)
D 30
		return (ENOMEM);
E 30
I 30
		return (EAGAIN);
E 30
#ifdef pmap_wired_count
	if (size + ptoa(pmap_wired_count(vm_map_pmap(&p->p_vmspace->vm_map))) >
	    p->p_rlimit[RLIMIT_MEMLOCK].rlim_cur)
D 30
		return (ENOMEM);
E 30
I 30
		return (EAGAIN);
E 30
#else
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
#endif

	error = vm_map_pageable(&p->p_vmspace->vm_map, addr, addr+size, FALSE);
	return (error == KERN_SUCCESS ? 0 : ENOMEM);
}

D 45
struct munlock_args {
	caddr_t	addr;
D 31
	int	len;
E 31
I 31
	size_t	len;
E 31
};
E 45
int
munlock(p, uap, retval)
	struct proc *p;
D 45
	struct munlock_args *uap;
	int *retval;
E 45
I 45
	struct munlock_args /* {
		syscallarg(caddr_t) addr;
		syscallarg(size_t) len;
	} */ *uap;
	register_t *retval;
E 45
{
	vm_offset_t addr;
	vm_size_t size;
	int error;

#ifdef DEBUG
	if (mmapdebug & MDB_FOLLOW)
		printf("munlock(%d): addr %x len %x\n",
D 45
		       p->p_pid, uap->addr, uap->len);
E 45
I 45
		       p->p_pid, SCARG(uap, addr), SCARG(uap, len));
E 45
#endif
D 45
	addr = (vm_offset_t)uap->addr;
D 35
	if ((addr & PAGE_MASK) || uap->len < 0)
E 35
I 35
	if ((addr & PAGE_MASK) || uap->addr + uap->len < uap->addr)
E 45
I 45
	addr = (vm_offset_t)SCARG(uap, addr);
	if ((addr & PAGE_MASK) || SCARG(uap, addr) + SCARG(uap, len) < SCARG(uap, addr))
E 45
E 35
		return (EINVAL);
#ifndef pmap_wired_count
	if (error = suser(p->p_ucred, &p->p_acflag))
		return (error);
#endif
D 45
	size = round_page((vm_size_t)uap->len);
E 45
I 45
	size = round_page((vm_size_t)SCARG(uap, len));
E 45

	error = vm_map_pageable(&p->p_vmspace->vm_map, addr, addr+size, TRUE);
	return (error == KERN_SUCCESS ? 0 : ENOMEM);
E 29
}

/*
 * Internal version of mmap.
 * Currently used by mmap, exec, and sys5 shared memory.
D 12
 * Handle is:
 *	MAP_FILE: a vnode pointer
 *	MAP_ANON: NULL or a file pointer
E 12
I 12
 * Handle is either a vnode pointer or NULL for MAP_ANON.
E 12
 */
I 10
int
E 10
D 24
vm_mmap(map, addr, size, prot, flags, handle, foff)
E 24
I 24
vm_mmap(map, addr, size, prot, maxprot, flags, handle, foff)
E 24
	register vm_map_t map;
	register vm_offset_t *addr;
	register vm_size_t size;
D 24
	vm_prot_t prot;
E 24
I 24
	vm_prot_t prot, maxprot;
E 24
	register int flags;
	caddr_t handle;		/* XXX should be vp */
	vm_offset_t foff;
{
	register vm_pager_t pager;
	boolean_t fitit;
	vm_object_t object;
D 35
	struct vnode *vp;
E 35
I 35
	struct vnode *vp = NULL;
E 35
	int type;
	int rv = KERN_SUCCESS;

	if (size == 0)
		return (0);

	if ((flags & MAP_FIXED) == 0) {
		fitit = TRUE;
		*addr = round_page(*addr);
	} else {
		fitit = FALSE;
D 15
		(void) vm_deallocate(map, *addr, size);
E 15
I 15
		(void)vm_deallocate(map, *addr, size);
E 15
	}

	/*
	 * Lookup/allocate pager.  All except an unnamed anonymous lookup
	 * gain a reference to ensure continued existance of the object.
	 * (XXX the exception is to appease the pageout daemon)
	 */
D 12
	if ((flags & MAP_TYPE) == MAP_ANON)
E 12
I 12
	if (flags & MAP_ANON)
E 12
		type = PG_DFLT;
	else {
		vp = (struct vnode *)handle;
		if (vp->v_type == VCHR) {
			type = PG_DEVICE;
			handle = (caddr_t)vp->v_rdev;
		} else
			type = PG_VNODE;
	}
D 37
	pager = vm_pager_allocate(type, handle, size, prot);
E 37
I 37
	pager = vm_pager_allocate(type, handle, size, prot, foff);
E 37
D 3
	if (pager == VM_PAGER_NULL)
E 3
I 3
	if (pager == NULL)
E 3
		return (type == PG_DEVICE ? EINVAL : ENOMEM);
	/*
	 * Find object and release extra reference gained by lookup
	 */
	object = vm_object_lookup(pager);
	vm_object_deallocate(object);

	/*
	 * Anonymous memory.
	 */
D 12
	if ((flags & MAP_TYPE) == MAP_ANON) {
E 12
I 12
	if (flags & MAP_ANON) {
E 12
		rv = vm_allocate_with_pager(map, addr, size, fitit,
D 25
					    pager, (vm_offset_t)foff, TRUE);
E 25
I 25
					    pager, foff, TRUE);
E 25
		if (rv != KERN_SUCCESS) {
			if (handle == NULL)
				vm_pager_deallocate(pager);
			else
				vm_object_deallocate(object);
			goto out;
		}
		/*
I 23
D 24
		 * The object of unnamed anonymous regions was just created
		 * find it for pager_cache.
		 */
		if (handle == NULL)
			object = vm_object_lookup(pager);

		/*
E 24
E 23
		 * Don't cache anonymous objects.
		 * Loses the reference gained by vm_pager_allocate.
I 24
		 * Note that object will be NULL when handle == NULL,
		 * this is ok since vm_allocate_with_pager has made
		 * sure that these objects are uncached.
E 24
		 */
		(void) pager_cache(object, FALSE);
#ifdef DEBUG
		if (mmapdebug & MDB_MAPIT)
			printf("vm_mmap(%d): ANON *addr %x size %x pager %x\n",
D 3
			       u.u_procp->p_pid, *addr, size, pager);
E 3
I 3
			       curproc->p_pid, *addr, size, pager);
E 3
#endif
	}
	/*
D 12
	 * Must be type MAP_FILE.
E 12
I 12
	 * Must be a mapped file.
E 12
	 * Distinguish between character special and regular files.
	 */
	else if (vp->v_type == VCHR) {
		rv = vm_allocate_with_pager(map, addr, size, fitit,
D 25
					    pager, (vm_offset_t)foff, FALSE);
E 25
I 25
					    pager, foff, FALSE);
E 25
		/*
		 * Uncache the object and lose the reference gained
		 * by vm_pager_allocate().  If the call to
		 * vm_allocate_with_pager() was sucessful, then we
		 * gained an additional reference ensuring the object
		 * will continue to exist.  If the call failed then
		 * the deallocate call below will terminate the
		 * object which is fine.
		 */
		(void) pager_cache(object, FALSE);
		if (rv != KERN_SUCCESS)
			goto out;
	}
	/*
	 * A regular file
	 */
	else {
#ifdef DEBUG
D 3
		if (object == VM_OBJECT_NULL)
E 3
I 3
		if (object == NULL)
E 3
			printf("vm_mmap: no object: vp %x, pager %x\n",
			       vp, pager);
#endif
		/*
		 * Map it directly.
		 * Allows modifications to go out to the vnode.
		 */
		if (flags & MAP_SHARED) {
			rv = vm_allocate_with_pager(map, addr, size,
						    fitit, pager,
D 25
						    (vm_offset_t)foff, FALSE);
E 25
I 25
						    foff, FALSE);
E 25
			if (rv != KERN_SUCCESS) {
				vm_object_deallocate(object);
				goto out;
			}
			/*
			 * Don't cache the object.  This is the easiest way
			 * of ensuring that data gets back to the filesystem
			 * because vnode_pager_deallocate() will fsync the
			 * vnode.  pager_cache() will lose the extra ref.
			 */
			if (prot & VM_PROT_WRITE)
				pager_cache(object, FALSE);
			else
				vm_object_deallocate(object);
		}
		/*
		 * Copy-on-write of file.  Two flavors.
		 * MAP_COPY is true COW, you essentially get a snapshot of
		 * the region at the time of mapping.  MAP_PRIVATE means only
		 * that your changes are not reflected back to the object.
		 * Changes made by others will be seen.
		 */
		else {
			vm_map_t tmap;
			vm_offset_t off;

			/* locate and allocate the target address space */
D 3
			rv = vm_map_find(map, VM_OBJECT_NULL, (vm_offset_t)0,
E 3
I 3
			rv = vm_map_find(map, NULL, (vm_offset_t)0,
E 3
					 addr, size, fitit);
			if (rv != KERN_SUCCESS) {
				vm_object_deallocate(object);
				goto out;
			}
			tmap = vm_map_create(pmap_create(size), VM_MIN_ADDRESS,
					     VM_MIN_ADDRESS+size, TRUE);
			off = VM_MIN_ADDRESS;
			rv = vm_allocate_with_pager(tmap, &off, size,
						    TRUE, pager,
D 25
						    (vm_offset_t)foff, FALSE);
E 25
I 25
						    foff, FALSE);
E 25
			if (rv != KERN_SUCCESS) {
				vm_object_deallocate(object);
				vm_map_deallocate(tmap);
				goto out;
			}
			/*
			 * (XXX)
			 * MAP_PRIVATE implies that we see changes made by
			 * others.  To ensure that we need to guarentee that
			 * no copy object is created (otherwise original
			 * pages would be pushed to the copy object and we
			 * would never see changes made by others).  We
			 * totally sleeze it right now by marking the object
			 * internal temporarily.
			 */
			if ((flags & MAP_COPY) == 0)
D 7
				object->internal = TRUE;
E 7
I 7
				object->flags |= OBJ_INTERNAL;
E 7
			rv = vm_map_copy(map, tmap, *addr, size, off,
					 FALSE, FALSE);
D 7
			object->internal = FALSE;
E 7
I 7
			object->flags &= ~OBJ_INTERNAL;
E 7
			/*
			 * (XXX)
			 * My oh my, this only gets worse...
			 * Force creation of a shadow object so that
			 * vm_map_fork will do the right thing.
			 */
			if ((flags & MAP_COPY) == 0) {
				vm_map_t tmap;
				vm_map_entry_t tentry;
				vm_object_t tobject;
				vm_offset_t toffset;
				vm_prot_t tprot;
				boolean_t twired, tsu;

				tmap = map;
				vm_map_lookup(&tmap, *addr, VM_PROT_WRITE,
					      &tentry, &tobject, &toffset,
					      &tprot, &twired, &tsu);
				vm_map_lookup_done(tmap, tentry);
			}
			/*
			 * (XXX)
			 * Map copy code cannot detect sharing unless a
			 * sharing map is involved.  So we cheat and write
D 4
			 * protect everything ourselves.  Note we cannot
			 * use vm_object_pmap_copy() because that relies
			 * on the page copy_on_write bit which isn't
			 * always accurate with shared objects.
E 4
I 4
			 * protect everything ourselves.
E 4
			 */
D 4
			vm_object_pmap_force_copy(object, (vm_offset_t)foff,
E 4
I 4
D 25
			vm_object_pmap_copy(object, (vm_offset_t)foff,
E 4
					    (vm_offset_t)foff+size);
E 25
I 25
			vm_object_pmap_copy(object, foff, foff + size);
E 25
			vm_object_deallocate(object);
			vm_map_deallocate(tmap);
			if (rv != KERN_SUCCESS)
				goto out;
		}
#ifdef DEBUG
		if (mmapdebug & MDB_MAPIT)
			printf("vm_mmap(%d): FILE *addr %x size %x pager %x\n",
D 3
			       u.u_procp->p_pid, *addr, size, pager);
E 3
I 3
			       curproc->p_pid, *addr, size, pager);
E 3
#endif
	}
	/*
	 * Correct protection (default is VM_PROT_ALL).
D 24
	 * Note that we set the maximum protection.  This may not be
	 * entirely correct.  Maybe the maximum protection should be based
	 * on the object permissions where it makes sense (e.g. a vnode).
	 *
	 * Changed my mind: leave max prot at VM_PROT_ALL.
E 24
I 24
	 * If maxprot is different than prot, we must set both explicitly.
E 24
	 */
D 24
	if (prot != VM_PROT_ALL) {
E 24
I 24
	rv = KERN_SUCCESS;
	if (maxprot != VM_PROT_ALL)
		rv = vm_map_protect(map, *addr, *addr+size, maxprot, TRUE);
	if (rv == KERN_SUCCESS && prot != maxprot)
E 24
		rv = vm_map_protect(map, *addr, *addr+size, prot, FALSE);
D 24
		if (rv != KERN_SUCCESS) {
			(void) vm_deallocate(map, *addr, size);
			goto out;
		}
E 24
I 24
	if (rv != KERN_SUCCESS) {
		(void) vm_deallocate(map, *addr, size);
		goto out;
E 24
	}
	/*
	 * Shared memory is also shared with children.
	 */
	if (flags & MAP_SHARED) {
D 39
		rv = vm_inherit(map, *addr, size, VM_INHERIT_SHARE);
E 39
I 39
		rv = vm_map_inherit(map, *addr, *addr+size, VM_INHERIT_SHARE);
E 39
		if (rv != KERN_SUCCESS) {
			(void) vm_deallocate(map, *addr, size);
			goto out;
		}
	}
out:
#ifdef DEBUG
	if (mmapdebug & MDB_MAPIT)
		printf("vm_mmap: rv %d\n", rv);
#endif
	switch (rv) {
	case KERN_SUCCESS:
		return (0);
	case KERN_INVALID_ADDRESS:
	case KERN_NO_SPACE:
		return (ENOMEM);
	case KERN_PROTECTION_FAILURE:
		return (EACCES);
	default:
		return (EINVAL);
	}
D 39
}

/*
 * Internal bastardized version of MACHs vm_region system call.
 * Given address and size it returns map attributes as well
 * as the (locked) object mapped at that location. 
 */
I 10
int
E 10
vm_region(map, addr, size, prot, max_prot, inheritance, shared, object, objoff)
	vm_map_t	map;
	vm_offset_t	*addr;		/* IN/OUT */
	vm_size_t	*size;		/* OUT */
	vm_prot_t	*prot;		/* OUT */
	vm_prot_t	*max_prot;	/* OUT */
	vm_inherit_t	*inheritance;	/* OUT */
	boolean_t	*shared;	/* OUT */
	vm_object_t	*object;	/* OUT */
	vm_offset_t	*objoff;	/* OUT */
{
	vm_map_entry_t	tmp_entry;
	register
	vm_map_entry_t	entry;
	register
	vm_offset_t	tmp_offset;
	vm_offset_t	start;

D 3
	if (map == VM_MAP_NULL)
E 3
I 3
	if (map == NULL)
E 3
		return(KERN_INVALID_ARGUMENT);
	
	start = *addr;

	vm_map_lock_read(map);
	if (!vm_map_lookup_entry(map, start, &tmp_entry)) {
		if ((entry = tmp_entry->next) == &map->header) {
			vm_map_unlock_read(map);
		   	return(KERN_NO_SPACE);
		}
		start = entry->start;
		*addr = start;
	} else
		entry = tmp_entry;

	*prot = entry->protection;
	*max_prot = entry->max_protection;
	*inheritance = entry->inheritance;

	tmp_offset = entry->offset + (start - entry->start);
	*size = (entry->end - start);

	if (entry->is_a_map) {
		register vm_map_t share_map;
		vm_size_t share_size;

		share_map = entry->object.share_map;

		vm_map_lock_read(share_map);
		(void) vm_map_lookup_entry(share_map, tmp_offset, &tmp_entry);

		if ((share_size = (tmp_entry->end - tmp_offset)) < *size)
			*size = share_size;

		vm_object_lock(tmp_entry->object);
		*object = tmp_entry->object.vm_object;
		*objoff = tmp_entry->offset + (tmp_offset - tmp_entry->start);

		*shared = (share_map->ref_count != 1);
		vm_map_unlock_read(share_map);
	} else {
		vm_object_lock(entry->object);
		*object = entry->object.vm_object;
		*objoff = tmp_offset;

		*shared = FALSE;
	}

	vm_map_unlock_read(map);

	return(KERN_SUCCESS);
}

/*
 * Yet another bastard routine.
 */
I 10
int
E 10
vm_allocate_with_pager(map, addr, size, fitit, pager, poffset, internal)
	register vm_map_t	map;
	register vm_offset_t	*addr;
	register vm_size_t	size;
	boolean_t		fitit;
	vm_pager_t		pager;
	vm_offset_t		poffset;
	boolean_t		internal;
{
	register vm_object_t	object;
	register int		result;

D 3
	if (map == VM_MAP_NULL)
E 3
I 3
	if (map == NULL)
E 3
		return(KERN_INVALID_ARGUMENT);

	*addr = trunc_page(*addr);
	size = round_page(size);

	/*
	 *	Lookup the pager/paging-space in the object cache.
	 *	If it's not there, then create a new object and cache
	 *	it.
	 */
	object = vm_object_lookup(pager);
D 7
	vm_stat.lookups++;
E 7
I 7
	cnt.v_lookups++;
E 7
D 3
	if (object == VM_OBJECT_NULL) {
E 3
I 3
	if (object == NULL) {
E 3
		object = vm_object_allocate(size);
D 11
		vm_object_enter(object, pager);
E 11
I 11
		/*
		 * From Mike Hibler: "unnamed anonymous objects should never
		 * be on the hash list ... For now you can just change
		 * vm_allocate_with_pager to not do vm_object_enter if this
		 * is an internal object ..."
		 */
		if (!internal)
			vm_object_enter(object, pager);
E 11
	} else
D 7
		vm_stat.hits++;
	object->internal = internal;
E 7
I 7
		cnt.v_hits++;
	if (internal)
		object->flags |= OBJ_INTERNAL;
	else
		object->flags &= ~OBJ_INTERNAL;
E 7

	result = vm_map_find(map, object, poffset, addr, size, fitit);
	if (result != KERN_SUCCESS)
		vm_object_deallocate(object);
D 3
	else if (pager != vm_pager_null)
E 3
I 3
	else if (pager != NULL)
E 3
		vm_object_setpager(object, pager, (vm_offset_t) 0, TRUE);
	return(result);
}

/*
 * XXX: this routine belongs in vm_map.c.
 *
 * Returns TRUE if the range [start - end) is allocated in either
 * a single entry (single_entry == TRUE) or multiple contiguous
 * entries (single_entry == FALSE).
 *
 * start and end should be page aligned.
 */
boolean_t
vm_map_is_allocated(map, start, end, single_entry)
	vm_map_t map;
	vm_offset_t start, end;
	boolean_t single_entry;
{
	vm_map_entry_t mapent;
	register vm_offset_t nend;

	vm_map_lock_read(map);

	/*
	 * Start address not in any entry
	 */
	if (!vm_map_lookup_entry(map, start, &mapent)) {
		vm_map_unlock_read(map);
		return (FALSE);
	}
	/*
	 * Find the maximum stretch of contiguously allocated space
	 */
	nend = mapent->end;
	if (!single_entry) {
		mapent = mapent->next;
		while (mapent != &map->header && mapent->start == nend) {
			nend = mapent->end;
			mapent = mapent->next;
		}
	}

	vm_map_unlock_read(map);
	return (end <= nend);
E 39
D 4
}

#include "../vm/vm_page.h"

/*
 * Doesn't trust the COW bit in the page structure.
 * vm_fault can improperly set it.
 */
D 3
void
E 3
vm_object_pmap_force_copy(object, start, end)
	register vm_object_t	object;
	register vm_offset_t	start;
	register vm_offset_t	end;
{
	register vm_page_t	p;

D 3
	if (object == VM_OBJECT_NULL)
E 3
I 3
	if (object == NULL)
E 3
		return;

	vm_object_lock(object);
	p = (vm_page_t) queue_first(&object->memq);
	while (!queue_end(&object->memq, (queue_entry_t) p)) {
		if (start <= p->offset && p->offset < end) {
			pmap_copy_on_write(VM_PAGE_TO_PHYS(p));
			p->copy_on_write = TRUE;
		}
		p = (vm_page_t) queue_next(&p->listq);
	}
	vm_object_unlock(object);
E 4
}
E 1
