h14164
s 00005/00005/00096
d D 8.2 94/04/01 07:28:42 bostic 11 10
c lint
e
s 00002/00002/00099
d D 8.1 93/06/06 14:39:18 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00036/00090
d D 5.9 93/05/01 11:51:39 bostic 9 8
c use library err/warn(3) functions; lint, prettiness police
e
s 00031/00028/00095
d D 5.8 91/05/24 15:17:13 bostic 8 7
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00003/00003/00120
d D 5.7 91/03/21 14:15:43 bostic 7 6
c rename error argument for C preprocessor
e
s 00001/00001/00122
d D 5.6 91/03/09 18:44:03 bostic 6 5
c ANSI
e
s 00027/00009/00096
d D 5.5 90/11/15 13:03:04 bostic 5 4
c use getchar() for queryuser function; lots of minor lint
e
s 00002/00003/00103
d D 5.4 90/11/15 12:22:39 bostic 4 3
c make status variables consistent
e
s 00001/00001/00105
d D 5.3 90/10/22 09:52:27 bostic 3 2
c add -r option, allowing -exec/-ok to do relative traversal
e
s 00009/00039/00097
d D 5.2 90/05/12 15:29:38 bostic 2 1
c new syntax
e
s 00136/00000/00000
d D 5.1 90/05/03 22:01:02 bostic 1 0
c new version derived from Cimarron Taylor's
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
D 11
 * Copyright (c) 1990, 1993
E 11
I 11
 * Copyright (c) 1990, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
I 4
D 9
#include <sys/errno.h>
E 9
I 9

#include <err.h>
#include <errno.h>
#include <fts.h>
E 9
E 4
#include <stdio.h>
D 6
#include "find.h"
E 6
I 5
#include <stdlib.h>
#include <string.h>
I 9

E 9
I 6
#include "find.h"
E 6
E 5
 
/*
D 2
 * find_getpaths --
 *	remove the path strings from the command line and returns them in
 *	another array.  The find syntax assumes all command arguments up
 *	to the first one beginning with a '-', '(' or '!' are pathnames.
 */
char **
find_getpaths(argvp)
	char ***argvp;
{
	register char **argv;
	char **start;

	/*
	 * find first '-', '(' or '!' to delimit paths; if no paths, it's
	 * an error.  Shift the array back one at the same time, creating
	 * a separate array of pathnames.
	 */
	for (argv = *argvp + 1;; ++argv) {
		argv[-1] = argv[0];
		if (!*argv || **argv == '-' || **argv == '!' || **argv == '(')
			break;
	}

	if (argv == *argvp + 1)
		usage();

	argv[-1] = NULL;

	start = *argvp;			/* save beginning of path array */
	*argvp = argv;			/* move argv value */
	return(start);			/* return path array */
}
    
/*
E 2
D 5
 * find_subst --
E 5
I 5
 * brace_subst --
E 5
 *	Replace occurrences of {} in s1 with s2 and return the result string.
D 2
 *	Find_subst always returns a newly allocated string which should be
 *	freed by the caller.
E 2
 */
D 5
find_subst(orig, store, path, len)
E 5
I 5
void
brace_subst(orig, store, path, len)
E 5
	char *orig, **store, *path;
	int len;
{
	register int plen;
	register char ch, *p;
D 2
	char *realloc();
E 2
I 2
D 5
	char *realloc(), *strerror();
E 5
E 2

	plen = strlen(path);
D 11
	for (p = *store; ch = *orig; ++orig)
E 11
I 11
	for (p = *store; (ch = *orig) != '\0'; ++orig)
E 11
		if (ch == '{' && orig[1] == '}') {
			while ((p - *store) + plen > len)
D 8
				if (!(*store = realloc(*store, len *= 2))) {
					(void)fprintf(stderr,
					    "find: %s.\n", strerror(errno));
					exit(1);
				}
E 8
I 8
				if (!(*store = realloc(*store, len *= 2)))
D 9
					err("%s", strerror(errno));
E 8
			bcopy(path, p, plen);
E 9
I 9
					err(1, NULL);
			memmove(p, path, plen);
E 9
			p += plen;
			++orig;
		} else
			*p++ = ch;
	*p = '\0';
}

/*
D 5
 * find_queryuser --
E 5
I 5
 * queryuser --
E 5
 *	print a message to standard error and then read input from standard
 *	input. If the input is 'y' then 1 is returned.
 */
I 9
int
E 9
D 5
find_queryuser(argv)
E 5
I 5
queryuser(argv)
E 5
	register char **argv;
{
D 5
	char buf[10];
E 5
I 5
	int ch, first, nl;
E 5

	(void)fprintf(stderr, "\"%s", *argv);
	while (*++argv)
		(void)fprintf(stderr, " %s", *argv);
	(void)fprintf(stderr, "\"? ");
	(void)fflush(stderr);
D 5
	return(!fgets(buf, sizeof(buf), stdin) || buf[0] != 'y' ? 0 : 1);
E 5
I 5

	first = ch = getchar();
	for (nl = 0;;) {
		if (ch == '\n') {
			nl = 1;
			break;
		}
		if (ch == EOF)
			break;
		ch = getchar();
	}

	if (!nl) {
		(void)fprintf(stderr, "\n");
		(void)fflush(stderr);
	}
D 9
        return(first == 'y');
E 9
I 9
        return (first == 'y');
E 9
E 5
}
 
/*
D 8
 * bad_arg --
 *	print out a bad argument message.
 */
void
D 7
bad_arg(option, error)
	char *option, *error;
E 7
I 7
bad_arg(option, err)
	char *option, *err;
E 7
{
D 7
	(void)fprintf(stderr, "find: %s: %s.\n", option, error);
E 7
I 7
	(void)fprintf(stderr, "find: %s: %s.\n", option, err);
E 7
	exit(1);
}
 
/*
E 8
 * emalloc --
 *	malloc with error checking.
 */
D 5
char *
E 5
I 5
void *
E 5
emalloc(len)
	u_int len;
{
D 2
	char *p, *malloc();
E 2
I 2
D 5
	char *p, *malloc(), *strerror();
E 5
I 5
	void *p;
E 5
E 2

D 8
	if (!(p = malloc(len))) {
		(void)fprintf(stderr, "find: %s.\n", strerror(errno));
		exit(1);
	}
	return(p);
E 8
I 8
D 11
	if (p = malloc(len))
D 9
		return(p);
	err("%s", strerror(errno));
	/* NOTREACHED */
E 8
}

D 8
usage()
E 8
I 8
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 8
{
D 2
	(void)fprintf(stderr, "usage: find path-list expression\n");
E 2
I 2
D 4
	extern int deprecated;

	if (deprecated)
E 4
I 4
D 8
	if (isdeprecated)
E 4
		(void)fprintf(stderr, "usage: find path-list expression\n");
	else
		(void)fprintf(stderr,
D 3
		    "usage: find [-dsx] -f path ... expression\n");
E 3
I 3
		    "usage: find [-drsx] -f path ... expression\n");
E 8
I 8
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "find: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 8
E 3
E 2
	exit(1);
I 8
	/* NOTREACHED */
E 9
I 9
		return (p);
	err(1, NULL);
E 11
I 11
	if ((p = malloc(len)) == NULL)
		err(1, NULL);
	return (p);
E 11
E 9
E 8
}
E 1
