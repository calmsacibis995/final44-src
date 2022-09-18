h23301
s 00002/00002/01015
d D 8.1 93/06/11 14:59:34 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00078/00166/00939
d D 7.3 93/03/09 23:49:17 utashiro 3 2
c cleanup header and machine dependency.
e
s 00012/00012/01093
d D 7.2 92/12/17 03:08:25 utashiro 2 1
c make kernel includes standard
e
s 01105/00000/00000
d D 7.1 92/06/04 16:03:41 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Sony Corp. and Kazumasa Utashiro of Software Research Associates, Inc.
 *
 * %sccs.include.redist.c%
 *
 * from: $Hdr: scsi.c,v 4.300 91/06/27 20:42:51 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 *	scsi.c	ver 1.1		
 */

D 2
#include "../include/fix_machine_type.h"
#include "../include/param.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 3
#include <machine/param.h>
E 2

D 2
#include "param.h"
#include "buf.h"
#include "proc.h"
#include "user.h"
E 2
I 2
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/user.h>
E 2

D 2
# include "../include/cpu.h"
E 2
I 2
# include <machine/cpu.h>
E 2

D 2
#include "../hbdev/hbvar.h"
#include "../hbdev/scsic.h"
#include "../hbdev/screg_1185.h"
E 2
I 2
#include <news3400/hbdev/hbvar.h>
#include <news3400/hbdev/scsic.h>
#include <news3400/hbdev/screg_1185.h>
E 2

D 2
#include "../iodev/scsireg.h"
#include "../iodev/ioptohb.h"
E 2
I 2
#include <news3400/iodev/scsireg.h>
#include <news3400/iodev/ioptohb.h>
E 2

#define DEBUG_LOSSBSY_HUNG

#ifdef DEBUG_LOSSBSY_HUNG
# define PROBE_MAXRETRY	100
#endif

#ifndef NO_SCSI_DISCONNECT
int Scsi_Disconnect = IDT_DISCON;
#else
int Scsi_Disconnect = 0;
#endif

# define MAXCTLR	8
struct sc_data sc_data[MAXCTLR];
struct scintsw scintsw[MAXCTLR];

#ifdef RSENSE_MSG_DISP
int	rsense_msg_disp = 1;	/* RSENSE-message display flag */
#else
int	rsense_msg_disp = 0;	/* RSENSE-message display flag */
#endif

int	mo_disp_format = 0;	/* MO format mode display flag */

struct msg_list {
	int	ml_code;		/* message code */
	int	ml_msglvl;		/* message level */
	char	*ml_msgstr;		/* message string */
};

#ifdef NO_SHRINK_RSENSE_MSG
I 3
#	define MSG(m) m
#else
#	define MSG(m) NULL
#endif

E 3
struct msg_list skeylist[] = {
D 3
	{ 0x00,	1, "No Sense" },
	{ 0x01,	0, "Recoverable Error" },
	{ 0x02,	0, "Not Ready" },
	{ 0x03,	0, "Medium Error" },
	{ 0x04,	0, "Hardware Error" },
	{ 0x05, 0, "Illegal Request" },
	{ 0x06, 1, "Unit Attention" },
	{ 0x07,	1, "Data protect" },
	{ 0x08, 0, "Blank Check" },
	{ 0x09,	0, "Vendor Unique" },
	{ 0x0a,	0, "Copy/Compare Aborted" },
	{ 0x0b, 0, "Aborted Command" },
	{ 0x0c, 0, "Equal" },
	{ 0x0d, 0, "Volume Overflow" },
	{ 0x0e,	0, "Miscompare" },
E 3
I 3
	{ 0x00,	1, MSG("No Sense") },
	{ 0x01,	0, MSG("Recoverable Error") },
	{ 0x02,	0, MSG("Not Ready") },
	{ 0x03,	0, MSG("Medium Error") },
	{ 0x04,	0, MSG("Hardware Error") },
	{ 0x05, 0, MSG("Illegal Request") },
	{ 0x06, 1, MSG("Unit Attention") },
	{ 0x07,	1, MSG("Data protect") },
	{ 0x08, 0, MSG("Blank Check") },
	{ 0x09,	0, MSG("Vendor Unique") },
	{ 0x0a,	0, MSG("Copy/Compare Aborted") },
	{ 0x0b, 0, MSG("Aborted Command") },
	{ 0x0c, 0, MSG("Equal") },
	{ 0x0d, 0, MSG("Volume Overflow") },
	{ 0x0e,	0, MSG("Miscompare") },
E 3
	{ -1,	0, (caddr_t)0 }
};
D 3
#else /* NO_SHRINK_RSENSE_MSG */
struct msg_list skeylist[] = {
	{ 0x00,	1, NULL },
	{ 0x01,	0, NULL },
	{ 0x02,	0, NULL },
	{ 0x03,	0, NULL },
	{ 0x04,	0, NULL },
	{ 0x05, 0, NULL },
	{ 0x06, 1, NULL },
	{ 0x07,	1, NULL },
	{ 0x08, 0, NULL },
	{ 0x09,	0, NULL },
	{ 0x0a,	0, NULL },
	{ 0x0b, 0, NULL },
	{ 0x0c, 0, NULL },
	{ 0x0d, 0, NULL },
	{ 0x0e,	0, NULL },
	{ -1,	0, NULL }
};
#endif /* NO_SHRINK_RSENSE_MSG */
E 3

D 3
#ifdef NO_SHRINK_RSENSE_MSG
E 3
struct msg_list ecodelist[] = {
D 3
	{ 0x00, 9, "No Additional Sense Information" },
/*HD*/	{ 0x01, 1, "No Index/Address Mark Found signal" },
	{ 0x02, 0, "No Seek Complete" },
	{ 0x03, 0, "Write Fault" },
	{ 0x04, 9, "Drive Not Ready" },
	{ 0x05, 0, "Drive Not Selected" },
/*HD*/	{ 0x06, 0, "No Track Zero" },
	{ 0x07, 0, "Multiple Drives Selected" },
	{ 0x08, 0, "Logical Unit Communication Failure" },
	{ 0x09, 2, "Track Following Error" },
/*MO*/	{ 0x0a, 1, "No Disk" },
/*MO*/	{ 0x0b, 1, "Load/Unload Failure" },
/*MO*/	{ 0x0c, 1, "Spindle Failure" },
/*MO*/	{ 0x0d, 1, "Focus Failure" },
/*MO*/	{ 0x0e, 1, "Tracking Failure" },
/*MO*/	{ 0x0f, 0, "Drive Initialization Failure" },
	{ 0x10, 1, "ID CRC or ECC error" },
	{ 0x11, 0, "Unrecoverd Read error" },
/*HD*/	{ 0x12, 0, "No Address Mark (byte sync byte) found in ID field" },
/*HD*/	{ 0x13, 0, "No Address Mark (byte sync byte) found in Data field" },
/*HD*/	{ 0x14, 0, "No record found" },
	{ 0x15, 1, "Seek Positioning Error" },
E 3
I 3
	{ 0x00, 9, MSG("No Additional Sense Information") },
/*HD*/	{ 0x01, 1, MSG("No Index/Address Mark Found signal") },
	{ 0x02, 0, MSG("No Seek Complete") },
	{ 0x03, 0, MSG("Write Fault") },
	{ 0x04, 9, MSG("Drive Not Ready") },
	{ 0x05, 0, MSG("Drive Not Selected") },
/*HD*/	{ 0x06, 0, MSG("No Track Zero") },
	{ 0x07, 0, MSG("Multiple Drives Selected") },
	{ 0x08, 0, MSG("Logical Unit Communication Failure") },
	{ 0x09, 2, MSG("Track Following Error") },
/*MO*/	{ 0x0a, 1, MSG("No Disk") },
/*MO*/	{ 0x0b, 1, MSG("Load/Unload Failure") },
/*MO*/	{ 0x0c, 1, MSG("Spindle Failure") },
/*MO*/	{ 0x0d, 1, MSG("Focus Failure") },
/*MO*/	{ 0x0e, 1, MSG("Tracking Failure") },
/*MO*/	{ 0x0f, 0, MSG("Drive Initialization Failure") },
	{ 0x10, 1, MSG("ID CRC or ECC error") },
	{ 0x11, 0, MSG("Unrecoverd Read error") },
/*HD*/	{ 0x12, 0, MSG("No Address Mark (byte sync byte) found in ID field") },
/*HD*/	{ 0x13, 0, MSG("No Address Mark (byte sync byte) found in Data field") },
/*HD*/	{ 0x14, 0, MSG("No record found") },
	{ 0x15, 1, MSG("Seek Positioning Error") },
E 3

D 3
/*HD*/	{ 0x17, 0, "Recovered Read data with Read retries" },
	{ 0x18, 0, "Recovered Read data with ECC procedure" },
/*HD*/	{ 0x19, 0, "Defect List error" },
/*HD*/	{ 0x1a, 0, "Parameter overrun" },
/*HD*/	{ 0x1b, 0, "Synchronous transfer error" },
/*HD*/	{ 0x1c, 0, "Primary Defect List not found" },
/*HD*/	{ 0x1d, 0, "Compare error" },
E 3
I 3
/*HD*/	{ 0x17, 0, MSG("Recovered Read data with Read retries") },
	{ 0x18, 0, MSG("Recovered Read data with ECC procedure") },
/*HD*/	{ 0x19, 0, MSG("Defect List error") },
/*HD*/	{ 0x1a, 0, MSG("Parameter overrun") },
/*HD*/	{ 0x1b, 0, MSG("Synchronous transfer error") },
/*HD*/	{ 0x1c, 0, MSG("Primary Defect List not found") },
/*HD*/	{ 0x1d, 0, MSG("Compare error") },
E 3

D 3
	{ 0x20, 0, "Invalid Command Operation Code" },
	{ 0x21, 0, "Illegal Logical Block Address" },
/*HD*/	{ 0x22, 0, "Illegal function for device type" },
/*MO*/	{ 0x23, 0, "Illegal function for Medium Type" },
	{ 0x24, 0, "Illegal Field in CDB" },
	{ 0x25, 0, "Invalid LUN" },
	{ 0x26, 0, "Invalid field in Parameter List" },
	{ 0x27, 0, "Write Protected" },
	{ 0x28, 1, "Medium Changed" },
	{ 0x29, 1, "Power On or Reset or Bus Device Reset Occured" },
	{ 0x2a, 1, "Mode Select Parameters Changed" },
/*HD*/	{ 0x2b, 0, "Host cannot Disconnect" },
E 3
I 3
	{ 0x20, 0, MSG("Invalid Command Operation Code") },
	{ 0x21, 0, MSG("Illegal Logical Block Address") },
/*HD*/	{ 0x22, 0, MSG("Illegal function for device type") },
/*MO*/	{ 0x23, 0, MSG("Illegal function for Medium Type") },
	{ 0x24, 0, MSG("Illegal Field in CDB") },
	{ 0x25, 0, MSG("Invalid LUN") },
	{ 0x26, 0, MSG("Invalid field in Parameter List") },
	{ 0x27, 0, MSG("Write Protected") },
	{ 0x28, 1, MSG("Medium Changed") },
	{ 0x29, 1, MSG("Power On or Reset or Bus Device Reset Occured") },
	{ 0x2a, 1, MSG("Mode Select Parameters Changed") },
/*HD*/	{ 0x2b, 0, MSG("Host cannot Disconnect") },
E 3

D 3
	{ 0x31, 0, "Medium Format Corrupted" },
	{ 0x32, 0, "No Defect Spare Location Available" },
E 3
I 3
	{ 0x31, 0, MSG("Medium Format Corrupted") },
	{ 0x32, 0, MSG("No Defect Spare Location Available") },
E 3

D 3
/*MO*/	{ 0x38, 1, "Recovered with Automatic Reallocation" },
/*MO*/	{ 0x39, 0, "Automatic Reallocation Failure" },
/*MO*/	{ 0x3a, 1, "Defect List Update Failure" },
E 3
I 3
/*MO*/	{ 0x38, 1, MSG("Recovered with Automatic Reallocation") },
/*MO*/	{ 0x39, 0, MSG("Automatic Reallocation Failure") },
/*MO*/	{ 0x3a, 1, MSG("Defect List Update Failure") },
E 3

D 3
/*MO*/	{ 0x3d, 0, "Defect List Not Available" },
E 3
I 3
/*MO*/	{ 0x3d, 0, MSG("Defect List Not Available") },
E 3

D 3
/*HD*/	{ 0x40, 0, "RAM failure" },
/*HD*/	{ 0x41, 0, "Data Path diagnostic failure" },
	{ 0x42, 0, "Power On Diagnostic Failure" },
	{ 0x43, 0, "Message Reject Error" },
	{ 0x44, 9, "Internal Controller Error" },
/*HD*/	{ 0x45, 0, "Selection/Reselection failure" },
E 3
I 3
/*HD*/	{ 0x40, 0, MSG("RAM failure") },
/*HD*/	{ 0x41, 0, MSG("Data Path diagnostic failure") },
	{ 0x42, 0, MSG("Power On Diagnostic Failure") },
	{ 0x43, 0, MSG("Message Reject Error") },
	{ 0x44, 9, MSG("Internal Controller Error") },
/*HD*/	{ 0x45, 0, MSG("Selection/Reselection failure") },
E 3

D 3
	{ 0x47, 0, "SCSI Interface Parity Error" },
	{ 0x48, 0, "Initiator Detected Error" },
	{ 0x49, 0, "Inappropriate/Illegal Message" },
E 3
I 3
	{ 0x47, 0, MSG("SCSI Interface Parity Error") },
	{ 0x48, 0, MSG("Initiator Detected Error") },
	{ 0x49, 0, MSG("Inappropriate/Illegal Message") },
E 3

D 3
	{ 0x64, 1, "Illegal mode for this track" },
E 3
I 3
	{ 0x64, 1, MSG("Illegal mode for this track") },
E 3

	{ -1,   0, (caddr_t)0 }
};
D 3
#else /* NO_SHRINK_RSENSE_MSG */
struct msg_list ecodelist[] = {
	{ 0x00, 9, NULL },
/*HD*/	{ 0x01, 1, NULL },
	{ 0x02, 0, NULL },
	{ 0x03, 0, NULL },
	{ 0x04, 9, NULL },
	{ 0x05, 0, NULL },
/*HD*/	{ 0x06, 0, NULL },
	{ 0x07, 0, NULL },
	{ 0x08, 0, NULL },
	{ 0x09, 2, NULL },
/*MO*/	{ 0x0a, 1, NULL },
/*MO*/	{ 0x0b, 1, NULL },
/*MO*/	{ 0x0c, 1, NULL },
/*MO*/	{ 0x0d, 1, NULL },
/*MO*/	{ 0x0e, 1, NULL },
/*MO*/	{ 0x0f, 0, NULL },
	{ 0x10, 1, NULL },
	{ 0x11, 0, NULL },
/*HD*/	{ 0x12, 0, NULL },
/*HD*/	{ 0x13, 0, NULL },
/*HD*/	{ 0x14, 0, NULL },
	{ 0x15, 1, NULL },
E 3
I 3
#undef MSG
E 3

D 3
/*HD*/	{ 0x17, 0, NULL },
	{ 0x18, 0, NULL },
/*HD*/	{ 0x19, 0, NULL },
/*HD*/	{ 0x1a, 0, NULL },
/*HD*/	{ 0x1b, 0, NULL },
/*HD*/	{ 0x1c, 0, NULL },
/*HD*/	{ 0x1d, 0, NULL },

	{ 0x20, 0, NULL },
	{ 0x21, 0, NULL },
/*HD*/	{ 0x22, 0, NULL },
/*MO*/	{ 0x23, 0, NULL },
	{ 0x24, 0, NULL },
	{ 0x25, 0, NULL },
	{ 0x26, 0, NULL },
	{ 0x27, 0, NULL },
	{ 0x28, 1, NULL },
	{ 0x29, 1, NULL },
	{ 0x2a, 1, NULL },
/*HD*/	{ 0x2b, 0, NULL },

	{ 0x31, 0, NULL },
	{ 0x32, 0, NULL },

/*MO*/	{ 0x38, 1, NULL },
/*MO*/	{ 0x39, 0, NULL },
/*MO*/	{ 0x3a, 1, NULL },

/*MO*/	{ 0x3d, 0, NULL },

/*HD*/	{ 0x40, 0, NULL },
/*HD*/	{ 0x41, 0, NULL },
	{ 0x42, 0, NULL },
	{ 0x43, 0, NULL },
	{ 0x44, 9, NULL },
/*HD*/	{ 0x45, 0, NULL },

	{ 0x47, 0, NULL },
	{ 0x48, 0, NULL },
	{ 0x49, 0, NULL },

	{ 0x64, 1, NULL },

	{ -1,   0, NULL }
};
#endif /* NO_SHRINK_RSENSE_MSG */

E 3
/*
 * Init a scsi bus.
 */
scop_init(scn)
	int	scn;
{
	static struct scsi sc;
	int chan;

	for (chan = 0; chan < MAXCTLR; chan++) {
		bzero((caddr_t)&sc, sizeof(struct scsi));
		sc.sc_cdb.un_reserved[0] = SCOP_RESET;
		sc.sc_cdb.un_reserved[1] = SCOP_RESET;

		if (!sc_busy(chan)) {
			sc_go(chan, (struct scsi *)&sc, SCSI_INTDIS);

			chan = (chan / 8 + 1) * 8;
		}
	}
}

/**************************************
	The multiple scsi bus is NOT suported by following routines.
	How about use inter like dev_t ( uper is scsi#, lower is inter ) 
	or hb_ctlr.
	probe() ga futatuarukara unit# ----- udauda. 
**************************************/

/*
 * scprobe. probe routine for mass storage controller.
 */
scprobe(im, ctlrintr, sc)
	struct iop/**/_ctlr *im;
	int (*ctlrintr)();
	register struct scsi *sc;
{
	register struct scintsw *sci;
	int s;
#ifdef DEBUG_LOSSBSY_HUNG
	int retry = 0;
#endif DEBUG_LOSSBSY_HUNG

	sci = &scintsw[im->im_intr];
	if (sci->sci_inthandler)
		return (0);

#ifdef DEBUG_LOSSBSY_HUNG
scprobe_loop:
	/* s = splsc(); */
	scop_inquiry(im->im_intr, sc, 0, SCSI_INTDIS, 4, (caddr_t)0);
	/* splx(s); */

	if (sc->sc_istatus != INST_EP) {
		if ((sc->sc_tstatus == TGST_BUSY) && (retry++ < PROBE_MAXRETRY)) {
			goto scprobe_loop;
		}
		return (0);
	}

#else /* DEBUG_LOSSBSY_HUNG */

	/* s = splsc(); */
	scop_inquiry(im->im_intr, sc, 0, SCSI_INTDIS, 4, (caddr_t)0);
	/* splx(s); */

	if (sc->sc_istatus != INST_EP)
		return (0);

#endif /* DEBUG_LOSSBSY_HUNG */

	sci->sci_inthandler = ctlrintr;
	sci->sci_ctlr = im->im_ctlr;
	return (1);
}

/*
 * ssprobe. probe routine for non-mass storage peripherals.
 */
ssprobe(ii, ctlrintr, sc)
	struct iop/**/_device *ii;
	int (*ctlrintr)();
	register struct scsi *sc;
{
	register struct scintsw *sci;
	int s;

	sci = &scintsw[ii->ii_intr];
	if (sci->sci_inthandler)
		return (0);

	/* s = splsc(); */
	scop_inquiry(ii->ii_intr, sc, 0, SCSI_INTDIS, 4, (caddr_t)0);
	/* splx(s); */

	if (sc->sc_istatus != INST_EP)
		return (0);

	sci->sci_inthandler = ctlrintr;
	sci->sci_ctlr = ii->ii_unit;
	return (1);
}

/*
 * SCOP_TST request
 */
scop_tst(intr, sc, slave, ie)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_TST;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_REZERO request
 */
scop_rezero(intr, sc, slave, ie)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_REZERO;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_REWIND request
 */
scop_rewind(intr, sc, slave, ie, imme)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie, imme;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_REZERO;
	sc->sc_tucode = imme;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_RSENSE request
 */
scop_rsense(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_RSENSE;
	sc->sc_count = count;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_RASBLK request
 */
scop_rasblk(intr, sc, slave, ie, lad)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int lad;
{
	struct sc_rab *sca = (struct sc_rab *)sc->sc_param;

	scinit(sc, slave, DEV_BSIZE);

	sca->sca_dllen = 4;
	sca->sca_dlad[0] = lad;
	sc->sc_cpoint = (u_char *)sca;

	sc->sc_ctrnscnt = 8;

	/* sc_cdb */
	sc->sc_opcode = SCOP_RASBLK;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_MERASE request
 */
scop_merase(intr, sc, slave, ie, count)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_MERASE;
	sc->sc_mtcount3 = count;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_WFMARK request
 */
scop_wfmark(intr, sc, slave, ie, count)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_WFMARK;
	count &= 0xffffff;
	sc->sc_tucount3 = count & 0xff;
	count >>= 8;
	sc->sc_tucount2 = count & 0xff;
	count >>= 8;
	sc->sc_tucount1 = count & 0xff;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_SPACE request
 */
scop_space(intr, sc, slave, ie, count, code)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register int code;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_SPACE;
	sc->sc_tucode = code;
	count &= 0xffffff;
	sc->sc_tucount3 = count & 0xff;
	count >>= 8;
	sc->sc_tucount2 = count & 0xff;
	count >>= 8;
	sc->sc_tucount1 = count & 0xff;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_INQUIRY request
 */
scop_inquiry(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_INQUIRY;
	sc->sc_count = count;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_STST request
 */
scop_stst(intr, sc, slave, ie, sw)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int sw;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_STST;
	sc->sc_switch = sw;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_RCAP request
 */
scop_rcap(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_RCAP;
	sc->sc_pmi = OFF;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_BSSRCH request
 */
scop_bssrch(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_BSSRCH;
	sc->sc_ladhi = *(short *)param;
	sc->sc_ladlo = *(short *)(param + 2);

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_WSSRCH request
 */
scop_wssrch(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_WSSRCH;
	sc->sc_ladhi = *(short *)param;
	sc->sc_ladlo = *(short *)(param + 2);

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 *
 * SCOP_EESENSE request
 * Enable/Disable Eject Request Sense
 * Write Once only supported.
 *
 */
scop_eesense(intr, sc, slave, ie, sw)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int sw;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_EESENSE;
	sc->sc_switch = sw;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_EJECT
 */
scop_eject(intr, sc, slave, ie)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_EJECT;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_RBLIM request
 */
scop_rblim(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count & 0xff;

	/* sc_cdb */
	sc->sc_opcode = SCOP_RBLIM;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_MSENSE request
 */
scop_msense(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count & 0xff;

	/* sc_cdb */
	sc->sc_opcode = SCOP_MSENSE;
	sc->sc_lad = count >> 8;
	sc->sc_count = count & 0xff;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_MSELECT request
 */
scop_mselect(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	u_char psave[20];

	bcopy((caddr_t)sc->sc_param, (caddr_t)psave, 20);
	scinit(sc, slave, DEV_BSIZE);
	bcopy((caddr_t)psave, (caddr_t)sc->sc_param, 20);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count & 0xff;

	/* sc_cdb */
	sc->sc_opcode = SCOP_MSELECT;
	sc->sc_lad = count >> 8;
	sc->sc_count = count & 0xff;

	sc_go(intr, (struct scsi *)sc, ie);
}

#ifdef SRD_MSELECT
/*
 * SCOP_MSELECT request
 */
scop_msense_OTHER_HD(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	scinit(sc, slave, DEV_BSIZE);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_MSENSE;
	sc->sc_count = count;
	sc->sc_lad = 0x3f00;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * SCOP_MSELECT request
 */
scop_mselect_OTHER_HD(intr, sc, slave, ie, count, param)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int count;
	register caddr_t param;
{
	u_char psave[20];

	bcopy((caddr_t)sc->sc_param, (caddr_t)psave, 20);
	scinit(sc, slave, DEV_BSIZE);
	bcopy((caddr_t)psave, (caddr_t)sc->sc_param, 20);

	sc->sc_cpoint = (u_char *)param;
	sc->sc_ctrnscnt = count;

	/* sc_cdb */
	sc->sc_opcode = SCOP_MSELECT;
	sc->sc_count = count;
	sc->sc_lad = 0;

	sc_go(intr, (struct scsi *)sc, ie);
}
#endif SRD_MSELECT

scop_erase(intr, sc, slave, ie)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_ERASE;
	sc->sc_tucode = 1;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * One sector programmed I/O
 */
scop_rdwr(intr, sc, slave, ie, flag, addr, lba, sectsize)
	int	intr;
	register struct scsi	*sc;
	int	slave;
	int	ie;
	int	flag;
	caddr_t	addr;
	int	lba;
	int	sectsize;
{
	scinit(sc, slave, sectsize);

	sc->sc_cpoint = (u_char *)addr;
	sc->sc_ctrnscnt = sectsize;

	/* sc_cdb */
	sc->sc_opcode = (flag & B_READ) ? SCOP_READ : SCOP_WRITE;
	sc->sc_lad = lba;
	sc->sc_count = 1;

	sc_go(intr, sc, ie);
}

/*
 * Medium allow/prevent removable
 */
scop_medrmv(intr, sc, slave, ie, sw)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
	register int sw;
{
	scinit(sc, slave, DEV_BSIZE);

	/* sc_cdb */
	sc->sc_opcode = SCOP_MEDRMV;
	sc->sc_count = sw;

	sc_go(intr, (struct scsi *)sc, ie);
}

/*
 * initialize struct scsi
 */
scinit(sc, slave, sectsize)
	register struct scsi *sc;
	int	slave;
	int	sectsize;
{
	bzero((caddr_t)sc, sizeof(struct scsi));

	sc->sc_identify = MSG_IDENT|Scsi_Disconnect|(slave & IDT_DRMASK);
	sc->sc_bytesec = sectsize;
	sc->sc_lun = slave;
}


/*
 * ABORT MESSAGE
 */
scms_abort(intr, sc, slave, ie)
	register int intr;
	register struct scsi *sc;
	register int slave;
	register int ie;
{
	bzero((caddr_t)sc, sizeof(struct scsi));

	sc->sc_identify = MSG_ABORT;

	/* sc_cdb */
	sc->sc_opcode = SCOP_TST;
	sc->sc_lun = slave;

	sc_go(intr, (struct scsi *)sc, ie);
}

sc_go(intr, sc, ie)
	int intr;
	struct scsi *sc;
	int ie;
{
	register struct sc_data *scdp;

	scdp = &sc_data[intr];

	if (sc->sc_cpoint)
		scdp->scd_vaddr = (char *)sc->sc_cpoint;
	else
		scdp->scd_vaddr = (char *)sc->sc_param;
	scdp->scd_procp = curproc;
	scdp->scd_scaddr = (char *)sc;
	scdp->scd_count = sc->sc_ctrnscnt;
	sc->sc_cpoint = (u_char *)ipc_phys(scdp->scd_vaddr);

	_sc_go(intr, sc, ie);

	if((ie & SCSI_INTEN) == 0) {
#ifdef mips
	/* if (DATAIN_PHASE_FINISHED) */
	MachFlushDCache(scdp->scd_scaddr, sizeof (struct scsi));
	if (MACH_IS_USPACE(scdp->scd_vaddr))
		panic("sc_go: user address is not supported");
	else if (MACH_IS_CACHED(scdp->scd_vaddr))
		MachFlushDCache(scdp->scd_vaddr, scdp->scd_count);
	else if (MACH_IS_MAPPED(scdp->scd_vaddr))
#ifdef notyet /* KU:XXX */
		clean_k2dcache(scdp->scd_vaddr, scdp->scd_count);
#else
		MachFlushCache(); /* Flush all caches */
#endif
#endif /* mips */
	}
}

#ifdef CPU_SINGLE
_sc_go(intr, sc, ie)
	int intr;
	struct scsi *sc;
	int ie;
{
	register int i, s;

	if((ie & SCSI_INTEN) == 0) {
		scsend(intr, ie|SCSI_NOTWAIT, sc);
		while (sc_busy(intr)) {
			splx(splscon());	/* splsc -1 */
#ifdef mc68030
			dcia();
#endif
		}
	} else {
		scsend(intr, ie, (caddr_t)sc);
	}
}
#endif /* CPU_SINGLE */

screset(chan)
	int chan;
{
	int i, s;

	s = splsc();
	printf("SCSI: screset() called ");
	scop_init(chan / 8);
	splx(s);

	for (s = 0; s < 10; s++) {
		DELAY(100000 * 10);
	}
	printf("\n");
	iop/**/reset();
}

scsisetup(bp, map, nmap)
	struct buf *bp;
	struct sc_map *map;
	int nmap;
{
	return (iop/**/setup(bp, map, nmap));
}


/*
 * transrate skey / ecode into message display ON/OFF value
 *	1 : display message
 *	0 : silence
 */
isdispmsg(code, list, count)
	register int code;
	register struct msg_list *list;
	int count;
{
	register int msglvl = 0;
	
	while (list->ml_code >= 0) {
		if (code == list->ml_code) {
			msglvl = list->ml_msglvl;
			break;
		}
		list++;
	}
	return (count >= msglvl);
}

#ifdef NO_SHRINK_RSENSE_MSG
/*
 * transrate skey / ecode into message
 */
char *
getmsg(code, list, defmsg)
	int code;
	struct msg_list *list;
	char *defmsg;
{
	while (list->ml_code >= 0) {
		if (code == list->ml_code)
			return (list->ml_msgstr);
		list++;
	}
	return (defmsg);
}
#endif /* NO_SHRINK_RSENSE_MSG */

check_chan_busy(intr, sc, slave)
	register int intr;
	register struct scsi *sc;
	register int slave;
{
	register struct sc_extnd *sce = (struct sc_extnd *)sc->sc_param;
	int	i = 0;

	if (sc->sc_istatus == INST_EP) {
		switch (sc->sc_tstatus) {

		case TGST_CC:
			scop_rsense(intr, sc, slave, SCSI_INTDIS, 18, 0);
			if (rsense_msg_disp ||
			    isdispmsg(sce->sce_skey, skeylist, 0)) {
#ifdef NO_SHRINK_RSENSE_MSG
				if (sce->sce_advalid) {
					printf("SCSI%d(block %d): %s (sense key = 0x%x)\n",
					intr,
					(sce->sce_infob1 << 24) +
					(sce->sce_infob2 << 16) +
					(sce->sce_infob3 <<  8) +
					(sce->sce_infob4),
					getmsg(sce->sce_skey, skeylist, "(reserved)"),
					sce->sce_skey);
				} else {
					printf("SCSI%d(unknown block): %s (sense key = 0x%x)\n",
					intr,
					getmsg(sce->sce_skey, skeylist, "(reserved)"),
					sce->sce_skey);
				}
#else /* NO_SHRINK_RSENSE_MSG */
				if (sce->sce_advalid) {
					printf("SCSI%d(sn %d): skey=0x%x)\n",
					intr,
					(sce->sce_infob1 << 24) +
					(sce->sce_infob2 << 16) +
					(sce->sce_infob3 <<  8) +
					(sce->sce_infob4),
					sce->sce_skey);
				} else {
					printf("SCSI%d: skey=0x%x)\n",
					intr, sce->sce_skey);
				}
#endif /* NO_SHRINK_RSENSE_MSG */
				printf("sense data = ");
				for (i = 0; i < 18; i++)
					printf("%x ", sc->sc_param[i]);
				printf("\n");
			}
			break;

		case TGST_GOOD:
			break;

		default:
			printf("SCSI%d: bad target status 0x%x\n", intr, sc->sc_tstatus);
			break;
		}
	} else {
		printf("SCSI%d: bad initiator status 0x%x\n", intr, sc->sc_istatus);
	}

	while (i++ < 100000) {
		scop_tst(intr, sc, slave, SCSI_INTDIS);
		if (sc->sc_tstatus != TGST_BUSY)
			break;
	}
	if (i > 100000)
		printf("SCSI%d: still busy after rasblk.\n", intr);
}

/***/
struct scsi_berr_bug_table {
	int model;
	int serial_l;
	int serial_h;
	int value;	/* 1:BUG, 0:NOBUG */
};
D 3

E 3
/***/
E 1
