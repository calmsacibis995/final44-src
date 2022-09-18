h54117
s 00001/00000/00271
d D 8.3 95/05/04 15:35:29 bostic 8 7
c optarg/optind moved to unistd.h
e
s 00002/00001/00269
d D 8.2 95/04/28 12:41:26 bostic 7 6
c fixed bug with -d leaving seperators; From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00265
d D 8.1 93/06/06 14:30:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00065/00039/00205
d D 5.5 92/08/20 10:48:23 bostic 5 4
c close file descriptors; ANSI C while I'm here
e
s 00004/00004/00240
d D 5.4 90/10/30 09:29:52 bostic 4 3
c BSD_LINE_MAX -> POSIX2_LINE_MAX
c 
e
s 00004/00004/00240
d D 5.3 90/06/24 15:20:54 bostic 3 2
c LINE_MAX -> _BSD_LINE_MAX
e
s 00001/00011/00243
d D 5.2 90/06/01 16:47:19 bostic 2 1
c new copyright notice
e
s 00256/00000/00000
d D 5.1 89/12/25 12:01:19 bostic 1 0
c date and time created 89/12/25 12:01:19 by bostic
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Adam S. Moskowitz of Menlo Consulting and Marciano Pitargue.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
D 6
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 5
#include <ctype.h>
#include <errno.h>
E 5
#include <limits.h>
#include <stdio.h>
D 5
#include <ctype.h>
E 5
I 5
#include <stdlib.h>
#include <string.h>
I 8
#include <unistd.h>
E 8
E 5

int	cflag;
char	dchar;
int	dflag;
int	fflag;
int	sflag;

I 5
void	c_cut __P((FILE *, char *));
void	err __P((const char *, ...));
void	f_cut __P((FILE *, char *));
void	get_list __P((char *));
void	usage __P((void));

int
E 5
main(argc, argv)
	int argc;
D 5
	char **argv;
E 5
I 5
	char *argv[];
E 5
{
D 5
	extern char *optarg;
	extern int errno, optind;
E 5
	FILE *fp;
D 5
	int ch, (*fcn)(), c_cut(), f_cut();
	char *strerror();
E 5
I 5
	void (*fcn) __P((FILE *, char *));
	int ch;
E 5

	dchar = '\t';			/* default delimiter is \t */

	while ((ch = getopt(argc, argv, "c:d:f:s")) != EOF)
		switch(ch) {
		case 'c':
			fcn = c_cut;
			get_list(optarg);
			cflag = 1;
			break;
		case 'd':
			dchar = *optarg;
			dflag = 1;
			break;
		case 'f':
			get_list(optarg);
			fcn = f_cut;
			fflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (fflag) {
		if (cflag)
			usage();
	} else if (!cflag || dflag || sflag)
		usage();

	if (*argv)
		for (; *argv; ++argv) {
D 5
			if (!(fp = fopen(*argv, "r"))) {
				(void)fprintf(stderr,
				    "cut: %s: %s\n", *argv, strerror(errno));
				exit(1);
			}
E 5
I 5
			if (!(fp = fopen(*argv, "r")))
				err("%s: %s\n", *argv, strerror(errno));
E 5
			fcn(fp, *argv);
I 5
			(void)fclose(fp);
E 5
		}
	else
		fcn(stdin, "stdin");
	exit(0);
}

int autostart, autostop, maxval;

D 3
char positions[LINE_MAX + 1];
E 3
I 3
D 4
char positions[_BSD_LINE_MAX + 1];
E 4
I 4
char positions[_POSIX2_LINE_MAX + 1];
E 4
E 3

I 5
void
E 5
get_list(list)
	char *list;
{
D 5
	register char *pos;
E 5
	register int setautostart, start, stop;
D 5
	char *p, *strtok();
E 5
I 5
	register char *pos;
	char *p;
E 5

	/*
	 * set a byte in the positions array to indicate if a field or
	 * column is to be selected; use +1, it's 1-based, not 0-based.
	 * This parser is less restrictive than the Draft 9 POSIX spec.
	 * POSIX doesn't allow lists that aren't in increasing order or
	 * overlapping lists.  We also handle "-3-5" although there's no
	 * real reason too.
	 */
	for (; p = strtok(list, ", \t"); list = NULL) {
		setautostart = start = stop = 0;
		if (*p == '-') {
			++p;
			setautostart = 1;
		}
		if (isdigit(*p)) {
			start = stop = strtol(p, &p, 10);
			if (setautostart && start > autostart)
				autostart = start;
		}
		if (*p == '-') {
			if (isdigit(p[1]))
				stop = strtol(p + 1, &p, 10);
			if (*p == '-') {
				++p;
				if (!autostop || autostop > stop)
					autostop = stop;
			}
		}
		if (*p)
D 5
			badlist("illegal list value");
E 5
I 5
			err("[-cf] list: illegal list value\n");
E 5
		if (!stop || !start)
D 5
			badlist("values may not include zero");
D 3
		if (stop > LINE_MAX) {
E 3
I 3
D 4
		if (stop > _BSD_LINE_MAX) {
E 4
I 4
		if (stop > _POSIX2_LINE_MAX) {
E 4
E 3
			/* positions used rather than allocate a new buffer */
			(void)sprintf(positions, "%d too large (max %d)",
E 5
I 5
			err("[-cf] list: values may not include zero\n");
		if (stop > _POSIX2_LINE_MAX)
			err("[-cf] list: %d too large (max %d)\n",
E 5
D 3
			    stop, LINE_MAX);
E 3
I 3
D 4
			    stop, _BSD_LINE_MAX);
E 4
I 4
			    stop, _POSIX2_LINE_MAX);
E 4
E 3
D 5
			badlist(positions);
		}
E 5
		if (maxval < stop)
			maxval = stop;
		for (pos = positions + start; start++ <= stop; *pos++ = 1);
	}

	/* overlapping ranges */
	if (autostop && maxval > autostop)
		maxval = autostop;

	/* set autostart */
	if (autostart)
		memset(positions + 1, '1', autostart);
}

/* ARGSUSED */
I 5
void
E 5
c_cut(fp, fname)
	FILE *fp;
	char *fname;
{
	register int ch, col;
	register char *pos;

	for (;;) {
		pos = positions + 1;
		for (col = maxval; col; --col) {
			if ((ch = getc(fp)) == EOF)
				return;
			if (ch == '\n')
				break;
			if (*pos++)
D 5
				putchar(ch);
E 5
I 5
				(void)putchar(ch);
E 5
		}
		if (ch != '\n')
			if (autostop)
				while ((ch = getc(fp)) != EOF && ch != '\n')
D 5
					putchar(ch);
E 5
I 5
					(void)putchar(ch);
E 5
			else
				while ((ch = getc(fp)) != EOF && ch != '\n');
D 5
		putchar('\n');
E 5
I 5
		(void)putchar('\n');
E 5
	}
}

I 5
void
E 5
f_cut(fp, fname)
	FILE *fp;
	char *fname;
{
	register int ch, field, isdelim;
	register char *pos, *p, sep;
	int output;
D 3
	char lbuf[LINE_MAX + 1];
E 3
I 3
D 4
	char lbuf[_BSD_LINE_MAX + 1];
E 4
I 4
	char lbuf[_POSIX2_LINE_MAX + 1];
E 4
E 3

D 7
	for (sep = dchar, output = 0; fgets(lbuf, sizeof(lbuf), fp);) {
E 7
I 7
	for (sep = dchar; fgets(lbuf, sizeof(lbuf), fp);) {
		output = 0;
E 7
		for (isdelim = 0, p = lbuf;; ++p) {
D 5
			if (!(ch = *p)) {
				(void)fprintf(stderr,
				    "cut: %s: line too long.\n", fname);
				exit(1);
			}
E 5
I 5
			if (!(ch = *p))
				err("%s: line too long.\n", fname);
E 5
			/* this should work if newline is delimiter */
			if (ch == sep)
				isdelim = 1;
			if (ch == '\n') {
				if (!isdelim && !sflag)
					(void)printf("%s", lbuf);
				break;
			}
		}
		if (!isdelim)
			continue;

		pos = positions + 1;
		for (field = maxval, p = lbuf; field; --field, ++pos) {
			if (*pos) {
				if (output++)
D 5
					putchar(sep);
E 5
I 5
					(void)putchar(sep);
E 5
				while ((ch = *p++) != '\n' && ch != sep)
D 5
					putchar(ch);
E 5
I 5
					(void)putchar(ch);
E 5
			} else
				while ((ch = *p++) != '\n' && ch != sep);
			if (ch == '\n')
				break;
		}
		if (ch != '\n')
			if (autostop) {
				if (output)
D 5
					putchar(sep);
E 5
I 5
					(void)putchar(sep);
E 5
				for (; (ch = *p) != '\n'; ++p)
D 5
					putchar(ch);
E 5
I 5
					(void)putchar(ch);
E 5
			} else
				for (; (ch = *p) != '\n'; ++p);
D 5
		putchar('\n');
E 5
I 5
		(void)putchar('\n');
E 5
	}
}

D 5
badlist(msg)
	char *msg;
E 5
I 5
void
usage()
E 5
{
D 5
	(void)fprintf(stderr, "cut: [-cf] list: %s.\n", msg);
E 5
I 5
	(void)fprintf(stderr,
"usage:\tcut -c list [file1 ...]\n\tcut -f list [-s] [-d delim] [file ...]\n");
E 5
	exit(1);
}

D 5
usage()
E 5
I 5
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
E 5
{
D 5
	(void)fprintf(stderr,
"usage:\tcut -c list [file1 ...]\n\tcut -f list [-s] [-d delim] [file ...]\n");
E 5
I 5
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "cut: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 5
	exit(1);
I 5
	/* NOTREACHED */
E 5
}
E 1
