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
#include "fields.h"

/*
 *	deflt (field_ptr)
 *
 *	This routine is called when a parsing routine wishes to use a
 *	default value.  The main difference between this and complete
 *	is the fact that a default field may not use the current atom buffer.
 */

deflt (field_ptr)
register struct field_item    *field_ptr;
{
	complete (field_ptr, field_ptr -> fndfs);
}
