h25412
s 00001/00001/00357
d D 8.5 95/02/07 08:49:58 bostic 28 27
c wrong termination statement, could cause the environment to be trashed
e
s 00147/00012/00211
d D 8.4 95/02/03 09:30:16 pendry 27 26
c break getcwd into two layers.
e
s 00001/00001/00222
d D 8.3 95/02/02 06:51:37 bostic 26 25
c ignore ${PWD} unless it begins with a leading slash
e
s 00023/00004/00200
d D 8.2 95/01/31 13:56:34 bostic 25 24
c check $PWD first, if it's right, it's fast
e
s 00002/00002/00202
d D 8.1 93/06/04 12:02:18 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00008/00194
d D 5.12 92/07/06 16:51:52 bostic 23 22
c realloc may have changed the pointer value; from Sean Fagan
e
s 00001/00001/00201
d D 5.11 91/02/24 19:38:47 bostic 22 21
c off-by-one in path termination
e
s 00001/00000/00201
d D 5.10 91/02/23 19:49:41 donn 21 20
c Add include files to get prototype declarations, and fix bugs found.
e
s 00134/00072/00067
d D 5.9 91/02/20 08:26:08 bostic 20 19
c rename getwd to getcwd for POSIX.1 compatibility
c add System V, X/Open style path malloc'ing if user argument is NULL.
e
s 00001/00011/00138
d D 5.8 90/06/01 14:11:34 bostic 19 18
c new copyright notice
e
s 00073/00042/00076
d D 5.7 90/05/27 11:33:01 bostic 18 17
c don't lstat if not crossing a mount point
e
s 00048/00014/00070
d D 5.6 90/03/20 17:11:44 karels 17 16
c keep going if lstat fails on random directory entry;
c don't just skip a level (or more) if a directory isn't found in its parent;
c always return pathname in error string
e
s 00001/00001/00083
d D 5.5 89/12/12 10:00:54 bostic 16 15
c return error message to the user
e
s 00065/00097/00017
d D 5.4 89/03/18 09:47:22 bostic 15 14
c from scratch; leave '/' on end of all pathnames
e
s 00001/00001/00113
d D 5.3 88/08/02 17:20:58 bostic 14 13
c don't reference free'd memory; bug report 4.3BSD/lib/129
e
s 00002/00002/00112
d D 5.2 86/03/09 19:49:27 donn 13 12
c added LIBC_SCCS condition for sccs ids
e
s 00009/00001/00105
d D 5.1 85/05/30 10:43:35 dist 12 11
c Add copyright
e
s 00034/00036/00072
d D 4.10 85/01/24 16:50:30 ralph 11 10
c modified to not call chdir(). Also, uses fewer stat()'s.
e
s 00001/00001/00107
d D 4.9 84/12/09 02:55:30 lepreau 10 9
c report real path even if a symlink to a root dir comes first
e
s 00001/00000/00107
d D 4.8 83/03/02 09:46:49 nicklin 9 8
c declared char *strcpy();
e
s 00002/00003/00105
d D 4.7 83/01/05 15:01:55 sam 8 7
c use MAXPATHLEN from <sys/param.h>
e
s 00079/00055/00029
d D 4.6 83/01/05 14:57:07 sam 7 6
c new version from nicklin -- bugs to him
e
s 00004/00003/00080
d D 4.5 83/01/04 20:51:23 sam 6 4
c make error messages returned legible
e
s 00001/00001/00082
d R 4.5 83/01/04 14:57:31 sam 5 4
c screwed up last time
e
s 00007/00012/00076
d D 4.4 83/01/04 14:42:04 sam 4 3
c don't abort, just return error in buff and NULL value
e
s 00006/00005/00082
d D 4.3 83/01/04 14:32:01 sam 3 2
c missing check on chdir
e
s 00012/00010/00075
d D 4.2 83/01/02 16:41:22 sam 2 1
c make it callable multiple times (from sun)
e
s 00085/00000/00000
d D 4.1 82/12/28 15:19:43 sam 1 0
c date and time created 82/12/28 15:19:43 by sam
e
u
U
t
T
I 1
D 12
/*	%W%	(Berkeley)	%G%	*/
E 12
I 12
/*
D 15
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
D 20
 * Copyright (c) 1989 The Regents of the University of California.
E 20
I 20
D 24
 * Copyright (c) 1989, 1991 The Regents of the University of California.
E 20
 * All rights reserved.
E 24
I 24
D 25
 * Copyright (c) 1989, 1991, 1993
E 25
I 25
 * Copyright (c) 1989, 1991, 1993, 1995
E 25
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
I 27
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry.
 *
E 27
D 19
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
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 15
 */

D 13
#ifndef lint
E 13
I 13
#if defined(LIBC_SCCS) && !defined(lint)
E 13
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif not lint
E 13
I 13
D 15
#endif LIBC_SCCS and not lint
E 15
I 15
#endif /* LIBC_SCCS and not lint */
E 15
E 13
E 12

D 15
/*
D 7
 * Getwd
E 7
I 7
 * getwd() returns the pathname of the current working directory. On error
 * an error message is copied to pathname and null pointer is returned.
E 7
 */
E 15
D 2
#include	<sys/param.h>
#include	<sys/stat.h>
#include	<sys/dir.h>
E 2
I 2
#include <sys/param.h>
#include <sys/stat.h>
I 23

E 23
I 20
D 27
#include <errno.h>
E 27
E 20
D 15
#include <sys/dir.h>
E 15
I 15
#include <dirent.h>
I 27
#include <errno.h>
#include <fcntl.h>
E 27
I 20
#include <stdio.h>
#include <stdlib.h>
E 20
I 18
#include <string.h>
I 21
#include <unistd.h>
E 21
E 18
E 15
E 2

I 27
static char *getcwd_physical __P((char *, size_t));

E 27
I 18
#define	ISDOT(dp) \
	(dp->d_name[0] == '.' && (dp->d_name[1] == '\0' || \
	    dp->d_name[1] == '.' && dp->d_name[2] == '\0'))

E 18
D 7
#define	dot	"."
#define	dotdot	".."
E 7
I 7
D 11
#define CURDIR		"."
E 11
D 15
#define GETWDERR(s)	strcpy(pathname, (s));
D 11
#define PARENTDIR	".."
#define PATHSEP		"/"
D 8
#define PATHSIZE	1024
E 8
#define ROOTDIR		"/"
E 11
E 7

I 9
char *strcpy();
E 9
I 4
D 6
#define	prexit(s)	{ strcpy(np, s); return (NULL); }
E 6
I 6
D 7
#define	prexit(s)	 { strcpy(esave, (s)); return (NULL); }
E 7
I 7
static int pathsize;			/* pathname length */
E 7
E 6

E 15
E 4
D 2
static	char	*name;
E 2
I 2
D 7
static	char *name;
E 2

D 2
static	DIR	*file;
static	int	off	= -1;
static	struct	stat	d, dd;
static	struct	direct	*dir;
E 2
I 2
static	DIR *file;
static	int off;
static	struct stat d, dd;
static	struct direct *dir;
E 2

E 7
char *
D 7
getwd(np)
D 2
char *np;
E 2
I 2
	char *np;
E 7
I 7
D 15
getwd(pathname)
	char *pathname;
E 15
I 15
D 20
getwd(store)
	char *store;
E 20
I 20
getcwd(pt, size)
	char *pt;
	size_t size;
E 20
E 15
E 7
E 2
{
D 2
	int rdev, rino;
E 2
I 2
D 7
	dev_t rdev;
	ino_t rino;
I 6
	char *esave = np;
E 7
I 7
D 8
	char pathbuf[PATHSIZE];		/* temporary pathname buffer */
E 8
I 8
D 15
	char pathbuf[MAXPATHLEN];		/* temporary pathname buffer */
E 8
	char *pnptr = &pathbuf[(sizeof pathbuf)-1]; /* pathname pointer */
I 11
	char curdir[MAXPATHLEN];	/* current directory buffer */
	char *dptr = curdir;		/* directory pointer */
E 11
	char *prepend();		/* prepend dirname to pathname */
D 11
	dev_t rdev;			/* root device number */
E 11
I 11
	dev_t cdev, rdev;		/* current & root device number */
	ino_t cino, rino;		/* current & root inode number */
E 11
	DIR *dirp;			/* directory stream */
D 11
	ino_t rino;			/* root inode number */
E 11
	struct direct *dir;		/* directory entry struct */
D 11
	struct stat d ,dd;		/* file status struct */
E 11
I 11
	struct stat d, dd;		/* file status struct */
E 15
I 15
D 20
	extern int errno;
E 20
D 18
	register DIR *dir;
E 18
D 27
	register struct dirent *dp;
D 18
	register int first;
E 18
I 18
	register DIR *dir;
I 20
	register dev_t dev;
E 20
	register ino_t ino;
E 18
D 20
	register char *pp, *pu;
E 20
D 18
	struct stat s, tmp;
	dev_t root_dev;
E 18
I 18
	register int first;
I 20
	register char *bpt, *bup;
E 27
I 27
	char *pwd;
	size_t pwdlen;
	dev_t dev;
	ino_t ino;
E 27
E 20
	struct stat s;
D 20
	dev_t root_dev, dev;
E 20
I 20
D 27
	dev_t root_dev;
E 20
E 18
	ino_t root_ino;
D 17
	char path[MAXPATHLEN], up[MAXPATHLEN], *strerror();
E 17
I 17
D 20
	int save_errno, found;
D 18
	char path[MAXPATHLEN], up[MAXPATHLEN], *file, *strerror();
E 18
I 18
	char path[MAXPATHLEN], up[MAXPATHLEN], *file;
E 20
I 20
D 25
	size_t ptsize, upsize;
E 25
I 25
	size_t ptsize, pwdlen, upsize;
E 25
	int save_errno;
D 25
	char *ept, *eup, *up;
E 25
I 25
	char *ept, *eup, *pwd, *up;
E 27
E 25
E 20
E 18
E 17
E 15
E 11
E 7
E 6
E 2

I 25
	/* Check $PWD -- if it's right, it's fast. */
D 26
	if ((pwd = getenv("PWD")) != NULL && !stat(pwd, &s)) {
E 26
I 26
	if ((pwd = getenv("PWD")) != NULL && pwd[0] == '/' && !stat(pwd, &s)) {
E 26
		dev = s.st_dev;
		ino = s.st_ino;
		if (!stat(".", &s) && dev == s.st_dev && ino == s.st_ino) {
			pwdlen = strlen(pwd);
			if (size != 0) {
				if (pwdlen + 1 > size) {
					errno = ERANGE;
					return (NULL);
				}
			} else if ((pt = malloc(pwdlen + 1)) == NULL)
				return (NULL);
			memmove(pt, pwd, pwdlen);
D 28
			pwd[pwdlen] = '\0';
E 28
I 28
			pt[pwdlen] = '\0';
E 28
			return (pt);
		}
	}
		
I 27
	return (getcwd_physical(pt, size));
}

/*
 * char *realpath(const char *path, char resolved_path[MAXPATHLEN]);
 *
 * Find the real name of path, by removing all ".", ".." and symlink
 * components.  Returns (resolved) on success, or (NULL) on failure,
 * in which case the path which caused trouble is left in (resolved).
 */
char *
realpath(path, resolved)
	const char *path;
	char *resolved;
{
	struct stat sb;
	int fd, n, rootd, serrno;
	char *p, *q, wbuf[MAXPATHLEN];

	/* Save the starting point. */
	if ((fd = open(".", O_RDONLY)) < 0) {
		(void)strcpy(resolved, ".");
		return (NULL);
	}

	/*
	 * Find the dirname and basename from the path to be resolved.
	 * Change directory to the dirname component.
	 * lstat the basename part.
	 *     if it is a symlink, read in the value and loop.
	 *     if it is a directory, then change to that directory.
	 * get the current directory name and append the basename.
	 */
	(void)strncpy(resolved, path, MAXPATHLEN - 1);
	resolved[MAXPATHLEN - 1] = '\0';
loop:
	q = strrchr(resolved, '/');
	if (q != NULL) {
		p = q + 1;
		if (q == resolved)
			q = "/";
		else {
			do {
				--q;
			} while (q > resolved && *q == '/');
			q[1] = '\0';
			q = resolved;
		}
		if (chdir(q) < 0)
			goto err1;
	} else
		p = resolved;

	/* Deal with the last component. */
	if (lstat(p, &sb) == 0) {
		if (S_ISLNK(sb.st_mode)) {
			n = readlink(p, resolved, MAXPATHLEN);
			if (n < 0)
				goto err1;
			resolved[n] = '\0';
			goto loop;
		}
		if (S_ISDIR(sb.st_mode)) {
			if (chdir(p) < 0)
				goto err1;
			p = "";
		}
	}

	/*
	 * Save the last component name and get the full pathname of
	 * the current directory.
	 */
	(void)strcpy(wbuf, p);

	/*
	 * Call the inernal internal version of getcwd which
	 * does a physical search rather than using the $PWD short-cut
	 */
	if (getcwd_physical(resolved, MAXPATHLEN) == 0)
		goto err1;

	/*
	 * Join the two strings together, ensuring that the right thing
	 * happens if the last component is empty, or the dirname is root.
	 */
	if (resolved[0] == '/' && resolved[1] == '\0')
		rootd = 1;
	else
		rootd = 0;

	if (*wbuf) {
		if (strlen(resolved) + strlen(wbuf) + rootd + 1 > MAXPATHLEN) {
			errno = ENAMETOOLONG;
			goto err1;
		}
		if (rootd == 0)
			(void)strcat(resolved, "/");
		(void)strcat(resolved, wbuf);
	}

	/* Go back to where we came from. */
	if (fchdir(fd) < 0) {
		serrno = errno;
		goto err2;
	}

	/* It's okay if the close fails, what's an fd more or less? */
	(void)close(fd);
	return (resolved);

err1:	serrno = errno;
	(void)fchdir(fd);
err2:	(void)close(fd);
	errno = serrno;
	return (NULL);
}

static char *
getcwd_physical(pt, size)
	char *pt;
	size_t size;
{
	register struct dirent *dp;
	register DIR *dir;
	register dev_t dev;
	register ino_t ino;
	register int first;
	register char *bpt, *bup;
	struct stat s;
	dev_t root_dev;
	ino_t root_ino;
	size_t ptsize, upsize;
	int save_errno;
	char *ept, *eup, *up;

E 27
E 25
I 18
D 20
	/* save root values */
E 18
I 2
D 7
	off = -1;
E 2
	*np++ = '/';
	name = np;
	stat("/", &d);
E 7
I 7
D 15
	pathsize = 0;
	*pnptr = '\0';
D 11
	stat(ROOTDIR, &d);
E 11
I 11
	if (stat("/", &d) < 0) {
		GETWDERR("getwd: can't stat /");
		return (NULL);
	}
E 11
E 7
	rdev = d.st_dev;
	rino = d.st_ino;
I 11
	strcpy(dptr, "./");
	dptr += 2;
	if (stat(curdir, &d) < 0) {
		GETWDERR("getwd: can't stat .");
		return (NULL);
	}
E 11
	for (;;) {
D 7
		stat(dot, &d);
		if (d.st_ino==rino && d.st_dev==rdev)
			goto done;
		if ((file = opendir(dotdot)) == NULL)
D 4
			prexit("getwd: cannot open ..\n");
E 4
I 4
			prexit("getwd: cannot open ..");
E 4
		fstat(file->dd_fd, &dd);
D 3
		chdir(dotdot);
		if(d.st_dev == dd.st_dev) {
E 3
I 3
		if (chdir(dotdot) < 0)
D 4
			prexit("getwd: cannot chdir to ..\n");
E 4
I 4
			prexit("getwd: cannot chdir to ..");
E 7
I 7
D 11
		stat(CURDIR, &d);
E 11
		if (d.st_ino == rino && d.st_dev == rdev)
			break;		/* reached root directory */
D 11
		if ((dirp = opendir(PARENTDIR)) == NULL) {
E 11
I 11
		cino = d.st_ino;
		cdev = d.st_dev;
		strcpy(dptr, "../");
		dptr += 3;
		if ((dirp = opendir(curdir)) == NULL) {
E 11
			GETWDERR("getwd: can't open ..");
D 11
			goto fail;
E 11
I 11
			return (NULL);
E 15
I 15
D 17
	if (stat("/", &s))
E 17
I 17
	if (stat("/", &s)) {
		file = "/";
E 17
		goto err;
E 20
I 20
	/*
	 * If no buffer specified by the user, allocate one as necessary.
	 * If a buffer is specified, the size has to be non-zero.  The path
	 * is built from the end of the buffer backwards.
	 */
	if (pt) {
		ptsize = 0;
		if (!size) {
			errno = EINVAL;
D 23
			return((char *)NULL);
E 23
I 23
			return (NULL);
E 23
		}
		ept = pt + size;
	} else {
D 23
		if (!(pt = (char *)malloc(ptsize = 1024 - 4)))
			return((char *)NULL);
E 23
I 23
		if ((pt = malloc(ptsize = 1024 - 4)) == NULL)
			return (NULL);
E 23
		ept = pt + ptsize;
E 20
I 17
	}
E 17
D 20
	root_dev = s.st_dev;
	root_ino = s.st_ino;
E 20
I 20
	bpt = ept - 1;
D 22
	*ept = '\0';
E 22
I 22
	*bpt = '\0';
E 22
E 20
D 17
	if (stat(".", &s))
E 17
I 17
D 18
	if (stat(".", &s)) {
		file = ".";
E 17
		goto err;
I 17
	}
E 18
I 18

D 20
	/* init path pointer; built from the end of the buffer */
E 18
E 17
	pp = path + sizeof(path) - 1;
	*pp = '\0';
I 18

	/* special case first stat, it's ".", not ".." */
E 20
I 20
	/*
	 * Allocate bytes (1024 - malloc space) for the string of "../"'s.
	 * Should always be enough (it's 340 levels).  If it's not, allocate
D 25
	 * as necessary.  Special * case the first stat, it's ".", not "..".
E 25
I 25
	 * as necessary.  Special case the first stat, it's ".", not "..".
E 25
	 */
D 23
	if (!(up = (char *)malloc(upsize = 1024 - 4)))
E 23
I 23
	if ((up = malloc(upsize = 1024 - 4)) == NULL)
E 23
		goto err;
	eup = up + MAXPATHLEN;
	bup = up;
E 20
	up[0] = '.';
	up[1] = '\0';

E 18
D 20
	for (pu = up, first = 1;; first = 0) {
D 18
		if (root_dev == s.st_dev && root_ino == s.st_ino) {
E 18
I 18
		/* stat current level */
		if (lstat(up, &s)) {
			file = up;
E 20
I 20
	/* Save root values, so know when to stop. */
	if (stat("/", &s))
		goto err;
	root_dev = s.st_dev;
	root_ino = s.st_ino;

	errno = 0;			/* XXX readdir has no error return. */

	for (first = 1;; first = 0) {
		/* Stat the current level. */
		if (lstat(up, &s))
E 20
			goto err;
D 20
		}
E 20

D 20
		/* save current node values */
E 20
I 20
		/* Save current node values. */
E 20
		ino = s.st_ino;
		dev = s.st_dev;

D 20
		/* check for root */
E 20
I 20
		/* Check for reaching root. */
E 20
		if (root_dev == dev && root_ino == ino) {
E 18
D 20
			*store = '/';
D 17
			(void)strcpy(store + 1, pp);
			return(store);
E 17
I 17
			(void) strcpy(store + 1, pp);
			return (store);
E 20
I 20
			*--bpt = '/';
			/*
			 * It's unclear that it's a requirement to copy the
			 * path to the beginning of the buffer, but it's always
			 * been that way and stuff would probably break.
			 */
			(void)bcopy(bpt, pt, ept - bpt);
			free(up);
D 23
			return(pt);
E 23
I 23
			return (pt);
E 23
E 20
E 17
E 15
E 11
		}
I 18

E 18
D 11
		if (chdir(PARENTDIR) < 0) {
			GETWDERR("getwd: can't chdir to ..");
			goto fail;
		}
		fstat(dirp->dd_fd, &dd);
E 7
E 4
		if (d.st_dev == dd.st_dev) {
E 3
D 7
			if(d.st_ino == dd.st_ino)
				goto done;
E 7
I 7
			if (d.st_ino == dd.st_ino) {
E 11
I 11
D 15
		fstat(dirp->dd_fd, &d);
		if (cdev == d.st_dev) {
			if (cino == d.st_ino) {
E 11
				/* reached root directory */
				closedir(dirp);
E 15
I 15
D 20
		*pu++ = '.';
		*pu++ = '.';
		*pu = '\0';
E 20
I 20
		/*
		 * Build pointer to the parent directory, allocating memory
		 * as necessary.  Max length is 3 for "../", the largest
		 * possible component name, plus a trailing NULL.
		 */
		if (bup + 3  + MAXNAMLEN + 1 >= eup) {
D 23
			if (!(up = (char *)realloc(up, upsize *= 2)))
E 23
I 23
			if ((up = realloc(up, upsize *= 2)) == NULL)
E 23
				goto err;
I 23
			bup = up;
E 23
			eup = up + upsize;
		}
		*bup++ = '.';
		*bup++ = '.';
		*bup = '\0';
E 20
D 18
		if (!(dir = opendir(up))) {
E 18
I 18

D 20
		/* open and stat parent */
		if (!(dir = opendir(up)) || fstat(dirfd(dir), &s)) {
E 18
D 17
			(void)strcpy(path, "getwd: opendir failed.");
			return((char *)NULL);
E 17
I 17
			file = up;
E 20
I 20
		/* Open and stat parent directory. */
		if (!(dir = opendir(up)) || fstat(dirfd(dir), &s))
E 20
			goto err;
E 17
D 20
		}
I 18
		found = save_errno = 0;
E 20

E 18
D 20
		*pu++ = '/';
E 20
I 20
		/* Add trailing slash for next directory. */
		*bup++ = '/';
E 20
D 17
		while (dp = readdir(dir)) {
			if (dp->d_name[0] == '.' && (!dp->d_name[1] ||
			    dp->d_name[1] == '.' && !dp->d_name[2]))
E 17
I 17
D 18
		found = 0;
		file = NULL;
		while (errno = 0, dp = readdir(dir)) {
			if (dp->d_name[0] == '.' && (dp->d_name[1] == '\0' ||
			    dp->d_name[1] == '.' && dp->d_name[2] == '\0'))
E 17
				continue;
			bcopy(dp->d_name, pu, dp->d_namlen + 1);
D 17
			if (lstat(up, &tmp))
				goto err;
E 17
I 17
			if (lstat(up, &tmp)) {
				file = dp->d_name;
E 18
I 18

		/*
D 20
		 * if it's a mount point you have to stat each element because
E 20
I 20
		 * If it's a mount point, have to stat each element because
E 20
		 * the inode number in the directory is for the entry in the
		 * parent directory, not the inode number of the mounted file.
		 */
I 20
		save_errno = 0;
E 20
		if (s.st_dev == dev) {
D 20
			while (dp = readdir(dir))
E 20
I 20
			for (;;) {
				if (!(dp = readdir(dir)))
					goto notfound;
E 20
				if (dp->d_fileno == ino)
D 20
					goto hit;
		} else {
			while (dp = readdir(dir)) {
E 20
I 20
					break;
			}
		} else
			for (;;) {
				if (!(dp = readdir(dir)))
					goto notfound;
E 20
				if (ISDOT(dp))
					continue;
D 20
				bcopy(dp->d_name, pu, dp->d_namlen + 1);
E 20
I 20
				bcopy(dp->d_name, bup, dp->d_namlen + 1);

				/* Save the first error for later. */
E 20
				if (lstat(up, &s)) {
D 20
					file = dp->d_name;
					save_errno = errno;
E 20
I 20
					if (!save_errno)
						save_errno = errno;
E 20
					errno = 0;
					continue;
				}
D 20
				if (s.st_dev == dev && s.st_ino == ino) {
hit:					if (!first)
						*--pp = '/';
					pp -= dp->d_namlen;
					bcopy(dp->d_name, pp, dp->d_namlen);
					found = 1;
E 20
I 20
				if (s.st_dev == dev && s.st_ino == ino)
E 20
					break;
D 20
				}
E 20
			}
D 20
			if (errno) {
				file = up;
E 18
				save_errno = errno;
D 18
				continue;
E 18
			}
E 17
D 18
			if (tmp.st_dev == s.st_dev && tmp.st_ino == s.st_ino) {
				if (!first)
					*--pp = '/';
				pp -= dp->d_namlen;
				bcopy(dp->d_name, pp, dp->d_namlen);
I 17
				found = 1;
E 17
E 15
				break;
			}
E 18
E 7
D 6
			do
E 6
I 6
D 15
			do {
E 6
D 7
				if ((dir = readdir(file)) == NULL)
D 4
					prexit("getwd: read error in ..\n");
E 4
I 4
					prexit("getwd: read error in ..");
E 7
I 7
				if ((dir = readdir(dirp)) == NULL) {
					closedir(dirp);
					GETWDERR("getwd: read error in ..");
D 11
					goto fail;
E 11
I 11
					return (NULL);
E 11
				}
E 7
E 4
D 6
			while (dir->d_ino != d.st_ino);
E 6
I 6
D 11
			} while (dir->d_ino != d.st_ino);
E 11
I 11
			} while (dir->d_ino != cino);
E 11
E 6
D 3
		}
		else do {
E 3
I 3
		} else
			do {
E 3
D 7
				if ((dir = readdir(file)) == NULL)
D 4
					prexit("getwd: read error in ..\n");
E 4
I 4
					prexit("getwd: read error in ..");
E 7
I 7
D 11
				if((dir = readdir(dirp)) == NULL) {
E 11
I 11
				if ((dir = readdir(dirp)) == NULL) {
E 11
					closedir(dirp);
					GETWDERR("getwd: read error in ..");
D 11
					goto fail;
E 11
I 11
					return (NULL);
E 11
				}
E 7
E 4
D 10
				stat(dir->d_name, &dd);
E 10
I 10
D 11
				lstat(dir->d_name, &dd);
E 10
			} while(dd.st_ino != d.st_ino || dd.st_dev != d.st_dev);
E 11
I 11
				strcpy(dptr, dir->d_name);
				lstat(curdir, &dd);
			} while(dd.st_ino != cino || dd.st_dev != cdev);
E 11
D 7
		closedir(file);
		cat();
E 7
I 7
D 14
		closedir(dirp);
E 14
D 11
		pnptr = prepend(PATHSEP, prepend(dir->d_name, pnptr));
E 11
I 11
		pnptr = prepend("/", prepend(dir->d_name, pnptr));
I 14
		closedir(dirp);
E 15
I 15
		}
I 17
D 18
		if (errno) {
			save_errno = errno;
			file = up;
		}
E 17
		closedir(dir);
E 18
I 18
		(void) closedir(dir);
E 20

E 18
D 20
		*pu = '\0';
E 20
I 20
		/*
		 * Check for length of the current name, preceding slash,
		 * leading slash.
		 */
		if (bpt - pt <= dp->d_namlen + (first ? 1 : 2)) {
			size_t len, off;
E 20
I 18

E 18
I 17
D 20
		if (!found) {
			/*
			 * We didn't find the current level in its parent
			 * directory; figure out what to complain about.
			 */
D 18
			if (file) {
E 18
I 18
			if (save_errno) {
E 18
				errno = save_errno;
E 20
I 20
			if (!ptsize) {
				errno = ERANGE;
E 20
				goto err;
			}
D 20
			(void) sprintf(store, "%s not found in %s?\n",
				first ? "." : pp, up);
			return ((char *)NULL);
E 20
I 20
			off = bpt - pt;
			len = ept - bpt;
D 23
			if (!(pt = (char *)realloc(pt, ptsize *= 2)))
E 23
I 23
			if ((pt = realloc(pt, ptsize *= 2)) == NULL)
E 23
				goto err;
			bpt = pt + off;
			ept = pt + ptsize;
			(void)bcopy(bpt, ept - len, len);
			bpt = ept - len;
E 20
		}
I 20
		if (!first)
			*--bpt = '/';
		bpt -= dp->d_namlen;
		bcopy(dp->d_name, bpt, dp->d_namlen);
		(void)closedir(dir);

		/* Truncate any file name. */
		*bup = '\0';
E 20
D 18

		/* stat "." at current level, then ascend */
E 17
		if (lstat(up, &s)) {
D 16
err:			(void)sprintf(path, "getwd: %s", strerror(errno));
E 16
I 16
D 17
err:			(void)sprintf(store, "getwd: %s", strerror(errno));
E 16
			return((char *)NULL);
E 17
I 17
			file = up;
			goto err;
E 17
		}
E 18
E 15
E 14
E 11
E 7
	}
I 20

notfound:
	/*
	 * If readdir set errno, use it, not any saved error; otherwise,
	 * didn't find the current directory in its parent directory, set
	 * errno to ENOENT.
	 */
	if (!errno)
		errno = save_errno ? save_errno : ENOENT;
	/* FALLTHROUGH */
E 20
I 17
D 18

E 18
err:
D 20
	(void) sprintf(store, "getwd: %s: %s", file, strerror(errno));
	return ((char *)NULL);
E 20
I 20
	if (ptsize)
		free(pt);
	free(up);
D 23
	return((char *)NULL);
E 23
I 23
	return (NULL);
E 23
E 20
E 17
D 7
done:
	name--;
	if (chdir(name) < 0)
D 4
		prexit("getwd: can't change back\n");
E 4
I 4
		prexit("getwd: can't change back");
E 4
	return (name);
E 7
I 7
D 15
	if (*pnptr == '\0')		/* current dir == root dir */
D 11
		strcpy(pathname, ROOTDIR);
	else {
E 11
I 11
		strcpy(pathname, "/");
	else
E 11
		strcpy(pathname, pnptr);
D 11
		if (chdir(pnptr) < 0) {
			GETWDERR("getwd: can't change back to .");
			return (NULL);
		}
	}
E 11
	return (pathname);
D 11

fail:
	chdir(prepend(CURDIR, pnptr));
	return (NULL);
E 11
E 7
}

D 7
cat()
E 7
I 7
/*
 * prepend() tacks a directory name onto the front of a pathname.
 */
static char *
prepend(dirname, pathname)
	register char *dirname;
	register char *pathname;
E 7
{
D 7
	register i, j;
E 7
I 7
	register int i;			/* directory name size counter */
E 7

D 7
	i = -1;
	while (dir->d_name[++i] != 0);
	if ((off+i+2) > 1024-1)
		return;
	for(j=off+1; j>=0; --j)
		name[j+i+1] = name[j];
	if (off >= 0)
		name[i] = '/';
	off=i+off+1;
	name[off] = 0;
	for(--i; i>=0; --i)
		name[i] = dir->d_name[i];
E 7
I 7
	for (i = 0; *dirname != '\0'; i++, dirname++)
		continue;
D 8
	if ((pathsize += i) < PATHSIZE)
E 8
I 8
	if ((pathsize += i) < MAXPATHLEN)
E 8
		while (i-- > 0)
			*--pathname = *--dirname;
	return (pathname);
E 15
E 7
D 4
}

prexit(cp)
D 3
char *cp;
E 3
I 3
	char *cp;
E 3
{
	write(2, cp, strlen(cp));
	exit(1);
E 4
}
E 1
