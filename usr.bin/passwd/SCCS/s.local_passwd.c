h22299
s 00001/00001/00126
d D 8.3 94/04/02 09:46:58 pendry 9 8
c add 1994 copyright
e
s 00058/00050/00069
d D 8.2 94/04/02 09:35:26 pendry 8 7
c prettyness police
e
s 00002/00002/00117
d D 8.1 93/06/06 15:49:18 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00118
d D 5.6 93/01/08 17:18:02 bostic 6 5
c allow users without passwords to change their passwords
e
s 00001/00001/00118
d D 5.5 91/05/06 12:34:54 bostic 5 4
c use _PASSWORD_EFMT1 instead of '_'
e
s 00005/00005/00114
d D 5.4 91/04/01 08:42:16 bostic 4 3
c make salt long enough for new password format; minor ANSIisms
e
s 00002/00002/00117
d D 5.3 91/03/03 16:12:30 bostic 3 2
c fix error message when user doesn't know the old passwd
e
s 00001/00001/00118
d D 5.2 91/03/03 16:08:05 bostic 2 1
c redo the pw_copy calling convention
e
s 00119/00000/00000
d D 5.1 91/02/12 22:15:27 bostic 1 0
c rework the password subsystem
c date and time created 91/02/12 22:15:27 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1990, 1993
E 9
I 9
 * Copyright (c) 1990, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 8
#include <pwd.h>
E 8
I 8

#include <ctype.h>
#include <err.h>
E 8
#include <errno.h>
I 8
#include <pwd.h>
E 8
#include <stdio.h>
I 8
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
E 8

D 8
uid_t uid;
E 8
I 8
#include <pw_copy.h>
#include <pw_util.h>
E 8

D 8
char *progname = "passwd";
char *tempname;
E 8
I 8
#include "extern.h"
E 8

D 8
local_passwd(uname)
	char *uname;
{
	struct passwd *pw;
	int pfd, tfd;
	char *getnewpasswd();
E 8
I 8
static uid_t uid;
E 8

D 8
	if (!(pw = getpwnam(uname))) {
		(void)fprintf(stderr, "passwd: unknown user %s.\n", uname);
		exit(1);
	}
E 8
I 8
char   *tempname;
E 8

D 8
	uid = getuid();
	if (uid && uid != pw->pw_uid) {
		(void)fprintf(stderr, "passwd: %s\n", strerror(EACCES));
		exit(1);
	}
E 8
I 8
static unsigned char itoa64[] =		/* 0 ... 63 => ascii - 64 */
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
E 8

D 8
	pw_init();
	pfd = pw_lock();
	tfd = pw_tmp();

	/*
	 * Get the new password.  Reset passwd change time to zero; when
	 * classes are implemented, go and get the "offset" value for this
	 * class and reset the timer.
	 */
	pw->pw_passwd = getnewpasswd(pw);
	pw->pw_change = 0;
D 2
	pw_copy(pfd, pw);
E 2
I 2
	pw_copy(pfd, tfd, pw);
E 2

	if (!pw_mkdb())
		pw_error((char *)NULL, 0, 1);
	exit(0);
E 8
I 8
void
to64(s, v, n)
	char *s;
	long v;
	int n;
{
	while (--n >= 0) {
		*s++ = itoa64[v&0x3f];
		v >>= 6;
	}
E 8
}

char *
getnewpasswd(pw)
D 8
	register struct passwd *pw;
E 8
I 8
	struct passwd *pw;
E 8
{
D 8
	register char *p, *t;
E 8
	int tries;
D 4
	char buf[_PASSWORD_LEN+1], salt[2], *crypt(), *getpass();
E 4
I 4
D 8
	char buf[_PASSWORD_LEN+1], salt[9], *crypt(), *getpass();
E 8
I 8
	char *p, *t;
	char buf[_PASSWORD_LEN+1], salt[9];
E 8
E 4

	(void)printf("Changing local password for %s.\n", pw->pw_name);

D 6
	if (uid && pw->pw_passwd &&
E 6
I 6
	if (uid && pw->pw_passwd[0] &&
E 6
	    strcmp(crypt(getpass("Old password:"), pw->pw_passwd),
	    pw->pw_passwd)) {
		errno = EACCES;
D 3
		pw_error(tempname, 1, 1);
E 3
I 3
		pw_error(NULL, 1, 1);
E 3
	}

	for (buf[0] = '\0', tries = 0;;) {
		p = getpass("New password:");
		if (!*p) {
			(void)printf("Password unchanged.\n");
D 3
			pw_error((char *)NULL, 0, 0);
E 3
I 3
			pw_error(NULL, 0, 0);
E 3
		}
		if (strlen(p) <= 5 && (uid != 0 || ++tries < 2)) {
			(void)printf("Please enter a longer password.\n");
			continue;
		}
		for (t = p; *t && islower(*t); ++t);
		if (!*t && (uid != 0 || ++tries < 2)) {
			(void)printf("Please don't use an all-lower case password.\nUnusual capitalization, control characters or digits are suggested.\n");
			continue;
		}
		(void)strcpy(buf, p);
		if (!strcmp(buf, getpass("Retype new password:")))
			break;
		(void)printf("Mismatch; try again, EOF to quit.\n");
	}
	/* grab a random printable character that isn't a colon */
	(void)srandom((int)time((time_t *)NULL));
#ifdef NEWSALT
D 5
	salt[0] = '_';
E 5
I 5
	salt[0] = _PASSWORD_EFMT1;
E 5
D 4
	to64(&salt[1], (long)(29*25), 4);
	to64(&salt[5], (long)random(), 4);
E 4
I 4
	to64(&salt[1], (long)(29 * 25), 4);
	to64(&salt[5], random(), 4);
E 4
#else
D 4
	to64(&salt[0], (long)random(), 2);
E 4
I 4
	to64(&salt[0], random(), 2);
E 4
#endif
D 8
	return(crypt(buf, salt));
E 8
I 8
	return (crypt(buf, salt));
E 8
}

D 4
static unsigned char itoa64[] =		/* 0..63 => ascii-64 */
E 4
I 4
D 8
static unsigned char itoa64[] =		/* 0 ... 63 => ascii - 64 */
E 4
	"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

to64(s, v, n)
	register char *s;
	register long v;
	register int n;
E 8
I 8
int
local_passwd(uname)
	char *uname;
E 8
{
D 8
	while (--n >= 0) {
		*s++ = itoa64[v&0x3f];
		v >>= 6;
	}
E 8
I 8
	struct passwd *pw;
	int pfd, tfd;

	if (!(pw = getpwnam(uname)))
		errx(1, "unknown user %s", uname);

	uid = getuid();
	if (uid && uid != pw->pw_uid)
		errx(1, "%s", strerror(EACCES));

	pw_init();
	pfd = pw_lock();
	tfd = pw_tmp();

	/*
	 * Get the new password.  Reset passwd change time to zero; when
	 * classes are implemented, go and get the "offset" value for this
	 * class and reset the timer.
	 */
	pw->pw_passwd = getnewpasswd(pw);
	pw->pw_change = 0;
	pw_copy(pfd, tfd, pw);

	if (!pw_mkdb())
		pw_error((char *)NULL, 0, 1);
	return (0);
E 8
}
E 1
