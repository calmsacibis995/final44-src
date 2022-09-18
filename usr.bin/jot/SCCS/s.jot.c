h44109
s 00005/00005/00362
d D 8.1 93/06/06 14:52:28 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00091/00065/00276
d D 4.4 93/05/26 14:45:28 bostic 6 5
c integrate into the 4BSD release
e
s 00001/00002/00340
d D 4.3 86/04/05 00:40:23 lepreau 5 4
c mising exit(0) in main
e
s 00020/00004/00322
d D 4.2 85/03/25 08:59:47 jak 4 1
c uses random(), not rand()
e
s 00008/00002/00324
d R 4.2 83/11/19 15:09:20 jak 3 1
c added -n option
e
s 00006/00001/00325
d R 4.2 83/11/19 15:00:11 jak 2 1
c added -n option
e
s 00326/00000/00000
d D 4.1 83/07/08 02:24:43 sam 1 0
c date and time created 83/07/08 02:24:43 by sam
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1983 Regents of the University of California */
E 6
I 6
/*-
D 7
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */
E 6

#ifndef lint
D 6
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 6
I 6
D 7
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */
E 6

I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 6
/*
D 6
 *	jot - print sequential or random data
 *	Author:  John Kunze, Office of Comp. Affairs, UCB
E 6
I 6
 * jot - print sequential or random data
 *
 * Author:  John Kunze, Office of Comp. Affairs, UCB
E 6
 */

D 6
#include <stdio.h>
E 6
#include <ctype.h>
I 6
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
E 6

#define	REPS_DEF	100
#define	BEGIN_DEF	1
#define	ENDER_DEF	100
#define	STEP_DEF	1

I 4
D 6
#define BSD4_2		1
#if BSD4_2
#define RAND		random
#define SRAND		srandom
long RAND();
#else
#define RAND		rand
#define SRAND		srand
#endif

E 6
E 4
#define	isdefault(s)	(strcmp((s), "-") == 0)
D 6
#define	LARGESTINT	(~ (unsigned) 0 >> 1)
#define	CASE		break; case
E 6

D 6
char	*sepstring = "\n";
char	format[BUFSIZ];
char	buf[BUFSIZ];
E 6
I 6
double	begin;
double	ender;
double	s;
long	reps;
E 6
int	randomize;
int	infinity;
int	boring;
int	prec;
int	dox;
int	chardata;
I 4
int	nofinalnl;
I 6
char	*sepstring = "\n";
char	format[BUFSIZ];
E 6
E 4

D 6
long	reps;
double	begin;
double	ender;
double	s;
E 6
I 6
void	error __P((char *, char *));
void	getargs __P((int, char *[]));
void	getformat __P((void));
int	getprec __P((char *));
void	putdata __P((double, long));
E 6

I 6
int
E 6
main(argc, argv)
D 6
int	argc;
char	**argv;
E 6
I 6
	int argc;
	char *argv[];
E 6
{
	double	xd, yd;
	long	id;
	register double	*x = &xd;
	register double	*y = &yd;
	register long	*i = &id;

D 6
	setbuf(stdout, buf);
E 6
	getargs(argc, argv);
	if (randomize) {
		*x = (ender - begin) * (ender > begin ? 1 : -1);
D 4
		srand((int) s);
E 4
I 4
D 6
		SRAND((int) s);
E 6
I 6
		srandom((int) s);
E 6
E 4
		for (*i = 1; *i <= reps || infinity; (*i)++) {
D 4
			*y = (double) rand() / LARGESTINT;
E 4
I 4
D 6
			*y = (double) RAND() / LARGESTINT;
E 6
I 6
			*y = (double) random() / INT_MAX;
E 6
E 4
			putdata(*y * *x + begin, reps - *i);
		}
	}
	else
		for (*i = 1, *x = begin; *i <= reps || infinity; (*i)++, *x += s)
			putdata(*x, reps - *i);
D 4
	putchar('\n');
E 4
I 4
	if (!nofinalnl)
		putchar('\n');
I 5
	exit(0);
E 5
E 4
}

I 6
void
E 6
getargs(ac, av)
D 6
int	ac;
char	**av;
E 6
I 6
	int ac;
	char *av[];
E 6
{
	register unsigned int	mask = 0;
	register int		n = 0;

	while (--ac && **++av == '-' && !isdefault(*av))
		switch ((*av)[1]) {
		case 'r':
			randomize = 1;
			break;
		case 'c':
			chardata = 1;
			break;
I 4
		case 'n':
			nofinalnl = 1;
			break;
E 4
		case 'b':
			boring = 1;
		case 'w':
			if ((*av)[2])
				strcpy(format, *av + 2);
			else if (!--ac)
				error("Need context word after -w or -b", "");
			else
				strcpy(format, *++av);
			break;
		case 's':
			if ((*av)[2])
				strcpy(sepstring, *av + 2);
			else if (!--ac)
				error("Need string after -s", "");
			else
				strcpy(sepstring, *++av);
			break;
		case 'p':
			if ((*av)[2])
				prec = atoi(*av + 2);
			else if (!--ac)
				error("Need number after -p", "");
			else
				prec = atoi(*++av);
			if (prec <= 0)
				error("Bad precision value", "");
			break;
		default:
			error("Unknown option %s", *av);
		}
I 6

E 6
	switch (ac) {	/* examine args right to left, falling thru cases */
	case 4:
		if (!isdefault(av[3])) {
D 6
			if (!sscanf(av[3], "%F", &s))
E 6
I 6
			if (!sscanf(av[3], "%lf", &s))
E 6
				error("Bad s value:  %s", av[3]);
			mask |= 01;
		}
	case 3:
		if (!isdefault(av[2])) {
D 6
			if (!sscanf(av[2], "%F", &ender))
E 6
I 6
			if (!sscanf(av[2], "%lf", &ender))
E 6
				ender = av[2][strlen(av[2])-1];
			mask |= 02;
			if (!prec)
				n = getprec(av[2]);
		}
	case 2:
		if (!isdefault(av[1])) {
D 6
			if (!sscanf(av[1], "%F", &begin))
E 6
I 6
			if (!sscanf(av[1], "%lf", &begin))
E 6
				begin = av[1][strlen(av[1])-1];
			mask |= 04;
			if (!prec)
				prec = getprec(av[1]);
			if (n > prec)		/* maximum precision */
				prec = n;
		}
	case 1:
		if (!isdefault(av[0])) {
D 6
			if (!sscanf(av[0], "%D", &reps))
E 6
I 6
			if (!sscanf(av[0], "%ld", &reps))
E 6
				error("Bad reps value:  %s", av[0]);
			mask |= 010;
		}
		break;
	case 0:
		error("jot - print sequential or random data", "");
	default:
		error("Too many arguments.  What do you mean by %s?", av[4]);
	}
	getformat();
	while (mask)	/* 4 bit mask has 1's where last 4 args were given */
		switch (mask) {	/* fill in the 0's by default or computation */
D 6
		CASE 001:
E 6
I 6
		case 001:
E 6
			reps = REPS_DEF;
			mask = 011;
D 6
		CASE 002:
E 6
I 6
			break;
		case 002:
E 6
			reps = REPS_DEF;
			mask = 012;
D 6
		CASE 003:
E 6
I 6
			break;
		case 003:
E 6
			reps = REPS_DEF;
			mask = 013;
D 6
		CASE 004:
E 6
I 6
			break;
		case 004:
E 6
			reps = REPS_DEF;
			mask = 014;
D 6
		CASE 005:
E 6
I 6
			break;
		case 005:
E 6
			reps = REPS_DEF;
			mask = 015;
D 6
		CASE 006:
E 6
I 6
			break;
		case 006:
E 6
			reps = REPS_DEF;
			mask = 016;
D 6
		CASE 007:
E 6
I 6
			break;
		case 007:
E 6
			if (randomize) {
				reps = REPS_DEF;
				mask = 0;
				break;
			}
			if (s == 0.0) {
				reps = 0;
				mask = 0;
				break;
			}
			reps = (ender - begin + s) / s;
			if (reps <= 0)
				error("Impossible stepsize", "");
			mask = 0;
D 6
		CASE 010:
E 6
I 6
			break;
		case 010:
E 6
			begin = BEGIN_DEF;
			mask = 014;
D 6
		CASE 011:
E 6
I 6
			break;
		case 011:
E 6
			begin = BEGIN_DEF;
			mask = 015;
D 6
		CASE 012:
E 6
I 6
			break;
		case 012:
E 6
			s = (randomize ? time(0) : STEP_DEF);
			mask = 013;
D 6
		CASE 013:
E 6
I 6
			break;
		case 013:
E 6
			if (randomize)
				begin = BEGIN_DEF;
			else if (reps == 0)
				error("Must specify begin if reps == 0", "");
			begin = ender - reps * s + s;
			mask = 0;
D 6
		CASE 014:
E 6
I 6
			break;
		case 014:
E 6
			s = (randomize ? time(0) : STEP_DEF);
			mask = 015;
D 6
		CASE 015:
E 6
I 6
			break;
		case 015:
E 6
			if (randomize)
				ender = ENDER_DEF;
			else
				ender = begin + reps * s - s;
			mask = 0;
D 6
		CASE 016:
E 6
I 6
			break;
		case 016:
E 6
			if (randomize)
				s = time(0);
			else if (reps == 0)
D 6
				error("Infinite sequences cannot be bounded", "");
E 6
I 6
				error("Infinite sequences cannot be bounded",
				    "");
E 6
			else if (reps == 1)
				s = 0.0;
			else
				s = (ender - begin) / (reps - 1);
			mask = 0;
D 6
		CASE 017:
			if (!randomize && s != 0.0) {	/* if reps given and implied, */
E 6
I 6
			break;
		case 017:		/* if reps given and implied, */
			if (!randomize && s != 0.0) {
E 6
				long t = (ender - begin + s) / s;
				if (t <= 0)
					error("Impossible stepsize", "");
				if (t < reps)		/* take lesser */
					reps = t;
			}
			mask = 0;
			break;
		default:
			error("Bad mask", "");
		}
	if (reps == 0)
		infinity = 1;
}

I 6
void
E 6
putdata(x, notlast)
D 6
double	x;
long	notlast;
E 6
I 6
	double x;
	long notlast;
E 6
{
	long		d = x;
D 5
	register char	*r;
	register char	*e;
E 5
	register long	*dp = &d;

	if (boring)				/* repeated word */
		printf(format);
	else if (dox)				/* scalar */
		printf(format, *dp);
	else					/* real */
		printf(format, x);
	if (notlast != 0)
		fputs(sepstring, stdout);
}

I 6
void
E 6
error(msg, s)
D 6
char	*msg;
char	*s;
E 6
I 6
	char *msg, *s;
E 6
{
D 6
	char	buf[BUFSIZ];

	setbuf(stderr, buf);
E 6
	fprintf(stderr, "jot: ");
	fprintf(stderr, msg, s);
D 6
	fprintf(stderr, "\nUsage:  jot [ options ] [ reps [ begin [ end [ s ] ] ] ]\n");
E 6
I 6
	fprintf(stderr,
	    "\nusage:  jot [ options ] [ reps [ begin [ end [ s ] ] ] ]\n");
E 6
	if (strncmp("jot - ", msg, 6) == 0)
D 4
		fprintf(stderr, "Options:\n\t%s\t%s\t%s\t%s\t%s",
E 4
I 4
D 6
		fprintf(stderr, "Options:\n\t%s\t%s\t%s\t%s\t%s\t%s",
E 6
I 6
		fprintf(stderr, "Options:\n\t%s\t%s\t%s\t%s\t%s\t%s\t%s",
E 6
E 4
			"-r		random data\n",
			"-c		character data\n",
I 4
			"-n		no final newline\n",
E 4
			"-b word		repeated word\n",
			"-w word		context word\n",
			"-s string	data separator\n",
			"-p precision	number of characters\n");
	exit(1);
}

I 6
int
E 6
getprec(s)
D 6
char	*s;
E 6
I 6
	char *s;
E 6
{
	register char	*p;
	register char	*q;

	for (p = s; *p; p++)
		if (*p == '.')
			break;
	if (!*p)
D 6
		return(0);
E 6
I 6
		return (0);
E 6
	for (q = ++p; *p; p++)
		if (!isdigit(*p))
			break;
D 6
	return(p - q);
E 6
I 6
	return (p - q);
E 6
}

I 6
void
E 6
getformat()
{
	register char	*p;

	if (boring)				/* no need to bother */
		return;
	for (p = format; *p; p++)		/* look for '%' */
		if (*p == '%' && *(p+1) != '%')	/* leave %% alone */
			break;
	if (!*p && !chardata)
		sprintf(p, "%%.%df", prec);
	else if (!*p && chardata) {
		strcpy(p, "%c");
		dox = 1;
	}
	else if (!*(p+1))
		strcat(format, "%");		/* cannot end in single '%' */
	else {
		while (!isalpha(*p))
			p++;
		switch (*p) {
		case 'f': case 'e': case 'g': case '%':
			break;
		case 's':
			error("Cannot convert numeric data to strings", "");
			break;
		/* case 'd': case 'o': case 'x': case 'D': case 'O': case 'X':
		case 'c': case 'u': */
		default:
			dox = 1;
			break;
		}
	}
}
E 1
