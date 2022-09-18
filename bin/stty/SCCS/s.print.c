h15321
s 00001/00001/00239
d D 8.6 94/04/16 07:14:46 bostic 11 10
c modes.c was fixed to reflect the fact that MDMBUF is a cflag,
c but print.c wasn't.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00001/00001/00239
d D 8.5 94/04/02 10:02:30 pendry 10 9
c add 1994 copyright
e
s 00006/00005/00234
d D 8.4 94/04/01 03:39:15 pendry 9 8
c prettyness police
e
s 00002/00000/00237
d D 8.3 94/03/26 06:12:30 bostic 8 7
c prettiness police
e
s 00009/00004/00228
d D 8.2 94/03/17 07:58:05 bostic 7 6
c support vmin, vtime display and set
e
s 00002/00002/00230
d D 8.1 93/05/31 15:47:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00230
d D 5.5 93/04/29 15:17:41 bostic 5 4
c prettiness police
e
s 00002/00002/00230
d D 5.4 91/06/10 07:39:46 bostic 4 3
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00002/00002/00230
d D 5.3 91/06/05 15:22:21 bostic 3 2
c distribute the rest of the main loop into the modes and cchars modules
c bsearch the cchars arrays, minor cleanups
e
s 00000/00003/00232
d D 5.2 91/06/04 17:42:47 bostic 2 1
c stty.h includes ioctl.h and termios.h; extern.h defines mode/char arrays
e
s 00235/00000/00000
d D 5.1 91/05/02 13:34:45 bostic 1 0
c date and time created 91/05/02 13:34:45 by bostic
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
D 10
 * Copyright (c) 1991, 1993
E 10
I 10
 * Copyright (c) 1991, 1993, 1994
E 10
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 8

E 8
D 2
#include <sys/ioctl.h>
#include <termios.h>
E 2
#include <stddef.h>
#include <stdio.h>
#include <string.h>
I 8

E 8
#include "stty.h"
#include "extern.h"

static void  binit __P((char *));
static void  bput __P((char *));
D 7
static char *ccval __P((int));
E 7
I 7
static char *ccval __P((struct cchar *, int));
E 7

void
print(tp, wp, ldisc, fmt)
	struct termios *tp;
	struct winsize *wp;
	int ldisc;
	enum FMT fmt;
{
D 2
	extern struct cchar cchars1[];
E 2
D 9
	register struct cchar *p;
	register long tmp;
	register int cnt;
	register u_char *cc;
	int ispeed, ospeed;
E 9
I 9
	struct cchar *p;
	long tmp;
	u_char *cc;
	int cnt, ispeed, ospeed;
E 9
	char buf1[100], buf2[100];

	cnt = 0;

	/* Line discipline. */
	if (ldisc != TTYDISC) {
		switch(ldisc) {
		case TABLDISC:	
			cnt += printf("tablet disc; ");
			break;
		case SLIPDISC:	
			cnt += printf("slip disc; ");
			break;
		default:	
			cnt += printf("#%d disc; ", ldisc);
			break;
		}
	}

	/* Line speed. */
	ispeed = cfgetispeed(tp);
	ospeed = cfgetospeed(tp);
	if (ispeed != ospeed)
		cnt +=
		    printf("ispeed %d baud; ospeed %d baud;", ispeed, ospeed);
	else
		cnt += printf("speed %d baud;", ispeed);
	if (fmt >= BSD)
		cnt += printf(" %d rows; %d columns;", wp->ws_row, wp->ws_col);
	if (cnt)
		(void)printf("\n");

#define	on(f)	((tmp&f) != 0)
#define put(n, f, d) \
	if (fmt >= BSD || on(f) != d) \
		bput(n + on(f));

	/* "local" flags */
	tmp = tp->c_lflag;
	binit("lflags");
	put("-icanon", ICANON, 1);
	put("-isig", ISIG, 1);
	put("-iexten", IEXTEN, 1);
	put("-echo", ECHO, 1);
	put("-echoe", ECHOE, 0);
	put("-echok", ECHOK, 0);
	put("-echoke", ECHOKE, 0);
	put("-echonl", ECHONL, 0);
	put("-echoctl", ECHOCTL, 0);
	put("-echoprt", ECHOPRT, 0);
	put("-altwerase", ALTWERASE, 0);
	put("-noflsh", NOFLSH, 0);
	put("-tostop", TOSTOP, 0);
D 11
	put("-mdmbuf", MDMBUF, 0);
E 11
	put("-flusho", FLUSHO, 0);
	put("-pendin", PENDIN, 0);
	put("-nokerninfo", NOKERNINFO, 0);
	put("-extproc", EXTPROC, 0);

	/* input flags */
	tmp = tp->c_iflag;
	binit("iflags");
	put("-istrip", ISTRIP, 0);
	put("-icrnl", ICRNL, 1);
	put("-inlcr", INLCR, 0);
	put("-igncr", IGNCR, 0);
	put("-ixon", IXON, 1);
	put("-ixoff", IXOFF, 0);
	put("-ixany", IXANY, 1);
	put("-imaxbel", IMAXBEL, 1);
	put("-ignbrk", IGNBRK, 0);
	put("-brkint", BRKINT, 1);
	put("-inpck", INPCK, 0);
	put("-ignpar", IGNPAR, 0);
	put("-parmrk", PARMRK, 0);

	/* output flags */
	tmp = tp->c_oflag;
	binit("oflags");
	put("-opost", OPOST, 1);
	put("-onlcr", ONLCR, 1);
	put("-oxtabs", OXTABS, 1);

	/* control flags (hardware state) */
	tmp = tp->c_cflag;
	binit("cflags");
	put("-cread", CREAD, 1);
	switch(tmp&CSIZE) {
	case CS5:
		bput("cs5");
		break;
	case CS6:
		bput("cs6");
		break;
	case CS7:
		bput("cs7");
		break;
	case CS8:
		bput("cs8");
		break;
	}
	bput("-parenb" + on(PARENB));
	put("-parodd", PARODD, 0);
	put("-hupcl", HUPCL, 1);
	put("-clocal", CLOCAL, 0);
	put("-cstopb", CSTOPB, 0);
	put("-crtscts", CRTSCTS, 0);
I 11
	put("-mdmbuf", MDMBUF, 0);
E 11

	/* special control characters */
	cc = tp->c_cc;
	if (fmt == POSIX) {
		binit("cchars");
D 3
		for (p = cchars1; p->name; ++p) {
E 3
I 3
D 4
		for (p = cchars1; *p->name; ++p) {
E 4
I 4
		for (p = cchars1; p->name; ++p) {
E 4
E 3
			(void)snprintf(buf1, sizeof(buf1), "%s = %s;",
D 7
			    p->name, ccval(cc[p->sub]));
E 7
I 7
			    p->name, ccval(p, cc[p->sub]));
E 7
			bput(buf1);
		}
		binit(NULL);
	} else {
		binit(NULL);
D 3
		for (p = cchars1, cnt = 0; p->name; ++p) {
E 3
I 3
D 4
		for (p = cchars1, cnt = 0; *p->name; ++p) {
E 4
I 4
		for (p = cchars1, cnt = 0; p->name; ++p) {
E 4
E 3
			if (fmt != BSD && cc[p->sub] == p->def)
				continue;
#define	WD	"%-8s"
			(void)sprintf(buf1 + cnt * 8, WD, p->name);
D 7
			(void)sprintf(buf2 + cnt * 8, WD, ccval(cc[p->sub]));
E 7
I 7
			(void)sprintf(buf2 + cnt * 8, WD, ccval(p, cc[p->sub]));
E 7
			if (++cnt == LINELENGTH / 8) {
				cnt = 0;
				(void)printf("%s\n", buf1);
				(void)printf("%s\n", buf2);
			}
		}
		if (cnt) {
			(void)printf("%s\n", buf1);
			(void)printf("%s\n", buf2);
		}
	}
}

static int col;
static char *label;

static void
binit(lb)
	char *lb;
{
I 9

E 9
	if (col) {
		(void)printf("\n");
		col = 0;
	}
	label = lb;
}

static void
bput(s)
	char *s;
{
I 9

E 9
	if (col == 0) {
		col = printf("%s: %s", label, s);
		return;
	}
	if ((col + strlen(s)) > LINELENGTH) {
		(void)printf("\n\t");
		col = printf("%s", s) + 8;
		return;
	}
	col += printf(" %s", s);
}

static char *
D 7
ccval(c)
E 7
I 7
ccval(p, c)
	struct cchar *p;
E 7
	int c;
{
	static char buf[5];
	char *bp;

	if (c == _POSIX_VDISABLE)
D 5
		return("<undef>");
E 5
I 5
		return ("<undef>");
E 5

I 7
	if (p->sub == VMIN || p->sub == VTIME) {
		(void)snprintf(buf, sizeof(buf), "%d", c);
		return (buf);
	}
E 7
	bp = buf;
	if (c & 0200) {
		*bp++ = 'M';
		*bp++ = '-';
		c &= 0177;
	}
	if (c == 0177) {
		*bp++ = '^';
		*bp++ = '?';
	}
	else if (c < 040) {
		*bp++ = '^';
		*bp++ = c + '@';
	}
	else
		*bp++ = c;
	*bp = '\0';
D 5
	return(buf);
E 5
I 5
	return (buf);
E 5
}
E 1
