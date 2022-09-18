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
 * $Log:	iprintf.c,v $
 * Revision 2.4  89/02/25  18:04:34  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/12/19  02:45:40  mwyoung
 * 	Don't assume that tab characters work.  Operate inside KDB.
 * 	[88/12/05            mwyoung]
 * 
 */

#include <mach_kdb.h>

int indent = 0;

/*VARARGS1*/
iprintf(a, b, c, d, e, f, g, h)
	char *a;
{
	register int i;

	for (i = indent; i > 0; --i)
#if	MACH_KDB
		kdbprintc(' ');
#else	MACH_KDB
		putchar(' ');
#endif	MACH_KDB

#if	MACH_KDB
	kdbprintf(a, b, c, d, e, f, g, h);
#else	MACH_KDB
	printf(a, b, c, d, e, f, g, h);
#endif	MACH_KDB
}
