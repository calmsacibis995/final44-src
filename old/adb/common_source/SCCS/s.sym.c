h60741
s 00008/00001/00137
d D 5.3 91/04/04 18:02:01 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00137
d D 5.2 89/04/09 16:16:51 torek 2 1
c typo
e
s 00138/00000/00000
d D 5.1 89/01/16 20:24:49 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 3
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

/*
 * adb - symbol table routines
 */
#include "defs.h"
#include <stab.h>

#define	isstab(sp)	((sp)->n_type & N_STAB)

/*
 * Lookup a symbol by name.
 */
struct nlist *
lookup(symstr)
	register char *symstr;
{
	register struct nlist *sp;

	if (symtab)
		for (sp = symtab; sp < esymtab; sp++)
			if (!isstab(sp) && eqsym(sp->n_un.n_name, symstr, '_'))
				return (sp);
	return (0);
}

/*
 * Find the closest symbol to val, and return it and (through
 * diffp) the difference between val and the symbol found.
 */
struct nlist *
findsym(val, space, diffp)
	register addr_t val;
	int space;
	addr_t *diffp;
{
	register struct nlist *sp;
	register addr_t diff;
	struct nlist *sym;

	diff = ~(addr_t)0;
	sym = NULL;
D 2
	if (space != SP_NONE || symtab != NULL) {
E 2
I 2
	if (space != SP_NONE && symtab != NULL) {
E 2
		for (sp = symtab; sp < esymtab; sp++) {
			/* must be global */
			if (isstab(sp) || (sp->n_type & N_EXT) == 0)
				continue;
			/* and not a function */
			if (sp->n_type == (N_FN|N_EXT))
				continue;
			/* and have a greater address */
			if (val < sp->n_value)
				continue;
			/* and be closer than the last one */
			if (val - sp->n_value >= diff)
				continue;
			sym = sp;
			diff = val - sp->n_value;
			if (diff == 0)
				break;
		}
	}
	*diffp = diff;
	return (sym);
}

/*
 * Return the next local symbol after sym, or NULL at end of such locals.
 */
/* ARGSUSED */
struct nlist *
nextlocal(sym)
	struct nlist *sym;
{

#ifdef busted
	/*
	 * none of this works at the moment, because the symbols are not in
	 * the desired order.
	 */
	if (sym == NULL)
		return (NULL);
	while (++sym < esymtab) {
		/*
		 * External and file name symbols terminate the
		 * list of local symbols.  Otherwise, if it is
		 * a .stabs parameter or local symbol, take it.
		 */
		if ((sym->n_type & N_EXT) || sym->n_type == N_FN)
			break;
		if (sym->n_type == N_LSYM || sym->n_type == N_PSYM)
			return (sym);
	}
#endif
	return (NULL);
}

/*
 * Print value v (in format f) and then (as another format) s.
 * If v is not zero, we look for a nearby symbol and print name+offset
 * if we find a symbol whose offset is small enough (less than o).
 */
psymoff(f, v, space, o, s)
	char *f;
	addr_t v;
	int space;
	addr_t o;
	char *s;
{
	struct nlist *sp;
	addr_t offset;

	if (v && (sp = findsym(v, space, &offset)) != NULL && offset < o)
		adbprintf("%s%?+R", sp->n_un.n_name,
			offset != 0, (expr_t)offset);
	else
		adbprintf(f, (expr_t)v);
	adbprintf(s);
}

/*
 * Print value v symbolically if it has a reasonable
 * interpretation as name+offset.  If not, print nothing.
 * Used in printing out registers $r.
 */
valpr(v, space)
	addr_t v;
	int space;
{
	struct nlist *sp;
	addr_t offset;

	if (v && (sp = findsym(v, space, &offset)) != NULL && offset < maxoff)
		adbprintf("%s%?+R", sp->n_un.n_name,
			offset != 0, (expr_t)offset);
}
E 1
