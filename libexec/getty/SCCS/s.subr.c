h15179
s 00002/00002/00503
d D 8.1 93/06/04 18:50:36 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00505
d D 5.13 93/05/27 16:08:07 elan 17 16
c deleted getttytab.c; turn off debugging
e
s 00026/00012/00480
d D 5.12 93/05/27 12:55:38 elan 16 15
c Convert to getcap(3) routines.
e
s 00056/00044/00436
d D 5.11 93/05/17 10:36:56 bostic 15 14
c ANSI C prototypes
e
s 00002/00002/00478
d D 5.10 91/02/26 12:46:19 bostic 14 13
c use defines for file descriptors
e
s 00004/00002/00476
d D 5.9 91/02/26 12:45:13 bostic 13 12
c more ANSI fixes
e
s 00002/00000/00476
d D 5.8 91/02/25 17:03:33 bostic 12 11
c ANSI fixes
e
s 00001/00011/00475
d D 5.7 90/06/01 15:54:04 bostic 11 10
c new copyright notice
e
s 00001/00000/00485
d D 5.6 90/06/01 15:53:12 marc 10 9
c  checked in for Marc; needed USE_OLD_TTY
e
s 00015/00004/00470
d D 5.5 89/02/27 09:55:24 bostic 9 8
c add Berkeley specific header for networking release
e
s 00003/00000/00471
d D 5.4 86/01/07 15:10:07 mckusick 8 7
c set DECCTLQ on specifc lines with getty (from muller@nprdc.arpa)
e
s 00001/00000/00470
d D 5.3 85/10/18 17:39:27 mckusick 7 6
c update for 19200 baud (from Keith Muller)
e
s 00001/00001/00469
d D 5.2 85/05/04 16:37:13 edward 6 5
c '\377' not '\0377'
e
s 00008/00002/00462
d D 5.1 85/04/29 12:46:16 dist 5 4
c Add copyright
e
s 00054/00001/00410
d D 4.4 85/02/05 08:48:58 ralph 4 3
c added autobaud detection.
e
s 00003/00000/00408
d D 4.3 84/06/05 11:25:24 ralph 3 2
c make `ck' work by setting the bit.
e
s 00014/00007/00394
d D 4.2 83/07/07 03:32:48 kre 2 1
c fix delay numbers, and make '1', '2', and '3' simply
c select the equiv delay algorithm.
e
s 00401/00000/00000
d D 4.1 83/07/06 00:10:15 sam 1 0
c date and time created 83/07/06 00:10:15 by sam
e
u
U
t
T
I 5
/*
D 9
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 18
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
 *
D 11
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
 */

E 5
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (Berkeley) %E%";
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 5

/*
 * Melbourne getty.
 */
I 10
#define USE_OLD_TTY
I 16
#include <stdlib.h>
E 16
E 10
#include <sgtty.h>
I 12
D 15
#include <unistd.h>
E 15
#include <string.h>
I 15
#include <unistd.h>

E 15
E 12
#include "gettytab.h"
I 15
#include "extern.h"
I 16
#include "pathnames.h"
E 16
E 15

extern	struct sgttyb tmode;
extern	struct tchars tc;
extern	struct ltchars ltc;

/*
 * Get a table entry.
 */
I 15
void
E 15
D 16
gettable(name, buf, area)
	char *name, *buf, *area;
E 16
I 16
gettable(name, buf)
	char *name, *buf;
E 16
{
	register struct gettystrs *sp;
	register struct gettynums *np;
	register struct gettyflags *fp;
D 16
	register n;
E 16
I 16
	long n;
	char *dba[2];
	dba[0] = _PATH_GETTYTAB;
	dba[1] = 0;
E 16

D 16
	hopcount = 0;		/* new lookup, start fresh */
	if (getent(buf, name) != 1)
E 16
I 16
	if (cgetent(&buf, dba, name) != 0)
E 16
		return;

D 16
	for (sp = gettystrs; sp->field; sp++)
		sp->value = getstr(sp->field, &area);
E 16
I 16
	for (sp = gettystrs; sp->field; sp++) 
		cgetstr(buf, sp->field, &sp->value);
E 16
	for (np = gettynums; np->field; np++) {
D 16
		n = getnum(np->field);
		if (n == -1)
E 16
I 16
		if (cgetnum(buf, np->field, &n) == -1)
E 16
			np->set = 0;
		else {
			np->set = 1;
			np->value = n;
		}
	}
	for (fp = gettyflags; fp->field; fp++) {
D 16
		n = getflag(fp->field);
		if (n == -1)
E 16
I 16
		if (cgetcap(buf, fp->field, ':') == NULL)
E 16
			fp->set = 0;
		else {
			fp->set = 1;
D 16
			fp->value = n ^ fp->invrt;
E 16
I 16
			fp->value = 1 ^ fp->invrt;
E 16
		}
	}
I 16
D 17
#define DEBUG
E 17
#ifdef DEBUG
	printf("name=\"%s\", buf=\"%s\"\n", name, buf);
	for (sp = gettystrs; sp->field; sp++)
		printf("cgetstr: %s=%s\n", sp->field, sp->value);
	for (np = gettynums; np->field; np++)
		printf("cgetnum: %s=%d\n", np->field, np->value);
	for (fp = gettyflags; fp->field; fp++)
		printf("cgetflags: %s='%c' set='%c'\n", fp->field, 
		       fp->value + '0', fp->set + '0');
	exit(1);
#endif /* DEBUG */
E 16
}

I 15
void
E 15
gendefaults()
{
	register struct gettystrs *sp;
	register struct gettynums *np;
	register struct gettyflags *fp;

	for (sp = gettystrs; sp->field; sp++)
		if (sp->value)
			sp->defalt = sp->value;
	for (np = gettynums; np->field; np++)
		if (np->set)
			np->defalt = np->value;
	for (fp = gettyflags; fp->field; fp++)
		if (fp->set)
			fp->defalt = fp->value;
		else
			fp->defalt = fp->invrt;
}

I 15
void
E 15
setdefaults()
{
	register struct gettystrs *sp;
	register struct gettynums *np;
	register struct gettyflags *fp;

	for (sp = gettystrs; sp->field; sp++)
		if (!sp->value)
			sp->value = sp->defalt;
	for (np = gettynums; np->field; np++)
		if (!np->set)
			np->value = np->defalt;
	for (fp = gettyflags; fp->field; fp++)
		if (!fp->set)
			fp->value = fp->defalt;
}

static char **
charnames[] = {
	&ER, &KL, &IN, &QU, &XN, &XF, &ET, &BK,
	&SU, &DS, &RP, &FL, &WE, &LN, 0
};

static char *
charvars[] = {
	&tmode.sg_erase, &tmode.sg_kill, &tc.t_intrc,
	&tc.t_quitc, &tc.t_startc, &tc.t_stopc,
	&tc.t_eofc, &tc.t_brkc, &ltc.t_suspc,
	&ltc.t_dsuspc, &ltc.t_rprntc, &ltc.t_flushc,
	&ltc.t_werasc, &ltc.t_lnextc, 0
};

I 15
void
E 15
setchars()
{
	register int i;
	register char *p;

	for (i = 0; charnames[i]; i++) {
		p = *charnames[i];
		if (p && *p)
			*charvars[i] = *p;
		else
D 6
			*charvars[i] = '\0377';
E 6
I 6
			*charvars[i] = '\377';
E 6
	}
}

long
setflags(n)
I 15
	int n;
E 15
{
	register long f;

	switch (n) {
	case 0:
		if (F0set)
			return(F0);
		break;
	case 1:
		if (F1set)
			return(F1);
		break;
	default:
		if (F2set)
			return(F2);
		break;
	}

	f = 0;

	if (AP)
		f |= ANYP;
	else if (OP)
		f |= ODDP;
	else if (EP)
		f |= EVENP;

	if (UC)
		f |= LCASE;

	if (NL)
		f |= CRMOD;

	f |= delaybits();

	if (n == 1) {		/* read mode flags */
		if (RW)
			f |= RAW;
		else
			f |= CBREAK;
		return (f);
	}

	if (!HT)
		f |= XTABS;

	if (n == 0)
		return (f);

	if (CB)
		f |= CRTBS;

	if (CE)
		f |= CRTERA;

I 3
	if (CK)
		f |= CRTKIL;

E 3
	if (PE)
		f |= PRTERA;

	if (EC)
		f |= ECHO;

	if (XC)
		f |= CTLECH;

I 8
	if (DX)
		f |= DECCTQ;

E 8
	return (f);
}

struct delayval {
	unsigned	delay;		/* delay in ms */
	int		bits;
};

/*
 * below are random guesses, I can't be bothered checking
 */

struct delayval	crdelay[] = {
D 2
	20,		CR1,
	30,		CR2,
	40,		CR3,
E 2
I 2
D 15
	1,		CR1,
	2,		CR2,
	3,		CR3,
	83,		CR1,
	166,		CR2,
E 2
	0,		CR3,
E 15
I 15
	{ 1,		CR1 },
	{ 2,		CR2 },
	{ 3,		CR3 },
	{ 83,		CR1 },
	{ 166,		CR2 },
	{ 0,		CR3 },
E 15
};

struct delayval nldelay[] = {
D 15
	1,		NL1,		/* special, calculated */
D 2
	16,		NL2,
	30,		NL3,
E 2
I 2
	2,		NL2,
	3,		NL3,
	100,		NL2,
E 2
	0,		NL3,
E 15
I 15
	{ 1,		NL1 },		/* special, calculated */
	{ 2,		NL2 },
	{ 3,		NL3 },
	{ 100,		NL2 },
	{ 0,		NL3 },
E 15
};

struct delayval	bsdelay[] = {
I 2
D 15
	1,		BS1,
E 2
	0,		0,
E 15
I 15
	{ 1,		BS1 },
	{ 0,		0 },
E 15
};

struct delayval	ffdelay[] = {
I 2
D 15
	1,		FF1,
E 2
	1750,		FF1,
	0,		FF1,
E 15
I 15
	{ 1,		FF1 },
	{ 1750,		FF1 },
	{ 0,		FF1 },
E 15
};

struct delayval	tbdelay[] = {
D 2
	10,		TAB1,
	20,		TAB2,
E 2
I 2
D 15
	1,		TAB1,
	2,		TAB2,
	3,		XTABS,		/* this is expand tabs */
	100,		TAB1,
E 2
	0,		TAB2,
E 15
I 15
	{ 1,		 TAB1 },
	{ 2,		 TAB2 },
	{ 3,		XTABS },	/* this is expand tabs */
	{ 100,		 TAB1 },
	{ 0,		 TAB2 },
E 15
};

I 15
int
E 15
delaybits()
{
D 15
	register f;
E 15
I 15
	register int f;
E 15

	f  = adelay(CD, crdelay);
	f |= adelay(ND, nldelay);
	f |= adelay(FD, ffdelay);
	f |= adelay(TD, tbdelay);
	f |= adelay(BD, bsdelay);
	return (f);
}

I 15
int
E 15
adelay(ms, dp)
	register ms;
	register struct delayval *dp;
{
	if (ms == 0)
		return (0);
	while (dp->delay && ms > dp->delay)
		dp++;
	return (dp->bits);
}

char	editedhost[32];

I 15
void
E 15
edithost(pat)
	register char *pat;
{
	register char *host = HN;
	register char *res = editedhost;

	if (!pat)
		pat = "";
	while (*pat) {
		switch (*pat) {

		case '#':
			if (*host)
				host++;
			break;

		case '@':
			if (*host)
				*res++ = *host++;
			break;

		default:
			*res++ = *pat;
			break;

		}
		if (res == &editedhost[sizeof editedhost - 1]) {
			*res = '\0';
			return;
		}
		pat++;
	}
	if (*host)
		strncpy(res, host, sizeof editedhost - (res - editedhost) - 1);
	else
		*res = '\0';
	editedhost[sizeof editedhost - 1] = '\0';
}

struct speedtab {
	int	speed;
	int	uxname;
} speedtab[] = {
D 15
	50,	B50,
	75,	B75,
	110,	B110,
	134,	B134,
	150,	B150,
	200,	B200,
	300,	B300,
	600,	B600,
	1200,	B1200,
	1800,	B1800,
	2400,	B2400,
	4800,	B4800,
	9600,	B9600,
	19200,	EXTA,
	19,	EXTA,		/* for people who say 19.2K */
	38400,	EXTB,
	38,	EXTB,
	7200,	EXTB,		/* alternative */
	0
E 15
I 15
	{ 50,	  B50 },
	{ 75,	  B75 },
	{ 110,	 B110 },
	{ 134,	 B134 },
	{ 150,	 B150 },
	{ 200,	 B200 },
	{ 300,	 B300 },
	{ 600,	 B600 },
	{ 1200,	B1200 },
	{ 1800,	B1800 },
	{ 2400,	B2400 },
	{ 4800,	B4800 },
	{ 9600,	B9600 },
	{ 19200, EXTA },
	{ 19,	 EXTA },	/* for people who say 19.2K */
	{ 38400, EXTB },
	{ 38,	 EXTB },
	{ 7200,	 EXTB },	/* alternative */
	{ 0 }
E 15
};

I 15
int
E 15
speed(val)
I 15
	int val;
E 15
{
	register struct speedtab *sp;

	if (val <= 15)
D 4
		return(val);
E 4
I 4
		return (val);
E 4

	for (sp = speedtab; sp->speed; sp++)
		if (sp->speed == val)
			return (sp->uxname);
	
	return (B300);		/* default in impossible cases */
}

I 15
void
E 15
makeenv(env)
	char *env[];
{
	static char termbuf[128] = "TERM=";
	register char *p, *q;
	register char **ep;
D 15
	char *index();
E 15

	ep = env;
	if (TT && *TT) {
		strcat(termbuf, TT);
		*ep++ = termbuf;
	}
	if (p = EV) {
		q = p;
D 15
		while (q = index(q, ',')) {
E 15
I 15
		while (q = strchr(q, ',')) {
E 15
			*q++ = '\0';
			*ep++ = p;
			p = q;
		}
		if (*p)
			*ep++ = p;
	}
	*ep = (char *)0;
}

/*
 * This speed select mechanism is written for the Develcon DATASWITCH.
 * The Develcon sends a string of the form "B{speed}\n" at a predefined
 * baud rate. This string indicates the user's actual speed.
 * The routine below returns the terminal type mapped from derived speed.
 */
struct	portselect {
	char	*ps_baud;
	char	*ps_type;
} portspeeds[] = {
	{ "B110",	"std.110" },
	{ "B134",	"std.134" },
	{ "B150",	"std.150" },
	{ "B300",	"std.300" },
	{ "B600",	"std.600" },
	{ "B1200",	"std.1200" },
	{ "B2400",	"std.2400" },
	{ "B4800",	"std.4800" },
	{ "B9600",	"std.9600" },
I 7
	{ "B19200",	"std.19200" },
E 7
	{ 0 }
};

char *
portselector()
{
	char c, baud[20], *type = "default";
	register struct portselect *ps;
	int len;

	alarm(5*60);
	for (len = 0; len < sizeof (baud) - 1; len++) {
D 14
		if (read(0, &c, 1) <= 0)
E 14
I 14
		if (read(STDIN_FILENO, &c, 1) <= 0)
E 14
			break;
		c &= 0177;
		if (c == '\n' || c == '\r')
			break;
		if (c == 'B')
			len = 0;	/* in case of leading garbage */
		baud[len] = c;
	}
	baud[len] = '\0';
	for (ps = portspeeds; ps->ps_baud; ps++)
		if (strcmp(ps->ps_baud, baud) == 0) {
			type = ps->ps_type;
			break;
		}
	sleep(2);	/* wait for connection to complete */
I 4
	return (type);
}

/*
 * This auto-baud speed select mechanism is written for the Micom 600
 * portselector. Selection is done by looking at how the character '\r'
 * is garbled at the different speeds.
 */
#include <sys/time.h>

char *
autobaud()
{
	int rfds;
	struct timeval timeout;
	char c, *type = "9600-baud";
	int null = 0;

	ioctl(0, TIOCFLUSH, &null);
	rfds = 1 << 0;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
D 13
	if (select(32, &rfds, (int *)0, (int *)0, &timeout) <= 0)
E 13
I 13
	if (select(32, (fd_set *)&rfds, (fd_set *)NULL,
	    (fd_set *)NULL, &timeout) <= 0)
E 13
		return (type);
D 14
	if (read(0, &c, sizeof(char)) != sizeof(char))
E 14
I 14
	if (read(STDIN_FILENO, &c, sizeof(char)) != sizeof(char))
E 14
		return (type);
	timeout.tv_sec = 0;
	timeout.tv_usec = 20;
D 13
	(void) select(32, (int *)0, (int *)0, (int *)0, &timeout);
E 13
I 13
	(void) select(32, (fd_set *)NULL, (fd_set *)NULL,
	    (fd_set *)NULL, &timeout);
E 13
	ioctl(0, TIOCFLUSH, &null);
	switch (c & 0377) {

	case 0200:		/* 300-baud */
		type = "300-baud";
		break;

	case 0346:		/* 1200-baud */
		type = "1200-baud";
		break;

	case  015:		/* 2400-baud */
	case 0215:
		type = "2400-baud";
		break;

	default:		/* 4800-baud */
		type = "4800-baud";
		break;

	case 0377:		/* 9600-baud */
		type = "9600-baud";
		break;
	}
E 4
	return (type);
}
E 1
