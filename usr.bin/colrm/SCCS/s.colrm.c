h03697
s 00001/00000/00141
d D 8.2 95/05/04 15:34:32 bostic 11 10
c optarg/optind moved to unistd.h
e
s 00005/00005/00136
d D 8.1 93/06/06 14:28:35 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00111/00070/00030
d D 5.5 92/01/08 12:41:33 bostic 9 8
c welcome to the 90's (or at least the 80's); complete rewrite.
e
s 00001/00011/00099
d D 5.4 90/06/01 16:46:25 bostic 8 7
c new copyright notice
e
s 00010/00005/00100
d D 5.3 88/06/29 21:50:40 bostic 7 6
c install approved copyright notice
e
s 00011/00004/00094
d D 5.2 87/12/02 17:32:09 bostic 6 5
c bug report 4.3BSD/ucb/149; exit 0 on success
e
s 00016/00001/00082
d D 5.1 85/05/31 09:08:55 dist 5 4
c Add copyright
e
s 00021/00021/00062
d D 4.4 84/07/02 16:13:43 ralph 4 3
c fix line length limitations and don't use setbuf.
e
s 00008/00003/00075
d D 4.3 82/02/13 23:16:08 root 3 2
c change to really check for eof from stdin
e
s 00007/00002/00071
d D 4.2 80/10/10 00:42:07 bill 2 1
c handle tabs properly
e
s 00073/00000/00000
d D 4.1 80/10/01 17:25:49 bill 1 0
c date and time created 80/10/01 17:25:49 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
I 2
D 5
static	char *Sccsid = "%W% (Berkeley) %G%";
E 5
I 5
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
E 9
I 9
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
E 9
D 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 8
 * Redistribution and use in source and binary forms are permitted
D 7
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
E 6
 */

#ifndef lint
D 10
char copyright[] =
D 9
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 9
I 9
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
E 9
 All rights reserved.\n";
E 10
I 10
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6

I 9
#include <sys/types.h>
#include <limits.h>
#include <errno.h>
E 9
E 5
E 2
#include <stdio.h>
D 9
/*
COLRM removes unwanted columns from a file
	Jeff Schriebman  UC Berkeley 11-74
*/
E 9
I 9
#include <stdlib.h>
#include <string.h>
I 11
#include <unistd.h>
E 11
E 9

I 9
#define	TAB	8
E 9

D 9
main(argc,argv)
char **argv;
E 9
I 9
void err __P((const char *, ...));
void check __P((FILE *));
void usage __P((void));

int
main(argc, argv)
	int argc;
	char *argv[];
E 9
{
D 4
	int first;
	register ct,last;
	register char c;
	char buffer[BUFSIZ];
E 4
I 4
D 9
	register c, ct, first, last;
E 9
I 9
	register u_long column, start, stop;
	register int ch;
	char *p;
E 9
E 4

D 4
	setbuf(stdout, buffer);
	first = 20000;
	last  = -1;
	if (argc>1) {
E 4
I 4
D 9
	first = 0;
	last = 0;
	if (argc > 1)
E 4
		first = getn(*++argv);
D 4
		last = 20000;
	}
	if (argc>2)
E 4
I 4
	if (argc > 2)
E 4
		last = getn(*++argv);
E 9
I 9
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;
E 9

D 9
start:
	ct = 0;
loop1:
D 3
	if ((c=getc(stdin))<0)
E 3
I 3
	c = getc(stdin);
	if (feof(stdin))
E 3
		goto fin;
D 2
	ct++;
E 2
I 2
	if (c == '\t')
D 4
		ct = (ct + 8) &~ 7;
E 4
I 4
		ct = (ct + 8) & ~7;
E 4
	else if (c == '\b')
		ct = ct ? ct - 1 : 0;
	else
		ct++;
E 2
D 4
	if (c=='\n') {
		putc(c,stdout);
E 4
I 4
	if (c == '\n') {
		putc(c, stdout);
E 4
		goto start;
E 9
I 9
	start = stop = 0;
	switch(argc) {
	case 2:
		stop = strtol(argv[1], &p, 10);
		if (stop <= 0 || *p)
			err("illegal column -- %s", argv[1]);
		/* FALLTHROUGH */
	case 1:
		start = strtol(argv[0], &p, 10);
		if (start <= 0 || *p)
			err("illegal column -- %s", argv[0]);
		break;
	case 0:
		break;
	default:
		usage();
E 9
	}
D 4
	if (ct<first) {
		putc(c,stdout);
E 4
I 4
D 9
	if (!first || ct < first) {
		putc(c, stdout);
E 4
		goto loop1;
	}
E 9

D 9
/* Loop getting rid of characters */
D 4
	for (;ct<last;ct++) {
E 4
I 4
	while (!last || ct < last) {
E 4
D 3
		if ((c=getc(stdin))<0)
E 3
I 3
		c = getc(stdin);
		if (feof(stdin))
E 3
			goto fin;
D 4
		if (c=='\n') {
			putc(c,stdout);
E 4
I 4
		if (c == '\n') {
			putc(c, stdout);
E 4
			goto start;
		}
I 4
		if (c == '\t')
			ct = (ct + 8) & ~7;
		else if (c == '\b')
			ct = ct ? ct - 1 : 0;
		else
			ct++;
E 4
	}
E 9
I 9
	if (stop && start > stop)
		err("illegal start and stop columns");
E 9

D 9
/* Output last of the line */
D 3
	while ((c=getc(stdin))>0) {
E 3
I 3
	for (;;) {
		c = getc(stdin);
		if (feof(stdin))
E 9
I 9
	for (column = 0;;) {
		switch (ch = getchar()) {
		case EOF:
			check(stdin);
E 9
			break;
E 3
D 4
		putc(c,stdout);
		if (c=='\n')
E 4
I 4
D 9
		putc(c, stdout);
		if (c == '\n')
E 4
			goto start;
E 9
I 9
		case '\b':
			if (column)
				--column;
			break;
		case '\n':
			column = 0;
			break;
		case '\t':
			column = (column + TAB) & ~(TAB - 1);
			break;
		default:
			++column;
			break;
		}

		if ((!start || column < start || stop && column > stop) &&
		    putchar(ch) == EOF)
			check(stdout);
E 9
	}
D 9
fin:
	fflush(stdout);
I 6
	exit(0);
E 9
E 6
}

D 9
getn(ap)
char *ap;
E 9
I 9
void
check(stream)
	FILE *stream;
E 9
{
D 9
	register int n,c;
	register char *p;
E 9
I 9
	if (feof(stream))
		exit(0);
	if (ferror(stream))
		err("%s: %s",
		    stream == stdin ? "stdin" : "stdout", strerror(errno));
}
E 9

D 9
	p = ap;
	n = 0;
	while ((c = *p++) >= '0' && c <= '9')
		n = n*10 + c - '0';
	return(n);
E 9
I 9
void
usage()
{
	(void)fprintf(stderr, "usage: colrm [start [stop]]\n");
	exit(1);
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
	(void)fprintf(stderr, "colrm: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 9
}
E 1
