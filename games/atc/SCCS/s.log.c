h28624
s 00002/00002/00219
d D 8.1 93/05/31 16:04:01 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00220
d D 5.7 90/10/30 08:14:02 bostic 7 6
c ANSI C snarfed "clock"; change to "clck"
e
s 00010/00000/00211
d D 5.6 90/04/30 21:24:15 bostic 6 5
c Berkeley headers, SCCS id's
e
s 00005/00007/00206
d D 5.5 90/04/30 21:09:44 bostic 5 4
c move score to /var/games, games to /usr/share/games
e
s 00001/00001/00212
d D 5.4 87/12/26 13:09:27 bostic 4 3
c declare index/rindex returns for ANSI C
e
s 00002/00000/00211
d D 5.3 87/12/15 15:32:06 bostic 3 2
c fix from Ed James for scorefile
e
s 00004/00004/00207
d D 5.2 87/10/22 11:33:32 bostic 2 1
c ANSI C; sprintf now returns an int.
e
s 00211/00000/00000
d D 5.1 87/10/22 11:32:35 bostic 1 0
c date and time created 87/10/22 11:32:35 by bostic
e
u
U
t
T
I 6
/*-
D 8
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Ed James.
 *
 * %sccs.include.redist.c%
 */

E 6
I 1
/*
 * Copyright (c) 1987 by Ed James, UC Berkeley.  All rights reserved.
 *
 * Copy permission is hereby granted provided that this notice is
 * retained on all partial or complete copies.
 *
 * For more info on this and all of my stuff, mail edjames@berkeley.edu.
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

#include "include.h"
I 5
#include "pathnames.h"
E 5

compar(a, b)
	SCORE	*a, *b;
{
	if (b->planes == a->planes)
		return (b->time - a->time);
	else
		return (b->planes - a->planes);
}

#define SECAMIN		60
#define MINAHOUR	60
#define HOURADAY	24
#define SECAHOUR	(SECAMIN * MINAHOUR)
#define SECADAY		(SECAHOUR * HOURADAY)
#define DAY(t)		((t) / SECADAY)
#define HOUR(t)		(((t) % SECADAY) / SECAHOUR)
#define MIN(t)		(((t) % SECAHOUR) / SECAMIN)
#define SEC(t)		((t) % SECAMIN)

char	*
timestr(t)
{
	static char	s[80];

	if (DAY(t) > 0)
D 2
		sprintf(s, "%dd+%02dhrs", DAY(t), HOUR(t));
E 2
I 2
		(void)sprintf(s, "%dd+%02dhrs", DAY(t), HOUR(t));
E 2
	else if (HOUR(t) > 0)
D 2
		sprintf(s, "%d:%02d:%02d", HOUR(t), MIN(t), SEC(t));
E 2
I 2
		(void)sprintf(s, "%d:%02d:%02d", HOUR(t), MIN(t), SEC(t));
E 2
	else if (MIN(t) > 0)
D 2
		sprintf(s, "%d:%02d", MIN(t), SEC(t));
E 2
I 2
		(void)sprintf(s, "%d:%02d", MIN(t), SEC(t));
E 2
	else if (SEC(t) > 0)
D 2
		sprintf(s, ":%02d", SEC(t));
E 2
I 2
		(void)sprintf(s, ":%02d", SEC(t));
E 2
	else
		*s = '\0';

	return (s);
}

log_score(list_em)
{
	register int	i, fd, num_scores = 0, good, changed = 0, found = 0;
	struct passwd	*pw;
	FILE		*fp;
D 4
	char		*cp, logstr[BUFSIZ];
E 4
I 4
D 5
	char		*cp, logstr[BUFSIZ], *index(), *rindex();
E 5
I 5
	char		*cp, *index(), *rindex();
E 5
E 4
	SCORE		score[100], thisscore;
#ifdef SYSV
	struct utsname	name;
#endif

D 5
	strcpy(logstr, SPECIAL_DIR);
	strcat(logstr, LOG);

E 5
	umask(0);
D 5
	fd = open(logstr, O_CREAT|O_RDWR, 0644);
E 5
I 5
	fd = open(_PATH_SCORE, O_CREAT|O_RDWR, 0644);
E 5
	if (fd < 0) {
D 5
		perror(logstr);
E 5
I 5
		perror(_PATH_SCORE);
E 5
		return (-1);
	}
	/*
	 * This is done to take advantage of stdio, while still 
	 * allowing a O_CREAT during the open(2) of the log file.
	 */
	fp = fdopen(fd, "r+");
	if (fp == NULL) {
D 5
		perror(logstr);
E 5
I 5
		perror(_PATH_SCORE);
E 5
		return (-1);
	}
#ifdef BSD
	if (flock(fileno(fp), LOCK_EX) < 0)
#endif
#ifdef SYSV
	while (lockf(fileno(fp), F_LOCK, 1) < 0)
#endif
	{
		perror("flock");
		return (-1);
	}
	for (;;) {
		good = fscanf(fp, "%s %s %s %d %d %d",
			score[num_scores].name, 
			score[num_scores].host, 
			score[num_scores].game,
			&score[num_scores].planes, 
			&score[num_scores].time,
			&score[num_scores].real_time);
		if (good != 6 || ++num_scores >= NUM_SCORES)
			break;
	}
	if (!test_mode && !list_em) {
		if ((pw = (struct passwd *) getpwuid(getuid())) == NULL) {
			fprintf(stderr, 
				"getpwuid failed for uid %d.  Who are you?\n",
				getuid());
			return (-1);
		}
		strcpy(thisscore.name, pw->pw_name);
#ifdef BSD
		if (gethostname(thisscore.host, sizeof (thisscore.host)) < 0) {
			perror("gethostname");
			return (-1);
		}
#endif
#ifdef SYSV
		uname(&name);
		strcpy(thisscore.host, name.sysname);
#endif

		cp = rindex(file, '/');
		if (cp == NULL) {
			fprintf(stderr, "log: where's the '/' in %s?\n", file);
			return (-1);
		}
		cp++;
		strcpy(thisscore.game, cp);

D 7
		thisscore.time = clock;
E 7
I 7
		thisscore.time = clck;
E 7
		thisscore.planes = safe_planes;
		thisscore.real_time = time(0) - start_time;

		for (i = 0; i < num_scores; i++) {
			if (strcmp(thisscore.name, score[i].name) == 0 &&
			    strcmp(thisscore.host, score[i].host) == 0 &&
			    strcmp(thisscore.game, score[i].game) == 0) {
				if (thisscore.time > score[i].time) {
					score[i].time = thisscore.time;
					score[i].planes = thisscore.planes;
I 3
					score[i].real_time =
						thisscore.real_time;
E 3
					changed++;
				}
				found++;
				break;
			}
		}
		if (!found) {
			for (i = 0; i < num_scores; i++) {
				if (thisscore.time > score[i].time) {
					if (num_scores < NUM_SCORES)
						num_scores++;
					bcopy(&score[i],
						&score[num_scores - 1], 
						sizeof (score[i]));
					bcopy(&thisscore, &score[i],
						sizeof (score[i]));
					changed++;
					break;
				}
			}
		}
		if (!found && !changed && num_scores < NUM_SCORES) {
			bcopy(&thisscore, &score[num_scores], 
				sizeof (score[num_scores]));
			num_scores++;
			changed++;
		}

		if (changed) {
			if (found)
				puts("You beat your previous score!");
			else
				puts("You made the top players list!");
			qsort(score, num_scores, sizeof (*score), compar);
			rewind(fp);
			for (i = 0; i < num_scores; i++)
				fprintf(fp, "%s %s %s %d %d %d\n",
					score[i].name, score[i].host, 
					score[i].game, score[i].planes,
					score[i].time, score[i].real_time);
		} else {
			if (found)
				puts("You didn't beat your previous score.");
			else
				puts("You didn't make the top players list.");
		}
		putchar('\n');
	}
#ifdef BSD
	flock(fileno(fp), LOCK_UN);
#endif
#ifdef SYSV
	/* lock will evaporate upon close */
#endif
	fclose(fp);
	printf("%2s:  %-8s  %-8s  %-18s  %4s  %9s  %4s\n", "#", "name", "host", 
		"game", "time", "real time", "planes safe");
	puts("-------------------------------------------------------------------------------");
	for (i = 0; i < num_scores; i++) {
		cp = index(score[i].host, '.');
		if (cp != NULL)
			*cp = '\0';
		printf("%2d:  %-8s  %-8s  %-18s  %4d  %9s  %4d\n", i + 1,
			score[i].name, score[i].host, score[i].game,
			score[i].time, timestr(score[i].real_time),
			score[i].planes);
	}
	putchar('\n');
	return (0);
}
E 1
