h15825
s 00021/00012/01197
d D 8.9 95/05/20 01:18:43 mckusick 37 36
c merge vfs_lock and vfs_busy; interlock mount points properly
e
s 00002/00002/01207
d D 8.8 95/05/14 00:33:14 mckusick 36 35
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00002/00001/01207
d D 8.7 95/05/09 12:17:51 mckusick 35 34
c change mountlist to CIRCLEQ so we can do unmountall (from mycroft)
e
s 00189/00131/01019
d D 8.6 95/03/30 11:26:57 mckusick 34 33
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00054/00108/01096
d D 8.5 94/08/18 23:33:48 mckusick 33 32
c conversion to queue.h list manipulation (from mycroft)
e
s 00011/00009/01193
d D 8.4 94/08/14 20:22:05 mckusick 32 31
c convert to vop call
e
s 00004/00007/01198
d D 8.3 94/01/04 22:00:26 bostic 31 30
c lint
e
s 00005/00007/01200
d D 8.2 93/12/30 16:21:13 mckusick 30 29
c new queue structure; vget now locks optionally
e
s 00002/00002/01205
d D 8.1 93/06/10 23:38:47 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/01188
d D 7.20 93/04/27 16:30:56 mckusick 28 27
c bug fixes for LEASES from Rick Macklem
e
s 00001/00001/01187
d D 7.19 93/03/31 15:21:19 hibler 27 26
c add missing third param for dounmount
e
s 00004/00004/01184
d D 7.18 93/02/02 15:04:18 mckusick 26 25
c update for 4.4BSD from Rick Macklem
e
s 00001/00001/01187
d D 7.17 92/11/15 21:55:25 mckusick 25 24
c MNT_NOFORCE no longer has its own flag
e
s 00013/00023/01175
d D 7.16 92/11/02 14:42:27 mckusick 24 23
c avoid unlocking directories
e
s 00006/00005/01192
d D 7.15 92/11/01 23:16:45 mckusick 23 22
c fix from Jeff Forys for tracking changing NFS file sizes
e
s 00001/00000/01196
d D 7.14 92/10/11 12:35:07 bostic 22 21
c make kernel includes standard
e
s 00001/00001/01195
d D 7.13 92/10/08 00:03:16 mckusick 21 20
c use new queue routines for buffer lists hanging off vnode
e
s 00004/00006/01192
d D 7.12 92/09/30 16:02:58 mckusick 20 19
c September update from Rick Macklem to add accept protocol to NQMFS
e
s 00057/00038/01141
d D 7.11 92/09/16 18:21:32 mckusick 19 18
c update from Rick Macklem
e
s 00018/00032/01161
d D 7.10 92/07/22 15:25:10 mckusick 18 17
c update to current hashing techniques
e
s 00000/00005/01193
d D 7.9 92/07/03 01:57:46 mckusick 17 16
c delete USES
e
s 00025/00026/01173
d D 7.8 92/07/02 20:01:51 mckusick 16 15
c clean up includes; nfs_netaddr_match goes to vfs_addr.c
e
s 00005/00002/01194
d D 7.7 92/06/25 13:12:40 mckusick 15 14
c new parameters to vinvalbuf; use VOP_FSYNC for vflushbuf
e
s 00004/00000/01192
d D 7.6 92/05/14 17:37:34 heideman 14 5
c vnode interface conversion
e
s 00013/00000/01192
d R 7.6 92/05/14 15:55:14 heideman 13 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/14 14:56:18 heideman 12 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/14 13:01:56 heideman 11 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/14 11:59:27 heideman 10 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/14 11:23:01 heideman 9 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/13 23:18:37 heideman 8 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/13 19:02:50 heideman 7 5
c vnode interface conversion
e
s 00004/00000/01192
d R 7.6 92/05/13 18:35:03 heideman 6 5
c vnode interface conversion
e
s 00011/00010/01181
d D 7.5 92/03/09 22:27:39 mckusick 5 4
c first cut at fixing discconect/reconnect hanging confusion
e
s 00001/00001/01190
d D 7.4 92/02/06 18:04:02 mckusick 4 3
c bug fix for leases from Rick Macklem
e
s 00001/00002/01190
d D 7.3 92/02/06 16:25:43 mckusick 3 2
c get rid of UFS dependencies
e
s 00004/00002/01188
d D 7.2 92/01/14 12:41:38 mckusick 2 1
c update from Rick Macklem (including leases)
e
s 01190/00000/00000
d D 7.1 92/01/07 21:08:50 mckusick 1 0
c new modules for NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 29
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 34

E 34
/*
 * References:
 *	Cary G. Gray and David R. Cheriton, "Leases: An Efficient Fault-Tolerant
 *		Mechanism for Distributed File Cache Consistency",
 *		In Proc. of the Twelfth ACM Symposium on Operating Systems
 *		Principals, pg. 202-210, Litchfield Park, AZ, Dec. 1989.
 *	Michael N. Nelson, Brent B. Welch and John K. Ousterhout, "Caching
 *		in the Sprite Network File System", ACM TOCS 6(1),
 *		pages 134-154, February 1988.
 *	V. Srinivasan and Jeffrey C. Mogul, "Spritely NFS: Implementation and
 *		Performance of Cache-Consistency Protocols", Digital
 *		Equipment Corporation WRL Research Report 89/5, May 1989.
 */
D 16
#include "param.h"
#include "vnode.h"
#include "mount.h"
#include "kernel.h"
#include "proc.h"
#include "systm.h"
#include "mbuf.h"
#include "socket.h"
#include "socketvar.h"
#include "file.h"
#include "buf.h"
I 3
#include "stat.h"
E 3
#include "protosw.h"
#include "machine/endian.h"
D 3
#include "ufs/ufs/quota.h"
#include "ufs/ufs/inode.h"
E 3
#include "netinet/in.h"
#include "rpcv2.h"
#include "nfsv2.h"
#include "nfs.h"
#include "nfsm_subs.h"
#include "xdr_subs.h"
#include "nqnfs.h"
#include "nfsnode.h"
#include "nfsmount.h"
E 16
I 16
#include <sys/param.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/file.h>
#include <sys/buf.h>
#include <sys/stat.h>
#include <sys/protosw.h>
I 22

E 22
#include <netinet/in.h>
#include <nfs/rpcv2.h>
D 34
#include <nfs/nfsv2.h>
E 34
I 34
#include <nfs/nfsproto.h>
E 34
#include <nfs/nfs.h>
#include <nfs/nfsm_subs.h>
#include <nfs/xdr_subs.h>
#include <nfs/nqnfs.h>
#include <nfs/nfsnode.h>
#include <nfs/nfsmount.h>
E 16

D 33
/*
 * List head for the lease queue and other global data.
 * At any time a lease is linked into a list ordered by increasing expiry time.
 */
D 18
#if	((NQLCHSZ&(NQLCHSZ-1)) == 0)
#define	NQFHHASH(f)	((*((u_long *)(f)))&(NQLCHSZ-1))
#else
#define	NQFHHASH(f)	((*((u_long *)(f)))%NQLCHSZ)
#endif
E 18
I 18
#define	NQFHHASH(f)	((*((u_long *)(f)))&nqfheadhash)
E 18

union nqsrvthead nqthead;
D 18
union nqsrvthead nqfhead[NQLCHSZ];
E 18
I 18
struct nqlease **nqfhead;
u_long nqfheadhash;
E 33
E 18
time_t nqnfsstarttime = (time_t)0;
D 34
u_long nqnfs_prog, nqnfs_vers;
E 34
int nqsrv_clockskew = NQ_CLOCKSKEW;
int nqsrv_writeslack = NQ_WRITESLACK;
int nqsrv_maxlease = NQ_MAXLEASE;
int nqsrv_maxnumlease = NQ_MAXNUMLEASE;
void nqsrv_instimeq(), nqsrv_send_eviction(), nfs_sndunlock();
D 5
void nqsrv_unlocklease(), nqsrv_waitfor_expiry();
E 5
I 5
void nqsrv_unlocklease(), nqsrv_waitfor_expiry(), nfsrv_slpderef();
E 5
void nqsrv_addhost(), nqsrv_locklease(), nqnfs_serverd();
I 19
void nqnfs_clientlease();
E 19
struct mbuf *nfsm_rpchead();

/*
 * Signifies which rpcs can have piggybacked lease requests
 */
int nqnfs_piggy[NFS_NPROCS] = {
	0,
D 34
	NQL_READ,
	NQL_WRITE,
E 34
	0,
D 34
	NQL_READ,
	NQL_READ,
	NQL_READ,
E 34
I 34
	ND_WRITE,
	ND_READ,
E 34
	0,
D 34
	NQL_WRITE,
E 34
I 34
	ND_READ,
	ND_READ,
	ND_WRITE,
E 34
	0,
	0,
	0,
	0,
	0,
	0,
	0,
D 34
	NQL_READ,
E 34
	0,
D 34
	NQL_READ,
E 34
I 34
	ND_READ,
	ND_READ,
E 34
	0,
	0,
	0,
I 20
	0,
I 34
	0,
	0,
	0,
	0,
E 34
E 20
};

D 33
int nnnnnn = sizeof (struct nqlease);
int oooooo = sizeof (struct nfsnode);
E 33
D 34
extern nfstype nfs_type[9];
E 34
I 34
extern nfstype nfsv2_type[9];
extern nfstype nfsv3_type[9];
E 34
extern struct nfssvc_sock *nfs_udpsock, *nfs_cltpsock;
D 33
extern struct nfsd nfsd_head;
E 33
extern int nfsd_waiting;
I 34
extern struct nfsstats nfsstats;
extern int nfs_mount_type;
E 34
I 28
D 33
extern struct nfsreq nfsreqh;
E 33
E 28

#define TRUE	1
#define	FALSE	0

/*
D 34
 * Get or check for a lease for "vp", based on NQL_CHECK flag.
E 34
I 34
 * Get or check for a lease for "vp", based on ND_CHECK flag.
E 34
 * The rules are as follows:
 * - if a current non-caching lease, reply non-caching
 * - if a current lease for same host only, extend lease
 * - if a read cachable lease and a read lease request
 *	add host to list any reply cachable
 * - else { set non-cachable for read-write sharing }
 *	send eviction notice messages to all other hosts that have lease
 *	wait for lease termination { either by receiving vacated messages
 *					from all the other hosts or expiry
 *					via. timeout }
 *	modify lease to non-cachable
 * - else if no current lease, issue new one
 * - reply
 * - return boolean TRUE iff nam should be m_freem()'d
 * NB: Since nqnfs_serverd() is called from a timer, any potential tsleep()
 *     in here must be framed by nqsrv_locklease() and nqsrv_unlocklease().
 *     nqsrv_locklease() is coded such that at least one of LC_LOCKED and
 *     LC_WANTED is set whenever a process is tsleeping in it. The exception
 *     is when a new lease is being allocated, since it is not in the timer
 *     queue yet. (Ditto for the splsoftclock() and splx(s) calls)
 */
D 34
nqsrv_getlease(vp, duration, flags, nd, nam, cachablep, frev, cred)
E 34
I 34
int
nqsrv_getlease(vp, duration, flags, slp, procp, nam, cachablep, frev, cred)
E 34
	struct vnode *vp;
	u_long *duration;
	int flags;
D 34
	struct nfsd *nd;
E 34
I 34
	struct nfssvc_sock *slp;
	struct proc *procp;
E 34
	struct mbuf *nam;
	int *cachablep;
	u_quad_t *frev;
	struct ucred *cred;
{
I 14
D 17
	USES_VOP_GETATTR;
	USES_VOP_LOCK;
	USES_VOP_UNLOCK;
E 17
E 14
D 18
	register struct nqlease *lp;
E 18
I 18
D 33
	register struct nqlease *lp, *lq, **lpp;
E 33
I 33
	register struct nqlease *lp;
D 34
	register struct nqfhhashhead *lpp;
E 33
E 18
	register struct nqhost *lph;
E 34
I 34
	register struct nqfhhashhead *lpp = 0;
	register struct nqhost *lph = 0;
E 34
D 18
	struct nqlease *tlp = (struct nqlease *)0;
E 18
I 18
	struct nqlease *tlp;
E 18
	struct nqm **lphp;
	struct vattr vattr;
D 18
	union nqsrvthead *lhp;
E 18
	fhandle_t fh;
	int i, ok, error, s;

	if (vp->v_type != VREG && vp->v_type != VDIR && vp->v_type != VLNK)
		return (0);
	if (*duration > nqsrv_maxlease)
		*duration = nqsrv_maxlease;
D 34
	if (error = VOP_GETATTR(vp, &vattr, cred, nd->nd_procp))
E 34
I 34
	error = VOP_GETATTR(vp, &vattr, cred, procp);
	if (error)
E 34
		return (error);
	*frev = vattr.va_filerev;
	s = splsoftclock();
	tlp = vp->v_lease;
D 34
	if ((flags & NQL_CHECK) == 0)
E 34
I 34
	if ((flags & ND_CHECK) == 0)
E 34
		nfsstats.srvnqnfs_getleases++;
D 33
	if (tlp == (struct nqlease *)0) {

E 33
I 33
D 34
	if (tlp == 0) {
E 34
I 34
	if (tlp == (struct nqlease *)0) {

E 34
E 33
		/*
		 * Find the lease by searching the hash list.
		 */
		fh.fh_fsid = vp->v_mount->mnt_stat.f_fsid;
D 34
		if (error = VFS_VPTOFH(vp, &fh.fh_fid)) {
E 34
I 34
		error = VFS_VPTOFH(vp, &fh.fh_fid);
		if (error) {
E 34
			splx(s);
			return (error);
		}
D 18
		lhp = &nqfhead[NQFHHASH(fh.fh_fid.fid_data)];
		for (lp = lhp->th_chain[0]; lp != (struct nqlease *)lhp;
			lp = lp->lc_fhnext)
E 18
I 18
D 33
		lpp = &nqfhead[NQFHHASH(fh.fh_fid.fid_data)];
		for (lp = *lpp; lp; lp = lp->lc_fhnext)
E 33
I 33
		lpp = NQFHHASH(fh.fh_fid.fid_data);
		for (lp = lpp->lh_first; lp != 0; lp = lp->lc_hash.le_next)
E 33
E 18
D 2
			if (QUADEQ(fh.fh_fsid, lp->lc_fsid) &&
E 2
I 2
			if (fh.fh_fsid.val[0] == lp->lc_fsid.val[0] &&
			    fh.fh_fsid.val[1] == lp->lc_fsid.val[1] &&
E 2
			    !bcmp(fh.fh_fid.fid_data, lp->lc_fiddata,
				  fh.fh_fid.fid_len - sizeof (long))) {
				/* Found it */
				lp->lc_vp = vp;
				vp->v_lease = lp;
				tlp = lp;
				break;
			}
D 33
	}
	lp = tlp;
	if (lp) {
E 33
I 33
	} else
		lp = tlp;
D 34
	if (lp != 0) {
E 34
I 34
	if (lp) {
E 34
E 33
		if ((lp->lc_flag & LC_NONCACHABLE) ||
		    (lp->lc_morehosts == (struct nqm *)0 &&
D 34
		     nqsrv_cmpnam(nd->nd_slp, nam, &lp->lc_host)))
E 34
I 34
		     nqsrv_cmpnam(slp, nam, &lp->lc_host)))
E 34
			goto doreply;
D 33
		if ((flags & NQL_READ) && (lp->lc_flag & LC_WRITE)==0) {
E 33
I 33
D 34
		if ((flags & NQL_READ) && (lp->lc_flag & LC_WRITE) == 0) {
E 33
			if (flags & NQL_CHECK)
E 34
I 34
		if ((flags & ND_READ) && (lp->lc_flag & LC_WRITE) == 0) {
			if (flags & ND_CHECK)
E 34
				goto doreply;
D 34
			if (nqsrv_cmpnam(nd->nd_slp, nam, &lp->lc_host))
E 34
I 34
			if (nqsrv_cmpnam(slp, nam, &lp->lc_host))
E 34
				goto doreply;
			i = 0;
			if (lp->lc_morehosts) {
				lph = lp->lc_morehosts->lpm_hosts;
				lphp = &lp->lc_morehosts->lpm_next;
				ok = 1;
			} else {
				lphp = &lp->lc_morehosts;
				ok = 0;
			}
			while (ok && (lph->lph_flag & LC_VALID)) {
D 34
				if (nqsrv_cmpnam(nd->nd_slp, nam, lph))
E 34
I 34
				if (nqsrv_cmpnam(slp, nam, lph))
E 34
					goto doreply;
				if (++i == LC_MOREHOSTSIZ) {
					i = 0;
					if (*lphp) {
						lph = (*lphp)->lpm_hosts;
						lphp = &((*lphp)->lpm_next);
					} else
						ok = 0;
				} else
					lph++;
			}
			nqsrv_locklease(lp);
			if (!ok) {
				*lphp = (struct nqm *)
					malloc(sizeof (struct nqm),
						M_NQMHOST, M_WAITOK);
				bzero((caddr_t)*lphp, sizeof (struct nqm));
				lph = (*lphp)->lpm_hosts;
			}
D 5
			nqsrv_addhost(lph, nd->nd_slp, nd->nd_sref, nam);
E 5
I 5
D 34
			nqsrv_addhost(lph, nd->nd_slp, nam);
E 34
I 34
			nqsrv_addhost(lph, slp, nam);
E 34
E 5
			nqsrv_unlocklease(lp);
		} else {
			lp->lc_flag |= LC_NONCACHABLE;
			nqsrv_locklease(lp);
D 24
			VOP_UNLOCK(vp);
E 24
D 34
			nqsrv_send_eviction(vp, lp, nd->nd_slp, nam, cred);
E 34
I 34
			nqsrv_send_eviction(vp, lp, slp, nam, cred);
E 34
			nqsrv_waitfor_expiry(lp);
D 24
			VOP_LOCK(vp);
E 24
			nqsrv_unlocklease(lp);
		}
doreply:
		/*
		 * Update the lease and return
		 */
D 34
		if ((flags & NQL_CHECK) == 0)
E 34
I 34
		if ((flags & ND_CHECK) == 0)
E 34
			nqsrv_instimeq(lp, *duration);
		if (lp->lc_flag & LC_NONCACHABLE)
			*cachablep = 0;
		else {
			*cachablep = 1;
D 34
			if (flags & NQL_WRITE)
E 34
I 34
			if (flags & ND_WRITE)
E 34
				lp->lc_flag |= LC_WRITTEN;
		}
		splx(s);
		return (0);
	}
	splx(s);
D 34
	if (flags & NQL_CHECK)
E 34
I 34
	if (flags & ND_CHECK)
E 34
		return (0);

	/*
	 * Allocate new lease
	 * The value of nqsrv_maxnumlease should be set generously, so that
	 * the following "printf" happens infrequently.
	 */
	if (nfsstats.srvnqnfs_leases > nqsrv_maxnumlease) {
		printf("Nqnfs server, too many leases\n");
		do {
			(void) tsleep((caddr_t)&lbolt, PSOCK,
					"nqsrvnuml", 0);
		} while (nfsstats.srvnqnfs_leases > nqsrv_maxnumlease);
	}
	MALLOC(lp, struct nqlease *, sizeof (struct nqlease), M_NQLEASE, M_WAITOK);
	bzero((caddr_t)lp, sizeof (struct nqlease));
D 34
	if (flags & NQL_WRITE)
E 34
I 34
	if (flags & ND_WRITE)
E 34
		lp->lc_flag |= (LC_WRITE | LC_WRITTEN);
D 5
	nqsrv_addhost(&lp->lc_host, nd->nd_slp, nd->nd_sref, nam);
E 5
I 5
D 34
	nqsrv_addhost(&lp->lc_host, nd->nd_slp, nam);
E 34
I 34
	nqsrv_addhost(&lp->lc_host, slp, nam);
E 34
E 5
	lp->lc_vp = vp;
	lp->lc_fsid = fh.fh_fsid;
D 34
	bcopy(fh.fh_fid.fid_data, lp->lc_fiddata, fh.fh_fid.fid_len - sizeof (long));
E 34
I 34
	bcopy(fh.fh_fid.fid_data, lp->lc_fiddata,
		fh.fh_fid.fid_len - sizeof (long));
	if(!lpp)
		panic("nfs_nqlease.c: Phoney lpp");
E 34
D 18
	lp->lc_fhnext = lhp->th_chain[0];
	if (lhp->th_head[0] == lhp)
		lhp->th_chain[1] = lp;
	else
		lhp->th_chain[0]->lc_fhprev = lp;
	lp->lc_fhprev = (struct nqlease *)lhp;
	lhp->th_chain[0] = lp;
E 18
I 18
D 33
	if (lq = *lpp)
		lq->lc_fhprev = &lp->lc_fhnext;
	lp->lc_fhnext = lq;
	lp->lc_fhprev = lpp;
	*lpp = lp;
E 33
I 33
	LIST_INSERT_HEAD(lpp, lp, lc_hash);
E 33
E 18
	vp->v_lease = lp;
	s = splsoftclock();
	nqsrv_instimeq(lp, *duration);
	splx(s);
	*cachablep = 1;
	if (++nfsstats.srvnqnfs_leases > nfsstats.srvnqnfs_maxleases)
		nfsstats.srvnqnfs_maxleases = nfsstats.srvnqnfs_leases;
	return (0);
}

/*
 * Local lease check for server syscalls.
 * Just set up args and let nqsrv_getlease() do the rest.
 */
D 32
void
lease_check(vp, p, cred, flag)
	struct vnode *vp;
	struct proc *p;
	struct ucred *cred;
	int flag;
E 32
I 32
D 34
lease_check(ap)
E 34
I 34
int
nqnfs_vop_lease_check(ap)
E 34
	struct vop_lease_args /* {
		struct vnode *a_vp;
		struct proc *a_p;
		struct ucred *a_cred;
		int a_flag;
	} */ *ap;
E 32
{
D 23
	int duration, cache;
E 23
I 23
D 34
	int duration = 0, cache;
E 23
	struct nfsd nfsd;
E 34
I 34
	u_long duration = 0;
	int cache;
E 34
	u_quad_t frev;

D 34
	nfsd.nd_slp = NQLOCALSLP;
D 32
	nfsd.nd_procp = p;
	(void) nqsrv_getlease(vp, &duration, NQL_CHECK | flag, &nfsd,
		(struct mbuf *)0, &cache, &frev, cred);
E 32
I 32
	nfsd.nd_procp = ap->a_p;
	(void) nqsrv_getlease(ap->a_vp, &duration, NQL_CHECK | ap->a_flag,
		&nfsd, (struct mbuf *)0, &cache, &frev, ap->a_cred);
E 34
I 34
	(void) nqsrv_getlease(ap->a_vp, &duration, ND_CHECK | ap->a_flag,
	    NQLOCALSLP, ap->a_p, (struct mbuf *)0, &cache, &frev, ap->a_cred);
E 34
	return (0);
E 32
}

/*
 * Add a host to an nqhost structure for a lease.
 */
void
D 5
nqsrv_addhost(lph, slp, sref, nam)
E 5
I 5
nqsrv_addhost(lph, slp, nam)
E 5
	register struct nqhost *lph;
	struct nfssvc_sock *slp;
D 5
	u_short sref;
E 5
	struct mbuf *nam;
{
	register struct sockaddr_in *saddr;

	if (slp == NQLOCALSLP)
		lph->lph_flag |= (LC_VALID | LC_LOCAL);
	else if (slp == nfs_udpsock) {
		saddr = mtod(nam, struct sockaddr_in *);
		lph->lph_flag |= (LC_VALID | LC_UDP);
		lph->lph_inetaddr = saddr->sin_addr.s_addr;
		lph->lph_port = saddr->sin_port;
	} else if (slp == nfs_cltpsock) {
		lph->lph_nam = m_copym(nam, 0, M_COPYALL, M_WAIT);
		lph->lph_flag |= (LC_VALID | LC_CLTP);
	} else {
D 5
		lph->lph_flag |= LC_VALID;
E 5
I 5
		lph->lph_flag |= (LC_VALID | LC_SREF);
E 5
		lph->lph_slp = slp;
D 5
		lph->lph_sref = sref;
E 5
I 5
		slp->ns_sref++;
E 5
	}
}

/*
 * Update the lease expiry time and position it in the timer queue correctly.
 */
void
nqsrv_instimeq(lp, duration)
	register struct nqlease *lp;
	u_long duration;
{
	register struct nqlease *tlp;
	time_t newexpiry;

	newexpiry = time.tv_sec + duration + nqsrv_clockskew;
	if (lp->lc_expiry == newexpiry)
		return;
D 33
	if (lp->lc_chain1[0])
		remque(lp);
E 33
I 33
D 34
	if (lp->lc_timer.cqe_next != 0)
E 34
I 34
	if (lp->lc_timer.cqe_next != 0) {
E 34
		CIRCLEQ_REMOVE(&nqtimerhead, lp, lc_timer);
I 34
	}
E 34
E 33
	lp->lc_expiry = newexpiry;

	/*
	 * Find where in the queue it should be.
	 */
D 33
	tlp = nqthead.th_chain[1];
	while (tlp->lc_expiry > newexpiry && tlp != (struct nqlease *)&nqthead)
		tlp = tlp->lc_chain1[1];
	if (tlp == nqthead.th_chain[1])
E 33
I 33
	tlp = nqtimerhead.cqh_last;
	while (tlp != (void *)&nqtimerhead && tlp->lc_expiry > newexpiry)
		tlp = tlp->lc_timer.cqe_prev;
I 34
#ifdef HASNVRAM
E 34
	if (tlp == nqtimerhead.cqh_last)
E 33
		NQSTORENOVRAM(newexpiry);
I 34
#endif /* HASNVRAM */
E 34
D 33
	insque(lp, tlp);
E 33
I 33
	if (tlp == (void *)&nqtimerhead) {
		CIRCLEQ_INSERT_HEAD(&nqtimerhead, lp, lc_timer);
	} else {
		CIRCLEQ_INSERT_AFTER(&nqtimerhead, tlp, lp, lc_timer);
	}
E 33
}

/*
 * Compare the requesting host address with the lph entry in the lease.
 * Return true iff it is the same.
 * This is somewhat messy due to the union in the nqhost structure.
 * The local host is indicated by the special value of NQLOCALSLP for slp.
 */
I 34
int
E 34
nqsrv_cmpnam(slp, nam, lph)
	register struct nfssvc_sock *slp;
	struct mbuf *nam;
	register struct nqhost *lph;
{
	register struct sockaddr_in *saddr;
	struct mbuf *addr;
	union nethostaddr lhaddr;
	int ret;

	if (slp == NQLOCALSLP) {
		if (lph->lph_flag & LC_LOCAL)
			return (1);
		else
			return (0);
	}
	if (slp == nfs_udpsock || slp == nfs_cltpsock)
		addr = nam;
	else
		addr = slp->ns_nam;
	if (lph->lph_flag & LC_UDP)
D 16
		ret = nfs_netaddr_match(AF_INET, &lph->lph_haddr,
E 16
I 16
D 20
		ret = netaddr_match(AF_INET, &lph->lph_haddr,
E 16
			(union nethostaddr *)0, addr);
E 20
I 20
		ret = netaddr_match(AF_INET, &lph->lph_haddr, addr);
E 20
	else if (lph->lph_flag & LC_CLTP)
D 16
		ret = nfs_netaddr_match(AF_ISO, &lph->lph_claddr,
E 16
I 16
D 20
		ret = netaddr_match(AF_ISO, &lph->lph_claddr,
E 16
			(union nethostaddr *)0, addr);
E 20
I 20
		ret = netaddr_match(AF_ISO, &lph->lph_claddr, addr);
E 20
	else {
D 5
		if (lph->lph_sref != lph->lph_slp->ns_sref)
E 5
I 5
		if ((lph->lph_slp->ns_flag & SLP_VALID) == 0)
E 5
			return (0);
		saddr = mtod(lph->lph_slp->ns_nam, struct sockaddr_in *);
		if (saddr->sin_family == AF_INET)
			lhaddr.had_inetaddr = saddr->sin_addr.s_addr;
		else
			lhaddr.had_nam = lph->lph_slp->ns_nam;
D 16
		ret = nfs_netaddr_match(saddr->sin_family, &lhaddr,
E 16
I 16
D 20
		ret = netaddr_match(saddr->sin_family, &lhaddr,
E 16
			(union nethostaddr *)0, addr);
E 20
I 20
		ret = netaddr_match(saddr->sin_family, &lhaddr, addr);
E 20
	}
	return (ret);
}

/*
 * Send out eviction notice messages to all other hosts for the lease.
 */
void
nqsrv_send_eviction(vp, lp, slp, nam, cred)
	struct vnode *vp;
	register struct nqlease *lp;
	struct nfssvc_sock *slp;
	struct mbuf *nam;
	struct ucred *cred;
{
	register struct nqhost *lph = &lp->lc_host;
	register struct mbuf *m;
	register int siz;
	struct nqm *lphnext = lp->lc_morehosts;
	struct mbuf *mreq, *mb, *mb2, *nam2, *mheadend;
	struct socket *so;
	struct sockaddr_in *saddr;
	fhandle_t *fhp;
	caddr_t bpos, cp;
	u_long xid;
	int len = 1, ok = 1, i = 0;
	int sotype, *solockp;

	while (ok && (lph->lph_flag & LC_VALID)) {
		if (nqsrv_cmpnam(slp, nam, lph))
			lph->lph_flag |= LC_VACATED;
		else if ((lph->lph_flag & (LC_LOCAL | LC_VACATED)) == 0) {
			if (lph->lph_flag & LC_UDP) {
				MGET(nam2, M_WAIT, MT_SONAME);
				saddr = mtod(nam2, struct sockaddr_in *);
				nam2->m_len = saddr->sin_len =
					sizeof (struct sockaddr_in);
				saddr->sin_family = AF_INET;
				saddr->sin_addr.s_addr = lph->lph_inetaddr;
				saddr->sin_port = lph->lph_port;
				so = nfs_udpsock->ns_so;
			} else if (lph->lph_flag & LC_CLTP) {
				nam2 = lph->lph_nam;
				so = nfs_cltpsock->ns_so;
D 5
			} else if (lph->lph_sref == lph->lph_slp->ns_sref) {
E 5
I 5
			} else if (lph->lph_slp->ns_flag & SLP_VALID) {
E 5
				nam2 = (struct mbuf *)0;
				so = lph->lph_slp->ns_so;
			} else
				goto nextone;
			sotype = so->so_type;
			if (so->so_proto->pr_flags & PR_CONNREQUIRED)
				solockp = &lph->lph_slp->ns_solock;
			else
				solockp = (int *)0;
			nfsm_reqhead((struct vnode *)0, NQNFSPROC_EVICTED,
D 34
				NFSX_FH);
			nfsm_build(cp, caddr_t, NFSX_FH);
			bzero(cp, NFSX_FH);
E 34
I 34
				NFSX_V3FH);
			nfsm_build(cp, caddr_t, NFSX_V3FH);
			bzero(cp, NFSX_V3FH);
E 34
			fhp = (fhandle_t *)cp;
			fhp->fh_fsid = vp->v_mount->mnt_stat.f_fsid;
			VFS_VPTOFH(vp, &fhp->fh_fid);
			m = mreq;
			siz = 0;
			while (m) {
				siz += m->m_len;
				m = m->m_next;
			}
			if (siz <= 0 || siz > NFS_MAXPACKET) {
				printf("mbuf siz=%d\n",siz);
				panic("Bad nfs svc reply");
			}
D 34
			m = nfsm_rpchead(cred, TRUE, NQNFSPROC_EVICTED,
				RPCAUTH_UNIX, 5*NFSX_UNSIGNED, (char *)0,
E 34
I 34
			m = nfsm_rpchead(cred, (NFSMNT_NFSV3 | NFSMNT_NQNFS),
				NQNFSPROC_EVICTED,
				RPCAUTH_UNIX, 5 * NFSX_UNSIGNED, (char *)0,
E 34
				mreq, siz, &mheadend, &xid);
			/*
			 * For stream protocols, prepend a Sun RPC
			 * Record Mark.
			 */
			if (sotype == SOCK_STREAM) {
				M_PREPEND(m, NFSX_UNSIGNED, M_WAIT);
				*mtod(m, u_long *) = htonl(0x80000000 |
					(m->m_pkthdr.len - NFSX_UNSIGNED));
			}
			if (((lph->lph_flag & (LC_UDP | LC_CLTP)) == 0 &&
D 5
			    lph->lph_sref != lph->lph_slp->ns_sref) ||
E 5
I 5
			    (lph->lph_slp->ns_flag & SLP_VALID) == 0) ||
E 5
			    (solockp && (*solockp & NFSMNT_SNDLOCK)))
				m_freem(m);
			else {
				if (solockp)
					*solockp |= NFSMNT_SNDLOCK;
				(void) nfs_send(so, nam2, m,
						(struct nfsreq *)0);
				if (solockp)
					nfs_sndunlock(solockp);
			}
			if (lph->lph_flag & LC_UDP)
				MFREE(nam2, m);
		}
nextone:
		if (++i == len) {
			if (lphnext) {
				i = 0;
				len = LC_MOREHOSTSIZ;
				lph = lphnext->lpm_hosts;
				lphnext = lphnext->lpm_next;
			} else
				ok = 0;
		} else
			lph++;
	}
}

/*
 * Wait for the lease to expire.
 * This will occur when all clients have sent "vacated" messages to
 * this server OR when it expires do to timeout.
 */
void
nqsrv_waitfor_expiry(lp)
	register struct nqlease *lp;
{
	register struct nqhost *lph;
	register int i;
	struct nqm *lphnext;
	int len, ok;

tryagain:
	if (time.tv_sec > lp->lc_expiry)
		return;
	lph = &lp->lc_host;
	lphnext = lp->lc_morehosts;
	len = 1;
	i = 0;
	ok = 1;
	while (ok && (lph->lph_flag & LC_VALID)) {
		if ((lph->lph_flag & (LC_LOCAL | LC_VACATED)) == 0) {
			lp->lc_flag |= LC_EXPIREDWANTED;
			(void) tsleep((caddr_t)&lp->lc_flag, PSOCK,
					"nqexp", 0);
			goto tryagain;
		}
		if (++i == len) {
			if (lphnext) {
				i = 0;
				len = LC_MOREHOSTSIZ;
				lph = lphnext->lpm_hosts;
				lphnext = lphnext->lpm_next;
			} else
				ok = 0;
		} else
			lph++;
	}
}

/*
 * Nqnfs server timer that maintains the server lease queue.
 * Scan the lease queue for expired entries:
 * - when one is found, wakeup anyone waiting for it
 *   else dequeue and free
 */
void
nqnfs_serverd()
{
D 18
	register struct nqlease *lp;
E 18
I 18
D 34
	register struct nqlease *lp, *lq;
E 34
I 34
	register struct nqlease *lp;
E 34
E 18
	register struct nqhost *lph;
	struct nqlease *nextlp;
	struct nqm *lphnext, *olphnext;
	struct mbuf *n;
D 31
	union nqsrvthead *lhp;
E 31
	int i, len, ok;

D 33
	lp = nqthead.th_chain[0];
	while (lp != (struct nqlease *)&nqthead) {
E 33
I 33
	for (lp = nqtimerhead.cqh_first; lp != (void *)&nqtimerhead;
	    lp = nextlp) {
E 33
		if (lp->lc_expiry >= time.tv_sec)
			break;
D 33
		nextlp = lp->lc_chain1[0];
E 33
I 33
		nextlp = lp->lc_timer.cqe_next;
E 33
		if (lp->lc_flag & LC_EXPIREDWANTED) {
			lp->lc_flag &= ~LC_EXPIREDWANTED;
			wakeup((caddr_t)&lp->lc_flag);
		} else if ((lp->lc_flag & (LC_LOCKED | LC_WANTED)) == 0) {
		    /*
		     * Make a best effort at keeping a write caching lease long
		     * enough by not deleting it until it has been explicitly
		     * vacated or there have been no writes in the previous
		     * write_slack seconds since expiry and the nfsds are not
		     * all busy. The assumption is that if the nfsds are not
		     * all busy now (no queue of nfs requests), then the client
		     * would have been able to do at least one write to the
		     * file during the last write_slack seconds if it was still
		     * trying to push writes to the server.
		     */
		    if ((lp->lc_flag & (LC_WRITE | LC_VACATED)) == LC_WRITE &&
			((lp->lc_flag & LC_WRITTEN) || nfsd_waiting == 0)) {
			lp->lc_flag &= ~LC_WRITTEN;
			nqsrv_instimeq(lp, nqsrv_writeslack);
		    } else {
D 33
			remque(lp);
D 18
			lhp = &nqfhead[NQFHHASH(lp->lc_fiddata)];
			if (lp->lc_fhprev == (struct nqlease *)lhp)
				lhp->th_chain[0] = lp->lc_fhnext;
			else
				lp->lc_fhprev->lc_fhnext = lp->lc_fhnext;
			if (lp->lc_fhnext == (struct nqlease *)lhp)
				lhp->th_chain[1] = lp->lc_fhprev;
			else
				lp->lc_fhnext->lc_fhprev = lp->lc_fhprev;
E 18
I 18
			if (lq = lp->lc_fhnext)
				lq->lc_fhprev = lp->lc_fhprev;
			*lp->lc_fhprev = lq;
E 33
I 33
			CIRCLEQ_REMOVE(&nqtimerhead, lp, lc_timer);
			LIST_REMOVE(lp, lc_hash);
E 33
E 18
			/*
			 * This soft reference may no longer be valid, but
			 * no harm done. The worst case is if the vnode was
			 * recycled and has another valid lease reference,
			 * which is dereferenced prematurely.
			 */
			lp->lc_vp->v_lease = (struct nqlease *)0;
			lph = &lp->lc_host;
			lphnext = lp->lc_morehosts;
			olphnext = (struct nqm *)0;
			len = 1;
			i = 0;
			ok = 1;
			while (ok && (lph->lph_flag & LC_VALID)) {
				if (lph->lph_flag & LC_CLTP)
					MFREE(lph->lph_nam, n);
I 5
				if (lph->lph_flag & LC_SREF)
					nfsrv_slpderef(lph->lph_slp);
E 5
				if (++i == len) {
					if (olphnext) {
						free((caddr_t)olphnext, M_NQMHOST);
						olphnext = (struct nqm *)0;
					}
					if (lphnext) {
						olphnext = lphnext;
						i = 0;
						len = LC_MOREHOSTSIZ;
						lph = lphnext->lpm_hosts;
						lphnext = lphnext->lpm_next;
					} else
						ok = 0;
				} else
					lph++;
			}
			FREE((caddr_t)lp, M_NQLEASE);
			if (olphnext)
				free((caddr_t)olphnext, M_NQMHOST);
			nfsstats.srvnqnfs_leases--;
		    }
		}
D 33
		lp = nextlp;
E 33
	}
}

/*
 * Called from nfssvc_nfsd() for a getlease rpc request.
 * Do the from/to xdr translation and call nqsrv_getlease() to
 * do the real work.
 */
D 34
nqnfsrv_getlease(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
	struct mbuf *nam, **mrq;
E 34
I 34
int
nqnfsrv_getlease(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 34
{
I 14
D 17
	USES_VOP_GETATTR;
E 17
E 14
D 34
	register struct nfsv2_fattr *fp;
E 34
I 34
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
	register struct nfs_fattr *fp;
E 34
	struct vattr va;
	register struct vattr *vap = &va;
	struct vnode *vp;
D 34
	nfsv2fh_t nfh;
E 34
I 34
	nfsfh_t nfh;
E 34
	fhandle_t *fhp;
	register u_long *tl;
	register long t1;
	u_quad_t frev;
	caddr_t bpos;
	int error = 0;
	char *cp2;
	struct mbuf *mb, *mb2, *mreq;
	int flags, rdonly, cache;

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 34
	nfsm_dissect(tl, u_long *, 2*NFSX_UNSIGNED);
E 34
I 34
	nfsm_dissect(tl, u_long *, 2 * NFSX_UNSIGNED);
E 34
	flags = fxdr_unsigned(int, *tl++);
	nfsd->nd_duration = fxdr_unsigned(int, *tl);
D 31
	if (error = nfsrv_fhtovp(fhp, TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 31
I 31
D 34
	if (error = nfsrv_fhtovp(fhp,
	    TRUE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
E 34
I 34
	error = nfsrv_fhtovp(fhp, 1, &vp, cred, slp, nam, &rdonly,
		(nfsd->nd_flag & ND_KERBAUTH));
	if (error)
E 34
E 31
		nfsm_reply(0);
D 34
	if (rdonly && flags == NQL_WRITE) {
E 34
I 34
	if (rdonly && flags == ND_WRITE) {
		vput(vp);
E 34
		error = EROFS;
		nfsm_reply(0);
	}
D 34
	(void) nqsrv_getlease(vp, &nfsd->nd_duration, flags, nfsd,
E 34
I 34
	(void) nqsrv_getlease(vp, &nfsd->nd_duration, flags, slp, procp,
E 34
		nam, &cache, &frev, cred);
D 34
	error = VOP_GETATTR(vp, vap, cred, nfsd->nd_procp);
E 34
I 34
	error = VOP_GETATTR(vp, vap, cred, procp);
E 34
	vput(vp);
D 19
	nfsm_reply(NFSX_FATTR + 4*NFSX_UNSIGNED);
E 19
I 19
D 34
	nfsm_reply(NFSX_NQFATTR + 4*NFSX_UNSIGNED);
E 19
	nfsm_build(tl, u_long *, 4*NFSX_UNSIGNED);
E 34
I 34
	nfsm_reply(NFSX_V3FATTR + 4 * NFSX_UNSIGNED);
	nfsm_build(tl, u_long *, 4 * NFSX_UNSIGNED);
E 34
	*tl++ = txdr_unsigned(cache);
	*tl++ = txdr_unsigned(nfsd->nd_duration);
	txdr_hyper(&frev, tl);
D 19
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_FATTR);
E 19
I 19
D 34
	nfsm_build(fp, struct nfsv2_fattr *, NFSX_NQFATTR);
E 19
	nfsm_srvfillattr;
E 34
I 34
	nfsm_build(fp, struct nfs_fattr *, NFSX_V3FATTR);
	nfsm_srvfillattr(vap, fp);
E 34
	nfsm_srvdone;
}

/*
 * Called from nfssvc_nfsd() when a "vacated" message is received from a
 * client. Find the entry and expire it.
 */
D 34
nqnfsrv_vacated(nfsd, mrep, md, dpos, cred, nam, mrq)
	struct nfsd *nfsd;
	struct mbuf *mrep, *md;
	caddr_t dpos;
	struct ucred *cred;
	struct mbuf *nam, **mrq;
E 34
I 34
int
nqnfsrv_vacated(nfsd, slp, procp, mrq)
	struct nfsrv_descript *nfsd;
	struct nfssvc_sock *slp;
	struct proc *procp;
	struct mbuf **mrq;
E 34
{
I 34
	struct mbuf *mrep = nfsd->nd_mrep, *md = nfsd->nd_md;
	struct mbuf *nam = nfsd->nd_nam;
	caddr_t dpos = nfsd->nd_dpos;
	struct ucred *cred = &nfsd->nd_cr;
E 34
	register struct nqlease *lp;
	register struct nqhost *lph;
	struct nqlease *tlp = (struct nqlease *)0;
D 31
	struct vnode *vp;
E 31
D 34
	nfsv2fh_t nfh;
E 34
I 34
	nfsfh_t nfh;
E 34
	fhandle_t *fhp;
	register u_long *tl;
	register long t1;
	struct nqm *lphnext;
D 31
	union nqsrvthead *lhp;
	u_quad_t frev;
	int error = 0, i, len, ok, rdonly, gotit = 0;
E 31
I 31
D 34
	int error = 0, i, len, ok, gotit = 0;
E 31
	char *cp2;
E 34
I 34
	struct mbuf *mreq, *mb;
	int error = 0, i, len, ok, gotit = 0, cache = 0;
	char *cp2, *bpos;
	u_quad_t frev;
E 34

	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
D 24
	if (error = nfsrv_fhtovp(fhp, FALSE, &vp, cred, nfsd->nd_slp, nam, &rdonly))
		return (error);
E 24
	m_freem(mrep);
D 24
	tlp = vp->v_lease;
	if (tlp == (struct nqlease *)0) {
		/*
		 * Find the lease by searching the hash list.
		 */
D 18
		lhp = &nqfhead[NQFHHASH(fhp->fh_fid.fid_data)];
		for (lp = lhp->th_chain[0]; lp != (struct nqlease *)lhp;
			lp = lp->lc_fhnext)
E 18
I 18
		for (lp = nqfhead[NQFHHASH(fhp->fh_fid.fid_data)]; lp;
		     lp = lp->lc_fhnext)
E 18
D 2
			if (QUADEQ(fhp->fh_fsid, lp->lc_fsid) &&
E 2
I 2
			if (fhp->fh_fsid.val[0] == lp->lc_fsid.val[0] &&
			    fhp->fh_fsid.val[1] == lp->lc_fsid.val[1] &&
E 2
			    !bcmp(fhp->fh_fid.fid_data, lp->lc_fiddata,
				  MAXFIDSZ)) {
				/* Found it */
				lp->lc_vp = vp;
				vp->v_lease = lp;
				tlp = lp;
				break;
			}
	}
	vrele(vp);
E 24
I 24
	/*
	 * Find the lease by searching the hash list.
	 */
D 33
	for (lp = nqfhead[NQFHHASH(fhp->fh_fid.fid_data)]; lp;
	     lp = lp->lc_fhnext)
E 33
I 33
	for (lp = NQFHHASH(fhp->fh_fid.fid_data)->lh_first; lp != 0;
	    lp = lp->lc_hash.le_next)
E 33
		if (fhp->fh_fsid.val[0] == lp->lc_fsid.val[0] &&
		    fhp->fh_fsid.val[1] == lp->lc_fsid.val[1] &&
		    !bcmp(fhp->fh_fid.fid_data, lp->lc_fiddata,
			  MAXFIDSZ)) {
			/* Found it */
			tlp = lp;
			break;
		}
E 24
D 33
	if (tlp) {
E 33
I 33
D 34
	if (tlp != 0) {
E 34
I 34
	if (tlp) {
E 34
E 33
		lp = tlp;
		len = 1;
		i = 0;
		lph = &lp->lc_host;
		lphnext = lp->lc_morehosts;
		ok = 1;
		while (ok && (lph->lph_flag & LC_VALID)) {
D 34
			if (nqsrv_cmpnam(nfsd->nd_slp, nam, lph)) {
E 34
I 34
			if (nqsrv_cmpnam(slp, nam, lph)) {
E 34
				lph->lph_flag |= LC_VACATED;
				gotit++;
				break;
			}
			if (++i == len) {
				if (lphnext) {
					len = LC_MOREHOSTSIZ;
					i = 0;
					lph = lphnext->lpm_hosts;
					lphnext = lphnext->lpm_next;
				} else
					ok = 0;
			} else
				lph++;
		}
		if ((lp->lc_flag & LC_EXPIREDWANTED) && gotit) {
			lp->lc_flag &= ~LC_EXPIREDWANTED;
			wakeup((caddr_t)&lp->lc_flag);
		}
nfsmout:
		return (EPERM);
	}
	return (EPERM);
}

/*
 * Client get lease rpc function.
 */
I 34
int
E 34
nqnfs_getlease(vp, rwflag, cred, p)
	register struct vnode *vp;
	int rwflag;
	struct ucred *cred;
	struct proc *p;
{
	register u_long *tl;
	register caddr_t cp;
D 34
	register long t1;
E 34
I 34
	register long t1, t2;
E 34
D 31
	register struct nfsnode *np, *tp;
E 31
I 31
	register struct nfsnode *np;
E 31
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	caddr_t bpos, dpos, cp2;
	time_t reqtime;
	int error = 0;
	struct mbuf *mreq, *mrep, *md, *mb, *mb2;
	int cachable;
I 19
	u_quad_t frev;
E 19
	
	nfsstats.rpccnt[NQNFSPROC_GETLEASE]++;
D 34
	mb = mreq = nfsm_reqh(vp, NQNFSPROC_GETLEASE, NFSX_FH+2*NFSX_UNSIGNED,
E 34
I 34
	mb = mreq = nfsm_reqh(vp, NQNFSPROC_GETLEASE, NFSX_V3FH+2*NFSX_UNSIGNED,
E 34
		 &bpos);
D 34
	nfsm_fhtom(vp);
	nfsm_build(tl, u_long *, 2*NFSX_UNSIGNED);
E 34
I 34
	nfsm_fhtom(vp, 1);
	nfsm_build(tl, u_long *, 2 * NFSX_UNSIGNED);
E 34
	*tl++ = txdr_unsigned(rwflag);
	*tl = txdr_unsigned(nmp->nm_leaseterm);
	reqtime = time.tv_sec;
	nfsm_request(vp, NQNFSPROC_GETLEASE, p, cred);
	np = VTONFS(vp);
D 34
	nfsm_dissect(tl, u_long *, 4*NFSX_UNSIGNED);
E 34
I 34
	nfsm_dissect(tl, u_long *, 4 * NFSX_UNSIGNED);
E 34
	cachable = fxdr_unsigned(int, *tl++);
	reqtime += fxdr_unsigned(int, *tl++);
	if (reqtime > time.tv_sec) {
D 19
		if (np->n_tnext) {
			if (np->n_tnext == (struct nfsnode *)nmp)
				nmp->nm_tprev = np->n_tprev;
			else
				np->n_tnext->n_tprev = np->n_tprev;
			if (np->n_tprev == (struct nfsnode *)nmp)
				nmp->nm_tnext = np->n_tnext;
			else
				np->n_tprev->n_tnext = np->n_tnext;
			if (rwflag == NQL_WRITE)
				np->n_flag |= NQNFSWRITE;
		} else if (rwflag == NQL_READ)
			np->n_flag &= ~NQNFSWRITE;
		else
			np->n_flag |= NQNFSWRITE;
		if (cachable)
			np->n_flag &= ~NQNFSNONCACHE;
		else
			np->n_flag |= NQNFSNONCACHE;
		np->n_expiry = reqtime;
		fxdr_hyper(tl, &np->n_lrev);
		tp = nmp->nm_tprev;
		while (tp != (struct nfsnode *)nmp && tp->n_expiry > np->n_expiry)
			tp = tp->n_tprev;
		if (tp == (struct nfsnode *)nmp) {
			np->n_tnext = nmp->nm_tnext;
			nmp->nm_tnext = np;
		} else {
			np->n_tnext = tp->n_tnext;
			tp->n_tnext = np;
		}
		np->n_tprev = tp;
		if (np->n_tnext == (struct nfsnode *)nmp)
			nmp->nm_tprev = np;
		else
			np->n_tnext->n_tprev = np;
E 19
I 19
		fxdr_hyper(tl, &frev);
		nqnfs_clientlease(nmp, np, rwflag, cachable, reqtime, frev);
E 19
		nfsm_loadattr(vp, (struct vattr *)0);
	} else
		error = NQNFS_EXPIRED;
	nfsm_reqdone;
	return (error);
}

/*
 * Client vacated message function.
 */
I 34
int
E 34
nqnfs_vacated(vp, cred)
	register struct vnode *vp;
	struct ucred *cred;
{
	register caddr_t cp;
	register struct mbuf *m;
	register int i;
I 34
	register u_long *tl;
	register long t1, t2;
E 34
	caddr_t bpos;
	u_long xid;
	int error = 0;
	struct mbuf *mreq, *mb, *mb2, *mheadend;
	struct nfsmount *nmp;
	struct nfsreq myrep;
	
	nmp = VFSTONFS(vp->v_mount);
	nfsstats.rpccnt[NQNFSPROC_VACATED]++;
D 34
	nfsm_reqhead(vp, NQNFSPROC_VACATED, NFSX_FH);
	nfsm_fhtom(vp);
E 34
I 34
	nfsm_reqhead(vp, NQNFSPROC_VACATED, NFSX_V3FH);
	nfsm_fhtom(vp, 1);
E 34
	m = mreq;
	i = 0;
	while (m) {
		i += m->m_len;
		m = m->m_next;
	}
D 34
	m = nfsm_rpchead(cred, TRUE, NQNFSPROC_VACATED,
		RPCAUTH_UNIX, 5*NFSX_UNSIGNED, (char *)0,
E 34
I 34
	m = nfsm_rpchead(cred, nmp->nm_flag, NQNFSPROC_VACATED,
		RPCAUTH_UNIX, 5 * NFSX_UNSIGNED, (char *)0,
E 34
		mreq, i, &mheadend, &xid);
	if (nmp->nm_sotype == SOCK_STREAM) {
		M_PREPEND(m, NFSX_UNSIGNED, M_WAIT);
		*mtod(m, u_long *) = htonl(0x80000000 | (m->m_pkthdr.len -
			NFSX_UNSIGNED));
	}
	myrep.r_flags = 0;
	myrep.r_nmp = nmp;
	if (nmp->nm_soflags & PR_CONNREQUIRED)
		(void) nfs_sndlock(&nmp->nm_flag, (struct nfsreq *)0);
	(void) nfs_send(nmp->nm_so, nmp->nm_nam, m, &myrep);
	if (nmp->nm_soflags & PR_CONNREQUIRED)
		nfs_sndunlock(&nmp->nm_flag);
I 34
nfsmout:
E 34
	return (error);
}

/*
 * Called for client side callbacks
 */
I 34
int
E 34
nqnfs_callback(nmp, mrep, md, dpos)
	struct nfsmount *nmp;
	struct mbuf *mrep, *md;
	caddr_t dpos;
{
	register struct vnode *vp;
	register u_long *tl;
	register long t1;
D 34
	nfsv2fh_t nfh;
E 34
I 34
	nfsfh_t nfh;
E 34
	fhandle_t *fhp;
	struct nfsnode *np;
D 34
	struct nfsd nd;
	int error;
	char *cp2;
E 34
I 34
	struct nfsd tnfsd;
	struct nfssvc_sock *slp;
	struct nfsrv_descript ndesc;
	register struct nfsrv_descript *nfsd = &ndesc;
	struct mbuf **mrq = (struct mbuf **)0, *mb, *mreq;
	int error = 0, cache = 0;
	char *cp2, *bpos;
	u_quad_t frev;
E 34

D 34
	nd.nd_mrep = mrep;
	nd.nd_md = md;
	nd.nd_dpos = dpos;
	if (error = nfs_getreq(&nd, FALSE))
E 34
I 34
#ifndef nolint
	slp = NULL;
#endif
	nfsd->nd_mrep = mrep;
	nfsd->nd_md = md;
	nfsd->nd_dpos = dpos;
	error = nfs_getreq(nfsd, &tnfsd, FALSE);
	if (error)
E 34
		return (error);
D 34
	md = nd.nd_md;
	dpos = nd.nd_dpos;
	if (nd.nd_procnum != NQNFSPROC_EVICTED) {
E 34
I 34
	md = nfsd->nd_md;
	dpos = nfsd->nd_dpos;
	if (nfsd->nd_procnum != NQNFSPROC_EVICTED) {
E 34
		m_freem(mrep);
		return (EPERM);
	}
	fhp = &nfh.fh_generic;
	nfsm_srvmtofh(fhp);
	m_freem(mrep);
D 34
	if (error = nfs_nget(nmp->nm_mountp, fhp, &np))
E 34
I 34
	error = nfs_nget(nmp->nm_mountp, (nfsfh_t *)fhp, NFSX_V3FH, &np);
	if (error)
E 34
		return (error);
	vp = NFSTOV(np);
D 33
	if (np->n_tnext) {
E 33
I 33
	if (np->n_timer.cqe_next != 0) {
E 33
		np->n_expiry = 0;
		np->n_flag |= NQNFSEVICTED;
D 33
		if (np->n_tprev != (struct nfsnode *)nmp) {
			if (np->n_tnext == (struct nfsnode *)nmp)
				nmp->nm_tprev = np->n_tprev;
			else
				np->n_tnext->n_tprev = np->n_tprev;
			np->n_tprev->n_tnext = np->n_tnext;
			np->n_tnext = nmp->nm_tnext;
			nmp->nm_tnext = np;
			np->n_tprev = (struct nfsnode *)nmp;
			if (np->n_tnext == (struct nfsnode *)nmp)
				nmp->nm_tprev = np;
			else
				np->n_tnext->n_tprev = np;
E 33
I 33
		if (nmp->nm_timerhead.cqh_first != np) {
			CIRCLEQ_REMOVE(&nmp->nm_timerhead, np, n_timer);
			CIRCLEQ_INSERT_HEAD(&nmp->nm_timerhead, np, n_timer);
E 33
		}
	}
	vrele(vp);
	nfsm_srvdone;
}

/*
 * Nqnfs client helper daemon. Runs once a second to expire leases.
 * It also get authorization strings for "kerb" mounts.
 * It must start at the beginning of the list again after any potential
 * "sleep" since nfs_reclaim() called from vclean() can pull a node off
 * the list asynchronously.
 */
I 34
int
E 34
nqnfs_clientd(nmp, cred, ncd, flag, argp, p)
	register struct nfsmount *nmp;
	struct ucred *cred;
	struct nfsd_cargs *ncd;
	int flag;
	caddr_t argp;
	struct proc *p;
{
I 15
D 17
	USES_VOP_FSYNC;
E 17
E 15
	register struct nfsnode *np;
	struct vnode *vp;
I 28
	struct nfsreq myrep;
E 28
D 34
	int error, vpid;
E 34
I 34
	struct nfsuid *nuidp, *nnuidp;
	int error = 0, vpid;
E 34

	/*
	 * First initialize some variables
	 */
D 34
	nqnfs_prog = txdr_unsigned(NQNFS_PROG);
	nqnfs_vers = txdr_unsigned(NQNFS_VER1);
E 34

	/*
	 * If an authorization string is being passed in, get it.
	 */
	if ((flag & NFSSVC_GOTAUTH) &&
D 34
		(nmp->nm_flag & (NFSMNT_WAITAUTH | NFSMNT_DISMNT)) == 0) {
		if (nmp->nm_flag & NFSMNT_HASAUTH)
			panic("cld kerb");
		if ((flag & NFSSVC_AUTHINFAIL) == 0) {
			if (ncd->ncd_authlen <= RPCAUTH_MAXSIZ &&
				copyin(ncd->ncd_authstr, nmp->nm_authstr,
				ncd->ncd_authlen) == 0) {
				nmp->nm_authtype = ncd->ncd_authtype;
				nmp->nm_authlen = ncd->ncd_authlen;
			} else
				nmp->nm_flag |= NFSMNT_AUTHERR;
E 34
I 34
	    (nmp->nm_flag & (NFSMNT_WAITAUTH | NFSMNT_DISMNT)) == 0) {
	    if (nmp->nm_flag & NFSMNT_HASAUTH)
		panic("cld kerb");
	    if ((flag & NFSSVC_AUTHINFAIL) == 0) {
		if (ncd->ncd_authlen <= nmp->nm_authlen &&
		    ncd->ncd_verflen <= nmp->nm_verflen &&
		    !copyin(ncd->ncd_authstr,nmp->nm_authstr,ncd->ncd_authlen)&&
		    !copyin(ncd->ncd_verfstr,nmp->nm_verfstr,ncd->ncd_verflen)){
		    nmp->nm_authtype = ncd->ncd_authtype;
		    nmp->nm_authlen = ncd->ncd_authlen;
		    nmp->nm_verflen = ncd->ncd_verflen;
#ifdef NFSKERB
		    nmp->nm_key = ncd->ncd_key;
#endif
E 34
		} else
D 34
			nmp->nm_flag |= NFSMNT_AUTHERR;
		nmp->nm_flag |= NFSMNT_HASAUTH;
		wakeup((caddr_t)&nmp->nm_authlen);
E 34
I 34
		    nmp->nm_flag |= NFSMNT_AUTHERR;
	    } else
		nmp->nm_flag |= NFSMNT_AUTHERR;
	    nmp->nm_flag |= NFSMNT_HASAUTH;
	    wakeup((caddr_t)&nmp->nm_authlen);
E 34
	} else
D 34
		nmp->nm_flag |= NFSMNT_WAITAUTH;
E 34
I 34
	    nmp->nm_flag |= NFSMNT_WAITAUTH;
E 34

	/*
	 * Loop every second updating queue until there is a termination sig.
	 */
	while ((nmp->nm_flag & NFSMNT_DISMNT) == 0) {
	    if (nmp->nm_flag & NFSMNT_NQNFS) {
I 28
		/*
		 * If there are no outstanding requests (and therefore no
		 * processes in nfs_reply) and there is data in the receive
		 * queue, poke for callbacks.
		 */
D 33
		if (nfsreqh.r_next == &nfsreqh && nmp->nm_so &&
E 33
I 33
		if (nfs_reqq.tqh_first == 0 && nmp->nm_so &&
E 33
		    nmp->nm_so->so_rcv.sb_cc > 0) {
		    myrep.r_flags = R_GETONEREP;
		    myrep.r_nmp = nmp;
		    myrep.r_mrep = (struct mbuf *)0;
		    myrep.r_procp = (struct proc *)0;
		    (void) nfs_reply(&myrep);
		}

		/*
		 * Loop through the leases, updating as required.
		 */
E 28
D 33
		np = nmp->nm_tnext;
		while (np != (struct nfsnode *)nmp &&
E 33
I 33
		np = nmp->nm_timerhead.cqh_first;
		while (np != (void *)&nmp->nm_timerhead &&
E 33
		       (nmp->nm_flag & NFSMNT_DISMINPROG) == 0) {
			vp = NFSTOV(np);
D 34
if (vp->v_mount->mnt_stat.f_fsid.val[1] != MOUNT_NFS) panic("trash2");
E 34
			vpid = vp->v_id;
			if (np->n_expiry < time.tv_sec) {
D 30
			   if (vget(vp) == 0) {
E 30
I 30
D 36
			   if (vget(vp, 1) == 0) {
E 36
I 36
			   if (vget(vp, LK_EXCLUSIVE, p) == 0) {
E 36
E 30
			     nmp->nm_inprog = vp;
			     if (vpid == vp->v_id) {
D 34
if (vp->v_mount->mnt_stat.f_fsid.val[1] != MOUNT_NFS) panic("trash3");
E 34
D 33
				if (np->n_tnext == (struct nfsnode *)nmp)
					nmp->nm_tprev = np->n_tprev;
				else
					np->n_tnext->n_tprev = np->n_tprev;
				if (np->n_tprev == (struct nfsnode *)nmp)
					nmp->nm_tnext = np->n_tnext;
				else
					np->n_tprev->n_tnext = np->n_tnext;
				np->n_tnext = (struct nfsnode *)0;
E 33
I 33
				CIRCLEQ_REMOVE(&nmp->nm_timerhead, np, n_timer);
				np->n_timer.cqe_next = 0;
E 33
				if ((np->n_flag & (NMODIFIED | NQNFSEVICTED))
				    && vp->v_type == VREG) {
D 23
					np->n_flag &= ~NMODIFIED;
E 23
					if (np->n_flag & NQNFSEVICTED) {
D 15
						vinvalbuf(vp, TRUE);
E 15
I 15
D 23
						(void) vinvalbuf(vp, TRUE,
						    cred, p);
E 23
I 23
D 26
						NFS_VINVBUF(np, vp,
						            TRUE, cred, p);
E 26
I 26
						(void) nfs_vinvalbuf(vp,
						       V_SAVE, cred, p, 0);
E 26
E 23
E 15
						np->n_flag &= ~NQNFSEVICTED;
I 4
						(void) nqnfs_vacated(vp, cred);
E 4
D 23
					} else
E 23
I 23
					} else {
D 26
						np->n_flag &= ~NMODIFIED;
E 26
E 23
D 15
						vflushbuf(vp, B_SYNC);
E 15
I 15
						(void) VOP_FSYNC(vp, cred,
						    MNT_WAIT, p);
I 26
						np->n_flag &= ~NMODIFIED;
E 26
I 23
					}
E 23
E 15
D 4
					(void) nqnfs_vacated(vp, cred);
E 4
				}
			      }
			      vrele(vp);
			      nmp->nm_inprog = NULLVP;
			    }
D 33
			    if (np != nmp->nm_tnext)
				np = nmp->nm_tnext;
			    else
				break;
E 33
			} else if ((np->n_expiry - NQ_RENEWAL) < time.tv_sec) {
			    if ((np->n_flag & (NQNFSWRITE | NQNFSNONCACHE))
D 21
				 == NQNFSWRITE && vp->v_dirtyblkhd &&
E 21
I 21
D 30
				 == NQNFSWRITE && vp->v_dirtyblkhd.le_next &&
E 21
				 vget(vp) == 0) {
E 30
I 30
				 == NQNFSWRITE && vp->v_dirtyblkhd.lh_first &&
D 36
				 vget(vp, 1) == 0) {
E 36
I 36
				 vget(vp, LK_EXCLUSIVE, p) == 0) {
E 36
E 30
				 nmp->nm_inprog = vp;
D 34
if (vp->v_mount->mnt_stat.f_fsid.val[1] != MOUNT_NFS) panic("trash4");
E 34
				 if (vpid == vp->v_id &&
D 34
				     nqnfs_getlease(vp, NQL_WRITE, cred, p)==0)
E 34
I 34
				     nqnfs_getlease(vp, ND_WRITE, cred, p)==0)
E 34
					np->n_brev = np->n_lrev;
				 vrele(vp);
				 nmp->nm_inprog = NULLVP;
			    }
D 33
			    if (np != nmp->nm_tnext)
				np = nmp->nm_tnext;
			    else
				break;
E 33
			} else
				break;
I 33
			if (np == nmp->nm_timerhead.cqh_first)
				break;
			np = nmp->nm_timerhead.cqh_first;
E 33
		}
	    }

	    /*
	     * Get an authorization string, if required.
	     */
	    if ((nmp->nm_flag & (NFSMNT_WAITAUTH | NFSMNT_DISMNT | NFSMNT_HASAUTH)) == 0) {
		ncd->ncd_authuid = nmp->nm_authuid;
D 26
		if (copyout((caddr_t)ncd, argp, sizeof (*ncd)))
E 26
I 26
		if (copyout((caddr_t)ncd, argp, sizeof (struct nfsd_cargs)))
E 26
			nmp->nm_flag |= NFSMNT_WAITAUTH;
		else
			return (ENEEDAUTH);
	    }

	    /*
	     * Wait a bit (no pun) and do it again.
	     */
	    if ((nmp->nm_flag & NFSMNT_DISMNT) == 0 &&
		(nmp->nm_flag & (NFSMNT_WAITAUTH | NFSMNT_HASAUTH))) {
		    error = tsleep((caddr_t)&nmp->nm_authstr, PSOCK | PCATCH,
			"nqnfstimr", hz / 3);
		    if (error == EINTR || error == ERESTART)
D 25
			(void) dounmount(nmp->nm_mountp, MNT_NOFORCE);
E 25
I 25
D 27
			(void) dounmount(nmp->nm_mountp, 0);
E 27
I 27
			(void) dounmount(nmp->nm_mountp, 0, p);
E 27
E 25
	    }
	}
I 34

	/*
	 * Finally, we can free up the mount structure.
	 */
	for (nuidp = nmp->nm_uidlruhead.tqh_first; nuidp != 0; nuidp = nnuidp) {
		nnuidp = nuidp->nu_lru.tqe_next;
		LIST_REMOVE(nuidp, nu_hash);
		TAILQ_REMOVE(&nmp->nm_uidlruhead, nuidp, nu_lru);
		free((caddr_t)nuidp, M_NFSUID);
	}
E 34
	free((caddr_t)nmp, M_NFSMNT);
	if (error == EWOULDBLOCK)
		error = 0;
	return (error);
}

/*
 * Adjust all timer queue expiry times when the time of day clock is changed.
 * Called from the settimeofday() syscall.
 */
void
D 34
lease_updatetime(deltat)
E 34
I 34
nqnfs_lease_updatetime(deltat)
E 34
	register int deltat;
{
D 37
	register struct nqlease *lp;
	register struct nfsnode *np;
	struct mount *mp;
E 37
I 37
	struct proc *p = curproc;	/* XXX */
	struct nqlease *lp;
	struct nfsnode *np;
	struct mount *mp, *nxtmp;
E 37
	struct nfsmount *nmp;
	int s;

	if (nqnfsstarttime != 0)
		nqnfsstarttime += deltat;
	s = splsoftclock();
D 33
	lp = nqthead.th_chain[0];
	while (lp != (struct nqlease *)&nqthead) {
E 33
I 33
	for (lp = nqtimerhead.cqh_first; lp != (void *)&nqtimerhead;
	    lp = lp->lc_timer.cqe_next)
E 33
		lp->lc_expiry += deltat;
D 33
		lp = lp->lc_chain1[0];
	}
E 33
	splx(s);

	/*
	 * Search the mount list for all nqnfs mounts and do their timer
	 * queues.
	 */
D 30
	mp = rootfs;
	do {
E 30
I 30
D 35
	for (mp = mountlist.tqh_first; mp != NULL; mp = mp->mnt_list.tqe_next) {
E 35
I 35
D 37
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist;
	     mp = mp->mnt_list.cqe_next) {
E 35
E 30
D 34
		if (mp->mnt_stat.f_fsid.val[1] == MOUNT_NFS) {
			nmp = VFSTONFS(mp);
			if (nmp->nm_flag & NFSMNT_NQNFS) {
D 33
				np = nmp->nm_tnext;
				while (np != (struct nfsnode *)nmp) {
E 33
I 33
				for (np = nmp->nm_timerhead.cqh_first;
				    np != (void *)&nmp->nm_timerhead;
				    np = np->n_timer.cqe_next) {
E 33
					np->n_expiry += deltat;
D 33
					np = np->n_tnext;
E 33
				}
E 34
I 34
		if (mp->mnt_stat.f_type != nfs_mount_type)
E 37
I 37
	simple_lock(&mountlist_slock);
	for (mp = mountlist.cqh_first; mp != (void *)&mountlist; mp = nxtmp) {
		if (vfs_busy(mp, LK_NOWAIT, &mountlist_slock, p)) {
			nxtmp = mp->mnt_list.cqe_next;
E 37
			continue;
D 37
		nmp = VFSTONFS(mp);
		if (nmp->nm_flag & NFSMNT_NQNFS) {
			for (np = nmp->nm_timerhead.cqh_first;
			    np != (void *)&nmp->nm_timerhead;
			    np = np->n_timer.cqe_next) {
				np->n_expiry += deltat;
E 37
I 37
		}
		if (mp->mnt_stat.f_type == nfs_mount_type) {
			nmp = VFSTONFS(mp);
			if (nmp->nm_flag & NFSMNT_NQNFS) {
				for (np = nmp->nm_timerhead.cqh_first;
				    np != (void *)&nmp->nm_timerhead;
				    np = np->n_timer.cqe_next) {
					np->n_expiry += deltat;
				}
E 37
E 34
			}
		}
I 37
		simple_lock(&mountlist_slock);
		nxtmp = mp->mnt_list.cqe_next;
		vfs_unbusy(mp, p);
E 37
D 30
		mp = mp->mnt_next;
	} while (mp != rootfs);
E 30
I 30
	}
I 37
	simple_unlock(&mountlist_slock);
E 37
E 30
}

/*
 * Lock a server lease.
 */
void
nqsrv_locklease(lp)
	struct nqlease *lp;
{

	while (lp->lc_flag & LC_LOCKED) {
		lp->lc_flag |= LC_WANTED;
		(void) tsleep((caddr_t)lp, PSOCK, "nqlc", 0);
	}
	lp->lc_flag |= LC_LOCKED;
	lp->lc_flag &= ~LC_WANTED;
}

/*
 * Unlock a server lease.
 */
void
nqsrv_unlocklease(lp)
	struct nqlease *lp;
{

	lp->lc_flag &= ~LC_LOCKED;
	if (lp->lc_flag & LC_WANTED)
		wakeup((caddr_t)lp);
I 19
}

/*
 * Update a client lease.
 */
void
nqnfs_clientlease(nmp, np, rwflag, cachable, expiry, frev)
	register struct nfsmount *nmp;
	register struct nfsnode *np;
	int rwflag, cachable;
	time_t expiry;
	u_quad_t frev;
{
	register struct nfsnode *tp;

D 33
	if (np->n_tnext) {
		if (np->n_tnext == (struct nfsnode *)nmp)
			nmp->nm_tprev = np->n_tprev;
		else
			np->n_tnext->n_tprev = np->n_tprev;
		if (np->n_tprev == (struct nfsnode *)nmp)
			nmp->nm_tnext = np->n_tnext;
		else
			np->n_tprev->n_tnext = np->n_tnext;
E 33
I 33
	if (np->n_timer.cqe_next != 0) {
		CIRCLEQ_REMOVE(&nmp->nm_timerhead, np, n_timer);
E 33
D 34
		if (rwflag == NQL_WRITE)
E 34
I 34
		if (rwflag == ND_WRITE)
E 34
			np->n_flag |= NQNFSWRITE;
D 34
	} else if (rwflag == NQL_READ)
E 34
I 34
	} else if (rwflag == ND_READ)
E 34
		np->n_flag &= ~NQNFSWRITE;
	else
		np->n_flag |= NQNFSWRITE;
	if (cachable)
		np->n_flag &= ~NQNFSNONCACHE;
	else
		np->n_flag |= NQNFSNONCACHE;
	np->n_expiry = expiry;
	np->n_lrev = frev;
D 33
	tp = nmp->nm_tprev;
	while (tp != (struct nfsnode *)nmp && tp->n_expiry > np->n_expiry)
		tp = tp->n_tprev;
	if (tp == (struct nfsnode *)nmp) {
		np->n_tnext = nmp->nm_tnext;
		nmp->nm_tnext = np;
E 33
I 33
	tp = nmp->nm_timerhead.cqh_last;
	while (tp != (void *)&nmp->nm_timerhead && tp->n_expiry > np->n_expiry)
		tp = tp->n_timer.cqe_prev;
	if (tp == (void *)&nmp->nm_timerhead) {
		CIRCLEQ_INSERT_HEAD(&nmp->nm_timerhead, np, n_timer);
E 33
	} else {
D 33
		np->n_tnext = tp->n_tnext;
		tp->n_tnext = np;
E 33
I 33
		CIRCLEQ_INSERT_AFTER(&nmp->nm_timerhead, tp, np, n_timer);
E 33
	}
D 33
	np->n_tprev = tp;
	if (np->n_tnext == (struct nfsnode *)nmp)
		nmp->nm_tprev = np;
	else
		np->n_tnext->n_tprev = np;
E 33
E 19
}
E 1
