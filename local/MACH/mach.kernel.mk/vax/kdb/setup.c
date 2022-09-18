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
 * $Log:	setup.c,v $
 * Revision 2.2  89/02/25  20:23:50  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 */

/* static	char sccsid[] = "@(#)setup.c	4.6 82/10/28"; */

/*
 * adb - routines to read a.out+core at startup
 */

#include <vax/kdb/defs.h>

setsym(ssym, esym, sstr)
struct nlist *ssym;
struct nlist *esym;
char *sstr;
{
	register struct nlist *sp;
	char *strtab;

	setcor();

	symtab = ssym;
	esymtab = esym;
	strtab = sstr;
	for (sp = symtab; sp < esymtab; sp++)
		if (sp->n_un.n_strx)
				/* SHOULD PERFORM RANGE CHECK HERE */
				sp->n_un.n_name = strtab + sp->n_un.n_strx;
}

setcor()
{
	txtmap.e1 = -1;
	datmap.e1 = -1;
}


setvar()
{
}
