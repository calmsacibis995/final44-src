h09769
s 00001/00001/00018
d D 8.2 94/07/03 15:07:43 mckusick 3 2
c declare variables extern and define only once (from ralph)
e
s 00002/00002/00017
d D 8.1 93/06/04 13:04:51 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00000/00000
d D 5.1 90/05/15 22:31:07 bostic 1 0
c date and time created 90/05/15 22:31:07 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* must be at least 32 to guarantee ANSI conformance */
#define	ATEXIT_SIZE	32

struct atexit {
	struct atexit *next;		/* next in list */
	int ind;			/* next index in this table */
	void (*fns[ATEXIT_SIZE])();	/* the table itself */
};

D 3
struct atexit *__atexit;	/* points to head of LIFO stack */
E 3
I 3
extern struct atexit *__atexit;	/* points to head of LIFO stack */
E 3
E 1
