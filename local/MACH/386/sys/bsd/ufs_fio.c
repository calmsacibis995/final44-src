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
 * $Log:	ufs_fio.c,v $
 * Revision 2.8  89/04/22  15:22:03  gm0w
 * 	Moved suser() to kern_prot.c.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/03/09  19:32:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/26  11:28:59  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/09  04:35:12  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  88/10/18  03:16:17  mwyoung
 * 	Use inode_uncache_try() when finding busy text files. in access().
 * 	[88/09/18            mwyoung]
 * 
 * Revision 2.3  88/08/24  01:35:12  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Use CMUCS_RFS now.
 * 	[88/08/23            mwyoung]
 * 
 * 18-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	MACH_VM: Change how text bit is checked when opening for write.
 *
 *  1-Jun-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added include of "builtin/inode_pager.h" to get inode_uncache.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged VICE changes -- include vice.h and change to #if VICE.
 *
 *  3-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use inode_uncache as a more general form of text_uncache.
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  enabled ITC/Andrew remote name processing for owner().
 *
 * 23-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Restored check for attempting to write text file in use.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 19-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  enabled remote namei() processing for all
 *	routines in this module.
 *	[V1(1)]
 */
 
#include <mach_xp.h>
#include <vice.h>
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)ufs_fio.c	7.1 (Berkeley) 6/5/86
 */

#include <machine/reg.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/fs.h>
#include <sys/file.h>
#include <sys/conf.h>
#include <sys/inode.h>
#include <sys/acct.h>
#include <sys/mount.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/proc.h>
#include <builtin/inode_pager.h>
#include <kern/mfs.h>

#if	MACH_RFS
/* 
 *  Force all namei() calls to permit remote names since this module has
 *  been updated.
 */
#undef	namei
#define namei	rnamei

#endif	MACH_RFS
/*
 * Check mode permission on inode pointer.
 * Mode is READ, WRITE or EXEC.
 * In the case of WRITE, the
 * read-only status of the file
 * system is checked.
 * Also in WRITE, prototype text
 * segments cannot be written.
 * The mode is shifted to select
 * the owner/group/other fields.
 * The super user is granted all
 * permissions.
 */
access(ip, mode)
	register struct inode *ip;
	int mode;
{
	register m;
	register gid_t *gp;

	m = mode;
	if (m == IWRITE) {
		/*
		 * Disallow write attempts on read-only
		 * file systems; unless the file is a block
		 * or character device resident on the
		 * file system.
		 */
		if (ip->i_fs->fs_ronly != 0) {
			if ((ip->i_mode & IFMT) != IFCHR &&
			    (ip->i_mode & IFMT) != IFBLK) {
				u.u_error = EROFS;
				return (1);
			}
		}
		/*
		 * If there's shared text associated with
		 * the inode, try to free it up once.  If
		 * we fail, we can't allow writing.
		 */
		if ((ip->i_flag & ITEXT) && !inode_uncache_try(ip)) {
			u.u_error = ETXTBSY;
			return(1);
		}
	}
	/*
	 * If you're the super-user,
	 * you always get access.
	 */
	if (u.u_uid == 0)
		return (0);
	/*
	 * Access check is based on only
	 * one of owner, group, public.
	 * If not owner, then check group.
	 * If not a member of the group, then
	 * check public access.
	 */
	if (u.u_uid != ip->i_uid) {
		m >>= 3;
		if (u.u_gid == ip->i_gid)
			goto found;
		gp = u.u_groups;
		for (; gp < &u.u_groups[NGROUPS] && *gp != NOGROUP; gp++)
			if (ip->i_gid == *gp)
				goto found;
		m >>= 3;
found:
		;
	}
	if ((ip->i_mode&m) != 0)
		return (0);
	u.u_error = EACCES;
	return (1);
}

/*
 * Look up a pathname and test if
 * the resultant inode is owned by the
 * current user.
 * If not, try for super-user.
 * If permission is granted,
 * return inode pointer.
 */
struct inode *
owner(fname, follow)
	caddr_t fname;
	int follow;
{
	register struct inode *ip;
	register struct nameidata *ndp = &u.u_nd;

	ndp->ni_nameiop = LOOKUP | follow;
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
#if	VICE
	u.u_rmt_requested = 1;
#endif	VICE
	ip = namei(ndp);
	if (ip == NULL)
		return (NULL);
	if (u.u_uid == ip->i_uid)
		return (ip);
	if (suser())
		return (ip);
	iput(ip);
	return (NULL);
}
