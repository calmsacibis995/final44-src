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

die (arg)
int     arg;
{
	mgo (SCRNLIN - 1, 0);
	clrl ();
	cook ();
	if (arg)
		abort (arg);
	else
		exit (0);
}
