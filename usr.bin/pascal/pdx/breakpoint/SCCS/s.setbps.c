h46719
s 00002/00002/00040
d D 8.1 93/06/06 15:32:47 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00035
d D 5.2 91/04/16 15:39:12 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00003/00032
d D 5.1 85/06/05 16:58:34 dist 2 1
c Add copyright
e
s 00035/00000/00000
d D 1.1 82/01/18 19:19:59 linton 1 0
c date and time created 82/01/18 19:19:59 by linton
e
u
U
t
T
I 1
D 2
/* Copyright (c) 1982 Regents of the University of California */
E 2
I 2
D 3
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
E 3
 */
E 2

D 2
static char sccsid[] = "%Z%%M% %I% %G%";

E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */

E 3
E 2
/*
 * set all breakpoints in object code
 */

#include "defs.h"
#include "breakpoint.h"
#include "process.h"
#include "machine.h"
#include "bp.rep"

setallbps()
{
	register BPINFO *p;

	for (p = bphead; p != NIL; p = p->bpnext) {
		setbp(p->bpaddr);
	}
}

/*
 * undo damage done by "setallbps"
 */

unsetallbps()
{
	register BPINFO *p;

	for (p = bphead; p != NIL; p = p->bpnext) {
		unsetbp(p->bpaddr);
	}
}
E 1
