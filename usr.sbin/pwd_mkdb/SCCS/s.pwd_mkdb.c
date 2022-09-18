h05534
s 00004/00002/00357
d D 8.5 94/04/20 17:12:49 bostic 13 12
c don't use chmod, reset the initial umask
e
s 00003/00001/00356
d D 8.4 94/04/16 08:00:14 bostic 12 11
c If pwd_mkdb is invoked with a umask of, say 077, /etc/passwd will end up
c being unreadable.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00355
d D 8.3 94/04/02 10:05:53 pendry 11 10
c add 1994 copyright
e
s 00015/00013/00342
d D 8.2 94/04/01 07:08:01 pendry 10 9
c lint, prettyness police
e
s 00005/00005/00350
d D 8.1 93/06/06 14:04:49 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00084/00054/00271
d D 5.8 93/05/29 16:12:12 bostic 8 7
c incorporate Steven Schultz's changes to make pwd_mkdb fast on big
c password files; 1: make two passes over the input file, one for each hash
c file; 2: tune hash database, plus 2Mb of cache
e
s 00002/00002/00323
d D 5.7 93/01/25 14:09:09 bostic 7 6
c dbopen(3) databases have to be read/write, not just write
e
s 00002/00002/00323
d D 5.6 91/09/23 14:09:22 bostic 6 5
c hash_open -> dbopen
e
s 00011/00000/00314
d D 5.5 91/05/06 18:11:17 bostic 5 4
c don't describe the format in the man page, so nobody depends on it
e
s 00001/00001/00313
d D 5.4 91/03/08 14:22:55 bostic 4 3
c typo...
e
s 00046/00042/00268
d D 5.3 91/03/08 14:22:30 bostic 3 2
c convert from ndbm(3) to db(3) interface
e
s 00002/00002/00308
d D 5.2 91/03/08 14:21:50 bostic 2 1
c use DBM_SUFFIX; db(3) now appends ".db" when old interface is used.
e
s 00310/00000/00000
d D 5.1 91/03/08 14:20:52 bostic 1 0
c rework the password subsystem
c date and time created 91/03/08 14:20:52 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 11
 * Copyright (c) 1991, 1993
E 11
I 11
 * Copyright (c) 1991, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
D 11
"%Z% Copyright (c) 1991, 1993\n\
E 11
I 11
"%Z% Copyright (c) 1991, 1993, 1994\n\
E 11
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
D 8
#include <signal.h>
#include <fcntl.h>
E 8
I 8

E 8
D 3
#include <ndbm.h>
E 3
I 3
#include <db.h>
I 10
#include <err.h>
E 10
E 3
D 8
#include <pwd.h>
E 8
#include <errno.h>
I 8
#include <fcntl.h>
E 8
#include <limits.h>
I 8
#include <pwd.h>
#include <signal.h>
E 8
#include <stdio.h>
I 8
#include <stdlib.h>
E 8
#include <string.h>
I 8
#include <unistd.h>
E 8

I 10
#include "pw_scan.h"

E 10
#define	INSECURE	1
#define	SECURE		2
#define	PERM_INSECURE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define	PERM_SECURE	(S_IRUSR|S_IWUSR)

I 8
HASHINFO openinfo = {
	4096,		/* bsize */
	32,		/* ffactor */
	256,		/* nelem */
	2048 * 1024,	/* cachesize */
	NULL,		/* hash() */
	0		/* lorder */
};

E 8
D 10
char *progname = "pwd_mkdb";

E 10
static enum state { FILE_INSECURE, FILE_SECURE, FILE_ORIG } clean;
static struct passwd pwd;			/* password structure */
static char *pname;				/* password file name */

I 8
void	cleanup __P((void));
void	error __P((char *));
void	mv __P((char *, char *));
int	scan __P((FILE *, struct passwd *));
void	usage __P((void));

int
E 8
main(argc, argv)
	int argc;
D 8
	char **argv;
E 8
I 8
	char *argv[];
E 8
{
D 10
	extern int optind;
	register int len, makeold;
	register char *p, *t;
E 10
D 8
	FILE *fp, *oldfp;
E 8
D 3
	DBM *dp, *edp;
E 3
I 3
	DB *dp, *edp;
E 3
D 8
	sigset_t set;
E 8
D 3
	datum key, data;
E 3
I 3
	DBT data, key;
I 8
	FILE *fp, *oldfp;
	sigset_t set;
E 8
E 3
D 10
	int ch, cnt, tfd;
E 10
I 10
	int ch, cnt, len, makeold, tfd;
	char *p, *t;
E 10
	char buf[MAX(MAXPATHLEN, LINE_MAX * 2)], tbuf[1024];

	makeold = 0;
	while ((ch = getopt(argc, argv, "pv")) != EOF)
		switch(ch) {
		case 'p':			/* create V7 "file.orig" */
			makeold = 1;
			break;
		case 'v':			/* backward compatible */
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage();

	/*
D 8
	 * This could be done to allow the user to interrupt.  Probably
	 * not worth the effort.
E 8
I 8
	 * This could be changed to allow the user to interrupt.
	 * Probably not worth the effort.
E 8
	 */
	sigemptyset(&set);
	sigaddset(&set, SIGTSTP);
	sigaddset(&set, SIGHUP);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGTERM);
	(void)sigprocmask(SIG_BLOCK, &set, (sigset_t *)NULL);

I 13
	/* We don't care what the user wants. */
	(void)umask(0);

E 13
	pname = *argv;
	/* Open the original password file */
	if (!(fp = fopen(pname, "r")))
		error(pname);

D 3
	/* Open the password database. */
E 3
I 3
	/* Open the temporary insecure password database. */
E 3
D 8
	(void)sprintf(buf, "%s.tmp", _PATH_MP_DB);
D 3
	if (!(dp = dbm_open(buf, O_WRONLY|O_CREAT|O_EXCL, PERM_INSECURE)))
E 3
I 3
D 6
	dp = hash_open(buf, O_WRONLY|O_CREAT|O_EXCL, PERM_INSECURE, NULL);
E 6
I 6
D 7
	dp = dbopen(buf, O_WRONLY|O_CREAT|O_EXCL, PERM_INSECURE, DB_HASH, NULL);
E 7
I 7
	dp = dbopen(buf, O_RDWR|O_CREAT|O_EXCL, PERM_INSECURE, DB_HASH, NULL);
E 7
E 6
	if (!dp)
E 8
I 8
	(void)snprintf(buf, sizeof(buf), "%s.tmp", _PATH_MP_DB);
	dp = dbopen(buf,
	    O_RDWR|O_CREAT|O_EXCL, PERM_INSECURE, DB_HASH, &openinfo);
	if (dp == NULL)
E 8
E 3
		error(buf);
	clean = FILE_INSECURE;

D 3
	/* Open the encrypted password database. */
E 3
I 3
D 8
	/* Open the temporary encrypted password database. */
E 3
	(void)sprintf(buf, "%s.tmp", _PATH_SMP_DB);
D 3
	if (!(edp = dbm_open(buf, O_WRONLY|O_CREAT|O_EXCL, PERM_SECURE)))
E 3
I 3
D 6
	edp = hash_open(buf, O_WRONLY|O_CREAT|O_EXCL, PERM_SECURE, NULL);
E 6
I 6
D 7
	edp = dbopen(buf, O_WRONLY|O_CREAT|O_EXCL, PERM_SECURE, DB_HASH, NULL);
E 7
I 7
	edp = dbopen(buf, O_RDWR|O_CREAT|O_EXCL, PERM_SECURE, DB_HASH, NULL);
E 7
E 6
	if (!edp)
E 3
		error(buf);
	clean = FILE_SECURE;

E 8
	/*
	 * Open file for old password file.  Minor trickiness -- don't want to
	 * chance the file already existing, since someone (stupidly) might
	 * still be using this for permission checking.  So, open it first and
D 12
	 * fdopen the resulting fd.  Don't really care who reads it.
E 12
I 12
	 * fdopen the resulting fd.  The resulting file should be readable by
D 13
	 * everyone, don't trust the user's umask.
E 13
I 13
	 * everyone.
E 13
E 12
	 */
	if (makeold) {
D 8
		(void)sprintf(buf, "%s.orig", pname);
E 8
I 8
		(void)snprintf(buf, sizeof(buf), "%s.orig", pname);
E 8
		if ((tfd = open(buf,
		    O_WRONLY|O_CREAT|O_EXCL, PERM_INSECURE)) < 0)
			error(buf);
I 12
D 13
		(void)fchmod(tfd, PERM_INSECURE);
E 13
E 12
D 8
		if (!(oldfp = fdopen(tfd, "w")))
E 8
I 8
		if ((oldfp = fdopen(tfd, "w")) == NULL)
E 8
			error(buf);
		clean = FILE_ORIG;
	}

I 5
	/*
	 * The databases actually contain three copies of the original data.
	 * Each password file entry is converted into a rough approximation
	 * of a ``struct passwd'', with the strings placed inline.  This
	 * object is then stored as the data for three separate keys.  The
	 * first key * is the pw_name field prepended by the _PW_KEYBYNAME
	 * character.  The second key is the pw_uid field prepended by the
	 * _PW_KEYBYUID character.  The third key is the line number in the
	 * original file prepended by the _PW_KEYBYNUM character.  (The special
	 * characters are prepended to ensure that the keys do not collide.)
	 */
E 5
D 3
	data.dptr = buf;
	key.dptr = tbuf;
E 3
I 3
	data.data = (u_char *)buf;
	key.data = (u_char *)tbuf;
E 3
	for (cnt = 1; scan(fp, &pwd); ++cnt) {
#define	COMPACT(e)	t = e; while (*p++ = *t++);
		/* Create insecure data. */
		p = buf;
		COMPACT(pwd.pw_name);
		COMPACT("*");
D 8
		bcopy((char *)&pwd.pw_uid, p, sizeof(int));
E 8
I 8
		memmove(p, &pwd.pw_uid, sizeof(int));
E 8
		p += sizeof(int);
D 8
		bcopy((char *)&pwd.pw_gid, p, sizeof(int));
E 8
I 8
		memmove(p, &pwd.pw_gid, sizeof(int));
E 8
		p += sizeof(int);
D 8
		bcopy((char *)&pwd.pw_change, p, sizeof(time_t));
E 8
I 8
		memmove(p, &pwd.pw_change, sizeof(time_t));
E 8
		p += sizeof(time_t);
		COMPACT(pwd.pw_class);
		COMPACT(pwd.pw_gecos);
		COMPACT(pwd.pw_dir);
		COMPACT(pwd.pw_shell);
D 8
		bcopy((char *)&pwd.pw_expire, p, sizeof(time_t));
E 8
I 8
		memmove(p, &pwd.pw_expire, sizeof(time_t));
E 8
		p += sizeof(time_t);
D 3
		data.dsize = p - buf;
E 3
I 3
		data.size = p - buf;
E 3

		/* Store insecure by name. */
		tbuf[0] = _PW_KEYBYNAME;
		len = strlen(pwd.pw_name);
D 8
		bcopy(pwd.pw_name, tbuf + 1, len);
E 8
I 8
		memmove(tbuf + 1, pwd.pw_name, len);
E 8
D 3
		key.dsize = len + 1;
		if (dbm_store(dp, key, data, DBM_INSERT) < 0)
			error("dbm file");
E 3
I 3
		key.size = len + 1;
		if ((dp->put)(dp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
E 3

		/* Store insecure by number. */
		tbuf[0] = _PW_KEYBYNUM;
D 8
		bcopy((char *)&cnt, tbuf + 1, sizeof(cnt));
E 8
I 8
		memmove(tbuf + 1, &cnt, sizeof(cnt));
E 8
D 3
		key.dsize = sizeof(cnt) + 1;
		if (dbm_store(dp, key, data, DBM_INSERT) < 0)
			error("dbm file");
E 3
I 3
		key.size = sizeof(cnt) + 1;
		if ((dp->put)(dp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
E 3

		/* Store insecure by uid. */
		tbuf[0] = _PW_KEYBYUID;
D 8
		bcopy((char *)&pwd.pw_uid, tbuf + 1, sizeof(pwd.pw_uid));
E 8
I 8
		memmove(tbuf + 1, &pwd.pw_uid, sizeof(pwd.pw_uid));
E 8
D 3
		key.dsize = sizeof(pwd.pw_uid) + 1;
		if (dbm_store(dp, key, data, DBM_INSERT) < 0)
			error("dbm file");
E 3
I 3
		key.size = sizeof(pwd.pw_uid) + 1;
		if ((dp->put)(dp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
E 3

I 8
		/* Create original format password file entry */
		if (makeold)
			(void)fprintf(oldfp, "%s:*:%d:%d:%s:%s:%s\n",
			    pwd.pw_name, pwd.pw_uid, pwd.pw_gid, pwd.pw_gecos,
			    pwd.pw_dir, pwd.pw_shell);
	}
	(void)(dp->close)(dp);
	if (makeold) {
		(void)fflush(oldfp);
		(void)fclose(oldfp);
	}

	/* Open the temporary encrypted password database. */
	(void)snprintf(buf, sizeof(buf), "%s.tmp", _PATH_SMP_DB);
	edp = dbopen(buf,
	    O_RDWR|O_CREAT|O_EXCL, PERM_SECURE, DB_HASH, &openinfo);
	if (!edp)
		error(buf);
	clean = FILE_SECURE;

	rewind(fp);
	for (cnt = 1; scan(fp, &pwd); ++cnt) {

E 8
		/* Create secure data. */
		p = buf;
		COMPACT(pwd.pw_name);
		COMPACT(pwd.pw_passwd);
D 8
		bcopy((char *)&pwd.pw_uid, p, sizeof(int));
E 8
I 8
		memmove(p, &pwd.pw_uid, sizeof(int));
E 8
		p += sizeof(int);
D 8
		bcopy((char *)&pwd.pw_gid, p, sizeof(int));
E 8
I 8
		memmove(p, &pwd.pw_gid, sizeof(int));
E 8
		p += sizeof(int);
D 8
		bcopy((char *)&pwd.pw_change, p, sizeof(time_t));
E 8
I 8
		memmove(p, &pwd.pw_change, sizeof(time_t));
E 8
		p += sizeof(time_t);
		COMPACT(pwd.pw_class);
		COMPACT(pwd.pw_gecos);
		COMPACT(pwd.pw_dir);
		COMPACT(pwd.pw_shell);
D 8
		bcopy((char *)&pwd.pw_expire, p, sizeof(time_t));
E 8
I 8
		memmove(p, &pwd.pw_expire, sizeof(time_t));
E 8
		p += sizeof(time_t);
D 3
		data.dsize = p - buf;
E 3
I 3
		data.size = p - buf;
E 3

		/* Store secure by name. */
		tbuf[0] = _PW_KEYBYNAME;
		len = strlen(pwd.pw_name);
D 8
		bcopy(pwd.pw_name, tbuf + 1, len);
E 8
I 8
		memmove(tbuf + 1, pwd.pw_name, len);
E 8
D 3
		key.dsize = len + 1;
		if (dbm_store(edp, key, data, DBM_INSERT) < 0)
			error("dbm file");
E 3
I 3
		key.size = len + 1;
		if ((dp->put)(edp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
E 3

		/* Store secure by number. */
		tbuf[0] = _PW_KEYBYNUM;
D 8
		bcopy((char *)&cnt, tbuf + 1, sizeof(cnt));
E 8
I 8
		memmove(tbuf + 1, &cnt, sizeof(cnt));
E 8
D 3
		key.dsize = sizeof(cnt) + 1;
		if (dbm_store(edp, key, data, DBM_INSERT) < 0)
			error("dbm file");
E 3
I 3
		key.size = sizeof(cnt) + 1;
		if ((dp->put)(edp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
E 3

		/* Store secure by uid. */
		tbuf[0] = _PW_KEYBYUID;
D 8
		bcopy((char *)&pwd.pw_uid, tbuf + 1, sizeof(pwd.pw_uid));
E 8
I 8
		memmove(tbuf + 1, &pwd.pw_uid, sizeof(pwd.pw_uid));
E 8
D 3
		key.dsize = sizeof(pwd.pw_uid) + 1;
		if (dbm_store(edp, key, data, DBM_INSERT) < 0)
			error("dbm file");
E 3
I 3
		key.size = sizeof(pwd.pw_uid) + 1;
		if ((dp->put)(edp, &key, &data, R_NOOVERWRITE) == -1)
			error("put");
E 3
D 8

		/* Create original format password file entry */
		if (makeold)
			(void)fprintf(oldfp, "%s:*:%d:%d:%s:%s:%s\n",
			    pwd.pw_name, pwd.pw_uid, pwd.pw_gid, pwd.pw_gecos,
			    pwd.pw_dir, pwd.pw_shell);
E 8
	}
D 3
	(void)dbm_close(edp);
	(void)dbm_close(dp);
	if (makeold)
E 3
I 3
D 8
	(void)(dp->close)(dp);
E 8
I 8

E 8
	(void)(edp->close)(edp);
D 8
	if (makeold) {
		(void)fsync(oldfp);
E 3
		(void)fclose(oldfp);
I 3
	}
E 8
E 3

	/* Set master.passwd permissions, in case caller forgot. */
D 4
	(void)fchmod(fp, S_IRUSR|S_IWUSR);
E 4
I 4
	(void)fchmod(fileno(fp), S_IRUSR|S_IWUSR);
E 4
	(void)fclose(fp);

	/* Install as the real password files. */
D 2
	(void)sprintf(buf, "%s.tmp", _PATH_MP_DB);
E 2
I 2
D 3
	(void)sprintf(buf, "%s.tmp.%s", _PATH_MP_DB, DBM_SUFFIX);
E 3
I 3
D 8
	(void)sprintf(buf, "%s.tmp", _PATH_MP_DB);
E 8
I 8
	(void)snprintf(buf, sizeof(buf), "%s.tmp", _PATH_MP_DB);
E 8
E 3
E 2
	mv(buf, _PATH_MP_DB);
D 2
	(void)sprintf(buf, "%s.tmp", _PATH_SMP_DB);
E 2
I 2
D 3
	(void)sprintf(buf, "%s.tmp.%s", _PATH_SMP_DB, DBM_SUFFIX);
E 3
I 3
D 8
	(void)sprintf(buf, "%s.tmp", _PATH_SMP_DB);
E 8
I 8
	(void)snprintf(buf, sizeof(buf), "%s.tmp", _PATH_SMP_DB);
E 8
E 3
E 2
	mv(buf, _PATH_SMP_DB);
	if (makeold) {
D 8
		(void)sprintf(buf, "%s.orig", pname);
E 8
I 8
		(void)snprintf(buf, sizeof(buf), "%s.orig", pname);
E 8
		mv(buf, _PATH_PASSWD);
	}
	/*
	 * Move the master password LAST -- chpass(1), passwd(1) and vipw(8)
	 * all use flock(2) on it to block other incarnations of themselves.
	 * The rename means that everything is unlocked, as the original file
	 * can no longer be accessed.
	 */
	mv(pname, _PATH_MASTERPASSWD);
	exit(0);
}

I 8
int
E 8
scan(fp, pw)
	FILE *fp;
	struct passwd *pw;
{
	static int lcnt;
	static char line[LINE_MAX];
	char *p;

	if (!fgets(line, sizeof(line), fp))
D 10
		return(0);
E 10
I 10
		return (0);
E 10
	++lcnt;
	/*
	 * ``... if I swallow anything evil, put your fingers down my
	 * throat...''
	 *	-- The Who
	 */
D 8
	if (!(p = index(line, '\n'))) {
E 8
I 8
	if (!(p = strchr(line, '\n'))) {
E 8
D 10
		(void)fprintf(stderr, "pwd_mkdb: line too long\n");
E 10
I 10
		warnx("line too long");
E 10
		goto fmt;

	}
	*p = '\0';
	if (!pw_scan(line, pw)) {
D 10
		(void)fprintf(stderr, "pwd_mkdb: at line #%d.\n", lcnt);
fmt:		errno = EFTYPE;
E 10
I 10
		warnx("at line #%d", lcnt);
fmt:		errno = EFTYPE;	/* XXX */
E 10
		error(pname);
D 8
		exit(1);
E 8
	}
I 10

	return (1);
E 10
}

I 8
void
E 8
mv(from, to)
	char *from, *to;
{
D 10
	int sverrno;
E 10
	char buf[MAXPATHLEN];

	if (rename(from, to)) {
D 10
		sverrno = errno;
E 10
I 10
		int sverrno = errno;
E 10
D 8
		(void)sprintf(buf, "%s to %s", from, to);
E 8
I 8
		(void)snprintf(buf, sizeof(buf), "%s to %s", from, to);
E 8
		errno = sverrno;
		error(buf);
	}
}

I 8
void
E 8
I 3
error(name)
	char *name;
{
D 10
	(void)fprintf(stderr, "pwd_mkdb: %s: %s\n", name, strerror(errno));
E 10
I 10

	warn(name);
E 10
	cleanup();
	exit(1);
}

I 8
void
E 8
E 3
cleanup()
{
	char buf[MAXPATHLEN];

	switch(clean) {
	case FILE_ORIG:
D 8
		(void)sprintf(buf, "%s.orig", pname);
E 8
I 8
		(void)snprintf(buf, sizeof(buf), "%s.orig", pname);
E 8
		(void)unlink(buf);
		/* FALLTHROUGH */
	case FILE_SECURE:
D 8
		(void)sprintf(buf, "%s.tmp", _PATH_SMP_DB);
E 8
I 8
		(void)snprintf(buf, sizeof(buf), "%s.tmp", _PATH_SMP_DB);
E 8
		(void)unlink(buf);
		/* FALLTHROUGH */
	case FILE_INSECURE:
D 8
		(void)sprintf(buf, "%s.tmp", _PATH_MP_DB);
E 8
I 8
		(void)snprintf(buf, sizeof(buf), "%s.tmp", _PATH_MP_DB);
E 8
		(void)unlink(buf);
	}
D 3
}

error(name)
	char *name;
{
	(void)fprintf(stderr, "pwd_mkdb: %s: %s\n", name, strerror(errno));
	cleanup();
	exit(1);
E 3
}

I 8
void
E 8
usage()
{
I 10

E 10
	(void)fprintf(stderr, "usage: pwd_mkdb [-p] file\n");
	exit(1);
}
E 1
