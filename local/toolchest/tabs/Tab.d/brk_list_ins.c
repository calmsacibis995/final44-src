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
 *	insert_brk_item (list, c)
 *
 *	The procedure inserts new elements into a break_item list.
 *
 */

struct break_item *
insert_brk_item (list, c)
register struct break_item *list;
register char c;
{
	struct break_item *top;

	top = list;
	while (list)
	{
		if (list -> which == c)
			return (top);

		list = list -> next;
	}

	list = (struct break_item *) malloc (sizeof (struct break_item));
	if (list == 0)
	{
		Print_Message (stdwindow, 0, "Cannot allocate break item space.");
		return (top);
	}

	list -> which = c;
	list -> next = top;

	return (list);
}
