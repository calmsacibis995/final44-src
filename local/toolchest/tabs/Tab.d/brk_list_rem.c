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
 *	remove_brk_item (list, c)
 *
 *	The procedure removes elements from a break_item list.
 *
 */

struct break_item *
remove_brk_item (list, c)
register struct break_item *list;
register char c;
{
	struct break_item *old_list;
	struct break_item *top;

	old_list = 0;
	top = list;
	while (list)
	{
		if (list -> which == c)
		{
			if (old_list)
				old_list -> next = list -> next;
			else
				top = list -> next;

			free (list);
			return (top);
		}
		old_list = list;
		list = list -> next;
	}

	return (top);
}
