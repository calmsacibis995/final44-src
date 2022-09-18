h01293
s 00005/00005/00294
d D 8.1 93/06/06 22:28:21 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00023/00281
d D 5.12 92/07/20 14:37:47 bostic 12 11
c mostly fix exit status, plus vfork(2) doesn't currently share
c the address space.  Probably still not quite right
e
s 00004/00003/00300
d D 5.11 91/06/19 15:00:49 bostic 11 10
c off-by-one in the buffer
e
s 00006/00005/00297
d D 5.10 91/05/23 18:21:17 bostic 10 9
c change limit to ARG_MAX - 4K
e
s 00154/00086/00148
d D 5.9 91/04/27 13:11:56 bostic 9 8
c increase default -n to 5000; add SVID/POSIX -x flag; redo allocation
c and -s flag to be POSIX compliant; bug fix to make "noinvoke" volatile;
c add err() routine for error messages
e
s 00071/00066/00163
d D 5.8 91/04/27 10:00:10 bostic 8 7
c minor consistency changes for -f flag; use _POSIX2_LINE_MAX line length
c use the user's name for the utility as argv[0]; minor cleanup to process loop
c handle the exit status as described in POSIX.2
e
s 00012/00004/00217
d D 5.7 91/03/05 16:37:52 donn 7 6
c (1) Don't forget to terminate the argument list (2 out of 3 places!), 
c (2) Add -f flag to force xargs to ignore program status.  (3) Fix includes.
e
s 00002/00002/00219
d D 5.6 91/03/02 13:38:00 bostic 6 5
c ANSI
e
s 00001/00001/00220
d D 5.5 90/10/30 09:35:20 bostic 5 4
c BSD_LINE_MAX -> POSIX2_LINE_MAX
e
s 00001/00001/00220
d D 5.4 90/06/24 15:22:18 bostic 4 3
c LINE_MAX -> _BSD_LINE_MAX
e
s 00001/00001/00220
d D 5.3 90/05/15 19:55:59 bostic 3 2
c string.h is ANSI C include file
e
s 00005/00001/00216
d D 5.2 90/04/18 17:00:21 bostic 2 1
c was appending a null argument to the argv array
e
s 00217/00000/00000
d D 5.1 90/04/17 21:22:12 bostic 1 0
c date and time created 90/04/17 21:22:12 by bostic
e
u
U
t
T
I 1
/*-
D 13
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
 *
 * This code is derived from software contributed to Berkeley by
 * John B. Roll Jr.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 13
char copyright[] =
"%Z% Copyright (c) 1990 The Regents of the University of California.\n\
 All rights reserved.\n";
E 13
I 13
static char copyright[] =
"%Z% Copyright (c) 1990, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 13
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
I 7
#include <stdlib.h>
E 7
D 3
#include <strings.h>
E 3
I 3
#include <string.h>
I 7
#include <unistd.h>
E 7
E 3
#include <limits.h>
#include "pathnames.h"

D 8
#define	DEF_ARGC	255
E 8
I 8
D 12
int fflag, tflag;
E 12
I 12
int tflag, rval;

E 12
I 9
void err __P((const char *, ...));
D 12
void run(), usage();
E 12
I 12
void run __P((char **));
void usage __P((void));
E 12
E 9
E 8

D 8
int tflag;
I 7
int fflag;
E 7

E 8
main(argc, argv)
	int argc;
	char **argv;
{
D 8
	extern int errno, optind;
E 8
I 8
D 12
	extern int optind;
E 8
	extern char *optarg;
E 12
	register int ch;
D 9
	register char *p, *bp, *endbp, **bxp, **endxp, **xp;
	int cnt, indouble, insingle, nargs, nline;
D 7
	char *mark, *prog, **xargs, *malloc();
E 7
I 7
D 8
	char *mark, *prog, **xargs;
E 8
I 8
	char *start, **xargs;
E 9
I 9
	register char *p, *bbp, *ebp, **bxp, **exp, **xp;
	int cnt, indouble, insingle, nargs, nflag, nline, xflag;
	char **av, *argp;
E 9
E 8
E 7

D 8
	nargs = DEF_ARGC;
D 4
	nline = LINE_MAX;
E 4
I 4
D 5
	nline = _BSD_LINE_MAX;
E 5
I 5
	nline = _POSIX2_LINE_MAX;
E 8
I 8
D 9
	nargs = 1024;				/* random value */
	nline = ARG_MAX - 2048;			/* max POSIX.2 value */
E 8
E 5
E 4

D 7
	while ((ch = getopt(argc, argv, "n:s:t")) != EOF)
E 7
I 7
D 8
	while ((ch = getopt(argc, argv, "n:s:tf")) != EOF)
E 8
I 8
	while ((ch = getopt(argc, argv, "fn:s:t")) != EOF)
E 9
I 9
	/*
D 10
	 * POSIX.2 limits the exec line length to ARG_MAX - 2K.  Given that
	 * the smallest argument is 2 bytes in length, this means that the
	 * number of arguments is limited to:
E 10
I 10
	 * POSIX.2 limits the exec line length to ARG_MAX - 2K.  Running that
	 * caused some E2BIG errors, so it was changed to ARG_MAX - 4K.  Given
	 * that the smallest argument is 2 bytes in length, this means that
	 * the number of arguments is limited to:
E 10
	 *
D 10
	 *	 (ARG_MAX - 2K - LENGTH(utility + arguments)) / 2.
E 10
I 10
	 *	 (ARG_MAX - 4K - LENGTH(utility + arguments)) / 2.
E 10
	 *
	 * We arbitrarily limit the number of arguments to 5000.  This is
	 * allowed by POSIX.2 as long as the resulting minimum exec line is
	 * at least LINE_MAX.  Realloc'ing as necessary is possible, but
	 * probably not worthwhile.
	 */
	nargs = 5000;
D 10
	nline = ARG_MAX - 2048;
E 10
I 10
	nline = ARG_MAX - 4 * 1024;
E 10
	nflag = xflag = 0;
D 12
	while ((ch = getopt(argc, argv, "fn:s:tx")) != EOF)
E 12
I 12
	while ((ch = getopt(argc, argv, "n:s:tx")) != EOF)
E 12
E 9
E 8
E 7
		switch(ch) {
I 8
D 12
		case 'f':
			fflag = 1;
			break;
E 12
E 8
		case 'n':
D 9
			if ((nargs = atoi(optarg)) <= 0) {
				(void)fprintf(stderr,
D 8
				    "xargs: bad argument count.\n");
E 8
I 8
				    "xargs: illegal argument count.\n");
E 8
				exit(1);
			}
E 9
I 9
			nflag = 1;
			if ((nargs = atoi(optarg)) <= 0)
				err("illegal argument count");
E 9
			break;
		case 's':
D 9
			if ((nline = atoi(optarg)) <= 0) {
				(void)fprintf(stderr,
D 8
				    "xargs: bad command length.\n");
E 8
I 8
				    "xargs: illegal command length.\n");
E 8
				exit(1);
			}
E 9
I 9
			nline = atoi(optarg);
E 9
			break;
		case 't':
			tflag = 1;
			break;
I 9
		case 'x':
			xflag = 1;
			break;
E 9
I 7
D 8
		case 'f':
			fflag = 1;
			break;
E 8
E 7
		case '?':
		default:
			usage();
	}
	argc -= optind;
	argv += optind;

I 9
	if (xflag && !nflag)
		usage();

E 9
D 8
	/* room for the command, leftover arguments and trailing NULL */
	if (!(xargs =
	    (char **)malloc((u_int)(nargs + argc + 2) * sizeof(char **))))
		enomem();
E 8
I 8
	/*
D 9
	 * Allocate for the utility and arguments passed to xarg, the pointers
	 * to the arguments read from stdin and the trailing NULL.  Allocate
	 * for the arguments read from stdin.
E 9
I 9
	 * Allocate pointers for the utility name, the utility arguments,
	 * the maximum arguments to be read from stdin and the trailing
	 * NULL.
E 9
	 */
D 9
	if (!(xargs = malloc((u_int)(nargs + argc + 2) * sizeof(char **))) ||
	    !(bp = malloc((u_int)nline + 1))) {
		(void)fprintf(stderr, "xargs: %s.\n", strerror(errno));
		exit(1);
	}
E 9
I 9
	if (!(av = bxp =
	    malloc((u_int)(1 + argc + nargs + 1) * sizeof(char **))))
		err("%s", strerror(errno));
E 9
E 8

D 8
	if (!(bp = malloc((u_int)nline + 1)))
		enomem();

E 8
I 8
	/*
	 * Use the user's name for the utility as argv[0], just like the
	 * shell.  Echo is the default.  Set up pointers for the user's
	 * arguments.
	 */
E 8
D 9
	xp = xargs + 1;
E 9
	if (!*argv)
D 8
		prog = _PATH_ECHO;
E 8
I 8
D 9
		*xp++ = _PATH_ECHO;
E 9
I 9
		cnt = strlen(*bxp++ = _PATH_ECHO);
E 9
E 8
	else {
D 8
		prog = *argv;
E 8
I 8
D 9
		*xp++ = *argv;
E 8
		while (*++argv)
			*xp++ = *argv;
E 9
I 9
		cnt = 0;
		do {
			cnt += strlen(*bxp++ = *argv) + 1;
		} while (*++argv);
E 9
	}

D 8
	if (xargs[0] = rindex(prog, '/'))
		++xargs[0];
	else
		xargs[0] = prog;

	/* set up the pointers into the buffer and the arguments */
E 8
I 8
D 9
	/* Set up the pointers into the buffer and the arguments */
E 8
	*(endxp = (bxp = xp) + nargs) = NULL;
D 8
	endbp = (mark = p = bp) + nline;
E 8
I 8
	endbp = (start = p = bp) + nline;
E 9
I 9
	/*
	 * Set up begin/end/traversing pointers into the array.  The -n
	 * count doesn't include the trailing NULL pointer, so the malloc
	 * added in an extra slot.
	 */
	exp = (xp = bxp) + nargs;
E 9
E 8

D 9
	insingle = indouble = 0;
	for (;;)
E 9
I 9
	/*
	 * Allocate buffer space for the arguments read from stdin and the
	 * trailing NULL.  Buffer space is defined as the default or specified
	 * space, minus the length of the utility name and arguments.  Set up
	 * begin/end/traversing pointers into the array.  The -s count does
	 * include the trailing NULL, so the malloc didn't add in an extra
	 * slot.
	 */
	nline -= cnt;
	if (nline <= 0)
		err("insufficient space for command");

	if (!(bbp = malloc((u_int)nline + 1)))
		err("%s", strerror(errno));
	ebp = (argp = p = bbp) + nline - 1;

	for (insingle = indouble = 0;;)
E 9
		switch(ch = getchar()) {
		case EOF:
D 2
			if (p == bp)			/* empty line */
E 2
I 2
D 8
			if (p == bp)		/* nothing to display */
E 8
I 8
D 9
			/* Nothing to display. */
			if (p == bp)
E 9
I 9
			/* No arguments since last exec. */
			if (p == bbp)
E 9
E 8
E 2
D 12
				exit(0);
E 12
I 12
				exit(rval);
E 12
I 2
D 8
			if (mark == p) {	/* nothing since last arg end */
E 8
I 8

D 9
			/* Nothing since last arg end. */
			if (start == p) {
E 9
I 9
			/* Nothing since end of last argument. */
			if (argp == p) {
E 9
E 8
I 7
				*xp = NULL;
E 7
D 8
				run(prog, xargs);
E 8
I 8
D 9
				run(xargs[0], xargs);
E 9
I 9
				run(av);
E 9
E 8
D 12
				exit(0);
E 12
I 12
				exit(rval);
E 12
			}
E 2
D 9
			goto addarg;
E 9
I 9
			goto arg1;
E 9
		case ' ':
		case '\t':
I 9
			/* Quotes escape tabs and spaces. */
E 9
			if (insingle || indouble)
				goto addch;
D 9
			goto addarg;
E 9
I 9
			goto arg2;
E 9
		case '\n':
D 8
			if (mark == p)			/* empty line */
E 8
I 8
D 9
			if (start == p)			/* Empty line. */
E 9
I 9
			/* Empty lines are skipped. */
			if (argp == p)
E 9
E 8
				continue;
D 8
addarg:			*xp++ = mark;
E 8
I 8
D 9
addarg:			if (insingle || indouble) {
				(void)fprintf(stderr,
				   "xargs: unterminated quote\n");
				exit(1);
			}
			*xp++ = start;
E 8
			*p++ = '\0';
D 8
			if (xp == endxp || p >= endbp || ch == EOF) {
				if (insingle || indouble) {
					(void)fprintf(stderr,
					   "xargs: unterminated quote.\n");
					exit(1);
				}
E 8
I 8
			if (xp == endxp || p == endbp || ch == EOF) {
E 9
I 9

			/* Quotes do not escape newlines. */
arg1:			if (insingle || indouble)
				 err("unterminated quote");

D 11
arg2:			*p++ = '\0';
E 11
I 11
arg2:			*p = '\0';
E 11
			*xp++ = argp;

			/*
			 * If max'd out on args or buffer, or reached EOF,
			 * run the command.  If xflag and max'd out on buffer
			 * but not on args, object.
			 */
			if (xp == exp || p == ebp || ch == EOF) {
				if (xflag && xp != exp && p == ebp)
					err("insufficient space for arguments");
E 9
E 8
I 7
				*xp = NULL;
E 7
D 8
				run(prog, xargs);
E 8
I 8
D 9
				run(xargs[0], xargs);
E 9
I 9
				run(av);
E 9
E 8
				if (ch == EOF)
D 12
					exit(0);
E 12
I 12
					exit(rval);
E 12
D 9
				p = bp;
E 9
I 9
				p = bbp;
E 9
				xp = bxp;
D 11
			}
E 11
I 11
			} else
				++p;
E 11
D 8
			mark = p;
E 8
I 8
D 9
			start = p;
E 9
I 9
			argp = p;
E 9
E 8
			break;
		case '\'':
			if (indouble)
				goto addch;
			insingle = !insingle;
			break;
		case '"':
			if (insingle)
				goto addch;
			indouble = !indouble;
			break;
		case '\\':
D 8
			if ((ch = getchar()) == EOF)
				ch = '\\';
			if (ch == '\n') {
E 8
I 8
D 9
			if ((ch = getchar()) == EOF) {
E 8
				(void)fprintf(stderr,
D 8
				    "xargs: newline may not be escaped.\n");
E 8
I 8
				    "xargs: backslash at EOF\n");
E 8
				exit(1);
			}
E 9
I 9
			/* Backslash escapes anything, is escaped by quotes. */
			if (!insingle && !indouble && (ch = getchar()) == EOF)
				err("backslash at EOF");
E 9
			/* FALLTHROUGH */
		default:
D 9
addch:			if (p != endbp) {
E 9
I 9
D 11
addch:			if (p != ebp) {
E 11
I 11
addch:			if (p < ebp) {
E 11
E 9
				*p++ = ch;
D 9
				continue;
E 9
I 9
				break;
E 9
			}
D 8
			if (xp == bxp) {
E 8
I 8
D 9
			if (bxp == xp) {
E 8
				(void)fprintf(stderr,
				    "xargs: argument too large.\n");
				exit(1);
			}
E 9
I 9

			/* If only one argument, not enough buffer space. */
			if (bxp == xp)
				err("insufficient space for argument");
			/* Didn't hit argument limit, so if xflag object. */
			if (xflag)
				err("insufficient space for arguments");

E 9
			*xp = NULL;
D 8
			run(prog, xargs);
			cnt = endbp - mark;
			bcopy(mark, bp, cnt);
			p = (mark = bp) + cnt;
E 8
I 8
D 9
			run(xargs[0], xargs);
			cnt = endbp - start;
			bcopy(start, bp, cnt);
			p = (start = bp) + cnt;
E 8
			*p++ = ch;
E 9
I 9
			run(av);
E 9
			xp = bxp;
I 9
			cnt = ebp - argp;
			bcopy(argp, bbp, cnt);
			p = (argp = bbp) + cnt;
			*p++ = ch;
E 9
			break;
		}
	/* NOTREACHED */
}

D 9
run(prog, argv)
	char *prog, **argv;
E 9
I 9
void
run(argv)
	char **argv;
E 9
{
I 12
	volatile int noinvoke;
E 12
D 8
	union wait pstat;
E 8
I 8
D 9
	int noinvoke, status;
E 9
I 9
	register char **p;
E 9
E 8
D 6
	pid_t pid, waitpid();
E 6
I 6
	pid_t pid;
E 6
D 9
	char **p;
E 9
I 9
D 12
	volatile int noinvoke;
E 12
	int status;
E 9

	if (tflag) {
		(void)fprintf(stderr, "%s", *argv);
		for (p = argv + 1; *p; ++p)
			(void)fprintf(stderr, " %s", *p);
		(void)fprintf(stderr, "\n");
		(void)fflush(stderr);
	}
I 8
	noinvoke = 0;
E 8
	switch(pid = vfork()) {
	case -1:
D 9
		(void)fprintf(stderr,
D 8
		   "xargs: vfork: %s.\n", strerror(errno));
E 8
I 8
		    "xargs: vfork: %s.\n", strerror(errno));
E 8
		exit(1);
E 9
I 9
		err("vfork: %s", strerror(errno));
E 9
	case 0:
D 9
		execvp(prog, argv);
E 9
I 9
		execvp(argv[0], argv);
E 9
		(void)fprintf(stderr,
D 8
		   "xargs: %s: %s.\n", prog, strerror(errno));
E 8
I 8
D 9
		    "xargs: %s: %s.\n", prog, strerror(errno));
E 9
I 9
D 12
		    "xargs: %s: %s.\n", argv[0], strerror(errno));
E 12
I 12
		    "xargs: %s: %s\n", argv[0], strerror(errno));
E 12
E 9
		noinvoke = 1;
E 8
		_exit(1);
	}
D 6
	pid = waitpid(pid, &pstat, 0);
E 6
I 6
D 8
	pid = waitpid(pid, (int *)&pstat, 0);
E 8
I 8
	pid = waitpid(pid, &status, 0);
E 8
E 6
D 9
	if (pid == -1) {
		(void)fprintf(stderr,
D 8
		   "xargs: waitpid: %s.\n", strerror(errno));
E 8
I 8
		    "xargs: waitpid: %s.\n", strerror(errno));
E 8
		exit(1);
	}
E 9
I 9
	if (pid == -1)
		err("waitpid: %s", strerror(errno));
E 9
D 7
	if (pstat.w_status)
E 7
I 7
D 8
	if (!fflag && pstat.w_status)
E 7
		exit(1);
E 8
I 8
D 12
	/*
	 * If we couldn't invoke the utility or the utility didn't exit
	 * properly, quit with 127.
	 * Otherwise, if not specified otherwise, and the utility exits
	 * non-zero, exit with that value.
	 */
	if (noinvoke || !WIFEXITED(status) || WIFSIGNALED(status))
E 12
I 12
	/* If we couldn't invoke the utility, exit 127. */
	if (noinvoke)
E 12
		exit(127);
D 12
	if (!fflag && WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
E 12
I 12
	/* If utility signaled or exited with a value of 255, exit 1-125. */
	if (WIFSIGNALED(status) || WEXITSTATUS(status) == 255)
		exit(1);
	if (WEXITSTATUS(status))
		rval = 1;
E 12
E 8
}

I 9
void
E 9
D 8
enomem()
{
	(void)fprintf(stderr, "xargs: %s.\n", strerror(ENOMEM));
	exit(1);
}

E 8
usage()
{
	(void)fprintf(stderr,
D 7
	    "xargs: [-t] [-n number] [-s size] [utility [argument ...]]\n");
E 7
I 7
D 8
	    "xargs: [-t] [-f] [-n number] [-s size] [utility [argument ...]]\n");
E 8
I 8
D 9
	    "xargs: [-ft] [-n number] [-s size] [utility [argument ...]]\n");
E 9
I 9
D 12
"usage: xargs [-ft] [[-x] -n number] [-s size] [utility [argument ...]]\n");
E 12
I 12
"usage: xargs [-t] [-n number [-x]] [-s size] [utility [argument ...]]\n");
E 12
E 9
E 8
E 7
	exit(1);
I 9
}

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
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "xargs: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 9
}
E 1
