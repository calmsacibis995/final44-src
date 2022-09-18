h63556
s 00005/00005/00097
d D 8.1 93/06/09 22:52:00 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00100
d D 5.4 92/06/18 12:20:20 bostic 11 10
c sys/resource.h needs sys/types.h now
e
s 00001/00011/00099
d D 5.3 90/06/01 17:32:00 bostic 10 9
c new copyright notice
e
s 00017/00006/00093
d D 5.2 89/09/05 11:31:13 bostic 9 8
c written by Sam Leffler; add Berkeley copyright
e
s 00014/00002/00085
d D 5.1 85/05/28 15:06:50 dist 8 7
c Add copyright
e
s 00002/00001/00085
d D 4.6 83/07/24 12:55:04 sam 7 6
c give full usage message
e
s 00002/00004/00084
d D 4.5 83/07/24 12:27:26 sam 6 4
c eliminate special case
e
s 00002/00004/00084
d R 4.5 83/07/24 12:23:13 sam 5 4
c renice'ng current proc is worthless
e
s 00018/00018/00070
d D 4.4 83/07/24 12:20:34 sam 4 3
c allow mix of pid, user, pgrp
e
s 00002/00002/00086
d D 4.3 83/07/02 00:19:00 sam 3 2
c include fixes
e
s 00029/00024/00059
d D 4.2 83/03/19 13:34:03 sam 2 1
c clean up
e
s 00083/00000/00000
d D 4.1 83/03/19 13:08:38 sam 1 0
c date and time created 83/03/19 13:08:38 by sam
e
u
U
t
T
I 8
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 12
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1983, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
 */

E 8
I 1
#ifndef lint
D 8
static	char *sccsid = "%W% (Berkeley) %E%";
#endif
E 8
I 8
D 12
char copyright[] =
D 9
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 9
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1983, 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 8

I 11
#include <sys/types.h>
E 11
D 3
#include <time.h>
#include <resource.h>
E 3
I 3
#include <sys/time.h>
#include <sys/resource.h>
I 11

E 11
E 3
#include <stdio.h>
#include <pwd.h>

/*
 * Change the priority (nice) of processes
 * or groups of processes which are already
 * running.
 */
main(argc, argv)
	char **argv;
{
	int which = PRIO_PROCESS;
D 2
	int who, id, prio, oldprio, errs = 0;
	extern int errno;
E 2
I 2
	int who = 0, prio, errs = 0;
E 2

	argc--, argv++;
D 4
	if (argc < 2)
		usage();
	if (strcmp(*argv, "-g") == 0) {
		which = PRIO_PGRP;
		argv++, argc--;
	} else if (strcmp(*argv, "-u") == 0) {
		which = PRIO_USER;
		argv++, argc--;
E 4
I 4
D 6
	if (argc < 1) {
		fprintf(stderr, "usage: renice priority [ who ... ]\n");
E 6
I 6
	if (argc < 2) {
D 7
		fprintf(stderr, "usage: renice priority who ...\n");
E 7
I 7
		fprintf(stderr, "usage: renice priority [ [ -p ] pids ] ");
		fprintf(stderr, "[ [ -g ] pgrps ] [ [ -u ] users ]\n");
E 7
E 6
		exit(1);
E 4
	}
	prio = atoi(*argv);
	argc--, argv++;
	if (prio > PRIO_MAX)
		prio = PRIO_MAX;
	if (prio < PRIO_MIN)
		prio = PRIO_MIN;
D 6
	if (argc == 0)
D 2
		usage();
E 2
I 2
D 4
		errs += donice(which, 0, prio);
E 4
I 4
		exit(donice(which, 0, prio));
E 6
E 4
E 2
	for (; argc > 0; argc--, argv++) {
I 4
		if (strcmp(*argv, "-g") == 0) {
			which = PRIO_PGRP;
			continue;
		}
		if (strcmp(*argv, "-u") == 0) {
			which = PRIO_USER;
			continue;
		}
		if (strcmp(*argv, "-p") == 0) {
			which = PRIO_PROCESS;
			continue;
		}
E 4
		if (which == PRIO_USER) {
			register struct passwd *pwd = getpwnam(*argv);
			
			if (pwd == NULL) {
				fprintf(stderr, "renice: %s: unknown user\n",
					*argv);
				continue;
			}
D 2
			id = pwd->pw_uid;
E 2
I 2
			who = pwd->pw_uid;
E 2
		} else {
D 2
			id = atoi(*argv);
			if (id < 0) {
E 2
I 2
			who = atoi(*argv);
			if (who < 0) {
E 2
				fprintf(stderr, "renice: %s: bad value\n",
					*argv);
				continue;
			}
		}
D 2
		oldprio = getpriority(which, who);
		if (oldprio == -1 && errno) {
			fprintf(stderr, "renice: ");
			perror(*argv);
			errs++;
			continue;
		}
		if (setpriority(which, who, prio) < 0) {
			fprintf(stderr, "renice: ");
			perror(*argv);
			errs++;
			continue;
		}
		printf("%s: old priority %d, new priority %d\n", *argv,
			oldprio, prio);
E 2
I 2
		errs += donice(which, who, prio);
E 2
	}
	exit(errs != 0);
}

I 2
donice(which, who, prio)
	int which, who, prio;
{
D 4
	int oldprio = getpriority(which, who);
E 4
I 4
	int oldprio;
E 4
	extern int errno;

I 4
	errno = 0, oldprio = getpriority(which, who);
E 4
	if (oldprio == -1 && errno) {
		fprintf(stderr, "renice: %d: ", who);
		perror("getpriority");
		return (1);
	}
	if (setpriority(which, who, prio) < 0) {
		fprintf(stderr, "renice: %d: ", who);
		perror("setpriority");
		return (1);
	}
	printf("%d: old priority %d, new priority %d\n", who, oldprio, prio);
	return (0);
D 4
}

E 2
usage()
{
D 2
	fprintf(stderr, "usage: renice priority pid ....\n");
	fprintf(stderr, "or, renice -g priority pgrp ....\n");
	fprintf(stderr, "or, renice -u priority user ....\n");
E 2
I 2
	fprintf(stderr, "usage: renice priority [ pid .... ]\n");
	fprintf(stderr, "or, renice -g priority [ pgrp .... ]\n");
	fprintf(stderr, "or, renice -u priority [ user .... ]\n");
E 2
	exit(1);
E 4
}
E 1
