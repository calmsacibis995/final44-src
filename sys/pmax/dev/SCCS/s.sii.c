h26710
s 00008/00000/01737
d D 8.4 94/11/30 10:52:43 mckusick 13 12
c fix undefined reference when DEBUG not defined (from ralph)
e
s 00259/00151/01478
d D 8.3 94/05/21 12:44:57 mckusick 12 11
c update from Ralph to fix serious SCSI bug
e
s 00006/00006/01623
d D 8.2 93/11/30 16:16:20 mckusick 11 10
c update from Ralph
e
s 00002/00002/01627
d D 8.1 93/06/29 15:13:08 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00007/01623
d D 7.8 93/06/29 15:12:44 mckusick 9 7
c fix log output (more work needed)
e
s 00002/00002/01628
d R 8.1 93/06/10 22:39:38 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00017/00012/01613
d D 7.7 92/11/15 15:49:08 ralph 7 6
c changes for maxine from Rick Macklem.
e
s 00003/00003/01622
d D 7.6 92/10/11 11:24:42 bostic 6 5
c use pmax as top directory, not mips
e
s 00010/00010/01615
d D 7.5 92/10/11 11:13:36 bostic 5 4
c make kernel includes standard
e
s 00002/00006/01623
d D 7.4 92/03/29 20:44:30 ralph 4 3
c minor cleanup
e
s 00001/00001/01628
d D 7.3 92/02/29 17:33:10 ralph 3 2
c fix syntax error
e
s 00010/00015/01619
d D 7.2 92/02/29 11:11:26 ralph 2 1
c changes to support DS5000
e
s 01634/00000/00000
d D 7.1 92/01/07 18:29:25 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 7
/*
 * Copyright (c) 1992 Regents of the University of California.
E 7
I 7
/*-
D 10
 * Copyright (c) 1992 The Regents of the University of California.
E 7
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
D 7
 * Ralph Campbell.
E 7
I 7
 * Ralph Campbell and Rick Macklem.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: /sprite/src/kernel/dev/ds3100.md/RCS/devSII.c,
D 3
 *	v 9.2 89/09/14 13:37:41 jhh Exp $ SPRITE (DECWRL)"; */
E 3
I 3
 *	v 9.2 89/09/14 13:37:41 jhh Exp $ SPRITE (DECWRL)";
E 3
 */

#include "sii.h"
#if NSII > 0
/*
 * SCSI interface driver
 */
D 5
#include "param.h"
#include "systm.h"
#include "dkstat.h"
#include "buf.h"
#include "conf.h"
#include "errno.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dkstat.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/errno.h>
E 5

D 5
#include "machine/machConst.h"
#include "device.h"
#include "scsi.h"
#include "siireg.h"
E 5
I 5
#include <machine/machConst.h>
D 6
#include <mips/dev/device.h>
#include <mips/dev/scsi.h>
#include <mips/dev/siireg.h>
E 6
I 6
#include <pmax/dev/device.h>
#include <pmax/dev/scsi.h>
#include <pmax/dev/siireg.h>
E 6
E 5

I 7
#include <pmax/pmax/kn01.h>

E 7
int	siiprobe();
void	siistart();
struct	driver siidriver = {
	"sii", siiprobe, siistart, 0,
};

typedef struct scsi_state {
	int	statusByte;	/* status byte returned during STATUS_PHASE */
	int	dmaDataPhase;	/* which data phase to expect */
	int	dmaCurPhase;	/* SCSI phase if DMA is in progress */
	int	dmaPrevPhase;	/* SCSI phase of DMA suspended by disconnect */
	u_short	*dmaAddr[2];	/* DMA buffer memory address */
	int	dmaBufIndex;	/* which of the above is currently in use */
	int	dmalen;		/* amount to transfer in this chunk */
	int	cmdlen;		/* total remaining amount of cmd to transfer */
	u_char	*cmd;		/* current pointer within scsicmd->cmd */
	int	buflen;		/* total remaining amount of data to transfer */
	char	*buf;		/* current pointer within scsicmd->buf */
	u_short	flags;		/* see below */
	u_short	prevComm;	/* command reg before disconnect */
	u_short	dmaCtrl;	/* DMA control register if disconnect */
	u_short	dmaAddrL;	/* DMA address register if disconnect */
	u_short	dmaAddrH;	/* DMA address register if disconnect */
	u_short	dmaCnt;		/* DMA count if disconnect */
	u_short	dmaByte;	/* DMA byte if disconnect on odd boundary */
	u_short	dmaReqAck;	/* DMA synchronous xfer offset or 0 if async */
} State;

/* state flags */
#define FIRST_DMA	0x01	/* true if no data DMA started yet */
I 12
#define PARITY_ERR	0x02	/* true if parity error seen */
E 12

#define SII_NCMD	7
struct siisoftc {
	SIIRegs	*sc_regs;		/* HW address of SII controller chip */
	int	sc_flags;
	int	sc_target;		/* target SCSI ID if connected */
	ScsiCmd	*sc_cmd[SII_NCMD];	/* active command indexed by ID */
	State	sc_st[SII_NCMD];	/* state info for each active command */
} sii_softc[NSII];

/* 
 * MACROS for timing out spin loops.
 *
 * Wait until expression is true.
 *
 * Control register bits can change at any time so when the CPU
 * reads a register, the bits might change and
 * invalidate the setup and hold times for the CPU.
 * This macro reads the register twice to be sure the value is stable.
 *
 *	args:	var 		- variable to save control register contents
 *		reg		- control register to read
 *		expr 		- expression to spin on
 *		spincount 	- maximum number of times through the loop
 *		cntr		- variable for number of tries
 */
#define	SII_WAIT_UNTIL(var, reg, expr, spincount, cntr) {	\
D 12
		register unsigned tmp = reg;			\
E 12
I 12
		register u_int tmp = reg;			\
E 12
		for (cntr = 0; cntr < spincount; cntr++) {	\
			while (tmp != (var = reg))		\
				tmp = var;			\
			if (expr)				\
				break;				\
			if (cntr >= 100)			\
				DELAY(100);			\
		}						\
	}

#ifdef DEBUG
int	sii_debug = 1;
int	sii_debug_cmd;
int	sii_debug_bn;
int	sii_debug_sz;
#define NLOG 16
struct sii_log {
	u_short	cstat;
	u_short	dstat;
	u_short	comm;
	u_short	msg;
I 12
	int	rlen;
	int	dlen;
E 12
	int	target;
} sii_log[NLOG], *sii_logp = sii_log;
#endif

u_char	sii_buf[256];	/* used for extended messages */

#define NORESET	0
#define RESET	1
#define NOWAIT	0
#define WAIT	1

/* define a safe address in the SCSI buffer for doing status & message DMA */
D 7
#define SII_BUF_ADDR	(MACH_SCSI_BUFFER_ADDR + SII_MAX_DMA_XFER_LENGTH * 14)
E 7
I 7
#define SII_BUF_ADDR	(MACH_PHYS_TO_UNCACHED(KN01_SYS_SII_B_START) \
		+ SII_MAX_DMA_XFER_LENGTH * 14)
E 7

D 7
extern void sii_Reset();
extern void sii_StartCmd();
extern void sii_CmdDone();
extern void sii_DoIntr();
extern void sii_StateChg();
extern void sii_DoSync();
extern void sii_StartDMA();
E 7
I 7
static void sii_Reset();
static void sii_StartCmd();
static void sii_CmdDone();
static void sii_DoIntr();
static void sii_StateChg();
static void sii_DoSync();
static void sii_StartDMA();
static int sii_GetByte();
E 7

/*
 * Test to see if device is present.
 * Return true if found and initialized ok.
 */
siiprobe(cp)
	register struct pmax_ctlr *cp;
{
	register struct siisoftc *sc;
	register int i;

	if (cp->pmax_unit >= NSII)
		return (0);
	sc = &sii_softc[cp->pmax_unit];
	sc->sc_regs = (SIIRegs *)cp->pmax_addr;
	sc->sc_flags = cp->pmax_flags;
	sc->sc_target = -1;	/* no command active */
	/*
	 * Give each target its own DMA buffer region.
	 * Make it big enough for 2 max transfers so we can ping pong buffers
	 * while we copy the data.
	 */
	for (i = 0; i < SII_NCMD; i++) {
D 7
		sc->sc_st[i].dmaAddr[0] = (u_short *)MACH_SCSI_BUFFER_ADDR +
E 7
I 7
		sc->sc_st[i].dmaAddr[0] = (u_short *)
			MACH_PHYS_TO_UNCACHED(KN01_SYS_SII_B_START) +
E 7
			2 * SII_MAX_DMA_XFER_LENGTH * i;
		sc->sc_st[i].dmaAddr[1] = sc->sc_st[i].dmaAddr[0] +
			SII_MAX_DMA_XFER_LENGTH;
	}

	printf("sii%d at nexus0 csr 0x%x\n", cp->pmax_unit, cp->pmax_addr);
	sii_Reset(sc->sc_regs, RESET);
	return (1);
}

/*
 * Start activity on a SCSI device.
 * We maintain information on each device separately since devices can
 * connect/disconnect during an operation.
 */
void
siistart(scsicmd)
	register ScsiCmd *scsicmd;	/* command to start */
{
	register struct scsi_device *sdp = scsicmd->sd;
	register struct siisoftc *sc = &sii_softc[sdp->sd_ctlr];
	int s;

	s = splbio();
	/*
	 * Check if another command is already in progress.
	 * We may have to change this if we allow SCSI devices with
	 * separate LUNs.
	 */
	if (sc->sc_cmd[sdp->sd_drive]) {
		printf("sii%d: device %s busy at start\n", sdp->sd_ctlr,
			sdp->sd_driver->d_name);
		(*sdp->sd_driver->d_done)(scsicmd->unit, EBUSY,
			scsicmd->buflen, 0);
		splx(s);
	}
	sc->sc_cmd[sdp->sd_drive] = scsicmd;
	sii_StartCmd(sc, sdp->sd_drive);
	splx(s);
}

/*
 * Check to see if any SII chips have pending interrupts
 * and process as appropriate.
 */
void
D 2
siiintr()
E 2
I 2
siiintr(unit)
	int unit;
E 2
{
D 2
	register struct siisoftc *sc;
E 2
I 2
	register struct siisoftc *sc = &sii_softc[unit];
E 2
D 12
	unsigned dstat;
E 12
I 12
	u_int dstat;
E 12
D 2
	int seenany;
E 2

	/*
	 * Find which controller caused the interrupt.
	 */
D 2
	for (sc = sii_softc; sc < &sii_softc[NSII]; sc++) {
		dstat = sc->sc_regs->dstat;
		if (dstat & (SII_CI | SII_DI)) {
			sii_DoIntr(sc, dstat);
			seenany++;
		}
	}
#ifdef DEBUG
	if (!seenany && sii_debug > 4)
		printf("sii?: spurious interrupt\n");
#endif
E 2
I 2
	dstat = sc->sc_regs->dstat;
	if (dstat & (SII_CI | SII_DI))
		sii_DoIntr(sc, dstat);
E 2
}

/*
 * Reset the SII chip and do a SCSI reset if 'reset' is true.
 * NOTE: if !cold && reset, should probably probe for devices
 * since a SCSI bus reset will set UNIT_ATTENTION.
 */
static void
sii_Reset(regs, reset)
	register SIIRegs *regs;
	int reset;				/* TRUE => reset SCSI bus */
{

#ifdef DEBUG
	if (sii_debug > 1)
		printf("sii: RESET\n");
#endif
	/*
	 * Reset the SII chip.
	 */
	regs->comm = SII_CHRESET;
	/*
	 * Set arbitrated bus mode.
	 */
	regs->csr = SII_HPM;
	/*
	 * SII is always ID 7.
	 */
	regs->id = SII_ID_IO | 7;
	/*
	 * Enable SII to drive the SCSI bus.
	 */
	regs->dictrl = SII_PRE;
	regs->dmctrl = 0;

	if (reset) {
		register int i;

		/*
		 * Assert SCSI bus reset for at least 25 Usec to clear the 
		 * world. SII_DO_RST is self clearing.
		 * Delay 250 ms before doing any commands.
		 */
		regs->comm = SII_DO_RST;
		MachEmptyWriteBuffer();
		DELAY(250000);

		/* rearbitrate synchronous offset */
		for (i = 0; i < SII_NCMD; i++)
			sii_softc[0].sc_st[i].dmaReqAck = 0;
	}

	/*
	 * Clear any pending interrupts from the reset.
	 */
	regs->cstat = regs->cstat;
	regs->dstat = regs->dstat;
	/*
	 * Set up SII for arbitrated bus mode, SCSI parity checking,
	 * Reselect Enable, and Interrupt Enable.
	 */
	regs->csr = SII_HPM | SII_RSE | SII_PCE | SII_IE;
	MachEmptyWriteBuffer();
}

/*
 * Start a SCSI command by sending the cmd data
 * to a SCSI controller via the SII.
 * Call the device done proceedure if it can't be started.
 * NOTE: we should be called with interrupts disabled.
 */
static void
sii_StartCmd(sc, target)
	register struct siisoftc *sc;	/* which SII to use */
	register int target;		/* which command to start */
{
	register SIIRegs *regs;	
	register ScsiCmd *scsicmd;
	register State *state;
D 12
	register unsigned status;
E 12
I 12
	register u_int status;
E 12
	int error, retval;

	/* if another command is currently in progress, just wait */
	if (sc->sc_target >= 0)
		return;

	/* initialize state information for this command */
	scsicmd = sc->sc_cmd[target];
	state = &sc->sc_st[target];
	state->flags = FIRST_DMA;
	state->prevComm = 0;
	state->dmalen = 0;
	state->dmaCurPhase = -1;
	state->dmaPrevPhase = -1;
	state->dmaBufIndex = 0;
	state->cmd = scsicmd->cmd;
	state->cmdlen = scsicmd->cmdlen;
	if ((state->buflen = scsicmd->buflen) == 0) {
		state->dmaDataPhase = -1; /* illegal phase. shouldn't happen */
		state->buf = (char *)0;
	} else {
		state->dmaDataPhase =
			(scsicmd->flags & SCSICMD_DATA_TO_DEVICE) ?
			SII_DATA_OUT_PHASE : SII_DATA_IN_PHASE;
		state->buf = scsicmd->buf;
D 4
		if (state->buflen > SII_MAX_DMA_XFER_LENGTH &&
		    (scsicmd->flags & SCSICMD_DATA_TO_DEVICE))
			printf("sii_StartCmd: target %d dma %d\n",
				target, state->buflen); /* XXX */
E 4
	}

#ifdef DEBUG
	if (sii_debug > 1) {
		printf("sii_StartCmd: %s target %d cmd 0x%x addr %x size %d dma %d\n",
			scsicmd->sd->sd_driver->d_name, target,
			scsicmd->cmd[0], scsicmd->buf, scsicmd->buflen,
			state->dmaDataPhase);
	}
	sii_debug_cmd = scsicmd->cmd[0];
D 12
	if (scsicmd->cmd[0] == SCSI_READ_EXT) {
E 12
I 12
	if (scsicmd->cmd[0] == SCSI_READ_EXT ||
	    scsicmd->cmd[0] == SCSI_WRITE_EXT) {
E 12
		sii_debug_bn = (scsicmd->cmd[2] << 24) |
			(scsicmd->cmd[3] << 16) |
			(scsicmd->cmd[4] << 8) |
			scsicmd->cmd[5];
		sii_debug_sz = (scsicmd->cmd[7] << 8) | scsicmd->cmd[8];
I 12
	} else {
		sii_debug_bn = 0;
		sii_debug_sz = 0;
E 12
	}
#endif

	/* try to select the target */
	regs = sc->sc_regs;

	/*
	 * Another device may have selected us; in which case,
	 * this command will be restarted later.
	 */
	if ((status = regs->dstat) & (SII_CI | SII_DI)) {
		sii_DoIntr(sc, status);
		return;
	}

	sc->sc_target = target;
I 12
#if 0
	/* seem to have problems with synchronous transfers */
E 12
	if (scsicmd->flags & SCSICMD_USE_SYNC) {
		printf("sii_StartCmd: doing extended msg\n"); /* XXX */
		/*
		 * Setup to send both the identify message and the synchronous
		 * data transfer request.
		 */
		sii_buf[0] = SCSI_DIS_REC_IDENTIFY;
		sii_buf[1] = SCSI_EXTENDED_MSG;
		sii_buf[2] = 3;		/* message length */
		sii_buf[3] = SCSI_SYNCHRONOUS_XFER;
		sii_buf[4] = 0;
		sii_buf[5] = 3;		/* maximum SII chip supports */

		state->dmaCurPhase = SII_MSG_OUT_PHASE,
		state->dmalen = 6;
		CopyToBuffer((u_short *)sii_buf,
			(volatile u_short *)SII_BUF_ADDR, 6);
		regs->slcsr = target;
D 12
		regs->dmctrl = 0;
D 11
		regs->dmaddrl = ((unsigned)SII_BUF_ADDR >> 1);
		regs->dmaddrh = ((unsigned)SII_BUF_ADDR >> 17) & 03;
E 11
I 11
		regs->dmaddrl = ((u_short)SII_BUF_ADDR >> 1);
		regs->dmaddrh = ((u_short)SII_BUF_ADDR >> 17) & 03;
E 12
I 12
		regs->dmctrl = state->dmaReqAck;
		regs->dmaddrl = (u_short)(SII_BUF_ADDR >> 1);
		regs->dmaddrh = (u_short)(SII_BUF_ADDR >> 17) & 03;
E 12
E 11
		regs->dmlotc = 6;
		regs->comm = SII_DMA | SII_INXFER | SII_SELECT | SII_ATN |
			SII_CON | SII_MSG_OUT_PHASE;
D 12
	} else {
E 12
I 12
	} else
#endif
	{
E 12
		/* do a chained, select with ATN and programmed I/O command */
		regs->data = SCSI_DIS_REC_IDENTIFY;
		regs->slcsr = target;
D 12
		regs->dmctrl = 0;
E 12
I 12
		regs->dmctrl = state->dmaReqAck;
E 12
		regs->comm = SII_INXFER | SII_SELECT | SII_ATN | SII_CON |
			SII_MSG_OUT_PHASE;
	}
	MachEmptyWriteBuffer();

	/*
	 * Wait for something to happen
	 * (should happen soon or we would use interrupts).
	 */
	SII_WAIT_UNTIL(status, regs->cstat, status & (SII_CI | SII_DI),
D 4
		SII_WAIT_COUNT/2, retval);
E 4
I 4
		SII_WAIT_COUNT/4, retval);
E 4

	/* check to see if we are connected OK */
	if ((status & (SII_RST | SII_SCH | SII_STATE_MSK)) ==
	    (SII_SCH | SII_CON)) {
		regs->cstat = status;
		MachEmptyWriteBuffer();

#ifdef DEBUG
		sii_logp->target = target;
		sii_logp->cstat = status;
		sii_logp->dstat = 0;
		sii_logp->comm = regs->comm;
		sii_logp->msg = -1;
I 12
		sii_logp->rlen = state->buflen;
		sii_logp->dlen = state->dmalen;
E 12
		if (++sii_logp >= &sii_log[NLOG])
			sii_logp = sii_log;
#endif

		/* wait a short time for command phase */
		SII_WAIT_UNTIL(status, regs->dstat, status & SII_MIS,
			SII_WAIT_COUNT, retval);
#ifdef DEBUG
		if (sii_debug > 2)
			printf("sii_StartCmd: ds %x cnt %d\n", status, retval);
#endif
		if ((status & (SII_CI | SII_MIS | SII_PHASE_MSK)) !=
		    (SII_MIS | SII_CMD_PHASE)) {
			printf("sii_StartCmd: timeout cs %x ds %x cnt %d\n",
				regs->cstat, status, retval); /* XXX */
			/* process interrupt or continue until it happens */
			if (status & (SII_CI | SII_DI))
				sii_DoIntr(sc, status);
			return;
		}
		regs->dstat = SII_DNE;	/* clear Msg Out DMA done */

		/* send command data */
		CopyToBuffer((u_short *)state->cmd,
			(volatile u_short *)state->dmaAddr[0], state->cmdlen);
		sii_StartDMA(regs, state->dmaCurPhase = SII_CMD_PHASE,
			state->dmaAddr[0], state->dmalen = scsicmd->cmdlen);

		/* wait a little while for DMA to finish */
		SII_WAIT_UNTIL(status, regs->dstat, status & (SII_CI | SII_DI),
			SII_WAIT_COUNT, retval);
#ifdef DEBUG
		if (sii_debug > 2)
			printf("sii_StartCmd: ds %x, cnt %d\n", status, retval);
#endif
		if (status & (SII_CI | SII_DI))
			sii_DoIntr(sc, status);
#ifdef DEBUG
		if (sii_debug > 2)
			printf("sii_StartCmd: DONE ds %x\n", regs->dstat);
#endif
		return;
	}

	/*
	 * Another device may have selected us; in which case,
	 * this command will be restarted later.
	 */
	if (status & (SII_CI | SII_DI)) {
		sii_DoIntr(sc, regs->dstat);
		return;
	}

	/*
	 * Disconnect if selection command still in progress.
	 */
	if (status & SII_SIP) {
		error = ENXIO;	/* device didn't respond */
		regs->comm = SII_DISCON;
		MachEmptyWriteBuffer();
		SII_WAIT_UNTIL(status, regs->cstat,
			!(status & (SII_CON | SII_SIP)),
			SII_WAIT_COUNT, retval);
	} else
		error = EBUSY;	/* couldn't get the bus */
#ifdef DEBUG
D 4
	if (sii_debug > 0)
E 4
I 4
	if (sii_debug > 1)
E 4
		printf("sii_StartCmd: Couldn't select target %d error %d\n",
			target, error);
#endif
	sc->sc_target = -1;
	regs->cstat = 0xffff;
	regs->dstat = 0xffff;
	regs->comm = 0;
	MachEmptyWriteBuffer();
	sii_CmdDone(sc, target, error);
}

/*
 * Process interrupt conditions.
 */
static void
sii_DoIntr(sc, dstat)
	register struct siisoftc *sc;
D 12
	register unsigned dstat;
E 12
I 12
	register u_int dstat;
E 12
{
	register SIIRegs *regs = sc->sc_regs;
	register State *state;
D 12
	register unsigned cstat;
	register int i;
	unsigned comm, msg;
E 12
I 12
	register u_int cstat;
	int i, msg;
	u_int comm;
E 12

again:
	comm = regs->comm;

#ifdef DEBUG
	if (sii_debug > 3)
		printf("sii_DoIntr: cs %x, ds %x cm %x ",
			regs->cstat, dstat, comm);
	sii_logp->target = sc->sc_target;
	sii_logp->cstat = regs->cstat;
	sii_logp->dstat = dstat;
	sii_logp->comm = comm;
	sii_logp->msg = -1;
I 12
	if (sc->sc_target >= 0) {
		sii_logp->rlen = sc->sc_st[sc->sc_target].buflen;
		sii_logp->dlen = sc->sc_st[sc->sc_target].dmalen;
	} else {
		sii_logp->rlen = 0;
		sii_logp->dlen = 0;
	}
E 12
	if (++sii_logp >= &sii_log[NLOG])
		sii_logp = sii_log;
#endif

	regs->dstat = dstat;	/* acknowledge everything */
	MachEmptyWriteBuffer();

	if (dstat & SII_CI) {
		/* deglitch cstat register */
		msg = regs->cstat;
		while (msg != (cstat = regs->cstat))
			msg = cstat;
		regs->cstat = cstat;	/* acknowledge everything */
		MachEmptyWriteBuffer();
#ifdef DEBUG
		if (sii_logp > sii_log)
			sii_logp[-1].cstat = cstat;
		else
			sii_log[NLOG - 1].cstat = cstat;
#endif

		/* check for a BUS RESET */
		if (cstat & SII_RST) {
			printf("sii%d: SCSI bus reset!!\n", sc - sii_softc);
			/* need to flush disconnected commands */
D 2
			for (i = 0; i < SII_NCMD; i++)
E 2
I 2
			for (i = 0; i < SII_NCMD; i++) {
				if (!sc->sc_cmd[i])
					continue;
E 2
				sii_CmdDone(sc, i, EIO);
I 2
			}
E 2
			/* rearbitrate synchronous offset */
			for (i = 0; i < SII_NCMD; i++)
				sc->sc_st[i].dmaReqAck = 0;
			sc->sc_target = -1;
			return;
		}

#ifdef notdef
		/*
		 * Check for a BUS ERROR.
		 * According to DEC, this feature doesn't really work
		 * and to just clear the bit if it's set.
		 */
		if (cstat & SII_BER) {
		}
#endif

		/* check for state change */
		if (cstat & SII_SCH) {
			sii_StateChg(sc, cstat);
			comm = regs->comm;
		}
	}

	/* check for DMA completion */
	if (dstat & SII_DNE) {
		u_short *dma;
		char *buf;

D 12
		/* check for a PARITY ERROR */
		if (dstat & SII_IPE) {
			printf("sii%d: Parity error!!\n", sc - sii_softc);
			goto abort;
		}
E 12
		/*
		 * There is a race condition with SII_SCH. There is a short
		 * window between the time a SII_SCH is seen after a disconnect 
		 * and when the SII_SCH is cleared. A reselect can happen
		 * in this window and we will clear the SII_SCH without
		 * processing the reconnect.
		 */
		if (sc->sc_target < 0) {
			cstat = regs->cstat;
			printf("sii%d: target %d DNE?? dev %d,%d cs %x\n",
				sc - sii_softc, sc->sc_target,
				regs->slcsr, regs->destat,
				cstat); /* XXX */
			if (cstat & SII_DST) {
				sc->sc_target = regs->destat;
				state->prevComm = 0;
			} else
				panic("sc_target 1");
		}
		state = &sc->sc_st[sc->sc_target];
I 12
		/* check for a PARITY ERROR */
		if (dstat & SII_IPE) {
			state->flags |= PARITY_ERR;
			printf("sii%d: Parity error!!\n", sc - sii_softc);
			goto abort;
		}
E 12
		/* dmalen = amount left to transfer, i = amount transfered */
		i = state->dmalen;
		state->dmalen = 0;
		state->dmaCurPhase = -1;
#ifdef DEBUG
		if (sii_debug > 4) {
			printf("DNE: amt %d ", i);
			if (!(dstat & SII_TCZ))
				printf("no TCZ?? (%d) ", regs->dmlotc);
		} else if (!(dstat & SII_TCZ)) {
			printf("sii%d: device %d: no TCZ?? (%d)\n",
				sc - sii_softc, sc->sc_target, regs->dmlotc);
			sii_DumpLog(); /* XXX */
		}
#endif
		switch (comm & SII_PHASE_MSK) {
		case SII_CMD_PHASE:
			state->cmdlen -= i;
			break;

		case SII_DATA_IN_PHASE:
			/* check for more data for the same phase */
			dma = state->dmaAddr[state->dmaBufIndex];
			buf = state->buf;
			state->buf += i;
			state->buflen -= i;
			if (state->buflen > 0 && !(dstat & SII_MIS)) {
				int len;

				/* start reading next chunk */
				len = state->buflen;
				if (len > SII_MAX_DMA_XFER_LENGTH)
					len = SII_MAX_DMA_XFER_LENGTH;
				state->dmaBufIndex = !state->dmaBufIndex;
				sii_StartDMA(regs,
					state->dmaCurPhase = SII_DATA_IN_PHASE,
					state->dmaAddr[state->dmaBufIndex],
					state->dmalen = len);
				dstat &= ~(SII_IBF | SII_TBE);
			}
			/* copy in the data */
			CopyFromBuffer((volatile u_short *)dma, buf, i);
			break;

		case SII_DATA_OUT_PHASE:
			state->dmaBufIndex = !state->dmaBufIndex;
			state->buf += i;
			state->buflen -= i;

			/* check for more data for the same phase */
			if (state->buflen <= 0 || (dstat & SII_MIS))
				break;

			/* start next chunk */
			i = state->buflen;
			if (i > SII_MAX_DMA_XFER_LENGTH) {
				sii_StartDMA(regs, state->dmaCurPhase =
					SII_DATA_OUT_PHASE,
					state->dmaAddr[state->dmaBufIndex],
					state->dmalen =
					SII_MAX_DMA_XFER_LENGTH);
				/* prepare for next chunk */
				i -= SII_MAX_DMA_XFER_LENGTH;
				if (i > SII_MAX_DMA_XFER_LENGTH)
					i = SII_MAX_DMA_XFER_LENGTH;
				CopyToBuffer((u_short *)(state->buf +
					SII_MAX_DMA_XFER_LENGTH),
					(volatile u_short *)
					state->dmaAddr[!state->dmaBufIndex], i);
			} else {
				sii_StartDMA(regs, state->dmaCurPhase =
					SII_DATA_OUT_PHASE,
					state->dmaAddr[state->dmaBufIndex],
					state->dmalen = i);
			}
			dstat &= ~(SII_IBF | SII_TBE);
D 12
			break;

		default:
			printf("sii%d: device %d: unexpected DNE\n",
				sc - sii_softc, sc->sc_target);
#ifdef DEBUG
			sii_DumpLog();
#endif
E 12
		}
	}

	/* check for phase change or another MsgIn/Out */
	if (dstat & (SII_MIS | SII_IBF | SII_TBE)) {
		/*
		 * There is a race condition with SII_SCH. There is a short
		 * window between the time a SII_SCH is seen after a disconnect 
		 * and when the SII_SCH is cleared. A reselect can happen
		 * in this window and we will clear the SII_SCH without
		 * processing the reconnect.
		 */
		if (sc->sc_target < 0) {
			cstat = regs->cstat;
			printf("sii%d: target %d MIS?? dev %d,%d cs %x ds %x\n",
				sc - sii_softc, sc->sc_target,
				regs->slcsr, regs->destat,
				cstat, dstat); /* XXX */
			if (cstat & SII_DST) {
				sc->sc_target = regs->destat;
				state->prevComm = 0;
D 12
			} else
E 12
I 12
			} else {
I 13
#ifdef DEBUG
E 13
				sii_DumpLog();
I 13
#endif
E 13
E 12
				panic("sc_target 2");
I 12
			}
E 12
		}
		state = &sc->sc_st[sc->sc_target];
		switch (dstat & SII_PHASE_MSK) {
		case SII_CMD_PHASE:
			if (state->dmaPrevPhase >= 0) {
				/* restart DMA after disconnect/reconnect */
				if (state->dmaPrevPhase != SII_CMD_PHASE) {
					printf("sii%d: device %d: dma reselect phase doesn't match\n",
						sc - sii_softc, sc->sc_target);
					goto abort;
				}
				state->dmaCurPhase = SII_CMD_PHASE;
				state->dmaPrevPhase = -1;
				regs->dmaddrl = state->dmaAddrL;
				regs->dmaddrh = state->dmaAddrH;
				regs->dmlotc = state->dmaCnt;
				if (state->dmaCnt & 1)
					regs->dmabyte = state->dmaByte;
				regs->comm = SII_DMA | SII_INXFER |
					(comm & SII_STATE_MSK) | SII_CMD_PHASE;
				MachEmptyWriteBuffer();
#ifdef DEBUG
				if (sii_debug > 4)
					printf("Cmd dcnt %d dadr %x ",
						state->dmaCnt,
						(state->dmaAddrH << 16) |
							state->dmaAddrL);
#endif
			} else {
				/* send command data */
				i = state->cmdlen;
				if (i == 0) {
					printf("sii%d: device %d: cmd count exceeded\n",
						sc - sii_softc, sc->sc_target);
					goto abort;
				}
				CopyToBuffer((u_short *)state->cmd,
					(volatile u_short *)state->dmaAddr[0],
					i);
				sii_StartDMA(regs, state->dmaCurPhase =
					SII_CMD_PHASE, state->dmaAddr[0],
					state->dmalen = i);
			}
			/* wait a short time for XFER complete */
			SII_WAIT_UNTIL(dstat, regs->dstat,
				dstat & (SII_CI | SII_DI), SII_WAIT_COUNT, i);
			if (dstat & (SII_CI | SII_DI)) {
#ifdef DEBUG
				if (sii_debug > 4)
					printf("cnt %d\n", i);
				else if (sii_debug > 0)
					printf("sii_DoIntr: cmd wait ds %x cnt %d\n",
						dstat, i);
#endif
				goto again;
			}
			break;

		case SII_DATA_IN_PHASE:
		case SII_DATA_OUT_PHASE:
D 12
			regs->dmctrl = state->dmaReqAck;
E 12
			if (state->cmdlen > 0) {
				printf("sii%d: device %d: cmd %x: command data not all sent (%d) 1\n",
					sc - sii_softc, sc->sc_target,
					sc->sc_cmd[sc->sc_target]->cmd[0],
					state->cmdlen);
				state->cmdlen = 0;
#ifdef DEBUG
				sii_DumpLog();
#endif
			}
			if (state->dmaPrevPhase >= 0) {
				/* restart DMA after disconnect/reconnect */
				if (state->dmaPrevPhase !=
				    (dstat & SII_PHASE_MSK)) {
					printf("sii%d: device %d: dma reselect phase doesn't match\n",
						sc - sii_softc, sc->sc_target);
					goto abort;
				}
				state->dmaCurPhase = state->dmaPrevPhase;
				state->dmaPrevPhase = -1;
				regs->dmaddrl = state->dmaAddrL;
				regs->dmaddrh = state->dmaAddrH;
				regs->dmlotc = state->dmaCnt;
				if (state->dmaCnt & 1)
					regs->dmabyte = state->dmaByte;
				regs->comm = SII_DMA | SII_INXFER |
					(comm & SII_STATE_MSK) |
					state->dmaCurPhase;
				MachEmptyWriteBuffer();
#ifdef DEBUG
				if (sii_debug > 4)
					printf("Data %d dcnt %d dadr %x ",
						state->dmaDataPhase,
						state->dmaCnt,
						(state->dmaAddrH << 16) |
							state->dmaAddrL);
#endif
				break;
			}
			if (state->dmaDataPhase != (dstat & SII_PHASE_MSK)) {
				printf("sii%d: device %d: cmd %x: dma phase doesn't match\n",
					sc - sii_softc, sc->sc_target,
					sc->sc_cmd[sc->sc_target]->cmd[0]);
				goto abort;
			}
#ifdef DEBUG
			if (sii_debug > 4) {
				printf("Data %d ", state->dmaDataPhase);
				if (sii_debug > 5)
					printf("\n");
			}
#endif
			i = state->buflen;
			if (i == 0) {
				printf("sii%d: device %d: data count exceeded\n",
					sc - sii_softc, sc->sc_target);
				goto abort;
			}
			if (i > SII_MAX_DMA_XFER_LENGTH)
				i = SII_MAX_DMA_XFER_LENGTH;
			if ((dstat & SII_PHASE_MSK) == SII_DATA_IN_PHASE) {
				sii_StartDMA(regs,
					state->dmaCurPhase = SII_DATA_IN_PHASE,
					state->dmaAddr[state->dmaBufIndex],
					state->dmalen = i);
				break;
			}
			/* start first chunk */
			if (state->flags & FIRST_DMA) {
				state->flags &= ~FIRST_DMA;
				CopyToBuffer((u_short *)state->buf,
					(volatile u_short *)
					state->dmaAddr[state->dmaBufIndex], i);
			}
			sii_StartDMA(regs,
				state->dmaCurPhase = SII_DATA_OUT_PHASE,
				state->dmaAddr[state->dmaBufIndex],
				state->dmalen = i);
			i = state->buflen - SII_MAX_DMA_XFER_LENGTH;
			if (i > 0) {
				/* prepare for next chunk */
				if (i > SII_MAX_DMA_XFER_LENGTH)
					i = SII_MAX_DMA_XFER_LENGTH;
				CopyToBuffer((u_short *)(state->buf +
					SII_MAX_DMA_XFER_LENGTH),
					(volatile u_short *)
					state->dmaAddr[!state->dmaBufIndex], i);
			}
			break;

		case SII_STATUS_PHASE:
			if (state->cmdlen > 0) {
				printf("sii%d: device %d: cmd %x: command data not all sent (%d) 2\n",
					sc - sii_softc, sc->sc_target,
					sc->sc_cmd[sc->sc_target]->cmd[0],
					state->cmdlen);
				state->cmdlen = 0;
#ifdef DEBUG
				sii_DumpLog();
#endif
			}

			/* read amount transfered if DMA didn't finish */
			if (state->dmalen > 0) {
				i = state->dmalen - regs->dmlotc;
				state->dmalen = 0;
				state->dmaCurPhase = -1;
				regs->dmlotc = 0;
				regs->comm = comm &
					(SII_STATE_MSK | SII_PHASE_MSK);
				MachEmptyWriteBuffer();
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
#ifdef DEBUG
				if (sii_debug > 4)
					printf("DMA amt %d ", i);
#endif
				switch (comm & SII_PHASE_MSK) {
				case SII_DATA_IN_PHASE:
					/* copy in the data */
					CopyFromBuffer((volatile u_short *)
					    state->dmaAddr[state->dmaBufIndex],
					    state->buf, i);

				case SII_CMD_PHASE:
				case SII_DATA_OUT_PHASE:
					state->buflen -= i;
				}
			}

			/* read a one byte status message */
			state->statusByte = msg =
D 12
				sii_GetByte(regs, SII_STATUS_PHASE);
E 12
I 12
				sii_GetByte(regs, SII_STATUS_PHASE, 1);
E 12
			if (msg < 0) {
				dstat = regs->dstat;
				goto again;
			}
#ifdef DEBUG
			if (sii_debug > 4)
				printf("Status %x ", msg);
			if (sii_logp > sii_log)
				sii_logp[-1].msg = msg;
			else
				sii_log[NLOG - 1].msg = msg;
#endif

			/* do a quick wait for COMMAND_COMPLETE */
			SII_WAIT_UNTIL(dstat, regs->dstat,
				dstat & (SII_CI | SII_DI), SII_WAIT_COUNT, i);
			if (dstat & (SII_CI | SII_DI)) {
#ifdef DEBUG
				if (sii_debug > 4)
					printf("cnt2 %d\n", i);
#endif
				goto again;
			}
			break;

		case SII_MSG_IN_PHASE:
			/*
			 * Save DMA state if DMA didn't finish.
			 * Be careful not to save state again after reconnect
			 * and see RESTORE_POINTER message.
			 * Note that the SII DMA address is not incremented
			 * as DMA proceeds.
			 */
			if (state->dmaCurPhase > 0) {
				/* save dma registers */
				state->dmaPrevPhase = state->dmaCurPhase;
				state->dmaCurPhase = -1;
				state->dmaCnt = i = regs->dmlotc;
				if (dstat & SII_OBB)
					state->dmaByte = regs->dmabyte;
				if (i == 0)
					i = SII_MAX_DMA_XFER_LENGTH;
				i = state->dmalen - i;
				/* note: no carry from dmaddrl to dmaddrh */
				state->dmaAddrL = regs->dmaddrl + i;
				state->dmaAddrH = regs->dmaddrh;
				regs->comm = comm &
					(SII_STATE_MSK | SII_PHASE_MSK);
				MachEmptyWriteBuffer();
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
#ifdef DEBUG
				if (sii_debug > 4) {
					printf("SavP dcnt %d dadr %x ",
						state->dmaCnt,
						(state->dmaAddrH << 16) |
						state->dmaAddrL);
					if (((dstat & SII_OBB) != 0) ^
					    (state->dmaCnt & 1))
						printf("OBB??? ");
				} else if (sii_debug > 0) {
					if (((dstat & SII_OBB) != 0) ^
					    (state->dmaCnt & 1)) {
						printf("sii_DoIntr: OBB??? ds %x cnt %d\n",
							dstat, state->dmaCnt);
						sii_DumpLog();
					}
				}
#endif
			}

			/* read a one byte message */
D 12
			msg = sii_GetByte(regs, SII_MSG_IN_PHASE);
E 12
I 12
			msg = sii_GetByte(regs, SII_MSG_IN_PHASE, 0);
E 12
			if (msg < 0) {
				dstat = regs->dstat;
				goto again;
			}
#ifdef DEBUG
			if (sii_debug > 4)
				printf("MsgIn %x ", msg);
			if (sii_logp > sii_log)
				sii_logp[-1].msg = msg;
			else
				sii_log[NLOG - 1].msg = msg;
#endif

			/* process message */
			switch (msg) {
			case SCSI_COMMAND_COMPLETE:
I 12
				/* acknowledge last byte */
				regs->comm = SII_INXFER | SII_MSG_IN_PHASE |
					(comm & SII_STATE_MSK);
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & SII_DNE, SII_WAIT_COUNT, i);
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
E 12
				msg = sc->sc_target;
				sc->sc_target = -1;
				/*
				 * Wait a short time for disconnect.
				 * Don't be fooled if SII_BER happens first.
				 * Note: a reselect may happen here.
				 */
				SII_WAIT_UNTIL(cstat, regs->cstat,
					cstat & (SII_RST | SII_SCH),
					SII_WAIT_COUNT, i);
				if ((cstat & (SII_RST | SII_SCH |
				    SII_STATE_MSK)) == SII_SCH) {
					regs->cstat = SII_SCH | SII_BER;
					regs->comm = 0;
					MachEmptyWriteBuffer();
					/*
					 * Double check that we didn't miss a
					 * state change between seeing it and
					 * clearing the SII_SCH bit.
					 */
					i = regs->cstat;
					if (!(i & SII_SCH) &&
					    (i & SII_STATE_MSK) !=
					    (cstat & SII_STATE_MSK))
						sii_StateChg(sc, i);
				}
#ifdef DEBUG
				if (sii_debug > 4)
					printf("cs %x\n", cstat);
#endif
				sii_CmdDone(sc, msg, 0);
				break;

			case SCSI_EXTENDED_MSG:
I 12
				/* acknowledge last byte */
				regs->comm = SII_INXFER | SII_MSG_IN_PHASE |
					(comm & SII_STATE_MSK);
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & SII_DNE, SII_WAIT_COUNT, i);
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
E 12
				/* read the message length */
D 12
				msg = sii_GetByte(regs, SII_MSG_IN_PHASE);
E 12
I 12
				msg = sii_GetByte(regs, SII_MSG_IN_PHASE, 1);
E 12
				if (msg < 0) {
					dstat = regs->dstat;
					goto again;
				}
I 12
				sii_buf[1] = msg;	/* message length */
E 12
				if (msg == 0)
					msg = 256;
D 12
				sii_StartDMA(regs, SII_MSG_IN_PHASE,
					(u_short *)SII_BUF_ADDR, msg);
				/* wait a short time for XFER complete */
				SII_WAIT_UNTIL(dstat, regs->dstat,
					(dstat & (SII_DNE | SII_TCZ)) ==
					(SII_DNE | SII_TCZ),
					SII_WAIT_COUNT, i);

				if ((dstat & (SII_DNE | SII_TCZ | SII_IPE)) !=
				    (SII_DNE | SII_TCZ)) {
#ifdef DEBUG
					if (sii_debug > 4)
						printf("cnt0 %d\n", i);
					else if (sii_debug > 0)
						printf("sii_DoIntr: emsg in ds %x cnt %d\n",
							dstat, i);
#endif
					printf("sii: ds %x cm %x i %d lotc %d\n",
						dstat, comm, i, regs->dmlotc); /* XXX */
					sii_DumpLog(); /* XXX */
					goto again;
E 12
I 12
				/*
				 * We read and acknowlege all the bytes
				 * except the last so we can assert ATN
				 * if needed before acknowledging the last.
				 */
				for (i = 0; i < msg; i++) {
					dstat = sii_GetByte(regs,
						SII_MSG_IN_PHASE, i < msg - 1);
					if ((int)dstat < 0) {
						dstat = regs->dstat;
						goto again;
					}
					sii_buf[i + 2] = dstat;
E 12
				}

D 12
				/* clear the DNE, other errors handled later */
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();

				CopyFromBuffer((volatile u_short *)SII_BUF_ADDR,
					sii_buf + 2, msg);
E 12
				switch (sii_buf[2]) {
				case SCSI_MODIFY_DATA_PTR:
I 12
					/* acknowledge last byte */
					regs->comm = SII_INXFER |
						SII_MSG_IN_PHASE |
						(comm & SII_STATE_MSK);
					SII_WAIT_UNTIL(dstat, regs->dstat,
						dstat & SII_DNE,
						SII_WAIT_COUNT, i);
					regs->dstat = SII_DNE;
					MachEmptyWriteBuffer();
E 12
					i = (sii_buf[3] << 24) |
						(sii_buf[4] << 16) |
						(sii_buf[5] << 8) |
						sii_buf[6];
					if (state->dmaPrevPhase >= 0) {
						state->dmaAddrL += i;
						state->dmaCnt -= i;
					}
					break;

				case SCSI_SYNCHRONOUS_XFER:
I 12
					/*
					 * Acknowledge last byte and
					 * signal a request for MSG_OUT.
					 */
					regs->comm = SII_INXFER | SII_ATN |
						SII_MSG_IN_PHASE |
						(comm & SII_STATE_MSK);
					SII_WAIT_UNTIL(dstat, regs->dstat,
						dstat & SII_DNE,
						SII_WAIT_COUNT, i);
					regs->dstat = SII_DNE;
					MachEmptyWriteBuffer();
E 12
					sii_DoSync(regs, state);
					break;

D 12
				case SCSI_EXTENDED_IDENTIFY:
				case SCSI_WIDE_XFER:
E 12
				default:
				reject:
I 12
					/*
					 * Acknowledge last byte and
					 * signal a request for MSG_OUT.
					 */
					regs->comm = SII_INXFER | SII_ATN |
						SII_MSG_IN_PHASE |
						(comm & SII_STATE_MSK);
					SII_WAIT_UNTIL(dstat, regs->dstat,
						dstat & SII_DNE,
						SII_WAIT_COUNT, i);
					regs->dstat = SII_DNE;
					MachEmptyWriteBuffer();

					/* wait for MSG_OUT phase */
					SII_WAIT_UNTIL(dstat, regs->dstat,
						dstat & SII_TBE,
						SII_WAIT_COUNT, i);

E 12
					/* send a reject message */
					regs->data = SCSI_MESSAGE_REJECT;
D 12
					regs->comm = SII_INXFER | SII_ATN |
E 12
I 12
					regs->comm = SII_INXFER |
E 12
						(regs->cstat & SII_STATE_MSK) |
						SII_MSG_OUT_PHASE;
D 12
					MachEmptyWriteBuffer();
					/* wait for XFER complete */
E 12
					SII_WAIT_UNTIL(dstat, regs->dstat,
D 12
						(dstat &
						(SII_DNE | SII_PHASE_MSK)) ==
						(SII_DNE | SII_MSG_OUT_PHASE),
E 12
I 12
						dstat & SII_DNE,
E 12
						SII_WAIT_COUNT, i);
D 12

					if ((dstat &
					    (SII_DNE | SII_PHASE_MSK)) !=
					    (SII_DNE | SII_MSG_OUT_PHASE))
						break;
E 12
					regs->dstat = SII_DNE;
					MachEmptyWriteBuffer();
				}
				break;

			case SCSI_SAVE_DATA_POINTER:
			case SCSI_RESTORE_POINTERS:
I 12
				/* acknowledge last byte */
				regs->comm = SII_INXFER | SII_MSG_IN_PHASE |
					(comm & SII_STATE_MSK);
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & SII_DNE, SII_WAIT_COUNT, i);
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
E 12
				/* wait a short time for another msg */
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & (SII_CI | SII_DI),
					SII_WAIT_COUNT, i);
				if (dstat & (SII_CI | SII_DI)) {
#ifdef DEBUG
					if (sii_debug > 4)
						printf("cnt %d\n", i);
#endif
					goto again;
				}
				break;

			case SCSI_DISCONNECT:
I 12
				/* acknowledge last byte */
				regs->comm = SII_INXFER | SII_MSG_IN_PHASE |
					(comm & SII_STATE_MSK);
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & SII_DNE, SII_WAIT_COUNT, i);
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
E 12
				state->prevComm = comm;
#ifdef DEBUG
				if (sii_debug > 4)
					printf("disconn %d ", sc->sc_target);
#endif
				/*
				 * Wait a short time for disconnect.
				 * Don't be fooled if SII_BER happens first.
				 * Note: a reselect may happen here.
				 */
				SII_WAIT_UNTIL(cstat, regs->cstat,
					cstat & (SII_RST | SII_SCH),
					SII_WAIT_COUNT, i);
				if ((cstat & (SII_RST | SII_SCH |
				    SII_STATE_MSK)) != SII_SCH) {
#ifdef DEBUG
					if (sii_debug > 4)
						printf("cnt %d\n", i);
#endif
					dstat = regs->dstat;
					goto again;
				}
				regs->cstat = SII_SCH | SII_BER;
				regs->comm = 0;
				MachEmptyWriteBuffer();
				sc->sc_target = -1;
				/*
				 * Double check that we didn't miss a state
				 * change between seeing it and clearing
				 * the SII_SCH bit.
				 */
				i = regs->cstat;
				if (!(i & SII_SCH) && (i & SII_STATE_MSK) !=
				    (cstat & SII_STATE_MSK))
					sii_StateChg(sc, i);
				break;

			case SCSI_MESSAGE_REJECT:
I 12
				/* acknowledge last byte */
				regs->comm = SII_INXFER | SII_MSG_IN_PHASE |
					(comm & SII_STATE_MSK);
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & SII_DNE, SII_WAIT_COUNT, i);
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
E 12
				printf("sii%d: device %d: message reject.\n",
					sc - sii_softc, sc->sc_target);
D 12
				goto abort;
E 12
I 12
				break;
E 12

			default:
				if (!(msg & SCSI_IDENTIFY)) {
D 12
					printf("sii%d: device %d: couldn't handle message 0x%x... ignoring.\n",
E 12
I 12
					printf("sii%d: device %d: couldn't handle message 0x%x... rejecting.\n",
E 12
						sc - sii_softc, sc->sc_target,
						msg);
#ifdef DEBUG
					sii_DumpLog();
#endif
D 12
					break;
E 12
I 12
					goto reject;
E 12
				}
I 12
				/* acknowledge last byte */
				regs->comm = SII_INXFER | SII_MSG_IN_PHASE |
					(comm & SII_STATE_MSK);
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & SII_DNE, SII_WAIT_COUNT, i);
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
E 12
				/* may want to check LUN some day */
				/* wait a short time for another msg */
				SII_WAIT_UNTIL(dstat, regs->dstat,
					dstat & (SII_CI | SII_DI),
					SII_WAIT_COUNT, i);
				if (dstat & (SII_CI | SII_DI)) {
#ifdef DEBUG
					if (sii_debug > 4)
						printf("cnt %d\n", i);
#endif
					goto again;
				}
			}
			break;

		case SII_MSG_OUT_PHASE:
#ifdef DEBUG
			if (sii_debug > 4)
				printf("MsgOut\n");
#endif
I 12
			printf("MsgOut %x\n", state->flags); /* XXX */
E 12

D 12
			regs->data = SCSI_NO_OP;
E 12
I 12
			/*
			 * Check for parity error.
			 * Hardware will automatically set ATN
			 * to request the device for a MSG_OUT phase.
			 */
			if (state->flags & PARITY_ERR) {
				state->flags &= ~PARITY_ERR;
				regs->data = SCSI_MESSAGE_PARITY_ERROR;
			} else
				regs->data = SCSI_NO_OP;
E 12
			regs->comm = SII_INXFER | (comm & SII_STATE_MSK) |
				SII_MSG_OUT_PHASE;
			MachEmptyWriteBuffer();

			/* wait a short time for XFER complete */
			SII_WAIT_UNTIL(dstat, regs->dstat, dstat & SII_DNE,
				SII_WAIT_COUNT, i);
#ifdef DEBUG
			if (sii_debug > 4)
				printf("ds %x i %d\n", dstat, i);
#endif
			/* just clear the DNE bit and check errors later */
			if (dstat & SII_DNE) {
				regs->dstat = SII_DNE;
				MachEmptyWriteBuffer();
			}
			break;

		default:
			printf("sii%d: Couldn't handle phase %d... ignoring.\n",
				   sc - sii_softc, dstat & SII_PHASE_MSK);
		}
	}

#ifdef DEBUG
	if (sii_debug > 3)
		printf("\n");
#endif
	/*
	 * Check to make sure we won't be interrupted again.
	 * Deglitch dstat register.
	 */
	msg = regs->dstat;
	while (msg != (dstat = regs->dstat))
		msg = dstat;
	if (dstat & (SII_CI | SII_DI))
		goto again;

	if (sc->sc_target < 0) {
		/* look for another device that is ready */
		for (i = 0; i < SII_NCMD; i++) {
			/* don't restart a disconnected command */
			if (!sc->sc_cmd[i] || sc->sc_st[i].prevComm)
				continue;
			sii_StartCmd(sc, i);
			break;
		}
	}
	return;

abort:
	/* jump here to abort the current command */
	printf("sii%d: device %d: current command terminated\n",
		sc - sii_softc, sc->sc_target);
#ifdef DEBUG
	sii_DumpLog();
#endif

	if ((cstat = regs->cstat) & SII_CON) {
		/* try to send an abort msg for awhile */
		regs->dstat = SII_DNE;
		regs->data = SCSI_ABORT;
		regs->comm = SII_INXFER | SII_ATN | (cstat & SII_STATE_MSK) |
			SII_MSG_OUT_PHASE;
		MachEmptyWriteBuffer();
		SII_WAIT_UNTIL(dstat, regs->dstat,
			(dstat & (SII_DNE | SII_PHASE_MSK)) ==
			(SII_DNE | SII_MSG_OUT_PHASE),
			2 * SII_WAIT_COUNT, i);
#ifdef DEBUG
		if (sii_debug > 0)
			printf("Abort: cs %x ds %x i %d\n", cstat, dstat, i);
#endif
		if (dstat & (SII_DNE | SII_PHASE_MSK) ==
		    (SII_DNE | SII_MSG_OUT_PHASE)) {
			/* disconnect if command in progress */
			regs->comm = SII_DISCON;
			MachEmptyWriteBuffer();
			SII_WAIT_UNTIL(cstat, regs->cstat,
				!(cstat & SII_CON), SII_WAIT_COUNT, i);
		}
	} else {
#ifdef DEBUG
		if (sii_debug > 0)
			printf("Abort: cs %x\n", cstat);
#endif
	}
	regs->cstat = 0xffff;
	regs->dstat = 0xffff;
	regs->comm = 0;
	MachEmptyWriteBuffer();

	i = sc->sc_target;
	sc->sc_target = -1;
	sii_CmdDone(sc, i, EIO);
#ifdef DEBUG
	if (sii_debug > 4)
		printf("sii_DoIntr: after CmdDone target %d\n", sc->sc_target);
#endif
}

static void
sii_StateChg(sc, cstat)
	register struct siisoftc *sc;
D 12
	register unsigned cstat;
E 12
I 12
	register u_int cstat;
E 12
{
	register SIIRegs *regs = sc->sc_regs;
	register State *state;
	register int i;

#ifdef DEBUG
	if (sii_debug > 4)
		printf("SCH: ");
#endif

	switch (cstat & SII_STATE_MSK) {
	case 0:
		/* disconnect */
		i = sc->sc_target;
		sc->sc_target = -1;
#ifdef DEBUG
		if (sii_debug > 4)
			printf("disconn %d ", i);
#endif
		if (i >= 0 && !sc->sc_st[i].prevComm) {
			printf("sii%d: device %d: spurrious disconnect (%d)\n",
				sc - sii_softc, i, regs->slcsr);
			sc->sc_st[i].prevComm = 0;
		}
		break;

	case SII_CON:
		/* connected as initiator */
		i = regs->slcsr;
		if (sc->sc_target == i)
			break;
		printf("sii%d: device %d: connect to device %d??\n",
			sc - sii_softc, sc->sc_target, i);
		sc->sc_target = i;
		break;

	case SII_DST:
		/*
		 * Wait for CON to become valid,
		 * chip is slow sometimes.
		 */
		SII_WAIT_UNTIL(cstat, regs->cstat,
			cstat & SII_CON, SII_WAIT_COUNT, i);
		if (!(cstat & SII_CON))
			panic("sii resel");
		/* FALLTHROUGH */

	case SII_CON | SII_DST:
		/*
		 * Its a reselection. Save the ID and wait for
		 * interrupts to tell us what to do next
		 * (should be MSG_IN of IDENTIFY).
		 * NOTE: sc_target may be >= 0 if we were in
		 * the process of trying to start a command
		 * and were reselected before the select
		 * command finished.
		 */
		sc->sc_target = i = regs->destat;
I 12
		state = &sc->sc_st[i];
E 12
		regs->comm = SII_CON | SII_DST | SII_MSG_IN_PHASE;
I 12
		regs->dmctrl = state->dmaReqAck;
E 12
		MachEmptyWriteBuffer();
D 12
		state = &sc->sc_st[i];
E 12
		if (!state->prevComm) {
			printf("sii%d: device %d: spurrious reselection\n",
				sc - sii_softc, i);
			break;
		}
		state->prevComm = 0;
#ifdef DEBUG
		if (sii_debug > 4)
			printf("resel %d ", sc->sc_target);
#endif
		break;

#ifdef notyet
	case SII_DST | SII_TGT:
	case SII_CON | SII_DST | SII_TGT:
		/* connected as target */
		printf("sii%d: Selected by device %d as target!!\n",
			sc - sii_softc, regs->destat);
		regs->comm = SII_DISCON;
		MachEmptyWriteBuffer();
		SII_WAIT_UNTIL(!(regs->cstat & SII_CON),
			SII_WAIT_COUNT, i);
		regs->cstat = 0xffff;
		regs->dstat = 0xffff;
		regs->comm = 0;
		break;
#endif

	default:
		printf("sii%d: Unknown state change (cs %x)!!\n",
			sc - sii_softc, cstat);
#ifdef DEBUG
		sii_DumpLog();
#endif
	}
}

/*
 * Read one byte of data.
I 12
 * If 'ack' is true, acknowledge the byte.
E 12
 */
static int
D 12
sii_GetByte(regs, phase)
E 12
I 12
sii_GetByte(regs, phase, ack)
E 12
	register SIIRegs *regs;
D 12
	int phase;
E 12
I 12
	int phase, ack;
E 12
{
D 12
	register unsigned dstat;
	register unsigned state;
#ifdef PROGXFER
	register unsigned data;
E 12
I 12
	register u_int dstat;
	register u_int state;
	register int i;
	register int data;
E 12

	dstat = regs->dstat;
	state = regs->cstat & SII_STATE_MSK;
D 12
	regs->dmctrl = 0;
E 12
	if (!(dstat & SII_IBF) || (dstat & SII_MIS)) {
		regs->comm = state | phase;
		MachEmptyWriteBuffer();
		/* wait a short time for IBF */
		SII_WAIT_UNTIL(dstat, regs->dstat, dstat & SII_IBF,
			SII_WAIT_COUNT, i);
#ifdef DEBUG
		if (!(dstat & SII_IBF))
			printf("status no IBF\n");
#endif
	}
D 12
	data = regs->data;
	if (regs->dstat & SII_DNE) { /* XXX */
E 12
I 12
	if (dstat & SII_DNE) { /* XXX */
E 12
		printf("sii_GetByte: DNE set 5\n");
I 13
#ifdef DEBUG
E 13
		sii_DumpLog();
I 13
#endif
E 13
		regs->dstat = SII_DNE;
	}
D 12
	regs->comm = SII_INXFER | state | phase;
	MachEmptyWriteBuffer();

	/* wait a short time for XFER complete */
	SII_WAIT_UNTIL(dstat, regs->dstat, dstat & SII_DNE,
		SII_WAIT_COUNT, i);

	if ((dstat & (SII_DNE | SII_IPE)) != SII_DNE) {
E 12
I 12
	data = regs->data;
	/* check for parity error */
	if (dstat & SII_IPE) {
E 12
#ifdef DEBUG
		if (sii_debug > 4)
			printf("cnt0 %d\n", i);
#endif
D 12
		printf("MsgIn %x ?? ds %x cm %x i %d\n",
			data, dstat, comm, i); /* XXX */
		sii_DumpLog(); /* XXX */
		panic("status"); /* XXX */
		goto again;
E 12
I 12
		printf("sii_GetByte: data %x ?? ds %x cm %x i %d\n",
			data, dstat, regs->comm, i); /* XXX */
		data = -1;
		ack = 1;
E 12
	}

D 12
	/* clear the DNE, other errors handled later */
	regs->dstat = SII_DNE;
	MachEmptyWriteBuffer();
	return (data);
E 12
I 12
	if (ack) {
		regs->comm = SII_INXFER | state | phase;
		MachEmptyWriteBuffer();
E 12

D 12
#else /* PROGXFER */
	register int i;
E 12
I 12
		/* wait a short time for XFER complete */
		SII_WAIT_UNTIL(dstat, regs->dstat, dstat & SII_DNE,
			SII_WAIT_COUNT, i);
E 12

D 12
	state = regs->cstat & SII_STATE_MSK;
	regs->dmctrl = 0;
	if (regs->dstat & SII_DNE) {
		printf("sii_GetByte: DNE cs %x ds %x cm %x\n",
			regs->cstat, regs->dstat, regs->comm); /* XXX */
		regs->dstat = SII_DNE;
E 12
I 12
		/* clear the DNE */
		if (dstat & SII_DNE) {
			regs->dstat = SII_DNE;
			MachEmptyWriteBuffer();
		}
E 12
	}
D 11
	regs->dmaddrl = ((unsigned)SII_BUF_ADDR >> 1);
	regs->dmaddrh = ((unsigned)SII_BUF_ADDR >> 17) & 03;
E 11
I 11
D 12
	regs->dmaddrl = ((u_short)SII_BUF_ADDR >> 1);
	regs->dmaddrh = ((u_short)SII_BUF_ADDR >> 17) & 03;
E 11
	regs->dmlotc = 1;
	regs->comm = SII_DMA | SII_INXFER | state | phase;
	MachEmptyWriteBuffer();
E 12

D 12
	/* wait a short time for XFER complete */
	SII_WAIT_UNTIL(dstat, regs->dstat,
		(dstat & (SII_DNE | SII_TCZ)) == (SII_DNE | SII_TCZ),
		SII_WAIT_COUNT, i);

	if ((dstat & (SII_DNE | SII_TCZ | SII_IPE)) != (SII_DNE | SII_TCZ)) {
D 9
		printf("sii_GetByte: ds %x cm %x i %d lotc %d\n",
			dstat, regs->comm, i, regs->dmlotc); /* XXX */
E 9
I 9
		printf("sii_GetByte: cs %x ds %x cm %x i %d lotc %d\n",
			regs->cstat, dstat, regs->comm, i,
			regs->dmlotc); /* XXX */
E 9
		sii_DumpLog(); /* XXX */
		return (-1);
	}

	/* clear the DNE, other errors handled later */
	regs->dstat = SII_DNE;
	MachEmptyWriteBuffer();

	/* return one byte of data (optimized CopyFromBuffer()) */
	return (*(volatile u_short *)SII_BUF_ADDR & 0xFF);
#endif /* PROGXFER */
E 12
I 12
	return (data);
E 12
}

/*
 * Exchange messages to initiate synchronous data transfers.
 */
static void
sii_DoSync(regs, state)
	register SIIRegs *regs;
	register State *state;
{
D 12
	register unsigned dstat;
	register int i;
	unsigned len;
E 12
I 12
	register u_int dstat, comm;
	register int i, j;
	u_int len;
E 12

D 12
	printf("sii_DoSync: per %d req/ack %d\n",
		sii_buf[3], sii_buf[4]); /* XXX */
E 12
I 12
#ifdef DEBUG
	if (sii_debug)
		printf("sii_DoSync: len %d per %d req/ack %d\n",
			sii_buf[1], sii_buf[3], sii_buf[4]);
#endif

	/* SII chip can only handle a minimum transfer period of ??? */
	if (sii_buf[3] < 64)
		sii_buf[3] = 64;
	/* SII chip can only handle a maximum REQ/ACK offset of 3 */
E 12
	len = sii_buf[4];
	if (len > 3)
D 12
		len = 3;	/* SII chip can only handle 3 max */
E 12
I 12
		len = 3;
E 12

	sii_buf[0] = SCSI_EXTENDED_MSG;
	sii_buf[1] = 3;		/* message length */
	sii_buf[2] = SCSI_SYNCHRONOUS_XFER;
	sii_buf[4] = len;
I 12
#if 1
	comm = SII_INXFER | SII_ATN | SII_MSG_OUT_PHASE |
		(regs->cstat & SII_STATE_MSK);
	regs->comm = comm & ~SII_INXFER;
	for (j = 0; j < 5; j++) {
		/* wait for target to request the next byte */
		SII_WAIT_UNTIL(dstat, regs->dstat, dstat & SII_TBE,
			SII_WAIT_COUNT, i);
		if (!(dstat & SII_TBE) ||
		    (dstat & SII_PHASE_MSK) != SII_MSG_OUT_PHASE) {
			printf("sii_DoSync: TBE? ds %x cm %x i %d\n",
				dstat, comm, i); /* XXX */
			return;
		}

		/* the last message byte should have ATN off */
		if (j == 4)
			comm &= ~SII_ATN;

		regs->data = sii_buf[j];
		regs->comm = comm;
		MachEmptyWriteBuffer();

		/* wait a short time for XFER complete */
		SII_WAIT_UNTIL(dstat, regs->dstat, dstat & SII_DNE,
			SII_WAIT_COUNT, i);

		if (!(dstat & SII_DNE)) {
			printf("sii_DoSync: DNE? ds %x cm %x i %d\n",
				dstat, comm, i); /* XXX */
			return;
		}

		/* clear the DNE, other errors handled later */
		regs->dstat = SII_DNE;
		MachEmptyWriteBuffer();
	}
#else
E 12
	CopyToBuffer((u_short *)sii_buf, (volatile u_short *)SII_BUF_ADDR, 5);
D 11
	regs->dmaddrl = ((unsigned)SII_BUF_ADDR >> 1);
	regs->dmaddrh = ((unsigned)SII_BUF_ADDR >> 17) & 03;
E 11
I 11
D 12
	regs->dmaddrl = ((u_short)SII_BUF_ADDR >> 1);
	regs->dmaddrh = ((u_short)SII_BUF_ADDR >> 17) & 03;
E 12
I 12
	printf("sii_DoSync: %x %x %x ds %x\n",
		((volatile u_short *)SII_BUF_ADDR)[0],
		((volatile u_short *)SII_BUF_ADDR)[2],
		((volatile u_short *)SII_BUF_ADDR)[4],
		regs->dstat); /* XXX */
	regs->dmaddrl = (u_short)(SII_BUF_ADDR >> 1);
	regs->dmaddrh = (u_short)(SII_BUF_ADDR >> 17) & 03;
E 12
E 11
	regs->dmlotc = 5;
	regs->comm = SII_DMA | SII_INXFER | SII_ATN |
		(regs->cstat & SII_STATE_MSK) | SII_MSG_OUT_PHASE;
	MachEmptyWriteBuffer();

	/* wait a short time for XFER complete */
	SII_WAIT_UNTIL(dstat, regs->dstat,
		(dstat & (SII_DNE | SII_TCZ)) == (SII_DNE | SII_TCZ),
		SII_WAIT_COUNT, i);

	if ((dstat & (SII_DNE | SII_TCZ)) != (SII_DNE | SII_TCZ)) {
		printf("sii_DoSync: ds %x cm %x i %d lotc %d\n",
			dstat, regs->comm, i, regs->dmlotc); /* XXX */
I 13
#ifdef DEBUG
E 13
		sii_DumpLog(); /* XXX */
I 13
#endif
E 13
		return;
	}
D 12

E 12
	/* clear the DNE, other errors handled later */
	regs->dstat = SII_DNE;
D 12
	regs->comm = regs->comm & SII_STATE_MSK;
E 12
	MachEmptyWriteBuffer();
I 12
#endif
E 12

I 12
#if 0
	SII_WAIT_UNTIL(dstat, regs->dstat, dstat & (SII_CI | SII_DI),
		SII_WAIT_COUNT, i);
	printf("sii_DoSync: ds %x cm %x i %d lotc %d\n",
		dstat, regs->comm, i, regs->dmlotc); /* XXX */
#endif

E 12
	state->dmaReqAck = len;
}

/*
 * Issue the sequence of commands to the controller to start DMA.
 * NOTE: the data buffer should be word-aligned for DMA out.
 */
static void
sii_StartDMA(regs, phase, dmaAddr, size)
	register SIIRegs *regs;	/* which SII to use */
	int phase;		/* phase to send/receive data */
	u_short *dmaAddr;	/* DMA buffer address */
	int size;		/* # of bytes to transfer */
{

	if (regs->dstat & SII_DNE) { /* XXX */
I 12
		regs->dstat = SII_DNE;
E 12
		printf("sii_StartDMA: DNE set\n");
I 13
#ifdef DEBUG
E 13
		sii_DumpLog();
I 13
#endif
E 13
D 12
		regs->dstat = SII_DNE;
E 12
	}
D 12
	regs->dmaddrl = ((unsigned)dmaAddr >> 1);
	regs->dmaddrh = ((unsigned)dmaAddr >> 17) & 03;
E 12
I 12
	regs->dmaddrl = ((u_long)dmaAddr >> 1);
	regs->dmaddrh = ((u_long)dmaAddr >> 17) & 03;
E 12
	regs->dmlotc = size;
	regs->comm = SII_DMA | SII_INXFER | (regs->cstat & SII_STATE_MSK) |
		phase;
	MachEmptyWriteBuffer();

#ifdef DEBUG
	if (sii_debug > 5) {
		printf("sii_StartDMA: cs 0x%x, ds 0x%x, cm 0x%x, size %d\n", 
			regs->cstat, regs->dstat, regs->comm, size);
	}
#endif
}

/*
 * Call the device driver's 'done' routine to let it know the command is done.
 * The 'done' routine may try to start another command.
 * To be fair, we should start pending commands for other devices
 * before allowing the same device to start another command.
 */
static void
sii_CmdDone(sc, target, error)
	register struct siisoftc *sc;	/* which SII to use */
	int target;			/* which device is done */
	int error;			/* error code if any errors */
{
	register ScsiCmd *scsicmd;
	register int i;

	scsicmd = sc->sc_cmd[target];
#ifdef DIAGNOSTIC
	if (target < 0 || !scsicmd)
		panic("sii_CmdDone");
#endif
	sc->sc_cmd[target] = (ScsiCmd *)0;
#ifdef DEBUG
	if (sii_debug > 1) {
		printf("sii_CmdDone: %s target %d cmd %x err %d resid %d\n",
			scsicmd->sd->sd_driver->d_name, target,
			scsicmd->cmd[0], error, sc->sc_st[target].buflen);
	}
#endif

	/* look for another device that is ready */
	for (i = 0; i < SII_NCMD; i++) {
		/* don't restart a disconnected command */
		if (!sc->sc_cmd[i] || sc->sc_st[i].prevComm)
			continue;
		sii_StartCmd(sc, i);
		break;
	}

	(*scsicmd->sd->sd_driver->d_done)(scsicmd->unit, error,
		sc->sc_st[target].buflen, sc->sc_st[target].statusByte);
}

#ifdef DEBUG
sii_DumpLog()
{
	register struct sii_log *lp;

	printf("sii: cmd %x bn %d cnt %d\n", sii_debug_cmd, sii_debug_bn,
		sii_debug_sz);
D 9
	lp = sii_logp + 1;
	if (lp > &sii_log[NLOG])
		lp = sii_log;
	while (lp != sii_logp) {
E 9
I 9
	lp = sii_logp;
	do {
E 9
D 12
		printf("target %d cs %x ds %x cm %x msg %x\n",
			lp->target, lp->cstat, lp->dstat, lp->comm, lp->msg);
E 12
I 12
		printf("target %d cs %x ds %x cm %x msg %x rlen %x dlen %x\n",
			lp->target, lp->cstat, lp->dstat, lp->comm, lp->msg,
			lp->rlen, lp->dlen);
E 12
		if (++lp >= &sii_log[NLOG])
			lp = sii_log;
D 9
	}
E 9
I 9
	} while (lp != sii_logp);
E 9
}
#endif
#endif
E 1
