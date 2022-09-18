h49706
s 00002/00002/00039
d D 8.1 93/06/04 17:31:09 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00039
d D 5.6 93/05/19 14:47:15 bostic 6 5
c include unistd.h for truncate prototype
e
s 00001/00011/00038
d D 5.5 90/06/01 15:49:07 bostic 5 4
c new copyright notice
e
s 00006/00006/00043
d D 5.4 90/05/08 14:47:37 karels 4 3
c KNF
e
s 00001/00003/00048
d D 5.3 89/04/02 12:45:20 bostic 3 2
c use utmp.h for WTMPFILE define
e
s 00013/00007/00038
d D 5.2 88/09/20 14:19:34 bostic 2 1
c take name and host as args, too, fix to truncate on write failure
e
s 00045/00000/00000
d D 5.1 88/08/31 23:01:29 bostic 1 0
c date and time created 88/08/31 23:01:29 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
#include <sys/file.h>
#include <sys/time.h>
I 2
#include <sys/stat.h>
I 6

#include <unistd.h>
E 6
E 2
#include <utmp.h>

D 3
#define	WTMPFILE	"/usr/adm/wtmp"

E 3
D 2
logwtmp(line)
	char *line;
E 2
I 2
logwtmp(line, name, host)
	char *line, *name, *host;
E 2
{
	struct utmp ut;
I 2
	struct stat buf;
E 2
	int fd;
	time_t time();
	char *strncpy();

D 3
	if ((fd = open(WTMPFILE, O_WRONLY|O_APPEND, 0)) < 0)
E 3
I 3
	if ((fd = open(_PATH_WTMP, O_WRONLY|O_APPEND, 0)) < 0)
E 3
		return;
D 2
	bzero(ut.ut_name, sizeof(ut.ut_name));
	bzero(ut.ut_host, sizeof(ut.ut_host));
	(void)strncpy(ut.ut_line, line, sizeof(ut.ut_line));
	(void)time(&ut.ut_time);
	(void)write(fd, (char *)&ut, sizeof(struct utmp));
E 2
I 2
D 4
	if (!fstat(fd, &buf)) {
		(void)strncpy(ut.ut_line, line, sizeof(ut.ut_line));
		(void)strncpy(ut.ut_name, name, sizeof(ut.ut_name));
		(void)strncpy(ut.ut_host, host, sizeof(ut.ut_host));
		(void)time(&ut.ut_time);
E 4
I 4
	if (fstat(fd, &buf) == 0) {
		(void) strncpy(ut.ut_line, line, sizeof(ut.ut_line));
		(void) strncpy(ut.ut_name, name, sizeof(ut.ut_name));
		(void) strncpy(ut.ut_host, host, sizeof(ut.ut_host));
		(void) time(&ut.ut_time);
E 4
		if (write(fd, (char *)&ut, sizeof(struct utmp)) !=
		    sizeof(struct utmp))
			(void) ftruncate(fd, buf.st_size);
	}
E 2
D 4
	(void)close(fd);
E 4
I 4
	(void) close(fd);
E 4
}
E 1
