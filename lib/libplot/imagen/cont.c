/*-
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)cont.c	8.1 (Berkeley) 6/4/93";
#endif /* not lint */

#include <stdio.h>
#include "imp.h"

cont(x,y){
	line(imPx, imPy, x, y);
	
}