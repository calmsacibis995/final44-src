h11078
s 00002/00002/00051
d D 8.1 93/06/06 13:59:50 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00052
d D 5.6 93/04/05 21:53:32 ralph 12 11
c change start to startcmd to avoid conflict with start in crt0.o
e
s 00006/00007/00047
d D 5.5 92/07/21 10:28:57 bostic 11 10
c prototype lpr to fix quad's
e
s 00001/00011/00053
d D 5.4 90/06/01 18:44:42 bostic 10 9
c new copyright notice
e
s 00010/00005/00054
d D 5.3 88/06/30 17:59:39 bostic 9 8
c install approved copyright notice
e
s 00009/00003/00050
d D 5.2 88/05/05 18:07:37 bostic 8 7
c written by Ralph Campbell; add Berkeley specific header
e
s 00007/00001/00046
d D 5.1 85/06/06 09:58:16 dist 7 6
c Add copyright
e
s 00007/00006/00040
d D 4.6 84/07/24 16:30:07 ralph 6 5
c added `up' command
e
s 00003/00001/00043
d D 4.5 84/01/30 16:16:00 ralph 5 4
c added lpc down printer "status message".
e
s 00001/00001/00043
d D 4.4 83/07/25 12:09:33 ralph 4 3
c fix protection on topq
e
s 00000/00000/00044
d D 4.3 83/07/17 00:10:49 sam 3 2
c put sccs id's to some use
e
s 00003/00000/00041
d D 4.2 83/07/02 23:48:11 root 2 1
c for ralph; stuff for moving jobs to the top of a queue
e
s 00041/00000/00000
d D 4.1 83/05/11 16:04:21 ralph 1 0
c date and time created 83/05/11 16:04:21 by ralph
e
u
U
t
T
I 7
/*
D 13
 * Copyright (c) 1983 Regents of the University of California.
D 8
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
D 10
 * Redistribution and use in source and binary forms are permitted
D 9
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 9
I 9
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 9
E 8
 */

E 7
I 1
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

D 11
/*
 * lpc -- command tables
 */
E 11
I 11
#include <sys/cdefs.h>
E 11

#include "lpc.h"
I 11
#include "extern.h"
E 11

D 6
int	abort(), clean(), enable(), disable(), help();
int	quit(), restart(), start(), status(), stop();
I 2
D 5
int	topq();
E 5
I 5
int	topq(), down();
E 6
I 6
D 11
int	abort(), clean(), enable(), disable(), down(), help();
int	quit(), restart(), start(), status(), stop(), topq(), up();
E 6
E 5
E 2

E 11
I 11
/*
 * lpc -- command tables
 */
E 11
char	aborthelp[] =	"terminate a spooling daemon immediately and disable printing";
char	cleanhelp[] =	"remove cruft files from a queue";
char	enablehelp[] =	"turn a spooling queue on";
char	disablehelp[] =	"turn a spooling queue off";
I 6
char	downhelp[] =	"do a 'stop' followed by 'disable' and put a message in status";
E 6
char	helphelp[] =	"get help on commands";
char	quithelp[] =	"exit lpc";
D 6
char	restarthelp[] =	"restart a spooling daemon that has died";
E 6
I 6
char	restarthelp[] =	"kill (if possible) and restart a spooling daemon";
E 6
char	starthelp[] =	"enable printing and start a spooling daemon";
D 6
char	statushelp[] =	"show status of daemon";
E 6
I 6
char	statushelp[] =	"show status of daemon and queue";
E 6
char	stophelp[] =	"stop a spooling daemon after current job completes and disable printing";
I 5
D 6
char	downhelp[] =	"do a 'stop' followed by 'disable' and put a message in status";
E 6
E 5
I 2
char	topqhelp[] =	"put job at top of printer queue";
I 6
char	uphelp[] =	"enable everything and restart spooling daemon";
E 6
E 2

struct cmd cmdtab[] = {
D 11
	{ "abort",	aborthelp,	abort,		1 },
E 11
I 11
	{ "abort",	aborthelp,	doabort,	1 },
E 11
	{ "clean",	cleanhelp,	clean,		1 },
	{ "enable",	enablehelp,	enable,		1 },
	{ "exit",	quithelp,	quit,		0 },
	{ "disable",	disablehelp,	disable,	1 },
I 5
	{ "down",	downhelp,	down,		1 },
E 5
	{ "help",	helphelp,	help,		0 },
	{ "quit",	quithelp,	quit,		0 },
	{ "restart",	restarthelp,	restart,	0 },
D 12
	{ "start",	starthelp,	start,		1 },
E 12
I 12
	{ "start",	starthelp,	startcmd,	1 },
E 12
	{ "status",	statushelp,	status,		0 },
	{ "stop",	stophelp,	stop,		1 },
I 2
D 4
	{ "topq",	topqhelp,	topq,		0 },
E 4
I 4
	{ "topq",	topqhelp,	topq,		1 },
I 6
	{ "up",		uphelp,		up,		1 },
E 6
E 4
E 2
	{ "?",		helphelp,	help,		0 },
	{ 0 },
};

int	NCMDS = sizeof (cmdtab) / sizeof (cmdtab[0]);
E 1
