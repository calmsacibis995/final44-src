h09729
s 00002/00002/00156
d D 8.1 93/05/31 17:45:56 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00157
d D 5.6 90/06/01 13:15:46 bostic 6 5
c new copyright notice
e
s 00002/00001/00166
d D 5.5 90/05/02 22:33:14 bostic 5 4
c move score file to /var/games
e
s 00001/00000/00166
d D 5.4 89/03/05 21:11:46 bostic 4 3
c pwd.h needs types.h
e
s 00010/00005/00156
d D 5.3 88/06/18 20:04:51 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00152
d D 5.2 88/03/09 11:18:49 bostic 2 1
c Written by Ken Arnold; add Berkeley specific copyright
e
s 00155/00000/00000
d D 5.1 85/05/30 18:36:16 mckusick 1 0
c date and time created 85/05/30 18:36:16 by mckusick
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1980 Regents of the University of California.
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

# include	"robots.h"
I 4
# include	<sys/types.h>
E 4
# include	<pwd.h>
I 5
# include	"pathnames.h"
E 5

typedef struct {
	int	s_uid;
	int	s_score;
	char	s_name[MAXNAME];
} SCORE;

typedef struct passwd	PASSWD;

D 5
char	*Scorefile = SCOREFILE;
E 5
I 5
char	*Scorefile = _PATH_SCORE;
E 5

int	Max_per_uid = MAX_PER_UID;

static SCORE	Top[MAXSCORES];

/*
 * score:
 *	Post the player's score, if reasonable, and then print out the
 *	top list.
 */
score()
{
	register int	inf;
	register SCORE	*scp;
	register int	uid;
	register bool	done_show = FALSE;
	static int	numscores, max_uid;

	Newscore = FALSE;
	if ((inf = open(Scorefile, 2)) < 0) {
		perror(Scorefile);
		return;
	}

	if (read(inf, &max_uid, sizeof max_uid) == sizeof max_uid)
		read(inf, Top, sizeof Top);
	else {
		for (scp = Top; scp < &Top[MAXSCORES]; scp++)
			scp->s_score = -1;
		max_uid = Max_per_uid;
	}

	uid = getuid();
	if (Top[MAXSCORES-1].s_score <= Score) {
		numscores = 0;
		for (scp = Top; scp < &Top[MAXSCORES]; scp++)
			if (scp->s_score < 0 ||
			    (scp->s_uid == uid && ++numscores == max_uid)) {
				if (scp->s_score > Score)
					break;
				scp->s_score = Score;
				scp->s_uid = uid;
				set_name(scp);
				Newscore = TRUE;
				break;
			}
		if (scp == &Top[MAXSCORES]) {
			Top[MAXSCORES-1].s_score = Score;
			Top[MAXSCORES-1].s_uid = uid;
			set_name(&Top[MAXSCORES-1]);
			Newscore = TRUE;
		}
		if (Newscore)
			qsort(Top, MAXSCORES, sizeof Top[0], cmp_sc);
	}

	if (!Newscore) {
		Full_clear = FALSE;
		close(inf);
		return;
	}
	else
		Full_clear = TRUE;

	for (scp = Top; scp < &Top[MAXSCORES]; scp++) {
		if (scp->s_score < 0)
			break;
		move((scp - Top) + 1, 15);
		if (!done_show && scp->s_uid == uid && scp->s_score == Score)
			standout();
		printw(" %d\t%d\t%-8.8s ", (scp - Top) + 1, scp->s_score, scp->s_name);
		if (!done_show && scp->s_uid == uid && scp->s_score == Score) {
			standend();
			done_show = TRUE;
		}
	}
	Num_scores = scp - Top;
	refresh();

	if (Newscore) {
		lseek(inf, 0L, 0);
		write(inf, &max_uid, sizeof max_uid);
		write(inf, Top, sizeof Top);
	}
	close(inf);
}

set_name(scp)
register SCORE	*scp;
{
	register PASSWD	*pp;

	if ((pp = getpwuid(scp->s_uid)) == NULL)
		pp->pw_name = "???";
	strncpy(scp->s_name, pp->pw_name, MAXNAME);
}

/*
 * cmp_sc:
 *	Compare two scores.
 */
cmp_sc(s1, s2)
register SCORE	*s1, *s2;
{
	return s2->s_score - s1->s_score;
}

/*
 * show_score:
 *	Show the score list for the '-s' option.
 */
show_score()
{
	register SCORE	*scp;
	register int	inf;
	static int	max_score;

	if ((inf = open(Scorefile, 0)) < 0) {
		perror(Scorefile);
		return;
	}

	for (scp = Top; scp < &Top[MAXSCORES]; scp++)
		scp->s_score = -1;

	read(inf, &max_score, sizeof max_score);
	read(inf, Top, sizeof Top);
	close(inf);
	inf = 1;
	for (scp = Top; scp < &Top[MAXSCORES]; scp++)
		if (scp->s_score >= 0)
			printf("%d\t%d\t%.*s\n", inf++, scp->s_score, sizeof scp->s_name, scp->s_name);
}
E 1
