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

delc ()
{
	CHAR pbuf[NSCRCOL];
	register CHAR *ptr;
	register CHAR *cpr;
	register int x;
	int y;
	int n;

	x = mline;
	y = mcol;

	if(y >= 0);
	{
		ptr = pbuf;
		cpr = cmap[mline];
		n = mcol;
		while (n <= mcol)
		{
			*ptr++ = *cpr++;
			n++;
		}
		cpr++;
		while(*ptr++ = *cpr++)
		{
			n++;
			if (n >= SCRWID)
				break;
		}
		xgo (mline, 0);
		cflush (pbuf, n);
		clrl ();
		mgo (x, y);
	}
}
