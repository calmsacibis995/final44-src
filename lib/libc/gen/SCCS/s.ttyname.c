h15827
s 00001/00000/00085
d D 8.2 94/01/27 11:16:56 bostic 21 20
c there may be a gap between the mode and the dev, bzero to be sure
e
s 00002/00002/00083
d D 8.1 93/06/04 12:06:42 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00011/00075
d D 5.14 91/10/28 17:30:56 bostic 19 18
c KNF, ANSI cleanups
e
s 00004/00005/00082
d D 5.13 91/10/17 16:10:15 mckusick 18 17
c do not close the directory twice (4.3BSD-reno/lib/8)
e
s 00002/00000/00085
d D 5.12 91/09/25 09:59:27 bostic 17 14
c close the open database
e
s 00004/00001/00084
d R 5.12 91/09/24 08:42:59 bostic 16 14
c close the db after opening
e
s 00001/00000/00085
d R 5.12 91/09/23 13:15:35 bostic 15 14
c close db file after oen
e
s 00001/00001/00084
d D 5.11 91/09/14 10:32:12 bostic 14 13
c hash_open -> dbopen
e
s 00008/00002/00077
d D 5.10 91/05/06 17:59:08 bostic 13 12
c change dev database to use "mode_t type dev_t dev" as the key
e
s 00013/00012/00066
d D 5.9 91/03/06 18:40:28 bostic 12 11
c update to use the real db(3) interface
e
s 00001/00000/00077
d D 5.8 91/02/23 19:50:11 donn 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00042/00013/00035
d D 5.7 91/02/08 17:37:28 bostic 10 9
c use the _PATH_DEVDB database if available
e
s 00001/00011/00047
d D 5.6 90/06/01 14:17:07 bostic 9 8
c new copyright notice
e
s 00001/00001/00057
d D 5.5 90/02/22 12:59:47 bostic 8 7
c typo.
e
s 00004/00005/00054
d D 5.4 89/09/11 17:17:25 bostic 7 6
c use paths.h
e
s 00042/00034/00017
d D 5.3 88/08/31 14:57:32 bostic 6 5
c add Berkeley specific copyright; from scratch
e
s 00002/00002/00049
d D 5.2 86/03/09 20:00:29 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00047
d D 5.1 85/06/05 12:40:48 mckusick 4 3
c Add copyright
e
s 00001/00001/00047
d D 4.3 82/05/07 20:38:54 mckusick 3 2
c update to new fs
e
s 00011/00013/00037
d D 4.2 82/03/30 13:16:03 mckusick 2 1
c convert to use new directory access routines
e
s 00050/00000/00000
d D 4.1 80/12/21 16:40:26 wnj 1 0
c date and time created 80/12/21 16:40:26 by wnj
e
u
U
t
T
I 1
D 4
/* %W% (Berkeley) %G% */
E 4
I 4
D 5
#ifndef lint
E 5
I 5
D 6
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif LIBC_SCCS and not lint
E 5

E 6
E 4
/*
D 6
 * ttyname(f): return "/dev/ttyXX" which the the name of the
 * tty belonging to file f.
 *  NULL if it is not a tty
E 6
I 6
D 20
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
D 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 6
 */

D 6
#define	NULL	0
D 2
#include <sys/types.h>
#include <sys/dir.h>
E 2
I 2
#include <sys/param.h>
E 6
I 6
#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
E 6
D 3
#include <sys/ndir.h>
E 3
I 3
D 10
#include <sys/dir.h>
E 10
E 3
E 2
#include <sys/stat.h>
I 10
#include <fcntl.h>
#include <dirent.h>
E 10
I 6
#include <sgtty.h>
I 10
D 12
#include <ndbm.h>
E 12
I 12
#include <db.h>
E 12
I 11
D 19
#include <unistd.h>
E 19
I 19
#include <string.h>
E 19
E 11
E 10
I 7
#include <paths.h>
E 7
E 6

I 10
static char buf[sizeof(_PATH_DEV) + MAXNAMLEN] = _PATH_DEV;
I 19
static char *oldttyname __P((int, struct stat *));
E 19

E 10
D 6
static	char	dev[]	= "/dev/";
char	*strcpy();
char	*strcat();
E 6
I 6
D 7
#define	DEVDIR	"/dev/"
E 6

E 7
char *
D 6
ttyname(f)
E 6
I 6
ttyname(fd)
	int fd;
E 6
{
D 6
	struct stat fsb;
	struct stat tsb;
D 2
	struct direct db;
E 2
I 2
	register struct direct *db;
	register DIR *df;
E 2
	static char rbuf[32];
E 6
I 6
D 10
	register struct direct *dirp;
	register DIR *dp;
	struct stat sb1, sb2;
E 10
I 10
	struct stat sb;
E 10
	struct sgttyb ttyb;
D 7
	static char buf[sizeof(DEVDIR) + MAXNAMLEN] = DEVDIR;
E 7
I 7
D 10
	static char buf[sizeof(_PATH_DEV) + MAXNAMLEN] = _PATH_DEV;
E 7
	char *rval, *strcpy();
E 10
I 10
D 12
	DBM *db;
	datum dp, key;
E 12
I 12
	DB *db;
	DBT data, key;
I 13
	struct {
		mode_t type;
		dev_t dev;
	} bkey;
E 13
E 12
D 19
	static char *__oldttyname();
E 19
E 10
E 6
D 2
	register df;
E 2

I 10
	/* Must be a terminal. */
E 10
D 6
	if (isatty(f)==0)
E 6
I 6
	if (ioctl(fd, TIOCGETP, &ttyb) < 0)
E 6
D 19
		return(NULL);
E 19
I 19
		return (NULL);
E 19
D 6
	if (fstat(f, &fsb) < 0)
E 6
I 6
D 10
	if (fstat(fd, &sb1) < 0 || (sb1.st_mode&S_IFMT) != S_IFCHR)
E 10
I 10
	/* Must be a character device. */
	if (fstat(fd, &sb) || !S_ISCHR(sb.st_mode))
E 10
E 6
D 19
		return(NULL);
E 19
I 19
		return (NULL);
E 19
I 10

D 12
	if (!(db = dbm_open(_PATH_DEVDB, O_RDONLY, 0)))
		return(__oldttyname(fd, &sb));
	key.dptr = (char *)&sb.st_rdev;
	key.dsize = sizeof(sb.st_rdev);
	dp = dbm_fetch(db, key);
	if (!dp.dptr)
		return(__oldttyname(fd, &sb));
	bcopy(dp.dptr, buf + sizeof(_PATH_DEV) - 1, dp.dsize);
	return(buf);
E 12
I 12
D 14
	if (db = hash_open(_PATH_DEVDB, O_RDONLY, 0, NULL)) {
E 14
I 14
	if (db = dbopen(_PATH_DEVDB, O_RDONLY, 0, DB_HASH, NULL)) {
I 21
		memset(&bkey, 0, sizeof(bkey));
E 21
E 14
D 13
		key.data = (u_char *)&sb.st_rdev;
		key.size = sizeof(sb.st_rdev);
E 13
I 13
		bkey.type = S_IFCHR;
		bkey.dev = sb.st_rdev;
		key.data = &bkey;
		key.size = sizeof(bkey);
E 13
		if (!(db->get)(db, &key, &data, 0)) {
			bcopy(data.data,
			    buf + sizeof(_PATH_DEV) - 1, data.size);
I 17
			(void)(db->close)(db);
E 17
D 19
			return(buf);
E 19
I 19
			return (buf);
E 19
		}
I 17
		(void)(db->close)(db);
E 17
	}
D 19
	return(__oldttyname(fd, &sb));
E 19
I 19
	return (oldttyname(fd, &sb));
E 19
E 12
}

static char *
D 19
__oldttyname(fd, sb)
E 19
I 19
oldttyname(fd, sb)
E 19
	int fd;
	struct stat *sb;
{
	register struct dirent *dirp;
	register DIR *dp;
	struct stat dsb;
D 18
	char *rval, *strcpy();
E 18
I 18
D 19
	char *strcpy();
E 19
E 18

E 10
D 6
	if ((fsb.st_mode&S_IFMT) != S_IFCHR)
E 6
I 6
D 7
	if ((dp = opendir(DEVDIR)) == NULL)
E 7
I 7
	if ((dp = opendir(_PATH_DEV)) == NULL)
E 7
E 6
D 19
		return(NULL);
E 19
I 19
		return (NULL);
E 19
I 10

E 10
D 2
	if ((df = open(dev, 0)) < 0)
E 2
I 2
D 6
	if ((df = opendir(dev)) == NULL)
E 2
		return(NULL);
D 2
	while (read(df, (char *)&db, sizeof(db)) == sizeof(db)) {
		if (db.d_ino == 0)
E 2
I 2
	while ((db = readdir(df)) != NULL) {
		if (db->d_ino != fsb.st_ino)
E 6
I 6
D 18
	for (rval = NULL; dirp = readdir(dp);) {
E 18
I 18
	while (dirp = readdir(dp)) {
E 18
D 10
		if (dirp->d_ino != sb1.st_ino)
E 10
I 10
		if (dirp->d_fileno != sb->st_ino)
E 10
E 6
E 2
			continue;
D 2
		if (db.d_ino != fsb.st_ino)
			continue;
E 2
D 6
		strcpy(rbuf, dev);
D 2
		strcat(rbuf, db.d_name);
E 2
I 2
		strcat(rbuf, db->d_name);
E 2
		if (stat(rbuf, &tsb) < 0)
E 6
I 6
D 7
		(void)strcpy(buf + sizeof(DEVDIR) - 1, dirp->d_name);
E 7
I 7
D 10
		(void)strcpy(buf + sizeof(_PATH_DEV) - 1, dirp->d_name);
E 7
		if (stat(buf, &sb2) < 0 || sb1.st_dev != sb2.st_dev ||
D 8
		    sb1.st_ino != sb1.st_ino)
E 8
I 8
		    sb1.st_ino != sb2.st_ino)
E 10
I 10
		bcopy(dirp->d_name, buf + sizeof(_PATH_DEV) - 1,
		    dirp->d_namlen + 1);
		if (stat(buf, &dsb) || sb->st_dev != dsb.st_dev ||
		    sb->st_ino != dsb.st_ino)
E 10
E 8
E 6
			continue;
D 2
		if (tsb.st_dev==fsb.st_dev && tsb.st_ino==fsb.st_ino) {
			close(df);
E 2
I 2
D 6
		if (tsb.st_dev == fsb.st_dev && tsb.st_ino == fsb.st_ino) {
			closedir(df);
E 2
			return(rbuf);
		}
E 6
I 6
D 10
		closedir(dp);
E 10
I 10
		(void)closedir(dp);
E 10
D 18
		rval = buf;
		break;
E 18
I 18
D 19
		return(buf);
E 19
I 19
		return (buf);
E 19
E 18
E 6
	}
D 2
	close(df);
E 2
I 2
D 6
	closedir(df);
E 2
	return(NULL);
E 6
I 6
D 10
	closedir(dp);
E 10
I 10
	(void)closedir(dp);
E 10
D 18
	return(rval);
E 18
I 18
D 19
	return(NULL);
E 19
I 19
	return (NULL);
E 19
E 18
E 6
}
E 1
