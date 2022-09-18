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
 *	Print_Form (Winner, x, y, attribute, string)
 *
 *	This procedure prints the specified string in the specified window
 *	at location (x,y) in the window.
 *
 */

Print_Form (Winner, x, y, attribute, string)
register struct window  *Winner;
int     x;
int     y;
int     attribute;
char   *string;
{
	w_xgo (Winner, x, y);

	waxprintf (Winner, attribute, "%s", string);
}
