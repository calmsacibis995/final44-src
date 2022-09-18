h09671
s 00005/00004/00108
d D 8.4 94/07/27 14:58:50 bostic 10 9
c __tscroll has to take a second integer argument for CS string
e
s 00001/00001/00111
d D 8.3 94/05/04 06:25:02 bostic 9 8
c upgrade some includes, make curses.h local
c helps out nvi, but it's cleaner regardless
e
s 00031/00033/00081
d D 8.2 94/04/15 09:45:26 bostic 8 7
c add %p, so we can load against System V terminfo files
c lots of random cleanup
e
s 00002/00002/00112
d D 8.1 93/06/04 16:49:27 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00112
d D 5.6 93/06/01 12:49:01 bostic 6 5
c don't return the address of an automatic
e
s 00001/00001/00112
d D 5.5 93/05/30 13:06:30 bostic 5 4
c include curses.h, that's where the function is prototyped
e
s 00001/00001/00112
d D 5.4 93/01/11 12:17:22 bostic 4 3
c tscroll -> __tscroll (for now)
e
s 00001/00002/00112
d D 5.3 92/12/22 15:03:29 bostic 3 2
c result doesn't need to be static
e
s 00002/00009/00112
d D 5.2 92/12/22 14:16:47 bostic 2 1
c don't include copyright notice
e
s 00121/00000/00000
d D 5.1 92/10/01 15:06:58 elan 1 0
c date and time created 92/10/01 15:06:58 by elan
e
u
U
t
T
I 1
D 2
/*
E 2
I 2
/*-
E 2
D 7
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 8
 * Copyright (c) 1992, 1993
E 8
I 8
 * Copyright (c) 1992, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 2
 *
E 2
 * %sccs.include.redist.c%
 */

#ifndef lint
D 2
static char copyright[] =
"%Z% Copyright (c) 1992 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 5
#include <stdio.h>
E 5
I 5
D 9
#include <curses.h>
E 9
I 9
#include "curses.h"
E 9
E 5

D 2
#define MAXRETURNSIZE 64
E 2
I 2
#define	MAXRETURNSIZE	64
E 2

/*
D 8
 * Routine to perform scrolling.  Derived from tgoto.c in tercamp(3) library.
 * Cap is a string containing printf type escapes to allow
 * scrolling.
 * The following escapes are defined for substituting n:
E 8
I 8
 * Routine to perform scrolling.  Derived from tgoto.c in tercamp(3)
 * library.  Cap is a string containing printf type escapes to allow
 * scrolling.  The following escapes are defined for substituting n:
E 8
 *
 *	%d	as in printf
 *	%2	like %2d
 *	%3	like %3d
 *	%.	gives %c hacking special case characters
 *	%+x	like %c but adding x first
 *
 *	The codes below affect the state but don't use up a value.
 *
 *	%>xy	if value > x add y
 *	%i	increments n
 *	%%	gives %
 *	%B	BCD (2 decimal digits encoded in one byte)
 *	%D	Delta Data (backwards bcd)
 *
 * all other characters are ``self-inserting''.
 */
char *
D 4
tscroll(cap, n)
E 4
I 4
D 10
__tscroll(cap, n)
E 10
I 10
__tscroll(cap, n1, n2)
E 10
E 4
	const char *cap;
D 10
	int n;
E 10
I 10
	int n1, n2;
E 10
{
I 6
	static char result[MAXRETURNSIZE];
E 6
D 3
	static char result[MAXRETURNSIZE];
E 3
D 8
	register char *dp;
	register int c;
D 3
	char *cp;
E 3
I 3
D 6
	char *cp, result[MAXRETURNSIZE];
E 6
I 6
	char *cp;
E 8
I 8
D 10
	int c;
E 10
I 10
	int c, n;
E 10
	char *dp;
E 8
E 6
E 3

D 8
	if (cap == NULL) {
toohard:
		/*
		 * ``We don't do that under BOZO's big top''
		 */
		return ("OOPS");
	}

	cp = (char *) cap;
	dp = result;
	while (c = *cp++) {
E 8
I 8
	if (cap == NULL)
		goto err;
D 10
	for (dp = result; (c = *cap++) != '\0';) {
E 10
I 10
	for (n = n1, dp = result; (c = *cap++) != '\0';) {
E 10
E 8
		if (c != '%') {
			*dp++ = c;
			continue;
		}
D 8
		switch (c = *cp++) {
E 8
I 8
		switch (c = *cap++) {
E 8
		case 'n':
			n ^= 0140;
			continue;
		case 'd':
			if (n < 10)
				goto one;
			if (n < 100)
				goto two;
D 8
			/* fall into... */
E 8
I 8
			/* FALLTHROUGH */
E 8
		case '3':
			*dp++ = (n / 100) | '0';
			n %= 100;
D 8
			/* fall into... */
E 8
I 8
			/* FALLTHROUGH */
E 8
		case '2':
D 8
two:	
			*dp++ = n / 10 | '0';
one:
			*dp++ = n % 10 | '0';
E 8
I 8
two:			*dp++ = n / 10 | '0';
one:			*dp++ = n % 10 | '0';
I 10
			n = n2;
E 10
E 8
			continue;
		case '>':
D 8
			if (n > *cp++)
				n += *cp++;
E 8
I 8
			if (n > *cap++)
				n += *cap++;
E 8
			else
D 8
				cp++;
E 8
I 8
				cap++;
E 8
			continue;
		case '+':
D 8
			n += *cp++;
			/* fall into... */
E 8
I 8
			n += *cap++;
			/* FALLTHROUGH */
E 8
		case '.':
			*dp++ = n;
			continue;
		case 'i':
			n++;
			continue;
		case '%':
			*dp++ = c;
			continue;
D 8

E 8
		case 'B':
			n = (n / 10 << 4) + n % 10;
			continue;
		case 'D':
			n = n - 2 * (n % 16);
			continue;
I 8
		/*
		 * XXX
		 * System V terminfo files have lots of extra gunk.
		 * The only one we've seen in scrolling strings is
		 * %pN, and it seems to work okay if we ignore it.
		 */
		case 'p':
			++cap;
			continue;
E 8
		default:
D 8
			goto toohard;
E 8
I 8
			goto err;
E 8
		}
	}
	*dp = '\0';
	return (result);
I 8

err:	return("curses: __tscroll failed");
E 8
}
E 1
