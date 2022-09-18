h05172
s 00012/00013/00055
d D 8.4 94/07/10 22:55:05 bostic 10 9
c changes for 64-bit machines
e
s 00003/00003/00065
d D 8.3 94/01/04 16:16:50 bostic 9 8
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00000/00005/00068
d D 8.2 93/12/29 20:27:25 hibler 8 7
c fix include spec, get rid of excess #endif
e
s 00002/00002/00071
d D 8.1 93/06/02 19:55:45 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00063
d D 7.5 91/02/15 14:25:04 bostic 6 5
c add Berkeley specific copyright notice
e
s 00005/00001/00068
d D 7.4 91/02/05 17:03:23 bostic 5 4
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00004/00004/00065
d D 7.3 87/12/18 11:35:17 bostic 4 3
c fix for ANSI C
e
s 00009/00007/00060
d D 7.2 86/12/14 14:49:46 sam 3 2
c add new gtco types (from pixar!sam)
e
s 00001/00001/00066
d D 7.1 86/06/04 23:29:03 mckusick 2 1
c 4.3BSD release version
e
s 00067/00000/00000
d D 6.1 85/11/06 18:20:54 sam 1 0
c date and time created 85/11/06 18:20:54 by sam
e
u
U
t
T
I 1
D 6
/*
D 2
 * Copyright (c) 1985 Regents of the University of California.
E 2
I 2
 * Copyright (c) 1985, 1986 Regents of the University of California.
E 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1985, 1986 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1985, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
E 6
 *
I 6
 * %sccs.include.redist.c%
 *
E 6
 *	%W% (Berkeley) %G%
 */

D 5
#ifndef _TABLET_
E 5
I 5
D 9
#ifndef _TABLET_H_
#define	_TABLET_H_
E 9
I 9
#ifndef _SYS_TABLET_H_
#define	_SYS_TABLET_H_
E 9

E 5
D 10
/*
E 10
 * Tablet line discipline.
 */
D 8
#ifdef KERNEL
#include "../h/ioctl.h"
#else
E 8
#include <sys/ioctl.h>
D 8
#endif
E 8

/*
D 6
 * Reads on the tablet return one of the following
 * structures, depending on the underlying tablet type.
 * The first two are defined such that a read of
 * sizeof (gtcopos) on a non-gtco tablet will return
 * meaningful info.  The in-proximity bit is simulated
 * where the tablet does not directly provide the information.
E 6
I 6
 * Reads on the tablet return one of the following structures, depending on
 * the underlying tablet type.  The first two are defined such that a read of
 * sizeof (gtcopos) on a non-gtco tablet will return meaningful info.  The
 * in-proximity bit is simulated where the tablet does not directly provide
 * the information.
E 6
 */
struct	tbpos {
D 10
	int	xpos, ypos;	/* raw x-y coordinates */
	short	status;		/* buttons/pen down */
E 10
I 10
	int32_t	xpos, ypos;	/* raw x-y coordinates */
	int16_t	status;		/* buttons/pen down */
E 10
#define	TBINPROX	0100000		/* pen in proximity of tablet */
D 10
	short	scount;		/* sample count */
E 10
I 10
	int16_t	scount;		/* sample count */
E 10
};

struct	gtcopos {
D 10
	int	xpos, ypos;	/* raw x-y coordinates */
	short	status;		/* as above */
	short	scount;		/* sample count */
	short	xtilt, ytilt;	/* raw tilt */
	short	pressure;
	short	pad;		/* pad to longword boundary */
E 10
I 10
	int32_t	xpos, ypos;	/* raw x-y coordinates */
	int16_t	status;		/* as above */
	int16_t	scount;		/* sample count */
	int16_t	xtilt, ytilt;	/* raw tilt */
	int16_t	pressure;
	int16_t	pad;		/* pad to longword boundary */
E 10
};

struct	polpos {
D 10
	short	p_x, p_y, p_z;	/* raw 3-space coordinates */
	short	p_azi, p_pit, p_rol;	/* azimuth, pitch, and roll */
	short	p_stat;		/* status, as above */
E 10
I 10
	int16_t	p_x, p_y, p_z;	/* raw 3-space coordinates */
	int16_t	p_azi, p_pit, p_rol;	/* azimuth, pitch, and roll */
	int16_t	p_stat;		/* status, as above */
E 10
	char	p_key;		/* calculator input keyboard */
};

D 4
#define BIOSMODE	_IOW(b, 1, int)		/* set mode bit(s) */
#define BIOGMODE	_IOR(b, 2, int)		/* get mode bit(s) */
E 4
I 4
#define BIOSMODE	_IOW('b', 1, int)	/* set mode bit(s) */
#define BIOGMODE	_IOR('b', 2, int)	/* get mode bit(s) */
E 4
#define	TBMODE		0xfff0		/* mode bits: */
#define		TBPOINT		0x0010		/* single point */
#define		TBRUN		0x0000		/* runs contin. */
#define		TBSTOP		0x0020		/* shut-up */
#define		TBGO		0x0000		/* ~TBSTOP */
#define	TBTYPE		0x000f		/* tablet type: */
D 3
#define		TBUNUSED	0x0000
#define		TBHITACHI	0x0001		/* hitachi tablet */
#define		TBTIGER		0x0002		/* hitachi tiger */
#define		TBGTCO		0x0003		/* gtco */
#define		TBPOL		0x0004		/* polhemus 3space */
#define		TBHDG		0x0005		/* hdg-1111b, low res */
#define		TBHDGHIRES	0x0006		/* hdg-1111b, high res */
E 3
I 3
#define		TBUNUSED	0x0
#define		TBHITACHI	0x1		/* hitachi tablet */
#define		TBTIGER		0x2		/* hitachi tiger */
#define		TBGTCO		0x3		/* gtco */
#define		TBPOL		0x4		/* polhemus 3space */
#define		TBHDG		0x5		/* hdg-1111b, low res */
#define		TBHDGHIRES	0x6		/* hdg-1111b, high res */
#define		TBDIGI		0x7		/* gtco digi-pad, low res */
#define		TBDIGIHIRES	0x8		/* gtco digi-pad, high res */
E 3
D 4
#define BIOSTYPE	_IOW(b, 3, int)		/* set tablet type */
#define BIOGTYPE	_IOR(b, 4, int)		/* get tablet type*/
E 4
I 4
#define BIOSTYPE	_IOW('b', 3, int)	/* set tablet type */
#define BIOGTYPE	_IOR('b', 4, int)	/* get tablet type*/
E 4
D 8
#endif
E 8
I 5

D 9
#endif /* !_TABLET_H_ */
E 9
I 9
#endif /* !_SYS_TABLET_H_ */
E 9
E 5
E 1
