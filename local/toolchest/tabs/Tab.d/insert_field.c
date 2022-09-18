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

insert_field( field_ptr, row )
register struct field_item	*field_ptr;
{
	register int	index;
	register struct field_item	*field_p;
	int	end = 0;
	int	count = 0;
	struct field_item	*f_chg_list[5];
	int	len;
	int	start = 5;

	for( index = *GL_Arg_Stack -> ptr_index; index < GL_Arg_Stack -> count; index++ )
	{
		field_p = GL_Arg_Stack -> f[index];
		if( field_ptr -> window == field_p -> window && field_p -> x_pos == row )
		{
			f_chg_list[count++] = field_p;
			if( field_p -> y_pos > end )
			{
				end = field_p -> y_pos + field_p -> length;
				if( field_p -> label -> where == 'r' )
					end += strlen( field_p -> label -> string );
			}
		}
	}
	len = field_ptr -> length + strlen( field_ptr -> label -> string) + 2;
	if( ( end + len )
		> field_ptr -> window -> _bot_y - field_ptr -> window -> _top_y )
		return( 0 );
	if( count )
	{
		for( index = 0; index < count; index++ )
		{
			field_p = f_chg_list[index];
			Move_Field( field_p, row, field_p -> y_pos + len, 0 );
		}
	}
	else
		insert_line( field_ptr, row );

	if( field_ptr -> label -> where == 'l' )
		start += strlen( field_ptr -> label -> string );
	Move_Field( field_ptr, row, start, 0 );
	return( 1 );
}
