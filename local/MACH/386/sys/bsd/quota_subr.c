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
 * $Log:	quota_subr.c,v $
 * Revision 2.4  89/03/09  19:29:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  14:43:34  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/02/09  04:32:05  mwyoung
 * Code cleanup cataclysm.
 * 
 * 25-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Removed dependancy on QUOTA, since this entire file is now
 *	conditionalized on it in the files file.
 *
 */

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)quota_subr.c	7.1 (Berkeley) 6/5/86
 */

/*
 * MELBOURNE QUOTAS
 *
 * Miscellaneous subroutines.
 */
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/inode.h>
#include <sys/quota.h>
#include <sys/mount.h>
#include <sys/fs.h>
#include <sys/uio.h>

struct dquot *
dqp(q, dev)
	struct quota *q;
	dev_t dev;
{
	register struct dquot **dqq;
	register i;

	if (q == NOQUOTA || q->q_flags & Q_NDQ)
		return (NODQUOT);
	i = getfsx(dev);
	if (i < 0 || i >= NMOUNT)
		return (NODQUOT);
	dqq = &q->q_dq[i];
	if (*dqq == LOSTDQUOT) {
		*dqq = discquota(q->q_uid, mount[i].m_qinod);
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

	if (q == NOQUOTA)
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

	if (dq->dq_isoftlimit && dq->dq_curinodes >= dq->dq_isoftlimit) {
		dq->dq_flags |= DQ_MOD;
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

	if (dq->dq_bsoftlimit && dq->dq_curblocks >= dq->dq_bsoftlimit) {
		dq->dq_flags |= DQ_MOD;
		if (fs == NULL)
			fs = getfs(dq->dq_dev);
		if (dq->dq_bwarn && --dq->dq_bwarn)
			uprintf(
		    "Warning: too much disc space on %s, %d warning%s left\n"
			    , fs->fs_fsmnt
			    , dq->dq_bwarn
			    , dq->dq_bwarn > 1 ? "s" : ""
			);
		else
			uprintf(
		    "WARNING: too much disc space on %s, NO MORE!!\n"
			    , fs->fs_fsmnt
			);
	} else
		dq->dq_bwarn = MAX_DQ_WARN;
}
