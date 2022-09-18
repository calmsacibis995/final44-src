h23828
s 00530/00472/00301
d D 7.4 92/07/03 01:33:44 bostic 4 3
c new inline structure (avoids use of USES)
e
s 00010/00014/00763
d D 7.3 92/06/25 12:59:25 mckusick 3 2
c FSYNC no longer takes fflags; READDIR no longer takes eofflags;
c INACTIVE no longer takes a proc pointer; truncate takes an off_t
e
s 00110/00110/00667
d D 7.2 92/06/25 12:56:38 mckusick 2 1
c eliminate excess spaces
e
s 00777/00000/00000
d D 7.1 92/06/24 15:44:01 mckusick 1 0
c date and time created 92/06/24 15:44:01 by mckusick
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * This file is produced by the script /sys/kern/vnode_if.sh.
 * Do not modify anything in here by hand.
E 4
 *
D 4
 * %sccs.include.redist.c%
 *
E 4
 *	%W% (Berkeley) %G%
 */
D 4

/*
 * This file should be automatically generated from a corresponding .int file.
 */

E 4
I 4
extern struct vnodeop_desc vop_default_desc;
E 4
struct vop_lookup_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode ** a_vpp;
	struct componentname * a_cnp;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode **a_vpp;
	struct componentname *a_cnp;
E 2
};
extern struct vnodeop_desc vop_lookup_desc;
D 4
#define USES_VOP_LOOKUP struct vop_lookup_args vop_lookup_a
#define VOP_LOOKUP(A0,A1,A2) \
		( vop_lookup_a.a_desc = VDESC(vop_lookup), \
		vop_lookup_a.a_dvp=(A0), \
		vop_lookup_a.a_vpp=(A1), \
		vop_lookup_a.a_cnp=(A2), \
		(VCALL((A0),VOFFSET(vop_lookup),&vop_lookup_a)))
E 4
I 4
static inline int VOP_LOOKUP(dvp, vpp, cnp)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
{
	struct vop_lookup_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_lookup);
	a.a_dvp = dvp;
	a.a_vpp = vpp;
	a.a_cnp = cnp;
	return (VCALL(dvp, VOFFSET(vop_lookup), &a));
}
E 4
struct vop_create_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode ** a_vpp;
	struct componentname * a_cnp;
	struct vattr * a_vap;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode **a_vpp;
	struct componentname *a_cnp;
	struct vattr *a_vap;
E 2
};
extern struct vnodeop_desc vop_create_desc;
D 4
#define USES_VOP_CREATE struct vop_create_args vop_create_a
#define VOP_CREATE(A0,A1,A2,A3) \
		( vop_create_a.a_desc = VDESC(vop_create), \
		vop_create_a.a_dvp=(A0), \
		vop_create_a.a_vpp=(A1), \
		vop_create_a.a_cnp=(A2), \
		vop_create_a.a_vap=(A3), \
		(VCALL((A0),VOFFSET(vop_create),&vop_create_a)))
E 4
I 4
static inline int VOP_CREATE(dvp, vpp, cnp, vap)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct vattr *vap;
{
	struct vop_create_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_create);
	a.a_dvp = dvp;
	a.a_vpp = vpp;
	a.a_cnp = cnp;
	a.a_vap = vap;
	return (VCALL(dvp, VOFFSET(vop_create), &a));
}
E 4
struct vop_mknod_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode ** a_vpp;
	struct componentname * a_cnp;
	struct vattr * a_vap;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode **a_vpp;
	struct componentname *a_cnp;
	struct vattr *a_vap;
E 2
};
extern struct vnodeop_desc vop_mknod_desc;
D 4
#define USES_VOP_MKNOD struct vop_mknod_args vop_mknod_a
#define VOP_MKNOD(A0,A1,A2,A3) \
		( vop_mknod_a.a_desc = VDESC(vop_mknod), \
		vop_mknod_a.a_dvp=(A0), \
		vop_mknod_a.a_vpp=(A1), \
		vop_mknod_a.a_cnp=(A2), \
		vop_mknod_a.a_vap=(A3), \
		(VCALL((A0),VOFFSET(vop_mknod),&vop_mknod_a)))
E 4
I 4
static inline int VOP_MKNOD(dvp, vpp, cnp, vap)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct vattr *vap;
{
	struct vop_mknod_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_mknod);
	a.a_dvp = dvp;
	a.a_vpp = vpp;
	a.a_cnp = cnp;
	a.a_vap = vap;
	return (VCALL(dvp, VOFFSET(vop_mknod), &a));
}
E 4
struct vop_open_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	int  a_mode;
E 4
I 4
	int a_mode;
E 4
D 2
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_open_desc;
D 4
#define USES_VOP_OPEN struct vop_open_args vop_open_a
#define VOP_OPEN(A0,A1,A2,A3) \
		( vop_open_a.a_desc = VDESC(vop_open), \
		vop_open_a.a_vp=(A0), \
		vop_open_a.a_mode=(A1), \
		vop_open_a.a_cred=(A2), \
		vop_open_a.a_p=(A3), \
		(VCALL((A0),VOFFSET(vop_open),&vop_open_a)))
E 4
I 4
static inline int VOP_OPEN(vp, mode, cred, p)
	struct vnode *vp;
	int mode;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_open_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_open);
	a.a_vp = vp;
	a.a_mode = mode;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_open), &a));
}
E 4
struct vop_close_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	int  a_fflag;
E 4
I 4
	int a_fflag;
E 4
D 2
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_close_desc;
D 4
#define USES_VOP_CLOSE struct vop_close_args vop_close_a
#define VOP_CLOSE(A0,A1,A2,A3) \
		( vop_close_a.a_desc = VDESC(vop_close), \
		vop_close_a.a_vp=(A0), \
		vop_close_a.a_fflag=(A1), \
		vop_close_a.a_cred=(A2), \
		vop_close_a.a_p=(A3), \
		(VCALL((A0),VOFFSET(vop_close),&vop_close_a)))
E 4
I 4
static inline int VOP_CLOSE(vp, fflag, cred, p)
	struct vnode *vp;
	int fflag;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_close_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_close);
	a.a_vp = vp;
	a.a_fflag = fflag;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_close), &a));
}
E 4
struct vop_access_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	int  a_mode;
E 4
I 4
	int a_mode;
E 4
D 2
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_access_desc;
D 4
#define USES_VOP_ACCESS struct vop_access_args vop_access_a
#define VOP_ACCESS(A0,A1,A2,A3) \
		( vop_access_a.a_desc = VDESC(vop_access), \
		vop_access_a.a_vp=(A0), \
		vop_access_a.a_mode=(A1), \
		vop_access_a.a_cred=(A2), \
		vop_access_a.a_p=(A3), \
		(VCALL((A0),VOFFSET(vop_access),&vop_access_a)))
E 4
I 4
static inline int VOP_ACCESS(vp, mode, cred, p)
	struct vnode *vp;
	int mode;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_access_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_access);
	a.a_vp = vp;
	a.a_mode = mode;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_access), &a));
}
E 4
struct vop_getattr_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct vattr * a_vap;
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct vnode *a_vp;
	struct vattr *a_vap;
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_getattr_desc;
D 4
#define USES_VOP_GETATTR struct vop_getattr_args vop_getattr_a
#define VOP_GETATTR(A0,A1,A2,A3) \
		( vop_getattr_a.a_desc = VDESC(vop_getattr), \
		vop_getattr_a.a_vp=(A0), \
		vop_getattr_a.a_vap=(A1), \
		vop_getattr_a.a_cred=(A2), \
		vop_getattr_a.a_p=(A3), \
		(VCALL((A0),VOFFSET(vop_getattr),&vop_getattr_a)))
E 4
I 4
static inline int VOP_GETATTR(vp, vap, cred, p)
	struct vnode *vp;
	struct vattr *vap;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_getattr_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_getattr);
	a.a_vp = vp;
	a.a_vap = vap;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_getattr), &a));
}
E 4
struct vop_setattr_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct vattr * a_vap;
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct vnode *a_vp;
	struct vattr *a_vap;
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_setattr_desc;
D 4
#define USES_VOP_SETATTR struct vop_setattr_args vop_setattr_a
#define VOP_SETATTR(A0,A1,A2,A3) \
		( vop_setattr_a.a_desc = VDESC(vop_setattr), \
		vop_setattr_a.a_vp=(A0), \
		vop_setattr_a.a_vap=(A1), \
		vop_setattr_a.a_cred=(A2), \
		vop_setattr_a.a_p=(A3), \
		(VCALL((A0),VOFFSET(vop_setattr),&vop_setattr_a)))
E 4
I 4
static inline int VOP_SETATTR(vp, vap, cred, p)
	struct vnode *vp;
	struct vattr *vap;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_setattr_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_setattr);
	a.a_vp = vp;
	a.a_vap = vap;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_setattr), &a));
}
E 4
struct vop_read_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct uio * a_uio;
E 2
I 2
	struct vnode *a_vp;
	struct uio *a_uio;
E 2
D 4
	int  a_ioflag;
E 4
I 4
	int a_ioflag;
E 4
D 2
	struct ucred * a_cred;
E 2
I 2
	struct ucred *a_cred;
E 2
};
extern struct vnodeop_desc vop_read_desc;
D 4
#define USES_VOP_READ struct vop_read_args vop_read_a
#define VOP_READ(A0,A1,A2,A3) \
		( vop_read_a.a_desc = VDESC(vop_read), \
		vop_read_a.a_vp=(A0), \
		vop_read_a.a_uio=(A1), \
		vop_read_a.a_ioflag=(A2), \
		vop_read_a.a_cred=(A3), \
		(VCALL((A0),VOFFSET(vop_read),&vop_read_a)))
E 4
I 4
static inline int VOP_READ(vp, uio, ioflag, cred)
	struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{
	struct vop_read_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_read);
	a.a_vp = vp;
	a.a_uio = uio;
	a.a_ioflag = ioflag;
	a.a_cred = cred;
	return (VCALL(vp, VOFFSET(vop_read), &a));
}
E 4
struct vop_write_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct uio * a_uio;
E 2
I 2
	struct vnode *a_vp;
	struct uio *a_uio;
E 2
D 4
	int  a_ioflag;
E 4
I 4
	int a_ioflag;
E 4
D 2
	struct ucred * a_cred;
E 2
I 2
	struct ucred *a_cred;
E 2
};
extern struct vnodeop_desc vop_write_desc;
D 4
#define USES_VOP_WRITE struct vop_write_args vop_write_a
#define VOP_WRITE(A0,A1,A2,A3) \
		( vop_write_a.a_desc = VDESC(vop_write), \
		vop_write_a.a_vp=(A0), \
		vop_write_a.a_uio=(A1), \
		vop_write_a.a_ioflag=(A2), \
		vop_write_a.a_cred=(A3), \
		(VCALL((A0),VOFFSET(vop_write),&vop_write_a)))
E 4
I 4
static inline int VOP_WRITE(vp, uio, ioflag, cred)
	struct vnode *vp;
	struct uio *uio;
	int ioflag;
	struct ucred *cred;
{
	struct vop_write_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_write);
	a.a_vp = vp;
	a.a_uio = uio;
	a.a_ioflag = ioflag;
	a.a_cred = cred;
	return (VCALL(vp, VOFFSET(vop_write), &a));
}
E 4
struct vop_ioctl_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	int  a_command;
	caddr_t  a_data;
	int  a_fflag;
E 4
I 4
	int a_command;
	caddr_t a_data;
	int a_fflag;
E 4
D 2
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_ioctl_desc;
D 4
#define USES_VOP_IOCTL struct vop_ioctl_args vop_ioctl_a
#define VOP_IOCTL(A0,A1,A2,A3,A4,A5) \
		( vop_ioctl_a.a_desc = VDESC(vop_ioctl), \
		vop_ioctl_a.a_vp=(A0), \
		vop_ioctl_a.a_command=(A1), \
		vop_ioctl_a.a_data=(A2), \
		vop_ioctl_a.a_fflag=(A3), \
		vop_ioctl_a.a_cred=(A4), \
		vop_ioctl_a.a_p=(A5), \
		(VCALL((A0),VOFFSET(vop_ioctl),&vop_ioctl_a)))
E 4
I 4
static inline int VOP_IOCTL(vp, command, data, fflag, cred, p)
	struct vnode *vp;
	int command;
	caddr_t data;
	int fflag;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_ioctl_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_ioctl);
	a.a_vp = vp;
	a.a_command = command;
	a.a_data = data;
	a.a_fflag = fflag;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_ioctl), &a));
}
E 4
struct vop_select_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	int  a_which;
	int  a_fflags;
E 4
I 4
	int a_which;
	int a_fflags;
E 4
D 2
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_select_desc;
D 4
#define USES_VOP_SELECT struct vop_select_args vop_select_a
#define VOP_SELECT(A0,A1,A2,A3,A4) \
		( vop_select_a.a_desc = VDESC(vop_select), \
		vop_select_a.a_vp=(A0), \
		vop_select_a.a_which=(A1), \
		vop_select_a.a_fflags=(A2), \
		vop_select_a.a_cred=(A3), \
		vop_select_a.a_p=(A4), \
		(VCALL((A0),VOFFSET(vop_select),&vop_select_a)))
E 4
I 4
static inline int VOP_SELECT(vp, which, fflags, cred, p)
	struct vnode *vp;
	int which;
	int fflags;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_select_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_select);
	a.a_vp = vp;
	a.a_which = which;
	a.a_fflags = fflags;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_select), &a));
}
E 4
struct vop_mmap_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	int  a_fflags;
E 4
I 4
	int a_fflags;
E 4
D 2
	struct ucred * a_cred;
	struct proc * a_p;
E 2
I 2
	struct ucred *a_cred;
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_mmap_desc;
D 4
#define USES_VOP_MMAP struct vop_mmap_args vop_mmap_a
#define VOP_MMAP(A0,A1,A2,A3) \
		( vop_mmap_a.a_desc = VDESC(vop_mmap), \
		vop_mmap_a.a_vp=(A0), \
		vop_mmap_a.a_fflags=(A1), \
		vop_mmap_a.a_cred=(A2), \
		vop_mmap_a.a_p=(A3), \
		(VCALL((A0),VOFFSET(vop_mmap),&vop_mmap_a)))
E 4
I 4
static inline int VOP_MMAP(vp, fflags, cred, p)
	struct vnode *vp;
	int fflags;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_mmap_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_mmap);
	a.a_vp = vp;
	a.a_fflags = fflags;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_mmap), &a));
}
E 4
struct vop_fsync_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 3
	int  a_fflags;
E 3
D 2
	struct ucred * a_cred;
E 2
I 2
	struct ucred *a_cred;
E 2
D 4
	int  a_waitfor;
E 4
I 4
	int a_waitfor;
E 4
D 2
	struct proc * a_p;
E 2
I 2
	struct proc *a_p;
E 2
};
extern struct vnodeop_desc vop_fsync_desc;
D 4
#define USES_VOP_FSYNC struct vop_fsync_args vop_fsync_a
D 3
#define VOP_FSYNC(A0,A1,A2,A3,A4) \
E 3
I 3
#define VOP_FSYNC(A0,A1,A2,A3) \
E 3
		( vop_fsync_a.a_desc = VDESC(vop_fsync), \
		vop_fsync_a.a_vp=(A0), \
D 3
		vop_fsync_a.a_fflags=(A1), \
		vop_fsync_a.a_cred=(A2), \
		vop_fsync_a.a_waitfor=(A3), \
		vop_fsync_a.a_p=(A4), \
E 3
I 3
		vop_fsync_a.a_cred=(A1), \
		vop_fsync_a.a_waitfor=(A2), \
		vop_fsync_a.a_p=(A3), \
E 3
		(VCALL((A0),VOFFSET(vop_fsync),&vop_fsync_a)))
E 4
I 4
static inline int VOP_FSYNC(vp, cred, waitfor, p)
	struct vnode *vp;
	struct ucred *cred;
	int waitfor;
	struct proc *p;
{
	struct vop_fsync_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_fsync);
	a.a_vp = vp;
	a.a_cred = cred;
	a.a_waitfor = waitfor;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_fsync), &a));
}
E 4
struct vop_seek_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	off_t  a_oldoff;
	off_t  a_newoff;
E 4
I 4
	off_t a_oldoff;
	off_t a_newoff;
E 4
D 2
	struct ucred * a_cred;
E 2
I 2
	struct ucred *a_cred;
E 2
};
extern struct vnodeop_desc vop_seek_desc;
D 4
#define USES_VOP_SEEK struct vop_seek_args vop_seek_a
#define VOP_SEEK(A0,A1,A2,A3) \
		( vop_seek_a.a_desc = VDESC(vop_seek), \
		vop_seek_a.a_vp=(A0), \
		vop_seek_a.a_oldoff=(A1), \
		vop_seek_a.a_newoff=(A2), \
		vop_seek_a.a_cred=(A3), \
		(VCALL((A0),VOFFSET(vop_seek),&vop_seek_a)))
E 4
I 4
static inline int VOP_SEEK(vp, oldoff, newoff, cred)
	struct vnode *vp;
	off_t oldoff;
	off_t newoff;
	struct ucred *cred;
{
	struct vop_seek_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_seek);
	a.a_vp = vp;
	a.a_oldoff = oldoff;
	a.a_newoff = newoff;
	a.a_cred = cred;
	return (VCALL(vp, VOFFSET(vop_seek), &a));
}
E 4
struct vop_remove_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode * a_vp;
	struct componentname * a_cnp;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode *a_vp;
	struct componentname *a_cnp;
E 2
};
extern struct vnodeop_desc vop_remove_desc;
D 4
#define USES_VOP_REMOVE struct vop_remove_args vop_remove_a
#define VOP_REMOVE(A0,A1,A2) \
		( vop_remove_a.a_desc = VDESC(vop_remove), \
		vop_remove_a.a_dvp=(A0), \
		vop_remove_a.a_vp=(A1), \
		vop_remove_a.a_cnp=(A2), \
		(VCALL((A0),VOFFSET(vop_remove),&vop_remove_a)))
E 4
I 4
static inline int VOP_REMOVE(dvp, vp, cnp)
	struct vnode *dvp;
	struct vnode *vp;
	struct componentname *cnp;
{
	struct vop_remove_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_remove);
	a.a_dvp = dvp;
	a.a_vp = vp;
	a.a_cnp = cnp;
	return (VCALL(dvp, VOFFSET(vop_remove), &a));
}
E 4
struct vop_link_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct vnode * a_tdvp;
	struct componentname * a_cnp;
E 2
I 2
	struct vnode *a_vp;
	struct vnode *a_tdvp;
	struct componentname *a_cnp;
E 2
};
extern struct vnodeop_desc vop_link_desc;
D 4
#define USES_VOP_LINK struct vop_link_args vop_link_a
#define VOP_LINK(A0,A1,A2) \
		( vop_link_a.a_desc = VDESC(vop_link), \
		vop_link_a.a_vp=(A0), \
		vop_link_a.a_tdvp=(A1), \
		vop_link_a.a_cnp=(A2), \
		(VCALL((A0),VOFFSET(vop_link),&vop_link_a)))
E 4
I 4
static inline int VOP_LINK(vp, tdvp, cnp)
	struct vnode *vp;
	struct vnode *tdvp;
	struct componentname *cnp;
{
	struct vop_link_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_link);
	a.a_vp = vp;
	a.a_tdvp = tdvp;
	a.a_cnp = cnp;
	return (VCALL(vp, VOFFSET(vop_link), &a));
}
E 4
struct vop_rename_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_fdvp;
	struct vnode * a_fvp;
	struct componentname * a_fcnp;
	struct vnode * a_tdvp;
	struct vnode * a_tvp;
	struct componentname * a_tcnp;
E 2
I 2
	struct vnode *a_fdvp;
	struct vnode *a_fvp;
	struct componentname *a_fcnp;
	struct vnode *a_tdvp;
	struct vnode *a_tvp;
	struct componentname *a_tcnp;
E 2
};
extern struct vnodeop_desc vop_rename_desc;
D 4
#define USES_VOP_RENAME struct vop_rename_args vop_rename_a
#define VOP_RENAME(A0,A1,A2,A3,A4,A5) \
		( vop_rename_a.a_desc = VDESC(vop_rename), \
		vop_rename_a.a_fdvp=(A0), \
		vop_rename_a.a_fvp=(A1), \
		vop_rename_a.a_fcnp=(A2), \
		vop_rename_a.a_tdvp=(A3), \
		vop_rename_a.a_tvp=(A4), \
		vop_rename_a.a_tcnp=(A5), \
		(VCALL((A0),VOFFSET(vop_rename),&vop_rename_a)))
E 4
I 4
static inline int VOP_RENAME(fdvp, fvp, fcnp, tdvp, tvp, tcnp)
	struct vnode *fdvp;
	struct vnode *fvp;
	struct componentname *fcnp;
	struct vnode *tdvp;
	struct vnode *tvp;
	struct componentname *tcnp;
{
	struct vop_rename_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_rename);
	a.a_fdvp = fdvp;
	a.a_fvp = fvp;
	a.a_fcnp = fcnp;
	a.a_tdvp = tdvp;
	a.a_tvp = tvp;
	a.a_tcnp = tcnp;
	return (VCALL(fdvp, VOFFSET(vop_rename), &a));
}
E 4
struct vop_mkdir_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode ** a_vpp;
	struct componentname * a_cnp;
	struct vattr * a_vap;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode **a_vpp;
	struct componentname *a_cnp;
	struct vattr *a_vap;
E 2
};
extern struct vnodeop_desc vop_mkdir_desc;
D 4
#define USES_VOP_MKDIR struct vop_mkdir_args vop_mkdir_a
#define VOP_MKDIR(A0,A1,A2,A3) \
		( vop_mkdir_a.a_desc = VDESC(vop_mkdir), \
		vop_mkdir_a.a_dvp=(A0), \
		vop_mkdir_a.a_vpp=(A1), \
		vop_mkdir_a.a_cnp=(A2), \
		vop_mkdir_a.a_vap=(A3), \
		(VCALL((A0),VOFFSET(vop_mkdir),&vop_mkdir_a)))
E 4
I 4
static inline int VOP_MKDIR(dvp, vpp, cnp, vap)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct vattr *vap;
{
	struct vop_mkdir_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_mkdir);
	a.a_dvp = dvp;
	a.a_vpp = vpp;
	a.a_cnp = cnp;
	a.a_vap = vap;
	return (VCALL(dvp, VOFFSET(vop_mkdir), &a));
}
E 4
struct vop_rmdir_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode * a_vp;
	struct componentname * a_cnp;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode *a_vp;
	struct componentname *a_cnp;
E 2
};
extern struct vnodeop_desc vop_rmdir_desc;
D 4
#define USES_VOP_RMDIR struct vop_rmdir_args vop_rmdir_a
#define VOP_RMDIR(A0,A1,A2) \
		( vop_rmdir_a.a_desc = VDESC(vop_rmdir), \
		vop_rmdir_a.a_dvp=(A0), \
		vop_rmdir_a.a_vp=(A1), \
		vop_rmdir_a.a_cnp=(A2), \
		(VCALL((A0),VOFFSET(vop_rmdir),&vop_rmdir_a)))
E 4
I 4
static inline int VOP_RMDIR(dvp, vp, cnp)
	struct vnode *dvp;
	struct vnode *vp;
	struct componentname *cnp;
{
	struct vop_rmdir_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_rmdir);
	a.a_dvp = dvp;
	a.a_vp = vp;
	a.a_cnp = cnp;
	return (VCALL(dvp, VOFFSET(vop_rmdir), &a));
}
E 4
struct vop_symlink_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct vnode ** a_vpp;
	struct componentname * a_cnp;
	struct vattr * a_vap;
	char * a_target;
E 2
I 2
	struct vnode *a_dvp;
	struct vnode **a_vpp;
	struct componentname *a_cnp;
	struct vattr *a_vap;
	char *a_target;
E 2
};
extern struct vnodeop_desc vop_symlink_desc;
D 4
#define USES_VOP_SYMLINK struct vop_symlink_args vop_symlink_a
#define VOP_SYMLINK(A0,A1,A2,A3,A4) \
		( vop_symlink_a.a_desc = VDESC(vop_symlink), \
		vop_symlink_a.a_dvp=(A0), \
		vop_symlink_a.a_vpp=(A1), \
		vop_symlink_a.a_cnp=(A2), \
		vop_symlink_a.a_vap=(A3), \
		vop_symlink_a.a_target=(A4), \
		(VCALL((A0),VOFFSET(vop_symlink),&vop_symlink_a)))
E 4
I 4
static inline int VOP_SYMLINK(dvp, vpp, cnp, vap, target)
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct vattr *vap;
	char *target;
{
	struct vop_symlink_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_symlink);
	a.a_dvp = dvp;
	a.a_vpp = vpp;
	a.a_cnp = cnp;
	a.a_vap = vap;
	a.a_target = target;
	return (VCALL(dvp, VOFFSET(vop_symlink), &a));
}
E 4
struct vop_readdir_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct uio * a_uio;
	struct ucred * a_cred;
	int * a_eofflagp;
E 2
I 2
	struct vnode *a_vp;
	struct uio *a_uio;
	struct ucred *a_cred;
D 3
	int *a_eofflagp;
E 3
E 2
};
extern struct vnodeop_desc vop_readdir_desc;
D 4
#define USES_VOP_READDIR struct vop_readdir_args vop_readdir_a
D 3
#define VOP_READDIR(A0,A1,A2,A3) \
E 3
I 3
#define VOP_READDIR(A0,A1,A2) \
E 3
		( vop_readdir_a.a_desc = VDESC(vop_readdir), \
		vop_readdir_a.a_vp=(A0), \
		vop_readdir_a.a_uio=(A1), \
		vop_readdir_a.a_cred=(A2), \
D 3
		vop_readdir_a.a_eofflagp=(A3), \
E 3
		(VCALL((A0),VOFFSET(vop_readdir),&vop_readdir_a)))
E 4
I 4
static inline int VOP_READDIR(vp, uio, cred)
	struct vnode *vp;
	struct uio *uio;
	struct ucred *cred;
{
	struct vop_readdir_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_readdir);
	a.a_vp = vp;
	a.a_uio = uio;
	a.a_cred = cred;
	return (VCALL(vp, VOFFSET(vop_readdir), &a));
}
E 4
struct vop_readlink_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct uio * a_uio;
	struct ucred * a_cred;
E 2
I 2
	struct vnode *a_vp;
	struct uio *a_uio;
	struct ucred *a_cred;
E 2
};
extern struct vnodeop_desc vop_readlink_desc;
D 4
#define USES_VOP_READLINK struct vop_readlink_args vop_readlink_a
#define VOP_READLINK(A0,A1,A2) \
		( vop_readlink_a.a_desc = VDESC(vop_readlink), \
		vop_readlink_a.a_vp=(A0), \
		vop_readlink_a.a_uio=(A1), \
		vop_readlink_a.a_cred=(A2), \
		(VCALL((A0),VOFFSET(vop_readlink),&vop_readlink_a)))
E 4
I 4
static inline int VOP_READLINK(vp, uio, cred)
	struct vnode *vp;
	struct uio *uio;
	struct ucred *cred;
{
	struct vop_readlink_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_readlink);
	a.a_vp = vp;
	a.a_uio = uio;
	a.a_cred = cred;
	return (VCALL(vp, VOFFSET(vop_readlink), &a));
}
E 4
struct vop_abortop_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_dvp;
	struct componentname * a_cnp;
E 2
I 2
	struct vnode *a_dvp;
	struct componentname *a_cnp;
E 2
};
extern struct vnodeop_desc vop_abortop_desc;
D 4
#define USES_VOP_ABORTOP struct vop_abortop_args vop_abortop_a
#define VOP_ABORTOP(A0,A1) \
		( vop_abortop_a.a_desc = VDESC(vop_abortop), \
		vop_abortop_a.a_dvp=(A0), \
		vop_abortop_a.a_cnp=(A1), \
		(VCALL((A0),VOFFSET(vop_abortop),&vop_abortop_a)))
E 4
I 4
static inline int VOP_ABORTOP(dvp, cnp)
	struct vnode *dvp;
	struct componentname *cnp;
{
	struct vop_abortop_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_abortop);
	a.a_dvp = dvp;
	a.a_cnp = cnp;
	return (VCALL(dvp, VOFFSET(vop_abortop), &a));
}
E 4
struct vop_inactive_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct proc * a_p;
E 2
I 2
	struct vnode *a_vp;
D 3
	struct proc *a_p;
E 3
E 2
};
extern struct vnodeop_desc vop_inactive_desc;
D 4
#define USES_VOP_INACTIVE struct vop_inactive_args vop_inactive_a
D 3
#define VOP_INACTIVE(A0,A1) \
E 3
I 3
#define VOP_INACTIVE(A0) \
E 3
		( vop_inactive_a.a_desc = VDESC(vop_inactive), \
		vop_inactive_a.a_vp=(A0), \
D 3
		vop_inactive_a.a_p=(A1), \
E 3
		(VCALL((A0),VOFFSET(vop_inactive),&vop_inactive_a)))
E 4
I 4
static inline int VOP_INACTIVE(vp)
	struct vnode *vp;
{
	struct vop_inactive_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_inactive);
	a.a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_inactive), &a));
}
E 4
struct vop_reclaim_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
};
extern struct vnodeop_desc vop_reclaim_desc;
D 4
#define USES_VOP_RECLAIM struct vop_reclaim_args vop_reclaim_a
#define VOP_RECLAIM(A0) \
		( vop_reclaim_a.a_desc = VDESC(vop_reclaim), \
		vop_reclaim_a.a_vp=(A0), \
		(VCALL((A0),VOFFSET(vop_reclaim),&vop_reclaim_a)))
E 4
I 4
static inline int VOP_RECLAIM(vp)
	struct vnode *vp;
{
	struct vop_reclaim_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_reclaim);
	a.a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_reclaim), &a));
}
E 4
struct vop_lock_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
};
extern struct vnodeop_desc vop_lock_desc;
D 4
#define USES_VOP_LOCK struct vop_lock_args vop_lock_a
#define VOP_LOCK(A0) \
		( vop_lock_a.a_desc = VDESC(vop_lock), \
		vop_lock_a.a_vp=(A0), \
		(VCALL((A0),VOFFSET(vop_lock),&vop_lock_a)))
E 4
I 4
static inline int VOP_LOCK(vp)
	struct vnode *vp;
{
	struct vop_lock_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_lock);
	a.a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_lock), &a));
}
E 4
struct vop_unlock_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
};
extern struct vnodeop_desc vop_unlock_desc;
D 4
#define USES_VOP_UNLOCK struct vop_unlock_args vop_unlock_a
#define VOP_UNLOCK(A0) \
		( vop_unlock_a.a_desc = VDESC(vop_unlock), \
		vop_unlock_a.a_vp=(A0), \
		(VCALL((A0),VOFFSET(vop_unlock),&vop_unlock_a)))
E 4
I 4
static inline int VOP_UNLOCK(vp)
	struct vnode *vp;
{
	struct vop_unlock_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_unlock);
	a.a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_unlock), &a));
}
E 4
struct vop_bmap_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	daddr_t  a_bn;
	struct vnode ** a_vpp;
	daddr_t * a_bnp;
E 2
I 2
	struct vnode *a_vp;
	daddr_t a_bn;
	struct vnode **a_vpp;
	daddr_t *a_bnp;
E 2
};
extern struct vnodeop_desc vop_bmap_desc;
D 4
#define USES_VOP_BMAP struct vop_bmap_args vop_bmap_a
#define VOP_BMAP(A0,A1,A2,A3) \
		( vop_bmap_a.a_desc = VDESC(vop_bmap), \
		vop_bmap_a.a_vp=(A0), \
		vop_bmap_a.a_bn=(A1), \
		vop_bmap_a.a_vpp=(A2), \
		vop_bmap_a.a_bnp=(A3), \
		(VCALL((A0),VOFFSET(vop_bmap),&vop_bmap_a)))
E 4
I 4
static inline int VOP_BMAP(vp, bn, vpp, bnp)
	struct vnode *vp;
	daddr_t bn;
	struct vnode **vpp;
	daddr_t *bnp;
{
	struct vop_bmap_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

struct vop_strategy_args {
	struct vnodeop_desc *a_desc;
D 2
	struct buf * a_bp;
E 2
I 2
	struct buf *a_bp;
E 2
};
extern struct vnodeop_desc vop_strategy_desc;
#define USES_VOP_STRATEGY struct vop_strategy_args vop_strategy_a
#define VOP_STRATEGY(A0) \
		( vop_strategy_a.a_desc = VDESC(vop_strategy), \
		vop_strategy_a.a_bp=(A0), \
		(VCALL((A0),VOFFSET(vop_strategy),&vop_strategy_a)))

/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_bmap);
	a.a_vp = vp;
	a.a_bn = bn;
	a.a_vpp = vpp;
	a.a_bnp = bnp;
	return (VCALL(vp, VOFFSET(vop_bmap), &a));
}
E 4
struct vop_print_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
};
extern struct vnodeop_desc vop_print_desc;
D 4
#define USES_VOP_PRINT struct vop_print_args vop_print_a
#define VOP_PRINT(A0) \
		( vop_print_a.a_desc = VDESC(vop_print), \
		vop_print_a.a_vp=(A0), \
		(VCALL((A0),VOFFSET(vop_print),&vop_print_a)))
E 4
I 4
static inline int VOP_PRINT(vp)
	struct vnode *vp;
{
	struct vop_print_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_print);
	a.a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_print), &a));
}
E 4
struct vop_islocked_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
};
extern struct vnodeop_desc vop_islocked_desc;
D 4
#define USES_VOP_ISLOCKED struct vop_islocked_args vop_islocked_a
#define VOP_ISLOCKED(A0) \
		( vop_islocked_a.a_desc = VDESC(vop_islocked), \
		vop_islocked_a.a_vp=(A0), \
		(VCALL((A0),VOFFSET(vop_islocked),&vop_islocked_a)))
E 4
I 4
static inline int VOP_ISLOCKED(vp)
	struct vnode *vp;
{
	struct vop_islocked_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_islocked);
	a.a_vp = vp;
	return (VCALL(vp, VOFFSET(vop_islocked), &a));
}
E 4
struct vop_advlock_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	caddr_t  a_id;
	int  a_op;
E 4
I 4
	caddr_t a_id;
	int a_op;
E 4
D 2
	struct flock * a_fl;
E 2
I 2
	struct flock *a_fl;
E 2
D 4
	int  a_flags;
E 4
I 4
	int a_flags;
E 4
};
extern struct vnodeop_desc vop_advlock_desc;
D 4
#define USES_VOP_ADVLOCK struct vop_advlock_args vop_advlock_a
#define VOP_ADVLOCK(A0,A1,A2,A3,A4) \
		( vop_advlock_a.a_desc = VDESC(vop_advlock), \
		vop_advlock_a.a_vp=(A0), \
		vop_advlock_a.a_id=(A1), \
		vop_advlock_a.a_op=(A2), \
		vop_advlock_a.a_fl=(A3), \
		vop_advlock_a.a_flags=(A4), \
		(VCALL((A0),VOFFSET(vop_advlock),&vop_advlock_a)))
E 4
I 4
static inline int VOP_ADVLOCK(vp, id, op, fl, flags)
	struct vnode *vp;
	caddr_t id;
	int op;
	struct flock *fl;
	int flags;
{
	struct vop_advlock_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_advlock);
	a.a_vp = vp;
	a.a_id = id;
	a.a_op = op;
	a.a_fl = fl;
	a.a_flags = flags;
	return (VCALL(vp, VOFFSET(vop_advlock), &a));
}
E 4
struct vop_blkatoff_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 4
	off_t  a_offset;
E 4
I 4
	off_t a_offset;
E 4
D 2
	char ** a_res;
	struct buf ** a_bpp;
E 2
I 2
	char **a_res;
	struct buf **a_bpp;
E 2
};
extern struct vnodeop_desc vop_blkatoff_desc;
D 4
#define USES_VOP_BLKATOFF struct vop_blkatoff_args vop_blkatoff_a
#define VOP_BLKATOFF(A0,A1,A2,A3) \
		( vop_blkatoff_a.a_desc = VDESC(vop_blkatoff), \
		vop_blkatoff_a.a_vp=(A0), \
		vop_blkatoff_a.a_offset=(A1), \
		vop_blkatoff_a.a_res=(A2), \
		vop_blkatoff_a.a_bpp=(A3), \
		(VCALL((A0),VOFFSET(vop_blkatoff),&vop_blkatoff_a)))
E 4
I 4
static inline int VOP_BLKATOFF(vp, offset, res, bpp)
	struct vnode *vp;
	off_t offset;
	char **res;
	struct buf **bpp;
{
	struct vop_blkatoff_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

struct vop_vget_args {
	struct vnodeop_desc *a_desc;
D 2
	struct mount * a_mp;
E 2
I 2
	struct mount *a_mp;
E 2
	ino_t  a_ino;
D 2
	struct vnode ** a_vpp;
E 2
I 2
	struct vnode **a_vpp;
E 2
};
extern struct vnodeop_desc vop_vget_desc;
#define USES_VOP_VGET struct vop_vget_args vop_vget_a
#define VOP_VGET(A0,A1,A2) \
		( vop_vget_a.a_desc = VDESC(vop_vget), \
		vop_vget_a.a_mp=(A0), \
		vop_vget_a.a_ino=(A1), \
		vop_vget_a.a_vpp=(A2), \
		(VCALL((A0),VOFFSET(vop_vget),&vop_vget_a)))

/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_blkatoff);
	a.a_vp = vp;
	a.a_offset = offset;
	a.a_res = res;
	a.a_bpp = bpp;
	return (VCALL(vp, VOFFSET(vop_blkatoff), &a));
}
E 4
struct vop_valloc_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_pvp;
E 2
I 2
	struct vnode *a_pvp;
E 2
D 4
	int  a_mode;
E 4
I 4
	int a_mode;
E 4
D 2
	struct ucred * a_cred;
	struct vnode ** a_vpp;
E 2
I 2
	struct ucred *a_cred;
	struct vnode **a_vpp;
E 2
};
extern struct vnodeop_desc vop_valloc_desc;
D 4
#define USES_VOP_VALLOC struct vop_valloc_args vop_valloc_a
#define VOP_VALLOC(A0,A1,A2,A3) \
		( vop_valloc_a.a_desc = VDESC(vop_valloc), \
		vop_valloc_a.a_pvp=(A0), \
		vop_valloc_a.a_mode=(A1), \
		vop_valloc_a.a_cred=(A2), \
		vop_valloc_a.a_vpp=(A3), \
		(VCALL((A0),VOFFSET(vop_valloc),&vop_valloc_a)))
E 4
I 4
static inline int VOP_VALLOC(pvp, mode, cred, vpp)
	struct vnode *pvp;
	int mode;
	struct ucred *cred;
	struct vnode **vpp;
{
	struct vop_valloc_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_valloc);
	a.a_pvp = pvp;
	a.a_mode = mode;
	a.a_cred = cred;
	a.a_vpp = vpp;
	return (VCALL(pvp, VOFFSET(vop_valloc), &a));
}
E 4
struct vop_vfree_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_pvp;
E 2
I 2
	struct vnode *a_pvp;
E 2
D 4
	ino_t  a_ino;
	int  a_mode;
E 4
I 4
	ino_t a_ino;
	int a_mode;
E 4
};
extern struct vnodeop_desc vop_vfree_desc;
D 4
#define USES_VOP_VFREE struct vop_vfree_args vop_vfree_a
#define VOP_VFREE(A0,A1,A2) \
		( vop_vfree_a.a_desc = VDESC(vop_vfree), \
		vop_vfree_a.a_pvp=(A0), \
		vop_vfree_a.a_ino=(A1), \
		vop_vfree_a.a_mode=(A2), \
		(VCALL((A0),VOFFSET(vop_vfree),&vop_vfree_a)))
E 4
I 4
static inline int VOP_VFREE(pvp, ino, mode)
	struct vnode *pvp;
	ino_t ino;
	int mode;
{
	struct vop_vfree_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_vfree);
	a.a_pvp = pvp;
	a.a_ino = ino;
	a.a_mode = mode;
	return (VCALL(pvp, VOFFSET(vop_vfree), &a));
}
E 4
struct vop_truncate_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
E 2
I 2
	struct vnode *a_vp;
E 2
D 3
	u_long  a_length;
E 3
I 3
D 4
	off_t  a_length;
E 3
	int  a_flags;
E 4
I 4
	off_t a_length;
	int a_flags;
E 4
D 2
	struct ucred * a_cred;
E 2
I 2
	struct ucred *a_cred;
I 3
	struct proc *a_p;
E 3
E 2
};
extern struct vnodeop_desc vop_truncate_desc;
D 4
#define USES_VOP_TRUNCATE struct vop_truncate_args vop_truncate_a
D 3
#define VOP_TRUNCATE(A0,A1,A2,A3) \
E 3
I 3
#define VOP_TRUNCATE(A0,A1,A2,A3,A4) \
E 3
		( vop_truncate_a.a_desc = VDESC(vop_truncate), \
		vop_truncate_a.a_vp=(A0), \
		vop_truncate_a.a_length=(A1), \
		vop_truncate_a.a_flags=(A2), \
		vop_truncate_a.a_cred=(A3), \
I 3
		vop_truncate_a.a_p=(A4), \
E 3
		(VCALL((A0),VOFFSET(vop_truncate),&vop_truncate_a)))
E 4
I 4
static inline int VOP_TRUNCATE(vp, length, flags, cred, p)
	struct vnode *vp;
	off_t length;
	int flags;
	struct ucred *cred;
	struct proc *p;
{
	struct vop_truncate_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */

E 4
I 4
	a.a_desc = VDESC(vop_truncate);
	a.a_vp = vp;
	a.a_length = length;
	a.a_flags = flags;
	a.a_cred = cred;
	a.a_p = p;
	return (VCALL(vp, VOFFSET(vop_truncate), &a));
}
E 4
struct vop_update_args {
	struct vnodeop_desc *a_desc;
D 2
	struct vnode * a_vp;
	struct timeval * a_ta;
	struct timeval * a_tm;
E 2
I 2
	struct vnode *a_vp;
	struct timeval *a_ta;
	struct timeval *a_tm;
E 2
D 4
	int  a_waitfor;
E 4
I 4
	int a_waitfor;
E 4
};
extern struct vnodeop_desc vop_update_desc;
D 4
#define USES_VOP_UPDATE struct vop_update_args vop_update_a
#define VOP_UPDATE(A0,A1,A2,A3) \
		( vop_update_a.a_desc = VDESC(vop_update), \
		vop_update_a.a_vp=(A0), \
		vop_update_a.a_ta=(A1), \
		vop_update_a.a_tm=(A2), \
		vop_update_a.a_waitfor=(A3), \
		(VCALL((A0),VOFFSET(vop_update),&vop_update_a)))
E 4
I 4
static inline int VOP_UPDATE(vp, ta, tm, waitfor)
	struct vnode *vp;
	struct timeval *ta;
	struct timeval *tm;
	int waitfor;
{
	struct vop_update_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */
E 4
I 4
	a.a_desc = VDESC(vop_update);
	a.a_vp = vp;
	a.a_ta = ta;
	a.a_tm = tm;
	a.a_waitfor = waitfor;
	return (VCALL(vp, VOFFSET(vop_update), &a));
}
#include <sys/buf.h>
struct vop_strategy_args {
	struct vnodeop_desc *a_desc;
	struct buf *a_bp;
};
extern struct vnodeop_desc vop_strategy_desc;
static inline int VOP_STRATEGY(bp)
	struct buf *bp;
{
	struct vop_strategy_args a;
E 4

I 4
	a.a_desc = VDESC(vop_strategy);
	a.a_bp = bp;
	return (VCALL((bp)->b_vp, VOFFSET(vop_strategy), &a));
}

E 4
struct vop_bwrite_args {
	struct vnodeop_desc *a_desc;
D 2
	struct buf * a_bp;
E 2
I 2
	struct buf *a_bp;
E 2
};
extern struct vnodeop_desc vop_bwrite_desc;
D 4
#define USES_VOP_BWRITE struct vop_bwrite_args vop_bwrite_a
#define VOP_BWRITE(A0) \
		( vop_bwrite_a.a_desc = VDESC(vop_bwrite), \
		vop_bwrite_a.a_bp=(A0), \
		(VCALL((A0),VOFFSET(vop_bwrite),&vop_bwrite_a)))
E 4
I 4
static inline int VOP_BWRITE(bp)
	struct buf *bp;
{
	struct vop_bwrite_args a;
E 4

D 4
/* This is automatically generated.  Modify the corresponding .int file. */
/* BEGIN VERBATIM H */
extern struct vnodeop_desc vop_default_desc;
/* END VERBATIM H */
/* This is automatically generated.  Modify the corresponding .int file. */
/* BEGIN VERBATIM H */
/*
 * Three existing BSD vnodeops (strategy, vget and bwrite)
 * don't take any vnodes as arguments.
 * This means that these operations will never function successfully
 * through a bypass routine.
 * Both these operations are going away (right, Kirk?):
 *    vget will become a vfs operation
 *    bwrite and strategy
 *	will be replaced with an integrated VM page/buffer cache.
 *
 * To get around this problem for now we handle
 * these ops as special cases.
 */
#undef VOP_STRATEGY
#define VOP_STRATEGY(BP) \
		( vop_strategy_a.a_desc = VDESC(vop_strategy), \
		vop_strategy_a.a_bp=(BP), \
		(VCALL((BP)->b_vp,VOFFSET(vop_strategy),&vop_strategy_a)))
#undef VOP_BWRITE
#define VOP_BWRITE(BP) \
		( vop_bwrite_a.a_desc = VDESC(vop_bwrite), \
		vop_bwrite_a.a_bp=(BP), \
		(VCALL((BP)->b_vp,VOFFSET(vop_bwrite),&vop_bwrite_a)))
#undef VOP_VGET
#define VOP_VGET(VP,INO,VPP) \
		( vop_vget_a.a_desc = VDESC(vop_vget), \
		vop_vget_a.a_mp=(VP)->v_mount, \
		vop_vget_a.a_ino=(INO), \
		vop_vget_a.a_vpp=(VPP), \
		(VCALL((VP),VOFFSET(vop_vget),&vop_vget_a)))
/*
 * Many clients invoke vop_vget directly.  To aid them,
 * we define a few more macros.  (These go away
 * whe vget goes to the vfs interface.)
 */
#define LFS_VGET(MP,INO,VPP) \
		( vop_vget_a.a_desc = VDESC(vop_vget), \
		vop_vget_a.a_mp=(MP), \
		vop_vget_a.a_ino=(INO), \
		vop_vget_a.a_vpp=(VPP), \
		lfs_vget(&vop_vget_a))
#define FFS_VGET(MP,INO,VPP) \
		( vop_vget_a.a_desc = VDESC(vop_vget), \
		vop_vget_a.a_mp=(MP), \
		vop_vget_a.a_ino=(INO), \
		vop_vget_a.a_vpp=(VPP), \
		ffs_vget(&vop_vget_a))
/* END VERBATIM H */
E 4
I 4
	a.a_desc = VDESC(vop_bwrite);
	a.a_bp = bp;
	return (VCALL((bp)->b_vp, VOFFSET(vop_bwrite), &a));
}
E 4
E 1
