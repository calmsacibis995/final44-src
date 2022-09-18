h55151
s 00002/00002/00881
d D 8.1 93/06/10 21:20:55 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00004/00880
d D 5.7 93/04/28 18:23:45 torek 7 6
c suser() sense changed way back when, but we forgot to fix it here
e
s 00011/00001/00873
d D 5.6 93/04/26 22:00:19 torek 6 5
c add DIOCGDINFO, DIOCGPART
e
s 00001/00001/00873
d D 5.5 93/02/01 11:26:32 torek 5 4
c rcsid
e
s 00048/00042/00826
d D 5.4 92/11/18 20:39:00 torek 4 3
c dk_wpms => dk_bps; turn on sddkdriver (for other sparc code);
c copy LUN into format ops; temp buffer in sd_lblkstrat must be malloc'd;
c make kernel includes standard
e
s 00025/00018/00843
d D 5.3 92/07/23 14:00:52 torek 3 2
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00002/00001/00859
d D 5.2 92/07/13 09:14:28 pendry 2 1
c MIN -> min
e
s 00860/00000/00000
d D 5.1 92/07/10 00:03:08 torek 1 0
c date and time created 92/07/10 00:03:08 by torek
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1990, 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 3
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 4
 *	California, Lawrence Berkeley Laboratories.
E 4
I 4
 *	California, Lawrence Berkeley Laboratory.
E 4
 *
E 3
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 4
 * from: $Header: sd.c,v 1.18 92/06/11 17:55:56 torek Exp $
E 4
I 4
D 5
 * from: $Header: sd.c,v 1.24 92/11/19 04:37:33 torek Exp $
E 5
I 5
D 6
 * from: $Header: sd.c,v 1.25 93/02/01 19:26:27 torek Exp $
E 6
I 6
D 7
 * from: $Header: sd.c,v 1.26 93/04/20 02:52:59 leres Exp $
E 7
I 7
 * from: $Header: sd.c,v 1.27 93/04/29 01:22:19 torek Exp $
E 7
E 6
E 5
E 4
 */

/*
 * SCSI CCS (Command Command Set) disk driver.
 *
 * MACHINE INDEPENDENT (do not put machine dependent goo in here!)
 *
 * (from sd.c,v 1.7 90/12/15 14:11:26 van Exp)
 */

D 3
#include "sys/param.h"
I 2
#include "sys/systm.h"
E 2
#include "sys/proc.h"
#include "sys/buf.h"
#include "sys/errno.h"
#include "sys/device.h"
#include "sys/disklabel.h"
#include "sys/dkstat.h"
#include "sys/disk.h"
#include "sys/ioctl.h"
#include "sys/malloc.h"
E 3
I 3
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/device.h>
#include <sys/disklabel.h>
#include <sys/dkstat.h>
#include <sys/disk.h>
#include <sys/ioctl.h>
#include <sys/malloc.h>
E 3

I 4
#include <dev/scsi/scsi.h>
#include <dev/scsi/disk.h>
#include <dev/scsi/scsivar.h>
#include <dev/scsi/scsi_ioctl.h>

E 4
D 3
#include "scsi/scsi.h"
#include "scsi/disk.h"
#include "scsi/scsivar.h"
#include "scsi/scsi_ioctl.h"
E 3
I 3
#include <machine/cpu.h>
E 3

D 3
#include "machine/cpu.h"
E 3
I 3
D 4
#include "scsi.h"
#include "disk.h"
#include "scsivar.h"
#include "scsi_ioctl.h"
E 4
I 4
#include <dev/scsi/sdtrace.h>
E 4
E 3

D 4
#include "sdtrace.h"

E 4
D 3
#define SUN_LABEL_HACK
E 3
I 3
#ifdef sparc					/* XXX */
#define SUN_LABEL_HACK				/* XXX */
#endif						/* XXX */
E 3

#ifdef SUN_LABEL_HACK
D 3
#include "sparc/sunos/sun_disklabel.h"
E 3
I 3
#include <sparc/sunos/sun_disklabel.h>
E 3
#endif

/*
 * Per-disk variables.
 *
 * sd_dk contains all the `disk' specific stuff (label/partitions,
 * transfer rate, etc).  We need only things that are special to
 * scsi disks.  Note that our blocks are in terms of DEV_BSIZE blocks.
 */
struct sd_softc {
	struct	dkdevice sc_dk;	/* base disk device, must be first */
	struct	unit sc_unit;	/* scsi unit */
	pid_t	sc_format_pid;	/* process using "format" mode */
	u_char	sc_type;	/* drive type */
	u_char	sc_bshift;	/* convert device blocks to DEV_BSIZE blks */
	short	sc_flags;	/* see below */
	u_int	sc_blks;	/* number of blocks on device */
	int	sc_blksize;	/* device block size in bytes */

	/* should be in dkdevice?? */
	struct	buf sc_tab;	/* transfer queue */

	/* statistics */
	long	sc_resets;	/* number of times reset */
	long	sc_transfers;	/* count of total transfers */
	long	sc_partials;	/* count of `partial' transfers */

	/* for user formatting */
	struct	scsi_cdb sc_cmd;
	struct	scsi_fmt_sense sc_sense;
};

#define	SDF_ALIVE	1	/* drive OK for regular kernel use */

/* definition of the autoconfig driver */
int	sdmatch __P((struct device *, struct cfdata *, void *));
void	sdattach __P((struct device *, struct device *, void *));

struct cfdriver sdcd =
    { NULL, "sd", sdmatch, sdattach, DV_DISK, sizeof(struct sd_softc) };

/* definition of the unit driver, for hba */
void	sdigo __P((struct device *, struct scsi_cdb *));
void	sdgo __P((struct device *, struct scsi_cdb *));
void	sdintr __P((struct device *, int, int));
void	sdreset __P((struct unit *));

static struct unitdriver sdunitdriver = { /*sdgo, sdintr*/ sdreset };

/* definition of the disk driver, for kernel */
void	sdstrategy __P((struct buf *));

D 4
#ifdef notyet
static struct sddkdriver = { sdstrategy };
#endif
E 4
I 4
static struct dkdriver sddkdriver = { sdstrategy };
E 4

#ifdef DEBUG
int sddebug = 1;
#define SDB_ERROR	0x01
#define SDB_PARTIAL	0x02
#endif

#define	sdunit(x)	(minor(x) >> 3)
#define sdpart(x)	(minor(x) & 0x7)

#define	b_cylin		b_resid

#define	SDRETRY		2

/*
 * Table of scsi commands users are allowed to access via `format'
 * mode.  0 means not legal.  1 means `immediate' (doesn't need dma).
 * -1 means needs dma and/or wait for intr (i.e., `slow').
 */
static char legal_cmds[256] = {
/*****  0   1   2   3   4   5   6   7     8   9   A   B   C   D   E   F */
/*00*/	0,  0,  0,  0, -1,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*10*/	0,  0,  1,  0,  0,  1,  0,  0,    0,  0,  1,  0,  0,  0,  0,  0,
/*20*/	0,  0,  0,  0,  0,  1,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*30*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*40*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*50*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*60*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*70*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*80*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*90*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*a0*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*b0*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*c0*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*d0*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*e0*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
/*f0*/	0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
};

int
sdmatch(parent, cf, aux)
	struct device *parent;
	register struct cfdata *cf;
	void *aux;
{
	register struct scsi_attach_args *sa = aux;
#ifdef DEBUG
	char *whynot;
#endif

	/*
	 * unit number must match, or be given as `any'
	 */
	if (cf->cf_loc[0] != -1 && cf->cf_loc[0] != sa->sa_unit)
		return (0);
	/*
	 * drive must be a disk, and of a kind we recognize
	 */
	if ((sa->sa_inq_status & STS_MASK) != STS_GOOD) {
#ifdef DEBUG
		whynot = "INQUIRY failed";
#endif
		goto notdisk;
	}

	switch (sa->sa_si.si_type & TYPE_TYPE_MASK) {

	case TYPE_DAD:		/* disk */
	case TYPE_WORM:		/* WORM */
	case TYPE_ROM:		/* CD-ROM */
	case TYPE_MO:		/* Magneto-optical */
	case TYPE_JUKEBOX:	/* medium changer */
		break;

	default:
	notdisk:
#ifdef DEBUG
		whynot = "not a disk";
		printf("[not matching `sd' at unit %d: %s]\n",
		    sa->sa_unit, whynot);
#endif
		return (0);
	}

	/*
	 * It is a disk of some kind; take it.  We will figure out
	 * the rest in the attach routine.
	 */
	return (1);
}

/*
 * Attach a disk (called after sdmatch returns true).
 * Note that this routine is never reentered (so we can use statics).
 */
void
sdattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	register struct sd_softc *sc = (struct sd_softc *)self;
	register struct scsi_attach_args *sa = aux;
	register int i;
	char vendor[10], drive[17], rev[5];
	static u_char capbuf[8];
	static struct scsi_cdb cap = { CMD_READ_CAPACITY };
#ifdef SUN_LABEL_HACK
	static struct scsi_cdb rd0 = { CMD_READ10, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
	caddr_t sector;
#endif

	/*
	 * Declare our existence.
	 */
	sc->sc_unit.u_driver = &sdunitdriver;
	scsi_establish(&sc->sc_unit, &sc->sc_dk.dk_dev, sa->sa_unit);

	/*
	 * Figure out what kind of disk this is.
	 * We only accepted it if the inquiry succeeded, so
	 * we can inspect those fields.
	 */
	i = (sa->sa_si.si_version >> VER_ANSI_SHIFT) & VER_ANSI_MASK;
	if (i == 1 || i == 2) {
		scsi_inq_ansi((struct scsi_inq_ansi *)&sa->sa_si,
		    vendor, drive, rev);
		printf(": %s %s", vendor, drive);
		/* XXX should we even ever bother printing this? */
		if (rev[0])
			printf(" %s", rev);
	} else {
		/* bleah */
		bcopy("<unknown>", vendor, 10);
		bcopy("<unknown>", drive, 10);
		printf(": type 0x%x, qual 0x%x, ver %d",
		    sa->sa_si.si_type, sa->sa_si.si_qual,
		    sa->sa_si.si_version);
	}

D 4
#ifdef notyet
	sc->sc_dk.dk_driver = &sddkdriver;
	dk_establish(&sc->sc_dk);
	/* READ DISK LABEL HERE, UNLESS REMOVABLE MEDIUM... NEEDS THOUGHT */
#endif

E 4
	CDB10(&cap)->cdb_lun_rel = sc->sc_unit.u_unit << 5;
	i = (*sc->sc_unit.u_hbd->hd_icmd)(sc->sc_unit.u_hba,
	    sc->sc_unit.u_targ, &cap, (char *)capbuf, sizeof capbuf, B_READ);
	i &= STS_MASK;
	if (i == STS_GOOD) {
#define	NUMBER(p) (((p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | (p)[3])
		sc->sc_blks = NUMBER(&capbuf[0]);
		sc->sc_blksize = NUMBER(&capbuf[4]);
	} else if (i == STS_CHECKCOND &&
	    (strcmp(vendor, "HP") == 0 && strcmp(drive, "S6300.650A") == 0)) {
		/* XXX unformatted or nonexistent MO medium: fake it */
		sc->sc_blks = 318664;
		sc->sc_blksize = 1024;
	} else {
I 4
		/* XXX shouldn't bail for removable media */
E 4
		printf(": unable to determine drive capacity [sts=%x]\n", i);
		return;
	}
	/* return value from read capacity is last valid block, not nblocks */
	sc->sc_blks++;
	printf(", %u %d byte blocks\n", sc->sc_blks, sc->sc_blksize);
	if (sc->sc_blksize != DEV_BSIZE) {
		for (i = sc->sc_blksize; i > DEV_BSIZE; i >>= 1)
			++sc->sc_bshift;
		if (i != DEV_BSIZE) {
			printf("%s: blksize not multiple of %d: cannot use\n",
			    sc->sc_dk.dk_dev.dv_xname, DEV_BSIZE);
			return;
		}
		sc->sc_blks <<= sc->sc_bshift;
	}
	sc->sc_type = sa->sa_si.si_type;	/* sufficient? */
D 4
	sc->sc_dk.dk_wpms = 32 * (60 * DEV_BSIZE / 2);	/* XXX */
E 4

I 4
	sc->sc_dk.dk_driver = &sddkdriver;
#ifdef notyet
	dk_establish(&sc->sc_dk);
	/* READ DISK LABEL HERE, UNLESS REMOVABLE MEDIUM... NEEDS THOUGHT */
#else
E 4
	sc->sc_dk.dk_label.d_secsize = 512;	/* XXX */
I 4
	sc->sc_dk.dk_bps = (3600/60) * 32 * 512;/* XXX */
E 4

#ifdef SUN_LABEL_HACK
	sector = (caddr_t)malloc(sc->sc_blksize, M_DEVBUF, M_NOWAIT);
	CDB10(&rd0)->cdb_lun_rel = sc->sc_unit.u_unit << 5;
	i = (*sc->sc_unit.u_hbd->hd_icmd)(sc->sc_unit.u_hba,
	    sc->sc_unit.u_targ, &rd0, sector, sc->sc_blksize, B_READ);
	if (i == STS_GOOD) {
		printf("%s: <%s>\n", sc->sc_dk.dk_dev.dv_xname,
		    ((struct sun_disklabel *)sector)->sl_text);
		if (sun_disklabel(sector, &sc->sc_dk.dk_label))
			sc->sc_flags |= SDF_ALIVE;
		else
			printf("%s: sun_disklabel fails\n",
			    sc->sc_dk.dk_dev.dv_xname);
	} else
		printf("%s: could not read sector 0 for disk label\n",
		    sc->sc_dk.dk_dev.dv_xname);
	free(sector, M_DEVBUF);
#endif
I 4
#endif /* notyet */
E 4
}

/*
 * Reset a disk, after a SCSI bus reset.
 *
 * XXX untested and probably incomplete/incorrect
 */
void
sdreset(u)
	register struct unit *u;
{
	register struct sd_softc *sc = (struct sd_softc *)u->u_dev;

	printf(" %s", sc->sc_dk.dk_dev.dv_xname);
	sc->sc_resets++;
}

/* dev_t is short, must use prototype syntax */
int
sdopen(dev_t dev, int flags, int ifmt, struct proc *p)
{
	register int unit = sdunit(dev);
	register struct sd_softc *sc;

	if (unit >= sdcd.cd_ndevs || (sc = sdcd.cd_devs[unit]) == NULL)
		return (ENXIO);
D 7
	if ((sc->sc_flags & SDF_ALIVE) == 0 &&
	    !suser(p->p_ucred, &p->p_acflag))
E 7
I 7
	if ((sc->sc_flags & SDF_ALIVE) == 0 && suser(p->p_ucred, &p->p_acflag))
E 7
		return (ENXIO);
	return (0);
}

int
sdclose(dev_t dev, int flags, int ifmt, struct proc *p)
{
	register struct sd_softc *sc = sdcd.cd_devs[sdunit(dev)];

	sc->sc_format_pid = 0;
	return (0);
}

/*
 * This routine is called for partial block transfers and non-aligned
 * transfers (the latter only being possible on devices with a block size
 * larger than DEV_BSIZE).  The operation is performed in three steps
 * using a locally allocated buffer:
 *	1. transfer any initial partial block
 *	2. transfer full blocks
 *	3. transfer any final partial block
 */
static void
sdlblkstrat(bp, bsize)
	register struct buf *bp;
	register int bsize;
{
	register int bn, resid, boff, count;
	register caddr_t addr, cbuf;
D 4
	struct buf tbp;
E 4
I 4
	struct buf *tbp;
E 4

I 4
	/* should probably use geteblk() here, but I fear consequences */
E 4
	cbuf = (caddr_t)malloc(bsize, M_DEVBUF, M_WAITOK);
D 4
	bzero((caddr_t)&tbp, sizeof tbp);
	tbp.b_proc = curproc;
	tbp.b_dev = bp->b_dev;
E 4
I 4
	tbp = (struct buf *)malloc(sizeof *tbp, M_DEVBUF, M_WAITOK);
	bzero((caddr_t)tbp, sizeof *tbp);
	tbp->b_proc = curproc;
	tbp->b_dev = bp->b_dev;
E 4
	bn = bp->b_blkno;
	resid = bp->b_bcount;
	addr = bp->b_un.b_addr;
#ifdef DEBUG
	if (sddebug & SDB_PARTIAL)
		printf("sdlblkstrat: bp %x flags %x bn %x resid %x addr %x\n",
		       bp, bp->b_flags, bn, resid, addr);
#endif

	while (resid > 0) {
		boff = dbtob(bn) & (bsize - 1);
		if (boff || resid < bsize) {
			struct sd_softc *sc = sdcd.cd_devs[sdunit(bp->b_dev)];
			sc->sc_partials++;
D 2
			count = MIN(resid, bsize - boff);
E 2
I 2
			count = min(resid, bsize - boff);
E 2
D 4
			tbp.b_flags = B_BUSY | B_READ;
			tbp.b_blkno = bn - btodb(boff);
			tbp.b_un.b_addr = cbuf;
			tbp.b_bcount = bsize;
E 4
I 4
			tbp->b_flags = B_BUSY | B_READ;
			tbp->b_blkno = bn - btodb(boff);
			tbp->b_un.b_addr = cbuf;
			tbp->b_bcount = bsize;
E 4
#ifdef DEBUG
			if (sddebug & SDB_PARTIAL)
				printf(" readahead: bn %x cnt %x off %x addr %x\n",
D 4
				       tbp.b_blkno, count, boff, addr);
E 4
I 4
				       tbp->b_blkno, count, boff, addr);
E 4
#endif
D 4
			sdstrategy(&tbp);
			biowait(&tbp);
			if (tbp.b_flags & B_ERROR) {
E 4
I 4
			sdstrategy(tbp);
			biowait(tbp);
			if (tbp->b_flags & B_ERROR) {
E 4
				bp->b_flags |= B_ERROR;
D 4
				bp->b_error = tbp.b_error;
E 4
I 4
				bp->b_error = tbp->b_error;
E 4
				break;
			}
			if (bp->b_flags & B_READ) {
				bcopy(&cbuf[boff], addr, count);
				goto done;
			}
			bcopy(addr, &cbuf[boff], count);
#ifdef DEBUG
			if (sddebug & SDB_PARTIAL)
				printf(" writeback: bn %x cnt %x off %x addr %x\n",
D 4
				       tbp.b_blkno, count, boff, addr);
E 4
I 4
				       tbp->b_blkno, count, boff, addr);
E 4
#endif
		} else {
			count = resid & ~(bsize - 1);
D 4
			tbp.b_blkno = bn;
			tbp.b_un.b_addr = addr;
			tbp.b_bcount = count;
E 4
I 4
			tbp->b_blkno = bn;
			tbp->b_un.b_addr = addr;
			tbp->b_bcount = count;
E 4
#ifdef DEBUG
			if (sddebug & SDB_PARTIAL)
				printf(" fulltrans: bn %x cnt %x addr %x\n",
D 4
				       tbp.b_blkno, count, addr);
E 4
I 4
				       tbp->b_blkno, count, addr);
E 4
#endif
		}
D 4
		tbp.b_flags = B_BUSY | (bp->b_flags & B_READ);
		sdstrategy(&tbp);
		biowait(&tbp);
		if (tbp.b_flags & B_ERROR) {
E 4
I 4
		tbp->b_flags = B_BUSY | (bp->b_flags & B_READ);
		sdstrategy(tbp);
		biowait(tbp);
		if (tbp->b_flags & B_ERROR) {
E 4
			bp->b_flags |= B_ERROR;
D 4
			bp->b_error = tbp.b_error;
E 4
I 4
			bp->b_error = tbp->b_error;
E 4
			break;
		}
done:
		bn += btodb(count);
		resid -= count;
		addr += count;
#ifdef DEBUG
		if (sddebug & SDB_PARTIAL)
			printf(" done: bn %x resid %x addr %x\n",
			       bn, resid, addr);
#endif
	}
	free(cbuf, M_DEVBUF);
I 4
	free((caddr_t)tbp, M_DEVBUF);
E 4
	biodone(bp);
}

/*
 * Start a transfer on sc as described by bp
 * (i.e., call hba or target start).
 * If in format mode, we may not need dma.
 */
#define sdstart(sc, bp) { \
	SD_TRACE(T_START, sc, bp); \
	if ((sc)->sc_format_pid && legal_cmds[(sc)->sc_cmd.cdb_bytes[0]] > 0) \
		(*(sc)->sc_unit.u_start)((sc)->sc_unit.u_updev, \
		    &(sc)->sc_unit.u_forw, (struct buf *)NULL, \
		    sdigo, &(sc)->sc_dk.dk_dev); \
	else \
		(*(sc)->sc_unit.u_start)((sc)->sc_unit.u_updev, \
		    &(sc)->sc_unit.u_forw, bp, sdgo, &(sc)->sc_dk.dk_dev); \
}

void
sdstrategy(bp)
	register struct buf *bp;
{
	register struct sd_softc *sc = sdcd.cd_devs[sdunit(bp->b_dev)];
	register int s;

	if (sc->sc_format_pid) {
		/* XXXXXXXXX SHOULD NOT COMPARE curproc IN HERE!?! */
		/*
		 * In format mode, only allow the owner to mess
		 * with the drive.  Skip all the partition checks.
		 */
		if (sc->sc_format_pid != curproc->p_pid) {
			bp->b_error = EPERM;
			bp->b_flags |= B_ERROR;
			biodone(bp);
			return;
		}
		bp->b_cylin = 0;
	} else {
		register daddr_t bn = bp->b_blkno;
		register int sz = howmany(bp->b_bcount, DEV_BSIZE);
		register struct partition *p;

		/*
		 * Make sure transfer is within partition.
		 * If it starts at the end, return EOF; if
		 * it extends past the end, truncate it.
		 */
		p = &sc->sc_dk.dk_label.d_partitions[sdpart(bp->b_dev)];
		if ((unsigned)bn >= p->p_size) {
			if ((unsigned)bn > p->p_size) {
				bp->b_error = EINVAL;
				bp->b_flags |= B_ERROR;
			} else
				bp->b_resid = bp->b_bcount;
			biodone(bp);
			return;
		}
		if (bn + sz > p->p_size) {
			sz = p->p_size - bn;
			bp->b_bcount = dbtob(sz);
		}
		/*
		 * Non-aligned or partial-block transfers handled specially.
		 * SHOULD THIS BE AT A HIGHER LEVEL?
		 */
		s = sc->sc_blksize - 1;
		if ((dbtob(bn) & s) || (bp->b_bcount & s)) {
			sdlblkstrat(bp, sc->sc_blksize);
			return;
		}
		bp->b_cylin = (bn + p->p_offset) >> sc->sc_bshift;
	}

	/*
	 * Transfer valid, or format mode.  Queue the request
	 * on the drive, and maybe try to start it.
	 */
	s = splbio();
	disksort(&sc->sc_tab, bp);
	if (sc->sc_tab.b_active == 0) {
		sc->sc_tab.b_active = 1;
		sdstart(sc, bp);
	}
	splx(s);
}

int
sderror(sc, stat)
	register struct sd_softc *sc;
	register int stat;
{
	register struct scsi_sense *sn;
	int retry = 0;

	sc->sc_sense.status = stat;
	if ((stat & STS_MASK) == STS_CHECKCOND) {
		sn = (struct scsi_sense *)sc->sc_sense.sense;
		stat = scsi_request_sense(sc->sc_unit.u_hba,
		    sc->sc_unit.u_targ, sc->sc_unit.u_unit,
		    (caddr_t)sn, sizeof sc->sc_sense.sense);
		sc->sc_sense.status = stat;	/* ??? */
		if ((stat & STS_MASK) != STS_GOOD) {
			printf("%s: sense failed, status %x\n",
			    sc->sc_dk.dk_dev.dv_xname, stat);
			return (0);
		}
		printf("%s: scsi sense class %d, code %d",
		    sc->sc_dk.dk_dev.dv_xname,
		    SENSE_ECLASS(sn), SENSE_ECODE(sn));
		if (SENSE_ISXSENSE(sn) && XSENSE_ISSTD(sn)) {
			int key;

			/*
			 * Standard extended sense: can examine sense key
			 * and (if valid) info.
			 */
			key = XSENSE_KEY(sn);
			printf(", key %d", key);
			if (XSENSE_IVALID(sn))
				printf(", blk %d", XSENSE_INFO(sn));
			/* no sense or recovered error, try again */
			if (key == 0 || key == 1)
				retry = 1;
		}
		printf("\n");
	}
	return (retry);
}

/*
 * sdigo is called from the hba driver when it has got the scsi bus
 * for us, and we were doing a format op that did not need dma.
 */
void
sdigo(sc0, cdb)
	struct device *sc0;
	struct scsi_cdb *cdb;
{
	register struct sd_softc *sc = (struct sd_softc *)sc0;
	register struct buf *bp = sc->sc_tab.b_actf;
	register int stat;

	stat = (*sc->sc_unit.u_hbd->hd_icmd)(sc->sc_unit.u_hba,
	    sc->sc_unit.u_targ, &sc->sc_cmd, bp->b_un.b_addr, bp->b_bcount,
	    bp->b_flags & B_READ);
	sc->sc_sense.status = stat;
	if (stat & 0xfe) {		/* XXX */
		(void) sderror(sc, stat);
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
	}
	/*
	 * Done with SCSI bus, before we `ought' to be.  Release it.
	 */
	(*sc->sc_unit.u_rel)(sc->sc_unit.u_updev);
	bp->b_resid = 0;
	sc->sc_tab.b_errcnt = 0;
	sc->sc_tab.b_actf = bp->b_actf;
	biodone(bp);
	if ((bp = sc->sc_tab.b_actf) == NULL)
		sc->sc_tab.b_active = 0;
	else
		sdstart(sc, bp);
}

/*
 * sdgo is called from the hba driver or target code when it has
 * allocated the scsi bus and DMA resources and target datapath for us.
 */
void
sdgo(sc0, cdb)
	struct device *sc0;
	register struct scsi_cdb *cdb;
{
	register struct sd_softc *sc = (struct sd_softc *)sc0;
	register struct buf *bp = sc->sc_tab.b_actf;
	register int n;
	register unsigned int u;

	SD_TRACE(T_MKCDB, sc, bp);
	if (sc->sc_format_pid) {
		*cdb = sc->sc_cmd;
		n = 0;
	} else {
		CDB10(cdb)->cdb_cmd = bp->b_flags & B_READ ? CMD_READ10 :
		    CMD_WRITE10;
		CDB10(cdb)->cdb_lun_rel = sc->sc_unit.u_unit << 5;
		u = bp->b_cylin;
		CDB10(cdb)->cdb_lbah = u >> 24;
		CDB10(cdb)->cdb_lbahm = u >> 16;
		CDB10(cdb)->cdb_lbalm = u >> 8;
		CDB10(cdb)->cdb_lbal = u;
		CDB10(cdb)->cdb_xxx = 0;
		n = sc->sc_blksize - 1;
		u = (bp->b_bcount + n) >> (DEV_BSHIFT + sc->sc_bshift);
		CDB10(cdb)->cdb_lenh = u >> 8;
		CDB10(cdb)->cdb_lenl = u;
		CDB10(cdb)->cdb_ctrl = 0;
		n = (bp->b_bcount & n) != 0;
#ifdef DEBUG
		if (n)
			printf("%s: partial block xfer -- %x bytes\n",
			    sc->sc_dk.dk_dev.dv_xname, bp->b_bcount);
#endif
		sc->sc_transfers++;
	}
	if ((*sc->sc_unit.u_go)(sc->sc_unit.u_updev, sc->sc_unit.u_targ,
	    sdintr, (void *)sc, bp, n) == 0) {
#ifdef notyet
		sc->sc_dk.dk_busy = 1;
		sc->sc_dk.dk_seek++;	/* XXX */
		sc->sc_dk.dk_xfer++;
		sc->sc_dk.dk_wds += bp->b_bcount >> 6;
#endif
		return;
	}
	/*
	 * Some sort of nasty unrecoverable error: clobber the
	 * transfer.  Call the bus release function first, though.
	 */
	(*sc->sc_unit.u_rel)(sc->sc_unit.u_updev);
#ifdef DEBUG
	if (sddebug & SDB_ERROR)
		printf("%s: sdgo: %s adr %d blk %d len %d ecnt %d\n",
		    sc->sc_dk.dk_dev.dv_xname,
		    bp->b_flags & B_READ? "read" : "write",
		    bp->b_un.b_addr, bp->b_cylin, bp->b_bcount,
		    sc->sc_tab.b_errcnt);
#endif
	bp->b_flags |= B_ERROR;
	bp->b_error = EIO;
	bp->b_resid = 0;
	sc->sc_tab.b_errcnt = 0;
	sc->sc_tab.b_actf = bp->b_actf;
	biodone(bp);
	if ((bp = sc->sc_tab.b_actf) == NULL)
		sc->sc_tab.b_active = 0;
	else
		sdstart(sc, bp);
}

/*
 * A transfer finished (or, someday, disconnected).
 * We are already off the target/hba queues.
 * Restart this one for error recovery, or start the next, as appropriate.
 */
void
sdintr(sc0, stat, resid)
	struct device *sc0;
	int stat, resid;
{
	register struct sd_softc *sc = (struct sd_softc *)sc0;
	register struct buf *bp = sc->sc_tab.b_actf;
	int retry;

	if (bp == NULL)
		panic("sdintr");
	SD_TRACE(T_INTR, sc, bp);
#ifdef notyet
	sc->sc_dk.dk_busy = 0;
#endif
	if ((stat & STS_MASK) != STS_GOOD) {
#ifdef DEBUG
		if (sddebug & SDB_ERROR)
			printf("%s: sdintr scsi status 0x%x resid %d\n",
			    sc->sc_dk.dk_dev.dv_xname, stat, resid);
#endif
		retry = sderror(sc, stat);
		if (retry && ++sc->sc_tab.b_errcnt <= SDRETRY) {
			printf("%s: retry %d\n",
			    sc->sc_dk.dk_dev.dv_xname, sc->sc_tab.b_errcnt);
			goto restart;
		}
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
	}
	bp->b_resid = resid;
	sc->sc_tab.b_errcnt = 0;
	sc->sc_tab.b_actf = bp->b_actf;
	biodone(bp);
	if ((bp = sc->sc_tab.b_actf) == NULL)
		sc->sc_tab.b_active = 0;
	else {
restart:
		sdstart(sc, bp);
	}
}

int
sdioctl(dev_t dev, int cmd, register caddr_t data, int flag, struct proc *p)
{
	register struct sd_softc *sc = sdcd.cd_devs[sdunit(dev)];
#ifdef COMPAT_SUNOS
	int error;

	error = sun_dkioctl(&sc->sc_dk, cmd, data, sdpart(dev));
	if (error >= 0)
		return (error);
#endif
	switch (cmd) {

	case SDIOCSFORMAT:
		/* take this device into or out of "format" mode */
D 7
		if (!suser(p->p_ucred, &p->p_acflag))
E 7
I 7
		if (suser(p->p_ucred, &p->p_acflag))
E 7
			return (EPERM);
		if (*(int *)data) {
			if (sc->sc_format_pid)
				return (EPERM);
			sc->sc_format_pid = p->p_pid;
		} else
			sc->sc_format_pid = 0;
		break;

	case SDIOCGFORMAT:
		/* find out who has the device in format mode */
		*(int *)data = sc->sc_format_pid;
		break;

	case SDIOCSCSICOMMAND:
#define cdb ((struct scsi_cdb *)data)
		/*
		 * Save what user gave us as SCSI cdb to use with next
D 4
		 * read or write to the char device.
E 4
I 4
		 * read or write to the char device.  Be sure to replace
		 * the lun field with the actual unit number.
E 4
		 */
		if (sc->sc_format_pid != p->p_pid)
			return (EPERM);
		if (legal_cmds[cdb->cdb_bytes[0]] == 0)
			return (EINVAL);
		sc->sc_cmd = *cdb;
I 4
		sc->sc_cmd.cdb_bytes[1] =
		    (sc->sc_cmd.cdb_bytes[1] & ~(7 << 5)) |
		    (sc->sc_unit.u_unit << 5);
E 4
#undef	cdb
		break;

	case SDIOCSENSE:
		/*
		 * return the SCSI sense data saved after the last
		 * operation that completed with "check condition" status.
		 */
		sc->sc_sense = *(struct scsi_fmt_sense *)data;
I 6
		break;

	case DIOCGDINFO:
		*(struct disklabel *)data = sc->sc_dk.dk_label;
		break;

	case DIOCGPART:
		((struct partinfo *)data)->disklab = &sc->sc_dk.dk_label;
		((struct partinfo *)data)->part =
		    &sc->sc_dk.dk_label.d_partitions[sdpart(dev)];
E 6
		break;

	default:
		return (ENOTTY);
	}
	return (0);
}

int
sdsize(dev_t dev)
{
	register int unit = sdunit(dev);
	register struct sd_softc *sc;

	if (unit >= sdcd.cd_ndevs || (sc = sdcd.cd_devs[unit]) == NULL ||
	    (sc->sc_flags & SDF_ALIVE) == 0)
		return (-1);
	return (sc->sc_dk.dk_label.d_partitions[sdpart(dev)].p_size);
}

/*
 * Write `len' bytes from address `addr' to drive and partition in `dev',
 * at block blkoff from the beginning of the partition.  The address is
 * either kernel virtual or physical (some machines may never use one or
 * the other, but we need it in the protocol to stay machine-independent).
 */
int
sddump(dev_t dev, daddr_t blkoff, caddr_t addr, int len)
{
	register struct sd_softc *sc;
	register struct partition *p;
	register daddr_t bn, n, nblks;
	register struct hba_softc *hba;
	register int stat, unit;
	struct scsi_cdb cdb;

	/* drive ok? */
	unit = sdunit(dev);
	if (unit >= sdcd.cd_ndevs || (sc = sdcd.cd_devs[unit]) == NULL ||
	    (sc->sc_flags & SDF_ALIVE) == 0)
		return (ENXIO);

	/* blocks in range? */
	p = &sc->sc_dk.dk_label.d_partitions[sdpart(dev)];
	n = (len + sc->sc_blksize - 1) >> DEV_BSHIFT;
	if (blkoff < 0 || blkoff >= p->p_size || blkoff + n > p->p_size)
		return (EINVAL);
	bn = blkoff + p->p_offset;
	bn >>= sc->sc_bshift;

	/* scsi bus idle? */
	hba = sc->sc_unit.u_hba;
	if (hba->hba_head) {
		(*hba->hba_driver->hd_reset)(hba, 0);
		printf("[reset %s] ", sc->sc_dk.dk_dev.dv_xname);
	}

	CDB10(&cdb)->cdb_cmd = CMD_WRITE10;
	CDB10(&cdb)->cdb_lun_rel = sc->sc_unit.u_unit << 5;
	CDB10(&cdb)->cdb_xxx = 0;
	CDB10(&cdb)->cdb_ctrl = 0;

#define	DUMP_MAX	(32 * 1024)	/* no more than 32k per write */
	for (;;) {
		if ((n = len) > DUMP_MAX)
			n = DUMP_MAX;
		CDB10(&cdb)->cdb_lbah = bn >> 24;
		CDB10(&cdb)->cdb_lbahm = bn >> 16;
		CDB10(&cdb)->cdb_lbalm = bn >> 8;
		CDB10(&cdb)->cdb_lbal = bn;
		nblks = n >> (DEV_BSHIFT + sc->sc_bshift);
		CDB10(&cdb)->cdb_lenh = nblks >> 8;
		CDB10(&cdb)->cdb_lenl = nblks;
		stat = hba->hba_driver->hd_dump(hba, sc->sc_unit.u_targ,
		    &cdb, addr, n);
		if ((stat & STS_MASK) != STS_GOOD) {
			printf("%s: scsi write error 0x%x\ndump ",
			    sc->sc_dk.dk_dev.dv_xname, stat);
			return (EIO);
		}
		if ((len -= n) == 0)
			return (0);
		addr += n;
		bn += nblks;
	}
}
E 1
