h29427
s 00002/00002/00043
d D 8.1 93/06/04 12:01:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00022/00017/00023
d D 5.5 93/04/27 18:46:14 bostic 5 4
c move daemon(3) to libc rom libutil
e
s 00001/00000/00039
d D 5.4 91/07/31 15:28:23 bostic 4 3
c return 0 on success
e
s 00007/00005/00032
d D 5.3 90/12/28 16:21:05 bostic 3 2
c use defined constants
e
s 00015/00009/00022
d D 5.2 90/06/29 00:14:52 marc 2 1
c new interface
e
s 00031/00000/00000
d D 5.1 90/06/15 14:47:14 marc 1 0
c date and time created 90/06/15 14:47:14 by marc
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

D 3
#include <sys/file.h>
E 3
I 3
D 5
#include <sys/fcntl.h>
#include <unistd.h>
E 5
I 5
#include <fcntl.h>
E 5
#include <paths.h>
I 5
#include <unistd.h>
E 5
E 3

I 5
int
E 5
D 2
daemon()
E 2
I 2
daemon(nochdir, noclose)
	int nochdir, noclose;
E 2
{
D 5
	int cpid;
E 5
I 5
	int fd;
E 5

D 5
	if ((cpid = fork()) == -1)
E 5
I 5
	switch (fork()) {
	case -1:
E 5
		return (-1);
D 5
	if (cpid)
		exit(0);
D 2

E 2
	(void) setsid();
E 5
I 5
	case 0:
		break;
	default:
		_exit(0);
	}

	if (setsid() == -1)
		return (-1);

E 5
D 2
	(void) chdir("/");
	(void) close(0);
	(void) close(1);
	(void) close(2);
	(void) open("/", O_RDONLY, 0);
	(void) dup2(0, 1);
	(void) dup2(0, 2);
E 2
I 2
	if (!nochdir)
D 5
		(void) chdir("/");
	if (!noclose) {
D 3
		int devnull = open("/dev/null", O_RDWR, 0);
E 3
I 3
		int devnull = open(_PATH_DEVNULL, O_RDWR, 0);
E 5
I 5
		(void)chdir("/");
E 5
E 3

D 5
		if (devnull != -1) {
D 3
			(void) dup2(devnull, 0);
			(void) dup2(devnull, 1);
			(void) dup2(devnull, 2);
E 3
I 3
			(void) dup2(devnull, STDIN_FILENO);
			(void) dup2(devnull, STDOUT_FILENO);
			(void) dup2(devnull, STDERR_FILENO);
E 3
			if (devnull > 2)
				(void) close(devnull);
		}
E 5
I 5
	if (!noclose && (fd = open(_PATH_DEVNULL, O_RDWR, 0)) != -1) {
		(void)dup2(fd, STDIN_FILENO);
		(void)dup2(fd, STDOUT_FILENO);
		(void)dup2(fd, STDERR_FILENO);
		if (fd > 2)
			(void)close (fd);
E 5
	}
I 4
	return (0);
E 4
E 2
}
E 1
