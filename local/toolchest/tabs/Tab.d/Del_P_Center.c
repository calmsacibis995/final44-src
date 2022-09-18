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
 *	Del_P_Center (Winner, x, string)
 *
 *	The procedure deletes the specified string centered on line x in the
 *	specified window.
 *
 */

Del_P_Center (Winner, x, string)
struct window  *Winner;
int     x;
char   *string;
{
	register int i;
	register int j;
	char sbuf[132];

	i = strlen (string);
	for (j = 0; j < i; j++)
	{
		sbuf[j] = ' ';
	}
	sbuf[j] = '\0';
	Print_Center (Winner, x, 0, sbuf);
}
