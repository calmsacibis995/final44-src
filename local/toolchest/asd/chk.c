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

/*
 *	little subroutines to check return codes
 */

nchk (n)
	register int n;
{
	if (n < 0) {
		fprintf (stderr, "unexpected error return -- help!\n");
		exit (1);
	}
}

schk (s)
	register char *s;
{
	if (s == NULL) {
		fprintf (stderr, "unexpected error return -- help!\n");
		exit (1);
	}
}
