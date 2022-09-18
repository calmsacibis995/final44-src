h47995
s 00002/00002/00052
d D 8.1 93/05/31 16:03:36 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00000/00042
d D 5.2 90/04/30 21:24:02 bostic 2 1
c Berkeley headers, SCCS id's
e
s 00042/00000/00000
d D 5.1 90/04/30 21:00:28 bostic 1 0
c date and time created 90/04/30 21:00:28 by bostic
e
u
U
t
T
I 2
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
I 1
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */

#define AUTHOR_STR		"ATC - by Ed James"

#define PI			3.14159654

#define LOWFUEL			15

#define REALLOC			10

#define SGN(x)			((x < 0) ? -1 : ((x > 0) ? 1 : 0))
#define ABS(x)			((x < 0) ? -(x) : (x))
#define DIR_FROM_DXDY(dx,dy)	((int) (atan2((double)(dy), (double)(dx)) \
				* MAXDIR / (2 * PI) + 2.5 + MAXDIR) % MAXDIR)

#define MAXDIR		8

#define D_LEFT		1
#define D_RIGHT		2
#define D_UP		3
#define D_DOWN		4

#define T_NODEST	0
#define T_BEACON	1
#define T_EXIT		2
#define T_AIRPORT	3

#define S_NONE		0
#define S_GONE		1
#define S_MARKED	2
#define S_UNMARKED	3
#define S_IGNORED	4

#define INPUT_LINES	3
#define PLANE_COLS	20
E 1
