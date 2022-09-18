h60565
s 00004/00002/00451
d D 8.8 95/05/22 23:03:18 mckusick 8 7
c have to unlock at the end of inactive; vrecycle replaces vgone
e
s 00029/00027/00424
d D 8.7 95/05/14 00:34:50 mckusick 7 6
c convert to use lock manager
e
s 00003/00001/00448
d D 8.6 95/03/30 14:23:48 mckusick 6 5
c cd9660_init gets a parameter
e
s 00028/00024/00421
d D 8.5 94/12/05 21:55:08 mckusick 5 4
c update from mycroft
e
s 00107/00284/00338
d D 8.4 94/07/13 16:34:18 mckusick 4 3
c update for 4.4BSD-Lite (from mycroft)
e
s 00001/00001/00621
d D 8.3 94/06/14 11:54:05 mkm 3 2
c phase error in computing time (from Wolfgang Solfrank via mycroft)
e
s 00031/00031/00591
d D 8.2 94/01/23 23:50:47 mckusick 2 1
c isofs => cd9660 naming convention
e
s 00622/00000/00000
d D 8.1 94/01/21 18:28:57 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1982, 1986, 1989, 1994
E 7
I 7
 * Copyright (c) 1982, 1986, 1989, 1994, 1995
E 7
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
#include <sys/mount.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/stat.h>

#include <isofs/cd9660/iso.h>
D 2
#include <isofs/cd9660/isofs_node.h>
E 2
I 2
#include <isofs/cd9660/cd9660_node.h>
I 6
#include <isofs/cd9660/cd9660_mount.h>
E 6
E 2
#include <isofs/cd9660/iso_rrip.h>

D 4
#define	INOHSZ	512
#if	((INOHSZ&(INOHSZ-1)) == 0)
#define	INOHASH(dev,ino)	(((dev)+((ino)>>12))&(INOHSZ-1))
#else
#define	INOHASH(dev,ino)	(((unsigned)((dev)+((ino)>>12)))%INOHSZ)
#endif
E 4
I 4
/*
 * Structures associated with iso_node caching.
 */
struct iso_node **isohashtbl;
u_long isohash;
#define	INOHASH(device, inum)	(((device) + ((inum)>>12)) & isohash)
I 7
struct simplelock cd9660_ihash_slock;
E 7
E 4

D 4
union iso_ihead {
	union  iso_ihead *ih_head[2];
	struct iso_node *ih_chain[2];
} iso_ihead[INOHSZ];

#ifdef	ISODEVMAP
#define	DNOHSZ	64
#if	((DNOHSZ&(DNOHSZ-1)) == 0)
#define	DNOHASH(dev,ino)	(((dev)+((ino)>>12))&(DNOHSZ-1))
#else
#define	DNOHASH(dev,ino)	(((unsigned)((dev)+((ino)>>12)))%DNOHSZ)
E 4
I 4
#ifdef ISODEVMAP
struct iso_node **idvhashtbl;
u_long idvhash;
#define	DNOHASH(device, inum)	(((device) + ((inum)>>12)) & idvhash)
E 4
#endif

D 4
union iso_dhead {
	union  iso_dhead  *dh_head[2];
	struct iso_dnode *dh_chain[2];
} iso_dhead[DNOHSZ];
#endif

E 4
int prtactive;	/* 1 => print out reclaim of active vnodes */

/*
 * Initialize hash links for inodes and dnodes.
 */
D 2
isofs_init()
E 2
I 2
D 6
cd9660_init()
E 6
I 6
cd9660_init(vfsp)
	struct vfsconf *vfsp;
E 6
E 2
{
D 4
	register int i;
	register union iso_ihead *ih = iso_ihead;
#ifdef	ISODEVMAP
	register union iso_dhead *dh = iso_dhead;
#endif
E 4

D 4
	for (i = INOHSZ; --i >= 0; ih++) {
		ih->ih_head[0] = ih;
		ih->ih_head[1] = ih;
	}
#ifdef	ISODEVMAP
	for (i = DNOHSZ; --i >= 0; dh++) {
		dh->dh_head[0] = dh;
		dh->dh_head[1] = dh;
	}
E 4
I 4
	isohashtbl = hashinit(desiredvnodes, M_ISOFSMNT, &isohash);
I 7
	simple_lock_init(&cd9660_ihash_slock);
E 7
#ifdef ISODEVMAP
	idvhashtbl = hashinit(desiredvnodes / 8, M_ISOFSMNT, &idvhash);
E 4
#endif
}

D 4
#ifdef	ISODEVMAP
E 4
I 4
#ifdef ISODEVMAP
E 4
/*
 * Enter a new node into the device hash list
 */
struct iso_dnode *
D 4
iso_dmap(dev,ino,create)
	dev_t	dev;
	ino_t	ino;
E 4
I 4
iso_dmap(device, inum, create)
	dev_t	device;
	ino_t	inum;
E 4
	int	create;
{
D 4
	struct iso_dnode *dp;
	union iso_dhead *dh;
	
	dh = &iso_dhead[DNOHASH(dev, ino)];
	for (dp = dh->dh_chain[0];
	     dp != (struct iso_dnode *)dh;
	     dp = dp->d_forw)
		if (ino == dp->i_number && dev == dp->i_dev)
			return dp;
E 4
I 4
	register struct iso_dnode **dpp, *dp, *dq;
E 4

I 4
	dpp = &idvhashtbl[DNOHASH(device, inum)];
	for (dp = *dpp;; dp = dp->d_next) {
		if (dp == NULL)
			return (NULL);
		if (inum == dp->i_number && device == dp->i_dev)
			return (dp);

E 4
	if (!create)
D 4
		return (struct iso_dnode *)0;
E 4
I 4
		return (NULL);
E 4

D 4
	MALLOC(dp,struct iso_dnode *,sizeof(struct iso_dnode),M_CACHE,M_WAITOK);
E 4
I 4
	MALLOC(dp, struct iso_dnode *, sizeof(struct iso_dnode), M_CACHE,
	       M_WAITOK);
E 4
	dp->i_dev = dev;
	dp->i_number = ino;
D 4
	insque(dp,dh);
	
	return dp;
E 4
I 4

	if (dq = *dpp)
		dq->d_prev = dp->d_next;
	dp->d_next = dq;
	dp->d_prev = dpp;
	*dpp = dp;

	return (dp);
E 4
}

void
D 4
iso_dunmap(dev)
	dev_t	dev;
E 4
I 4
iso_dunmap(device)
	dev_t device;
E 4
{
D 4
	struct iso_dnode *dp, *dq;
	union iso_dhead *dh;
E 4
I 4
	struct iso_dnode **dpp, *dp, *dq;
E 4
	
D 4
	for (dh = iso_dhead; dh < iso_dhead + DNOHSZ; dh++) {
		for (dp = dh->dh_chain[0];
		     dp != (struct iso_dnode *)dh;
		     dp = dq) {
			dq = dp->d_forw;
			if (dev == dp->i_dev) {
				remque(dp);
				FREE(dp,M_CACHE);
E 4
I 4
	for (dpp = idvhashtbl; dpp <= idvhashtbl + idvhash; dpp++) {
		for (dp = *dpp; dp != NULL; dp = dq)
			dq = dp->d_next;
			if (device == dp->i_dev) {
				if (dq)
					dq->d_prev = dp->d_prev;
				*dp->d_prev = dq;
				FREE(dp, M_CACHE);
E 4
			}
		}
	}
}
#endif

/*
D 4
 * Look up a ISOFS dinode number to find its incore vnode.
 * If it is not in core, read it in from the specified device.
 * If it is in core, wait for the lock bit to clear, then
 * return the inode locked. Detection and handling of mount
 * points must be done by the calling routine.
E 4
I 4
 * Use the device/inum pair to find the incore inode, and return a pointer
 * to it. If it is in core, but locked, wait for it.
E 4
 */
D 4
iso_iget(xp, ino, relocated, ipp, isodir)
	struct iso_node *xp;
	ino_t ino;
	struct iso_node **ipp;
	struct iso_directory_record *isodir;
E 4
I 4
struct vnode *
D 7
cd9660_ihashget(device, inum)
	dev_t device;
E 7
I 7
cd9660_ihashget(dev, inum)
	dev_t dev;
E 7
	ino_t inum;
E 4
{
D 4
	dev_t dev = xp->i_dev;
	struct mount *mntp = ITOV(xp)->v_mount;
	register struct iso_node *ip, *iq;
	register struct vnode *vp;
	register struct iso_dnode *dp;
	struct vnode *nvp;
	struct buf *bp = NULL, *bp2 = NULL;
	union iso_ihead *ih;
	union iso_dhead *dh;
	int i, error, result;
	struct iso_mnt *imp;
	ino_t defino;
	
	ih = &iso_ihead[INOHASH(dev, ino)];
loop:
	for (ip = ih->ih_chain[0];
	     ip != (struct iso_node *)ih;
	     ip = ip->i_forw) {
		if (ino != ip->i_number || dev != ip->i_dev)
			continue;
		if ((ip->i_flag&ILOCKED) != 0) {
			ip->i_flag |= IWANT;
			sleep((caddr_t)ip, PINOD);
			goto loop;
		}
		if (vget(ITOV(ip), 1))
			goto loop;
		*ipp = ip;
		return 0;
	}
	/*
	 * Allocate a new vnode/iso_node.
	 */
D 2
	if (error = getnewvnode(VT_ISOFS, mntp, isofs_vnodeop_p, &nvp)) {
E 2
I 2
	if (error = getnewvnode(VT_ISOFS, mntp, cd9660_vnodeop_p, &nvp)) {
E 2
		*ipp = 0;
		return error;
	}
	MALLOC(ip, struct iso_node *, sizeof(struct iso_node),
	       M_ISOFSNODE, M_WAITOK);
	bzero((caddr_t)ip, sizeof(struct iso_node));
	nvp->v_data = ip;
	ip->i_vnode = nvp;
	ip->i_flag = 0;
	ip->i_devvp = 0;
	ip->i_diroff = 0;
	ip->i_lockf = 0;
	
	/*
	 * Put it onto its hash chain and lock it so that other requests for
	 * this inode will block if they arrive while we are sleeping waiting
	 * for old data structures to be purged or for the contents of the
	 * disk portion of this inode to be read.
	 */
	ip->i_dev = dev;
	ip->i_number = ino;
	insque(ip, ih);
	ISO_ILOCK(ip);
E 4
I 4
D 7
	register struct iso_node *ip;
E 7
I 7
	struct proc *p = curproc;		/* XXX */
	struct iso_node *ip;
E 7
	struct vnode *vp;
E 4

D 4
	imp = VFSTOISOFS (mntp);
	ip->i_mnt = imp;
	ip->i_devvp = imp->im_devvp;
	VREF(ip->i_devvp);
	
	if (relocated) {
		/*
		 * On relocated directories we must
		 * read the `.' entry out of a dir.
		 */
		ip->iso_start = ino >> imp->im_bshift;
		if (error = iso_blkatoff(ip,0,&bp)) {
			vrele(ip->i_devvp);
			remque(ip);
			ip->i_forw = ip;
			ip->i_back = ip;
			iso_iput(ip);
			*ipp = 0;
			return error;
E 4
I 4
D 7
	for (;;)
		for (ip = isohashtbl[INOHASH(device, inum)];; ip = ip->i_next) {
			if (ip == NULL)
				return (NULL);
			if (inum == ip->i_number && device == ip->i_dev) {
				if (ip->i_flag & IN_LOCKED) {
					ip->i_flag |= IN_WANTED;
					sleep(ip, PINOD);
					break;
				}
				vp = ITOV(ip);
				if (!vget(vp, 1))
					return (vp);
				break;
			}
E 7
I 7
loop:
	simple_lock(&cd9660_ihash_slock);
	for (ip = isohashtbl[INOHASH(dev, inum)]; ip; ip = ip->i_next) {
		if (inum == ip->i_number && dev == ip->i_dev) {
			vp = ITOV(ip);
			simple_lock(&vp->v_interlock);
			simple_unlock(&cd9660_ihash_slock);
			if (vget(vp, LK_EXCLUSIVE | LK_INTERLOCK, p))
				goto loop;
			return (vp);
E 7
E 4
		}
D 4
		isodir = (struct iso_directory_record *)bp->b_un.b_addr;
	}
	
	ip->iso_extent = isonum_733(isodir->extent);
	ip->i_size = isonum_733(isodir->size);
	ip->iso_start = isonum_711(isodir->ext_attr_length) + ip->iso_extent;
	
	vp = ITOV(ip);
	
	/*
	 * Setup time stamp, attribute
	 */
	vp->v_type = VNON;
	switch (imp->iso_ftype) {
	default:	/* ISO_FTYPE_9660 */
		if ((imp->im_flags&ISOFSMNT_EXTATT)
		    && isonum_711(isodir->ext_attr_length))
			iso_blkatoff(ip,-isonum_711(isodir->ext_attr_length),
				     &bp2);
D 2
		isofs_defattr(isodir,ip,bp2 );
		isofs_deftstamp(isodir,ip,bp2 );
E 2
I 2
		cd9660_defattr(isodir,ip,bp2 );
		cd9660_deftstamp(isodir,ip,bp2 );
E 2
		break;
	case ISO_FTYPE_RRIP:
D 2
		result = isofs_rrip_analyze(isodir,ip,imp);
E 2
I 2
		result = cd9660_rrip_analyze(isodir,ip,imp);
E 2
		break;
	}
	if (bp2)
		brelse(bp2);
	if (bp)
		brelse(bp);
	
	/*
	 * Initialize the associated vnode
	 */
	vp->v_type = IFTOVT(ip->inode.iso_mode);
	
	if ( vp->v_type == VFIFO ) {
#ifdef	FIFO
D 2
		extern int (**isofs_fifoop_p)();
		vp->v_op = isofs_fifoop_p;
E 2
I 2
		extern int (**cd9660_fifoop_p)();
		vp->v_op = cd9660_fifoop_p;
E 2
#else
		iso_iput(ip);
		*ipp = 0;
		return EOPNOTSUPP;
#endif	/* FIFO */
	} else if ( vp->v_type == VCHR || vp->v_type == VBLK ) {
D 2
		extern int (**isofs_specop_p)();
E 2
I 2
		extern int (**cd9660_specop_p)();
E 4
I 4
D 7
	/* NOTREACHED */
E 7
I 7
	}
	simple_unlock(&cd9660_ihash_slock);
	return (NULL);
E 7
}
E 4
E 2

D 4
		/*
		 * if device, look at device number table for translation
		 */
#ifdef	ISODEVMAP
		if (dp = iso_dmap(dev,ino,0))
			ip->inode.iso_rdev = dp->d_dev;
#endif
D 2
		vp->v_op = isofs_specop_p;
E 2
I 2
		vp->v_op = cd9660_specop_p;
E 2
		if (nvp = checkalias(vp, ip->inode.iso_rdev, mntp)) {
			/*
			 * Reinitialize aliased inode.
			 */
			vp = nvp;
			iq = VTOI(vp);
			iq->i_vnode = vp;
			iq->i_flag = 0;
			ISO_ILOCK(iq);
			iq->i_dev = dev;
			iq->i_number = ino;
			iq->i_mnt = ip->i_mnt;
			bcopy(&ip->iso_extent,&iq->iso_extent,
			      (char *)(ip + 1) - (char *)&ip->iso_extent);
			insque(iq, ih);
			/*
			 * Discard unneeded vnode
			 * (This introduces the need of INACTIVE modification)
			 */
			ip->inode.iso_mode = 0;
			iso_iput(ip);
			ip = iq;
		}
	}
	
	if (ip->iso_extent == imp->root_extent)
		vp->v_flag |= VROOT;
	
E 4
I 4
/*
 * Insert the inode into the hash table, and return it locked.
 */
void
cd9660_ihashins(ip)
	struct iso_node *ip;
{
I 7
	struct proc *p = curproc;		/* XXX */
E 7
	struct iso_node **ipp, *iq;

I 7
	simple_lock(&cd9660_ihash_slock);
E 7
	ipp = &isohashtbl[INOHASH(ip->i_dev, ip->i_number)];
	if (iq = *ipp)
		iq->i_prev = &ip->i_next;
	ip->i_next = iq;
	ip->i_prev = ipp;
E 4
	*ipp = ip;
D 4
	return 0;
E 4
I 4
D 7
	if (ip->i_flag & IN_LOCKED)
		panic("cd9660_ihashins: already locked");
	if (curproc)
		ip->i_lockholder = curproc->p_pid;
	else
		ip->i_lockholder = -1;
	ip->i_flag |= IN_LOCKED;
E 7
I 7
	simple_unlock(&cd9660_ihash_slock);

	lockmgr(&ip->i_lock, LK_EXCLUSIVE, (struct simplelock *)0, p);
E 7
E 4
}

/*
D 4
 * Unlock and decrement the reference count of an inode structure.
E 4
I 4
 * Remove the inode from the hash table.
E 4
 */
D 4
iso_iput(ip)
E 4
I 4
void
cd9660_ihashrem(ip)
E 4
	register struct iso_node *ip;
{
D 4
	
	if ((ip->i_flag & ILOCKED) == 0)
		panic("iso_iput");
	ISO_IUNLOCK(ip);
	vrele(ITOV(ip));
E 4
I 4
	register struct iso_node *iq;

I 7
	simple_lock(&cd9660_ihash_slock);
E 7
	if (iq = ip->i_next)
		iq->i_prev = ip->i_prev;
	*ip->i_prev = iq;
#ifdef DIAGNOSTIC
	ip->i_next = NULL;
	ip->i_prev = NULL;
#endif
I 7
	simple_unlock(&cd9660_ihash_slock);
E 7
E 4
}

/*
 * Last reference to an inode, write the inode out and if necessary,
 * truncate and deallocate the file.
 */
int
D 2
isofs_inactive(ap)
E 2
I 2
cd9660_inactive(ap)
E 2
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 7
		struct proc *a_p;
E 7
	} */ *ap;
{
	struct vnode *vp = ap->a_vp;
I 8
	struct proc *p = ap->a_p;
E 8
	register struct iso_node *ip = VTOI(vp);
	int mode, error = 0;
	
	if (prtactive && vp->v_usecount != 0)
D 2
		vprint("isofs_inactive: pushing active", vp);
E 2
I 2
		vprint("cd9660_inactive: pushing active", vp);
E 2
	
	ip->i_flag = 0;
I 8
	VOP_UNLOCK(vp, 0, p);
E 8
	/*
	 * If we are done with the inode, reclaim it
	 * so that it can be reused immediately.
	 */
D 8
	if (vp->v_usecount == 0 && ip->inode.iso_mode == 0)
		vgone(vp);
E 8
I 8
	if (ip->inode.iso_mode == 0)
		vrecycle(vp, (struct simplelock *)0, p);
E 8
	return error;
}

/*
 * Reclaim an inode so that it can be used for other purposes.
 */
int
D 2
isofs_reclaim(ap)
E 2
I 2
cd9660_reclaim(ap)
E 2
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
I 7
		struct proc *a_p;
E 7
	} */ *ap;
{
	register struct vnode *vp = ap->a_vp;
	register struct iso_node *ip = VTOI(vp);
	int i;
	
	if (prtactive && vp->v_usecount != 0)
D 2
		vprint("isofs_reclaim: pushing active", vp);
E 2
I 2
		vprint("cd9660_reclaim: pushing active", vp);
E 2
	/*
	 * Remove the inode from its hash chain.
	 */
D 4
	remque(ip);
	ip->i_forw = ip;
	ip->i_back = ip;
E 4
I 4
	cd9660_ihashrem(ip);
E 4
	/*
	 * Purge old data structures associated with the inode.
	 */
	cache_purge(vp);
	if (ip->i_devvp) {
		vrele(ip->i_devvp);
		ip->i_devvp = 0;
	}
	FREE(vp->v_data, M_ISOFSNODE);
	vp->v_data = NULL;
D 4
	return 0;
}

/*
 * Lock an inode. If its already locked, set the WANT bit and sleep.
 */
iso_ilock(ip)
	register struct iso_node *ip;
{
	
	while (ip->i_flag & ILOCKED) {
		ip->i_flag |= IWANT;
		if (ip->i_spare0 == curproc->p_pid)
			panic("locking against myself");
		ip->i_spare1 = curproc->p_pid;
		(void) sleep((caddr_t)ip, PINOD);
	}
	ip->i_spare1 = 0;
	ip->i_spare0 = curproc->p_pid;
	ip->i_flag |= ILOCKED;
}

/*
 * Unlock an inode.  If WANT bit is on, wakeup.
 */
iso_iunlock(ip)
	register struct iso_node *ip;
{

	if ((ip->i_flag & ILOCKED) == 0)
		vprint("iso_iunlock: unlocked inode", ITOV(ip));
	ip->i_spare0 = 0;
	ip->i_flag &= ~ILOCKED;
	if (ip->i_flag&IWANT) {
		ip->i_flag &= ~IWANT;
		wakeup((caddr_t)ip);
	}
E 4
I 4
	return (0);
E 4
}

/*
 * File attributes
 */
void
D 2
isofs_defattr(isodir,inop,bp)
E 2
I 2
D 5
cd9660_defattr(isodir,inop,bp)
E 5
I 5
cd9660_defattr(isodir, inop, bp)
E 5
E 2
	struct iso_directory_record *isodir;
	struct iso_node *inop;
	struct buf *bp;
{
	struct buf *bp2 = NULL;
	struct iso_mnt *imp;
	struct iso_extended_attributes *ap = NULL;
	int off;
	
	if (isonum_711(isodir->flags)&2) {
		inop->inode.iso_mode = S_IFDIR;
		/*
		 * If we return 2, fts() will assume there are no subdirectories
		 * (just links for the path and .), so instead we return 1.
		 */
		inop->inode.iso_links = 1;
	} else {
		inop->inode.iso_mode = S_IFREG;
		inop->inode.iso_links = 1;
	}
	if (!bp
D 5
	    && ((imp = inop->i_mnt)->im_flags&ISOFSMNT_EXTATT)
E 5
I 5
	    && ((imp = inop->i_mnt)->im_flags & ISOFSMNT_EXTATT)
E 5
	    && (off = isonum_711(isodir->ext_attr_length))) {
D 5
		iso_blkatoff(inop,-off * imp->logical_block_size,&bp2);
E 5
I 5
		VOP_BLKATOFF(ITOV(inop), (off_t)-(off << imp->im_bshift), NULL,
			     &bp2);
E 5
		bp = bp2;
	}
	if (bp) {
D 5
		ap = (struct iso_extended_attributes *)bp->b_un.b_addr;
E 5
I 5
		ap = (struct iso_extended_attributes *)bp->b_data;
E 5
		
		if (isonum_711(ap->version) == 1) {
			if (!(ap->perm[0]&0x40))
				inop->inode.iso_mode |= VEXEC >> 6;
			if (!(ap->perm[0]&0x10))
				inop->inode.iso_mode |= VREAD >> 6;
			if (!(ap->perm[0]&4))
				inop->inode.iso_mode |= VEXEC >> 3;
			if (!(ap->perm[0]&1))
				inop->inode.iso_mode |= VREAD >> 3;
			if (!(ap->perm[1]&0x40))
				inop->inode.iso_mode |= VEXEC;
			if (!(ap->perm[1]&0x10))
				inop->inode.iso_mode |= VREAD;
			inop->inode.iso_uid = isonum_723(ap->owner); /* what about 0? */
			inop->inode.iso_gid = isonum_723(ap->group); /* what about 0? */
		} else
			ap = NULL;
	}
	if (!ap) {
		inop->inode.iso_mode |= VREAD|VEXEC|(VREAD|VEXEC)>>3|(VREAD|VEXEC)>>6;
		inop->inode.iso_uid = (uid_t)0;
		inop->inode.iso_gid = (gid_t)0;
	}
	if (bp2)
		brelse(bp2);
}

/*
 * Time stamps
 */
void
D 2
isofs_deftstamp(isodir,inop,bp)
E 2
I 2
cd9660_deftstamp(isodir,inop,bp)
E 2
	struct iso_directory_record *isodir;
	struct iso_node *inop;
	struct buf *bp;
{
	struct buf *bp2 = NULL;
	struct iso_mnt *imp;
	struct iso_extended_attributes *ap = NULL;
	int off;
	
	if (!bp
D 5
	    && ((imp = inop->i_mnt)->im_flags&ISOFSMNT_EXTATT)
E 5
I 5
	    && ((imp = inop->i_mnt)->im_flags & ISOFSMNT_EXTATT)
E 5
	    && (off = isonum_711(isodir->ext_attr_length))) {
D 5
		iso_blkatoff(inop,-off * imp->logical_block_size,&bp2);
E 5
I 5
		VOP_BLKATOFF(ITOV(inop), (off_t)-(off << imp->im_bshift), NULL,
			     &bp2);
E 5
		bp = bp2;
	}
	if (bp) {
D 5
		ap = (struct iso_extended_attributes *)bp->b_un.b_addr;
E 5
I 5
		ap = (struct iso_extended_attributes *)bp->b_data;
E 5
		
		if (isonum_711(ap->version) == 1) {
D 2
			if (!isofs_tstamp_conv17(ap->ftime,&inop->inode.iso_atime))
				isofs_tstamp_conv17(ap->ctime,&inop->inode.iso_atime);
			if (!isofs_tstamp_conv17(ap->ctime,&inop->inode.iso_ctime))
E 2
I 2
			if (!cd9660_tstamp_conv17(ap->ftime,&inop->inode.iso_atime))
				cd9660_tstamp_conv17(ap->ctime,&inop->inode.iso_atime);
			if (!cd9660_tstamp_conv17(ap->ctime,&inop->inode.iso_ctime))
E 2
				inop->inode.iso_ctime = inop->inode.iso_atime;
D 2
			if (!isofs_tstamp_conv17(ap->mtime,&inop->inode.iso_mtime))
E 2
I 2
			if (!cd9660_tstamp_conv17(ap->mtime,&inop->inode.iso_mtime))
E 2
				inop->inode.iso_mtime = inop->inode.iso_ctime;
		} else
			ap = NULL;
	}
	if (!ap) {
D 2
		isofs_tstamp_conv7(isodir->date,&inop->inode.iso_ctime);
E 2
I 2
		cd9660_tstamp_conv7(isodir->date,&inop->inode.iso_ctime);
E 2
		inop->inode.iso_atime = inop->inode.iso_ctime;
		inop->inode.iso_mtime = inop->inode.iso_ctime;
	}
	if (bp2)
		brelse(bp2);
}

int
D 2
isofs_tstamp_conv7(pi,pu)
E 2
I 2
cd9660_tstamp_conv7(pi,pu)
E 2
D 5
char *pi;
struct timeval *pu;
E 5
I 5
	u_char *pi;
	struct timespec *pu;
E 5
{
	int i;
	int crtime, days;
	int y, m, d, hour, minute, second, tz;
	
	y = pi[0] + 1900;
	m = pi[1];
	d = pi[2];
	hour = pi[3];
	minute = pi[4];
	second = pi[5];
	tz = pi[6];
	
	if (y < 1970) {
D 5
		pu->tv_sec  = 0;
		pu->tv_usec = 0;
E 5
I 5
		pu->ts_sec  = 0;
		pu->ts_nsec = 0;
E 5
		return 0;
	} else {
#ifdef	ORIGINAL
		/* computes day number relative to Sept. 19th,1989 */
		/* don't even *THINK* about changing formula. It works! */
		days = 367*(y-1980)-7*(y+(m+9)/12)/4-3*((y+(m-9)/7)/100+1)/4+275*m/9+d-100;
#else
		/*
		 * Changed :-) to make it relative to Jan. 1st, 1970
		 * and to disambiguate negative division
		 */
		days = 367*(y-1960)-7*(y+(m+9)/12)/4-3*((y+(m+9)/12-1)/100+1)/4+275*m/9+d-239;
#endif
		crtime = ((((days * 24) + hour) * 60 + minute) * 60) + second;
		
		/* timezone offset is unreliable on some disks */
		if (-48 <= tz && tz <= 52)
D 3
			crtime += tz * 15 * 60;
E 3
I 3
			crtime -= tz * 15 * 60;
E 3
	}
D 5
	pu->tv_sec  = crtime;
	pu->tv_usec = 0;
E 5
I 5
	pu->ts_sec  = crtime;
	pu->ts_nsec = 0;
E 5
	return 1;
}

D 5
static unsigned
E 5
I 5
static u_int
E 5
D 2
isofs_chars2ui(begin,len)
E 2
I 2
cd9660_chars2ui(begin,len)
E 2
D 5
	unsigned char *begin;
E 5
I 5
	u_char *begin;
E 5
	int len;
{
D 5
	unsigned rc;
E 5
I 5
	u_int rc;
E 5
	
	for (rc = 0; --len >= 0;) {
		rc *= 10;
		rc += *begin++ - '0';
	}
	return rc;
}

int
D 2
isofs_tstamp_conv17(pi,pu)
E 2
I 2
cd9660_tstamp_conv17(pi,pu)
E 2
D 5
	unsigned char *pi;
	struct timeval *pu;
E 5
I 5
	u_char *pi;
	struct timespec *pu;
E 5
{
D 5
	unsigned char buf[7];
E 5
I 5
	u_char buf[7];
E 5
	
	/* year:"0001"-"9999" -> -1900  */
D 2
	buf[0] = isofs_chars2ui(pi,4) - 1900;
E 2
I 2
	buf[0] = cd9660_chars2ui(pi,4) - 1900;
E 2
	
	/* month: " 1"-"12"      -> 1 - 12 */
D 2
	buf[1] = isofs_chars2ui(pi + 4,2);
E 2
I 2
	buf[1] = cd9660_chars2ui(pi + 4,2);
E 2
	
	/* day:   " 1"-"31"      -> 1 - 31 */
D 2
	buf[2] = isofs_chars2ui(pi + 6,2);
E 2
I 2
	buf[2] = cd9660_chars2ui(pi + 6,2);
E 2
	
	/* hour:  " 0"-"23"      -> 0 - 23 */
D 2
	buf[3] = isofs_chars2ui(pi + 8,2);
E 2
I 2
	buf[3] = cd9660_chars2ui(pi + 8,2);
E 2
	
	/* minute:" 0"-"59"      -> 0 - 59 */
D 2
	buf[4] = isofs_chars2ui(pi + 10,2);
E 2
I 2
	buf[4] = cd9660_chars2ui(pi + 10,2);
E 2
	
	/* second:" 0"-"59"      -> 0 - 59 */
D 2
	buf[5] = isofs_chars2ui(pi + 12,2);
E 2
I 2
	buf[5] = cd9660_chars2ui(pi + 12,2);
E 2
	
	/* difference of GMT */
	buf[6] = pi[16];
	
D 2
	return isofs_tstamp_conv7(buf,pu);
E 2
I 2
	return cd9660_tstamp_conv7(buf,pu);
E 2
}

D 5
void
isodirino(inump,isodir,imp)
	ino_t *inump;
E 5
I 5
ino_t
isodirino(isodir, imp)
E 5
	struct iso_directory_record *isodir;
	struct iso_mnt *imp;
{
D 5
	*inump = (isonum_733(isodir->extent) + isonum_711(isodir->ext_attr_length))
		 * imp->logical_block_size;
E 5
I 5
	ino_t ino;

	ino = (isonum_733(isodir->extent) + isonum_711(isodir->ext_attr_length))
	      << imp->im_bshift;
	return (ino);
E 5
}
E 1
