h60224
s 00002/00001/00264
d D 8.3 95/05/04 15:28:32 bostic 10 9
c optarg/optind moved to unistd.h
e
s 00159/00111/00106
d D 8.2 94/03/31 07:37:15 bostic 9 8
c KNF, add the -l flag for shell scripts
e
s 00005/00005/00212
d D 8.1 93/05/31 17:30:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00217
d D 5.1 91/02/28 14:21:47 bostic 7 6
c ANSI
e
s 00001/00011/00221
d D 4.6 90/06/01 13:11:27 bostic 6 5
c new copyright notice
e
s 00010/00005/00222
d D 4.5 88/06/27 16:35:17 bostic 5 4
c install approved copyright notice
e
s 00017/00005/00210
d D 4.4 87/11/30 15:09:22 bostic 4 3
c Berkeley code, add copyright
e
s 00182/00171/00033
d D 4.3 87/04/02 20:12:40 bostic 3 2
c it would be difficult to explain.  complete rewrite.
e
s 00006/00004/00198
d D 4.2 86/11/26 13:52:10 bostic 2 1
c bug report 4.3BSD/games/4
e
s 00202/00000/00000
d D 4.1 82/10/24 18:26:36 mckusick 1 0
c date and time created 82/10/24 18:26:36 by mckusick
e
u
U
t
T
I 3
/*
D 4
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
D 8
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 8
I 8
D 9
 * Copyright (c) 1988, 1993
E 9
I 9
 * Copyright (c) 1988, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 6
 * Redistribution and use in source and binary forms are permitted
D 5
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific written prior permission. This software
 * is provided ``as is'' without express or implied warranty.
E 5
I 5
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
E 5
E 4
 */
E 3
I 1

I 3
#ifndef lint
E 3
D 4
static char sccsid[] = "	%M%	%I%	%E%	";
I 3
#endif
E 4
I 4
D 8
char copyright[] =
"%Z% Copyright (c) 1988 Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
D 9
"%Z% Copyright (c) 1988, 1993\n\
E 9
I 9
"%Z% Copyright (c) 1988, 1993, 1994\n\
E 9
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 3

I 2
D 9
#include <stdio.h>
E 9
I 9
#include <sys/types.h>

E 9
I 3
#include <ctype.h>
I 10
#include <err.h>
E 10
I 9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
D 10
#include <err.h>
E 10
I 10
#include <unistd.h>
E 10
E 9
E 3

E 2
D 3
int	flag;
int max = 21;
char	*card[] =
{
	"hundred",
	"thousand",
	"million",
	"billion",
	"trillion",
	"quadrillion",
	"quintillion",
	"sextillion",
	"septillion",
	"octillion",
	"nonillion",
	"decillion",
	"undecillion",
	"duodecillion",
	"tredecillion",
	"quattuordecillion",
	"quindecillion",
	"sexdecillion",
	"septendecillion",
	"octodecillion",
	"novemdecillion",
	"vigintillion"
E 3
I 3
D 9
#define	YES		1
#define	NO		0
#define	EOS		'\0'
#define	MAXNUM		65		/* biggest number we handle */
E 9
I 9
#define	MAXNUM		65		/* Biggest number we handle. */
E 9

static char	*name1[] = {
	"",		"one",		"two",		"three",
	"four",		"five",		"six",		"seven",
	"eight",	"nine",		"ten",		"eleven",
	"twelve",	"thirteen",	"fourteen",	"fifteen",
	"sixteen",	"seventeen",	"eighteen",	"nineteen",
},
		*name2[] = {
	"",		"ten",		"twenty",	"thirty",
	"forty",	"fifty",	"sixty",	"seventy",
	"eighty",	"ninety",
},
		*name3[] = {
	"hundred",	"thousand",	"million",	"billion",
	"trillion",	"quadrillion",	"quintillion",	"sextillion",
	"septillion",	"octillion",	"nonillion",	"decillion",
	"undecillion",	"duodecillion",	"tredecillion",	"quattuordecillion",
	"quindecillion",		"sexdecillion",	
	"septendecillion",		"octodecillion",
	"novemdecillion",		"vigintillion",
E 3
};
D 3
char *unit[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};
char *teen[] = {
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen"
};
char *decade[] = {
	"zero",
	"ten",
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety"
};
char	line[100];
main()
E 3
I 3

D 9
main(argc,argv)
	int	argc;
	char	**argv;
E 9
I 9
void	convert __P((char *));
int	number __P((char *, int));
void	pfract __P((int));
void	toobig __P((void));
int	unit __P((int, char *));
void	usage __P((void));

int lflag;

int
main(argc, argv)
	int argc;
	char *argv[];
E 9
E 3
{
D 3
	register c, i, fraction;
	int r;
E 3
I 3
D 9
	register int	cnt;
	char	line[MAXNUM * 2 + 2];		/* MAXNUM '.' MAXNUM '\0' */
E 9
I 9
	int ch, first;
	char line[256];
E 9
E 3

D 3

	fraction = 0;
D 2
	while(c = getchar()) {
E 2
I 2
	while((c = getchar()) != EOF) {
E 2
		if(!digit(c))  {
			fraction = (c == '.');
			putchar(c);
			continue;
E 3
I 3
D 9
	if (argc > 1)
		for (cnt = 1;cnt < argc;++cnt) {
			convert(argv[cnt]);
			puts("...");
E 9
I 9
	lflag = 0;
	while ((ch = getopt(argc, argv, "l")) != EOF)
		switch (ch) {
		case 'l':
			lflag = 1;
			break;
		case '?':
		default:
			usage();
E 9
E 3
		}
D 3
		if(fraction) {
			while(digit(c)) {
				putchar(' ');
				putchar(c);
D 2
				if(!(c=getchar()))
E 2
I 2
				if((c=getchar()) == EOF)
E 2
					exit(1);
			}
			putchar(' ');
			goto out;
E 3
I 3
D 9
	else
		while (fgets(line,sizeof(line),stdin)) {
E 9
I 9
	argc -= optind;
	argv += optind;

	if (*argv == NULL)
		for (first = 1;
		    fgets(line, sizeof(line), stdin) != NULL; first = 0) {
			if (strchr(line, '\n') == NULL)
				errx(1, "line too long.");
			if (!first)
				(void)printf("...\n");
E 9
			convert(line);
D 9
			puts("...");
E 9
E 3
		}
I 9
	else
		for (first = 1; *argv != NULL; first = 0, ++argv) {
			if (!first)
				(void)printf("...\n");
			convert(*argv);
		}
E 9
D 3

		putchar(' ');
		i = 0;
		line[i++] = '0';
		line[i++] = '0';
		while(c == '0')
D 2
			if(!(c=getchar()))
E 2
I 2
			if((c=getchar()) == EOF)
E 2
				exit(1);
		while(digit(c)) {
			if(i < 98)
				line[i++] = c;
D 2
			if(!(c=getchar()))
E 2
I 2
			if((c=getchar()) == EOF)
E 2
				exit(1);
		}
		line[i] = 0;
		r = i/3;
		if(r == 0) {
			print("zero");
			goto out;
		}
		conv(line+i-3*r, r);

out:
		fraction = (c == '.');
		nline();
		printf("...\n");
		if(c != '\n')
			putchar(c);
	}
E 3
I 3
	exit(0);
E 3
}

I 9
void
E 9
D 3
conv(p, c)
char *p;
E 3
I 3
D 7
static
E 7
convert(line)
D 9
	char	*line;
E 9
I 9
	char *line;
E 9
E 3
{
I 3
D 9
	register int	len,
			ret;
	register char	*C,
			*fraction;
E 9
I 9
	register flen, len, rval;
	register char *p, *fraction;
E 9
E 3

D 3
	if(c > max) {
		conv(p, c-max);
		print(card[max]);
		nline();
		p += (c-max)*3;
		c = max;
E 3
I 3
D 9
	for (fraction = NULL, C = line;*C && *C != '\n';++C)
		if (!isdigit(*C))
			switch(*C) {
			case '-':
				if (C != line)
					usage(NO);
				break;
			case '.':
				if (!fraction) {
					fraction = C + 1;
					*C = EOS;
					break;
				}
			default:
				usage(NO);
E 9
I 9
	fraction = NULL;
	for (p = line; *p != '\0' && *p != '\n'; ++p) {
		if (isblank(*p)) {
			if (p == line) {
				++line;
				continue;
E 9
			}
D 9
	*C = EOS;
E 9
I 9
			goto badnum;
		}
		if (isdigit(*p))
			continue;
		switch (*p) {
		case '.':
			if (fraction != NULL)
				goto badnum;
			fraction = p + 1;
			*p = '\0';
			break;
		case '-':
			if (p == line)
				break;
			/* FALLTHROUGH */
		default:
badnum:			errx(1, "illegal number: %s", line);
			break;
		}
	}
	*p = '\0';

	if ((len = strlen(line)) > MAXNUM ||
	    fraction != NULL && (flen = strlen(fraction)) > MAXNUM)
		errx(1, "number too large, max %d digits.", MAXNUM);

E 9
	if (*line == '-') {
D 9
		puts("minus");
E 9
I 9
		(void)printf("minus%s", lflag ? " " : "\n");
E 9
		++line;
E 3
	}
D 3
	while(c > 1) {
		c--;
		conv(p, 1);
		cprint(card[c]);
		nline();
		p += 3;
E 3
I 3
D 9
	ret = NO;
	if (len = strlen(line)) {
		if (len > MAXNUM)
			usage(YES);
		ret = unit(len,line);
E 3
	}
D 3
	ones(p[0]);
	cprint(card[0]);
	tens(p);
	ones(p[2]);
E 3
I 3
	if (fraction && (len = strlen(fraction))) {
		if (len > MAXNUM)
			usage(YES);
		for (C = fraction;*C;++C)
			if (*C != '0') {
				if (ret)
					puts("and");
				if (unit(len,fraction)) {
					++ret;
					pfract(len);
E 9
I 9

	rval = len > 0 ? unit(len, line) : 0;
	if (fraction != NULL && flen != 0)
		for (p = fraction; *p != '\0'; ++p)
			if (*p != '0') {
				if (rval)
					(void)printf("%sand%s",
					    lflag ? " " : "",
					    lflag ? " " : "\n");
				if (unit(flen, fraction)) {
					if (lflag)
						(void)printf(" ");
					pfract(flen);
					rval = 1;
E 9
				}
				break;
			}
D 9
	}
	if (!ret)
		puts("zero.");
E 9
I 9
	if (!rval)
		(void)printf("zero%s", lflag ? "" : ".\n");
	if (lflag)
		(void)printf("\n");
E 9
E 3
}

D 3
ones(d)
E 3
I 3
D 7
static
E 7
D 9
unit(len,C)
	register int	len;
	register char	*C;
E 9
I 9
int
unit(len, p)
	register int len;
	register char *p;
E 9
E 3
{
D 3
	if(d=='0')
		return;
	print(unit[d-'0']);
}
E 3
I 3
D 9
	register int	off,
			ret;
E 9
I 9
	register int off, rval;
E 9
E 3

D 3
tens(p)
char *p;
{

	switch(p[1]) {

	case '0':
		return;

	case '1':
		print(teen[p[2]-'0']);
		p[2] = '0';
		return;
E 3
I 3
D 9
	ret = NO;
E 9
I 9
	rval = 0;
E 9
	if (len > 3) {
		if (len % 3) {
			off = len % 3;
			len -= off;
D 9
			if (number(C,off)) {
				ret = YES;
				printf(" %s.\n",name3[len / 3]);
E 9
I 9
			if (number(p, off)) {
				rval = 1;
				(void)printf(" %s%s",
				    name3[len / 3], lflag ? " " : ".\n");
E 9
			}
D 9
			C += off;
E 9
I 9
			p += off;
E 9
		}
D 9
		for (;len > 3;C += 3) {
E 9
I 9
		for (; len > 3; p += 3) {
E 9
			len -= 3;
D 9
			if (number(C,3)) {
				ret = YES;
				printf(" %s.\n",name3[len / 3]);
E 9
I 9
			if (number(p, 3)) {
				rval = 1;
				(void)printf(" %s%s",
				    name3[len / 3], lflag ? " " : ".\n");
E 9
			}
		}
E 3
	}
D 3

	print(decade[p[1]-'0']);
E 3
I 3
D 9
	if (number(C,len)) {
		puts(".");
		ret = YES;
E 9
I 9
	if (number(p, len)) {
		if (!lflag)
			(void)printf(".\n");
		rval = 1;
E 9
	}
D 9
	return(ret);
E 9
I 9
	return (rval);
E 9
E 3
}

D 3

digit(c)
E 3
I 3
D 7
static
E 7
D 9
number(C,len)
	register char	*C;
	int	len;
E 9
I 9
int
number(p, len)
	register char *p;
	int len;
E 9
E 3
{
I 3
D 9
	register int	val,
			ret;
E 9
I 9
	register int val, rval;
E 9
E 3

D 3
	if(c < '0' || c > '9')
		return(0);
	return(1);
E 3
I 3
D 9
	ret = 0;
	switch(len) {
E 9
I 9
	rval = 0;
	switch (len) {
E 9
	case 3:
D 9
		if (*C != '0') {
			++ret;
			printf("%s hundred",name1[*C - '0']);
E 9
I 9
		if (*p != '0') {
			rval = 1;
			(void)printf("%s hundred", name1[*p - '0']);
E 9
		}
D 9
		++C;
		/*FALLTHROUGH*/
E 9
I 9
		++p;
		/* FALLTHROUGH */
E 9
	case 2:
D 9
		val = (C[1] - '0') + (C[0] - '0') * 10;
E 9
I 9
		val = (p[1] - '0') + (p[0] - '0') * 10;
E 9
		if (val) {
D 9
			if (ret++)
				putchar(' ');
E 9
I 9
			if (rval)
				(void)printf(" ");
E 9
			if (val < 20)
D 9
				fputs(name1[val],stdout);
E 9
I 9
				(void)printf("%s", name1[val]);
E 9
			else {
D 9
				fputs(name2[val / 10],stdout);
E 9
I 9
				(void)printf("%s", name2[val / 10]);
E 9
				if (val % 10)
D 9
					printf("-%s",name1[val % 10]);
E 9
I 9
					(void)printf("-%s", name1[val % 10]);
E 9
			}
I 9
			rval = 1;
E 9
		}
		break;
	case 1:
D 9
		if (*C != '0') {
			++ret;
			fputs(name1[*C - '0'],stdout);
E 9
I 9
		if (*p != '0') {
			rval = 1;
			(void)printf("%s", name1[*p - '0']);
E 9
		}
	}
D 9
	return(ret);
E 9
I 9
	return (rval);
E 9
E 3
}

I 9
void
E 9
D 3
nline()
E 3
I 3
D 7
static
E 7
pfract(len)
D 9
	register int	len;
E 9
I 9
	int len;
E 9
E 3
{
I 3
D 9
	static char	*pref[] = { "", "ten-", "hundred-" };
E 9
I 9
	static char *pref[] = { "", "ten-", "hundred-" };
E 9
E 3

D 3
	if(flag)
		printf(".\n");
	flag = 0;
E 3
I 3
	switch(len) {
	case 1:
D 9
		puts("tenths.");
E 9
I 9
		(void)printf("tenths.\n");
E 9
		break;
	case 2:
D 9
		puts("hundredths.");
E 9
I 9
		(void)printf("hundredths.\n");
E 9
		break;
	default:
D 9
		printf("%s%sths.\n",pref[len % 3],name3[len / 3]);
E 9
I 9
		(void)printf("%s%sths.\n", pref[len % 3], name3[len / 3]);
		break;
E 9
	}
E 3
}

D 3
cprint(s)
E 3
I 3
D 7
static
E 7
D 9
usage(toobig)
	int	toobig;
E 9
I 9
void
usage()
E 9
E 3
{
D 3

	if(flag)
		print(s);
}

print(s)
{

	if(flag)
		printf(" ");
	printf(s);
	flag = 1;
E 3
I 3
D 9
	if (toobig)
		fprintf(stderr,"number: number too large, max %d digits.\n",MAXNUM);
	fputs("usage: number # ...\n",stderr);
	exit(-1);
E 9
I 9
	(void)fprintf(stderr, "usage: number [# ...]\n");
	exit(1);
E 9
E 3
}
E 1
