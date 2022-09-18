h03909
s 00005/00005/00343
d D 8.1 93/05/31 15:58:45 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00348
d D 5.6 93/03/22 05:48:57 bostic 7 6
c lint
e
s 00002/00002/00347
d D 5.5 91/02/27 17:21:05 bostic 6 5
c ANSI fix
e
s 00001/00011/00348
d D 5.4 90/06/01 12:50:35 bostic 5 4
c new copyright notice
e
s 00001/00001/00358
d D 5.3 90/05/15 19:42:06 bostic 4 3
c string.h is ANSI C include file
e
s 00001/00008/00358
d D 5.2 89/09/13 08:58:50 bostic 3 2
c minor cleanups, don't check for divide by zero, range can't be zero
e
s 00319/00171/00047
d D 5.1 89/09/08 13:08:50 bostic 2 1
c new version from Eamonn McManus <emcmanus@cs.tcd.ie>
e
s 00218/00000/00000
d D 4.1 82/10/24 18:24:51 mckusick 1 0
c date and time created 82/10/24 18:24:51 by mckusick
e
u
U
t
T
I 2
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
 * Eamonn McManus of Trinity College Dublin.
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
E 2
I 1

D 2
static char sccsid[] = "	%M%	%I%	%E%	";
E 2
I 2
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
E 2

I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * By Eamonn McManus, Trinity College Dublin <emcmanus@cs.tcd.ie>.
 *
 * The operation of this program mimics that of the standard Unix game
 * `arithmetic'.  I've made it as close as I could manage without examining
 * the source code.  The principal differences are:
 *
 * The method of biasing towards numbers that had wrong answers in the past
 * is different; original `arithmetic' seems to retain the bias forever,
 * whereas this program lets the bias gradually decay as it is used.
 *
 * Original `arithmetic' delays for some period (3 seconds?) after printing
 * the score.  I saw no reason for this delay, so I scrapped it.
 *
 * There is no longer a limitation on the maximum range that can be supplied
 * to the program.  The original program required it to be less than 100.
 * Anomalous results may occur with this program if ranges big enough to
 * allow overflow are given.
 *
 * I have obviously not attempted to duplicate bugs in the original.  It
 * would go into an infinite loop if invoked as `arithmetic / 0'.  It also
 * did not recognise an EOF in its input, and would continue trying to read
 * after it.  It did not check that the input was a valid number, treating any
 * garbage as 0.  Finally, it did not flush stdout after printing its prompt,
 * so in the unlikely event that stdout was not a terminal, it would not work
 * properly.
 */

#include <sys/types.h>
#include <sys/signal.h>
#include <ctype.h>
E 2
#include <stdio.h>
D 2
#include <signal.h>
#define	MAX	100
E 2
I 2
D 4
#include <strings.h>
E 4
I 4
#include <string.h>
E 4
E 2

D 2
char	types[10];
int	right[MAX];
int	left[MAX];
int	rights;
int	wrongs;
long	stvec;
long	etvec;
long	dtvec;
E 2
I 2
char keylist[] = "+-x/";
char defaultkeys[] = "+-";
char *keys = defaultkeys;
int nkeys = sizeof(defaultkeys) - 1;
int rangemax = 10;
int nright, nwrong;
time_t qtime;
#define	NQUESTS	20
E 2

D 2
main(argc,argv)
char	*argv[];
E 2
I 2
/*
 * Select keys from +-x/ to be asked addition, subtraction, multiplication,
 * and division problems.  More than one key may be given.  The default is
 * +-.  Specify a range to confine the operands to 0 - range.  Default upper
 * bound is 10.  After every NQUESTS questions, statistics on the performance
 * so far are printed.
 */
void
main(argc, argv)
	int argc;
	char **argv;
E 2
{
D 2
	int range, k, dif, l;
	char line[100];
	int ans,pans,i,j,t;
	char	dir,sense;
	extern	delete();
E 2
I 2
	extern char *optarg;
	extern int optind;
	int ch, cnt;
D 7
	time_t time();
E 7
D 6
	sig_t intr();
E 6
I 6
	void intr();
E 6
E 2

D 2
	signal(SIGINT, delete);
E 2
I 2
	while ((ch = getopt(argc, argv, "r:o:")) != EOF)
		switch(ch) {
		case 'o': {
			register char *p;
E 2

D 2
	range = 11;
	dif = 0;
	while(argc > 1) {
		switch(*argv[1]) {
		case '+':
		case '-':
		case 'x':
		case '/':
			while(types[dif] = argv[1][dif])
				dif++;
E 2
I 2
			for (p = keys = optarg; *p; ++p)
				if (!index(keylist, *p)) {
					(void)fprintf(stderr,
					    "arithmetic: unknown key.\n");
					exit(1);
				}
			nkeys = p - optarg;
E 2
			break;
D 2

E 2
I 2
		}
		case 'r':
			if ((rangemax = atoi(optarg)) <= 0) {
				(void)fprintf(stderr,
				    "arithmetic: invalid range.\n");
				exit(1);
			}
			break;
		case '?':
E 2
		default:
D 2
			range = getnum(argv[1]) + 1;
E 2
I 2
			usage();
E 2
		}
D 2
		argv++;
		argc--;
	}
	if(range > MAX) {
		printf("Range is too large.\n");
		exit();
	}
E 2
I 2
	if (argc -= optind)
		usage();
E 2

D 2
	if(dif == 0) {
		types[0] = '+';
		types[1] = '-';
		dif = 2;
E 2
I 2
D 3
	/* Check for a case that would cause trouble: arithmetic / 0. */
	if (rangemax == 0 && index(keys, '/')) {
		(void)fprintf(stderr,
		    "arithmetic: you can't MAKE me divide by zero!\n");
		exit(1);
E 2
	}

E 3
D 2
	for(i = 0; i < range; i++) {
		left[i] = right[i] = i;
	}
	time(&stvec);
	k = stvec;
	srand(k);
	k = 0;
	l = 0;
	goto start;
E 2
I 2
	/* Seed the random-number generator. */
	srandom((int)time((time_t *)NULL));
E 2

D 2
loop:
	if(++k%20 == 0)
		score();
E 2
I 2
	(void)signal(SIGINT, intr);
E 2

D 2
start:
	i = skrand(range);
	j = skrand(range);
	if(dif > 1)
		l = random(dif);

	switch(types[l]) {
		case '+':
		default:
			ans = left[i] + right[j];
			printf("%d + %d =   ", left[i], right[j]);
			break;

		case '-':
			t = left[i] + right[j];
			ans = left[i];
			printf("%d - %d =   ", t, right[j]);
			break;

		case 'x':
			ans = left[i] * right[j];
			printf("%d x %d =   ", left[i], right[j]);
			break;

		case '/':
			while(right[j] == 0)
				j = random(range);
			t = left[i] * right[j] + random(right[j]);
			ans = left[i];
			printf("%d / %d =   ", t, right[j]);
			break;
E 2
I 2
	/* Now ask the questions. */
	for (;;) {
		for (cnt = NQUESTS; cnt--;)
			if (problem() == EOF)
				exit(0);
		showstats();
E 2
	}
I 2
	/* NOTREACHED */
}
E 2

I 2
/* Handle interrupt character.  Print score and exit. */
D 6
sig_t
E 6
I 6
void
E 6
intr()
{
	showstats();
	exit(0);
}
E 2

D 2
loop1:
	getline(line);
	dtvec += etvec - stvec;
	if(line[0]=='\n') goto loop1;
	pans = getnum(line);
	if(pans == ans) {
		printf("Right!\n");
		rights++;
		goto loop;
E 2
I 2
/* Print score.  Original `arithmetic' had a delay after printing it. */
showstats()
{
	if (nright + nwrong > 0) {
		(void)printf("\n\nRights %d; Wrongs %d; Score %d%%",
		    nright, nwrong, (int)(100L * nright / (nright + nwrong)));
		if (nright > 0)
	(void)printf("\nTotal time %ld seconds; %.1f seconds per problem\n\n",
			    (long)qtime, (float)qtime / nright);
E 2
	}
D 2
	else {
		printf("What?\n");
		wrongs++;
		if(range >= MAX)	goto loop1;
		left[range] = left[i];
		right[range++] = right[j];
		goto loop1;
	}
E 2
I 2
	(void)printf("\n");
E 2
}

D 2
getline(s)
char *s;
E 2
I 2
/*
 * Pick a problem and ask it.  Keeps asking the same problem until supplied
 * with the correct answer, or until EOF or interrupt is typed.  Problems are
 * selected such that the right operand and either the left operand (for +, x)
 * or the correct result (for -, /) are in the range 0 to rangemax.  Each wrong
 * answer causes the numbers in the problem to be penalised, so that they are
 * more likely to appear in subsequent problems.
 */
problem()
E 2
{
D 2
	register char	*rs;
E 2
I 2
	register char *p;
	time_t start, finish;
	int left, op, right, result;
	char line[80];
E 2

D 2
	rs = s;
E 2
I 2
	op = keys[random() % nkeys];
	if (op != '/')
		right = getrandom(rangemax + 1, op, 1);
retry:
	/* Get the operands. */
	switch (op) {
	case '+':
		left = getrandom(rangemax + 1, op, 0);
		result = left + right;
		break;
	case '-':
		result = getrandom(rangemax + 1, op, 0);
		left = right + result;
		break;
	case 'x':
		left = getrandom(rangemax + 1, op, 0);
		result = left * right;
		break;
	case '/':
		right = getrandom(rangemax, op, 1) + 1;
		result = getrandom(rangemax + 1, op, 0);
		left = right * result + random() % right;
		break;
	}
E 2

D 2
	while((*rs = getchar()) == ' ');
	while(*rs != '\n')
		if(*rs == 0)
			exit();
		else if(rs >= &s[99]) {
			while((*rs = getchar()) != '\n')
				if(*rs == '\0')	exit();
E 2
I 2
	/*
	 * A very big maxrange could cause negative values to pop
	 * up, owing to overflow.
	 */
	if (result < 0 || left < 0)
		goto retry;

	(void)printf("%d %c %d =   ", left, op, right);
	(void)fflush(stdout);
	(void)time(&start);

	/*
	 * Keep looping until the correct answer is given, or until EOF or
	 * interrupt is typed.
	 */
	for (;;) {
		if (!fgets(line, sizeof(line), stdin)) {
			(void)printf("\n");
			return(EOF);
E 2
		}
I 2
		for (p = line; *p && isspace(*p); ++p);
		if (!isdigit(*p)) {
			(void)printf("Please type a number.\n");
			continue;
		}
		if (atoi(p) == result) {
			(void)printf("Right!\n");
			++nright;
			break;
		}
		/* Wrong answer; penalise and ask again. */
		(void)printf("What?\n");
		++nwrong;
		penalise(right, op, 1);
		if (op == 'x' || op == '+')
			penalise(left, op, 0);
E 2
		else
D 2
			*++rs = getchar();
	while(*--rs == ' ')
		*rs = '\n';
E 2
I 2
			penalise(result, op, 0);
	}

	/*
	 * Accumulate the time taken.  Obviously rounding errors happen here;
	 * however they should cancel out, because some of the time you are
	 * charged for a partially elapsed second at the start, and some of
	 * the time you are not charged for a partially elapsed second at the
	 * end.
	 */
	(void)time(&finish);
	qtime += finish - start;
	return(0);
E 2
}

D 2
getnum(s)
char *s;
{
	int	a;
	char	c;
E 2
I 2
/*
 * Here is the code for accumulating penalties against the numbers for which
 * a wrong answer was given.  The right operand and either the left operand
 * (for +, x) or the result (for -, /) are stored in a list for the particular
 * operation, and each becomes more likely to appear again in that operation.
 * Initially, each number is charged a penalty of WRONGPENALTY, giving it that
 * many extra chances of appearing.  Each time it is selected because of this,
 * its penalty is decreased by one; it is removed when it reaches 0.
 *
 * The penalty[] array gives the sum of all penalties in the list for
 * each operation and each operand.  The penlist[] array has the lists of
 * penalties themselves.
 */
E 2

D 2
	a = 0;
	while((c = *s++) >= '0' && c <= '9') {
		a = a*10 + c - '0';
	}
	return(a);
}
E 2
I 2
int penalty[sizeof(keylist) - 1][2];
struct penalty {
	int value, penalty;	/* Penalised value and its penalty. */
	struct penalty *next;
} *penlist[sizeof(keylist) - 1][2];
E 2

D 2
int arand;
E 2
I 2
#define	WRONGPENALTY	5	/* Perhaps this should depend on maxrange. */
E 2

D 2
srand(n)
E 2
I 2
/*
 * Add a penalty for the number `value' to the list for operation `op',
 * operand number `operand' (0 or 1).  If we run out of memory, we just
 * forget about the penalty (how likely is this, anyway?).
 */
penalise(value, op, operand)
	int value, op, operand;
E 2
{
D 2
	arand = n&077774 | 01;
E 2
I 2
	struct penalty *p;
	char *malloc();

	op = opnum(op);
	if ((p = (struct penalty *)malloc((u_int)sizeof(*p))) == NULL)
		return;
	p->next = penlist[op][operand];
	penlist[op][operand] = p;
	penalty[op][operand] += p->penalty = WRONGPENALTY;
	p->value = value;
E 2
}

D 2
rand()		/*uniform on 0 to 2**13-1*/
E 2
I 2
/*
 * Select a random value from 0 to maxval - 1 for operand `operand' (0 or 1)
 * of operation `op'.  The random number we generate is either used directly
 * as a value, or represents a position in the penalty list.  If the latter,
 * we find the corresponding value and return that, decreasing its penalty.
 */
getrandom(maxval, op, operand)
	int maxval, op, operand;
E 2
{
I 2
	int value;
	register struct penalty **pp, *p;
E 2

D 2
	arand *= 3125;
	arand &= 077777;
	return(arand/4);
}
E 2
I 2
	op = opnum(op);
	value = random() % (maxval + penalty[op][operand]);
E 2

D 2
random(range)
{
	return(hmul(rand(), 8*range));
}
E 2
I 2
	/*
	 * 0 to maxval - 1 is a number to be used directly; bigger values
	 * are positions to be located in the penalty list.
	 */
	if (value < maxval)
		return(value);
	value -= maxval;
E 2

D 2
skrand(range){
int temp;
	temp = rand() + rand();
	if(temp >017777) temp = 040000 - temp;
	return(hmul(temp,8*range));
E 2
I 2
	/*
	 * Find the penalty at position `value'; decrement its penalty and
	 * delete it if it reaches 0; return the corresponding value.
	 */
	for (pp = &penlist[op][operand]; (p = *pp) != NULL; pp = &p->next) {
		if (p->penalty > value) {
			value = p->value;
			penalty[op][operand]--;
			if (--(p->penalty) <= 0) {
				p = p->next;
				(void)free((char *)*pp);
				*pp = p;
			}
			return(value);
		}
		value -= p->penalty;
E 2
	}
I 2
	/*
	 * We can only get here if the value from the penalty[] array doesn't
	 * correspond to the actual sum of penalties in the list.  Provide an
	 * obscure message.
	 */
	(void)fprintf(stderr, "arithmetic: bug: inconsistent penalties\n");
	exit(1);
	/* NOTREACHED */
}
E 2

D 2
/* 'hmul' returns the upper 16 bits of the product, where the operands
   are assumed to be 16-bit integers. It replaces an old PDP-11 
   assembler language subroutine. -- dks.
*/
hmul(a,b) { return(a*b >> 16); }
score()
E 2
I 2
/* Return an index for the character op, which is one of [+-x/]. */
opnum(op)
	int op;
E 2
{
D 2
	time(&etvec);
E 2
I 2
	char *p;
E 2

D 2
	printf("\n\nRights %d; Wrongs %d; Score %d%%\n", rights, wrongs,
		(rights * 100)/(rights + wrongs));

	if(rights == 0)	return;
	printf("Total time %ld seconds; %.1f seconds per problem\n\n\n",
		etvec - stvec,
		(etvec - stvec) / (rights + 0.));

	sleep(3);
	time(&dtvec);
	stvec += dtvec - etvec;
	return(0);
E 2
I 2
	if (op == 0 || (p = index(keylist, op)) == NULL) {
		(void)fprintf(stderr,
		    "arithmetic: bug: op %c not in keylist %s\n", op, keylist);
		exit(1);
	}
	return(p - keylist);
E 2
}

D 2
delete()
E 2
I 2
/* Print usage message and quit. */
usage()
E 2
{
D 2
	if(rights + wrongs == 0.) {
		printf("\n");
		exit();
	}
	score();
	exit();
E 2
I 2
D 3
	(void)fprintf(stderr, "usage: arithmetic [-o [+-x/]] [-r range]\n");
E 3
I 3
	(void)fprintf(stderr, "usage: arithmetic [-o +-x/] [-r range]\n");
E 3
	exit(1);
E 2
}
D 2

E 2
E 1
