h06379
s 00004/00006/00115
d D 5.2 91/10/27 08:56:15 bostic 2 1
c use err() routine
e
s 00121/00000/00000
d D 5.1 91/04/03 11:22:34 bostic 1 0
c date and time created 91/04/03 11:22:34 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 2
#include <stdio.h>
E 2
#include <string.h>
D 2
#include "cp.h"
E 2
I 2
#include "extern.h"
E 2

/*
 * These functions manipulate paths in PATH_T structures.
 * 
 * They eliminate multiple slashes in paths when they notice them,
 * and keep the path non-slash terminated.
 *
 * Both path_set() and path_append() return 0 if the requested name
 * would be too long.
 */

#define	STRIP_TRAILING_SLASH(p) { \
	while ((p)->p_end > (p)->p_path && (p)->p_end[-1] == '/') \
		*--(p)->p_end = 0; \
}

/*
 * Move specified string into path.  Convert "" to "." to handle BSD
 * semantics for a null path.  Strip trailing slashes.
 */
I 2
int
E 2
path_set(p, string)
	register PATH_T *p;
	char *string;
{
	if (strlen(string) > MAXPATHLEN) {
D 2
		(void)fprintf(stderr,
		    "%s: %s: name too long.\n", progname, string);
E 2
I 2
		err("%s: name too long", string);
E 2
		return(0);
	}

	(void)strcpy(p->p_path, string);
	p->p_end = p->p_path + strlen(p->p_path);

	if (p->p_path == p->p_end) {
		*p->p_end++ = '.';
		*p->p_end = 0;
	}

	STRIP_TRAILING_SLASH(p);
	return(1);
}

/*
 * Append specified string to path, inserting '/' if necessary.  Return a
 * pointer to the old end of path for restoration.
 */
char *
path_append(p, name, len)
	register PATH_T *p;
	char *name;
	int len;
{
	char *old;

	old = p->p_end;
	if (len == -1)
		len = strlen(name);

	/* The "+ 1" accounts for the '/' between old path and name. */
	if ((len + p->p_end - p->p_path + 1) > MAXPATHLEN) {
D 2
		(void)fprintf(stderr,
		    "%s: %s/%s: name too long.\n", progname, p->p_path, name);
E 2
I 2
		err("%s/%s: name too long", p->p_path, name);
E 2
		return(0);
	}

	/*
	 * This code should always be executed, since paths shouldn't
	 * end in '/'.
	 */
	if (p->p_end[-1] != '/') {
		*p->p_end++ = '/';
		*p->p_end = 0;
	}

	(void)strncat(p->p_end, name, len);
	p->p_end += len;
	*p->p_end = 0;

	STRIP_TRAILING_SLASH(p);
	return(old);
}

/*
 * Restore path to previous value.  (As returned by path_append.)
 */
void
path_restore(p, old)
	PATH_T *p;
	char *old;
{
	p->p_end = old;
	*p->p_end = 0;
}

/*
 * Return basename of path.
 */
char *
path_basename(p)
	PATH_T *p;
{
	char *basename;

	basename = rindex(p->p_path, '/');
	return(basename ? basename + 1 : p->p_path);
}
E 1
