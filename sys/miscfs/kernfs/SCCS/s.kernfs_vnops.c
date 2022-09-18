h20813
s 00011/00004/00723
d D 8.15 95/05/21 22:44:18 mckusick 25 23
c have to follow locking protocol in kernfs_lookup
e
s 00004/00002/00725
d R 8.15 95/05/21 22:13:25 mckusick 24 23
c have to follow locking protocol in kernfs_lookup
e
s 00002/00000/00725
d D 8.14 95/05/21 19:36:36 mckusick 23 22
c inactive routine must unlock node
e
s 00007/00005/00718
d D 8.13 95/05/14 00:40:52 mckusick 22 21
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00011/00011/00712
d D 8.12 95/05/10 10:07:49 mckusick 21 20
c lookup error return cleanups (from mycroft)
e
s 00022/00031/00701
d D 8.11 95/04/03 18:43:36 mckusick 20 19
c add revoke operator
e
s 00003/00001/00729
d D 8.10 95/01/09 18:24:29 cgd 19 18
c microtime takes a timeval ptr.
e
s 00002/00000/00728
d D 8.9 94/06/15 11:06:11 pendry 18 17
c minor tweak to keep DIAGNOSTIC code from crashing
e
s 00132/00147/00596
d D 8.8 94/06/15 10:41:43 pendry 17 16
c merge netbsd modifications
e
s 00010/00000/00733
d D 8.7 94/06/04 19:34:44 mckusick 16 15
c add cookie and eofflag parameters to readdir
e
s 00001/00001/00732
d D 8.6 94/02/10 18:14:19 pendry 15 14
c disallow read from the root directory
e
s 00000/00001/00733
d D 8.5 94/01/21 19:56:26 bostic 14 13
c copyright typo
e
s 00050/00013/00684
d D 8.4 94/01/14 08:29:10 pendry 13 12
c add pathconf entry point
e
s 00006/00013/00691
d D 8.3 94/01/04 18:53:46 bostic 12 11
c lint
e
s 00002/00002/00702
d D 8.2 94/01/04 06:54:17 pendry 11 10
c allocate private VT_ tags
e
s 00002/00002/00702
d D 8.1 93/06/10 23:38:32 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00702
d D 7.9 93/05/30 13:56:49 mckusick 9 8
c missing ifdef
e
s 00012/00004/00690
d D 7.8 93/04/29 23:43:49 pendry 8 7
c fix bounds error on hostname
c remove "root" to avoid filesystem recursion.
e
s 00020/00006/00674
d D 7.7 92/10/09 22:49:37 mckusick 7 6
c cannot compute VTOKERN for root vnode
e
s 00002/00002/00678
d D 7.6 92/07/21 15:39:03 pendry 6 5
c fix write checks
e
s 00001/00000/00679
d D 7.5 92/07/19 08:13:41 pendry 5 4
c added boottime
e
s 00035/00020/00644
d D 7.4 92/07/19 04:56:06 pendry 4 3
c added raw root device support to kernfs
e
s 00002/00000/00662
d D 7.3 92/07/19 03:48:08 pendry 3 2
c unknown target names should return ENOENT in lookup
e
s 00003/00003/00659
d D 7.2 92/07/18 17:08:46 pendry 2 1
c minor clean up
e
s 00662/00000/00000
d D 7.1 92/07/18 16:42:23 pendry 1 0
c date and time created 92/07/18 16:42:23 by pendry
e
u
U
t
T
I 1
/*
D 10
 * Copyright (c) 1992 The Regents of the University of California
 * Copyright (c) 1990, 1992 Jan-Simon Pendry
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
D 14
 * All rights reserved.
E 14
 *
 * This code is derived from software donated to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Kernel parameter filesystem (/kern)
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/vmmeter.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/malloc.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/buf.h>
#include <sys/dirent.h>
#include <miscfs/kernfs/kernfs.h>

#define KSTRING	256		/* Largest I/O available via this filesystem */
#define	UIO_MX 32

I 4
#define	READ_MODE	(S_IRUSR|S_IRGRP|S_IROTH)
#define	WRITE_MODE	(S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH)
#define DIR_MODE	(S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)

E 4
struct kern_target {
I 17
	u_char kt_type;
	u_char kt_namlen;
E 17
	char *kt_name;
	void *kt_data;
D 17
#define	KTT_NULL 1
#define	KTT_TIME 5
#define KTT_INT	17
#define	KTT_STRING 31
#define KTT_HOSTNAME 47
#define KTT_AVENRUN 53
	int kt_tag;
D 4
#define	KTM_RO	0
#define	KTM_RO_MODE		(S_IRUSR|S_IRGRP|S_IROTH)
#define	KTM_RW	43
#define	KTM_RW_MODE		(S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH)
#define KTM_DIR_MODE (S_IRUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)
E 4
	int kt_rw;
	int kt_vtype;
E 17
I 17
#define	KTT_NULL	 1
#define	KTT_TIME	 5
#define KTT_INT		17
#define	KTT_STRING	31
#define KTT_HOSTNAME	47
#define KTT_AVENRUN	53
#define KTT_DEVICE	71
	u_char kt_tag;
	u_char kt_vtype;
	mode_t kt_mode;
E 17
} kern_targets[] = {
/* NOTE: The name must be less than UIO_MX-16 chars in length */
D 17
	/* name		data		tag		ro/rw */
D 4
	{ ".",		0,		KTT_NULL,	KTM_RO,	VDIR },
	{ "copyright",	copyright,	KTT_STRING,	KTM_RO,	VREG },
	{ "hostname",	0,		KTT_HOSTNAME,	KTM_RW,	VREG },
	{ "hz",		&hz,		KTT_INT,	KTM_RO,	VREG },
	{ "loadavg",	0,		KTT_AVENRUN,	KTM_RO,	VREG },
	{ "pagesize",	&cnt.v_page_size, KTT_INT,	KTM_RO,	VREG },
	{ "physmem",	&physmem,	KTT_INT,	KTM_RO,	VREG },
	{ "root",	0,		KTT_NULL,	KTM_RO,	VDIR },
	{ "rootdev",	0,		KTT_NULL,	KTM_RO,	VBLK },
	{ "time",	0,		KTT_TIME,	KTM_RO,	VREG },
	{ "version",	version,	KTT_STRING,	KTM_RO,	VREG },
E 4
I 4
	{ ".",		0,		KTT_NULL,	VREAD,		VDIR },
	{ "..",		0,		KTT_NULL,	VREAD,		VDIR },
I 5
	{ "boottime",	&boottime.tv_sec, KTT_INT,	VREAD,		VREG },
E 5
	{ "copyright",	copyright,	KTT_STRING,	VREAD,		VREG },
	{ "hostname",	0,		KTT_HOSTNAME,	VREAD|VWRITE,	VREG },
	{ "hz",		&hz,		KTT_INT,	VREAD,		VREG },
	{ "loadavg",	0,		KTT_AVENRUN,	VREAD,		VREG },
	{ "pagesize",	&cnt.v_page_size, KTT_INT,	VREAD,		VREG },
	{ "physmem",	&physmem,	KTT_INT,	VREAD,		VREG },
E 17
I 17
#define N(s) sizeof(s)-1, s
     /*        name            data          tag           type  ro/rw */
     { DT_DIR, N("."),         0,            KTT_NULL,     VDIR, DIR_MODE   },
     { DT_DIR, N(".."),        0,            KTT_NULL,     VDIR, DIR_MODE   },
     { DT_REG, N("boottime"),  &boottime.tv_sec, KTT_INT,  VREG, READ_MODE  },
     { DT_REG, N("copyright"), copyright,    KTT_STRING,   VREG, READ_MODE  },
     { DT_REG, N("hostname"),  0,            KTT_HOSTNAME, VREG, WRITE_MODE },
     { DT_REG, N("hz"),        &hz,          KTT_INT,      VREG, READ_MODE  },
     { DT_REG, N("loadavg"),   0,            KTT_AVENRUN,  VREG, READ_MODE  },
     { DT_REG, N("pagesize"),  &cnt.v_page_size, KTT_INT,  VREG, READ_MODE  },
     { DT_REG, N("physmem"),   &physmem,     KTT_INT,      VREG, READ_MODE  },
E 17
I 8
#if 0
E 8
D 17
	{ "root",	0,		KTT_NULL,	VREAD,		VDIR },
E 17
I 17
     { DT_DIR, N("root"),      0,            KTT_NULL,     VDIR, DIR_MODE   },
E 17
I 8
#endif
E 8
D 17
	{ "rootdev",	0,		KTT_NULL,	VREAD,		VBLK },
	{ "rrootdev",	0,		KTT_NULL,	VREAD,		VCHR },
	{ "time",	0,		KTT_TIME,	VREAD,		VREG },
	{ "version",	version,	KTT_STRING,	VREAD,		VREG },
E 17
I 17
     { DT_BLK, N("rootdev"),   &rootdev,     KTT_DEVICE,   VBLK, READ_MODE  },
     { DT_CHR, N("rrootdev"),  &rrootdev,    KTT_DEVICE,   VCHR, READ_MODE  },
     { DT_REG, N("time"),      0,            KTT_TIME,     VREG, READ_MODE  },
     { DT_REG, N("version"),   version,      KTT_STRING,   VREG, READ_MODE  },
#undef N
E 17
E 4
};
D 17

E 17
static int nkern_targets = sizeof(kern_targets) / sizeof(kern_targets[0]);

static int
kernfs_xread(kt, buf, len, lenp)
	struct kern_target *kt;
	char *buf;
	int len;
	int *lenp;
{
I 17

E 17
D 12
	int xlen;

E 12
	switch (kt->kt_tag) {
	case KTT_TIME: {
		struct timeval tv;
		microtime(&tv);
		sprintf(buf, "%d %d\n", tv.tv_sec, tv.tv_usec);
		break;
	}

	case KTT_INT: {
		int *ip = kt->kt_data;
		sprintf(buf, "%d\n", *ip);
		break;
	}

	case KTT_STRING: {
		char *cp = kt->kt_data;
		int xlen = strlen(cp) + 1;

		if (xlen >= len)
			return (EINVAL);

		bcopy(cp, buf, xlen);
		break;
	}

	case KTT_HOSTNAME: {
		char *cp = hostname;
		int xlen = hostnamelen;

D 8
		if (xlen >= len)
E 8
I 8
		if (xlen >= (len-2))
E 8
			return (EINVAL);

D 8
		sprintf(buf, "%s\n", cp);
E 8
I 8
		bcopy(cp, buf, xlen);
		buf[xlen] = '\n';
		buf[xlen+1] = '\0';
E 8
		break;
	}

	case KTT_AVENRUN:
		sprintf(buf, "%ld %ld %ld %ld\n",
D 17
				averunnable.ldavg[0],
				averunnable.ldavg[1],
				averunnable.ldavg[2],
				averunnable.fscale);
E 17
I 17
		    averunnable.ldavg[0], averunnable.ldavg[1],
		    averunnable.ldavg[2], averunnable.fscale);
E 17
		break;

	default:
D 17
		return (EINVAL);
E 17
I 17
		return (EIO);
E 17
	}

	*lenp = strlen(buf);
	return (0);
}

static int
kernfs_xwrite(kt, buf, len)
	struct kern_target *kt;
	char *buf;
	int len;
{
I 17

E 17
	switch (kt->kt_tag) {
D 17
	case KTT_HOSTNAME: {
E 17
I 17
	case KTT_HOSTNAME:
E 17
		if (buf[len-1] == '\n')
			--len;
		bcopy(buf, hostname, len);
D 8
		hostnamelen = len - 1;
E 8
I 8
		hostname[len] = '\0';
		hostnamelen = len;
E 8
		return (0);
D 17
	}
E 17

	default:
		return (EIO);
	}
}


/*
 * vp is the current namei directory
 * ndp is the name to locate in that directory...
 */
kernfs_lookup(ap)
	struct vop_lookup_args /* {
		struct vnode * a_dvp;
		struct vnode ** a_vpp;
		struct componentname * a_cnp;
	} */ *ap;
{
I 17
	struct componentname *cnp = ap->a_cnp;
E 17
	struct vnode **vpp = ap->a_vpp;
	struct vnode *dvp = ap->a_dvp;
D 17
	struct componentname *cnp = ap->a_cnp;
E 17
I 17
	char *pname = cnp->cn_nameptr;
I 22
	struct proc *p = cnp->cn_proc;
E 22
	struct kern_target *kt;
E 17
D 12
	char *pname;
	struct proc *p;
	int error;
E 12
	struct vnode *fvp;
D 12
	int i;
E 12
I 12
	int error, i;
D 17
	char *pname;
E 17
E 12

#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_lookup(%x)\n", ap);
	printf("kernfs_lookup(dp = %x, vpp = %x, cnp = %x)\n", dvp, vpp, ap->a_cnp);
D 17
#endif
	pname = cnp->cn_nameptr;
#ifdef KERNFS_DIAGNOSTIC
E 17
	printf("kernfs_lookup(%s)\n", pname);
#endif
I 17

I 21
	*vpp = NULLVP;

	if (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME)
		return (EROFS);

I 25
	VOP_UNLOCK(dvp, 0, p);
E 25
E 21
E 17
	if (cnp->cn_namelen == 1 && *pname == '.') {
		*vpp = dvp;
D 2
		VREF(dvp);	
E 2
I 2
		VREF(dvp);
E 2
D 25
		/*VOP_LOCK(dvp);*/
E 25
I 25
		vn_lock(dvp, LK_SHARED | LK_RETRY, p);
E 25
		return (0);
	}

I 8
#if 0
E 8
	if (cnp->cn_namelen == 4 && bcmp(pname, "root", 4) == 0) {
		*vpp = rootdir;
		VREF(rootdir);
D 22
		VOP_LOCK(rootdir);
E 22
I 22
D 25
		vn_lock(rootdir, LK_EXCLUSIVE | LK_RETRY, p)
E 25
I 25
		vn_lock(rootdir, LK_SHARED | LK_RETRY, p)
E 25
E 22
		return (0);
	}
I 8
#endif
E 8
D 2
	
E 2
I 2

I 18
D 21
	*vpp = NULLVP;

E 18
E 2
D 17
	/*
	 * /kern/rootdev is the root device
	 */
	if (cnp->cn_namelen == 7 && bcmp(pname, "rootdev", 7) == 0) {
		*vpp = rootvp;
		VREF(rootvp);
		VOP_LOCK(rootvp);
		return (0);
	}

I 4
	/*
	 * /kern/rrootdev is the raw root device
	 */
	if (cnp->cn_namelen == 8 && bcmp(pname, "rrootdev", 8) == 0) {
		if (rrootvp) {
			*vpp = rrootvp;
			VREF(rrootvp);
			VOP_LOCK(rrootvp);
			return (0);
		}
		error = ENXIO;
		goto bad;
	}

E 4
I 3
	error = ENOENT;

E 3
	for (i = 0; i < nkern_targets; i++) {
		struct kern_target *kt = &kern_targets[i];
		if (cnp->cn_namelen == strlen(kt->kt_name) &&
E 17
I 17
	for (error = ENOENT, kt = kern_targets, i = 0; i < nkern_targets;
	     kt++, i++) {
E 21
I 21
	for (kt = kern_targets, i = 0; i < nkern_targets; kt++, i++) {
E 21
		if (cnp->cn_namelen == kt->kt_namlen &&
E 17
D 21
		    bcmp(kt->kt_name, pname, cnp->cn_namelen) == 0) {
			error = 0;
			break;
		}
E 21
I 21
		    bcmp(kt->kt_name, pname, cnp->cn_namelen) == 0)
			goto found;
E 21
	}

#ifdef KERNFS_DIAGNOSTIC
D 21
	printf("kernfs_lookup: i = %d, error = %d\n", i, error);
E 21
I 21
	printf("kernfs_lookup: i = %d, failed", i);
E 21
#endif

I 25
	vn_lock(dvp, LK_SHARED | LK_RETRY, p);
E 25
D 21
	if (error)
D 17
		goto bad;
E 17
I 17
		return (error);
E 21
I 21
	return (cnp->cn_nameiop == LOOKUP ? ENOENT : EROFS);
E 21
E 17

I 21
found:
E 21
I 17
	if (kt->kt_tag == KTT_DEVICE) {
		dev_t *dp = kt->kt_data;
	loop:
D 25
		if (*dp == NODEV || !vfinddev(*dp, kt->kt_vtype, &fvp))
E 25
I 25
		if (*dp == NODEV || !vfinddev(*dp, kt->kt_vtype, &fvp)) {
			vn_lock(dvp, LK_SHARED | LK_RETRY, p);
E 25
			return (ENOENT);
I 25
		}
E 25
		*vpp = fvp;
D 22
		if (vget(fvp, 1))
E 22
I 22
		if (vget(fvp, LK_EXCLUSIVE, p))
E 22
			goto loop;
		return (0);
	}

E 17
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_lookup: allocate new vnode\n");
#endif
D 11
	error = getnewvnode(VT_UFS, dvp->v_mount, kernfs_vnodeop_p, &fvp);
E 11
I 11
D 17
	error = getnewvnode(VT_KERNFS, dvp->v_mount, kernfs_vnodeop_p, &fvp);
E 11
	if (error)
		goto bad;
	MALLOC(fvp->v_data, void *, sizeof(struct kernfs_node), M_TEMP, M_WAITOK);
	VTOKERN(fvp)->kf_kt = &kern_targets[i];
	fvp->v_type = VTOKERN(fvp)->kf_kt->kt_vtype;
E 17
I 17
	if (error = getnewvnode(VT_KERNFS, dvp->v_mount, kernfs_vnodeop_p,
D 25
	    &fvp))
E 25
I 25
	    &fvp)) {
		vn_lock(dvp, LK_SHARED | LK_RETRY, p);
E 25
		return (error);
I 25
	}
E 25

	MALLOC(fvp->v_data, void *, sizeof(struct kernfs_node), M_TEMP,
	    M_WAITOK);
	VTOKERN(fvp)->kf_kt = kt;
	fvp->v_type = kt->kt_vtype;
I 25
	vn_lock(fvp, LK_SHARED | LK_RETRY, p);
E 25
E 17
	*vpp = fvp;
I 17

E 17
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_lookup: newvp = %x\n", fvp);
#endif
	return (0);
D 17

bad:;
	*vpp = NULL;
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_lookup: error = %d\n", error);
#endif
	return (error);
E 17
}

kernfs_open(ap)
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
D 17
	struct vnode *vp = ap->a_vp;
E 17

D 17
	/*
	 * Can always open the root (modulo perms)
	 */
	if (vp->v_flag & VROOT)
		return (0);

#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_open, mode = %x, file = %s\n",
			ap->a_mode, VTOKERN(vp)->kf_kt->kt_name);
#endif

D 4
	if ((ap->a_mode & FWRITE) && VTOKERN(vp)->kf_kt->kt_rw != KTM_RW)
E 4
I 4
D 6
	if ((ap->a_mode & FWRITE) && VTOKERN(vp)->kf_kt->kt_rw != VWRITE)
E 6
I 6
	if ((ap->a_mode & FWRITE) && !(VTOKERN(vp)->kf_kt->kt_rw & VWRITE))
E 6
E 4
D 8
		return (EBADF);
E 8
I 8
		return (EOPNOTSUPP);
E 8

E 17
I 17
	/* Only need to check access permissions. */
E 17
	return (0);
}

static int
kernfs_access(ap)
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
D 17
	struct vnode *vp = ap->a_vp;
	struct ucred *cred = ap->a_cred;
D 7
	struct kern_target *kt = VTOKERN(vp)->kf_kt;
E 7
	mode_t mode = ap->a_mode;
E 17
I 17
	register struct vnode *vp = ap->a_vp;
	register struct ucred *cred = ap->a_cred;
	mode_t amode = ap->a_mode;
	mode_t fmode =
	    (vp->v_flag & VROOT) ? DIR_MODE : VTOKERN(vp)->kf_kt->kt_mode;
	mode_t mask = 0;
	register gid_t *gp;
	int i;
E 17

D 17
	if (mode & VEXEC) {
		if (vp->v_flag & VROOT)
			return (0);
		return (EACCES);
	}
E 17
I 17
	/* Some files are simply not modifiable. */
	if ((amode & VWRITE) && (fmode & (S_IWUSR|S_IWGRP|S_IWOTH)) == 0)
		return (EPERM);
E 17

D 17
	if (cred->cr_uid == 0) {
D 4
		if ((mode & VWRITE) && (kt->kt_rw != KTM_RW))
E 4
I 4
D 6
		if ((mode & VWRITE) && (kt->kt_rw != VWRITE))
E 6
I 6
D 7
		if ((mode & VWRITE) && !(kt->kt_rw & VWRITE))
E 6
E 4
			return (EROFS);
E 7
I 7
		if ((vp->v_flag & VROOT) == 0) {
			struct kern_target *kt = VTOKERN(vp)->kf_kt;
E 17
I 17
	/* Root can do anything else. */
	if (cred->cr_uid == 0)
		return (0);
E 17

D 17
			if ((mode & VWRITE) && !(kt->kt_rw & VWRITE))
				return (EROFS);
E 17
I 17
	/* Check for group 0 (wheel) permissions. */
	for (i = 0, gp = cred->cr_groups; i < cred->cr_ngroups; i++, gp++)
		if (*gp == 0) {
			if (amode & VEXEC)
				mask |= S_IXGRP;
			if (amode & VREAD)
				mask |= S_IRGRP;
			if (amode & VWRITE)
				mask |= S_IWGRP;
			return ((fmode & mask) == mask ?  0 : EACCES);
E 17
		}
E 7
D 17
		return (0);
	}
E 17

D 17
	if (mode & VWRITE)
		return (EACCES);

	return (0);
E 17
I 17
        /* Otherwise, check everyone else. */
	if (amode & VEXEC)
		mask |= S_IXOTH;
	if (amode & VREAD)
		mask |= S_IROTH;
	if (amode & VWRITE)
		mask |= S_IWOTH;
	return ((fmode & mask) == mask ? 0 : EACCES);
E 17
}

D 17

E 17
kernfs_getattr(ap)
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct vattr *vap = ap->a_vap;
I 19
	struct timeval tv;
E 19
	int error = 0;
	char strbuf[KSTRING];
D 7
	struct kern_target *kt = VTOKERN(vp)->kf_kt;
E 7

	bzero((caddr_t) vap, sizeof(*vap));
	vattr_null(vap);
	vap->va_uid = 0;
	vap->va_gid = 0;
	vap->va_fsid = vp->v_mount->mnt_stat.f_fsid.val[0];
D 17
	/* vap->va_qsize = 0; */
E 17
I 17
	vap->va_size = 0;
E 17
	vap->va_blocksize = DEV_BSIZE;
D 19
	microtime(&vap->va_atime);
E 19
I 19
	microtime(&tv);
	TIMEVAL_TO_TIMESPEC(&tv, &vap->va_atime);
E 19
	vap->va_mtime = vap->va_atime;
	vap->va_ctime = vap->va_ctime;
	vap->va_gen = 0;
	vap->va_flags = 0;
	vap->va_rdev = 0;
D 17
	/* vap->va_qbytes = 0; */
E 17
	vap->va_bytes = 0;

	if (vp->v_flag & VROOT) {
#ifdef KERNFS_DIAGNOSTIC
		printf("kernfs_getattr: stat rootdir\n");
#endif
		vap->va_type = VDIR;
D 4
		vap->va_mode = KTM_DIR_MODE;
E 4
I 4
		vap->va_mode = DIR_MODE;
E 4
		vap->va_nlink = 2;
		vap->va_fileid = 2;
		vap->va_size = DEV_BSIZE;
	} else {
I 7
		struct kern_target *kt = VTOKERN(vp)->kf_kt;
E 7
		int nbytes;
#ifdef KERNFS_DIAGNOSTIC
		printf("kernfs_getattr: stat target %s\n", kt->kt_name);
#endif
		vap->va_type = kt->kt_vtype;
D 4
		vap->va_mode = (kt->kt_rw ? KTM_RW_MODE : KTM_RO_MODE);
E 4
I 4
D 17
		vap->va_mode = (kt->kt_rw & VWRITE ? WRITE_MODE : READ_MODE);
E 17
I 17
		vap->va_mode = kt->kt_mode;
E 17
E 4
		vap->va_nlink = 1;
D 17
		vap->va_fileid = 3 + (kt - kern_targets) / sizeof(*kt);
E 17
I 17
		vap->va_fileid = 1 + (kt - kern_targets) / sizeof(*kt);
E 17
		error = kernfs_xread(kt, strbuf, sizeof(strbuf), &nbytes);
		vap->va_size = nbytes;
	}

D 17
	vp->v_type = vap->va_type;
E 17
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_getattr: return error %d\n", error);
#endif
	return (error);
}

kernfs_setattr(ap)
	struct vop_setattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{

	/*
	 * Silently ignore attribute changes.
	 * This allows for open with truncate to have no
	 * effect until some data is written.  I want to
	 * do it this way because all writes are atomic.
	 */
	return (0);
}

static int
kernfs_read(ap)
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
D 7
	struct kern_target *kt = VTOKERN(vp)->kf_kt;
E 7
I 7
	struct kern_target *kt;
E 7
	char strbuf[KSTRING];
	int off = uio->uio_offset;
D 12
	int len = 0;
	char *cp = strbuf;
	int error;
E 12
I 12
	int error, len;
	char *cp;
E 12
I 7

D 17
	if (vp->v_flag & VROOT)
E 17
I 17
	if (vp->v_type == VDIR)
E 17
D 15
		return (0);
E 15
I 15
		return (EOPNOTSUPP);
E 15

	kt = VTOKERN(vp)->kf_kt;

E 7
#ifdef KERNFS_DIAGNOSTIC
	printf("kern_read %s\n", kt->kt_name);
#endif

I 12
	len = 0;
E 12
D 17
	error = kernfs_xread(kt, strbuf, sizeof(strbuf), &len);
	if (error)
E 17
I 17
	if (error = kernfs_xread(kt, strbuf, sizeof(strbuf), &len))
E 17
		return (error);
D 17
	cp = strbuf + off;
	len -= off;
	return (uiomove(cp, len, uio));
E 17
I 17
	if (len <= off)
		return (0);
	return (uiomove(&strbuf[off], len - off, uio));
E 17
}

static int
kernfs_write(ap)
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct uio *uio = ap->a_uio;
D 7
	struct kern_target *kt = VTOKERN(vp)->kf_kt;
E 7
I 7
	struct kern_target *kt;
I 12
	int error, xlen;
E 12
E 7
	char strbuf[KSTRING];
D 12
	int len = uio->uio_resid;
	char *cp = strbuf;
	int xlen;
	int error;
E 12
I 7

D 17
	if (vp->v_flag & VROOT)
		return (0);
E 17
I 17
	if (vp->v_type == VDIR)
		return (EOPNOTSUPP);
E 17

	kt = VTOKERN(vp)->kf_kt;
E 7

	if (uio->uio_offset != 0)
		return (EINVAL);

	xlen = min(uio->uio_resid, KSTRING-1);
D 17
	error = uiomove(strbuf, xlen, uio);
	if (error)
E 17
I 17
	if (error = uiomove(strbuf, xlen, uio))
E 17
		return (error);

	if (uio->uio_resid != 0)
		return (EIO);

	strbuf[xlen] = '\0';
I 8
	xlen = strlen(strbuf);
E 8
	return (kernfs_xwrite(kt, strbuf, xlen));
}

D 17

E 17
kernfs_readdir(ap)
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
I 16
		int *a_eofflag;
		u_long *a_cookies;
		int a_ncookies;
E 16
	} */ *ap;
{
I 17
	int error, i;
E 17
	struct uio *uio = ap->a_uio;
D 17
	int i;
	int error;
E 17
I 17
	struct kern_target *kt;
	struct dirent d;
E 17
I 16

I 17
	if (ap->a_vp->v_type != VDIR)
		return (ENOTDIR);

E 17
	/*
	 * We don't allow exporting kernfs mounts, and currently local
	 * requests do not need cookies.
	 */
D 17
	if (ap->a_ncookies)
E 17
I 17
	if (ap->a_ncookies != NULL)
E 17
		panic("kernfs_readdir: not hungry");
E 16

	i = uio->uio_offset / UIO_MX;
	error = 0;
D 17
	while (uio->uio_resid > 0 && i < nkern_targets) {
		struct dirent d;
E 17
I 17
	for (kt = &kern_targets[i];
		uio->uio_resid >= UIO_MX && i < nkern_targets; kt++, i++) {
E 17
		struct dirent *dp = &d;
D 17
		struct kern_target *kt = &kern_targets[i];
E 17
#ifdef KERNFS_DIAGNOSTIC
		printf("kernfs_readdir: i = %d\n", i);
#endif

D 17
		bzero((caddr_t) dp, UIO_MX);
E 17
I 17
		if (kt->kt_tag == KTT_DEVICE) {
			dev_t *dp = kt->kt_data;
			struct vnode *fvp;
E 17

D 17
		dp->d_namlen = strlen(kt->kt_name);
		bcopy(kt->kt_name, dp->d_name, dp->d_namlen+1);
E 17
I 17
			if (*dp == NODEV || !vfinddev(*dp, kt->kt_vtype, &fvp))
				continue;
		}
E 17

I 17
		bzero((caddr_t)dp, UIO_MX);
		dp->d_namlen = kt->kt_namlen;
		bcopy(kt->kt_name, dp->d_name, kt->kt_namlen+1);

E 17
#ifdef KERNFS_DIAGNOSTIC
		printf("kernfs_readdir: name = %s, len = %d\n",
				dp->d_name, dp->d_namlen);
#endif
		/*
		 * Fill in the remaining fields
		 */
		dp->d_reclen = UIO_MX;
		dp->d_fileno = i + 3;
D 17
		dp->d_type = DT_UNKNOWN;	/* XXX */
E 17
I 17
		dp->d_type = kt->kt_type;
E 17
		/*
		 * And ship to userland
		 */
D 17
		error = uiomove((caddr_t) dp, UIO_MX, uio);
		if (error)
E 17
I 17
		if (error = uiomove((caddr_t)dp, UIO_MX, uio))
E 17
			break;
D 17
		i++;
E 17
	}

	uio->uio_offset = i * UIO_MX;

	return (error);
}

kernfs_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 23
		struct proc *a_p;
E 23
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;

I 17
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_inactive(%x)\n", vp);
#endif
E 17
	/*
	 * Clear out the v_type field to avoid
	 * nasty things happening in vgone().
	 */
I 23
	VOP_UNLOCK(vp, 0, ap->a_p);
E 23
	vp->v_type = VNON;
D 17
#ifdef KERNFS_DIAGNOSTIC
	printf("kernfs_inactive(%x)\n", vp);
#endif
E 17
	return (0);
}

kernfs_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
I 17

E 17
I 9
#ifdef KERNFS_DIAGNOSTIC
E 9
	printf("kernfs_reclaim(%x)\n", vp);
I 9
#endif
E 9
	if (vp->v_data) {
		FREE(vp->v_data, M_TEMP);
		vp->v_data = 0;
	}
	return (0);
}

/*
I 13
 * Return POSIX pathconf information applicable to special devices.
 */
kernfs_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_MAX_CANON:
		*ap->a_retval = MAX_CANON;
		return (0);
	case _PC_MAX_INPUT:
		*ap->a_retval = MAX_INPUT;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_VDISABLE:
		*ap->a_retval = _POSIX_VDISABLE;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}

/*
E 13
 * Print out the contents of a /dev/fd vnode.
 */
/* ARGSUSED */
kernfs_print(ap)
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
{

D 11
	printf("tag VT_NON, kernfs vnode\n");
E 11
I 11
	printf("tag VT_KERNFS, kernfs vnode\n");
E 11
	return (0);
}

/*void*/
kernfs_vfree(ap)
	struct vop_vfree_args /* {
		struct vnode *a_pvp;
		ino_t a_ino;
		int a_mode;
	} */ *ap;
{

	return (0);
}

/*
D 20
 * /dev/fd vnode unsupported operation
 */
kernfs_enotsupp()
{

	return (EOPNOTSUPP);
}

/*
E 20
 * /dev/fd "should never get here" operation
 */
kernfs_badop()
{

	panic("kernfs: bad op");
	/* NOTREACHED */
}

/*
D 2
 * /dev/fd vnode null operation
E 2
I 2
 * kernfs vnode null operation
E 2
 */
kernfs_nullop()
{

	return (0);
}

D 20
#define kernfs_create ((int (*) __P((struct  vop_create_args *)))kernfs_enotsupp)
#define kernfs_mknod ((int (*) __P((struct  vop_mknod_args *)))kernfs_enotsupp)
E 20
I 20
#define kernfs_create ((int (*) __P((struct  vop_create_args *)))eopnotsupp)
#define kernfs_mknod ((int (*) __P((struct  vop_mknod_args *)))eopnotsupp)
E 20
#define kernfs_close ((int (*) __P((struct  vop_close_args *)))nullop)
D 20
#define kernfs_ioctl ((int (*) __P((struct  vop_ioctl_args *)))kernfs_enotsupp)
#define kernfs_select ((int (*) __P((struct  vop_select_args *)))kernfs_enotsupp)
#define kernfs_mmap ((int (*) __P((struct  vop_mmap_args *)))kernfs_enotsupp)
E 20
I 20
#define kernfs_ioctl ((int (*) __P((struct  vop_ioctl_args *)))eopnotsupp)
#define kernfs_select ((int (*) __P((struct  vop_select_args *)))eopnotsupp)
#define kernfs_revoke vop_revoke
#define kernfs_mmap ((int (*) __P((struct  vop_mmap_args *)))eopnotsupp)
E 20
#define kernfs_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define kernfs_seek ((int (*) __P((struct  vop_seek_args *)))nullop)
D 20
#define kernfs_remove ((int (*) __P((struct  vop_remove_args *)))kernfs_enotsupp)
#define kernfs_link ((int (*) __P((struct  vop_link_args *)))kernfs_enotsupp)
#define kernfs_rename ((int (*) __P((struct  vop_rename_args *)))kernfs_enotsupp)
#define kernfs_mkdir ((int (*) __P((struct  vop_mkdir_args *)))kernfs_enotsupp)
#define kernfs_rmdir ((int (*) __P((struct  vop_rmdir_args *)))kernfs_enotsupp)
#define kernfs_symlink ((int (*) __P((struct vop_symlink_args *)))kernfs_enotsupp)
#define kernfs_readlink \
	((int (*) __P((struct  vop_readlink_args *)))kernfs_enotsupp)
E 20
I 20
#define kernfs_remove ((int (*) __P((struct  vop_remove_args *)))eopnotsupp)
#define kernfs_link ((int (*) __P((struct  vop_link_args *)))eopnotsupp)
#define kernfs_rename ((int (*) __P((struct  vop_rename_args *)))eopnotsupp)
#define kernfs_mkdir ((int (*) __P((struct  vop_mkdir_args *)))eopnotsupp)
#define kernfs_rmdir ((int (*) __P((struct  vop_rmdir_args *)))eopnotsupp)
#define kernfs_symlink ((int (*) __P((struct vop_symlink_args *)))eopnotsupp)
#define kernfs_readlink ((int (*) __P((struct  vop_readlink_args *)))eopnotsupp)
E 20
#define kernfs_abortop ((int (*) __P((struct  vop_abortop_args *)))nullop)
D 22
#define kernfs_lock ((int (*) __P((struct  vop_lock_args *)))nullop)
#define kernfs_unlock ((int (*) __P((struct  vop_unlock_args *)))nullop)
E 22
I 22
#define kernfs_lock ((int (*) __P((struct  vop_lock_args *)))vop_nolock)
#define kernfs_unlock ((int (*) __P((struct  vop_unlock_args *)))vop_nounlock)
E 22
#define kernfs_bmap ((int (*) __P((struct  vop_bmap_args *)))kernfs_badop)
D 20
#define kernfs_strategy ((int (*) __P((struct  vop_strategy_args *)))kernfs_badop)
E 20
I 20
#define kernfs_strategy \
	((int (*) __P((struct  vop_strategy_args *)))kernfs_badop)
E 20
D 22
#define kernfs_islocked ((int (*) __P((struct  vop_islocked_args *)))nullop)
E 22
I 22
#define kernfs_islocked \
	((int (*) __P((struct vop_islocked_args *)))vop_noislocked)
E 22
D 20
#define kernfs_advlock ((int (*) __P((struct vop_advlock_args *)))kernfs_enotsupp)
#define kernfs_blkatoff \
	((int (*) __P((struct  vop_blkatoff_args *)))kernfs_enotsupp)
E 20
I 20
#define kernfs_advlock ((int (*) __P((struct vop_advlock_args *)))eopnotsupp)
#define kernfs_blkatoff ((int (*) __P((struct  vop_blkatoff_args *)))eopnotsupp)
E 20
#define kernfs_valloc ((int(*) __P(( \
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
D 20
		struct vnode **vpp))) kernfs_enotsupp)
#define kernfs_truncate \
	((int (*) __P((struct  vop_truncate_args *)))kernfs_enotsupp)
#define kernfs_update ((int (*) __P((struct  vop_update_args *)))kernfs_enotsupp)
#define kernfs_bwrite ((int (*) __P((struct  vop_bwrite_args *)))kernfs_enotsupp)
E 20
I 20
		struct vnode **vpp))) eopnotsupp)
#define kernfs_truncate ((int (*) __P((struct  vop_truncate_args *)))eopnotsupp)
#define kernfs_update ((int (*) __P((struct  vop_update_args *)))eopnotsupp)
#define kernfs_bwrite ((int (*) __P((struct  vop_bwrite_args *)))eopnotsupp)
E 20

int (**kernfs_vnodeop_p)();
struct vnodeopv_entry_desc kernfs_vnodeop_entries[] = {
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, kernfs_lookup },	/* lookup */
	{ &vop_create_desc, kernfs_create },	/* create */
	{ &vop_mknod_desc, kernfs_mknod },	/* mknod */
D 13
	{ &vop_open_desc, kernfs_open },		/* open */
E 13
I 13
	{ &vop_open_desc, kernfs_open },	/* open */
E 13
	{ &vop_close_desc, kernfs_close },	/* close */
	{ &vop_access_desc, kernfs_access },	/* access */
	{ &vop_getattr_desc, kernfs_getattr },	/* getattr */
	{ &vop_setattr_desc, kernfs_setattr },	/* setattr */
D 13
	{ &vop_read_desc, kernfs_read },		/* read */
E 13
I 13
	{ &vop_read_desc, kernfs_read },	/* read */
E 13
	{ &vop_write_desc, kernfs_write },	/* write */
	{ &vop_ioctl_desc, kernfs_ioctl },	/* ioctl */
	{ &vop_select_desc, kernfs_select },	/* select */
I 20
	{ &vop_revoke_desc, kernfs_revoke },	/* revoke */
E 20
D 13
	{ &vop_mmap_desc, kernfs_mmap },		/* mmap */
E 13
I 13
	{ &vop_mmap_desc, kernfs_mmap },	/* mmap */
E 13
	{ &vop_fsync_desc, kernfs_fsync },	/* fsync */
D 13
	{ &vop_seek_desc, kernfs_seek },		/* seek */
E 13
I 13
	{ &vop_seek_desc, kernfs_seek },	/* seek */
E 13
	{ &vop_remove_desc, kernfs_remove },	/* remove */
D 13
	{ &vop_link_desc, kernfs_link },		/* link */
E 13
I 13
	{ &vop_link_desc, kernfs_link },	/* link */
E 13
	{ &vop_rename_desc, kernfs_rename },	/* rename */
	{ &vop_mkdir_desc, kernfs_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, kernfs_rmdir },	/* rmdir */
	{ &vop_symlink_desc, kernfs_symlink },	/* symlink */
	{ &vop_readdir_desc, kernfs_readdir },	/* readdir */
D 13
	{ &vop_readlink_desc, kernfs_readlink },	/* readlink */
E 13
I 13
	{ &vop_readlink_desc, kernfs_readlink },/* readlink */
E 13
	{ &vop_abortop_desc, kernfs_abortop },	/* abortop */
D 13
	{ &vop_inactive_desc, kernfs_inactive },	/* inactive */
E 13
I 13
	{ &vop_inactive_desc, kernfs_inactive },/* inactive */
E 13
	{ &vop_reclaim_desc, kernfs_reclaim },	/* reclaim */
D 13
	{ &vop_lock_desc, kernfs_lock },		/* lock */
E 13
I 13
	{ &vop_lock_desc, kernfs_lock },	/* lock */
E 13
	{ &vop_unlock_desc, kernfs_unlock },	/* unlock */
D 13
	{ &vop_bmap_desc, kernfs_bmap },		/* bmap */
	{ &vop_strategy_desc, kernfs_strategy },	/* strategy */
E 13
I 13
	{ &vop_bmap_desc, kernfs_bmap },	/* bmap */
	{ &vop_strategy_desc, kernfs_strategy },/* strategy */
E 13
	{ &vop_print_desc, kernfs_print },	/* print */
D 13
	{ &vop_islocked_desc, kernfs_islocked },	/* islocked */
E 13
I 13
	{ &vop_islocked_desc, kernfs_islocked },/* islocked */
	{ &vop_pathconf_desc, kernfs_pathconf },/* pathconf */
E 13
	{ &vop_advlock_desc, kernfs_advlock },	/* advlock */
D 13
	{ &vop_blkatoff_desc, kernfs_blkatoff },	/* blkatoff */
E 13
I 13
	{ &vop_blkatoff_desc, kernfs_blkatoff },/* blkatoff */
E 13
	{ &vop_valloc_desc, kernfs_valloc },	/* valloc */
	{ &vop_vfree_desc, kernfs_vfree },	/* vfree */
D 13
	{ &vop_truncate_desc, kernfs_truncate },	/* truncate */
E 13
I 13
	{ &vop_truncate_desc, kernfs_truncate },/* truncate */
E 13
	{ &vop_update_desc, kernfs_update },	/* update */
	{ &vop_bwrite_desc, kernfs_bwrite },	/* bwrite */
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
struct vnodeopv_desc kernfs_vnodeop_opv_desc =
	{ &kernfs_vnodeop_p, kernfs_vnodeop_entries };
E 1
