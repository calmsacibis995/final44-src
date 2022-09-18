/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)besj0_.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

double j0();

float besj0_(x)
float *x;
{
	return((float)j0((double)*x));
}
