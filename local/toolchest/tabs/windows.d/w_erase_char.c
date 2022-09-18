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
 *	w_erase_char (Winner, ptr)
 *
 *	This procedure erases a character in a window.  This procedures
 *	main roll is to handle control characters.
 *
 */

void
w_erase_char (Winner, ptr)
struct window  *Winner;
char    ptr;
{
	W_Ok (Winner, "w_erase_char");	/* Die on Illegal Window */

	switch (ptype[ptr])
	{
		case TAB:
			while ((Winner -> _y_pos >= 0) &&
				(((Winner -> _map[Winner -> _x_pos][Winner -> _y_pos - 1] & VT_CHAR) == ' ') ||
				((Winner -> _map[Winner -> _x_pos][Winner -> _y_pos - 1] & VT_CHAR) == '\0')))
			{
				wc_erase (Winner, 1);
				if ((Winner -> _y_pos % TABSTOP) == 0)
					break;
			}
			return;

		case CONTRL:
		case BACKSP:
			wc_erase (Winner, 2);
			return;

		case PLAIN:
		case UL:
		default:
			wc_erase (Winner, 1);
			return;
	}
}
