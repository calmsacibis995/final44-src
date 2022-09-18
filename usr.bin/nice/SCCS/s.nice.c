h14054
s 00004/00003/00064
d D 8.3 95/04/28 12:51:15 bostic 11 10
c nice dumps core w/ no args
c From: Chris Torek <torek@BSDI.COM>
e
s 00013/00025/00054
d D 8.2 94/04/16 06:47:31 bostic 10 9
c somewhere along the line I broke the "nice --3" syntax
e
s 00005/00005/00074
d D 8.1 93/06/06 15:46:10 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00005/00069
d D 5.6 93/02/10 22:47:54 bostic 8 7
c ANSI C prototypes
e
s 00002/00000/00072
d D 5.5 92/06/18 12:16:55 bostic 7 6
c resource.h needs types.h now
e
s 00001/00011/00071
d D 5.4 90/06/01 17:28:02 bostic 6 5
c new copyright notice
e
s 00058/00020/00024
d D 5.3 89/05/20 12:44:31 bostic 5 4
c from scratch, add Berkeley specific copyright
e
s 00002/00001/00042
d D 5.2 86/01/12 02:04:42 lepreau 4 3
c nice is relative
e
s 00014/00002/00029
d D 5.1 85/04/30 15:05:02 dist 3 2
c Add copyright
e
s 00015/00011/00016
d D 4.2 83/05/22 18:16:13 sam 2 1
c replace nice with setpriority
e
s 00027/00000/00000
d D 4.1 80/10/01 17:27:39 bill 1 0
c date and time created 80/10/01 17:27:39 by bill
e
u
U
t
T
I 3
/*
D 5
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 10
 * Copyright (c) 1989, 1993
E 10
I 10
 * Copyright (c) 1989, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 6
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 5
 */

E 3
I 2
#ifndef lint
E 2
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
D 2
/* nice */
E 2
I 2
#endif
E 3
I 3
D 9
char copyright[] =
D 5
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 5
I 5
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 5
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
D 10
"%Z% Copyright (c) 1989, 1993\n\
E 10
I 10
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 10
	The Regents of the University of California.  All rights reserved.\n";
E 9
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5
E 3
E 2

I 7
#include <sys/types.h>
E 7
D 5
#include <stdio.h>

E 5
I 2
#include <sys/time.h>
#include <sys/resource.h>
I 7

E 7
I 5
D 8
#include <stdio.h>
E 8
#include <ctype.h>
I 10
#include <err.h>
E 10
I 8
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
E 8
E 5

I 5
#define	DEFNICE	10

D 8
/* ARGSUSED */
E 8
I 8
void usage __P((void));

int
E 8
E 5
E 2
main(argc, argv)
D 2
int argc;
char *argv[];
E 2
I 2
	int argc;
D 5
	char *argv[];
E 5
I 5
D 8
	char **argv;
E 8
I 8
	char *argv[];
E 8
E 5
E 2
{
D 5
	int nicarg = 10;
E 5
I 5
D 8
	extern int errno;
E 8
D 10
	int niceness;
E 10
I 10
	int niceness = DEFNICE;
E 10
D 8
	char *strerror();
E 8
E 5
D 2
	extern errno;
	extern char *sys_errlist[];
E 2

I 11
	if (argv[1] == NULL)
		usage();
E 11
D 2
	if(argc > 1 && argv[1][0] == '-') {
E 2
I 2
D 5
	if (argc > 1 && argv[1][0] == '-') {
E 2
		nicarg = atoi(&argv[1][1]);
D 2
		argc--;
		argv++;
E 2
I 2
		argc--, argv++;
E 2
	}
D 2
	if(argc < 2) {
E 2
I 2
	if (argc < 2) {
E 2
		fputs("usage: nice [ -n ] command\n", stderr);
E 5
I 5
D 10
	niceness = DEFNICE;
E 10
	if (argv[1][0] == '-')
D 10
		if (isdigit(argv[1][1])) {
E 10
I 10
		if (argv[1][1] == '-' || isdigit(argv[1][1])) {
E 10
			niceness = atoi(argv[1] + 1);
			++argv;
I 11
			if (argv[1] == NULL)
				usage();
E 11
D 10
		}
		else {
			(void)fprintf(stderr, "nice: illegal option -- %c\n",
			    argv[1][1]);
			usage();
		}
E 10
I 10
		} else
			errx(1, "illegal option -- %s", argv[1]);
E 10
D 11

D 10
	if (!argv[1])
E 10
I 10
	if (argv[1] == NULL)
E 10
		usage();
E 11

	errno = 0;
	niceness += getpriority(PRIO_PROCESS, 0);
D 10
	if (errno) {
		(void)fprintf(stderr, "nice: getpriority: %s\n",
		    strerror(errno));
E 5
		exit(1);
	}
D 2
	nice(nicarg);
E 2
I 2
D 4
	if (setpriority(PRIO_PROCESS, 0, nicarg) < 0) {
E 4
I 4
D 5
	if (setpriority(PRIO_PROCESS, 0, 
	    getpriority(PRIO_PROCESS, 0) + nicarg) < 0) {
E 4
		perror("setpriority");
E 5
I 5
	if (setpriority(PRIO_PROCESS, 0, niceness)) {
		(void)fprintf(stderr,
		    "nice: setpriority: %s\n", strerror(errno));
E 5
		exit(1);
	}
E 10
I 10
	if (errno)
		err(1, "getpriority");
	if (setpriority(PRIO_PROCESS, 0, niceness))
		err(1, "setpriority");
E 10
E 2
	execvp(argv[1], &argv[1]);
D 2
	fprintf(stderr, "%s: %s\n", sys_errlist[errno], argv[1]);
E 2
I 2
D 5
	perror(argv[1]);
E 5
I 5
D 10
	(void)fprintf(stderr,
	    "nice: %s: %s\n", argv[1], strerror(errno));
	exit(1);
E 10
I 10
	err(1, "%s", argv[1]);
E 10
}

I 8
void
E 8
usage()
{
	(void)fprintf(stderr,
	    "nice [ -# ] command [ options ] [ operands ]\n");
E 5
E 2
	exit(1);
}
E 1
