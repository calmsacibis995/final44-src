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

Ext_Field( field_ptr )
register struct field_item	*field_ptr;
{
	register int	index;
	register struct field_item	*field_p;
	register int	row;
	struct field_item	*skip_field = 0;
	register int	end;
	char	ch;
	int	start;
	int	col;
	int	win_width;
	char	label_where;
	int	label_len;
	int	ncol;
	int	y_col;
	int	x_row;
	int	ret;
	struct field_item	*same_line[ 5 ];
	register int	same_index = 0;
	int	move_em = FALSE;
	int	bottom_x;
	

	Print_Message( field_ptr -> meswin, Mess_Attribute, "Extending field" );
	
	y_col = field_ptr -> window -> _y_pos;

	x_row = field_ptr -> window -> _x_pos;
	end = field_ptr -> y_pos + field_ptr -> length;
	if( field_ptr -> label -> where == 'r' )
		end += strlen( field_ptr -> label -> string );
	win_width = field_ptr -> window -> _bot_y - field_ptr -> window -> _top_y;
	if( end > win_width )
	{
		Print_Message( field_ptr -> meswin,
				 Mess_Attribute,
		"Can not extend - at end of line" );
		sleep( 2 );
		return( 0 );
	}
	col = ( end - win_width );

	for( index = 0; index < GL_Arg_Stack -> count; index++ )
	{
		field_p = GL_Arg_Stack -> f[index];
		F_Ok( field_p, "Extend_Field" );

		label_len = strlen( field_p -> label -> string );
		if( field_p -> label -> where == 'l' )
			ncol = field_p -> y_pos - label_len;
		else
			ncol = field_p -> y_pos;
		
		if( field_ptr -> window == field_p -> window &&
				field_p -> x_pos == row &&
				ncol >= col )
		{
			same_line[same_index++] = field_p;
			move_em = TRUE;
		}
	}
	if( move_em )
	{
		for( index = 0; index < same_index; index++ )
		{
			field_p = same_line[ index ];
			label_len = strlen( field_p -> label -> string );
			if( field_p -> label -> where == 'l' )
				ncol = field_p -> y_pos - label_len;
			else
				ncol = field_p -> y_pos;
		
			ncol++;
			if( label_where == 'b' || 
					label_where == 'a' )
			{
				Print_Message( field_ptr -> meswin, Mess_Attribute,
		"Can not extend because can not move some other field" );
				sleep( 2 );
				return( 0 );
			}
			end = field_p -> y_pos + field_p -> length + label_len;
			if( end >= field_p -> window -> _bot_y -1 )
			{
				Print_Message( field_ptr -> meswin,
						 Mess_Attribute,
				"Can not extend - at bottom of window" );
				sleep( 2 );
				return( 0 );
			}
		}
	}
	ret = Extend( field_ptr );
	w_mgo( field_ptr -> window, x_row, y_col );
	return( ret );
}
