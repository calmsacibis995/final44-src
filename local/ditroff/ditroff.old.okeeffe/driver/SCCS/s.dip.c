h26414
s 00028/00010/01158
d D 1.12 85/10/29 13:28:59 slatteng 14 13
c put in font file searching
e
s 00005/00001/01163
d D 1.11 84/06/01 18:19:28 slatteng 13 12
c fixed so non-existent glyphs in the stipple file won't upset Imagen
e
s 00008/00004/01156
d D 1.10 84/05/17 11:39:14 slatteng 12 10
c add unbordered polygons and fixed error message about resolution
e
s 00007/00003/01157
d R 1.10 84/05/09 16:59:55 slatteng 11 10
c add unbordered polygons
e
s 00017/00000/01143
d D 1.9 84/04/30 20:06:51 slatteng 10 9
c fixed font-swapping to work correctly.
e
s 00113/00020/01030
d D 1.8 84/04/17 14:38:13 slatteng 9 7
c add stippled polygons, stop reinit at each page, fixed bug getting smallest point size
e
s 00108/00020/01030
d R 1.8 84/04/13 15:09:54 slatteng 8 7
c added stipples and polygons, took out "reinit" at each page,
c fixed problem with using smallest font
e
s 00006/00006/01044
d D 1.7 84/03/14 17:45:25 slatteng 7 6
c cleaned up input (checking for EOF)
e
s 00001/00001/01049
d D 1.6 84/01/03 15:36:15 slatteng 6 5
c fix mis-alignment for fonts that don't start with the zeroeth char code
e
s 00002/00000/01048
d D 1.5 83/12/18 15:30:09 slatteng 5 4
c make FONTDIR moveable
e
s 00014/00020/01034
d D 1.4 83/11/30 10:29:41 slatteng 4 3
c removed t_rule (unused), redo format of drawwig call for gremlin and
c pic splines, fix "stop" command to stop program too.
e
s 00012/00008/01042
d D 1.3 83/10/22 15:15:27 slatteng 3 2
c add MAXxy command option, improve: error reporting, font search, font read
e
s 00467/00575/00583
d D 1.2 83/09/14 11:18:53 slatteng 2 1
c production version - first attempt
e
s 01158/00000/00000
d D 1.1 83/08/08 11:28:45 slatteng 1 0
c date and time created 83/08/08 11:28:45 by slatteng
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
/*	%M%	%I%	(Berkeley)	%E%
E 2
 *	dip
 *	driver for impress/imagen canon laser printer
 */

/*
output language from troff:
all numbers are character strings

sn	size in points
fn	font as number from 1-n
I 9
in	stipple `font' as number from 1-n
E 9
cx	ascii character x
Cxyz	funny char xyz. terminated by white space
Hn	go to absolute horizontal position n
Vn	go to absolute vertical position n (down is positive)
hn	go n units horizontally (relative)
vn	ditto vertically
nnc	move right nn, then print c (exactly 2 digits!)
		(this wart is an optimization that shrinks output file size
		 about 35% and run-time about 15% while preserving ascii-ness)
Dt ...\n	draw operation 't':
I 9
	Dt d		line thickness set to d
	Ds d		line style (coordinate bit map) set to d
E 9
	Dl x y		line from here by x,y
	Dc d		circle of diameter d with left side here
	De x y		ellipse of axes x,y with left side here
	Da x y r	arc counter-clockwise by x,y of radius r
	D~ x y x y ...	wiggly line by x,y then x,y ...
I 9
	Dg x y x y ...	gremlin spline by x,y then x,y ...
	Dp s x y ...	polygon filled with s by x,y then ...
I 12
	DP s x y ...	unbordered polygon filled with s by x,y then ...
E 12
E 9
nb a	end of line (information only -- no action needed)
	b = space before line, a = after
D 2
p	new page begins -- set v to 0
E 2
I 2
pn	new page begins -- set v to 0
E 2
#...\n	comment
x ...\n	device control functions:
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

	Subcommands like "i" are often spelled out like "init".
*/

#include	<stdio.h>
#include	<signal.h>
#include	<math.h>
#include	<ctype.h>
D 2
#include	<sys/time.h>
E 2
#include	"dev.h"
#include	"canon.h"
D 2
#include	"glyph.h"
E 2
I 2
#include	"rst.h"
E 2

D 2
#define abs(n)  ((n) >= 0 ? (n) : -(n))
E 2

D 2
#define	NFONT	10
#define	RES	240		/* resolution of canon */
E 2
I 2
/* #define  DEBUGABLE	/* whether or not it'll accept the -d option */
#define  abs(n)		((n) >= 0 ? (n) : -(n))
#define  hmot(n)	hpos += n
#define  hgoto(n)	hpos = n
#define  vmot(n)	vpos += n
#define  vgoto(n)	vpos = n
E 2

D 2
int	xx, yy;
int	inputarea	= 5;	/* input area = 5 * 8k bytes */
int	rotate	= 0;	/* 0 => portrait, 1 => landscape */
int	output	= 0;	/* do we do output at all? */
int	pageno	= -1;	/* output page number */
int	nolist	= 0;	/* output page list if > 0 */
int	olist[20];	/* pairs of page numbers */
E 2
I 2
#define	FATAL	1
#define	BMASK	0377
D 9
#define	NFONT	30		/* maximum forever */
E 9
I 9
#define	NFONT	35		/* maximum forever */
E 9
E 2

I 5
#ifndef FONTDIR
E 5
I 2
#define FONTDIR	"/usr/lib/font";
I 5
#endif
E 5
#define BITDIR	"/usr/local/lib/ifontt";

				/* BOTTOMTHRESH and DELTATHRESH are used to */
				/* search through the glyphs downloaded to */
				/* determine which ones to keep and which to */
				/* dump.  They're tested against BOTTOMTHRESH */
				/* first, then if THAT doesn't release enough */
				/* space, DELTATHRESH is added until it is. */
#define BOTTOMTHRESH	16
#define DELTATHRESH	16
#define MEMSIZE	70000		/* amount of memory inside imagen */
#define BUFFER	20000		/* imagen memory set aside for page buffer */
#define CHARRAY	128		/* size of character use count array */

int	MAXX = (RES*8+RES/3);	/* size of the page... (not 8-1/2" x 11", */
int	MAXY = (RES*10+RES/2+RES/4);		/*  but 8-1/3" x 10-3/4") */

int	output	= 0;		/* do we do output at all? */
int	pageno	= -1;		/* output page number */
int	nolist	= 0;		/* output page list if > 0 */
int	olist[20];		/* pairs of page numbers */

E 2
struct dev dev;
struct font *fontbase[NFONT+1];
D 2
short	*pstab;
int	nsizes	= 1;
E 2
I 2
short *	pstab;
int	nsizes = 1;
E 2
int	nfonts;
I 9
int	nstips;
E 9
D 2
int	smnt;	/* index of first special font */
E 2
int	nchtab;
D 2
char	*chname;
short	*chtab;
char	*fitab[NFONT+1];
char	*widthtab[NFONT+1];	/* widtab would be a better name */
char	*codetab[NFONT+1];	/* device codes */
E 2
I 2
char *	chname;
short *	chtab;
unsigned char *	fitab[NFONT+1];		/* legal characters for each font */
unsigned char *	widtab[NFONT+1];	/* width table for each font */
unsigned char *	codetab[NFONT+1];	/* device code translation */
char *	fontname[NFONT+1];		/* what font is on what position? */
E 2

D 2
#define	FATAL	1
#define	BMASK	0377
E 2
I 2
#ifdef DEBUGABLE
E 2
int	dbg	= 0;
D 2
int	res	= 240;		/* input assumed computed according to this resolution */
				/* initial value to avoid 0 divide */
FILE	*tf	= NULL;		/* output file pointer */
char	*tempfile;
char	*fontdir	= "/usr/lib/font";
char	*bitdir		= "/usr/src/local/ditroff/troff/devcan";
char	*acctfile	= "/usr/adm/dipacct";
int	acctpages	= 0;
int	copies		= 1;
char	*username	= "???";
char	*getlogin();
extern char devname[];
E 2
I 2
#endif
E 2

D 2
FILE *fp	= stdin;	/* input file pointer */
extern int DX, DY, maxdots;
E 2
I 2
FILE *	tf = stdout;		/* output file pointer */
char *	fontdir = FONTDIR;
char *	bitdir = BITDIR;
FILE *	fp = stdin;		/* input file pointer */
E 2

I 2
int	totglyph= 0;		/* total space used by glyphs sent down */
int	maxglyph= MEMSIZE - BUFFER;		/* maximum space for glyphs */

int	size = 1;
int	font = 1;
I 9
int	stip = 1;
E 9
int	family;
int	hpos;		/* current horizontal position (left = 0) */
int	vpos;		/* current vertical position (down positive) */
int	lastw	= 0;	/* width of last input character */
D 12
extern int linethickness;	/* line drawing pars:  Thickness (pixels) */
extern int style;		/*   and type (SOLID, DOTTED, . . . ) */
E 12
I 12
extern int polyborder;		/* flag to turn off borders around a polygon */
E 12

typedef struct {
	int	font;
	int	size;
I 9
	short	first;
	short	last;
E 9
	unsigned char chused[CHARRAY];	/* test array - character downloaded? */
	glyph_dir *glyph;		/* array of character descriptions */
	unsigned char *cdp;		/* char data pointer */
} fontset;

fontset	*fs;			/* A global pointer to the current family */
fontset fontdata[NFONT+1];	/* table of family data descripters */

int	lastsize	= -1;
int	lastfont	= -1;
int	lastx		= -1;
int	lasty		= -1;
int	lastfam		= -1;
I 9
int	laststip	= -1;
int	laststipmem	= -1;
E 9



E 2
main(argc, argv)
char *argv[];
{
D 2
	char buf[BUFSIZ];
E 2
I 2
	int i;
E 2
	char *mktemp();
D 2
	int cleanup();
E 2
I 2
	char *operand();
E 2

D 2
	username = getlogin();
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'c':
			copies = atoi(&argv[1][2]);
E 2
I 2
	while (--argc > 0 && **++argv == '-') {
		switch ((*argv)[1]) {
I 3
		case 'X':
			MAXX = atoi(operand(&argc, &argv));
			break;
		case 'Y':
			MAXY = atoi(operand(&argc, &argv));
			break;
E 3
		case 'F':
			fontdir = operand(&argc, &argv);
E 2
			break;
D 2
		case 'r':
			rotate = !rotate;
			break;
		case 't':
			tf = stdout;
			break;
E 2
		case 'f':
D 2
			bitdir = argv[2];
			argv++;
			argc--;
E 2
I 2
			bitdir = operand(&argc, &argv);
E 2
			break;
		case 'o':
D 2
			outlist(&argv[1][2]);
E 2
I 2
			outlist(operand(&argc, &argv));
E 2
			break;
D 2
		case 'i':	/* set input area parameter */
			inputarea = atoi(&argv[1][2]);
			if (inputarea < 1)
				inputarea = 1;
			else if (inputarea > 5)
				inputarea = 5;
			break;
		case 'p':	/* pixels of resolution */
			DX = DY = atoi(&argv[1][2]);
			if (DX == 0)
				DX = DY = 1;
			break;
		case 'n':	/* number of dots in object */
			maxdots = atoi(&argv[1][2]);
			if (maxdots <= 0)
				maxdots = 32000;
			break;
E 2
		case 'b':
D 2
			fprintf(stderr, "It's never busy!");
			exit(0);
E 2
I 2
			if ((i = atoi(operand(&argc, &argv))) < 1000) i = 1000;
			else if (i > MEMSIZE - 1000) i = MEMSIZE - 1000;
			maxglyph = MEMSIZE - i; 
E 2
			break;
I 2
#ifdef DEBUGABLE
E 2
		case 'd':
D 2
			dbg = atoi(&argv[1][2]);
			if (dbg == 0) dbg = 1;
			tf = stdout;
E 2
I 2
			dbg = atoi(operand(&argc, &argv));
			if (dbg == 0) error (FATAL, "no debug value");
E 2
			break;
I 2
#endif
E 2
		}
D 2
		argc--;
		argv++;
E 2
	}

D 2
	tempfile = mktemp("/tmp/dipXXXXX");
	if (tf != stdout) {
		if ((tf = fopen(tempfile, "w")) == NULL) {
			error(FATAL, "can't open temporary file %s", tempfile);
		}
		signal(SIGINT, cleanup);
		signal(SIGHUP, cleanup);
		signal(SIGQUIT, cleanup);
	}

	if (argc <= 1)
E 2
I 2
	if (argc < 1)
E 2
		conv(stdin);
	else
D 2
		while (--argc > 0) {
			if (strcmp(*++argv, "-") == 0)
E 2
I 2
		while (argc-- > 0) {
			if (strcmp(*argv, "-") == 0)
E 2
				fp = stdin;
			else if ((fp = fopen(*argv, "r")) == NULL)
				error(FATAL, "can't open %s", *argv);
			conv(fp);
			fclose(fp);
I 2
			argv++;
E 2
		}
D 2
/*	banner(username); */
E 2
I 2

E 2
	t_wrapup();
D 2
	fclose(tf);
/*	sprintf(buf, "ipr -p %d %s 0</dev/null 1>/dev/null 2>&1 &",
		pageno, tempfile);					*/
	buf[0] = '\0';
	if(dbg){fprintf(stderr, "executing %s\n", buf); done();}
	if (tf != stdout) {
		system(buf);
		account();
E 2
I 2
	exit(0);
}


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
D 3
	    fprintf (stderr, "command-line option operand missing.\n");
	    exit(1);
E 3
I 3
	    error (FATAL, "command-line option operand missing.");
E 3
E 2
	}
D 2
	done();
E 2
I 2
	return(*(++(*argvp)));			/* operand next word */
E 2
}

I 2

E 2
outlist(s)	/* process list of page numbers to be printed */
D 4
char *s;
E 4
I 4
register char *s;
E 4
{
D 4
	int n1, n2, i;
E 4
I 4
	register int n1, n2;
E 4

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
I 2
#ifdef DEBUGABLE
E 2
	if (dbg)
		for (i=0; i<nolist; i += 2)
			printf("%3d %3d\n", olist[i], olist[i+1]);
I 2
#endif
E 2
}

I 2

E 2
in_olist(n)	/* is n in olist? */
int n;
{
	int i;

	if (nolist == 0)
		return(1);	/* everything is included */
	for (i = 0; i < nolist; i += 2)
		if (n >= olist[i] && n <= olist[i+1])
			return(1);
	return(0);
}

I 2

E 2
conv(fp)
register FILE *fp;
{
D 2
	register int c, k;
	int m, n, i, n1, m1;
E 2
I 2
	register int c;
	register int k;
	int m, n, n1, m1;
E 2
	char str[100], buf[300];

	while ((c = getc(fp)) != EOF) {
		switch (c) {
		case '\n':	/* when input is text */
		case ' ':
		case 0:		/* occasional noise creeps in */
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
		case 'D':	/* draw function */
D 7
			fgets(buf, sizeof(buf), fp);
E 7
I 7
			if (fgets(buf, sizeof(buf), fp) == NULL)
			    error(FATAL, "unexpected end of input");
E 7
			switch (buf[0]) {
			case 'l':	/* draw a line */
				sscanf(buf+1, "%d %d", &n, &m);
D 2
				t_line(n, m, ".");
E 2
I 2
				drawline(n, m, ".");
E 2
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
I 12
			case 'P':
				polyborder = 0;		/* borderless polygon */
E 12
I 9
			case 'p':	/* polygon */
				sscanf(buf+1, "%d", &m);/* get stipple */
				n = 1;			/* number first */
				while (buf[++n] == ' ');
				while (isdigit(buf[n])) n++;
				setfill(m);		/* set up stipple */
				drawwig(buf+n, fp, -1);	/* draw polygon */
D 12
				break;
E 12
I 12
				polyborder = 1;		/* assume polygons */
				break;			/*   all have borders */

E 12
E 9
			case 'g':	/* gremlin curve */
I 4
				drawwig(buf+1, fp, 0);
				break;
E 4
			case '~':	/* wiggly line */
D 4
				drawwig(buf+1);
E 4
I 4
				drawwig(buf+1, fp, 1);
E 4
I 2
				break;
E 2
D 4
			case 't':
E 4
I 4
			case 't':	/* line-thickness */
E 4
I 2
				sscanf(buf+1, "%d", &n);
				drawthick(n);
				break;
E 2
D 4
			case 's':
E 4
I 4
			case 's':	/* line-style */
E 4
I 2
				sscanf(buf+1, "%d", &n);
				drawstyle(n);
E 2
				break;
			default:
D 2
				error(FATAL, "unknown drawing function %s", buf);
E 2
I 2
				error(FATAL, "unknown drawing function %s",buf);
E 2
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
I 9
		case 'i':
			fscanf(fp, "%d", &n);
			setstip(n);
			break;
E 9
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
			/* fscanf(fp, "%d", &n); */
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
D 7
			while (getc(fp) != '\n')
				;
E 7
D 2
			t_newline();
E 2
I 2
			hpos = 0;
E 2
D 7
			break;
E 7
I 7

E 7
		case '#':	/* comment */
D 7
			while (getc(fp) != '\n')
				;
E 7
I 7
			do
				c = getc(fp);
			while (c != '\n' && c != EOF);
E 7
			break;
		case 'x':	/* device control */
D 4
			devcntrl(fp);
E 4
I 4
			if (devcntrl(fp)) return;
E 4
			break;
		default:
D 3
			error(!FATAL, "unknown input character %o %c", c, c);
D 2
			done();
E 2
I 2
			exit(0);
E 3
I 3
			error(FATAL, "unknown input character %o %c", c, c);
E 3
E 2
		}
	}
}

I 2

E 2
D 4
devcntrl(fp)	/* interpret device control functions */
FILE *fp;
E 4
I 4
int devcntrl(fp)	/* interpret device control functions */
FILE *fp;		/* returns -1 upon "stop" command */
E 4
{
        char str[20], str1[50], buf[50];
	int c, n;

	fscanf(fp, "%s", str);
	switch (str[0]) {	/* crude for now */
	case 'i':	/* initialize */
		fileinit();
D 9
		t_init(0);
E 9
I 9
		t_init();
E 9
		break;
	case 'T':	/* device name */
D 2
		fscanf(fp, "%s", devname);
		break;
E 2
	case 't':	/* trailer */
D 2
		t_trailer();
		break;
E 2
	case 'p':	/* pause -- can restart */
D 2
		t_reset('p');
		break;
E 2
D 4
	case 's':	/* stop */
E 4
D 2
		t_reset('s');
E 2
		break;
I 4
	case 's':	/* stop */
		return -1;
E 4
	case 'r':	/* resolution assumed when prepared */
D 2
		fscanf(fp, "%d", &res);
E 2
I 2
		fscanf(fp, "%d", &n);
D 12
		if (n!=RES) error(FATAL,"Input computed with wrong resolution");
E 12
I 12
		if (n!=RES) error(FATAL,"Input computed for wrong printer");
E 12
E 2
		break;
	case 'f':	/* font used */
		fscanf(fp, "%d %s", &n, str);
		fgets(buf, sizeof buf, fp);	/* in case there's a filename */
		ungetc('\n', fp);	/* fgets goes too far */
		str1[0] = 0;	/* in case there's nothing to come in */
		sscanf(buf, "%s", str1);
		loadfont(n, str, str1);
		break;
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
D 4
			break;
E 4
I 4
			return -1;
	return 0;
E 4
}

I 2

E 2
fileinit()	/* read in font and code files, etc. */
{
D 2
	int i, fin, nw;
	char *malloc(), *filebase, *p;
	char temp[60];
E 2
I 2
	register int i;
	register int fin;
	register int nw;
	register unsigned char *filebase;
	register unsigned char *p;
	unsigned char *malloc();
	char temp[100];
E 2

D 2
	/* open table for device,
	 * read in resolution, size info, font info, etc.
	 * and set params
	 */
E 2
I 2
		/* open table for device,
		 * read in resolution, size info, font info, etc.
		 * and set params
		 */
E 2

D 2
	sprintf(temp, "%s/dev%s/DESC.out", fontdir, devname);
E 2
I 2
	sprintf(temp, "%s/devip/DESC.out", fontdir);
E 2
	if ((fin = open(temp, 0)) < 0)
		error(FATAL, "can't open tables for %s", temp);
	read(fin, &dev, sizeof(struct dev));
	nfonts = dev.nfonts;
I 9
	nstips = dev.nstips;
E 9
	nsizes = dev.nsizes;
	nchtab = dev.nchtab;
	filebase = malloc(dev.filesize);	/* enough room for whole file */
	read(fin, filebase, dev.filesize);	/* all at once */
	pstab = (short *) filebase;
	chtab = pstab + nsizes + 1;
	chname = (char *) (chtab + dev.nchtab);
D 2
	p = chname + dev.lchname;
	for (i = 0; i <= nfonts; i++) {
		fontbase[i] = NULL;
		widthtab[i] = codetab[i] = fitab[i] = NULL;
E 2
I 2
	p = (unsigned char *) chname + dev.lchname;
	for (i = 1; i <= nfonts; i++) {
		fontbase[i] = (struct font *) p;
		nw = *p & BMASK;		/* 1st thing is width count */
		p += sizeof(struct font);
		widtab[i] = p;			/* then width table */
		codetab[i] = p + 2 * nw;	/* then code conversion table */
		fitab[i] = p + 3 * nw;		/* then font inclusion table */
		p += 3 * nw + dev.nchtab + 128 - 32;
		t_fp(i, fontbase[i]->namefont, fontbase[i]->intname);
#ifdef DEBUGABLE
		if (dbg > 1) fontprint(i);
#endif
E 2
	}
I 9
	for (i = 1; i <= nstips; i++) {		/* add in Stipple "filenames" */
		if (nfonts + i <= NFONT)
		    t_fp(nfonts + i, p, (char *)0);
		p += strlen(p) + 1;
	}
E 9
D 2
	close(fin);
E 2
I 2
	fontbase[0] = NULL;
	close(fin);				/* no fonts loaded yet */
	for (i = 0; i <= NFONT; i++) fontdata[i].font = fontdata[i].size = -1;
E 2
}

I 2

#ifdef DEBUGABLE
E 2
fontprint(i)	/* debugging print of font i (0,...) */
{
D 2
	int j, k, n;
E 2
I 2
	int j, n;
E 2
	char *p;

	printf("font %d:\n", i);
	p = (char *) fontbase[i];
	n = fontbase[i]->nwfont & BMASK;
	printf("base=0%o, nchars=%d, spec=%d, name=%s, widtab=0%o, fitab=0%o\n",
D 2
		p, n, fontbase[i]->specfont, fontbase[i]->namefont, widthtab[i], fitab[i]);
E 2
I 2
		p, n, fontbase[i]->specfont, fontbase[i]->namefont, widtab[i], fitab[i]);
E 2
	printf("widths:\n");
	for (j=0; j <= n; j++) {
D 2
		printf(" %2d", widthtab[i][j] & BMASK);
E 2
I 2
		printf(" %2d", widtab[i][j] & BMASK);
E 2
		if (j % 20 == 19) printf("\n");
	}
	printf("\ncodetab:\n");
	for (j=0; j <= n; j++) {
		printf(" %2d", codetab[i][j] & BMASK);
		if (j % 20 == 19) printf("\n");
	}
	printf("\nfitab:\n");
	for (j=0; j <= dev.nchtab + 128-32; j++) {
		printf(" %2d", fitab[i][j] & BMASK);
		if (j % 20 == 19) printf("\n");
	}
	printf("\n");
}
I 2
#endif
E 2

I 2

E 2
loadfont(n, s, s1)	/* load font info for font s on position n (0...) */
int n;
char *s, *s1;
{
	char temp[60];
D 2
	int fin, nw, norig;
E 2
I 2
	int fin, nw;
E 2

	if (n < 0 || n > NFONT)
		error(FATAL, "illegal fp command %d %s", n, s);
	if (fontbase[n] != NULL && strcmp(s, fontbase[n]->namefont) == 0)
		return;
I 10

	for (fin = 1; fin <= NFONT; fin++)	/* first check to see if the */
	    if (strcmp(s, fontbase[fin]->namefont) == 0) {  /* font is loaded */
		register unsigned char *c;		    /* somewhere else */

#define ptrswap(x, y) { c = (unsigned char*) (x); x = y; y = c; }
#define ptrfswap(x, y) { c=(unsigned char*)(x); x = y; y = (struct font *) c; }

		ptrfswap(fontbase[n], fontbase[fin]);
		ptrswap(codetab[n], codetab[fin]);
		ptrswap(widtab[n], widtab[fin]);
		ptrswap(fitab[n], fitab[fin]);
		t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
		t_fp(fin, fontbase[fin]->namefont, fontbase[fin]->intname);
		return;
	    }

E 10
	if (s1 == NULL || s1[0] == '\0')
D 2
		sprintf(temp, "%s/dev%s/%s.out", fontdir, devname, s);
E 2
I 2
		sprintf(temp, "%s/devip/%s.out", fontdir, s);
E 2
	else
		sprintf(temp, "%s/%s.out", s1, s);
	if ((fin = open(temp, 0)) < 0) {
		error(!FATAL, "can't open font table %s", temp);
		return;
	}
	if (fontbase[n] != NULL)
		free(fontbase[n]);
	fontbase[n] = (struct font *) malloc(3*255 + dev.nchtab +
				(128-32) + sizeof(struct font));
	if (fontbase[n] == NULL)
		error(FATAL, "Out of space in loadfont %s", s);
	read(fin, fontbase[n], 3*255 + nchtab+128-32 + sizeof(struct font));
	close(fin);
D 2
	if (smnt == 0 && fontbase[n]->specfont == 1)
		smnt = n;
E 2
	nw = fontbase[n]->nwfont & BMASK;
D 2
	widthtab[n] = (char *) fontbase[n] + sizeof(struct font);
	codetab[n] = (char *) widthtab[n] + 2 * nw;
	fitab[n] = (char *) widthtab[n] + 3 * nw;
E 2
I 2
	widtab[n] = (unsigned char *) fontbase[n] + sizeof(struct font);
	codetab[n] = (unsigned char *) widtab[n] + 2 * nw;
	fitab[n] = (unsigned char *) widtab[n] + 3 * nw;
E 2
	t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
I 2
#ifdef DEBUGABLE
E 2
	if (dbg > 1) fontprint(n);
I 2
#endif
E 2
}

D 2
cleanup()
{
	unlink(tempfile);
	exit(1);
}
E 2

D 2
error(f, s, a1, a2, a3, a4, a5, a6, a7) {
E 2
I 2
/*VARARGS2*/
error(f, s, a1, a2, a3, a4, a5, a6, a7)
int f;
char *s;
{
E 2
	fprintf(stderr, "dip: ");
	fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
	fprintf(stderr, "\n");
	if (f)
D 2
		cleanup();
E 2
I 2
D 3
		exit(1);
E 3
I 3
		exit(2);
E 3
E 2
}


D 2
/*
	Here beginneth all the stuff that really depends
	on the canon (we hope).
*/

#define	SLOP	1	/* how much positioning error is allowed? */
#define	MAXX	(8*RES + RES/2)		/* 8-1/2 inches? */
#define	MAXY	(11 * RES)
#define	WIDTH	8
#define	LOGWID	3
#define	K	* 1024	/* clever, so watch out */

char	devname[20]	= "ip";

int	nglyph		= 0;	/* number of glyphs loaded */
int	totglyph	= 0;	/* total space used by glyphs sent down */
int	maxglyph	= 28 K;	/* maximum space for glyphs */

#define	oput(c)	if (output) xychar(c); else;

/* input coordinate system: */

int	size	= 1;
int	font	= 1;		/* current font */
int	hpos;		/* horizontal position where we are supposed to be next (left = 0) */
int	vpos;		/* current vertical position (down positive) */
int	lastw	= 0;	/* width of last input character */
int	DX	= 10;	/* step size in x for drawing */
int	DY	= 10;	/* step size in y for drawing */

/* canon coordinate system: */

int	lastsize	= -1;
int	lastfont	= -1;
int	lastx		= -1;
int	lasty		= -1;
int	lastfam		= -1;

int	drawdot	= '.';	/* draw with this character */
int	drawsize = 1;	/* shrink by this factor when drawing */

E 2
D 9
t_init(reinit)	/* initialize device */
int reinit;
E 9
I 9
t_init()	/* initialize device */
E 9
{
D 2
	int i;

E 2
D 9
	if (! reinit) {
D 2
		for (i = 0; i < nchtab; i++)
			if (strcmp(&chname[chtab[i]], "l.") == 0)
				break;
		if (i < nchtab) {
			drawdot = i + 128;
			drawsize = 1;
		} else {
			drawdot = '.';
			drawsize = 2;	/* half size */
		}

		/* some Imagen-specific junk: */
		fprintf(tf, "%1d", inputarea);	/* their kludge for setting */
						/* input area to x * 8k */
		maxglyph = (68 -  inputarea - 4) K;
						/* glyph area = 68K - input */
		fprintf(tf, " %s\n\0", username);	/* terminated string */
		fprintf(tf, "%8.8s", "d_ip1/24");	/* padding 8 bytes */
						     /* ignored but needed */
E 2
I 2
		drawthick(3);		/* set the line thickness parameter */
E 2
	}
E 9
I 9
	drawthick(3);		/* set the line thickness parameter */
E 9
	hpos = vpos = 0;
	setsize(t_size(10));	/* start somewhere */
}

D 2
t_line(n, m, s)
	int n, m;
	char *s;
{
	if (m == 0) {	/* horizontal rule needed */
		if (n > 0) {
			t_rule(n, 2);
			hmot(n);	/* finish at the end */
		} else {
			hmot(n);
			t_rule(-n, 2);
		}
	} else if (n == 0) {	/* vertical rule */
		if (m > 0) {
			vmot(m);	/* finish at the end */
			t_rule(2, m);
		} else {
			t_rule(2, -m);
			vmot(m);
		}
	} else {
		drawline(n, m, s);
	}
}
E 2

I 2
/*----------------------------------------------------------------------------*
 | Routine:	t_page ( page_number )
 |
 | Results:	mark this page done for printing.  If we think we've filled
 |		the imagen too much, delete some of the info in the glyph cache.
 |		This is a good time to do this since it's at the end of a page
 |		and will get done every so often.
 *----------------------------------------------------------------------------*/

E 2
t_page(pg)	/* do whatever new page functions */
{
D 2
	register int i, j, n;
	register unsigned char *p;
	static int firstpage = 1;
E 2
I 2
	register int i;
	register int threshold;
E 2

	pageno = pg;
I 2
#ifdef DEBUGABLE
E 2
	if(dbg)fprintf(stderr, "t_page %d, output=%d\n", pg, output);
D 2
	if (output != 0) {
		/* beginning of first page, or */
		/* have just printed something, and seen p<n> for next one */
		/* ought to read in entire page, select needed glyphs */
E 2
I 2
#endif
	if (output != 0)
E 2
		putc(AEND, tf);
D 2
		firstpage = 0;
	}
E 2
	output = in_olist(pg);
I 2

E 2
	if (output) {
D 2
		if (totglyph >= maxglyph) {
			clearglyphs();
			totglyph = 0;
E 2
I 2
	    threshold = BOTTOMTHRESH;
	    while (totglyph >= maxglyph) {
		for (i = 0; i < NFONT; i++) {
		    if (fontdata[i].font != -1)
			clearglyphs(i, threshold);
E 2
		}
D 2
		acctpages++;
E 2
I 2
		threshold += DELTATHRESH;
	    }
E 2
	}
	lastx = lasty = -1;
D 9
	t_init(1);
E 9
I 9
	hpos = vpos = 0;
E 9
}

D 2
t_newline()	/* do whatever for the end of a line */
{
	hpos = 0;
}
E 2

t_size(n)	/* convert integer to internal size number*/
int n;
{
	int i;

	if (n <= pstab[0])
D 9
		return(1);
E 9
I 9
		return(0);
E 9
	else if (n >= pstab[nsizes-1])
D 2
		return(nsizes);
E 2
I 2
		return(nsizes-1);
E 2
	for (i = 0; n > pstab[i]; i++)
		;
D 2
	return(i+1);
E 2
I 2
	return(i);
E 2
}

I 2

E 2
t_charht(n)	/* set character height to n */
int n;
{
	/* punt for now */
}

I 2

E 2
t_slant(n)	/* set slant to n */
int n;
{
	/* punt for now */
}

I 2

E 2
t_font(s)	/* convert string to internal font number */
char *s;
{
	int n;

	n = atoi(s);
	if (n < 0 || n > nfonts)
		n = 1;
	return(n);
}

D 2
t_reset(c)
{
	int n;
E 2

D 2
	if (output)
		acctpages++;
}

E 2
t_wrapup()
{
	putc(AEND, tf);
	putc(AEOF, tf);
D 4
}

D 2
account()	/* record paper use */
{
/*					HIDE THIS!!!
	FILE *f = NULL;
E 2

D 2
	if (tf == stdout)
		return;
	f = fopen(acctfile, "a");
	if (f != NULL) {
		if (username == NULL)
			username = "???";
		fprintf(f, "%4d %s\n", acctpages, username);
	}
*/
}

banner(s)
	char *s;
{
	long t, time();
	char *ctime();

	time(&t);
	putc(AEND, tf); /* clean up previous page */
	setsize(16);
	loadfont(1, "CW", "");
	lastx = lasty = -1;
	vgoto(1500);
	hgoto(500);
	while (*s) {
		put1(*s++);
		hmot(128);
	}
	hmot(3*128);
	put1(' ');
	t_rule(960, 24);
	vgoto(2500);
	hgoto(2000);
	s = ctime(&t);
	while (*s) {
		put1(*s++);
		hmot(128);
	}
}

E 2
t_rule(w, h)
{
	hvflush();
	putc(ABRULE, tf);
	putint(w, tf);
	putint(h, tf);
	putint(-h, tf);
E 4
}


D 2
t_trailer()
{
}

hgoto(n)
{
	hpos = n;	/* this is where we want to be */
			/* before printing a character, */
			/* have to make sure it's true */
}

hmot(n)	/* generate n units of horizontal motion */
int n;
{
	hpos += n;
}

vgoto(n)
{
	vpos = n;
}

vmot(n)	/* generate n units of vertical motion */
int n;
{
	vgoto(vpos + n);	/* ignores rounding */
}

E 2
put1s(s)	/* s is a funny char name */
D 2
	register char *s;
E 2
I 2
register char *s;
E 2
{
	static int i = 0;

	if (!output)
		return;
I 2
#ifdef DEBUGABLE
E 2
	if (dbg) printf("%s ", s);
I 2
#endif
E 2
	if (strcmp(s, &chname[chtab[i]]) != 0)
		for (i = 0; i < nchtab; i++)
			if (strcmp(&chname[chtab[i]], s) == 0)
				break;
	if (i < nchtab)
		put1(i + 128);
	else
		i = 0;
}

I 2

E 2
put1(c)	/* output char c */
D 2
	register int c;
E 2
I 2
register int c;
E 2
{
D 2
	char *pw;
	register char *p;
	register int i, j, k;
	int ofont, code, w;
E 2
I 2
	register unsigned char *pw;
	register unsigned char *p;
	register int i;
	register int j;
	register int k;
	int ofont, code;
E 2

	if (!output)
		return;
	c -= 32;
	if (c <= 0) {
I 2
#ifdef DEBUGABLE
E 2
		if (dbg) printf("non-exist 0%o\n", c+32);
I 2
#endif
E 2
		return;
	}
D 2
	k = ofont = font;
	i = fitab[font][c] & BMASK;
E 2
I 2
	ofont = font;
	i = fitab[font][c];
E 2
	if (i != 0) {	/* it's on this font */
		p = codetab[font];
D 2
		pw = widthtab[font];
	} else if (smnt > 0) {		/* on special (we hope) */
		for (k=smnt, j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1))
			if ((i = fitab[k][c] & BMASK) != 0) {
E 2
I 2
		pw = widtab[font];
	} else {		/* on another font */
D 3
		k = 1;		/* start with ROMAN, then run down the list */
E 3
I 3
		k = font;	/* start with current, then run down the list */
E 3
		for (j=0; j++ <= nfonts; k = (k+1) % (nfonts+1))
			if (fontbase[k] != NULL && (i = fitab[k][c]) != 0) {
E 2
				p = codetab[k];
D 2
				pw = widthtab[k];
E 2
I 2
				pw = widtab[k];
E 2
				setfont(k);
				break;
			}
	}
D 2
	if (i == 0 || (code = p[i] & BMASK) == 0 || k > nfonts) {
E 2
I 2
	code = p[i] & BMASK;
	if (i == 0) {
#ifdef DEBUGABLE
E 2
		if (dbg) printf("not found 0%o\n", c+32);
I 2
#endif
E 2
		return;
	}
D 2
	lastw = pw[i] & 077;
	lastw = (lastw * pstab[size-1] + dev.unitwidth/2) / dev.unitwidth;
E 2
I 2
	lastw = (pw[i] * pstab[size] + dev.unitwidth/2) / dev.unitwidth;
#ifdef DEBUGABLE
E 2
	if (dbg) {
		if (isprint(c+32))
			printf("%c %d\n", c+32, code);
		else
			printf("%03o %d\n", c+32, code);
	} else
D 2
		oput(code);
E 2
I 2
#endif
		if (output) xychar(code);
E 2
	if (font != ofont)
		setfont(ofont);
}

I 2

E 2
setsize(n)	/* set point size to n (internal) */
int n;
{
	size = n;
}

D 2
/* font position info: */
E 2

D 2
struct {
	char *name;
	int number;
} fontname[NFONT+1];
E 2
I 2
/*----------------------------------------------------------------------------*
 | Routine:	t_fp ( number, string, string_internal )
 |
 | Results:	font position number now contains font 'string', internal
 |		font name (number) is ignored.
 |
 | Side Efct:	any fonts loaded into fontdata with this font number are
 |		removed.  And, to make sure they're not accessed, if lastfont
 |		equals number, it is "disabled" by setting lastfont to -1.
 *----------------------------------------------------------------------------*/
E 2

D 2
t_fp(n, s, si)	/* font position n now contains font s, intname si */
E 2
I 2
t_fp(n, s, si)
E 2
int n;
char *s, *si;
{
D 2
	fontname[n].name = s;
	fontname[n].number = atoi(si);
E 2
I 2
	register int i;

	fontname[n] = s;
	for (i = 0; i <= NFONT; i++)		/* release any font files */
		if (fontdata[i].font == n) {	/* for this font */
			clearglyphs (i, 1000);
			putc(AFORCE, tf);
			free (fontdata[i].cdp);
			free (fontdata[i].glyph);
			fontdata[i].font = -1;
		}
	if (n == lastfont) lastfont = -1;
E 2
}

I 2

E 2
setfont(n)	/* set font to n */
int n;
{
	if (!output)
		return;
D 9
	if (n < 0 || n > NFONT)
E 9
I 9
	if (n < 0 || n > nfonts)
E 9
		error(FATAL, "illegal font %d", n);
	font = n;
}

D 2
done()
{
	exit(0);
}
E 2

I 9
setstip(n)	/* set stipple "font" to n */
int n;
{
	if (!output)
		return;
	if (n < 1 || n > nstips)
		error(FATAL, "illegal stipple %d", n);
	stip = n;
}


E 9
D 2
/*
	The following things manage raster font information.
	The big problem is mapping desired font + size into
	available font + size.  For now, a file RASTERLIST
	contains entries like
		R 6 8 10 14 999
		I 8 10 12 999
		...
	This data is used to create an array "fontdata" that
	describes legal fonts and sizes, and pointers to any
	data from files that has actually been loaded.
*/
E 2
I 2
/*----------------------------------------------------------------------------*
 | Routine:	rd1, rd2, rd3, rd4 ( file_pointer )
 |
 | Results:	gets one, two three or four bytes from a file and interprets
 |		them as integers.  Most significant bytes come first.
 *----------------------------------------------------------------------------*/
E 2

D 2
struct fontdata {
	char	name[4];	/* e.g., "R" or "PA" */
	int	size[10];	/* e.g., 6 8 10 14 0 */
	struct	fontset	*fsp[10];	/* either NULL or block of data */
};
E 2
I 2
int rd1(fp)
FILE *fp;
{
    register int i;
E 2

D 2
#define	MAXFONT	60	/* no more than this many fonts forever */
E 2
I 2
    if((i = getc(fp)) == EOF) error(FATAL, "font file read error");
    return i;
}
E 2

D 2
struct	fontdata	fontdata[MAXFONT];
int	maxfonts	= 0;	/* how many actually used; set in initfontdata() */
E 2
I 2
int rd2(fp)
FILE *fp;
{
    register short i = rd1(fp) << 8;
E 2

D 2
struct	Fontheader	fh;
struct	fontset {
	int	size;
	int	family;
	struct	Charparam *chp;
	unsigned char	*cdp;	/* char data pointer */
	unsigned char	*chused;	/* bit-indexed; 1 if char downloaded */
};
E 2
I 2
    return i | rd1(fp);
}
E 2

D 2
/* A global variable for the current font+size */
struct	fontset	*fs;
int	nfamily		= 0;	/* number of "families" (font+size) */
E 2
I 2
int rd3(fp)
FILE *fp;
{
    register int i = rd2(fp) << 8;
E 2

D 2
initfontdata()	/* read RASTERLIST information */
E 2
I 2
    return i | rd1(fp);
}

int rd4(fp)
FILE *fp;
E 2
{
D 2
	char name[100];
	FILE *fp;
	int i, j, n;
E 2
I 2
    register int i = rd2(fp) << 16;
E 2

D 2
	sprintf(name, "%s/dev%s/RASTERLIST", fontdir, devname);
	if ((fp = fopen(name, "r")) == NULL)
		error(FATAL, "can't open %s", name);
	maxfonts = 0;
	while (fscanf(fp, "%s", fontdata[maxfonts].name) != EOF) {
		i = 0;
		while (fscanf(fp, "%d", &n) != EOF && n < 100) {
			fontdata[maxfonts].size[i] = n;
			fontdata[maxfonts].fsp[i] = NULL;
			i++;
		}
		fontdata[maxfonts].size[i] = 999;
		if (++maxfonts > MAXFONT)
			error(FATAL, "Too many fonts in RASTERLIST");
	}
	fclose(fp);
	if (dbg) {
		fprintf(stderr, "initfontdata():  maxfonts=%d\n", maxfonts);
		for (i = 0; i < maxfonts; i++) {
			fprintf(stderr, "%.4s ", fontdata[i].name);
			for (j = 0; fontdata[i].size[j] < 100; j++)
				fprintf(stderr, " %3d", fontdata[i].size[j]);
			fprintf(stderr, "\n");
		}
	}
E 2
I 2
    return i | rd2(fp);
E 2
}

D 2
getfontdata(f, s)	/* causes loading of font information if needed */
	char *f;
	int s;
E 2
I 2

/*----------------------------------------------------------------------------*
 | Routine:	getfontdata ( font, size )
 |
D 14
 | Results:	returns the family number of the font/size found.  The font
 |		information pointer, fs, is set to point to data for "font"
 |		at point size "size".  If no information for that font is
 |		available, the info is read in from the appropriate font file.
 |		The table "fontdata" holds all the fonts, and it is cleared
 |		of a random font/size if necessary.
E 14
I 14
 | Results:	returns the family number of the font/size found.  If the
 |		particular point size requested is not found, other sizes are
 |		searched for.  The font information pointer, fs, is set to
 |		point to data for "font" at point size "size".  If no infor-
 |		mation for that font is available, the info is read in from
 |		the appropriate font file.  The table "fontdata" holds all the
 |		fonts, and it is cleared of a random font/size if necessary.
E 14
 *----------------------------------------------------------------------------*/

int getfontdata(f, s)
int f;
int s;
E 2
{
D 2
	int fd, n, i, j;
E 2
	char name[100];
D 2
	static int first = 1;
E 2
I 2
	register FILE *fd;
	register int i;
	register int fam;
	register int bitbase;
	register glyph_dir *maxgp;
D 9
	register glyph_dir *mingp;
E 9
	register glyph_dir *gp;
	preamble p;
E 2

D 2
	if (first) {
		initfontdata();
		first = 0;
E 2
I 2
				/* first check if it's here already */
	for (fam = 0; fam <= NFONT; fam++)
	    if (fontdata[fam].font == f && fontdata[fam].size == s) {
		fs = &fontdata[fam];
		return (fam);
	    }
						/* find an empty slot */
	for (fam = 0; fam < NFONT && fontdata[fam].font != -1; fam++);
	fs = &fontdata[fam];
	if (fs->font != -1) {		/* clear a slot if not empty */
		clearglyphs(fam, 1000);		/* dumb version - always take */
		putc(AFORCE, tf);		/* the last one to replace */
		free(fs->glyph);
		free(fs->cdp);
E 2
	}
I 2
D 14
					/* open font file */
	sprintf(name, "%s/%s.%d", bitdir, fontname[f], pstab[s]);
	if ((fd = fopen(name, "r")) == NULL)
		error(FATAL, "can't open %s", name);
E 14
I 14

	bitbase = s;
			/* try to open font file - if unsuccessful, hunt for */
			/* a file of same style, different size to substitute */
	i = -1;	 /* direction to look in pstab (smaller first) */
	do {
	    sprintf(name, "%s/%s.%d", bitdir, fontname[f], pstab[bitbase]);
	    fd = fopen(name, "r");
	    if (fd == NULL) {		/* File wasn't found. Try another ps */
		bitbase += i;
		if (bitbase < 0) {	/* past beginning - look higher */
		    i = 1;
		    bitbase = s + i;
		}
		if (bitbase > nsizes)	/* past top - forget it */
		    i = 0;
	    }
	} while (fd == NULL && i != 0);

	if (fd == NULL)			/* completely unsuccessful */
		error(FATAL,"can't open %s/%s.%d",bitdir,fontname[f],pstab[s]);
E 14
						/* check for proper file mark */
D 3
	i = fscanf(fd, "%8s", &filemark[0]);
	if (strncmp(filemark, "Rast", 4) || i == EOF)
E 3
I 3
	for(i = 0; i < FMARK; filemark[i++] = getc(fd));
	if (strncmp(filemark, "Rast", 4))
E 3
		error(FATAL, "bad File Mark in %s.", name);
					/* get preamble */
	p.p_size = rd2(fd);
	p.p_version = rd1(fd);
	if (p.p_version)
		error(FATAL, "wrong version of Font file: %s.", name);
	p.p_glyph = rd3(fd);
D 9
	p.p_first = rd2(fd);
	p.p_last = rd2(fd);
E 9
I 9
	fs->first = p.p_first = rd2(fd);
	fs->last = p.p_last = rd2(fd);
E 9
				/* skip rest of preamble */
	i = p.p_glyph - 18;
	while (i--) getc(fd);
	fs->glyph = (glyph_dir *)	/* allocate first */
		((char *) malloc((p.p_last - p.p_first + 1) * sizeof(glyph_dir))
		- (char *) (p.p_first * sizeof(glyph_dir)));
D 6
	mingp = maxgp = gp = fs->glyph;
E 6
I 6
D 9
	mingp = maxgp = gp = &(fs->glyph[p.p_first]);
E 9
I 9
	maxgp = gp = &(fs->glyph[p.p_first]);
	bitbase = maxgp->g_bitp;
E 9
E 6
	for (i = p.p_first; i++ <= p.p_last; gp++) {
	    gp->g_height = rd2(fd);
	    gp->g_width = rd2(fd);
	    gp->g_up = rd2(fd);
	    gp->g_left = rd2(fd);
	    gp->g_pwidth = rd4(fd);
	    if ((gp->g_bitp = rd3(fd)) > maxgp->g_bitp)	/* find the glyphs */
D 9
		maxgp = gp;				/* farthest and */
	    else if(gp->g_bitp < mingp->g_bitp)		/* nearest to the */
		mingp = gp;				/* start of the file */
E 9
I 9
		maxgp = gp;				/* farthest from and */
	    else if(gp->g_bitp < bitbase)		/* nearest to the */
		bitbase = gp->g_bitp;			/* start of the file */
E 9
	}
D 9
	bitbase = mingp->g_bitp;	/* remove file offset in bit pointers */
E 9
I 9
					/* remove file offset in bit pointers */
E 9
	for (gp = fs->glyph, i = p.p_first; i++ <= p.p_last; gp++)
	    gp->g_bitp -= bitbase;
E 2

D 2
	for (i = 0; i < maxfonts; i++)
		if (strcmp(f, fontdata[i].name) == 0)
			break;
	if (i >= maxfonts)	/* the requested font wasn't there */
		i = 0;		/* use the first one (probably R) */
E 2
I 2
	i = maxgp->g_bitp + maxgp->g_height * ((maxgp->g_width + 7) / 8);
	fs->cdp = (unsigned char *) malloc(i);
	lseek(fileno(fd), (long) bitbase, 0);
	if (read(fileno (fd), fs->cdp, i) != i)
		error(FATAL, "can't read in %s", name);
	fclose(fd);
E 2

D 2
	/* find the best approximation to size s */
	for (j = 1; s >= fontdata[i].size[j]; j++)
		;
	j--;

	/* open file if necessary */
	if (fontdata[i].fsp[j] == NULL) {
		fs = (struct fontset *) malloc(sizeof(struct fontset));
		fontdata[i].fsp[j] = fs;
		fs->chp = (struct Charparam *) malloc(256*sizeof(struct Charparam));
		sprintf(name, "%s/%s.%d%s", bitdir,
			f, fontdata[i].size[j], rotate? "r" : "");
		fd = open(name, 0);
		if (fd == -1)
			error(FATAL, "can't open %s", name);
		read(fd, &fh, sizeof(struct Fontheader));
		read(fd, fs->chp, 256*sizeof(struct Charparam));
		fs->size = fontdata[i].size[j];
		fs->family = nfamily;
		nfamily += 2;	/* even-odd leaves room for big fonts */
		fs->cdp = (unsigned char *) malloc(fh.f_size);
		fs->chused = (unsigned char *) malloc(256/8);
		for (n = 0; n < 256/8; n++)
			fs->chused[n] = 0;
		n = read(fd, fs->cdp, fh.f_size);
		close(fd);
	}
	fs = fontdata[i].fsp[j];
E 2
I 2
	fs->size = s;
	fs->font = f;
	for (i = 0; i < CHARRAY; fs->chused[i++] = 0);
	return (fam);
E 2
}

I 2

I 9
/*----------------------------------------------------------------------------*
 | Routine:	setfill(stipple_number)
 |
 | Results:	sends the appropriate command to set the fill-pattern
 |		for a particular stipple.  Sends the glyph if necessary,
 |		and does nothing if the pattern is the same.  Takes stipple
 |		font from current "stip" number.
 *----------------------------------------------------------------------------*/

setfill(number)
register int number;
{
	register int fam;
	register int gsize;
	register glyph_dir *par;
	register unsigned char *p;
	register fontset *savefs;

	if (stip == laststip && number == laststipmem)
		return;

	savefs = fs;			/* getfontdata sets fs, so we have to */
					/* save it before calling getfontdata */
	fam = getfontdata(nfonts + stip, nsizes);
	laststip = stip;
	laststipmem = number;		/* must be set before call to polygon */

	if (!number || number < fs->first || number > fs->last) {
I 13
nostipbits:
E 13
		fs = savefs;		/* forget it if it's out of range */
		laststipmem = 0;	/* force NO stipple */
		return;
	}
	if (fs->chused[number] == 0) {		/* stipple not down-loaded */
D 13
		totglyph += glspace(par = &(fs->glyph[number]));
E 13
I 13
		par = &(fs->glyph[number]);
		if (!par->g_bitp)
		    goto nostipbits;
		totglyph += glspace(par);
E 13
		putc(ABGLY, tf);
		putint((fam << 7) | number, tf);
 		putint(par->g_pwidth, tf);
		putint(par->g_width, tf);
		putint(par->g_left, tf);
		putint(par->g_height, tf);
		putint(par->g_up, tf);
		gsize = ((par->g_width + 7)/8) * par->g_height;
		p = fs->cdp + par->g_bitp;
		while (gsize--)
			putc(*p++, tf);
	}
						/* mark that it's been used */
	if (fs->chused[number] != BMASK)
		fs->chused[number]++;
	putc(ASTEXTURE, tf);			/* set the texture */
	putint((fam << 7) | number, tf);
	fs = savefs;				/* return fs to proper spot */
}


E 9
E 2
xychar(c)
D 2
	register int c;
E 2
I 2
register int c;
E 2
{
	register unsigned char *p;
D 2
	register struct Charparam *par;
	register int x;
	register int y;
	int i, n, rwid, ht, fam;
E 2
I 2
	register glyph_dir *par;
	register int gsize;
E 2

D 2
	x = hpos;
	y = vpos;
E 2

I 2
	if (c >= CHARRAY) {
#ifdef DEBUGABLE
		if (dbg) error(!FATAL, "character out of range: %d 0%o", c, c);
#endif
		return;
	}
E 2
	if (font != lastfont || size != lastsize) {
D 2
		getfontdata(fontname[font].name, pstab[size-1]);
E 2
I 2
		family = getfontdata(font, size);
E 2
		lastsize = size;
		lastfont = font;
	}
D 2
	par = fs->chp + c;
	p = fs->cdp + par->c_addr;

	fam = fs->family;
	if (c > 127)
		fam++;
	if (fam != lastfam) {
E 2
I 2
	par = &(fs->glyph[c]);
	p = fs->cdp + par->g_bitp;
	if (family != lastfam) {
E 2
		putc(AF, tf);
D 2
		putc(lastfam = fam, tf);
E 2
I 2
		putc(lastfam = family ,tf);
E 2
	}

D 2
	/* first cut:  ship each glyph as needed. */
	/* ignore memory use, efficiency, etc. */

	if ( !bit(fs->chused, c) ) {	/* 1st use of this character */
		nglyph++;
E 2
I 2
	if (fs->chused[c] == 0) {	/* 1st use of this character */
E 2
		totglyph += glspace(par);
D 2
		setbit(fs->chused, c);
		putc(ASGLY, tf);
		putint((fam << 7) | c, tf);
		par->c_width = (lastw * RES) / res;
 		putc(par->c_width, tf);	/* character width */
		putc(par->c_left + par->c_right + 1, tf);
		putc(par->c_left, tf);
  /* this nonsense fixes a bug in output produced by rec.c: */
  /* when up is < 0 (and = 0?) size is one too big */
		rwid = (1 + par->c_left + par->c_right + WIDTH-1) / WIDTH;
		ht = par->c_size / rwid;
		par->c_down = ht - par->c_up;
		putc(par->c_down + par->c_up, tf);
		putc(par->c_up, tf);
		for (i = par->c_size; i--; )
E 2
I 2
D 9
		if ((fs->chused[c])++ == BMASK) fs->chused[c] = BMASK;
E 9
		putc(ABGLY, tf);
		putint((family << 7) | c, tf);
 		putint(lastw, tf);		/* use troff's width, not */
		putint(par->g_width, tf);	/* the RST character width */
		putint(par->g_left, tf);
		putint(par->g_height, tf);
		putint(par->g_up, tf);
		gsize = ((par->g_width + 7)/8) * par->g_height;
		while (gsize--)
E 2
			putc(*p++, tf);
	}
D 9

E 9
I 9
					/* note that character's been used */
	if (fs->chused[c] != BMASK)
		fs->chused[c]++;
E 9
D 2
	if (y != lasty) {
		putc(AV, tf);
		putint(y<<1, tf);
		lasty = y;
	}

	if (abs(x-lastx) > 127) {
		putc(AH, tf);
		putint(x<<1, tf);
		lastx = x + par->c_width;
	} else if (abs(x-lastx) > SLOP) {
		putc(AM, tf);
		putc(x-lastx, tf);
		putc(AM, tf);
		lastx = x + par->c_width;
	} else {
		lastx += par->c_width;
	}

	if (c <= 127)
		putc(c, tf);	/* fails if c > 127, probably disastrously */
	else
		putc(c-128, tf);
E 2
I 2
	hvflush();
	putc(c, tf);		/* guaranteed to be in range */
	lastx += lastw;		/* take account of the automatic advance */
E 2
}

D 2
hvflush()	/* force position recorded in hpos,vpos */
{
	register int x;
	register int y;
E 2

D 2
	x = hpos;
	y = vpos;
E 2
I 2
/*----------------------------------------------------------------------------*
 | Routine:	hvflush ( )
 |
 | Results:	force current position (hpos, vpos) on the imagen
 *----------------------------------------------------------------------------*/
E 2

D 2
	if (y != lasty) {
		putc(AV, tf);
		putint(y<<1, tf);
		lasty = y;
E 2
I 2
hvflush()
{
	if (vpos != lasty) {
		putc(ASETV, tf);
		putint(lasty = vpos, tf);
E 2
	}
D 2
	if (abs(x-lastx) > 127) {
		putc(AH, tf);
		putint(x<<1, tf);
		lastx = x;
	} else if (abs(x-lastx) > SLOP) {
		putc(AM, tf);
		putc(x-lastx, tf);
		putc(AM, tf);
		lastx = x;
E 2
I 2
	if (hpos != lastx) {
		putc(ASETH, tf);
		putint(lastx = hpos, tf);
E 2
	}
}

I 2

/*----------------------------------------------------------------------------*
 | Routine:	glspace ( glyph )
 |
 | Results:	returns how much space the glyph (defined by the glyph_dir
 |		entry) will take in the imagen's memory.
 *----------------------------------------------------------------------------*/

E 2
glspace(par)
D 2
	struct Charparam *par;
E 2
I 2
glyph_dir *par;
E 2
{
D 2
	int n;
E 2
I 2
	return 19 + ((par->g_width + 15) / 16 ) * (par->g_height);
}
E 2

D 2
	/* works only for small glyphs right now */
E 2

D 2
	n = 12
	  + ((par->c_left+par->c_right+1+15)/16 ) * (par->c_up+par->c_down)
	  + 2;
	return n;
}
E 2
I 2
/*----------------------------------------------------------------------------*
 | Routine:	clearglyphs ( index, limit )
 |
 | Results:	any glyphs downloaded into the imagen with a "chused" entry
 |		less than "limit" (and > 0) are marked for deletion and their
 |		space is "unrecorded" in totglyph.
 |
 | Bugs:	clearglyphs does NOT check index to make sure the family exists
 *----------------------------------------------------------------------------*/
E 2

D 2
clearglyphs()	/* remove "used" bits from all glyphs */
		/* delete all families */
		/* very conservative policy */
E 2
I 2
clearglyphs(index, limit)
int index;
int limit;
E 2
{
D 2
	int i, j, k;
	struct fontset *f;
E 2
I 2
	register fontset *f = &fontdata[index];
	register int j;
E 2

D 2
	if (tf == stdout) fprintf(stderr, "clear %d glyphs (%d/%d) on page %d\n",
		nglyph, totglyph, maxglyph, pageno);
	for (i = 0; i < maxfonts; i++)
		for (j = 0; fontdata[i].size[j] < 999; j++) {
			f = fontdata[i].fsp[j];
			if (f != NULL) {
				putc(ADELF, tf);
				putc(f->family, tf);
				for (k = 0; k < 256/8; k++)
					f->chused[k] = 0;
			}
E 2
I 2
#ifdef DEBUGABLE
	if (dbg) fprintf(stderr, "clear %d family of %d (%d/%d) on page %d\n",
			index, limit, totglyph, maxglyph, pageno);
#endif
	for (j = 0; j < CHARRAY; j++) {
		if (f->chused[j] && f->chused[j] < limit) {
			putc(ADELG, tf);
			putint(index<<7 | j, tf);
			totglyph -= glspace (&(f->glyph[j]));
			f->chused[j] = 0;
E 2
		}
I 2
	}
E 2
}

D 2
bit(p, n)	/* return n-th bit of p[] */
char *p;
int n;
{
	return (p[n/8] >> (7 - n%8)) & 01;
}

setbit(p, n)	/* set bit n of p[] */
char *p;
int n;
{
	p[n/8] |= 01 << (7 - n%8);
}
E 2

putint(n, f)
int n;
FILE *f;
{
	putc(n >> 8, f);
	putc(n & 0377, f);
}
E 1
