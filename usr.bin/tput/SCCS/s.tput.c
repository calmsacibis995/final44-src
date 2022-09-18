h34946
s 00002/00002/00198
d D 8.3 95/04/28 15:34:18 bostic 12 11
c Switch order rows and cols are extracted from the command line.
c From: "J.T. Conklin" <jtc@NetBSD.ORG>
e
s 00099/00018/00101
d D 8.2 94/03/19 11:27:54 bostic 11 10
c tput patch to support 'tput cm 10 20'
c From: Christos-Zoulas@deshaw.com (Christos Zoulas)
e
s 00005/00005/00114
d D 8.1 93/06/06 16:37:23 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00014/00115
d D 5.7 90/06/07 11:57:39 bostic 9 8
c new copyright notice
e
s 00004/00005/00128
d D 5.6 90/05/12 15:27:42 bostic 8 7
c don't fail if not a terminal
e
s 00001/00002/00132
d D 5.5 90/03/14 17:46:07 bostic 7 6
c initialize exitval in the right place
e
s 00049/00031/00085
d D 5.4 89/10/31 10:12:31 bostic 6 5
c add boolean and numeric capabilities, key word longname; specify exit values
e
s 00083/00008/00033
d D 5.3 89/10/30 17:07:41 bostic 5 4
c replace clear with simple version of tput
e
s 00027/00044/00014
d D 5.2 88/08/12 12:45:25 bostic 4 3
c general cleanup, it was pretty unreasonable
e
s 00016/00001/00042
d D 5.1 85/05/31 09:08:12 dist 3 2
c Add copyright
e
s 00001/00001/00042
d D 4.2 85/01/08 17:13:35 serge 2 1
c Exit status was inverted.
e
s 00043/00000/00000
d D 4.1 80/10/01 17:25:36 bill 1 0
c date and time created 80/10/01 17:25:36 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
E 3
I 3
D 9
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1980, 1988 Regents of the University of California.
E 9
I 9
/*-
D 10
 * Copyright (c) 1980, 1988 The Regents of the University of California.
E 9
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1980, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 9
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
E 4
 */

#ifndef lint
D 10
char copyright[] =
D 4
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 4
I 4
D 9
"%Z% Copyright (c) 1980, 1988 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1980, 1988 The Regents of the University of California.\n\
E 9
E 4
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1980, 1988, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 3
D 4
/* load me with -ltermlib */
/* #include <retrofit.h> on version 6 */
/*
 * clear - clear the screen
 */

#include <stdio.h>
#include <sgtty.h>

char	*getenv();
char	*tgetstr();
char	PC;
short	ospeed;
#undef	putchar
int	putchar();

E 4
D 5
main()
E 5
I 5
#include <sys/termios.h>
I 11

#include <err.h>
#include <curses.h>
E 11
#include <stdio.h>
I 11
#include <stdlib.h>
E 11
#include <unistd.h>

I 11
static void   prlongname __P((char *));
static void   setospeed __P((void));
static void   outc __P((int));
static void   usage __P((void));
static char **process __P((char *, char *, char **));

int
E 11
main(argc, argv)
	int argc;
	char **argv;
E 5
{
D 4
	char *cp = getenv("TERM");
	char clbuf[20];
	char pcbuf[20];
	char *clbp = clbuf;
	char *pcbp = pcbuf;
	char *clear;
	char buf[1024];
	char *pc;
	struct sgttyb tty;
E 4
I 4
D 5
	char *cp, *clbp, clbuf[100], tbuf[1024], *getenv(), *tgetstr();
	int putchar();
E 5
I 5
	extern char *optarg;
	extern int optind;
D 6
	int ch, exitval, myputchar();
	char *ap, *p, *term, buf[1024], tbuf[1024];
E 6
I 6
D 11
	int ch, exitval, n, outc();
E 11
I 11
	int ch, exitval, n;
E 11
	char *cptr, *p, *term, buf[1024], tbuf[1024];
E 6
D 11
	char *getenv(), *tgetstr(), *realname();
E 11
E 5
E 4

D 4
	gtty(1, &tty);
	ospeed = tty.sg_ospeed;
	if (cp == (char *) 0)
		exit(1);
	if (tgetent(buf, cp) != 1)
		exit(1);
	pc = tgetstr("pc", &pcbp);
	if (pc)
		PC = *pc;
	clear = tgetstr("cl", &clbp);
	if (clear)
		tputs(clear, tgetnum("li"), putchar);
D 2
	exit (clear != (char *) 0);
E 2
I 2
	exit (clear == (char *) 0);
E 4
I 4
D 5
	if ((cp = getenv("TERM")) && tgetent(tbuf, cp) == 1) {
		clbp = clbuf;
		if (cp = tgetstr("cl", &clbp)) {
			tputs(cp, 1, putchar);
			exit(0);
E 5
I 5
	term = NULL;
	while ((ch = getopt(argc, argv, "T:")) != EOF)
		switch(ch) {
		case 'T':
			term = optarg;
			break;
		case '?':
		default:
			usage();
E 5
		}
I 5
	argc -= optind;
	argv += optind;

D 11
	if (!term && !(term = getenv("TERM"))) {
		(void)fprintf(stderr, "tput: no terminal type specified.\n");
D 6
		exit(3);
E 6
I 6
		exit(2);
E 6
E 5
	}
I 5
	if (tgetent(tbuf, term) != 1) {
		(void)fprintf(stderr, "tput: tgetent failure.\n");
D 6
		exit(3);
E 6
I 6
		exit(2);
E 6
	}
E 11
I 11
	if (!term && !(term = getenv("TERM")))
errx(2, "no terminal type specified and no TERM environmental variable.");
	if (tgetent(tbuf, term) != 1)
		err(2, "tgetent failure");
E 11
	setospeed();
D 6
	for (p = buf, exitval = 0; *argv; ++argv)
		if (ap = tgetstr(realname(*argv), &p))
			tputs(ap, 1, myputchar);
E 6
I 6
D 7
	for (cptr = buf; p = *argv; ++argv) {
		exitval = 0;
E 7
I 7
D 11
	for (cptr = buf, exitval = 0; p = *argv; ++argv) {
E 7
		switch(*p) {
E 11
I 11
	for (exitval = 0; (p = *argv) != NULL; ++argv) {
		switch (*p) {
E 11
		case 'c':
			if (!strcmp(p, "clear"))
				p = "cl";
			break;
		case 'i':
			if (!strcmp(p, "init"))
				p = "is";
			break;
		case 'l':
			if (!strcmp(p, "longname"))
				prlongname(tbuf);
			continue;
		case 'r':
			if (!strcmp(p, "reset"))
				p = "rs";
			break;
		}
I 11
		cptr = buf;
E 11
		if (tgetstr(p, &cptr))
D 11
			(void)tputs(buf, 1, outc);
E 11
I 11
			argv = process(p, buf, argv);
E 11
		else if ((n = tgetnum(p)) != -1)
			(void)printf("%d\n", n);
E 6
		else
D 6
			exitval = 2;
E 6
I 6
			exitval = !tgetflag(p);
	}
E 6
	exit(exitval);
}

I 11
static void
E 11
D 6
char *
realname(s)
	char *s;
E 6
I 6
prlongname(buf)
	char *buf;
E 6
{
D 6
	switch(*s) {
	case 'c':
		if (!strcmp(s, "clear"))
			return("cl");
		break;
	case 'i':
		if (!strcmp(s, "init"))
			return("is");
		break;
	case 'r':
		if (!strcmp(s, "reset"))
			return("rs");
		break;
	}
	return(s);
}
E 6
I 6
D 11
	register char *p;
E 11
	int savech;
D 11
	char *savep;
E 11
I 11
	char *p, *savep;
E 11
E 6

D 6
myputchar(c)
	int c;
{
	putchar(c);
E 6
I 6
	for (p = buf; *p && *p != ':'; ++p);
	savech = *(savep = p);
	for (*p = '\0'; p >= buf && *p != '|'; --p);
	(void)printf("%s\n", p + 1);
	*savep = savech;
E 6
}

I 11
static char **
process(cap, str, argv)
	char *cap, *str, **argv;
{
	static char errfew[] =
	    "not enough arguments (%d) for capability `%s'";
	static char errmany[] =
	    "too many arguments (%d) for capability `%s'";
	static char erresc[] =
	    "unknown %% escape `%c' for capability `%s'";
	char *cp;
	int arg_need, arg_rows, arg_cols;

	/* Count how many values we need for this capability. */
	for (cp = str, arg_need = 0; *cp != '\0'; cp++)
		if (*cp == '%')
			    switch (*++cp) {
			    case 'd':
			    case '2':
			    case '3':
			    case '.':
			    case '+':
				    arg_need++;
				    break;
			    case '%':
			    case '>':
			    case 'i':
			    case 'r':
			    case 'n':
			    case 'B':
			    case 'D':
				    break;
			    default:
				/*
				 * hpux has lot's of them, but we complain
				 */
				 errx(2, erresc, *cp, cap);
			    }

	/* And print them. */
	switch (arg_need) {
	case 0:
		(void)tputs(str, 1, outc);
		break;
	case 1:
		arg_cols = 0;

		if (*++argv == NULL || *argv[0] == '\0')
			errx(2, errfew, 1, cap);
		arg_rows = atoi(*argv);

		(void)tputs(tgoto(str, arg_cols, arg_rows), 1, outc);
		break;
	case 2:
		if (*++argv == NULL || *argv[0] == '\0')
			errx(2, errfew, 2, cap);
D 12
		arg_cols = atoi(*argv);
E 12
I 12
		arg_rows = atoi(*argv);
E 12

		if (*++argv == NULL || *argv[0] == '\0')
			errx(2, errfew, 2, cap);
D 12
		arg_rows = atoi(*argv);
E 12
I 12
		arg_cols = atoi(*argv);
E 12

		(void) tputs(tgoto(str, arg_cols, arg_rows), arg_rows, outc);
		break;

	default:
		errx(2, errmany, arg_need, cap);
	}
	return (argv);
}

static void
E 11
setospeed()
{
D 11
	extern int errno, ospeed;
E 11
I 11
#undef ospeed
	extern short ospeed;
E 11
	struct termios t;
D 11
	char *strerror();
E 11

D 8
	if (tcgetattr(STDOUT_FILENO, &t) == -1) {
		(void)fprintf(stderr, "tput: %s\n", strerror(errno));
		exit(1);
	}
	ospeed = cfgetospeed(&t);
E 8
I 8
	if (tcgetattr(STDOUT_FILENO, &t) != -1)
		ospeed = 0;
	else
		ospeed = cfgetospeed(&t);
E 8
I 6
}

I 11
static void
E 11
outc(c)
	int c;
{
D 11
	putchar(c);
E 11
I 11
	(void)putchar(c);
E 11
E 6
}

I 11
static void
E 11
usage()
{
	(void)fprintf(stderr, "usage: tput [-T term] attribute ...\n");
E 5
	exit(1);
E 4
E 2
}
E 1
