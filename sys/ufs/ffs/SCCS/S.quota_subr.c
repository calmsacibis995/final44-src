h60361
s 00059/00000/00135
d D 7.5 89/12/30 22:45:12 mckusick 11 10
c getfs and getfsx move in from ufs_subr.c
e
s 00006/00009/00129
d D 7.4 89/05/19 15:35:15 mckusick 10 9
c merge in vnodes
e
s 00010/00005/00128
d D 7.3 88/06/29 17:20:17 bostic 9 8
c install approved copyright notice
e
s 00008/00002/00125
d D 7.2 88/05/20 12:29:37 bostic 8 7
c add Berkeley specific header
e
s 00001/00001/00126
d D 7.1 86/06/05 00:05:56 mckusick 7 6
c 4.3BSD release version
e
s 00007/00001/00120
d D 6.4 85/06/08 14:40:14 mckusick 6 5
c Add copyright
e
s 00010/00010/00111
d D 6.3 84/08/29 20:21:09 bloom 5 4
c Change to includes.  no more ../h
e
s 00000/00001/00121
d D 6.2 84/07/08 16:19:00 mckusick 4 3
c rework `namei' interface to eliminate global variables
e
s 00000/00000/00122
d D 6.1 83/07/29 06:35:20 sam 3 2
c 4.2 distribution
e
s 00014/00012/00108
d D 4.2 83/05/21 23:19:18 sam 2 1
c cleanup
e
s 00120/00000/00000
d D 4.1 83/05/21 15:50:31 sam 1 0
c date and time created 83/05/21 15:50:31 by sam
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
/*
D 7
 * Copyright (c) 1982 Regents of the University of California.
E 7
I 7
D 10
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 10
I 10
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 10
E 7
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
D 10
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
E 9
E 8
 *
 *	%W% (Berkeley) %G%
 */
E 6

#ifdef QUOTA
/*
D 2
 * Quotas: subroutines.
E 2
I 2
 * MELBOURNE QUOTAS
 *
 * Miscellaneous subroutines.
E 2
 */
D 5
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/proc.h"
#include "../h/inode.h"
#include "../h/quota.h"
#include "../h/mount.h"
#include "../h/fs.h"
#include "../h/uio.h"
E 5
I 5
#include "param.h"
I 11
#include "systm.h"
E 11
D 10
#include "systm.h"
#include "dir.h"
E 10
#include "user.h"
#include "proc.h"
D 10
#include "inode.h"
#include "quota.h"
E 10
#include "mount.h"
D 10
#include "fs.h"
#include "uio.h"
E 10
I 10
#include "../ufs/quota.h"
#include "../ufs/ufsmount.h"
#include "../ufs/fs.h"
E 10
E 5
D 4
#include "../h/nami.h"
E 4

struct dquot *
dqp(q, dev)
	struct quota *q;
	dev_t dev;
{
	register struct dquot **dqq;
	register i;

D 2
	if (q == NOQUOT || q->q_flg & Q_NDQ)
E 2
I 2
	if (q == NOQUOTA || q->q_flags & Q_NDQ)
E 2
		return (NODQUOT);
	i = getfsx(dev);
	if (i < 0 || i >= NMOUNT)
		return (NODQUOT);
	dqq = &q->q_dq[i];
	if (*dqq == LOSTDQUOT) {
D 10
		*dqq = discquota(q->q_uid, mount[i].m_qinod);
E 10
I 10
		*dqq = discquota(q->q_uid, mounttab[i].um_qinod);
E 10
		if (*dqq != NODQUOT)
			(*dqq)->dq_own = q;
	}
	if (*dqq != NODQUOT)
		(*dqq)->dq_cnt++;
	return (*dqq);
}

/*
 * Quota cleanup at process exit, or when
 * switching to another user.
 */
qclean()
{
	register struct proc *p = u.u_procp;
	register struct quota *q = p->p_quota;

D 2
	if (q == NOQUOT)
E 2
I 2
	if (q == NOQUOTA)
E 2
		return;
	/*
	 * Before we rid ourselves of this quota, we must be sure that
	 * we no longer reference it (otherwise clock might do nasties).
	 * But we have to have some quota (or clock will get upset).
	 * (Who is this clock anyway ??). So we will give ourselves
	 * root's quota for a short while, without counting this as
	 * a reference in the ref count (as either this proc is just
	 * about to die, in which case it refers to nothing, or it is
	 * about to be given a new quota, which will just overwrite this
	 * one).
	 */
	p->p_quota = quota;
	u.u_quota = quota;
	delquota(q);
}

qstart(q)
	register struct quota *q;
{

	u.u_quota = q;
	u.u_procp->p_quota = q;
}

qwarn(dq)
	register struct dquot *dq;
{
	register struct fs *fs = NULL;

D 2
	if (dq->dq_iq && dq->dq_inod >= dq->dq_iq) {
		dq->dq_flg |= DQ_MOD;
E 2
I 2
	if (dq->dq_isoftlimit && dq->dq_curinodes >= dq->dq_isoftlimit) {
		dq->dq_flags |= DQ_MOD;
E 2
		fs = getfs(dq->dq_dev);
		if (dq->dq_iwarn && --dq->dq_iwarn)
			uprintf(
			    "Warning: too many files on %s, %d warning%s left\n"
			    , fs->fs_fsmnt
			    , dq->dq_iwarn
			    , dq->dq_iwarn > 1 ? "s" : ""
			);
		else
			uprintf(
			    "WARNING: too many files on %s, NO MORE!!\n"
			    , fs->fs_fsmnt
			);
	} else
		dq->dq_iwarn = MAX_IQ_WARN;

D 2
	if (dq->dq_quot && dq->dq_blks >= dq->dq_quot) {
		dq->dq_flg |= DQ_MOD;
		if (!fs)
E 2
I 2
	if (dq->dq_bsoftlimit && dq->dq_curblocks >= dq->dq_bsoftlimit) {
		dq->dq_flags |= DQ_MOD;
		if (fs == NULL)
E 2
			fs = getfs(dq->dq_dev);
D 2
		if (dq->dq_dwarn && --dq->dq_dwarn)
E 2
I 2
		if (dq->dq_bwarn && --dq->dq_bwarn)
E 2
			uprintf(
		    "Warning: too much disc space on %s, %d warning%s left\n"
			    , fs->fs_fsmnt
D 2
			    , dq->dq_dwarn
			    , dq->dq_dwarn > 1 ? "s" : ""
E 2
I 2
			    , dq->dq_bwarn
			    , dq->dq_bwarn > 1 ? "s" : ""
E 2
			);
		else
			uprintf(
		    "WARNING: too much disc space on %s, NO MORE!!\n"
			    , fs->fs_fsmnt
			);
	} else
D 2
		dq->dq_dwarn = MAX_DQ_WARN;
E 2
I 2
		dq->dq_bwarn = MAX_DQ_WARN;
I 11
}

/*
 * Getfs maps a device number into a pointer to the incore super block.
 *
 * The algorithm is a linear search through the mount table. A
 * consistency check of the super block magic number is performed.
 * Filesystems still working on a mount are skipped.
 *
 * panic: no fs -- the device is not mounted.
 *	this "cannot happen"
 */
struct fs *
getfs(dev)
	dev_t dev;
{
	register struct ufsmount *mp;
	register struct fs *fs;

	for (mp = &mounttab[0]; mp < &mounttab[NMOUNT]; mp++) {
		if (mp->um_fs == NULL || mp->um_dev != dev ||
		    mp->um_fs == (struct fs *)1)		/* XXX */
			continue;
		fs = mp->um_fs;
		if (fs->fs_magic != FS_MAGIC) {
			printf("dev = 0x%x, fs = %s\n", dev, fs->fs_fsmnt);
			panic("getfs: bad magic");
		}
		return (fs);
	}
	printf("dev = 0x%x\n", dev);
	panic("getfs: no fs");
	return (NULL);
}

/*
 * Getfsx returns the index in the file system
 * table of the specified device.  The swap device
 * is also assigned a pseudo-index.  The index may
 * be used as a compressed indication of the location
 * of a block, recording
 *	<getfsx(dev),blkno>
 * rather than
 *	<dev, blkno>
 * provided the information need remain valid only
 * as long as the file system is mounted.
 */
getfsx(dev)
	dev_t dev;
{
	register struct ufsmount *mp;

	if (dev == swapdev)
		return (MSWAPX);
	for(mp = &mounttab[0]; mp < &mounttab[NMOUNT]; mp++)
		if (mp->um_dev == dev)
			return (mp - &mounttab[0]);
	return (-1);
E 11
E 2
}
#endif
E 1
