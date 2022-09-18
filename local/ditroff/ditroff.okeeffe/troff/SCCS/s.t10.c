h28633
s 00033/00027/00543
d D 2.7 93/02/25 17:19:29 sklower 8 7
c Long since forgotten attempts to integrate gremlin support into
c a slightly later version of ditroff
e
s 00024/00011/00546
d D 2.6 90/11/03 20:41:45 karels 7 6
c changes to allow use of fonts > nfonts (caching font data for fonts
c nfonts+1...NFONTS; other minor cleanups
e
s 00009/00023/00548
d D 2.5 90/11/03 20:36:16 karels 6 5
c changes from van: use malloc, stdio; in-memory environments
e
s 00017/00000/00554
d D 2.4 89/08/14 14:09:11 jaap 5 4
c checking stuff in, so charlie will stop sending me mail
e
s 00015/00006/00539
d D 2.3 88/03/18 15:51:51 jaap 4 3
c fixed bug in ptout0. code was plainly wrong
e
s 00002/00000/00543
d D 2.2 88/03/09 15:20:40 jaap 3 2
c added psfig support
e
s 00121/00110/00422
d D 2.1 85/07/18 14:29:16 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00532/00000/00000
d D 1.1 85/07/17 17:54:55 jaap 1 0
c date and time created 85/07/17 17:54:55 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 6
static char sccsid[] = "%W% (CWI) %E%";
E 6
I 6
/*
static char sccsid[] = "@(#)t10.c	2.4 (CWI) 89/08/14";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 6
#endif lint
D 2

E 2
#include "tdef.h"
D 2
extern
#include "d.h"
extern
#include "v.h"
/*
troff10.c

CAT interface
*/

E 2
#include <sgtty.h>
I 2
#include <ctype.h>
E 2
#include "ext.h"
I 2
/*
 * troff10.c
 * 
 * typesetter interface
 */

E 2
int	vpos	 = 0;	/* absolute vertical position on page */
int	hpos	 = 0;	/* ditto horizontal */

D 2
#define	T_IESC	16

E 2
short	*chtab;
char	*chname;
char	*fontab[NFONT+1];
char	*kerntab[NFONT+1];
char	*fitab[NFONT+1];
I 2
char	*codetab[NFONT+1];
E 2

int	Inch;
int	Hor;
int	Vert;
int	Unitwidth;
D 7
int	nfonts;
E 7
I 7
int	nfonts;		/* highest font num. in fontab */
int	physfonts;	/* highest font num. known to printer */
int	zfont;		/* internal font num. mapped to 0 on printer */
E 7
int	nsizes;
int	nchtab;
I 5
D 6
#ifndef 0
E 6
int	nstips;
I 8
int	xstip	= ~STIP;
E 8
tchar	*stiplab;
D 6
#endif
E 6
E 5

/* these characters are used as various signals or values
/* in miscellaneous places.
/* values are set in specnames in t10.c
*/

int	c_hyphen;
int	c_emdash;
int	c_rule;
int	c_minus;
D 2
int	c_narsp;
int	c_hnarsp;
E 2
int	c_fi;
int	c_fl;
int	c_ff;
int	c_ffi;
int	c_ffl;
int	c_acute;
int	c_grave;
int	c_under;
int	c_rooten;
int	c_boxrule;
int	c_lefthand;
I 2
int	c_dagger;
E 2

#include "dev.h"
struct dev dev;
D 2
struct font *fontbase[NFONT+1];
E 2
I 2
struct Font *fontbase[NFONT+1];
E 2


ptinit()
{
	int	i, fin, nw;
D 6
	char	*setbrk(), *filebase, *p;
E 6
I 6
	char	*filebase, *p;
E 6

	/* open table for device,
	/* read in resolution, size info, font info, etc.
	/* and set params
	*/
	strcat(termtab, "/dev");
	strcat(termtab, devname);
	strcat(termtab, "/DESC.out");	/* makes "..../devXXX/DESC.out" */
	if ((fin = open(termtab, 0)) < 0) {
D 2
		fprintf(stderr, "troff: can't open tables for %s\n", termtab);
E 2
I 2
		errprint("can't open tables for %s", termtab);
E 2
		done3(1);
	}
D 2
	read(fin, &dev, sizeof(struct dev ));
E 2
I 2
D 7
	read(fin, (char *) &dev, sizeof(struct dev ));
E 7
I 7
	if (read(fin, (char *) &dev, sizeof(struct dev)) < sizeof(struct dev)) {
		errprint("short read on %s", termtab);
		done3(1);
	}
E 7
E 2
	Inch = dev.res;
	Hor = dev.hor;
	Vert = dev.vert;
	Unitwidth = dev.unitwidth;
D 7
	nfonts = dev.nfonts;
E 7
I 7
	physfonts = nfonts = dev.nfonts;
E 7
	nsizes = dev.nsizes;
	nchtab = dev.nchtab;
I 5
D 6
#ifndef 0
E 6
D 7
	nstips = dev.spare1;
E 7
I 7
	nstips = dev.nstip;
E 7
D 6
			/* "unsigned" so very large files will work properly */
	stiplab = (tchar *) setbrk((nstips + 1) * sizeof(tchar));
#endif
E 5
D 2
	filebase = setbrk(dev.filesize + EXTRAFONT);	/* enough room for whole file */
		/* plus room for fontcache */
E 2
I 2
	filebase = setbrk(dev.filesize + 2 * EXTRAFONT);	/* enough room for whole file */
E 6
I 6
	stiplab = (tchar *) malloc((nstips + 1) * sizeof(tchar));
D 7
	filebase = malloc(dev.filesize + 2 * EXTRAFONT);
E 6
E 2
	read(fin, filebase, dev.filesize);	/* all at once */
E 7
I 7
	filebase = malloc(dev.filesize + EXTRAFONT);
	if (read(fin, filebase, dev.filesize) < dev.filesize) {
		errprint("short read on %s", termtab);
		done3(1);
	}
E 7
	pstab = (short *) filebase;
	chtab = pstab + nsizes + 1;
	chname = (char *) (chtab + dev.nchtab);
	p = chname + dev.lchname;
	for (i = 1; i <= nfonts; i++) {
D 2
		fontbase[i] = (struct font *) p;
		nw = *p & BMASK;	/* 1st thing is width count */
E 2
I 2
		fontbase[i] = (struct Font *) p;
		nw = *p & BYTEMASK;	/* 1st thing is width count */
E 2
		fontlab[i] = PAIR(fontbase[i]->namefont[0], fontbase[i]->namefont[1]);
		/* for now, still 2 char names */
		if (smnt == 0 && fontbase[i]->specfont == 1)
			smnt = i;	/* first special font */
D 2
		p += sizeof(struct font);	/* that's what's on the beginning */
E 2
I 2
		p += sizeof(struct Font);	/* that's what's on the beginning */
E 2
		fontab[i] = p;
		kerntab[i] = p + nw;
I 2
		codetab[i] = p + 2 * nw;
E 2
		fitab[i] = p + 3 * nw;	/* skip width, kern, code */
		p += 3 * nw + dev.nchtab + 128 - 32;
D 6
		/*
D 2
		 *MC:jna skip also fcode, if there
		 *See also comment in makedev.c
E 2
I 2
		 * jaap
		 *
		 * skip also fcode, if there
		 * See remarks in dev.h and makedev.c
E 2
		 */
I 5
#ifdef 0
E 5
		if(fontbase[i]->fonttab == 1)
			p += nw * sizeof(short);
I 5
#endif
E 6
E 5
	}
I 5
D 6
#ifndef 0
E 6
	for (i = 1; i <= nstips; i++) {		/* make stipple names tchars */
		stiplab[i] = PAIR(*p, *(p+1));
		while (*(p++));
	}
D 6
#endif
E 6
E 5
D 2
	fontbase[0] = (struct font *) p;	/* the last shall be first */

	/*
	fontbase[0]->nwfont = EXTRAFONT - dev.nchtab - (128-32) - sizeof (struct font) - 255*(sizeof(short) + 2*sizeof(char));
	last is for 255*(fonttab, kerntab and codetab(leaves us the
		space for maximum chars
	Yes, this is correct if you want to calculate this, but it has
	been defined as well now
	*/

E 2
I 2
	fontbase[0] = (struct Font *) p;	/* the last shall be first */
E 2
	fontbase[0]->nwfont = MAXCHARS;
D 2
	fontab[0] = p + sizeof (struct font);
E 2
I 2
	fontab[0] = p + sizeof (struct Font);
E 2
	close(fin);
	/* there are a lot of things that used to be constant
	/* that now require code to be executed.
	*/
	sps = SPS;
	ics = ICS;
	for (i = 0; i < 16; i++)
		tabtab[i] = DTAB * (i + 1);
	pl = 11 * INCH;
	po = PO;
	spacesz = SS;
	lss = lss1 = VS;
	ll = ll1 = lt = lt1 = LL;
	specnames();	/* install names like "hyphen", etc. */
	if (ascii)
		return;
D 2
	fprintf(ptid, "x T %s\n", devname);
	fprintf(ptid, "x res %d %d %d\n", Inch, Hor, Vert);
	fprintf(ptid, "x init\n");	/* do initialization for particular device */
	for (i = 1; i <= nfonts; i++)
		fprintf(ptid, "x font %d %s\n", i, fontbase[i]->namefont);
E 2
I 2
	fdprintf(ptid, "x T %s\n", devname);
	fdprintf(ptid, "x res %d %d %d\n", Inch, Hor, Vert);
	fdprintf(ptid, "x init\n");	/* do initialization for particular device */
E 2
D 6
  /*
E 6
I 6
#ifdef notdef
E 6
D 2
	fprintf(ptid, "x xxx fonts=%d sizes=%d unit=%d\n", nfonts, nsizes, Unitwidth);
	fprintf(ptid, "x xxx nchtab=%d lchname=%d nfitab=%d\n",
E 2
I 2
	for (i = 1; i <= nfonts; i++)
		fdprintf(ptid, "x font %d %s\n", i, fontbase[i]->namefont);
	fdprintf(ptid, "x xxx fonts=%d sizes=%d unit=%d\n", nfonts, nsizes, Unitwidth);
	fdprintf(ptid, "x xxx nchtab=%d lchname=%d nfitab=%d\n",
E 2
		dev.nchtab, dev.lchname, dev.nchtab+128-32);
D 2
	fprintf(ptid, "x xxx sizes:\nx xxx ");
E 2
I 2
	fdprintf(ptid, "x xxx sizes:\nx xxx ");
E 2
	for (i = 0; i < nsizes; i++)
D 2
		fprintf(ptid, " %d", pstab[i]);
	fprintf(ptid, "\nx xxx chars:\nx xxx ");
E 2
I 2
		fdprintf(ptid, " %d", pstab[i]);
	fdprintf(ptid, "\nx xxx chars:\nx xxx ");
E 2
	for (i = 0; i < dev.nchtab; i++)
D 2
		fprintf(ptid, " %s", &chname[chtab[i]]);
	fprintf(ptid, "\nx xxx\n");
E 2
I 2
		fdprintf(ptid, " %s", &chname[chtab[i]]);
	fdprintf(ptid, "\nx xxx\n");
E 2
D 6
  */
E 6
I 6
#endif
E 6
}

specnames()
{
	static struct {
		int	*n;
		char	*v;
	} spnames[] = {
		&c_hyphen, "hy",
		&c_emdash, "em",
		&c_rule, "ru",
		&c_minus, "\\-",
D 2
		&c_narsp, "\\|",
		&c_hnarsp, "\\^",
E 2
		&c_fi, "fi",
		&c_fl, "fl",
		&c_ff, "ff",
		&c_ffi, "Fi",
		&c_ffl, "Fl",
		&c_acute, "aa",
		&c_grave, "ga",
		&c_under, "ul",
		&c_rooten, "rn",
		&c_boxrule, "br",
		&c_lefthand, "lh",
I 2
		&c_dagger, "dg",
E 2
		0, 0
	};
	int	i;

	for (i = 0; spnames[i].n; i++)
		*spnames[i].n = findch(spnames[i].v);
}

findch(s)	/* find char s in chname */
register char	*s;
{
	register int	i;

	for (i = 0; i < nchtab; i++)
		if (strcmp(s, &chname[chtab[i]]) == 0)
			return(i + 128);
	return(0);
}

ptout(i)
D 2
tchar	i;
E 2
I 2
register tchar	i;
E 2
{
D 2
	register dv, ik;
E 2
I 2
	register dv;
E 2
	register tchar	*k;
D 2
	int	temp, a, b;
E 2
I 2
	int temp, a, b;
E 2

	if (cbits(i) != '\n') {
		*olinep++ = i;
		return;
	}
	if (olinep == oline) {
		lead += lss;
		return;
	}

	hpos = po;	/* ??? */
	esc = 0;	/* ??? */
	ptesc();	/* the problem is to get back to the left end of the line */
	dv = 0;
	for (k = oline; k < olinep; k++) {
		if (ismot(*k) && isvmot(*k)) {
			temp = absmot(*k);
			if (isnmot(*k))
				temp = -temp;
			dv += temp;
		}
	}
	if (dv) {
		vflag++;
		*olinep++ = makem(-dv);
		vflag = 0;
	}

	b = dip->blss + lss;
	lead += dip->blss + lss;
	dip->blss = 0;
	for (k = oline; k < olinep; )
		k += ptout0(k);	/* now passing a pointer! */
	olinep = oline;
	lead += dip->alss;
	a = dip->alss;
	dip->alss = 0;
	/*
D 2
	fprintf(ptid, "x xxx end of line: hpos=%d, vpos=%d\n", hpos, vpos);
E 2
I 2
	fdprintf(ptid, "x xxx end of line: hpos=%d, vpos=%d\n", hpos, vpos);
E 2
*/
D 2
	fprintf(ptid, "n%d %d\n", b, a);	/* be nice to chuck */
E 2
I 2
	fdprintf(ptid, "n%d %d\n", b, a);	/* be nice to chuck */
E 2
}

ptout0(pi)
tchar	*pi;
{
	register short j, k, w;
	short	z, dx, dy, dx2, dy2, n;
D 2
	tchar	i;
E 2
I 2
	register tchar	i;
E 2
	int outsize;	/* size of object being printed */

	outsize = 1;	/* default */
	i = *pi;
	k = cbits(i);
	if (ismot(i)) {
		j = absmot(i);
		if (isnmot(i))
			j = -j;
		if (isvmot(i))
			lead += j;
		else 
			esc += j;
		return(outsize);
	}
I 2
	if (k == XON) {
		int c;
		if (xfont != mfont)
			ptfont();
		if (xpts != mpts)
			ptps();
		if (lead)
			ptlead();
I 3
		if (esc)	/* for psfig ???*/
			ptesc();
E 3
		fdprintf(ptid, "x X ");
		for (j = 1; (c=cbits(pi[j])) != XOFF; j++)
			outascii(pi[j]);
		oput('\n');
		return j+1;
	}
			;
E 2
	if (k == CHARHT) {
		if (xpts != mpts)
			ptps();
D 2
		fprintf(ptid, "x H %d\n", sbits(i));
E 2
I 2
		fdprintf(ptid, "x H %d\n", sbits(i));
E 2
		return(outsize);
	}
	if (k == SLANT) {
D 2
		fprintf(ptid, "x S %d\n", sfbits(i)-180);
E 2
I 2
		fdprintf(ptid, "x S %d\n", sfbits(i)-180);
E 2
		return(outsize);
	}
	if (k == WORDSP) {
		oput('w');
		return(outsize);
	}
D 2
	if (k == FONTPOS) {
		char temp[3];
		n = i >> 16;
		temp[0] = n & BMASK;
		temp[1] = n >> BYTE;
		temp[2] = 0;
		fprintf(stderr, "troff: Oops, still finding PONTPOS, save the files and warn jaap\n");
		ptfpcmd(0, temp);
		return(outsize);
	}
	xbitf = 2;
E 2
	if (sfbits(i) == oldbits) {
		xfont = pfont;
		xpts = ppts;
D 2
		xbitf = 0;
E 2
	} else 
D 2
		xbits(i);
E 2
I 2
		xbits(i, 2);
E 2
	if (k < 040 && k != DRAWFCN)
		return(outsize);
D 2
	w = getcw(k - 32);
E 2
I 2
D 4
	if (widcache[k-32].fontpts == (xfont<<8) + xpts  && !setwdf) {
		w = widcache[k-32].width;
		bd = 0;
		cs = 0;
	} else
		w = getcw(k-32);
E 4
I 4
	/*
	 * Bug fix, if k == DRAWFCN, thewidcache gets a negative index.
	 * This worked by magic on the vax and tahoe, but caused somtimes
	 * a segment violaton on the suns.
	 *
	 * The code was plainly wrong (jna).
	 */
	if ( k != DRAWFCN) {
		if (widcache[k-32].fontpts == (xfont<<8) + xpts  && !setwdf) {
			w = widcache[k-32].width;
			bd = 0;
			cs = 0;
		} else
			w = getcw(k-32);
	}
E 4
E 2
	j = z = 0;
	if (k != DRAWFCN) {
		if (cs) {
			if (bd)
				w += (bd - 1) * HOR;
			j = (cs - w) / 2;
			w = cs - j;
			if (bd)
				w -= (bd - 1) * HOR;
		}
		if (iszbit(i)) {
			if (cs)
				w = -j; 
			else 
				w = 0;
			z = 1;
		}
	}
	esc += j;
	if (xfont != mfont)
		ptfont();
	if (xpts != mpts)
		ptps();
	if (lead)
		ptlead();
	/* put out the real character here */
	if (k == DRAWFCN) {
		if (esc)
			ptesc();
D 8
		dx = absmot(pi[3]);
		if (isnmot(pi[3]))
E 8
I 8
		dx = absmot(pi[2]);
		if (isnmot(pi[2]))
E 8
			dx = -dx;
D 8
		dy = absmot(pi[4]);
		if (isnmot(pi[4]))
E 8
I 8
		dy = absmot(pi[3]);
		if (isnmot(pi[3]))
E 8
			dy = -dy;
I 8
		w = 0;
E 8
		switch (cbits(pi[1])) {
		case DRAWCIRCLE:	/* circle */
D 2
			fprintf(ptid, "D%c %d\n", DRAWCIRCLE, dx);	/* dx is diameter */
E 2
I 2
D 8
			fdprintf(ptid, "D%c %d\n", DRAWCIRCLE, dx);	/* dx is diameter */
E 2
			w = 0;
E 8
			hpos += dx;
I 8
				/* FALLTHROUGH */
		case DRAWTHICK:
		case DRAWSTYLE:
			fdprintf(ptid, "D%c %d\n", cbits(pi[1]), dx);	/* dx is diameter */
E 8
			break;
		case DRAWELLIPSE:
D 2
			fprintf(ptid, "D%c %d %d\n", DRAWELLIPSE, dx, dy);
E 2
I 2
			fdprintf(ptid, "D%c %d %d\n", DRAWELLIPSE, dx, dy);
E 2
D 8
			w = 0;
E 8
			hpos += dx;
			break;
		case DRAWLINE:	/* line */
D 8
			k = cbits(pi[2]);
D 2
			fprintf(ptid, "D%c %d %d ", DRAWLINE, dx, dy);
E 2
I 2
			fdprintf(ptid, "D%c %d %d ", DRAWLINE, dx, dy);
E 2
			if (k < 128)
D 2
				fprintf(ptid, "%c\n", k);
E 2
I 2
				fdprintf(ptid, "%c\n", k);
E 2
			else
D 2
				fprintf(ptid, "%s\n", &chname[chtab[k - 128]]);
E 2
I 2
				fdprintf(ptid, "%s\n", &chname[chtab[k - 128]]);
E 2
			w = 0;
E 8
I 8
			fdprintf(ptid, "D%c %d %d\n", DRAWLINE, dx, dy);
E 8
			hpos += dx;
			vpos += dy;
			break;
		case DRAWARC:	/* arc */
D 8
			dx2 = absmot(pi[5]);
			if (isnmot(pi[5]))
E 8
I 8
			dx2 = absmot(pi[4]);
			if (isnmot(pi[4]))
E 8
				dx2 = -dx2;
D 8
			dy2 = absmot(pi[6]);
			if (isnmot(pi[6]))
E 8
I 8
			dy2 = absmot(pi[5]);
			if (isnmot(pi[5]))
E 8
				dy2 = -dy2;
D 2
			fprintf(ptid, "D%c %d %d %d %d\n", DRAWARC,
E 2
I 2
			fdprintf(ptid, "D%c %d %d %d %d\n", DRAWARC,
E 2
				dx, dy, dx2, dy2);
D 8
			w = 0;
E 8
			hpos += dx + dx2;
			vpos += dy + dy2;
			break;
D 2
		case DRAWWIG:	/* wiggly line */
			fprintf(ptid, "D%c %d %d", DRAWWIG, dx, dy);
E 2
I 2
		case DRAWSPLINE:	/* spline */
I 8
		/* case DRAWWIG:	/* wiggly line */
		case DRAWCURVE:	/* gremlin-style curve */
E 8
		default:	/* something else; copy it like spline */
			fdprintf(ptid, "D%c %d %d", cbits(pi[1]), dx, dy);
E 2
D 8
			w = 0;
E 8
			hpos += dx;
			vpos += dy;
D 2
			for (n = 5; cbits(pi[n]) != '.'; n += 2) {
E 2
I 2
D 8
			if (cbits(pi[3]) == DRAWFCN || cbits(pi[4]) == DRAWFCN) {
				/* it was somehow defective */
				fdprintf(ptid, "\n");
				break;
			}
			for (n = 5; cbits(pi[n]) != DRAWFCN; n += 2) {
E 8
I 8
writecoords:
			for (n = 4; cbits(pi[n]) != '.'; n += 2) {
E 8
E 2
				dx = absmot(pi[n]);
				if (isnmot(pi[n]))
					dx = -dx;
				dy = absmot(pi[n+1]);
				if (isnmot(pi[n+1]))
					dy = -dy;
D 2
				fprintf(ptid, " %d %d", dx, dy);
E 2
I 2
				fdprintf(ptid, " %d %d", dx, dy);
E 2
				hpos += dx;
				vpos += dy;
			}
D 2
			fprintf(ptid, "\n");
E 2
I 2
			fdprintf(ptid, "\n");
E 2
			break;
I 8

		case DRAWPOLY:	/* polygon with stipple */
		case DRAWUBPOLY:/* polygon, stipple, no border */
			if (xstip != stip) ptstip();
			fdprintf(ptid, "D%c %d", cbits(pi[1]), dx);
			goto writecoords;
E 8
		}
D 2
		for (n = 3; cbits(pi[n]) != '.'; n++)
E 2
I 2
D 8
		for (n = 3; cbits(pi[n]) != DRAWFCN; n++)
E 8
I 8
		for (n = 2; cbits(pi[n]) != '.'; n++)
E 8
E 2
			;
		outsize = n + 1;
	} else if (k < 128) {
		/* try to go faster and compress output */
		/* by printing nnc for small positive motion followed by c */
		/* kludgery; have to make sure set all the vars too */
		if (esc > 0 && esc < 100) {
			oput(esc / 10 + '0');
			oput(esc % 10 + '0');
			oput(k);
			hpos += esc;
			esc = 0;
		} else {
			if (esc)
				ptesc();
D 2
			fprintf(ptid, "c%c\n", k);
E 2
I 2
			oput('c');
			oput(k);
			oput('\n');
E 2
		}
	} else {
		if (esc)
			ptesc();
D 2
		fprintf(ptid, "C%s\n", &chname[chtab[k - 128]]);
E 2
I 2
		if (k >= nchtab + 128)
			fdprintf(ptid, "N%d\n", k - (nchtab+128));
		else
			fdprintf(ptid, "C%s\n", &chname[chtab[k - 128]]);
E 2
	}
	if (bd) {
		bd -= HOR;
		if (esc += bd)
			ptesc();
		if (k < 128) {
D 2
			fprintf(ptid, "c%c\n", k);
E 2
I 2
			fdprintf(ptid, "c%c\n", k);
		} else if (k >= nchtab + 128) {
			fdprintf(ptid, "N%d\n", k - (nchtab+128));
E 2
		} else
D 2
			fprintf(ptid, "C%s\n", &chname[chtab[k - 128]]);
E 2
I 2
			fdprintf(ptid, "C%s\n", &chname[chtab[k - 128]]);
E 2
		if (z)
			esc -= bd;
	}
	esc += w;
	return(outsize);
}

ptps()
{
	register i, j, k;

	i = xpts;
	for (j = 0; i > (k = pstab[j]); j++)
		if (!k) {
			k = pstab[--j];
			break;
		}
D 2
	fprintf(ptid, "s%d\n", k);	/* really should put out string rep of size */
E 2
I 2
	fdprintf(ptid, "s%d\n", k);	/* really should put out string rep of size */
E 2
	mpts = i;
}
I 8

ptstip()
{
	xstip = stip;
	fdprintf(ptid, "i%d\n", xstip);
}

E 8

ptfont()
{
I 2
	extern char *unpair();
E 2
	mfont = xfont;
D 7
	if( xfont > nfonts) {
D 2
		char temp[3];	/* TODO: make a routine to convert */
		temp[0] = fontlab[xfont] & BMASK;	/* a name */
		temp[1] = fontlab[xfont] >> BYTE;	/* like */
		temp[2] = 0;				/* this */

E 2
I 2
		register char *temp = unpair(fontlab[xfont]);
E 2
		ptfpcmd(0, temp);	/* Put the desired font in the
					 * fontcache of the filter */
E 7
I 7
	if( xfont > physfonts) {
		if (xfont != zfont) {
			register char *temp = unpair(fontlab[xfont]);
			ptfpcmd(0, temp);	/* Put the desired font in the
						 * fontcache of the filter */
		}
E 7
D 2
		fprintf(ptid, "f0\n");	/* make sure that it gets noticed */
E 2
I 2
		fdprintf(ptid, "f0\n");	/* make sure that it gets noticed */
I 7
		zfont = xfont;
E 7
E 2
	} else
D 2
		fprintf(ptid, "f%d\n", xfont);
E 2
I 2
		fdprintf(ptid, "f%d\n", xfont);
E 2
}

ptfpcmd(f, s)
int	f;
char	*s;
{
	if (ascii)
		return;
D 2
	fprintf(ptid, "x font %d %s\n", f, s);
E 2
I 2
	fdprintf(ptid, "x font %d %s\n", f, s);
E 2
}

ptlead()
{
	vpos += lead;
	if (!ascii)
D 2
		fprintf(ptid, "V%d\n", vpos);
E 2
I 2
		fdprintf(ptid, "V%d\n", vpos);
E 2
	lead = 0;
}

ptesc()
{
	hpos += esc;
D 2
	if (esc > 0)
		fprintf(ptid, "h%d", esc);
	else
		fprintf(ptid, "H%d\n", hpos);
E 2
I 2
	if (esc > 0) {
		oput('h');
		if (esc>=10 && esc<100) {
			oput(esc/10 + '0');
			oput(esc%10 + '0');
		} else
			fdprintf(ptid, "%d", esc);
	} else
		fdprintf(ptid, "H%d\n", hpos);
E 2
	esc = 0;
}

newpage(n)	/* called at end of each output page (we hope) */
{
I 2
	int i;

E 2
	ptlead();
	vpos = 0;
	if (ascii)
		return;
D 2
	flusho();
	fprintf(ptid, "p%d\n", n);	/* new page */
E 2
I 2
	fdprintf(ptid, "p%d\n", n);	/* new page */
D 7
	for (i = 0; i <= nfonts; i++)
E 7
I 7
	if (fontbase[zfont]->namefont && fontbase[zfont]->namefont[0])
		fdprintf(ptid, "x font 0 %s\n", fontbase[zfont]->namefont);
	for (i = 1; i <= physfonts; i++)
E 7
		if (fontbase[i]->namefont && fontbase[i]->namefont[0])
			fdprintf(ptid, "x font %d %s\n", i, fontbase[i]->namefont);
E 2
	ptps();
	ptfont();
}

pttrailer()
{
D 2
	fprintf(ptid, "x trailer\n");
E 2
I 2
	fdprintf(ptid, "x trailer\n");
E 2
}

ptstop()
{
D 2
	fprintf(ptid, "x stop\n");
E 2
I 2
	fdprintf(ptid, "x stop\n");
E 2
}

dostop()
{
	if (ascii)
		return;
	ptlead();
	vpos = 0;
D 2
	/*	fprintf(ptid, "x xxx end of page\n");*/
E 2
I 2
	/* fdprintf(ptid, "x xxx end of page\n");*/
E 2
	if (!nofeed)
		pttrailer();
	ptlead();
D 2
	fprintf(ptid, "x pause\n");
E 2
I 2
	fdprintf(ptid, "x pause\n");
E 2
	flusho();
	mpts = mfont = 0;
D 2
	paper = 0;
	esc = T_IESC;	/* this is a dreg */
E 2
	ptesc();
	esc = po;
	hpos = vpos = 0;	/* probably in wrong place */
}
E 1
