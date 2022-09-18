h51002
s 00002/00001/01431
d D 8.5 95/01/09 18:29:01 cgd 15 14
c ioctl cmd arg is u_long, strategy returns void.
e
s 00006/00004/01426
d D 8.4 94/05/27 12:46:26 hibler 14 13
c fix a divide by zero problem
e
s 00000/00004/01430
d D 8.3 94/01/12 16:36:49 hibler 13 12
c lint
e
s 00005/00001/01429
d D 8.2 93/11/15 21:57:53 mckusick 12 11
c have to do tprintf_open before trying to print
e
s 00002/00002/01428
d D 8.1 93/06/10 21:34:37 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/01427
d D 7.10 93/06/01 13:33:08 marc 10 9
c deal with new message
e
s 00013/00013/01416
d D 7.9 92/10/11 09:24:11 bostic 9 8
c make kernel includes standard
e
s 00014/00007/01415
d D 7.8 92/10/02 00:14:00 mckusick 8 7
c av_forw/av_back are gone; now use b_actf/b_actb for linking active buffers
e
s 00004/00012/01418
d D 7.7 92/06/05 15:31:55 hibler 7 6
c merge latest Utah hp300 code including 68040 support
e
s 00011/00010/01419
d D 7.6 92/03/19 16:43:45 marc 6 5
c M4 support
e
s 00001/00001/01428
d D 7.5 92/02/15 18:02:31 mckusick 5 4
c have to include proc.h before socketvar.h
e
s 00046/00006/01383
d D 7.4 91/09/18 17:11:25 karels 4 3
c checkin karels changes (plus fix sleep -> tsleep)
e
s 00008/00010/01381
d D 7.3 91/05/04 19:49:27 karels 3 2
c update to current include, device calling conventions
e
s 00004/00002/01387
d D 7.2 91/03/17 13:07:44 mckusick 2 1
c put in (probably required) delay
e
s 01389/00000/00000
d D 7.1 91/02/05 19:14:14 mckusick 1 0
c Exabyte driver from Mike Hibler at Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 University of Utah.
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 7
 * from: Utah $Hdr: st.c 1.8 90/10/14$
E 7
I 7
 * from: Utah $Hdr: st.c 1.11 92/01/21$
E 7
 *
 *      %W% (Berkeley) %G%
 */

/*
 * SCSI CCS (Command Command Set) tape driver.
 *
 * Specific to Exabyte:
 * mt status: residual="Mbytes to LEOM"
 * minor bit 4 [b1bbbb] (aka /dev/rst16) selects short filemarks
 * minor bit 5 [1bbbbb] (aka /dev/rst32) selects fix block mode, 1k blocks.
 *
 * Archive drive:
 * can read both QIC-24 and QIC-II. But only writes
 * QIC-24.
 * 
 * Supports Archive Viper QIC-150 tape drive, but scsi.c reports selection
 * errors.
 *
 * Supports Archive Python DAT drive, but will sometimes hang machine.
 *
 * Supports HP 35450A DAT drive, but will sometimes hang machine.
 * Partitioning of tape not supported.
 * Vendor unique support has not been added.
 *
 *
 * Supports Archive VIPER (QIC-150).
 * Mostly Supports Archive PYTHON (DAT). 
 *     Hangs if write after spin down. 
 *     Need scsi.c that does connect/disconnect.
 */

/*
 * support for the block device not implemented 
 */

#include "st.h"
#if NST > 0

D 9
#include "param.h"
#include "systm.h"
#include "buf.h"
D 3
#include "errno.h"
#include "device.h"
E 3
D 7
#include "scsireg.h"
E 7
#include "file.h"
D 5
#include "tty.h"
E 5
D 3
#include "user.h"
E 3
#include "proc.h"
I 7
#include "ioctl.h"
E 7
I 5
#include "tty.h"
E 5
#include "mtio.h"
D 7
#include "ioctl.h"
E 7
D 3
#include "uio.h"
E 3
#include "kernel.h"
I 3
#include "tprintf.h"
E 9
I 9
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/file.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/mtio.h>
#include <sys/kernel.h>
#include <sys/tprintf.h>
E 9
E 3

I 3
D 7
#include "device.h"
E 7
I 7
D 9
#include "hp/dev/device.h"
#include "scsireg.h"
E 7
E 3
#include "stvar.h"
E 9
I 9
#include <hp/dev/device.h>
#include <hp300/dev/scsireg.h>
#include <hp300/dev/stvar.h>
E 9

I 4
D 6
/*
E 6
E 4
I 2
D 7
#define ADD_DELAY
D 4

E 4
I 4
D 6
*/
E 6
I 6

E 7
E 6
E 4
E 2
extern int scsi_test_unit_rdy();
extern int scsi_request_sense();
extern int scsiustart();
extern int scsigo();
extern void scsifree();
extern void scsireset();
extern void scsi_delay();
extern int scsi_tt_oddio();

extern int scsi_immed_command();

int	stinit(), ststart(), stgo(), stintr();
struct	driver stdriver = {
	stinit, "st", ststart, stgo, stintr,
};

struct	st_softc {
	struct	hp_device *sc_hd;
	struct	devqueue sc_dq;
	long	sc_blkno;       /* (possible block device support?) */
	long	sc_resid;	/* (possible block device support?) */
	int	sc_flags;
	int	sc_blklen;	/* 0 = variable len records */
	int	sc_filepos;	/* file position on tape */
	long	sc_numblks;	/* number of blocks on tape */
	short	sc_type;	/* ansi scsi type */
	short	sc_punit;	/* physical unit (scsi lun) */
	short	sc_tapeid;	/* tape drive id */
	char	sc_datalen[32];	/* additional data length on some commands */
	short	sc_tticntdwn;	/* interrupts between TTi display updates */
D 3
	caddr_t	sc_ctty;
E 3
I 3
	tpr_t	sc_ctty;
E 3
	struct	buf *sc_bp;
	u_char	sc_cmd;
} st_softc[NST];

/* softc flags */
#define STF_ALIVE	0x0001
#define STF_OPEN	0x0002
#define STF_WMODE	0x0004
#define STF_WRTTN	0x0008
#define STF_CMD		0x0010
#define STF_LEOT	0x0020
#define STF_MOVED	0x0040

struct	st_mode st_mode[NST];

/*
 * Maybe this should not be global, but gives chance to get
 * tape remaining, Rewrites/ECC, etc outside the driver 
 */
static struct st_xsense {
	struct	scsi_xsense sc_xsense;	/* data from sense */
	struct	exb_xsense exb_xsense;	/* additional info from exabyte */
} st_xsense[NST];

static struct scsi_fmt_cdb stcmd[NST];

static struct scsi_fmt_cdb st_read_cmd = { 6, CMD_READ };
static struct scsi_fmt_cdb st_write_cmd = { 6, CMD_WRITE };

struct buf sttab[NST];
struct buf stbuf[NST];

#define UNIT(x)		(minor(x) & 3)
#define stpunit(x)	((x) & 7)

#define STDEV_NOREWIND	0x04
#define STDEV_HIDENSITY	0x08
#define STDEV_EXSFMK	0x10
#define STDEV_FIXEDBLK	0x20

#ifdef DEBUG
int st_debug = 0x0000;
#define ST_OPEN		0x0001
#define ST_GO		0x0002
#define ST_FMKS		0x0004
#define ST_OPENSTAT	0x0008
#define ST_BRESID	0x0010
#define ST_ODDIO	0x0020
#endif

/*
 * Patchable variable.  If an even length read is requested a dma transfer is
 * used.  Only after the read will we find out if the read had an odd number
 * of bytes.  The HP98658 hardware cannot do odd length transfers, the last
 * byte of the data will always be 0x00.  Normally, the driver will complain
 * about such transfers and return EIO.  However, if st_dmaoddretry is non-
 * zero, the driver will try and issue a BSR and then re-read the data using
 * 'programmed transfer mode'.  In most cases this works, however for unknown
 * reasons it will hang the machine in certain cases.
 *
 * Note:
 * Odd length read requests are always done using programmed transfer mode.
 */
int st_dmaoddretry = 0;

/*
 * Exabyte only:
 * From adb can have access to fixed vs. variable length modes.
 * Use 0x400 for 1k (best capacity) fixed length records.
 * In st_open, if minor bit 4 set then 1k records are used.
 * If st_exblken is set to anything other then 0 we are in fixed length mode.
D 6
 * Minor bit 4 overrides any setting of st_exblklen.
E 6
I 6
 * Minor bit 5 requests 1K fixed-length, overriding any setting of st_exblklen.
E 6
D 7
 * 
E 7
 */
int st_exblklen = 0;

/* exabyte here for adb access, set at open time */
#define EX_CT 	0x80		/* international cart - more space W/P6  */
#define EX_ND	0x20		/* no disconnect  */
#define EX_NBE	0x08		/* no busy enable  */
#define EX_EBD	0x04		/* even byte disconnect  */
#define EX_PE	0x02		/* parity enable  */
#define EX_NAL	0x01		/* no auto load  */
int st_exvup = (EX_CT|EX_ND|EX_NBE); /* vendor unique parameters */

/*
 * motion and reconnect thresholds guidelines:
 * write operation; lower motion threshold for faster transfer
 *                  raise reconnect threshold for slower transfer
 * read operation; lower motion threshold for slower transfer
 *                 raise reconnect threshold for faster transfer
 */
int st_exmotthr = 0x80;		/* motion threshold, 0x80 default */
int st_exreconthr = 0xa0;	/* reconnect threshold, 0xa0 default */
int st_exgapthr = 7;		/* gap threshold, 7 default */
#ifdef TTI
int st_extti = 0x01;		/* bitmask of unit numbers, do extra */
				/* sensing so TTi display gets updated */
#endif

stinit(hd)
	register struct hp_device *hd;
{
	register struct st_softc *sc = &st_softc[hd->hp_unit];
I 8
	register struct buf *bp;
E 8

I 8
	for (bp = sttab; bp < &sttab[NST]; bp++)
		bp->b_actb = &bp->b_actf;
E 8
	sc->sc_hd = hd;
	sc->sc_punit = stpunit(hd->hp_flags);
	sc->sc_type = stident(sc, hd);
	if (sc->sc_type < 0)
		return(0);
I 4
D 7

E 7
E 4
	sc->sc_dq.dq_ctlr = hd->hp_ctlr;
	sc->sc_dq.dq_unit = hd->hp_unit;
	sc->sc_dq.dq_slave = hd->hp_slave;
	sc->sc_dq.dq_driver = &stdriver;
	sc->sc_blkno = 0;
	sc->sc_flags = STF_ALIVE;
	return(1);
}

stident(sc, hd)
	register struct st_softc *sc;
	register struct hp_device *hd;
{
	int unit;
	int ctlr, slave;
	int i, stat, inqlen;
	char idstr[32];
D 2
#if 0
E 2
I 2
D 7
#ifdef ADD_DELAY
E 7
E 2
	static int havest = 0;
D 7
#endif
E 7
	struct st_inquiry {
		struct	scsi_inquiry inqbuf;
		struct  exb_inquiry exb_inquiry;
	} st_inqbuf;
	static struct scsi_fmt_cdb st_inq = {
		6,
		CMD_INQUIRY, 0, 0, 0, sizeof(st_inqbuf), 0
	};

	ctlr = hd->hp_ctlr;
	slave = hd->hp_slave;
	unit = sc->sc_punit;
	scsi_delay(-1);

	inqlen = 0x05; /* min */
	st_inq.cdb[4] = 0x05;
	stat = scsi_immed_command(ctlr, slave, unit, &st_inq, 
				  (u_char *)&st_inqbuf, inqlen, B_READ);
	/* do twice as first command on some scsi tapes always fails */
	stat = scsi_immed_command(ctlr, slave, unit, &st_inq, 
				  (u_char *)&st_inqbuf, inqlen, B_READ);
	if (stat == -1)
		goto failed;

D 4
	if (st_inqbuf.inqbuf.type != 0x01 ||  /* sequential access device */
E 4
I 4
	if ((st_inqbuf.inqbuf.type != 0x01 ||  /* sequential access device */
E 4
	    st_inqbuf.inqbuf.qual != 0x80 ||  /* removable media */
	    (st_inqbuf.inqbuf.version != 0x01 && /* current ANSI SCSI spec */
D 4
	     st_inqbuf.inqbuf.version != 0x02))  /* 0x02 is for HP DAT */
E 4
I 4
	     st_inqbuf.inqbuf.version != 0x02)) /* 0x02 is for HP DAT */
	    &&
	    (st_inqbuf.inqbuf.type != 0x01 ||	/* M4 ??! */
	     /*
	      * the M4 is a little too smart (ass?) for its own good:
	      * qual codes:
	      * 0x80: you can take the tape out (unit not online)
	      * 0xf8: online and at 6250bpi
	      * 0xf9: online and at 1600bpi
	      */
	     st_inqbuf.inqbuf.version != 0x09))	/* M4 tape */
{
printf("st: wrong specs: type %x qual %x version %d\n", st_inqbuf.inqbuf.type,
st_inqbuf.inqbuf.qual, st_inqbuf.inqbuf.version);
E 4
		goto failed;
I 4
}
E 4

	/* now get additonal info */
	inqlen = 0x05 + st_inqbuf.inqbuf.len;
	st_inq.cdb[4] = inqlen;
	bzero(&st_inqbuf, sizeof(st_inqbuf));
	stat = scsi_immed_command(ctlr, slave, unit, &st_inq, 
				  (u_char *)&st_inqbuf, inqlen, B_READ);

	if (st_inqbuf.inqbuf.len >= 28) {
		bcopy((caddr_t)&st_inqbuf.inqbuf.vendor_id, (caddr_t)idstr, 28);
		for (i = 27; i > 23; --i)
			if (idstr[i] != ' ')
				break;
		idstr[i+1] = 0;
		for (i = 23; i > 7; --i)
			if (idstr[i] != ' ')
				break;
		idstr[i+1] = 0;
		for (i = 7; i >= 0; --i)
			if (idstr[i] != ' ')
				break;
		idstr[i+1] = 0;
D 10
		printf("st%d: %s %s rev %s\n", hd->hp_unit, idstr, &idstr[8],
E 10
I 10
		printf("st%d: %s, %s rev %s\n", hd->hp_unit, idstr, &idstr[8],
E 10
		       &idstr[24]);
	} else if (inqlen == 5)
		/* great it's a stupid device, doesn't know it's know name */
		idstr[0] = idstr[8] = '\0';
	else
		idstr[8] = '\0';

	if (stat == 0xff) { 
		printf("st%d: Cant handle this tape drive\n", hd->hp_unit);
		goto failed;
	}

	if (bcmp("EXB-8200", &idstr[8], 8) == 0) {
		sc->sc_tapeid = MT_ISEXABYTE;
		sc->sc_datalen[CMD_REQUEST_SENSE] = 26;
		sc->sc_datalen[CMD_INQUIRY] = 52;
		sc->sc_datalen[CMD_MODE_SELECT] = 17;
		sc->sc_datalen[CMD_MODE_SENSE] = 17;
	} else if (bcmp("VIPER 150", &idstr[8], 9) == 0) {
		sc->sc_tapeid = MT_ISVIPER1;
		sc->sc_datalen[CMD_REQUEST_SENSE] = 14;
		sc->sc_datalen[CMD_INQUIRY] = 36;
		sc->sc_datalen[CMD_MODE_SELECT] = 12;
		sc->sc_datalen[CMD_MODE_SENSE] = 12;
	} else if (bcmp("Python 25501", &idstr[8], 12) == 0) {
		sc->sc_tapeid = MT_ISPYTHON;
		sc->sc_datalen[CMD_REQUEST_SENSE] = 14;
		sc->sc_datalen[CMD_INQUIRY] = 36;
		sc->sc_datalen[CMD_MODE_SELECT] = 12;
		sc->sc_datalen[CMD_MODE_SENSE] = 12;
	} else if (bcmp("HP35450A", &idstr[8], 8) == 0) {
		/* XXX "extra" stat makes the HP drive happy at boot time */
		stat = scsi_test_unit_rdy(ctlr, slave, unit);
		sc->sc_tapeid = MT_ISHPDAT;
		sc->sc_datalen[CMD_REQUEST_SENSE] = 14;
		sc->sc_datalen[CMD_INQUIRY] = 36;
		sc->sc_datalen[CMD_MODE_SELECT] = 12;
		sc->sc_datalen[CMD_MODE_SENSE] = 12;
I 4
D 10
	} else if (bcmp("123107 SCSI", &idstr[8], 11) == 0) {
E 10
I 10
	} else if (bcmp("123107 SCSI", &idstr[8], 11) == 0 ||
		   bcmp("OPEN REEL TAPE", &idstr[8], 14) == 0) {
E 10
		sc->sc_tapeid = MT_ISMFOUR;
		sc->sc_datalen[CMD_REQUEST_SENSE] = 8;
		sc->sc_datalen[CMD_INQUIRY] = 5;
		sc->sc_datalen[CMD_MODE_SELECT] = 12;
		sc->sc_datalen[CMD_MODE_SENSE] = 12;
E 4
	} else {
		if (idstr[8] == '\0')
			printf("st%d: No ID, assuming Archive\n", hd->hp_unit);
		else
			printf("st%d: Unsupported tape device\n", hd->hp_unit);
		sc->sc_tapeid = MT_ISAR;
		sc->sc_datalen[CMD_REQUEST_SENSE] = 8;
		sc->sc_datalen[CMD_INQUIRY] = 5;
		sc->sc_datalen[CMD_MODE_SELECT] = 12;
		sc->sc_datalen[CMD_MODE_SENSE] = 12;
	}

	sc->sc_filepos = 0;
	
	/* load xsense */
	stxsense(ctlr, slave, unit, sc);

	scsi_delay(0);
D 2
#if 0
E 2
I 2
D 7
#ifdef ADD_DELAY
E 7
E 2
	/* XXX if we have a tape, we must up the delays in the HA driver */
	if (!havest) {
		havest = 1;
		scsi_delay(20000);
	}
D 7
#endif
E 7
	return(st_inqbuf.inqbuf.type);
failed:
	scsi_delay(0);
	return(-1);
}

D 3
stopen(dev, flag)
E 3
I 3
stopen(dev, flag, type, p)
E 3
	dev_t dev;
D 3
	int flag;
E 3
I 3
	int flag, type;
	struct proc *p;
E 3
{
	register struct st_softc *sc = &st_softc[UNIT(dev)];
	register struct st_xsense *xsense;
	register int count;
	register int stat;
	int ctlr, slave, unit;
	struct mode_select_data msd;
	struct mode_sense mode;
	int modlen;
I 4
	int error;
E 4
	static struct scsi_fmt_cdb modsel = {
		6,
		CMD_MODE_SELECT, 0, 0, 0, sizeof(msd), 0
	};
D 13
	static struct scsi_fmt_cdb unitready = {
		6,
		CMD_TEST_UNIT_READY, 0, 0, 0, 0, 0
	};
E 13
	static struct scsi_fmt_cdb modsense = {
		6,
		CMD_MODE_SENSE, 0, 0, 0, sizeof(mode), 0
	};

	ctlr = sc->sc_dq.dq_ctlr;
	slave = sc->sc_dq.dq_slave;
	unit = sc->sc_punit;
	xsense = &st_xsense[UNIT(dev)];

	if (UNIT(dev) > NST || (sc->sc_flags & STF_ALIVE) == 0)
		return(ENXIO);
	if (sc->sc_flags & STF_OPEN)
		return(EBUSY);

I 12
	/*
	 * Be prepared to print error messages
	 */
	sc->sc_ctty = tprintf_open(p);

E 12
	/* do a mode sense to get current */
	modlen = sc->sc_datalen[CMD_MODE_SENSE];
	modsense.cdb[4] = modlen;
	stat = scsi_immed_command(ctlr, slave, unit, &modsense,
				  (u_char *)&mode, modlen, B_READ);

	/* do a mode sense to get current */
	modlen = sc->sc_datalen[CMD_MODE_SENSE];
	modsense.cdb[4] = modlen;
	stat = scsi_immed_command(ctlr, slave, unit, &modsense,
				  (u_char *)&mode, modlen, B_READ);

	/* set record length */
	switch (sc->sc_tapeid) {
	case MT_ISAR:
		sc->sc_blklen = 512;
		break;
	case MT_ISEXABYTE:
		if (minor(dev) & STDEV_FIXEDBLK)
			sc->sc_blklen = 0x400;
		else
			sc->sc_blklen = st_exblklen;
		break;
	case MT_ISHPDAT:
		sc->sc_blklen = 512;
		break;
	case MT_ISVIPER1:
		sc->sc_blklen = 512;
		break;
	case MT_ISPYTHON:
		sc->sc_blklen = 512;
		break;
I 4
	case MT_ISMFOUR:
		sc->sc_blklen = 0;
		break;
E 4
	default:
		if ((mode.md.blklen2 << 16 |
		     mode.md.blklen1 << 8 |
		     mode.md.blklen0) != 0)
			sc->sc_blklen = mode.md.blklen2 << 16 |
					mode.md.blklen1 << 8 |
					mode.md.blklen0;
		else
			sc->sc_blklen = 512;
	}

	/* setup for mode select */
	msd.rsvd1 = 0;
	msd.rsvd2 = 0;
	msd.rsvd3 = 0;
	msd.buff = 1;
	msd.speed = 0;
	msd.blkdeslen = 0x08;
	msd.density = 0;
	msd.blks2 = 0;
	msd.blks1 = 0;
	msd.blks0 = 0;
	msd.rsvd4 = 0;
	msd.blklen2 = (sc->sc_blklen >> 16) & 0xff;
	msd.blklen1 = (sc->sc_blklen >> 8) & 0xff;
	msd.blklen0 = sc->sc_blklen & 0xff;

I 4
	/*
	 * Do we have any density problems?
	 */

E 4
	switch (sc->sc_tapeid) {
I 4
D 6
	case MT_ISMFOUR:
		break;
E 6
E 4
	case MT_ISAR:
		if (minor(dev) & STDEV_HIDENSITY)
			msd.density = 0x5;
		else {
			if (flag & FWRITE) {
				uprintf("Can only write QIC-24\n");
				return(EIO);
			}
			msd.density = 0x4;
		}
		break;
	case MT_ISEXABYTE:
		if (minor(dev) & STDEV_HIDENSITY)
			uprintf("EXB-8200 density support only\n");
		msd.vupb = (u_char)st_exvup;
		msd.rsvd5 = 0;
		msd.p5 = 0;
		msd.motionthres = (u_char)st_exmotthr;
		msd.reconthres = (u_char)st_exreconthr;
		msd.gapthres = (u_char)st_exgapthr;
		break;
	case MT_ISHPDAT:
	case MT_ISVIPER1:
	case MT_ISPYTHON:
		if (minor(dev) & STDEV_HIDENSITY)
			uprintf("Only one density supported\n");
		break;
I 6
	case MT_ISMFOUR:
		break;		/* XXX could do density select? */
E 6
	default:
		uprintf("Unsupported drive\n");
		return(EIO);
	}

	modlen = sc->sc_datalen[CMD_MODE_SELECT];
	modsel.cdb[4] = modlen;

	/* mode select */
	count = 0;
retryselect:
	stat = scsi_immed_command(ctlr, slave, unit, &modsel,
				  (u_char *)&msd, modlen, B_WRITE);
	/*
	 * First command after power cycle, bus reset or tape change 
	 * will error. Try command again
	 */
	if (stat == STS_CHECKCOND) {
		sc->sc_filepos = 0;
		stxsense(ctlr, slave, unit, sc);
		stat = scsi_immed_command(ctlr, slave, unit, &modsel,
					  (u_char *)&msd, modlen, B_WRITE);
#ifdef DEBUG
		if (stat && (st_debug & ST_OPEN))
			printf("stopen: stat on mode select 0x%x second try\n", stat);
#endif
		if (stat == STS_CHECKCOND) {
			stxsense(ctlr, slave, unit, sc);
			prtkey(UNIT(dev), sc);
		}
		if (stat)
			return(EIO);
	}
	if (stat == -1 || stat == STS_BUSY) {
		/*
		 * XXX it might just be that the bus is busy because
		 * another tape is doing a command. This would change
		 * with connect/disconnect, ie. the other drive would
		 * not hold onto the bus.
		 *
		 * Sleep on lbolt for up to 20 minutes (max time to FSF
		 * an exabyte to EOT: 16:xx minutes)
		 */
		if (++count > 60*20) {
			uprintf("SCSI bus timeout\n");
			return(EBUSY);
		}
D 4
		sleep((caddr_t)&lbolt, PZERO+1);
E 4
I 4
		if (error = tsleep((caddr_t)&lbolt, PZERO | PCATCH, 
		    "st_scsiwait", 0))
			return (error);
E 4
		goto retryselect;
	}

	/* drive ready ? */
	stat = scsi_test_unit_rdy(ctlr, slave, unit);

	if (stat == STS_CHECKCOND) {
		stxsense(ctlr, slave, unit, sc);
		switch (sc->sc_tapeid) {
		case MT_ISEXABYTE:
			if ((xsense->sc_xsense.key & XSK_NOTRDY) &&
			    xsense->exb_xsense.tnp)
				uprintf("no cartridge\n");
			else if (xsense->sc_xsense.key & XSK_NOTRDY)
				uprintf("cartridge not loaded\n");
			else if (xsense->sc_xsense.key & XSK_UNTATTEN) {
				uprintf("new cart/power interrupt\n");
				stat = 0;
			} else if ((xsense->sc_xsense.key & XSK_UNTATTEN) &&
				   xsense->exb_xsense.tnp)
				uprintf("cartridge unloading\n");
			else 
				prtkey(UNIT(dev), sc);
			break;
I 4
		case MT_ISMFOUR:
E 4
		case MT_ISAR:
			if (xsense->sc_xsense.key & XSK_UNTATTEN)
				stat = scsi_test_unit_rdy(ctlr, slave, unit);
			if (stat == STS_CHECKCOND) {
				stxsense(ctlr, slave, unit, sc);
				if (xsense->sc_xsense.key)
					prtkey(UNIT(dev), sc);
			} else { 
				sc->sc_filepos = 0; /* new tape */
				stat = 0;
			}
			break;
		case MT_ISHPDAT:
		case MT_ISVIPER1:
		case MT_ISPYTHON:
			if (xsense->sc_xsense.key & XSK_UNTATTEN)
				stat = scsi_test_unit_rdy(ctlr, slave, unit);
			if (stat == STS_CHECKCOND) {
				stxsense(ctlr, slave, unit, sc);
				if (xsense->sc_xsense.key)
					prtkey(UNIT(dev), sc);
			}
			break;
		default:
			uprintf("st%d: not ready\n", UNIT(dev));
			prtkey(UNIT(dev), sc);
			break;
		}
	}
	if (stat)
		return(EIO);

	/* mode sense */
	modlen = sc->sc_datalen[CMD_MODE_SENSE];
	modsense.cdb[4] = modlen;
	stat = scsi_immed_command(ctlr, slave, unit, &modsense,
				  (u_char *)&mode, modlen, B_READ);
#ifdef DEBUG
	if (st_debug & ST_OPENSTAT)
		prtmodstat(&mode);
#endif

	if (stat == STS_CHECKCOND) {
		stxsense(ctlr, slave, unit, sc);
#ifdef DEBUG
		if (st_debug & ST_OPEN)
			dumpxsense(xsense);
#endif
	}
	if (stat)
		return(EIO);

	if ((flag & FWRITE) && mode.md.wp) {
		uprintf("st:%d write protected\n", UNIT(dev));
		return(EACCES);
	}

D 3
	sc->sc_ctty = (caddr_t)(u.u_procp->p_flag&SCTTY ? 
			u.u_procp->p_session->s_ttyvp : 0);
E 3
I 3
D 12
	sc->sc_ctty = tprintf_open(p);
E 12
E 3
	/* save total number of blocks on tape */
	sc->sc_numblks = mode.md.numblk2 << 16 |
			 mode.md.numblk1 << 8 |
			 mode.md.numblk0;

	if (xsense->sc_xsense.eom && !(sc->sc_flags & STF_LEOT))
		sc->sc_filepos = 0;
#ifdef DEBUG
	if (st_debug & ST_FMKS)
		printf("st%d: open filepos = %d\n", UNIT(dev), sc->sc_filepos);
#endif

	sc->sc_flags |= (STF_OPEN);
	if (flag & FWRITE)
		sc->sc_flags |= STF_WMODE;
	sc->sc_flags &= ~STF_MOVED;

#ifdef TTI
	/* make stats available, also lit up TTi display */
	sc->sc_tticntdwn = 100;
#endif
	stxsense(ctlr, slave, unit, sc);

	return(0);
}

/*ARGSUSED*/
stclose(dev, flag)
	dev_t dev;
	int flag;
{
	register struct st_softc *sc = &st_softc[UNIT(dev)];
	register int hit = 0;

	if ((sc->sc_flags & (STF_WMODE|STF_WRTTN)) == (STF_WMODE|STF_WRTTN)) {
		/*
D 6
		 * XXX driver only supports cartridge tapes.
E 6
		 * Cartridge tapes don't do double EOFs on EOT.
I 6
		 * We assume that variable-block devices use double EOF.
E 6
		 */
		stcommand(dev, MTWEOF, 1); 
I 6
		if (sc->sc_blklen == 0) {
			stcommand(dev, MTWEOF, 1); 
			stcommand(dev, MTBSR, 1); 
		}
E 6
		hit++;
	}
	if ((minor(dev) & STDEV_NOREWIND) == 0) {
		stcommand(dev, MTREW, 1);
		hit++;
	}
#ifdef NOTDEF
	/* wait until more stable before trying [XXX Needed ?] */
	if (!hit && (sc->sc_flags & SFT_WMODE))
		/* force out any any bufferd write data */
		stcommand(dev, MTFSR, 0); 
#endif
	/* make stats available */
	stxsense(sc->sc_dq.dq_ctlr, sc->sc_dq.dq_slave, sc->sc_punit, sc);

	sc->sc_flags &= ~(STF_OPEN|STF_WMODE|STF_WRTTN);
D 3
	sc->sc_ctty = NULL;
E 3
I 3
	tprintf_close(sc->sc_ctty);
E 3
	return(0);	/* XXX */
}

I 15
void
E 15
ststrategy(bp)
	register struct buf *bp;
{
	struct buf *dp;
	int unit, s;

	unit = UNIT(bp->b_dev);
	dp = &sttab[unit];
D 8
	bp->av_forw = NULL;
E 8
I 8
	bp->b_actf = NULL;
E 8
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
		stustart(unit);
	}
	splx(s);
}

stustart(unit)
	int unit;
{
	if (scsireq(&st_softc[unit].sc_dq))
		ststart(unit);
}

ststart(unit)
	int unit;
{
	struct hp_device *hp = st_softc[unit].sc_hd;

	if (scsiustart(hp->hp_ctlr))
		stgo(unit);
}

stgo(unit)
	int unit;
{
	register struct st_softc *sc = &st_softc[unit];
	register struct scsi_fmt_cdb *cmd;
	register struct buf *bp = sttab[unit].b_actf;
	struct hp_device *hp = sc->sc_hd;
	int pad, stat;
	long nblks;

	if (sc->sc_flags & STF_CMD) {
		cmd = &stcmd[unit];
		pad = 0;
	} else {
		cmd = bp->b_flags & B_READ ? &st_read_cmd : &st_write_cmd;
		if (sc->sc_blklen)
			cmd->cdb[1] |= 0x01; /* fixed mode */
		else
			cmd->cdb[1] &= 0xfe;
		if (bp->b_flags & B_READ)
			sc->sc_flags &= ~STF_WRTTN;
		else
			sc->sc_flags |= STF_WRTTN;

		if (sc->sc_blklen) { /* fixed mode */
			nblks = bp->b_bcount / sc->sc_blklen;
			if (bp->b_bcount % sc->sc_blklen) {
				tprintf(sc->sc_ctty,
					"st%d: I/O not block aligned %d/%ld\n",
					unit, sc->sc_blklen, bp->b_bcount);
				cmd->cdb[1] &= 0xfe; /* force error */
			}
		} else	/* variable len */
			nblks = bp->b_bcount;

		*(u_char *)(&cmd->cdb[2]) = (u_char) (nblks >> 16);
		*(u_char *)(&cmd->cdb[3]) = (u_char) (nblks >> 8);
		*(u_char *)(&cmd->cdb[4]) = (u_char) nblks;
		/*
		 * Always Zero. We are either writing in variable
		 * length mode we are writing in fixed block mode,
		 * or we are going to do odd length IO and are not
		 * going to use DMA.
		 */
		pad = 0; 
	}

#ifdef DEBUG
	if (st_debug & ST_GO)
		printf("stgo: cmd len %d [0]0x%x [1]0x%x [2]0x%x [3]0x%x [4]0x%x [5]0x%x\n",
		       cmd->len, cmd->cdb[0], cmd->cdb[1], cmd->cdb[2],
		       cmd->cdb[3], cmd->cdb[4], cmd->cdb[5]);
#endif

	sc->sc_flags |= STF_MOVED;
	if (bp->b_bcount & 1) {
#ifdef DEBUG
		if (st_debug & ST_ODDIO)
			printf("stgo%d: odd count %d using manual transfer\n",
			       unit, bp->b_bcount);
#endif
		stat = scsi_tt_oddio(hp->hp_ctlr, hp->hp_slave, sc->sc_punit,
				     bp->b_un.b_addr, bp->b_bcount,
				     bp->b_flags, 1);
		if (stat == 0) {
			bp->b_resid = 0;
			stfinish(unit, sc, bp);
		}
	} else
		stat = scsigo(hp->hp_ctlr, hp->hp_slave, sc->sc_punit,
			      bp, cmd, pad);
	if (stat) {
		bp->b_error = EIO;
		bp->b_flags |= B_ERROR;
		stxsense(sc->sc_dq.dq_ctlr, sc->sc_dq.dq_slave, 
			 sc->sc_punit, sc);
		sterror(unit, sc, stat);
		stfinish(unit, sc, bp);
	}
}

stfinish(unit, sc, bp)
	int unit;
	struct st_softc *sc;
	struct buf *bp;
{
I 8
	register struct buf *dp;

E 8
	sttab[unit].b_errcnt = 0;
D 8
	sttab[unit].b_actf = bp->b_actf;
E 8
I 8
	if (dp = bp->b_actf)
		dp->b_actb = bp->b_actb;
	else
		sttab[unit].b_actb = bp->b_actb;
	*bp->b_actb = dp;
E 8
	iodone(bp);
	scsifree(&sc->sc_dq);
	if (sttab[unit].b_actf)
		stustart(unit);
	else
		sttab[unit].b_active = 0;
}

stread(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	int unit = UNIT(dev);

	return(physio(ststrategy, &stbuf[unit], dev, B_READ, minphys, uio));
}

stwrite(dev, uio)
	dev_t dev;
	struct uio *uio;
{
	int unit = UNIT(dev);

	return(physio(ststrategy, &stbuf[unit], dev, B_WRITE, minphys, uio));
}

/*ARGSUSED*/
stdump(dev)
	dev_t dev;
{
	return(ENXIO);
}

/*ARGSUSED*/
stioctl(dev, cmd, data, flag)
	dev_t dev;
D 15
	int cmd;
E 15
I 15
	u_long cmd;
E 15
	caddr_t data; 
	int flag;
{
	register struct st_softc *sc = &st_softc[UNIT(dev)];
	register int cnt;
	register struct mtget *mtget;
	register struct st_xsense *xp = &st_xsense[UNIT(dev)];
	register struct mtop *op;
	long resid;

	switch (cmd) {

	/* tape operation */
	case MTIOCTOP:
		op = (struct mtop *)data;
		switch (op->mt_op) {

		case MTBSR:
		case MTFSR:
			if (sc->sc_tapeid == MT_ISAR)
				return(ENXIO);
		case MTWEOF:
		case MTFSF:
		case MTBSF:
			cnt = (int)op->mt_count;
			break;

		case MTREW:
		case MTOFFL:
			cnt = 1;
			break;

		case MTNOP:
			return(0);
		default:
			return(EINVAL);
		}
		if (cnt <= 0)
			return(EINVAL);
		stcommand(dev, (u_int)op->mt_op, cnt);
		break;

	/* drive status */
	case MTIOCGET:
		mtget = (struct mtget *)data;
		stxsense(sc->sc_dq.dq_ctlr, sc->sc_dq.dq_slave, 
			 sc->sc_punit, sc);
		mtget->mt_type = sc->sc_tapeid;
		mtget->mt_dsreg = 0;
		mtget->mt_erreg = ((xp->sc_xsense.valid << 15) |
				   (xp->sc_xsense.filemark << 14) |
				   (xp->sc_xsense.eom << 13) |
				   (xp->sc_xsense.ili << 12) |
				   (xp->sc_xsense.key << 8));
		
		if (sc->sc_tapeid == MT_ISEXABYTE) {
			mtget->mt_dsreg = sc->sc_flags;
			resid = (xp->exb_xsense.tplft2 << 16 |
				 xp->exb_xsense.tplft1 << 8 |
				 xp->exb_xsense.tplft0);
			mtget->mt_resid = resid / 1000;
D 14
			mtget->mt_erreg |= (((xp->exb_xsense.rwerrcnt2 << 16 |
					      xp->exb_xsense.rwerrcnt1 << 8 |
					      xp->exb_xsense.rwerrcnt0) * 100) / 
					    (sc->sc_numblks - resid)) & 0xff;
E 14
I 14
			if (sc->sc_numblks - resid)
				mtget->mt_erreg |=
					(((xp->exb_xsense.rwerrcnt2 << 16 |
					   xp->exb_xsense.rwerrcnt1 << 8 |
					   xp->exb_xsense.rwerrcnt0) * 100) / 
					 (sc->sc_numblks - resid)) & 0xff;
E 14
		} else if (xp->sc_xsense.valid) {
			resid = ((xp->sc_xsense.info1 << 24) |
				 (xp->sc_xsense.info2 << 16) |
				 (xp->sc_xsense.info3 << 8) |
				 (xp->sc_xsense.info4));
			if (sc->sc_blklen) /* if fixed mode */
				resid *= sc->sc_blklen;
			mtget->mt_resid = resid;
		} else
			mtget->mt_resid = 0;
		break;

	default:
		return(ENXIO);
	}
	return(0);
}

stintr(unit, stat)
	int unit, stat;
{
	register struct st_softc *sc = &st_softc[unit];
	register struct st_xsense *xp = &st_xsense[unit];
	register struct buf *bp = sttab[unit].b_actf;
	struct hp_device *hp = sc->sc_hd;

#ifdef DEBUG
	if (bp == NULL) {
		printf("st%d: bp == NULL\n", unit);
		return;
	}
#endif
	switch (stat) {
	/* scsi command completed ok */
	case 0:
		bp->b_resid = 0;
		break;

	/* more status */
	case STS_CHECKCOND:
		stxsense(sc->sc_dq.dq_ctlr, sc->sc_dq.dq_slave, 
			 sc->sc_punit, sc);
		if (xp->sc_xsense.valid) {
			bp->b_resid = (u_long)((xp->sc_xsense.info1 << 24) |
					      (xp->sc_xsense.info2 << 16) |
					      (xp->sc_xsense.info3 << 8) |
					      (xp->sc_xsense.info4));
			if (sc->sc_blklen) /* fixed mode */
				bp->b_resid *= sc->sc_blklen;
		}
		if (xp->sc_xsense.filemark) {
			sc->sc_filepos++;
			break;
		}
D 4
		if (xp->sc_xsense.key) {
E 4
I 4
		if (xp->sc_xsense.key != XSK_NOSENCE
		    && xp->sc_xsense.key != XSK_NOTUSED1
		    && xp->sc_xsense.key != XSK_NOTUSEDC
		    && xp->sc_xsense.key != XSK_NOTUSEDE) {
E 4
			sterror(unit, sc, stat);
			bp->b_flags |= B_ERROR;
			bp->b_error = EIO;
			break;
		}
		if (xp->sc_xsense.ili) {
			/*
			 * Fixed length blocks, an error.
			 */
			if (sc->sc_blklen) {
				tprintf(sc->sc_ctty,
					"st%d: Incorrect Length Indicator, blkcnt diff %d\n",
					unit, sc->sc_blklen - bp->b_resid);
				bp->b_flags |= B_ERROR;
				bp->b_error = EIO;
				break;
			}
			/*
			 * Variable length but read more than requested,
D 6
			 * an error.
E 6
I 6
			 * an error.  (XXX ??? wrong for 9 track?)
E 6
			 */
			if (bp->b_resid < 0) {
				bp->b_resid = 0;
				bp->b_flags |= B_ERROR;
				bp->b_error = ENOMEM;
				break;
			}
			/*
			 * Variable length and odd, may require special
			 * handling.
			 */
D 4
			if (bp->b_resid & 1 && sc->sc_tapeid != MT_ISAR) {
E 4
I 4
D 6
			if (bp->b_resid & 1
			   && (sc->sc_tapeid != MT_ISAR 
			      || sc->sc_tapeid != MT_ISMFOUR)) {
E 6
I 6
			if (bp->b_resid & 1 && (sc->sc_tapeid != MT_ISAR)) {
E 6
E 4
				/*
				 * Normal behavior, treat as an error.
				 */
				if (!st_dmaoddretry) {
					tprintf(sc->sc_ctty,
						"st%d: Odd length read %d\n", 
						UNIT(bp->b_dev),
						bp->b_bcount - bp->b_resid);
					bp->b_error = EIO;
					bp->b_flags |= B_ERROR;
					break;
				}
				/*
				 * Attempt to back up and re-read using oddio.
				 */
#ifdef DEBUG
				if (st_debug & ST_ODDIO)
					printf("st%d: stintr odd count %d, do BSR then oddio\n",
					       UNIT(bp->b_dev),
					       bp->b_bcount - bp->b_resid);
#endif
				stat = scsi_tt_oddio(hp->hp_ctlr, hp->hp_slave,
						     sc->sc_punit, 0, -1, 0, 0);
				if (stat == 0)
					stat = scsi_tt_oddio(hp->hp_ctlr,
							     hp->hp_slave,
							     sc->sc_punit,
							     bp->b_un.b_addr,
							     bp->b_bcount - bp->b_resid,
							     bp->b_flags, 0);
				if (stat) {
					bp->b_error = EIO;
					bp->b_flags |= B_ERROR;
					stxsense(sc->sc_dq.dq_ctlr, sc->sc_dq.dq_slave,
						 sc->sc_punit, sc);
					sterror(unit, sc, stat);
				}
			}
			break;
		}
		if (xp->sc_xsense.eom) {
			bp->b_flags |= B_ERROR;
			bp->b_error = ENOSPC;
			break;
		}
		tprintf(sc->sc_ctty, "st%d: unknown scsi error\n", unit);
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
		break;

	default:
		printf("st%d: stintr unknown stat 0x%x\n", unit, stat);
		break;
	}
#ifdef DEBUG
	if ((st_debug & ST_BRESID) && bp->b_resid != 0)
		printf("b_resid %d b_flags 0x%x b_error 0x%x\n", 
		       bp->b_resid, bp->b_flags, bp->b_error);
#endif
	/* asked for more filemarks then on tape */
	if (bp->b_resid != 0 &&
	    (sc->sc_flags & STF_CMD) && sc->sc_cmd == CMD_SPACE) {
		sc->sc_filepos -= bp->b_resid;
		if (sc->sc_filepos < 0)
			sc->sc_filepos = 0;
	}

#ifdef TTI
	if (st_extti & (1<<unit) &&
	    sc->sc_type == MT_ISEXABYTE) /* to make display lit up */
		/*
		 * XXX severe performance penality for this.
		 * Try and throttle by not calling stxsense on every intr.
		 * Mostly for TTi we, get a stxsense call in open and close.
		 */
		if (sc->sc_tticntdwn-- == 0) {
			stxsense(sc->sc_dq.dq_ctlr, sc->sc_dq.dq_slave,
				 sc->sc_punit, sc);
			sc->sc_tticntdwn = 100;
		}
#endif

	stfinish(unit, sc, bp);
}

stcommand(dev, command, cnt)
	dev_t dev;
	u_int command;
	int cnt;
{
	register struct st_softc *sc = &st_softc[UNIT(dev)];
	register struct buf *bp = &stbuf[UNIT(dev)];
	register struct scsi_fmt_cdb *cmd = &stcmd[UNIT(dev)];
	register cmdcnt;
	int s;

	cmd->len = 6; /* all tape commands are cdb6 */
	cmd->cdb[1] = sc->sc_punit;
	cmd->cdb[2] = cmd->cdb[3] = cmd->cdb[4] = cmd->cdb[5] = 0;
	cmdcnt = 0;

	/*
	 * XXX Assumption is that everything except Archive can take
	 * repeat count in cdb block.
	 */
	switch (command) {
	case MTWEOF:
		cmd->cdb[0] = CMD_WRITE_FILEMARK;
		if (sc->sc_tapeid != MT_ISAR) {
			cmdcnt = cnt;
			cnt = 1;
		} else
			cmdcnt = 1;
		*(u_char *)(&cmd->cdb[2]) = (u_char) (cmdcnt >> 16);
		*(u_char *)(&cmd->cdb[3]) = (u_char) (cmdcnt >> 8);
		*(u_char *)(&cmd->cdb[4]) = (u_char) cmdcnt;

		if (sc->sc_tapeid == MT_ISEXABYTE &&
		    (minor(dev) & STDEV_EXSFMK)) /* short filemarks */
			cmd->cdb[5] |= 0x80;
		else
			cmd->cdb[5] &= 0x7f;
		break;
	case MTBSF:
		/* Archive can't back up, will not get to BSR case */
		if (sc->sc_tapeid == MT_ISAR) {
			if ((sc->sc_filepos - cnt) < 0) {
				stcommand(dev, MTREW, 1);
				return;
			}
			cmdcnt = sc->sc_filepos - cnt + 1;
			stcommand(dev, MTREW, 1);
			stcommand(dev, MTFSF, cmdcnt);
			return;
		}
	case MTBSR:
	case MTFSR:
	case MTFSF:
		if (command == MTBSF || command == MTBSR)
			cnt = cnt * (-1); /* backward move */
		if (command == MTFSF || command == MTBSF)
			cmd->cdb[1] |= 0x01; /* filemarks */
		else
			cmd->cdb[1] |= 0x00; /* logical blocks */
		if (sc->sc_tapeid != MT_ISAR) {
			cmdcnt = cnt;
			cnt = 1;
		} else
			cmdcnt = 1;
		*(u_char *)(&cmd->cdb[2]) = (u_char) (cmdcnt >> 16);
		*(u_char *)(&cmd->cdb[3]) = (u_char) (cmdcnt >> 8);
		*(u_char *)(&cmd->cdb[4]) = (u_char) cmdcnt;
		cmd->cdb[0] = CMD_SPACE;
		break;
	case MTREW:
		cmd->cdb[0] = CMD_REWIND;
		sc->sc_filepos = 0;
		break;
	case MTOFFL:
		cmd->cdb[0] = CMD_LOADUNLOAD;
		sc->sc_filepos = 0;
		break;
	default:
		printf("st%d: stcommand bad command 0x%x\n", 
		       UNIT(dev), command);
	}

	sc->sc_flags |= STF_CMD;
	sc->sc_cmd = cmd->cdb[0];

	sc->sc_bp = bp;
again:
#ifdef DEBUG
	if (st_debug & ST_FMKS)
		printf("st%d: stcommand filepos %d cmdcnt %d cnt %d\n", 
		       UNIT(dev), sc->sc_filepos, cmdcnt, cnt);
#endif
	s = splbio();
	while (bp->b_flags & B_BUSY) {
		if (bp->b_flags & B_DONE)
			break;
		bp->b_flags |= B_WANTED;
		sleep((caddr_t)bp, PRIBIO);
	}
	bp->b_flags = B_BUSY|B_READ;
	splx(s);
	bp->b_dev = dev;
	bp->b_bcount = 0;
	bp->b_resid = 0;
	bp->b_blkno = 0;
	bp->b_error = 0;
	ststrategy(bp);
	iowait(bp);
	if (bp->b_flags & B_WANTED)
		wakeup((caddr_t)bp);
	bp->b_flags &= B_ERROR;

	if (command == MTWEOF || command == MTFSF || command == MTBSF)
		sc->sc_filepos += cmdcnt;

	if (--cnt > 0)
		goto again;

	sc->sc_flags |= STF_MOVED;
	sc->sc_flags &= ~(STF_CMD|STF_WRTTN);
}

sterror(unit, sc, stat)
	int unit, stat;
	struct st_softc *sc;
{
	/* stxsense must have been called before sterror() */
	if (stat & STS_CHECKCOND)
		prtkey(unit, sc);
	else if (stat)
		tprintf(sc->sc_ctty,
			"st%d: bad scsi status 0x%x\n", unit, stat);

	if ((sc->sc_flags & STF_CMD) && sc->sc_cmd == CMD_SPACE) /* fsf */
		sc->sc_filepos--;
}

stxsense(ctlr, slave, unit, sc)
	int ctlr, slave, unit;
	struct st_softc *sc;
{
	u_char *sensebuf;
	unsigned len;

	sensebuf = (u_char *)&st_xsense[sc->sc_dq.dq_unit];
	len = sc->sc_datalen[CMD_REQUEST_SENSE];
	scsi_request_sense(ctlr, slave, unit, sensebuf, len);
}

prtkey(unit, sc)
	int unit;
	struct st_softc *sc;
{
	register struct st_xsense *xp = &st_xsense[unit];

	switch (xp->sc_xsense.key) {
	case XSK_NOSENCE:
		break;
	case XSK_NOTUSED1:
	case XSK_NOTUSEDC:
	case XSK_NOTUSEDE:
		break;
	case XSK_REVERVED:
		tprintf(sc->sc_ctty, "st%d: Reserved sense key 0x%x\n",
			unit, xp->sc_xsense.key);
		break;
	case XSK_NOTRDY:
		tprintf(sc->sc_ctty, "st%d: NOT READY\n", unit);
		break;
	case XSK_MEDERR:
		tprintf(sc->sc_ctty, "st%d: MEDIUM ERROR\n", unit);
		break;
	case XSK_HRDWERR:
		tprintf(sc->sc_ctty, "st%d: HARDWARE ERROR\n", unit);
		break;
	case XSK_ILLREQ:
		tprintf(sc->sc_ctty, "st%d: ILLEGAL REQUEST\n", unit);
		break;
	case XSK_UNTATTEN:
		tprintf(sc->sc_ctty, "st%d: UNIT ATTENTION\n", unit);
		break;
	case XSK_DATAPROT:
		tprintf(sc->sc_ctty, "st%d: DATA PROTECT\n", unit);
		break;
	case XSK_BLNKCHK:
		tprintf(sc->sc_ctty, "st%d: BLANK CHECK\n", unit);
		break;
	case XSK_VENDOR:
		tprintf(sc->sc_ctty, "st%d: VENDER UNIQUE SENSE KEY ", unit);
		switch (sc->sc_tapeid) {
		case MT_ISEXABYTE:
			tprintf(sc->sc_ctty, "Exabyte: ");
			if (xp->exb_xsense.xfr)
				tprintf(sc->sc_ctty,
					"Transfer Abort Error\n");
			if (xp->exb_xsense.tmd)
				tprintf(sc->sc_ctty,
					"Tape Mark Detect Error\n");
			break;
		default:
			tprintf(sc->sc_ctty, "\n");
		}
		break;
	case XSK_CPYABORT:
		tprintf(sc->sc_ctty, "st%d: COPY ABORTED\n", unit);
		break;
	case XSK_ABORTCMD:
		tprintf(sc->sc_ctty, "st%d: ABORTED COMMAND\n", unit);
		break;
	case XSK_VOLOVER:
		tprintf(sc->sc_ctty, "st%d: VOLUME OVERFLOW\n", unit);
		break;
	default:
		tprintf(sc->sc_ctty, "st%d: unknown sense key 0x%x\n",
			unit, xp->sc_xsense.key);
	}
	if (sc->sc_tapeid == MT_ISEXABYTE) {
		if (xp->exb_xsense.bpe)
			tprintf(sc->sc_ctty, "st%d: Bus Parity Errorn", unit);
		if (xp->exb_xsense.fpe)
			tprintf(sc->sc_ctty,
				"st%d: Formatted Buffer Parity Errorn", unit);
		if (xp->exb_xsense.eco)
			tprintf(sc->sc_ctty, "st%d: Error Counter Overflown",
				unit);
		if (xp->exb_xsense.tme)
			tprintf(sc->sc_ctty, "st%d: Tape Motion Errorn", unit);
		if (xp->exb_xsense.xfr)
			tprintf(sc->sc_ctty, "st%d: Transfer About Errorn",
				unit);
		if (xp->exb_xsense.tmd)
			tprintf(sc->sc_ctty, "st%d: Tape Mark Detect Errorn",
				unit);
		if (xp->exb_xsense.fmke)
			tprintf(sc->sc_ctty, "st%d: Filemark Errorn", unit);
		if (xp->exb_xsense.ure)
			tprintf(sc->sc_ctty, "st%d: Under Run Errorn", unit);
		if (xp->exb_xsense.sse)
			tprintf(sc->sc_ctty, "st%d: Servo System Errorn",
				unit);
		if (xp->exb_xsense.fe)
			tprintf(sc->sc_ctty, "st%d: Formatter Errorn", unit);
		if (xp->exb_xsense.wseb)
			tprintf(sc->sc_ctty, "st%d: WSEB Errorn", unit);
		if (xp->exb_xsense.wseo)
			tprintf(sc->sc_ctty, "st%d: WSEO Errorn", unit);
	}
}

#ifdef DEBUG

dumpxsense(sensebuf)
	struct st_xsense *sensebuf;
{
        struct st_xsense *xp = sensebuf;

	printf("valid 0x%x errorclass 0x%x errorcode 0x%x\n", 
	       xp->sc_xsense.valid, 
	       xp->sc_xsense.class, xp->sc_xsense.code);
	printf("seg number 0x%x\n", xp->sc_xsense.segment);
	printf("FMK 0x%x EOM 0x%x ILI 0x%x RSVD 0x%x sensekey 0x%x\n", 
	       xp->sc_xsense.filemark, xp->sc_xsense.eom, xp->sc_xsense.ili, 
	       xp->sc_xsense.rsvd, xp->sc_xsense.key);
	printf("info 0x%lx\n", 
	       (u_long)((xp->sc_xsense.info1<<24)|(xp->sc_xsense.info2<<16)|
			(xp->sc_xsense.info3<<8)|(xp->sc_xsense.info4)) );
	printf("ASenseL 0x%x\n", xp->sc_xsense.len);

	if (xp->sc_xsense.len != 0x12) /* MT_ISEXB Exabyte only ?? */
		return;			/* What about others */

	printf("ASenseC 0x%x\n", xp->exb_xsense.addsens);
	printf("AsenseQ 0x%x\n", xp->exb_xsense.addsensq);
	printf("R/W Errors 0x%lx\n", 
	       (u_long)((xp->exb_xsense.rwerrcnt2<<16)|
			(xp->exb_xsense.rwerrcnt1<<8)|
			(xp->exb_xsense.rwerrcnt1)) );
	printf("PF   0x%x BPE  0x%x FPE 0x%x ME   0x%x ECO 0x%x TME 0x%x TNP 0x%x BOT 0x%x\n",
	       xp->exb_xsense.pf, xp->exb_xsense.bpe, xp->exb_xsense.fpe, 
	       xp->exb_xsense.me, xp->exb_xsense.eco, xp->exb_xsense.tme, 
	       xp->exb_xsense.tnp, xp->exb_xsense.bot);
	printf("XFR  0x%x TMD  0x%x WP  0x%x FMKE 0x%x URE 0x%x WE1 0x%x SSE 0x%x FE  0x%x\n",
	       xp->exb_xsense.xfr, xp->exb_xsense.tmd, xp->exb_xsense.wp, 
	       xp->exb_xsense.fmke, xp->exb_xsense.ure, xp->exb_xsense.we1, 
	       xp->exb_xsense.sse, xp->exb_xsense.fe);
	printf("WSEB 0x%x WSEO 0x%x\n",
	       xp->exb_xsense.wseb, xp->exb_xsense.wseo);
	printf("Remaining Tape 0x%lx\n", 
	       (u_long)((xp->exb_xsense.tplft2<<16)|
			(xp->exb_xsense.tplft1<<8)|
			(xp->exb_xsense.tplft0)) );
}

prtmodsel(msd, modlen)
	struct mode_select_data *msd;
	int modlen;
{
	printf("Modsel command. len is 0x%x.\n", modlen);
	printf("rsvd1 0x%x rsvd2 0x%x rsvd3 0x%x bufferd 0x%x speed 0x%x bckdeslen 0x%x\n",
	       msd->rsvd1,msd->rsvd2,msd->rsvd3,msd->buff,msd->speed,msd->blkdeslen);
	printf("density 0x%x blks2 0x%x blks1 0x%x blks0 0x%x rsvd 0x%x blklen2 0x%x blklen1 0x%x blklen0 0x%x\n",
	       msd->density,msd->blks2,msd->blks1,msd->blks0,msd->rsvd4,msd->blklen2,msd->blklen1,msd->blklen0);
	printf("vupb 0x%x rsvd 0x%x p5 0x%x motionthres 0x%x reconthres 0x%x gapthres 0x%x \n",
	       msd->vupb,msd->rsvd5,msd->p5,msd->motionthres,msd->reconthres,msd->gapthres);
}

prtmodstat(mode)
	struct mode_sense *mode;
{
	printf("Mode Status\n");
	printf("sdl 0x%x medtype 0x%x wp 0x%x bfmd 0x%x speed 0x%x bdl 0x%x\n",
	       mode->md.sdl, mode->md.medtype, mode->md.wp, mode->md.bfmd, 
	       mode->md.speed, mode->md.bdl);
	printf("dencod 0x%x numblk 0x%x blklen 0x%x\n",
	       mode->md.dencod, 
	       (mode->md.numblk2<<16)|(mode->md.numblk1<<8)|(mode->md.numblk0),
	       (mode->md.blklen2<<16)|(mode->md.blklen1<<8)|(mode->md.blklen0) );
	printf("ct 0x%x nd 0x%x nbe 0x%x edb 0x%x pe 0x%x nal 0x%x p5 0x%x\n",
	       mode->ex.ct, mode->ex.nd, mode->ex.nbe, 
	       mode->ex.ebd, mode->ex.pe, mode->ex.nal, mode->ex.p5);
	printf("motionthres 0x%x reconthres 0x%x gapthres 0x%x\n",
	       mode->ex.motionthres, mode->ex.reconthres,  mode->ex.gapthres);
}
#endif /* DEBUG */

#endif
E 1
