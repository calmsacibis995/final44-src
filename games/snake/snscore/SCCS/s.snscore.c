h40174
s 00005/00005/00087
d D 8.1 93/07/19 15:06:18 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00011/00080
d D 5.8 93/07/19 15:06:09 bostic 11 9
c An uninitialized variable could make it print out null scores
c From: Craig Leres <leres@ee.lbl.gov>
e
s 00005/00005/00086
d R 8.1 93/05/31 17:53:05 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00091
d D 5.7 91/02/28 15:39:14 bostic 9 8
c minor fix -- this needs to just use ndbm instead
e
s 00002/00004/00089
d D 5.6 91/02/28 15:08:10 bostic 8 7
c ANSI
e
s 00001/00011/00092
d D 5.5 90/06/01 13:18:00 bostic 7 6
c new copyright notice
e
s 00004/00001/00099
d D 5.4 89/03/05 21:12:00 bostic 6 5
c pwd.h needs types.h; add pathnames.h
e
s 00010/00005/00090
d D 5.3 88/06/18 19:30:55 bostic 5 4
c install approved copyright notice
e
s 00015/00003/00080
d D 5.2 88/03/09 11:29:55 bostic 4 3
c add Berkeley specific header
e
s 00007/00001/00076
d D 5.1 85/05/30 08:45:38 dist 3 2
c Add copyright
e
s 00000/00017/00077
d D 4.2 84/07/06 19:02:36 karels 2 1
c don't need internal getpwuid now
e
s 00094/00000/00000
d D 4.1 83/07/04 12:48:31 sam 1 0
c date and time created 83/07/04 12:48:31 by sam
e
u
U
t
T
I 3
/*
D 12
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 7
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 5
E 4
 */

E 3
I 1
#ifndef lint
I 4
D 12
char copyright[] =
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
#endif /* not lint */

#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 3

D 8
#include <stdio.h>
E 8
I 6
#include <sys/types.h>
E 6
#include <pwd.h>
I 8
#include <stdio.h>
#include <stdlib.h>
E 8
D 6
char *recfile = "/usr/games/lib/snakerawscores";
E 6
I 6
#include "pathnames.h"

char *recfile = _PATH_RAWSCORES;
E 6
#define MAXPLAYERS 256
D 8

struct	passwd	*getpwuid();
char	*malloc();
E 8

struct	player	{
	short	uids;
	short	scores;
	char	*name;
} players[MAXPLAYERS], temp;

I 11
int
E 11
main()
{
D 11
	char	buf[80], cp;
E 11
	short	uid, score;
	FILE	*fd;
	int	noplayers;
	int	i, j, notsorted;
	short	whoallbest, allbest;
	char	*q;
	struct	passwd	*p;

	fd = fopen(recfile, "r");
	if (fd == NULL) {
		perror(recfile);
		exit(1);
	}
	printf("Snake players scores to date\n");
	fread(&whoallbest, sizeof(short), 1, fd);
	fread(&allbest, sizeof(short), 1, fd);
D 11
	for (uid=2;;uid++) {
E 11
I 11
	noplayers = 0;
	for (uid = 2; ;uid++) {
E 11
		if(fread(&score, sizeof(short), 1, fd) == 0)
			break;
		if (score > 0) {
			if (noplayers > MAXPLAYERS) {
				printf("too many players\n");
				exit(2);
			}
			players[noplayers].uids = uid;
			players[noplayers].scores = score;
D 2
			/* This is faster if passwd is sorted by uid. */
E 2
			p = getpwuid(uid);
			if (p == NULL)
				continue;
			q = p -> pw_name;
D 11
			players[noplayers].name = malloc(strlen(q)+1);
E 11
I 11
			players[noplayers].name = malloc(strlen(q) + 1);
E 11
			strcpy(players[noplayers].name, q);
			noplayers++;
		}
	}

	/* bubble sort scores */
D 11
	for (notsorted=1; notsorted; ) {
E 11
I 11
	for (notsorted = 1; notsorted; ) {
E 11
		notsorted = 0;
D 11
		for (i=0; i<noplayers-1; i++)
			if (players[i].scores < players[i+1].scores) {
E 11
I 11
		for (i = 0; i < noplayers - 1; i++)
			if (players[i].scores < players[i + 1].scores) {
E 11
				temp = players[i];
D 11
				players[i] = players[i+1];
				players[i+1] = temp;
E 11
I 11
				players[i] = players[i + 1];
				players[i + 1] = temp;
E 11
				notsorted++;
			}
	}

	j = 1;
D 11
	for (i=0; i<noplayers; i++) {
E 11
I 11
	for (i = 0; i < noplayers; i++) {
E 11
		printf("%d:\t$%d\t%s\n", j, players[i].scores, players[i].name);
D 11
		if (players[i].scores > players[i+1].scores)
			j = i+2;
E 11
I 11
		if (players[i].scores > players[i + 1].scores)
			j = i + 2;
E 11
	}
	exit(0);
D 2
}

struct passwd *
getpwuid(uid)
register uid;
{
	register struct passwd *p;
	struct passwd *getpwent();

	while( (p = getpwent()) && p->pw_uid != uid );
	if (p->pw_uid == uid)
		return(p);
	setpwent();
	while( (p = getpwent()) && p->pw_uid != uid );
	endpwent();
	return(p);
E 2
}
E 1
