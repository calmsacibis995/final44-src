h25900
s 00002/00002/00035
d D 8.1 93/06/06 22:13:21 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00001/00029
d D 5.3 91/04/24 17:36:55 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00027
d D 5.2 85/06/20 10:03:59 bloom 2 1
c fixes from rick adams
e
s 00028/00000/00000
d D 5.1 85/03/22 09:03:14 ralph 1 0
c date and time created 85/03/22 09:03:14 by ralph
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

#ifndef BSD4_2
#include <stdio.h>
I 2

E 2
/*
 * make a directory. Also make sure that the directory is owned
 * by the right userid
 */
mkdir(path, mode)
char *path;
int mode;
{
	int pid, status, w;

	if (pid=fork()) {
		while ((w = wait(&status)) != pid && w != -1)
			;
		(void) chmod(path, mode);
	} else {
D 2
		(void) umask(mode);
E 2
I 2
		(void) umask(~mode);
E 2
		(void) execlp("mkdir", "mkdir", path, (char *)NULL);
		perror(path);
		_exit(1);
	}
I 2
	return status;
E 2
}
#endif !BSD4_2
E 1
