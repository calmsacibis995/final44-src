h53996
s 00002/00002/00022
d D 8.1 93/06/11 15:58:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00023
d D 7.5 92/10/11 10:22:57 bostic 5 4
c make kernel includes standard
e
s 00000/00120/00024
d D 7.4 91/05/04 15:29:22 bostic 4 3
c use standard printf routine in ../stand/printf.c
e
s 00001/00001/00143
d D 7.3 91/04/28 17:18:51 william 3 2
c redist
e
s 00005/00014/00139
d D 7.2 91/04/28 17:18:09 william 2 1
c cruft
e
s 00153/00000/00000
d D 7.1 90/04/24 19:57:08 william 1 0
c date and time created 90/04/24 19:57:08 by william
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
D 3
 * %sccs.include.noredist.c%
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include <sys/types.h>
E 2
I 2
D 5
#include "types.h"
E 5
I 5
#include <sys/types.h>
E 5
E 2

I 2
D 4

E 2
/*
 * Scaled down version of C Library printf.
 * Used to print diagnostic information directly on console tty.
 *
 * One additional format: %b is supported to decode error registers.
 * Usage is:
 *	printf("reg=%b\n", regval, "<base><arg>*");
 * Where <base> is the output base expressed as a control character,
 * e.g. \10 gives octal; \20 gives hex.  Each arg is a sequence of
 * characters, the first of which gives the bit number to be inspected
 * (origin 1), and the next characters (up to a control character, i.e.
 * a character <= 32), give the name of the register.  Thus
 *	printf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
 * would produce output:
 *	reg=3<BITTWO,BITONE>
 */
/*VARARGS1*/
printf(fmt, x1)
	char *fmt;
	unsigned x1;
{

	prf(fmt, &x1);
}

prf(fmt, adx)
	register char *fmt;
	register *adx;
{
	register int b, c, i;
	char *s, sep;

loop:
	while ((c = *fmt++) != '%') {
		if(c == '\0')
			return;
		putchar(c);
	}
again:
	c = *fmt++;
D 2
	/*
	 * THIS CODE IS BYTE-ORDER DEPENDENT IN HANDLING %c
	 * AND IGNORES SHORT/LONG DISTINCTIONS.
	 */
E 2
	switch (c) {

	case 'l':
		goto again;
	case 'x': case 'X':
		b = 16;
		goto number;
	case 'd': case 'D':
	case 'u':		/* what a joke */
		b = 10;
		goto number;
	case 'o': case 'O':
		b = 8;
number:
		printn((u_long)*adx, b);
		break;
	case 'c':
		b = *adx;
		for (i = 24; i >= 0; i -= 8)
			if (c = (b >> i) & 0x7f)
				putchar(c);
		break;
D 2
#ifndef notyet
E 2
I 2
#ifdef notyet
E 2
	case 'b':
		b = *adx++;
		s = (char *)*adx;
		printn((u_long)b, *s++);
		if (b) {
			sep = '<';
			while (i = *s++) {
				if (b & (1 << (i-1))) {
					putchar(sep);
					sep = ',';
					for (; (c = *s) > 32; s++)
						putchar(c);
				} else
					for (; *s > 32; s++)
						;
			}
			if (sep != '<')
				putchar('>');
		}
		break;
#endif

	case 's':
		s = (char *)*adx;
		while (c = *s++)
			putchar(c);
		break;
	}
	adx++;
	goto loop;
}

/*
 * Printn prints a number n in base b.
 * We don't use recursion to avoid deep kernel stacks.
 */
printn(n, b)
	u_long n;
{
	char prbuf[11];
	register char *cp;

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

E 4
D 2
#define lf	10	
#define cr	13	

E 2
putchar(c)
char c;
{
D 2
        if (c == lf)
{
		sput(cr);
wait(60000);
}
E 2
I 2
        if (c == '\n')
		sput('\r');
E 2
	sput(c);
	return(0);
}

wait(n) { while(n--) ; }
E 1
