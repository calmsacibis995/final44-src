h06671
s 00002/00002/00029
d D 8.1 93/06/06 14:09:21 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00031
d D 2.7 93/05/11 11:49:34 bostic 8 7
c new version from Vernon Schryver (vjs@sgi.com); see ../timed/CHANGES for details
e
s 00001/00011/00032
d D 2.6 90/06/01 19:03:15 bostic 7 6
c new copyright notice
e
s 00010/00005/00033
d D 2.5 88/06/18 14:08:11 bostic 6 5
c install approved copyright notice
e
s 00009/00003/00029
d D 2.4 87/12/23 14:30:06 bostic 5 4
c append Berkeley header; NASA wants a copy
e
s 00002/00002/00030
d D 2.3 86/05/28 12:00:08 bloom 4 3
c change command names
e
s 00000/00001/00032
d D 2.2 86/01/24 09:11:27 bloom 3 2
c purge extra null entry from table and correct search in getcmd (sam@okeeffe)
e
s 00000/00000/00033
d D 2.1 85/12/10 13:06:45 bloom 2 1
c Multi network support
e
s 00033/00000/00000
d D 1.1 85/06/24 00:20:26 gusella 1 0
c date and time created 85/06/24 00:20:26 by gusella
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 6
E 5
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#include "timedc.h"

D 8
int	clockdiff(), help(), msite(), quit(), testing(), tracing();

E 8
char	clockdiffhelp[] =	"measures clock differences between machines";
char	helphelp[] =		"gets help on commands";
char	msitehelp[] =		"finds location of master";
char	quithelp[] =		"exits timedc";
char	testinghelp[] =		"causes election timers to expire";
char	tracinghelp[] =		"turns tracing on or off";

struct cmd cmdtab[] = {
	{ "clockdiff",	clockdiffhelp,	clockdiff,	0 },
I 4
	{ "election",	testinghelp,	testing,	1 },
E 4
	{ "help",	helphelp,	help,		0 },
	{ "msite",	msitehelp,	msite,		0 },
	{ "quit",	quithelp,	quit,		0 },
D 4
	{ "testing",	testinghelp,	testing,	1 },
	{ "tracing",	tracinghelp,	tracing,	1 },
E 4
I 4
	{ "trace",	tracinghelp,	tracing,	1 },
E 4
	{ "?",		helphelp,	help,		0 },
D 3
	{ 0 },
E 3
};

int	NCMDS = sizeof (cmdtab) / sizeof (cmdtab[0]);
E 1
