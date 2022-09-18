h46452
s 00002/00002/00058
d D 8.1 93/06/04 13:09:54 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00004/00054
d D 5.2 93/03/25 07:31:33 bostic 10 9
c Jeff Forys' changes to keep from leaving two slashes in the pathname
c GNU Emacs doesn't like this
e
s 00028/00039/00030
d D 5.1 91/02/22 16:59:59 bostic 9 8
c cleanup, update, reimplement to work as correctly as possible
e
s 00003/00001/00066
d D 4.8 90/06/22 22:40:04 bostic 8 7
c free up the memory if it fails
e
s 00001/00011/00066
d D 4.7 90/06/01 14:45:08 bostic 7 6
c new copyright notice
e
s 00020/00034/00057
d D 4.6 88/07/23 16:11:43 bostic 6 5
c cleanup; tmpfile now lets tmpnam allocate space for it, also checks
c result of tmpnam() call.  tmpnam() allocates space, doesn't use a static buf;
c rewrite tempnam() to do no error checking, just depend on mktemp(3).
e
s 00010/00005/00081
d D 4.5 88/06/27 18:25:54 bostic 5 4
c install approved copyright notice
e
s 00077/00009/00009
d D 4.4 88/06/08 18:06:45 bostic 4 3
c rewrite tmpnam(BA_LIB) from manual page and add Berkeley specific header
c add tempnam(BA_LIB) and tmpfile(BA_LIB)
e
s 00002/00002/00016
d D 4.3 86/03/09 19:37:07 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00010/00001/00008
d D 4.2 85/05/30 13:54:19 mckusick 2 1
c Add copyrights
e
s 00009/00000/00000
d D 4.1 80/12/21 16:51:02 wnj 1 0
c date and time created 80/12/21 16:51:02 by wnj
e
u
U
t
T
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 11
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
E 4
 */

D 3
#ifndef lint
E 3
I 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
D 4
#endif LIBC_SCCS and not lint
E 4
I 4
#endif /* LIBC_SCCS and not lint */
E 4
E 3

E 2
D 4
char *tmpnam(s)
char *s;
E 4
I 4
#include <sys/param.h>
I 9
#include <errno.h>
E 9
D 6
#include <sys/stat.h>
#include <sys/file.h>
E 6
#include <stdio.h>
I 9
#include <stdlib.h>
#include <unistd.h>
#include <paths.h>
E 9

D 9
#define	P_tmpdir	"/usr/tmp"

FILE *
tmpfile()
E 4
{
D 4
	static seed;
E 4
I 4
	FILE *fp;
D 6
	char *f, name[MAXPATHLEN], *tmpnam();
E 6
I 6
	char *f, *tmpnam();
E 6
E 4

D 4
	sprintf(s, "temp.%d.%d", getpid(), seed++);
	return(s);
E 4
I 4
D 6
	if (!(fp = fopen(f = tmpnam(name), "w+"))) {
		fprintf(stderr, "tmpfile: cannot open %s.\n", name);
E 6
I 6
	if (!(f = tmpnam((char *)NULL)) || !(fp = fopen(f, "w+"))) {
		fprintf(stderr, "tmpfile: cannot open %s.\n", f);
E 6
		return(NULL);
	}
	(void)unlink(f);
	return(fp);
}

E 9
char *
D 9
tmpnam(s)
	char *s;
{
D 6
	static char name[MAXPATHLEN];
	char *mktemp();
E 6
I 6
	char *malloc(), *mktemp();
E 6

D 6
	if (!s)
		s = name;
E 6
I 6
	if (!s && !(s = malloc((u_int)MAXPATHLEN)))
		return(NULL);
E 6
	(void)sprintf(s, "%s/XXXXXX", P_tmpdir);
	return(mktemp(s));
}

char *
E 9
tempnam(dir, pfx)
D 9
	char *dir, *pfx;
E 9
I 9
	const char *dir, *pfx;
E 9
{
D 6
	struct stat buf;
	char *f, *name, *getenv(), *malloc(), *mktemp(), *strcat(), *strcpy();
E 6
I 6
D 9
	char *f, *name, *getenv(), *malloc(), *mktemp();
E 9
I 9
	int sverrno;
	char *f, *name;
E 9
E 6

D 9
	if (!(name = malloc((u_int)MAXPATHLEN)))
E 9
I 9
	if (!(name = malloc(MAXPATHLEN)))
E 9
		return(NULL);
D 6
	if ((f = getenv("TMPDIR")) && !stat(f, &buf) &&
	    (buf.st_mode&S_IFMT) == S_IFDIR && !access(f, W_OK|X_OK)) {
		(void)strcpy(name, f);
		goto done;
E 6
I 6

I 9
	if (!pfx)
		pfx = "tmp.";

E 9
	if (f = getenv("TMPDIR")) {
D 9
		(void)sprintf(name, "%s/%sXXXXXX", f, pfx ? "" : pfx);
E 9
I 9
D 10
		(void)snprintf(name, MAXPATHLEN, "%s/%sXXXXXX", f, pfx);
E 10
I 10
		(void)snprintf(name, MAXPATHLEN, "%s%s%sXXXXXX", f,
		    *(f + strlen(f) - 1) == '/'? "": "/", pfx);
E 10
E 9
		if (f = mktemp(name))
			return(f);
E 6
	}
D 6
	if (dir && !stat(dir, &buf) &&
	    (buf.st_mode&S_IFMT) == S_IFDIR && !access(dir, W_OK|X_OK)) {
		(void)strcpy(name, dir);
		goto done;
E 6
I 6
D 9
	if (dir) {
		(void)sprintf(name, "%s/%sXXXXXX", dir, pfx ? "" : pfx);
E 9
I 9

	if (f = (char *)dir) {
D 10
		(void)snprintf(name, MAXPATHLEN, "%s/%sXXXXXX", f, pfx);
E 10
I 10
		(void)snprintf(name, MAXPATHLEN, "%s%s%sXXXXXX", f,
		    *(f + strlen(f) - 1) == '/'? "": "/", pfx);
E 10
E 9
		if (f = mktemp(name))
			return(f);
E 6
	}
D 6
	if (!stat(P_tmpdir, &buf) &&
	    (buf.st_mode&S_IFMT) == S_IFDIR && !access(P_tmpdir, W_OK|X_OK)) {
		(void)strcpy(name, P_tmpdir);
		goto done;
	}
	if (!stat("/tmp", &buf) &&
	    (buf.st_mode&S_IFMT) == S_IFDIR && !access("/tmp", W_OK|X_OK)) {
		(void)strcpy(name, "/tmp");
		goto done;
	}
	return(NULL);
done:	(void)strcat(name, "/");
	if (pfx)
		(void)strcat(name, pfx);
	(void)strcat(name, "XXXXXX");
E 6
I 6
D 9
	(void)sprintf(name, "%s/%sXXXXXX", P_tmpdir, pfx ? "" : pfx);
E 9
I 9

	f = P_tmpdir;
D 10
	(void)snprintf(name, MAXPATHLEN, "%s/%sXXXXXX", f, pfx);
E 10
I 10
	(void)snprintf(name, MAXPATHLEN, "%s%sXXXXXX", f, pfx);
E 10
E 9
	if (f = mktemp(name))
		return(f);
D 9
	(void)sprintf(name, "/tmp/%sXXXXXX", pfx ? "" : pfx);
E 6
D 8
	return(mktemp(name));
E 8
I 8
	if (!(f = mktemp(name)))
		(void)free(name);
	return(f);
E 9
I 9

	f = _PATH_TMP;
D 10
	(void)snprintf(name, MAXPATHLEN, "%s/%sXXXXXX", f, pfx);
E 10
I 10
	(void)snprintf(name, MAXPATHLEN, "%s%sXXXXXX", f, pfx);
E 10
	if (f = mktemp(name))
		return(f);

	sverrno = errno;
	free(name);
	errno = sverrno;
	return(NULL);
E 9
E 8
E 4
}
E 1
