h05389
s 00001/00001/00102
d D 8.6 94/04/02 10:02:16 pendry 11 10
c add 1994 copyright
e
s 00013/00015/00090
d D 8.5 94/04/01 03:39:13 pendry 10 9
c prettyness police
e
s 00014/00078/00091
d D 8.4 94/03/28 08:20:17 bostic 9 8
c use the cchars1 array instead of listing the options
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00006/00006/00163
d D 8.3 94/03/26 06:14:15 bostic 8 7
c use "min" and "time", not "vmin" and "vtime"
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00010/00000/00159
d D 8.2 94/03/17 07:58:05 bostic 7 6
c support vmin, vtime display and set
e
s 00002/00002/00157
d D 8.1 93/05/31 15:47:39 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00004/00152
d D 5.5 93/04/29 15:18:43 bostic 5 4
c use C library err/warn routines, index->strchr, etc.
e
s 00001/00001/00155
d D 5.4 91/06/10 07:39:43 bostic 4 3
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00001/00001/00155
d D 5.3 91/06/07 08:32:09 bostic 3 2
c can't use NULL terminator any more
e
s 00000/00003/00156
d D 5.2 91/06/04 17:42:45 bostic 2 1
c stty.h includes ioctl.h and termios.h; extern.h defines mode/char arrays
e
s 00159/00000/00000
d D 5.1 91/05/02 13:34:40 bostic 1 0
c date and time created 91/05/02 13:34:40 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 11
 * Copyright (c) 1991, 1993
E 11
I 11
 * Copyright (c) 1991, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 5

#include <err.h>
E 5
D 2
#include <sys/ioctl.h>
#include <termios.h>
E 2
#include <stdio.h>
#include <string.h>
I 5

E 5
#include "stty.h"
#include "extern.h"

D 10
static void gerr __P((char *));
E 10
I 10
static void
gerr(s)
	char *s;
{
	if (s)
		errx(1, "illegal gfmt1 option -- %s", s);
	else
		errx(1, "illegal gfmt1 option");
}
E 10

void
gprint(tp, wp, ldisc)
	struct termios *tp;
	struct winsize *wp;
	int ldisc;
{
D 2
	extern struct cchar cchars1[];
E 2
D 10
	register struct cchar *cp;
E 10
I 10
	struct cchar *cp;
E 10

	(void)printf("gfmt1:cflag=%x:iflag=%x:lflag=%x:oflag=%x:",
	    tp->c_cflag, tp->c_iflag, tp->c_lflag, tp->c_oflag);
D 3
	for (cp = cchars1; cp->name; ++cp)
E 3
I 3
D 4
	for (cp = cchars1; *cp->name; ++cp)
E 4
I 4
	for (cp = cchars1; cp->name; ++cp)
E 4
E 3
		(void)printf("%s=%x:", cp->name, tp->c_cc[cp->sub]);
	(void)printf("ispeed=%d:ospeed=%d\n", cfgetispeed(tp), cfgetospeed(tp));
}

void
gread(tp, s) 
D 10
	register struct termios *tp;
E 10
I 10
	struct termios *tp;
E 10
	char *s;
{
D 10
	register char *ep, *p;
I 9
	register struct cchar *cp;
E 10
I 10
	struct cchar *cp;
	char *ep, *p;
E 10
E 9
	long tmp;

D 9
#define	CHK(s)	(*p == s[0] && !strcmp(p, s))
D 5
	if (!(s = index(s, ':')))
E 5
I 5
	if (!(s = strchr(s, ':')))
E 9
I 9
	if ((s = strchr(s, ':')) == NULL)
E 9
E 5
		gerr(NULL);
D 9
	for (++s; s;) {
E 9
I 9
	for (++s; s != NULL;) {
E 9
		p = strsep(&s, ":\0");
		if (!p || !*p)
			break;
D 5
		if (!(ep = index(p, '=')))
E 5
I 5
		if (!(ep = strchr(p, '=')))
E 5
			gerr(p);
		*ep++ = '\0';
		(void)sscanf(ep, "%lx", &tmp);
I 9

#define	CHK(s)	(*p == s[0] && !strcmp(p, s))
E 9
		if (CHK("cflag")) {
			tp->c_cflag = tmp;
			continue;
		}
D 9
		if (CHK("discard")) {
			tp->c_cc[VDISCARD] = tmp;
			continue;
		}
		if (CHK("dsusp")) {
			tp->c_cc[VDSUSP] = tmp;
			continue;
		}
		if (CHK("eof")) {
			tp->c_cc[VEOF] = tmp;
			continue;
		}
		if (CHK("eol")) {
			tp->c_cc[VEOL] = tmp;
			continue;
		}
		if (CHK("eol2")) {
			tp->c_cc[VEOL2] = tmp;
			continue;
		}
		if (CHK("erase")) {
			tp->c_cc[VERASE] = tmp;
			continue;
		}
E 9
		if (CHK("iflag")) {
			tp->c_iflag = tmp;
			continue;
		}
D 9
		if (CHK("intr")) {
			tp->c_cc[VINTR] = tmp;
			continue;
		}
E 9
		if (CHK("ispeed")) {
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_ispeed = tmp;
			continue;
		}
D 9
		if (CHK("kill")) {
			tp->c_cc[VKILL] = tmp;
			continue;
		}
E 9
		if (CHK("lflag")) {
			tp->c_lflag = tmp;
			continue;
		}
D 9
		if (CHK("lnext")) {
			tp->c_cc[VLNEXT] = tmp;
			continue;
		}
I 8
		if (CHK("min")) {
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_cc[VMIN] = tmp;
			continue;
		}
E 9
E 8
		if (CHK("oflag")) {
			tp->c_oflag = tmp;
			continue;
		}
		if (CHK("ospeed")) {
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_ospeed = tmp;
			continue;
		}
D 9
		if (CHK("quit")) {
			tp->c_cc[VQUIT] = tmp;
			continue;
		}
		if (CHK("reprint")) {
			tp->c_cc[VREPRINT] = tmp;
			continue;
		}
		if (CHK("start")) {
			tp->c_cc[VSTART] = tmp;
			continue;
		}
		if (CHK("status")) {
			tp->c_cc[VSTATUS] = tmp;
			continue;
		}
		if (CHK("stop")) {
			tp->c_cc[VSTOP] = tmp;
			continue;
		}
		if (CHK("susp")) {
			tp->c_cc[VSUSP] = tmp;
			continue;
		}
I 7
D 8
		if (CHK("vmin")) {
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_cc[VMIN] = tmp;
			continue;
		}
		if (CHK("vtime")) {
E 8
I 8
		if (CHK("time")) {
E 8
			(void)sscanf(ep, "%ld", &tmp);
			tp->c_cc[VTIME] = tmp;
			continue;
		}
E 7
		if (CHK("werase")) {
			tp->c_cc[VWERASE] = tmp;
			continue;
		}
		gerr(p);
E 9
I 9
		for (cp = cchars1; cp->name != NULL; ++cp)
			if (CHK(cp->name)) {
				if (cp->sub == VMIN || cp->sub == VTIME)
					(void)sscanf(ep, "%ld", &tmp);
				tp->c_cc[cp->sub] = tmp;
				break;
			}
		if (cp->name == NULL)
			gerr(p);
E 9
	}
D 10
}

static void
gerr(s)
	char *s;
{
	if (s)
D 5
		err("illegal gfmt1 option -- %s", s);
E 5
I 5
		errx(1, "illegal gfmt1 option -- %s", s);
E 5
	else
D 5
		err("illegal gfmt1 option");
E 5
I 5
		errx(1, "illegal gfmt1 option");
E 10
E 5
}
E 1
