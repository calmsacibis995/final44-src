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

Pop_Rel_Window( window, depth )
struct window	*window;
int	depth;
{
	W_Ok( window, "Pop_Window" );
	if (window -> _depth != depth)
	{
		if( depth == INVISIBLE )
			depth += 199;
		Move_Rel_Window( window, window -> _top_x, window -> _top_y, depth );
		Ref_All_Windows();
	}
	fflush (stdout);
}
Push_Rel_Window( window )
struct window	*window;
{
	W_Ok(window, "Push_Window" );
	Pop_Rel_Window( window, INVISIBLE );
}
