h30454
s 00012/00012/00127
d D 8.2 93/10/30 22:17:04 torek 4 3
c multicast address filter needs to be four shortwords
e
s 00002/00002/00137
d D 8.1 93/06/11 15:14:56 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00137
d D 7.2 93/04/20 19:43:10 torek 2 1
c fix spelling in copyright
e
s 00139/00000/00000
d D 7.1 92/07/13 00:44:07 torek 1 0
c date and time created 92/07/13 00:44:07 by torek
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1982, 1992 Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1982, 1992 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 2
 * from: $Header: if_lereg.h,v 1.5 92/07/10 06:45:26 torek Exp $
E 2
I 2
D 4
 * from: $Header: if_lereg.h,v 1.6 92/11/26 02:28:12 torek Exp $
E 4
I 4
 * from: $Header: if_lereg.h,v 1.7 93/10/31 04:41:00 leres Locked $
E 4
E 2
 */

#define	LEMTU		1518
#define	LEMINSIZE	60	/* should be 64 if mode DTCR is set */
#define	LERBUF		8
#define	LERBUFLOG2	3
#define	LE_RLEN		(LERBUFLOG2 << 13)
#define	LETBUF		1
#define	LETBUFLOG2	0
#define	LE_TLEN		(LETBUFLOG2 << 13)

/* Local Area Network Controller for Ethernet (LANCE) registers */
struct lereg1 {
	u_short	ler1_rdp;	/* register data port */
	u_short	ler1_rap;	/* register address port */
};

/* register addresses */
#define	LE_CSR0		0		/* Control and status register */
#define	LE_CSR1		1		/* low address of init block */
#define	LE_CSR2		2		/* high address of init block */
#define	LE_CSR3		3		/* Bus master and control */

/* Control and status register 0 (csr0) */
#define	LE_C0_ERR	0x8000		/* error summary */
#define	LE_C0_BABL	0x4000		/* transmitter timeout error */
#define	LE_C0_CERR	0x2000		/* collision */
#define	LE_C0_MISS	0x1000		/* missed a packet */
#define	LE_C0_MERR	0x0800		/* memory error */
#define	LE_C0_RINT	0x0400		/* receiver interrupt */
#define	LE_C0_TINT	0x0200		/* transmitter interrupt */
#define	LE_C0_IDON	0x0100		/* initalization done */
#define	LE_C0_INTR	0x0080		/* interrupt condition */
#define	LE_C0_INEA	0x0040		/* interrupt enable */
#define	LE_C0_RXON	0x0020		/* receiver on */
#define	LE_C0_TXON	0x0010		/* transmitter on */
#define	LE_C0_TDMD	0x0008		/* transmit demand */
#define	LE_C0_STOP	0x0004		/* disable all external activity */
#define	LE_C0_STRT	0x0002		/* enable external activity */
#define	LE_C0_INIT	0x0001		/* begin initalization */

#define LE_C0_BITS \
    "\20\20ERR\17BABL\16CERR\15MISS\14MERR\13RINT\
\12TINT\11IDON\10INTR\07INEA\06RXON\05TXON\04TDMD\03STOP\02STRT\01INIT"

/* Control and status register 3 (csr3) */
#define	LE_C3_BSWP	0x4		/* byte swap */
#define	LE_C3_ACON	0x2		/* ALE control, eh? */
#define	LE_C3_BCON	0x1		/* byte control */
/*
 * Current size is 13,758 bytes with 8 x 1518 receive buffers and
 * 1 x 1518 transmit buffer.
 */
struct lereg2 {
	/* initialization block */
D 4
	u_short	ler2_mode;		/* +0x0000: mode */
	u_char	ler2_padr[6];		/* +0x0002: physical address */
	u_long	ler2_ladrf[2];		/* +0x0008: logical address filter */
	u_short	ler2_rdra;		/* +0x0010: receive descriptor addr */
	u_short	ler2_rlen;		/* +0x0012: rda high and ring size */
	u_short	ler2_tdra;		/* +0x0014: transmit descriptor addr */
	u_short	ler2_tlen;		/* +0x0016: tda high and ring size */
E 4
I 4
	u_short	ler2_mode;		/* mode */
	u_char	ler2_padr[6];		/* physical address */
	u_short	ler2_ladrf[4];		/* logical address filter */
	u_short	ler2_rdra;		/* receive descriptor addr */
	u_short	ler2_rlen;		/* rda high and ring size */
	u_short	ler2_tdra;		/* transmit descriptor addr */
	u_short	ler2_tlen;		/* tda high and ring size */
E 4
	/* receive message descriptors. bits/hadr are byte order dependent. */
D 4
	struct	lermd {			/* +0x0018 */
E 4
I 4
	struct	lermd {
E 4
		u_short	rmd0;		/* low address of packet */
		u_char	rmd1_bits;	/* descriptor bits */
		u_char	rmd1_hadr;	/* high address of packet */
		short	rmd2;		/* buffer byte count */
		u_short	rmd3;		/* message byte count */
	} ler2_rmd[LERBUF];
	/* transmit message descriptors */
D 4
	struct	letmd {			/* +0x0058 */
E 4
I 4
	struct	letmd {
E 4
		u_short	tmd0;		/* low address of packet */
		u_char	tmd1_bits;	/* descriptor bits */
		u_char	tmd1_hadr;	/* high address of packet */
		short	tmd2;		/* buffer byte count */
		u_short	tmd3;		/* transmit error bits */
	} ler2_tmd[LETBUF];
D 4
	char	ler2_rbuf[LERBUF][LEMTU]; /* +0x0060 */
	char	ler2_tbuf[LETBUF][LEMTU]; /* +0x2fd0 */
E 4
I 4
	char	ler2_rbuf[LERBUF][LEMTU];
	char	ler2_tbuf[LETBUF][LEMTU];
E 4
};

/* Initialzation block (mode) */
#define	LE_MODE_PROM	0x8000		/* promiscuous mode */
/*			0x7f80		   reserved, must be zero */
#define	LE_MODE_INTL	0x0040		/* internal loopback */
#define	LE_MODE_DRTY	0x0020		/* disable retry */
#define	LE_MODE_COLL	0x0010		/* force a collision */
#define	LE_MODE_DTCR	0x0008		/* disable transmit CRC */
#define	LE_MODE_LOOP	0x0004		/* loopback mode */
#define	LE_MODE_DTX	0x0002		/* disable transmitter */
#define	LE_MODE_DRX	0x0001		/* disable receiver */
#define	LE_MODE_NORMAL	0		/* none of the above */


/* Receive message descriptor 1 (rmd1_bits) */ 
#define	LE_R1_OWN	0x80		/* LANCE owns the packet */
#define	LE_R1_ERR	0x40		/* error summary */
#define	LE_R1_FRAM	0x20		/* framing error */
#define	LE_R1_OFLO	0x10		/* overflow error */
#define	LE_R1_CRC	0x08		/* CRC error */
#define	LE_R1_BUFF	0x04		/* buffer error */
#define	LE_R1_STP	0x02		/* start of packet */
#define	LE_R1_ENP	0x01		/* end of packet */

#define LE_R1_BITS \
    "\20\10OWN\7ERR\6FRAM\5OFLO\4CRC\3BUFF\2STP\1ENP"

/* Transmit message descriptor 1 (tmd1_bits) */ 
#define	LE_T1_OWN	0x80		/* LANCE owns the packet */
#define	LE_T1_ERR	0x40		/* error summary */
#define	LE_T1_MORE	0x10		/* multiple collisions */
#define	LE_T1_ONE	0x08		/* single collision */
#define	LE_T1_DEF	0x04		/* defferred transmit */
#define	LE_T1_STP	0x02		/* start of packet */
#define	LE_T1_ENP	0x01		/* end of packet */

#define LE_T1_BITS \
    "\20\10OWN\7ERR\6RES\5MORE\4ONE\3DEF\2STP\1ENP"

/* Transmit message descriptor 3 (tmd3) */ 
#define	LE_T3_BUFF	0x8000		/* buffer error */
#define	LE_T3_UFLO	0x4000		/* underflow error */
#define	LE_T3_LCOL	0x1000		/* late collision */
#define	LE_T3_LCAR	0x0800		/* loss of carrier */
#define	LE_T3_RTRY	0x0400		/* retry error */
#define	LE_T3_TDR_MASK	0x03ff		/* time domain reflectometry counter */

#define LE_T3_BITS \
    "\20\20BUFF\17UFLO\16RES\15LCOL\14LCAR\13RTRY"
E 1
