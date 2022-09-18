h30573
s 00001/00004/01163
d D 8.9 95/05/14 00:51:37 mckusick 28 27
c just use <vm/vm.h> for VM include files
e
s 00003/00015/01164
d D 8.8 95/05/10 10:33:04 mckusick 27 26
c avoid panic's on attempted open's of non-existent devices
e
s 00001/00001/01178
d D 8.7 95/05/10 10:31:26 root 26 25
c lock.h moves to /sys/sys
e
s 00001/00001/01178
d D 8.6 95/01/09 18:28:56 cgd 25 24
c ioctl cmd arg is u_long, strategy returns void.
e
s 00003/00000/01176
d D 8.5 94/05/19 21:40:45 hibler 24 23
c if no label, reset partition info since readdisklabel changes it
e
s 00010/00001/01166
d D 8.4 94/04/22 13:32:32 hibler 23 22
c make sure even root can't open a drive that was not fully qualified
e
s 00043/00024/01124
d D 8.3 94/02/13 10:38:46 hibler 22 21
c don't use a kernel stack buffer!
c sc_format_pid "null" value is now -1 instead of 0
e
s 00197/00088/00951
d D 8.2 94/01/12 14:36:03 hibler 21 20
c improvements for removable media
e
s 00002/00002/01037
d D 8.1 93/06/10 21:34:26 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/01039
d D 7.19 93/06/05 13:41:07 mckusick 19 18
c don't fail on sdopen even in the face of an I/O error (to allow formatting)
e
s 00004/00000/01037
d D 7.18 93/02/18 20:47:11 hibler 18 17
c default ncylinders to 1 for disklabel, avoid zero-divide in open
e
s 00245/00134/00792
d D 7.17 92/12/27 09:32:37 hibler 17 16
c disklabel support
e
s 00015/00014/00911
d D 7.16 92/10/11 09:24:10 bostic 16 15
c make kernel includes standard
e
s 00001/00000/00924
d D 7.15 92/07/20 12:10:23 bostic 15 14
c needs ioctl.h, now that scsireg.h doesn't include it
e
s 00001/00001/00923
d D 7.14 92/07/12 17:43:37 pendry 14 13
c MIN -> min
e
s 00044/00008/00880
d D 7.13 92/06/05 15:31:01 hibler 13 12
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00887
d D 7.12 92/02/19 21:03:03 mckusick 12 11
c pmap_kernel() becomes kernel_pmap
e
s 00002/00001/00886
d D 7.11 91/11/05 17:03:05 mckusick 11 10
c lint
e
s 00001/00001/00886
d D 7.10 91/09/12 16:44:23 marc 10 9
c need vm_prot.h before pmap.h
e
s 00000/00001/00887
d D 7.9 91/08/28 15:48:30 mckusick 9 8
c no longer need vm_statistics.h
e
s 00030/00015/00858
d D 7.8 91/06/09 13:22:31 karels 8 7
c from hibler: don't need retry on key 1
e
s 00005/00002/00868
d D 7.7 91/06/09 13:19:14 karels 7 6
c make retry printf's conditional on debug
e
s 00037/00036/00833
d D 7.6 91/05/07 09:48:33 hibler 6 5
c updates from utah
e
s 00026/00027/00843
d D 7.5 91/05/04 19:49:14 karels 5 4
c update to current include, device calling conventions
e
s 00013/00013/00857
d D 7.4 90/12/16 16:37:14 bostic 4 3
c kernel reorg
e
s 00093/00036/00777
d D 7.3 90/12/05 18:26:42 mckusick 3 2
c update from Mike Hibler for new VM and other machine support
e
s 00001/00001/00812
d D 7.2 90/05/15 22:04:42 mckusick 2 1
c use proper include files
e
s 00813/00000/00000
d D 7.1 90/05/08 22:07:08 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 20
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson of Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SCSI CCS (Command Command Set) disk driver.
 */
#include "sd.h"
#if NSD > 0

#ifndef lint
D 3
static char rcsid[] = "$Header: sd.c,v 1.5 90/01/10 16:06:12 mike Locked $";
E 3
I 3
D 6
static char rcsid[] = "$Header: sd.c,v 1.3 90/10/10 14:55:10 mike Exp $";
E 6
I 6
D 13
static char rcsid[] = "$Header: sd.c,v 1.15 91/04/24 11:54:30 mike Exp $";
E 13
I 13
D 17
static char rcsid[] = "$Header: /usr/src/sys/hp300/dev/RCS/sd.c,v 1.2 92/04/10 20:48:35 mike Exp $";
E 17
I 17
D 21
static char rcsid[] = "$Header: /usr/src/sys/hp300/dev/RCS/sd.c,v 1.4 92/12/26 13:26:40 mike Exp $";
E 21
I 21
static char rcsid[] = "$Header: /sys.lite/hp300/dev/RCS/sd.c,v 1.2 1994/01/10 18:29:19 mike Exp mike $";
E 21
E 17
E 13
E 6
E 3
#endif

D 4
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "errno.h"
#include "dkstat.h"
#include "disklabel.h"
E 4
I 4
D 16
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
D 5
#include "sys/errno.h"
E 5
#include "sys/dkstat.h"
#include "sys/disklabel.h"
E 4
D 5
#include "device.h"
E 5
D 4
#include "malloc.h"
E 4
I 4
#include "sys/malloc.h"
E 4
D 5
#include "scsireg.h"

D 4
#include "user.h"
#include "proc.h"
#include "uio.h"
E 4
I 4
#include "sys/user.h"
E 5
#include "sys/proc.h"
I 15
#include "sys/ioctl.h"
E 16
I 16
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
I 17
#include <sys/stat.h>
E 17
#include <sys/dkstat.h>
#include <sys/disklabel.h>
#include <sys/malloc.h>
#include <sys/proc.h>
#include <sys/ioctl.h>
I 17
#include <sys/fcntl.h>
E 17
E 16
E 15
D 5
#include "sys/uio.h"
E 5
E 4

I 5
D 13
#include "device.h"
E 13
I 13
D 16
#include "hp/dev/device.h"
E 13
#include "scsireg.h"
E 5
I 3
D 4
#include "../vm/vm_param.h"
#include "../vm/pmap.h"
#include "../vm/vm_prot.h"
E 4
I 4
#include "vm/vm_param.h"
I 5
#include "vm/lock.h"
D 9
#include "vm/vm_statistics.h"
E 9
E 5
D 10
#include "vm/pmap.h"
E 10
#include "vm/vm_prot.h"
I 10
#include "vm/pmap.h"
E 16
I 16
#include <hp/dev/device.h>
#include <hp300/dev/scsireg.h>
I 17
#include <hp300/dev/sdvar.h>
#ifdef USELEDS
#include <hp300/hp300/led.h>
#endif
E 17

D 28
#include <vm/vm_param.h>
D 26
#include <vm/lock.h>
E 26
I 26
#include <sys/lock.h>
E 26
#include <vm/vm_prot.h>
#include <vm/pmap.h>
E 28
I 28
#include <vm/vm.h>
E 28
E 16
E 10
E 4

E 3
extern int scsi_test_unit_rdy();
extern int scsi_request_sense();
extern int scsi_inquiry();
extern int scsi_read_capacity();
extern int scsi_tt_write();
extern int scsireq();
extern int scsiustart();
extern int scsigo();
extern void scsifree();
extern void scsireset();
I 6
extern void scsi_delay();
E 6

D 5
extern void printf();
extern void bcopy();
E 5
extern void disksort();
D 5
extern int splbio();
extern void splx();
E 5
extern void biodone();
extern int physio();
extern void TBIS();

int	sdinit();
void	sdstrategy(), sdstart(), sdustart(), sdgo(), sdintr();

struct	driver sddriver = {
	sdinit, "sd", (int (*)())sdstart, (int (*)())sdgo, (int (*)())sdintr,
};

D 17
struct	size {
	u_long	strtblk;
	u_long	endblk;
	int	nblocks;
};

struct sdinfo {
	struct	size part[8];
};

/*
 * since the SCSI standard tends to hide the disk structure, we define
 * partitions in terms of DEV_BSIZE blocks.  The default partition table
 * (for an unlabeled disk) reserves 512K for a boot area, has an 8 meg
 * root and 32 meg of swap.  The rest of the space on the drive goes in
 * the G partition.  As usual, the C partition covers the entire disk
 * (including the boot area).
 */
struct sdinfo sddefaultpart = {
	     1024,   17408,   16384   ,	/* A */
	    17408,   82944,   65536   ,	/* B */
	        0,       0,       0   ,	/* C */
	    17408,  115712,   98304   ,	/* D */
	   115712,  218112,  102400   ,	/* E */
	   218112,       0,       0   ,	/* F */
	    82944,       0,       0   ,	/* G */
	   115712,       0,       0   ,	/* H */
};

struct	sd_softc {
	struct	hp_device *sc_hd;
	struct	devqueue sc_dq;
	int	sc_format_pid;	/* process using "format" mode */
	short	sc_flags;
	short	sc_type;	/* drive type */
	short	sc_punit;	/* physical unit (scsi lun) */
	u_short	sc_bshift;	/* convert device blocks to DEV_BSIZE blks */
	u_int	sc_blks;	/* number of blocks on device */
	int	sc_blksize;	/* device block size in bytes */
	u_int	sc_wpms;	/* average xfer rate in 16 bit wds/sec. */
	struct	sdinfo sc_info;	/* drive partition table & label info */
} sd_softc[NSD];

/* sc_flags values */
#define	SDF_ALIVE	0x1
I 13
#define SDF_WANTED	0x2
#define SDF_RMEDIA	0x4
E 13

E 17
#ifdef DEBUG
int sddebug = 1;
#define SDB_ERROR	0x01
#define SDB_PARTIAL	0x02
I 21
#define SDB_CAPACITY	0x04
E 21
#endif

D 17
struct sdstats {
	long	sdresets;
	long	sdtransfers;
	long	sdpartials;
} sdstats[NSD];

E 17
I 17
struct	sd_softc sd_softc[NSD];
struct	sdstats sdstats[NSD];
E 17
struct	buf sdtab[NSD];
D 5
struct	buf sdbuf[NSD];
E 5
struct	scsi_fmt_cdb sdcmd[NSD];
struct	scsi_fmt_sense sdsense[NSD];

static struct scsi_fmt_cdb sd_read_cmd = { 10, CMD_READ_EXT };
static struct scsi_fmt_cdb sd_write_cmd = { 10, CMD_WRITE_EXT };

D 5
#define	sdunit(x)	((minor(x) >> 3) & 0x7)
E 5
I 5
D 17
#define	sdunit(x)	(minor(x) >> 3)
E 5
#define sdpart(x)	(minor(x) & 0x7)
#define	sdpunit(x)	((x) & 7)
#define	b_cylin		b_resid
I 3

E 3
#define	SDRETRY		2

E 17
/*
 * Table of scsi commands users are allowed to access via "format"
 * mode.  0 means not legal.  1 means "immediate" (doesn't need dma).
 * -1 means needs dma and/or wait for intr.
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

static struct scsi_inquiry inqbuf;
static struct scsi_fmt_cdb inq = {
	6,
	CMD_INQUIRY, 0, 0, 0, sizeof(inqbuf), 0
};

D 21
static u_char capbuf[8];
struct scsi_fmt_cdb cap = {
	10,
	CMD_READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

E 21
static int
sdident(sc, hd)
	struct sd_softc *sc;
	struct hp_device *hd;
{
	int unit;
	register int ctlr, slave;
	register int i;
	register int tries = 10;
I 6
	char idstr[32];
E 6
I 3
D 21
	int ismo = 0;
E 21
I 21
	int isrm = 0;
E 21
E 3

	ctlr = hd->hp_ctlr;
	slave = hd->hp_slave;
	unit = sc->sc_punit;
I 6
	scsi_delay(-1);
E 6

	/*
	 * See if unit exists and is a disk then read block size & nblocks.
	 */
	while ((i = scsi_test_unit_rdy(ctlr, slave, unit)) != 0) {
D 3
		if (i == -1 || --tries < 0)
E 3
I 3
		if (i == -1 || --tries < 0) {
D 21
			if (ismo)
E 21
I 21
			if (isrm)
E 21
				break;
E 3
			/* doesn't exist or not a CCS device */
D 6
			return (-1);
E 6
I 6
			goto failed;
E 6
I 3
		}
E 3
		if (i == STS_CHECKCOND) {
			u_char sensebuf[128];
			struct scsi_xsense *sp = (struct scsi_xsense *)sensebuf;

			scsi_request_sense(ctlr, slave, unit, sensebuf,
					   sizeof(sensebuf));
D 3
			if (sp->class == 7 && sp->key == 6)
E 3
I 3
			if (sp->class == 7)
				switch (sp->key) {
D 21
				/* not ready -- might be MO with no media */
E 21
I 21
				/*
				 * Not ready -- might be removable media
				 * device with no media.  Assume as much,
				 * if it really isn't, the inquiry commmand
				 * below will fail.
				 */
E 21
				case 2:
D 21
					if (sp->len == 12 &&
					    sensebuf[12] == 10)	/* XXX */
						ismo = 1;
E 21
I 21
					isrm = 1;
E 21
					break;
E 3
				/* drive doing an RTZ -- give it a while */
D 3
				DELAY(1000000);
E 3
I 3
				case 6:
					DELAY(1000000);
					break;
				default:
					break;
				}
E 3
		}
		DELAY(1000);
	}
D 3
	if (scsi_immed_command(ctlr, slave, unit, &inq, (u_char *)&inqbuf,
			       sizeof(inqbuf), B_READ) ||
	    scsi_immed_command(ctlr, slave, unit, &cap, (u_char *)&capbuf,
			       sizeof(capbuf), B_READ))
		/* doesn't exist or not a CCS device */
		return (-1);

E 3
I 3
	/*
	 * Find out about device
	 */
	if (scsi_immed_command(ctlr, slave, unit, &inq,
			       (u_char *)&inqbuf, sizeof(inqbuf), B_READ))
D 6
		return(-1);
E 6
I 6
		goto failed;
E 6
E 3
	switch (inqbuf.type) {
	case 0:		/* disk */
	case 4:		/* WORM */
	case 5:		/* CD-ROM */
	case 7:		/* Magneto-optical */
		break;
	default:	/* not a disk */
D 6
		return (-1);
E 6
I 6
		goto failed;
E 6
	}
D 3
	sc->sc_blks = *(u_int *)&capbuf[0];
	sc->sc_blksize = *(int *)&capbuf[4];
E 3
I 3
	/*
D 6
	 * XXX determine if this is an HP MO drive.
E 6
I 6
	 * Get a usable id string
E 6
	 */
D 6
	{
		u_long *id = (u_long *)&inqbuf;
E 3

I 3
		ismo = (id[2] == 0x48502020 &&	/* "HP  " */
			id[3] == 0x20202020 &&	/* "    " */
			id[4] == 0x53363330 &&	/* "S630" */
			id[5] == 0x302e3635 &&	/* "0.65" */
			id[6] == 0x30412020);	/* "0A  " */
E 6
I 6
D 17
	if (inqbuf.version != 1) {
		bcopy("UNKNOWN", &idstr[0], 8);
		bcopy("DRIVE TYPE", &idstr[8], 11);
	} else {
E 17
I 17
	switch (inqbuf.version) {
	case 1:
	case 2:
E 17
		bcopy((caddr_t)&inqbuf.vendor_id, (caddr_t)idstr, 28);
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
I 17
		break;
	default:
		bcopy("UNKNOWN", &idstr[0], 8);
		bcopy("DRIVE TYPE", &idstr[8], 11);
E 17
E 6
	}
D 21
	i = scsi_immed_command(ctlr, slave, unit, &cap,
			       (u_char *)&capbuf, sizeof(capbuf), B_READ);
	if (i) {
I 6
		if (i != STS_CHECKCOND ||
		    bcmp(&idstr[0], "HP", 3) ||
		    bcmp(&idstr[8], "S6300.650A", 11))
			goto failed;
E 6
		/* XXX unformatted or non-existant MO media; fake it */
D 6
		if (i == STS_CHECKCOND && ismo) {
			sc->sc_blks = 318664;
			sc->sc_blksize = 1024;
		} else
			return(-1);
E 6
I 6
		sc->sc_blks = 318664;
		sc->sc_blksize = 1024;
E 6
	} else {
		sc->sc_blks = *(u_int *)&capbuf[0];
		sc->sc_blksize = *(int *)&capbuf[4];
	}
	/* return value of read capacity is last valid block number */
	sc->sc_blks++;
E 21
I 21
	if (inqbuf.qual & 0x80)
		sc->sc_flags |= SDF_RMEDIA;
E 21

I 21
	if (sdgetcapacity(sc, hd, NODEV) < 0)
		goto failed;

E 21
E 3
D 17
	if (inqbuf.version != 1)
		printf("sd%d: type 0x%x, qual 0x%x, ver %d", hd->hp_unit,
			inqbuf.type, inqbuf.qual, inqbuf.version);
D 6
	else {
		char idstr[32];

		bcopy((caddr_t)&inqbuf.vendor_id, (caddr_t)idstr, 28);
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
E 6
I 6
	else
E 17
I 17
	switch (inqbuf.version) {
	case 1:
	case 2:
E 17
E 6
		printf("sd%d: %s %s rev %s", hd->hp_unit, idstr, &idstr[8],
			&idstr[24]);
I 17
		if (inqbuf.version == 2)
			printf(" (SCSI-2)");
		break;
	default:
		printf("sd%d: type 0x%x, qual 0x%x, ver %d", hd->hp_unit,
		       inqbuf.type, inqbuf.qual, inqbuf.version);
		break;
	}
E 17
D 6
	}
E 6
D 21
	printf(", %d %d byte blocks\n", sc->sc_blks, sc->sc_blksize);
I 13
	if (inqbuf.qual & 0x80)
		sc->sc_flags |= SDF_RMEDIA;
E 13
	if (sc->sc_blksize != DEV_BSIZE) {
		if (sc->sc_blksize < DEV_BSIZE) {
			printf("sd%d: need %d byte blocks - drive ignored\n",
				unit, DEV_BSIZE);
D 6
			return (-1);
E 6
I 6
			goto failed;
E 6
		}
		for (i = sc->sc_blksize; i > DEV_BSIZE; i >>= 1)
			++sc->sc_bshift;
		sc->sc_blks <<= sc->sc_bshift;
	}
E 21
I 21
	if (sc->sc_blks)
		printf(", %d %d byte blocks",
		       sc->sc_blks >> sc->sc_bshift, sc->sc_blksize);
	printf("\n");
E 21
	sc->sc_wpms = 32 * (60 * DEV_BSIZE / 2);	/* XXX */
I 6
	scsi_delay(0);
E 6
	return(inqbuf.type);
I 6
failed:
	scsi_delay(0);
	return(-1);
E 6
}

int
sdinit(hd)
	register struct hp_device *hd;
{
	register struct sd_softc *sc = &sd_softc[hd->hp_unit];

	sc->sc_hd = hd;
I 13
	sc->sc_flags = 0;
I 22
	/*
	 * XXX formerly 0 meant unused but now pid 0 can legitimately
	 * use this interface (sdgetcapacity).
	 */
	sc->sc_format_pid = -1;
E 22
E 13
	sc->sc_punit = sdpunit(hd->hp_flags);
	sc->sc_type = sdident(sc, hd);
	if (sc->sc_type < 0)
		return(0);
	sc->sc_dq.dq_ctlr = hd->hp_ctlr;
	sc->sc_dq.dq_unit = hd->hp_unit;
	sc->sc_dq.dq_slave = hd->hp_slave;
	sc->sc_dq.dq_driver = &sddriver;

D 17
	/*
	 * If we don't have a disk label, build a default partition
	 * table with 'standard' size root & swap and everything else
	 * in the G partition.
	 */
	sc->sc_info = sddefaultpart;
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
	} else {
		sc->sc_info.part[7].strtblk = 0;
	}

E 17
D 13
	sc->sc_flags = SDF_ALIVE;
E 13
I 13
	sc->sc_flags |= SDF_ALIVE;
E 13
	return(1);
}

void
sdreset(sc, hd)
	register struct sd_softc *sc;
	register struct hp_device *hd;
{
	sdstats[hd->hp_unit].sdresets++;
}

I 17
/*
I 21
 * Determine capacity of a drive.
 * Returns -1 on a failure, 0 on success, 1 on a failure that is probably
 * due to missing media.
 */
int
sdgetcapacity(sc, hd, dev)
	struct sd_softc *sc;
	struct hp_device *hd;
	dev_t dev;
{
	static struct scsi_fmt_cdb cap = {
		10,
		CMD_READ_CAPACITY, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
D 22
	u_char capbuf[8];
	struct buf tbuf;
	int i;
E 22
I 22
	u_char *capbuf;
	int i, capbufsize;
E 22

I 22
	/*
	 * Cannot use stack space for this buffer since stack KVA may not
	 * be valid (i.e. in context of this process) when the operation
	 * actually starts.
	 */
	capbufsize = 8;
	capbuf = malloc(capbufsize, M_DEVBUF, M_WAITOK);

E 22
	if (dev == NODEV) {
		i = scsi_immed_command(hd->hp_ctlr, hd->hp_slave, sc->sc_punit,
D 22
				       &cap, capbuf, sizeof(capbuf), B_READ);
E 22
I 22
				       &cap, capbuf, capbufsize, B_READ);
E 22
	} else {
I 22
		struct buf *bp;

E 22
		/*
		 * XXX this is horrible
		 */
D 22
		if (sc->sc_format_pid)
E 22
I 22
		if (sc->sc_format_pid >= 0)
E 22
			panic("sdgetcapacity");
I 22
		bp = malloc(sizeof *bp, M_DEVBUF, M_WAITOK);
E 22
		sc->sc_format_pid = curproc->p_pid;
		bcopy((caddr_t)&cap, (caddr_t)&sdcmd[hd->hp_unit], sizeof cap);
D 22
		tbuf.b_dev = dev;
		tbuf.b_flags = B_READ | B_BUSY;
		tbuf.b_un.b_addr = (caddr_t)capbuf;
		tbuf.b_bcount = sizeof capbuf;
		sdstrategy(&tbuf);
		i = biowait(&tbuf) ? sdsense[hd->hp_unit].status : 0;
		sc->sc_format_pid = 0;
E 22
I 22
		bp->b_dev = dev;
		bp->b_flags = B_READ | B_BUSY;
		bp->b_un.b_addr = (caddr_t)capbuf;
		bp->b_bcount = capbufsize;
		sdstrategy(bp);
		i = biowait(bp) ? sdsense[hd->hp_unit].status : 0;
		free(bp, M_DEVBUF);
		sc->sc_format_pid = -1;
E 22
	}
	if (i) {
		if (i != STS_CHECKCOND || (sc->sc_flags & SDF_RMEDIA) == 0) {
#ifdef DEBUG
			if (sddebug & SDB_CAPACITY)
				printf("sd%d: read_capacity returns %d\n",
				       hd->hp_unit, i);
#endif
I 22
			free(capbuf, M_DEVBUF);
E 22
			return (-1);
		}
		/*
		 * XXX assume unformatted or non-existant media
		 */
		sc->sc_blks = 0;
		sc->sc_blksize = DEV_BSIZE;
		sc->sc_bshift = 0;
#ifdef DEBUG
		if (sddebug & SDB_CAPACITY)
			printf("sd%d: removable media not present\n",
			       hd->hp_unit);
#endif
I 22
		free(capbuf, M_DEVBUF);
E 22
		return (1);
	}
	sc->sc_blks = *(u_int *)&capbuf[0];
	sc->sc_blksize = *(int *)&capbuf[4];
I 22
	free(capbuf, M_DEVBUF);
E 22
	sc->sc_bshift = 0;

	/* return value of read capacity is last valid block number */
	sc->sc_blks++;

	if (sc->sc_blksize != DEV_BSIZE) {
		if (sc->sc_blksize < DEV_BSIZE) {
D 22
			printf("sd%d: need %d byte blocks - drive ignored\n",
				hd->hp_unit, DEV_BSIZE);
E 22
I 22
			printf("sd%d: need at least %d byte blocks - %s\n",
				hd->hp_unit, DEV_BSIZE, "drive ignored");
E 22
			return (-1);
		}
		for (i = sc->sc_blksize; i > DEV_BSIZE; i >>= 1)
			++sc->sc_bshift;
		sc->sc_blks <<= sc->sc_bshift;
	}
#ifdef DEBUG
	if (sddebug & SDB_CAPACITY)
		printf("sd%d: blks=%d, blksize=%d, bshift=%d\n", hd->hp_unit,
		       sc->sc_blks, sc->sc_blksize, sc->sc_bshift);
#endif
	return (0);
}

/*
E 21
 * Read or constuct a disklabel
 */
E 17
int
I 17
sdgetinfo(dev)
	dev_t dev;
{
	int unit = sdunit(dev);
	register struct sd_softc *sc = &sd_softc[unit];
	register struct disklabel *lp = &sc->sc_info.si_label;
	register struct partition *pi;
	char *msg, *readdisklabel();
I 21
#ifdef COMPAT_NOLABEL
	int usedefault = 1;
E 21

	/*
D 21
	 * Set some default values to use while reading the label
	 * or to use if there isn't a label.
E 21
I 21
	 * For CD-ROM just define a single partition
E 21
	 */
I 21
	if (sc->sc_type == 5)
		usedefault = 0;
#endif

E 21
	bzero((caddr_t)lp, sizeof *lp);
D 21
	lp->d_type = DTYPE_SCSI;
	lp->d_secsize = DEV_BSIZE;
	lp->d_nsectors = 32;
	lp->d_ntracks = 20;
I 18
	lp->d_ncylinders = 1;
E 18
	lp->d_secpercyl = 32*20;
	lp->d_npartitions = 3;
	lp->d_partitions[2].p_offset = 0;
I 18
	/* XXX we can open a device even without SDF_ALIVE */
	if (sc->sc_blksize == 0)
		sc->sc_blksize = DEV_BSIZE;
E 18
	/* XXX ensure size is at least one device block */
	lp->d_partitions[2].p_size =
		roundup(LABELSECTOR+1, btodb(sc->sc_blksize));
E 21
I 21
	msg = NULL;
E 21

	/*
D 21
	 * Now try to read the disklabel
E 21
I 21
	 * If removable media or the size unavailable at boot time
	 * (i.e. unformatted hard disk), attempt to set the capacity
	 * now.
E 21
	 */
D 21
	msg = readdisklabel(sdlabdev(dev), sdstrategy, lp);
	if (msg == NULL)
		return(0);
E 21
I 21
	if ((sc->sc_flags & SDF_RMEDIA) || sc->sc_blks == 0) {
		switch (sdgetcapacity(sc, sc->sc_hd, dev)) {
		case 0:
			break;
		case -1:
			/*
			 * Hard error, just return (open will fail).
			 */
			return (EIO);
		case 1:
			/*
			 * XXX return 0 so open can continue just in case
			 * the media is unformatted and we want to format it.
			 * We set the error flag so they cannot do much else.
			 */
			sc->sc_flags |= SDF_ERROR;
			msg = "unformatted/missing media";
#ifdef COMPAT_NOLABEL
			usedefault = 0;
#endif
			break;
		}
	}
E 21
D 19
	if (bcmp(msg, "I/O", 3) == 0) /* XXX */
		return(EIO);
E 19

I 21
	/*
	 * Set some default values to use while reading the label
	 * (or to use if there isn't a label) and try reading it.
	 */
	if (msg == NULL) {
		lp->d_type = DTYPE_SCSI;
		lp->d_secsize = DEV_BSIZE;
		lp->d_nsectors = 32;
		lp->d_ntracks = 20;
		lp->d_ncylinders = 1;
		lp->d_secpercyl = 32*20;
		lp->d_npartitions = 3;
		lp->d_partitions[2].p_offset = 0;
		/* XXX we can open a device even without SDF_ALIVE */
		if (sc->sc_blksize == 0)
			sc->sc_blksize = DEV_BSIZE;
		/* XXX ensure size is at least one device block */
		lp->d_partitions[2].p_size =
			roundup(LABELSECTOR+1, btodb(sc->sc_blksize));
		msg = readdisklabel(sdlabdev(dev), sdstrategy, lp);
		if (msg == NULL)
			return (0);
	}

E 21
	pi = lp->d_partitions;
	printf("sd%d: WARNING: %s, ", unit, msg);
#ifdef COMPAT_NOLABEL
D 21
	printf("using old default partitioning\n");
	sdmakedisklabel(unit, lp);
#else
E 21
I 21
	if (usedefault) {
		printf("using old default partitioning\n");
		sdmakedisklabel(unit, lp);
		return(0);
	}
#endif
E 21
	printf("defining `c' partition as entire disk\n");
	pi[2].p_size = sc->sc_blks;
I 24
	/* XXX reset other info since readdisklabel screws with it */
	lp->d_npartitions = 3;
	pi[0].p_size = 0;
E 24
D 21
#endif
E 21
	return(0);
}

int
E 17
D 5
sdopen(dev, flags)
E 5
I 5
sdopen(dev, flags, mode, p)
E 5
	dev_t dev;
D 5
	int flags;
E 5
I 5
	int flags, mode;
	struct proc *p;
E 5
{
	register int unit = sdunit(dev);
	register struct sd_softc *sc = &sd_softc[unit];
I 17
D 27
	int mask, error;
E 27
I 27
	int error, mask;
E 27
E 17

D 27
	if (unit >= NSD)
E 27
I 27
	if (unit >= NSD || (sc->sc_flags & SDF_ALIVE) == 0)
E 27
		return(ENXIO);
D 5
	if ((sc->sc_flags & SDF_ALIVE) == 0 && suser(u.u_cred, &u.u_acflag))
E 5
I 5
D 23
	if ((sc->sc_flags & SDF_ALIVE) == 0 && suser(p->p_ucred, &p->p_acflag))
E 23
I 23
D 27
	/*
	 * If a drive's position was fully qualified (i.e. not wildcarded in
	 * any way, we allow root to open the device even though it wasn't
	 * found at autoconfig time.  This allows initial formatting of disks.
	 * However, if any part of the specification was wildcarded, we won't
	 * be able to locate the drive so there is nothing we can do.
	 */
	if ((sc->sc_flags & SDF_ALIVE) == 0 &&
	    (suser(p->p_ucred, &p->p_acflag) ||
	     sc->sc_hd->hp_ctlr < 0 || sc->sc_hd->hp_slave < 0))
E 23
E 5
		return(ENXIO);
I 17
	if (sc->sc_flags & SDF_ERROR)
		return(EIO);
E 27
E 17

I 17
	/*
	 * Wait for any pending opens/closes to complete
	 */
	while (sc->sc_flags & (SDF_OPENING|SDF_CLOSING))
		sleep((caddr_t)sc, PRIBIO);
I 27

E 27
	/*
	 * On first open, get label and partition info.
	 * We may block reading the label, so be careful
	 * to stop any other opens.
	 */
	if (sc->sc_info.si_open == 0) {
		sc->sc_flags |= SDF_OPENING;
		error = sdgetinfo(dev);
		sc->sc_flags &= ~SDF_OPENING;
		wakeup((caddr_t)sc);
		if (error)
			return(error);
	}
E 17
	if (sc->sc_hd->hp_dk >= 0)
		dk_wpms[sc->sc_hd->hp_dk] = sc->sc_wpms;
I 17

	mask = 1 << sdpart(dev);
	if (mode == S_IFCHR)
		sc->sc_info.si_copen |= mask;
	else
		sc->sc_info.si_bopen |= mask;
	sc->sc_info.si_open |= mask;
E 17
	return(0);
}

I 13
int
sdclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	int unit = sdunit(dev);
	register struct sd_softc *sc = &sd_softc[unit];
D 17
	int s;
E 17
I 17
	register struct sdinfo *si = &sc->sc_info;
	int mask, s;
E 17

I 17
	mask = 1 << sdpart(dev);
	if (mode == S_IFCHR)
		si->si_copen &= ~mask;
	else
		si->si_bopen &= ~mask;
	si->si_open = si->si_bopen | si->si_copen;
E 17
	/*
D 17
	 * XXX we should really do this for all drives.
E 17
I 17
	 * On last close, we wait for all activity to cease since
	 * the label/parition info will become invalid.  Since we
	 * might sleep, we must block any opens while we are here.
	 * Note we don't have to about other closes since we know
	 * we are the last one.
E 17
	 */
D 17
	if (sc->sc_flags & SDF_RMEDIA) {
E 17
I 17
	if (si->si_open == 0) {
		sc->sc_flags |= SDF_CLOSING;
E 17
		s = splbio();
		while (sdtab[unit].b_active) {
			sc->sc_flags |= SDF_WANTED;
			sleep((caddr_t)&sdtab[unit], PRIBIO);
		}
		splx(s);
I 17
		sc->sc_flags &= ~(SDF_CLOSING|SDF_WLABEL|SDF_ERROR);
		wakeup((caddr_t)sc);
E 17
	}
D 22
	sc->sc_format_pid = 0;
E 22
I 22
	sc->sc_format_pid = -1;
E 22
I 17
	return(0);
E 17
}

E 13
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
	register struct buf *cbp = (struct buf *)malloc(sizeof(struct buf),
							M_DEVBUF, M_WAITOK);
	caddr_t cbuf = (caddr_t)malloc(bsize, M_DEVBUF, M_WAITOK);
	register int bn, resid;
	register caddr_t addr;

	bzero((caddr_t)cbp, sizeof(*cbp));
D 5
	cbp->b_proc = u.u_procp;
E 5
I 5
	cbp->b_proc = curproc;		/* XXX */
E 5
	cbp->b_dev = bp->b_dev;
	bn = bp->b_blkno;
	resid = bp->b_bcount;
	addr = bp->b_un.b_addr;
#ifdef DEBUG
	if (sddebug & SDB_PARTIAL)
		printf("sdlblkstrat: bp %x flags %x bn %x resid %x addr %x\n",
		       bp, bp->b_flags, bn, resid, addr);
#endif

	while (resid > 0) {
		register int boff = dbtob(bn) & (bsize - 1);
		register int count;

		if (boff || resid < bsize) {
			sdstats[sdunit(bp->b_dev)].sdpartials++;
D 14
			count = MIN(resid, bsize - boff);
E 14
I 14
			count = min(resid, bsize - boff);
E 14
			cbp->b_flags = B_BUSY | B_PHYS | B_READ;
			cbp->b_blkno = bn - btodb(boff);
			cbp->b_un.b_addr = cbuf;
			cbp->b_bcount = bsize;
#ifdef DEBUG
			if (sddebug & SDB_PARTIAL)
				printf(" readahead: bn %x cnt %x off %x addr %x\n",
				       cbp->b_blkno, count, boff, addr);
#endif
			sdstrategy(cbp);
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
			if (sddebug & SDB_PARTIAL)
				printf(" writeback: bn %x cnt %x off %x addr %x\n",
				       cbp->b_blkno, count, boff, addr);
#endif
		} else {
			count = resid & ~(bsize - 1);
			cbp->b_blkno = bn;
			cbp->b_un.b_addr = addr;
			cbp->b_bcount = count;
#ifdef DEBUG
			if (sddebug & SDB_PARTIAL)
				printf(" fulltrans: bn %x cnt %x addr %x\n",
				       cbp->b_blkno, count, addr);
#endif
		}
		cbp->b_flags = B_BUSY | B_PHYS | (bp->b_flags & B_READ);
		sdstrategy(cbp);
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
		if (sddebug & SDB_PARTIAL)
			printf(" done: bn %x resid %x addr %x\n",
			       bn, resid, addr);
#endif
	}
	free(cbuf, M_DEVBUF);
	free(cbp, M_DEVBUF);
}

void
sdstrategy(bp)
	register struct buf *bp;
{
D 3
	register int part = sdpart(bp->b_dev);
E 3
D 17
	register int unit = sdunit(bp->b_dev);
E 17
I 17
	int unit = sdunit(bp->b_dev);
E 17
D 3
	register int bn, sz;
E 3
	register struct sd_softc *sc = &sd_softc[unit];
I 3
D 17
	register struct size *pinfo = &sc->sc_info.part[sdpart(bp->b_dev)];
E 17
E 3
	register struct buf *dp = &sdtab[unit];
I 17
	register struct partition *pinfo;
E 17
D 3
	register int s;
E 3
I 3
	register daddr_t bn;
	register int sz, s;
E 3

I 17
D 21
	if (sc->sc_flags & SDF_ERROR) {
		bp->b_error = EIO;
		goto bad;
	}
E 21
E 17
D 22
	if (sc->sc_format_pid) {
E 22
I 22
	if (sc->sc_format_pid >= 0) {
E 22
D 5
		if (sc->sc_format_pid != u.u_procp->p_pid) {
E 5
I 5
		if (sc->sc_format_pid != curproc->p_pid) {	/* XXX */
E 5
			bp->b_error = EPERM;
D 3
			goto bad;
E 3
I 3
D 17
			bp->b_flags |= B_ERROR;
			goto done;
E 17
I 17
			goto bad;
E 17
E 3
		}
		bp->b_cylin = 0;
	} else {
I 21
		if (sc->sc_flags & SDF_ERROR) {
			bp->b_error = EIO;
			goto bad;
		}
E 21
		bn = bp->b_blkno;
D 3
		sz = (bp->b_bcount + (DEV_BSIZE - 1)) >> DEV_BSHIFT;
		if (bn < 0 || bn + sz > sc->sc_info.part[part].nblocks) {
			if (bn == sc->sc_info.part[part].nblocks) {
E 3
I 3
		sz = howmany(bp->b_bcount, DEV_BSIZE);
D 17
		if (bn < 0 || bn + sz > pinfo->nblocks) {
			sz = pinfo->nblocks - bn;
E 17
I 17
		pinfo = &sc->sc_info.si_label.d_partitions[sdpart(bp->b_dev)];
		if (bn < 0 || bn + sz > pinfo->p_size) {
			sz = pinfo->p_size - bn;
E 17
			if (sz == 0) {
E 3
				bp->b_resid = bp->b_bcount;
				goto done;
			}
D 3
			bp->b_error = EINVAL;
			goto bad;
E 3
I 3
			if (sz < 0) {
				bp->b_error = EINVAL;
D 17
				bp->b_flags |= B_ERROR;
				goto done;
E 17
I 17
				goto bad;
E 17
			}
			bp->b_bcount = dbtob(sz);
E 3
		}
		/*
I 17
		 * Check for write to write protected label
		 */
		if (bn + pinfo->p_offset <= LABELSECTOR &&
#if LABELSECTOR != 0
		    bn + pinfo->p_offset + sz > LABELSECTOR &&
#endif
		    !(bp->b_flags & B_READ) && !(sc->sc_flags & SDF_WLABEL)) {
			bp->b_error = EROFS;
			goto bad;
		}
		/*
E 17
		 * Non-aligned or partial-block transfers handled specially.
		 */
		s = sc->sc_blksize - 1;
		if ((dbtob(bn) & s) || (bp->b_bcount & s)) {
			sdlblkstrat(bp, sc->sc_blksize);
			goto done;
		}
D 3
		bp->b_cylin = (bn + sc->sc_info.part[part].strtblk) >>
				sc->sc_bshift;
E 3
I 3
D 17
		bp->b_cylin = (bn + pinfo->strtblk) >> sc->sc_bshift;
E 17
I 17
		bp->b_cylin = (bn + pinfo->p_offset) >> sc->sc_bshift;
E 17
E 3
	}
	s = splbio();
	disksort(dp, bp);
	if (dp->b_active == 0) {
		dp->b_active = 1;
		sdustart(unit);
	}
	splx(s);
	return;
I 17
bad:
	bp->b_flags |= B_ERROR;
E 17
D 3
bad:
	bp->b_flags |= B_ERROR;
E 3
done:
D 3
	iodone(bp);
E 3
I 3
	biodone(bp);
E 3
}

void
sdustart(unit)
	register int unit;
{
	if (scsireq(&sd_softc[unit].sc_dq))
		sdstart(unit);
}

I 8
/*
 * Return:
 *	0	if not really an error
 *	<0	if we should do a retry
 *	>0	if a fatal error
 */
E 8
D 3
static void
E 3
I 3
static int
E 3
sderror(unit, sc, hp, stat)
	int unit, stat;
	register struct sd_softc *sc;
	register struct hp_device *hp;
{
I 3
D 8
	int retry = 0;
E 8
I 8
	int cond = 1;
E 8

E 3
	sdsense[unit].status = stat;
	if (stat & STS_CHECKCOND) {
		struct scsi_xsense *sp;

		scsi_request_sense(hp->hp_ctlr, hp->hp_slave,
				   sc->sc_punit, sdsense[unit].sense,
				   sizeof(sdsense[unit].sense));
		sp = (struct scsi_xsense *)sdsense[unit].sense;
		printf("sd%d: scsi sense class %d, code %d", unit,
			sp->class, sp->code);
		if (sp->class == 7) {
			printf(", key %d", sp->key);
			if (sp->valid)
				printf(", blk %d", *(int *)&sp->info1);
I 3
D 8
			/* no sense or recovered error, try again */
			if (sp->key == 0 || sp->key == 1)
				retry = 1;
E 8
I 8
			switch (sp->key) {
			/* no sense, try again */
			case 0:
				cond = -1;
				break;
			/* recovered error, not a problem */
			case 1:
				cond = 0;
				break;
I 17
			/* possible media change */
			case 6:
				/*
				 * For removable media, if we are doing the
				 * first open (i.e. reading the label) go
				 * ahead and retry, otherwise someone has
				 * changed the media out from under us and
				 * we should abort any further operations
				 * until a close is done.
				 */
				if (sc->sc_flags & SDF_RMEDIA) {
					if (sc->sc_flags & SDF_OPENING)
						cond = -1;
					else
						sc->sc_flags |= SDF_ERROR;
				}
				break;
E 17
			}
E 8
E 3
		}
		printf("\n");
	}
I 3
D 8
	return(retry);
E 8
I 8
	return(cond);
E 8
E 3
}

static void
sdfinish(unit, sc, bp)
	int unit;
	register struct sd_softc *sc;
	register struct buf *bp;
{
D 13
	sdtab[unit].b_errcnt = 0;
	sdtab[unit].b_actf = bp->b_actf;
E 13
I 13
	register struct buf *dp = &sdtab[unit];

	dp->b_errcnt = 0;
	dp->b_actf = bp->b_actf;
E 13
	bp->b_resid = 0;
D 3
	iodone(bp);
E 3
I 3
	biodone(bp);
E 3
	scsifree(&sc->sc_dq);
D 13
	if (sdtab[unit].b_actf)
E 13
I 13
	if (dp->b_actf)
E 13
		sdustart(unit);
D 13
	else
		sdtab[unit].b_active = 0;
E 13
I 13
	else {
		dp->b_active = 0;
		if (sc->sc_flags & SDF_WANTED) {
			sc->sc_flags &= ~SDF_WANTED;
			wakeup((caddr_t)dp);
		}
	}
E 13
}

void
sdstart(unit)
	register int unit;
{
	register struct sd_softc *sc = &sd_softc[unit];
	register struct hp_device *hp = sc->sc_hd;

	/*
	 * we have the SCSI bus -- in format mode, we may or may not need dma
	 * so check now.
	 */
D 22
	if (sc->sc_format_pid && legal_cmds[sdcmd[unit].cdb[0]] > 0) {
E 22
I 22
	if (sc->sc_format_pid >= 0 && legal_cmds[sdcmd[unit].cdb[0]] > 0) {
E 22
		register struct buf *bp = sdtab[unit].b_actf;
		register int sts;

D 21
		sts = scsi_immed_command(hp->hp_ctlr, hp->hp_slave,
					 sc->sc_punit, &sdcmd[unit],
					 bp->b_un.b_addr, bp->b_bcount,
					 bp->b_flags & B_READ);
		sdsense[unit].status = sts;
		if (sts & 0xfe) {
D 3
			sderror(unit, sc, hp, sts);
E 3
I 3
			(void) sderror(unit, sc, hp, sts);
E 3
			bp->b_flags |= B_ERROR;
			bp->b_error = EIO;
E 21
I 21
		sdtab[unit].b_errcnt = 0;
		while (1) {
			sts = scsi_immed_command(hp->hp_ctlr, hp->hp_slave,
						 sc->sc_punit, &sdcmd[unit],
						 bp->b_un.b_addr, bp->b_bcount,
						 bp->b_flags & B_READ);
			sdsense[unit].status = sts;
			if ((sts & 0xfe) == 0 ||
			    (sts = sderror(unit, sc, hp, sts)) == 0)
				break;
			if (sts > 0 || sdtab[unit].b_errcnt++ >= SDRETRY) {
				bp->b_flags |= B_ERROR;
				bp->b_error = EIO;
				break;
			}
E 21
		}
		sdfinish(unit, sc, bp);

	} else if (scsiustart(hp->hp_ctlr))
		sdgo(unit);
}

void
sdgo(unit)
	register int unit;
{
	register struct sd_softc *sc = &sd_softc[unit];
	register struct hp_device *hp = sc->sc_hd;
	register struct buf *bp = sdtab[unit].b_actf;
	register int pad;
	register struct scsi_fmt_cdb *cmd;

I 17
D 21
	/*
	 * Drive is in an error state, abort all operations
	 */
	if (sc->sc_flags & SDF_ERROR) {
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
		sdfinish(unit, sc, bp);
		return;
	}
E 21
E 17
D 22
	if (sc->sc_format_pid) {
E 22
I 22
	if (sc->sc_format_pid >= 0) {
E 22
		cmd = &sdcmd[unit];
		pad = 0;
	} else {
I 21
		/*
		 * Drive is in an error state, abort all operations
		 */
		if (sc->sc_flags & SDF_ERROR) {
			bp->b_flags |= B_ERROR;
			bp->b_error = EIO;
			sdfinish(unit, sc, bp);
			return;
		}
E 21
		cmd = bp->b_flags & B_READ? &sd_read_cmd : &sd_write_cmd;
		*(int *)(&cmd->cdb[2]) = bp->b_cylin;
		pad = howmany(bp->b_bcount, sc->sc_blksize);
		*(u_short *)(&cmd->cdb[7]) = pad;
		pad = (bp->b_bcount & (sc->sc_blksize - 1)) != 0;
#ifdef DEBUG
		if (pad)
			printf("sd%d: partial block xfer -- %x bytes\n",
			       unit, bp->b_bcount);
#endif
		sdstats[unit].sdtransfers++;
	}
I 17
#ifdef USELEDS
	if (inledcontrol == 0)
		ledcontrol(0, 0, LED_DISK);
#endif
E 17
	if (scsigo(hp->hp_ctlr, hp->hp_slave, sc->sc_punit, bp, cmd, pad) == 0) {
		if (hp->hp_dk >= 0) {
			dk_busy |= 1 << hp->hp_dk;
			++dk_seek[hp->hp_dk];
			++dk_xfer[hp->hp_dk];
			dk_wds[hp->hp_dk] += bp->b_bcount >> 6;
		}
		return;
	}
#ifdef DEBUG
	if (sddebug & SDB_ERROR)
		printf("sd%d: sdstart: %s adr %d blk %d len %d ecnt %d\n",
		       unit, bp->b_flags & B_READ? "read" : "write",
		       bp->b_un.b_addr, bp->b_cylin, bp->b_bcount,
		       sdtab[unit].b_errcnt);
#endif
	bp->b_flags |= B_ERROR;
	bp->b_error = EIO;
	sdfinish(unit, sc, bp);
}

void
sdintr(unit, stat)
	register int unit;
	int stat;
{
	register struct sd_softc *sc = &sd_softc[unit];
	register struct buf *bp = sdtab[unit].b_actf;
	register struct hp_device *hp = sc->sc_hd;
I 3
D 8
	int retry;
E 8
I 8
	int cond;
E 8
E 3
	
	if (bp == NULL) {
		printf("sd%d: bp == NULL\n", unit);
		return;
	}
	if (hp->hp_dk >= 0)
		dk_busy &=~ (1 << hp->hp_dk);
	if (stat) {
#ifdef DEBUG
		if (sddebug & SDB_ERROR)
			printf("sd%d: sdintr: bad scsi status 0x%x\n",
				unit, stat);
#endif
D 3
		sderror(unit, sc, hp, stat);
E 3
I 3
D 8
		retry = sderror(unit, sc, hp, stat);
		if (retry && sdtab[unit].b_errcnt++ < SDRETRY) {
E 8
I 8
		cond = sderror(unit, sc, hp, stat);
		if (cond) {
			if (cond < 0 && sdtab[unit].b_errcnt++ < SDRETRY) {
E 8
D 7
			printf("sd%d: retry #%d\n",
			       unit, sdtab[unit].b_errcnt);
E 7
I 7
#ifdef DEBUG
D 8
			if (sddebug & SDB_ERROR)
				printf("sd%d: retry #%d\n",
				       unit, sdtab[unit].b_errcnt);
E 8
I 8
				if (sddebug & SDB_ERROR)
					printf("sd%d: retry #%d\n",
					       unit, sdtab[unit].b_errcnt);
E 8
#endif
E 7
D 8
			sdstart(unit);
			return;
E 8
I 8
				sdstart(unit);
				return;
			}
			bp->b_flags |= B_ERROR;
			bp->b_error = EIO;
E 8
		}
E 3
D 8
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
E 8
	}
	sdfinish(unit, sc, bp);
}

int
D 5
sdread(dev, uio)
E 5
I 5
sdread(dev, uio, flags)
E 5
	dev_t dev;
	struct uio *uio;
I 5
	int flags;
E 5
{
	register int unit = sdunit(dev);
	register int pid;

D 5
	if ((pid = sd_softc[unit].sc_format_pid) && pid != u.u_procp->p_pid)
E 5
I 5
D 22
	if ((pid = sd_softc[unit].sc_format_pid) &&
E 22
I 22
	if ((pid = sd_softc[unit].sc_format_pid) >= 0 &&
E 22
	    pid != uio->uio_procp->p_pid)
E 5
		return (EPERM);
		
D 5
	return(physio(sdstrategy, &sdbuf[unit], dev, B_READ, minphys, uio));
E 5
I 5
	return (physio(sdstrategy, NULL, dev, B_READ, minphys, uio));
E 5
}

int
D 5
sdwrite(dev, uio)
E 5
I 5
sdwrite(dev, uio, flags)
E 5
	dev_t dev;
	struct uio *uio;
I 5
	int flags;
E 5
{
	register int unit = sdunit(dev);
	register int pid;

D 5
	if ((pid = sd_softc[unit].sc_format_pid) && pid != u.u_procp->p_pid)
E 5
I 5
D 22
	if ((pid = sd_softc[unit].sc_format_pid) &&
E 22
I 22
	if ((pid = sd_softc[unit].sc_format_pid) >= 0 &&
E 22
	    pid != uio->uio_procp->p_pid)
E 5
		return (EPERM);
		
D 5
	return(physio(sdstrategy, &sdbuf[unit], dev, B_WRITE, minphys, uio));
E 5
I 5
	return (physio(sdstrategy, NULL, dev, B_WRITE, minphys, uio));
E 5
}

int
D 5
sdioctl(dev, cmd, data, flag)
E 5
I 5
sdioctl(dev, cmd, data, flag, p)
E 5
	dev_t dev;
D 25
	int cmd;
E 25
I 25
	u_long cmd;
E 25
	caddr_t data;
	int flag;
I 5
	struct proc *p;
E 5
{
D 17
	register int unit = sdunit(dev);
E 17
I 17
	int unit = sdunit(dev);
E 17
	register struct sd_softc *sc = &sd_softc[unit];
I 17
	register struct disklabel *lp = &sc->sc_info.si_label;
	int error, flags;
E 17

	switch (cmd) {
	default:
		return (EINVAL);

I 17
	case DIOCGDINFO:
		*(struct disklabel *)data = *lp;
		return (0);

	case DIOCGPART:
		((struct partinfo *)data)->disklab = lp;
		((struct partinfo *)data)->part =
			&lp->d_partitions[sdpart(dev)];
		return (0);

        case DIOCWLABEL:
                if ((flag & FWRITE) == 0)
                        return (EBADF);
		if (*(int *)data)
			sc->sc_flags |= SDF_WLABEL;
		else
			sc->sc_flags &= ~SDF_WLABEL;
		return (0);

        case DIOCSDINFO:
                if ((flag & FWRITE) == 0)
                        return (EBADF);
		error = setdisklabel(lp, (struct disklabel *)data,
				     (sc->sc_flags & SDF_WLABEL) ? 0
				     : sc->sc_info.si_open);
		return (error);

        case DIOCWDINFO:
		if ((flag & FWRITE) == 0)
			return (EBADF);
		error = setdisklabel(lp, (struct disklabel *)data,
				     (sc->sc_flags & SDF_WLABEL) ? 0
				     : sc->sc_info.si_open);
		if (error)
			return (error);
		flags = sc->sc_flags;
		sc->sc_flags = SDF_ALIVE | SDF_WLABEL;
		error = writedisklabel(sdlabdev(dev), sdstrategy, lp);
		sc->sc_flags = flags;
		return (error);

E 17
	case SDIOCSFORMAT:
		/* take this device into or out of "format" mode */
D 5
		if (suser(u.u_cred, &u.u_acflag))
E 5
I 5
		if (suser(p->p_ucred, &p->p_acflag))
E 5
			return(EPERM);

		if (*(int *)data) {
D 22
			if (sc->sc_format_pid)
E 22
I 22
			if (sc->sc_format_pid >= 0)
E 22
				return (EPERM);
D 5
			sc->sc_format_pid = u.u_procp->p_pid;
E 5
I 5
			sc->sc_format_pid = p->p_pid;
E 5
		} else
D 22
			sc->sc_format_pid = 0;
E 22
I 22
			sc->sc_format_pid = -1;
E 22
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
D 5
		if (sc->sc_format_pid != u.u_procp->p_pid)
E 5
I 5
		if (sc->sc_format_pid != p->p_pid)
E 5
			return (EPERM);
		if (legal_cmds[((struct scsi_fmt_cdb *)data)->cdb[0]] == 0)
			return (EINVAL);
		bcopy(data, (caddr_t)&sdcmd[unit], sizeof(sdcmd[0]));
		return (0);

	case SDIOCSENSE:
		/*
		 * return the SCSI sense data saved after the last
		 * operation that completed with "check condition" status.
		 */
		bcopy((caddr_t)&sdsense[unit], data, sizeof(sdsense[0]));
		return (0);
		
	}
	/*NOTREACHED*/
}

int
sdsize(dev)
	dev_t dev;
{
	register int unit = sdunit(dev);
	register struct sd_softc *sc = &sd_softc[unit];
I 17
	int psize, didopen = 0;
E 17

	if (unit >= NSD || (sc->sc_flags & SDF_ALIVE) == 0)
		return(-1);

D 17
	return(sc->sc_info.part[sdpart(dev)].nblocks);
E 17
I 17
	/*
	 * We get called very early on (via swapconf)
	 * without the device being open so we may need
	 * to handle it here.
	 */
	if (sc->sc_info.si_open == 0) {
		if (sdopen(dev, FREAD|FWRITE, S_IFBLK, NULL))
			return(-1);
		didopen = 1;
	}
	psize = sc->sc_info.si_label.d_partitions[sdpart(dev)].p_size;
	if (didopen)
		(void) sdclose(dev, FREAD|FWRITE, S_IFBLK, NULL);
	return (psize);
E 17
}

D 3
#include "machine/pte.h"
#include "machine/vmparam.h"
D 2
#include "../h/vmmac.h"
E 2
I 2
#include "../sys/vmmac.h"
E 2

E 3
/*
 * Non-interrupt driven, non-dma dump routine.
 */
int
sddump(dev)
	dev_t dev;
{
	int part = sdpart(dev);
	int unit = sdunit(dev);
	register struct sd_softc *sc = &sd_softc[unit];
	register struct hp_device *hp = sc->sc_hd;
I 17
	register struct partition *pinfo;
E 17
	register daddr_t baddr;
	register int maddr;
	register int pages, i;
	int stat;
D 22
	extern int lowram;
E 22
I 22
	extern int lowram, dumpsize;
E 22

D 17
	/*
	 * Hmm... all vax drivers dump maxfree pages which is physmem minus
	 * the message buffer.  Is there a reason for not dumping the
	 * message buffer?  Savecore expects to read 'dumpsize' pages of
	 * dump, where dumpsys() sets dumpsize to physmem!
	 */
	pages = physmem;

E 17
	/* is drive ok? */
	if (unit >= NSD || (sc->sc_flags & SDF_ALIVE) == 0)
		return (ENXIO);
I 17
	pinfo = &sc->sc_info.si_label.d_partitions[part];
E 17
	/* dump parameters in range? */
D 17
	if (dumplo < 0 || dumplo >= sc->sc_info.part[part].nblocks)
E 17
I 17
	if (dumplo < 0 || dumplo >= pinfo->p_size ||
	    pinfo->p_fstype != FS_SWAP)
E 17
		return (EINVAL);
D 17
	if (dumplo + ctod(pages) > sc->sc_info.part[part].nblocks)
		pages = dtoc(sc->sc_info.part[part].nblocks - dumplo);
E 17
I 17
D 22
	pages = physmem;
E 22
I 22
	pages = dumpsize;
E 22
	if (dumplo + ctod(pages) > pinfo->p_size)
		pages = dtoc(pinfo->p_size - dumplo);
E 17
	maddr = lowram;
D 17
	baddr = dumplo + sc->sc_info.part[part].strtblk;
E 17
I 17
	baddr = dumplo + pinfo->p_offset;
E 17
	/* scsi bus idle? */
	if (!scsireq(&sc->sc_dq)) {
		scsireset(hp->hp_ctlr);
		sdreset(sc, sc->sc_hd);
		printf("[ drive %d reset ] ", unit);
	}
	for (i = 0; i < pages; i++) {
#define NPGMB	(1024*1024/NBPG)
		/* print out how many Mbs we have dumped */
		if (i && (i % NPGMB) == 0)
			printf("%d ", i / NPGMB);
#undef NPBMG
D 3
		mapin(mmap, (u_int)vmmap, btop(maddr), PG_URKR|PG_CI|PG_V);
E 3
I 3
D 11
		pmap_enter(pmap_kernel(), vmmap, maddr, VM_PROT_READ, TRUE);
E 11
I 11
D 12
		pmap_enter(pmap_kernel(), (vm_offset_t)vmmap, maddr,
E 12
I 12
		pmap_enter(kernel_pmap, (vm_offset_t)vmmap, maddr,
E 12
		    VM_PROT_READ, TRUE);
E 11
E 3
		stat = scsi_tt_write(hp->hp_ctlr, hp->hp_slave, sc->sc_punit,
				     vmmap, NBPG, baddr, sc->sc_bshift);
		if (stat) {
			printf("sddump: scsi write error 0x%x\n", stat);
			return (EIO);
		}
		maddr += NBPG;
		baddr += ctod(1);
	}
	return (0);
}
#endif
E 1
