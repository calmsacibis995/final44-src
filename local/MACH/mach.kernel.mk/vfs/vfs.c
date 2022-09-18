/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	vfs.c,v $
 * Revision 2.10  92/02/06  00:27:11  mja
 * 	Added hooks for file reference tracing.
 * 	[92/01/03            lily]
 * 
 * Revision 2.9  89/08/02  08:47:37  jsb
 * 	Removed Mach conditionals. Added zone initialization. Use vfs zones.
 * 	[89/07/31  15:19:39  jsb]
 * 
 * Revision 2.8  89/07/14  15:29:43  rvb
 * 	Generalize "cover_mount" to deal with nfs stuff from ULTRIX.
 * 	[89/06/08            rvb]
 * 
 * Revision 2.7  89/06/03  15:42:24  jsb
 * 	Remove rfs_sync call.
 * 	[89/05/26  23:11:51  jsb]
 * 
 * Revision 2.6  89/04/22  15:33:52  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  22:43:57  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:12:34  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/01/23  15:31:54  rvb
 * 	Don't rfs_sync in sync() unless MACH_NFS
 * 	[89/01/22            rvb]
 * 
 * Revision 2.2  89/01/18  01:24:19  jsb
 * 	Include file references; added cover_mount, to allow afs and old
 * 	/etc/mount to work; modify smount so that cover_mount can call it; use
 * 	kalloc instead of zalloc for vfsp's to save memory; don't zinit
 * 	vfs_zone or vnode_zone (the later was never used!); remove
 * 	vm_object_cache_clear, see ufs_vfsops.c.
 * 	[89/01/17  15:51:37  jsb]
 * 
 * 25-Aug-87  Peter King (king) at NeXT
 *	Ported from NFS distribution.
 */ 

/* @(#)vfs.c	1.3 87/06/25 3.2/4.3NFSSRC */
/*	@(#)vfs.c 1.1 86/09/25 SMI	*/

#include <mach_nbc.h>
#include <mach_nfs.h>
#include <mach_afs.h>
#include <dfstrace.h>

#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/uio.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/systm.h>
#include <sys/mount.h>
#include <sys/inode.h>
#include <kern/zalloc.h>
#include <mach/vm_param.h>

#if DFSTRACE > 0
#include <dfs/dfs_log.h>
#endif DFSTRACE

zone_t vfs_name_zone;
zone_t vfs_vfs_zone;

/*
 * vfs global data
 */
struct inode *rootdir;			/* pointer to root vnode */

struct vfs *rootvfs;			/* pointer to root vfs. This is */
					/* also the head of the vfs list */

/*
 * System calls
 */
cover_mount()
{
	char *special, *dir;
	int rwflag;
	char afsdir[5];
	register struct a {
		char	*special;
		char	*dir;
		int	rwflag;
#ifdef	PMAX
		int	type;
		caddr_t	data;
#endif	PMAX
	} *uap = (struct a *)u.u_ap;
	register struct b {
		int	type;
		char	*dir;
		int	flags;
		caddr_t	data;
	} *uap2 = (struct b *)u.u_ap;

	special	= uap->special;
	dir	= uap->dir;
	rwflag	= uap->rwflag;

#ifdef	PMAX
	if (uap->type == 05) {	/* nfs */
		uap2->type  = MOUNT_NFS;
		uap2->dir   = dir;
		uap2->flags = rwflag;
		uap2->data  = (caddr_t) uap->data;
			/* we need to fudge an nfs_arg !! yuck. */
	} else if (uap ->type == 01) {
#endif	PMAX
	if (copyinstr(dir, afsdir, 5, 0) == EFAULT) {
		u.u_error = EFAULT;
		return;
	}
	if (! strcmp(afsdir, "/afs")) {
		uap2->type  = MOUNT_AFS;
		uap2->dir   = dir;
		uap2->flags = rwflag;
		uap2->data  = (caddr_t) 0;
	} else {
		uap2->type  = MOUNT_UFS;
		uap2->dir   = dir;
		uap2->flags = rwflag | 0x8;	/* see smount, below */
		uap2->data  = (caddr_t) special;
	}
#ifdef	PMAX
	}
#endif	PMAX
	smount();
}

/*
 * mount system call
 */
smount()
{
	register struct a {
		int	type;
		char	*dir;
		int	flags;
		caddr_t	data;
	} *uap = (struct a *)u.u_ap;
	struct pathname pn;
	struct vnode *vp;
	struct vfs *vfsp;
	extern struct vnodeops ufs_vnodeops;

	/*
	 * Must be super user
	 */
	if (!suser())
		return;
	/*
	 * Do all the stupid things necessary to make cover_mount work.
	 * If MOUNT_UFS and uap->flags has magic cookie on (0x8),
	 * then we know we don't have to copy in pointer to special.
	 */
	if (uap->type == MOUNT_UFS) {
		if (uap->flags & 0x8) {
			uap->flags ^= 0x8;
		} else {
			struct ufs_args args;

			u.u_error = copyin(uap->data, (caddr_t)&args,
				sizeof (struct ufs_args));
			if (u.u_error)
				return;
			uap->data = (caddr_t) args.fspec;
		}
	}
	/*
	 * Get vnode to be covered
	 */
	u.u_error = lookupname(uap->dir, UIO_USERSPACE, FOLLOW_LINK,
	    (struct vnode **)0, &vp);
	if (u.u_error)
		return;
	dnlc_purge();
	if (vp->v_count != 1) {
		VN_RELE(vp);
		u.u_error = EBUSY;
		return;
	}
	if ((vp->v_mode&VFMT) != VDIR) {
		VN_RELE(vp);
		u.u_error = ENOTDIR;
		return;
	}
	u.u_error = pn_get(uap->dir, UIO_USERSPACE, &pn);
	if (u.u_error) {
		VN_RELE(vp);
		return;
	}
	/*  Check for negative values of uap->type also  */
	if ((uap->type < 0 ||
	     uap->type > MOUNT_MAXTYPE) ||
	     vfssw[uap->type] == (struct vfsops *)0) {
		u.u_error = ENODEV;
		VN_RELE(vp);
		pn_free(&pn);
		return;
	}
	ZALLOC(vfs_vfs_zone, vfsp, struct vfs *);
	VFS_INIT(vfsp, vfssw[uap->type], (caddr_t)0);

	/*
	 * Mount the filesystem.
	 * Lock covered vnode (XXX this currently only works if it is type ufs)
	 */
	if (vp->v_type == ITYPE_UFS)
		ilock(VTOI(vp));
	u.u_error = vfs_add(vp, vfsp, uap->flags);
	if (!u.u_error) {
		u.u_error = VFS_MOUNT(vfsp, pn.pn_path, uap->data);
	}
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_MOUNT, uap->flags, &pn, vp);
#endif DFSTRACE
	if (vp->v_type == ITYPE_UFS)
		iunlock(VTOI(vp));
	pn_free(&pn);
	if (!u.u_error) {
		vfs_unlock(vfsp);
#ifdef	PMAX
		storemnt(uap->type, uap->dir, uap->data);
#endif	PMAX
	} else {
		vfs_remove(vfsp);
		ZFREE(vfs_vfs_zone, vfsp);
		VN_RELE(vp);
	}
	return;
}


/*
 * Sync system call. sync each vfs
 */
sync()
{
	register struct vfs *vfsp;

#if	MACH_NBC
	mfs_sync();
#endif	MACH_NBC

	for (vfsp = rootvfs; vfsp != (struct vfs *)0; vfsp = vfsp->vfs_next) {
		VFS_SYNC(vfsp);
	}
}

/*
 * get filesystem statistics
 */
statfs()
{
	struct a {
		char *path;
		struct statfs *buf;
	} *uap = (struct a *)u.u_ap;
	struct vnode *vp;

	u.u_error = lookupname(uap->path, UIO_USERSPACE, FOLLOW_LINK,
	    (struct vnode **)0, &vp);
	if (u.u_error)
		return;
	cstatfs(vp->v_vfsp, uap->buf);
	VN_RELE(vp);
}

fstatfs()
{
	struct a {
		int fd;
		struct statfs *buf;
	} *uap = (struct a *)u.u_ap;
	struct file *fp;

	u.u_error = getvnodefp(uap->fd, &fp);
	if (u.u_error == 0)
		cstatfs(((struct vnode *)fp->f_data)->v_vfsp, uap->buf);
}

cstatfs(vfsp, ubuf)
	struct vfs *vfsp;
	struct statfs *ubuf;
{
	struct statfs sb;

	u.u_error = VFS_STATFS(vfsp, &sb);
	if (u.u_error)
		return;
	u.u_error = copyout((caddr_t)&sb, (caddr_t)ubuf, sizeof(sb));
}

/*
 * Unmount system call.
 *
 * Note: unmount takes a path to the vnode mounted on as argument,
 * not special file (as before).
 */
unmount()
{
	struct a {
		char	*pathp;
	} *uap = (struct a *)u.u_ap;
	struct vnode *fsrootvp;
	register struct vfs *vfsp;

	if (!suser())
		return;
	/*
	 * lookup root of fs
	 */
	u.u_error = lookupname(uap->pathp, UIO_USERSPACE, FOLLOW_LINK,
	    (struct vnode **)0, &fsrootvp);
	if (u.u_error)
		return;
	/*
	 * make sure this is a root
	 */
	if ((fsrootvp->v_flag & VROOT) == 0) {
		u.u_error = EINVAL;
		VN_RELE(fsrootvp);
		return;
	}
	/*
	 * get vfs
	 */
	vfsp = fsrootvp->v_vfsp;
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_UNMOUNT, 0, fsrootvp);
#endif DFSTRACE
	VN_RELE(fsrootvp);
	/*
	 * Do the unmount.
	 */
#if	MACH_NBC
	mfs_cache_clear();		/* clear the MFS cache */
#endif	MACH_NBC
	dounmount(vfsp);
#if DFSTRACE > 0
	if (traceon) dfs_log(DFS_UNMOUNT, DFS_POST, uap->pathp);
#endif DFSTRACE
#ifdef	PMAX
	if (u.u_error == 0)
		deletemnt_path(uap->pathp);
#endif	PMAX
}

/*
 * XXX Subroutine so the old 4.2/S5-style "umount" call can use this code
 * as well.
 */
dounmount(vfsp)
	register struct vfs *vfsp;
{
	register struct vnode *coveredvp;

	/*
	 * Get covered vnode.
	 */
	coveredvp = vfsp->vfs_vnodecovered;
	/*
	 * lock vnode to maintain fs status quo during unmount
	 */
	u.u_error = vfs_lock(vfsp);
	if (u.u_error)
		return;

#if	0 /* XXX Until we do something more intelligent */
	vm_object_cache_clear();	/* remove cached files */
#endif	0
	dnlc_purge();	/* remove dnlc entries for this file sys */
	VFS_SYNC(vfsp);

	u.u_error = VFS_UNMOUNT(vfsp);
	if (u.u_error) {
		vfs_unlock(vfsp);
	} else {
		VN_RELE(coveredvp);
		vfs_remove(vfsp);
		ZFREE(vfs_vfs_zone, vfsp);
	}
}

/*
 * vfs_init is called by setup_main (init_main.c) to setup any
 * structures needed by the VFS, eg. vfs_name_zone.
 */
void
vfs_init()
{
	vfs_name_zone = zinit(MAXPATHLEN, ninode*MAXPATHLEN, PAGE_SIZE,
			FALSE, "vfs name");
	vfs_vfs_zone = zinit(sizeof(struct vfs), 1024*1024, PAGE_SIZE,
			FALSE, "vfs vfs");
	specfs_zone_init();
	ufs_zone_init();
#if	MACH_AFS
	afs_zone_init();
#endif	MACH_AFS
#if	MACH_NFS
	nfs_zone_init();
	rpc_zone_init();
#endif	MACH_NFS
}

/*
 * External routines
 */

/*
 * vfs_mountroot is called by main (init_main.c) to
 * mount the root filesystem.
 */
void
vfs_mountroot()
{
	register int error;
	extern int (*rootfsmount)();	/* pointer to root mounting routine */
					/* set by (auto)configuration */
#if	MACH_NFS
	extern int nfs_mountroot();

	rootfsmount = nfs_mountroot;	/* will ask, may call ufs_mountroot */
#endif	MACH_NFS

	/*
	 * Rootfsmount is a pointer to the routine which will mount a specific
	 * filesystem as the root. It is setup by autoconfiguration.
	 * If error panic.
	 */
	error = (*rootfsmount)();
	if (error) {
		panic("rootmount cannot mount root");
	}
	/*
	 * Get vnode for '/'.
	 * Setup rootdir, u.u_rdir and u.u_cdir to point to it.
	 * These are used by lookuppn so that it knows where
	 * to start from '/' or '.'.
	 */
	error = VFS_ROOT(rootvfs, &rootdir);
	if (error)
		panic("rootmount: cannot find root vnode");
	u.u_cdir = rootdir;
	VN_HOLD(ITOV(u.u_cdir));
	u.u_rdir = NULL;
}

/*
 * vfs_add is called by a specific filesystem's mount routine to add
 * the new vfs into the vfs list and to cover the mounted on vnode.
 * The vfs is also locked so that lookuppn will not venture into the
 * covered vnodes subtree.
 * coveredvp is zero if this is the root.
 */
int
vfs_add(coveredvp, vfsp, mflag)
	register struct vnode *coveredvp;
	register struct vfs *vfsp;
	int mflag;
{
	register int error;

	error = vfs_lock(vfsp);
	if (error)
		return (error);
	if (coveredvp != (struct vnode *)0) {
		/*
		 * Return EBUSY if the covered vp is already mounted on.
		 */
		if (coveredvp->v_vfsmountedhere != (struct vfs *)0) {
			vfs_unlock(vfsp);
			return(EBUSY);
		}
		/*
		 * Put the new vfs on the vfs list after root.
		 * Point the covered vnode at the new vfs so lookuppn
		 * (vfs_lookup.c) can work its way into the new file system.
		 */
		vfsp->vfs_next = rootvfs->vfs_next;
		rootvfs->vfs_next = vfsp;
		coveredvp->v_vfsmountedhere = vfsp;
	} else {
		/*
		 * This is the root of the whole world.
		 */
		rootvfs = vfsp;
		vfsp->vfs_next = (struct vfs *)0;
	}
	vfsp->vfs_vnodecovered = coveredvp;
	if (mflag & M_RDONLY) {
		vfsp->vfs_flag |= VFS_RDONLY;
	} else {
		vfsp->vfs_flag &= ~VFS_RDONLY;
	}
	if (mflag & M_NOSUID) {
		vfsp->vfs_flag |= VFS_NOSUID;
	} else {
		vfsp->vfs_flag &= ~VFS_NOSUID;
	}
	return (0);
}

/*
 * Remove a vfs from the vfs list, and destory pointers to it.
 * Should be called by filesystem implementation after it determines
 * that an unmount is legal but before it destroys the vfs.
 */
void
vfs_remove(vfsp)
register struct vfs *vfsp;
{
	register struct vfs *tvfsp;
	register struct vnode *vp;

	/*
	 * can't unmount root. Should never happen, because fs will be busy.
	 */
	if (vfsp == rootvfs)
		panic("vfs_remove: unmounting root");
	for (tvfsp = rootvfs;
	    tvfsp != (struct vfs *)0; tvfsp = tvfsp->vfs_next) {
		if (tvfsp->vfs_next == vfsp) {
			/*
			 * remove vfs from list, unmount covered vp.
			 */
			tvfsp->vfs_next = vfsp->vfs_next;
			vp = vfsp->vfs_vnodecovered;
			vp->v_vfsmountedhere = (struct vfs *)0;
			/*
			 * release lock and wakeup anybody waiting
			 */
			vfs_unlock(vfsp);
			return;
		}
	}
	/*
	 * can't find vfs to remove
	 */
	panic("vfs_remove: vfs not found");
}

/*
 * Lock a filesystem to prevent access to it while mounting and unmounting.
 * Returns error if already locked.
 * XXX This totally inadequate for unmount right now - srk
 */
int
vfs_lock(vfsp)
	register struct vfs *vfsp;
{

	if (vfsp->vfs_flag & VFS_MLOCK)
		return (EBUSY);
	vfsp->vfs_flag |= VFS_MLOCK;
	return (0);
}

/*
 * Unlock a locked filesystem.
 * Panics if not locked
 */
void
vfs_unlock(vfsp)
	register struct vfs *vfsp;
{

	if ((vfsp->vfs_flag & VFS_MLOCK) == 0)
		panic("vfs_unlock");
	vfsp->vfs_flag &= ~VFS_MLOCK;
	/*
	 * Wake anybody waiting for the lock to clear
	 */
	if (vfsp->vfs_flag & VFS_MWAIT) {
		vfsp->vfs_flag &= ~VFS_MWAIT;
		wakeup((caddr_t)vfsp);
	}
}

struct vfs *
getvfs(fsid)
	fsid_t *fsid;
{
	register struct vfs *vfsp;

	for (vfsp = rootvfs; vfsp; vfsp = vfsp->vfs_next) {
		if (vfsp->vfs_fsid.val[0] == fsid->val[0] &&
		    vfsp->vfs_fsid.val[1] == fsid->val[1]) {
			break;
		}
	}
	return (vfsp);
}

/*
 * Take a file system ID of the sort that appears in a "struct vattr"
 * and find the VFS that has that file system ID.  This is done by
 * finding the root directory for each VFS, finding its attributes,
 * and comparing its file system ID with the given file system ID;
 * if we have a match, we've found the right VFS.  It's slow, but it
 * works, and it's only used for the System V "ustat" call which is
 * a crock anyway ("statfs" is better).
 */
int
vafsidtovfs(vafsid, vfspp)
	long vafsid;
	struct vfs **vfspp;
{
	register struct vfs *vfsp;
	struct vnode *rootvn;		/* pointer to root vnode of vfs */
	struct vattr vattr;
	register int error;

	for (vfsp = rootvfs; vfsp != (struct vfs *)0; vfsp = vfsp->vfs_next) {
		error = VFS_ROOT(vfsp, &rootvn);
		if (error)
			return(error);
		error = VOP_GETATTR(rootvn, &vattr, u.u_cred);
		if (error)
			return(error);
		if (vafsid == vattr.va_fsid) {
			*vfspp = vfsp;
			return(0);
		}
	}
	return(EINVAL);			/* not found */
}
