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

/* move the display cursor to the specified destination.  sgo attempts
 * to optimize the movement, using single character or absolute
 * positioning
 */

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

sgo (x, y)
register int    x;
register int    y;
{
	int     mx;
	int     my;
	int     xcost;			/* cost with all relative movement */
	int     ycost;			/* cost with carriage return */
	int	home;

	home = FALSE;

 /* acost is cost of absolute positioning */

/* calculate relative costs of various movements.  cost functions  */
/* automatically indicate that un-doable motions have infinite cost */

	vputch (0);		/* Turn off all of the attributes */
	if (osert)
		unsert ();

 /* calculate xcost and ycost */

	if ((scrlin < 0) || (scrcol < 0))
	{
		xcost = acost + 1;
		ycost = acost + 1;
		mx = x;
		my = y;
		scrlin = 0;
		scrcol = 0;
		if (HOME)
			home = TRUE;
	}
	else
	{
		mx = x - scrlin;
		if (mx < 0)
		{
			mx = -mx;
			xcost = mx * lUP;
		}
		else
			xcost = mx * lDOWN;

		ycost = y + xcost + lCR;

		my = y - scrcol;
		if (my < 0)
		{
			my = -my;
			xcost += my * lBAK;
		}
		else
			xcost += my * lFORWARD;
	}


	if (acost < ycost)
	{
		if (acost < xcost)
		{
		/* do absolute positioning */
#ifdef TERMCAP
			putpad (tgoto (CURAD, y, x));
#else
			if (CURAD) {	/* have absolute addrs */
#ifdef VT_TERMINFO
				eprintf(CURAD, x, y);
#else
				if (SRCADD) {
					eprintf(CURAD,x+XBASE,y+YBASE);
				} else { 
					eprintf(CURAD,y+YBASE,x+XBASE);
				}
			} else {	/* have relative addrs */
				if (home) eprintf (HOME);
				if (x>scrlin) eprintf (RELDOWN,mx);
				if (x<scrlin) eprintf (RELUP,mx);
				if (y>scrcol) eprintf (RELFORW,my);
				if (y<scrcol) eprintf (RELBACK,my);
#endif VT_TERMINFO
			}
#endif TERMCAP
			scrlin = x;
			scrcol = y;
			return;
		}			/* else relative is cheap, do it */
	}
	else
	{
		if (osert && (MI == 0))
		{
			unsert ();	/* LEAVE insert character mode */
		}
		if (ycost < xcost)
		{

			eprintf (CR);	/* do carriage return processing */
			scrcol = 0;

		}
	}

 /* fall through to finish with relative motion */

	while (x != scrlin)
	{
		if (x < scrlin)
		{
			eprintf (UP);
			scrlin--;
		}
		else
		{
			eprintf (DOWN);
			scrlin++;
		}
	}

 /* now correct row */

	while (y != scrcol)
	{
		if (y < scrcol)
		{
			eprintf (BACK);
			scrcol--;
		}
		else
		{
			if (FORWARD == NULL)
			{
				if (osert)
				{
					unsert ();
				}
				
				if (cmap[scrlin][scrcol] == 0)
					cmap[scrlin][scrcol] = ' ';
				vputch (cmap[scrlin][scrcol]);
			}
			else
			{
				eprintf (FORWARD);
			}
			scrcol++;
		}
	}

	return;
}
