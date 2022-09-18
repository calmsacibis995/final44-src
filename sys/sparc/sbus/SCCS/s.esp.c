h55766
s 00008/00059/01290
d D 8.4 94/05/06 11:57:26 torek 10 9
c remove bogus clear, it really was wrong; fix esprel queueing
e
s 00058/00015/01291
d D 8.3 94/05/03 18:22:32 torek 9 8
c must wait in espicmd if someone else is using the chip --
c messy, but this should do the trick
e
s 00351/00472/00955
d D 8.2 93/12/14 20:30:52 torek 8 7
c work around hardware 64K/16M limits; redo some internal protocols.
c bogus `clear' still in place for now.
e
s 00002/00002/01425
d D 8.1 93/06/11 15:14:43 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00003/01409
d D 7.6 93/04/27 07:43:41 torek 6 5
c understands dma rev 3 (but this is untested).  Set DMA_TURBO on rev 2
c chips where allowed (i.e., for all but ESP100).
e
s 00032/00006/01380
d D 7.5 93/04/20 19:31:50 torek 5 4
c update from elf: bootpath; interrupts are now events
e
s 00011/00011/01375
d D 7.4 92/10/11 12:49:45 bostic 4 3
c make kernel includes standard
e
s 00002/00002/01384
d D 7.3 92/07/23 14:02:35 torek 3 2
c /sys/scsi moves to /sys/dev/scsi
e
s 00005/00000/01381
d D 7.2 92/07/21 16:52:05 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 01381/00000/00000
d D 7.1 92/07/13 00:44:05 torek 1 0
c date and time created 92/07/13 00:44:05 by torek
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 5
 *	California, Lawrence Berkeley Laboratories.
E 5
I 5
 *	California, Lawrence Berkeley Laboratory.
E 5
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 5
 * from: $Header: esp.c,v 1.22 92/06/17 06:59:33 torek Exp $ (LBL)
E 5
I 5
D 6
 * from: $Header: esp.c,v 1.27 93/04/20 11:20:38 torek Exp $ (LBL)
E 6
I 6
 * from: $Header: esp.c,v 1.28 93/04/27 14:40:44 torek Exp $ (LBL)
E 6
E 5
 *
 * Loosely derived from Mary Baker's devSCSIC90.c from the Berkeley
 * Sprite project, which is:
 *
 * Copyright 1988 Regents of the University of California
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  The University of California
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 * from /sprite/src/kernel/dev/sun4c.md/RCS/devSCSIC90.c,v 1.4
 * 90/12/19 12:37:58 mgbaker Exp $ SPRITE (Berkeley)
 */

/*
 * Sbus ESP/DMA driver.  A single driver must be used for both devices
 * as they are physically tied to each other:  The DMA chip can only
 * be used to assist ESP SCSI transactions; the ESP interrupt enable is
 * in the DMA chip csr.
 *
 * Since DMA and SCSI interrupts are handled in the same routine, the
 * DMA device does not declare itself as an sbus device.  This saves
 * some space.
 */

D 4
#include "sys/param.h"
#include "sys/buf.h"
#include "sys/device.h"
#include "sys/malloc.h"
E 4
I 4
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/device.h>
#include <sys/malloc.h>
E 4

D 3
#include "scsi/scsi.h"
#include "scsi/scsivar.h"
E 3
I 3
D 4
#include "dev/scsi/scsi.h"
#include "dev/scsi/scsivar.h"
E 4
I 4
#include <dev/scsi/scsi.h>
#include <dev/scsi/scsivar.h>
E 4
E 3

D 4
#include "machine/autoconf.h"
#include "machine/cpu.h"
E 4
I 4
#include <machine/autoconf.h>
#include <machine/cpu.h>
E 4

D 4
#include "dmareg.h"
E 4
I 4
#include <sparc/sbus/dmareg.h>
E 4
#define ESP_PHASE_NAMES
D 4
#include "espreg.h"
#include "sbusvar.h"
E 4
I 4
#include <sparc/sbus/espreg.h>
#include <sparc/sbus/sbusvar.h>
E 4

D 8
#ifdef DEBUG
int espdebug = 1;
#endif
E 8
I 8
#include <libkern/libkern.h>
E 8

/*
D 8
 * This driver is organized as a collection of state machines.  The
 * primary machine is the SCSI sequencer:
E 8
I 8
 * This driver is largely a giant state machine:
E 8
 *
D 8
 *	Given some previous SCSI state (as set up or tracked by us earlier)
 *	and the interrupt registers provided on the chips (dmacsr, espstat,
 *	espstep, and espintr), derive an action.  In many cases this is
 *	just a matter of reading the target's phase and following its orders,
 *	which sets a new state.
E 8
I 8
 *	Given some previous SCSI state (as set up or tracked by us
 *	earlier) and the interrupt registers provided on the chips
 *	(dmacsr, espstat, espstep, and espintr), derive an action.
 *	In many cases this is just a matter of reading the target's
 *	phase and following its orders, which sets a new state.
E 8
 *
 * This sequencing is done in espact(); the state is primed in espselect().
 *
D 8
 * There will be (update this comment when there is) another state machine
 * used to handle transfers that fall afoul of chip limits (16 bit DMA
 * counter; 24 bit address counter in 32 bit address field).
E 8
I 8
 * Data transfer is always done via DMA.  Unfortunately, there are
 * limits in the DMA and ESP chips on how much data can be moved
 * in a single operation.  The ESP chip has a 16-bit counter, so
 * it is limited to 65536 bytes.  More insidiously, while the DMA
 * chip has a 32-bit address, this is composed of a 24-bit counter
 * with an 8-bit latch, so it cannot cross a 16 MB boundary.  To
 * handle these, we program a smaller count than our caller requests;
 * when this shorter transfer is done, if the target is still up
 * for data transfer, we simply keep going (updating the DMA address)
 * as needed.
E 8
D 10
 *
 * Another state bit is used to recover from bus resets:
 *
 *	A single TEST UNIT READY is attempted on each target before any
 *	real communication begins; this TEST UNIT READY is allowed to
 *	fail in any way.  This is required for the Quantum ProDrive 100
 *	MB disks, for instance, which respond to their first selection
 *	with status phase, and for anything that insists on implementing
 *	the broken SCSI-2 synch transfer initial message.
 *
 * This is done in espclear() (which calls espselect(); functions that
 * call espselect() must check for clearing first).
 *
 * The state machines actually intermingle, as some SCSI sequences are
 * only allowed during clearing.
E 10
 */

/* per-DMA variables */
struct dma_softc {
D 8
	struct	device	sc_dev;		/* base device */
	volatile struct dmareg *sc_dma;	/* register virtual address */
I 6
	int	sc_dmarev;		/* revision */
	char	*sc_dmafmt;		/* format for error messages */

E 8
I 8
	struct	device dc_dev;		/* base device */
	volatile struct dmareg *dc_dma;	/* register virtual address */
	int	dc_dmarev;		/* revision */
	char	*dc_dmafmt;		/* format for error messages */
E 8
E 6
};
void	dmaattach(struct device *, struct device *, void *);
struct cfdriver dmacd =
    { NULL, "dma", matchbyname, dmaattach, DV_DULL, sizeof(struct dma_softc) };

/* per-ESP variables */
struct esp_softc {
	/*
	 * External interfaces.
	 */
	struct	hba_softc sc_hba;	/* base device + hba, must be first */
I 8
#define	sc_dev	sc_hba.hba_dev
E 8
	struct	sbusdev sc_sd;		/* sbus device */
	struct	intrhand sc_ih;		/* interrupt entry */
D 5
	int	sc_interrupts;		/* total number of interrupts taken */
E 5
I 5
	struct	evcnt sc_intrcnt;	/* interrupt counter */
E 5
D 8
	struct	dma_softc *sc_dsc;	/* pointer to corresponding dma sc */
E 8
I 8
	struct	dma_softc *sc_dc;	/* pointer to corresponding dma sc */
E 8

	/*
	 * Addresses mapped to hardware registers.
	 */
	volatile struct espreg *sc_esp;
	volatile struct dmareg *sc_dma;

	/*
	 * Copies of registers cleared/unlatched by reading.
I 8
	 * (FIFO flags is not cleared, but we want it for debugging.)
E 8
	 */
	u_long	sc_dmacsr;
	u_char	sc_espstat;
	u_char	sc_espstep;
	u_char	sc_espintr;
I 8
	u_char	sc_espfflags;
E 8

	/* miscellaneous */
	int	sc_clockfreq;		/* clock frequency */
	u_char	sc_sel_timeout;		/* select timeout */
	u_char	sc_id;			/* initiator ID (default = 7) */
D 10
	u_char	sc_needclear;		/* uncleared targets (1 bit each) */
E 10
	u_char	sc_esptype;		/* 100, 100A, 2xx (see below) */
	u_char	sc_ccf;			/* clock conversion factor */
	u_char	sc_conf1;		/* value for config reg 1 */
	u_char	sc_conf2;		/* value for config reg 2 */
	u_char	sc_conf3;		/* value for config reg 3 */
I 5
	struct	bootpath *sc_bp;	/* esp bootpath so far */
E 5

	/*
	 * Information pertaining to the current transfer,
	 * including sequencing.
	 *
	 * The size of sc_msg is the size of the ESP fifo,
	 * since we do message-in simply by allowing the fifo to fill.
	 */
	char	sc_probing;		/* used during autoconf; see below */
D 10
	char	sc_clearing;		/* true => cmd is just to clear targ */
E 10
I 9
	char	sc_iwant;		/* true => icmd needs wakeup on idle */
E 9
	char	sc_state;		/* SCSI protocol state; see below */
	char	sc_sentcmd;		/* set once we get cmd out */
	char	sc_dmaactive;		/* true => doing dma */
#ifdef notyet
	u_char	sc_sync;		/* synchronous transfer stuff (?) */
#endif
	u_char	sc_stat[2];		/* status from last `status' phase */
	u_char	sc_msg[16];		/* message from device */
	u_short	sc_dmactl;		/* control to load into dma csr */
D 8
	u_long	sc_dmaaddr;		/* addr to load into dma addr */
E 8
I 8
	u_long	sc_dmaaddr;		/* address for next xfer */
	int	sc_dmasize;		/* size of current xfer */
	int	sc_resid;		/* count of bytes not yet xferred */
E 8
	int	sc_targ;		/* the target involved */
D 8
	int	sc_resid;		/* count of bytes not xferred */
	struct	scsi_cdb sc_cdb;	/* current command (not in dvma) */
E 8
I 8
	struct	scsi_cdb *sc_curcdb;	/* ptr to current command */
	/* might cdbspace eventually be per-target? */
	struct	scsi_cdb sc_cdbspace;	/* space for one command */
E 8
};

/*
D 8
 * Values for sc_esptype (used to control configuration reset).
 * The order is important; see espreset().
E 8
I 8
 * Values for sc_esptype (used to control configuration reset, and for
 * workarounds for chip bugs).  The order is important; see espreset().
E 8
 */
#define	ESP100	0
#define	ESP100A	1
#define	ESP2XX	2

/*
 * Probe state.  0 means not probing.  While looking for each target
 * we set this to PROBE_TESTING and do a TEST UNIT READY on unit 0.
 * If selection fails, this is changed to PROBE_NO_TARGET; otherwise
 * we assume the target exists, regardless of the result of the test.
 */
#define	PROBE_TESTING	1
#define	PROBE_NO_TARGET	2

/*
 * States in sc_state.
 *
D 8
 * Note that S_CMDSVC is rare: normally we load the SCSI command into the
E 8
I 8
 * Note that S_SVC is rare: normally we load the SCSI command into the
E 8
 * ESP fifo and get interrupted only when the device has gone to data
 * or status phase.  If the device wants to play games, though, we end
 * up doing things differently.
 */
char *espstates[] = {
#define	S_IDLE		0	/* not doing anything */
	"idle",
#define	S_SEL		1	/* expecting select done interrupt */
	"selecting",
D 8
#define	S_CMDSVC	2	/* expecting service req interrupt */
	"waiting for service request after command",
#define	S_IOSVC		3	/* expecting service req interrupt */
	"waiting for service request after io",
#define	S_DI		4	/* expecting data-in done interrupt */
E 8
I 8
#define	S_SVC		2	/* expecting service req interrupt */
	"waiting for svc req",
#define	S_DI		3	/* expecting data-in done interrupt */
E 8
	"receiving data",
D 8
#define	S_DO		5	/* expecting data-out done interrupt */
E 8
I 8
#define	S_DO		4	/* expecting data-out done interrupt */
E 8
	"sending data",
D 8
#define	S_STAT		6	/* expecting status done interrupt */
E 8
I 8
#define	S_STAT		5	/* expecting status done interrupt */
E 8
	"receiving status",
D 8
#define	S_MI		7	/* expecting message-in done interrupt */
E 8
I 8
#define	S_MI		6	/* expecting message-in done interrupt */
E 8
	"receiving message",
D 8
#define	S_FI		8	/* expecting final disconnect interrupt */
E 8
I 8
#define	S_FI		7	/* expecting final disconnect interrupt */
E 8
	"waiting for disconnect"
};

/*
I 8
 * Hardware limits on transfer sizes (see comments at top).
 */
#define	ESPMAX		(64 * 1024)
#define	DMAMAX(a)	(0x01000000 - ((a) & 0x00ffffff))

/*
E 8
 * Return values from espact().
 */
#define	ACT_CONT	0	/* espact() handled everything */
D 8
#define	ACT_READ	1	/* target said it is sending us data */
#define	ACT_WRITE	2	/* target said it is expecting data */
#define	ACT_DONE	3	/* handled everything, and op is now done */
#define	ACT_ERROR	4	/* an error occurred, op has been trashed */
#define	ACT_RESET	5	/* please reset ESP, then do ACT_ERROR */
#define	ACT_QUICKINTR	6	/* another interrupt is expected immediately */
E 8
I 8
#define	ACT_IO		1	/* espact() is xferring data */
#define	ACT_DONE	2	/* handled everything, and op is now done */
#define	ACT_ERROR	3	/* an error occurred, op has been trashed */
#define	ACT_RESET	4	/* please reset ESP, then do ACT_ERROR */
#define	ACT_QUICKINTR	5	/* another interrupt is expected immediately */
E 8

/* autoconfiguration driver */
void	espattach(struct device *, struct device *, void *);
struct cfdriver espcd =
D 5
    { NULL, "esp", matchbyname, espattach, DV_DULL, sizeof(struct esp_softc) };
E 5
I 5
D 10
    { NULL, "esp", matchbyname, espattach, DV_DULL, sizeof(struct esp_softc),
      "intr" };
E 10
I 10
    { NULL, "esp", matchbyname, espattach, DV_DULL, sizeof(struct esp_softc) };
E 10
E 5

/* Sbus driver */
void	espsbreset(struct device *);

/* interrupt interface */
int	espintr(void *);

/* SCSI HBA driver */
int	espicmd(struct hba_softc *, int, struct scsi_cdb *, caddr_t, int, int);
int	espdump(struct hba_softc *, int, struct scsi_cdb *, caddr_t, int);
void	espstart(struct device *, struct sq *, struct buf *,
		scdgo_fn, struct device *);
int	espgo(struct device *, int, scintr_fn, struct device *,
		struct buf *, int);
void	esprel(struct device *);
void	esphbareset(struct hba_softc *, int);
static struct hbadriver esphbadriver =
    { espicmd, espdump, espstart, espgo, esprel, esphbareset };

D 8
/* forward declarations */
static void espdoattach(int unit);
static void espreset(struct esp_softc *);
E 8
I 8
/* other prototypes */
static void espdoattach(int);
static void dmareset(struct esp_softc *);
static void espreset(struct esp_softc *, int);
static void esperror(struct esp_softc *, const char *);
static int espact(struct esp_softc *);
void espselect(struct esp_softc *, int, struct scsi_cdb *);
E 8

D 8
/*
 * The transfer size is limited to 16 bits since the scsi ctrl transfer
 * counter is only 2 bytes.  A 0 value means the biggest transfer size
 * (2 ** 16) == 64k.
 */
#define MAX_TRANSFER_SIZE	(64 * 1024)
E 8
I 8
/* second arg to espreset() */
#define	RESET_ESPCHIP	0x1
#define	RESET_SCSIBUS	0x2
#define	RESET_BOTH	(RESET_ESPCHIP | RESET_SCSIBUS)
E 8

D 8
/* Return true if this transfer will cross a dma boundary */
#define CROSS_DMA(addr, len) \
    (((int)(addr) & 0xff000000) != (((int)(addr) + (len) - 1) & 0xff000000))

E 8
/*
 * Attach a found DMA chip.
 * The second argument is really a pointer to an sbus_attach_args.
 */
void
dmaattach(parent, dev, args)
	struct device *parent;
	struct device *dev;
	void *args;
{
D 8
	register struct dma_softc *dsc = (struct dma_softc *)dev;
E 8
I 8
	register struct dma_softc *dc = (struct dma_softc *)dev;
E 8
	register struct sbus_attach_args *sa = args;
	register volatile struct dmareg *dma;
	register int rev;
	struct esp_softc *esc;

	if (sa->sa_ra.ra_vaddr)
		dma = (volatile struct dmareg *)sa->sa_ra.ra_vaddr;
	else
		dma = (volatile struct dmareg *)
		    mapiodev(sa->sa_ra.ra_paddr, sizeof(struct dmareg));
D 8
	dsc->sc_dma = dma;
E 8
I 8
	dc->dc_dma = dma;
E 8

	switch (rev = DMA_REV(dma->dma_csr)) {
	case DMAREV_1:
		printf(": rev 1\n");
I 6
D 8
		dsc->sc_dmafmt = DMA_REV1_BITS;
E 8
I 8
		dc->dc_dmafmt = DMA_REV1_BITS;
E 8
E 6
		break;
	case DMAREV_2:
		printf(": rev 2\n");
I 6
D 8
		dsc->sc_dmafmt = DMA_REV2_BITS;
E 8
I 8
		dc->dc_dmafmt = DMA_REV2_BITS;
E 8
E 6
		break;
I 6
	case DMAREV_3:
		printf(": rev 3\n");
		printf("WARNING: esp.c not yet updated for rev 3\n");
D 8
		dsc->sc_dmafmt = DMA_REV3_BITS;
E 8
I 8
		dc->dc_dmafmt = DMA_REV3_BITS;
E 8
		break;
E 6
	default:
D 6
		printf(": unknown revision %d\n", rev);
E 6
I 6
		printf(": unknown revision code 0x%x\n", rev);
D 8
		dsc->sc_dmafmt = DMA_REV3_BITS;	/* cross fingers */
E 8
I 8
		dc->dc_dmafmt = DMA_REV3_BITS;	/* cross fingers */
E 8
E 6
		break;
	}
I 6
D 8
	dsc->sc_dmarev = rev;
E 6
	espdoattach(dsc->sc_dev.dv_unit);
E 8
I 8
	dc->dc_dmarev = rev;
	espdoattach(dc->dc_dev.dv_unit);
E 8
}

/*
 * Attach a found ESP chip.  Search for targets; attach each one found.
 * The latter must be deferred if the corresponding dma chip has not yet
 * been configured.
 */
void
espattach(parent, self, args)
	struct device *parent;
	struct device *self;
	void *args;
{
	register struct esp_softc *sc = (struct esp_softc *)self;
	register struct sbus_attach_args *sa = args;
	register volatile struct espreg *esp;
I 5
	register struct bootpath *bp;
E 5
D 8
	struct dma_softc *dsc;
E 8
	int node, pri, freq, t;

	if (sa->sa_ra.ra_nintr != 1) {
		printf(": expected 1 interrupt, got %d\n", sa->sa_ra.ra_nintr);
		return;
	}
	pri = sa->sa_ra.ra_intr[0].int_pri;
	printf(" pri %d", pri);
	if (sa->sa_ra.ra_vaddr)
		esp = (volatile struct espreg *)sa->sa_ra.ra_vaddr;
	else
		esp = (volatile struct espreg *)
		    mapiodev(sa->sa_ra.ra_paddr, sizeof(struct espreg));
	sc->sc_esp = esp;
	node = sa->sa_ra.ra_node;
	sc->sc_id = getpropint(node, "initiator-id", 7);
	freq = getpropint(node, "clock-frequency", -1);
	if (freq < 0)
D 8
		freq = ((struct sbus_softc *)sc->sc_hba.hba_dev.dv_parent)->sc_clockfreq;
E 8
I 8
		freq =
		    ((struct sbus_softc *)sc->sc_dev.dv_parent)->sc_clockfreq;
E 8

	/* MIGHT NEED TO RESET ESP CHIP HERE ...? */

	/*
	 * Find out whether we have a -100, -100A, or -2xx,
	 * and what speed it runs at.
	 */
	sc->sc_conf1 = sc->sc_id | ESPCONF1_PARENB;
	/* sc->sc_conf2 = 0; */
	/* sc->sc_conf3 = 0; */
	esp->esp_conf1 = sc->sc_conf1;
	esp->esp_conf2 = 0;
	esp->esp_conf2 = ESPCONF2_SCSI2 | ESPCONF2_RPE;
	if ((esp->esp_conf2 & ~ESPCONF2_RSVD) !=
	    (ESPCONF2_SCSI2 | ESPCONF2_RPE)) {
		printf(": ESP100");
		sc->sc_esptype = ESP100;
	} else {
		esp->esp_conf2 = 0;
		esp->esp_conf3 = 0;
		esp->esp_conf3 = 5;
		if (esp->esp_conf3 != 5) {	/* XXX def bits */
			printf(": ESP100A");
			sc->sc_esptype = ESP100A;
		} else {
			esp->esp_conf3 = 0;
			printf(": ESP2XX");
			sc->sc_esptype = ESP2XX;
		}
	}
	printf(", clock = %s MHz, ID = %d\n", clockfreq(freq), sc->sc_id);

	/*
	 * Set clock conversion factor and select timeout.
	 * N.B.: clock frequency is not actually used in the rest
	 * of the driver; I calculate it here for completeness only
	 * (so I can see it when debugging).
	 */
	sc->sc_clockfreq = freq;
	freq = howmany(freq, 1000 * 1000);	/* convert to MHz */
	t = ESPCCF_FROMMHZ(freq);
	if (t < ESPCCF_MIN)
		t = ESPCCF_MIN;
	sc->sc_ccf = t;
	t = ESPTIMO_REGVAL(250, t, freq);	/* timeout = 250 ms. */
	if (t >= 256)
		t = 0;
	sc->sc_sel_timeout = t;

	/*
	 * Link into sbus; set interrupt handler.
	 */
	sc->sc_sd.sd_reset = espsbreset;
D 8
	sbus_establish(&sc->sc_sd, &sc->sc_hba.hba_dev);
E 8
I 8
	sbus_establish(&sc->sc_sd, &sc->sc_dev);
E 8
	sc->sc_ih.ih_fun = espintr;
	sc->sc_ih.ih_arg = sc;
	intr_establish(pri, &sc->sc_ih);
I 5
D 8
	evcnt_attach(&sc->sc_hba.hba_dev, "intr", &sc->sc_intrcnt);
E 8
I 8
	evcnt_attach(&sc->sc_dev, "intr", &sc->sc_intrcnt);
E 8

#define SAME_ESP(bp, sa) \
	((bp->val[0] == sa->sa_slot && bp->val[1] == sa->sa_offset) || \
D 8
	 (bp->val[0] == -1 && bp->val[1] == sc->sc_hba.hba_dev.dv_unit))
E 8
I 8
	 (bp->val[0] == -1 && bp->val[1] == sc->sc_dev.dv_unit))
E 8

	bp = sa->sa_ra.ra_bp;
	if (bp != NULL && strcmp(bp->name, "esp") == 0 && SAME_ESP(bp, sa))
		sc->sc_bp = bp + 1;
E 5
D 8
	espdoattach(sc->sc_hba.hba_dev.dv_unit);
E 8
I 8
	espdoattach(sc->sc_dev.dv_unit);
E 8
}

/*
 * `Final' attach of esp occurs once esp and dma chips have been found
 * and assigned virtual addresses.  Set up the ESP SCSI data structures
 * and probe the SCSI bus.
 */
static void
espdoattach(unit)
	int unit;
{
	register struct esp_softc *sc;
D 8
	register struct dma_softc *dsc;
E 8
I 8
	register struct dma_softc *dc;
E 8
D 5
	register int targ;
E 5
I 5
	register struct bootpath *bp;
	register struct targ *t;
	register int targ, u;
E 5

	/* make sure we have both */
	if (espcd.cd_ndevs <= unit ||
	    dmacd.cd_ndevs <= unit ||
	    (sc = espcd.cd_devs[unit]) == NULL ||
D 8
	    (dsc = dmacd.cd_devs[unit]) == NULL)
E 8
I 8
	    (dc = dmacd.cd_devs[unit]) == NULL)
E 8
		return;
D 8
	sc->sc_dsc = dsc;
	sc->sc_dma = dsc->sc_dma;
E 8
I 8
	sc->sc_dc = dc;
	sc->sc_dma = dc->dc_dma;
E 8
	sc->sc_hba.hba_driver = &esphbadriver;

D 8
	espreset(sc);
E 8
I 8
	sc->sc_dma->dma_csr = 0;	/* ??? */
	espreset(sc, RESET_ESPCHIP);
E 8

	/* MAYBE THIS SHOULD BE MOVED TO scsi_subr.c? */
	for (targ = 0; targ < 8; targ++) {
		if (targ == sc->sc_id)
			continue;
		sc->sc_probing = PROBE_TESTING;
D 10
		sc->sc_clearing = 1;
E 10
D 8
		(void) scsi_test_unit_ready(&sc->sc_hba, targ, 0);
E 8
I 8
		(void)scsi_test_unit_ready(&sc->sc_hba, targ, 0);
E 8
		if (sc->sc_probing != PROBE_NO_TARGET) {
			sc->sc_probing = 0;
D 10
			sc->sc_clearing = 0;
E 10
			SCSI_FOUNDTARGET(&sc->sc_hba, targ);
		}
	}
	sc->sc_probing = 0;
D 10
	sc->sc_clearing = 0;
E 10
I 5

D 8
	if ((bp = sc->sc_bp) == NULL || (u_int)(targ = bp->val[0]) >= 8 ||
	    (u_int)(u = bp->val[1]) >= 8)
		return;

E 8
	/*
D 8
	 * Did we find it? We could compare bp->name against the unit's
	 * name but there's no real need since a target and unit
	 * uniquely specify a scsi device.
E 8
I 8
	 * See if we booted from a unit on this target.  We could
	 * compare bp->name against the unit's name but there's no
	 * real need since a target and unit uniquely specify a
	 * scsi device.
E 8
	 */
D 8
	if ((t = sc->sc_hba.hba_targets[targ]) != NULL && t->t_units[u] != NULL)
E 8
I 8
	if ((bp = sc->sc_bp) != NULL && (u_int)(targ = bp->val[0]) < 8 &&
	    (u_int)(u = bp->val[1]) < 8 &&
	    (t = sc->sc_hba.hba_targets[targ]) != NULL && t->t_units[u] != NULL)
E 8
		bootdv = t->t_units[u]->u_dev;
E 5
}

/*
D 8
 * Internal DMA reset.
E 8
I 8
 * We are not allowed to touch the DMA "flush" and "drain" bits
 * while it is still thinking about a request (DMA_RP).
E 8
 */
I 8
#define	DMAWAIT(dma)	while ((dma)->dma_csr & DMA_RP) DELAY(1)
I 9
#define	DMAWAIT1(dma)	while ((dma)->dma_csr & DMA_PC) DELAY(1)
E 9

/*
 * Reset the DMA chip.
 */
E 8
static void
dmareset(sc)
	struct esp_softc *sc;
{
	register volatile struct dmareg *dma = sc->sc_dma;

D 8
	/* reset DMA chip */
E 8
I 8
	DMAWAIT(dma);
E 8
	dma->dma_csr |= DMA_RESET;
	DELAY(200);
	dma->dma_csr &= ~DMA_RESET;	/* ??? */
D 9
	sc->sc_state = S_IDLE;
E 9
	sc->sc_dmaactive = 0;
I 6
D 8
	if (sc->sc_dsc->sc_dmarev == DMAREV_2 && sc->sc_esptype != ESP100)
E 8
I 8
	if (sc->sc_dc->dc_dmarev == DMAREV_2 && sc->sc_esptype != ESP100)
E 8
		dma->dma_csr |= DMA_TURBO;
E 6
	dma->dma_csr |= DMA_IE;		/* enable interrupts */
	DELAY(200);
}

/*
D 8
 * Reset the chip.  N.B.: this causes a SCSI bus reset!
E 8
I 8
 * Reset the chip and/or SCSI bus (always resets DMA).
E 8
 */
static void
D 8
espreset(sc)
E 8
I 8
espreset(sc, how)
E 8
	register struct esp_softc *sc;
I 8
	int how;
E 8
{
	register volatile struct espreg *esp = sc->sc_esp;

	dmareset(sc);
D 8
	esp->esp_cmd = ESPCMD_RESET_CHIP;
	DELAY(200);
	esp->esp_cmd = ESPCMD_NOP;
	DELAY(200);

	/*
	 * Reload configuration registers (cleared by RESET_CHIP command).
	 * Reloading conf2 on an ESP100 goofs it up, so out of paranoia
	 * we load only the registers that exist.
	 */
	esp->esp_conf1 = sc->sc_conf1;
	if (sc->sc_esptype > ESP100) {		/* 100A, 2XX */
		esp->esp_conf2 = sc->sc_conf2;
		if (sc->sc_esptype > ESP100A)	/* 2XX only */
			esp->esp_conf3 = sc->sc_conf3;
E 8
I 8
	if (how & RESET_ESPCHIP) {
		esp->esp_cmd = ESPCMD_RESET_CHIP;
		esp->esp_cmd = ESPCMD_NOP;
		/*
		 * Reload configuration registers (cleared by
		 * RESET_CHIP command).  Reloading conf2 on an
		 * ESP100 goofs it up, so out of paranoia we load
		 * only the registers that exist.
		 */
		esp->esp_conf1 = sc->sc_conf1;
		if (sc->sc_esptype > ESP100) {		/* 100A, 2XX */
			esp->esp_conf2 = sc->sc_conf2;
			if (sc->sc_esptype > ESP100A)	/* 2XX only */
				esp->esp_conf3 = sc->sc_conf3;
		}
		esp->esp_ccf = sc->sc_ccf;
		esp->esp_timeout = sc->sc_sel_timeout;
		/* We set synch offset later. */
E 8
	}
D 8
	esp->esp_ccf = sc->sc_ccf;
	esp->esp_timeout = sc->sc_sel_timeout;
	/* We set synch offset later. */
E 8
I 8
	if (how & RESET_SCSIBUS) {
		/*
		 * The chip should retain most of its parameters
		 * (including esp_ccf) across this kind of reset
		 * (see section 3.5 of Emulex documentation).
		 */
		/* turn off scsi bus reset interrupts and reset scsi bus */
		esp->esp_conf1 = sc->sc_conf1 | ESPCONF1_REPORT;
		esp->esp_cmd = ESPCMD_RESET_BUS;
		esp->esp_cmd = ESPCMD_NOP;
		DELAY(100000);	/* ??? */
		(void)esp->esp_intr;
		esp->esp_conf1 = sc->sc_conf1;
	}
E 8
D 9

E 9
I 9
	sc->sc_state = S_IDLE;
D 10
	if (sc->sc_iwant) {
		wakeup((caddr_t)&sc->sc_iwant);
		sc->sc_iwant = 0;
	}
E 9
	sc->sc_needclear = 0xff;
E 10
}

/*
 * Reset the SCSI bus and, optionally, all attached targets.
D 8
 * The chip should retain most of its parameters (including esp_ccf)
 * across this kind of reset (see section 3.5 of Emulex documentation).
E 8
 */
void
esphbareset(hba, resetunits)
	struct hba_softc *hba;
	int resetunits;
{
	register struct esp_softc *sc = (struct esp_softc *)hba;
D 8
	register volatile struct espreg *esp = sc->sc_esp;
E 8

D 8
	dmareset(sc);

	/* BEGIN ??? */
	/* turn off scsi bus reset interrupts and reset scsi bus */
	esp->esp_conf1 = sc->sc_conf1 | ESPCONF1_REPORT;
	DELAY(200);
	esp->esp_cmd = ESPCMD_RESET_BUS;
	DELAY(800);
	esp->esp_cmd = ESPCMD_NOP;
	DELAY(200);
	esp->esp_conf1 = sc->sc_conf1;
	/* END ??? */

	sc->sc_needclear = 0xff;

E 8
I 8
	espreset(sc, RESET_SCSIBUS);
E 8
	if (resetunits)
		scsi_reset_units(&sc->sc_hba);
}

/*
 * Reset the esp, after an Sbus reset.
 * Also resets corresponding dma chip.
 *
 * THIS ROUTINE MIGHT GO AWAY
 */
void
espsbreset(dev)
	struct device *dev;
{
	struct esp_softc *sc = (struct esp_softc *)dev;

D 8
	if (sc->sc_dsc) {
		printf(" %s %s", sc->sc_dsc->sc_dev.dv_xname,
		    sc->sc_hba.hba_dev.dv_xname);
E 8
I 8
	if (sc->sc_dc) {
		printf(" %s %s", sc->sc_dc->dc_dev.dv_xname,
		    sc->sc_dev.dv_xname);
E 8
		esphbareset(&sc->sc_hba, 1);
	}
}

I 8
/*
 * Log an error.
 */
E 8
static void
esperror(sc, err)
D 8
	char *err;
E 8
	register struct esp_softc *sc;
I 8
	const char *err;
E 8
{
I 8
	int stat;
E 8

D 8
	printf("%s: %s (target=%d): stat=%b step=%x dmacsr=%b intr=%b\n",
	    sc->sc_hba.hba_dev.dv_xname, err, sc->sc_targ,
	    sc->sc_espstat, ESPSTAT_BITS, sc->sc_espstep,
D 6
	    sc->sc_dmacsr, DMA_BITS, sc->sc_espintr, ESPINTR_BITS);
E 6
I 6
	    sc->sc_dmacsr, sc->sc_dsc->sc_dmafmt,
	    sc->sc_espintr, ESPINTR_BITS);
E 8
I 8
	stat = sc->sc_espstat;
	printf(
"%s target %d cmd 0x%x (%s): %s:\n\
\tstat=%b (%s) step=%x dmacsr=%b fflags=%x intr=%b\n",
	    sc->sc_dev.dv_xname, sc->sc_targ, sc->sc_curcdb->cdb_bytes[0],
	    espstates[sc->sc_state], err,
	    stat, ESPSTAT_BITS, espphases[stat & ESPSTAT_PHASE],
	    sc->sc_espstep, sc->sc_dmacsr, sc->sc_dc->dc_dmafmt,
	    sc->sc_espfflags, sc->sc_espintr, ESPINTR_BITS);
E 8
E 6
}

/*
D 8
 * An interrupt has occurred.  Sequence through the SCSI state machine.
 * Return the action to take.
E 8
I 8
 * Issue a select, loading command into the FIFO.
 * Return nonzero on error, 0 if OK.
 * Sets state to `selecting'; espact() will sequence state FSM.
 */
void
espselect(sc, targ, cdb)
	register struct esp_softc *sc;
	register int targ;
	register struct scsi_cdb *cdb;
{
	register volatile struct espreg *esp;
	register int i, cmdlen;

	sc->sc_targ = targ;
	sc->sc_state = S_SEL;
	sc->sc_curcdb = cdb;
	sc->sc_sentcmd = 0;
	sc->sc_stat[0] = 0xff;		/* ??? */
	sc->sc_msg[0] = 0xff;		/* ??? */

	/*
	 * Try to talk to target.
	 * Synch offset 0 => asynchronous transfer.
	 */
	esp = sc->sc_esp;
	esp->esp_id = targ;
	esp->esp_syncoff = 0;

	/*
	 * Stuff the command bytes into the fifo.
	 * Select without attention since we do not do disconnect yet.
	 */
	cmdlen = SCSICMDLEN(cdb->cdb_bytes[0]);
	for (i = 0; i < cmdlen; i++)
		esp->esp_fifo = cdb->cdb_bytes[i];
	esp->esp_cmd = ESPCMD_SEL_NATN;
	/* the rest is done elsewhere */
}

/*
 * Sequence through the SCSI state machine.  Return the action to take.
E 8
 *
 * Most of the work happens here.
 *
 * There are three interrupt sources:
 *   -- ESP interrupt request (typically, some device wants something).
 *   -- DMA memory error.
 *   -- DMA byte count has reached 0 (we do not often want this one but
 *	can only turn it off in rev 2 DMA chips, it seems).
 *	DOES THIS OCCUR AT ALL HERE?  THERE IS NOTHING TO HANDLE IT!
 */
static int
D 8
espact(sc, esp, dma, cdb)
E 8
I 8
espact(sc)
E 8
	register struct esp_softc *sc;
I 8
{
E 8
	register volatile struct espreg *esp;
	register volatile struct dmareg *dma;
I 8
	register int reg, i, resid, newstate;
E 8
	register struct scsi_cdb *cdb;
D 8
{
	register char *xname = sc->sc_hba.hba_dev.dv_xname;
	register int reg, phase, i;
E 8

I 8
	dma = sc->sc_dma;
E 8
	/* check various error conditions, using as little code as possible */
	if (sc->sc_dmacsr & DMA_EP) {
		esperror(sc, "DMA error");
I 8
		DMAWAIT(dma);
E 8
		dma->dma_csr |= DMA_FLUSH;
I 9
		DMAWAIT1(dma);
E 9
		return (ACT_ERROR);
	}
	reg = sc->sc_espstat;
	if (reg & ESPSTAT_GE) {
		/*
		 * This often occurs when there is no target.
		 * (See DSC code below.)
		 */
		if (sc->sc_espintr & ESPINTR_DSC &&
		    sc->sc_state == S_SEL && sc->sc_probing) {
			sc->sc_probing = PROBE_NO_TARGET;
			return (ACT_RESET);
		}
D 8
esperror(sc, "DIAGNOSTIC: gross error (ignored)");
E 8
I 8
esperror(sc, "DIAG: gross error (ignored)");
E 8
	}
	if (reg & ESPSTAT_PE) {
		esperror(sc, "parity error");
		return (ACT_RESET);
	}
	reg = sc->sc_espintr;
#define ERR (ESPINTR_SBR|ESPINTR_ILC|ESPINTR_RSL|ESPINTR_SAT|ESPINTR_SEL)
	if (reg & ERR) {
		if (reg & ESPINTR_SBR)
			esperror(sc, "scsi bus reset");
		else if (reg & ESPINTR_ILC)
			esperror(sc, "illegal command (driver bug)");
		else {
D 8
			printf("%s: target %d", xname, sc->sc_targ);
E 8
I 8
			printf("%s: target %d", sc->sc_dev.dv_xname,
			    sc->sc_targ);
E 8
			if (reg & ESPINTR_RSL)
				printf(" tried to reselect;");
			if (reg & ESPINTR_SAT)
				printf(" selected with ATN;");
			if (reg & ESPINTR_SEL)
				printf(" selected us as target;");
			printf("we do not allow this yet\n");
		}
		return (ACT_ERROR);
	}
#undef ERR

I 8
	esp = sc->sc_esp;

E 8
	/*
	 * Disconnect currently only allowed in `final interrupt' states.
	 */
	if (reg & ESPINTR_DSC) {
		if (sc->sc_state == S_FI)
			return (ACT_DONE);
		/*
		 * If we were doing a select just to test the existence
		 * of the target, note that it did not respond; otherwise
		 * gripe.
		 */
		if (sc->sc_state == S_SEL) {
			if (sc->sc_probing) {
				sc->sc_probing = PROBE_NO_TARGET;
				return (ACT_RESET);
			}
		}
		/* flush fifo, in case we were selecting or sending data */
		esp->esp_cmd = ESPCMD_FLUSH_FIFO;
I 8
		DELAY(1);
E 8
		printf("%s: target %d not responding\n",
D 8
		    xname, sc->sc_targ);
E 8
I 8
		    sc->sc_dev.dv_xname, sc->sc_targ);
E 8
		return (ACT_ERROR);
	}

	/*
	 * Okay, things are moving along.
	 * What were we doing the last time we did something,
	 * and did it complete normally?
	 */
D 8
	phase = sc->sc_espstat & ESPSTAT_PHASE;
E 8
	switch (sc->sc_state) {

	case S_SEL:
		/*
		 * We were selecting.  Arbitration and select are
		 * complete (because ESPINTR_DSC was not set), but
		 * there is no guarantee the command went out.
		 */
		if ((reg & (ESPINTR_SVC|ESPINTR_CMP)) !=
		    (ESPINTR_SVC|ESPINTR_CMP)) {
			esperror(sc, "selection failed");
			return (ACT_RESET);
		}
		if (sc->sc_espstep == ESPSTEP_DONE) {
			sc->sc_sentcmd = 1;
			break;
		}
		if (sc->sc_espstep == 2) {
			/*
			 * We got something other than command phase.
			 * Just pretend things are normal; the
			 * device will ask for the command later.
			 */
D 8
esperror(sc, "DIAGNOSTIC: esp step 2");
E 8
I 8
esperror(sc, "DIAG: esp step 2");
E 8
		} else if (sc->sc_espstep == 3) {
			/*
			 * Device entered command phase and then exited it
			 * before we finished handing out the command.
D 10
			 * Let this happen iff we are trying to clear the
			 * target state.
E 10
I 10
			 * Do not know how to handle this.
E 10
			 */
D 8
esperror(sc, "DIAGNOSTIC: esp step 3");
E 8
I 8
esperror(sc, "DIAG: esp step 3");
E 8
D 10
			if (!sc->sc_clearing)
				return (ACT_RESET);
E 10
		} else {
			printf("%s: mysterious esp step %d\n",
D 8
			    xname, sc->sc_espstep);
E 8
I 8
			    sc->sc_dev.dv_xname, sc->sc_espstep);
E 8
			return (ACT_RESET);
		}
I 8

E 8
		/*
		 * Part of the command may still be lodged in the FIFO.
		 */
D 8
		esp->esp_cmd = ESPCMD_FLUSH_FIFO;
E 8
I 8
		if (ESP_NFIFO(sc->sc_espfflags)) {
			esp->esp_cmd = ESPCMD_FLUSH_FIFO;
			DELAY(1);
		}
E 8
		break;

D 8
	case S_CMDSVC:
E 8
I 8
	case S_SVC:
E 8
		/*
		 * We were waiting for phase change after stuffing the command
		 * into the FIFO.  Make sure it got out.
		 */
D 8
		reg = ESP_NFIFO(esp);
		if (reg) {
esperror(sc, "DIAGNOSTIC: CMDSVC, fifo not empty");
printf("\tfifo count = %x\n", reg);
E 8
I 8
		if (ESP_NFIFO(sc->sc_espfflags)) {
esperror(sc, "DIAG: CMDSVC, fifo not empty");
E 8
			esp->esp_cmd = ESPCMD_FLUSH_FIFO;
I 8
			DELAY(1);
E 8
		} else
			sc->sc_sentcmd = 1;
		break;

D 8
	case S_IOSVC:
		/*
		 * We were waiting for phase change after I/O.
		 */
		break;

E 8
	case S_DI:
		/*
		 * We were doing DMA data in, and expecting a
		 * transfer-count-zero interrupt or a phase change.
D 8
		 * We got that; drain the pack register and
		 * handle as for data out.
E 8
I 8
		 * We got that; drain the pack register and handle
		 * as for data out -- but ignore FIFO (it should be
		 * empty, except for sync mode which we are not
		 * using anyway).
E 8
		 */
I 8
		DMAWAIT(dma);
E 8
		dma->dma_csr |= DMA_DRAIN;
D 8
		reg = 0;		/* FIFO auto flushed? */
E 8
I 8
D 9
		DELAY(1);
E 9
I 9
		DMAWAIT1(dma);
E 9
		resid = 0;
E 8
		goto dma_data_done;

	case S_DO:
		/*
		 * We were doing DMA data out.  If there is data in the
		 * FIFO, it is stuff that got DMAed out but never made
		 * it to the device, so it counts as residual.
D 8
		 *
		 * XXX	handle DMA IO with large count or address
		 *	boundary condition by resuming here, or below?
E 8
		 */
D 8
		if ((reg = ESP_NFIFO(esp)) != 0)
E 8
I 8
		if ((resid = ESP_NFIFO(sc->sc_espfflags)) != 0) {
E 8
			esp->esp_cmd = ESPCMD_FLUSH_FIFO;
I 8
			DELAY(1);
		}
E 8
dma_data_done:
		if (sc->sc_dmaactive == 0) {
D 8
			printf("%s: dma done while %s, dmaactive==0\n",
			    xname, espstates[sc->sc_state]);
E 8
I 8
			esperror(sc, "dma done w/o dmaactive");
E 8
			panic("espact");
		}
		sc->sc_dmaactive = 0;
D 8
		reg += esp->esp_tcl | (esp->esp_tch << 8);
E 8
I 8

		/* Finish computing residual count. */
		reg = esp->esp_tcl | (esp->esp_tch << 8);
E 8
		if (reg == 0 && (sc->sc_espstat & ESPSTAT_TC) == 0)
			reg = 65536;
D 8
		if (reg > sc->sc_resid) {
E 8
I 8
		resid += reg;

		/* Compute xfer count (requested - resid). */
		i = sc->sc_dmasize - resid;
		if (i < 0) {
E 8
			printf("%s: xfer resid (%d) > xfer req (%d)\n",
D 8
			    xname, reg, sc->sc_resid);
			reg = sc->sc_resid;
E 8
I 8
			    sc->sc_dev.dv_xname, resid, sc->sc_dmasize);
			i = sc->sc_dmasize;	/* forgiving... */
E 8
		}
D 8
		/*
		 * If data came in we must flush cache.
		 */
E 8
I 8

		/* If data came in we must flush cache. */
E 8
		if (sc->sc_state == S_DI)
D 8
			cache_flush(sc->sc_dmaaddr, sc->sc_resid - reg);
		sc->sc_resid = reg;
E 8
I 8
			cache_flush(sc->sc_dmaaddr, i);
		sc->sc_dmaaddr += i;
		sc->sc_resid -= i;
E 8
		if ((sc->sc_espintr & ESPINTR_SVC) == 0) {
D 8
			printf("%s: no bus service req\n", xname);
E 8
I 8
			esperror(sc, "no bus service req");
E 8
			return (ACT_RESET);
		}
		break;

	case S_STAT:
		/*
		 * The last thing we did was tell it `initiator complete'
		 * and so we expect to have gotten both the status byte
		 * and the final message byte.  It is possible that we
		 * got something else....
		 *
		 * Apparently, BUS SERVICE is set if we got just status,
		 * while FUNCTION COMPLETE is set if we got both.
		 */
		if ((reg & (ESPINTR_SVC|ESPINTR_CMP)) != ESPINTR_CMP) {
			esperror(sc, "bad status interrupt state");
			return (ACT_RESET);
		}
D 8
		reg = ESP_NFIFO(esp);
E 8
I 8
		reg = ESP_NFIFO(sc->sc_espfflags);
E 8
		if (reg < 2) {
			printf(
D 8
		"%s: command done but fifo count = %d; must be >= 2\n", xname,
			    reg);
E 8
I 8
		"%s: command done but fifo count = %d; must be >= 2\n",
			    sc->sc_dev.dv_xname, reg);
E 8
			return (ACT_RESET);
		}
		/*
		 * Read the status and the first msg byte.
		 * It should be CMD_COMPLETE.  Eventually we
		 * may handle IDENTIFY, DISCONNECT, etc., as well.
		 */
		sc->sc_stat[0] = esp->esp_fifo;
		sc->sc_msg[0] = reg = esp->esp_fifo;
		esp->esp_cmd = ESPCMD_MSG_ACCEPT;
		if (reg == MSG_CMD_COMPLETE) {
			sc->sc_state = S_FI;
			return (ACT_CONT);
		}
		if (SCSIMSGLEN(reg) != 1) {
			printf("%s: target %d is naughty\n",
D 8
			    xname, sc->sc_targ);
E 8
I 8
			    sc->sc_dev.dv_xname, sc->sc_targ);
E 8
			return (ACT_RESET);
		}
		printf("%s: warning: target %d returned msg 0x%x\n",
D 8
		    xname, sc->sc_targ, reg);
E 8
I 8
		    sc->sc_dev.dv_xname, sc->sc_targ, reg);
E 8
		sc->sc_state = S_FI;
		return (ACT_CONT);

	case S_MI:
		if ((reg & ESPINTR_SVC) == 0) {
			esperror(sc, "missing phase after msg in");
			return (ACT_RESET);
		}
D 8
		reg = ESP_NFIFO(esp);
E 8
I 8
		reg = ESP_NFIFO(sc->sc_espfflags);
E 8
		for (i = 0; i < reg; i++)
			sc->sc_msg[i] = esp->esp_fifo;
		break;

	case S_FI:
		esperror(sc, "target did not disconnect");
		return (ACT_RESET);
	}

	/*
	 * Things are still moving along.  The phase tells us
	 * what the device wants next.  Do it.
	 */
D 8
	switch (phase) {
E 8
I 8
	switch (sc->sc_espstat & ESPSTAT_PHASE) {
E 8

	case ESPPHASE_DATA_OUT:
D 8
if (!sc->sc_sentcmd) esperror(sc, "DIAGNOSTIC: data out without command");
		sc->sc_state = S_DO;
		return (ACT_WRITE);
E 8
I 8
if (!sc->sc_sentcmd) esperror(sc, "DIAG: data out without command");
		if (sc->sc_dmactl & DMA_READ) {
			esperror(sc, "wrong phase (want to read)");
			return (ACT_RESET);
		}
		newstate = S_DO;
		goto do_data_xfer;
E 8

	case ESPPHASE_DATA_IN:
D 8
if (!sc->sc_sentcmd) esperror(sc, "DIAGNOSTIC: data in without command");
		sc->sc_state = S_DI;
		return (ACT_READ);
E 8
I 8
if (!sc->sc_sentcmd) esperror(sc, "DIAG: data in without command");
		if (!(sc->sc_dmactl & DMA_READ)) {
			esperror(sc, "wrong phase (want to write)");
			return (ACT_RESET);
		}
		newstate = S_DI;
do_data_xfer:
		if (sc->sc_resid == 0) {
			esperror(sc, "data count error");
			return (ACT_RESET);
		}
E 8

I 8
		/*
		 * Compute DMA count based on chip limits.
		 * Set DMA address and load transfer count into
		 * ESP via DMA NOP, then set DMA control, and
		 * then we can start the DMA.
		 */
		sc->sc_state = newstate;
		i = min(sc->sc_resid, ESPMAX);
		i = min(i, DMAMAX(sc->sc_dmaaddr));
		sc->sc_dmasize = i;
		dma->dma_addr = sc->sc_dmaaddr;
		esp->esp_tch = i >> 8;
		esp->esp_tcl = i;
		esp->esp_cmd = ESPCMD_DMA | ESPCMD_NOP;
		dma->dma_csr = sc->sc_dmactl;
		sc->sc_dmaactive = 1;
		esp->esp_cmd = ESPCMD_DMA | ESPCMD_XFER_INFO;
		return (ACT_IO);

E 8
	case ESPPHASE_CMD:
		/*
		 * Silly thing wants the command again.
D 8
		 * Load it into the FIFO and go to CMDSVC state.
E 8
I 8
		 * Load it into the FIFO and go to SVC state.
E 8
		 */
D 8
printf("%s: redoing command\n", xname);
E 8
I 8
printf("%s: redoing command\n", sc->sc_dev.dv_xname);
		cdb = sc->sc_curcdb;
E 8
		reg = SCSICMDLEN(cdb->cdb_bytes[0]);
		for (i = 0; i < reg; i++)
			esp->esp_fifo = cdb->cdb_bytes[i];
D 8
		sc->sc_state = S_CMDSVC;
E 8
I 8
		sc->sc_state = S_SVC;
E 8
		esp->esp_cmd = ESPCMD_XFER_INFO;
		return (ACT_CONT);

	case ESPPHASE_STATUS:
		sc->sc_state = S_STAT;
		esp->esp_cmd = ESPCMD_INIT_COMP;
		return (ACT_CONT);

	case ESPPHASE_MSG_IN:
D 8
printf("%s: accepting (& ignoring) msg from target %d\n", xname, sc->sc_targ);
E 8
I 8
printf("%s: accepting (& ignoring) msg from target %d\n",
    sc->sc_dev.dv_xname, sc->sc_targ);
E 8
		sc->sc_state = S_MI;
		esp->esp_cmd = ESPCMD_MSG_ACCEPT;
		return (ACT_CONT);

	default:
D 8
		printf("%s: target %d asked for strange phase (%s)\n",
		    xname, sc->sc_targ, espphases[phase]);
E 8
I 8
		esperror(sc, "bad phase");
E 8
		return (ACT_RESET);
	}
	/* NOTREACHED */
}

/*
D 8
 * Issue a select, loading command into the FIFO.
 * Return nonzero on error, 0 if OK.
 * Sets state to `selecting'; espact() will sequence state FSM.
 */
void
espselect(sc, esp, targ, cdb)
	register struct esp_softc *sc;
	register volatile struct espreg *esp;
	register int targ;
	register struct scsi_cdb *cdb;
{
	register int i, cmdlen = SCSICMDLEN(cdb->cdb_bytes[0]);

	sc->sc_targ = targ;
	sc->sc_state = S_SEL;
	sc->sc_sentcmd = 0;
	sc->sc_stat[0] = 0xff;		/* ??? */
	sc->sc_msg[0] = 0xff;		/* ??? */

	/*
	 * Try to talk to target.
	 * Synch offset 0 => asynchronous transfer.
	 */
	esp->esp_id = targ;
	esp->esp_syncoff = 0;

	/*
	 * Stuff the command bytes into the fifo.
	 * Select without attention since we do not do disconnect yet.
	 */
	for (i = 0; i < cmdlen; i++)
		esp->esp_fifo = cdb->cdb_bytes[i];
	esp->esp_cmd = ESPCMD_SEL_NATN;
	/* the rest is done elsewhere */
}

/*
 * THIS SHOULD BE ADJUSTABLE
 */
	/* name		howlong		purpose */
#define	SELECT_WAIT	300000		/* wait for select to complete */
#define	CMD_WAIT	1000		/* wait for next phase, generic */
#define	IO_WAIT		1000000		/* time to xfer data in/out */
#define	POSTDATA_WAIT	10000000	/* wait for next phase, after dataio */

/*
 * Transfer data out via polling.  Return success (0) iff all
 * the bytes were sent and we got an interrupt.
 *
 * This returns -1 on timeout, resid count on early interrupt,
 * but no one really cares....
 */
static int
espixfer_out(sc, esp, dma, buf, len)
	register struct esp_softc *sc;
	register volatile struct espreg *esp;
	register volatile struct dmareg *dma;
	register caddr_t buf;
	register int len;
{
	register int wait, n;

	if (CROSS_DMA(buf, len))
		panic("espixfer_out: 16MB boundary");

	/* set dma address and transfer count */
	dma->dma_addr = (int)buf;
	esp->esp_tch = len >> 8;
	esp->esp_tcl = len;

	/* load count into counter via DMA NOP */
	esp->esp_cmd = ESPCMD_DMA | ESPCMD_NOP;

	/* enable dma (but not interrupts) */
	dma->dma_csr = DMA_ENA;

	/* and go */
	esp->esp_cmd = ESPCMD_DMA | ESPCMD_XFER_INFO;

	/* wait for completion */
	for (wait = IO_WAIT; wait > 0; --wait) {
		n = dma->dma_csr;
		if (DMA_INTR(n)) {
			sc->sc_espstat = esp->esp_stat;
			sc->sc_espstep = esp->esp_step & ESPSTEP_MASK;
			sc->sc_espintr = esp->esp_intr;
			sc->sc_dmacsr = n;
			n = esp->esp_tcl | (esp->esp_tch << 8);
			if (n == 0 && (sc->sc_espstat & ESPSTAT_TC) == 0)
				n = 65536;

			return (n);
		}
		DELAY(1);
	}
	return (-1);
}

/*
 * Transfer data in via polling.
 * Return resid count on interrupt, -1 if timed out.
 */
static int
espixfer_in(sc, esp, dma, buf, len)
	register struct esp_softc *sc;
	register volatile struct espreg *esp;
	register volatile struct dmareg *dma;
	register caddr_t buf;
	register int len;
{
	register int wait, n;

	if (CROSS_DMA(buf, len))
		panic("espixfer_in: 16MB boundary");

	/* set dma address and transfer count */
	dma->dma_addr = (int)buf;
	esp->esp_tch = len >> 8;
	esp->esp_tcl = len;

	/* load count into counter via DMA NOP */
	esp->esp_cmd = ESPCMD_DMA | ESPCMD_NOP;

	/* enable dma (but not interrupts) */
	dma->dma_csr = DMA_ENA | DMA_READ;

	/* and go */
	esp->esp_cmd = ESPCMD_DMA | ESPCMD_XFER_INFO;

	/* wait for completion */
	for (wait = IO_WAIT; wait > 0; --wait) {
		n = dma->dma_csr;
		if (DMA_INTR(n)) {
			sc->sc_espstat = esp->esp_stat;
			sc->sc_espstep = esp->esp_step & ESPSTEP_MASK;
			sc->sc_espintr = esp->esp_intr;
			dma->dma_csr |= DMA_DRAIN;
			sc->sc_dmacsr = n;
			n = esp->esp_tcl | (esp->esp_tch << 8);
			if (n == 0 && (sc->sc_espstat & ESPSTAT_TC) == 0)
				n = 65536;

			cache_flush(buf, (u_int)len - n);
			return (n);
		}
		DELAY(1);
	}
	return (-1);
}

/*
E 8
D 10
 * Clear out target state by doing a special TEST UNIT READY.
 * Note that this calls espicmd (possibly recursively).
 */
void
espclear(sc, targ)
	register struct esp_softc *sc;
	register int targ;
{

	/* turn off needclear immediately since this calls espicmd() again */
	sc->sc_needclear &= ~(1 << targ);
	sc->sc_clearing = 1;
	(void) scsi_test_unit_ready(&sc->sc_hba, targ, 0);
	sc->sc_clearing = 0;
}

/*
E 10
I 8
 * THIS SHOULD BE ADJUSTABLE
 */
	/* name		howlong		purpose */
#define	SELECT_WAIT	300000		/* wait for select to complete */
#define	CMD_WAIT	100000		/* wait for next phase, generic */
#define	DATA_WAIT	100000		/* time to xfer data in/out */

/*
E 8
 * Send an `immediate' command, i.e., poll until the whole thing is done.
D 8
 * Return the status byte from the device, or -1 if we timed out.
E 8
I 8
 * Return the status byte from the device, or -1 if we timed out.  We use
 * DMA to transfer the data as the fifo only moves one byte at a time.
E 8
 */
int
espicmd(hba, targ, cdb, buf, len, rw)
D 8
	register struct hba_softc *hba;
E 8
I 8
	struct hba_softc *hba;
E 8
	int targ;
D 8
	register struct scsi_cdb *cdb;
E 8
I 8
	struct scsi_cdb *cdb;
E 8
	caddr_t buf;
D 8
	register int len;
	int rw;
E 8
I 8
	int len, rw;
E 8
{
	register struct esp_softc *sc = (struct esp_softc *)hba;
	register volatile struct espreg *esp = sc->sc_esp;
	register volatile struct dmareg *dma = sc->sc_dma;
D 9
	register int r, wait;
E 9
I 9
	register int r, s, wait;
	register struct sq *sq;
E 9
D 8
	char *msg;
E 8

D 8
	if ((unsigned)len > MAX_TRANSFER_SIZE) {
		printf("%s: bad length %d\n", sc->sc_hba.hba_dev.dv_xname, len);
		panic("espicmd");
	}

E 8
	/*
I 9
	 * Wait for any ongoing operation to complete.
	 */
	s = splbio();
	while (sc->sc_state != S_IDLE) {
		sc->sc_iwant = 1;
		tsleep((caddr_t)&sc->sc_iwant, PRIBIO, "espicmd", 0);
	}
	sc->sc_hba.hba_busy = 1;
	splx(s);

	/*
E 9
D 10
	 * Clear the target if necessary.
	 */
	if (sc->sc_needclear & (1 << targ) && !sc->sc_probing)
		espclear(sc, targ);

	/*
E 10
D 8
	 * Disable hardware interrupts, start select sequence.
	 * Wait for interrupt-pending bit, then call espact() to
	 * sequence the state machine.  When it tells us to do
	 * data transfer, we do programmed I/O.
	 * In any case, we loop calling espact() until done.
E 8
I 8
	 * Set up DMA transfer control (leaving interrupts disabled).
E 8
	 */
D 8
	dma->dma_csr = 0;	/* disable hardware interrupts */
	espselect(sc, esp, targ, cdb);
E 8
I 8
	sc->sc_dmactl = rw & B_READ ? DMA_ENA | DMA_READ : DMA_ENA;
	sc->sc_dmaaddr = (u_long)buf;
	sc->sc_resid = len;

	/*
	 * Disable hardware interrupts and start select sequence,
	 * then loop, calling espact() after each ``interrupt''.
	 */
	DMAWAIT(dma);		/* ??? */
	dma->dma_csr = 0;
	espselect(sc, targ, cdb);
E 8
	wait = SELECT_WAIT;
D 8
loop:
E 8
	for (;;) {
		r = dma->dma_csr;
		if (!DMA_INTR(r)) {
			if (--wait < 0) {
D 8
				msg = "timeout waiting for phase change";
				goto err;
E 8
I 8
				esperror(sc, "timeout");
				goto reset;
E 8
			}
			DELAY(1);
			continue;
		}
D 8
		break;
	}
	sc->sc_espstat = esp->esp_stat;
	sc->sc_espstep = esp->esp_step & ESPSTEP_MASK;
	sc->sc_espintr = esp->esp_intr;
	sc->sc_dmacsr = r;
	/*
	 * The action happens `twice around' for read and write.
	 * All the rest `goto loop' or return or some such.
	 */
	wait = CMD_WAIT;
	for (;;) {
		switch (r = espact(sc, esp, dma, cdb)) {
E 8
I 8
		sc->sc_espstat = esp->esp_stat;
		sc->sc_espstep = esp->esp_step & ESPSTEP_MASK;
		sc->sc_espintr = esp->esp_intr;
		sc->sc_espfflags = esp->esp_fflags;
		sc->sc_dmacsr = r;
		switch (r = espact(sc)) {
E 8

		case ACT_CONT:
		case ACT_QUICKINTR:
D 8
			goto loop;

		case ACT_READ:
			if (len == 0 || (rw & B_READ) == 0) {
				msg = "wrong phase";
				goto err;
			}
			r = espixfer_in(sc, esp, dma, buf, len);
			if (r < 0) {
				msg = "timeout reading from device";
				goto err;
			}
			buf += len - r;
			len = r;
			/* we did the io, expecting `generic service' */
			sc->sc_state = S_IOSVC;
			wait = POSTDATA_WAIT;
E 8
I 8
			wait = CMD_WAIT;
E 8
			break;

D 8
		case ACT_WRITE:
			if (len == 0 || rw & B_READ) {
				msg = "wrong phase";
				goto err;
			}
			if (espixfer_out(sc, esp, dma, buf, len)) {
				msg = "timeout writing to device";
				goto err;
			}
			sc->sc_state = S_IOSVC;
			wait = POSTDATA_WAIT;
E 8
I 8
		case ACT_IO:
			wait = DATA_WAIT;
E 8
			break;

		case ACT_RESET:
D 9
			sc->sc_state = S_IDLE;
E 9
			goto reset;

		case ACT_DONE:
D 9
			sc->sc_state = S_IDLE;
			return (sc->sc_stat[0]);
E 9
I 9
			r = sc->sc_stat[0];
			goto done;
E 9

		case ACT_ERROR:
D 9
			sc->sc_state = S_IDLE;
			return (-1);
E 9
I 9
			r = -1;
			goto done;
E 9

		default:
			panic("espicmd action");
		}
	}
D 8
err:
	printf("%s: target %d: %s (phase = %s)\n",
	    sc->sc_hba.hba_dev.dv_xname, targ, msg,
	    espphases[sc->sc_espstat & ESPSTAT_PHASE]);
E 8
reset:
D 8
	espreset(sc);		/* ??? */
E 8
I 8
	espreset(sc, RESET_ESPCHIP);		/* ??? */
E 8
D 9
	return (-1);
E 9
I 9
	r = -1;
done:
	sc->sc_state = S_IDLE;
	s = splbio();
	if (sc->sc_iwant) {
		sc->sc_iwant = 0;
		wakeup((caddr_t)&sc->sc_iwant);
	} else if ((sq = sc->sc_hba.hba_head) != NULL) {
		sc->sc_hba.hba_head = sq->sq_forw;
		(*sq->sq_dgo)(sq->sq_dev, &sc->sc_cdbspace);
	} else
		sc->sc_hba.hba_busy = 0;
	splx(s);
	return (r);
E 9
}

/*
 * Dump (write memory, possibly physmem).
 * SPARC higher-level dump code always provides virtual addresses,
 * so we need not do any I/O mapping here.
 */
int
espdump(hba, targ, cdb, buf, len)
	register struct hba_softc *hba;
	int targ;
D 8
	register struct scsi_cdb *cdb;
E 8
I 8
	struct scsi_cdb *cdb;
E 8
	caddr_t buf;
	register int len;
{
I 9
	register struct esp_softc *sc = (struct esp_softc *)hba;
E 9

I 9
	/*
	 * If we crashed in the middle of a bus transaction...
	 */
	if (sc->sc_state != S_IDLE)
		espreset(sc, RESET_BOTH);       /* ??? */
E 9
	return (espicmd(hba, targ, cdb, buf, len, B_WRITE));
}

/*
 * Allocate resources (SCSI bus and DVMA space) for the given transfer.
 * Must be called at splbio().
 *
 * THIS SHOULD RETURN SUCCESS/FAIL INDICATION
 */
void
espstart(self, sq, bp, dgo, dev)
	struct device *self;
	register struct sq *sq;
	struct buf *bp;
	scdgo_fn dgo;
	struct device *dev;
{
	register struct esp_softc *sc = (struct esp_softc *)self;

	if (sc->sc_hba.hba_busy == 0) {
		/*
		 * Bus not busy, nothing to do here, just tell
		 * this target or unit that it has the SCSI bus.
		 */
		sc->sc_hba.hba_busy = 1;
D 8
		(*dgo)(dev, &sc->sc_cdb);
E 8
I 8
		(*dgo)(dev, &sc->sc_cdbspace);
E 8
	} else {
		/*
		 * Bus is busy; just enqueue.
		 */
		sq->sq_dgo = dgo;
		sq->sq_dev = dev;
		sq->sq_forw = NULL;
		if (sc->sc_hba.hba_head == NULL)
			sc->sc_hba.hba_head = sq;
		else
			sc->sc_hba.hba_tail->sq_forw = sq;
		sc->sc_hba.hba_tail = sq;
	}
}

/*
D 8
 * Send a `dma' command, i.e., send the cdb and use DMA to send the data.
E 8
I 8
 * Start buffered I/O.
E 8
 * Return 0 on success, 1 on failure.
 */
int
espgo(self, targ, intr, dev, bp, pad)
	struct device *self;
	int targ;
	scintr_fn intr;
	struct device *dev;
	register struct buf *bp;
	int pad;
{
	register struct esp_softc *sc = (struct esp_softc *)self;
D 8
	register int len = bp->b_bcount;
	register u_long addr;
E 8

D 8
	if ((unsigned)len > MAX_TRANSFER_SIZE) {
		printf("%s: %s\n", sc->sc_hba.hba_dev.dv_xname,
		    len < 0 ? "negative length" : "transfer too big");
		return (1);
	}

E 8
D 10
	if (sc->sc_needclear & (1 << targ))
		espclear(sc, targ);

E 10
D 8
	/*
	 * Set dma registers later, on data transfer,
	 * but compute the contents now.
	 * COULD JUST REMEMBER bp HERE...?
	 *
	 * The DMA chip cannot cross a 16 MB address boundary.
	 * We should do this as multiple DMA transactions on a
	 * single SCSI command, but I have not written that yet.
	 */
	sc->sc_dmactl = bp->b_flags & B_READ ? DMA_ENA | DMA_READ | DMA_IE :
	    DMA_ENA | DMA_IE;
	addr = (u_long)bp->b_un.b_addr;
	/* dma chip cannot cross 16MB boundary  XXX */
	if (CROSS_DMA(addr, len))
		panic("dma crosses 16MB boundary: fix esp.c");
	sc->sc_dmaaddr = addr;
	sc->sc_resid = len;
E 8
I 8
	/* Set up dma control for espact(). */
	sc->sc_dmactl = bp->b_flags & B_READ ?
	    DMA_ENA | DMA_READ | DMA_IE : DMA_ENA | DMA_IE;
	sc->sc_dmaaddr = (u_long)bp->b_un.b_addr;
	sc->sc_resid = bp->b_bcount;
E 8

	/*
	 * Enable interrupts and start selection.
D 8
	 * The rest is done in our interrupt handler.
E 8
I 8
	 * The rest is done in espintr() and espact().
E 8
	 */
	sc->sc_hba.hba_intr = intr;	/* remember dev done function */
	sc->sc_hba.hba_intrdev = dev;	/* and its first arg */
	sc->sc_dma->dma_csr = DMA_IE;
D 8
	espselect(sc, sc->sc_esp, targ, &sc->sc_cdb);
E 8
I 8
	espselect(sc, targ, &sc->sc_cdbspace);
E 8
	return (0);
}

/*
 * Handle interrupt.  Return 1 if taken.
 */
int
espintr(sc0)
	void *sc0;
{
	register struct esp_softc *sc = (struct esp_softc *)sc0;
	register volatile struct espreg *esp = sc->sc_esp;
	register volatile struct dmareg *dma = sc->sc_dma;
	register int r, wait;
	register struct sq *sq;

	r = dma->dma_csr;
	if (!DMA_INTR(r))
		return (0);		/* not ours */
D 5
	sc->sc_interrupts++;
E 5
I 5
	sc->sc_intrcnt.ev_count++;
E 5

again:
	sc->sc_espstat = esp->esp_stat;
	sc->sc_espstep = esp->esp_step & ESPSTEP_MASK;
	sc->sc_espintr = esp->esp_intr;
I 8
	sc->sc_espfflags = esp->esp_fflags;
E 8
	sc->sc_dmacsr = r;

	if (sc->sc_state == S_IDLE) {
D 8
		printf("%s: stray interrupt\n", sc->sc_hba.hba_dev.dv_xname);
E 8
I 8
		printf("%s: stray interrupt\n", sc->sc_dev.dv_xname);
E 8
		dma->dma_csr &= ~DMA_IE;	/* ??? */
		return (1);
	}
D 8
	switch (r = espact(sc, esp, dma, &sc->sc_cdb)) {
E 8
I 8
	switch (r = espact(sc)) {
E 8

	case ACT_CONT:		/* just return */
I 8
	case ACT_IO:
E 8
		break;

D 8
	case ACT_READ:
	case ACT_WRITE:
		/*
		 * We have to do this ourselves since another
		 * user of espact() wants to do programmed I/O.
		 * If we already did dma, and are done, stop.
		 */
		if (sc->sc_resid == 0) {
			printf("%s: target %d sent too much data\n",
			    sc->sc_hba.hba_dev.dv_xname, sc->sc_targ);
			goto reset;
		}
		sc->sc_dmaactive = 1;
		dma->dma_addr = sc->sc_dmaaddr;
		esp->esp_tch = sc->sc_resid >> 8;
		esp->esp_tcl = sc->sc_resid;
		/* load count into counter via DMA NOP */
		esp->esp_cmd = ESPCMD_DMA | ESPCMD_NOP;
		/* enable dma */
		dma->dma_csr = sc->sc_dmactl;
		/* and go */
		esp->esp_cmd = ESPCMD_DMA | ESPCMD_XFER_INFO;
		break;

E 8
	case ACT_RESET:		/* please reset esp */
reset:
D 8
		espreset(sc);	/* ??? */
E 8
I 8
		espreset(sc, RESET_ESPCHIP);	/* ??? */
E 8
		/* FALLTHROUGH */

	case ACT_DONE:		/* this one is done, successfully */
	case ACT_ERROR:		/* this one is done due to `severe' error */
D 9
		sc->sc_state = S_IDLE;
E 9
		if (!sc->sc_hba.hba_busy)
			panic("espintr sq");
		/*
D 9
		 * This transaction is done.
		 * Call the driver's intr routine,
		 * then start the next guy if any.
E 9
I 9
		 * This transaction is done.  Call the driver's intr routine.
		 * If an immediate command is pending, let it run in front
		 * of us, otherwise start the next transation.  Note that
		 * the interrupt routine may run its own immediate commands
		 * (`request sense' for errors, eg) before we get around to
		 * the process waiting to do immediate command, but that
		 * is OK; if we did not set S_IDLE here we could deadlock.
E 9
		 */
I 9
		sc->sc_state = S_IDLE;
E 9
		(*sc->sc_hba.hba_intr)(sc->sc_hba.hba_intrdev,
		    r == ACT_DONE ? sc->sc_stat[0] : -1, sc->sc_resid);
D 9
		if ((sq = sc->sc_hba.hba_head) != NULL) {
E 9
I 9
		if (sc->sc_iwant) {
			wakeup((caddr_t)&sc->sc_iwant);
			sc->sc_iwant = 0;
		} else if ((sq = sc->sc_hba.hba_head) != NULL) {
E 9
			sc->sc_hba.hba_head = sq->sq_forw;
D 8
			(*sq->sq_dgo)(sq->sq_dev, &sc->sc_cdb);
E 8
I 8
			(*sq->sq_dgo)(sq->sq_dev, &sc->sc_cdbspace);
E 8
		} else
			sc->sc_hba.hba_busy = 0;
		break;

	case ACT_QUICKINTR:	/* wait a short while for another interrupt */
D 8
printf("%s: quickintr: ", sc->sc_hba.hba_dev.dv_xname);
E 8
I 8
printf("%s: quickintr: ", sc->sc_dev.dv_xname);
E 8
		wait = 100;
		do {
			r = dma->dma_csr;
			if (DMA_INTR(r)) {
printf("got one, wait=%d\n", wait);
				goto again;
			}
		} while (--wait > 0);
printf("did not get one\n");
		break;

	default:
		panic("espintr action");
	}
	return (1);
}

/*
 * Target or unit decided to let go of the bus early.
 */
void
esprel(self)
	struct device *self;
{
	register struct esp_softc *sc = (struct esp_softc *)self;
	register struct sq *sq;

	/* if there is someone else waiting, give them a crack at it */
D 10
	if ((sq = sc->sc_hba.hba_head) != NULL)
E 10
I 10
	if (sc->sc_iwant) {
		wakeup((caddr_t)&sc->sc_iwant);
		sc->sc_iwant = 0;
	} else if ((sq = sc->sc_hba.hba_head) != NULL) {
		sc->sc_hba.hba_head = sq->sq_forw;
E 10
D 8
		(*sq->sq_dgo)(sq->sq_dev, &sc->sc_cdb);
E 8
I 8
		(*sq->sq_dgo)(sq->sq_dev, &sc->sc_cdbspace);
E 8
D 10
	else
E 10
I 10
	} else
E 10
		sc->sc_hba.hba_busy = 0;
}
E 1
