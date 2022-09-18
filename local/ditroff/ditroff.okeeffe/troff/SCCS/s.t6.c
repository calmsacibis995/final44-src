h51246
s 00034/00000/00916
d D 2.6 93/02/25 17:19:21 sklower 7 6
c Long since forgotten attempts to integrate gremlin support into
c a slightly later version of ditroff
e
s 00004/00001/00912
d D 2.5 90/11/30 15:44:12 karels 6 5
c checkpoint before sklower mucks around with it (by sklower)
e
s 00040/00025/00873
d D 2.4 90/11/03 20:41:48 karels 5 4
c changes to allow use of fonts > nfonts (caching font data for fonts
c nfonts+1...NFONTS; other minor cleanups
e
s 00002/00002/00896
d D 2.3 90/11/03 20:30:14 karels 4 3
c fix problem with ligatures in fonts mapped onto 0 (> nfonts)
e
s 00011/00002/00887
d D 2.2 87/07/10 17:05:42 jaap 3 2
c Dealing OK now with ligatures and the font cache
e
s 00264/00246/00625
d D 2.1 85/07/18 14:29:35 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00871/00000/00000
d D 1.1 85/07/17 17:54:59 jaap 1 0
c date and time created 85/07/17 17:54:59 by jaap
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
static char sccsid[] = "@(#)t6.c	2.2 (CWI) 87/07/10";
E 4
#endif lint
I 2
/*
 * t6.c
 * 
 * width functions, sizes and fonts
 */
E 2

#include "tdef.h"
D 2
extern
#include "d.h"
extern
#include "v.h"
E 2
#include "dev.h"
D 2
#include <ctype.h>
/*
troff6.c

width functions, sizes and fonts
*/

E 2
#include <sgtty.h>
I 2
#include <ctype.h>
E 2
#include "ext.h"
D 2
int	trflg;
E 2
I 2

E 2
/* fitab[f][c] is 0 if c is not on font f
	/* if it's non-zero, c is in fontab[f] at position
	/* fitab[f][c].
	*/
D 2
int	fontlab[MAXFONTS+1];	/* Need 1 extra for the fontcache */
E 2
I 2
extern	struct Font *fontbase[NFONT+1];
extern	char *codetab[NFONT+1];
extern int nchtab;

int	fontlab[MAXFONTS+1];
E 2
short	*pstab;
D 2
int	cstab[MAXFONTS+1], ccstab[MAXFONTS+1];
E 2
I 2
int	cstab[MAXFONTS+1];
int	ccstab[MAXFONTS+1];
E 2
int	bdtab[MAXFONTS+1];
int	sbold = 0;

width(j)
D 2
tchar j;
E 2
I 2
register tchar j;
E 2
{
	register i, k;

D 2
	k = 0;
	i = cbits(j);
	if (ismot(j)) {
E 2
I 2
	if (j & (ZBIT|MOT)) {
		if (iszbit(j))
			return(0);
E 2
		if (isvmot(j))
D 2
			goto rtn;
E 2
I 2
			return(0);
E 2
		k = absmot(j);
		if (isnmot(j))
			k = -k;
D 2
		goto rtn;
E 2
I 2
		return(k);
E 2
	}
D 2
	if (i == '\b') {
		k = -widthp;
		goto rtn;
E 2
I 2
	i = cbits(j);
	if (i < ' ') {
		if (i == '\b')
			return(-widthp);
		if (i == PRESC)
			i = eschar;
		else if (iscontrol(i))
			return(0);
E 2
	}
D 2
	if (i == PRESC)
		i = eschar;
	else if (i == ohc || iscontrol(i))
		goto rtn;
E 2
I 2
	if (i==ohc)
		return(0);
	i = trtab[i];
	if (i < 32)
		return(0);
E 2
	if (sfbits(j) == oldbits) {
		xfont = pfont;
		xpts = ppts;
	} else 
D 2
		xbits(j);
	if (iszbit(j))
		goto rtn;
	if (!trflg)
		i = trtab[i];
	if ((i -= 32) < 0)
		goto rtn;
	k = getcw(i);
	if (bd)
		k += (bd - 1) * HOR;
	if (cs)
		k = cs;
E 2
I 2
		xbits(j, 0);
	if (widcache[i-32].fontpts == (xfont<<8) + xpts && !setwdf)
		k = widcache[i-32].width;
	else {
		k = getcw(i-32);
		if (bd)
			k += (bd - 1) * HOR;
		if (cs)
			k = cs;
	}
E 2
	widthp = k;
D 2
rtn:
	xbitf = trflg = 0;
E 2
	return(k);
}

I 2
/*
 * clear width cache-- s means just space
 */
zapwcache(s)
{
	register i;
E 2

I 2
	if (s) {
		widcache[0].fontpts = 0;
		return;
	}
	for (i=0; i<NWIDCACHE; i++)
		widcache[i].fontpts = 0;
}

E 2
getcw(i)
register int	i;
{
	register int	k;
	register char	*p;
D 2
	int	x, j;
E 2
I 2
	register int	x, j;
	int nocache = 0;
E 2
	int	savxfont = 0, savsbold = 0, savulfont = 0;

	/*
D 2
	 * Here comes the kludgy bug fix itself
E 2
I 2
	 * Here comes first part of bug fix
E 2
	 */

D 2
	if( xfont > nfonts) {		/* not mounted font */
E 2
I 2
	if( xfont > nfonts) {		/* font is not mounted */
E 2
		savxfont = xfont;
		if( xfont == sbold) {
			savsbold = sbold;
			sbold = 0;
		}
		if( xfont == ulfont) {
			savulfont = ulfont;
			ulfont = 0;
		}
		xfont = 0;
D 2
		setfp(0, fontlab[savxfont]);
		bdtab[0] = bdtab[savxfont];	/* Just */
		cstab[0] = cstab[savxfont];	/*  in  */
		ccstab[0] = ccstab[savxfont];	/* case */
E 2
I 2
		setfp(0, fontlab[savxfont], 0);
		bdtab[0] = bdtab[savxfont];	/* Save */
		cstab[0] = cstab[savxfont];	/*  as  */
		ccstab[0] = ccstab[savxfont];	/* well */
E 2
	}
I 2
	/* End */
E 2

I 2

E 2
	bd = 0;
I 2
	if (i >= nchtab + 128-32) {
		j = abscw(i + 32 - (nchtab+128));
		goto g0;
	}
E 2
	if (i == 0) {	/* a blank */
		k = (fontab[xfont][0] * spacesz + 6) / 12;
		/* this nonsense because .ss cmd uses 1/36 em as its units */
		/* and default is 12 */
		goto g1;
	}
D 2
	if ((j = fitab[xfont][i] & BMASK) == 0) {	/* it's not on current font */
E 2
I 2
	if ((j = fitab[xfont][i] & BYTEMASK) == 0) {	/* it's not on current font */
E 2
		/* search through search list of xfont
		/* to see what font it ought to be on.
D 2
		/* for now, searches S, then remaining fonts in wraparound
		 * order (but only when a special font is mounted!!)
E 2
I 2
		/* searches S, then remaining fonts in wraparound order.
E 2
		*/
I 2
		nocache = 1;
E 2
		if (smnt) {
D 2
			int	ii, jj;
E 2
I 2
			int ii, jj;
E 2
			for (ii=smnt, jj=0; jj < nfonts; jj++, ii=ii % nfonts + 1) {
D 2
				j = fitab[ii][i] & BMASK;
E 2
I 2
				j = fitab[ii][i] & BYTEMASK;
E 2
				if (j != 0) {
					p = fontab[ii];
					k = *(p + j);
D 2
					if (xfont == sbold && ii >= smnt)
						/* Oops, only set bd
						 * when it is a special
						 * font!!
						 */
E 2
I 2
					if (xfont == sbold)
E 2
						bd = bdtab[ii];
					if (setwdf)
D 2
						v.ct |= kerntab[ii][j];
E 2
I 2
						numtab[CT].val |= kerntab[ii][j];
E 2
					goto g1;
				}
			}
		}
D 2
		code = 0;
E 2
		k = fontab[xfont][0];	/* leave a space-size space */
		goto g1;
	}
I 2
 g0:
E 2
	p = fontab[xfont];
	if (setwdf)
D 2
		v.ct |= kerntab[xfont][j];
E 2
I 2
		numtab[CT].val |= kerntab[xfont][j];
E 2
	k = *(p + j);
D 2
g1:
E 2
I 2
 g1:
E 2
	if (!bd)
		bd = bdtab[xfont];
	if (cs = cstab[xfont]) {
I 2
		nocache = 1;
E 2
		if (ccs = ccstab[xfont])
			x = ccs; 
		else 
			x = xpts;
		cs = (cs * EMPTS(x)) / 36;
	}
D 2

E 2
I 2
	k = ((k&BYTEMASK) * xpts + (Unitwidth / 2)) / Unitwidth;
E 2
	/*
D 2
	 * undo the kludge
E 2
I 2
	 * undo the fontswap
E 2
	 */
	if(savxfont) {
		xfont = savxfont;
		if(savsbold)
			sbold = savsbold;
		if(savulfont)
			ulfont = savulfont;
I 2
		/*
		 * H'm, I guess we should not put
		 * this width in the cache
		 */
		nocache = 1;
E 2
	}
D 2

	return(((k&BMASK) * xpts + (Unitwidth / 2)) / Unitwidth);
E 2
I 2
	if (nocache|bd)
		widcache[i].fontpts = 0;
	else {
		widcache[i].fontpts = (xfont<<8) + xpts;
		widcache[i].width = k;
	}
	return(k);
E 2
	/* Unitwidth is Units/Point, where
	/* Units is the fundamental digitization
	/* of the character set widths, and
	/* Point is the number of goobies in a point
	/* e.g., for cat, Units=36, Point=6, so Unitwidth=36/6=6
	/* In effect, it's the size at which the widths
	/* translate directly into units.
	*/
}

I 2
abscw(n)	/* return index of abs char n in fontab[], etc. */
{	register int i, ncf;
E 2

D 2
xbits(i)
tchar i;
E 2
I 2
	ncf = fontbase[xfont]->nwfont & BYTEMASK;
	for (i = 0; i < ncf; i++)
		if (codetab[xfont][i] == n)
			return i;
	return 0;
}

xbits(i, bitf)
register tchar i;
E 2
{
D 2
	register j, k;
E 2
I 2
	register k;
E 2

	xfont = fbits(i);
	k = sbits(i);
	if (k) {
		xpts = pstab[--k];
		oldbits = sfbits(i);
		pfont = xfont;
		ppts = xpts;
D 2
		goto rtn;
E 2
I 2
		return;
E 2
	}
D 2
	switch (xbitf) {
E 2
I 2
	switch (bitf) {
E 2
	case 0:
		xfont = font;
		xpts = pts;
		break;
	case 1:
		xfont = pfont;
		xpts = ppts;
		break;
	case 2:
		xfont = mfont;
		xpts = mpts;
	}
D 2
rtn:
	xbitf = 0;
E 2
}


tchar setch()
{
	register j;
	char	temp[10];
	register char	*s;
	extern char	*chname;
	extern short	*chtab;
	extern int	nchtab;

	s = temp;
	if ((*s++ = getach()) == 0 || (*s++ = getach()) == 0)
		return(0);
	*s = '\0';
	for (j = 0; j < nchtab; j++)
		if (strcmp(&chname[chtab[j]], temp) == 0)
			return(j + 128 | chbits);
	return(0);
}

D 2

tchar absch()	/* absolute character number */
E 2
I 2
tchar setabs()		/* set absolute char from \C'...' */
E 2
{
D 2
	fprintf(stderr, "troff: no \\C yet (How do you know about it?)\n");
	return(0);
}
E 2
I 2
	int i, n, nf;
	extern int	nchtab;
E 2

D 2
/*****
E 2
I 2
	getch();
	n = 0;
	n = inumb(&n);
	getch();
	if (nonumb)
		return 0;
	return n + nchtab + 128;
}
/*
 * I (jaap) expand fontlab to the maximum of fonts troff can
 * handle. The maximum number i, due to the two chars
 * fontname limit, is 99.
 * If we don't use the (named) font in one of the
 * standard position, we install the name in the next
 * free slot. Whenever we need info about the font, we
 * read in the data at position zero, and secretly use
 * the data (actually only necessary for the width
 * and ligature info). The ptfont() (t10.c) routine will tell
 * the device filter to put the font always at position
D 5
 * zero if xfont > nfonts, so no need to change these filters.
E 5
I 5
 * zero if xfont > physfonts, so no need to change these filters.
E 5
 * Yes, this is a bit kludgy.
 *
 * This gives the new specs of findft:
 *
E 2
 * find the font name i, where i also can be a number.
 *
D 2
 * Installs the font i when not present
E 2
I 2
 * Installs the font(name) i when not present
E 2
 *
 * returns -1 on error
 */

findft(i)
register int	i;
{
	register k;
D 2
	char	name[2];
E 2
I 2
	register char *p;
	extern char * unpair();
E 2

D 2
	name[0] = i & BMASK;
	name[1] = i >> BYTE;
E 2
I 2
	p = unpair(i);
E 2

D 2
	if( isdigit(name[0])) {		/* first look for numbers */
		k = name[0] - '0';
		if( name[1] > 0 && isdigit(name[1]))
			k = 10 * k + ( name[1] - '0');
E 2
I 2
D 5
	if( isdigit(p[0])) {		/* first look for numbers */
E 5
I 5
	/* first look for numbers */
D 6
	if( isdigit(p[0] && (p[1] == 0 || isdigit(p[1])))) {
E 6
I 6
	if( isdigit(p[0]) && (p[1] == 0 || isdigit(p[1]))) {
E 6
E 5
		k = p[0] - '0';
		if( p[1] > 0 && isdigit(p[1]))
			k = 10 * k + ( p[1] - '0');
E 2

		/*
		fprintf(ptid, "x xxx it's a number: %d\n", k);
		*/
D 5
		if( k > 0 && k <= nfonts && k < smnt ) {
E 5
I 5
		if( k > 0 && k <= nfonts && fontbase[k]->specfont == 0 ) {
E 5
			/*
			fprintf(ptid, "x xxx it's a mounted font\n");
			*/
			return(k);	/* mounted font */
		}
		if( fontlab[k] && k <= MAXFONTS) {	/* translate */
			/*
			fprintf(ptid, "x xxx font exists\n");
			*/
			return(k);			/*number to a name */
		}
		else {
			fprintf(stderr, "troff: no font at position %d\n", k);
			return(-1);	/* wild number */
		}
	}

	/*
	 * Now we look for font names
	 */
	for (k = 1; fontlab[k] != i; k++) {
		if (k > MAXFONTS +1)	/* the +1 is for the ``font cache'' */
			return(-1);	/* running out of fontlab space */
		if ( !fontlab[k] ) {	/* passed all existing names */
D 2
			if(setfp(0, i) < 0)
E 2
I 2
D 5
			if(setfp(0, i, 0) < 0)
E 2
				return(-1);
			else {
E 5
I 5
			if (k <= NFONT) {
				if(setfp(k, i, 0) < 0)
					return(-1);
				nfonts = k;
			} else
				if(setfp(0, i, 0) < 0)
					return(-1);
			/*
			fprintf(ptid, "x xxx installed %s on %d\n", name ,k);
			*/
				/* now install the name */
			fontlab[k] = i;
E 5
				/*
D 5
				fprintf(ptid, "x xxx installed %s on %d\n", name ,k);
E 5
I 5
				 * and remember accociated with
				 * this font, ligature info etc.
E 5
				*/
D 3
				fontlab[k] = i;	/* install the name */
E 3
I 3
D 5
					/* now install the name */
				fontlab[k] = i;
					/*
					 * and remember accociated with
					 * this font, ligature info etc.
					*/
E 3
				return(k);
			}
E 5
I 5
			return(k);
E 5
		}
	}
	return(k);			/* was one of the existing names */
}


caseps()
{
	register i;

	if (skip())
		i = apts1;
	else {
		noscale++;
		i = inumb(&apts);	/* this is a disaster for fractional point sizes */
		noscale = 0;
		if (nonumb)
			return;
	}
	casps1(i);
}


casps1(i)
register int	i;
{
I 2

/*
 * in olden times, it used to ignore changes to 0 or negative.
 * this is meant to allow the requested size to be anything,
 * in particular so eqn can generate lots of \s-3's and still
 * get back by matching \s+3's.

E 2
	if (i <= 0)
		return;
I 2
*/
E 2
	apts1 = apts;
	apts = i;
	pts1 = pts;
	pts = findps(i);
	mchbits();
}


findps(i)
register int	i;
{
	register j, k;

D 2
	for (j = 0; i > (k = pstab[j]); j++)
		if (!k) {
			k = pstab[--j];
			break;
		}
	return(k);
E 2
I 2
	for (j=k=0 ; pstab[j] != 0 ; j++)
		if (abs(pstab[j]-i) < abs(pstab[k]-i))
			k = j;

	return(pstab[k]);
E 2
}


mchbits()
{
	register i, j, k;

	i = pts;
	for (j = 0; i > (k = pstab[j]); j++)
		if (!k) {
			k = pstab[--j];
			break;
		}
	chbits = 0;
	setsbits(chbits, ++j);
	setfbits(chbits, font);
	sps = width(' ' | chbits);
I 2
	zapwcache(1);
E 2
}

D 2

E 2
setps()
{
D 2
	register i, j;
E 2
I 2
	register int i, j;
E 2

D 2
	if (((i = cbits(getch())) == '+' || i == '-') && (j = cbits(ch = getch()) - '0') >= 0 && j <= 9) {
E 2
I 2
	i = cbits(getch());
	if (isdigit(i)) {		/* \sd or \sdd */
		i -= '0';
		if (i == 0)		/* \s0 */
			j = apts1;
		else if (i <= 3 && isdigit(j = cbits(ch=getch()))) {	/* \sdd */
			j = 10 * i + j - '0';
			ch = 0;
		} else		/* \sd */
			j = i;
	} else if (i == '(') {		/* \s(dd */
		j = cbits(getch()) - '0';
		j = 10 * j + cbits(getch()) - '0';
		if (j == 0)		/* \s(00 */
			j = apts1;
	} else if (i == '+' || i == '-') {	/* \s+, \s- */
		j = cbits(getch());
		if (isdigit(j)) {		/* \s+d, \s-d */
			j -= '0';
		} else if (j == '(') {		/* \s+(dd, \s-(dd */
			j = cbits(getch()) - '0';
			j = 10 * j + cbits(getch()) - '0';
		}
E 2
		if (i == '-')
			j = -j;
D 2
		ch = 0;
		casps1(apts + j);
		return;
E 2
I 2
		j += apts;
E 2
	}
D 2
	if ((i -= '0') == 0) {
		casps1(apts1);
		return;
	}
	if (i > 0 && i <= 9) {
		/* removed if (i <= 3 && */
		/* didn't work!!!! */
		if (i <= 3 && (j = cbits(ch = getch()) - '0') >= 0 && j <= 9) {
			i = 10 * i + j;
			ch = 0;
		}
		casps1(i);
	}
E 2
I 2
	casps1(j);
E 2
}


tchar setht()		/* set character height from \H'...' */
{
	int n;
	tchar c;

	getch();
	n = inumb(&apts);
	getch();
	if (n == 0 || nonumb)
		n = apts;	/* does this work? */
	c = CHARHT;
	c |= ZBIT;
	setsbits(c, n);
	return(c);
}

tchar setslant()		/* set slant from \S'...' */
{
	int n;
	tchar c;

	getch();
	n = 0;
	n = inumb(&n);
	getch();
	if (nonumb)
		n = 0;
	c = SLANT;
	c |= ZBIT;
	setsfbits(c, n+180);
	return(c);
}


I 7
casest()
{
	register i, j;
	register char last;

	skip();
	i = getrq();
	if (!i || i == 'P') {
	    stip = stip1;
	    return;
	}
	if (i == '0')
	    goto sterr;

	last = cbits(i) >> BYTE;
	if ((j = (i & BYTEMASK) - '0') >= 0 && j <= 9) {/* digit - see if two */
	    if (last)
		if ((last -= '0') < 0 || last > 9)
		    goto sterr;
	    if (j > nstips)
		goto sterr;
	} else {					/* stipple name */
	    for (j = 0; stiplab[j] != i; j++)
		if (j > nstips)
		    goto sterr;
	}
	stip1 = stip;
	stip = j;
	return;
sterr:
	fprintf(stderr, "troff: Can't find stipple %c%c\n", i & BYTEMASK, last);
}


E 7
caseft()
{
	skip();
	setfont(1);
}


setfont(a)
int	a;
{
	register i, j;

	if (a)
		i = getrq();
	else 
		i = getsn();
	if (!i || i == 'P') {
D 2
				/*
				 * when .ft <zero argument or the
				 	     argument is the non-documented P,>
				 * pop previous font.
				 * Alas, if the current font is in the
				 * font cache already, we have to be
				 * be very careful. No solution yet
				 * for this bug.
				 */
E 2
		j = font1;
		goto s0;
	}
	if (i == 'S' || i == '0')
		return;
	if ((j = findft(i)) == -1)
I 6
#ifdef notdef
		/* findft does the setfp if possible */
E 6
D 2
			return;		/* unable to find or mount font */
E 2
I 2
		if ((j = setfp(0, i, 0)) == -1)	/* try to put it in position 0 */
I 6
#endif
E 6
			return;
E 2
s0:
	font1 = font;
	font = j;
	mchbits();
}


setwd()
{
	register base, wid;
D 2
	tchar i;
	int	delim, em, k;
	int	savlevel, savhp, savapts, savapts1, savfont, savfont1, savpts, savpts1;
	tchar *savpinchar, *p, *q, tempinchar[LNSIZE];	/* XXX */
E 2
I 2
	register tchar i;
	int	delim, emsz, k;
	int	savhp, savapts, savapts1, savfont, savfont1, savpts, savpts1;
E 2

D 2
	base = v.st = v.sb = wid = v.ct = 0;
E 2
I 2
	base = numtab[ST].val = numtab[ST].val = wid = numtab[CT].val = 0;
E 2
	if (ismot(i = getch()))
		return;
	delim = cbits(i);
D 2
	savhp = v.hp;
	savpinchar = pinchar;	/* XXX */
	for (p=inchar, q=tempinchar; p < pinchar; )	/* XXX */
		*q++ = *p++;	/* XXX */
	pinchar = inchar;	/* XXX */
	savlevel = level;
	v.hp = level = 0;
E 2
I 2
	savhp = numtab[HP].val;
	numtab[HP].val = 0;
E 2
	savapts = apts;
	savapts1 = apts1;
	savfont = font;
	savfont1 = font1;
	savpts = pts;
	savpts1 = pts1;
	setwdf++;
	while (cbits(i = getch()) != delim && !nlflg) {
D 2
		wid += width(i);
E 2
I 2
		k = width(i);
		wid += k;
		numtab[HP].val += k;
E 2
		if (!ismot(i)) {
D 2
			em = POINT * xpts;
E 2
I 2
			emsz = POINT * xpts;
E 2
		} else if (isvmot(i)) {
			k = absmot(i);
			if (isnmot(i))
				k = -k;
			base -= k;
D 2
			em = 0;
E 2
I 2
			emsz = 0;
E 2
		} else 
			continue;
D 2
		if (base < v.sb)
			v.sb = base;
		if ((k = base + em) > v.st)
			v.st = k;
E 2
I 2
		if (base < numtab[SB].val)
			numtab[SB].val = base;
		if ((k = base + emsz) > numtab[ST].val)
			numtab[ST].val = k;
E 2
	}
D 2
	nform = 0;
	setn1(wid);
	v.hp = savhp;
	pinchar = savpinchar;	/* XXX */
	for (p=inchar, q=tempinchar; p < pinchar; )	/* XXX */
		*p++ = *q++;	/* XXX */
	level = savlevel;
E 2
I 2
	setn1(wid, 0, (tchar) 0);
	numtab[HP].val = savhp;
E 2
	apts = savapts;
	apts1 = savapts1;
	font = savfont;
	font1 = savfont1;
	pts = savpts;
	pts1 = savpts1;
	mchbits();
	setwdf = 0;
}


tchar vmot()
{
	dfact = lss;
	vflag++;
	return(mot());
}


tchar hmot()
{
	dfact = EM;
	return(mot());
}


tchar mot()
{
D 2
	register short j, n;
	tchar i;
E 2
I 2
	register int j, n;
	register tchar i;
E 2

	j = HOR;
	getch(); /*eat delim*/
	if (n = atoi()) {
		if (vflag)
			j = VERT;
		i = makem(quant(n, j));
	} else
		i = 0;
	getch();
	vflag = 0;
	dfact = 1;
	return(i);
}


tchar sethl(k)
int	k;
{
	register j;
	tchar i;

	j = EM / 2;
	if (k == 'u')
		j = -j;
	else if (k == 'r')
		j = -2 * j;
	vflag++;
	i = makem(j);
	vflag = 0;
	return(i);
}


tchar makem(i)
D 2
int	i;
E 2
I 2
register int	i;
E 2
{
D 2
	tchar j;
E 2
I 2
	register tchar j;
E 2

	if ((j = i) < 0)
		j = -j;
	j |= MOT;
	if (i < 0)
		j |= NMOT;
	if (vflag)
		j |= VMOT;
	return(j);
}


tchar getlg(i)
tchar i;
{
	tchar j, k;
D 2
	register int lf, tmp;
E 2
I 2
	register int lf;
E 2

D 2
	tmp = fbits(i);
	if(tmp > nfonts) {
		if( setfp(0, fontlab[tmp]) < 0)
			return(i);
		else
			tmp = 0;
	}

	if ((lf = fontbase[tmp]->ligfont) == 0)	/* the font has no ligatures */
E 2
I 2
D 3
	if ((lf = fontbase[fbits(i)]->ligfont) == 0) /* font lacks ligatures */
E 3
I 3
		/* remember to map the font */
D 4
	if ((lf = fontbase[fbits(i) > NFONT ? 0 : fbits(i)]->ligfont) == 0) {
E 4
I 4
	if ((lf = fontbase[fbits(i) > nfonts ? 0 : fbits(i)]->ligfont) == 0) {
E 4
		/* font lacks ligatures */
E 3
E 2
		return(i);
I 3
	}
E 3
	j = getch0();
	if (cbits(j) == 'i' && (lf & LFI))
		j = LIG_FI;
	else if (cbits(j) == 'l' && (lf & LFL))
		j = LIG_FL;
	else if (cbits(j) == 'f' && (lf & LFF)) {
		if ((lf & (LFFI|LFFL)) && lg != 2) {
			k = getch0();
			if (cbits(k)=='i' && (lf&LFFI))
				j = LIG_FFI;
			else if (cbits(k)=='l' && (lf&LFFL))
				j = LIG_FFL;
			else {
D 2
				ch0 = k;
E 2
I 2
				*pbp++ = k;
E 2
				j = LIG_FF;
			}
		} else 
			j = LIG_FF;
	} else {
D 2
		ch0 = j;
E 2
I 2
		*pbp++ = j;
E 2
		j = i;
	}
	return(i & SFMASK | j);
}


caselg()
{

	lg = 1;
	if (skip())
		return;
	lg = atoi();
}


casefp()
{
D 2
	register i, j;
	register char *p;
	char dir[50];
E 2
I 2
	register int i, j;
	register char *s;
E 2

	skip();
I 5
	/* allow .fp for fonts >nfonts, <NFONTS? */
E 5
	if ((i = cbits(getch()) - '0') <= 0 || i > nfonts)
D 2
		fprintf(stderr, "troff: fp: bad font position %d\n", i);
E 2
I 2
		errprint("fp: bad font position %d", i);
E 2
	else if (skip() || !(j = getrq()))
D 2
		fprintf(stderr, "troff: fp: no font name\n"); 
	else {
		/* should check for third argument, (directory)
		 * doesn't work at all */
		skip();
		setfp(i, j);
	}
E 2
I 2
		errprint("fp: no font name"); 
	else if (skip() || !getname())
		setfp(i, j, 0);
	else		/* 3rd argument = filename */
		setfp(i, j, nextf);
E 2
}

D 2
setfp(pos, f)	/* mount font f at position pos[0...nfonts] */
E 2
I 2
D 5
setfp(pos, f, truename)	/* mount font f at position pos[0...nfonts] */
E 2
int pos, f;
E 5
I 5
setfp(pos, f, truename)	/* mount font f at position pos[0...NFONTS] */
register pos;
int f;
E 5
I 2
char *truename;
E 2
{
D 2
	register i, j, k;
E 2
I 2
	register k;
I 5
	register struct Font *ft;
E 5
E 2
	int n;
D 2
	char	longname[NS], shortname[10], *p;
	extern int	nchtab;
E 2
I 2
	char longname[NS], shortname[20];
	extern int nchtab;
I 5
	extern struct dev dev;
E 5
E 2

D 2
	if( fontlab[pos] == f)			/* f already mounted at pos, */
		return(pos);			/* don't remount it */
	shortname[0] = f & BMASK;
	shortname[1] = f >> BYTE;
	shortname[2] = '\0';
E 2
I 2
	if (fontlab[pos] == f)		/* if f already mounted at pos, */
		return(pos);		/* don't remount it */
	zapwcache(0);
	if (truename)
		strcpy(shortname, truename);
	else {
		shortname[0] = f & BYTEMASK;
		shortname[1] = f >> BYTE;
		shortname[2] = '\0';
	}
E 2
	sprintf(longname, "%s/dev%s/%s.out", fontfile, devname, shortname);
D 2

E 2
	if ((k = open(longname, 0)) < 0) {
D 2
		fprintf(stderr, "troff: Can't open %s\n", longname);
E 2
I 2
		errprint("Can't open %s", longname);
E 2
		return(-1);
	}
D 2
	n = fontbase[pos]->nwfont & BMASK;
	read(k, fontbase[pos], 3*n + nchtab + 128 - 32 + sizeof(struct font));
	kerntab[pos] = (char *) fontab[pos] + (fontbase[pos]->nwfont & BMASK);
E 2
I 2
D 5
	n = fontbase[pos]->nwfont & BYTEMASK;
	read(k, (char *) fontbase[pos], 3*n + nchtab + 128 - 32 + sizeof(struct Font));
E 5
I 5
	if ((ft = fontbase[pos]) == 0) {
		ft = fontbase[pos] = (struct Font *) malloc(EXTRAFONT);
		ft->nwfont = MAXCHARS;
		fontab[pos] = (char *)(ft + 1);
	}
	n = ft->nwfont;
	read(k, (char *) ft, 3*n + nchtab + 128 - 32 + sizeof(struct Font));
	close(k);
E 5
I 3

E 3
D 5
	kerntab[pos] = (char *) fontab[pos] + (fontbase[pos]->nwfont & BYTEMASK);
E 5
I 5
	k = ft->nwfont;
	kerntab[pos] = (char *) fontab[pos] + k;
	codetab[pos] = (char *) fontab[pos] + 2 * k;
E 5
E 2
	/* have to reset the fitab pointer because the width may be different */
D 2
	fitab[pos] = (char *) fontab[pos] + 3 * (fontbase[pos]->nwfont & BMASK);
	if ((fontbase[pos]->nwfont & BMASK) > n) {
		fprintf(stderr, "troff: Font %s too big for position %d\n", shortname, pos);
E 2
I 2
D 5
	fitab[pos] = (char *) fontab[pos] + 3 * (fontbase[pos]->nwfont & BYTEMASK);
	if ((fontbase[pos]->nwfont & BYTEMASK) > n) {
E 5
I 5
	fitab[pos] = (char *) fontab[pos] + 3 * k;
	ft->nwfont = n;	/* so can load a larger one again later */
	if (k > n) {
E 5
		errprint("Font %s too big for position %d", shortname, pos);
E 2
		return(-1);
	}
D 5
	fontbase[pos]->nwfont = n;	/* so can load a larger one again later */
	close(k);
E 5
	if (pos == smnt) {
D 2
		smnt = 0;	/* Small bug here, we should test for
				 * other special fonts mounted, needs
				 * to be fixed in future
				 */
E 2
I 2
		smnt = 0; 
E 2
		sbold = 0; 
	}
	if ((fontlab[pos] = f) == 'S')
		smnt = pos;
	bdtab[pos] = cstab[pos] = ccstab[pos] = 0;
		/* if there is a directory, no place to store its name. */
		/* if position isn't zero, no place to store its value. */
		/* only time a FONTPOS is pushed back is if it's a */
		/* standard font on position 0 (i.e., mounted implicitly. */
		/* there's a bug here:  if there are several input lines */
		/* that look like .ft XX in short successtion, the output */
		/* will all be in the last one because the "x font ..." */
		/* comes out too soon.  pushing back FONTPOS doesn't work */
		/* with .ft commands because input is flushed after .xx cmds */

D 2
		/* Trying to fix this problem:
		 *
		 * I expand fontlab to the maximum of fonts troff can
		 * handle. The maximum number i, due to the two chars
		 * fontname limit, is 99.
		 * If we don't use the (named) font in one of the
		 * standard position, we install the name in the next
		 * free slot. Whenever we need info about the font, we
		 * read in the data at position zero, and secretly use
		 * the data (actually only necessary for the width
		 *  and ligature info). The ptfont() routine will tell
		 * the device filter to put the font always at position
		 * zero, so no need to change these filters.
		 * Yes, this is a bit kludgy.
		 *
		 * BTW, I removed the directory stuff completly since
		 * setfp is always called as setfp(x, y, 0).
		 *
		 * TODO: It must be possible to do this with all the
		 * font positions. Dynamically switch the ``mounted''
		 * fonts in a LRU style, whithout bothering the user
		 * with it. Then they never have to use the .fp
		 * request. For compatibilty reason we could leave it
		 * in (it can shuffle the date in the fontlab table),
		 * or make it a NOOP.
		 * Of course we do not touch positions with a ``Special'' font.
		 *
		 * Simple things TODO
		 * 	A routine to extract two characters troff
		 *	  names is handy.
		 *	A routine to find out whether a font discription
		 *	  file is available, currently setfp(...)
		 *	  handle this and read in the font when
		 *	  appropriate. (Proposing ftstat() here).
		 *	Fix the ``smnt info''.
E 2
I 2
		/*
		 * Trying to fix this FONTPOS problem: See findft()
E 2
		 */
D 2

	/*
	 * In case we are mounting a font to a standard position ...
	 */
	if( pos > 0 && pos <= nfonts)
E 2
I 2
D 5
	if ( pos > 0 && pos <= nfonts)
E 5
I 5
	if ( pos > 0 && pos <= physfonts)
E 5
E 2
		ptfpcmd(pos, shortname);
	return(pos);
}


casecs()
{
	register i, j;

	noscale++;
	skip();
	if (!(i = getrq()) || (i = findft(i)) < 0)
		goto rtn;
	skip();
	cstab[i] = atoi();
	skip();
	j = atoi();
	if (nonumb)
		ccstab[i] = 0;
	else
		ccstab[i] = findps(j);
rtn:
I 2
	zapwcache(0);
E 2
	noscale = 0;
}


casebd()
{
	register i, j, k;

I 2
	zapwcache(0);
E 2
	k = 0;
bd0:
	if (skip() || !(i = getrq()) || (j = findft(i)) == -1) {
		if (k)
			goto bd1;
		else 
			return;
	}
	if (j == smnt) {
		k = smnt;
		goto bd0;
	}
	if (k) {
		sbold = j;
		j = k;
D 2
		/* Undocumented feature here, you can only do .bd S F N,
		 * for one font F.
		 */
E 2
	}
bd1:
	skip();
	noscale++;
	bdtab[j] = atoi();
	noscale = 0;
}


casevs()
{
	register i;

	skip();
	vflag++;
	dfact = INCH; /* default scaling is points! */
	dfactd = 72;
	res = VERT;
	i = inumb(&lss);
	if (nonumb)
		i = lss1;
	/*	if(i < VERT)i = VERT; */
	if (i < VERT) 
		i = 0;
	lss1 = lss;
	lss = i;
}


casess()
{
	register i;

	noscale++;
	skip();
	if (i = atoi()) {
		spacesz = i & 0177;
I 2
		zapwcache(0);
E 2
		sps = width(' ' | chbits);
	}
	noscale = 0;
}


tchar xlss()
{
	/* stores \x'...' into
	/* two successive tchars.
	/* the first contains HX, the second the value,
	/* encoded as a vertical motion.
	/* decoding is done in n2.c by pchar().
	*/
	int	i;
D 2
	tchar c;
E 2

	getch();
	dfact = lss;
	i = quant(atoi(), VERT);
	dfact = 1;
	getch();
	if (i >= 0)
D 2
		ch0 = MOT | VMOT | i;
E 2
I 2
		*pbp++ = MOT | VMOT | i;
E 2
	else
D 2
		ch0 = MOT | VMOT | NMOT | -i;
	c = HX;
	dummy();
	return(c);
E 2
I 2
		*pbp++ = MOT | VMOT | NMOT | -i;
	return(HX);
}

char *
unpair(i)
register int i;
{	static char name[3];

	name[0] = i & BYTEMASK;
	name[1] = i >> BYTE;
	name[2] = 0;
	return (name);
E 2
}
E 1
