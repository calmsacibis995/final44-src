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

/* adjust vertical position of line -- open (or close) lines on */
/* the screen  argument is the number of lines to add (or drop). */

vadjust (xline, tline, x)
register        x;
int     xline;
int     tline;
{
	register        i;
	int     oldx;


	if (LOPEN == NULL)
		return (0);

	oldx = xline;

	if (x < 0)
	{
		x = -x;
		i = 1;
	}
	else
		i = 0;
	SREGION = tline-oldx;		/* effected region */
	if (i)
	{				/* if deleting lines */
		sgo (xline, 0);

		if (SCREG)
		{			/* if vt100 stype scrolling */

#ifdef VT_TERMINFO
			eprintf (SCREG, oldx + XBASE, tline + XBASE);
#else
			eprintf (SCREG, oldx + XBASE, tline + XBASE);
#endif

		/* define region */
			scrlin = scrcol = -100;
			sgo (tline, 0);
			for (i = 0; i < x; i++)
			{
				eprintf (SSCROLL);
			}
#ifdef VT_TERMINFO
			eprintf (SCREG, 0, SCRNLIN - 1);
#else
			eprintf (SCREG, XBASE, SCRNLIN);
#endif
			scrlin = scrcol = -100;
		}
		else
		{
#ifndef TERMCAP
			if (CLDEL)
			{
				eprintf(CLDEL, x+XBASE);
			}
			else
#endif TERMCAP
			{
				for (i = 0; i < x; i++) {
					eprintf(LDEL);
				}
			}
			sgo (tline-x + 1, 0);
#ifndef TERMCAP
			if (CLOPEN)
			{
				eprintf(CLOPEN, x+XBASE);
			}
			else
#endif TERMCAP
			{
				for (i = 0; i < x; i++) {
					eprintf(LOPEN);
				}
			}
		}
		sgo (oldx, 0);
		vshift (oldx, tline, x);
	}
	else
	{
		if (SCREG)
		{			/* if vt100 style scrolling */

#ifdef VT_TERMINFO
			eprintf (SCREG, oldx + XBASE, tline + XBASE);
#else
			eprintf (SCREG, oldx + XBASE, tline + XBASE);
#endif
		/* define region */
			scrlin = scrcol = -100;/* vt100 dies */
			sgo (xline, 0);
			for (i = 0; i < x; i++)
			{
				eprintf (RSCROLL);
			}
#ifdef VT_TERMINFO
			eprintf (SCREG, 0, SCRNLIN - 1);
#else
			eprintf (SCREG, XBASE, SCRNLIN);
#endif
			scrlin = scrcol = -100;
		}
		else
		{
			sgo (tline + 1 - x, 0);
#ifndef TERMCAP
			if (CLDEL)
			{
				eprintf(CLDEL, x+XBASE);
			}
			else
#endif TERMCAP
			{
				for (i = 0; i < x;i++) eprintf(LDEL);
			}
			sgo (oldx, 0);
#ifndef TERMCAP
			if (CLOPEN)
			{
				eprintf(CLOPEN, x+XBASE);
			}
			else
#endif TERMCAP
			{
				for (i = 0; i < x; i++) eprintf(LOPEN);
			}
		}
		mgo (oldx, 0);

		vshift (oldx, tline, -x);
	}
	return (1);
}
