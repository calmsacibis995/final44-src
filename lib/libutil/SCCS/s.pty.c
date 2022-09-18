h62264
s 00008/00007/00094
d D 8.3 94/05/16 17:12:09 bostic 12 11
c prettiness police
e
s 00001/00001/00100
d D 8.2 94/05/16 17:07:50 bostic 11 10
c line[5] wasn't getting reset if the first open wasn't successful
e
s 00002/00002/00099
d D 8.1 93/06/04 17:31:15 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00099
d D 5.6 91/05/10 12:43:10 marc 9 8
c broken by doing fchown a year ago...
e
s 00001/00001/00100
d D 5.5 91/03/07 15:22:54 marc 8 7
c only stop looking when getting an ENOENT (fell past number of configured ptys)
e
s 00001/00001/00100
d D 5.4 91/03/06 16:33:59 karels 7 6
c fix winsize (extra indirection)
e
s 00001/00001/00100
d D 5.3 91/03/03 21:16:18 bostic 6 5
c fix aggregate initialization for pcc
e
s 00009/00004/00092
d D 5.2 91/02/27 17:07:08 bostic 5 3
c ANSI fixes
e
s 00004/00003/00093
d R 5.2 91/02/24 16:15:20 bostic 4 3
c Add include files to get prototype declarations, and fix bugs found.
e
s 00006/00006/00090
d D 5.1 90/10/14 12:41:22 bostic 3 2
c don't translate the name again, use symbolic permissions
e
s 00055/00005/00041
d D 1.2 90/06/29 00:14:37 marc 2 1
c new interface
e
s 00046/00000/00000
d D 1.1 90/06/07 16:01:57 marc 1 0
c date and time created 90/06/07 16:01:57 by marc
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
D 12
 * Copyright (c) 1990, 1993
E 12
I 12
 * Copyright (c) 1990, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 5
D 12
#include <sys/cdefs.h>
E 12
E 5
I 3
#include <sys/types.h>
D 12
#include <sys/stat.h>
E 12
E 3
D 5
#include <sys/file.h>
E 5
I 2
#include <sys/ioctl.h>
I 3
D 5
#include <sys/errno.h>
E 5
I 5
D 12
#include <fcntl.h>
E 5
E 3
#include <termios.h>
E 12
I 12
#include <sys/stat.h>

E 12
I 5
#include <errno.h>
D 12
#include <unistd.h>
E 12
I 12
#include <fcntl.h>
#include <grp.h>
E 12
#include <stdio.h>
I 12
#include <stdlib.h>
E 12
#include <string.h>
E 5
D 12
#include <grp.h>
E 12
I 12
#include <termios.h>
#include <unistd.h>
E 12
E 2
D 3
#include <errno.h>
E 3

D 2
openpty(amaster, aslave, name, flag)
E 2
I 2
openpty(amaster, aslave, name, termp, winp)
E 2
	int *amaster, *aslave;
	char *name;
D 2
	int flag;
E 2
I 2
	struct termios *termp;
	struct winsize *winp;
E 2
{
I 6
	static char line[] = "/dev/ptyXX";
E 6
D 5
	register char *line = "/dev/ptyXX", *cp1, *cp2;
E 5
I 5
	register const char *cp1, *cp2;
E 5
D 2
	register master, slave;
E 2
I 2
D 3
	register master, slave, ruid, ttygid;
E 3
I 3
	register int master, slave, ttygid;
E 3
	struct group *gr;
I 5
D 6
	char line[] = "/dev/ptyXX";
E 6
E 5
E 2
D 3
	extern errno;
E 3

I 2
	if ((gr = getgrnam("tty")) != NULL)
		ttygid = gr->gr_gid;
	else
		ttygid = -1;
D 3
	ruid = getuid();
E 3

E 2
	for (cp1 = "pqrs"; *cp1; cp1++) {
		line[8] = *cp1;
		for (cp2 = "0123456789abcdef"; *cp2; cp2++) {
I 11
			line[5] = 'p';
E 11
			line[9] = *cp2;
			if ((master = open(line, O_RDWR, 0)) == -1) {
D 8
				if (errno != EIO)
E 8
I 8
				if (errno == ENOENT)
E 8
D 2
					return (-1);
E 2
I 2
					return (-1);	/* out of ptys */
E 2
			} else {
				line[5] = 't';
I 2
D 3
				(void) chown(line, ruid, ttygid);
				(void) chmod(line, 0620);
E 3
I 3
D 9
				(void) fchown(master, getuid(), ttygid);
				(void) fchmod(master, S_IRUSR|S_IWUSR|S_IWGRP);
E 9
I 9
				(void) chown(line, getuid(), ttygid);
				(void) chmod(line, S_IRUSR|S_IWUSR|S_IWGRP);
E 9
E 3
				(void) revoke(line);
E 2
				if ((slave = open(line, O_RDWR, 0)) != -1) {
					*amaster = master;
					*aslave = slave;
					if (name)
						strcpy(name, line);
I 2
					if (termp)
						(void) tcsetattr(slave, 
D 5
							TCSAFLUSH, &termp);
E 5
I 5
							TCSAFLUSH, termp);
E 5
					if (winp)
						(void) ioctl(slave, TIOCSWINSZ, 
D 7
							(char *)&winp);
E 7
I 7
							(char *)winp);
E 7
E 2
					return (0);
				}
D 2
				close(master);
E 2
I 2
				(void) close(master);
E 2
D 11
				line[5] = 'p';
E 11
			}
		}
	}
I 2
	errno = ENOENT;	/* out of ptys */
E 2
	return (-1);
I 2
}

forkpty(amaster, name, termp, winp)
	int *amaster;
	char *name;
	struct termios *termp;
	struct winsize *winp;
{
	int master, slave, pid;

	if (openpty(&master, &slave, name, termp, winp) == -1)
		return (-1);
	switch (pid = fork()) {
	case -1:
		return (-1);
	case 0:
		/* 
		 * child
		 */
		(void) close(master);
		login_tty(slave);
		return (0);
	}
	/*
	 * parent
	 */
	*amaster = master;
	(void) close(slave);
	return (pid);
E 2
}
E 1
