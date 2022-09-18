h07517
s 00002/00002/00098
d D 8.1 93/06/04 13:08:07 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00099
d D 5.11 92/07/12 12:26:02 bostic 12 11
c needs ctype.h for isdigit()
e
s 00003/00002/00096
d D 5.10 91/02/24 13:30:14 bostic 11 10
c Add include files to get prototype declarations, and fix bugs found.
e
s 00001/00011/00097
d D 5.9 90/06/01 14:12:20 bostic 10 9
c new copyright notice
e
s 00039/00038/00069
d D 5.8 89/10/16 13:40:28 bostic 9 8
c make sure we stat the right directory
e
s 00010/00005/00097
d D 5.7 88/06/27 17:34:08 bostic 8 7
c install approved copyright notice
e
s 00001/00001/00101
d D 5.6 88/05/23 20:42:00 bostic 7 6
c ANSI C fix
e
s 00008/00002/00094
d D 5.5 87/11/30 11:13:51 bostic 6 5
c Berkeley code; fix copyright
e
s 00017/00010/00079
d D 5.4 87/09/14 12:30:03 bostic 5 4
c use stat, not access; bug report 4.3BSD/lib/94
e
s 00076/00017/00013
d D 5.3 87/04/10 14:58:52 bostic 4 3
c bug report 4.2BSD/lib/63
e
s 00002/00002/00028
d D 5.2 86/03/09 19:50:51 donn 3 2
c added LIBC_SCCS condition for sccs ids
e
s 00003/00001/00027
d D 5.1 85/06/05 12:27:33 mckusick 2 1
c Add copyright
e
s 00028/00000/00000
d D 4.1 83/06/22 18:18:00 root 1 0
c date and time created 83/06/22 18:18:00 by root
e
u
U
t
T
I 4
/*
D 13
 * Copyright (c) 1987 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 8
I 8
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
E 6
 */

E 4
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
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
D 7
#endif LIBC_SCCS and not lint
E 7
I 7
#endif /* LIBC_SCCS and not lint */
E 7
E 3
E 2

I 4
#include <sys/types.h>
D 11
#include <sys/file.h>
E 11
I 5
#include <sys/stat.h>
I 11
#include <fcntl.h>
E 11
#include <errno.h>
E 5
#include <stdio.h>
I 12
#include <ctype.h>
E 12
D 11
#include <ctype.h>
E 11
I 11

static int _gettemp();
E 11

D 9
#define	YES	1
#define	NO	0

mkstemp(as)
	char	*as;
E 9
I 9
mkstemp(path)
	char *path;
E 9
{
D 9
	int	fd;
E 9
I 9
	int fd;
E 9

D 9
	return (_gettemp(as, &fd) ? fd : -1);
E 9
I 9
	return (_gettemp(path, &fd) ? fd : -1);
E 9
}

E 4
char *
D 9
mktemp(as)
D 4
char *as;
E 4
I 4
	char	*as;
E 9
I 9
mktemp(path)
	char *path;
E 9
E 4
{
D 4
	register char *s;
	register unsigned pid;
	register i;
E 4
I 4
D 9
	return(_gettemp(as, (int *)NULL) ? as : (char *)NULL);
E 9
I 9
	return(_gettemp(path, (int *)NULL) ? path : (char *)NULL);
E 9
}
E 4

I 4
static
D 9
_gettemp(as, doopen)
	char	*as;
	register int	*doopen;
E 9
I 9
_gettemp(path, doopen)
	char *path;
	register int *doopen;
E 9
{
I 5
D 9
	extern int	errno;
E 5
	register char	*start, *trv;
I 5
	struct stat	sbuf;
E 5
	u_int	pid;
E 9
I 9
	extern int errno;
	register char *start, *trv;
	struct stat sbuf;
	u_int pid;
E 9
D 5
	char	savech;
E 5

E 4
	pid = getpid();
D 4
	s = as;
	while (*s++)
		;
	s--;
	while (*--s == 'X') {
		*s = (pid%10) + '0';
E 4
I 4
D 9

	/* extra X's get set to 0's */
D 5
	for (trv = as;*trv;++trv);
E 5
I 5
	for (trv = as; *trv; ++trv);
E 9
I 9
	for (trv = path; *trv; ++trv);		/* extra X's get set to 0's */
E 9
E 5
	while (*--trv == 'X') {
		*trv = (pid % 10) + '0';
E 4
		pid /= 10;
	}
D 4
	s++;
	i = 'a';
	while (access(as, 0) != -1) {
		if (i=='z')
			return("/");
		*s = i++;
E 4
I 4

	/*
D 9
	 * check for write permission on target directory; if you have
	 * six X's and you can't write the directory, this will run for
	 * a *very* long time.
E 9
I 9
	 * check the target directory; if you have six X's and it
	 * doesn't exist this runs for a *very* long time.
E 9
	 */
D 5
	for (start = ++trv;trv > as && *trv != '/';--trv);
E 5
I 5
D 9
	for (start = ++trv; trv > as && *trv != '/'; --trv);
E 5
	if (*trv == '/') {
D 5
		savech = *++trv;
E 5
		*trv = '\0';
D 5
		if (access(as, W_OK))
E 5
I 5
		if (stat(as, &sbuf) || !(sbuf.st_mode & S_IFDIR))
E 5
			return(NO);
D 5
		*trv = savech;
E 5
I 5
		*trv = '/';
E 9
I 9
	for (start = trv + 1;; --trv) {
		if (trv <= path)
			break;
		if (*trv == '/') {
			*trv = '\0';
			if (stat(path, &sbuf))
				return(0);
			if (!S_ISDIR(sbuf.st_mode)) {
				errno = ENOTDIR;
				return(0);
			}
			*trv = '/';
			break;
		}
E 9
E 5
E 4
	}
D 4
	return(as);
E 4
I 4
D 5
	else if (access(".", W_OK))
E 5
I 5
D 9
	else if (stat(".", &sbuf) == -1)
E 5
		return(NO);
E 9

	for (;;) {
D 5
		if (doopen
		    && (*doopen = open(as, O_CREAT|O_EXCL|O_RDWR, 0600)) != -1
		    || access(as, F_OK))
E 5
I 5
		if (doopen) {
D 9
		    if ((*doopen = open(as, O_CREAT|O_EXCL|O_RDWR, 0600)) >= 0)
E 5
			return(YES);
I 5
		    if (errno != EEXIST)
			return(NO);
E 9
I 9
			if ((*doopen =
			    open(path, O_CREAT|O_EXCL|O_RDWR, 0600)) >= 0)
				return(1);
			if (errno != EEXIST)
				return(0);
E 9
		}
D 9
		else if (stat(as, &sbuf))
			return(errno == ENOENT ? YES : NO);
E 9
I 9
		else if (stat(path, &sbuf))
			return(errno == ENOENT ? 1 : 0);
E 9

E 5
		/* tricky little algorithm for backward compatibility */
		for (trv = start;;) {
			if (!*trv)
D 9
				return(NO);
E 9
I 9
				return(0);
E 9
			if (*trv == 'z')
				*trv++ = 'a';
			else {
				if (isdigit(*trv))
					*trv = 'a';
				else
					++*trv;
				break;
			}
		}
	}
	/*NOTREACHED*/
E 4
}
E 1
