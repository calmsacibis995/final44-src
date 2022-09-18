h54045
s 00002/00002/00042
d D 8.1 93/06/11 15:16:01 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00040
d D 7.3 93/04/20 21:12:50 torek 3 2
c LED_ON and LED_OFF were reversed
e
s 00005/00000/00039
d D 7.2 92/07/21 16:54:18 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00039/00000/00000
d D 7.1 92/07/13 00:44:28 torek 1 0
c date and time created 92/07/13 00:44:28 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: auxreg.h,v 1.5 92/06/17 05:21:55 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: auxreg.h,v 1.8 92/11/26 03:04:45 torek Exp $ (LBL)
E 3
 */

/*
 * Sun-4c Auxiliary I/O register.  This register talks to the floppy
 * (if it exists) and the front-panel LED.
 */

#define	AUXIO_MB1	0xf0		/* must be set on write */
#define	AUXIO_FHD	0x20		/* floppy: high density (unreliable?)*/
#define	AUXIO_FDC	0x10		/* floppy: diskette was changed */
#define	AUXIO_FDS	0x08		/* floppy: drive select */
#define	AUXIO_FTC	0x04		/* floppy: drives Terminal Count pin */
#define	AUXIO_FEJ	0x02		/* floppy: eject disk */
#define	AUXIO_LED	0x01		/* front panel LED */

/*
 * We use a fixed virtual address for the register because we use it for
 * timing short sections of code (via external hardware attached to the LED).
 */
#define	AUXIO_REG	((volatile u_char *)(AUXREG_VA + 3))

D 3
#define LED_ON		*AUXIO_REG = AUXIO_MB1|AUXIO_FEJ
#define LED_OFF		*AUXIO_REG = AUXIO_MB1|AUXIO_FEJ|AUXIO_LED
E 3
I 3
#define LED_ON		*AUXIO_REG = AUXIO_MB1|AUXIO_FEJ|AUXIO_LED
#define LED_OFF		*AUXIO_REG = AUXIO_MB1|AUXIO_FEJ
E 3
#define LED_FLIP	*AUXIO_REG = (*AUXIO_REG | AUXIO_MB1) ^ AUXIO_LED

#define	AUXIO_BITS	"\20\6FHD\5FDC\4FDS\3FTC\2FEJ\1LED"
E 1
