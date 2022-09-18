/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *	pwd() - return the name of the current directory.
 *	We assume that the current directory never changes.
 */

#include "asd.h"

#define CHUNK 64

char *
pwd()
{
	register FILE *f;
	static char *r;
	static unsigned size;
	register int n, c;

	if (r == NULL) {
		f = popen ("pwd", "r");
		schk ((char *) f);
		
		n = 0;
		while ((c = getc (f)) != EOF) {
			if (n >= size) {
				size += CHUNK;
				r = ralloc (r, size);
			}
			r[n++] = c;
		}

		/* replace the trailing newline by a null */
		r[n - 1] = '\0';

		pclose (f);
	}

	return r;
}
