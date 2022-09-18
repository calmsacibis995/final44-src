h22301
s 00058/00058/00155
d D 7.3 90/05/03 17:47:21 sklower 3 2
c first crack at torek changes, may need bug fixes
e
s 00022/00017/00191
d D 7.2 86/12/15 20:26:50 sam 2 1
c lint
e
s 00208/00000/00000
d D 7.1 86/11/20 12:22:05 sam 1 0
c date and time created 86/11/20 12:22:05 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 2

#include "../kdb/defs.h"

D 3
long	maxpos;
int	radix = 16;
E 3
I 3
long	kdbmaxpos;
int	kdbradix = 16;
E 3

D 3
char	printbuf[MAXLIN];
char	*printptr = printbuf;
char	*digitptr;
E 3
I 3
char	kdbprintbuf[MAXLIN];
char	*kdbprintptr = kdbprintbuf;
char	*kdbdigitptr;
E 3

D 3
printc(c)
E 3
I 3
kdbprintc(c)
E 3
	char c;
{
	char d;
	register char *q;
	register posn, tabs, p;

D 3
	if (mkfault)
E 3
I 3
	if (kdbmkfault)
E 3
		return;
D 3
	if ((*printptr=c)==EOR) {
		tabs=0; posn=0; q=printbuf;
		for (p=0; p<printptr-printbuf; p++) {
			d=printbuf[p];
E 3
I 3
	if ((*kdbprintptr=c)==EOR) {
		tabs=0; posn=0; q=kdbprintbuf;
		for (p=0; p<kdbprintptr-kdbprintbuf; p++) {
			d=kdbprintbuf[p];
E 3
			if ((p&7)==0 && posn) {
				tabs++;
				posn=0;
			}
			if (d!=SP) {
				while (tabs>0)
					*q++=TB, tabs--;
				while (posn>0)
					*q++=SP, posn--;
				*q++=d;
			} else
				posn++;
		 }
		 *q++=EOR;
D 3
		 kdbwrite(printbuf,q-printbuf);
		 printptr=printbuf;
E 3
I 3
		 kdbwrite(kdbprintbuf,q-kdbprintbuf);
		 kdbprintptr=kdbprintbuf;
E 3
	} else if (c==TB) {
D 3
		*printptr++=SP;
		while ((printptr-printbuf)&7)
			*printptr++=SP;
E 3
I 3
		*kdbprintptr++=SP;
		while ((kdbprintptr-kdbprintbuf)&7)
			*kdbprintptr++=SP;
E 3
	} else if (c)
D 3
		printptr++;
	if (printptr >= &printbuf[MAXLIN-9]) {
		kdbwrite(printbuf, printptr - printbuf);
		printptr = printbuf;
E 3
I 3
		kdbprintptr++;
	if (kdbprintptr >= &kdbprintbuf[MAXLIN-9]) {
		kdbwrite(kdbprintbuf, kdbprintptr - kdbprintbuf);
		kdbprintptr = kdbprintbuf;
E 3
	}
}

D 3
charpos()
E 3
I 3
kdbcharpos()
E 3
{

D 3
	return (printptr-printbuf);
E 3
I 3
	return (kdbprintptr-kdbprintbuf);
E 3
}

D 3
flushbuf()
E 3
I 3
kdbflushbuf()
E 3
{

D 3
	if (printptr!=printbuf)
		printc(EOR);
E 3
I 3
	if (kdbprintptr!=kdbprintbuf)
		kdbprintc(EOR);
E 3
}

/* VARARGS1 */
D 3
printf(fmat,a1)
E 3
I 3
kdbprintf(fmat,a1)
E 3
	char *fmat, *a1;
{
	char *fptr;
	register char *s;
	register long *dptr;
D 2
	double *rptr;
E 2
	register width, prec;
	char c, adj;
	int x, n;
	register long lx;
	char digits[64];

	fptr = fmat; dptr = (long *)&a1;
	while (c = *fptr++) {
		if (c!='%') {
D 3
			printc(c);
E 3
I 3
			kdbprintc(c);
E 3
			continue;
		}
		if (*fptr=='-') {
			adj='l'; fptr++;
		} else
			adj='r';
D 3
		width=convert(&fptr);
E 3
I 3
		width=kdbconvert(&fptr);
E 3
		if (*fptr=='.') {
D 3
			fptr++; prec=convert(&fptr);
E 3
I 3
			fptr++; prec=kdbconvert(&fptr);
E 3
		} else
			prec = -1;
D 3
		digitptr=digits;
E 3
I 3
		kdbdigitptr=digits;
E 3
D 2
		rptr=(double *)dptr; x = lx = *dptr++;
E 2
I 2
		x = lx = *dptr++;
E 2
		s=0;
		switch (c = *fptr++) {
		case 'd':
D 2
			printnum(x, -10); break;
E 2
I 2
D 3
			printnum((u_long)x, -10); break;
E 3
I 3
			kdbprintnum((u_long)x, -10); break;
E 3
E 2
		case 'u':
D 2
			printnum((unsigned short)x, 10); break;
E 2
I 2
D 3
			printnum((u_long)x, 10); break;
E 3
I 3
			kdbprintnum((u_long)x, 10); break;
E 3
E 2
		case 'o':
D 2
			printnum((unsigned short)x, 8); break;
E 2
I 2
D 3
			printnum((u_long)x, 8); break;
E 3
I 3
			kdbprintnum((u_long)x, 8); break;
E 3
E 2
		case 'q':
D 2
			printnum(x, -8); break;
E 2
I 2
D 3
			printnum((u_long)x, -8); break;
E 3
I 3
			kdbprintnum((u_long)x, -8); break;
E 3
E 2
		case 'x':
D 2
			printnum((unsigned short)x, 16); break;
E 2
I 2
D 3
			printnum((u_long)x, 16); break;
E 3
I 3
			kdbprintnum((u_long)x, 16); break;
E 3
E 2
		case 'z':
D 2
			printnum((unsigned short)x, -16); break;
E 2
I 2
D 3
			printnum((u_long)x, -16); break;
E 3
I 3
			kdbprintnum((u_long)x, -16); break;
E 3
E 2
		case 'R':
D 2
			printnum(lx, radix); break;
E 2
I 2
D 3
			printnum((u_long)lx, radix); break;
E 3
I 3
			kdbprintnum((u_long)lx, kdbradix); break;
E 3
E 2
		case 'D':
D 2
			printnum(lx, -10); break;
E 2
I 2
D 3
			printnum((u_long)lx, -10); break;
E 3
I 3
			kdbprintnum((u_long)lx, -10); break;
E 3
E 2
		case 'U':
D 2
			printnum(lx, 10); break;
E 2
I 2
D 3
			printnum((u_long)lx, 10); break;
E 3
I 3
			kdbprintnum((u_long)lx, 10); break;
E 3
E 2
		case 'O':
D 2
			printnum(lx, 8); break;
E 2
I 2
D 3
			printnum((u_long)lx, 8); break;
E 3
I 3
			kdbprintnum((u_long)lx, 8); break;
E 3
E 2
		case 'Q':
D 2
			printnum(lx, -8); break;
E 2
I 2
D 3
			printnum((u_long)lx, -8); break;
E 3
I 3
			kdbprintnum((u_long)lx, -8); break;
E 3
E 2
		case 'X':
D 2
			printnum(lx, 16); break;
E 2
I 2
D 3
			printnum((u_long)lx, 16); break;
E 3
I 3
			kdbprintnum((u_long)lx, 16); break;
E 3
E 2
		case 'Z':
D 2
			printnum(lx, -16); break;
E 2
I 2
D 3
			printnum((u_long)lx, -16); break;
E 3
I 3
			kdbprintnum((u_long)lx, -16); break;
E 3
E 2
		case 'c':
D 3
			printc(x); break;
E 3
I 3
			kdbprintc(x); break;
E 3
		case 's':
			s=(char *)lx; break;
		case 'm':
			break;
		case 'M':
			width=x; break;
		case 'T': case 't':
			if (c=='T')
				width=x;
			else
				dptr--;
			if (width)
D 3
				width -= charpos()%width;
E 3
I 3
				width -= kdbcharpos()%width;
E 3
			break;
		default:
D 3
			printc(c); dptr--;
E 3
I 3
			kdbprintc(c); dptr--;
E 3
			break;
		}
		if (s==0) {
D 3
			*digitptr=0; s=digits;
E 3
I 3
			*kdbdigitptr=0; s=digits;
E 3
		}
		n=strlen(s);
		n=(prec<n && prec>=0 ? prec : n);
		width -= n;
		if (adj=='r')
			while (width-- > 0)
D 3
				printc(SP);
E 3
I 3
				kdbprintc(SP);
E 3
		while (n--)
D 3
			printc(*s++);
E 3
I 3
			kdbprintc(*s++);
E 3
		while (width-- > 0)
D 3
			printc(SP);
		digitptr=digits;
E 3
I 3
			kdbprintc(SP);
		kdbdigitptr=digits;
E 3
	}
}

static
D 3
convert(cp)
E 3
I 3
kdbconvert(cp)
E 3
	register char **cp;
{
	register char c;
	int n;

	n=0;
	while (((c = *(*cp)++)>='0') && c<='9')
		n=n*10+c-'0';
	(*cp)--;
	return (n);
}

static
D 3
printnum(n, base)
E 3
I 3
kdbprintnum(n, base)
E 3
D 2
	register POS n;
E 2
I 2
	register u_long n;
E 2
{
	register char *dptr;
	char digs[15];

	dptr=digs;
	if (base<0) {
		base = -base;
		if ((long)n<0) {
			n = -n;
D 3
			*digitptr++ = '-';
E 3
I 3
			*kdbdigitptr++ = '-';
E 3
		}
	}
	while (n) {
		*dptr++ = n%base;
		n /= base;
	}
	if (dptr==digs)
		*dptr++=0;
	while (dptr!=digs) {
		n = *--dptr;
D 3
		*digitptr++ = (n+(n<=9 ? '0' : 'a'-10));
E 3
I 3
		*kdbdigitptr++ = (n+(n<=9 ? '0' : 'a'-10));
E 3
	}
}

D 3
endline()
E 3
I 3
kdbendline()
E 3
{

D 3
	if (maxpos <= charpos())
		printf("\n");
E 3
I 3
	if (kdbmaxpos <= kdbcharpos())
		kdbprintf("\n");
E 3
}
E 1
