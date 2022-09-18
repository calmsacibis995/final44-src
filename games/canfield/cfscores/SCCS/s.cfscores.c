h28144
s 00005/00005/00117
d D 8.1 93/05/31 16:35:09 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00121
d D 5.6 90/06/01 13:03:14 bostic 8 7
c new copyright notice
e
s 00003/00003/00129
d D 5.5 90/04/30 21:55:18 bostic 7 6
c move score to /var/games
e
s 00001/00000/00131
d D 5.4 89/03/05 20:45:37 bostic 6 5
c pwd.h needs sys/types.h
e
s 00010/00005/00121
d D 5.3 88/06/18 19:49:18 bostic 5 4
c install approved copyright notice
e
s 00010/00004/00116
d D 5.2 88/05/06 10:36:10 bostic 4 3
c add Berkeley header
e
s 00012/00002/00108
d D 5.1 85/05/29 11:20:28 dist 3 2
c Add copyright
e
s 00001/00001/00109
d D 4.2 84/09/10 09:37:00 ralph 2 1
c check for null score file.
e
s 00110/00000/00000
d D 4.1 83/05/12 20:56:44 mckusick 1 0
c date and time created 83/05/12 20:56:44 by mckusick
e
u
U
t
T
I 1
D 3
/* Copyright (c) 1983 Regents of the University of California */
E 3
I 3
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 5
E 4
 */
E 3

#ifndef lint
D 3
static char sccsid[] = "%W%	(Berkeley)	%G%";
E 3
I 3
D 9
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

I 6
#include <sys/types.h>
E 6
#include <pwd.h>
I 7
#include "pathnames.h"
E 7

struct betinfo {
	long	hand;		/* cost of dealing hand */
	long	inspection;	/* cost of inspecting hand */
	long	game;		/* cost of buying game */
	long	runs;		/* cost of running through hands */
	long	information;	/* cost of information */
	long	thinktime;	/* cost of thinking time */
	long	wins;		/* total winnings */
	long	worth;		/* net worth after costs */
};

D 7
char *scorefile = "/usr/games/lib/cfscores";
E 7
int dbfd;

main(argc, argv)
	int argc;
	char *argv[];
{
	register struct passwd *pw;
	int uid;

	if (argc > 2) {
		printf("Usage: cfscores [user]\n");
		exit(1);
	}
D 7
	dbfd = open(scorefile, 0);
E 7
I 7
	dbfd = open(_PATH_SCORE, 0);
E 7
	if (dbfd < 0) {
D 7
		perror(scorefile);
E 7
I 7
		perror(_PATH_SCORE);
E 7
		exit(2);
	}
	setpwent();
	if (argc == 1) {
		uid = getuid();
		pw = getpwuid(uid);
		if (pw == 0) {
			printf("You are not listed in the password file?!?\n");
			exit(2);
		}
		printuser(pw, 1);
		exit(0);
	}
	if (strcmp(argv[1], "-a") == 0) {
		while ((pw = getpwent()) != 0)
			printuser(pw, 0);
		exit(0);
	}
	pw = getpwnam(argv[1]);
	if (pw == 0) {
		printf("User %s unknown\n", argv[1]);
		exit(3);
	}
	printuser(pw, 1);
	exit(0);
}

/*
 * print out info for specified password entry
 */
printuser(pw, printfail)
	register struct passwd *pw;
	int printfail;
{
	struct betinfo total;
	int i;

	if (pw->pw_uid < 0) {
		printf("Bad uid %d\n", pw->pw_uid);
		return;
	}
	i = lseek(dbfd, pw->pw_uid * sizeof(struct betinfo), 0);
	if (i < 0) {
		perror("lseek");
		return;
	}
	i = read(dbfd, (char *)&total, sizeof(total));
	if (i < 0) {
		perror("read");
		return;
	}
D 2
	if (total.hand == 0) {
E 2
I 2
	if (i == 0 || total.hand == 0) {
E 2
		if (printfail)
			printf("%s has never played canfield.\n", pw->pw_name);
		return;
	}
	printf("*----------------------*\n");
	if (total.worth >= 0)
		printf("* Winnings for %-8s*\n", pw->pw_name);
	else
		printf("* Losses for %-10s*\n", pw->pw_name);
	printf("*======================*\n");
	printf("|Costs           Total |\n");
	printf("| Hands       %8d |\n", total.hand);
	printf("| Inspections %8d |\n", total.inspection);
	printf("| Games       %8d |\n", total.game);
	printf("| Runs        %8d |\n", total.runs);
	printf("| Information %8d |\n", total.information);
	printf("| Think time  %8d |\n", total.thinktime);
	printf("|Total Costs  %8d |\n", total.wins - total.worth);
	printf("|Winnings     %8d |\n", total.wins);
	printf("|Net Worth    %8d |\n", total.worth);
	printf("*----------------------*\n\n");
}
E 1
