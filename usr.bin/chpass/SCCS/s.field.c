h38740
s 00001/00001/00241
d D 8.4 94/04/02 10:06:26 pendry 17 16
c add 1994 copyright
e
s 00075/00066/00167
d D 8.3 94/04/02 07:56:53 pendry 16 15
c prettyness police
e
s 00013/00010/00220
d D 8.2 94/01/03 10:10:42 pendry 15 14
c fix range checks for uid and gid
e
s 00002/00002/00228
d D 8.1 93/06/06 14:27:13 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00220
d D 5.13 91/02/12 22:38:01 bostic 13 12
c rework the password subsystem
e
s 00001/00011/00229
d D 5.12 90/06/01 16:45:06 bostic 12 11
c new copyright notice
e
s 00001/00001/00239
d D 5.11 90/05/15 19:58:46 bostic 11 10
c string.h is ANSI C include file
e
s 00011/00015/00229
d D 5.10 89/06/01 18:20:32 bostic 10 9
c add -s flag to allow command line change of shell
e
s 00001/00001/00243
d D 5.9 89/05/11 09:42:08 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00018/00017/00226
d D 5.8 89/03/16 21:58:17 bostic 8 7
c allow re-editing of file if reject entries
e
s 00028/00018/00215
d D 5.7 89/03/15 21:03:53 bostic 7 6
c warn on use of upper-case or dot in user name
e
s 00016/00000/00217
d D 5.6 89/03/11 17:07:32 bostic 6 5
c allow root to edit encrypted passwords
e
s 00012/00011/00205
d D 5.5 89/03/09 15:28:26 bostic 5 4
c make empty fields work, get rid of pw_class keywords
e
s 00001/00005/00215
d D 5.4 89/03/08 08:23:34 bostic 4 3
c allow empty gecos fields
e
s 00003/00002/00217
d D 5.3 89/03/05 21:20:22 bostic 3 2
c add pathnames.h
e
s 00005/00000/00214
d D 5.2 89/02/23 12:01:44 bostic 2 1
c login names may not begin with a hyphen
e
s 00214/00000/00000
d D 5.1 89/02/22 17:23:48 bostic 1 0
c date and time created 89/02/22 17:23:48 by bostic
e
u
U
t
T
I 1
/*
D 14
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
D 17
 * Copyright (c) 1988, 1993
E 17
I 17
 * Copyright (c) 1988, 1993, 1994
E 17
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 12
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
E 12
I 12
 * %sccs.include.redist.c%
E 12
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 3
#include </usr/src/include/pwd.h>
E 3
I 3
D 16
#include <pwd.h>
E 16
I 16

#include <ctype.h>
#include <err.h>
#include <errno.h>
E 16
E 3
#include <grp.h>
D 11
#include <strings.h>
E 11
I 11
D 16
#include <string.h>
E 16
I 16
#include <pwd.h>
E 16
E 11
#include <stdio.h>
I 15
D 16
#include <errno.h>
E 15
#include <ctype.h>
E 16
I 16
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

E 16
D 9
#include <chpass.h>
E 9
I 9
#include "chpass.h"
E 9
I 3
#include "pathnames.h"
E 3

/* ARGSUSED */
I 16
int
E 16
p_login(p, pw, ep)
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
	if (!*p) {
D 5
		fprintf(stderr, "chpass: empty field");
E 5
I 5
D 7
		fprintf(stderr, "chpass: empty login field");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: empty login field");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: empty login field.\n");
E 8
E 7
E 5
		return(1);
E 16
I 16
		warnx("empty login field");
		return (1);
E 16
	}
I 2
	if (*p == '-') {
D 7
		fprintf(stderr,
E 7
I 7
D 16
		(void)fprintf(stderr,
E 7
		    "chpass: login names may not begin with a hyphen.\n");
		return(1);
E 16
I 16
		warnx("login names may not begin with a hyphen");
		return (1);
E 16
	}
E 2
	if (!(pw->pw_name = strdup(p))) {
D 7
		fprintf(stderr, "chpass: can't save entry");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't save entry");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: can't save entry.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("can't save entry");
		return (1);
E 16
	}
I 7
D 16
	if (index(p, '.'))
		(void)fprintf(stderr,
		    "chpass: \'.\' is dangerous in a login name.\n");
E 16
I 16
	if (strchr(p, '.'))
		warnx("\'.\' is dangerous in a login name");
E 16
	for (; *p; ++p)
		if (isupper(*p)) {
D 16
			(void)fprintf(stderr,
			    "chpass: upper-case letters are dangerous in a login name.\n");
E 16
I 16
			warnx("upper-case letters are dangerous in a login name");
E 16
			break;
		}
E 7
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
I 6
p_passwd(p, pw, ep)
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
	if (!*p)
		pw->pw_passwd = "";	/* "NOLOGIN"; */
	else if (!(pw->pw_passwd = strdup(p))) {
D 7
		fprintf(stderr, "chpass: can't save password entry");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't save password entry");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: can't save password entry.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("can't save password entry");
		return (1);
E 16
	}
	
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
E 6
p_uid(p, pw, ep)
D 16
	register char *p;
E 16
I 16
	char *p;
E 16
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
D 15
	int id;
E 15
I 15
	uid_t id;
	char *np;
E 15

	if (!*p) {
D 5
		fprintf(stderr, "chpass: empty field");
E 5
I 5
D 7
		fprintf(stderr, "chpass: empty uid field");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: empty uid field");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: empty uid field.\n");
E 8
E 7
E 5
		return(1);
E 16
I 16
		warnx("empty uid field");
		return (1);
E 16
	}
	if (!isdigit(*p)) {
D 7
		fprintf(stderr, "chpass: illegal uid");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: illegal uid");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: illegal uid.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("illegal uid");
		return (1);
E 16
	}
D 15
	id = atoi(p);
	if ((u_int)id > USHRT_MAX) {
D 7
		fprintf(stderr, "chpass: %d > max uid value (%d)",
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: %d > max uid value (%d)",
E 8
I 8
		(void)fprintf(stderr, "chpass: %d > max uid value (%d).\n",
E 8
E 7
		    id, USHRT_MAX);
E 15
I 15
	errno = 0;
	id = strtoul(p, &np, 10);
	if (*np || (id == ULONG_MAX && errno == ERANGE)) {
D 16
		(void)fprintf(stderr, "chpass: illegal uid.\n");
E 15
		return(1);
E 16
I 16
		warnx("illegal uid");
		return (1);
E 16
	}
	pw->pw_uid = id;
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
p_gid(p, pw, ep)
D 16
	register char *p;
E 16
I 16
	char *p;
E 16
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
	struct group *gr;
D 15
	int id;
E 15
I 15
	gid_t id;
	char *np;
E 15

	if (!*p) {
D 5
		fprintf(stderr, "chpass: empty field");
E 5
I 5
D 7
		fprintf(stderr, "chpass: empty gid field");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: empty gid field");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: empty gid field.\n");
E 8
E 7
E 5
		return(1);
E 16
I 16
		warnx("empty gid field");
		return (1);
E 16
	}
	if (!isdigit(*p)) {
		if (!(gr = getgrnam(p))) {
D 7
			fprintf(stderr, "chpass: unknown group %s", p);
E 7
I 7
D 8
			(void)fprintf(stderr, "chpass: unknown group %s", p);
E 8
I 8
D 16
			(void)fprintf(stderr,
			    "chpass: unknown group %s.\n", p);
E 8
E 7
			return(1);
E 16
I 16
			warnx("unknown group %s", p);
			return (1);
E 16
		}
		pw->pw_gid = gr->gr_gid;
D 16
		return(0);
E 16
I 16
		return (0);
E 16
	}
D 15
	id = atoi(p);
	if ((u_int)id > USHRT_MAX) {
D 7
		fprintf(stderr, "chpass: %d > max gid value (%d)",
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: %d > max gid value (%d)",
E 8
I 8
		(void)fprintf(stderr, "chpass: %d > max gid value (%d).\n",
E 8
E 7
		    id, USHRT_MAX);
E 15
I 15
	errno = 0;
	id = strtoul(p, &np, 10);
	if (*np || (id == ULONG_MAX && errno == ERANGE)) {
D 16
		(void)fprintf(stderr, "chpass: illegal gid.\n");
E 15
		return(1);
E 16
I 16
		warnx("illegal gid");
		return (1);
E 16
	}
	pw->pw_gid = id;
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
p_class(p, pw, ep)
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
D 5
	if (!*p) {
		fprintf(stderr, "chpass: empty field");
		return(0);
	}
	if (!(pw->pw_class = strdup(p))) {
E 5
I 5
	if (!*p)
		pw->pw_class = "";
	else if (!(pw->pw_class = strdup(p))) {
E 5
D 7
		fprintf(stderr, "chpass: can't save entry");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't save entry");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: can't save entry.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("can't save entry");
		return (1);
E 16
	}
I 5
	
E 5
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
p_change(p, pw, ep)
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
	if (!atot(p, &pw->pw_change))
D 16
		return(0);
D 7
	fprintf(stderr, "chpass: illegal date for change field");
E 7
I 7
D 8
	(void)fprintf(stderr, "chpass: illegal date for change field");
E 8
I 8
	(void)fprintf(stderr, "chpass: illegal date for change field.\n");
E 8
E 7
	return(1);
E 16
I 16
		return (0);
	warnx("illegal date for change field");
	return (1);
E 16
}

/* ARGSUSED */
I 16
int
E 16
p_expire(p, pw, ep)
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
	if (!atot(p, &pw->pw_expire))
D 16
		return(0);
D 7
	fprintf(stderr, "chpass: illegal date for expire field");
E 7
I 7
D 8
	(void)fprintf(stderr, "chpass: illegal date for expire field");
E 8
I 8
	(void)fprintf(stderr, "chpass: illegal date for expire field.\n");
E 8
E 7
	return(1);
E 16
I 16
		return (0);
	warnx("illegal date for expire field");
	return (1);
E 16
}

/* ARGSUSED */
I 16
int
E 16
D 5
p_save(p, pw, ep)
E 5
I 5
p_gecos(p, pw, ep)
E 5
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
D 4
	if (!*p) {
		fprintf(stderr, "chpass: empty field.");
		return(1);
	}
	if (!(ep->save = strdup(p))) {
E 4
I 4
D 5
	if (*p && !(ep->save = strdup(p))) {
E 5
I 5
	if (!*p)
		ep->save = "";
	else if (!(ep->save = strdup(p))) {
E 5
E 4
D 7
		fprintf(stderr, "chpass: can't save entry");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't save entry");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: can't save entry.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("can't save entry");
		return (1);
E 16
	}
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
p_hdir(p, pw, ep)
	char *p;
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
	if (!*p) {
D 5
		fprintf(stderr, "chpass: empty field");
E 5
I 5
D 7
		fprintf(stderr, "chpass: empty home directory field");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: empty home directory field");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: empty home directory field.\n");
E 8
E 7
E 5
		return(1);
E 16
I 16
		warnx("empty home directory field");
		return (1);
E 16
	}
	if (!(pw->pw_dir = strdup(p))) {
D 7
		fprintf(stderr, "chpass: can't save entry");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't save entry");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: can't save entry.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("can't save entry");
		return (1);
E 16
	}
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}

/* ARGSUSED */
I 16
int
E 16
p_shell(p, pw, ep)
D 16
	register char *p;
E 16
I 16
	char *p;
E 16
	struct passwd *pw;
D 13
	struct entry *ep;
E 13
I 13
	ENTRY *ep;
E 13
{
D 10
	register char *sh, *t;
	char *getusershell();
E 10
I 10
	char *t, *ok_shell();
E 10

	if (!*p) {
D 3
		pw->pw_shell = "/bin/sh";
E 3
I 3
		pw->pw_shell = _PATH_BSHELL;
E 3
D 16
		return(0);
E 16
I 16
		return (0);
E 16
	}
D 10
	setusershell();
	for (;;) {
		if (!(sh = getusershell())) {
			/* only admin can set "restricted" shells */
			if (!uid)
				break;
E 10
I 10
	/* only admin can change from or to "restricted" shells */
	if (uid && pw->pw_shell && !ok_shell(pw->pw_shell)) {
D 16
		(void)fprintf(stderr,
		    "chpass: %s: current shell non-standard.\n", pw->pw_shell);
		return(1);
E 16
I 16
		warnx("%s: current shell non-standard", pw->pw_shell);
		return (1);
E 16
	}
	if (!(t = ok_shell(p))) {
		if (uid) {
E 10
D 7
			fprintf(stderr, "chpass: %s: non-standard shell", p);
E 7
I 7
D 16
			(void)fprintf(stderr,
D 8
			    "chpass: %s: non-standard shell", p);
E 8
I 8
			    "chpass: %s: non-standard shell.\n", p);
E 8
E 7
			return(1);
E 16
I 16
			warnx("%s: non-standard shell", p);
			return (1);
E 16
		}
D 10
		if (!strcmp(p, sh))
			break;
		/* allow just shell name */
		if ((t = rindex(sh, '/')) && !strcmp(p, t)) {
			p = t;
			break;
		}
E 10
	}
I 10
	else
		p = t;
E 10
	if (!(pw->pw_shell = strdup(p))) {
D 7
		fprintf(stderr, "chpass: can't save entry");
E 7
I 7
D 8
		(void)fprintf(stderr, "chpass: can't save entry");
E 8
I 8
D 16
		(void)fprintf(stderr, "chpass: can't save entry.\n");
E 8
E 7
		return(1);
E 16
I 16
		warnx("can't save entry");
		return (1);
E 16
	}
D 16
	return(0);
E 16
I 16
	return (0);
E 16
}
E 1
