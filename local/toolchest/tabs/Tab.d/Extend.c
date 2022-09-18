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

Extend( field_ptr )
register struct field_item	*field_ptr;
{
	register char	*pch;
	register int	diff;
	char	*malloc();
	char	*realloc();
	static char	*fill_char = 0;
	register int	len;

	len = field_ptr -> length++;
	if( len >= 255 || field_ptr -> ext_fill_char[ len ] == '\0')
	{
		field_ptr-> length--;
		field_ptr -> txflg &= ~(TXEXT);
		return(FALSE);
	}

	/* add to fill_char */
	field_ptr -> fill_char[len] = field_ptr -> ext_fill_char[len];
	field_ptr -> fill_char[field_ptr -> length] = '\0';

	/* add to txbuf */
	field_ptr -> txbuf[field_ptr -> length] = '\0';
	field_ptr -> txend++;
	ReShow_Field( field_ptr );	
	return(TRUE);
}
