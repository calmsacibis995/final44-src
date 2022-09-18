h27725
s 00004/00000/00089
d D 8.5 95/04/27 14:59:00 bostic 8 7
c don't add an extra space between the process's args and the
c parenthesized p_comm
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00007/00005/00082
d D 8.4 94/04/15 17:11:57 mckusick 7 6
c avoid breaking up output when commands have newlines in them (for marc)
e
s 00001/00001/00086
d D 8.3 94/04/02 10:01:05 pendry 6 5
c add 1994 copyright
e
s 00007/00007/00080
d D 8.2 94/04/02 09:58:40 pendry 5 4
c prettyness police
e
s 00002/00002/00085
d D 8.1 93/05/31 15:05:35 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00086
d D 5.3 93/04/29 13:19:04 bostic 3 2
c rindex -> strrchr
e
s 00008/00001/00079
d D 5.2 92/06/05 18:56:51 bostic 2 1
c ANSI prototypes (two real bugs)
e
s 00080/00000/00000
d D 5.1 92/04/03 14:56:23 mckusick 1 0
c from Steve McCanne
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
D 6
 * Copyright (c) 1992, 1993
E 6
I 6
 * Copyright (c) 1992, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 2
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
I 8

E 8
E 2
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 7
#include <vis.h>
I 8

E 8
E 7
I 2
#include "ps.h"
E 2

I 2
static char *cmdpart __P((char *));
static char *shquote __P((char **));

E 2
/*
 * XXX
 * This is a stub until marc does the real one.
 */
static char *
shquote(argv)
D 5
	register char **argv;
E 5
I 5
	char **argv;
E 5
{
D 5
	register char **p, *dst, *src;
E 5
I 5
	char **p, *dst, *src;
E 5
D 7
	static char buf[1024];		/* XXX */
E 7
I 7
	static char buf[4096];		/* XXX */
E 7

	if (*argv == 0) {
		buf[0] = 0;
		return (buf);
	}
	dst = buf;
	for (p = argv; (src = *p++) != 0; ) {
		if (*src == 0)
			continue;
D 7
		while ((*dst++ = *src++) != 0)
			continue;
		dst[-1] = ' ';
E 7
I 7
		strvis(dst, src, VIS_NL | VIS_CSTYLE);
		while (*dst)
			dst++;
		*dst++ = ' ';
E 7
	}
I 8
	if (dst != buf)
		--dst;
E 8
D 7
	dst[-1] = 0;
E 7
I 7
	*dst = '\0';
E 7
	return (buf);
}

static char *
cmdpart(arg0)
	char *arg0;
{
D 5
	register char *cp;
E 5
I 5
	char *cp;
E 5

D 3
	return ((cp = rindex(arg0, '/')) != NULL ? cp + 1 : arg0);
E 3
I 3
	return ((cp = strrchr(arg0, '/')) != NULL ? cp + 1 : arg0);
E 3
}

char *
fmt_argv(argv, cmd, maxlen)
D 5
	register char **argv;
	register char *cmd;
E 5
I 5
	char **argv;
	char *cmd;
E 5
	int maxlen;
{
D 5
	register int len;
D 2
	register char *ap, *cp, *arg0;
E 2
I 2
	register char *ap, *cp;
E 5
I 5
	int len;
	char *ap, *cp;
E 5
E 2

	if (argv == 0 || argv[0] == 0) {
		if (cmd == NULL)
			return ("");
		ap = NULL;
		len = maxlen + 3;
	} else {
		ap = shquote(argv);
		len = strlen(ap) + maxlen + 4;
	}
	if ((cp = malloc(len)) == NULL)
		return (NULL);
	if (ap == NULL)
		sprintf(cp, "(%.*s)", maxlen, cmd);
	else if (strncmp(cmdpart(argv[0]), cmd, maxlen) != 0)
		sprintf(cp, "%s (%.*s)", ap, maxlen, cmd);
	else
		(void) strcpy(cp, ap);
	return (cp);
}
E 1
