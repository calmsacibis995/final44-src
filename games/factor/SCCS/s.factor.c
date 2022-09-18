h39678
s 00001/00000/00175
d D 8.4 95/05/04 15:27:34 bostic 9 8
c optarg/optind moved to unistd.h
e
s 00003/00003/00172
d D 8.3 94/03/30 13:20:43 bostic 8 7
c lint, ubig is an unsigned long
e
s 00079/00225/00096
d D 8.2 94/03/21 07:22:57 bostic 7 6
c use the C library routines for conversion
e
s 00005/00005/00316
d D 8.1 93/05/31 16:52:59 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00312
d D 4.5 93/05/15 18:52:31 torek 5 4
c avoid gcc warning, and fix a bug in the process (serendipity)
e
s 00001/00011/00319
d D 4.4 90/06/01 12:49:15 bostic 4 3
c new copyright notice
e
s 00006/00006/00324
d D 4.3 90/02/02 16:31:59 bostic 3 2
c updated comments from Chongo
e
s 00296/00066/00034
d D 4.2 90/02/01 10:22:55 bostic 2 1
c new version from Landon Curt Noll
e
s 00100/00000/00000
d D 4.1 83/06/13 00:57:39 sam 1 0
c date and time created 83/06/13 00:57:39 by sam
e
u
U
t
T
I 2
/*
D 6
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Landon Curt Noll.
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W% (Wollongong) %G%";
#endif
E 2
I 2
D 6
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
#endif /* not lint */
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

E 2
/*
D 2
 *              factor [ number ]
E 2
I 2
 * factor - factor a number into primes
E 2
 *
D 2
 * Written to replace factor.s in Bell V7 distribution
E 2
I 2
 * By: Landon Curt Noll   chongo@toad.com,   ...!{sun,tolsoft}!hoptoad!chongo
 *
 *   chongo <for a good prime call: 391581 * 2^216193 - 1> /\oo/\
 *
 * usage:
 *	factor [number] ...
 *
D 3
 * With no args, reads numbers from stdin and factors them.
 * With 1 or more args, factors such args.  Factors are printed
 * in assending order, with a leading tab, one per line.
E 3
I 3
 * The form of the output is:
E 3
 *
D 3
 * When more than one arg is supplied, the argument value, left
 * justified is printed before the set of factors.  This is not
 * one for reading values from input for historical reasons.
E 3
I 3
 *	number: factor1 factor1 factor2 factor3 factor3 factor3 ...
 *
 * where factor1 < factor2 < factor3 < ...
 *
 * If no args are given, the list of numbers are read from stdin.
E 3
E 2
 */

I 7
#include <err.h>
E 7
I 2
D 5
#include <stdio.h>
E 5
#include <ctype.h>
I 7
#include <errno.h>
E 7
I 5
#include <limits.h>
#include <stdio.h>
I 7
#include <stdlib.h>
I 9
#include <unistd.h>
E 9

E 7
E 5
#include "primes.h"

/*
 * prime[i] is the (i-1)th prime.
 *
 * We are able to sieve 2^32-1 because this byte table yields all primes 
 * up to 65537 and 65537^2 > 2^32-1.
 */
extern ubig prime[];
D 7
extern ubig *pr_limit;	/* largest prime in the prime array */
E 7
I 7
extern ubig *pr_limit;		/* largest prime in the prime array */
E 7

D 7
#define MAX_LINE 255	/* max line allowed on stdin */
E 7
I 7
void	pr_fact __P((ubig));	/* print factors of a value */
void	usage __P((void));
E 7

D 7
void pr_fact();		/* print factors of a value */
long small_fact();	/* find smallest factor of a value */
char *read_num_buf();	/* read a number buffer */
char *program;		/* name of this program */

E 7
I 7
int
E 7
E 2
main(argc, argv)
D 2
char	*argv[];
E 2
I 2
D 7
	int argc;	/* arg count */
	char *argv[];	/* the args */
E 7
I 7
	int argc;
	char *argv[];
E 7
E 2
{
D 2
	int	n;
E 2
I 2
D 7
	int arg;	/* which arg to factor */
	long val;	/* the value to factor */
	char buf[MAX_LINE+1];	/* input buffer */
E 7
I 7
	ubig val;
	int ch;
	char *p, buf[100];		/* > max number of digits. */
E 7
E 2

I 2
D 7
	/* parse args */
	program = argv[0];
E 2
	if (argc >= 2) {
D 2
		sscanf(argv[1], "%d", &n);
		if (n > 0)
			printfactors(n);
E 2
I 2

		/* factor each arg */
		for (arg=1; arg < argc; ++arg) {

			/* process the buffer */
			if (read_num_buf(NULL, argv[arg]) == NULL) {
				fprintf(stderr, "%s: ouch\n", program);
				exit(1);
			}

			/* factor the argument */
			if (sscanf(argv[arg], "%ld", &val) == 1) {
				pr_fact(val);
			} else {
				fprintf(stderr, "%s: ouch\n", program);
				exit(1);
			}
E 7
I 7
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch (ch) {
		case '?':
		default:
			usage();
E 7
		}
I 7
	argc -= optind;
	argv += optind;
E 7

D 7
	/* no args supplied, read numbers from stdin */
E 2
	} else {
D 2
		while (scanf("%d", &n) == 1)
			if (n > 0)
				printfactors(n);
E 2
I 2
		/*
		 * read asciii numbers from input
		 */
		while (read_num_buf(stdin, buf) != NULL) {

			/* factor the argument */
			if (sscanf(buf, "%ld", &val) == 1) {
				pr_fact(val);
E 7
I 7
	/* No args supplied, read numbers from stdin. */
	if (argc == 0)
		for (;;) {
			if (fgets(buf, sizeof(buf), stdin) == NULL) {
				if (ferror(stdin))
					err(1, "stdin");
				exit (0);
E 7
			}
I 7
			for (p = buf; isblank(*p); ++p);
			if (*p == '\n' || *p == '\0')
				continue;
			if (*p == '-')
				errx(1, "negative numbers aren't permitted.");
			errno = 0;
			val = strtoul(buf, &p, 10);
			if (errno)
				err(1, "%s", buf);
			if (*p != '\n')
				errx(1, "%s: illegal numeric format.", buf);
			pr_fact(val);
E 7
		}
E 2
D 7
	}
E 7
I 7
	/* Factor the arguments. */
	else
		for (; *argv != NULL; ++argv) {
			if (argv[0][0] == '-')
				errx(1, "negative numbers aren't permitted.");
			errno = 0;
			val = strtoul(argv[0], &p, 10);
			if (errno)
				err(1, "%s", argv[0]);
			if (*p != '\0')
				errx(1, "%s: illegal numeric format.", argv[0]);
			pr_fact(val);
		}
E 7
I 2
	exit(0);
E 2
}

/*
D 2
 * Print all prime factors of integer n > 0, smallest first, one to a line
E 2
I 2
D 7
 * read_num_buf - read a number buffer from a stream
 *
 * Read a number on a line of the form:
 *
 *	^[ \t]*\([+-]?[0-9][0-9]\)*.*$
 *
 * where ? is a 1-or-0 operator and the number is within \( \).
 *
 * If does not match the above pattern, it is ignored and a new
 * line is read.  If the number is too large or small, we will
 * print ouch and read a new line.
 *
 * We have to be very careful on how we check the magnitude of the
 * input.  We can not use numeric checks because of the need to
 * check values against maximum numeric values.
 *
 * This routine will return a line containing a ascii number between
 * NEG_SEMIBIG and SEMIBIG, or it will return NULL.
 *
 * If the stream is NULL then buf will be processed as if were
 * a single line stream.
 *
 * returns:
 *	char *	pointer to leading digit, + or -
 *	NULL	EOF or error
E 2
 */
D 2
printfactors(n)
	register int	n;
E 2
I 2
char *
read_num_buf(input, buf)
	FILE *input;		/* input stream or NULL */
	char *buf;		/* input buffer */
E 2
{
D 2
	register int	prime;
E 2
I 2
	static char limit[MAX_LINE+1];	/* ascii value of SEMIBIG */
	static int limit_len;		/* digit count of limit */
	static char neg_limit[MAX_LINE+1];	/* value of NEG_SEMIBIG */
	static int neg_limit_len;		/* digit count of neg_limit */
	int len;			/* digits in input (excluding +/-) */
	char *s;	/* line start marker */
	char *d;	/* first digit, skip +/- */
	char *p;	/* scan pointer */
	char *z;	/* zero scan pointer */
E 2

D 2
	if (n == 1)
		printf("\t1\n");
	else while (n != 1) {
		prime = factor(n);
		printf("\t%d\n", prime);
		n /= prime;
E 2
I 2
	/* form the ascii value of SEMIBIG if needed */
	if (!isascii(limit[0]) || !isdigit(limit[0])) {
		sprintf(limit, "%ld", SEMIBIG);
		limit_len = strlen(limit);
		sprintf(neg_limit, "%ld", NEG_SEMIBIG);
		neg_limit_len = strlen(neg_limit)-1;	/* exclude - */
E 2
	}
D 2
}
E 2
I 2
	
	/*
	 * the search for a good line
	 */
	if (input != NULL && fgets(buf, MAX_LINE, input) == NULL) {
		/* error or EOF */
		return NULL;
	}
	do {
E 2

D 2
/*
 * Return smallest prime factor of integer N > 0
 *
 * Algorithm from E.W. Dijkstra (A Discipline of Programming, Chapter 20)
 */
E 2
I 2
		/* ignore leading whitespace */
		for (s=buf; *s && s < buf+MAX_LINE; ++s) {
			if (!isascii(*s) || !isspace(*s)) {
				break;
			}
		}
E 2

D 2
int
factor(N)
	int	N;
{
	int		p;
	register int	f;
	static struct {
		int	hib;
		int	val[24];
	} ar;
E 2
I 2
		/* skip over any leading + or - */
		if (*s == '+' || *s == '-') {
			d = s+1;
		} else {
			d = s;
		}
E 2

D 2
	{	register int	x, y;
E 2
I 2
		/* note leading zeros */
		for (z=d; *z && z < buf+MAX_LINE; ++z) {
			if (*z != '0') {
				break;
			}
		}
E 2

D 2
		ar.hib = -1;
		x = N; y = 2;
		while (x != 0) {
			ar.val[++ar.hib] = x % y;
			x /= y;
			y += 1;
E 2
I 2
		/* scan for the first non-digit */
		for (p=d; *p && p < buf+MAX_LINE; ++p) {
			if (!isascii(*p) || !isdigit(*p)) {
				break;
			}
E 2
		}
D 2
	}
E 2

D 2
	f = 2;
E 2
I 2
		/* ignore empty lines */
		if (p == d) {
			continue;
		}
		*p = '\0';
E 2

D 2
	while (ar.val[0] != 0 && ar.hib > 1) {
		register int	i;
E 2
I 2
		/* object if too many digits */
		len = strlen(z);
		len = (len<=0) ? 1 : len;
		if (*s == '-') {
			/* accept if digit count is below limit */
			if (len < neg_limit_len) {
				/* we have good input */
				return s;
E 2

D 2
		f += 1;
		i = 0;
		while (i != ar.hib) {
			register int	j;
E 2
I 2
			/* reject very large numbers */
			} else if (len > neg_limit_len) {
				fprintf(stderr, "%s: ouch\n", program);
				exit(1);
E 2

D 2
			j = i + 1;
			ar.val[i] -= j * ar.val[j];
			while (ar.val[i] < 0) {
				ar.val[i] += f + i;
				ar.val[j] -= 1;
E 2
I 2
			/* carefully check against near limit numbers */
			} else if (strcmp(z, neg_limit+1) > 0) {
				fprintf(stderr, "%s: ouch\n", program);
				exit(1);
E 2
			}
D 2
			i = j;
E 2
I 2
			/* number is near limit, but is under it */
			return s;
		
		} else {
			/* accept if digit count is below limit */
			if (len < limit_len) {
				/* we have good input */
				return s;

			/* reject very large numbers */
			} else if (len > limit_len) {
				fprintf(stderr, "%s: ouch\n", program);
				exit(1);

			/* carefully check against near limit numbers */
			} else if (strcmp(z, limit) > 0) {
				fprintf(stderr, "%s: ouch\n", program);
				exit(1);
			}
			/* number is near limit, but is under it */
			return s;
E 2
		}
D 2
		while (ar.val[ar.hib] == 0)
			ar.hib--;
E 2
I 2
	} while (input != NULL && fgets(buf, MAX_LINE, input) != NULL);

	/* error or EOF */
	return NULL;
}


/*
E 7
 * pr_fact - print the factors of a number
 *
 * If the number is 0 or 1, then print the number and return.
 * If the number is < 0, print -1, negate the number and continue
 * processing.
 *
 * Print the factors of the number, from the lowest to the highest.
 * A factor will be printed numtiple times if it divides the value
 * multiple times.
 *
 * Factors are printed with leading tabs.
 */
void
pr_fact(val)
D 7
	long val;	/* factor this value */
E 7
I 7
	ubig val;		/* Factor this value. */
E 7
{
D 7
	ubig *fact;	/* the factor found */
E 7
I 7
	ubig *fact;		/* The factor found. */
E 7

D 7
	/* firewall - catch 0 and 1 */
	switch (val) {
D 5
	case -2147483648:
		/* avoid negation problems */
		puts("-2147483648: -1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2\n");
		return;
E 5
I 5
	case LONG_MIN:
		/* avoid negation problems - assumes LONG_MIN is even  XXX */
		printf("%ld: -1 2", val);
		val /= -2;
		break;
E 5
	case -1:
		puts("-1: -1\n");
		return;
	case 0:
E 7
I 7
	/* Firewall - catch 0 and 1. */
	if (val == 0)		/* Historical practice; 0 just exits. */
E 7
		exit(0);
D 7
	case 1:
		puts("1: 1\n");
E 7
I 7
	if (val == 1) {
		(void)printf("1: 1\n");
E 7
		return;
D 7
	default:
		if (val < 0) {
			val = -val;
			printf("%ld: -1", val);
D 5
		} else {
E 5
I 5
		} else
E 5
			printf("%ld:", val);
D 5
		}
		fflush(stdout);
E 5
		break;
E 7
E 2
	}
I 5
D 7
	fflush(stdout);
E 7
E 5

D 2
	if (ar.val[0] == 0)
		p = f;
	else
		p = N;
E 2
I 2
D 7
	/*
	 * factor value
	 */
	fact = &prime[0];
	while (val > 1) {
E 2

D 2
	return(p);
E 2
I 2
		/* look for the smallest factor */
E 7
I 7
	/* Factor value. */
D 8
	(void)printf("%ld:", val);
E 8
I 8
	(void)printf("%lu:", val);
E 8
	for (fact = &prime[0]; val > 1; ++fact) {
		/* Look for the smallest factor. */
E 7
		do {
D 7
			if (val%(long)*fact == 0) {
E 7
I 7
			if (val % (long)*fact == 0)
E 7
				break;
D 7
			}
E 7
		} while (++fact <= pr_limit);

D 7
		/* watch for primes larger than the table */
E 7
I 7
		/* Watch for primes larger than the table. */
E 7
		if (fact > pr_limit) {
D 7
			printf(" %ld\n", val);
			return;
E 7
I 7
D 8
			(void)printf(" %ld", val);
E 8
I 8
			(void)printf(" %lu", val);
E 8
			break;
E 7
		}

D 7
		/* divide factor out until none are left */
E 7
I 7
		/* Divide factor out until none are left. */
E 7
		do {
D 7
			printf(" %ld", *fact);
E 7
I 7
D 8
			(void)printf(" %ld", *fact);
E 8
I 8
			(void)printf(" %lu", *fact);
E 8
E 7
			val /= (long)*fact;
		} while ((val % (long)*fact) == 0);
D 7
		fflush(stdout);
		++fact;
E 7
I 7

		/* Let the user know we're doing something. */
		(void)fflush(stdout);
E 7
	}
D 7
	putchar('\n');
	return;
E 7
I 7
	(void)putchar('\n');
}

void
usage()
{
	(void)fprintf(stderr, "usage: factor [value ...]\n");
	exit (0);
E 7
E 2
}
E 1
