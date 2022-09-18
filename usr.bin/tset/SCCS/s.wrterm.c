h36182
s 00002/00002/00084
d D 8.1 93/06/09 22:54:26 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00085
d D 5.2 91/12/24 10:19:38 bostic 2 1
c remove whitespace on the end of the lines
e
s 00086/00000/00000
d D 5.1 91/12/22 18:55:14 bostic 1 0
c date and time created 91/12/22 18:55:14 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "extern.h"

/*
 * Output termcap entry to stdout, quoting characters that would give the
 * shell problems and omitting empty fields.
 */
void
wrtermcap(bp)
	char *bp;
{
	register int ch;
	register char *p;
	char *t, *sep;

	/* Find the end of the terminal names. */
	if ((t = index(bp, ':')) == NULL)
		err("termcap names not colon terminated");
	*t++ = '\0';

	/* Output terminal names that don't have whitespace. */
	sep = "";
	while ((p = strsep(&bp, "|")) != NULL)
		if (*p != '\0' && strpbrk(p, " \t") == NULL) {
			(void)printf("%s%s", sep, p);
			sep = "|";
		}
	(void)putchar(':');
D 2
		
E 2
I 2

E 2
	/*
	 * Output fields, transforming any dangerous characters.  Skip
	 * empty fields or fields containing only whitespace.
	 */
	while ((p = strsep(&t, ":")) != NULL) {
		while ((ch = *p) != '\0' && isspace(ch))
			++p;
		if (ch == '\0')
			continue;
		while ((ch = *p++) != '\0')
			switch(ch) {
			case '\033':
				(void)printf("\\E");
			case  ' ':		/* No spaces. */
				(void)printf("\\040");
				break;
			case '!':		/* No csh history chars. */
				(void)printf("\\041");
				break;
			case ',':		/* No csh history chars. */
				(void)printf("\\054");
				break;
			case '"':		/* No quotes. */
				(void)printf("\\042");
				break;
			case '\'':		/* No quotes. */
				(void)printf("\\047");
				break;
			case '`':		/* No quotes. */
				(void)printf("\\140");
				break;
			case '\\':		/* Anything following is OK. */
			case '^':
				(void)putchar(ch);
				if ((ch = *p++) == '\0')
					break;
				/* FALLTHROUGH */
			default:
				(void)putchar(ch);
		}
		(void)putchar(':');
	}
}
E 1
