h61770
s 00112/00083/00356
d D 2.1 85/07/18 14:27:21 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00439/00000/00000
d D 1.1 85/07/17 17:54:44 jaap 1 0
c date and time created 85/07/17 17:54:44 by jaap
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
/*
troff9.c

misc functions
*/

E 2
#include <sgtty.h>
#include "ext.h"

I 2
/*
 * troff9.c
 * 
 * misc functions
 */

E 2
tchar setz()
{
	tchar i;

	if (!ismot(i = getch()))
		i |= ZBIT;
	return(i);
}

D 2

E 2
setline()
{
	register tchar *i;
	tchar c;
	int	length;
	int	w, cnt, delim, rem, temp;
I 2
	tchar linebuf[NC];
E 2

	if (ismot(c = getch()))
		return;
	delim = cbits(c);
	vflag = 0;
	dfact = EM;
	length = quant(atoi(), HOR);
	dfact = 1;
	if (!length) {
		eat(delim);
		return;
	}
s0:
	if ((cbits(c = getch())) == delim) {
		ch = c;
		c = RULE | chbits;
	} else if (cbits(c) == FILLER)
		goto s0;
	w = width(c);
D 2
	i = cbuf;
E 2
I 2
	i = linebuf;
E 2
	if (length < 0) {
		*i++ = makem(length);
		length = -length;
	}
	if (!(cnt = length / w)) {
		*i++ = makem(-(temp = ((w - length) / 2)));
		*i++ = c;
		*i++ = makem(-(w - length - temp));
		goto s1;
	}
	if (rem = length % w) {
		if (cbits(c) == RULE || cbits(c) == UNDERLINE || cbits(c) == ROOTEN)
			*i++ = c | ZBIT;
		*i++ = makem(rem);
	}
	if (cnt) {
		*i++ = RPT;
		*i++ = cnt;
		*i++ = c;
	}
s1:
	*i++ = 0;
	eat(delim);
D 2
	cp = cbuf;
E 2
I 2
	pushback(linebuf);
E 2
}


eat(c)
D 2
int	c;
E 2
I 2
register int	c;
E 2
{
	register i;

	while ((i = cbits(getch())) != c &&  (i != '\n'))
		;
	return(i);
}


setov()
{
	register j, k;
D 2
	tchar i, *p, o[NOV];
	int	delim, w[NOV];
E 2
I 2
	tchar i, o[NOV];
	int delim, w[NOV];
E 2

	if (ismot(i = getch()))
		return;
	delim = cbits(i);
	for (k = 0; (k < NOV) && ((j = cbits(i = getch())) != delim) &&  (j != '\n'); k++) {
		o[k] = i;
		w[k] = width(i);
	}
	o[k] = w[k] = 0;
	if (o[0])
		for (j = 1; j; ) {
			j = 0;
			for (k = 1; o[k] ; k++) {
				if (w[k-1] < w[k]) {
					j++;
					i = w[k];
					w[k] = w[k-1];
					w[k-1] = i;
					i = o[k];
					o[k] = o[k-1];
					o[k-1] = i;
				}
			}
		}
	else 
		return;
D 2
	p = cbuf;
	for (k = 0; o[k]; k++) {
		*p++ = o[k];
		*p++ = makem(-((w[k] + w[k+1]) / 2));
E 2
I 2
	*pbp++ = makem(w[0] / 2);
	for (k = 0; o[k]; k++)
		;
	while (k>0) {
		k--;
		*pbp++ = makem(-((w[k] + w[k+1]) / 2));
		*pbp++ = o[k];
E 2
	}
D 2
	*p++ = makem(w[0] / 2);
	*p = 0;
	cp = cbuf;
E 2
}


setbra()
{
	register k;
	tchar i, *j, dwn;
	int	cnt, delim;
I 2
	tchar brabuf[NC];
E 2

	if (ismot(i = getch()))
		return;
	delim = cbits(i);
D 2
	j = cbuf + 1;
E 2
I 2
	j = brabuf + 1;
E 2
	cnt = 0;
#ifdef NROFF
	dwn = (2 * t.Halfline) | MOT | VMOT;
#endif
#ifndef NROFF
	dwn = EM | MOT | VMOT;
#endif
D 2
	while (((k = cbits(i = getch())) != delim) && (k != '\n') &&  (j <= (cbuf + NC - 4))) {
E 2
I 2
	while (((k = cbits(i = getch())) != delim) && (k != '\n') &&  (j <= (brabuf + NC - 4))) {
E 2
		*j++ = i | ZBIT;
		*j++ = dwn;
		cnt++;
	}
	if (--cnt < 0)
		return;
	else if (!cnt) {
		ch = *(j - 2);
		return;
	}
	*j = 0;
#ifdef NROFF
D 2
	*--j = *cbuf = (cnt * t.Halfline) | MOT | NMOT | VMOT;
E 2
I 2
	*--j = *brabuf = (cnt * t.Halfline) | MOT | NMOT | VMOT;
E 2
#endif
#ifndef NROFF
D 2
	*--j = *cbuf = (cnt * EM) / 2 | MOT | NMOT | VMOT;
E 2
I 2
	*--j = *brabuf = (cnt * EM) / 2 | MOT | NMOT | VMOT;
E 2
#endif
	*--j &= ~ZBIT;
D 2
	cp = cbuf;
E 2
I 2
	pushback(brabuf);
E 2
}


setvline()
{
	register i;
D 2
	tchar c, *k, rem, ver, neg;
E 2
I 2
	tchar c, rem, ver, neg;
E 2
	int	cnt, delim, v;
I 2
	tchar vlbuf[NC];
	register tchar *vlp;
E 2

	if (ismot(c = getch()))
		return;
	delim = cbits(c);
	dfact = lss;
	vflag++;
	i = quant(atoi(), VERT);
	dfact = 1;
	if (!i) {
		eat(delim);
		vflag = 0;
		return;
	}
	if ((cbits(c = getch())) == delim) {
		c = BOXRULE | chbits;	/*default box rule*/
	} else 
		getch();
	c |= ZBIT;
	neg = 0;
	if (i < 0) {
		i = -i;
		neg = NMOT;
	}
#ifdef NROFF
	v = 2 * t.Halfline;
#endif
#ifndef NROFF
	v = EM;
#endif
	cnt = i / v;
	rem = makem(i % v) | neg;
	ver = makem(v) | neg;
D 2
	k = cbuf;
E 2
I 2
	vlp = vlbuf;
E 2
	if (!neg)
D 2
		*k++ = ver;
E 2
I 2
		*vlp++ = ver;
E 2
	if (absmot(rem) != 0) {
D 2
		*k++ = c;
		*k++ = rem;
E 2
I 2
		*vlp++ = c;
		*vlp++ = rem;
E 2
	}
D 2
	while ((k < (cbuf + NC - 3)) && cnt--) {
		*k++ = c;
		*k++ = ver;
E 2
I 2
	while ((vlp < (vlbuf + NC - 3)) && cnt--) {
		*vlp++ = c;
		*vlp++ = ver;
E 2
	}
D 2
	*(k - 2) &= ~ZBIT;
E 2
I 2
	*(vlp - 2) &= ~ZBIT;
E 2
	if (!neg)
D 2
		k--;
	*k = 0;
	cp = cbuf;
E 2
I 2
		vlp--;
	*vlp++ = 0;
	pushback(vlbuf);
E 2
	vflag = 0;
}

I 2
#define	NPAIR	(NC/2-6)	/* max pairs in spline, etc. */
E 2

setdraw()	/* generate internal cookies for a drawing function */
{
D 2
	int i, j, k, dx[100], dy[100], delim, type, temp;
	tchar c;
	/* input is \D'f x y x y ... c' (or at least it had better be) */
E 2
I 2
	int i, j, k, dx[NPAIR], dy[NPAIR], delim, type;
	tchar c, drawbuf[NC];

	/* input is \D'f dx dy dx dy ... c' (or at least it had better be) */
E 2
	/* this does drawing function f with character c and the */
D 2
	/* specified x,y pairs interpreted as appropriate */
E 2
I 2
	/* specified dx,dy pairs interpreted as appropriate */
	/* pairs are deltas from last point, except for radii */
E 2

D 2
	/* l x y:	line from here by x,y */
E 2
I 2
	/* l dx dy:	line from here by dx,dy */
E 2
	/* c x:		circle of diameter x, left side here */
	/* e x y:	ellipse of diameters x,y, left side here */
D 2
	/* a x y r:	arc to x,y with radius r (ccw) */
	/* ~ x y ...:	wiggly line */
E 2
I 2
	/* a dx1 dy1 dx2 dy2:
			ccw arc: ctr at dx1,dy1, then end at dx2,dy2 from there */
	/* ~ dx1 dy1 dx2 dy2...:
			spline to dx1,dy1 to dx2,dy2 ... */
	/* f dx dy ...:	f is any other char:  like spline */
E 2

	if (ismot(c = getch()))
		return;
	delim = cbits(c);
	type = cbits(getch());
D 2
	for (i = 0; i < 50 ; i++) {
E 2
I 2
	for (i = 0; i < NPAIR ; i++) {
E 2
		c = getch();
		if (cbits(c) == delim)
			break;
	/* ought to pick up optional drawing character */
		if (cbits(c) != ' ')
			ch = c;
		vflag = 0;
		dfact = EM;
		dx[i] = quant(atoi(), HOR);
		if (dx[i] > MAXMOT)
			dx[i] = MAXMOT;
		else if (dx[i] < -MAXMOT)
			dx[i] = -MAXMOT;
		if (cbits((c = getch())) == delim) {	/* spacer */
			dy[i++] = 0;
			break;
		}
		vflag = 1;
		dfact = lss;
		dy[i] = quant(atoi(), VERT);
		if (dy[i] > MAXMOT)
			dy[i] = MAXMOT;
		else if (dy[i] < -MAXMOT)
			dy[i] = -MAXMOT;
	}
	dfact = 1;
	vflag = 0;
#ifndef NROFF
D 2
	cbuf[0] = DRAWFCN | chbits | ZBIT;
	cbuf[1] = type | chbits | ZBIT;
	cbuf[2] = '.' | chbits | ZBIT;	/* indicates to use default drawing character */
E 2
I 2
	drawbuf[0] = DRAWFCN | chbits | ZBIT;
	drawbuf[1] = type | chbits | ZBIT;
	drawbuf[2] = '.' | chbits | ZBIT;	/* use default drawing character */
E 2
	for (k = 0, j = 3; k < i; k++) {
D 2
		cbuf[j++] = MOT | ((dx[k] >= 0) ? dx[k] : (NMOT | -dx[k]));
		cbuf[j++] = MOT | VMOT | ((dy[k] >= 0) ? dy[k] : (NMOT | -dy[k]));
E 2
I 2
		drawbuf[j++] = MOT | ((dx[k] >= 0) ? dx[k] : (NMOT | -dx[k]));
		drawbuf[j++] = MOT | VMOT | ((dy[k] >= 0) ? dy[k] : (NMOT | -dy[k]));
E 2
	}
	if (type == DRAWELLIPSE) {
D 2
		cbuf[5] = cbuf[4] | NMOT;	/* so the net vertical is zero */
E 2
I 2
		drawbuf[5] = drawbuf[4] | NMOT;	/* so the net vertical is zero */
E 2
		j = 6;
	}
D 2
	cbuf[j++] = '.' | chbits | ZBIT;	/* marks end for ptout */
	cbuf[j] = 0;
	cp = cbuf;
E 2
I 2
	drawbuf[j++] = DRAWFCN | chbits | ZBIT;	/* marks end for ptout */
	drawbuf[j] = 0;
	pushback(drawbuf);
E 2
#endif
}


casefc()
{
	register i;
	tchar j;

I 2
	gchtab[fc] &= ~FCBIT;
E 2
	fc = IMP;
	padc = ' ';
	if (skip() || ismot(j = getch()) || (i = cbits(j)) == '\n')
		return;
	fc = i;
I 2
	gchtab[fc] |= FCBIT;
E 2
	if (skip() || ismot(ch) || (ch = cbits(ch)) == fc)
		return;
	padc = ch;
}


D 2
tchar setfield(x)
E 2
I 2
tchar
setfield(x)
E 2
int	x;
{
D 2
	tchar ii, jj, *fp;
E 2
I 2
	register tchar ii, jj, *fp;
E 2
	register i, j;
D 2
	int	length, ws, npad, temp, type;
	tchar * *pp, *padptr[NPP];
	static tchar fbuf[FBUFSZ];
	int	savfc, savtc, savlc;
E 2
I 2
	int length, ws, npad, temp, type;
	tchar **pp, *padptr[NPP];
	tchar fbuf[FBUFSZ];
	int savfc, savtc, savlc;
	tchar rchar;
	int savepos;
E 2

	if (x == tabch) 
		rchar = tabc | chbits;
	else if (x ==  ldrch) 
		rchar = dotc | chbits;
	temp = npad = ws = 0;
	savfc = fc;
	savtc = tabch;
	savlc = ldrch;
	tabch = ldrch = fc = IMP;
I 2
	savepos = numtab[HP].val;
	gchtab[tabch] &= ~TABBIT;
	gchtab[ldrch] &= ~LDRBIT;
	gchtab[fc] &= ~FCBIT;
	gchtab[IMP] |= TABBIT|LDRBIT|FCBIT;
E 2
	for (j = 0; ; j++) {
D 2
		if ((tabtab[j] & TMASK) == 0) {
E 2
I 2
		if ((tabtab[j] & TABMASK) == 0) {
E 2
			if (x == savfc)
D 2
				fprintf(stderr, "troff: zero field width.\n");
E 2
I 2
				errprint("zero field width.");
E 2
			jj = 0;
			goto rtn;
		}
D 2
		v.hp = sumhp();	/* XXX */
		if ((length = ((tabtab[j] & TMASK) - v.hp)) > 0 )
E 2
I 2
		if ((length = ((tabtab[j] & TABMASK) - numtab[HP].val)) > 0 )
E 2
			break;
	}
D 2
	type = tabtab[j] & (~TMASK);
E 2
I 2
	type = tabtab[j] & (~TABMASK);
E 2
	fp = fbuf;
	pp = padptr;
	if (x == savfc) {
		while (1) {
D 2
			if (((j = cbits(ii = getch()))) == padc) {
E 2
I 2
			j = cbits(ii = getch());
			jj = width(ii);
			widthp = jj;
			numtab[HP].val += jj;
			if (j == padc) {
E 2
				npad++;
				*pp++ = fp;
				if (pp > (padptr + NPP - 1))
					break;
				goto s1;
			} else if (j == savfc) 
				break;
			else if (j == '\n') {
				temp = j;
				nlflg = 0;
				break;
			}
D 2
			ws += width(ii);
E 2
I 2
			ws += jj;
E 2
s1:
			*fp++ = ii;
			if (fp > (fbuf + FBUFSZ - 3))
				break;
		}
		if (!npad) {
			npad++;
			*pp++ = fp;
			*fp++ = 0;
		}
		*fp++ = temp;
		*fp++ = 0;
		temp = i = (j = length - ws) / npad;
		i = (i / HOR) * HOR;
		if ((j -= i * npad) < 0)
			j = -j;
		ii = makem(i);
		if (temp < 0)
			ii |= NMOT;
		for (; npad > 0; npad--) {
			*(*--pp) = ii;
			if (j) {
				j -= HOR;
				(*(*pp)) += HOR;
			}
		}
D 2
		cp = fbuf;
E 2
I 2
		pushback(fbuf);
E 2
		jj = 0;
	} else if (type == 0) {
		/*plain tab or leader*/
D 2
		if ((j = width(rchar)) == 0)
			nchar = 0;
		else {
			nchar = length / j;
E 2
I 2
		if ((j = width(rchar)) > 0) {
			int nchar = length / j;
			while (nchar-->0 && pbp < &pbbuf[NC-3]) {
				numtab[HP].val += j;
				widthp = j;
				*pbp++ = rchar;
			}
E 2
			length %= j;
		}
		if (length)
			jj = length | MOT;
		else 
			jj = getch0();
	} else {
		/*center tab*/
		/*right tab*/
		while (((j = cbits(ii = getch())) != savtc) &&  (j != '\n') && (j != savlc)) {
D 2
			ws += width(ii);
E 2
I 2
			jj = width(ii);
			ws += jj;
			numtab[HP].val += jj;
			widthp = jj;
E 2
			*fp++ = ii;
			if (fp > (fbuf + FBUFSZ - 3)) 
				break;
		}
		*fp++ = ii;
		*fp++ = 0;
		if (type == RTAB)
			length -= ws;
		else 
			length -= ws / 2; /*CTAB*/
D 2
		if (((j = width(rchar)) == 0) || (length <= 0))
			nchar = 0;
		else {
			nchar = length / j;
E 2
I 2
		pushback(fbuf);
		if ((j = width(rchar)) != 0 && length > 0) {
			int nchar = length / j;
			while (nchar-- > 0 && pbp < &pbbuf[NC-3])
				*pbp++ = rchar;
E 2
			length %= j;
		}
		length = (length / HOR) * HOR;
		jj = makem(length);
D 2
		cp = fbuf;
E 2
		nlflg = 0;
	}
rtn:
I 2
	gchtab[fc] &= ~FCBIT;
	gchtab[tabch] &= ~TABBIT;
	gchtab[ldrch] &= ~LDRBIT;
E 2
	fc = savfc;
	tabch = savtc;
	ldrch = savlc;
I 2
	gchtab[fc] |= FCBIT;
	gchtab[tabch] = TABBIT;
	gchtab[ldrch] |= LDRBIT;
	numtab[HP].val = savepos;
E 2
	return(jj);
}


E 1
