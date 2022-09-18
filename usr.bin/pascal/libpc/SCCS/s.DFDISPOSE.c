h06182
s 00002/00002/00037
d D 8.1 93/06/06 15:15:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00030
d D 4.4 90/04/09 18:26:13 bostic 4 3
c written by Kirk McKusick; add Berkeley specific copyright notice
e
s 00001/00001/00031
d D 4.3 86/07/07 18:38:13 mckusick 3 2
c do not get too carried away (from tektronix!sutton <Carl D. Sutton>)
e
s 00001/00001/00031
d D 4.2 83/01/21 18:58:41 mckusick 2 1
c fix for prematurely removing temp files
e
s 00032/00000/00000
d D 4.1 83/01/10 14:50:59 mckusick 1 0
c date and time created 83/01/10 14:50:59 by mckusick
e
u
U
t
T
I 1
D 4
/* Copyright (c) 1982 Regents of the University of California */
E 4
I 4
/*-
D 5
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */
E 4

D 4
static	char sccsid[] = "%W%	(Berkeley)	%G%";
E 4
I 4
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

/*
 * Close all active files within a dynamic record,
 * then dispose of the record.
 */

#include "h00vars.h"
#include "libpc.h"

DFDISPOSE(var, size)
	char	**var;	/* pointer to pointer being deallocated */
	long	size;	/* sizeof(bletch) */
{
	register struct iorec	*next, *prev;
	struct iorec *start, *end;

	start = (struct iorec *)(*var);
	end = (struct iorec *)(*var + size);
	prev = (struct iorec *)(&_fchain);
	next = _fchain.fchain;
	while(next != FILNIL && (next->flev < GLVL || next < start)) {
		prev = next;
		next = next->fchain;
	}
D 3
	while(next != FILNIL && next < end)
E 3
I 3
	while(next != FILNIL && start <= next && next < end)
E 3
D 2
		next = PFCLOSE(next);
E 2
I 2
		next = PFCLOSE(next, TRUE);
E 2
	prev->fchain = next;
	DISPOSE(var, size);
}
E 1
