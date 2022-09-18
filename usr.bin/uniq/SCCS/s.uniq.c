h43103
s 00001/00000/00249
d D 8.3 95/05/04 15:48:28 bostic 9 8
c optarg/optind moved to unistd.h
e
s 00002/00001/00247
d D 8.2 95/04/28 14:11:58 bostic 8 7
c Fixed case where output is returned with -c option and empty file.
c (POSIX 1003.2 D11.2 section 4.69.6.2)
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00243
d D 8.1 93/06/06 16:41:33 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00001/00243
d D 5.5 92/07/15 09:07:35 bostic 6 5
c quit if the input is empty; test case is "uniq -c /dev/null"
e
s 00098/00044/00146
d D 5.4 92/01/09 10:37:56 bostic 5 4
c make source match the man page, handle -number/+number more cleanly
e
s 00001/00001/00189
d D 5.3 91/09/12 19:57:00 leres 4 3
c Be careful to not look at **argv unless there are more arguments.
e
s 00001/00011/00189
d D 5.2 90/06/01 17:49:04 bostic 3 2
c new copyright notice
e
s 00168/00111/00032
d D 5.1 89/05/28 13:43:15 bostic 2 1
c uniq replacement -- old uniq didn't handle `-d -u' or `-c -anything'
c reasonably.  Hopefully POSIX will fix all this.
e
s 00143/00000/00000
d D 4.1 80/10/01 17:29:11 bill 1 0
c date and time created 80/10/01 17:29:11 by bill
e
u
U
t
T
I 1
D 2
static char *sccsid = "%W% (Berkeley) %G%";
E 2
/*
D 2
 * Deal with duplicated lines in a file
E 2
I 2
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Case Larsen.
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */
I 2

#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 5
#include <errno.h>
E 5
E 2
#include <stdio.h>
#include <ctype.h>
I 5
#include <stdlib.h>
#include <string.h>
I 9
#include <unistd.h>
E 9
E 5
D 2
int	fields;
int	letters;
int	linec;
char	mode;
int	uniq;
char	*skip();
E 2

I 5
#define	MAXLINELEN	(8 * 1024)

E 5
D 2
main(argc, argv)
int argc;
char *argv[];
{
	static char b1[1000], b2[1000];
E 2
I 2
int cflag, dflag, uflag;
int numchars, numfields, repeats;
E 2

D 2
	while(argc > 1) {
		if(*argv[1] == '-') {
			if (isdigit(argv[1][1]))
				fields = atoi(&argv[1][1]);
			else mode = argv[1][1];
			argc--;
			argv++;
			continue;
		}
		if(*argv[1] == '+') {
			letters = atoi(&argv[1][1]);
			argc--;
			argv++;
			continue;
		}
		if (freopen(argv[1], "r", stdin) == NULL)
			printe("cannot open %s\n", argv[1]);
		break;
	}
	if(argc > 2 && freopen(argv[2], "w", stdout) == NULL)
		printe("cannot create %s\n", argv[2]);
E 2
I 2
D 5
#define	MAXLINELEN	(2048 + 1)
E 5
I 5
void	 err __P((const char *, ...));
FILE	*file __P((char *, char *));
void	 show __P((FILE *, char *));
char	*skip __P((char *));
void	 obsolete __P((char *[]));
void	 usage __P((void));
E 5
E 2

D 2
	if(gline(b1))
		exit(0);
	for(;;) {
		linec++;
		if(gline(b2)) {
			pline(b1);
			exit(0);
		}
		if(!equal(b1, b2)) {
			pline(b1);
			linec = 0;
			do {
				linec++;
				if(gline(b1)) {
					pline(b2);
					exit(0);
				}
			} while(equal(b1, b2));
			pline(b2);
			linec = 0;
		}
	}
}

gline(buf)
register char buf[];
E 2
I 2
D 5
main (argc,argv)
E 5
I 5
int
main (argc, argv)
E 5
	int argc;
D 5
	char **argv;
E 5
I 5
	char *argv[];
E 5
E 2
{
D 2
	register c;
E 2
I 2
D 5
	extern int optind;
	FILE *ifp, *ofp, *file();
	int ch;
E 5
	register char *t1, *t2;
D 5
	char *prevline, *thisline, *malloc(), *skip();
E 5
I 5
	FILE *ifp, *ofp;
	int ch;
	char *prevline, *thisline, *p;
E 5
E 2

D 2
	while((c = getchar()) != '\n') {
		if(c == EOF)
			return(1);
		*buf++ = c;
E 2
I 2
D 5
	while ((ch = getopt(argc, argv, "-cdu123456789")) != EOF)
E 5
I 5
	obsolete(argv);
	while ((ch = getopt(argc, argv, "-cdf:s:u")) != EOF)
E 5
		switch (ch) {
		case '-':
			--optind;
			goto done;
		case 'c':
			cflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
I 5
		case 'f':
			numfields = strtol(optarg, &p, 10);
			if (numfields < 0 || *p)
				err("illegal field skip value: %s", optarg);
			break;
		case 's':
			numchars = strtol(optarg, &p, 10);
			if (numchars < 0 || *p)
				err("illegal character skip value: %s", optarg);
			break;
E 5
		case 'u':
			uflag = 1;
			break;
D 5
		/*
		 * since -n is a valid option that could be picked up by
		 * getopt, but is better handled by the +n and -n code, we
		 * break out.
		 */
		case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			--optind;
			goto done;
E 5
		case '?':
		default:
			usage();
E 2
	}
D 2
	*buf = 0;
	return(0);
}
E 2

D 2
pline(buf)
register char buf[];
{
E 2
I 2
done:	argc -= optind;
	argv +=optind;
E 2

D 2
	switch(mode) {
E 2
I 2
D 5
	/* if no flags are set, default is -d -u */
E 5
I 5
	/* If no flags are set, default is -d -u. */
E 5
	if (cflag) {
		if (dflag || uflag)
			usage();
	} else if (!dflag && !uflag)
		dflag = uflag = 1;
E 2

D 2
	case 'u':
		if(uniq) {
			uniq = 0;
			return;
E 2
I 2
D 5
	/* because of the +, getopt is messed up */
D 4
	for (; **argv == '+' || **argv == '-'; ++argv, --argc)
E 4
I 4
	for (; argc > 0 && (**argv == '+' || **argv == '-'); ++argv, --argc)
E 4
		switch (**argv) {
		case '+':
			if ((numchars = atoi(*argv + 1)) < 0)
				goto negerr;
			break;
		case '-':
			if ((numfields = atoi(*argv + 1)) < 0) {
negerr:				(void)fprintf(stderr,
				    "uniq: negative field/char skip value.\n");
				usage();
			}
			break;
E 2
		}
I 2
    
E 5
	switch(argc) {
	case 0:
		ifp = stdin;
		ofp = stdout;
E 2
		break;
I 2
	case 1:
		ifp = file(argv[0], "r");
		ofp = stdout;
		break;
	case 2:
		ifp = file(argv[0], "r");
		ofp = file(argv[1], "w");
		break;
	default:
		usage();
	}
E 2

D 2
	case 'd':
		if(uniq) break;
		return;
E 2
I 2
	prevline = malloc(MAXLINELEN);
	thisline = malloc(MAXLINELEN);
D 6
	(void)fgets(prevline, MAXLINELEN, ifp);
E 6
I 6
	if (prevline == NULL || thisline == NULL)
		err("%s", strerror(errno));

	if (fgets(prevline, MAXLINELEN, ifp) == NULL)
		exit(0);
E 6
E 2

D 2
	case 'c':
		printf("%4d ", linec);
E 2
I 2
	while (fgets(thisline, MAXLINELEN, ifp)) {
D 5
		/* if requested get the chosen fields + character offsets */
E 5
I 5
		/* If requested get the chosen fields + character offsets. */
E 5
		if (numfields || numchars) {
			t1 = skip(thisline);
			t2 = skip(prevline);
		} else {
			t1 = thisline;
			t2 = prevline;
		}

D 5
		/* if different, print; set previous to new value */
E 5
I 5
		/* If different, print; set previous to new value. */
E 5
		if (strcmp(t1, t2)) {
			show(ofp, prevline);
			t1 = prevline;
			prevline = thisline;
			thisline = t1;
			repeats = 0;
D 5
		}
		else
E 5
I 5
		} else
E 5
			++repeats;
E 2
	}
D 2
	uniq = 0;
	fputs(buf, stdout);
	putchar('\n');
E 2
I 2
	show(ofp, prevline);
	exit(0);
E 2
}

D 2
equal(b1, b2)
register char b1[], b2[];
E 2
I 2
/*
 * show --
D 5
 *	output a line depending on the flags and number of repetitions
E 5
I 5
 *	Output a line depending on the flags and number of repetitions
E 5
 *	of the line.
 */
I 5
void
E 5
show(ofp, str)
	FILE *ofp;
	char *str;
E 2
{
D 2
	register char c;

	b1 = skip(b1);
	b2 = skip(b2);
	while((c = *b1++) != 0)
		if(c != *b2++) return(0);
	if(*b2 != 0)
		return(0);
	uniq++;
	return(1);
E 2
I 2
D 8
	if (cflag)
E 8
I 8

	if (cflag && *str)
E 8
		(void)fprintf(ofp, "%4d %s", repeats + 1, str);
	if (dflag && repeats || uflag && !repeats)
		(void)fprintf(ofp, "%s", str);
E 2
}

char *
D 2
skip(s)
register char *s;
E 2
I 2
skip(str)
	register char *str;
E 2
{
D 2
	register nf, nl;
E 2
I 2
	register int infield, nchars, nfields;
E 2

D 2
	nf = nl = 0;
	while(nf++ < fields) {
		while(*s == ' ' || *s == '\t')
			s++;
		while( !(*s == ' ' || *s == '\t' || *s == 0) ) 
			s++;
E 2
I 2
	for (nfields = numfields, infield = 0; nfields && *str; ++str)
		if (isspace(*str)) {
			if (infield) {
				infield = 0;
				--nfields;
			}
		} else if (!infield)
			infield = 1;
	for (nchars = numchars; nchars-- && *str; ++str);
	return(str);
}

FILE *
file(name, mode)
	char *name, *mode;
{
	FILE *fp;

D 5
	if (!(fp = fopen(name, mode))) {
		(void)fprintf(stderr, "uniq: can't open %s.\n", name);
		exit(1);
E 2
	}
E 5
I 5
	if ((fp = fopen(name, mode)) == NULL)
		err("%s: %s", name, strerror(errno));
E 5
D 2
	while(nl++ < letters && *s != 0) 
			s++;
	return(s);
E 2
I 2
	return(fp);
E 2
}

I 5
void
obsolete(argv)
	char *argv[];
{
	int len;
	char *ap, *p, *start;

	while (ap = *++argv) {
		/* Return if "--" or not an option of any form. */
		if (ap[0] != '-') {
			if (ap[0] != '+')
				return;
		} else if (ap[1] == '-')
			return;
		if (!isdigit(ap[1]))
			continue;
		/*
		 * Digit signifies an old-style option.  Malloc space for dash,
		 * new option and argument.
		 */
		len = strlen(ap);
		if ((start = p = malloc(len + 3)) == NULL)
			err("%s", strerror(errno));
		*p++ = '-';
		*p++ = ap[0] == '+' ? 's' : 'f';
		(void)strcpy(p, ap + 1);
		*argv = start;
	}
}

void
E 5
D 2
printe(p,s)
char *p,*s;
E 2
I 2
usage()
E 2
{
D 2
	fprintf(stderr, p, s);
E 2
I 2
	(void)fprintf(stderr,
D 5
	    "usage: uniq [-c | -du] [- #fields] [+ #chars] [input [output]]\n");
E 5
I 5
	    "usage: uniq [-c | -du] [-f fields] [-s chars] [input [output]]\n");
E 5
E 2
	exit(1);
I 5
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
	(void)fprintf(stderr, "uniq: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 5
}
E 1
