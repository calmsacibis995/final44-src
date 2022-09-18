h56261
s 00005/00005/00147
d D 8.1 93/05/31 17:42:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00001/00149
d D 5.3 91/02/28 14:23:00 bostic 3 2
c ANSI
e
s 00001/00011/00149
d D 5.2 90/06/01 13:12:21 bostic 2 1
c new copyright notice
e
s 00160/00000/00000
d D 5.1 89/09/07 17:32:27 bostic 1 0
c date and time created 89/09/07 17:32:27 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software posted to USENET.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Phase of the Moon.  Calculates the current phase of the moon.
 * Based on routines from `Practical Astronomy with Your Calculator',
 * by Duffett-Smith.  Comments give the section from the book that
 * particular piece of code was adapted from.
 *
 * -- Keith E. Brandt  VIII 1984
 *
 */

#include <sys/time.h>
#include <stdio.h>
#include <tzfile.h>
#include <math.h>

#define	PI	  3.141592654
#define	EPOCH	  85
#define	EPSILONg  279.611371	/* solar ecliptic long at EPOCH */
#define	RHOg	  282.680403	/* solar ecliptic long of perigee at EPOCH */
#define	ECCEN	  0.01671542	/* solar orbit eccentricity */
#define	lzero	  18.251907	/* lunar mean long at EPOCH */
#define	Pzero	  192.917585	/* lunar mean long of perigee at EPOCH */
#define	Nzero	  55.204723	/* lunar mean long of node at EPOCH */

I 3
double dtor(), potm(), adj360();

E 3
main()
{
	extern int errno;
	struct timeval tp;
	struct timezone tzp;
	struct tm *GMT, *gmtime();
D 3
	double days, today, tomorrow, dtor(), adj360(), potm();
E 3
I 3
	double days, today, tomorrow;
E 3
	int cnt;
	char *strerror();

	if (gettimeofday(&tp,&tzp)) {
		(void)fprintf(stderr, "pom: %s\n", strerror(errno));
		exit(1);
	}
	GMT = gmtime(&tp.tv_sec);
	days = (GMT->tm_yday + 1) + ((GMT->tm_hour +
	    (GMT->tm_min / 60.0) + (GMT->tm_sec / 3600.0)) / 24.0);
	for (cnt = EPOCH; cnt < GMT->tm_year; ++cnt)
		days += isleap(cnt) ? 366 : 365;
	today = potm(days) + .5;
	(void)printf("The Moon is ");
	if ((int)today == 100)
		(void)printf("Full\n");
	else if (!(int)today)
		(void)printf("New\n");
	else {
		tomorrow = potm(days + 1);
		if ((int)today == 50)
			(void)printf("%s\n", tomorrow > today ?
			    "at the First Quarter" : "at the Last Quarter");
		else {
			(void)printf("%s ", tomorrow > today ?
			    "Waxing" : "Waning");
			if (today > 50)
				(void)printf("Gibbous (%1.0f%% of Full)\n",
				    today);
			else if (today < 50)
				(void)printf("Crescent (%1.0f%% of Full)\n",
				    today);
		}
	}
}

/*
 * potm --
 *	return phase of the moon
 */
double
potm(days)
	double days;
{
	double N, Msol, Ec, LambdaSol, l, Mm, Ev, Ac, A3, Mmprime;
	double A4, lprime, V, ldprime, D, Nm;

	N = 360 * days / 365.2422;				/* sec 42 #3 */
	adj360(&N);
	Msol = N + EPSILONg - RHOg;				/* sec 42 #4 */
	adj360(&Msol);
	Ec = 360 / PI * ECCEN * sin(dtor(Msol));		/* sec 42 #5 */
	LambdaSol = N + Ec + EPSILONg;				/* sec 42 #6 */
	adj360(&LambdaSol);
	l = 13.1763966 * days + lzero;				/* sec 61 #4 */
	adj360(&l);
	Mm = l - (0.1114041 * days) - Pzero;			/* sec 61 #5 */
	adj360(&Mm);
	Nm = Nzero - (0.0529539 * days);			/* sec 61 #6 */
	adj360(&Nm);
	Ev = 1.2739 * sin(dtor(2*(l - LambdaSol) - Mm));	/* sec 61 #7 */
	Ac = 0.1858 * sin(dtor(Msol));				/* sec 61 #8 */
	A3 = 0.37 * sin(dtor(Msol));
	Mmprime = Mm + Ev - Ac - A3;				/* sec 61 #9 */
	Ec = 6.2886 * sin(dtor(Mmprime));			/* sec 61 #10 */
	A4 = 0.214 * sin(dtor(2 * Mmprime));			/* sec 61 #11 */
	lprime = l + Ev + Ec - Ac + A4;				/* sec 61 #12 */
	V = 0.6583 * sin(dtor(2 * (lprime - LambdaSol)));	/* sec 61 #13 */
	ldprime = lprime + V;					/* sec 61 #14 */
	D = ldprime - LambdaSol;				/* sec 63 #2 */
	return(50 * (1 - cos(dtor(D))));			/* sec 63 #3 */
}

/*
 * dtor --
 *	convert degrees to radians
 */
double
dtor(deg)
	double deg;
{
	return(deg * PI / 180);
}

/*
 * adj360 --
 *	adjust value so 0 <= deg <= 360
 */
double
adj360(deg)
	double *deg;
{
	for (;;)
		if (*deg < 0)
			*deg += 360;
		else if (*deg > 360)
			*deg -= 360;
		else
			break;
}
E 1
