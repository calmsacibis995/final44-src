h27479
s 00002/00002/00356
d D 8.1 93/06/10 22:38:45 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00248/00051/00110
d D 7.3 92/11/15 15:49:06 ralph 3 2
c changes for maxine from Rick Macklem.
e
s 00036/00023/00125
d D 7.2 92/02/29 11:07:02 ralph 2 1
c added support for DS5000
e
s 00148/00000/00000
d D 7.1 92/01/07 18:29:21 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1992 Regents of the University of California.
E 3
I 3
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
E 3
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
D 3
 * Ralph Campbell.
E 3
I 3
 * Ralph Campbell and Rick Macklem.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	LEMTU		1518
I 3
#define	LEBLEN		1520	/* LEMTU up to a multiple of 16 */
E 3
#define	LEMINSIZE	60	/* should be 64 if mode DTCR is set */
#define	LERBUF		32
#define	LERBUFLOG2	5
#define	LE_RLEN		(LERBUFLOG2 << 13)
#define	LETBUF		8
#define	LETBUFLOG2	3
#define	LE_TLEN		(LETBUFLOG2 << 13)

/*
 * LANCE registers.
 */
struct lereg1 {
	u_short	ler1_rdp;	/* data port */
	short	pad0;
	u_short	ler1_rap;	/* register select port */
	short	pad1;
};

I 2
D 3
#ifdef DS3100
#define LEPAD(x)	short x;
#define LE_RAM_SIZE	0x10000

typedef u_short	le_buf_t;
#endif
#ifdef DS5000
#define LEPAD(x)
#define LE_RAM_SIZE	0x20000

typedef u_char	le_buf_t;
#endif

E 3
E 2
/*
D 2
 * Overlayed on 64Kbyte dual-port RAM.
E 2
I 2
 * This structure is overlayed on the network dual-port RAM.
E 2
D 3
 * Currently 32 * 1518 receive plus 8 * 1518 transmit buffers plus
E 3
I 3
 * Currently 32 * 1520 receive plus 8 * 1520 transmit buffers plus
E 3
 * buffer descriptor rings.
I 3
 * There are two variants of the structure, one for the Pmax/3min/maxine
 * with 2 byte pads between entries and one for the 3max and turbochannel
 * option densely packed.
E 3
 */
I 3
struct	lermd {			/* +0x0020 */
	u_short	rmd0;
	u_short	rmd1;
	short	rmd2;
	u_short	rmd3;
};

struct	letmd {			/* +0x0058 */
	u_short	tmd0;
	u_short	tmd1;
	short	tmd2;
	u_short	tmd3;
};

struct	lermdpad {			/* +0x0020 */
	u_short	rmd0;
	short	pad0;
	u_short	rmd1;
	short	pad1;
	short	rmd2;
	short	pad2;
	u_short	rmd3;
	short	pad3;
};

struct	letmdpad {			/* +0x0058 */
	u_short	tmd0;
	short	pad0;
	u_short	tmd1;
	short	pad1;
	short	tmd2;
	short	pad2;
	u_short	tmd3;
	short	pad3;
};

E 3
struct lereg2 {
	/* init block */		/* CHIP address */
	u_short	ler2_mode;		/* +0x0000 */
D 2
	short	pad0;
E 2
I 2
D 3
	LEPAD(pad0)
E 3
E 2
	u_short	ler2_padr0;		/* +0x0002 */
D 2
	short	pad1;
E 2
I 2
D 3
	LEPAD(pad1)
E 3
E 2
	u_short	ler2_padr1;		/* +0x0004 */
D 2
	short	pad2;
E 2
I 2
D 3
	LEPAD(pad2)
E 3
E 2
	u_short	ler2_padr2;		/* +0x0006 */
D 2
	short	pad3;
E 2
I 2
D 3
	LEPAD(pad3)
E 3
E 2
	u_short	ler2_ladrf0;		/* +0x0008 */
D 2
	short	pad4;
E 2
I 2
D 3
	LEPAD(pad4)
E 3
E 2
	u_short	ler2_ladrf1;		/* +0x000A */
D 2
	short	pad5;
E 2
I 2
D 3
	LEPAD(pad5)
E 3
E 2
	u_short	ler2_ladrf2;		/* +0x000C */
D 2
	short	pad6;
E 2
I 2
D 3
	LEPAD(pad6)
E 3
E 2
	u_short	ler2_ladrf3;		/* +0x000E */
D 2
	short	pad7;
E 2
I 2
D 3
	LEPAD(pad7)
E 3
E 2
	u_short	ler2_rdra;		/* +0x0010 */
D 2
	short	pad8;
E 2
I 2
D 3
	LEPAD(pad8)
E 3
E 2
	u_short	ler2_rlen;		/* +0x0012 */
D 2
	short	pad9;
E 2
I 2
D 3
	LEPAD(pad9)
E 3
E 2
	u_short	ler2_tdra;		/* +0x0014 */
D 2
	short	pad10;
E 2
I 2
D 3
	LEPAD(pad10)
E 3
E 2
	u_short	ler2_tlen;		/* +0x0016 */
D 2
	short	pad11;
E 2
I 2
D 3
	LEPAD(pad11)
E 3
I 3
	short	pad0[4];		/* Pad to 16 shorts */
E 3
E 2
	/* receive message descriptors */
D 3
	struct	lermd {			/* +0x0018 */
		u_short	rmd0;
D 2
		short	pad0;
E 2
I 2
		LEPAD(pad0)
E 2
		u_short	rmd1;
D 2
		short	pad1;
E 2
I 2
		LEPAD(pad1)
E 2
		short	rmd2;
D 2
		short	pad2;
E 2
I 2
		LEPAD(pad2)
E 2
		u_short	rmd3;
D 2
		short	pad3;
E 2
I 2
		LEPAD(pad3)
E 2
	} ler2_rmd[LERBUF];
E 3
I 3
	struct lermd ler2_rmd[LERBUF];
E 3
	/* transmit message descriptors */
D 3
	struct	letmd {			/* +0x0058 */
		u_short	tmd0;
D 2
		short	pad0;
E 2
I 2
		LEPAD(pad0)
E 2
		u_short	tmd1;
D 2
		short	pad1;
E 2
I 2
		LEPAD(pad1)
E 2
		short	tmd2;
D 2
		short	pad2;
E 2
I 2
		LEPAD(pad2)
E 2
		u_short	tmd3;
D 2
		short	pad3;
E 2
I 2
		LEPAD(pad3)
E 2
	} ler2_tmd[LETBUF];
D 2
	u_short	ler2_rbuf[LERBUF][LEMTU]; /* +0x0060 */
	u_short	ler2_tbuf[LETBUF][LEMTU]; /* +0x2FD0 */
E 2
I 2
	le_buf_t	ler2_rbuf[LERBUF][LEMTU]; /* +0x0060 */
	le_buf_t	ler2_tbuf[LETBUF][LEMTU]; /* +0x2FD0 */
E 3
I 3
	struct letmd ler2_tmd[LETBUF];
	char	ler2_rbuf[LERBUF][LEBLEN]; /* +0x0060 */
	char	ler2_tbuf[LETBUF][LEBLEN]; /* +0x2FD0 */
E 3
E 2
};
I 3

struct lereg2pad {
	/* init block */		/* CHIP address */
	u_short	ler2_mode;		/* +0x0000 */
	short	pad0;
	u_short	ler2_padr0;		/* +0x0002 */
	short	pad1;
	u_short	ler2_padr1;		/* +0x0004 */
	short	pad2;
	u_short	ler2_padr2;		/* +0x0006 */
	short	pad3;
	u_short	ler2_ladrf0;		/* +0x0008 */
	short	pad4;
	u_short	ler2_ladrf1;		/* +0x000A */
	short	pad5;
	u_short	ler2_ladrf2;		/* +0x000C */
	short	pad6;
	u_short	ler2_ladrf3;		/* +0x000E */
	short	pad7;
	u_short	ler2_rdra;		/* +0x0010 */
	short	pad8;
	u_short	ler2_rlen;		/* +0x0012 */
	short	pad9;
	u_short	ler2_tdra;		/* +0x0014 */
	short	pad10;
	u_short	ler2_tlen;		/* +0x0016 */
	short	pad11[9];		/* Pad to 32 shorts */
	/* receive message descriptors */
	struct lermdpad ler2_rmd[LERBUF];
	/* transmit message descriptors */
	struct letmdpad ler2_tmd[LETBUF];
	short	ler2_rbuf[LERBUF][LEBLEN]; /* +0x0060 */
	short	ler2_tbuf[LETBUF][LEBLEN]; /* +0x2FD0 */
};

/*
 * Now for some truly ugly macros to access the structure fields
 * padded/non-padded at runtime. (For once, a Pascal like record variant
 * would be nice to have.)
 */
#define	LER2_RMDADDR(p, i) \
		(le->sc_ler2pad ? \
		 (volatile void *)&(((struct lereg2pad *)(p))->ler2_rmd[(i)]) : \
		 (volatile void *)&(((struct lereg2 *)(p))->ler2_rmd[(i)]))

#define	LER2_TMDADDR(p, i) \
		((le->sc_ler2pad ? \
		 (volatile void *)&(((struct lereg2pad *)(p))->ler2_tmd[(i)]) : \
		 (volatile void *)&(((struct lereg2 *)(p))->ler2_tmd[(i)])))

#define	LER2_RBUFADDR(p, i) \
		((le->sc_ler2pad ? \
		 (volatile void *)(((struct lereg2pad *)(p))->ler2_rbuf[(i)]) : \
		 (volatile void *)(((struct lereg2 *)(p))->ler2_rbuf[(i)])))

#define	LER2_TBUFADDR(p, i) \
		((le->sc_ler2pad ? \
		 (volatile void *)(((struct lereg2pad *)(p))->ler2_tbuf[(i)]) : \
		 (volatile void *)(((struct lereg2 *)(p))->ler2_tbuf[(i)])))

#define LER2_mode(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_mode = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_mode = (v)))
#define	LER2V_mode(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_mode : \
	 ((volatile struct lereg2 *)(p))->ler2_mode)

#define LER2_padr0(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_padr0 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_padr0 = (v)))
#define	LER2V_padr0(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_padr0 : \
	 ((volatile struct lereg2 *)(p))->ler2_padr0)

#define LER2_padr1(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_padr1 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_padr1 = (v)))
#define	LER2V_padr1(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_padr1 : \
	 ((volatile struct lereg2 *)(p))->ler2_padr1)

#define LER2_padr2(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_padr2 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_padr2 = (v)))
#define	LER2V_padr2(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_padr2 : \
	 ((volatile struct lereg2 *)(p))->ler2_padr2)

#define LER2_ladrf0(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_ladrf0 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_ladrf0 = (v)))
#define	LER2V_ladrf0(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_ladrf0 : \
	 ((volatile struct lereg2 *)(p))->ler2_ladrf0)

#define LER2_ladrf1(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_ladrf1 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_ladrf1 = (v)))
#define	LER2V_ladrf1(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_ladrf1 : \
	 ((volatile struct lereg2 *)(p))->ler2_ladrf1)

#define LER2_ladrf2(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_ladrf2 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_ladrf2 = (v)))
#define	LER2V_ladrf2(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_ladrf2 : \
	 ((volatile struct lereg2 *)(p))->ler2_ladrf2)

#define LER2_ladrf3(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_ladrf3 = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_ladrf3 = (v)))
#define	LER2V_ladrf3(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_ladrf3 : \
	 ((volatile struct lereg2 *)(p))->ler2_ladrf3)

#define LER2_rdra(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_rdra = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_rdra = (v)))
#define	LER2V_rdra(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_rdra : \
	 ((volatile struct lereg2 *)(p))->ler2_rdra)

#define LER2_rlen(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_rlen = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_rlen = (v)))
#define	LER2V_rlen(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_rlen : \
	 ((volatile struct lereg2 *)(p))->ler2_rlen)

#define LER2_tdra(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_tdra = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_tdra = (v)))
#define	LER2V_tdra(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_tdra : \
	 ((volatile struct lereg2 *)(p))->ler2_tdra)

#define LER2_tlen(p, v) \
	(le->sc_ler2pad ? (((volatile struct lereg2pad *)(p))->ler2_tlen = (v)) : \
	 (((volatile struct lereg2 *)(p))->ler2_tlen = (v)))
#define	LER2V_tlen(p) \
	(le->sc_ler2pad ? ((volatile struct lereg2pad *)(p))->ler2_tlen : \
	 ((volatile struct lereg2 *)(p))->ler2_tlen)

#define LER2_rmd0(p, v) \
	(le->sc_ler2pad ? (((volatile struct lermdpad *)(p))->rmd0 = (v)) : \
	 ((((volatile struct lermd *)(p))->rmd0 = (v))))
#define LER2V_rmd0(p) \
	(le->sc_ler2pad ? ((volatile struct lermdpad *)(p))->rmd0 : \
	 ((volatile struct lermd *)(p))->rmd0)

#define LER2_rmd1(p, v) \
	(le->sc_ler2pad ? (((volatile struct lermdpad *)(p))->rmd1 = (v)) : \
	 (((volatile struct lermd *)(p))->rmd1 = (v)))
#define LER2V_rmd1(p) \
	(le->sc_ler2pad ? ((volatile struct lermdpad *)(p))->rmd1 : \
	 ((volatile struct lermd *)(p))->rmd1)

#define LER2_rmd2(p, v) \
	(le->sc_ler2pad ? (((volatile struct lermdpad *)(p))->rmd2 = (v)) : \
	 (((volatile struct lermd *)(p))->rmd2 = (v)))
#define LER2V_rmd2(p) \
	(le->sc_ler2pad ? ((volatile struct lermdpad *)(p))->rmd2 : \
	 ((volatile struct lermd *)(p))->rmd2)

#define LER2_rmd3(p, v) \
	(le->sc_ler2pad ? (((volatile struct lermdpad *)(p))->rmd3 = (v)) : \
	 (((volatile struct lermd *)(p))->rmd3 = (v)))
#define LER2V_rmd3(p) \
	(le->sc_ler2pad ? ((volatile struct lermdpad *)(p))->rmd3 : \
	 ((volatile struct lermd *)(p))->rmd3)

#define LER2_tmd0(p, v) \
	(le->sc_ler2pad ? (((volatile struct letmdpad *)(p))->tmd0 = (v)) : \
	 (((volatile struct letmd *)(p))->tmd0 = (v)))
#define LER2V_tmd0(p) \
	(le->sc_ler2pad ? ((volatile struct letmdpad *)(p))->tmd0 : \
	 ((volatile struct letmd *)(p))->tmd0)

#define LER2_tmd1(p, v) \
	(le->sc_ler2pad ? (((volatile struct letmdpad *)(p))->tmd1 = (v)) : \
	 (((volatile struct letmd *)(p))->tmd1 = (v)))
#define LER2V_tmd1(p) \
	(le->sc_ler2pad ? ((volatile struct letmdpad *)(p))->tmd1 : \
	 ((volatile struct letmd *)(p))->tmd1)

#define LER2_tmd2(p, v) \
	(le->sc_ler2pad ? (((volatile struct letmdpad *)(p))->tmd2 = (v)) : \
	 (((volatile struct letmd *)(p))->tmd2 = (v)))
#define LER2V_tmd2(p) \
	(le->sc_ler2pad ? ((volatile struct letmdpad *)(p))->tmd2 : \
	 ((volatile struct letmd *)(p))->tmd2)

#define LER2_tmd3(p, v) \
	(le->sc_ler2pad ? (((volatile struct letmdpad *)(p))->tmd3 = (v)) : \
	 (((volatile struct letmd *)(p))->tmd3 = (v)))
#define LER2V_tmd3(p) \
	(le->sc_ler2pad ? ((volatile struct letmdpad *)(p))->tmd3 : \
	 ((volatile struct letmd *)(p))->tmd3)
E 3

/*
 * Control and status bits -- lereg0
 */
#define	LE_IE		0x80		/* interrupt enable */
#define	LE_IR		0x40		/* interrupt requested */
#define	LE_LOCK		0x08		/* lock status register */
#define	LE_ACK		0x04		/* ack of lock */
#define	LE_JAB		0x02		/* loss of tx clock (???) */
#define LE_IPL(x)	((((x) >> 4) & 0x3) + 3)

/*
 * Control and status bits -- lereg1
 */
#define	LE_CSR0		0
#define	LE_CSR1		1
#define	LE_CSR2		2
#define	LE_CSR3		3

#define	LE_SERR		0x8000
#define	LE_BABL		0x4000
#define	LE_CERR		0x2000
#define	LE_MISS		0x1000
#define	LE_MERR		0x0800
#define	LE_RINT		0x0400
#define	LE_TINT		0x0200
#define	LE_IDON		0x0100
#define	LE_INTR		0x0080
#define	LE_INEA		0x0040
#define	LE_RXON		0x0020
#define	LE_TXON		0x0010
#define	LE_TDMD		0x0008
#define	LE_STOP		0x0004
#define	LE_STRT		0x0002
#define	LE_INIT		0x0001

#define	LE_BSWP		0x4
#define	LE_MODE		0x0

/*
 * Control and status bits -- lereg2
 */
#define	LE_OWN		0x8000
#define	LE_ERR		0x4000
#define	LE_STP		0x0200
#define	LE_ENP		0x0100

#define	LE_FRAM		0x2000
#define	LE_OFLO		0x1000
#define	LE_CRC		0x0800
#define	LE_RBUFF	0x0400

#define	LE_MORE		0x1000
#define	LE_ONE		0x0800
#define	LE_DEF		0x0400

#define	LE_TBUFF	0x8000
#define	LE_UFLO		0x4000
#define	LE_LCOL		0x1000
#define	LE_LCAR		0x0800
#define	LE_RTRY		0x0400
E 1
