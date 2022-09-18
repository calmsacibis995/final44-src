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

insert_line( field_ptr, row )
register struct field_item	*field_ptr;
register int	row;
{
	register int	index;
	register struct field_item	*field_p;
	register int	bottom_x;

	for( index = 0; index < GL_Arg_Stack -> count; index++ )
	{
		field_p = GL_Arg_Stack -> f[index];
		if( field_p -> x_pos > row && field_ptr -> window == field_p -> window )
		{
			bottom_x = field_p -> window -> _bot_x;
			if( field_p -> window == field_p -> meswin )
				bottom_x--;
			
			if( field_p -> window -> _top_x + field_p -> x_pos >= 
				bottom_x )
				return( 0 );
			Move_Field( field_p, field_p -> x_pos + 1,
					field_p -> y_pos, 0 );
		}
	}
	return( 1 );
}
