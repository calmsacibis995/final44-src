/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mtio.h,v $
 * Revision 2.4  89/03/09  22:06:03  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  17:55:03  gm0w
 * 	Changed romp to ibmrt.
 * 	[89/02/13            mrt]
 * 
 * Revision 2.2  89/01/23  22:27:33  af
 * 	Added controllers supported by Mips machines.
 * 	[89/01/04            af]
 * 
 *  8-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Convert to cpp symbols for multimax/balance.
 *
 * 29-Jun-87  David Kirschen (kirschen) at Encore Computer Corporation
 *      MULTIMAX: added SCSI controller type for Multimaxen
 *
 * 14-Apr-87  David Black (dlb) at Carnegie-Mellon University
 *	MULTIMAX: added machine-specific tape ioctl definitions.
 *
 *  4-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Use features.h for non-KERNEL include.
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Add some #ifdef BALANCE new MTxxx defines (Sequent specific).
 *
 *  5-Aug-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in stuff for Sun tape drives.
 *
 * 22-Mar-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged VM and Romp versions.
 *
 * 18-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added definitions of MTERASE and MTRETENSION for Sailboat under
 *	switch romp.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mtio.h	7.1 (Berkeley) 6/4/86
 */
/*
 * Structures and definitions for mag tape io control commands
 */

#ifndef	_SYS_MTIO_H_
#define _SYS_MTIO_H_

#include <sys/types.h>

/* structure for MTIOCTOP - mag tape op command */
struct	mtop	{
	short	mt_op;		/* operations defined below */
	daddr_t	mt_count;	/* how many of them */
};

/* operations */
#define MTWEOF	0	/* write an end-of-file record */
#define MTFSF	1	/* forward space file */
#define MTBSF	2	/* backward space file */
#define MTFSR	3	/* forward space record */
#define MTBSR	4	/* backward space record */
#define MTREW	5	/* rewind */
#define MTOFFL	6	/* rewind and put the drive offline */
#define MTNOP	7	/* no operation, sets status only */
#define MTCACHE	8	/* enable controller cache */
#define MTNOCACHE 9	/* disable controller cache */
#ifdef	ibmrt
#define MTERASE 18	/* for streamer: erase tape */
#define MTRETENSION 19	/* for streamer: retension tape */
#endif	ibmrt
#ifdef	sun
#define MTRETEN 8       /* retension the tape */
#define MTERASE 9       /* erase the entire tape */
#endif	sun
#ifdef	multimax
/*
 * Additional Encore-specific commands
 */
#define MTERASE	8	/* erase, valid only for streamers. */
#define MTRETEN	9	/* retension, valid only for streamers. */
#define MTEOT	10	/* space to end of data, valid only for streamers. */
#define MTFSSF	11	/* forward space sequential file */
#define MTBSSF	12	/* backward space sequential file */
#endif	multimax
#ifdef	balance
/*
 * Additional Sequent specific commands for SCSI streamer tape.
 */
#define MTERASE	8	/* Erase from current position to eot */
#define MTRET	9	/* Retention the tape (streamers) */
#define MTSEOD	10	/* Space to end of data */
#define MTNORET	11	/* don't retention the tape this time */
#endif	balance

#ifdef	mips
/* Mips specific commands */
#define MTRET	10	/* retention operation */
#define MTRST	11	/* reset operation */
#define MTERASE	12	/* secuity erase (9-track only) */
#define MTRETEN	13	/* retension the tape */
#endif	mips

/* structure for MTIOCGET - mag tape get status command */

struct	mtget	{
	short	mt_type;	/* type of magtape device */
/* the following two registers are grossly device dependent */
	short	mt_dsreg;	/* ``drive status'' register */
	short	mt_erreg;	/* ``error'' register */
/* end device-dependent registers */
	short	mt_resid;	/* residual count */
/* the following two are not yet implemented */
	daddr_t	mt_fileno;	/* file number of current position */
	daddr_t	mt_blkno;	/* block number of current position */
/* end not yet implemented */
};

/*
 * Constants for mt_type byte.  These are the same
 * for controllers compatible with the types listed.
 */
#define MT_ISTS		0x01		/* TS-11 */
#define MT_ISHT		0x02		/* TM03 Massbus: TE16, TU45, TU77 */
#define MT_ISTM		0x03		/* TM11/TE10 Unibus */
#define MT_ISMT		0x04		/* TM78/TU78 Massbus */
#define MT_ISUT		0x05		/* SI TU-45 emulation on Unibus */
#define MT_ISCPC	0x06		/* SUN */
#define MT_ISAR		0x07		/* SUN */
#define MT_ISTMSCP	0x08		/* DEC TMSCP protocol (TU81, TK50) */
#ifdef	multimax
#define MT_ISCSI        0x08            /* Multimax SCSI Tape controller */
#endif	multimax
#ifdef	ibmrt
#define MT_ISST		0x08
#endif	ibmrt
#ifdef	sun
#define MT_ISSC         0x08            /* sun: SCSI archive */
#define MT_ISXY         0x09            /* sun: Xylogics 472 */
#endif	sun
#ifdef	mips
#define MT_ISQIC	0x09		/* ISI ts11 qic-2 tape controller */
#define MT_ISSC		0x0a		/* SUN */
#define MT_ISXY		0x0b		/* SUN */
#endif	mips

/* mag tape io control commands */
#define MTIOCTOP	_IOW(m, 1, struct mtop)		/* do a mag tape op */
#define MTIOCGET	_IOR(m, 2, struct mtget)	/* get tape status */
#define MTIOCIEOT	_IO(m, 3)			/* ignore EOT error */
#define MTIOCEEOT	_IO(m, 4)			/* enable EOT error */

#ifndef	KERNEL
#define DEFTAPE	"/dev/rmt12"
#endif	KERNEL
#endif	_SYS_MTIO_H_
