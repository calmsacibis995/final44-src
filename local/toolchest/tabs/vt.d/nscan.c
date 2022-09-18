/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"

/*VARARGS2*/

char   *
nscan (stptr, ret)
register char  *stptr;
register int   *ret;
{
	register        c;

	*ret = 0;
	while (((c = *stptr) >= '0') && (c <= '9'))
	{
		stptr++;
		*ret = *ret * 10 + (c - '0');
	}
	return (stptr);
}
