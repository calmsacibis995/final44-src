h18541
s 00002/00002/00052
d D 8.1 93/06/04 15:12:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00052
d D 5.6 92/08/01 18:56:10 bostic 6 5
c fix the comment
e
s 00001/00001/00053
d D 5.5 91/11/16 10:22:40 bostic 5 4
c header consistency police
e
s 00001/00001/00053
d D 5.4 91/01/26 15:32:07 bostic 4 3
c stdc.h -> cdefs.h
e
s 00035/00037/00019
d D 5.3 90/05/18 18:31:28 marc 3 2
c new calling convention for strsep, takes char **
e
s 00001/00001/00055
d D 5.2 89/10/10 18:07:47 torek 2 1
c strsep("", any) should return "", not NULL
e
s 00056/00000/00000
d D 5.1 88/09/19 12:01:53 bostic 1 0
c strtok, only don't skip multiple separators
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1988 The Regents of the University of California.
E 3
I 3
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
E 3
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

I 3
D 4
#include <sys/stdc.h>
E 4
I 4
#include <sys/cdefs.h>
E 4
#include <string.h>
#include <stdio.h>

E 3
#if defined(LIBC_SCCS) && !defined(lint)
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 5
static const char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
E 3
#endif /* LIBC_SCCS and not lint */

D 3
#include <stdio.h>

E 3
I 3
/*
D 6
 * Get next token from string *stringp, where tokens are nonempty
E 6
I 6
 * Get next token from string *stringp, where tokens are possibly-empty
E 6
 * strings separated by characters from delim.  
 *
 * Writes NULs into the string at *stringp to end tokens.
 * delim need not remain constant from call to call.
 * On return, *stringp points past the last NUL written (if there might
 * be further tokens), or is NULL (if there are definitely no more tokens).
 *
D 6
 * If *stringp is NULL, strtoken returns NULL.
E 6
I 6
 * If *stringp is NULL, strsep returns NULL.
E 6
 */
E 3
char *
D 3
strsep(s, delim)
	register char *s, *delim;
E 3
I 3
strsep(stringp, delim)
	register char **stringp;
	register const char *delim;
E 3
{
D 3
	register char *spanp;
E 3
I 3
	register char *s;
	register const char *spanp;
E 3
	register int c, sc;
D 3
	static char *last;
E 3
	char *tok;

D 3
	if (s == NULL && (s = last) == NULL)
		return(NULL);

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (tok = s;; ++s) {
		c = *s;
E 3
I 3
	if ((s = *stringp) == NULL)
		return (NULL);
	for (tok = s;;) {
		c = *s++;
E 3
		spanp = delim;
		do {
			if ((sc = *spanp++) == c) {
D 3
				if (c == 0) {
					last = NULL;
D 2
					return(tok == s ? NULL : tok);
E 2
I 2
					return(tok);
E 2
				}
				*s++ = '\0';
				last = s;
				return(tok);
E 3
I 3
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*stringp = s;
				return (tok);
E 3
			}
D 3
		} while (sc);
E 3
I 3
		} while (sc != 0);
E 3
	}
	/* NOTREACHED */
}
E 1
