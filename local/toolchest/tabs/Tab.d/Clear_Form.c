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
 *	Clear_Form (Winner)
 *
 *	This procedure clears the specified window.  The windows cursor is
 *	placed at position (0,0) in the window.
 *
 */

Clear_Form (Winner)
register struct window *Winner;
{
	s_werase (Winner);
	if (Winner -> _depth < INVISIBLE)
	{
		if ((CLEAR) && (!CWINDOW) && (Winner == stdwindow))
		{
			clear ();
			Ref_All_Windows ();
			w_xgo (Winner, 0, 0);
			return;
		}
		if(_wclear (Winner))
		{
			Ref_All_Windows ();
		}
		else
		{
			box (Winner);
			Wrefresh (Winner);
		}
	}
	w_xgo (Winner, 0, 0);
}
