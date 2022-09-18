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
 *	wsputc (Winner, c)
 *
 *	This procedure prints a character in the specified window.
 *	This procedure is provided only for compatibility with other systems.
 *
 */

void
wsputc (Winner, c)
register struct window *Winner;
register char   c;
{
	wxprintf (Winner, "%c", c);	/* hmmm..... */
}
