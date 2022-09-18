h61290
s 00002/00002/00058
d D 8.1 93/06/06 14:56:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00002/00051
d D 4.3 91/04/17 18:00:37 bostic 3 2
c new copyright; att/bsd/shared
e
s 00007/00004/00046
d D 4.2 83/04/25 23:59:00 mckusick 2 1
c 
e
s 00050/00000/00000
d D 4.1 83/02/24 12:56:00 mckusick 1 0
c date and time created 83/02/24 12:56:00 by mckusick
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "stdio.h"
#include "signal.h"
#include "lrnref.h"

static int oldout;
static char tee[50];

maktee()
{
	int fpip[2], in, out;

	if (tee[0] == 0)
D 2
		sprintf(tee, "%s/tee", direct);
E 2
I 2
		sprintf(tee, "%s/bin/lrntee", direct);
E 2
	pipe(fpip);
	in = fpip[0];
	out= fpip[1];
	if (fork() == 0) {
		signal(SIGINT, SIG_IGN);
		close(0);
		close(out);
		dup(in);
		close(in);
		execl (tee, "lrntee", 0);
D 2
		fprintf(stderr, "Tee exec failed\n");
E 2
I 2
		perror(tee);
		fprintf(stderr, "Maktee:  lrntee exec failed\n");
E 2
		exit(1);
	}
	close(in);
	fflush(stdout);
	oldout = dup(1);
	close(1);
D 2
	if (dup(out) != 1)
		fprintf(stderr, "Error making tee for copyout\n");
E 2
I 2
	if (dup(out) != 1) {
		perror("dup");
		fprintf(stderr, "Maktee:  error making tee for copyout\n");
	}
E 2
	close(out);
	return(1);
}

untee()
{
	int x;

	fflush(stdout);
	close(1);
	dup(oldout);
	close(oldout);
	wait(&x);
}
E 1
