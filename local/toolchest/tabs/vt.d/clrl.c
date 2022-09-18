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

/* clear the rest of the line, checking to see if the line previously
 * displayed corresponds to the one displayed here now
 */

clrl ()
{
	register        x;
	register        y;
	register        z;
	CHAR   *xln;
	int     xcol;

	vputch (0);		/* Turn off all of the attributes */
	if (osert)
		unsert ();

	x = mline;
	z = mcol;
	y = scrjnk[mline] - mcol;
	if (y > 0)
	{
		xln = cmap[mline];
		xcol = mcol;
		while (y--)
		{
			if (xln[xcol] && xln[xcol] != ' ')
			{
				if (CLINE)
				{
					sgo (mline, z);
					SREGION = 1;
					eprintf (CLINE);
					break;
				}
				sgo (mline, xcol);
				vputch (' ');/* wipe line */
				if ((scrcol++ >= SCRWID) && SCRWRAP)
				{
					scrlin++;
					scrcol = 0;
				}
			}
			xcol++;
		}
		scrjnk[x] = z;
	}
}
