h28597
s 00053/00032/00092
d D 8.2 94/04/16 14:13:35 bostic 8 7
c Fixed the most major defect in fnmatch(): backslash-escape processing in
c bracket expressions.
c Implement the FNM_PERIOD flag.
c Random ANSI C cleanups, KNF, prettiness police
c From: conklin@ngai.kaleida.com (J.T. Conklin)
e
s 00002/00002/00122
d D 8.1 93/06/04 12:01:44 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00120
d D 5.6 92/06/28 13:00:58 bostic 6 5
c get the const's right
e
s 00051/00047/00073
d D 5.5 92/06/28 12:58:27 bostic 5 4
c bring up to date with POSIX 1003.2 D11.2; still broken, but at least
c the return values are right, now
e
s 00002/00001/00118
d D 5.4 91/02/23 19:49:38 donn 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00028/00028/00091
d D 5.3 90/06/23 16:35:31 bostic 3 2
c rearrange to make ANSI compilers happy;
c f() { char *g(); } is an implicit extern declaration for g().
e
s 00001/00011/00118
d D 5.2 90/06/01 14:10:11 bostic 2 1
c new copyright notice
e
s 00129/00000/00000
d D 5.1 89/12/19 12:38:55 bostic 1 0
c date and time created 89/12/19 12:38:55 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 8
 * Copyright (c) 1989, 1993
E 8
I 8
 * Copyright (c) 1989, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Guido van Rossum.
 *
D 2
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

/*
D 6
 * Function fnmatch() as proposed in Posix 1003.2 B.6 (rev. 9).
E 6
I 6
D 8
 * Function fnmatch() as proposed in POSIX 1003.2 B.6 (D11.2).
E 8
I 8
 * Function fnmatch() as specified in POSIX 1003.2-1992, section B.6.
E 8
E 6
 * Compares a filename or pathname to a pattern.
 */

D 5
#include <unistd.h>
E 5
I 5
#include <fnmatch.h>
E 5
#include <string.h>

#define	EOS	'\0'

I 3
D 5
static char *
rangematch(pattern, test)
	register char *pattern, test;
{
	register char c, c2;
	int negate, ok;
E 5
I 5
D 6
static char *rangematch __P((char *, int));
E 6
I 6
D 8
static const char *rangematch __P((const char *, int));
E 8
I 8
static const char *rangematch __P((const char *, int, int));
E 8
E 6
E 5

I 8
int
E 8
D 5
	if (negate = (*pattern == '!'))
		++pattern;

	/*
	 * TO DO: quoting
	 */

	for (ok = 0; (c = *pattern++) != ']';) {
		if (c == EOS)
			return(NULL);		/* illegal pattern */
		if (*pattern == '-' && (c2 = pattern[1]) != EOS && c2 != ']') {
			if (c <= test && test <= c2)
				ok = 1;
			pattern += 2;
		}
		else if (c == test)
			ok = 1;
	}
	return(ok == negate ? NULL : pattern);
}

E 5
E 3
fnmatch(pattern, string, flags)
D 4
	register char *pattern, *string;
E 4
I 4
D 5
	register const char *pattern;
	register const char *string;
E 5
I 5
D 8
	register const char *pattern, *string;
E 8
I 8
	const char *pattern, *string;
E 8
E 5
E 4
	int flags;
{
D 8
	register char c;
D 5
	char test, *rangematch();
E 5
I 5
	char test;
E 8
I 8
	const char *stringstart;
	char c, test;
E 8
E 5

D 8
	for (;;)
E 8
I 8
	for (stringstart = string;;)
E 8
		switch (c = *pattern++) {
		case EOS:
D 5
			return(*string == EOS);
E 5
I 5
			return (*string == EOS ? 0 : FNM_NOMATCH);
E 5
		case '?':
D 8
			if ((test = *string++) == EOS ||
			    test == '/' && flags & FNM_PATHNAME)
E 8
I 8
			if (*string == EOS)
E 8
D 5
				return(0);
E 5
I 5
				return (FNM_NOMATCH);
I 8
			if (*string == '/' && (flags & FNM_PATHNAME))
				return (FNM_NOMATCH);
			if (*string == '.' && (flags & FNM_PERIOD) &&
			    (string == stringstart ||
			    ((flags & FNM_PATHNAME) && *(string - 1) == '/')))
				return (FNM_NOMATCH);
			++string;
E 8
E 5
			break;
		case '*':
			c = *pattern;
D 5
			/* collapse multiple stars */
E 5
I 5
			/* Collapse multiple stars. */
E 5
			while (c == '*')
				c = *++pattern;

I 8
			if (*string == '.' && (flags & FNM_PERIOD) &&
			    (string == stringstart ||
			    ((flags & FNM_PATHNAME) && *(string - 1) == '/')))
				return (FNM_NOMATCH);

E 8
D 5
			/* optimize for pattern with * at end or before / */
E 5
I 5
			/* Optimize for pattern with * at end or before /. */
E 5
			if (c == EOS)
				if (flags & FNM_PATHNAME)
D 5
					return(!index(string, '/'));
E 5
I 5
D 8
					return (index(string, '/') == NULL ?
E 8
I 8
					return (strchr(string, '/') == NULL ?
E 8
					    0 : FNM_NOMATCH);
E 5
				else
D 5
					return(1);
E 5
I 5
					return (0);
E 5
			else if (c == '/' && flags & FNM_PATHNAME) {
D 8
				if ((string = index(string, '/')) == NULL)
E 8
I 8
				if ((string = strchr(string, '/')) == NULL)
E 8
D 5
					return(0);
E 5
I 5
					return (FNM_NOMATCH);
E 5
				break;
			}

D 5
			/* general case, use recursion */
E 5
I 5
			/* General case, use recursion. */
E 5
			while ((test = *string) != EOS) {
D 5
				if (fnmatch(pattern, string, flags))
					return(1);
E 5
I 5
D 8
				if (!fnmatch(pattern, string, flags))
E 8
I 8
				if (!fnmatch(pattern, string, flags & ~FNM_PERIOD))
E 8
					return (0);
E 5
				if (test == '/' && flags & FNM_PATHNAME)
					break;
				++string;
			}
D 5
			return(0);
E 5
I 5
			return (FNM_NOMATCH);
E 5
		case '[':
D 8
			if ((test = *string++) == EOS ||
			    test == '/' && flags & FNM_PATHNAME)
E 8
I 8
			if (*string == EOS)
E 8
D 5
				return(0);
E 5
I 5
				return (FNM_NOMATCH);
E 5
D 8
			if ((pattern = rangematch(pattern, test)) == NULL)
E 8
I 8
			if (*string == '/' && flags & FNM_PATHNAME)
E 8
D 5
				return(0);
E 5
I 5
				return (FNM_NOMATCH);
I 8
			if ((pattern =
			    rangematch(pattern, *string, flags)) == NULL)
				return (FNM_NOMATCH);
			++string;
E 8
E 5
			break;
		case '\\':
D 5
			if (flags & FNM_QUOTE) {
E 5
I 5
			if (!(flags & FNM_NOESCAPE)) {
E 5
				if ((c = *pattern++) == EOS) {
					c = '\\';
					--pattern;
				}
D 8
				if (c != *string++)
D 5
					return(0);
E 5
I 5
					return (FNM_NOMATCH);
E 5
				break;
E 8
			}
			/* FALLTHROUGH */
		default:
			if (c != *string++)
D 5
				return(0);
E 5
I 5
				return (FNM_NOMATCH);
E 5
			break;
		}
I 5
	/* NOTREACHED */
}

D 6
static char *
E 6
I 6
static const char *
E 6
D 8
rangematch(pattern, test)
D 6
	register char *pattern;
E 6
I 6
	register const char *pattern;
E 6
	register int test;
E 8
I 8
rangematch(pattern, test, flags)
	const char *pattern;
	int test, flags;
E 8
{
D 8
	register char c, c2;
E 8
	int negate, ok;
I 8
	char c, c2;
E 8

D 8
	if (negate = (*pattern == '!'))
		++pattern;

E 8
	/*
D 8
	 * XXX
	 * TO DO: quoting
E 8
I 8
	 * A bracket expression starting with an unquoted circumflex
	 * character produces unspecified results (IEEE 1003.2-1992,
	 * 3.13.2).  This implementation treats it like '!', for
	 * consistency with the regular expression syntax.
	 * J.T. Conklin (conklin@ngai.kaleida.com)
E 8
	 */
I 8
	if (negate = (*pattern == '!' || *pattern == '^'))
		++pattern;
	
E 8
	for (ok = 0; (c = *pattern++) != ']';) {
I 8
		if (c == '\\' && !(flags & FNM_NOESCAPE))
			c = *pattern++;
E 8
		if (c == EOS)
D 8
			return (NULL);		/* Illegal pattern. */
		if (*pattern == '-' && (c2 = pattern[1]) != EOS && c2 != ']') {
E 8
I 8
			return (NULL);
		if (*pattern == '-' 
		    && (c2 = *(pattern+1)) != EOS && c2 != ']') {
			pattern += 2;
			if (c2 == '\\' && !(flags & FNM_NOESCAPE))
				c2 = *pattern++;
			if (c2 == EOS)
				return (NULL);
E 8
			if (c <= test && test <= c2)
				ok = 1;
D 8
			pattern += 2;
		}
		else if (c == test)
E 8
I 8
		} else if (c == test)
E 8
			ok = 1;
	}
	return (ok == negate ? NULL : pattern);
E 5
D 3
}

static char *
rangematch(pattern, test)
	register char *pattern, test;
{
	register char c, c2;
	int negate, ok;

	if (negate = (*pattern == '!'))
		++pattern;

	/*
	 * TO DO: quoting
	 */

	for (ok = 0; (c = *pattern++) != ']';) {
		if (c == EOS)
			return(NULL);		/* illegal pattern */
		if (*pattern == '-' && (c2 = pattern[1]) != EOS && c2 != ']') {
			if (c <= test && test <= c2)
				ok = 1;
			pattern += 2;
		}
		else if (c == test)
			ok = 1;
	}
	return(ok == negate ? NULL : pattern);
E 3
}
E 1
