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

Clear_Marked_Areas ()
{
	register int	i;

	for (i = 0; i < 3; i++)
		Area[ i ].bot_y = 0;

		ReShow_All_Lists (FANORMAL, FALSE);
}
