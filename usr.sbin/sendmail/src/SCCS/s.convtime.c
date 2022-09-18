h26150
s 00001/00000/00176
d D 8.4 95/05/19 16:00:10 eric 17 16
c fix compile problems on various platforms
e
s 00001/00001/00175
d D 8.3 95/04/21 09:56:51 eric 16 15
c update copyright notice
e
s 00005/00000/00171
d D 8.2 95/03/08 17:20:14 eric 15 14
c diagnose bogus time units
e
s 00002/00002/00169
d D 8.1 93/06/07 10:29:38 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00170
d D 6.4 93/05/28 07:00:36 eric 13 12
c change alias initialization to general map initialization
e
s 00006/00001/00165
d D 6.3 93/03/23 19:50:41 eric 12 11
c improved debugging; pass convtime a default units; allow addition
c of Comments: and stripping of Return-Path:
e
s 00001/00001/00165
d D 6.2 93/02/18 20:22:13 eric 11 10
c move the meta-characters from C0 into C1 space
e
s 00000/00000/00166
d D 6.1 92/12/21 16:08:11 eric 10 9
c Release 6
e
s 00001/00011/00165
d D 5.4 90/06/01 19:00:55 bostic 9 8
c new copyright notice
e
s 00011/00009/00165
d D 5.3 88/06/30 14:58:34 bostic 8 7
c install approved copyright notice
e
s 00016/00010/00158
d D 5.2 88/03/13 19:51:43 bostic 7 6
c add Berkeley specific header
e
s 00014/00002/00154
d D 5.1 85/06/07 14:37:16 dist 6 5
m 
c Add copyright
e
s 00000/00000/00156
d D 4.1 83/07/25 19:43:07 eric 5 4
m 
c 4.2 release version
e
s 00006/00007/00150
d D 3.4 83/04/19 19:20:37 eric 4 3
m 228
c Fix bug causing convtime to loop forever on "w" (week) specification.
e
s 00092/00000/00065
d D 3.3 82/11/28 00:20:53 eric 3 2
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00036/00020/00029
d D 3.2 81/12/06 12:41:04 eric 2 1
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00049/00000/00000
d D 3.1 81/10/26 09:33:08 eric 1 0
c date and time created 81/10/26 09:33:08 by eric
e
u
U
f b 
f i 
t
T
I 6
/*
I 8
D 16
 * Copyright (c) 1983 Eric P. Allman
E 16
I 16
 * Copyright (c) 1983, 1995 Eric P. Allman
E 16
E 8
D 7
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 7
I 7
D 14
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 14
I 14
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
D 9
 * Redistribution and use in source and binary forms are permitted
D 8
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 8
I 8
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
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 8
 */
E 7

#ifndef lint
D 7
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 7

E 6
I 1
D 2
# include <sys/types.h>
E 2
# include <ctype.h>
I 17
# include <string.h>
E 17
I 2
# include "useful.h"
E 2
D 6

D 2
static char	SccsId[] =	"%W%	%G%";
E 2
I 2
SCCSID(%W%	%Y%	%G%);
E 6
E 2

/*
**  CONVTIME -- convert time
**
I 2
**	Takes a time as an ascii string with a trailing character
**	giving units:
**	  s -- seconds
**	  m -- minutes
**	  h -- hours
**	  d -- days (default)
**	  w -- weeks
I 3
**	For example, "3d12h" is three and a half days.
E 3
**
E 2
**	Parameters:
**		p -- pointer to ascii time.
I 12
**		units -- default units if none specified.
E 12
**
**	Returns:
**		time in seconds.
**
**	Side Effects:
**		none.
*/

time_t
D 12
convtime(p)
E 12
I 12
convtime(p, units)
E 12
	char *p;
I 12
	char units;
E 12
{
D 2
	register time_t t;
E 2
I 2
	register time_t t, r;
I 4
	register char c;
E 4
E 2

D 2
	t = 0;
	while (isdigit(*p))
		t = t * 10 + (*p++ - '0');
	switch (*p)
E 2
I 2
	r = 0;
	while (*p != '\0')
E 2
	{
D 2
	  case 'w':		/* weeks */
		t *= 7;
E 2
I 2
		t = 0;
D 4
		while (isdigit(*p))
			t = t * 10 + (*p++ - '0');
		switch (*p++)
E 4
I 4
D 11
		while (isdigit(c = *p++))
E 11
I 11
D 13
		while (isascii(c = *p++) && isdigit(c))
E 13
I 13
		while ((c = *p++) != '\0' && isascii(c) && isdigit(c))
E 13
E 11
			t = t * 10 + (c - '0');
		if (c == '\0')
I 12
		{
			c = units;
E 12
			p--;
I 12
		}
I 15
		else if (strchr("wdhms", c) == NULL)
		{
			usrerr("Invalid time unit `%c'", c);
			c = units;
		}
E 15
E 12
		switch (c)
E 4
		{
		  case 'w':		/* weeks */
			t *= 7;
E 2
D 4

D 2
	  case 'd':		/* days */
	  case '\0':
	  default:
		t *= 24;
E 2
I 2
		  case '\0':
			p--;
			/* fall through... */
E 4
E 2

D 2
	  case 'h':		/* hours */
		t *= 60;
E 2
I 2
		  case 'd':		/* days */
		  default:
			t *= 24;
E 2

D 2
	  case 'm':		/* minutes */
		t *= 60;
E 2
I 2
		  case 'h':		/* hours */
			t *= 60;
E 2

D 2
	  case 's':		/* seconds */
		break;
E 2
I 2
		  case 'm':		/* minutes */
			t *= 60;

		  case 's':		/* seconds */
			break;
		}
		r += t;
E 2
	}

D 2
	return (t);
E 2
I 2
	return (r);
I 3
}
/*
**  PINTVL -- produce printable version of a time interval
**
**	Parameters:
**		intvl -- the interval to be converted
**		brief -- if TRUE, print this in an extremely compact form
**			(basically used for logging).
**
**	Returns:
**		A pointer to a string version of intvl suitable for
**			printing or framing.
**
**	Side Effects:
**		none.
**
**	Warning:
**		The string returned is in a static buffer.
*/

# define PLURAL(n)	((n) == 1 ? "" : "s")

char *
pintvl(intvl, brief)
	time_t intvl;
	bool brief;
{
	static char buf[256];
	register char *p;
	int wk, dy, hr, mi, se;

	if (intvl == 0 && !brief)
		return ("zero seconds");

	/* decode the interval into weeks, days, hours, minutes, seconds */
	se = intvl % 60;
	intvl /= 60;
	mi = intvl % 60;
	intvl /= 60;
	hr = intvl % 24;
	intvl /= 24;
	if (brief)
		dy = intvl;
	else
	{
		dy = intvl % 7;
		intvl /= 7;
		wk = intvl;
	}

	/* now turn it into a sexy form */
	p = buf;
	if (brief)
	{
		if (dy > 0)
		{
			(void) sprintf(p, "%d+", dy);
			p += strlen(p);
		}
		(void) sprintf(p, "%02d:%02d:%02d", hr, mi, se);
		return (buf);
	}

	/* use the verbose form */
	if (wk > 0)
	{
		(void) sprintf(p, ", %d week%s", wk, PLURAL(wk));
		p += strlen(p);
	}
	if (dy > 0)
	{
		(void) sprintf(p, ", %d day%s", dy, PLURAL(dy));
		p += strlen(p);
	}
	if (hr > 0)
	{
		(void) sprintf(p, ", %d hour%s", hr, PLURAL(hr));
		p += strlen(p);
	}
	if (mi > 0)
	{
		(void) sprintf(p, ", %d minute%s", mi, PLURAL(mi));
		p += strlen(p);
	}
	if (se > 0)
	{
		(void) sprintf(p, ", %d second%s", se, PLURAL(se));
		p += strlen(p);
	}

	return (buf + 2);
E 3
E 2
}
E 1
