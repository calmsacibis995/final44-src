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
 * $Log:	kern_prot.c,v $
 * Revision 2.7.2.2  90/05/14  13:17:04  rvb
 * 	Don't leak identity obj. if operation fails after falloc.
 * 	Leak found; below undo
 * 	[90/04/27            rvb]
 * 
 * Revision 2.7.2.1  90/03/07  13:25:54  rvb
 * 		Make bigger identity_zone - have seen crashes from empty zone
 * 		while running expire(8). [kupfer]
 * 
 * Revision 2.7  89/08/02  08:03:15  jsb
 * 	Use new identity zone instead of kalloc.
 * 	[89/07/31  17:10:15  jsb]
 * 
 * Revision 2.6  89/04/22  15:20:43  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	Added subroutines to manipulate user identity information from
 * 	the user structure that is needed for network file operations.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/03/09  19:28:50  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  14:41:49  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  89/02/09  04:31:15  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.2  89/01/18  00:36:47  jsb
 * 	Vnode support, including credential support.
 * 	[89/01/13            jsb]
 * 
 *
 * 19-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Changed inodes to vnodes.  Add support for credentials
 *		 record - crget(), crfree(), crcopy(), and crdup().
 *
 * 25-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-type option.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_prot.c	7.1 (Berkeley) 6/5/86
 */

#include <quota.h>

/*
 * System calls related to processes and protection
 */

#include <machine/reg.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/acct.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/reboot.h>
#include <sys/fs.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/quota.h>
#include <kern/zalloc.h>

zone_t identity_zone;

getpid()
{

	u.u_r.r_val1 = u.u_procp->p_pid;
	u.u_r.r_val2 = u.u_procp->p_ppid;
}

getpgrp()
{
	register struct a {
		int	pid;
	} *uap = (struct a *)u.u_ap;
	register struct proc *p;

	if (uap->pid == 0)
		uap->pid = u.u_procp->p_pid;
	p = pfind(uap->pid);
	if (p == 0) {
		u.u_error = ESRCH;
		return;
	}
	u.u_r.r_val1 = p->p_pgrp;
}

/*
 * Test if the current user is the
 * super user.
 */
suser()
{

	if (u.u_uid == 0) {
		u.u_acflag |= ASU;
		return (1);
	}
	u.u_error = EPERM;
	return (0);
}

getuid()
{

	u.u_r.r_val1 = u.u_ruid;
	u.u_r.r_val2 = u.u_uid;
}

getgid()
{

	u.u_r.r_val1 = u.u_rgid;
	u.u_r.r_val2 = u.u_gid;
}

getgroups()
{
	register struct	a {
		u_int	gidsetsize;
		int	*gidset;
	} *uap = (struct a *)u.u_ap;
	register gid_t *gp;
	register int *lp;
	int groups[NGROUPS];

	for (gp = &u.u_groups[NGROUPS]; gp > u.u_groups; gp--)
		if (gp[-1] != NOGROUP)
			break;
	if (uap->gidsetsize < gp - u.u_groups) {
		u.u_error = EINVAL;
		return;
	}
	uap->gidsetsize = gp - u.u_groups;
	for (lp = groups, gp = u.u_groups; lp < &groups[uap->gidsetsize]; )
		*lp++ = *gp++;
	u.u_error = copyout((caddr_t)groups, (caddr_t)uap->gidset,
	    uap->gidsetsize * sizeof (groups[0]));
	if (u.u_error)
		return;
	u.u_r.r_val1 = uap->gidsetsize;
}

setpgrp()
{
	register struct proc *p;
	register struct a {
		int	pid;
		int	pgrp;
	} *uap = (struct a *)u.u_ap;

	if (uap->pid == 0)
		uap->pid = u.u_procp->p_pid;
	p = pfind(uap->pid);
	if (p == 0) {
		u.u_error = ESRCH;
		return;
	}
/* need better control mechanisms for process groups */
	if (p->p_uid != u.u_uid && u.u_uid && !inferior(p)) {
		u.u_error = EPERM;
		return;
	}
	p->p_pgrp = uap->pgrp;
}

setreuid()
{
	struct a {
		int	ruid;
		int	euid;
	} *uap;
	register int ruid, euid;

	uap = (struct a *)u.u_ap;
	ruid = uap->ruid;
	if (ruid == -1)
		ruid = u.u_ruid;
	if (u.u_ruid != ruid && u.u_uid != ruid && !suser())
		return;
	euid = uap->euid;
	if (euid == -1)
		euid = u.u_uid;
	if (u.u_ruid != euid && u.u_uid != euid && !suser())
		return;
	/*
	 * Everything's okay, do it.
	 */
	u.u_identity = change_identity(u.u_identity);
#if	QUOTA
	if (u.u_quota->q_uid != ruid) {
		qclean();
		qstart(getquota((uid_t)ruid, 0, 0));
	}
#endif	QUOTA
	u.u_procp->p_uid = euid;
	u.u_ruid = ruid;
	u.u_uid = euid;
}

setregid()
{
	register struct a {
		int	rgid;
		int	egid;
	} *uap;
	register int rgid, egid;

	uap = (struct a *)u.u_ap;
	rgid = uap->rgid;
	if (rgid == -1)
		rgid = u.u_rgid;
	if (u.u_rgid != rgid && u.u_gid != rgid && !suser())
		return;
	egid = uap->egid;
	if (egid == -1)
		egid = u.u_gid;
	if (u.u_rgid != egid && u.u_gid != egid && !suser())
		return;
	u.u_identity = change_identity(u.u_identity);
	if (u.u_rgid != rgid) {
		leavegroup(u.u_rgid);
		(void) entergroup((gid_t)rgid);
		u.u_rgid = rgid;
	}
	u.u_gid = egid;
}

setgroups()
{
	register struct	a {
		u_int	gidsetsize;
		int	*gidset;
	} *uap = (struct a *)u.u_ap;
	register gid_t *gp;
	register int *lp;
	int groups[NGROUPS];

	if (!suser())
		return;
	if (uap->gidsetsize > sizeof (u.u_groups) / sizeof (u.u_groups[0])) {
		u.u_error = EINVAL;
		return;
	}
	u.u_error = copyin((caddr_t)uap->gidset, (caddr_t)groups,
	    uap->gidsetsize * sizeof (groups[0]));
	if (u.u_error)
		return;
	u.u_identity = change_identity(u.u_identity);
	for (lp = groups, gp = u.u_groups; lp < &groups[uap->gidsetsize]; )
		*gp++ = *lp++;
	for ( ; gp < &u.u_groups[NGROUPS]; gp++)
		*gp = NOGROUP;
}

/*
 * Group utility functions.
 */

/*
 * Delete gid from the group set.
 */
leavegroup(gid)
	gid_t gid;
{
	register gid_t *gp;

	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++)
		if (*gp == gid)
			goto found;
	return;
found:
	for (; gp < &u.u_groups[NGROUPS-1]; gp++)
		*gp = *(gp+1);
	*gp = NOGROUP;
}

/*
 * Add gid to the group set.
 */
entergroup(gid)
	gid_t gid;
{
	register gid_t *gp;

	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS]; gp++) {
		if (*gp == gid)
			return (0);
		if (*gp == NOGROUP) {
			*gp = gid;
			return (0);
		}
	}
	return (-1);
}

/*
 * Check if gid is a member of the group set.
 */
groupmember(gid)
	gid_t gid;
{
	register gid_t *gp;

	if (u.u_gid == gid)
		return (1);
	for (gp = u.u_groups; gp < &u.u_groups[NGROUPS] && *gp != NOGROUP; gp++)
		if (*gp == gid)
			return (1);
	return (0);
}

struct identity *root_identity;

/*
 * Allocate a new user identity
 */
struct identity *
alloc_identity()
{
	register struct identity *id;

	ZALLOC(identity_zone, id, struct identity *);
	bzero((char *) id, sizeof(struct identity));
	id->id_ref++;
	return(id);
}

/*
 * Free a user identity
 */
free_identity(id)
	register struct identity *id;
{
	int s = splclock();

	if (id->id_ref == 0)
		panic("freeing unreferenced identity");

	if (--id->id_ref != 0) {
		(void) splx(s);
		return;
	}
	ZFREE(identity_zone, id);
	(void) splx(s);
}

/*
 * Create new identity from old one
 */
struct identity *
change_identity(id)
	struct identity *id;
{
	struct identity *nid;

	nid = alloc_identity();
	bcopy((char *) id, (char *) nid, sizeof(struct identity));
	free_identity(id);
	nid->id_ref = 1;
	return(nid);
}

/*
 * Create copy of identity
 */
struct identity *
copy_identity(id)
	struct identity *id;
{
	struct identity *nid;

	nid = alloc_identity();
	bcopy((char *) id, (char *) nid, sizeof(struct identity));
	nid->id_ref = 1;
 	return(nid);
}

kern_prot_init()
{
	identity_zone		= zinit(sizeof(struct identity), 1024*1024,
					0, FALSE, "identity");
}
