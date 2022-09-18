h51435
s 00002/00002/00092
d D 8.1 93/06/02 19:54:30 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00092
d D 7.8 92/03/29 20:27:57 ralph 22 21
c added MT_ISTK50 for DEC SCSI TK50 & MT02
e
s 00001/00000/00091
d D 7.7 91/09/03 18:00:15 sellgren 21 20
c Add a 9 track device
e
s 00023/00001/00068
d D 7.6 91/02/05 19:17:27 mckusick 20 19
c add support for Exabyte tape
e
s 00001/00011/00068
d D 7.5 90/06/28 21:59:50 bostic 19 18
c new copyright notice
e
s 00026/00015/00053
d D 7.4 88/08/31 14:02:03 bostic 18 17
c add Berkeley specific copyright
e
s 00004/00004/00064
d D 7.3 87/12/18 11:35:13 bostic 17 16
c fix for ANSI C
e
s 00001/00000/00067
d D 7.2 86/10/13 21:22:41 karels 16 15
c merge in tahoe system
e
s 00001/00001/00066
d D 7.1 86/06/04 23:25:30 mckusick 15 14
c 4.3BSD release version
e
s 00012/00008/00055
d D 6.4 86/02/11 17:40:03 karels 14 13
c add TMSCP, CACHE/NOCACHE
e
s 00007/00001/00056
d D 6.3 85/06/08 15:02:15 mckusick 13 12
c Add copyright
e
s 00002/00000/00055
d D 6.2 84/09/25 10:53:27 mckusick 12 11
c TU78 error recovery (ulysses!ggs)
e
s 00000/00000/00055
d D 6.1 83/07/29 06:13:15 sam 11 10
c 4.2 distribution
e
s 00000/00002/00055
d D 4.10 83/01/17 15:46:47 sam 10 9
c pull back sun mods
e
s 00006/00000/00051
d D 4.9 83/01/13 00:21:16 sam 9 8
c some stuff for suns
e
s 00009/00007/00042
d D 4.8 82/10/31 16:03:28 root 8 7
c add SUN device definitions
e
s 00004/00004/00045
d D 4.7 82/08/01 19:20:25 sam 7 6
c new ioctl's
e
s 00003/00000/00046
d D 4.6 81/11/07 10:48:27 wnj 6 5
c add tu78 and si unibus tape
e
s 00020/00012/00026
d D 4.5 81/04/02 15:20:31 root 5 4
c cleanup and mt_type
e
s 00003/00000/00035
d D 4.4 81/02/25 23:30:09 wnj 4 3
c functional version with %b printf, etc
e
s 00001/00001/00034
d D 4.3 81/02/19 21:41:24 wnj 3 2
c %G%->%E%
e
s 00002/00000/00033
d D 4.2 81/01/30 17:46:51 toy 2 1
c Added sccs id and MTNOP define
e
s 00033/00000/00000
d D 4.1 81/01/30 17:45:14 toy 1 0
c date and time created 81/01/30 17:45:14 by toy
e
u
U
t
T
I 2
D 3
/*	%M%	%I%	%G%	*/
E 3
I 3
D 13
/*	%M%	%I%	%E%	*/
E 13
I 13
/*
D 15
 * Copyright (c) 1982 Regents of the University of California.
E 15
I 15
D 18
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 15
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
D 23
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
E 18
 *
I 18
D 19
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 19
I 19
 * %sccs.include.redist.c%
E 19
 *
E 18
 *	%W% (Berkeley) %G%
 */
E 13
I 6

E 6
E 3
E 2
I 1
/*
 * Structures and definitions for mag tape io control commands
 */

D 5
/* structure for MTIOCTOP - mag tape op command */
E 5
I 5
D 7
/* mag tape io control commands */
#define MTIOCTOP	(('m'<<8)|1)	/* do a mag tape op */
#define MTIOCGET	(('m'<<8)|2)	/* get mag tape status */
E 5

E 7
I 5
/* structure for MTIOCTOP - mag tape op command */
E 5
D 18
struct	mtop	{
E 18
I 18
struct mtop {
E 18
	short	mt_op;		/* operations defined below */
D 5
	short	mt_count;	/* how many of them */
E 5
I 5
	daddr_t	mt_count;	/* how many of them */
E 5
};

D 5
/* operations: */
E 5
I 5
/* operations */
E 5
D 18
#define MTWEOF	0	/* write an end-of-file record */
#define MTFSF	1	/* forward space file */
#define MTBSF	2	/* backward space file */
#define MTFSR	3	/* forward space record */
#define MTBSR	4	/* backward space record */
#define MTREW	5	/* rewind */
#define MTOFFL	6	/* rewind and put the drive offline */
I 2
#define MTNOP	7	/* no operation, sets status only */
I 14
#define MTCACHE	8	/* enable controller cache */
#define MTNOCACHE 9	/* disable controller cache */
E 18
I 18
#define MTWEOF		0	/* write an end-of-file record */
#define MTFSF		1	/* forward space file */
#define MTBSF		2	/* backward space file */
#define MTFSR		3	/* forward space record */
#define MTBSR		4	/* backward space record */
#define MTREW		5	/* rewind */
#define MTOFFL		6	/* rewind and put the drive offline */
#define MTNOP		7	/* no operation, sets status only */
#define MTCACHE		8	/* enable controller cache */
#define MTNOCACHE	9	/* disable controller cache */
E 18
E 14
I 9
D 10
#define	MTTENSE	8	/* streamer - ??? */
#define	MTERASE	9	/* streamer - erase previous record? */
E 10
E 9
E 2

/* structure for MTIOCGET - mag tape get status command */

D 18
struct	mtget	{
E 18
I 18
struct mtget {
E 18
D 5
	short	mt_dsreg;	/* drive status register */
	short	mt_erreg;	/* error register */
E 5
I 5
	short	mt_type;	/* type of magtape device */
/* the following two registers are grossly device dependent */
	short	mt_dsreg;	/* ``drive status'' register */
	short	mt_erreg;	/* ``error'' register */
/* end device-dependent registers */
E 5
	short	mt_resid;	/* residual count */
/* the following two are not yet implemented */
D 5
	short	mt_fileno;	/* file number of current position */
	short	mt_blkno;	/* block number of current position */
E 5
I 5
	daddr_t	mt_fileno;	/* file number of current position */
	daddr_t	mt_blkno;	/* block number of current position */
/* end not yet implemented */
E 5
};

D 5
/* unfortunately the bits in these registers are grossly device dependent */
/* should be defined here but aren't */
I 4
/* mag tape io control commands */
#define MTIOCTOP	(('m'<<8)|1)	/* do a mag tape op (see <mtio.h>) */
#define MTIOCGET	(('m'<<8)|2)	/* get mag tape status (see <mtio.h>*/
E 5
I 5
/*
D 14
 * Constants for mt_type byte
E 14
I 14
 * Constants for mt_type byte.  These are the same
 * for controllers compatible with the types listed.
E 14
 */
D 8
#define MT_ISTS		01
#define MT_ISHT		02
#define MT_ISTM		03
I 6
#define MT_ISMT		04
#define MT_ISUT		05
E 8
I 8
D 14
#define	MT_ISTS		0x01
#define	MT_ISHT		0x02
#define	MT_ISTM		0x03
#define	MT_ISMT		0x04
#define	MT_ISUT		0x05
#define	MT_ISCPC	0x06
#define	MT_ISAR		0x07
E 14
I 14
#define	MT_ISTS		0x01		/* TS-11 */
#define	MT_ISHT		0x02		/* TM03 Massbus: TE16, TU45, TU77 */
#define	MT_ISTM		0x03		/* TM11/TE10 Unibus */
#define	MT_ISMT		0x04		/* TM78/TU78 Massbus */
#define	MT_ISUT		0x05		/* SI TU-45 emulation on Unibus */
#define	MT_ISCPC	0x06		/* SUN */
#define	MT_ISAR		0x07		/* SUN */
#define	MT_ISTMSCP	0x08		/* DEC TMSCP protocol (TU81, TK50) */
I 16
D 20
#define	MT_ISCY		0x09		/* CCI Cipher */
E 20
I 20
#define MT_ISCY		0x09		/* CCI Cipher */
#define MT_ISCT		0x0a		/* HP 1/4 tape */
#define MT_ISFHP	0x0b		/* HP 7980 1/2 tape */
#define MT_ISEXABYTE	0x0c		/* Exabyte */
#define MT_ISEXA8200	0x0c		/* Exabyte EXB-8200 */
#define MT_ISEXA8500	0x0d		/* Exabyte EXB-8500 */
#define MT_ISVIPER1	0x0e		/* Archive Viper-150 */
#define MT_ISPYTHON	0x0f		/* Archive Python (DAT) */
#define MT_ISHPDAT	0x10		/* HP 35450A DAT drive */
I 21
#define MT_ISMFOUR	0x11		/* M4 Data 1/2 9track drive */
I 22
#define MT_ISTK50	0x12		/* DEC SCSI TK50 */
#define MT_ISMT02	0x13		/* Emulex MT02 SCSI tape controller */
E 22
E 21
E 20
E 16
E 14
E 8
I 7

/* mag tape io control commands */
D 8
#define MTIOCTOP	_IOW(m, 1, struct mtop)		/* do a mag tape op */
#define MTIOCGET	_IOR(m, 2, struct mtget)	/* get tape status */
E 8
I 8
D 17
#define	MTIOCTOP	_IOW(m, 1, struct mtop)		/* do a mag tape op */
#define	MTIOCGET	_IOR(m, 2, struct mtget)	/* get tape status */
I 12
#define MTIOCIEOT	_IO(m, 3)			/* ignore EOT error */
#define MTIOCEEOT	_IO(m, 4)			/* enable EOT error */
E 17
I 17
#define	MTIOCTOP	_IOW('m', 1, struct mtop)	/* do a mag tape op */
#define	MTIOCGET	_IOR('m', 2, struct mtget)	/* get tape status */
#define MTIOCIEOT	_IO('m', 3)			/* ignore EOT error */
#define MTIOCEEOT	_IO('m', 4)			/* enable EOT error */
E 17
E 12
I 9

#ifndef KERNEL
#define	DEFTAPE	"/dev/rmt12"
I 20
#endif

#ifdef	KERNEL
/*
 * minor device number
 */

#define	T_UNIT		003		/* unit selection */
#define	T_NOREWIND	004		/* no rewind on close */
#define	T_DENSEL	030		/* density select */
#define	T_800BPI	000		/* select  800 bpi */
#define	T_1600BPI	010		/* select 1600 bpi */
#define	T_6250BPI	020		/* select 6250 bpi */
#define	T_BADBPI	030		/* undefined selection */
E 20
#endif
E 9
E 8
E 7
E 6
E 5
E 4
E 1
