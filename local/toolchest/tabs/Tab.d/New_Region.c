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

New_Region (winner, Field_List, count, rows, Field_Region, skip)
struct window  *winner;
struct field_item     **Field_List;
int     count;
int     rows;
struct field_item     **Field_Region;
int     skip;
{
	extern struct field_item *Dup_Field ();
	register int    index;
	register int    j;
	register int    i;

	winner -> _type_scroll = TRUE;		/* Make sure it scrolls */

	index = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < count; j++)
		{
			if ((Field_Region[index] = Dup_Field (Field_List[j])) == 0)
				return;
			Field_Region[index] -> window = winner;
			Field_Region[index] -> meswin = winner;
			Field_Region[index] -> x_pos = Field_Region[index] -> x_pos + i * skip;
			if (Field_Region[index] -> x_pos >= (winner -> _bot_x - winner -> _top_x - 1))
				Field_Region[index] -> x_pos += 512;
			index++;
		}
	}
}
