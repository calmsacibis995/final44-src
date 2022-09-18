h31631
s 00002/00000/00227
d D 8.6 95/05/22 23:02:03 mckusick 62 61
c have to unlock node at end of inactive
e
s 00003/00053/00224
d D 8.5 95/05/14 00:32:22 mckusick 61 60
c no longer need nfs_lock* functions (use vop_nolock* instead)
e
s 00059/00034/00218
d D 8.4 95/03/30 11:26:34 mckusick 60 59
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00015/00031/00237
d D 8.3 94/08/18 23:33:39 mckusick 59 58
c conversion to queue.h list manipulation (from mycroft)
e
s 00001/00001/00267
d D 8.2 93/12/30 16:19:34 mckusick 58 57
c vget now locks optionally
e
s 00002/00002/00266
d D 8.1 93/06/10 23:38:42 bostic 57 56
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00266
d D 7.48 93/05/03 18:37:28 mckusick 56 55
c the final polish to leases from Rick Macklem
e
s 00001/00001/00266
d D 7.47 93/04/27 16:30:31 mckusick 55 54
c bug fixes for LEASES from Rick Macklem
e
s 00008/00001/00259
d D 7.46 93/02/02 15:04:00 mckusick 54 53
c update for 4.4BSD from Rick Macklem
e
s 00007/00000/00253
d D 7.45 92/11/14 23:32:25 mckusick 53 52
c have to wait for VXLOCK to clear
e
s 00014/00014/00239
d D 7.44 92/10/11 12:35:06 bostic 52 51
c make kernel includes standard
e
s 00002/00002/00251
d D 7.43 92/09/16 18:20:47 mckusick 51 50
c update from Rick Macklem
e
s 00018/00028/00235
d D 7.42 92/07/22 15:25:08 mckusick 50 49
c update to current hashing techniques
e
s 00033/00019/00230
d D 7.41 92/07/03 01:55:19 mckusick 49 48
c add parameter declarations; streamline unmarshalling
e
s 00003/00003/00246
d D 7.40 92/06/25 13:10:14 mckusick 48 47
c get rid of NOQUAD; nfs_removeit no longer takes a proc pointer
e
s 00013/00029/00236
d D 7.39 92/05/15 13:56:57 heideman 47 46
c vnodeop argument macro expansion
e
s 00030/00016/00235
d D 7.38 92/05/14 17:37:15 heideman 46 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/14 15:54:35 heideman 45 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/14 14:55:59 heideman 44 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/14 13:01:20 heideman 43 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/14 11:59:00 heideman 42 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/14 10:38:59 heideman 41 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/13 23:18:08 heideman 40 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/13 19:02:30 heideman 39 37
c vnode interface conversion
e
s 00030/00016/00235
d R 7.38 92/05/13 18:34:42 heideman 38 37
c vnode interface conversion
e
s 00006/00004/00245
d D 7.37 92/01/22 09:39:40 heideman 37 36
c lookup converted to new form
e
s 00028/00079/00221
d D 7.36 92/01/14 12:41:22 mckusick 36 35
c update from Rick Macklem (including leases)
e
s 00008/00007/00292
d D 7.35 91/12/16 17:26:32 mckusick 35 34
c allocate and free nfsnode private part; sillyrename now in nfsnode
e
s 00002/00000/00297
d D 7.34 91/05/15 20:20:33 mckusick 34 33
c nfs_abortop must free pathname buffer
e
s 00008/00002/00289
d D 7.33 91/05/08 21:48:22 mckusick 33 32
c enable the ability to avoid doing locking
e
s 00006/00007/00285
d D 7.32 91/04/19 18:35:45 mckusick 32 31
c redefine sillyrename structure to avoid use of nameidata structure
c (thus reducing its allocation size from 512 to 64 bytes)
e
s 00004/00002/00288
d D 7.31 91/04/16 00:39:31 mckusick 31 30
c add proc pointers to appropriate vnode operations
e
s 00006/00009/00284
d D 7.30 91/03/19 11:24:41 karels 30 29
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00001/00011/00292
d D 7.29 90/06/28 21:51:47 bostic 29 28
c new copyright notice
e
s 00002/00002/00301
d D 7.28 90/06/21 11:16:07 mckusick 28 27
c "update from Rick Macklem"
e
s 00007/00011/00296
d D 7.27 90/05/30 11:39:52 mckusick 27 26
c VOP_ABORTOP is no longer responsible for unlocking and vreleing vnodes
e
s 00003/00002/00304
d D 7.26 90/05/14 11:40:03 mckusick 26 25
c "update from Rick Macklem adding TCP support to NFS"
e
s 00000/00011/00306
d D 7.25 90/05/04 20:52:26 mckusick 25 24
c mount structure prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00000/00010/00317
d D 7.24 90/04/07 11:53:49 mckusick 24 23
c buffer invalidation is now handled by vclean
e
s 00001/00000/00326
d D 7.23 90/03/05 19:38:13 mckusick 23 22
c readdir fixes from Rick Macklem
e
s 00000/00002/00326
d D 7.22 90/02/17 10:27:51 mckusick 22 21
c get rid of unneeded header files
e
s 00007/00010/00321
d D 7.21 90/02/16 13:36:54 mckusick 21 20
c have to use generic routines as we may be crossing a mount point
e
s 00015/00002/00316
d D 7.20 90/01/15 18:35:34 mckusick 20 19
c lint; do nfs_lock explicitly; add nfs_islocked
e
s 00010/00000/00308
d D 7.19 90/01/14 11:26:52 mckusick 19 18
c debugging, track the holder and waiter for an nfsnode lock
e
s 00003/00005/00305
d D 7.18 90/01/04 22:11:06 mckusick 18 17
c v_blockh is split into clean and dirty lists
e
s 00002/00002/00308
d D 7.17 89/12/30 22:34:57 mckusick 17 16
c v_count => v_usecount
e
s 00010/00005/00300
d D 7.16 89/12/20 18:04:55 mckusick 16 15
c "December update from Rick Macklem"
e
s 00002/00004/00303
d D 7.15 89/11/30 22:53:17 mckusick 15 14
c use vprint in place of printf
e
s 00002/00002/00305
d D 7.14 89/11/22 19:29:26 mckusick 14 13
c lock/unlock use vnodes not nfsnodes
e
s 00004/00002/00303
d D 7.13 89/11/21 23:00:00 mckusick 13 12
c suppress printing of pushes of active vnodes
e
s 00008/00007/00297
d D 7.12 89/11/13 11:30:07 mckusick 12 11
c flush first, then remove from hashlist
e
s 00000/00029/00304
d D 7.11 89/11/10 12:44:14 mckusick 11 10
c nfs_nflush is replaced by the more general vflush
e
s 00002/00000/00331
d D 7.10 89/11/03 15:30:16 mckusick 10 9
c lint
e
s 00034/00059/00297
d D 7.9 89/10/29 23:56:26 mckusick 9 8
c nfs_ngrab is replaced by vget; flushing vnodes handled by vgone
e
s 00001/00002/00355
d D 7.8 89/10/25 17:19:57 mckusick 8 7
c must not clear NBUFFERED flag when inactive
e
s 00119/00169/00238
d D 7.7 89/10/24 19:52:55 mckusick 7 6
c merge inode and nfsnode tables into a single vnode table;
c link together all vnodes associated with a particular mount point
e
s 00000/00014/00407
d D 7.6 89/10/21 11:32:31 mckusick 6 5
c "bug fixes and cleanups from Rick Macklem"
e
s 00004/00007/00417
d D 7.5 89/10/19 22:33:23 mckusick 5 4
c "update from Rick Macklem"
e
s 00031/00013/00393
d D 7.4 89/08/30 20:29:54 macklem 4 3
c first buffer cache implementation; name cache usage; code cleanups
e
s 00003/00003/00403
d D 7.3 89/07/06 17:42:22 mckusick 3 2
c update of July 5th from Rick Macklem
e
s 00000/00006/00406
d D 7.2 89/07/05 11:38:13 mckusick 2 1
c dynamic allocation of nfsnode table
e
s 00412/00000/00000
d D 7.1 89/07/05 11:36:01 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 57
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 57
I 57
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 57
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 29
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
E 29
I 29
 * %sccs.include.redist.c%
E 29
 *
 *	%W% (Berkeley) %G%
 */

I 60

E 60
D 52
#include "param.h"
#include "systm.h"
D 30
#include "user.h"
E 30
#include "proc.h"
#include "mount.h"
I 31
#include "namei.h"
E 31
#include "vnode.h"
D 3
#include "dir.h"
E 3
I 3
D 22
#include "../ufs/dir.h"
E 3
#include "namei.h"
E 22
D 30
#include "errno.h"
E 30
I 30
#include "kernel.h"
#include "malloc.h"
E 52
I 52
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/vnode.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
E 52

I 36
D 52
#include "rpcv2.h"
E 36
E 30
#include "nfsv2.h"
#include "nfs.h"
#include "nfsnode.h"
#include "nfsmount.h"
I 36
#include "nqnfs.h"
E 52
I 52
#include <nfs/rpcv2.h>
D 60
#include <nfs/nfsv2.h>
E 60
I 60
#include <nfs/nfsproto.h>
E 60
#include <nfs/nfs.h>
#include <nfs/nfsnode.h>
#include <nfs/nfsmount.h>
#include <nfs/nqnfs.h>
E 52
E 36
D 30
#include "kernel.h"
#include "malloc.h"
E 30

D 50
/* The request list head */
extern struct nfsreq nfsreqh;
E 50
I 50
D 59
struct nfsnode **nheadhashtbl;
u_long nheadhash;
#define	NFSNOHASH(fhsum)	((fhsum)&nheadhash)
E 59
I 59
D 60
#define	NFSNOHASH(fhsum) \
	(&nfsnodehashtbl[(fhsum) & nfsnodehash])
E 60
LIST_HEAD(nfsnodehashhead, nfsnode) *nfsnodehashtbl;
u_long nfsnodehash;
E 59
E 50

D 2
/* Someday this should be dynamically sized like the inode table */
struct nfsnode nfsnd[2000];
struct nfsnode *nfsnode = &nfsnd[0];
struct nfsnode *nfsnodeNNFSNODE = &nfsnd[2000];
int nnfsnode = 2000;

E 2
D 50
#define	NFSNOHSZ	512
#if	((NFSNOHSZ&(NFSNOHSZ-1)) == 0)
#define	NFSNOHASH(fhsum)	((fhsum)&(NFSNOHSZ-1))
#else
#define	NFSNOHASH(fhsum)	(((unsigned)(fhsum))%NFSNOHSZ)
#endif

D 7
union nhead {				/* inode LRU cache, Chris Maltby */
E 7
I 7
union nhead {
E 7
	union  nhead *nh_head[2];
	struct nfsnode *nh_chain[2];
} nhead[NFSNOHSZ];

E 50
D 7
struct nfsnode *nfreeh, **nfreet;

E 7
I 4
#define TRUE	1
#define	FALSE	0

E 4
/*
 * Initialize hash links for nfsnodes
 * and build nfsnode free list.
 */
I 60
void
E 60
nfs_nhinit()
{
D 50
	register int i;
D 7
	register struct nfsnode *np = nfsnode;
E 7
	register union  nhead *nh = nhead;
E 50

I 10
#ifndef lint
E 10
I 7
D 35
	if (VN_MAXPRIVATE < sizeof(struct nfsnode))
		panic("nfs_nhinit: too small");
E 35
I 35
	if ((sizeof(struct nfsnode) - 1) & sizeof(struct nfsnode))
		printf("nfs_nhinit: bad size %d\n", sizeof(struct nfsnode));
E 35
I 10
#endif /* not lint */
E 10
E 7
D 50
	for (i = NFSNOHSZ; --i >= 0; nh++) {
		nh->nh_head[0] = nh;
		nh->nh_head[1] = nh;
	}
E 50
I 50
D 59
	nheadhashtbl = hashinit(desiredvnodes, M_NFSNODE, &nheadhash);
E 59
I 59
	nfsnodehashtbl = hashinit(desiredvnodes, M_NFSNODE, &nfsnodehash);
E 59
E 50
D 7
	nfreeh = np;
	nfreet = &np->n_freef;
	np->n_freeb = &nfreeh;
	np->n_forw = np;
	np->n_back = np;
	NFSTOV(np)->v_data = (qaddr_t)np;
I 4
	NFSTOV(np)->v_type = VNON;
E 4
	for (i = nnfsnode; --i > 0; ) {
		++np;
		np->n_forw = np;
		np->n_back = np;
		NFSTOV(np)->v_data = (qaddr_t)np;
I 4
		NFSTOV(np)->v_type = VNON;
E 4
		*nfreet = np;
		np->n_freeb = nfreet;
		nfreet = &np->n_freef;
	}
	np->n_freef = NULL;
E 7
}

/*
I 9
 * Compute an entry in the NFS hash table structure
 */
D 50
union nhead *
E 50
I 50
D 59
struct nfsnode **
E 59
I 59
D 60
struct nfsnodehashhead *
E 59
E 50
nfs_hash(fhp)
	register nfsv2fh_t *fhp;
E 60
I 60
u_long
nfs_hash(fhp, fhsize)
	register nfsfh_t *fhp;
	int fhsize;
E 60
{
	register u_char *fhpp;
	register u_long fhsum;
D 60
	int i;
E 60
I 60
	register int i;
E 60

	fhpp = &fhp->fh_bytes[0];
	fhsum = 0;
D 60
	for (i = 0; i < NFSX_FH; i++)
E 60
I 60
	for (i = 0; i < fhsize; i++)
E 60
		fhsum += *fhpp++;
D 50
	return (&nhead[NFSNOHASH(fhsum)]);
E 50
I 50
D 59
	return (&nheadhashtbl[NFSNOHASH(fhsum)]);
E 59
I 59
D 60
	return (NFSNOHASH(fhsum));
E 60
I 60
	return (fhsum);
E 60
E 59
E 50
}

/*
E 9
D 7
 * Look up an vnode/nfsnode by file handle.
E 7
I 7
 * Look up a vnode/nfsnode by file handle.
E 7
 * Callers must check for mount points!!
 * In all cases, a pointer to a
 * nfsnode structure is returned.
 */
D 60
nfs_nget(mntp, fhp, npp)
E 60
I 60
int
nfs_nget(mntp, fhp, fhsize, npp)
E 60
	struct mount *mntp;
D 60
	register nfsv2fh_t *fhp;
E 60
I 60
	register nfsfh_t *fhp;
	int fhsize;
E 60
	struct nfsnode **npp;
{
D 50
	register struct nfsnode *np;
E 50
I 50
D 59
	register struct nfsnode *np, *nq, **nhpp;
E 59
I 59
D 61
	register struct nfsnode *np;
E 61
I 61
	struct proc *p = curproc;	/* XXX */
	struct nfsnode *np;
E 61
	struct nfsnodehashhead *nhpp;
E 59
E 50
	register struct vnode *vp;
D 7
	register struct nfsnode *nq;
E 7
D 9
	register u_char *fhpp;
	register u_long fhsum;
E 9
I 9
D 46
	extern struct vnodeops nfsv2_vnodeops;
E 46
I 46
	extern int (**nfsv2_vnodeop_p)();
E 46
E 9
D 7
	register int i;
	union  nhead *nh;
	int error;
E 7
I 7
	struct vnode *nvp;
D 50
	union nhead *nh;
E 50
D 9
	int i, error;
E 9
I 9
	int error;
E 9
E 7

D 9
	fhpp = &fhp->fh_bytes[0];
	fhsum = 0;
	for (i = 0; i < NFSX_FH; i++)
		fhsum += *fhpp++;
E 9
I 9
D 50
	nh = nfs_hash(fhp);
E 50
I 50
D 60
	nhpp = nfs_hash(fhp);
E 60
I 60
	nhpp = NFSNOHASH(nfs_hash(fhp, fhsize));
E 60
E 50
E 9
loop:
D 9
	nh = &nhead[NFSNOHASH(fhsum)];
E 9
D 4
	for (np = nh->nh_chain[0]; np != (struct nfsnode *)nh; np = np->n_forw)
E 4
I 4
D 50
	for (np = nh->nh_chain[0]; np != (struct nfsnode *)nh; np = np->n_forw) {
E 50
I 50
D 59
	for (np = *nhpp; np; np = np->n_forw) {
E 59
I 59
	for (np = nhpp->lh_first; np != 0; np = np->n_hash.le_next) {
E 59
E 50
E 4
D 7
		if (mntp == NFSTOV(np)->v_mount &&
		    !bcmp((caddr_t)fhp, (caddr_t)&np->n_fh, NFSX_FH)) {
			/*
			 * Following is essentially an inline expanded
			 * copy of ngrab(), expanded inline for speed,
			 * and so that the test for a mounted on nfsnode
			 * can be deferred until after we are sure that
			 * the nfsnode isn't busy.
			 */
			if ((np->n_flag & NLOCKED) != 0) {
				np->n_flag |= NWANT;
				sleep((caddr_t)np, PINOD);
				goto loop;
			}
			vp = NFSTOV(np);
			if (vp->v_count == 0) {		/* nfsno on free list */
				if (nq = np->n_freef)
					nq->n_freeb = np->n_freeb;
				else
					nfreet = np->n_freeb;
				*np->n_freeb = nq;
				np->n_freef = NULL;
				np->n_freeb = NULL;
			}
			np->n_flag |= NLOCKED;
D 3
			vp->v_count++;
E 3
I 3
			VREF(vp);
E 3
			*npp = np;
			return(0);
E 7
I 7
D 60
		if (mntp != NFSTOV(np)->v_mount ||
		    bcmp((caddr_t)fhp, (caddr_t)&np->n_fh, NFSX_FH))
E 60
I 60
		if (mntp != NFSTOV(np)->v_mount || np->n_fhsize != fhsize ||
		    bcmp((caddr_t)fhp, (caddr_t)np->n_fhp, fhsize))
E 60
			continue;
D 9
		/*
		 * Following is essentially an inline expanded
		 * copy of ngrab(), expanded inline for speed,
		 * and so that the test for a mounted on nfsnode
		 * can be deferred until after we are sure that
		 * the nfsnode isn't busy.
		 */
E 9
D 36
		if ((np->n_flag & NLOCKED) != 0) {
			np->n_flag |= NWANT;
D 28
			sleep((caddr_t)np, PINOD);
E 28
I 28
			(void) tsleep((caddr_t)np, PINOD, "nfsnode", 0);
E 28
			goto loop;
E 7
		}
E 36
D 7

E 7
I 7
		vp = NFSTOV(np);
D 9
		if (vp->v_count == 0)	/* nfsnode on free list */
			vget(vp);
		else
			VREF(vp);
		np->n_flag |= NLOCKED;
E 9
I 9
D 58
		if (vget(vp))
E 58
I 58
D 61
		if (vget(vp, 1))
E 61
I 61
		if (vget(vp, LK_EXCLUSIVE, p))
E 61
E 58
			goto loop;
E 9
		*npp = np;
		return(0);
E 7
I 4
	}
E 4
D 7
	if ((np = nfreeh) == NULL) {
		tablefull("nfsnode");
E 7
I 7
D 46
	if (error = getnewvnode(VT_NFS, mntp, &nfsv2_vnodeops, &nvp)) {
E 46
I 46
D 60
	if (error = getnewvnode(VT_NFS, mntp, nfsv2_vnodeop_p, &nvp)) {
E 60
I 60
	error = getnewvnode(VT_NFS, mntp, nfsv2_vnodeop_p, &nvp);
	if (error) {
E 60
E 46
E 7
		*npp = 0;
D 7
		return(ENFILE);
E 7
I 7
		return (error);
E 7
	}
D 7
	vp = NFSTOV(np);
	if (vp->v_count)
		panic("free nfsnode isn't");
	if (nq = np->n_freef)
		nq->n_freeb = &nfreeh;
	nfreeh = nq;
	np->n_freef = NULL;
	np->n_freeb = NULL;
E 7
I 7
	vp = nvp;
D 35
	np = VTONFS(vp);
E 35
I 35
	MALLOC(np, struct nfsnode *, sizeof *np, M_NFSNODE, M_WAITOK);
I 60
	bzero((caddr_t)np, sizeof *np);
E 60
	vp->v_data = np;
E 35
	np->n_vnode = vp;
E 7
	/*
D 7
	 * Now to take nfsnode off the hash chain it was on
	 * (initially, or after an nflush, it is on a "hash chain"
	 * consisting entirely of itself, and pointed to by no-one,
D 4
	 * but that doesn't matter), and put it on the chain for
	 * its new file handle
E 4
I 4
	 * but that doesn't matter)
E 4
	 */
	remque(np);
I 4
	/*
	 * Flush out any associated bio buffers that might be lying about
	 */
D 5
	if (vp->v_type == VREG && (np->n_flag & NMODIFIED) == 0) {
E 5
I 5
	if (vp->v_type == VREG && (np->n_flag & NBUFFERED)) {
E 5
		np->n_flag |= NLOCKED;
		nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
	}
	/*
E 7
	 * Insert the nfsnode in the hash queue for its new file handle
	 */
D 20
	np->n_flag = NLOCKED;
E 20
I 20
D 60
	np->n_flag = 0;
E 60
E 20
E 4
D 50
	insque(np, nh);
E 50
I 50
D 59
	if (nq = *nhpp)
		nq->n_back = &np->n_forw;
	np->n_forw = nq;
	np->n_back = nhpp;
	*nhpp = np;
E 59
I 59
	LIST_INSERT_HEAD(nhpp, np, n_hash);
E 59
E 50
I 20
D 36
	nfs_lock(vp);
E 36
E 20
D 60
	bcopy((caddr_t)fhp, (caddr_t)&np->n_fh, NFSX_FH);
D 4
#ifdef notyet
E 4
I 4
D 6
#ifndef notyet
E 6
E 4
D 7
	cache_purge(vp);
E 7
D 6
#endif
E 6
D 4
	np->n_flag = NLOCKED;
E 4
	np->n_attrstamp = 0;
I 23
D 26
	np->n_direofstamp = 0;
E 26
I 26
	np->n_direofoffset = 0;
E 26
E 23
	np->n_sillyrename = (struct sillyrename *)0;
D 7
	np->n_id = ++nextnfsnodeid;
E 7
I 4
	np->n_size = 0;
I 51
	np->n_mtime = 0;
E 51
D 36
	np->n_mtime = 0;
E 36
I 36
	if (VFSTONFS(mntp)->nm_flag & NFSMNT_NQNFS) {
D 48
		ZEROQUAD(np->n_brev);
		ZEROQUAD(np->n_lrev);
E 48
I 48
		np->n_brev = 0;
		np->n_lrev = 0;
E 48
		np->n_expiry = (time_t)0;
D 59
		np->n_tnext = (struct nfsnode *)0;
E 59
I 59
		np->n_timer.cqe_next = (struct nfsnode *)0;
E 59
D 51
	} else
		np->n_mtime = 0;
E 51
I 51
	}
E 60
I 60
	if (fhsize > NFS_SMALLFH) {
		MALLOC(np->n_fhp, nfsfh_t *, fhsize, M_NFSBIGFH, M_WAITOK);
	} else
		np->n_fhp = &np->n_fh;
	bcopy((caddr_t)fhp, (caddr_t)np->n_fhp, fhsize);
	np->n_fhsize = fhsize;
E 60
E 51
E 36
E 4
D 9
	/*
	 * Initialize the associated vnode
	 */
E 9
D 7
	vinit(vp, mntp, VNON, &nfsv2_vnodeops);
E 7
	*npp = np;
	return (0);
}

I 60
int
E 60
D 9
/*
 * Convert a pointer to an nfsnode into a reference to an nfsnode.
 *
 * This is basically the internal piece of nget (after the
 * nfsnode pointer is located) but without the test for mounted
 * filesystems.  It is caller's responsibility to check that
 * the nfsnode pointer is valid.
 */
nfs_ngrab(np)
	register struct nfsnode *np;
{
	register struct vnode *vp = NFSTOV(np);

	while ((np->n_flag & NLOCKED) != 0) {
		np->n_flag |= NWANT;
		sleep((caddr_t)np, PINOD);
	}
D 7
	if (vp->v_count == 0) {		/* ino on free list */
		register struct nfsnode *nq;

		if (nq = np->n_freef)
			nq->n_freeb = np->n_freeb;
		else
			nfreet = np->n_freeb;
		*np->n_freeb = nq;
		np->n_freef = NULL;
		np->n_freeb = NULL;
	}
D 3
	vp->v_count++;
E 3
I 3
	VREF(vp);
E 7
I 7
	if (vp->v_count == 0)		/* ino on free list */
		vget(vp);
	else
		VREF(vp);
E 7
E 3
	np->n_flag |= NLOCKED;
}

E 9
D 31
nfs_inactive(vp)
E 31
I 31
D 46
nfs_inactive(vp, p)
E 31
	struct vnode *vp;
I 31
	struct proc *p;
E 46
I 46
D 49
nfs_inactive (ap)
	struct vop_inactive_args *ap;
E 49
I 49
nfs_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 62
		struct proc *a_p;
E 62
	} */ *ap;
E 49
D 47
#define vp (ap->a_vp)
#define p (ap->a_p)
E 47
E 46
E 31
{
	register struct nfsnode *np;
D 32
	register struct nameidata *ndp;
E 32
	register struct sillyrename *sp;
I 54
	struct proc *p = curproc;	/* XXX */
E 54
D 7
	register struct nfsreq *rep;
	struct nfsreq *rep2;
E 7
D 36
	struct nfsnode *dnp;
E 36
I 13
	extern int prtactive;
E 13
D 7
	int s;
E 7

D 7
	if (vp == NULL)
		panic("nfs_inactive NULL vp");
	if (vp->v_count == 0) {
		np = VTONFS(vp);
I 5
		nfs_lock(vp);
E 5
D 4
		np->n_flag |= NLOCKED;
		if (np->n_sillyrename) {
E 4
I 4
		sp = np->n_sillyrename;
		np->n_sillyrename = (struct sillyrename *)0;
D 5
		nfs_lock(vp);
E 5
		if (sp) {
D 5
printf("in silltren inact\n");
E 5
E 4
			/*
			 * Remove the silly file that was rename'd earlier
			 */
D 4
			sp = np->n_sillyrename;
E 4
			ndp = &sp->s_namei;
			if (!nfs_nget(vp->v_mount, &sp->s_fh, &dnp)) {
I 4
D 5
printf("got the dir\n");
E 5
E 4
				ndp->ni_dvp = NFSTOV(dnp);
D 4
				if (sp->s_flag == REMOVE)
					nfs_removeit(ndp);
				else
					nfs_rmdirit(ndp);
E 4
I 4
				nfs_removeit(ndp);
E 4
				nfs_nput(ndp->ni_dvp);
			}
			crfree(ndp->ni_cred);
			free((caddr_t)sp, M_TEMP);
D 4
			np->n_sillyrename = (struct sillyrename *)0;
E 4
		}
		nfs_unlock(vp);
		np->n_flag = 0;
I 4
#ifdef notdef
E 7
I 7
D 9
	if (vp == NULL || vp->v_count != 0)
		panic("nfs_inactive: NULL or active vp");
E 9
D 47
	np = VTONFS(vp);
I 9
D 13
	if (vp->v_count != 0)
E 13
I 13
D 17
	if (prtactive && vp->v_count != 0)
E 17
I 17
	if (prtactive && vp->v_usecount != 0)
E 17
E 13
D 15
		printf("nfs_inactive: pushing active fileid %d fsid 0x%x\n",
			np->n_vattr.va_fileid, np->n_vattr.va_fsid);
E 15
I 15
		vprint("nfs_inactive: pushing active", vp);
E 47
I 47
	np = VTONFS(ap->a_vp);
	if (prtactive && ap->a_vp->v_usecount != 0)
		vprint("nfs_inactive: pushing active", ap->a_vp);
E 47
E 15
E 9
D 36
	nfs_lock(vp);
E 36
D 60
	sp = np->n_sillyrename;
E 60
I 60
	if (ap->a_vp->v_type != VDIR)
		sp = np->n_sillyrename;
	else
		sp = (struct sillyrename *)0;
E 60
	np->n_sillyrename = (struct sillyrename *)0;
	if (sp) {
E 7
E 4
		/*
D 7
		 * Scan the request list for any requests left hanging about
E 7
I 7
		 * Remove the silly file that was rename'd earlier
E 7
		 */
I 54
		(void) nfs_vinvalbuf(ap->a_vp, 0, sp->s_cred, p, 1);
E 54
D 7
		s = splnet();
		rep = nfsreqh.r_next;
D 5
		while (rep) {
E 5
I 5
		while (rep && rep != &nfsreqh) {
E 5
			if (rep->r_vp == vp) {
				rep->r_prev->r_next = rep2 = rep->r_next;
D 5
				if (rep->r_next != NULL)
					rep->r_next->r_prev = rep->r_prev;
E 5
I 5
				rep->r_next->r_prev = rep->r_prev;
E 5
				m_freem(rep->r_mreq);
				if (rep->r_mrep != NULL)
					m_freem(rep->r_mrep);
				free((caddr_t)rep, M_NFSREQ);
				rep = rep2;
			} else
				rep = rep->r_next;
E 7
I 7
D 32
		ndp = &sp->s_namei;
E 32
D 36
		if (!nfs_nget(vp->v_mount, &sp->s_fh, &dnp)) {
D 32
			ndp->ni_dvp = NFSTOV(dnp);
D 31
			nfs_removeit(ndp);
E 31
I 31
			nfs_removeit(ndp, p);
E 31
			nfs_nput(ndp->ni_dvp);
E 32
I 32
			sp->s_dvp = NFSTOV(dnp);
			nfs_removeit(sp, p);
			nfs_nput(sp->s_dvp);
E 32
E 7
		}
E 36
I 36
D 47
		nfs_removeit(sp, p);
E 47
I 47
D 48
		nfs_removeit(sp, ap->a_p);
E 48
I 48
		nfs_removeit(sp);
E 48
E 47
E 36
D 7
		splx(s);
E 7
I 7
D 32
		crfree(ndp->ni_cred);
		free((caddr_t)sp, M_TEMP);
E 32
I 32
		crfree(sp->s_cred);
		vrele(sp->s_dvp);
I 35
D 60
#ifdef SILLYSEPARATE
E 35
		free((caddr_t)sp, M_NFSREQ);
I 35
#endif
E 60
I 60
		FREE((caddr_t)sp, M_NFSREQ);
E 60
E 35
E 32
	}
D 36
	nfs_unlock(vp);
E 36
D 8
	np->n_flag = 0;
E 8
I 8
D 26
	np->n_flag &= NBUFFERED;
E 26
I 26
D 54
	np->n_flag &= NMODIFIED;
E 54
I 54
D 55
	np->n_flag &= (NMODIFIED | NFLUSHINPROG | NFLUSHWANT);
E 55
I 55
D 56
	np->n_flag &= (NMODIFIED | NFLUSHINPROG | NFLUSHWANT | NQNFSEVICTED);
E 56
I 56
	np->n_flag &= (NMODIFIED | NFLUSHINPROG | NFLUSHWANT | NQNFSEVICTED |
		NQNFSNONCACHE | NQNFSWRITE);
I 62
	VOP_UNLOCK(ap->a_vp, 0, ap->a_p);
E 62
E 56
E 55
E 54
E 26
E 8
D 36
#ifdef notdef
	/*
	 * Scan the request list for any requests left hanging about
	 */
	s = splnet();
	rep = nfsreqh.r_next;
	while (rep && rep != &nfsreqh) {
		if (rep->r_vp == vp) {
			rep->r_prev->r_next = rep2 = rep->r_next;
			rep->r_next->r_prev = rep->r_prev;
			m_freem(rep->r_mreq);
			if (rep->r_mrep != NULL)
				m_freem(rep->r_mrep);
			free((caddr_t)rep, M_NFSREQ);
			rep = rep2;
		} else
			rep = rep->r_next;
	}
	splx(s);
E 7
I 4
#endif
E 36
E 4
D 7
		/*
		 * Put the nfsnode on the end of the free list.
		 */
		if (nfreeh) {
			*nfreet = np;
			np->n_freeb = nfreet;
		} else {
			nfreeh = np;
			np->n_freeb = &nfreeh;
		}
		np->n_freef = NULL;
		nfreet = &np->n_freef;
E 7
I 7
	return (0);
}
I 46
D 47
#undef vp
#undef p
E 47
E 46

/*
 * Reclaim an nfsnode so that it can be used for other purposes.
 */
I 60
int
E 60
D 46
nfs_reclaim(vp)
	register struct vnode *vp;
E 46
I 46
D 49
nfs_reclaim (ap)
	struct vop_reclaim_args *ap;
E 49
I 49
nfs_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 49
D 47
#define vp (ap->a_vp)
E 47
E 46
{
D 47
	register struct nfsnode *np = VTONFS(vp);
I 36
	register struct nfsmount *nmp = VFSTONFS(vp->v_mount);
E 47
I 47
D 49
	register struct nfsnode *np = VTONFS(ap->a_vp);
	register struct nfsmount *nmp = VFSTONFS(ap->a_vp->v_mount);
E 49
I 49
	register struct vnode *vp = ap->a_vp;
	register struct nfsnode *np = VTONFS(vp);
	register struct nfsmount *nmp = VFSTONFS(vp->v_mount);
I 60
	register struct nfsdmap *dp, *dp2;
E 60
I 50
D 59
	register struct nfsnode *nq;
E 59
E 50
E 49
E 47
E 36
I 13
	extern int prtactive;
E 13

I 12
D 24
	/*
D 16
	 * Flush out any associated bio buffers that might be lying about
E 16
I 16
	 * Flush out any bio buffer or cmap references
E 16
	 */
D 16
	if (vp->v_type == VREG && (np->n_flag & NBUFFERED)) {
D 14
		nfs_lock(np);
E 14
I 14
		nfs_lock(vp);
E 14
		nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
D 14
		nfs_unlock(np);
E 14
I 14
		nfs_unlock(vp);
E 16
I 16
	if (vp->v_type == VREG) {
D 18
		if (vp->v_blockh) {
			nfs_lock(vp);
			vinvalbuf(vp, TRUE);
			nfs_unlock(vp);
		}
E 18
I 18
		nfs_lock(vp);
		vinvalbuf(vp, TRUE);
		nfs_unlock(vp);
E 18
		if (np->n_flag & NPAGEDON)
			mpurge(vp);
E 16
E 14
	}
E 24
E 12
D 13
	if (vp->v_count != 0)
E 13
I 13
D 17
	if (prtactive && vp->v_count != 0)
E 17
I 17
D 47
	if (prtactive && vp->v_usecount != 0)
E 17
E 13
D 9
		panic("nfs_reclaim: active inode");
E 9
I 9
D 15
		printf("nfs_reclaim: pushing active fileid %d fsid 0x%x\n",
			np->n_vattr.va_fileid, np->n_vattr.va_fsid);
E 15
I 15
		vprint("nfs_reclaim: pushing active", vp);
E 47
I 47
D 49
	if (prtactive && ap->a_vp->v_usecount != 0)
		vprint("nfs_reclaim: pushing active", ap->a_vp);
E 49
I 49
	if (prtactive && vp->v_usecount != 0)
		vprint("nfs_reclaim: pushing active", vp);
I 60

E 60
E 49
E 47
E 15
E 9
D 59
	/*
	 * Remove the nfsnode from its hash chain.
	 */
D 50
	remque(np);
E 50
I 50
	if (nq = np->n_forw)
		nq->n_back = np->n_back;
	*np->n_back = nq;
E 59
I 59
	LIST_REMOVE(np, n_hash);
E 59
E 50
I 36

	/*
	 * For nqnfs, take it off the timer queue as required.
	 */
D 59
	if ((nmp->nm_flag & NFSMNT_NQNFS) && np->n_tnext) {
		if (np->n_tnext == (struct nfsnode *)nmp)
			nmp->nm_tprev = np->n_tprev;
		else
			np->n_tnext->n_tprev = np->n_tprev;
		if (np->n_tprev == (struct nfsnode *)nmp)
			nmp->nm_tnext = np->n_tnext;
		else
			np->n_tprev->n_tnext = np->n_tnext;
	}
E 59
I 59
D 60
	if ((nmp->nm_flag & NFSMNT_NQNFS) && np->n_timer.cqe_next != 0)
E 60
I 60
	if ((nmp->nm_flag & NFSMNT_NQNFS) && np->n_timer.cqe_next != 0) {
E 60
		CIRCLEQ_REMOVE(&nmp->nm_timerhead, np, n_timer);
I 60
	}

	/*
	 * Free up any directory cookie structures and
	 * large file handle structures that might be associated with
	 * this nfs node.
	 */
	if (vp->v_type == VDIR) {
		dp = np->n_cookies.lh_first;
		while (dp) {
			dp2 = dp;
			dp = dp->ndm_list.le_next;
			FREE((caddr_t)dp2, M_NFSDIROFF);
		}
	}
	if (np->n_fhsize > NFS_SMALLFH) {
		FREE((caddr_t)np->n_fhp, M_NFSBIGFH);
	}

E 60
E 59
E 36
D 35
	np->n_forw = np;
	np->n_back = np;
E 35
D 47
	cache_purge(vp);
I 16
D 35
	np->n_flag = 0;
I 26
	np->n_direofoffset = 0;
E 35
I 35
	FREE(vp->v_data, M_NFSNODE);
D 36
	vp->v_data = NULL;
E 36
I 36
	vp->v_data = (void *)0;
E 47
I 47
D 49
	cache_purge(ap->a_vp);
	FREE(ap->a_vp->v_data, M_NFSNODE);
	ap->a_vp->v_data = (void *)0;
E 49
I 49
	cache_purge(vp);
	FREE(vp->v_data, M_NFSNODE);
	vp->v_data = (void *)0;
E 49
E 47
E 36
E 35
E 26
E 16
D 12
	/*
	 * Flush out any associated bio buffers that might be lying about
D 8
	 * XXX n_flags are set to zero by nfs_inactive.
E 8
	 */
	if (vp->v_type == VREG && (np->n_flag & NBUFFERED)) {
		np->n_flag |= NLOCKED;
		nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE);
E 7
	}
E 12
I 7
D 9
	vp->v_type = VNON;
E 9
E 7
D 61
	return (0);
}
I 46
D 47
#undef vp
E 47
E 46

/*
I 33
D 36
 * In theory, NFS does not need locking, but we make provision
 * for doing it just in case it is needed.
 */
int donfslocking = 0;
/*
E 36
E 33
D 11
 * Remove any nfsnodes in the nfsnode cache belonging to mount.
 *
 * There should not be any active ones, return error if any are found
 * (nb: this is a user error, not a system err).
 */
nfs_nflush(mntp)
	struct mount *mntp;
{
D 7
	register struct nfsnode *np;
E 7
D 9
	register struct vnode *vp;
E 9
I 9
	register struct vnode *nvp, *vp;
E 9
I 7
	int busy = 0;
E 7

D 7
	for (np = nfsnode; np < nfsnodeNNFSNODE; np++) {
		vp = NFSTOV(np);
		if (vp->v_mount == mntp)
			if (vp->v_count)
				return (EBUSY);
			else {
				remque(np);
				np->n_forw = np;
				np->n_back = np;
				/*
				 * as v_count == 0, the inode was on the free
				 * list already, just leave it there, it will
				 * fall off the bottom eventually. We could
				 * perhaps move it to the head of the free
				 * list, but as umounts are done so
				 * infrequently, we would gain very little,
				 * while making the code bigger.
				 */
			}
E 7
I 7
D 9
	for (vp = mntp->m_mounth; vp; vp = vp->v_mountf) {
E 9
I 9
	for (vp = mntp->m_mounth; vp; vp = nvp) {
		nvp = vp->v_mountf;
E 9
		if (vp->v_count) {
			busy++;
			continue;
		}
		/*
D 9
		 * As v_count == 0, the nfsnode was on the free list already,
		 * so it will fall off the bottom eventually.
		 * We could perhaps move it to the head of the free list,
		 * but as umounts are done so infrequently, we would gain
		 * very little, while making the code bigger.
E 9
I 9
		 * With v_count == 0, all we need to do is clear out the
		 * vnode data structures and we are done.
E 9
		 */
D 9
		nfs_reclaim(vp);
E 9
I 9
		vgone(vp);
E 9
E 7
	}
I 7
	if (busy)
		return (EBUSY);
E 7
	return (0);
}

/*
E 11
 * Lock an nfsnode
 */
I 60
int
E 60
I 33
D 36

E 36
E 33
D 46
nfs_lock(vp)
	struct vnode *vp;
E 46
I 46
D 49
nfs_lock (ap)
	struct vop_lock_args *ap;
E 49
I 49
nfs_lock(ap)
	struct vop_lock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 49
D 47
#define vp (ap->a_vp)
E 47
E 46
{
I 53
	register struct vnode *vp = ap->a_vp;
E 53
D 36
	register struct nfsnode *np = VTONFS(vp);
E 36

I 54
	/*
	 * Ugh, another place where interruptible mounts will get hung.
	 * If you make this sleep interruptible, then you have to fix all
	 * the VOP_LOCK() calls to expect interruptibility.
	 */
E 54
I 53
	while (vp->v_flag & VXLOCK) {
		vp->v_flag |= VXWANT;
D 60
		sleep((caddr_t)vp, PINOD);
E 60
I 60
		(void) tsleep((caddr_t)vp, PINOD, "nfslck", 0);
E 60
	}
	if (vp->v_tag == VT_NON)
		return (ENOENT);
E 53
I 33
D 36
	if (!donfslocking)
		return;
E 33
D 6
	if (np->n_flag & NLOCKED)
		printf("pid %d hit locked nfsnode=0x%x\n",
		    u.u_procp->p_pid, np);
E 6
	while (np->n_flag & NLOCKED) {
		np->n_flag |= NWANT;
I 19
D 30
		if (np->n_lockholder == u.u_procp->p_pid)
E 30
I 30
		if (np->n_lockholder == curproc->p_pid)
E 30
			panic("locking against myself");
D 30
		np->n_lockwaiter = u.u_procp->p_pid;
E 30
I 30
		np->n_lockwaiter = curproc->p_pid;
E 30
E 19
D 20
		sleep((caddr_t)np, PINOD);
E 20
I 20
D 28
		(void) sleep((caddr_t)np, PINOD);
E 28
I 28
		(void) tsleep((caddr_t)np, PINOD, "nfslock", 0);
E 28
E 20
	}
I 19
	np->n_lockwaiter = 0;
D 30
	np->n_lockholder = u.u_procp->p_pid;
	u.u_spare[0]++;
E 30
I 30
	np->n_lockholder = curproc->p_pid;
E 30
E 19
	np->n_flag |= NLOCKED;
E 36
I 36
	return (0);
E 36
}
I 46
D 47
#undef vp
E 47
E 46

/*
 * Unlock an nfsnode
 */
I 60
int
E 60
D 46
nfs_unlock(vp)
	struct vnode *vp;
E 46
I 46
D 49
nfs_unlock (ap)
	struct vop_unlock_args *ap;
E 49
I 49
nfs_unlock(ap)
	struct vop_unlock_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 49
D 47
#define vp (ap->a_vp)
E 47
E 46
{
D 36
	register struct nfsnode *np = VTONFS(vp);
E 36

I 19
D 33
	if ((np->n_flag & NLOCKED) == 0)
		vprint("nfs_unlock: unlocked nfsnode", vp);
E 33
D 36
	np->n_lockholder = 0;
D 30
	u.u_spare[0]--;
E 30
E 19
D 6
	if ((np->n_flag & NLOCKED) == 0) {
		printf("pid %d unlocking unlocked nfsnode=0x%x ",
		    u.u_procp->p_pid, np);
		printf("fh0=0x%x fh1=0x%x fh2=0x%x fh3=0x%x fh4=0x%x fh5=0x%x fh6=0x%x fh7=0x%x\n",
			np->n_fh.fh_bytes[0],np->n_fh.fh_bytes[1],
			np->n_fh.fh_bytes[2],np->n_fh.fh_bytes[3],
			np->n_fh.fh_bytes[4],np->n_fh.fh_bytes[5],
			np->n_fh.fh_bytes[6],np->n_fh.fh_bytes[7]);
	}
E 6
	np->n_flag &= ~NLOCKED;
	if (np->n_flag & NWANT) {
		np->n_flag &= ~NWANT;
		wakeup((caddr_t)np);
	}
E 36
I 36
	return (0);
E 36
I 20
}
I 46
D 47
#undef vp
E 47
E 46

/*
 * Check for a locked nfsnode
 */
I 60
int
E 60
D 46
nfs_islocked(vp)
	struct vnode *vp;
E 46
I 46
D 49
nfs_islocked (ap)
	struct vop_islocked_args *ap;
E 49
I 49
nfs_islocked(ap)
	struct vop_islocked_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 49
D 47
#define vp (ap->a_vp)
E 47
E 46
{

E 61
D 36
	if (VTONFS(vp)->n_flag & NLOCKED)
		return (1);
E 36
	return (0);
E 20
D 36
}

/*
 * Unlock and vrele()
 * since I can't decide if dirs. should be locked, I will check for
 * the lock and be flexible
 */
nfs_nput(vp)
	struct vnode *vp;
{
	register struct nfsnode *np = VTONFS(vp);

	if (np->n_flag & NLOCKED)
		nfs_unlock(vp);
	vrele(vp);
E 36
}
I 46
D 47
#undef vp
E 47
E 46

I 27
/*
 * Nfs abort op, called after namei() when a CREATE/DELETE isn't actually
 * done. Currently nothing to do.
 */
/* ARGSUSED */
E 27
D 37
nfs_abortop(ndp)
D 27
	register struct nameidata *ndp;
E 27
I 27
	struct nameidata *ndp;
E 37
I 37
int
D 46
nfs_abortop(dvp, cnp)
	struct vnode *dvp;
	struct componentname *cnp;
E 46
I 46
D 49
nfs_abortop (ap)
	struct vop_abortop_args *ap;
E 49
I 49
nfs_abortop(ap)
	struct vop_abortop_args /* {
		struct vnode *a_dvp;
		struct componentname *a_cnp;
	} */ *ap;
E 49
D 47
#define dvp (ap->a_dvp)
#define cnp (ap->a_cnp)
E 47
E 46
E 37
E 27
{
D 21
	register struct nfsnode *np;
E 21

I 34
D 37
	if ((ndp->ni_nameiop & (HASBUF | SAVESTART)) == HASBUF)
		FREE(ndp->ni_pnbuf, M_NAMEI);
E 37
I 37
D 47
	if ((cnp->cn_flags & (HASBUF | SAVESTART)) == HASBUF)
		FREE(cnp->cn_pnbuf, M_NAMEI);
E 47
I 47
	if ((ap->a_cnp->cn_flags & (HASBUF | SAVESTART)) == HASBUF)
		FREE(ap->a_cnp->cn_pnbuf, M_NAMEI);
E 47
E 37
E 34
D 21
	if (ndp->ni_vp != NULL) {
		np = VTONFS(ndp->ni_vp);
		if (np->n_flag & NLOCKED)
			nfs_unlock(ndp->ni_vp);
		vrele(ndp->ni_vp);
	}
E 21
D 27
	if (ndp->ni_dvp != NULL) {
D 21
		np = VTONFS(ndp->ni_dvp);
		if (np->n_flag & NLOCKED)
			nfs_unlock(ndp->ni_dvp);
E 21
I 21
		if (VOP_ISLOCKED(ndp->ni_dvp))
			VOP_UNLOCK(ndp->ni_dvp);
E 21
		vrele(ndp->ni_dvp);
I 21
	}
	if (ndp->ni_vp != NULL) {
		if (VOP_ISLOCKED(ndp->ni_vp))
			VOP_UNLOCK(ndp->ni_vp);
		vrele(ndp->ni_vp);
E 21
	}
E 27
I 27
	return (0);
E 27
}
I 46
D 47
#undef dvp
#undef cnp
E 47
E 46
D 25

/*
 * This is silly, but if you use a macro and try and use it in a file
 * that has mbuf.h included, m_data --> m_hdr.mh_data and this is not
 * a good thing
 */
struct nfsmount *vfs_to_nfs(mp)
	struct mount *mp;
{
	return ((struct nfsmount *)mp->m_data);
}
E 25
E 1
