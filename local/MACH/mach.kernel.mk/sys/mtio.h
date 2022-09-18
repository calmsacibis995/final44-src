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
 * Revision 2.9  91/08/29  22:41:22  berman
 * 	Updated some definitions for suns from SunOS 4.1.1.
 * 	[91/06/12            berman]
 * 
 * Revision 2.8  91/05/10  16:10:31  berman
 * 	Added some definitions for PMAX tape driver.
 * 	[91/05/10            berman]
 * 
 * Revision 2.7  90/08/30  11:50:28  bohman
 * 	Ioctl changes for STDC.
 * 	[90/08/28            bohman]
 * 
 * Revision 2.6  90/08/08  17:19:30  mrt
 * 	Added some DEC-specific codes.
 * 	[90/05/20  14:50:51  af]
 * 
 * Revision 2.5  90/07/06  12:59:39  mrt
 * 	Merged in more stuff for Sun tape drives from SunOS 4.0.3.
 * 	[90/05/28            jjc]
 * 
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
#define MTEOM		10	/* position to end of media (SCSI only) */
#define MTNBSF		11	/* backspace filemark */
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
#define MTCSE		0x0a		/* Clear serious exception	*/
#define MTCLX		0x0b		/* Clear hard/soft-ware problem */
#define MTCLS		0x0c		/* Clear subsystem		*/
#define MTENAEOT	0x0d		/* Enable default eot code	*/
#define MTDISEOT	0x0e		/* Disable default eot code	*/
#define MTFLUSH		0x0f		/* Flush controller write cache */
#define MTGTON		0x10		/* Turn on gapless TBC tm32	*/
#define MTGTOFF		0x11		/* Torn off gapless mode	*/
#define MTRETEN		0x12		/* Retension command qic like	*/
#endif	mips

/* structure for MTIOCGET - mag tape get status command */

struct	mtget	{
	short	mt_type;	/* type of magtape device */
/* the following two registers are grossly device dependent */
	short	mt_dsreg;	/* ``drive status'' register */
	short	mt_erreg;	/* ``error'' register */
/* end device-dependent registers */
#ifdef	sun
	daddr_t	mt_resid;	/* residual count */
#else	sun
	short	mt_resid;	/* residual count */
#endif	sun
/* the following two are not yet implemented */
	daddr_t	mt_fileno;	/* file number of current position */
	daddr_t	mt_blkno;	/* block number of current position */
/* end not yet implemented */
#if	sun
	u_short	mt_flags;
	short	mt_bf;		/* optimum blocking factor */
#endif	sun
};

#if	sun
/*
 * values for mt_flags
 */
#define MTF_SCSI	0x01
#define MTF_REEL	0x02
#define MTF_ASF		0x04
#endif	sun

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
#define	MT_ISSYSGEN11	0x10		/* sun: SCSI Sysgen, QIC-11 only */
#define	MT_ISSYSGEN	0x11		/* sun: SCSI Sysgen QIC-24/11 */
#define	MT_ISDEFAULT	0x12		/* sun: SCSI default CCS */
#define	MT_ISCCS3	0x13		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISMT02	0x14		/* sun: SCSI Emulex MT02 */
#define	MT_ISVIPER1	0x15		/* sun: SCSI Archive QIC-150 Viper */
#define	MT_ISWANGTEK1	0x16		/* sun: SCSI Wangtek QIC-150 */
#define	MT_ISCCS7	0x17		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS8	0x18		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS9	0x19		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS11	0x1a		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS12	0x1b		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS13	0x1c		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS14	0x1d		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS15	0x1e		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS16	0x1f		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCDC	0x20		/* sun: SCSI CDC 1/2" cartridge */
#define	MT_ISFUJI	0x21		/* sun: SCSI Fujitsu 1/2" cartridge */
#define	MT_ISKENNEDY	0x22		/* sun: SCSI Kennedy 1/2" reel */
#define	MT_ISHP		0x23		/* sun: SCSI HP 1/2" reel */
#define	MT_ISCCS21	0x24		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS22	0x25		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS23	0x26		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS24	0x27		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISEXABYTE	0x28		/* sun: SCSI Exabyte 8mm cartridge */
#define	MT_ISCCS26	0x29		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS27	0x2a		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS28	0x2b		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS29	0x2c		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS30	0x2d		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS31	0x2e		/* sun: SCSI generic (unknown) CCS */
#define	MT_ISCCS32	0x2f		/* sun: SCSI generic (unknown) CCS */
#endif	sun
#ifdef	mips
#define MT_ISST		0x07		/* TZK50 on VS2000/MV2000	*/
#define MT_ISSCSI	0x08		/* SCSI tapes (TZK50 & TZ30)	*/
#define MT_ISQIC	0x09		/* ISI ts11 qic-2 tape controller */
#define MT_ISSC		0x0a		/* SUN */
#define MT_ISXY		0x0b		/* SUN */
#endif	mips

#if	sun
/*
 * Device table structure and data for looking tape name from
 * tape id number.  Used by mt.c.
 */
struct mt_tape_info {
	short	t_type;		/* type of magtape device */
	char	*t_name;	/* printing name */
	char	*t_dsbits;	/* "drive status" register */
	char	*t_erbits;	/* "error" register */
};
#define MT_TAPE_INFO  {\
{ MT_ISCPC,		"TapeMaster 1/2-inch",		TMS_BITS, 0 }, \
{ MT_ISXY,		"Xylogics 472 1/2-inch",	XTS_BITS, 0 }, \
{ MT_ISAR,		"Archive QIC-11",	ARCH_CTRL_BITS,	ARCH_BITS }, \
{ MT_ISSYSGEN11,	"Sysgen QIC-11",		0, 0 }, \
{ MT_ISSYSGEN,		"Sysgen QIC-24",		0, 0 }, \
{ MT_ISMT02,		"Emulex MT-02 QIC-24",		0, 0 }, \
{ MT_ISVIPER1,		"Archive QIC-150",		0, 0 }, \
{ MT_ISWANGTEK1,	"Wangtek QIC-150",		0, 0 }, \
{ MT_ISKENNEDY,		"Kennedy 9612 1/2-inch",	0, 0 }, \
{ MT_ISHP,		"HP 88780 1/2-inch",		0, 0 }, \
{ MT_ISEXABYTE,		"Exabyte EXB-8200 8mm",		0, 0 }, \
{ 0 } \
}
#endif	sun

/* mag tape io control commands */
#ifdef	__STDC__
#define MTIOCTOP	_IOW('m', 1, struct mtop)	/* do a mag tape op */
#define MTIOCGET	_IOR('m', 2, struct mtget)	/* get tape status */
#define MTIOCIEOT	_IO('m', 3)			/* ignore EOT error */
#define MTIOCEEOT	_IO('m', 4)			/* enable EOT error */
#else
#define MTIOCTOP	_IOW(m, 1, struct mtop)		/* do a mag tape op */
#define MTIOCGET	_IOR(m, 2, struct mtget)	/* get tape status */
#define MTIOCIEOT	_IO(m, 3)			/* ignore EOT error */
#define MTIOCEEOT	_IO(m, 4)			/* enable EOT error */
#endif

#ifndef	KERNEL
#define DEFTAPE	"/dev/rmt12"
#endif	KERNEL

#if	sun
/*
 * Layout of minor device byte
 * 7    6    5    4    3    2    1    0
 * ------------------------------------
 * |    |    |    |    |    |    |----| Unit #. lower 2 bits
 * |    |    |    |    |    |---------- No rewind on close bit....
 * |    |    |    |----|--------------- Density Select
 * |    |    |------------------------- Reserved (additional campus density bit)
 * |    |------------------------------ Unit #. high bit
 * |----------------------------------- Reserved
 */

#define MTUNIT(dev)	(((minor(dev) & 0x40) >> 4) + (minor(dev) & 0x3))
#define MT_NOREWIND	(1 <<2)
#define MT_DENSITY_MASK	(3 <<3)
#define MT_DENSITY1	(0 <<3)         /* Lowest density/format */
#define MT_DENSITY2	(1 <<3)
#define MT_DENSITY3	(2 <<3)
#define MT_DENSITY4	(3 <<3)         /* Highest density/format */
#define MTMINOR(unit)	(((unit & 0x04) << 4) + (unit & 0x3))
#endif	sun

#endif	_SYS_MTIO_H_
