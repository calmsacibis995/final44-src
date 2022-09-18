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

move_txcursor( field_ptr, x, y )
register struct field_item	*field_ptr;
register int	x;
register int	y;
{
	register char	*pch;
	int	tx_length;
	register struct window	*Winner;
	register int	attributes;

	if (field_ptr -> type == CMREGN)
		return (FALSE);

	Winner = field_ptr -> window;
	attributes = field_ptr -> attribute;
	
	*field_ptr -> txptr = '\0';
	pch = field_ptr -> txbuf;
	/* make adjustments to location of field if zapped by Right_Field or 
	 * Center_Field
	 */

	if( field_ptr -> cmflg & CMTAMPR && !(attributes & FALEFT) )
	{
		tx_length = f_length( field_ptr -> y_pos, field_ptr -> txbuf );
		if( attributes & FARIGHT )
			/* need to figure out where start of field really is */
			y += field_ptr -> length - tx_length;
		else if( attributes & FACENTER )
			y += ( field_ptr -> length - tx_length ) / 2;
	}

	w_xgo( Winner, field_ptr -> x_pos, field_ptr -> y_pos );
	while( TRUE )
	{
		if( Winner -> _y_pos == y &&
				Winner -> _x_pos == x )
		{
			field_ptr -> txcursor = pch;
			return( TRUE );
		}
		if( *(pch) == '\0' )
			break;
		waxprintf( Winner, attributes, "%c", *pch++ );
	}
	field_ptr -> txcursor = pch;
	return( FALSE );
}
