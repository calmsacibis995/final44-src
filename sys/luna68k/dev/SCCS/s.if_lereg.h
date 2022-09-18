h33904
s 00002/00002/00126
d D 8.1 93/06/10 22:16:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00126
d D 7.4 93/01/13 15:49:18 akito 4 3
c sync up to hp300/dev/if_lereg.h 7.5
e
s 00001/00005/00127
d D 7.3 92/10/11 10:57:18 bostic 3 2
c make kernel includes standard
e
s 00014/00009/00118
d D 7.2 92/07/23 16:02:04 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00127/00000/00000
d D 7.1 92/06/15 06:45:49 fujita 1 0
c date and time created 92/06/15 06:45:49 by fujita
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1982, 1990, 1992 The Regents of the University of California.
E 2
I 2
D 5
 * Copyright (c) 1982, 1990 The Regents of the University of California.
E 2
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
I 2
D 4
 * from: hp300/dev/if_lereg.h	7.4 (Berkeley) 7/6/92
E 4
I 4
 * from: hp300/dev/if_lereg.h	7.5 (Berkeley) 10/11/92
E 4
 *
E 2
 *	%W% (Berkeley) %G%
 */

I 2
D 3
#ifdef KERNEL
#include "iotypes.h"	/* XXX */
#else
#include <luna68k/dev/iotypes.h>	/* XXX */
#endif
E 3
I 3
D 4
#include <hp/dev/iotypes.h>	/* XXX */
E 4
I 4
#include <luna68k/dev/iotypes.h>	/* XXX */
E 4
E 3

E 2
#define	LEID		21

#define	LEMTU		1518
#define	LEMINSIZE	60	/* should be 64 if mode DTCR is set */
#define	LERBUF		8
#define	LERBUFLOG2	3
#define	LE_RLEN		(LERBUFLOG2 << 13)
#define	LETBUF		2
#define	LETBUFLOG2	1
#define	LE_TLEN		(LETBUFLOG2 << 13)

D 2
#define vu_char		volatile u_char

E 2
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
D 2
 * Current size is 13,758 bytes with 8 x 1518 receive buffers and
 * 1 x 1518 transmit buffer.
E 2
I 2
 * Current size is 15,284 bytes with 8 x 1518 receive buffers and
 * 2 x 1518 transmit buffers.
E 2
 */
struct lereg2 {
	/* init block */
	u_short	ler2_mode;		/* +0x0000 */
	u_char	ler2_padr[6];		/* +0x0002 */
D 2
	u_long	ler2_ladrf0;		/* +0x0008 */
	u_long	ler2_ladrf1;		/* +0x000C */
E 2
I 2
	u_long	ler2_ladrf[2];		/* +0x0008 */
E 2
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
D 2
	char	ler2_rbuf[LERBUF][LEMTU]; /* +0x0060 */
	char	ler2_tbuf[LETBUF][LEMTU]; /* +0x2FD0 */
E 2
I 2
	char	ler2_rbuf[LERBUF][LEMTU]; /* +0x0068 */
	char	ler2_tbuf[LETBUF][LEMTU]; /* +0x2FD8 */
E 2
};

/*
 * Control and status bits -- lereg0
 */
#define	LE_IE		0x80		/* interrupt enable */
#define	LE_IR		0x40		/* interrupt requested */
#define	LE_LOCK		0x08		/* lock status register */
#define	LE_ACK		0x04		/* ack of lock */
#define	LE_JAB		0x02		/* loss of tx clock (???) */

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
