h17043
s 00002/00002/00065
d D 8.1 93/06/06 22:10:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00059
d D 5.4 91/04/24 17:33:41 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00000/00058
d D 5.3 85/06/19 17:33:40 bloom 3 2
c lint fix from rick adams
e
s 00007/00007/00051
d D 5.2 85/01/22 12:28:49 ralph 2 1
c bug fixes & changes from Rick Adams
e
s 00058/00000/00000
d D 5.1 83/07/02 17:56:22 sam 1 0
c date and time created 83/07/02 17:56:22 by sam
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

/*
 * get nonblank, non-comment, (possibly continued) line. Alan S. Watt 
 */

#include <stdio.h>
#define COMMENT		'#'
#define CONTINUE	'\\'
#define EOLN		'\n'
#define EOS		'\0'

I 3
/*LINTLIBRARY*/

E 3
char *
D 2
cfgets (buf, siz, fil)
E 2
I 2
cfgets(buf, siz, fil)
E 2
register char *buf;
int siz;
FILE *fil;
{
	register char *s;
	register i, c, len;
	char *fgets();

D 2
	for (i=0,s=buf; i = (fgets (s, siz-i, fil) != NULL); i = s - buf) {
E 2
I 2
	for (i=0,s=buf; i = (fgets(s, siz-i, fil) != NULL); i = s - buf) {
E 2

		/* get last character of line */
D 2
		c = s[len = (strlen (s) - 1)];
E 2
I 2
		c = s[len = (strlen(s) - 1)];
E 2

		/* skip comments; make sure end of comment line seen */
		if (*s == COMMENT) {
			while (c != EOLN && c != EOF)
D 2
				c = fgetc (fil);
E 2
I 2
				c = getc(fil);
E 2
			*s = EOS;
		}

		/* skip blank lines */
		else if (*s != EOLN) {
			s += len;

			/* continue lines ending with CONTINUE */
			if (c != EOLN || *--s != CONTINUE)
				break;
		}
	}
	
D 2
	return (i ? buf : NULL);
E 2
I 2
	return i ? buf : NULL;
E 2
}

#ifdef TEST
main()
{
	char buf[512];

D 2
	while (cfgets (buf, sizeof buf, stdin))
		fputs (buf, stdout);
E 2
I 2
	while (cfgets(buf, sizeof buf, stdin))
		fputs(buf, stdout);
E 2
}
#endif TEST
E 1
