/*-
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)getnum.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include <stdio.h>

getnum()
{
	int c, n;

	n = 0;
	while ((c=getchar()) >= '0' && c <= '9')
		n = n*10 + c - '0';
	if (c == EOF)
		return(-1);
	return(n);
}
