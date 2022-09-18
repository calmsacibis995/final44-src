h18883
s 00001/00001/00053
d D 8.3 94/03/20 14:35:10 bostic 5 4
c delete UofT; requested change from Henry Spencer <henry@zoo.toronto.edu>
e
s 00003/00003/00051
d D 8.2 94/03/16 12:43:03 bostic 4 3
c alpha3.3
e
s 00002/00002/00052
d D 8.1 93/06/04 12:58:23 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00051
d D 5.2 93/05/21 16:06:57 bostic 2 1
c Henry Spencer's Alpha 3.0 regex release
e
s 00053/00000/00000
d D 5.1 92/08/06 11:58:12 bostic 1 0
c date and time created 92/08/06 11:58:12 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 Henry Spencer.
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
E 4
I 4
 * Copyright (c) 1992, 1993, 1994 Henry Spencer.
 * Copyright (c) 1992, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
D 5
 * Henry Spencer of the University of Toronto.
E 5
I 5
 * Henry Spencer.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 2

E 2
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "utils.h"
#include "regex2.h"

/*
 - regfree - free everything
I 2
D 4
 = extern void regfree(regex_t *preg);
E 4
I 4
 = extern void regfree(regex_t *);
E 4
E 2
 */
void
regfree(preg)
regex_t *preg;
{
	register struct re_guts *g;

	if (preg->re_magic != MAGIC1)	/* oops */
		return;			/* nice to complain, but hard */

	g = preg->re_g;
	if (g == NULL || g->magic != MAGIC2)	/* oops again */
		return;
	preg->re_magic = 0;		/* mark it invalid */
	g->magic = 0;			/* mark it invalid */

	if (g->strip != NULL)
		free((char *)g->strip);
	if (g->sets != NULL)
		free((char *)g->sets);
	if (g->setbits != NULL)
		free((char *)g->setbits);
	if (g->must != NULL)
D 2
		free((char *)g->must);
E 2
I 2
		free(g->must);
	free((char *)g);
E 2
}
E 1
