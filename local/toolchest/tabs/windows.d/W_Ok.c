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

W_Ok (Winner, message)
register struct window *Winner;
char *message;
{
	if ((Winner >= _Windows) &&
		(Winner <= &_Windows[TOTAL_WINDOWS - 1]))
	{
		if (Winner -> _bot_x)
			return;		/* Not checking the return */
	}

	_illegal_pointer (message, ": Illegal window pointer.");
}

_illegal_pointer (message, type)
char *message;
char *type;
{
	mgo (0, 0);
	clrl ();
	mgo (0, 0);
	fflush (stdout);

	write (0, message, strlen (message));
	write (0, type, strlen (type));
	sleep (5);
	die (1);
}
