h36312
s 00002/00002/00029
d D 8.1 93/06/10 23:06:39 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00031/00000/00000
d D 7.1 92/11/15 16:28:36 ralph 1 0
c date and time created 92/11/15 16:28:36 by ralph
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct consdev {
	int	cn_disabled;	/* If true use rom I/O routines */
	int	cn_screen;	/* True iff console is a screen/keyboard */
	dev_t	cn_dev;		/* major/minor of device */
	struct	pmax_fb *cn_fb;	/* Frame buffer struct for console screen */
	int	(*cn_getc)();	/* kernel getchar interface */
	int	(*cn_kbdgetc)(); /* kernel keyboard getchar interface */
	void	(*cn_putc)();	/* kernel putchar interface */
	struct	tty *cn_tp;	/* tty structure for console device */
};

/*
 * Major device numbers for possible console devices. XXX
 */
#define	DTOPDEV		15
#define	DCDEV		16
#define	SCCDEV		17
E 1
