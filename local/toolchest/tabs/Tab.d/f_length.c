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
 *	f_length (field_y, string)
 *
 *	This function returns the printed length of the specified string.
 *	Tabs are interpreted with ``field_y'' as the starting position of
 *	the string.
 *
 */

f_length (field_y, string)
int field_y;
char   *string;
{
	register char  *ptr;
	register int    length;

	length = 0;
	ptr = string;
	while (*ptr)
	{
		length = fc_length (field_y, *ptr, length);
		ptr++;
	}

	return (length);
}
