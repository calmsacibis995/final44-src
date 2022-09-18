h29086
s 00002/00002/00399
d D 8.4 94/04/02 10:04:49 pendry 14 13
c add 1994 copyright
e
s 00063/00045/00338
d D 8.3 94/04/01 05:40:22 pendry 13 12
c prettyness police.
c fix error messages
e
s 00003/00000/00380
d D 8.2 93/09/30 06:45:41 pendry 12 11
c ensure lineout array is nul terminated in monthly, yearly & j_yearly.
e
s 00005/00005/00375
d D 8.1 93/06/06 14:25:27 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00022/00359
d D 5.2 91/04/19 18:55:06 bostic 10 9
c reduce static space, make a bit cleaner
e
s 00055/00030/00326
d D 5.1 91/04/19 18:51:51 bostic 9 8
c bug was that "month" wasn't initialized in main, so could drop core
c make day headings right justified -- not backward compatible, but nicer
c lots of minor cleanups/speedups when trying to remember how it worked
e
s 00001/00011/00355
d D 4.8 90/06/01 16:37:36 bostic 8 7
c new copyright notice
e
s 00132/00051/00234
d D 4.7 89/11/27 12:57:17 bostic 7 6
c add Julian calendar format
e
s 00028/00008/00257
d D 4.6 89/10/27 17:54:53 bostic 6 5
c add -y flag, I'm tired of trying to type in the year
e
s 00222/00159/00043
d D 4.5 89/09/28 14:20:24 bostic 5 4
c new version from Kim Letkeman (mitel!spock!kim@uunet.UU.NET)
e
s 00034/00040/00168
d D 4.4 87/05/28 21:04:37 sam 4 3
c make cal print calendar for current month with no arguments
e
s 00004/00001/00204
d D 4.3 83/08/11 20:27:38 sam 3 2
c standardize sccs keyword lines
e
s 00001/00001/00204
d D 4.2 82/02/28 23:16:41 wnj 2 1
c fix sccs keywords
e
s 00205/00000/00000
d D 4.1 82/02/28 23:15:28 wnj 1 0
c date and time created 82/02/28 23:15:28 by wnj
e
u
U
t
T
I 5
/*
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
D 14
 * Copyright (c) 1989, 1993
E 14
I 14
 * Copyright (c) 1989, 1993, 1994
E 14
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Kim Letkeman.
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
 */

E 5
I 1
D 2
char	*sccsid = "%W% %I%";
E 2
I 2
D 3
char	*sccsid = "%W% %E%";
E 3
I 3
#ifndef lint
D 5
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 5
I 5
D 11
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 11
I 11
static char copyright[] =
D 14
"%Z% Copyright (c) 1989, 1993\n\
E 14
I 14
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 14
	The Regents of the University of California.  All rights reserved.\n";
E 11
#endif /* not lint */
E 5

I 5
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 5
I 4
#include <sys/types.h>
D 5
#include <time.h>
E 5
I 5
D 13
#include <sys/time.h>
E 5
#include <stdio.h>
E 13
I 13

E 13
I 5
#include <ctype.h>
I 13
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
E 13
E 5

E 4
E 3
E 2
D 5
char	dayw[] = {
	" S  M Tu  W Th  F  S"
E 5
I 5
#define	THURSDAY		4		/* for reformation */
#define	SATURDAY 		6		/* 1 Jan 1 was a Saturday */
I 9

E 9
#define	FIRST_MISSING_DAY 	639787		/* 3 Sep 1752 */
#define	NUMBER_MISSING_DAYS 	11		/* 11 day correction */
I 9

#define	MAXDAYS			42		/* max slots in a month array */
E 9
D 7
#define	SPACE			99		/* used in day array */
E 7
I 7
#define	SPACE			-1		/* used in day array */
E 7

static int days_in_month[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
E 5
};
D 5
char	*smon[]= {
	"January", "February", "March", "April",
	"May", "June", "July", "August",
	"September", "October", "November", "December",
E 5
I 5

D 9
static int sep1752[42] = {
E 9
I 9
int sep1752[MAXDAYS] = {
E 9
D 7
	SPACE, SPACE,     1,     2,    14,    15,    16,
	   17,    18,    19,    20,    21,    22,    23,
	   24,    25,    26,    27,    28,    29,    30,
	SPACE, SPACE, SPACE, SPACE, SPACE, SPACE, SPACE,
	SPACE, SPACE, SPACE, SPACE, SPACE, SPACE, SPACE,
	SPACE, SPACE, SPACE, SPACE, SPACE, SPACE, SPACE,
E 7
I 7
	SPACE,	SPACE,	1,	2,	14,	15,	16,
	17,	18,	19,	20,	21,	22,	23,
	24,	25,	26,	27,	28,	29,	30,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
D 9
}, j_sep1752[42] = {
E 9
I 9
}, j_sep1752[MAXDAYS] = {
E 9
	SPACE,	SPACE,	245,	246,	258,	259,	260,
	261,	262,	263,	264,	265,	266,	267,
	268,	269,	270,	271,	272,	273,	274,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
I 9
}, empty[MAXDAYS] = {
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,	SPACE,
E 9
E 7
E 5
};
D 5
char	string[432];
E 5
I 5

D 9
static char *month_names[12] = {
E 9
I 9
char *month_names[12] = {
E 9
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December",
};

D 7
static char *day_headings = " S  M Tu  W Th  F  S";
E 7
I 7
D 9
static char *day_headings = " S  M  Tu W  Th F  S";
static char *j_day_headings = " S   M   Tu  W   Th  F   S";
E 9
I 9
char *day_headings = " S  M Tu  W Th  F  S";
char *j_day_headings = "  S   M  Tu   W  Th   F   S";
E 9
E 7

/* leap year -- account for gregorian reformation in 1752 */
#define	leap_year(yr) \
	((yr) <= 1752 ? !((yr) % 4) : \
	!((yr) % 4) && ((yr) % 100) || !((yr) % 400))

/* number of centuries since 1700, not inclusive */
#define	centuries_since_1700(yr) \
	((yr) > 1700 ? (yr) / 100 - 17 : 0)

/* number of centuries since 1700 whose modulo of 400 is 0 */
#define	quad_centuries_since_1700(yr) \
	((yr) > 1600 ? ((yr) - 1600) / 400 : 0)

/* number of leap years between year 1 and this year, not inclusive */
#define	leap_years_since_year_1(yr) \
	((yr) / 4 - centuries_since_1700(yr) + quad_centuries_since_1700(yr))

I 7
int julian;

I 13
void	ascii_day __P((char *, int));
void	center __P((char *, int, int));
void	day_array __P((int, int, int *));
int	day_in_week __P((int, int, int));
int	day_in_year __P((int, int, int));
void	j_yearly __P((int));
void	monthly __P((int, int));
void	trim_trailing_spaces __P((char *));
void	usage __P((void));
void	yearly __P((int));

int
E 13
E 7
E 5
main(argc, argv)
D 5
char *argv[];
E 5
I 5
	int argc;
	char **argv;
E 5
{
I 6
D 13
	extern char *optarg;
	extern int optind;
E 13
E 6
D 5
	register y, i, j;
	int m;
E 5
I 5
	struct tm *local_time;
D 13
	time_t now, time();
E 13
I 13
	time_t now;
E 13
D 6
	int month, year;
E 6
I 6
	int ch, month, year, yflag;
E 6
E 5

D 4
	if(argc < 2) {
		printf("usage: cal [month] year\n");
		exit(0);
	}
E 4
D 5
	if(argc == 2)
		goto xlong;
I 4
	/*
	 * print out just month
	 */
	if(argc < 2) {			/* current month */
		time_t t;
		struct tm *tm;
E 4

D 4
/*
 *	print out just month
 */

	m = number(argv[1]);
	if(m<1 || m>12)
		goto badarg;
	y = number(argv[2]);
	if(y<1 || y>9999)
		goto badarg;
E 4
I 4
		t = time(0);
		tm = localtime(&t);
		m = tm->tm_mon + 1;
		y = tm->tm_year + 1900;
	} else {
		m = atoi(argv[1]);
		if(m<1 || m>12) {
			fprintf(stderr, "cal: %s: Bad month.\n", argv[1]);
E 5
I 5
D 6
	++argv;
E 6
I 6
	yflag = 0;
D 7
	while ((ch = getopt(argc, argv, "y")) != EOF)
E 7
I 7
	while ((ch = getopt(argc, argv, "jy")) != EOF)
E 7
		switch(ch) {
I 7
		case 'j':
			julian = 1;
			break;
E 7
		case 'y':
			yflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

I 9
	month = 0;
E 9
E 6
	switch(argc) {
D 6
	case 3:
E 6
I 6
	case 2:
E 6
D 13
		if ((month = atoi(*argv++)) <= 0 || month > 12) {
D 9
			(void)fprintf(stderr, "cal: illegal month value.\n");
E 9
I 9
			(void)fprintf(stderr,
			    "cal: illegal month value: use 0-12\n");
E 9
E 5
			exit(1);
		}
E 13
I 13
		if ((month = atoi(*argv++)) < 1 || month > 12)
			errx(1, "illegal month value: use 1-12");
E 13
D 5
		y = atoi(argv[2]);
		if(y<1 || y>9999) {
			fprintf(stderr, "cal: %s: Bad year.\n", argv[2]);
			exit(2);
E 5
I 5
		/* FALLTHROUGH */
D 6
	case 2:
E 6
I 6
	case 1:
E 6
D 13
		if ((year = atoi(*argv)) <= 0 || year > 9999) {
D 9
			(void)fprintf(stderr, "cal: illegal year value.\n");
E 9
I 9
			(void)fprintf(stderr,
			    "cal: illegal year value: use 0-9999\n");
E 9
			exit(1);
E 5
		}
E 13
I 13
		if ((year = atoi(*argv)) < 1 || year > 9999)
			errx(1, "illegal year value: use 1-9999");
E 13
I 5
		break;
D 6
	case 1:
E 6
I 6
	case 0:
E 6
		(void)time(&now);
		local_time = localtime(&now);
D 6
		month = local_time->tm_mon + 1;
E 6
		year = local_time->tm_year + 1900;
I 6
		if (!yflag)
			month = local_time->tm_mon + 1;
E 6
		break;
	default:
D 6
		(void)fprintf(stderr, "usage: cal [[month] year]\n");
		exit(1);
E 6
I 6
		usage();
E 6
E 5
	}
I 9

E 9
E 4
D 5
	printf("   %s %u\n", smon[m-1], y);
	printf("%s\n", dayw);
	cal(m, y, string, 24);
	for(i=0; i<6*24; i+=24)
		pstr(string+i, 24);
E 5
I 5
	if (month)
D 7
		print_monthly_calendar(month, year);
E 7
I 7
		monthly(month, year);
	else if (julian)
		j_yearly(year);
E 7
	else
D 7
		print_yearly_calendar(year);
E 7
I 7
		yearly(year);
E 7
E 5
	exit(0);
D 5

D 4
/*
 *	print out complete year
 */

E 4
xlong:
D 4
	y = number(argv[1]);
	if(y<1 || y>9999)
		goto badarg;
E 4
I 4
	/*
	 * print out complete year
	 */
	y = atoi(argv[1]);
	if(y<1 || y>9999) {
		fprintf(stderr, "cal: %s: Bad year.\n", argv[1]);
		exit(2);
	}
E 4
	printf("\n\n\n");
	printf("				%u\n", y);
	printf("\n");
	for(i=0; i<12; i+=3) {
		for(j=0; j<6*72; j++)
			string[j] = '\0';
		printf("	 %.3s", smon[i]);
		printf("			%.3s", smon[i+1]);
		printf("		       %.3s\n", smon[i+2]);
		printf("%s   %s   %s\n", dayw, dayw, dayw);
		cal(i+1, y, string, 72);
		cal(i+2, y, string+23, 72);
		cal(i+3, y, string+46, 72);
		for(j=0; j<6*72; j+=72)
			pstr(string+j, 72);
	}
	printf("\n\n\n");
	exit(0);
E 5
D 4

badarg:
	printf("Bad argument\n");
}

number(str)
char *str;
{
	register n, c;
	register char *s;

	n = 0;
	s = str;
	while(c = *s++) {
		if(c<'0' || c>'9')
			return(0);
		n = n*10 + c-'0';
	}
	return(n);
E 4
}

D 5
pstr(str, n)
char *str;
E 5
I 5
D 7
print_monthly_calendar(month, year)
E 7
I 7
#define	DAY_LEN		3		/* 3 spaces per day */
#define	J_DAY_LEN	4		/* 4 spaces per day */
#define	WEEK_LEN	20		/* 7 * 3 - one space at the end */
#define	J_WEEK_LEN	27		/* 7 * 4 - one space at the end */
#define	HEAD_SEP	2		/* spaces between day headings */
D 9
#define	J_HEAD_SEP	3
E 9
I 9
#define	J_HEAD_SEP	2
E 9

I 13
void
E 13
monthly(month, year)
E 7
	int month, year;
E 5
{
D 5
	register i;
	register char *s;
E 5
I 5
D 13
	register int col, row;
	register char *p;
D 7
	int days[42];
E 7
I 7
D 9
	int len, days[42];
E 9
I 9
	int len, days[MAXDAYS];
E 9
E 7
	char lineout[30];
E 13
I 13
	int col, row, len, days[MAXDAYS];
	char *p, lineout[30];
E 13
E 5

D 5
	s = str;
	i = n;
	while(i--)
		if(*s++ == '\0')
			s[-1] = ' ';
	i = n+1;
	while(i--)
		if(*--s != ' ')
			break;
	s[1] = '\0';
	printf("%s\n", str);
E 5
I 5
D 7
	generate_day_array(month, year, days);
	(void)printf("   %s %d\n%s\n",
	    month_names[month - 1], year, day_headings);
E 7
I 7
	day_array(month, year, days);
	len = sprintf(lineout, "%s %d", month_names[month - 1], year);
	(void)printf("%*s%s\n%s\n",
	    ((julian ? J_WEEK_LEN : WEEK_LEN) - len) / 2, "",
	    lineout, julian ? j_day_headings : day_headings);
E 7
	for (row = 0; row < 6; row++) {
D 7
		for (col = 0, p = lineout; col < 7; col++, p += 3)
E 7
I 7
		for (col = 0, p = lineout; col < 7; col++,
		    p += julian ? J_DAY_LEN : DAY_LEN)
E 7
			ascii_day(p, days[row * 7 + col]);
I 12
		*p = '\0';
E 12
		trim_trailing_spaces(lineout);
		(void)printf("%s\n", lineout);
	}
E 5
}

I 13
void
E 13
D 5
char	mon[] = {
	0,
	31, 29, 31, 30,
	31, 30, 31, 31,
	30, 31, 30, 31,
};

cal(m, y, p, w)
char *p;
E 5
I 5
D 7
print_yearly_calendar(year)
E 7
I 7
j_yearly(year)
E 7
	int year;
E 5
{
D 5
	register d, i;
	register char *s;
E 5
I 5
D 13
	register int col, *dp, i, month, row, which_cal;
	register char *p;
E 13
I 13
	int col, *dp, i, month, row, which_cal;
E 13
D 9
	int days[12][42];
E 9
I 9
	int days[12][MAXDAYS];
E 9
D 13
	char lineout[80];
E 13
I 13
	char *p, lineout[80];
E 13
E 5

D 5
	s = p;
	d = jan1(y);
	mon[2] = 29;
	mon[9] = 30;

	switch((jan1(y+1)+7-d)%7) {

	/*
	 *	non-leap year
	 */
	case 1:
		mon[2] = 28;
		break;

	/*
	 *	1752
	 */
	default:
		mon[9] = 19;
		break;

	/*
	 *	leap year
	 */
	case 2:
		;
	}
	for(i=1; i<m; i++)
		d += mon[i];
	d %= 7;
	s += 3*d;
	for(i=1; i<=mon[m]; i++) {
		if(i==3 && mon[m]==19) {
			i += 11;
			mon[m] += 11;
E 5
I 5
D 7
	(void)printf("\n\n\n\t\t\t\t%d\n\n", year);
E 7
I 7
	(void)sprintf(lineout, "%d", year);
	center(lineout, J_WEEK_LEN * 2 + J_HEAD_SEP, 0);
	(void)printf("\n\n");
E 7
	for (i = 0; i < 12; i++)
D 7
		generate_day_array(i + 1, year, &days[i][0]);
E 7
I 7
D 9
		day_array(i + 1, year, &days[i][0]);
E 9
I 9
		day_array(i + 1, year, days[i]);
E 9
E 7
	(void)memset(lineout, ' ', sizeof(lineout) - 1);
	lineout[sizeof(lineout) - 1] = '\0';
D 7
	for (month = 0; month < 12; month += 3) {
		(void)printf("\t %.3s\t\t\t%.3s\t\t       %.3s\n",
		    month_names[month], month_names[month + 1],
		    month_names[month + 2]);
		for (i = 0; i < 3; i++) {
			(void)printf("%s", day_headings);
			if (i < 2)
				(void)printf("   ");
E 7
I 7
	for (month = 0; month < 12; month += 2) {
		center(month_names[month], J_WEEK_LEN, J_HEAD_SEP);
		center(month_names[month + 1], J_WEEK_LEN, 0);
		(void)printf("\n%s%*s%s\n", j_day_headings, J_HEAD_SEP, "",
		    j_day_headings);
		for (row = 0; row < 6; row++) {
			for (which_cal = 0; which_cal < 2; which_cal++) {
				p = lineout + which_cal * (J_WEEK_LEN + 2);
				dp = &days[month + which_cal][row * 7];
				for (col = 0; col < 7; col++, p += J_DAY_LEN)
					ascii_day(p, *dp++);
			}
I 12
			*p = '\0';
E 12
			trim_trailing_spaces(lineout);
			(void)printf("%s\n", lineout);
E 7
E 5
		}
D 5
		if(i > 9)
			*s = i/10+'0';
		s++;
		*s++ = i%10+'0';
		s++;
		if(++d == 7) {
			d = 0;
			s = p+w;
			p = s;
E 5
I 5
D 7
		(void)printf("\n");
E 7
I 7
	}
	(void)printf("\n");
}

I 13
void
E 13
yearly(year)
	int year;
{
D 13
	register int col, *dp, i, month, row, which_cal;
	register char *p;
E 13
I 13
	int col, *dp, i, month, row, which_cal;
E 13
D 9
	int days[12][42];
E 9
I 9
	int days[12][MAXDAYS];
E 9
D 13
	char lineout[80];
E 13
I 13
	char *p, lineout[80];
E 13

	(void)sprintf(lineout, "%d", year);
	center(lineout, WEEK_LEN * 3 + HEAD_SEP * 2, 0);
	(void)printf("\n\n");
	for (i = 0; i < 12; i++)
D 9
		day_array(i + 1, year, &days[i][0]);
E 9
I 9
		day_array(i + 1, year, days[i]);
E 9
	(void)memset(lineout, ' ', sizeof(lineout) - 1);
	lineout[sizeof(lineout) - 1] = '\0';
	for (month = 0; month < 12; month += 3) {
		center(month_names[month], WEEK_LEN, HEAD_SEP);
		center(month_names[month + 1], WEEK_LEN, HEAD_SEP);
		center(month_names[month + 2], WEEK_LEN, 0);
		(void)printf("\n%s%*s%s%*s%s\n", day_headings, HEAD_SEP,
		    "", day_headings, HEAD_SEP, "", day_headings);
E 7
		for (row = 0; row < 6; row++) {
			for (which_cal = 0; which_cal < 3; which_cal++) {
D 7
				p = lineout + which_cal * 23;
E 7
I 7
				p = lineout + which_cal * (WEEK_LEN + 2);
E 7
				dp = &days[month + which_cal][row * 7];
D 7
				for (col = 0; col < 7; col++, p += 3)
E 7
I 7
				for (col = 0; col < 7; col++, p += DAY_LEN)
E 7
					ascii_day(p, *dp++);
			}
I 12
			*p = '\0';
E 12
			trim_trailing_spaces(lineout);
			(void)printf("%s\n", lineout);
E 5
		}
	}
I 5
D 7
	(void)printf("\n\n\n");
E 7
I 7
	(void)printf("\n");
E 7
E 5
}

/*
D 5
 *	return day of the week
 *	of jan 1 of given year
E 5
I 5
D 7
 * generate_day_array --
E 7
I 7
 * day_array --
E 7
 *	Fill in an array of 42 integers with a calendar.  Assume for a moment
 *	that you took the (maximum) 6 rows in a calendar and stretched them
 *	out end to end.  You would have 42 numbers or spaces.  This routine
 *	builds that array for any month from Jan. 1 through Dec. 9999.
E 5
 */
I 13
void
E 13
D 5

jan1(yr)
E 5
I 5
D 7
generate_day_array(month, year, days)
	int month, year, *days;
E 7
I 7
day_array(month, year, days)
D 13
	register int *days;
E 13
	int month, year;
I 13
	int *days;
E 13
E 7
E 5
{
D 5
	register y, d;
E 5
I 5
D 7
	register int i, day, dw, dm;
E 7
I 7
D 9
	register int i, day, dw, dm, *p;
E 9
I 9
D 13
	register int i, day, dw, dm;
E 13
I 13
	int day, dw, dm;
E 13
E 9
E 7
E 5

I 5
D 9
	dm = days_in_month[leap_year(year)][month];
	dw = day_in_week(1, month, year);
E 9
D 7
	if (month == 9 && year == 1752)
E 7
I 7
	if (month == 9 && year == 1752) {
D 9
		p = julian ? j_sep1752 : sep1752;
E 7
		for (i = 0; i < 42; i++)
D 7
			days[i] = sep1752[i];
	else {
		for (i = 0; i < 42; i++)
			days[i] = SPACE;
		for (day = 1, i = dw; day <= dm; ++day, ++i)
			days[i] = day;
E 7
I 7
			*days++ = *p++;
E 9
I 9
D 13
		bcopy(julian ? j_sep1752 : sep1752,
		    days, MAXDAYS * sizeof(int));
E 13
I 13
		memmove(days,
			julian ? j_sep1752 : sep1752, MAXDAYS * sizeof(int));
E 13
E 9
		return;
E 7
	}
I 7
D 9
	for (i = 42, p = days; i--;)
		*p++ = SPACE;
E 9
I 9
D 13
	bcopy(empty, days, MAXDAYS * sizeof(int));
E 13
I 13
	memmove(days, empty, MAXDAYS * sizeof(int));
E 13
	dm = days_in_month[leap_year(year)][month];
	dw = day_in_week(1, month, year);
E 9
	day = julian ? day_in_year(1, month, year) : 1;
	while (dm--)
		days[dw++] = day++;
E 7
}

E 5
/*
D 5
 *	normal gregorian calendar
 *	one extra day per four years
E 5
I 5
 * day_in_year --
 *	return the 1 based day number within the year
E 5
 */
I 13
int
E 13
I 5
day_in_year(day, month, year)
D 13
	register int day, month;
	int year;
E 13
I 13
	int day, month, year;
E 13
{
D 13
	register int i, leap;
E 13
I 13
	int i, leap;
E 13
E 5

D 5
	y = yr;
	d = 4+y+(y+3)/4;
E 5
I 5
	leap = leap_year(year);
	for (i = 1; i < month; i++)
		day += days_in_month[leap][i];
D 13
	return(day);
E 13
I 13
	return (day);
E 13
}
E 5

/*
D 5
 *	julian calendar
 *	regular gregorian
 *	less three days per 400
E 5
I 5
 * day_in_week
 *	return the 0 based day number for any date from 1 Jan. 1 to
 *	31 Dec. 9999.  Assumes the Gregorian reformation eliminates
 *	3 Sep. 1752 through 13 Sep. 1752.  Returns Thursday for all
 *	missing days.
E 5
 */
I 13
int
E 13
I 5
day_in_week(day, month, year)
	int day, month, year;
{
	long temp;
E 5

D 5
	if(y > 1800) {
		d -= (y-1701)/100;
		d += (y-1601)/400;
	}
E 5
I 5
	temp = (long)(year - 1) * 365 + leap_years_since_year_1(year - 1)
	    + day_in_year(day, month, year);
	if (temp < FIRST_MISSING_DAY)
D 13
		return((temp - 1 + SATURDAY) % 7);
E 13
I 13
		return ((temp - 1 + SATURDAY) % 7);
E 13
	if (temp >= (FIRST_MISSING_DAY + NUMBER_MISSING_DAYS))
D 13
		return(((temp - 1 + SATURDAY) - NUMBER_MISSING_DAYS) % 7);
	return(THURSDAY);
E 13
I 13
		return (((temp - 1 + SATURDAY) - NUMBER_MISSING_DAYS) % 7);
	return (THURSDAY);
E 13
}
E 5

I 13
void
E 13
D 5
/*
 *	great calendar changeover instant
 */
E 5
I 5
ascii_day(p, day)
D 13
	register char *p;
	register int day;
E 13
I 13
	char *p;
	int day;
E 13
{
D 7
	register int ten;
E 7
I 7
D 13
	register int display, val;
E 13
I 13
	int display, val;
E 13
I 9
	static char *aday[] = {
		"",
D 10
		" 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ",
		" 8 ", " 9 ", "10 ", "11 ", "12 ", "13 ", "14 ",
		"15 ", "16 ", "17 ", "18 ", "19 ", "20 ", "21 ",
		"22 ", "23 ", "24 ", "25 ", "26 ", "27 ", "28 ",
		"29 ", "30 ", "31 ",
E 10
I 10
		" 1", " 2", " 3", " 4", " 5", " 6", " 7",
		" 8", " 9", "10", "11", "12", "13", "14",
		"15", "16", "17", "18", "19", "20", "21",
		"22", "23", "24", "25", "26", "27", "28",
		"29", "30", "31",
E 10
	};
E 9
E 7
E 5

D 5
	if(y > 1752)
		d += 3;
E 5
I 5
	if (day == SPACE) {
D 7
		*p++ = ' ';
		*p++ = ' ';
E 7
I 7
D 9
		memset(p, ' ', julian ? 4 : 3);
E 9
I 9
		memset(p, ' ', julian ? J_DAY_LEN : DAY_LEN);
E 9
		return;
E 7
	}
D 7
	else {
		ten = day / 10;
		*p++ = ten ? ten + '0' : ' ';
		*p++ = day % 10 + '0';
E 7
I 7
D 9
	display = 0;
	if (julian) {
		if (val = day / 100) {
			day %= 100;
			*p++ = val + '0';
			display = 1;
		} else
			*p++ = ' ';
E 9
I 9
D 10
	if (!julian) {
E 10
I 10
	if (julian) {
		if (val = day / 100) {
			day %= 100;
			*p++ = val + '0';
			display = 1;
		} else {
			*p++ = ' ';
			display = 0;
		}
		val = day / 10;
		if (val || display)
			*p++ = val + '0';
		else
			*p++ = ' ';
		*p++ = day % 10 + '0';
	} else {
E 10
		*p++ = aday[day][0];
		*p++ = aday[day][1];
D 10
		*p = aday[day][2];
		return;
E 10
	}
D 10
	if (val = day / 100) {
		day %= 100;
		*p++ = val + '0';
		display = 1;
	} else {
		*p++ = ' ';
		display = 0;
E 9
E 7
	}
I 7
	val = day / 10;
	if (val || display)
		*p++ = val + '0';
	else
		*p++ = ' ';
	*p++ = day % 10 + '0';
E 10
E 7
	*p = ' ';
}
E 5

I 13
void
E 13
D 5
	return(d%7);
E 5
I 5
trim_trailing_spaces(s)
D 13
	register char *s;
E 13
I 13
	char *s;
E 13
{
D 13
	register char *p;
E 13
I 13
	char *p;
E 13

D 13
	for (p = s; *p; ++p);
	while (p > s && isspace(*--p));
E 13
I 13
	for (p = s; *p; ++p)
		continue;
	while (p > s && isspace(*--p))
		continue;
E 13
	if (p > s)
		++p;
	*p = '\0';
I 6
}

I 13
void
E 13
I 7
center(str, len, separate)
	char *str;
D 13
	register int len;
E 13
I 13
	int len;
E 13
	int separate;
{
I 13

E 13
	len -= strlen(str);
	(void)printf("%*s%s%*s", len / 2, "", str, len / 2 + len % 2, "");
	if (separate)
		(void)printf("%*s", separate, "");
}

I 13
void
E 13
E 7
usage()
{
I 13

E 13
D 7
	(void)fprintf(stderr, "usage: cal [-y] [[month] year]\n");
E 7
I 7
	(void)fprintf(stderr, "usage: cal [-jy] [[month] year]\n");
E 7
	exit(1);
E 6
E 5
}
E 1
