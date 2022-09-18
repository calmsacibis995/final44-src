h49199
s 00002/00002/00032
d D 8.1 93/06/04 13:06:02 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00031
d D 5.4 91/02/23 22:56:35 donn 5 4
c Adjustments and bug fixes after adding prototypes to include files.
e
s 00025/00005/00006
d D 5.3 91/01/20 14:52:35 bostic 4 3
c new stdio version of exit.c; from Chris Torek
e
s 00002/00002/00009
d D 5.2 86/03/09 20:48:40 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00008
d D 5.1 85/06/05 13:32:52 mckusick 2 1
c Add copyright
e
s 00009/00000/00000
d D 1.1 83/06/23 23:31:43 root 1 0
c date and time created 83/06/23 23:31:43 by root
e
u
U
t
T
I 4
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

E 4
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3
E 2

I 5
#include <stdlib.h>
#include <unistd.h>
E 5
D 4
exit(code)
	int code;
E 4
I 4
#include "atexit.h"

void (*__cleanup)();

/*
 * Exit, flushing stdio buffers if necessary.
 */
I 5
void
E 5
exit(status)
	int status;
E 4
{
I 4
	register struct atexit *p;
	register int n;
E 4

D 4
	_cleanup();
	_exit(code);
E 4
I 4
	for (p = __atexit; p; p = p->next)
		for (n = p->ind; --n >= 0;)
			(*p->fns[n])();
	if (__cleanup)
		(*__cleanup)();
	_exit(status);
E 4
}
E 1
