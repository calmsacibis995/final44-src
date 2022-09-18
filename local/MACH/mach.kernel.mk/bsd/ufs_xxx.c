/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ufs_xxx.c,v $
 * Revision 2.5  89/03/09  19:33:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/26  11:30:16  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/09  04:35:43  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.2  88/08/24  01:38:00  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:05:45  mwyoung]
 * 
 *
 * 16-Jul-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	CS_GENERIC: Changed size fields from ints to u_longs.
 *
 * 26-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 27-Sep-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added simple-minded emulation for ofstat() on a pipe.
 *	[V1(1)]
 *
 * 18-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  changed to enable remote names for all namei()
 *	calls in this module.
 *	[V1(1)]
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_xxx.c	7.1 (Berkeley) 6/5/86
 */
 
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/mount.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/conf.h>

#ifdef	COMPAT
#include <sys/file.h>
#include <sys/kernel.h>
#if	MACH_RFS
 
/*
 *  Force all namei() calls to permit remote names since this module has
 *  been updated.
 */
#undef	namei
#define namei	rnamei
#endif	MACH_RFS

/*
 * Oh, how backwards compatibility is ugly!!!
 */
struct	ostat {
	dev_t	ost_dev;
	u_short	ost_ino;
	u_short ost_mode;
	short  	ost_nlink;
	short  	ost_uid;
	short  	ost_gid;
	dev_t	ost_rdev;
	u_long	ost_size;
	int	ost_atime;
	int	ost_mtime;
	int	ost_ctime;
};

/*
 * The old fstat system call.
 */
ofstat()
{
	register struct file *fp;
	register struct a {
		int	fd;
		struct ostat *sb;
	} *uap = (struct a *)u.u_ap;
	extern struct file *getinode();

	fp = getinode(uap->fd);
	if (fp == NULL)
		return;
	ostat1((struct inode *)fp->f_data, uap->sb);
}

/*
 * Old stat system call.  This version follows links.
 */
ostat()
{
	register struct inode *ip;
	register struct a {
		char	*fname;
		struct ostat *sb;
	} *uap = (struct a *)u.u_ap;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | FOLLOW;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = uap->fname;
	ip = namei(ndp);
	if (ip == NULL)
		return;
	ostat1(ip, uap->sb);
	iput(ip);
}

ostat1(ip, ub)
	register struct inode *ip;
	struct ostat *ub;
{
	struct ostat ds;

	IUPDAT(ip, &time, &time, 0);
	/*
	 * Copy from inode table
	 */
	ds.ost_dev = ip->i_dev;
	ds.ost_ino = (short)ip->i_number;
	ds.ost_mode = (u_short)ip->i_mode;
	ds.ost_nlink = ip->i_nlink;
	ds.ost_uid = (short)ip->i_uid;
	ds.ost_gid = (short)ip->i_gid;
	ds.ost_rdev = (dev_t)ip->i_rdev;
	ds.ost_size = (u_long)ip->i_size;
	ds.ost_atime = (int)ip->i_atime;
	ds.ost_mtime = (int)ip->i_mtime;
	ds.ost_ctime = (int)ip->i_ctime;
	u.u_error = copyout((caddr_t)&ds, (caddr_t)ub, sizeof(ds));
}

/*
 * Set IUPD and IACC times on file.
 * Can't set ICHG.
 */
outime()
{
	register struct a {
		char	*fname;
		time_t	*tptr;
	} *uap = (struct a *)u.u_ap;
	register struct inode *ip;
	time_t tv[2];
	struct timeval tv0, tv1;

	if ((ip = owner(uap->fname, FOLLOW)) == NULL)
		return;
	u.u_error = copyin((caddr_t)uap->tptr, (caddr_t)tv, sizeof (tv));
	if (u.u_error == 0) {
		ip->i_flag |= IACC|IUPD|ICHG;
		tv0.tv_sec = tv[0]; tv0.tv_usec = 0;
		tv1.tv_sec = tv[1]; tv1.tv_usec = 0;
		iupdat(ip, &tv0, &tv1, 0);
	}
	iput(ip);
}
#endif
