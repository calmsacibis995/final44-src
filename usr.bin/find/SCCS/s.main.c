h07238
s 00001/00000/00127
d D 8.4 95/05/04 15:37:03 bostic 17 16
c optarg/optind moved to unistd.h
e
s 00011/00003/00116
d D 8.3 94/04/16 13:51:29 bostic 16 15
c The find command used the results of option() to delimit the file list
c from its expression.  But misspellings of the expression can cause
c disasterous results, and POSIX.2 requires more stringent criteria.
c For example: find . -naame '*.o' | xargs rm
c will remove every file in the current directory heirarchy.
c From: conklin@ngai.kaleida.com (J.T. Conklin)
e
s 00039/00029/00080
d D 8.2 94/04/01 07:33:20 bostic 15 14
c POSIX 1003.2B/D9 symbolic links
e
s 00002/00002/00107
d D 8.1 93/06/06 14:39:13 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00003/00103
d D 5.13 93/05/01 11:51:39 bostic 13 12
c use library err/warn(3) functions; lint, prettiness police
e
s 00003/00004/00103
d D 5.12 93/04/26 22:41:55 bostic 12 11
c don't turn off FTS_NOSTAT for -x ... at least I can't think of
c why you should...
e
s 00015/00003/00092
d D 5.11 92/06/01 12:21:22 elan 11 10
c Added -Hh options.
e
s 00001/00000/00094
d D 5.10 91/12/05 08:39:34 bostic 10 9
c main didn't exit
e
s 00008/00006/00086
d D 5.9 91/05/24 15:36:43 bostic 9 8
c change find to do an fchdir on exec/ok; this means that the -r
c option can go away and everybody gets the speedup
e
s 00043/00016/00049
d D 5.8 91/05/24 15:17:12 bostic 8 7
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00004/00001/00061
d D 5.7 91/04/27 13:37:41 bostic 7 6
c add -X flag to make the world safe for xargs
e
s 00002/00001/00060
d D 5.6 91/03/09 18:44:30 bostic 6 5
c ANSI
e
s 00003/00005/00058
d D 5.5 90/11/15 12:22:07 bostic 5 4
c make status variables consistent
e
s 00001/00000/00062
d D 5.4 90/11/15 10:47:20 bostic 4 3
c lint
e
s 00006/00001/00056
d D 5.3 90/10/22 09:52:29 bostic 3 2
c add -r option, allowing -exec/-ok to do relative traversal
e
s 00002/00002/00055
d D 5.2 90/05/22 15:00:52 bostic 2 1
c fts now has flag to keep from crossing mount points
e
s 00057/00000/00000
d D 5.1 90/05/12 15:30:02 bostic 1 0
c date and time created 90/05/12 15:30:02 by bostic
e
u
U
t
T
I 1
/*-
D 14
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 14
I 14
D 15
 * Copyright (c) 1990, 1993
E 15
I 15
 * Copyright (c) 1990, 1993, 1994
E 15
 *	The Regents of the University of California.  All rights reserved.
E 14
 *
I 15
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
E 15
 * %sccs.include.redist.c%
 */

#ifndef lint
I 15
char copyright[] =
"%Z% Copyright (c) 1990, 1993, 1994\n\
	The Regents of the University of California.  All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 15
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/stat.h>
I 13

#include <err.h>
#include <errno.h>
E 13
I 9
#include <fcntl.h>
E 9
I 8
D 13
#include <time.h>
E 13
E 8
D 6
#include <stdio.h>
E 6
#include <fts.h>
I 9
D 13
#include <errno.h>
E 13
E 9
I 6
#include <stdio.h>
#include <stdlib.h>
I 13
#include <time.h>
I 17
#include <unistd.h>
E 17

E 13
E 6
#include "find.h"

I 3
D 5
int relative;

E 5
I 4
D 8
void
E 4
E 3
newsyntax(argc, argvp)
E 8
I 8
time_t now;			/* time find was run */
I 9
int dotfd;			/* starting directory */
E 9
int ftsoptions;			/* options for the ftsopen(3) call */
int isdeprecated;		/* using deprecated syntax */
int isdepth;			/* do directories on post-order visit */
int isoutput;			/* user specified output operator */
D 9
int isrelative;			/* can do -exec/ok on relative path */
E 9
int isxargs;			/* don't permit xargs delimiting chars */

D 12
static void usage();
E 12
I 12
static void usage __P((void));
E 12

I 12
int
E 12
main(argc, argv)
E 8
	int argc;
D 8
	char ***argvp;
E 8
I 8
D 12
	char **argv;
E 12
I 12
	char *argv[];
E 12
E 8
{
I 5
D 8
	extern int optind;
E 5
	extern char *optarg;
E 8
I 8
	register char **p, **start;
D 12
	PLAN *find_formplan();
E 12
E 8
D 2
	extern int depth, optind, xdev;
E 2
I 2
D 5
	extern int depth, optind;
E 5
E 2
D 15
	int ch;
E 15
I 15
	int Hflag, Lflag, Pflag, ch;
E 15
D 8
	char **argv, **cur;
E 8

D 8
	cur = argv = *argvp;
E 8
I 8
	(void)time(&now);	/* initialize the time-of-day */

	p = start = argv;
D 15
	ftsoptions = FTS_NOSTAT|FTS_PHYSICAL;
E 8
D 3
	while ((ch = getopt(argc, argv, "df:sx")) != EOF)
E 3
I 3
D 7
	while ((ch = getopt(argc, argv, "df:rsx")) != EOF)
E 7
I 7
D 9
	while ((ch = getopt(argc, argv, "df:rsXx")) != EOF)
E 9
I 9
D 11
	while ((ch = getopt(argc, argv, "df:sXx")) != EOF)
E 11
I 11
	while ((ch = getopt(argc, argv, "Hdf:hXx")) != EOF)
E 11
E 9
E 7
E 3
		switch(ch) {
E 15
I 15
	Hflag = Lflag = Pflag = 0;
	ftsoptions = FTS_NOSTAT | FTS_PHYSICAL;
	while ((ch = getopt(argc, argv, "HLPXdf:x")) != EOF)
		switch (ch) {
E 15
I 11
		case 'H':
D 15
			ftsoptions |= FTS_COMFOLLOW;
E 15
I 15
			Hflag = 1;
			Lflag = Pflag = 0;
E 15
			break;
I 15
		case 'L':
			Lflag = 1;
			Hflag = Pflag = 0;
			break;
		case 'P':
			Pflag = 1;
			Hflag = Lflag = 0;
			break;
		case 'X':
			isxargs = 1;
			break;
E 15
E 11
		case 'd':
D 5
			depth = 1;
E 5
I 5
			isdepth = 1;
E 5
			break;
		case 'f':
D 8
			*cur++ = optarg;
E 8
I 8
			*p++ = optarg;
E 8
I 3
			break;
D 9
		case 'r':
D 5
			relative = 1;
E 5
I 5
			isrelative = 1;
E 5
E 3
			break;
E 9
D 11
		case 's':
E 11
I 11
D 15
		case 'h':
E 11
			ftsoptions &= ~FTS_PHYSICAL;
			ftsoptions |= FTS_LOGICAL;
I 7
			break;
		case 'X':
			isxargs = 1;
E 7
			break;
E 15
		case 'x':
D 2
			xdev = 1;
E 2
D 12
			ftsoptions &= ~FTS_NOSTAT;
E 12
I 2
			ftsoptions |= FTS_XDEV;
E 2
			break;
		case '?':
		default:
D 8
			usage();
E 8
I 8
			break;
E 8
		}

D 8
	*argvp += optind;
	if (cur == argv) {
		if (!**argvp)
			usage();
		*cur++ = **argvp;
		++*argvp;
E 8
I 8
	argc -= optind;	
	argv += optind;

I 15
	if (Hflag)
		ftsoptions |= FTS_COMFOLLOW;
	if (Lflag) {
		ftsoptions &= ~FTS_PHYSICAL;
		ftsoptions |= FTS_LOGICAL;
	}

E 15
D 16
	/* Find first option to delimit the file list. */
D 15
	while (*argv) {
E 15
I 15
	for (; *argv != NULL; *p++ = *argv++)
E 15
		if (option(*argv))
E 16
I 16
	/*
	 * Find first option to delimit the file list.  The first argument
	 * that starts with a -, or is a ! or a ( must be interpreted as a
	 * part of the find expression, according to POSIX .2.
	 */
	for (; *argv != NULL; *p++ = *argv++) {
		if (argv[0][0] == '-')
E 16
			break;
I 16
		if ((argv[0][0] == '!' || argv[0][0] == '(') &&
		    argv[0][1] == '\0')
			break;
	}
E 16
D 15
		*p++ = *argv++;
E 8
	}
E 15
D 8
	*cur = NULL;
E 8
I 8

	if (p == start)
		usage();
	*p = NULL;

I 9
	if ((dotfd = open(".", O_RDONLY, 0)) < 0)
D 13
		err(".: %s", strerror(errno));
E 13
I 13
D 15
		err(1, ".:");
E 15
I 15
		err(1, ".");
E 15
E 13

E 9
D 15
	find_execute(find_formplan(argv), start);
I 10
	exit(0);
E 15
I 15
	exit(find_execute(find_formplan(argv), start));
E 15
E 10
}

static void
usage()
{
	(void)fprintf(stderr,
D 9
	    "usage: find [-drsXx] [-f file] [file ...] expression\n");
E 9
I 9
D 11
	    "usage: find [-dsXx] [-f file] [file ...] expression\n");
E 11
I 11
D 15
	    "usage: find [-HdhXx] [-f file] [file ...] expression\n");
E 15
I 15
"usage: find [-H | -L | -P] [-Xdx] [-f file] [file ...] [expression]\n");
E 15
E 11
E 9
	exit(1);
E 8
}
I 11
D 15









E 15
E 11
E 1
