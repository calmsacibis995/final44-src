h03423
s 00002/00002/00133
d D 8.1 93/06/10 22:17:08 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00131
d D 7.3 93/05/02 05:43:33 akito 3 2
c add PORT related macro
e
s 00014/00006/00117
d D 7.2 92/11/17 16:19:32 akito 2 1
c for bmc driver
e
s 00123/00000/00000
d D 7.1 92/06/15 06:46:05 fujita 1 0
c date and time created 92/06/15 06:46:05 by fujita
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* 
 * sioreg.h -- NEC uPD7201A Hardware Discription
 * by A.Fujita, NOV-26-1991
 */

struct siodevice {
	volatile u_char sio_data;
	u_char sio_pad1;
	volatile u_char sio_cmd;
	u_char sio_pad2;
};

#define sio_stat sio_cmd

#define splsio			spl6


#define REG(u, r)	( (u << 4) | r )
#define CHANNEL(r)	( r >> 4 )
#define REGNO(r)	( r & 0x07 )
#define isStatusReg(r)	( r & 0x08 )

#define WR0		0x00
#define WR1		0x01
#define WR2		0x02
#define WR3		0x03
#define WR4		0x04
#define WR5		0x05
#define WR6		0x06
#define WR7		0x07

D 2
#define WR2A		0x02
#define WR2B		0x12

E 2
#define RR0		0x08
#define RR1		0x09
#define RR2		0x0A
#define RR3		0x0B
#define RR4		0x0C

#define RR2A		0x0A
#define RR2B		0x1A

#define WR0_NOP		0x00	/* No Operation */
#define WR0_SNDABRT	0x08	/* Send Abort (HDLC) */
#define WR0_RSTINT	0x10	/* Reset External/Status Interrupt */
#define WR0_CHANRST	0x18	/* Channel Reset */
#define WR0_INTNXT	0x20	/* Enable Interrupt on Next Receive Character */
#define WR0_RSTPEND	0x28	/* Reset Transmitter Interrput/DMA Pending */
#define WR0_ERRRST	0x30	/* Error Reset */
#define WR0_ENDINTR	0x38	/* End of Interrupt */

#define WR1_ESENBL	0x01	/* External/Status Interrupt Enable */
#define WR1_TXENBL	0x02	/* Tx Interrupt/DMA Enable */
#define WR1_STATVEC	0x04	/* Status Affects Vector (Only Chan-B) */
#define WR1_RXDSEBL	0x00	/* Rx Interrupt/DMA Disable */
#define WR1_RXFIRST	0x08	/* Interrupt only First Character Received */
#define WR1_RXALLS	0x10	/* Interrupt Every Characters Received (with Special Char.) */
#define WR1_RXALL	0x18	/* Interrupt Every Characters Received (without Special Char.) */

#define WR2_INTR_0	0x00	/* Interrupt Priority: RxA TxA RxB TxB E/SA E/SA */
#define WR2_INTR_1	0x04	/* Interrupt Priority: RxA RxB TxA TxB E/SA E/SA */
#define WR2_VEC85_1	0x00	/* 8085 Vectored Mode - 1 */
#define WR2_VEC85_2	0x08	/* 8085 Vectored Mode - 2 */
#define WR2_VEC86	0x10	/* 8086 Vectored */
#define WR2_VEC85_3	0x18	/* 8085 Vectored Mode - 3 */

#define WR3_RXENBL	0x01	/* Rx Enable */
#define WR3_RXCRC	0x08	/* Rx CRC Check */
#define WR3_AUTOEBL	0x20	/* Auto Enable (flow control for MODEM) */
#define WR3_RX5BIT	0x00	/* Rx Bits/Character: 5 Bits */
#define WR3_RX7BIT	0x40	/* Rx Bits/Character: 7 Bits */
#define WR3_RX6BIT	0x80	/* Rx Bits/Character: 6 Bits */
#define WR3_RX8BIT	0xc0	/* Rx Bits/Character: 8 Bits */

#define WR4_NPARITY	0x00	/* No Parity */
I 2
#define WR4_PARENAB	0x01	/* Parity Enable */
E 2
#define WR4_OPARITY	0x01	/* Parity Odd */
#define WR4_EPARITY	0x02	/* Parity Even */
#define WR4_STOP1	0x04	/* Stop  Bits (1bit) */
#define WR4_STOP15	0x08	/* Stop  Bits (1.5bit) */
#define WR4_STOP2	0x0c	/* Stop  Bits (2bit) */
#define WR4_BAUD96	0x40	/* Clock Rate (9600 BAUD) */
#define WR4_BAUD48	0x80	/* Clock Rate (4800 BAUD) */
#define WR4_BAUD24	0xc0	/* Clock Rate (2400 BAUD) */

#define WR5_TXCRC	0x01	/* Tx CRC Check */
D 2
#define WR5_REQSND	0x02	/* Request To Send (LOW) */
E 2
I 2
#define WR5_RTS		0x02	/* Request To Send     [RTS] */
E 2
#define WR5_TXENBL	0x08	/* Transmit Enable */
D 2
#define WR5_BREAK	0x10	/* Send Break */
E 2
I 2
#define WR5_BREAK	0x10	/* Send Break          [BRK] */
E 2
#define WR5_TX5BIT	0x00	/* Tx Bits/Character: 5 Bits */
#define WR5_TX7BIT	0x20	/* Tx Bits/Character: 7 Bits */
#define WR5_TX6BIT	0x40	/* Tx Bits/Character: 6 Bits */
#define WR5_TX8BIT	0x60	/* Tx Bits/Character: 8 Bits */
I 2
#define WR5_DTR		0x80	/* Data Terminal Ready [DTR] */
E 2

#define RR0_RXAVAIL	0x01	/* Rx Character Available */
#define RR0_INTRPEND	0x02	/* Interrupt Pending (Channel-A Only) */
#define RR0_TXEMPTY	0x04	/* Tx Buffer Empty */
D 2
#define RR0_BREAK	0x80	/* Break Detected */
E 2
I 2
#define RR0_DCD		0x08	/* Data Carrier Detect [DCD] */
#define RR0_SYNC	0x10	/* Synchronization */
#define RR0_CTS		0x20	/* Clear To Send       [CTS] */
#define RR0_BREAK	0x80	/* Break Detected      [BRK] */
E 2

#define RR1_PARITY	0x10	/* Parity Error */
#define RR1_OVERRUN	0x20	/* Data Over Run */
#define RR1_FRAMING	0x40	/* Framing Error */

#define RR_RXRDY	0x0100	/* Rx Character Available */
#define RR_INTRPEND	0x0200	/* Interrupt Pending (Channel-A Only) */
#define RR_TXRDY	0x0400	/* Tx Buffer Empty */
I 2
#define RR_DCD		0x0800	/* Data Carrier Detect [DCD] */
#define RR_SYNC		0x1000	/* Synchronization */
#define RR_CTS		0x2000	/* Clear To Send       [CTS] */
E 2
#define RR_BREAK	0x8000	/* Break Detected */
#define RR_PARITY	0x0010	/* Parity Error */
#define RR_OVERRUN	0x0020	/* Data Over Run */
#define RR_FRAMING	0x0040	/* Framing Error */
I 2


#define SIO_HARDADDR	0x51000000			/* build-in serial-interface address */
I 3

#define	NPORT		2
#define	SIO_PORT	0
#define	BMC_PORT	1
E 3
E 2
E 1
