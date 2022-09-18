h48803
s 00002/00002/00520
d D 8.9 95/05/14 00:49:21 mckusick 39 38
c convert VOP_LOCK to vn_lock; add parameters to VOP_UNLOCK and vget
e
s 00001/00000/00521
d D 8.8 95/01/09 17:36:50 cgd 38 37
c strategy returns void, ioctl cmd is u_long
e
s 00001/00001/00520
d D 8.7 94/08/24 10:44:03 mckusick 37 36
c return ENOTTY to keep disklabel happy (from cgd)
e
s 00001/00001/00520
d D 8.6 94/04/01 16:47:12 hibler 36 35
c oops, forgot to update the Utah id
e
s 00035/00019/00486
d D 8.5 94/04/01 16:45:30 hibler 35 34
c take advantage of contig block info returned from BMAP
c sigh...when will I learn, don't do IO to buffers on the stack!
c get rid of the "if 0"ed FSYNC call, it doesn't apply anymore anyway
e
s 00001/00001/00504
d D 8.4 93/12/30 18:06:40 mckusick 34 33
c lint
e
s 00004/00004/00501
d D 8.3 93/11/16 14:20:57 hibler 33 32
c b_un.b_addr -> b_data
e
s 00016/00000/00489
d D 8.2 93/09/27 12:03:16 hibler 32 31
c return an error if file has a hole (VOP_BMAP returns blkno==-1)
e
s 00002/00002/00487
d D 8.1 93/06/10 21:21:26 bostic 31 30
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00050/00026/00439
d D 7.16 93/04/27 13:24:37 hibler 30 29
c add attach routine for Torek's autoconf code
e
s 00011/00002/00454
d D 7.15 92/12/27 08:54:58 hibler 29 28
c init some needed buf fields
e
s 00001/00001/00455
d D 7.14 92/10/11 08:47:22 bostic 28 27
c make kernel includes standard
e
s 00001/00001/00455
d D 7.13 92/10/07 17:15:48 margo 27 26
c Add an argument to bmap.
e
s 00017/00022/00439
d D 7.12 92/07/13 09:09:52 pendry 26 25
c bring up to date wrt vnode conventions
e
s 00003/00002/00458
d D 7.11 92/06/05 15:21:00 hibler 25 24
c merge latest Utah hp300 code including 68040 support
e
s 00009/00003/00451
d D 7.10 92/05/14 17:25:20 heideman 24 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 16:59:13 heideman 23 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 16:41:45 heideman 22 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 16:31:42 heideman 21 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 15:49:04 heideman 20 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 15:37:46 heideman 19 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 14:43:56 heideman 18 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 12:46:28 heideman 17 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 11:43:31 heideman 16 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/14 10:24:24 heideman 15 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/13 23:02:12 heideman 14 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/13 18:50:35 heideman 13 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/13 18:22:17 heideman 12 10
c vnode interface conversion
e
s 00009/00003/00451
d R 7.10 92/05/13 18:11:51 heideman 11 10
c vnode interface conversion
e
s 00002/00001/00452
d D 7.9 92/05/13 18:07:55 heideman 10 8
c minor syntax change before vnode interface conversion
e
s 00009/00002/00451
d R 7.9 92/05/13 17:56:28 heideman 9 8
c vnode interface conversion
e
s 00002/00003/00451
d D 7.8 92/02/29 18:35:50 hibler 8 7
c sync with current vn_open interface
e
s 00001/00001/00453
d D 7.7 91/12/14 21:32:21 mckusick 7 6
c statfs.f_bsize => statfs.f_iosize; statfs.f_fsize => statfs.f_bsize (for SunOS)
e
s 00009/00009/00445
d D 7.6 91/06/21 10:57:07 mckusick 6 5
c have to unlock after call to vn_open; 
c use vn_close rather than vrele after vn_open
e
s 00173/00162/00281
d D 7.5 91/05/07 09:46:18 hibler 5 4
c fd -> vn
e
s 00004/00000/00439
d D 7.4 91/05/04 19:43:54 karels 4 3
c mark as broken
e
s 00012/00012/00427
d D 7.3 90/12/16 16:35:41 bostic 3 2
c kernel reorg
e
s 00001/00001/00438
d D 7.2 90/11/04 19:21:57 mckusick 2 1
c update from Mike Hibler
e
s 00439/00000/00000
d D 7.1 90/05/08 22:06:53 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 31
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 31
I 31
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 31
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: fd.c 1.3 89/12/03$
E 2
I 2
D 5
 * from: Utah $Hdr: fd.c 1.1 90/07/09$
E 5
I 5
D 25
 * from: Utah $Hdr: vn.c 1.1 91/04/30$
E 25
I 25
D 29
 * from: Utah $Hdr: fd.c 1.3 89/12/03$
E 29
I 29
D 36
 * from: Utah $Hdr: vn.c 1.8 92/12/20$
E 36
I 36
 * from: Utah $Hdr: vn.c 1.13 94/04/02$
E 36
E 29
E 25
E 5
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
I 4
D 5
 * CURRENTLY BROKEN; the name "fd" collides with /dev/fd/xxx.
 * This would need to be converted to the new proc/user layout as well.
 */
/*
E 4
 * File (vnode) disk driver.
E 5
I 5
 * Vnode disk driver.
E 5
 *
D 5
 * Block/character interface to a vnode.  Note that this uses the
 * VOP_BMAP/VOP_STRATEGY interface to the vnode instead of a simple
 * VOP_RDWR.  We do this to avoid distorting the local buffer cache.
E 5
I 5
 * Block/character interface to a vnode.  Allows one to treat a file
 * as a disk (e.g. build a filesystem in it, mount it, etc.).
E 5
 *
D 5
 * NOTE: There is a security issue involved with this driver.
E 5
I 5
 * NOTE 1: This uses the VOP_BMAP/VOP_STRATEGY interface to the vnode
 * instead of a simple VOP_RDWR.  We do this to avoid distorting the
 * local buffer cache.
 *
 * NOTE 2: There is a security issue involved with this driver.
E 5
 * Once mounted all access to the contents of the "mapped" file via
 * the special file is controlled by the permissions on the special
 * file, the protection of the mapped file is ignored (effectively,
 * by using root credentials in all transactions).
I 29
 *
 * NOTE 3: Doesn't interact with leases, should it?
E 29
 */
D 5
#include "fd.h"
#if NFD > 0
E 5
I 5
#include "vn.h"
#if NVN > 0
E 5

D 3
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "errno.h"
#include "dkstat.h"
#include "ioctl.h"
#include "user.h"
#include "vfs.h"
#include "vnode.h"
#include "file.h"
#include "uio.h"
#include "malloc.h"
E 3
I 3
D 26
#include "sys/param.h"
#include "sys/systm.h"
D 5
#include "sys/buf.h"
E 5
I 5
#include "sys/namei.h"
#include "sys/proc.h"
E 5
#include "sys/errno.h"
#include "sys/dkstat.h"
I 5
#include "sys/buf.h"
#include "sys/malloc.h"
E 5
#include "sys/ioctl.h"
D 5
#include "sys/user.h"
#include "sys/vfs.h"
E 5
I 5
#include "sys/mount.h"
E 5
#include "sys/vnode.h"
I 5
#include "sys/specdev.h"
E 5
#include "sys/file.h"
#include "sys/uio.h"
E 26
I 26
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/errno.h>
#include <sys/dkstat.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/ioctl.h>
#include <sys/mount.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/uio.h>
E 26
D 5
#include "sys/malloc.h"
E 5
E 3

I 26
#include <miscfs/specfs/specdev.h>

E 26
D 5
#include "fdioctl.h"
E 5
I 5
D 28
#include "vnioctl.h"
E 28
I 28
#include <dev/vnioctl.h>
E 28
E 5

#ifdef DEBUG
I 35
int dovncluster = 1;
E 35
D 5
int fddebug = 0x00;
#define FDB_FOLLOW	0x01
#define FDB_INIT	0x02
#define FDB_IO		0x04
E 5
I 5
int vndebug = 0x00;
#define VDB_FOLLOW	0x01
#define VDB_INIT	0x02
#define VDB_IO		0x04
E 5
#endif

D 5
struct	buf fdbuf[NFD];
struct	buf fdtab[NFD];
E 5
I 5
D 30
struct	buf vnbuf[NVN];
struct	buf vntab[NVN];
E 5

E 30
#define b_cylin	b_resid

D 5
#define	fdunit(x)	((minor(x) >> 3) & 0x7)	/* for consistency */
E 5
I 5
#define	vnunit(x)	((minor(x) >> 3) & 0x7)	/* for consistency */
E 5

D 5
#define	getfdbuf()	\
E 5
I 5
#define	getvnbuf()	\
E 5
	((struct buf *)malloc(sizeof(struct buf), M_DEVBUF, M_WAITOK))
D 5
#define putfdbuf(bp)	\
E 5
I 5
#define putvnbuf(bp)	\
E 5
	free((caddr_t)(bp), M_DEVBUF)

D 5
struct fd_softc {
E 5
I 5
struct vn_softc {
E 5
	int		 sc_flags;	/* flags */
D 5
	size_t		 sc_size;	/* size of fd */
E 5
I 5
	size_t		 sc_size;	/* size of vn */
E 5
	struct vnode	*sc_vp;		/* vnode */
	struct ucred	*sc_cred;	/* credentials */
	int		 sc_maxactive;	/* max # of active requests */
D 5
} fd_softc[NFD];
E 5
I 5
D 30
} vn_softc[NVN];
E 30
I 30
	struct buf	 sc_tab;	/* transfer queue */
};
E 30
E 5

/* sc_flags */
D 5
#define	FDF_ALIVE	0x01
#define FDF_INITED	0x02
E 5
I 5
#define	VNF_ALIVE	0x01
#define VNF_INITED	0x02
E 5

I 30
#if 0	/* if you need static allocation */
struct vn_softc vn_softc[NVN];
int numvnd = NVN;
#else
struct vn_softc *vn_softc;
int numvnd;
#endif

void
vnattach(num)
	int num;
{
	char *mem;
	register u_long size;

	if (num <= 0)
		return;
	size = num * sizeof(struct vn_softc);
	mem = malloc(size, M_DEVBUF, M_NOWAIT);
	if (mem == NULL) {
		printf("WARNING: no memory for vnode disks\n");
		return;
	}
	bzero(mem, size);
	vn_softc = (struct vn_softc *)mem;
	numvnd = num;
}

E 30
D 5
fdopen(dev, flags)
E 5
I 5
int
vnopen(dev, flags, mode, p)
E 5
	dev_t dev;
I 5
	int flags, mode;
	struct proc *p;
E 5
{
D 5
	int unit = fdunit(dev);
E 5
I 5
	int unit = vnunit(dev);
E 5

#ifdef DEBUG
D 5
	if (fddebug & FDB_FOLLOW)
		printf("fdopen(%x, %x)\n", dev, flags);
E 5
I 5
	if (vndebug & VDB_FOLLOW)
		printf("vnopen(%x, %x, %x, %x)\n", dev, flags, mode, p);
E 5
#endif
D 5
	if (unit >= NFD)
E 5
I 5
D 30
	if (unit >= NVN)
E 30
I 30
	if (unit >= numvnd)
E 30
E 5
		return(ENXIO);
	return(0);
}

/*
 * Break the request into bsize pieces and submit using VOP_BMAP/VOP_STRATEGY.
 * Note that this driver can only be used for swapping over NFS on the hp
 * since nfs_strategy on the vax cannot handle u-areas and page tables.
 */
I 38
void
E 38
D 5
fdstrategy(bp)
E 5
I 5
vnstrategy(bp)
E 5
	register struct buf *bp;
{
I 24
D 26
	USES_VOP_BMAP;
E 26
E 24
D 5
	int unit = fdunit(bp->b_dev);
	register struct fd_softc *fs = &fd_softc[unit];
E 5
I 5
	int unit = vnunit(bp->b_dev);
	register struct vn_softc *vn = &vn_softc[unit];
E 5
	register struct buf *nbp;
	register int bn, bsize, resid;
	register caddr_t addr;
D 35
	int sz, flags;
E 35
I 35
	int sz, flags, error;
E 35
D 5
	extern int fdiodone();
E 5
I 5
D 25
	extern int vniodone();
E 25
I 25
	extern void vniodone();
E 25
E 5

#ifdef DEBUG
D 5
	if (fddebug & FDB_FOLLOW)
		printf("fdstrategy(%x): unit %d\n", bp, unit);
E 5
I 5
	if (vndebug & VDB_FOLLOW)
		printf("vnstrategy(%x): unit %d\n", bp, unit);
E 5
#endif
D 5
	if ((fs->sc_flags & FDF_INITED) == 0) {
E 5
I 5
	if ((vn->sc_flags & VNF_INITED) == 0) {
E 5
		bp->b_error = ENXIO;
		bp->b_flags |= B_ERROR;
D 5
		iodone(bp);
E 5
I 5
		biodone(bp);
E 5
		return;
	}
	bn = bp->b_blkno;
	sz = howmany(bp->b_bcount, DEV_BSIZE);
	bp->b_resid = bp->b_bcount;
D 5
	if (bn < 0 || bn + sz > fs->sc_size) {
		if (bn != fs->sc_size) {
E 5
I 5
	if (bn < 0 || bn + sz > vn->sc_size) {
		if (bn != vn->sc_size) {
E 5
			bp->b_error = EINVAL;
			bp->b_flags |= B_ERROR;
		}
D 5
		iodone(bp);
E 5
I 5
		biodone(bp);
E 5
		return;
	}
	bn = dbtob(bn);
D 5
	bsize = fs->sc_vp->v_vfsp->vfs_bsize;
E 5
I 5
D 7
	bsize = vn->sc_vp->v_mount->mnt_stat.f_bsize;
E 7
I 7
	bsize = vn->sc_vp->v_mount->mnt_stat.f_iosize;
E 7
E 5
D 33
	addr = bp->b_un.b_addr;
E 33
I 33
	addr = bp->b_data;
E 33
	flags = bp->b_flags | B_CALL;
	for (resid = bp->b_resid; resid; resid -= sz) {
		struct vnode *vp;
		daddr_t nbn;
D 35
		int off, s;
E 35
I 35
		int off, s, nra;
E 35

D 5
		nbp = getfdbuf();
E 5
I 5
D 35
		nbp = getvnbuf();
E 5
		off = bn % bsize;
D 26
		sz = MIN(bsize - off, resid);
E 26
I 26
		sz = min(bsize - off, resid);
E 26
D 5
		(void) VOP_BMAP(fs->sc_vp, bn / bsize, &vp, &nbn);
E 5
I 5
D 27
		(void) VOP_BMAP(vn->sc_vp, bn / bsize, &vp, &nbn);
E 27
I 27
		(void) VOP_BMAP(vn->sc_vp, bn / bsize, &vp, &nbn, NULL);
E 35
I 35
		nra = 0;
		error = VOP_BMAP(vn->sc_vp, bn / bsize, &vp, &nbn, &nra);
		if (error == 0 && (long)nbn == -1)
			error = EIO;
E 35
E 27
E 5
#ifdef DEBUG
I 35
		if (!dovncluster)
			nra = 0;
#endif

		if (off = bn % bsize)
			sz = bsize - off;
		else
			sz = (1 + nra) * bsize;
		if (resid < sz)
			sz = resid;
#ifdef DEBUG
E 35
D 5
		if (fddebug & FDB_IO)
			printf("fdstrategy: vp %x/%x bn %x/%x dev %x\n",
			       fs->sc_vp, vp, bn, nbn, vp->v_rdev);
E 5
I 5
		if (vndebug & VDB_IO)
D 35
			printf("vnstrategy: vp %x/%x bn %x/%x\n",
			       vn->sc_vp, vp, bn, nbn);
E 35
I 35
			printf("vnstrategy: vp %x/%x bn %x/%x sz %x\n",
			       vn->sc_vp, vp, bn, nbn, sz);
E 35
E 5
#endif
I 35

		nbp = getvnbuf();
E 35
		nbp->b_flags = flags;
		nbp->b_bcount = sz;
		nbp->b_bufsize = bp->b_bufsize;
		nbp->b_error = 0;
D 5
		nbp->b_dev = vp->v_rdev;
E 5
I 5
		if (vp->v_type == VBLK || vp->v_type == VCHR)
			nbp->b_dev = vp->v_rdev;
		else
			nbp->b_dev = NODEV;
E 5
D 33
		nbp->b_un.b_addr = addr;
E 33
I 33
		nbp->b_data = addr;
E 33
		nbp->b_blkno = nbn + btodb(off);
		nbp->b_proc = bp->b_proc;
D 5
		nbp->b_iodone = fdiodone;
E 5
I 5
		nbp->b_iodone = vniodone;
E 5
		nbp->b_vp = vp;
		nbp->b_pfcent = (int) bp;	/* XXX */
I 29
		nbp->b_rcred = vn->sc_cred;	/* XXX crdup? */
		nbp->b_wcred = vn->sc_cred;	/* XXX crdup? */
		nbp->b_dirtyoff = bp->b_dirtyoff;
		nbp->b_dirtyend = bp->b_dirtyend;
		nbp->b_validoff = bp->b_validoff;
		nbp->b_validend = bp->b_validend;
E 29
		/*
I 32
D 35
		 * There is a hole in the file...punt.
E 35
I 35
		 * If there was an error or a hole in the file...punt.
E 35
		 * Note that we deal with this after the nbp allocation.
		 * This ensures that we properly clean up any operations
		 * that we have already fired off.
		 *
D 35
		 * XXX we could deal with this but it would be
E 35
I 35
		 * XXX we could deal with holes here but it would be
E 35
		 * a hassle (in the write case).
		 */
D 35
		if ((long)nbn == -1) {
			nbp->b_error = EIO;
E 35
I 35
		if (error) {
			nbp->b_error = error;
E 35
			nbp->b_flags |= B_ERROR;
			bp->b_resid -= (resid - sz);
			biodone(nbp);
			return;
		}
		/*
E 32
		 * Just sort by block number
		 */
		nbp->b_cylin = nbp->b_blkno;
		s = splbio();
D 5
		disksort(&fdtab[unit], nbp);
		if (fdtab[unit].b_active < fs->sc_maxactive) {
			fdtab[unit].b_active++;
			fdstart(unit);
E 5
I 5
D 30
		disksort(&vntab[unit], nbp);
		if (vntab[unit].b_active < vn->sc_maxactive) {
			vntab[unit].b_active++;
			vnstart(unit);
E 30
I 30
		disksort(&vn->sc_tab, nbp);
		if (vn->sc_tab.b_active < vn->sc_maxactive) {
			vn->sc_tab.b_active++;
			vnstart(vn);
E 30
E 5
		}
		splx(s);
		bn += sz;
		addr += sz;
	}
}

/*
 * Feed requests sequentially.
 * We do it this way to keep from flooding NFS servers if we are connected
 * to an NFS file.  This places the burden on the client rather than the
 * server.
 */
D 5
fdstart(unit)
E 5
I 5
D 30
vnstart(unit)
E 30
I 30
vnstart(vn)
	register struct vn_softc *vn;
E 30
E 5
{
I 24
D 26
	USES_VOP_STRATEGY;
E 26
E 24
D 5
	register struct fd_softc *fs = &fd_softc[unit];
E 5
I 5
D 30
	register struct vn_softc *vn = &vn_softc[unit];
E 30
E 5
	register struct buf *bp;

	/*
	 * Dequeue now since lower level strategy routine might
	 * queue using same links
	 */
D 5
	bp = fdtab[unit].b_actf;
	fdtab[unit].b_actf = bp->b_actf;
E 5
I 5
D 30
	bp = vntab[unit].b_actf;
	vntab[unit].b_actf = bp->b_actf;
E 30
I 30
	bp = vn->sc_tab.b_actf;
	vn->sc_tab.b_actf = bp->b_actf;
E 30
E 5
#ifdef DEBUG
D 5
	if (fddebug & FDB_IO)
		printf("fdstart(%d): bp %x vp %x blkno %x addr %x cnt %x\n",
E 5
I 5
	if (vndebug & VDB_IO)
		printf("vnstart(%d): bp %x vp %x blkno %x addr %x cnt %x\n",
E 5
D 30
		       unit, bp, bp->b_vp, bp->b_blkno, bp->b_un.b_addr,
E 30
I 30
D 33
		       vn-vn_softc, bp, bp->b_vp, bp->b_blkno, bp->b_un.b_addr,
E 33
I 33
		       vn-vn_softc, bp, bp->b_vp, bp->b_blkno, bp->b_data,
E 33
E 30
		       bp->b_bcount);
#endif
I 29
	if ((bp->b_flags & B_READ) == 0)
		bp->b_vp->v_numoutput++;
E 29
	VOP_STRATEGY(bp);
}

I 25
void
E 25
D 5
fdiodone(bp)
E 5
I 5
vniodone(bp)
E 5
	register struct buf *bp;
{
	register struct buf *pbp = (struct buf *)bp->b_pfcent;	/* XXX */
D 5
	register int unit = fdunit(pbp->b_dev);
E 5
I 5
D 30
	register int unit = vnunit(pbp->b_dev);
E 30
I 30
	register struct vn_softc *vn = &vn_softc[vnunit(pbp->b_dev)];
E 30
E 5
	int s;

	s = splbio();
#ifdef DEBUG
D 5
	if (fddebug & FDB_IO)
		printf("fdiodone(%d): bp %x vp %x blkno %x addr %x cnt %x\n",
E 5
I 5
	if (vndebug & VDB_IO)
		printf("vniodone(%d): bp %x vp %x blkno %x addr %x cnt %x\n",
E 5
D 30
		       unit, bp, bp->b_vp, bp->b_blkno, bp->b_un.b_addr,
E 30
I 30
D 33
		       vn-vn_softc, bp, bp->b_vp, bp->b_blkno, bp->b_un.b_addr,
E 33
I 33
		       vn-vn_softc, bp, bp->b_vp, bp->b_blkno, bp->b_data,
E 33
E 30
		       bp->b_bcount);
#endif
	if (bp->b_error) {
#ifdef DEBUG
D 5
		if (fddebug & FDB_IO)
			printf("fdiodone: bp %x error %d\n", bp, bp->b_error);
E 5
I 5
		if (vndebug & VDB_IO)
			printf("vniodone: bp %x error %d\n", bp, bp->b_error);
E 5
#endif
		pbp->b_flags |= B_ERROR;
D 5
		pbp->b_error = geterror(bp);
E 5
I 5
		pbp->b_error = biowait(bp);
E 5
	}
	pbp->b_resid -= bp->b_bcount;
D 5
	putfdbuf(bp);
E 5
I 5
	putvnbuf(bp);
E 5
	if (pbp->b_resid == 0) {
#ifdef DEBUG
D 5
		if (fddebug & FDB_IO)
			printf("fdiodone: pbp %x iodone\n", pbp);
E 5
I 5
		if (vndebug & VDB_IO)
			printf("vniodone: pbp %x iodone\n", pbp);
E 5
#endif
D 5
		iodone(pbp);
E 5
I 5
		biodone(pbp);
E 5
	}
D 5
	if (fdtab[unit].b_actf)
		fdstart(unit);
E 5
I 5
D 30
	if (vntab[unit].b_actf)
		vnstart(unit);
E 30
I 30
	if (vn->sc_tab.b_actf)
		vnstart(vn);
E 30
E 5
	else
D 5
		fdtab[unit].b_active--;
E 5
I 5
D 30
		vntab[unit].b_active--;
E 30
I 30
		vn->sc_tab.b_active--;
E 30
E 5
	splx(s);
}

D 5
fdread(dev, uio)
E 5
I 5
vnread(dev, uio, flags, p)
E 5
	dev_t dev;
	struct uio *uio;
I 5
	int flags;
	struct proc *p;
E 5
{
D 5
	register int unit = fdunit(dev);
E 5
I 5
D 30
	register int unit = vnunit(dev);
E 30
E 5

#ifdef DEBUG
D 5
	if (fddebug & FDB_FOLLOW)
		printf("fdread(%x, %x)\n", dev, uio);
E 5
I 5
	if (vndebug & VDB_FOLLOW)
		printf("vnread(%x, %x, %x, %x)\n", dev, uio, flags, p);
E 5
#endif
D 5
	return(physio(fdstrategy, &fdbuf[unit], dev, B_READ, minphys, uio));
E 5
I 5
D 30
	return(physio(vnstrategy, &vnbuf[unit], dev, B_READ, minphys, uio));
E 30
I 30
	return(physio(vnstrategy, NULL, dev, B_READ, minphys, uio));
E 30
E 5
}

D 5
fdwrite(dev, uio)
E 5
I 5
vnwrite(dev, uio, flags, p)
E 5
	dev_t dev;
	struct uio *uio;
I 5
	int flags;
	struct proc *p;
E 5
{
D 5
	register int unit = fdunit(dev);
E 5
I 5
D 30
	register int unit = vnunit(dev);
E 30
E 5

#ifdef DEBUG
D 5
	if (fddebug & FDB_FOLLOW)
		printf("fdwrite(%x, %x)\n", dev, uio);
E 5
I 5
	if (vndebug & VDB_FOLLOW)
		printf("vnwrite(%x, %x, %x, %x)\n", dev, uio, flags, p);
E 5
#endif
D 5
	return(physio(fdstrategy, &fdbuf[unit], dev, B_WRITE, minphys, uio));
E 5
I 5
D 30
	return(physio(vnstrategy, &vnbuf[unit], dev, B_WRITE, minphys, uio));
E 30
I 30
	return(physio(vnstrategy, NULL, dev, B_WRITE, minphys, uio));
E 30
E 5
}

/* ARGSUSED */
D 5
fdioctl(dev, cmd, data, flag)
E 5
I 5
vnioctl(dev, cmd, data, flag, p)
E 5
	dev_t dev;
	u_long cmd;
	caddr_t data;
	int flag;
I 5
	struct proc *p;
E 5
{
I 24
D 26
	USES_VOP_GETATTR;
	USES_VOP_UNLOCK;
E 26
E 24
D 5
	int unit = fdunit(dev);
	register struct fd_softc *fs;
	struct fd_ioctl *fio;
E 5
I 5
	int unit = vnunit(dev);
	register struct vn_softc *vn;
	struct vn_ioctl *vio;
E 5
	struct vattr vattr;
D 5
	struct vnode *vp;
E 5
I 5
	struct nameidata nd;
E 5
	int error;

#ifdef DEBUG
D 5
	if (fddebug & FDB_FOLLOW)
		printf("fdioctl(%x, %x, %x, %x): unit %d\n",
		       dev, cmd, data, flag, unit);
E 5
I 5
	if (vndebug & VDB_FOLLOW)
		printf("vnioctl(%x, %x, %x, %x, %x): unit %d\n",
		       dev, cmd, data, flag, p, unit);
E 5
#endif
D 5
	error = suser(u.u_cred, &u.u_acflag);
E 5
I 5
	error = suser(p->p_ucred, &p->p_acflag);
E 5
	if (error)
		return (error);
D 5
	if (unit >= NFD)
E 5
I 5
D 30
	if (unit >= NVN)
E 30
I 30
	if (unit >= numvnd)
E 30
E 5
		return (ENXIO);

D 5
	fs = &fd_softc[unit];
	fio = (struct fd_ioctl *)data;
E 5
I 5
	vn = &vn_softc[unit];
	vio = (struct vn_ioctl *)data;
E 5
	switch (cmd) {

D 5
	case FDIOCSET:
		if (fs->sc_flags & FDF_INITED)
E 5
I 5
	case VNIOCSET:
		if (vn->sc_flags & VNF_INITED)
E 5
			return(EBUSY);
		/*
		 * Always open for read and write.
		 * This is probably bogus, but it lets vn_open()
		 * weed out directories, sockets, etc. so we don't
		 * have to worry about them.
		 */
D 5
		error = vn_open(fio->fd_file, UIO_USERSPACE,
				FREAD|FWRITE, 0, &vp);
E 5
I 5
D 8
		nd.ni_segflg = UIO_USERSPACE;
		nd.ni_dirp = vio->vn_file;
D 6
		error = vn_open(&nd, p, FREAD|FWRITE, 0);
E 5
		if (error)
E 6
I 6
		if (error = vn_open(&nd, p, FREAD|FWRITE, 0))
E 8
I 8
		NDINIT(&nd, LOOKUP, FOLLOW, UIO_USERSPACE, vio->vn_file, p);
		if (error = vn_open(&nd, FREAD|FWRITE, 0))
E 8
E 6
			return(error);
D 5
		error = VOP_GETATTR(vp, &vattr, u.u_cred);
E 5
I 5
D 6
		error = VOP_GETATTR(nd.ni_vp, &vattr, p->p_ucred, p);
E 5
		if (error) {
D 5
			vn_close(vp, FREAD|FWRITE);
			VN_RELE(vp);
E 5
I 5
			vrele(nd.ni_vp);
E 6
I 6
		if (error = VOP_GETATTR(nd.ni_vp, &vattr, p->p_ucred, p)) {
D 39
			VOP_UNLOCK(nd.ni_vp);
E 39
I 39
			VOP_UNLOCK(nd.ni_vp, 0, p);
E 39
			(void) vn_close(nd.ni_vp, FREAD|FWRITE, p->p_ucred, p);
E 6
E 5
			return(error);
		}
I 6
D 39
		VOP_UNLOCK(nd.ni_vp);
E 39
I 39
		VOP_UNLOCK(nd.ni_vp, 0, p);
E 39
E 6
D 5
		fs->sc_vp = vp;
		fs->sc_size = btodb(vattr.va_size);	/* note truncation */
		error = fdsetcred(fs);
E 5
I 5
		vn->sc_vp = nd.ni_vp;
		vn->sc_size = btodb(vattr.va_size);	/* note truncation */
D 6
		error = vnsetcred(vn, p->p_ucred);
E 5
		if (error) {
D 5
			vn_close(vp, FREAD|FWRITE);
			VN_RELE(vp);
E 5
I 5
			vrele(vn->sc_vp);
E 6
I 6
		if (error = vnsetcred(vn, p->p_ucred)) {
D 35
			(void) vn_close(vn->sc_vp, FREAD|FWRITE, p->p_ucred, p);
E 35
I 35
			(void) vn_close(nd.ni_vp, FREAD|FWRITE, p->p_ucred, p);
E 35
E 6
E 5
			return(error);
		}
D 5
		fdthrottle(fs, vp);
		fio->fd_size = dbtob(fs->sc_size);
		fs->sc_flags |= FDF_INITED;
E 5
I 5
		vnthrottle(vn, vn->sc_vp);
		vio->vn_size = dbtob(vn->sc_size);
		vn->sc_flags |= VNF_INITED;
E 5
#ifdef DEBUG
D 5
		if (fddebug & FDB_INIT)
			printf("fdioctl: SET vp %x size %x\n",
			       fs->sc_vp, fs->sc_size);
E 5
I 5
		if (vndebug & VDB_INIT)
			printf("vnioctl: SET vp %x size %x\n",
			       vn->sc_vp, vn->sc_size);
E 5
#endif
		break;

D 5
	case FDIOCCLR:
		if ((fs->sc_flags & FDF_INITED) == 0)
E 5
I 5
	case VNIOCCLR:
		if ((vn->sc_flags & VNF_INITED) == 0)
E 5
			return(ENXIO);
D 5
		fdclear(fs);
E 5
I 5
		vnclear(vn);
E 5
#ifdef DEBUG
D 5
		if (fddebug & FDB_INIT)
			printf("fdioctl: CLRed\n");
E 5
I 5
		if (vndebug & VDB_INIT)
			printf("vnioctl: CLRed\n");
E 5
#endif
		break;

	default:
D 37
		return(ENXIO);
E 37
I 37
		return(ENOTTY);
E 37
	}
	return(0);
}

/*
 * Duplicate the current processes' credentials.  Since we are called only
 * as the result of a SET ioctl and only root can do that, any future access
 * to this "disk" is essentially as root.  Note that credentials may change
 * if some other uid can write directly to the mapped file (NFS).
 */
D 5
fdsetcred(fs)
	register struct fd_softc *fs;
E 5
I 5
vnsetcred(vn, cred)
	register struct vn_softc *vn;
D 34
	struct ucred cred;
E 34
I 34
	struct ucred *cred;
E 34
E 5
{
I 24
D 26
	USES_VOP_READ;
E 26
E 24
	struct uio auio;
	struct iovec aiov;
D 35
	char tmpbuf[DEV_BSIZE];
E 35
I 35
	char *tmpbuf;
	int error;
E 35

D 5
	fs->sc_cred = crdup(u.u_cred);
E 5
I 5
	vn->sc_cred = crdup(cred);
I 35
	tmpbuf = malloc(DEV_BSIZE, M_TEMP, M_WAITOK);

E 35
E 5
	/* XXX: Horrible kludge to establish credentials for NFS */
	aiov.iov_base = tmpbuf;
D 5
	aiov.iov_len = MIN(DEV_BSIZE, dbtob(fs->sc_size));
E 5
I 5
D 26
	aiov.iov_len = MIN(DEV_BSIZE, dbtob(vn->sc_size));
E 26
I 26
	aiov.iov_len = min(DEV_BSIZE, dbtob(vn->sc_size));
E 26
E 5
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = 0;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_resid = aiov.iov_len;
D 5
	return(VOP_READ(fs->sc_vp, &auio, 0, fs->sc_cred));
E 5
I 5
D 35
	return(VOP_READ(vn->sc_vp, &auio, 0, vn->sc_cred));
E 35
I 35
	error = VOP_READ(vn->sc_vp, &auio, 0, vn->sc_cred);

	free(tmpbuf, M_TEMP);
	return (error);
E 35
E 5
}

/*
 * Set maxactive based on FS type
 */
D 5
fdthrottle(fs, vp)
	register struct fd_softc *fs;
E 5
I 5
vnthrottle(vn, vp)
	register struct vn_softc *vn;
E 5
	struct vnode *vp;
{
D 5
	extern struct vnodeops ufs_vnodeops, nfs_vnodeops;
E 5
I 5
D 10
	extern struct vnodeops ufs_vnodeops, nfsv2_vnodeops;
E 10
I 10
D 24
	extern struct vnodeops ufs_vnodeops;
	extern struct vnodeops nfsv2_vnodeops;
E 24
I 24
D 29
	extern int (**ufs_vnodeop_p)();
E 29
	extern int (**nfsv2_vnodeop_p)();
E 24
E 10
E 5

D 5
	if (vp->v_op == &nfs_vnodeops)
		fs->sc_maxactive = 2;
E 5
I 5
D 24
	if (vp->v_op == &nfsv2_vnodeops)
E 24
I 24
	if (vp->v_op == nfsv2_vnodeop_p)
E 24
		vn->sc_maxactive = 2;
E 5
	else
D 5
		fs->sc_maxactive = 8;
E 5
I 5
		vn->sc_maxactive = 8;
E 5

D 5
	if (fs->sc_maxactive < 1)
		fs->sc_maxactive = 1;
E 5
I 5
	if (vn->sc_maxactive < 1)
		vn->sc_maxactive = 1;
E 5
}

D 5
fdshutdown()
E 5
I 5
vnshutdown()
E 5
{
D 5
	register struct fd_softc *fs;
E 5
I 5
	register struct vn_softc *vn;
E 5

D 5
	for (fs = &fd_softc[0]; fs < &fd_softc[NFD]; fs++)
		if (fs->sc_flags & FDF_INITED)
			fdclear(fs);
E 5
I 5
D 30
	for (vn = &vn_softc[0]; vn < &vn_softc[NVN]; vn++)
E 30
I 30
	for (vn = &vn_softc[0]; vn < &vn_softc[numvnd]; vn++)
E 30
		if (vn->sc_flags & VNF_INITED)
			vnclear(vn);
E 5
}

D 5
fdclear(fs)
	register struct fd_softc *fs;
E 5
I 5
vnclear(vn)
	register struct vn_softc *vn;
E 5
{
I 24
D 26
	USES_VOP_FSYNC;
E 26
E 24
D 5
	register struct vnode *vp = fs->sc_vp;
E 5
I 5
	register struct vnode *vp = vn->sc_vp;
I 6
	struct proc *p = curproc;		/* XXX */
E 6
E 5

#ifdef DEBUG
D 5
	if (fddebug & FDB_FOLLOW)
		printf("fdclear(%x): vp %x\n", vp);
E 5
I 5
	if (vndebug & VDB_FOLLOW)
		printf("vnclear(%x): vp %x\n", vp);
E 5
#endif
D 5
	fs->sc_flags &= ~FDF_INITED;
E 5
I 5
	vn->sc_flags &= ~VNF_INITED;
E 5
	if (vp == (struct vnode *)0)
D 5
		panic("fdioctl: null vp");
E 5
I 5
		panic("vnioctl: null vp");
E 5
D 35
#if 0
	/* XXX - this doesn't work right now */
D 5
	(void) VOP_FSYNC(vp, fs->sc_cred);
E 5
I 5
	(void) VOP_FSYNC(vp, 0, vn->sc_cred, MNT_WAIT, p);
E 5
#endif
E 35
D 5
	vn_close(vp, FREAD|FWRITE);
	VN_RELE(vp);
	crfree(fs->sc_cred);
	fs->sc_vp = (struct vnode *)0;
	fs->sc_cred = (struct ucred *)0;
	fs->sc_size = 0;
E 5
I 5
D 6
	vrele(vp);
E 6
I 6
	(void) vn_close(vp, FREAD|FWRITE, vn->sc_cred, p);
E 6
	crfree(vn->sc_cred);
	vn->sc_vp = (struct vnode *)0;
	vn->sc_cred = (struct ucred *)0;
	vn->sc_size = 0;
E 5
}

D 5
fdsize(dev)
E 5
I 5
vnsize(dev)
E 5
	dev_t dev;
{
D 5
	int unit = fdunit(dev);
	register struct fd_softc *fs = &fd_softc[unit];
E 5
I 5
	int unit = vnunit(dev);
	register struct vn_softc *vn = &vn_softc[unit];
E 5

D 5
	if (unit >= NFD || (fs->sc_flags & FDF_INITED) == 0)
E 5
I 5
D 30
	if (unit >= NVN || (vn->sc_flags & VNF_INITED) == 0)
E 30
I 30
	if (unit >= numvnd || (vn->sc_flags & VNF_INITED) == 0)
E 30
E 5
		return(-1);
D 5
	return(fs->sc_size);
E 5
I 5
	return(vn->sc_size);
E 5
}

D 5
fddump(dev)
E 5
I 5
vndump(dev)
E 5
{
	return(ENXIO);
}
#endif
E 1
