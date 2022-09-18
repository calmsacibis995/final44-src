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

New_Marked_Area( index, top_row, top_col, bot_row, bot_col)
register int	index;
register int	top_row;
register int	top_col;
register int	bot_row;
register int	bot_col;
{
	Area[index].top_x = top_row;
	Area[index].top_y = top_col;
	Area[index].bot_x = bot_row;
	Area[index].bot_y = bot_col;
}
