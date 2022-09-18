h21231
s 00002/00002/00038
d D 8.1 93/06/10 21:23:08 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00039
d D 7.4 92/06/05 15:23:31 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00039
d D 7.3 90/11/02 16:26:44 mckusick 3 2
c update identifier from Utah
e
s 00006/00000/00034
d D 7.2 90/05/25 15:49:20 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00034/00000/00000
d D 7.1 90/05/08 17:51:14 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 3
 * from: Utah $Hdr: cons.h 1.4 88/12/03$
E 3
I 3
D 4
 * from: Utah $Hdr: cons.h 1.1 90/07/09$
E 4
I 4
 * from: Utah $Hdr: cons.h 1.6 92/01/21$
E 4
E 3
 *
 *	%W% (Berkeley) %G%
 */

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
I 2

#ifdef KERNEL
extern	struct consdev constab[];
extern	struct consdev *cn_tab;
extern	struct tty *cn_tty;
#endif
E 2
E 1
