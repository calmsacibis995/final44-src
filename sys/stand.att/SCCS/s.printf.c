h17105
s 00002/00002/00148
d D 8.1 93/06/11 16:02:08 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00150
d D 5.7 92/10/11 10:01:06 bostic 7 6
c make kernel includes standard
e
s 00000/00012/00150
d D 5.6 91/05/25 15:31:20 bostic 6 5
c delete obsolete printf formats (%D, %O, %U, %X)
e
s 00003/00001/00159
d D 5.5 91/05/05 14:28:20 william 5 4
c bug in kprintn, buffer too small
e
s 00035/00027/00125
d D 5.4 91/05/04 17:53:39 bostic 4 3
c bring into line with the kernel version, minor cleanups/fixes
e
s 00019/00019/00133
d D 5.3 91/05/03 17:13:55 bostic 3 2
c sign removal was wrong, Mike doesn't like _ on local variables
e
s 00001/00003/00151
d D 5.2 91/05/03 16:55:17 bostic 2 1
c don't need sys/param.h
e
s 00154/00000/00000
d D 5.1 91/05/03 16:54:23 bostic 1 0
c date and time created 91/05/03 16:54:23 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include <sys/param.h>

E 2
/*
D 2
 * Scaled down version of C Library printf.
E 2
I 2
 * Scaled down version of printf(3).
E 2
 *
D 4
 * Used to print diagnostic information directly on the console tty.  Since
 * it is not interrupt driven, all system activities are suspended.  Printf
 * should not be used for chit-chat.
E 4
I 4
 * One additional format:
E 4
 *
D 4
 * One additional format: %b is supported to decode error registers.
E 4
I 4
 * The format %b is supported to decode error registers.
E 4
 * Its usage is:
 *
 *	printf("reg=%b\n", regval, "<base><arg>*");
 *
 * where <base> is the output base expressed as a control character, e.g.
 * \10 gives octal; \20 gives hex.  Each arg is a sequence of characters,
 * the first of which gives the bit number to be inspected (origin 1), and
 * the next characters (up to a control character, i.e. a character <= 32),
 * give the name of the register.  Thus:
 *
 *	printf("reg=%b\n", 3, "\10\2BITTWO\1BITONE\n");
 *
 * would produce output:
 *
 *	reg=3<BITTWO,BITONE>
 */

D 4
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
E 4
I 4
#include <sys/cdefs.h>
I 5
#include <sys/types.h>
E 5
E 4

D 4
static void abort(){}				/* Needed by stdarg macros. */
static void number();
E 4
I 4
/*
 * Note that stdarg.h and the ANSI style va_start macro is used for both
 * ANSI and traditional C compilers.
 */
#define KERNEL
#include <machine/stdarg.h>
#undef KERNEL
E 4

I 4
static void kprintn __P((u_long, int));

E 4
void
#if __STDC__
printf(const char *fmt, ...)
#else
D 4
printf(fmt, va_alist)
E 4
I 4
printf(fmt /* , va_alist */)
E 4
	char *fmt;
D 4
        va_dcl
E 4
#endif
{
	register char *p;
	register int ch, n;
D 3
	unsigned long _ulong;
E 3
I 3
	unsigned long ul;
E 3
	int lflag, set;
D 4

E 4
	va_list ap;
D 4
#if __STDC__
E 4
I 4

E 4
	va_start(ap, fmt);
D 4
#else
	va_start(ap);
#endif
E 4
	for (;;) {
		while ((ch = *fmt++) != '%') {
			if (ch == '\0')
				return;
			putchar(ch);
		}
		lflag = 0;
reswitch:	switch (ch = *fmt++) {
		case 'l':
			lflag = 1;
			goto reswitch;
		case 'b':
D 3
			_ulong = va_arg(ap, int);
E 3
I 3
			ul = va_arg(ap, int);
E 3
			p = va_arg(ap, char *);
D 3
			number(_ulong, *p++);
E 3
I 3
D 4
			number(ul, *p++);
E 4
I 4
			kprintn(ul, *p++);
E 4
E 3

D 3
			if (!_ulong)
E 3
I 3
			if (!ul)
E 3
				break;

			for (set = 0; n = *p++;) {
D 3
				if (_ulong & (1 << (n - 1))) {
E 3
I 3
				if (ul & (1 << (n - 1))) {
E 3
					putchar(set ? ',' : '<');
					for (; (n = *p) > ' '; ++p)
						putchar(n);
					set = 1;
				} else
					for (; *p > ' '; ++p);
			}
			if (set)
				putchar('>');
			break;
		case 'c':
			ch = va_arg(ap, int);
				putchar(ch & 0x7f);
			break;
		case 's':
			p = va_arg(ap, char *);
			while (ch = *p++)
				putchar(ch);
			break;
I 4
D 6
		case 'D':
			lflag = 1;
			/* FALLTHROUGH */
E 6
E 4
		case 'd':
D 3
			_ulong = lflag ?
E 3
I 3
			ul = lflag ?
E 3
			    va_arg(ap, long) : va_arg(ap, int);
D 3
			if ((long)_ulong < 0) {
E 3
I 3
			if ((long)ul < 0) {
E 3
				putchar('-');
D 3
				_ulong = -_ulong;
E 3
I 3
				ul = -(long)ul;
E 3
			}
D 3
			number(_ulong, 10);
E 3
I 3
D 4
			number(ul, 10);
E 4
I 4
			kprintn(ul, 10);
E 4
E 3
			break;
I 4
D 6
		case 'O':
			lflag = 1;
			/* FALLTHROUGH */
E 6
E 4
		case 'o':
D 3
			_ulong = lflag ?
E 3
I 3
			ul = lflag ?
E 3
D 4
			    va_arg(ap, long) : va_arg(ap, unsigned int);
D 3
			number(_ulong, 8);
E 3
I 3
			number(ul, 8);
E 4
I 4
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 8);
E 4
E 3
			break;
I 4
D 6
		case 'U':
			lflag = 1;
			/* FALLTHROUGH */
E 6
E 4
		case 'u':
D 3
			_ulong = lflag ?
E 3
I 3
			ul = lflag ?
E 3
D 4
			    va_arg(ap, long) : va_arg(ap, unsigned int);
D 3
			number(_ulong, 10);
E 3
I 3
			number(ul, 10);
E 4
I 4
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 10);
E 4
E 3
			break;
I 4
D 6
		case 'X':
			lflag = 1;
			/* FALLTHROUGH */
E 6
E 4
		case 'x':
D 3
			_ulong = lflag ?
E 3
I 3
			ul = lflag ?
E 3
D 4
			    va_arg(ap, long) : va_arg(ap, unsigned int);
D 3
			number(_ulong, 16);
E 3
I 3
			number(ul, 16);
E 4
I 4
			    va_arg(ap, u_long) : va_arg(ap, u_int);
			kprintn(ul, 16);
E 4
E 3
			break;
		default:
			putchar('%');
			if (lflag)
				putchar('l');
			putchar(ch);
		}
	}
	va_end(ap);
}

static void
D 3
number(_ulong, base)
	unsigned long _ulong;
E 3
I 3
D 4
number(ul, base)
E 4
I 4
kprintn(ul, base)
E 4
	unsigned long ul;
E 3
	int base;
{
D 5
	char *p, buf[11];			/* hold 2^32 in base 8 */
E 5
I 5
					/* hold a long in base 8 */
	char *p, buf[(sizeof(long) * NBBY / 3) + 1];
E 5

	p = buf;
	do {
D 3
		*p++ = "0123456789abcdef"[_ulong % base];
	} while (_ulong /= base);
E 3
I 3
		*p++ = "0123456789abcdef"[ul % base];
	} while (ul /= base);
E 3
	do {
		putchar(*--p);
	} while (p > buf);
}
E 1
