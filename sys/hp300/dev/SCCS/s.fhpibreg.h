h06026
s 00002/00002/00059
d D 8.1 93/06/10 21:32:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00061
d D 7.3 92/10/11 09:23:46 bostic 3 2
c make kernel includes standard
e
s 00005/00001/00060
d D 7.2 92/06/05 15:31:04 hibler 2 1
c merge latest Utah hp300 code including 68040 support
e
s 00061/00000/00000
d D 7.1 90/05/08 22:06:36 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#define	vu_char	volatile u_char
E 2
I 2
D 3
#ifdef KERNEL
#include "hp/dev/iotypes.h"	/* XXX */
#else
E 3
#include <hp/dev/iotypes.h>	/* XXX */
D 3
#endif
E 3
E 2

struct	fhpibdevice {
	u_char	hpib_pad0;
	vu_char	hpib_cid;
	u_char	hpib_pad1;
#define	hpib_ie		hpib_ids
	vu_char	hpib_ids;
	u_char	hpib_pad2;
	vu_char	hpib_ctrl2;
	u_char	hpib_pad3;
	vu_char	hpib_latch;
	u_char	hpib_pad4[9];
	vu_char	hpib_intr;
	u_char	hpib_pad5;
	vu_char	hpib_imask;
	u_char	hpib_pad6;
	vu_char	hpib_data;
	u_char	hpib_pad7;
	vu_char	hpib_stat;
	u_char	hpib_pad8;
	vu_char	hpib_cmd;
	u_char	hpib_pad9;
	vu_char	hpib_ar;
	u_char	hpib_pad10;
	vu_char	hpib_pmask;
	u_char	hpib_pad11;
	vu_char	hpib_psense;
};

/* status bits */
#define	ST_READ0        0xC0
#define	ST_READ1	0x80
#define	ST_IENAB	0x80
#define	ST_EOI		0x80
#define	ST_ATN		0x40
#define	ST_WRITE	0x00

/* control bits */
#define	CT_8BIT		0x80
#define	CT_REN		0x20
#define	CT_IFC		0x10
#define	CT_FIFOSEL	0x02
#define	CT_INITFIFO	0x01

#define	IM_PABORT	0x40
#define	IM_PPRESP	0x20
#define	IM_ROOM		0x08
#define	IM_BYTE		0x04
#define	IM_IDLE		0x02

#define	AR_ARONC	0x80
E 1
