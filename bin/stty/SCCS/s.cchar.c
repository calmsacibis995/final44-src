h29373
s 00001/00001/00118
d D 8.5 94/04/02 10:02:13 pendry 12 11
c add 1994 copyright
e
s 00009/00010/00110
d D 8.4 94/04/01 03:39:12 pendry 11 10
c prettyness police
e
s 00002/00002/00118
d D 8.3 94/03/26 06:14:14 bostic 10 9
c use "min" and "time", not "vmin" and "vtime"
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00023/00002/00097
d D 8.2 94/03/17 07:58:04 bostic 9 8
c support vmin, vtime display and set
e
s 00002/00002/00097
d D 8.1 93/05/31 15:47:34 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00033/00028/00066
d D 5.7 93/04/29 15:17:06 bostic 7 6
c use C library err/warn routines; make GCC 2 happy
e
s 00000/00002/00094
d D 5.6 92/07/10 11:11:48 marc 6 5
c remove xon and xoff
e
s 00001/00001/00095
d D 5.5 91/08/12 14:47:37 bostic 5 4
c picked and dropped a bit too fast...
e
s 00004/00004/00092
d D 5.4 91/06/10 07:39:41 bostic 4 3
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00048/00002/00048
d D 5.3 91/06/05 15:22:18 bostic 3 2
c distribute the rest of the main loop into the modes and cchars modules
c bsearch the cchars arrays, minor cleanups
e
s 00000/00001/00050
d D 5.2 91/06/04 17:42:44 bostic 2 1
c stty.h includes ioctl.h and termios.h; extern.h defines mode/char arrays
e
s 00051/00000/00000
d D 5.1 91/05/02 13:34:29 bostic 1 0
c date and time created 91/05/02 13:34:29 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 12
 * Copyright (c) 1991, 1993
E 12
I 12
 * Copyright (c) 1991, 1993, 1994
E 12
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 7

#include <err.h>
I 9
#include <limits.h>
E 9
E 7
D 2
#include <termios.h>
E 2
#include <stddef.h>
I 3
#include <stdlib.h>
#include <string.h>
I 7

E 7
E 3
#include "stty.h"
I 3
#include "extern.h"
E 3

/*
 * Special control characters.
 *
 * Cchars1 are the standard names, cchars2 are the old aliases.
 * The first are displayed, but both are recognized on the
 * command line.
 */
struct cchar cchars1[] = {
D 7
	"discard",	VDISCARD, 	CDISCARD,
	"dsusp", 	VDSUSP,		CDSUSP,
	"eof",		VEOF,		CEOF,
	"eol",		VEOL,		CEOL,
	"eol2",		VEOL2,		CEOL,
	"erase",	VERASE,		CERASE,
	"intr",		VINTR,		CINTR,
	"kill",		VKILL,		CKILL,
	"lnext",	VLNEXT,		CLNEXT,
	"quit",		VQUIT,		CQUIT,
	"reprint",	VREPRINT, 	CREPRINT,
	"start",	VSTART,		CSTART,
	"status",	VSTATUS, 	CSTATUS,
	"stop",		VSTOP,		CSTOP,
	"susp",		VSUSP,		CSUSP,
	"werase",	VWERASE,	CWERASE,
D 3
	NULL
E 3
I 3
D 4
	"",						/* not NULL */
E 4
I 4
	NULL,
E 7
I 7
	{ "discard",	VDISCARD, 	CDISCARD },
	{ "dsusp", 	VDSUSP,		CDSUSP },
	{ "eof",	VEOF,		CEOF },
	{ "eol",	VEOL,		CEOL },
	{ "eol2",	VEOL2,		CEOL },
	{ "erase",	VERASE,		CERASE },
	{ "intr",	VINTR,		CINTR },
	{ "kill",	VKILL,		CKILL },
	{ "lnext",	VLNEXT,		CLNEXT },
I 10
	{ "min",	VMIN,		CMIN },
E 10
	{ "quit",	VQUIT,		CQUIT },
	{ "reprint",	VREPRINT, 	CREPRINT },
	{ "start",	VSTART,		CSTART },
	{ "status",	VSTATUS, 	CSTATUS },
	{ "stop",	VSTOP,		CSTOP },
	{ "susp",	VSUSP,		CSUSP },
I 9
D 10
	{ "vmin",	VMIN,		CMIN },
	{ "vtime",	VTIME,		CTIME },
E 10
I 10
	{ "time",	VTIME,		CTIME },
E 10
E 9
	{ "werase",	VWERASE,	CWERASE },
	{ NULL },
E 7
E 4
E 3
};

struct cchar cchars2[] = {
D 7
	"brk",		VEOL,		CEOL,
	"flush",	VDISCARD, 	CDISCARD,
	"rprnt",	VREPRINT, 	CREPRINT,
D 6
	"xoff",		VSTOP,		CSTOP,
	"xon",		VSTART,		CSTART,
E 6
D 3
	NULL
E 3
I 3
D 4
	"",						/* not NULL */
E 4
I 4
	NULL,
E 7
I 7
	{ "brk",	VEOL,		CEOL },
	{ "flush",	VDISCARD, 	CDISCARD },
	{ "rprnt",	VREPRINT, 	CREPRINT },
	{ NULL },
E 7
E 4
E 3
};
I 3

I 11
static int
c_cchar(a, b)
        const void *a, *b;
{

        return (strcmp(((struct cchar *)a)->name, ((struct cchar *)b)->name));
}

E 11
I 7
int
E 7
csearch(argvp, ip)
	char ***argvp;
	struct info *ip;
{
D 7
	extern char *usage;
E 7
D 11
	register struct cchar *cp;
	struct cchar tmp;
E 11
I 11
	struct cchar *cp, tmp;
E 11
D 9
	char *arg, *name;
E 9
I 9
	long val;
	char *arg, *ep, *name;
E 9
D 11
	static int c_cchar __P((const void *, const void *));
E 11
		
	name = **argvp;

	tmp.name = name;
	if (!(cp = (struct cchar *)bsearch(&tmp, cchars1,
D 4
	    sizeof(cchars1)/sizeof(struct cchar), sizeof(struct cchar),
E 4
I 4
	    sizeof(cchars1)/sizeof(struct cchar) - 1, sizeof(struct cchar),
E 4
	    c_cchar)) && !(cp = (struct cchar *)bsearch(&tmp, cchars1,
D 4
	    sizeof(cchars1)/sizeof(struct cchar), sizeof(struct cchar),
E 4
I 4
	    sizeof(cchars1)/sizeof(struct cchar) - 1, sizeof(struct cchar),
E 4
	    c_cchar)))
D 7
		return(0);
E 7
I 7
		return (0);
E 7

	arg = *++*argvp;
D 7
	if (!arg)
		err("option requires an argument -- %s\n%s", name, usage);
E 7
I 7
	if (!arg) {
		warnx("option requires an argument -- %s", name);
		usage();
	}
E 7

D 5
#define CHK(s)  (*name == s[0] && !strcmp(name, s))
E 5
I 5
#define CHK(s)  (*arg == s[0] && !strcmp(arg, s))
E 5
	if (CHK("undef") || CHK("<undef>"))
		ip->t.c_cc[cp->sub] = _POSIX_VDISABLE;
D 9
	else if (arg[0] == '^')
E 9
I 9
	else if (cp->sub == VMIN || cp->sub == VTIME) {
		val = strtol(arg, &ep, 10);
		if (val == _POSIX_VDISABLE) {
			warnx("value of %ld would disable the option -- %s",
			    val, name);
			usage();
		}
		if (val > UCHAR_MAX) {
			warnx("maximum option value is %d -- %s",
			    UCHAR_MAX, name);
			usage();
		}
		if (*ep != '\0') {
			warnx("option requires a numeric argument -- %s", name);
			usage();
		}
		ip->t.c_cc[cp->sub] = val;
	} else if (arg[0] == '^')
E 9
		ip->t.c_cc[cp->sub] = (arg[1] == '?') ? 0177 :
		    (arg[1] == '-') ? _POSIX_VDISABLE : arg[1] & 037;
	else
		ip->t.c_cc[cp->sub] = arg[0];
	ip->set = 1;
D 7
	return(1);
E 7
I 7
	return (1);
E 7
D 11
}

D 7
static
E 7
I 7
static int
E 7
c_cchar(a, b)
        const void *a, *b;
{
D 7
        return(strcmp(((struct cchar *)a)->name, ((struct cchar *)b)->name));
E 7
I 7
        return (strcmp(((struct cchar *)a)->name, ((struct cchar *)b)->name));
E 11
E 7
}
E 3
E 1
