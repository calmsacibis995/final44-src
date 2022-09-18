h61729
s 00136/00136/00188
d D 7.6 90/05/03 17:47:27 sklower 6 5
c first crack at torek changes, may need bug fixes
e
s 00006/00007/00318
d D 7.5 89/05/29 22:05:59 mckusick 5 4
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00046/00040/00279
d D 7.4 86/12/15 20:26:46 sam 4 3
c lint
e
s 00032/00023/00287
d D 7.3 86/11/23 13:36:00 sam 3 2
c move machine dependencies to ../machine/kdbparam.h
e
s 00001/00001/00309
d D 7.2 86/11/20 14:43:17 sam 2 1
c no more TRUE|FALSE
e
s 00310/00000/00000
d D 7.1 86/11/20 12:22:02 sam 1 0
c date and time created 86/11/20 12:22:02 by sam
e
u
U
t
T
I 1
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 4

#include "../kdb/defs.h"

D 6
char	*BADSYM;
char	*BADVAR;
char	*BADKET;
char	*BADSYN;
char	*NOCFN;
char	*NOADR;
char	*BADLOC;
E 6
I 6
char	*kdbBADSYM;
char	*kdbBADVAR;
char	*kdbBADKET;
char	*kdbBADSYN;
char	*kdbNOCFN;
char	*kdbNOADR;
char	*kdbBADLOC;
E 6

D 6
ADDR	lastframe;
ADDR	savlastf;
ADDR	savframe;
ADDR	savpc;
ADDR	callpc;
E 6
I 6
ADDR	kdblastframe;
ADDR	kdbsavlastf;
ADDR	kdbsavframe;
ADDR	kdbsavpc;
ADDR	kdbcallpc;
E 6

D 6
char	*lp;
int	radix;
char	isymbol[1024];
E 6
I 6
char	*kdblp;
int	kdbradix;
char	kdbisymbol[1024];
E 6

D 6
char	lastc, peekc;
E 6
I 6
char	kdblastc, kdbpeekc;
E 6

D 6
long	ditto;
long	expv;
E 6
I 6
long	kdbditto;
long	kdbexpv;
E 6

I 4
static long
D 6
round(a,b)
E 6
I 6
kdbround(a,b)
E 6
	register long a, b;
{
	register long w;

	w = (a/b)*b;
	if (a!=w)
		w += b;
	return (w);
}

E 4
/* term | term dyadic expr |  */
D 6
expr(a)
E 6
I 6
kdbexpr(a)
E 6
{
	register rc;
	register long lhs;

D 4
	rdc(); lp--; rc=term(a);
E 4
I 4
D 6
	(void) rdc(); lp--; rc=term(a);
E 6
I 6
	(void) kdbrdc(); kdblp--; rc=kdbterm(a);
E 6
E 4

	while (rc) {
D 6
		lhs = expv;
		switch ((int)readchar()) {
E 6
I 6
		lhs = kdbexpv;
		switch ((int)kdbreadchar()) {
E 6
		case '+':
D 4
			term(a|1); expv += lhs; break;
E 4
I 4
D 6
			(void) term(a|1); expv += lhs; break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv += lhs; break;
E 6
E 4
		case '-':
D 4
			term(a|1); expv = lhs - expv; break;
E 4
I 4
D 6
			(void) term(a|1); expv = lhs - expv; break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv = lhs - kdbexpv; break;
E 6
E 4
		case '#':
D 4
			term(a|1); expv = round(lhs,expv); break;
E 4
I 4
D 6
			(void) term(a|1); expv = round(lhs,expv); break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv = kdbround(lhs,kdbexpv); break;
E 6
E 4
		case '*':
D 4
			term(a|1); expv *= lhs; break;
E 4
I 4
D 6
			(void) term(a|1); expv *= lhs; break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv *= lhs; break;
E 6
E 4
		case '%':
D 4
			term(a|1); expv = lhs/expv; break;
E 4
I 4
D 6
			(void) term(a|1); expv = lhs/expv; break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv = lhs/kdbexpv; break;
E 6
E 4
		case '&':
D 4
			term(a|1); expv &= lhs; break;
E 4
I 4
D 6
			(void) term(a|1); expv &= lhs; break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv &= lhs; break;
E 6
E 4
		case '|':
D 4
			term(a|1); expv |= lhs; break;
E 4
I 4
D 6
			(void) term(a|1); expv |= lhs; break;
E 6
I 6
			(void) kdbterm(a|1); kdbexpv |= lhs; break;
E 6
E 4
		case ')':
			if ((a&2)==0)
D 6
				error(BADKET);
E 6
I 6
				kdberror(kdbBADKET);
E 6
		default:
D 6
			lp--;
E 6
I 6
			kdblp--;
E 6
			return (rc);
		}
	}
	return (rc);
}

/* item | monadic item | (expr) | */
static
D 6
term(a)
E 6
I 6
kdbterm(a)
E 6
{

D 6
	switch ((int)readchar()) {
E 6
I 6
	switch ((int)kdbreadchar()) {
E 6
	case '*':
D 4
		term(a|1); expv=chkget(expv,DSP);
E 4
I 4
D 6
		(void) term(a|1); expv=chkget(expv,DSP);
E 6
I 6
		(void) kdbterm(a|1); kdbexpv=kdbchkget(kdbexpv,DSP);
E 6
E 4
		return(1);
	case '@':
D 4
		term(a|1); expv=chkget(expv,ISP);
E 4
I 4
D 6
		(void) term(a|1); expv=chkget(expv,ISP);
E 6
I 6
		(void) kdbterm(a|1); kdbexpv=kdbchkget(kdbexpv,ISP);
E 6
E 4
		return(1);
	case '-':
D 4
		term(a|1); expv = -expv;
E 4
I 4
D 6
		(void) term(a|1); expv = -expv;
E 6
I 6
		(void) kdbterm(a|1); kdbexpv = -kdbexpv;
E 6
E 4
		return(1);
	case '~':
D 4
		term(a|1); expv = ~expv;
E 4
I 4
D 6
		(void) term(a|1); expv = ~expv;
E 6
I 6
		(void) kdbterm(a|1); kdbexpv = ~kdbexpv;
E 6
E 4
		return(1);
	case '#':
D 4
		term(a|1); expv = !expv;
E 4
I 4
D 6
		(void) term(a|1); expv = !expv;
E 6
I 6
		(void) kdbterm(a|1); kdbexpv = !kdbexpv;
E 6
E 4
		return(1);
	case '(':
D 4
		expr(2);
E 4
I 4
D 6
		(void) expr(2);
E 4
		if (*lp!=')')
			error(BADSYN);
		lp++;
E 6
I 6
		(void) kdbexpr(2);
		if (*kdblp!=')')
			kdberror(kdbBADSYN);
		kdblp++;
E 6
		return(1);
	}
D 6
	lp--;
	return (item(a));
E 6
I 6
	kdblp--;
	return (kdbitem(a));
E 6
}

/* name [ . local ] | number | . | ^ | <var | <register | 'x | | */
static
D 6
item(a)
E 6
I 6
kdbitem(a)
E 6
{
	register base, d, regptr;
	char savc;
	register long frame;
	register struct nlist *symp;

D 4
	readchar();
E 4
I 4
D 6
	(void) readchar();
E 4
	if (symchar(0)) {
		readsym();
		if (lastc=='.') {
			frame = pcb.pcb_fp; lastframe = 0;
D 3
			callpc= pcb.pcb_pc;
			while (errflg==0) {
			    savpc=callpc;
			    findsym(callpc,ISYM);
			    if (eqsym(cursym->n_un.n_name,isymbol,'~'))
				    break;
			    callpc=get(frame-8, DSP);
			    lastframe=frame;
			    frame=get(frame, DSP)&ALIGN;
			    if (frame==0)
				    error(NOCFN);
E 3
I 3
			callpc = pcb.pcb_pc;
			while (!errflg) {
				savpc = callpc;
D 4
				findsym(callpc,ISYM);
E 4
I 4
				(void) findsym((long)callpc,ISYM);
E 4
				if (eqsym(cursym->n_un.n_name,isymbol,'~'))
E 6
I 6
	(void) kdbreadchar();
	if (kdbsymchar(0)) {
		kdbreadsym();
		if (kdblastc=='.') {
			frame = kdbpcb.pcb_fp; kdblastframe = 0;
			kdbcallpc = kdbpcb.pcb_pc;
			while (!kdberrflg) {
				kdbsavpc = kdbcallpc;
				(void) kdbfindsym((long)kdbcallpc,ISYM);
				if (kdbeqsym(kdbcursym->n_un.n_name,kdbisymbol,'~'))
E 6
					break;
D 6
				callpc = getprevpc(frame);
				lastframe = frame;
E 6
I 6
				kdbcallpc = getprevpc(frame);
				kdblastframe = frame;
E 6
				frame = getprevframe(frame);
				if (frame == NOFRAME)
D 6
					error(NOCFN);
E 6
I 6
					kdberror(kdbNOCFN);
E 6
E 3
			}
D 3
			savlastf=lastframe; savframe=frame;
E 3
I 3
D 6
			savlastf = lastframe; savframe = frame;
E 3
D 4
			readchar();
E 4
I 4
			(void) readchar();
E 4
			if (symchar(0))
				chkloc(expv=frame);
		} else if ((symp=lookup(isymbol))==0)
			error(BADSYM);
E 6
I 6
			kdbsavlastf = kdblastframe; kdbsavframe = frame;
			(void) kdbreadchar();
			if (kdbsymchar(0))
				kdbchkloc(kdbexpv=frame);
		} else if ((symp=kdblookup(kdbisymbol))==0)
			kdberror(kdbBADSYM);
E 6
		else
D 6
			expv = symp->n_value;
		lp--;
E 6
I 6
			kdbexpv = symp->n_value;
		kdblp--;
E 6
D 3
	} else if (getnum())
		;
	else if (lastc=='.') {
E 3
I 3
		return (1);
	}
D 6
	if (getnum())
E 6
I 6
	if (kdbgetnum())
E 6
		return (1);
D 6
	switch (lastc) {
E 6
I 6
	switch (kdblastc) {
E 6
	case '.':
E 3
D 4
		readchar();
E 4
I 4
D 6
		(void) readchar();
E 4
		if (symchar(0)) {
			lastframe=savlastf; callpc=savpc;
D 4
			chkloc(savframe);
E 4
I 4
			chkloc((long)savframe);
E 6
I 6
		(void) kdbreadchar();
		if (kdbsymchar(0)) {
			kdblastframe=kdbsavlastf; kdbcallpc=kdbsavpc;
			kdbchkloc((long)kdbsavframe);
E 6
E 4
		} else
D 6
			expv=dot;
		lp--;
E 6
I 6
			kdbexpv=kdbdot;
		kdblp--;
E 6
D 3
	} else if (lastc=='"')
E 3
I 3
		break;
	case '"':
E 3
D 6
		expv=ditto;
E 6
I 6
		kdbexpv=kdbditto;
E 6
D 3
	else if (lastc=='+')
E 3
I 3
		break;
	case '+':
E 3
D 6
		expv=inkdot(dotinc);
E 6
I 6
		kdbexpv=kdbinkdot(kdbdotinc);
E 6
D 3
	else if (lastc=='^')
E 3
I 3
		break;
	case '^':
E 3
D 6
		expv=inkdot(-dotinc);
E 6
I 6
		kdbexpv=kdbinkdot(-kdbdotinc);
E 6
D 3
	else if (lastc=='<') {
E 3
I 3
		break;
	case '<':
E 3
D 6
		savc=rdc();
		if ((regptr=getreg(savc)) != -1)
			expv = *(int *)regptr;
		else if ((base=varchk(savc)) != -1)
			expv=var[base];
E 6
I 6
		savc=kdbrdc();
		if ((regptr=kdbgetreg(savc)) != -1)
			kdbexpv = *(int *)regptr;
		else if ((base=kdbvarchk(savc)) != -1)
			kdbexpv=kdbvar[base];
E 6
		else
D 6
			error(BADVAR);
E 6
I 6
			kdberror(kdbBADVAR);
E 6
D 3
	} else if (lastc=='\'') {
E 3
I 3
		break;
	case '\'':
E 3
D 6
		d=4; expv=0;
		while (quotchar()) {
E 6
I 6
		d=4; kdbexpv=0;
		while (kdbquotchar()) {
E 6
		    if (d--) {
D 6
		         expv <<= 8;
			 expv |= lastc;
E 6
I 6
		         kdbexpv <<= 8;
			 kdbexpv |= kdblastc;
E 6
		    } else
D 6
			error(BADSYN);
E 6
I 6
			kdberror(kdbBADSYN);
E 6
		}
D 3
	} else if (a)
		error(NOADR);
	else {
E 3
I 3
		break;
	default:
		if (a)
D 6
			error(NOADR);
E 3
		lp--;
E 6
I 6
			kdberror(kdbNOADR);
		kdblp--;
E 6
		return(0);
	}
	return (1);
}

/* service routines for expression reading */
static
D 6
getnum()
E 6
I 6
kdbgetnum()
E 6
{
	register base,d,frpt;
D 5
	union { float r; long i;} real;
E 5

D 6
	if (!isdigit(lastc))
E 6
I 6
	if (!isdigit(kdblastc))
E 6
		return (0);
D 6
	if ((base = radix) < 0)
E 6
I 6
	if ((base = kdbradix) < 0)
E 6
		base = -base;
D 6
	expv = 0;
	while (base>10 ? isxdigit(lastc) : isdigit(lastc)) {
E 6
I 6
	kdbexpv = 0;
	while (base>10 ? isxdigit(kdblastc) : isdigit(kdblastc)) {
E 6
		register m = MAXINT/base;

D 6
		if (expv>m)		/* avoid overflow */
			expv = (expv-m)*base+m*base;
E 6
I 6
		if (kdbexpv>m)		/* avoid overflow */
			kdbexpv = (kdbexpv-m)*base+m*base;
E 6
		else
D 6
			expv *= base;
		if ((d=convdig(lastc))>=base || d<0)
			error(BADSYN);
D 4
		expv += d; readchar();
E 4
I 4
		expv += d; (void) readchar();
E 4
		if (expv==0) {
			if (lastc=='x' || lastc=='X') {
D 4
				 base=16; readchar();
E 4
I 4
				 base=16; (void) readchar();
E 4
			} else if (lastc=='t' || lastc=='T') {
D 4
				 base=10; readchar();
E 4
I 4
				 base=10; (void) readchar();
E 4
			} else if (lastc=='o' || lastc=='O') {
D 4
				 base=8; readchar();
E 4
I 4
				 base=8; (void) readchar();
E 6
I 6
			kdbexpv *= base;
		if ((d=kdbconvdig(kdblastc))>=base || d<0)
			kdberror(kdbBADSYN);
		kdbexpv += d; (void) kdbreadchar();
		if (kdbexpv==0) {
			if (kdblastc=='x' || kdblastc=='X') {
				 base=16; (void) kdbreadchar();
			} else if (kdblastc=='t' || kdblastc=='T') {
				 base=10; (void) kdbreadchar();
			} else if (kdblastc=='o' || kdblastc=='O') {
				 base=8; (void) kdbreadchar();
E 6
E 4
			}
		}
	}
D 6
	if (lastc=='.' && (base==10 || expv==0)) {
E 6
I 6
	if (kdblastc=='.' && (base==10 || kdbexpv==0)) {
E 6
D 5
		real.r=expv; frpt=0; base=10;
E 5
I 5
		frpt=0; base=10;
E 5
D 6
		while (isdigit(readchar())) {
E 6
I 6
		while (isdigit(kdbreadchar())) {
E 6
D 5
			real.r *= base; frpt++;
			real.r += lastc-'0';
E 5
I 5
			if (frpt)
				continue;
			frpt++;
D 6
			if (lastc - '0' >= 5)
				expv++;
E 6
I 6
			if (kdblastc - '0' >= 5)
				kdbexpv++;
E 6
E 5
		}
D 5
		while (frpt--)
			real.r /= base;
		expv = real.i;
E 5
	}
D 6
	peekc=lastc;
E 6
I 6
	kdbpeekc=kdblastc;
E 6
	return (1);
}

static
D 6
readsym()
E 6
I 6
kdbreadsym()
E 6
{
	register char *p;

D 6
	p = isymbol;
E 6
I 6
	p = kdbisymbol;
E 6
	do {
D 4
	    if (p < &isymbol[sizeof(isymbol)-1])
		    *p++ = lastc;
	    readchar();
E 4
I 4
D 6
		if (p < &isymbol[sizeof(isymbol)-1])
			*p++ = lastc;
		(void) readchar();
E 4
	} while (symchar(1));
E 6
I 6
		if (p < &kdbisymbol[sizeof(kdbisymbol)-1])
			*p++ = kdblastc;
		(void) kdbreadchar();
	} while (kdbsymchar(1));
E 6
	*p++ = 0;
}

static
D 6
convdig(c)
E 6
I 6
kdbconvdig(c)
E 6
	char c;
{
	if (isdigit(c))
		return (c-'0');
	if (isxdigit(c))
		return (c-'a'+10);
	return (-1);
}

static
D 6
symchar(dig)
E 6
I 6
kdbsymchar(dig)
E 6
{

D 6
	if (lastc=='\\') {
D 4
		readchar();
E 4
I 4
		(void) readchar();
E 6
I 6
	if (kdblastc=='\\') {
		(void) kdbreadchar();
E 6
E 4
D 2
		return (TRUE);
E 2
I 2
		return (1);
E 2
	}
D 6
	return (isalpha(lastc) || lastc=='_' || dig && isdigit(lastc));
E 6
I 6
	return (isalpha(kdblastc) || kdblastc=='_' || dig && isdigit(kdblastc));
E 6
}

D 6
varchk(name)
E 6
I 6
kdbvarchk(name)
E 6
	register name;
{
	if (isdigit(name))
		return (name-'0');
	if (isalpha(name))
		return ((name&037)-1+10);
	return (-1);
}

static
D 6
chkloc(frame)
E 6
I 6
kdbchkloc(frame)
E 6
	long frame;
{

D 6
	readsym();
E 6
I 6
	kdbreadsym();
E 6
	do {
D 6
		if (localsym(frame)==0)
			error(BADLOC);
		expv=localval;
	} while (!eqsym(cursym->n_un.n_name,isymbol,'~'));
E 6
I 6
		if (kdblocalsym(frame)==0)
			kdberror(kdbBADLOC);
		kdbexpv=kdblocalval;
	} while (!kdbeqsym(kdbcursym->n_un.n_name,kdbisymbol,'~'));
E 6
}

D 6
eqsym(s1, s2, c)
E 6
I 6
kdbeqsym(s1, s2, c)
E 6
	register char *s1, *s2;
{

D 6
	if (streq(s1,s2))
E 6
I 6
	if (kdbstreq(s1,s2))
E 6
		return (1);
D 6
	if (*s1 == c && streq(s1+1, s2))
E 6
I 6
	if (*s1 == c && kdbstreq(s1+1, s2))
E 6
		return (1);
	return (0);
}

static
D 6
streq(s1, s2)
E 6
I 6
kdbstreq(s1, s2)
E 6
	char *s1, *s2;
{

	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (1);
	return (0);
D 4
}

static
round(a,b)
	register long a, b;
{
	register long w;

	w = (a/b)*b;
	if (a!=w)
		w += b;
	return (w);
E 4
}
E 1
