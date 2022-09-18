h16497
s 00002/00002/00428
d D 8.1 93/06/10 21:47:45 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00429
d D 7.8 93/05/24 22:50:08 mckusick 8 7
c fix include directives
e
s 00001/00001/00429
d D 7.7 92/12/26 16:49:50 hibler 7 6
c Utah update (mostly disklabels)
e
s 00007/00007/00423
d D 7.6 92/10/11 10:01:49 bostic 6 5
c make kernel includes standard
e
s 00063/00066/00367
d D 7.5 92/06/18 21:33:17 hibler 5 4
c merge with latest Utah version
e
s 00003/00003/00430
d D 7.4 91/05/07 10:05:43 hibler 4 3
c DIO-II support
e
s 00002/00002/00431
d D 7.3 91/05/05 13:31:20 bostic 3 2
c includes for standard stand source
e
s 00004/00004/00429
d D 7.2 90/12/16 16:39:46 bostic 2 1
c kernel reorg
e
s 00433/00000/00000
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
D 9
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Van Jacobson of Lawrence Berkeley Laboratory and the Systems
 * Programming Group of the University of Utah Computer Science Department.
 *
 * %sccs.include.redist.c%
 *
 * from: Utah $Hdr: scsi.c 1.3 90/01/27$
 *
 *	%W% (Berkeley) %G%
 */

/*
 * SCSI bus driver for standalone programs.
 */

D 2
#include "../sys/types.h"
#include "../sys/reboot.h"
#include "../hpdev/device.h"
#include "../hpdev/scsireg.h"
E 2
I 2
D 3
#include "sys/types.h"
#include "sys/reboot.h"
E 3
I 3
D 5
#include <sys/param.h>
#include <sys/reboot.h>
E 3
#include "../dev/device.h"
E 5
I 5
D 6
#include "sys/param.h"
#include "sys/reboot.h"
#include "hp/dev/device.h"
E 5
#include "../dev/scsireg.h"
E 2
#include "scsivar.h"
E 6
I 6
#include <sys/param.h>
#include <sys/reboot.h>
#include <hp/dev/device.h>
#include <hp300/dev/scsireg.h>
#include <hp300/stand/scsivar.h>
E 6

D 6
#include "saio.h"
#include "samachdep.h"
E 6
I 6
D 8
#include <stand/saio.h>
E 8
I 8
#include <stand.att/saio.h>
E 8
#include <hp300/stand/samachdep.h>
E 6

struct	scsi_softc scsi_softc[NSCSI];

D 5
#define	scsiunit(x)	((x) >> 3)
#define	scsislave(x)	((x) & 7)

E 5
void scsireset();
D 5
int scsi_cmd_wait = 500;
int scsi_data_wait = 300000;
E 5
I 5
int scsi_cmd_wait = 50000;	/* use the "real" driver init_wait value */
int scsi_data_wait = 50000;	/* use the "real" driver init_wait value */
E 5

scsiinit()
{
	extern struct hp_hw sc_table[];
	register struct hp_hw *hw;
	register struct scsi_softc *hs;
	register int i, addr;
D 5
	static int first = 1;
E 5
I 5
	static int waitset = 0;
E 5
	
	i = 0;
D 4
	for (hw = sc_table; i < NSCSI && hw < &sc_table[MAX_CTLR]; hw++) {
		if (hw->hw_type != SCSI)
E 4
I 4
	for (hw = sc_table; i < NSCSI && hw < &sc_table[MAXCTLRS]; hw++) {
		if (!HW_ISSCSI(hw))
E 4
			continue;
		hs = &scsi_softc[i];
D 4
		hs->sc_addr = hw->hw_addr;
E 4
I 4
		hs->sc_addr = hw->hw_kva;
E 4
		scsireset(i);
		if (howto & RB_ASKNAME)
			printf("scsi%d at sc%d\n", i, hw->hw_sc);
D 5
		/*
		 * Adjust devtype on first call.  This routine assumes that
		 * adaptor is in the high byte of devtype.
		 */
		if (first && ((devtype >> 24) & 0xff) == hw->hw_sc) {
			devtype = (devtype & 0x00ffffff) | (i << 24);
			first = 0;
		}
E 5
I 5
		hw->hw_pa = (caddr_t) i;	/* XXX for autoconfig */
E 5
		hs->sc_alive = 1;
		i++;
	}
I 5
	/*
	 * Adjust the wait values
	 */
	if (!waitset) {
		scsi_cmd_wait *= cpuspeed;
		scsi_data_wait *= cpuspeed;
		waitset = 1;
	}
E 5
}

scsialive(unit)
	register int unit;
{
D 5
	unit = scsiunit(unit);
E 5
	if (unit >= NSCSI || scsi_softc[unit].sc_alive == 0)
		return (0);
	return (1);
}

void
scsireset(unit)
	register int unit;
{
	volatile register struct scsidevice *hd;
	register struct scsi_softc *hs;
	u_int i;

D 5
	unit = scsiunit(unit);
E 5
	hs = &scsi_softc[unit];
	hd = (struct scsidevice *)hs->sc_addr;
	hd->scsi_id = 0xFF;
	DELAY(100);
	/*
	 * Disable interrupts then reset the FUJI chip.
	 */
	hd->scsi_csr  = 0;
	hd->scsi_sctl = SCTL_DISABLE | SCTL_CTRLRST;
	hd->scsi_scmd = 0;
	hd->scsi_tmod = 0;
	hd->scsi_pctl = 0;
	hd->scsi_temp = 0;
	hd->scsi_tch  = 0;
	hd->scsi_tcm  = 0;
	hd->scsi_tcl  = 0;
	hd->scsi_ints = 0;

	/*
	 * Configure the FUJI chip with its SCSI address, all
	 * interrupts enabled & appropriate parity.
	 */
	i = (~hd->scsi_hconf) & 0x7;
	hs->sc_scsi_addr = 1 << i;
	hd->scsi_bdid = i;
	if (hd->scsi_hconf & HCONF_PARITY)
		hd->scsi_sctl = SCTL_DISABLE | SCTL_ABRT_ENAB |
				SCTL_SEL_ENAB | SCTL_RESEL_ENAB |
				SCTL_INTR_ENAB | SCTL_PARITY_ENAB;
	else
		hd->scsi_sctl = SCTL_DISABLE | SCTL_ABRT_ENAB |
				SCTL_SEL_ENAB | SCTL_RESEL_ENAB |
				SCTL_INTR_ENAB;
	hd->scsi_sctl &=~ SCTL_DISABLE;
}


int
scsiabort(hs, hd)
	register struct scsi_softc *hs;
	volatile register struct scsidevice *hd;
{
D 5
	printf("scsi error: scsiabort\n");
E 5
I 5
	printf("scsi%d error: scsiabort\n", hs - scsi_softc);

	scsireset(hs - scsi_softc);
E 5
D 7
	return (0);
E 7
I 7
	DELAY(1000000);
E 7
}

static int
issue_select(hd, target, our_addr)
	volatile register struct scsidevice *hd;
	u_char target, our_addr;
{
	if (hd->scsi_ssts & (SSTS_INITIATOR|SSTS_TARGET|SSTS_BUSY))
		return (1);

	if (hd->scsi_ints & INTS_DISCON)
		hd->scsi_ints = INTS_DISCON;

	hd->scsi_pctl = 0;
	hd->scsi_temp = (1 << target) | our_addr;
	/* select timeout is hardcoded to 2ms */
	hd->scsi_tch = 0;
	hd->scsi_tcm = 32;
	hd->scsi_tcl = 4;

	hd->scsi_scmd = SCMD_SELECT;
	return (0);
}

static int
wait_for_select(hd)
	volatile register struct scsidevice *hd;
{
I 5
	register int wait;
E 5
	u_char ints;

D 5
	while ((ints = hd->scsi_ints) == 0)
E 5
I 5
	wait = scsi_data_wait;
	while ((ints = hd->scsi_ints) == 0) {
		if (--wait < 0)
			return (1);
E 5
		DELAY(1);
I 5
	}
E 5
	hd->scsi_ints = ints;
	return (!(hd->scsi_ssts & SSTS_INITIATOR));
}

static int
ixfer_start(hd, len, phase, wait)
	volatile register struct scsidevice *hd;
	int len;
	u_char phase;
	register int wait;
{

	hd->scsi_tch = len >> 16;
	hd->scsi_tcm = len >> 8;
	hd->scsi_tcl = len;
	hd->scsi_pctl = phase;
	hd->scsi_tmod = 0; /*XXX*/
	hd->scsi_scmd = SCMD_XFR | SCMD_PROG_XFR;

	/* wait for xfer to start or svc_req interrupt */
	while ((hd->scsi_ssts & SSTS_BUSY) == 0) {
		if (hd->scsi_ints || --wait < 0)
			return (0);
		DELAY(1);
	}
	return (1);
}

static int
ixfer_out(hd, len, buf)
	volatile register struct scsidevice *hd;
	int len;
	register u_char *buf;
{
	register int wait = scsi_data_wait;

	for (; len > 0; --len) {
		while (hd->scsi_ssts & SSTS_DREG_FULL) {
			if (hd->scsi_ints || --wait < 0)
				return (len);
			DELAY(1);
		}
		hd->scsi_dreg = *buf++;
	}
	return (0);
}

static int
ixfer_in(hd, len, buf)
	volatile register struct scsidevice *hd;
	int len;
	register u_char *buf;
{
	register int wait = scsi_data_wait;

	for (; len > 0; --len) {
		while (hd->scsi_ssts & SSTS_DREG_EMPTY) {
			if (hd->scsi_ints || --wait < 0) {
				while (! (hd->scsi_ssts & SSTS_DREG_EMPTY)) {
					*buf++ = hd->scsi_dreg;
					--len;
				}
				return (len);
			}
			DELAY(1);
		}
		*buf++ = hd->scsi_dreg;
	}
	return (len);
}

static int
scsiicmd(hs, target, cbuf, clen, buf, len, xferphase)
	struct scsi_softc *hs;
	int target;
	u_char *cbuf;
	int clen;
	u_char *buf;
	int len;
	u_char xferphase;
{
	volatile register struct scsidevice *hd =
				(struct scsidevice *)hs->sc_addr;
D 5
	int i;
E 5
	u_char phase, ints;
	register int wait;

	/* select the SCSI bus (it's an error if bus isn't free) */
	if (issue_select(hd, target, hs->sc_scsi_addr))
D 5
		return (0);
E 5
I 5
		return (-2);
E 5
	if (wait_for_select(hd))
D 5
		return (0);
E 5
I 5
		return (-2);
E 5
	/*
	 * Wait for a phase change (or error) then let the device
	 * sequence us through the various SCSI phases.
	 */
I 5
	hs->sc_stat = -1;
E 5
	phase = CMD_PHASE;
	while (1) {
		wait = scsi_cmd_wait;
		switch (phase) {

		case CMD_PHASE:
			if (ixfer_start(hd, clen, phase, wait))
				if (ixfer_out(hd, clen, cbuf))
					goto abort;
			phase = xferphase;
			break;

		case DATA_IN_PHASE:
			if (len <= 0)
				goto abort;
			wait = scsi_data_wait;
			if (ixfer_start(hd, len, phase, wait) ||
			    !(hd->scsi_ssts & SSTS_DREG_EMPTY))
				ixfer_in(hd, len, buf);
			phase = STATUS_PHASE;
			break;

		case DATA_OUT_PHASE:
			if (len <= 0)
				goto abort;
			wait = scsi_data_wait;
			if (ixfer_start(hd, len, phase, wait))
				if (ixfer_out(hd, len, buf))
					goto abort;
			phase = STATUS_PHASE;
			break;

		case STATUS_PHASE:
			wait = scsi_data_wait;
			if (ixfer_start(hd, sizeof(hs->sc_stat), phase, wait) ||
			    !(hd->scsi_ssts & SSTS_DREG_EMPTY))
				ixfer_in(hd, sizeof(hs->sc_stat), &hs->sc_stat);
			phase = MESG_IN_PHASE;
			break;

		case MESG_IN_PHASE:
			if (ixfer_start(hd, sizeof(hs->sc_msg), phase, wait) ||
			    !(hd->scsi_ssts & SSTS_DREG_EMPTY)) {
				ixfer_in(hd, sizeof(hs->sc_msg), &hs->sc_msg);
				hd->scsi_scmd = SCMD_RST_ACK;
			}
			phase = BUS_FREE_PHASE;
			break;

		case BUS_FREE_PHASE:
D 5
			return (1);
E 5
I 5
			goto out;
E 5

		default:
D 5
			printf("unexpected scsi phase %d\n", phase);
E 5
I 5
			printf("scsi%d: unexpected scsi phase %d\n",
			       hs - scsi_softc, phase);
E 5
			goto abort;
		}
I 5
#ifdef SLOWSCSI
		/*
		 * XXX we have wierd transient problems with booting from
		 * slow scsi disks on fast machines.  I have never been
		 * able to pin the problem down, but a large delay here
		 * seems to always work.
		 */
		DELAY(1000);
#endif
E 5
		/* wait for last command to complete */
		while ((ints = hd->scsi_ints) == 0) {
			if (--wait < 0)
				goto abort;
			DELAY(1);
		}
		hd->scsi_ints = ints;
		if (ints & INTS_SRV_REQ)
			phase = hd->scsi_psns & PHASE;
		else if (ints & INTS_DISCON)
D 5
			return (1);
		else if ((ints & INTS_CMD_DONE) == 0) {
E 5
I 5
			goto out;
		else if ((ints & INTS_CMD_DONE) == 0)
E 5
			goto abort;
D 5
		}
E 5
	}
abort:
	scsiabort(hs, hd);
D 5
	return (0);
E 5
I 5
out:
	return (hs->sc_stat);
E 5
}

int
D 5
scsi_test_unit_rdy(unit)
E 5
I 5
scsi_test_unit_rdy(ctlr, slave)
	int ctlr, slave;
E 5
{
D 5
	int ctlr = scsiunit(unit);
	int slave = scsislave(unit);
E 5
	register struct scsi_softc *hs = &scsi_softc[ctlr];
	static struct scsi_cdb6 cdb = { CMD_TEST_UNIT_READY };

D 5
	if (scsiicmd(hs, slave, &cdb, sizeof(cdb), (u_char *)0, 0,
		     STATUS_PHASE) == 0)
		return (0);
		
	return (hs->sc_stat == 0);
E 5
I 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), (u_char *)0, 0,
			 STATUS_PHASE));
E 5
}

int
D 5
scsi_request_sense(unit, buf, len)
	int unit;
E 5
I 5
scsi_request_sense(ctlr, slave, buf, len)
	int ctlr, slave;
E 5
	u_char *buf;
	unsigned len;
{
D 5
	int ctlr = scsiunit(unit);
	int slave = scsislave(unit);
E 5
	register struct scsi_softc *hs = &scsi_softc[ctlr];
	static struct scsi_cdb6 cdb = { CMD_REQUEST_SENSE };

	cdb.len = len;
D 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len, DATA_IN_PHASE));
E 5
I 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len,
			 DATA_IN_PHASE));
E 5
}

int
D 5
scsi_read_capacity(unit, buf, len)
	int unit;
E 5
I 5
scsi_read_capacity(ctlr, slave, buf, len)
	int ctlr, slave;
E 5
	u_char *buf;
	unsigned len;
{
D 5
	int ctlr = scsiunit(unit);
	int slave = scsislave(unit);
E 5
	register struct scsi_softc *hs = &scsi_softc[ctlr];
	static struct scsi_cdb10 cdb = { CMD_READ_CAPACITY };

D 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len, DATA_IN_PHASE));
E 5
I 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len,
			 DATA_IN_PHASE));
E 5
}

int
D 5
scsi_tt_read(unit, buf, len, blk, nblk)
	int unit;
E 5
I 5
scsi_tt_read(ctlr, slave, buf, len, blk, nblk)
	int ctlr, slave;
E 5
	u_char *buf;
	u_int len;
	daddr_t blk;
	u_int nblk;
{
D 5
	int ctlr = scsiunit(unit);
	int slave = scsislave(unit);
E 5
	register struct scsi_softc *hs = &scsi_softc[ctlr];
	struct scsi_cdb10 cdb;
D 5
	int stat;
E 5

	bzero(&cdb, sizeof(cdb));
	cdb.cmd = CMD_READ_EXT;
	cdb.lbah = blk >> 24;
	cdb.lbahm = blk >> 16;
	cdb.lbalm = blk >> 8;
	cdb.lbal = blk;
	cdb.lenh = nblk >> (8 + DEV_BSHIFT);
	cdb.lenl = nblk >> DEV_BSHIFT;
D 5
	stat = scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len, DATA_IN_PHASE);
	if (stat == 0)
		return (1);
	return (hs->sc_stat);
E 5
I 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len,
			 DATA_IN_PHASE));
E 5
}

int
D 5
scsi_tt_write(unit, buf, len, blk, nblk)
	int unit;
E 5
I 5
scsi_tt_write(ctlr, slave, buf, len, blk, nblk)
	int ctlr, slave;
E 5
	u_char *buf;
	u_int len;
	daddr_t blk;
	u_int nblk;
{
D 5
	int ctlr = scsiunit(unit);
	int slave = scsislave(unit);
E 5
	register struct scsi_softc *hs = &scsi_softc[ctlr];
	struct scsi_cdb10 cdb;
D 5
	int stat;
E 5

	bzero(&cdb, sizeof(cdb));
	cdb.cmd = CMD_WRITE_EXT;
	cdb.lbah = blk >> 24;
	cdb.lbahm = blk >> 16;
	cdb.lbalm = blk >> 8;
	cdb.lbal = blk;
	cdb.lenh = nblk >> (8 + DEV_BSHIFT);
	cdb.lenl = nblk >> DEV_BSHIFT;
D 5
	stat = scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len, DATA_OUT_PHASE);
	if (stat == 0)
		return (1);
	return (hs->sc_stat);
E 5
I 5
	return (scsiicmd(hs, slave, &cdb, sizeof(cdb), buf, len,
			 DATA_OUT_PHASE));
E 5
}
E 1
