h64668
s 00005/00005/00308
d D 8.1 93/06/30 11:19:19 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00312
d D 5.8 93/06/30 11:18:32 mckusick 14 12
c no .TH for old man pages when doing -t
e
s 00005/00005/00308
d R 8.1 93/06/18 01:04:37 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00024/00001/00289
d D 5.7 93/06/18 01:03:54 mckusick 12 10
c work arounds for bogus man page formats
e
s 00005/00005/00285
d R 8.1 93/06/14 19:08:51 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00086/00019/00204
d D 5.6 93/06/14 18:58:08 mckusick 10 8
c update for new manual format
e
s 00005/00005/00218
d R 8.1 93/06/04 18:48:27 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00003/00205
d D 5.5 93/05/17 10:15:26 bostic 8 7
c ANSI prototypes
e
s 00042/00015/00166
d D 5.4 91/01/20 12:43:47 bostic 7 6
c written at Berkeley, use BSD copyright; lint, getopt(3)
e
s 00001/00001/00180
d D 5.3 90/05/15 19:47:07 bostic 6 5
c string.h is ANSI C include file
e
s 00001/00001/00180
d D 5.2 85/10/21 17:52:42 karels 5 4
c don't quit if one file isn't readable
e
s 00008/00002/00173
d D 5.1 85/04/30 12:56:09 dist 4 3
c Add copyright
e
s 00022/00001/00153
d D 4.3 83/07/10 20:08:28 sam 3 2
c need different style reference name for intro sections
e
s 00076/00021/00078
d D 4.2 83/07/10 20:00:38 sam 2 1
c add -i for building intro sections
e
s 00099/00000/00000
d D 4.1 80/10/01 17:26:57 bill 1 0
c date and time created 80/10/01 17:26:57 by bill
e
u
U
t
T
I 4
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 15
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
E 7
 */

E 4
I 2
#ifndef lint
I 7
D 15
char copyright[] =
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 15
#endif /* not lint */

#ifndef lint
E 7
E 2
I 1
D 4
static char *sccsid = "%W% (Berkeley) %G%";
I 2
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif not lint
E 7
I 7
#endif /* not lint */
E 7
E 4

/*
 * Get name sections from manual pages.
 *	-t	for building toc
 *	-i	for building intro entries
 *	other	apropos database
 */
D 6
#include <strings.h>
E 6
E 2
#include <stdio.h>
I 8
#include <stdlib.h>
E 8
I 6
#include <string.h>
E 6

int tocrc;
I 2
int intro;
I 10
int typeflag;
E 10
E 2

I 8
void doname __P((char *));
void dorefname __P((char *));
void getfrom __P((char *));
void split __P((char *, char *));
void trimln __P((char *));
void usage __P((void));

int
E 8
main(argc, argv)
	int argc;
D 7
	char *argv[];
E 7
I 7
D 8
	char **argv;
E 8
I 8
	char *argv[];
E 8
E 7
{
I 7
	extern int optind;
	int ch;
E 7

D 7
	argc--, argv++;
	if (!strcmp(argv[0], "-t"))
		argc--, argv++, tocrc++;
I 2
	if (!strcmp(argv[0], "-i"))
		argc--, argv++, intro++;
E 2
	while (argc > 0)
		getfrom(*argv++), argc--;
E 7
I 7
D 10
	while ((ch = getopt(argc, argv, "it")) != EOF)
E 10
I 10
	while ((ch = getopt(argc, argv, "itw")) != EOF)
E 10
		switch(ch) {
		case 'i':
			intro = 1;
			break;
		case 't':
			tocrc = 1;
			break;
I 10
		case 'w':
			typeflag = 1;
			break;
E 10
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!*argv)
		usage();

	for (; *argv; ++argv)
		getfrom(*argv);
E 7
	exit(0);
}

I 8
void
E 8
D 10
getfrom(name)
	char *name;
E 10
I 10
getfrom(pathname)
	char *pathname;
E 10
{
I 7
	int i = 0;
I 10
	char *name, *loc;
E 10
E 7
	char headbuf[BUFSIZ];
	char linbuf[BUFSIZ];
D 7
	register char *cp;
	int i = 0;
E 7

D 10
	if (freopen(name, "r", stdin) == 0) {
		perror(name);
E 10
I 10
	if (freopen(pathname, "r", stdin) == 0) {
		perror(pathname);
E 10
D 5
		exit(1);
E 5
I 5
		return;
E 5
	}
I 10
	if (name = strrchr(pathname, '/'))
		name++;
	else
		name = pathname;
E 10
	for (;;) {
D 10
		if (fgets(headbuf, sizeof headbuf, stdin) == NULL)
E 10
I 10
		if (fgets(headbuf, sizeof headbuf, stdin) == NULL) {
			if (typeflag)
				printf("%-60s	UNKNOWN\n", pathname);
E 10
			return;
I 10
		}
E 10
		if (headbuf[0] != '.')
			continue;
D 10
		if (headbuf[1] == 'T' && headbuf[2] == 'H')
E 10
I 10
		if ((headbuf[1] == 'T' && headbuf[2] == 'H') ||
		    (headbuf[1] == 't' && headbuf[2] == 'h'))
E 10
			break;
D 10
		if (headbuf[1] == 't' && headbuf[2] == 'h')
			break;
E 10
I 10
		if (headbuf[1] == 'D' && headbuf[2] == 't') {
			if (typeflag) {
				printf("%-60s	NEW\n", pathname);
				return;
			}
			goto newman;
		}
E 10
	}
I 10
	if (typeflag) {
		printf("%-60s	OLD\n", pathname);
		return;
	}
E 10
	for (;;) {
		if (fgets(linbuf, sizeof linbuf, stdin) == NULL)
			return;
		if (linbuf[0] != '.')
			continue;
		if (linbuf[1] == 'S' && linbuf[2] == 'H')
			break;
		if (linbuf[1] == 's' && linbuf[2] == 'h')
			break;
	}
	trimln(headbuf);
D 2
	if (tocrc) {
		register char *dp = name, *ep;

again:
		while (*dp && *dp != '.')
			putchar(*dp++);
		if (*dp)
			for (ep = dp+1; *ep; ep++)
				if (*ep == '.') {
					putchar(*dp++);
					goto again;
				}
		putchar('(');
		if (*dp)
			dp++;
		while (*dp)
			putchar (*dp++);
		putchar(')');
		putchar(' ');
	}
	printf("%s\t", headbuf);
E 2
I 2
	if (tocrc)
		doname(name);
D 14
	if (!intro)
E 14
I 14
	if (!tocrc && !intro)
E 14
		printf("%s\t", headbuf);
I 10
	linbuf[0] = '\0';
E 10
E 2
	for (;;) {
D 10
		if (fgets(linbuf, sizeof linbuf, stdin) == NULL)
E 10
I 10
		if (fgets(headbuf, sizeof headbuf, stdin) == NULL)
E 10
			break;
D 10
		if (linbuf[0] == '.') {
			if (linbuf[1] == 'S' && linbuf[2] == 'H')
E 10
I 10
		if (headbuf[0] == '.') {
			if (headbuf[1] == 'S' && headbuf[2] == 'H')
E 10
				break;
D 10
			if (linbuf[1] == 's' && linbuf[2] == 'h')
E 10
I 10
			if (headbuf[1] == 's' && headbuf[2] == 'h')
E 10
				break;
		}
D 10
		trimln(linbuf);
I 2
		if (intro) {
			split(linbuf, name);
E 10
I 10
		if (i != 0)
			strcat(linbuf, " ");
		i++;
		trimln(headbuf);
		strcat(linbuf, headbuf);
	}
	if (intro)
		split(linbuf, name);
	else
		printf("%s\n", linbuf);
	return;

newman:
	for (;;) {
		if (fgets(linbuf, sizeof linbuf, stdin) == NULL)
			return;
		if (linbuf[0] != '.')
E 10
			continue;
I 10
		if (linbuf[1] == 'S' && linbuf[2] == 'h')
			break;
	}
	trimln(headbuf);
	if (tocrc)
		doname(name);
	if (!tocrc && !intro)
		printf(".TH%s\t", &headbuf[3]);
	linbuf[0] = '\0';
	for (;;) {
		if (fgets(headbuf, sizeof headbuf, stdin) == NULL)
			break;
		if (headbuf[0] == '.') {
			if (headbuf[1] == 'S' && headbuf[2] == 'h')
				break;
E 10
		}
E 2
		if (i != 0)
D 10
			printf(" ");
E 10
I 10
			strcat(linbuf, " ");
E 10
		i++;
D 10
		printf("%s", linbuf);
E 10
I 10
		trimln(headbuf);
D 12
		for (loc = headbuf; loc; loc = strchr(loc, ' '))
E 12
I 12
		for (loc = strchr(headbuf, ' '); loc; loc = strchr(loc, ' '))
E 12
			if (loc[1] == ',')
				strcpy(loc, &loc[1]);
			else
				loc++;
		if (headbuf[0] != '.') {
			strcat(linbuf, headbuf);
		} else {
I 12
			/*
			 * Get rid of quotes in macros.
			 */
			for (loc = strchr(&headbuf[4], '"'); loc; ) {
				strcpy(loc, &loc[1]);
				loc = strchr(loc, '"');
			}
			/*
			 * Handle cross references
			 */
			if (headbuf[1] == 'X' && headbuf[2] == 'r') {
				for (loc = &headbuf[4]; *loc != ' '; loc++)
					continue;
				loc[0] = '(';
				loc[2] = ')';
				loc[3] = '\0';
			}
			/*
			 * Put dash between names and description.
			 */
E 12
			if (headbuf[1] == 'N' && headbuf[2] == 'd')
				strcat(linbuf, "\\- ");
I 12
			/*
			 * Skip over macro names.
			 */
E 12
			strcat(linbuf, &headbuf[4]);
		}
E 10
	}
D 10
	printf("\n");
E 10
I 10
	if (intro)
		split(linbuf, name);
	else
		printf("%s\n", linbuf);
E 10
}

I 8
void
E 8
trimln(cp)
	register char *cp;
{

	while (*cp)
		cp++;
	if (*--cp == '\n')
		*cp = 0;
I 2
}

I 8
void
E 8
doname(name)
	char *name;
{
	register char *dp = name, *ep;

again:
	while (*dp && *dp != '.')
		putchar(*dp++);
	if (*dp)
		for (ep = dp+1; *ep; ep++)
			if (*ep == '.') {
				putchar(*dp++);
				goto again;
			}
	putchar('(');
	if (*dp)
		dp++;
	while (*dp)
		putchar (*dp++);
	putchar(')');
	putchar(' ');
}

I 8
void
E 8
split(line, name)
	char *line, *name;
{
	register char *cp, *dp;
	char *sp, *sep;

D 8
	cp = index(line, '-');
E 8
I 8
	cp = strchr(line, '-');
E 8
	if (cp == 0)
		return;
	sp = cp + 1;
	for (--cp; *cp == ' ' || *cp == '\t' || *cp == '\\'; cp--)
		;
	*++cp = '\0';
	while (*sp && (*sp == ' ' || *sp == '\t'))
		sp++;
	for (sep = "", dp = line; dp && *dp; dp = cp, sep = "\n") {
D 8
		cp = index(dp, ',');
E 8
I 8
		cp = strchr(dp, ',');
E 8
		if (cp) {
			register char *tp;

			for (tp = cp - 1; *tp == ' ' || *tp == '\t'; tp--)
				;
			*++tp = '\0';
			for (++cp; *cp == ' ' || *cp == '\t'; cp++)
				;
		}
		printf("%s%s\t", sep, dp);
D 3
		doname(name);
E 3
I 3
		dorefname(name);
E 3
		printf("\t%s", sp);
	}
I 3
}

I 8
void
E 8
dorefname(name)
	char *name;
{
	register char *dp = name, *ep;

again:
	while (*dp && *dp != '.')
		putchar(*dp++);
	if (*dp)
		for (ep = dp+1; *ep; ep++)
			if (*ep == '.') {
				putchar(*dp++);
				goto again;
			}
	putchar('.');
	if (*dp)
		dp++;
	while (*dp)
		putchar (*dp++);
I 7
}

I 8
void
E 8
usage()
{
	(void)fprintf(stderr, "usage: getNAME [-it] file ...\n");
	exit(1);
E 7
E 3
E 2
}
E 1
