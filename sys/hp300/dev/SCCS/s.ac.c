h49791
s 00001/00000/00507
d D 8.2 94/01/12 21:28:31 hibler 8 7
c missing close bracket (from cgd)
e
s 00002/00002/00505
d D 8.1 93/06/10 21:31:41 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00008/00496
d D 7.6 93/04/27 13:30:53 hibler 6 5
c fix race in open
e
s 00000/00005/00504
d D 7.5 92/12/27 09:31:32 hibler 5 4
c get rid of unneeded includes
e
s 00004/00006/00505
d D 7.4 92/11/30 20:53:42 bostic 4 3
c from Carl Staelin, make it compile
e
s 00005/00000/00506
d D 7.3 92/11/06 08:59:04 bostic 3 2
c Cael Staelin made it compile
e
s 00012/00011/00494
d D 7.2 92/10/11 09:23:37 bostic 2 1
c make kernel includes standard
e
s 00505/00000/00000
d D 7.1 92/06/05 15:33:06 hibler 1 0
c merge latest Utah hp300 code including 68040 support
e
u
U
t
T
I 1
/*
 * Copyright (c) 1991 University of Utah.
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: ac.c 1.5 92/01/21$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SCSI driver for MO autochanger.
 *
 * Very crude.  Because of the lack of connect/disconnect support in the
 * scsi driver, this driver can tie up the SCSI bus for a long time.  It
 * also grabs a DMA channel and holds it for the duration even though it
 * never uses it.
 */

#include "ac.h"
#if NAC > 0

D 2
#include "param.h"
#include "buf.h"
#include "errno.h"
#include "user.h"
#include "ioctl.h"
#include "kernel.h"
#include "malloc.h"
E 2
I 2
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/errno.h>
I 4
D 5
#include <sys/time.h>
#include <sys/ucred.h>
#include <sys/proc.h>
#include <vm/vm.h>
E 4
#include <sys/user.h>
E 5
#include <sys/ioctl.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
I 3
D 4
#include <sys/time.h>
#include <sys/ucred.h>
#include <sys/proc.h>
E 4

D 4
#include <vm/vm.h>
E 3
E 2

E 4
D 2
#include "hp/dev/device.h"
#include "scsireg.h"
#include "acioctl.h"
#include "acvar.h"
E 2
I 2
#include <hp/dev/device.h>
D 4

E 4
#include <hp300/dev/scsireg.h>
#include <hp300/dev/acioctl.h>
#include <hp300/dev/acvar.h>
E 2

extern int scsi_test_unit_rdy();
extern int scsi_request_sense();
extern int scsiustart();
extern int scsigo();
extern void scsifree();
extern void scsireset();
extern void scsi_delay();

extern int scsi_immed_command();

int	acinit(), acstart(), acgo(), acintr();

struct	driver acdriver = {
	acinit, "ac", acstart, acgo, acintr,
};

struct	ac_softc ac_softc[NAC];
static	struct buf acbuf[NAC];
static	struct scsi_fmt_cdb accmd[NAC];

#ifdef DEBUG
int ac_debug = 0x0000;
#define ACD_FOLLOW	0x0001
#define ACD_OPEN	0x0002
#endif

acinit(hd)
	register struct hp_device *hd;
{
	int unit = hd->hp_unit;
	register struct ac_softc *sc = &ac_softc[unit];

	sc->sc_hd = hd;
	sc->sc_punit = hd->hp_flags & 7;
	if (acident(sc, hd) < 0)
		return(0);
	sc->sc_dq.dq_unit = unit;
	sc->sc_dq.dq_ctlr = hd->hp_ctlr;
	sc->sc_dq.dq_slave = hd->hp_slave;
	sc->sc_dq.dq_driver = &acdriver;
	sc->sc_bp = &acbuf[unit];
	sc->sc_cmd = &accmd[unit];
	sc->sc_flags = ACF_ALIVE;
	return(1);
}

acident(sc, hd)
	register struct ac_softc *sc;
	register struct hp_device *hd;
{
	int unit;
	register int ctlr, slave;
	int i, stat;
	int tries = 5;
	char idstr[32];
	struct scsi_inquiry inqbuf;
	static struct scsi_fmt_cdb inq = {
		6,
		CMD_INQUIRY, 0, 0, 0, sizeof(inqbuf), 0
	};

	ctlr = hd->hp_ctlr;
	slave = hd->hp_slave;
	unit = sc->sc_punit;
	scsi_delay(-1);

	/*
	 * See if device is ready
	 */
	while ((i = scsi_test_unit_rdy(ctlr, slave, unit)) != 0) {
		if (i == -1 || --tries < 0)
			/* doesn't exist or not a CCS device */
			goto failed;
		if (i == STS_CHECKCOND) {
			u_char sensebuf[128];
			struct scsi_xsense *sp;

			scsi_request_sense(ctlr, slave, unit,
					   sensebuf, sizeof(sensebuf));
			sp = (struct scsi_xsense *) sensebuf;
			if (sp->class == 7 && sp->key == 6)
				/* drive doing an RTZ -- give it a while */
				DELAY(1000000);
		}
		DELAY(1000);
	}
	/*
	 * Find out if it is an autochanger
	 */
	if (scsi_immed_command(ctlr, slave, unit, &inq,
			       (u_char *)&inqbuf, sizeof(inqbuf), B_READ))
		goto failed;

	if (inqbuf.type != 8 || inqbuf.qual != 0x80 || inqbuf.version != 2)
		goto failed;

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
	printf("ac%d: %s %s rev %s\n", hd->hp_unit,
	       &idstr[0], &idstr[8], &idstr[24]);

	scsi_delay(0);
	return(inqbuf.type);
failed:
	scsi_delay(0);
	return(-1);
}

/*ARGSUSED*/
acopen(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	register int unit = minor(dev);
	register struct ac_softc *sc = &ac_softc[unit];
	int error = 0;

	if (unit >= NAC || (sc->sc_flags & ACF_ALIVE) == 0)
D 6
		error = ENXIO;
	else if (sc->sc_flags & ACF_OPEN)
		error = EBUSY;
	else if (acgeteinfo(dev))
		error = EIO;
	else
		sc->sc_flags |= ACF_OPEN;
	return(error);
E 6
I 6
		return(ENXIO);
	if (sc->sc_flags & ACF_OPEN)
		return(EBUSY);
	/*
	 * Since acgeteinfo can block we mark the changer open now.
	 */
	sc->sc_flags |= ACF_OPEN;
	if (acgeteinfo(dev)) {
		sc->sc_flags &= ~ACF_OPEN;
		return(EIO);
I 8
	}
E 8
	return(0);
E 6
}

/*ARGSUSED*/
acclose(dev, flag, mode, p)
	dev_t dev;
	int flag, mode;
	struct proc *p;
{
	struct ac_softc *sc = &ac_softc[minor(dev)];

	sc->sc_flags &= ~ACF_OPEN;
}

#define ACRESLEN(ep)	\
	(8 + (ep)->nmte*12 + (ep)->nse*12 + (ep)->niee*12 + (ep)->ndte*20)

/*ARGSUSED*/
acioctl(dev, cmd, data, flag, p)
	dev_t dev;
	int cmd;
	caddr_t data; 
	int flag;
	struct proc *p;
{
	register struct ac_softc *sc = &ac_softc[minor(dev)];
	char *dp;
	int dlen, error = 0;

	switch (cmd) {

	default:
		return (EINVAL);

	/* perform an init element status and mode sense to reset state */
	case ACIOCINIT:
		error = accommand(dev, ACCMD_INITES, (caddr_t)0, 0);
		if (!error)
			error = acgeteinfo(dev);
		break;

	/* copy internal element information */
	case ACIOCGINFO:
		*(struct acinfo *)data = sc->sc_einfo;
		break;

	case ACIOCRAWES:
	{
		struct acbuffer *acbp = (struct acbuffer *)data;

		dlen = ACRESLEN(&sc->sc_einfo);
		dp = (char *) malloc(dlen, M_DEVBUF, M_WAITOK);
		error = accommand(dev, ACCMD_READES, dp, dlen);
		if (!error) {
			dlen = *(int *)&dp[4] + 8;
			if (dlen > acbp->buflen)
				dlen = acbp->buflen;
			error = copyout(dp, acbp->bufptr, dlen);
		}
		break;
	}

	case ACIOCGSTAT:
	{
		struct acbuffer *acbp = (struct acbuffer *)data;

		dlen = ACRESLEN(&sc->sc_einfo);
		dp = (char *) malloc(dlen, M_DEVBUF, M_WAITOK);
		error = accommand(dev, ACCMD_READES, dp, dlen);
		if (!error) {
			int ne;
			char *tbuf;

			ne = sc->sc_einfo.nmte + sc->sc_einfo.nse +
				sc->sc_einfo.niee + sc->sc_einfo.ndte;
			dlen = ne * sizeof(struct aceltstat);
			tbuf = (char *) malloc(dlen, M_DEVBUF, M_WAITOK);
			acconvert(dp, tbuf, ne);
			if (dlen > acbp->buflen)
				dlen = acbp->buflen;
			error = copyout(tbuf, acbp->bufptr, dlen);
			free(tbuf, M_DEVBUF);
		}
		free(dp, M_DEVBUF);
		break;
	}

	case ACIOCMOVE:
		error = accommand(dev, ACCMD_MOVEM, data,
				  sizeof(struct acmove));
		break;
	}
	return(error);
}

accommand(dev, command, bufp, buflen)
	dev_t dev;
	int command;
	char *bufp;
	int buflen;
{
	int unit = minor(dev);
	register struct ac_softc *sc = &ac_softc[unit];
	register struct buf *bp = sc->sc_bp;
	register struct scsi_fmt_cdb *cmd = sc->sc_cmd;
	int error;

#ifdef DEBUG
	if (ac_debug & ACD_FOLLOW)
		printf("accommand(dev=%x, cmd=%x, buf=%x, buflen=%x)\n",
		       dev, command, bufp, buflen);
#endif
	if (sc->sc_flags & ACF_ACTIVE)
		panic("accommand: active!");

	sc->sc_flags |= ACF_ACTIVE;
	bzero((caddr_t)cmd->cdb, sizeof(cmd->cdb));
	cmd->cdb[0] = command;

	switch (command) {
	case ACCMD_INITES:
		cmd->len = 6;
		break;
	case ACCMD_READES:
		cmd->len = 12;
		*(short *)&cmd->cdb[2] = 0;
		*(short *)&cmd->cdb[4] =
			sc->sc_einfo.nmte + sc->sc_einfo.nse +
			sc->sc_einfo.niee + sc->sc_einfo.ndte;
		cmd->cdb[7] = buflen >> 16;
		cmd->cdb[8] = buflen >> 8;
		cmd->cdb[9] = buflen;
		break;
	case ACCMD_MODESENSE:
		cmd->len = 6;
		cmd->cdb[2] = 0x3F;	/* all pages */
		cmd->cdb[4] = buflen;
		break;
	case ACCMD_MOVEM:
		cmd->len = 12;
		*(short *)&cmd->cdb[2] = sc->sc_picker;
		*(short *)&cmd->cdb[4] = *(short *)&bufp[0];
		*(short *)&cmd->cdb[6] = *(short *)&bufp[2];
		if (*(short *)&bufp[4] & AC_INVERT)
			cmd->cdb[10] = 1;
		bufp = 0;
		buflen = 0;
		break;
	default:
		panic("accommand: bad command");
	}
	bp->b_flags = B_BUSY|B_READ;
	bp->b_dev = dev;
	bp->b_un.b_addr = bufp;
	bp->b_bcount = buflen;
	bp->b_resid = 0;
	bp->b_blkno = 0;
	bp->b_error = 0;
	if (scsireq(&sc->sc_dq))
		acstart(unit);
	error = biowait(bp);
	sc->sc_flags &= ~ACF_ACTIVE;
	return (error);
}

acstart(unit)
	int unit;
{
#ifdef DEBUG
	if (ac_debug & ACD_FOLLOW)
		printf("acstart(unit=%x)\n", unit);
#endif
	if (scsiustart(ac_softc[unit].sc_hd->hp_ctlr))
		acgo(unit);
}

acgo(unit)
	int unit;
{
	register struct ac_softc *sc = &ac_softc[unit];
	register struct buf *bp = sc->sc_bp;
	struct hp_device *hp = sc->sc_hd;
	int stat;

#ifdef DEBUG
	if (ac_debug & ACD_FOLLOW)
		printf("acgo(unit=%x): ", unit);
#endif
	stat = scsigo(hp->hp_ctlr, hp->hp_slave, sc->sc_punit,
		      bp, sc->sc_cmd, 0);
#ifdef DEBUG
	if (ac_debug & ACD_FOLLOW)
		printf("scsigo returns %x\n", stat);
#endif
	if (stat) {
		bp->b_error = EIO;
		bp->b_flags |= B_ERROR;
		(void) biodone(bp);
		scsifree(&sc->sc_dq);
	}
}

acintr(unit, stat)
	int unit, stat;
{
	register struct ac_softc *sc = &ac_softc[unit];
	register struct buf *bp = sc->sc_bp;
	u_char sensebuf[78];
	struct scsi_xsense *sp;

#ifdef DEBUG
	if (ac_debug & ACD_FOLLOW)
		printf("acintr(unit=%x, stat=%x)\n", unit, stat);
#endif
	switch (stat) {
	case 0:
		bp->b_resid = 0;
		break;
	case STS_CHECKCOND:
		scsi_request_sense(sc->sc_hd->hp_ctlr, sc->sc_hd->hp_slave,
				   sc->sc_punit, sensebuf, sizeof sensebuf);
		sp = (struct scsi_xsense *)sensebuf;
		printf("ac%d: acintr sense key=%x, ac=%x, acq=%x\n",
		       unit, sp->key, sp->info4, sp->len);
		bp->b_flags |= B_ERROR;
		bp->b_error = EIO;
		break;
	default:
		printf("ac%d: acintr unknown status 0x%x\n", unit, stat);
		break;
	}
	(void) biodone(sc->sc_bp);
	scsifree(&sc->sc_dq);
}

acgeteinfo(dev)
	dev_t dev;
{
	register struct ac_softc *sc = &ac_softc[minor(dev)];
	register char *bp;
	char msbuf[48];
	int error;

	bzero(msbuf, sizeof msbuf);
	error = accommand(dev, ACCMD_MODESENSE, msbuf, sizeof msbuf);
	if (error)
		return(error);
	bp = &msbuf[4];
	while (bp < &msbuf[48]) {
		switch (bp[0] & 0x3F) {
		case 0x1D:
			sc->sc_einfo = *(struct acinfo *)&bp[2];
			sc->sc_picker = sc->sc_einfo.fmte;	/* XXX */
			return(0);
		case 0x1E:
			bp += 4;
			break;
		case 0x1F:
			bp += 20;
			break;
		default:
			printf("acgeteinfo: bad page type %x\n", bp[0]);
			return(EIO);
		}
	}
	return(EIO);
}

acconvert(sbuf, dbuf, ne)
	char *sbuf, *dbuf;
	int ne;
{
	register struct aceltstat *ep = (struct aceltstat *)dbuf;
	register struct ac_restatphdr *phdr;
	register struct ac_restatdb *dbp;
	struct ac_restathdr *hdr;
#ifdef DEBUG
	register int bcount;
#endif

	hdr = (struct ac_restathdr *)&sbuf[0];
	sbuf += sizeof *hdr;
#ifdef DEBUG
	if (ac_debug & ACD_FOLLOW)
		printf("element status: first=%d, num=%d, len=%d\n",
		       hdr->ac_felt, hdr->ac_nelt, hdr->ac_bcount);
	if (hdr->ac_nelt != ne) {
		printf("acconvert: # of elements, %d != %d\n",
		       hdr->ac_nelt, ne);
		if (hdr->ac_nelt < ne)
			ne = hdr->ac_nelt;
	}
	bcount = hdr->ac_bcount;
#endif
	while (ne) {
		phdr = (struct ac_restatphdr *)sbuf;
		sbuf += sizeof *phdr;
#ifdef DEBUG
		bcount -= sizeof *phdr;
#endif
		dbp = (struct ac_restatdb *)sbuf;
		sbuf += phdr->ac_bcount;
#ifdef DEBUG
		bcount -= phdr->ac_bcount;
#endif
		while (dbp < (struct ac_restatdb *)sbuf) {
			ep->type = phdr->ac_type;
			ep->eaddr = dbp->ac_eaddr;
			ep->flags = 0;
			if (dbp->ac_full)
				ep->flags |= AC_FULL;
			if (dbp->ac_exc)
				ep->flags |= AC_ERROR;
			if (dbp->ac_acc)
				ep->flags |= AC_ACCESS;
			dbp = (struct ac_restatdb *)
				((char *)dbp + phdr->ac_dlen);
			ep++;
			ne--;
		}
#ifdef DEBUG
		if (ne < 0 || bcount < 0)
			panic("acconvert: inconsistant");
#endif
	}
}
#endif
E 1
