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

/* sscroll -- try to fix display by scrolling */

sscroll (x)
register int    x;
{
	register int    i;

	if (SSCROLL == NULL || (SCRNLIN - 2 - x < 3))
		return;

	sgo (SCRNLIN - 1, 0);		/* to bottom */
	SREGION = SCRNLIN;		/* number of lines effected */
	if (CLSCROLL)
	{
		eprintf (CLSCROLL, x + XBASE);
	}
	else
	{
		for (i = 0; i < x; i++)
		{
			eprintf (SSCROLL); /* scroll screen */
		}
	}
	vshift (0, SCRNLIN - 1, x);
}
