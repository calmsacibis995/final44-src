h44399
s 00052/00003/01133
d D 8.19 95/05/27 22:22:54 mckusick 19 18
c read-only checking must be done by the filesystem layers
e
s 00011/00058/01125
d D 8.18 95/05/14 00:35:19 mckusick 18 17
c convert to use lock manager
e
s 00043/00029/01140
d D 8.17 95/03/30 14:24:50 mckusick 17 16
c readdir now produces cookies; cd9660_enotsupp => eopnotsupp
e
s 00003/00000/01166
d D 8.16 95/02/27 15:36:12 mckusick 16 15
c vgone => VOP_REVOKE
e
s 00002/00000/01164
d D 8.15 94/12/05 22:27:51 mckusick 15 14
c cleanups
e
s 00136/00101/01028
d D 8.14 94/12/05 22:11:24 mckusick 14 13
c update from mycroft
e
s 00018/00019/01111
d D 8.13 94/11/07 15:54:48 mckusick 13 12
c use proper spec and fifo ops
e
s 00018/00008/01112
d D 8.12 94/08/19 12:44:05 mckusick 12 11
c streamline getting length of symbolic link
e
s 00023/00000/01097
d D 8.11 94/08/17 22:09:22 mckusick 11 10
c get lstat of symlinks to return the correct length
e
s 00009/00000/01088
d D 8.10 94/08/11 00:09:06 mckusick 10 9
c add vop_lease
e
s 00012/00015/01076
d D 8.9 94/07/24 22:40:02 mckusick 9 8
c more bugfixes from mycroft
e
s 00008/00003/01083
d D 8.8 94/07/13 18:55:05 mckusick 8 7
c update for 4.4BSD-Lite (from mycroft)
e
s 00054/00009/01032
d D 8.7 94/07/13 16:41:59 mckusick 7 6
c update for 4.4BSD-Lite (from mycroft)
e
s 00063/00031/00978
d D 8.6 94/06/14 12:27:35 mkm 6 5
c add code for access check; bug fix for readlink; formatting
c (from Wolfgang Solfrank via mycroft)
e
s 00017/00020/00992
d D 8.5 94/06/04 19:59:02 mckusick 5 4
c calculate and return cookies and eof flag
e
s 00002/00002/01010
d D 8.4 94/05/09 19:55:23 mckusick 4 3
c use temporary short for call to isofs_rrip_getname in getdirentries
e
s 00144/00139/00868
d D 8.3 94/01/23 23:50:50 mckusick 3 2
c isofs => cd9660 naming convention
e
s 00000/00002/01007
d D 8.2 94/01/22 20:32:29 hibler 2 1
c get rid of some left over debug stuff
e
s 01009/00000/00000
d D 8.1 94/01/21 18:29:00 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/resourcevar.h>
#include <sys/kernel.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/conf.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <miscfs/specfs/specdev.h>
#include <miscfs/fifofs/fifo.h>
#include <sys/malloc.h>
#include <sys/dir.h>

#include <isofs/cd9660/iso.h>
D 3
#include <isofs/cd9660/isofs_node.h>
E 3
I 3
#include <isofs/cd9660/cd9660_node.h>
E 3
#include <isofs/cd9660/iso_rrip.h>

#if 0
/*
 * Mknod vnode call
 *  Actually remap the device number
 */
D 3
isofs_mknod(ndp, vap, cred, p)
E 3
I 3
cd9660_mknod(ndp, vap, cred, p)
E 3
	struct nameidata *ndp;
	struct ucred *cred;
	struct vattr *vap;
	struct proc *p;
{
#ifndef	ISODEVMAP
	free(ndp->ni_pnbuf, M_NAMEI);
	vput(ndp->ni_dvp);
	vput(ndp->ni_vp);
D 6
	return EINVAL;
E 6
I 6
	return (EINVAL);
E 6
#else
	register struct vnode *vp;
	struct iso_node *ip;
	struct iso_dnode *dp;
	int error;
D 14
	
E 14
I 14

E 14
	vp = ndp->ni_vp;
	ip = VTOI(vp);
D 14
	
E 14
I 14

E 14
	if (ip->i_mnt->iso_ftype != ISO_FTYPE_RRIP
	    || vap->va_type != vp->v_type
	    || (vap->va_type != VCHR && vap->va_type != VBLK)) {
		free(ndp->ni_pnbuf, M_NAMEI);
		vput(ndp->ni_dvp);
		vput(ndp->ni_vp);
D 6
		return EINVAL;
E 6
I 6
		return (EINVAL);
E 6
	}
D 14
	
E 14
I 14

E 14
	dp = iso_dmap(ip->i_dev,ip->i_number,1);
	if (ip->inode.iso_rdev == vap->va_rdev || vap->va_rdev == VNOVAL) {
		/* same as the unmapped one, delete the mapping */
		remque(dp);
		FREE(dp,M_CACHE);
	} else
		/* enter new mapping */
		dp->d_dev = vap->va_rdev;
D 14
	
E 14
I 14

E 14
	/*
	 * Remove inode so that it will be reloaded by iget and
	 * checked to see if it is an alias of an existing entry
	 * in the inode cache.
	 */
	vput(vp);
	vp->v_type = VNON;
	vgone(vp);
	return (0);
#endif
}
#endif

/*
I 19
 * Setattr call. Only allowed for block and character special devices.
 */
int
cd9660_setattr(ap)
	struct vop_setattr_args /* {
		struct vnodeop_desc *a_desc;
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	struct vattr *vap = ap->a_vap;

  	if (vap->va_flags != VNOVAL || vap->va_uid != (uid_t)VNOVAL ||
	    vap->va_gid != (gid_t)VNOVAL || vap->va_atime.ts_sec != VNOVAL ||
	    vap->va_mtime.ts_sec != VNOVAL || vap->va_mode != (mode_t)VNOVAL)
		return (EROFS);
	if (vap->va_size != VNOVAL) {
 		switch (vp->v_type) {
 		case VDIR:
 			return (EISDIR);
		case VLNK:
		case VREG:
			return (EROFS);
 		case VCHR:
 		case VBLK:
 		case VSOCK:
 		case VFIFO:
			return (0);
		}
	}
}

/*
E 19
 * Open called.
 *
 * Nothing to do.
 */
/* ARGSUSED */
int
D 3
isofs_open(ap)
E 3
I 3
cd9660_open(ap)
E 3
	struct vop_open_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	return (0);
}

/*
 * Close called
 *
 * Update the times on the inode on writeable file systems.
 */
/* ARGSUSED */
int
D 3
isofs_close(ap)
E 3
I 3
cd9660_close(ap)
E 3
	struct vop_close_args /* {
		struct vnode *a_vp;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	return (0);
}

/*
 * Check mode permission on inode pointer. Mode is READ, WRITE or EXEC.
 * The mode is shifted to select the owner/group/other fields. The
 * super user is granted all permissions.
 */
/* ARGSUSED */
D 3
isofs_access(ap)
E 3
I 3
cd9660_access(ap)
E 3
	struct vop_access_args /* {
		struct vnode *a_vp;
		int  a_mode;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
D 6
	return (0);
E 6
I 6
D 19
	struct iso_node *ip = VTOI(ap->a_vp);
E 19
I 19
	struct vnode *vp = ap->a_vp;
	struct iso_node *ip = VTOI(vp);
E 19
	struct ucred *cred = ap->a_cred;
	mode_t mask, mode = ap->a_mode;
	gid_t *gp;
D 14
	int i, error;
E 14
I 14
	int i;
E 14

I 19
	/*
	 * Disallow write attempts unless the file is a socket,
	 * fifo, or a block or character device resident on the
	 * file system.
	 */
	if (mode & VWRITE) {
		switch (vp->v_type) {
		case VDIR:
		case VLNK:
		case VREG:
			return (EROFS);
		}
	}

E 19
	/* User id 0 always gets access. */
	if (cred->cr_uid == 0)
		return (0);

	mask = 0;

	/* Otherwise, check the owner. */
	if (cred->cr_uid == ip->inode.iso_uid) {
		if (mode & VEXEC)
			mask |= S_IXUSR;
		if (mode & VREAD)
			mask |= S_IRUSR;
		if (mode & VWRITE)
			mask |= S_IWUSR;
		return ((ip->inode.iso_mode & mask) == mask ? 0 : EACCES);
	}

	/* Otherwise, check the groups. */
	for (i = 0, gp = cred->cr_groups; i < cred->cr_ngroups; i++, gp++)
		if (ip->inode.iso_gid == *gp) {
			if (mode & VEXEC)
				mask |= S_IXGRP;
			if (mode & VREAD)
				mask |= S_IRGRP;
			if (mode & VWRITE)
				mask |= S_IWGRP;
			return ((ip->inode.iso_mode & mask) == mask ?
			    0 : EACCES);
		}

	/* Otherwise, check everyone else. */
	if (mode & VEXEC)
		mask |= S_IXOTH;
	if (mode & VREAD)
		mask |= S_IROTH;
	if (mode & VWRITE)
		mask |= S_IWOTH;
	return ((ip->inode.iso_mode & mask) == mask ? 0 : EACCES);
E 6
}

D 3
isofs_getattr(ap)
E 3
I 3
cd9660_getattr(ap)
E 3
	struct vop_getattr_args /* {
		struct vnode *a_vp;
		struct vattr *a_vap;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;

{
	struct vnode *vp = ap->a_vp;
	register struct vattr *vap = ap->a_vap;
	register struct iso_node *ip = VTOI(vp);
	int i;

	vap->va_fsid	= ip->i_dev;
	vap->va_fileid	= ip->i_number;

	vap->va_mode	= ip->inode.iso_mode;
	vap->va_nlink	= ip->inode.iso_links;
	vap->va_uid	= ip->inode.iso_uid;
	vap->va_gid	= ip->inode.iso_gid;
	vap->va_atime	= ip->inode.iso_atime;
	vap->va_mtime	= ip->inode.iso_mtime;
	vap->va_ctime	= ip->inode.iso_ctime;
	vap->va_rdev	= ip->inode.iso_rdev;

	vap->va_size	= (u_quad_t) ip->i_size;
I 11
	if (ip->i_size == 0 && (vap->va_mode & S_IFMT) == S_IFLNK) {
		struct vop_readlink_args rdlnk;
		struct iovec aiov;
		struct uio auio;
		char *cp;

		MALLOC(cp, char *, MAXPATHLEN, M_TEMP, M_WAITOK);
		aiov.iov_base = cp;
		aiov.iov_len = MAXPATHLEN;
		auio.uio_iov = &aiov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = 0;
		auio.uio_rw = UIO_READ;
		auio.uio_segflg = UIO_SYSSPACE;
		auio.uio_procp = ap->a_p;
		auio.uio_resid = MAXPATHLEN;
		rdlnk.a_uio = &auio;
		rdlnk.a_vp = ap->a_vp;
		rdlnk.a_cred = ap->a_cred;
		if (cd9660_readlink(&rdlnk) == 0)
			vap->va_size = MAXPATHLEN - auio.uio_resid;
		FREE(cp, M_TEMP);
	}
E 11
	vap->va_flags	= 0;
	vap->va_gen = 1;
	vap->va_blocksize = ip->i_mnt->logical_block_size;
	vap->va_bytes	= (u_quad_t) ip->i_size;
	vap->va_type	= vp->v_type;
	return (0);
}

#if ISO_DEFAULT_BLOCK_SIZE >= NBPG
#ifdef DEBUG
extern int doclusterread;
#else
#define doclusterread 1
#endif
#else
/* XXX until cluster routines can handle block sizes less than one page */
#define doclusterread 0
#endif

/*
 * Vnode op for reading.
 */
D 3
isofs_read(ap)
E 3
I 3
cd9660_read(ap)
E 3
	struct vop_read_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
	register struct uio *uio = ap->a_uio;
	register struct iso_node *ip = VTOI(vp);
	register struct iso_mnt *imp;
	struct buf *bp;
	daddr_t lbn, bn, rablock;
	off_t diff;
	int rasize, error = 0;
	long size, n, on;
D 14
	
E 14
I 14

E 14
	if (uio->uio_resid == 0)
		return (0);
	if (uio->uio_offset < 0)
		return (EINVAL);
D 7
	ip->i_flag |= IACC;
E 7
I 7
	ip->i_flag |= IN_ACCESS;
E 7
	imp = ip->i_mnt;
	do {
D 14
		lbn = iso_lblkno(imp, uio->uio_offset);
		on = iso_blkoff(imp, uio->uio_offset);
		n = min((unsigned)(imp->logical_block_size - on),
E 14
I 14
		lbn = lblkno(imp, uio->uio_offset);
		on = blkoff(imp, uio->uio_offset);
		n = min((u_int)(imp->logical_block_size - on),
E 14
			uio->uio_resid);
		diff = (off_t)ip->i_size - uio->uio_offset;
		if (diff <= 0)
			return (0);
		if (diff < n)
			n = diff;
D 14
		size = iso_blksize(imp, ip, lbn);
E 14
I 14
		size = blksize(imp, ip, lbn);
E 14
		rablock = lbn + 1;
D 2
#if 1
E 2
		if (doclusterread) {
D 14
			if (iso_lblktosize(imp, rablock) <= ip->i_size)
E 14
I 14
			if (lblktosize(imp, rablock) <= ip->i_size)
E 14
				error = cluster_read(vp, (off_t)ip->i_size,
						     lbn, size, NOCRED, &bp);
D 14
			else 
E 14
I 14
			else
E 14
				error = bread(vp, lbn, size, NOCRED, &bp);
		} else {
			if (vp->v_lastr + 1 == lbn &&
D 14
			    iso_lblktosize(imp, rablock) < ip->i_size) {
				rasize = iso_blksize(imp, ip, rablock);
E 14
I 14
			    lblktosize(imp, rablock) < ip->i_size) {
				rasize = blksize(imp, ip, rablock);
E 14
				error = breadn(vp, lbn, size, &rablock,
					       &rasize, 1, NOCRED, &bp);
			} else
				error = bread(vp, lbn, size, NOCRED, &bp);
		}
D 2
#endif
E 2
		vp->v_lastr = lbn;
		n = min(n, size - bp->b_resid);
		if (error) {
			brelse(bp);
			return (error);
		}

D 14
		error = uiomove(bp->b_un.b_addr + on, (int)n, uio);
E 14
I 14
		error = uiomove(bp->b_data + on, (int)n, uio);
E 14
		if (n + on == imp->logical_block_size ||
		    uio->uio_offset == (off_t)ip->i_size)
			bp->b_flags |= B_AGE;
		brelse(bp);
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
	return (error);
}

/* ARGSUSED */
int
D 3
isofs_ioctl(ap)
E 3
I 3
cd9660_ioctl(ap)
E 3
	struct vop_ioctl_args /* {
		struct vnode *a_vp;
D 14
		int  a_command;
E 14
I 14
		u_long a_command;
E 14
		caddr_t  a_data;
		int  a_fflag;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{
	printf("You did ioctl for isofs !!\n");
	return (ENOTTY);
}

/* ARGSUSED */
int
D 3
isofs_select(ap)
E 3
I 3
cd9660_select(ap)
E 3
	struct vop_select_args /* {
		struct vnode *a_vp;
		int  a_which;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{

	/*
	 * We should really check to see if I/O is possible.
	 */
	return (1);
}

/*
 * Mmap a file
 *
 * NB Currently unsupported.
 */
/* ARGSUSED */
int
D 3
isofs_mmap(ap)
E 3
I 3
cd9660_mmap(ap)
E 3
	struct vop_mmap_args /* {
		struct vnode *a_vp;
		int  a_fflags;
		struct ucred *a_cred;
		struct proc *a_p;
	} */ *ap;
{

	return (EINVAL);
}

/*
 * Seek on a file
 *
 * Nothing to do, so just return.
 */
/* ARGSUSED */
int
D 3
isofs_seek(ap)
E 3
I 3
cd9660_seek(ap)
E 3
	struct vop_seek_args /* {
		struct vnode *a_vp;
		off_t  a_oldoff;
		off_t  a_newoff;
		struct ucred *a_cred;
	} */ *ap;
{

	return (0);
}

/*
 * Structure for reading directories
 */
struct isoreaddir {
	struct dirent saveent;
	struct dirent assocent;
	struct dirent current;
	off_t saveoff;
	off_t assocoff;
	off_t curroff;
	struct uio *uio;
	off_t uio_off;
D 5
	u_int *cookiep;
E 5
I 5
	int eofflag;
	u_long *cookies;
E 5
	int ncookies;
D 5
	int eof;
E 5
};

D 14
static int
E 14
I 14
int
E 14
iso_uiodir(idp,dp,off)
	struct isoreaddir *idp;
	struct dirent *dp;
	off_t off;
{
	int error;
D 14
	
E 14
I 14

E 14
	dp->d_name[dp->d_namlen] = 0;
	dp->d_reclen = DIRSIZ(dp);
D 14
	
E 14
I 14

E 14
	if (idp->uio->uio_resid < dp->d_reclen) {
D 5
		idp->eof = 0;
		return -1;
E 5
I 5
		idp->eofflag = 0;
		return (-1);
E 5
	}
D 14
	
E 14
I 14

E 14
D 5
	if (idp->cookiep) {
E 5
I 5
	if (idp->cookies) {
E 5
		if (idp->ncookies <= 0) {
D 5
			idp->eof = 0;
			return -1;
E 5
I 5
			idp->eofflag = 0;
			return (-1);
E 5
		}
D 14
		
E 14
I 14

E 14
D 5
		*idp->cookiep++ = off;
E 5
I 5
		*idp->cookies++ = off;
E 5
		--idp->ncookies;
	}
D 14
	
E 14
I 14

E 14
	if (error = uiomove(dp,dp->d_reclen,idp->uio))
D 5
		return error;
E 5
I 5
		return (error);
E 5
	idp->uio_off = off;
D 5
	return 0;
E 5
I 5
	return (0);
E 5
}

D 14
static int
E 14
I 14
int
E 14
iso_shipdir(idp)
	struct isoreaddir *idp;
{
	struct dirent *dp;
	int cl, sl, assoc;
	int error;
	char *cname, *sname;
D 14
	
E 14
I 14

E 14
	cl = idp->current.d_namlen;
	cname = idp->current.d_name;
	if (assoc = cl > 1 && *cname == ASSOCCHAR) {
		cl--;
		cname++;
	}
D 14
	
E 14
I 14

E 14
	dp = &idp->saveent;
	sname = dp->d_name;
	if (!(sl = dp->d_namlen)) {
		dp = &idp->assocent;
		sname = dp->d_name + 1;
		sl = dp->d_namlen - 1;
	}
	if (sl > 0) {
		if (sl != cl
		    || bcmp(sname,cname,sl)) {
			if (idp->assocent.d_namlen) {
				if (error = iso_uiodir(idp,&idp->assocent,idp->assocoff))
D 6
					return error;
E 6
I 6
					return (error);
E 6
				idp->assocent.d_namlen = 0;
			}
			if (idp->saveent.d_namlen) {
				if (error = iso_uiodir(idp,&idp->saveent,idp->saveoff))
D 6
					return error;
E 6
I 6
					return (error);
E 6
				idp->saveent.d_namlen = 0;
			}
		}
	}
	idp->current.d_reclen = DIRSIZ(&idp->current);
	if (assoc) {
		idp->assocoff = idp->curroff;
		bcopy(&idp->current,&idp->assocent,idp->current.d_reclen);
	} else {
		idp->saveoff = idp->curroff;
		bcopy(&idp->current,&idp->saveent,idp->current.d_reclen);
	}
D 6
	return 0;
E 6
I 6
	return (0);
E 6
}

/*
 * Vnode op for readdir
D 6
 * XXX make sure everything still works now that eofflagp and cookiep
E 6
I 6
D 7
 * XXX make sure everything still works now that eofflagp and cookies
E 6
 * are no longer args.
E 7
 */
int
D 3
isofs_readdir(ap)
E 3
I 3
cd9660_readdir(ap)
E 3
	struct vop_readdir_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
I 5
		int *a_eofflag;
I 17
		int *a_ncookies;
E 17
		u_long *a_cookies;
D 17
		int a_ncookies;
E 17
E 5
	} */ *ap;
{
	register struct uio *uio = ap->a_uio;
	struct isoreaddir *idp;
I 14
	struct vnode *vdp = ap->a_vp;
	struct iso_node *dp;
	struct iso_mnt *imp;
	struct buf *bp = NULL;
	struct iso_directory_record *ep;
E 14
	int entryoffsetinblock;
I 14
	doff_t endsearch;
	u_long bmask;
E 14
	int error = 0;
D 14
	int endsearch;
	struct iso_directory_record *ep;
	u_short elen;
E 14
	int reclen;
D 14
	struct iso_mnt *imp;
	struct iso_node *ip;
	struct buf *bp = NULL;
	
	ip = VTOI(ap->a_vp);
	imp = ip->i_mnt;
	
E 14
I 14
	u_short namelen;
I 17
	int ncookies = 0;
	u_long *cookies = NULL;
E 17

	dp = VTOI(vdp);
	imp = dp->i_mnt;
	bmask = imp->im_bmask;

E 14
D 8
	MALLOC(idp,struct isoreaddir *,sizeof(*idp),M_TEMP,M_WAITOK);
	idp->saveent.d_namlen = 0;
	idp->assocent.d_namlen = 0;
E 8
I 8
	MALLOC(idp, struct isoreaddir *, sizeof(*idp), M_TEMP, M_WAITOK);
	idp->saveent.d_namlen = idp->assocent.d_namlen = 0;
	/*
	 * XXX
	 * Is it worth trying to figure out the type?
	 */
	idp->saveent.d_type = idp->assocent.d_type = idp->current.d_type =
	    DT_UNKNOWN;
E 8
	idp->uio = uio;
I 17
	if (ap->a_ncookies == NULL) {
		idp->cookies = NULL;
	} else {
		/*
		 * Guess the number of cookies needed.
		 */
		ncookies = uio->uio_resid / 16;
		MALLOC(cookies, u_int *, ncookies * sizeof(u_int), M_TEMP,
		    M_WAITOK);
		idp->cookies = cookies;
		idp->ncookies = ncookies;
	}
E 17
D 5
#if 0
	idp->cookiep = cookies;
	idp->ncookies = ncookies;
	idp->eof = 1;
#else
	idp->cookiep = 0;
#endif
E 5
I 5
	idp->eofflag = 1;
D 17
	idp->cookies = ap->a_cookies;
	idp->ncookies = ap->a_ncookies;
E 17
E 5
	idp->curroff = uio->uio_offset;
D 14
	
	entryoffsetinblock = iso_blkoff(imp, idp->curroff);
	if (entryoffsetinblock != 0) {
		if (error = iso_blkatoff(ip, idp->curroff, &bp)) {
			FREE(idp,M_TEMP);
			return (error);
		}
E 14
I 14

	if ((entryoffsetinblock = idp->curroff & bmask) &&
	    (error = VOP_BLKATOFF(vdp, (off_t)idp->curroff, NULL, &bp))) {
		FREE(idp, M_TEMP);
		return (error);
E 14
	}
D 14
	
D 9
	endsearch = ip->i_size;
E 9
I 9
	endsearch = roundup(ip->i_size, imp->logical_block_size);
E 9
	
E 14
I 14
	endsearch = dp->i_size;

E 14
	while (idp->curroff < endsearch) {
		/*
		 * If offset is on a block boundary,
		 * read the next directory block.
		 * Release previous if it exists.
		 */
D 14
		
		if (iso_blkoff(imp, idp->curroff) == 0) {
E 14
I 14
		if ((idp->curroff & bmask) == 0) {
E 14
			if (bp != NULL)
				brelse(bp);
D 14
			if (error = iso_blkatoff(ip, idp->curroff, &bp))
E 14
I 14
			if (error =
			    VOP_BLKATOFF(vdp, (off_t)idp->curroff, NULL, &bp))
E 14
				break;
			entryoffsetinblock = 0;
		}
		/*
		 * Get pointer to next entry.
		 */
D 14
		
E 14
		ep = (struct iso_directory_record *)
D 14
			(bp->b_un.b_addr + entryoffsetinblock);
		
		reclen = isonum_711 (ep->length);
E 14
I 14
			((char *)bp->b_data + entryoffsetinblock);

		reclen = isonum_711(ep->length);
E 14
		if (reclen == 0) {
			/* skip to next block, if any */
D 9
			idp->curroff = roundup (idp->curroff,
						imp->logical_block_size);
E 9
I 9
			idp->curroff =
D 14
				roundup(idp->curroff, imp->logical_block_size);
E 14
I 14
			    (idp->curroff & ~bmask) + imp->logical_block_size;
E 14
E 9
			continue;
		}
D 14
		
E 14
I 14

E 14
		if (reclen < ISO_DIRECTORY_RECORD_SIZE) {
			error = EINVAL;
			/* illegal entry, stop */
			break;
		}
D 14
		
E 14
I 14

E 14
		if (entryoffsetinblock + reclen > imp->logical_block_size) {
			error = EINVAL;
			/* illegal directory, so stop looking */
			break;
		}
D 14
		
E 14
I 14

E 14
D 9
		idp->current.d_namlen = isonum_711 (ep->name_len);
		if (isonum_711(ep->flags)&2)
			isodirino(&idp->current.d_fileno,ep,imp);
		else
			idp->current.d_fileno = dbtob(bp->b_blkno) +
				idp->curroff;
		
E 9
I 9
		idp->current.d_namlen = isonum_711(ep->name_len);

E 9
		if (reclen < ISO_DIRECTORY_RECORD_SIZE + idp->current.d_namlen) {
			error = EINVAL;
			/* illegal entry, stop */
			break;
		}
D 14
		
E 14
I 14

E 14
I 9
		if (isonum_711(ep->flags)&2)
D 14
			isodirino(&idp->current.d_fileno,ep,imp);
E 14
I 14
			idp->current.d_fileno = isodirino(ep, imp);
E 14
		else
			idp->current.d_fileno = dbtob(bp->b_blkno) +
				entryoffsetinblock;
D 14
		
E 14
I 14

E 14
E 9
		idp->curroff += reclen;
D 9
		/*
		 *
		 */
E 9
I 9

E 9
		switch (imp->iso_ftype) {
		case ISO_FTYPE_RRIP:
D 3
			isofs_rrip_getname(ep,idp->current.d_name,
E 3
I 3
D 4
			cd9660_rrip_getname(ep,idp->current.d_name,
E 3
					   (u_short *)&idp->current.d_namlen,
E 4
I 4
D 14
			cd9660_rrip_getname(ep,idp->current.d_name, &elen,
E 14
I 14
			cd9660_rrip_getname(ep,idp->current.d_name, &namelen,
E 14
E 4
					   &idp->current.d_fileno,imp);
I 4
D 14
			idp->current.d_namlen = (u_char)elen;
E 14
I 14
			idp->current.d_namlen = (u_char)namelen;
E 14
E 4
			if (idp->current.d_namlen)
				error = iso_uiodir(idp,&idp->current,idp->curroff);
			break;
		default:	/* ISO_FTYPE_DEFAULT || ISO_FTYPE_9660 */
			strcpy(idp->current.d_name,"..");
			switch (ep->name[0]) {
			case 0:
				idp->current.d_namlen = 1;
				error = iso_uiodir(idp,&idp->current,idp->curroff);
				break;
			case 1:
				idp->current.d_namlen = 2;
				error = iso_uiodir(idp,&idp->current,idp->curroff);
				break;
			default:
				isofntrans(ep->name,idp->current.d_namlen,
D 14
					   idp->current.d_name, &elen,
E 14
I 14
					   idp->current.d_name, &namelen,
E 14
					   imp->iso_ftype == ISO_FTYPE_9660,
					   isonum_711(ep->flags)&4);
D 14
				idp->current.d_namlen = (u_char)elen;
E 14
I 14
				idp->current.d_namlen = (u_char)namelen;
E 14
				if (imp->iso_ftype == ISO_FTYPE_DEFAULT)
					error = iso_shipdir(idp);
				else
					error = iso_uiodir(idp,&idp->current,idp->curroff);
				break;
			}
		}
		if (error)
			break;
D 14
		
E 14
I 14

E 14
		entryoffsetinblock += reclen;
	}
D 14
	
E 14
I 14

E 14
	if (!error && imp->iso_ftype == ISO_FTYPE_DEFAULT) {
		idp->current.d_namlen = 0;
		error = iso_shipdir(idp);
	}
	if (error < 0)
		error = 0;
D 14
	
E 14
I 14

I 17
	if (ap->a_ncookies != NULL) {
		if (error)
			free(cookies, M_TEMP);
		else {
			/*
			 * Work out the number of cookies actually used.
			 */
			*ap->a_ncookies = ncookies - idp->ncookies;
			*ap->a_cookies = cookies;
		}
	}

E 17
E 14
	if (bp)
		brelse (bp);
I 14

E 14
D 9

E 9
	uio->uio_offset = idp->uio_off;
D 5
#if 0
	*eofflagp = idp->eof;
#endif
E 5
I 5
	*ap->a_eofflag = idp->eofflag;
E 5
D 14
	
	FREE(idp,M_TEMP);
	
E 14
I 14

	FREE(idp, M_TEMP);

E 14
	return (error);
}
I 14

E 14
D 9

E 9
/*
 * Return target name of a symbolic link
 * Shouldn't we get the parent vnode and read the data from there?
D 3
 * This could eventually result in deadlocks in isofs_lookup.
E 3
I 3
 * This could eventually result in deadlocks in cd9660_lookup.
E 3
 * But otherwise the block read here is in the block buffer two times.
 */
typedef struct iso_directory_record ISODIR;
typedef struct iso_node             ISONODE;
typedef struct iso_mnt              ISOMNT;
int
D 3
isofs_readlink(ap)
E 3
I 3
cd9660_readlink(ap)
E 3
	struct vop_readlink_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		struct ucred *a_cred;
	} */ *ap;
{
	ISONODE	*ip;
D 14
	ISODIR	*dirp;                   
E 14
I 14
	ISODIR	*dirp;
E 14
	ISOMNT	*imp;
	struct	buf *bp;
I 15
	struct	uio *uio;
E 15
I 12
D 14
	struct	uio *uio;
E 14
E 12
	u_short	symlen;
	int	error;
	char	*symname;
	ino_t	ino;
D 14
	
E 14
I 14

E 14
	ip  = VTOI(ap->a_vp);
	imp = ip->i_mnt;
I 15
	uio = ap->a_uio;
E 15
I 12
D 14
	uio = ap->a_uio;
E 12
	
E 14
I 14

E 14
	if (imp->iso_ftype != ISO_FTYPE_RRIP)
D 6
		return EINVAL;
E 6
I 6
		return (EINVAL);
E 6
D 14
	
E 14
I 14

E 14
	/*
	 * Get parents directory record block that this inode included.
	 */
	error = bread(imp->im_devvp,
D 6
		      (daddr_t)(ip->i_number / DEV_BSIZE),
E 6
I 6
D 14
		      (daddr_t)((ip->i_number&~imp->im_bmask) / DEV_BSIZE),
E 6
		      imp->logical_block_size,
		      NOCRED,
		      &bp);
E 14
I 14
		      (ip->i_number >> imp->im_bshift) <<
		      (imp->im_bshift - DEV_BSHIFT),
		      imp->logical_block_size, NOCRED, &bp);
E 14
	if (error) {
		brelse(bp);
D 6
		return EINVAL;
E 6
I 6
		return (EINVAL);
E 6
	}

	/*
	 * Setup the directory pointer for this inode
	 */
D 14
	dirp = (ISODIR *)(bp->b_un.b_addr + (ip->i_number & imp->im_bmask));
E 14
I 14
	dirp = (ISODIR *)(bp->b_data + (ip->i_number & imp->im_bmask));
E 14
D 6
#ifdef DEBUG
	printf("lbn=%d,off=%d,bsize=%d,DEV_BSIZE=%d, dirp= %08x, b_addr=%08x, offset=%08x(%08x)\n",
	       (daddr_t)(ip->i_number >> imp->im_bshift),
	       ip->i_number & imp->im_bmask,
	       imp->logical_block_size,
	       DEV_BSIZE,
	       dirp,
	       bp->b_un.b_addr,
	       ip->i_number,
	       ip->i_number & imp->im_bmask );
#endif
	
E 6
I 6

E 6
	/*
	 * Just make sure, we have a right one....
	 *   1: Check not cross boundary on block
	 */
	if ((ip->i_number & imp->im_bmask) + isonum_711(dirp->length)
	    > imp->logical_block_size) {
		brelse(bp);
D 6
		return EINVAL;
E 6
I 6
		return (EINVAL);
E 6
	}
D 14
	
E 14
I 14

E 14
	/*
	 * Now get a buffer
	 * Abuse a namei buffer for now.
	 */
D 12
	MALLOC(symname,char *,MAXPATHLEN,M_NAMEI,M_WAITOK);
E 12
I 12
	if (uio->uio_segflg == UIO_SYSSPACE)
		symname = uio->uio_iov->iov_base;
	else
		MALLOC(symname, char *, MAXPATHLEN, M_NAMEI, M_WAITOK);
E 12
	
	/*
	 * Ok, we just gathering a symbolic name in SL record.
	 */
D 3
	if (isofs_rrip_getsymname(dirp,symname,&symlen,imp) == 0) {
E 3
I 3
D 12
	if (cd9660_rrip_getsymname(dirp,symname,&symlen,imp) == 0) {
E 3
		FREE(symname,M_NAMEI);
E 12
I 12
	if (cd9660_rrip_getsymname(dirp, symname, &symlen, imp) == 0) {
		if (uio->uio_segflg != UIO_SYSSPACE)
			FREE(symname, M_NAMEI);
E 12
		brelse(bp);
D 6
		return EINVAL;
E 6
I 6
		return (EINVAL);
E 6
	}
	/*
	 * Don't forget before you leave from home ;-)
	 */
	brelse(bp);
	
	/*
	 * return with the symbolic name to caller's.
	 */
D 12
	error = uiomove(symname,symlen,ap->a_uio);
	
	FREE(symname,M_NAMEI);
	
D 6
	return error;
E 6
I 6
	return (error);
E 12
I 12
	if (uio->uio_segflg != UIO_SYSSPACE) {
		error = uiomove(symname, symlen, uio);
		FREE(symname, M_NAMEI);
		return (error);
	}
	uio->uio_resid -= symlen;
	uio->uio_iov->iov_base += symlen;
	uio->uio_iov->iov_len -= symlen;
	return (0);
E 12
E 6
}

/*
 * Ufs abort op, called after namei() when a CREATE/DELETE isn't actually
 * done. If a buffer has been saved in anticipation of a CREATE, delete it.
 */
int
D 3
isofs_abortop(ap)
E 3
I 3
cd9660_abortop(ap)
E 3
	struct vop_abortop_args /* {
		struct vnode *a_dvp;
		struct componentname *a_cnp;
	} */ *ap;
{
	if ((ap->a_cnp->cn_flags & (HASBUF | SAVESTART)) == HASBUF)
		FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
D 6
	return 0;
E 6
I 6
	return (0);
E 6
}

/*
 * Lock an inode.
 */
int
D 3
isofs_lock(ap)
E 3
I 3
cd9660_lock(ap)
E 3
	struct vop_lock_args /* {
		struct vnode *a_vp;
I 18
		int a_flags;
		struct proc *a_p;
E 18
	} */ *ap;
{
D 7
	register struct iso_node *ip = VTOI(ap->a_vp);
E 7
I 7
D 18
	register struct vnode *vp = ap->a_vp;
	register struct iso_node *ip;
	struct proc *p = curproc;	/* XXX */
E 18
I 18
	struct vnode *vp = ap->a_vp;
E 18
E 7

D 7
	ISO_ILOCK(ip);
E 7
I 7
D 18
start:
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
		sleep((caddr_t)vp, PINOD);
	}
	if (vp->v_tag == VT_NON)
		return (ENOENT);
	ip = VTOI(vp);
	if (ip->i_flag & IN_LOCKED) {
		ip->i_flag |= IN_WANTED;
#ifdef DIAGNOSTIC
		if (p) {
			if (p->p_pid == ip->i_lockholder)
				panic("locking against myself");
			ip->i_lockwaiter = p->p_pid;
		} else
			ip->i_lockwaiter = -1;
#endif
		(void) sleep((caddr_t)ip, PINOD);
	}
#ifdef DIAGNOSTIC
	ip->i_lockwaiter = 0;
	if (ip->i_lockholder != 0)
		panic("lockholder (%d) != 0", ip->i_lockholder);
	if (p && p->p_pid == 0)
		printf("locking by process 0\n");
	if (p)
		ip->i_lockholder = p->p_pid;
	else
		ip->i_lockholder = -1;
#endif
	ip->i_flag |= IN_LOCKED;
E 7
D 6
	return 0;
E 6
I 6
	return (0);
E 18
I 18
	return (lockmgr(&VTOI(vp)->i_lock, ap->a_flags, &vp->v_interlock,
		ap->a_p));
E 18
E 6
}

/*
 * Unlock an inode.
 */
int
D 3
isofs_unlock(ap)
E 3
I 3
cd9660_unlock(ap)
E 3
	struct vop_unlock_args /* {
		struct vnode *a_vp;
I 18
		int a_flags;
		struct proc *a_p;
E 18
	} */ *ap;
{
D 18
	register struct iso_node *ip = VTOI(ap->a_vp);
I 7
	struct proc *p = curproc;	/* XXX */
E 18
I 18
	struct vnode *vp = ap->a_vp;
E 18
E 7

D 7
	if (!(ip->i_flag & ILOCKED))
D 3
		panic("isofs_unlock NOT LOCKED");
E 3
I 3
		panic("cd9660_unlock NOT LOCKED");
E 3
	ISO_IUNLOCK(ip);
E 7
I 7
D 18
#ifdef DIAGNOSTIC
	if ((ip->i_flag & IN_LOCKED) == 0) {
		vprint("ufs_unlock: unlocked inode", ap->a_vp);
		panic("ufs_unlock NOT LOCKED");
	}
	if (p && p->p_pid != ip->i_lockholder && p->p_pid > -1 &&
	    ip->i_lockholder > -1/* && lockcount++ < 100*/)
		panic("unlocker (%d) != lock holder (%d)",
		    p->p_pid, ip->i_lockholder);
	ip->i_lockholder = 0;
#endif
	ip->i_flag &= ~IN_LOCKED;
	if (ip->i_flag & IN_WANTED) {
		ip->i_flag &= ~IN_WANTED;
		wakeup((caddr_t)ip);
	}
E 7
D 6
	return 0;
E 6
I 6
	return (0);
E 18
I 18
	return (lockmgr(&VTOI(vp)->i_lock, ap->a_flags | LK_RELEASE,
		&vp->v_interlock, ap->a_p));
E 18
E 6
}

/*
D 14
 * Check for a locked inode.
 */
int
D 3
isofs_islocked(ap)
E 3
I 3
cd9660_islocked(ap)
E 3
	struct vop_islocked_args /* {
		struct vnode *a_vp;
	} */ *ap;
{

D 7
	if (VTOI(ap->a_vp)->i_flag & ILOCKED)
E 7
I 7
	if (VTOI(ap->a_vp)->i_flag & IN_LOCKED)
E 7
D 6
		return 1;
	return 0;
E 6
I 6
		return (1);
	return (0);
E 6
}

/*
E 14
 * Calculate the logical to physical mapping if not done already,
 * then call the device strategy routine.
 */
int
D 3
isofs_strategy(ap)
E 3
I 3
cd9660_strategy(ap)
E 3
	struct vop_strategy_args /* {
		struct buf *a_bp;
	} */ *ap;
{
	register struct buf *bp = ap->a_bp;
	register struct vnode *vp = bp->b_vp;
	register struct iso_node *ip;
	int error;

	ip = VTOI(vp);
	if (vp->v_type == VBLK || vp->v_type == VCHR)
D 3
		panic("isofs_strategy: spec");
E 3
I 3
		panic("cd9660_strategy: spec");
E 3
	if (bp->b_blkno == bp->b_lblkno) {
		if (error =
		    VOP_BMAP(vp, bp->b_lblkno, NULL, &bp->b_blkno, NULL)) {
			bp->b_error = error;
			bp->b_flags |= B_ERROR;
			biodone(bp);
			return (error);
		}
		if ((long)bp->b_blkno == -1)
			clrbuf(bp);
	}
	if ((long)bp->b_blkno == -1) {
		biodone(bp);
		return (0);
	}
	vp = ip->i_devvp;
	bp->b_dev = vp->v_rdev;
	VOCALL (vp->v_op, VOFFSET(vop_strategy), ap);
	return (0);
}

/*
 * Print out the contents of an inode.
 */
int
D 3
isofs_print(ap)
E 3
I 3
cd9660_print(ap)
E 3
	struct vop_print_args /* {
		struct vnode *a_vp;
	} */ *ap;
{
I 14

E 14
	printf("tag VT_ISOFS, isofs vnode\n");
D 6
	return 0;
E 6
I 6
	return (0);
E 6
}

/*
I 14
 * Check for a locked inode.
 */
int
cd9660_islocked(ap)
	struct vop_islocked_args /* {
		struct vnode *a_vp;
	} */ *ap;
{

D 18
	if (VTOI(ap->a_vp)->i_flag & IN_LOCKED)
		return (1);
	return (0);
E 18
I 18
	return (lockstatus(&VTOI(ap->a_vp)->i_lock));
E 18
}

/*
 * Return POSIX pathconf information applicable to cd9660 filesystems.
 */
int
cd9660_pathconf(ap)
	struct vop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		register_t *a_retval;
	} */ *ap;
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = 1;
		return (0);
	case _PC_NAME_MAX:
		if (VTOI(ap->a_vp)->i_mnt->iso_ftype == ISO_FTYPE_RRIP)
			*ap->a_retval = NAME_MAX;
		else
			*ap->a_retval = 37;
		return (0);
	case _PC_PATH_MAX:
		*ap->a_retval = PATH_MAX;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 1;
		return (0);
	case _PC_NO_TRUNC:
		*ap->a_retval = 1;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}

/*
E 14
D 17
 * Unsupported operation
 */
int
D 3
isofs_enotsupp()
E 3
I 3
cd9660_enotsupp()
E 3
{

	return (EOPNOTSUPP);
}

/*
E 17
 * Global vfs data structures for isofs
 */
D 3
#define isofs_create ((int (*) __P((struct  vop_create_args *)))isofs_enotsupp)
#define isofs_mknod ((int (*) __P((struct  vop_mknod_args *)))isofs_enotsupp)
#define isofs_setattr \
	((int (*) __P((struct  vop_setattr_args *)))isofs_enotsupp)
#define isofs_write ((int (*) __P((struct  vop_write_args *)))isofs_enotsupp)
#define isofs_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define isofs_remove ((int (*) __P((struct  vop_remove_args *)))isofs_enotsupp)
#define isofs_link ((int (*) __P((struct  vop_link_args *)))isofs_enotsupp)
#define isofs_rename ((int (*) __P((struct  vop_rename_args *)))isofs_enotsupp)
#define isofs_mkdir ((int (*) __P((struct  vop_mkdir_args *)))isofs_enotsupp)
#define isofs_rmdir ((int (*) __P((struct  vop_rmdir_args *)))isofs_enotsupp)
#define isofs_symlink \
	((int (*) __P((struct vop_symlink_args *)))isofs_enotsupp)
#define isofs_pathconf \
	((int (*) __P((struct vop_pathconf_args *)))isofs_enotsupp)
#define isofs_advlock \
	((int (*) __P((struct vop_advlock_args *)))isofs_enotsupp)
#define isofs_blkatoff \
	((int (*) __P((struct  vop_blkatoff_args *)))isofs_enotsupp)
#define isofs_valloc ((int(*) __P(( \
E 3
I 3
#define cd9660_create \
D 17
	((int (*) __P((struct  vop_create_args *)))cd9660_enotsupp)
#define cd9660_mknod ((int (*) __P((struct  vop_mknod_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_create_args *)))eopnotsupp)
#define cd9660_mknod ((int (*) __P((struct  vop_mknod_args *)))eopnotsupp)
E 17
D 19
#define cd9660_setattr \
D 17
	((int (*) __P((struct  vop_setattr_args *)))cd9660_enotsupp)
#define cd9660_write ((int (*) __P((struct  vop_write_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_setattr_args *)))eopnotsupp)
E 19
#define cd9660_write ((int (*) __P((struct  vop_write_args *)))eopnotsupp)
E 17
I 10
#ifdef NFS
int	 lease_check __P((struct vop_lease_args *));
#define	 cd9660_lease_check lease_check
#else
#define	 cd9660_lease_check ((int (*) __P((struct vop_lease_args *)))nullop)
#endif
E 10
#define cd9660_fsync ((int (*) __P((struct  vop_fsync_args *)))nullop)
#define cd9660_remove \
D 17
	((int (*) __P((struct  vop_remove_args *)))cd9660_enotsupp)
#define cd9660_link ((int (*) __P((struct  vop_link_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_remove_args *)))eopnotsupp)
#define cd9660_link ((int (*) __P((struct  vop_link_args *)))eopnotsupp)
E 17
#define cd9660_rename \
D 17
	((int (*) __P((struct  vop_rename_args *)))cd9660_enotsupp)
#define cd9660_mkdir ((int (*) __P((struct  vop_mkdir_args *)))cd9660_enotsupp)
#define cd9660_rmdir ((int (*) __P((struct  vop_rmdir_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_rename_args *)))eopnotsupp)
#define cd9660_mkdir ((int (*) __P((struct  vop_mkdir_args *)))eopnotsupp)
#define cd9660_rmdir ((int (*) __P((struct  vop_rmdir_args *)))eopnotsupp)
E 17
#define cd9660_symlink \
D 17
	((int (*) __P((struct vop_symlink_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct vop_symlink_args *)))eopnotsupp)
E 17
D 14
#define cd9660_pathconf \
	((int (*) __P((struct vop_pathconf_args *)))cd9660_enotsupp)
E 14
#define cd9660_advlock \
D 17
	((int (*) __P((struct vop_advlock_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct vop_advlock_args *)))eopnotsupp)
E 17
D 14
#define cd9660_blkatoff \
	((int (*) __P((struct  vop_blkatoff_args *)))cd9660_enotsupp)
E 14
#define cd9660_valloc ((int(*) __P(( \
E 3
		struct vnode *pvp, \
		int mode, \
		struct ucred *cred, \
D 3
		struct vnode **vpp))) isofs_enotsupp)
#define isofs_vfree ((int (*) __P((struct  vop_vfree_args *)))isofs_enotsupp)
#define isofs_truncate \
	((int (*) __P((struct  vop_truncate_args *)))isofs_enotsupp)
#define isofs_update ((int (*) __P((struct  vop_update_args *)))isofs_enotsupp)
#define isofs_bwrite ((int (*) __P((struct  vop_bwrite_args *)))isofs_enotsupp)
E 3
I 3
D 17
		struct vnode **vpp))) cd9660_enotsupp)
#define cd9660_vfree ((int (*) __P((struct  vop_vfree_args *)))cd9660_enotsupp)
E 17
I 17
		struct vnode **vpp))) eopnotsupp)
#define cd9660_vfree ((int (*) __P((struct  vop_vfree_args *)))eopnotsupp)
E 17
#define cd9660_truncate \
D 17
	((int (*) __P((struct  vop_truncate_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_truncate_args *)))eopnotsupp)
E 17
#define cd9660_update \
D 17
	((int (*) __P((struct  vop_update_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_update_args *)))eopnotsupp)
E 17
#define cd9660_bwrite \
D 17
	((int (*) __P((struct  vop_bwrite_args *)))cd9660_enotsupp)
E 17
I 17
	((int (*) __P((struct  vop_bwrite_args *)))eopnotsupp)
E 17
E 3

/*
D 14
 * Global vfs data structures for nfs
E 14
I 14
 * Global vfs data structures for cd9660
E 14
 */
D 3
int (**isofs_vnodeop_p)();
struct vnodeopv_entry_desc isofs_vnodeop_entries[] = {
E 3
I 3
int (**cd9660_vnodeop_p)();
struct vnodeopv_entry_desc cd9660_vnodeop_entries[] = {
E 3
	{ &vop_default_desc, vn_default_error },
D 3
	{ &vop_lookup_desc, isofs_lookup },	/* lookup */
	{ &vop_create_desc, isofs_create },	/* create */
	{ &vop_mknod_desc, isofs_mknod },	/* mknod */
	{ &vop_open_desc, isofs_open },		/* open */
	{ &vop_close_desc, isofs_close },	/* close */
	{ &vop_access_desc, isofs_access },	/* access */
	{ &vop_getattr_desc, isofs_getattr },	/* getattr */
	{ &vop_setattr_desc, isofs_setattr },	/* setattr */
	{ &vop_read_desc, isofs_read },		/* read */
	{ &vop_write_desc, isofs_write },	/* write */
	{ &vop_ioctl_desc, isofs_ioctl },	/* ioctl */
	{ &vop_select_desc, isofs_select },	/* select */
	{ &vop_mmap_desc, isofs_mmap },		/* mmap */
	{ &vop_fsync_desc, isofs_fsync },	/* fsync */
	{ &vop_seek_desc, isofs_seek },		/* seek */
	{ &vop_remove_desc, isofs_remove },	/* remove */
	{ &vop_link_desc, isofs_link },		/* link */
	{ &vop_rename_desc, isofs_rename },	/* rename */
	{ &vop_mkdir_desc, isofs_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, isofs_rmdir },	/* rmdir */
	{ &vop_symlink_desc, isofs_symlink },	/* symlink */
	{ &vop_readdir_desc, isofs_readdir },	/* readdir */
	{ &vop_readlink_desc, isofs_readlink },	/* readlink */
	{ &vop_abortop_desc, isofs_abortop },	/* abortop */
	{ &vop_inactive_desc, isofs_inactive },	/* inactive */
	{ &vop_reclaim_desc, isofs_reclaim },	/* reclaim */
	{ &vop_lock_desc, isofs_lock },		/* lock */
	{ &vop_unlock_desc, isofs_unlock },	/* unlock */
	{ &vop_bmap_desc, isofs_bmap },		/* bmap */
	{ &vop_strategy_desc, isofs_strategy },	/* strategy */
	{ &vop_print_desc, isofs_print },	/* print */
	{ &vop_islocked_desc, isofs_islocked },	/* islocked */
	{ &vop_pathconf_desc, isofs_pathconf },	/* pathconf */
	{ &vop_advlock_desc, isofs_advlock },	/* advlock */
	{ &vop_blkatoff_desc, isofs_blkatoff },	/* blkatoff */
	{ &vop_valloc_desc, isofs_valloc },	/* valloc */
	{ &vop_vfree_desc, isofs_vfree },	/* vfree */
	{ &vop_truncate_desc, isofs_truncate },	/* truncate */
	{ &vop_update_desc, isofs_update },	/* update */
E 3
I 3
	{ &vop_lookup_desc, cd9660_lookup },	/* lookup */
	{ &vop_create_desc, cd9660_create },	/* create */
	{ &vop_mknod_desc, cd9660_mknod },	/* mknod */
	{ &vop_open_desc, cd9660_open },	/* open */
	{ &vop_close_desc, cd9660_close },	/* close */
	{ &vop_access_desc, cd9660_access },	/* access */
	{ &vop_getattr_desc, cd9660_getattr },	/* getattr */
	{ &vop_setattr_desc, cd9660_setattr },	/* setattr */
	{ &vop_read_desc, cd9660_read },	/* read */
	{ &vop_write_desc, cd9660_write },	/* write */
I 10
	{ &vop_lease_desc, cd9660_lease_check },/* lease */
E 10
	{ &vop_ioctl_desc, cd9660_ioctl },	/* ioctl */
	{ &vop_select_desc, cd9660_select },	/* select */
I 16
	{ &vop_revoke_desc, cd9660_revoke },	/* revoke */
E 16
	{ &vop_mmap_desc, cd9660_mmap },	/* mmap */
	{ &vop_fsync_desc, cd9660_fsync },	/* fsync */
	{ &vop_seek_desc, cd9660_seek },	/* seek */
	{ &vop_remove_desc, cd9660_remove },	/* remove */
	{ &vop_link_desc, cd9660_link },	/* link */
	{ &vop_rename_desc, cd9660_rename },	/* rename */
	{ &vop_mkdir_desc, cd9660_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, cd9660_rmdir },	/* rmdir */
	{ &vop_symlink_desc, cd9660_symlink },	/* symlink */
	{ &vop_readdir_desc, cd9660_readdir },	/* readdir */
	{ &vop_readlink_desc, cd9660_readlink },/* readlink */
	{ &vop_abortop_desc, cd9660_abortop },	/* abortop */
	{ &vop_inactive_desc, cd9660_inactive },/* inactive */
	{ &vop_reclaim_desc, cd9660_reclaim },	/* reclaim */
	{ &vop_lock_desc, cd9660_lock },	/* lock */
	{ &vop_unlock_desc, cd9660_unlock },	/* unlock */
	{ &vop_bmap_desc, cd9660_bmap },	/* bmap */
	{ &vop_strategy_desc, cd9660_strategy },/* strategy */
	{ &vop_print_desc, cd9660_print },	/* print */
	{ &vop_islocked_desc, cd9660_islocked },/* islocked */
	{ &vop_pathconf_desc, cd9660_pathconf },/* pathconf */
	{ &vop_advlock_desc, cd9660_advlock },	/* advlock */
	{ &vop_blkatoff_desc, cd9660_blkatoff },/* blkatoff */
	{ &vop_valloc_desc, cd9660_valloc },	/* valloc */
	{ &vop_vfree_desc, cd9660_vfree },	/* vfree */
	{ &vop_truncate_desc, cd9660_truncate },/* truncate */
	{ &vop_update_desc, cd9660_update },	/* update */
E 3
	{ &vop_bwrite_desc, vn_bwrite },
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
D 3
struct vnodeopv_desc isofs_vnodeop_opv_desc =
	{ &isofs_vnodeop_p, isofs_vnodeop_entries };
E 3
I 3
struct vnodeopv_desc cd9660_vnodeop_opv_desc =
	{ &cd9660_vnodeop_p, cd9660_vnodeop_entries };
E 3

/*
 * Special device vnode ops
 */
D 3
int (**isofs_specop_p)();
struct vnodeopv_entry_desc isofs_specop_entries[] = {
E 3
I 3
int (**cd9660_specop_p)();
struct vnodeopv_entry_desc cd9660_specop_entries[] = {
E 3
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, spec_lookup },	/* lookup */
D 3
	{ &vop_create_desc, isofs_create },	/* create */
	{ &vop_mknod_desc, isofs_mknod },	/* mknod */
E 3
I 3
D 13
	{ &vop_create_desc, cd9660_create },	/* create */
	{ &vop_mknod_desc, cd9660_mknod },	/* mknod */
E 13
I 13
	{ &vop_create_desc, spec_create },	/* create */
	{ &vop_mknod_desc, spec_mknod },	/* mknod */
E 13
E 3
	{ &vop_open_desc, spec_open },		/* open */
	{ &vop_close_desc, spec_close },	/* close */
D 3
	{ &vop_access_desc, isofs_access },	/* access */
	{ &vop_getattr_desc, isofs_getattr },	/* getattr */
	{ &vop_setattr_desc, isofs_setattr },	/* setattr */
E 3
I 3
	{ &vop_access_desc, cd9660_access },	/* access */
	{ &vop_getattr_desc, cd9660_getattr },	/* getattr */
	{ &vop_setattr_desc, cd9660_setattr },	/* setattr */
E 3
	{ &vop_read_desc, spec_read },		/* read */
	{ &vop_write_desc, spec_write },	/* write */
I 10
	{ &vop_lease_desc, spec_lease_check },	/* lease */
E 10
	{ &vop_ioctl_desc, spec_ioctl },	/* ioctl */
	{ &vop_select_desc, spec_select },	/* select */
I 16
	{ &vop_revoke_desc, spec_revoke },	/* revoke */
E 16
	{ &vop_mmap_desc, spec_mmap },		/* mmap */
	{ &vop_fsync_desc, spec_fsync },	/* fsync */
	{ &vop_seek_desc, spec_seek },		/* seek */
D 3
	{ &vop_remove_desc, isofs_remove },	/* remove */
	{ &vop_link_desc, isofs_link },		/* link */
	{ &vop_rename_desc, isofs_rename },	/* rename */
	{ &vop_mkdir_desc, isofs_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, isofs_rmdir },	/* rmdir */
	{ &vop_symlink_desc, isofs_symlink },	/* symlink */
E 3
I 3
D 13
	{ &vop_remove_desc, cd9660_remove },	/* remove */
	{ &vop_link_desc, cd9660_link },	/* link */
	{ &vop_rename_desc, cd9660_rename },	/* rename */
	{ &vop_mkdir_desc, cd9660_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, cd9660_rmdir },	/* rmdir */
	{ &vop_symlink_desc, cd9660_symlink },	/* symlink */
E 13
I 13
	{ &vop_remove_desc, spec_remove },	/* remove */
	{ &vop_link_desc, spec_link },		/* link */
	{ &vop_rename_desc, spec_rename },	/* rename */
	{ &vop_mkdir_desc, spec_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, spec_rmdir },	/* rmdir */
	{ &vop_symlink_desc, spec_symlink },	/* symlink */
E 13
E 3
	{ &vop_readdir_desc, spec_readdir },	/* readdir */
	{ &vop_readlink_desc, spec_readlink },	/* readlink */
	{ &vop_abortop_desc, spec_abortop },	/* abortop */
D 3
	{ &vop_inactive_desc, isofs_inactive },	/* inactive */
	{ &vop_reclaim_desc, isofs_reclaim },	/* reclaim */
	{ &vop_lock_desc, isofs_lock },		/* lock */
	{ &vop_unlock_desc, isofs_unlock },	/* unlock */
E 3
I 3
	{ &vop_inactive_desc, cd9660_inactive },/* inactive */
	{ &vop_reclaim_desc, cd9660_reclaim },	/* reclaim */
	{ &vop_lock_desc, cd9660_lock },	/* lock */
	{ &vop_unlock_desc, cd9660_unlock },	/* unlock */
E 3
	{ &vop_bmap_desc, spec_bmap },		/* bmap */
D 13
		/* XXX strategy: panics, should be notsupp instead? */
D 3
	{ &vop_strategy_desc, isofs_strategy },	/* strategy */
	{ &vop_print_desc, isofs_print },	/* print */
	{ &vop_islocked_desc, isofs_islocked },	/* islocked */
E 3
I 3
	{ &vop_strategy_desc, cd9660_strategy },/* strategy */
E 13
I 13
	{ &vop_strategy_desc, spec_strategy },	/* strategy */
E 13
	{ &vop_print_desc, cd9660_print },	/* print */
	{ &vop_islocked_desc, cd9660_islocked },/* islocked */
E 3
	{ &vop_pathconf_desc, spec_pathconf },	/* pathconf */
	{ &vop_advlock_desc, spec_advlock },	/* advlock */
	{ &vop_blkatoff_desc, spec_blkatoff },	/* blkatoff */
	{ &vop_valloc_desc, spec_valloc },	/* valloc */
	{ &vop_vfree_desc, spec_vfree },	/* vfree */
	{ &vop_truncate_desc, spec_truncate },	/* truncate */
D 3
	{ &vop_update_desc, isofs_update },	/* update */
E 3
I 3
	{ &vop_update_desc, cd9660_update },	/* update */
E 3
	{ &vop_bwrite_desc, vn_bwrite },
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
D 3
struct vnodeopv_desc isofs_specop_opv_desc =
	{ &isofs_specop_p, isofs_specop_entries };
E 3
I 3
struct vnodeopv_desc cd9660_specop_opv_desc =
	{ &cd9660_specop_p, cd9660_specop_entries };
E 3

#ifdef FIFO
D 3
int (**isofs_fifoop_p)();
struct vnodeopv_entry_desc isofs_fifoop_entries[] = {
E 3
I 3
int (**cd9660_fifoop_p)();
struct vnodeopv_entry_desc cd9660_fifoop_entries[] = {
E 3
	{ &vop_default_desc, vn_default_error },
	{ &vop_lookup_desc, fifo_lookup },	/* lookup */
D 3
	{ &vop_create_desc, isofs_create },	/* create */
	{ &vop_mknod_desc, isofs_mknod },	/* mknod */
E 3
I 3
D 13
	{ &vop_create_desc, cd9660_create },	/* create */
	{ &vop_mknod_desc, cd9660_mknod },	/* mknod */
E 13
I 13
	{ &vop_create_desc, fifo_create },	/* create */
	{ &vop_mknod_desc, fifo_mknod },	/* mknod */
E 13
E 3
	{ &vop_open_desc, fifo_open },		/* open */
	{ &vop_close_desc, fifo_close },	/* close */
D 3
	{ &vop_access_desc, isofs_access },	/* access */
	{ &vop_getattr_desc, isofs_getattr },	/* getattr */
	{ &vop_setattr_desc, isofs_setattr },	/* setattr */
E 3
I 3
	{ &vop_access_desc, cd9660_access },	/* access */
	{ &vop_getattr_desc, cd9660_getattr },	/* getattr */
	{ &vop_setattr_desc, cd9660_setattr },	/* setattr */
E 3
	{ &vop_read_desc, fifo_read },		/* read */
	{ &vop_write_desc, fifo_write },	/* write */
I 10
	{ &vop_lease_desc, fifo_lease_check },	/* lease */
E 10
	{ &vop_ioctl_desc, fifo_ioctl },	/* ioctl */
	{ &vop_select_desc, fifo_select },	/* select */
I 16
	{ &vop_revoke_desc, fifo_revoke },	/* revoke */
E 16
	{ &vop_mmap_desc, fifo_mmap },		/* mmap */
	{ &vop_fsync_desc, fifo_fsync },	/* fsync */
	{ &vop_seek_desc, fifo_seek },		/* seek */
D 3
	{ &vop_remove_desc, isofs_remove },	/* remove */
	{ &vop_link_desc, isofs_link },		/* link */
	{ &vop_rename_desc, isofs_rename },	/* rename */
	{ &vop_mkdir_desc, isofs_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, isofs_rmdir },	/* rmdir */
	{ &vop_symlink_desc, isofs_symlink },	/* symlink */
E 3
I 3
D 13
	{ &vop_remove_desc, cd9660_remove },	/* remove */
	{ &vop_link_desc, cd9660_link },	/* link */
	{ &vop_rename_desc, cd9660_rename },	/* rename */
	{ &vop_mkdir_desc, cd9660_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, cd9660_rmdir },	/* rmdir */
	{ &vop_symlink_desc, cd9660_symlink },	/* symlink */
E 13
I 13
	{ &vop_remove_desc, fifo_remove },	/* remove */
	{ &vop_link_desc, fifo_link }	,	/* link */
	{ &vop_rename_desc, fifo_rename },	/* rename */
	{ &vop_mkdir_desc, fifo_mkdir },	/* mkdir */
	{ &vop_rmdir_desc, fifo_rmdir },	/* rmdir */
	{ &vop_symlink_desc, fifo_symlink },	/* symlink */
E 13
E 3
	{ &vop_readdir_desc, fifo_readdir },	/* readdir */
	{ &vop_readlink_desc, fifo_readlink },	/* readlink */
	{ &vop_abortop_desc, fifo_abortop },	/* abortop */
D 3
	{ &vop_inactive_desc, isofs_inactive },	/* inactive */
	{ &vop_reclaim_desc, isofs_reclaim },	/* reclaim */
	{ &vop_lock_desc, isofs_lock },		/* lock */
	{ &vop_unlock_desc, isofs_unlock },	/* unlock */
E 3
I 3
	{ &vop_inactive_desc, cd9660_inactive },/* inactive */
	{ &vop_reclaim_desc, cd9660_reclaim },	/* reclaim */
	{ &vop_lock_desc, cd9660_lock },	/* lock */
	{ &vop_unlock_desc, cd9660_unlock },	/* unlock */
E 3
	{ &vop_bmap_desc, fifo_bmap },		/* bmap */
D 13
	{ &vop_strategy_desc, fifo_badop },	/* strategy */
E 13
I 13
	{ &vop_strategy_desc, fifo_strategy },	/* strategy */
E 13
D 3
	{ &vop_print_desc, isofs_print },	/* print */
	{ &vop_islocked_desc, isofs_islocked },	/* islocked */
E 3
I 3
	{ &vop_print_desc, cd9660_print },	/* print */
	{ &vop_islocked_desc, cd9660_islocked },/* islocked */
E 3
	{ &vop_pathconf_desc, fifo_pathconf },	/* pathconf */
	{ &vop_advlock_desc, fifo_advlock },	/* advlock */
	{ &vop_blkatoff_desc, fifo_blkatoff },	/* blkatoff */
	{ &vop_valloc_desc, fifo_valloc },	/* valloc */
	{ &vop_vfree_desc, fifo_vfree },	/* vfree */
	{ &vop_truncate_desc, fifo_truncate },	/* truncate */
D 3
	{ &vop_update_desc, isofs_update },	/* update */
E 3
I 3
	{ &vop_update_desc, cd9660_update },	/* update */
E 3
	{ &vop_bwrite_desc, vn_bwrite },
	{ (struct vnodeop_desc*)NULL, (int(*)())NULL }
};
D 3
struct vnodeopv_desc isofs_fifoop_opv_desc =
	{ &isofs_fifoop_p, isofs_fifoop_entries };
E 3
I 3
struct vnodeopv_desc cd9660_fifoop_opv_desc =
	{ &cd9660_fifoop_p, cd9660_fifoop_entries };
E 3
#endif /* FIFO */
E 1
