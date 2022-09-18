h02711
s 00002/00002/00213
d D 8.1 93/06/11 14:59:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00019/00214
d D 7.3 93/03/09 23:48:57 utashiro 3 2
c cleanup header and machine dependency.
e
s 00017/00019/00216
d D 7.2 92/12/17 03:08:24 utashiro 2 1
c make kernel includes standard
e
s 00235/00000/00000
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
 * from: $Hdr: psd.c,v 4.300 91/06/09 06:38:07 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Copyright (c) 1987, 1988 by SONY Corporation.
 */

/*
 * psd.c	ver 1.0
 *			Fri Mar 31 16:01:42 JST 1989
 *
 * Probe SCSI device routine
 *
 */

D 2
#include "../include/fix_machine_type.h"
E 2
I 2
D 3
#include <machine/fix_machine_type.h>
E 2

E 3
D 2
#include "param.h"
#include "buf.h"
#include "proc.h"
#include "user.h"
#include "dkstat.h"
#include "uio.h"
#include "kernel.h"
#include "ioctl.h"
#ifdef BSD4_3
#include "syslog.h"
#endif
E 2
I 2
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/dkstat.h>
#include <sys/uio.h>
#include <sys/kernel.h>
#include <sys/ioctl.h>
#include <sys/syslog.h>
E 2

D 2
#include "vm/vm.h"
E 2
I 2
#include <vm/vm.h>
E 2

#ifdef mips
D 2
#include "../include/cpu.h"
E 2
I 2
#include <machine/cpu.h>
E 2
#endif

#ifdef IPC_MRX
#include "../iop/iopvar.h"
#include "../ipc/newsipc.h"
#endif

#ifdef CPU_SINGLE
D 2
#include "../hbdev/hbvar.h"
#include "../hbdev/scsic.h"
E 2
I 2
#include <news3400/hbdev/hbvar.h>
#include <news3400/hbdev/scsic.h>
E 2
#endif

D 2
#include "../iodev/scsireg.h"
#include "../iodev/scu.h"
E 2
I 2
#include <news3400/iodev/scsireg.h>
#include <news3400/iodev/scu.h>
E 2

D 2
#include "../iodev/ioptohb.h"
E 2
I 2
#include <news3400/iodev/ioptohb.h>
E 2


#define	PROBE_MAXRETRY	100
#define	NRETRY		10
#define	MAXHRDERR	100
#define	NSCSICHAN	7

#define	NOSUCHDEV	0x7f

D 3
#ifdef news800
#define	MAXCTLR		8
#endif

#ifdef news1200
#define	MAXCTLR		8
#endif

#ifdef news1700
#define	MAXCTLR		8
#endif

#ifdef news1800
#define	MAXCTLR		8
#endif

E 3
#ifdef news3400
#define	MAXCTLR		8
#endif

#ifdef news3800
#define	MAXCTLR		16
#endif

#define	MAXSLAVE	8

struct scsi scsi[MAXCTLR];
struct sc_map scmap[MAXCTLR];
struct sc_inq scinq[MAXCTLR];

#ifdef IPC_MRX
extern int port_scsi;		/* UNIX port of SCSI */
extern int iop_scsi[];		/* IOP port of SCSI process */
#endif

#ifdef CPU_DOUBLE
extern struct scintsw scintsw[];
#endif

/*
 * Universal SCSI probe routine
 *	for mass storage controller.
 */
psdprobe(im)
	register struct iop/**/_ctlr *im;
{
	register int intr = im->im_intr;
	struct scintsw *sci;
	int ctlrintr;
	int j;
	char name[16];
	register struct sc_inq *inq = &scinq[intr];

#ifdef IPC_MRX
	int scintr();

	if (port_scsi == 0) {
		port_scsi = port_create("@scsi", scintr, -1);
		for(j = 0; j < MAXCTLR; j++) {
			if(j == 7 || j == 15)
				continue;
			iop_scsi[j] = object_query(make_name(name, "scsiportXX", j));
		}
	}
#endif /* IPC_MRX */
	sci = &scintsw[intr];
	if (sci->sci_inthandler) {
		/*
		 * already probed.
		 */
		return (-1);
	}

	/*
	 * probe device product ID
	 *	& set driver interrupt handler
	 */
	if (probe_inq(im, inq) == 0) {
		/*
		 * inquiry command terminate with bad status
		 *	set 0x7f(Specified device is nonexistent) to devtype
		 */
		inq->sci_devtype = NOSUCHDEV;
	}
	return (inq->sci_devtype);
}

set_inthandler(im, handler)
	register struct iop/**/_ctlr *im;
	int (*handler)();
{
	struct scintsw *sci;

	sci = &scintsw[im->im_intr];
	if (sci->sci_inthandler)
		return (0);	/* already probed. */

	sci->sci_inthandler = handler;
	sci->sci_ctlr = im->im_ctlr;
	return (1);
}

probe_inq(im, inq)
	register struct iop/**/_ctlr *im;
	register struct sc_inq *inq;
{
	register int intr = im->im_intr;
	register struct scsi *sc = &scsi[intr];
	register int retry = 0;
	
	bzero(inq, sizeof(struct sc_inq));

psdprobe_loop:

	scop_inquiry(intr, sc, 0, SCSI_INTDIS, sizeof(struct sc_inq), inq);

	if (sc->sc_istatus != INST_EP) {
		/*
		 * probe fault.
		 */
		if (sc->sc_istatus == (INST_EP|INST_HE)) {
			/*
			 * bus reset, retry
			 */
			goto psdprobe_loop;
		}
		return (0);
	}
#ifndef NO_STATUS_BYTE_MASK
	sc->sc_tstatus &= TGSTMASK;
D 3
#endif /* !NO_STATUS_BYTE_MASK */
E 3
I 3
#endif
E 3
	if (sc->sc_tstatus != TGST_GOOD) {
		if (sc->sc_tstatus == TGST_CC)
			scop_rsense(intr, sc, 0, SCSI_INTDIS, 18, 0);
		if (retry++ < PROBE_MAXRETRY) {
			DELAY(600000);		/* XXX  1 sec */
			goto psdprobe_loop;
		}
		/*
		 * probe fault.
		 */
		return (0);
	}
	return (1);
}

struct scsi *
get_scsi(intr)
	int	intr;
{
	return (&scsi[intr]);
}

struct sc_map *
get_sc_map(intr)
	int	intr;
{
	return (&scmap[intr]);
}

struct sc_inq *
get_sc_inq(intr)
	int	intr;
{
	return (&scinq[intr]);
}
E 1
