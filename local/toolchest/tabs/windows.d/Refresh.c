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
#include "vt.h"
#include "windows.h"

/*
 *	Refresh ()
 *
 *	This procedure clears the screen and then updates all of the windows.
 *	This is useful for recovering from things like "wall" messages.
 *
 */

void
Refresh ()
{
	clear ();
	Ref_All_Windows ();
}
