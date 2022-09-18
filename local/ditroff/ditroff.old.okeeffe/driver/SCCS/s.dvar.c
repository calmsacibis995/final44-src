h32989
s 00008/00000/01718
d D 1.15 85/08/05 12:37:26 slatteng 16 15
c take out vax dependency in clearing bytes (still dependent on byt-swapping)
e
s 00002/00000/01716
d D 1.14 85/04/29 14:06:09 slatteng 15 14
c made vfont directory setable in the makefile
e
s 00002/00003/01714
d D 1.13 84/09/28 16:41:47 slatteng 14 13
c fix core dump on using stipples First thing.
e
s 00417/00005/01300
d D 1.12 84/05/24 17:02:12 slatteng 13 11
c added polygons with stipples to varian/versatec drivers and sorter
e
s 00418/00006/01299
d R 1.12 84/05/24 16:57:40 slatteng 12 11
c added polygons with stipples to varian/versatec drivers and sorter
e
s 00006/00006/01299
d D 1.11 84/03/14 17:56:59 slatteng 11 10
c cleaned up input (testing for EOF)
e
s 00010/00005/01295
d D 1.10 84/02/27 18:02:41 slatteng 10 9
c fixed pointer compile warning message, and fixed messup with glyphs in pos 0
e
s 00002/00000/01298
d D 1.9 83/12/18 15:22:43 slatteng 9 8
c make font directory moveable
e
s 00026/00007/01272
d D 1.8 83/11/30 11:44:09 slatteng 8 7
c add program stop on "stop" command, added capability of swapping fonts
e
s 00057/00049/01222
d D 1.7 83/10/22 16:10:52 slatteng 7 6
c install double-buffering with simultaneous fill & empty 
c devvar -> devva;  font position marked by fnum, not fbits
e
s 00041/00045/01230
d D 1.6 83/10/06 11:00:44 slatteng 6 5
c fix point size search bug, remove special font number and search
c algorithm, remove internal font "name", put options as #defines
e
s 00034/00016/01241
d D 1.5 83/08/23 15:38:28 slatteng 5 4
c use new option operand grabber
e
s 00146/00078/01111
d D 1.4 83/08/12 13:36:35 slatteng 4 3
c added more fonts, put in fontmap to convert troff font names to filenames
c added feature to search for different point sizes, and changed internal usage
c of point size table index "size" for actual, not one more.
e
s 00060/00060/01129
d D 1.3 83/07/29 16:56:11 slatteng 3 2
c works for producing raster output
e
s 00024/00014/01165
d D 1.2 83/07/09 21:45:53 slatteng 2 1
c added three new graphics functions: g, s, t
e
s 01179/00000/00000
d D 1.1 83/07/08 14:49:02 slatteng 1 0
c date and time created 83/07/08 14:49:02 by slatteng
e
u
U
t
T
I 1
/*	%M%	%I%	%E%
 *
 * Varian driver for the new troff
 *
 * Authors:	BWK(BELL)
 *		VCAT(berkley)
 *		Richard L. Hyde, Perdue University
D 4
 *		and David Slattengren, Berkeley
E 4
I 4
 *		and David Slattengren, U.C. Berkeley
E 4
 */

 
/*******************************************************************************

    output language from troff:
    all numbers are character strings

#..\n	comment
sn	size in points
fn	font as number from 1 to n
I 13
in	stipple `font' as number from 1 to n
E 13
cx	ascii character x
Cxyz	funny char \(xyz. terminated by white space
Hn	go to absolute horizontal position n
Vn	go to absolute vertical position n (down is positive)
hn	go n units horizontally (relative)
vn	ditto vertically
nnc	move right nn, then print c (exactly 2 digits!)
		(this wart is an optimization that shrinks output file size
		 about 35% and run-time about 15% while preserving ascii-ness)
p	new page begins -- set v to 0
nb a	end of line (information only -- no action needed)
	b = space before line, a = after
w	paddable word space -- no action needed

Dt ..\n	draw operation 't':
I 13
	Dt d		set line thickness to d
	Ds d		set line style (mask) to d
E 13
	Dl x y		line from here by x,y
	Dc d		circle of diameter d with left side here
	De x y		ellipse of axes x,y with left side here
	Da x y r	arc counter-clockwise by x,y of radius r
	D~ x y x y ...	B-spline curve by x,y then x,y ...
I 13
	Dg x y x y ...	gremlin spline curve by x,y then x,y ...
	Dp s x y ...	polygon by x,y then ... filled with stipple s
E 13

x ..\n	device control functions:
     x i	init
     x T s	name of device is s
     x r n h v	resolution is n/inch h = min horizontal motion, v = min vert
     x p	pause (can restart)
     x s	stop -- done for ever
     x t	generate trailer
     x f n s	font position n contains font s
     x H n	set character height to n
     x S n	set slant to N

	Subcommands like "i" are often spelled out like "init".

*******************************************************************************/


#include <stdio.h>
#include <ctype.h>
#include <sys/vcmd.h>
#include "dev.h"


D 6
#define DEBUGABLE		/* Yes, debugable... */
E 6
I 6
/* #define DEBUGABLE		/* No, not debugable... */
#define DRIVER  		/* Yes, we're driving directly */
/* #define FULLPAGE		/* No, don't output full pages */
E 6
D 4
#define	NFONTS	25		/* total number of fonts useable */
E 4
I 4
D 13
#define	NFONTS	60		/* total number of fonts useable */
E 13
I 13
#define	NFONTS	65		/* total number of fonts useable */
E 13
E 4
#define	MAXSTATE 6		/* number of environments rememberable */
#define OPENREAD 0		/* mode for openning files */
#define RESTART	1		/* upon exit, return either RESTART */
#define ABORT	2		/*     or ABORT */
#define	FATAL	1		/* type of error */
#define	BMASK	0377		/* byte grabber */
I 9
#ifndef FONTDIR
E 9
D 4
#define FONTDIR	"/usr/lib/font"	/* default place to look for fonts */
E 4
I 4
#define FONTDIR	"/usr/lib/font"	/* default place to find font descriptions */
I 9
#endif
I 15
#ifndef BITDIR
E 15
E 9
#define BITDIR "/usr/lib/vfont" /* default place to look for font rasters */
I 15
#endif
E 15
E 4
#define MAXWRIT 4096		/* max characters allowed to write at once */

D 3
#define  hmot(n)	hpos += n
#define  hgoto(n)	hpos = n
E 3
I 3
#define  hmot(n)	hgoto(hpos + n)
E 3
#define  vmot(n)	vgoto(vpos + n)


char	SccsId[]= "%M%	%I%	%E%";

int	output	= 0;	/* do we do output at all? */
int	nolist	= 0;	/* output page list if > 0 */
int	olist[20];	/* pairs of page numbers */
int	spage	= 9999;	/* stop every spage pages */
int	scount	= 0;
struct	dev	dev;
struct	font	*fontbase[NFONTS+1];
D 4
short	*pstab;		/* point size table pointer */
int	res;		/* input was computed according to this resolution */
E 4
I 4
short *	pstab;		/* point size table pointer */
E 4
int	nsizes;		/* number of sizes device is capable of printing */
int	nfonts;		/* number of fonts device is capable of printing */
I 13
int	nstips;		/* number of stipple fonts device can print */
E 13
D 6
int	smnt;		/* index of first special font */
E 6
int	nchtab;
D 4
char	*chname;
short	*chtab;
char	*fitab[NFONTS+1];
char	*widtab[NFONTS+1];
char	*codetab[NFONTS+1];	/* device codes */
char	*fontdir = FONTDIR;
E 4
I 4
char *	chname;
short *	chtab;
char *	fitab[NFONTS+1];	/* font inclusion table - maps ascii to ch # */
char *	widtab[NFONTS+1];	/* width table for each font */
char *	codetab[NFONTS+1];	/* device codes */
char *	fontdir = FONTDIR;	/* place to find devxxx directories */
char *	bitdir = BITDIR;	/* place to find raster fonts and fontmap */
D 6


E 6
I 6
char *	fontname[NFONTS+1];	/* table of what font is on what position */
E 6
E 4
struct {			/* table of what font */
D 6
	char *name;		/*   name is on what */
	int number;		/*   position in font tables */
} fontname[NFONTS+1];
I 4
struct {			/* table of what font */
E 6
	char fname[3];		/*   name maps to what */
	char *ffile;		/*   filename in bitdirectory */
} fontmap[NFONTS+1];
E 4

I 4

E 4
#ifdef DEBUGABLE
int	dbg	= 0;
#endif
D 3
int	maxH;		/* farthest down we've been on the current page */
E 3
D 4
int	size	= -1;	/* current point size being use */
E 4
I 4
int	size	= -1;	/* current point size (internal pstable index) */
E 4
int	font	= -1;	/* current font - not using any to start with */
I 13
int	stip	= -1;	/* current stipple font - not using any to start with */
int	stipmem	= 0;	/* current member to use from stipple font */
E 13
int	hpos;		/* horizontal position we are to be at next; left = 0 */
int	vpos;		/* current vertical position (down positive) */
D 3
int	horig;		/* h origin of current block (just a marker) */
int	vorig;		/* v origin of current block (just a marker) */
E 3
I 3
D 4
extern	linethickness;	/* thickness, in pixels, of any drawn object */
E 4
I 4
extern	linethickness;	/* thickness (in pixels) of any drawn object */
E 4
extern	linmod;		/* line style (a bit mask - dotted, etc.) of objects */
E 3
int	lastw;		/* width of last character printed */


#define DISPATCHSIZE	256		/* must be a power of two */
#define CHARMASK	(DISPATCHSIZE-1)
#define DSIZ		((sizeof *dispatch)*DISPATCHSIZE)
#define OUTFILE 	fileno (stdout)
D 4
#define	RES		200		/* resolution of the device */
D 3
#define	TRAILER		(10 * RES)	/* position of trailer */
E 3
I 3
#define	TRAILER		(10*RES+RES/2)	/* position of trailer */
E 4
I 4
#define	RES		200		/* resolution of the device (dots/in) */
E 4
E 3

D 2
#define RASTER_LENGTH	2048			/* device line length */
E 2
I 2
#define RASTER_LENGTH	2112			/* device line length */
E 2
#define BYTES_PER_LINE	(RASTER_LENGTH/8)
D 2
#define NLINES		(11 * RES)		/* 11" long paper */
E 2
I 2
D 3
#define NLINES		1600			/* device page width */
E 3
I 3
D 6
#define NLINES		1700			/* page width, 8.5 inches */
E 6
I 6
#ifndef FULLPAGE
#	define NLINES	1600			/* page width, 8 inches */
#endif
#ifdef FULLPAGE
#	define NLINES	1700			/* page width, 8.5 inches */
#endif
E 6
E 3
E 2
#define BUFFER_SIZE	(NLINES*BYTES_PER_LINE)	/* number of chars in picture */


int	pltmode[] = { VPLOT };
int	prtmode[] = { VPRINT };
D 7
char	buffer[BUFFER_SIZE];	/* Big line buffers  */
D 4
char	*buf0p = &buffer[0];	/* Zero origin in circular buffer  */
E 4
I 4
char *	buf0p = &buffer[0];	/* Zero origin in circular buffer  */
E 7
I 7
char	buffer1[BUFFER_SIZE];	/* Big line buffers  */
char	buffer2[BUFFER_SIZE];
char *	fill = &buffer1[0];	/* Zero origin in filling buffer */
char *	empty = &buffer2[0];	/* Zero origin in emptying buffer */
char *	elevel = &buffer2[0];	/* current position in emptying buffer */
int	emptypos = NLINES;	/* amount of emptying done (initially "done") */
E 7
E 4

I 7

E 7
D 4
char	*calloc();
char	*nalloc();
char	*allpanic();
E 4
I 4
char *	calloc();
char *	nalloc();
char *	allpanic();
I 5
char *	operand();
E 5
E 4

struct header {
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
D 7
	int	fnum;
E 7
I 7
	int	fnum;		/* if == -1, then this position is empty */
E 7
	int	psize;
	struct	dispatch *disp;
	char	*bits;
D 7
} fontdes[NFONTS] = {
	-1,
	-1
};
E 7
I 7
} fontdes[NFONTS+1];		/* initialized at program start */
E 7

struct dispatch *dispatch;
I 13
struct dispatch *stip_disp;
E 13
int	cfnum = -1;
int	cpsize = 10;
int	cfont = 1;
char	*bits;
I 13
char	*stip_bits;
int	bordered = 1;		/* flag:  "do polygons get bordered?" */
E 13
int	fontwanted = 1;		/* flag:  "has a new font been requested?" */
int	nfontnum = -1;
int	npsize = 10;

 

main(argc, argv)
char *argv[];
{
D 7
	FILE *fp;
E 7
I 7
	register FILE *fp;
	register int i;
E 7
D 3
	int done();
E 3

I 7
	for (i = 0; i <= NFONTS; fontdes[i++].fnum = -1);
E 7
D 5
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
E 5
I 5
	while (--argc > 0 && **++argv == '-') {
		switch ((*argv)[1]) {
E 5
D 4
		case 'f':
E 4
		case 'F':
I 4
D 5
			bitdir = argv[2];
			argv++;
			argc--;
E 5
I 5
D 6
			bitdir = operand(&argc, &argv));
E 6
I 6
			bitdir = operand(&argc, &argv);
E 6
E 5
			break;
		case 'f':
E 4
D 5
			fontdir = argv[2];
			argv++;
			argc--;
E 5
I 5
D 6
			fontdir = operand(&argc, &argv));
E 6
I 6
			fontdir = operand(&argc, &argv);
E 6
E 5
			break;
		case 'o':
D 5
			outlist(&argv[1][2]);
E 5
I 5
			outlist(operand(&argc, &argv));
E 5
			break;
#ifdef DEBUGABLE
		case 'd':
D 5
			dbg = atoi(&argv[1][2]);
E 5
I 5
			dbg = atoi(operand(&argc, &argv));
E 5
			if (dbg == 0) dbg = 1;
			break;
#endif
		case 's':
D 5
			spage = atoi(&argv[1][2]);
E 5
I 5
			spage = atoi(operand(&argc, &argv));
E 5
			if (spage <= 0)
				spage = 9999;
			break;
		}
D 5
		argc--;
		argv++;
E 5
	}

D 6
/* noversatec
E 6
I 6
#ifdef DRIVER
E 6
	ioctl(OUTFILE, VSETSTATE, pltmode);
D 6
noversatec */
E 6
I 6
#endif
E 6

D 5
	if (argc <= 1)
E 5
I 5
	if (argc < 1)
E 5
		conv(stdin);
	else
D 5
		while (--argc > 0) {
			if (strcmp(*++argv, "-") == 0)
E 5
I 5
		while (argc--) {
			if (strcmp(*argv, "-") == 0)
E 5
				fp = stdin;
			else if ((fp = fopen(*argv, "r")) == NULL)
				error(FATAL, "can't open %s", *argv);
			conv(fp);
			fclose(fp);
I 5
			argv++;
E 5
		}
D 3
	done();
E 3
	exit(0);
}
I 5


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
	if ((--*argcp) <= 0)			/* no operand */
	    error (FATAL, "command-line option operand missing.\n");
	return(*(++(*argvp)));			/* operand next word */
}

E 5

outlist(s)	/* process list of page numbers to be printed */
char *s;
{
	int n1, n2, i;

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
#ifdef DEBUGABLE
	if (dbg)
		for (i=0; i<nolist; i += 2)
			fprintf(stderr,"%3d %3d\n", olist[i], olist[i+1]);
#endif
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
		case ' ':
		case 0:		/* occasional noise creeps in */
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
			fgets(buf, sizeof(buf), fp);
			t_text(buf);
			break;
		case 'D':	/* draw function */
D 11
			fgets(buf, sizeof(buf), fp);
E 11
I 11
			if (fgets(buf, sizeof(buf), fp) == NULL)
			    error(FATAL, "unexpected end of input");;
E 11
			switch (buf[0]) {
			case 'l':	/* draw a line */
			    sscanf(buf+1, "%d %d", &n, &m);
			    drawline(n, m);
			    break;
			case 'c':	/* circle */
			    sscanf(buf+1, "%d", &n);
			    drawcirc(n);
			    break;
			case 'e':	/* ellipse */
			    sscanf(buf+1, "%d %d", &m, &n);
			    drawellip(m, n);
			    break;
			case 'a':	/* arc */
			    sscanf(buf+1, "%d %d %d %d", &n, &m, &n1, &m1);
			    drawarc(n, m, n1, m1);
			    break;
I 13
			case 'P':	/* unbordered polygon */
			    bordered = 0;		/* unset border flag */
			case 'p':	/* polygon */
			    sscanf(buf+1, "%d", &m);	/* get stipple */
			    n = 1;			/* number first */
			    while (buf[++n] == ' ');
			    while (isdigit(buf[++n]));
			    setfill(m);			/* set up stipple */
			    drawwig(buf+n, fp, -1);	/* draw polygon */
			    bordered = 1;		/* ALWAYS set after */
			    break;
E 13
			case '~':	/* wiggly line */
I 13
			    drawwig(buf+1, fp, 1);
			    break;
E 13
D 2
			    drawwig(buf+1, fp);
E 2
I 2
			case 'g':	/* gremlin spline */
D 13
			    drawwig(buf+1, fp, buf[0] == '~');
E 13
I 13
			    drawwig(buf+1, fp, 0);
E 13
E 2
			    break;
I 2
			case 't':	/* line thickness */
			    sscanf(buf+1, "%d", &n);
			    drawthick(n);
			    break;
			case 's':	/* line style */
			    sscanf(buf+1, "%d", &n);
			    drawstyle(n);
			    break;
E 2
			default:
D 3
			    error(FATAL, "unknown drawing function %s\n", buf);
E 3
I 3
			    error(FATAL, "unknown drawing function %s", buf);
E 3
			    break;
			}
			break;
		case 's':
			fscanf(fp, "%d", &n);	/* ignore fractional sizes */
			setsize(t_size(n));
			break;
		case 'f':
			fscanf(fp, "%s", str);
			setfont(t_font(str));
			break;
I 13
		case 'i':
			fscanf(fp, "%d", &n);
			setstip(n);
			break;
E 13
		case 'H':	/* absolute horizontal motion */
			/* fscanf(fp, "%d", &n); */
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
		case 'p':	/* new page */
			fscanf(fp, "%d", &n);
			t_page(n);
			break;
		case 'n':	/* end of line */
D 11
			while (getc(fp) != '\n')
				;
E 11
			t_newline();
D 11
			break;
E 11
I 11

E 11
		case '#':	/* comment */
D 11
			while (getc(fp) != '\n')
				;
E 11
I 11
			do
				c = getc(fp);
			while (c != '\n' && c != EOF);
E 11
			break;
		case 'x':	/* device control */
D 8
			devcntrl(fp);
E 8
I 8
			if (devcntrl(fp)) return;
E 8
			break;
		default:
D 3
			error(!FATAL, "unknown input character %o %c\n", c, c);
			done();
E 3
I 3
			error(FATAL, "unknown input character %o %c", c, c);
E 3
		}
I 7
		if (emptypos < NLINES) {	/* for each input operation */
			slop_lines(1);		/* put out an output line */
#ifdef DRIVER
			if (emptypos == NLINES) {
				ioctl(OUTFILE, VSETSTATE, prtmode);
				if (write(OUTFILE, "\f", 2) != 2)
					exit(RESTART);
				ioctl(OUTFILE, VSETSTATE, pltmode);
			}
#endif
		}
E 7
	}
}

D 8
devcntrl(fp)	/* interpret device control functions */
FILE *fp;
E 8
I 8
int devcntrl(fp)	/* interpret device control functions */
FILE *fp;		/* returns -1 upon "stop" command */
E 8
{
        char str[20], str1[50], buf[50];
	int c, n;

	fscanf(fp, "%s", str);
	switch (str[0]) {	/* crude for now */
	case 'i':	/* initialize */
		fileinit();
		t_init();
		break;
	case 't':	/* trailer */
D 4
		t_trailer();
E 4
		break;
	case 'p':	/* pause -- can restart */
		t_reset('p');
		break;
	case 's':	/* stop */
		t_reset('s');
D 8
		break;
E 8
I 8
		return -1;
E 8
	case 'r':	/* resolution assumed when prepared */
D 4
		fscanf(fp, "%d", &res);
E 4
I 4
		fscanf(fp, "%d", &n);
D 13
		if (n!=RES) error(FATAL,"Input computed with wrong resolution");
E 13
I 13
		if (n!=RES) error(FATAL,"Input computed for wrong printer");
E 13
E 4
		break;
	case 'f':	/* font used */
		fscanf(fp, "%d %s", &n, str);
		fgets(buf, sizeof buf, fp);	/* in case there's a filename */
		ungetc('\n', fp);		/* fgets goes too far */
		str1[0] = 0;			/* in case nothing comes in */
		sscanf(buf, "%s", str1);
		loadfont(n, str, str1);
		break;
						/* these don't belong here... */
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
D 8
			break;
E 8
I 8
			return -1;
	return 0;
E 8
}

/* fileinit:	read in font and code files, etc.
		Must open table for device, read in resolution,
D 4
		size info, font info, etc. and set params
E 4
I 4
		size info, font info, etc. and set params.
		Also read in font name mapping.
E 4
*/
I 4

E 4
fileinit()
{
D 4
	int i, fin, nw;
	char	*filebase, *p;
	char	temp[60];
E 4
I 4
	register int i;
	register int fin;
	register int nw;
	register char *filebase;
	register char *p;
	register FILE *fp;
	char	temp[100];
E 4

I 4
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

E 4
D 3
	sprintf(temp, "%s/devver/DESC.out", fontdir);
E 3
I 3
D 7
	sprintf(temp, "%s/devvar/DESC.out", fontdir);
E 7
I 7
	sprintf(temp, "%s/devva/DESC.out", fontdir);
E 7
E 3
	if ((fin = open(temp, 0)) < 0)
D 3
		error(FATAL, "can't open tables for %s\n", temp);
E 3
I 3
		error(FATAL, "can't open tables for %s", temp);
E 3
	read(fin, &dev, sizeof(struct dev));
	nfonts = dev.nfonts;
I 13
	nstips = dev.nstips;
E 13
	nsizes = dev.nsizes;
	nchtab = dev.nchtab;
D 4
	filebase = calloc(1,dev.filesize);	/* enough room for whole file */
E 4
I 4
	filebase = calloc(1, dev.filesize);	/* enough room for whole file */
E 4
	read(fin, filebase, dev.filesize);	/* all at once */
	pstab = (short *) filebase;
	chtab = pstab + nsizes + 1;
	chname = (char *) (chtab + dev.nchtab);
	p = chname + dev.lchname;
	for (i = 1; i <= nfonts; i++) {
		fontbase[i] = (struct font *) p;
		nw = *p & BMASK;		/* 1st thing is width count */
D 6
		if (smnt == 0 && fontbase[i]->specfont == 1)
			smnt = i;		/* first special font */
		p += sizeof(struct font);	/* that is on the beginning */
E 6
I 6
		p += sizeof(struct font);
E 6
		widtab[i] = p;
		codetab[i] = p + 2 * nw;
		fitab[i] = p + 3 * nw;
		p += 3 * nw + dev.nchtab + 128 - 32;
		t_fp(i, fontbase[i]->namefont, fontbase[i]->intname);
#ifdef DEBUGABLE
		if (dbg > 1) fontprint(i);
#endif
	}
I 13
	for (i = 1; i <= nstips; i++) {		/* add in stipple "filenames" */
		if (nfonts + i <= NFONTS)
			t_fp(nfonts + i, p, (char *)0);
		p += strlen(p) + 1;
	}
E 13
	fontbase[0] = (struct font *)
		calloc(1,3*255 + dev.nchtab + (128-32) + sizeof (struct font));
	widtab[0] = (char *) fontbase[0] + sizeof (struct font);
	fontbase[0]->nwfont = 255;
	close(fin);
I 4

E 4
}

I 4

I 10
#ifdef DEBUGABLE
E 10
E 4
fontprint(i)	/* debugging print of font i (0,...) */
{
	int j, n;
	char *p;

	fprintf(stderr,"font %d:\n", i);
	p = (char *) fontbase[i];
	n = fontbase[i]->nwfont & BMASK;
	fprintf(stderr,
	    "base=0%o, nchars=%d, spec=%d, name=%s, widtab=0%o, fitab=0%o\n",p,
	    n,fontbase[i]->specfont,fontbase[i]->namefont,widtab[i],fitab[i]);
	fprintf(stderr,"widths:\n");
	for (j=0; j <= n; j++) {
		fprintf(stderr," %2d", widtab[i][j] & BMASK);
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
I 10
#endif
E 10

I 8

E 8
loadfont(n, s, s1)	/* load font info for font s on position n (0...) */
int n;
char *s, *s1;
{
	char temp[60];
D 8
	int fin, nw, norig;
E 8
I 8
	register int fin;
	register int nw;
	register int norig;
E 8

I 4
D 8

E 8
E 4
	if (n < 0 || n > NFONTS)
		error(FATAL, "illegal fp command %d %s", n, s);
	if (strcmp(s, fontbase[n]->namefont) == 0)
		return;
I 8

	for (fin = 1; fin <= NFONTS; fin++)	/* first check to see if the */
	    if (strcmp(s, fontbase[fin]->namefont) == 0) {  /* font is loaded */
		register char *c;			    /* somewhere else */

#define ptrswap(x, y) { c = (char*) (x); x = y; y = c; }
I 10
#define ptrfswap(x, y) { c = (char*) (x); x = y; y = (struct font *) c; }
E 10

D 10
		ptrswap(fontbase[n], fontbase[fin]);
E 10
I 10
		ptrfswap(fontbase[n], fontbase[fin]);
E 10
		ptrswap(codetab[n], codetab[fin]);
		ptrswap(widtab[n], widtab[fin]);
		ptrswap(fitab[n], fitab[fin]);
		t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
		t_fp(fin, fontbase[fin]->namefont, fontbase[fin]->intname);
		return;
	    }

E 8
	if (s1 == NULL || s1[0] == '\0')
D 3
		sprintf(temp, "%s/devver/%s.out", fontdir, s);
E 3
I 3
D 7
		sprintf(temp, "%s/devvar/%s.out", fontdir, s);
E 7
I 7
		sprintf(temp, "%s/devva/%s.out", fontdir, s);
E 7
E 3
	else
		sprintf(temp, "%s/%s.out", s1, s);
	if ((fin = open(temp, 0)) < 0)
		error(FATAL, "can't open font table %s", temp);
	norig = fontbase[n]->nwfont & BMASK;
	read(fin, fontbase[n], 3*norig + nchtab+128-32 + sizeof(struct font));
	if ((fontbase[n]->nwfont & BMASK) > norig)
D 3
		error(FATAL, "Font %s too big for position %d\n", s, n);
E 3
I 3
		error(FATAL, "Font %s too big for position %d", s, n);
E 3
	close(fin);
	nw = fontbase[n]->nwfont & BMASK;
	widtab[n] = (char *) fontbase[n] + sizeof(struct font);
	codetab[n] = (char *) widtab[n] + 2 * nw;
	fitab[n] = (char *) widtab[n] + 3 * nw;
	t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
	fontbase[n]->nwfont = norig;	/* to later use full original size */
#ifdef DEBUGABLE
	if (dbg > 1) fontprint(n);
#endif
}

D 3
done()
{
	t_reset('s');
	exit(0);
}
E 3
I 3

E 3
/*VARARGS1*/
error(f, s, a1, a2, a3, a4, a5, a6, a7) {
D 3
	fprintf(stderr, "dver: ");
E 3
I 3
	fprintf(stderr, "dvar: ");
E 3
	fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
	fprintf(stderr, "\n");
D 6
	if (f)
D 3
		done();
E 3
I 3
		exit(1);
E 6
I 6
	if (f) exit(ABORT);
E 6
E 3
}


D 3
/*******************************************************************************
 * Routine:	
 * Results:	
 * Side Efct:	
 ******************************************************************************/

E 3
t_init()	/* initialize device */
{
	int i;

	hpos = vpos = 0;

	setsize(t_size(10));	/* start somewhere */
	setfont(1);
}


struct state {
	int	ssize;
	int	sfont;
	int	shpos;
	int	svpos;
D 3
	int	shorig;
	int	svorig;
E 3
I 3
	int	sstyle;
	int	sthick;
E 3
};
struct	state	state[MAXSTATE];
struct	state	*statep = state;

t_push()	/* begin a new block */
{
	statep->ssize = size;
	statep->sfont = font;
D 3
	statep->shorig = horig;
	statep->svorig = vorig;
E 3
I 3
	statep->sstyle = linmod;
	statep->sthick = linethickness;
E 3
	statep->shpos = hpos;
	statep->svpos = vpos;
D 3
	horig = hpos;
	vorig = vpos;
E 3
D 4
	hpos = vpos = 0;
E 4
	if (statep++ >= state+MAXSTATE)
		error(FATAL, "{ nested too deep");
D 4
	hpos = vpos = 0;
E 4
}

t_pop()	/* pop to previous state */
{
	if (--statep < state)
		error(FATAL, "extra }");
	size = statep->ssize;
	font = statep->sfont;
	hpos = statep->shpos;
	vpos = statep->svpos;
D 3
	horig = statep->shorig;
	vorig = statep->svorig;
E 3
I 3
	linmod = statep->sstyle;
	linethickness = statep->sthick;
E 3
}

t_page(n)	/* do whatever new page functions */
{
	int i;


D 7
	if (output) {
		if (++scount >= spage) {
			t_reset('p');
			scount = 0;
		}
D 3
		slop_lines(maxH);
E 3
I 3
		slop_lines(NLINES);
E 7
I 7
	if (emptypos < NLINES) {		/* finish off last page, if */
		slop_lines(NLINES - emptypos);	/* it's not done yet */
E 7
E 3
D 6
/* noversatec
E 6
I 6
#ifdef DRIVER
E 6
		ioctl(OUTFILE, VSETSTATE, prtmode);
		if (write(OUTFILE, "\f", 2) != 2)
			exit(RESTART);
		ioctl(OUTFILE, VSETSTATE, pltmode);
D 6
noversatec */
E 6
I 6
#endif
E 6
D 3
		size = BYTES_PER_LINE * maxH;
		vclear(buf0p, size);
E 3
I 3
D 4
		vclear(buf0p, BYTES_PER_LINE * NLINES);
E 3
		buf0p = buffer;
E 4
	}
I 7
	if (output) {
		emptypos = 0;		/* set emptying to be started */
		elevel = fill;		/* swap buffer pointers */
		fill = empty;
		empty = elevel;
	}
E 7

D 3
	maxH = 0;

E 3
	vpos = 0;
	output = 1;
	if (nolist == 0)
D 4
		return;	/* no -o specified */
E 4
I 4
		return;		/* no -o specified */
E 4
	output = 0;
	for (i = 0; i < nolist; i += 2)
		if (n >= olist[i] && n <= olist[i+1]) {
			output = 1;
			break;
		}
}

t_newline()	/* do whatever for the end of a line */
{
	hpos = 0;	/* because we're now back at the left margin */
}

t_size(n)	/* convert integer to internal size number*/
int n;
{
	int i;

	if (n <= pstab[0])
D 4
		return(1);
	else if (n >= pstab[nsizes-1])
		return(nsizes);
E 4
I 4
		return(0);
	else if (n >= pstab[nsizes - 1])
		return(nsizes - 1);
E 4
	for (i = 0; n > pstab[i]; i++)
		;
D 4
	return(i+1);
E 4
I 4
	return(i);
E 4
}

t_charht(n)	/* set character height to n */
int n;
{
#ifdef DEBUGABLE
D 3
	if (dbg)fprintf(stderr,"can't set height on versatec yet\n");
E 3
I 3
D 4
	if (dbg) error(!FATAL, "can't set height on varian yet");
E 4
I 4
	if (dbg) error(!FATAL, "can't set height on varian");
E 4
E 3
#endif
}

t_slant(n)	/* set slant to n */
int n;
{
#ifdef DEBUGABLE
D 3
	if (dbg)fprintf(stderr,"can't set slant on versatec yet\n");
E 3
I 3
D 4
	if (dbg) error(!FATAL, "can't set slant on varian yet");
E 4
I 4
	if (dbg) error(!FATAL, "can't set slant on varian");
E 4
E 3
#endif
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
#ifdef DEBUGABLE
		if (dbg) fprintf(stderr,"width = %d\n", lastw);
#endif
	}
}

I 7

E 7
t_reset(c)
{	
D 3


E 3
D 7
	output = 1;
	switch(c){
	case 'p':
D 3
		slop_lines(maxH);
		maxH = 0;
E 3
I 3
		slop_lines(NLINES);
E 3
D 4
		buf0p = buffer;
E 4
		break;
	case 's':
D 3
		slop_lines(maxH);
E 3
I 3
		slop_lines(NLINES);
E 7
I 7
	if (c == 's') {
		t_page();
		output = 0;
		t_page();
E 7
E 3
D 4
		t_done();
E 4
I 4
D 6
/* noversatec
E 6
I 6
#ifdef DRIVER
E 6
		ioctl(OUTFILE, VSETSTATE, prtmode);
		if (write(OUTFILE, "\f", 2) != 2)
			exit(RESTART);
D 6
noversatec */
E 6
I 6
#endif
E 6
E 4
D 7
		break; /* no Return */
E 7
	}
}

D 4
t_done()	/* clean up and get ready to die */
{
/* noversatec
	ioctl(OUTFILE, VSETSTATE, prtmode);
	if (write(OUTFILE, "\f", 2) != 2)
		exit(RESTART);
noversatec */
}
E 4

D 4
t_trailer()
{
	vpos = 0;
	vgoto(TRAILER);
	vpos = 0;
}

I 3

E 4
/*----------------------------------------------------------------------------*
 | Routine:	hgoto (horizontal_spot)
 |
 | Results:	hpos is set to n.  If n overlaps in either direction, it wraps
 |		around to the other end of the page.
 *----------------------------------------------------------------------------*/

hgoto(n)
int n;
{
    if (n < 0)
	n += NLINES;
    else if (n >= NLINES)
	n -= NLINES;
    hpos = n;
}


/*----------------------------------------------------------------------------*
 | Routine:	vgoto (vertical_spot)
 |
 | Results:	vpos is set to n.  If n overlaps in either direction, it wraps
 |		around to the other end of the page.
 *----------------------------------------------------------------------------*/

E 3
vgoto(n)
I 3
int n;
E 3
{
D 3
			/* check to see if n would move use past buf0p */
    if (n < 0) {
	fprintf (stderr, "ERROR vgoto past the beginning");
	done();
    }
					/* check for end of page */
    if (n > RES * 11) n -= RES * 11;	/* wrap around on to the top */
E 3
I 3
    if (n < 0)
	n += RASTER_LENGTH;
    else if (n > RASTER_LENGTH)
	n -= RASTER_LENGTH;
E 3
    vpos = n;
}

put1s(s)	/* s is a funny char name */
char *s;
{
	int i;

	if (!output)
		return;
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr,"%s ", s);
#endif
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
#ifdef DEBUGABLE
		if (dbg) fprintf(stderr,"non-exist 0%o\n", c + 32);
#endif
D 4
 		lastw = (widtab[font][0] * pstab[size-1] + dev.unitwidth/2)
E 4
I 4
 		lastw = (widtab[font][0] * pstab[size] + dev.unitwidth/2)
E 4
								/ dev.unitwidth;
		return;
	}
	k = ofont = font;
	i = fitab[font][c] & BMASK;
	if (i != 0) {			/* it's on this font */
		p = codetab[font];	/* get the printing value of ch */
		pw = widtab[font];	/* get the width */
D 6
	} else if (smnt > 0) {		/* on special (we hope) */
		for (k=smnt, j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1)){
E 6
I 6
D 10
	} else		/* on another font (we hope) */
		for (k=font, j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1)){
E 10
I 10
	} else {		/* on another font - run down the font list */
		for (j=0; j++ <= nfonts; k = (k+1) % (nfonts+1)) {
E 10
E 6
			if (fitab[k] == 0)
				continue;
D 10
			if ((i = fitab[k][c] & BMASK) != 0) {
E 10
I 10
			if ((i=fitab[k][c] & BMASK) != 0) {
E 10
				p = codetab[k];
				pw = widtab[k];
				setfont(k);
				break;
			}
		}
I 10
	}
E 10
D 6
	}
E 6
I 6

E 6
D 10
	if (i == 0 || (code = p[i] & BMASK) == 0 || k > nfonts) {
E 10
I 10
	if (i == 0) {
E 10
#ifdef DEBUGABLE
		if (dbg) fprintf(stderr,"not found 0%o\n", c+32);
#endif
		return;
	}
I 10
	code = p[i] & BMASK;
E 10
#ifdef DEBUGABLE
	if (dbg) {
		if (isprint(c+32))
			fprintf(stderr,"%c %d\n", c+32, code);
		else
			fprintf(stderr,"%03o %d\n", c+32, code);
	}
#endif
	outc(code);	/* character is < 254 */
	if (font != ofont)
		setfont(ofont);
D 4
	lastw = ((pw[i]&077) * pstab[size-1] + dev.unitwidth/2) / dev.unitwidth;
E 4
I 4
	lastw = ((pw[i]&077) * pstab[size] + dev.unitwidth/2) / dev.unitwidth;
E 4
}



setsize(n)	/* set point size to n (internal) */
int n;
{

	if (n == size)
		return;	/* already there */
D 4
	if (vloadfont(font,pstab[n-1]) != -1)
E 4
I 4
	if (vloadfont(font, pstab[n]) != -1)
E 4
		size = n;
}

t_fp(n, s, si)	/* font position n now contains font s, intname si */
D 6
int n;
E 6
I 6
int n;		/* internal name is ignored */
E 6
char *s, *si;
{
D 4
	register	i;
E 4
I 4
	register int i;
E 4

I 4

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
E 4
D 6
	fontname[n].name = s;
	fontname[n].number = atoi(si);
E 6
I 6
	fontname[n] = s;
E 6
D 4
	for(i = 0;i < NFONTS;i++)/* free the bits of that font */
E 4
I 4
D 7
	for(i = 0;i < NFONTS;i++)	/* free the bits of that font */
E 7
I 7
	for(i = 0;i <= NFONTS;i++)	/* free the bits of that font */
E 7
E 4
		if (fontdes[i].fnum == n){
			nfree(fontdes[i].bits);
D 7
			fontdes[i].bits = 0;
E 7
			fontdes[i].fnum = -1;
		}
}

I 4

E 4
setfont(n)	/* set font to n */
int n;
{
D 13
	if (n < 0 || n > NFONTS)
E 13
I 13
	if (n < 0 || n > nfonts)
E 13
D 3
		error(FATAL, "illegal font %d\n", n);
E 3
I 3
		error(FATAL, "illegal font %d", n);
E 3
D 4
	if (vloadfont(n,pstab[size - 1]) != -1)
E 4
I 4
	if (vloadfont(n,pstab[size]) != -1)
E 4
		font = n;
}

I 13

setstip(n)	/* set stipple font to n */
int n;
{
	if (n < 1 || n > nstips)
		error(FATAL, "illegal stipple %d", n);
	stip = n;
}


E 13
vloadfont(fnum, fsize)
register int fnum;
register int fsize;
{
	register int i;

	fontwanted = 0;
	if (fnum == cfnum && fsize == cpsize)
		return(0);
	for (i = 0; i < NFONTS; i++) {
		if (fontdes[i].fnum == fnum && fontdes[i].psize == fsize) {
			cfnum = fontdes[i].fnum;
			cpsize = fontdes[i].psize;
			dispatch = &fontdes[i].disp[0];
			bits = fontdes[i].bits;
			cfont = i;
			return (0);
		}
	}
		/* this is a new font */
D 6
	if (fnum < 0 || fnum > NFONTS || fontname[fnum].name == 0) {
E 6
I 6
	if (fnum < 0 || fnum > NFONTS || fontname[fnum] == 0) {
E 6
D 14
	    fprintf(stderr, "Internal error: illegal font %d name %s size\n",
D 4
			    fontname[fnum].name,fnum,fsize);
E 4
I 4
D 6
			    fontname[fnum].name, fnum, fsize);
E 6
I 6
			    fontname[fnum], fnum, fsize);
E 14
I 14
	    error(!FATAL,"error: illegal font %d, size %d\n", fnum, fsize);
E 14
E 6
E 4
	    return(-1);
	}
		/* Need to verify the existance of that font/size here*/
	nfontnum = fnum;
	npsize = fsize;
	fontwanted++;
	return (0);
}


getfont()
{
D 4
	register int fnum, fsize, fontd;
	int d;
E 4
I 4
	register int fnum;
	register int fsize;
	register int fontd;
	register int d;
D 6
	register int savesize = size;
E 6
I 6
	register int sizehunt = size;
E 6
E 4
	char cbuf[BUFSIZ];

	fnum = nfontnum;
	fsize = npsize;
D 2
	sprintf(cbuf, "/usr/lib/vfont/%s.%d",fontname[fnum].name, fsize);
E 2
I 2
D 4
	sprintf(cbuf, "/usr/lib/vfont/%s.%dr",fontname[fnum].name, fsize);
E 2
	fontd = open(cbuf, OPENREAD);
	if (fontd == -1) {
		perror(cbuf);
D 3
		error(0,"fnum = %d size = %d name = %s\n",
E 3
I 3
		error(!FATAL,"fnum = %d size = %d name = %s",
E 3
			fnum,fsize,fontname[fnum]);
		fontwanted = 0;
		return (-1);
E 4
I 4
			/* try to open font file - if unsuccessful, hunt for */
			/* a file of same style, different size to substitute */
D 6
	d = -1;	/* direction to look in pstab (smaller first) */
E 6
I 6
	d = -1;	 /* direction to look in pstab (smaller first) */
E 6
	do {
D 6
	    sprintf(cbuf, "%s/%s.%dr", bitdir, fontname[fnum].name, fsize);
E 6
I 6
	    sprintf(cbuf, "%s/%s.%dr", bitdir, fontname[fnum], fsize);
E 6
	    fontd = open(cbuf, OPENREAD);
	    if (fontd == -1) {		/* File wasn't found. Try another ps */
D 6
		size += d;
		if (size < 0) {		/* past beginning - look higher */
E 6
I 6
		sizehunt += d;
		if (sizehunt < 0) {	/* past beginning - look higher */
E 6
		    d = 1;
D 6
		    size = savesize + 1;
E 6
I 6
		    sizehunt = size + 1;
E 6
		}
D 6
		if (size > nsizes) {	/* past top - forget it */
E 6
I 6
		if (sizehunt > nsizes) {	/* past top - forget it */
E 6
		    d = 0;
		} else {
D 6
		    fsize = pstab[size];
E 6
I 6
		    fsize = pstab[sizehunt];
E 6
		}
	    }
	} while (fontd == -1 && d != 0);

	if (fontd == -1) {		/* completely unsuccessful */
	    perror(cbuf);
	    error(!FATAL,"fnum = %d, psize = %d, name = %s",
D 6
		fnum, npsize, fontname[fnum].name);
E 6
I 6
		fnum, npsize, fontname[fnum]);
E 6
	    fontwanted = 0;
	    return (-1);
E 4
	}
	if (read(fontd, &header, sizeof  (header)) != sizeof (header)
						|| header.magic != 0436)
		fprintf(stderr, "%s: Bad font file", cbuf);
	else {
		cfont = relfont();
		if ((bits=nalloc(header.size+DSIZ+1,1))== NULL)
			if ((bits=allpanic(header.size+DSIZ+1))== NULL) {
D 6
				fprintf(stderr,"%s: ran out of memory\n", cbuf);
				exit(ABORT);
E 6
I 6
				error(FATAL,"%s: ran out of memory", cbuf);
E 6
			}

			/*
			 * have allocated one chunk of mem for font, dispatch.
			 * get the dispatch addr, align to word boundary.
			 */

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
		}
	}
	close(fontd);
	fontwanted = 0;
	return(-1);
}

/*
 * "release" a font position - find an empty one, if possible
 */

relfont()
{
    register int newfont;

    for (newfont = 0; newfont < NFONTS; newfont++)
D 7
	if (fontdes [newfont].bits == (char *) -1  ||  !fontdes [newfont].bits)
E 7
I 7
	if (fontdes [newfont].fnum == -1)
E 7
	    break;
D 7
    if (fontdes [newfont].bits != (char *) -1  &&  fontdes [newfont].bits) {
E 7
I 7
    if (fontdes [newfont].fnum != -1) {
E 7
	nfree (fontdes [newfont].bits);
D 7
	fontdes [newfont].bits = (char *)0;
E 7
#ifdef DEBUGABLE
	if (dbg) fprintf (stderr, "freeing position %d\n", newfont);
    } else {
	if (dbg)
	    fprintf (stderr, "taking, not freeing, position %d\n", newfont);
#endif
    }
D 7
    fontdes[newfont].bits = 0;
E 7
I 7
    fontdes[newfont].fnum = -1;
E 7
    return (newfont);
}

char *allpanic (nbytes)
int nbytes;
{
	register int i;

D 7
	for (i = 0; i <= NFONTS; i++)
	    if (fontdes[i].bits != (char *)-1 && fontdes[i].bits != (char *)0)
		nfree(fontdes[i].bits);
E 7
	for (i = 0; i <= NFONTS; i++) {
D 7
		fontdes[i].fnum = fontdes[i].psize = -1;
		fontdes[i].bits = 0;
E 7
I 7
		if (fontdes[i].fnum != -1) nfree(fontdes[i].bits);
		fontdes[i].fnum = -1;
E 7
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
int code;		/* character to print */
{
    register struct dispatch *dis; /* ptr to character font record */
    register char *addr;	/* addr of font data */
    int llen;			/* length of each font line */
    int nlines;			/* number of font lines */
    register char *scanp;	/* ptr to output buffer */
    int scanp_inc;		/* increment to start of next buffer */
    int offset;			/* bit offset to start of font data */
D 4
    int i;			/* loop counter */
E 4
I 4
    register int i;		/* loop counter */
E 4
    register int count;		/* font data ptr */
    register unsigned fontdata;	/* font data temporary */
    register int off8;		/* offset + 8 */

    if (fontwanted)
	getfont();
    dis = dispatch + code;
    if (dis->nbytes) {
	addr = bits + dis->addr;
D 2
	llen = (dis->left + dis->right + 7) / 8;
	nlines = dis->up + dis->down;
	if ((i = vpos + dis->down) > maxH) maxH = i;	/* remember page len */
	scanp = buf0p + (((vpos - dis->up) - 1) * BYTES_PER_LINE
			+ (hpos - dis->left) / 8);
E 2
I 2
	llen = (dis->up + dis->down + 7) >> 3;
	nlines = dis->right + dis->left;
D 3
	if ((i = hpos + dis->right) > maxH) maxH = i;	/* remember page len */
E 3
D 7
	scanp = buf0p + (hpos - dis->left) * BYTES_PER_LINE
			- (1 + ((dis->down + vpos) >> 3));
E 2
	if (scanp < &buffer[0])
	    scanp += sizeof buffer;
E 7
I 7
	scanp = fill + (hpos + 1 - dis->left) * BYTES_PER_LINE
			- (1 + ((dis->down + vpos - 1) >> 3));
	if (scanp < fill)
	    scanp += BUFFER_SIZE;
E 7
	scanp_inc = BYTES_PER_LINE - llen;
D 2
	offset = - ((hpos - dis->left) &07);
	off8 = offset + 8;
E 2
I 2
D 7
	off8 = ((dis->down + vpos) &07);
E 7
I 7
	off8 = ((dis->down + vpos - 1) &07);
E 7
	offset = off8 - 8;
E 2
	for (i = 0; i < nlines; i++) {
D 7
	    if (scanp >= &buffer[BUFFER_SIZE])
E 7
I 7
	    if (scanp >= fill + BUFFER_SIZE)
E 7
D 6
		scanp -= sizeof buffer;
E 6
I 6
		scanp -= BUFFER_SIZE;
E 6
	    count = llen;
D 6
	    if (scanp + count <= &buffer[BUFFER_SIZE]) {
E 6
I 6
D 7
	    if (scanp + count < &buffer[BUFFER_SIZE]) {
E 7
I 7
	    if (scanp + count < fill + BUFFER_SIZE) {
E 7
E 6
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
	    }
	    scanp += scanp_inc+count;
	    addr += count;
	}
	return;
    }
    return;
}

I 13

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
D 14
	vloadfont(curfont, cursize);
E 14
I 14
	if (curfont >= 0) vloadfont(curfont, cursize);
E 14
}


E 13
slop_lines(nlines)
int nlines;

/* Output "nlines" lines from the buffer, and clear that section of the  */
D 7
/* buffer.	*/
E 7
I 7
/* buffer.	Also updates the pointers to the emptying buffer */
E 7

{
	unsigned usize;

	usize = BYTES_PER_LINE * nlines;
D 4
	writev(buf0p,usize);
E 4
I 4
D 7
	vwrite(buf0p, usize);
E 4
	vclear(buf0p, usize);
D 6
/* noversatec
E 6
I 6
#ifdef DRIVER
E 6
	ioctl(OUTFILE, VSETSTATE, pltmode);
D 6
noversatec */
E 6
I 6
#endif
E 7
I 7
	vwrite(elevel, usize);
	vclear(elevel, usize);
	elevel += usize;
	emptypos += nlines;
E 7
E 6
}

D 4
writev(buf,usize)
E 4
I 4
vwrite(buf,usize)
E 4
char *buf;
unsigned usize;
{
	register int tsize = 0;

	while (usize){
		buf += tsize;
		tsize = usize > MAXWRIT ? MAXWRIT : usize;
#ifdef DEBUGABLE
		if (dbg)fprintf(stderr,"buf = %d size = %d\n",buf,tsize);
#endif
		if ((tsize = write(OUTFILE, buf, tsize)) < 0) {
D 3
			perror("dver: write failed");
E 3
I 3
			perror("dvar: write failed");
E 3
			exit(RESTART);
		}
		usize -= tsize;
	}
}

vclear (ptr, nbytes)
char	*ptr;
unsigned nbytes;
{
    register tsize = 0;

    while (nbytes){
	if ((unsigned)(16*1024) < nbytes) {
	    tsize = 16 * 1024;
	} else
	    tsize = nbytes;
	nbytes -= tsize;
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr,"clearing ptr = %d size = %d\n",ptr,tsize);
#endif
	clear(ptr,tsize);
	ptr += tsize;
    }
}

/*ARGSUSED*/
clear(lp, nbytes)
int *lp;
int nbytes;
{
I 16
#ifdef vax
E 16
	asm("movc5 $0,(sp),$0,8(ap),*4(ap)");
I 16
#else
	register int i = nbytes;
	register int *cp = lp;

	while (i-- > 0)
		*(cp++) = 0;
#endif
E 16
}

char *
nalloc(i, j)
int i, j;
{
	register char *cp;

	cp = calloc(i, j);
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "allocated %d bytes at %x\n", i * j, cp);
#endif
	return(cp);
}

nfree(cp)
char *cp;
{
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "freeing at %x\n", cp);
#endif
	free(cp);
}


/*
 * Points should be in the range 0 <= x < RASTER_LENGTH, 0 <= y < NLINES.
 * The origin is the top left-hand corner with increasing x towards the
D 4
 * right and increasing y going down.
 * The output array is NLINES x BYTES_PER_LINE pixels.
E 4
I 4
 * right and increasing y going down.  X and Y should be sent as (0,0) being
 * at the bottom left.  The output array is NLINES x BYTES_PER_LINE pixels.
E 4
 */
point(x, y)
D 2
register int x, y;
E 2
I 2
register int x;
register int y;
E 2
{
D 2
    if ((unsigned) x < RASTER_LENGTH && (unsigned) y < NLINES) {
	buffer [y * BYTES_PER_LINE + (x >> 3)] |= 1 << (7 - (x & 07));
E 2
I 2
D 13
    if ((unsigned)(y=RASTER_LENGTH-y) < RASTER_LENGTH && (unsigned)x < NLINES) {
E 13
I 13
    if ((unsigned)(y=(RASTER_LENGTH-1)-y)<RASTER_LENGTH && (unsigned)x<NLINES) {
E 13
D 7
	buffer [x * BYTES_PER_LINE + (y >> 3)] |= 1 << (7 - (y & 07));
E 7
I 7
	*(fill + x * BYTES_PER_LINE + (y >> 3)) |= 1 << (7 - (y & 07));
E 7
E 2
    }
}
I 13


#define pv(x)	((polyvector *)x)

typedef struct poly {
	struct poly *next;	/* doublely-linked lists of vectors */
	struct poly *prev;
	int param;	/* bressenham line algorithm parameter */
	short dy;	/* delta-y for calculating line */
	short dx;	/* delta-x for calculating line */
	short curry;	/* current y in this vector */
	short endx;	/* where vector ends */
} polyvector;


/*----------------------------------------------------------------------------*
 | Routine:	polygon ( x_coordinates, y_coordinates, num_of_points )
 |
 | Results:	draws a polygon starting at (x[1], y[1]) going through
 |		each of (x_coordinates, y_coordinates), and fills it
 |		with a stipple pattern from stip_disp and stip_bits,
 |		which point to the stipple font.  The pattern is defined
 |		by "stip" and "stipmem".
 |
 |		The scan-line algorithm implemented scans from left to
 |		right (low x to high x).  It also scans, within a line,
 |		from bottom to top (high y to low y).
 |
 |		polygons are clipped to page boundary.
 |
 | Bugs:	stipple pattern MUST be a power of two bytes "wide" and
 |		square.  The square restriction comes from the fact that
 |		the varian and versatec are respectively rotated.
 *----------------------------------------------------------------------------*/

polygon(x, y, npts)
int x[];
int y[];
int npts;
{
    int nextx;			/* at what x value the next vector starts */
    int maxx, minx, maxy, miny;		/* finds bounds of polygon */
    polyvector *activehead;		/* doing fill, is active edge list */
    polyvector *waitinghead;		/* edges waiting to be active */
    register polyvector *vectptr;	/* random vector */
    register int i;			/* random register */

    char *topstipple;		/* points to beginning of stipple glyph */
    char *leftstipple;		/* points to beginning of line of stipple */
    char *bottompage;		/* points to the edge of a raster line */
    int bytewidth;		/* glyph width in bytes */
    int mask;			/* mask to pick off pixel index into stipple */
    int bytemask;		/* mask to pick off byte index into stipple */


    if (bordered) {
	for (i = 1; i < npts; i++)		/* first draw outlines */
	    HGtline(x[i], y[i], x[i+1], y[i+1]);
    }

						/* if no stipple, don't fill */
    if (stip_disp == (struct dispatch *) NULL || stip_bits == (char *) NULL)
	return;

    stip_disp += stipmem;			/* set up parameters for */
    if (!stip_disp->nbytes) {			/* tiling with the stipple */
#ifdef DEBUGABLE
	error(!FATAL, "member not found: member %d, stipple %d", stipmem, stip);
#endif
	return;
    }
    topstipple = stip_bits + stip_disp->addr;
    bytewidth = stip_disp->up + stip_disp->down;
    for (i = 1 << 30; i && i != bytewidth; i = i >> 1)
	;
    if (i==0 || bytewidth<8 || bytewidth != stip_disp->right+stip_disp->left) {
	error(!FATAL, "invalid stipple: number %d, member %d", stip, stipmem);
	return;
    }
    mask = bytewidth - 1;
    bytewidth = bytewidth >> 3;
    bytemask = bytewidth - 1;

				/* allocate space for raster-fill algorithm*/
    if ((vectptr = pv( nalloc(sizeof(polyvector), npts + 6) )) == NULL) {
	error(!FATAL, "unable to allocate space for polygon");
	return;
    }
#ifdef DEBUGABLE
    if (dbg) fprintf(stderr, "polygon, %d points\n", npts);
#endif

    waitinghead = vectptr;
    minx = maxx = x[1];
    miny = maxy = y[1];
    (vectptr++)->prev = pv( NULL );	/* put dummy entry at start */
    waitinghead->next = vectptr;
    vectptr->prev = waitinghead;
    i = 1;					/* starting point of coords */
    if (y[1] != y[npts] || x[1] != x[npts]) {
	y[0] = y[npts];				/* close polygon if it's not */
	x[0] = x[npts];
	i = 0;
    }
    while (i < npts) {		/* set up the vectors */
	register int j;			/* indexes to work off of */
	register int k;

	if (miny > y[i]) miny = y[i];		/* remember limits */
	else if (maxy < y[i]) maxy = y[i];
	if (maxx < x[i]) maxx = x[i];
	else if (minx > x[i]) minx = x[i];

	j = i;			/* j "points" to the higher (lesser) point */
	k = ++i;
	if (x[j] == x[k])		/* ignore vertical lines */
	    continue;

	if (x[j] > x[k]) {
	    j++;
	    k--;
	}
	vectptr->next = vectptr + 1;
	vectptr->param = x[j];		/* starting point of vector */
	vectptr->dy = y[k] - y[j];	/* line-calculating parameters */
	vectptr->dx = x[k] - x[j];
	vectptr->curry = y[j];		/* starting point */
	(vectptr++)->endx = x[k];	/* ending point */
	vectptr->prev = vectptr - 1;
    }
				/* set now because we didn't know minx before */
    leftstipple = topstipple + (minx & mask) * bytewidth;
    bottompage = fill + minx * BYTES_PER_LINE;
    waitinghead->param = minx - 1;
					/* if no useable vectors, quit */
    if (vectptr == waitinghead + 1)
	goto leavepoly;

    vectptr->param = maxx + 1;		/* dummy entry at end, too */
    vectptr->next = pv( NULL );

    activehead = ++vectptr;		/* two dummy entries for active list */
    vectptr->curry = maxy + 1;		/* head */
    vectptr->endx = maxx + 1;
    vectptr->param = vectptr->dx = vectptr->dy = 0;
    activehead->next = ++vectptr;
    activehead->prev = vectptr;

    vectptr->prev = activehead;		/* tail */
    vectptr->next = activehead;
    vectptr->curry = miny - 1;
    vectptr->endx = maxx + 1;
    vectptr->param = vectptr->dx = vectptr->dy = 0;


			/* main loop -- gets vectors off the waiting list, */
			/* then displays spans while updating the vectors in */
			/* the active list */
    while (minx <= maxx) {
	i = maxx + 1;		/* this is the NEXT time to get a new vector */
	for (vectptr = waitinghead->next; vectptr != pv( NULL ); ) {
	    if (minx == vectptr->param) {
				/* the entry in waiting list (vectptr) is */
				/*   ready to go into active list.  Need to */
				/*   convert some vector stuff and sort the */
				/*   entry into the list. */
		register polyvector *p;	/* random vector pointers */
		register polyvector *v;

							/* convert this */
		if (vectptr->dy < 0)			/* entry to active */
		    vectptr->param = (vectptr->dy >> 1) - (vectptr->dx >> 1);
		else
		    vectptr->param = -((vectptr->dx >> 1) + (vectptr->dy >> 1));

		p = vectptr;			/* remove from the */
		vectptr = vectptr->next;	/* waiting list */
		vectptr->prev = p->prev;
		p->prev->next = vectptr;
						/* find where it goes */
						/* in the active list */
						/* (sorted greatest first) */
		for (v = activehead->next; v->curry > p->curry; v = v->next)
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
	nextx = i;

					/* print the polygon while there */
					/* are no more vectors to add */
	while (minx < nextx) {
					/* remove any finished vectors */
	    vectptr = activehead->next;
	    do {
		if (vectptr->endx <= minx) {
		    vectptr->prev->next = vectptr->next;
		    vectptr->next->prev = vectptr->prev;
		}
	    } while ((vectptr = vectptr->next) != activehead);

					/* draw the span */
	    if (((unsigned) minx) < NLINES) {
	      vectptr = activehead->next;
	      while (vectptr->next != activehead) {
		register int start;	/* get the beginning */
		register int length;	/*   and the end of span */
		register char *glyph;
		register char *raster;

		start = (RASTER_LENGTH - 1) - vectptr->curry;
		vectptr = vectptr->next;
		length = RASTER_LENGTH - vectptr->curry;
		vectptr = vectptr->next;

					/* bound the polygon to the page */
		if (start >= RASTER_LENGTH)
		    break;
		if (start < 0) start = 0;
		if (length > RASTER_LENGTH) length = RASTER_LENGTH;
		length -= start;		/* length is in pixels */

		i = start & 7;
		start = start >> 3;		/* start is in bytes */
		raster = bottompage + start;
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
	    }

#ifdef DEBUGABLE
	    if (dbg) {
		vectptr = activehead;
		do {
		    fprintf (stderr, "%d ", vectptr->curry);
		    vectptr = vectptr->next;
		} while (vectptr != activehead);
	    }
#endif
					/* update the vectors */
	    vectptr = activehead->next;
	    do {
		if (vectptr->dy > 0) {
		    while (vectptr->param >= 0) {
			vectptr->param -= vectptr->dx;
			vectptr->curry++;
		    }
		    vectptr->param += vectptr->dy;
		} else if (vectptr->dy < 0) {
		    while (vectptr->param >= 0) {
			vectptr->param -= vectptr->dx;
			vectptr->curry--;
		    }
		    vectptr->param -= vectptr->dy;
		}
					/* must sort the vectors if updates */
					/* caused them to cross */
					/* also move to next vector here */
		if (vectptr->curry > vectptr->prev->curry) {
		    register polyvector *v;		/* vector to move */
		    register polyvector *p;	/* vector to put it after */

		    v = vectptr;
		    p = v->prev;
		    while (v->curry > p->curry)	/* find the */
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

	    if (++minx & mask) {
		leftstipple += bytewidth;
	    } else {
		leftstipple = topstipple;
	    }
	    bottompage += BYTES_PER_LINE;
	} /* while (minx < nextx) */
    } /* while (minx <= maxx) */

leavepoly:
    nfree(waitinghead);
}  /* polygon function */
E 13
E 1
