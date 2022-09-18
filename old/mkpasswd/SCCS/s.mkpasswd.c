h20984
s 00001/00000/00222
d D 5.7 92/07/17 23:56:30 bostic 14 13
c lint
e
s 00001/00011/00221
d D 5.6 90/06/01 18:49:03 bostic 13 12
c new copyright notice
e
s 00012/00010/00220
d D 5.5 90/05/10 17:51:41 marc 12 11
c new calling convention for strsep
e
s 00183/00058/00047
d D 5.4 89/02/22 17:03:03 bostic 11 10
c shadow passwords
e
s 00010/00005/00095
d D 5.3 88/06/18 14:34:35 bostic 10 9
c install approved copyright notice
e
s 00022/00018/00078
d D 5.2 87/12/26 12:37:50 bostic 9 8
c Berkeley header; cpp usage fixes for ANSI C; minor cleanups
e
s 00014/00002/00082
d D 5.1 85/05/28 14:58:28 dist 8 7
c Add copyright
e
s 00006/00003/00078
d D 4.6 85/01/10 09:16:28 ralph 7 6
c make code more portable
e
s 00012/00004/00069
d D 4.5 84/10/26 09:11:07 ralph 6 4
c update for new ndbm routines.
e
s 00011/00004/00069
d R 4.5 84/10/26 09:04:37 ralph 5 4
c update for new ndbm routines.
e
s 00003/00045/00070
d D 4.4 84/05/17 16:01:10 ralph 4 3
c use new setpwfile() and sethostfile() to override default files.
e
s 00052/00004/00063
d D 4.3 84/01/25 15:11:42 ralph 3 2
c read from the right password file.
e
s 00002/00002/00065
d D 4.2 83/12/20 12:15:38 ralph 2 1
c added new parameter to dbmstore().
e
s 00067/00000/00000
d D 4.1 83/12/05 16:21:09 ralph 1 0
c date and time created 83/12/05 16:21:09 by ralph
e
u
U
t
T
I 8
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
 * Copyright (c) 1980, 1983 Regents of the University of California.
 * All rights reserved.
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 10
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 10
I 10
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 10
E 9
 */

E 8
I 1
#ifndef lint
D 8
static	char *sccsid = "%W% (Berkeley) %E%";
#endif
E 8
I 8
char copyright[] =
D 9
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1980, 1983 Regents of the University of California.\n\
E 9
 All rights reserved.\n";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 8

I 11
#include <sys/param.h>
E 11
#include <sys/file.h>
D 11
#include <stdio.h>
#include <pwd.h>
E 11
#include <ndbm.h>
I 11
#include <pwd.h>
#include <stdio.h>
E 11

I 11
static FILE *_pw_fp;
static struct passwd _pw_passwd;
static off_t offset;

#define	MAXLINELENGTH	1024
static char line[MAXLINELENGTH];

/*
 * Mkpasswd does two things -- use the ``arg'' file to create ``arg''.{pag,dir}
 * for ndbm, and, if the -p flag is on, create a password file in the original
 * format.  It doesn't use the getpwent(3) routines because it has to figure
 * out offsets for the encrypted passwords to put in the dbm files.  One other
 * problem is that, since the addition of shadow passwords, getpwent(3) has to
 * use the dbm databases rather than simply scanning the actual file.  This
 * required the addition of a flag field to the dbm database to distinguish
 * between a record keyed by name, and one keyed by uid.
 */

E 11
D 9
char	buf[BUFSIZ];
I 3
D 4
char	line[BUFSIZ+1];
char	EMPTY[] = "";
struct	passwd passwd;
E 4
E 3

I 3
struct	passwd *fgetpwent();

E 9
E 3
main(argc, argv)
I 9
	int argc;
E 9
D 11
	char *argv[];
E 11
I 11
	char **argv;
E 11
{
I 11
	extern int errno, optind;
	register char *flag, *p, *t;
	register int makeold;
	FILE *oldfp;
E 11
I 3
D 4
	FILE *pwf;
E 4
E 3
	DBM *dp;
	datum key, content;
D 11
	register char *cp, *tp;
	register struct passwd *pwd;
	int verbose = 0, entries = 0, maxlen = 0;
I 9
	char buf[BUFSIZ];
E 11
I 11
	int ch;
	char buf[8192], nbuf[50], *strerror();
I 14
	static int scanpw();
E 14
E 11
E 9

D 11
	if (argc > 1 && strcmp(argv[1], "-v") == 0) {
		verbose++;
		argv++, argc--;
	}
	if (argc != 2) {
		fprintf(stderr, "usage: mkpasswd [ -v ] file\n");
E 11
I 11
	makeold = 0;
	while ((ch = getopt(argc, argv, "pv")) != EOF)
		switch(ch) {
		case 'p':			/* create ``password.orig'' */
			makeold = 1;
			/* FALLTHROUGH */
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

	if (!(_pw_fp = fopen(*argv, "r"))) {
		(void)fprintf(stderr,
		    "mkpasswd: %s: can't open for reading.\n", *argv);
E 11
		exit(1);
	}
I 3
D 4
	if ((pwf = fopen(argv[1], "r" )) == NULL) {
E 4
I 4
D 11
	if (access(argv[1], R_OK) < 0) {
E 4
		fprintf(stderr, "mkpasswd: ");
		perror(argv[1]);
		exit(1);
	}
E 11
I 11

	rmall(*argv);
E 11
E 3
D 9
	umask(0);
E 9
I 9
	(void)umask(0);
E 9
D 6
	dp = ndbmopen(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0644);
E 6
I 6
D 11
	dp = dbm_open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0644);
E 6
	if (dp == NULL) {
D 3
		fprintf(stderr, "dbminit failed: ");
E 3
I 3
		fprintf(stderr, "mkpasswd: ");
E 3
		perror(argv[1]);
		exit(1);
	}
D 6
	dp->db_maxbno = 0;
E 6
D 3
	setpwent();
	while (pwd = getpwent()) {
E 3
I 3
D 4
	while (pwd = fgetpwent(pwf)) {
E 4
I 4
	setpwfile(argv[1]);
	while (pwd = getpwent()) {
E 4
E 3
		cp = buf;
D 9
#define	COMPACT(e)	tp = pwd->pw_/**/e; while (*cp++ = *tp++);
		COMPACT(name);
		COMPACT(passwd);
E 9
I 9
#define	COMPACT(e)	tp = pwd->e; while (*cp++ = *tp++);
		COMPACT(pw_name);
		COMPACT(pw_passwd);
E 9
D 7
		*(int *)cp = pwd->pw_uid; cp += sizeof (int);
		*(int *)cp = pwd->pw_gid; cp += sizeof (int);
		*(int *)cp = pwd->pw_quota; cp += sizeof (int);
E 7
I 7
		bcopy((char *)&pwd->pw_uid, cp, sizeof (int));
		cp += sizeof (int);
		bcopy((char *)&pwd->pw_gid, cp, sizeof (int));
		cp += sizeof (int);
		bcopy((char *)&pwd->pw_quota, cp, sizeof (int));
		cp += sizeof (int);
E 7
D 9
		COMPACT(comment);
		COMPACT(gecos);
		COMPACT(dir);
		COMPACT(shell);
E 9
I 9
		COMPACT(pw_comment);
		COMPACT(pw_gecos);
		COMPACT(pw_dir);
		COMPACT(pw_shell);
E 9
		content.dptr = buf;
		content.dsize = cp - buf;
		if (verbose)
			printf("store %s, uid %d\n", pwd->pw_name, pwd->pw_uid);
		key.dptr = pwd->pw_name;
		key.dsize = strlen(pwd->pw_name);
D 2
		dbmstore(dp, key, content);
E 2
I 2
D 6
		dbmstore(dp, key, content, DB_INSERT);
E 6
I 6
		if (dbm_store(dp, key, content, DBM_INSERT) < 0) {
			fprintf(stderr, "mkpasswd: ");
			perror("dbm_store failed");
E 11
I 11

	/* open old password format file, dbm files */
	if (makeold) {
		int oldfd;

		(void)sprintf(buf, "%s.orig", *argv);
		if ((oldfd = open(buf, O_WRONLY|O_CREAT|O_EXCL, 0644)) < 0) {
			(void)fprintf(stderr, "mkpasswd: %s: %s\n", buf,
			    strerror(errno));
E 11
			exit(1);
		}
E 6
E 2
D 11
		key.dptr = (char *)&pwd->pw_uid;
		key.dsize = sizeof (int);
D 2
		dbmstore(dp, key, content);
E 2
I 2
D 6
		dbmstore(dp, key, content, DB_INSERT);
E 6
I 6
		if (dbm_store(dp, key, content, DBM_INSERT) < 0) {
			fprintf(stderr, "mkpasswd: ");
			perror("dbm_store failed");
E 11
I 11
		if (!(oldfp = fdopen(oldfd, "w"))) {
			(void)fprintf(stderr, "mkpasswd: %s: fdopen failed.\n",
			    buf);
E 11
			exit(1);
		}
E 6
E 2
D 11
		entries++;
		if (cp - buf > maxlen)
			maxlen = cp - buf;
E 11
I 11
	}
	if (!(dp = dbm_open(*argv, O_WRONLY|O_CREAT|O_EXCL, 0644))) {
		(void)fprintf(stderr, "mkpasswd: %s: %s\n", *argv,
		    strerror(errno));
		exit(1);
	}

	content.dptr = buf;
	while (scanpw()) {
		/* create dbm entry */
		p = buf;
#define	COMPACT(e)	t = e; while (*p++ = *t++);
		COMPACT(_pw_passwd.pw_name);
		(void)sprintf(nbuf, "%ld", offset);
		COMPACT(nbuf);
		bcopy((char *)&_pw_passwd.pw_uid, p, sizeof(int));
		p += sizeof(int);
		bcopy((char *)&_pw_passwd.pw_gid, p, sizeof(int));
		p += sizeof(int);
		bcopy((char *)&_pw_passwd.pw_change, p, sizeof(time_t));
		p += sizeof(time_t);
		COMPACT(_pw_passwd.pw_class);
		COMPACT(_pw_passwd.pw_gecos);
		COMPACT(_pw_passwd.pw_dir);
		COMPACT(_pw_passwd.pw_shell);
		bcopy((char *)&_pw_passwd.pw_expire, p, sizeof(time_t));
		p += sizeof(time_t);
		flag = p;
		*p++ = _PW_KEYBYNAME;
		content.dsize = p - buf;
#ifdef debug
		(void)printf("store %s, uid %d\n", _pw_passwd.pw_name,
		    _pw_passwd.pw_uid);
#endif
		key.dptr = _pw_passwd.pw_name;
		key.dsize = strlen(_pw_passwd.pw_name);
		if (dbm_store(dp, key, content, DBM_INSERT) < 0)
			goto bad;
		key.dptr = (char *)&_pw_passwd.pw_uid;
		key.dsize = sizeof(int);
		*flag = _PW_KEYBYUID;
		if (dbm_store(dp, key, content, DBM_INSERT) < 0)
			goto bad;

		/* create original format password file entry */
		if (!makeold)
			continue;
		fprintf(oldfp, "%s:*:%d:%d:%s:%s:%s\n", _pw_passwd.pw_name,
		    _pw_passwd.pw_uid, _pw_passwd.pw_gid, _pw_passwd.pw_gecos,
		    _pw_passwd.pw_dir, _pw_passwd.pw_shell);
E 11
	}
I 6
	dbm_close(dp);
E 6
D 3
	endpwent();
E 3
D 11
	printf("%d password entries, maximum length %d\n", entries, maxlen);
E 11
	exit(0);
I 11

bad:	(void)fprintf(stderr, "mkpasswd: dbm_store failed.\n");
	rmall(*argv);
	exit(1);
}

rmall(fname)
	char *fname;
{
	register char *p;
	char buf[MAXPATHLEN], *strcpy();

	for (p = strcpy(buf, fname); *p; ++p);
	bcopy(".pag", p, 5);
	(void)unlink(buf);
	bcopy(".dir", p, 5);
	(void)unlink(buf);
	bcopy(".orig", p, 6);
	(void)unlink(buf);
}

usage()
{
	(void)fprintf(stderr, "usage: mkpasswd [-p] passwd_file\n");
	exit(1);
}

/* from libc/gen/getpwent.c */

static
scanpw()
{
	register char *cp;
	long atol(), ftell();
I 12
	char *bp;
E 12
	char *fgets(), *strsep(), *index();

	for (;;) {
		offset = ftell(_pw_fp);
		if (!(fgets(line, sizeof(line), _pw_fp)))
			return(0);
		/* skip lines that are too big */
		if (!index(line, '\n')) {
			int ch;

			while ((ch = getc(_pw_fp)) != '\n' && ch != EOF)
				;
			continue;
		}
D 12
		_pw_passwd.pw_name = strsep(line, ":\n");
		_pw_passwd.pw_passwd = strsep((char *)NULL, ":\n");
E 12
I 12
		bp = line;
		_pw_passwd.pw_name = strsep(&bp, ":\n");
		_pw_passwd.pw_passwd = strsep(&bp, ":\n");
E 12
		offset += _pw_passwd.pw_passwd - line;
D 12
		if (!(cp = strsep((char *)NULL, ":\n")))
E 12
I 12
		if (!(cp = strsep(&bp, ":\n")))
E 12
			continue;
		_pw_passwd.pw_uid = atoi(cp);
D 12
		if (!(cp = strsep((char *)NULL, ":\n")))
E 12
I 12
		if (!(cp = strsep(&bp, ":\n")))
E 12
			continue;
		_pw_passwd.pw_gid = atoi(cp);
D 12
		_pw_passwd.pw_class = strsep((char *)NULL, ":\n");
		if (!(cp = strsep((char *)NULL, ":\n")))
E 12
I 12
		_pw_passwd.pw_class = strsep(&bp, ":\n");
		if (!(cp = strsep(&bp, ":\n")))
E 12
			continue;
		_pw_passwd.pw_change = atol(cp);
D 12
		if (!(cp = strsep((char *)NULL, ":\n")))
E 12
I 12
		if (!(cp = strsep(&bp, ":\n")))
E 12
			continue;
		_pw_passwd.pw_expire = atol(cp);
D 12
		_pw_passwd.pw_gecos = strsep((char *)NULL, ":\n");
		_pw_passwd.pw_dir = strsep((char *)NULL, ":\n");
		_pw_passwd.pw_shell = strsep((char *)NULL, ":\n");
E 12
I 12
		_pw_passwd.pw_gecos = strsep(&bp, ":\n");
		_pw_passwd.pw_dir = strsep(&bp, ":\n");
		_pw_passwd.pw_shell = strsep(&bp, ":\n");
E 12
		return(1);
	}
	/* NOTREACHED */
E 11
I 3
D 4
}

static char *
pwskip(p)
register char *p;
{
	while( *p && *p != ':' )
		++p;
	if( *p ) *p++ = 0;
	return(p);
}

struct passwd *
fgetpwent(pwf)
	FILE *pwf;
{
	register char *p;

	p = fgets(line, BUFSIZ, pwf);
	if (p==NULL)
		return(0);
	passwd.pw_name = p;
	p = pwskip(p);
	passwd.pw_passwd = p;
	p = pwskip(p);
	passwd.pw_uid = atoi(p);
	p = pwskip(p);
	passwd.pw_gid = atoi(p);
	passwd.pw_quota = 0;
	passwd.pw_comment = EMPTY;
	p = pwskip(p);
	passwd.pw_gecos = p;
	p = pwskip(p);
	passwd.pw_dir = p;
	p = pwskip(p);
	passwd.pw_shell = p;
	while(*p && *p != '\n') p++;
	*p = '\0';
	return(&passwd);
E 4
E 3
}
E 1
