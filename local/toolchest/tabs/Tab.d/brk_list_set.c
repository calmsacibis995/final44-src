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
 *	set_brk_list (list, dscard_type)
 *
 *	The procedure sets the elements of a break_item list.
 *
 */

set_brk_list (list, dscard_type)
register struct break_item *list;
register int dscard_type;
{
	while (list)
	{
		chartyp[(list -> which & 0377)] = dscard_type;
		list = list -> next;
	}
}
