h03740
s 00001/00000/00083
d D 8.3 95/05/04 15:46:33 bostic 11 10
c optarg/optind moved to unistd.h
e
s 00003/00001/00080
d D 8.2 94/01/02 14:26:52 bostic 10 9
c fgetline(3) interface changed, newline no longer replaced
c From: "Chris G. Demetriou" <cgd@vangogh.CS.Berkeley.EDU>
c rename fgetline -> fgetln
e
s 00005/00005/00076
d D 8.1 93/06/09 22:52:18 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00031/00076
d D 5.3 93/05/20 16:39:40 bostic 8 7
c use library versions of warn and friends
e
s 00001/00001/00106
d D 5.2 92/03/21 10:48:15 bostic 7 6
c forgot to exit with right status
e
s 00079/00015/00028
d D 5.1 92/03/21 10:44:42 bostic 6 5
c bring rev back into the main-line source tree
c reimplement it to work like the rest of the programs
e
s 00004/00014/00039
d D 4.5 91/07/17 16:44:48 bostic 5 4
c new copyright; att/bsd/shared
e
s 00010/00005/00043
d D 4.4 88/06/29 21:54:32 bostic 4 3
c install approved copyright notice
e
s 00039/00037/00009
d D 4.3 87/12/13 13:59:04 bostic 3 2
c handle lines larger than 256 chars
e
s 00001/00000/00045
d D 4.2 87/12/02 16:46:57 bostic 2 1
c bug report 4.3BSD/usr.bin/110; exit 0 on success
e
s 00045/00000/00000
d D 4.1 80/10/01 17:28:10 bill 1 0
c date and time created 80/10/01 17:28:10 by bill
e
u
U
t
T
I 1
D 3
static char *sccsid = "%W% (Berkeley) %G%";
#include <stdio.h>
E 3
I 3
D 5
/*
 * Copyright (c) 1987 Regents of the University of California.
E 5
I 5
/*-
D 6
 * Copyright (c) 1987 The Regents of the University of California.
E 6
I 6
D 9
 * Copyright (c) 1987, 1992 The Regents of the University of California.
E 6
E 5
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1987, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 4
 */
E 3

D 3
/* reverse lines of a file */
E 3
I 3
#ifndef lint
D 9
char copyright[] =
D 5
"%Z% Copyright (c) 1987 Regents of the University of California.\n\
E 5
I 5
D 6
"%Z% Copyright (c) 1987 The Regents of the University of California.\n\
E 6
I 6
"%Z% Copyright (c) 1987, 1992 The Regents of the University of California.\n\
E 6
E 5
 All rights reserved.\n";
E 9
I 9
static char copyright[] =
"%Z% Copyright (c) 1987, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 9
#endif /* not lint */
E 3

D 3
#define N 256
char line[N];
FILE *input;
E 3
I 3
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

I 6
#include <sys/types.h>
I 8

#include <err.h>
E 8
#include <errno.h>
E 6
D 3
main(argc,argv)
char **argv;
E 3
I 3
#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
I 11
#include <unistd.h>
E 11
E 6

I 6
void usage __P((void));
D 8
void warn __P((const char *, ...));
E 8

int
E 6
main(argc, argv)
	int argc;
D 6
	char **argv;
E 6
I 6
	char *argv[];
E 6
E 3
{
D 3
	register i,c;
	input = stdin;
E 3
I 3
D 6
	register char *t, *bp;
	char buf[BUFSIZ];
E 6
I 6
	register char *filename, *p, *t;
	FILE *fp;
	size_t len;
	int ch, rval;
E 6

D 6
	bp = buf;
E 6
I 6
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch(ch) {
		case '?':
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	fp = stdin;
	filename = "stdin";
	rval = 0;
E 6
E 3
	do {
D 3
		if(argc>1) {
			if((input=fopen(argv[1],"r"))==NULL) {
				fprintf(stderr,"rev: cannot open %s\n",
					argv[1]);
				exit(1);
			}
E 3
I 3
D 6
		if (argc > 1 && !freopen(*++argv, "r", stdin)) {
			fprintf(stderr, "rev: cannot open %s.\n", *argv);
			exit(1);
E 6
I 6
		if (*argv) {
			if ((fp = fopen(*argv, "r")) == NULL) {
D 8
				warn("%s: %s", *argv, strerror(errno));
E 8
I 8
				warn("%s", *argv);
E 8
				rval = 1;
				++argv;
				continue;
			}
			filename = *argv++;
E 6
E 3
		}
D 3
		for(;;){
			for(i=0;i<N;i++) {
				line[i] = c = getc(input);
				switch(c) {
				case EOF:
					goto eof;
				default:
					continue;
				case '\n':
					break;
				}
				break;
			}
			while(--i>=0)
				putc(line[i],stdout);
			putc('\n',stdout);
E 3
I 3
D 6
		while (fgets(bp, sizeof(buf), stdin)) {
			for (t = bp; *t; ++t);
			if (*--t == '\n')
				--t;
			for (; t >= bp; --t)
E 6
I 6
D 8
		while (p = fgetline(fp, &len)) {
E 8
I 8
D 10
		while ((p = fgetline(fp, &len)) != NULL) {
E 10
I 10
		while ((p = fgetln(fp, &len)) != NULL) {
			if (p[len - 1] == '\n')
				--len;
E 10
E 8
			t = p + len - 1;
			for (t = p + len - 1; t >= p; --t)
E 6
				putchar(*t);
			putchar('\n');
E 3
		}
D 3
eof:
		fclose(input);
		argc--;
		argv++;
	} while(argc>1);
E 3
I 3
D 6
	} while(--argc > 1);
E 6
I 6
		if (ferror(fp)) {
D 8
			warn("%s: %s", filename, strerror(errno));
E 8
I 8
			warn("%s", filename);
E 8
			rval = 1;
		}
		(void)fclose(fp);
	} while(*argv);
E 6
E 3
I 2
D 7
	exit(0);
E 7
I 7
	exit(rval);
E 7
I 6
D 8
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
warn(const char *fmt, ...)
#else
warn(fmt, va_alist)
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
	(void)fprintf(stderr, "rev: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 8
}

void
usage()
{
	(void)fprintf(stderr, "usage: rev [file ...]\n");
	exit(1);
E 6
E 2
}
E 1
