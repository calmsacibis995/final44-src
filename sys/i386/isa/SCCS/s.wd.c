h53097
s 00002/00002/01180
d D 8.1 93/06/11 15:54:35 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00015/01166
d D 7.4 92/10/11 10:20:14 bostic 14 13
c make kernel includes standard
e
s 00001/00001/01180
d D 7.3 92/05/11 16:40:32 bostic 13 12
c pmap_kernel() -> kernel_pmap; from Pace Willison
e
s 00005/00004/01176
d D 7.2 91/05/09 23:32:54 bostic 12 11
c new copyright; att/bsd/shared
e
s 00336/00200/00844
d D 7.1 91/05/09 20:24:40 william 11 10
c just prior to new disklabels
e
s 00011/00011/01033
d D 5.10 91/02/26 13:47:21 william 10 9
c nulldev() -> nullop()
e
s 00000/00000/01044
d D 5.9 91/01/08 19:15:23 william 9 8
c reno changes
e
s 00001/00001/01043
d D 5.8 90/11/18 11:32:06 bill 8 7
c auto conf, bus control, conventions, interrupt control, per host config
e
s 00000/00001/01044
d D 5.7 90/11/08 21:33:33 bill 7 6
c obselete code
e
s 00034/00014/01011
d D 5.6 90/11/08 20:11:36 bill 6 5
c compaq changes that does not break everyone else(I hope)
e
s 00005/00003/01020
d D 5.5 90/11/08 20:10:23 bill 5 4
c compaq changes
e
s 00057/00041/00966
d D 5.4 90/11/08 20:09:40 bill 4 3
c changes, except for compaq
e
s 00002/00004/01005
d D 5.3 90/11/08 20:08:04 bill 3 2
c changes to make function
e
s 00012/00015/00997
d D 5.2 90/06/23 18:54:59 donahn 2 1
c cyl offset changes
e
s 01012/00000/00000
d D 5.1 90/04/24 12:59:42 william 1 0
c date and time created 90/04/24 12:59:42 by william
e
u
U
t
T
I 11
D 12
/* TODO:peel out buffer at low ipl,
   speed improvement, rewrite to clean code from garbage artifacts */

E 12
E 11
I 1
/*-
D 15
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 11
 * %sccs.include.386.c%
E 11
I 11
D 12
 * %sccs.include.redist%
E 12
I 12
 * %sccs.include.redist.c%
E 12
E 11
 *
 *	%W% (Berkeley) %G%
 */
I 12

/* TODO:peel out buffer at low ipl,
   speed improvement, rewrite to clean code from garbage artifacts */

E 12
I 2

E 2
#include "wd.h"
#if	NWD > 0
D 2
#define WDDEBUG
E 2

D 14
#include "param.h"
#include "dkbad.h"
#include "systm.h"
#include "conf.h"
#include "file.h"
D 11
#include "dir.h"
#include "user.h"
E 11
I 11
#include "stat.h"
E 11
#include "ioctl.h"
D 11
#include "disk.h"
E 11
I 11
#include "disklabel.h"
E 11
#include "buf.h"
D 11
#include "vm.h"
E 11
#include "uio.h"
D 11
#include "machine/pte.h"
D 6
#include "machine/device.h"
E 6
I 6
D 8
#include "machine/isa/device.h"
E 8
I 8
#include "machine/isa/isa_device.h"
E 8
E 6
D 7
#include "atio.h"
E 7
#include "icu.h"
#include "wdreg.h"
E 11
I 11
#include "i386/isa/isa_device.h"
#include "i386/isa/icu.h"
#include "i386/isa/wdreg.h"
E 11
#include "syslog.h"
I 11
#include "vm/vm.h"
E 14
I 14
#include <sys/param.h>
#include <sys/dkbad.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/disklabel.h>
#include <sys/buf.h>
#include <sys/uio.h>
#include <sys/syslog.h>

#include <i386/isa/isa_device.h>
#include <i386/isa/icu.h>
#include <i386/isa/wdreg.h>
#include <vm/vm.h>
E 14
E 11

#define	RETRIES		5	/* number of retries before giving up */
D 11
#define	MAXTRANSFER	256	/* max size of transfer in page clusters */
E 11
I 11
#define	MAXTRANSFER	32	/* max size of transfer in page clusters */
E 11

D 11
#define WDUNIT(dev)	((minor(dev) & 070) >> 3)
E 11
I 11
#define wdctlr(dev)	((minor(dev) & 0x80) >> 7)
#define wdunit(dev)	((minor(dev) & 0x60) >> 5)
#define wdpart(dev)	((minor(dev) & 0x1f))
E 11

#define b_cylin	b_resid		/* cylinder number for doing IO to */
				/* shares an entry in the buf struct */

/*
 * Drive states.  Used for open and format operations.
 * States < OPEN (> 0) are transient, during an open operation.
 * OPENRAW is used for unlabeled disks, and for floppies, to inhibit
 * bad-sector forwarding.
 */
#define RAWDISK		8		/* raw disk operation, no translation*/
#define ISRAWSTATE(s)	(RAWDISK&(s))	/* are we in a raw state? */
#define DISKSTATE(s)	(~RAWDISK&(s))	/* are we in a given state regardless
					   of raw or cooked mode? */

#define	CLOSED		0		/* disk is closed. */
					/* "cooked" disk states */
#define	WANTOPEN	1		/* open requested, not started */
#define	RECAL		2		/* doing restore */
#define	RDLABEL		3		/* reading pack label */
#define	RDBADTBL	4		/* reading bad-sector table */
#define	OPEN		5		/* done with open */

#define	WANTOPENRAW	(WANTOPEN|RAWDISK)	/* raw WANTOPEN */
#define	RECALRAW	(RECAL|RAWDISK)	/* raw open, doing restore */
#define	OPENRAW		(OPEN|RAWDISK)	/* open, but unlabeled disk or floppy */


/*
 * The structure of a disk drive.
 */
struct	disk {
D 11
	struct disklabel dk_dd;			/* device configuration data */
	long	dk_bc;				/* byte count left */
	short	dk_skip;			/* blocks already transferred */
	char	dk_unit;			/* physical unit number */
	char	dk_sdh;				/* sdh prototype */
	char	dk_state;			/* control state */
	u_char	dk_status;			/* copy of status reg. */
	u_char	dk_error;			/* copy of error reg. */
	short	dk_open;			/* open/closed refcnt */
E 11
I 11
	struct disklabel dk_dd;	/* device configuration data */
	long	dk_bc;		/* byte count left */
	short	dk_skip;	/* blocks already transferred */
	char	dk_unit;	/* physical unit number */
	char	dk_state;	/* control state */
	u_char	dk_status;	/* copy of status reg. */
	u_char	dk_error;	/* copy of error reg. */
	short	dk_open;	/* open/closed refcnt */
        u_long  dk_copenpart;   /* character units open on this drive */
        u_long  dk_bopenpart;   /* block units open on this drive */
        u_long  dk_openpart;    /* all units open on this drive */
	short	dk_wlabel;	/* label writable? */
E 11
};

/*
 * This label is used as a default when initializing a new or raw disk.
 * It really only lets us access the first track until we know more.
 */
struct disklabel dflt_sizes = {
D 11
	DISKMAGIC, DTYPE_ST506,
	{
E 11
I 11
	DISKMAGIC, DTYPE_ST506, 0, "default", "",
E 11
		512,		/* sector size */
D 4
		17,		/* # of sectors per track */
E 4
I 4
D 11
		36,		/* # of sectors per track */
E 4
		15,		/* # of tracks per cylinder */
D 4
		918,		/* # of cylinders per unit */
		17*15,		/* # of sectors per cylinder */
		918*15*17,	/* # of sectors per unit */
E 4
I 4
		1224,		/* # of cylinders per unit */
		36*15,		/* # of sectors per cylinder */
		1224*15*36,	/* # of sectors per unit */
E 4
		0		/* write precomp cylinder (none) */
	},
D 4
	7560,	0,	/* A=root filesystem */
	7560,	56,
	123930, 0,	/* C=whole disk */
E 4
I 4
	21600,	0,	/* A=root filesystem */
	21600,	40,
	660890, 0,	/* C=whole disk */
	216000,	80,
E 4
	0,	0,
D 4
	7560,	861,
E 4
	0,	0,
	0,	0,
D 4
	101115,	112
E 4
I 4
	399600,	480
E 11
I 11
		17,		/* # of sectors per track */
		8,		/* # of tracks per cylinder */
		766,		/* # of cylinders per unit */
		17*8,		/* # of sectors per cylinder */
		766*8*17,	/* # of sectors per unit */
		0,		/* # of spare sectors per track */
		0,		/* # of spare sectors per cylinder */
		0,		/* # of alt. cylinders per unit */
		3600,		/* rotational speed */
		1,		/* hardware sector interleave */
		0,		/* sector 0 skew, per track */
		0,		/* sector 0 skew, per cylinder */
		0,		/* head switch time, usec */
		0,		/* track-to-track seek, usec */
		0,		/* generic flags */
		0,0,0,0,0,
		0,0,0,0,0,
		DISKMAGIC,
		0,
		8,
		8192,
		8192,
	
	{{21600,	0, 0,0,0,0},	/* A=root filesystem */
	{21600,	40, 0,0,0,0},
	{660890, 0, 0,0,0,0},	/* C=whole disk */
	{216000,	80, 0,0,0,0},
	{0,	0, 0,0,0,0},
	{0,	0, 0,0,0,0},
	{0,	0, 0,0,0,0},
	{399600,	480, 0,0,0,0}}
E 11
E 4
};
I 4

E 4
static	struct	dkbad	dkbad[NWD];
struct	disk	wddrives[NWD] = {0};	/* table of units */
struct	buf	wdtab = {0};
struct	buf	wdutab[NWD] = {0};	/* head of queue per drive */
struct	buf	rwdbuf[NWD] = {0};	/* buffers for raw IO */
long	wdxfer[NWD] = {0};		/* count of transfers */
int	writeprotected[NWD] = { 0 };
int	wdprobe(), wdattach(), wdintr();
D 6
struct	driver wddriver = {
E 6
I 6
struct	isa_driver wddriver = {
E 6
	wdprobe, wdattach, "wd",
};
D 11
#include "dbg.h"
E 11

I 6
static wdc;
E 6
/*
 * Probe routine
 */
wdprobe(dvp)
D 6
	struct device *dvp;
E 6
I 6
	struct isa_device *dvp;
E 6
{
D 6
	register wdc = dvp->ioa;
E 6
I 6
wdc = dvp->id_iobase;
E 6

#ifdef lint
	wdintr(0);
#endif
I 11
	/* XXX sorry, needs to be better */
E 11
	outb(wdc+wd_error, 0x5a) ;	/* error register not writable */
D 11
	/*wdp->wd_cyl_hi = 0xff ;/* only two bits of cylhi are implemented */
E 11
	outb(wdc+wd_cyl_lo, 0xa5) ;	/* but all of cyllo are implemented */
D 11
	if(inb(wdc+wd_error) != 0x5a /*&& wdp->wd_cyl_hi == 3*/
	   && inb(wdc+wd_cyl_lo) == 0xa5)
E 11
I 11
	if(inb(wdc+wd_error) != 0x5a && inb(wdc+wd_cyl_lo) == 0xa5)
E 11
		return(1) ;
	return (0);
}

/*
 * attach each drive if possible.
 */
wdattach(dvp)
D 6
	struct device *dvp;
E 6
I 6
	struct isa_device *dvp;
E 6
{
D 6
	int unit = dvp->unit;
E 6
I 6
	int unit = dvp->id_unit;
E 6

D 6
	INTREN((IRQ14|4));
D 4
	outb(0x3f6,0);
E 4
I 4
	outb(0x3f6,8);
E 6
I 6
	outb(wdc+wd_ctlr,12);
	DELAY(1000);
	outb(wdc+wd_ctlr,8);
E 6
E 4
}

/* Read/write routine for a buffer.  Finds the proper unit, range checks
 * arguments, and schedules the transfer.  Does not wait for the transfer
 * to complete.  Multi-page transfers are supported.  All I/O requests must
 * be a multiple of a sector in length.
 */
wdstrategy(bp)
	register struct buf *bp;	/* IO operation to perform */
{
	register struct buf *dp;
	register struct disk *du;	/* Disk unit to do the IO.	*/
D 11
	long nblocks, cyloff, blknum;
	int	unit = WDUNIT(bp->b_dev), xunit = minor(bp->b_dev) & 7;
E 11
I 11
	register struct partition *p;
	long maxsz, sz;
	int	unit = wdunit(bp->b_dev);
E 11
	int	s;

	if ((unit >= NWD) || (bp->b_blkno < 0)) {
D 2
		dprintf(DDSK,"wdstrat: unit = %d, blkno = %d, bcount = %d\n",
E 2
I 2
		printf("wdstrat: unit = %d, blkno = %d, bcount = %d\n",
E 2
			unit, bp->b_blkno, bp->b_bcount);
D 2
		dprintf(DDSK,"wd:error in wdstrategy\n");
E 2
I 2
		pg("wd:error in wdstrategy");
E 2
		bp->b_flags |= B_ERROR;
		goto bad;
	}
	if (writeprotected[unit] && (bp->b_flags & B_READ) == 0) {
		printf("wd%d: write protected\n", unit);
		goto bad;
	}
	du = &wddrives[unit];
	if (DISKSTATE(du->dk_state) != OPEN)
		goto q;
I 11
#ifdef old
E 11
	/*
	 * Convert DEV_BSIZE "blocks" to sectors.
	 * Note: doing the conversions this way limits the partition size
	 * to about 8 million sectors (1-8 Gb).
	 */
D 11
	blknum = (unsigned long) bp->b_blkno * DEV_BSIZE / du->dk_dd.dk_secsize;
	if (((u_long) bp->b_blkno * DEV_BSIZE % du->dk_dd.dk_secsize != 0) ||
E 11
I 11
	blknum = (unsigned long) bp->b_blkno * DEV_BSIZE / du->dk_dd.d_secsize;
	if (((u_long) bp->b_blkno * DEV_BSIZE % du->dk_dd.d_secsize != 0) ||
E 11
D 2
	    bp->b_bcount >= MAXTRANSFER * CLBYTES /*||
	    bp->b_bcount % du->dk_dd.dk_secsize*/) {
E 2
I 2
	    bp->b_bcount >= MAXTRANSFER * CLBYTES) {
E 2
		bp->b_flags |= B_ERROR;
D 2
printf("wdstrat: blknum %d bcount %d blkno %d ", blknum,
bp->b_bcount, bp->b_blkno);
E 2
		goto bad;
	}
D 11
	nblocks = du->dk_dd.dk_partition[xunit].nblocks;
	cyloff = du->dk_dd.dk_partition[xunit].cyloff;
	if (blknum + (bp->b_bcount / du->dk_dd.dk_secsize) > nblocks) {
E 11
I 11
	nblocks = du->dk_dd.d_partitions[part].p_size;
	cyloff = du->dk_dd.d_partitions[part].p_offset;
	if (blknum + (bp->b_bcount / du->dk_dd.d_secsize) > nblocks) {
E 11
D 2
		dprintf(DDSK,"blknum = %d, fssize = %d\n", blknum, nblocks);
E 2
		if (blknum == nblocks)
			bp->b_resid = bp->b_bcount;
		else
			bp->b_flags |= B_ERROR;
		goto bad;
	}
D 11
	bp->b_cylin = blknum / du->dk_dd.dk_secpercyl + cyloff;
E 11
I 11
	bp->b_cylin = blknum / du->dk_dd.d_secpercyl + cyloff;
#else
        /*
         * Determine the size of the transfer, and make sure it is
         * within the boundaries of the partition.
         */
        p = &du->dk_dd.d_partitions[wdpart(bp->b_dev)];
        maxsz = p->p_size;
        sz = (bp->b_bcount + DEV_BSIZE - 1) >> DEV_BSHIFT;
        if (bp->b_blkno + p->p_offset <= LABELSECTOR &&
#if LABELSECTOR != 0
            bp->b_blkno + p->p_offset + sz > LABELSECTOR &&
#endif
            (bp->b_flags & B_READ) == 0 && du->dk_wlabel == 0) {
                bp->b_error = EROFS;
                goto bad;
        }
        if (bp->b_blkno < 0 || bp->b_blkno + sz > maxsz) {
                /* if exactly at end of disk, return an EOF */
                if (bp->b_blkno == maxsz) {
                        bp->b_resid = bp->b_bcount;
                        biodone(bp);
                        return;
                }
                /* or truncate if part of it fits */
                sz = maxsz - bp->b_blkno;
                if (sz <= 0)
                        goto bad;
                bp->b_bcount = sz << DEV_BSHIFT;
        }
        bp->b_cylin = (bp->b_blkno + p->p_offset) / du->dk_dd.d_secpercyl;
#endif
E 11
q:
	dp = &wdutab[unit];
D 4
	s = splbio();
E 4
I 4
	s = splhigh();
E 4
	disksort(dp, bp);
	if (dp->b_active == 0)
		wdustart(du);		/* start drive if idle */
	if (wdtab.b_active == 0)
		wdstart(s);		/* start IO if controller idle */
	splx(s);
	return;

bad:
	bp->b_error = EINVAL;
	biodone(bp);
}

/* Routine to queue a read or write command to the controller.  The request is
 * linked into the active list for the controller.  If the controller is idle,
 * the transfer is started.
 */
wdustart(du)
	register struct disk *du;
{
	register struct buf *bp, *dp;

	dp = &wdutab[du->dk_unit];
	if (dp->b_active)
		return;
	bp = dp->b_actf;
	if (bp == NULL)
		return;	
	dp->b_forw = NULL;
	if (wdtab.b_actf  == NULL)		/* link unit into active list */
		wdtab.b_actf = dp;
	else
		wdtab.b_actl->b_forw = dp;
	wdtab.b_actl = dp;
	dp->b_active = 1;		/* mark the drive as busy */
}

/*
 * Controller startup routine.  This does the calculation, and starts
 * a single-sector read or write operation.  Called to start a transfer,
 * or from the interrupt routine to continue a multi-sector transfer.
 * RESTRICTIONS:
 * 1.	The transfer length must be an exact multiple of the sector size.
 */

I 4
static wd_sebyse;

E 4
wdstart()
{
	register struct disk *du;	/* disk unit for IO */
D 6
	register wdc = IO_WD0; /*XXX*/
E 6
	register struct buf *bp;
	struct buf *dp;
	register struct bt_bad *bt_ptr;
	long	blknum, pagcnt, cylin, head, sector;
	long	secpertrk, secpercyl, addr, i;
D 11
	int	minor_dev, unit, s;
E 11
I 11
	int	unit, s;
E 11

loop:
	dp = wdtab.b_actf;
	if (dp == NULL)
		return;
	bp = dp->b_actf;
	if (bp == NULL) {
		wdtab.b_actf = dp->b_forw;
		goto loop;
	}
D 11
	unit = WDUNIT(bp->b_dev);
E 11
I 11
	unit = wdunit(bp->b_dev);
E 11
	du = &wddrives[unit];
	if (DISKSTATE(du->dk_state) <= RDLABEL) {
		if (wdcontrol(bp)) {
			dp->b_actf = bp->av_forw;
			goto loop;	/* done */
		}
		return;
	}
D 11
	minor_dev = minor(bp->b_dev) & 7;
	secpertrk = du->dk_dd.dk_nsectors;
	secpercyl = du->dk_dd.dk_secpercyl;
E 11
I 11
	secpertrk = du->dk_dd.d_nsectors;
	secpercyl = du->dk_dd.d_secpercyl;
E 11
	/*
	 * Convert DEV_BSIZE "blocks" to sectors.
	 */
D 11
	blknum = (unsigned long) bp->b_blkno * DEV_BSIZE / du->dk_dd.dk_secsize
E 11
I 11
	blknum = (unsigned long) bp->b_blkno * DEV_BSIZE / du->dk_dd.d_secsize
E 11
		+ du->dk_skip;
#ifdef	WDDEBUG
	if (du->dk_skip == 0) {
		dprintf(DDSK,"\nwdstart %d: %s %d@%d; map ", unit,
			(bp->b_flags & B_READ) ? "read" : "write",
			bp->b_bcount, blknum);
	} else {
D 4
		dprintf(DDSK," %d)", du->dk_skip);
E 4
I 4
		dprintf(DDSK," %d)%x", du->dk_skip, inb(wdc+wd_altsts));
E 4
	}
#endif

	addr = (int) bp->b_un.b_addr;
	if(du->dk_skip==0) du->dk_bc = bp->b_bcount;
	cylin = blknum / secpercyl;
	head = (blknum % secpercyl) / secpertrk;
D 4
	sector = blknum % secpertrk + 1;
E 4
I 4
	sector = blknum % secpertrk;
E 4
	if (DISKSTATE(du->dk_state) == OPEN)
D 11
		cylin += du->dk_dd.dk_partition[minor_dev].cyloff;
E 11
I 11
		cylin += du->dk_dd.d_partitions[wdpart(bp->b_dev)].p_offset
				/ secpercyl;
E 11

D 4

E 4
	/* 
	 * See if the current block is in the bad block list.
	 * (If we have one, and not formatting.)
	 */
D 4
#ifdef notyet
	if (du->dk_state == OPEN)
E 4
I 4
	if (DISKSTATE(du->dk_state) == OPEN && wd_sebyse)
E 4
	    for (bt_ptr = dkbad[unit].bt_bad; bt_ptr->bt_cyl != -1; bt_ptr++) {
		if (bt_ptr->bt_cyl > cylin)
			/* Sorted list, and we passed our cylinder. quit. */
			break;
		if (bt_ptr->bt_cyl == cylin &&
				bt_ptr->bt_trksec == (head << 8) + sector) {
			/*
			 * Found bad block.  Calculate new block addr.
			 * This starts at the end of the disk (skip the
			 * last track which is used for the bad block list),
			 * and works backwards to the front of the disk.
			 */
#ifdef	WDDEBUG
			    dprintf(DDSK,"--- badblock code -> Old = %d; ",
				blknum);
#endif
D 11
			blknum = du->dk_dd.dk_secperunit - du->dk_dd.dk_nsectors
E 11
I 11
			blknum = du->dk_dd.d_secperunit - du->dk_dd.d_nsectors
E 11
				- (bt_ptr - dkbad[unit].bt_bad) - 1;
			cylin = blknum / secpercyl;
			head = (blknum % secpercyl) / secpertrk;
			sector = blknum % secpertrk;
#ifdef	WDDEBUG
			    dprintf(DDSK, "new = %d\n", blknum);
#endif
			break;
		}
	}
D 4
#endif
E 4
I 4
	sector += 1;	/* sectors begin with 1, not 0 */
E 4

	wdtab.b_active = 1;		/* mark controller active */

I 4
	if(du->dk_skip==0 || wd_sebyse) {
	if(wdtab.b_errcnt && (bp->b_flags & B_READ) == 0) du->dk_bc += 512;
	while ((inb(wdc+wd_status) & WDCS_BUSY) != 0) ;
	/*while ((inb(wdc+wd_status) & WDCS_DRQ)) inb(wdc+wd_data);*/
E 4
	outb(wdc+wd_precomp, 0xff);
	/*wr(wdc+wd_precomp, du->dk_dd.dk_precompcyl / 4);*/
	/*if (bp->b_flags & B_FORMAT) {
		wr(wdc+wd_sector, du->dk_dd.dk_gap3);
		wr(wdc+wd_seccnt, du->dk_dd.dk_nsectors);
	} else {*/
D 4
	outb(wdc+wd_seccnt, 1);
E 4
I 4
	if(wd_sebyse)
		outb(wdc+wd_seccnt, 1);
	else
		outb(wdc+wd_seccnt, ((du->dk_bc +511) / 512));
E 4
	outb(wdc+wd_sector, sector);

	outb(wdc+wd_cyl_lo, cylin);
	outb(wdc+wd_cyl_hi, cylin >> 8);

	/* Set up the SDH register (select drive).     */
	outb(wdc+wd_sdh, WDSD_IBM | (unit<<4) | (head & 0xf));
D 5
	while ((inb(wdc+wd_altsts) & WDCS_READY) == 0) ;
E 5
I 5
	while ((inb(wdc+wd_status) & WDCS_READY) == 0) ;
E 5

	/*if (bp->b_flags & B_FORMAT)
		wr(wdc+wd_command, WDCC_FORMAT);
	else*/
		outb(wdc+wd_command,
			(bp->b_flags & B_READ)? WDCC_READ : WDCC_WRITE);
#ifdef	WDDEBUG
D 4
	if(du->dk_skip == 0)
	dprintf(DDSK,"sector %d cylin %d head %d addr %x\n",
	    sector, cylin, head, addr);
E 4
I 4
	dprintf(DDSK,"sector %d cylin %d head %d addr %x sts %x\n",
	    sector, cylin, head, addr, inb(wdc+wd_altsts));
E 4
#endif
D 4

E 4
I 4
}
E 4
		
	/* If this is a read operation, just go away until it's done.	*/
	if (bp->b_flags & B_READ) return;

	/* Ready to send data?	*/
D 5
	while ((inb(wdc+wd_altsts) & WDCS_DRQ) == 0)
E 5
I 5
D 11
	while ((inb(wdc+wd_status) & WDCS_DRQ) == 0)
E 5
D 10
		nulldev();		/* So compiler won't optimize out */
E 10
I 10
		nullop();		/* So compiler won't optimize out */
E 11
I 11
	while ((inb(wdc+wd_status) & WDCS_DRQ) == 0);
E 11
E 10

	/* ASSUMES CONTIGUOUS MEMORY */
D 4
	{ register buff_addr;

	buff_addr = addr;
	buff_addr += (du->dk_skip * 512)/* & CLOFSET*/;
	outsw (wdc+wd_data, buff_addr, 256);
	}
E 4
I 4
	outsw (wdc+wd_data, addr+du->dk_skip*512, 256);
E 4
	du->dk_bc -= 512;
}

/*
 * these are globally defined so they can be found
 * by the debugger easily in the case of a system crash
 */
daddr_t wd_errsector;
daddr_t wd_errbn;
unsigned char wd_errstat;

/* Interrupt routine for the controller.  Acknowledge the interrupt, check for
 * errors on the current operation, mark it done if necessary, and start
 * the next request.  Also check for a partially done transfer, and
 * continue with the next chunk if so.
 */
D 11
wdintr()
E 11
I 11
wdintr(unit)
E 11
{
	register struct	disk *du;
D 6
	register wdc = IO_WD0; /*XXX*/
E 6
	register struct buf *bp, *dp;
	int status;
	char partch ;
I 4
D 11
static shit[32];
static wd_haderror;
E 11
I 11
	static wd_haderror;
E 11
E 4

	/* Shouldn't need this, but it may be a slow controller.	*/
D 4
	while ((status = inb(wdc+wd_altsts)) & WDCS_BUSY)
E 4
I 4
D 11
	while ((status = inb(wdc+wd_status)) & WDCS_BUSY)
E 4
D 10
		nulldev();
E 10
I 10
		nullop();
E 11
I 11
	while ((status = inb(wdc+wd_status)) & WDCS_BUSY) ;
E 11
E 10
	if (!wdtab.b_active) {
		printf("wd: extra interrupt\n");
		return;
	}

D 3
#ifdef	WDDEBUGx
E 3
I 3
#ifdef	WDDEBUG
E 3
	dprintf(DDSK,"I ");
#endif
	dp = wdtab.b_actf;
	bp = dp->b_actf;
D 11
	du = &wddrives[WDUNIT(bp->b_dev)];
	partch = "abcdefgh"[minor(bp->b_dev)&7] ;
E 11
I 11
	du = &wddrives[wdunit(bp->b_dev)];
	partch = wdpart(bp->b_dev) + 'a';
E 11
	if (DISKSTATE(du->dk_state) <= RDLABEL) {
		if (wdcontrol(bp))
			goto done;
		return;
	}
	if (status & (WDCS_ERR | WDCS_ECCCOR)) {
I 4
		wd_errstat = inb(wdc+wd_error);		/* save error status */
I 5
D 6
outb(wdc+wd_command, WDCC_RESTORE);
while (inb(wdc+wd_status)&WDCS_BUSY);
E 6
E 5
E 4
#ifdef	WDDEBUG
D 2
		dprintf(DDSK|DPAUSE,"error %x\n", wd_errstat);
E 2
I 2
D 4
		printf("error %x\n", wd_errstat);
E 4
I 4
		printf("status %x error %x\n", status, wd_errstat);
E 4
E 2
#endif
I 4
		if(wd_sebyse == 0) {
			wd_haderror = 1;
			goto outt;
		}
E 4
		/*if (bp->b_flags & B_FORMAT) {
			du->dk_status = status;
			du->dk_error = wdp->wd_error;
			bp->b_flags |= B_ERROR;
			goto done;
		}*/
		
D 4
		wd_errstat = inb(wdc+wd_error);		/* save error status */
E 4
D 11
		wd_errsector = (bp->b_cylin * du->dk_dd.dk_secpercyl) +
E 11
I 11
		wd_errsector = (bp->b_cylin * du->dk_dd.d_secpercyl) +
E 11
			(((unsigned long) bp->b_blkno * DEV_BSIZE /
D 11
			    du->dk_dd.dk_secsize) % du->dk_dd.dk_secpercyl) +
E 11
I 11
			    du->dk_dd.d_secsize) % du->dk_dd.d_secpercyl) +
E 11
			du->dk_skip;
		wd_errbn = bp->b_blkno
D 11
			+ du->dk_skip * du->dk_dd.dk_secsize / DEV_BSIZE ;
E 11
I 11
			+ du->dk_skip * du->dk_dd.d_secsize / DEV_BSIZE ;
E 11
		if (status & WDCS_ERR) {
D 4
			if (++wdtab.b_errcnt < RETRIES)
E 4
I 4
			if (++wdtab.b_errcnt < RETRIES) {
E 4
				wdtab.b_active = 0;
D 4
			else {
E 4
I 4
D 11
				/*while ((inb(wdc+wd_status) & WDCS_DRQ))
				insw(wdc+wd_data, &shit, sizeof(shit)/2);*/
E 11
			} else {
E 4
				printf("wd%d%c: ", du->dk_unit, partch);
				printf(
				"hard %s error, sn %d bn %d status %b error %b\n",
					(bp->b_flags & B_READ)? "read":"write",
					wd_errsector, wd_errbn, status, WDCS_BITS,
					wd_errstat, WDERR_BITS);
				bp->b_flags |= B_ERROR;	/* flag the error */
			}
		} else
			log(LOG_WARNING,"wd%d%c: soft ecc sn %d bn %d\n",
				du->dk_unit, partch, wd_errsector,
				wd_errbn);
	}
I 4
outt:
E 4

	/*
	 * If this was a successful read operation, fetch the data.
	 */
	if (((bp->b_flags & (B_READ | B_ERROR)) == B_READ) && wdtab.b_active) {
		int chk, dummy;

D 4
		chk = min(256,(du->dk_bc/2));
E 4
I 4
		chk = min(256,du->dk_bc/2);
E 4
		/* Ready to receive data?	*/
D 11
		while ((inb(wdc+wd_status) & WDCS_DRQ) == 0)
D 10
			nulldev();
E 10
I 10
			nullop();
E 11
I 11
		while ((inb(wdc+wd_status) & WDCS_DRQ) == 0) ;
E 11
E 10

/*dprintf(DDSK,"addr %x\n", (int)bp->b_un.b_addr + du->dk_skip * 512);*/
		insw(wdc+wd_data,(int)bp->b_un.b_addr + du->dk_skip * 512 ,chk);
D 2
		du->dk_bc -= chk;
E 2
I 2
		du->dk_bc -= 2*chk;
E 2
D 4
		while(chk++ < 256) insw(wdc+wd_data,&dummy,1);
E 4
I 4
		while (chk++ < 256) insw (wdc+wd_data,&dummy,1);
E 4
	}

	wdxfer[du->dk_unit]++;
	if (wdtab.b_active) {
		if ((bp->b_flags & B_ERROR) == 0) {
			du->dk_skip++;		/* Add to successful sectors. */
			if (wdtab.b_errcnt) {
				log(LOG_WARNING, "wd%d%c: ",
						du->dk_unit, partch);
				log(LOG_WARNING,
			"soft %s error, sn %d bn %d error %b retries %d\n",
				    (bp->b_flags & B_READ) ? "read" : "write",
				    wd_errsector, wd_errbn, wd_errstat,
				    WDERR_BITS, wdtab.b_errcnt);
			}
			wdtab.b_errcnt = 0;

			/* see if more to transfer */
D 2
			if (du->dk_skip < bp->b_bcount / 512) {
E 2
I 2
			/*if (du->dk_skip < (bp->b_bcount + 511) / 512) {*/
D 4
			if (du->dk_bc > 0) {
E 4
I 4
			if (du->dk_bc > 0 && wd_haderror == 0) {
E 4
E 2
				wdstart();
				return;		/* next chunk is started */
I 4
			} else if (wd_haderror && wd_sebyse == 0) {
				du->dk_skip = 0;
				wd_haderror = 0;
				wd_sebyse = 1;
				wdstart();
				return;		/* redo xfer sector by sector */
E 4
			}
		}

done:
I 4
		wd_sebyse = 0;
E 4
		/* done with this transfer, with or without error */
		wdtab.b_actf = dp->b_forw;
		wdtab.b_errcnt = 0;
		du->dk_skip = 0;
		dp->b_active = 0;
		dp->b_actf = bp->av_forw;
		dp->b_errcnt = 0;
		bp->b_resid = 0;
		biodone(bp);
	}
	wdtab.b_active = 0;
	if (dp->b_actf)
		wdustart(du);		/* requeue disk if more io to do */
	if (wdtab.b_actf)
		wdstart();		/* start IO on next drive */
}

/*
 * Initialize a drive.
 */
D 11
wdopen(dev, flags)
	dev_t	dev;
	int	flags;
E 11
I 11
wdopen(dev, flags, fmt)
        dev_t dev;
        int flags, fmt;
E 11
{
	register unsigned int unit;
	register struct buf *bp;
	register struct disk *du;
I 11
        int part = wdpart(dev), mask = 1 << part;
        struct partition *pp;
E 11
	struct dkbad *db;
	int i, error = 0;

D 11
	unit = WDUNIT(dev);
E 11
I 11
	unit = wdunit(dev);
E 11
D 2
dprintf(DDSK,"wdopen %x\n",unit);
E 2
I 2
D 3
/*dprintf(DDSK,"wdopen %x\n",unit);*/
E 3
E 2
	if (unit >= NWD) return (ENXIO) ;
	du = &wddrives[unit];
I 11
#ifdef notdef
E 11
	if (du->dk_open){
		du->dk_open++ ;
		return(0);	/* already is open, don't mess with it */
	}
D 11
#ifdef THE_BUG
	if (du->dk_state && DISKSTATE(du->dk_state) <= OPEN)
		return(0);
E 11
#endif
	du->dk_unit = unit;
	wdutab[unit].b_actf = NULL;
	/*if (flags & O_NDELAY)
		du->dk_state = WANTOPENRAW;
	else*/
		du->dk_state = WANTOPEN;
	/*
	 * Use the default sizes until we've read the label,
	 * or longer if there isn't one there.
	 */
	du->dk_dd = dflt_sizes;

	/*
	 * Recal, read of disk label will be done in wdcontrol
	 * during first read operation.
	 */
	bp = geteblk(512);
D 3
	bp->b_dev = dev;
E 3
I 3
	bp->b_dev = dev & 0xff00;
E 3
D 11
	bp->b_blkno = bp->b_bcount = 0;
E 11
I 11
	bp->b_bcount = 0;
	bp->b_blkno = LABELSECTOR;
E 11
	bp->b_flags = B_READ;
	wdstrategy(bp);
	biowait(bp);
	if (bp->b_flags & B_ERROR) {
D 11
		u.u_error = 0; 	/* XXX */
E 11
		error = ENXIO;
		du->dk_state = CLOSED;
		goto done;
	}
	if (du->dk_state == OPENRAW) {
		du->dk_state = OPENRAW;
		goto done;
	}
D 4
#ifdef notyet
E 4
	/*
	 * Read bad sector table into memory.
	 */
	i = 0;
	do {
D 11
		u.u_error = 0;				/* XXX */
E 11
		bp->b_flags = B_BUSY | B_READ;
D 11
		bp->b_blkno = du->dk_dd.dk_secperunit - du->dk_dd.dk_nsectors
E 11
I 11
		bp->b_blkno = du->dk_dd.d_secperunit - du->dk_dd.d_nsectors
E 11
			+ i;
D 11
		if (du->dk_dd.dk_secsize > DEV_BSIZE)
			bp->b_blkno *= du->dk_dd.dk_secsize / DEV_BSIZE;
E 11
I 11
		if (du->dk_dd.d_secsize > DEV_BSIZE)
			bp->b_blkno *= du->dk_dd.d_secsize / DEV_BSIZE;
E 11
		else
D 11
			bp->b_blkno /= DEV_BSIZE / du->dk_dd.dk_secsize;
		bp->b_bcount = du->dk_dd.dk_secsize;
		bp->b_cylin = du->dk_dd.dk_ncylinders - 1;
E 11
I 11
			bp->b_blkno /= DEV_BSIZE / du->dk_dd.d_secsize;
		bp->b_bcount = du->dk_dd.d_secsize;
		bp->b_cylin = du->dk_dd.d_ncylinders - 1;
E 11
		wdstrategy(bp);
		biowait(bp);
	} while ((bp->b_flags & B_ERROR) && (i += 2) < 10 &&
D 11
		i < du->dk_dd.dk_nsectors);
E 11
I 11
		i < du->dk_dd.d_nsectors);
E 11
	db = (struct dkbad *)(bp->b_un.b_addr);
I 4
#define DKBAD_MAGIC 0x4321
E 4
	if ((bp->b_flags & B_ERROR) == 0 && db->bt_mbz == 0 &&
	    db->bt_flag == DKBAD_MAGIC) {
		dkbad[unit] = *db;
		du->dk_state = OPEN;
	} else {
		printf("wd%d: %s bad-sector file\n", unit,
		    (bp->b_flags & B_ERROR) ? "can't read" : "format error in");
D 11
		u.u_error = 0;				/* XXX */
		/*error = ENXIO ;*/
E 11
I 11
		error = ENXIO ;
E 11
		du->dk_state = OPENRAW;
	}
D 4
#else
	du->dk_state = OPEN;
#endif
E 4
done:
	bp->b_flags = B_INVAL | B_AGE;
	brelse(bp);
	if (error == 0)
		du->dk_open = 1;
I 11

        /*
         * Warn if a partion is opened
         * that overlaps another partition which is open
         * unless one is the "raw" partition (whole disk).
         */
#define RAWPART         8               /* 'x' partition */     /* XXX */
        if ((du->dk_openpart & mask) == 0 && part != RAWPART) {
		int	start, end;

                pp = &du->dk_dd.d_partitions[part];
                start = pp->p_offset;
                end = pp->p_offset + pp->p_size;
                for (pp = du->dk_dd.d_partitions;
                     pp < &du->dk_dd.d_partitions[du->dk_dd.d_npartitions];
			pp++) {
                        if (pp->p_offset + pp->p_size <= start ||
                            pp->p_offset >= end)
                                continue;
                        if (pp - du->dk_dd.d_partitions == RAWPART)
                                continue;
                        if (du->dk_openpart & (1 << (pp -
					du->dk_dd.d_partitions)))
                                log(LOG_WARNING,
                                    "wd%d%c: overlaps open partition (%c)\n",
                                    unit, part + 'a',
                                    pp - du->dk_dd.d_partitions + 'a');
                }
        }
        if (part >= du->dk_dd.d_npartitions)
                return (ENXIO);
        du->dk_openpart |= mask;
        switch (fmt) {
        case S_IFCHR:
                du->dk_copenpart |= mask;
                break;
        case S_IFBLK:
                du->dk_bopenpart |= mask;
                break;
        }
E 11
	return (error);
}

/*
 * Implement operations other than read/write.
 * Called from wdstart or wdintr during opens and formats.
 * Uses finite-state-machine to track progress of operation in progress.
 * Returns 0 if operation still in progress, 1 if completed.
 */
wdcontrol(bp)
	register struct buf *bp;
{
	register struct disk *du;
D 6
	register wdc = IO_WD0; /*XXX*/
E 6
	register unit;
	unsigned char  stat;
	int s, cnt;
	extern int bootdev, cyloffset;

D 2
	cyloffset=290;
E 2
I 2
D 3
	cyloffset=0;
E 3
E 2
D 11
	du = &wddrives[WDUNIT(bp->b_dev)];
E 11
I 11
	du = &wddrives[wdunit(bp->b_dev)];
E 11
	unit = du->dk_unit;
	switch (DISKSTATE(du->dk_state)) {

	tryagainrecal:
	case WANTOPEN:			/* set SDH, step rate, do restore */
#ifdef	WDDEBUG
		dprintf(DDSK,"wd%d: recal ", unit);
#endif
		s = splbio();		/* not called from intr level ... */
I 6
D 11

#ifdef notdef
		/* some compaq controllers require this ... */
		outb(wdc+wd_sdh, WDSD_IBM | (unit << 4) 
			+ du->dk_dd.dk_ntracks-1);
		outb(wdc+wd_seccnt, du->dk_dd.dk_nsectors);
		outb(wdc+wd_command, 0x91);
D 10
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) nulldev();
E 10
I 10
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) nullop();
E 10
#endif

E 11
E 6
		outb(wdc+wd_sdh, WDSD_IBM | (unit << 4));
		wdtab.b_active = 1;
		outb(wdc+wd_command, WDCC_RESTORE | WD_STEP);
		du->dk_state++;
		splx(s);
		return(0);

	case RECAL:
D 5
		if ((stat = inb(wdc+wd_altsts)) & WDCS_ERR) {
E 5
I 5
		if ((stat = inb(wdc+wd_status)) & WDCS_ERR) {
E 5
			printf("wd%d: recal", du->dk_unit);
			if (unit == 0) {
				printf(": status %b error %b\n",
					stat, WDCS_BITS,
					inb(wdc+wd_error), WDERR_BITS);
				if (++wdtab.b_errcnt < RETRIES)
					goto tryagainrecal;
			}
			goto badopen;
		}
I 11

		/* some compaq controllers require this ... */
		wdsetctlr(bp->b_dev, du);

E 11
		wdtab.b_errcnt = 0;
		if (ISRAWSTATE(du->dk_state)) {
			du->dk_state = OPENRAW;
			return(1);
		}
retry:
#ifdef	WDDEBUG
		dprintf(DDSK,"rdlabel ");
#endif
I 4
D 6
cyloffset=0;
E 6
I 6
D 11
if( cyloffset < 0 || cyloffset > 2048) cyloffset=0;
E 11
I 11
if( cyloffset < 0 || cyloffset > 8192) cyloffset=0;
E 11
E 6
E 4
		/*
D 11
		 * Read in sector 0 to get the pack label and geometry.
E 11
I 11
		 * Read in sector LABELSECTOR to get the pack label
		 * and geometry.
E 11
		 */
		outb(wdc+wd_precomp, 0xff);/* sometimes this is head bit 3 */
		outb(wdc+wd_seccnt, 1);
D 11
		outb(wdc+wd_sector, 1);
E 11
I 11
		outb(wdc+wd_sector, LABELSECTOR+1);
E 11
		/*if (bp->b_dev == bootdev) {
			(wdc+wd_cyl_lo = cyloffset & 0xff;
			(wdc+wd_cyl_hi = cyloffset >> 8;
		} else {
			(wdc+wd_cyl_lo = 0;
			(wdc+wd_cyl_hi = 0;
		}*/
		outb(wdc+wd_cyl_lo, (cyloffset & 0xff));
		outb(wdc+wd_cyl_hi, (cyloffset >> 8));
		outb(wdc+wd_sdh, WDSD_IBM | (unit << 4));
		outb(wdc+wd_command, WDCC_READ);
		du->dk_state = RDLABEL;
		return(0);

	case RDLABEL:
		if ((stat = inb(wdc+wd_status)) & WDCS_ERR) {
			if (++wdtab.b_errcnt < RETRIES)
				goto retry;
			printf("wd%d: read label", unit);
			goto badopen;
		}

		insw(wdc+wd_data, bp->b_un.b_addr, 256);

		if (((struct disklabel *)
D 11
		    (bp->b_un.b_addr + LABELOFFSET))->dk_magic == DISKMAGIC) {
E 11
I 11
		    (bp->b_un.b_addr + LABELOFFSET))->d_magic == DISKMAGIC) {
E 11
		       du->dk_dd =
			 * (struct disklabel *) (bp->b_un.b_addr + LABELOFFSET);
		} else {
			printf("wd%d: bad disk label\n", du->dk_unit);
			du->dk_state = OPENRAW;
		}
I 6

		s = splbio();		/* not called from intr level ... */
D 10
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) nulldev();
E 10
I 10
D 11
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) nullop();
E 10
		outb(wdc+wd_sdh, WDSD_IBM | (unit << 4) 
			+ du->dk_dd.dk_ntracks-1);
		outb(wdc+wd_cyl_lo, du->dk_dd.dk_ncylinders);
		outb(wdc+wd_cyl_hi, du->dk_dd.dk_ncylinders>>8);
		outb(wdc+wd_seccnt, du->dk_dd.dk_nsectors);
		outb(wdc+wd_command, 0x91);
D 10
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) nulldev();
E 10
I 10
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) nullop();
E 11
I 11
		while ((stat = inb(wdc+wd_status)) & WDCS_BUSY);

		wdsetctlr(bp->b_dev, du);

E 11
E 10
		outb(wdc+wd_seccnt, 0);
		splx(s);

E 6
		if (du->dk_state == RDLABEL)
			du->dk_state = RDBADTBL;
		/*
		 * The rest of the initialization can be done
		 * by normal means.
		 */
		return(1);

	default:
D 11
		panic("wdcontrol %x", du->dk_state );
E 11
I 11
		panic("wdcontrol");
E 11
	}
	/* NOTREACHED */

badopen:
	printf(": status %b error %b\n",
		stat, WDCS_BITS, inb(wdc+wd_error), WDERR_BITS);
	du->dk_state = OPENRAW;
	return(1);
}

D 11
wdclose(dev)
	dev_t dev;
{	struct disk *du;
E 11
I 11
wdsetctlr(dev, du) dev_t dev; struct disk *du; {
	int stat;
E 11

D 11
	du = &wddrives[WDUNIT(dev)];
E 11
I 11
	outb(wdc+wd_cyl_lo, du->dk_dd.d_ncylinders);
	outb(wdc+wd_cyl_hi, (du->dk_dd.d_ncylinders)>>8);
	outb(wdc+wd_sdh, WDSD_IBM | (wdunit(dev) << 4) + du->dk_dd.d_ntracks-1);
	outb(wdc+wd_seccnt, du->dk_dd.d_nsectors);
	outb(wdc+wd_command, 0x91);

	while ((stat = inb(wdc+wd_status)) & WDCS_BUSY) ;
	stat = inb(wdc+wd_error);
	return(stat);
}

/* ARGSUSED */
wdclose(dev, flags, fmt)
        dev_t dev;
        int flags, fmt;
{
	register struct disk *du;

	du = &wddrives[wdunit(dev)];
E 11
	du->dk_open-- ;
	/*if (du->dk_open == 0) du->dk_state = CLOSED ; does not work */
}

wdioctl(dev,cmd,addr,flag)
	dev_t dev;
	caddr_t addr;
{
D 11
	int unit = WDUNIT(dev);
E 11
I 11
	int unit = wdunit(dev);
E 11
	register struct disk *du;
	int error = 0;
	struct uio auio;
	struct iovec aiov;
	/*int wdformat();*/

	du = &wddrives[unit];

	switch (cmd) {

	case DIOCGDINFO:
		*(struct disklabel *)addr = du->dk_dd;
		break;

I 11
        case DIOCGPART:
                ((struct partinfo *)addr)->disklab = &du->dk_dd;
                ((struct partinfo *)addr)->part =
                    &du->dk_dd.d_partitions[wdpart(dev)];
                break;

        case DIOCSDINFO:
                if ((flag & FWRITE) == 0)
                        error = EBADF;
                else
                        error = setdisklabel(&du->dk_dd,
					(struct disklabel *)addr,
                         0 /*(dk->dk_state == OPENRAW) ? 0 : dk->dk_openpart*/);
                /*if (error == 0 && dk->dk_state == OPENRAW &&
                    vdreset_drive(vddinfo[unit]))
                        dk->dk_state = OPEN;*/
		wdsetctlr(dev, du);
                break;

        case DIOCWLABEL:
                if ((flag & FWRITE) == 0)
                        error = EBADF;
                else
                        du->dk_wlabel = *(int *)addr;
                break;

        case DIOCWDINFO:
                if ((flag & FWRITE) == 0)
                        error = EBADF;
                else if ((error = setdisklabel(&du->dk_dd, (struct disklabel *)addr,
                  0/*(dk->dk_state == OPENRAW) ? 0 : dk->dk_openpart*/)) == 0) {
                        int wlab;

                        /*if (error == 0 && dk->dk_state == OPENRAW &&
                            vdreset_drive(vddinfo[unit]))
                                dk->dk_state = OPEN; */
			wdsetctlr(dev, du);

                        /* simulate opening partition 0 so write succeeds */
                        /* dk->dk_openpart |= (1 << 0);            /* XXX */
                        wlab = du->dk_wlabel;
                        du->dk_wlabel = 1;
                        error = writedisklabel(dev, wdstrategy, &du->dk_dd,wdpart(dev));
                        /*dk->dk_openpart = dk->dk_copenpart | dk->dk_bopenpart;*/
                        du->dk_wlabel = wlab;
                }
                break;

#ifdef notyet
E 11
	case DIOCGDINFOP:
		*(struct disklabel **)addr = &(du->dk_dd);
		break;

D 11
#ifdef notyet
E 11
	case DIOCWFORMAT:
		if ((flag & FWRITE) == 0)
			error = EBADF;
		else {
			register struct format_op *fop;

			fop = (struct format_op *)addr;
			aiov.iov_base = fop->df_buf;
			aiov.iov_len = fop->df_count;
			auio.uio_iov = &aiov;
			auio.uio_iovcnt = 1;
			auio.uio_resid = fop->df_count;
			auio.uio_segflg = 0;
			auio.uio_offset =
D 11
				fop->df_startblk * du->dk_dd.dk_secsize;
E 11
I 11
				fop->df_startblk * du->dk_dd.d_secsize;
E 11
			error = physio(wdformat, &rwdbuf[unit], dev, B_WRITE,
				minphys, &auio);
			fop->df_count -= auio.uio_resid;
			fop->df_reg[0] = du->dk_status;
			fop->df_reg[1] = du->dk_error;
		}
		break;
#endif

	default:
		error = ENOTTY;
		break;
	}
	return (error);
}

/*wdformat(bp)
	struct buf *bp;
{

	bp->b_flags |= B_FORMAT;
	return (wdstrategy(bp));
}*/

/*
 * Routines to do raw IO for a unit.
 */
wdread(dev, uio)			/* character read routine */
	dev_t dev;
	struct uio *uio;
{
D 11
	int unit = WDUNIT(dev) ;
E 11
I 11
	int unit = wdunit(dev) ;
E 11

	if (unit >= NWD) return(ENXIO);
	return(physio(wdstrategy, &rwdbuf[unit], dev, B_READ, minphys, uio));
}


wdwrite(dev, uio)			/* character write routine */
	dev_t dev;
	struct uio *uio;
{
D 11
	int unit = WDUNIT(dev) ;
E 11
I 11
	int unit = wdunit(dev) ;
E 11

	if (unit >= NWD) return(ENXIO);
	return(physio(wdstrategy, &rwdbuf[unit], dev, B_WRITE, minphys, uio));
}

wdsize(dev)
	dev_t dev;
{
D 11
	register unit = WDUNIT(dev) ;
	register xunit = minor(dev) & 07;
E 11
I 11
	register unit = wdunit(dev);
	register part = wdpart(dev);
E 11
	register struct disk *du;
	register val ;

D 2
	return(8704);
E 2
I 2
D 4
	return(12144);
E 4
I 4
D 11
	return(21600);
E 4
E 2
#ifdef notdef
E 11
	if (unit >= NWD) return(-1);
D 11
	if (wddrives[unit].dk_state == 0) /*{
		val = wdopen (dev, 0) ;
		if (val < 0) return (val) ;
	}*/	return (-1) ;
E 11
I 11
	if (wddrives[unit].dk_state == 0) {
		val = wdopen (dev, 0);
		if (val < 0)
			return (-1);
	}
E 11
	du = &wddrives[unit];
D 11
	return((int)((u_long)du->dk_dd.dk_partition[xunit].nblocks *
		du->dk_dd.dk_secsize / 512));
#endif
E 11
I 11
	return((int)((u_long)du->dk_dd.d_partitions[part].p_size *
		du->dk_dd.d_secsize / 512));
E 11
}

I 11
extern        char *vmmap;            /* poor name! */

E 11
wddump(dev)			/* dump core after a system crash */
	dev_t dev;
{
D 11
#ifdef notyet
E 11
	register struct disk *du;	/* disk unit to do the IO */
D 11
	register struct wd1010 *wdp = (struct wd1010 *) VA_WD;
E 11
	register struct bt_bad *bt_ptr;
	long	num;			/* number of sectors to write */
D 11
	int	unit, xunit;
E 11
I 11
	int	unit, part;
E 11
	long	cyloff, blknum, blkcnt;
D 11
	long	cylin, head, sector;
E 11
I 11
	long	cylin, head, sector, stat;
E 11
	long	secpertrk, secpercyl, nblocks, i;
D 11
	register char *addr;
	char	*end;
	extern	int dumplo, totalclusters;
E 11
I 11
	char *addr;
	extern	int Maxmem;
E 11
	static  wddoingadump = 0 ;
I 11
	extern CMAP1;
	extern char CADDR1[];
E 11

D 11
	addr = (char *) PA_RAM;		/* starting address */
E 11
I 11
	
#ifdef ARGO
outb(0x461,0);	/* disable failsafe timer */
#endif
	addr = (char *) 0;		/* starting address */
E 11
	/* size of memory to dump */
D 11
	num = totalclusters * CLSIZE - PA_RAM / PGSIZE;
	unit = WDUNIT(dev) ;		/* eventually support floppies? */
	xunit = minor(dev) & 7;		/* file system */
E 11
I 11
	num = Maxmem;
	unit = wdunit(dev);		/* eventually support floppies? */
	part = wdpart(dev);		/* file system */
E 11
	/* check for acceptable drive number */
	if (unit >= NWD) return(ENXIO);

	du = &wddrives[unit];
	/* was it ever initialized ? */
	if (du->dk_state < OPEN) return (ENXIO) ;

	/* Convert to disk sectors */
D 11
	num = (u_long) num * PGSIZE / du->dk_dd.dk_secsize;
E 11
I 11
	num = (u_long) num * NBPG / du->dk_dd.d_secsize;
E 11

	/* check if controller active */
	/*if (wdtab.b_active) return(EFAULT); */
	if (wddoingadump) return(EFAULT);

D 11
	secpertrk = du->dk_dd.dk_nsectors;
	secpercyl = du->dk_dd.dk_secpercyl;
	nblocks = du->dk_dd.dk_partition[xunit].nblocks;
	cyloff = du->dk_dd.dk_partition[xunit].cyloff;
E 11
I 11
	secpertrk = du->dk_dd.d_nsectors;
	secpercyl = du->dk_dd.d_secpercyl;
	nblocks = du->dk_dd.d_partitions[part].p_size;
	cyloff = du->dk_dd.d_partitions[part].p_offset / secpercyl;
E 11

I 11
/*pg("xunit %x, nblocks %d, dumplo %d num %d\n", part,nblocks,dumplo,num);*/
E 11
	/* check transfer bounds against partition size */
D 11
	if ((dumplo < 0) || ((dumplo + num) >= nblocks))
E 11
I 11
	if ((dumplo < 0) || ((dumplo + num) > nblocks))
E 11
		return(EINVAL);

	/*wdtab.b_active = 1;		/* mark controller active for if we
					   panic during the dump */
	wddoingadump = 1  ;  i = 100000 ;
D 10
	while ((wdp->wd_status & WDCS_BUSY) && (i-- > 0)) nulldev() ;
E 10
I 10
D 11
	while ((wdp->wd_status & WDCS_BUSY) && (i-- > 0)) nullop() ;
E 10
	inb(wdc+wd_sdh = du->dk_sdh ;
	inb(wdc+wd_command = WDCC_RESTORE | WD_STEP;
D 10
	while (inb(wdc+wd_status & WDCS_BUSY) nulldev() ;
E 10
I 10
	while (inb(wdc+wd_status & WDCS_BUSY) nullop() ;
E 11
I 11
	while ((inb(wdc+wd_status) & WDCS_BUSY) && (i-- > 0)) ;
	outb(wdc+wd_sdh, WDSD_IBM | (unit << 4));
	outb(wdc+wd_command, WDCC_RESTORE | WD_STEP);
	while (inb(wdc+wd_status) & WDCS_BUSY) ;

	/* some compaq controllers require this ... */
	wdsetctlr(dev, du);
E 11
E 10
	
	blknum = dumplo;
	while (num > 0) {
#ifdef notdef
		if (blkcnt > MAXTRANSFER) blkcnt = MAXTRANSFER;
		if ((blknum + blkcnt - 1) / secpercyl != blknum / secpercyl)
			blkcnt = secpercyl - (blknum % secpercyl);
			    /* keep transfer within current cylinder */
#endif
I 11
D 13
		pmap_enter(pmap_kernel(), vmmap, addr, VM_PROT_READ, TRUE);
E 13
I 13
		pmap_enter(kernel_pmap, vmmap, addr, VM_PROT_READ, TRUE);
E 13
E 11

		/* compute disk address */
		cylin = blknum / secpercyl;
		head = (blknum % secpercyl) / secpertrk;
		sector = blknum % secpertrk;
D 11
		sector++;		/* origin 1 */
E 11
D 2
		cylin += cyloff + 290;
E 2
I 2
		cylin += cyloff;
E 2

I 11
#ifdef notyet
E 11
		/* 
		 * See if the current block is in the bad block list.
		 * (If we have one.)
		 */
	    		for (bt_ptr = dkbad[unit].bt_bad;
				bt_ptr->bt_cyl != -1; bt_ptr++) {
			if (bt_ptr->bt_cyl > cylin)
				/* Sorted list, and we passed our cylinder.
					quit. */
				break;
			if (bt_ptr->bt_cyl == cylin &&
				bt_ptr->bt_trksec == (head << 8) + sector) {
			/*
			 * Found bad block.  Calculate new block addr.
			 * This starts at the end of the disk (skip the
			 * last track which is used for the bad block list),
			 * and works backwards to the front of the disk.
			 */
D 11
				blknum = (du->dk_dd.dk_secperunit)
					- du->dk_dd.dk_nsectors
E 11
I 11
				blknum = (du->dk_dd.d_secperunit)
					- du->dk_dd.d_nsectors
E 11
					- (bt_ptr - dkbad[unit].bt_bad) - 1;
				cylin = blknum / secpercyl;
				head = (blknum % secpercyl) / secpertrk;
				sector = blknum % secpertrk;
				break;
			}

I 11
#endif
		sector++;		/* origin 1 */

E 11
		/* select drive.     */
D 11
		inb(wdc+wd_sdh = du->dk_sdh | (head&07);
D 10
		while ((inb(wdc+wd_status & WDCS_READY) == 0) nulldev();
E 10
I 10
		while ((inb(wdc+wd_status & WDCS_READY) == 0) nullop();
E 11
I 11
		outb(wdc+wd_sdh, WDSD_IBM | (unit<<4) | (head & 0xf));
		while ((inb(wdc+wd_status) & WDCS_READY) == 0) ;
E 11
E 10

		/* transfer some blocks */
D 11
		inb(wdc+wd_sector = sector;
		inb(wdc+wd_seccnt = 1;
		inb(wdc+wd_cyl_lo = cylin;
		if (du->dk_dd.dk_ntracks > 8) { 
			if (head > 7)
				inb(wdc+wd_precomp = 0;	/* set 3rd head bit */
			else
				inb(wdc+wd_precomp = 0xff;	/* set 3rd head bit */
		}
		inb(wdc+wd_cyl_hi = cylin >> 8;
E 11
I 11
		outb(wdc+wd_sector, sector);
		outb(wdc+wd_seccnt,1);
		outb(wdc+wd_cyl_lo, cylin);
		outb(wdc+wd_cyl_hi, cylin >> 8);
E 11
#ifdef notdef
		/* lets just talk about this first...*/
D 11
		printf ("sdh 0%o sector %d cyl %d addr 0x%x\n",
			wdp->wd_sdh, wdp->wd_sector,
			wdp->wd_cyl_hi*256+wdp->wd_cyl_lo, addr) ;
		for (i=10000; i > 0 ; i--)
			;
		continue;
E 11
I 11
		pg ("sdh 0%o sector %d cyl %d addr 0x%x",
			inb(wdc+wd_sdh), inb(wdc+wd_sector),
			inb(wdc+wd_cyl_hi)*256+inb(wdc+wd_cyl_lo), addr) ;
E 11
#endif
D 11
		inb(wdc+wd_command = WDCC_WRITE;
E 11
I 11
#ifdef ODYSSEUS
if(cylin < 46 || cylin > 91)pg("oops");
#endif
#ifdef PRIAM
if(cylin < 40 || cylin > 79)pg("oops");
#endif
		outb(wdc+wd_command, WDCC_WRITE);
E 11
		
		/* Ready to send data?	*/
D 10
		while ((inb(wdc+wd_status & WDCS_DRQ) == 0) nulldev();
E 10
I 10
D 11
		while ((inb(wdc+wd_status & WDCS_DRQ) == 0) nullop();
E 10
		if (inb(wdc+wd_status & WDCS_ERR) return(EIO) ;
E 11
I 11
		while ((inb(wdc+wd_status) & WDCS_DRQ) == 0) ;
		if (inb(wdc+wd_status) & WDCS_ERR) return(EIO) ;
E 11

D 11
		end = (char *)addr + du->dk_dd.dk_secsize;
		for (; addr < end; addr += 8) {
			wdp->wd_data = addr[0];
			wdp->wd_data = addr[1];
			wdp->wd_data = addr[2];
			wdp->wd_data = addr[3];
			wdp->wd_data = addr[4];
			wdp->wd_data = addr[5];
			wdp->wd_data = addr[6];
			wdp->wd_data = addr[7];
		}
		if (inb(wdc+wd_status & WDCS_ERR) return(EIO) ;
E 11
I 11
		outsw (wdc+wd_data, CADDR1+((int)addr&(NBPG-1)), 256);
		(int) addr += 512;

		if (inb(wdc+wd_status) & WDCS_ERR) return(EIO) ;
E 11
		/* Check data request (should be done).         */
D 11
		if (inb(wdc+wd_status & WDCS_DRQ) return(EIO) ;
E 11
I 11
		if (inb(wdc+wd_status) & WDCS_DRQ) return(EIO) ;
E 11

		/* wait for completion */
D 11
		for ( i = 1000000 ; inb(wdc+wd_status & WDCS_BUSY ; i--) {
E 11
I 11
		for ( i = 1000000 ; inb(wdc+wd_status) & WDCS_BUSY ; i--) {
E 11
				if (i < 0) return (EIO) ;
D 10
				nulldev () ;
E 10
I 10
D 11
				nullop () ;
E 11
E 10
		}
		/* error check the xfer */
D 11
		if (inb(wdc+wd_status & WDCS_ERR) return(EIO) ;
E 11
I 11
		if (inb(wdc+wd_status) & WDCS_ERR) return(EIO) ;
E 11
		/* update block count */
		num--;
		blknum++ ;
D 11
#ifdef	WDDEBUG
E 11
if (num % 100 == 0) printf(".") ;
D 11
#endif
E 11
	}
	return(0);
D 11
#endif
E 11
}
#endif
E 1
