h25033
s 00004/00002/00113
d D 2.2 93/07/27 09:15:43 bostic 3 2
c checkpoint; Mike Karels left this checked out.
e
s 00019/00039/00096
d D 2.1 85/07/18 14:28:37 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00135/00000/00000
d D 1.1 85/07/17 17:54:49 jaap 1 0
c date and time created 85/07/17 17:54:49 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% (CWI) %E%";
E 3
I 3
/*
static char sccsid[] = "@(#)nii.c	2.1 (CWI) 85/07/18";
*/
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
#endif lint
D 2

E 2
#include "tdef.h"
#ifdef NROFF
#include "tw.h"
#endif
D 2
#include "s.h"
#include "d.h"
#include "v.h"
E 2
I 2
#include "ext.h"
E 2
#include <sgtty.h>

D 2
int	*vlist = (int *)
&v;
struct s *frame, *stk, *ejl;
struct s *nxf;
E 2
I 2
struct 	s *frame, *stk, *ejl;
struct	s *nxf;
E 2

int	pipeflg;
D 2
#ifdef NROFF
int	hflg;
int	eqflg;
#endif
E 2
I 2
int	hflg;	/* used in nroff only */
int	eqflg;	/* used in nroff only */
E 2

#ifndef NROFF
int	xpts;
D 2
int	*pslp;
int	psflg;
E 2
int	ppts;
int	pfont;
D 2
int	paper;
E 2
int	mpts;
int	mfont;
int	cs;
D 2
int	code;
E 2
int	ccs;
int	bd;
D 2
int	back;
E 2
#endif

D 2
int	level;
E 2
int	stdi;
D 2
int	waitf;
E 2
int	nofeed;
int	quiet;
int	stop;
char	ibuf[IBUFSZ];
char	xbuf[IBUFSZ];
char	*ibufp;
char	*xbufp;
char	*eibuf;
char	*xeibuf;
D 2
tchar	cbuf[NC];
tchar	*cp;
E 2
I 2
tchar	pbbuf[NC];	/* pushback buffer for arguments, \n, etc. */
tchar	*pbp = pbbuf;	/* next free slot in pbbuf */
tchar	*lastpbp = pbbuf;	/* pbp in previous stack frame */
E 2
int	nx;
int	mflg;
tchar	ch = 0;
D 2
int	cps;
E 2
int	ibf;
int	ttyod;
D 2
struct sgttyb ttys;
E 2
I 2
struct	sgttyb ttys;
E 2
int	iflg;
D 3
char	*enda;
E 3
int	rargc;
char	**argp;
int	trtab[NTRTAB];
int	lgf;
int	copyf;
D 2
tchar	ch0;
int	cwidth;
filep ip;
E 2
I 2
filep	ip;
E 2
int	nlflg;
D 2
tchar	*ap;
E 2
int	donef;
int	nflush;
D 2
int	nchar;
tchar	rchar;
E 2
int	nfo;
int	ifile;
int	padc;
int	raw;
int	ifl[NSO];
int	ifi;
int	flss;
int	nonumb;
int	trap;
int	tflg;
int	ejf;
int	gflag;
int	dilev;
D 2
int	tlss;
filep offset;
E 2
I 2
filep	offset;
E 2
int	em;
int	ds;
D 2
filep woff;
E 2
I 2
filep	woff;
E 2
int	app;
int	ndone;
int	lead;
int	ralss;
D 2
filep nextb;
E 2
I 2
filep	nextb;
E 2
tchar	nrbits;
int	nform;
int	oldmn;
int	newmn;
int	macerr;
D 2
filep apptr;
E 2
I 2
filep	apptr;
E 2
int	diflg;
D 2
filep roff;
E 2
I 2
filep	roff;
E 2
int	wbfi;
D 2
int	inc[NN];
int	fmt[NN];
E 2
int	evi;
int	vflag;
int	noscale;
int	po1;
int	nlist[NTRAP];
int	mlist[NTRAP];
int	evlist[EVLSZ];
int	ev;
int	tty;
int	sfont	= FT;	/* appears to be "standard" font; used by .ul */
int	sv;
int	esc;
int	widthp;
int	xfont;
int	setwdf;
D 2
int	xbitf;
E 2
int	over;
int	nhyp;
tchar	**hyp;
D 2
int	*olinep;
E 2
I 2
tchar	*olinep;
E 2
int	ttysave = -1;
int	dotT;
char	*unlkp;
int	no_out;
I 2
struct	widcache widcache[NWIDCACHE];
struct	d d[NDI];
struct	d *dip;
E 2
E 1
