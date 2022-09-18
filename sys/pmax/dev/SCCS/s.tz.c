h11693
s 00001/00001/00771
d D 8.5 95/06/02 17:26:15 ralph 16 15
c final changes for pmax 4.4-Lite II release
e
s 00001/00001/00771
d D 8.4 94/01/11 16:01:49 mckusick 15 14
c fix error message being partially printed on two different terminals (from ralph)
e
s 00001/00001/00771
d D 8.3 94/01/04 17:32:58 mckusick 14 13
c minor typo that didn't make it into the previous version (from ralph)
e
s 00002/00001/00770
d D 8.2 93/11/30 16:12:29 mckusick 13 12
c update from Ralph
e
s 00002/00002/00769
d D 8.1 93/06/29 15:11:43 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00770
d D 7.10 93/06/29 15:11:30 mckusick 11 9
c do not crash if probe is not called
e
s 00002/00002/00769
d R 8.1 93/06/10 22:39:52 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00770
d D 7.9 93/04/13 19:53:04 ralph 9 8
c turn off debug by default
e
s 00049/00019/00722
d D 7.8 92/10/24 14:08:46 ralph 8 7
c changes for buf->b_actf
e
s 00002/00002/00739
d D 7.7 92/10/11 11:24:44 bostic 7 6
c use pmax as top directory, not mips
e
s 00011/00011/00730
d D 7.6 92/10/11 11:13:37 bostic 6 5
c make kernel includes standard
e
s 00001/00001/00740
d D 7.5 92/07/25 18:32:22 ralph 5 4
c allow variable size records for python DAT tape drive.
e
s 00002/00005/00739
d D 7.4 92/04/19 08:46:27 ralph 4 3
c changed debug printfs.
e
s 00330/00052/00414
d D 7.3 92/03/29 20:51:14 ralph 3 2
c working version!
e
s 00005/00009/00461
d D 7.2 92/03/07 09:41:09 ralph 2 1
c fix so it compiles
e
s 00470/00000/00000
d D 7.1 92/01/07 18:29:26 mckusick 1 0
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
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: /sprite/src/kernel/dev/RCS/devSCSITape.c,
 *	v 8.14 89/07/31 17:26:13 mendel Exp $ SPRITE (Berkeley)
 */

/*
 * SCSI CCS (Command Command Set) tape driver.
 */
#include "tz.h"
#if NTZ > 0

D 6
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "errno.h"
#include "file.h"
#include "ioctl.h"
#include "mtio.h"
#include "syslog.h"
I 3
#include "tprintf.h"
E 6
I 6
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/errno.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/mtio.h>
#include <sys/syslog.h>
#include <sys/tprintf.h>
E 6
E 3

D 6
#include "device.h"
#include "scsi.h"
E 6
I 6
D 7
#include <mips/dev/device.h>
#include <mips/dev/scsi.h>
E 7
I 7
#include <pmax/dev/device.h>
#include <pmax/dev/scsi.h>
E 7
E 6

int	tzprobe();
void	tzstart(), tzdone();

struct	driver tzdriver = {
	"tz", tzprobe, tzstart, tzdone,
};

struct	tz_softc {
	struct	scsi_device *sc_sd;	/* physical unit info */
	int	sc_flags;		/* see below */
I 3
	int	sc_tapeid;		/* tape drive id */
	int	sc_blklen;		/* 0 = variable len records */
	long	sc_numblks;		/* number of blocks on tape */
	tpr_t	sc_ctty;		/* terminal for error messages */
E 3
	struct	buf sc_tab;		/* queue of pending operations */
	struct	buf sc_buf;		/* buf for doing I/O */
	struct	buf sc_errbuf;		/* buf for doing REQUEST_SENSE */
	struct	ScsiCmd sc_cmd;		/* command for controller */
	ScsiGroup0Cmd sc_rwcmd;		/* SCSI cmd for read/write */
	struct	scsi_fmt_cdb sc_cdb;	/* SCSI cmd if not read/write */
	struct	scsi_fmt_sense sc_sense;	/* sense data from last cmd */
I 3
	struct	ScsiTapeModeSelectHdr sc_mode;	/* SCSI_MODE_SENSE data */
	char	sc_modelen;		/* SCSI_MODE_SENSE data length */
E 3
} tz_softc[NTZ];

/* sc_flags values */
#define	TZF_ALIVE		0x01	/* drive found and ready */
#define	TZF_SENSEINPROGRESS	0x02	/* REQUEST_SENSE command in progress */
#define	TZF_ALTCMD		0x04	/* alternate command in progress */
#define	TZF_WRITTEN		0x08	/* tape has been written to */
#define	TZF_OPEN		0x10	/* device is open */
#define	TZF_WAIT		0x20	/* waiting for sc_tab to drain */
I 3
#define TZF_SEENEOF		0x40	/* seen file mark on read */
E 3

/* bits in minor device */
D 3
#define	tzunit(x)	(minor(x) >> 1)	/* tz%d unit number */
#define TZ_NOREWIND	0x1		/* don't rewind on close */
E 3
I 3
#define	tzunit(x)	(minor(x) >> 4)	/* tz%d unit number */
#define TZ_NOREWIND	0x01		/* don't rewind on close */
#define TZ_HIDENSITY	0x02
#define TZ_EXSFMK	0x04
#define TZ_FIXEDBLK	0x08
E 3

D 3
#define	INF	(daddr_t)1000000L	/* a block number that won't exist */

E 3
#ifdef DEBUG
D 9
int	tzdebug = 1;
E 9
I 9
int	tzdebug = 0;
E 9
#endif

/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
tzprobe(sd)
	struct scsi_device *sd;
{
	register struct tz_softc *sc = &tz_softc[sd->sd_unit];
	register int i;
	ScsiInquiryData inqbuf;
	ScsiClass7Sense *sp;

D 3
	printf("tzprobe()\n"); /* XXX */
E 3
	/* init some parameters that don't change */
	sc->sc_sd = sd;
	sc->sc_cmd.sd = sd;
	sc->sc_cmd.unit = sd->sd_unit;
I 3
	sc->sc_cmd.flags = 0;
E 3
	sc->sc_rwcmd.unitNumber = sd->sd_slave;
D 3
/*	sc->sc_rwcmd.highAddr = 1;	/* count in blocks */
E 3

	/* try to find out what type of device this is */
	sc->sc_flags = TZF_ALTCMD;	/* force use of sc_cdb */
	sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
	scsiGroup0Cmd(SCSI_INQUIRY, sd->sd_slave, 0, sizeof(inqbuf),
		(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
	sc->sc_buf.b_flags = B_BUSY | B_READ;
	sc->sc_buf.b_bcount = sizeof(inqbuf);
	sc->sc_buf.b_un.b_addr = (caddr_t)&inqbuf;
D 8
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
	sc->sc_buf.b_actf = (struct buf *)0;
	sc->sc_buf.b_actb = &sc->sc_tab.b_actf;
	sc->sc_tab.b_actf = &sc->sc_buf;
	sc->sc_tab.b_actb = &sc->sc_buf.b_actf;
E 8
	tzstart(sd->sd_unit);
	if (biowait(&sc->sc_buf) ||
	    (i = sizeof(inqbuf) - sc->sc_buf.b_resid) < 5)
		goto bad;
D 3
	if (inqbuf.type != SCSI_TAPE_TYPE)
E 3
I 3
	if (inqbuf.type != SCSI_TAPE_TYPE || !inqbuf.rmb)
E 3
		goto bad;

	/* check for device ready to clear UNIT_ATTN */
	sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
	scsiGroup0Cmd(SCSI_TEST_UNIT_READY, sd->sd_slave, 0, 0,
		(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
	sc->sc_buf.b_flags = B_BUSY | B_READ;
	sc->sc_buf.b_bcount = 0;
	sc->sc_buf.b_un.b_addr = (caddr_t)0;
D 8
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
	sc->sc_buf.b_actf = (struct buf *)0;
	sc->sc_buf.b_actb = &sc->sc_tab.b_actf;
	sc->sc_tab.b_actf = &sc->sc_buf;
	sc->sc_tab.b_actb = &sc->sc_buf.b_actf;
E 8
	tzstart(sd->sd_unit);
	(void) biowait(&sc->sc_buf);

	sc->sc_flags = TZF_ALIVE;
I 3
	sc->sc_modelen = 12;
E 3
	sc->sc_buf.b_flags = 0;
D 3
	printf("tz%d at %s%d drive %d slave %d\n", sd->sd_unit,
E 3
I 3
	printf("tz%d at %s%d drive %d slave %d", sd->sd_unit,
E 3
		sd->sd_cdriver->d_name, sd->sd_ctlr, sd->sd_drive,
		sd->sd_slave);
I 3
	if (i == 5 && inqbuf.version == 1 && inqbuf.qualifier == 0x50) {
		printf(" TK50\n");
		sc->sc_tapeid = MT_ISTK50;
D 13
	} else if (i == 5 && inqbuf.version == 1 && inqbuf.qualifier == 0) {
E 13
I 13
D 14
	} else if (i == 5 && inqbuf.version == 1 && inqbuf.qualifier == 0 &&
E 14
I 14
	} else if (i >= 5 && inqbuf.version == 1 && inqbuf.qualifier == 0 &&
E 14
	    inqbuf.length == 0) {
E 13
		/* assume Emultex MT02 controller */
		printf(" MT02\n");
		sc->sc_tapeid = MT_ISMT02;
	} else if (inqbuf.version > 2 || i < 36) {
		printf(" GENERIC SCSI tape device: qual 0x%x, ver %d\n",
			inqbuf.qualifier, inqbuf.version);
		sc->sc_tapeid = 0;
	} else {
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
		printf(" %s %s rev %s\n", vid, pid, revl);

		if (bcmp("EXB-8200", pid, 8) == 0) {
			sc->sc_tapeid = MT_ISEXABYTE;
			sc->sc_modelen = 17;
		} else if (bcmp("VIPER 150", pid, 9) == 0) {
			sc->sc_tapeid = MT_ISVIPER1;
		} else if (bcmp("Python 25501", pid, 12) == 0) {
			sc->sc_tapeid = MT_ISPYTHON;
		} else if (bcmp("HP35450A", pid, 8) == 0) {
#if 0
			/* XXX "extra" stat makes the HP drive happy at boot time */
			stat = scsi_test_unit_rdy(ctlr, slave, unit);
#endif
			sc->sc_tapeid = MT_ISHPDAT;
		} else if (bcmp("123107 SCSI", pid, 11) == 0) {
			sc->sc_tapeid = MT_ISMFOUR;
		} else {
			printf("tz%d: assuming GENERIC SCSI tape device\n",
				sd->sd_unit,
				inqbuf.type, inqbuf.qualifier, inqbuf.version);
			sc->sc_tapeid = 0;
		}
	}
E 3
	return (1);

bad:
	/* doesn't exist or not a CCS device */
	sc->sc_flags = 0;
	sc->sc_buf.b_flags = 0;
	return (0);
}

/*
 * Perform a special tape command on a SCSI Tape drive.
 */
D 3
tzcommand(dev, command, code, count)
E 3
I 3
tzcommand(dev, command, code, count, data)
E 3
	dev_t dev;
	int command;
	int code;
	int count;
I 3
	caddr_t data;
E 3
{
	register struct tz_softc *sc = &tz_softc[tzunit(dev)];
I 3
	register ScsiGroup0Cmd *c;
E 3
	int s, error;

	s = splbio();
I 3
	/* wait for pending operations to finish */
E 3
	while (sc->sc_tab.b_actf) {
		sc->sc_flags |= TZF_WAIT;
		sleep(&sc->sc_flags, PZERO);
	}
	sc->sc_flags |= TZF_ALTCMD;	/* force use of sc_cdb */
	sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
D 3
	scsiGroup0Cmd(command, sc->sc_sd->sd_slave,
		(code << 16) | ((count >> 8) & 0xFFFF), count & 0xFF,
		(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
	sc->sc_buf.b_flags = B_BUSY | B_READ;
	sc->sc_buf.b_bcount = 0;
	sc->sc_buf.b_un.b_addr = (caddr_t)0;
E 3
I 3
	c = (ScsiGroup0Cmd *)sc->sc_cdb.cdb;
	c->command = command;
	c->unitNumber = sc->sc_sd->sd_slave;
	c->highAddr = code;
	c->midAddr = count >> 16;
	c->lowAddr = count >> 8;
	c->blockCount = count;
	c->control = 0;
	if (command == SCSI_MODE_SELECT)
		sc->sc_buf.b_flags = B_BUSY;
	else {
		sc->sc_buf.b_flags = B_BUSY | B_READ;
#if 0
		/* this seems to work but doesn't give us a speed advantage */
		if (command == SCSI_TEST_UNIT_READY)
			sc->sc_cmd.flags |= SCSICMD_USE_SYNC;
#endif
	}
	sc->sc_buf.b_bcount = data ? count : 0;
	sc->sc_buf.b_un.b_addr = data;
E 3
D 8
	sc->sc_buf.av_forw = (struct buf *)0;
	sc->sc_tab.b_actf = sc->sc_tab.b_actl = &sc->sc_buf;
E 8
I 8
	sc->sc_buf.b_actf = (struct buf *)0;
	sc->sc_buf.b_actb = &sc->sc_tab.b_actf;
	sc->sc_tab.b_actf = &sc->sc_buf;
	sc->sc_tab.b_actb = &sc->sc_buf.b_actf;
E 8
	tzstart(sc->sc_sd->sd_unit);
	error = biowait(&sc->sc_buf);
	sc->sc_flags &= ~TZF_ALTCMD;	/* force use of sc_cdb */
	sc->sc_buf.b_flags = 0;
I 3
	sc->sc_cmd.flags = 0;
	if (sc->sc_buf.b_resid)
		printf("tzcommand: resid %d\n", sc->sc_buf.b_resid); /* XXX */
	if (error == 0)
		switch (command) {
		case SCSI_SPACE:
		case SCSI_WRITE_EOF:
		case SCSI_REWIND:
			sc->sc_flags &= ~TZF_SEENEOF;
		}
E 3
	splx(s);
	return (error);
}

void
tzstart(unit)
	int unit;
{
	register struct tz_softc *sc = &tz_softc[unit];
	register struct buf *bp = sc->sc_tab.b_actf;
	register int n;
D 2
	extern int sii_debug; /* XXX */
E 2

	sc->sc_cmd.buf = bp->b_un.b_addr;
	sc->sc_cmd.buflen = bp->b_bcount;

	if (sc->sc_flags & (TZF_SENSEINPROGRESS | TZF_ALTCMD)) {
D 2
		sc->sc_cmd.dataToDevice = !(bp->b_flags & B_READ);
E 2
I 2
D 3
		sc->sc_cmd.flags = !(bp->b_flags & B_READ) ?
			SCSICMD_DATA_TO_DEVICE : 0;
E 3
I 3
		if (bp->b_flags & B_READ)
			sc->sc_cmd.flags &= ~SCSICMD_DATA_TO_DEVICE;
		else
			sc->sc_cmd.flags |= SCSICMD_DATA_TO_DEVICE;
E 3
E 2
		sc->sc_cmd.cmd = sc->sc_cdb.cdb;
		sc->sc_cmd.cmdlen = sc->sc_cdb.len;
	} else {
		if (bp->b_flags & B_READ) {
D 2
			sc->sc_cmd.dataToDevice = 0;
E 2
I 2
			sc->sc_cmd.flags = 0;
E 2
			sc->sc_rwcmd.command = SCSI_READ;
I 3
			sc->sc_flags &= ~TZF_WRITTEN;
E 3
		} else {
D 2
			sc->sc_cmd.dataToDevice = 1;
E 2
I 2
			sc->sc_cmd.flags = SCSICMD_DATA_TO_DEVICE;
E 2
			sc->sc_rwcmd.command = SCSI_WRITE;
I 3
			sc->sc_flags |= TZF_WRITTEN;
E 3
		}
		sc->sc_cmd.cmd = (u_char *)&sc->sc_rwcmd;
		sc->sc_cmd.cmdlen = sizeof(sc->sc_rwcmd);
D 3
		n = howmany(bp->b_bcount, 512);
E 3
I 3
		if (sc->sc_blklen) {
			/* fixed sized records */
			n = bp->b_bcount / sc->sc_blklen;
			if (bp->b_bcount % sc->sc_blklen) {
				tprintf(sc->sc_ctty,
					"tz%d: I/O not block aligned %d/%ld\n",
					unit, sc->sc_blklen, bp->b_bcount);
				tzdone(unit, EIO, bp->b_bcount, 0);
			}
			sc->sc_rwcmd.highAddr = 1;
		} else {
			/* variable sized records */
			n = bp->b_bcount;
			sc->sc_rwcmd.highAddr = 0;
		}
E 3
		sc->sc_rwcmd.midAddr = n >> 16;
		sc->sc_rwcmd.lowAddr = n >> 8;
		sc->sc_rwcmd.blockCount = n;
D 3
		if ((bp->b_bcount & (512 - 1)) != 0)
			printf("tz%d: partial block xfer -- %x bytes\n",
				unit, bp->b_bcount);
E 3
	}

D 3
	printf("tzstart(%d) flags %x, addr %x sz %d\n", unit,
		sc->sc_flags, sc->sc_cmd.buf, sc->sc_cmd.buflen); /* XXX */
E 3
	/* tell controller to start this command */
D 3
	if (sc->sc_cmd.cmd[0] == SCSI_READ)
E 3
D 2
		sii_debug = 5; /* XXX */
E 2
	(*sc->sc_sd->sd_cdriver->d_start)(&sc->sc_cmd);
}

/*
 * This is called by the controller driver when the command is done.
 */
void
tzdone(unit, error, resid, status)
	int unit;
	int error;		/* error number from errno.h */
	int resid;		/* amount not transfered */
	int status;		/* SCSI status byte */
{
	register struct tz_softc *sc = &tz_softc[unit];
	register struct buf *bp = sc->sc_tab.b_actf;
I 8
	register struct buf *dp;
E 8
	extern int cold;
D 2
	extern int sii_debug; /* XXX */
E 2

D 3
	printf("tzdone(%d, %d, %d, %x) %x flags %x\n", unit, error, resid,
		status, sc, sc->sc_flags); /* XXX */
E 3
	if (bp == NULL) {
		printf("tz%d: bp == NULL\n", unit);
		return;
	}
	if (sc->sc_flags & TZF_SENSEINPROGRESS) {
		sc->sc_flags &= ~TZF_SENSEINPROGRESS;
D 8
		sc->sc_tab.b_actf = bp = bp->b_actf;	/* remove sc_errbuf */
E 8
I 8
		*bp->b_actb = dp = bp->b_actf;	/* remove sc_errbuf */
E 8
D 3
		if (bp == 0) {
D 2
			sii_DumpLog();
E 2
			panic("tzdone"); /* XXX */
		}
E 3
I 3
#ifdef DIAGNOSTIC
D 8
		if (bp == 0)
E 8
I 8
		if (!dp)
E 8
			panic("tzdone");
#endif
I 8
		dp->b_actb = bp->b_actb;
		bp = dp;
E 8
E 3

		if (error || (status & SCSI_STATUS_CHECKCOND)) {
D 4
#ifdef DEBUG
			if (tzdebug)
				printf("tz%d: error reading sense data: error %d scsi status 0x%x\n",
					unit, error, status);
#endif
E 4
I 4
			printf("tz%d: error reading sense data: error %d scsi status 0x%x\n",
				unit, error, status);
E 4
			/*
			 * We got an error during the REQUEST_SENSE,
			 * fill in no sense for data.
			 */
			sc->sc_sense.sense[0] = 0x70;
			sc->sc_sense.sense[2] = SCSI_CLASS7_NO_SENSE;
D 3
		} else if (!cold
#ifdef DEBUG
			|| tzdebug
#endif
		) {
			printf("tz%d: ", unit);
			scsiPrintSense((ScsiClass7Sense *)sc->sc_sense.sense,
				sizeof(sc->sc_sense.sense) - resid);
E 3
I 3
		} else if (!cold) {
			ScsiClass7Sense *sp;
			long resid;

			sp = (ScsiClass7Sense *)sc->sc_sense.sense;
			if (sp->error7 != 0x70)
				goto prerr;
			if (sp->valid) {
				resid = (sp->info1 << 24) | (sp->info2 << 16) |
					(sp->info3 << 8) | sp->info4;
				if (sc->sc_blklen)
					resid *= sc->sc_blklen;
			} else
				resid = 0;
			switch (sp->key) {
			case SCSI_CLASS7_NO_SENSE:
				/*
				 * Hit a filemark, end of media, or
				 * end of record.
				 * Fixed length blocks, an error.
				 */
				if (sp->endOfMedia) {
					bp->b_error = ENOSPC;
					bp->b_resid = resid;
					break;
				}
				if (sc->sc_blklen && sp->badBlockLen) {
					tprintf(sc->sc_ctty,
						"tz%d: Incorrect Block Length, expected %d got %d\n",
						unit, sc->sc_blklen, resid);
					break;
				}
I 8
				if (resid < 0) {
					/*
					 * Variable length records but
					 * attempted to read less than a
					 * full record.
					 */
					tprintf(sc->sc_ctty,
						"tz%d: Partial Read of Variable Length Tape Block, expected %d read %d\n",
						unit, bp->b_bcount - resid,
						bp->b_bcount);
					bp->b_resid = 0;
					break;
				}
E 8
				if (sp->fileMark)
					sc->sc_flags |= TZF_SEENEOF;
I 8
				/*
				 * Attempting to read more than a record is
				 * OK. Just record how much was actually read.
				 */
E 8
				bp->b_flags &= ~B_ERROR;
				bp->b_error = 0;
				bp->b_resid = resid;
				break;

			case SCSI_CLASS7_UNIT_ATTN:
				if (!(sc->sc_flags & TZF_OPEN))
					break;

			default:
			prerr:
D 15
				tprintf(sc->sc_ctty, "tz%d: ", unit);
E 15
I 15
				printf("tz%d: ", unit);
E 15
				scsiPrintSense((ScsiClass7Sense *)
					sc->sc_sense.sense,
					sizeof(sc->sc_sense.sense) - resid);
			}
E 3
		}
	} else if (error || (status & SCSI_STATUS_CHECKCOND)) {
#ifdef DEBUG
D 3
		if (tzdebug)
E 3
I 3
		if (!cold && tzdebug)
E 3
			printf("tz%d: error %d scsi status 0x%x\n",
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
			sc->sc_flags |= TZF_SENSEINPROGRESS;
			sc->sc_cdb.len = sizeof(ScsiGroup0Cmd);
			scsiGroup0Cmd(SCSI_REQUEST_SENSE, sc->sc_sd->sd_slave,
				0, sizeof(sc->sc_sense.sense),
				(ScsiGroup0Cmd *)sc->sc_cdb.cdb);
D 8
			sc->sc_errbuf.b_flags = B_BUSY | B_READ;
E 8
I 8
			sc->sc_errbuf.b_flags = B_BUSY | B_PHYS | B_READ;
E 8
			sc->sc_errbuf.b_bcount = sizeof(sc->sc_sense.sense);
			sc->sc_errbuf.b_un.b_addr = (caddr_t)sc->sc_sense.sense;
D 8
			sc->sc_errbuf.av_forw = bp;
			sc->sc_tab.b_actf = &sc->sc_errbuf;
E 8
I 8
			sc->sc_errbuf.b_actf = bp;
			sc->sc_errbuf.b_actb = bp->b_actb;
			*bp->b_actb = &sc->sc_errbuf;
			bp->b_actb = &sc->sc_errbuf.b_actf;
E 8
			tzstart(unit);
			return;
		}
	} else {
		sc->sc_sense.status = status;
		bp->b_resid = resid;
	}

D 8
	sc->sc_tab.b_actf = bp->b_actf;
E 8
I 8
	if (dp = bp->b_actf)
		dp->b_actb = bp->b_actb;
	else
		sc->sc_tab.b_actb = bp->b_actb;
	*bp->b_actb = dp;
E 8
	biodone(bp);
	if (sc->sc_tab.b_actf)
		tzstart(unit);
	else {
D 2
		sii_debug = 1; /* XXX */
E 2
		sc->sc_tab.b_active = 0;
		if (sc->sc_flags & TZF_WAIT) {
			sc->sc_flags &= ~TZF_WAIT;
			wakeup(&sc->sc_flags);
		}
	}
}

D 3
tzopen(dev, flags)
E 3
I 3
/* ARGSUSED */
tzopen(dev, flags, type, p)
E 3
	dev_t dev;
D 3
	int flags;
E 3
I 3
	int flags, type;
	struct proc *p;
E 3
{
	register int unit = tzunit(dev);
	register struct tz_softc *sc = &tz_softc[unit];
	int error;

D 11
	if (unit >= NTZ)
E 11
I 11
	if (unit >= NTZ || sc->sc_sd == NULL)
E 11
		return (ENXIO);
	if (!(sc->sc_flags & TZF_ALIVE)) {
		/* check again, tape may have been turned off at boot time */
		if (!tzprobe(sc->sc_sd))
			return (ENXIO);
	}
	if (sc->sc_flags & TZF_OPEN)
		return (EBUSY);

	/* clear UNIT_ATTENTION */
D 3
	error = tzcommand(dev, SCSI_TEST_UNIT_READY, 0, 0);
E 3
I 3
	error = tzcommand(dev, SCSI_TEST_UNIT_READY, 0, 0, 0);
E 3
D 8
	if (error) {
E 8
I 8
	while (error) {
E 8
		ScsiClass7Sense *sp = (ScsiClass7Sense *)sc->sc_sense.sense;

		/* return error if last error was not UNIT_ATTENTION */
		if (!(sc->sc_sense.status & SCSI_STATUS_CHECKCOND) ||
		    sp->error7 != 0x70 || sp->key != SCSI_CLASS7_UNIT_ATTN)
			return (error);
I 3

		/*
		 * Try it again just to be sure and
		 * try to negotiate synchonous transfers.
		 */
		error = tzcommand(dev, SCSI_TEST_UNIT_READY, 0, 0, 0);
E 3
	}

D 3
#ifdef notdef
	if ((flag&FWRITE) && (sc->sc_dsreg&HTDS_WRL)) {
		sc->sc_openf = 0;
D 2
		uprintf("tu%d: no write ring\n", tuunit);
E 2
I 2
		uprintf("tz%d: no write ring\n", unit);
E 2
		return (EIO);
E 3
I 3
	/* get the current mode settings */
	error = tzcommand(dev, SCSI_MODE_SENSE, 0,
		sc->sc_modelen, (caddr_t)&sc->sc_mode);
	if (error)
		return (error);

	/* check for write protected tape */
	if ((flags & FWRITE) && sc->sc_mode.writeprot) {
		uprintf("tz%d: write protected\n", unit);
		return (EACCES);
E 3
	}
D 3
	sc->sc_ctty = (caddr_t)(u.u_procp->p_flag & SCTTY ? 
			u.u_procp->p_session->s_ttyp : 0);
E 3
I 3

	/* set record length */
	switch (sc->sc_tapeid) {
	case MT_ISAR:
	case MT_ISHPDAT:
	case MT_ISVIPER1:
D 5
	case MT_ISPYTHON:
E 5
		sc->sc_blklen = 512;
		break;

	case MT_ISEXABYTE:
#if 0
		if (minor(dev) & TZ_FIXEDBLK)
			sc->sc_blklen = 1024;
		else
			sc->sc_blklen = st_exblklen;
E 3
#endif
I 3
		break;

I 5
	case MT_ISPYTHON:
E 5
	case MT_ISMFOUR:
	case MT_ISTK50:
		sc->sc_blklen = 0;
		break;

	default:
		sc->sc_blklen = (sc->sc_mode.block_size2 << 16) |
			(sc->sc_mode.block_size1 << 8) | sc->sc_mode.block_size0;
	}

	/* save total number of blocks on tape */
	sc->sc_numblks = (sc->sc_mode.blocks_2 << 16) |
		(sc->sc_mode.blocks_1 << 8) | sc->sc_mode.blocks_0;

	/* setup for mode select */
	sc->sc_mode.len = 0;
	sc->sc_mode.media = 0;
	sc->sc_mode.bufferedMode = 1;
	sc->sc_mode.blocks_0 = 0;
	sc->sc_mode.blocks_1 = 0;
	sc->sc_mode.blocks_2 = 0;
	sc->sc_mode.block_size0 = sc->sc_blklen >> 16;
	sc->sc_mode.block_size1 = sc->sc_blklen >> 8;
	sc->sc_mode.block_size2 = sc->sc_blklen;

	/* check for tape density changes */
	switch (sc->sc_tapeid) {
	case MT_ISAR:
		if (minor(dev) & TZ_HIDENSITY)
			sc->sc_mode.density = 0x5;
		else {
			if (flags & FWRITE) {
				uprintf("Can only write QIC-24\n");
				return (EIO);
			}
			sc->sc_mode.density = 0x4;
		}
		break;

	case MT_ISMT02:
		/*
		 * The tape density is set automatically when the tape
		 * is loaded. We only need to change it if we are writing.
		 */
		if (flags & FWRITE) {
			if (minor(dev) & TZ_HIDENSITY)
				sc->sc_mode.density = 0;
			else
				sc->sc_mode.density = 0x4;
		}
		break;

	case MT_ISEXABYTE:
#if 0
		if (minor(dev) & TZ_HIDENSITY)
			uprintf("EXB-8200 density support only\n");
		sc->sc_mode.vupb = (u_char)st_exvup;
		sc->sc_mode.rsvd5 = 0;
		sc->sc_mode.p5 = 0;
		sc->sc_mode.motionthres = (u_char)st_exmotthr;
		sc->sc_mode.reconthres = (u_char)st_exreconthr;
		sc->sc_mode.gapthres = (u_char)st_exgapthr;
#endif
		break;

	case MT_ISHPDAT:
	case MT_ISVIPER1:
	case MT_ISPYTHON:
	case MT_ISTK50:
		if (minor(dev) & TZ_HIDENSITY)
			uprintf("tz%d: Only one density supported\n", unit);
		break;

	case MT_ISMFOUR:
		break;		/* XXX could do density select? */
	}

	/* set the current mode settings */
	error = tzcommand(dev, SCSI_MODE_SELECT, 0,
		sc->sc_modelen, (caddr_t)&sc->sc_mode);
	if (error)
		return (error);

	sc->sc_ctty = tprintf_open(p);
E 3
	sc->sc_flags = TZF_ALIVE | TZF_OPEN;
	return (0);
}

tzclose(dev, flag)
	dev_t dev;
	int flag;
{
	register struct tz_softc *sc = &tz_softc[tzunit(dev)];
I 3
	int error = 0;
E 3

	if (!(sc->sc_flags & TZF_OPEN))
		return (0);
	if (flag == FWRITE ||
	    ((flag & FWRITE) && (sc->sc_flags & TZF_WRITTEN))) {
D 3
		(void) tzcommand(dev, SCSI_WRITE_EOF, 0, 1);
E 3
I 3
		error = tzcommand(dev, SCSI_WRITE_EOF, 0, 1, 0);
#if 0
		/*
		 * Cartridge tapes don't do double EOFs on EOT.
		 */
		switch (sc->sc_tapeid) {
		case MT_ISAR:
		case MT_ISMT02:
			break;

		default:
			error = tzcommand(dev, SCSI_WRITE_EOF, 0, 1, 0);
			if (minor(dev) & TZ_NOREWIND)
				(void) tzcommand(dev, SCSI_SPACE, 0, -1, 0);
		}
#endif
E 3
	}
	if ((minor(dev) & TZ_NOREWIND) == 0)
D 3
		(void) tzcommand(dev, SCSI_REWIND, 0, 0);
E 3
I 3
		(void) tzcommand(dev, SCSI_REWIND, 0, 0, 0);
E 3
	sc->sc_flags &= ~(TZF_OPEN | TZF_WRITTEN);
D 3
	return (0);
E 3
I 3
	tprintf_close(sc->sc_ctty);
	return (error);
E 3
}

tzioctl(dev, cmd, data, flag)
	dev_t dev;
D 16
	int cmd;
E 16
I 16
	u_long cmd;
E 16
	caddr_t data;
	int flag;
{
	register struct tz_softc *sc = &tz_softc[tzunit(dev)];
	register struct buf *bp = &sc->sc_buf;
	struct mtop *mtop;
	struct mtget *mtget;
	int code, count;
	static tzops[] = {
		SCSI_WRITE_EOF, SCSI_SPACE, SCSI_SPACE, SCSI_SPACE, SCSI_SPACE,
		SCSI_REWIND, SCSI_REWIND, SCSI_TEST_UNIT_READY
	};

	switch (cmd) {

	case MTIOCTOP:	/* tape operation */
		mtop = (struct mtop *)data;
		if ((unsigned)mtop->mt_op < MTREW && mtop->mt_count <= 0)
			return (EINVAL);
		switch (mtop->mt_op) {

		case MTWEOF:
			code = 0;
			count = mtop->mt_count;
			break;

		case MTFSF:
			code = 1;
			count = mtop->mt_count;
			break;

		case MTBSF:
			code = 1;
			count = -mtop->mt_count;
			break;

		case MTFSR:
			code = 0;
I 3
			count = mtop->mt_count;
E 3
			break;

		case MTBSR:
			code = 0;
			count = -mtop->mt_count;
			break;

		case MTREW:
		case MTOFFL:
		case MTNOP:
			code = 0;
			count = 0;
			break;

		default:
			return (EINVAL);
		}
D 3
		return (tzcommand(dev, tzops[mtop->mt_op], code, count));
E 3
I 3
		return (tzcommand(dev, tzops[mtop->mt_op], code, count, 0));
E 3

	case MTIOCGET:
		mtget = (struct mtget *)data;
		mtget->mt_dsreg = 0;
		mtget->mt_erreg = sc->sc_sense.status;
		mtget->mt_resid = 0;
		mtget->mt_type = 0;
		break;

	default:
		return (EINVAL);
	}
	return (0);
}

void
tzstrategy(bp)
	register struct buf *bp;
{
	register int unit = tzunit(bp->b_dev);
	register struct tz_softc *sc = &tz_softc[unit];
	register struct buf *dp;
	register int s;

I 3
	if (sc->sc_flags & TZF_SEENEOF) {
		bp->b_resid = bp->b_bcount;
		biodone(bp);
		return;
	}
E 3
D 8
	bp->av_forw = NULL;
E 8
I 8
	bp->b_actf = NULL;
E 8
	dp = &sc->sc_tab;
	s = splbio();
D 8
	if (dp->b_actf == NULL)
		dp->b_actf = bp;
	else
		dp->b_actl->av_forw = bp;
	dp->b_actl = bp;
E 8
I 8
	bp->b_actb = dp->b_actb;
	*dp->b_actb = bp;
	dp->b_actb = &bp->b_actf;
E 8
	if (dp->b_active == 0) {
		dp->b_active = 1;
		tzstart(unit);
	}
	splx(s);
}
#endif
E 1
