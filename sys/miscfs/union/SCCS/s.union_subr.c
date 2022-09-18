h23877
s 00011/00003/01049
d D 8.20 95/05/20 07:30:04 pendry 31 30
c lock vnode while computing dircache
e
s 00018/00015/01034
d D 8.19 95/05/14 00:48:39 mckusick 30 29
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00015/00011/01034
d D 8.18 95/05/11 16:05:27 pendry 29 28
c messing around with hashing and locking (checked in by mckusick for pendry)
e
s 00003/00003/01042
d D 8.17 95/03/11 11:09:56 mckusick 28 27
c VOP_CLOSE takes four arguments (from mycroft)
e
s 00096/00012/00949
d D 8.16 94/12/10 13:03:07 pendry 27 26
c fix readdir for no-linear stacks
e
s 00004/00005/00957
d D 8.15 94/12/02 06:11:24 pendry 26 25
c fix dangling pointer
e
s 00023/00000/00939
d D 8.14 94/09/29 08:15:08 pendry 25 24
c ensure unlink/rmdir create whiteouts when appropriate
e
s 00017/00013/00922
d D 8.13 94/08/31 05:53:04 pendry 24 23
c LEASE_CHECK -> VOP_LEASE
c fix component length when creating shadow directories/whiteouts.
c *** CHANGED *** 94/08/31 05:55:57 pendry
c LEASE_CHECK -> VOP_LEASE.
e
s 00102/00037/00833
d D 8.12 94/07/28 03:39:27 pendry 23 22
c changes for whiteouts and union filesystem
e
s 00006/00001/00864
d D 8.11 94/06/17 09:43:17 pendry 22 21
c keep track of parent union node, so allowing .. to refer to
e
s 00007/00003/00858
d D 8.10 94/06/16 09:15:54 pendry 21 20
c keep track of deleted upper layer objects
e
s 00002/00001/00859
d D 8.9 94/05/17 19:29:08 pendry 20 19
c don't reference lower layer root vnode if it doesn't exist
e
s 00078/00007/00782
d D 8.8 94/05/17 19:27:43 pendry 19 18
c abstract the copyup function
e
s 00046/00000/00743
d D 8.7 94/05/07 13:18:05 pendry 18 17
c keep track of vnode size changes.
e
s 00032/00022/00711
d D 8.6 94/04/28 06:33:48 pendry 17 16
c keep track of whether the union node is cached or not.
c this allows anonymous union_node's to be handled correctly.
c (an anon node is one with neither an upper or lower layer and comes
c into being when an existing upper-layer file is deleted.)
e
s 00015/00000/00718
d D 8.5 94/04/24 08:46:47 pendry 16 15
c detect root node and set VROOT flag
e
s 00004/00001/00714
d D 8.4 94/02/17 16:35:57 pendry 15 14
c implement new access policy
c fixup locking for UNMNT_BELOW.
e
s 00025/00041/00690
d D 8.3 94/02/10 23:26:58 pendry 14 13
c fix reference counts in union_vn_create and union_mkshadow
e
s 00001/00001/00730
d D 8.2 94/02/10 18:52:28 pendry 13 12
c use miscfs include path
e
s 00000/00000/00731
d D 8.1 94/02/10 18:50:24 pendry 12 11
c up to v8
e
s 00181/00051/00550
d D 2.2 94/02/10 18:38:11 pendry 11 10
c cleanup & lint
e
s 00131/00053/00470
d D 2.1 94/02/10 14:08:23 pendry 10 9
c new locking scheme
e
s 00025/00008/00498
d D 1.9 94/02/08 16:16:01 pendry 9 8
c checkpoint
e
s 00018/00002/00488
d D 1.8 94/02/07 21:35:15 pendry 8 7
c checkpoint
e
s 00057/00009/00433
d D 1.7 94/02/07 16:13:11 pendry 7 6
c checkpoint
e
s 00090/00005/00352
d D 1.6 94/02/04 17:50:31 pendry 6 5
c checkpoint
e
s 00158/00000/00199
d D 1.5 94/02/03 20:07:55 pendry 5 4
c checkpoint
e
s 00026/00014/00173
d D 1.4 94/02/03 12:25:30 pendry 4 3
c checkpoint
e
s 00034/00007/00153
d D 1.3 94/02/01 20:45:32 pendry 3 2
c checkpoint
e
s 00000/00000/00160
d D 1.2 94/02/01 17:11:09 pendry 2 1
c checkpoint
e
s 00160/00000/00000
d D 1.1 94/01/28 09:42:43 pendry 1 0
c date and time created 94/01/28 09:42:43 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1994 Jan-Simon Pendry
 * Copyright (c) 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/vnode.h>
#include <sys/namei.h>
#include <sys/malloc.h>
I 5
#include <sys/file.h>
I 6
#include <sys/filedesc.h>
I 11
#include <sys/queue.h>
I 16
#include <sys/mount.h>
I 25
#include <sys/stat.h>
E 25
I 18
#include <vm/vm.h>		/* for vnode_pager_setsize */
E 18
E 16
E 11
E 6
E 5
D 13
#include "union.h" /*<miscfs/union/union.h>*/
E 13
I 13
#include <miscfs/union/union.h>
E 13

I 4
#ifdef DIAGNOSTIC
#include <sys/proc.h>
#endif

E 4
D 11
static struct union_node *unhead;
static int unvplock;
E 11
I 11
/* must be power of two, otherwise change UNION_HASH() */
#define NHASH 32
E 11

I 11
/* unsigned int ... */
#define UNION_HASH(u, l) \
	(((((unsigned long) (u)) + ((unsigned long) l)) >> 8) & (NHASH-1))

static LIST_HEAD(unhead, union_node) unhead[NHASH];
static int unvplock[NHASH];

E 11
int
union_init()
{
I 11
	int i;
E 11

D 11
	unhead = 0;
	unvplock = 0;
E 11
I 11
	for (i = 0; i < NHASH; i++)
		LIST_INIT(&unhead[i]);
	bzero((caddr_t) unvplock, sizeof(unvplock));
E 11
}

I 11
static int
union_list_lock(ix)
	int ix;
{

	if (unvplock[ix] & UN_LOCKED) {
		unvplock[ix] |= UN_WANT;
		sleep((caddr_t) &unvplock[ix], PINOD);
		return (1);
	}

	unvplock[ix] |= UN_LOCKED;

	return (0);
}

E 11
I 10
static void
D 11
union_remlist(un)
E 11
I 11
union_list_unlock(ix)
	int ix;
{

	unvplock[ix] &= ~UN_LOCKED;

	if (unvplock[ix] & UN_WANT) {
		unvplock[ix] &= ~UN_WANT;
		wakeup((caddr_t) &unvplock[ix]);
	}
}

void
union_updatevp(un, uppervp, lowervp)
E 11
	struct union_node *un;
I 11
	struct vnode *uppervp;
	struct vnode *lowervp;
E 11
{
D 11
	struct union_node **unpp;
E 11
I 11
	int ohash = UNION_HASH(un->un_uppervp, un->un_lowervp);
	int nhash = UNION_HASH(uppervp, lowervp);
I 17
	int docache = (lowervp != NULLVP || uppervp != NULLVP);
I 29
	int lhash, hhash, uhash;
E 29
E 17
E 11

D 11
	for (unpp = &unhead; *unpp != 0; unpp = &(*unpp)->un_next) {
		if (*unpp == un) {
			*unpp = un->un_next;
			break;
E 11
I 11
D 17
	if (ohash != nhash) {
		/*
		 * Ensure locking is ordered from lower to higher
		 * to avoid deadlocks.
		 */
		if (nhash < ohash) {
			int t = ohash;
			ohash = nhash;
			nhash = t;
E 11
		}
E 17
I 17
	/*
	 * Ensure locking is ordered from lower to higher
	 * to avoid deadlocks.
	 */
	if (nhash < ohash) {
D 29
		int t = ohash;
		ohash = nhash;
		nhash = t;
E 29
I 29
		lhash = nhash;
		uhash = ohash;
	} else {
		lhash = ohash;
		uhash = nhash;
E 29
	}
E 17
I 11

I 17
D 29
	if (ohash != nhash)
E 17
		while (union_list_lock(ohash))
E 29
I 29
	if (lhash != uhash)
		while (union_list_lock(lhash))
E 29
			continue;

D 17
		while (union_list_lock(nhash))
			continue;
E 17
I 17
D 29
	while (union_list_lock(nhash))
E 29
I 29
	while (union_list_lock(uhash))
E 29
		continue;
E 17

D 17
		LIST_REMOVE(un, un_cache);
		union_list_unlock(ohash);
	} else {	
		while (union_list_lock(nhash))
			continue;
E 17
I 17
	if (ohash != nhash || !docache) {
		if (un->un_flags & UN_CACHED) {
D 21
			LIST_REMOVE(un, un_cache);
E 21
			un->un_flags &= ~UN_CACHED;
I 21
			LIST_REMOVE(un, un_cache);
E 21
		}
E 17
E 11
	}
I 11

I 17
	if (ohash != nhash)
		union_list_unlock(ohash);

E 17
	if (un->un_lowervp != lowervp) {
		if (un->un_lowervp) {
			vrele(un->un_lowervp);
			if (un->un_path) {
				free(un->un_path, M_TEMP);
				un->un_path = 0;
			}
			if (un->un_dirvp) {
				vrele(un->un_dirvp);
				un->un_dirvp = NULLVP;
			}
		}
		un->un_lowervp = lowervp;
I 18
		un->un_lowersz = VNOVAL;
E 18
	}

	if (un->un_uppervp != uppervp) {
		if (un->un_uppervp)
			vrele(un->un_uppervp);

		un->un_uppervp = uppervp;
I 18
		un->un_uppersz = VNOVAL;
E 18
	}

D 17
	if (ohash != nhash)
E 17
I 17
	if (docache && (ohash != nhash)) {
E 17
		LIST_INSERT_HEAD(&unhead[nhash], un, un_cache);
I 17
		un->un_flags |= UN_CACHED;
	}
E 17

	union_list_unlock(nhash);
E 11
}

I 11
void
union_newlower(un, lowervp)
	struct union_node *un;
	struct vnode *lowervp;
{

	union_updatevp(un, un->un_uppervp, lowervp);
}

void
union_newupper(un, uppervp)
	struct union_node *un;
	struct vnode *uppervp;
{

	union_updatevp(un, uppervp, un->un_lowervp);
}

E 11
E 10
/*
I 18
 * Keep track of size changes in the underlying vnodes.
 * If the size changes, then callback to the vm layer
 * giving priority to the upper layer size.
 */
void
union_newsize(vp, uppersz, lowersz)
	struct vnode *vp;
	off_t uppersz, lowersz;
{
	struct union_node *un;
	off_t sz;

	/* only interested in regular files */
	if (vp->v_type != VREG)
		return;

	un = VTOUNION(vp);
	sz = VNOVAL;

	if ((uppersz != VNOVAL) && (un->un_uppersz != uppersz)) {
		un->un_uppersz = uppersz;
		if (sz == VNOVAL)
			sz = un->un_uppersz;
	}

	if ((lowersz != VNOVAL) && (un->un_lowersz != lowersz)) {
		un->un_lowersz = lowersz;
		if (sz == VNOVAL)
			sz = un->un_lowersz;
	}

	if (sz != VNOVAL) {
#ifdef UNION_DIAGNOSTIC
		printf("union: %s size now %ld\n",
			uppersz != VNOVAL ? "upper" : "lower", (long) sz);
#endif
		vnode_pager_setsize(vp, sz);
	}
}

/*
E 18
 * allocate a union_node/vnode pair.  the vnode is
D 3
 * referenced and locked.
E 3
I 3
 * referenced and locked.  the new vnode is returned
 * via (vpp).  (mp) is the mountpoint of the union filesystem,
 * (dvp) is the parent directory where the upper layer object
 * should exist (but doesn't) and (cnp) is the componentname
 * information which is partially copied to allow the upper
 * layer object to be created at a later time.  (uppervp)
 * and (lowervp) reference the upper and lower layer objects
 * being mapped.  either, but not both, can be nil.
I 10
 * if supplied, (uppervp) is locked.
E 10
I 6
 * the reference is either maintained in the new union_node
 * object which is allocated, or they are vrele'd.
E 6
E 3
 *
 * all union_nodes are maintained on a singly-linked
 * list.  new nodes are only allocated when they cannot
 * be found on this list.  entries on the list are
 * removed when the vfs reclaim entry is called.
 *
 * a single lock is kept for the entire list.  this is
 * needed because the getnewvnode() function can block
 * waiting for a vnode to become free, in which case there
 * may be more than one process trying to get the same
 * vnode.  this lock is only taken if we are going to
 * call getnewvnode, since the kernel itself is single-threaded.
 *
 * if an entry is found on the list, then call vget() to
 * take a reference.  this is done because there may be
 * zero references to it and so it needs to removed from
 * the vnode free list.
 */
int
D 4
union_allocvp(vpp, mp, dvp, cnp, uppervp, lowervp)
E 4
I 4
D 27
union_allocvp(vpp, mp, undvp, dvp, cnp, uppervp, lowervp)
E 27
I 27
union_allocvp(vpp, mp, undvp, dvp, cnp, uppervp, lowervp, docache)
E 27
E 4
	struct vnode **vpp;
	struct mount *mp;
I 4
D 22
	struct vnode *undvp;
E 22
I 22
	struct vnode *undvp;		/* parent union vnode */
E 22
E 4
	struct vnode *dvp;		/* may be null */
	struct componentname *cnp;	/* may be null */
	struct vnode *uppervp;		/* may be null */
	struct vnode *lowervp;		/* may be null */
I 27
	int docache;
E 27
{
	int error;
	struct union_node *un;
	struct union_node **pp;
I 3
D 11
	struct vnode *xlowervp = 0;
E 11
I 11
	struct vnode *xlowervp = NULLVP;
I 16
	struct union_mount *um = MOUNTTOUNIONMOUNT(mp);
E 16
	int hash;
I 16
	int vflag;
E 16
	int try;
E 11
E 3

I 3
D 11
	if (uppervp == 0 && lowervp == 0)
E 11
I 11
	if (uppervp == NULLVP && lowervp == NULLVP)
E 11
		panic("union: unidentifiable allocation");

	if (uppervp && lowervp && (uppervp->v_type != lowervp->v_type)) {
		xlowervp = lowervp;
D 11
		lowervp = 0;
E 11
I 11
		lowervp = NULLVP;
E 11
	}

I 16
	/* detect the root vnode (and aliases) */
	vflag = 0;
	if ((uppervp == um->um_uppervp) &&
	    ((lowervp == NULLVP) || lowervp == um->um_lowervp)) {
		if (lowervp == NULLVP) {
			lowervp = um->um_lowervp;
D 20
			VREF(lowervp);
E 20
I 20
			if (lowervp != NULLVP)
				VREF(lowervp);
E 20
		}
		vflag = VROOT;
	}

E 16
E 3
loop:
D 11
	for (un = unhead; un != 0; un = un->un_next) {
		if ((un->un_lowervp == lowervp ||
		     un->un_lowervp == 0) &&
		    (un->un_uppervp == uppervp ||
		     un->un_uppervp == 0) &&
		    (UNIONTOV(un)->v_mount == mp)) {
D 4
			if (vget(un->un_vnode, 1))
E 4
I 4
			if (vget(UNIONTOV(un), 0))
E 4
				goto loop;
E 11
I 11
D 27
	for (try = 0; try < 3; try++) {
E 27
I 27
	if (!docache) {
		un = 0;
	} else for (try = 0; try < 3; try++) {
E 27
		switch (try) {
		case 0:
			if (lowervp == NULLVP)
				continue;
			hash = UNION_HASH(uppervp, lowervp);
E 11
D 3
			un->un_lowervp = lowervp;
E 3
D 4
			un->un_uppervp = uppervp;
I 3
			if ((lowervp == 0) && un->un_lowervp)
				vrele(un->un_lowervp);
			un->un_lowervp = lowervp;
E 3
			*vpp = un->un_vnode;
E 4
I 4
D 10
			if (UNIONTOV(un) != undvp)
				VOP_LOCK(UNIONTOV(un));
E 10
I 10
			break;
I 11

		case 1:
			if (uppervp == NULLVP)
				continue;
			hash = UNION_HASH(uppervp, NULLVP);
			break;

		case 2:
			if (lowervp == NULLVP)
				continue;
			hash = UNION_HASH(NULLVP, lowervp);
			break;
E 11
		}
I 11

		while (union_list_lock(hash))
			continue;

		for (un = unhead[hash].lh_first; un != 0;
					un = un->un_cache.le_next) {
			if ((un->un_lowervp == lowervp ||
			     un->un_lowervp == NULLVP) &&
			    (un->un_uppervp == uppervp ||
			     un->un_uppervp == NULLVP) &&
			    (UNIONTOV(un)->v_mount == mp)) {
D 30
				if (vget(UNIONTOV(un), 0)) {
E 30
I 30
				if (vget(UNIONTOV(un), 0,
				    cnp ? cnp->cn_proc : NULL)) {
E 30
					union_list_unlock(hash);
					goto loop;
				}
				break;
			}
		}

		union_list_unlock(hash);

		if (un)
			break;
E 11
	}
E 10
I 7

I 10
	if (un) {
		/*
		 * Obtain a lock on the union_node.
		 * uppervp is locked, though un->un_uppervp
		 * may not be.  this doesn't break the locking
		 * hierarchy since in the case that un->un_uppervp
		 * is not yet locked it will be vrele'd and replaced
		 * with uppervp.
		 */

		if ((dvp != NULLVP) && (uppervp == dvp)) {
E 10
			/*
D 10
			 * Save information about the upper layer.
E 10
I 10
			 * Access ``.'', so (un) will already
			 * be locked.  Since this process has
			 * the lock on (uppervp) no other
			 * process can hold the lock on (un).
E 10
			 */
E 7
D 10
			if (uppervp != un->un_uppervp) {
				if (un->un_uppervp)
					vrele(un->un_uppervp);
				un->un_uppervp = uppervp;
I 6
			} else if (uppervp) {
				vrele(uppervp);
E 10
I 10
#ifdef DIAGNOSTIC
			if ((un->un_flags & UN_LOCKED) == 0)
				panic("union: . not locked");
			else if (curproc && un->un_pid != curproc->p_pid &&
				    un->un_pid > -1 && curproc->p_pid > -1)
				panic("union: allocvp not lock owner");
#endif
		} else {
			if (un->un_flags & UN_LOCKED) {
				vrele(UNIONTOV(un));
				un->un_flags |= UN_WANT;
				sleep((caddr_t) &un->un_flags, PINOD);
				goto loop;
E 10
E 6
			}
I 10
			un->un_flags |= UN_LOCKED;
E 10
I 7

D 10
			/*
			 * Save information about the lower layer.
			 * This needs to keep track of pathname
			 * and directory information which union_vn_create
			 * might need.
			 */
E 7
			if (lowervp != un->un_lowervp) {
D 7
				if (un->un_lowervp)
E 7
I 7
				if (un->un_lowervp) {
E 7
					vrele(un->un_lowervp);
I 7
					free(un->un_path, M_TEMP);
					vrele(un->un_dirvp);
				}
E 7
				un->un_lowervp = lowervp;
I 7
				if (cnp && (lowervp != NULLVP) &&
				    (lowervp->v_type == VREG)) {
					un->un_hash = cnp->cn_hash;
					un->un_path = malloc(cnp->cn_namelen+1,
							M_TEMP, M_WAITOK);
					bcopy(cnp->cn_nameptr, un->un_path,
							cnp->cn_namelen);
					un->un_path[cnp->cn_namelen] = '\0';
					VREF(dvp);
					un->un_dirvp = dvp;
				}
E 7
I 6
			} else if (lowervp) {
				vrele(lowervp);
E 10
I 10
#ifdef DIAGNOSTIC
			if (curproc)
				un->un_pid = curproc->p_pid;
			else
				un->un_pid = -1;
#endif
		}

		/*
		 * At this point, the union_node is locked,
		 * un->un_uppervp may not be locked, and uppervp
		 * is locked or nil.
		 */

		/*
		 * Save information about the upper layer.
		 */
		if (uppervp != un->un_uppervp) {
D 11
			if (un->un_uppervp)
				vrele(un->un_uppervp);
			un->un_uppervp = uppervp;
E 11
I 11
			union_newupper(un, uppervp);
E 11
		} else if (uppervp) {
			vrele(uppervp);
		}

		if (un->un_uppervp) {
			un->un_flags |= UN_ULOCK;
			un->un_flags &= ~UN_KLOCK;
		}

		/*
		 * Save information about the lower layer.
		 * This needs to keep track of pathname
		 * and directory information which union_vn_create
		 * might need.
		 */
		if (lowervp != un->un_lowervp) {
D 11
			if (un->un_lowervp) {
				vrele(un->un_lowervp);
				free(un->un_path, M_TEMP);
				vrele(un->un_dirvp);
E 10
E 6
			}
D 10
			*vpp = UNIONTOV(un);
E 4
			return (0);
E 10
I 10
			un->un_lowervp = lowervp;
E 11
I 11
			union_newlower(un, lowervp);
E 11
D 23
			if (cnp && (lowervp != NULLVP) &&
			    (lowervp->v_type == VREG)) {
E 23
I 23
			if (cnp && (lowervp != NULLVP)) {
E 23
				un->un_hash = cnp->cn_hash;
				un->un_path = malloc(cnp->cn_namelen+1,
						M_TEMP, M_WAITOK);
				bcopy(cnp->cn_nameptr, un->un_path,
						cnp->cn_namelen);
				un->un_path[cnp->cn_namelen] = '\0';
				VREF(dvp);
				un->un_dirvp = dvp;
			}
		} else if (lowervp) {
			vrele(lowervp);
E 10
		}
I 10
		*vpp = UNIONTOV(un);
		return (0);
E 10
	}

D 27
	/*
	 * otherwise lock the vp list while we call getnewvnode
	 * since that can block.
	 */ 
D 11
	if (unvplock & UN_LOCKED) {
		unvplock |= UN_WANT;
		sleep((caddr_t) &unvplock, PINOD);
E 11
I 11
	hash = UNION_HASH(uppervp, lowervp);
E 27
I 27
	if (docache) {
		/*
		 * otherwise lock the vp list while we call getnewvnode
		 * since that can block.
		 */ 
		hash = UNION_HASH(uppervp, lowervp);
E 27

D 27
	if (union_list_lock(hash))
E 11
		goto loop;
E 27
I 27
		if (union_list_lock(hash))
			goto loop;
	}
E 27
D 11
	}
	unvplock |= UN_LOCKED;
E 11

	error = getnewvnode(VT_UNION, mp, union_vnodeop_p, vpp);
D 10
	if (error)
E 10
I 10
	if (error) {
		if (uppervp) {
			if (dvp == uppervp)
				vrele(uppervp);
			else
				vput(uppervp);
		}
		if (lowervp)
			vrele(lowervp);

E 10
		goto out;
I 10
	}
E 10

	MALLOC((*vpp)->v_data, void *, sizeof(struct union_node),
		M_TEMP, M_WAITOK);

I 16
	(*vpp)->v_flag |= vflag;
E 16
I 3
	if (uppervp)
		(*vpp)->v_type = uppervp->v_type;
	else
		(*vpp)->v_type = lowervp->v_type;
E 3
	un = VTOUNION(*vpp);
I 4
	un->un_vnode = *vpp;
E 4
D 11
	un->un_next = 0;
E 11
D 3
	un->un_dirvp = dvp;
E 3
	un->un_uppervp = uppervp;
I 18
	un->un_uppersz = VNOVAL;
E 18
	un->un_lowervp = lowervp;
I 18
	un->un_lowersz = VNOVAL;
I 22
	un->un_pvp = undvp;
	if (undvp != NULLVP)
		VREF(undvp);
I 27
	un->un_dircache = 0;
E 27
E 22
E 18
I 6
D 8
	un->un_open = 0;
E 8
I 8
	un->un_openl = 0;
E 8
E 6
D 4
	un->un_vnode = *vpp;
E 4
D 10
	un->un_flags = 0;
E 10
I 10
	un->un_flags = UN_LOCKED;
	if (un->un_uppervp)
		un->un_flags |= UN_ULOCK;
#ifdef DIAGNOSTIC
	if (curproc)
		un->un_pid = curproc->p_pid;
	else
		un->un_pid = -1;
#endif
E 10
D 3
	if (cnp) {
E 3
I 3
D 7
	if (uppervp == 0 && cnp) {
E 7
I 7
D 23
	if (cnp && (lowervp != NULLVP) && (lowervp->v_type == VREG)) {
E 23
I 23
	if (cnp && (lowervp != NULLVP)) {
E 23
		un->un_hash = cnp->cn_hash;
E 7
E 3
		un->un_path = malloc(cnp->cn_namelen+1, M_TEMP, M_WAITOK);
		bcopy(cnp->cn_nameptr, un->un_path, cnp->cn_namelen);
		un->un_path[cnp->cn_namelen] = '\0';
I 3
		VREF(dvp);
		un->un_dirvp = dvp;
E 3
	} else {
I 7
		un->un_hash = 0;
E 7
		un->un_path = 0;
I 3
		un->un_dirvp = 0;
E 3
	}

D 4
#ifdef DIAGNOSTIC
	un->un_pid = 0;
#endif

E 4
D 11
	/* add to union vnode list */
	for (pp = &unhead; *pp; pp = &(*pp)->un_next)
		continue;
	*pp = un;
E 11
I 11
D 27
	LIST_INSERT_HEAD(&unhead[hash], un, un_cache);
I 17
	un->un_flags |= UN_CACHED;
E 27
I 27
	if (docache) {
		LIST_INSERT_HEAD(&unhead[hash], un, un_cache);
		un->un_flags |= UN_CACHED;
	}
E 27
E 17
E 11

I 3
D 4
	if (un)
		un->un_flags |= UN_LOCKED;
E 4
I 4
D 10
	un->un_flags |= UN_LOCKED;

#ifdef DIAGNOSTIC
	un->un_pid = curproc->p_pid;
#endif
E 4

E 10
	if (xlowervp)
		vrele(xlowervp);

E 3
out:
D 11
	unvplock &= ~UN_LOCKED;
E 11
I 11
D 27
	union_list_unlock(hash);
E 27
I 27
	if (docache)
		union_list_unlock(hash);
E 27
E 11

D 11
	if (unvplock & UN_WANT) {
		unvplock &= ~UN_WANT;
		wakeup((caddr_t) &unvplock);
	}
D 3

	if (un)
		VOP_LOCK(UNIONTOV(un));
E 3

E 11
	return (error);
}

int
union_freevp(vp)
	struct vnode *vp;
{
D 10
	struct union_node **unpp;
E 10
	struct union_node *un = VTOUNION(vp);

D 10
	for (unpp = &unhead; *unpp != 0; unpp = &(*unpp)->un_next) {
		if (*unpp == un) {
			*unpp = un->un_next;
			break;
		}
	}
E 10
I 10
D 11
	union_remlist(un);
E 11
I 11
D 17
	LIST_REMOVE(un, un_cache);
E 17
I 17
	if (un->un_flags & UN_CACHED) {
D 21
		LIST_REMOVE(un, un_cache);
E 21
		un->un_flags &= ~UN_CACHED;
I 21
		LIST_REMOVE(un, un_cache);
E 21
	}
E 17
E 11
E 10

I 22
	if (un->un_pvp != NULLVP)
		vrele(un->un_pvp);
E 22
I 11
D 17
	if (un->un_uppervp)
E 17
I 17
	if (un->un_uppervp != NULLVP)
E 17
		vrele(un->un_uppervp);
D 17
	if (un->un_lowervp)
E 17
I 17
	if (un->un_lowervp != NULLVP)
E 17
		vrele(un->un_lowervp);
D 17
	if (un->un_dirvp)
E 17
I 17
	if (un->un_dirvp != NULLVP)
E 17
		vrele(un->un_dirvp);
	if (un->un_path)
		free(un->un_path, M_TEMP);

E 11
D 6
	if (un->un_path)
		FREE(un->un_path, M_TEMP);

E 6
	FREE(vp->v_data, M_TEMP);
	vp->v_data = 0;
I 11

E 11
	return (0);
I 5
}

/*
 * copyfile.  copy the vnode (fvp) to the vnode (tvp)
 * using a sequence of reads and writes.  both (fvp)
 * and (tvp) are locked on entry and exit.
 */
int
D 19
union_copyfile(p, cred, fvp, tvp)
	struct proc *p;
	struct ucred *cred;
E 19
I 19
union_copyfile(fvp, tvp, cred, p)
E 19
	struct vnode *fvp;
	struct vnode *tvp;
I 19
	struct ucred *cred;
	struct proc *p;
E 19
{
	char *buf;
	struct uio uio;
	struct iovec iov;
	int error = 0;

	/*
	 * strategy:
	 * allocate a buffer of size MAXBSIZE.
	 * loop doing reads and writes, keeping track
	 * of the current uio offset.
	 * give up at the first sign of trouble.
	 */

	uio.uio_procp = p;
	uio.uio_segflg = UIO_SYSSPACE;
	uio.uio_offset = 0;

D 30
	VOP_UNLOCK(fvp);				/* XXX */
E 30
I 30
	VOP_UNLOCK(fvp, 0, p);				/* XXX */
E 30
D 24
	LEASE_CHECK(fvp, p, cred, LEASE_READ);
E 24
I 24
	VOP_LEASE(fvp, p, cred, LEASE_READ);
E 24
D 30
	VOP_LOCK(fvp);					/* XXX */
	VOP_UNLOCK(tvp);				/* XXX */
E 30
I 30
	vn_lock(fvp, LK_EXCLUSIVE | LK_RETRY, p);	/* XXX */
	VOP_UNLOCK(tvp, 0, p);				/* XXX */
E 30
D 24
	LEASE_CHECK(tvp, p, cred, LEASE_WRITE);
E 24
I 24
	VOP_LEASE(tvp, p, cred, LEASE_WRITE);
E 24
D 30
	VOP_LOCK(tvp);					/* XXX */
E 30
I 30
	vn_lock(tvp, LK_EXCLUSIVE | LK_RETRY, p);	/* XXX */
E 30

	buf = malloc(MAXBSIZE, M_TEMP, M_WAITOK);

	/* ugly loop follows... */
	do {
		off_t offset = uio.uio_offset;

		uio.uio_iov = &iov;
		uio.uio_iovcnt = 1;
		iov.iov_base = buf;
		iov.iov_len = MAXBSIZE;
		uio.uio_resid = iov.iov_len;
		uio.uio_rw = UIO_READ;
		error = VOP_READ(fvp, &uio, 0, cred);

		if (error == 0) {
			uio.uio_iov = &iov;
			uio.uio_iovcnt = 1;
			iov.iov_base = buf;
			iov.iov_len = MAXBSIZE - uio.uio_resid;
			uio.uio_offset = offset;
			uio.uio_rw = UIO_WRITE;
			uio.uio_resid = iov.iov_len;

			if (uio.uio_resid == 0)
				break;

			do {
				error = VOP_WRITE(tvp, &uio, 0, cred);
			} while ((uio.uio_resid > 0) && (error == 0));
		}

	} while (error == 0);

	free(buf, M_TEMP);
	return (error);
}

/*
I 19
 * (un) is assumed to be locked on entry and remains
 * locked on exit.
 */
int
union_copyup(un, docopy, cred, p)
	struct union_node *un;
	int docopy;
	struct ucred *cred;
	struct proc *p;
{
	int error;
	struct vnode *lvp, *uvp;

	error = union_vn_create(&uvp, un, p);
	if (error)
		return (error);

	/* at this point, uppervp is locked */
	union_newupper(un, uvp);
	un->un_flags |= UN_ULOCK;

	lvp = un->un_lowervp;

	if (docopy) {
		/*
		 * XX - should not ignore errors
		 * from VOP_CLOSE
		 */
D 30
		VOP_LOCK(lvp);
E 30
I 30
		vn_lock(lvp, LK_EXCLUSIVE | LK_RETRY, p);
E 30
		error = VOP_OPEN(lvp, FREAD, cred, p);
		if (error == 0) {
			error = union_copyfile(lvp, uvp, cred, p);
D 30
			VOP_UNLOCK(lvp);
E 30
I 30
			VOP_UNLOCK(lvp, 0, p);
E 30
D 28
			(void) VOP_CLOSE(lvp, FREAD);
E 28
I 28
			(void) VOP_CLOSE(lvp, FREAD, cred, p);
E 28
		}
#ifdef UNION_DIAGNOSTIC
		if (error == 0)
			uprintf("union: copied up %s\n", un->un_path);
#endif

	}
	un->un_flags &= ~UN_ULOCK;
D 30
	VOP_UNLOCK(uvp);
E 30
I 30
	VOP_UNLOCK(uvp, 0, p);
E 30
	union_vn_close(uvp, FWRITE, cred, p);
D 30
	VOP_LOCK(uvp);
E 30
I 30
	vn_lock(uvp, LK_EXCLUSIVE | LK_RETRY, p);
E 30
	un->un_flags |= UN_ULOCK;

	/*
	 * Subsequent IOs will go to the top layer, so
	 * call close on the lower vnode and open on the
	 * upper vnode to ensure that the filesystem keeps
	 * its references counts right.  This doesn't do
	 * the right thing with (cred) and (FREAD) though.
	 * Ignoring error returns is not right, either.
	 */
	if (error == 0) {
		int i;

		for (i = 0; i < un->un_openl; i++) {
D 28
			(void) VOP_CLOSE(lvp, FREAD);
E 28
I 28
			(void) VOP_CLOSE(lvp, FREAD, cred, p);
E 28
			(void) VOP_OPEN(uvp, FREAD, cred, p);
		}
		un->un_openl = 0;
	}

	return (error);

}

I 23
static int
D 24
union_relookup(um, dvp, vpp, cnp, cn, path)
E 24
I 24
union_relookup(um, dvp, vpp, cnp, cn, path, pathlen)
E 24
	struct union_mount *um;
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
	struct componentname *cn;
	char *path;
I 24
	int pathlen;
E 24
{
	int error;

	/*
	 * A new componentname structure must be faked up because
	 * there is no way to know where the upper level cnp came
	 * from or what it is being used for.  This must duplicate
	 * some of the work done by NDINIT, some of the work done
	 * by namei, some of the work done by lookup and some of
	 * the work done by VOP_LOOKUP when given a CREATE flag.
	 * Conclusion: Horrible.
	 *
	 * The pathname buffer will be FREEed by VOP_MKDIR.
	 */
D 24
	cn->cn_namelen = strlen(path);
E 24
I 24
	cn->cn_namelen = pathlen;
E 24
	cn->cn_pnbuf = malloc(cn->cn_namelen+1, M_NAMEI, M_WAITOK);
	bcopy(path, cn->cn_pnbuf, cn->cn_namelen);
	cn->cn_pnbuf[cn->cn_namelen] = '\0';

	cn->cn_nameiop = CREATE;
	cn->cn_flags = (LOCKPARENT|HASBUF|SAVENAME|SAVESTART|ISLASTCN);
	cn->cn_proc = cnp->cn_proc;
	if (um->um_op == UNMNT_ABOVE)
		cn->cn_cred = cnp->cn_cred;
	else
		cn->cn_cred = um->um_cred;
	cn->cn_nameptr = cn->cn_pnbuf;
	cn->cn_hash = cnp->cn_hash;
	cn->cn_consume = cnp->cn_consume;

	VREF(dvp);
	error = relookup(dvp, vpp, cn);
	if (!error)
		vrele(dvp);

	return (error);
}

E 23
/*
E 19
I 6
 * Create a shadow directory in the upper layer.
 * The new vnode is returned locked.
 *
 * (um) points to the union mount structure for access to the
 * the mounting process's credentials.
 * (dvp) is the directory in which to create the shadow directory.
 * it is unlocked on entry and exit.
 * (cnp) is the componentname to be created.
 * (vpp) is the returned newly created shadow directory, which
 * is returned locked.
 */
int
union_mkshadow(um, dvp, cnp, vpp)
	struct union_mount *um;
	struct vnode *dvp;
	struct componentname *cnp;
	struct vnode **vpp;
{
	int error;
	struct vattr va;
	struct proc *p = cnp->cn_proc;
	struct componentname cn;

I 23
D 24
	error = union_relookup(um, dvp, vpp, cnp, &cn, cnp->cn_nameptr);
E 24
I 24
	error = union_relookup(um, dvp, vpp, cnp, &cn,
			cnp->cn_nameptr, cnp->cn_namelen);
E 24
	if (error)
		return (error);

	if (*vpp) {
		VOP_ABORTOP(dvp, &cn);
D 30
		VOP_UNLOCK(dvp);
E 30
I 30
		VOP_UNLOCK(dvp, 0, p);
E 30
		vrele(*vpp);
		*vpp = NULLVP;
		return (EEXIST);
	}

E 23
	/*
	 * policy: when creating the shadow directory in the
D 9
	 * upper layer, create it owned by the current user,
	 * group from parent directory, and mode 777 modified
	 * by umask (ie mostly identical to the mkdir syscall).
	 * (jsp, kb)
	 * TODO: create the directory owned by the user who
	 * did the mount (um->um_cred).
E 9
I 9
	 * upper layer, create it owned by the user who did
	 * the mount, group from parent directory, and mode
	 * 777 modified by umask (ie mostly identical to the
	 * mkdir syscall).  (jsp, kb)
E 9
	 */

D 23
	/*
	 * A new componentname structure must be faked up because
	 * there is no way to know where the upper level cnp came
	 * from or what it is being used for.  This must duplicate
	 * some of the work done by NDINIT, some of the work done
	 * by namei, some of the work done by lookup and some of
	 * the work done by VOP_LOOKUP when given a CREATE flag.
	 * Conclusion: Horrible.
	 *
	 * The pathname buffer will be FREEed by VOP_MKDIR.
	 */
	cn.cn_pnbuf = malloc(cnp->cn_namelen+1, M_NAMEI, M_WAITOK);
D 7
	bcopy(cnp->cn_nameptr, cn.cn_pnbuf, cnp->cn_namelen+1);
E 7
I 7
	bcopy(cnp->cn_nameptr, cn.cn_pnbuf, cnp->cn_namelen);
	cn.cn_pnbuf[cnp->cn_namelen] = '\0';
E 23
I 23
	VATTR_NULL(&va);
	va.va_type = VDIR;
	va.va_mode = um->um_cmode;
E 23
E 7

D 23
	cn.cn_nameiop = CREATE;
D 14
	cn.cn_flags = (LOCKPARENT|HASBUF|SAVENAME|ISLASTCN);
E 14
I 14
	cn.cn_flags = (LOCKPARENT|HASBUF|SAVENAME|SAVESTART|ISLASTCN);
E 14
	cn.cn_proc = cnp->cn_proc;
D 9
	cn.cn_cred = cnp->cn_cred;
E 9
I 9
D 15
	cn.cn_cred = um->um_cred;
E 15
I 15
	if (um->um_op == UNMNT_ABOVE)
		cn.cn_cred = cnp->cn_cred;
	else
		cn.cn_cred = um->um_cred;
E 15
E 9
	cn.cn_nameptr = cn.cn_pnbuf;
	cn.cn_namelen = cnp->cn_namelen;
	cn.cn_hash = cnp->cn_hash;
	cn.cn_consume = cnp->cn_consume;
E 23
I 23
D 24
	/* LEASE_CHECK: dvp is locked */
	LEASE_CHECK(dvp, p, cn.cn_cred, LEASE_WRITE);
E 24
I 24
	/* VOP_LEASE: dvp is locked */
	VOP_LEASE(dvp, p, cn.cn_cred, LEASE_WRITE);
E 24
E 23

I 7
D 23
	VREF(dvp);
E 7
	if (error = relookup(dvp, vpp, &cn))
E 23
I 23
	error = VOP_MKDIR(dvp, vpp, &cn, &va);
	return (error);
}

/*
 * Create a whiteout entry in the upper layer.
 *
 * (um) points to the union mount structure for access to the
 * the mounting process's credentials.
 * (dvp) is the directory in which to create the whiteout.
 * it is locked on entry and exit.
 * (cnp) is the componentname to be created.
 */
int
union_mkwhiteout(um, dvp, cnp, path)
	struct union_mount *um;
	struct vnode *dvp;
	struct componentname *cnp;
	char *path;
{
	int error;
	struct vattr va;
	struct proc *p = cnp->cn_proc;
D 26
	struct vnode **vpp;
E 26
I 26
	struct vnode *wvp;
E 26
	struct componentname cn;

D 30
	VOP_UNLOCK(dvp);
E 30
I 30
	VOP_UNLOCK(dvp, 0, p);
E 30
D 24
	error = union_relookup(um, dvp, vpp, cnp, &cn, path);
	if (error)
E 24
I 24
D 26
	error = union_relookup(um, dvp, vpp, cnp, &cn, path, strlen(path));
E 26
I 26
	error = union_relookup(um, dvp, &wvp, cnp, &cn, path, strlen(path));
E 26
	if (error) {
D 30
		VOP_LOCK(dvp);
E 30
I 30
		vn_lock(dvp, LK_EXCLUSIVE | LK_RETRY, p);
E 30
E 24
E 23
		return (error);
I 24
	}
E 24
I 7
D 23
	vrele(dvp);
E 23
E 7

D 26
	if (*vpp) {
E 26
I 26
	if (wvp) {
E 26
		VOP_ABORTOP(dvp, &cn);
D 23
		VOP_UNLOCK(dvp);
E 23
I 23
		vrele(dvp);
E 23
D 26
		vrele(*vpp);
		*vpp = NULLVP;
E 26
I 26
		vrele(wvp);
E 26
		return (EEXIST);
	}

D 23
	VATTR_NULL(&va);
	va.va_type = VDIR;
D 7
	va.va_mode = UN_DIRMODE &~ p->p_fd->fd_cmask;
E 7
I 7
D 9
	va.va_mode = UN_DIRMODE & ~p->p_fd->fd_cmask;
E 9
I 9
	va.va_mode = um->um_cmode;
E 9
E 7

E 23
D 24
	/* LEASE_CHECK: dvp is locked */
	LEASE_CHECK(dvp, p, p->p_ucred, LEASE_WRITE);
E 24
I 24
	/* VOP_LEASE: dvp is locked */
	VOP_LEASE(dvp, p, p->p_ucred, LEASE_WRITE);
E 24

D 14
	VREF(dvp);
E 14
D 23
	error = VOP_MKDIR(dvp, vpp, &cn, &va);
E 23
I 23
	error = VOP_WHITEOUT(dvp, &cn, CREATE);
D 24
	if (error != 0)
E 24
I 24
	if (error)
E 24
		VOP_ABORTOP(dvp, &cn);

	vrele(dvp);

E 23
	return (error);
}

/*
E 6
 * union_vn_create: creates and opens a new shadow file
 * on the upper union layer.  this function is similar
 * in spirit to calling vn_open but it avoids calling namei().
 * the problem with calling namei is that a) it locks too many
 * things, and b) it doesn't start at the "right" directory,
 * whereas relookup is told where to start.
 */
int
D 6
union_vn_create(vpp, un, cmode, p)
E 6
I 6
union_vn_create(vpp, un, p)
E 6
	struct vnode **vpp;
	struct union_node *un;
D 6
	int cmode;
E 6
	struct proc *p;
{
	struct vnode *vp;
	struct ucred *cred = p->p_ucred;
	struct vattr vat;
	struct vattr *vap = &vat;
	int fmode = FFLAGS(O_WRONLY|O_CREAT|O_TRUNC|O_EXCL);
	int error;
D 7
	int hash;
I 6
	int cmode = UN_FILEMODE &~ p->p_fd->fd_cmask;
E 7
I 7
	int cmode = UN_FILEMODE & ~p->p_fd->fd_cmask;
E 7
E 6
	char *cp;
	struct componentname cn;

	*vpp = NULLVP;

I 9
	/*
	 * Build a new componentname structure (for the same
	 * reasons outlines in union_mkshadow).
	 * The difference here is that the file is owned by
	 * the current user, rather than by the person who
	 * did the mount, since the current user needs to be
	 * able to write the file (that's why it is being
	 * copied in the first place).
	 */
E 9
	cn.cn_namelen = strlen(un->un_path);
	cn.cn_pnbuf = (caddr_t) malloc(cn.cn_namelen, M_NAMEI, M_WAITOK);
	bcopy(un->un_path, cn.cn_pnbuf, cn.cn_namelen+1);
	cn.cn_nameiop = CREATE;
D 14
	cn.cn_flags = (LOCKLEAF|LOCKPARENT|HASBUF|SAVENAME|ISLASTCN);
E 14
I 14
	cn.cn_flags = (LOCKPARENT|HASBUF|SAVENAME|SAVESTART|ISLASTCN);
E 14
	cn.cn_proc = p;
	cn.cn_cred = p->p_ucred;
	cn.cn_nameptr = cn.cn_pnbuf;
D 7
	for (hash = 0, cp = cn.cn_nameptr; *cp != 0 && *cp != '/'; cp++)
		hash += (unsigned char)*cp;
	cn.cn_hash = hash;
E 7
I 7
	cn.cn_hash = un->un_hash;
E 7
	cn.cn_consume = 0;

I 7
	VREF(un->un_dirvp);
E 7
	if (error = relookup(un->un_dirvp, &vp, &cn))
		return (error);
I 7
	vrele(un->un_dirvp);

E 7
D 14
	if (vp == NULLVP) {
I 9
		/*
		 * Good - there was no race to create the file
		 * so go ahead and create it.  The permissions
		 * on the file will be 0666 modified by the
		 * current user's umask.  Access to the file, while
		 * it is unioned, will require access to the top *and*
		 * bottom files.  Access when not unioned will simply
		 * require access to the top-level file.
		 * TODO: confirm choice of access permissions.
		 */
E 9
		VATTR_NULL(vap);
		vap->va_type = VREG;
		vap->va_mode = cmode;
		LEASE_CHECK(un->un_dirvp, p, cred, LEASE_WRITE);
		if (error = VOP_CREATE(un->un_dirvp, &vp,
		    &cn, vap))
			return (error);
	} else {
E 14
I 14
	if (vp) {
E 14
		VOP_ABORTOP(un->un_dirvp, &cn);
		if (un->un_dirvp == vp)
			vrele(un->un_dirvp);
		else
D 14
			vput(vp);
		error = EEXIST;
		goto bad;
E 14
I 14
			vput(un->un_dirvp);
		vrele(vp);
		return (EEXIST);
E 14
	}

D 14
	if (vp->v_type != VREG) {
		error = EOPNOTSUPP;
		goto bad;
	}

	VOP_UNLOCK(vp);				/* XXX */
	LEASE_CHECK(vp, p, cred, LEASE_WRITE);
	VOP_LOCK(vp);				/* XXX */
E 14
I 14
	/*
	 * Good - there was no race to create the file
	 * so go ahead and create it.  The permissions
	 * on the file will be 0666 modified by the
	 * current user's umask.  Access to the file, while
	 * it is unioned, will require access to the top *and*
	 * bottom files.  Access when not unioned will simply
	 * require access to the top-level file.
	 * TODO: confirm choice of access permissions.
	 */
E 14
	VATTR_NULL(vap);
D 14
	vap->va_size = 0;
	if (error = VOP_SETATTR(vp, vap, cred, p))
		goto bad;
E 14
I 14
	vap->va_type = VREG;
	vap->va_mode = cmode;
D 24
	LEASE_CHECK(un->un_dirvp, p, cred, LEASE_WRITE);
E 24
I 24
	VOP_LEASE(un->un_dirvp, p, cred, LEASE_WRITE);
E 24
	if (error = VOP_CREATE(un->un_dirvp, &vp, &cn, vap))
		return (error);
E 14

D 14
	if (error = VOP_OPEN(vp, fmode, cred, p))
		goto bad;
E 14
I 14
	if (error = VOP_OPEN(vp, fmode, cred, p)) {
		vput(vp);
		return (error);
	}
E 14

	vp->v_writecount++;
	*vpp = vp;
	return (0);
D 14
bad:
	vput(vp);
	return (error);
E 14
I 7
}

int
D 8
union_vn_close(vp, fmode)
E 8
I 8
union_vn_close(vp, fmode, cred, p)
E 8
	struct vnode *vp;
	int fmode;
I 8
	struct ucred *cred;
	struct proc *p;
E 8
{
I 23

E 23
	if (fmode & FWRITE)
		--vp->v_writecount;
D 28
	return (VOP_CLOSE(vp, fmode));
E 28
I 28
	return (VOP_CLOSE(vp, fmode, cred, p));
E 28
}

void
union_removed_upper(un)
	struct union_node *un;
{
I 30
	struct proc *p = curproc;	/* XXX */
E 30
I 21

E 21
D 10
	vrele(un->un_uppervp);
E 10
I 10
D 29
	if (un->un_flags & UN_ULOCK) {
		un->un_flags &= ~UN_ULOCK;
D 11
		vput(un->un_uppervp);
	} else {
		vrele(un->un_uppervp);
E 11
I 11
		VOP_UNLOCK(un->un_uppervp);
E 11
	}
E 10
D 11
	un->un_uppervp = NULLVP;
E 11
I 11

E 29
I 29
	union_newupper(un, NULLVP);
E 29
D 21
	union_newupper(un, NULLVP);
E 21
I 21
	if (un->un_flags & UN_CACHED) {
		un->un_flags &= ~UN_CACHED;
		LIST_REMOVE(un, un_cache);
I 29
	}

	if (un->un_flags & UN_ULOCK) {
		un->un_flags &= ~UN_ULOCK;
D 30
		VOP_UNLOCK(un->un_uppervp);
E 30
I 30
		VOP_UNLOCK(un->un_uppervp, 0, p);
E 30
E 29
	}
E 21
E 11
I 8
}

I 27
#if 0
E 27
struct vnode *
union_lowervp(vp)
	struct vnode *vp;
{
	struct union_node *un = VTOUNION(vp);

D 19
	if (un->un_lowervp && (vp->v_type == un->un_lowervp->v_type)) {
		if (vget(un->un_lowervp, 0))
			return (NULLVP);
E 19
I 19
	if ((un->un_lowervp != NULLVP) &&
	    (vp->v_type == un->un_lowervp->v_type)) {
		if (vget(un->un_lowervp, 0) == 0)
			return (un->un_lowervp);
E 19
	}

D 19
	return (un->un_lowervp);
E 19
I 19
	return (NULLVP);
I 25
}
I 27
#endif
E 27

/*
 * determine whether a whiteout is needed
 * during a remove/rmdir operation.
 */
int
union_dowhiteout(un, cred, p)
	struct union_node *un;
	struct ucred *cred;
	struct proc *p;
{
	struct vattr va;

	if (un->un_lowervp != NULLVP)
		return (1);

	if (VOP_GETATTR(un->un_uppervp, &va, cred, p) == 0 &&
	    (va.va_flags & OPAQUE))
		return (1);

	return (0);
I 27
}

static void
union_dircache_r(vp, vppp, cntp)
	struct vnode *vp;
	struct vnode ***vppp;
	int *cntp;
{
	struct union_node *un;

	if (vp->v_op != union_vnodeop_p) {
		if (vppp) {
			VREF(vp);
			*(*vppp)++ = vp;
			if (--(*cntp) == 0)
				panic("union: dircache table too small");
		} else {
			(*cntp)++;
		}

		return;
	}

	un = VTOUNION(vp);
	if (un->un_uppervp != NULLVP)
		union_dircache_r(un->un_uppervp, vppp, cntp);
	if (un->un_lowervp != NULLVP)
		union_dircache_r(un->un_lowervp, vppp, cntp);
}

struct vnode *
D 30
union_dircache(vp)
E 30
I 30
union_dircache(vp, p)
E 30
	struct vnode *vp;
I 30
	struct proc *p;
E 30
{
	int cnt;
	struct vnode *nvp;
	struct vnode **vpp;
D 31
	struct vnode **dircache = VTOUNION(vp)->un_dircache;
E 31
I 31
	struct vnode **dircache;
E 31
	struct union_node *un;
	int error;

I 31
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY, p);
	dircache = VTOUNION(vp)->un_dircache;

	nvp = NULLVP;

E 31
	if (dircache == 0) {
		cnt = 0;
		union_dircache_r(vp, 0, &cnt);
		cnt++;
		dircache = (struct vnode **)
				malloc(cnt * sizeof(struct vnode *),
					M_TEMP, M_WAITOK);
		vpp = dircache;
		union_dircache_r(vp, &vpp, &cnt);
		*vpp = NULLVP;
		vpp = dircache + 1;
	} else {
		vpp = dircache;
		do {
			if (*vpp++ == VTOUNION(vp)->un_uppervp)
				break;
		} while (*vpp != NULLVP);
	}

	if (*vpp == NULLVP)
D 31
		return (NULLVP);
E 31
I 31
		goto out;
E 31

D 30
	VOP_LOCK(*vpp);
E 30
I 30
	vn_lock(*vpp, LK_EXCLUSIVE | LK_RETRY, p);
E 30
	VREF(*vpp);
	error = union_allocvp(&nvp, vp->v_mount, NULLVP, NULLVP, 0, *vpp, NULLVP, 0);
	if (error)
D 31
		return (NULLVP);
E 31
I 31
		goto out;

E 31
	VTOUNION(vp)->un_dircache = 0;
	un = VTOUNION(nvp);
	un->un_dircache = dircache;

I 31
out:
	VOP_UNLOCK(vp, 0, p);
E 31
	return (nvp);
E 27
E 25
E 19
E 8
E 7
E 5
}
E 1
