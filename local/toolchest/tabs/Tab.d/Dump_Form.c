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
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	Dump_Form (Winner, where)
 *
 *	This procedure prints the specified window.  "where" is a stream
 *	pointer obtained from a call to a library like fopen or popen.
 *
 */

Dump_Form (Winner, where)
register struct window *Winner;
FILE *where;
{
	char    pbuf[FORM_BUF];
	register CHAR  *xmap;
	register char  *p;		/* Assume everything goes into regs */
	register int    k;
	int     i;
	int     j;

	W_Ok (Winner, "Dump_Form");

	for (i = Winner -> _top_x, j = 0; i < Winner -> _bot_x; i++, j++)
	{
		p = pbuf;
		xmap = Winner -> _map[j];
		for (k = Winner -> _top_y; k < Winner -> _bot_y;
				k++, xmap++, p++)
		{
			*p = *xmap & VT_CHAR;
			if (*p == 0)
				*p = ' ';
		}
		*p = 0;
		p--;
		while (*p == ' ')
			*p-- = 0;
		fprintf (where, "%s\n", pbuf);
	}
}
