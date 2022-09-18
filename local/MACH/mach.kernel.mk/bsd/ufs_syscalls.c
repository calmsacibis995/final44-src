/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	ufs_syscalls.c,v $
 * Revision 2.16  90/03/27  18:27:35  dlb
 * 	Use freefp instead of decrementing count in f_open because fp
 * 	may have to be cleaned up.  Fix from kupfer@orc.olivetti.com.
 * 	[90/03/26            dlb]
 * 
 * Revision 2.15  89/10/10  10:48:05  mwyoung
 * 	Make fast symbolic links an architecture-independent option.
 * 	[89/05/12  16:02:14  mwyoung]
 * 
 * Revision 2.14  89/08/06  13:13:04  gm0w
 * 	Added missing code to subtract the size of the offset pointer
 * 	from the f_offset and return value in getdirentries() for rfs
 * 	directories.
 * 	[89/08/05            gm0w]
 * 
 * Revision 2.13  89/07/30  18:28:54  gm0w
 * 	Added getdirentries support for RFS.
 * 	[89/07/29            gm0w]
 * 
 * Revision 2.12  89/04/22  15:22:41  gm0w
 * 	Changed vm_info to i_vm_info.  Moved xutimes here from cmu_syscalls.c.
 * 	Moved getdirectries here from compat/xxx_syscalls.c.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.11  89/03/10  01:27:39  rpd
 * 	More cleanup.
 * 
 * Revision 2.10  89/03/05  00:40:05  rpd
 * 	Installed comp.4bsd.bugs.ucb-fixes V1.77 (re-fix for chown
 * 	security problem).
 * 	[89/02/13  12:57:16  mja]
 * 
 * Revision 2.9  89/02/26  11:29:54  gm0w
 * 	changed include of CMUCS_RFS to MACH_RFS
 * 	removed includes of cmucs.h and mach.h. Removed
 * 	symbolic link restriction that was dependent on CS_ONLY.
 * 	[89/02/23            mrt]
 * 
 * Revision 2.8  89/01/18  00:44:40  jsb
 * 	Vnode support: changed EREMOTE to ERFSREMOTE.
 * 	[89/01/16  15:22:18  jsb]
 * 
 * Revision 2.7  88/12/19  12:51:48  mja
 * 	Cause iopen() call to return EBUSY if the inode reference count
 * 	is not 1 and the FEXCL mode bit was specified (to correct
 * 	problem with VENUS restarts and in-use i-nodes - requires a
 * 	companion change to VENUS).
 * 	[88/12/05  12:47:58  mja]
 * 
 * Revision 2.6  88/08/24  01:37:03  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Use new CS conditionals.
 * 	[88/08/23            mwyoung]
 * 
 * Revision 2.5  88/07/17  17:48:33  mwyoung
 *	Use new memory object types.
 * 
 * Revision 2.4  88/07/15  15:40:22  mja
 *	Fixed to include <sys/table.h> instead of <sys/syscall.h> for
 *	UMODE_* definitions.
 * 
 * 16-Feb-88  Joseph Boykin (boykin) at Encore Computer Corporation
 *	Added support to create 'fast' symbolic links.
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 * 25-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-style option.
 *
 * 26-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	When a files link count goes to zero be sure the file will no
 *	longer be cached in the object cache.
 *
 *  1-Jun-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added include of "vm/inode_pager.h" to get inode_uncache.
 *
 * 17-Mar-87  David Golub (dbg) at Carnegie-Mellon University
 *	Made igetinode always return something.  De-linted.
 *
 * 12-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged in VICE changes - minor changes in getinode for "proper"
 *	conditional compilation.
 *
 *  3-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use inode_uncache as a more general form of text_uncache.
 *
 * 30-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  corrected handling of Vice files in ftruncate
 *	(a NULL fp was being used previously).
 *
 * 22-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Added proper cleanup in chdirec() for the cases where
 *	we change from an rfs to an Andrew directory (or vice-versa).
 *
 * 23-Dec-86  David L. Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: Make readlink understand Encore (UMAX) fast
 *	symbolic links.
 *
 * 11-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Also make symbolic link check conditional on a run-time switch
 *	if CS_ONLY is selected.
 *
 *  3-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make symbolic link creation restriction conditional on CS_ONLY
 *	as opposed to not MACH_ONLY.  (No sense in singling out Mach in
 *	the regard).
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  installed hooks for ITC/Andrew remote file system.
 *
 * 15-Nov-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Removed unnecessary exclusion of fragment size check in mkdir()
 *	for old-style file systems.
 *
 * 23-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Restored checks for text files still in cache.
 *
 * 10-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  fix mkdir() to also create directories in the
 *	current group rather than that of the parent.
 *
 * 28-Apr-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  correct chown() fix typo introduced in merge so
 *	that it follows symbolic links again.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.  (Left a section for handling the old directory
 *	format out).
 *
 * 21-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  fix bug in copen() which neglected to allow for
 *	another signal interrupting the close following the previous
 *	signal which aborted the open.
 *	[V1(1)]
 *
 * 19-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Modify chdirec() to clear remote current/root
 *	directory state bits.
 *
 * 17-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  Fix chown() system call to follow symbolic links.
 *	[V1(1)].
 *
 * 07-Sep-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CMUCS:  changed to default to 4.1-style inode group
 *	ownership (from effective GID).
 *	[V1(1)]
 *
 * 20-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  enabled remote namei() processing for all
 *	routines in this module;  added hook to remote inode file
 *	descriptor handling in getinode().
 *	[V1(1)]
 *
 */ 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_syscalls.c	7.1 (Berkeley) 6/5/86
 */
 
#include <mach_rfs.h>
#include <mach_fastlink.h>
#include <quota.h>
#include <vice.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/quota.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mount.h>
#include <kern/mfs.h>
#include <builtin/inode_pager.h>
#include <sys/table.h>

#if	VICE
#include <sys/ioctl.h>	/* for pioctl() */
#include <sys/viceioctl.h>	/* for pioctl() */
#endif	VICE

#if	MACH_RFS
/*
 *  Force all namei() calls to permit remote names since this module has
 *  been updated.
 */
#undef	namei
#define namei	rnamei

#endif	MACH_RFS
extern	struct fileops inodeops;
struct	file *getinode();

/*
 * Change current working directory (``.'').
 */
chdir()
{

	chdirec(&u.u_cdir);
}

/*
 * Change notion of root (``/'') directory.
 */
chroot()
{

	if (suser())
		chdirec(&u.u_rdir);
}

/*
 * Common routine for chroot and chdir.
 */
chdirec(ipp)
	register struct inode **ipp;
{
	register struct inode *ip;
	struct a {
		char	*fname;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
#if	MACH_RFS && VICE
	{
		if (u.u_error == EVICEOP) {
			if (ipp == &u.u_cdir)
				u.u_rfs &= ~URFS_CDIR;
			else if (ipp == &u.u_rdir)
				u.u_rfs &= ~URFS_RDIR;
		}
		else if (u.u_error == ERFSREMOTE) {
			if (ipp == &u.u_cdir)
				u.u_rmtWd.dev = NODEV;
		}
		return;
	}
#else	MACH_RFS && VICE
		return;
#endif	MACH_RFS && VICE
	if ((ip->i_mode&IFMT) != IFDIR) {
		u.u_error = ENOTDIR;
		goto bad;
	}
	if (access(ip, IEXEC))
		goto bad;
	IUNLOCK(ip);
	if (*ipp)
		irele(*ipp);
#if	MACH_RFS
	if (ipp == &u.u_cdir)
		u.u_rfs &= ~URFS_CDIR;
	else if (ipp == &u.u_rdir)
		u.u_rfs &= ~URFS_RDIR;
#endif	MACH_RFS
#if	VICE
	if (ipp == &u.u_cdir)
		u.u_rmtWd.dev = NODEV;
#endif	VICE
	*ipp = ip;
	return;

bad:
	iput(ip);
}

/*
 * Open system call.
 */
open()
{
	struct a {
		char	*fname;
		int	mode;
		int	crtmode;
	} *uap = (struct a *) u.u_ap;

	copen(uap->mode-FOPEN, uap->crtmode, uap->fname);
}

/*
 * Creat system call.
 */
creat()
{
	struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;

	copen(FWRITE|FCREAT|FTRUNC, uap->fmode, uap->fname);
}

/*
 * Common code for open and creat.
 * Check permissions, allocate an open file structure,
 * and call the device open routine if any.
 */
copen(mode, arg, fname)
	register int mode;
	int arg;
	caddr_t fname;
{
	register struct inode *ip;
	register struct file *fp;
	register struct nameidata *ndp = &u.u_nd;
	int indx;

	fp = falloc();
	if (fp == NULL)
		return;
	indx = u.u_r.r_val1;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
	if (mode&FCREAT) {
		if (mode & FEXCL)
			ndp->ni_nameiop = CREATE;
		else
			ndp->ni_nameiop = CREATE | FOLLOW;
#if	VICE
		u.u_rmt_requested = 1;
#endif	VICE
		ip = namei(ndp);
		if (ip == NULL) {
			if (u.u_error)
				goto bad1;
			ip = maknode(arg&07777&(~ISVTX), ndp);
			if (ip == NULL)
				goto bad1;
			mode &= ~FTRUNC;
		} else {
			if (mode&FEXCL) {
				u.u_error = EEXIST;
				goto bad;
			}
			mode &= ~FCREAT;
		}
	} else {
		ndp->ni_nameiop = LOOKUP | FOLLOW;
#if	VICE
		u.u_rmt_requested = 1;
#endif	VICE
		ip = namei(ndp);
		if (ip == NULL)
			goto bad1;
	}
	if ((ip->i_mode & IFMT) == IFSOCK) {
		u.u_error = EOPNOTSUPP;
		goto bad;
	}
	if ((mode&FCREAT) == 0) {
		if (mode&FREAD)
			if (access(ip, IREAD))
				goto bad;
		if (mode&(FWRITE|FTRUNC)) {
			if (access(ip, IWRITE))
				goto bad;
			if ((ip->i_mode&IFMT) == IFDIR) {
				u.u_error = EISDIR;
				goto bad;
			}
		}
	}
	if (mode&FTRUNC)
		itrunc(ip, (u_long)0);
	IUNLOCK(ip);
	fp->f_flag = mode&FMASK;
	fp->f_type = DTYPE_INODE;
	fp->f_ops = &inodeops;
	fp->f_data = (caddr_t)ip;
	if (setjmp(&u.u_qsave)) {
		if (u.u_error == 0)
			u.u_error = EINTR;

		/*
		 *  Yes, the openi() might be interrupted by a signal and
		 *  require that we clean up here.  Then again, so could the
		 *  closef() in which case we can't afford to close down the
		 *  same file yet another time.
		 */
		if (u.u_ofile[indx])
		{
		    u.u_ofile[indx] = NULL;
		    closef(fp);
		}

		return;
	}
	u.u_error = openi(ip, mode);
	if (u.u_error == 0)
		return;
	ILOCK(ip);
bad:
	iput(ip);
bad1:
#if	MACH_RFS
	if (u.u_error == ERFSREMOTE)
		return;
#endif	MACH_RFS
#if	VICE
	if (u.u_error == EVICEOP)
		return;
#endif	VICE
	u.u_ofile[indx] = NULL;
	freefp(fp);
}

/*
 * Mknod system call
 */
mknod()
{
	register struct inode *ip;
	register struct a {
		char	*fname;
		int	fmode;
		int	dev;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;

	if (!suser())
		return;
	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
				/* rmt_op NOT enabled */
#endif	VICE
	ip = namei(ndp);
	if (ip != NULL) {
		u.u_error = EEXIST;
		goto out;
	}
	if (u.u_error)
		return;
	ip = maknode(uap->fmode, ndp);
	if (ip == NULL)
		return;
	switch (ip->i_mode & IFMT) {

	case IFMT:	/* used by badsect to flag bad sectors */
	case IFCHR:
	case IFBLK:
		if (uap->dev) {
			/*
			 * Want to be able to use this to make badblock
			 * inodes, so don't truncate the dev number.
			 */
			ip->i_rdev = uap->dev;
			ip->i_flag |= IACC|IUPD|ICHG;
		}
	}

out:
	iput(ip);
}

/*
 * link system call
 */
link()
{
	register struct inode *ip, *xp;
	register struct a {
		char	*target;
		char	*linkname;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->target;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);	/* well, this routine is doomed anyhow */
	if (ip == NULL)
		return;
	if ((ip->i_mode&IFMT) == IFDIR && !suser()) {
		iput(ip);
		return;
	}
	ip->i_nlink++;
	ip->i_flag |= ICHG;
	iupdat(ip, &time, &time, 1);
	IUNLOCK(ip);
	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = (caddr_t)uap->linkname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	xp = namei(ndp);
	if (xp != NULL) {
		u.u_error = EEXIST;
		iput(xp);
		goto out;
	}
	if (u.u_error)
		goto out;
	if (ndp->ni_pdir->i_dev != ip->i_dev) {
		iput(ndp->ni_pdir);
		u.u_error = EXDEV;
		goto out;
	}
	u.u_error = direnter(ip, ndp);
out:
	if (u.u_error) {
		ip->i_nlink--;
		ip->i_flag |= ICHG;
	}
	irele(ip);
}


/*
 * symlink -- make a symbolic link
 */

symlink()
{
	register struct a {
		char	*target;
		char	*linkname;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	register char *tp;
	register c, nc;
	register struct nameidata *ndp = &u.u_nd;
#if	MACH_FASTLINK
	char	symname[MAX_FASTLINK_SIZE];
	int	fastlen = 0;
#endif	MACH_FASTLINK

	tp = uap->target;
	nc = 0;
	while (c = fubyte(tp)) {
		if (c < 0) {
			u.u_error = EFAULT;
			return;
		}
#if	MACH_FASTLINK
		if(fastlen < sizeof(symname)-1)
			symname[fastlen++] = c;
#endif	MACH_FASTLINK
		nc++;
		tp++;
	}

	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->linkname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip) {
		iput(ip);
		u.u_error = EEXIST;
		return;
	}
	if (u.u_error)
		return;
	ip = maknode(IFLNK | 0777, ndp);
	if (ip == NULL)
		return;
#if	MACH_FASTLINK
	if(nc < MAX_FASTLINK_SIZE && create_fastlinks) {
		symname[fastlen] = '\0';
		copystr(symname, ip->i_symlink, nc, (u_int *)0);
		ip->i_size = nc;
		ip->i_icflags |= IC_FASTLINK;
		ip->i_flag |= IACC|IUPD|ICHG;
	} else
#endif	MACH_FASTLINK
	u.u_error = rdwri(UIO_WRITE, ip, uap->target, nc, (off_t)0, 0,
	    (int *)0);
	/* handle u.u_error != 0 */
	iput(ip);
}

/*
 * Unlink system call.
 * Hard to avoid races here, especially
 * in unlinking directories.
 */
unlink()
{
	struct a {
		char	*fname;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip, *dp;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	dp = ndp->ni_pdir;
	if ((ip->i_mode&IFMT) == IFDIR && !suser())
		goto out;
	/*
	 * Don't unlink a mounted file.
	 */
	if (ip->i_dev != dp->i_dev) {
		u.u_error = EBUSY;
		goto out;
	}

	if (dirremove(ndp)) {
		ip->i_nlink--;
		ip->i_flag |= ICHG;
	}
	if ((ip->i_nlink == 0) && (ip->i_vm_info->pager != MEMORY_OBJECT_NULL))
		inode_uncache(ip);

out:
	if (dp == ip)
		irele(ip);
	else
		iput(ip);
	iput(dp);
}

/*
 * Seek system call
 */
lseek()
{
	register struct file *fp;
	register struct a {
		int	fd;
		off_t	off;
		int	sbase;
	} *uap = (struct a *)u.u_ap;

	GETF(fp, uap->fd);
#if	VICE
	if (fp->f_type != DTYPE_INODE && fp->f_type != DTYPE_VICEINO) {
#else	VICE
	if (fp->f_type != DTYPE_INODE) {
#endif	VICE
#if	MACH_RFS
		if (fp->f_type == DTYPE_RFSINO) {
			extern struct file *rfs_finode();

			(void) rfs_finode(fp);
			return;
		}
#endif	MACH_RFS
		u.u_error = ESPIPE;
		return;
	}
	switch (uap->sbase) {

	case L_INCR:
		fp->f_offset += uap->off;
		break;

	case L_XTND:
		fp->f_offset = uap->off + ((struct inode *)fp->f_data)->i_size;
		break;

	case L_SET:
		fp->f_offset = uap->off;
		break;

	default:
		u.u_error = EINVAL;
		return;
	}
	u.u_r.r_off = fp->f_offset;
}

/*
 * Access system call
 */
saccess()
{
	register svuid, svgid;
	register struct inode *ip;
	register struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;

	svuid = u.u_uid;
	svgid = u.u_gid;
	u.u_uid = u.u_ruid;
	u.u_gid = u.u_rgid;
	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip != NULL) {
		if ((uap->fmode&R_OK) && access(ip, IREAD))
			goto done;
		if ((uap->fmode&W_OK) && access(ip, IWRITE))
			goto done;
		if ((uap->fmode&X_OK) && access(ip, IEXEC))
			goto done;
done:
		iput(ip);
	}
	u.u_uid = svuid;
	u.u_gid = svgid;
}

/*
 * Stat system call.  This version follows links.
 */
stat()
{

	stat1(FOLLOW);
}

/*
 * Lstat system call.  This version does not follow links.
 */
lstat()
{

	stat1(NOFOLLOW);
}

stat1(follow)
	int follow;
{
	register struct inode *ip;
	register struct a {
		char	*fname;
		struct stat *ub;
	} *uap = (struct a *)u.u_ap;
	struct stat sb;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | follow;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	(void) ino_stat(ip, &sb);
	iput(ip);
	u.u_error = copyout((caddr_t)&sb, (caddr_t)uap->ub, sizeof (sb));
}

/*
 * Return target name of a symbolic link
 */
readlink()
{
	register struct inode *ip;
	register struct a {
		char	*name;
		char	*buf;
		int	count;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;
	int resid;

	ndp->ni_nameiop = LOOKUP;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	if ((ip->i_mode&IFMT) != IFLNK) {
		u.u_error = EINVAL;
		goto out;
	}
#if	MACH_FASTLINK
	/*
	 *	Encore fast symbolic link support
	 */
	if ((ip->i_icflags & IC_FASTLINK) != 0 && use_fastlinks) {
		u.u_r.r_val1 = (ip->i_size < uap->count) ? ip->i_size :
					uap->count;
		u.u_error = copyout (ip->i_symlink, uap->buf, u.u_r.r_val1);
		iput(ip);
		return;
	}
#endif	MACH_FASTLINK
	u.u_error = rdwri(UIO_READ, ip, uap->buf, uap->count, (off_t)0, 0,
	    &resid);
out:
	iput(ip);
	u.u_r.r_val1 = uap->count - resid;
}

/*
 * Change mode of a file given path name.
 */
chmod()
{
	struct inode *ip;
	struct a {
		char	*fname;
		int	fmode;
	} *uap = (struct a *)u.u_ap;

	if ((ip = owner(uap->fname, FOLLOW)) == NULL)
		return;
	u.u_error = chmod1(ip, uap->fmode);
	iput(ip);
}

/*
 * Change mode of a file given a file descriptor.
 */
fchmod()
{
	struct a {
		int	fd;
		int	fmode;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	register struct file *fp;

	fp = getinode(uap->fd);
	if (fp == NULL)
		return;
	ip = (struct inode *)fp->f_data;
	if (u.u_uid != ip->i_uid && !suser())
		return;
	ILOCK(ip);
	u.u_error = chmod1(ip, uap->fmode);
	IUNLOCK(ip);
}

/*
 * Change the mode on a file.
 * Inode must be locked before calling.
 */
chmod1(ip, mode)
	register struct inode *ip;
	register int mode;
{

	if (ip->i_fs->fs_ronly)
		return (EROFS);
	ip->i_mode &= ~07777;
	if (u.u_uid) {
		if ((ip->i_mode & IFMT) != IFDIR)
			mode &= ~ISVTX;
		if (!groupmember(ip->i_gid))
			mode &= ~ISGID;
	}
	ip->i_mode |= mode&07777;
	ip->i_flag |= ICHG;

	return (0);
}

/*
 * Set ownership given a path name.
 */
chown()
{
	struct inode *ip;
	struct a {
		char	*fname;
		int	uid;
		int	gid;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	u.u_error = chown1(ip, uap->uid, uap->gid);
	iput(ip);
}

/*
 * Set ownership given a file descriptor.
 */
fchown()
{
	struct a {
		int	fd;
		int	uid;
		int	gid;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	register struct file *fp;

	fp = getinode(uap->fd);
	if (fp == NULL)
		return;
	ip = (struct inode *)fp->f_data;
	ILOCK(ip);
	u.u_error = chown1(ip, uap->uid, uap->gid);
	IUNLOCK(ip);
}

/*
 * Perform chown operation on inode ip;
 * inode must be locked prior to call.
 */
chown1(ip, uid, gid)
	register struct inode *ip;
	int uid, gid;
{
#if	QUOTA
	register long change;
#endif	QUOTA

	if (ip->i_fs->fs_ronly)
		return (EROFS);
	if (uid == -1)
		uid = ip->i_uid;
	if (gid == -1)
		gid = ip->i_gid;
	/*
	 * If we don't own the file, are trying to change the owner
	 * of the file, or are not a member of the target group,
	 * the caller must be superuser or the call fails.
	 */
	if ((u.u_uid != ip->i_uid || uid != ip->i_uid ||
	    !groupmember((gid_t)gid)) && !suser())
		return (u.u_error);
#if	QUOTA
	if (ip->i_uid == uid)		/* this just speeds things a little */
		change = 0;
	else
		change = ip->i_blocks;
	(void) chkdq(ip, -change, 1);
	(void) chkiq(ip->i_dev, ip, ip->i_uid, 1);
	dqrele(ip->i_dquot);
#endif	QUOTA
	ip->i_uid = uid;
	ip->i_gid = gid;
	ip->i_flag |= ICHG;
	if (u.u_ruid != 0)
		ip->i_mode &= ~(ISUID|ISGID);
#if	QUOTA
	ip->i_dquot = inoquota(ip);
	(void) chkdq(ip, change, 1);
	(void) chkiq(ip->i_dev, (struct inode *)NULL, (uid_t)uid, 1);
	return (u.u_error);		/* should == 0 ALWAYS !! */
#else	QUOTA
	return (0);
#endif	QUOTA
}

utimes()
{
	register struct a {
		char	*fname;
		struct	timeval *tptr;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	struct timeval tv[2];

	if ((ip = owner(uap->fname, FOLLOW)) == NULL)
		return;
	if (ip->i_fs->fs_ronly) {
		u.u_error = EROFS;
		iput(ip);
		return;
	}
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error == 0) {
		ip->i_flag |= IACC|IUPD|ICHG;
		iupdat(ip, &tv[0], &tv[1], 0);
	}
	iput(ip);
}

/*
 *  xutimes() - extended utimes() call to update inode creation time
 *
 *  This call is identical to the normal utimes() call except that it expects
 *  three elements in the time value array rather than two.  If the caller is
 *  privileged, the third element is used to set the inode creation time of the
 *  corresponding inode.  If the caller is not privileged, the operation
 *  performs the same funtion as the standard utimes() call to update only the
 *  access and modification times.
 */

xutimes()
{
	register struct a {
		char	*fname;
		struct	timeval *tptr;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	struct timeval tv[3];

	if ((ip = owner(uap->fname, FOLLOW)) == NULL)
		return;
	if (ip->i_fs->fs_ronly) {
		u.u_error = EROFS;
		iput(ip);
		return;
	}
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error == 0) {
		if (u.u_uid == 0) {
			ip->i_flag &= ~ICHG;
			ip->i_ctime = tv[2].tv_sec;
			ip->i_flag |= IACC|IUPD|IMOD;
		}
		else
			ip->i_flag |= IACC|IUPD|ICHG;
		iupdat(ip, &tv[0], &tv[1], 0);
	}
	iput(ip);
}

/*
 * Flush any pending I/O.
 */
sync()
{

	update();
}

/*
 * Truncate a file given its path name.
 */
truncate()
{
	struct a {
		char	*fname;
		off_t	length;
	} *uap = (struct a *)u.u_ap;
	struct inode *ip;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	if (access(ip, IWRITE))
		goto bad;
	if ((ip->i_mode&IFMT) == IFDIR) {
		u.u_error = EISDIR;
		goto bad;
	}
	itrunc(ip, (u_long)uap->length);
bad:
	iput(ip);
}

/*
 * Truncate a file given a file descriptor.
 */
ftruncate()
{
	struct a {
		int	fd;
		off_t	length;
	} *uap = (struct a *)u.u_ap;
	struct inode *ip;
	struct file *fp;

	fp = getinode(uap->fd);
	if (fp == NULL)
		return;
#if	VICE
	if (u.u_error == EVICEOP)
		u.u_error = 0;		/* Allow normal processing */
#endif	VICE
	if ((fp->f_flag&FWRITE) == 0) {
		u.u_error = EINVAL;
		return;
	}
	ip = (struct inode *)fp->f_data;
	ILOCK(ip);
	itrunc(ip, (u_long)uap->length);
	IUNLOCK(ip);
}

/*
 * Synch an open file.
 */
fsync()
{
	struct a {
		int	fd;
	} *uap = (struct a *)u.u_ap;
	struct inode *ip;
	struct file *fp;

	fp = getinode(uap->fd);
	if (fp == NULL)
		return;
	ip = (struct inode *)fp->f_data;
	ILOCK(ip);
	syncip(ip);
	IUNLOCK(ip);
}

/*
 * Rename system call.
 * 	rename("foo", "bar");
 * is essentially
 *	unlink("bar");
 *	link("foo", "bar");
 *	unlink("foo");
 * but ``atomically''.  Can't do full commit without saving state in the
 * inode on disk which isn't feasible at this time.  Best we can do is
 * always guarantee the target exists.
 *
 * Basic algorithm is:
 *
 * 1) Bump link count on source while we're linking it to the
 *    target.  This also insure the inode won't be deleted out
 *    from underneath us while we work (it may be truncated by
 *    a concurrent `trunc' or `open' for creation).
 * 2) Link source to destination.  If destination already exists,
 *    delete it first.
 * 3) Unlink source reference to inode if still around. If a
 *    directory was moved and the parent of the destination
 *    is different from the source, patch the ".." entry in the
 *    directory.
 *
 * Source and destination must either both be directories, or both
 * not be directories.  If target is a directory, it must be empty.
 */
rename()
{
	struct a {
		char	*from;
		char	*to;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip, *xp, *dp;
	struct dirtemplate dirbuf;
	int doingdirectory = 0, oldparent = 0, newparent = 0;
	register struct nameidata *ndp = &u.u_nd;
	int error = 0;

	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->from;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	dp = ndp->ni_pdir;
	if ((ip->i_mode&IFMT) == IFDIR) {
		register struct direct *d;

		d = &ndp->ni_dent;
		/*
		 * Avoid ".", "..", and aliases of "." for obvious reasons.
		 */
		if ((d->d_namlen == 1 && d->d_name[0] == '.') ||
		    (d->d_namlen == 2 && bcmp(d->d_name, "..", 2) == 0) ||
		    (dp == ip) || (ip->i_flag & IRENAME)) {
			iput(dp);
			if (dp == ip)
				irele(ip);
			else
				iput(ip);
			u.u_error = EINVAL;
			return;
		}
		ip->i_flag |= IRENAME;
		oldparent = dp->i_number;
		doingdirectory++;
	}
	iput(dp);

	/*
	 * 1) Bump link count while we're moving stuff
	 *    around.  If we crash somewhere before
	 *    completing our work, the link count
	 *    may be wrong, but correctable.
	 */
	ip->i_nlink++;
	ip->i_flag |= ICHG;
	iupdat(ip, &time, &time, 1);
	IUNLOCK(ip);

	/*
	 * When the target exists, both the directory
	 * and target inodes are returned locked.
	 */
	ndp->ni_nameiop = CREATE | LOCKPARENT | NOCACHE;
	ndp->ni_dirp = (caddr_t)uap->to;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	xp = namei(ndp);
	if (u.u_error) {
		error = u.u_error;
		goto out;
	}
	dp = ndp->ni_pdir;
	/*
	 * If ".." must be changed (ie the directory gets a new
	 * parent) then the source directory must not be in the
	 * directory heirarchy above the target, as this would
	 * orphan everything below the source directory. Also
	 * the user must have write permission in the source so
	 * as to be able to change "..". We must repeat the call 
	 * to namei, as the parent directory is unlocked by the
	 * call to checkpath().
	 */
	if (oldparent != dp->i_number)
		newparent = dp->i_number;
	if (doingdirectory && newparent) {
		if (access(ip, IWRITE))
			goto bad;
		do {
			dp = ndp->ni_pdir;
			if (xp != NULL)
				iput(xp);
			u.u_error = checkpath(ip, dp);
			if (u.u_error)
				goto out;
			xp = namei(ndp);
			if (u.u_error) {
				error = u.u_error;
				goto out;
			}
		} while (dp != ndp->ni_pdir);
	}
	/*
	 * 2) If target doesn't exist, link the target
	 *    to the source and unlink the source. 
	 *    Otherwise, rewrite the target directory
	 *    entry to reference the source inode and
	 *    expunge the original entry's existence.
	 */
	if (xp == NULL) {
		if (dp->i_dev != ip->i_dev) {
			error = EXDEV;
			goto bad;
		}
		/*
		 * Account for ".." in new directory.
		 * When source and destination have the same
		 * parent we don't fool with the link count.
		 */
		if (doingdirectory && newparent) {
			dp->i_nlink++;
			dp->i_flag |= ICHG;
			iupdat(dp, &time, &time, 1);
		}
		error = direnter(ip, ndp);
		if (error)
			goto out;
	} else {
		if (xp->i_dev != dp->i_dev || xp->i_dev != ip->i_dev) {
			error = EXDEV;
			goto bad;
		}
		/*
		 * Short circuit rename(foo, foo).
		 */
		if (xp->i_number == ip->i_number)
			goto bad;
		/*
		 * If the parent directory is "sticky", then the user must
		 * own the parent directory, or the destination of the rename,
		 * otherwise the destination may not be changed (except by
		 * root). This implements append-only directories.
		 */
		if ((dp->i_mode & ISVTX) && u.u_uid != 0 &&
		    u.u_uid != dp->i_uid && xp->i_uid != u.u_uid) {
			error = EPERM;
			goto bad;
		}
		/*
		 * Target must be empty if a directory
		 * and have no links to it.
		 * Also, insure source and target are
		 * compatible (both directories, or both
		 * not directories).
		 */
		if ((xp->i_mode&IFMT) == IFDIR) {
			if (!dirempty(xp, dp->i_number) || xp->i_nlink > 2) {
				error = ENOTEMPTY;
				goto bad;
			}
			if (!doingdirectory) {
				error = ENOTDIR;
				goto bad;
			}
			cacheinval(dp);
		} else if (doingdirectory) {
			error = EISDIR;
			goto bad;
		}
		dirrewrite(dp, ip, ndp);
		if (u.u_error) {
			error = u.u_error;
			goto bad1;
		}
		/*
		 * Adjust the link count of the target to
		 * reflect the dirrewrite above.  If this is
		 * a directory it is empty and there are
		 * no links to it, so we can squash the inode and
		 * any space associated with it.  We disallowed
		 * renaming over top of a directory with links to
		 * it above, as the remaining link would point to
		 * a directory without "." or ".." entries.
		 */
		xp->i_nlink--;
		if (doingdirectory) {
			if (--xp->i_nlink != 0)
				panic("rename: linked directory");
			itrunc(xp, (u_long)0);
		}
		xp->i_flag |= ICHG;
		iput(xp);
		xp = NULL;
	}

	/*
	 * 3) Unlink the source.
	 */
	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->from;
	xp = namei(ndp);
	if (xp != NULL)
		dp = ndp->ni_pdir;
	else
		dp = NULL;
	/*
	 * Insure that the directory entry still exists and has not
	 * changed while the new name has been entered. If the source is
	 * a file then the entry may have been unlinked or renamed. In
	 * either case there is no further work to be done. If the source
	 * is a directory then it cannot have been rmdir'ed; its link
	 * count of three would cause a rmdir to fail with ENOTEMPTY.
	 * The IRENAME flag insures that it cannot be moved by another
	 * rename.
	 */
	if (xp != ip) {
		if (doingdirectory)
			panic("rename: lost dir entry");
	} else {
		/*
		 * If the source is a directory with a
		 * new parent, the link count of the old
		 * parent directory must be decremented
		 * and ".." set to point to the new parent.
		 */
		if (doingdirectory && newparent) {
			dp->i_nlink--;
			dp->i_flag |= ICHG;
			error = rdwri(UIO_READ, xp, (caddr_t)&dirbuf,
				sizeof (struct dirtemplate), (off_t)0, 1,
				(int *)0);
			if (error == 0) {
				if (dirbuf.dotdot_namlen != 2 ||
				    dirbuf.dotdot_name[0] != '.' ||
				    dirbuf.dotdot_name[1] != '.') {
					printf("rename: mangled dir\n");
				} else {
					dirbuf.dotdot_ino = newparent;
					(void) rdwri(UIO_WRITE, xp,
					    (caddr_t)&dirbuf,
					    sizeof (struct dirtemplate),
					    (off_t)0, 1, (int *)0);
					cacheinval(dp);
				}
			}
		}
		if (dirremove(ndp)) {
			xp->i_nlink--;
			xp->i_flag |= ICHG;
		}
		xp->i_flag &= ~IRENAME;
		if (error == 0)		/* XXX conservative */
			error = u.u_error;
	}
	if (dp)
		iput(dp);
	if (xp)
		iput(xp);
	irele(ip);
	if (error)
		u.u_error = error;
	return;

bad:
	iput(dp);
bad1:
	if (xp)
		iput(xp);
out:
	ip->i_nlink--;
	ip->i_flag |= ICHG;
	irele(ip);
	if (error)
		u.u_error = error;
}

/*
 * Make a new file.
 */
struct inode *
maknode(mode, ndp)
	int mode;
	register struct nameidata *ndp;
{
	register struct inode *ip;
	register struct inode *pdir = ndp->ni_pdir;
	ino_t ipref;

	if ((mode & IFMT) == IFDIR)
		ipref = dirpref(pdir->i_fs);
	else
		ipref = pdir->i_number;
	ip = ialloc(pdir, ipref, mode);
	if (ip == NULL) {
		iput(pdir);
		return (NULL);
	}
#if	QUOTA
	if (ip->i_dquot != NODQUOT)
		panic("maknode: dquot");
#endif	QUOTA
	ip->i_flag |= IACC|IUPD|ICHG;
	if ((mode & IFMT) == 0)
		mode |= IFREG;
	ip->i_mode = mode & ~u.u_cmask;
	ip->i_nlink = 1;
	ip->i_uid = u.u_uid;
	if ((u.u_modes&UMODE_P_GID) == 0)
	    ip->i_gid = u.u_gid;
	else
	ip->i_gid = pdir->i_gid;
	if (ip->i_mode & ISGID && !groupmember(ip->i_gid))
		ip->i_mode &= ~ISGID;
#if	QUOTA
	ip->i_dquot = inoquota(ip);
#endif	QUOTA

	/*
	 * Make sure inode goes to disk before directory entry.
	 */
	iupdat(ip, &time, &time, 1);
	u.u_error = direnter(ip, ndp);
	if (u.u_error) {
		/*
		 * Write error occurred trying to update directory
		 * so must deallocate the inode.
		 */
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
		iput(ip);
		return (NULL);
	}
	return (ip);
}

/*
 * A virgin directory (no blushing please).
 */
struct dirtemplate mastertemplate = {
	0, 12, 1, ".",
	0, DIRBLKSIZ - 12, 2, ".."
};

/*
 * Mkdir system call
 */
mkdir()
{
	struct a {
		char	*name;
		int	dmode;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip, *dp;
	struct dirtemplate dirtemplate;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = CREATE;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (u.u_error)
		return;
	if (ip != NULL) {
		iput(ip);
		u.u_error = EEXIST;
		return;
	}
	dp = ndp->ni_pdir;
	uap->dmode &= 0777;
	uap->dmode |= IFDIR;
	/*
	 * Must simulate part of maknode here
	 * in order to acquire the inode, but
	 * not have it entered in the parent
	 * directory.  The entry is made later
	 * after writing "." and ".." entries out.
	 */
	ip = ialloc(dp, dirpref(dp->i_fs), uap->dmode);
	if (ip == NULL) {
		iput(dp);
		return;
	}
#if	QUOTA
	if (ip->i_dquot != NODQUOT)
		panic("mkdir: dquot");
#endif	QUOTA
	ip->i_flag |= IACC|IUPD|ICHG;
	ip->i_mode = uap->dmode & ~u.u_cmask;
	ip->i_nlink = 2;
	ip->i_uid = u.u_uid;
	if ((u.u_modes&UMODE_P_GID) == 0)
	    ip->i_gid = u.u_gid;
	else
	ip->i_gid = dp->i_gid;
#if	QUOTA
	ip->i_dquot = inoquota(ip);
#endif	QUOTA
	iupdat(ip, &time, &time, 1);

	/*
	 * Bump link count in parent directory
	 * to reflect work done below.  Should
	 * be done before reference is created
	 * so reparation is possible if we crash.
	 */
	dp->i_nlink++;
	dp->i_flag |= ICHG;
	iupdat(dp, &time, &time, 1);

	/*
	 * Initialize directory with "."
	 * and ".." from static template.
	 */
	dirtemplate = mastertemplate;
	dirtemplate.dot_ino = ip->i_number;
	dirtemplate.dotdot_ino = dp->i_number;
	u.u_error = rdwri(UIO_WRITE, ip, (caddr_t)&dirtemplate,
		sizeof (dirtemplate), (off_t)0, 1, (int *)0);
	if (u.u_error) {
		dp->i_nlink--;
		dp->i_flag |= ICHG;
		goto bad;
	}
	if (DIRBLKSIZ > ip->i_fs->fs_fsize)
		panic("mkdir: blksize");     /* XXX - should grow with bmap() */
	else
		ip->i_size = DIRBLKSIZ;
	/*
	 * Directory all set up, now
	 * install the entry for it in
	 * the parent directory.
	 */
	u.u_error = direnter(ip, ndp);
	dp = NULL;
	if (u.u_error) {
		ndp->ni_nameiop = LOOKUP | NOCACHE;
		ndp->ni_segflg = UIO_USERSPACE;
		ndp->ni_dirp = uap->name;
		dp = namei(ndp);
		if (dp) {
			dp->i_nlink--;
			dp->i_flag |= ICHG;
		}
	}
bad:
	/*
	 * No need to do an explicit itrunc here,
	 * irele will do this for us because we set
	 * the link count to 0.
	 */
	if (u.u_error) {
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
	}
	if (dp)
		iput(dp);
	iput(ip);
}

/*
 * Rmdir system call.
 */
rmdir()
{
	struct a {
		char	*name;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip, *dp;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = DELETE | LOCKPARENT;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->name;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return;
	dp = ndp->ni_pdir;
	/*
	 * No rmdir "." please.
	 */
	if (dp == ip) {
		irele(dp);
		iput(ip);
		u.u_error = EINVAL;
		return;
	}
	if ((ip->i_mode&IFMT) != IFDIR) {
		u.u_error = ENOTDIR;
		goto out;
	}
	/*
	 * Don't remove a mounted on directory.
	 */
	if (ip->i_dev != dp->i_dev) {
		u.u_error = EBUSY;
		goto out;
	}
	/*
	 * Verify the directory is empty (and valid).
	 * (Rmdir ".." won't be valid since
	 *  ".." will contain a reference to
	 *  the current directory and thus be
	 *  non-empty.)
	 */
	if (ip->i_nlink != 2 || !dirempty(ip, dp->i_number)) {
		u.u_error = ENOTEMPTY;
		goto out;
	}
	/*
	 * Delete reference to directory before purging
	 * inode.  If we crash in between, the directory
	 * will be reattached to lost+found,
	 */
	if (dirremove(ndp) == 0)
		goto out;
	dp->i_nlink--;
	dp->i_flag |= ICHG;
	cacheinval(dp);
	iput(dp);
	dp = NULL;
	/*
	 * Truncate inode.  The only stuff left
	 * in the directory is "." and "..".  The
	 * "." reference is inconsequential since
	 * we're quashing it.  The ".." reference
	 * has already been adjusted above.  We've
	 * removed the "." reference and the reference
	 * in the parent directory, but there may be
	 * other hard links so decrement by 2 and
	 * worry about them later.
	 */
	ip->i_nlink -= 2;
	itrunc(ip, (u_long)0);
	cacheinval(ip);
out:
	if (dp)
		iput(dp);
	iput(ip);
}

#if	MACH
/*
 * getdirentries()
 *	Read directory entries in a file system independent format.
 *
 * Adapted from VFS code of the same function.
 */

getdirentries()
{
	register struct a {
		int	fd;
		char	*buf;
		unsigned count;
		long	*basep;
	} *uap = (struct a *) u.u_ap;
	register struct file *fp;
	struct uio auio;
	struct iovec aiov[2];

	GETF(fp, uap->fd);
#if	VICE
	if (fp->f_type != DTYPE_INODE && fp->f_type != DTYPE_VICEINO) {
#else	VICE
	if (fp->f_type != DTYPE_INODE) {
#endif	VICE
#if	MACH_RFS
		if (fp->f_type == DTYPE_RFSINO) {
			aiov[0].iov_base = (char *)uap->basep;
			aiov[0].iov_len = sizeof(long);
			aiov[1].iov_base = uap->buf;
			aiov[1].iov_len = uap->count;
			auio.uio_iov = aiov;
			auio.uio_iovcnt = 2;
			rwuio(&auio, UIO_READ);
			if (u.u_error)
				return;
			if (u.u_r.r_val1 < sizeof(long)) {
				u.u_error = EINVAL;
				return;
			}
			u.u_r.r_val1 -= sizeof(long);
			fp->f_offset -= sizeof(long);
			return;
		}
#endif	MACH_RFS
		u.u_error = EBADF;
		return;
	}

	if ((fp->f_flag & FREAD) == 0) {
		u.u_error = EBADF;
		return;
	}
	/*
	 * Must read at least one directory block and read from
	 * block boundary.
	 */

	if (uap->count < DIRBLKSIZ || (fp->f_offset & (DIRBLKSIZ-1))) {
		u.u_error = EINVAL;
		return;
	}

	/*
	 * Only read an integral number of directory blocks.
	 */

	aiov[0].iov_base = uap->buf;
	aiov[0].iov_len = uap->count & ~(DIRBLKSIZ-1);

	auio.uio_iov = aiov;
	auio.uio_iovcnt = 1;
	u.u_error = copyout((caddr_t)&fp->f_offset, (caddr_t)uap->basep,
								sizeof(long));
	if (u.u_error)
		return;

	if (fp->f_type == DTYPE_INODE)
		ILOCK((struct inode *)fp->f_data);

	rwuio(&auio, UIO_READ);		/* NB.  rwuio expects 1st arg*/
					/* in u.u_ap to be a file descriptor*/

	if (fp->f_type == DTYPE_INODE)
		IUNLOCK((struct inode *)fp->f_data);

}
#endif	MACH

struct file *
getinode(fdes)
	int fdes;
{
	struct file *fp;

	if ((unsigned)fdes >= NOFILE || (fp = u.u_ofile[fdes]) == NULL) {
		u.u_error = EBADF;
		return ((struct file *)0);
	}
#if	MACH_RFS || VICE
	switch(fp->f_type) {
#if	MACH_RFS
		/*
		 *  Perform RFS system call handling if necessary.
		 */
		case DTYPE_RFSINO:
		{
		    extern struct file *rfs_finode();

		    return(rfs_finode(fp));
		}
#endif	MACH_RFS
#if	VICE
		/*
		 *  Perform ITC/REMOTE system call handling if necessary.
		 */
		case DTYPE_VICEINO:
		{
		    extern struct file *rmt_fdes();

		    return(rmt_fdes(fp));
		}
#endif	VICE
		case DTYPE_INODE:
		    return(fp);
		default:
		    u.u_error = EINVAL;
		    return ((struct file *)0);
	}
#else	MACH_RFS || VICE
	if (fp->f_type != DTYPE_INODE) {
		u.u_error = EINVAL;
		return ((struct file *)0);
	}
	return (fp);
#endif	MACH_RFS || VICE
}

/*
 * mode mask for creation of files
 */
umask()
{
	register struct a {
		int	mask;
	} *uap = (struct a *)u.u_ap;

	u.u_r.r_val1 = u.u_cmask;
	u.u_cmask = uap->mask & 07777;
}

#if	VICE
extern struct fs *igetfs();
/* 
 * Get an existing inode.  
 * Common code for iopen, iread/write, iinc/dec.
 * Also used by rmt_remote to support passing of inode number from venus.
 */
struct inode *
igetinode(dev, i_number)
	dev_t dev;
	ino_t i_number;
{
	register struct inode *ip;
	register struct fs *fs;

	fs = igetfs(dev);
	if (u.u_error)
	    return (struct inode *)0;
	/* Note:  should optimize here--annoying that iget immediately does
	   another getfs... */
	ip = iget(dev, fs, i_number);
	if (ip == NULL) {
	    u.u_error = ENOENT;		/* Well... */
	    return (struct inode *)0;
	}
	if (ip->i_mode == 0) {
	    /* Not an allocated inode */
	    iforget(ip);	    
	    u.u_error = ENOENT;
	    return (struct inode *)0;
	}
	if (ip->i_nlink == 0 || (ip->i_mode&IFMT) != IFREG) {
	    iput(ip);
	    u.u_error = ENOENT;
	    return (struct inode *)0;
	}
	return ip;
}


/*
 * icreate system call -- create an inode
 */
icreate()
{
	register struct a {
		int	dev;
		int	near_inode;
		int	param1;
		int	param2;
		int	param3;
		int	param4;
	} *uap = (struct a *) u.u_ap;
	register struct inode *ip, *newip;
	struct fs *fs;

	if (!suser())
		return;
	fs = igetfs((dev_t)uap->dev);
	if (u.u_error)
		return;
	/* Shouldn t be doing following line */
	ip = iget((dev_t)uap->dev, fs, ROOTINO);
			/* An example inode from this
			   file system, just to
			   satisfy ialloc */
	if (u.u_error)
		return;
	newip = ialloc(ip, (ino_t)0, 0);
        iput(ip);
	if  (u.u_error)
	    return;
	newip->i_flag |= IACC|IUPD|ICHG;
	newip->i_nlink = 1;
	newip->i_uid = 0;
	newip->i_gid = -2;
	newip->i_mode = IFREG;
	newip->i_vicemagic = VICEMAGIC;
	newip->i_vicep1 = uap->param1;
	newip->i_vicep2 = uap->param2;
	newip->i_vicep3 = uap->param3;
	newip->i_vicep4 = uap->param4;
	u.u_r.r_val1 = newip->i_number;
	iput(newip);
	return;
}


/*
 * iopen system call -- open an inode for reading/writing
 * Restricted to super user.
 * Any IFREG files.
 */
iopen()
{
	register struct a {
		int	dev;
		int	inode;
		int	usermode;
	} *uap = (struct a *) u.u_ap;
	register struct file *fp;
	register struct inode *ip;

	if (!suser())
		return;
	ip = igetinode((dev_t)uap->dev, (ino_t)uap->inode);
	if (u.u_error)
		return;
	if (ip->i_gid != (gid_t)-2 && ip->i_vicemagic != VICEMAGIC) {
	    iput(ip);
	    u.u_error = EPERM;
	    return;
	}
	if ((uap->usermode&FEXCL) && ip->i_count != 1) {
	    iput(ip);
	    u.u_error = EBUSY;
	    return;
	}
	fp = falloc();
	if (fp == NULL) {
		iput(ip);
		return;
	}
	iunlock(ip);
	fp->f_flag = (uap->usermode-FOPEN)&FMASK;
	fp->f_type = DTYPE_INODE;
	fp->f_ops = &inodeops;
	fp->f_data = (caddr_t)ip;

	return;
}


/*
 * Support for iinc() and idec() system calls--increment or decrement
 * count on inode.
 * Restricted to super user.
 * Only VICEMAGIC type inodes.
 */
iincdec(amount)
	int amount;
{
	register struct a {
		int	dev;
		int	inode;
		long	inode_p1;
	} *uap = (struct a *) u.u_ap;
	register struct inode *ip;

	if (!suser())
		return;
	ip = igetinode((dev_t)uap->dev, (ino_t)uap->inode);
	if (u.u_error)
		return;
	if (ip->i_vicemagic != VICEMAGIC)
		u.u_error = EPERM;
	else if (ip->i_vicep1 != uap->inode_p1)
	    u.u_error = ENXIO;
	else
		ip->i_nlink += amount;
	if (ip->i_nlink == 0)
		ip->i_vicemagic = 0;
	ip->i_flag |= ICHG;
	iput(ip);
}


iinc() {
    iincdec(1);
}


idec() {
    iincdec(-1);
}


/*
 * Support for iread/iwrite system calls.
 * Restricted to super user.
 * Only inodes with owner and group == -1.
 * NB:  VICEMAGIC inodes default to this owner and group.
 */
ireadwrite(rw)
	enum uio_rw	rw;
{
	register struct a {
		int		dev;
		int		inode;
		long		inode_p1;
		unsigned int 	offset;
		char		*cbuf;
		unsigned int 	count;
	} *uap = (struct a *) u.u_ap;
	register struct inode *ip;
	unsigned int resid;
	daddr_t	db[NDADDR], ib[NIADDR];
	int size;

	if (!suser())
		return;
	ip = igetinode((dev_t)uap->dev, (ino_t)uap->inode);
	if (u.u_error)
		return;
	if (ip->i_gid != (gid_t)-2 && ip->i_vicemagic != VICEMAGIC) {
		iput(ip);
		u.u_error = EPERM;
		return;
	}
	if (ip->i_vicep1 != uap->inode_p1) {
	        iput(ip);
	        u.u_error = ENXIO;
		return;
	}
	bcopy((caddr_t)ip->i_db, (caddr_t)db, sizeof db);
	bcopy((caddr_t)ip->i_ib, (caddr_t)ib, sizeof ib);
	size = ip->i_size;
	resid = 0;
	u.u_error = rdwri(
	    rw, ip, (caddr_t) uap->cbuf, uap->count, uap->offset, 0, &resid);
	u.u_r.r_val1 = uap->count - resid;
	if (size == ip->i_size
	    && bcmp((caddr_t)ip->i_db, (caddr_t)db, sizeof db) == 0
	    && bcmp((caddr_t)ip->i_ib, (caddr_t)ib, sizeof ib) == 0) {
		/* Don t write out the inode if it hasn t really changed.
		   We don t care about inode dates in file server files */
		ip->i_flag &= ~(IUPD|IACC|ICHG);
	}
	iput(ip);
}


iread()
{
	ireadwrite(UIO_READ);
}


iwrite()
{
    	ireadwrite(UIO_WRITE);
}


/* 
 *  pioctl:  pathname ioctl (for remote pathnames only) 
 */

pioctl()
{
    register struct a {
	char	*path;
	int	com;
	caddr_t	comarg;
	int	follow;
    } *uap = (struct a *)u.u_ap;
    register struct inode	*ip;
    register struct nameidata	*ndp = &u.u_nd;

    if (! _VALIDVICEIOCTL(uap->com))
    {
	u.u_error = EINVAL;	/* Not supported on non-remote files */
	return;
    }

    ndp->ni_nameiop = LOOKUP | (uap->follow ? FOLLOW: NULL);
    ndp->ni_segflg = UIO_USERSPACE;
    ndp->ni_dirp = uap->path;
    u.u_rmt_requested = 1;
    ip = namei(ndp);

    if (ip)
    {
	iput(ip);
	u.u_error = EINVAL;	/* Not supported on non-remote files */
    }
				/* Results are discarded!!! */
}
#endif	VICE
