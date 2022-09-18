h08742
s 00002/00002/00072
d D 8.1 93/06/10 21:33:45 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00074
d D 7.3 92/10/11 09:24:05 bostic 3 2
c make kernel includes standard
e
s 00035/00030/00043
d D 7.2 92/06/05 15:31:43 hibler 2 1
c merge latest Utah hp300 code including 68040 support
e
s 00073/00000/00000
d D 7.1 90/05/08 22:06:47 mckusick 1 0
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

I 2
struct	nhpibdevice {
	u_char	hpib_pad0;
	vu_char	hpib_cid;
	u_char	hpib_pad1;
#define	hpib_ie		hpib_ids
	vu_char	hpib_ids;
	u_char	hpib_pad2;
	vu_char	hpib_csa;
	u_char	hpib_pad3[11];
#define	hpib_mim	hpib_mis
	vu_char	hpib_mis;
	u_char	hpib_pad4;
#define	hpib_lim	hpib_lis
	vu_char	hpib_lis;
	u_char	hpib_pad5;
	vu_char	hpib_is;
	u_char	hpib_pad6;
#define	hpib_acr	hpib_cls
	vu_char	hpib_cls;
	u_char	hpib_pad7;
	vu_char	hpib_ar;
	u_char	hpib_pad8;
	vu_char	hpib_sprb;
	u_char	hpib_pad9;
#define	hpib_ppr	hpib_cpt
	vu_char	hpib_cpt;
	u_char	hpib_pad10;
	vu_char	hpib_data;
};

E 2
#define	LIS_SRQ		0x02
#define	LIS_ERR		0x40

#define	MIS_END		0x08
#define	MIS_BO		0x10
#define	MIS_BI		0x20

#define	IS_TADS		0x02
#define	IS_LADS		0x04

#define	AUX_CSWRST	0
#define	AUX_RHDF	2
#define	AUX_CHDFA	3
#define	AUX_CHDFE	4
#define	AUX_EOI		8
#define	AUX_GTS		11
#define	AUX_TCA		12
#define	AUX_TCS		13
#define	AUX_CPP		14
#define	AUX_CSIC	15
#define	AUX_CSRE	16
#define	AUX_CDAI	19
#define	AUX_CSHDW	22
#define	AUX_SSWRST	128
#define	AUX_SHDFE	132
#define	AUX_SLON	137
#define	AUX_STON	138
#define	AUX_SPP		142
#define	AUX_SSIC	143
#define	AUX_SSRE	144
#define	AUX_SSTD1	149
#define	AUX_SVSTD1	151

D 2
struct	nhpibdevice {
	u_char	hpib_pad0;
	vu_char	hpib_cid;
	u_char	hpib_pad1;
#define	hpib_ie		hpib_ids
	vu_char	hpib_ids;
	u_char	hpib_pad2;
	vu_char	hpib_csa;
	u_char	hpib_pad3[11];
#define	hpib_mim	hpib_mis
	vu_char	hpib_mis;
	u_char	hpib_pad4;
#define	hpib_lim	hpib_lis
	vu_char	hpib_lis;
	u_char	hpib_pad5;
	vu_char	hpib_is;
	u_char	hpib_pad6;
#define	hpib_acr	hpib_cls
	vu_char	hpib_cls;
	u_char	hpib_pad7;
	vu_char	hpib_ar;
	u_char	hpib_pad8;
	vu_char	hpib_sprb;
	u_char	hpib_pad9;
#define	hpib_ppr	hpib_cpt
	vu_char	hpib_cpt;
	u_char	hpib_pad10;
	vu_char	hpib_data;
};
E 2
E 1
