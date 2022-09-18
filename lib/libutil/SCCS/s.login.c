h16758
s 00002/00002/00035
d D 8.1 93/06/04 17:30:52 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00005/00030
d D 5.5 92/07/01 10:21:45 bostic 5 4
c fix seek calls for quads
e
s 00001/00011/00034
d D 5.4 90/06/01 15:49:00 bostic 4 3
c new copyright notice
e
s 00001/00001/00044
d D 5.3 90/03/29 11:37:44 mckusick 3 2
c create utmp file if it does not exist (from shanzer@ritcsh.rit.edu)
e
s 00002/00005/00043
d D 5.2 89/04/18 12:06:02 bostic 2 1
c use defines in /usr/include/utmp.h
e
s 00048/00000/00000
d D 5.1 88/09/27 22:30:57 bostic 1 0
c date and time created 88/09/27 22:30:57 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>
D 5
#include <sys/file.h>
E 5
I 5

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
E 5
#include <utmp.h>
#include <stdio.h>

D 2
#define	UTMPFILE	"/etc/utmp"
#define	WTMPFILE	"/usr/adm/wtmp"

E 2
void
login(ut)
	struct utmp *ut;
{
	register int fd;
	int tty;
D 5
	off_t lseek();
E 5

	tty = ttyslot();
D 2
	if (tty > 0 && (fd = open(UTMPFILE, O_WRONLY, 0)) >= 0) {
E 2
I 2
D 3
	if (tty > 0 && (fd = open(_PATH_UTMP, O_WRONLY, 0)) >= 0) {
E 3
I 3
	if (tty > 0 && (fd = open(_PATH_UTMP, O_WRONLY|O_CREAT, 0644)) >= 0) {
E 3
E 2
D 5
		(void)lseek(fd, (long)(tty * sizeof(struct utmp)), L_SET);
		(void)write(fd, (char *)ut, sizeof(struct utmp));
E 5
I 5
		(void)lseek(fd, (off_t)(tty * sizeof(struct utmp)), L_SET);
		(void)write(fd, ut, sizeof(struct utmp));
E 5
		(void)close(fd);
	}
D 2
	if ((fd = open(WTMPFILE, O_WRONLY|O_APPEND, 0)) >= 0) {
E 2
I 2
	if ((fd = open(_PATH_WTMP, O_WRONLY|O_APPEND, 0)) >= 0) {
E 2
D 5
		(void)write(fd, (char *)ut, sizeof(struct utmp));
E 5
I 5
		(void)write(fd, ut, sizeof(struct utmp));
E 5
		(void)close(fd);
	}
}
E 1
