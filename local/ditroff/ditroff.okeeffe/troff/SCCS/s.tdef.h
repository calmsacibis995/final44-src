h10595
s 00014/00000/00532
d D 2.5 93/02/25 17:19:24 sklower 6 5
c Long since forgotten attempts to integrate gremlin support into
c a slightly later version of ditroff
e
s 00006/00001/00526
d D 2.4 90/11/03 20:41:51 karels 5 4
c changes to allow use of fonts > nfonts (caching font data for fonts
c nfonts+1...NFONTS; other minor cleanups
e
s 00093/00088/00434
d D 2.3 90/11/03 20:36:18 karels 4 3
c changes from van: use malloc, stdio; in-memory environments
e
s 00001/00001/00521
d D 2.2 86/08/14 23:02:53 jaap 3 2
c Line buffer increased for blit screen dumps
e
s 00330/00101/00192
d D 2.1 85/07/18 14:30:47 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00293/00000/00000
d D 1.1 85/07/17 17:55:11 jaap 1 0
c date and time created 85/07/17 17:55:11 by jaap
e
u
U
t
T
I 4
/*
 * %W% (Berkeley) %G%
 */
E 4
I 1
D 2
#include <signal.h>
E 2

D 2
#ifdef vax
#define MAXPTR	(char *)0xfffffff
				/* max value of pointer on vaxes */
#define INCORE
#endif
#ifdef pdp11
#define	MAXPTR	(char *)-1	/* max value of any pointer variable */
				/* likely to be machine-dependent */
#endif

E 2
/* starting values for typesetting parameters: */

#define	PS	10	/* default point size */
#define	FT	1	/* default font position */
I 2
#define ULFONT	2	/* default underline font */
#define	BDFONT	3	/* default emboldening font */
#define	BIFONT	4	/* default bold italic font */
I 6
#define STIP	1	/* default stipple */
E 6
E 2
#define	LL	(unsigned) 65*INCH/10	/* line length; 39picas=6.5in */
#define	VS	((12*INCH)/72)	/* initial vert space */

#ifdef	NROFF
#	define	EM	t.Em
D 2
#	define	HOR	t.Hor
E 2
I 2
#	define	HOR	t.Adj
E 2
#	define	VERT	t.Vert
#	define	INCH	240	/* increments per inch */
#	define	SPS	INCH/10	/* space size */
#	define	SS	INCH/10	/* " */
#	define	TRAILER	0
D 2
#	define	UNPAD	0227
E 2
#	define	PO	0 /* page offset */
#	define	ASCII	1
D 4
#	define	PTID	1
E 4
#	define	LG	0
#	define	DTAB	0	/* set at 8 Ems at init time */
#	define	ICS	2*SPS
#endif
#ifndef NROFF	/* TROFF */
	/* Inch is set by ptinit() when troff started.
	/* all derived values set then too
	*/
#	define	INCH	Inch	/* troff resolution -- number of goobies/inch  */
#	define	POINT	(INCH/72)	/* goobies per point (1/72 inch) */
#	define	HOR	Hor	/* horizontal resolution in goobies */
#	define	VERT	Vert	/* vertical resolution in goobies */
#	define	SPS	(EM/3)	/* space size  */
#	define	SS	12	/* space size in 36ths of an em */
D 2
#	define	UNPAD	027
#	define	PO	(INCH - INCH/27) /* page offset 26/27ths inch */
E 2
I 2
#	define	PO	(INCH)	/* page offset 1 inch */
E 2
/* #	define	EM	(POINT * pts) */
#define	EM	(((long) INCH * pts + 36) / 72)	/* don't lose significance */
#define	EMPTS(pts)	(((long) INCH * (pts) + 36) / 72)
#	define	ASCII	0
D 4
#	define	PTID	1
E 4
#	define	LG	1
#	define	DTAB	(INCH/2)
#	define	ICS	3*SPS
#endif

/* These "characters" are used to encode various internal functions
/* Some make use of the fact that most ascii characters between
/* 0 and 040 don't have any graphic or other function.
/* The few that do have a purpose (e.g., \n, \b, \t, ...
/* are avoided by the ad hoc choices here.
/* See ifilt[] in n1.c for others -- 1, 2, 3, 5, 6, 7, 010, 011, 012 
*/

#define	LEADER	001
#define	IMP	004	/* impossible char; glues things together */
#define	TAB	011
#define	RPT	014	/* next character is to be repeated many times */
#define	CHARHT	015	/* size field sets character height */
#define	SLANT	016	/* size field sets amount of slant */
#define	DRAWFCN	017	/* next several chars describe arb drawing fcn */
I 6
			/* style: 's' m */
			/* thickness: 't' w */
E 6
			/* line: 'l' dx dy char */
			/* circle: 'c' r */
			/* ellipse: 'e' rx ry */
			/* arc: 'a' dx dy r */
			/* wiggly line '~' x y x y ... */
I 6
			/*	or     'g' x y x y ... */
#define DRAWTHICK	't'
#define DRAWSTYLE	's'
E 6
#define	DRAWLINE	'l'
#define	DRAWCIRCLE	'c'	/* circle */
#define	DRAWELLIPSE	'e'
#define	DRAWARC		'a'	/* arbitrary arc */
I 6
#define DRAWCURVE	'g'	/* gremlin spline */
#define	DRAWWIG		'~'	/* wiggly line with spline */
E 6
D 2
#define	DRAWWIG		'~'	/* wiggly line with spline */
E 2
I 2
#define	DRAWSPLINE	'~'	/* quadratic B spline */
I 6
#define	DRAWPOLY	'p'	/* polygon with stipples */
#define	DRAWUBPOLY	'P'	/* polygon, stipples, no border */
E 6
E 2

#define	LEFT	020	/* \{ */
#define	RIGHT	021	/* \} */
#define	FILLER	022	/* \& and similar purposes */
I 2
#define	XON	023	/* \X'...' starts here */
E 2
#define	OHC	024	/* optional hyphenation character \% */
#define	CONT	025	/* \c character */
#define	PRESC	026	/* printable escape */
I 2
#define	UNPAD	027	/* unpaddable blank */
E 2
#define	XPAR	030	/* transparent mode indicator */
#define	FLSS	031
#define	WORDSP	032	/* paddable word space */
#define	ESC	033
I 2
#define	XOFF	034	/* \X'...' ends here */
E 2

D 2
	/* there are several tests (using iscontrol())
	/* that rely on these having 034 true.
	*/
#define	iscontrol(n)	(n>=034 && n<=037)	/* used to test the next two */
E 2
I 2
#define	iscontrol(n)	(n==035 || n==036)	/* used to test the next two */
E 2
#define	HX	035	/* next character is value of \x'...' */
D 2
#define	FONTPOS	036	/* position of font \f(XX encoded in top */
#define MAXFONTS      99      /* Maximum number of fonts (in fontlab) */
E 2
I 2
D 5
#define MAXFONTS	99	/* Maximum number of fonts (in fontab) */
E 5
I 5
#define MAXFONTS	99	/* Max number of mounted fonts (in fontab) */
E 5
E 2

#define	HYPHEN	c_hyphen
#define	EMDASH	c_emdash	/* \(em */
D 2
#define	RULE	c_rule	/* \(ru */
#define	MINUS	c_minus	/* minus sign on current font */
#define	NARSP	c_narsp	/* narrow space \|: fake character */
#define	HNARSP	c_hnarsp	/* half narrow space \^: fake character */
#define	LIG_FI	c_fi	/* \(ff */
#define	LIG_FL	c_fl	/* \(fl */
#define	LIG_FF	c_ff	/* \(ff */
#define	LIG_FFI	c_ffi	/* \(Fi */
#define	LIG_FFL	c_ffl	/* \(Fl */
#define	ACUTE	c_acute	/* acute accent \(aa */
#define	GRAVE	c_grave	/* grave accent \(ga */
#define	UNDERLINE	c_under	/* \(ul */
E 2
I 2
#define	RULE	c_rule		/* \(ru */
#define	MINUS	c_minus		/* minus sign on current font */
#define	LIG_FI	c_fi		/* \(ff */
#define	LIG_FL	c_fl		/* \(fl */
#define	LIG_FF	c_ff		/* \(ff */
#define	LIG_FFI	c_ffi		/* \(Fi */
#define	LIG_FFL	c_ffl		/* \(Fl */
#define	ACUTE	c_acute		/* acute accent \(aa */
#define	GRAVE	c_grave		/* grave accent \(ga */
#define	UNDERLINE c_under	/* \(ul */
E 2
#define	ROOTEN	c_rooten	/* root en \(rn */
#define	BOXRULE	c_boxrule	/* box rule \(br */
D 2
#define	LEFTHAND	c_lefthand
E 2
I 2
#define	LEFTHAND c_lefthand	/* left hand for word overflow */
#define	DAGGER	c_dagger	/* dagger for footnotes */
E 2

/* array sizes, and similar limits: */

D 4
#define	NFONT	10	/* maximum number of fonts (including specials) */
E 4
I 4
#define	NFONT	128	/* maximum number of fonts (including specials) */
E 4
D 2

#define MAXCHARS	255	/* Maximum characters in one font up to now */

/* define enough space for the fontcache. EXTRAFONT is maximum space
currently to be used by a font
		  widthtab+kerntab+code 	dev.nchtab "asciifitab" */
#define EXTRAFONT (3*MAXCHARS * sizeof(char) + dev.nchtab + (128-32)\
	* sizeof(char) + sizeof(struct font) + 255 * sizeof(short))
/*							fonttab */

#define	NN	300	/* number registers */
E 2
I 2
#define	NN	400	/* number registers */
E 2
#define	NNAMES	15	 /* predefined reg names */
#define	NIF	15	/* if-else nesting */
D 2
#define	NS	64	/* name buffer */
E 2
I 2
#define	NS	128	/* name buffer */
E 2
#define	NTM	256	/* tm buffer */
#define	NEV	3	/* environments */
#define	EVLSZ	10	/* size of ev stack */
D 4
#define	DSIZE	512	/* disk sector size in chars */
E 4
I 4
#define	DSIZE	2048	/* disk sector size in chars */
E 4

D 2
/* the following defines the size of the infamous environment block.
   this macro is guaranteed to blow older C preprocessors out of the
   water.
   Furthermore, it is wrong: the proper value is more accurately
   determined by using sizeof *tchar in several places.
   no harm is done as long as it's big enough.
*/

#define	EVUSED	\
		(62 * sizeof(int)	/* integers in env block */	\
		+ 9 * sizeof(tchar)	/* tchars in env block */	\
		+ NHYP * sizeof(tchar)	/* hytab */	\
		+ NTAB * sizeof(int)	/* tabtab */	\
		+ (LNSIZE+WDSIZE) * sizeof(tchar))	/* line+word */

/* added two int's to environment block for ha request jna */
/* added another int for changed ht request jna */

#define	EVSPARE	DSIZE - EVUSED % DSIZE	/* number of leftover chars */
#define	EVS	(EVUSED + EVSPARE)	/* should be a multiple of DSIZE */
#define	NM	350	/* requests + macros */
E 2
I 2
#define	NM	500	/* requests + macros */
E 2
D 4
#define	DELTA	1024	/* delta core bytes */
E 4
I 4
#define	DELTA	8192	/* delta core bytes */
E 4
#define	NHYP	10	/* max hyphens per word */
#define	NHEX	128	/* byte size of exception word list */
D 2
#define	NTAB	35	/* tab stops */
E 2
I 2
#define	NTAB	40	/* tab stops */
E 2
#define	NSO	5	/* "so" depth */
#define	WDSIZE	270	/* word buffer size */
D 3
#define	LNSIZE	680	/* line buffer size */
E 3
I 3
#define	LNSIZE	1024	/* line buffer size */
E 3
#define	NDI	5	/* number of diversions */
D 2
#define	NTRTAB	350	/* number of items in trtab[] */
E 2
I 2
#define	NTRTAB	512	/* number of items in trtab[] */
#define NWIDCACHE 512	/* number of items in widcache[] */
E 2
#define	NTRAP	20	/* number of traps */
#define	NPN	20	/* numbers in "-o" */
#define	FBUFSZ	256	/* field buf size words */
D 2
#define	OBUFSZ	512	/* bytes */
#define	IBUFSZ	512	/* bytes */
#define	NC	256	/* cbuf size words */
E 2
I 2
D 4
#define	OBUFSZ	4096	/* bytes */
#define	IBUFSZ	4096	/* bytes */
E 4
I 4
#define	IBUFSZ	8192	/* bytes */
E 4
#define	NC	1024	/* cbuf size words */
E 2
#define	NOV	10	/* number of overstrike chars */
#define	NPP	10	/* pads per field */

/*
	Internal character representation:
	Internally, every character is carried around as
	a 32 bit cookie, called a "tchar" (typedef long).
	Bits are numbered 31..0 from left to right.
	If bit 15 is 1, the character is motion, with
		if bit 16 it's vertical motion
		if bit 17 it's negative motion
	If bit 15 is 0, the character is a real character.
		if bit 31	zero motion
		bits 30..24	size
		bits 23..16	font
I 2
		bit 8		absolute char number in 7..0
	This implies at most 256-32 characters in a single font,
	which is going to be a problem somewhere
E 2
*/

/* in the following, "L" should really be a tchar, but ... */

D 2
#define	MOT	(unsigned short)(01<<15)	/* motion character indicator */
E 2
I 2
#define	MOT	(01L<<15)	/* motion character indicator */
E 2
#define	MOTV	(07L<<15)	/* clear for motion part */
#define	VMOT	(01L<<16)	/* vert motion bit */
#define	NMOT	(01L<<17)	/* negative motion indicator*/
#define	MAXMOT	32767	/* bad way to write this!!! */
D 2
#define	ismot(n)	((unsigned short)(n) & MOT)	/* (short) is a cheap mask */
E 2
I 2
#define	ismot(n)	((n) & MOT)
E 2
#define	isvmot(n)	((n) & VMOT)	/* must have tested MOT previously */
#define	isnmot(n)	((n) & NMOT)	/* ditto */
D 2
#define	absmot(n)	((unsigned short)(n) & ~MOT)	/* (short) is cheap mask */
E 2
I 2
#define	absmot(n)	(unsigned)(0177777 & (n) & ~MOT)	/* (short) is cheap mask */
E 2

#define	ZBIT	(01L << 31)	/* zero width char */
#define	iszbit(n)	((n) & ZBIT)
I 2
#define	ABSCHAR		0400	/* absolute char number in this font */
E 2

#define	SMASK		(0177L << 24)
#define	FMASK		(0377L << 16)
#define	SFMASK		(SMASK|FMASK)	/* size and font in a tchar */
D 2
#define	CMASK		~MOT		/* clears MOT */
#define	CMASKL		077777L
#define	sbits(n)	((unsigned short)((n) >> 24) & 0177)
#define	fbits(n)	((unsigned short)((n) >> 16) & 0377)
#define	sfbits(n)	((unsigned short)(((n) & SFMASK) >> 16))
#define	cbits(n)	(unsigned short)(n)	/* isolate bottom 16 bits  */
E 2
I 2
#define	sbits(n)	(((n) >> 24) & 0177)
#define	fbits(n)	(((n) >> 16) & 0377)
#define	sfbits(n)	(unsigned)(0177777 & (((n) & SFMASK) >> 16))
#define	cbits(n)	(unsigned)(0177777 & (n))	/* isolate bottom 16 bits  */
#define	absbits(n)	(cbits(n) & ~ABSCHAR)

E 2
#define	setsbits(n,s)	n = (n & ~SMASK) | (tchar)(s) << 24
#define	setfbits(n,f)	n = (n & ~FMASK) | (tchar)(f) << 16
#define	setsfbits(n,sf)	n = (n & ~SFMASK) | (tchar)(sf) << 16
D 2
#define	setcbits(n,c)	n = (n & ~CMASKL | (c))	/* set character bits */
E 2
I 2
#define	setcbits(n,c)	n = (n & ~077777L | (c))	/* set character bits */
E 2

D 2
#define	MMASK	0100000	/* macro mask indicator */
#define	BMASK	0377
E 2
I 2
#define	BYTEMASK	0377
E 2
#define	BYTE	8

D 2
#define	TMASK	 037777
E 2
I 2
#define	ZONE	5	/* 5 hrs for EST */
#define	TABMASK	 037777
E 2
#define	RTAB	(unsigned) 0100000
#define	CTAB	040000

I 2
#define	TABBIT	02		/* bits in gchtab */
#define	LDRBIT	04
#define	FCBIT	010

E 2
#define	PAIR(A,B)	(A|(B<<BYTE))

D 2
typedef unsigned filep;
#define	BLK	128	/* alloc block tchars */
#define	NBLIST	1024	/* allocation list */
/* previous values were BLK 256 NBLIST 512 */
/* it seems good to keep the product constant */
		/* BLK*NBLIST<=65536 words, if filep=unsigned */
E 2
I 2
D 4
#define	oput(c)	if ((*obufp++ = (c)), obufp >= &obuf[OBUFSZ]) flusho(); else
E 4
I 4
#define	oput(c)	putc(c, ptid)
E 4
E 2

I 2
/*
 * "temp file" parameters.  macros and strings
 * are stored in an array of linked blocks,
 * which may be in memory if INCORE is set during
 * compilation, or otherwise in a file.
 * The numerology is delicate if filep is 16 bits:
	#define BLK 128
	#define NBLIST 512
 * i.e., the product is 16 bits long.
E 2

D 2
#define THRESH 160 /*digram goodness threshold*/
#define DUTCH_THRESH	3	/* for recursive bestesplits jna */
/* added the ha request, to change the hyphenation algorithm jna */
E 2
I 2
 * If filep is an unsigned long (and if your
 * compiler will let you say that) then NBLIST
 * can be a lot bigger.  Of course that makes
 * the file or core image a lot bigger too,
 * and means you don't detect missing diversion
 * terminations as quickly... .
 * It also means that you may have trouble running
 * on non-swapping systems, since the core image
 * will be over 1Mb.
E 2

D 2
#define ORIGINAL	0	/* The original (American English) algorithm */
#define DUTCH		1	/* "Bestesplits" routine */
#define MAXDIALECTS	1	/* number of dialects minus 1 */
E 2
I 2
 * In any case, both must be powers of 2.
 */
E 2

I 2
typedef unsigned int filep;	/* this is good for 32 bit machines */

#define	BLK	128	/* alloc block in tchars */
#ifdef SMALLER

#define NBLIST	1024

#else

#define	NBLIST	2048	/* allocation list.  smallish machines use 1024, bigger use 2048 */

#endif

E 2
typedef	long	tchar;	/* as an experiment */

extern	tchar	getch(), getch0();
extern	tchar	rbf(), rbf0();
extern	tchar	mot(), hmot(), vmot();
extern	tchar	makem(), sethl();
extern	tchar	popi();
extern	tchar	getlg();
extern	tchar	xlss();
extern	tchar	setfield();
extern	tchar	setz();
D 2
extern	tchar	setch(), absch();
E 2
I 2
extern	tchar	setch();
E 2
extern	tchar	setht(), setslant();

#define	atoi(i)		((int) atoi0(i))
extern	long	atoi0();

extern	int	Inch, Hor, Vert, Unitwidth;

/* these characters are used as various signals or values
/* in miscellaneous places.
/* values are set in specnames in t10.c
*/

extern int	c_hyphen;
extern int	c_emdash;
extern int	c_rule;
extern int	c_minus;
D 2
extern int	c_narsp;
extern int	c_hnarsp;
E 2
extern int	c_fi;
extern int	c_fl;
extern int	c_ff;
extern int	c_ffi;
extern int	c_ffl;
extern int	c_acute;
extern int	c_grave;
extern int	c_under;
extern int	c_rooten;
extern int	c_boxrule;
extern int	c_lefthand;
I 2
extern int	c_dagger;
E 2

D 4
extern int	stderr;	/* this is NOT the stdio value! */
I 2

extern	struct	d {	/* diversion */
E 4
I 4
struct	d {	/* diversion */
E 4
	filep	op;
	int	dnl;
	int	dimac;
	int	ditrap;
	int	ditf;
	int	alss;
	int	blss;
	int	nls;
	int	mkline;
	int	maxl;
	int	hnl;
	int	curd;
};

D 4
extern	struct	s {	/* stack frame */
E 4
I 4
struct	s {	/* stack frame */
E 4
	int	nargs;
	struct s *pframe;
	filep	pip;
	int	pnchar;
	tchar	prchar;
	int	ppendt;
	tchar	pch;
	tchar	*lastpbp;
	int	mname;
};

extern struct contab {
	unsigned short	rq;
	struct	contab *link;
	int	(*f)();
	unsigned mx;
} contab[NM];

extern struct numtab {
	short	r;		/* name */
	short	fmt;
	short	inc;
	int	val;
	struct	numtab *link;
} numtab[NN];

#define	PN	0
#define	NL	1
#define	YR	2
#define	HP	3
#define	CT	4
#define	DN	5
#define	MO	6
#define	DY	7
#define	DW	8
#define	LN	9
#define	DL	10
#define	ST	11
#define	SB	12
#define	CD	13
#define	PID	14

/* the infamous environment block */

D 4
#define	ics	env._ics
#define	sps	env._sps
#define	spacesz	env._spacesz
#define	lss	env._lss
#define	lss1	env._lss1
#define	ll	env._ll
#define	ll1	env._ll1
#define	lt	env._lt
#define	lt1	env._lt1
#define	ic	env._ic
#define	icf	env._icf
#define	chbits	env._chbits
#define	spbits	env._spbits
#define	nmbits	env._nmbits
#define	apts	env._apts
#define	apts1	env._apts1
#define	pts	env._pts
#define	pts1	env._pts1
#define	font	env._font
#define	font1	env._font1
#define	ls	env._ls
#define	ls1	env._ls1
#define	ad	env._ad
#define	nms	env._nms
#define	ndf	env._ndf
#define	fi	env._fi
#define	cc	env._cc
#define	c2	env._c2
#define	ohc	env._ohc
#define	tdelim	env._tdelim
#define	hyf	env._hyf
#define	hyoff	env._hyoff
#define hyalg	env._hyalg
#define hyalg1	env._hyalg1
#define	thresh	env._thresh
#define	un1	env._un1
#define	tabc	env._tabc
#define	dotc	env._dotc
#define	adsp	env._adsp
#define	adrem	env._adrem
#define	lastl	env._lastl
#define	nel	env._nel
#define	admod	env._admod
#define	wordp	env._wordp
#define	spflg	env._spflg
#define	linep	env._linep
#define	wdend	env._wdend
#define	wdstart	env._wdstart
#define	wne	env._wne
#define	ne	env._ne
#define	nc	env._nc
#define	nb	env._nb
#define	lnmod	env._lnmod
#define	nwd	env._nwd
#define	nn	env._nn
#define	ni	env._ni
#define	ul	env._ul
#define	cu	env._cu
#define	ce	env._ce
#define	in	env._in
#define	in1	env._in1
#define	un	env._un
#define	wch	env._wch
#define	pendt	env._pendt
#define	pendw	env._pendw
#define	pendnf	env._pendnf
#define	spread	env._spread
#define	it	env._it
#define	itmac	env._itmac
#define	lnsize	env._lnsize
#define	hyptr	env._hyptr
#define	tabtab	env._tabtab
#define	line	env._line
#define	word	env._word
E 4
I 4
#define	ics	(env->_ics)
#define	sps	(env->_sps)
#define	spacesz	(env->_spacesz)
#define	lss	(env->_lss)
#define	lss1	(env->_lss1)
#define	ll	(env->_ll)
#define	ll1	(env->_ll1)
#define	lt	(env->_lt)
#define	lt1	(env->_lt1)
#define	ic	(env->_ic)
#define	icf	(env->_icf)
#define	chbits	(env->_chbits)
#define	spbits	(env->_spbits)
#define	nmbits	(env->_nmbits)
#define	apts	(env->_apts)
#define	apts1	(env->_apts1)
#define	pts	(env->_pts)
#define	pts1	(env->_pts1)
#define	font	(env->_font)
#define	font1	(env->_font1)
#define	ls	(env->_ls)
#define	ls1	(env->_ls1)
#define	ad	(env->_ad)
#define	nms	(env->_nms)
#define	ndf	(env->_ndf)
#define	fi	(env->_fi)
#define	cc	(env->_cc)
#define	c2	(env->_c2)
#define	ohc	(env->_ohc)
#define	tdelim	(env->_tdelim)
#define	hyf	(env->_hyf)
#define	hyoff	(env->_hyoff)
#define hyalg	(env->_hyalg)
#define hyalg1	(env->_hyalg1)
#define	thresh	(env->_thresh)
#define	un1	(env->_un1)
#define	tabc	(env->_tabc)
#define	dotc	(env->_dotc)
#define	adsp	(env->_adsp)
#define	adrem	(env->_adrem)
#define	lastl	(env->_lastl)
#define	nel	(env->_nel)
#define	admod	(env->_admod)
#define	wordp	(env->_wordp)
#define	spflg	(env->_spflg)
#define	linep	(env->_linep)
#define	wdend	(env->_wdend)
#define	wdstart	(env->_wdstart)
#define	wne	(env->_wne)
#define	ne	(env->_ne)
#define	nc	(env->_nc)
#define	nb	(env->_nb)
#define	lnmod	(env->_lnmod)
#define	nwd	(env->_nwd)
#define	nn	(env->_nn)
#define	ni	(env->_ni)
#define	ul	(env->_ul)
#define	cu	(env->_cu)
#define	ce	(env->_ce)
#define	in	(env->_in)
#define	in1	(env->_in1)
#define	un	(env->_un)
#define	wch	(env->_wch)
#define	pendt	(env->_pendt)
#define	pendw	(env->_pendw)
#define	pendnf	(env->_pendnf)
#define	spread	(env->_spread)
#define	it	(env->_it)
#define	itmac	(env->_itmac)
#define	lnsize	(env->_lnsize)
#define	hyptr	(env->_hyptr)
#define	tabtab	(env->_tabtab)
#define	line	(env->_line)
#define	word	(env->_word)
I 6
#define	stip1	(env->_stip1)
#define	stip	(env->_stip)
E 6
E 4

/*
 * Note (jaap)
 * If this structure changes in ni.c, you should change
 * this as well
 */
D 4
extern struct env {
E 4
I 4
struct env {
E 4
	int	_ics;
	int	_sps;
	int	_spacesz;
	int	_lss;
	int	_lss1;
	int	_ll;
	int	_ll1;
	int	_lt;
	int	_lt1;
	tchar	_ic;
	int	_icf;
	tchar	_chbits;
	tchar	_spbits;
	tchar	_nmbits;
	int	_apts;
	int	_apts1;
	int	_pts;
	int	_pts1;
	int	_font;
	int	_font1;
	int	_ls;
	int	_ls1;
	int	_ad;
	int	_nms;
	int	_ndf;
	int	_fi;
	int	_cc;
	int	_c2;
	int	_ohc;
	int	_tdelim;
	int	_hyf;
	int	_hyoff;
	int	_hyalg;
	int	_hyalg1;
	int	_thresh;
	int	_un1;
	int	_tabc;
	int	_dotc;
	int	_adsp;
	int	_adrem;
	int	_lastl;
	int	_nel;
	int	_admod;
	tchar	*_wordp;
	int	_spflg;
	tchar	*_linep;
	tchar	*_wdend;
	tchar	*_wdstart;
	int	_wne;
	int	_ne;
	int	_nc;
	int	_nb;
	int	_lnmod;
	int	_nwd;
	int	_nn;
	int	_ni;
	int	_ul;
	int	_cu;
	int	_ce;
	int	_in;
	int	_in1;
	int	_un;
	int	_wch;
	int	_pendt;
	tchar	*_pendw;
	int	_pendnf;
	int	_spread;
	int	_it;
	int	_itmac;
	int	_lnsize;
I 6
	int	_stip;
	int	_stip1;
E 6
	tchar	*_hyptr[NHYP];
	int	_tabtab[NTAB];
	tchar	_line[LNSIZE];
	tchar	_word[WDSIZE];
D 4
} env;
E 4
I 4
};
E 4

I 4
extern struct env *env;
extern struct env env_array[];

E 4
/*
 * All changes will come after this comment (jaap)
 */

/*
 * hyphenation dependent stuff (jaap)
 */
#define THRESH 160	/*digram goodness threshold (from n8.c, (jaap))*/
#define	DUTCH_THRESH	3	/* for recursive bestesplits (jaap) */

#define ORIGINAL	0	/* original (American) English) algorithm */
#define DUTCH		1	/* second hyphenation routine (bestesplits) */
#define	MAXDIALECTS	1	/* number of hyphenation algorithms */

/*
 * define enough space for the fontcache. EXTRAFONT is maximum space
 * currently to be used by a font. The space for the fonttab is
 * for the "logical to physical font table mapping addition (jaap).
 */
#define MAXCHARS	255	/* current maximum of characters in a font */

I 5
#ifdef CWI
E 5
#define EXTRAFONT (3*MAXCHARS * sizeof(char) + dev.nchtab + (128-32) \
	* sizeof(char) + sizeof(struct Font) + 255 * sizeof(short))
I 5
#else
#define EXTRAFONT (3*MAXCHARS * sizeof(char) + dev.nchtab + (128-32) \
	* sizeof(char) + sizeof(struct Font))
#endif
E 5
I 4

#include <stdio.h>
#define fdprintf fprintf
#define flusho()
E 4
E 2
E 1
