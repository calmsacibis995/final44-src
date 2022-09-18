h28351
s 00002/00002/00179
d D 8.1 93/06/10 21:47:52 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00180
d D 7.9 93/05/24 22:50:11 mckusick 9 8
c fix include directives
e
s 00056/00009/00125
d D 7.8 92/12/26 16:49:51 hibler 8 7
c Utah update (mostly disklabels)
e
s 00004/00004/00130
d D 7.7 92/10/11 10:01:50 bostic 7 6
c make kernel includes standard
e
s 00005/00006/00129
d D 7.6 92/08/14 09:28:21 hibler 6 5
c check for 0-length IO requests, VJ's prints no longer needed
e
s 00049/00037/00086
d D 7.5 92/06/18 21:33:32 hibler 5 4
c merge with latest Utah version
e
s 00002/00001/00121
d D 7.4 91/05/05 13:32:31 bostic 4 3
c includes for standard stand source, READ, WRITE -> F_READ, FWRITE
e
s 00001/00001/00121
d D 7.3 90/12/16 16:39:49 bostic 3 2
c kernel reorg
e
s 00001/00001/00121
d D 7.2 90/05/25 16:17:46 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00122/00000/00000
d D 7.1 90/05/08 22:46:12 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson of Lawrence Berkeley Laboratory and the Systems
 * Programming Group of the University of Utah Computer Science Department.
 *
 * %sccs.include.redist.c%
 *
D 8
 * from: Utah $Hdr: sd.c 1.2 90/01/23$
E 8
I 8
 * from: Utah $Hdr: sd.c 1.9 92/12/21$
E 8
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SCSI CCS disk driver
 */

I 4
D 5
#include <sys/param.h>
E 5
I 5
D 7
#include "sys/param.h"
E 5
E 4
#include "saio.h"
#include "samachdep.h"
E 7
I 7
#include <sys/param.h>
I 8
#include <sys/disklabel.h>
E 8
D 9
#include <stand/saio.h>
E 9
I 9
#include <stand.att/saio.h>
E 9
#include <hp300/stand/samachdep.h>
E 7

D 3
#include "../hpdev/scsireg.h"
E 3
I 3
D 7
#include "../dev/scsireg.h"
E 7
I 7
#include <hp300/dev/scsireg.h>
E 7
E 3

I 8
struct	disklabel sdlabel;

struct	sdminilabel {
	u_short	npart;
	u_long	offset[MAXPARTITIONS];
};

E 8
struct	sd_softc {
	char	sc_retry;
	char	sc_alive;
	short	sc_blkshift;
I 8
	struct	sdminilabel sc_pinfo;
E 8
D 5
} sd_softc[NSD];
E 5
I 5
} sd_softc[NSCSI][NSD];
E 5

D 8
int sdpartoff[] = {
	1024,	17408,	0,	17408,
D 5
	115712,	218112,	82944,	0
E 5
I 5
	115712,	218112,	82944,	115712
E 5
};

E 8
#define	SDRETRY		2

D 5
sdinit(unit)
	register int unit;
E 5
I 5
sdinit(ctlr, unit)
	int ctlr, unit;
E 5
{
D 5
	register struct sd_softc *ss;
E 5
I 5
	register struct sd_softc *ss = &sd_softc[ctlr][unit];
E 5
	u_char stat;
	int capbuf[2];

D 5
	if (unit > NSD)
		return (0);
	ss = &sd_softc[unit];
E 5
D 6
	/* NB: HP6300 won't boot if next printf is removed (???) - vj */
D 5
	printf("sd%d: ", unit);
	if ((stat = scsi_test_unit_rdy(unit)) == 0) {
E 5
I 5
	printf("sd(%d,%d,0,0): ", ctlr, unit);
E 6
	stat = scsi_test_unit_rdy(ctlr, unit);
	if (stat) {
E 5
		/* drive may be doing RTZ - wait a bit */
D 5
		printf("not ready - retrying ... ");
E 5
I 5
D 6
		printf("not ready - ");
E 6
E 5
		if (stat == STS_CHECKCOND) {
I 5
D 6
			printf("retrying ... ");
E 6
E 5
			DELAY(1000000);
D 5
			if (scsi_test_unit_rdy(unit) == 0) {
				printf("giving up.\n");
				return (0);
			}
E 5
I 5
			stat = scsi_test_unit_rdy(ctlr, unit);
E 5
		}
I 5
		if (stat) {
D 6
			printf("giving up (stat=%x).\n", stat);
E 6
I 6
			printf("sd(%d,%d,0,0): init failed (stat=%x)\n",
			       ctlr, unit, stat);
E 6
			return (0);
		}
E 5
	}
D 6
	printf("unit ready.\n");
E 6
	/*
	 * try to get the drive block size.
	 */
	capbuf[0] = 0;
	capbuf[1] = 0;
D 5
	if (scsi_read_capacity(unit, (u_char *)capbuf, sizeof(capbuf)) != 0) {
E 5
I 5
	stat = scsi_read_capacity(ctlr, unit,
				  (u_char *)capbuf, sizeof(capbuf));
	if (stat == 0) {
E 5
		if (capbuf[1] > DEV_BSIZE)
			for (; capbuf[1] > DEV_BSIZE; capbuf[1] >>= 1)
				++ss->sc_blkshift;
	}
	ss->sc_alive = 1;
	return (1);
}

D 5
sdreset(unit)
E 5
I 5
sdreset(ctlr, unit)
	int ctlr, unit;
E 5
{
}

I 8
#ifdef COMPAT_NOLABEL
struct	sdminilabel defaultpinfo = {
	8,
	{ 1024, 17408, 0, 17408, 115712, 218112, 82944, 115712 }
};
#endif

sdgetinfo(io)
	register struct iob *io;
{
	struct sd_softc *ss = &sd_softc[io->i_adapt][io->i_ctlr];
	register struct sdminilabel *pi = &ss->sc_pinfo;
	register struct disklabel *lp = &sdlabel;
	char *msg, *readdisklabel();
	int sdstrategy(), i;

	bzero((caddr_t)lp, sizeof *lp);
	lp->d_secsize = (DEV_BSIZE << ss->sc_blkshift);
	msg = readdisklabel(io, sdstrategy, lp);
	if (msg) {
		printf("sd(%d,%d,%d,%d): WARNING: %s, ",
		       io->i_adapt, io->i_ctlr, io->i_unit, io->i_part, msg);
#ifdef COMPAT_NOLABEL
		printf("using old default partitioning\n");
		*pi = defaultpinfo;
#else
		printf("defining `c' partition as entire disk\n");
		pi->npart = 3;
		pi->offset[0] = pi->offset[1] = -1;
		pi->offset[2] = 0;
#endif
	} else {
		pi->npart = lp->d_npartitions;
		for (i = 0; i < pi->npart; i++)
			pi->offset[i] = lp->d_partitions[i].p_size == 0 ?
				-1 : lp->d_partitions[i].p_offset;
	}
	return(1);
}

E 8
sdopen(io)
	struct iob *io;
{
D 5
	register int unit = io->i_unit;
	register struct sd_softc *ss = &sd_softc[unit];
	struct sdinfo *ri;
E 5
I 5
	register struct sd_softc *ss;
	int ctlr, unit, part;
E 5

D 5
	if (scsialive(unit) == 0)
		_stop("scsi controller not configured");
E 5
I 5
	devconvert(io);

	ctlr = io->i_adapt;
	if (ctlr >= NSCSI || scsialive(ctlr) == 0)
		return (EADAPT);
	unit = io->i_ctlr;
	if (unit >= NSD)
		return (ECTLR);
	ss = &sd_softc[ctlr][unit];
E 5
D 8
	if (ss->sc_alive == 0)
E 8
I 8
	if (ss->sc_alive == 0) {
E 8
D 5
		if (sdinit(unit) == 0)
			_stop("sd init failed");
	if (io->i_boff < 0 || io->i_boff > 7)
		_stop("sd bad minor");
	io->i_boff = sdpartoff[io->i_boff];
E 5
I 5
		if (sdinit(ctlr, unit) == 0)
			return (ENXIO);
I 8
		if (sdgetinfo(io) == 0)
			return (ERDLAB);
	}
E 8
	part = io->i_part;
D 8
	if (part >= 8)
E 8
I 8
	if (part >= ss->sc_pinfo.npart || ss->sc_pinfo.offset[part] == -1)
E 8
		return (EPART);
D 8
	io->i_boff = sdpartoff[part];
E 8
I 8
	io->i_boff = ss->sc_pinfo.offset[part];
E 8
	return (0);
E 5
}

sdstrategy(io, func)
	register struct iob *io;
D 5
	register int func;
E 5
I 5
	int func;
E 5
{
D 5
	register int unit = io->i_unit;
	register struct sd_softc *ss = &sd_softc[unit];
	char stat;
E 5
I 5
	register int ctlr = io->i_adapt;
	register int unit = io->i_ctlr;
	register struct sd_softc *ss = &sd_softc[ctlr][unit];
E 5
	daddr_t blk = io->i_bn >> ss->sc_blkshift;
	u_int nblk = io->i_cc >> ss->sc_blkshift;
I 5
	char stat;
I 6

	if (io->i_cc == 0)
		return(0);
E 6
E 5

	ss->sc_retry = 0;
retry:
D 4
	if (func == READ)
E 4
I 4
	if (func == F_READ)
E 4
D 5
		stat = scsi_tt_read(unit, io->i_ma, io->i_cc, blk, nblk);
E 5
I 5
		stat = scsi_tt_read(ctlr, unit, io->i_ma, io->i_cc, blk, nblk);
E 5
	else
D 5
		stat = scsi_tt_write(unit, io->i_ma, io->i_cc, blk, nblk);
E 5
I 5
		stat = scsi_tt_write(ctlr, unit, io->i_ma, io->i_cc, blk, nblk);
E 5
	if (stat) {
D 2
		printf("sd(%d,?) err: 0x%x", unit, stat);
E 2
I 2
D 5
		printf("sd(%d,?) err: 0x%x\n", unit, stat);
E 5
I 5
		printf("sd(%d,%d,%d,%d): block=%x, error=0x%x\n",
		       ctlr, unit, io->i_unit, io->i_part, blk, stat);
E 5
E 2
		if (++ss->sc_retry > SDRETRY)
			return(-1);
D 5
		else
			goto retry;
E 5
I 5
		goto retry;
E 5
	}
	return(io->i_cc);
}
E 1
