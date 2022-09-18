/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	inode_macros.h,v $
 * Revision 2.5  90/08/30  11:00:06  bohman
 * 	Changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.4  89/09/05  20:41:58  jsb
 * 	Fixed bug in CONNECT_TO_INODE which returned incorrect error code.
 * 	[89/09/05  16:24:46  jsb]
 * 
 * Revision 2.3  89/05/11  15:39:59  gm0w
 * 	Minor fixes for NBC code from rfr.
 * 	[89/05/11            gm0w]
 * 
 * Revision 2.2  89/04/22  15:24:16  gm0w
 * 	Created macros for manipulating inode and filesystems independent
 * 	of VFS/non-VFS configurations.  These are the non-VFS variants.
 * 	[89/04/14            gm0w]
 * 
 */
/*
 *  CMU Macros for modifying inode reference counts -
 *  used to check for consistency at each reference.
 *
 *  The idecr_chk() macro is defined such that it doesn't decrement the
 *  reference count when already zero.  This is in order to avoid the nested
 *  iincr panic which would otherwise occur when update() tries to sync the
 *  inode before halting and increments the count back to zero.
 *
 *  The panic message strings are initialized variables rather than constant
 *  strings since they are potentially used in many places.
 */

extern char *PANICMSG_IINCR;
extern char *PANICMSG_IDECR;

#define iincr_chk(ip)					\
MACRO_BEGIN						\
	if (++(ip)->i_count == 0)			\
		panic(PANICMSG_IINCR);			\
MACRO_END

#define idecr_chk(ip)					\
MACRO_BEGIN						\
	if ((ip)->i_count != 0)				\
		(ip)->i_count--;			\
	else						\
		panic(PANICMSG_IDECR);			\
MACRO_END

#define	CLEAR_INODE_FLAGS(ip)	((ip)->i_flag = 0)

#define	CLEAR_VNODE_FLAGS(ip)	((ip)->i_flag = 0)

#define	FINISH_WITH_INODE(ip)	iput(ip)

#define	UNLOCK_INODE(ip)	iunlock(ip)

#define	LOCK_INODE(ip)		ilock(ip)

#define	RELEASE_INODE(ip)	irele(ip)

#define	CHECK_MOUNT_DEV(mp, dev, fs)

#define	INIT_INODE_OPS(ip)

#if	VICE
#define	CHECK_MOUNT_TABLE(ip) \
MACRO_BEGIN \
	if ((ip->i_flag&IMOUNT) != 0) { \
		for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) \
			if(mp->m_inodp == ip) { \
				if (mp->m_remote) { \
					u.u_rmt_dev = mp->m_dev; \
					if (!u.u_rmt_requested) \
						u.u_error = EINVAL; \
					return NULL; \
				} \
				dev = mp->m_dev; \
				fs = mp->m_bufp->b_un.b_fs; \
				ino = ROOTINO; \
				goto loop; \
			} \
		panic("no imt"); \
	} \
MACRO_END
#else	VICE
#define	CHECK_MOUNT_TABLE(ip) \
MACRO_BEGIN \
	if ((ip->i_flag&IMOUNT) != 0) { \
		for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++) \
			if(mp->m_inodp == ip) { \
				dev = mp->m_dev; \
				fs = mp->m_bufp->b_un.b_fs; \
				ino = ROOTINO; \
				goto loop; \
			} \
		panic("no imt"); \
	} \
MACRO_END
#endif	VICE

#define	RELEASE_INODE_CHECK(ip, check) \
MACRO_BEGIN \
	if ((ip)->i_count != 1 && !((ip)->i_flag & ILOCKED)) { \
		ITIMES(ip, &time, &time);\
		DECR_INODE(ip); \
		return; \
	} \
	(check) = ((ip)->i_count == 1); \
MACRO_END

#define	STAT_INODE(ip, ub)	ino_stat(ip, ub)

#define	LOCK_FILE(fp, how)	ino_lock(fp, how)

#define	UNLOCK_FILE(fp, how)	ino_unlock(fp, how)

#ifdef	__STDC__
#define	INODE_TYPE(ip, typ)	(((ip)->i_mode&IFMT) == IF##typ)
#else
#define	INODE_TYPE(ip, typ)	(((ip)->i_mode&IFMT) == IF/**/typ)
#endif

#define	REFERENCE_INODE(ip)

#define	MARK_INODE_MODIFIED(ip)	(ip)->i_flag |= IMOD

#define	CHG_INODE(ip)		(ip)->i_flag |= ICHG

#define	CHGUPD_INODE(ip)	(ip)->i_flag |= (ICHG|IUPD)

#define	MODIFY_INODE(ip)	(ip)->i_flag |= (ICHG|IUPD|IACC)

#define	UPDATE_INODE(ip, flag)	iupdat(ip, &time, &time, flag)

#define	INODE_DEV_TYPE		dev_t

#define	INODE_DEV(ip)		(ip)->i_dev

#define	INODE_RDEV(ip)		((ip)->i_rdev)

#define	BUF_FOR_INODE(bp, ip)	((bp)->b_dev == (ip)->i_dev)

#define	FLUSH_BLOCK(ip, bn, bs)	blkflush((ip)->i_dev, bn, bs)

#define	BFLUSH_ALL		bflush(NODEV)

#define	INCR_INODE(ip)		iincr_chk(ip)

#define	DECR_INODE(ip)		idecr_chk(ip)

#ifdef	__STDC__
#define	INODE_ACCESS(ip, acc)	(access(ip, I##acc))
#else
#define	INODE_ACCESS(ip, acc)	(access(ip, I/**/acc))
#endif

#define	INODE_LOCKED(ip)	(((ip)->i_flag&ILOCKED) != 0)

#define	INODE_REFERENCED(ip)	((ip)->i_count != 0)

#define	INODE_CHANGED(ip)	(((ip)->i_flag&(IMOD|IACC|IUPD|ICHG)) != 0)

#define	CHANGE_INODE(ip, ta, tm) \
MACRO_BEGIN \
	if ((ip)->i_flag&IACC) \
		(ip)->i_atime = (ta)->tv_sec; \
	if ((ip)->i_flag&IUPD) \
		(ip)->i_mtime = (tm)->tv_sec; \
	if ((ip)->i_flag&ICHG) \
		(ip)->i_ctime = time.tv_sec; \
MACRO_END

#define	UNCHANGE_INODE(ip)	(ip)->i_flag &= ~(IUPD|IACC|ICHG|IMOD)

#define	PURGE_INODE_FREELIST

#define	INCR_INODE_GEN(ip)

#define	INIT_DEV_MOUNT(ip, mp)

#define	INVALIDATE_CACHE(ip)	cacheinval(ip)

#define	INIT_DIRECTORY(ip, val)

#define	INIT_INCR_INODE(ip)	iincr_chk(ip)

#define	NO_DISK_QUOTA(ip)	(ip)->i_dquot = NODQUOT

#define	DONT_USE_INODE(ip)	iput(ip)

#define	INITIALIZE_INODE(ip, mp)

#define	INODE_QUOTA(ip)		inoquota(ip)

#define BMAP(ip, bn, rw, size)	bmap(ip, bn, rw, size)

#define	QUOTA_DEV(ip)		((ip)->i_dev)

#define	RESTART_QUOTA(uid) \
MACRO_BEGIN \
	qclean(); \
	qstart(getquota(uid, 0, 0)); \
MACRO_END

#define	GET_FD_FILE(fd, fp)	GETF(fp, fd)

#define	RDWRI(a,b,c,d,e,f,g)	rdwri(a,b,c,d,e,f,g)

#define	SETUP_ROOTFS() \
MACRO_BEGIN \
	fs = mountfs(rootdev, 0, (struct inode *)0); \
	if (fs == 0) \
		panic("iinit"); \
	bcopy("/", fs->fs_fsmnt, 2); \
	inittodr(fs->fs_time); \
	boottime = time; \
	rootdir = iget(rootdev, fs, (ino_t)ROOTINO); \
	iunlock(rootdir); \
	u.u_cdir = iget(rootdev, fs, (ino_t)ROOTINO); \
	iunlock(u.u_cdir); \
	u.u_rdir = NULL; \
MACRO_END

#define	NAME_CACHE_INIT		nchinit

#define	INITIALIZE_VFS

#define	INITIALIZE_QUOTA(p)	p->p_quota = u.u_quota = getquota(0, 0, Q_NDQ)

#define	APPEND_TO_INODE(ip, ptr, len) \
MACRO_BEGIN \
	off_t siz = ip->i_size; \
	u.u_error = 0; \
	u.u_error = \
	    rdwri(UIO_WRITE, ip, ptr, len, siz, UIO_SYSSPACE, (int *)0); \
	if (u.u_error) \
		itrunc(ip, (u_long)siz); \
MACRO_END

#define	CHECK_FREESPACE(ip, level, cmp) \
MACRO_BEGIN \
	struct fs *fs; \
	fs = (ip)->i_fs; \
	(cmp) = freespace(fs, fs->fs_minfree + (level)); \
MACRO_END

#define	FS_READ_ONLY(ip)	((ip)->i_fs->fs_ronly)

#define	PATH_TO_INODE(path, ip) \
MACRO_BEGIN \
	struct nameidata *ndp = &u.u_nd; \
	ndp->ni_nameiop = LOOKUP | FOLLOW; \
	ndp->ni_segflg = UIO_USERSPACE; \
	ndp->ni_dirp = path; \
	(ip) = namei(ndp); \
	if ((ip) == NULL) \
		return; \
MACRO_END

#define	BIND_INODE(path, ip) \
MACRO_BEGIN \
	struct nameidata *ndp = &u.u_nd; \
	ndp->ni_dirp = path; \
	ndp->ni_nameiop = CREATE | FOLLOW; \
	ndp->ni_segflg = UIO_SYSSPACE; \
	(ip) = namei(ndp); \
	if ((ip) != NULL) { \
		FINISH_WITH_INODE(ip); \
		return(EADDRINUSE); \
	} \
	if (error = u.u_error) { \
		u.u_error = 0; \
		return(error); \
	} \
	ip = maknode(IFSOCK|0777, ndp); \
	if (ip == NULL) { \
		error = u.u_error; \
		u.u_error = 0; \
		return(error); \
	} \
MACRO_END

#define	CONNECT_TO_INODE(path, ip) \
MACRO_BEGIN \
	struct nameidata *ndp = &u.u_nd; \
	ndp->ni_dirp = path; \
	ndp->ni_nameiop = LOOKUP | FOLLOW; \
	ndp->ni_segflg = UIO_SYSSPACE; \
	(ip) = namei(ndp); \
	if ((ip) == NULL) { \
		error = u.u_error; \
		u.u_error = 0; \
		return (error); \
	} \
	if (access(ip, IWRITE)) { \
		error = u.u_error; \
		u.u_error = 0; \
		FINISH_WITH_INODE(ip); \
		return (error); \
	} \
MACRO_END

#if	VICE
#define	CREATE_CORE_FILE(ip) \
MACRO_BEGIN \
	struct nameidata *ndp = &u.u_nd; \
	ndp->ni_nameiop = CREATE | FOLLOW; \
	ndp->ni_segflg = UIO_SYSSPACE; \
	ndp->ni_dirp = "core"; \
	(ip) = namei(ndp); \
	u.u_rmt_code = 0; \
	if ((ip) == NULL) { \
		if (u.u_error != EVICEOP) { \
			if (u.u_error) \
				return (0); \
			(ip) = maknode(0644, ndp); \
			if ((ip)==NULL) \
				return (0); \
		} else { \
			int fd = u.u_r.r_val1; \
			u.u_error = 0; \
			if (((unsigned) fd >= NOFILE) || \
			    ((fp = u.u_ofile[fd]) == NULL)) { \
				u.u_error = EBADF; \
				return(0); \
			} \
			(ip) = (struct inode *)fp->f_data; \
			(ip)->i_count++; \
			u.u_ofile[fd] = NULL; \
		} \
	} \
	if (access(ip, IWRITE) || \
	   ((ip)->i_mode&IFMT) != IFREG || \
	   (ip)->i_nlink != 1) { \
		u.u_error = EFAULT; \
		goto out; \
	} \
	itrunc(ip, (u_long)0); \
MACRO_END
#else	VICE
#define	CREATE_CORE_FILE(ip) \
MACRO_BEGIN \
	struct nameidata *ndp = &u.u_nd; \
	ndp->ni_nameiop = CREATE | FOLLOW; \
	ndp->ni_segflg = UIO_SYSSPACE; \
	ndp->ni_dirp = "core"; \
	(ip) = namei(ndp); \
	if ((ip) == NULL) { \
		if (u.u_error) \
			return (0); \
		(ip) = maknode(0644, ndp); \
		if ((ip)==NULL) \
			return (0); \
	} \
	if (access(ip, IWRITE) || \
	   ((ip)->i_mode&IFMT) != IFREG || \
	   (ip)->i_nlink != 1) { \
		u.u_error = EFAULT; \
		goto out; \
	} \
	itrunc(ip, (u_long)0); \
MACRO_END
#endif	VICE

#define	NAME_LOOKUP_DECL	struct nameidata ndata, *ndp = &ndata

#define	NAME_CLOOKUP_DECL	struct nameidata *ndp = &u.u_nd

#define	NAME_LOOKUP(name, ip) \
MACRO_BEGIN \
    ndata.ni_iov = &ndata.ni_iovec; \
    ndata.ni_nameiop = LOOKUP | FOLLOW | KEEPNAMEBUF; \
    ndata.ni_segflg = UIO_USERSPACE; \
    ndata.ni_dirp = name; \
    (ip) = namei(&ndata); \
MACRO_END

#define	NAME_CLOOKUP(name, ip) \
MACRO_BEGIN \
	ndp->ni_nameiop = LOOKUP | FOLLOW | OKREMOTE | KEEPNAMEBUF; \
	ndp->ni_segflg  = UIO_SYSSPACE; \
	ndp->ni_dirp    = name; \
	(ip) = cnamei(ndp); \
MACRO_END

#define	NAME_LOOKUP_LENGTH()	rfsNameLength(&ndata)

#define	NAME_LOOKUP_PATH	ndp->ni_dirp

#define	NAME_LOOKUP_FREE() \
MACRO_BEGIN \
	if ((ndp->ni_nameiop&KEEPNAMEBUF) == 0) \
		nameifree(*ni_nbpp(ndp)); \
MACRO_END

#define	GET_ROOT_INODE(mi, pip) \
MACRO_BEGIN \
	(pip) = iget(mount[mi].m_dev, mount[mi].m_bufp->b_un.b_fs, ROOTINO); \
MACRO_END

#define	GET_ROOT_PAGING_INODE(mi, ip) \
MACRO_BEGIN \
	struct inode root_dummy; \
	root_dummy.i_fs = mount[mi].m_bufp->b_un.b_fs; \
	root_dummy.i_dev = mount[mi].m_dev; \
	(ip) = ialloc(&root_dummy, (ino_t)0, 0); \
MACRO_END

#define	FS_FREE_SPACE(fs, n) \
MACRO_BEGIN \
	(n) = freespace((fs), (fs)->fs_minfree); \
MACRO_END

#define	FS_PAGING_FREE_SPACE(fs, n, pass) \
MACRO_BEGIN \
	(n) = freespace(fs, ((pass) <= 4) ? (fs)->fs_minfree : 0); \
MACRO_END

#define	NO_MOUNT_DEVICE(mp)	((mp)->m_dev == NODEV)

#define	MOUNT_TO_FS(mp)		((mp)->m_bufp->b_un.b_fs)

#define	FS_READONLY(fs)		((fs)->fs_ronly != 0)

#define	FS_BSIZE(fs)		((fs)->fs_bsize)

#define	LOOKUP_ROOT_NAME(name, ip) \
MACRO_BEGIN \
	struct nameidata *ndp = &u.u_nd; \
	u.u_error = 0; \
	ndp->ni_nameiop = LOOKUP; \
	ndp->ni_segflg = UIO_SYSSPACE; \
	ndp->ni_dirp = (name); \
	(ip) = namei(ndp); \
MACRO_END

#define	DECLARE_EXECVE_LOCALS \
	char cfname[MAXCOMLEN+1]; \
	register struct nameidata *ndp = &u.u_nd

#if	VICE
#define	LOOKUP_EXECVE_NAME(name, ip) \
MACRO_BEGIN \
	ndp->ni_nameiop = LOOKUP | FOLLOW; \
	ndp->ni_segflg = UIO_USERSPACE; \
	ndp->ni_dirp = (name); \
	u.u_rmt_requested = 1; \
	if (((ip) = namei(ndp)) == NULL) \
		if (u.u_error == EVICEOP) { \
			int	fd = u.u_r.r_val1; \
			u.u_error = 0; \
		 	GETF(fp, fd); \
			(ip) = (struct inode *)fp->f_data; \
			(ip)->i_count++; \
			u.u_ofile[fd] = NULL; \
		} else \
			return; \
MACRO_END
#else	VICE
#define	LOOKUP_EXECVE_NAME(name, ip) \
MACRO_BEGIN \
	ndp->ni_nameiop = LOOKUP | FOLLOW; \
	ndp->ni_segflg = UIO_USERSPACE; \
	ndp->ni_dirp = (name); \
	if (((ip) = namei(ndp)) == NULL) \
		return; \
MACRO_END
#endif	VICE

#define	VERIFY_SETUID(ip) \
MACRO_BEGIN \
	if ((ip)->i_mode & (ISUID | ISGID)) { \
		if (task_secure(current_task())) { \
			if ((ip)->i_mode & ISUID) \
				uid = (ip)->i_uid; \
			if ((ip)->i_mode & ISGID) \
				gid = (ip)->i_gid; \
		} else { \
			uprintf("%s: privileges disabled because of outstanding IPC access to task\n", \
				u.u_comm); \
		} \
	} \
MACRO_END

#define	CHECK_ACCESS(ip, acc)	access(ip, acc)

#define	INODE_MODE(ip)		((ip)->i_mode)

#if	VICE
#define	LOOKUP_SHELL_NAME(name, ip) \
MACRO_BEGIN \
		if (fp) { \
			closef(fp); \
			fp = NULL; \
		} \
		ndp->ni_nameiop = LOOKUP | FOLLOW; \
		ndp->ni_segflg = UIO_SYSSPACE; \
		ndp->ni_dirp = (name); \
		u.u_rmt_requested = 1; \
		(ip) = namei(ndp); \
		if (ip == NULL) \
		if (u.u_error == EVICEOP) \
		{ \
			int	fd = u.u_r.r_val1; \
			u.u_error = 0; \
		 	GETF(fp, fd); \
			ip = (struct inode *)fp->f_data; \
			ip->i_count++; \
			u.u_ofile[fd] = NULL; \
		} \
		else \
			return; \
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)cfname, \
		    MAXCOMLEN); \
		cfname[MAXCOMLEN] = '\0'; \
MACRO_END
#else	VICE
#define	LOOKUP_SHELL_NAME(name, ip) \
MACRO_BEGIN \
		ndp->ni_nameiop = LOOKUP | FOLLOW; \
		ndp->ni_segflg = UIO_SYSSPACE; \
		ndp->ni_dirp = (name); \
		ip = namei(ndp); \
		if (ip == NULL) \
			return; \
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)cfname, \
		    MAXCOMLEN); \
		cfname[MAXCOMLEN] = '\0'; \
MACRO_END
#endif	VICE

#define	EXECVE_SHARG		cfname

#define	SET_COMM_NAME() \
MACRO_BEGIN \
	if (indir) \
		bcopy((caddr_t)cfname, (caddr_t)u.u_comm, MAXCOMLEN); \
	else { \
		if (ndp->ni_dent.d_namlen > MAXCOMLEN) \
			ndp->ni_dent.d_namlen = MAXCOMLEN; \
		bcopy((caddr_t)ndp->ni_dent.d_name, (caddr_t)u.u_comm, \
		    (unsigned)(ndp->ni_dent.d_namlen + 1)); \
	} \
MACRO_END

#define	EXECVE_FREE_PATH()
