h59097
s 00001/00001/00080
d D 8.4 94/04/02 10:06:33 pendry 7 6
c add 1994 copyright
e
s 00001/00000/00080
d D 8.3 94/04/02 09:09:02 pendry 6 5
c new pw_copy.h file for passwd
e
s 00012/00011/00068
d D 8.2 94/04/02 07:56:56 pendry 5 4
c prettyness police
e
s 00002/00002/00077
d D 8.1 93/06/06 14:27:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00007/00063
d D 5.3 91/05/02 16:04:26 bostic 3 2
c fail gracefully if the writes fail
e
s 00003/00003/00067
d D 5.2 91/03/03 16:07:48 bostic 2 1
c get the temporary file and fd handling right.
e
s 00070/00000/00000
d D 5.1 91/02/12 22:34:00 bostic 1 0
c rework the password subsystem
c date and time created 91/02/12 22:34:00 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
D 7
 * Copyright (c) 1990, 1993
E 7
I 7
 * Copyright (c) 1990, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * This module is used to copy the master password file, replacing a single
 * record, by chpass(1) and passwd(1).
 */

I 5
#include <err.h>
E 5
#include <pwd.h>
#include <stdio.h>
#include <string.h>

D 3
extern char *tempname;
E 3
I 3
D 5
extern char *progname, *tempname;
E 5
I 5
#include <pw_util.h>
I 6
#include "pw_copy.h"
E 6
E 5
E 3

I 5
extern char *tempname;

void
E 5
D 2
pw_copy(ffd, pw)
	int ffd;
E 2
I 2
pw_copy(ffd, tfd, pw)
	int ffd, tfd;
E 2
	struct passwd *pw;
{
D 5
	register FILE *from, *to;
	register int done;
	register char *p;
	char buf[8192];
E 5
I 5
	FILE *from, *to;
	int done;
	char *p, buf[8192];
E 5

	if (!(from = fdopen(ffd, "r")))
		pw_error(_PATH_MASTERPASSWD, 1, 1);
D 2
	if (!(to = fopen(tempname, "w")))
E 2
I 2
	if (!(to = fdopen(tfd, "w")))
E 2
		pw_error(tempname, 1, 1);

	for (done = 0; fgets(buf, sizeof(buf), from);) {
D 5
		if (!index(buf, '\n')) {
D 3
			(void)fprintf(stderr, "chpass: %s: line too long\n",
			    _PATH_MASTERPASSWD);
			pw_error((char *)NULL, 0, 1);
E 3
I 3
			(void)fprintf(stderr, "%s: %s: line too long\n",
			    progname, _PATH_MASTERPASSWD);
E 5
I 5
		if (!strchr(buf, '\n')) {
			warnx("%s: line too long", _PATH_MASTERPASSWD);
E 5
			pw_error(NULL, 0, 1);
E 3
		}
		if (done) {
			(void)fprintf(to, "%s", buf);
I 3
			if (ferror(to))
				goto err;
E 3
			continue;
		}
D 5
		if (!(p = index(buf, ':'))) {
D 3
			(void)fprintf(stderr, "chpass: %s: corrupted entry\n",
			    _PATH_MASTERPASSWD);
			pw_error((char *)NULL, 0, 1);
E 3
I 3
			(void)fprintf(stderr, "%s: %s: corrupted entry\n",
			    progname, _PATH_MASTERPASSWD);
E 5
I 5
		if (!(p = strchr(buf, ':'))) {
			warnx("%s: corrupted entry", _PATH_MASTERPASSWD);
E 5
			pw_error(NULL, 0, 1);
E 3
		}
		*p = '\0';
		if (strcmp(buf, pw->pw_name)) {
			*p = ':';
			(void)fprintf(to, "%s", buf);
I 3
			if (ferror(to))
				goto err;
E 3
			continue;
		}
		(void)fprintf(to, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
		    pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid,
		    pw->pw_class, pw->pw_change, pw->pw_expire, pw->pw_gecos,
		    pw->pw_dir, pw->pw_shell);
		done = 1;
I 3
		if (ferror(to))
			goto err;
E 3
	}
	if (!done)
		(void)fprintf(to, "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s\n",
		    pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid,
		    pw->pw_class, pw->pw_change, pw->pw_expire, pw->pw_gecos,
		    pw->pw_dir, pw->pw_shell);
I 3

	if (ferror(to))
err:		pw_error(NULL, 1, 1);
E 3
	(void)fclose(to);
}
E 1
