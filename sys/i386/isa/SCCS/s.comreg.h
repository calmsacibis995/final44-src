h05087
s 00002/00002/00085
d D 8.1 93/06/11 15:53:36 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00027/00010/00060
d D 7.2 91/05/09 20:33:35 william 2 1
c donn's changes
e
s 00070/00000/00000
d D 7.1 91/04/03 12:33:10 william 1 0
c date and time created 91/04/03 12:33:10 by william
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1982, 1986, 1990, 1991 The Regents of the University of
 * California. All rights reserved.
E 2
I 2
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
E 2
 *
D 2
 * This code is derived from software contributed to Berkeley by
 * the University of Utah and William Jolitz.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */


/* 16 bit baud rate divisor (lower byte in dca_data, upper in dca_ier) */
#define	COMBRD(x)	(1843200 / (16*(x)))

/* interrupt enable register */
#define	IER_ERXRDY	0x1
#define	IER_ETXRDY	0x2
#define	IER_ERLS	0x4
#define	IER_EMSC	0x8

/* interrupt identification register */
I 2
#define	IIR_IMASK	0xf
#define	IIR_RXTOUT	0xc
#define	IIR_RLS		0x6
#define	IIR_RXRDY	0x4
#define	IIR_TXRDY	0x2
E 2
#define	IIR_NOPEND	0x1
D 2
#define	IIR_IMASK	0x6
#define	IIR_RLS		6
#define	IIR_RXRDY	4
#define	IIR_TXRDY	2
#define	IIR_MLSC	0
E 2
I 2
#define	IIR_MLSC	0x0
#define	IIR_FIFO_MASK	0xc0	/* set if FIFOs are enabled */
E 2

I 2
/* fifo control register */
#define	FIFO_ENABLE	0x01
#define	FIFO_RCV_RST	0x02
#define	FIFO_XMT_RST	0x04
#define	FIFO_DMA_MODE	0x08
#define	FIFO_TRIGGER_1	0x00
#define	FIFO_TRIGGER_4	0x40
#define	FIFO_TRIGGER_8	0x80
#define	FIFO_TRIGGER_14	0xc0

E 2
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
#define	MCR_IENABLE	0x08
#define	MCR_DRS		0x04
#define	MCR_RTS		0x02
#define	MCR_DTR		0x01

/* line status register */
I 2
#define	LSR_RCV_FIFO	0x80
E 2
#define	LSR_TSRE	0x40
#define	LSR_TXRDY	0x20
#define	LSR_BI		0x10
#define	LSR_FE		0x08
#define	LSR_PE		0x04
#define	LSR_OE		0x02
#define	LSR_RXRDY	0x01
I 2
#define	LSR_RCV_MASK	0x1f
E 2

/* modem status register */
#define	MSR_DCD		0x80
#define	MSR_RI		0x40
#define	MSR_DSR		0x20
#define	MSR_CTS		0x10
#define	MSR_DDCD	0x08
#define	MSR_TERI	0x04
#define	MSR_DDSR	0x02
#define	MSR_DCTS	0x01

I 2
/*
 * WARNING: Serial console is assumed to be at COM1 address
 * and CONUNIT must be 0.
 */
#define	CONADDR	(0x3f8)
#define	CONUNIT	(0)
E 2
E 1
