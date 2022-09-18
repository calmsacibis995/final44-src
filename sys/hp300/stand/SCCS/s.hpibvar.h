h62385
s 00002/00002/00031
d D 8.1 93/06/10 21:46:55 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00000/00000
d D 7.1 90/05/08 22:45:55 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	HPIBA		32
#define	HPIBB		1
#define	HPIBC		8
#define	HPIBA_BA	21
#define	HPIBC_BA	30

#define	CSA_BA		0x1F

#define	C_DCL		20
#define	C_LAG		32
#define	C_UNL		63
#define	C_TAG		64
#define	C_UNA		94
#define	C_UNT		95
#define	C_SCG		96

struct	hpib_softc {
	char	sc_alive;
	char	sc_type;
	int	sc_ba;
	char	*sc_addr;
};

extern	struct hpib_softc hpib_softc[];
E 1
