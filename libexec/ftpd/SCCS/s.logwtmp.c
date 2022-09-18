h22331
s 00002/00002/00047
d D 8.1 93/06/04 18:48:37 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00045
d D 5.8 92/06/27 16:56:18 andrew 8 7
c (bostic) changes for prototyping
e
s 00003/00001/00044
d D 5.7 91/02/25 16:46:24 bostic 7 6
c ANSI fixes, struct direct -> struct dirent, rename glob() -> ftpglob()
e
s 00001/00011/00044
d D 5.6 90/06/01 15:52:41 bostic 6 5
c new copyright notice
e
s 00001/00003/00054
d D 5.5 89/04/02 12:46:03 bostic 5 4
c grab wtmp path from utmp.h
e
s 00001/00002/00056
d D 5.4 89/02/14 21:47:09 rick 4 3
c correct spelling of merchantAbility
e
s 00008/00003/00050
d D 5.3 88/12/07 11:35:49 karels 3 2
c fix user/pass to reset all on failure (*don't* leave failed anonymous
c login as root!), limit login attempts, sleep after failures to slow down
c guessing, correct telnet option processing, various cleanups
e
s 00003/00003/00050
d D 5.2 88/09/22 15:05:51 bostic 2 1
c change to preserve wtmp file descriptor so can logout after chroot
e
s 00053/00000/00000
d D 5.1 88/09/22 15:05:05 bostic 1 0
c version 5.2 of logwtmp from the library
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 6
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
D 4
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 4
 *
D 4
 * static char sccsid[] = "@(#)logwtmp.c	5.2 (Berkeley) 9/20/88";
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 7
#include <sys/file.h>
E 7
#include <sys/time.h>
#include <sys/stat.h>
I 8

E 8
I 7
#include <fcntl.h>
E 7
#include <utmp.h>
I 7
#include <unistd.h>
I 8
#include <stdio.h>
E 8
#include <string.h>
I 8
#include "extern.h"
E 8
E 7

D 5
#define	WTMPFILE	"/usr/adm/wtmp"

E 5
I 2
D 3
static int fd;
E 3
I 3
static int fd = -1;
E 3

I 3
/*
 * Modified version of logwtmp that holds wtmp file open
 * after first call, for use with ftp (which may chroot
 * after login, but before logout).
 */
I 8
void
E 8
E 3
E 2
logwtmp(line, name, host)
	char *line, *name, *host;
{
	struct utmp ut;
	struct stat buf;
D 2
	int fd;
E 2
D 8
	time_t time();
	char *strncpy();
E 8

D 2
	if ((fd = open(WTMPFILE, O_WRONLY|O_APPEND, 0)) < 0)
E 2
I 2
D 3
	if (!fd && (fd = open(WTMPFILE, O_WRONLY|O_APPEND, 0)) < 0)
E 3
I 3
D 5
	if (fd < 0 && (fd = open(WTMPFILE, O_WRONLY|O_APPEND, 0)) < 0)
E 5
I 5
	if (fd < 0 && (fd = open(_PATH_WTMP, O_WRONLY|O_APPEND, 0)) < 0)
E 5
E 3
E 2
		return;
D 3
	if (!fstat(fd, &buf)) {
E 3
I 3
	if (fstat(fd, &buf) == 0) {
E 3
		(void)strncpy(ut.ut_line, line, sizeof(ut.ut_line));
		(void)strncpy(ut.ut_name, name, sizeof(ut.ut_name));
		(void)strncpy(ut.ut_host, host, sizeof(ut.ut_host));
		(void)time(&ut.ut_time);
		if (write(fd, (char *)&ut, sizeof(struct utmp)) !=
		    sizeof(struct utmp))
			(void)ftruncate(fd, buf.st_size);
	}
D 2
	(void)close(fd);
E 2
}
E 1
