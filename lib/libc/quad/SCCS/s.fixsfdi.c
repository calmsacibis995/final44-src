h04627
s 00037/00000/00000
d D 5.1 92/07/07 11:46:25 torek 1 0
c date and time created 92/07/07 11:46:25 by torek
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include "quad.h"

/*
 * Convert float to (signed) quad.
 * We clamp anything that is out of range.
 *
 * N.B.: must use new ANSI syntax (sorry).
 */
long long
__fixsfdi(float x)
{
	if (x < 0)
		if (x <= QUAD_MIN)
			return (QUAD_MIN);
		else
			return ((quad_t)-(u_quad_t)-x);
	else
		if (x >= QUAD_MAX)
			return (QUAD_MAX);
		else
			return ((quad_t)(u_quad_t)x);
}
E 1
