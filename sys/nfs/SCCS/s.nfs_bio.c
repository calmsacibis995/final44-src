h29387
s 00211/00115/00666
d D 8.9 95/03/30 11:26:55 mckusick 56 55
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00004/00002/00777
d D 8.8 95/01/09 17:27:38 mckusick 55 54
c update from Rick Macklem
e
s 00001/00000/00778
d D 8.7 94/08/11 11:59:17 mckusick 54 53
c bug fix from Macklem
e
s 00005/00000/00773
d D 8.6 94/06/08 16:00:16 hibler 53 52
c on write, be sure to flush the vnode from the VM object cache
e
s 00001/00001/00772
d D 8.5 94/01/04 21:57:58 bostic 52 51
c lint
e
s 00001/00002/00772
d D 8.4 93/12/30 16:20:54 mckusick 51 50
c new queue structure
e
s 00001/00001/00773
d D 8.3 93/09/23 15:59:28 bostic 50 49
c changes for 4.4BSD-Lite requested by USL
e
s 00005/00005/00769
d D 8.2 93/09/21 07:41:34 bostic 49 48
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00772
d D 8.1 93/06/10 23:38:39 bostic 48 47
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00773
d D 7.38 93/05/03 18:37:12 mckusick 47 46
c the final polish to leases from Rick Macklem
e
s 00009/00009/00764
d D 7.37 93/02/02 21:08:44 mckusick 46 44
c nfsincore => incore; nfsgetblk => getblk; nfsvinvalbuf => vinvalbuf
e
s 00002/00002/00771
d R 7.37 93/02/02 16:43:33 mckusick 45 44
c nfsvinvalbuf becomes vinvalbuf
e
s 00454/00122/00319
d D 7.36 93/02/02 15:03:39 mckusick 44 43
c update for 4.4BSD from Rick Macklem
e
s 00002/00001/00439
d D 7.35 92/11/05 11:26:05 mckusick 43 42
c paranoid
e
s 00008/00013/00432
d D 7.34 92/11/01 23:16:43 mckusick 42 41
c fix from Jeff Forys for tracking changing NFS file sizes
e
s 00002/00001/00443
d D 7.33 92/10/11 12:35:05 bostic 41 40
c make kernel includes standard
e
s 00004/00001/00440
d D 7.32 92/09/16 18:20:34 mckusick 40 39
c update from Rick Macklem
e
s 00001/00000/00440
d D 7.31 92/07/12 17:34:54 pendry 39 38
c need to include <sys/systm.h>
e
s 00009/00009/00431
d D 7.30 92/07/12 17:16:52 pendry 38 37
c MIN -> min, MAX -> max
e
s 00001/00003/00439
d D 7.29 92/07/03 01:57:33 mckusick 37 36
c delete USES
e
s 00052/00043/00390
d D 7.28 92/06/25 13:11:44 mckusick 36 35
c dump NOQUAD; new parameters to vinvalbuf; cleanup stackable filesystem merge
e
s 00003/00003/00430
d D 7.27 92/06/19 19:29:31 mckusick 35 34
c timeval => timespec in vattr and dinode
e
s 00004/00000/00429
d D 7.26 92/05/20 10:55:19 mckusick 34 33
c update for spec and fifo times for NFS (from Macklem)
e
s 00033/00041/00396
d D 7.25 92/05/15 13:56:47 heideman 33 32
c vnodeop argument macro expansion
e
s 00016/00009/00421
d D 7.24 92/05/14 17:37:06 heideman 32 23
c vnode interface conversion
e
s 00016/00009/00421
d R 7.24 92/05/14 15:54:21 heideman 31 23
c vnode interface conversion
e
s 00016/00009/00421
d R 7.24 92/05/14 14:55:51 heideman 30 23
c vnode interface conversion
e
s 00016/00009/00421
d R 7.24 92/05/14 13:01:07 heideman 29 23
c vnode interface conversion
e
s 00016/00009/00421
d R 7.24 92/05/14 11:58:49 heideman 28 23
c vnode interface conversion
e
s 00027/00006/00424
d R 7.24 92/05/14 10:38:50 heideman 27 23
c vnode interface conversion
e
s 00036/00009/00421
d R 7.24 92/05/13 23:17:58 heideman 26 23
c vnode interface conversion
e
s 00036/00009/00421
d R 7.24 92/05/13 19:02:22 heideman 25 23
c vnode interface conversion
e
s 00036/00009/00421
d R 7.24 92/05/13 18:34:33 heideman 24 23
c vnode interface conversion
e
s 00017/00016/00413
d D 7.23 92/05/04 16:38:33 mckusick 23 22
c lint; clean up include directives
e
s 00012/00000/00417
d D 7.22 92/03/17 12:23:38 mckusick 22 21
c fix for append mode bug (from Rick Macklem)
e
s 00209/00071/00208
d D 7.21 92/01/14 12:41:37 mckusick 21 20
c update from Rick Macklem (including leases)
e
s 00001/00001/00278
d D 7.20 91/12/15 14:44:06 mckusick 20 19
c include ordering
e
s 00017/00007/00262
d D 7.19 91/04/16 00:32:42 mckusick 19 18
c pass proc pointers down to lower levels; use NFS_DIRBLKSIZ
e
s 00008/00005/00261
d D 7.18 91/03/19 11:23:50 karels 18 17
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
e
s 00003/00001/00263
d D 7.17 90/12/05 16:02:30 mckusick 17 16
c update for new VM
e
s 00001/00011/00263
d D 7.16 90/06/28 21:51:39 bostic 16 15
c new copyright notice
e
s 00036/00025/00238
d D 7.15 90/06/21 11:15:48 mckusick 15 14
c "update from Rick Macklem"
e
s 00003/00002/00260
d D 7.14 90/05/18 14:50:03 mckusick 14 13
c "nfs_mknod update from Rick Macklem"
e
s 00077/00041/00185
d D 7.13 90/05/14 11:39:49 mckusick 13 12
c "update from Rick Macklem adding TCP support to NFS"
e
s 00001/00004/00225
d D 7.12 90/02/23 17:03:47 mckusick 12 11
c no longer need to munhash, handled by xuntext instead
e
s 00009/00024/00220
d D 7.11 90/02/08 16:15:28 mckusick 11 10
c use bwrite to avoid getting out of sync with it
e
s 00003/00002/00241
d D 7.10 90/01/14 10:51:48 mckusick 10 9
c n_lastr is replaced by v_lastr
e
s 00003/00002/00240
d D 7.9 90/01/04 22:12:58 mckusick 9 8
c v_blockh is split into clean and dirty lists; count active I/O's
e
s 00011/00068/00231
d D 7.8 89/12/20 17:51:45 mckusick 8 7
c "December update from Rick Macklem"
e
s 00002/00002/00297
d D 7.7 89/11/30 22:50:58 mckusick 7 6
c now use b_lblkno in place of b_blkno
e
s 00000/00001/00299
d D 7.6 89/11/26 14:19:05 mckusick 6 5
c brelvp now implied by setting B_INVAL
e
s 00027/00050/00273
d D 7.5 89/11/22 21:33:04 mckusick 5 4
c locking now done above vnode level; read/write no longer take an offp
e
s 00002/00009/00321
d D 7.4 89/11/03 11:04:24 mckusick 4 3
c lint
e
s 00042/00032/00288
d D 7.3 89/10/21 11:31:19 mckusick 3 2
c "bug fixes and cleanups from Rick Macklem"
e
s 00009/00006/00311
d D 7.2 89/10/19 22:32:18 mckusick 2 1
c "update from Rick Macklem"
e
s 00317/00000/00000
d D 7.1 89/08/30 20:26:15 macklem 1 0
c first buffer cache implementation
e
u
U
t
T
I 1
/*
D 48
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 48
I 48
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 48
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 16
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
 *
 *	%W% (Berkeley) %G%
 */

I 56

E 56
D 23
#include "param.h"
I 21
#include "resourcevar.h"
E 21
D 18
#include "user.h"
E 18
I 18
#include "proc.h"
E 18
#include "buf.h"
I 19
D 21
#include "uio.h"
#include "namei.h"
E 21
E 19
#include "vnode.h"
#include "trace.h"
#include "mount.h"
I 18
D 21
#include "resourcevar.h"

E 21
I 21
#include "kernel.h"
#include "machine/endian.h"
#include "nfsnode.h"
#include "rpcv2.h"
E 21
E 18
D 20
#include "nfsnode.h"
E 20
I 8
#include "nfsv2.h"
#include "nfs.h"
I 20
D 21
#include "nfsnode.h"
E 20
E 8
#include "nfsiom.h"
E 21
I 13
#include "nfsmount.h"
I 21
#include "nqnfs.h"
E 23
I 23
#include <sys/param.h>
I 39
#include <sys/systm.h>
E 39
#include <sys/resourcevar.h>
I 56
#include <sys/signalvar.h>
E 56
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/vnode.h>
#include <sys/trace.h>
#include <sys/mount.h>
#include <sys/kernel.h>
D 41
#include <machine/endian.h>
E 41
I 41

E 41
#include <vm/vm.h>
I 41

E 41
D 56
#include <nfs/nfsnode.h>
E 56
#include <nfs/rpcv2.h>
D 56
#include <nfs/nfsv2.h>
E 56
I 56
#include <nfs/nfsproto.h>
E 56
#include <nfs/nfs.h>
#include <nfs/nfsmount.h>
#include <nfs/nqnfs.h>
I 56
#include <nfs/nfsnode.h>
E 56
E 23
E 21
E 13

D 44
/* True and false, how exciting */
#define	TRUE	1
#define	FALSE	0
E 44
I 44
D 46
struct buf *nfsincore(), *nfs_getcacheblk(), *nfsgetblk();
E 46
I 46
D 56
struct buf *incore(), *nfs_getcacheblk();
E 56
I 56
struct buf *nfs_getcacheblk();
E 56
E 46
D 51
extern struct queue_entry nfs_bufq;
E 51
extern struct proc *nfs_iodwant[NFS_MAXASYNCDAEMON];
extern int nfs_numasync;
I 56
extern struct nfsstats nfsstats;
E 56
E 44

/*
 * Vnode op for read using bio
 * Any similarity to readip() is purely coincidental
 */
I 56
int
E 56
D 5
nfs_read(vp, uio, offp, ioflag, cred)
E 5
I 5
D 13
nfs_read(vp, uio, ioflag, cred)
E 13
I 13
nfs_bioread(vp, uio, ioflag, cred)
E 13
E 5
	register struct vnode *vp;
D 15
	struct uio *uio;
E 15
I 15
	register struct uio *uio;
E 15
D 5
	off_t *offp;
E 5
	int ioflag;
	struct ucred *cred;
{
I 32
D 37
	USES_VOP_GETATTR;
E 37
E 32
	register struct nfsnode *np = VTONFS(vp);
I 15
D 44
	register int biosize;
E 15
I 13
D 14
	struct nfsmount *nmp;
E 14
E 13
	struct buf *bp;
E 44
I 44
D 56
	register int biosize, diff;
	struct buf *bp, *rabp;
E 56
I 56
	register int biosize, diff, i;
	struct buf *bp = 0, *rabp;
E 56
E 44
	struct vattr vattr;
I 44
	struct proc *p;
E 44
D 21
	daddr_t lbn, bn, rablock;
D 4
	int error = 0;
	int diff;
E 4
I 4
	int diff, error = 0;
E 4
	long n, on;
E 21
I 21
D 56
	struct nfsmount *nmp;
D 44
	daddr_t lbn, bn, rablock[NFS_MAXRAHEAD];
	int rasize[NFS_MAXRAHEAD], nra, diff, error = 0;
	int n, on;
E 44
I 44
	daddr_t lbn, bn, rabn;
E 56
I 56
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	daddr_t lbn, bn, bn2, rabn;
E 56
	caddr_t baddr;
D 52
	int got_buf, len, nra, error = 0, n, on, not_readin;
E 52
I 52
D 56
	int got_buf, nra, error = 0, n, on, not_readin;
E 56
I 56
	int got_buf = 0, nra, error = 0, n = 0, on = 0, not_readin;
	nfsquad_t tquad;
E 56
E 52
E 44
E 21
D 4
	int count;
E 4

I 14
D 56
#ifdef lint
	ioflag = ioflag;
#endif /* lint */
E 56
I 19
#ifdef DIAGNOSTIC
E 19
E 14
D 5
	if (!(ioflag & IO_NODELOCKED))
		nfs_lock(vp);
E 5
D 2
	uio->uio_offset = *offp;
E 2
D 13
	/*
	 * Avoid caching directories. Once everything is using getdirentries()
	 * this will never happen anyhow.
	 */
D 5
	if (vp->v_type == VDIR) {
		error = nfs_readrpc(vp, uio, offp, cred);
D 2
		goto out;
E 2
I 2
		if (!(ioflag & IO_NODELOCKED))
			nfs_unlock(vp);
		return (error);
E 2
	}
I 2
	uio->uio_offset = *offp;
E 5
I 5
	if (vp->v_type == VDIR)
		return (nfs_readrpc(vp, uio, cred));
E 13
E 5
E 2
D 4
	count = uio->uio_resid;
E 4
	if (uio->uio_rw != UIO_READ)
		panic("nfs_read mode");
I 19
#endif
E 19
D 13
	if (vp->v_type != VREG)
		panic("nfs_read type");
E 13
	if (uio->uio_resid == 0)
D 5
		goto out;
	if (uio->uio_offset < 0) {
		error = EINVAL;
		goto out;
	}
E 5
I 5
		return (0);
D 13
	if (uio->uio_offset < 0)
E 13
I 13
D 56
	if (uio->uio_offset < 0 && vp->v_type != VDIR)
E 56
I 56
	if (uio->uio_offset < 0)
E 56
E 13
		return (EINVAL);
I 15
D 21
	biosize = VFSTONFS(vp->v_mount)->nm_rsize;
E 21
I 21
D 56
	nmp = VFSTONFS(vp->v_mount);
	biosize = nmp->nm_rsize;
E 56
I 44
	p = uio->uio_procp;
I 56
	if ((nmp->nm_flag & (NFSMNT_NFSV3 | NFSMNT_GOTFSINFO)) == NFSMNT_NFSV3)
		(void)nfs_fsinfo(nmp, vp, cred, p);
	biosize = nmp->nm_rsize;
E 56
E 44
E 21
E 15
E 5
	/*
I 21
	 * For nfs, cache consistency can only be maintained approximately.
	 * Although RFC1094 does not specify the criteria, the following is
	 * believed to be compatible with the reference port.
	 * For nqnfs, full cache consistency is maintained within the loop.
	 * For nfs:
E 21
	 * If the file's modify time on the server has changed since the
	 * last read rpc or you have written to the file,
	 * you may have lost data cache consistency with the
	 * server, so flush all of the file's data out of the cache.
D 13
	 * This will implicitly bring the modify time up to date, since
	 * up to date attributes are returned in the reply to any write rpc's
E 13
I 13
	 * Then force a getattr rpc to ensure that you have up to date
	 * attributes.
I 21
D 56
	 * The mount flag NFSMNT_MYWRITE says "Assume that my writes are
	 * the ones changing the modify time.
E 56
E 21
E 13
	 * NB: This implies that cache data can be read when up to
	 * NFS_ATTRTIMEO seconds out of date. If you find that you need current
	 * attributes this could be forced by setting n_attrstamp to 0 before
D 15
	 * the nfs_getattr() call.
E 15
I 15
D 21
	 * the nfs_dogetattr() call.
E 21
I 21
D 32
	 * the nfs_getattr() call.
E 32
I 32
	 * the VOP_GETATTR() call.
E 32
E 21
E 15
	 */
D 13
	if (np->n_flag & NMODIFIED) {
		np->n_flag &= ~NMODIFIED;
D 2
		if (error = nfs_blkflush(vp, (daddr_t)0, np->n_size, FALSE))
E 2
I 2
D 8
		if (error = nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE))
E 2
D 5
			goto out;
E 5
I 5
			return (error);
E 8
I 8
D 9
		if (vp->v_blockh && vinvalbuf(vp, TRUE)) {
E 9
I 9
		if (vinvalbuf(vp, TRUE)) {
E 13
I 13
D 21
	if (vp->v_type != VLNK) {
E 21
I 21
	if ((nmp->nm_flag & NFSMNT_NQNFS) == 0 && vp->v_type != VLNK) {
E 21
		if (np->n_flag & NMODIFIED) {
D 42
			np->n_flag &= ~NMODIFIED;
E 42
D 21
			vinvalbuf(vp, TRUE);
E 21
I 21
D 56
			if ((nmp->nm_flag & NFSMNT_MYWRITE) == 0 ||
D 44
			     vp->v_type != VREG)
D 36
				vinvalbuf(vp, TRUE);
E 36
I 36
D 42
				vinvalbuf(vp, TRUE, cred, uio->uio_procp);
E 42
I 42
				NFS_VINVBUF(np, vp, TRUE, cred, uio->uio_procp);
E 44
I 44
			     vp->v_type != VREG) {
				if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
			if (vp->v_type != VREG) {
				if (vp->v_type != VDIR)
					panic("nfs: bioread, not dir");
				nfs_invaldir(vp);
				error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
				if (error)
E 56
					return (error);
			}
E 44
E 42
E 36
E 21
			np->n_attrstamp = 0;
D 56
			np->n_direofoffset = 0;
E 13
E 9
D 15
			if (error = nfs_getattr(vp, &vattr, cred))
E 15
I 15
D 19
			if (error = nfs_dogetattr(vp, &vattr, cred, 1))
E 19
I 19
D 21
			if (error = nfs_dogetattr(vp, &vattr, cred, 1,
			    uio->uio_procp))
E 21
I 21
D 32
			if (error = nfs_getattr(vp, &vattr, cred, uio->uio_procp))
E 32
I 32
D 44
			if (error = VOP_GETATTR(vp, &vattr, cred, uio->uio_procp))
E 44
I 44
			if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 56
I 56
			error = VOP_GETATTR(vp, &vattr, cred, p);
			if (error)
E 56
E 44
E 32
E 21
E 19
E 15
				return (error);
D 35
			np->n_mtime = vattr.va_mtime.tv_sec;
E 35
I 35
			np->n_mtime = vattr.va_mtime.ts_sec;
E 35
I 13
		} else {
D 15
			if (error = nfs_getattr(vp, &vattr, cred))
E 15
I 15
D 19
			if (error = nfs_dogetattr(vp, &vattr, cred, 1))
E 19
I 19
D 21
			if (error = nfs_dogetattr(vp, &vattr, cred, 1,
			    uio->uio_procp))
E 21
I 21
D 32
			if (error = nfs_getattr(vp, &vattr, cred, uio->uio_procp))
E 32
I 32
D 44
			if (error = VOP_GETATTR(vp, &vattr, cred, uio->uio_procp))
E 44
I 44
D 56
			if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 56
I 56
			error = VOP_GETATTR(vp, &vattr, cred, p);
			if (error)
E 56
E 44
E 32
E 21
E 19
E 15
				return (error);
D 35
			if (np->n_mtime != vattr.va_mtime.tv_sec) {
E 35
I 35
			if (np->n_mtime != vattr.va_mtime.ts_sec) {
E 35
D 56
				np->n_direofoffset = 0;
D 36
				vinvalbuf(vp, TRUE);
E 36
I 36
D 42
				vinvalbuf(vp, TRUE, cred, uio->uio_procp);
E 42
I 42
D 44
				NFS_VINVBUF(np, vp, TRUE, cred, uio->uio_procp);
E 44
I 44
				if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
				if (vp->v_type == VDIR)
					nfs_invaldir(vp);
				error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
				if (error)
E 56
					return (error);
E 44
E 42
E 36
D 35
				np->n_mtime = vattr.va_mtime.tv_sec;
E 35
I 35
				np->n_mtime = vattr.va_mtime.ts_sec;
E 35
			}
E 13
		}
D 9
	} else if (vp->v_blockh) {
E 9
I 9
D 13
	} else if (vp->v_cleanblkhd || vp->v_dirtyblkhd) {
E 9
E 8
E 5
		if (error = nfs_getattr(vp, &vattr, cred))
D 5
			goto out;
E 5
I 5
			return (error);
E 5
D 3
		np->n_size = vattr.va_size;
E 3
D 8
		np->n_mtime = vattr.va_mtime.tv_sec;
	} else {
		if (error = nfs_getattr(vp, &vattr, cred))
D 5
			goto out;
E 5
I 5
			return (error);
E 8
E 5
		if (np->n_mtime != vattr.va_mtime.tv_sec) {
D 2
			if (error = nfs_blkflush(vp, (daddr_t)0, np->n_size, FALSE))
E 2
I 2
D 3
			if (error = nfs_blkflush(vp, (daddr_t)0, np->n_size, TRUE))
E 3
I 3
D 8
			if (error = nfs_blkflush(vp, (daddr_t)0,
				np->n_size, TRUE))
E 3
E 2
D 5
				goto out;
E 5
I 5
				return (error);
E 8
I 8
			vinvalbuf(vp, TRUE);
E 8
E 5
D 3
			np->n_size = vattr.va_size;
E 3
			np->n_mtime = vattr.va_mtime.tv_sec;
		}
E 13
	}
I 2
D 13
	np->n_flag |= NBUFFERED;
E 13
I 13
D 14
	nmp = VFSTONFS(vp->v_mount);
E 14
E 13
E 2
	do {
I 21

	    /*
	     * Get a valid lease. If cached data is stale, flush it.
	     */
D 44
	    if ((nmp->nm_flag & NFSMNT_NQNFS) &&
		NQNFS_CKINVALID(vp, np, NQL_READ)) {
		do {
			error = nqnfs_getlease(vp, NQL_READ, cred, uio->uio_procp);
		} while (error == NQNFS_EXPIRED);
		if (error)
E 44
I 44
	    if (nmp->nm_flag & NFSMNT_NQNFS) {
D 56
		if (NQNFS_CKINVALID(vp, np, NQL_READ)) {
E 56
I 56
		if (NQNFS_CKINVALID(vp, np, ND_READ)) {
E 56
		    do {
D 56
			error = nqnfs_getlease(vp, NQL_READ, cred, p);
E 56
I 56
			error = nqnfs_getlease(vp, ND_READ, cred, p);
E 56
		    } while (error == NQNFS_EXPIRED);
		    if (error)
E 44
			return (error);
D 36
		if (QUADNE(np->n_lrev, np->n_brev) ||
E 36
I 36
D 44
		if (np->n_lrev != np->n_brev ||
E 36
		    ((np->n_flag & NMODIFIED) && vp->v_type == VDIR)) {
E 44
I 44
		    if (np->n_lrev != np->n_brev ||
I 47
			(np->n_flag & NQNFSNONCACHE) ||
E 47
			((np->n_flag & NMODIFIED) && vp->v_type == VDIR)) {
E 44
D 56
			if (vp->v_type == VDIR) {
D 44
				np->n_direofoffset = 0;
				cache_purge(vp);
E 44
I 44
			    np->n_direofoffset = 0;
			    cache_purge(vp);
E 44
			}
D 42
			np->n_flag &= ~NMODIFIED;
D 36
			vinvalbuf(vp, TRUE);
E 36
I 36
			vinvalbuf(vp, TRUE, cred, uio->uio_procp);
E 42
I 42
D 44
			NFS_VINVBUF(np, vp, TRUE, cred, uio->uio_procp);
E 44
I 44
			if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
			if (vp->v_type == VDIR)
			    nfs_invaldir(vp);
			error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
			if (error)
E 56
			    return (error);
E 44
E 42
E 36
			np->n_brev = np->n_lrev;
I 44
		    }
		} else if (vp->v_type == VDIR && (np->n_flag & NMODIFIED)) {
D 56
		    np->n_direofoffset = 0;
		    cache_purge(vp);
		    if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
		    nfs_invaldir(vp);
		    error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
		    if (error)
E 56
			return (error);
E 44
		}
	    }
	    if (np->n_flag & NQNFSNONCACHE) {
		switch (vp->v_type) {
		case VREG:
D 56
			error = nfs_readrpc(vp, uio, cred);
			break;
E 56
I 56
			return (nfs_readrpc(vp, uio, cred));
E 56
		case VLNK:
D 56
			error = nfs_readlinkrpc(vp, uio, cred);
			break;
E 56
I 56
			return (nfs_readlinkrpc(vp, uio, cred));
E 56
		case VDIR:
D 56
			error = nfs_readdirrpc(vp, uio, cred);
E 56
			break;
I 56
		default:
			printf(" NQNFSNONCACHE: type %x unexpected\n",	
				vp->v_type);
E 56
		};
D 56
		return (error);
E 56
	    }
I 44
	    baddr = (caddr_t)0;
E 44
E 21
I 13
	    switch (vp->v_type) {
	    case VREG:
E 13
I 8
		nfsstats.biocache_reads++;
E 8
D 15
		lbn = uio->uio_offset >> NFS_BIOSHIFT;
		on = uio->uio_offset & (NFS_BIOSIZE-1);
		n = MIN((unsigned)(NFS_BIOSIZE - on), uio->uio_resid);
E 15
I 15
		lbn = uio->uio_offset / biosize;
D 56
		on = uio->uio_offset & (biosize-1);
E 56
I 56
		on = uio->uio_offset & (biosize - 1);
E 56
I 44
		bn = lbn * (biosize / DEV_BSIZE);
		not_readin = 1;

		/*
		 * Start the read ahead(s), as required.
		 */
D 56
		if (nfs_numasync > 0 && nmp->nm_readahead > 0 &&
		    lbn == vp->v_lastr + 1) {
E 56
I 56
		if (nfs_numasync > 0 && nmp->nm_readahead > 0) {
E 56
		    for (nra = 0; nra < nmp->nm_readahead &&
			(lbn + 1 + nra) * biosize < np->n_size; nra++) {
			rabn = (lbn + 1 + nra) * (biosize / DEV_BSIZE);
D 46
			if (!nfsincore(vp, rabn)) {
E 46
I 46
			if (!incore(vp, rabn)) {
E 46
			    rabp = nfs_getcacheblk(vp, rabn, biosize, p);
			    if (!rabp)
				return (EINTR);
			    if ((rabp->b_flags & (B_DELWRI | B_DONE)) == 0) {
				rabp->b_flags |= (B_READ | B_ASYNC);
				if (nfs_asyncio(rabp, cred)) {
				    rabp->b_flags |= B_INVAL;
				    brelse(rabp);
				}
D 55
			    }
E 55
I 55
			    } else
				brelse(rabp);
E 55
			}
		    }
		}

		/*
		 * If the block is in the cache and has the required data
		 * in a valid region, just copy it out.
		 * Otherwise, get the block and write back/read in,
		 * as required.
		 */
D 46
		if ((bp = nfsincore(vp, bn)) &&
E 46
I 46
		if ((bp = incore(vp, bn)) &&
E 46
		    (bp->b_flags & (B_BUSY | B_WRITEINPROG)) ==
		    (B_BUSY | B_WRITEINPROG))
			got_buf = 0;
		else {
again:
			bp = nfs_getcacheblk(vp, bn, biosize, p);
			if (!bp)
				return (EINTR);
			got_buf = 1;
			if ((bp->b_flags & (B_DONE | B_DELWRI)) == 0) {
				bp->b_flags |= B_READ;
				not_readin = 0;
D 56
				if (error = nfs_doio(bp, cred, p)) {
E 56
I 56
				error = nfs_doio(bp, cred, p);
				if (error) {
E 56
				    brelse(bp);
				    return (error);
				}
			}
		}
E 44
D 38
		n = MIN((unsigned)(biosize - on), uio->uio_resid);
E 38
I 38
		n = min((unsigned)(biosize - on), uio->uio_resid);
E 38
E 15
		diff = np->n_size - uio->uio_offset;
D 44
		if (diff <= 0)
D 5
			goto out;
E 5
I 5
			return (error);
E 44
E 5
		if (diff < n)
			n = diff;
D 15
		bn = lbn*(NFS_BIOSIZE/DEV_BSIZE);
		rablock = (lbn+1)*(NFS_BIOSIZE/DEV_BSIZE);
E 15
I 15
D 44
		bn = lbn*(biosize/DEV_BSIZE);
D 21
		rablock = (lbn+1)*(biosize/DEV_BSIZE);
E 15
D 3
		if (np->n_lastr+1 == lbn)
E 3
I 3
D 10
		if (np->n_lastr+1 == lbn && np->n_size > (rablock*DEV_BSIZE))
E 10
I 10
		if (vp->v_lastr + 1 == lbn &&
		    np->n_size > (rablock * DEV_BSIZE))
E 10
E 3
D 15
			error = breada(vp, bn, NFS_BIOSIZE, rablock, NFS_BIOSIZE,
E 15
I 15
			error = breada(vp, bn, biosize, rablock, biosize,
E 21
I 21
		for (nra = 0; nra < nmp->nm_readahead &&
			(lbn + 1 + nra) * biosize < np->n_size; nra++) {
			rablock[nra] = (lbn + 1 + nra) * (biosize / DEV_BSIZE);
			rasize[nra] = biosize;
		}
again:
		if (nra > 0 && lbn >= vp->v_lastr)
			error = breadn(vp, bn, biosize, rablock, rasize, nra,
E 21
E 15
				cred, &bp);
		else
D 15
			error = bread(vp, bn, NFS_BIOSIZE, cred, &bp);
E 15
I 15
			error = bread(vp, bn, biosize, cred, &bp);
I 21
		if (bp->b_validend > 0) {
			if (on < bp->b_validoff || (on+n) > bp->b_validend) {
E 44
I 44
		if (not_readin && n > 0) {
			if (on < bp->b_validoff || (on + n) > bp->b_validend) {
				if (!got_buf) {
				    bp = nfs_getcacheblk(vp, bn, biosize, p);
				    if (!bp)
					return (EINTR);
				    got_buf = 1;
				}
E 44
D 56
				bp->b_flags |= B_INVAL;
E 56
I 56
				bp->b_flags |= B_INVAFTERWRITE;
E 56
				if (bp->b_dirtyend > 0) {
D 44
					if ((bp->b_flags & B_DELWRI) == 0)
						panic("nfsbioread");
					(void) bwrite(bp);
E 44
I 44
				    if ((bp->b_flags & B_DELWRI) == 0)
					panic("nfsbioread");
				    if (VOP_BWRITE(bp) == EINTR)
					return (EINTR);
E 44
				} else
D 44
					brelse(bp);
E 44
I 44
				    brelse(bp);
E 44
				goto again;
			}
D 44
		} else {
			bp->b_validoff = 0;
			bp->b_validend = biosize - bp->b_resid;
E 44
		}
E 21
E 15
D 10
		np->n_lastr = lbn;
E 10
I 10
		vp->v_lastr = lbn;
E 10
D 44
		if (bp->b_resid) {
D 13
			diff = (on >= (NFS_BIOSIZE-bp->b_resid)) ? 0 :
				(NFS_BIOSIZE-bp->b_resid-on);
			n = MIN(n, diff);
E 13
I 13
D 15
		   diff = (on >= (NFS_BIOSIZE-bp->b_resid)) ? 0 :
			(NFS_BIOSIZE-bp->b_resid-on);
E 15
I 15
		   diff = (on >= (biosize-bp->b_resid)) ? 0 :
			(biosize-bp->b_resid-on);
E 15
D 38
		   n = MIN(n, diff);
E 38
I 38
		   n = min(n, diff);
E 38
E 13
		}
E 44
I 44
		diff = (on >= bp->b_validend) ? 0 : (bp->b_validend - on);
		if (diff < n)
			n = diff;
E 44
D 13
		if (error) {
			brelse(bp);
D 5
			goto out;
E 5
I 5
			return (error);
E 5
		}
		if (n > 0)
			error = uiomove(bp->b_un.b_addr + on, (int)n, uio);
E 13
I 13
		break;
	    case VLNK:
		nfsstats.biocache_readlinks++;
D 44
		on = 0;
		error = bread(vp, (daddr_t)0, NFS_MAXPATHLEN, cred, &bp);
E 44
I 44
		bp = nfs_getcacheblk(vp, (daddr_t)0, NFS_MAXPATHLEN, p);
		if (!bp)
			return (EINTR);
		if ((bp->b_flags & B_DONE) == 0) {
			bp->b_flags |= B_READ;
D 56
			if (error = nfs_doio(bp, cred, p)) {
E 56
I 56
			error = nfs_doio(bp, cred, p);
			if (error) {
E 56
				brelse(bp);
				return (error);
			}
		}
E 44
D 38
		n = MIN(uio->uio_resid, NFS_MAXPATHLEN - bp->b_resid);
E 38
I 38
		n = min(uio->uio_resid, NFS_MAXPATHLEN - bp->b_resid);
I 44
		got_buf = 1;
		on = 0;
E 44
E 38
		break;
	    case VDIR:
		nfsstats.biocache_readdirs++;
D 44
		on = 0;
D 19
		error = bread(vp, uio->uio_offset, DIRBLKSIZ, cred, &bp);
		n = MIN(uio->uio_resid, DIRBLKSIZ - bp->b_resid);
E 19
I 19
D 43
		error = bread(vp, uio->uio_offset, NFS_DIRBLKSIZ, cred, &bp);
E 43
I 43
		error = bread(vp, (daddr_t)uio->uio_offset, NFS_DIRBLKSIZ,
		    cred, &bp);
E 43
D 38
		n = MIN(uio->uio_resid, NFS_DIRBLKSIZ - bp->b_resid);
E 38
I 38
		n = min(uio->uio_resid, NFS_DIRBLKSIZ - bp->b_resid);
E 38
E 19
		break;
	    };
	    if (error) {
		brelse(bp);
		return (error);
	    }
I 21

	    /*
	     * For nqnfs:
	     * Must check for valid lease, since it may have expired while in
	     * bread(). If expired, get a lease.
	     * If data is stale, flush and try again.
	     * nb: If a read rpc is done by bread() or breada() and there is
	     *     no valid lease, a get_lease request will be piggy backed.
	     */
	    if (nmp->nm_flag & NFSMNT_NQNFS) {
		if (NQNFS_CKINVALID(vp, np, NQL_READ)) {
			do {
				error = nqnfs_getlease(vp, NQL_READ, cred, uio->uio_procp);
			} while (error == NQNFS_EXPIRED);
			if (error) {
E 44
I 44
D 56
		bn = (daddr_t)uio->uio_offset;
		bp = nfs_getcacheblk(vp, bn, NFS_DIRBLKSIZ, p);
E 56
I 56
		lbn = uio->uio_offset / NFS_DIRBLKSIZ;
		on = uio->uio_offset & (NFS_DIRBLKSIZ - 1);
		bp = nfs_getcacheblk(vp, lbn, NFS_DIRBLKSIZ, p);
E 56
		if (!bp)
D 56
			return (EINTR);
E 56
I 56
		    return (EINTR);
E 56
		if ((bp->b_flags & B_DONE) == 0) {
D 56
			bp->b_flags |= B_READ;
			if (error = nfs_doio(bp, cred, p)) {
E 44
				brelse(bp);
				return (error);
E 56
I 56
		    bp->b_flags |= B_READ;
		    error = nfs_doio(bp, cred, p);
		    if (error) {
			brelse(bp);
			while (error == NFSERR_BAD_COOKIE) {
			    nfs_invaldir(vp);
			    error = nfs_vinvalbuf(vp, 0, cred, p, 1);
			    /*
			     * Yuck! The directory has been modified on the
			     * server. The only way to get the block is by
			     * reading from the beginning to get all the
			     * offset cookies.
			     */
			    for (i = 0; i <= lbn && !error; i++) {
				bp = nfs_getcacheblk(vp, i, NFS_DIRBLKSIZ, p);
				if (!bp)
				    return (EINTR);
				if ((bp->b_flags & B_DONE) == 0) {
				    bp->b_flags |= B_READ;
				    error = nfs_doio(bp, cred, p);
				    if (error)
					brelse(bp);
				}
			    }
E 56
			}
I 56
			if (error)
			    return (error);
		    }
E 56
D 44
			if ((np->n_flag & NQNFSNONCACHE) ||
D 36
			    QUADNE(np->n_lrev, np->n_brev) ||
E 36
I 36
			    np->n_lrev != np->n_brev ||
E 36
			    ((np->n_flag & NMODIFIED) && vp->v_type == VDIR)) {
				if (vp->v_type == VDIR) {
					np->n_direofoffset = 0;
					cache_purge(vp);
E 44
I 44
		}

		/*
		 * If not eof and read aheads are enabled, start one.
		 * (You need the current block first, so that you have the
D 56
		 *  directory offset cookie of the next block.
E 56
I 56
		 *  directory offset cookie of the next block.)
E 56
		 */
D 56
		rabn = bp->b_blkno;
E 56
		if (nfs_numasync > 0 && nmp->nm_readahead > 0 &&
D 56
		    rabn != 0 && rabn != np->n_direofoffset &&
D 46
		    !nfsincore(vp, rabn)) {
E 46
I 46
		    !incore(vp, rabn)) {
E 46
			rabp = nfs_getcacheblk(vp, rabn, NFS_DIRBLKSIZ, p);
E 56
I 56
		    (np->n_direofoffset == 0 ||
		    (lbn + 1) * NFS_DIRBLKSIZ < np->n_direofoffset) &&
		    !(np->n_flag & NQNFSNONCACHE) &&
		    !incore(vp, lbn + 1)) {
			rabp = nfs_getcacheblk(vp, lbn + 1, NFS_DIRBLKSIZ, p);
E 56
			if (rabp) {
			    if ((rabp->b_flags & (B_DONE | B_DELWRI)) == 0) {
				rabp->b_flags |= (B_READ | B_ASYNC);
				if (nfs_asyncio(rabp, cred)) {
				    rabp->b_flags |= B_INVAL;
				    brelse(rabp);
E 44
				}
D 44
				brelse(bp);
D 42
				np->n_flag &= ~NMODIFIED;
D 36
				vinvalbuf(vp, TRUE);
E 36
I 36
				vinvalbuf(vp, TRUE, cred, uio->uio_procp);
E 42
I 42
				NFS_VINVBUF(np, vp, TRUE, cred, uio->uio_procp);
E 42
E 36
				np->n_brev = np->n_lrev;
				continue;
E 44
I 44
D 55
			    }
E 55
I 55
			    } else
				brelse(rabp);
E 55
E 44
			}
D 44
		} else if ((np->n_flag & NQNFSNONCACHE) ||
		    ((np->n_flag & NMODIFIED) && vp->v_type == VDIR)) {
			np->n_direofoffset = 0;
			brelse(bp);
D 42
			np->n_flag &= ~NMODIFIED;
D 36
			vinvalbuf(vp, TRUE);
E 36
I 36
			vinvalbuf(vp, TRUE, cred, uio->uio_procp);
E 42
I 42
			NFS_VINVBUF(np, vp, TRUE, cred, uio->uio_procp);
E 42
E 36
			np->n_brev = np->n_lrev;
			continue;
E 44
		}
I 44
D 56
		on = 0;
		n = min(uio->uio_resid, NFS_DIRBLKSIZ - bp->b_resid);
E 56
I 56
		n = min(uio->uio_resid, NFS_DIRBLKSIZ - bp->b_resid - on);
E 56
		got_buf = 1;
		break;
I 56
	    default:
		printf(" nfsbioread: type %x unexpected\n",vp->v_type);
		break;
E 56
	    };

	    if (n > 0) {
		if (!baddr)
D 49
			baddr = bp->b_un.b_addr;
E 49
I 49
			baddr = bp->b_data;
E 49
		error = uiomove(baddr + on, (int)n, uio);
E 44
	    }
E 21
D 44
	    if (n > 0)
		error = uiomove(bp->b_un.b_addr + on, (int)n, uio);
E 44
	    switch (vp->v_type) {
	    case VREG:
E 13
D 15
		if (n+on == NFS_BIOSIZE || uio->uio_offset == np->n_size)
E 15
I 15
D 44
		if (n+on == biosize || uio->uio_offset == np->n_size)
E 44
I 44
D 56
		if (n + on == biosize || uio->uio_offset == np->n_size)
E 44
E 15
			bp->b_flags |= B_AGE;
E 56
D 13
		brelse(bp);
E 13
I 13
		break;
	    case VLNK:
		n = 0;
		break;
	    case VDIR:
D 56
		uio->uio_offset = bp->b_blkno;
E 56
I 56
		if (np->n_flag & NQNFSNONCACHE)
			bp->b_flags |= B_INVAL;
E 56
		break;
D 56
	    };
E 56
I 56
	    default:
		printf(" nfsbioread: type %x unexpected\n",vp->v_type);
	    }
E 56
D 44
	    brelse(bp);
E 13
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 44
I 44
	    if (got_buf)
		brelse(bp);
	} while (error == 0 && uio->uio_resid > 0 && n > 0);
E 44
D 5
out:
	*offp = uio->uio_offset;
D 2
	if ((ioflag & IO_NODELOCKED) == 0)
E 2
I 2
	if (!(ioflag & IO_NODELOCKED))
E 2
		nfs_unlock(vp);
E 5
	return (error);
}

/*
 * Vnode op for write using bio
 */
I 56
int
E 56
D 5
nfs_write(vp, uio, offp, ioflag, cred)
E 5
I 5
D 32
nfs_write(vp, uio, ioflag, cred)
E 5
	register struct vnode *vp;
	register struct uio *uio;
D 5
	off_t *offp;
E 5
	int ioflag;
	struct ucred *cred;
E 32
I 32
D 37
nfs_write (ap)
E 37
I 37
nfs_write(ap)
E 37
D 36
	struct vop_write_args *ap;
E 36
I 36
	struct vop_write_args /* {
		struct vnode *a_vp;
		struct uio *a_uio;
		int  a_ioflag;
		struct ucred *a_cred;
	} */ *ap;
E 36
D 33
#define vp (ap->a_vp)
#define uio (ap->a_uio)
#define ioflag (ap->a_ioflag)
#define cred (ap->a_cred)
E 33
E 32
{
I 32
D 37
	USES_VOP_GETATTR;
E 37
E 32
I 18
D 19
	struct proc *p = curproc;		/* XXX */
E 19
I 19
D 21
	struct proc *p = uio->uio_procp;
E 21
E 19
E 18
I 15
	register int biosize;
I 21
D 33
	struct proc *p = uio->uio_procp;
E 33
I 33
D 36
	struct proc *p = ap->a_uio->uio_procp;
E 36
I 36
	register struct uio *uio = ap->a_uio;
	struct proc *p = uio->uio_procp;
	register struct vnode *vp = ap->a_vp;
	struct nfsnode *np = VTONFS(vp);
	register struct ucred *cred = ap->a_cred;
	int ioflag = ap->a_ioflag;
E 36
E 33
E 21
E 15
	struct buf *bp;
D 33
	struct nfsnode *np = VTONFS(vp);
E 33
I 33
D 36
	struct nfsnode *np = VTONFS(ap->a_vp);
E 36
E 33
I 13
	struct vattr vattr;
I 21
D 56
	struct nfsmount *nmp;
E 56
I 56
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
E 56
E 21
E 13
	daddr_t lbn, bn;
D 4
	int i, n, on;
	int flags, count, size;
	int error = 0;
	int cnt;
	u_long osize;
E 4
I 4
D 5
	int i, n, on, cnt, count, error = 0;
E 5
I 5
D 12
	int i, n, on, count, error = 0;
E 12
I 12
D 56
	int n, on, error = 0;
E 56
I 56
	int n, on, error = 0, iomode, must_commit;
E 56
E 12
E 5
E 4

I 19
#ifdef DIAGNOSTIC
E 19
I 13
D 33
	if (uio->uio_rw != UIO_WRITE)
E 33
I 33
D 36
	if (ap->a_uio->uio_rw != UIO_WRITE)
E 36
I 36
	if (uio->uio_rw != UIO_WRITE)
E 36
E 33
		panic("nfs_write mode");
I 19
D 33
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
E 33
I 33
D 36
	if (ap->a_uio->uio_segflg == UIO_USERSPACE && ap->a_uio->uio_procp != curproc)
E 36
I 36
	if (uio->uio_segflg == UIO_USERSPACE && uio->uio_procp != curproc)
E 36
E 33
		panic("nfs_write proc");
#endif
E 19
D 33
	if (vp->v_type != VREG)
E 33
I 33
D 36
	if (ap->a_vp->v_type != VREG)
E 36
I 36
	if (vp->v_type != VREG)
E 36
E 33
		return (EIO);
I 34
	if (np->n_flag & NWRITEERR) {
		np->n_flag &= ~NWRITEERR;
		return (np->n_error);
	}
I 56
	if ((nmp->nm_flag & (NFSMNT_NFSV3 | NFSMNT_GOTFSINFO)) == NFSMNT_NFSV3)
		(void)nfs_fsinfo(nmp, vp, cred, p);
E 56
E 34
I 22
D 33
	if (ioflag & (IO_APPEND | IO_SYNC)) {
E 33
I 33
D 36
	if (ap->a_ioflag & (IO_APPEND | IO_SYNC)) {
E 36
I 36
	if (ioflag & (IO_APPEND | IO_SYNC)) {
E 36
E 33
		if (np->n_flag & NMODIFIED) {
D 42
			np->n_flag &= ~NMODIFIED;
E 42
I 40
			np->n_attrstamp = 0;
E 40
D 33
			vinvalbuf(vp, TRUE);
E 33
I 33
D 36
			vinvalbuf(ap->a_vp, TRUE);
E 36
I 36
D 42
			vinvalbuf(vp, TRUE, cred, p);
E 42
I 42
D 44
			NFS_VINVBUF(np, vp, TRUE, cred, p);
E 44
I 44
D 56
			if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
			error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
			if (error)
E 56
				return (error);
E 44
E 42
E 36
E 33
		}
D 33
		if (ioflag & IO_APPEND) {
E 33
I 33
D 36
		if (ap->a_ioflag & IO_APPEND) {
E 36
I 36
		if (ioflag & IO_APPEND) {
E 36
E 33
			np->n_attrstamp = 0;
D 32
			if (error = nfs_getattr(vp, &vattr, cred, p))
E 32
I 32
D 33
			if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 33
I 33
D 36
			if (error = VOP_GETATTR(ap->a_vp, &vattr, ap->a_cred, p))
E 36
I 36
D 56
			if (error = VOP_GETATTR(vp, &vattr, cred, p))
E 56
I 56
			error = VOP_GETATTR(vp, &vattr, cred, p);
			if (error)
E 56
E 36
E 33
E 32
				return (error);
D 33
			uio->uio_offset = np->n_size;
E 33
I 33
D 36
			ap->a_uio->uio_offset = np->n_size;
E 36
I 36
			uio->uio_offset = np->n_size;
E 36
E 33
		}
	}
E 22
E 13
D 5
	if ((ioflag & IO_NODELOCKED) == 0)
		nfs_lock(vp);
E 5
D 21
	/* Should we try and do this ?? */
D 13
	if (vp->v_type == VREG && (ioflag & IO_APPEND))
E 13
I 13
D 15
	if (ioflag & IO_APPEND) {
E 15
I 15
	if (ioflag & (IO_APPEND | IO_SYNC)) {
E 15
		if (np->n_flag & NMODIFIED) {
			np->n_flag &= ~NMODIFIED;
			vinvalbuf(vp, TRUE);
		}
D 15
		np->n_attrstamp = 0;
		if (error = nfs_getattr(vp, &vattr, cred))
			return (error);
E 13
D 5
		*offp = np->n_size;
	uio->uio_offset = *offp;
	cnt = uio->uio_resid;
E 5
I 5
		uio->uio_offset = np->n_size;
E 15
I 15
		if (ioflag & IO_APPEND) {
			np->n_attrstamp = 0;
D 19
			if (error = nfs_dogetattr(vp, &vattr, cred, 1))
E 19
I 19
			if (error = nfs_dogetattr(vp, &vattr, cred, 1, p))
E 19
				return (error);
			uio->uio_offset = np->n_size;
		}
E 15
I 13
D 18
		return (nfs_writerpc(vp, uio, cred, u.u_procp));
E 18
I 18
D 19
		return (nfs_writerpc(vp, uio, cred, p));
E 19
I 19
		return (nfs_writerpc(vp, uio, cred));
E 19
E 18
	}
E 13
E 5
#ifdef notdef
I 5
	cnt = uio->uio_resid;
E 5
	osize = np->n_size;
#endif
E 21
I 21
D 33
	nmp = VFSTONFS(vp->v_mount);
E 21
D 13
	if (uio->uio_rw != UIO_WRITE)
		panic("nfs_write mode");
	if (vp->v_type != VREG)
		panic("nfs_write type");
E 13
D 5
	if (uio->uio_offset < 0) {
		error = EINVAL;
		goto out;
	}
E 5
I 5
	if (uio->uio_offset < 0)
E 33
I 33
D 36
	nmp = VFSTONFS(ap->a_vp->v_mount);
	if (ap->a_uio->uio_offset < 0)
E 36
I 36
D 56
	nmp = VFSTONFS(vp->v_mount);
E 56
	if (uio->uio_offset < 0)
E 36
E 33
		return (EINVAL);
E 5
D 33
	if (uio->uio_resid == 0)
E 33
I 33
D 36
	if (ap->a_uio->uio_resid == 0)
E 36
I 36
	if (uio->uio_resid == 0)
E 36
E 33
D 5
		goto out;
E 5
I 5
		return (0);
E 5
	/*
	 * Maybe this should be above the vnode op call, but so long as
	 * file servers have no limits, i don't think it matters
	 */
D 13
	if (vp->v_type == VREG &&
	    uio->uio_offset + uio->uio_resid >
E 13
I 13
D 21
	if (uio->uio_offset + uio->uio_resid >
E 21
I 21
D 33
	if (p && uio->uio_offset + uio->uio_resid >
E 33
I 33
D 36
	if (p && ap->a_uio->uio_offset + ap->a_uio->uio_resid >
E 36
I 36
	if (p && uio->uio_offset + uio->uio_resid >
E 36
E 33
E 21
E 13
D 18
	      u.u_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(u.u_procp, SIGXFSZ);
E 18
I 18
	      p->p_rlimit[RLIMIT_FSIZE].rlim_cur) {
		psignal(p, SIGXFSZ);
E 18
D 5
		error = EFBIG;
		goto out;
E 5
I 5
		return (EFBIG);
E 5
	}
I 15
	/*
	 * I use nm_rsize, not nm_wsize so that all buffer cache blocks
	 * will be the same size within a filesystem. nfs_writerpc will
	 * still use nm_wsize when sizing the rpc's.
	 */
D 21
	biosize = VFSTONFS(vp->v_mount)->nm_rsize;
E 21
I 21
	biosize = nmp->nm_rsize;
E 21
E 15
D 2
	np->n_flag |= NMODIFIED;
E 2
I 2
D 13
	np->n_flag |= (NMODIFIED|NBUFFERED);
E 13
I 13
D 44
	np->n_flag |= NMODIFIED;
E 44
E 13
E 2
	do {
I 21

		/*
I 53
		 * XXX make sure we aren't cached in the VM page cache
		 */
		(void)vnode_pager_uncache(vp);

		/*
E 53
		 * Check for a valid write lease.
D 56
		 * If non-cachable, just do the rpc
E 56
		 */
		if ((nmp->nm_flag & NFSMNT_NQNFS) &&
D 33
		    NQNFS_CKINVALID(vp, np, NQL_WRITE)) {
E 33
I 33
D 36
		    NQNFS_CKINVALID(ap->a_vp, np, NQL_WRITE)) {
E 36
I 36
D 56
		    NQNFS_CKINVALID(vp, np, NQL_WRITE)) {
E 56
I 56
		    NQNFS_CKINVALID(vp, np, ND_WRITE)) {
E 56
E 36
E 33
			do {
D 33
				error = nqnfs_getlease(vp, NQL_WRITE, cred, p);
E 33
I 33
D 36
				error = nqnfs_getlease(ap->a_vp, NQL_WRITE, ap->a_cred, p);
E 36
I 36
D 56
				error = nqnfs_getlease(vp, NQL_WRITE, cred, p);
E 56
I 56
				error = nqnfs_getlease(vp, ND_WRITE, cred, p);
E 56
E 36
E 33
			} while (error == NQNFS_EXPIRED);
			if (error)
				return (error);
D 36
			if (QUADNE(np->n_lrev, np->n_brev) ||
E 36
I 36
			if (np->n_lrev != np->n_brev ||
E 36
			    (np->n_flag & NQNFSNONCACHE)) {
D 33
				vinvalbuf(vp, TRUE);
E 33
I 33
D 36
				vinvalbuf(ap->a_vp, TRUE);
E 36
I 36
D 42
				vinvalbuf(vp, TRUE, cred, p);
E 42
I 42
D 44
				NFS_VINVBUF(np, vp, TRUE, cred, p);
E 44
I 44
D 56
				if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
				error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
				if (error)
E 56
					return (error);
E 44
E 42
E 36
E 33
				np->n_brev = np->n_lrev;
			}
		}
D 56
		if (np->n_flag & NQNFSNONCACHE)
D 33
			return (nfs_writerpc(vp, uio, cred));
E 33
I 33
D 36
			return (nfs_writerpc(ap->a_vp, ap->a_uio, ap->a_cred));
E 36
I 36
D 40
			return (nfs_writerpc(vp, uio, cred));
E 40
I 40
D 44
			return (nfs_writerpc(vp, uio, cred, 0));
E 44
I 44
			return (nfs_writerpc(vp, uio, cred, ioflag));
E 56
I 56
		if ((np->n_flag & NQNFSNONCACHE) && uio->uio_iovcnt == 1) {
		    iomode = NFSV3WRITE_FILESYNC;
		    error = nfs_writerpc(vp, uio, cred, &iomode, &must_commit);
		    if (must_commit)
			nfs_clearcommit(vp->v_mount);
		    return (error);
		}
E 56
E 44
E 40
E 36
E 33
E 21
I 8
		nfsstats.biocache_writes++;
E 8
D 15
		lbn = uio->uio_offset >> NFS_BIOSHIFT;
		on = uio->uio_offset & (NFS_BIOSIZE-1);
		n = MIN((unsigned)(NFS_BIOSIZE - on), uio->uio_resid);
E 15
I 15
D 33
		lbn = uio->uio_offset / biosize;
		on = uio->uio_offset & (biosize-1);
		n = MIN((unsigned)(biosize - on), uio->uio_resid);
E 15
D 17
		if (uio->uio_offset+n > np->n_size)
E 17
I 17
D 21
		if (uio->uio_offset+n > np->n_size) {
E 17
			np->n_size = uio->uio_offset+n;
E 21
I 21
		if (uio->uio_offset + n > np->n_size) {
			np->n_size = uio->uio_offset + n;
E 21
I 17
D 23
			vnode_pager_setsize(vp, np->n_size);
E 23
I 23
			vnode_pager_setsize(vp, (u_long)np->n_size);
E 33
I 33
D 36
		lbn = ap->a_uio->uio_offset / biosize;
		on = ap->a_uio->uio_offset & (biosize-1);
		n = MIN((unsigned)(biosize - on), ap->a_uio->uio_resid);
		if (ap->a_uio->uio_offset + n > np->n_size) {
			np->n_size = ap->a_uio->uio_offset + n;
			vnode_pager_setsize(ap->a_vp, (u_long)np->n_size);
E 36
I 36
		lbn = uio->uio_offset / biosize;
		on = uio->uio_offset & (biosize-1);
D 38
		n = MIN((unsigned)(biosize - on), uio->uio_resid);
E 38
I 38
		n = min((unsigned)(biosize - on), uio->uio_resid);
E 38
D 44
		if (uio->uio_offset + n > np->n_size) {
			np->n_size = uio->uio_offset + n;
			vnode_pager_setsize(vp, (u_long)np->n_size);
E 36
E 33
E 23
		}
E 44
E 17
D 15
		bn = lbn*(NFS_BIOSIZE/DEV_BSIZE);
E 15
I 15
D 21
		bn = lbn*(biosize/DEV_BSIZE);
E 21
I 21
		bn = lbn * (biosize / DEV_BSIZE);
E 21
E 15
D 12
		count = howmany(NFS_BIOSIZE, CLBYTES);
		for (i = 0; i < count; i++)
			munhash(vp, bn + i * CLBYTES / DEV_BSIZE);
E 12
I 11
again:
E 11
D 15
		bp = getblk(vp, bn, NFS_BIOSIZE);
E 15
I 15
D 33
		bp = getblk(vp, bn, biosize);
E 33
I 33
D 36
		bp = getblk(ap->a_vp, bn, biosize);
E 36
I 36
D 44
		bp = getblk(vp, bn, biosize);
E 44
I 44
		bp = nfs_getcacheblk(vp, bn, biosize, p);
		if (!bp)
			return (EINTR);
E 44
E 36
E 33
E 15
		if (bp->b_wcred == NOCRED) {
D 33
			crhold(cred);
			bp->b_wcred = cred;
E 33
I 33
D 36
			crhold(ap->a_cred);
			bp->b_wcred = ap->a_cred;
E 36
I 36
			crhold(cred);
			bp->b_wcred = cred;
E 36
E 33
		}
I 44
		np->n_flag |= NMODIFIED;
		if (uio->uio_offset + n > np->n_size) {
			np->n_size = uio->uio_offset + n;
			vnode_pager_setsize(vp, (u_long)np->n_size);
		}
E 44
D 21
		if (bp->b_dirtyend > 0) {
			/*
D 5
			 * Iff the new write will leave a contiguous
E 5
I 5
D 11
			 * If the new write will leave a contiguous
E 5
			 * dirty area, just update the b_dirtyoff and
			 * b_dirtyend
			 * otherwise force a write rpc of the old dirty
			 * area
E 11
I 11
			 * If the new write will leave a contiguous dirty
			 * area, just update the b_dirtyoff and b_dirtyend,
			 * otherwise force a write rpc of the old dirty area.
E 11
			 */
			if (on <= bp->b_dirtyend && (on+n) >= bp->b_dirtyoff) {
				bp->b_dirtyoff = MIN(on, bp->b_dirtyoff);
				bp->b_dirtyend = MAX((on+n), bp->b_dirtyend);
			} else {
I 13
D 18
				bp->b_proc = u.u_procp;
E 18
I 18
				bp->b_proc = p;
E 18
E 13
D 11
				/*
				 * Like bwrite() but without the brelse
				 */
				bp->b_flags &= ~(B_READ | B_DONE |
				    B_ERROR | B_DELWRI | B_ASYNC);
				u.u_ru.ru_oublock++;
I 9
				bp->b_vp->v_numoutput++;
E 9
				VOP_STRATEGY(bp);
				error = biowait(bp);
				if (bp->b_flags & B_ERROR) {
					brelse(bp);
					if (bp->b_error)
						error = bp->b_error;
					else
						error = EIO;
E 11
I 11
				if (error = bwrite(bp))
E 11
D 5
					goto out;
E 5
I 5
					return (error);
E 5
D 11
				}
				bp->b_dirtyoff = on;
				bp->b_dirtyend = on+n;
E 11
I 11
				goto again;
E 21
I 21

		/*
		 * If the new write will leave a contiguous dirty
		 * area, just update the b_dirtyoff and b_dirtyend,
		 * otherwise force a write rpc of the old dirty area.
		 */
		if (bp->b_dirtyend > 0 &&
		    (on > bp->b_dirtyend || (on + n) < bp->b_dirtyoff)) {
			bp->b_proc = p;
D 44
			if (error = bwrite(bp))
				return (error);
E 44
I 44
			if (VOP_BWRITE(bp) == EINTR)
				return (EINTR);
E 44
			goto again;
		}

		/*
		 * Check for valid write lease and get one as required.
		 * In case getblk() and/or bwrite() delayed us.
		 */
		if ((nmp->nm_flag & NFSMNT_NQNFS) &&
D 33
		    NQNFS_CKINVALID(vp, np, NQL_WRITE)) {
E 33
I 33
D 36
		    NQNFS_CKINVALID(ap->a_vp, np, NQL_WRITE)) {
E 36
I 36
D 56
		    NQNFS_CKINVALID(vp, np, NQL_WRITE)) {
E 56
I 56
		    NQNFS_CKINVALID(vp, np, ND_WRITE)) {
E 56
E 36
E 33
			do {
D 33
				error = nqnfs_getlease(vp, NQL_WRITE, cred, p);
E 33
I 33
D 36
				error = nqnfs_getlease(ap->a_vp, NQL_WRITE, ap->a_cred, p);
E 36
I 36
D 56
				error = nqnfs_getlease(vp, NQL_WRITE, cred, p);
E 56
I 56
				error = nqnfs_getlease(vp, ND_WRITE, cred, p);
E 56
E 36
E 33
			} while (error == NQNFS_EXPIRED);
			if (error) {
				brelse(bp);
				return (error);
E 21
E 11
			}
D 21
		} else {
			bp->b_dirtyoff = on;
			bp->b_dirtyend = on+n;
E 21
I 21
D 36
			if (QUADNE(np->n_lrev, np->n_brev) ||
E 36
I 36
			if (np->n_lrev != np->n_brev ||
E 36
			    (np->n_flag & NQNFSNONCACHE)) {
I 40
				brelse(bp);
E 40
D 33
				vinvalbuf(vp, TRUE);
E 33
I 33
D 36
				vinvalbuf(ap->a_vp, TRUE);
E 36
I 36
D 42
				vinvalbuf(vp, TRUE, cred, p);
E 42
I 42
D 44
				NFS_VINVBUF(np, vp, TRUE, cred, p);
E 44
I 44
D 56
				if (error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1))
E 56
I 56
				error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
				if (error)
E 56
					return (error);
E 44
E 42
E 36
E 33
				np->n_brev = np->n_lrev;
I 40
				goto again;
E 40
			}
E 21
		}
D 11
		if (error = uiomove(bp->b_un.b_addr + on, n, uio))
E 11
I 11
D 33
		if (error = uiomove(bp->b_un.b_addr + on, n, uio)) {
E 33
I 33
D 36
		if (error = uiomove(bp->b_un.b_addr + on, n, ap->a_uio)) {
E 36
I 36
D 49
		if (error = uiomove(bp->b_un.b_addr + on, n, uio)) {
E 49
I 49
D 56
		if (error = uiomove((char *)bp->b_data + on, n, uio)) {
E 56
I 56
		error = uiomove((char *)bp->b_data + on, n, uio);
		if (error) {
E 56
E 49
I 44
			bp->b_flags |= B_ERROR;
E 44
E 36
E 33
			brelse(bp);
E 11
D 5
			goto out;
E 5
I 5
			return (error);
I 11
		}
E 11
E 5
D 15
		if ((n+on) == NFS_BIOSIZE) {
E 15
I 15
D 21
		if ((n+on) == biosize) {
E 21
I 21
		if (bp->b_dirtyend > 0) {
D 38
			bp->b_dirtyoff = MIN(on, bp->b_dirtyoff);
			bp->b_dirtyend = MAX((on+n), bp->b_dirtyend);
E 38
I 38
			bp->b_dirtyoff = min(on, bp->b_dirtyoff);
D 44
			bp->b_dirtyend = max((on+n), bp->b_dirtyend);
E 44
I 44
			bp->b_dirtyend = max((on + n), bp->b_dirtyend);
E 44
E 38
		} else {
			bp->b_dirtyoff = on;
D 44
			bp->b_dirtyend = on+n;
E 44
I 44
			bp->b_dirtyend = on + n;
E 44
		}
I 44
D 56
#ifndef notdef
E 56
E 44
		if (bp->b_validend == 0 || bp->b_validend < bp->b_dirtyoff ||
		    bp->b_validoff > bp->b_dirtyend) {
			bp->b_validoff = bp->b_dirtyoff;
			bp->b_validend = bp->b_dirtyend;
		} else {
D 38
			bp->b_validoff = MIN(bp->b_validoff, bp->b_dirtyoff);
			bp->b_validend = MAX(bp->b_validend, bp->b_dirtyend);
E 38
I 38
			bp->b_validoff = min(bp->b_validoff, bp->b_dirtyoff);
			bp->b_validend = max(bp->b_validend, bp->b_dirtyend);
E 38
		}
I 44
D 56
#else
		bp->b_validoff = bp->b_dirtyoff;
		bp->b_validend = bp->b_dirtyend;
#endif
		if (ioflag & IO_APPEND)
			bp->b_flags |= B_APPENDWRITE;
E 44

E 56
		/*
		 * If the lease is non-cachable or IO_SYNC do bwrite().
		 */
D 33
		if ((np->n_flag & NQNFSNONCACHE) || (ioflag & IO_SYNC)) {
E 33
I 33
D 36
		if ((np->n_flag & NQNFSNONCACHE) || (ap->a_ioflag & IO_SYNC)) {
E 36
I 36
		if ((np->n_flag & NQNFSNONCACHE) || (ioflag & IO_SYNC)) {
E 36
E 33
			bp->b_proc = p;
D 44
			bwrite(bp);
		} else if ((n+on) == biosize &&
			 (nmp->nm_flag & NFSMNT_NQNFS) == 0) {
E 21
E 15
			bp->b_flags |= B_AGE;
E 44
I 44
D 56
			if (error = VOP_BWRITE(bp))
E 56
I 56
			error = VOP_BWRITE(bp);
			if (error)
E 56
				return (error);
I 56
			if (np->n_flag & NQNFSNONCACHE) {
				error = nfs_vinvalbuf(vp, V_SAVE, cred, p, 1);
				if (error)
					return (error);
			}
E 56
		} else if ((n + on) == biosize &&
			(nmp->nm_flag & NFSMNT_NQNFS) == 0) {
E 44
I 13
			bp->b_proc = (struct proc *)0;
E 13
D 56
			bawrite(bp);
E 56
I 56
			bp->b_flags |= B_ASYNC;
			(void)nfs_writebp(bp, 0);
E 56
D 44
		} else {
I 13
			bp->b_proc = (struct proc *)0;
E 44
I 44
		} else
E 44
E 13
			bdwrite(bp);
I 44
	} while (uio->uio_resid > 0 && n > 0);
	return (0);
}

/*
 * Get an nfs cache block.
 * Allocate a new one if the block isn't currently in the cache
 * and return the block marked busy. If the calling process is
 * interrupted by a signal for an interruptible mount point, return
 * NULL.
 */
struct buf *
nfs_getcacheblk(vp, bn, size, p)
	struct vnode *vp;
	daddr_t bn;
	int size;
	struct proc *p;
{
	register struct buf *bp;
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);

	if (nmp->nm_flag & NFSMNT_INT) {
D 46
		bp = nfsgetblk(vp, bn, size, PCATCH, 0);
E 46
I 46
		bp = getblk(vp, bn, size, PCATCH, 0);
E 46
		while (bp == (struct buf *)0) {
			if (nfs_sigintr(nmp, (struct nfsreq *)0, p))
				return ((struct buf *)0);
D 46
			bp = nfsgetblk(vp, bn, size, 0, 2 * hz);
E 46
I 46
			bp = getblk(vp, bn, size, 0, 2 * hz);
E 46
E 44
		}
D 33
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 33
I 33
D 36
	} while (error == 0 && ap->a_uio->uio_resid > 0 && n != 0);
E 36
I 36
D 44
	} while (error == 0 && uio->uio_resid > 0 && n != 0);
E 44
I 44
	} else
D 46
		bp = nfsgetblk(vp, bn, size, 0, 0);
E 46
I 46
		bp = getblk(vp, bn, size, 0, 0);
E 46
	return (bp);
}

/*
 * Flush and invalidate all dirty buffers. If another process is already
 * doing the flush, just wait for completion.
 */
I 56
int
E 56
nfs_vinvalbuf(vp, flags, cred, p, intrflg)
	struct vnode *vp;
	int flags;
	struct ucred *cred;
	struct proc *p;
	int intrflg;
{
	register struct nfsnode *np = VTONFS(vp);
	struct nfsmount *nmp = VFSTONFS(vp->v_mount);
	int error = 0, slpflag, slptimeo;

	if ((nmp->nm_flag & NFSMNT_INT) == 0)
		intrflg = 0;
	if (intrflg) {
		slpflag = PCATCH;
		slptimeo = 2 * hz;
	} else {
		slpflag = 0;
		slptimeo = 0;
	}
	/*
	 * First wait for any other process doing a flush to complete.
	 */
	while (np->n_flag & NFLUSHINPROG) {
		np->n_flag |= NFLUSHWANT;
		error = tsleep((caddr_t)&np->n_flag, PRIBIO + 2, "nfsvinval",
			slptimeo);
		if (error && intrflg && nfs_sigintr(nmp, (struct nfsreq *)0, p))
			return (EINTR);
	}

	/*
	 * Now, flush as required.
	 */
	np->n_flag |= NFLUSHINPROG;
D 46
	error = nfsvinvalbuf(vp, flags, cred, p, slpflag, 0);
E 46
I 46
	error = vinvalbuf(vp, flags, cred, p, slpflag, 0);
E 46
	while (error) {
		if (intrflg && nfs_sigintr(nmp, (struct nfsreq *)0, p)) {
			np->n_flag &= ~NFLUSHINPROG;
			if (np->n_flag & NFLUSHWANT) {
				np->n_flag &= ~NFLUSHWANT;
				wakeup((caddr_t)&np->n_flag);
			}
			return (EINTR);
		}
D 46
		error = nfsvinvalbuf(vp, flags, cred, p, 0, slptimeo);
E 46
I 46
		error = vinvalbuf(vp, flags, cred, p, 0, slptimeo);
E 46
	}
	np->n_flag &= ~(NMODIFIED | NFLUSHINPROG);
	if (np->n_flag & NFLUSHWANT) {
		np->n_flag &= ~NFLUSHWANT;
		wakeup((caddr_t)&np->n_flag);
	}
	return (0);
}

/*
 * Initiate asynchronous I/O. Return an error if no nfsiods are available.
 * This is mainly to avoid queueing async I/O requests when the nfsiods
 * are all hung on a dead server.
 */
I 56
int
E 56
nfs_asyncio(bp, cred)
	register struct buf *bp;
	struct ucred *cred;
{
	register int i;

	if (nfs_numasync == 0)
		return (EIO);
	for (i = 0; i < NFS_MAXASYNCDAEMON; i++)
	    if (nfs_iodwant[i]) {
		if (bp->b_flags & B_READ) {
			if (bp->b_rcred == NOCRED && cred != NOCRED) {
				crhold(cred);
				bp->b_rcred = cred;
			}
		} else {
I 56
			bp->b_flags |= B_WRITEINPROG;
E 56
			if (bp->b_wcred == NOCRED && cred != NOCRED) {
				crhold(cred);
				bp->b_wcred = cred;
			}
		}
	
D 51
		queue_enter_tail(&nfs_bufq, bp, struct buf *, b_freelist);
E 51
I 51
		TAILQ_INSERT_TAIL(&nfs_bufq, bp, b_freelist);
E 51
		nfs_iodwant[i] = (struct proc *)0;
		wakeup((caddr_t)&nfs_iodwant[i]);
		return (0);
	    }
D 56
	return (EIO);
E 56
I 56

	/*
	 * If it is a read or a write already marked B_WRITEINPROG or B_NOCACHE
	 * return EIO so the process will call nfs_doio() and do it
	 * synchronously.
	 */
	if (bp->b_flags & (B_READ | B_WRITEINPROG | B_NOCACHE))
		return (EIO);

	/*
	 * Just turn the async write into a delayed write, instead of
	 * doing in synchronously. Hopefully, at least one of the nfsiods
	 * is currently doing a write for this file and will pick up the
	 * delayed writes before going back to sleep.
	 */
	bp->b_flags |= B_DELWRI;
	reassignbuf(bp, bp->b_vp);
	biodone(bp);
	return (0);
E 56
}

/*
 * Do an I/O operation to/from a cache block. This may be called
 * synchronously or from an nfsiod.
 */
int
nfs_doio(bp, cr, p)
	register struct buf *bp;
D 56
	struct cred *cr;
E 56
I 56
	struct ucred *cr;
E 56
	struct proc *p;
{
	register struct uio *uiop;
	register struct vnode *vp;
	struct nfsnode *np;
	struct nfsmount *nmp;
D 56
	int error, diff, len;
E 56
I 56
	int error = 0, diff, len, iomode, must_commit = 0;
E 56
	struct uio uio;
	struct iovec io;
I 56
	nfsquad_t tquad;
E 56

	vp = bp->b_vp;
	np = VTONFS(vp);
	nmp = VFSTONFS(vp->v_mount);
	uiop = &uio;
	uiop->uio_iov = &io;
	uiop->uio_iovcnt = 1;
	uiop->uio_segflg = UIO_SYSSPACE;
	uiop->uio_procp = p;

	/*
	 * Historically, paging was done with physio, but no more.
	 */
D 56
	if (bp->b_flags & B_PHYS)
	    panic("doio phys");
	if (bp->b_flags & B_READ) {
E 56
I 56
	if (bp->b_flags & B_PHYS) {
	    /*
	     * ...though reading /dev/drum still gets us here.
	     */
E 56
	    io.iov_len = uiop->uio_resid = bp->b_bcount;
I 56
	    /* mapping was done by vmapbuf() */
E 56
D 49
	    io.iov_base = bp->b_un.b_addr;
E 49
I 49
	    io.iov_base = bp->b_data;
I 56
	    uiop->uio_offset = ((off_t)bp->b_blkno) * DEV_BSIZE;
	    if (bp->b_flags & B_READ) {
		uiop->uio_rw = UIO_READ;
		nfsstats.read_physios++;
		error = nfs_readrpc(vp, uiop, cr);
	    } else
		panic("physio write");
	    if (error) {
		bp->b_flags |= B_ERROR;
		bp->b_error = error;
	    }
	} else if (bp->b_flags & B_READ) {
	    io.iov_len = uiop->uio_resid = bp->b_bcount;
	    io.iov_base = bp->b_data;
E 56
E 49
	    uiop->uio_rw = UIO_READ;
	    switch (vp->v_type) {
	    case VREG:
D 56
		uiop->uio_offset = bp->b_blkno * DEV_BSIZE;
E 56
I 56
		uiop->uio_offset = ((off_t)bp->b_blkno) * DEV_BSIZE;
E 56
		nfsstats.read_bios++;
		error = nfs_readrpc(vp, uiop, cr);
		if (!error) {
		    bp->b_validoff = 0;
		    if (uiop->uio_resid) {
			/*
			 * If len > 0, there is a hole in the file and
			 * no writes after the hole have been pushed to
			 * the server yet.
			 * Just zero fill the rest of the valid area.
			 */
			diff = bp->b_bcount - uiop->uio_resid;
D 56
			len = np->n_size - (bp->b_blkno * DEV_BSIZE
E 56
I 56
			len = np->n_size - (((u_quad_t)bp->b_blkno) * DEV_BSIZE
E 56
				+ diff);
			if (len > 0) {
			    len = min(len, uiop->uio_resid);
D 49
			    bzero(bp->b_un.b_addr + diff, len);
E 49
I 49
			    bzero((char *)bp->b_data + diff, len);
E 49
			    bp->b_validend = diff + len;
			} else
			    bp->b_validend = diff;
		    } else
			bp->b_validend = bp->b_bcount;
		}
		if (p && (vp->v_flag & VTEXT) &&
			(((nmp->nm_flag & NFSMNT_NQNFS) &&
I 54
D 56
			  NQNFS_CKINVALID(vp, np, NQL_READ) &&
E 56
I 56
			  NQNFS_CKINVALID(vp, np, ND_READ) &&
E 56
E 54
			  np->n_lrev != np->n_brev) ||
			 (!(nmp->nm_flag & NFSMNT_NQNFS) &&
			  np->n_mtime != np->n_vattr.va_mtime.ts_sec))) {
			uprintf("Process killed due to text file modification\n");
			psignal(p, SIGKILL);
D 50
			p->p_flag |= SKEEP;
E 50
I 50
			p->p_flag |= P_NOSWAP;
E 50
		}
		break;
	    case VLNK:
D 56
		uiop->uio_offset = 0;
E 56
I 56
		uiop->uio_offset = (off_t)0;
E 56
		nfsstats.readlink_bios++;
		error = nfs_readlinkrpc(vp, uiop, cr);
		break;
	    case VDIR:
D 56
		uiop->uio_offset = bp->b_lblkno;
E 56
		nfsstats.readdir_bios++;
D 56
		if (VFSTONFS(vp->v_mount)->nm_flag & NFSMNT_NQNFS)
		    error = nfs_readdirlookrpc(vp, uiop, cr);
		else
		    error = nfs_readdirrpc(vp, uiop, cr);
		/*
		 * Save offset cookie in b_blkno.
		 */
		bp->b_blkno = uiop->uio_offset;
E 56
I 56
		uiop->uio_offset = ((u_quad_t)bp->b_lblkno) * NFS_DIRBLKSIZ;
		if (nmp->nm_flag & NFSMNT_RDIRPLUS) {
			error = nfs_readdirplusrpc(vp, uiop, cr);
			if (error == NFSERR_NOTSUPP)
				nmp->nm_flag &= ~NFSMNT_RDIRPLUS;
		}
		if ((nmp->nm_flag & NFSMNT_RDIRPLUS) == 0)
			error = nfs_readdirrpc(vp, uiop, cr);
E 56
		break;
I 56
	    default:
		printf("nfs_doio:  type %x unexpected\n",vp->v_type);
		break;
E 56
	    };
	    if (error) {
		bp->b_flags |= B_ERROR;
		bp->b_error = error;
	    }
	} else {
	    io.iov_len = uiop->uio_resid = bp->b_dirtyend
		- bp->b_dirtyoff;
D 56
	    uiop->uio_offset = (bp->b_blkno * DEV_BSIZE)
E 56
I 56
	    uiop->uio_offset = ((off_t)bp->b_blkno) * DEV_BSIZE
E 56
		+ bp->b_dirtyoff;
D 49
	    io.iov_base = bp->b_un.b_addr + bp->b_dirtyoff;
E 49
I 49
	    io.iov_base = (char *)bp->b_data + bp->b_dirtyoff;
E 49
	    uiop->uio_rw = UIO_WRITE;
	    nfsstats.write_bios++;
D 56
	    if (bp->b_flags & B_APPENDWRITE)
		error = nfs_writerpc(vp, uiop, cr, IO_APPEND);
E 56
I 56
	    if ((bp->b_flags & (B_ASYNC | B_NEEDCOMMIT | B_NOCACHE)) == B_ASYNC)
		iomode = NFSV3WRITE_UNSTABLE;
E 56
	    else
D 56
		error = nfs_writerpc(vp, uiop, cr, 0);
	    bp->b_flags &= ~(B_WRITEINPROG | B_APPENDWRITE);
E 56
I 56
		iomode = NFSV3WRITE_FILESYNC;
	    bp->b_flags |= B_WRITEINPROG;
	    error = nfs_writerpc(vp, uiop, cr, &iomode, &must_commit);
	    if (!error && iomode == NFSV3WRITE_UNSTABLE)
		bp->b_flags |= B_NEEDCOMMIT;
	    else
		bp->b_flags &= ~B_NEEDCOMMIT;
	    bp->b_flags &= ~B_WRITEINPROG;
E 56

	    /*
	     * For an interrupted write, the buffer is still valid and the
	     * write hasn't been pushed to the server yet, so we can't set
	     * B_ERROR and report the interruption by setting B_EINTR. For
	     * the B_ASYNC case, B_EINTR is not relevant, so the rpc attempt
	     * is essentially a noop.
I 56
	     * For the case of a V3 write rpc not being committed to stable
	     * storage, the block is still dirty and requires either a commit
	     * rpc or another write rpc with iomode == NFSV3WRITE_FILESYNC
	     * before the block is reused. This is indicated by setting the
	     * B_DELWRI and B_NEEDCOMMIT flags.
E 56
	     */
D 56
	    if (error == EINTR) {
		bp->b_flags &= ~B_INVAL;
E 56
I 56
	    if (error == EINTR || (!error && (bp->b_flags & B_NEEDCOMMIT))) {
E 56
		bp->b_flags |= B_DELWRI;

		/*
		 * Since for the B_ASYNC case, nfs_bwrite() has reassigned the
		 * buffer to the clean list, we have to reassign it back to the
		 * dirty one. Ugh.
		 */
		if (bp->b_flags & B_ASYNC)
		    reassignbuf(bp, vp);
		else
		    bp->b_flags |= B_EINTR;
	    } else {
		if (error) {
		    bp->b_flags |= B_ERROR;
		    bp->b_error = np->n_error = error;
		    np->n_flag |= NWRITEERR;
		}
		bp->b_dirtyoff = bp->b_dirtyend = 0;
	    }
	}
	bp->b_resid = uiop->uio_resid;
I 56
	if (must_commit)
		nfs_clearcommit(vp->v_mount);
E 56
	biodone(bp);
E 44
E 36
E 33
D 21
#ifdef notdef
	/* Should we try and do this for nfs ?? */
D 5
	if (error && (ioflag & IO_UNIT))
E 5
I 5
	if (error && (ioflag & IO_UNIT)) {
E 5
		np->n_size = osize;
D 5
	else
E 5
I 5
		uio->uio_offset -= cnt - uio->uio_resid;
		uio->uio_resid = cnt;
	}
E 5
#endif
E 21
D 5
		*offp += cnt - uio->uio_resid;
out:
	if ((ioflag & IO_NODELOCKED) == 0)
		nfs_unlock(vp);
E 5
	return (error);
D 8
}

/*
 * Flush and invalidate all of the buffers associated with the blocks of vp
 */
nfs_blkflush(vp, blkno, size, invalidate)
	struct vnode *vp;
	daddr_t blkno;
	long size;
	int invalidate;
{
	register struct buf *ep;
	struct buf *dp;
D 3
	daddr_t curblkno, last;
E 3
I 3
	daddr_t curblk, nextblk, ecurblk, lastblk;
E 3
	int s, error, allerrors = 0;
D 3

	last = blkno + btodb(size);
	for (curblkno = blkno; curblkno <= last;
	     curblkno += (NFS_BIOSIZE / DEV_BSIZE)) {
		dp = BUFHASH(vp, curblkno);
E 3
I 3
     
	/*
	 * Iterate through each possible hash chain.
	 */
	lastblk = blkno + btodb(size+DEV_BSIZE-1) - 1;
	for (curblk = blkno; curblk <= lastblk; curblk = nextblk) {
#if RND & (RND-1)
	        nextblk = ((curblk / RND) + 1) * RND;
#else
	        nextblk = ((curblk & ~(RND-1)) + RND);
#endif
	        ecurblk = nextblk > lastblk ? lastblk : nextblk - 1;
	        dp = BUFHASH(vp, curblk);
E 3
loop:
D 3
		for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
			if (ep->b_vp != vp || (ep->b_flags & B_INVAL))
				continue;
			if (curblkno != ep->b_blkno)
				continue;
			s = splbio();
			if (ep->b_flags & B_BUSY) {
				ep->b_flags |= B_WANTED;
				sleep((caddr_t)ep, PRIBIO+1);
				splx(s);
				goto loop;
			}
			splx(s);
			notavail(ep);
			if (ep->b_flags & B_DELWRI) {
				ep->b_flags &= ~B_ASYNC;
				if (error = bwrite(ep))
					allerrors = error;
				goto loop;
			}
E 3
I 3
	        for (ep = dp->b_forw; ep != dp; ep = ep->b_forw) {
	                if (ep->b_vp != vp || (ep->b_flags & B_INVAL))
	                        continue;
	                /* look for overlap */
D 7
	                if (ep->b_bcount == 0 || ep->b_blkno > ecurblk ||
	                    ep->b_blkno + btodb(ep->b_bcount) <= curblk)
E 7
I 7
	                if (ep->b_bcount == 0 || ep->b_lblkno > ecurblk ||
	                    ep->b_lblkno + btodb(ep->b_bcount) <= curblk)
E 7
	                        continue;
	                s = splbio();
	                if (ep->b_flags&B_BUSY) {
	                        ep->b_flags |= B_WANTED;
	                        sleep((caddr_t)ep, PRIBIO+1);
	                        splx(s);
	                        goto loop;
	                }
	                if (ep->b_flags & B_DELWRI) {
	                        splx(s);
	                        notavail(ep);
	                        if (error = bwrite(ep))
	                                allerrors = error;
	                        goto loop;
	                }
	                splx(s);
E 3
			if (invalidate) {
I 3
				notavail(ep);
E 3
				ep->b_flags |= B_INVAL;
D 6
				brelvp(ep);
E 6
I 3
				brelse(ep);
E 3
			}
D 3
			brelse(ep);
		}
E 3
I 3
	        }
E 3
	}
	return (allerrors);
E 8
}
I 32
D 33
#undef vp
#undef uio
#undef ioflag
#undef cred
E 33
E 32
E 1
