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
 *	fc_length (field_y, c, old_length)
 *
 *	This function returns the printed length of the specified
 *	character.
 *
 *	Tabs are interpreted with ``field_y'' as the starting position of
 *	the string.
 *
 *	The function returns ``old_length'' incremented by the width of
 *	the character.
 */

fc_length (field_y, c, old_length)
register int field_y;
register char    c;
register int	old_length;
{
	switch (ptype[c])
	{
		case TAB:
			return (old_length + (TABSTOP - ((field_y + old_length) % TABSTOP)));

		case CONTRL:
		case BACKSP:
			return (old_length + 2);

		case PLAIN:
		case UL:
		default:
			return (old_length + 1);
	}
}
