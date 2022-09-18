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
 *	Print_Center (Winner, x, attribute, string)
 *
 *	The procedure prints the specified string centered on line x in the
 *	specified window.  These routines do NOT handle control and TAB
 *	characters.
 *
 */

Print_Center (Winner, x, attribute, string)
register struct window  *Winner;
int     x;
int     attribute;
char   *string;
{
	register int     mid;

	mid = Winner -> _bot_y - Winner -> _top_y;

	mid = (mid - strlen (string)) / 2;

	if (mid < 0)
		mid = 0;

	w_xgo (Winner, x, mid);

	waxprintf (Winner, attribute, "%s", string);

}
