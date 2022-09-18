h25384
s 00002/00002/00125
d D 8.1 93/06/10 21:33:18 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00127
d D 7.5 92/10/11 09:23:59 bostic 5 4
c make kernel includes standard
e
s 00001/00002/00130
d D 7.4 92/07/06 15:30:20 sklower 4 3
c multicast changes from lbl
e
s 00010/00006/00122
d D 7.3 92/06/05 15:31:42 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00002/00002/00126
d D 7.2 91/08/08 20:13:21 sklower 2 1
c this version has 2 tx buffers; appears to work.
e
s 00128/00000/00000
d D 7.1 90/05/08 22:06:43 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
D 5
#ifdef KERNEL
#include "hp/dev/iotypes.h"	/* XXX */
#else
E 5
#include <hp/dev/iotypes.h>	/* XXX */
D 5
#endif
E 5

E 3
#define	LEID		21

#define	LEMTU		1518
#define	LEMINSIZE	60	/* should be 64 if mode DTCR is set */
#define	LERBUF		8
#define	LERBUFLOG2	3
#define	LE_RLEN		(LERBUFLOG2 << 13)
D 2
#define	LETBUF		1
#define	LETBUFLOG2	0
E 2
I 2
#define	LETBUF		2
#define	LETBUFLOG2	1
E 2
#define	LE_TLEN		(LETBUFLOG2 << 13)

D 3
#define vu_char		volatile u_char

E 3
/*
 * LANCE registers.
 */
struct lereg0 {
	u_char	ler0_pad0;
	vu_char	ler0_id;	/* ID */
	u_char	ler0_pad1;
	vu_char	ler0_status;	/* interrupt enable/status */
};

struct lereg1 {
	u_short	ler1_rdp;	/* data port */
	u_short	ler1_rap;	/* register select port */
};

/*
 * Overlayed on 16K dual-port RAM.
D 3
 * Current size is 13,758 bytes with 8 x 1518 receive buffers and
 * 1 x 1518 transmit buffer.
E 3
I 3
 * Current size is 15,284 bytes with 8 x 1518 receive buffers and
 * 2 x 1518 transmit buffers.
E 3
 */
struct lereg2 {
	/* init block */
	u_short	ler2_mode;		/* +0x0000 */
	u_char	ler2_padr[6];		/* +0x0002 */
D 4
	u_long	ler2_ladrf0;		/* +0x0008 */
	u_long	ler2_ladrf1;		/* +0x000C */
E 4
I 4
	u_long	ler2_ladrf[2];		/* +0x0008 */
E 4
	u_short	ler2_rdra;		/* +0x0010 */
	u_short	ler2_rlen;		/* +0x0012 */
	u_short	ler2_tdra;		/* +0x0014 */
	u_short	ler2_tlen;		/* +0x0016 */
	/* receive message descriptors */
	struct	lermd {			/* +0x0018 */
		u_short	rmd0;
		u_short	rmd1;
		short	rmd2;
		u_short	rmd3;
	} ler2_rmd[LERBUF];
	/* transmit message descriptors */
	struct	letmd {			/* +0x0058 */
		u_short	tmd0;
		u_short	tmd1;
		short	tmd2;
		u_short	tmd3;
	} ler2_tmd[LETBUF];
D 3
	char	ler2_rbuf[LERBUF][LEMTU]; /* +0x0060 */
	char	ler2_tbuf[LETBUF][LEMTU]; /* +0x2FD0 */
E 3
I 3
	char	ler2_rbuf[LERBUF][LEMTU]; /* +0x0068 */
	char	ler2_tbuf[LETBUF][LEMTU]; /* +0x2FD8 */
E 3
};

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
