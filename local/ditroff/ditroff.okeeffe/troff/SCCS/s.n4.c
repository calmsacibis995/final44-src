h56902
s 00002/00000/00774
d D 2.2 90/11/30 14:22:48 sklower 3 2
c fix that Dave Slattengren made concerning ligatures
e
s 00168/00130/00606
d D 2.1 85/07/18 14:23:25 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00736/00000/00000
d D 1.1 85/07/17 17:54:30 jaap 1 0
c date and time created 85/07/17 17:54:30 by jaap
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
D 2

E 2
I 2
/*      @(#)n4.c	1.1     */
E 2
#include	<ctype.h>
#include "tdef.h"
D 2
extern
#include "d.h"
extern
#include "v.h"
E 2
#ifdef NROFF
D 2
extern
E 2
#include "tw.h"
#endif
D 2
#include "s.h"
E 2
I 2
#include "ext.h"
#include <sgtty.h>
E 2
/*
D 2
troff4.c
E 2
I 2
 * troff4.c
 * 
 * number registers, conversion, arithmetic
 */
E 2

D 2
number registers, conversion, arithmetic
*/
E 2

D 2
#include <sgtty.h>
#include "ext.h"

E 2
int	regcnt = NNAMES;
int	falsef	= 0;	/* on if inside false branch of if */
I 2
#define	NHASH(i)	((i>>6)^i)&0177
struct	numtab	*nhash[128];	/* 128 == the 0177 on line above */
E 2

setn()
{
	register i, j;
D 2
	tchar ii;
E 2
I 2
	register tchar ii;
E 2
	int	f;

	f = nform = 0;
I 3
	lgf++;					/* don;t catch ligatures */
E 3
	if ((i = cbits(ii = getach())) == '+')
		f = 1;
	else if (i == '-')
		f = -1;
	else 
		ch = ii;
I 3
	lgf--;					/* ok, catch `em again */
E 3
	if (falsef)
		f = 0;
	if ((i = getsn()) == 0)
		return;
	if ((i & 0177) == '.')
		switch (i >> BYTE) {
		case 's': 
			i = pts;	
			break;
		case 'v': 
			i = lss;		
			break;
		case 'f': 
			i = font;	
			break;
		case 'p': 
			i = pl;		
			break;
		case 't':  
			i = findt1();	
			break;
		case 'o': 
			i = po;		
			break;
		case 'l': 
			i = ll;		
			break;
		case 'i': 
			i = in;		
			break;
		case '$': 
			i = frame->nargs;		
			break;
		case 'A': 
			i = ascii;		
			break;
		case 'c': 
D 2
			i = v.cd;		
E 2
I 2
			i = numtab[CD].val;		
E 2
			break;
		case 'n': 
			i = lastl;		
			break;
		case 'a': 
			i = ralss;		
			break;
		case 'h': 
			i = dip->hnl;	
			break;
		case 'd':
			if (dip != d)
				i = dip->dnl; 
			else 
D 2
				i = v.nl;
E 2
I 2
				i = numtab[NL].val;
E 2
			break;
		case 'u': 
			i = fi;		
			break;
		case 'j': 
			i = ad + 2 * admod;	
			break;
		case 'w': 
D 2
			i = width(*(pinchar-1));	/* XXX */
E 2
I 2
			i = widthp;
E 2
			break;
		case 'x': 
			i = nel;	
			break;
		case 'y': 
			i = un;		
			break;
		case 'T': 
			i = dotT;		
			break; /*-Tterm used in nroff*/
		case 'V': 
			i = VERT;		
			break;
		case 'H': 
			i = HOR;		
			break;
		case 'k': 
			i = ne;		
			break;
		case 'P': 
			i = print;		
			break;
		case 'L': 
			i = ls;		
			break;
		case 'R': 
			i = NN - regcnt;	
			break;
		case 'z': 
			i = dip->curd;
D 2
			cbuf[0] = i & BMASK;
			cbuf[1] = (i >> BYTE) & BMASK;
			cbuf[2] = 0;
			cp = cbuf;
E 2
I 2
			*pbp++ = (i >> BYTE) & BYTEMASK;
			*pbp++ = i & BYTEMASK;
E 2
			return;
		case 'b': 
			i = bdtab[font];
			break;
D 2
		case 'D':		/* Dialect, hyphenation algoritm jna */
			i = hyalg;
E 2
I 2
		case 'F':
			cpushback(cfname[ifi]);
			return;
		case 'D':
			i = hyalg;	/* "Dialect" register (jaap) */
E 2
			break;
		case 'e':
D 2
			i = thresh;
E 2
I 2
			i = thresh;	/* (jaap) */
E 2
			break;

		default:
			goto s0;
		}
	else {
s0:
		if ((j = findr(i)) == -1)
			i = 0;
		else {
D 2
			i = (vlist[j] = (vlist[j] + inc[j] * f));
			nform = fmt[j];
E 2
I 2
			i = numtab[j].val = (numtab[j].val+numtab[j].inc*f);
			nform = numtab[j].fmt;
E 2
		}
	}
D 2
	setn1(i);
	cp = cbuf;
E 2
I 2
	setn1(i, nform, (tchar) 0);
E 2
}

I 2
tchar	numbuf[17];
tchar	*numbufp;
E 2

D 2
setn1(i)
E 2
I 2
wrc(i)
tchar i;
{
	if (numbufp >= &numbuf[16])
		return(0);
	*numbufp++ = i;
	return(1);
}



/* insert into input number i, in format form, with size-font bits bits */
setn1(i, form, bits)
E 2
int	i;
I 2
tchar bits;
E 2
{
	extern int	wrc();

D 2
	cp = cbuf;
	nrbits = 0;
E 2
I 2
	numbufp = numbuf;
	nrbits = bits;
	nform = form;
E 2
	fnumb(i, wrc);
D 2
	*cp = 0;
	cp = cbuf;
E 2
I 2
	*numbufp = 0;
	pushback(numbuf);
E 2
}


I 2
nrehash()
{
	register struct numtab *p;
	register i;

	for (i=0; i<128; i++)
		nhash[i] = 0;
	for (p=numtab; p < &numtab[NN]; p++)
		p->link = 0;
	for (p=numtab; p < &numtab[NN]; p++) {
		if (p->r == 0)
			continue;
		i = NHASH(p->r);
		p->link = nhash[i];
		nhash[i] = p;
	}
}

nunhash(rp)
register struct numtab *rp;
{	
	register struct numtab *p;
	register struct numtab **lp;

	if (rp->r == 0)
		return;
	lp = &nhash[NHASH(rp->r)];
	p = *lp;
	while (p) {
		if (p == rp) {
			*lp = p->link;
			p->link = 0;
			return;
		}
		lp = &p->link;
		p = p->link;
	}
}

E 2
findr(i)
register int	i;
{
D 2
	register j;
	register int *p;
E 2
I 2
	register struct numtab *p;
	register h = NHASH(i);
E 2

	if (i == 0)
		return(-1);
D 2
	for (p = r; p < &r[NN]; p++) {
		if (i == *p)
			break;
	}
	if (p != &r[NN])
		return(p - r);
	for (p = r; p < &r[NN]; p++) {
		if (*p == 0) {
			*p = i;
E 2
I 2
	for (p = nhash[h]; p; p = p->link)
		if (i == p->r)
			return(p - numtab);
	for (p = numtab; p < &numtab[NN]; p++) {
		if (p->r == 0) {
			p->r = i;
			p->link = nhash[h];
			nhash[h] = p;
E 2
			regcnt++;
D 2
			break;
E 2
I 2
			return(p - numtab);
E 2
		}
	}
D 2
	if (p == &r[NN]) {
		fprintf(stderr, "troff: too many number registers (%d).\n", NN);
		done2(04); 
	}
	return(p - r);
E 2
I 2
	errprint("too many number registers (%d).", NN);
	done2(04); 
	/* NOTREACHED */
E 2
}

usedr(i)	/* returns -1 if nr i has never been used */
register int	i;
{
D 2
	register j;
	register int *p;
E 2
I 2
	register struct numtab *p;
E 2

	if (i == 0)
		return(-1);
D 2
	for (p = r; p < &r[NN]; p++) {
		if (i == *p)
			break;
	}
	if (p != &r[NN])
		return(p - r);
	else
		return -1;
E 2
I 2
	for (p = nhash[NHASH(i)]; p; p = p->link)
		if (i == p->r)
			return(p - numtab);
	return -1;
E 2
}


fnumb(i, f)
D 2
int	i, (*f)();
E 2
I 2
register int	i, (*f)();
E 2
{
	register j;

	j = 0;
	if (i < 0) {
		j = (*f)('-' | nrbits);
		i = -i;
	}
	switch (nform) {
	default:
	case '1':
	case 0: 
D 2
		return(decml(i, f) + j);
E 2
I 2
		return decml(i, f) + j;
		break;
E 2
	case 'i':
	case 'I': 
D 2
		return(roman(i, f) + j);
E 2
I 2
		return roman(i, f) + j;
		break;
E 2
	case 'a':
	case 'A': 
D 2
		return(abc(i, f) + j);
E 2
I 2
		return abc(i, f) + j;
		break;
E 2
	}
}


decml(i, f)
D 2
int	i, (*f)();
E 2
I 2
register int	i, (*f)();
E 2
{
	register j, k;

	k = 0;
	nform--;
	if ((j = i / 10) || (nform > 0))
		k = decml(j, f);
	return(k + (*f)((i % 10 + '0') | nrbits));
}


roman(i, f)
int	i, (*f)();
{

	if (!i)
		return((*f)('0' | nrbits));
	if (nform == 'i')
		return(roman0(i, f, "ixcmz", "vldw"));
	else 
		return(roman0(i, f, "IXCMZ", "VLDW"));
}


roman0(i, f, onesp, fivesp)
int	i, (*f)();
char	*onesp, *fivesp;
{
	register q, rem, k;

	k = 0;
	if (!i)
		return(0);
	k = roman0(i / 10, f, onesp + 1, fivesp + 1);
	q = (i = i % 10) / 5;
	rem = i % 5;
	if (rem == 4) {
		k += (*f)(*onesp | nrbits);
		if (q)
			i = *(onesp + 1);
		else 
			i = *fivesp;
		return(k += (*f)(i | nrbits));
	}
	if (q)
		k += (*f)(*fivesp | nrbits);
	while (--rem >= 0)
		k += (*f)(*onesp | nrbits);
	return(k);
}


abc(i, f)
int	i, (*f)();
{
	if (!i)
		return((*f)('0' | nrbits));
	else 
		return(abc0(i - 1, f));
}


abc0(i, f)
int	i, (*f)();
{
	register j, k;

	k = 0;
	if (j = i / 26)
		k = abc0(j - 1, f);
	return(k + (*f)((i % 26 + nform) | nrbits));
}

D 2

wrc(i)
tchar i;
{
	if (cp >= &cbuf[NC])
		return(0);
	*cp++ = i;
	return(1);
}


E 2
long	atoi0()
{
	register c, k, cnt;
D 2
	tchar ii;
E 2
I 2
	register tchar ii;
E 2
	long	i, acc;
	extern long	ckph();

	i = 0; 
	acc = 0;
	nonumb = 0;
	cnt = -1;
a0:
	cnt++;
	ii = getch();
	c = cbits(ii);
	switch (c) {
	default:
		ch = ii;
		if (cnt)
			break;
	case '+':
		i = ckph();
		if (nonumb)
			break;
		acc += i;
		goto a0;
	case '-':
		i = ckph();
		if (nonumb)
			break;
		acc -= i;
		goto a0;
	case '*':
		i = ckph();
		if (nonumb)
			break;
		acc *= i;
		goto a0;
	case '/':
		i = ckph();
		if (nonumb)
			break;
		if (i == 0) {
			flusho();
D 2
			fprintf(stderr, "troff: divide by zero.\n");
E 2
I 2
			errprint("divide by zero.");
E 2
			acc = 0;
		} else 
			acc /= i;
		goto a0;
	case '%':
		i = ckph();
		if (nonumb)
			break;
		acc %= i;
		goto a0;
	case '&':	/*and*/
		i = ckph();
		if (nonumb)
			break;
		if ((acc > 0) && (i > 0))
			acc = 1; 
		else 
			acc = 0;
		goto a0;
	case ':':	/*or*/
		i = ckph();
		if (nonumb)
			break;
		if ((acc > 0) || (i > 0))
			acc = 1; 
		else 
			acc = 0;
		goto a0;
	case '=':
		if (cbits(ii = getch()) != '=')
			ch = ii;
		i = ckph();
		if (nonumb) {
			acc = 0; 
			break;
		}
		if (i == acc)
			acc = 1;
		else 
			acc = 0;
		goto a0;
	case '>':
		k = 0;
		if (cbits(ii = getch()) == '=')
			k++; 
		else 
			ch = ii;
		i = ckph();
		if (nonumb) {
			acc = 0; 
			break;
		}
		if (acc > (i - k))
			acc = 1; 
		else 
			acc = 0;
		goto a0;
	case '<':
		k = 0;
		if (cbits(ii = getch()) == '=')
			k++; 
		else 
			ch = ii;
		i = ckph();
		if (nonumb) {
			acc = 0; 
			break;
		}
		if (acc < (i + k))
			acc = 1; 
		else 
			acc = 0;
		goto a0;
	case ')': 
		break;
	case '(':
		acc = atoi0();
		goto a0;
	}
	return(acc);
}


long	ckph()
{
D 2
	tchar i;
	long	j;
E 2
I 2
	register tchar i;
	register long	j;
E 2
	extern long	atoi0();
	extern long	atoi1();

	if (cbits(i = getch()) == '(')
		j = atoi0();
	else {
D 2
		ch = i;
		j = atoi1();
E 2
I 2
		j = atoi1(i);
E 2
	}
	return(j);
}


D 2
long	atoi1()
E 2
I 2
long	atoi1(ii)
register tchar ii;
E 2
{
	register i, j, digits;
D 2
	tchar ii;
	long	acc;
E 2
I 2
	register long	acc;
E 2
	int	neg, abs, field;

	neg = abs = field = digits = 0;
	acc = 0;
D 2
a0:
	ii = getch();
	i = cbits(ii);
	switch (i) {
	default:
		ch = ii;
E 2
I 2
	for (;;) {
		i = cbits(ii);
		switch (i) {
		default:
			break;
		case '+':
			ii = getch();
			continue;
		case '-':
			neg = 1;
			ii = getch();
			continue;
		case '|':
			abs = 1 + neg;
			neg = 0;
			ii = getch();
			continue;
		}
E 2
		break;
D 2
	case '+':
		goto a0;
	case '-':
		neg = 1;
		goto a0;
	case '|':
		abs = 1 + neg;
		neg = 0;
		goto a0;
E 2
	}
a1:
D 2
	while (((j = (cbits(ii = getch())) - '0') >= 0) && (j <= 9)) {
E 2
I 2
	while (i >= '0' && i <= '9') {
E 2
		field++;
		digits++;
D 2
		acc = 10 * acc + j;
E 2
I 2
		acc = 10 * acc + i - '0';
		ii = getch();
		i = cbits(ii);
E 2
	}
D 2
	if (cbits(ii) == '.') {
E 2
I 2
	if (i == '.') {
E 2
		field++;
		digits = 0;
I 2
		ii = getch();
		i = cbits(ii);
E 2
		goto a1;
	}
D 2
	ch = ii;
	if (!field)
E 2
I 2
	if (!field) {
		ch = ii;
E 2
		goto a2;
D 2
	ii = getch();
	switch (i = cbits(ii)) {
E 2
I 2
	}
	switch (i) {
E 2
	case 'u':
		i = j = 1;	/* should this be related to HOR?? */
		break;
	case 'v':	/*VSs - vert spacing*/
		j = lss;
		i = 1;
		break;
	case 'm':	/*Ems*/
		j = EM;
		i = 1;
		break;
	case 'n':	/*Ens*/
		j = EM;
#ifndef NROFF
		i = 2;
#endif
#ifdef NROFF
		i = 1;	/*Same as Ems in NROFF*/
#endif
		break;
	case 'p':	/*Points*/
		j = INCH;
		i = 72;
		break;
	case 'i':	/*Inches*/
		j = INCH;
		i = 1;
		break;
	case 'c':	/*Centimeters*/
		/* if INCH is too big, this will overflow */
		j = INCH * 50;
		i = 127;
		break;
	case 'P':	/*Picas*/
		j = INCH;
		i = 6;
		break;
	default:
		j = dfact;
		ch = ii;
		i = dfactd;
	}
	if (neg) 
		acc = -acc;
	if (!noscale) {
		acc = (acc * j) / i;
	}
	if ((field != digits) && (digits > 0))
		while (digits--)
			acc /= 10;
	if (abs) {
		if (dip != d)
			j = dip->dnl; 
		else 
D 2
			j = v.nl;
E 2
I 2
			j = numtab[NL].val;
E 2
		if (!vflag) {
D 2
			j = v.hp = sumhp();	/* XXX */
E 2
I 2
			j = numtab[HP].val;
E 2
		}
		if (abs == 2)
			j = -j;
		acc -= j;
	}
a2:
	nonumb = !field;
	return(acc);
}


caserr()
{
	register i, j;
I 2
	register struct numtab *p;
E 2

	lgf++;
	while (!skip() && (i = getrq()) ) {
D 2
		for (j = NNAMES; j < NN; j++) {  /*NNAMES predefined names*/
			if (i == r[j])
				break;
		}
		if (j != NN) {
			r[j] = vlist[j] = inc[j] = fmt[j] = 0;
			regcnt--;
		}
E 2
I 2
		j = usedr(i);
		if (j < 0)
			continue;
		p = &numtab[j];
		nunhash(p);
		p->r = p->val = p->inc = p->fmt = 0;
		regcnt--;
E 2
	}
}


casenr()
{
	register i, j;

	lgf++;
	skip();
	if ((i = findr(getrq())) == -1)
		goto rtn;
	skip();
D 2
	j = inumb(&vlist[i]);
E 2
I 2
	j = inumb(&numtab[i].val);
E 2
	if (nonumb)
		goto rtn;
D 2
	vlist[i] = j;
E 2
I 2
	numtab[i].val = j;
E 2
	skip();
	j = atoi();
	if (nonumb)
		goto rtn;
D 2
	inc[i] = j;
E 2
I 2
	numtab[i].inc = j;
E 2
rtn:
	return;
}


caseaf()
{
	register i, k;
D 2
	tchar j;
E 2
I 2
	register tchar j;
E 2

	lgf++;
	if (skip() || !(i = getrq()) || skip())
		return;
	k = 0;
	j = getch();
	if (!isalpha(cbits(j))) {
		ch = j;
		while ((j = cbits(getch())) >= '0' &&  j <= '9')
			k++;
	}
	if (!k)
		k = j;
D 2
	fmt[findr(i)] = k & BMASK;
E 2
I 2
	numtab[findr(i)].fmt = k & BYTEMASK;
E 2
}

setaf()	/* return format of number register */
{
	register int i, j;

	i = usedr(getsn());
	if (i == -1)
		return;
D 2
	cp = cbuf;
	if (fmt[i] > 20)	/* it was probably a, A, i or I */
		*cp++ = fmt[i];
E 2
I 2
	if (numtab[i].fmt > 20)	/* it was probably a, A, i or I */
		*pbp++ = numtab[i].fmt;
E 2
	else
D 2
		for (j = (fmt[i] ? fmt[i] : 1); j; j--)
			*cp++ = '0';
	*cp = 0;
	cp = cbuf;
E 2
I 2
		for (j = (numtab[i].fmt ? numtab[i].fmt : 1); j; j--)
			*pbp++ = '0';
E 2
}


vnumb(i)
int	*i;
{
	vflag++;
	dfact = lss;
	res = VERT;
	return(inumb(i));
}


hnumb(i)
int	*i;
{
	dfact = EM;
	res = HOR;
	return(inumb(i));
}


inumb(n)
int	*n;
{
	register i, j, f;
D 2
	tchar ii;
E 2
I 2
	register tchar ii;
E 2

	f = 0;
	if (n) {
		if ((j = cbits(ii = getch())) == '+')
			f = 1;
		else if (j == '-')
			f = -1;
		else 
			ch = ii;
	}
	i = atoi();
	if (n && f)
		i = *n + f * i;
	i = quant(i, res);
	vflag = 0;
	res = dfactd = dfact = 1;
	if (nonumb)
		i = 0;
	return(i);
}


quant(n, m)
int	n, m;
{
	register i, neg;

	neg = 0;
	if (n < 0) {
		neg++;
		n = -n;
	}
	/* better as i = ((n + (m/2))/m)*m */
	i = n / m;
	if ((n - m * i) > (m / 2))
		i += 1;
	i *= m;
	if (neg)
		i = -i;
	return(i);
}


E 1
