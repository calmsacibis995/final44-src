h24577
s 00002/00002/00031
d D 8.1 93/06/04 13:07:11 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00002/00032
d D 5.2 91/02/24 13:30:11 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00034/00000/00000
d D 5.1 91/01/20 21:34:53 bostic 1 0
c new stdio
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

D 2
#include <stdio.h>
#include <stdlib.h>
E 2
#include <errno.h>
I 2
#include <stdio.h>
E 2
#include "local.h"
#include "glue.h"

_fwalk(function)
	register int (*function)();
{
	register FILE *fp;
	register int n, ret;
	register struct glue *g;

	ret = 0;
	for (g = &__sglue; g != NULL; g = g->next)
		for (fp = g->iobs, n = g->niobs; --n >= 0; fp++)
			if (fp->_flags != 0)
				ret |= (*function)(fp);
	return (ret);
}
E 1
