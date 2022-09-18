h21871
s 00002/00002/00037
d D 8.1 93/06/11 15:34:34 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00017/00035
d D 7.2 91/05/09 18:19:55 donn 2 1
c final version
e
s 00052/00000/00000
d D 7.1 91/04/13 10:54:24 donn 1 0
c date and time created 91/04/13 10:54:24 by donn
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1990 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1991 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
D 2
 * from: Utah $Hdr: cons.h 1.1 90/07/09$
 *
 *	@(#)cons.h	7.3 (Berkeley) 11/2/90
E 2
I 2
 *	%W% (Berkeley) %G%
E 2
 */
I 2

E 2

struct consdev {
	int	(*cn_probe)();	/* probe hardware and fill in consdev info */
	int	(*cn_init)();	/* turn on as console */
	int	(*cn_getc)();	/* kernel getchar interface */
	int	(*cn_putc)();	/* kernel putchar interface */
	struct	tty *cn_tp;	/* tty structure for console device */
	dev_t	cn_dev;		/* major/minor of device */
	short	cn_pri;		/* pecking order; the higher the better */
};

/* values for cn_pri - reflect our policy for console selection */
#define	CN_DEAD		0	/* device doesn't exist */
#define CN_NORMAL	1	/* device exists but is nothing special */
#define CN_INTERNAL	2	/* "internal" bit-mapped display */
#define CN_REMOTE	3	/* serial interface with remote bit set */

/* XXX */
#define	CONSMAJOR	0

#ifdef KERNEL
extern	struct consdev constab[];
extern	struct consdev *cn_tab;
extern	struct tty *cn_tty;
#endif
E 1
