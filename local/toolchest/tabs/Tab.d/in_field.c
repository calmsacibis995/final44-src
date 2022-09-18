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

in_field( field_ptr, x, y )
register struct field_item	*field_ptr;
register int	x;
register int	y;
{
	register int	field_len;
	register int	win_width;
	register int	rows;
	register int	len;
	register int	nrows;
	
	field_len = field_ptr -> length;
	win_width = field_ptr -> window -> _bot_y - 
			field_ptr -> window -> _top_y;
	nrows = (field_len + field_ptr -> y_pos )/win_width;

	/* check if field exists on x row */
	if( field_ptr -> x_pos <= x &&
		field_ptr -> x_pos + nrows >= x )
	{
		rows = x - field_ptr -> x_pos;
		if( rows )
			len = win_width - field_ptr -> y_pos;
		else
		{
			if( y >= field_ptr -> y_pos && 
					y <= field_ptr -> y_pos + field_len )
			{
				if( move_txcursor( field_ptr, x, y ) == 0 )
				{	
					_position( field_ptr );
				}
				return( TRUE );
			}
			else
				return( FALSE );
		}
		if( rows )
			len += y;
		rows--;
		len += ( win_width * rows );
		if( len > field_len )
			return( FALSE );
		if( move_txcursor( field_ptr, x, y ) == 0 )
		{	
			_position( field_ptr );
		}
		return( TRUE );
	}
	return( FALSE );
}
_position( field_ptr )
register struct field_item	*field_ptr;
{
	if( Keep_Cursor_Pos )
		return( FALSE );

	if (_Entry_Type == FAR_LEFT)
		field_ptr -> txcursor = field_ptr -> txbuf;
	else
		field_ptr -> txcursor = field_ptr -> txptr;
	return( TRUE );
}
