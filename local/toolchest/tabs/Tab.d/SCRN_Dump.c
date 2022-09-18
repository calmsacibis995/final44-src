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
 *	SCRN_Form (where)
 *
 *	This procedure prints the screen to a UNIX(TM) stream.  "where"
 *	is a stream pointer obtained from a call to a library like
 *	fopen or popen.
 *
 */

SCRN_Dump (where)
FILE *where;
{
	register        xline;
	register        xcol;
	char pbuf[NSCRCOL];
	char *p;
	CHAR *c;

	for (xline = 0; xline < SCRNLIN; xline++)
	{
		for(xcol = 0, c = cmap[xline], p = pbuf;
				xcol < scrjnk[xline];
					xcol++, p++, c++)
		{
			*p = *c & VT_CHAR;
			if(*p == 0)
				*p = ' ';
		}
		*p = 0;
		p--;
		while (*p == ' ')
			*p-- = 0;
		fprintf (where, "%s\n", pbuf);
	}
}
