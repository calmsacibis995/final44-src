h43491
s 00008/00000/01721
d D 1.17 85/08/05 12:22:49 slatteng 19 18
c take out vax dependency in clearing bytes (still dependent on byte-swap)
e
s 00002/00000/01719
d D 1.16 85/04/29 14:06:52 slatteng 18 17
c made vfont directory setable in the makefile
e
s 00445/00004/01274
d D 1.15 84/05/24 16:56:59 slatteng 17 16
c added polygons with stipples to varian/versatec drivers and sorter
e
s 00015/00001/01263
d D 1.14 84/03/21 17:15:31 slatteng 16 15
c fixed bug that eliminates glyphs that didn't fit on the buffer (sign problem)
e
s 00029/00030/01235
d D 1.13 84/03/16 15:40:01 slatteng 15 14
c fixed error handling, page-end output, etc.
e
s 00006/00004/01259
d D 1.12 84/02/27 18:09:29 slatteng 14 11
c fix compile-time pointer warning, fix problem with glyphs in position zero
e
s 00004/00003/01260
d R 1.12 84/02/13 16:33:32 slatteng 13 11
c fix complaint about pointer combinations.
e
s 00003/00002/01261
d R 1.12 84/02/09 23:07:54 slatteng 12 11
c fixed complaint of possible pointer mess-up
e
s 00002/00000/01261
d D 1.11 83/12/18 15:24:16 slatteng 11 10
c make font directory moveable
e
s 00028/00009/01233
d D 1.10 83/11/30 11:49:14 slatteng 10 9
c add prog "stop", set band height to 1 inch, implement font swapping
e
s 00117/00105/01125
d D 1.9 83/10/22 16:00:54 slatteng 9 8
c change font search alg.;  remove internal font #;  fix error reporting;
c fix band output;  font position use marked by fnum, not fbits;  new argv user
e
s 00214/00168/01016
d D 1.8 83/08/19 14:56:57 slatteng 8 7
c it WORKS!!
e
s 00008/00012/01176
d D 1.7 83/07/29 16:55:12 slatteng 7 6
c convienient place to break... (it works)
e
s 00010/00001/01178
d D 1.6 83/07/09 21:45:16 slatteng 6 5
c added three new graphics functions: g, s, t
e
s 00005/00007/01174
d D 1.5 83/07/08 14:45:19 slatteng 5 4
c changed the heading...
e
s 00112/00117/01069
d D 1.4 83/07/05 17:20:54 slatteng 4 3
c fix various bugs, remove graphics stuff, put in  point function
e
s 00181/00248/01005
d D 1.3 83/06/24 17:24:00 slatteng 3 2
c ripped out lots of unnecessary code - ready to make driver from
e
s 00158/00127/01095
d D 1.2 83/05/19 20:15:38 slatteng 2 1
c Clean up the file, get it to just compile (added blank graphics)
e
s 01222/00000/00000
d D 1.1 83/05/19 18:57:30 slatteng 1 0
c date and time created 83/05/19 18:57:30 by slatteng
e
u
U
t
T
I 1
D 2
/* 
E 2
I 2
D 8
/* %M%	%I%	%E%
E 8
I 8
/*	%M%	%I%	%E%
E 8
 *
E 2
D 5
 * dver.c - Versatec driver for the new troff
E 5
I 5
D 14
 * Versatec driver for the new troff
E 14
I 14
 * VAX Versatec driver for the new troff
E 14
E 5
 *
D 5
 * Authors:	BWK(BELL), VCAT(berkley), and Richard L. Hyde
 *		Many parts where lifted from the above sources.
 * Editor:	Richard L. Hyde
 * 		Dept. of Computer Sciences
 * 		Purdue University
 * Date:	Thu Oct 28 1982
E 5
I 5
 * Authors:	BWK(BELL)
 *		VCAT(berkley)
 *		Richard L. Hyde, Perdue University
D 8
 *		and David Slattengren, Berkeley
E 8
I 8
 *		and David Slattengren, U.C. Berkeley
E 8
E 5
 */

 
D 2
/*
output language from troff:
all numbers are character strings
E 2
I 2
/*******************************************************************************
E 2

I 2
    output language from troff:
    all numbers are character strings

I 3
#..\n	comment
E 3
E 2
sn	size in points
D 3
fn	font as number from 1-n
E 3
I 3
fn	font as number from 1 to n
I 17
in	stipple as number from 1 to n
E 17
E 3
cx	ascii character x
D 3
Cxyz	funny char xyz. terminated by white space
E 3
I 3
Cxyz	funny char \(xyz. terminated by white space
E 3
Hn	go to absolute horizontal position n
Vn	go to absolute vertical position n (down is positive)
hn	go n units horizontally (relative)
vn	ditto vertically
nnc	move right nn, then print c (exactly 2 digits!)
		(this wart is an optimization that shrinks output file size
		 about 35% and run-time about 15% while preserving ascii-ness)
I 3
D 8
p	new page begins -- set v to 0
E 8
I 8
pn	new page begins (number n) -- set v to 0
P	spread ends -- output it.
E 8
nb a	end of line (information only -- no action needed)
	b = space before line, a = after
w	paddable word space -- no action needed

E 3
D 2
Dt ...\n	draw operation 't':
E 2
I 2
Dt ..\n	draw operation 't':
I 17
	Dt d		set line thickness to d pixels
	Ds d		set line style mask to d
E 17
E 2
	Dl x y		line from here by x,y
	Dc d		circle of diameter d with left side here
	De x y		ellipse of axes x,y with left side here
	Da x y r	arc counter-clockwise by x,y of radius r
D 3
	D~ x y x y ...	wiggly line by x,y then x,y ...
nb a	end of line (information only -- no action needed)
w	paddable word space -- no action needed
	b = space before line, a = after
p	new page begins -- set v to 0
D 2
#...\n	comment
x ...\n	device control functions:
E 2
I 2
#..\n	comment
E 3
I 3
	D~ x y x y ...	B-spline curve by x,y then x,y ...
I 17
	Dg x y x y ...	gremlin spline curve by x,y then x,y ...
	Dq d n miny maxy [p dx dy curx endy]	polygon filled with d, has n
			vectors, with extents from miny to maxy (no border)
E 17

E 3
x ..\n	device control functions:
E 2
D 3
	x i	init
	x T s	name of device is s
	x r n h v	resolution is n/inch
		h = min horizontal motion, v = min vert
	x p	pause (can restart)
	x s	stop -- done for ever
	x t	generate trailer
	x f n s	font position n contains font s
	x H n	set character height to n
	x S n	set slant to N
E 3
I 3
     x i	init
     x T s	name of device is s
     x r n h v	resolution is n/inch h = min horizontal motion, v = min vert
     x p	pause (can restart)
     x s	stop -- done for ever
     x t	generate trailer
     x f n s	font position n contains font s
     x H n	set character height to n
     x S n	set slant to N
E 3

	Subcommands like "i" are often spelled out like "init".
D 2
*/
E 2

D 2
#include	<stdio.h>
#include	<ctype.h>
#include	<signal.h>
E 2
I 2
*******************************************************************************/


#include <stdio.h>
#include <ctype.h>
D 3
#include <signal.h>
E 3
I 3
#include <sys/vcmd.h>
E 3
E 2
#include "dev.h"
D 3
#include <errno.h>
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include "modes.h"
E 3

D 2
/*
 * Versatec troff driver hacked from vcat and others.
 */
E 2

I 2
D 3
/*#define ACCOUNT*/
E 2
#define	NFONT	25
#define OPENREAD 0
#define RESTART 1
#define ABORT 2
E 3
I 3
D 9
#define DEBUGABLE		/* Yes, debugable... */
E 9
I 9
/* #define DEBUGABLE		/* No, not debugable... */
#define DRIVER			/* Yes, we're driving directly */
E 9
D 8
#define	NFONTS	25		/* total number of fonts useable */
E 8
I 8
D 17
#define	NFONTS	60		/* total number of fonts useable */
E 17
I 17
#define	NFONTS	65		/* total number of fonts useable */
E 17
E 8
I 4
#define	MAXSTATE 6		/* number of environments rememberable */
E 4
#define OPENREAD 0		/* mode for openning files */
#define RESTART	1		/* upon exit, return either RESTART */
#define ABORT	2		/*     or ABORT */
#define	FATAL	1		/* type of error */
#define	BMASK	0377		/* byte grabber */
I 11
#ifndef FONTDIR
E 11
D 8
#define FONTDIR	"/usr/lib/font"	/* default place to look for fonts */
E 8
I 8
#define FONTDIR	"/usr/lib/font"	/* default place to find font descriptions */
I 11
#endif
I 18
#ifndef BITDIR
E 18
E 11
#define BITDIR "/usr/lib/vfont" /* default place to look for font rasters */
I 18
#endif
E 18
E 8
I 4
#define MAXWRIT 4096		/* max characters allowed to write at once */
E 4
E 3

I 3
#define  hmot(n)	hpos += n
#define  hgoto(n)	hpos = n
D 8
#define  vmot(n)	vgoto(vpos + n)
E 8
I 8
#define  vmot(n)	vgoto(vpos + (n))
E 8


E 3
I 2
char	SccsId[]= "%M%	%I%	%E%";

E 2
int	output	= 0;	/* do we do output at all? */
int	nolist	= 0;	/* output page list if > 0 */
int	olist[20];	/* pairs of page numbers */
D 15
int	spage	= 9999;	/* stop every spage pages */
int	scount	= 0;
E 15
D 3
int	DX	= 1;
int	DY	= 1;
E 3
struct	dev	dev;
D 2
struct font *fontbase[NFONT+1];
E 2
I 2
D 3
struct	font	*fontbase[NFONT+1];
E 3
I 3
struct	font	*fontbase[NFONTS+1];
E 3
E 2
D 4
short	*pstab;
int	nsizes;
int	nfonts;
E 4
I 4
D 8
short	*pstab;		/* point size table pointer */
int	res;		/* input was computed according to this resolution */
E 8
I 8
short *	pstab;		/* point size table pointer */
E 8
int	nsizes;		/* number of sizes device is capable of printing */
D 17
int	nfonts;		/* number of fonts device is capable of printing */
E 17
I 17
int	nfonts = 1;	/* number of fonts device is capable of printing */
int	nstips = 1;	/* number of stipple fonts device can print */
E 17
E 4
D 3
int	smnt;	/* index of first special font */
E 3
I 3
D 9
int	smnt;		/* index of first special font */
E 9
E 3
int	nchtab;
D 8
char	*chname;
short	*chtab;
D 3
char	*fitab[NFONT+1];
char	*widthtab[NFONT+1];	/* widtab would be a better name */
char	*codetab[NFONT+1];	/* device codes */

#define	FATAL	1
#undef  BMASK
#define	BMASK	0377
int	dbg	= 0;
E 3
I 3
char	*fitab[NFONTS+1];
char	*widtab[NFONTS+1];
char	*codetab[NFONTS+1];	/* device codes */
E 3
D 2
int	res;		/* input assumed computed according to this resolution */
E 2
I 2
D 4
int	res;		/* input was computed according to this resolution */
E 4
I 3
char	*fontdir = FONTDIR;
E 8
I 8
char *	chname;
short *	chtab;
char *	fitab[NFONTS+1];	/* font inclusion table - maps ascii to ch # */
char *	widtab[NFONTS+1];	/* width table for each font */
char *	codetab[NFONTS+1];	/* device codes */
char *	fontdir = FONTDIR;	/* place to find devxxx directories */
char *	bitdir = BITDIR;	/* place to find raster fonts and fontmap */
D 9

E 9
I 9
char *	fontname[NFONTS+1];	/* list of what font is on what position */
E 9
E 8
I 4
struct {			/* table of what font */
D 9
	char *name;		/*   name is on what */
	int number;		/*   position in font tables */
} fontname[NFONTS+1];
I 8
struct {			/* table of what font */
E 9
	char fname[3];		/*   name maps to what */
	char *ffile;		/*   filename in bitdirectory */
} fontmap[NFONTS+1];
E 8
E 4
E 3
E 2

D 2
FILE	*tf	= NULL;	/* output file */
char	*fontdir	= "/usr/lib/font";
extern char devname[];
E 2
I 2
D 3
FILE	*tf	= NULL;		/* output file */
char	*fontdir= "/usr/lib/font";
extern	char	devname[];
E 2

/* hpos == hpos */
/* vpos != vpos vpos = vertical postion on the page xpos is rel buf0p */

#define	hmot(n)		hpos += n
#define	hgoto(n)	hpos = n
#define	vmot(n)		vgoto(vpos + n)
E 3
I 3
#ifdef DEBUGABLE
int	dbg	= 0;
#endif
E 3
D 4
int	maxX;
int	size	= -1;	/* this is invalid */
int	font	= -1;	/* current font */
E 4
I 4
D 8
int	maxH;		/* farthest down we've been on the current page */
int	size	= -1;	/* current point size being use */
int	font	= -1;	/* current font - not using any to start with */
E 8
I 8
int	size	= 1;	/* current point size (internal pstable index) */
int	font	= 1;	/* current font - assume reasonable starting font */
I 17
int	stip	= -1;	/* current stipple font - none to start with */
int	stipmem	= 0;	/* current member from stipple font to use */
E 17
E 8
E 4
D 2
int	hpos;		/* horizontal position where we are supposed to be next (left = 0) */
E 2
I 2
int	hpos;		/* horizontal position we are to be at next; left = 0 */
E 2
D 3
int	oldh;		/* previous H position */
E 3
int	vpos;		/* current vertical position (down positive) */
D 3
int	oldv;		/* current pos in 1/4 point units */
E 3
D 4
int	horig;		/* h origin of current block; hpos rel to this */
int	vorig;
E 4
I 4
D 7
int	horig;		/* h origin of current block (just a marker) */
int	vorig;		/* v origin of current block (just a marker) */
E 7
I 7
D 8
extern	linethickness;	/* thickness (in pixels) of any drawn objects */
E 8
I 8
int	maxv;		/* farthest down the page we've been */
extern	linethickness;	/* thickness (in pixels) of any drawn object */
E 8
extern	linmod;		/* line style (a bit mask - dotted, etc.) of objects */
E 7
int	lastw;		/* width of last character printed */
E 4
D 3
int	drawdot	= '.';	/* draw with this character */
int	drawsize = 2;	/* shrink by this factor when drawing */
/* new
 */
E 3

D 3
#define DISPATCHSIZE		256	/* must be a power of two */
#define CHARMASK		(DISPATCHSIZE-1)
#define NFONTS			25
#define SPECIALFONT		3
#define DSIZ			((sizeof *dispatch)*DISPATCHSIZE)
#define MAXF			(NFONT + 1)
#define OUTFILE 		1
E 3

I 3
#define DISPATCHSIZE	256		/* must be a power of two */
#define CHARMASK	(DISPATCHSIZE-1)
#define DSIZ		((sizeof *dispatch)*DISPATCHSIZE)
D 4
#define MAXF		(NFONTS + 1)
E 4
#define OUTFILE 	fileno (stdout)
I 4
D 8
#define	RES		200		/* resolution of the device */
#define	TRAILER		(10 * RES)	/* position of trailer */
E 8
E 4
E 3

D 3
#define RASTER_LENGTH           1600   /* 100 characters, 16 bits / character */
#define BYTES_PER_LINE		(RASTER_LENGTH/8)
#define NLINES			(11*200 + 10)
#define BUFFER_SIZE		(NLINES*BYTES_PER_LINE)
E 3
I 3
D 4
#define RASTER_LENGTH	7040
E 4
I 4
D 8
#define RASTER_LENGTH	2048			/* device line length */
E 8
I 8
#define	RES		200		/* resolution of the device (dots/in) */
#define RASTER_LENGTH	7040		/* device line length */
E 8
E 4
#define BYTES_PER_LINE	(RASTER_LENGTH/8)
D 4
#define NLINES		100
#define BUFFER_SIZE	(NLINES*BYTES_PER_LINE)
E 4
I 4
D 8
#define NLINES		(11 * RES)		/* 11" long paper */
E 8
I 8
D 9
#define BAND		3			/* length of a band in inches */
#define NLINES		(int)(BAND * RES)	/* 3" long bands */
E 9
I 9
D 10
#define BAND		2			/* length of a band in inches */
E 10
I 10
#define BAND		1			/* length of a band in inches */
E 10
#define NLINES		(int)(BAND * RES)	/* BAND" long bands */
E 9
E 8
#define BUFFER_SIZE	(NLINES*BYTES_PER_LINE)	/* number of chars in picture */
E 4
E 3

I 8
#define BUFTOP		(&buffer[0])
#define BUFBOTTOM	(&buffer[BUFFER_SIZE] - 1)
I 9
#define buf0p		BUFTOP			/* vorigin in circular buffer */
E 9
#define PAGEEND		1			/* flags to "outband" to tell */
#define OVERBAND	0			/* whether to fill out a page */
E 8
I 3

I 8

E 8
int	pltmode[] = { VPLOT };
int	prtmode[] = { VPRINT };
E 3
D 8
char	buffer[BUFFER_SIZE];	/* Big line buffers  */
char	*buf0p = &buffer[0];	/* Zero origin in circular buffer  */
E 8
I 8
char	buffer[BUFFER_SIZE];	/* versatec-wide NLINES buffer */
D 9
char *	buf0p = BUFTOP;		/* vorigin in circular buffer */
E 9
int	vorigin = 0;		/* where on the page startbuf maps to */
int	pagelen = 0;		/* how long the current "page" has printed */
E 8

D 8
char	*calloc();
char	*nalloc();
char	*allpanic();
E 8
I 8
char *	calloc();
char *	nalloc();
char *	allpanic();
I 9
char *	operand();
E 9
E 8
D 3
struct	passwd *getpwuid();
E 3

D 3
struct	header{
E 3
I 3
struct header {
E 3
	short	magic;
	unsigned short	size;
	short	maxx;
	short	maxy;
	short	xtnd;
} header;

struct	dispatch{
	unsigned short	addr;
	short	nbytes;
	char	up;
	char	down;
	char	left;
	char	right;
	short	width;
};

struct	fontdes {
D 9
	int	fnum;
E 9
I 9
	int	fnum;			/* if == -1, this position unused */
E 9
	int	psize;
	struct	dispatch *disp;
	char	*bits;
D 9
} fontdes[NFONTS] = {
	-1,
	-1
};
E 9
I 9
} fontdes[NFONTS+1];			/* is initialized at start of main */
E 9

struct dispatch *dispatch;
I 17
struct dispatch *stip_disp;
E 17
D 3
/* Accounting assumes roll paper */
#define FFLINES		650
#define EOTLINES	1400
E 3
int	cfnum = -1;
int	cpsize = 10;
int	cfont = 1;
char	*bits;
I 17
char	*stip_bits;
E 17
I 3
int	fontwanted = 1;		/* flag:  "has a new font been requested?" */
E 3
int	nfontnum = -1;
D 3
int	fontwanted = 1;
E 3
int	npsize = 10;

D 2
/* accounting variables */
E 2
I 2
D 3
#ifdef ACCOUNT
E 2
int lines = 0;		/* line counter */
char *user;		/* user name */
I 2
#endif
E 2

/*
    old
 */
E 3
 
I 3

E 3
main(argc, argv)
char *argv[];
{
D 9
	FILE *fp;
E 9
I 9
	register FILE *fp;
	register int i;
E 9
D 8
	int done();
E 8

D 2
	idput();

E 2
D 3
	tf = stdout;
E 3
D 9
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
E 9
I 9
	for (i = 0; i <= NFONTS; fontdes[i++].fnum = -1);
	while (--argc > 0 && **++argv == '-') {
		switch ((*argv)[1]) {
E 9
D 8
		case 'f':
E 8
		case 'F':
D 8
			fontdir = argv[2];
			argv++;
			argc--;
E 8
I 8
D 9
			bitdir = &argv[1][2];
E 9
I 9
			bitdir = operand(&argc, &argv);
E 9
E 8
			break;
I 8
		case 'f':
D 9
			fontdir = &argv[1][2];
E 9
I 9
			fontdir = operand(&argc, &argv);
E 9
			break;
E 8
		case 'o':
D 9
			outlist(&argv[1][2]);
E 9
I 9
			outlist(operand(&argc, &argv));
E 9
			break;
I 3
#ifdef DEBUGABLE
E 3
		case 'd':
D 9
			dbg = atoi(&argv[1][2]);
E 9
I 9
			dbg = atoi(operand(&argc, &argv));
E 9
			if (dbg == 0) dbg = 1;
D 3
			tf = stdout;
E 3
			break;
I 3
#endif
E 3
D 15
		case 's':
D 9
			spage = atoi(&argv[1][2]);
E 9
I 9
			spage = atoi(operand(&argc, &argv));
E 9
			if (spage <= 0)
				spage = 9999;
			break;
E 15
D 3
		case 'n':	/* user's name */
			argc--;
D 2
			user = *++argv;
E 2
I 2
#ifdef ACCOUNT
user =
#endif
			*++argv;
E 2
			break;
E 3
		}
D 9
		argc--;
		argv++;
E 9
	}
I 9
#ifdef DRIVER
	ioctl(OUTFILE, VSETSTATE, pltmode);
#endif
E 9

I 4
D 8
/* noversatec
E 4
	ioctl(OUTFILE, VSETSTATE, pltmode);
I 4
noversatec */
E 8
I 8
D 9
/*nov	ioctl(OUTFILE, VSETSTATE, pltmode);  */
E 8
E 4

	if (argc <= 1)
E 9
I 9
	if (argc < 1)
E 9
		conv(stdin);
	else
D 9
		while (--argc > 0) {
			if (strcmp(*++argv, "-") == 0)
E 9
I 9
		while (argc-- > 0) {
			if (strcmp(*argv, "-") == 0)
E 9
				fp = stdin;
			else if ((fp = fopen(*argv, "r")) == NULL)
				error(FATAL, "can't open %s", *argv);
			conv(fp);
			fclose(fp);
I 9
			argv++;
E 9
		}
I 2
D 3
#ifdef ACCOUNT
E 2
	accounting();
I 2
#endif
E 2
	waitchild();
E 3
D 8
	done();
E 8
	exit(0);
}

I 9

/*----------------------------------------------------------------------------*
 | Routine:	char  * operand (& argc,  & argv)
 |
 | Results:	returns address of the operand given with a command-line
 |		option.  It uses either "-Xoperand" or "-X operand", whichever
 |		is present.  The program is terminated if no option is present.
 |
 | Side Efct:	argc and argv are updated as necessary.
 *----------------------------------------------------------------------------*/

char *operand(argcp, argvp)
int * argcp;
char ***argvp;
{
	if ((**argvp)[2]) return(**argvp + 2); /* operand immediately follows */
	if ((--*argcp) <= 0) {			/* no operand */
	    error (FATAL, "command-line option operand missing.");
	}
	return(*(++(*argvp)));			/* operand next word */
}


E 9
outlist(s)	/* process list of page numbers to be printed */
char *s;
{
D 9
	int n1, n2, i;
E 9
I 9
	int n1, n2;
#ifdef DEBUGABLE
	int i;
#endif
E 9

	nolist = 0;
	while (*s) {
		n1 = 0;
		if (isdigit(*s))
			do
				n1 = 10 * n1 + *s++ - '0';
			while (isdigit(*s));
		else
			n1 = -9999;
		n2 = n1;
		if (*s == '-') {
			s++;
			n2 = 0;
			if (isdigit(*s))
				do
					n2 = 10 * n2 + *s++ - '0';
				while (isdigit(*s));
			else
				n2 = 9999;
		}
		olist[nolist++] = n1;
		olist[nolist++] = n2;
		if (*s != '\0')
			s++;
	}
	olist[nolist] = 0;
I 3
#ifdef DEBUGABLE
E 3
	if (dbg)
		for (i=0; i<nolist; i += 2)
			fprintf(stderr,"%3d %3d\n", olist[i], olist[i+1]);
I 3
#endif
E 3
}

conv(fp)
register FILE *fp;
{
	register int c, k;
	int m, n, n1, m1;
	char str[100], buf[300];

	while ((c = getc(fp)) != EOF) {
		switch (c) {
		case '\n':	/* when input is text */
D 15
		case ' ':
E 15
		case 0:		/* occasional noise creeps in */
I 15
		case '\t':
		case ' ':
E 15
			break;
		case '{':	/* push down current environment */
			t_push();
			break;
		case '}':
			t_pop();
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			/* two motion digits plus a character */
			hmot((c-'0')*10 + getc(fp)-'0');
			put1(getc(fp));
			break;
		case 'c':	/* single ascii character */
			put1(getc(fp));
			break;
		case 'C':
			fscanf(fp, "%s", str);
			put1s(str);
			break;
		case 't':	/* straight text */
D 9
			fgets(buf, sizeof(buf), fp);
E 9
I 9
D 15
			(void) fgets(buf, sizeof(buf), fp);
E 15
I 15
			if (fgets(buf, sizeof(buf), fp) == NULL)
			    error(FATAL, "unexpected end of input");
E 15
E 9
			t_text(buf);
			break;
		case 'D':	/* draw function */
D 9
			fgets(buf, sizeof(buf), fp);
E 9
I 9
D 15
			(void) fgets(buf, sizeof(buf), fp);
E 15
I 15
			if (fgets(buf, sizeof(buf), fp) == NULL)
			    error(FATAL, "unexpected end of input");
E 15
E 9
			switch (buf[0]) {
			case 'l':	/* draw a line */
D 2
				sscanf(buf+1, "%d %d", &n, &m);
				drawline(n, m, ".");
				break;
E 2
I 2
			    sscanf(buf+1, "%d %d", &n, &m);
D 4
			    drawline(n, m, ".");
E 4
I 4
			    drawline(n, m);
E 4
			    break;
E 2
			case 'c':	/* circle */
D 2
				sscanf(buf+1, "%d", &n);
				drawcirc(n);
				break;
E 2
I 2
			    sscanf(buf+1, "%d", &n);
			    drawcirc(n);
			    break;
E 2
			case 'e':	/* ellipse */
D 2
				sscanf(buf+1, "%d %d", &m, &n);
				drawellip(m, n);
				break;
E 2
I 2
			    sscanf(buf+1, "%d %d", &m, &n);
			    drawellip(m, n);
			    break;
E 2
			case 'a':	/* arc */
D 2
				sscanf(buf+1, "%d %d %d %d", &n, &m, &n1, &m1);
				drawarc(n, m, n1, m1);
				break;
E 2
I 2
			    sscanf(buf+1, "%d %d %d %d", &n, &m, &n1, &m1);
			    drawarc(n, m, n1, m1);
			    break;
I 17
                        case 'q':	/* polygon */
			    n = 1;			/* get stipple */
			    while (isspace(buf[++n]));	/* number first */
			    setfill(atoi(&(buf[n])));	/* set up stipple */
			    while (isdigit(buf[++n]));
			    polygon(&(buf[n]), fp);	/* draw polygon */
                            break;
E 17
E 2
			case '~':	/* wiggly line */
D 2
				drawwig(buf+1);
				break;
E 2
I 2
D 4
			    drawwig(buf+1);
E 4
I 4
D 6
			    drawwig(buf+1, fp);
E 6
I 6
			case 'g':	/* gremlin spline */
			    drawwig(buf+1, fp, buf[0] == '~');
			    break;
			case 't':	/* line thickness */
			    sscanf(buf+1, "%d", &n);
			    drawthick(n);
			    break;
			case 's':	/* line style */
			    sscanf(buf+1, "%d", &n);
			    drawstyle(n);
E 6
E 4
			    break;
E 2
			default:
D 2
				error(FATAL, "unknown drawing function %s\n", buf);
				break;
E 2
I 2
D 8
			    error(FATAL, "unknown drawing function %s\n", buf);
E 8
I 8
			    error(FATAL, "unknown drawing function %s", buf);
E 8
			    break;
E 2
			}
			break;
		case 's':
D 15
			fscanf(fp, "%d", &n);	/* ignore fractional sizes */
E 15
I 15
			fscanf(fp, "%d", &n);
E 15
			setsize(t_size(n));
			break;
I 17
		case 'i':
			fscanf(fp, "%d", &n);
			setstip(n);
			break;
E 17
		case 'f':
			fscanf(fp, "%s", str);
			setfont(t_font(str));
			break;
		case 'H':	/* absolute horizontal motion */
D 15
			/* fscanf(fp, "%d", &n); */
E 15
			while ((c = getc(fp)) == ' ')
				;
			k = 0;
			do {
				k = 10 * k + c - '0';
			} while (isdigit(c = getc(fp)));
			ungetc(c, fp);
			hgoto(k);
			break;
		case 'h':	/* relative horizontal motion */
D 2
			/* fscanf(fp, "%d", &n); */
E 2
			while ((c = getc(fp)) == ' ')
				;
			k = 0;
			do {
				k = 10 * k + c - '0';
			} while (isdigit(c = getc(fp)));
			ungetc(c, fp);
			hmot(k);
			break;
		case 'w':	/* word space */
			break;
		case 'V':
			fscanf(fp, "%d", &n);
			vgoto(n);
			break;
		case 'v':
			fscanf(fp, "%d", &n);
			vmot(n);
			break;
I 8
		case 'P':	/* new spread */
D 9
			outband(OVERBAND);
E 9
I 9
			if (output) outband(OVERBAND);
E 9
			break;
E 8
		case 'p':	/* new page */
			fscanf(fp, "%d", &n);
			t_page(n);
			break;
		case 'n':	/* end of line */
D 15
			while (getc(fp) != '\n')
				;
E 15
			t_newline();
D 15
			break;
E 15
I 15

E 15
		case '#':	/* comment */
D 15
			while (getc(fp) != '\n')
				;
E 15
I 15
			do
				c = getc(fp);
			while (c != '\n' && c != EOF);
E 15
			break;
		case 'x':	/* device control */
D 10
			devcntrl(fp);
E 10
I 10
			if (devcntrl(fp)) return;
E 10
			break;
		default:
D 8
			error(!FATAL, "unknown input character %o %c\n", c, c);
			done();
E 8
I 8
			error(FATAL, "unknown input character %o %c", c, c);
E 8
		}
	}
}

D 10
devcntrl(fp)	/* interpret device control functions */
FILE *fp;
E 10
I 10
int devcntrl(fp)	/* interpret device control functions */
FILE *fp;		/* returns -1 apon recieving "stop" command */
E 10
{
        char str[20], str1[50], buf[50];
	int c, n;

	fscanf(fp, "%s", str);
	switch (str[0]) {	/* crude for now */
	case 'i':	/* initialize */
		fileinit();
D 4
		t_init(0);
E 4
I 4
		t_init();
E 4
		break;
D 3
	case 'T':	/* device name */
		fscanf(fp, "%s", devname);
		break;
E 3
	case 't':	/* trailer */
D 8
		t_trailer();
E 8
		break;
	case 'p':	/* pause -- can restart */
		t_reset('p');
		break;
	case 's':	/* stop */
		t_reset('s');
D 10
		break;
E 10
I 10
		return -1;
E 10
	case 'r':	/* resolution assumed when prepared */
D 8
		fscanf(fp, "%d", &res);
E 8
I 8
		fscanf(fp, "%d", &n);
D 17
		if (n!=RES) error(FATAL,"Input computed with wrong resolution");
E 17
I 17
		if (n!=RES) error(FATAL,"Input computed for wrong printer");
E 17
E 8
		break;
	case 'f':	/* font used */
		fscanf(fp, "%d %s", &n, str);
D 9
		fgets(buf, sizeof buf, fp);	/* in case there's a filename */
E 9
I 9
		(void) fgets(buf, sizeof buf, fp);   /* in case of filename */
E 9
D 2
		ungetc('\n', fp);	/* fgets goes too far */
		str1[0] = 0;	/* in case there's nothing to come in */
E 2
I 2
		ungetc('\n', fp);		/* fgets goes too far */
		str1[0] = 0;			/* in case nothing comes in */
E 2
		sscanf(buf, "%s", str1);
		loadfont(n, str, str1);
		break;
D 2
	/* these don't belong here... */
E 2
I 2
						/* these don't belong here... */
E 2
	case 'H':	/* char height */
		fscanf(fp, "%d", &n);
		t_charht(n);
		break;
	case 'S':	/* slant */
		fscanf(fp, "%d", &n);
		t_slant(n);
		break;
	}
	while ((c = getc(fp)) != '\n')	/* skip rest of input line */
		if (c == EOF)
D 10
			break;
E 10
I 10
			return -1;
	return 0;
E 10
}

D 2
fileinit()	/* read in font and code files, etc. */
E 2
I 2
/* fileinit:	read in font and code files, etc.
		Must open table for device, read in resolution,
D 8
		size info, font info, etc. and set params
E 8
I 8
		size info, font info, etc. and set params.
		Also read in font name mapping.
E 8
*/
fileinit()
E 2
{
D 8
	int i, fin, nw;
	char	*filebase, *p;
	char	temp[60];
E 8
I 8
	register int i;
	register int fin;
	register int nw;
	register char *filebase;
	register char *p;
	register FILE *fp;
	char	temp[100];
E 8

I 8

		/* first, read in font map file.  The file must be of Format:
			XX  FILENAME  (XX = troff font name)
			with one entry per text line of the file.
		   Extra stuff after FILENAME is ignored */

	sprintf(temp, "%s/fontmap", bitdir);
	if ((fp = fopen(temp, "r")) == NULL)
		error(FATAL, "Can't open %s", temp);
	for (i = 0; i <= NFONTS && fgets(temp, 100, fp) != NULL; i++) {
		sscanf(temp, "%2s", fontmap[i].fname);
		p = &temp[0];
		while (*p != ' ' && *p != '	') p++;
		while (*p == ' ' || *p == '	') p++;
		filebase = p;
		for (nw = 1; *p != '\n' && *p != ' ' && *p != '\t'; p++) nw++;
		fontmap[i].ffile = nalloc(1, nw);
		sscanf(filebase, "%s", fontmap[i].ffile);
	}
	fontmap[++i].fname[0] = '0';		/* finish off with zeros */
	fontmap[i].ffile = (char *) 0;
	fclose(fp);
#ifdef DEBUGABLE
	if(dbg) {
	    fprintf(stderr, "font map:\n");
	    for (i = 0; fontmap[i].ffile; i++)
		fprintf(stderr,"%s = %s\n", fontmap[i].fname, fontmap[i].ffile);
	}
#endif


E 8
D 2
	/* open table for device,
	/* read in resolution, size info, font info, etc.
	/* and set params
	*/
E 2
D 3
	sprintf(temp, "%s/dev%s/DESC.out", fontdir, devname);
E 3
I 3
D 9
	sprintf(temp, "%s/devver/DESC.out", fontdir);
E 9
I 9
	sprintf(temp, "%s/devvp/DESC.out", fontdir);
E 9
E 3
	if ((fin = open(temp, 0)) < 0)
D 8
		error(FATAL, "can't open tables for %s\n", temp);
E 8
I 8
		error(FATAL, "can't open tables for %s", temp);
E 8
D 9
	read(fin, &dev, sizeof(struct dev));
E 9
I 9
	if (read(fin, &dev, sizeof(struct dev)) != sizeof(struct dev))
		error(FATAL, "can't read header for %s", temp);
E 9
	nfonts = dev.nfonts;
	nsizes = dev.nsizes;
I 17
	nstips = dev.nstips;
E 17
	nchtab = dev.nchtab;
D 8
	filebase = calloc(1,dev.filesize);	/* enough room for whole file */
E 8
I 8
	filebase = calloc(1, dev.filesize);	/* enough room for whole file */
E 8
D 9
	read(fin, filebase, dev.filesize);	/* all at once */
E 9
I 9
	if (read(fin, filebase, dev.filesize) != dev.filesize)	/* at once */
		error(FATAL, "can't read width table for %s", temp);
E 9
	pstab = (short *) filebase;
	chtab = pstab + nsizes + 1;
	chname = (char *) (chtab + dev.nchtab);
	p = chname + dev.lchname;
	for (i = 1; i <= nfonts; i++) {
		fontbase[i] = (struct font *) p;
D 2
		nw = *p & BMASK;	/* 1st thing is width count */
E 2
I 2
		nw = *p & BMASK;		/* 1st thing is width count */
E 2
D 9
		if (smnt == 0 && fontbase[i]->specfont == 1)
D 2
			smnt = i;	/* first special font */
		p += sizeof(struct font);	/* that's what's on the beginning */
E 2
I 2
			smnt = i;		/* first special font */
		p += sizeof(struct font);	/* that is on the beginning */
E 9
I 9
		p += sizeof(struct font);
E 9
E 2
D 3
		widthtab[i] = p;
E 3
I 3
		widtab[i] = p;
E 3
		codetab[i] = p + 2 * nw;
		fitab[i] = p + 3 * nw;
		p += 3 * nw + dev.nchtab + 128 - 32;
		t_fp(i, fontbase[i]->namefont, fontbase[i]->intname);
D 3
		if(dbg > 1) fontprint(i);
E 3
I 3
#ifdef DEBUGABLE
		if (dbg > 1) fontprint(i);
#endif
E 3
	}
I 17
	for (i = 1; i <= nstips; i++) {		/* add in stipple "filenames" */
		if (nfonts + i <= NFONTS)
			t_fp(nfonts + i, p, (char *)0);
		p += strlen(p) + 1;
	}
E 17
D 2
	fontbase[0] = (struct font *) calloc(1,3*255 + dev.nchtab + (128-32) + sizeof (struct font));
E 2
I 2
	fontbase[0] = (struct font *)
		calloc(1,3*255 + dev.nchtab + (128-32) + sizeof (struct font));
E 2
D 3
	widthtab[0] = (char *) fontbase[0] + sizeof (struct font);
E 3
I 3
	widtab[0] = (char *) fontbase[0] + sizeof (struct font);
E 3
	fontbase[0]->nwfont = 255;
	close(fin);
}

I 9
#ifdef DEBUGABLE
E 9
fontprint(i)	/* debugging print of font i (0,...) */
{
	int j, n;
	char *p;

	fprintf(stderr,"font %d:\n", i);
	p = (char *) fontbase[i];
	n = fontbase[i]->nwfont & BMASK;
D 2
	fprintf(stderr,"base=0%o, nchars=%d, spec=%d, name=%s, widtab=0%o, fitab=0%o\n",
		p, n, fontbase[i]->specfont, fontbase[i]->namefont, widthtab[i], fitab[i]);
E 2
I 2
	fprintf(stderr,
	    "base=0%o, nchars=%d, spec=%d, name=%s, widtab=0%o, fitab=0%o\n",p,
D 3
	    n,fontbase[i]->specfont,fontbase[i]->namefont,widthtab[i],fitab[i]);
E 3
I 3
	    n,fontbase[i]->specfont,fontbase[i]->namefont,widtab[i],fitab[i]);
E 3
E 2
	fprintf(stderr,"widths:\n");
	for (j=0; j <= n; j++) {
D 3
		fprintf(stderr," %2d", widthtab[i][j] & BMASK);
E 3
I 3
		fprintf(stderr," %2d", widtab[i][j] & BMASK);
E 3
		if (j % 20 == 19) fprintf(stderr,"\n");
	}
	fprintf(stderr,"\ncodetab:\n");
	for (j=0; j <= n; j++) {
		fprintf(stderr," %2d", codetab[i][j] & BMASK);
		if (j % 20 == 19) fprintf(stderr,"\n");
	}
	fprintf(stderr,"\nfitab:\n");
	for (j=0; j <= dev.nchtab + 128-32; j++) {
		fprintf(stderr," %2d", fitab[i][j] & BMASK);
		if (j % 20 == 19) fprintf(stderr,"\n");
	}
	fprintf(stderr,"\n");
}
I 9
#endif
E 9

I 8

E 8
loadfont(n, s, s1)	/* load font info for font s on position n (0...) */
int n;
char *s, *s1;
{
	char temp[60];
D 10
	int fin, nw, norig;
E 10
I 10
	register int fin;
	register int nw;
	register int norig;
E 10

D 3
	if (n < 0 || n > NFONT)
E 3
I 3
	if (n < 0 || n > NFONTS)
E 3
		error(FATAL, "illegal fp command %d %s", n, s);
	if (strcmp(s, fontbase[n]->namefont) == 0)
		return;
I 10

	for (fin = 1; fin <= NFONTS; fin++)	/* first check to see if the */
	    if (strcmp(s, fontbase[fin]->namefont) == 0) {  /* font is loaded */
		register char *c;			    /* somewhere else */

#define ptrswap(x, y) { c = (char*) (x); x = y; y = c; }
I 14
#define ptrfswap(x, y) { c = (char*) (x); x = y; y = (struct font *)c; }
E 14

D 14
		ptrswap(fontbase[n], fontbase[fin]);
E 14
I 14
		ptrfswap(fontbase[n], fontbase[fin]);
E 14
		ptrswap(codetab[n], codetab[fin]);
		ptrswap(widtab[n], widtab[fin]);
		ptrswap(fitab[n], fitab[fin]);
		t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
		t_fp(fin, fontbase[fin]->namefont, fontbase[fin]->intname);
		return;
	    }

E 10
	if (s1 == NULL || s1[0] == '\0')
D 3
		sprintf(temp, "%s/dev%s/%s.out", fontdir, devname, s);
E 3
I 3
D 9
		sprintf(temp, "%s/devver/%s.out", fontdir, s);
E 9
I 9
		sprintf(temp, "%s/devvp/%s.out", fontdir, s);
E 9
E 3
	else
		sprintf(temp, "%s/%s.out", s1, s);
	if ((fin = open(temp, 0)) < 0)
		error(FATAL, "can't open font table %s", temp);
	norig = fontbase[n]->nwfont & BMASK;
D 9
	read(fin, fontbase[n], 3*norig + nchtab+128-32 + sizeof(struct font));
E 9
I 9
	if (read(fin,fontbase[n],3*norig+nchtab+128-32+sizeof(struct font)) < 0)
		error(FATAL, "Can't read in font %s on position %d", s, n);
E 9
	if ((fontbase[n]->nwfont & BMASK) > norig)
D 8
		error(FATAL, "Font %s too big for position %d\n", s, n);
E 8
I 8
		error(FATAL, "Font %s too big for position %d", s, n);
E 8
	close(fin);
	nw = fontbase[n]->nwfont & BMASK;
D 3
	widthtab[n] = (char *) fontbase[n] + sizeof(struct font);
	codetab[n] = (char *) widthtab[n] + 2 * nw;
	fitab[n] = (char *) widthtab[n] + 3 * nw;
E 3
I 3
	widtab[n] = (char *) fontbase[n] + sizeof(struct font);
	codetab[n] = (char *) widtab[n] + 2 * nw;
	fitab[n] = (char *) widtab[n] + 3 * nw;
E 3
	t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
D 2
	fontbase[n]->nwfont = norig; /* so can later use full original size */
E 2
I 2
	fontbase[n]->nwfont = norig;	/* to later use full original size */
I 3
#ifdef DEBUGABLE
E 3
E 2
	if (dbg > 1) fontprint(n);
I 3
#endif
E 3
}

D 8
done()
{
	t_reset('s');
	exit(0);
}
E 8
I 8

E 8
/*VARARGS1*/
error(f, s, a1, a2, a3, a4, a5, a6, a7) {
	fprintf(stderr, "dver: ");
	fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
	fprintf(stderr, "\n");
D 9
	if (f)
D 8
		done();
E 8
I 8
		exit(1);
E 9
I 9
	if (f) exit(ABORT);
E 9
E 8
}

D 2
/*
	Here beginneth all the stuff that really depends
	on the versatec  (we hope).
*/
E 2

I 2
D 8
/*******************************************************************************
I 4
 * Routine:	
 * Results:	
 * Side Efct:	
 ******************************************************************************/
E 4
E 2

E 8
I 2
D 4
    Here beginneth all the stuff that really depends on the versatec (we hope).

*******************************************************************************/


E 2
D 3
char	devname[20]	= "dver";

E 3
#define	RES	200
D 3

E 3
#define	TRAILER	(14 * res)
D 3
#define	LMARGIN	0		/* left margin offset */
#define	HMAX	(48 * (res/6))	/* maximum horizontal size = 48 picas */
#define	VMAX	(12 * res)	/* 15 inch page */
E 3

D 2
int	lastw;	/* last character and width (maybe not used) */

E 2
I 2
int	lastw;		/* last character and width (maybe not used) */
E 2
long	paper;		/* paper used */


t_init(reinit)	/* initialize device */
int reinit;
E 4
I 4
t_init()	/* initialize device */
E 4
{
D 9
	int i;
E 9
I 9
	vorigin = pagelen = maxv = hpos = vpos = 0;
E 9

D 3
	hpos = vpos = oldv = oldh = 0;
E 3
I 3
D 8
	hpos = vpos = 0;
E 8
I 8
D 9
	maxv = hpos = vpos = 0;
E 8
E 3
D 2
	/* the above are not true until the code below happens*/
E 2
I 2

E 9
I 9
	output = 0;		/* don't output anything yet */
E 9
D 4
		/* the above are not true until the code below happens*/

E 4
E 2
	setsize(t_size(10));	/* start somewhere */
	setfont(1);
D 3

D 2
	for (i = 0; i < nchtab; i++)/* find the line drawing character */
E 2
I 2
	for (i = 0; i < nchtab; i++)		/* find the line drawing char */
E 2
		if (strcmp(&chname[chtab[i]], "l.") == 0)
			break;
	if (i < nchtab) {
		drawdot = i + 128;
		drawsize = 1;
	} else {
		drawdot = '.';
		drawsize = 2;	/* half size */
	}
E 3
}

D 4
#define	MAXSTATE	6
E 4

struct state {
	int	ssize;
	int	sfont;
	int	shpos;
	int	svpos;
D 7
	int	shorig;
	int	svorig;
E 7
I 7
	int	sstyle;
	int	sthick;
E 7
};
struct	state	state[MAXSTATE];
struct	state	*statep = state;

t_push()	/* begin a new block */
{
	statep->ssize = size;
	statep->sfont = font;
D 7
	statep->shorig = horig;
	statep->svorig = vorig;
E 7
I 7
	statep->sstyle = linmod;
	statep->sthick = linethickness;
E 7
	statep->shpos = hpos;
	statep->svpos = vpos;
D 7
	horig = hpos;
	vorig = vpos;
	hpos = vpos = 0;
E 7
	if (statep++ >= state+MAXSTATE)
		error(FATAL, "{ nested too deep");
D 7
	hpos = vpos = 0;
E 7
}

t_pop()	/* pop to previous state */
{
	if (--statep < state)
		error(FATAL, "extra }");
	size = statep->ssize;
	font = statep->sfont;
	hpos = statep->shpos;
	vpos = statep->svpos;
D 7
	horig = statep->shorig;
	vorig = statep->svorig;
E 7
I 7
	linmod = statep->sstyle;
	linethickness = statep->sthick;
E 7
}

I 8

E 8
t_page(n)	/* do whatever new page functions */
{
	int i;


D 9
	if (output) {
D 3
		if (tf != stdout)
			paper += vpos;
E 3
I 3
D 4
		paper += vpos;
E 4
E 3
		if (++scount >= spage) {
D 8
			t_reset('p');
E 8
			scount = 0;
D 8
		}
D 2
	/* flush out the buffer. Do it in a child proc */
	/* this buffering was added by Bob Brown to stop the versatec */
	/* from smearing while waiting for the next page */
E 2
I 2
D 3
/*******
	flush out the buffer. Do it in a child proc
	this buffering was added by Bob Brown to stop the versatec
	from smearing while waiting for the next page
*******/
E 2
		waitchild();
		if (fork() == 0) {
			slop_lines(maxX);
			ioctl(OUTFILE, VSETSTATE, prtmode);
			if (write(OUTFILE, "\f", 2) != 2)
				exit(RESTART);
			ioctl(OUTFILE, VSETSTATE, pltmode);
			exit(0);
		}
I 2
#ifdef ACCOUNT
E 2
		lines += maxX;
I 2
#endif
E 3
I 3
D 4
		slop_lines(maxX);
E 4
I 4
		slop_lines(maxH);
/* noversatec
E 4
		ioctl(OUTFILE, VSETSTATE, prtmode);
		if (write(OUTFILE, "\f", 2) != 2)
			exit(RESTART);
		ioctl(OUTFILE, VSETSTATE, pltmode);
E 3
E 2
D 4
		size = BYTES_PER_LINE * maxX;
E 4
I 4
noversatec */
		size = BYTES_PER_LINE * maxH;
E 4
		vclear(buf0p, size);
		buf0p = buffer;
E 8
I 8
			t_reset('p');
		} else
			outband(PAGEEND);
E 8
	}
E 9
I 9
	if (output) outband(PAGEEND);

E 9
I 8
	maxv = vpos = 0;
E 8

D 4
	maxX = 0;
E 4
I 4
D 8
	maxH = 0;
E 4

	vpos = 0;
E 8
D 3
	oldv = 0;
E 3
	output = 1;
	if (nolist == 0)
D 8
		return;	/* no -o specified */
E 8
I 8
		return;		/* no -o specified */
E 8
	output = 0;
	for (i = 0; i < nolist; i += 2)
		if (n >= olist[i] && n <= olist[i+1]) {
			output = 1;
			break;
		}
}
D 3
waitchild()
{
	int status;
	while ( wait(&status) != -1 )
		if ( ((status>>8) & 0xff ) != 0 )
			exit((status>>8) & 0xff);
}
E 3

I 8

outband(page)
int page;
{
    register int outsize;

D 9
    if (page == PAGEEND) {		/* set to inch boundary */
	if ((outsize = maxv - ++pagelen) < 1) return;
	outsize = ((outsize + RES - 1) / RES) * RES * BYTES_PER_LINE;
	vwrite(buf0p, outsize);
	vclear(buf0p, outsize);
	vorigin = 0;
	pagelen = 0;
E 9
I 9
    if (page == PAGEEND) {		/* set outsize to inch boundary */
D 15
	outsize = (maxv + (RES - 1) - pagelen) / RES;
E 15
I 15
	outsize = (maxv + (RES - 2) - pagelen) / RES;
E 15
I 10
	vorigin = pagelen = 0;		/* reset for new page */
E 10
	if (outsize < 1) return;	/* if outsize <= zero, forget it */

D 15
	outsize *= RES * BYTES_PER_LINE;	/* are assured that outsize */
	vwrite(buf0p, outsize);			/* will NOT be > BUFFER_SIZE */
	vclear(buf0p, outsize);			/* since vsort makes sure of */
D 10
	vorigin = pagelen = 0;			/* putting P commands in */
E 9
    } else {
E 10
I 10
    } else {					/* putting P commands in */
E 15
I 15
	outsize *= RES * BYTES_PER_LINE;
	vwrite(buf0p, outsize > BUFFER_SIZE ? BUFFER_SIZE : outsize);
	vclear(buf0p, BUFFER_SIZE);
	while ((outsize -= BUFFER_SIZE) > 0)
	    vwrite(buf0p, outsize > BUFFER_SIZE ? BUFFER_SIZE : outsize);
    } else {
E 15
E 10
	vorigin += NLINES;
	pagelen += NLINES;
	vwrite(buf0p, BUFFER_SIZE);
	vclear(buf0p, BUFFER_SIZE);
    }
}


E 8
t_newline()	/* do whatever for the end of a line */
{
	hpos = 0;	/* because we're now back at the left margin */
D 2

E 2
}

t_size(n)	/* convert integer to internal size number*/
int n;
{
	int i;

	if (n <= pstab[0])
D 8
		return(1);
	else if (n >= pstab[nsizes-1])
		return(nsizes);
E 8
I 8
		return(0);
	else if (n >= pstab[nsizes - 1])
		return(nsizes - 1);
E 8
	for (i = 0; n > pstab[i]; i++)
		;
D 8
	return(i+1);
E 8
I 8
	return(i);
E 8
}

I 9
/*ARGSUSED*/
E 9
t_charht(n)	/* set character height to n */
int n;
{
D 2
	if(dbg)fprintf(stderr,"can't set height on versatec \n");
E 2
I 2
D 3
	if(dbg)fprintf(stderr,"can't set height on versatec yet\n");
E 3
I 3
#ifdef DEBUGABLE
D 8
	if (dbg)fprintf(stderr,"can't set height on versatec yet\n");
E 8
I 8
	if (dbg) error(!FATAL, "can't set height on versatec");
E 8
#endif
E 3
E 2
}

I 9
/*ARGSUSED*/
E 9
t_slant(n)	/* set slant to n */
int n;
{
D 3
	if(dbg)fprintf(stderr,"can't set slant on versatec yet\n");
E 3
I 3
#ifdef DEBUGABLE
D 8
	if (dbg)fprintf(stderr,"can't set slant on versatec yet\n");
E 8
I 8
	if (dbg) error(!FATAL, "can't set slant on versatec");
E 8
#endif
E 3
}

t_font(s)	/* convert string to internal font number */
char *s;
{
	int n;

	n = atoi(s);
	if (n < 0 || n > nfonts)
		n = 1;
	return(n);
}

t_text(s)	/* print string s as text */
char *s;
{
	int c;
	char str[100];

	if (!output)
		return;
	while (c = *s++) {
		if (c == '\\') {
			switch (c = *s++) {
			case '\\':
			case 'e':
				put1('\\');
				break;
			case '(':
				str[0] = *s++;
				str[1] = *s++;
				str[2] = '\0';
				put1s(str);
				break;
			}
		} else {
			put1(c);
		}
		hmot(lastw);
I 3
#ifdef DEBUGABLE
E 3
		if (dbg) fprintf(stderr,"width = %d\n", lastw);
I 3
#endif
E 3
	}
}

I 8

E 8
t_reset(c)
{	
D 8


E 8
D 4
	if (output)
		paper += vpos;
E 4
D 9
	output = 1;
E 9
	switch(c){
D 9
	case 'p':
D 3
		waitchild();
E 3
D 4
		slop_lines(maxX);
		maxX = 0;
E 4
I 4
D 8
		slop_lines(maxH);
		maxH = 0;
E 4
		buf0p = buffer;
E 8
I 8
		outband(PAGEEND);
E 8
		break;
E 9
	case 's':
D 3
		waitchild();
E 3
D 4
		slop_lines(maxX);
E 4
I 4
D 8
		slop_lines(maxH);
E 4
		t_done();
		break; /* no Return */
E 8
I 8
D 9
		outband(PAGEEND);
/*nov		ioctl(OUTFILE, VSETSTATE, prtmode); */
E 9
I 9
		t_page(0);
#ifdef DRIVER
		ioctl(OUTFILE, VSETSTATE, prtmode);
#endif
E 9
		break;
E 8
	}
}
D 2
t_done(){
E 2

D 2

	/* clean up and get ready to die */
E 2
I 2
D 8
t_done()	/* clean up and get ready to die */
{
I 4
/* noversatec
E 4
E 2
D 3
	waitchild();
E 3
	ioctl(OUTFILE, VSETSTATE, prtmode);
	if (write(OUTFILE, "\f", 2) != 2)
		exit(RESTART);
I 4
noversatec */
E 4
}
E 8

D 8
t_trailer()
E 8
I 8
vgoto (n)
int n;
E 8
{
D 3
	vpos = oldv = 0;
E 3
I 3
D 8
	vpos = 0;
E 3
	vgoto(TRAILER);
D 3
	vpos = oldv = 0;
E 3
I 3
	vpos = 0;
E 8
I 8
	vpos = n;
D 15
	if (vpos > maxv) maxv = vpos;
E 15
E 8
E 3
}

D 8
vgoto(n)
{
D 3
	if(n < 0){
		/* check to see if n would move use past buf0p */
		fprintf(stderr,"ERROR vgoto past the beginning");
		done();			/* no return */
	}
E 3
I 3
			/* check to see if n would move use past buf0p */
    if (n < 0) {
	fprintf (stderr, "ERROR vgoto past the beginning");
	done();
    }
E 3
					/* check for end of page */
D 3
	if(n > RES * 11) n -= RES * 11;	/* wrap around on to the top */
	vpos = n;

E 3
I 3
    if (n > RES * 11) n -= RES * 11;	/* wrap around on to the top */
    vpos = n;
E 3
}
E 8

D 2

E 2
put1s(s)	/* s is a funny char name */
char *s;
{
	int i;

	if (!output)
		return;
I 3
#ifdef DEBUGABLE
E 3
	if (dbg) fprintf(stderr,"%s ", s);
I 3
#endif
E 3
	for (i = 0; i < nchtab; i++)
		if (strcmp(&chname[chtab[i]], s) == 0)
			break;
	if (i < nchtab)
		put1(i + 128);
}

put1(c)	/* output char c */
int c;
{
	char *pw;
	register char *p;
	register int i, k;
	int j, ofont, code;

	if (!output)
		return;
	c -= 32;
	if (c <= 0) {
I 3
#ifdef DEBUGABLE
E 3
		if (dbg) fprintf(stderr,"non-exist 0%o\n", c + 32);
D 3
		lastw = widthtab[font][0] * pstab[size-1] / dev.unitwidth;
E 3
I 3
#endif
D 4
		lastw = widtab[font][0] * pstab[size-1] / dev.unitwidth;
E 4
I 4
D 8
 		lastw = (widtab[font][0] * pstab[size-1] + dev.unitwidth/2)
E 8
I 8
 		lastw = (widtab[font][0] * pstab[size] + dev.unitwidth/2)
E 8
								/ dev.unitwidth;
E 4
E 3
		return;
	}
	k = ofont = font;
	i = fitab[font][c] & BMASK;
D 4
	if (i != 0) {	/* it's on this font */
		p = codetab[font]; /* get the printing value of ch */
D 3
		pw = widthtab[font]; /* get the width */
E 3
I 3
		pw = widtab[font]; /* get the width */
E 4
I 4
	if (i != 0) {			/* it's on this font */
		p = codetab[font];	/* get the printing value of ch */
		pw = widtab[font];	/* get the width */
E 4
E 3
D 9
	} else if (smnt > 0) {		/* on special (we hope) */
		for (k=smnt, j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1)){
E 9
I 9
	} else		/* on another font (we hope) */
D 14
		for (k=font, j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1)){
E 14
I 14
		for (j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1)){
E 14
E 9
D 3
			if(fitab[k] == 0)
E 3
I 3
			if (fitab[k] == 0)
E 3
				continue;
			if ((i = fitab[k][c] & BMASK) != 0) {
				p = codetab[k];
D 3
				pw = widthtab[k];
E 3
I 3
				pw = widtab[k];
E 3
				setfont(k);
				break;
			}
		}
D 9
	}
E 9
I 9

E 9
D 14
	if (i == 0 || (code = p[i] & BMASK) == 0 || k > nfonts) {
E 14
I 14
	if (i == 0) {
E 14
I 3
#ifdef DEBUGABLE
E 3
		if (dbg) fprintf(stderr,"not found 0%o\n", c+32);
I 3
#endif
E 3
		return;
	}
I 14
	code = p[i] & BMASK;
E 14
I 3
#ifdef DEBUGABLE
E 3
	if (dbg) {
		if (isprint(c+32))
			fprintf(stderr,"%c %d\n", c+32, code);
		else
			fprintf(stderr,"%03o %d\n", c+32, code);
D 3
	} else
		outc(code);	/* character is < 254 */
E 3
I 3
	}
#endif
	outc(code);	/* character is < 254 */
E 3
	if (font != ofont)
		setfont(ofont);
D 4
	lastw = pw[i] & 077;
	lastw = (lastw * pstab[size-1] + dev.unitwidth/2) / dev.unitwidth;
E 4
I 4
D 8
	lastw = ((pw[i]&077) * pstab[size-1] + dev.unitwidth/2) / dev.unitwidth;
E 8
I 8
	lastw = ((pw[i]&077) * pstab[size] + dev.unitwidth/2) / dev.unitwidth;
E 8
E 4
}

D 4
/* font position info: */
E 4

D 4
struct {
	char *name;
	int number;
D 3
} fontname[NFONT+1];
E 3
I 3
} fontname[NFONTS+1];
E 4
E 3

D 4

E 4
setsize(n)	/* set point size to n (internal) */
int n;
{

	if (n == size)
		return;	/* already there */
D 3
	if(vloadfont(font,pstab[n-1]) != -1)
E 3
I 3
D 8
	if (vloadfont(font,pstab[n-1]) != -1)
E 8
I 8
	if (vloadfont(font, pstab[n]) != -1)
E 8
E 3
		size = n;
}

I 9
/*ARGSUSED*/
E 9
t_fp(n, s, si)	/* font position n now contains font s, intname si */
D 9
int n;
E 9
I 9
int n;		/* internal name is ignored */
E 9
char *s, *si;
{
D 8
	register	i;
E 8
I 8
	register int i;
E 8

I 8
			/* first convert s to filename if possible */
	for (i = 0; fontmap[i].ffile != (char *) 0; i++) {
#ifdef DEBUGABLE
		if(dbg>1)fprintf(stderr,"testing :%s:%s:\n",s,fontmap[i].fname);
#endif
		if (strcmp(s, fontmap[i].fname) == 0) {
			s = fontmap[i].ffile;
#ifdef DEBUGABLE
			if(dbg)fprintf(stderr, "found :%s:\n",fontmap[i].ffile);
#endif
			break;
		}
	}

E 8
D 9
	fontname[n].name = s;
	fontname[n].number = atoi(si);
D 3
	for(i = 0;i < NFONT;i++)/* free the bits of that font */
		if(fontdes[i].fnum == n){
E 3
I 3
D 8
	for(i = 0;i < NFONTS;i++)/* free the bits of that font */
E 8
I 8
	for(i = 0;i < NFONTS;i++)	/* free the bits of that font */
E 9
I 9
	fontname[n] = s;
	for(i = 0;i <= NFONTS;i++)	/* free the bits of that font */
E 9
E 8
		if (fontdes[i].fnum == n){
E 3
			nfree(fontdes[i].bits);
D 9
			fontdes[i].bits = 0;
E 9
			fontdes[i].fnum = -1;
		}
}

setfont(n)	/* set font to n */
int n;
{
D 3
	if (n < 0 || n > NFONT)
E 3
I 3
D 17
	if (n < 0 || n > NFONTS)
E 17
I 17
	if (n < 0 || n > nfonts)
E 17
E 3
D 8
		error(FATAL, "illegal font %d\n", n);
D 3
	if(vloadfont(n,pstab[size - 1]) != -1)
E 3
I 3
	if (vloadfont(n,pstab[size - 1]) != -1)
E 8
I 8
		error(FATAL, "illegal font %d", n);
	if (vloadfont(n,pstab[size]) != -1)
E 8
E 3
		font = n;
}

I 17
setstip(n)	/* set stipple font to n */
int n;
{
	if (n < 1 || n > nstips)
		error(FATAL, "illegal stipple %d", n);
	stip = n;
}


/*----------------------------------------------------------------------------*
 | Routine:	setfill(stipple_number)
 |
 | Results:	sets the fill-pattern pointers (stip_disp and
 |		stip_bits) for a particular stipple.  Takes stipple
 |		font from current "stip" number.
 *----------------------------------------------------------------------------*/

setfill(number)
int number;
{
	int curfont;		/* places to save current text font */
	int cursize;

					/* set global stipmem for polygon */
	if (number < 0 || number >= DISPATCHSIZE)
		stipmem = 0;
	else
		stipmem = number;

	curfont = cfnum;		/* get pointers to */
	cursize = cpsize;		/* the inuse font */
	if (vloadfont(nfonts + stip, 0)) {
	    stip_disp = (struct dispatch *) NULL;	/* stipple not here */
	} else {
	    if (fontwanted) {
		if (getfont()) {
		    stip_disp = (struct dispatch *) NULL;
		} else {
		    stip_disp = dispatch;	/* save for polygon routine */
		    stip_bits = bits;
		}
	    } else {
		stip_disp = dispatch;	/* save for polygon routine */
		stip_bits = bits;
	    }
	}
	vloadfont(curfont, cursize);
}


E 17
D 2

E 2
vloadfont(fnum, fsize)
register int fnum;
register int fsize;
{
	register int i;

	fontwanted = 0;
	if (fnum == cfnum && fsize == cpsize)
		return(0);
D 2
	for (i = 0; i < NFONTS; i++)
E 2
I 2
D 9
	for (i = 0; i < NFONTS; i++) {
E 9
I 9
	for (i = 0; i <= NFONTS; i++) {
E 9
E 2
		if (fontdes[i].fnum == fnum && fontdes[i].psize == fsize) {
			cfnum = fontdes[i].fnum;
			cpsize = fontdes[i].psize;
			dispatch = &fontdes[i].disp[0];
			bits = fontdes[i].bits;
			cfont = i;
			return (0);
		}
I 2
	}
E 2
		/* this is a new font */
D 4
	if (fnum < 0 || fnum >= MAXF || fontname[fnum].name == 0) {
E 4
I 4
D 9
	if (fnum < 0 || fnum > NFONTS || fontname[fnum].name == 0) {
E 9
I 9
	if (fnum < 0 || fnum > NFONTS || fontname[fnum] == 0) {
E 9
E 4
D 3
		fprintf(stderr,
			"Internal error: illegal font %d name %s size\n",
		fontname[fnum].name,fnum,fsize);
		return(-1);
E 3
I 3
D 8
	    fprintf(stderr, "Internal error: illegal font %d name %s size\n",
			    fontname[fnum].name,fnum,fsize);
E 8
I 8
#ifdef DEBUGABLE
	    if (dbg) error(!FATAL, "illegal font %d size %d", fnum, fsize);
#endif
E 8
	    return(-1);
E 3
	}
D 2
	/* Need to verify the existance of that font/size here*/
E 2
I 2
		/* Need to verify the existance of that font/size here*/
E 2
	nfontnum = fnum;
	npsize = fsize;
	fontwanted++;
	return (0);
}


getfont()
{
D 8
	register int fnum, fsize, fontd;
	int d;
E 8
I 8
	register int fnum;
	register int fsize;
	register int fontd;
	register int d;
D 9
	register int savesize = size;
E 9
I 9
	register int sizehunt = size;
E 9
E 8
	char cbuf[BUFSIZ];

I 8

E 8
D 3
	if (!fontwanted)
		return(0);
E 3
	fnum = nfontnum;
	fsize = npsize;
D 8
	sprintf(cbuf, "/usr/lib/vfont/%s.%d",fontname[fnum].name, fsize);
	fontd = open(cbuf, OPENREAD);
	if (fontd == -1) {
		perror(cbuf);
		error(0,"fnum = %d size = %d name = %s\n",
			fnum,fsize,fontname[fnum]);
		fontwanted = 0;
		return (-1);
E 8
I 8
			/* try to open font file - if unsuccessful, hunt for */
			/* a file of same style, different size to substitute */
	d = -1;	/* direction to look in pstab (smaller first) */
	do {
D 9
	    sprintf(cbuf, "%s/%s.%d", bitdir, fontname[fnum].name, fsize);
E 9
I 9
	    sprintf(cbuf, "%s/%s.%d", bitdir, fontname[fnum], fsize);
E 9
	    fontd = open(cbuf, OPENREAD);
	    if (fontd == -1) {		/* File wasn't found. Try another ps */
D 9
		size += d;
		if (size < 0) {		/* past beginning - look higher */
E 9
I 9
		sizehunt += d;
		if (sizehunt < 0) {	/* past beginning - look higher */
E 9
		    d = 1;
D 9
		    size = savesize + 1;
E 9
I 9
		    sizehunt = size + 1;
E 9
		}
D 9
		if (size > nsizes) {	/* past top - forget it */
E 9
I 9
		if (sizehunt > nsizes) {	/* past top - forget it */
E 9
		    d = 0;
		} else {
D 9
		    fsize = pstab[size];
E 9
I 9
		    fsize = pstab[sizehunt];
E 9
		}
	    }
	} while (fontd == -1 && d != 0);

	if (fontd == -1) {		/* completely unsuccessful */
	    perror(cbuf);
	    error(!FATAL,"fnum = %d, psize = %d, name = %s",
D 9
		fnum, npsize, fontname[fnum].name);
E 9
I 9
		fnum, npsize, fontname[fnum]);
E 9
	    fontwanted = 0;
	    return (-1);
E 8
	}
D 2
	if (read(fontd, &header, sizeof header)!=sizeof header || header.magic!=0436)
E 2
I 2
	if (read(fontd, &header, sizeof  (header)) != sizeof (header)
						|| header.magic != 0436)
E 2
		fprintf(stderr, "%s: Bad font file", cbuf);
	else {
		cfont = relfont();
D 3
		if (((bits=nalloc(header.size+DSIZ+1,1))== NULL)
			&& ((bits=allpanic(header.size+DSIZ+1))== NULL)) {
E 3
I 3
		if ((bits=nalloc(header.size+DSIZ+1,1))== NULL)
			if ((bits=allpanic(header.size+DSIZ+1))== NULL) {
E 3
D 2
				fprintf(stderr, "%s: ran out of memory\n", cbuf);
E 2
I 2
D 9
				fprintf(stderr,"%s: ran out of memory\n", cbuf);
E 2
				exit(ABORT);
E 9
I 9
				error(FATAL, "%s: ran out of memory", cbuf);
E 9
D 3
		} else {
E 3
I 3
			}

E 3
			/*
			 * have allocated one chunk of mem for font, dispatch.
			 * get the dispatch addr, align to word boundary.
			 */
D 3
			d = (int) bits+header.size;
			d += 1;
			d &= ~1;
			if (read(fontd, d, DSIZ)!=DSIZ
D 2
			  || read(fontd, bits, header.size)!=header.size)
E 2
I 2
			  || read(fontd, bits, header.size) != header.size)
E 2
				fprintf(stderr, "bad font header");
			else {
				close(fontd);
				cfnum = fontdes[cfont].fnum = fnum;
				cpsize = fontdes[cfont].psize = fsize;
				fontdes[cfont].bits = bits;
				fontdes[cfont].disp = (struct dispatch *) d;
				dispatch = &fontdes[cfont].disp[0];
				fontwanted = 0;
				return (0);
			}
E 3
I 3

		d = (int) bits+header.size;
		d += 1;
		d &= ~1;
		if (read (fontd, d, DSIZ) != DSIZ
			    || read (fontd, bits, header.size) != header.size)
			fprintf(stderr, "bad font header");
		else {
			close(fontd);
			cfnum = fontdes[cfont].fnum = fnum;
			cpsize = fontdes[cfont].psize = fsize;
			fontdes [cfont].bits = bits;
			fontdes [cfont].disp = (struct dispatch *) d;
			dispatch = &fontdes[cfont].disp[0];
			fontwanted = 0;
			return (0);
E 3
		}
	}
	close(fontd);
	fontwanted = 0;
	return(-1);
}

D 3
int lastloaded	= -1;
E 3
I 3
/*
 * "release" a font position - find an empty one, if possible
 */
E 3

relfont()
{
D 3
	register int newfont;
E 3
I 3
    register int newfont;
E 3

D 3
	newfont = lastloaded;
I 2

E 2
	/*
	 * optimization for special font.  since we think that usually
	 * there is only one character at a time from any special math
	 * font, make it the candidate for removal.
	 */
I 2

E 2
	if (fontdes[newfont].fnum != SPECIALFONT || fontdes[newfont].bits==0)
		if (++newfont>=NFONTS)
			newfont = 0;
	lastloaded = newfont;
D 2
	if(fontdes[newfont].bits!=(char *)-1&&fontdes[newfont].bits!=(char *)0) {
		/* fprintf(stderr, "freeing position %d\n", newfont); */
		nfree(fontdes[newfont].bits);
		fontdes[newfont].bits = (char *)0;
	} else
		/* fprintf(stderr, "taking without freeing position %d\n", newfont); */
		;
E 2
I 2
	if (fontdes [newfont].bits != (char *) -1
			&& fontdes [newfont].bits != (char *) 0) {
		nfree (fontdes [newfont].bits);
		fontdes [newfont].bits = (char *)0;
	     /* fprintf(stderr, "freeing position %d\n", newfont); */
	} /* else
	    fprintf(stderr, "taking without freeing position %d\n", newfont); */
E 2
	fontdes[newfont].bits = 0;
	return (newfont);
E 3
I 3
    for (newfont = 0; newfont < NFONTS; newfont++)
D 9
	if (fontdes [newfont].bits == (char *) -1  ||  !fontdes [newfont].bits)
E 9
I 9
	if (fontdes [newfont].fnum == -1)
E 9
	    break;
D 9
    if (fontdes [newfont].bits != (char *) -1  &&  fontdes [newfont].bits) {
E 9
I 9
    if (fontdes [newfont].fnum != -1) {
E 9
	nfree (fontdes [newfont].bits);
D 9
	fontdes [newfont].bits = (char *)0;
E 9
#ifdef DEBUGABLE
	if (dbg) fprintf (stderr, "freeing position %d\n", newfont);
    } else {
	if (dbg)
	    fprintf (stderr, "taking, not freeing, position %d\n", newfont);
#endif
    }
D 9
    fontdes[newfont].bits = 0;
E 9
I 9
    fontdes[newfont].fnum = -1;
E 9
    return (newfont);
E 3
}

D 2
char *
allpanic(nbytes)
	int nbytes;
E 2
I 2
char *allpanic (nbytes)
int nbytes;
E 2
{
	register int i;

D 9
	for (i = 0; i <= NFONTS; i++)
D 2
		if (fontdes[i].bits != (char *)-1 && fontdes[i].bits != (char *)0)
			nfree(fontdes[i].bits);
E 2
I 2
	    if (fontdes[i].bits != (char *)-1 && fontdes[i].bits != (char *)0)
		nfree(fontdes[i].bits);
E 9
E 2
D 3
	lastloaded = cfont;
E 3
	for (i = 0; i <= NFONTS; i++) {
I 9
		if (fontdes[i].fnum != -1) nfree(fontdes[i].bits);
E 9
		fontdes[i].fnum = fontdes[i].psize = -1;
D 9
		fontdes[i].bits = 0;
E 9
		cfnum = cpsize = -1;
	}
	return(nalloc(nbytes,1));
}

int	M[] = { 0xffffffff, 0xfefefefe, 0xfcfcfcfc, 0xf8f8f8f8,
		0xf0f0f0f0, 0xe0e0e0e0, 0xc0c0c0c0, 0x80808080, 0x0 };
int	N[] = { 0x00000000, 0x01010101, 0x03030303, 0x07070707,
		0x0f0f0f0f, 0x1f1f1f1f, 0x3f3f3f3f, 0x7f7f7f7f, 0xffffffff };
int	strim[] = { 0xffffffff, 0xffffff00, 0xffff0000, 0xff000000, 0 };

outc(code)
D 4
	int code;
E 4
I 4
int code;		/* character to print */
E 4
{
D 4
	char c;				/* character to print */
	register struct dispatch *d;	/* ptr to character font record */
	register char *addr;		/* addr of font data */
	int llen;			/* length of each font line */
	int nlines;			/* number of font lines */
	register char *scanp;		/* ptr to output buffer */
	int scanp_inc;			/* increment to start of next buffer */
	int offset;			/* bit offset to start of font data */
	int i;				/* loop counter */
	register int count;		/* font data ptr */
	register unsigned fontdata;	/* font data temporary */
	register int off8;		/* offset + 8 */
E 4
I 4
    register struct dispatch *dis; /* ptr to character font record */
    register char *addr;	/* addr of font data */
    int llen;			/* length of each font line */
    int nlines;			/* number of font lines */
    register char *scanp;	/* ptr to output buffer */
    int scanp_inc;		/* increment to start of next buffer */
    int offset;			/* bit offset to start of font data */
D 8
    int i;			/* loop counter */
E 8
I 8
    register int i;		/* loop counter */
E 8
    register int count;		/* font data ptr */
    register unsigned fontdata;	/* font data temporary */
D 15
    register int off8;		/* offset + 8 */
E 15
I 15
    register int off8;		/* reverse of offset */
E 15
E 4

D 4
	if (fontwanted)
		getfont();
	c = code;
	d = dispatch+c;
	if (d->nbytes) {
		addr = bits+d->addr;
		llen = (d->left+d->right+7)/8;
		nlines = d->up+d->down;
		i = vpos + d->down;
D 3
		if( i > maxX ) maxX = i; /* for flush */
E 3
I 3
		if ( i > maxX ) maxX = i; /* for flush */
E 3
		scanp= ((vpos-d->up-1)*BYTES_PER_LINE+(hpos-d->left)/8)+buf0p;
		if (scanp < &buffer[0])
			scanp += sizeof buffer;
		scanp_inc = BYTES_PER_LINE-llen;
		offset = -((hpos-d->left)&07);
		off8 = offset+8;
		for (i = 0; i < nlines; i++) {
D 2
			if (scanp >= &buffer[BUFFER_SIZE])
				scanp -= sizeof buffer;
			count = llen;
			if (scanp + count <= &buffer[BUFFER_SIZE])
				do {
					fontdata = *(unsigned *)addr;
					addr += 4;
					if (count < 4)
						fontdata &= ~strim[count];
					*(unsigned *)scanp |= (fontdata << offset) &~ M[off8];
					scanp++;
					*(unsigned *)scanp |= (fontdata << off8) &~ N[off8];
					scanp += 3;
					count -= 4;
				} while (count > 0);
			scanp += scanp_inc+count;
			addr += count;
E 2
I 2
		    if (scanp >= &buffer[BUFFER_SIZE])
			    scanp -= sizeof buffer;
		    count = llen;
		    if (scanp + count <= &buffer[BUFFER_SIZE])
			do {
			    fontdata = *(unsigned *)addr;
			    addr += 4;
			    if (count < 4)
				    fontdata &= ~strim[count];
			    *(unsigned*)scanp |=(fontdata << offset) & ~M[off8];
			    scanp++;
			    *(unsigned*)scanp |=(fontdata << off8) & ~N[off8];
			    scanp += 3;
			    count -= 4;
			} while (count > 0);
		    scanp += scanp_inc+count;
		    addr += count;
E 2
		}
		return;
E 4
I 4
    if (fontwanted)
D 9
	getfont();
E 9
I 9
	if (getfont()) return;
E 9
    dis = dispatch + code;
    if (dis->nbytes) {
I 16
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "char %d at (%d,%d)", code, hpos, vpos);
#endif
E 16
	addr = bits + dis->addr;
	llen = (dis->left + dis->right + 7) / 8;
	nlines = dis->up + dis->down;
D 8
	if ((i = vpos + dis->down) > maxH) maxH = i;	/* remember page len */
	scanp = buf0p + (((vpos - dis->up) - 1) * BYTES_PER_LINE
			+ (hpos - dis->left) / 8);
	if (scanp < &buffer[0])
	    scanp += sizeof buffer;
E 8
I 8
	if ((i = vpos + dis->down) > maxv) maxv = i;
D 9
	scanp = buf0p + (vpos - (vorigin + dis->up + 1)) * BYTES_PER_LINE
E 9
I 9
	scanp = buf0p + (vpos - (vorigin + dis->up)) * BYTES_PER_LINE
E 9
			+ (hpos - dis->left) / 8;
E 8
	scanp_inc = BYTES_PER_LINE - llen;
D 15
	offset = - ((hpos - dis->left) &07);
	off8 = offset + 8;
E 15
I 15
	offset = (hpos - dis->left) &07;
	off8 = 8 - offset;
E 15
	for (i = 0; i < nlines; i++) {
D 8
	    if (scanp >= &buffer[BUFFER_SIZE])
		scanp -= sizeof buffer;
	    count = llen;
	    if (scanp + count <= &buffer[BUFFER_SIZE]) {
E 8
I 8
D 9
	    if (scanp + (count = llen) > BUFBOTTOM) return;
E 9
I 9
D 16
	    if ((unsigned) (scanp + (count = llen)) > (unsigned) BUFBOTTOM)
E 16
I 16
	    if (scanp + (count = llen) > BUFBOTTOM) {
#ifdef DEBUGABLE
		if (dbg) fprintf(stderr, " scrapped\n");
#endif
E 16
		return;
I 16
	    }
#ifdef DEBUGABLE
	    if (dbg) fprintf(stderr, "-");
#endif
E 16
E 9
	    if (scanp >= BUFTOP) {
E 8
		do {
		    fontdata = *(unsigned *)addr;
		    addr += 4;
		    if (count < 4)
			fontdata &= ~strim[count];
D 15
		    *(unsigned*)scanp |=(fontdata << offset) & ~M[off8];
E 15
I 15
		    *(unsigned*)scanp |=(fontdata >> offset) & ~M[off8];
E 15
		    scanp++;
		    *(unsigned*)scanp |=(fontdata << off8) & ~N[off8];
		    scanp += 3;
		    count -= 4;
		} while (count > 0);
	    }
	    scanp += scanp_inc+count;
	    addr += count;
E 4
	}
I 16
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "\n");
#endif
E 16
D 9
	return;
E 9
I 4
    }
D 9
    return;
E 9
E 4
}

D 8
slop_lines(nlines)
int nlines;
E 8

D 8
/* Output "nlines" lines from the buffer, and clear that section of the  */
/* buffer.	*/

{
	unsigned usize;

D 3
	if(!nlines );
/*	rlines = (&buffer[BUFFER_SIZE] - buf0p) / BYTES_PER_LINE; */
E 3
	usize = BYTES_PER_LINE * nlines;
	writev(buf0p,usize);
	vclear(buf0p, usize);
I 4
/* noversatec
E 4
	ioctl(OUTFILE, VSETSTATE, pltmode);
I 4
noversatec */
E 4
}

writev(buf,usize)
E 8
I 8
vwrite(buf,usize)
E 8
char *buf;
D 9
unsigned usize;
E 9
I 9
int usize;
E 9
{
D 3
	register tsize = 0;
	while(usize){
E 3
I 3
	register int tsize = 0;

D 9
	while (usize){
E 9
I 9
	while (usize) {
E 9
E 3
		buf += tsize;
D 3
		if(usize > (unsigned)(1024 * 1024)){
			tsize = 1024 * 1024;
		}else tsize = usize;
		usize -= tsize;
		if(dbg)fprintf(stderr,"buf = %d size = %d\n",buf,tsize);
		
		if (tsize != write(OUTFILE, buf, tsize)) {
E 3
I 3
D 4
		tsize = usize;
E 4
I 4
		tsize = usize > MAXWRIT ? MAXWRIT : usize;
E 4
#ifdef DEBUGABLE
		if (dbg)fprintf(stderr,"buf = %d size = %d\n",buf,tsize);
I 16
	    if (!dbg)
E 16
#endif
		if ((tsize = write(OUTFILE, buf, tsize)) < 0) {
E 3
			perror("dver: write failed");
			exit(RESTART);
		}
I 3
		usize -= tsize;
E 3
	}
}

D 2
vclear(ptr,nbytes)
E 2
I 2
vclear (ptr, nbytes)
E 2
char	*ptr;
D 2
unsigned	nbytes;
E 2
I 2
D 9
unsigned nbytes;
E 9
I 9
int nbytes;
E 9
E 2
{
D 2
	register	tsize = 0;
	while(nbytes){
		if( (unsigned)(16*1024) < nbytes){
			tsize = 16 * 1024;
		}else tsize = nbytes;
		nbytes -= tsize;
		if(dbg)fprintf(stderr,"clearing ptr = %d size = %d\n",ptr,tsize);
		clear(ptr,tsize);
		ptr += tsize;
	}
E 2
I 2
    register tsize = 0;

D 3
    while(nbytes){
E 3
I 3
    while (nbytes){
E 3
	if ((unsigned)(16*1024) < nbytes) {
	    tsize = 16 * 1024;
	} else
	    tsize = nbytes;
	nbytes -= tsize;
I 3
#ifdef DEBUGABLE
E 3
	if (dbg) fprintf(stderr,"clearing ptr = %d size = %d\n",ptr,tsize);
I 3
#endif
E 3
	clear(ptr,tsize);
	ptr += tsize;
    }
E 2
}

/*ARGSUSED*/
clear(lp, nbytes)
D 2
	int *lp;
	int nbytes;
E 2
I 2
D 9
int *lp;
E 9
I 9
char *lp;
E 9
int nbytes;
E 2
{
I 19
#ifdef vax
E 19
D 2

E 2
	asm("movc5 $0,(sp),$0,8(ap),*4(ap)");
I 19
#else
	register int i = nbytes;
	register char *cp = lp;

	while(i-- > 0)
		*(cp++) = 0;
#endif
E 19
D 2

E 2
}

char *
nalloc(i, j)
D 2
	int i, j;
E 2
I 2
int i, j;
E 2
{
	register char *cp;

	cp = calloc(i, j);
D 3
	if(dbg) fprintf(stderr, "allocated %d bytes at %x\n", i * j, cp);
E 3
I 3
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "allocated %d bytes at %x\n", i * j, cp);
#endif
E 3
	return(cp);
}

nfree(cp)
D 2
	char *cp;
E 2
I 2
char *cp;
E 2
{
D 2

E 2
D 3
	if(dbg) fprintf(stderr, "freeing at %x\n", cp);/* DEBUG */
E 3
I 3
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "freeing at %x\n", cp);
#endif
E 3
	free(cp);
}
I 2

D 3
#ifdef ACCOUNT
accounting(){}
#endif
E 3

D 4
/*******************************************************************************

	graphics routines go here

*******************************************************************************/

drawline(){}
drawcirc(){}
drawellip(){}
drawarc(){}
drawwig(){}

E 4
I 4
/*
D 8
 * Points should be in the range 0 <= x < RASTER_LENGTH, 0 <= y < NLINES.
 * The origin is the top left-hand corner with increasing x towards the
 * right and increasing y going down.
 * The output array is NLINES x BYTES_PER_LINE pixels.
E 8
I 8
 * Plot a dot at (x, y).  Points should be in the range 0 <= x < RASTER_LENGTH,
 * vorigin <= y < vorigin + NLINES.  If the point will not fit on the buffer,
 * it is left out.  Things outside the x boundary are wrapped around the end.
E 8
 */
point(x, y)
D 8
register int x, y;
E 8
I 8
D 15
int x, y;
E 15
I 15
register int x;
register int y;
E 15
E 8
{
D 8
    if ((unsigned) x < RASTER_LENGTH && (unsigned) y < NLINES) {
	buffer [y * BYTES_PER_LINE + (x >> 3)] |= 1 << (7 - (x & 07));
    }
E 8
I 8
    register char *ptr = buf0p + (y - vorigin) * BYTES_PER_LINE + (x >> 3);

D 15
    if (ptr <= BUFBOTTOM && ptr >= BUFTOP)	/* ignore it if it wraps over */
	*ptr |= 1 << (7 - (x & 07));
E 15
I 15
    if (ptr > BUFBOTTOM || ptr < BUFTOP)	/* ignore if it's off buffer */
	return;

    *ptr |= 1 << (7 - (x & 07));
    if (y > maxv) maxv = y;
E 15
E 8
}
I 17


#define MAXX	0x7fff		/* largest positive int */
#define MINX	0x8000		/* smallest negative int */
#define MAXVECT	75

typedef struct poly {
	struct poly *next;	/* doublely-linked lists of vectors */
	struct poly *prev;
	int param;	/* bressenham line algorithm parameter */
	short dy;	/* delta-y for calculating line */
	short dx;	/* delta-x for calculating line */
	short currx;	/* current x in this vector */
	short endy;	/* where vector ends */
} polyvector;

int	rp_len;		/* length of the string in "buf" */
char *	rp_ptr;		/* "walking" pointer into buf */


/*----------------------------------------------------------------------------*
 | Routine:	read_poly (input_buffer, file_pointer)
 |
 | Results:	gets an integer from buffer pointed to by rp_ptr,
 |		and advances in the file.  If there is nothing left,
 |		more can be read in from the file.  rp_ptr and rp_len
 |		are set in "polygon".
 *----------------------------------------------------------------------------*/

read_poly(buf, fp)
char *buf;
FILE *fp;
{
	register int i;


	if (*rp_ptr == '\n')
	    return 0;

	while (isspace(*++rp_ptr));	/* skip any leading spaces */
	i = atoi(rp_ptr);		/* convert motion to curve points */
	while (isdigit(*++rp_ptr));	/* skip number*/
					/* if the amount we read wasn't the */
					/*    whole thing, read some more in */
	if (rp_len - (rp_ptr - buf) < 10 && *(buf + rp_len - 1) != '\n') {
	    register char *cop = buf;

	    while (*(cop++) = *(rp_ptr++));	/* what's left to beginning */
	    if (fgets ((cop - 1), rp_len - (cop - buf), fp) == NULL)
		error(FATAL, "unexpected end of input");
	    rp_ptr = buf;
	}

	return i;
}


/*----------------------------------------------------------------------------*
 | Routine:	polygon ( string, file )
 |
 | Results:	draws a polygon specified by the parameters encoded into the
 |		string (and from the file, if necessary).  The parameters are
 |		broken up into separate vectors.  The vectors are encoded as
 |		follows:  (p dx dy curx endy); endy is the bottom of vector,
 |		curx is where x starts;  dx, dy are the deltas for the line;
 |		if dy is negative, p is the Bresenham line algorithm parameter,
 |		otherwise p is the starting y.  All the active vectors must be
 |		put first.
 |
 |		The polygon is filled with a stipple pattern from stip_disp
 |		and stip_bits, which point to the stipple font.  The pattern
 |		is defined by "stip" and "stipmem".
 |
 |		The scan-line algorithm implemented scans from top to
 |		bottom (low y to high y).  It also scans, within a line,
 |		from left to right (low x to high x).
 |
 | Bugs:	stipple pattern MUST be a power of two bytes "wide" and
 |		square.  The square restriction comes from the fact that
 |		the varian and versatec are respectively rotated.
 *----------------------------------------------------------------------------*/

polygon(buf, fp)
char *buf;
FILE *fp;
{
    int nexty;			/* at what y value the next vector starts */
    int maxy, miny;		/* finds bounds of polygon */
    polyvector *activehead;		/* doing fill, is active edge list */
    polyvector *waitinghead;		/* edges waiting to be active */
    register polyvector *vectptr;	/* random vector */
    register int i;			/* random register */

    char *topstipple;		/* points to beginning of stipple glyph */
    char *leftstipple;		/* points to beginning of line of stipple */
    char *leftpage;		/* points to the edge of a raster line */
    int bytewidth;		/* glyph width in bytes */
    int mask;			/* mask to pick off pixel index into stipple */
    int bytemask;		/* mask to pick off byte index into stipple */


    rp_len = strlen(buf);	/* length of the string in "buf" */
    rp_ptr = buf;		/* "walking" pointer into buf */
						/* if no stipple, don't fill */
    if (stip_disp == (struct dispatch *) NULL || stip_bits == (char *) NULL)
	goto leavepoly;

    stip_disp += stipmem;			/* set up parameters for */
    if (!stip_disp->nbytes) {			/* tiling with the stipple */
#ifdef DEBUGABLE
	error(!FATAL, "member not found: member %d, stipple %d", stipmem, stip);
#endif
	goto leavepoly;
    }
    topstipple = stip_bits + stip_disp->addr;
    bytewidth = stip_disp->up + stip_disp->down;
    for (i = 1 << 30; i && i != bytewidth; i = i >> 1)
	;
    if (i==0 || bytewidth<8 || bytewidth != stip_disp->right+stip_disp->left) {
	error(!FATAL, "invalid stipple: number %d, member %d", stip, stipmem);
	goto leavepoly;
    }
    mask = bytewidth - 1;
    bytewidth = bytewidth >> 3;
    bytemask = bytewidth - 1;

    if ((i = read_poly(buf, fp)) < 2)	/* # of vects command holds */
	goto leavepoly;
    miny = read_poly(buf, fp);		/* get limits from command */
    maxy = read_poly(buf, fp);

    leftstipple = topstipple + (miny & mask) * bytewidth;
    leftpage = buf0p + (miny - vorigin) * BYTES_PER_LINE;

				/* allocate space for raster-fill algorithm*/
    vectptr = (polyvector *) nalloc(sizeof(polyvector), i + 4);
    if (vectptr == (polyvector *) NULL) {
	error(!FATAL, "unable to allocate space for polygon");
	return;
    }

    waitinghead = vectptr;
    vectptr->param = miny - 1;		/* put dummy entry at start */
    (vectptr++)->prev = NULL;
    waitinghead->next = vectptr;
    vectptr->prev = waitinghead;

    while (i--) {
	vectptr->next = vectptr + 1;
	vectptr->param = read_poly(buf, fp);
	vectptr->dx = read_poly(buf,fp);
	vectptr->dy = read_poly(buf,fp);
	vectptr->currx = read_poly(buf,fp);
	(vectptr++)->endy = read_poly(buf,fp);
	vectptr->prev = vectptr - 1;
    }

    vectptr->param = maxy + 1;		/* dummy entry at end, too */
    vectptr->currx = vectptr->dx = vectptr->dy = 0;
    vectptr->next = NULL;

    activehead = ++vectptr;		/* two dummy entries for active list */
    vectptr->currx = MINX;		/* head */
    vectptr->endy = maxy + 1;
    vectptr->param = vectptr->dx = vectptr->dy = 0;
    activehead->next = ++vectptr;
    activehead->prev = vectptr;
    vectptr->prev = activehead;		/* tail */
    vectptr->next = activehead;
    vectptr->currx = MAXX;
    vectptr->endy = maxy + 1;
    vectptr->param = vectptr->dx = vectptr->dy = 0;

    vectptr = waitinghead->next;	/* if anything is active already */
    if (vectptr->dy < 0) {		/*   put them into the active list */
	register polyvector *p;		/* random useful register pointer */

	p = vectptr;
	do {
	    vectptr->dy = -vectptr->dy;
	} while ((++vectptr)->dy < 0);

	waitinghead->next = vectptr;	/* first, remove list from waiting */
	(vectptr--)->prev = waitinghead;

	activehead->next->prev = vectptr;	/* link in end */
	vectptr->next = activehead->next;
	activehead->next = p;			/* link in start */
	p->prev = activehead;
    }

			/* main loop -- gets vectors off the waiting list, */
			/* then displays spans while updating the vectors in */
			/* the active list */
    while (miny <= maxy) {
	i = maxy + 1;		/* this is the NEXT time to get a new vector */
	for (vectptr = waitinghead->next; vectptr != NULL; ) {
	    if (miny == vectptr->param) {
				/* the entry in waiting list (vectptr) is */
				/*   ready to go into active list.  Need to */
				/*   convert some vector stuff and sort the */
				/*   entry into the list. */
		register polyvector *p;	/* random vector pointers */
		register polyvector *v;

							/* convert this */
		if (vectptr->dx < 0)			/* entry to active */
		    vectptr->param = -((vectptr->dx >> 1) + (vectptr->dy >> 1));
		else
		    vectptr->param = (vectptr->dx >> 1) - (vectptr->dy >> 1);

		p = vectptr;			/* remove from the */
		vectptr = vectptr->next;	/* waiting list */
		vectptr->prev = p->prev;
		p->prev->next = vectptr;
						/* find where it goes */
						/* in the active list */
						/* (sorted smallest first) */
		for (v = activehead->next; v->currx < p->currx; v = v->next)
		    ;
		p->next = v;		/* insert into active list */
		p->prev = v->prev;	/* before the one it stopped on */
		v->prev = p;
		p->prev->next = p;
	    } else {
		if (i > vectptr->param) {
		    i = vectptr->param;
		}
		vectptr = vectptr->next;
	    }
	}
	nexty = i;

					/* print the polygon while there */
					/* are no more vectors to add */
	while (miny < nexty) {
					/* remove any finished vectors */
	    vectptr = activehead->next;
	    do {
		if (vectptr->endy <= miny) {
		    vectptr->prev->next = vectptr->next;
		    vectptr->next->prev = vectptr->prev;
		}
	    } while ((vectptr = vectptr->next) != activehead);

					/* draw the span */
	    vectptr = activehead->next;
	    while (vectptr->next != activehead) {
		register int start;	/* get the beginning */
		register int length;	/*   and the end of span */
		register char *glyph;
		register char *raster;

		start = vectptr->currx;
		vectptr = vectptr->next;
		length = vectptr->currx + 1;
		vectptr = vectptr->next;

					/* bound the polygon to the page */
		if (start >= RASTER_LENGTH)
		    break;
		if (start < 0) start = 0;
		if (length > RASTER_LENGTH) length = RASTER_LENGTH;
		length -= start;		/* length is in pixels */

		i = start & 7;
		start = start >> 3;		/* start is in bytes */
		raster = leftpage + start;
		glyph = leftstipple + (start & bytemask);

		if (i) {			/* do any piece of byte */
		    register char data;		/* that hangs on the front */

		    data = (*(glyph++)) & (0x7f >> --i);
		    length -= 7 - i;
		    if (length < 0) {		/* less than one byte wide? */
			data &= 0xff << -length;
			length = 0;	/* force clean stoppage */
		    }
		    *(raster++) |= data;
					/* update glyph ptr after first byte */
		    if (!(++start & bytemask))
			glyph = leftstipple;
		}
						/* fill the line of raster */
		while ((length -= 8) >= 0) {
		    *(raster++) |= *(glyph++);
		    if (!(++start & bytemask))
			glyph = leftstipple;
		}
		if (length & 7) {	/* add any part hanging off the end */
		    *raster |= (*glyph) & (0xff << -length);
		}
	    }

#ifdef DEBUGABLE
	    if (dbg) {
		vectptr = activehead;
		do {
		    fprintf (stderr, "%d ", vectptr->currx);
		    vectptr = vectptr->next;
		} while (vectptr != activehead);
	    }
#endif
					/* update the vectors */
	    vectptr = activehead->next;
	    do {
		if (vectptr->dx > 0) {
		    while (vectptr->param >= 0) {
			vectptr->param -= vectptr->dy;
			vectptr->currx++;
		    }
		    vectptr->param += vectptr->dx;
		} else if (vectptr->dx < 0) {
		    while (vectptr->param >= 0) {
			vectptr->param -= vectptr->dy;
			vectptr->currx--;
		    }
		    vectptr->param -= vectptr->dx;
		}
					/* must sort the vectors if updates */
					/* caused them to cross */
					/* also move to next vector here */
		if (vectptr->currx < vectptr->prev->currx) {
		    register polyvector *v;		/* vector to move */
		    register polyvector *p;	/* vector to put it after */

		    v = vectptr;
		    p = v->prev;
		    while (v->currx < p->currx)	/* find the */
			p = p->prev;		/* right vector */

		    vectptr = vectptr->next;	/* remove from spot */
		    vectptr->prev = v->prev;
		    v->prev->next = vectptr;

		    v->prev = p;		/* put in new spot */
		    v->next = p->next;
		    p->next = v;
		    v->next->prev = v;
		} else {
		    vectptr = vectptr->next;
		}
	    } while (vectptr != activehead);
#ifdef DEBUGABLE
	    if (dbg) fprintf(stderr, "line done\n");
#endif

	    if (++miny & mask) {
		leftstipple += bytewidth;
	    } else {
		leftstipple = topstipple;
	    }
	    leftpage += BYTES_PER_LINE;
	} /* while (miny < nexty) */
    } /* while (miny <= maxy) */

    nfree(waitinghead);		/* dump the space allocated for polygon */

leavepoly:
    while (*rp_ptr != '\n')
	i = read_poly(buf, fp);
}  /* polygon function */
E 17
E 4
E 2
E 1
