h14121
s 00002/00001/00682
d D 8.3 95/01/09 17:36:51 cgd 10 9
c strategy returns void, ioctl cmd is u_long
e
s 00004/00004/00679
d D 8.2 93/11/16 14:21:06 hibler 9 8
c b_un.b_addr -> b_data
e
s 00002/00002/00681
d D 8.1 93/06/10 21:21:08 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00085/00035/00598
d D 7.7 93/05/09 20:06:58 hibler 7 6
c cleanup, integrate with new pseudo-device interface
e
s 00038/00003/00595
d D 7.6 93/02/18 20:37:05 hibler 6 5
c disklabel inspired changes
e
s 00008/00008/00590
d D 7.5 92/10/11 08:47:21 bostic 5 4
c make kernel includes standard
e
s 00047/00008/00551
d D 7.4 91/05/07 09:47:41 hibler 4 3
c update from utah versoin
e
s 00007/00007/00552
d D 7.3 90/12/16 16:35:26 bostic 3 2
c kernel reorg
e
s 00025/00018/00534
d D 7.2 90/11/04 19:09:14 mckusick 2 1
c update from Mike Hibler
e
s 00552/00000/00000
d D 7.1 90/05/08 22:06:49 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: cd.c 1.4 89/09/17$
E 2
I 2
D 4
 * from: Utah $Hdr: cd.c 1.1 90/07/09$
E 4
I 4
 * from: Utah $Hdr: cd.c 1.6 90/11/28$
E 4
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * "Concatenated" disk driver.
 */
#include "cd.h"
#if NCD > 0

D 3
#include "param.h"
#include "systm.h"
#include "errno.h"
#include "dkstat.h"
#include "buf.h"
#include "malloc.h"
#include "conf.h"
E 3
I 3
D 5
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/errno.h"
#include "sys/dkstat.h"
#include "sys/buf.h"
#include "sys/malloc.h"
#include "sys/conf.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
I 7
#include <sys/proc.h>
E 7
#include <sys/errno.h>
#include <sys/dkstat.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/conf.h>
I 6
#include <sys/stat.h>
#ifdef COMPAT_NOLABEL
#include <sys/ioctl.h>
#include <sys/disklabel.h>
#include <sys/fcntl.h>
#endif
E 6
E 5
E 3

D 5
#include "cdvar.h"
E 5
I 5
#include <dev/cdvar.h>
E 5

#ifdef DEBUG
int cddebug = 0x00;
#define CDB_FOLLOW	0x01
#define CDB_INIT	0x02
#define CDB_IO		0x04
#endif

D 7
struct	buf cdbuf[NCD];
E 7
struct	buf *cdbuffer();
I 4
char	*cddevtostr();
E 4
D 7
int	cdiodone();
E 7
I 7
void	cdiodone();
E 7

D 7
#define	cdunit(x)	((minor(x) >> 3) & 0x7)	/* for consistency */
E 7
I 7
#define	cdunit(x)	((minor(x) >> 3) & 0xf)	/* for consistency */
E 7

#define	getcbuf()	\
	((struct buf *)malloc(sizeof(struct buf), M_DEVBUF, M_WAITOK))
#define putcbuf(bp)	\
	free((caddr_t)(bp), M_DEVBUF)

struct cd_softc {
	int		 sc_flags;		/* flags */
	size_t		 sc_size;		/* size of cd */
	int		 sc_ileave;		/* interleave */
	int		 sc_ncdisks;		/* number of components */
	struct cdcinfo	 sc_cinfo[NCDISKS];	/* component info */
	struct cdiinfo	 *sc_itable;		/* interleave table */
	int		 sc_usecnt;		/* number of requests active */
D 7
	struct buf	 *sc_bp;		/* "current" request */
E 7
	int		 sc_dk;			/* disk index */
D 7
} cd_softc[NCD];
E 7
I 7
};
E 7

/* sc_flags */
#define	CDF_ALIVE	0x01
#define CDF_INITED	0x02

I 7
struct cd_softc *cd_softc;
int numcd;

/*
 * Since this is called after auto-configuration of devices,
 * we can handle the initialization here.
 *
 * XXX this will not work if you want to use a cd as your primary
 * swap device since swapconf() has been called before now.
 */
void
cdattach(num)
	int num;
{
	char *mem;
	register u_long size;
	register struct cddevice *cd;
	extern int dkn;

	if (num <= 0)
		return;
	size = num * sizeof(struct cd_softc);
	mem = malloc(size, M_DEVBUF, M_NOWAIT);
	if (mem == NULL) {
		printf("WARNING: no memory for concatonated disks\n");
		return;
	}
	bzero(mem, size);
	cd_softc = (struct cd_softc *)mem;
	numcd = num;
	for (cd = cddevice; cd->cd_unit >= 0; cd++) {
		/*
		 * XXX
		 * Assign disk index first so that init routine
		 * can use it (saves having the driver drag around
		 * the cddevice pointer just to set up the dk_*
		 * info in the open routine).
		 */
		if (dkn < DK_NDRIVE)
			cd->cd_dk = dkn++;
		else
			cd->cd_dk = -1;
		if (cdinit(cd))
			printf("cd%d configured\n", cd->cd_unit);
		else if (cd->cd_dk >= 0) {
			cd->cd_dk = -1;
			dkn--;
		}
	}
}

E 7
cdinit(cd)
	struct cddevice *cd;
{
	register struct cd_softc *cs = &cd_softc[cd->cd_unit];
	register struct cdcinfo *ci;
	register size_t size;
	register int ix;
	size_t minsize;
	dev_t dev;
I 6
	struct bdevsw *bsw;
	int error;
I 7
	struct proc *p = curproc; /* XXX */
E 7
E 6

#ifdef DEBUG
	if (cddebug & (CDB_FOLLOW|CDB_INIT))
		printf("cdinit: unit %d\n", cd->cd_unit);
#endif
	cs->sc_dk = cd->cd_dk;
	cs->sc_size = 0;
	cs->sc_ileave = cd->cd_interleave;
	cs->sc_ncdisks = 0;
	/*
	 * Verify that each component piece exists and record
	 * relevant information about it.
	 */
	minsize = 0;
	for (ix = 0; ix < NCDISKS; ix++) {
		if ((dev = cd->cd_dev[ix]) == NODEV)
			break;
		ci = &cs->sc_cinfo[ix];
		ci->ci_dev = dev;
I 6
		bsw = &bdevsw[major(dev)];
E 6
		/*
I 6
		 * Open the partition
		 */
D 7
		if (bsw->d_open && (error = (*bsw->d_open)(dev, 0, S_IFBLK))) {
E 7
I 7
		if (bsw->d_open &&
		    (error = (*bsw->d_open)(dev, 0, S_IFBLK, p))) {
E 7
			printf("cd%d: component %s open failed, error = %d\n",
			       cd->cd_unit, cddevtostr(dev), error);
			return(0);
		}
		/*
E 6
		 * Calculate size (truncated to interleave boundary
		 * if necessary.
		 */
D 6
		if (bdevsw[major(dev)].d_psize) {
D 4
			size = (*bdevsw[major(dev)].d_psize)(dev);
			if (size <= 0)
E 4
I 4
			size = (size_t) (*bdevsw[major(dev)].d_psize)(dev);
E 6
I 6
		if (bsw->d_psize) {
			size = (size_t) (*bsw->d_psize)(dev);
E 6
			if ((int)size < 0)
E 4
				size = 0;
		} else
			size = 0;
		if (cs->sc_ileave > 1)
			size -= size % cs->sc_ileave;
D 4
		if (size == 0)
E 4
I 4
		if (size == 0) {
			printf("cd%d: not configured (component %s missing)\n",
D 6
			       cd->cd_unit, cddevtostr(ci->ci_dev));
E 6
I 6
			       cd->cd_unit, cddevtostr(dev));
E 6
E 4
			return(0);
I 4
		}
I 6
#ifdef COMPAT_NOLABEL
		/*
		 * XXX if this is a 'c' partition then we need to mark the
		 * label area writeable since there cannot be a label.
		 */
		if ((minor(dev) & 7) == 2 && bsw->d_open) {
			int i, flag;

			for (i = 0; i < nchrdev; i++)
				if (cdevsw[i].d_open == bsw->d_open)
					break;
			if (i != nchrdev && cdevsw[i].d_ioctl) {
				flag = 1;
				(void)(*cdevsw[i].d_ioctl)(dev, DIOCWLABEL,
D 7
							   &flag, FWRITE);
E 7
I 7
					(caddr_t)&flag, FWRITE, p);
E 7
			}
		}
#endif
E 6
E 4
		if (minsize == 0 || size < minsize)
			minsize = size;
		ci->ci_size = size;
		cs->sc_size += size;
		cs->sc_ncdisks++;
	}
	/*
	 * If uniform interleave is desired set all sizes to that of
	 * the smallest component.
	 */
	if (cd->cd_flags & CDF_UNIFORM) {
		for (ci = cs->sc_cinfo;
		     ci < &cs->sc_cinfo[cs->sc_ncdisks]; ci++)
			ci->ci_size = minsize;
		cs->sc_size = cs->sc_ncdisks * minsize;
	}
	/*
	 * Construct the interleave table
	 */
	if (!cdinterleave(cs))
		return(0);
	if (cd->cd_dk >= 0)
		dk_wpms[cd->cd_dk] = 32 * (60 * DEV_BSIZE / 2);	/* XXX */
D 4
	printf("cd%d: %d components (%d blocks) concatenated",
	       cd->cd_unit, cs->sc_ncdisks, cs->sc_size);
E 4
I 4
	printf("cd%d: %d components ", cd->cd_unit, cs->sc_ncdisks);
	for (ix = 0; ix < cs->sc_ncdisks; ix++)
		printf("%c%s%c",
		       ix == 0 ? '(' : ' ',
		       cddevtostr(cs->sc_cinfo[ix].ci_dev),
		       ix == cs->sc_ncdisks - 1 ? ')' : ',');
	printf(", %d blocks ", cs->sc_size);
E 4
	if (cs->sc_ileave)
D 4
		printf(", %d block interleave\n", cs->sc_ileave);
E 4
I 4
		printf("interleaved at %d blocks\n", cs->sc_ileave);
E 4
	else
D 4
		printf(" serially\n");
E 4
I 4
		printf("concatenated\n");
E 4
	cs->sc_flags = CDF_ALIVE | CDF_INITED;
	return(1);
I 4
}

/*
 * XXX not really cd specific.
I 7
 * Could be called something like bdevtostr in machine/conf.c.
E 7
 */
char *
cddevtostr(dev)
	dev_t dev;
{
	static char dbuf[5];

D 7
	dbuf[1] = 'd';
E 7
	switch (major(dev)) {
I 7
#ifdef hp300
E 7
	case 2:
D 7
		dbuf[0] = 'r';
E 7
I 7
		dbuf[0] = 'r'; dbuf[1] = 'd';
E 7
		break;
	case 4:
D 7
		dbuf[0] = 's';
E 7
I 7
		dbuf[0] = 's'; dbuf[1] = 'd';
E 7
		break;
	case 5:
D 7
		dbuf[0] = 'c';
E 7
I 7
		dbuf[0] = 'c'; dbuf[1] = 'd';
E 7
		break;
I 7
	case 6:
		dbuf[0] = 'v'; dbuf[1] = 'n';
		break;
#endif
E 7
	default:
		dbuf[0] = dbuf[1] = '?';
		break;
	}
	dbuf[2] = (minor(dev) >> 3) + '0';
	dbuf[3] = (minor(dev) & 7) + 'a';
	dbuf[4] = '\0';
	return (dbuf);
E 4
}

cdinterleave(cs)
	register struct cd_softc *cs;
{
	register struct cdcinfo *ci, *smallci;
	register struct cdiinfo *ii;
	register daddr_t bn, lbn;
	register int ix;
	u_long size;

#ifdef DEBUG
	if (cddebug & CDB_INIT)
		printf("cdinterleave(%x): ileave %d\n", cs, cs->sc_ileave);
#endif
	/*
	 * Allocate an interleave table.
	 * Chances are this is too big, but we don't care.
	 */
	size = (cs->sc_ncdisks + 1) * sizeof(struct cdiinfo);
	cs->sc_itable = (struct cdiinfo *)malloc(size, M_DEVBUF, M_WAITOK);
	bzero((caddr_t)cs->sc_itable, size);
	/*
	 * Trivial case: no interleave (actually interleave of disk size).
	 * Each table entry represent a single component in its entirety.
	 */
	if (cs->sc_ileave == 0) {
		bn = 0;
		ii = cs->sc_itable;
		for (ix = 0; ix < cs->sc_ncdisks; ix++) {
			ii->ii_ndisk = 1;
			ii->ii_startblk = bn;
			ii->ii_startoff = 0;
			ii->ii_index[0] = ix;
			bn += cs->sc_cinfo[ix].ci_size;
			ii++;
		}
		ii->ii_ndisk = 0;
#ifdef DEBUG
		if (cddebug & CDB_INIT)
			printiinfo(cs->sc_itable);
#endif
		return(1);
	}
	/*
	 * The following isn't fast or pretty; it doesn't have to be.
	 */
	size = 0;
	bn = lbn = 0;
	for (ii = cs->sc_itable; ; ii++) {
		/*
		 * Locate the smallest of the remaining components
		 */
		smallci = NULL;
		for (ci = cs->sc_cinfo;
		     ci < &cs->sc_cinfo[cs->sc_ncdisks]; ci++)
			if (ci->ci_size > size &&
			    (smallci == NULL ||
			     ci->ci_size < smallci->ci_size))
				smallci = ci;
		/*
		 * Nobody left, all done
		 */
		if (smallci == NULL) {
			ii->ii_ndisk = 0;
			break;
		}
		/*
		 * Record starting logical block and component offset
		 */
		ii->ii_startblk = bn / cs->sc_ileave;
		ii->ii_startoff = lbn;
		/*
		 * Determine how many disks take part in this interleave
		 * and record their indices.
		 */
		ix = 0;
		for (ci = cs->sc_cinfo;
		     ci < &cs->sc_cinfo[cs->sc_ncdisks]; ci++)
			if (ci->ci_size >= smallci->ci_size)
				ii->ii_index[ix++] = ci - cs->sc_cinfo;
		ii->ii_ndisk = ix;
		bn += ix * (smallci->ci_size - size);
		lbn = smallci->ci_size / cs->sc_ileave;
		size = smallci->ci_size;
	}
#ifdef DEBUG
	if (cddebug & CDB_INIT)
		printiinfo(cs->sc_itable);
#endif
	return(1);
}

#ifdef DEBUG
printiinfo(ii)
	struct cdiinfo *ii;
{
	register int ix, i;

	for (ix = 0; ii->ii_ndisk; ix++, ii++) {
		printf(" itab[%d]: #dk %d sblk %d soff %d",
		       ix, ii->ii_ndisk, ii->ii_startblk, ii->ii_startoff);
		for (i = 0; i < ii->ii_ndisk; i++)
			printf(" %d", ii->ii_index[i]);
		printf("\n");
	}
}
#endif

cdopen(dev, flags)
	dev_t dev;
{
	int unit = cdunit(dev);
	register struct cd_softc *cs = &cd_softc[unit];

#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
		printf("cdopen(%x, %x)\n", dev, flags);
#endif
D 7
	if (unit >= NCD || (cs->sc_flags & CDF_ALIVE) == 0)
E 7
I 7
	if (unit >= numcd || (cs->sc_flags & CDF_ALIVE) == 0)
E 7
		return(ENXIO);
	return(0);
}

I 10
void
E 10
cdstrategy(bp)
	register struct buf *bp;
{
	register int unit = cdunit(bp->b_dev);
	register struct cd_softc *cs = &cd_softc[unit];
D 2
	register int bn, sz;
	int s;
E 2
I 2
	register daddr_t bn;
	register int sz, s;
E 2

#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
		printf("cdstrategy(%x): unit %d\n", bp, unit);
#endif
	if ((cs->sc_flags & CDF_INITED) == 0) {
		bp->b_error = ENXIO;
D 2
		goto bad;
E 2
I 2
		bp->b_flags |= B_ERROR;
		goto done;
E 2
	}
	bn = bp->b_blkno;
D 2
	sz = (bp->b_bcount + (DEV_BSIZE - 1)) >> DEV_BSHIFT;
	bp->b_resid = bp->b_bcount;
E 2
I 2
	sz = howmany(bp->b_bcount, DEV_BSIZE);
E 2
	if (bn < 0 || bn + sz > cs->sc_size) {
D 2
		if (bn == cs->sc_size)
E 2
I 2
		sz = cs->sc_size - bn;
		if (sz == 0) {
			bp->b_resid = bp->b_bcount;
E 2
			goto done;
D 2
		bp->b_error = EINVAL;
		goto bad;
E 2
I 2
		}
		if (sz < 0) {
			bp->b_error = EINVAL;
			bp->b_flags |= B_ERROR;
			goto done;
		}
		bp->b_bcount = dbtob(sz);
E 2
	}
I 2
	bp->b_resid = bp->b_bcount;
E 2
	/*
	 * "Start" the unit.
D 7
	 * XXX: the use of sc_bp is just to retain the "traditional"
	 * interface to the start routine.
E 7
	 */
	s = splbio();
D 7
	cs->sc_bp = bp;
	cdstart(unit);
E 7
I 7
	cdstart(cs, bp);
E 7
	splx(s);
	return;
D 2
bad:
	bp->b_flags |= B_ERROR;
E 2
done:
D 2
	iodone(bp);
E 2
I 2
	biodone(bp);
E 2
}

D 7
cdstart(unit)
	int unit;
E 7
I 7
cdstart(cs, bp)
	register struct cd_softc *cs;
	register struct buf *bp;
E 7
{
D 7
	register struct cd_softc *cs = &cd_softc[unit];
	register struct buf *bp = cs->sc_bp;
E 7
	register long bcount, rcount;
	struct buf *cbp;
	caddr_t addr;
	daddr_t bn;

#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
D 7
		printf("cdstart(%d)\n", unit);
E 7
I 7
		printf("cdstart(%x, %x)\n", cs, bp);
E 7
#endif
	/*
	 * Instumentation (not real meaningful)
	 */
	cs->sc_usecnt++;
	if (cs->sc_dk >= 0) {
		dk_busy |= 1 << cs->sc_dk;
		dk_xfer[cs->sc_dk]++;
		dk_wds[cs->sc_dk] += bp->b_bcount >> 6;
	}
	/*
	 * Allocate component buffers and fire off the requests
	 */
	bn = bp->b_blkno;
D 9
	addr = bp->b_un.b_addr;
E 9
I 9
	addr = bp->b_data;
E 9
	for (bcount = bp->b_bcount; bcount > 0; bcount -= rcount) {
		cbp = cdbuffer(cs, bp, bn, addr, bcount);
		rcount = cbp->b_bcount;
		(*bdevsw[major(cbp->b_dev)].d_strategy)(cbp);
		bn += btodb(rcount);
		addr += rcount;
	}
}

/*
 * Build a component buffer header.
 */
struct buf *
cdbuffer(cs, bp, bn, addr, bcount)
	register struct cd_softc *cs;
	struct buf *bp;
	daddr_t bn;
	caddr_t addr;
	long bcount;
{
	register struct cdcinfo *ci;
	register struct buf *cbp;
	register daddr_t cbn, cboff;

#ifdef DEBUG
	if (cddebug & CDB_IO)
		printf("cdbuffer(%x, %x, %d, %x, %d)\n",
		       cs, bp, bn, addr, bcount);
#endif
	/*
	 * Determine which component bn falls in.
	 */
	cbn = bn;
	cboff = 0;
	/*
	 * Serially concatenated
	 */
	if (cs->sc_ileave == 0) {
		register daddr_t sblk;

		sblk = 0;
		for (ci = cs->sc_cinfo; cbn >= sblk + ci->ci_size; ci++)
			sblk += ci->ci_size;
		cbn -= sblk;
	}
	/*
	 * Interleaved
	 */
	else {
		register struct cdiinfo *ii;
		int cdisk, off;

		cboff = cbn % cs->sc_ileave;
		cbn /= cs->sc_ileave;
		for (ii = cs->sc_itable; ii->ii_ndisk; ii++)
			if (ii->ii_startblk > cbn)
				break;
		ii--;
		off = cbn - ii->ii_startblk;
		if (ii->ii_ndisk == 1) {
			cdisk = ii->ii_index[0];
			cbn = ii->ii_startoff + off;
		} else {
			cdisk = ii->ii_index[off % ii->ii_ndisk];
			cbn = ii->ii_startoff + off / ii->ii_ndisk;
		}
		cbn *= cs->sc_ileave;
		ci = &cs->sc_cinfo[cdisk];
	}
	/*
	 * Fill in the component buf structure.
	 */
	cbp = getcbuf();
	cbp->b_flags = bp->b_flags | B_CALL;
	cbp->b_iodone = cdiodone;
	cbp->b_proc = bp->b_proc;
	cbp->b_dev = ci->ci_dev;
	cbp->b_blkno = cbn + cboff;
D 9
	cbp->b_un.b_addr = addr;
E 9
I 9
	cbp->b_data = addr;
E 9
I 2
	cbp->b_vp = 0;
E 2
	if (cs->sc_ileave == 0)
		cbp->b_bcount = dbtob(ci->ci_size - cbn);
	else
		cbp->b_bcount = dbtob(cs->sc_ileave - cboff);
	if (cbp->b_bcount > bcount)
		cbp->b_bcount = bcount;
	/*
D 7
	 * XXX: context for cdiodone
E 7
I 7
	 * XXX context for cdiodone
E 7
	 */
D 2
	cbp->b_vp = (struct vnode *)bp;
E 2
I 2
	cbp->b_saveaddr = (caddr_t)bp;
E 2
	cbp->b_pfcent = ((cs - cd_softc) << 16) | (ci - cs->sc_cinfo);
#ifdef DEBUG
	if (cddebug & CDB_IO)
		printf(" dev %x(u%d): cbp %x bn %d addr %x bcnt %d\n",
		       ci->ci_dev, ci-cs->sc_cinfo, cbp, cbp->b_blkno,
D 9
		       cbp->b_un.b_addr, cbp->b_bcount);
E 9
I 9
		       cbp->b_data, cbp->b_bcount);
E 9
#endif
	return(cbp);
}

D 7
cdintr(unit)
	int unit;
E 7
I 7
cdintr(cs, bp)
	register struct cd_softc *cs;
	register struct buf *bp;
E 7
{
D 7
	register struct cd_softc *cs = &cd_softc[unit];
	register struct buf *bp = cs->sc_bp;
E 7

#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
D 2
		printf("cdintr(%d)\n", unit);
E 2
I 2
D 7
		printf("cdintr(%d): bp %x\n", unit, bp);
E 7
I 7
		printf("cdintr(%x, %x)\n", cs, bp);
E 7
E 2
#endif
	/*
	 * Request is done for better or worse, wakeup the top half.
	 */
	if (--cs->sc_usecnt == 0 && cs->sc_dk >= 0)
		dk_busy &= ~(1 << cs->sc_dk);
	if (bp->b_flags & B_ERROR)
		bp->b_resid = bp->b_bcount;
D 2
	iodone(bp);
E 2
I 2
	biodone(bp);
E 2
}

/*
D 2
 * Called by iodone at interrupt time.
E 2
I 2
 * Called by biodone at interrupt time.
E 2
 * Mark the component as done and if all components are done,
 * take a cd interrupt.
 */
I 7
void
E 7
cdiodone(cbp)
	register struct buf *cbp;
{
D 2
	register struct buf *bp = (struct buf *)cbp->b_vp;	/* XXX */
E 2
I 2
	register struct buf *bp = (struct buf *)cbp->b_saveaddr;/* XXX */
E 2
	register int unit = (cbp->b_pfcent >> 16) & 0xFFFF;	/* XXX */
	int count, s;

	s = splbio();
#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
		printf("cdiodone(%x)\n", cbp);
	if (cddebug & CDB_IO) {
		printf("cdiodone: bp %x bcount %d resid %d\n",
		       bp, bp->b_bcount, bp->b_resid);
		printf(" dev %x(u%d), cbp %x bn %d addr %x bcnt %d\n",
		       cbp->b_dev, cbp->b_pfcent & 0xFFFF, cbp,
D 9
		       cbp->b_blkno, cbp->b_un.b_addr, cbp->b_bcount);
E 9
I 9
		       cbp->b_blkno, cbp->b_data, cbp->b_bcount);
E 9
	}
#endif

	if (cbp->b_flags & B_ERROR) {
		bp->b_flags |= B_ERROR;
D 2
		bp->b_error = geterror(cbp);
E 2
I 2
		bp->b_error = biowait(cbp);
E 2
#ifdef DEBUG
		printf("cd%d: error %d on component %d\n",
		       unit, bp->b_error, cbp->b_pfcent & 0xFFFF);
#endif
	}
	count = cbp->b_bcount;
	putcbuf(cbp);

	/*
	 * If all done, "interrupt".
D 7
	 * Again, sc_bp is only used to preserve the traditional interface.
E 7
	 */
	bp->b_resid -= count;
	if (bp->b_resid < 0)
		panic("cdiodone: count");
D 7
	if (bp->b_resid == 0) {
		cd_softc[unit].sc_bp = bp;
		cdintr(unit);
	}
E 7
I 7
	if (bp->b_resid == 0)
		cdintr(&cd_softc[unit], bp);
E 7
	splx(s);
}

cdread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register int unit = cdunit(dev);

#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
		printf("cdread(%x, %x)\n", dev, uio);
#endif
D 7
	return(physio(cdstrategy, &cdbuf[unit], dev, B_READ, minphys, uio));
E 7
I 7
	return(physio(cdstrategy, NULL, dev, B_READ, minphys, uio));
E 7
}

cdwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register int unit = cdunit(dev);

#ifdef DEBUG
	if (cddebug & CDB_FOLLOW)
		printf("cdwrite(%x, %x)\n", dev, uio);
#endif
D 7
	return(physio(cdstrategy, &cdbuf[unit], dev, B_WRITE, minphys, uio));
E 7
I 7
	return(physio(cdstrategy, NULL, dev, B_WRITE, minphys, uio));
E 7
}

cdioctl(dev, cmd, data, flag)
	dev_t dev;
D 10
	int cmd;
E 10
I 10
	u_long cmd;
E 10
	caddr_t data;
	int flag;
{
	return(EINVAL);
}

cdsize(dev)
	dev_t dev;
{
	int unit = cdunit(dev);
	register struct cd_softc *cs = &cd_softc[unit];

D 7
	if (unit >= NCD || (cs->sc_flags & CDF_INITED) == 0)
E 7
I 7
	if (unit >= numcd || (cs->sc_flags & CDF_INITED) == 0)
E 7
		return(-1);
	return(cs->sc_size);
}

cddump(dev)
{
	return(ENXIO);
}
#endif
E 1
