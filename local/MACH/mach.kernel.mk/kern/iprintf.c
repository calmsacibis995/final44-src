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
 * Revision 2.7  91/10/28  13:43:37  mja
 * 	Rewrote the multimax conditional.
 * 	[91/10/07            mrt]
 * 
 * Revision 2.6  91/08/30  09:38:07  berman
 * 	Rig up things to make MACH_KDB conditional happy. The MMAX has an
 * 	external debugger.
 * 	[91/07/30  12:34:07  ern]
 * 
 * Revision 2.5  91/04/03  13:06:46  mbj
 * 	For the luna88k and MACH_KDB, we use ddb's iprintf.
 * 	[91/03/15  18:04:40  rvb]
 * 
 * Revision 2.4  89/02/25  18:04:34  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/12/19  02:45:40  mwyoung
 * 	Don't assume that tab characters work.  Operate inside KDB.
 * 	[88/12/05            mwyoung]
 * 
 */

#include <mach_kdb.h>

#if	(!(defined(luna88k) && MACH_KDB))
int indent = 0;

/*VARARGS1*/
iprintf(a, b, c, d, e, f, g, h)
	char *a;
{
	register int i;

	for (i = indent; i > 0; --i)
#if	MACH_KDB && !(defined(multimax))
		kdbprintc(' ');
	kdbprintf(a, b, c, d, e, f, g, h);
#else	MACH_KDB && !(defined(multimax)
		putchar(' ');
	printf(a, b, c, d, e, f, g, h);
#endif	MACH_KDB && !(defined(multimax))

}
#endif	(!(defined(luna88k) && MACH_KDB))
