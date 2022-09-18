h27144
s 00001/00000/00197
d D 8.8 95/05/04 15:33:21 bostic 22 21
c optarg/optind moved to unistd.h
e
s 00002/00002/00195
d D 8.7 94/04/02 10:03:12 pendry 21 20
c add 1994 copyright
e
s 00028/00024/00169
d D 8.6 94/04/01 04:09:50 pendry 20 19
c prettyness police
e
s 00004/00004/00189
d D 8.5 94/01/02 10:17:15 bostic 19 18
c convert to new <sys/queue.h> structures
e
s 00007/00003/00186
d D 8.4 94/01/02 10:16:40 bostic 18 17
c Donn's patches for exit values and malloc sizes
e
s 00009/00008/00180
d D 8.3 94/01/02 10:15:53 bostic 17 16
c add a way to specify the config file (-C)
e
s 00024/00014/00164
d D 8.2 94/01/02 10:15:21 bostic 16 15
c rewrite man to make the configuration file more flexible
e
s 00005/00005/00173
d D 8.1 93/06/06 15:21:31 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00176
d D 5.13 91/09/26 15:11:07 bostic 14 13
c make the line longer, don't quit if the line's too long
e
s 00001/00011/00177
d D 5.12 90/06/01 16:59:04 bostic 13 12
c new copyright notice
e
s 00032/00025/00156
d D 5.11 90/05/27 15:25:39 bostic 12 11
c new apropos version, using new man.conf file
e
s 00001/00001/00180
d D 5.10 90/05/15 19:56:39 bostic 11 10
c string.h is ANSI C include file
e
s 00054/00028/00127
d D 5.9 90/03/11 15:08:37 bostic 10 9
c add -m flag, configurable search directories
e
s 00002/00002/00153
d D 5.8 89/05/11 10:00:41 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00041/00103/00114
d D 5.7 88/09/18 18:15:51 bostic 8 7
c use fgets, not gets so we don't overflow; split apropos and whatis
e
s 00010/00005/00207
d D 5.6 88/06/29 19:42:45 bostic 7 6
c install approved copyright notice
e
s 00092/00061/00120
d D 5.5 88/03/28 11:22:20 bostic 6 5
c kernel normal format; fix whatis to look for full word tokens;
c redo match routines for both apropos and whatis, other minor whacking
e
s 00010/00004/00171
d D 5.4 87/12/16 15:39:12 bostic 5 4
c add Berkeley headers
e
s 00001/00002/00174
d D 5.3 87/07/30 10:25:59 bostic 4 3
c change DEFPATH to include new and local
e
s 00003/00003/00173
d D 5.2 87/06/30 19:17:14 bostic 3 1
c MAXLINELEN of 500 too small, lint fixes
e
s 00005/00005/00171
d R 5.2 87/06/30 19:16:03 bostic 2 1
c MAXLINELEN of 500 too small; lint errors
e
s 00176/00000/00000
d D 5.1 87/06/29 20:53:49 bostic 1 0
c date and time created 87/06/29 20:53:49 by bostic
e
u
U
t
T
I 1
/*
D 15
 * Copyright (c) 1987 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 15
I 15
D 21
 * Copyright (c) 1987, 1993
E 21
I 21
 * Copyright (c) 1987, 1993, 1994
E 21
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
D 13
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 7
I 7
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
E 13
I 13
 * %sccs.include.redist.c%
E 13
E 7
E 5
 */

#ifndef lint
D 15
char copyright[] =
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
 All rights reserved.\n";
E 15
I 15
static char copyright[] =
D 21
"%Z% Copyright (c) 1987, 1993\n\
E 21
I 21
"%Z% Copyright (c) 1987, 1993, 1994\n\
E 21
	The Regents of the University of California.  All rights reserved.\n";
E 15
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
#endif /* not lint */
E 5

#include <sys/param.h>
D 16
#include <stdio.h>
E 16
I 16
#include <sys/queue.h>

E 16
#include <ctype.h>
I 6
D 11
#include <strings.h>
E 11
I 11
D 16
#include <string.h>
E 16
I 16
#include <err.h>
I 20
#include <limits.h>
E 20
#include <stdio.h>
E 16
I 12
#include <stdlib.h>
I 16
#include <string.h>
I 22
#include <unistd.h>
E 22

#include "../man/config.h"
E 16
E 12
E 11
I 9
D 10
#include "pathnames.h"
E 10
I 10
#include "../man/pathnames.h"
E 10
E 9
E 6

D 4
#define	DEF_PATH	"/usr/man"		/* default man path */
E 4
I 4
D 9
#define	DEF_PATH	"/usr/man:/usr/new/man:/usr/local/man"
E 9
E 4
D 3
#define	MAXLINELEN	500			/* max line handled */
E 3
I 3
D 10
#define	MAXLINELEN	1000			/* max line handled */
E 3
D 6
#define	NO		0			/* no/false */
E 6
#define	WHATIS		"whatis"		/* database name */
E 10
I 10
D 14
#define	MAXLINELEN	256			/* max line handled */
E 14
I 14
D 20
#define	MAXLINELEN	1024			/* max line handled */
E 14
E 10
D 6
#define	YES		1			/* yes/true */
E 6

E 20
I 10
D 12
int *found, foundman;
E 12
D 17
char *progname;

E 17
I 12
static int *found, foundman;

I 20
void apropos __P((char **, char *, int));
void lowstr __P((char *, char *));
int match __P((char *, char *));
void usage __P((void));

E 20
I 16
int
E 16
E 12
E 10
D 6
static char	*myname;
E 6
I 6
D 8
#define	NO	0				/* no/false */
#define	YES	1				/* yes/true */
E 6

I 6
static char *myname;

E 8
E 6
main(argc, argv)
D 6
	int	argc;
	char	**argv;
E 6
I 6
	int argc;
D 16
	char **argv;
E 16
I 16
	char *argv[];
E 16
E 6
{
D 6
	extern char	*optarg;
	extern int	optind;
	register char	*beg, *end, **C;
	int	ch, foundman = NO, *found, isapropos,
		a_match(), w_match(), (*match)();
	char	*manpath = NULL,
		buf[MAXLINELEN + 1], fname[MAXPATHLEN + 1],
		wbuf[MAXLINELEN + 1],
		*getenv(), *index(), *malloc(), *rindex();
E 6
I 6
D 20
	extern char *optarg;
	extern int optind;
E 20
D 8
	register char *beg, *end, **C;
	int ch, foundman = NO, *found, isapropos;
	int a_match(), w_match(), (*match)();
	char *manpath = NULL, buf[MAXLINELEN + 1], fname[MAXPATHLEN + 1];
E 8
I 8
D 10
	register char *beg, *end, **p;
	int ch, foundman = 0, *found;
	char *manpath, buf[MAXLINELEN + 1], fname[MAXPATHLEN + 1];
E 8
	char wbuf[MAXLINELEN + 1], *getenv(), *malloc();
E 10
I 10
D 16
	register char **p;
E 16
I 16
	ENTRY *ep;
I 19
	TAG *tp;
E 19
E 16
D 18
	int ch;
E 18
I 18
	int ch, rv;
E 18
D 12
	char *p_augment, *p_path, *config(), *getenv(), *malloc();
E 12
I 12
D 16
	char *p_augment, *p_path, **getdb();
E 16
I 16
D 17
	char **p, *p_augment, *p_path;
E 17
I 17
	char *conffile, **p, *p_augment, *p_path;
E 17
E 16
E 12
E 10
E 6

D 8
	myname = (beg = rindex(*argv, '/')) ? beg + 1 : *argv;
	if (!strcmp(myname, "apropos")) {
		isapropos = YES;
		match = a_match;
	}
	else {
		isapropos = NO;
		match = w_match;
	}
E 8
D 10
	while ((ch = getopt(argc, argv, "M:P:")) != EOF)
E 10
I 10
D 17
	progname = "apropos";
E 17
I 17
	conffile = NULL;
E 17
	p_augment = p_path = NULL;
D 17
	while ((ch = getopt(argc, argv, "M:m:P:")) != EOF)
E 17
I 17
	while ((ch = getopt(argc, argv, "C:M:m:P:")) != EOF)
E 17
E 10
D 16
		switch((char)ch) {
E 16
I 16
		switch (ch) {
I 17
		case 'C':
			conffile = optarg;
			break;
E 17
E 16
D 8
			case 'M':
			case 'P':		/* backward contemptible */
				manpath = optarg;
				break;
			case '?':
			default:
				usage();
E 8
I 8
		case 'M':
		case 'P':		/* backward compatible */
D 10
			manpath = optarg;
E 10
I 10
			p_path = optarg;
E 10
			break;
I 10
		case 'm':
			p_augment = optarg;
			break;
E 10
		case '?':
		default:
			usage();
E 8
		}
	argv += optind;
	argc -= optind;
I 10

E 10
	if (argc < 1)
		usage();

D 10
	if (!(manpath = getenv("MANPATH")))
D 9
		manpath = DEF_PATH;
E 9
I 9
		manpath = _PATH_DEFAULT;
E 10
I 10
D 12
	if (!p_path && !(p_path = getenv("MANPATH")))
		p_path = config();
E 10
E 9

E 12
D 16
	/*NOSTRICT*/
D 10
	if (!(found = (int *)malloc((u_int)argc))) {
D 8
		fprintf(stderr, "%s: out of space.\n", myname);
E 8
I 8
		fprintf(stderr, "apropos: out of space.\n");
E 8
		exit(1);
	}
E 10
I 10
	if (!(found = (int *)malloc((u_int)argc)))
		enomem();
E 10
D 3
	bzero(found, argc * sizeof(int));	/* calloc is silly */
E 3
I 3
D 6
	bzero((char *)found, argc * sizeof(int));	/* calloc is silly */
E 6
I 6
D 12
	bzero((char *)found, argc * sizeof(int));
E 12
I 12
	bzero((void *)found, argc * sizeof(int));
E 16
I 16
D 17
	if ((found = malloc((size_t)argc)) == NULL)
E 17
I 17
D 18
	if ((found = malloc((u_int)argc)) == NULL)
E 18
I 18
	if ((found = malloc((u_int)argc * sizeof(int))) == NULL)
E 18
E 17
		err(1, NULL);
	memset(found, 0, argc * sizeof(int));
E 16
E 12
E 6
E 3

D 6
	if (!isapropos)
D 3
		for (C = argv; *C; ++C) {	/* trim full paths */
E 3
I 3
		for (C = argv; *C; ++C) {		/* trim full paths */
E 3
			if (beg = rindex(*C, '/'))
				*C = beg + 1;
		}
	for (C = argv; *C; ++C)			/* convert to lower-case */
		lowstr(*C, *C);
E 6
I 6
D 8
	if (isapropos)
		for (C = argv; *C; ++C)		/* convert to lower-case */
			lowstr(*C, *C);
	else for (C = argv; *C; ++C)		/* trim full paths */
		if (beg = rindex(*C, '/'))
			*C = beg + 1;
E 6

E 8
I 8
	for (p = argv; *p; ++p)			/* convert to lower-case */
		lowstr(*p, *p);
E 8
D 10
	for (beg = manpath; beg; beg = end) {	/* through path list */
E 10
I 10

	if (p_augment)
D 12
		apropos(argv, p_augment);
	if (p_path)
		apropos(argv, p_path);
E 12
I 12
		apropos(argv, p_augment, 1);
	if (p_path || (p_path = getenv("MANPATH")))
		apropos(argv, p_path, 1);
D 16
	else
		for (p = getdb(); *p; ++p)
			apropos(argv, *p, 0);
E 16
I 16
	else {
D 17
		config();
E 17
I 17
		config(conffile);
E 17
D 19
		ep = getlist("_whatdb");
		if (ep != NULL)
			ep = ep->list.qe_next;
		for (; ep != NULL; ep = ep->list.qe_next)
E 19
I 19
		ep = (tp = getlist("_whatdb")) == NULL ?
		    NULL : tp->list.tqh_first;
		for (; ep != NULL; ep = ep->q.tqe_next)
E 19
			apropos(argv, ep->s, 0);
	}
E 16

E 12
D 20
	if (!foundman) {
D 12
		(void)fprintf(stderr, "apropos: no %s file found.\n",
		    _PATH_WHATIS);
E 12
I 12
		(void)fprintf(stderr,
D 16
		    "apropos: : no %s file found.\n", _PATH_WHATIS);
E 16
I 16
		    "apropos: no %s file found.\n", _PATH_WHATIS);
E 16
E 12
		exit(1);
	}
E 20
I 20
	if (!foundman)
		errx(1, "no %s file found", _PATH_WHATIS);

E 20
I 18
	rv = 1;
E 18
	for (p = argv; *p; ++p)
D 18
		if (!found[p - argv])
E 18
I 18
		if (found[p - argv])
			rv = 0;
		else
E 18
			(void)printf("%s: nothing appropriate\n", *p);
I 18
	exit(rv);
E 18
}

I 20
void
E 20
D 12
apropos(argv, path)
E 12
I 12
apropos(argv, path, buildpath)
E 12
	char **argv, *path;
I 12
	int buildpath;
E 12
{
D 12
	register char *beg, *end, **p;
	char fname[MAXPATHLEN + 1];
E 12
I 12
D 20
	register char *end, *name, **p;
E 12
	char buf[MAXLINELEN + 1], wbuf[MAXLINELEN + 1];
E 20
I 20
	char *end, *name, **p;
	char buf[LINE_MAX + 1], wbuf[LINE_MAX + 1];
E 20

D 12
	for (beg = path; beg; beg = end) {	/* through path list */
E 10
		end = index(beg, ':');
		if (!end)
D 10
			(void)sprintf(fname, "%s/%s", beg, WHATIS);
E 10
I 10
			(void)sprintf(fname, "%s/%s", beg, _PATH_WHATIS);
E 10
		else {
D 10
			(void)sprintf(fname, "%.*s/%s", end - beg, beg, WHATIS);
E 10
I 10
			(void)sprintf(fname, "%.*s/%s", end - beg, beg,
			    _PATH_WHATIS);
E 10
			++end;
E 12
I 12
	for (name = path; name; name = end) {	/* through name list */
D 20
		if (end = index(name, ':'))
E 20
I 20
		if (end = strchr(name, ':'))
E 20
			*end++ = '\0';

		if (buildpath) {
			char hold[MAXPATHLEN + 1];

			(void)sprintf(hold, "%s/%s", name, _PATH_WHATIS);
			name = hold;
E 12
		}
I 6
D 12
		if (!freopen(fname, "r", stdin))
E 12
I 12

		if (!freopen(name, "r", stdin))
E 12
			continue;

I 12
		foundman = 1;

E 12
E 6
D 8
						/* for each file found */
D 6
		if (freopen(fname, "r", stdin)) {
			foundman = YES;
			while (gets(buf)) {	/* read & convert to lcase */
E 6
I 6
		for (foundman = YES; gets(buf);) {
			if (isapropos)
E 6
				lowstr(buf, wbuf);
D 6
				for (C = argv; *C; ++C)
					if ((*match)(wbuf, *C)) {
						puts(buf);
						found[C - argv] = YES;
E 6
I 6
			else
				dashtrunc(buf, wbuf);
			for (C = argv; *C; ++C)
				if ((*match)(wbuf, *C)) {
					puts(buf);
					found[C - argv] = YES;
E 8
I 8
		/* for each file found */
D 12
		for (foundman = 1; fgets(buf, sizeof(buf), stdin);) {
E 12
I 12
		while (fgets(buf, sizeof(buf), stdin)) {
E 12
I 10
D 20
			if (!index(buf, '\n')) {
				(void)fprintf(stderr,
D 12
				    "apropos: %s line too long.\n", fname);
E 12
I 12
				    "apropos: %s line too long.\n", name);
E 20
I 20
			if (!strchr(buf, '\n')) {
				warnx("%s: line too long", name);
E 20
E 12
D 14
				exit(1);
E 14
I 14
				continue;
E 14
			}
E 10
			lowstr(buf, wbuf);
			for (p = argv; *p; ++p)
				if (match(wbuf, *p)) {
D 10
					printf("%s", buf);
E 10
I 10
					(void)printf("%s", buf);
E 10
					found[p - argv] = 1;
E 8
E 6

D 6
						/* only print line once */
						while (*++C)
							if ((*match)(wbuf, *C))
								found[C - argv] = YES;
						break;
					}
			}
E 6
I 6
					/* only print line once */
D 8
					while (*++C)
						if ((*match)(wbuf, *C))
							found[C - argv] = YES;
E 8
I 8
					while (*++p)
						if (match(wbuf, *p))
							found[p - argv] = 1;
E 8
					break;
				}
E 6
		}
	}
D 10
	if (!foundman) {
D 8
		fprintf(stderr, "%s: no %s file found in %s.\n", myname, WHATIS, manpath);
E 8
I 8
		fprintf(stderr, "apropos: no %s file found in %s.\n",
		    WHATIS, manpath);
E 8
		exit(1);
	}
D 6
	for (C = argv; *C; C++)
E 6
I 6
D 8
	for (C = argv; *C; ++C)
E 6
		if (!found[C - argv])
			printf("%s: %s\n", *C, isapropos ? "nothing appropriate" : "not found");
E 8
I 8
	for (p = argv; *p; ++p)
		if (!found[p - argv])
			printf("%s: nothing appropriate\n", *p);
E 10
E 8
}

I 6
/*
D 8
 * a_match --
 *	match for apropos; anywhere the string appears
E 8
I 8
 * match --
 *	match anywhere the string appears
E 8
 */
I 20
int
E 20
E 6
D 8
static
a_match(bp, str)
E 8
I 8
match(bp, str)
E 8
D 6
	register char	*bp, *str;
E 6
I 6
D 20
	register char *bp, *str;
E 20
I 20
	char *bp, *str;
E 20
E 6
{
D 6
	register char	test, *Cs, *Cb;
E 6
I 6
D 20
	register int len;
	register char test;
E 20
I 20
	int len;
	char test;
E 20
E 6

	if (!*bp)
D 8
		return(NO);
E 8
I 8
D 20
		return(0);
E 20
I 20
		return (0);
E 20
E 8
D 6
	/* backward contemptible: everything matches empty string */
E 6
I 6
	/* backward compatible: everything matches empty string */
E 6
	if (!*str)
D 8
		return(YES);
E 8
I 8
D 20
		return(1);
E 20
I 20
		return (1);
E 20
E 8
D 6
	for (test = *str++; *bp;)
		if (test == *bp++) {
			Cs = str;
			Cb = bp;
			do {
				if (!*Cs)
					return(YES);
			} while (*Cb++ == *Cs++);
		}
E 6
I 6
	for (test = *str++, len = strlen(str); *bp;)
		if (test == *bp++ && !strncmp(bp, str, len))
D 8
			return(YES);
E 6
	return(NO);
E 8
I 8
D 20
			return(1);
	return(0);
E 20
I 20
			return (1);
	return (0);
E 20
E 8
}

I 6
/*
D 8
 * w_match --
 *	match for whatis; looks for full word match
 */
E 6
static
w_match(bp, str)
D 6
	register char	*bp, *str;
E 6
I 6
	register char *bp, *str;
E 6
{
D 6
	register char	test, *Cs, *Cb;
E 6
I 6
	register int len;
	register char *start;
E 6

	if (!*str || !*bp)
		return(NO);
D 6
	for (test = *str++; *bp;)
		if (test == *bp++) {
			for (Cs = str, Cb = bp; *Cs == *Cb; ++Cs, ++Cb);
			if (!*Cs && (isspace(*Cb) || *Cb == '(' || *Cb == ','))
				return(YES);
		}
E 6
I 6
	for (len = strlen(str);;) {
		for (; *bp && !isdigit(*bp) && !isalpha(*bp); ++bp);
		if (!*bp)
			break;
		for (start = bp++; *bp && (isdigit(*bp) || isalpha(*bp)); ++bp);
		if (bp - start == len && !strncasecmp(start, str, len))
			return(YES);
	}
E 6
	return(NO);
}

I 6
/*
 * dashtrunc --
 *	truncate a string at " - "
 */
E 6
static
D 6
lowstr(from, to)
	register char	*from, *to;
E 6
I 6
dashtrunc(from, to)
	register char *from, *to;
E 6
{
D 6
	for (; *from; ++from, ++to)
		*to = isupper(*from) ? tolower(*from) : *from;
E 6
I 6
	do {
		if (from[0] == ' ' && from[1] == '-' && from[2] == ' ')
			break;
	} while (*to++ = *from++);
E 6
	*to = '\0';
}

I 6
/*
E 8
 * lowstr --
 *	convert a string to lower case
 */
I 20
void
E 20
D 8
static
E 8
lowstr(from, to)
D 20
	register char *from, *to;
E 20
I 20
	char *from, *to;
E 20
{
D 8
	do {
		*to++ = isupper(*from) ? tolower(*from) : *from;
	} while (*from++);
E 8
I 8
D 20
	register char ch;
E 20
I 20
	char ch;
E 20

	while ((ch = *from++) && ch != '\n')
		*to++ = isupper(ch) ? tolower(ch) : ch;
	*to = '\0';
E 8
}

/*
 * usage --
 *	print usage message and die
 */
I 20
void
E 20
E 6
D 8
static
E 8
usage()
{
I 20

E 20
D 8
	fprintf(stderr, "usage: %s [-M path] string ...\n", myname);
E 8
I 8
D 10
	fprintf(stderr, "usage: apropos [-M path] string ...\n");
E 10
I 10
	(void)fprintf(stderr,
D 17
	    "usage: apropos [-M path] [-m path] keyword ...\n");
E 17
I 17
	    "usage: apropos [-C file] [-M path] [-m path] keyword ...\n");
E 17
E 10
E 8
	exit(1);
}
D 4

E 4
E 1
