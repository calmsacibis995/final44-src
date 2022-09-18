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

Ext_Long_Field( field_ptr )
register struct field_item	*field_ptr;
{
	register int	index;
	register struct field_item	*field_p;
	register int	row;
	struct field_item	*skip_field = 0;
	register int	end;
	char	ch;
	int	start;
	int	nrows;
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
	nrows = end / (win_width + 1);
	row = field_ptr -> x_pos + nrows;
	col = end - ( nrows * win_width ) + 2;

	for( index = 0; index < GL_Arg_Stack -> count; index++ )
	{
		field_p = GL_Arg_Stack -> f[index];
		F_Ok( field_p, "Extend_Long_Field" );

		label_len = strlen( field_p -> label -> string );
		if( field_p -> label -> where == 'l' )
			ncol = field_p -> y_pos - label_len;
		else
			ncol = field_p -> y_pos;
		
		if( field_ptr -> window == field_p -> window &&
				field_p -> x_pos == row &&
				ncol >= col - 3 )
		{
			same_line[same_index++] = field_p;
		}
		
		if( field_ptr -> window == field_p -> window &&
				field_p -> x_pos == row &&
				ncol <= col && 
				ncol >= col - 3 )
		{
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
				return( 0 );
			}
			end = field_p -> y_pos + field_p -> length + label_len;
			if( end >= field_p -> window -> _bot_y )
			{
				ncol = 2;
				if( label_where == 'l' )
					ncol += label_len;
				/* add to next line if fits */
				if( insert_field( field_p, row + 1 ) )
					continue;

				/* move field to next line after insert blank line */
				if( !insert_line( field_ptr, row ) )
				{
					Print_Message( field_ptr -> meswin,
						 Mess_Attribute,
		"Can not extend because the next field can not be moved" );
					return( 0 );
				}
				bottom_x = field_p -> window -> _bot_x;
				if( field_p -> window == field_p -> meswin )
					bottom_x--;
				if( field_p -> window -> _top_x + field_p -> x_pos >= 
					bottom_x )
				{
					Print_Message( field_ptr -> meswin, Mess_Attribute,
		"Can not extend because the next field can not be moved" );
					return( 0 );
				}
				Move_Field( field_p, field_p -> x_pos + 1,
						ncol, 0 );
			}
			else
			{
				Move_Field( field_p, field_p -> x_pos,
					field_p -> y_pos + 1, 0 );
				continue;
			}
		}
	}
	ret = Extend( field_ptr );
	w_mgo( field_ptr -> window, x_row, y_col );
	return( ret );
}

