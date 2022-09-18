h16224
s 00001/00011/00058
d D 5.4 90/06/01 15:53:36 bostic 5 4
c new copyright notice
e
s 00015/00004/00054
d D 5.3 89/02/27 09:47:06 bostic 4 3
c add Berkeley specific header for networking release
e
s 00001/00001/00057
d D 5.2 87/10/22 11:11:41 bostic 3 2
c ANSI C; sprintf now returns an int.
e
s 00008/00002/00050
d D 5.1 85/04/29 12:08:03 dist 2 1
c Add copyright
e
s 00052/00000/00000
d D 4.1 85/02/05 08:44:43 ralph 1 0
c date and time created 85/02/05 08:44:43 by ralph
e
u
U
t
T
I 2
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4
E 2

#include <stdio.h>
#include <sys/time.h>

static char *days[] = {
	"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"
};

static char *months[] = {
	"Jan", "Feb", "Mar", "Apr", "May", "June",
	"July", "Aug", "Sept", "Oct", "Nov", "Dec"
};

#define AM "am"
#define PM "pm"

get_date(datebuffer)
	char *datebuffer;
{
	struct tm *localtime(), *tmp;
	struct timeval tv;
	int realhour;
	char *zone;

	gettimeofday(&tv, 0);
	tmp = localtime(&tv.tv_sec);

	realhour = tmp->tm_hour;
	zone = AM;			/* default to morning */
	if (tmp->tm_hour == 0)
		realhour = 12;		/* midnight */
	else if (tmp->tm_hour == 12)
		zone = PM;		/* noon */
	else if (tmp->tm_hour >= 13 && tmp->tm_hour <= 23) { /* afternoon */
		realhour = realhour - 12;
		zone = PM;
	}
	
	/* format is '8:10pm on Sunday, 16 Sept 1973' */

D 3
	sprintf(datebuffer, "%d:%02d%s on %s, %d %s %d",
E 3
I 3
	(void)sprintf(datebuffer, "%d:%02d%s on %s, %d %s %d",
E 3
		realhour,
		tmp->tm_min,
		zone,
		days[tmp->tm_wday],
		tmp->tm_mday,
		months[tmp->tm_mon],
		1900 + tmp->tm_year);
}
E 1
