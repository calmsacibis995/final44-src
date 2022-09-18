h38049
s 00002/00002/00050
d D 8.1 93/06/10 21:47:33 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00002/00044
d D 7.5 92/06/18 21:33:31 hibler 5 4
c merge with latest Utah version
e
s 00009/00190/00037
d D 7.4 91/05/05 13:44:58 bostic 4 3
c use common printf, printn, gets code; rename peekkey to scankbd
c I deleted the romprintf() routine, and userom variable -- it's not set by
c any of the current HP code, and has to be done differently anyway to use
c the common printf routines
e
s 00001/00001/00226
d D 7.3 90/12/16 16:39:41 bostic 3 2
c kernel reorg
e
s 00001/00001/00226
d D 7.2 90/06/24 14:58:26 karels 2 1
c update includes
e
s 00227/00000/00000
d D 7.1 90/05/08 22:46:10 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 5
/*
 * XXX we know that scankbd is only called from read/write to interrupt
 * a boot program.  Since we restart only on ^C and we do that here, we
 * always return 0 to avoid a longjmp in the caller.
 */
E 5
D 2
#include "../h/param.h"
E 2
I 2
D 3
#include "param.h"
E 3
I 3
D 4
#include "sys/param.h"
E 3
E 2

/*
 * Scaled down version of C Library printf.
 * Used to print diagnostic information directly on console tty.
 * Since it is not interrupt driven, all system activities are
 * suspended.  Printf should not be used for chit-chat.
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
 *	reg=2<BITTWO,BITONE>
 */
/*VARARGS1*/
printf(fmt, x1)
	char *fmt;
	unsigned x1;
E 4
I 4
scankbd()
E 4
{
I 4
	register int c;
E 4

D 4
	prf(0, fmt, &x1);
}

/*VARARGS1*/
romprintf(fmt, x1)
	char *fmt;
	unsigned x1;
{

	prf(1, fmt, &x1);
}

prf(userom, fmt, adx)
	register char *fmt;
	register u_int *adx;
{
	register int b, c, i;
	char *s;
	int any;

loop:
	while ((c = *fmt++) != '%') {
		if(c == '\0')
			return;
		putchar(userom, c);
	}
again:
	c = *fmt++;
	/* THIS CODE IS VAX DEPENDENT IN HANDLING %l? AND %c */
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
		printn(userom, (u_long)*adx, b);
		break;
	case 'c':
		b = *adx;
		for (i = 24; i >= 0; i -= 8)
			if (c = (b >> i) & 0x7f)
				putchar(userom, c);
		break;
	case 'b':
		b = *adx++;
		s = (char *)*adx;
		printn(userom, (u_long)b, *s++);
		any = 0;
		if (b) {
			while (i = *s++) {
				if (b & (1 << (i-1))) {
					putchar(userom, any? ',' : '<');
					any = 1;
					for (; (c = *s) > 32; s++)
						putchar(userom, c);
				} else
					for (; *s > 32; s++)
						;
			}
			if (any)
				putchar(userom, '>');
		}
		break;

	case 's':
		s = (char *)*adx;
		while (c = *s++)
			putchar(userom, c);
		break;
	}
	adx++;
	goto loop;
}

/*
 * Printn prints a number n in base b.
 * We don't use recursion to avoid deep kernel stacks.
 */
printn(userom, n, b)
	u_long n;
{
	char prbuf[11];
	register char *cp;

	if (b == 10 && (int)n < 0) {
		putchar(userom, '-');
		n = (unsigned)(-(int)n);
	}
	cp = prbuf;
	do {
		*cp++ = "0123456789abcdef"[n%b];
		n /= b;
	} while (n);
	do
		putchar(userom, *--cp);
	while (cp > prbuf);
}

/*
 * Print a character on console.
 */
putchar(userom, c)
	register c;
{
#ifdef ROMPRF
	if (userom) {
		romputchar(c);
		return;
	}
#endif
	cnputc(c);
	if(c == '\n')
		cnputc('\r');
}

peekchar()
{
	register c;

E 4
	c = cngetc();
	if (c == ('c'&037)) {
		printf("^C");
		_stop("");
		/* NOTREACHED */
	}
D 5
	return(c);
E 5
I 5
	return(0);
E 5
}

getchar()
{
D 4
	register c;
E 4
I 4
	register int c;
E 4

	while((c = cngetc()) == 0)
		;
	if (c == '\r')
		c = '\n';
	else if (c == ('c'&037)) {
		printf("^C");
		_stop("");
		/* NOTREACHED */
	}
D 4
	putchar(0, c);
E 4
I 4
D 5
	putchar(c);
E 5
I 5
	if (c != '\b' && c != '\177')
		putchar(c);
E 5
E 4
	return(c);
}

D 4
gets(buf)
	char *buf;
E 4
I 4
putchar(c)
	register int c;
E 4
{
D 4
	register char *lp;
	register c;

	lp = buf;
	for (;;) {
		c = getchar() & 0177;
		switch(c) {
		case '\n':
		case '\r':
			c = '\n';
			*lp++ = '\0';
			return;
		case '\b':
			if (lp > buf) {
				lp--;
				putchar(0, ' ');
				putchar(0, '\b');
			}
			continue;
		case '#':
		case '\177':
			lp--;
			if (lp < buf)
				lp = buf;
			continue;
		case '@':
		case 'u'&037:
			lp = buf;
			putchar(0, '\n');
			continue;
		default:
			*lp++ = c;
		}
	}
E 4
I 4
	cnputc(c);
	if (c == '\n')
		cnputc('\r');
E 4
}
D 4

E 4
E 1
