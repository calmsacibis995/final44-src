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
#include "windows.h"

term_dep( mp )
register char	*mp;
{
	if ((strncmp (mp, "etty", 4) == 0) ||
		(strncmp (mp, "netty", 5) == 0) ||
		(strncmp (mp, "Tabs", 4) == 0))
	{
		if (strncmp (mp, "netty", 5) == 0)
		{
			_Key( K_MOUSE ) = "\030\037";
			_Key( K_MOUSE2 ) = "\030\035";
		}
		else
			_Key( K_MOUSE ) = "\033#";
		CWINDOW = "\033v%p1%' '%+%c%p2%' '%+%c%p3%' '%+%c%p4%' '%+%c";
		JQTYPE = TRUE;
		UPLEFT = VT_ALTCHAR | 'l';
		UPRIGHT = VT_ALTCHAR | 'k';
		LORIGHT = VT_ALTCHAR | 'j';
		LOLEFT = VT_ALTCHAR | 'm';
		HORIX = VT_ALTCHAR | 'q';
		VERTX = VT_ALTCHAR | 'x';
	}
	else
	if (strncmp (mp, "c10", 3) == 0)
	{
		CWINDOW = "\033v%p1%' '%+%c%p2%' '%+%c%p3%' '%+%c%p4%' '%+%c";
	}
	else
	if (strcmp (mp, "blewett") == 0)
	{
		CWINDOW = "\034v%p1%' '%+%c%p2%' '%+%c%p3%' '%+%c%p4%' '%+%c";
	}
}
