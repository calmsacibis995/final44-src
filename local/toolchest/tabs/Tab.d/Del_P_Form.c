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
 *	Del_P_Form (Winner, x, y, string)
 *
 *	This procedure deletes the specified string in the specified window
 *	at location (x,y) in the window.  A string of blanks is used to "cover"
 *	the old string.  No check is made as to whether the string is actually
 *	present in the window prior to performing the delete operation.
 *
 */

Del_P_Form (Winner, x, y, string)
struct window  *Winner;
int     x;
int     y;
char   *string;
{
	register int i;
	register int j;
	char sbuf[FORM_BUF];

	i = strlen (string);
	for (j = 0; j < i; j++)
	{
		sbuf[j] = ' ';
	}
	sbuf[j] = '\0';
	Print_Form (Winner, x, y, 0, sbuf);
}
