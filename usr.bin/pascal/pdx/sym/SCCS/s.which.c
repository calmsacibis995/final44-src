h18653
s 00002/00002/00102
d D 8.1 93/06/06 15:46:00 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00098
d D 5.2 91/04/16 15:03:23 bostic 3 2
c new copyright; att/bsd/shared
e
s 00008/00002/00095
d D 5.1 85/06/06 11:59:50 dist 2 1
c Add copyright
e
s 00097/00000/00000
d D 1.1 82/01/18 19:21:23 linton 1 0
c date and time created 82/01/18 19:21:23 by linton
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
 * Routines to distinguish symbols of the same name.
 */

#include "defs.h"
#include "sym.h"
#include "classes.h"
#include "symtab.h"
#include "mappings.h"
#include "machine.h"
#include "sym.rep"

/*
 * Figure out the "current" symbol being referred to,
 * this is either the active one or the most visible from the
 * current scope.
 *
 * Fields are purposely ignored; these can be gotten to via "findclass".
 */

SYM *which(s)
SYM *s;
{
	register SYM *p, *t, *f;

	if (s == program || isbuiltin(s)) {
		return(s);
	}
	if (!isactive(program)) {
		f = program;
	} else {
		f = whatblock(pc);
		if (f == NIL) {
			panic("no block for addr 0x%x", pc);
		}
	}
	for (p = f; p != NIL; p = p->func) {
		if ((t = findsym(s, p)) != NIL) {
			break;
		}
	}
	if (t == NIL) {
		error("\"%s\" is not known in \"%s\"", s->symbol, f->symbol);
	}
	return(t);
}

/*
 * Find a (non-field) symbol with name s->symbol belonging to block f.
 *
 * Parameters to the main program are purposely "not found" because
 * pi gives them no type.
 */

SYM *findsym(s, f)
SYM *s;
SYM *f;
{
	register SYM *t;

	if (!isblock(f)) {
		error("%s is not a block", f->symbol);
	}
	for (t = s; t != NIL; t = t->next_sym) {
		if (t->func == f && !(f == program && isparam(t)) &&
		  t->class != FIELD && streq(t->symbol, s->symbol)) {
			break;
		}
	}
	return(t);
}

/*
 * Find the symbol which is has the same name and scope as the
 * given symbol but is of the given field.  Return NIL if there is none.
 */

SYM *findclass(s, cl)
SYM *s;
char cl;
{
	register SYM *t;

	if (s->class == cl) {
		return(s);
	}
	t = st_lookup(symtab, s->symbol);
	while (t != NIL && (t->class != cl || t->func != s->func ||
	  !streq(s->symbol, t->symbol))) {
		t = t->next_sym;
	}
	return(t);
}
E 1
