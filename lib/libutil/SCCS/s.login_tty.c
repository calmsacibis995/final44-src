h23378
s 00002/00002/00025
d D 8.1 93/06/04 17:30:57 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00005/00022
d D 1.2 90/06/21 11:49:35 marc 3 1
c return failure if TIOCSCTTY fails. work for any fd.
e
s 00004/00005/00022
d R 1.2 90/06/21 11:46:47 marc 2 1
c check return value of TIOCSCTTY.  dup2 closes open descriptors.
e
s 00027/00000/00000
d D 1.1 90/06/15 15:01:20 marc 1 0
c date and time created 90/06/15 15:01:20 by marc
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/ioctl.h>

login_tty(fd)
	int fd;
{
	(void) setsid();
D 3
	(void) ioctl(fd, TIOCSCTTY, (char *)NULL);
	(void) close(0); 
	(void) close(1); 
	(void) close(2);
E 3
I 3
	if (ioctl(fd, TIOCSCTTY, (char *)NULL) == -1)
		return (-1);
E 3
	(void) dup2(fd, 0);
	(void) dup2(fd, 1);
	(void) dup2(fd, 2);
D 3
	(void) close(fd);
E 3
I 3
	if (fd > 2)
		(void) close(fd);
	return (0);
E 3
}
E 1
