h24855
s 00002/00002/00023
d D 8.1 93/06/10 21:32:19 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00006/00019
d D 7.2 90/11/04 19:21:23 mckusick 2 1
c update from Mike Hibler
e
s 00025/00000/00000
d D 7.1 90/05/08 22:06:35 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* dmago flags */
D 2
#define DMAGO_BYTE	0x00
#define DMAGO_WORD	0x01
#define DMAGO_LWORD	0x02
#define	DMAGO_PRI	0x04
#define	DMAGO_READ	0x08
#define	DMAGO_NOINT	0x80
E 2
I 2
#define	DMAGO_BYTE	0x00	/* do byte (8 bit) transfers */
#define	DMAGO_WORD	0x01	/* do word (16 bit) transfers */
#define	DMAGO_LWORD	0x02	/* do longword (32 bit) transfers */
#define	DMAGO_PRI	0x04	/* do "priority" DMA */
#define	DMAGO_READ	0x08	/* transfer is a read */
#define	DMAGO_NOINT	0x80	/* don't interrupt on completion */
E 2

/* dma "controllers" (channels) */
#define	DMA0		0x1
#define	DMA1		0x2

#ifdef KERNEL
extern void	dmago(), dmafree();
extern int	dmareq();
#endif
E 1
