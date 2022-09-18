h42062
s 00017/00017/00973
d D 2.3 90/11/03 20:36:09 karels 4 3
c changes from van: use malloc, stdio; in-memory environments
e
s 00001/00001/00989
d D 2.2 87/03/31 16:17:13 jaap 3 2
c added some debugging
e
s 00095/00117/00895
d D 2.1 85/07/18 14:24:02 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 01012/00000/00000
d D 1.1 85/07/17 17:54:34 jaap 1 0
c date and time created 85/07/17 17:54:34 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% (CWI) %E%";
E 4
I 4
/*
static char sccsid[] = "@(#)n5.c	2.2 (CWI) 87/03/31";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
#endif lint
D 2

E 2
#include "tdef.h"
#include <sgtty.h>
D 2
extern
#include "d.h"
extern
#include "v.h"
#include "s.h"
E 2
I 2
#include "ext.h"
E 2

/*
D 2
troff5.c
E 2
I 2
 * troff5.c
 * 
 * misc processing requests
 */
E 2

D 2
misc processing requests
*/

#include "ext.h"
E 2
int	iflist[NIF];
int	ifx;

casead()
{
	register i;

	ad = 1;
	/*leave admod alone*/
	if (skip())
		return;
	switch (i = cbits(getch())) {
	case 'r':	/*right adj, left ragged*/
		admod = 2;
		break;
	case 'l':	/*left adj, right ragged*/
		admod = ad = 0;	/*same as casena*/
		break;
	case 'c':	/*centered adj*/
		admod = 1;
		break;
	case 'b': 
	case 'n':
		admod = 0;
		break;
	case '0': 
	case '2': 
	case '4':
		ad = 0;
	case '1': 
	case '3': 
	case '5':
		admod = (i - '0') / 2;
	}
}


casena()
{
	ad = 0;
}


casefi()
{
	tbreak();
	fi++;
	pendnf = 0;
	lnsize = LNSIZE;
}


casenf()
{
	tbreak();
	fi = 0;
D 2
	/* can't do while oline is only LNSIZE
	lnsize = LNSIZE + WDSIZE;
*/
E 2
}


casers()
{
	dip->nls = 0;
}


casens()
{
	dip->nls++;
}


chget(c)
int	c;
{
	tchar i;

	if (skip() || ismot(i = getch()) || cbits(i) == ' ' || cbits(i) == '\n') {
		ch = i;
		return(c);
	} else 
D 2
		return(i & BMASK);
E 2
I 2
		return(i & BYTEMASK);
E 2
}


casecc()
{
	cc = chget('.');
}


casec2()
{
	c2 = chget('\'');
}


casehc()
{
	ohc = chget(OHC);
}


casetc()
{
	tabc = chget(0);
}


caselc()
{
	dotc = chget(0);
}


casehy()
{
	register i;

	hyf = 1;
	if (skip())
		return;
	noscale++;
	i = atoi();
	noscale = 0;
	if (nonumb)
		return;
	hyf = max(i, 0);
}


casenh()
{
	hyf = 0;
}


max(aa, bb)
int	aa, bb;
{
	if (aa > bb)
		return(aa);
	else 
		return(bb);
}


casece()
{
	register i;

	noscale++;
	skip();
	i = max(atoi(), 0);
	if (nonumb)
		i = 1;
	tbreak();
	ce = i;
	noscale = 0;
}


casein()
{
	register i;

	if (skip())
		i = in1;
	else 
		i = max(hnumb(&in), 0);
	tbreak();
	in1 = in;
	in = i;
	if (!nc) {
		un = in;
		setnel();
	}
}


casell()
{
	register i;

	if (skip())
		i = ll1;
	else 
		i = max(hnumb(&ll), INCH / 10);
	ll1 = ll;
	ll = i;
	setnel();
}


caselt()
{
	register i;

	if (skip())
		i = lt1;
	else 
		i = max(hnumb(&lt), 0);
	lt1 = lt;
	lt = i;
}


caseti()
{
	register i;

	if (skip())
		return;
	i = max(hnumb(&in), 0);
	tbreak();
	un1 = i;
	setnel();
}


casels()
{
	register i;

	noscale++;
	if (skip())
		i = ls1;
	else 
		i = max(inumb(&ls), 1);
	ls1 = ls;
	ls = i;
	noscale = 0;
}


casepo()
{
	register i;

	if (skip())
		i = po1;
	else 
		i = max(hnumb(&po), 0);
	po1 = po;
	po = i;
#ifndef NROFF
	if (!ascii)
		esc += po - po1;
#endif
}


casepl()
{
	register i;

	skip();
	if ((i = vnumb(&pl)) == 0)
		pl = 11 * INCH; /*11in*/
	else 
		pl = i;
D 2
	if (v.nl > pl)
		v.nl = pl;
E 2
I 2
	if (numtab[NL].val > pl)
		numtab[NL].val = pl;
E 2
}


casewh()
{
	register i, j, k;

	lgf++;
	skip();
	i = vnumb((int *)0);
	if (nonumb)
		return;
	skip();
	j = getrq();
	if ((k = findn(i)) != NTRAP) {
		mlist[k] = j;
		return;
	}
	for (k = 0; k < NTRAP; k++)
		if (mlist[k] == 0)
			break;
	if (k == NTRAP) {
		flusho();
D 2
		fprintf(stderr, "troff: cannot plant trap.\n");
E 2
I 2
		errprint("cannot plant trap.");
E 2
		return;
	}
	mlist[k] = j;
	nlist[k] = i;
}


casech()
{
	register i, j, k;

	lgf++;
	skip();
	if (!(j = getrq()))
		return;
	else 
		for (k = 0; k < NTRAP; k++)
			if (mlist[k] == j)
				break;
	if (k == NTRAP)
		return;
	skip();
	i = vnumb((int *)0);
	if (nonumb)
		mlist[k] = 0;
	nlist[k] = i;
}


findn(i)
int	i;
{
	register k;

	for (k = 0; k < NTRAP; k++)
		if ((nlist[k] == i) && (mlist[k] != 0))
			break;
	return(k);
}


casepn()
{
	register i;

	skip();
	noscale++;
D 2
	i = max(inumb(&v.pn), 0);
E 2
I 2
	i = max(inumb(&numtab[PN].val), 0);
E 2
	noscale = 0;
	if (!nonumb) {
		npn = i;
		npnflg++;
	}
}


casebp()
{
	register i;
	register struct s *savframe;

	if (dip != d)
		return;
	savframe = frame;
	skip();
D 2
	if ((i = inumb(&v.pn)) < 0)
E 2
I 2
	if ((i = inumb(&numtab[PN].val)) < 0)
E 2
		i = 0;
	tbreak();
	if (!nonumb) {
		npn = i;
		npnflg++;
	} else if (dip->nls)
		return;
	eject(savframe);
}


D 2
casetm(x) 
int	x;
E 2
I 2
casetm(ab) 
	int ab;
E 2
{
	register i;
	char	tmbuf[NTM];

	lgf++;
	copyf++;
D 2
	if (skip() && x)
		fprintf(stderr, "troff: user Abort.");
E 2
I 2
	skip();
E 2
	for (i = 0; i < NTM - 2; )
		if ((tmbuf[i++] = getch()) == '\n')
			break;
	if (i == NTM - 2)
		tmbuf[i++] = '\n';
	tmbuf[i] = 0;
I 2
D 4
	if (ab)	/* truncate output */
		obufp = obuf;	/* should be a function in n2.c */
E 4
E 2
	flusho();
D 2
	fprintf(stderr, "%s", tmbuf);
E 2
I 2
	fdprintf(stderr, "%s", tmbuf);
E 2
	copyf--;
I 2
	lgf--;
E 2
}


casesp(a)
int	a;
{
	register i, j, savlss;

	tbreak();
	if (dip->nls || trap)
		return;
	i = findt1();
	if (!a) {
		skip();
		j = vnumb((int *)0);
		if (nonumb)
			j = lss;
	} else 
		j = a;
	if (j == 0)
		return;
	if (i < j)
		j = i;
	savlss = lss;
	if (dip != d)
		i = dip->dnl; 
	else 
D 2
		i = v.nl;
E 2
I 2
		i = numtab[NL].val;
E 2
	if ((i + j) < 0)
		j = -i;
	lss = j;
	newline(0);
	lss = savlss;
}


casert()
{
	register a, *p;

	skip();
	if (dip != d)
		p = &dip->dnl; 
	else 
D 2
		p = &v.nl;
E 2
I 2
		p = &numtab[NL].val;
E 2
	a = vnumb(p);
	if (nonumb)
		a = dip->mkline;
	if ((a < 0) || (a >= *p))
		return;
	nb++;
	casesp(a - *p);
}


caseem()
{
	lgf++;
	skip();
	em = getrq();
}


casefl()
{
	tbreak();
	flusho();
}


caseev()
{
	register nxev;
D 2
	extern int	block;
E 2

	if (skip()) {
D 4
e0:
		if (evi == 0)
			return;
		nxev =  evlist[--evi];
		goto e1;
E 4
I 4
		if (evi != 0) {
			ev =  evlist[--evi];
			env = &env_array[ev];
		}
		return;
E 4
	}
	noscale++;
	nxev = atoi();
	noscale = 0;
D 4
	if (nonumb)
		goto e0;
E 4
I 4
	if (nonumb) {
		if (evi != 0) {
			ev =  evlist[--evi];
			env = &env_array[ev];
		}
		return;
	}
E 4
	flushi();
	if ((nxev >= NEV) || (nxev < 0) || (evi >= EVLSZ)) {
		flusho();
D 2
		fprintf(stderr, "troff: cannot do ev.\n");
E 2
I 2
D 3
		errprint("cannot do ev.");
E 3
I 3
		errprint("cannot do ev %d. (evi %d)", nxev, evi);
E 3
E 2
		if (error)
			done2(040);
		else 
			edone(040);
		return;
	}
	evlist[evi++] = ev;
D 4
e1:
	if (ev == nxev)
		return;
D 2
	lseek(ibf, (long)(ev * EVS), 0);
	write(ibf, (char *) & block, EVS);
	lseek(ibf, (long)(nxev * EVS), 0);
	read(ibf, (char *) & block, EVS);
E 2
I 2
	lseek(ibf, ev * (long)sizeof(env), 0);
	write(ibf, (char *) & env, sizeof(env));
	lseek(ibf, nxev * (long)sizeof(env), 0);
	read(ibf, (char *) & env, sizeof(env));
E 4
E 2
	ev = nxev;
I 4
	env = &env_array[ev];
E 4
}


caseel()
{
	if (--ifx < 0) {
		ifx = 0;
		iflist[0] = 0;
	}
	caseif(2);
}


caseie()
{
	if (ifx >= NIF) {
D 2
		fprintf(stderr, "troff: if-else overflow.\n");
E 2
I 2
		errprint("if-else overflow.");
E 2
		ifx = 0;
		edone(040);
	}
	caseif(1);
	ifx++;
}


caseif(x)
int	x;
{
	extern int falsef;
D 2
	register j, notflag, true;
E 2
I 2
	register notflag, true;
E 2
	tchar i;

	if (x == 2) {
		notflag = 0;
		true = iflist[ifx];
		goto i1;
	}
	true = 0;
	skip();
	if ((cbits(i = getch())) == '!') {
		notflag = 1;
	} else {
		notflag = 0;
		ch = i;
	}
	i = atoi();
	if (!nonumb) {
		if (i > 0)
			true++;
		goto i1;
	}
	i = getch();
D 2
	switch (j = cbits(i)) {
E 2
I 2
	switch (cbits(i)) {
E 2
	case 'e':
D 2
		if (!(v.pn & 01))
E 2
I 2
		if (!(numtab[PN].val & 01))
E 2
			true++;
		break;
	case 'o':
D 2
		if (v.pn & 01)
E 2
I 2
		if (numtab[PN].val & 01)
E 2
			true++;
		break;
#ifdef NROFF
	case 'n':
		true++;
	case 't':
#endif
#ifndef NROFF
	case 't':
		true++;
	case 'n':
#endif
	case ' ':
		break;
	default:
		true = cmpstr(i);
	}
i1:
	true ^= notflag;
	if (x == 1)
		iflist[ifx] = !true;
	if (true) {
i2:
D 2
		do {
			v.hp = 0;
			pinchar = inchar;	/* XXX */
		} while ((cbits(i = getch())) == ' ');
E 2
I 2
		while ((cbits(i = getch())) == ' ')
			;
E 2
		if (cbits(i) == LEFT)
			goto i2;
		ch = i;
		nflush++;
	} else {
		copyf++;
		falsef++;
D 2
		if (eat(LEFT) == LEFT) {
			while (eatblk(RIGHT, LEFT) != RIGHT)
				nlflg = 0;
		}
E 2
I 2
		eatblk(0);
E 2
		copyf--;
		falsef--;
	}
}

D 2
eat0(c)
int	c;
{
	register i;
E 2
I 2
eatblk(inblk)
int inblk;
{	register int cnt, i;
E 2

D 2
	while ((i = cbits(getch0())) != c &&  (i != '\n'))
		;
	return(i);
E 2
I 2
	cnt = 0;
	do {
		if (ch)	{
			i = cbits(ch);
			ch = 0;
		} else
			i = cbits(getch0());
		if (i == ESC)
			cnt++;
		else {
			if (cnt == 1)
				switch (i) {
				case '{':  i = LEFT; break;
				case '}':  i = RIGHT; break;
				case '\n': i = 'x'; break;
				}
			cnt = 0;
		}
		if (i == LEFT) eatblk(1);
	} while ((!inblk && (i != '\n')) || (inblk && (i != RIGHT)));
	if (i == '\n')
		nlflg++;
E 2
}

D 2
eatblk(right, left)
int	right, left;
{
	register i;
E 2

D 2
e0:
	while ((i = cbits(getch())) != right && i != left && i != '\n')
		;
	if (i == left) {
		while ((i = eatblk(right, left)) != right)
			nlflg = 0;
		goto e0;
	}
	return(i);
}


E 2
cmpstr(c)
tchar c;
{
	register j, delim;
D 2
	tchar i;
	register filep p;
	extern filep alloc();
	extern filep incoff();
	filep begin;
	int	cnt, k;
	int	savapts, savapts1, savfont, savfont1,
	savpts, savpts1;
E 2
I 2
	register tchar i;
	register val;
	int savapts, savapts1, savfont, savfont1, savpts, savpts1;
	tchar string[1280];
	register tchar *sp;
E 2

	if (ismot(c))
		return(0);
	delim = cbits(c);
D 2
	if (dip != d)
		wbfl();
	if ((offset = begin = alloc()) == (filep)0)
		return(0);
	cnt = 0;
	v.hp = 0;
	pinchar = inchar;	/* XXX */
E 2
	savapts = apts;
	savapts1 = apts1;
	savfont = font;
	savfont1 = font1;
	savpts = pts;
	savpts1 = pts1;
D 2
	while ((j = cbits(i = getch())) != delim && j != '\n') {
		wbf(i);
		cnt++;
E 2
I 2
	sp = string;
	while ((j = cbits(i = getch()))!=delim && j!='\n' && sp<&string[1280-1])
		*sp++ = i;
	if (sp >= string + 1280) {
		errprint("too-long string compare.");
		edone(0100);
E 2
	}
D 2
	wbt((tchar)0);
	k = !cnt;
	if (nlflg)
E 2
I 2
	if (nlflg) {
		val = sp==string;
E 2
		goto rtn;
D 2
	p = begin;
E 2
I 2
	}
	*sp++ = 0;
E 2
	apts = savapts;
	apts1 = savapts1;
	font = savfont;
	font1 = savfont1;
	pts = savpts;
	pts1 = savpts1;
	mchbits();
D 2
	v.hp = 0;
	pinchar = inchar;	/* XXX */
E 2
I 2
	val = 1;
	sp = string;
E 2
	while ((j = cbits(i = getch())) != delim && j != '\n') {
D 2
		if (rbf0(p) != i) {
E 2
I 2
		if (*sp != i) {
E 2
			eat(delim);
D 2
			k = 0;
			break;
E 2
I 2
			val = 0;
			goto rtn;
E 2
		}
D 2
		p = incoff(p);
		k = !(--cnt);
E 2
I 2
		sp++;
E 2
	}
I 2
	if (*sp)
		val = 0;
E 2
rtn:
	apts = savapts;
	apts1 = savapts1;
	font = savfont;
	font1 = savfont1;
	pts = savpts;
	pts1 = savpts1;
	mchbits();
D 2
	offset = dip->op;
	ffree(begin);
	return(k);
E 2
I 2
	return(val);
E 2
}


caserd()
{

	lgf++;
	skip();
	getname();
	if (!iflg) {
		if (quiet) {
			ttys.sg_flags &= ~ECHO;
			stty(0, &ttys);
			flusho();
D 2
			fprintf(stderr, "\007"); /*bell*/
E 2
I 2
			fdprintf(stderr, "\007"); /*bell*/
E 2
		} else {
			if (nextf[0]) {
D 2
				fprintf(stderr, "%s:", nextf);
E 2
I 2
				fdprintf(stderr, "%s:", nextf);
E 2
			} else {
D 2
				fprintf(stderr, "\007"); /*bell*/
E 2
I 2
				fdprintf(stderr, "\007"); /*bell*/
E 2
			}
		}
	}
	collect();
	tty++;
D 2
	pushi((filep) - 1);
E 2
I 2
	pushi(NBLIST*BLK, PAIR('r','d'));
E 2
}


rdtty()
{
	char	onechar;

	onechar = 0;
	if (read(0, &onechar, 1) == 1) {
		if (onechar == '\n')
			tty++;
		else 
			tty = 1;
		if (tty != 3)
			return(onechar);
	}
	popi();
	tty = 0;
	if (quiet) {
		ttys.sg_flags |= ECHO;
		stty(0, &ttys);
	}
	return(0);
}


caseec()
{
	eschar = chget('\\');
}


caseeo()
{
	eschar = 0;
}


caseta()
{
	register i;

	tabtab[0] = nonumb = 0;
	for (i = 0; ((i < (NTAB - 1)) && !nonumb); i++) {
		if (skip())
			break;
D 2
		tabtab[i] = max(hnumb(&tabtab[max(i-1,0)]), 0) & TMASK;
E 2
I 2
		tabtab[i] = max(hnumb(&tabtab[max(i-1,0)]), 0) & TABMASK;
E 2
		if (!nonumb) 
			switch (cbits(ch)) {
			case 'C':
				tabtab[i] |= CTAB;
				break;
			case 'R':
				tabtab[i] |= RTAB;
				break;
			default: /*includes L*/
				break;
			}
		nonumb = ch = 0;
	}
	tabtab[i] = 0;
}


casene()
{
	register i, j;

	skip();
	i = vnumb((int *)0);
	if (nonumb)
		i = lss;
	if (i > (j = findt1())) {
		i = lss;
		lss = j;
		dip->nls = 0;
		newline(0);
		lss = i;
	}
}


casetr()
{
	register i, j;
	tchar k;

	lgf++;
	skip();
	while ((i = cbits(k=getch())) != '\n') {
		if (ismot(k))
			return;
		if (ismot(k = getch()))
			return;
		if ((j = cbits(k)) == '\n')
			j = ' ';
		trtab[i] = j;
	}
}


casecu()
{
	cu++;
	caseul();
}


caseul()
{
	register i;

	noscale++;
	if (skip())
		i = 1;
	else 
		i = atoi();
	if (ul && (i == 0)) {
		font = sfont;
		ul = cu = 0;
	}
	if (i) {
		if (!ul) {
			sfont = font;
			font = ulfont;
		}
		ul = i;
	}
	noscale = 0;
	mchbits();
}


caseuf()
{
	register i, j;

	if (skip() || !(i = getrq()) || i == 'S' ||  (j = findft(i))  == -1)
D 2
		ulfont = FT + 1; /*default position 2*/
E 2
I 2
		ulfont = ULFONT; /*default underline position*/
E 2
	else 
		ulfont = j;
#ifdef NROFF
D 2
	if (ulfont == 1)
		ulfont = 2;
E 2
I 2
	if (ulfont == FT)
		ulfont = ULFONT;
E 2
#endif
D 2
	ulbit = ulfont << 9;	/* certain to fail in tchar version */
E 2
}


caseit()
{
	register i;

	lgf++;
	it = itmac = 0;
	noscale++;
	skip();
	i = atoi();
	skip();
	if (!nonumb && (itmac = getrq()))
		it = i;
	noscale = 0;
}


casemc()
{
	register i;

	if (icf > 1)
		ic = 0;
	icf = 0;
	if (skip())
		return;
	ic = getch();
	icf = 1;
	skip();
	i = max(hnumb((int *)0), 0);
	if (!nonumb)
		ics = i;
}


casemk()
{
	register i, j;

	if (dip != d)
		j = dip->dnl; 
	else 
D 2
		j = v.nl;
E 2
I 2
		j = numtab[NL].val;
E 2
	if (skip()) {
		dip->mkline = j;
		return;
	}
	if ((i = getrq()) == 0)
		return;
D 2
	vlist[findr(i)] = j;
E 2
I 2
	numtab[findr(i)].val = j;
E 2
}


casesv()
{
	register i;

	skip();
	if ((i = vnumb((int *)0)) < 0)
		return;
	if (nonumb)
		i = 1;
	sv += i;
	caseos();
}


caseos()
{
	register savlss;

	if (sv <= findt1()) {
		savlss = lss;
		lss = sv;
		newline(0);
		lss = savlss;
		sv = 0;
	}
}


casenm()
{
	register i;

	lnmod = nn = 0;
	if (skip())
		return;
	lnmod++;
	noscale++;
D 2
	i = inumb(&v.ln);
E 2
I 2
	i = inumb(&numtab[LN].val);
E 2
	if (!nonumb)
D 2
		v.ln = max(i, 0);
E 2
I 2
		numtab[LN].val = max(i, 0);
E 2
	getnm(&ndf, 1);
	getnm(&nms, 0);
	getnm(&ni, 0);
	noscale = 0;
	nmbits = chbits;
}


getnm(p, min)
int	*p, min;
{
	register i;

	eat(' ');
	if (skip())
		return;
	i = atoi();
	if (nonumb)
		return;
	*p = max(i, min);
}


casenn()
{
	noscale++;
	skip();
	nn = max(atoi(), 1);
	noscale = 0;
}


caseab()
{
	casetm(1);
D 2
	done2(0);
E 2
I 2
	done3(0);
E 2
}
D 2


E 2
E 1
