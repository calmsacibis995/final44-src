h15734
s 00005/00004/00030
d D 7.3 91/05/03 12:15:57 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00033
d D 7.2 90/03/15 19:54:16 root 2 1
c update location of include files
e
s 00032/00000/00000
d D 7.1 88/02/05 16:58:20 bostic 1 0
c date and time created 88/02/05 16:58:20 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include "param.h"
E 2
I 2
#include "sys/param.h"
E 2

/*
 * Printn prints a number n in base b.
 * We don't use recursion to avoid deep kernel stacks.
 */
printn(n, b)
	u_long n;
	int b;
{
	register char *cp;
	char prbuf[11];

	if (b == 10 && (int)n < 0) {
		putchar('-');
		n = (unsigned)(-(int)n);
	}
	cp = prbuf;
	do {
		*cp++ = "0123456789abcdef"[n%b];
		n /= b;
	} while (n);
	do
		putchar(*--cp);
	while (cp > prbuf);
}
E 1
