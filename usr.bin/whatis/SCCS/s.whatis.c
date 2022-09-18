h05832
s 00004/00004/00188
d D 8.5 94/01/02 10:21:06 bostic 13 11
c convert to new <sys/queue.h> structures
e
s 00000/00000/00192
d R 8.5 94/01/02 10:20:13 bostic 12 11
c convert to new <sys/queue.h> structures
e
s 00007/00003/00185
d D 8.4 94/01/02 10:19:52 bostic 11 10
c Donn's patches for exit values and malloc sizes
e
s 00011/00009/00177
d D 8.3 94/01/02 10:19:32 bostic 10 9
c add a way to specify the config file (-C)
e
s 00020/00011/00166
d D 8.2 94/01/02 10:19:08 bostic 9 8
c rewrite man to make the configuration file more flexible
e
s 00005/00005/00172
d D 8.1 93/06/06 22:24:29 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00176
d D 5.7 92/01/08 14:33:02 bostic 7 6
c initialize p_augment, p_path
e
s 00001/00011/00175
d D 5.6 90/06/01 16:59:22 bostic 6 5
c new copyright notice
e
s 00027/00021/00159
d D 5.5 90/05/27 15:29:31 bostic 5 4
c new whatis version, using new man.conf file
e
s 00047/00028/00133
d D 5.4 90/03/11 15:06:10 bostic 4 3
c add -m option, configurable search directories
e
s 00002/00002/00159
d D 5.3 89/05/11 10:00:45 bostic 3 2
c file reorg, pathnames.h, paths.h
e
s 00002/00001/00159
d D 5.2 88/09/19 10:43:34 bostic 2 1
c find names with underscores, i.e. "sys_siglist"; bug report 4.3BSD/ucb/243
e
s 00160/00000/00000
d D 5.1 88/09/18 18:16:18 bostic 1 0
c use fgets, not gets so we don't overflow; split apropos and whatis
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1987, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
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
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1987, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
D 9
#include <stdio.h>
E 9
I 9
#include <sys/queue.h>

E 9
#include <ctype.h>
D 4
#include <strings.h>
I 3
#include "pathnames.h"
E 4
I 4
D 9
#include <string.h>
E 9
I 9
#include <err.h>
#include <stdio.h>
E 9
I 5
#include <stdlib.h>
I 9
#include <string.h>

#include "../man/config.h"
E 9
E 5
#include "../man/pathnames.h"
E 4
E 3

D 3
#define	DEF_PATH	"/usr/man:/usr/new/man:/usr/local/man"
E 3
D 4
#define	MAXLINELEN	1000			/* max line handled */
#define	WHATIS		"whatis"		/* database name */
E 4
I 4
#define	MAXLINELEN	256			/* max line handled */
E 4

I 4
D 5
int *found, foundman;
E 5
D 10
char *progname;

E 10
I 5
static int *found, foundman;

I 10
int
E 10
E 5
E 4
main(argc, argv)
	int argc;
D 10
	char **argv;
E 10
I 10
	char *argv[];
E 10
{
	extern char *optarg;
	extern int optind;
D 4
	register char *beg, *end, **p;
	int ch, foundman = 0, *found;
	char *manpath, buf[MAXLINELEN + 1], fname[MAXPATHLEN + 1];
	char wbuf[MAXLINELEN + 1], *getenv(), *malloc();
E 4
I 4
D 9
	register char *beg, **p;
E 9
I 9
	ENTRY *ep;
I 13
	TAG *tp;
E 13
E 9
D 11
	int ch;
E 11
I 11
	int ch, rv;
E 11
D 5
	char *p_augment, *p_path, *config(), *getenv(), *malloc();
E 5
I 5
D 9
	char *p_augment, *p_path, **getdb();
E 9
I 9
D 10
	char *beg, **p, *p_augment, *p_path, **getdb();
E 10
I 10
	char *beg, *conffile, **p, *p_augment, *p_path;
E 10
E 9
E 5
E 4

D 4
	while ((ch = getopt(argc, argv, "M:P:")) != EOF)
E 4
I 4
D 10
	progname = "whatis";
E 10
I 10
	conffile = NULL;
E 10
I 7
	p_augment = p_path = NULL;
E 7
D 10
	while ((ch = getopt(argc, argv, "M:m:P:")) != EOF)
E 4
		switch((char)ch) {
E 10
I 10
	while ((ch = getopt(argc, argv, "C:M:m:P:")) != EOF)
		switch (ch) {
		case 'C':
			conffile = optarg;
			break;
E 10
		case 'M':
		case 'P':		/* backward compatible */
D 4
			manpath = optarg;
E 4
I 4
			p_path = optarg;
E 4
			break;
I 4
		case 'm':
			p_augment = optarg;
			break;
E 4
		case '?':
		default:
			usage();
		}
	argv += optind;
	argc -= optind;
I 4

E 4
	if (argc < 1)
		usage();

D 4
	if (!(manpath = getenv("MANPATH")))
D 3
		manpath = DEF_PATH;
E 3
I 3
		manpath = _PATH_DEFAULT;
E 4
I 4
D 5
	if (!p_path && !(p_path = getenv("MANPATH")))
		p_path = config();
E 4
E 3

E 5
D 9
	/*NOSTRICT*/
D 4
	if (!(found = (int *)malloc((u_int)argc))) {
		fprintf(stderr, "whatis: out of space.\n");
		exit(1);
	}
E 4
I 4
	if (!(found = (int *)malloc((u_int)argc)))
		enomem();
E 4
	bzero((char *)found, argc * sizeof(int));
E 9
I 9
D 11
	if ((found = malloc((u_int)argc)) == NULL)
E 11
I 11
	if ((found = malloc((u_int)argc * sizeof(int))) == NULL)
E 11
		err(1, NULL);
	memset(found, 0, argc * sizeof(int));
E 9

	for (p = argv; *p; ++p)			/* trim full paths */
		if (beg = rindex(*p, '/'))
			*p = beg + 1;

D 4
	for (beg = manpath; beg; beg = end) {	/* through path list */
E 4
I 4
	if (p_augment)
D 5
		whatis(argv, p_augment);
	if (p_path)
		whatis(argv, p_path);
E 5
I 5
		whatis(argv, p_augment, 1);
	if (p_path || (p_path = getenv("MANPATH")))
		whatis(argv, p_path, 1);
D 9
	else
		for (p = getdb(); *p; ++p)
			whatis(argv, *p, 0);
E 9
I 9
	else {
D 10
		config();
E 10
I 10
		config(conffile);
E 10
D 13
		ep = getlist("_whatdb");
		if (ep != NULL)
			ep = ep->list.qe_next;
		for (; ep != NULL; ep = ep->list.qe_next)
E 13
I 13
		ep = (tp = getlist("_whatdb")) == NULL ?
		   NULL : tp->list.tqh_first;
		for (; ep != NULL; ep = ep->q.tqe_next)
E 13
			whatis(argv, ep->s, 0);
	}
E 9
E 5

	if (!foundman) {
		fprintf(stderr, "whatis: no %s file found.\n", _PATH_WHATIS);
		exit(1);
	}
I 11
	rv = 1;
E 11
	for (p = argv; *p; ++p)
D 11
		if (!found[p - argv])
E 11
I 11
		if (found[p - argv])
			rv = 0;
		else
E 11
			printf("%s: not found\n", *p);
I 11
	exit(rv);
E 11
}

D 5
whatis(argv, path)
E 5
I 5
whatis(argv, path, buildpath)
E 5
	char **argv, *path;
I 5
	int buildpath;
E 5
{
D 5
	register char *beg, *end, **p;
	char fname[MAXPATHLEN + 1];
E 5
I 5
	register char *end, *name, **p;
E 5
	char buf[MAXLINELEN + 1], wbuf[MAXLINELEN + 1];

D 5
	for (beg = path; beg; beg = end) {	/* through path list */
E 4
		end = index(beg, ':');
		if (!end)
D 4
			(void)sprintf(fname, "%s/%s", beg, WHATIS);
E 4
I 4
			(void)sprintf(fname, "%s/%s", beg, _PATH_WHATIS);
E 4
		else {
D 4
			(void)sprintf(fname, "%.*s/%s", end - beg, beg, WHATIS);
E 4
I 4
			(void)sprintf(fname, "%.*s/%s", end - beg, beg,
			    _PATH_WHATIS);
E 4
			++end;
E 5
I 5
	for (name = path; name; name = end) {	/* through name list */
		if (end = index(name, ':'))
			*end++ = '\0';

		if (buildpath) {
			char hold[MAXPATHLEN + 1];

			(void)sprintf(hold, "%s/%s", name, _PATH_WHATIS);
			name = hold;
E 5
		}
D 5
		if (!freopen(fname, "r", stdin))
E 5
I 5

		if (!freopen(name, "r", stdin))
E 5
			continue;

I 5
		foundman = 1;

E 5
		/* for each file found */
D 5
		for (foundman = 1; fgets(buf, sizeof(buf), stdin);) {
E 5
I 5
		while (fgets(buf, sizeof(buf), stdin)) {
E 5
			dashtrunc(buf, wbuf);
			for (p = argv; *p; ++p)
				if (match(wbuf, *p)) {
					printf("%s", buf);
					found[p - argv] = 1;

					/* only print line once */
					while (*++p)
						if (match(wbuf, *p))
							found[p - argv] = 1;
					break;
				}
		}
	}
D 4
	if (!foundman) {
		fprintf(stderr, "whatis: no %s file found in %s.\n",
		    WHATIS, manpath);
		exit(1);
	}
	for (p = argv; *p; ++p)
		if (!found[p - argv])
			printf("%s: not found\n", *p);
E 4
}

/*
 * match --
 *	match a full word
 */
match(bp, str)
	register char *bp, *str;
{
	register int len;
	register char *start;

	if (!*str || !*bp)
		return(0);
	for (len = strlen(str);;) {
		for (; *bp && !isdigit(*bp) && !isalpha(*bp); ++bp);
		if (!*bp)
			break;
D 2
		for (start = bp++; *bp && (isdigit(*bp) || isalpha(*bp)); ++bp);
E 2
I 2
		for (start = bp++;
		    *bp && (*bp == '_' || isdigit(*bp) || isalpha(*bp)); ++bp);
E 2
		if (bp - start == len && !strncasecmp(start, str, len))
			return(1);
	}
	return(0);
}

/*
 * dashtrunc --
 *	truncate a string at " - "
 */
dashtrunc(from, to)
	register char *from, *to;
{
	register int ch;

	for (; (ch = *from) && ch != '\n' &&
	    (ch != ' ' || from[1] != '-' || from[2] != ' '); ++from)
		*to++ = ch;
	*to = '\0';
}

/*
 * usage --
 *	print usage message and die
 */
usage()
{
D 4
	fprintf(stderr, "usage: whatis [-M path] string ...\n");
E 4
I 4
	(void)fprintf(stderr,
D 10
	    "usage: whatis [-M path] [-m path] command ...\n");
E 10
I 10
	    "usage: whatis [-C file] [-M path] [-m path] command ...\n");
E 10
E 4
	exit(1);
}
E 1
