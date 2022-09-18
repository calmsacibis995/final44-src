h00283
s 00002/00002/00064
d D 8.1 93/06/02 00:03:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00066/00000/00000
d D 5.1 92/03/29 11:48:12 bostic 1 0
c date and time created 92/03/29 11:48:12 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * James da Silva at the University of Maryland at College Park.
 *
 * %sccs.include.redist.c%
 */

/*
 * Compatibility routines that implement the old re_comp/re_exec interface in
 * terms of the regcomp/regexec interface.  It's possible that some programs
 * rely on dark corners of re_comp/re_exec and won't work with this version,
 * but most programs should be fine.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <stddef.h>
#include <regexp.h>
#include <string.h>
#include <stdlib.h>

static regexp *re_regexp;
static int re_goterr;
static char *re_errstr;

char *
re_comp(s)
	char *s;
{
	if (s == NULL)
		return (NULL);
	if (re_regexp)
		free(re_regexp);
	if (re_errstr)
		free(re_errstr);
	re_goterr = 0;
	re_regexp = regcomp(s);
	return (re_goterr ? re_errstr : NULL);
}

int
re_exec(s)
	char *s;
{
	int rc;

	re_goterr = 0;
	rc = regexec(re_regexp, s);
	return (re_goterr ? -1 : rc);
}

void
regerror(s)
	const char *s;
{
	re_goterr = 1;
	if (re_errstr)
		free(re_errstr);
	re_errstr = strdup(s);
}
E 1
