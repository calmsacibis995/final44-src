h46437
s 00002/00002/00720
d D 8.1 93/06/04 13:10:17 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00006/00720
d D 5.7 92/12/14 01:57:49 mcilroy 10 9
c use strtod, not atof
e
s 00001/00002/00725
d D 5.6 91/02/24 13:30:28 bostic 9 8
c Add include files to get prototype declarations, and fix bugs found.
e
s 00002/00000/00725
d D 5.5 91/02/05 00:27:37 torek 8 7
c keep gcc happy
e
s 00001/00001/00724
d D 5.4 91/02/01 19:31:55 bostic 7 6
c stdc.h -> cdefs.h
e
s 00690/00258/00035
d D 5.3 91/01/20 21:19:42 bostic 6 5
c new stdio; renamed from doscan.c
e
s 00002/00002/00291
d D 5.2 86/03/09 20:48:23 donn 5 4
c added LIBC_SCCS condition for sccs ids
e
s 00003/00002/00290
d D 5.1 85/06/05 13:32:24 mckusick 4 3
c Add copyright
e
s 00029/00015/00263
d D 4.3 85/02/13 15:49:22 serge 3 2
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00001/00001/00277
d D 4.2 82/12/03 20:48:53 mckusick 2 1
c fix for reading non-negative numerics
e
s 00278/00000/00000
d D 4.1 82/12/03 20:47:34 mckusick 1 0
c date and time created 82/12/03 20:47:34 by mckusick
e
u
U
t
T
I 6
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 */

E 6
I 1
D 4
static char sccsid[] = "%W%	(Berkeley)	%E%";
E 4
I 4
D 5
#ifndef lint
E 5
I 5
#if defined(LIBC_SCCS) && !defined(lint)
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif not lint
E 5
I 5
D 6
#endif LIBC_SCCS and not lint
E 6
I 6
#endif /* LIBC_SCCS and not lint */
E 6
E 5
E 4

I 6
D 7
#include <sys/stdc.h>
E 7
I 7
D 9
#include <sys/cdefs.h>
E 9
E 7
E 6
D 4
/* @(#)doscan.c	4.1 (Berkeley) 12/21/80 */
E 4
#include <stdio.h>
D 6
#include	<ctype.h>
E 6
I 6
D 9
#include <ctype.h>
E 9
#include <stdlib.h>
I 9
#include <ctype.h>
E 9
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif
#include "local.h"
E 6

D 6
#define	SPC	01
#define	STP	02
E 6
I 6
#define FLOATING_POINT
E 6

D 6
#define	SHORT	0
#define	REGULAR	1
#define	LONG	2
#define	INT	0
#define	FLOAT	1
E 6
I 6
D 10
#ifdef FLOATING_POINT
E 10
#include "floatio.h"
D 10
#define	BUF	(MAXEXP+MAXFRACT+3)	/* 3 = sign + decimal point + NUL */
#else
#define	BUF	40
#endif
E 10
I 10
#define	BUF		513	/* Maximum length of numeric string. */
E 10
E 6

D 3
char	*_getccl();
E 3
I 3
D 6
static char *_getccl();
E 6
I 6
/*
 * Flags used during conversion.
 */
#define	LONG		0x01	/* l: long or double */
#define	LONGDBL		0x02	/* L: long double; unimplemented */
#define	SHORT		0x04	/* h: short */
#define	SUPPRESS	0x08	/* suppress assignment */
#define	POINTER		0x10	/* weird %p pointer (`fake hex') */
#define	NOSKIP		0x20	/* do not skip blanks */
E 6
E 3

D 3
char	_sctab[128] = {
E 3
I 3
D 6
static char _sctab[256] = {
E 3
	0,0,0,0,0,0,0,0,
	0,SPC,SPC,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	SPC,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
};
E 6
I 6
/*
 * The following are used in numeric conversions only:
 * SIGNOK, NDIGITS, DPTOK, and EXPOK are for floating point;
 * SIGNOK, NDIGITS, PFXOK, and NZDIGITS are for integral.
 */
#define	SIGNOK		0x40	/* +/- is (still) legal */
#define	NDIGITS		0x80	/* no digits detected */
E 6

D 6
_doscan(iop, fmt, argp)
FILE *iop;
register char *fmt;
register int **argp;
E 6
I 6
#define	DPTOK		0x100	/* (float) decimal point is still legal */
#define	EXPOK		0x200	/* (float) exponent (e+3, etc) still legal */

#define	PFXOK		0x100	/* 0x prefix is (still) legal */
#define	NZDIGITS	0x200	/* no zero digits detected */

/*
 * Conversion types.
 */
#define	CT_CHAR		0	/* %c conversion */
#define	CT_CCL		1	/* %[...] conversion */
#define	CT_STRING	2	/* %s conversion */
#define	CT_INT		3	/* integer, i.e., strtol or strtoul */
#define	CT_FLOAT	4	/* floating, i.e., strtod */

#define u_char unsigned char
#define u_long unsigned long

static u_char *__sccl();

/*
 * vfscanf
 */
__svfscanf(fp, fmt0, ap)
	register FILE *fp;
	char const *fmt0;
	va_list ap;
E 6
{
D 6
	register int ch;
	int nmatch, len, ch1;
	int **ptr, fileended, size;
E 6
I 6
	register u_char *fmt = (u_char *)fmt0;
	register int c;		/* character from format, or conversion */
	register size_t width;	/* field width, or 0 */
	register char *p;	/* points into all kinds of strings */
	register int n;		/* handy integer */
	register int flags;	/* flags as defined above */
	register char *p0;	/* saves original value of p when necessary */
	int nassigned;		/* number of fields assigned */
	int nread;		/* number of characters consumed from fp */
	int base;		/* base argument to strtol/strtoul */
	u_long (*ccfn)();	/* conversion function (strtol/strtoul) */
	char ccltab[256];	/* character class table for %[...] */
	char buf[BUF];		/* buffer for numeric conversions */
E 6

D 6
	nmatch = 0;
	fileended = 0;
	for (;;) switch (ch = *fmt++) {
	case '\0': 
		return (nmatch);
	case '%': 
		if ((ch = *fmt++) == '%')
			goto def;
		ptr = 0;
		if (ch != '*')
			ptr = argp++;
		else
			ch = *fmt++;
		len = 0;
		size = REGULAR;
		while (isdigit(ch)) {
			len = len*10 + ch - '0';
			ch = *fmt++;
E 6
I 6
	/* `basefix' is used to avoid `if' tests in the integer scanner */
	static short basefix[17] =
		{ 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	nassigned = 0;
	nread = 0;
I 8
	base = 0;		/* XXX just to keep gcc happy */
	ccfn = NULL;		/* XXX just to keep gcc happy */
E 8
	for (;;) {
		c = *fmt++;
		if (c == 0)
			return (nassigned);
		if (isspace(c)) {
			for (;;) {
				if (fp->_r <= 0 && __srefill(fp))
					return (nassigned);
				if (!isspace(*fp->_p))
					break;
				nread++, fp->_r--, fp->_p++;
			}
			continue;
E 6
		}
D 6
		if (len == 0)
			len = 30000;
		if (ch=='l') {
			size = LONG;
			ch = *fmt++;
		} else if (ch=='h') {
			size = SHORT;
			ch = *fmt++;
		} else if (ch=='[')
			fmt = _getccl(fmt);
		if (isupper(ch)) {
			ch = tolower(ch);
			size = LONG;
E 6
I 6
		if (c != '%')
			goto literal;
		width = 0;
		flags = 0;
		/*
		 * switch on the format.  continue if done;
		 * break once format type is derived.
		 */
again:		c = *fmt++;
		switch (c) {
		case '%':
literal:
			if (fp->_r <= 0 && __srefill(fp))
				goto input_failure;
			if (*fp->_p != c)
				goto match_failure;
			fp->_r--, fp->_p++;
			nread++;
			continue;

		case '*':
			flags |= SUPPRESS;
			goto again;
		case 'l':
			flags |= LONG;
			goto again;
		case 'L':
			flags |= LONGDBL;
			goto again;
		case 'h':
			flags |= SHORT;
			goto again;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			width = width * 10 + c - '0';
			goto again;

		/*
		 * Conversions.
		 * Those marked `compat' are for 4.[123]BSD compatibility.
		 *
		 * (According to ANSI, E and X formats are supposed
		 * to the same as e and x.  Sorry about that.)
		 */
		case 'D':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'd':
			c = CT_INT;
			ccfn = (u_long (*)())strtol;
			base = 10;
			break;

		case 'i':
			c = CT_INT;
			ccfn = (u_long (*)())strtol;
			base = 0;
			break;

		case 'O':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'o':
			c = CT_INT;
			ccfn = strtoul;
			base = 8;
			break;

		case 'u':
			c = CT_INT;
			ccfn = strtoul;
			base = 10;
			break;

		case 'X':	/* compat   XXX */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'x':
			flags |= PFXOK;	/* enable 0x prefixing */
			c = CT_INT;
			ccfn = strtoul;
			base = 16;
			break;

#ifdef FLOATING_POINT
		case 'E':	/* compat   XXX */
		case 'F':	/* compat */
			flags |= LONG;
			/* FALLTHROUGH */
		case 'e': case 'f': case 'g':
			c = CT_FLOAT;
			break;
#endif

		case 's':
			c = CT_STRING;
			break;

		case '[':
			fmt = __sccl(ccltab, fmt);
			flags |= NOSKIP;
			c = CT_CCL;
			break;

		case 'c':
			flags |= NOSKIP;
			c = CT_CHAR;
			break;

		case 'p':	/* pointer format is like hex */
			flags |= POINTER | PFXOK;
			c = CT_INT;
			ccfn = strtoul;
			base = 16;
			break;

		case 'n':
			if (flags & SUPPRESS)	/* ??? */
				continue;
			if (flags & SHORT)
				*va_arg(ap, short *) = nread;
			else if (flags & LONG)
				*va_arg(ap, long *) = nread;
			else
				*va_arg(ap, int *) = nread;
			continue;

		/*
		 * Disgusting backwards compatibility hacks.	XXX
		 */
		case '\0':	/* compat */
			return (EOF);

		default:	/* compat */
			if (isupper(c))
				flags |= LONG;
			c = CT_INT;
			ccfn = (u_long (*)())strtol;
			base = 10;
			break;
E 6
		}
D 6
		if (ch == '\0')
			return(-1);
		if (_innum(ptr, ch, len, size, iop, &fileended) && ptr)
			nmatch++;
		if (fileended)
			return(nmatch? nmatch: -1);
		break;
E 6

D 6
	case ' ':
	case '\n':
	case '\t': 
		while ((ch1 = getc(iop))==' ' || ch1=='\t' || ch1=='\n')
			;
		if (ch1 != EOF)
			ungetc(ch1, iop);
		break;
E 6
I 6
		/*
		 * We have a conversion that requires input.
		 */
		if (fp->_r <= 0 && __srefill(fp))
			goto input_failure;
E 6

D 6
	default: 
	def:
		ch1 = getc(iop);
		if (ch1 != ch) {
			if (ch1==EOF)
				return(-1);
			ungetc(ch1, iop);
			return(nmatch);
E 6
I 6
		/*
		 * Consume leading white space, except for formats
		 * that suppress this.
		 */
		if ((flags & NOSKIP) == 0) {
			while (isspace(*fp->_p)) {
				nread++;
				if (--fp->_r > 0)
					fp->_p++;
				else if (__srefill(fp))
					goto input_failure;
			}
			/*
			 * Note that there is at least one character in
			 * the buffer, so conversions that do not set NOSKIP
			 * ca no longer result in an input failure.
			 */
E 6
		}
D 6
	}
}
E 6

I 3
D 6
static
E 3
_innum(ptr, type, len, size, iop, eofptr)
int **ptr, *eofptr;
D 3
struct _iobuf *iop;
E 3
I 3
FILE *iop;
E 3
{
	extern double atof();
	register char *np;
	char numbuf[64];
	register c, base;
	int expseen, scale, negflg, c1, ndigit;
	long lcval;
E 6
I 6
		/*
		 * Do the conversion.
		 */
		switch (c) {
E 6

D 6
	if (type=='c' || type=='s' || type=='[')
		return(_instr(ptr? *(char **)ptr: (char *)NULL, type, len, iop, eofptr));
	lcval = 0;
	ndigit = 0;
	scale = INT;
	if (type=='e'||type=='f')
		scale = FLOAT;
	base = 10;
	if (type=='o')
		base = 8;
	else if (type=='x')
		base = 16;
	np = numbuf;
	expseen = 0;
	negflg = 0;
	while ((c = getc(iop))==' ' || c=='\t' || c=='\n');
	if (c=='-') {
		negflg++;
		*np++ = c;
		c = getc(iop);
		len--;
	} else if (c=='+') {
		len--;
		c = getc(iop);
	}
	for ( ; --len>=0; *np++ = c, c = getc(iop)) {
		if (isdigit(c)
		 || base==16 && ('a'<=c && c<='f' || 'A'<=c && c<='F')) {
			ndigit++;
			if (base==8)
				lcval <<=3;
			else if (base==10)
				lcval = ((lcval<<2) + lcval)<<1;
			else
				lcval <<= 4;
			c1 = c;
			if (isdigit(c))
				c -= '0';
			else if ('a'<=c && c<='f')
				c -= 'a'-10;
			else
				c -= 'A'-10;
			lcval += c;
			c = c1;
E 6
I 6
		case CT_CHAR:
			/* scan arbitrary characters (sets NOSKIP) */
			if (width == 0)
				width = 1;
			if (flags & SUPPRESS) {
				size_t sum = 0;
				for (;;) {
					if ((n = fp->_r) < width) {
						sum += n;
						width -= n;
						fp->_p += n;
						if (__srefill(fp)) {
							if (sum == 0)
							    goto input_failure;
							break;
						}
					} else {
						sum += width;
						fp->_r -= width;
						fp->_p += width;
						break;
					}
				}
				nread += sum;
			} else {
				size_t r = fread((void *)va_arg(ap, char *), 1,
				    width, fp);

				if (r == 0)
					goto input_failure;
				nread += r;
				nassigned++;
			}
			break;

		case CT_CCL:
			/* scan a (nonempty) character class (sets NOSKIP) */
			if (width == 0)
				width = ~0;	/* `infinity' */
			/* take only those things in the class */
			if (flags & SUPPRESS) {
				n = 0;
				while (ccltab[*fp->_p]) {
					n++, fp->_r--, fp->_p++;
					if (--width == 0)
						break;
					if (fp->_r <= 0 && __srefill(fp)) {
						if (n == 0)
							goto input_failure;
						break;
					}
				}
				if (n == 0)
					goto match_failure;
			} else {
				p0 = p = va_arg(ap, char *);
				while (ccltab[*fp->_p]) {
					fp->_r--;
					*p++ = *fp->_p++;
					if (--width == 0)
						break;
					if (fp->_r <= 0 && __srefill(fp)) {
						if (p == p0)
							goto input_failure;
						break;
					}
				}
				n = p - p0;
				if (n == 0)
					goto match_failure;
				*p = 0;
				nassigned++;
			}
			nread += n;
			break;

		case CT_STRING:
			/* like CCL, but zero-length string OK, & no NOSKIP */
			if (width == 0)
				width = ~0;
			if (flags & SUPPRESS) {
				n = 0;
				while (!isspace(*fp->_p)) {
					n++, fp->_r--, fp->_p++;
					if (--width == 0)
						break;
					if (fp->_r <= 0 && __srefill(fp))
						break;
				}
				nread += n;
			} else {
				p0 = p = va_arg(ap, char *);
				while (!isspace(*fp->_p)) {
					fp->_r--;
					*p++ = *fp->_p++;
					if (--width == 0)
						break;
					if (fp->_r <= 0 && __srefill(fp))
						break;
				}
				*p = 0;
				nread += p - p0;
				nassigned++;
			}
E 6
			continue;
D 6
		} else if (c=='.') {
			if (base!=10 || scale==INT)
E 6
I 6

		case CT_INT:
			/* scan an integer as if by strtol/strtoul */
#ifdef hardway
			if (width == 0 || width > sizeof(buf) - 1)
				width = sizeof(buf) - 1;
#else
			/* size_t is unsigned, hence this optimisation */
			if (--width > sizeof(buf) - 2)
				width = sizeof(buf) - 2;
			width++;
#endif
			flags |= SIGNOK | NDIGITS | NZDIGITS;
			for (p = buf; width; width--) {
				c = *fp->_p;
				/*
				 * Switch on the character; `goto ok'
				 * if we accept it as a part of number.
				 */
				switch (c) {

				/*
				 * The digit 0 is always legal, but is
				 * special.  For %i conversions, if no
				 * digits (zero or nonzero) have been
				 * scanned (only signs), we will have
				 * base==0.  In that case, we should set
				 * it to 8 and enable 0x prefixing.
				 * Also, if we have not scanned zero digits
				 * before this, do not turn off prefixing
				 * (someone else will turn it off if we
				 * have scanned any nonzero digits).
				 */
				case '0':
					if (base == 0) {
						base = 8;
						flags |= PFXOK;
					}
					if (flags & NZDIGITS)
					    flags &= ~(SIGNOK|NZDIGITS|NDIGITS);
					else
					    flags &= ~(SIGNOK|PFXOK|NDIGITS);
					goto ok;

				/* 1 through 7 always legal */
				case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
					base = basefix[base];
					flags &= ~(SIGNOK | PFXOK | NDIGITS);
					goto ok;

				/* digits 8 and 9 ok iff decimal or hex */
				case '8': case '9':
					base = basefix[base];
					if (base <= 8)
						break;	/* not legal here */
					flags &= ~(SIGNOK | PFXOK | NDIGITS);
					goto ok;

				/* letters ok iff hex */
				case 'A': case 'B': case 'C':
				case 'D': case 'E': case 'F':
				case 'a': case 'b': case 'c':
				case 'd': case 'e': case 'f':
					/* no need to fix base here */
					if (base <= 10)
						break;	/* not legal here */
					flags &= ~(SIGNOK | PFXOK | NDIGITS);
					goto ok;

				/* sign ok only as first character */
				case '+': case '-':
					if (flags & SIGNOK) {
						flags &= ~SIGNOK;
						goto ok;
					}
					break;

				/* x ok iff flag still set & 2nd char */
				case 'x': case 'X':
					if (flags & PFXOK && p == buf + 1) {
						base = 16;	/* if %i */
						flags &= ~PFXOK;
						goto ok;
					}
					break;
				}

				/*
				 * If we got here, c is not a legal character
				 * for a number.  Stop accumulating digits.
				 */
E 6
				break;
D 6
			ndigit++;
			continue;
		} else if ((c=='e'||c=='E') && expseen==0) {
			if (base!=10 || scale==INT || ndigit==0)
				break;
			expseen++;
			*np++ = c;
			c = getc(iop);
			if (c!='+'&&c!='-'&&('0'>c||c>'9'))
				break;
		} else
E 6
I 6
		ok:
				/*
				 * c is legal: store it and look at the next.
				 */
				*p++ = c;
				if (--fp->_r > 0)
					fp->_p++;
				else if (__srefill(fp))
					break;		/* EOF */
			}
			/*
			 * If we had only a sign, it is no good; push
			 * back the sign.  If the number ends in `x',
			 * it was [sign] '0' 'x', so push back the x
			 * and treat it as [sign] '0'.
			 */
			if (flags & NDIGITS) {
				if (p > buf)
					(void) ungetc(*(u_char *)--p, fp);
				goto match_failure;
			}
			c = ((u_char *)p)[-1];
			if (c == 'x' || c == 'X') {
				--p;
				(void) ungetc(c, fp);
			}
			if ((flags & SUPPRESS) == 0) {
				u_long res;

				*p = 0;
				res = (*ccfn)(buf, (char **)NULL, base);
				if (flags & POINTER)
					*va_arg(ap, void **) = (void *)res;
				else if (flags & SHORT)
					*va_arg(ap, short *) = res;
				else if (flags & LONG)
					*va_arg(ap, long *) = res;
				else
					*va_arg(ap, int *) = res;
				nassigned++;
			}
			nread += p - buf;
E 6
			break;
D 6
	}
	if (negflg)
		lcval = -lcval;
	if (c != EOF) {
		ungetc(c, iop);
		*eofptr = 0;
	} else
		*eofptr = 1;
D 2
 	if (ptr==NULL || np==numbuf)
E 2
I 2
 	if (ptr==NULL || np==numbuf || (negflg && np==numbuf+1) )/* gene dykes*/
E 2
		return(0);
	*np++ = 0;
	switch((scale<<4) | size) {
E 6

D 6
	case (FLOAT<<4) | SHORT:
	case (FLOAT<<4) | REGULAR:
		**(float **)ptr = atof(numbuf);
		break;
E 6
I 6
#ifdef FLOATING_POINT
		case CT_FLOAT:
			/* scan a floating point number as if by strtod */
#ifdef hardway
			if (width == 0 || width > sizeof(buf) - 1)
				width = sizeof(buf) - 1;
#else
			/* size_t is unsigned, hence this optimisation */
			if (--width > sizeof(buf) - 2)
				width = sizeof(buf) - 2;
			width++;
#endif
			flags |= SIGNOK | NDIGITS | DPTOK | EXPOK;
			for (p = buf; width; width--) {
				c = *fp->_p;
				/*
				 * This code mimicks the integer conversion
				 * code, but is much simpler.
				 */
				switch (c) {
E 6

D 6
	case (FLOAT<<4) | LONG:
		**(double **)ptr = atof(numbuf);
		break;
E 6
I 6
				case '0': case '1': case '2': case '3':
				case '4': case '5': case '6': case '7':
				case '8': case '9':
					flags &= ~(SIGNOK | NDIGITS);
					goto fok;
E 6

D 6
	case (INT<<4) | SHORT:
		**(short **)ptr = lcval;
		break;
E 6
I 6
				case '+': case '-':
					if (flags & SIGNOK) {
						flags &= ~SIGNOK;
						goto fok;
					}
					break;
				case '.':
					if (flags & DPTOK) {
						flags &= ~(SIGNOK | DPTOK);
						goto fok;
					}
					break;
				case 'e': case 'E':
					/* no exponent without some digits */
					if ((flags&(NDIGITS|EXPOK)) == EXPOK) {
						flags =
						    (flags & ~(EXPOK|DPTOK)) |
						    SIGNOK | NDIGITS;
						goto fok;
					}
					break;
				}
				break;
		fok:
				*p++ = c;
				if (--fp->_r > 0)
					fp->_p++;
				else if (__srefill(fp))
					break;	/* EOF */
			}
			/*
			 * If no digits, might be missing exponent digits
			 * (just give back the exponent) or might be missing
			 * regular digits, but had sign and/or decimal point.
			 */
			if (flags & NDIGITS) {
				if (flags & EXPOK) {
					/* no digits at all */
					while (p > buf)
						ungetc(*(u_char *)--p, fp);
					goto match_failure;
				}
				/* just a bad exponent (e and maybe sign) */
				c = *(u_char *)--p;
				if (c != 'e' && c != 'E') {
					(void) ungetc(c, fp);/* sign */
					c = *(u_char *)--p;
				}
				(void) ungetc(c, fp);
			}
			if ((flags & SUPPRESS) == 0) {
				double res;
E 6

D 6
	case (INT<<4) | REGULAR:
		**(int **)ptr = lcval;
		break;

	case (INT<<4) | LONG:
		**(long **)ptr = lcval;
		break;
E 6
I 6
				*p = 0;
D 10
				res = atof(buf);
E 10
I 10
				res = strtod(buf,(char **) NULL);
E 10
				if (flags & LONG)
					*va_arg(ap, double *) = res;
				else
					*va_arg(ap, float *) = res;
				nassigned++;
			}
			nread += p - buf;
			break;
#endif /* FLOATING_POINT */
		}
E 6
	}
D 6
	return(1);
E 6
I 6
input_failure:
	return (nassigned ? nassigned : -1);
match_failure:
	return (nassigned);
E 6
}

I 3
D 6
static
E 3
_instr(ptr, type, len, iop, eofptr)
register char *ptr;
D 3
register struct _iobuf *iop;
E 3
I 3
register FILE *iop;
E 3
int *eofptr;
E 6
I 6
/*
 * Fill in the given table from the scanset at the given format
 * (just after `[').  Return a pointer to the character past the
 * closing `]'.  The table has a 1 wherever characters should be
 * considered part of the scanset.
 */
static u_char *
__sccl(tab, fmt)
	register char *tab;
	register u_char *fmt;
E 6
{
D 6
	register ch;
	register char *optr;
	int ignstp;
E 6
I 6
	register int c, n, v;
E 6

D 6
	*eofptr = 0;
	optr = ptr;
	if (type=='c' && len==30000)
		len = 1;
	ignstp = 0;
	if (type=='s')
		ignstp = SPC;
D 3
	while (_sctab[ch = getc(iop)] & ignstp)
		if (ch==EOF)
			break;
E 3
I 3
	while ((ch = getc(iop)) != EOF && _sctab[ch] & ignstp)
		;
E 3
	ignstp = SPC;
	if (type=='c')
		ignstp = 0;
	else if (type=='[')
		ignstp = STP;
	while (ch!=EOF && (_sctab[ch]&ignstp)==0) {
		if (ptr)
			*ptr++ = ch;
		if (--len <= 0)
			break;
		ch = getc(iop);
	}
	if (ch != EOF) {
		if (len > 0)
			ungetc(ch, iop);
		*eofptr = 0;
E 6
I 6
	/* first `clear' the whole table */
	c = *fmt++;		/* first char hat => negated scanset */
	if (c == '^') {
		v = 1;		/* default => accept */
		c = *fmt++;	/* get new first char */
E 6
	} else
D 6
		*eofptr = 1;
	if (ptr && ptr!=optr) {
		if (type!='c')
			*ptr++ = '\0';
		return(1);
	}
	return(0);
}
E 6
I 6
		v = 0;		/* default => reject */
	/* should probably use memset here */
	for (n = 0; n < 256; n++)
		tab[n] = v;
	if (c == 0)
		return (fmt - 1);/* format ended before closing ] */
E 6

D 3
char *
E 3
I 3
D 6
static char *
E 3
_getccl(s)
D 3
register char *s;
E 3
I 3
register unsigned char *s;
E 3
{
	register c, t;
E 6
I 6
	/*
	 * Now set the entries corresponding to the actual scanset
	 * to the opposite of the above.
	 *
	 * The first character may be ']' (or '-') without being special;
	 * the last character may be '-'.
	 */
	v = 1 - v;
	for (;;) {
		tab[c] = v;		/* take character c */
doswitch:
		n = *fmt++;		/* and examine the next */
		switch (n) {
E 6

D 6
	t = 0;
	if (*s == '^') {
		t++;
		s++;
E 6
I 6
		case 0:			/* format ended too soon */
			return (fmt - 1);

		case '-':
			/*
			 * A scanset of the form
			 *	[01+-]
			 * is defined as `the digit 0, the digit 1,
			 * the character +, the character -', but
			 * the effect of a scanset such as
			 *	[a-zA-Z0-9]
			 * is implementation defined.  The V7 Unix
			 * scanf treats `a-z' as `the letters a through
			 * z', but treats `a-a' as `the letter a, the
			 * character -, and the letter a'.
			 *
			 * For compatibility, the `-' is not considerd
			 * to define a range if the character following
			 * it is either a close bracket (required by ANSI)
			 * or is not numerically greater than the character
			 * we just stored in the table (c).
			 */
			n = *fmt;
			if (n == ']' || n < c) {
				c = '-';
				break;	/* resume the for(;;) */
			}
			fmt++;
			do {		/* fill in the range */
				tab[++c] = v;
			} while (c < n);
#if 1	/* XXX another disgusting compatibility hack */
			/*
			 * Alas, the V7 Unix scanf also treats formats
			 * such as [a-c-e] as `the letters a through e'.
			 * This too is permitted by the standard....
			 */
			goto doswitch;
#else
			c = *fmt++;
			if (c == 0)
				return (fmt - 1);
			if (c == ']')
				return (fmt);
#endif
			break;

		case ']':		/* end of scanset */
			return (fmt);

		default:		/* just another character */
			c = n;
			break;
		}
E 6
	}
D 3
	for (c = 0; c < 128; c++)
E 3
I 3
D 6
	for (c = 0; c < (sizeof _sctab / sizeof _sctab[0]); c++)
E 3
		if (t)
			_sctab[c] &= ~STP;
		else
			_sctab[c] |= STP;
D 3
	while (((c = *s++)&0177) != ']') {
E 3
I 3
	if ((c = *s) == ']' || c == '-') {	/* first char is special */
E 3
		if (t)
D 3
			_sctab[c++] |= STP;
E 3
I 3
			_sctab[c] |= STP;
E 3
		else
D 3
			_sctab[c++] &= ~STP;
E 3
I 3
			_sctab[c] &= ~STP;
		s++;
	}
	while ((c = *s++) != ']') {
E 3
		if (c==0)
D 3
			return(--s);
E 3
I 3
			return((char *)--s);
		else if (c == '-' && *s != ']' && s[-2] < *s) {
			for (c = s[-2] + 1; c < *s; c++)
				if (t)
					_sctab[c] |= STP;
				else
					_sctab[c] &= ~STP;
		} else if (t)
			_sctab[c] |= STP;
		else
			_sctab[c] &= ~STP;
E 3
	}
D 3
	return(s);
E 3
I 3
	return((char *)s);
E 6
I 6
	/* NOTREACHED */
E 6
E 3
}
E 1
