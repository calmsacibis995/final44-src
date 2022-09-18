h51817
s 00002/00000/00040
d D 8.2 94/07/03 15:08:39 mckusick 4 3
c declare variables extern and define only once (from ralph)
e
s 00002/00002/00038
d D 8.1 93/06/04 13:04:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00037
d D 5.2 90/11/14 12:50:24 bostic 2 1
c broke if registered more than 32 atexit functions; from Chris Torek
e
s 00039/00000/00000
d D 5.1 90/05/15 22:31:39 bostic 1 0
c date and time created 90/05/15 22:31:39 by bostic
e
u
U
t
T
I 1
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
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <stddef.h>
#include <stdlib.h>
#include "atexit.h"

I 4
struct atexit *__atexit;	/* points to head of LIFO stack */

E 4
/*
 * Register a function to be performed at exit.
 */
int
atexit(fn)
	void (*fn)();
{
	static struct atexit __atexit0;	/* one guaranteed table */
	register struct atexit *p;

	if ((p = __atexit) == NULL)
		__atexit = p = &__atexit0;
D 2
	if (p->ind >= ATEXIT_SIZE) {
E 2
I 2
	else if (p->ind >= ATEXIT_SIZE) {
E 2
		if ((p = malloc(sizeof(*p))) == NULL)
			return (-1);
D 2
		__atexit->next = p;
E 2
I 2
		p->ind = 0;
		p->next = __atexit;
E 2
		__atexit = p;
	}
	p->fns[p->ind++] = fn;
	return (0);
}
E 1
