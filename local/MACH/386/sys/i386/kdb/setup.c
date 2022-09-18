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
 * Revision 1.4.1.2  90/01/08  13:26:58  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4.1.1  89/12/21  17:56:03  rvb
 * 	Cleaned up dead code.
 * 
 * Revision 1.4  89/03/09  20:02:13  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:36:01  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 */

/*
 * adb - routines to read a.out+core at startup
 */
#include "defs.h"

setsym(ssym, esym, sstr)
struct nlist *ssym;
struct nlist *esym;
char *sstr;
{
	register struct nlist *sp;
	char *strtab;

	symtab = ssym;
	esymtab = esym;
	strtab = sstr;

#ifdef	wheeze
#else	wheeze
	for (sp = symtab; sp < esymtab; sp++)
		if (sp->n_un.n_strx)
				/* SHOULD PERFORM RANGE CHECK HERE */
				sp->n_un.n_name = strtab + sp->n_un.n_strx;
#endif	wheeze
}
