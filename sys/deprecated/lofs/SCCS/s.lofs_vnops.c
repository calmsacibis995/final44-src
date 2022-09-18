h34490
s 00000/00001/00971
d D 8.4 94/01/21 19:52:46 bostic 12 11
c copyright typo
e
s 00016/00007/00956
d D 8.3 94/01/14 08:29:20 pendry 11 10
c add pathconf entry point
e
s 00054/00209/00909
d D 8.2 94/01/05 12:30:35 pendry 10 9
c remove debug code, general cleanup.  KNF.
e
s 00002/00002/01116
d D 8.1 93/06/10 23:42:57 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00002/01113
d D 7.5 93/06/10 20:39:48 mckusick 8 7
c avoid NULL pointers in VOP_FSYNC
e
s 00012/00007/01103
d D 7.4 92/11/14 23:43:58 mckusick 7 6
c have to wait for VXLOCK to clear when trying to lock
e
s 00002/00001/01108
d D 7.3 92/10/07 17:17:52 margo 6 5
c Add argument to VOP_BMAP.
e
s 00002/00002/01107
d D 7.2 92/07/15 11:19:41 pendry 5 4
c fix reference counts in lofs_mkdir
e
s 00275/00085/00834
d D 7.1 92/07/12 14:52:47 mckusick 4 3
c move to rev 7; new location; syntactic niggles
e
s 00002/00047/00917
d D 1.3 92/07/12 10:08:40 pendry 3 2
c new vop conventions
e
s 00063/00059/00901
d D 1.2 92/06/18 15:03:51 pendry 2 1
c local variables
c fix trace messages
e
s 00960/00000/00000
d D 1.1 92/06/03 14:19:10 pendry 1 0
c date and time created 92/06/03 14:19:10 by pendry
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
D 12
 * All rights reserved.
E 12
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * $Id: lofs_vnops.c,v 1.11 1992/05/30 10:05:43 jsp Exp jsp $
 */

/*
 * Loopback Filesystem
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/buf.h>
D 4
#include <lofs/lofs.h>
E 4
I 4
#include <miscfs/lofs/lofs.h>
E 4

/*
 * Basic strategy: as usual, do as little work as possible.
 * Nothing is ever locked in the lofs'ed filesystem, all
 * locks are held in the underlying filesystems.
 */

/*
 * Save a vnode and replace with
 * the lofs'ed one
 */
#define PUSHREF(v, nd) \
{ \
	struct { struct vnode *vnp; } v; \
	v.vnp = (nd); \
	(nd) = LOFSVP(v.vnp)

/*
 * Undo the PUSHREF
 */
#define POP(v, nd) \
	\
	(nd) = v.vnp; \
}

D 10

E 10
/*
 * vp is the current namei directory
 * ndp is the name to locate in that directory...
 */
I 10
int
E 10
D 4
lofs_lookup (ap)
	struct vop_lookup_args *ap;
E 4
I 4
lofs_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_LOOKUP;
E 3
I 2
	struct vnode *dvp = ap->a_dvp;
E 2
	struct vnode *newvp;
	struct vnode *targetdvp;
	int error;
	int flag = ap->a_cnp->cn_nameiop /*& OPMASK*/;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_LOOKUP(ap->a_dvp = %x->%x, \"%s\", op = %d)\n",
		ap->a_dvp, LOFSVP(ap->a_dvp), ap->a_cnp->cn_nameptr, flag);
E 2
I 2
	printf("lofs_lookup(ap->a_dvp = %x->%x, \"%s\", op = %d)\n",
		dvp, LOFSVP(dvp), ap->a_cnp->cn_nameptr, flag);
E 2
#endif

E 10
	/*
	 * (ap->a_dvp) was locked when passed in, and it will be replaced
	 * with the target vnode, BUT that will already have been
	 * locked when (ap->a_dvp) was locked [see lofs_lock].  all that
	 * must be done here is to keep track of reference counts.
	 */
D 2
	targetdvp = LOFSVP(ap->a_dvp);
	VREF(targetdvp);
E 2
I 2
	targetdvp = LOFSVP(dvp);
	/*VREF(targetdvp);*/
E 2
D 10
#ifdef LOFS_DIAGNOSTIC
	vprint("lofs VOP_LOOKUP", targetdvp);
#endif
E 10

	/*
	 * Call lookup on the looped vnode
	 */
D 2
	error = VOP_LOOKUP(targetdvp, ap->a_vpp, ap->a_cnp);
	vrele(targetdvp);
E 2
I 2
	error = VOP_LOOKUP(targetdvp, &newvp, ap->a_cnp);
	/*vrele(targetdvp);*/
E 2

	if (error) {
		*ap->a_vpp = NULLVP;
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
		printf("VOP_LOOKUP(%x->%x) = %d\n",
			ap->a_dvp, LOFSVP(ap->a_dvp), error);
E 2
I 2
		printf("lofs_lookup(%x->%x) = %d\n", dvp, LOFSVP(dvp), error);
E 2
#endif
E 10
		return (error);
	}
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_LOOKUP(%x->%x) = OK\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_lookup(%x->%x) = OK\n", dvp, LOFSVP(dvp));
E 2
#endif
E 10

D 2
	newvp = *ap->a_vpp;
E 2
I 2
	*ap->a_vpp = newvp;
E 2

	/*
	 * If we just found a directory then make
	 * a loopback node for it and return the loopback
	 * instead of the real vnode.  Otherwise simply
	 * return the aliased directory and vnode.
	 */
	if (newvp && newvp->v_type == VDIR && flag == LOOKUP) {
D 10
#ifdef LOFS_DIAGNOSTIC
		printf("lofs_lookup: found VDIR\n");
#endif
E 10
		/*
		 * At this point, newvp is the vnode to be looped.
		 * Activate a loopback and return the looped vnode.
		 */
D 2
		return (make_lofs(ap->a_dvp->v_mount, ap->a_vpp));
E 2
I 2
		return (make_lofs(dvp->v_mount, ap->a_vpp));
E 2
	}

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("lofs_lookup: not VDIR; vrele(%x)\n", ap->a_dvp);
E 2
I 2
	printf("lofs_lookup: not VDIR\n");
E 2
#endif

E 10
	return (0);
}

/*
 * this = ni_dvp
 * ni_dvp references the locked directory.
 * ni_vp is NULL.
 */
I 10
int
E 10
D 4
lofs_mknod (ap)
	struct vop_mknod_args *ap;
E 4
I 4
lofs_mknod(ap)
	struct vop_mknod_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
E 4
{
D 3
	USES_VOP_MKNOD;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_MKNOD(vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_mknod(vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
#endif

E 10
	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);

	error = VOP_MKNOD(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap);

	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

	return (error);
}

/*
 * this = ni_dvp;
 * ni_dvp references the locked directory
 * ni_vp is NULL.
 */
I 10
int
E 10
D 4
lofs_create (ap)
	struct vop_create_args *ap;
E 4
I 4
lofs_create(ap)
	struct vop_create_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
E 4
{
D 3
	USES_VOP_CREATE;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_CREATE(ap->a_dvp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_create(ap->a_dvp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
#endif

E 10
	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);

	error = VOP_CREATE(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap);

	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_CREATE(ap->a_dvp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_create(ap->a_dvp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
#endif

E 10
	return (error);
}

I 10
int
E 10
D 4
lofs_open (ap)
	struct vop_open_args *ap;
E 4
I 4
lofs_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_OPEN;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_OPEN(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_open(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_OPEN(LOFSVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_OPEN(LOFSVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_close (ap)
	struct vop_close_args *ap;
E 4
I 4
lofs_close(ap)
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_CLOSE;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_CLOSE(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_close(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_CLOSE(LOFSVP(ap->a_vp), ap->a_fflag, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_CLOSE(LOFSVP(ap->a_vp), ap->a_fflag, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_access (ap)
	struct vop_access_args *ap;
E 4
I 4
lofs_access(ap)
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_ACCESS;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_ACCESS(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_access(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_ACCESS(LOFSVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_ACCESS(LOFSVP(ap->a_vp), ap->a_mode, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_getattr (ap)
	struct vop_getattr_args *ap;
E 4
I 4
lofs_getattr(ap)
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
D 3
	USES_VOP_GETATTR;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_GETATTR(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_getattr(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

E 10
	/*
	 * Get the stats from the underlying filesystem
	 */
	error = VOP_GETATTR(LOFSVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p);
	if (error)
		return (error);
	/*
	 * and replace the fsid field with the loopback number
	 * to preserve the namespace.
	 */
	ap->a_vap->va_fsid = ap->a_vp->v_mount->mnt_stat.f_fsid.val[0];
	return (0);
}

I 10
int
E 10
D 4
lofs_setattr (ap)
	struct vop_setattr_args *ap;
E 4
I 4
lofs_setattr(ap)
	struct vop_setattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_SETATTR;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_SETATTR(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_setattr(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_SETATTR(LOFSVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_SETATTR(LOFSVP(ap->a_vp), ap->a_vap, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_read (ap)
	struct vop_read_args *ap;
E 4
I 4
lofs_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_READ;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_READ(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_read(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_READ(LOFSVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred);
E 10
I 10
	return (VOP_READ(LOFSVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred));
E 10
}

I 10
int
E 10
D 4
lofs_write (ap)
	struct vop_write_args *ap;
E 4
I 4
lofs_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_WRITE;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_WRITE(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_write(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_WRITE(LOFSVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred);
E 10
I 10
	return (VOP_WRITE(LOFSVP(ap->a_vp), ap->a_uio, ap->a_ioflag, ap->a_cred));
E 10
}

I 10
int
E 10
D 4
lofs_ioctl (ap)
	struct vop_ioctl_args *ap;
E 4
I 4
lofs_ioctl(ap)
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
		int  a_command;
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_IOCTL;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_IOCTL(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_ioctl(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_IOCTL(LOFSVP(ap->a_vp), ap->a_command, ap->a_data, ap->a_fflag, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_IOCTL(LOFSVP(ap->a_vp), ap->a_command, ap->a_data, ap->a_fflag, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_select (ap)
	struct vop_select_args *ap;
E 4
I 4
lofs_select(ap)
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_SELECT;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_SELECT(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_select(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_SELECT(LOFSVP(ap->a_vp), ap->a_which, ap->a_fflags, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_SELECT(LOFSVP(ap->a_vp), ap->a_which, ap->a_fflags, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_mmap (ap)
	struct vop_mmap_args *ap;
E 4
I 4
lofs_mmap(ap)
	struct vop_mmap_args /* {
		struct vnode *a_vp;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_MMAP;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_MMAP(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_mmap(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_MMAP(LOFSVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_p);
E 10
I 10
	return (VOP_MMAP(LOFSVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_p));
E 10
}

I 10
int
E 10
D 4
lofs_fsync (ap)
	struct vop_fsync_args *ap;
E 4
I 4
lofs_fsync(ap)
	struct vop_fsync_args /* {
		struct vnode *a_vp;
		struct ucred *a_cred;
		int  a_waitfor;
		struct proc *a_p;
	} */ *ap;
E 4
{
I 8
	struct vnode *targetvp = LOFSVP(ap->a_vp);
E 8
I 4

E 4
D 3
	USES_VOP_FSYNC;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_FSYNC(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
D 8
	printf("lofs_fsync(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 8
I 8
	printf("lofs_fsync(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 8
E 2
#endif

E 10
D 3
	return VOP_FSYNC(LOFSVP(ap->a_vp), ap->a_fflags, ap->a_cred, ap->a_waitfor, ap->a_p);
E 3
I 3
D 8
	return VOP_FSYNC(LOFSVP(ap->a_vp), ap->a_cred, ap->a_waitfor, ap->a_p);
E 8
I 8
	if (targetvp)
D 10
		return VOP_FSYNC(targetvp, ap->a_cred, ap->a_waitfor, ap->a_p);
E 10
I 10
		return (VOP_FSYNC(targetvp, ap->a_cred, ap->a_waitfor, ap->a_p));
E 10
	return (0);
E 8
E 3
}

I 10
int
E 10
D 4
lofs_seek (ap)
	struct vop_seek_args *ap;
E 4
I 4
lofs_seek(ap)
	struct vop_seek_args /* {
		struct vnode *a_vp;
		off_t  a_oldoff;
		off_t  a_newoff;
		struct ucred *a_cred;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_SEEK;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_SEEK(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_seek(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_SEEK(LOFSVP(ap->a_vp), ap->a_oldoff, ap->a_newoff, ap->a_cred);
E 10
I 10
	return (VOP_SEEK(LOFSVP(ap->a_vp), ap->a_oldoff, ap->a_newoff, ap->a_cred));
E 10
}

I 10
int
E 10
D 4
lofs_remove (ap)
	struct vop_remove_args *ap;
E 4
I 4
lofs_remove(ap)
	struct vop_remove_args /* {
		struct vnode *a_dvp;
		struct vnode *a_vp;
		struct componentname *a_cnp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_REMOVE;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_REMOVE(ap->a_vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_remove(ap->a_vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
#endif

E 10
	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);
	PUSHREF(xvp, ap->a_vp);
	VREF(ap->a_vp);

	error = VOP_REMOVE(ap->a_dvp, ap->a_vp, ap->a_cnp);

	POP(xvp, ap->a_vp);
	vrele(ap->a_vp);
	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

	return (error);
}

/*
 * vp is this.
 * ni_dvp is the locked parent of the target.
 * ni_vp is NULL.
 */
I 10
int
E 10
D 4
lofs_link (ap)
	struct vop_link_args *ap;
E 4
I 4
lofs_link(ap)
	struct vop_link_args /* {
		struct vnode *a_vp;
		struct vnode *a_tdvp;
		struct componentname *a_cnp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_LINK;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_LINK(ap->a_tdvp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_link(ap->a_tdvp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

E 10
	PUSHREF(xdvp, ap->a_vp);
	VREF(ap->a_vp);

	error = VOP_LINK(ap->a_vp, LOFSVP(ap->a_tdvp), ap->a_cnp);

	POP(xdvp, ap->a_vp);
	vrele(ap->a_vp);

	return (error);
}

I 10
int
E 10
D 4
lofs_rename (ap)
	struct vop_rename_args *ap;
E 4
I 4
lofs_rename(ap)
	struct vop_rename_args  /* {
		struct vnode *a_fdvp;
		struct vnode *a_fvp;
		struct componentname *a_fcnp;
		struct vnode *a_tdvp;
		struct vnode *a_tvp;
		struct componentname *a_tcnp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_RENAME;
E 3
	struct vnode *fvp, *tvp;
	struct vnode *tdvp;
D 4
#if 0
E 4
I 4
#ifdef notdef
E 4
	struct vnode *fsvp, *tsvp;
#endif
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_RENAME(fdvp = %x->%x)\n", ap->a_fdvp, LOFSVP(ap->a_fdvp));
	/*printf("VOP_RENAME(tdvp = %x->%x)\n", tndp->ni_dvp, LOFSVP(tndp->ni_dvp));*/
E 2
I 2
	printf("lofs_rename(fdvp = %x->%x)\n", ap->a_fdvp, LOFSVP(ap->a_fdvp));
	/*printf("lofs_rename(tdvp = %x->%x)\n", tndp->ni_dvp, LOFSVP(tndp->ni_dvp));*/
E 2
#endif

#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch source dvp\n");
#endif
E 10
	/*
	 * Switch source directory to point to lofsed vnode
	 */
	PUSHREF(fdvp, ap->a_fdvp);
	VREF(ap->a_fdvp);

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch source vp\n");
#endif
E 10
	/*
	 * And source object if it is lofsed...
	 */
	fvp = ap->a_fvp;
	if (fvp && fvp->v_op == lofs_vnodeop_p) {
		ap->a_fvp = LOFSVP(fvp);
		VREF(ap->a_fvp);
	} else {
		fvp = 0;
	}

D 4
#if 0
E 4
I 4
#ifdef notdef
E 4
D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch source start vp\n");
#endif
E 10
	/*
	 * And source startdir object if it is lofsed...
	 */
	fsvp = fndp->ni_startdir;
	if (fsvp && fsvp->v_op == lofs_vnodeop_p) {
		fndp->ni_startdir = LOFSVP(fsvp);
		VREF(fndp->ni_startdir);
	} else {
		fsvp = 0;
	}
#endif

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch target dvp\n");
#endif
E 10
	/*
 	 * Switch target directory to point to lofsed vnode
	 */
	tdvp = ap->a_tdvp;
	if (tdvp && tdvp->v_op == lofs_vnodeop_p) {
		ap->a_tdvp = LOFSVP(tdvp);
		VREF(ap->a_tdvp);
	} else {
		tdvp = 0;
	}

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch target vp\n");
#endif
E 10
	/*
	 * And target object if it is lofsed...
	 */
	tvp = ap->a_tvp;
	if (tvp && tvp->v_op == lofs_vnodeop_p) {
		ap->a_tvp = LOFSVP(tvp);
		VREF(ap->a_tvp);
	} else {
		tvp = 0;
	}

D 4
#if 0
E 4
I 4
#ifdef notdef
E 4
D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - switch target start vp\n");
#endif
E 10
	/*
	 * And target startdir object if it is lofsed...
	 */
	tsvp = tndp->ni_startdir;
	if (tsvp && tsvp->v_op == lofs_vnodeop_p) {
		tndp->ni_startdir = LOFSVP(fsvp);
		VREF(tndp->ni_startdir);
	} else {
		tsvp = 0;
	}
#endif

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - VOP_RENAME(%x, %x, %x, %x)\n",
		ap->a_fdvp, ap->a_fvp, ap->a_tdvp, ap->a_tvp);
	vprint("ap->a_fdvp", ap->a_fdvp);
	vprint("ap->a_fvp", ap->a_fvp);
	vprint("ap->a_tdvp", ap->a_tdvp);
	if (ap->a_tvp) vprint("ap->a_tvp", ap->a_tvp);
	DELAY(16000000);
#endif

E 10
	error = VOP_RENAME(ap->a_fdvp, ap->a_fvp, ap->a_fcnp, ap->a_tdvp, ap->a_tvp, ap->a_tcnp);

	/*
	 * Put everything back...
	 */
 
D 4
#if 0
E 4
I 4
#ifdef notdef
E 4
D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore target startdir\n");
#endif
E 10

	if (tsvp) {
		if (tndp->ni_startdir)
			vrele(tndp->ni_startdir);
		tndp->ni_startdir = tsvp;
	}
#endif

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore target vp\n");
#endif

E 10
	if (tvp) {
		ap->a_tvp = tvp;
		vrele(ap->a_tvp);
	}

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore target dvp\n");
#endif

E 10
	if (tdvp) {
		ap->a_tdvp = tdvp;
		vrele(ap->a_tdvp);
	}

D 4
#if 0
E 4
I 4
#ifdef notdef
E 4
D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore source startdir\n");
#endif
E 10

	if (fsvp) {
		if (fndp->ni_startdir)
			vrele(fndp->ni_startdir);
		fndp->ni_startdir = fsvp;
	}
#endif

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore source vp\n");
#endif


E 10
	if (fvp) {
		ap->a_fvp = fvp;
		vrele(ap->a_fvp);
	}

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("lofs_rename - restore source dvp\n");
#endif

E 10
	POP(fdvp, ap->a_fdvp);
	vrele(ap->a_fdvp);

	return (error);
}

/*
 * ni_dvp is the locked (alias) parent.
 * ni_vp is NULL.
 */
I 10
int
E 10
D 4
lofs_mkdir (ap)
	struct vop_mkdir_args *ap;
E 4
I 4
lofs_mkdir(ap)
	struct vop_mkdir_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
	} */ *ap;
E 4
{
D 3
	USES_VOP_MKDIR;
E 3
	int error;
I 2
	struct vnode *dvp = ap->a_dvp;
E 2
	struct vnode *xdvp;
I 2
	struct vnode *newvp;
E 2

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_MKDIR(vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_mkdir(vp = %x->%x)\n", dvp, LOFSVP(dvp));
E 2
#endif

E 10
D 2
	xdvp = ap->a_dvp;
	ap->a_dvp = LOFSVP(xdvp);
	VREF(ap->a_dvp);
E 2
I 2
	xdvp = dvp;
	dvp = LOFSVP(xdvp);
D 5
	/*VREF(dvp);*/
E 5
I 5
	VREF(dvp);
E 5
E 2

D 2
	error = VOP_MKDIR(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap);
E 2
I 2
	error = VOP_MKDIR(dvp, &newvp, ap->a_cnp, ap->a_vap);
E 2

	if (error) {
D 2
		vrele(xdvp);
E 2
I 2
		*ap->a_vpp = NULLVP;
D 5
		/*vrele(xdvp);*/
E 5
I 5
		vrele(xdvp);
E 5
E 2
		return (error);
	}

	/*
	 * Make a new lofs node
	 */
D 2
	VREF(ap->a_dvp); 
E 2
I 2
	/*VREF(dvp);*/
E 2

D 2
	error = make_lofs(ap->a_dvp->v_mount, ap->a_vpp);
E 2
I 2
	error = make_lofs(dvp->v_mount, &newvp);
E 2

D 2
	vrele(xdvp);
	vrele(xdvp);
E 2
I 2
	*ap->a_vpp = newvp;
E 2

	return (error);
}

/*
 * ni_dvp is the locked parent.
 * ni_vp is the entry to be removed.
 */
I 10
int
E 10
D 4
lofs_rmdir (ap)
	struct vop_rmdir_args *ap;
E 4
I 4
lofs_rmdir(ap)
	struct vop_rmdir_args /* {
		struct vnode *a_dvp;
		struct vnode *a_vp;
		struct componentname *a_cnp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_RMDIR;
E 3
I 2
	struct vnode *vp = ap->a_vp;
	struct vnode *dvp = ap->a_dvp;
E 2
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_RMDIR(ap->a_vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
E 2
I 2
	printf("lofs_rmdir(dvp = %x->%x)\n", dvp, LOFSVP(dvp));
E 2
#endif

E 10
D 2
	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);
	PUSHREF(xvp, ap->a_vp);
	VREF(ap->a_vp);
E 2
I 2
	PUSHREF(xdvp, dvp);
	VREF(dvp);
	PUSHREF(xvp, vp);
	VREF(vp);
E 2

D 2
	error = VOP_RMDIR(ap->a_dvp, ap->a_vp, ap->a_cnp);
E 2
I 2
	error = VOP_RMDIR(dvp, vp, ap->a_cnp);
E 2

D 2
	POP(xvp, ap->a_vp);
	vrele(ap->a_vp);
	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);
E 2
I 2
	POP(xvp, vp);
	vrele(vp);
	POP(xdvp, dvp);
	vrele(dvp);
E 2

	return (error);
}

/*
 * ni_dvp is the locked parent.
 * ni_vp is NULL.
 */
I 10
int
E 10
D 4
lofs_symlink (ap)
	struct vop_symlink_args *ap;
E 4
I 4
lofs_symlink(ap)
	struct vop_symlink_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
		struct vattr *a_vap;
		char *a_target;
	} */ *ap;
E 4
{
D 3
	USES_VOP_SYMLINK;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
	printf("VOP_SYMLINK(vp = %x->%x)\n", ap->a_dvp, LOFSVP(ap->a_dvp));
#endif

E 10
	PUSHREF(xdvp, ap->a_dvp);
	VREF(ap->a_dvp);

	error = VOP_SYMLINK(ap->a_dvp, ap->a_vpp, ap->a_cnp, ap->a_vap, ap->a_target);

	POP(xdvp, ap->a_dvp);
	vrele(ap->a_dvp);

	return (error);
}

I 10
int
E 10
D 4
lofs_readdir (ap)
	struct vop_readdir_args *ap;
E 4
I 4
lofs_readdir(ap)
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_READDIR;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_READDIR(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_readdir(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

D 3
	return VOP_READDIR(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred, ap->a_eofflagp);
E 3
I 3
	return VOP_READDIR(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred);
E 10
I 10
	return (VOP_READDIR(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred));
E 10
E 3
}

I 10
int
E 10
D 4
lofs_readlink (ap)
	struct vop_readlink_args *ap;
E 4
I 4
lofs_readlink(ap)
	struct vop_readlink_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_READLINK;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_READLINK(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_readlink(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

	return VOP_READLINK(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred);
E 10
I 10
	return (VOP_READLINK(LOFSVP(ap->a_vp), ap->a_uio, ap->a_cred));
E 10
}

/*
 * Anyone's guess...
 */
I 10
int
E 10
D 4
lofs_abortop (ap)
	struct vop_abortop_args *ap;
E 4
I 4
lofs_abortop(ap)
	struct vop_abortop_args /* {
		struct vnode *a_dvp;
		struct componentname *a_cnp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_ABORTOP;
E 3
	int error;

	PUSHREF(xdvp, ap->a_dvp);

	error = VOP_ABORTOP(ap->a_dvp, ap->a_cnp);

	POP(xdvp, ap->a_dvp);

	return (error);
}

I 10
int
E 10
D 4
lofs_inactive (ap)
	struct vop_inactive_args *ap;
E 4
I 4
lofs_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_INACTIVE;
E 3
	struct vnode *targetvp = LOFSVP(ap->a_vp);
I 4

E 4
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_INACTIVE(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
I 2
	printf("lofs_inactive(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
#endif

E 10
#ifdef DIAGNOSTIC
	{ extern int prtactive;
	if (prtactive && ap->a_vp->v_usecount != 0)
		vprint("lofs_inactive: pushing active", ap->a_vp);
	}
#endif

	if (targetvp) {
		vrele(targetvp);
		LOFSP(ap->a_vp)->a_lofsvp = 0;
	}
}

I 10
int
E 10
D 4
lofs_reclaim (ap)
	struct vop_reclaim_args *ap;
E 4
I 4
lofs_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_RECLAIM;
E 3
	struct vnode *targetvp;
I 4

E 4
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_RECLAIM(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_reclaim(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif
E 10
	remque(LOFSP(ap->a_vp));
	targetvp = LOFSVP(ap->a_vp);
	if (targetvp) {
		printf("lofs: delayed vrele of %x\n", targetvp);
		vrele(targetvp);	/* XXX should never happen */
	}
	FREE(ap->a_vp->v_data, M_TEMP);
	ap->a_vp->v_data = 0;
	return (0);
}

I 10
int
E 10
D 4
lofs_lock (ap)
	struct vop_lock_args *ap;
E 4
I 4
lofs_lock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_LOCK;
E 3
	int error;
D 7
	struct vnode *targetvp = LOFSVP(ap->a_vp);
E 7
I 7
	register struct vnode *vp = ap->a_vp;
	struct vnode *targetvp;
E 7

I 7
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
	}
	if (vp->v_tag == VT_NON)
		return (ENOENT);
	targetvp = LOFSVP(ap->a_vp);

E 7
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_LOCK(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
I 2
	printf("lofs_lock(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
	/*vprint("lofs_lock ap->a_vp", ap->a_vp);
	if (targetvp)
		vprint("lofs_lock ->ap->a_vp", targetvp);
	else
		printf("lofs_lock ->ap->a_vp = NIL\n");*/
#endif

E 10
D 7
	if (targetvp) {
		error = VOP_LOCK(targetvp);
		if (error)
			return (error);
	}

E 7
I 7
	if (targetvp && (error = VOP_LOCK(targetvp)))
		return (error);
E 7
	return (0);
}

I 10
int
E 10
D 4
lofs_unlock (ap)
	struct vop_unlock_args *ap;
E 4
I 4
lofs_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_UNLOCK;
E 3
	struct vnode *targetvp = LOFSVP(ap->a_vp);

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_UNLOCK(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
I 2
	printf("lofs_unlock(ap->a_vp = %x->%x)\n", ap->a_vp, targetvp);
E 2
#endif

E 10
	if (targetvp)
		return (VOP_UNLOCK(targetvp));
	return (0);
}

I 10
int
E 10
D 4
lofs_bmap (ap)
	struct vop_bmap_args *ap;
E 4
I 4
lofs_bmap(ap)
	struct vop_bmap_args /* {
		struct vnode *a_vp;
		daddr_t  a_bn;
		struct vnode **a_vpp;
		daddr_t *a_bnp;
I 6
		int *a_runp;
E 6
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_BMAP;
E 3
D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_BMAP(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
I 2
	printf("lofs_bmap(ap->a_vp = %x->%x)\n", ap->a_vp, LOFSVP(ap->a_vp));
E 2
#endif

D 6
	return VOP_BMAP(LOFSVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp);
E 6
I 6
	return VOP_BMAP(LOFSVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp, ap->a_runp);
E 10
I 10
	return (VOP_BMAP(LOFSVP(ap->a_vp), ap->a_bn, ap->a_vpp, ap->a_bnp, ap->a_runp));
E 10
E 6
}

I 10
int
E 10
D 4
lofs_strategy (ap)
	struct vop_strategy_args *ap;
E 4
I 4
lofs_strategy(ap)
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
E 4
{
D 3
	USES_VOP_STRATEGY;
E 3
	int error;

D 10
#ifdef LOFS_DIAGNOSTIC
D 2
	printf("VOP_STRATEGY(vp = %x->%x)\n", ap->a_bp->b_vp, LOFSVP(ap->a_bp->b_vp));
E 2
I 2
	printf("lofs_strategy(vp = %x->%x)\n", ap->a_bp->b_vp, LOFSVP(ap->a_bp->b_vp));
E 2
#endif

E 10
	PUSHREF(vp, ap->a_bp->b_vp);

	error = VOP_STRATEGY(ap->a_bp);

	POP(vp, ap->a_bp->b_vp);

	return (error);
}

I 10
int
E 10
D 4
lofs_print (ap)
	struct vop_print_args *ap;
E 4
I 4
lofs_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_PRINT;
E 3
	struct vnode *targetvp = LOFSVP(ap->a_vp);
	printf("tag VT_LOFS ref ");
	if (targetvp)
		return (VOP_PRINT(targetvp));
	printf("NULLVP\n");
	return (0);
}

I 10
int
E 10
D 4
lofs_islocked (ap)
	struct vop_islocked_args *ap;
E 4
I 4
lofs_islocked(ap)
	struct vop_islocked_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_ISLOCKED;
E 3
	struct vnode *targetvp = LOFSVP(ap->a_vp);
	if (targetvp)
		return (VOP_ISLOCKED(targetvp));
	return (0);
}

I 10
int
I 11
lofs_pathconf(ap)
	struct vop_pathconf_args *ap;
{

	return (VOP_PATHCONF(LOFSVP(ap->a_vp), ap->a_name, ap->a_retval));
}

int
E 11
E 10
D 4
lofs_advlock (ap)
	struct vop_advlock_args *ap;
E 4
I 4
lofs_advlock(ap)
	struct vop_advlock_args /* {
		struct vnode *a_vp;
		caddr_t  a_id;
		int  a_op;
		struct flock *a_fl;
		int  a_flags;
	} */ *ap;
E 4
{
I 4

E 4
D 3
	USES_VOP_ADVLOCK;
E 3
D 10
	return VOP_ADVLOCK(LOFSVP(ap->a_vp), ap->a_id, ap->a_op, ap->a_fl, ap->a_flags);
E 10
I 10
	return (VOP_ADVLOCK(LOFSVP(ap->a_vp), ap->a_id, ap->a_op, ap->a_fl, ap->a_flags));
E 10
}

/*
 * LOFS directory offset lookup.
 * Currently unsupported.
 */
I 10
int
E 10
D 4
lofs_blkatoff (ap)
	struct vop_blkatoff_args *ap;
E 4
I 4
lofs_blkatoff(ap)
	struct vop_blkatoff_args /* {
		struct vnode *a_vp;
		off_t a_offset;
		char **a_res;
		struct buf **a_bpp;
	} */ *ap;
E 4
{

	return (EOPNOTSUPP);
}

/*
D 3
 * LOFS flat namespace lookup.
 * Currently unsupported.
 */
lofs_vget (ap)
	struct vop_vget_args *ap;
{

	return (EOPNOTSUPP);
}

/*
E 3
 * LOFS flat namespace allocation.
 * Currently unsupported.
 */
I 10
int
E 10
D 4
lofs_valloc (ap)
	struct vop_valloc_args *ap;
E 4
I 4
lofs_valloc(ap)
	struct vop_valloc_args /* {
		struct vnode *a_pvp;
		int a_mode;
		struct ucred *a_cred;
		struct vnode **a_vpp;
	} */ *ap;
E 4
{

	return (EOPNOTSUPP);
}

/*
 * LOFS flat namespace free.
 * Currently unsupported.
 */
/*void*/
I 10
int
E 10
D 4
lofs_vfree (ap)
	struct vop_vfree_args *ap;
E 4
I 4
lofs_vfree(ap)
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
E 4
{

D 4
	return;
E 4
I 4
	return (0);
E 4
}

/*
 * LOFS file truncation.
 */
I 10
int
E 10
D 4
lofs_truncate (ap)
	struct vop_truncate_args *ap;
E 4
I 4
lofs_truncate(ap)
	struct vop_truncate_args /* {
		struct vnode *a_vp;
		off_t a_length;
		int a_flags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
E 4
{

	/* Use lofs_setattr */
	printf("lofs_truncate: need to implement!!");
	return (EOPNOTSUPP);
}

/*
 * LOFS update.
 */
I 10
int
E 10
D 4
lofs_update (ap)
	struct vop_update_args *ap;
E 4
I 4
lofs_update(ap)
	struct vop_update_args /* {
		struct vnode *a_vp;
		struct timeval *a_ta;
		struct timeval *a_tm;
		int a_waitfor;
	} */ *ap;
E 4
{

	/* Use lofs_setattr */
	printf("lofs_update: need to implement!!");
	return (EOPNOTSUPP);
}

/*
 * LOFS bwrite
 */
I 10
int
E 10
D 4
lofs_bwrite (ap)
	struct vop_bwrite_args *ap;
E 4
I 4
lofs_bwrite(ap)
	struct vop_bwrite_args /* {
		struct buf *a_bp;
	} */ *ap;
E 4
{
I 4

E 4
	return (EOPNOTSUPP);
}

/*
 * Global vfs data structures for ufs
 */
int (**lofs_vnodeop_p)();
struct vnodeopv_entry_desc lofs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, lofs_lookup },		/* lookup */
	{ &vop_create_desc, lofs_create },		/* create */
	{ &vop_mknod_desc, lofs_mknod },		/* mknod */
D 11
	{ &vop_open_desc, lofs_open },		/* open */
E 11
I 11
	{ &vop_open_desc, lofs_open },			/* open */
E 11
	{ &vop_close_desc, lofs_close },		/* close */
	{ &vop_access_desc, lofs_access },		/* access */
	{ &vop_getattr_desc, lofs_getattr },		/* getattr */
	{ &vop_setattr_desc, lofs_setattr },		/* setattr */
D 11
	{ &vop_read_desc, lofs_read },		/* read */
E 11
I 11
	{ &vop_read_desc, lofs_read },			/* read */
E 11
	{ &vop_write_desc, lofs_write },		/* write */
	{ &vop_ioctl_desc, lofs_ioctl },		/* ioctl */
	{ &vop_select_desc, lofs_select },		/* select */
D 11
	{ &vop_mmap_desc, lofs_mmap },		/* mmap */
E 11
I 11
	{ &vop_mmap_desc, lofs_mmap },			/* mmap */
E 11
	{ &vop_fsync_desc, lofs_fsync },		/* fsync */
D 11
	{ &vop_seek_desc, lofs_seek },		/* seek */
E 11
I 11
	{ &vop_seek_desc, lofs_seek },			/* seek */
E 11
	{ &vop_remove_desc, lofs_remove },		/* remove */
D 11
	{ &vop_link_desc, lofs_link },		/* link */
E 11
I 11
	{ &vop_link_desc, lofs_link },			/* link */
E 11
	{ &vop_rename_desc, lofs_rename },		/* rename */
	{ &vop_mkdir_desc, lofs_mkdir },		/* mkdir */
	{ &vop_rmdir_desc, lofs_rmdir },		/* rmdir */
	{ &vop_symlink_desc, lofs_symlink },		/* symlink */
	{ &vop_readdir_desc, lofs_readdir },		/* readdir */
	{ &vop_readlink_desc, lofs_readlink },		/* readlink */
	{ &vop_abortop_desc, lofs_abortop },		/* abortop */
	{ &vop_inactive_desc, lofs_inactive },		/* inactive */
	{ &vop_reclaim_desc, lofs_reclaim },		/* reclaim */
D 11
	{ &vop_lock_desc, lofs_lock },		/* lock */
E 11
I 11
	{ &vop_lock_desc, lofs_lock },			/* lock */
E 11
	{ &vop_unlock_desc, lofs_unlock },		/* unlock */
D 11
	{ &vop_bmap_desc, lofs_bmap },		/* bmap */
E 11
I 11
	{ &vop_bmap_desc, lofs_bmap },			/* bmap */
E 11
	{ &vop_strategy_desc, lofs_strategy },		/* strategy */
	{ &vop_print_desc, lofs_print },		/* print */
	{ &vop_islocked_desc, lofs_islocked },		/* islocked */
I 11
	{ &vop_pathconf_desc, lofs_pathconf },		/* pathconf */
E 11
	{ &vop_advlock_desc, lofs_advlock },		/* advlock */
	{ &vop_blkatoff_desc, lofs_blkatoff },		/* blkatoff */
D 3
	{ &vop_vget_desc, lofs_vget },		/* vget */
E 3
	{ &vop_valloc_desc, lofs_valloc },		/* valloc */
	{ &vop_vfree_desc, lofs_vfree },		/* vfree */
	{ &vop_truncate_desc, lofs_truncate },		/* truncate */
	{ &vop_update_desc, lofs_update },		/* update */
	{ &vop_bwrite_desc, lofs_bwrite },		/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc lofs_vnodeop_opv_desc =
	{ &lofs_vnodeop_p, lofs_vnodeop_entries };
E 1
