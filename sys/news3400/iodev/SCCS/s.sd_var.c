h45238
s 00002/00002/00056
d D 8.1 93/06/11 14:59:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00058
d D 7.3 93/03/09 23:50:29 utashiro 3 2
c cleanup header and machine dependency.
e
s 00006/00014/00054
d D 7.2 92/12/17 03:08:31 utashiro 2 1
c make kernel includes standard
e
s 00068/00000/00000
d D 7.1 92/06/04 16:03:44 mckusick 1 0
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
 * from: $Hdr: sd_var.c,v 4.300 91/06/09 06:38:23 root Rel41 $ SONY
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Copyright (c) 1989 by SONY Corporation.
 */
/*
 *	sd_var.c - SCSI disk device driver
 *			variable definition file.
 */

#include "sd.h"
#if NSD > 0

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
#include "disklabel.h"
E 2
I 2
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/disklabel.h>
E 2

D 2
#if defined(news800) || defined(news1800)
# include "../iop/iopvar.h"
#endif

#if defined(news1700)
# include "../hbdev/hbvar.h"
#endif

#include "../iodev/scsireg.h"
#include "../iodev/sdreg.h"
E 2
I 2
#include <news3400/iodev/scsireg.h>
#include <news3400/iodev/sdreg.h>
E 2

struct iop/**/_ctlr *sdminfo[NSDC];
struct iop/**/_device *sddinfo[NSD];
struct iop/**/_device *sdip[NSDC][MAXSLAVE];

struct buf rsdbuf[NSD];			/* buffer for raw I/O */
struct buf csdbuf[NSD];			/* buffer for controll */
struct buf sdutab[NSD];			/* per drive buffers */

struct sdc_softc sdc_softc[NSDC];
struct sdd_softc sdd_softc[NSD];
u_char sd_b_openf[NSD][PNUM];
u_char sd_c_openf[NSD][PNUM];

struct scsi kernscsi[NSD];
struct sdst sdstdrv[NSD];
struct disklabel sdlabel[NSD];
struct size sdsizedrv[NSD][PNUM];

u_char sdc_rsense[NSDC][RSEN_CNT];

struct sync_param sd_sync_param[NSD];

int nsd = NSD;
int nsdc = NSDC;

#endif /* NSD > 0 */
E 1
