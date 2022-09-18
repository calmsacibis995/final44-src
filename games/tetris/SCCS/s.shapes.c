h33434
s 00002/00002/00083
d D 8.1 93/05/31 17:54:13 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00082
d D 5.2 92/12/23 10:16:48 bostic 2 1
c update copyright notice with contrib notice
e
s 00082/00000/00000
d D 5.1 92/12/22 11:50:42 bostic 1 0
c date and time created 92/12/22 11:50:42 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Chris Torek and Darren F. Provine.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Tetris shapes and related routines.
 *
 * Note that the first 7 are `well known'.
 */

#include <sys/cdefs.h>
#include "tetris.h"

#define	TL	-B_COLS-1	/* top left */
#define	TC	-B_COLS		/* top center */
#define	TR	-B_COLS+1	/* top right */
#define	ML	-1		/* middle left */
#define	MR	1		/* middle right */
#define	BL	B_COLS-1	/* bottom left */
#define	BC	B_COLS		/* bottom center */
#define	BR	B_COLS+1	/* bottom right */

struct shape shapes[] = {
	/* 0*/	7,	TL, TC, MR,
	/* 1*/	8,	TC, TR, ML,
	/* 2*/	9,	ML, MR, BC,
	/* 3*/	3,	TL, TC, ML,
	/* 4*/	12,	ML, BL, MR,
	/* 5*/	15,	ML, BR, MR,
	/* 6*/	18,	ML, MR, /* sticks out */ 2,
	/* 7*/	0,	TC, ML, BL,
	/* 8*/	1,	TC, MR, BR,
	/* 9*/	10,	TC, MR, BC,
	/*10*/	11,	TC, ML, MR,
	/*11*/	2,	TC, ML, BC,
	/*12*/	13,	TC, BC, BR,
	/*13*/	14,	TR, ML, MR,
	/*14*/	4,	TL, TC, BC,
	/*15*/	16,	TR, TC, BC,
	/*16*/	17,	TL, MR, ML,
	/*17*/	5,	TC, BC, BL,
	/*18*/	6,	TC, BC, /* sticks out */ 2*B_COLS,
};

/*
 * Return true iff the given shape fits in the given position,
 * taking the current board into account.
 */
int
fits_in(shape, pos)
	struct shape *shape;
	register int pos;
{
	register int *o = shape->off;

	if (board[pos] || board[pos + *o++] || board[pos + *o++] ||
	    board[pos + *o])
		return 0;
	return 1;
}

/*
 * Write the given shape into the current board, turning it on
 * if `onoff' is 1, and off if `onoff' is 0.
 */
void
place(shape, pos, onoff)
	struct shape *shape;
	register int pos, onoff;
{
	register int *o = shape->off;

	board[pos] = onoff;
	board[pos + *o++] = onoff;
	board[pos + *o++] = onoff;
	board[pos + *o] = onoff;
}
E 1
