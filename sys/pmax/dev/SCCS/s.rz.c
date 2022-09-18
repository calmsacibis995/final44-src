h55366
s 00003/00007/01064
d D 8.4 95/06/02 17:26:14 ralph 15 14
c final changes for pmax 4.4-Lite II release
e
s 00149/00082/00922
d D 8.3 94/11/30 10:52:27 mckusick 14 13
c get disk and block size when opening device rather than probe time (from ralph)
e
s 00001/00001/01003
d D 8.2 94/07/03 14:45:35 mckusick 13 12
c handle SCSI II devices (from Ralph)
e
s 00002/00002/01001
d D 8.1 93/07/29 11:06:49 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00066/00035/00937
d D 7.10 93/07/29 11:06:12 mckusick 11 9
c fix swap sizing bug
e
s 00002/00002/00970
d R 8.1 93/06/10 22:39:08 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00970
d D 7.9 93/05/09 15:49:14 ralph 9 8
c use comments after #endif
e
s 00023/00024/00949
d D 7.8 92/10/24 14:07:01 ralph 8 7
c changes for buf->b_actf
e
s 00002/00002/00971
d D 7.7 92/10/11 11:24:40 bostic 7 6
c use pmax as top directory, not mips
e
s 00017/00016/00956
d D 7.6 92/10/11 11:13:33 bostic 6 5
c make kernel includes standard
e
s 00001/00001/00971
d D 7.5 92/07/27 21:19:29 ralph 5 4
c use min() not MIN()
e
s 00001/00001/00971
d D 7.4 92/06/20 12:18:43 ralph 4 3
c should declare readdisklabel correctly but then have to fix arg types.
e
s 00215/00192/00757
d D 7.3 92/04/19 08:50:54 ralph 3 2
c added disk label support.
e
s 00002/00006/00947
d D 7.2 92/03/29 20:40:11 ralph 2 1
c remove debug stuff
e
s 00953/00000/00000
d D 7.1 92/01/07 18:29:23 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 12
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson of Lawrence Berkeley Laboratory and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SCSI CCS (Command Command Set) disk driver.
D 3
 * NOTE: The name was changed from "sd" to "rz" for DEC compatibility.
E 3
I 3
 * NOTE: The name was changed from "sd" to "rz" for DEC naming compatibility.
E 3
 * I guess I can't avoid confusion someplace.
 */
#include "rz.h"
#if NRZ > 0

D 6
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "errno.h"
I 3
#include "fcntl.h"
#include "ioctl.h"
E 3
#include "dkstat.h"
#include "disklabel.h"
#include "malloc.h"
I 3
#include "proc.h"
#include "uio.h"
#include "stat.h"
#include "syslog.h"
#include "ufs/ffs/fs.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/dkstat.h>
#include <sys/disklabel.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/syslog.h>
E 6
D 4
#include "ufs/ufs/ufs_extern.h"
E 4
E 3

D 6
#include "device.h"
#include "scsi.h"
E 6
I 6
D 15
#include <ufs/ffs/fs.h>

E 15
D 7
#include <mips/dev/device.h>
#include <mips/dev/scsi.h>
E 7
I 7
#include <pmax/dev/device.h>
#include <pmax/dev/scsi.h>
E 7
E 6
D 3
#include "devDiskLabel.h"
E 3

D 3
#include "proc.h"
#include "uio.h"

extern void printf();
extern void bcopy();
extern void disksort();
E 3
extern int splbio();
extern void splx();
extern int physio();
I 4
D 11
extern char *readdisklabel();
E 11
E 4

int	rzprobe();
void	rzstrategy(), rzstart(), rzdone();

struct	driver rzdriver = {
	"rz", rzprobe, rzstart, rzdone,
};

struct	size {
	u_long	strtblk;
D 3
	u_long	endblk;
	int	nblocks;
E 3
I 3
	u_long	nblocks;
E 3
};

D 3
struct rzinfo {
	struct	size part[8];
};

E 3
/*
 * Since the SCSI standard tends to hide the disk structure, we define
 * partitions in terms of DEV_BSIZE blocks.  The default partition table
D 3
 * (for an unlabeled disk) reserves 512K for a boot area, has an 8 meg
E 3
I 3
 * (for an unlabeled disk) reserves 8K for a boot area, has an 8 meg
E 3
 * root and 32 meg of swap.  The rest of the space on the drive goes in
 * the G partition.  As usual, the C partition covers the entire disk
 * (including the boot area).
 */
D 3
struct rzinfo rzdefaultpart = {
	     1024,   17408,   16384   ,	/* A */
	    17408,   82944,   65536   ,	/* B */
	        0,       0,       0   ,	/* C */
	    17408,  115712,   98304   ,	/* D */
	   115712,  218112,  102400   ,	/* E */
	   218112,       0,       0   ,	/* F */
	    82944,       0,       0   ,	/* G */
	   115712,       0,       0   ,	/* H */
E 3
I 3
D 8
struct size rzdefaultpart[MAXPARTITIONS] = {
E 8
I 8
static struct size rzdefaultpart[MAXPARTITIONS] = {
E 8
	        0,   16384,	/* A */
	    16384,   65536,	/* B */
	        0,       0,	/* C */
	    17408,       0,	/* D */
	   115712,       0,	/* E */
	   218112,       0,	/* F */
	    81920,       0,	/* G */
	   115712,       0,	/* H */
E 3
};

I 3
#define	RAWPART		2	/* 'c' partition */	/* XXX */

E 3
struct rzstats {
	long	rzresets;
	long	rztransfers;
	long	rzpartials;
};

struct	rz_softc {
	struct	scsi_device *sc_sd;	/* physical unit info */
D 3
	int	sc_format_pid;		/* process using "format" mode */
E 3
I 3
	pid_t	sc_format_pid;		/* process using "format" mode */
	u_long	sc_openpart;		/* partitions open */
	u_long	sc_bopenpart;		/* block partitions open */
	u_long	sc_copenpart;		/* character partitions open */
E 3
	short	sc_flags;		/* see below */
	short	sc_type;		/* drive type from INQUIRY cmd */
	u_int	sc_blks;		/* number of blocks on device */
	int	sc_blksize;		/* device block size in bytes */
	int	sc_bshift;		/* convert device blocks to DEV_BSIZE */
	u_int	sc_wpms;		/* average xfer rate in 16bit wds/sec */
D 3
	struct	rzinfo sc_info;		/* drive partition table & label info */
E 3
I 3
	struct	disklabel sc_label;	/* disk label for this disk */
E 3
	struct	rzstats sc_stats;	/* statisic counts */
	struct	buf sc_tab;		/* queue of pending operations */
	struct	buf sc_buf;		/* buf for doing I/O */
	struct	buf sc_errbuf;		/* buf for doing REQUEST_SENSE */
	struct	ScsiCmd sc_cmd;		/* command for controller */
	ScsiGroup1Cmd sc_rwcmd;		/* SCSI cmd if not in "format" mode */
	struct	scsi_fmt_cdb sc_cdb;	/* SCSI cmd if in "format" mode */
	struct	scsi_fmt_sense sc_sense;	/* sense data from last cmd */
I 14
	u_char	sc_capbuf[8];		/* buffer for SCSI_READ_CAPACITY */
E 14
} rz_softc[NRZ];

/* sc_flags values */
D 3
#define	RZF_ALIVE		0x1	/* drive found and ready */
#define	RZF_SENSEINPROGRESS	0x2	/* REQUEST_SENSE command in progress */
E 3
I 3
D 14
#define	RZF_ALIVE		0x01	/* drive found and ready */
#define	RZF_SENSEINPROGRESS	0x02	/* REQUEST_SENSE command in progress */
#define	RZF_HAVELABEL		0x04	/* valid label found on disk */
#define	RZF_WLABEL		0x08	/* label is writeable */
E 14
I 14
#define	RZF_ALIVE		0x0001	/* drive found and ready */
#define	RZF_SENSEINPROGRESS	0x0002	/* REQUEST_SENSE command in progress */
#define	RZF_ALTCMD		0x0004	/* alternate command in progress */
#define	RZF_HAVELABEL		0x0008	/* valid label found on disk */
#define	RZF_WLABEL		0x0010	/* label is writeable */
#define	RZF_WAIT		0x0020	/* waiting for sc_tab to drain */
#define	RZF_REMOVEABLE		0x0040	/* disk is removable */
#define	RZF_TRYSYNC		0x0080	/* try synchronous operation */
#define	RZF_NOERR		0x0100	/* don't print error messages */
E 14
E 3

#ifdef DEBUG
int	rzdebug = 3;
#define RZB_ERROR	0x01
#define RZB_PARTIAL	0x02
#define RZB_PRLABEL	0x04
#endif

D 3
#define	rzunit(x)	((minor(x) >> 3) & 0x7)
E 3
I 3
#define	rzunit(x)	(minor(x) >> 3)
E 3
#define rzpart(x)	(minor(x) & 0x7)
#define	b_cylin		b_resid

/*
 * Table of scsi commands users are allowed to access via "format" mode.
 *  0 means not legal.
 *  1 means legal.
 */
static char legal_cmds[256] = {
/*****  0   1   2   3   4   5   6   7     8   9   A   B   C   D   E   F */
/*00*/	0,  0,  0,  0,  1,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,
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

/*
D 14
 * Test to see if device is present.
 * Return true if found and initialized ok.
E 14
I 14
 * Test to see if the unit is ready and if not, try to make it ready.
 * Also, find the drive capacity.
E 14
 */
D 14
rzprobe(sd)
	register struct scsi_device *sd;
E 14
I 14
static int
rzready(sc)
	register struct rz_softc *sc;
E 14
{
D 14
	register struct rz_softc *sc = &rz_softc[sd->sd_unit];
E 14
	register int tries, i;
D 14
	ScsiInquiryData inqbuf;
	u_char capbuf[8];
E 14
	ScsiClass7Sense *sp;

D 14
	/* init some parameters that don't change */
	sc->sc_sd = sd;
	sc->sc_cmd.sd = sd;
	sc->sc_cmd.unit = sd->sd_unit;
	sc->sc_rwcmd.unitNumber = sd->sd_slave;
E 14
I 14
	/* don't print SCSI errors */
D 15
	sc->sc_flags |= RZF_NOERR;
E 15
I 15
	sc->sc_flags |= RZF_NOERR | RZF_ALTCMD;
E 15
E 14

D 14
	/* try to find out what type of device this is */
	sc->sc_format_pid = 1;		/* force use of sc_cdb */
	sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
	scsiGroup0Cmd(SCSI_INQUIRY, sd->sd_slave, 0, sizeof(inqbuf),
		(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
	sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
	sc->sc_buf.b_bcount = sizeof(inqbuf);
	sc->sc_buf.b_un.b_addr = (caddr_t)&inqbuf;
D 8
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
	sc->sc_buf.b_actf = (struct buf *)0;
	sc->sc_tab.b_actf = &sc->sc_buf;
E 8
	rzstart(sd->sd_unit);
	if (biowait(&sc->sc_buf) ||
	    (i = sizeof(inqbuf) - sc->sc_buf.b_resid) < 5)
		goto bad;
	switch (inqbuf.type) {
	case SCSI_DISK_TYPE:		/* disk */
	case SCSI_WORM_TYPE:		/* WORM */
	case SCSI_ROM_TYPE:		/* CD-ROM */
	case SCSI_OPTICAL_MEM_TYPE:	/* Magneto-optical */
		break;

	default:			/* not a disk */
		goto bad;
	}
	sc->sc_type = inqbuf.type;

	/* see if device is ready */
E 14
I 14
	/* see if the device is ready */
E 14
	for (tries = 10; ; ) {
		sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
D 14
		scsiGroup0Cmd(SCSI_TEST_UNIT_READY, sd->sd_slave, 0, 0,
			(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
E 14
I 14
		scsiGroup0Cmd(SCSI_TEST_UNIT_READY, sc->sc_rwcmd.unitNumber,
			0, 0, (ScsiGroup0Cmd *)sc->sc_cdb.cdb);
E 14
		sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
		sc->sc_buf.b_bcount = 0;
		sc->sc_buf.b_un.b_addr = (caddr_t)0;
D 8
		sc->sc_buf.av_forw = (struct buf *)0;
		sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
		sc->sc_buf.b_actf = (struct buf *)0;
		sc->sc_tab.b_actf = &sc->sc_buf;
E 8

		sc->sc_cmd.cmd = sc->sc_cdb.cdb;
		sc->sc_cmd.cmdlen = sc->sc_cdb.len;
		sc->sc_cmd.buf = (caddr_t)0;
		sc->sc_cmd.buflen = 0;
		/* setup synchronous data transfers if the device supports it */
D 14
		if (tries == 10 && (inqbuf.flags & SCSI_SYNC))
E 14
I 14
		if (tries == 10 && (sc->sc_flags & RZF_TRYSYNC))
E 14
			sc->sc_cmd.flags = SCSICMD_USE_SYNC;
		else
			sc->sc_cmd.flags = 0;

		(*sc->sc_sd->sd_cdriver->d_start)(&sc->sc_cmd);
		if (!biowait(&sc->sc_buf))
			break;
		if (--tries < 0)
D 14
			goto bad;
E 14
I 14
			return (0);
E 14
		if (!(sc->sc_sense.status & SCSI_STATUS_CHECKCOND))
			goto again;
		sp = (ScsiClass7Sense *)sc->sc_sense.sense;
		if (sp->error7 != 0x70)
			goto again;
		if (sp->key == SCSI_CLASS7_UNIT_ATTN && tries != 9) {
			/* drive recalibrating, give it a while */
			DELAY(1000000);
			continue;
		}
		if (sp->key == SCSI_CLASS7_NOT_READY) {
			ScsiStartStopCmd *cp;

			/* try to spin-up disk with start/stop command */
			sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
			cp = (ScsiStartStopCmd *)sc->sc_cdb.cdb;
			cp->command = SCSI_START_STOP;
D 14
			cp->unitNumber = sd->sd_slave;
E 14
I 14
			cp->unitNumber = sc->sc_rwcmd.unitNumber;
E 14
			cp->immed = 0;
			cp->loadEject = 0;
			cp->start = 1;
			cp->pad1 = 0;
			cp->pad2 = 0;
			cp->pad3 = 0;
			cp->pad4 = 0;
			cp->control = 0;
			sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
			sc->sc_buf.b_bcount = 0;
			sc->sc_buf.b_un.b_addr = (caddr_t)0;
D 8
			sc->sc_buf.av_forw = (struct buf *)0;
			sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
			sc->sc_buf.b_actf = (struct buf *)0;
			sc->sc_tab.b_actf = &sc->sc_buf;
E 8
D 14
			rzstart(sd->sd_unit);
E 14
I 14
			rzstart(sc->sc_cmd.unit);
E 14
			if (biowait(&sc->sc_buf))
D 14
				goto bad;
E 14
I 14
				return (0);
E 14
			continue;
		}
	again:
		DELAY(1000);
	}

I 14
	/* print SCSI errors */
D 15
	sc->sc_flags &= ~RZF_NOERR;
E 15
I 15
	sc->sc_flags &= ~(RZF_NOERR | RZF_ALTCMD);
E 15

E 14
	/* find out how big a disk this is */
	sc->sc_cdb.len = sizeof(ScsiGroup1Cmd);
D 14
	scsiGroup1Cmd(SCSI_READ_CAPACITY, sd->sd_slave, 0, 0,
E 14
I 14
	scsiGroup1Cmd(SCSI_READ_CAPACITY, sc->sc_rwcmd.unitNumber, 0, 0,
E 14
		(ScsiGroup1Cmd *)sc->sc_cdb.cdb);
	sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
D 14
	sc->sc_buf.b_bcount = sizeof(capbuf);
	sc->sc_buf.b_un.b_addr = (caddr_t)capbuf;
E 14
I 14
	sc->sc_buf.b_bcount = sizeof(sc->sc_capbuf);
	sc->sc_buf.b_un.b_addr = (caddr_t)sc->sc_capbuf;
E 14
D 8
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
	sc->sc_buf.b_actf = (struct buf *)0;
	sc->sc_tab.b_actf = &sc->sc_buf;
E 8
D 14
	rzstart(sd->sd_unit);
E 14
I 14
	sc->sc_flags |= RZF_ALTCMD;
	rzstart(sc->sc_cmd.unit);
	sc->sc_flags &= ~RZF_ALTCMD;
E 14
	if (biowait(&sc->sc_buf) || sc->sc_buf.b_resid != 0)
I 14
		return (0);
	sc->sc_blks = ((sc->sc_capbuf[0] << 24) | (sc->sc_capbuf[1] << 16) |
		(sc->sc_capbuf[2] << 8) | sc->sc_capbuf[3]) + 1;
	sc->sc_blksize = (sc->sc_capbuf[4] << 24) | (sc->sc_capbuf[5] << 16) |
		(sc->sc_capbuf[6] << 8) | sc->sc_capbuf[7];

	sc->sc_bshift = 0;
	for (i = sc->sc_blksize; i > DEV_BSIZE; i >>= 1)
		++sc->sc_bshift;
	sc->sc_blks <<= sc->sc_bshift;

	return (1);
}

/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
rzprobe(sd)
	register struct scsi_device *sd;
{
	register struct rz_softc *sc = &rz_softc[sd->sd_unit];
	register int i;
	ScsiInquiryData inqbuf;
	ScsiClass7Sense *sp;

	/* init some parameters that don't change */
	sc->sc_sd = sd;
	sc->sc_cmd.sd = sd;
	sc->sc_cmd.unit = sd->sd_unit;
	sc->sc_rwcmd.unitNumber = sd->sd_slave;

	/* try to find out what type of device this is */
	sc->sc_format_pid = 1;		/* force use of sc_cdb */
	sc->sc_flags = RZF_NOERR;	/* don't print SCSI errors */
	sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
	scsiGroup0Cmd(SCSI_INQUIRY, sd->sd_slave, 0, sizeof(inqbuf),
		(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
	sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
	sc->sc_buf.b_bcount = sizeof(inqbuf);
	sc->sc_buf.b_un.b_addr = (caddr_t)&inqbuf;
	sc->sc_buf.b_actf = (struct buf *)0;
	sc->sc_tab.b_actf = &sc->sc_buf;
	rzstart(sd->sd_unit);
	if (biowait(&sc->sc_buf) ||
	    (i = sizeof(inqbuf) - sc->sc_buf.b_resid) < 5)
E 14
		goto bad;
D 3
	sc->sc_blks = (capbuf[0] << 24) | (capbuf[1] << 16) |
		(capbuf[2] << 8) | capbuf[3];
E 3
I 3
D 14
	sc->sc_blks = ((capbuf[0] << 24) | (capbuf[1] << 16) |
		(capbuf[2] << 8) | capbuf[3]) + 1;
E 3
	sc->sc_blksize = (capbuf[4] << 24) | (capbuf[5] << 16) |
		(capbuf[6] << 8) | capbuf[7];
E 14
I 14
	switch (inqbuf.type) {
	case SCSI_DISK_TYPE:		/* disk */
	case SCSI_WORM_TYPE:		/* WORM */
	case SCSI_ROM_TYPE:		/* CD-ROM */
	case SCSI_OPTICAL_MEM_TYPE:	/* Magneto-optical */
		break;
E 14

I 14
	default:			/* not a disk */
		goto bad;
	}
	sc->sc_type = inqbuf.type;
	if (inqbuf.flags & SCSI_SYNC)
		sc->sc_flags |= RZF_TRYSYNC;

	if (!inqbuf.rmb) {
		if (!rzready(sc))
			goto bad;
	}

E 14
	printf("rz%d at %s%d drive %d slave %d", sd->sd_unit,
		sd->sd_cdriver->d_name, sd->sd_ctlr, sd->sd_drive,
		sd->sd_slave);
D 13
	if (inqbuf.version > 1 || i < 36)
E 13
I 13
	if (inqbuf.version > 2 || i < 36)
E 13
		printf(" type 0x%x, qual 0x%x, ver %d",
			inqbuf.type, inqbuf.qualifier, inqbuf.version);
	else {
		char vid[9], pid[17], revl[5];

		bcopy((caddr_t)inqbuf.vendorID, (caddr_t)vid, 8);
		bcopy((caddr_t)inqbuf.productID, (caddr_t)pid, 16);
		bcopy((caddr_t)inqbuf.revLevel, (caddr_t)revl, 4);
		for (i = 8; --i > 0; )
			if (vid[i] != ' ')
				break;
		vid[i+1] = 0;
		for (i = 16; --i > 0; )
			if (pid[i] != ' ')
				break;
		pid[i+1] = 0;
		for (i = 4; --i > 0; )
			if (revl[i] != ' ')
				break;
		revl[i+1] = 0;
		printf(" %s %s rev %s", vid, pid, revl);
	}
	printf(", %d %d byte blocks\n", sc->sc_blks, sc->sc_blksize);
D 14
	if (sc->sc_blksize != DEV_BSIZE) {
E 14
I 14
	if (!inqbuf.rmb && sc->sc_blksize != DEV_BSIZE) {
E 14
		if (sc->sc_blksize < DEV_BSIZE) {
			printf("rz%d: need %d byte blocks - drive ignored\n",
				sd->sd_unit, DEV_BSIZE);
			goto bad;
		}
D 14
		for (i = sc->sc_blksize; i > DEV_BSIZE; i >>= 1)
			++sc->sc_bshift;
		sc->sc_blks <<= sc->sc_bshift;
E 14
	}
	sc->sc_wpms = 32 * (60 * DEV_BSIZE / 2);	/* XXX */
	sc->sc_format_pid = 0;
D 14
	sc->sc_flags = RZF_ALIVE;
E 14
I 14
	sc->sc_flags |= RZF_ALIVE;
	if (inqbuf.rmb)
		sc->sc_flags |= RZF_REMOVEABLE;
E 14
D 3

	/* try to read disk label or partition table information */
	if (rzreadlabel(sc, sd) == 0)
		goto ok;

	/*
	 * We don't have a disk label, build a default partition
	 * table with 'standard' size root & swap and everything else
	 * in the G partition.
	 */
	sc->sc_info = rzdefaultpart;
	/* C gets everything */
	sc->sc_info.part[2].nblocks = sc->sc_blks;
	sc->sc_info.part[2].endblk = sc->sc_blks;
	/* G gets from end of B to end of disk */
	sc->sc_info.part[6].nblocks = sc->sc_blks - sc->sc_info.part[1].endblk;
	sc->sc_info.part[6].endblk = sc->sc_blks;
	/*
	 * We also define the D, E and F paritions as an alternative to
	 * B and G.  D is 48Mb, starts after A and is intended for swapping.
	 * E is 50Mb, starts after D and is intended for /usr. F starts
	 * after E and is what ever is left.
	 */
	if (sc->sc_blks >= sc->sc_info.part[4].endblk) {
		sc->sc_info.part[5].nblocks =
			sc->sc_blks - sc->sc_info.part[4].endblk;
		sc->sc_info.part[5].endblk = sc->sc_blks;
	} else {
		sc->sc_info.part[5].strtblk = 0;
		sc->sc_info.part[3] = sc->sc_info.part[5];
		sc->sc_info.part[4] = sc->sc_info.part[5];
	}
	/*
	 * H is a single partition alternative to E and F.
	 */
	if (sc->sc_blks >= sc->sc_info.part[3].endblk) {
		sc->sc_info.part[7].nblocks =
			sc->sc_blks - sc->sc_info.part[3].endblk;
		sc->sc_info.part[7].endblk = sc->sc_blks;
	} else
		sc->sc_info.part[7].strtblk = 0;

ok:
E 3
	sc->sc_buf.b_flags = 0;
	return (1);

bad:
	/* doesn't exist or not a CCS device */
	sc->sc_format_pid = 0;
	sc->sc_buf.b_flags = 0;
	return (0);
}

/*
D 3
 * Try to read the disk label and fill in the partition table info.
 */
static int
rzreadlabel(sc, sd)
	register struct rz_softc *sc;
	register struct scsi_device *sd;
{
	register struct size *sp;
	Sun_DiskLabel *sunLabelPtr;
	Dec_DiskLabel *decLabelPtr;
	char labelBuffer[DEV_BSIZE];
	int part, error;

	/*
	 * The label of a SCSI disk normally resides in the first sector.
	 * Format and send a SCSI READ command to fetch the sector.
	 */
	sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
	sc->sc_buf.b_bcount = sizeof(labelBuffer);
	sc->sc_buf.b_un.b_addr = labelBuffer;
	sc->sc_buf.b_cylin = SUN_LABEL_SECTOR;
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
	rzstart(sd->sd_unit);
	if (error = biowait(&sc->sc_buf))
		return (error);
	sunLabelPtr = (Sun_DiskLabel *)labelBuffer;
	if (sunLabelPtr->magic == SUN_DISK_MAGIC) {
		/*
		 * XXX - Should really check if label is valid.
		 */
#ifdef DEBUG
		if (rzdebug & RZB_PRLABEL) {
			printf("rz%d: SUN label %s\n", sd->sd_unit,
				sunLabelPtr->asciiLabel);
			printf("  Partitions");
		}
#endif
		sp = sc->sc_info.part;
		for (part = 0; part < DEV_NUM_DISK_PARTS; part++, sp++) {
			sp->strtblk =
				sunLabelPtr->map[part].cylinder *
				sunLabelPtr->numHeads * 
				sunLabelPtr->numSectors;
			sp->nblocks =
				sunLabelPtr->map[part].numBlocks;
			sp->endblk = sp->strtblk + sp->nblocks;
#ifdef DEBUG
			if (rzdebug & RZB_PRLABEL)
				printf(" (%d,%d)", sp->strtblk, sp->nblocks);
#endif
		}
#ifdef DEBUG
		if (rzdebug & RZB_PRLABEL)
			printf("\n");
#endif
		return (0);
	}

	/*
	 * The disk isn't in SUN or UNIX format so try Dec format.
	 * We have to read the right sector first.
	 */
	sc->sc_buf.b_flags = B_BUSY | B_PHYS | B_READ;
	sc->sc_buf.b_bcount = sizeof(labelBuffer);
	sc->sc_buf.b_un.b_addr = labelBuffer;
	sc->sc_buf.b_cylin = DEC_LABEL_SECTOR;
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
	rzstart(sd->sd_unit);
	if (error = biowait(&sc->sc_buf))
		return (error);
	decLabelPtr = (Dec_DiskLabel *)labelBuffer;
	if (decLabelPtr->magic == DEC_LABEL_MAGIC &&
	    decLabelPtr->isPartitioned) {
		/*
		 * XXX - Should really check if label is valid.
		 */
#ifdef DEBUG
		if (rzdebug & RZB_PRLABEL) {
			printf("rz%d: DEC label\n", sd->sd_unit);
			printf("  Partitions");
		}
#endif
		sp = sc->sc_info.part;
		for (part = 0; part < DEV_NUM_DISK_PARTS; part++, sp++) {
			sp->strtblk = decLabelPtr->map[part].startBlock;
			sp->nblocks = decLabelPtr->map[part].numBlocks;
			sp->endblk = sp->strtblk + sp->nblocks;
#ifdef DEBUG
			if (rzdebug & RZB_PRLABEL)
				printf(" (%d,%d)", sp->strtblk, sp->nblocks);
#endif
		}
#ifdef DEBUG
		if (rzdebug & RZB_PRLABEL)
			printf("\n");
#endif
		return (0);
	}
	return (EIO);
}

/*
E 3
 * This routine is called for partial block transfers and non-aligned
 * transfers (the latter only being possible on devices with a block size
 * larger than DEV_BSIZE).  The operation is performed in three steps
 * using a locally allocated buffer:
 *	1. transfer any initial partial block
 *	2. transfer full blocks
 *	3. transfer any final partial block
 */
static void
rzlblkstrat(bp, bsize)
	register struct buf *bp;
	register int bsize;
{
	register struct buf *cbp;
	caddr_t cbuf;
	register int bn, resid;
	register caddr_t addr;

	cbp = (struct buf *)malloc(sizeof(struct buf), M_DEVBUF, M_WAITOK);
	cbuf = (caddr_t)malloc(bsize, M_DEVBUF, M_WAITOK);
	bzero((caddr_t)cbp, sizeof(*cbp));
	cbp->b_proc = curproc;
	cbp->b_dev = bp->b_dev;
	bn = bp->b_blkno;
	resid = bp->b_bcount;
	addr = bp->b_un.b_addr;
#ifdef DEBUG
	if (rzdebug & RZB_PARTIAL)
		printf("rzlblkstrat: bp %x flags %x bn %x resid %x addr %x\n",
		       bp, bp->b_flags, bn, resid, addr);
#endif

	while (resid > 0) {
		register int boff = dbtob(bn) & (bsize - 1);
		register int count;

		if (boff || resid < bsize) {
			rz_softc[rzunit(bp->b_dev)].sc_stats.rzpartials++;
D 5
			count = MIN(resid, bsize - boff);
E 5
I 5
			count = min(resid, bsize - boff);
E 5
			cbp->b_flags = B_BUSY | B_PHYS | B_READ;
			cbp->b_blkno = bn - btodb(boff);
			cbp->b_un.b_addr = cbuf;
			cbp->b_bcount = bsize;
#ifdef DEBUG
			if (rzdebug & RZB_PARTIAL)
				printf(" readahead: bn %x cnt %x off %x addr %x\n",
				       cbp->b_blkno, count, boff, addr);
#endif
			rzstrategy(cbp);
			biowait(cbp);
			if (cbp->b_flags & B_ERROR) {
				bp->b_flags |= B_ERROR;
				bp->b_error = cbp->b_error;
				break;
			}
			if (bp->b_flags & B_READ) {
				bcopy(&cbuf[boff], addr, count);
				goto done;
			}
			bcopy(addr, &cbuf[boff], count);
#ifdef DEBUG
			if (rzdebug & RZB_PARTIAL)
				printf(" writeback: bn %x cnt %x off %x addr %x\n",
				       cbp->b_blkno, count, boff, addr);
#endif
		} else {
			count = resid & ~(bsize - 1);
			cbp->b_blkno = bn;
			cbp->b_un.b_addr = addr;
			cbp->b_bcount = count;
#ifdef DEBUG
			if (rzdebug & RZB_PARTIAL)
				printf(" fulltrans: bn %x cnt %x addr %x\n",
				       cbp->b_blkno, count, addr);
#endif
		}
		cbp->b_flags = B_BUSY | B_PHYS | (bp->b_flags & B_READ);
		rzstrategy(cbp);
		biowait(cbp);
		if (cbp->b_flags & B_ERROR) {
			bp->b_flags |= B_ERROR;
			bp->b_error = cbp->b_error;
			break;
		}
done:
		bn += btodb(count);
		resid -= count;
		addr += count;
#ifdef DEBUG
		if (rzdebug & RZB_PARTIAL)
			printf(" done: bn %x resid %x addr %x\n",
			       bn, resid, addr);
#endif
	}
	free(cbuf, M_DEVBUF);
	free(cbp, M_DEVBUF);
}

void
rzstrategy(bp)
	register struct buf *bp;
{
	register int unit = rzunit(bp->b_dev);
	register int part = rzpart(bp->b_dev);
D 3
	register int bn, sz;
E 3
I 3
D 8
	register u_long bn, sz;
E 8
E 3
	register struct rz_softc *sc = &rz_softc[unit];
I 3
	register struct partition *pp = &sc->sc_label.d_partitions[part];
E 3
D 8
	register int s;
E 8
I 8
	register daddr_t bn;
	register long sz, s;
E 8

	if (sc->sc_format_pid) {
		if (sc->sc_format_pid != curproc->p_pid) {
			bp->b_error = EPERM;
			goto bad;
		}
		bp->b_cylin = 0;
	} else {
		bn = bp->b_blkno;
D 3
		sz = (bp->b_bcount + (DEV_BSIZE - 1)) >> DEV_BSHIFT;
		if (bn < 0 || bn + sz > sc->sc_info.part[part].nblocks) {
			if (bn == sc->sc_info.part[part].nblocks) {
E 3
I 3
D 8
		sz = (bp->b_bcount + DEV_BSIZE - 1) >> DEV_BSHIFT;
		if (bn + sz > pp->p_size) {
E 8
I 8
		sz = howmany(bp->b_bcount, DEV_BSIZE);
		if ((unsigned)bn + sz > pp->p_size) {
			sz = pp->p_size - bn;
E 8
			/* if exactly at end of disk, return an EOF */
D 8
			if (bn == pp->p_size) {
E 8
I 8
			if (sz == 0) {
E 8
E 3
				bp->b_resid = bp->b_bcount;
				goto done;
			}
D 3
			bp->b_error = EINVAL;
E 3
I 3
			/* if none of it fits, error */
D 8
			if (bn >= pp->p_size) {
E 8
I 8
			if (sz < 0) {
E 8
				bp->b_error = EINVAL;
				goto bad;
			}
			/* otherwise, truncate */
D 8
			sz = pp->p_size - bn;
			bp->b_bcount = sz << DEV_BSHIFT;
E 8
I 8
			bp->b_bcount = dbtob(sz);
E 8
		}
		/* check for write to write protected label */
		if (bn + pp->p_offset <= LABELSECTOR &&
#if LABELSECTOR != 0
		    bn + pp->p_offset + sz > LABELSECTOR &&
#endif
		    !(bp->b_flags & B_READ) && !(sc->sc_flags & RZF_WLABEL)) {
			bp->b_error = EROFS;
E 3
			goto bad;
		}
		/*
		 * Non-aligned or partial-block transfers handled specially.
		 */
		s = sc->sc_blksize - 1;
		if ((dbtob(bn) & s) || (bp->b_bcount & s)) {
			rzlblkstrat(bp, sc->sc_blksize);
			goto done;
		}
D 3
		bp->b_cylin = (bn + sc->sc_info.part[part].strtblk) >>
				sc->sc_bshift;
E 3
I 3
		bp->b_cylin = (bn + pp->p_offset) >> sc->sc_bshift;
E 3
	}
	/* don't let disksort() see sc_errbuf */
	while (sc->sc_flags & RZF_SENSEINPROGRESS)
		printf("SENSE\n"); /* XXX */
	s = splbio();
	disksort(&sc->sc_tab, bp);
	if (sc->sc_tab.b_active == 0) {
		sc->sc_tab.b_active = 1;
		rzstart(unit);
	}
	splx(s);
	return;
bad:
	bp->b_flags |= B_ERROR;
done:
	biodone(bp);
}

void
rzstart(unit)
	int unit;
{
	register struct rz_softc *sc = &rz_softc[unit];
	register struct buf *bp = sc->sc_tab.b_actf;
	register int n;

	sc->sc_cmd.buf = bp->b_un.b_addr;
	sc->sc_cmd.buflen = bp->b_bcount;

D 14
	if (sc->sc_format_pid || (sc->sc_flags & RZF_SENSEINPROGRESS)) {
E 14
I 14
	if (sc->sc_format_pid ||
	    (sc->sc_flags & (RZF_SENSEINPROGRESS | RZF_ALTCMD))) {
E 14
		sc->sc_cmd.flags = !(bp->b_flags & B_READ) ?
			SCSICMD_DATA_TO_DEVICE : 0;
		sc->sc_cmd.cmd = sc->sc_cdb.cdb;
		sc->sc_cmd.cmdlen = sc->sc_cdb.len;
	} else {
		if (bp->b_flags & B_READ) {
			sc->sc_cmd.flags = 0;
			sc->sc_rwcmd.command = SCSI_READ_EXT;
		} else {
			sc->sc_cmd.flags = SCSICMD_DATA_TO_DEVICE;
			sc->sc_rwcmd.command = SCSI_WRITE_EXT;
		}
		sc->sc_cmd.cmd = (u_char *)&sc->sc_rwcmd;
		sc->sc_cmd.cmdlen = sizeof(sc->sc_rwcmd);
		n = bp->b_cylin;
		sc->sc_rwcmd.highAddr = n >> 24;
		sc->sc_rwcmd.midHighAddr = n >> 16;
		sc->sc_rwcmd.midLowAddr = n >> 8;
		sc->sc_rwcmd.lowAddr = n;
		n = howmany(bp->b_bcount, sc->sc_blksize);
		sc->sc_rwcmd.highBlockCount = n >> 8;
		sc->sc_rwcmd.lowBlockCount = n;
#ifdef DEBUG
		if ((bp->b_bcount & (sc->sc_blksize - 1)) != 0)
			printf("rz%d: partial block xfer -- %x bytes\n",
				unit, bp->b_bcount);
#endif
		sc->sc_stats.rztransfers++;
		if ((n = sc->sc_sd->sd_dk) >= 0) {
			dk_busy |= 1 << n;
			++dk_seek[n];
			++dk_xfer[n];
			dk_wds[n] += bp->b_bcount >> 6;
		}
	}

	/* tell controller to start this command */
	(*sc->sc_sd->sd_cdriver->d_start)(&sc->sc_cmd);
}

/*
 * This is called by the controller driver when the command is done.
 */
void
rzdone(unit, error, resid, status)
	register int unit;
	int error;		/* error number from errno.h */
	int resid;		/* amount not transfered */
	int status;		/* SCSI status byte */
{
	register struct rz_softc *sc = &rz_softc[unit];
	register struct buf *bp = sc->sc_tab.b_actf;
	register struct scsi_device *sd = sc->sc_sd;
D 14
	extern int cold;
E 14

	if (bp == NULL) {
		printf("rz%d: bp == NULL\n", unit);
		return;
	}
	if (sd->sd_dk >= 0)
		dk_busy &= ~(1 << sd->sd_dk);
	if (sc->sc_flags & RZF_SENSEINPROGRESS) {
		sc->sc_flags &= ~RZF_SENSEINPROGRESS;
D 8
		sc->sc_tab.b_actf = bp = bp->av_forw;	/* remove sc_errbuf */
E 8
I 8
		sc->sc_tab.b_actf = bp = bp->b_actf;	/* remove sc_errbuf */
E 8

		if (error || (status & SCSI_STATUS_CHECKCOND)) {
#ifdef DEBUG
			if (rzdebug & RZB_ERROR)
				printf("rz%d: error reading sense data: error %d scsi status 0x%x\n",
					unit, error, status);
#endif
			/*
			 * We got an error during the REQUEST_SENSE,
			 * fill in no sense for data.
			 */
			sc->sc_sense.sense[0] = 0x70;
			sc->sc_sense.sense[2] = SCSI_CLASS7_NO_SENSE;
D 2
		} else if (!cold
#ifdef DEBUG
			|| (rzdebug & RZB_ERROR)
#endif
		) {
E 2
I 2
D 14
		} else if (!cold) {
E 14
I 14
		} else if (!(sc->sc_flags & RZF_NOERR)) {
E 14
E 2
			printf("rz%d: ", unit);
			scsiPrintSense((ScsiClass7Sense *)sc->sc_sense.sense,
				sizeof(sc->sc_sense.sense) - resid);
		}
	} else if (error || (status & SCSI_STATUS_CHECKCOND)) {
#ifdef DEBUG
D 2
		if (rzdebug & RZB_ERROR)
E 2
I 2
D 14
		if (!cold && (rzdebug & RZB_ERROR))
E 14
I 14
		if (!(sc->sc_flags & RZF_NOERR) && (rzdebug & RZB_ERROR))
E 14
E 2
			printf("rz%d: error %d scsi status 0x%x\n",
				unit, error, status);
#endif
		/* save error info */
		sc->sc_sense.status = status;
		bp->b_flags |= B_ERROR;
		bp->b_error = error;
		bp->b_resid = resid;

		if (status & SCSI_STATUS_CHECKCOND) {
			/*
			 * Start a REQUEST_SENSE command.
			 * Since we are called at interrupt time, we can't
			 * wait for the command to finish; that's why we use
			 * the sc_flags field.
			 */
			sc->sc_flags |= RZF_SENSEINPROGRESS;
			sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
			scsiGroup0Cmd(SCSI_REQUEST_SENSE, sd->sd_slave, 0,
				sizeof(sc->sc_sense.sense),
				(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
			sc->sc_errbuf.b_flags = B_BUSY | B_PHYS | B_READ;
			sc->sc_errbuf.b_bcount = sizeof(sc->sc_sense.sense);
			sc->sc_errbuf.b_un.b_addr = (caddr_t)sc->sc_sense.sense;
D 8
			sc->sc_errbuf.av_forw = bp;
E 8
I 8
			sc->sc_errbuf.b_actf = bp;
E 8
			sc->sc_tab.b_actf = &sc->sc_errbuf;
			rzstart(unit);
			return;
		}
	} else {
		sc->sc_sense.status = status;
		bp->b_resid = resid;
	}

D 8
	sc->sc_tab.b_actf = bp->av_forw;
E 8
I 8
	sc->sc_tab.b_actf = bp->b_actf;
E 8
	biodone(bp);
	if (sc->sc_tab.b_actf)
		rzstart(unit);
D 3
	else
E 3
I 3
	else {
E 3
		sc->sc_tab.b_active = 0;
I 3
		/* finish close protocol */
		if (sc->sc_openpart == 0)
			wakeup((caddr_t)&sc->sc_tab);
	}
E 3
}

I 11
/*
 * Read or constuct a disklabel
 */
void
rzgetinfo(dev)
	dev_t dev;
{
	register int unit = rzunit(dev);
	register struct rz_softc *sc = &rz_softc[unit];
	register struct disklabel *lp = &sc->sc_label;
	register int i;
	char *msg;
	int part;
	extern char *readdisklabel();

	part = rzpart(dev);
	sc->sc_flags |= RZF_HAVELABEL;

I 14
	if (sc->sc_type == SCSI_ROM_TYPE) {
		lp->d_type = DTYPE_SCSI;
		lp->d_secsize = sc->sc_blksize;
		lp->d_nsectors = 100;
		lp->d_ntracks = 1;
		lp->d_ncylinders = (sc->sc_blks / 100) + 1;
		lp->d_secpercyl	= 100;
		lp->d_secperunit = sc->sc_blks;
		lp->d_rpm = 300;
		lp->d_interleave = 1;
		lp->d_flags = D_REMOVABLE;
		lp->d_npartitions = 1;
		lp->d_partitions[0].p_offset = 0;
		lp->d_partitions[0].p_size = sc->sc_blks;
		lp->d_partitions[0].p_fstype = FS_ISO9660;
		lp->d_magic = DISKMAGIC;
		lp->d_magic2 = DISKMAGIC;
		lp->d_checksum = dkcksum(lp);
		return;
	}

E 14
	lp->d_type = DTYPE_SCSI;
	lp->d_secsize = DEV_BSIZE;
	lp->d_secpercyl = 1 << sc->sc_bshift;
	lp->d_npartitions = MAXPARTITIONS;
	lp->d_partitions[part].p_offset = 0;
	lp->d_partitions[part].p_size = sc->sc_blks;

	/*
	 * Now try to read the disklabel
	 */
	msg = readdisklabel(dev, rzstrategy, lp);
	if (msg == NULL)
		return;

	printf("rz%d: WARNING: %s\n", unit, msg);
D 14
	sc->sc_label.d_magic = DISKMAGIC;
	sc->sc_label.d_magic2 = DISKMAGIC;
	sc->sc_label.d_type = DTYPE_SCSI;
	sc->sc_label.d_subtype = 0;
	sc->sc_label.d_typename[0] = '\0';
	sc->sc_label.d_secsize = DEV_BSIZE;
	sc->sc_label.d_secperunit = sc->sc_blks;
	sc->sc_label.d_npartitions = MAXPARTITIONS;
	sc->sc_label.d_bbsize = BBSIZE;
	sc->sc_label.d_sbsize = SBSIZE;
E 14
I 14
	lp->d_magic = DISKMAGIC;
	lp->d_magic2 = DISKMAGIC;
	lp->d_type = DTYPE_SCSI;
	lp->d_subtype = 0;
	lp->d_typename[0] = '\0';
	lp->d_secsize = DEV_BSIZE;
	lp->d_secperunit = sc->sc_blks;
	lp->d_npartitions = MAXPARTITIONS;
D 15
	lp->d_bbsize = BBSIZE;
	lp->d_sbsize = SBSIZE;
E 15
E 14
	for (i = 0; i < MAXPARTITIONS; i++) {
D 14
		sc->sc_label.d_partitions[i].p_size =
			rzdefaultpart[i].nblocks;
		sc->sc_label.d_partitions[i].p_offset =
			rzdefaultpart[i].strtblk;
E 14
I 14
		lp->d_partitions[i].p_size = rzdefaultpart[i].nblocks;
		lp->d_partitions[i].p_offset = rzdefaultpart[i].strtblk;
E 14
	}
D 14
	sc->sc_label.d_partitions[RAWPART].p_size = sc->sc_blks;
E 14
I 14
	lp->d_partitions[RAWPART].p_size = sc->sc_blks;
E 14
}

E 11
int
rzopen(dev, flags, mode, p)
	dev_t dev;
	int flags, mode;
	struct proc *p;
{
	register int unit = rzunit(dev);
	register struct rz_softc *sc = &rz_softc[unit];
I 3
	register struct disklabel *lp;
	register int i;
D 11
	char *err_msg;
E 11
	int part;
	u_long mask;
E 3

D 3
	if (unit >= NRZ)
E 3
I 3
	if (unit >= NRZ || !(sc->sc_flags & RZF_ALIVE))
E 3
		return (ENXIO);
D 3
	if (!(sc->sc_flags & RZF_ALIVE) || suser(p->p_ucred, &p->p_acflag))
E 3
I 3

I 14
	/* make sure disk is ready */
	if (sc->sc_flags & RZF_REMOVEABLE) {
		if (!rzready(sc))
			return (ENXIO);
	}

E 14
	/* try to read disk label and partition table information */
	part = rzpart(dev);
D 11
	lp = &sc->sc_label;
	if (!(sc->sc_flags & RZF_HAVELABEL)) {
		sc->sc_flags |= RZF_HAVELABEL;
		lp->d_secsize = DEV_BSIZE;
		lp->d_secpercyl = 1 << sc->sc_bshift;
		lp->d_npartitions = MAXPARTITIONS;
		lp->d_partitions[part].p_offset = 0;
		lp->d_partitions[part].p_size = sc->sc_blks;
		if (err_msg = readdisklabel(dev, rzstrategy, lp)) {
			printf("rz%d: %s\n", unit, err_msg);
			sc->sc_label.d_magic = DISKMAGIC;
			sc->sc_label.d_magic2 = DISKMAGIC;
			sc->sc_label.d_type = DTYPE_SCSI;
			sc->sc_label.d_subtype = 0;
			sc->sc_label.d_typename[0] = '\0';
			sc->sc_label.d_secsize = DEV_BSIZE;
			sc->sc_label.d_secperunit = sc->sc_blks;
			sc->sc_label.d_npartitions = MAXPARTITIONS;
			sc->sc_label.d_bbsize = BBSIZE;
			sc->sc_label.d_sbsize = SBSIZE;
			for (i = 0; i < MAXPARTITIONS; i++) {
				sc->sc_label.d_partitions[i].p_size =
					rzdefaultpart[i].nblocks;
				sc->sc_label.d_partitions[i].p_offset =
					rzdefaultpart[i].strtblk;
			}
			sc->sc_label.d_partitions[RAWPART].p_size =
				sc->sc_blks;
		}
	}
E 11
I 11
	if (!(sc->sc_flags & RZF_HAVELABEL))
		rzgetinfo(dev);
E 11

I 11
	lp = &sc->sc_label;
E 11
	if (part >= lp->d_npartitions || lp->d_partitions[part].p_size == 0)
E 3
		return (ENXIO);
I 3
	/*
	 * Warn if a partition is opened that overlaps another
	 * already open, unless either is the `raw' partition
	 * (whole disk).
	 */
	mask = 1 << part;
	if ((sc->sc_openpart & mask) == 0 && part != RAWPART) {
		register struct partition *pp;
		u_long start, end;
E 3

I 3
		pp = &lp->d_partitions[part];
		start = pp->p_offset;
		end = pp->p_offset + pp->p_size;
		for (pp = lp->d_partitions, i = 0;
		     i < lp->d_npartitions; pp++, i++) {
			if (pp->p_offset + pp->p_size <= start ||
			    pp->p_offset >= end || i == RAWPART)
				continue;
			if (sc->sc_openpart & (1 << i))
				log(LOG_WARNING,
				    "rz%d%c: overlaps open partition (%c)\n",
				    unit, part + 'a', i + 'a');
		}
	}
	switch (mode) {
	case S_IFCHR:
		sc->sc_copenpart |= mask;
		break;
	case S_IFBLK:
		sc->sc_bopenpart |= mask;
		break;
	}
	sc->sc_openpart |= mask;
E 3
	if (sc->sc_sd->sd_dk >= 0)
		dk_wpms[sc->sc_sd->sd_dk] = sc->sc_wpms;
	return (0);
}

D 3
rzclose(dev, flags)
E 3
I 3
rzclose(dev, flags, mode)
E 3
	dev_t dev;
D 3
	int flags;
E 3
I 3
	int flags, mode;
E 3
{
I 3
	register struct rz_softc *sc = &rz_softc[rzunit(dev)];
	u_long mask = (1 << rzpart(dev));
	int s;

	switch (mode) {
	case S_IFCHR:
		sc->sc_copenpart &= ~mask;
		break;
	case S_IFBLK:
		sc->sc_bopenpart &= ~mask;
		break;
	}
	sc->sc_openpart = sc->sc_copenpart | sc->sc_bopenpart;

	/*
	 * Should wait for I/O to complete on this partition even if
	 * others are open, but wait for work on blkflush().
	 */
	if (sc->sc_openpart == 0) {
		s = splbio();
		while (sc->sc_tab.b_actf)
			sleep((caddr_t)&sc->sc_tab, PZERO - 1);
		splx(s);
		sc->sc_flags &= ~RZF_WLABEL;
	}
E 3
	return (0);
}

int
rzread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct rz_softc *sc = &rz_softc[rzunit(dev)];

	if (sc->sc_format_pid && sc->sc_format_pid != curproc->p_pid)
		return (EPERM);

	return (physio(rzstrategy, (struct buf *)0, dev,
		B_READ, minphys, uio));
}

int
rzwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	register struct rz_softc *sc = &rz_softc[rzunit(dev)];
I 14

	if (sc->sc_type == SCSI_ROM_TYPE)
		return (EROFS);
E 14

	if (sc->sc_format_pid && sc->sc_format_pid != curproc->p_pid)
		return (EPERM);

	return (physio(rzstrategy, (struct buf *)0, dev,
		B_WRITE, minphys, uio));
}

int
rzioctl(dev, cmd, data, flag, p)
	dev_t dev;
D 15
	int cmd;
E 15
I 15
	u_long cmd;
E 15
	caddr_t data;
	int flag;
	struct proc *p;
{
	register struct rz_softc *sc = &rz_softc[rzunit(dev)];
I 3
	int error;
	int flags;
E 3

	switch (cmd) {
	default:
		return (EINVAL);

	case SDIOCSFORMAT:
		/* take this device into or out of "format" mode */
		if (suser(p->p_ucred, &p->p_acflag))
			return (EPERM);

		if (*(int *)data) {
			if (sc->sc_format_pid)
				return (EPERM);
			sc->sc_format_pid = p->p_pid;
		} else
			sc->sc_format_pid = 0;
		return (0);

	case SDIOCGFORMAT:
		/* find out who has the device in format mode */
		*(int *)data = sc->sc_format_pid;
		return (0);

	case SDIOCSCSICOMMAND:
		/*
		 * Save what user gave us as SCSI cdb to use with next
		 * read or write to the char device.
		 */
		if (sc->sc_format_pid != p->p_pid)
			return (EPERM);
		if (legal_cmds[((struct scsi_fmt_cdb *)data)->cdb[0]] == 0)
			return (EINVAL);
		bcopy(data, (caddr_t)&sc->sc_cdb, sizeof(sc->sc_cdb));
		return (0);

	case SDIOCSENSE:
		/*
		 * return the SCSI sense data saved after the last
		 * operation that completed with "check condition" status.
		 */
		bcopy((caddr_t)&sc->sc_sense, data, sizeof(sc->sc_sense));
		return (0);

I 3
	case DIOCGDINFO:
		/* get the current disk label */
		*(struct disklabel *)data = sc->sc_label;
		return (0);

	case DIOCSDINFO:
		/* set the current disk label */
		if (!(flag & FWRITE))
			return (EBADF);
D 8
		return (setdisklabel(&sc->sc_label,
E 8
I 8
		error = setdisklabel(&sc->sc_label,
E 8
			(struct disklabel *)data,
D 8
			(sc->sc_flags & RZF_WLABEL) ? 0 : sc->sc_openpart));
E 8
I 8
			(sc->sc_flags & RZF_WLABEL) ? 0 : sc->sc_openpart);
		return (error);
E 8

D 8
#if 0
E 8
	case DIOCGPART:
		/* return the disk partition data */
		((struct partinfo *)data)->disklab = &sc->sc_label;
		((struct partinfo *)data)->part =
			&sc->sc_label.d_partitions[rzpart(dev)];
		return (0);
D 8
#endif
E 8

	case DIOCWLABEL:
		if (!(flag & FWRITE))
			return (EBADF);
		if (*(int *)data)
			sc->sc_flags |= RZF_WLABEL;
		else
			sc->sc_flags &= ~RZF_WLABEL;
		return (0);

	case DIOCWDINFO:
		/* write the disk label to disk */
		if (!(flag & FWRITE))
			return (EBADF);
		error = setdisklabel(&sc->sc_label,
			(struct disklabel *)data,
			(sc->sc_flags & RZF_WLABEL) ? 0 : sc->sc_openpart);
		if (error)
			return (error);

		/* simulate opening partition 0 so write succeeds */
		flags = sc->sc_flags;
		sc->sc_flags = RZF_ALIVE | RZF_WLABEL;
		error = writedisklabel(dev, rzstrategy, &sc->sc_label);
		sc->sc_flags = flags;
		return (error);
E 3
	}
	/*NOTREACHED*/
}

int
rzsize(dev)
	dev_t dev;
{
	register int unit = rzunit(dev);
I 3
	register int part = rzpart(dev);
E 3
	register struct rz_softc *sc = &rz_softc[unit];

D 3
	if (unit >= NRZ || !(sc->sc_flags & RZF_ALIVE))
E 3
I 3
D 11
	if (unit >= NRZ || !(sc->sc_flags & RZF_ALIVE) ||
	    part >= sc->sc_label.d_npartitions)
E 11
I 11
	if (unit >= NRZ || !(sc->sc_flags & RZF_ALIVE))
E 11
E 3
		return (-1);

I 11
	/*
	 * We get called very early on (via swapconf)
	 * without the device being open so we need to
	 * read the disklabel here.
	 */
	if (!(sc->sc_flags & RZF_HAVELABEL))
		rzgetinfo(dev);

	if (part >= sc->sc_label.d_npartitions)
		return (-1);
E 11
D 3
	return (sc->sc_info.part[rzpart(dev)].nblocks);
E 3
I 3
	return (sc->sc_label.d_partitions[part].p_size);
E 3
}

/*
 * Non-interrupt driven, non-dma dump routine.
 */
int
rzdump(dev)
	dev_t dev;
{
#ifdef notdef
	int part = rzpart(dev);
	int unit = rzunit(dev);
	register struct rz_softc *sc = &rz_softc[unit];
	register struct scsi_device *sd = sc->sc_hd;
	register daddr_t baddr;
	register int maddr;
	register int pages, i;
	int stat;
	extern int lowram;

	/*
	 * Hmm... all vax drivers dump maxfree pages which is physmem minus
	 * the message buffer.  Is there a reason for not dumping the
	 * message buffer?  Savecore expects to read 'dumpsize' pages of
	 * dump, where dumpsys() sets dumpsize to physmem!
	 */
	pages = physmem;

	/* is drive ok? */
	if (unit >= NRZ || (sc->sc_flags & RZF_ALIVE) == 0)
		return (ENXIO);
	/* dump parameters in range? */
	if (dumplo < 0 || dumplo >= sc->sc_info.part[part].nblocks)
		return (EINVAL);
	if (dumplo + ctod(pages) > sc->sc_info.part[part].nblocks)
		pages = dtoc(sc->sc_info.part[part].nblocks - dumplo);
	maddr = lowram;
	baddr = dumplo + sc->sc_info.part[part].strtblk;
	/* scsi bus idle? */
	if (!scsireq(&sc->sc_dq)) {
		scsireset(sd->sd_ctlr);
		sc->sc_stats.rzresets++;
		printf("[ drive %d reset ] ", unit);
	}
	for (i = 0; i < pages; i++) {
#define NPGMB	(1024*1024/NBPG)
		/* print out how many Mbs we have dumped */
		if (i && (i % NPGMB) == 0)
			printf("%d ", i / NPGMB);
#undef NPBMG
		mapin(mmap, (u_int)vmmap, btop(maddr), PG_URKR|PG_CI|PG_V);
		stat = scsi_tt_write(sd->sd_ctlr, sd->sd_drive, sd->sd_slave,
				     vmmap, NBPG, baddr, sc->sc_bshift);
		if (stat) {
			printf("rzdump: scsi write error 0x%x\n", stat);
			return (EIO);
		}
		maddr += NBPG;
		baddr += ctod(1);
	}
	return (0);
D 9
#else notdef
E 9
I 9
#else /* notdef */
E 9
	return (ENXIO);
D 9
#endif notdef
E 9
I 9
#endif /* notdef */
E 9
}
#endif
E 1
