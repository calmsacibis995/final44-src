/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)c_sin.c	5.2 (Berkeley) 4/12/91";
#endif /* not lint */

#include "complex"

c_sin(r, z)
complex *r, *z;
{
double sin(), cos(), sinh(), cosh();

r->real = sin(z->real) * cosh(z->imag);
r->imag = cos(z->real) * sinh(z->imag);
}
