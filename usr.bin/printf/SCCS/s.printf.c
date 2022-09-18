h57550
s 00001/00001/00383
d D 8.2 95/03/22 12:02:36 christos 19 18
c added != '\0' to avoid gcc -Wall warning
e
s 00005/00005/00379
d D 8.1 93/07/20 07:03:18 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00381
d D 5.16 93/07/20 07:03:08 bostic 17 15
c lint: warnx("%s", ... -> warnx("%s: %s", ...
c From: Jan-Simon Pendry <pendry@vangogh.CS.Berkeley.EDU>
e
s 00005/00005/00379
d R 8.1 93/06/06 15:58:17 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00010/00374
d D 5.15 93/04/29 23:19:56 bostic 15 14
c make all calls to warnx, and get errno strings with strerror(3)
e
s 00001/00000/00383
d D 5.14 93/04/29 23:12:49 bostic 14 13
c declare optind
e
s 00110/00076/00273
d D 5.13 93/04/29 23:06:43 bostic 13 12
c use C library err/warn(3), do more error checking for over/underflow
c various minor cleanups
e
s 00005/00001/00344
d D 5.12 92/07/20 14:36:51 marc 12 11
c don't include from /usr/src/devel
e
s 00023/00013/00322
d D 5.11 92/05/14 18:38:06 marc 11 10
c modify for use within /bin/sh
e
s 00093/00039/00242
d D 5.10 91/07/22 17:36:06 bostic 10 9
c turn into a csh built-in; ANSI cleanups
e
s 00001/00011/00280
d D 5.9 90/06/01 17:30:07 bostic 9 8
c new copyright notice
e
s 00001/00001/00290
d D 5.8 90/04/18 09:53:17 bostic 8 7
c evaluate numerical arguments as C constants, i.e. 010 == 8, 0x10 == 16
e
s 00001/00001/00290
d D 5.7 89/07/20 17:59:19 bostic 7 6
c decimal point may start a number
e
s 00007/00002/00284
d D 5.6 89/07/20 17:34:38 bostic 6 5
c print single % sign for %% format
e
s 00005/00005/00281
d D 5.5 89/02/23 16:51:48 bostic 5 4
c reset fieldwidth/precision for each new format
e
s 00013/00013/00273
d D 5.4 89/02/16 16:50:57 bostic 4 3
c exit 0 on success, 1 on failure
e
s 00001/00001/00283
d D 5.3 89/02/12 20:03:14 bostic 3 2
c add %i
e
s 00002/00001/00282
d D 5.2 89/02/12 19:53:12 bostic 2 1
c add \'
e
s 00283/00000/00000
d D 5.1 89/02/12 19:35:15 bostic 1 0
c date and time created 89/02/12 19:35:15 by bostic
e
u
U
t
T
I 1
/*
D 18
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 9
I 9
 * %sccs.include.redist.c%
E 9
 */

I 10
D 11
#ifndef BUILTIN
E 11
I 11
D 13
#if ! defined(BUILTIN) && ! defined(SHELL)
E 13
I 13
#if !defined(BUILTIN) && !defined(SHELL)
E 13
E 11
E 10
#ifndef lint
D 18
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 18
I 18
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 18
#endif /* not lint */
I 10
#endif
E 10

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 11
D 13

E 13
E 11
#include <sys/types.h>
I 13

#include <err.h>
E 13
I 10
#include <errno.h>
I 11
D 13
#ifndef SHELL
E 13
I 13
#include <limits.h>
#ifdef SHELL
#define	EOF	-1
#else
E 13
E 11
E 10
#include <stdio.h>
I 11
#endif
E 11
I 10
#include <stdlib.h>
#include <string.h>
E 10

I 12
/*
 * XXX
 * This *has* to go away.  TK.
 */
E 12
I 11
#ifdef SHELL
#define main printfcmd
D 13
#define err error
E 13
I 13
D 15
#define warnx(a, b) {							\
E 15
I 15
#define warnx(a, b, c) {						\
E 15
	char buf[64];							\
D 15
	(void)sprintf(buf, sizeof(buf), a, b);				\
E 15
I 15
	(void)sprintf(buf, sizeof(buf), a, b, c);			\
E 15
	error(buf);							\
}
E 13
D 12
#include "/usr/src/devel/sh/bltin/bltin.h"
E 12
I 12
#include "../../bin/sh/bltin/bltin.h"
E 12
#endif

E 11
#define PF(f, func) { \
	if (fieldwidth) \
		if (precision) \
D 4
			cnt += printf(f, fieldwidth, precision, func); \
E 4
I 4
			(void)printf(f, fieldwidth, precision, func); \
E 4
		else \
D 4
			cnt += printf(f, fieldwidth, func); \
E 4
I 4
			(void)printf(f, fieldwidth, func); \
E 4
	else if (precision) \
D 4
		cnt += printf(f, precision, func); \
E 4
I 4
		(void)printf(f, precision, func); \
E 4
	else \
D 4
		cnt += printf(f, func); \
E 4
I 4
		(void)printf(f, func); \
E 4
}

D 10
char **gargv;
E 10
I 10
static int	 asciicode __P((void));
I 11
D 13
#ifndef SHELL
E 11
static void	 err __P((const char *fmt, ...));
I 11
#endif
E 13
E 11
static void	 escape __P((char *));
static int	 getchr __P((void));
static double	 getdouble __P((void));
D 13
static int	 getint __P((void));
static long	 getlong __P((void));
E 13
I 13
static int	 getint __P((int *));
static int	 getlong __P((long *));
E 13
static char	*getstr __P((void));
static char	*mklong __P((char *, int));
I 13
static void	 usage __P((void));
E 13
E 10

I 10
static char **gargv;

int
#ifdef BUILTIN
progprintf(argc, argv)
#else
E 10
main(argc, argv)
I 10
#endif
E 10
	int argc;
D 13
	char **argv;
E 13
I 13
	char *argv[];
E 13
{
I 14
	extern int optind;
E 14
	static char *skip1, *skip2;
D 13
	register char *format, *fmt, *start;
D 4
	register int end, cnt, fieldwidth, precision;
E 4
I 4
	register int end, fieldwidth, precision;
E 4
D 10
	char convch, nextch, *getstr(), *index(), *mklong();
	double getdouble();
	long getlong();
E 10
I 10
	char convch, nextch;
E 13
I 13
	int ch, end, fieldwidth, precision;
	char convch, nextch, *format, *fmt, *start;
E 13
E 10

D 13
	if (argc < 2) {
D 10
		fprintf(stderr, "usage: printf format [arg ...]\n");
D 4
		exit(0);
E 4
I 4
		exit(1);
E 10
I 10
		(void)fprintf(stderr, "usage: printf format [arg ...]\n");
E 13
I 13
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch (ch) {
		case '?':
		default:
			usage();
			return (1);
		}
	argc -= optind;
	argv += optind;

	if (argc < 1) {
		usage();
E 13
		return (1);
E 10
E 4
	}

	/*
	 * Basic algorithm is to scan the format string for conversion
	 * specifications -- once one is found, find out if the field
	 * width or precision is a '*'; if it is, gather up value.  Note,
	 * format strings are reused as necessary to use up the provided
	 * arguments, arguments of zero/null string are provided to use
	 * up the format string.
	 */
	skip1 = "#-+ 0";
	skip2 = "*0123456789";

D 13
	escape(fmt = format = *++argv);		/* backslash interpretation */
E 13
I 13
	escape(fmt = format = *argv);		/* backslash interpretation */
E 13
	gargv = ++argv;
D 4
	for (cnt = 0;;) {
E 4
I 4
	for (;;) {
E 4
		end = 0;
		/* find next format specification */
next:		for (start = fmt;; ++fmt) {
			if (!*fmt) {
				/* avoid infinite loop */
				if (end == 1) {
D 10
					fprintf(stderr,
					    "printf: missing format character.\n");
D 4
					exit(0);
E 4
I 4
					exit(1);
E 10
I 10
D 13
					err("missing format character");
E 13
I 13
D 15
					warnx("missing format character", NULL);
E 15
I 15
					warnx("missing format character",
					    NULL, NULL);
E 15
E 13
					return (1);
E 10
E 4
				}
				end = 1;
				if (fmt > start)
D 4
					cnt += printf("%s", start);
E 4
I 4
					(void)printf("%s", start);
E 4
				if (!*gargv)
D 4
					exit(cnt);
E 4
I 4
D 10
					exit(0);
E 10
I 10
					return (0);
E 10
E 4
				fmt = format;
				goto next;
			}
			/* %% prints a % */
D 6
			if (*fmt == '%' && *++fmt != '%')
				break;
E 6
I 6
			if (*fmt == '%') {
				if (*++fmt != '%')
					break;
				*fmt++ = '\0';
				(void)printf("%s", start);
				goto next;
			}
E 6
		}

		/* skip to field width */
D 13
		for (; index(skip1, *fmt); ++fmt);
D 5
		if (*fmt == '*')
			fieldwidth = getint();
		/* skip to possible '.' */
E 5
I 5
		fieldwidth = *fmt == '*' ? getint() : 0;

E 13
I 13
		for (; strchr(skip1, *fmt); ++fmt);
		if (*fmt == '*') {
			if (getint(&fieldwidth))
				return (1);
		} else
			fieldwidth = 0;

E 13
		/* skip to possible '.', get following precision */
E 5
D 13
		for (; index(skip2, *fmt); ++fmt);
E 13
I 13
		for (; strchr(skip2, *fmt); ++fmt);
E 13
		if (*fmt == '.')
			++fmt;
D 5
		if (*fmt == '*')
			precision = getint();
E 5
I 5
D 13
		precision = *fmt == '*' ? getint() : 0;

E 13
I 13
		if (*fmt == '*') {
			if (getint(&precision))
				return (1);
		} else
			precision = 0;

E 13
E 5
		/* skip to conversion char */
D 13
		for (; index(skip2, *fmt); ++fmt);
E 13
I 13
		for (; strchr(skip2, *fmt); ++fmt);
E 13
		if (!*fmt) {
D 10
			fprintf(stderr, "printf: missing format character.\n");
D 4
			exit(-1);
E 4
I 4
			exit(1);
E 10
I 10
D 13
			err("missing format character");
E 13
I 13
D 15
			warnx("missing format character", NULL);
E 15
I 15
			warnx("missing format character", NULL, NULL);
E 15
E 13
			return (1);
E 10
E 4
		}

		convch = *fmt;
		nextch = *++fmt;
		*fmt = '\0';
		switch(convch) {
		case 'c': {
D 10
			char p = getchr();
E 10
I 10
			char p;

			p = getchr();
E 10
			PF(start, p);
			break;
		}
		case 's': {
D 10
			char *p = getstr();
E 10
I 10
			char *p;

			p = getstr();
E 10
			PF(start, p);
			break;
		}
D 3
		case 'd': case 'o': case 'u': case 'x': case 'X': {
E 3
I 3
		case 'd': case 'i': case 'o': case 'u': case 'x': case 'X': {
E 3
D 10
			char *f = mklong(start, convch);
			long p = getlong();
E 10
I 10
			long p;
			char *f;
			
			if ((f = mklong(start, convch)) == NULL)
				return (1);
D 13
			p = getlong();
E 13
I 13
			if (getlong(&p))
				return (1);
E 13
E 10
			PF(f, p);
			break;
		}
		case 'e': case 'E': case 'f': case 'g': case 'G': {
D 10
			double p = getdouble();
E 10
I 10
			double p;

			p = getdouble();
E 10
			PF(start, p);
			break;
		}
		default:
D 10
			fprintf(stderr, "printf: illegal format character.\n");
D 4
			exit(-1);
E 4
I 4
			exit(1);
E 10
I 10
D 13
			err("illegal format character.\n");
E 13
I 13
D 15
			warnx("illegal format character", NULL);
E 15
I 15
			warnx("illegal format character", NULL, NULL);
E 15
E 13
			return (1);
E 10
E 4
		}
		*fmt = nextch;
	}
	/* NOTREACHED */
}

D 10
char *
E 10
I 10
static char *
E 10
mklong(str, ch)
D 10
	char *str, ch;
E 10
I 10
	char *str;
	int ch;
E 10
{
I 10
D 11
	register char *copy;
E 11
I 11
	static char copy[64];
E 11
E 10
	int len;
D 10
	char *copy, *malloc();
E 10

	len = strlen(str) + 2;
D 10
	if (!(copy = malloc((u_int)len))) {	/* never freed; XXX */
		fprintf(stderr, "printf: out of memory.\n");
D 4
		exit(-1);
E 4
I 4
		exit(1);
E 4
	}
	bcopy(str, copy, len - 3);
	copy[len - 3] = 'l';
	copy[len - 2] = ch;
	copy[len - 1] = '\0';
E 10
I 10
D 11
	if (copy = malloc((u_int)len)) {	/* never freed; XXX */
		bcopy(str, copy, len - 3);
		copy[len - 3] = 'l';
		copy[len - 2] = ch;
		copy[len - 1] = '\0';
	} else
		err("%s", strerror(errno));
E 11
I 11
D 13
	bcopy(str, copy, len - 3);
E 13
I 13
	memmove(copy, str, len - 3);
E 13
	copy[len - 3] = 'l';
	copy[len - 2] = ch;
	copy[len - 1] = '\0';
E 11
E 10
D 13
	return(copy);
E 13
I 13
	return (copy);
E 13
}

I 10
static void
E 10
escape(fmt)
	register char *fmt;
{
	register char *store;
	register int value, c;

D 19
	for (store = fmt; c = *fmt; ++fmt, ++store) {
E 19
I 19
	for (store = fmt; (c = *fmt) != '\0'; ++fmt, ++store) {
E 19
		if (c != '\\') {
			*store = c;
			continue;
		}
		switch (*++fmt) {
		case '\0':		/* EOS, user error */
			*store = '\\';
			*++store = '\0';
			return;
		case '\\':		/* backslash */
D 2
			*store = '\\';
E 2
I 2
		case '\'':		/* single quote */
			*store = *fmt;
E 2
			break;
		case 'a':		/* bell/alert */
			*store = '\7';
			break;
		case 'b':		/* backspace */
			*store = '\b';
			break;
		case 'f':		/* form-feed */
			*store = '\f';
			break;
		case 'n':		/* newline */
			*store = '\n';
			break;
		case 'r':		/* carriage-return */
			*store = '\r';
			break;
		case 't':		/* horizontal tab */
			*store = '\t';
			break;
		case 'v':		/* vertical tab */
			*store = '\13';
			break;
					/* octal constant */
		case '0': case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			for (c = 3, value = 0;
			    c-- && *fmt >= '0' && *fmt <= '7'; ++fmt) {
				value <<= 3;
				value += *fmt - '0';
			}
			--fmt;
			*store = value;
			break;
		default:
			*store = *fmt;
			break;
		}
	}
	*store = '\0';
}

I 10
static int
E 10
getchr()
{
	if (!*gargv)
D 10
		return((int)'\0');
E 10
I 10
D 13
		return('\0');
E 10
	return((int)**gargv++);
E 13
I 13
		return ('\0');
	return ((int)**gargv++);
E 13
}

D 10
char *
E 10
I 10
static char *
E 10
getstr()
{
	if (!*gargv)
D 13
		return("");
	return(*gargv++);
E 13
I 13
		return ("");
	return (*gargv++);
E 13
}

D 7
static char *number = "+-0123456789";
E 7
I 7
D 11
static char *number = "+-.0123456789";
E 11
I 11
static char *Number = "+-.0123456789";
E 11
I 10
static int
E 10
E 7
D 13
getint()
E 13
I 13
getint(ip)
	int *ip;
E 13
{
D 13
	if (!*gargv)
		return(0);
D 11
	if (index(number, **gargv))
E 11
I 11
	if (index(Number, **gargv))
E 11
		return(atoi(*gargv++));
	return(asciicode());
E 13
I 13
	long val;

	if (getlong(&val))
		return (1);
	if (val > INT_MAX) {
D 15
		errno = ERANGE;
		warn("%s", *gargv);
E 15
I 15
D 17
		warnx("%s", *gargv, strerror(ERANGE));
E 17
I 17
		warnx("%s: %s", *gargv, strerror(ERANGE));
E 17
E 15
		return (1);
	}
	*ip = val;
	return (0);
E 13
}

D 10
long
E 10
I 10
D 13
static long
E 10
getlong()
E 13
I 13
static int
getlong(lp)
	long *lp;
E 13
{
D 10
	long atol();

E 10
D 13
	if (!*gargv)
		return((long)0);
D 11
	if (index(number, **gargv))
E 11
I 11
	if (index(Number, **gargv))
E 11
D 8
		return(atol(*gargv++));
E 8
I 8
		return(strtol(*gargv++, (char **)NULL, 0));
E 8
	return((long)asciicode());
E 13
I 13
	long val;
	char *ep;

	if (!*gargv) {
		*lp = 0;
		return (0);
	}
	if (strchr(Number, **gargv)) {
		errno = 0;
		val = strtol(*gargv, &ep, 0);
		if (*ep != '\0') {
D 15
			warnx("%s: illegal number", *gargv);
E 15
I 15
			warnx("%s: illegal number", *gargv, NULL);
E 15
			return (1);
		}
		if (errno == ERANGE)
			if (val == LONG_MAX) {
D 15
				warn("%s", *gargv);
E 15
I 15
D 17
				warnx("%s", *gargv, strerror(ERANGE));
E 17
I 17
				warnx("%s: %s", *gargv, strerror(ERANGE));
E 17
E 15
				return (1);
			}
			if (val == LONG_MIN) {
D 15
				warn("%s", *gargv);
E 15
I 15
D 17
				warnx("%s", *gargv, strerror(ERANGE));
E 17
I 17
				warnx("%s: %s", *gargv, strerror(ERANGE));
E 17
E 15
				return (1);
			}
			
		*lp = val;
		++gargv;
		return (0);
	}
	*lp =  (long)asciicode();
	return (0);
E 13
}

D 10
double
E 10
I 10
static double
E 10
getdouble()
{
D 10
	double atof();

E 10
	if (!*gargv)
D 13
		return((double)0);
D 11
	if (index(number, **gargv))
E 11
I 11
	if (index(Number, **gargv))
E 11
		return(atof(*gargv++));
	return((double)asciicode());
E 13
I 13
		return ((double)0);
	if (strchr(Number, **gargv))
		return (atof(*gargv++));
	return ((double)asciicode());
E 13
}

I 10
static int
E 10
asciicode()
{
D 10
	register char ch;
E 10
I 10
	register int ch;
E 10

	ch = **gargv;
	if (ch == '\'' || ch == '"')
		ch = (*gargv)[1];
	++gargv;
D 13
	return(ch);
E 13
I 13
	return (ch);
E 13
I 10
}

I 11
D 13
#ifndef SHELL
E 11
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 13
static void
D 13
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
	va_dcl
#endif
E 13
I 13
usage()
E 13
{
D 13
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "printf: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 13
I 13
	(void)fprintf(stderr, "usage: printf format [arg ...]\n");
E 13
E 10
}
I 11
D 13
#endif /* !SHELL */
E 13
E 11
E 1
