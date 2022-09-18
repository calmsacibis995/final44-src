h12802
s 00037/00037/00135
d D 7.3 90/05/03 17:47:25 sklower 3 2
c first crack at torek changes, may need bug fixes
e
s 00013/00007/00159
d D 7.2 86/12/15 20:26:53 sam 2 1
c lint
e
s 00166/00000/00000
d D 7.1 86/11/20 12:22:07 sam 1 0
c date and time created 86/11/20 12:22:07 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 2

/*
 * adb - symbol table routines
 */
#include "../kdb/defs.h"
#include <stab.h>

/*
 * Initialize the symbol table.
 */
D 3
setsym(sym, esym, strtab, strsize)
E 3
I 3
kdbsetsym(sym, esym, strtab, strsize)
E 3
D 2
	struct nlist *sym, *esym;
	char *strtab;
E 2
I 2
	char *sym, *esym, *strtab;
E 2
{
	register struct nlist *sp;

D 2
	symtab = sym, esymtab = esym;
E 2
I 2
D 3
	symtab = (struct nlist *)sym, esymtab = (struct nlist *)esym;
E 2
	for (sp = symtab; sp < esymtab; sp++)
E 3
I 3
	kdbsymtab = (struct nlist *)sym, kdbesymtab = (struct nlist *)esym;
	for (sp = kdbsymtab; sp < kdbesymtab; sp++)
E 3
		if (sp->n_un.n_strx) {
			if (sp->n_un.n_strx > strsize) {
D 3
				printf("setsym: Bad string table index (%d)\n",
E 3
I 3
				kdbprintf("setsym: Bad string table index (%d)\n",
E 3
				    sp->n_un.n_strx);
				sp->n_un.n_strx = 0;	/* XXX */
				continue;
			}
			sp->n_un.n_name = strtab + sp->n_un.n_strx;
		}
}

/*
 * Lookup a symbol by name.
 */
struct nlist *
D 3
lookup(symstr)
E 3
I 3
kdblookup(symstr)
E 3
	char *symstr;
{
	register struct nlist *sp;

D 3
	cursym = 0;
	if (symtab)
	for (sp = symtab; sp < esymtab; sp++)
E 3
I 3
	kdbcursym = 0;
	if (kdbsymtab)
	for (sp = kdbsymtab; sp < kdbesymtab; sp++)
E 3
		/* SHOULD DO SOME OF EQSYM INLINE TO SAVE TIME */
D 3
		if ((sp->n_type&N_STAB)==0 && eqsym(sp->n_un.n_name, symstr, '_'))
			return(cursym = sp);
E 3
I 3
		if ((sp->n_type&N_STAB)==0 && kdbeqsym(sp->n_un.n_name, symstr, '_'))
			return(kdbcursym = sp);
E 3
	return (0);
}

/*
 * Find the closest symbol to val, and return
 * the difference between val and the symbol found.
 * Leave a pointer to the symbol found as cursym.
 */
D 3
findsym(val, type)
E 3
I 3
kdbfindsym(val, type)
E 3
D 2
	register val;
E 2
I 2
	register long val;
E 2
	int type;
{
	register diff;
	register struct nlist *sp;

D 3
	cursym = 0;
E 3
I 3
	kdbcursym = 0;
E 3
	diff = MAXINT;
D 3
	if (type == NSYM || symtab == 0)
E 3
I 3
	if (type == NSYM || kdbsymtab == 0)
E 3
		return (diff);
D 3
	for (sp = symtab; sp < esymtab; sp++) {
E 3
I 3
	for (sp = kdbsymtab; sp < kdbesymtab; sp++) {
E 3
		if (sp->n_type&N_STAB || (sp->n_type&N_EXT)==0)
			continue;
		if (val - sp->n_value < diff && val >= sp->n_value) {
			diff = val - sp->n_value;
D 3
			cursym = sp;
E 3
I 3
			kdbcursym = sp;
E 3
			if (diff == 0)
				break;
		}
	}
	return (diff);
}

/*
 * Advance cursym to the next local variable.
 * Leave its value in localval as a side effect.
 * Return 0 at end of file.
 */
D 3
localsym(cframe)
E 3
I 3
kdblocalsym(cframe)
E 3
D 2
	ADDR cframe;
E 2
I 2
	long cframe;
E 2
{
	register int type;
	register struct nlist *sp;

D 3
	if (cursym)
	for (sp = cursym; ++sp < esymtab; ) {
E 3
I 3
	if (kdbcursym)
	for (sp = kdbcursym; ++sp < kdbesymtab; ) {
E 3
		type = sp->n_type;
		if (sp->n_un.n_name[0] =='_' || type == N_FN)
			return (0);
		switch (type) {

		case N_TEXT:
		case N_TEXT|N_EXT:
		case N_DATA:
		case N_DATA|N_EXT:
		case N_BSS:
		case N_BSS|N_EXT:
D 3
			localval = sp->n_value;
			cursym = sp;
E 3
I 3
			kdblocalval = sp->n_value;
			kdbcursym = sp;
E 3
			return (1);

		case N_LSYM:
D 3
			localval = cframe - sp->n_value;
			cursym = sp;
E 3
I 3
			kdblocalval = cframe - sp->n_value;
			kdbcursym = sp;
E 3
			return (1);

		case N_PSYM:
		case N_ABS:
D 3
			localval = cframe + sp->n_value;
			cursym = sp;
E 3
I 3
			kdblocalval = cframe + sp->n_value;
			kdbcursym = sp;
E 3
			return (1);
		}
	}
D 3
	cursym = 0;
E 3
I 3
	kdbcursym = 0;
E 3
	return (0);
}

/*
 * Print value v and then the string s.
 * If v is not zero, then we look for a nearby symbol
 * and print name+offset if we find a symbol for which
 * offset is small enough.
 *
 * For values which are just into kernel address space
 * that they match exactly or that they be more than maxoff
 * bytes into kernel space.
 */
D 3
psymoff(v, type, s)
E 3
I 3
kdbpsymoff(v, type, s)
E 3
D 2
	register v;
E 2
I 2
	register long v;
E 2
	int type;
	char *s;
{
	register w;

	if (v) 
D 3
		w = findsym(v, type);
	if (v==0 || w >= maxoff)
		printf(LPRMODE, v);
E 3
I 3
		w = kdbfindsym(v, type);
	if (v==0 || w >= kdbmaxoff)
		kdbprintf(LPRMODE, v);
E 3
	else {
D 3
		printf("%s", cursym->n_un.n_name);
E 3
I 3
		kdbprintf("%s", kdbcursym->n_un.n_name);
E 3
		if (w)
D 3
			printf(OFFMODE, w);
E 3
I 3
			kdbprintf(OFFMODE, w);
E 3
	}
D 3
	printf(s);
E 3
I 3
	kdbprintf(s);
E 3
}

/*
 * Print value v symbolically if it has a reasonable
 * interpretation as name+offset.  If not, print nothing.
 * Used in printing out registers $r.
 */
D 3
valpr(v, idsp)
E 3
I 3
kdbvalpr(v, idsp)
E 3
I 2
	long v;
E 2
{
	register off_t d;

D 3
	d = findsym(v, idsp);
	if (d >= maxoff)
E 3
I 3
	d = kdbfindsym(v, idsp);
	if (d >= kdbmaxoff)
E 3
		return;
D 3
	printf("%s", cursym->n_un.n_name);
E 3
I 3
	kdbprintf("%s", kdbcursym->n_un.n_name);
E 3
	if (d)
D 3
		printf(OFFMODE, d);
E 3
I 3
		kdbprintf(OFFMODE, d);
E 3
}
E 1
