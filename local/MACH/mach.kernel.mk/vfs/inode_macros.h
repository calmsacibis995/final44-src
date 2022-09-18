/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	inode_macros.h,v $
 * Revision 2.7  92/02/06  00:27:05  mja
 * 	Added hooks for file reference tracing.
 * 	[92/01/03            lily]
 * 
 * Revision 2.6  90/08/30  11:51:19  bohman
 * 	Changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.5  90/07/03  16:55:32  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:26:09  mrt]
 * 
 * Revision 2.4  90/03/27  18:56:03  dlb
 * 	Remove MACH_RFS dependency by providing version of
 * 	LOOKUP_EXECVE_NAME and LOOKUP_SHELL_NAME that call lookuppn
 * 	instead of rlookuppn if MACH_RFS is off.  This ought to be done
 * 	in bsd/kern_exec.c, but that would introduce a VFS dependency.
 * 	[90/03/26            dlb]
 * 
 * Revision 2.3  89/05/11  15:40:25  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.2  89/04/22  15:33:01  gm0w
 * 	Created macros for manipulating inode and filesystems independent
 * 	of VFS/non-VFS configurations.  These are the VFS variants.
 * 	[89/04/14            gm0w]
 * 
 */
#include <mach_rfs.h>
#include <dfstrace.h>

#ifndef	vnode
#include <vfs/vnode.h>
#endif	vnode
#ifndef	DTYPE_VNODE
#include <vfs/vfs.h>
#endif	DTYPE_VNODE
#ifndef	pn_peekchar
#include <vfs/pathname.h>
#endif	pn_peekchar

#define	CLEAR_INODE_FLAGS(ip)	((ip)->i_flag &= (IROOT|ITEXT|ISHLOCK|IEXLOCK|ILWAIT))

#define	CLEAR_VNODE_FLAGS(vp)	((vp)->v_flag &= ~(VROOT|VTEXT|VSHLOCK|VEXLOCK|VLWAIT))

#define	FINISH_WITH_INODE(ip)	VN_RELE(ip)

#define	UNLOCK_INODE(ip)

#define	LOCK_INODE(ip)

#define	RELEASE_INODE(ip)	VN_RELE(ip)

#define	CHECK_MOUNT_DEV(mp, dev, fs) \
MACRO_BEGIN \
	(mp) = getmp(dev); \
	if ((mp) == NULL) \
		panic("iget: bad dev\n"); \
	if ((mp)->m_bufp->b_un.b_fs != (fs)) \
		panic("iget: bad fs"); \
MACRO_END

#define	INIT_INODE_OPS(ip) 	(ip)->i_vops = &ufs_vnodeops

#define	CHECK_MOUNT_TABLE(ip)

#define	RELEASE_INODE_CHECK(ip, check) \
MACRO_BEGIN \
	if ((ip)->i_flag&ILOCKED) \
		panic("ufs_inactive"); \
	(check) = ((ip)->i_fs->fs_ronly == 0); \
MACRO_END

#define	STAT_INODE(ip, ub)	vno_stat(ip, ub)

#define	LOCK_FILE(fp, how)	vno_bsd_lock(fp, how)

#define	UNLOCK_FILE(fp, how)	vno_bsd_unlock(fp, how)

#ifdef	__STDC__
#define	INODE_TYPE(ip, typ)	((ITOV(ip)->v_mode&VFMT) == V##typ)
#else
#define	INODE_TYPE(ip, typ)	((ITOV(ip)->v_mode&VFMT) == V/**/typ)
#endif

#define	REFERENCE_INODE(ip)	((ip)->i_flag |= IREF)

#define	MARK_INODE_MODIFIED(ip)	imark(ip, ICHG)

#define	CHG_INODE(ip)		imark(ip, ICHG)

#define	CHGUPD_INODE(ip)	imark(ip, (ICHG|IUPD))

#define	MODIFY_INODE(ip)	imark(ip, (ICHG|IUPD|IACC))

#define	UPDATE_INODE(ip, flag)	iupdat(ip, &time, &time, flag)

#define	INODE_DEV_TYPE		struct inode *

#define	INODE_DEV(ip)		(ip)->i_devp

#define	INODE_RDEV(ip)		(ITOV(ip)->v_rdev)

#define	BUF_FOR_INODE(bp, ip)	((bp)->b_vp == (ip)->i_devp)

#define	FLUSH_BLOCK(ip, bn, bs)	blkflush((ip)->i_devp, bn, (long)bs)

#define	BFLUSH_ALL		bflush((struct inode *) 0)

#define	INCR_INODE(ip)		VN_HOLD(ITOV(ip))

#define	DECR_INODE(ip)

#ifdef	__STDC__
#define	INODE_ACCESS(ip, acc)	(VOP_ACCESS(ITOV(ip), V##acc, u.u_identity))
#else
#define	INODE_ACCESS(ip, acc)	(VOP_ACCESS(ITOV(ip), V/**/acc, u.u_identity))
#endif

#define	INODE_LOCKED(ip)	(((ip)->i_flag&ILOCKED) != 0)

#define	INODE_REFERENCED(ip)	(((ip)->i_flag&IREF) != 0)

#define	INODE_CHANGED(ip)	(((ip)->i_flag&(IACC|IUPD|ICHG)) != 0)

#define	CHANGE_INODE(ip, ta, tm)

#define	UNCHANGE_INODE(ip)	(ip)->i_flag &= ~(IUPD|IACC|ICHG)

#define	PURGE_INODE_FREELIST \
MACRO_BEGIN \
	while (ifreeh == NULL) { \
		if (dnlc_purge1() == 0) { \
			break; \
		} \
	} \
MACRO_END

#define	INCR_INODE_GEN(ip)	(ip)->i_gen++

#define	INIT_DEV_MOUNT(ip, mp)	(ip)->i_devp = (mp)->m_devp

#define	INVALIDATE_CACHE(ip)

#define	INIT_DIRECTORY(ip, val)	(ip)->i_diroff = val

#define	INIT_INCR_INODE(ip)

#define	NO_DISK_QUOTA(ip)

#define	DONT_USE_INODE(ip) \
MACRO_BEGIN \
	iunlock(ip); \
	irele(ip); \
MACRO_END

#define	INITIALIZE_INODE(ip, mp) \
MACRO_BEGIN \
	VN_INIT(ITOV(ip), (mp)->m_vfsp, ((ip)->i_mode&IFMT), (ip)->i_rdev); \
	if (ino == (ino_t)ROOTINO) { \
		ITOV(ip)->v_flag |= VROOT; \
	} \
MACRO_END

#define	INODE_QUOTA(ip)		getinoquota(ip)

#define BMAP(ip, bn, rw, size)	bmap(ip, bn, rw, size, 0)

#define	QUOTA_DEV(ip)		(VFSTOM(ITOV(ip)->v_vfsp))

#define	RESTART_QUOTA(uid)

#define	GET_FD_FILE(fd, fp) \
MACRO_BEGIN \
	u.u_error = getvnodefp(fd, &(fp)); \
	if (u.u_error) \
		return; \
MACRO_END

#define	RDWRI(a,b,c,d,e,f,g)	vn_rdwr(a,b,c,d,e,f,IO_UNIT,g)

#define	SETUP_ROOTFS() \
MACRO_BEGIN \
	vfs_mountroot(); \
	boottime = time; \
MACRO_END

#define	NAME_CACHE_INIT		dnlc_init

#define	INITIALIZE_VFS		vfs_init()

#define	INITIALIZE_QUOTA(p)

#define	APPEND_TO_INODE(ip, ptr, len) \
MACRO_BEGIN \
	u.u_error = \
	    vn_rdwr(UIO_WRITE, ip, ptr, len, 0, UIO_SYSSPACE, \
		    IO_UNIT|IO_APPEND, (int *)0); \
MACRO_END

#define	CHECK_FREESPACE(ip, level, cmp) \
MACRO_BEGIN \
	struct statfs sb; \
	(void)VFS_STATFS(ITOV(ip)->v_vfsp, &sb); \
	(cmp) = sb.f_bavail - ((level) * sb.f_blocks / 100); \
MACRO_END

#define	FS_READ_ONLY(ip)	0

#define	PATH_TO_INODE(path, ip) \
MACRO_BEGIN \
	u.u_error = \
	    lookupname(path, UIO_USERSPACE, FOLLOW_LINK, \
		       (struct inode **)0, &(ip)); \
	if (u.u_error) \
		return; \
MACRO_END

#if DFSTRACE > 0
#define	BIND_INODE(path, ip) \
MACRO_BEGIN \
	struct vattr vattr; \
        vattr_null(&vattr); \
        vattr.va_mode = VSOCK | 0777; \
        error = vn_create(path, UIO_SYSSPACE, &vattr, \
			  EXCL, 0, &(ip), 0); \
        if (error) { \
                if (error == EEXIST) \
                        return(EADDRINUSE); \
		return(error); \
	} \
MACRO_END
#else DFSTRACE
#define	BIND_INODE(path, ip) \
MACRO_BEGIN \
	struct vattr vattr; \
        vattr_null(&vattr); \
        vattr.va_mode = VSOCK | 0777; \
        error = vn_create(path, UIO_SYSSPACE, &vattr, \
			  EXCL, 0, &(ip)); \
        if (error) { \
                if (error == EEXIST) \
                        return(EADDRINUSE); \
		return(error); \
	} \
MACRO_END
#endif DFSTRACE

#define	CONNECT_TO_INODE(path, ip) \
MACRO_BEGIN \
	error = \
	    lookupname(path, UIO_SYSSPACE, FOLLOW_LINK, \
		       (struct inode **)0, &(ip)); \
	if (error) \
		return(error); \
MACRO_END

#if DFSTRACE > 0
#define	CREATE_CORE_FILE(ip) \
MACRO_BEGIN \
	struct vattr vattr; \
	vattr_null(&vattr); \
	vattr.va_mode = VREG | 0644; \
	u.u_error = \
	    vn_create("core", UIO_SYSSPACE, &vattr, NONEXCL, VWRITE, &ip, 0); \
	if (u.u_error) \
		return (0); \
	if (vattr.va_nlink != 1) { \
		u.u_error = EFAULT; \
		goto out; \
	} \
MACRO_END
#else DFSTRACE
#define	CREATE_CORE_FILE(ip) \
MACRO_BEGIN \
	struct vattr vattr; \
	vattr_null(&vattr); \
	vattr.va_mode = VREG | 0644; \
	u.u_error = \
	    vn_create("core", UIO_SYSSPACE, &vattr, NONEXCL, VWRITE, &ip); \
	if (u.u_error) \
		return (0); \
	if (vattr.va_nlink != 1) { \
		u.u_error = EFAULT; \
		goto out; \
	} \
MACRO_END
#endif DFSTRACE

#define	NAME_LOOKUP_DECL	struct pathname pathname

#define	NAME_CLOOKUP_DECL	struct pathname pathname

#define	NAME_LOOKUP(name, ip) \
MACRO_BEGIN \
    (void) extended_lookupname(name, UIO_USERSPACE, FOLLOW_LINK, \
		0, &(ip), 1, &pathname); \
MACRO_END

#define	NAME_CLOOKUP(name, ip) \
MACRO_BEGIN \
	u.u_error = extended_lookupname(name, UIO_SYSSPACE, \
		FOLLOW_LINK, 0, &(ip), 1, &pathname); \
MACRO_END

#define	NAME_LOOKUP_LENGTH()	pathname.pn_pathlen

#define	NAME_LOOKUP_PATH	pathname.pn_path

#define	NAME_LOOKUP_FREE() \
MACRO_BEGIN \
	pn_free(&pathname); \
MACRO_END

#define	GET_ROOT_INODE(mi, pip) \
MACRO_BEGIN \
	struct vfs *vfsp; \
	vfsp = mount[mi].m_vfsp; \
	if (VFS_ROOT(vfsp, &(pip))) \
		(pip) = NULL; \
MACRO_END

#define	GET_ROOT_PAGING_INODE(mi, ip) \
MACRO_BEGIN \
	struct vfs *vfsp; \
	struct inode *pip; \
	vfsp = mount[mi].m_vfsp; \
	if (VFS_ROOT(vfsp, &(pip))) \
		(ip) = NULL; \
	else { \
		(ip) = ialloc(pip, (ino_t)0, 0); \
		VN_RELE(pip); \
	} \
MACRO_END

#define	FS_FREE_SPACE(fs, n) \
MACRO_BEGIN \
	struct statfs fstat; \
	VFS_STATFS((struct vfs *)(fs), &fstat); \
	(n) = fstat.f_bfree * fstat.f_bsize; \
MACRO_END

#define	FS_PAGING_FREE_SPACE(fs, n, pass) \
MACRO_BEGIN \
	struct statfs fstat; \
	VFS_STATFS((struct vfs *)(fs), &fstat); \
	(n) = fstat.f_bfree * fstat.f_bsize; \
MACRO_END

#define	NO_MOUNT_DEVICE(mp)	((mp)->m_devp == NULL)

#define	MOUNT_TO_FS(mp)		((struct fs *)((mp)->m_vfsp))

#define	FS_READONLY(fs)		((((struct vfs *)(fs))->vfs_flag & VFS_RDONLY) != 0)

#define	FS_BSIZE(fs)		(((struct vfs *)(fs))->vfs_bsize)

#define	LOOKUP_ROOT_NAME(name, ip) \
MACRO_BEGIN \
	(void) lookupname(name, UIO_SYSSPACE, NO_FOLLOW, 0, &(ip)); \
MACRO_END

#if DFSTRACE > 0
#define	DECLARE_EXECVE_LOCALS \
	struct vattr vattr; \
	struct pathname pn; \
	char dfs_done_logging = 0; \
	char tracewason = 0; \
	int dfs_pn_error = 0; \
	struct pathname dfs_pn
#else   DFSTRACE
#define	DECLARE_EXECVE_LOCALS \
	struct vattr vattr; \
	struct pathname pn
#endif  DFSTRACE

#if DFSTRACE > 0
#if	MACH_RFS
#define	LOOKUP_EXECVE_NAME(name, ip) \
MACRO_BEGIN \
	u.u_error = pn_get(name, UIO_USERSPACE, &pn); \
	if (u.u_error) { \
		if (traceon) \
			dfs_log(DFS_EXECVE, &dfs_done_logging, UIO_USERSPACE, \
				name, NULL, 0); \
  		return; \
	} \
	u.u_error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &(ip)); \
	if (u.u_error || (ip) == 0) { \
		if (traceon) \
			dfs_log(DFS_EXECVE, &dfs_done_logging, UIO_USERSPACE, \
				name, NULL, 0); \
		pn_free(&pn); \
		return; \
	} \
	if (traceon) { \
		dfs_pn_error = pn_get(name, UIO_USERSPACE, &dfs_pn); \
		tracewason = 1; \
	} \
MACRO_END
#else	MACH_RFS
#define	LOOKUP_EXECVE_NAME(name, ip) \
MACRO_BEGIN \
	u.u_error = pn_get(name, UIO_USERSPACE, &pn); \
	if (u.u_error) { \
		if (traceon) \
			dfs_log(DFS_EXECVE, &dfs_done_logging, UIO_USERSPACE, \
				name, NULL, 0); \
  		return; \
	} \
	u.u_error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &(ip)); \
	if (u.u_error || (ip) == 0) { \
		if (traceon) \
			dfs_log(DFS_EXECVE, &dfs_done_logging, UIO_USERSPACE, \
				name, NULL, 0); \
		pn_free(&pn); \
		return; \
	} \
	if (traceon) { \
		dfs_pn_error = pn_get(name, UIO_USERSPACE, &dfs_pn); \
		tracewason = 1; \
	} \
MACRO_END
#endif	MACH_RFS
#else   DFSTRACE
#if	MACH_RFS
#define	LOOKUP_EXECVE_NAME(name, ip) \
MACRO_BEGIN \
	u.u_error = pn_get(name, UIO_USERSPACE, &pn); \
	if (u.u_error) \
  		return; \
	u.u_error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &(ip)); \
	if (u.u_error || (ip) == 0) { \
		pn_free(&pn); \
		return; \
	} \
MACRO_END
#else	MACH_RFS
#define	LOOKUP_EXECVE_NAME(name, ip) \
MACRO_BEGIN \
	u.u_error = pn_get(name, UIO_USERSPACE, &pn); \
	if (u.u_error) \
  		return; \
	u.u_error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &(ip)); \
	if (u.u_error || (ip) == 0) { \
		pn_free(&pn); \
		return; \
	} \
MACRO_END
#endif	MACH_RFS
#endif  DFSTRACE

#define	VERIFY_SETUID(ip) \
MACRO_BEGIN \
	if (u.u_error = VOP_GETATTR(ITOV(ip), &vattr, u.u_identity)) \
		goto bad; \
	if ((ITOV(ip)->v_vfsp->vfs_flag & VFS_NOSUID) == 0) { \
		if (vattr.va_mode & (VSUID | VSGID)) { \
			if (task_secure(current_task())) { \
				if (vattr.va_mode & VSUID) \
					uid = vattr.va_uid; \
				if (vattr.va_mode & VSGID) \
					gid = vattr.va_gid; \
			} else { \
				uprintf("%s: privileges disabled because of outstanding IPC access to task\n", \
					u.u_comm); \
			} \
		} \
	} else if ((vattr.va_mode & VSUID) || (vattr.va_mode & VSGID)) { \
		struct pathname tmppn; \
		u.u_error = pn_get(uap->fname, UIO_USERSPACE, &tmppn); \
		if (u.u_error) \
			goto bad; \
		uprintf("%s: Setuid execution not allowed\n", tmppn.pn_buf); \
		pn_free(&tmppn); \
	} \
MACRO_END

#define	CHECK_ACCESS(ip, acc)	(u.u_error = VOP_ACCESS(ITOV(ip), acc, u.u_identity))

#define	INODE_MODE(ip)		(vattr.va_mode)

#if	MACH_RFS
#define	LOOKUP_SHELL_NAME(name, ip) \
MACRO_BEGIN \
		if (u.u_error = pn_set(&pn, name)) \
			goto bad; \
		u.u_error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &(ip)); \
		if (u.u_error) \
			goto bad; \
		if (u.u_error = VOP_GETATTR(ITOV(ip), &vattr, u.u_identity)) \
			goto bad; \
MACRO_END
#else	MACH_RFS
#define	LOOKUP_SHELL_NAME(name, ip) \
MACRO_BEGIN \
		if (u.u_error = pn_set(&pn, name)) \
			goto bad; \
		u.u_error = lookuppn(&pn, FOLLOW_LINK, (struct vnode **)0, &(ip)); \
		if (u.u_error) \
			goto bad; \
		if (u.u_error = VOP_GETATTR(ITOV(ip), &vattr, u.u_identity)) \
			goto bad; \
MACRO_END
#endif	MACH_RFS

#define	EXECVE_SHARG		pn.pn_buf

#define	SET_COMM_NAME() \
MACRO_BEGIN \
	if (pn.pn_pathlen > MAXCOMLEN) \
		pn.pn_pathlen = MAXCOMLEN; \
	bcopy((caddr_t)pn.pn_buf, (caddr_t)u.u_comm, \
	      (unsigned)(pn.pn_pathlen + 1)); \
MACRO_END

#if DFSTRACE > 0
#define EXECVE_FREE_PATH() \
MACRO_BEGIN \
	pn_free(&pn); \
	if (tracewason && !dfs_pn_error) pn_free(&dfs_pn); \
MACRO_END
#else DFSTRACE	
#define	EXECVE_FREE_PATH()	pn_free(&pn)
#endif DFSTRACE
