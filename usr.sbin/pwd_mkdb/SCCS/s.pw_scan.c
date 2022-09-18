h33066
s 00001/00001/00095
d D 8.3 94/04/02 10:05:48 pendry 4 3
c add 1994 copyright
e
s 00018/00019/00078
d D 8.2 94/04/01 07:08:12 pendry 3 2
c prettyness police
e
s 00002/00002/00095
d D 8.1 93/06/06 14:04:41 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00097/00000/00000
d D 5.1 91/02/12 21:51:09 bostic 1 0
c rework the password subsystem
c date and time created 91/02/12 21:51:09 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
D 4
 * Copyright (c) 1990, 1993
E 4
I 4
 * Copyright (c) 1990, 1993, 1994
E 4
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * This module is used to "verify" password entries by chpass(1) and
 * pwd_mkdb(8).
 */

#include <sys/param.h>
I 3

#include <err.h>
E 3
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
I 3
#include <unistd.h>
E 3

D 3
extern char *progname;
E 3
I 3
#include "pw_scan.h"
E 3

I 3
int
E 3
pw_scan(bp, pw)
	char *bp;
	struct passwd *pw;
{
D 3
	register long id;
	register int root;
	register char *p, *sh;
	char *getusershell();
E 3
I 3
	long id;
	int root;
	char *p, *sh;
E 3

	if (!(pw->pw_name = strsep(&bp, ":")))		/* login */
		goto fmt;
	root = !strcmp(pw->pw_name, "root");

	if (!(pw->pw_passwd = strsep(&bp, ":")))	/* passwd */
		goto fmt;

	if (!(p = strsep(&bp, ":")))			/* uid */
		goto fmt;
	id = atol(p);
	if (root && id) {
D 3
		(void)fprintf(stderr, "%s: root uid should be 0", progname);
		return(0);
E 3
I 3
		warnx("root uid should be 0");
		return (0);
E 3
	}
	if (id > USHRT_MAX) {
D 3
		(void)fprintf(stderr,
		    "%s: %s > max uid value (%d)", progname, p, USHRT_MAX);
		return(0);
E 3
I 3
		warnx("%s > max uid value (%d)", p, USHRT_MAX);
		return (0);
E 3
	}
	pw->pw_uid = id;

	if (!(p = strsep(&bp, ":")))			/* gid */
		goto fmt;
	id = atol(p);
	if (id > USHRT_MAX) {
D 3
		(void)fprintf(stderr,
		    "%s: %s > max gid value (%d)", progname, p, USHRT_MAX);
		return(0);
E 3
I 3
		warnx("%s > max gid value (%d)", p, USHRT_MAX);
		return (0);
E 3
	}
	pw->pw_gid = id;

	pw->pw_class = strsep(&bp, ":");		/* class */
	if (!(p = strsep(&bp, ":")))			/* change */
		goto fmt;
	pw->pw_change = atol(p);
	if (!(p = strsep(&bp, ":")))			/* expire */
		goto fmt;
	pw->pw_expire = atol(p);
	pw->pw_gecos = strsep(&bp, ":");		/* gecos */
	pw->pw_dir = strsep(&bp, ":");			/* directory */
	if (!(pw->pw_shell = strsep(&bp, ":")))		/* shell */
		goto fmt;

	p = pw->pw_shell;
	if (root && *p)					/* empty == /bin/sh */
		for (setusershell();;) {
			if (!(sh = getusershell())) {
D 3
				(void)fprintf(stderr,
				    "%s: warning, unknown root shell\n",
				    progname);
E 3
I 3
				warnx("warning, unknown root shell");
E 3
				break;
			}
			if (!strcmp(p, sh))
				break;	
		}

	if (p = strsep(&bp, ":")) {			/* too many */
D 3
fmt:		(void)fprintf(stderr, "%s: corrupted entry\n", progname);
		return(0);
E 3
I 3
fmt:		warnx("corrupted entry");
		return (0);
E 3
	}
D 3
	return(1);
E 3
I 3
	return (1);
E 3
}
E 1
