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


ReShow_All_Lists( clear_flag )
int	clear_flag;
{
	register struct arg_stack	*arg_stack_ptr;
	struct field_item	*field_ptr;

	for( arg_stack_ptr = GL_Arg_Stack; arg_stack_ptr;
			arg_stack_ptr = arg_stack_ptr -> previous )
	{
		ReShow_List( arg_stack_ptr -> f, arg_stack_ptr -> count, 
				clear_flag );
	}
}

ReShow_List (Field_List, Count, clear_flag )
register struct field_item     *Field_List[];
int     Count;
int	clear_flag;
{
	register int    index;
	struct field_item **f;

	for (index = 0; index < Count; index++)
	{
		F_Ok( Field_List[index], "ReShow_List" );
		if (Field_List[index] -> type == CMREGN)
		{
			f = (struct field_item **) Field_List[index] -> fnalt;
			box (f[0] -> window);
			Wrefresh (f[0] -> window);
			ReShow_List (f, Field_List[index] -> length, clear_flag);
		}
		else
		{
			if( clear_flag == TRUE )
				cmini( Field_List[index] );
			ReShow_Field (Field_List[index]);
		}

	}
}

ReShow_Field( field_ptr )
register struct field_item	*field_ptr;
{
	if( field_ptr -> cmflg & CMVERIFY )
		Show_Default_Field ( field_ptr, field_ptr -> txbuf );
	else
	{
		F_Ok (field_ptr, "ReShow_Field");
		Left_Field( field_ptr );
		if (field_ptr -> label)
			Show_Label (field_ptr, field_ptr -> label);
	}
}
