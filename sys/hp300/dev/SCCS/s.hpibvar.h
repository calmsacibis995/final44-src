h62945
s 00002/00002/00059
d D 8.1 93/06/10 21:33:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00059
d D 7.4 92/07/07 19:02:37 torek 4 3
c lint
e
s 00001/00001/00058
d D 7.3 91/05/07 09:50:11 hibler 3 2
c internalhpib now caddr_t
e
s 00002/00000/00057
d D 7.2 90/11/04 19:32:41 mckusick 2 1
c update from Mike Hibler
e
s 00057/00000/00000
d D 7.1 90/05/08 22:06:43 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	HPIB_IPL(x)	((((x) >> 4) & 0x3) + 3)

#define	HPIBA		32
#define	HPIBB		1
#define	HPIBC		8
#define	HPIBA_BA	21
#define	HPIBC_BA	30
#define	HPIBA_IPL	3

#define	CSA_BA		0x1F

#define	IDS_WDMA	0x04
#define	IDS_WRITE	0x08
#define	IDS_IR		0x40
#define	IDS_IE		0x80
#define	IDS_DMA(x)	(1 << (x))

#define	C_DCL		0x14
#define	C_LAG		0x20
#define	C_UNL		0x3f
#define	C_TAG		0x40
#define	C_UNA		0x5e
#define	C_UNT		0x5f
#define	C_SCG		0x60

struct	hpib_softc {
	struct	hp_ctlr *sc_hc;
	int	sc_flags;
	struct	devqueue sc_dq;
	struct	devqueue sc_sq;
	int	sc_ba;
	int	sc_type;
	char	*sc_addr;
	int	sc_count;
	int	sc_curcnt;
};

/* sc_flags */
#define	HPIBF_IO	0x1
#define	HPIBF_DONE	0x2
#define	HPIBF_PPOLL	0x4
#define	HPIBF_READ	0x8
#define	HPIBF_DMA16	0x8000

#ifdef KERNEL
extern	struct hpib_softc hpib_softc[];
D 3
extern	int internalhpib;
E 3
I 3
extern	caddr_t internalhpib;
E 3
I 2
extern	int hpibtimeout;
extern	int hpibdmathresh;
I 4
void	fhpibppwatch __P((void *arg));
void	nhpibppwatch __P((void *arg));
E 4
E 2
#endif
E 1
