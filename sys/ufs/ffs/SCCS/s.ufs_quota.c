h36140
s 00012/00012/00900
d D 8.2 93/12/30 16:08:44 mckusick 31 30
c vget now locks optionally; new queue structures
e
s 00002/00002/00910
d D 8.1 93/06/11 16:29:11 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00028/00044/00884
d D 7.17 92/07/22 17:20:03 mckusick 29 28
c new hashing scheme
e
s 00000/00008/00928
d D 7.16 92/07/03 01:43:32 mckusick 28 27
c delete USES
e
s 00008/00000/00928
d D 7.15 92/05/14 17:27:53 heideman 27 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 17:04:06 heideman 26 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 16:44:53 heideman 25 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 16:34:51 heideman 24 14
c vnode interface conversion
e
s 00018/00000/00928
d R 7.15 92/05/14 15:54:07 heideman 23 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 15:40:57 heideman 22 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 14:46:58 heideman 21 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 12:50:06 heideman 20 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 11:47:17 heideman 19 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/14 10:27:58 heideman 18 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/13 23:06:08 heideman 17 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/13 18:53:17 heideman 16 14
c vnode interface conversion
e
s 00008/00000/00928
d R 7.15 92/05/13 18:25:25 heideman 15 14
c vnode interface conversion
e
s 00001/00001/00927
d D 7.14 92/03/11 21:25:08 torek 14 13
c gcc lint
e
s 00002/00003/00926
d D 7.13 92/02/04 14:31:14 mckusick 13 12
c new namei calling convention
e
s 00048/00027/00881
d D 7.12 91/11/01 18:09:23 bostic 12 11
c UFS/FFS split for LFS version 1; inode can no longer directly access
c the superblock
e
s 00011/00010/00897
d D 7.11 91/06/21 10:54:27 mckusick 11 10
c use vn_close rather than vrele after vn_open
e
s 00013/00002/00894
d D 7.10 91/06/04 22:21:49 mckusick 10 9
c speed up sync of filesystems with no quotas; skip locked inodes
e
s 00001/00000/00895
d D 7.9 91/06/03 20:39:29 mckusick 9 8
c must unlock vnode after vn_open
e
s 00002/00000/00893
d D 7.8 91/04/16 00:09:38 mckusick 8 7
c initialize proc pointer in uio setup
e
s 00016/00016/00877
d D 7.7 91/03/19 10:30:39 karels 7 6
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00004/00001/00889
d D 7.6 90/11/08 21:56:42 mckusick 6 5
c do not forget to unlock resources (from Torek)
e
s 00003/00001/00887
d D 7.5 90/08/29 14:42:22 mckusick 5 4
c missing vput
e
s 00001/00011/00887
d D 7.4 90/06/28 22:30:54 bostic 4 3
c new copyright notice
e
s 00002/00002/00896
d D 7.3 90/06/19 17:10:26 mckusick 3 2
c handle short reads on quota files by using default values
e
s 00007/00007/00891
d D 7.2 90/05/04 20:51:26 mckusick 2 1
c mount struct prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00898/00000/00000
d D 7.1 90/05/02 19:27:15 mckusick 1 0
c derived from quota_kern.c, quota_subr.c, quota_sys.c, quota_ufs.c
e
u
U
t
T
I 1
/*
D 30
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
 * This code is derived from software contributed to Berkeley by
 * Robert Elz at The University of Melbourne.
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */
D 12
#include "param.h"
D 7
#include "time.h"
E 7
#include "kernel.h"
#include "systm.h"
D 7
#include "ucred.h"
E 7
#include "namei.h"
D 7
#include "errno.h"
E 7
#include "malloc.h"
#include "file.h"
I 7
#include "proc.h"
E 7
#include "vnode.h"
#include "mount.h"
E 12
I 12
#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/malloc.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
E 12
D 7
#include "../ufs/fs.h"
#include "../ufs/quota.h"
#include "../ufs/inode.h"
#include "../ufs/ufsmount.h"
E 7

I 7
D 12
#include "fs.h"
#include "quota.h"
#include "inode.h"
#include "ufsmount.h"
E 12
I 12
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/ufs_extern.h>
E 12

E 7
/*
 * Quota name to error message mapping.
 */
static char *quotatypes[] = INITQFNAMES;

/*
 * Set up the quotas for an inode.
 *
 * This routine completely defines the semantics of quotas.
 * If other criterion want to be used to establish quotas, the
 * MAXQUOTAS value in quotas.h should be increased, and the
 * additional dquots set up here.
 */
I 12
int
E 12
getinoquota(ip)
	register struct inode *ip;
{
	struct ufsmount *ump;
	struct vnode *vp = ITOV(ip);
	int error;

	ump = VFSTOUFS(vp->v_mount);
	/*
	 * Set up the user quota based on file uid.
	 * EINVAL means that quotas are not enabled.
	 */
	if (ip->i_dquot[USRQUOTA] == NODQUOT &&
	    (error =
		dqget(vp, ip->i_uid, ump, USRQUOTA, &ip->i_dquot[USRQUOTA])) &&
	    error != EINVAL)
		return (error);
	/*
	 * Set up the group quota based on file gid.
	 * EINVAL means that quotas are not enabled.
	 */
	if (ip->i_dquot[GRPQUOTA] == NODQUOT &&
	    (error =
		dqget(vp, ip->i_gid, ump, GRPQUOTA, &ip->i_dquot[GRPQUOTA])) &&
	    error != EINVAL)
		return (error);
	return (0);
}

/*
 * Update disk usage, and take corrective action.
 */
I 12
int
E 12
chkdq(ip, change, cred, flags)
	register struct inode *ip;
	long change;
	struct ucred *cred;
	int flags;
{
	register struct dquot *dq;
	register int i;
	int ncurblocks, error;

#ifdef DIAGNOSTIC
	if ((flags & CHOWN) == 0)
		chkdquot(ip);
#endif
	if (change == 0)
		return (0);
	if (change < 0) {
		for (i = 0; i < MAXQUOTAS; i++) {
			if ((dq = ip->i_dquot[i]) == NODQUOT)
				continue;
			while (dq->dq_flags & DQ_LOCK) {
				dq->dq_flags |= DQ_WANT;
				sleep((caddr_t)dq, PINOD+1);
			}
			ncurblocks = dq->dq_curblocks + change;
			if (ncurblocks >= 0)
				dq->dq_curblocks = ncurblocks;
			else
				dq->dq_curblocks = 0;
			dq->dq_flags &= ~DQ_BLKS;
			dq->dq_flags |= DQ_MOD;
		}
		return (0);
	}
	if ((flags & FORCE) == 0 && cred->cr_uid != 0) {
		for (i = 0; i < MAXQUOTAS; i++) {
			if ((dq = ip->i_dquot[i]) == NODQUOT)
				continue;
			if (error = chkdqchg(ip, change, cred, i))
				return (error);
		}
	}
	for (i = 0; i < MAXQUOTAS; i++) {
		if ((dq = ip->i_dquot[i]) == NODQUOT)
			continue;
		while (dq->dq_flags & DQ_LOCK) {
			dq->dq_flags |= DQ_WANT;
			sleep((caddr_t)dq, PINOD+1);
		}
		dq->dq_curblocks += change;
		dq->dq_flags |= DQ_MOD;
	}
	return (0);
}

/*
 * Check for a valid change to a users allocation.
 * Issue an error message if appropriate.
 */
I 12
int
E 12
chkdqchg(ip, change, cred, type)
	struct inode *ip;
	long change;
	struct ucred *cred;
	int type;
{
	register struct dquot *dq = ip->i_dquot[type];
	long ncurblocks = dq->dq_curblocks + change;

	/*
	 * If user would exceed their hard limit, disallow space allocation.
	 */
	if (ncurblocks >= dq->dq_bhardlimit && dq->dq_bhardlimit) {
		if ((dq->dq_flags & DQ_BLKS) == 0 &&
		    ip->i_uid == cred->cr_uid) {
			uprintf("\n%s: write failed, %s disk limit reached\n",
D 12
			    ip->i_fs->fs_fsmnt, quotatypes[type]);
E 12
I 12
			    ITOV(ip)->v_mount->mnt_stat.f_mntonname,
			    quotatypes[type]);
E 12
			dq->dq_flags |= DQ_BLKS;
		}
		return (EDQUOT);
	}
	/*
	 * If user is over their soft limit for too long, disallow space
	 * allocation. Reset time limit as they cross their soft limit.
	 */
	if (ncurblocks >= dq->dq_bsoftlimit && dq->dq_bsoftlimit) {
		if (dq->dq_curblocks < dq->dq_bsoftlimit) {
			dq->dq_btime = time.tv_sec +
			    VFSTOUFS(ITOV(ip)->v_mount)->um_btime[type];
			if (ip->i_uid == cred->cr_uid)
				uprintf("\n%s: warning, %s %s\n",
D 12
				    ip->i_fs->fs_fsmnt, quotatypes[type],
				    "disk quota exceeded");
E 12
I 12
				    ITOV(ip)->v_mount->mnt_stat.f_mntonname,
				    quotatypes[type], "disk quota exceeded");
E 12
			return (0);
		}
		if (time.tv_sec > dq->dq_btime) {
			if ((dq->dq_flags & DQ_BLKS) == 0 &&
			    ip->i_uid == cred->cr_uid) {
				uprintf("\n%s: write failed, %s %s\n",
D 12
				    ip->i_fs->fs_fsmnt, quotatypes[type],
				    "disk quota exceeded too long");
E 12
I 12
				    ITOV(ip)->v_mount->mnt_stat.f_mntonname,
				    quotatypes[type],
				    "disk quota exceeded for too long");
E 12
				dq->dq_flags |= DQ_BLKS;
			}
			return (EDQUOT);
		}
	}
	return (0);
}

/*
 * Check the inode limit, applying corrective action.
 */
I 12
int
E 12
chkiq(ip, change, cred, flags)
	register struct inode *ip;
	long change;
	struct ucred *cred;
	int flags;
{
	register struct dquot *dq;
	register int i;
	int ncurinodes, error;

#ifdef DIAGNOSTIC
	if ((flags & CHOWN) == 0)
		chkdquot(ip);
#endif
	if (change == 0)
		return (0);
	if (change < 0) {
		for (i = 0; i < MAXQUOTAS; i++) {
			if ((dq = ip->i_dquot[i]) == NODQUOT)
				continue;
			while (dq->dq_flags & DQ_LOCK) {
				dq->dq_flags |= DQ_WANT;
				sleep((caddr_t)dq, PINOD+1);
			}
			ncurinodes = dq->dq_curinodes + change;
			if (ncurinodes >= 0)
				dq->dq_curinodes = ncurinodes;
			else
				dq->dq_curinodes = 0;
			dq->dq_flags &= ~DQ_INODS;
			dq->dq_flags |= DQ_MOD;
		}
		return (0);
	}
	if ((flags & FORCE) == 0 && cred->cr_uid != 0) {
		for (i = 0; i < MAXQUOTAS; i++) {
			if ((dq = ip->i_dquot[i]) == NODQUOT)
				continue;
			if (error = chkiqchg(ip, change, cred, i))
				return (error);
		}
	}
	for (i = 0; i < MAXQUOTAS; i++) {
		if ((dq = ip->i_dquot[i]) == NODQUOT)
			continue;
		while (dq->dq_flags & DQ_LOCK) {
			dq->dq_flags |= DQ_WANT;
			sleep((caddr_t)dq, PINOD+1);
		}
		dq->dq_curinodes += change;
		dq->dq_flags |= DQ_MOD;
	}
	return (0);
}

/*
 * Check for a valid change to a users allocation.
 * Issue an error message if appropriate.
 */
I 12
int
E 12
chkiqchg(ip, change, cred, type)
	struct inode *ip;
	long change;
	struct ucred *cred;
	int type;
{
	register struct dquot *dq = ip->i_dquot[type];
	long ncurinodes = dq->dq_curinodes + change;

	/*
	 * If user would exceed their hard limit, disallow inode allocation.
	 */
	if (ncurinodes >= dq->dq_ihardlimit && dq->dq_ihardlimit) {
		if ((dq->dq_flags & DQ_INODS) == 0 &&
		    ip->i_uid == cred->cr_uid) {
			uprintf("\n%s: write failed, %s inode limit reached\n",
D 12
			    ip->i_fs->fs_fsmnt, quotatypes[type]);
E 12
I 12
			    ITOV(ip)->v_mount->mnt_stat.f_mntonname,
			    quotatypes[type]);
E 12
			dq->dq_flags |= DQ_INODS;
		}
		return (EDQUOT);
	}
	/*
	 * If user is over their soft limit for too long, disallow inode
	 * allocation. Reset time limit as they cross their soft limit.
	 */
	if (ncurinodes >= dq->dq_isoftlimit && dq->dq_isoftlimit) {
		if (dq->dq_curinodes < dq->dq_isoftlimit) {
			dq->dq_itime = time.tv_sec +
			    VFSTOUFS(ITOV(ip)->v_mount)->um_itime[type];
			if (ip->i_uid == cred->cr_uid)
				uprintf("\n%s: warning, %s %s\n",
D 12
				    ip->i_fs->fs_fsmnt, quotatypes[type],
				    "inode quota exceeded");
E 12
I 12
				    ITOV(ip)->v_mount->mnt_stat.f_mntonname,
				    quotatypes[type], "inode quota exceeded");
E 12
			return (0);
		}
		if (time.tv_sec > dq->dq_itime) {
			if ((dq->dq_flags & DQ_INODS) == 0 &&
			    ip->i_uid == cred->cr_uid) {
				uprintf("\n%s: write failed, %s %s\n",
D 12
				    ip->i_fs->fs_fsmnt, quotatypes[type],
				    "inode quota exceeded too long");
E 12
I 12
				    ITOV(ip)->v_mount->mnt_stat.f_mntonname,
				    quotatypes[type],
				    "inode quota exceeded for too long");
E 12
				dq->dq_flags |= DQ_INODS;
			}
			return (EDQUOT);
		}
	}
	return (0);
}

#ifdef DIAGNOSTIC
/*
D 12
 * On filesystems with quotas enabled,
 * it is an error for a file to change size and not
 * to have a dquot structure associated with it.
E 12
I 12
 * On filesystems with quotas enabled, it is an error for a file to change
 * size and not to have a dquot structure associated with it.
E 12
 */
I 12
void
E 12
chkdquot(ip)
	register struct inode *ip;
{
	struct ufsmount *ump = VFSTOUFS(ITOV(ip)->v_mount);
	register int i;

	for (i = 0; i < MAXQUOTAS; i++) {
		if (ump->um_quotas[i] == NULLVP ||
		    (ump->um_qflags[i] & (QTF_OPENING|QTF_CLOSING)))
			continue;
		if (ip->i_dquot[i] == NODQUOT) {
			vprint("chkdquot: missing dquot", ITOV(ip));
			panic("missing dquot");
		}
	}
}
D 12
#endif /* DIAGNOSTIC */
E 12
I 12
#endif
E 12

/*
 * Code to process quotactl commands.
 */

/*
 * Q_QUOTAON - set up a quota file for a particular file system.
 */
I 12
int
E 12
D 7
quotaon(ndp, mp, type, fname)
	register struct nameidata *ndp;
E 7
I 7
quotaon(p, mp, type, fname)
	struct proc *p;
E 7
	struct mount *mp;
	register int type;
	caddr_t fname;
{
I 27
D 28
	USES_VOP_UNLOCK;
E 28
E 27
	register struct ufsmount *ump = VFSTOUFS(mp);
	register struct vnode *vp, **vpp;
	struct vnode *nextvp;
	struct dquot *dq;
	int error;
D 7
	
E 7
I 7
	struct nameidata nd;

E 7
	vpp = &ump->um_quotas[type];
D 7
	ndp->ni_segflg = UIO_USERSPACE;
	ndp->ni_dirp = fname;
	if (error = vn_open(ndp, FREAD|FWRITE, 0))
E 7
I 7
D 13
	nd.ni_segflg = UIO_USERSPACE;
	nd.ni_dirp = fname;
	if (error = vn_open(&nd, p, FREAD|FWRITE, 0))
E 13
I 13
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, fname, p);
	if (error = vn_open(&nd, FREAD|FWRITE, 0))
E 13
E 7
		return (error);
D 7
	vp = ndp->ni_vp;
E 7
I 7
	vp = nd.ni_vp;
I 9
	VOP_UNLOCK(vp);
E 9
E 7
	if (vp->v_type != VREG) {
D 11
		vrele(vp);
E 11
I 11
		(void) vn_close(vp, FREAD|FWRITE, p->p_ucred, p);
E 11
		return (EACCES);
	}
	if (vfs_busy(mp)) {
D 11
		vrele(vp);
E 11
I 11
		(void) vn_close(vp, FREAD|FWRITE, p->p_ucred, p);
E 11
		return (EBUSY);
	}
	if (*vpp != vp)
D 11
		quotaoff(mp, type);
E 11
I 11
		quotaoff(p, mp, type);
E 11
	ump->um_qflags[type] |= QTF_OPENING;
D 2
	mp->m_flag |= M_QUOTA;
E 2
I 2
	mp->mnt_flag |= MNT_QUOTA;
E 2
	vp->v_flag |= VSYSTEM;
	*vpp = vp;
	/*
	 * Save the credential of the process that turned on quotas.
	 * Set up the time limits for this quota.
	 */
D 7
	crhold(ndp->ni_cred);
	ump->um_cred[type] = ndp->ni_cred;
E 7
I 7
	crhold(p->p_ucred);
	ump->um_cred[type] = p->p_ucred;
E 7
	ump->um_btime[type] = MAX_DQ_TIME;
	ump->um_itime[type] = MAX_IQ_TIME;
	if (dqget(NULLVP, 0, ump, type, &dq) == 0) {
		if (dq->dq_btime > 0)
			ump->um_btime[type] = dq->dq_btime;
		if (dq->dq_itime > 0)
			ump->um_itime[type] = dq->dq_itime;
		dqrele(NULLVP, dq);
	}
	/*
	 * Search vnodes associated with this mount point,
	 * adding references to quota file being opened.
D 11
	 * NB: only need to add dquot's for inodes being modified;
	 * vp->v_usecount == 0 below should use vp->v_writecnt == 0.
E 11
I 11
	 * NB: only need to add dquot's for inodes being modified.
E 11
	 */
again:
D 2
	for (vp = mp->m_mounth; vp; vp = nextvp) {
E 2
I 2
D 31
	for (vp = mp->mnt_mounth; vp; vp = nextvp) {
E 2
		nextvp = vp->v_mountf;
E 31
I 31
	for (vp = mp->mnt_vnodelist.lh_first; vp != NULL; vp = nextvp) {
		nextvp = vp->v_mntvnodes.le_next;
E 31
D 11
		if (vp->v_usecount == 0)
E 11
I 11
		if (vp->v_writecount == 0)
E 11
			continue;
D 31
		if (vget(vp))
E 31
I 31
		if (vget(vp, 1))
E 31
			goto again;
D 5
		if (error = getinoquota(VTOI(vp)))
E 5
I 5
		if (error = getinoquota(VTOI(vp))) {
			vput(vp);
E 5
			break;
I 5
		}
E 5
		vput(vp);
D 31
		if (vp->v_mountf != nextvp || vp->v_mount != mp)
E 31
I 31
		if (vp->v_mntvnodes.le_next != nextvp || vp->v_mount != mp)
E 31
			goto again;
	}
	ump->um_qflags[type] &= ~QTF_OPENING;
	if (error)
D 11
		quotaoff(mp, type);
E 11
I 11
		quotaoff(p, mp, type);
E 11
	vfs_unbusy(mp);
	return (error);
}

/*
 * Q_QUOTAOFF - turn off disk quotas for a filesystem.
 */
I 12
int
E 12
D 11
quotaoff(mp, type)
E 11
I 11
quotaoff(p, mp, type)
	struct proc *p;
E 11
	struct mount *mp;
	register int type;
{
	register struct vnode *vp;
	struct vnode *qvp, *nextvp;
	struct ufsmount *ump = VFSTOUFS(mp);
	register struct dquot *dq;
	register struct inode *ip;
I 11
	int error;
E 11
	
D 2
	if ((mp->m_flag & M_MPBUSY) == 0)
E 2
I 2
	if ((mp->mnt_flag & MNT_MPBUSY) == 0)
E 2
		panic("quotaoff: not busy");
	if ((qvp = ump->um_quotas[type]) == NULLVP)
		return (0);
	ump->um_qflags[type] |= QTF_CLOSING;
	/*
	 * Search vnodes associated with this mount point,
	 * deleting any references to quota file being closed.
	 */
again:
D 2
	for (vp = mp->m_mounth; vp; vp = nextvp) {
E 2
I 2
D 31
	for (vp = mp->mnt_mounth; vp; vp = nextvp) {
E 2
		nextvp = vp->v_mountf;
		if (vget(vp))
E 31
I 31
	for (vp = mp->mnt_vnodelist.lh_first; vp != NULL; vp = nextvp) {
		nextvp = vp->v_mntvnodes.le_next;
		if (vget(vp, 1))
E 31
			goto again;
		ip = VTOI(vp);
		dq = ip->i_dquot[type];
		ip->i_dquot[type] = NODQUOT;
		dqrele(vp, dq);
		vput(vp);
D 31
		if (vp->v_mountf != nextvp || vp->v_mount != mp)
E 31
I 31
		if (vp->v_mntvnodes.le_next != nextvp || vp->v_mount != mp)
E 31
			goto again;
	}
	dqflush(qvp);
	qvp->v_flag &= ~VSYSTEM;
D 11
	vrele(qvp);
E 11
I 11
	error = vn_close(qvp, FREAD|FWRITE, p->p_ucred, p);
E 11
	ump->um_quotas[type] = NULLVP;
	crfree(ump->um_cred[type]);
	ump->um_cred[type] = NOCRED;
	ump->um_qflags[type] &= ~QTF_CLOSING;
	for (type = 0; type < MAXQUOTAS; type++)
		if (ump->um_quotas[type] != NULLVP)
			break;
	if (type == MAXQUOTAS)
D 2
		mp->m_flag &= ~M_QUOTA;
E 2
I 2
		mp->mnt_flag &= ~MNT_QUOTA;
E 2
D 11
	return (0);
E 11
I 11
	return (error);
E 11
}

/*
 * Q_GETQUOTA - return current values in a dqblk structure.
 */
I 12
int
E 12
getquota(mp, id, type, addr)
	struct mount *mp;
	u_long id;
	int type;
	caddr_t addr;
{
	struct dquot *dq;
	int error;

	if (error = dqget(NULLVP, id, VFSTOUFS(mp), type, &dq))
		return (error);
	error = copyout((caddr_t)&dq->dq_dqb, addr, sizeof (struct dqblk));
	dqrele(NULLVP, dq);
	return (error);
}

/*
 * Q_SETQUOTA - assign an entire dqblk structure.
 */
I 12
int
E 12
setquota(mp, id, type, addr)
	struct mount *mp;
	u_long id;
	int type;
	caddr_t addr;
{
	register struct dquot *dq;
	struct dquot *ndq;
	struct ufsmount *ump = VFSTOUFS(mp);
	struct dqblk newlim;
	int error;

	if (error = copyin(addr, (caddr_t)&newlim, sizeof (struct dqblk)))
		return (error);
	if (error = dqget(NULLVP, id, ump, type, &ndq))
		return (error);
	dq = ndq;
	while (dq->dq_flags & DQ_LOCK) {
		dq->dq_flags |= DQ_WANT;
		sleep((caddr_t)dq, PINOD+1);
	}
	/*
	 * Copy all but the current values.
	 * Reset time limit if previously had no soft limit or were
	 * under it, but now have a soft limit and are over it.
	 */
	newlim.dqb_curblocks = dq->dq_curblocks;
	newlim.dqb_curinodes = dq->dq_curinodes;
	if (dq->dq_id != 0) {
		newlim.dqb_btime = dq->dq_btime;
		newlim.dqb_itime = dq->dq_itime;
	}
	if (newlim.dqb_bsoftlimit &&
	    dq->dq_curblocks >= newlim.dqb_bsoftlimit &&
	    (dq->dq_bsoftlimit == 0 || dq->dq_curblocks < dq->dq_bsoftlimit))
		newlim.dqb_btime = time.tv_sec + ump->um_btime[type];
	if (newlim.dqb_isoftlimit &&
	    dq->dq_curinodes >= newlim.dqb_isoftlimit &&
	    (dq->dq_isoftlimit == 0 || dq->dq_curinodes < dq->dq_isoftlimit))
		newlim.dqb_itime = time.tv_sec + ump->um_itime[type];
	dq->dq_dqb = newlim;
	if (dq->dq_curblocks < dq->dq_bsoftlimit)
		dq->dq_flags &= ~DQ_BLKS;
	if (dq->dq_curinodes < dq->dq_isoftlimit)
		dq->dq_flags &= ~DQ_INODS;
	if (dq->dq_isoftlimit == 0 && dq->dq_bsoftlimit == 0 &&
	    dq->dq_ihardlimit == 0 && dq->dq_bhardlimit == 0)
		dq->dq_flags |= DQ_FAKE;
	else
		dq->dq_flags &= ~DQ_FAKE;
	dq->dq_flags |= DQ_MOD;
	dqrele(NULLVP, dq);
	return (0);
}

/*
 * Q_SETUSE - set current inode and block usage.
 */
I 12
int
E 12
setuse(mp, id, type, addr)
	struct mount *mp;
	u_long id;
	int type;
	caddr_t addr;
{
	register struct dquot *dq;
	struct ufsmount *ump = VFSTOUFS(mp);
	struct dquot *ndq;
	struct dqblk usage;
	int error;

	if (error = copyin(addr, (caddr_t)&usage, sizeof (struct dqblk)))
		return (error);
	if (error = dqget(NULLVP, id, ump, type, &ndq))
		return (error);
	dq = ndq;
	while (dq->dq_flags & DQ_LOCK) {
		dq->dq_flags |= DQ_WANT;
		sleep((caddr_t)dq, PINOD+1);
	}
	/*
	 * Reset time limit if have a soft limit and were
	 * previously under it, but are now over it.
	 */
	if (dq->dq_bsoftlimit && dq->dq_curblocks < dq->dq_bsoftlimit &&
	    usage.dqb_curblocks >= dq->dq_bsoftlimit)
		dq->dq_btime = time.tv_sec + ump->um_btime[type];
	if (dq->dq_isoftlimit && dq->dq_curinodes < dq->dq_isoftlimit &&
	    usage.dqb_curinodes >= dq->dq_isoftlimit)
		dq->dq_itime = time.tv_sec + ump->um_itime[type];
	dq->dq_curblocks = usage.dqb_curblocks;
	dq->dq_curinodes = usage.dqb_curinodes;
	if (dq->dq_curblocks < dq->dq_bsoftlimit)
		dq->dq_flags &= ~DQ_BLKS;
	if (dq->dq_curinodes < dq->dq_isoftlimit)
		dq->dq_flags &= ~DQ_INODS;
	dq->dq_flags |= DQ_MOD;
	dqrele(NULLVP, dq);
	return (0);
}

/*
 * Q_SYNC - sync quota files to disk.
 */
I 12
int
E 12
qsync(mp)
	struct mount *mp;
{
I 27
D 28
	USES_VOP_ISLOCKED;
E 28
E 27
	struct ufsmount *ump = VFSTOUFS(mp);
	register struct vnode *vp, *nextvp;
	register struct dquot *dq;
	register int i;

	/*
D 10
	 * Search vnodes associated with this mount point,
	 * synchronizing any modified dquot structures.
E 10
I 10
	 * Check if the mount point has any quotas.
	 * If not, simply return.
E 10
	 */
D 2
	if ((mp->m_flag & M_MPBUSY) == 0)
E 2
I 2
	if ((mp->mnt_flag & MNT_MPBUSY) == 0)
E 2
		panic("qsync: not busy");
I 10
	for (i = 0; i < MAXQUOTAS; i++)
		if (ump->um_quotas[i] != NULLVP)
			break;
	if (i == MAXQUOTAS)
		return (0);
	/*
	 * Search vnodes associated with this mount point,
	 * synchronizing any modified dquot structures.
	 */
E 10
again:
D 2
	for (vp = mp->m_mounth; vp; vp = nextvp) {
E 2
I 2
D 31
	for (vp = mp->mnt_mounth; vp; vp = nextvp) {
E 2
		nextvp = vp->v_mountf;
E 31
I 31
	for (vp = mp->mnt_vnodelist.lh_first; vp != NULL; vp = nextvp) {
		nextvp = vp->v_mntvnodes.le_next;
E 31
I 10
		if (VOP_ISLOCKED(vp))
			continue;
E 10
D 31
		if (vget(vp))
E 31
I 31
		if (vget(vp, 1))
E 31
			goto again;
		for (i = 0; i < MAXQUOTAS; i++) {
			dq = VTOI(vp)->i_dquot[i];
			if (dq != NODQUOT && (dq->dq_flags & DQ_MOD))
				dqsync(vp, dq);
		}
		vput(vp);
D 31
		if (vp->v_mountf != nextvp || vp->v_mount != mp)
E 31
I 31
		if (vp->v_mntvnodes.le_next != nextvp || vp->v_mount != mp)
E 31
			goto again;
	}
	return (0);
}

/*
 * Code pertaining to management of the in-core dquot data structures.
 */
I 29
struct dquot **dqhashtbl;
u_long dqhash;
E 29

/*
D 29
 * Dquot cache - hash chain headers.
 */
union	dqhead	{
	union	dqhead	*dqh_head[2];
	struct	dquot	*dqh_chain[2];
};
#define	dqh_forw	dqh_chain[0]
#define	dqh_back	dqh_chain[1]

union dqhead *dqhashtbl;
long dqhash;

/*
E 29
 * Dquot free list.
 */
#define	DQUOTINC	5	/* minimum free dquots desired */
struct dquot *dqfreel, **dqback = &dqfreel;
long numdquot, desireddquot = DQUOTINC;

/*
 * Initialize the quota system.
 */
I 12
void
E 12
dqinit()
{
D 29
	register union dqhead *dhp;
	register long dqhashsize;
E 29

D 29
	dqhashsize = roundup((desiredvnodes + 1) * sizeof *dhp / 2,
		NBPG * CLSIZE);
	dqhashtbl = (union dqhead *)malloc(dqhashsize, M_DQUOT, M_WAITOK);
	for (dqhash = 1; dqhash <= dqhashsize / sizeof *dhp; dqhash <<= 1)
D 14
		/* void */;
E 14
I 14
		continue;
E 14
	dqhash = (dqhash >> 1) - 1;
	for (dhp = &dqhashtbl[dqhash]; dhp >= dqhashtbl; dhp--) {
		dhp->dqh_head[0] = dhp;
		dhp->dqh_head[1] = dhp;
	}
E 29
I 29
	dqhashtbl = hashinit(desiredvnodes, M_DQUOT, &dqhash);
E 29
}

/*
 * Obtain a dquot structure for the specified identifier and quota file
 * reading the information from the file if necessary.
 */
I 12
int
E 12
dqget(vp, id, ump, type, dqp)
	struct vnode *vp;
	u_long id;
	register struct ufsmount *ump;
	register int type;
	struct dquot **dqp;
{
I 27
D 28
	USES_VOP_LOCK;
	USES_VOP_READ;
	USES_VOP_UNLOCK;
E 28
E 27
D 29
	register struct dquot *dq;
	register union dqhead *dh;
	register struct dquot *dp;
E 29
I 29
	register struct dquot *dq, *dp, **dpp;
E 29
	register struct vnode *dqvp;
	struct iovec aiov;
	struct uio auio;
	int error;

	dqvp = ump->um_quotas[type];
	if (dqvp == NULLVP || (ump->um_qflags[type] & QTF_CLOSING)) {
		*dqp = NODQUOT;
		return (EINVAL);
	}
	/*
	 * Check the cache first.
	 */
D 29
	dh = &dqhashtbl[((((int)(dqvp)) >> 8) + id) & dqhash];
	for (dq = dh->dqh_forw; dq != (struct dquot *)dh; dq = dq->dq_forw) {
E 29
I 29
	dpp = &dqhashtbl[((((int)(dqvp)) >> 8) + id) & dqhash];
	for (dq = *dpp; dq; dq = dq->dq_forw) {
E 29
		if (dq->dq_id != id ||
		    dq->dq_ump->um_quotas[dq->dq_type] != dqvp)
			continue;
		/*
		 * Cache hit with no references.  Take
		 * the structure off the free list.
		 */
		if (dq->dq_cnt == 0) {
D 29
			dp = dq->dq_freef;
			if (dp != NODQUOT)
E 29
I 29
			if ((dp = dq->dq_freef) != NODQUOT)
E 29
				dp->dq_freeb = dq->dq_freeb;
			else
				dqback = dq->dq_freeb;
			*dq->dq_freeb = dp;
		}
		DQREF(dq);
		*dqp = dq;
		return (0);
	}
	/*
	 * Not in cache, allocate a new one.
	 */
	if (dqfreel == NODQUOT && numdquot < MAXQUOTAS * desiredvnodes)
		desireddquot += DQUOTINC;
	if (numdquot < desireddquot) {
		dq = (struct dquot *)malloc(sizeof *dq, M_DQUOT, M_WAITOK);
		bzero((char *)dq, sizeof *dq);
		numdquot++;
	} else {
		if ((dq = dqfreel) == NULL) {
			tablefull("dquot");
			*dqp = NODQUOT;
			return (EUSERS);
		}
		if (dq->dq_cnt || (dq->dq_flags & DQ_MOD))
			panic("free dquot isn't");
		if ((dp = dq->dq_freef) != NODQUOT)
			dp->dq_freeb = &dqfreel;
		else
			dqback = &dqfreel;
		dqfreel = dp;
		dq->dq_freef = NULL;
		dq->dq_freeb = NULL;
D 29
		remque(dq);
E 29
I 29
		if (dp = dq->dq_forw)
			dp->dq_back = dq->dq_back;
		*dq->dq_back = dp;
E 29
	}
	/*
	 * Initialize the contents of the dquot structure.
	 */
	if (vp != dqvp)
		VOP_LOCK(dqvp);
D 29
	insque(dq, dh);
E 29
I 29
	if (dp = *dpp)
		dp->dq_back = &dq->dq_forw;
	dq->dq_forw = dp;
	dq->dq_back = dpp;
	*dpp = dq;
E 29
	DQREF(dq);
	dq->dq_flags = DQ_LOCK;
	dq->dq_id = id;
	dq->dq_ump = ump;
	dq->dq_type = type;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = (caddr_t)&dq->dq_dqb;
	aiov.iov_len = sizeof (struct dqblk);
	auio.uio_resid = sizeof (struct dqblk);
	auio.uio_offset = (off_t)(id * sizeof (struct dqblk));
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = UIO_READ;
I 8
	auio.uio_procp = (struct proc *)0;
E 8
	error = VOP_READ(dqvp, &auio, 0, ump->um_cred[type]);
D 3
	if (auio.uio_resid && error == 0)
		error = EIO;
E 3
I 3
	if (auio.uio_resid == sizeof(struct dqblk) && error == 0)
		bzero((caddr_t)&dq->dq_dqb, sizeof(struct dqblk));
E 3
	if (vp != dqvp)
		VOP_UNLOCK(dqvp);
	if (dq->dq_flags & DQ_WANT)
		wakeup((caddr_t)dq);
	dq->dq_flags = 0;
	/*
	 * I/O error in reading quota file, release
	 * quota structure and reflect problem to caller.
	 */
	if (error) {
D 29
		remque(dq);
		dq->dq_forw = dq;	/* on a private, unfindable hash list */
		dq->dq_back = dq;
E 29
I 29
		if (dp = dq->dq_forw)
			dp->dq_back = dq->dq_back;
		*dq->dq_back = dp;
		dq->dq_forw = NULL;
		dq->dq_back = NULL;
E 29
		dqrele(vp, dq);
		*dqp = NODQUOT;
		return (error);
	}
	/*
	 * Check for no limit to enforce.
	 * Initialize time values if necessary.
	 */
	if (dq->dq_isoftlimit == 0 && dq->dq_bsoftlimit == 0 &&
	    dq->dq_ihardlimit == 0 && dq->dq_bhardlimit == 0)
		dq->dq_flags |= DQ_FAKE;
	if (dq->dq_id != 0) {
		if (dq->dq_btime == 0)
			dq->dq_btime = time.tv_sec + ump->um_btime[type];
		if (dq->dq_itime == 0)
			dq->dq_itime = time.tv_sec + ump->um_itime[type];
	}
	*dqp = dq;
	return (0);
}

/*
 * Obtain a reference to a dquot.
 */
I 12
void
E 12
dqref(dq)
	struct dquot *dq;
{

	dq->dq_cnt++;
}

/*
 * Release a reference to a dquot.
 */
I 12
void
E 12
dqrele(vp, dq)
	struct vnode *vp;
	register struct dquot *dq;
{

	if (dq == NODQUOT)
		return;
	if (dq->dq_cnt > 1) {
		dq->dq_cnt--;
		return;
	}
	if (dq->dq_flags & DQ_MOD)
		(void) dqsync(vp, dq);
	if (--dq->dq_cnt > 0)
		return;
	if (dqfreel != NODQUOT) {
		*dqback = dq;
		dq->dq_freeb = dqback;
	} else {
		dqfreel = dq;
		dq->dq_freeb = &dqfreel;
	}
	dq->dq_freef = NODQUOT;
	dqback = &dq->dq_freef;
}

/*
 * Update the disk quota in the quota file.
 */
I 12
int
E 12
dqsync(vp, dq)
	struct vnode *vp;
	register struct dquot *dq;
{
I 27
D 28
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
	USES_VOP_WRITE;
E 28
E 27
	struct vnode *dqvp;
	struct iovec aiov;
	struct uio auio;
	int error;

	if (dq == NODQUOT)
		panic("dqsync: dquot");
	if ((dq->dq_flags & DQ_MOD) == 0)
		return (0);
	if ((dqvp = dq->dq_ump->um_quotas[dq->dq_type]) == NULLVP)
		panic("dqsync: file");
	if (vp != dqvp)
		VOP_LOCK(dqvp);
	while (dq->dq_flags & DQ_LOCK) {
		dq->dq_flags |= DQ_WANT;
		sleep((caddr_t)dq, PINOD+2);
D 6
		if ((dq->dq_flags & DQ_MOD) == 0)
E 6
I 6
		if ((dq->dq_flags & DQ_MOD) == 0) {
			if (vp != dqvp)
				VOP_UNLOCK(dqvp);
E 6
			return (0);
I 6
		}
E 6
	}
	dq->dq_flags |= DQ_LOCK;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = (caddr_t)&dq->dq_dqb;
	aiov.iov_len = sizeof (struct dqblk);
	auio.uio_resid = sizeof (struct dqblk);
	auio.uio_offset = (off_t)(dq->dq_id * sizeof (struct dqblk));
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = UIO_WRITE;
I 8
	auio.uio_procp = (struct proc *)0;
E 8
	error = VOP_WRITE(dqvp, &auio, 0, dq->dq_ump->um_cred[dq->dq_type]);
	if (auio.uio_resid && error == 0)
		error = EIO;
	if (dq->dq_flags & DQ_WANT)
		wakeup((caddr_t)dq);
	dq->dq_flags &= ~(DQ_MOD|DQ_LOCK|DQ_WANT);
	if (vp != dqvp)
		VOP_UNLOCK(dqvp);
	return (error);
}

/*
 * Flush all entries from the cache for a particular vnode.
 */
I 12
void
E 12
dqflush(vp)
	register struct vnode *vp;
{
D 29
	register union dqhead *dh;
	register struct dquot *dq, *nextdq;
E 29
I 29
	register struct dquot *dq, *dp, **dpp, *nextdq;
E 29

	/*
	 * Move all dquot's that used to refer to this quota
	 * file off their hash chains (they will eventually
	 * fall off the head of the free list and be re-used).
	 */
D 29
	for (dh = &dqhashtbl[dqhash]; dh >= dqhashtbl; dh--) {
		for (dq = dh->dqh_forw; dq != (struct dquot *)dh; dq = nextdq) {
E 29
I 29
	for (dpp = &dqhashtbl[dqhash]; dpp >= dqhashtbl; dpp--) {
		for (dq = *dpp; dq; dq = nextdq) {
E 29
			nextdq = dq->dq_forw;
			if (dq->dq_ump->um_quotas[dq->dq_type] != vp)
				continue;
			if (dq->dq_cnt)
				panic("dqflush: stray dquot");
D 29
			remque(dq);
			dq->dq_forw = dq;
			dq->dq_back = dq;
E 29
I 29
			if (dp = dq->dq_forw)
				dp->dq_back = dq->dq_back;
			*dq->dq_back = dp;
			dq->dq_forw = NULL;
			dq->dq_back = NULL;
E 29
			dq->dq_ump = (struct ufsmount *)0;
		}
	}
}
E 1
