h08088
s 00001/00001/00186
d D 8.3 94/04/02 10:06:21 pendry 7 6
c add 1994 copyright
e
s 00033/00028/00154
d D 8.2 94/04/02 07:56:57 pendry 6 5
c prettyness police
e
s 00002/00002/00180
d D 8.1 93/06/06 14:27:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00006/00174
d D 5.4 91/10/17 08:06:49 bostic 4 3
c a better fix, just realize that empty files are "corrupted" in verify
e
s 00007/00002/00173
d D 5.3 91/10/17 08:02:23 bostic 3 2
c vi O_TRUNC's the file, resulting in a changed mod time but a size of
c 0 if the file system is unwritable
e
s 00004/00014/00171
d D 5.2 91/03/03 16:07:47 bostic 2 1
c get the temporary file and fd handling right.
e
s 00185/00000/00000
d D 5.1 91/02/12 22:36:34 bostic 1 0
c rework the password subsystem
c date and time created 91/02/12 22:36:34 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1990, 1993
E 7
I 7
 * Copyright (c) 1990, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
D 6
#include <pwd.h>
E 6
I 6

#include <ctype.h>
#include <err.h>
E 6
#include <errno.h>
D 6
#include <stdio.h>
E 6
#include <paths.h>
I 6
#include <pwd.h>
#include <stdio.h>
E 6
#include <stdlib.h>
#include <string.h>
I 6
#include <unistd.h>

#include <pw_scan.h>
#include <pw_util.h>

E 6
#include "chpass.h"

extern char *tempname;

D 2
edit(tfd, pw)
	int tfd;
E 2
I 2
void
edit(pw)
E 2
	struct passwd *pw;
{
	struct stat begin, end;

D 2
	/*
	 * Give the file to the real user; setuid permissions are discarded
	 * in pw_edit().
	 */
	(void)fchown(tfd, getuid(), getgid());

	display(tfd, pw);

E 2
	for (;;) {
		if (stat(tempname, &begin))
			pw_error(tempname, 1, 1);
D 2
		if (pw_edit(1)) {
			(void)fprintf(stderr, "chpass: edit failed\n");
			break;
		}
E 2
I 2
		pw_edit(1);
E 2
		if (stat(tempname, &end))
			pw_error(tempname, 1, 1);
D 3
		if (begin.st_mtime == end.st_mtime) {
E 3
I 3
D 4
		/*
		 * Some editors O_TRUNC the file when they write it out.  This
		 * can result in an empty file with a changed modified time if
		 * the file system is out of space.
		 */
		if (end.st_size == 0 || begin.st_mtime == end.st_mtime) {
E 4
I 4
		if (begin.st_mtime == end.st_mtime) {
E 4
E 3
D 6
			(void)fprintf(stderr, "chpass: no changes made\n");
E 6
I 6
			warnx("no changes made");
E 6
D 3
			pw_error((char *)NULL, 0, 0);
E 3
I 3
			pw_error(NULL, 0, 0);
E 3
		}
		if (verify(pw))
			break;
		pw_prompt();
	}
}

/*
 * display --
 *	print out the file for the user to edit; strange side-effect:
 *	set conditional flag if the user gets to edit the shell.
 */
I 6
void
E 6
display(fd, pw)
	int fd;
	struct passwd *pw;
{
D 6
	register char *p;
E 6
	FILE *fp;
D 6
	char *bp, *ok_shell(), *ttoa();
E 6
I 6
	char *bp, *p, *ttoa();
E 6

	if (!(fp = fdopen(fd, "w")))
		pw_error(tempname, 1, 1);

	(void)fprintf(fp,
	    "#Changing user database information for %s.\n", pw->pw_name);
	if (!uid) {
		(void)fprintf(fp, "Login: %s\n", pw->pw_name);
		(void)fprintf(fp, "Password: %s\n", pw->pw_passwd);
		(void)fprintf(fp, "Uid [#]: %d\n", pw->pw_uid);
		(void)fprintf(fp, "Gid [# or name]: %d\n", pw->pw_gid);
		(void)fprintf(fp, "Change [month day year]: %s\n",
		    ttoa(pw->pw_change));
		(void)fprintf(fp, "Expire [month day year]: %s\n",
		    ttoa(pw->pw_expire));
		(void)fprintf(fp, "Class: %s\n", pw->pw_class);
		(void)fprintf(fp, "Home directory: %s\n", pw->pw_dir);
		(void)fprintf(fp, "Shell: %s\n",
		    *pw->pw_shell ? pw->pw_shell : _PATH_BSHELL);
	}
	/* Only admin can change "restricted" shells. */
	else if (ok_shell(pw->pw_shell))
		/*
		 * Make shell a restricted field.  Ugly with a
		 * necklace, but there's not much else to do.
		 */
		(void)fprintf(fp, "Shell: %s\n",
		    *pw->pw_shell ? pw->pw_shell : _PATH_BSHELL);
	else
		list[E_SHELL].restricted = 1;
	bp = pw->pw_gecos;
	p = strsep(&bp, ",");
	(void)fprintf(fp, "Full Name: %s\n", p ? p : "");
	p = strsep(&bp, ",");
	(void)fprintf(fp, "Location: %s\n", p ? p : "");
	p = strsep(&bp, ",");
	(void)fprintf(fp, "Office Phone: %s\n", p ? p : "");
	p = strsep(&bp, ",");
	(void)fprintf(fp, "Home Phone: %s\n", p ? p : "");

I 2
	(void)fchown(fd, getuid(), getgid());
E 2
	(void)fclose(fp);
}

I 6
int
E 6
verify(pw)
	struct passwd *pw;
{
D 6
	register ENTRY *ep;
	register char *p;
E 6
I 6
	ENTRY *ep;
	char *p;
E 6
I 4
	struct stat sb;
E 4
	FILE *fp;
	int len;
	char buf[LINE_MAX];

	if (!(fp = fopen(tempname, "r")))
		pw_error(tempname, 1, 1);
I 4
	if (fstat(fileno(fp), &sb))
		pw_error(tempname, 1, 1);
	if (sb.st_size == 0) {
D 6
		(void)fprintf(stderr, "chpass: corrupted temporary file.\n");
E 6
I 6
		warnx("corrupted temporary file");
E 6
		goto bad;
	}
E 4
	while (fgets(buf, sizeof(buf), fp)) {
		if (!buf[0] || buf[0] == '#')
			continue;
D 6
		if (!(p = index(buf, '\n'))) {
			(void)fprintf(stderr, "chpass: line too long.\n");
E 6
I 6
		if (!(p = strchr(buf, '\n'))) {
			warnx("line too long");
E 6
			goto bad;
		}
		*p = '\0';
		for (ep = list;; ++ep) {
			if (!ep->prompt) {
D 6
				(void)fprintf(stderr,
				    "chpass: unrecognized field.\n");
E 6
I 6
				warnx("unrecognized field");
E 6
				goto bad;
			}
			if (!strncasecmp(buf, ep->prompt, ep->len)) {
				if (ep->restricted && uid) {
D 6
					(void)fprintf(stderr,
			    "chpass: you may not change the %s field.\n",
					    ep->prompt);
E 6
I 6
					warnx(
					    "you may not change the %s field",
						ep->prompt);
E 6
					goto bad;
				}
D 6
				if (!(p = index(buf, ':'))) {
					(void)fprintf(stderr,
					    "chpass: line corrupted.\n");
E 6
I 6
				if (!(p = strchr(buf, ':'))) {
					warnx("line corrupted");
E 6
					goto bad;
				}
				while (isspace(*++p));
				if (ep->except && strpbrk(p, ep->except)) {
D 6
					(void)fprintf(stderr,
			    "chpass: illegal character in the \"%s\" field.\n",
E 6
I 6
					warnx(
				   "illegal character in the \"%s\" field",
E 6
					    ep->prompt);
					goto bad;
				}
				if ((ep->func)(p, pw, ep)) {
bad:					(void)fclose(fp);
D 6
					return(0);
E 6
I 6
					return (0);
E 6
				}
				break;
			}
		}
	}
	(void)fclose(fp);

	/* Build the gecos field. */
	len = strlen(list[E_NAME].save) + strlen(list[E_BPHONE].save) +
	    strlen(list[E_HPHONE].save) + strlen(list[E_LOCATE].save) + 4;
D 6
	if (!(p = malloc(len))) {
		(void)fprintf(stderr, "chpass: %s\n", strerror(errno));
		exit(1);
	}
E 6
I 6
	if (!(p = malloc(len)))
		err(1, NULL);
E 6
	(void)sprintf(pw->pw_gecos = p, "%s,%s,%s,%s", list[E_NAME].save,
	    list[E_LOCATE].save, list[E_BPHONE].save, list[E_HPHONE].save);

	if (snprintf(buf, sizeof(buf),
	    "%s:%s:%d:%d:%s:%ld:%ld:%s:%s:%s",
	    pw->pw_name, pw->pw_passwd, pw->pw_uid, pw->pw_gid, pw->pw_class,
	    pw->pw_change, pw->pw_expire, pw->pw_gecos, pw->pw_dir,
	    pw->pw_shell) >= sizeof(buf)) {
D 6
		(void)fprintf(stderr, "chpass: entries too long\n");
		return(0);
E 6
I 6
		warnx("entries too long");
		return (0);
E 6
	}
D 6
	return(pw_scan(buf, pw));
E 6
I 6
	return (pw_scan(buf, pw));
E 6
}
E 1
