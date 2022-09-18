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
 *      Free_Region (field_ptr)
 *
 *      This procedure frees the space associated with the specified region.
 *      This routine frees a label for the region if present and frees
 *      the window associated with the region.
 *
 */

Free_Region (field_ptr)
register struct field_item      *field_ptr;
{
	register int    index;
	register struct field_item **f;
        
        if (field_ptr == 0)     /* Already Freed */
                return;

        F_Ok (field_ptr, "Free_Region");

	if( field_ptr -> type != CMREGN )
	{
		Del_Field(field_ptr);
		Free_Field(field_ptr);
		return;
	}

        f = ( struct field_item ** )field_ptr -> fnalt;
        F_Ok (f[0], "Free_Region");

	if( field_ptr-> window != f[0] -> window )
	{
	        Push_Rel_Window( f[0] -> window );
		for( index = 0; index < field_ptr->length; Free_Field( f[index++] ) );
	        Free_Rel_Window( f[0] -> window );
	}
	else
	{
		for( index = 0; index < field_ptr->length; Del_Field( f[index] ), Free_Field( f[index++] ) );
	}

	Free_Field( field_ptr );
}
