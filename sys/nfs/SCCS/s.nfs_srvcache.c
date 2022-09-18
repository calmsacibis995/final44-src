h46178
s 00028/00022/00282
d D 8.3 95/03/30 11:26:33 mckusick 24 23
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00025/00043/00279
d D 8.2 94/08/18 23:33:38 mckusick 23 22
c conversion to queue.h list manipulation (from mycroft)
e
s 00002/00002/00320
d D 8.1 93/06/10 23:39:06 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00023/00309
d D 7.21 93/05/20 13:08:50 mckusick 21 20
c performance fixes from Rick Macklem
e
s 00002/00000/00330
d D 7.20 93/03/02 13:52:07 mckusick 20 19
c clear hash pointers when nfsd's terminate (from Macklem)
e
s 00001/00000/00329
d D 7.19 92/10/11 12:35:12 bostic 19 18
c make kernel includes standard
e
s 00004/00002/00325
d D 7.18 92/09/30 16:04:05 mckusick 18 17
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00001/00001/00326
d D 7.17 92/09/16 17:43:02 mckusick 17 16
c keep those hash chains and LRU chains separate
e
s 00062/00088/00265
d D 7.16 92/07/22 15:25:06 mckusick 16 15
c update to current hashing techniques
e
s 00017/00017/00336
d D 7.15 92/07/09 23:21:46 mckusick 15 14
c fix up include files
e
s 00002/00002/00351
d D 7.14 92/07/02 19:54:54 mckusick 14 13
c nfs_netaddr_match goes to vfs_addr.c
e
s 00001/00000/00352
d D 7.13 92/02/15 17:37:58 mckusick 13 12
c have to include proc before socketvar.h
e
s 00114/00036/00238
d D 7.12 92/01/14 12:41:21 mckusick 12 11
c update from Rick Macklem (including leases)
e
s 00001/00000/00273
d D 7.11 91/04/16 00:39:00 mckusick 11 10
c add include of namei.h
e
s 00002/00001/00271
d D 7.10 91/03/19 11:24:44 karels 10 9
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; consolidate *nullops()
e
s 00001/00011/00271
d D 7.9 90/06/28 21:52:34 bostic 9 8
c new copyright notice
e
s 00006/00000/00276
d D 7.8 90/06/22 16:21:31 mckusick 8 7
c add reference
e
s 00003/00003/00273
d D 7.7 90/06/21 11:18:36 mckusick 7 6
c "update from Rick Macklem"
e
s 00010/00013/00266
d D 7.6 90/05/14 11:43:40 mckusick 6 5
c "update from Rick Macklem adding TCP support to NFS"
e
s 00020/00010/00259
d D 7.5 90/03/01 14:13:08 mckusick 5 4
c delete cache entries on invalid replies
e
s 00001/00001/00268
d D 7.4 90/02/17 15:16:19 mckusick 4 3
c need to reference netinet as ../netinet
e
s 00001/00001/00268
d D 7.3 90/02/16 14:03:12 mckusick 3 2
c nonidempotent requests are needed elsewhere
e
s 00001/00000/00268
d D 7.2 89/12/20 18:56:31 mckusick 2 1
c need to include systm.h
e
s 00268/00000/00000
d D 7.1 89/12/20 11:56:27 mckusick 1 0
c from Rick Macklem
e
u
U
t
T
I 1
/*
D 22
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 9
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
 *
 *	%W% (Berkeley) %G%
 */

I 8
/*
 * Reference: Chet Juszczak, "Improving the Performance and Correctness
D 12
 *            of an NFS Server", in Proc. Winter 1989 USENIX Conference,
 *            pages 53-63. San Diego, February 1989.
E 12
I 12
 *		of an NFS Server", in Proc. Winter 1989 USENIX Conference,
 *		pages 53-63. San Diego, February 1989.
E 12
 */
D 12

E 12
E 8
D 15
#include "param.h"
I 11
D 12
#include "namei.h"
E 12
E 11
D 10
#include "user.h"
E 10
#include "vnode.h"
#include "mount.h"
#include "kernel.h"
I 2
#include "systm.h"
I 13
#include "proc.h"
E 13
E 2
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
I 10
D 12

E 10
D 4
#include "netinet/in.h"
E 4
I 4
#include "../netinet/in.h"
I 10

E 12
I 12
#include "netinet/in.h"
E 15
I 15
#include <sys/param.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
I 16
#include <sys/malloc.h>
E 16
#include <sys/socket.h>
#include <sys/socketvar.h>
I 19

E 19
#include <netinet/in.h>
E 15
#ifdef ISO
D 15
#include "netiso/iso.h"
E 15
I 15
#include <netiso/iso.h>
E 15
#endif
E 12
E 10
E 4
D 15
#include "nfsm_subs.h"
I 12
#include "rpcv2.h"
E 12
#include "nfsv2.h"
#include "nfsrvcache.h"
#include "nfs.h"
I 12
#include "nqnfs.h"
E 15
I 15
#include <nfs/nfsm_subs.h>
#include <nfs/rpcv2.h>
D 24
#include <nfs/nfsv2.h>
E 24
I 24
#include <nfs/nfsproto.h>
E 24
#include <nfs/nfs.h>
#include <nfs/nfsrvcache.h>
#include <nfs/nqnfs.h>
E 15
E 12

I 24
extern struct nfsstats nfsstats;
extern int nfsv2_procid[NFS_NPROCS];
E 24
D 16
#if	((NFSRCHSZ&(NFSRCHSZ-1)) == 0)
#define	NFSRCHASH(xid)		(((xid)+((xid)>>16))&(NFSRCHSZ-1))
#else
#define	NFSRCHASH(xid)		(((unsigned)((xid)+((xid)>>16)))%NFSRCHSZ)
#endif
E 16
I 16
long numnfsrvcache, desirednfsrvcache = NFSRVCACHESIZ;
E 16

D 16
union rhead {
	union  rhead *rh_head[2];
	struct nfsrvcache *rh_chain[2];
} rhead[NFSRCHSZ];
E 16
I 16
D 21
#define	NFSRCHASH(xid)		(((xid) + ((xid) >> 16)) & rheadhash)
E 21
I 21
D 23
#define	NFSRCHASH(xid)		(((xid) + ((xid) >> 24)) & rheadhash)
E 21
static struct nfsrvcache *nfsrvlruhead, **nfsrvlrutail = &nfsrvlruhead;
static struct nfsrvcache **rheadhtbl;
static u_long rheadhash;
E 23
I 23
#define	NFSRCHASH(xid) \
	(&nfsrvhashtbl[((xid) + ((xid) >> 24)) & nfsrvhash])
LIST_HEAD(nfsrvhash, nfsrvcache) *nfsrvhashtbl;
TAILQ_HEAD(nfsrvlru, nfsrvcache) nfsrvlruhead;
u_long nfsrvhash;
E 23
E 16

D 16
static struct nfsrvcache nfsrvcachehead;
static struct nfsrvcache nfsrvcache[NFSRVCACHESIZ];

E 16
#define TRUE	1
#define	FALSE	0

I 12
#define	NETFAMILY(rp) \
		(((rp)->rc_flag & RC_INETADDR) ? AF_INET : AF_ISO)

E 12
/*
 * Static array that defines which nfs rpc's are nonidempotent
 */
D 3
static int nonidempotent[NFS_NPROCS] = {
E 3
I 3
int nonidempotent[NFS_NPROCS] = {
E 3
	FALSE,
	FALSE,
	TRUE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
D 24
	FALSE,
E 24
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
I 24
	TRUE,
E 24
	FALSE,
	FALSE,
I 12
	FALSE,
	FALSE,
	FALSE,
	FALSE,
I 18
	FALSE,
I 24
	FALSE,
	FALSE,
	FALSE,
E 24
E 18
E 12
};

/* True iff the rpc reply is an nfs status ONLY! */
D 24
static int repliesstatus[NFS_NPROCS] = {
E 24
I 24
static int nfsv2_repstat[NFS_NPROCS] = {
E 24
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	TRUE,
	TRUE,
	TRUE,
	TRUE,
	FALSE,
	TRUE,
	FALSE,
	FALSE,
I 12
D 24
	FALSE,
	FALSE,
	FALSE,
	FALSE,
I 18
	TRUE,
E 24
E 18
E 12
};

/*
 * Initialize the server request cache list
 */
I 24
void
E 24
nfsrv_initcache()
{
D 16
	register int i;
	register struct nfsrvcache *rp = nfsrvcache;
	register struct nfsrvcache *hp = &nfsrvcachehead;
	register union  rhead *rh = rhead;
E 16

D 16
	for (i = NFSRCHSZ; --i >= 0; rh++) {
		rh->rh_head[0] = rh;
		rh->rh_head[1] = rh;
	}
	hp->rc_next = hp->rc_prev = hp;
	for (i = NFSRVCACHESIZ; i-- > 0; ) {
		rp->rc_state = RC_UNUSED;
		rp->rc_flag = 0;
		rp->rc_forw = rp;
		rp->rc_back = rp;
		rp->rc_next = hp->rc_next;
		hp->rc_next->rc_prev = rp;
		rp->rc_prev = hp;
		hp->rc_next = rp;
		rp++;
	}
E 16
I 16
D 23
	rheadhtbl = hashinit(desirednfsrvcache, M_NFSD, &rheadhash);
E 23
I 23
	nfsrvhashtbl = hashinit(desirednfsrvcache, M_NFSD, &nfsrvhash);
	TAILQ_INIT(&nfsrvlruhead);
E 23
E 16
}

/*
 * Look for the request in the cache
 * If found then
 *    return action and optionally reply
 * else
 *    insert it in the cache
 *
 * The rules are as follows:
 * - if in progress, return DROP request
 * - if completed within DELAY of the current time, return DROP it
 * - if completed a longer time ago return REPLY if the reply was cached or
 *   return DOIT
 * Update/add new request at end of lru list
 */
D 12
nfsrv_getcache(nam, xid, proc, repp)
E 12
I 12
D 24
nfsrv_getcache(nam, nd, repp)
E 12
	struct mbuf *nam;
D 12
	u_long xid;
	int proc;
E 12
I 12
	register struct nfsd *nd;
E 24
I 24
int
nfsrv_getcache(nd, slp, repp)
	register struct nfsrv_descript *nd;
	struct nfssvc_sock *slp;
E 24
E 12
	struct mbuf **repp;
{
D 16
	register struct nfsrvcache *rp;
	register union  rhead *rh;
E 16
I 16
D 23
	register struct nfsrvcache *rp, *rq, **rpp;
E 23
I 23
	register struct nfsrvcache *rp;
E 23
E 16
D 6
	register u_long saddr;
E 6
	struct mbuf *mb;
I 12
	struct sockaddr_in *saddr;
E 12
	caddr_t bpos;
	int ret;

D 12
	rh = &rhead[NFSRCHASH(xid)];
E 12
I 12
D 24
	if (nd->nd_nqlflag != NQL_NOVAL)
E 24
I 24
	/*
	 * Don't cache recent requests for reliable transport protocols.
	 * (Maybe we should for the case of a reconnect, but..)
	 */
	if (!nd->nd_nam2)
E 24
		return (RC_DOIT);
D 16
	rh = &rhead[NFSRCHASH(nd->nd_retxid)];
E 16
I 16
D 23
	rpp = &rheadhtbl[NFSRCHASH(nd->nd_retxid)];
E 23
E 16
E 12
D 6
	saddr = mtod(nam, struct sockaddr_in *)->sin_addr.s_addr;
E 6
loop:
D 16
	for (rp = rh->rh_chain[0]; rp != (struct nfsrvcache *)rh; rp = rp->rc_forw) {
E 16
I 16
D 23
	for (rp = *rpp; rp; rp = rp->rc_forw) {
E 23
I 23
	for (rp = NFSRCHASH(nd->nd_retxid)->lh_first; rp != 0;
	    rp = rp->rc_hash.le_next) {
E 23
E 16
D 6
		if (xid == rp->rc_xid && saddr == rp->rc_saddr &&
		    proc == rp->rc_proc) {
E 6
I 6
D 12
		if (xid == rp->rc_xid && proc == rp->rc_proc &&
		    nfs_netaddr_match(nam, &rp->rc_nam)) {
E 12
I 12
	    if (nd->nd_retxid == rp->rc_xid && nd->nd_procnum == rp->rc_proc &&
D 14
		nfs_netaddr_match(NETFAMILY(rp), &rp->rc_haddr, (union nethostaddr *)0, nam)) {
E 14
I 14
D 18
		netaddr_match(NETFAMILY(rp), &rp->rc_haddr, (union nethostaddr *)0, nam)) {
E 18
I 18
D 24
		netaddr_match(NETFAMILY(rp), &rp->rc_haddr, nam)) {
E 24
I 24
		netaddr_match(NETFAMILY(rp), &rp->rc_haddr, nd->nd_nam)) {
E 24
E 18
E 14
E 12
E 6
			if ((rp->rc_flag & RC_LOCKED) != 0) {
				rp->rc_flag |= RC_WANTED;
D 7
				sleep((caddr_t)rp, PZERO-1);
E 7
I 7
				(void) tsleep((caddr_t)rp, PZERO-1, "nfsrc", 0);
E 7
				goto loop;
			}
			rp->rc_flag |= RC_LOCKED;
D 12
			put_at_head(rp);
E 12
I 12
D 16
			if (rp->rc_prev != &nfsrvcachehead) {
E 16
I 16
			/* If not at end of LRU chain, move it there */
D 23
			if (rp->rc_next) {
				/* remove from LRU chain */
				*rp->rc_prev = rp->rc_next;
E 16
				rp->rc_next->rc_prev = rp->rc_prev;
D 16
				rp->rc_prev->rc_next = rp->rc_next;
				rp->rc_next = nfsrvcachehead.rc_next;
				nfsrvcachehead.rc_next = rp;
				rp->rc_prev = &nfsrvcachehead;
				rp->rc_next->rc_prev = rp;
E 16
I 16
				/* and replace at end of it */
				rp->rc_next = NULL;
				rp->rc_prev = nfsrvlrutail;
				*nfsrvlrutail = rp;
				nfsrvlrutail = &rp->rc_next;
E 23
I 23
			if (rp->rc_lru.tqe_next) {
				TAILQ_REMOVE(&nfsrvlruhead, rp, rc_lru);
				TAILQ_INSERT_TAIL(&nfsrvlruhead, rp, rc_lru);
E 23
E 16
			}
E 12
			if (rp->rc_state == RC_UNUSED)
				panic("nfsrv cache");
D 21
			if (rp->rc_state == RC_INPROG ||
			   (time.tv_sec - rp->rc_timestamp) < RC_DELAY) {
E 21
I 21
			if (rp->rc_state == RC_INPROG) {
E 21
				nfsstats.srvcache_inproghits++;
				ret = RC_DROPIT;
			} else if (rp->rc_flag & RC_REPSTATUS) {
D 21
				nfsstats.srvcache_idemdonehits++;
E 21
I 21
				nfsstats.srvcache_nonidemdonehits++;
E 21
D 12
				nfs_rephead(0, xid, rp->rc_status, repp, &mb,
					&bpos);
E 12
I 12
D 24
				nfs_rephead(0, nd, rp->rc_status,
E 24
I 24
				nfs_rephead(0, nd, slp, rp->rc_status,
E 24
				   0, (u_quad_t *)0, repp, &mb, &bpos);
E 12
D 21
				rp->rc_timestamp = time.tv_sec;
E 21
				ret = RC_REPLY;
			} else if (rp->rc_flag & RC_REPMBUF) {
D 21
				nfsstats.srvcache_idemdonehits++;
E 21
I 21
				nfsstats.srvcache_nonidemdonehits++;
E 21
D 6
				*repp = NFSMCOPY(rp->rc_reply, 0, M_COPYALL,
E 6
I 6
				*repp = m_copym(rp->rc_reply, 0, M_COPYALL,
E 6
						M_WAIT);
D 21
				rp->rc_timestamp = time.tv_sec;
E 21
				ret = RC_REPLY;
			} else {
D 21
				nfsstats.srvcache_nonidemdonehits++;
E 21
I 21
				nfsstats.srvcache_idemdonehits++;
E 21
				rp->rc_state = RC_INPROG;
				ret = RC_DOIT;
			}
			rp->rc_flag &= ~RC_LOCKED;
			if (rp->rc_flag & RC_WANTED) {
				rp->rc_flag &= ~RC_WANTED;
				wakeup((caddr_t)rp);
			}
			return (ret);
		}
	}
	nfsstats.srvcache_misses++;
D 16
	rp = nfsrvcachehead.rc_prev;
	while ((rp->rc_flag & RC_LOCKED) != 0) {
		rp->rc_flag |= RC_WANTED;
D 7
		sleep((caddr_t)rp, PZERO-1);
E 7
I 7
		(void) tsleep((caddr_t)rp, PZERO-1, "nfsrc", 0);
I 12
		rp = nfsrvcachehead.rc_prev;
E 12
E 7
	}
I 12
	rp->rc_flag |= RC_LOCKED;
E 12
	remque(rp);
D 12
	put_at_head(rp);
E 12
I 12
	if (rp->rc_prev != &nfsrvcachehead) {
E 16
I 16
	if (numnfsrvcache < desirednfsrvcache) {
		rp = (struct nfsrvcache *)malloc((u_long)sizeof *rp,
		    M_NFSD, M_WAITOK);
		bzero((char *)rp, sizeof *rp);
		numnfsrvcache++;
		rp->rc_flag = RC_LOCKED;
	} else {
D 23
		rp = nfsrvlruhead;
E 23
I 23
		rp = nfsrvlruhead.tqh_first;
E 23
		while ((rp->rc_flag & RC_LOCKED) != 0) {
			rp->rc_flag |= RC_WANTED;
			(void) tsleep((caddr_t)rp, PZERO-1, "nfsrc", 0);
D 23
			rp = nfsrvlruhead;
E 23
I 23
			rp = nfsrvlruhead.tqh_first;
E 23
		}
		rp->rc_flag |= RC_LOCKED;
D 23
		/* remove from hash chain */
		if (rq = rp->rc_forw)
			rq->rc_back = rp->rc_back;
		*rp->rc_back = rq;
		/* remove from LRU chain */
		*rp->rc_prev = rp->rc_next;
E 16
		rp->rc_next->rc_prev = rp->rc_prev;
E 23
I 23
		LIST_REMOVE(rp, rc_hash);
		TAILQ_REMOVE(&nfsrvlruhead, rp, rc_lru);
E 23
D 16
		rp->rc_prev->rc_next = rp->rc_next;
		rp->rc_next = nfsrvcachehead.rc_next;
		nfsrvcachehead.rc_next = rp;
		rp->rc_prev = &nfsrvcachehead;
		rp->rc_next->rc_prev = rp;
E 16
I 16
		if (rp->rc_flag & RC_REPMBUF)
			m_freem(rp->rc_reply);
		if (rp->rc_flag & RC_NAM)
			MFREE(rp->rc_nam, mb);
		rp->rc_flag &= (RC_LOCKED | RC_WANTED);
E 16
	}
E 12
D 16
	if (rp->rc_flag & RC_REPMBUF)
D 12
		mb = rp->rc_reply;
	else
		mb = (struct mbuf *)0;
	rp->rc_flag = 0;
E 12
I 12
		m_freem(rp->rc_reply);
	if (rp->rc_flag & RC_NAM)
		MFREE(rp->rc_nam, mb);
	rp->rc_flag &= (RC_LOCKED | RC_WANTED);
E 16
I 16
D 23
	/* place at end of LRU list */
	rp->rc_next = NULL;
	rp->rc_prev = nfsrvlrutail;
	*nfsrvlrutail = rp;
	nfsrvlrutail = &rp->rc_next;
E 23
I 23
	TAILQ_INSERT_TAIL(&nfsrvlruhead, rp, rc_lru);
E 23
E 16
E 12
	rp->rc_state = RC_INPROG;
D 12
	rp->rc_xid = xid;
D 6
	rp->rc_saddr = saddr;
E 6
I 6
	bcopy((caddr_t)nam, (caddr_t)&rp->rc_nam, sizeof (struct mbuf));
E 6
	rp->rc_proc = proc;
E 12
I 12
	rp->rc_xid = nd->nd_retxid;
D 24
	saddr = mtod(nam, struct sockaddr_in *);
E 24
I 24
	saddr = mtod(nd->nd_nam, struct sockaddr_in *);
E 24
	switch (saddr->sin_family) {
	case AF_INET:
		rp->rc_flag |= RC_INETADDR;
		rp->rc_inetaddr = saddr->sin_addr.s_addr;
		break;
	case AF_ISO:
	default:
		rp->rc_flag |= RC_NAM;
D 24
		rp->rc_nam = m_copym(nam, 0, M_COPYALL, M_WAIT);
E 24
I 24
		rp->rc_nam = m_copym(nd->nd_nam, 0, M_COPYALL, M_WAIT);
E 24
		break;
	};
	rp->rc_proc = nd->nd_procnum;
E 12
D 16
	insque(rp, rh);
E 16
I 16
D 23
	/* insert into hash chain */
	if (rq = *rpp)
		rq->rc_back = &rp->rc_forw;
D 17
	rp->rc_next = rq;
E 17
I 17
	rp->rc_forw = rq;
E 17
	rp->rc_back = rpp;
	*rpp = rp;
E 23
I 23
	LIST_INSERT_HEAD(NFSRCHASH(nd->nd_retxid), rp, rc_hash);
E 23
E 16
D 12
	if (mb)
		m_freem(mb);
E 12
I 12
	rp->rc_flag &= ~RC_LOCKED;
	if (rp->rc_flag & RC_WANTED) {
		rp->rc_flag &= ~RC_WANTED;
		wakeup((caddr_t)rp);
	}
E 12
	return (RC_DOIT);
}

/*
 * Update a request cache entry after the rpc has been done
 */
D 5
nfsrv_updatecache(nam, xid, proc, repstat, repmbuf)
E 5
I 5
D 12
nfsrv_updatecache(nam, xid, proc, repvalid, repstat, repmbuf)
E 12
I 12
void
D 24
nfsrv_updatecache(nam, nd, repvalid, repmbuf)
E 12
E 5
	struct mbuf *nam;
D 12
	u_long xid;
	int proc;
E 12
I 12
	register struct nfsd *nd;
E 24
I 24
nfsrv_updatecache(nd, repvalid, repmbuf)
	register struct nfsrv_descript *nd;
E 24
E 12
I 5
	int repvalid;
E 5
D 12
	int repstat;
E 12
	struct mbuf *repmbuf;
{
	register struct nfsrvcache *rp;
D 16
	register union	rhead *rh;
E 16
D 6
	register u_long saddr;
E 6

D 12
	rh = &rhead[NFSRCHASH(xid)];
E 12
I 12
D 24
	if (nd->nd_nqlflag != NQL_NOVAL)
E 24
I 24
	if (!nd->nd_nam2)
E 24
		return;
D 16
	rh = &rhead[NFSRCHASH(nd->nd_retxid)];
E 16
E 12
D 6
	saddr = mtod(nam, struct sockaddr_in *)->sin_addr.s_addr;
E 6
loop:
D 16
	for (rp = rh->rh_chain[0]; rp != (struct nfsrvcache *)rh; rp = rp->rc_forw) {
E 16
I 16
D 23
	for (rp = rheadhtbl[NFSRCHASH(nd->nd_retxid)]; rp; rp = rp->rc_forw) {
E 23
I 23
	for (rp = NFSRCHASH(nd->nd_retxid)->lh_first; rp != 0;
	    rp = rp->rc_hash.le_next) {
E 23
E 16
D 6
		if (xid == rp->rc_xid && saddr == rp->rc_saddr &&
		    proc == rp->rc_proc) {
E 6
I 6
D 12
		if (xid == rp->rc_xid && proc == rp->rc_proc &&
		    nfs_netaddr_match(nam, &rp->rc_nam)) {
E 12
I 12
	    if (nd->nd_retxid == rp->rc_xid && nd->nd_procnum == rp->rc_proc &&
D 14
		nfs_netaddr_match(NETFAMILY(rp), &rp->rc_haddr, (union nethostaddr *)0, nam)) {
E 14
I 14
D 18
		netaddr_match(NETFAMILY(rp), &rp->rc_haddr, (union nethostaddr *)0, nam)) {
E 18
I 18
D 24
		netaddr_match(NETFAMILY(rp), &rp->rc_haddr, nam)) {
E 24
I 24
		netaddr_match(NETFAMILY(rp), &rp->rc_haddr, nd->nd_nam)) {
E 24
E 18
E 14
E 12
E 6
			if ((rp->rc_flag & RC_LOCKED) != 0) {
				rp->rc_flag |= RC_WANTED;
D 7
				sleep((caddr_t)rp, PZERO-1);
E 7
I 7
				(void) tsleep((caddr_t)rp, PZERO-1, "nfsrc", 0);
E 7
				goto loop;
			}
			rp->rc_flag |= RC_LOCKED;
			rp->rc_state = RC_DONE;
D 5
			rp->rc_timestamp = time.tv_sec;
			if (nonidempotent[proc]) {
				if (repliesstatus[proc]) {
					rp->rc_status = repstat;
					rp->rc_flag |= RC_REPSTATUS;
				} else {
					rp->rc_reply = NFSMCOPY(repmbuf, 0,
							M_COPYALL, M_WAIT);
					rp->rc_flag |= RC_REPMBUF;
E 5
I 5
			/*
			 * If we have a valid reply update status and save
D 6
			 * the reply for non-idempotent rpc's. Otherwise
			 * invalidate entry by setting the timestamp to nil.
E 6
I 6
			 * the reply for non-idempotent rpc's.
D 21
			 * Otherwise invalidate entry by setting the timestamp
			 * to nil.
E 21
E 6
			 */
D 21
			if (repvalid) {
				rp->rc_timestamp = time.tv_sec;
D 12
				if (nonidempotent[proc]) {
					if (repliesstatus[proc]) {
						rp->rc_status = repstat;
E 12
I 12
				if (nonidempotent[nd->nd_procnum]) {
					if (repliesstatus[nd->nd_procnum]) {
						rp->rc_status = nd->nd_repstat;
E 12
						rp->rc_flag |= RC_REPSTATUS;
					} else {
D 6
						rp->rc_reply = NFSMCOPY(repmbuf,
E 6
I 6
						rp->rc_reply = m_copym(repmbuf,
E 6
							0, M_COPYALL, M_WAIT);
						rp->rc_flag |= RC_REPMBUF;
					}
E 21
I 21
			if (repvalid && nonidempotent[nd->nd_procnum]) {
D 24
				if (repliesstatus[nd->nd_procnum]) {
E 24
I 24
				if ((nd->nd_flag & ND_NFSV3) == 0 &&
				  nfsv2_repstat[nfsv2_procid[nd->nd_procnum]]) {
E 24
					rp->rc_status = nd->nd_repstat;
					rp->rc_flag |= RC_REPSTATUS;
				} else {
					rp->rc_reply = m_copym(repmbuf,
						0, M_COPYALL, M_WAIT);
					rp->rc_flag |= RC_REPMBUF;
E 21
E 5
				}
I 5
D 21
			} else {
				rp->rc_timestamp = 0;
E 21
E 5
			}
			rp->rc_flag &= ~RC_LOCKED;
			if (rp->rc_flag & RC_WANTED) {
				rp->rc_flag &= ~RC_WANTED;
				wakeup((caddr_t)rp);
			}
			return;
		}
I 12
	}
}

/*
 * Clean out the cache. Called when the last nfsd terminates.
 */
void
nfsrv_cleancache()
{
D 16
	register int i;
	register struct nfsrvcache *rp = nfsrvcache;
	register struct nfsrvcache *hp = &nfsrvcachehead;
	register union  rhead *rh = rhead;
E 16
I 16
	register struct nfsrvcache *rp, *nextrp;
E 16

D 16
	for (i = NFSRCHSZ; --i >= 0; rh++) {
		rh->rh_head[0] = rh;
		rh->rh_head[1] = rh;
E 16
I 16
D 23
	for (rp = nfsrvlruhead; rp; rp = nextrp) {
		nextrp = rp->rc_next;
E 23
I 23
	for (rp = nfsrvlruhead.tqh_first; rp != 0; rp = nextrp) {
		nextrp = rp->rc_lru.tqe_next;
		LIST_REMOVE(rp, rc_hash);
		TAILQ_REMOVE(&nfsrvlruhead, rp, rc_lru);
E 23
		free(rp, M_NFSD);
E 16
	}
D 16
	hp->rc_next = hp->rc_prev = hp;
	for (i = NFSRVCACHESIZ; i-- > 0; ) {
		if (rp->rc_flag & RC_REPMBUF)
			m_freem(rp->rc_reply);
		if (rp->rc_flag & RC_NAM)
			m_freem(rp->rc_nam);
		rp->rc_state = RC_UNUSED;
		rp->rc_flag = 0;
		rp->rc_forw = rp;
		rp->rc_back = rp;
		rp->rc_next = hp->rc_next;
		hp->rc_next->rc_prev = rp;
		rp->rc_prev = hp;
		hp->rc_next = rp;
		rp++;
E 12
	}
E 16
I 16
D 23
	bzero((char *)rheadhtbl, (rheadhash + 1) * sizeof(void *));
I 20
	nfsrvlruhead = NULL;
	nfsrvlrutail = &nfsrvlruhead;
E 23
E 20
	numnfsrvcache = 0;
E 16
}
E 1
