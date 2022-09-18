h38243
s 00002/00002/00044
d D 8.1 93/06/06 15:57:09 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00045
d D 5.2 93/04/30 16:58:55 bostic 2 1
c minor integration in 4BSD source tree
e
s 00046/00000/00000
d D 5.1 93/04/30 13:30:06 muller 1 0
c date and time created 93/04/30 13:30:06 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1991 Keith Muller.
D 2
 * Copyright (c) 1991 The Regents of the University of California.
E 2
I 2
D 3
 * Copyright (c) 1993 The Regents of the University of California.
E 2
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 *
 *      %W% (Berkeley) %G%
 */

/*
 * parameter defaults
 */
#define	CLCNT		1
#define	INCHAR		'\t'
#define	INGAP		8
#define	OCHAR		'\t'
#define OGAP		8
#define	LINES		66
#define	NMWD		5
#define	NMCHAR		'\t'
#define	SCHAR		'\t'
#define	PGWD		72
#define SPGWD		512

/*
 * misc default values
 */
#define	HDFMT		"%s %s Page %d\n\n\n"
#define	HEADLEN		5
#define	TAILLEN		5
#define	TIMEFMT		"%b %e %H:%M %Y"
#define	FNAME		""
#define	LBUF		8192
#define	HDBUF		512

/*
 * structure for vertical columns. Used to balance cols on last page
 */
struct vcol {
	char *pt;		/* ptr to col */
	int cnt;		/* char count */
};
E 1
