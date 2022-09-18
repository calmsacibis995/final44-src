h36964
s 00002/00002/00157
d D 8.1 93/06/10 21:23:16 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00005/00158
d D 7.5 92/10/11 08:55:05 bostic 5 4
c make kernel includes standard
e
s 00068/00022/00095
d D 7.4 92/06/05 15:23:14 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00023/00008/00094
d D 7.3 91/05/07 09:50:30 hibler 3 2
c FIFO support from Donn, DIO-II support
e
s 00004/00003/00098
d D 7.2 90/06/27 09:01:31 hibler 2 1
c Van's speed enhancements and rts/cts flow control additions
e
s 00101/00000/00000
d D 7.1 90/05/08 22:06:33 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#ifdef KERNEL
#include "hp/dev/iotypes.h"	/* XXX */
#else
#include <hp/dev/iotypes.h>	/* XXX */
#endif
E 5
I 5
#include <hp/dev/iotypes.h>			/* XXX */
E 5

#ifdef hp700
E 4
struct dcadevice {
I 4
	vu_char	dca_reset;
	vu_char dca_pad[0x800-1];
	vu_char	dca_data;			/* receive buf or xmit hold */
	vu_char	dca_ier;			/* interrupt enable */
	vu_char	dca_iir;			/* (RO) interrupt identify */
#define		dca_fifo	dca_iir		/* (WO) FIFO control */
	vu_char	dca_cfcr;			/* line control */
	vu_char	dca_mcr;			/* modem control */
	vu_char	dca_lsr;			/* line status */
	vu_char	dca_msr;			/* modem status */
	vu_char	dca_scr;			/* scratch pad */
};
#else
struct dcadevice {
	/* card registers */
E 4
	u_char	dca_pad0;
D 4
	volatile u_char	dca_irid;
	volatile short	dca_ic;
	volatile short	dca_ocbrc;
	volatile short	dca_lcsm;
	short	dca_pad1[4];
E 4
I 4
	vu_char	dca_id;				/* 0x01 (read) */
#define		dca_reset	dca_id		/* 0x01 (write) */
	u_char	dca_pad1;
	vu_char	dca_ic;				/* 0x03 */
E 4
	u_char	dca_pad2;
D 4
	volatile u_char	dca_data;
	volatile short	dca_ier;
D 2
	volatile short	dca_iir;
E 2
I 2
	u_char	dca_pad4;
D 3
	volatile u_char	dca_iir;
E 3
I 3
	volatile u_char	dca_iir;			/* read-only */
#define			dca_fifo	dca_iir		/* write-only */
E 3
E 2
	volatile short	dca_cfcr;
	volatile short	dca_mcr;
	volatile short	dca_lsr;
E 4
I 4
	vu_char	dca_ocbrc;			/* 0x05 */
E 4
	u_char	dca_pad3;
D 4
	volatile u_char	dca_msr;
E 4
I 4
	vu_char	dca_lcsm;			/* 0x07 */
	u_char	dca_pad4[8];
	/* chip registers */
	u_char	dca_pad5;
	vu_char	dca_data;			/* 0x11 */
	u_char	dca_pad6;
	vu_char	dca_ier;			/* 0x13 */
	u_char	dca_pad7;
	vu_char	dca_iir;			/* 0x15 (read) */
#define		dca_fifo	dca_iir		/* 0x15 (write) */
	u_char	dca_pad8;
	vu_char	dca_cfcr;			/* 0x17 */
	u_char	dca_pad9;
	vu_char	dca_mcr;			/* 0x19 */
	u_char	dca_padA;
	vu_char	dca_lsr;			/* 0x1B */
	u_char	dca_padB;
	vu_char	dca_msr;			/* 0x1D */
E 4
};
I 4
#endif
E 4

D 4
/* interface reset/id */
E 4
I 4
/* interface reset/id (300 only) */
E 4
#define	DCAID0		0x02
#define DCAREMID0	0x82
#define	DCAID1		0x42
#define DCAREMID1	0xC2

D 4
/* interrupt control */
E 4
I 4
/* interrupt control (300 only) */
E 4
#define	DCAIPL(x)	((((x) >> 4) & 3) + 3)
#define	IC_IR		0x40
#define	IC_IE		0x80

D 4
/* 16 bit baud rate divisor (lower byte in dca_data, upper in dca_ier) */
E 4
I 4
/*
 * 16 bit baud rate divisor (lower byte in dca_data, upper in dca_ier)
 * NB: This constant is for a 7.3728 clock frequency. The 300 clock
 *     frequency is 2.4576, giving a constant of 153600.
 */
#ifdef hp300
E 4
#define	DCABRD(x)	(153600 / (x))
I 4
#endif
#ifdef hp700
#define	DCABRD(x)	(460800 / (x))
#endif
E 4

/* interrupt enable register */
#define	IER_ERXRDY	0x1
#define	IER_ETXRDY	0x2
#define	IER_ERLS	0x4
#define	IER_EMSC	0x8

/* interrupt identification register */
I 3
#define	IIR_IMASK	0xf
#define	IIR_RXTOUT	0xc
#define	IIR_RLS		0x6
#define	IIR_RXRDY	0x4
#define	IIR_TXRDY	0x2
E 3
#define	IIR_NOPEND	0x1
D 3
#define	IIR_IMASK	0x6
#define	IIR_RLS		6
#define	IIR_RXRDY	4
#define	IIR_TXRDY	2
#define	IIR_MLSC	0
E 3
I 3
#define	IIR_MLSC	0x0
#define	IIR_FIFO_MASK	0xc0	/* set if FIFOs are enabled */
E 3

I 3
/* fifo control register */
#define	FIFO_ENABLE	0x01
#define	FIFO_RCV_RST	0x02
#define	FIFO_XMT_RST	0x04
#define	FIFO_DMA_MODE	0x08
#define	FIFO_TRIGGER_1	0x00
#define	FIFO_TRIGGER_4	0x40
#define	FIFO_TRIGGER_8	0x80
#define	FIFO_TRIGGER_14	0xc0

E 3
/* character format control register */
#define	CFCR_DLAB	0x80
#define	CFCR_SBREAK	0x40
#define	CFCR_PZERO	0x30
#define	CFCR_PONE	0x20
#define	CFCR_PEVEN	0x10
#define	CFCR_PODD	0x00
#define	CFCR_PENAB	0x08
#define	CFCR_STOPB	0x04
#define	CFCR_8BITS	0x03
#define	CFCR_7BITS	0x02
#define	CFCR_6BITS	0x01
#define	CFCR_5BITS	0x00

/* modem control register */
#define	MCR_LOOPBACK	0x10
D 4
#define	MCR_SRTS	0x08
E 4
I 4
#define	MCR_IEN		0x08
E 4
#define	MCR_DRS		0x04
#define	MCR_RTS		0x02
#define	MCR_DTR		0x01

/* line status register */
I 3
#define	LSR_RCV_FIFO	0x80
E 3
#define	LSR_TSRE	0x40
#define	LSR_TXRDY	0x20
#define	LSR_BI		0x10
#define	LSR_FE		0x08
#define	LSR_PE		0x04
#define	LSR_OE		0x02
#define	LSR_RXRDY	0x01
I 3
#define	LSR_RCV_MASK	0x1f
E 3

/* modem status register */
#define	MSR_DCD		0x80
#define	MSR_RI		0x40
#define	MSR_DSR		0x20
#define	MSR_CTS		0x10
D 2
#define	MSR_CCD		0x08
E 2
I 2
#define	MSR_DDCD	0x08
E 2
#define	MSR_TERI	0x04
#define	MSR_DDSR	0x02
D 2
#define	MSR_CCTS	0x01
E 2
I 2
#define	MSR_DCTS	0x01
E 2

D 4
/*
 * WARNING: Serial console is assumed to be at SC9
 * and CONUNIT must be 0.
 */
E 4
I 4
#ifdef hp300
/* WARNING: Serial console is assumed to be at SC9 */
E 4
D 3
#define CONADDR	((struct dcadevice *)(IOV(EXTIOBASE + (9 * IOCARDSIZE))))
#define CONUNIT	(0)
E 3
I 3
#define CONSCODE	(9)
I 4
#endif
#ifdef hp700
/* hardwired port addresses */
#define PORT1		((struct dcadevice *)CORE_RS232_1)
#define PORT2		((struct dcadevice *)CORE_RS232_2)
#define CONPORT		PORT1
#endif
E 4
#define CONUNIT		(0)
E 3
E 1
