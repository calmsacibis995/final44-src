/*	%M%	%I%	%E%
 *
 * whole-screen Sun II (not 120) driver for device independent troff
 *
 */

 
#include <suntool/tool_hs.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "framebuf.h"
#include "dev.h"
				/***************************/
				/** suntools declarations **/
				/***************************/
static	struct screen my_screen;	/* uninitialized struct to give to */
					/* "win_screennew" call for keyboard */
					/* input while not in window system */
static	struct tool *tool;
static	struct toolsw *dsun_window;
static	int keyboard;			/* file descriptor for keyboard */
static	struct rect whole_screen = { 0, 0, 1024, 800 };

					/* structures to send to initializer */
					/* to turn off the mouse & get input */
extern struct pixrectops mem_ops;
struct pixrect null_bits = {&mem_ops, 0, 0, 1, 0};
struct cursor null_cursor = {0, 0, PIX_DST, &null_bits};
struct inputmask ascii_only;
				/*********************/
				/* dsun declarations */
				/*********************/

/* #define DEBUGABLE		/* Debugable?.. */
#define	NFONTS	60		/* total number of fonts useable */
#define	MAXSTATE 6		/* number of environments rememberable */
#define OPENREAD 0		/* mode for openning files */
#define RESTART	1		/* upon exit, return either RESTART */
#define ABORT	2		/*     or ABORT */
#define	FATAL	1		/* type of error */
#define	BMASK	0377		/* byte grabber */
#define DEVNAME	10		/* maximum characters in devicename */
#define FONTDIR	"/usr/lib/font"	/* default place to find font descriptions */
#define BITDIR "/usr/lib/font"	/* default place to look for font rasters */

#define  hmot(n)	h_pos += n
#define  hgoto(n)	h_pos = n
#define  vmot(n)	v_pos += n
#define  vgoto(n)	v_pos = n


char	SccsId[]= "%M%	%I%	%E%";

int	uninited= 1;	/* flag - has "device" been initialized? */
int	output	= 0;	/* do we do output at all? */
int	nolist	= 0;	/* output page list if > 0 */
short	olist[40];	/* pairs of page numbers */
struct	dev	dev;
struct	font	*fontbase[NFONTS+1];
short *	pstab;		/* point size table pointer */
int	nsizes;		/* number of sizes device is capable of printing */
int	nfonts;		/* number of fonts device is capable of printing */
int	nchtab;
short *	chtab;
char *	chname;
char *	fitab[NFONTS+1];	/* font inclusion table - maps ascii to ch # */
char *	widtab[NFONTS+1];	/* width table for each font */
char *	codetab[NFONTS+1];	/* device codes */
char *	fontdir = FONTDIR;	/* place to find devxxx directories */
char *	bitdir = BITDIR;	/* place to find raster fonts */
char *	fontname[NFONTS+1];	/* list of what font is on what position */
char	devname[DEVNAME];	/* printer (device) to make output for */

#ifdef DEBUGABLE
int	dbg	= 0;
#endif
int	pause	= 0;	/* flag - "should we pause at each 'P' command ?" */
int	xor	= 0;	/* flag - "should stuff on screen be `xor'ed in ?" */
short * basexPointer;	/* frame buffer base pointers - initialized in */
short * baseyPointer;	/*	t_init after calling _core_GXinit */

int	size	= 1;	/* current point size (internal pstable index) */
int	font	= 1;	/* current font - assume reasonable starting font */
int	h_pos;		/* horizontal position we are to be at next; left = 0 */
int	v_pos;		/* current vertical position (down positive) */
extern	linethickness;	/* thickness (in pixels) of any drawn object */
extern	linmod;		/* line style (a bit mask - dotted, etc.) of objects */
int	bordered= 1;	/* flag for bordering polygons (default = yes) */
int	lastw;		/* width of last character printed */


#define DISPATCHSIZE	256		/* must be a power of two */
#define CHARMASK	(DISPATCHSIZE-1)
#define DSIZ		((sizeof *dispatch)*DISPATCHSIZE)
#define OUTFILE 	fileno (stdout)

#define	RES		120		/* resolution of device (dots/"inch") */
#define RASTER_LENGTH	1024		/* device line length (pixels) */
#define RASTER_WORDS	((RASTER_LENGTH + 15 ) / 16)
#define PAGELEN		11		/* length of page (inches) */
#define NLINES		1024		/* size of actual page (pixels) */
#define SLOP_SIZE	(PAGELEN * RES - NLINES)
#define BUFFER_SIZE	(SLOP_SIZE * RASTER_WORDS)

#define BUFFTOP		(&buffer[0])
short	buffer[BUFFER_SIZE];		/* to put what won't fit on screen */
int	outres = RES;	/* resolution that original text was computed in */
int	sunres = RES;	/* resolution assumed for the console */


char *	calloc();
char *	nalloc();
char *	allpanic();
char *	operand();

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

typedef struct {
	int width, height, depth;
	short *bits;
} rast_type;

struct	fontdes {
	int	fnum;			/* if == -1, this position unused */
	int	psize;
	struct	dispatch *disp;
	char	*bits;
} fontdes[NFONTS+1];			/* is initialized at start of main */

struct dispatch *dispatch;
int	cfnum = -1;
int	cpsize = 10;
int	cfont = 1;
char	*bits;
int	fontwanted = 1;		/* flag:  "has a new font been requested?" */
int	nfontnum = -1;
int	npsize = 10;

 

main(argc, argv)
char *argv[];
{
	register FILE *fp;
	register int i;


	signal(SIGWINCH, SIG_IGN);
	init_screen();
						/* Start troff processing */

	for (i = 0; i <= NFONTS; fontdes[i++].fnum = -1);
	while (--argc > 0 && **++argv == '-') {
		switch ((*argv)[1]) {
		case 'x':
			xor = 1;
			break;
		case 'p':
			pause = 1;
			break;
		case 'r':
			i = atoi(operand(&argc, &argv));
			if (i > 0 && i < 20480) sunres = i;
			break;
		case 'F':
			bitdir = operand(&argc, &argv);
			break;
		case 'f':
			fontdir = operand(&argc, &argv);
			break;
		case 'o':
			outlist(operand(&argc, &argv));
			break;
#ifdef DEBUGABLE
		case 'd':
			dbg = atoi(operand(&argc, &argv));
			if (dbg == 0) dbg = 1;
			break;
#endif
		}
	}

	if (argc < 1)
		conv(stdin);
	else
		while (argc-- > 0) {
			if (strcmp(*argv, "-") == 0)
				fp = stdin;
			else if ((fp = fopen(*argv, "r")) == NULL)
				error(FATAL, "can't open %s", *argv);
			conv(fp);
			fclose(fp);
			argv++;
		}
	leave(0);
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
	    error (FATAL, "command-line option operand missing.");
	}
	return(*(++(*argvp)));			/* operand next word */
}


/*----------------------------------------------------------------------------*
 | Routine:	init_screen()
 |
 | Results:	
 |
 | Side Efct:	sets the global variable "tool" to be a nonzero ONLY if dsun
 |		is being run in the window system.
 |
 | Bugs:	
 *----------------------------------------------------------------------------*/

init_screen()
{
	if (!getenv("WINDOW_PARENT")) {
	    if (!(keyboard = win_screennew(&my_screen)))
		error(FATAL, "can't open screen.");
	    tool = (struct tool*) 0;
	} else {
						/* Create tool window */
	    tool = tool_create("Dsun.Tool",TOOL_NAMESTRIPE,&whole_screen,NULL);
	    if (tool == (struct tool *) NULL)
		error(FATAL, "can't create subwindow");

						/* Create i/o subwindow */
	    dsun_window = tool_createsubwindow(tool, "dsun",
				TOOL_SWEXTENDTOEDGE, TOOL_SWEXTENDTOEDGE);
	    if (dsun_window == (struct toolsw *) NULL)
		error(FATAL, "can't open subwindow");
	    keyboard = dsun_window->ts_windowfd;

					/* Install tool in tree of windows */
	    tool_install(tool);
	}
							/* Initialize i/o */
	win_setcursor(keyboard, &null_cursor);	/* no mouse */
	ascii_only.im_flags = IM_ASCII;
	win_setinputmask(keyboard, &ascii_only, &ascii_only, WIN_NULLLINK);
}


outlist(s)	/* process list of page numbers to be printed */
char *s;
{
	int n1, n2;
#ifdef DEBUGABLE
	int i;
#endif

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
	long pending;
	char str[100], buf[300];

	for (;;) {
	    if ((c = getc(fp)) != EOF) {
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
			if (fgets(buf, sizeof(buf), fp) == NULL)
			    error(FATAL, "unexpected end of input");
			t_text(buf);
			break;
		case 'D':	/* draw function */
			if (fgets(buf, sizeof(buf), fp) == NULL)
			    error(FATAL, "unexpected end of input");
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
			case 'q':	/* versatec polygon - ignore */
			    while (buf[strlen(buf) - 1] != '\n')
				if (fgets(buf, sizeof(buf), fp) == NULL)
				    error(FATAL,"unexpected end of input");
			    break;
			case 'P':	/* unbordered */
			    bordered = 0;
			case 'p':	/* polygon */
			    sscanf(buf+1, "%d", &n);
			    n = 1;
			    while(buf[n++] == ' ');
			    while(isdigit(buf[n])) n++;
			    drawwig(buf+n, fp, -1);
			    bordered = 1;
			    break;
			case '~':	/* wiggly line */
			    drawwig(buf+1, fp, 1);
			    break;
			case 'g':	/* gremlin spline */
			    drawwig(buf+1, fp, 0);
			    break;
			case 't':	/* line thickness */
			    sscanf(buf+1, "%d", &n);
			    drawthick(n);
			    break;
			case 's':	/* line style */
			    sscanf(buf+1, "%d", &n);
			    drawstyle(n);
			    break;
			default:
			    error(FATAL, "unknown drawing function %s", buf);
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
		case 'i':
			fscanf(fp, "%d", &n);
/*			setstip(n);	/* ignore for now */
			break;
		case 'H':	/* absolute horizontal motion */
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
		case 'P':	/* new spread */
			if (pause)
			    t_page(0, fp);
			break;
		case 'p':	/* new page */
			fscanf(fp, "%d", &n);
			t_page(n, fp);
			break;
		case 'n':	/* end of line */
			t_newline();
		case '#':	/* comment */
			do
			    c = getc(fp);
			while (c != '\n' && c != EOF);
			break;
		case 'x':	/* device control */
			if (devcntrl(fp)) return;
			break;
		default:
			error(FATAL, "unknown input character %o %c", c, c);
		}
	    } else {
		if (t_reset('s', fp)) return;
	    }
	}
}

int devcntrl(fp)	/* interpret device control functions */
FILE *fp;		/* returns -1 upon "stop" command */
{
        char str[20], str1[50], buf[50];
	int c, n;

	fscanf(fp, "%s", str);
	switch (str[0]) {	/* crude for now */
	case 'T':	/* output device */
		fscanf(fp, "%10s", devname);
		break;
	case 'i':	/* initialize */
		fileinit();
		t_init();
		break;
	case 't':	/* trailer */
		break;
	case 'p':	/* pause -- can restart */
		t_reset('p', fp);
		break;
	case 's':	/* stop */
		n = t_reset('s', fp);
		return n;
	case 'r':	/* resolution assumed when prepared */
		fscanf(fp, "%d", &n);
		outres = n;
		break;
	case 'f':	/* font used */
		fscanf(fp, "%d %s", &n, str);
		if (fgets(buf, sizeof buf, fp)==NULL)
		    return -1;			/* in case of filename */
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
			return -1;
	return 0;
}

/* fileinit:	read in font and code files, etc.
		Must open table for device, read in resolution,
		size info, font info, etc. and set params.
*/
fileinit()
{
	register int i;
	register int fin;
	register int nw;
	register char *filebase;
	register char *p;
	register FILE *fp;
	char	temp[100];


	sprintf(temp, "%s/dev%s/DESC.out", fontdir, devname);
	if ((fin = open(temp, 0)) < 0)
		error(FATAL, "can't open tables for %s", temp);
	if (read(fin, &dev, sizeof(struct dev)) != sizeof(struct dev))
		error(FATAL, "can't read header for %s", temp);
	nfonts = dev.nfonts;
	nsizes = dev.nsizes;
	nchtab = dev.nchtab;
	filebase = calloc(1, dev.filesize);	/* enough room for whole file */
	if (read(fin, filebase, dev.filesize) != dev.filesize)	/* at once */
		error(FATAL, "can't read width table for %s", temp);
	pstab = (short *) filebase;
	chtab = pstab + nsizes + 1;
	chname = (char *) (chtab + dev.nchtab);
	p = chname + dev.lchname;
	for (i = 1; i <= nfonts; i++) {
		fontbase[i] = (struct font *) p;
		nw = *p & BMASK;		/* 1st thing is width count */
		p += sizeof(struct font);
		widtab[i] = p;
		codetab[i] = p + 2 * nw;
		fitab[i] = p + 3 * nw;
		p += 3 * nw + dev.nchtab + 128 - 32;
		t_fp(i, fontbase[i]->namefont, fontbase[i]->intname);
#ifdef DEBUGABLE
		if (dbg > 1) fontprint(i);
#endif
	}
	while (i <= NFONTS) fontbase[i++] = (struct font *) 0;
	fontbase[0] = (struct font *)
		calloc(1,3*255 + dev.nchtab + (128-32) + sizeof (struct font));
	widtab[0] = (char *) fontbase[0] + sizeof (struct font);
	fontbase[0]->nwfont = 255;
	close(fin);
}

#ifdef DEBUGABLE
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
#endif


loadfont(n, s, s1)	/* load font info for font s on position n (0...) */
int n;
char *s, *s1;
{
	char temp[60];
	register int fin;
	register int nw;
	register int norig;

	if (n < 0 || n > NFONTS)
		error(FATAL, "illegal fp command %d %s", n, s);

	if (fontbase[n] && strcmp(s, fontbase[n]->namefont) == 0)
		return;
	for (fin = 1; fin <= NFONTS; fin++)	/* first check to see if the */
	    if (fontbase[fin] &&		/* font is loaded somewhere */
		    strcmp(s, fontbase[fin]->namefont) == 0) {	   /* else */
		register char *c;

#define ptrswap(x, y) { c = (char*) (x); x = y; y = c; }

		ptrswap(((char *) fontbase[n]), ((char *) fontbase[fin]));
		ptrswap(codetab[n], codetab[fin]);
		ptrswap(widtab[n], widtab[fin]);
		ptrswap(fitab[n], fitab[fin]);
		t_fp(n, fontbase[n]->namefont, fontbase[n]->intname);
		t_fp(fin, fontbase[fin]->namefont, fontbase[fin]->intname);
		return;
	    }

	if (s1 == NULL || s1[0] == '\0')
		sprintf(temp, "%s/dev%s/%s.out", fontdir, devname, s);
	else
		sprintf(temp, "%s/%s.out", s1, s);
				/* If the font doesn't exist, forget it */
	if ((fin = open(temp, 0)) < 0) return;

	norig = fontbase[n]->nwfont & BMASK;
	if (read(fin,fontbase[n],3*norig+nchtab+128-32+sizeof(struct font)) < 0)
		error(FATAL, "Can't read in font %s on position %d", s, n);
	if ((fontbase[n]->nwfont & BMASK) > norig)
		error(FATAL, "Font %s too big for position %d", s, n);
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


/*VARARGS1*/
error(f, s, a1, a2, a3, a4, a5, a6, a7) {
	fprintf(stderr, "dsun: ");
	fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
	fprintf(stderr, "\n");
	if (f) leave(ABORT);
}


leave(n)
{
	if (tool)		/* be graceful if in windows */
	    tool_destroy(tool);
	exit(n);
}


t_init()	/* initialize device */
{
	h_pos = v_pos = 0;

	output = 0;		/* don't output anything yet */
	setsize(t_size(10));	/* start somewhere */
	setfont(1);

	if(!_core_GXopen()) error(FATAL, "can't open display");
	GXcontrol = GXvideoEnable;
	if (xor)
	    GXfunction = GXxor;
	else
	    GXfunction = GXpaintInverted;
	GXsetMask = 0;
	basexPointer = (short *) (GXBase + GXselectX);
	baseyPointer = (short *) (GXBase + GXupdate + GXsource + GXselectY);

	uninited = 0;	/* tell t_page that the "device" is initiallized */
}


struct state {
	int	ssize;
	int	sfont;
	int	sh_pos;
	int	sv_pos;
	int	sstyle;
	int	sthick;
};
struct	state	state[MAXSTATE];
struct	state	*statep = state;

t_push()	/* begin a new block */
{
	statep->ssize = size;
	statep->sfont = font;
	statep->sstyle = linmod;
	statep->sthick = linethickness;
	statep->sh_pos = h_pos;
	statep->sv_pos = v_pos;
	if (statep++ >= state+MAXSTATE)
		error(FATAL, "{ nested too deep");
}

t_pop()	/* pop to previous state */
{
	if (--statep < state)
		error(FATAL, "extra }");
	size = statep->ssize;
	font = statep->sfont;
	h_pos = statep->sh_pos;
	v_pos = statep->sv_pos;
	linmod = statep->sstyle;
	linethickness = statep->sthick;
}


scrollup()
{
	register short *source;
	register short *dest;
	register int i;
	rast_type raster;
	short temprast[BUFFER_SIZE];


	raster.width = RASTER_LENGTH;
	raster.height = SLOP_SIZE;
	raster.depth = 1;
	raster.bits = &temprast[0];	/* top of screen to temp buffer */
	ROPcopysm(0, 0, 0, 0, &raster, RASTER_LENGTH, SLOP_SIZE);

	GXfunction = GXcopy;		/* scroll up screen */
	ROPssur(0, SLOP_SIZE, 0, 0, RASTER_LENGTH, NLINES - SLOP_SIZE);

	raster.bits = BUFFTOP;		/* extra buffer to screen */
	ROPms(0, 0, &raster, 0, NLINES - SLOP_SIZE, RASTER_LENGTH, SLOP_SIZE);

	dest = BUFFTOP;
	source = &temprast[0];		/* temp buffer to extra buffer */
	for (i = BUFFER_SIZE; i--;) *dest++ = *source++;
}


scrolldown()
{
	register short *source;
	register short *dest;
	register int i;
	rast_type raster;
	short temprast[BUFFER_SIZE];


	source = BUFFTOP;
	dest = &temprast[0];		/* extra buffer to temp buffer */
	for (i = BUFFER_SIZE; i--;) *dest++ = *source++;

	raster.width = RASTER_LENGTH;
	raster.height = SLOP_SIZE;
	raster.depth = 1;
	raster.bits = BUFFTOP;		/* bottom of screen to extra buffer */
	ROPcopysm(0, NLINES-SLOP_SIZE, 0, 0, &raster, RASTER_LENGTH, SLOP_SIZE);

	GXfunction = GXcopy;		/* scroll down screen */
	ROPssdr(0, 0, 0, SLOP_SIZE, RASTER_LENGTH, NLINES - SLOP_SIZE);

	raster.bits = &temprast[0];	/* temp buffer to screen */
	ROPms(0, 0, &raster, 0, 0, RASTER_LENGTH, SLOP_SIZE);
}


/* Here are some declarations for keeping track of pages, and moving about in
   the document.  They're ONLY used in this routine. */

#define NOPAGES 300
#define beep	putc('\007', stderr)

long	pageaddr[NOPAGES];
int	pagelimit = -1;
int	currpage;

/*----------------------------------------------------------------------------*
 | Routine:	t_page (pagenumber, filepointer)
 |
 | Results:	stops at start of each page (if pagenumber (n) is -1 then
 |		this is the end of the last page), remembers where the
 |		start of the pages are (in "pageaddr") and accepts input
 |		from the user to view the page and/or move around in the
 |		document.
 |
 | Side-Affect:	can reposition the input to just after the start of any
 |		page in the input file.
 *----------------------------------------------------------------------------*/

int t_page(n, fp)
int n;
FILE *fp;
{
	register int i;			/* random index */
	register short *ptr;		/* used to clear extra page buffer */
	register int pagenum = -1;	/* in use: -1 means no random access */
	register char character;	/* character read in from user */
	int saveres;			/* place to save sunres for prompt */
	char notice[50];		/* prompt holder */
	struct inputevent event;	/* tty_sub_window input event holder */
	struct timeval *timeout = 0;	/* dummy pointer to a timeout */


	if (uninited) return -1;
	if (n >= 0) {		/* before the last page */
	    currpage = n;
	    if (fp == stdin)	/* don't do anything if we're reading stdin */
		pagelimit = -1;
	    else {		/* remember high water mark of input file */
		if (currpage > pagelimit) pagelimit = currpage;
		if (currpage < NOPAGES && !pageaddr[currpage]) {
		    pageaddr[currpage] = ftell(fp);
		} else {	/* check for duplicate page numbers at start */
		    if (currpage > 0 && !pageaddr[currpage - 1]) {
			pageaddr[currpage - 1] = pageaddr[currpage];
			pageaddr[currpage] = ftell(fp);
		    }
		}
	    }
	} else
	    ++currpage;

	if (output) {		/* page has been printed */
	    saveres = sunres;
	    sunres = RES;
	    sprintf (notice, "%sage %d:", n>=0 ? "P" : "Last p", currpage-1);
	    hgoto(outres / 10);	 /* move to 1/10" from left edge */
	    vgoto(outres / 3);	 /*   and 1/3" from top of screen */
	    setsize(t_size(10)); /*   change to 10 point in currrent font */
	    t_text(notice);	 /*   and print the message */
	    sunres = saveres;

	    i = 2;	/* number of times to scroll before going on to */
	    do {	/*   the next page if user hits spaces */
				/* get a character from window system */
		if (input_readevent(keyboard, &event)) {
		    perror("dsun");
		    leave(1);
		}
		character = event.ie_code;	/* character now has input */

		if (character == ' ') {
		    if (i > 0)
			character = 'u';
		    else
			character = 012;
		}
		switch (character) {
		    case '':		/* reset with 'escape' */
			pagenum = -1;
			break;

		    case 'u':		/* scroll up */
		    case 'A':		/* or up arrow */
			i--;		/* count scrolls */
			scrollup();
			break;

		    case 'd':		/* scroll down */
		    case 'B':		/* or down arrow */
			scrolldown();
			break;

		    case 'C':		/* right arrow - to next page */
			nolist = 0;		/* forget any list of pages */
		    case 012:		/* CR/LF - next requested page */
		    case 015:
			character = 0;
			break;

		    case 'D':		/* back one page */
		    case 'b':
			if (currpage > 1) {
			    nolist = 0;		/* forget any list of pages */
			    if (pageaddr[currpage - 2]) {
				fseek(fp, pageaddr[n = (currpage -= 2)], 0);
				character = 0;
			    } else
				beep;
			} else
			    beep;
			break;

					/* gather a page number to move to */
		    case '0': case '1': case '2': case '3': case '4':
		    case '5': case '6': case '7': case '8': case '9':
			if (pagenum < 0) pagenum = 0;
			pagenum = 10 * pagenum + character - '0';
			break;

		    case '$':		/* go to last page */
			pagenum = 9999;
		    case 'g':		/* go to certain page */
		    case 'G':
		    case 'p':
			if (pagenum >= 0 && pagelimit >= 0) {
			    if (pagenum <= pagelimit) {
				nolist = 0;
				fseek(fp, pageaddr[currpage = pagenum], 0);
			    } else {
				if (currpage < pagelimit)
				    fseek(fp, pageaddr[currpage=pagelimit], 0);
				nolist = 1;
				olist[0] = pagenum;
				olist[1] = 9999;
			    }
			    n = character = 0;
			} else
			    beep;
			break;

		    case 19:		/* ^X */
		    case 3:		/* ^C */
		    case 127:		/* "break" */
		    case 'q':		/* quit */
			leave(0);
			break;

		    case 26:		/* ^Z = suspend */
			if (tool) {
			    tool_destroy(tool);
			} else {
			    close (keyboard);
			}
			kill (0, SIGTSTP);
			init_screen();
			character = 0;
			break;
		}
	    } while (character);
	} else if (n < 0) {
	    fseek(fp, pageaddr[--currpage], 0);
	    nolist = 0;		/* don't mask off any pages */
	    n = 0;		/* this is NOT the last page */
	}

	v_pos = 0;

	if (n >= 0) {
	    ptr = BUFFTOP;		/* clear out page buffer and screen */
	    i = BUFFER_SIZE;
	    while (i--) *ptr++ = 0xffff;
	    GXfunction = GXset;
	    ROPds(0, 0, 1024, 1024);
	    if (xor)			/* function reset ONCE here; */
		GXfunction = GXxor;
	    else
		GXfunction = GXpaintInverted;
	}				/* it needn't be done for each glyph */

	output = 1;
	if (nolist != 0) {		/* -o specified */
	    output = 0;
	    for (i = 0; i < nolist; i += 2)
		if (n >= olist[i] && n <= olist[i+1]) {
			output = 1;
			break;
		}
	}
	return  (n < 0);
}


t_newline()	/* do whatever for the end of a line */
{
	h_pos = 0;	/* because we're now back at the left margin */
}


t_size(n)	/* convert integer to internal size number*/
int n;
{
	int i;

	if (pstab == (short *) 0) return(1);

	if (n <= pstab[0])
		return(0);
	else if (n >= pstab[nsizes - 1])
		return(nsizes - 1);
	for (i = 0; n > pstab[i]; i++)
		;
	return(i);
}

/*ARGSUSED*/
t_charht(n)	/* set character height to n */
int n;
{
#ifdef DEBUGABLE
	if (dbg) error(!FATAL, "can't set height on suns");
#endif
}

/*ARGSUSED*/
t_slant(n)	/* set slant to n */
int n;
{
#ifdef DEBUGABLE
	if (dbg) error(!FATAL, "can't set slant on suns");
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


int t_reset(c, fp)
int c;
FILE *fp;
{	
	switch(c){
	case 's':
		c = t_page(-1, fp);
		break;
	}
	return c;
}


put1s(s)	/* s is a funny char name */
char *s;
{				/* --- Notice:  BIG KLUDGE --- */
	int i;		/* \^ and \| are special cases that can NOT be */
			/* printed because they have output code == 0 */
	if (!output || (s[0] == '\\' && (s[1] == '^' || s[1] == '|')))
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
 		lastw = (widtab[font][0] * pstab[size] + dev.unitwidth/2)
								/ dev.unitwidth;
		return;
	}
	k = ofont = font;
	i = fitab[font][c] & BMASK;
	if (i != 0) {			/* it's on this font */
		p = codetab[font];	/* get the printing value of ch */
		pw = widtab[font];	/* get the width */
	} else		/* on another font (we hope) */
		for (j=0; j <= nfonts; j++, k = (k+1) % (nfonts+1)){
			if (fitab[k] == 0)
				continue;
			if ((i = fitab[k][c] & BMASK) != 0) {
				p = codetab[k];
				pw = widtab[k];
				setfont(k);
				break;
			}
		}

	if (i == 0) {
#ifdef DEBUGABLE
		if (dbg) fprintf(stderr,"not found 0%o\n", c+32);
#endif
		return;
	}
	code = p[i] & BMASK;
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
	lastw = ((pw[i]&0177) * pstab[size] + dev.unitwidth/2) / dev.unitwidth;
}


setsize(n)	/* set point size to n (internal) */
int n;
{
	if (n == size)
		return;	/* already there */
	if (vloadfont(font, pstab[n]) != -1)
		size = n;
}

/*ARGSUSED*/
t_fp(n, s, si)	/* font position n now contains font s, intname si */
int n;		/* internal name is ignored */
char *s, *si;
{
	register int i;


	fontname[n] = s;
	for(i = 0;i <= NFONTS;i++)	/* free the bits of that font */
		if (fontdes[i].fnum == n){
			nfree(fontdes[i].bits);
			fontdes[i].fnum = -1;
		}
}

setfont(n)	/* set font to n */
int n;
{
	if (n < 0 || n > NFONTS)
		error(FATAL, "illegal font %d", n);
	if (pstab != (short *) 0)
	    if (vloadfont(n,pstab[size]) != -1)
		font = n;
}

vloadfont(fnum, fsize)
register int fnum;
register int fsize;
{
	register int i;

	fontwanted = 0;
	if (fnum == cfnum && fsize == cpsize)
		return(0);
	for (i = 0; i <= NFONTS; i++) {
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
	if (fnum < 0 || fnum > NFONTS || fontname[fnum] == 0) {
#ifdef DEBUGABLE
	    if (dbg) error(!FATAL, "illegal font %d size %d", fnum, fsize);
#endif
	    return(-1);
	}
		/* Need to verify the existance of that font/size here */
	nfontnum = fnum;
	npsize = fsize;
	fontwanted++;
	return (0);
}


findfont(device, cbuf)
char *device;
char *cbuf;
{
	register int fnum;
	register int fsize;
	register int fontd;
	register int d;
	register int sizehunt = size;


	fnum = nfontnum;
	fsize = npsize;
			/* try to open font file - if unsuccessful, hunt for */
			/* a file of same style, different size to substitute */
	d = -1;	/* direction to look in pstab (smaller first) */
	do {
	    sprintf(cbuf,"%s/dev%s/%s.%d",bitdir,device,fontname[fnum],fsize);
	    fontd = open(cbuf, OPENREAD);
	    if (fontd == -1) {		/* File wasn't found. Try another ps */
		sizehunt += d;
		if (sizehunt < 0) {	/* past beginning - look higher */
		    d = 1;
		    sizehunt = size + 1;
		}
		if (sizehunt > nsizes) {	/* past top - forget it */
		    d = 0;
		} else {
		    fsize = pstab[sizehunt];
		}
	    }
	} while (fontd == -1 && d != 0);
	return fontd;
}


getfont()
{
	register int fnum;
	register int fsize;
	register int fontd;
	register int d;
	char cbuf[BUFSIZ];


	fnum = nfontnum;
	fsize = npsize;
			/* try to open font file in target machine's area. */
			/* if unsuccessful, hunt in for one in bitdir */
	if ((fontd = findfont(devname, cbuf)) == -1)
	    fontd = findfont("sun", cbuf);

	if (fontd == -1) {		/* completely unsuccessful */
#ifdef DEBUGABLE
	    perror(cbuf);
	    error(!FATAL,"fnum = %d, psize = %d, name = %s",
		fnum, npsize, fontname[fnum]);
#endif
	    fontwanted = 0;
	    return (-1);
	}
	if (read(fontd, &header, sizeof  (header)) != sizeof (header)
						|| header.magic != 0436)
		fprintf(stderr, "%s: Bad font file", cbuf);
	else {
		cfont = relfont();
		if ((bits=nalloc((header.size+DSIZ+2)/2,2))== NULL)
			if ((bits=allpanic(((header.size+DSIZ+2)/2)*2))==NULL) {
				error(FATAL, "%s: ran out of memory", cbuf);
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
	if (fontdes [newfont].fnum == -1)
	    break;
    if (fontdes [newfont].fnum != -1) {
	nfree (fontdes [newfont].bits);
#ifdef DEBUGABLE
	if (dbg) fprintf (stderr, "freeing position %d\n", newfont);
    } else {
	if (dbg)
	    fprintf (stderr, "taking, not freeing, position %d\n", newfont);
#endif
    }
    fontdes[newfont].fnum = -1;
    return (newfont);
}

char *allpanic (nbytes)
int nbytes;
{
	register int i;

	for (i = 0; i <= NFONTS; i++) {
		if (fontdes[i].fnum != -1) nfree(fontdes[i].bits);
		fontdes[i].fnum = fontdes[i].psize = -1;
		cfnum = cpsize = -1;
	}
	return(nalloc((nbytes+1)/2,2));
}


outc(code)
int code;		/* character to print */
{
    struct dispatch *dis;	/* ptr to character font record */
    int x;			/* x position in page */
    int y;			/* y position in page */
    int hite;			/* height (stores height for use twice) */
    rast_type raster;		/* raster to send to ROPms */

    if (fontwanted)
	if (getfont()) return;
    dis = dispatch + code;

    if (dis->nbytes) {
	x = ((h_pos * sunres) / outres) - dis->left;
	y = ((v_pos * sunres) / outres) - dis->up;
	raster.bits = (short *) (bits + dis->addr);
	raster.width = dis->left + dis->right;
	raster.height = hite = dis->up + dis->down;
	raster.depth = 1;
				/* if ANY part of raster is off the "page" */
				/* then forget about this character */
	if (x + raster.width > RASTER_LENGTH || x < 0
		|| y + raster.height > SLOP_SIZE + NLINES || y < 0) return;

				/* if at least part of raster will fit on */
	if (y < NLINES) {	/* the screen do the raster-to-screen move */
			
		if (y + raster.height > NLINES)		/* truncate a raster */
			raster.height = NLINES - y;	/* that passes bottom */

		ROPms(0, 0, &raster, x, y, raster.width, raster.height);
	}

	if (y + hite > NLINES) {	/* if (at least part of) raster will */
					/* fit onto the buffer, put it there */
		register short *daddr = BUFFTOP+(y-NLINES)*RASTER_WORDS+(x>>4);
		register short *saddr = raster.bits;
		register short roffset = x & 15;
		register short loffset = 16 - roffset;
		register short rmask = 0xffff >> roffset;
		register short lmask = ~rmask;

		raster.width = (raster.width + 15) / 16;

		while (daddr < BUFFTOP) {
			daddr += RASTER_WORDS;
			saddr += raster.width;
			hite--;
		}
		while (hite-- > 0) {
		    for (x = raster.width; x-- > 0; ) {
			*(daddr++) &= ~((*saddr >> roffset) & rmask);
			*daddr &= ~((*(saddr++) << loffset) & lmask);
		    }
		    daddr += RASTER_WORDS - raster.width;
		}
	}
    }
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
 * Plot a dot at (x, y).  Points must be in the range 0 <= x < RASTER_LENGTH,
 * 0 <= y < SLOP_SIZE + NLINES.  If the point will not fit on the buffer,
 * it is left out.
 */
point(sun_x, sun_y)
register int sun_x;
register int sun_y;
{
				/* check to see if point is off page entirely */
    if (((unsigned) sun_y) >= (NLINES + SLOP_SIZE)
	|| ((unsigned) sun_x) >= RASTER_LENGTH) return;
    
    if (sun_y < NLINES) {	/* on screen */

	GXwidth = 1;		/* set width of "raster" to 1 for one pixel */

	*((short *) (basexPointer + sun_x)) = 1;
	*((short *) (baseyPointer + sun_y)) = 0x8000;
    } else {			/* off screen, on extra buffer */
	*(BUFFTOP + (sun_y - NLINES) * RASTER_WORDS + (sun_x >> 4))
						&= 0xffff7fff >> (sun_x & 15);
    }
}


/*
 * Routine to scale points for graphical routines.
 */
int scale(n)
register int n;
{
    return ((n * sunres) / outres);
}


/*----------------------------------------------------------------------------*
 | Routine:	polygon (x_coordinates, y_coordinates, num_points)
 |
 | Results:	draws the outline of the polygon delimited by the coordinates
 |		in (x[1], y[1]) -> (x[npts], y[npts]).
 |
 | Bugs:	does not fill.
 *----------------------------------------------------------------------------*/

polygon(x, y, npts)
int x[];
int y[];
int npts;
{
    register int i;	/* random int */

			/* do this whether or not the polygon is bordered */
/*  if (bordered) {  */
	for (i = 1; i < npts; i++)		/* first draw outlines */
	    HGtline(x[i], y[i], x[i+1], y[i+1]);
/*  }  */
}
