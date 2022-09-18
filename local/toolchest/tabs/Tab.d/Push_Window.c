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
 *	Push_Window (Winner)
 *
 *	The procedure moves the specified window to hyperspace (level INVISIBLE).
 *
 */

Push_Window (Winner)
register struct window  *Winner;
{
	W_Ok (Winner, "Push_Window");

	Pop_Window (Winner, INVISIBLE);
}

Pop_Window (Winner, depth)
register struct window  *Winner;
register int depth;
{
	W_Ok (Winner, "Pop_Window");

	if (Winner -> _depth != depth)
	{
		Move_Window (Winner,
				Winner -> _top_x,
				Winner -> _top_y, depth);
		Ref_All_Windows ();
	}
	fflush (stdout);
}
