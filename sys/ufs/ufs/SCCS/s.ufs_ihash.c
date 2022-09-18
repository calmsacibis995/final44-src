h36156
s 00003/00002/00122
d D 8.7 95/05/17 11:36:18 pendry 15 14
c lock the inode before putting it on the hash list
e
s 00028/00022/00096
d D 8.6 95/05/14 00:24:40 mckusick 14 13
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget;
c replace locking with calls to lock manager
e
s 00029/00039/00089
d D 8.5 95/03/20 23:46:37 mckusick 13 12
c use new list macros
e
s 00001/00001/00127
d D 8.4 93/12/30 16:12:05 mckusick 12 11
c vget now locks optionally
e
s 00024/00019/00104
d D 8.3 93/09/23 16:09:32 bostic 11 10
c changes for 4.4BSD-Lite requested by USL
e
s 00027/00032/00096
d D 8.2 93/09/05 09:44:05 bostic 10 9
c Cleanups for 4.4BSD-Lite
e
s 00002/00002/00126
d D 8.1 93/06/11 16:28:50 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00000/00107
d D 7.8 92/12/09 14:26:58 margo 8 7
c add ufs_ihashlookup that does not lock inode (for LFS cleaner)
e
s 00005/00000/00102
d D 7.7 92/12/09 14:25:13 mckusick 7 6
c debugging check for identifying holder of lock
e
s 00003/00001/00099
d D 7.6 92/11/14 23:19:34 mckusick 6 5
c just set lock bit, as it should never be preset
e
s 00033/00028/00067
d D 7.5 92/07/20 00:30:44 mckusick 5 4
c updated hashing scheme
e
s 00001/00001/00094
d D 7.4 92/03/11 21:23:41 torek 4 3
c gcc lint
e
s 00029/00019/00066
d D 7.3 91/12/16 15:28:30 mckusick 3 2
c make hash table size dynamically allocated
e
s 00005/00003/00080
d D 7.2 91/11/05 14:42:41 mckusick 2 1
c reorganization to move ufsmount ops to be vnode ops; 
c ufs_ihash returns a vnode instead of an inode
e
s 00083/00000/00000
d D 7.1 91/11/01 18:15:56 bostic 1 0
c UFS/FFS split for LFS version 1
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1982, 1986, 1989, 1991 Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 14
 * Copyright (c) 1982, 1986, 1989, 1991, 1993
E 14
I 14
 * Copyright (c) 1982, 1986, 1989, 1991, 1993, 1995
E 14
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
D 5
#include <sys/namei.h>
E 5
#include <sys/vnode.h>
I 3
#include <sys/malloc.h>
I 7
#include <sys/proc.h>
E 7
E 3

#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufs_extern.h>

D 3
#define	INOHSZ	512
#if	((INOHSZ & (INOHSZ - 1)) == 0)
#define	INOHASH(dev, ino)	(((dev) + (ino)) & (INOHSZ - 1))
#else
#define	INOHASH(dev, ino)	(((unsigned int)((dev) + (ino))) % INOHSZ)
#endif
E 3
I 3
/*
 * Structures associated with inode cacheing.
 */
D 5
union ihash {
	union	ihash *ih_head[2];
	struct	inode *ih_chain[2];
} *ihashtbl;
#define	ih_forw	ih_chain[0]
#define	ih_back	ih_chain[1]
E 3

D 3
static union ihead {
	union  ihead *ih_head[2];
	struct inode *ih_chain[2];
} ihead[INOHSZ];
E 3
I 3
u_long	ihash;			/* size of hash table - 1 */
E 5
I 5
D 13
struct inode **ihashtbl;
E 13
I 13
LIST_HEAD(ihashhead, inode) *ihashtbl;
E 13
u_long	ihash;		/* size of hash table - 1 */
E 5
D 10
#define	INOHASH(dev, ino)	(((dev) + (ino)) & ihash)
E 10
I 10
D 13
#define	INOHASH(device, inum)	(((device) + (inum)) & ihash)
E 13
I 13
#define	INOHASH(device, inum)	(&ihashtbl[((device) + (inum)) & ihash])
I 14
struct simplelock ufs_ihash_slock;
E 14
E 13
E 10
E 3

D 3

E 3
/*
 * Initialize inode hash table.
 */
void
ufs_ihashinit()
{
D 3
	register union ihead *ih;
	register int i;
E 3
I 3
D 5
	register union ihash *ihp;
	long ihashsize;
E 5
E 3

D 3
	for (ih = ihead, i = INOHSZ; --i >= 0; ++ih)
		ih->ih_head[0] = ih->ih_head[1] = ih;
E 3
I 3
D 5
	ihashsize = roundup((desiredvnodes + 1) * sizeof *ihp / 2,
		NBPG * CLSIZE);
	ihashtbl = (union ihash *)malloc((u_long)ihashsize,
	    M_UFSMNT, M_WAITOK);
	for (ihash = 1; ihash <= ihashsize / sizeof *ihp; ihash <<= 1)
D 4
		/* void */;
E 4
I 4
		continue;
E 4
	ihash = (ihash >> 1) - 1;
	for (ihp = &ihashtbl[ihash]; ihp >= ihashtbl; ihp--) {
		ihp->ih_head[0] = ihp;
		ihp->ih_head[1] = ihp;
	}
E 5
I 5
	ihashtbl = hashinit(desiredvnodes, M_UFSMNT, &ihash);
I 14
	simple_lock_init(&ufs_ihash_slock);
E 14
E 5
E 3
}

/*
D 10
 * Use the dev/ino pair to find the incore inode, and return a pointer to it.
I 8
 * If it is in core, return it, even if it is locked.
E 10
I 10
 * Use the device/inum pair to find the incore inode, and return a pointer
 * to it. If it is in core, return it, even if it is locked.
E 10
 */
struct vnode *
D 10
ufs_ihashlookup(dev, ino)
	dev_t dev;
	ino_t ino;
E 10
I 10
D 13
ufs_ihashlookup(device, inum)
	dev_t device;
E 13
I 13
ufs_ihashlookup(dev, inum)
	dev_t dev;
E 13
	ino_t inum;
E 10
{
D 11
	register struct inode **ipp, *ip;
E 11
I 11
D 14
	register struct inode *ip;
E 14
I 14
	struct inode *ip;
E 14
E 11

D 10
	ipp = &ihashtbl[INOHASH(dev, ino)];
loop:
	for (ip = *ipp; ip; ip = ip->i_next) {
		if (ino != ip->i_number || dev != ip->i_dev)
			continue;
		return (ITOV(ip));
	}
E 10
I 10
D 11
	ipp = &ihashtbl[INOHASH(device, inum)];
	for (ip = *ipp; ip; ip = ip->i_next)
E 11
I 11
D 13
	for (ip = ihashtbl[INOHASH(device, inum)];; ip = ip->i_next) {
		if (ip == NULL)
			return (NULL);
E 11
		if (inum == ip->i_number && device == ip->i_dev)
E 13
I 13
D 14
	for (ip = INOHASH(dev, inum)->lh_first; ip; ip = ip->i_hash.le_next) {
E 14
I 14
	simple_lock(&ufs_ihash_slock);
	for (ip = INOHASH(dev, inum)->lh_first; ip; ip = ip->i_hash.le_next)
E 14
		if (inum == ip->i_number && dev == ip->i_dev)
E 13
D 14
			return (ITOV(ip));
E 10
D 11
	return (NULL);
E 11
I 11
	}
D 13
	/* NOTREACHED */
E 13
I 13
	return (NULL);
E 14
I 14
			break;
	simple_unlock(&ufs_ihash_slock);

	if (ip)
		return (ITOV(ip));
	return (NULLVP);
E 14
E 13
E 11
}

/*
D 10
 * Use the dev/ino pair to find the incore inode, and return a pointer to it.
E 8
 * If it is in core, but locked, wait for it.
E 10
I 10
 * Use the device/inum pair to find the incore inode, and return a pointer
 * to it. If it is in core, but locked, wait for it.
E 10
 */
D 2
struct inode *
E 2
I 2
struct vnode *
E 2
D 10
ufs_ihashget(dev, ino)
D 5
	/* dev_t */ int dev;
E 5
I 5
	dev_t dev;
E 5
	ino_t ino;
E 10
I 10
D 13
ufs_ihashget(device, inum)
	dev_t device;
E 13
I 13
ufs_ihashget(dev, inum)
	dev_t dev;
E 13
	ino_t inum;
E 10
{
D 3
	register union ihead *ih;
E 3
I 3
D 5
	register union ihash *ihp;
E 3
	register struct inode *ip;
E 5
I 5
D 11
	register struct inode **ipp, *ip;
E 11
I 11
D 14
	register struct inode *ip;
E 14
I 14
	struct proc *p = curproc;	/* XXX */
	struct inode *ip;
E 14
E 11
E 5
I 2
	struct vnode *vp;
E 2

D 3
	ih = &ihead[INOHASH(dev, ino)];
E 3
I 3
D 5
	ihp = &ihashtbl[INOHASH(dev, ino)];
E 5
I 5
D 10
	ipp = &ihashtbl[INOHASH(dev, ino)];
E 5
E 3
loop:
D 3
	for (ip = ih->ih_chain[0]; ip != (struct inode *)ih; ip = ip->i_forw) {
E 3
I 3
D 5
	for (ip = ihp->ih_forw; ip != (struct inode *)ihp; ip = ip->i_forw) {
E 5
I 5
	for (ip = *ipp; ip; ip = ip->i_next) {
E 5
E 3
		if (ino != ip->i_number || dev != ip->i_dev)
			continue;
		if ((ip->i_flag & ILOCKED) != 0) {
			ip->i_flag |= IWANT;
			sleep((caddr_t)ip, PINOD);
			goto loop;
E 10
I 10
D 11
	ipp = &ihashtbl[INOHASH(device, inum)];
retry:	for (ip = *ipp; ip != NULL; ip = ip->i_next)
		if (inum == ip->i_number && device == ip->i_dev) {
			if (ip->i_flag & ILOCKED) {
				ip->i_flag |= IWANT;
				sleep(ip, PINOD);
				goto retry;
E 11
I 11
D 13
	for (;;)
		for (ip = ihashtbl[INOHASH(device, inum)];; ip = ip->i_next) {
			if (ip == NULL)
				return (NULL);
			if (inum == ip->i_number && device == ip->i_dev) {
				if (ip->i_flag & IN_LOCKED) {
					ip->i_flag |= IN_WANTED;
					sleep(ip, PINOD);
					break;
				}
				vp = ITOV(ip);
D 12
				if (!vget(vp))
E 12
I 12
				if (!vget(vp, 1))
E 12
					return (vp);
				break;
E 13
I 13
loop:
I 14
	simple_lock(&ufs_ihash_slock);
E 14
	for (ip = INOHASH(dev, inum)->lh_first; ip; ip = ip->i_hash.le_next) {
		if (inum == ip->i_number && dev == ip->i_dev) {
D 14
			if (ip->i_flag & IN_LOCKED) {
				ip->i_flag |= IN_WANTED;
				sleep(ip, PINOD);
				goto loop;
E 13
E 11
			}
E 14
I 13
			vp = ITOV(ip);
D 14
			if (vget(vp, 1))
E 14
I 14
			simple_lock(&vp->v_interlock);
			simple_unlock(&ufs_ihash_slock);
			if (vget(vp, LK_EXCLUSIVE | LK_INTERLOCK, p))
E 14
				goto loop;
			return (vp);
E 13
D 11
			vp = ITOV(ip);
			if (vget(vp))
				goto retry;
			return (vp);
E 11
E 10
		}
D 2
		if (vget(ITOV(ip)))
E 2
I 2
D 10
		vp = ITOV(ip);
		if (vget(vp))
E 2
			goto loop;
D 2
		return (ip);
E 2
I 2
		return (vp);
E 2
	}
E 10
D 11
	return (NULL);
E 11
I 11
D 13
	/* NOTREACHED */
E 13
I 13
	}
I 14
	simple_unlock(&ufs_ihash_slock);
E 14
	return (NULL);
E 13
E 11
}

/*
D 13
 * Insert the inode into the hash table, and return it locked.
E 13
I 13
* Insert the inode into the hash table, and return it locked.
E 13
 */
void
ufs_ihashins(ip)
	struct inode *ip;
{
I 14
	struct proc *p = curproc;		/* XXX */
E 14
D 3
	insque(ip, &ihead[INOHASH(ip->i_dev, ip->i_number)]);
E 3
I 3
D 5
	insque(ip, &ihashtbl[INOHASH(ip->i_dev, ip->i_number)]);
E 5
I 5
D 13
	struct inode **ipp, *iq;
E 13
I 13
	struct ihashhead *ipp;
E 13

I 15
	/* lock the inode, then put it on the appropriate hash list */
	lockmgr(&ip->i_lock, LK_EXCLUSIVE, (struct simplelock *)0, p);

E 15
I 14
	simple_lock(&ufs_ihash_slock);
E 14
D 13
	ipp = &ihashtbl[INOHASH(ip->i_dev, ip->i_number)];
	if (iq = *ipp)
		iq->i_prev = &ip->i_next;
	ip->i_next = iq;
	ip->i_prev = ipp;
	*ipp = ip;
E 13
I 13
	ipp = INOHASH(ip->i_dev, ip->i_number);
	LIST_INSERT_HEAD(ipp, ip, i_hash);
E 13
E 5
E 3
D 6
	ILOCK(ip);
E 6
I 6
D 11
	if ((ip->i_flag & ILOCKED) != 0)
E 11
I 11
D 14
	if (ip->i_flag & IN_LOCKED)
E 11
		panic("ufs_ihashins: already locked");
I 7
	if (curproc)
		ip->i_lockholder = curproc->p_pid;
	else
		ip->i_lockholder = -1;
E 7
D 11
	ip->i_flag |= ILOCKED;
E 11
I 11
	ip->i_flag |= IN_LOCKED;
E 14
I 14
	simple_unlock(&ufs_ihash_slock);
D 15

	lockmgr(&ip->i_lock, LK_EXCLUSIVE, (struct simplelock *)0, p);
E 15
E 14
E 11
E 6
I 5
}

/*
 * Remove the inode from the hash table.
 */
void
ufs_ihashrem(ip)
D 14
	register struct inode *ip;
E 14
I 14
	struct inode *ip;
E 14
{
D 14
	register struct inode *iq;
E 14
I 14
	struct inode *iq;
E 14

I 14
	simple_lock(&ufs_ihash_slock);
E 14
D 13
	if (iq = ip->i_next)
		iq->i_prev = ip->i_prev;
	*ip->i_prev = iq;
E 13
I 13
	LIST_REMOVE(ip, i_hash);
E 13
#ifdef DIAGNOSTIC
D 13
	ip->i_next = NULL;
	ip->i_prev = NULL;
E 13
I 13
	ip->i_hash.le_next = NULL;
	ip->i_hash.le_prev = NULL;
E 13
#endif
I 14
	simple_unlock(&ufs_ihash_slock);
E 14
E 5
}
E 1
