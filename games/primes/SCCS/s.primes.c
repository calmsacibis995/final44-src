h34102
s 00001/00000/00306
d D 8.5 95/05/10 06:01:35 bostic 10 9
c getopt and friends moved to <unistd.h>
e
s 00001/00001/00305
d D 8.4 94/03/21 07:22:18 bostic 9 8
c EOF isn't an error
e
s 00074/00145/00232
d D 8.3 94/03/21 07:01:06 bostic 8 7
c use the C library routines for conversion
e
s 00076/00083/00301
d D 8.2 94/03/01 06:25:23 bostic 7 6
c primes did not support numbers in the 2^31 - 2^32 range; redefine
c the upper limit, and change the %ld's to %lu's appears to fix it.
c From: Arne Juul <arnej@dsl.unit.no>
e
s 00005/00005/00379
d D 8.1 93/05/31 17:43:15 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00383
d D 5.4 90/06/01 13:13:36 bostic 5 4
c new copyright notice
e
s 00003/00004/00391
d D 5.3 90/02/02 16:32:02 bostic 4 3
c updated comments from Chongo
e
s 00349/00105/00046
d D 5.2 90/02/01 10:22:58 bostic 3 2
c new version from Landon Curt Noll
e
s 00013/00001/00138
d D 5.1 85/05/29 11:23:22 dist 2 1
c Add copyright
e
s 00139/00000/00000
d D 4.1 83/06/13 00:57:38 sam 1 0
c date and time created 83/06/13 00:57:38 by sam
e
u
U
t
T
I 2
/*
D 3
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
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
E 3
 */

E 2
I 1
#ifndef lint
I 2
D 6
char copyright[] =
D 3
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 3
I 3
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
E 3
 All rights reserved.\n";
E 6
I 6
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 6
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

#ifndef lint
E 2
D 3
static char sccsid[] = "%W% (Wollongong) %G%";
D 2
#endif
E 2
I 2
#endif not lint
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3
E 2

/*
D 3
 *	primes [ number ]
E 3
I 3
 * primes - generate a table of primes between two values
E 3
 *
D 3
 *	Print all primes greater than argument (or number read from stdin).
E 3
I 3
D 7
 * By: Landon Curt Noll   chongo@toad.com,   ...!{sun,tolsoft}!hoptoad!chongo
E 7
I 7
 * By: Landon Curt Noll chongo@toad.com, ...!{sun,tolsoft}!hoptoad!chongo
E 7
E 3
 *
D 3
 *	A free translation of 'primes.s'
E 3
I 3
D 7
 *   chongo <for a good prime call: 391581 * 2^216193 - 1> /\oo/\
E 7
I 7
 * chongo <for a good prime call: 391581 * 2^216193 - 1> /\oo/\
E 7
E 3
 *
I 3
 * usage:
 *	primes [start [stop]]
 *
D 4
 *	Print primes >= start and <= stop.  If stop is omitted,
E 4
I 4
 *	Print primes >= start and < stop.  If stop is omitted,
E 4
 *	the value 4294967295 (2^32-1) is assumed.  If start is
 *	omitted, start is read from standard input.
 *
D 4
 *	Prints "ouch" if start or stop is > 4294967295 (2^32-1)
 *	or if a non-numeric is read on stdin.
E 4
I 4
D 7
 *	Prints "ouch" if start or stop is bogus.
E 4
 *
E 7
D 4
 * Validation check: there are 664579 primes between 0 and 10^7
E 4
I 4
 * validation check: there are 664579 primes between 0 and 10^7
E 4
E 3
 */

I 8
#include <ctype.h>
E 8
D 7
#include <stdio.h>
E 7
I 7
#include <err.h>
#include <errno.h>
D 8
#include <ctype.h>
E 8
#include <limits.h>
E 7
#include <math.h>
I 3
#include <memory.h>
D 7
#include <ctype.h>
E 7
I 7
#include <stdio.h>
#include <stdlib.h>
I 10
#include <unistd.h>
E 10
I 8

E 8
E 7
#include "primes.h"
E 3

D 3
#define	TABSIZE	1000		/* size of sieve table */
#define	BIG	4294967296.	/* largest unsigned int */
E 3
I 3
/*
 * Eratosthenes sieve table
 *
 * We only sieve the odd numbers.  The base of our sieve windows are always
 * odd.  If the base of table is 1, table[i] represents 2*i-1.  After the
 * sieve, table[i] == 1 if and only iff 2*i-1 is prime.
 *
 * We make TABSIZE large to reduce the overhead of inner loop setup.
 */
char table[TABSIZE];	 /* Eratosthenes sieve of odd numbers */
E 3

D 3
char	table[TABSIZE];		/* table for sieve of Eratosthenes */
int	tabbits	= 8*TABSIZE;	/* number of bits in table */
E 3
I 3
/*
 * prime[i] is the (i-1)th prime.
 *
 * We are able to sieve 2^32-1 because this byte table yields all primes 
 * up to 65537 and 65537^2 > 2^32-1.
 */
extern ubig prime[];
extern ubig *pr_limit;		/* largest prime in the prime array */
E 3

D 3
float	fstart;
unsigned	start;			/* lowest number to test for prime */
char	bittab[] = {		/* bit positions (to save shifting) */
	01, 02, 04, 010, 020, 040, 0100, 0200
};
E 3
I 3
/*
 * To avoid excessive sieves for small factors, we use the table below to 
 * setup our sieve blocks.  Each element represents a odd number starting 
 * with 1.  All non-zero elements are factors of 3, 5, 7, 11 and 13.
 */
extern char pattern[];
extern int pattern_size;	/* length of pattern array */
E 3

D 3
unsigned pt[] =	{		/* primes < 100 */
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
	47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
};
E 3
I 3
D 7
#define MAX_LINE 255    /* max line allowed on stdin */
E 7
I 7
D 8
#define MAX_LINE 255		/* max line allowed on stdin */
E 8
I 8
void	primes __P((ubig, ubig));
ubig	read_num_buf __P((void));
void	usage __P((void));
E 8
E 7
E 3

D 3
unsigned factab[] = {		/* difference between succesive trial factors */
	10, 2, 4, 2, 4, 6, 2, 6, 4, 2, 4, 6, 6, 2, 6, 4,
	2, 6, 4, 6, 8, 4, 2, 4, 2, 4, 8, 6, 4, 6, 2, 4,
	6, 2, 6, 6, 4, 2, 4, 6, 2, 6, 4, 2, 4, 2, 10, 2
};
E 3
I 3
D 7
char *read_num_buf();	 /* read a number buffer */
void primes();		 /* print the primes in range */
char *program;		 /* our name */
E 7
I 7
D 8
void	 primes __P((ubig, ubig));
char	*read_num_buf __P((FILE *, char *));
void	 usage __P((void));
E 7
E 3

E 8
I 7
int
E 7
main(argc, argv)
D 3
int	argc;
char	**argv;
E 3
I 3
D 7
	int argc;	/* arg count */
	char *argv[];	/* args */
E 7
I 7
	int argc;
	char *argv[];
E 7
E 3
{
D 3
	register unsigned	*fp;
	register char	*p;
	register int	i;
	unsigned	quot;
	unsigned	factor, v;
E 3
I 3
D 7
	char buf[MAX_LINE+1];   /* input buffer */
	char *ret;	/* return result */
	ubig start;	/* where to start generating */
	ubig stop;	/* don't generate at or above this value */
E 7
I 7
	ubig start;		/* where to start generating */
	ubig stop;		/* don't generate at or above this value */
	int ch;
D 8
	char buf[MAX_LINE+1];	/* input buffer */
E 8
I 8
	char *p;
E 8
E 7
E 3

I 7
	while ((ch = getopt(argc, argv, "")) != EOF)
		switch (ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

E 7
D 3
	if (argc >= 2) {		/* get starting no. from arg */
		if (sscanf(argv[1], "%f", &fstart) != 1
		    || fstart < 0.0 || fstart >= BIG) {
			ouch();
E 3
I 3
D 8
	/*
	 * parse args
	 */
E 8
D 7
	program = argv[0];
E 7
	start = 0;
	stop = BIG;
D 7
	if (argc == 3) {
E 7
I 7
D 8
	if (argc == 2) {
E 7
		/* convert low and high args */
D 7
		if (read_num_buf(NULL, argv[1]) == NULL) {
			fprintf(stderr, "%s: ouch\n", program);
E 3
			exit(1);
		}
D 3
	} else {			/* get starting no. from stdin */
		while ((i = scanf("%f", &fstart)) != 1
		    || fstart < 0.0 || fstart >= BIG) {
			if (i == EOF)
E 3
I 3
		if (read_num_buf(NULL, argv[2]) == NULL) {
			fprintf(stderr, "%s: ouch\n", program);
			exit(1);
		}
		if (sscanf(argv[1], "%ld", &start) != 1) {
			fprintf(stderr, "%s: ouch\n", program);
			exit(1);
		}
		if (sscanf(argv[2], "%ld", &stop) != 1) {
			fprintf(stderr, "%s: ouch\n", program);
			exit(1);
		}

	} else if (argc == 2) {
E 7
I 7
		if (read_num_buf(NULL, argv[0]) == NULL)
			exit (1);
		if (sscanf(argv[0], "%lu", &start) != 1)
E 8
I 8

	/*
	 * Convert low and high args.  Strtoul(3) sets errno to
	 * ERANGE if the number is too large, but, if there's
	 * a leading minus sign it returns the negation of the
	 * result of the conversion, which we'd rather disallow.
	 */
	switch (argc) {
	case 2:
		/* Start and stop supplied on the command line. */
		if (argv[0][0] == '-' || argv[1][0] == '-')
			errx(1, "negative numbers aren't permitted.");

		errno = 0;
		start = strtoul(argv[0], &p, 10);
		if (errno)
E 8
			err(1, "%s", argv[0]);
D 8
		if (read_num_buf(NULL, argv[1]) == NULL)
			exit (1);
		if (sscanf(argv[1], "%lu", &stop) != 1)
E 8
I 8
		if (*p != '\0')
			errx(1, "%s: illegal numeric format.", argv[0]);

		errno = 0;
		stop = strtoul(argv[1], &p, 10);
		if (errno)
			err(1, "%s", argv[1]);
		if (*p != '\0')
			errx(1, "%s: illegal numeric format.", argv[1]);
		break;
	case 1:
		/* Start on the command line. */
		if (argv[0][0] == '-')
			errx(1, "negative numbers aren't permitted.");

		errno = 0;
		start = strtoul(argv[0], &p, 10);
		if (errno)
E 8
			err(1, "%s", argv[0]);
D 8
	} else if (argc == 1) {
E 7
		/* convert low arg */
D 7
		if (read_num_buf(NULL, argv[1]) == NULL) {
			fprintf(stderr, "%s: ouch\n", program);
			exit(1);
		}
		if (sscanf(argv[1], "%ld", &start) != 1) {
			fprintf(stderr, "%s: ouch\n", program);
			exit(1);
		}

E 7
I 7
		if (read_num_buf(NULL, argv[0]) == NULL)
			exit (1);
		if (sscanf(argv[0], "%lu", &start) != 1)
			err(1, "%s", argv[0]);
E 7
	} else {
		/* read input until we get a good line */
D 7
		if (read_num_buf(stdin, buf) != NULL) {

			/* convert the buffer */
			if (sscanf(buf, "%ld", &start) != 1) {
				fprintf(stderr, "%s: ouch\n", program);
E 3
				exit(1);
D 3
			ouch();
E 3
I 3
			}
		} else {
			exit(0);
E 3
		}
E 7
I 7
		if (read_num_buf(stdin, buf) == NULL)
			exit (1);
		if (sscanf(buf, "%lu", &start) != 1)
			err(1, "illegal value: %s", buf);
E 8
I 8
		if (*p != '\0')
			errx(1, "%s: illegal numeric format.", argv[0]);
		break;
	case 0:
		start = read_num_buf();
		break;
	default:
		usage();
E 8
E 7
	}
I 8

E 8
D 3
	start = (unsigned)fstart;

	/*
	 * Quick list of primes < 100
	 */
	if (start <= 97) {
		for (fp = pt; *fp < start; fp++)
			;
		do
			printf("%u\n", *fp);
		while (++fp < &pt[sizeof(pt) / sizeof(*pt)]);
		start = 100;
E 3
I 3
D 7
	if (start > stop) {
		fprintf(stderr, "%s: ouch\n", program);
		exit(1);
E 3
	}
E 7
I 7
	if (start > stop)
D 8
		errx(1, "start value > stop value");
E 8
I 8
		errx(1, "start value must be less than stop value.");
E 8
E 7
D 3
	quot = start/2;
	start = quot * 2 + 1;
E 3
I 3
	primes(start, stop);
	exit(0);
}
E 3

/*
D 3
 * Loop forever:
E 3
I 3
D 8
 * read_num_buf - read a number buffer from a stream
 *
 * Read a number on a line of the form:
 *
 *	^[ \t]*\(+?[0-9][0-9]\)*.*$
 *
 * where ? is a 1-or-0 operator and the number is within \( \).
 *
 * If does not match the above pattern, it is ignored and a new
 * line is read.  If the number is too large or small, we will
D 7
 * print ouch and read a new line.
E 7
I 7
 * object and read a new line.
E 7
 *
 * We have to be very careful on how we check the magnitude of the
 * input.  We can not use numeric checks because of the need to
 * check values against maximum numeric values.
 *
 * This routine will return a line containing a ascii number between
 * 0 and BIG, or it will return NULL.
 *
 * If the stream is NULL then buf will be processed as if were
 * a single line stream.
 *
 * returns:
 *	char *	pointer to leading digit or +
 *	NULL	EOF or error
E 8
I 8
 * read_num_buf --
 *	This routine returns a number n, where 0 <= n && n <= BIG.
E 8
E 3
 */
D 3
    for (;;) {
E 3
I 3
D 8
char *
read_num_buf(input, buf)
	FILE *input;		/* input stream or NULL */
	char *buf;		/* input buffer */
E 8
I 8
ubig
read_num_buf()
E 8
{
D 8
	static char limit[MAX_LINE+1];	/* ascii value of BIG */
	static int limit_len;		/* digit count of limit */
	int len;			/* digits in input (excluding +/-) */
	char *s;	/* line start marker */
	char *d;	/* first digit, skip +/- */
	char *p;	/* scan pointer */
	char *z;	/* zero scan pointer */
E 8
I 8
	ubig val;
	char *p, buf[100];		/* > max number of digits. */
E 8

D 7
	/* form the ascii value of SEMIBIG if needed */
E 7
I 7
D 8
	/* form the ascii value of BIG if needed */
E 7
	if (!isascii(limit[0]) || !isdigit(limit[0])) {
D 7
		sprintf(limit, "%ld", SEMIBIG);
E 7
I 7
		(void)sprintf(limit, "%lu", BIG);
E 7
		limit_len = strlen(limit);
	}
	
E 3
	/*
D 3
	 * Generate primes via sieve of Eratosthenes
E 3
I 3
	 * the search for a good line
E 3
	 */
D 3
	for (p = table; p < &table[TABSIZE]; p++)	/* clear sieve */
		*p = '\0';
	v = (unsigned)sqrt((float)(start + tabbits)); /* highest useful factor */
	sieve(3);
	sieve(5);
	sieve(7);
	factor = 11;
	fp = &factab[1];
	do {
		sieve(factor);
		factor += *fp;
		if (++fp >= &factab[sizeof(factab) / sizeof(*factab)])
			fp = factab;
	} while (factor <= v);
	/*
	 * Print generated primes
	 */
	for (i = 0; i < 8*TABSIZE; i += 2) {
		if ((table[i>>3] & bittab[i&07]) == 0)
			printf("%u\n", start);
		start += 2;
E 3
I 3
	if (input != NULL && fgets(buf, MAX_LINE, input) == NULL) {
		/* error or EOF */
D 7
		return NULL;
E 7
I 7
		return (NULL);
E 7
E 3
	}
D 3
    }
}
E 3
I 3
	do {
E 3

D 3
/*
 * Insert all multiples of given factor into the sieve
 */
sieve(factor)
unsigned factor;
{
	register int	i;
	unsigned	off;
	unsigned	quot;
E 3
I 3
		/* ignore leading whitespace */
		for (s=buf; *s && s < buf+MAX_LINE; ++s) {
			if (!isascii(*s) || !isspace(*s)) {
				break;
			}
E 8
I 8
	for (;;) {
		if (fgets(buf, sizeof(buf), stdin) == NULL) {
			if (ferror(stdin))
				err(1, "stdin");
D 9
			errx(1, "stdin: unexpected end-of-file.");
E 9
I 9
			exit(0);
E 9
E 8
		}
E 3
D 8

D 3
	quot = start / factor;
	off = (quot * factor) - start;
	if ((int)off < 0)
		off += factor;
	while (off < tabbits ) {
		i = (int)off;
		table[i>>3] |= bittab[i&07];
		off += factor;
	}
E 3
I 3
		/* object if - */
		if (*s == '-') {
D 7
			fprintf(stderr, "%s: ouch\n", program);
E 7
I 7
			(void)fprintf(stderr,
			    "primes: numbers can't be negative.\n");
E 8
I 8
		for (p = buf; isblank(*p); ++p);
		if (*p == '\n' || *p == '\0')
E 8
E 7
			continue;
D 8
		}

		/* skip over any leading + */
		if (*s == '+') {
			d = s+1;
		} else {
			d = s;
		}

		/* note leading zeros */
		for (z=d; *z && z < buf+MAX_LINE; ++z) {
			if (*z != '0') {
				break;
			}
		}

		/* scan for the first non-digit/non-plus/non-minus */
		for (p=d; *p && p < buf+MAX_LINE; ++p) {
			if (!isascii(*p) || !isdigit(*p)) {
				break;
			}
		}

		/* ignore empty lines */
		if (p == d) {
			continue;
		}
		*p = '\0';

		/* object if too many digits */
		len = strlen(z);
		len = (len<=0) ? 1 : len;
		/* accept if digit count is below limit */
		if (len < limit_len) {
			/* we have good input */
D 7
			return s;
E 7
I 7
			return (s);
E 7

D 7
		/* reject very large numbers */
		} else if (len > limit_len) {
			fprintf(stderr, "%s: ouch\n", program);
E 7
I 7
		/*
		 * reject very large numbers, carefully check against
		 * near limit numbers
		 */
		} else if (len > limit_len || strcmp(z, limit) > 0) {
			errno = ERANGE;
			warn("%s", z);
E 7
			continue;
D 7

		/* carefully check against near limit numbers */
		} else if (strcmp(z, limit) > 0) {
			fprintf(stderr, "%s: ouch\n", program);
			continue;
E 7
		}
		/* number is near limit, but is under it */
D 7
		return s;
E 7
I 7
		return (s);
E 7
	} while (input != NULL && fgets(buf, MAX_LINE, input) != NULL);

	/* error or EOF */
D 7
	return NULL;
E 7
I 7
	return (NULL);
E 8
I 8
		if (*p == '-')
			errx(1, "negative numbers aren't permitted.");
		errno = 0;
		val = strtoul(buf, &p, 10);
		if (errno)
			err(1, "%s", buf);
		if (*p != '\n')
			errx(1, "%s: illegal numeric format.", buf);
		return (val);
	}
E 8
E 7
E 3
}

/*
D 3
 * Error message
E 3
I 3
 * primes - sieve and print primes from start up to and but not including stop
E 3
 */
D 3
ouch()
E 3
I 3
void
primes(start, stop)
	ubig start;	/* where to start generating */
	ubig stop;	/* don't generate at or above this value */
E 3
{
D 3
	fprintf(stderr, "Ouch.\n");
E 3
I 3
	register char *q;		/* sieve spot */
	register ubig factor;		/* index and factor */
	register char *tab_lim;		/* the limit to sieve on the table */
	register ubig *p;		/* prime table pointer */
	register ubig fact_lim;		/* highest prime for current block */

	/*
D 7
	 * A number of systems can not convert double values 
	 * into unsigned longs when the values are larger than
	 * the largest signed value.  Thus we take case when
	 * the double is larger than the value SEMIBIG. *sigh*
E 7
I 7
	 * A number of systems can not convert double values into unsigned
	 * longs when the values are larger than the largest signed value.
	 * We don't have this problem, so we can go all the way to BIG.
E 7
	 */
	if (start < 3) {
		start = (ubig)2;
	}
	if (stop < 3) {
		stop = (ubig)2;
	}
	if (stop <= start) {
		return;
	}

	/*
	 * be sure that the values are odd, or 2
	 */
	if (start != 2 && (start&0x1) == 0) {
		++start;
	}
	if (stop != 2 && (stop&0x1) == 0) {
		++stop;
	}

	/*
	 * quick list of primes <= pr_limit
	 */
	if (start <= *pr_limit) {
		/* skip primes up to the start value */
		for (p = &prime[0], factor = prime[0];
D 7
		     factor < stop && p <= pr_limit; 
		     factor = *(++p)) {
E 7
I 7
		    factor < stop && p <= pr_limit; factor = *(++p)) {
E 7
			if (factor >= start) {
				printf("%u\n", factor);
			}
		}
		/* return early if we are done */
		if (p <= pr_limit) {
			return;
		}
		start = *pr_limit+2;
	}

	/*
	 * we shall sieve a bytemap window, note primes and move the window
	 * upward until we pass the stop point
	 */
	while (start < stop) {
		/*
		 * factor out 3, 5, 7, 11 and 13
		 */
		/* initial pattern copy */
		factor = (start%(2*3*5*7*11*13))/2; /* starting copy spot */
		memcpy(table, &pattern[factor], pattern_size-factor);
		/* main block pattern copies */
		for (fact_lim=pattern_size-factor;
D 7
		     fact_lim+pattern_size<=TABSIZE;
		     fact_lim+=pattern_size) {
E 7
I 7
		    fact_lim+pattern_size<=TABSIZE; fact_lim+=pattern_size) {
E 7
			memcpy(&table[fact_lim], pattern, pattern_size);
		}
		/* final block pattern copy */
		memcpy(&table[fact_lim], pattern, TABSIZE-fact_lim);

		/*
		 * sieve for primes 17 and higher
		 */
		/* note highest useful factor and sieve spot */
		if (stop-start > TABSIZE+TABSIZE) {
			tab_lim = &table[TABSIZE]; /* sieve it all */
			fact_lim = (int)sqrt(
					(double)(start)+TABSIZE+TABSIZE+1.0);
		} else {
			tab_lim = &table[(stop-start)/2]; /* partial sieve */
			fact_lim = (int)sqrt((double)(stop)+1.0);
		}
		/* sieve for factors >= 17 */
		factor = 17;	/* 17 is first prime to use */
		p = &prime[7];	/* 19 is next prime, pi(19)=7 */
		do {
			/* determine the factor's initial sieve point */
			q = (char *)(start%factor); /* temp storage for mod */
			if ((int)q & 0x1) {
				q = &table[(factor-(int)q)/2];
			} else {
				q = &table[q ? factor-((int)q/2) : 0];
			}
			/* sive for our current factor */
			for ( ; q < tab_lim; q += factor) {
				*q = '\0'; /* sieve out a spot */
			}
		} while ((factor=(ubig)(*(p++))) <= fact_lim);

		/*
		 * print generated primes
		 */
		for (q = table; q < tab_lim; ++q, start+=2) {
			if (*q) {
				printf("%u\n", start);
			}
		}
	}
I 7
}

void
usage()
{
D 8
	(void)fprintf(stderr, "usage: primes [start stop]\n");
E 8
I 8
	(void)fprintf(stderr, "usage: primes [start [stop]]\n");
E 8
	exit(1);
E 7
E 3
}
E 1
