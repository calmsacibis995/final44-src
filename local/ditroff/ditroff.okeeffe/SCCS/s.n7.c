h59675
s 00006/00000/00831
d D 2.4 86/08/15 12:07:25 jaap 5 4
c Page feeder assist added (eject)
e
s 00004/00001/00827
d D 2.3 86/08/14 23:06:05 jaap 4 3
c fix of tbreak doesn't work with mm macros
e
s 00005/00002/00823
d D 2.2 85/12/12 14:05:16 jaap 3 2
c Force poper initialising by newlin(1) if first request is nobreak
e
s 00138/00132/00687
d D 2.1 85/07/18 14:25:34 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00819/00000/00000
d D 1.1 85/07/17 17:54:37 jaap 1 0
c date and time created 85/07/17 17:54:37 by jaap
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
#ifdef NROFF
#define GETCH gettch
#endif
#ifndef NROFF
#define GETCH getch
#endif

/*
D 2
troff7.c
E 2
I 2
 * troff7.c
 * 
 * text
 */
E 2

D 2
text
*/

E 2
#include <sgtty.h>
I 2
#include <ctype.h>
E 2
#include "ext.h"
int	brflg;

tbreak()
{
	register pad, k;
D 2
	tchar	*i, j;
	int	res;
E 2
I 2
	register tchar	*i, j;
	register int resol = 0;
E 2

	trap = 0;
D 3
	if (nb)
		return;
E 3
I 3
	if (nb) {
I 4
/*
E 4
		if( dip == d && numtab[NL].val == -1)
			newline(1);
D 4
		else return;
E 4
I 4
		else
*/
		return;
E 4
	}
E 3
D 2
	if ((dip == d) && (v.nl == -1)) {
E 2
I 2
	if (dip == d && numtab[NL].val == -1) {
E 2
		newline(1);
		return;
	}
	if (!nc) {
		setnel();
		if (!wch)
			return;
		if (pendw)
			getword(1);
		movword();
	} else if (pendw && !brflg) {
		getword(1);
		movword();
	}
	*linep = dip->nls = 0;
#ifdef NROFF
	if (dip == d)
		horiz(po);
#endif
	if (lnmod)
		donum();
	lastl = ne;
	if (brflg != 1) {
		totout = 0;
	} else if (ad) {
D 2
		if ((lastl = (ll - un)) < ne)
E 2
I 2
		if ((lastl = ll - un) < ne)
E 2
			lastl = ne;
	}
	if (admod && ad && (brflg != 2)) {
		lastl = ne;
		adsp = adrem = 0;
D 2
#ifdef NROFF
E 2
		if (admod == 1)
D 2
			un +=  quant(nel / 2, t.Adj);
#endif
#ifndef NROFF
		if (admod == 1)
			un += nel / 2;
#endif
E 2
I 2
			un +=  quant(nel / 2, HOR);
E 2
		else if (admod == 2)
			un += nel;
	}
	totout++;
	brflg = 0;
D 2
	if ((lastl + un) > dip->maxl)
		dip->maxl = (lastl + un);
E 2
I 2
	if (lastl + un > dip->maxl)
		dip->maxl = lastl + un;
E 2
	horiz(un);
#ifdef NROFF
	if (adrem % t.Adj)
D 2
		res = t.Hor; 
E 2
I 2
		resol = t.Hor; 
E 2
	else 
D 2
		res = t.Adj;
E 2
I 2
		resol = t.Adj;
#else
	resol = HOR;
E 2
#endif
	for (i = line; nc > 0; ) {
		if ((cbits(j = *i++)) == ' ') {
			pad = 0;
			do {
				pad += width(j);
				nc--;
			} while ((cbits(j = *i++)) == ' ');
			i--;
			pad += adsp;
			--nwd;
			if (adrem) {
				if (adrem < 0) {
D 2
#ifdef NROFF
					pad -= res;
					adrem += res;
				} else if ((totout & 01) ||  ((adrem / res) >= (nwd))) {
					pad += res;
					adrem -= res;
#endif
#ifndef NROFF
					pad--;
					adrem++;
				} else {
					pad++;
					adrem--;
#endif
E 2
I 2
					pad -= resol;
					adrem += resol;
				} else if ((totout & 01) || adrem / resol >= nwd) {
					pad += resol;
					adrem -= resol;
E 2
				}
			}
			pchar((tchar) WORDSP);
			horiz(pad);
		} else {
			pchar(j);
			nc--;
		}
	}
	if (ic) {
		if ((k = ll - un - lastl + ics) > 0)
			horiz(k);
		pchar(ic);
	}
	if (icf)
		icf++;
	else 
		ic = 0;
	ne = nwd = 0;
	un = in;
	setnel();
	newline(0);
	if (dip != d) {
		if (dip->dnl > dip->hnl)
			dip->hnl = dip->dnl;
	} else {
D 2
		if (v.nl > dip->hnl)
			dip->hnl = v.nl;
E 2
I 2
		if (numtab[NL].val > dip->hnl)
			dip->hnl = numtab[NL].val;
E 2
	}
	for (k = ls - 1; k > 0 && !trap; k--)
		newline(0);
	spread = 0;
}

donum()
{
	register i, nw;
	extern pchar();

	nrbits = nmbits;
	nw = width('1' | nrbits);
	if (nn) {
		nn--;
		goto d1;
	}
D 2
	if (v.ln % ndf) {
		v.ln++;
E 2
I 2
	if (numtab[LN].val % ndf) {
		numtab[LN].val++;
E 2
d1:
		un += nw * (3 + nms + ni);
		return;
	}
	i = 0;
D 2
	if (v.ln < 100)
E 2
I 2
	if (numtab[LN].val < 100)
E 2
		i++;
D 2
	if (v.ln < 10)
E 2
I 2
	if (numtab[LN].val < 10)
E 2
		i++;
	horiz(nw * (ni + i));
	nform = 0;
D 2
	fnumb(v.ln, pchar);
E 2
I 2
	fnumb(numtab[LN].val, pchar);
E 2
	un += nw * nms;
D 2
	v.ln++;
E 2
I 2
	numtab[LN].val++;
E 2
}


text()
{
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2
	static int	spcnt;

	nflush++;
D 2
	if ((dip == d) && (v.nl == -1)) {
E 2
I 2
	numtab[HP].val = 0;
	if ((dip == d) && (numtab[NL].val == -1)) {
E 2
		newline(1); 
		return;
	}
	setnel();
	if (ce || !fi) {
		nofill();
		return;
	}
	if (pendw)
		goto t4;
	if (pendt)
		if (spcnt)
			goto t2; 
		else 
			goto t3;
	pendt++;
	if (spcnt)
		goto t2;
D 2
	while ((cbits(i = GETCH())) == ' ')
E 2
I 2
	while ((cbits(i = GETCH())) == ' ') {
E 2
		spcnt++;
I 2
		numtab[HP].val += sps;
		widthp = sps;
	}
E 2
	if (nlflg) {
t1:
		nflush = pendt = ch = spcnt = 0;
		callsp();
		return;
	}
	ch = i;
	if (spcnt) {
t2:
		tbreak();
		if (nc || wch)
			goto rtn;
		un += spcnt * sps;
		spcnt = 0;
		setnel();
		if (trap)
			goto rtn;
		if (nlflg)
			goto t1;
	}
t3:
	if (spread)
		goto t5;
	if (pendw || !wch)
t4:
		if (getword(0))
			goto t6;
	if (!movword())
		goto t3;
t5:
	if (nlflg)
		pendt = 0;
	adsp = adrem = 0;
	if (ad) {
		if (nwd == 1)
			adsp = nel; 
		else 
			adsp = nel / (nwd - 1);
D 2
#ifdef NROFF
		adsp = (adsp / t.Adj)*t.Adj;
#endif
		adrem = nel -adsp*(nwd-1);
E 2
I 2
		adsp = (adsp / HOR) * HOR;
		adrem = nel - adsp*(nwd-1);
E 2
	}
	brflg = 1;
	tbreak();
	spread = 0;
	if (!trap)
		goto t3;
	if (!nlflg)
		goto rtn;
t6:
	pendt = 0;
	ckul();
rtn:
	nflush = 0;
}


nofill()
{
	register j;
D 2
	tchar i;
E 2
I 2
	register tchar i;
E 2

	if (!pendnf) {
		over = 0;
		tbreak();
		if (trap)
			goto rtn;
		if (nlflg) {
			ch = nflush = 0;
			callsp();
			return;
		}
		adsp = adrem = 0;
		nwd = 10000;
	}
	while ((j = (cbits(i = GETCH()))) != '\n') {
		if (j == ohc)
			continue;
		if (j == CONT) {
			pendnf++;
			nflush = 0;
			flushi();
			ckul();
			return;
		}
D 2
		storeline(i, -1);
E 2
I 2
		j = width(i);
		widthp = j;
		numtab[HP].val += j;
		storeline(i, j);
E 2
	}
	if (ce) {
		ce--;
		if ((i = quant(nel / 2, HOR)) > 0)
			un += i;
	}
	if (!nc)
		storeline((tchar)FILLER, 0);
	brflg = 2;
	tbreak();
	ckul();
rtn:
	pendnf = nflush = 0;
}


callsp()
{
	register i;

	if (flss)
		i = flss; 
	else 
		i = lss;
	flss = 0;
	casesp(i);
}


ckul()
{
	if (ul && (--ul == 0)) {
		cu = 0;
		font = sfont;
		mchbits();
	}
	if (it && (--it == 0) && itmac)
		control(itmac, 0);
}


storeline(c, w)
D 2
tchar c;
E 2
I 2
register tchar c;
E 2
{
D 2
	register i;

E 2
	if (linep >= line + lnsize - 1) {
		if (!over) {
			flusho();
D 2
			fprintf(stderr, "troff: Line overflow.\n");
E 2
I 2
			errprint("Line overflow.");
E 2
			over++;
			c = LEFTHAND;
			w = -1;
			goto s1;
		}
		return;
	}
s1:
	if (w == -1)
		w = width(c);
	ne += w;
	nel -= w;
	*linep++ = c;
	nc++;
}


newline(a)
int	a;
{
	register i, j, nlss;
	int	opn;

	if (a)
		goto nl1;
	if (dip != d) {
		j = lss;
		pchar1((tchar)FLSS);
		if (flss)
			lss = flss;
		i = lss + dip->blss;
		dip->dnl += i;
		pchar1((tchar)i);
		pchar1((tchar)'\n');
		lss = j;
		dip->blss = flss = 0;
		if (dip->alss) {
			pchar1((tchar)FLSS);
			pchar1((tchar)dip->alss);
			pchar1((tchar)'\n');
			dip->dnl += dip->alss;
			dip->alss = 0;
		}
D 2
		if (dip->ditrap && !dip->ditf &&  (dip->dnl >= dip->ditrap) && dip->dimac)
E 2
I 2
		if (dip->ditrap && !dip->ditf && dip->dnl >= dip->ditrap && dip->dimac)
E 2
			if (control(dip->dimac, 0)) {
				trap++; 
				dip->ditf++;
			}
		return;
	}
	j = lss;
	if (flss)
		lss = flss;
	nlss = dip->alss + dip->blss + lss;
D 2
	v.nl += nlss;
E 2
I 2
	numtab[NL].val += nlss;
E 2
#ifndef NROFF
	if (ascii) {
		dip->alss = dip->blss = 0;
	}
#endif
	pchar1((tchar)'\n');
	flss = 0;
	lss = j;
D 2
	if (v.nl < pl)
E 2
I 2
	if (numtab[NL].val < pl)
E 2
		goto nl2;
nl1:
D 2
	ejf = dip->hnl = v.nl = 0;
E 2
I 2
	ejf = dip->hnl = numtab[NL].val = 0;
E 2
	ejl = frame;
	if (donef) {
		if ((!nc && !wch) || ndone)
			done1(0);
		ndone++;
		donef = 0;
		if (frame == stk)
			nflush++;
	}
D 2
	opn = v.pn;
	v.pn++;
E 2
I 2
	opn = numtab[PN].val;
	numtab[PN].val++;
E 2
	if (npnflg) {
D 2
		v.pn = npn;
E 2
I 2
		numtab[PN].val = npn;
E 2
		npn = npnflg = 0;
	}
nlpn:
D 2
	if (v.pn == pfrom) {
E 2
I 2
	if (numtab[PN].val == pfrom) {
E 2
		print++;
		pfrom = -1;
	} else if (opn == pto) {
		print = 0;
		opn = -1;
		chkpn();
		goto nlpn;
	}
	if (print)
D 2
		newpage(v.pn);	/* supposedly in a clean state so can pause */
E 2
I 2
		newpage(numtab[PN].val);	/* supposedly in a clean state so can pause */
I 5
#ifdef NROFF
	if (print && *t.eject) {
		oputs(t.eject);
		flusho();
	}
#endif
E 5
E 2
	if (stop && print) {
		dpn++;
		if (dpn >= stop) {
			dpn = 0;
			dostop();
		}
	}
nl2:
	trap = 0;
D 2
	if (v.nl == 0) {
E 2
I 2
	if (numtab[NL].val == 0) {
E 2
		if ((j = findn(0)) != NTRAP)
			trap = control(mlist[j], 0);
D 2
	} else if ((i = findt(v.nl - nlss)) <= nlss) {
		if ((j = findn1(v.nl - nlss + i)) == NTRAP) {
E 2
I 2
	} else if ((i = findt(numtab[NL].val - nlss)) <= nlss) {
		if ((j = findn1(numtab[NL].val - nlss + i)) == NTRAP) {
E 2
			flusho();
D 2
			fprintf(stderr, "troff: Trap botch.\n");
E 2
I 2
			errprint("Trap botch.");
E 2
			done2(-5);
		}
		trap = control(mlist[j], 0);
	}
}


findn1(a)
int	a;
{
	register i, j;

	for (i = 0; i < NTRAP; i++) {
		if (mlist[i]) {
			if ((j = nlist[i]) < 0)
				j += pl;
			if (j == a)
				break;
		}
	}
	return(i);
}


chkpn()
{
	pto = *(pnp++);
	pfrom = pto>=0 ? pto : -pto;
	if (pto == -32767) {
		flusho();
		done1(0);
	}
	if (pto < 0) {
		pto = -pto;
		print++;
		pfrom = 0;
	}
}


findt(a)
int	a;
{
	register i, j, k;

	k = 32767;
	if (dip != d) {
D 2
		if (dip->dimac && ((i = dip->ditrap - a) > 0))
E 2
I 2
		if (dip->dimac && (i = dip->ditrap - a) > 0)
E 2
			k = i;
		return(k);
	}
	for (i = 0; i < NTRAP; i++) {
		if (mlist[i]) {
			if ((j = nlist[i]) < 0)
				j += pl;
D 2
			if ((j -= a)  <=  0)
E 2
I 2
			if ((j -= a) <= 0)
E 2
				continue;
			if (j < k)
				k = j;
		}
	}
	i = pl - a;
	if (k > i)
		k = i;
	return(k);
}


findt1()
{
	register i;

	if (dip != d)
		i = dip->dnl;
	else 
D 2
		i = v.nl;
E 2
I 2
		i = numtab[NL].val;
E 2
	return(findt(i));
}


eject(a)
struct s *a;
{
	register savlss;

	if (dip != d)
		return;
	ejf++;
	if (a)
		ejl = a;
	else 
		ejl = frame;
	if (trap)
		return;
e1:
	savlss = lss;
D 2
	lss = findt(v.nl);
E 2
I 2
	lss = findt(numtab[NL].val);
E 2
	newline(0);
	lss = savlss;
D 2
	if (v.nl && !trap)
E 2
I 2
	if (numtab[NL].val && !trap)
E 2
		goto e1;
}


movword()
{
	register w;
D 2
	tchar i, *wp;
E 2
I 2
	register tchar i, *wp;
E 2
	int	savwch, hys;

	over = 0;
	wp = wordp;
	if (!nwd) {
D 2
		while ((cbits(i = *wp++)) == ' ') {
E 2
I 2
		while (cbits(i = *wp++) == ' ') {
E 2
			wch--;
D 2
			wne -= width(i);
E 2
I 2
			wne -= sps;
E 2
		}
		wp--;
	}
D 2
	if ((wne > nel) &&  !hyoff && hyf &&  (!nwd || (nel > 3 * sps)) &&  (!(hyf & 02) || (findt1() > lss)))
E 2
I 2
	if (wne > nel && !hyoff && hyf && (!nwd || nel > 3 * sps) &&
	   (!(hyf & 02) || (findt1() > lss)))
E 2
		hyphen(wp);
	savwch = wch;
	hyp = hyptr;
	nhyp = 0;
D 2
	while (*hyp && (*hyp <= wp))
E 2
I 2
	while (*hyp && *hyp <= wp)
E 2
		hyp++;
	while (wch) {
D 2
		if ((hyoff != 1) && (*hyp == wp)) {
E 2
I 2
		if (hyoff != 1 && *hyp == wp) {
E 2
			hyp++;
D 2
			if (!wdstart ||  ((wp > (wdstart + 1)) &&  (wp < wdend) &&  (!(hyf & 04) || (wp < (wdend - 1))) &&
			    (!(hyf & '\b') || wp > wdstart + 2))) {
E 2
I 2
			if (!wdstart || (wp > wdstart + 1 && wp < wdend &&
			   (!(hyf & 04) || wp < wdend - 1) &&		/* 04 => last 2 */
			   (!(hyf & 010) || wp > wdstart + 2))) {	/* 010 => 1st 2 */
E 2
				nhyp++;
				storeline((tchar)IMP, 0);
			}
		}
		i = *wp++;
		w = width(i);
		wne -= w;
		wch--;
		storeline(i, w);
	}
	if (nel >= 0) {
		nwd++;
D 2
		return(0);
E 2
I 2
		return(0);	/* line didn't fill up */
E 2
	}
D 2
	xbitf = 1;
E 2
I 2
#ifndef NROFF
	xbits((tchar)HYPHEN, 1);
#endif
E 2
	hys = width((tchar)HYPHEN);
m1:
	if (!nhyp) {
		if (!nwd)
			goto m3;
		if (wch == savwch)
			goto m4;
	}
	if (*--linep != IMP)
		goto m5;
	if (!(--nhyp))
		if (!nwd)
			goto m2;
	if (nel < hys) {
		nc--;
		goto m1;
	}
m2:
D 2
	if ((i = cbits(*(linep - 1))) != '-' &&  (i != EMDASH)) {
E 2
I 2
	if ((i = cbits(*(linep - 1))) != '-' && i != EMDASH) {
E 2
		*linep = (*(linep - 1) & SFMASK) | HYPHEN;
		w = width(*linep);
		nel -= w;
		ne += w;
		linep++;
	}
m3:
	nwd++;
m4:
	wordp = wp;
D 2
	return(1);
E 2
I 2
	return(1);	/* line filled up */
E 2
m5:
	nc--;
	w = width(*linep);
	ne -= w;
	nel += w;
	wne += w;
	wch++;
	wp--;
	goto m1;
}


horiz(i)
int	i;
{
	vflag = 0;
	if (i)
		pchar(makem(i));
}


setnel()
{
	if (!nc) {
		linep = line;
		if (un1 >= 0) {
			un = un1;
			un1 = -1;
		}
		nel = ll - un;
		ne = adsp = adrem = 0;
	}
}


getword(x)
int	x;
{
D 2
	register j, swp;
	tchar i;
	int	noword;
E 2
I 2
	register int j, k;
	register tchar i, *wp;
	int noword;
E 2

	noword = 0;
	if (x)
		if (pendw) {
			*pendw = 0;
			goto rtn;
		}
	if (wordp = pendw)
		goto g1;
	hyp = hyptr;
	wordp = word;
	over = wne = wch = 0;
	hyoff = 0;
D 2
	while (1) {
E 2
I 2
	while (1) {	/* picks up 1st char of word */
E 2
		j = cbits(i = GETCH());
		if (j == '\n') {
			wne = wch = 0;
			noword = 1;
			goto rtn;
		}
		if (j == ohc) {
D 2
			hyoff = 1;
E 2
I 2
			hyoff = 1;	/* 1 => don't hyphenate */
E 2
			continue;
		}
		if (j == ' ') {
D 2
			storeword(i, width(i));
E 2
I 2
			numtab[HP].val += sps;
			widthp = sps;
			storeword(i, sps);
E 2
			continue;
		}
		break;
	}
D 2
	swp = widthp;
	storeword(' ' | chbits, -1);
E 2
I 2
	storeword(' ' | chbits, sps);
E 2
	if (spflg) {
D 2
		storeword(' ' | chbits, -1);
E 2
I 2
		storeword(' ' | chbits, sps);
E 2
		spflg = 0;
	}
D 2
	widthp = swp;
E 2
g0:
	if (j == CONT) {
		pendw = wordp;
		nflush = 0;
		flushi();
		return(1);
	}
	if (hyoff != 1) {
		if (j == ohc) {
			hyoff = 2;
			*hyp++ = wordp;
			if (hyp > (hyptr + NHYP - 1))
				hyp = hyptr + NHYP - 1;
			goto g1;
		}
D 2
		if ((j == '-') ||  (j == EMDASH))
E 2
I 2
		if (j == '-' || j == EMDASH)
E 2
			if (wordp > word + 1) {
				hyoff = 2;
				*hyp++ = wordp + 1;
				if (hyp > (hyptr + NHYP - 1))
					hyp = hyptr + NHYP - 1;
			}
	}
D 2
	storeword(i, width(i));
E 2
I 2
	j = width(i);
	numtab[HP].val += j;
	storeword(i, j);
E 2
g1:
	j = cbits(i = GETCH());
	if (j != ' ') {
I 2
		static char *sentchar = ".?!";	/* sentence terminators */
E 2
		if (j != '\n')
			goto g0;
D 2
						/* fix bwk
						 * improve the quality by
						 * look for special cases
						 * ("'\)]) at end of
						 * sentence
						 */
		    {	tchar *wp = wordp-1;
			while (wp >= word) {
				j = cbits(*wp--);
				if (j=='"' || j=='\'' || j==')' ||j==']')
					continue;
						/* This the real fix, don't
						 * raise the spaceflg i these
						 * cases
						 */
				if (j == '.' || j == '!' || j == '?')
E 2
I 2
		wp = wordp-1;	/* handle extra space at end of sentence */
		while (wp >= word) {
			j = cbits(*wp--);
			if (j=='"' || j=='\'' || j==')' || j==']' || j=='*' || j==DAGGER)
				continue;
			for (k = 0; sentchar[k]; k++)
				if (j == sentchar[k]) {
E 2
					spflg++;
D 2
				break;
			}
		    }
E 2
I 2
					break;
				}
			break;
		}
E 2
	}
	*wordp = 0;
I 2
	numtab[HP].val += sps;
E 2
rtn:
I 2
	for (wp = word; *wp; wp++) {
		j = cbits(*wp);
		if (j == ' ')
			continue;
		if (!isdigit(j) && j != '-')
			break;
	}
	if (*wp == 0)	/* all numbers, so don't hyphenate */
		hyoff = 1;
E 2
	wdstart = 0;
	wordp = word;
	pendw = 0;
	*hyp++ = 0;
	setnel();
	return(noword);
}


storeword(c, w)
D 2
tchar c;
int	w;
E 2
I 2
register tchar c;
register int	w;
E 2
{

D 2
	if (wordp >= &word[WDSIZE - 1]) {
E 2
I 2
	if (wordp >= &word[WDSIZE - 3]) {
E 2
		if (!over) {
			flusho();
D 2
			fprintf(stderr, "troff: Word overflow.\n");
E 2
I 2
			errprint("Word overflow.");
E 2
			over++;
			c = LEFTHAND;
			w = -1;
			goto s1;
		}
		return;
	}
s1:
	if (w == -1)
		w = width(c);
I 2
	widthp = w;
E 2
	wne += w;
	*wordp++ = c;
	wch++;
}


#ifdef NROFF
tchar gettch()
{
I 2
	extern int c_isalnum;
E 2
	tchar i;
	int j;

	i = getch();
	j = cbits(i);
D 2
	if (ismot(i) || i & ulbit)
E 2
I 2
	if (ismot(i) || fbits(i) != ulfont)
E 2
		return(i);
D 2
	if (cu && trtab[j] == ' ') {
		setcbits(i, '_');
		i &= ~ulbit;
E 2
I 2
	if (cu) {
		if (trtab[j] == ' ') {
			setcbits(i, '_');
			setfbits(i, FT);	/* default */
		}
		return(i);
E 2
	}
D 2
	if (!cu && j > 32 && !iscontrol(j) && !(*t.codetab[j-32] & 0200))
		i &= ~ulbit;
E 2
I 2
	/* should test here for characters that ought to be underlined */
	/* in the old nroff, that was the 200 bit on the width! */
	/* for now, just do letters, digits and certain special chars */
	if (j <= 127) {
		if (!isalnum(j))
			setfbits(i, FT);
	} else {
		if (j < c_isalnum)
			setfbits(i, FT);
	}
E 2
	return(i);
}


#endif
E 1
