h49440
s 00002/00002/00127
d D 8.1 93/06/09 22:54:07 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00121
d D 5.5 92/05/11 17:29:52 bostic 5 4
c fix (ruthlessly tested, too!) boundary conditions where terminal values
c from the user are NULL or stupid
e
s 00011/00001/00112
d D 5.4 92/05/07 17:22:58 bostic 4 3
c Don't loop endlessly on EOF
e
s 00001/00001/00112
d D 5.3 92/03/31 16:39:20 bostic 3 2
c don't run if getting nothing from the terminal
e
s 00010/00009/00103
d D 5.2 91/12/25 18:10:13 bostic 2 1
c don't blow away TERMCAP environmental variable if a path
e
s 00112/00000/00000
d D 5.1 91/12/22 18:55:05 bostic 1 0
c date and time created 91/12/22 18:55:05 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <errno.h>
#include <ttyent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extern.h"

char    tbuf[1024];      		/* Termcap entry. */

char	*askuser __P((char *));
char	*ttys __P((char *));

/*
 * Figure out what kind of terminal we're dealing with, and then read in
 * its termcap entry.
 */
char *
get_termcap_entry(userarg, tcapbufp)
	char *userarg, **tcapbufp;
{
	struct ttyent *t;
	int rval;
D 2
	char *base, *ttype, *ttypath;
E 2
I 2
	char *p, *ttype, *ttypath;
E 2

	if (userarg) {
		ttype = userarg;
		goto found;
	}

	/* Try the environment. */
	if (ttype = getenv("TERM"))
		goto map;

	/* Try ttyname(3); check for dialup or other mapping. */
	if (ttypath = ttyname(STDERR_FILENO)) {
D 2
		if (base = rindex(ttypath, '/'))
			++base;
E 2
I 2
		if (p = rindex(ttypath, '/'))
			++p;
E 2
		else
D 2
			base = ttypath;
		if ((t = getttynam(base))) {
E 2
I 2
			p = ttypath;
		if ((t = getttynam(p))) {
E 2
			ttype = t->ty_type;
			goto map;
		}
	}

	/* If still undefined, use "unknown". */
	ttype = "unknown";

map:	ttype = mapped(ttype);

	/*
D 2
	 * Remove TERMCAP from the environment so we get a real entry from
	 * /etc/termcap.  This prevents us from being fooled by out of date
	 * stuff in the environment.
E 2
I 2
	 * If not a path, remove TERMCAP from the environment so we get a
	 * real entry from /etc/termcap.  This prevents us from being fooled
	 * by out of date stuff in the environment.
E 2
	 */
D 2
found:	unsetenv("TERMCAP");
E 2
I 2
found:	if ((p = getenv("TERMCAP")) != NULL && *p != '/')
		unsetenv("TERMCAP");
E 2

	/*
	 * ttype now contains a pointer to the type of the terminal.
	 * If the first character is '?', ask the user.
	 */
	if (ttype[0] == '?')
D 5
		ttype = askuser(ttype + 1);
E 5
I 5
		if (ttype[1] != '\0')
			ttype = askuser(ttype + 1);
		else
			ttype = askuser(NULL);
E 5

	/* Find the termcap entry.  If it doesn't exist, ask the user. */
	while ((rval = tgetent(tbuf, ttype)) == 0) {
		(void)fprintf(stderr,
		    "tset: terminal type %s is unknown\n", ttype);
		ttype = askuser(NULL);
	}
	if (rval == -1)
		err("termcap: %s", strerror(errno ? errno : ENOENT));
	*tcapbufp = tbuf;
	return (ttype);
}

/* Prompt the user for a terminal type. */
char *
askuser(dflt)
	char *dflt;
{
	static char answer[256];
	char *p;

I 4
	/* We can get recalled; if so, don't continue uselessly. */
	if (feof(stdin) || ferror(stdin)) {
		(void)fprintf(stderr, "\n");
		exit(1);
	}
E 4
	for (;;) {
		if (dflt)
			(void)fprintf(stderr, "Terminal type? [%s] ", dflt);
		else
			(void)fprintf(stderr, "Terminal type? ");
		(void)fflush(stderr);

D 4
		if (fgets(answer, sizeof(answer), stdin) == NULL)
E 4
I 4
		if (fgets(answer, sizeof(answer), stdin) == NULL) {
			if (dflt == NULL) {
				(void)fprintf(stderr, "\n");
				exit(1);
			}
E 4
D 3
			continue;
E 3
I 3
			return (dflt);
I 4
		}
E 4
E 3

		if (p = index(answer, '\n'))
			*p = '\0';
D 5
		return (answer[0] ? answer : dflt);
E 5
I 5
		if (answer[0])
			return (answer);
		if (dflt != NULL)
			return (dflt);
E 5
	}
}
E 1
