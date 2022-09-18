h25101
s 00002/00002/00024
d D 8.1 93/06/11 15:47:47 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00000/00000
d D 7.1 92/07/23 20:13:48 bostic 1 0
c date and time created 92/07/23 20:13:48 by bostic
e
u
U
t
T
I 1
/*-
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
 * William Jolitz.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Screen debug flags
 */
#define	DPAUSE		0x0001	/* wait for key press */
#define	DALLTRAPS	0x0002	/* print on alltraps */
#define	DALLSYSC	0x0004	/* print on allsystem calls */
#define	DSYSFAIL	0x0008	/* print on system call failures */
#define	DPAGIN		0x0010	/* print on pagin activity */
#define	DEXEC		0x0020	/* print on exec activity */
#define	DNAMEI		0x0040	/* print on namei activity */
#define	DEXPAND		0x0080	/* print on segment expand activity */
#define	DCLK		0x0100	/* print on clock activity */
#define	DDSK		0x0200	/* print on disk activity */
#define	DSIGNAL		0x0400	/* print on signal delivery */
E 1
