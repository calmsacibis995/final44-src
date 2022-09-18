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
 *	Set_Actions (field_ptr, pre, post)
 *
 *	This procedure sets the pre and post action routies to be
 *	associated with the specified field.
 *
 */

Set_Actions (field_ptr, pre, post)
register struct field_item *field_ptr;
int     (*pre) ();
int     (*post) ();
{
	F_Ok (field_ptr, "Set_Actions");

	field_ptr -> pre_action = pre;
	field_ptr -> post_action = post;
}
