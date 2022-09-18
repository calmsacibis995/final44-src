h43815
s 00004/00001/00458
d D 8.7 95/05/27 22:22:25 mckusick 7 6
c read-only checking must be done by the filesystem layers
e
s 00012/00011/00447
d D 8.6 95/05/14 00:35:34 mckusick 6 5
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00060/00045/00398
d D 8.5 94/12/05 21:54:40 mckusick 5 4
c update from mycroft
e
s 00029/00025/00414
d D 8.4 94/07/13 16:16:14 mckusick 4 3
c update for 4.4BSD-Lite (from mycroft)
e
s 00001/00001/00438
d D 8.3 94/06/14 11:52:15 mkm 3 2
c formatting
e
s 00004/00004/00435
d D 8.2 94/01/23 23:50:45 mckusick 2 1
c isofs => cd9660 naming convention
e
s 00439/00000/00000
d D 8.1 94/01/21 18:28:56 mckusick 1 0
c from Mike Hibler
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1989, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley
 * by Pace Willisson (pace@blitz.com).  The Rock Ridge Extension
 * Support code is derived from software contributed to Berkeley
 * by Atsushi Murai (amurai@spec.co.jp).
 *
 * %sccs.include.redist.c%
 *
 *	from: @(#)ufs_lookup.c	7.33 (Berkeley) 5/19/91
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/namei.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/vnode.h>
#include <sys/mount.h>

#include <isofs/cd9660/iso.h>
D 2
#include <isofs/cd9660/isofs_node.h>
E 2
I 2
#include <isofs/cd9660/cd9660_node.h>
E 2
#include <isofs/cd9660/iso_rrip.h>
D 2
#include <isofs/cd9660/isofs_rrip.h>
E 2
I 2
#include <isofs/cd9660/cd9660_rrip.h>
E 2

struct	nchstats iso_nchstats;

/*
 * Convert a component of a pathname into a pointer to a locked inode.
 * This is a very central and rather complicated routine.
 * If the file system is not maintained in a strict tree hierarchy,
 * this can result in a deadlock situation (see comments in code below).
 *
 * The flag argument is LOOKUP, CREATE, RENAME, or DELETE depending on
 * whether the name is to be looked up, created, renamed, or deleted.
 * When CREATE, RENAME, or DELETE is specified, information usable in
 * creating, renaming, or deleting a directory entry may be calculated.
 * If flag has LOCKPARENT or'ed into it and the target of the pathname
 * exists, lookup returns both the target and its parent directory locked.
 * When creating or renaming and LOCKPARENT is specified, the target may
 * not be ".".  When deleting and LOCKPARENT is specified, the target may
 * be "."., but the caller must check to ensure it does an vrele and iput
 * instead of two iputs.
 *
 * Overall outline of ufs_lookup:
 *
 *	check accessibility of directory
 *	look for name in cache, if found, then if at end of path
 *	  and deleting or creating, drop it, else return name
 *	search for name in directory, to found or notfound
 * notfound:
 *	if creating, return locked directory, leaving info on available slots
 *	else return error
 * found:
 *	if at end of path and deleting, return information to allow delete
 *	if at end of path and rewriting (RENAME and LOCKPARENT), lock target
 *	  inode and return info to allow rewrite
 *	if not at end, add name to cache; if at end and neither creating
 *	  nor deleting, add name to cache
 *
 * NOTE: (LOOKUP | LOCKPARENT) currently returns the parent inode unlocked.
 */
D 2
isofs_lookup(ap)
E 2
I 2
cd9660_lookup(ap)
E 2
	struct vop_lookup_args /* {
		struct vnode *a_dvp;
		struct vnode **a_vpp;
		struct componentname *a_cnp;
	} */ *ap;
{
	register struct vnode *vdp;	/* vnode for directory being searched */
	register struct iso_node *dp;	/* inode for directory being searched */
	register struct iso_mnt *imp;	/* file system that directory is in */
	struct buf *bp;			/* a buffer of directory entries */
	struct iso_directory_record *ep;/* the current directory entry */
	int entryoffsetinblock;		/* offset of ep in bp's buffer */
	int saveoffset;			/* offset of last directory entry in dir */
	int numdirpasses;		/* strategy for directory search */
	doff_t endsearch;		/* offset to end directory search */
D 4
	struct iso_node *pdp;		/* saved dp during symlink work */
	struct iso_node *tdp;		/* returned by iget */
E 4
I 4
	struct vnode *pdp;		/* saved dp during symlink work */
	struct vnode *tdp;		/* returned by cd9660_vget_internal */
I 5
	u_long bmask;			/* block offset mask */
E 5
E 4
	int lockparent;			/* 1 => lockparent flag is set */
	int wantparent;			/* 1 => wantparent or lockparent flag */
	int error;
	ino_t ino = 0;
	int reclen;
	u_short namelen;
	char altname[NAME_MAX];
	int res;
	int assoc, len;
	char *name;
	struct vnode **vpp = ap->a_vpp;
	struct componentname *cnp = ap->a_cnp;
	struct ucred *cred = cnp->cn_cred;
	int flags = cnp->cn_flags;
	int nameiop = cnp->cn_nameiop;
I 6
	struct proc *p = cnp->cn_proc;
E 6
	
	bp = NULL;
	*vpp = NULL;
	vdp = ap->a_dvp;
	dp = VTOI(vdp);
	imp = dp->i_mnt;
	lockparent = flags & LOCKPARENT;
	wantparent = flags & (LOCKPARENT|WANTPARENT);
	
	/*
	 * Check accessiblity of directory.
	 */
	if (vdp->v_type != VDIR)
D 3
	    return (ENOTDIR);
E 3
I 3
		return (ENOTDIR);
E 3
	if (error = VOP_ACCESS(vdp, VEXEC, cred, cnp->cn_proc))
		return (error);
I 7
	if ((flags & ISLASTCN) && (vdp->v_mount->mnt_flag & MNT_RDONLY) &&
	    (cnp->cn_nameiop == DELETE || cnp->cn_nameiop == RENAME))
		return (EROFS);
E 7
	
	/*
	 * We now have a segment name to search for, and a directory to search.
	 *
	 * Before tediously performing a linear scan of the directory,
	 * check the name cache to see if the directory/name pair
	 * we are looking for is known already.
	 */
	if (error = cache_lookup(vdp, vpp, cnp)) {
		int vpid;	/* capability number of vnode */

		if (error == ENOENT)
			return (error);
#ifdef PARANOID
		if ((vdp->v_flag & VROOT) && (flags & ISDOTDOT))
D 5
			panic("ufs_lookup: .. through root");
E 5
I 5
			panic("cd9660_lookup: .. through root");
E 5
#endif
		/*
		 * Get the next vnode in the path.
		 * See comment below starting `Step through' for
		 * an explaination of the locking protocol.
		 */
D 4
		pdp = dp;
E 4
I 4
		pdp = vdp;
E 4
		dp = VTOI(*vpp);
		vdp = *vpp;
		vpid = vdp->v_id;
D 4
		if (pdp == dp) {
E 4
I 4
		if (pdp == vdp) {
E 4
			VREF(vdp);
			error = 0;
		} else if (flags & ISDOTDOT) {
D 4
			ISO_IUNLOCK(pdp);
E 4
I 4
D 6
			VOP_UNLOCK(pdp);
E 4
			error = vget(vdp, 1);
E 6
I 6
			VOP_UNLOCK(pdp, 0, p);
			error = vget(vdp, LK_EXCLUSIVE, p);
E 6
			if (!error && lockparent && (flags & ISLASTCN))
D 4
				ISO_ILOCK(pdp);
E 4
I 4
D 6
				error = VOP_LOCK(pdp);
E 6
I 6
				error = vn_lock(pdp, LK_EXCLUSIVE, p);
E 6
E 4
		} else {
D 6
			error = vget(vdp, 1);
E 6
I 6
			error = vget(vdp, LK_EXCLUSIVE, p);
E 6
			if (!lockparent || error || !(flags & ISLASTCN))
D 4
				ISO_IUNLOCK(pdp);
E 4
I 4
D 6
				VOP_UNLOCK(pdp);
E 6
I 6
				VOP_UNLOCK(pdp, 0, p);
E 6
E 4
		}
		/*
		 * Check that the capability number did not change
		 * while we were waiting for the lock.
		 */
		if (!error) {
			if (vpid == vdp->v_id)
				return (0);
D 4
			iso_iput(dp);
			if (lockparent && pdp != dp && (flags & ISLASTCN))
				ISO_IUNLOCK(pdp);
E 4
I 4
			vput(vdp);
			if (lockparent && pdp != vdp && (flags & ISLASTCN))
D 6
				VOP_UNLOCK(pdp);
E 6
I 6
				VOP_UNLOCK(pdp, 0, p);
E 6
E 4
		}
D 4
		ISO_ILOCK(pdp);
		dp = pdp;
		vdp = ITOV(dp);
E 4
I 4
D 6
		if (error = VOP_LOCK(pdp))
E 6
I 6
		if (error = vn_lock(pdp, LK_EXCLUSIVE, p))
E 6
			return (error);
		vdp = pdp;
		dp = VTOI(pdp);
E 4
		*vpp = NULL;
	}
	
	len = cnp->cn_namelen;
	name = cnp->cn_nameptr;
	/*
	 * A leading `=' means, we are looking for an associated file
	 */
	if (assoc = (imp->iso_ftype != ISO_FTYPE_RRIP && *name == ASSOCCHAR)) {
		len--;
		name++;
	}
	
	/*
	 * If there is cached information on a previous search of
	 * this directory, pick up where we last left off.
	 * We cache only lookups as these are the most common
	 * and have the greatest payoff. Caching CREATE has little
	 * benefit as it usually must search the entire directory
	 * to determine that the entry does not exist. Caching the
	 * location of the last DELETE or RENAME has not reduced
	 * profiling time and hence has been removed in the interest
	 * of simplicity.
	 */
I 5
	bmask = imp->im_bmask;
E 5
	if (nameiop != LOOKUP || dp->i_diroff == 0 ||
	    dp->i_diroff > dp->i_size) {
		entryoffsetinblock = 0;
		dp->i_offset = 0;
		numdirpasses = 1;
	} else {
		dp->i_offset = dp->i_diroff;
D 5
		entryoffsetinblock = iso_blkoff(imp, dp->i_offset);
		if (entryoffsetinblock != 0) {
			if (error = iso_blkatoff(dp, dp->i_offset, &bp))
E 5
I 5
		if ((entryoffsetinblock = dp->i_offset & bmask) &&
		    (error = VOP_BLKATOFF(vdp, (off_t)dp->i_offset, NULL, &bp)))
E 5
				return (error);
D 5
		}
E 5
		numdirpasses = 2;
		iso_nchstats.ncs_2passes++;
	}
D 5
	endsearch = roundup(dp->i_size, imp->logical_block_size);
E 5
I 5
	endsearch = dp->i_size;
E 5
	
searchloop:
	while (dp->i_offset < endsearch) {
		/*
		 * If offset is on a block boundary,
		 * read the next directory block.
		 * Release previous if it exists.
		 */
D 5
		if (iso_blkoff(imp, dp->i_offset) == 0) {
E 5
I 5
		if ((dp->i_offset & bmask) == 0) {
E 5
			if (bp != NULL)
				brelse(bp);
D 5
			if (error = iso_blkatoff(dp, dp->i_offset, &bp))
E 5
I 5
			if (error =
			    VOP_BLKATOFF(vdp, (off_t)dp->i_offset, NULL, &bp))
E 5
				return (error);
			entryoffsetinblock = 0;
		}
		/*
		 * Get pointer to next entry.
		 */
		ep = (struct iso_directory_record *)
D 5
			(bp->b_un.b_addr + entryoffsetinblock);
E 5
I 5
			((char *)bp->b_data + entryoffsetinblock);
E 5
		
D 5
		reclen = isonum_711 (ep->length);
E 5
I 5
		reclen = isonum_711(ep->length);
E 5
		if (reclen == 0) {
			/* skip to next block, if any */
			dp->i_offset =
D 5
				roundup(dp->i_offset, imp->logical_block_size);
E 5
I 5
			    (dp->i_offset & ~bmask) + imp->logical_block_size;
E 5
			continue;
		}
		
		if (reclen < ISO_DIRECTORY_RECORD_SIZE)
			/* illegal entry, stop */
			break;
		
		if (entryoffsetinblock + reclen > imp->logical_block_size)
			/* entries are not allowed to cross boundaries */
			break;
		
D 5
		/*
		 * Check for a name match.
		 */
E 5
		namelen = isonum_711(ep->name_len);
		
		if (reclen < ISO_DIRECTORY_RECORD_SIZE + namelen)
			/* illegal entry, stop */
			break;
		
I 5
		/*
		 * Check for a name match.
		 */
E 5
		switch (imp->iso_ftype) {
		default:
			if ((!(isonum_711(ep->flags)&4)) == !assoc) {
				if ((len == 1
				     && *name == '.')
				    || (flags & ISDOTDOT)) {
					if (namelen == 1
					    && ep->name[0] == ((flags & ISDOTDOT) ? 1 : 0)) {
						/*
						 * Save directory entry's inode number and
D 5
						 * reclen in ndp->ni_ufs area, and release
						 * directory buffer.
E 5
I 5
						 * release directory buffer.
E 5
						 */
D 5
						isodirino(&dp->i_ino,ep,imp);
E 5
I 5
						dp->i_ino = isodirino(ep, imp);
E 5
						goto found;
					}
					if (namelen != 1
					    || ep->name[0] != 0)
						goto notfound;
				} else if (!(res = isofncmp(name,len,
							    ep->name,namelen))) {
					if (isonum_711(ep->flags)&2)
D 5
						isodirino(&ino,ep,imp);
E 5
I 5
						ino = isodirino(ep, imp);
E 5
					else
						ino = dbtob(bp->b_blkno)
							+ entryoffsetinblock;
					saveoffset = dp->i_offset;
				} else if (ino)
					goto foundino;
#ifdef	NOSORTBUG	/* On some CDs directory entries are not sorted correctly */
				else if (res < 0)
					goto notfound;
				else if (res > 0 && numdirpasses == 2)
					numdirpasses++;
#endif
			}
			break;
		case ISO_FTYPE_RRIP:
			if (isonum_711(ep->flags)&2)
D 5
				isodirino(&ino,ep,imp);
E 5
I 5
				ino = isodirino(ep, imp);
E 5
			else
				ino = dbtob(bp->b_blkno) + entryoffsetinblock;
			dp->i_ino = ino;
D 2
			isofs_rrip_getname(ep,altname,&namelen,&dp->i_ino,imp);
E 2
I 2
			cd9660_rrip_getname(ep,altname,&namelen,&dp->i_ino,imp);
E 2
			if (namelen == cnp->cn_namelen
			    && !bcmp(name,altname,namelen))
				goto found;
			ino = 0;
			break;
		}
		dp->i_offset += reclen;
		entryoffsetinblock += reclen;
	}
	if (ino) {
foundino:
		dp->i_ino = ino;
		if (saveoffset != dp->i_offset) {
D 5
			if (iso_lblkno(imp,dp->i_offset)
			    != iso_lblkno(imp,saveoffset)) {
E 5
I 5
			if (lblkno(imp, dp->i_offset) !=
			    lblkno(imp, saveoffset)) {
E 5
				if (bp != NULL)
					brelse(bp);
D 5
				if (error = iso_blkatoff(dp, saveoffset, &bp))
E 5
I 5
				if (error = VOP_BLKATOFF(vdp,
				    (off_t)saveoffset, NULL, &bp))
E 5
					return (error);
			}
D 5
			ep = (struct iso_directory_record *)(bp->b_un.b_addr
							     + iso_blkoff(imp,saveoffset));
E 5
I 5
			entryoffsetinblock = saveoffset & bmask;
			ep = (struct iso_directory_record *)
				((char *)bp->b_data + entryoffsetinblock);
E 5
			dp->i_offset = saveoffset;
		}
		goto found;
	}
notfound:
	/*
	 * If we started in the middle of the directory and failed
	 * to find our target, we must check the beginning as well.
	 */
	if (numdirpasses == 2) {
		numdirpasses--;
		dp->i_offset = 0;
		endsearch = dp->i_diroff;
		goto searchloop;
	}
	if (bp != NULL)
		brelse(bp);
I 5

E 5
	/*
	 * Insert name into cache (as non-existent) if appropriate.
	 */
	if (cnp->cn_flags & MAKEENTRY)
		cache_enter(vdp, *vpp, cnp);
	if (nameiop == CREATE || nameiop == RENAME)
D 7
		return (EJUSTRETURN);
E 7
I 7
		return (EROFS);
E 7
	return (ENOENT);
	
found:
	if (numdirpasses == 2)
		iso_nchstats.ncs_pass2++;
D 5
	if (bp != NULL)
		brelse(bp);
E 5
	
	/*
	 * Found component in pathname.
	 * If the final component of path name, save information
	 * in the cache as to where the entry was found.
	 */
	if ((flags & ISLASTCN) && nameiop == LOOKUP)
		dp->i_diroff = dp->i_offset;
	
	/*
	 * Step through the translation in the name.  We do not `iput' the
	 * directory because we may need it again if a symbolic link
	 * is relative to the current directory.  Instead we save it
	 * unlocked as "pdp".  We must get the target inode before unlocking
	 * the directory to insure that the inode will not be removed
	 * before we get it.  We prevent deadlock by always fetching
	 * inodes from the root, moving down the directory tree. Thus
	 * when following backward pointers ".." we must unlock the
	 * parent directory before getting the requested directory.
	 * There is a potential race condition here if both the current
	 * and parent directories are removed before the `iget' for the
	 * inode associated with ".." returns.  We hope that this occurs
	 * infrequently since we cannot avoid this race condition without
	 * implementing a sophisticated deadlock detection algorithm.
	 * Note also that this simple deadlock detection scheme will not
	 * work if the file system has any hard links other than ".."
	 * that point backwards in the directory structure.
	 */
D 4
	pdp = dp;
E 4
I 4
	pdp = vdp;
E 4
	/*
	 * If ino is different from dp->i_ino,
	 * it's a relocated directory.
	 */
	if (flags & ISDOTDOT) {
D 4
		ISO_IUNLOCK(pdp);	/* race to get the inode */
		if (error = iso_iget(dp,dp->i_ino,
				     dp->i_ino != ino,
				     &tdp,ep)) {
			ISO_ILOCK(pdp);
E 4
I 4
D 6
		VOP_UNLOCK(pdp);	/* race to get the inode */
E 6
I 6
		VOP_UNLOCK(pdp, 0, p);	/* race to get the inode */
E 6
D 5
		if (error = cd9660_vget_internal(vdp->v_mount, dp->i_ino, &tdp,
						 dp->i_ino != ino, ep)) {
E 5
I 5
		error = cd9660_vget_internal(vdp->v_mount, dp->i_ino, &tdp,
					     dp->i_ino != ino, ep);
		brelse(bp);
		if (error) {
E 5
D 6
			VOP_LOCK(pdp);
E 6
I 6
			vn_lock(pdp, LK_EXCLUSIVE | LK_RETRY, p);
E 6
E 4
			return (error);
		}
D 4
		if (lockparent && (flags & ISLASTCN))
			ISO_ILOCK(pdp);
		*vpp = ITOV(tdp);
E 4
I 4
		if (lockparent && (flags & ISLASTCN) &&
D 6
		    (error = VOP_LOCK(pdp))) {
E 6
I 6
		    (error = vn_lock(pdp, LK_EXCLUSIVE, p))) {
E 6
			vput(tdp);
			return (error);
		}
		*vpp = tdp;
E 4
	} else if (dp->i_number == dp->i_ino) {
I 5
		brelse(bp);
E 5
		VREF(vdp);	/* we want ourself, ie "." */
		*vpp = vdp;
	} else {
D 4
		if (error = iso_iget(dp,dp->i_ino,dp->i_ino!=ino,&tdp,ep))
E 4
I 4
D 5
		if (error = cd9660_vget_internal(vdp->v_mount, dp->i_ino, &tdp,
						 dp->i_ino != ino, ep))
E 5
I 5
		error = cd9660_vget_internal(vdp->v_mount, dp->i_ino, &tdp,
					     dp->i_ino != ino, ep);
		brelse(bp);
		if (error)
E 5
E 4
			return (error);
		if (!lockparent || !(flags & ISLASTCN))
D 4
			ISO_IUNLOCK(pdp);
		*vpp = ITOV(tdp);
E 4
I 4
D 6
			VOP_UNLOCK(pdp);
E 6
I 6
			VOP_UNLOCK(pdp, 0, p);
E 6
		*vpp = tdp;
E 4
	}
	
	/*
	 * Insert name into cache if appropriate.
	 */
	if (cnp->cn_flags & MAKEENTRY)
		cache_enter(vdp, *vpp, cnp);
	return (0);
}

/*
D 5
 * Return buffer with contents of block "offset"
 * from the beginning of directory "ip".  If "res"
 * is non-zero, fill it in with a pointer to the
E 5
I 5
 * Return buffer with the contents of block "offset" from the beginning of
 * directory "ip".  If "res" is non-zero, fill it in with a pointer to the
E 5
 * remaining space in the directory.
 */
D 5
iso_blkatoff(ip, offset, bpp)
	struct iso_node *ip;
	doff_t offset;
	struct buf **bpp;
E 5
I 5
int
cd9660_blkatoff(ap)
	struct vop_blkatoff_args /* {
		struct vnode *a_vp;
		off_t a_offset;
		char **a_res;
		struct buf **a_bpp;
	} */ *ap;
E 5
{
D 5
	register struct iso_mnt *imp = ip->i_mnt;
	daddr_t lbn = iso_lblkno(imp,offset);
	int bsize = iso_blksize(imp,ip,lbn);
E 5
I 5
	struct iso_node *ip;
	register struct iso_mnt *imp;
E 5
	struct buf *bp;
D 5
	int error;
E 5
I 5
	daddr_t lbn;
	int bsize, error;

	ip = VTOI(ap->a_vp);
	imp = ip->i_mnt;
	lbn = lblkno(imp, ap->a_offset);
	bsize = blksize(imp, ip, lbn);
E 5
	
D 5
	if (error = bread(ITOV(ip),lbn,bsize,NOCRED,&bp)) {
E 5
I 5
	if (error = bread(ap->a_vp, lbn, bsize, NOCRED, &bp)) {
E 5
		brelse(bp);
D 5
		*bpp = 0;
E 5
I 5
		*ap->a_bpp = NULL;
E 5
		return (error);
	}
D 5
	*bpp = bp;
	
E 5
I 5
	if (ap->a_res)
		*ap->a_res = (char *)bp->b_data + blkoff(imp, ap->a_offset);
	*ap->a_bpp = bp;
E 5
	return (0);
}
E 1
