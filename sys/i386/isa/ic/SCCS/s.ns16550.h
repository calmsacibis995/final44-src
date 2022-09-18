h16075
s 00002/00002/00022
d D 8.1 93/06/11 15:55:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00000/00000
d D 7.1 91/05/09 21:40:34 william 1 0
c date and time created 91/05/09 21:40:34 by william
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * NS16550 UART registers
 */

#define	com_data	0	/* data register (R/W) */
#define	com_dlbl	0	/* divisor latch low (W) */
#define	com_dlbh	1	/* divisor latch high (W) */
#define	com_ier		1	/* interrupt enable (W) */
#define	com_iir		2	/* interrupt identification (R) */
#define	com_fifo	2	/* FIFO control (W) */
#define	com_lctl	3	/* line control register (R/W) */
#define	com_cfcr	3	/* line control register (R/W) */
#define	com_mcr		4	/* modem control register (R/W) */
#define	com_lsr		5	/* line status register (R/W) */
#define	com_msr		6	/* modem status register (R/W) */
E 1
