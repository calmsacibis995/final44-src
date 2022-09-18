h15126
s 00005/00005/00044
d D 8.1 93/06/06 14:12:03 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00005/00046
d D 5.1 91/06/06 19:35:37 bostic 9 8
c minor cleanups, no fixes
e
s 00000/00007/00051
d D 4.8 91/06/06 19:30:00 bostic 8 7
c no reason to keep file/directories open anymore
e
s 00035/00018/00023
d D 4.7 91/04/19 15:49:03 bostic 7 6
c remove last vestiges of AT&T code; fix for ANSI; Berkeley copyright
e
s 00001/00001/00040
d D 4.6 91/03/02 18:07:56 bostic 6 5
c ANSI
e
s 00005/00011/00036
d D 4.5 90/06/29 19:09:30 karels 5 4
c use daemon() call
e
s 00001/00010/00046
d D 4.4 89/05/11 14:34:21 bostic 4 3
c file reorg, pathnames.h, paths.h
e
s 00031/00018/00022
d D 4.3 87/03/28 11:15:24 bostic 3 2
c just hacking
e
s 00003/00000/00037
d D 4.2 80/10/16 01:07:31 bill 2 1
c open more directories
e
s 00037/00000/00000
d D 4.1 80/10/01 17:29:14 bill 1 0
c date and time created 80/10/01 17:29:14 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
D 7
/*
I 3
D 5
 * Copyright (c) 1987 Regents of the University of California.
E 5
I 5
 * Copyright (c) 1987, 1990 Regents of the University of California.
E 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 10
 * Copyright (c) 1987, 1990 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1987, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
E 7
 */

#ifndef lint
I 7
D 10
char copyright[] =
"%Z% Copyright (c) 1987, 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1987, 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
#endif /* not lint */

#ifndef lint
E 7
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
#endif /* not lint */
E 7

D 7
/*
E 3
 * Update the file system every 30 seconds.
 * For cache benefit, open certain system directories.
 */

E 7
D 3
#include <signal.h>
E 3
I 3
#include <sys/time.h>
D 7
#include <sys/file.h>
#include <sys/signal.h>
E 7
I 7
#include <signal.h>
D 8
#include <fcntl.h>
E 8
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
E 7
D 5
#include <syslog.h>
#include <stdio.h>
E 5
E 3
D 4

char *fillst[] = {
	"/bin",
I 2
	"/lib",
E 2
	"/usr",
	"/usr/bin",
I 2
	"/usr/lib",
	"/usr/ucb",
E 2
	0,
};
E 4
I 4
D 8
#include "pathnames.h"
E 8
E 4

main()
{
D 3
	char **f;
E 3
I 3
D 5
	struct itimerval	value;
	register char	**f;
	extern int	sync();
E 5
I 5
	struct itimerval value;
D 7
	register char **f;
D 6
	extern int sync();
E 6
I 6
	void sync();
E 7
I 7
	void mysync();
E 7
E 6
E 5
E 3

D 3
	if(fork())
E 3
I 3
D 5
	if (fork())
E 3
		exit(0);
D 3
	close(0);
	close(1);
	close(2);
	for(f = fillst; *f; f++)
		open(*f, 0);
	dosync();
	for(;;)
E 3
I 3
	(void)close(0);
	(void)close(1);
	(void)close(2);
E 5
I 5
	daemon(0, 0);
E 5
D 7
	for (f = fillst; *f; f++)
		(void)open(*f, O_RDONLY, 0);
	(void)signal(SIGALRM, sync);
E 7
I 7
D 8

	(void)open(_PATH_BIN, O_RDONLY, 0);
	(void)open(_PATH_USR, O_RDONLY, 0);
	(void)open(_PATH_USRBIN, O_RDONLY, 0);
	(void)open(_PATH_USRLIB, O_RDONLY, 0);
E 8

	(void)signal(SIGALRM, mysync);

E 7
	value.it_interval.tv_sec = 30;
	value.it_interval.tv_usec = 0;
	value.it_value = value.it_interval;
D 7
	if (setitimer(ITIMER_REAL, &value, (struct itimerval *)NULL)) {
E 7
I 7
	if (setitimer(ITIMER_REAL, &value, NULL)) {
E 7
		perror("update: setitimer");
		exit(1);
	}
	for (;;)
E 3
D 9
		pause();
D 3
}

dosync()
{
	sync();
	signal(SIGALRM, dosync);
	alarm(30);
E 3
I 3
	/*NOTREACHED*/
E 9
I 9
		sigpause(sigblock(0L));
	/* NOTREACHED */
E 9
I 7
}

D 9
/* VARARGS */
E 9
void
D 9
mysync(i)
	int i;
E 9
I 9
mysync()
E 9
{
	(void)sync();
E 7
E 3
}
E 1
