h09300
s 00002/00002/00044
d D 8.1 93/06/04 17:31:03 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00007/00036
d D 5.6 92/07/01 10:21:46 bostic 6 5
c fix seek calls for quads
e
s 00001/00011/00042
d D 5.5 90/06/01 15:49:03 bostic 5 4
c new copyright notice
e
s 00012/00014/00041
d D 5.4 89/09/19 16:28:13 bostic 4 3
c can't use fwrite, multiple writers will overwrite entries
e
s 00001/00003/00054
d D 5.3 89/04/18 12:06:03 bostic 3 2
c use defines in /usr/include/utmp.h
e
s 00004/00002/00053
d D 5.2 89/02/17 15:29:28 bostic 2 1
c make exit values consistent
e
s 00055/00000/00000
d D 5.1 88/08/31 23:01:37 bostic 1 0
c date and time created 88/08/31 23:01:37 by bostic
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
D 6
#include <sys/file.h>
E 6
#include <sys/time.h>
I 6

#include <fcntl.h>
E 6
#include <utmp.h>
I 6
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
E 6
D 4
#include <stdio.h>
E 4

D 3
#define	UTMPFILE	"/etc/utmp"

E 3
I 2
D 4
/* 0 on failure, 1 on success */
E 4
I 4
typedef struct utmp UTMP;
E 4

I 6
int
E 6
E 2
logout(line)
	register char *line;
{
D 4
	register FILE *fp;
	struct utmp ut;
E 4
I 4
	register int fd;
	UTMP ut;
E 4
	int rval;
I 4
D 6
	off_t lseek();
E 4
	time_t time();
E 6

D 3
	if (!(fp = fopen(UTMPFILE, "r+")))
E 3
I 3
D 4
	if (!(fp = fopen(_PATH_UTMP, "r+")))
E 4
I 4
D 6
	if ((fd = open(_PATH_UTMP, O_RDWR)) < 0)
E 6
I 6
	if ((fd = open(_PATH_UTMP, O_RDWR, 0)) < 0)
E 6
E 4
E 3
		return(0);
D 2
	rval = 1;
E 2
I 2
	rval = 0;
E 2
D 4
	while (fread((char *)&ut, sizeof(struct utmp), 1, fp) == 1) {
		if (!ut.ut_name[0] ||
		    strncmp(ut.ut_line, line, sizeof(ut.ut_line)))
E 4
I 4
D 6
	while (read(fd, (char *)&ut, sizeof(UTMP)) == sizeof(UTMP)) {
E 6
I 6
	while (read(fd, &ut, sizeof(UTMP)) == sizeof(UTMP)) {
E 6
		if (!ut.ut_name[0] || strncmp(ut.ut_line, line, UT_LINESIZE))
E 4
			continue;
D 4
		bzero(ut.ut_name, sizeof(ut.ut_name));
		bzero(ut.ut_host, sizeof(ut.ut_host));
E 4
I 4
		bzero(ut.ut_name, UT_NAMESIZE);
		bzero(ut.ut_host, UT_HOSTSIZE);
E 4
		(void)time(&ut.ut_time);
D 4
		(void)fseek(fp, (long)-sizeof(struct utmp), L_INCR);
		(void)fwrite((char *)&ut, sizeof(struct utmp), 1, fp);
		(void)fseek(fp, (long)0, L_INCR);
E 4
I 4
D 6
		(void)lseek(fd, -(long)sizeof(UTMP), L_INCR);
		(void)write(fd, (char *)&ut, sizeof(UTMP));
E 6
I 6
		(void)lseek(fd, -(off_t)sizeof(UTMP), L_INCR);
		(void)write(fd, &ut, sizeof(UTMP));
E 6
E 4
D 2
		rval = 0;
E 2
I 2
		rval = 1;
E 2
	}
D 4
	(void)fclose(fp);
E 4
I 4
	(void)close(fd);
E 4
	return(rval);
}
E 1
