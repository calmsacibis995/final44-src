/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include "asd.h"

extern char *mktemp(), *strcpy(), *strcat();
static char str[TMPNAML], seed[] = { 'a', 'a', 'a', '\0' };

char *
tmpname(s)
char	*s;
{
	register char *p, *q;

	p = (s == NULL)? str: s;
	(void) strcpy(p, TMPDIR);
	(void) strcat(p, seed);
	(void) strcat(p, "XXXXXX");

	q = seed;
	while(*q == 'z')
		*q++ = 'a';
	++*q;

	(void) mktemp(p);
	return(p);
}
