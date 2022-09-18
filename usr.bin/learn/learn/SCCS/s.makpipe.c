h50494
s 00002/00002/00033
d D 8.1 93/06/06 14:56:37 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00026
d D 4.5 91/04/17 18:00:36 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00004/00025
d D 4.4 89/05/10 22:47:11 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00001/00001/00028
d D 4.3 86/05/15 17:58:38 bloom 3 2
c updates from John Kunze
e
s 00007/00002/00022
d D 4.2 83/04/25 23:58:58 mckusick 2 1
c 
e
s 00024/00000/00000
d D 4.1 83/02/24 12:55:57 mckusick 1 0
c date and time created 83/02/24 12:55:57 by mckusick
e
u
U
t
T
I 5
/*-
D 6
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 5
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

#include "stdio.h"
I 4
#include "pathnames.h"
E 4

makpipe()
{
	int f[2];

	pipe(f);
	if (fork()==0) {
		close(f[1]);
		close(0);
		dup(f[0]);
		close(f[0]);
I 2
D 3
#if vax
E 3
I 3
#if BSD4_2
E 3
E 2
D 4
		execl ("/bin/sh", "sh", "-i", 0);
D 2
		execl ("/usr/bin/sh", "sh", "-i", 0);
		write(2,"Exec error\n",11);
E 2
I 2
		execl ("/usr/ucb/bin/sh", "sh", "-i", 0);
E 4
I 4
		execl (_PATH_BSHELL, "sh", "-i", 0);
E 4
#else
D 4
		execlp("/bin/csh", "csh", "-if", 0);
		/*execl ("/usr/ucb/bin/csh", "csh", "-if", 0);*/
E 4
I 4
		execlp(_PATH_CSHELL, "csh", "-if", 0);
E 4
#endif
		write(2, "Exec error\n", 11);
E 2
	}
	close(f[0]);
	sleep(2);	/* so shell won't eat up too much input */
	return(f[1]);
}
E 1
