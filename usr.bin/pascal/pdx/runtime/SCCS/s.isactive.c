h41975
s 00002/00002/00032
d D 8.1 93/06/06 15:44:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00027
d D 5.2 91/04/16 15:15:33 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00003/00024
d D 5.1 85/06/06 11:49:42 dist 2 1
c Add copyright
e
s 00027/00000/00000
d D 1.1 82/01/18 19:20:57 linton 1 0
c date and time created 82/01/18 19:20:57 by linton
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
 * Decide a the given function is currently active.
 */

#include "defs.h"
#include "runtime.h"
#include "frame.rep"
#include "sym.h"
#include "machine.h"
#include "process.h"

BOOLEAN isactive(f)
SYM *f;
{
	if (isfinished(process)) {
		return(FALSE);
	} else {
		if (f == program) {
			return(TRUE);
		}
		return(findframe(f) != NIL);
	}
}
E 1
