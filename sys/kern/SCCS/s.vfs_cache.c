h01416
s 00012/00003/00282
d D 8.5 95/03/22 16:33:26 mckusick 21 20
c track whiteout negative cache entries (from mycroft)
e
s 00126/00086/00159
d D 8.4 95/03/18 22:20:14 mckusick 20 19
c merge in code from Poul-Henning Kamp
e
s 00038/00097/00207
d D 8.3 94/08/22 10:20:09 mckusick 19 18
c use new queue.h data structures
e
s 00003/00001/00301
d D 8.2 94/07/05 15:12:59 mckusick 18 17
c turn off MAKEENTRY flag when doingcache is disabled (from cgd)
e
s 00002/00002/00300
d D 8.1 93/06/10 22:00:19 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00294
d D 7.16 92/10/11 10:39:03 bostic 16 15
c make kernel includes standard
e
s 00012/00007/00290
d D 7.15 92/09/24 18:10:46 mckusick 15 14
c have to check for insertion into head of an empty LRU list
e
s 00016/00010/00281
d D 7.14 92/07/25 20:18:19 mckusick 14 13
c have to verify that name is on hash chain before trying to remove it
e
s 00043/00055/00248
d D 7.13 92/07/22 17:19:17 mckusick 13 12
c new cacheing structure
e
s 00004/00000/00299
d D 7.12 92/07/13 23:22:48 mckusick 12 11
c add namelength consistency check
e
s 00001/00001/00298
d D 7.11 92/03/14 23:40:25 torek 11 10
c gcc lint
e
s 00003/00005/00296
d D 7.10 92/02/03 23:28:06 heideman 10 9
c misc cleanups
e
s 00027/00022/00274
d D 7.9 92/01/22 09:37:38 heideman 9 8
c lookup converted to new form
e
s 00017/00014/00279
d D 7.8 91/02/28 13:23:00 mckusick 8 7
c cache open with O_CREAT when the name already exists
e
s 00005/00003/00288
d D 7.7 90/08/24 10:00:23 mckusick 7 6
c lint
e
s 00001/00011/00290
d D 7.6 90/06/28 21:25:43 bostic 6 5
c new copyright notice
e
s 00048/00046/00253
d D 7.5 90/04/10 20:32:56 mckusick 5 4
c dynamically allocate the name cache and name cache hashing header
e
s 00076/00064/00223
d D 7.4 89/08/25 23:56:17 mckusick 4 3
c update for soft references and negative cacheing
e
s 00002/00000/00285
d D 7.3 89/05/09 20:49:27 mckusick 3 2
c no caching for now
e
s 00000/00001/00285
d D 7.2 89/05/05 00:06:58 mckusick 2 1
c delete unneeded include of dir.h
e
s 00286/00000/00000
d D 7.1 89/04/24 20:38:59 mckusick 1 0
c first bootable vnodes (extracted from vfs_lookup.c)
e
u
U
t
T
I 1
/*
D 17
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 17
I 17
D 20
 * Copyright (c) 1989, 1993
E 20
I 20
 * Copyright (c) 1989, 1993, 1995
E 20
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
I 20
 * This code is derived from software contributed to Berkeley by
 * Poul-Henning Kamp of the FreeBSD Project.
 *
E 20
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 *
I 20
 * from: vfs_cache.c,v 1.11 1995/03/12 02:01:20 phk Exp $
 *
E 20
 *	%W% (Berkeley) %G%
 */

D 16
#include "param.h"
#include "systm.h"
#include "time.h"
I 7
#include "mount.h"
E 7
#include "vnode.h"
D 2
#include "dir.h"
E 2
#include "namei.h"
I 4
#include "errno.h"
I 5
#include "malloc.h"
E 16
I 16
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/namei.h>
#include <sys/errno.h>
#include <sys/malloc.h>
E 16
E 5
E 4

/*
 * Name caching works as follows:
 *
 * Names found by directory scans are retained in a cache
 * for future reference.  It is managed LRU, so frequently
 * used names will hang around.  Cache is indexed by hash value
D 4
 * obtained from (ino,dev,name) where ino & dev refer to the
 * directory containing name.
E 4
I 4
 * obtained from (vp, name) where vp refers to the directory
 * containing name.
E 4
 *
I 20
 * If it is a "negative" entry, (i.e. for a name that is known NOT to
 * exist) the vnode pointer will be NULL.
 *
E 20
 * For simplicity (and economy of storage), names longer than
 * a maximum length of NCHNAMLEN are not cached; they occur
 * infrequently in any case, and are almost never of interest.
 *
 * Upon reaching the last segment of a path, if the reference
 * is for DELETE, or NOCACHE is set (rewrite), and the
 * name is located in the cache, it will be dropped.
 */

/*
 * Structures associated with name cacheing.
 */
D 5
#define	NCHHASH		128	/* size of hash table */

#if	((NCHHASH)&((NCHHASH)-1)) != 0
D 4
#define	NHASH(h)	(((unsigned)(h) >> 6) % (NCHHASH))
E 4
I 4
#define	NHASH(vp, h)	((((unsigned)(h) >> 6) + (h)) % (NCHHASH))
E 4
#else
D 4
#define	NHASH(h)	(((unsigned)(h) >> 6) & ((NCHHASH)-1))
E 4
I 4
#define	NHASH(vp, h)	((((unsigned)(h) >> 6) + (h)) & ((NCHHASH)-1))
E 4
#endif

E 5
D 13
union nchash {
	union	nchash *nch_head[2];
	struct	namecache *nch_chain[2];
D 5
} nchash[NCHHASH];
E 5
I 5
} *nchashtbl;
E 5
#define	nch_forw	nch_chain[0]
#define	nch_back	nch_chain[1]

E 13
I 13
D 19
struct namecache **nchashtbl;
E 19
I 19
D 20
LIST_HEAD(nchashhead, namecache) *nchashtbl;
E 20
I 20
#define NCHHASH(dvp, cnp) \
	(&nchashtbl[((dvp)->v_id + (cnp)->cn_hash) & nchash])
LIST_HEAD(nchashhead, namecache) *nchashtbl;	/* Hash Table */
E 20
E 19
E 13
I 5
u_long	nchash;				/* size of hash table - 1 */
long	numcache;			/* number of cache entries allocated */
E 5
D 19
struct	namecache *nchhead, **nchtail;	/* LRU chain pointers */
E 19
I 19
D 20
TAILQ_HEAD(, namecache) nclruhead;		/* LRU chain */
E 20
I 20
TAILQ_HEAD(, namecache) nclruhead;	/* LRU chain */
E 20
E 19
struct	nchstats nchstats;		/* cache effectiveness statistics */

I 4
int doingcache = 1;			/* 1 => enable the cache */

E 4
/*
D 20
 * Look for a the name in the cache. We don't do this
 * if the segment name is long, simply so the cache can avoid
 * holding long names (which would either waste space, or
E 20
I 20
 * Delete an entry from its hash list and move it to the front
 * of the LRU list for immediate reuse.
 */
#define PURGE(ncp)  {						\
	LIST_REMOVE(ncp, nc_hash);				\
	ncp->nc_hash.le_prev = 0;				\
	TAILQ_REMOVE(&nclruhead, ncp, nc_lru);			\
	TAILQ_INSERT_HEAD(&nclruhead, ncp, nc_lru);		\
}

/*
 * Move an entry that has been used to the tail of the LRU list
 * so that it will be preserved for future use.
 */
#define TOUCH(ncp)  {						\
	if (ncp->nc_lru.tqe_next != 0) {			\
		TAILQ_REMOVE(&nclruhead, ncp, nc_lru);		\
		TAILQ_INSERT_TAIL(&nclruhead, ncp, nc_lru);	\
	}							\
}

/*
 * Lookup an entry in the cache 
 *
 * We don't do this if the segment name is long, simply so the cache 
 * can avoid holding long names (which would either waste space, or
E 20
 * add greatly to the complexity).
I 4
 *
D 20
 * Lookup is called with ni_dvp pointing to the directory to search,
 * ni_ptr pointing to the name of the entry being sought, ni_namelen
 * tells the length of the name, and ni_hash contains a hash of
 * the name. If the lookup succeeds, the vnode is returned in ni_vp
 * and a status of -1 is returned. If the lookup determines that
 * the name does not exist (negative cacheing), a status of ENOENT
 * is returned. If the lookup fails, a status of zero is returned.
E 20
I 20
 * Lookup is called with dvp pointing to the directory to search,
 * cnp pointing to the name of the entry being sought. If the lookup
 * succeeds, the vnode is returned in *vpp, and a status of -1 is
 * returned. If the lookup determines that the name does not exist
 * (negative cacheing), a status of ENOENT is returned. If the lookup
 * fails, a status of zero is returned.
E 20
E 4
 */
I 20

E 20
D 4
struct vnode *
E 4
D 9
cache_lookup(ndp)
	register struct nameidata *ndp;
E 9
I 9
int
D 10
cache_lookup(dvp, vpp, cnp)      /* converted to CN.  NEEDSWORK: do callers */
/* old: cache_lookup(ndp) */
E 10
I 10
cache_lookup(dvp, vpp, cnp)
E 10
	struct vnode *dvp;
	struct vnode **vpp;
	struct componentname *cnp;
E 9
{
D 4
	register struct vnode *dp;
E 4
I 4
D 9
	register struct vnode *dvp;
E 9
E 4
D 13
	register struct namecache *ncp;
	union nchash *nhp;
E 13
I 13
D 19
	register struct namecache *ncp, *ncq, **ncpp;
E 19
I 19
D 20
	register struct namecache *ncp;
E 20
I 20
	register struct namecache *ncp, *nnp;
E 20
	register struct nchashhead *ncpp;
E 19
E 13

I 3
D 4
	return (0);		/* XXX for now */
E 3
	if (ndp->ni_dent.d_namlen > NCHNAMLEN) {
E 4
I 4
D 18
	if (!doingcache)
E 18
I 18
	if (!doingcache) {
		cnp->cn_flags &= ~MAKEENTRY;
E 18
		return (0);
I 18
	}
E 18
D 9
	if (ndp->ni_namelen > NCHNAMLEN) {
E 9
I 9
	if (cnp->cn_namelen > NCHNAMLEN) {
E 9
E 4
		nchstats.ncs_long++;
D 9
		ndp->ni_makeentry = 0;
E 9
I 9
		cnp->cn_flags &= ~MAKEENTRY;
E 9
		return (0);
	}
D 4
	dp = ndp->ni_vp;
	nhp = &nchash[NHASH(dp)];
E 4
I 4
D 9
	dvp = ndp->ni_dvp;
D 5
	nhp = &nchash[NHASH(dvp, ndp->ni_hash)];
E 5
I 5
	nhp = &nchashtbl[ndp->ni_hash & nchash];
E 9
I 9
D 13
	nhp = &nchashtbl[cnp->cn_hash & nchash];
E 9
E 5
E 4
	for (ncp = nhp->nch_forw; ncp != (struct namecache *)nhp;
	    ncp = ncp->nc_forw) {
E 13
I 13
D 20
	ncpp = &nchashtbl[cnp->cn_hash & nchash];
D 19
	for (ncp = *ncpp; ncp; ncp = ncp->nc_forw) {
E 19
I 19
	for (ncp = ncpp->lh_first; ncp != 0; ncp = ncp->nc_hash.le_next) {
E 20
I 20

	ncpp = NCHHASH(dvp, cnp);
	for (ncp = ncpp->lh_first; ncp != 0; ncp = nnp) {
		nnp = ncp->nc_hash.le_next;
		/* If one of the vp's went stale, don't bother anymore. */
		if ((ncp->nc_dvpid != ncp->nc_dvp->v_id) ||
		    (ncp->nc_vp && ncp->nc_vpid != ncp->nc_vp->v_id)) {
			nchstats.ncs_falsehits++;
			PURGE(ncp);
			continue;
		}
		/* Now that we know the vp's to be valid, is it ours ? */
E 20
E 19
E 13
D 4
		if (ncp->nc_vp == dp &&
		    ncp->nc_nlen == ndp->ni_dent.d_namlen &&
		    !bcmp(ncp->nc_name, ndp->ni_dent.d_name,
			(unsigned)ncp->nc_nlen))
E 4
I 4
		if (ncp->nc_dvp == dvp &&
D 20
		    ncp->nc_dvpid == dvp->v_id &&
E 20
D 9
		    ncp->nc_nlen == ndp->ni_namelen &&
		    !bcmp(ncp->nc_name, ndp->ni_ptr, (unsigned)ncp->nc_nlen))
E 9
I 9
		    ncp->nc_nlen == cnp->cn_namelen &&
D 13
		    !bcmp(ncp->nc_name, cnp->cn_nameptr, (unsigned)ncp->nc_nlen))
E 13
I 13
		    !bcmp(ncp->nc_name, cnp->cn_nameptr, (u_int)ncp->nc_nlen))
E 13
E 9
E 4
			break;
	}
I 20

	/* We failed to find an entry */
E 20
D 13
	if (ncp == (struct namecache *)nhp) {
E 13
I 13
D 19
	if (ncp == NULL) {
E 19
I 19
	if (ncp == 0) {
E 19
E 13
		nchstats.ncs_miss++;
D 4
		ncp = NULL;
E 4
		return (0);
	}
I 20

	/* We don't want to have an entry, so dump it */
E 20
D 4
	if (ndp->ni_makeentry) {
E 4
I 4
D 9
	if (!ndp->ni_makeentry) {
E 9
I 9
D 19
	if (!(cnp->cn_flags & MAKEENTRY)) {
E 19
I 19
	if ((cnp->cn_flags & MAKEENTRY) == 0) {
E 19
E 9
		nchstats.ncs_badhits++;
D 20
	} else if (ncp->nc_vp == NULL) {
D 8
		nchstats.ncs_neghits++;
E 4
		/*
D 4
		 * move this slot to end of LRU
		 * chain, if not already there
E 4
I 4
		 * move this slot to end of LRU chain, if not already there
E 4
		 */
		if (ncp->nc_nxt) {
			/* remove from LRU chain */
			*ncp->nc_prev = ncp->nc_nxt;
			ncp->nc_nxt->nc_prev = ncp->nc_prev;
D 4

E 4
			/* and replace at end of it */
			ncp->nc_nxt = NULL;
			ncp->nc_prev = nchtail;
			*nchtail = ncp;
			nchtail = &ncp->nc_nxt;
E 8
I 8
D 9
		if ((ndp->ni_nameiop & OPMASK) != CREATE) {
E 9
I 9
D 10
		if ((cnp->cn_nameiop & OPMASK) != CREATE) {
E 10
I 10
		if (cnp->cn_nameiop != CREATE) {
E 10
E 9
			nchstats.ncs_neghits++;
			/*
			 * Move this slot to end of LRU chain,
			 * if not already there.
			 */
D 19
			if (ncp->nc_nxt) {
				/* remove from LRU chain */
				*ncp->nc_prev = ncp->nc_nxt;
				ncp->nc_nxt->nc_prev = ncp->nc_prev;
				/* and replace at end of it */
				ncp->nc_nxt = NULL;
				ncp->nc_prev = nchtail;
				*nchtail = ncp;
				nchtail = &ncp->nc_nxt;
E 19
I 19
			if (ncp->nc_lru.tqe_next != 0) {
				TAILQ_REMOVE(&nclruhead, ncp, nc_lru);
				TAILQ_INSERT_TAIL(&nclruhead, ncp, nc_lru);
E 19
			}
			return (ENOENT);
E 8
		}
D 4
		/* ndp->ni_dent.d_ino = dp->i_number; */
		/* ni_dent.d_reclen is garbage ... */
E 4
I 4
D 8
		return (ENOENT);
E 8
	} else if (ncp->nc_vpid != ncp->nc_vp->v_id) {
		nchstats.ncs_falsehits++;
	} else {
E 20
I 20
		PURGE(ncp);
		return (0);
	} 

	/* We found a "positive" match, return the vnode */
        if (ncp->nc_vp) {
E 20
E 4
		nchstats.ncs_goodhits++;
D 4
		return (ncp->nc_vp);
E 4
I 4
D 20
		/*
		 * move this slot to end of LRU chain, if not already there
		 */
D 19
		if (ncp->nc_nxt) {
			/* remove from LRU chain */
			*ncp->nc_prev = ncp->nc_nxt;
			ncp->nc_nxt->nc_prev = ncp->nc_prev;
			/* and replace at end of it */
			ncp->nc_nxt = NULL;
			ncp->nc_prev = nchtail;
			*nchtail = ncp;
			nchtail = &ncp->nc_nxt;
E 19
I 19
		if (ncp->nc_lru.tqe_next != 0) {
			TAILQ_REMOVE(&nclruhead, ncp, nc_lru);
			TAILQ_INSERT_TAIL(&nclruhead, ncp, nc_lru);
E 19
		}
E 20
I 20
		TOUCH(ncp);
E 20
D 9
		ndp->ni_vp = ncp->nc_vp;
E 9
I 9
		*vpp = ncp->nc_vp;
E 9
		return (-1);
E 4
	}

D 20
	/*
	 * Last component and we are renaming or deleting,
	 * the cache entry is invalid, or otherwise don't
	 * want cache entry to exist.
	 */
D 4
	nchstats.ncs_badhits++;
E 4
D 19
	/* remove from LRU chain */
D 13
	*ncp->nc_prev = ncp->nc_nxt;
	if (ncp->nc_nxt)
		ncp->nc_nxt->nc_prev = ncp->nc_prev;
E 13
I 13
	if (ncq = ncp->nc_nxt)
		ncq->nc_prev = ncp->nc_prev;
E 13
	else
		nchtail = ncp->nc_prev;
I 13
	*ncp->nc_prev = ncq;
E 13
D 4
	remque(ncp);		/* remove from hash chain */
E 4
I 4
	/* remove from hash chain */
D 13
	remque(ncp);
E 13
I 13
	if (ncq = ncp->nc_forw)
		ncq->nc_back = ncp->nc_back;
	*ncp->nc_back = ncq;
	/* and make a dummy hash chain */
	ncp->nc_forw = NULL;
	ncp->nc_back = NULL;
E 13
E 4
	/* insert at head of LRU list (first to grab) */
D 15
	ncp->nc_nxt = nchhead;
	ncp->nc_prev = &nchhead;
	nchhead->nc_prev = &ncp->nc_nxt;
E 15
I 15
	if (ncq = nchhead)
		ncq->nc_prev = &ncp->nc_nxt;
	else
		nchtail = &ncp->nc_nxt;
E 15
	nchhead = ncp;
I 15
	ncp->nc_nxt = ncq;
	ncp->nc_prev = &nchhead;
E 19
I 19
	TAILQ_REMOVE(&nclruhead, ncp, nc_lru);
	LIST_REMOVE(ncp, nc_hash);
	ncp->nc_hash.le_prev = 0;
	TAILQ_INSERT_HEAD(&nclruhead, ncp, nc_lru);
E 19
E 15
D 13
	/* and make a dummy hash chain */
	ncp->nc_forw = ncp;
	ncp->nc_back = ncp;
E 13
D 4
	ncp = NULL;
E 4
	return (0);
E 20
I 20
	/* We found a negative match, and want to create it, so purge */
	if (cnp->cn_nameiop == CREATE) {
		nchstats.ncs_badhits++;
		PURGE(ncp);
		return (0);
	}

D 21
	/* We found a "negative" match, ENOENT notifies client of this match */
E 21
I 21
	/*
	 * We found a "negative" match, ENOENT notifies client of this match.
	 * The nc_vpid field records whether this is a whiteout.
	 */
E 21
	nchstats.ncs_neghits++;
	TOUCH(ncp);
I 21
	cnp->cn_flags |= ncp->nc_vpid;
E 21
	return (ENOENT);
E 20
}

/*
D 20
 * Add an entry to the cache
E 20
I 20
 * Add an entry to the cache.
E 20
 */
I 20
void
E 20
D 9
cache_enter(ndp)
	register struct nameidata *ndp;
E 9
I 9
D 10
cache_enter(dvp, vp, cnp)      /* converted to CN.  NEEDSWORK: do callers */
/* old: cache_lookup(ndp) */
E 10
I 10
cache_enter(dvp, vp, cnp)
E 10
	struct vnode *dvp;
	struct vnode *vp;
	struct componentname *cnp;
E 9
{
D 13
	register struct namecache *ncp;
	union nchash *nhp;
E 13
I 13
D 19
	register struct namecache *ncp, *ncq, **ncpp;
E 19
I 19
	register struct namecache *ncp;
	register struct nchashhead *ncpp;
E 19
E 13

I 20
	if (!doingcache)
		return;

E 20
I 12
#ifdef DIAGNOSTIC
	if (cnp->cn_namelen > NCHNAMLEN)
		panic("cache_enter: name too long");
#endif
E 12
I 3
D 4
	return;		/* XXX for now */
E 4
I 4
D 20
	if (!doingcache)
		return;
E 20
I 20

E 20
E 4
E 3
	/*
D 20
	 * Free the cache slot at head of lru chain.
E 20
I 20
	 * We allocate a new entry if we are less than the maximum
	 * allowed and the one at the front of the LRU list is in use.
	 * Otherwise we use the one at the front of the LRU list.
E 20
	 */
D 5
	if (ncp = nchhead) {
E 5
I 5
D 20
	if (numcache < desiredvnodes) {
E 20
I 20
	if (numcache < desiredvnodes &&
	    ((ncp = nclruhead.tqh_first) == NULL ||
	    ncp->nc_hash.le_prev != 0)) {
		/* Add one more entry */
E 20
		ncp = (struct namecache *)
D 7
			malloc(sizeof *ncp, M_CACHE, M_WAITOK);
E 7
I 7
			malloc((u_long)sizeof *ncp, M_CACHE, M_WAITOK);
E 7
		bzero((char *)ncp, sizeof *ncp);
		numcache++;
D 19
	} else if (ncp = nchhead) {
E 5
		/* remove from lru chain */
D 13
		*ncp->nc_prev = ncp->nc_nxt;
		if (ncp->nc_nxt)
			ncp->nc_nxt->nc_prev = ncp->nc_prev;
E 13
I 13
		if (ncq = ncp->nc_nxt)
			ncq->nc_prev = ncp->nc_prev;
E 13
		else
			nchtail = ncp->nc_prev;
I 13
		*ncp->nc_prev = ncq;
E 13
D 4
		remque(ncp);		/* remove from old hash chain */
E 4
I 4
D 14
		/* remove from old hash chain */
D 13
		remque(ncp);
E 13
I 13
		if (ncq = ncp->nc_forw)
			ncq->nc_back = ncp->nc_back;
		*ncp->nc_back = ncq;
E 14
I 14
		/* remove from old hash chain, if on one */
		if (ncp->nc_back) {
			if (ncq = ncp->nc_forw)
				ncq->nc_back = ncp->nc_back;
			*ncp->nc_back = ncq;
			ncp->nc_forw = NULL;
			ncp->nc_back = NULL;
E 19
I 19
	} else if (ncp = nclruhead.tqh_first) {
I 20
		/* reuse an old entry */
E 20
		TAILQ_REMOVE(&nclruhead, ncp, nc_lru);
		if (ncp->nc_hash.le_prev != 0) {
			LIST_REMOVE(ncp, nc_hash);
			ncp->nc_hash.le_prev = 0;
E 19
		}
E 14
E 13
E 4
D 5
		/* grab the inode we just found */
		ncp->nc_vp = ndp->ni_vp;
I 4
		if (ndp->ni_vp)
			ncp->nc_vpid = ndp->ni_vp->v_id;
		else
			ncp->nc_vpid = 0;
E 4
		/* fill in cache info */
D 4
		ncp->nc_dp = ndp->ni_dvp;	/* parents vnode */
		ncp->nc_nlen = ndp->ni_dent.d_namlen;
		bcopy(ndp->ni_dent.d_name, ncp->nc_name,
		    (unsigned)ncp->nc_nlen);
E 4
I 4
		ncp->nc_dvp = ndp->ni_dvp;
		ncp->nc_dvpid = ndp->ni_dvp->v_id;
		ncp->nc_nlen = ndp->ni_namelen;
		bcopy(ndp->ni_ptr, ncp->nc_name, (unsigned)ncp->nc_nlen);
E 4
		/* link at end of lru chain */
		ncp->nc_nxt = NULL;
		ncp->nc_prev = nchtail;
		*nchtail = ncp;
		nchtail = &ncp->nc_nxt;
		/* and insert on hash chain */
D 4
		nhp = &nchash[NHASH(ndp->ni_vp)];
E 4
I 4
		nhp = &nchash[NHASH(ndp->ni_vp, ndp->ni_hash)];
E 4
		insque(ncp, nhp);
	}
E 5
I 5
D 20
	} else
E 20
I 20
	} else {
		/* give up */
E 20
		return;
D 20
	/* grab the vnode we just found */
E 20
I 20
	}

D 21
	/* fill in cache info, if vp is NULL this is a "negative" cache entry */
E 21
I 21
	/*
	 * Fill in cache info, if vp is NULL this is a "negative" cache entry.
	 * For negative entries, we have to record whether it is a whiteout.
	 * the whiteout flag is stored in the nc_vpid field which is
	 * otherwise unused.
	 */
E 21
E 20
D 9
	ncp->nc_vp = ndp->ni_vp;
	if (ndp->ni_vp)
		ncp->nc_vpid = ndp->ni_vp->v_id;
E 9
I 9
	ncp->nc_vp = vp;
	if (vp)
		ncp->nc_vpid = vp->v_id;
E 9
	else
D 21
		ncp->nc_vpid = 0;
E 21
I 21
		ncp->nc_vpid = cnp->cn_flags & ISWHITEOUT;
E 21
D 20
	/* fill in cache info */
E 20
D 9
	ncp->nc_dvp = ndp->ni_dvp;
	ncp->nc_dvpid = ndp->ni_dvp->v_id;
	ncp->nc_nlen = ndp->ni_namelen;
	bcopy(ndp->ni_ptr, ncp->nc_name, (unsigned)ncp->nc_nlen);
E 9
I 9
	ncp->nc_dvp = dvp;
	ncp->nc_dvpid = dvp->v_id;
	ncp->nc_nlen = cnp->cn_namelen;
	bcopy(cnp->cn_nameptr, ncp->nc_name, (unsigned)ncp->nc_nlen);
E 9
D 19
	/* link at end of lru chain */
	ncp->nc_nxt = NULL;
	ncp->nc_prev = nchtail;
	*nchtail = ncp;
	nchtail = &ncp->nc_nxt;
	/* and insert on hash chain */
E 19
I 19
	TAILQ_INSERT_TAIL(&nclruhead, ncp, nc_lru);
E 19
D 9
	nhp = &nchashtbl[ndp->ni_hash & nchash];
E 9
I 9
D 13
	nhp = &nchashtbl[cnp->cn_hash & nchash];
E 9
	insque(ncp, nhp);
E 13
I 13
D 20
	ncpp = &nchashtbl[cnp->cn_hash & nchash];
E 20
I 20
	ncpp = NCHHASH(dvp, cnp);
E 20
D 19
	if (ncq = *ncpp)
		ncq->nc_back = &ncp->nc_forw;
	ncp->nc_forw = ncq;
	ncp->nc_back = ncpp;
	*ncpp = ncp;
E 19
I 19
	LIST_INSERT_HEAD(ncpp, ncp, nc_hash);
E 19
E 13
E 5
}

/*
D 5
 * Name cache initialization, from main() when we are booting
E 5
I 5
 * Name cache initialization, from vfs_init() when we are booting
E 5
 */
I 20
void
E 20
nchinit()
{
D 13
	register union nchash *nchp;
D 5
	register struct namecache *ncp;
E 5
I 5
	long nchashsize;
E 13
E 5

D 13
	nchhead = 0;
E 13
D 19
	nchtail = &nchhead;
E 19
I 19
	TAILQ_INIT(&nclruhead);
E 19
D 5
	for (ncp = namecache; ncp < &namecache[nchsize]; ncp++) {
		ncp->nc_forw = ncp;			/* hash chain */
		ncp->nc_back = ncp;
		ncp->nc_nxt = NULL;			/* lru chain */
		*nchtail = ncp;
		ncp->nc_prev = nchtail;
		nchtail = &ncp->nc_nxt;
		/* all else is zero already */
	}
	for (nchp = nchash; nchp < &nchash[NCHHASH]; nchp++) {
E 5
I 5
D 13
	nchashsize = roundup((desiredvnodes + 1) * sizeof *nchp / 2,
		NBPG * CLSIZE);
D 7
	nchashtbl = (union nchash *)malloc(nchashsize, M_CACHE, M_WAITOK);
E 7
I 7
	nchashtbl = (union nchash *)malloc((u_long)nchashsize,
	    M_CACHE, M_WAITOK);
E 7
	for (nchash = 1; nchash <= nchashsize / sizeof *nchp; nchash <<= 1)
D 11
		/* void */;
E 11
I 11
		continue;
E 11
	nchash = (nchash >> 1) - 1;
	for (nchp = &nchashtbl[nchash]; nchp >= nchashtbl; nchp--) {
E 5
		nchp->nch_head[0] = nchp;
		nchp->nch_head[1] = nchp;
	}
E 13
I 13
	nchashtbl = hashinit(desiredvnodes, M_CACHE, &nchash);
E 13
}

/*
D 20
 * Cache flush, a particular vnode; called when a vnode is renamed to
D 4
 * remove entries that would now be invalid
 *
 * The line "nxtcp = nchhead" near the end is to avoid potential problems
 * if the cache lru chain is modified while we are dumping the
 * inode.  This makes the algorithm O(n^2), but do you think I care?
E 4
I 4
 * hide entries that would now be invalid
E 20
I 20
 * Invalidate a all entries to particular vnode.
 * 
 * We actually just increment the v_id, that will do it. The entries will
 * be purged by lookup as they get found. If the v_id wraps around, we
 * need to ditch the entire cache, to avoid confusion. No valid vnode will
 * ever have (v_id == 0).
E 20
E 4
 */
I 20
void
E 20
cache_purge(vp)
D 4
	register struct vnode *vp;
E 4
I 4
	struct vnode *vp;
E 4
{
I 5
D 13
	union nchash *nhp;
E 5
D 4
	register struct namecache *ncp, *nxtcp;
E 4
I 4
	struct namecache *ncp;
E 13
I 13
D 19
	struct namecache *ncp, **ncpp;
E 19
I 19
	struct namecache *ncp;
	struct nchashhead *ncpp;
E 19
E 13
E 4

D 4
	for (ncp = nchhead; ncp; ncp = nxtcp) {
		nxtcp = ncp->nc_nxt;
		if (ncp->nc_vp == NULL || ncp->nc_vp != vp)
			continue;
		/* free the resources we had */
		ncp->nc_vp = NULL;
		ncp->nc_dp = NULL;
		remque(ncp);		/* remove entry from its hash chain */
		ncp->nc_forw = ncp;	/* and make a dummy one */
		ncp->nc_back = ncp;
		/* delete this entry from LRU chain */
		*ncp->nc_prev = nxtcp;
		if (nxtcp)
			nxtcp->nc_prev = ncp->nc_prev;
		else
			nchtail = ncp->nc_prev;
		/* cause rescan of list, it may have altered */
		nxtcp = nchhead;
		/* put the now-free entry at head of LRU */
		ncp->nc_nxt = nxtcp;
		ncp->nc_prev = &nchhead;
		nxtcp->nc_prev = &ncp->nc_nxt;
		nchhead = ncp;
E 4
I 4
	vp->v_id = ++nextvnodeid;
	if (nextvnodeid != 0)
		return;
D 5
	for (ncp = namecache; ncp < &namecache[nchsize]; ncp++) {
		ncp->nc_vpid = 0;
		ncp->nc_dvpid = 0;
E 5
I 5
D 13
	for (nhp = &nchashtbl[nchash]; nhp >= nchashtbl; nhp--) {
		for (ncp = nhp->nch_forw; ncp != (struct namecache *)nhp;
		    ncp = ncp->nc_forw) {
E 13
I 13
	for (ncpp = &nchashtbl[nchash]; ncpp >= nchashtbl; ncpp--) {
D 19
		for (ncp = *ncpp; ncp; ncp = ncp->nc_forw) {
E 19
I 19
D 20
		for (ncp = ncpp->lh_first; ncp != 0; ncp = ncp->nc_hash.le_next) {
E 19
E 13
			ncp->nc_vpid = 0;
			ncp->nc_dvpid = 0;
		}
E 20
I 20
		while (ncp = ncpp->lh_first)
			PURGE(ncp);
E 20
E 5
E 4
	}
I 4
	vp->v_id = ++nextvnodeid;
E 4
}

/*
D 20
 * Cache flush, a whole filesystem; called when filesys is umounted to
 * remove entries that would now be invalid
E 20
I 20
 * Flush all entries referencing a particular filesystem.
E 20
 *
D 20
 * The line "nxtcp = nchhead" near the end is to avoid potential problems
 * if the cache lru chain is modified while we are dumping the
 * inode.  This makes the algorithm O(n^2), but do you think I care?
E 20
I 20
 * Since we need to check it anyway, we will flush all the invalid
 * entriess at the same time.
E 20
 */
I 20
void
E 20
cache_purgevfs(mp)
D 7
	register struct mount *mp;
E 7
I 7
	struct mount *mp;
E 7
{
D 20
	register struct namecache *ncp, *nxtcp;
E 20
I 20
	struct nchashhead *ncpp;
	struct namecache *ncp, *nnp;
E 20

D 19
	for (ncp = nchhead; ncp; ncp = nxtcp) {
E 19
I 19
D 20
	for (ncp = nclruhead.tqh_first; ncp != 0; ncp = nxtcp) {
E 19
D 13
		nxtcp = ncp->nc_nxt;
D 4
		if (ncp->nc_vp == NULL || ncp->nc_vp->v_mount != mp)
E 4
I 4
		if (ncp->nc_dvp == NULL || ncp->nc_dvp->v_mount != mp)
E 13
I 13
		if (ncp->nc_dvp == NULL || ncp->nc_dvp->v_mount != mp) {
D 19
			nxtcp = ncp->nc_nxt;
E 19
I 19
			nxtcp = ncp->nc_lru.tqe_next;
E 19
E 13
E 4
			continue;
E 20
I 20
	/* Scan hash tables for applicable entries */
	for (ncpp = &nchashtbl[nchash]; ncpp >= nchashtbl; ncpp--) {
		for (ncp = ncpp->lh_first; ncp != 0; ncp = nnp) {
			nnp = ncp->nc_hash.le_next;
			if (ncp->nc_dvpid != ncp->nc_dvp->v_id ||
			    (ncp->nc_vp && ncp->nc_vpid != ncp->nc_vp->v_id) ||
			    ncp->nc_dvp->v_mount == mp) {
				PURGE(ncp);
			}
E 20
I 13
		}
E 13
D 20
		/* free the resources we had */
		ncp->nc_vp = NULL;
D 4
		ncp->nc_dp = NULL;
E 4
I 4
		ncp->nc_dvp = NULL;
E 4
D 13
		remque(ncp);		/* remove entry from its hash chain */
		ncp->nc_forw = ncp;	/* and make a dummy one */
		ncp->nc_back = ncp;
E 13
I 13
D 14
		/* remove entry from its hash chain */
		if (nxtcp = ncp->nc_forw)
			nxtcp->nc_back = ncp->nc_back;
		*ncp->nc_back = nxtcp;
		ncp->nc_forw = NULL;
		ncp->nc_back = NULL;
E 14
I 14
D 19
		/* remove from old hash chain, if on one */
		if (ncp->nc_back) {
			if (nxtcp = ncp->nc_forw)
				nxtcp->nc_back = ncp->nc_back;
			*ncp->nc_back = nxtcp;
			ncp->nc_forw = NULL;
			ncp->nc_back = NULL;
E 19
I 19
		TAILQ_REMOVE(&nclruhead, ncp, nc_lru);
		if (ncp->nc_hash.le_prev != 0) {
			LIST_REMOVE(ncp, nc_hash);
			ncp->nc_hash.le_prev = 0;
E 19
		}
E 14
E 13
D 19
		/* delete this entry from LRU chain */
D 13
		*ncp->nc_prev = nxtcp;
		if (nxtcp)
E 13
I 13
		if (nxtcp = ncp->nc_nxt)
E 13
			nxtcp->nc_prev = ncp->nc_prev;
		else
			nchtail = ncp->nc_prev;
I 13
		*ncp->nc_prev = nxtcp;
E 19
E 13
		/* cause rescan of list, it may have altered */
D 15
		nxtcp = nchhead;
		/* put the now-free entry at head of LRU */
E 15
I 15
D 19
		/* also put the now-free entry at head of LRU */
		if (nxtcp = nchhead)
			nxtcp->nc_prev = &ncp->nc_nxt;
		else
			nchtail = &ncp->nc_nxt;
		nchhead = ncp;
E 15
		ncp->nc_nxt = nxtcp;
		ncp->nc_prev = &nchhead;
E 19
I 19
		nxtcp = nclruhead.tqh_first;
		TAILQ_INSERT_HEAD(&nclruhead, ncp, nc_lru);
E 20
E 19
D 15
		nxtcp->nc_prev = &ncp->nc_nxt;
		nchhead = ncp;
E 15
	}
}
E 1
