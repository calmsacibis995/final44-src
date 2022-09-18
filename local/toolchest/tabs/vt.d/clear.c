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

clear ()
{
	register int    i;
	register int    j;

	vputch (0);		/* Turn off all of the attributes */
	if (osert)
		unsert ();

	eprintf (CLEAR);

	for (i = 0; i < SCRNLIN; i++)
	{
		scrjnk[i] = 0;
		for(j = 0; j <= SCRWID; j++) cmap[i][j] = 0;
	}

	scrlin = scrcol = 0;

	mline = mcol = 0;
}
