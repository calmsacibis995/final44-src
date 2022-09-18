/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sym.c,v $
 * Revision 2.2  89/02/25  20:24:04  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 *  7-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made findsym ignore symbols outside kernel if kernel debugger -
 *	avoids printing 'INCLUDE_VERSION' for stack offsets.
 *
 */

/* static	char sccsid[] = "@(#)sym.c 4.1 5/14/81";*/

/*
 * adb - symbol table routines
 */

#include <vax/kdb/defs.h>
#include <stab.h>

/*
 * Lookup a symbol by name.
 */
struct nlist *
lookup(symstr)
char *symstr;
{
	register struct nlist *sp;

	cursym = 0;
	if (symtab)
		for (sp = symtab; sp < esymtab; sp++)
			/* SHOULD DO SOME OF EQSYM INLINE TO SAVE TIME */
			if ((sp->n_type&N_STAB)==0 && eqsym(sp->n_un.n_name, symstr, '_'))
				return(cursym = sp);
	return (0);
}

/*
 * Find the closest symbol to val, and return
 * the difference between val and the symbol found.
 * Leave a pointer to the symbol found as cursym.
 */
findsym(val, type)
long val;
int type;
{
	long diff;
	register struct nlist *sp;

	cursym = 0;
	diff = MAXINT;
	if (type == NSYM || symtab == 0)
		return (diff);
	for (sp = symtab; sp < esymtab; sp++) {
		if (sp->n_type&N_STAB || (sp->n_type&N_EXT)==0)
			continue;
		/*
				 *	Ignore symbols outside kernel.
				 */
		if ((sp->n_value & 0x80000000) == 0)
			continue;
		if (val - sp->n_value < diff && val >= sp->n_value) {
			diff = val - sp->n_value;
			cursym = sp;
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
localsym(cframe, cargp)
long cframe, cargp;
{
	register struct nlist *sp;

	if (cursym)
		for (sp = cursym; ++sp < esymtab; ) {
			if (sp->n_un.n_name[0] =='_' || sp->n_type == N_FN)
				return (0);
			switch (sp->n_type) {

			case N_TEXT:
			case N_TEXT|N_EXT:
			case N_DATA:
			case N_DATA|N_EXT:
			case N_BSS:
			case N_BSS|N_EXT:
				localval = sp->n_value;
				cursym = sp;
				return (1);

			case N_LSYM:
				localval = cframe - sp->n_value;
				cursym = sp;
				return (1);

			case N_PSYM:
				/* code below works since n_value > 0 */
			case N_ABS:
				localval = cargp + sp->n_value;
				cursym = sp;
				return (1);
			}
		}
	cursym = 0;
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
psymoff(v, type, s)
long v;
int type;
char *s;
{
	long w;

	if (v)
		w = findsym(v, type);
	if (v==0 || w >= maxoff)
			printf(LPRMODE, v);
		else {
			printf("%s", cursym->n_un.n_name);
			if (w)
				printf(OFFMODE, w);
		}
	printf(s);
}

/*
 * Print value v symbolically if it has a reasonable
 * interpretation as name+offset.  If not, print nothing.
 * Used in printing out registers $r.
 */
valpr(v, idsp)
long v;
{
	off_t d;

	d = findsym(v, idsp);
	if (d >= maxoff)
		return;
	printf("%s", cursym->n_un.n_name);
	if (d)
		printf(OFFMODE, d);
}
