h25985
s 00005/00005/00202
d D 8.1 93/06/06 14:53:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00058/00043/00149
d D 4.6 93/05/26 21:09:56 bostic 6 5
c integrate into the 4BSD release
e
s 00027/00018/00165
d D 4.5 88/05/19 14:33:23 jak 5 4
c fixed -P bug, multiple -[PF] bug, and first line after EOF bug
c bug report 4.3BSD/new/23
e
s 00001/00001/00182
d D 4.4 86/04/05 00:40:53 lepreau 4 3
c args to setbuf were backwards
e
s 00002/00000/00181
d D 4.3 84/07/28 21:39:45 jak 3 2
c fixed bug in final separator string
e
s 00022/00008/00159
d D 4.2 84/02/11 13:35:09 jak 2 1
c added -t option
e
s 00167/00000/00000
d D 4.1 83/07/08 02:24:44 sam 1 0
c date and time created 83/07/08 02:24:44 by sam
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1983 Regents of the University of California */
E 6
I 6
/*-
D 7
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */
E 6

#ifndef lint
D 6
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 6
I 6
D 7
char copyright[] =
"%Z% Copyright (c) 1993 The Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif /* not lint */
E 6

I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 6
/*
 *	lam - laminate files
D 5
 *	Author:  John Kunze, Office of Comp. Affairs, UCB
E 5
I 5
 *	Author:  John Kunze, UCB
E 5
 */

#include <stdio.h>
I 6
#include <stdlib.h>
#include <string.h>
E 6

#define	MAXOFILES	20
#define	BIGBUFSIZ	5 * BUFSIZ

struct	openfile {		/* open file structure */
	FILE	*fp;		/* file pointer */
	short	eof;		/* eof flag */
	short	pad;		/* pad flag for missing columns */
I 2
	char	eol;		/* end of line character */
E 2
	char	*sepstring;	/* string to print before each line */
	char	*format;	/* printf(3) style string spec. */
}	input[MAXOFILES];

D 2
int	P;
int	S;
int	F;
E 2
int	morefiles;		/* set by getargs(), changed by gatherline() */
I 2
int	nofinalnl;		/* normally append \n to each output line */
E 2
D 6
char	buf[BUFSIZ];
E 6
char	line[BIGBUFSIZ];
char	*linep;

I 6
void	 error __P((char *, char *));
char	*gatherline __P((struct openfile *));
void	 getargs __P((char *[]));
char	*pad __P((struct openfile *));

int
E 6
main(argc, argv)
D 6
int	argc;
char	**argv;
E 6
I 6
	int argc;
	char *argv[];
E 6
{
D 6
	register struct	openfile	*ip;
	char	*gatherline();
E 6
I 6
	register struct	openfile *ip;
E 6

D 4
	setbuf(buf, stdout);
E 4
I 4
D 6
	setbuf(stdout, buf);
E 6
E 4
	getargs(argv);
	if (!morefiles)
		error("lam - laminate files", "");
	for (;;) {
		linep = line;
		for (ip = input; ip->fp != NULL; ip++)
			linep = gatherline(ip);
		if (!morefiles)
			exit(0);
		fputs(line, stdout);
		fputs(ip->sepstring, stdout);
D 2
		putchar('\n');
E 2
I 2
		if (!nofinalnl)
			putchar('\n');
E 2
	}
}

I 6
void
E 6
getargs(av)
D 6
char	**av;
E 6
I 6
	char *av[];
E 6
{
D 6
	register struct	openfile	*ip = input;
	register char	*p;
	register char	*c;
	static	char	fmtbuf[BUFSIZ];
	char	*fmtp = fmtbuf;
I 2
	int	P, S, F, T;
E 6
I 6
	register struct	openfile *ip = input;
	register char *p;
	register char *c;
	static char fmtbuf[BUFSIZ];
	char *fmtp = fmtbuf;
	int P, S, F, T;
E 6
E 2

I 2
	P = S = F = T = 0;		/* capitalized options */
E 2
D 6
	while (p = *++av) {
E 6
I 6
	while ((p = *++av) != NULL) {
E 6
		if (*p != '-' || !p[1]) {
			morefiles++;
			if (*p == '-')
				ip->fp = stdin;
			else if ((ip->fp = fopen(p, "r")) == NULL) {
				perror(p);
				exit(1);
			}
			ip->pad = P;
			if (!ip->sepstring)
				ip->sepstring = (S ? (ip-1)->sepstring : "");
			if (!ip->format)
D 5
				ip->format = (F ? (ip-1)->format : "%s");
E 5
I 5
				ip->format = ((P || F) ? (ip-1)->format : "%s");
E 5
I 2
			if (!ip->eol)
				ip->eol = (T ? (ip-1)->eol : '\n');
E 2
			ip++;
			continue;
		}
		switch (*(c = ++p) | 040) {
		case 's':
			if (*++p || (p = *++av))
				ip->sepstring = p;
			else
				error("Need string after -%s", c);
			S = (*c == 'S' ? 1 : 0);
			break;
I 2
		case 't':
			if (*++p || (p = *++av))
				ip->eol = *p;
			else
				error("Need character after -%s", c);
			T = (*c == 'T' ? 1 : 0);
			nofinalnl = 1;
			break;
E 2
		case 'p':
			ip->pad = 1;
			P = (*c == 'P' ? 1 : 0);
		case 'f':
			F = (*c == 'F' ? 1 : 0);
			if (*++p || (p = *++av)) {
D 5
				fmtp += strlen(fmtp);
E 5
I 5
				fmtp += strlen(fmtp) + 1;
E 5
				if (fmtp > fmtbuf + BUFSIZ)
					error("No more format space", "");
				sprintf(fmtp, "%%%ss", p);
				ip->format = fmtp;
			}
			else
				error("Need string after -%s", c);
			break;
		default:
			error("What do you mean by -%s?", c);
			break;
		}
	}
	ip->fp = NULL;
I 3
	if (!ip->sepstring)
		ip->sepstring = "";
E 3
}

D 6
char	*
E 6
I 6
char *
E 6
I 5
pad(ip)
D 6
struct	openfile	*ip;
E 6
I 6
	struct openfile *ip;
E 6
{
D 6
	register char	*p = ip->sepstring;
	register char	*lp = linep;
E 6
I 6
	register char *p = ip->sepstring;
	register char *lp = linep;
E 6

	while (*p)
		*lp++ = *p++;
	if (ip->pad) {
		sprintf(lp, ip->format, "");
		lp += strlen(lp);
	}
D 6
	return(lp);
E 6
I 6
	return (lp);
E 6
}

D 6
char	*
E 6
I 6
char *
E 6
E 5
gatherline(ip)
D 6
struct	openfile	*ip;
E 6
I 6
	struct openfile *ip;
E 6
{
D 6
	char	s[BUFSIZ];
	register int	c;
	register char	*p;
	register char	*lp = linep;
	char	*end = s + BUFSIZ;
E 6
I 6
	char s[BUFSIZ];
	register int c;
	register char *p;
	register char *lp = linep;
	char *end = s + BUFSIZ;
E 6

D 5
	if (ip->eof) {
		p = ip->sepstring;
		while (*p)
			*lp++ = *p++;
		if (ip->pad) {
			sprintf(lp, ip->format, "");
			lp += strlen(lp);
		}
		return(lp);
	}
E 5
I 5
	if (ip->eof)
D 6
		return(pad(ip));
E 6
I 6
		return (pad(ip));
E 6
E 5
	for (p = s; (c = fgetc(ip->fp)) != EOF && p < end; p++)
D 2
		if ((*p = c) == '\n')
E 2
I 2
		if ((*p = c) == ip->eol)
E 2
			break;
	*p = '\0';
D 5
	p = ip->sepstring;
	while (*p)
		*lp++ = *p++;
	sprintf(lp, ip->format, s);
	lp += strlen(lp);
E 5
	if (c == EOF) {
		ip->eof = 1;
		if (ip->fp == stdin)
			fclose(stdin);
		morefiles--;
I 5
D 6
		return(pad(ip));
E 6
I 6
		return (pad(ip));
E 6
E 5
	}
I 5
	p = ip->sepstring;
	while (*p)
		*lp++ = *p++;
	sprintf(lp, ip->format, s);
	lp += strlen(lp);
E 5
D 6
	return(lp);
E 6
I 6
	return (lp);
E 6
}

I 6
void
E 6
error(msg, s)
D 6
char	*msg;
char	*s;
E 6
I 6
	char *msg, *s;
E 6
{
D 6
	char	buf[BUFSIZ];

	setbuf(stderr, buf);
E 6
	fprintf(stderr, "lam: ");
	fprintf(stderr, msg, s);
D 2
	fprintf(stderr, "\nUsage:  lam [ -[fp] min.max ] [ -s sepstring ] file ...\n");
E 2
I 2
D 6
	fprintf(stderr, "\nUsage:  lam [ -[fp] min.max ] [ -s sepstring ] [ -t c ] file ...\n");
E 6
I 6
	fprintf(stderr,
"\nUsage:  lam [ -[fp] min.max ] [ -s sepstring ] [ -t c ] file ...\n");
E 6
E 2
	if (strncmp("lam - ", msg, 6) == 0)
D 2
		fprintf(stderr, "Options:\n\t%s\t%s\t%s",
E 2
I 2
		fprintf(stderr, "Options:\n\t%s\t%s\t%s\t%s\t%s",
E 2
D 6
			"-f min.max	field widths for file fragments\n",
			"-p min.max	like -f, but pad missing fragments\n",
D 2
			"-s sepstring	fragment separator\n");
E 2
I 2
			"-s sepstring	fragment separator\n",
			"-t c		input line terminator is c, no \\n after output lines\n",
			"Capitalized options affect more than one file.\n");
E 6
I 6
		    "-f min.max	field widths for file fragments\n",
		    "-p min.max	like -f, but pad missing fragments\n",
		    "-s sepstring	fragment separator\n",
"-t c		input line terminator is c, no \\n after output lines\n",
		    "Capitalized options affect more than one file.\n");
E 6
E 2
	exit(1);
}
E 1
