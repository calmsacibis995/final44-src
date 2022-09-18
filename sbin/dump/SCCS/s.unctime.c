h52436
s 00002/00053/00078
d D 8.2 94/06/14 16:14:15 mkm 15 14
c get rid of emitl and dcmp as they are done by mktime (from mycroft)
e
s 00002/00002/00129
d D 8.1 93/06/05 10:53:05 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00004/00128
d D 5.7 93/04/17 10:31:56 mckusick 13 12
c avoid clobbering the other arguments (from leres@ee.lbl.gov)
e
s 00014/00010/00118
d D 5.6 93/01/25 15:36:03 mckusick 12 11
c cleanups from leres@lbl
e
s 00001/00001/00127
d D 5.5 92/06/18 18:54:51 mckusick 11 10
c lint
e
s 00005/00004/00123
d D 5.4 91/03/07 17:49:59 mckusick 10 9
c verified to be free of AT&T code
e
s 00003/00001/00124
d D 5.3 91/02/28 19:33:57 bostic 9 8
c ANSI; break #includes out of dump.h into separate files
e
s 00015/00008/00110
d D 5.2 91/02/23 16:15:28 torek 8 7
c fix gcc warnings
e
s 00007/00001/00111
d D 5.1 85/06/05 08:48:20 dist 7 6
c Add copyright
e
s 00004/00001/00108
d D 1.5 83/08/13 11:33:30 sam 6 4
c standardize sccs keyword lines
e
s 00004/00000/00109
d R 1.5 83/08/11 22:56:17 sam 5 4
c standardize sccs keyword lines
e
s 00001/00001/00108
d D 1.4 83/07/03 20:55:49 sam 4 3
c include fix
e
s 00001/00001/00108
d D 1.3 81/04/18 11:19:44 root 3 2
c fix problem with GMT
e
s 00005/00003/00104
d D 1.2 81/04/18 11:19:14 root 2 1
c correct fix for GMT time conversion problem
e
s 00107/00000/00000
d D 1.1 80/10/13 17:30:33 root 1 0
c date and time created 80/10/13 17:30:33 by root
e
u
U
t
T
I 7
D 10
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
/*-
D 14
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
 * %sccs.include.redist.c%
E 10
 */

E 7
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8
E 7

E 6
I 1
D 2
static	char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 3
static	char *sccsid = "@(#)unctime.c	1.1 (Berkeley) 10/13/80";
E 3
E 2
#include <sys/types.h>
D 4
#include <time.h>
E 4
I 4
D 9
#include <sys/time.h>
E 9
I 9
D 12
#include <time.h>
E 12
I 12

E 12
E 9
E 4
I 2
#include <stdio.h>
I 12
#include <time.h>
E 12
I 9
#ifdef __STDC__
E 9
I 8
#include <stdlib.h>
#include <string.h>
I 9
#endif
E 9

I 12
#ifndef __P
#include <sys/cdefs.h>
#endif

E 12
E 8
E 2
/*
 * Convert a ctime(3) format string into a system format date.
 * Return the date thus calculated.
 *
 * Return -1 if the string is not in ctime format.
 */

/*
 * Offsets into the ctime string to various parts.
 */

#define	E_MONTH		4
#define	E_DAY		8
#define	E_HOUR		11
#define	E_MINUTE	14
#define	E_SECOND	17
#define	E_YEAR		20

D 8
time_t unctime(str)
E 8
I 8
D 12
static int lookup();
E 12
I 12
D 15
static	int dcmp __P((struct tm *, struct tm *));
static	time_t emitl __P((struct tm *));
E 15
static	int lookup __P((char *));
E 12

I 12

E 12
time_t
unctime(str)
E 8
	char *str;
{
	struct tm then;
D 13
	char dbuf[30];
E 13
I 13
	char dbuf[26];
E 13
D 12
	time_t emitl();
E 12

D 13
	if (strlen(str) != 25)
D 12
		str[25] = 0;
E 12
I 12
		str[25] = '\0';
E 12
D 11
	strcpy(dbuf, str);
E 11
I 11
	(void) strcpy(dbuf, str);
E 13
I 13
	(void) strncpy(dbuf, str, sizeof(dbuf) - 1);
	dbuf[sizeof(dbuf) - 1] = '\0';
E 13
E 11
D 12
	dbuf[E_MONTH+3] = 0;
E 12
I 12
	dbuf[E_MONTH+3] = '\0';
E 12
D 2
	if ( (then.tm_mon = lookup(&dbuf[E_MONTH])) < 0)
E 2
I 2
D 8
	if ( (then.tm_mon = lookup(&dbuf[E_MONTH])) < 0) {
E 2
		return(-1);;
I 2
	}
E 8
I 8
	if ((then.tm_mon = lookup(&dbuf[E_MONTH])) < 0)
		return (-1);
E 8
E 2
	then.tm_mday = atoi(&dbuf[E_DAY]);
	then.tm_hour = atoi(&dbuf[E_HOUR]);
	then.tm_min = atoi(&dbuf[E_MINUTE]);
	then.tm_sec = atoi(&dbuf[E_SECOND]);
	then.tm_year = atoi(&dbuf[E_YEAR]) - 1900;
D 15
	return(emitl(&then));
E 15
I 15
	then.tm_isdst = -1;
	return(mktime(&then));
E 15
}

static char months[] =
	"JanFebMarAprMayJunJulAugSepOctNovDec";

D 8
static
E 8
I 8
static int
E 8
lookup(str)
	char *str;
{
	register char *cp, *cp2;

D 12
	for (cp = months, cp2 = str; *cp != 0; cp += 3)
E 12
I 12
	for (cp = months, cp2 = str; *cp != '\0'; cp += 3)
E 12
		if (strncmp(cp, cp2, 3) == 0)
			return((cp-months) / 3);
	return(-1);
D 15
}
/*
 * Routine to convert a localtime(3) format date back into
 * a system format date.
 *
 *	Use a binary search.
 */

D 12
struct tm *localtime();
I 8
static int dcmp();
E 8

D 8
time_t emitl(dp)
E 8
I 8
time_t
E 12
I 12
static time_t
E 12
emitl(dp)
E 8
	struct tm *dp;
{
	time_t conv;
	register int i, bit;
	struct tm dcopy;

	dcopy = *dp;
	dp = &dcopy;
	conv = 0;
D 2
	for (i = 31; i >= 0; i--) {
E 2
I 2
	for (i = 30; i >= 0; i--) {
E 2
		bit = 1 << i;
		conv |= bit;
		if (dcmp(localtime(&conv), dp) > 0)
			conv &= ~bit;
	}
	return(conv);
}

/*
 * Compare two localtime dates, return result.
 */

#define DECIDE(a) \
	if (dp->a > dp2->a) \
		return(1); \
	if (dp->a < dp2->a) \
		return(-1)

D 8
static
E 8
I 8
static int
E 8
dcmp(dp, dp2)
	register struct tm *dp, *dp2;
{

	DECIDE(tm_year);
	DECIDE(tm_mon);
	DECIDE(tm_mday);
	DECIDE(tm_hour);
	DECIDE(tm_min);
	DECIDE(tm_sec);
	return(0);
E 15
}
I 3
D 6
static	char *sccsid = "%W% (Berkeley) %E%";
E 6
E 3
E 1
