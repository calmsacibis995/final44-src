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

Set_Overflow (field_ptr, flag)
register struct field_item      *field_ptr;
register char	*flag;
{
	if (flag)
		field_ptr -> txflg |= TXEXT;
	else
		field_ptr -> txflg &= ~(TXEXT);
}
Set_Extend (field_ptr, string)
register struct field_item      *field_ptr;
register char	*string;
{
	register int	len;
	extern char	*realloc();
	extern char	*malloc();
	char	*pch;
	int	len_diff;
	char	buf[256];
	
	F_Ok (field_ptr, "Set_Extend");

	len = strlen (string);
	len_diff = len - field_ptr -> length;

	if (field_ptr -> txflg & TXEXT)
		field_ptr -> fill_char = realloc (field_ptr -> fill_char, len + 1);
	else
		field_ptr -> fill_char = malloc (len + 1);

	field_ptr -> ext_fill_char = string;
	if (len_diff <= 0)
	{
		/* making shorter */
		field_ptr -> txend += len_diff;
		if (field_ptr -> txptr > field_ptr -> txend)
			field_ptr -> txptr = field_ptr -> txend;
		if (field_ptr -> txcursor > field_ptr -> txend)
			field_ptr -> txcursor = field_ptr -> txend;
		field_ptr -> txbuf[len] = '\0';
		field_ptr -> length = len;
		strcpy (field_ptr -> fill_char, string);
	}
	else
	{
		/* extending */
		pch = realloc (field_ptr -> txbuf, len + 2 + MXTRA);
		field_ptr -> txflg |= TXEXT;
		field_ptr -> txcursor = (char *)
				((unsigned int) field_ptr -> txcursor -
				 (unsigned int) field_ptr -> txbuf +
				 (unsigned int) pch);
		field_ptr -> txptr = (char *)
				((unsigned int) field_ptr -> txptr -
				 (unsigned int) field_ptr -> txbuf +
				 (unsigned int) pch);
		field_ptr -> txend = (char *)
				((unsigned int) field_ptr -> txend -
				 (unsigned int) field_ptr -> txbuf +
				 (unsigned int) pch);
		field_ptr -> txbuf = pch;
	}
}
