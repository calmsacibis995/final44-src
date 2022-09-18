h05619
s 00005/00005/00150
d D 8.1 93/06/06 13:56:01 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00154
d D 5.14 93/03/18 12:23:42 torek 14 13
c must use lstat in case, e.g., /dev/fd is mounted and /dev/stdin
c is a symlink to /dev/fd/0 (then stat("/dev/stdin") is like fstat(0))
e
s 00004/00001/00151
d D 5.13 93/03/09 03:15:31 torek 13 12
c device keys may contain padding, so make sure it is zero bytes
e
s 00001/00001/00151
d D 5.12 92/11/02 09:17:48 bostic 12 11
c database must be readable
e
s 00046/00022/00106
d D 5.11 92/07/30 16:30:31 bostic 11 10
c cleanups from Criag Leres, and minor upgrades for cleanliness
e
s 00001/00002/00127
d D 5.10 91/09/17 07:58:59 bostic 10 9
c hash_open -> dbopen
e
s 00001/00001/00128
d D 5.9 91/05/17 15:30:05 marc 9 8
c wouldn't compile.  remove unnecessary static declaration.
e
s 00024/00012/00105
d D 5.8 91/05/06 18:05:07 bostic 8 7
c change dev database to use "mode_t type dev_t dev" as the key
c ANSI clenaups
e
s 00002/00000/00115
d D 5.7 91/05/02 15:44:14 marc 7 6
c oops - didn't set dev_t in key
e
s 00021/00007/00094
d D 5.6 91/05/02 11:36:23 marc 6 5
c put block devices in database as we,lll
e
s 00000/00001/00101
d D 5.5 91/04/27 16:18:28 bostic 5 4
c doesn't need user.h
e
s 00018/00017/00084
d D 5.4 91/03/03 13:31:10 bostic 4 3
c convert from ndbm(3) to db(3) interface
e
s 00003/00001/00098
d D 5.3 91/03/02 14:41:12 bostic 3 2
c ANSI
e
s 00002/00001/00097
d D 5.2 91/02/14 12:14:23 bostic 2 1
c use DBM_SUFFIX; db(3) now appends ".db" when old interface is used.
e
s 00098/00000/00000
d D 5.1 91/02/12 22:00:46 bostic 1 0
c date and time created 91/02/12 22:00:46 by bostic
e
u
U
t
T
I 1
/*-
D 15
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 15
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
I 11

E 11
I 3
D 5
#include <sys/user.h>
E 5
E 3
#include <fcntl.h>
D 3
#include <dirent.h>
E 3
D 4
#include <ndbm.h>
E 4
I 3
#undef DIRBLKSIZ
#include <dirent.h>
I 7
D 8
struct nlist;	/* XXX bletch */
E 8
I 8
#include <nlist.h>
E 8
E 7
E 3
#include <kvm.h>
I 4
#include <db.h>
E 4
#include <errno.h>
I 8
#include <unistd.h>
E 8
#include <stdio.h>
#include <paths.h>
I 8
#include <stdlib.h>
E 8
#include <string.h>

I 8
D 9
static void error(), usage();
E 9
I 9
D 11
void error(), usage();
E 11
I 11
void	err __P((const char *, ...));
void	usage __P((void));
E 11
E 9

I 11
int
E 11
E 8
main(argc, argv)
	int argc;
D 11
	char **argv;
E 11
I 11
	char *argv[];
E 11
{
D 11
	extern int optind;
E 11
	register DIR *dirp;
	register struct dirent *dp;
	struct stat sb;
I 6
D 8
	char bkeybuf[sizeof(sb.st_rdev) + 1];
E 8
I 8
	struct {
		mode_t type;
		dev_t dev;
	} bkey;
E 8
E 6
D 4
	DBM *db;
	datum key, data;
E 4
I 4
	DB *db;
	DBT data, key;
E 4
	int ch;
D 4
	char buf[MAXNAMLEN + 1], dbtmp[MAXPATHLEN + 1], dbname[MAXPATHLEN + 1];
E 4
I 4
	u_char buf[MAXNAMLEN + 1];
	char dbtmp[MAXPATHLEN + 1], dbname[MAXPATHLEN + 1];
E 4

	while ((ch = getopt(argc, argv, "")) != EOF)
		switch((char)ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

I 11
	if (argc > 0)
		usage();

E 11
	if (chdir(_PATH_DEV))
D 11
		error(_PATH_DEV);
E 11
I 11
		err("%s: %s", _PATH_DEV, strerror(errno));
E 11

	dirp = opendir(".");

D 2
	(void)sprintf(dbtmp, "%s/dev.db.tmp", _PATH_VARRUN);
E 2
I 2
D 4
	(void)sprintf(dbtmp, "%s/dev.tmp", _PATH_VARRUN);
E 2
	(void)sprintf(dbname, "%s/dev.db", _PATH_VARRUN);
	if ((db = dbm_open(dbtmp, O_CREAT|O_WRONLY|O_EXCL,
	    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) == NULL)
E 4
I 4
D 11
	(void)snprintf(dbtmp, sizeof(dbtmp), "%s/dev.tmp", _PATH_VARRUN);
	(void)snprintf(dbname, sizeof(dbtmp), "%s/dev.db", _PATH_VARRUN);
D 10
	db = hash_open(dbtmp, O_CREAT|O_WRONLY|O_EXCL, DEFFILEMODE,
	    (HASHINFO *)NULL);
E 10
I 10
	db = dbopen(dbtmp, O_CREAT|O_WRONLY|O_EXCL, DEFFILEMODE, DB_HASH, NULL);
E 10
	if (!db)
E 4
		error(dbtmp);
E 11
I 11
	(void)snprintf(dbtmp, sizeof(dbtmp), "%sdev.tmp", _PATH_VARRUN);
	(void)snprintf(dbname, sizeof(dbtmp), "%sdev.db", _PATH_VARRUN);
D 12
	db = dbopen(dbtmp, O_CREAT|O_EXLOCK|O_TRUNC|O_WRONLY,
E 12
I 12
	db = dbopen(dbtmp, O_CREAT|O_EXLOCK|O_RDWR|O_TRUNC,
E 12
	    S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, DB_HASH, NULL);
	if (db == NULL)
		err("%s: %s", dbtmp, strerror(errno));
E 11

D 4
	key.dptr = (char *)&sb.st_rdev;
	key.dsize = sizeof(sb.st_rdev);
	data.dptr = buf;
E 4
I 4
D 6
	key.data = (u_char *)&sb.st_rdev;
	key.size = sizeof(sb.st_rdev);
E 6
I 6
	/*
D 8
	 * Character devices are stored using st_rdev as the key.
	 * Block devices are stores using st_rdev followed by exactly
	 * one NULL byte as the key.
E 8
I 8
	 * Keys are a mode_t followed by a dev_t.  The former is the type of
D 13
	 * the file (mode & S_IFMT), the latter is the st_rdev field.
E 13
I 13
	 * the file (mode & S_IFMT), the latter is the st_rdev field.  Note
	 * that the structure may contain padding, so we have to clear it
	 * out here.
E 13
E 8
	 */
I 13
	bzero(&bkey, sizeof(bkey));
E 13
D 8
	key.data = bkeybuf;
	bkeybuf[sizeof(sb.st_rdev)] = NULL;
E 8
I 8
	key.data = &bkey;
	key.size = sizeof(bkey);
E 8
E 6
	data.data = buf;
E 4
	while (dp = readdir(dirp)) {
D 6
		if (stat(dp->d_name, &sb))
			error(dp->d_name);
		if (!S_ISCHR(sb.st_mode))
E 6
I 6
D 14
		if (stat(dp->d_name, &sb)) {
E 14
I 14
		if (lstat(dp->d_name, &sb)) {
E 14
D 11
			(void)fprintf(stderr, "dev_mkdb: can't stat %s\n",
				dp->d_name);
E 11
I 11
			(void)fprintf(stderr,
			    "dev_mkdb: %s: %s\n", dp->d_name, strerror(errno));
E 11
E 6
			continue;
D 6

		/* Nul terminate the name so ps doesn't have to. */
E 6
I 6
		}
I 8

		/* Create the key. */
E 8
		if (S_ISCHR(sb.st_mode))
D 8
			key.size = sizeof(sb.st_rdev);
E 8
I 8
			bkey.type = S_IFCHR;
E 8
		else if (S_ISBLK(sb.st_mode))
D 8
			key.size = sizeof(sb.st_rdev) + 1;
E 8
I 8
			bkey.type = S_IFBLK;
E 8
		else
			continue;
I 7
D 8
		bcopy(&sb.st_rdev, bkeybuf, sizeof(sb.st_rdev));
E 7
		/* 
		 * Nul terminate the name so caller doesn't have to. 
E 8
I 8
		bkey.dev = sb.st_rdev;

		/*
		 * Create the data; nul terminate the name so caller doesn't
		 * have to.
E 8
		 */
E 6
		bcopy(dp->d_name, buf, dp->d_namlen);
		buf[dp->d_namlen] = '\0';
D 4
		data.dsize = dp->d_namlen + 1;
		if (dbm_store(db, key, data, DBM_INSERT) < 0)
			error("dbm_store");
E 4
I 4
		data.size = dp->d_namlen + 1;
		if ((db->put)(db, &key, &data, 0))
D 11
			error(dbtmp);
E 11
I 11
			err("dbput %s: %s\n", dbtmp, strerror(errno));
E 11
E 4
	}
D 4
	(void)dbm_close(db);
I 2
	(void)strcat(dbtmp, DBM_SUFFIX);
E 4
I 4
	(void)(db->close)(db);
E 4
E 2
D 11
	if (rename(dbtmp, dbname)) {
		(void)fprintf(stderr, "dev_mkdb: %s to %s: %s.\n",
		    dbtmp, dbname, strerror(errno));
		exit(1);
	}
E 11
I 11
	if (rename(dbtmp, dbname))
		err("rename %s to %s: %s", dbtmp, dbname, strerror(errno));
E 11
	exit(0);
}

I 8
void
E 8
D 11
error(n)
	char *n;
E 11
I 11
usage()
E 11
{
D 4
	(void)fprintf(stderr, "kvm_mkdb: %s: %s\n", n, strerror(errno));
E 4
I 4
D 11
	(void)fprintf(stderr, "dev_mkdb: %s: %s\n", n, strerror(errno));
E 11
I 11
	(void)fprintf(stderr, "usage: dev_mkdb\n");
E 11
E 4
	exit(1);
}

I 11
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 11
I 8
void
E 8
D 11
usage()
E 11
I 11
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 11
{
D 11
	(void)fprintf(stderr, "usage: dev_mkdb\n");
E 11
I 11
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "dev_mkdb: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 11
	exit(1);
I 11
	/* NOTREACHED */
E 11
}
E 1
