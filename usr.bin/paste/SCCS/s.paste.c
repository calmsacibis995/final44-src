h09384
s 00005/00005/00220
d D 8.1 93/06/06 15:50:11 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00223
d D 5.7 90/10/30 09:33:03 bostic 7 6
c BSD_LINE_MAX -> POSIX2_LINE_MAX
e
s 00002/00002/00223
d D 5.6 90/06/24 15:21:53 bostic 6 5
c LINE_MAX -> _BSD_LINE_MAX
e
s 00001/00011/00224
d D 5.5 90/06/01 17:29:31 bostic 5 4
c new copyright notice
e
s 00002/00003/00233
d D 5.4 90/06/01 17:29:24 bostic 4 3
c strings.h -> string.h
e
s 00018/00011/00218
d D 5.3 90/03/06 12:50:40 bostic 3 2
c output delimiters even if the input file is empty
e
s 00001/00001/00228
d D 5.2 90/03/06 12:05:47 bostic 2 1
c bug, tries to open "-"
e
s 00229/00000/00000
d D 5.1 89/12/31 16:42:55 bostic 1 0
c date and time created 89/12/31 16:42:55 by bostic
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Adam S. Moskowitz of Menlo Consulting.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 */

#ifndef lint
D 8
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
D 4
#include <strings.h>
E 4
I 4
#include <string.h>
E 4

D 4
extern int errno;
E 4
char *delim;
int delimcnt;

D 4
main (argc, argv)
E 4
I 4
main(argc, argv)
E 4
	int argc;
	char **argv;
{
	extern char *optarg;
	extern int optind;
	int ch, seq;

	seq = 0;
	while ((ch = getopt(argc, argv, "d:s")) != EOF)
		switch(ch) {
		case 'd':
			delimcnt = tr(delim = optarg);
			break;
		case 's':
			seq = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!delim) {
		delimcnt = 1;
		delim = "\t";
	}

	if (seq)
		sequential(argv);
	else
		parallel(argv);
	exit(0);
}

typedef struct _list {
	struct _list *next;
	FILE *fp;
	int cnt;
	char *name;
} LIST;

parallel(argv)
	char **argv;
{
	register LIST *lp;
	register int cnt;
	register char ch, *p;
	LIST *head, *tmp;
	int opencnt, output;
D 6
	char buf[LINE_MAX + 1], *malloc();
E 6
I 6
D 7
	char buf[_BSD_LINE_MAX + 1], *malloc();
E 7
I 7
	char buf[_POSIX2_LINE_MAX + 1], *malloc();
E 7
E 6

	for (cnt = 0, head = NULL; p = *argv; ++argv, ++cnt) {
		if (!(lp = (LIST *)malloc((u_int)sizeof(LIST)))) {
			(void)fprintf(stderr, "paste: %s.\n", strerror(ENOMEM));
			exit(1);
		}
		if (p[0] == '-' && !p[1])
			lp->fp = stdin;
		else if (!(lp->fp = fopen(p, "r"))) {
			(void)fprintf(stderr, "paste: %s: %s.\n", p,
			    strerror(errno));
			exit(1);
		}
		lp->next = NULL;
		lp->cnt = cnt;
		lp->name = p;
		if (!head)
			head = tmp = lp;
		else {
			tmp->next = lp;
			tmp = lp;
		}
	}

	for (opencnt = cnt; opencnt;) {
D 3
		for (cnt = -1, output = 0, lp = head; lp; lp = lp->next) {
E 3
I 3
		for (output = 0, lp = head; lp; lp = lp->next) {
E 3
			if (!lp->fp) {
D 3
				if (cnt == -1)
					cnt = 0;
E 3
I 3
				if (output && lp->cnt &&
				    (ch = delim[(lp->cnt - 1) % delimcnt]))
					putchar(ch);
E 3
				continue;
			}
			if (!fgets(buf, sizeof(buf), lp->fp)) {
				if (!--opencnt)
					break;
				lp->fp = NULL;
D 3
				if (cnt == -1)
					cnt = 0;
E 3
I 3
				if (output && lp->cnt &&
				    (ch = delim[(lp->cnt - 1) % delimcnt]))
					putchar(ch);
E 3
				continue;
			}
			if (!(p = index(buf, '\n'))) {
				(void)fprintf(stderr,
				    "paste: %s: input line too long.\n",
				    lp->name);
				exit(1);
			}
			*p = '\0';
D 3
			if (cnt == -1)
				cnt = 0;
			else for (; cnt < lp->cnt; ++cnt)
				if (ch = delim[cnt % delimcnt])
					putchar(ch);
			output = 1;
E 3
I 3
			/*
			 * make sure that we don't print any delimiters
			 * unless there's a non-empty file.
			 */
			if (!output) {
				output = 1;
				for (cnt = 0; cnt < lp->cnt; ++cnt)
					if (ch = delim[cnt % delimcnt])
						putchar(ch);
			} else if (ch = delim[(lp->cnt - 1) % delimcnt])
				putchar(ch);
E 3
			(void)printf("%s", buf);
		}
		if (output)
			putchar('\n');
	}
}

sequential(argv)
	char **argv;
{
	register FILE *fp;
	register int cnt;
	register char ch, *p, *dp;
D 6
	char buf[LINE_MAX + 1];
E 6
I 6
D 7
	char buf[_BSD_LINE_MAX + 1];
E 7
I 7
	char buf[_POSIX2_LINE_MAX + 1];
E 7
E 6

	for (; p = *argv; ++argv) {
		if (p[0] == '-' && !p[1])
			fp = stdin;
D 2
		if (!(fp = fopen(p, "r"))) {
E 2
I 2
		else if (!(fp = fopen(p, "r"))) {
E 2
			(void)fprintf(stderr, "paste: %s: %s.\n", p,
			    strerror(errno));
			continue;
		}
		if (fgets(buf, sizeof(buf), fp)) {
			for (cnt = 0, dp = delim;;) {
				if (!(p = index(buf, '\n'))) {
					(void)fprintf(stderr,
					    "paste: %s: input line too long.\n",
					    *argv);
					exit(1);
				}
				*p = '\0';
				(void)printf("%s", buf);
				if (!fgets(buf, sizeof(buf), fp))
					break;
				if (ch = *dp++)
					putchar(ch);
				if (++cnt == delimcnt) {
					dp = delim;
					cnt = 0;
				}
			}
			putchar('\n');
		}
		if (fp != stdin)
			(void)fclose(fp);
	}
}

tr(arg)
	char *arg;
{
	register int cnt;
	register char ch, *p;

	for (p = arg, cnt = 0; (ch = *p++); ++arg, ++cnt)
		if (ch == '\\')
			switch(ch = *p++) {
			case 'n':
				*arg = '\n';
				break;
			case 't':
				*arg = '\t';
				break;
			case '0':
				*arg = '\0';
				break;
			default:
				*arg = ch;
				break;
		} else
			*arg = ch;

	if (!cnt) {
		(void)fprintf(stderr, "paste: no delimiters specified.\n");
		exit(1);
	}
	return(cnt);
}

usage()
{
	(void)fprintf(stderr, "paste: [-s] [-d delimiters] file ...\n");
	exit(1);
}
E 1
