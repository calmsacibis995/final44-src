h52478
s 00002/00002/00064
d D 8.1 93/06/10 21:20:59 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00065
d D 5.3 93/02/01 11:27:41 torek 3 2
c rcsid
e
s 00005/00000/00061
d D 5.2 92/07/23 14:00:54 torek 2 1
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00061/00000/00000
d D 5.1 92/07/10 00:03:10 torek 1 0
c date and time created 92/07/10 00:03:10 by torek
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
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratories.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * $Header: sdtrace.h,v 1.5 92/07/10 07:00:38 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: sdtrace.h,v 1.6 92/12/02 03:53:47 torek Exp $ (LBL)
E 3
 */

/*
 * SCSI disk command tracing
 */

#if defined(SDTRACE) || !defined(KERNEL)
struct sdtrace {
	struct	timeval time;	/* timestamp */
	u_int	block;		/* disk block */
	u_int	bcount;		/* # bytes transferred */
	u_char	tcode;		/* trace code */
	u_char	target;		/* target number */
	u_char	unit;		/* unit number on target */
	u_char	read;		/* read operation */
};

#define	T_START		0x01
#define	T_MKCDB		0x02
#define	T_INTR		0x03
#endif

#ifdef SDTRACE
/* Allow kernel config to override number of entries */
#ifndef NSDOPBUF
#define	NSDOPBUF 1024
#endif

struct	sdtrace sdopbuf[NSDOPBUF];
struct	sdtrace *sdopptr = sdopbuf;
int	nsdopbuf = NSDOPBUF;	/* for sdtrace */
u_long	sdopcnt;

#define	SD_TRACE(code, sc, bp) { \
	if (++sdopptr >= &sdopbuf[NSDOPBUF]) \
		sdopptr = sdopbuf; \
	microtime(&sdopptr->time); \
	sdopptr->tcode = code; \
	sdopptr->read = bp->b_flags & B_READ; \
	sdopptr->block = bp->b_blkno; \
	sdopptr->bcount = bp->b_bcount; \
	sdopptr->target = sc->sc_unit.u_targ; \
	sdopptr->unit = sc->sc_unit.u_unit; \
	++sdopcnt; \
}
#else
#define	SD_TRACE(code, sc, bp) { }
#endif
E 1
