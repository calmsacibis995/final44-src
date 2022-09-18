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

/* Refresh the screen.  Clears and then restores what we think is there */

refresh ()
{
	register        xline;
	register        xcol;
	CHAR pbuf[NSCRCOL];
	CHAR *p;
	CHAR *c;

	vputch (0);		/* Turn off all of the attributes */
	eprintf (CLEAR);

	scrlin = scrcol = mline = mcol = 0;

	for (xline = 0; xline < SCRNLIN; xline++)
	{
		for(xcol = 0, c = cmap[xline], p = pbuf;
				xcol < scrjnk[xline];
					xcol++, p++, c++)
		{
			*p = *c;
			if ((*p & VT_CHAR) == 0)
				*p |= ' ';
			*c = 0;
		}
		scrjnk[xline] = 0;
		mline = xline;
		mcol = 0;
		cflush(pbuf, xcol);
	}
}
