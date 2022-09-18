h42834
s 00015/00009/00260
d D 2.4 93/07/27 09:15:42 bostic 5 4
c checkpoint; Mike Karels left this checked out.
e
s 00004/00004/00265
d D 2.3 89/08/14 14:09:08 jaap 4 3
c checking stuff in, so charlie will stop sending me mail
e
s 00002/00001/00267
d D 2.2 86/08/15 00:53:21 jaap 3 2
c Added nroff support (by denise)
e
s 00204/00241/00064
d D 2.1 85/07/18 14:28:10 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00305/00000/00000
d D 1.1 85/07/17 17:54:47 jaap 1 0
c date and time created 85/07/17 17:54:47 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (CWI) %E%";
E 5
I 5
/*
static char sccsid[] = "@(#)ni.c	2.3 (CWI) 89/08/14";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
#endif lint
D 2

E 2
#include "tdef.h"
I 5
#include "pathnames.h"
E 5

/* You may want to change these names */

D 2
#ifndef NROFF
char	termtab[NS] = "/usr/lib/ditroff/font";	/* rest added in ptinit() */
char	fontfile[NS] = "/usr/lib/ditroff/font";	/* rest added in casefp() */
char	devname[10]	 = "har";	/* default typesetter */
E 2
I 2
#ifdef NROFF

D 3
char	termtab[NS] = "/usr/lib/term/tab.";	/* term type added in ptinit() */
E 3
I 3
D 5
char	termtab[NS] = "/usr/local/lib/ditroff/term/tab.";
E 5
I 5
char	termtab[NS] = _PATH_TERMTAB;
E 5
					/* term type added in ptinit() */
E 3
char	fontfile[NS] = "";	/* not used */
char	devname[20] = "37";

#else

D 4
char	termtab[NS] = "/usr/local/lib/ditroff/font";	/* rest added in ptinit() */
char	fontfile[NS] = "/usr/local/lib/ditroff/font";	/* rest added in casefp() */
char	devname[20]	 = "har";	/* default typesetter */
E 4
I 4
D 5
char	termtab[NS] = "/usr/local/lib/font";	/* rest added in ptinit() */
char	fontfile[NS] = "/usr/local/lib/font";	/* rest added in casefp() */
E 5
I 5
char	termtab[NS] = _PATH_FONTS;	/* rest added in ptinit() */
char	fontfile[NS] = _PATH_FONTS;	/* rest added in casefp() */
E 5
char	devname[20]	 = "psc";	/* default typesetter */
E 4

E 2
#endif
D 2
char	obuf[OBUFSZ];	/* characters collected here for actual typesetter output */
E 2
I 2
D 5
char	obuf[OBUFSZ];	/* characters collected here for typesetter output */
E 2
char	*obufp = obuf;
E 5
D 2
int	r[NN] = {	/* read-only number registers at beginning */
	PAIR('%', 0),
	PAIR('n', 'l'),
	PAIR('y', 'r'),
	PAIR('h', 'p'),
	PAIR('c', 't'),
	PAIR('d', 'n'),
	PAIR('m', 'o'),
	PAIR('d', 'y'),
	PAIR('d', 'w'),
	PAIR('l', 'n'),
	PAIR('d', 'l'),
	PAIR('s', 't'),
	PAIR('s', 'b'),
	PAIR('c', '.'),
	PAIR('$', '$'),
E 2
I 2
struct numtab numtab[NN] = {
	{ PAIR('%', 0) },
	{ PAIR('n', 'l') },
	{ PAIR('y', 'r') },
	{ PAIR('h', 'p') },
	{ PAIR('c', 't') },
	{ PAIR('d', 'n') },
	{ PAIR('m', 'o') },
	{ PAIR('d', 'y') },
	{ PAIR('d', 'w') },
	{ PAIR('l', 'n') },
	{ PAIR('d', 'l') },
	{ PAIR('s', 't') },
	{ PAIR('s', 'b') },
	{ PAIR('c', '.') },
	{ PAIR('$', '$') },
E 2
};


int	pto = 10000;
int	pfrom = 1;
int	print = 1;
D 2
char	nextf[NS] = "/usr/lib/ditroff/tmac/tmac.xxxxx";
int	nfi = 27;	/* This is terrible!*/
#ifdef NROFF
char	termtab[NS] = "/usr/lib/term/tab37";
#endif
E 2
I 2
D 4
char	nextf[NS] = "/usr/local/lib/ditroff/tmac/tmac.";
E 4
I 4
D 5
char	nextf[NS] = "/usr/lib/tmac/tmac.";
E 5
I 5
char	nextf[NS] = _PATH_TMAC;
E 5
E 4
E 2
#ifndef NROFF
int	oldbits = -1;
#endif
int	init = 1;
int	fc = IMP;	/* field character */
int	eschar = '\\';
#ifdef	NROFF
int	pl = 11*INCH;
int	po = PO;
#else
int	pl;
int	po;
#endif
int	dfact = 1;
int	dfactd = 1;
int	res = 1;
int	smnt = 0;	/* beginning of special fonts */
int	ascii = ASCII;
D 5
int	ptid = PTID;
E 5
I 5
FILE	*ptid = stdout;
E 5
int	lg = LG;
D 2
int	pnlist[NPN] = {
	-1};
E 2
I 2
int	pnlist[NPN] = { -1 };
E 2


int	*pnp = pnlist;
int	npn = 1;
int	npnflg = 1;
D 2
int	xflg = 1;
E 2
int	dpn = -1;
int	totout = 1;
D 2
int	ulfont = FT + 1;
int	ulbit = 1 << 9;
E 2
I 2
int	ulfont = ULFONT;
E 2
int	tabch = TAB;
int	ldrch = LEADER;
D 2
int	xxx;
extern caseds(), caseas(), casesp(), caseft(), caseps(), casevs(),
E 2
I 2

extern    caseds(), caseas(), casesp(), caseft(), caseps(), casevs(),
E 2
casenr(), caseif(), casepo(), casetl(), casetm(), casebp(), casech(),
casepn(), tbreak(), caseti(), casene(), casenf(), casece(), casefi(),
casein(), casell(), casens(), casemk(), casert(), caseam(),
casede(), casedi(), caseda(), casewh(), casedt(), caseit(), caserm(),
casern(), casead(), casers(), casena(), casepl(), caseta(), casetr(),
caseul(), caselt(), casenx(), caseso(), caseig(), casetc(), casefc(),
caseec(), caseeo(), caselc(), caseev(), caserd(), caseab(), casefl(),
D 2
done(), casess(), casefp(), casecs(), casebd(), caselg(), casehc(),
E 2
I 2
done(),   casess(), casefp(), casecs(), casebd(), caselg(), casehc(),
E 2
casehy(), casenh(), casenm(), casenn(), casesv(), caseos(), casels(),
casecc(), casec2(), caseem(), caseaf(), casehw(), casemc(), casepm(),
casecu(), casepi(), caserr(), caseuf(), caseie(), caseel(), casepc(),
D 2
caseht(), casecf(), casesy(), caseha();
E 2
I 2
caseht(), casecf(), casesy(), caself(), caseha();
E 2

D 2
struct contab {
	int	rq;
	/*
	union {
 */
	int	(*f)();
	/*
		unsigned mx;
	}x;
 */
} contab[NM] = {
	PAIR('d', 's'), caseds,
	PAIR('a', 's'), caseas,
	PAIR('s', 'p'), casesp,
	PAIR('f', 't'), caseft,
	PAIR('p', 's'), caseps,
	PAIR('v', 's'), casevs,
	PAIR('n', 'r'), casenr,
	PAIR('i', 'f'), caseif,
	PAIR('i', 'e'), caseie,
	PAIR('e', 'l'), caseel,
	PAIR('p', 'o'), casepo,
	PAIR('t', 'l'), casetl,
	PAIR('t', 'm'), casetm,
	PAIR('b', 'p'), casebp,
	PAIR('c', 'h'), casech,
	PAIR('p', 'n'), casepn,
	PAIR('b', 'r'), tbreak,
	PAIR('t', 'i'), caseti,
	PAIR('n', 'e'), casene,
	PAIR('n', 'f'), casenf,
	PAIR('c', 'e'), casece,
	PAIR('f', 'i'), casefi,
	PAIR('i', 'n'), casein,
	PAIR('l', 'l'), casell,
	PAIR('n', 's'), casens,
	PAIR('m', 'k'), casemk,
	PAIR('r', 't'), casert,
	PAIR('a', 'm'), caseam,
	PAIR('d', 'e'), casede,
	PAIR('d', 'i'), casedi,
	PAIR('d', 'a'), caseda,
	PAIR('w', 'h'), casewh,
	PAIR('d', 't'), casedt,
	PAIR('i', 't'), caseit,
	PAIR('r', 'm'), caserm,
	PAIR('r', 'r'), caserr,
	PAIR('r', 'n'), casern,
	PAIR('a', 'd'), casead,
	PAIR('r', 's'), casers,
	PAIR('n', 'a'), casena,
	PAIR('p', 'l'), casepl,
	PAIR('t', 'a'), caseta,
	PAIR('t', 'r'), casetr,
	PAIR('u', 'l'), caseul,
	PAIR('c', 'u'), casecu,
	PAIR('l', 't'), caselt,
	PAIR('n', 'x'), casenx,
	PAIR('s', 'o'), caseso,
	PAIR('i', 'g'), caseig,
	PAIR('t', 'c'), casetc,
	PAIR('f', 'c'), casefc,
	PAIR('e', 'c'), caseec,
	PAIR('e', 'o'), caseeo,
	PAIR('l', 'c'), caselc,
	PAIR('e', 'v'), caseev,
	PAIR('r', 'd'), caserd,
	PAIR('a', 'b'), caseab,
	PAIR('f', 'l'), casefl,
	PAIR('e', 'x'), done,
	PAIR('s', 's'), casess,
	PAIR('f', 'p'), casefp,
	PAIR('c', 's'), casecs,
	PAIR('b', 'd'), casebd,
	PAIR('l', 'g'), caselg,
	PAIR('h', 'c'), casehc,
	PAIR('h', 'y'), casehy,
	PAIR('n', 'h'), casenh,
	PAIR('n', 'm'), casenm,
	PAIR('n', 'n'), casenn,
	PAIR('s', 'v'), casesv,
	PAIR('o', 's'), caseos,
	PAIR('l', 's'), casels,
	PAIR('c', 'c'), casecc,
	PAIR('c', '2'), casec2,
	PAIR('e', 'm'), caseem,
	PAIR('a', 'f'), caseaf,
	PAIR('h', 'w'), casehw,
	PAIR('m', 'c'), casemc,
	PAIR('p', 'm'), casepm,
	PAIR('p', 'i'), casepi,
	PAIR('u', 'f'), caseuf,
	PAIR('p', 'c'), casepc,
	PAIR('h', 't'), caseht,
	PAIR('c', 'f'), casecf,
	PAIR('s', 'y'), casesy,
	PAIR('!', 0), casesy,	/* synonym for .sy */
	PAIR('h', 'a'), caseha,	/* new request, jna */
E 2
I 2
#define	C(a,b)	{a, 0, b, 0}
struct contab contab[NM] = {
	C(PAIR('d', 's'), caseds),
	C(PAIR('a', 's'), caseas),
	C(PAIR('s', 'p'), casesp),
	C(PAIR('f', 't'), caseft),
	C(PAIR('p', 's'), caseps),
	C(PAIR('v', 's'), casevs),
	C(PAIR('n', 'r'), casenr),
	C(PAIR('i', 'f'), caseif),
	C(PAIR('i', 'e'), caseie),
	C(PAIR('e', 'l'), caseel),
	C(PAIR('p', 'o'), casepo),
	C(PAIR('t', 'l'), casetl),
	C(PAIR('t', 'm'), casetm),
	C(PAIR('b', 'p'), casebp),
	C(PAIR('c', 'h'), casech),
	C(PAIR('p', 'n'), casepn),
	C(PAIR('b', 'r'), tbreak),
	C(PAIR('t', 'i'), caseti),
	C(PAIR('n', 'e'), casene),
	C(PAIR('n', 'f'), casenf),
	C(PAIR('c', 'e'), casece),
	C(PAIR('f', 'i'), casefi),
	C(PAIR('i', 'n'), casein),
	C(PAIR('l', 'l'), casell),
	C(PAIR('n', 's'), casens),
	C(PAIR('m', 'k'), casemk),
	C(PAIR('r', 't'), casert),
	C(PAIR('a', 'm'), caseam),
	C(PAIR('d', 'e'), casede),
	C(PAIR('d', 'i'), casedi),
	C(PAIR('d', 'a'), caseda),
	C(PAIR('w', 'h'), casewh),
	C(PAIR('d', 't'), casedt),
	C(PAIR('i', 't'), caseit),
	C(PAIR('r', 'm'), caserm),
	C(PAIR('r', 'r'), caserr),
	C(PAIR('r', 'n'), casern),
	C(PAIR('a', 'd'), casead),
	C(PAIR('r', 's'), casers),
	C(PAIR('n', 'a'), casena),
	C(PAIR('p', 'l'), casepl),
	C(PAIR('t', 'a'), caseta),
	C(PAIR('t', 'r'), casetr),
	C(PAIR('u', 'l'), caseul),
	C(PAIR('c', 'u'), casecu),
	C(PAIR('l', 't'), caselt),
	C(PAIR('n', 'x'), casenx),
	C(PAIR('s', 'o'), caseso),
	C(PAIR('i', 'g'), caseig),
	C(PAIR('t', 'c'), casetc),
	C(PAIR('f', 'c'), casefc),
	C(PAIR('e', 'c'), caseec),
	C(PAIR('e', 'o'), caseeo),
	C(PAIR('l', 'c'), caselc),
	C(PAIR('e', 'v'), caseev),
	C(PAIR('r', 'd'), caserd),
	C(PAIR('a', 'b'), caseab),
	C(PAIR('f', 'l'), casefl),
	C(PAIR('e', 'x'), done),
	C(PAIR('s', 's'), casess),
	C(PAIR('f', 'p'), casefp),
	C(PAIR('c', 's'), casecs),
	C(PAIR('b', 'd'), casebd),
	C(PAIR('l', 'g'), caselg),
	C(PAIR('h', 'c'), casehc),
	C(PAIR('h', 'y'), casehy),
	C(PAIR('n', 'h'), casenh),
	C(PAIR('n', 'm'), casenm),
	C(PAIR('n', 'n'), casenn),
	C(PAIR('s', 'v'), casesv),
	C(PAIR('o', 's'), caseos),
	C(PAIR('l', 's'), casels),
	C(PAIR('c', 'c'), casecc),
	C(PAIR('c', '2'), casec2),
	C(PAIR('e', 'm'), caseem),
	C(PAIR('a', 'f'), caseaf),
	C(PAIR('h', 'w'), casehw),
	C(PAIR('m', 'c'), casemc),
	C(PAIR('p', 'm'), casepm),
	C(PAIR('p', 'i'), casepi),
	C(PAIR('u', 'f'), caseuf),
	C(PAIR('p', 'c'), casepc),
	C(PAIR('h', 't'), caseht),
	C(PAIR('c', 'f'), casecf),
	C(PAIR('s', 'y'), casesy),
	C(PAIR('l', 'f'), caself),
	C(PAIR('!',  0 ), casesy),	/* synonym for .sy */
	C(PAIR('h', 'a'), caseha),	/* select hyphenation, (jaap) */
E 2
};


tchar oline[LNSIZE+1];

/*
D 2
troff environment block
*/
E 2
I 2
 * troff environment block
 *
 * If you change this, don't forget to update tdef.h (jaap)
 */
E 2

D 2
int	block	 = 0;
#ifdef	NROFF
/* these are initialized statically in nroff (so far)
	/* and dynamically in ptinit() in troff beacuse INCH
	/* is a variable
	*/
int	ics	 = ICS;	/* space for insertion character */
int	sps	 = SPS;
int	spacesz	 = SS;
int	lss	 = VS;
int	lss1	 = VS;
int	ll	 = LL;
int	ll1	 = LL;
int	lt	 = LL;
int	lt1	 = LL;
E 2
I 2
D 5
struct	env env = {
E 5
I 5
struct	env env_array[NEV] = {
{
E 5
/* int	ics	 */	0,
/* int	sps	 */	0,
/* int	spacesz	 */	0,
/* int	lss	 */	0,
/* int	lss1	 */	0,
/* int	ll	 */	0,
/* int	ll1	 */	0,
/* int	lt	 */	0,
/* int	lt1	 */	0,
/* tchar	i*/	0,	/* insertion character (/* = margin character) */
/* int	icf	 */	0,
/* tchar	chbits	 */	0,	/* size+font bits for current character */
/* tchar	spbits	 */	0,
/* tchar	nmbits	 */	0,
/* int	apts	 */	PS,	/* actual point size -- as requested by user */
/* int	apts1	 */	PS,	/* need not match an existent size */
/* int	pts	 */	PS,	/* hence, this is the size that really exists */
/* int	pts1	 */	PS,
/* int	font	 */	FT,
/* int	font1	 */	FT,
/* int	ls	 */	1,
/* int	ls1	 */	1,
/* int	ad	 */	1,
/* int	nms	 */	1,
/* int	ndf	 */	1,
/* int	fi	 */	1,
/* int	cc	 */	'.',
/* int	c2	 */	'\'',
/* int	ohc	 */	OHC,
/* int	tdelim	 */	IMP,
#ifdef NROFF
/* int	hyf	 */	0,
E 2
#else
D 2
int	ics	 = 0;
int	sps	 = 0;
int	spacesz	 = 0;
int	lss	 = 0;
int	lss1	 = 0;
int	ll	 = 0;
int	ll1	 = 0;
int	lt	 = 0;
int	lt1	 = 0;
E 2
I 2
/* int	hyf	 */	1,
E 2
#endif
D 2
tchar	ic	 = 0;	/* insertion character (= margin character) */
int	icf	 = 0;
tchar	chbits	 = 0;	/* size+font bits for current character */
tchar	spbits	 = 0;	/* ditto for special font */
tchar	nmbits	 = 0;
int	apts	 = PS;	/* actual point size -- as requested by user */
int	apts1	 = PS;	/* need not match an existent size */
int	pts	 = PS;	/* hence, this is the size that really exists */
int	pts1	 = PS;
int	font	 = FT;
int	font1	 = FT;
int	ls	 = 1;
int	ls1	 = 1;
int	ad	 = 1;
int	nms	 = 1;
int	ndf	 = 1;
int	fi	 = 1;
int	cc	 = '.';
int	c2	 = '\'';
int	ohc	 = OHC;
int	tdelim	 = IMP;
int	hyf	 = 1;
int	hyoff	 = 0;
int	hyalg	 = ORIGINAL;	/* Default hyphenation algorithm */
int	hyalg1	 = ORIGINAL;
int	thresh	 = THRESH;	/* threshold is part of environment now jna */
int	un1	 = -1;
int	tabc	 = 0;
int	dotc	 = '.';
int	adsp	 = 0;
int	adrem	 = 0;
int	lastl	 = 0;
int	nel	 = 0;
int	admod	 = 0;
tchar	*wordp	 = 0;
int	spflg	 = 0;	/* probably to indicate space after punctuation needed */
tchar	*linep	 = 0;
tchar	*wdend	 = 0;
tchar	*wdstart	 = 0;
int	wne	 = 0;
int	ne	 = 0;
int	nc	 = 0;
int	nb	 = 0;
int	lnmod	 = 0;
int	nwd	 = 0;
int	nn	 = 0;
int	ni	 = 0;
int	ul	 = 0;
int	cu	 = 0;
int	ce	 = 0;
int	in	 = 0;
int	in1	 = 0;
int	un	 = 0;
int	wch	 = 0;
int	pendt	 = 0;
tchar	*pendw	 = 0;
int	pendnf	 = 0;
int	spread	 = 0;
int	it	 = 0;
int	itmac	 = 0;
int	lnsize	 = LNSIZE;
tchar	*hyptr[NHYP]	 = {
	0};


int	tabtab[NTAB]	 = {
	0};


tchar	line[LNSIZE]	 = {
	0};


tchar	word[WDSIZE]	 = {
	0};


char	blockxxx[EVSPARE]	 = {
	0};


E 2
I 2
/* int	hyoff	 */	0,
/* int	hyalg	 */	ORIGINAL,	/* Default hyphenation style (jaap)*/
/* int	hyalg1	 */	ORIGINAL,
/* int	thresh	 */	THRESH,		/* now part of environment (jaap) */
/* int	un1	 */	-1,
/* int	tabc	 */	0,
/* int	dotc	 */	'.',
/* int	adsp	 */	0,
/* int	adrem	 */	0,
/* int	lastl	 */	0,
/* int	nel	 */	0,
/* int	admod	 */	0,
/* tchar	*wordp	 */	0,
/* int	spflg	 */	0,	/* probably to indicate space after punctuation needed */
/* tchar	*linep	 */	0,
/* tchar	*wdend	 */	0,
/* tchar	*wdstart	 */	0,
/* int	wne	 */	0,
/* int	ne	 */	0,
/* int	nc	 */	0,
/* int	nb	 */	0,
/* int	lnmod	 */	0,
/* int	nwd	 */	0,
/* int	nn	 */	0,
/* int	ni	 */	0,
/* int	ul	 */	0,
/* int	cu	 */	0,
/* int	ce	 */	0,
/* int	in	 */	0,
/* int	in1	 */	0,
/* int	un	 */	0,
/* int	wch	 */	0,
/* int	pendt	 */	0,
/* tchar	*pendw	 */	(tchar *)0,
/* int	pendnf	 */	0,
/* int	spread	 */	0,
/* int	it	 */	0,
/* int	itmac	 */	0,
/* int	lnsize	 */	LNSIZE,
I 5
},
E 5
};
I 5

struct env *env = &env_array[0];
E 5
E 2
E 1
