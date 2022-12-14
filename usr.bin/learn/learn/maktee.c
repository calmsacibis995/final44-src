/*-
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 */

#ifndef lint
static char sccsid[] = "@(#)maktee.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#include "stdio.h"
#include "signal.h"
#include "lrnref.h"

static int oldout;
static char tee[50];

maktee()
{
	int fpip[2], in, out;

	if (tee[0] == 0)
		sprintf(tee, "%s/bin/lrntee", direct);
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
		perror(tee);
		fprintf(stderr, "Maktee:  lrntee exec failed\n");
		exit(1);
	}
	close(in);
	fflush(stdout);
	oldout = dup(1);
	close(1);
	if (dup(out) != 1) {
		perror("dup");
		fprintf(stderr, "Maktee:  error making tee for copyout\n");
	}
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
