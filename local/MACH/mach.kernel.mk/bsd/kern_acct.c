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
 * $Log:	kern_acct.c,v $
 * Revision 2.8  89/04/22  15:19:43  gm0w
 * 	Changed to use new inode access macros for manipulation of the
 * 	system accounting file.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.7  89/03/09  19:28:01  rpd
 * 	More cleanup.
 * 
 * Revision 2.6  89/02/25  14:18:08  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.5  89/02/09  04:30:32  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.4  89/01/18  00:34:23  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.3  88/08/24  01:17:17  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  22:04:21  mwyoung]
 * 
 *
 * 19-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Add include of "sys/proc.h" to support controlling tty fields
 *	which have been moved to this structure.
 *	[ V5.1(XF23) ]
 *
 * 18-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS:  Changed inode usage to vnode usage.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 *  8-May-85  Glenn Marcy (gm0w) at Carnegie-Mellon University
 *	Upgraded to 4.2BSD.  Carried over changes below [V1(1)].
 *
 * 22-Jun-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_ACCT:  Adjusted to use account ID instead of group ID in
 *	record written to accounting file (V3.05a).
 *
 */
 
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_acct.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/fs.h>
#include <sys/kernel.h>
#include <sys/acct.h>
#include <sys/uio.h>

/*
 * SHOULD REPLACE THIS WITH A DRIVER THAT CAN BE READ TO SIMPLIFY.
 */
struct	inode *acctp;
struct	inode *savacctp;

/*
 * Perform process accounting functions.
 */
sysacct()
{
	struct inode *ip;
	struct inode *tip;
	register struct a {
		char	*fname;
	} *uap = (struct a *)u.u_ap;

	if (suser()) {
		if (savacctp) {
			acctp = savacctp;
			savacctp = NULL;
		}
		if (uap->fname==NULL) {
			if (ip = acctp) {
				acctp = NULL;
				RELEASE_INODE(ip);
			}
			return;
		}
		PATH_TO_INODE(uap->fname, ip);
		if (!INODE_TYPE(ip,REG)) {
			u.u_error = EACCES;
			FINISH_WITH_INODE(ip);
			return;
		}
		if (FS_READ_ONLY(ip)) {
			u.u_error = EROFS;
			FINISH_WITH_INODE(ip);
			return;
		}
		if (acctp) {
			tip = acctp;
			acctp = ip;
			RELEASE_INODE(tip);
		} else
			acctp = ip;
		UNLOCK_INODE(ip);
	}
}

int	acctsuspend = 2;	/* stop accounting when < 2% free space left */
int	acctresume = 4;		/* resume when free space risen to > 4% */

struct	acct acctbuf;
/*
 * On exit, write a record on the accounting file.
 */
acct()
{
	register int i;
	register struct inode *ip;
	register struct rusage *ru;
	struct timeval t;
	register struct acct *ap = &acctbuf;
	struct identity *saved_identity;
	int cmp;

	if (savacctp) {
		CHECK_FREESPACE(savacctp, acctresume, cmp);
		if (cmp > 0) {
			acctp = savacctp;
			savacctp = NULL;
			printf("Accounting resumed\n");
		}
	}
	if ((ip = acctp) == NULL)
		return;
	CHECK_FREESPACE(acctp, acctsuspend, cmp);
	if (cmp <= 0) {
		savacctp = acctp;
		acctp = NULL;
		printf("Accounting suspended\n");
		return;
	}
	LOCK_INODE(ip);
	for (i = 0; i < sizeof (ap->ac_comm); i++)
		ap->ac_comm[i] = u.u_comm[i];
	ru = &u.u_ru;
	ap->ac_utime = compress(ru->ru_utime.tv_sec, ru->ru_utime.tv_usec);
	ap->ac_stime = compress(ru->ru_stime.tv_sec, ru->ru_stime.tv_usec);
	t = time;
	timevalsub(&t, &u.u_start);
	ap->ac_etime = compress(t.tv_sec, t.tv_usec);
	ap->ac_btime = u.u_start.tv_sec;
	ap->ac_uid = u.u_ruid;
	ap->ac_gid = u.u_rgid;
	t = ru->ru_stime;
	timevaladd(&t, &ru->ru_utime);
	if (i = t.tv_sec * hz + t.tv_usec / tick)
		ap->ac_mem = (ru->ru_ixrss+ru->ru_idrss+ru->ru_isrss) / i;
	else
		ap->ac_mem = 0;
	ap->ac_mem >>= CLSIZELOG2;
	ap->ac_io = compress(ru->ru_inblock + ru->ru_oublock, (long)0);
	if (u.u_ttyp)
		ap->ac_tty = u.u_ttyd;
	else
		ap->ac_tty = NODEV;
	ap->ac_flag = u.u_acflag;
	saved_identity = u.u_identity;
	u.u_identity = root_identity;
	APPEND_TO_INODE(ip, (caddr_t)ap, sizeof(acctbuf));
	u.u_identity = saved_identity;
	UNLOCK_INODE(ip);
}

/*
 * Produce a pseudo-floating point representation
 * with 3 bits base-8 exponent, 13 bits fraction.
 */
compress(t, ut)
	register long t;
	long ut;
{
	register exp = 0, round = 0;

	t = t * AHZ;  /* compiler will convert only this format to a shift */
	if (ut)
		t += ut / (1000000 / AHZ);
	while (t >= 8192) {
		exp++;
		round = t&04;
		t >>= 3;
	}
	if (round) {
		t++;
		if (t >= 8192) {
			t >>= 3;
			exp++;
		}
	}
	return ((exp<<13) + t);
}
