h06302
s 00002/00003/00144
d D 2.2 93/07/27 09:15:35 bostic 3 2
c checkpoint; Mike Karels left this checked out.
e
s 00011/00100/00136
d D 2.1 85/07/18 14:30:34 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00236/00000/00000
d D 1.1 85/07/17 17:55:07 jaap 1 0
c date and time created 85/07/17 17:55:07 by jaap
e
u
U
t
T
I 1
D 2

E 2
extern	char	**argp;
extern	char	*chname;
extern	char	*eibuf;
extern	char	*enda;
extern	char	*fitab[];
extern	char	*fontab[];
extern	char	*kerntab[];
extern	char	*ibufp;
D 3
extern	char	*obufp;
E 3
extern	char	*unlkp;
extern	char	*xbufp;
extern	char	*xeibuf;
D 2
extern	char	codetab[];
E 2
I 2
extern	char	cfname[NSO][NS];
E 2
extern	char	devname[];
extern	char	fontfile[];
extern	char	ibuf[IBUFSZ];
extern	char	nextf[];
D 3
extern	char	obuf[],	*obufp;
E 3
extern	char	termtab[],	fontfile[];
extern	char	xbuf[IBUFSZ];
extern	filep	apptr;
extern	filep	ip;
extern	filep	nextb;
extern	filep	offset;
extern	filep	roff;
extern	filep	woff;
extern	short	*chtab;
extern	int	*pnp;
D 2
extern	int	*pslp;
E 2
extern	short	*pstab;
D 2
extern	int	*vlist;
extern	int	Bflg;
extern	int	ad,	admod;
extern	int	adrem;
extern	int	adsp;
E 2
extern	int	app;
D 2
extern	int	apts,	apts1,	pts,	pts1,	font,	font1;
E 2
extern	int	ascii;
D 2
extern	int	back;
E 2
extern	int	bd;
extern	int	bdtab[];
D 2
extern	int	c2;
extern	int	cc;
E 2
extern	int	ccs;
D 2
extern	int	ce;
extern	int	code;
E 2
extern	int	copyf;
D 2
extern	int	cps;
E 2
extern	int	cs;
D 2
extern	int	cu;
extern	int	cwidth;
E 2
extern	int	dfact;
extern	int	dfactd;
extern	int	diflg;
extern	int	dilev;
extern	int	donef;
extern	int	dotT;
D 2
extern	int	dotc;
E 2
extern	int	dpn;
extern	int	ds;
extern	int	ejf;
extern	int	em;
extern	int	eqflg;
extern	int	error;
extern	int	esc;
extern	int	eschar;
extern	int	ev;
extern	int	evi;
extern	int	evlist[EVLSZ];
extern	int	fc;
D 2
extern	int	fi;
E 2
extern	int	flss;
D 2
extern	int	fmt[NN];
extern	int	font1;
extern	int	font;
E 2
extern	int	fontlab[];
extern	int	gflag;
D 2
extern	int	hyalg;
extern	int	hyalg1;
E 2
extern	int	hflg;
D 2
extern	int	hyf;
extern	int	hyoff;
E 2
extern	int	ibf;
D 2
extern	int	icf;
extern	int	ics;
E 2
extern	int	ifi;
extern	int	ifile;
extern	int	ifl[NSO];
extern	int	iflg;
D 2
extern	int	in1;
extern	int	in;
extern	int	inc[NN];
E 2
extern	int	init;
D 2
extern	int	it;
extern	int	itmac;
extern	int	lastl;
E 2
extern	int	lead;
D 2
extern	int	level;
E 2
extern	int	lg;
extern	int	lgf;
D 2
extern	int	ll1;
extern	int	ll;
extern	int	lnmod;
extern	int	lnsize;
extern	int	ls1;
extern	int	ls;
extern	int	lss1;
extern	int	lss;
extern	int	lt1;
extern	int	lt;
E 2
extern	int	macerr;
extern	int	mflg;
extern	int	mfont;
extern	int	mlist[NTRAP];
extern	int	mpts;
D 2
extern	int	nb;
extern	int	nc;
extern	int	nchar;
extern	int	ndf;
E 2
extern	int	ndone;
D 2
extern	int	ne;
extern	int	nel,	un;
E 2
extern	int	newmn;
D 2
extern	int	nfi;
E 2
extern	int	nflush;
extern	int	nfo;
extern	int	nfonts;
extern	int	nform;
extern	int	nhyp;
D 2
extern	int	ni;
E 2
extern	int	nlflg;
extern	int	nlist[NTRAP];
D 2
extern	int	nms;
extern	int	nn;
E 2
extern	int	no_out;
extern	int	nofeed;
extern	int	nonumb;
extern	int	noscale;
extern	int	npn;
extern	int	npnflg;
D 2
extern	int	nwd;
E 2
extern	int	nx;
D 2
extern	int	ohc;
E 2
extern	int	oldbits;
extern	int	oldmn;
extern	int	over;
extern	int	padc;
D 2
extern	int	paper;
extern	int	pendnf;
extern	int	pendt;
E 2
extern	int	pfont;
extern	int	pfrom;
extern	int	pipeflg;
extern	int	pl;
extern	int	pnlist[];
extern	int	po1;
extern	int	po;
extern	int	ppts;
extern	int	print;
D 2
extern	int	psflg;
E 2
D 3
extern	int	ptid;
E 3
I 3
extern	FILE	*ptid;
E 3
extern	int	pto;
D 2
extern	int	pts1;
extern	int	pts;
E 2
extern	int	quiet;
D 2
extern	int	r[NN];
E 2
extern	int	ralss;
extern	int	rargc;
extern	int	raw;
extern	int	res;
extern	int	setwdf;
extern	int	sfont;
extern	int	smnt;
D 2
extern	int	spacesz;
extern	int	spflg;
extern	int	spread;
extern	int	sps;
E 2
extern	int	stdi;
extern	int	stop;
extern	int	sv;
D 2
extern	int	tabc,	dotc;
E 2
extern	int	tabch,	ldrch;
D 2
extern	int	tabtab[NTAB];
extern	int	tdelim;
E 2
extern	int	tflg;
D 2
extern	int	tlss;
E 2
extern	int	totout;
extern	int	trap;
D 2
extern 	int	thresh;
extern	int	trflg;
E 2
extern	int	trtab[];
extern	int	tty;
extern	int	ttyod;
extern	int	ttysave;
D 2
extern	int	ul;
extern	tchar	ulbit;
E 2
extern	int	ulfont;
D 2
extern	int	un1;
extern	int	un;
E 2
extern	int	vflag;
D 2
extern	int	waitf;
E 2
extern	int	wbfi;
D 2
extern	int	wch;
E 2
extern	int	widthp;
D 2
extern	int	wne;
extern	int	xbitf;
extern	int	xflg;
E 2
extern	int	xfont;
extern	int	xpts;
extern	no_out;
D 2
extern	struct	font	*fontbase[NFONT+1];	/* origin of each font in core hole */
E 2
extern	struct	s	*ejl;
extern	struct	s	*frame,	*stk,	*nxf;
extern	struct	sgttyb	ttys;
extern	tchar	**hyp;
D 2
extern	tchar	*ap;
extern	tchar	*cp;
extern	tchar	*hyptr[NHYP];
extern	tchar	*linep;
E 2
extern	tchar	*olinep;
D 2
extern	tchar	*pendw;
extern	tchar	*wdstart,	*wdend;
extern	tchar	*wordp;
extern	tchar	cbuf[NC];
extern	tchar	ch0;
E 2
I 2
extern	tchar	pbbuf[NC];
extern	tchar	*pbp;
extern	tchar	*lastpbp;
E 2
extern	tchar	ch;
D 2
extern	tchar	chbits;
extern	tchar	ic;
extern	tchar	inchar[LNSIZE],	*pinchar;
extern	tchar	line[];
extern	tchar	nmbits;
E 2
extern	tchar	nrbits;
extern	tchar	oline[];
D 2
extern	tchar	rchar;
extern	tchar	word[];
E 2
I 2
extern	struct widcache {	/* width cache, indexed by character */
	short	fontpts;
	short	width;
} widcache[NWIDCACHE];
extern	char gchtab[];
extern	struct	d	d[NDI];
extern	struct	d	*dip;
I 3
extern	char *malloc();
E 3
E 2
E 1
