h30068
s 00001/00001/00192
d D 8.4 95/04/21 09:57:07 eric 49 48
c update copyright notice
e
s 00008/00008/00185
d D 8.3 94/08/07 14:00:34 eric 48 47
c change name of TZ_TYPE values -- the USE_ was bogus
e
s 00051/00005/00142
d D 8.2 94/08/07 12:27:17 eric 47 46
c include alpha time zone as 822 comment in Date: line
e
s 00002/00002/00145
d D 8.1 93/06/07 10:29:11 bostic 46 45
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00045/00147
d D 6.9 93/06/05 17:07:55 eric 45 44
c lint-style cleanup
e
s 00000/00001/00192
d D 6.8 93/03/01 06:53:34 eric 44 43
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00000/00329/00193
d D 6.7 93/02/21 13:45:37 eric 43 42
c change $d to be current date, not origination date
e
s 00011/00011/00511
d D 6.6 93/02/18 20:22:21 eric 42 41
c move the meta-characters from C0 into C1 space
e
s 00086/00044/00436
d D 6.5 93/02/16 18:29:53 eric 41 40
c clean up log levels; allow IDA-style split header/envelope rewriting;
c extend arpatounix with more zones (but is this even needed?)
e
s 00001/00001/00479
d D 6.4 93/01/22 17:20:17 eric 40 39
c fix -e compat flag; a few compilation warnings; improve error messages
e
s 00000/00003/00480
d D 6.3 93/01/21 15:18:35 eric 39 38
c more environment problems; limit resource exhaustion; fix incorrect
c name in Connection timed out message; ANSI C fixes; log message sender on
c returned mail during queue run; count recipients properly; fix YP code;
c diagnose "message timed out" properly
e
s 00333/00003/00150
d D 6.2 93/01/18 14:32:19 eric 38 37
c implement arpatounix; log more info; allow nested $?...$|...$.;
c POSIX compatibility; handle SMTP MAIL command errors properly;
c do early diagnosis of .cf errors; adjust checkpointing; misc bugs
e
s 00000/00000/00153
d D 6.1 92/12/21 16:08:24 eric 37 36
c Release 6
e
s 00003/00011/00150
d D 5.13 92/09/21 17:07:56 eric 36 35
c duh....  easier way to handle four digit years
e
s 00011/00001/00150
d D 5.12 92/08/09 15:21:08 eric 35 34
c represent arpa dates with four digit years instead of two digits
e
s 00001/00011/00150
d D 5.11 90/06/01 19:00:18 bostic 34 33
c new copyright notice
e
s 00046/00114/00115
d D 5.10 89/01/08 10:17:13 bostic 33 32
c arpadate to make everyone happy (except Eric)
e
s 00011/00009/00218
d D 5.9 88/06/30 14:58:19 bostic 32 31
c install approved copyright notice
e
s 00000/00015/00227
d D 5.8 88/04/01 16:50:36 bostic 31 30
c remove V6 #ifdefs
e
s 00016/00010/00226
d D 5.7 88/03/13 19:51:29 bostic 30 29
c add Berkeley specific header
e
s 00002/00004/00234
d D 5.6 88/03/13 18:21:56 bostic 29 28
c replace sameword with strcasecmp
e
s 00001/00002/00237
d D 5.5 87/03/18 15:27:05 bostic 28 27
c removed timezone call; tm structure now has zone entry.
e
s 00009/00008/00230
d D 5.4 86/01/09 15:18:50 eric 27 26
c apparently European timezones were wrong; thanks to Piet Beertema
c <mcvax!piet@seismo.CSS.GOV> for this one
e
s 00002/00000/00236
d D 5.3 85/06/08 10:26:40 eric 26 25
m 
c lint for 4.3 release
e
s 00000/00002/00236
d D 5.2 85/06/07 22:00:54 miriam 25 24
m 
c Resolve duplicate SccsId
e
s 00014/00000/00224
d D 5.1 85/06/07 14:28:06 dist 24 23
m 
c Add copyright
e
s 00037/00015/00187
d D 4.4 84/08/11 17:47:56 eric 23 22
m 
c Assorted changes from Guy Harris <rlgvax!guy>: mostly lint & USG
e
s 00052/00030/00150
d D 4.3 83/10/01 16:57:03 eric 22 21
m 
c clean up error handling in general; make sure that something gets logged
c in the transcript if the connection cannot be established; clean up Teus
c Hagen's mod to arpadate.c to match the sendmail coding style.
e
s 00040/00002/00140
d D 4.2 83/09/27 12:18:09 karels 21 20
m 
c mods for european dates (from mcvax!teus)
e
s 00000/00000/00142
d D 4.1 83/07/25 19:43:32 eric 20 19
m 
c 4.2 release version
e
s 00008/00009/00134
d D 3.13 83/07/13 10:37:46 eric 19 18
m 
c Delete "load limiting" for SMTP connections (a bad ethernet board can
c hang up all incoming mail); use sfgets in collect (same reason); check
c for I/O error in collect (from Bill Nowicki); switch date format to
c RFC822 style.
e
s 00001/00001/00142
d D 3.12 83/07/01 23:04:49 wnj 18 17
m 
c 
e
s 00003/00003/00140
d D 3.11 83/01/12 08:56:46 eric 17 16
m 144
c fix date format to be truly RFC822
e
s 00001/00000/00142
d D 3.10 82/11/13 18:13:03 eric 16 15
m 070
c move configuration to conf.h
e
s 00001/00001/00141
d D 3.9 81/12/06 12:37:12 eric 15 14
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00017/00081/00125
d D 3.8 81/12/05 14:13:28 eric 14 13
c insert SMTP "Mail-From:" line.
e
s 00001/00002/00205
d D 3.7 81/09/24 10:30:10 eric 13 11
c changes to work under a V6 system -- mostly compilation flags
e
s 00001/00000/00207
d D 3.6.1.1 81/09/23 18:22:39 eric 12 11
c break some configuration into conf.h -- simplifies makefile changes
c on different machines.  But there are still conditional libraries, so
c this may not be a good idea.....
e
s 00019/00008/00188
d D 3.6 81/09/06 19:47:35 eric 11 10
c cleanup, commenting, linting, etc.
e
s 00019/00018/00177
d D 3.5 81/04/20 14:45:00 eric 10 9
c change format to fit Kurt's standard
e
s 00073/00010/00122
d D 3.4 81/03/27 14:30:37 eric 9 8
c make more readable dates
e
s 00005/00000/00127
d D 3.3 81/03/11 10:45:01 eric 8 7
c general cleanup, esp. macro processor
e
s 00002/00002/00125
d D 3.2 81/03/07 14:25:11 eric 7 6
c ----- delivermail ==> postbox -----
e
s 00092/00016/00035
d D 3.1 81/03/04 09:33:42 eric 6 5
c install fancy header stuff
e
s 00000/00000/00051
d D 2.1 80/11/05 11:00:14 eric 5 4
c release 2
e
s 00002/00000/00049
d D 1.4 80/10/21 12:20:08 eric 4 3
c clean up type botches
e
s 00000/00010/00049
d D 1.3 80/08/02 13:48:17 eric 3 2
c cleaned up comments
e
s 00002/00000/00057
d D 1.2 80/07/25 22:02:32 eric 2 1
c add ID keywords
e
s 00057/00000/00000
d D 1.1 80/06/23 08:23:18 eric 1 0
e
u
U
f b 
f i 
t
T
I 24
/*
I 32
D 49
 * Copyright (c) 1983 Eric P. Allman
E 49
I 49
 * Copyright (c) 1983, 1995 Eric P. Allman
E 49
E 32
D 30
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 30
I 30
D 46
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 46
I 46
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 46
 *
D 34
 * Redistribution and use in source and binary forms are permitted
D 32
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 32
I 32
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
E 34
I 34
 * %sccs.include.redist.c%
E 34
E 32
 */
E 30

#ifndef lint
D 30
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 30
I 30
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 30

E 24
I 16
D 38
# include "conf.h"
I 23
D 33
# ifdef USG
E 33
# include <time.h>
E 38
I 38
# include "sendmail.h"
E 38
D 33
# else
E 23
E 16
I 12
# include "conf.h"
E 12
I 1
D 18
# include <time.h>
E 18
I 18
# include <sys/time.h>
E 33
E 18
I 6
D 31
# ifndef V6
E 31
D 44
# include <sys/types.h>
E 44
D 33
# include <sys/timeb.h>
D 23
# endif
E 23
I 23
D 31
# endif V6
E 31
# endif USG
E 33
E 23
I 13
D 38
# include "useful.h"
E 38
E 13
E 6

I 2
D 15
static char SccsId[] = "%W%	%G%";
E 15
I 15
D 25
SCCSID(%W%	%Y%	%G%);
E 15

E 25
I 23
D 31
# ifdef V6
# define OLDTIME
# endif V6
E 31
D 33
# ifdef USG
# define OLDTIME
# endif USG

E 33
E 23
E 2
/*
**  ARPADATE -- Create date in ARPANET format
**
**	Parameters:
D 6
**		none
E 6
I 6
**		ud -- unix style date string.  if NULL, one is created.
E 6
**
**	Returns:
**		pointer to an ARPANET date field
**
**	Side Effects:
**		none
**
**	WARNING:
**		date is stored in a local buffer -- subsequent
**		calls will overwrite.
I 8
**
**	Bugs:
**		Timezone is computed from local time, rather than
**		from whereever (and whenever) the message was sent.
**		To do better is very hard.
I 11
**
**		Some sites are now inserting the timezone into the
**		local date.  This routine should figure out what
**		the format is and work appropriately.
E 11
E 8
D 3
**
**	Requires:
**		time (sys)
**		ctime (sys)
**		strcpy (sys)
**		strcat (sys)
**		localtime (sys)
**
**	History:
**		1/15/80 -- written.
E 3
*/
D 13

I 6
D 11
# ifdef V6
# define DST_NAME	"PDT"
# define STD_NAME	"PST"
# endif

E 11
# define NULL		0
E 13

I 47
#ifndef TZNAME_MAX
# define TZNAME_MAX	50	/* max size of timezone */
#endif

/* values for TZ_TYPE */
#define TZ_NONE		0	/* no character timezone support */
D 48
#define TZ_USE_TM_NAME	1	/* use tm->tm_name */
#define TZ_USE_TM_ZONE	2	/* use tm->tm_zone */
#define TZ_USE_TZNAME	3	/* use tzname[] */
#define TZ_USE_TIMEZONE	4	/* use timezone() */
E 48
I 48
#define TZ_TM_NAME	1	/* use tm->tm_name */
#define TZ_TM_ZONE	2	/* use tm->tm_zone */
#define TZ_TZNAME	3	/* use tzname[] */
#define TZ_TIMEZONE	4	/* use timezone() */
E 48

E 47
I 9
D 14
struct cvttab
{
	char	*old;
	char	*new;
};

struct cvttab	DowTab[] =
{
	"Sun",		"Sunday",
	"Mon",		"Monday",
	"Tue",		"Tuesday",
	"Wed",		"Wednesday",
	"Thu",		"Thursday",
	"Fri",		"Friday",
	"Sat",		"Saturday",
	NULL,		NULL
};

struct cvttab	MonthTab[] =
{
	"Jan",		"January",
	"Feb",		"February",
	"Mar",		"March",
	"Apr",		"April",
	"May",		"May",
	"Jun",		"June",
	"Jul",		"July",
	"Aug",		"August",
	"Sep",		"September",
	"Oct",		"October",
	"Nov",		"November",
	"Dec",		"December",
	NULL,		NULL
};

E 14
E 9
E 6
I 4
char *
E 4
D 6
arpadate()
E 6
I 6
arpadate(ud)
	register char *ud;
E 6
{
D 6
	register char *ud;	/* the unix date */
	long t;
	extern struct tm *localtime();
E 6
	register char *p;
I 6
	register char *q;
I 33
	register int off;
	register int i;
	register struct tm *lt;
	time_t t;
	struct tm gmt;
E 33
E 6
D 47
	static char b[40];
E 47
I 47
	char *tz;
	static char b[43 + TZNAME_MAX];
E 47
I 33
D 39
	extern struct tm *localtime(), *gmtime();
E 33
I 4
	extern char *ctime();
I 6
D 33
	register int i;
I 9
D 14
	struct cvttab *c;
E 14
E 9
	extern struct tm *localtime();
I 22
	extern bool fconvert();
E 22
D 23
# ifdef V6
E 23
I 23
# ifdef OLDTIME
E 23
	long t;
I 11
D 23
	extern char *StdTimezone, *DstTimezone;
E 23
	extern long time();
E 11
D 23
# else
E 23
I 23
# else OLDTIME
E 23
	struct timeb t;
	extern struct timeb *ftime();
D 28
	extern char *timezone();
E 28
D 23
# endif
E 23
I 23
# endif OLDTIME
D 31
# ifdef V6
	extern char *StdTimezone, *DstTimezone;
# endif V6
E 31
# ifdef USG
	extern char *tzname[2];
# endif USG
E 33
I 33
	extern time_t time();
E 39
E 33
E 23
E 6
E 4

I 11
	/*
	**  Get current time.
	**	This will be used if a null argument is passed and
	**	to resolve the timezone.
	*/

E 11
I 6
D 23
# ifdef V6
E 23
I 23
D 33
# ifdef OLDTIME
E 33
E 23
E 6
D 11
	time(&t);
E 11
I 11
	(void) time(&t);
E 11
D 6
	ud = ctime(&t);
E 6
I 6
	if (ud == NULL)
		ud = ctime(&t);
D 33
# else
	ftime(&t);
	if (ud == NULL)
		ud = ctime(&t.time);
D 23
# endif
E 23
I 23
# endif OLDTIME
E 33
E 23
E 6

I 11
	/*
	**  Crack the UNIX date line in a singularly unoriginal way.
	*/

E 11
D 6
	ud[3] = ud[7] = ud[10] = ud[19] = ud[24] = '\0';
E 6
I 6
	q = b;

I 19
	p = &ud[0];		/* Mon */
	*q++ = *p++;
	*q++ = *p++;
	*q++ = *p++;
	*q++ = ',';
	*q++ = ' ';

E 19
D 9
	p = &ud[0];		/* Mon */
	*q++ = *p++;
	*q++ = *p++;
	*q++ = *p++;
	*q++ = ',';
	*q++ = ' ';
E 9
I 9
D 10
	p = NULL;		/* Mon */
	for (c = DowTab; c->old != NULL; c++)
	{
		if (strncmp(&ud[0], c->old, 3) == 0)
		{
			p = c->new;
			break;
		}
	}
	if (p != NULL)
	{
		while (*p != '\0')
			*q++ = *p++;
		*q++ = ',';
		*q++ = ' ';
	}
E 9

E 10
E 6
	p = &ud[8];		/* 16 */
	if (*p == ' ')
		p++;
D 6
	strcpy(b, p);
	strcat(b, " ");
	strcat(b, &ud[4]);	/* Sep */
	strcat(b, " ");
	strcat(b, &ud[20]);	/* 1979 */
	strcat(b, " ");
	strcat(b, &ud[11]);	/* 01:03:52 */
E 6
I 6
	else
		*q++ = *p++;
	*q++ = *p++;
D 7
	*q++ = '-';
E 7
I 7
D 14
	*q++ = ' ';
E 14
I 14
D 17
	*q++ = '-';
E 17
I 17
	*q++ = ' ';
E 17
E 14
E 7

D 9
	p = &ud[4];		/* Sep */
	*q++ = *p++;
	*q++ = *p++;
	*q++ = *p++;
E 9
I 9
D 14
	p = NULL;		/* Sep */
	for (c = MonthTab; c->old != NULL; c++)
	{
		if (strncmp(&ud[4], c->old, 3) == 0)
		{
			p = c->new;
			break;
		}
	}
	if (p != NULL)
	{
		while (*p != '\0')
			*q++ = *p++;
	}
	else
	{
		p = &ud[4];
		*q++ = *p++;
		*q++ = *p++;
		*q++ = *p++;
	}
E 9
D 7
	*q++ = '-';
E 7
I 7
	*q++ = ' ';
E 14
I 14
	p = &ud[4];		/* Sep */
	*q++ = *p++;
	*q++ = *p++;
	*q++ = *p++;
D 17
	*q++ = '-';
E 17
I 17
	*q++ = ' ';
E 17
E 14
E 7

D 14
	p = &ud[20];		/* 1979 */
	for (i = 4; i > 0; i--)
		*q++ = *p++;
E 14
I 14
D 19
	p = &ud[22];		/* 1979 */
E 19
I 19
D 35
	p = &ud[22];		/* 79 */
E 35
I 35
D 36
	p = &ud[22];		/* 1979 */
	if (*p >= '6')
	{
		*q++ = '1';
		*q++ = '9';
	}
	else
	{
		*q++ = '2';
		*q++ = '0';
	}
E 36
I 36
	p = &ud[20];		/* 1979 */
	*q++ = *p++;
	*q++ = *p++;
E 36
E 35
E 19
	*q++ = *p++;
	*q++ = *p++;
E 14
	*q++ = ' ';

	p = &ud[11];		/* 01:03:52 */
D 10
	for (i = 8; i > 0; i--)
E 10
I 10
D 14
	for (i = 5; i > 0; i--)
E 14
I 14
	for (i = 8; i > 0; i--)
E 14
E 10
		*q++ = *p++;

D 33
				/* -PST or -PDT */
D 31
# ifdef V6
E 6
	if (localtime(&t)->tm_isdst)
D 6
		strcat(b, "-PDT");
E 6
I 6
D 11
		p = DST_NAME;
E 11
I 11
		p = DstTimezone;
E 11
E 6
	else
D 6
		strcat(b, "-PST");
E 6
I 6
D 11
		p = STD_NAME;
E 11
I 11
		p = StdTimezone;
E 11
# else
E 31
I 23
# ifdef USG
	if (localtime(&t)->tm_isdst)
		p = tzname[1];
	else
		p = tzname[0];
# else
E 23
D 28
	p = timezone(t.timezone, localtime(&t.time)->tm_isdst);
E 28
I 28
	p = localtime(&t.time)->tm_zone;
E 28
I 23
# endif USG
E 23
D 31
# endif V6
E 31
D 21
	if (p[3] != '\0')
E 21
I 21
D 22
	if ( (strncmp(p,"GMT",3)==0 || strncmp(p,"gmt",3)==0) && p[3] != '\0')
E 22
I 22
	if ((strncmp(p, "GMT", 3) == 0 || strncmp(p, "gmt", 3) == 0) &&
	    p[3] != '\0')
E 22
E 21
	{
		/* hours from GMT */
		p += 3;
		*q++ = *p++;
		if (p[1] == ':')
			*q++ = '0';
		else
			*q++ = *p++;
		*q++ = *p++;
		p++;		/* skip ``:'' */
		*q++ = *p++;
		*q++ = *p++;
I 21
		*q = '\0';
E 21
	}
D 22
	else
I 21
	if( !fconvert(p,q) )
E 22
I 22
	else if (!fconvert(p, q))
E 22
E 21
	{
D 17
		*q++ = '-';
E 17
I 17
		*q++ = ' ';
E 17
		*q++ = *p++;
		*q++ = *p++;
		*q++ = *p++;
I 21
		*q = '\0';
E 21
I 10
	}
E 33
I 33
	/*
	 * should really get the timezone from the time in "ud" (which
	 * is only different if a non-null arg was passed which is different
	 * from the current time), but for all practical purposes, returning
	 * the current local zone will do (its all that is ever needed).
	 */
	gmt = *gmtime(&t);
	lt = localtime(&t);
E 33
D 19

D 14
	p = NULL;		/* Mon */
	for (c = DowTab; c->old != NULL; c++)
	{
		if (strncmp(&ud[0], c->old, 3) == 0)
		{
			p = c->new;
			break;
		}
	}
	if (p != NULL)
	{
		*q++ = ' ';
		*q++ = '(';
		while (*p != '\0')
			*q++ = *p++;
		*q++ = ')';
E 10
	}
E 14
I 14
	p = &ud[0];		/* Mon */
	*q++ = ' ';
	*q++ = '(';
	*q++ = *p++;
	*q++ = *p++;
	*q++ = *p++;
	*q++ = ')';
E 19
E 14

D 21
	*q = '\0';
E 21
D 14

E 14
E 6
D 33
	return (b);
I 21
}
I 22
/*
**  FCONVERT -- convert foreign timezones to ARPA timezones
**
**	This routine is essentially from Teus Hagen.
**
**	Parameters:
**		a -- timezone as returned from UNIX.
**		b -- place to put ARPA-style timezone.
**
**	Returns:
**		TRUE -- if a conversion was made (and b was filled in).
**		FALSE -- if this is not a recognized local time.
**
**	Side Effects:
**		none.
*/
E 33
I 33
	off = (lt->tm_hour - gmt.tm_hour) * 60 + lt->tm_min - gmt.tm_min;
E 33
E 22

D 22
/* convert foreign identifications to some ARPA interpretable form */
/* with dst we put the time zone one hour ahead */
struct foreign { 
E 22
I 22
D 33
/* UNIX to arpa conversion table */
struct foreign
{
E 22
	char *f_from; 
	char *f_to; 
D 22
} foreign[] = {
	{"eet", " -0200"}, /* eastern europe */
	{"met", " -0100"}, /* middle europe */
	{"wet", " GMT"},   /* western europe, and what for australia? */
	{"eet dst", " -0300"}, /* daylight saving times */
	{"met dst", " -0200"},
	{"wet dst", " -0100"},
	{NULL, NULL}
E 22
};
E 33
I 33
	/* assume that offset isn't more than a day ... */
	if (lt->tm_year < gmt.tm_year)
		off -= 24 * 60;
	else if (lt->tm_year > gmt.tm_year)
		off += 24 * 60;
	else if (lt->tm_yday < gmt.tm_yday)
		off -= 24 * 60;
	else if (lt->tm_yday > gmt.tm_yday)
		off += 24 * 60;
E 33

D 22
fconvert( a, b ) register char *a; char *b;
{	register struct foreign *euptr;
	register char *ptr;
	extern makelower();
E 22
I 22
D 27
static struct foreign Foreign[] =
E 27
I 27
D 33
static struct foreign	Foreign[] =
E 27
{
D 23
	{ "eet",	" -0200" },	/* eastern europe */
	{ "met",	" -0100" },	/* middle europe */
	{ "wet",	" GMT"   },	/* western europe */
	{ "eet dst",	" -0300" },	/* daylight saving times */
	{ "met dst",	" -0200" },
	{ "wet dst",	" -0100" },
E 23
I 23
D 27
	{ "EET",	" -0200" },	/* eastern europe */
	{ "MET",	" -0100" },	/* middle europe */
	{ "WET",	" GMT"   },	/* western europe */
	{ "EET DST",	" -0300" },	/* daylight saving times */
	{ "MET DST",	" -0200" },
	{ "WET DST",	" -0100" },
E 27
I 27
	{ "EET",	"+0200" },	/* eastern europe */
	{ "MET",	"+0100" },	/* middle europe */
	{ "WET",	"GMT"   },	/* western europe */
	{ "EET DST",	"+0300" },	/* daylight saving times */
	{ "MET DST",	"+0200" },
	{ "WET DST",	"+0100" },
E 27
E 23
	{ NULL,		NULL	 }
};
E 33
I 33
	*q++ = ' ';
D 47
	if (off == 0) {
E 47
I 47
	if (off == 0)
	{
E 47
		*q++ = 'G';
		*q++ = 'M';
		*q++ = 'T';
D 47
	} else {
		if (off < 0) {
E 47
I 47
	}
	else
	{
		tz = NULL;
D 48
#if TZ_TYPE == TZ_USE_TM_NAME
E 48
I 48
#if TZ_TYPE == TZ_TM_NAME
E 48
		tz = lt->tm_name;
#endif
D 48
#if TZ_TYPE == TZ_USE_TM_ZONE
E 48
I 48
#if TZ_TYPE == TZ_TM_ZONE
E 48
		tz = lt->tm_zone;
#endif
D 48
#if TZ_TYPE == TZ_USE_TZNAME
E 48
I 48
#if TZ_TYPE == TZ_TZNAME
E 48
		{
			extern char *tzname[];

			tz = tzname[lt->tm_isdst];
		}
#endif
D 48
#if TZ_TYPE == TZ_USE_TIMEZONE
E 48
I 48
#if TZ_TYPE == TZ_TIMEZONE
E 48
		{
			extern char *timezone();

			tz = timezone(off, lt->tm_isdst);
		}
#endif
		if (off < 0)
		{
E 47
			off = -off;
			*q++ = '-';
D 47
		} else
E 47
I 47
		}
		else
E 47
			*q++ = '+';
E 33
E 22

D 22
/* for news:	for ( ptr = a; *ptr; ptr++ )
		if ( isupper(*ptr) )
			*ptr = tolower( *ptr );
*/
	makelower( a );
	for ( euptr = &foreign[0]; euptr->f_from != NULL; euptr++ )
		if ( strcmp(euptr->f_from, a) == 0 )
		{	ptr = euptr->f_to;
			while ( *ptr )
				*b++ = *ptr++;
E 22
I 22
D 33
bool
fconvert(a, b)
	register char *a;
D 29
	char *b;
E 29
I 29
	register char *b;
E 29
{
	register struct foreign *euptr;
	register char *p;
E 33
I 33
		if (off >= 24*60)		/* should be impossible */
			off = 23*60+59;		/* if not, insert silly value */
E 33

D 23
	makelower(a);
E 23
D 33
	for (euptr = Foreign; euptr->f_from != NULL; euptr++)
	{
I 26
D 29
		extern bool sameword();

E 26
D 23
		if (strcmp(euptr->f_from, a) == 0)
E 23
I 23
		if (sameword(euptr->f_from, a))
E 29
I 29
		if (!strcasecmp(euptr->f_from, a))
E 29
E 23
		{
			p = euptr->f_to;
D 27
			while (*p)
E 27
I 27
			*b++ = ' ';
			while (*p != '\0')
E 27
				*b++ = *p++;
E 22
			*b = '\0';
D 22
			return 1;
E 22
I 22
			return (TRUE);
E 22
		}
E 33
I 33
		*q++ = (off / 600) + '0';
		*q++ = (off / 60) % 10 + '0';
		off %= 60;
		*q++ = (off / 10) + '0';
		*q++ = (off % 10) + '0';
I 47
		if (tz != NULL && *tz != '\0')
		{
			*q++ = ' ';
			*q++ = '(';
			while (*tz != '\0')
				*q++ = *tz++;
			*q++ = ')';
		}
E 47
E 33
D 22
	return 0;
E 22
I 22
	}
D 33
	return (FALSE);
E 33
I 33
	*q = '\0';

	return (b);
I 38
}
D 45

/*
**  NEXTATOM -- Return pointer to next atom in header
**		(skip whitespace and comments)
**
**	Parameters:
**		s -- pointer to header string
**
**	Returns:
**		pointer advanced to next non-comment header atom
**
**	Side Effects:
**		none
*/

static char *
nextatom(s)
	char *s;
{
	char *p;

	for (p = s;
	     *p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '(');
	     p++)
	{
		if (*p == '(')
		{
			int nested = 0;

			/* ignore comments */
			p++;
			for (; *p; p++)
			{
				if (*p == '(')
					nested++;
				else if (*p == ')')
					if (!nested)
						break;
					else
						nested--;
			}
		}
	}
	return (p);
}
E 45
D 43

/*
**  ARPATOUNIX -- Convert RFC-822/1123 date-time specification to ctime format.
**
**	Parameters:
**		s -- pointer to date string
**
**	Returns:
**		pointer to a string in ctime format
**
**	Side Effects:
**		Calls asctime() which modifies its static area.
**
**	Syntax:
**		date-time field specification from RFC822
**		as amended by RFC 1123:
**
**			[ day "," ] 1*2DIGIT month 2*4DIGIT \
**			2DIGIT ":" 2DIGIT [ ":" 2DIGIT  ] zone
**
**		Day can be "Mon" "Tue" "Wed" "Thu" "Fri" "Sat" "Sun"
**			(case-insensitive)
**		Month can be "Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul"
**			"Aug" "Sep" "Oct" "Nov" "Dec" (also case-insensitive)
D 41
**		Zone can be "UT" "GMT" "EST" "EDT" "CST" "CDT" "MST" "MDT"
**			"PST" "PDT" or "+"4*DIGIT or "-"4*DIGIT
**			(case-insensitive; military zones not useful
**			per RFC1123)
E 41
I 41
**		Zone can be as in the list below.
E 41
**		Additional whitespace or comments may occur.
I 41
**
**	Notes:
**		It's not clear this routine is valuable, since about the
**		only place UNIX dates are used is in the UNIX mailbox
**		header, which should probably be delivery time, not
**		message creation time.  Oh well, I'll leave this for
**		the time being.
E 41
*/

static char MonthDays[] = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

I 41
struct tzone
{
	char	*tzname;	/* string name */
	int	tzoff;		/* offset in hours from GMT */
	bool	tzdst;		/* daylight savings */
};

static struct tzone	Zones[] =
{
	"UT",		0,	FALSE,
	"GMT",		0,	FALSE,
	"AST",		-4,	FALSE,		/* Atlantic */
	"ADT",		-3,	TRUE,
	"EST",		-5,	FALSE,		/* Eastern */
	"EDT",		-4,	TRUE,
	"CST",		-6,	FALSE,		/* Central */
	"CDT",		-5,	TRUE,
	"MST",		-7,	FALSE,		/* Mountain */
	"MDT",		-6,	TRUE,
	"PST",		-8,	FALSE,		/* Pacific */
	"PDT",		-7,	TRUE,
	"YST",		-9,	FALSE,		/* Yukon */
	"YDT",		-8,	TRUE,
	"JST",		9,	FALSE,		/* Japan */
	"AHST",		-10,	FALSE,		/* Aleutian */
	"AHDT",		-9,	TRUE,
	"HAST",		-10,	FALSE,		/* Aleutian */
	"HADT",		-9,	TRUE,
	"NST",		-11,	FALSE,		/* Nome */
	"BST",		-11,	FALSE,		/* Bering */
	"SST",		-11,	FALSE,		/* Samoa */
	"HST",		-10,	FALSE,		/* Hawaii */
	"BST",		1,	TRUE,
	"WET",		0,	FALSE,		/* Western European */
	"WET DST",	1,	TRUE,
	"MET",		1,	FALSE,		/* Middle European */
	"MET DST",	2,	TRUE,
	"CET",		1,	FALSE,		/* Central European */
	"CET DST",	2,	TRUE,
	"EET",		2,	FALSE,		/* Eastern European */
	"MET DST",	3,	TRUE,
	"HKT",		8,	FALSE,		/* Hong Kong */
	"IST",		2,	FALSE,		/* Israel */
	"IDT",		3,	TRUE,
	"KST",		9,	FALSE,		/* Korea */
	"KDT",		10,	TRUE,
	"SST",		8,	FALSE,		/* Singapore */
	"NZST",		12,	FALSE,		/* New Zealand */
	"NZDT",		13,	TRUE,
	NULL,
};

E 41
char *
arpatounix(s, e)
	char	*s;
	ENVELOPE *e;
{
	char *p;
	char *n;
	int h_offset = 0;		/* hours */
	int m_offset = 0;		/* minutes */
	struct tm tm;
I 41
	register struct tzone *z;
E 41
	extern char *DowList[];		/* defined in collect.c */
	extern char *MonthList[];	/* defined in collect.c */

	bzero((char *) &tm, sizeof tm);
	tm.tm_wday = -1;	/* impossible value */
	p = nextatom (s);

	/* next atom must be a day or a date */
	if (isalpha((int) *p))
	{
		/* day */
		for (tm.tm_wday = 0; DowList[tm.tm_wday]; tm.tm_wday++)
		{
			if (strncasecmp (p, DowList[tm.tm_wday], 3))
				continue;
			else
			{
				p += 3;
				break;
			}
		}
		p = nextatom(p);		/* ',' */
		if (*p == ',')
			p = nextatom(++p);
	}

	/* now must have date */
	tm.tm_mday = atoi(p);
D 42
	while (isdigit((int) *p))		/* skip over date */
E 42
I 42
	while (isascii(*p) && isdigit(*p))	/* skip over date */
E 42
		p++;
	p = nextatom(p);			/* point to month name */
	for (tm.tm_mon = 0; MonthList[tm.tm_mon]; tm.tm_mon++)
	{
		if (strncasecmp(p, MonthList[tm.tm_mon], 3) == 0)
		{
			p += 3;
			break;
		}
	}
	p = nextatom(p);			/* year */
	tm.tm_year = atoi(p);

	/* if this was 4 digits, subtract 1900 */
	if (tm.tm_year > 999)
		tm.tm_year -= 1900;
	else
	{
		/* if 2 or 3 digits, guess which century and convert */
		time_t now;
		struct tm *gmt;

		(void) time(&now);
		gmt = gmtime(&now);

		/* more likely +1 day than -100(0) years */
		if (gmt->tm_mon == 11 && gmt->tm_mday == 31 &&
		    tm.tm_mon == 0 && tm.tm_mday == 1)
			gmt->tm_year++;
		if (tm.tm_year > 99)
		{
			/* 3 digits */
			tm.tm_year += ((gmt->tm_year + 900 - tm.tm_year) / 1000) * 1000;
		}
		else
		{
			/* 2 digits */
			tm.tm_year += ((gmt->tm_year - tm.tm_year) / 100) * 100;
		}
	}
D 42
	while (isdigit((int) *p))	/* skip over year */
E 42
I 42
	while (isascii(*p) && isdigit(*p))	/* skip over year */
E 42
		p++;
D 42
	p = nextatom(p);		/* hours */
E 42
I 42
	p = nextatom(p);			/* hours */
E 42
	tm.tm_hour = atoi(p);
D 42
	while (isdigit((int) *p))	/* skip over hours */
E 42
I 42
	while (isascii(*p) && isdigit(*p))	/* skip over hours */
E 42
		p++;
D 42
	p = nextatom(p);		/* colon */
E 42
I 42
	p = nextatom(p);			/* colon */
E 42
	if (*p == ':')
		p = nextatom(++p);
D 42
	p = nextatom(p);		/* minutes */
E 42
I 42
	p = nextatom(p);			/* minutes */
E 42
	tm.tm_min = atoi(p);
D 42
	while (isdigit((int) *p))	/* skip over minutes */
E 42
I 42
	while (isascii(*p) && isdigit(*p))	/* skip over minutes */
E 42
		p++;
D 42
	p = nextatom(p);		/* colon or zone */
	if (*p == ':')			/* have seconds field */
E 42
I 42
	p = nextatom(p);			/* colon or zone */
	if (*p == ':')				/* have seconds field */
E 42
	{
		p = nextatom(++p);
		tm.tm_sec = atoi(p);
D 42
		while (isdigit((int) *p))	/* skip over seconds */
E 42
I 42
		while (isascii(*p) && isdigit(*p))	/* skip over seconds */
E 42
			p++;
	}
D 42
	p = nextatom(p);		/* zone */
E 42
I 42
	p = nextatom(p);			/* zone */
E 42
D 41
	if (!strncasecmp(p, "UT", 2) || !strncasecmp(p, "GMT", 3))
		;
	else if (!strncasecmp(p, "EDT", 3))
		h_offset = -4;
	else if (!strncasecmp(p, "EST", 3))
E 41
I 41

	if (*p == '+')
E 41
	{
D 41
		h_offset = -5;
		tm.tm_isdst = 1;
	}
	else if (!strncasecmp(p, "CDT", 3))
		h_offset = -5;
	else if (!strncasecmp(p, "CST", 3))
	{
		h_offset = -6;
		tm.tm_isdst = 1;
	}
	else if (!strncasecmp(p, "MDT", 3))
		h_offset = -6;
	else if (!strncasecmp(p, "MST", 3))
	{
		h_offset = -7;
		tm.tm_isdst = 1;
	}
	else if (!strncasecmp(p, "PDT", 3))
		h_offset = -7;
	else if (!strncasecmp(p, "PST", 3))
	{
		h_offset = -8;
		tm.tm_isdst = 1;
	}
	else if (*p == '+')
	{
E 41
		int off;

		off = atoi(++p);
		h_offset = off / 100;
		m_offset = off % 100;
	}
	else if (*p == '-')
	{
		int off;

		off = atoi(++p);
		h_offset = off / -100;
		m_offset = -1 * (off % 100);
	}
	else
	{
I 41
		for (z = Zones; z->tzname != NULL; z++)
		{
			if (strncasecmp(p, z->tzname, strlen(z->tzname)) == 0)
				break;
		}

		if (z->tzname != NULL)
		{
			h_offset = z->tzoff;
			tm.tm_isdst = z->tzdst;
		}
		else
		{
E 41
#ifdef LOG
D 41
		if (LogLevel > 0)
			syslog(LOG_NOTICE, "%s: arpatounix: unparseable date: %s",
				e->e_id, s);
E 41
I 41
			if (LogLevel > 3)
				syslog(LOG_NOTICE, "%s: arpatounix: unparseable date: %s",
					e->e_id, s);
E 41
#endif /* LOG */
D 41
		return(NULL);
E 41
I 41
			return (NULL);
		}
E 41
	}

	/* is the year a leap year? */
	if ((tm.tm_year % 4 == 0) &&
	    ((tm.tm_year % 100 != 0) || (tm.tm_year % 400 == 0)))
		MonthDays[2] = 29;
	else
		MonthDays[2] = 28;

D 41
	/* apply offset */
	if (h_offset || m_offset)
E 41
I 41
	/* apply offset -- this leaves the date in GMT */
	if (h_offset != 0 || m_offset != 0)
E 41
	{
D 41
		tm.tm_min += m_offset;
		tm.tm_hour += h_offset;
E 41
I 41
		tm.tm_min -= m_offset;
		tm.tm_hour -= h_offset;
E 41

		/* normalize */
		if (tm.tm_min < 0)
		{
			tm.tm_hour--;
			tm.tm_min += 60;
		}
		else if (tm.tm_min > 59)
		{
			tm.tm_hour++;
			tm.tm_min -= 60;
		}
		if (tm.tm_hour < 0)
		{
			tm.tm_mday--;
			tm.tm_wday--;
			tm.tm_hour += 24;
		}
		else if (tm.tm_hour > 23)
		{
			tm.tm_mday++;
			tm.tm_wday++;
			tm.tm_hour -= 24;
		}
		if (tm.tm_mday < 1)
		{
			if (--tm.tm_mon == -1)
			{
				tm.tm_mon = 11;
				tm.tm_year--;

				/* is the year a leap year? */
				if ((tm.tm_year % 4 == 0) &&
				    ((tm.tm_year % 100 != 0) || (tm.tm_year % 400 == 0)))
					MonthDays[2] = 29;
				else
					MonthDays[2] = 28;
			}
			tm.tm_mday += MonthDays[tm.tm_mon];
		}
		else if (tm.tm_mday > MonthDays[tm.tm_mon])
		{
			tm.tm_mday -= MonthDays[tm.tm_mon++];
			if (tm.tm_mon > 11)
			{
				tm.tm_mon = 0;
				tm.tm_year++;

				/*
				* Don't have to worry about leap years in
				* January.
				*/
			}
		}
	}

	/* determine day of week if not set from RFC822/1123 line */
	if (tm.tm_wday < 0)
	{
		int i;

		for (i = 0; i < tm.tm_mon; i++)
			tm.tm_yday += MonthDays[i];
		tm.tm_yday += tm.tm_mday;

		/* I wouldn't change these constants if I were you... */
		tm.tm_wday = (int) (((((tm.tm_year + 699L) * 146097L) / 400L) + tm.tm_yday) % 7);
	}

	/* now get UT */
	if ((p = asctime(&tm)) == NULL || *p == '\0' || strlen(p) < 25)
	{
#ifdef LOG
D 41
		if (LogLevel > 0)
E 41
I 41
		if (LogLevel > 1)
E 41
			syslog(LOG_NOTICE, "%s: arpatounix: asctime failed: %s",
				e->e_id, s);
#endif /* LOG */
		return(NULL);
	}
D 40
	if ((n = index(p, '\n')) != NULL)
E 40
I 40
	if ((n = strchr(p, '\n')) != NULL)
E 40
		*n = '\0';
	return(p);
E 38
E 33
E 22
E 21
}
E 43
E 1
