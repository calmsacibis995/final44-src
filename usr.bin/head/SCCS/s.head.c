h24408
s 00004/00002/00152
d D 8.2 95/05/04 15:38:43 bostic 11 10
c optarg/optind moved to unistd.h
e
s 00005/00005/00149
d D 8.1 93/06/06 14:48:43 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00006/00145
d D 5.7 92/03/04 14:35:42 bostic 9 8
c can't use freopen; example is "date | head file1 /dev/stdin"
e
s 00117/00034/00034
d D 5.6 92/03/03 15:33:39 bostic 8 7
c add -n for POSIX 1003.2 compatibility, document file header
e
s 00001/00011/00067
d D 5.5 90/06/01 16:52:12 bostic 7 6
c new copyright notice
e
s 00010/00005/00068
d D 5.4 88/06/29 21:50:45 bostic 6 5
c install approved copyright notice
e
s 00010/00004/00063
d D 5.3 88/04/19 19:20:27 bostic 5 4
c add Berkeley specific copyright
e
s 00041/00064/00026
d D 5.2 87/11/14 14:30:40 bostic 4 3
c standardize error messages; don't close and then freopen stdin; 
c don't flush stdout after every line; use C library atoi; don't limit line 
c length; do lint cleanup
e
s 00016/00001/00074
d D 5.1 85/05/31 09:17:05 dist 3 2
c Add copyright
e
s 00000/00002/00075
d D 4.2 84/09/17 10:46:26 ralph 2 1
c don't call setbuf.
e
s 00077/00000/00000
d D 4.1 80/10/01 17:27:05 bill 1 0
c date and time created 80/10/01 17:27:05 by bill
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
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 8
 * Copyright (c) 1980, 1987 Regents of the University of California.
E 8
I 8
D 10
 * Copyright (c) 1980, 1987, 1992 Regents of the University of California.
E 8
E 4
D 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 5
I 5
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1980, 1987, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 7
 * Redistribution and use in source and binary forms are permitted
D 6
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 6
I 6
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
E 7
I 7
 * %sccs.include.redist.c%
E 7
E 6
E 5
 */

#ifndef lint
D 10
char copyright[] =
D 4
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 4
I 4
D 8
"%Z% Copyright (c) 1980, 1987 Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1980, 1987, 1992 Regents of the University of California.\n\
E 8
E 4
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1980, 1987, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 4
#endif not lint
E 4
I 4
D 5
#endif /* !lint */
E 5
I 5
#endif /* not lint */
E 5
E 4

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif /* !lint */
E 5
I 5
#endif /* not lint */
E 5
E 4

I 8
#include <sys/types.h>
I 11

#include <ctype.h>
E 11
#include <errno.h>
I 11
#include <stdio.h>
E 11
#include <stdlib.h>
#include <string.h>
E 8
E 3
D 11
#include <stdio.h>
I 4
#include <ctype.h>
E 11
I 11
#include <unistd.h>
E 11
I 8

E 8
E 4
/*
 * head - give the first few lines of a stream or of each of a set of files
 *
 * Bill Joy UCB August 24, 1977
 */

I 8
void err __P((int, const char *, ...));
D 9
void head __P((int));
E 9
I 9
void head __P((FILE *, int));
E 9
void obsolete __P((char *[]));
void usage __P((void));

int eval;

int
E 8
D 4
int	linecnt	= 10;
int	argc;

main(Argc, argv)
	int Argc;
	char *argv[];
E 4
I 4
main(argc, argv)
D 8
	int	argc;
	char	**argv;
E 8
I 8
	int argc;
	char *argv[];
E 8
E 4
{
D 4
	register int argc;
	char *name;
	register char *argp;
	static int around;
E 4
I 4
D 8
	register int	ch, cnt;
	int	firsttime, linecnt = 10;
E 8
I 8
	register int ch;
I 9
	FILE *fp;
E 9
	int first, linecnt;
	char *ep;
E 8
E 4
D 2
	char obuf[BUFSIZ];
E 2

D 2
	setbuf(stdout, obuf);
E 2
D 4
	Argc--, argv++;
	argc = Argc;
	do {
		while (argc > 0 && argv[0][0] == '-') {
			linecnt = getnum(argv[0] + 1);
			argc--, argv++, Argc--;
E 4
I 4
D 8
	if (argc > 1 && argv[1][0] == '-') {
		if (!isdigit(argv[1][1])) {
			fprintf(stderr, "head: illegal option -- %c\n", argv[1][1]);
			goto usage;
E 8
I 8
	obsolete(argv);
	linecnt = 10;
	while ((ch = getopt(argc, argv, "n:")) != EOF)
		switch(ch) {
		case 'n':
			linecnt = strtol(optarg, &ep, 10);
			if (*ep || linecnt <= 0)
				err(1, "illegal line count -- %s", optarg);
			break;
		case '?':
		default:
			usage();
E 8
E 4
		}
D 4
		if (argc == 0 && around)
			break;
		if (argc > 0) {
			close(0);
			if (freopen(argv[0], "r", stdin) == NULL) {
				perror(argv[0]);
E 4
I 4
D 8
		if ((linecnt = atoi(argv[1] + 1)) < 0) {
usage:			fputs("usage: head [-line_count] [file ...]\n", stderr);
			exit(1);
		}
		--argc; ++argv;
	}
	/* setlinebuf(stdout); */
	for (firsttime = 1, --argc, ++argv;; firsttime = 0) {
		if (!*argv) {
			if (!firsttime)
				exit(0);
		}
		else {
E 8
I 8
	argc -= optind;
	argv += optind;

	if (*argv)
		for (first = 1; *argv; ++argv) {
E 8
D 9
			if (!freopen(*argv, "r", stdin)) {
E 9
I 9
			if ((fp = fopen(*argv, "r")) == NULL) {
E 9
D 8
				fprintf(stderr, "head: can't read %s.\n", *argv);
E 4
				exit(1);
E 8
I 8
				err(0, "%s: %s", *argv, strerror(errno));
				continue;
E 8
			}
D 4
			name = argv[0];
			argc--, argv++;
		} else
			name = 0;
		if (around)
			putchar('\n');
		around++;
		if (Argc > 1 && name)
			printf("==> %s <==\n", name);
		copyout(linecnt);
		fflush(stdout);
	} while (argc > 0);
}

copyout(cnt)
	register int cnt;
{
	register int c;
	char lbuf[BUFSIZ];

	while (cnt > 0 && fgets(lbuf, sizeof lbuf, stdin) != 0) {
		printf("%s", lbuf);
		fflush(stdout);
		cnt--;
E 4
I 4
			if (argc > 1) {
D 8
				if (!firsttime)
					putchar('\n');
				printf("==> %s <==\n", *argv);
E 8
I 8
				(void)printf("%s==> %s <==\n",
				    first ? "" : "\n", *argv);
				first = 0;
E 8
			}
D 8
			++argv;
E 8
I 8
D 9
			head(linecnt);
E 9
I 9
			head(fp, linecnt);
			(void)fclose(fp);
E 9
E 8
		}
D 8
		for (cnt = linecnt; cnt; --cnt)
			while ((ch = getchar()) != EOF)
				if (putchar(ch) == '\n')
					break;
E 8
I 8
	else
D 9
		head(linecnt);
E 9
I 9
		head(stdin, linecnt);
E 9
	exit(eval);
}

void
D 9
head(cnt)
E 9
I 9
head(fp, cnt)
	FILE *fp;
E 9
	register int cnt;
{
	register int ch;

	while (cnt--)
D 9
		while ((ch = getchar()) != EOF) {
E 9
I 9
		while ((ch = getc(fp)) != EOF) {
E 9
			if (putchar(ch) == EOF)
				err(1, "stdout: %s", strerror(errno));
			if (ch == '\n')
				break;
		}
}

void
obsolete(argv)
	char *argv[];
{
	char *ap;

	while (ap = *++argv) {
		/* Return if "--" or not "-[0-9]*". */
		if (ap[0] != '-' || ap[1] == '-' || !isdigit(ap[1]))
			return;
		if ((ap = malloc(strlen(*argv) + 2)) == NULL)
			err(1, "%s", strerror(errno));
		ap[0] = '-';
		ap[1] = 'n';
		(void)strcpy(ap + 2, *argv + 1);
		*argv = ap;
E 8
E 4
	}
D 4
}

getnum(cp)
	register char *cp;
{
	register int i;

	for (i = 0; *cp >= '0' && *cp <= '9'; cp++)
		i *= 10, i += *cp - '0';
	if (*cp) {
		fprintf(stderr, "Badly formed number\n");
		exit(1);
	}
	return (i);
E 4
I 4
D 8
	/*NOTREACHED*/
E 8
I 8
}

void
usage()
{
	(void)fprintf(stderr, "usage: head [-n lines] [file ...]\n");
	exit(1);
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(int fatal, const char *fmt, ...)
#else
err(fatal, fmt, va_alist)
	int fatal;
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
	(void)fprintf(stderr, "head: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	if (fatal)
		exit(1);
	eval = 1;
E 8
E 4
}
E 1
