h37420
s 00001/00000/00278
d D 8.4 95/05/04 15:34:56 bostic 12 11
c optarg/optind moved to unistd.h
e
s 00002/00002/00276
d D 8.3 94/04/02 10:07:33 pendry 11 10
c add 1994 copyright
e
s 00026/00035/00252
d D 8.2 94/04/01 08:23:17 pendry 10 9
c prettyness police
e
s 00005/00005/00282
d D 8.1 93/06/06 14:28:43 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00021/00251
d D 5.8 91/08/26 14:16:49 bostic 8 7
c flag variable wasn't getting initialized; ANSI whacks while I'm here
e
s 00006/00008/00266
d D 5.7 91/02/24 16:39:55 bostic 7 6
c if entry length is bigger than the terminal, print only
e
s 00001/00011/00273
d D 5.6 90/06/01 16:46:32 bostic 6 5
c new copyright notice
e
s 00001/00001/00283
d D 5.5 90/05/15 20:00:48 bostic 5 4
c string.h is ANSI C include file
e
s 00007/00003/00277
d D 5.4 89/11/01 19:55:03 bostic 4 3
c add -s option
e
s 00097/00026/00183
d D 5.3 89/09/13 14:00:08 bostic 3 2
c add table formatting code
e
s 00014/00015/00195
d D 5.2 89/06/28 17:02:01 bostic 2 1
c infinite loop on bad file name
e
s 00210/00000/00000
d D 5.1 89/06/25 13:27:28 bostic 1 0
c date and time created 89/06/25 13:27:28 by bostic
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
D 11
 * Copyright (c) 1989, 1993
E 11
I 11
 * Copyright (c) 1989, 1993, 1994
E 11
 *	The Regents of the University of California.  All rights reserved.
E 9
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
D 9
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
D 11
"%Z% Copyright (c) 1989, 1993\n\
E 11
I 11
"%Z% Copyright (c) 1989, 1993, 1994\n\
E 11
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/ioctl.h>
I 8
D 10
#include <errno.h>
E 10
I 10

#include <ctype.h>
#include <err.h>
#include <limits.h>
E 10
E 8
#include <stdio.h>
I 8
#include <stdlib.h>
E 8
D 5
#include <strings.h>
E 5
I 5
#include <string.h>
I 12
#include <unistd.h>
E 12
E 5
I 3
D 10
#include <ctype.h>
E 10
E 3

I 8
void  c_columnate __P((void));
void *emalloc __P((int));
void  input __P((FILE *));
void  maketbl __P((void));
D 10
void  nomem __P((void));
E 10
void  print __P((void));
void  r_columnate __P((void));
void  usage __P((void));

E 8
int termwidth = 80;		/* default terminal width */

D 4
char **list;			/* array of pointers to records */
E 4
int entries;			/* number of records */
I 3
int eval;			/* exit value */
E 3
int maxlength;			/* longest record */
I 4
char **list;			/* array of pointers to records */
char *separator = "\t ";	/* field separator for table option */
E 4

I 8
int
E 8
main(argc, argv)
	int argc;
	char **argv;
{
D 8
	extern char *optarg;
	extern int errno, optind;
E 8
	struct winsize win;
	FILE *fp;
D 2
	int ch, xflag;
E 2
I 2
D 3
	int ch, eval, xflag;
E 3
I 3
	int ch, tflag, xflag;
E 3
E 2
D 8
	char *p, *getenv();
E 8
I 8
	char *p;
E 8

	if (ioctl(1, TIOCGWINSZ, &win) == -1 || !win.ws_col) {
		if (p = getenv("COLUMNS"))
			termwidth = atoi(p);
	} else
		termwidth = win.ws_col;

D 8
	xflag = 0;
E 8
I 8
	tflag = xflag = 0;
E 8
D 3
	while ((ch = getopt(argc, argv, "c:x")) != EOF)
E 3
I 3
D 4
	while ((ch = getopt(argc, argv, "c:tx")) != EOF)
E 4
I 4
	while ((ch = getopt(argc, argv, "c:s:tx")) != EOF)
E 4
E 3
		switch(ch) {
		case 'c':
			termwidth = atoi(optarg);
			break;
I 4
		case 's':
			separator = optarg;
			break;
E 4
I 3
		case 't':
			tflag = 1;
			break;
E 3
		case 'x':
			xflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

D 2
	fp = stdin;
	do {
		if (*argv)
			if (!(fp = fopen(*argv, "r"))) {
				(void)fprintf(stderr, "column: %s: %s\n",
				    *argv, strerror(errno));
				continue;
			} else
				++argv;
		input(fp);
		if (fp != stdin)
E 2
I 2
D 3
	eval = 0;
E 3
	if (!*argv)
		input(stdin);
	else for (; *argv; ++argv)
		if (fp = fopen(*argv, "r")) {
			input(fp);
E 2
			(void)fclose(fp);
D 2
	} while (*argv);
E 2
I 2
		} else {
D 10
			(void)fprintf(stderr, "column: %s: %s\n", *argv,
			    strerror(errno));
E 10
I 10
			warn("%s", *argv);
E 10
			eval = 1;
		}
E 2

	if (!entries)
D 2
		exit(0);
E 2
I 2
		exit(eval);
E 2

D 3
	if (maxlength >= termwidth)
		print();
	else if (xflag)
		c_columnate();
	else
		r_columnate();
E 3
I 3
	if (tflag)
		maketbl();
D 7
	else {
		if (maxlength >= termwidth)
			print();
		if (xflag)
			c_columnate();
		else
			r_columnate();
	}
E 7
I 7
	else if (maxlength >= termwidth)
		print();
	else if (xflag)
		c_columnate();
	else
		r_columnate();
E 7
E 3
D 2
	exit(0);
E 2
I 2
	exit(eval);
E 2
}

#define	TAB	8
I 8
void
E 8
c_columnate()
{
D 10
	register int chcnt, col, cnt, numcols;
	int endcol;
E 10
I 10
	int chcnt, col, cnt, endcol, numcols;
E 10
	char **lp;

	maxlength = (maxlength + TAB) & ~(TAB - 1);
	numcols = termwidth / maxlength;
	endcol = maxlength;
	for (chcnt = col = 0, lp = list;; ++lp) {
		chcnt += printf("%s", *lp);
		if (!--entries)
			break;
		if (++col == numcols) {
			chcnt = col = 0;
			endcol = maxlength;
			putchar('\n');
		} else {
			while ((cnt = (chcnt + TAB & ~(TAB - 1))) <= endcol) {
				(void)putchar('\t');
				chcnt = cnt;
			}
			endcol += maxlength;
		}
	}
	if (chcnt)
		putchar('\n');
}

I 8
void
E 8
r_columnate()
{
D 10
	register int base, chcnt, cnt, col;
	int endcol, numcols, numrows, row;
E 10
I 10
	int base, chcnt, cnt, col, endcol, numcols, numrows, row;
E 10

	maxlength = (maxlength + TAB) & ~(TAB - 1);
	numcols = termwidth / maxlength;
	numrows = entries / numcols;
	if (entries % numcols)
		++numrows;

	for (row = 0; row < numrows; ++row) {
		endcol = maxlength;
		for (base = row, chcnt = col = 0; col < numcols; ++col) {
			chcnt += printf("%s", list[base]);
			if ((base += numrows) >= entries)
				break;
			while ((cnt = (chcnt + TAB & ~(TAB - 1))) <= endcol) {
				(void)putchar('\t');
				chcnt = cnt;
			}
			endcol += maxlength;
		}
		putchar('\n');
	}
}

I 8
void
E 8
print()
{
D 10
	register int cnt;
	register char **lp;
E 10
I 10
	int cnt;
	char **lp;
E 10

	for (cnt = entries, lp = list; cnt--; ++lp)
D 3
		printf("%s\n", *lp);
E 3
I 3
		(void)printf("%s\n", *lp);
E 3
}

I 3
typedef struct _tbl {
	char **list;
	int cols, *len;
} TBL;
#define	DEFCOLS	25

I 8
void
E 8
maketbl()
{
D 10
	register TBL *t;
	register int coloff, cnt;
	register char *p, **lp;
E 10
I 10
	TBL *t;
	int coloff, cnt;
	char *p, **lp;
E 10
	int *lens, maxcols;
	TBL *tbl;
D 8
	char **cols, *emalloc(), *realloc();
E 8
I 8
	char **cols;
E 8

D 8
	t = tbl = (TBL *)emalloc(entries * sizeof(TBL));
	cols = (char **)emalloc((maxcols = DEFCOLS) * sizeof(char *));
	lens = (int *)emalloc(maxcols * sizeof(int));
E 8
I 8
	t = tbl = emalloc(entries * sizeof(TBL));
	cols = emalloc((maxcols = DEFCOLS) * sizeof(char *));
	lens = emalloc(maxcols * sizeof(int));
E 8
	for (cnt = 0, lp = list; cnt < entries; ++cnt, ++lp, ++t) {
D 4
		for (coloff = 0, p = *lp; cols[coloff] = strtok(p, "\t ");
E 4
I 4
		for (coloff = 0, p = *lp; cols[coloff] = strtok(p, separator);
E 4
		    p = NULL)
			if (++coloff == maxcols) {
D 8
				if (!(cols = (char **)realloc((char *)cols,
				    (u_int)maxcols + DEFCOLS * sizeof(char *))) ||
				    !(lens = (int *)realloc((char *)lens,
E 8
I 8
				if (!(cols = realloc(cols, (u_int)maxcols +
				    DEFCOLS * sizeof(char *))) ||
				    !(lens = realloc(lens,
E 8
				    (u_int)maxcols + DEFCOLS * sizeof(int))))
D 10
					nomem();
				bzero((char *)lens + maxcols * sizeof(int),
				    DEFCOLS * sizeof(int));
E 10
I 10
					err(1, NULL);
				memset((char *)lens + maxcols * sizeof(int),
				    0, DEFCOLS * sizeof(int));
E 10
				maxcols += DEFCOLS;
			}
D 8
		t->list = (char **)emalloc(coloff * sizeof(char *));
		t->len = (int *)emalloc(coloff * sizeof(int));
E 8
I 8
		t->list = emalloc(coloff * sizeof(char *));
		t->len = emalloc(coloff * sizeof(int));
E 8
		for (t->cols = coloff; --coloff >= 0;) {
			t->list[coloff] = cols[coloff];
			t->len[coloff] = strlen(cols[coloff]);
			if (t->len[coloff] > lens[coloff])
				lens[coloff] = t->len[coloff];
		}
	}
	for (cnt = 0, t = tbl; cnt < entries; ++cnt, ++t) {
		for (coloff = 0; coloff < t->cols  - 1; ++coloff)
			(void)printf("%s%*s", t->list[coloff],
			    lens[coloff] - t->len[coloff] + 2, " ");
		(void)printf("%s\n", t->list[coloff]);
	}
}

E 3
#define	DEFNUM		1000
D 10
#define	MAXLINELEN	(2048 + 1)
E 10
I 10
#define	MAXLINELEN	(LINE_MAX + 1)
E 10

I 8
void
E 8
input(fp)
D 10
	register FILE *fp;
E 10
I 10
	FILE *fp;
E 10
{
D 3
	static u_int maxentry;
E 3
I 3
	static int maxentry;
E 3
D 10
	register int len;
	register char *p;
D 3
	char buf[MAXLINELEN], *malloc(), *realloc();
E 3
I 3
D 8
	char buf[MAXLINELEN], *emalloc(), *realloc();
E 8
I 8
	char buf[MAXLINELEN];
E 10
I 10
	int len;
	char *p, buf[MAXLINELEN];
E 10
E 8
E 3

D 3
	if (!list &&
	    !(list = (char **)malloc((maxentry = DEFNUM) * sizeof(char *))))
		nomem();
E 3
I 3
	if (!list)
D 8
		list = (char **)emalloc((maxentry = DEFNUM) * sizeof(char *));
E 8
I 8
		list = emalloc((maxentry = DEFNUM) * sizeof(char *));
E 8
E 3
	while (fgets(buf, MAXLINELEN, fp)) {
D 3
		if (buf[0] == '\n')
E 3
I 3
		for (p = buf; *p && isspace(*p); ++p);
		if (!*p)
E 3
			continue;
I 3
D 10
		if (!(p = index(p, '\n'))) {
			(void)fprintf(stderr, "column: line too long.\n");
E 10
I 10
		if (!(p = strchr(p, '\n'))) {
			warnx("line too long");
E 10
			eval = 1;
			continue;
		}
		*p = '\0';
		len = p - buf;
		if (maxlength < len)
			maxlength = len;
E 3
		if (entries == maxentry) {
			maxentry += DEFNUM;
D 8
			if (!(list =
D 3
			    (char **)realloc(list, maxentry * sizeof(char *))))
E 3
I 3
			    (char **)realloc((char *)list,
E 8
I 8
			if (!(list = realloc(list,
E 8
			    (u_int)maxentry * sizeof(char *))))
E 3
D 10
				nomem();
E 10
I 10
				err(1, NULL);
E 10
		}
D 3
		if (p = index(buf, '\n')) {
			*p = '\0';
			len = p - buf;
		}
		else
			len = strlen(buf);
		if (maxlength < len)
			maxlength = len;
E 3
		list[entries++] = strdup(buf);
	}
}

I 3
D 8
char *
E 8
I 8
void *
E 8
emalloc(size)
	int size;
{
D 8
	char *p, *malloc();
E 8
I 8
	char *p;
E 8

D 8
	/* NOSTRICT */
	if (!(p = malloc((u_int)size)))
E 8
I 8
	if (!(p = malloc(size)))
E 8
D 10
		nomem();
	bzero(p, size);
	return(p);
E 10
I 10
		err(1, NULL);
	memset(p, 0, size);
	return (p);
E 10
}

I 8
void
E 8
E 3
D 10
nomem()
{
	(void)fprintf(stderr, "column: out of memory.\n");
	exit(1);
}

I 8
void
E 10
E 8
usage()
{
I 10

E 10
	(void)fprintf(stderr,
D 3
	    "usage: column [-x] [-c columns] [file ...]\n");
E 3
I 3
	    "usage: column [-tx] [-c columns] [file ...]\n");
E 3
	exit(1);
}
E 1
