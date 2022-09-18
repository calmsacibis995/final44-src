/*	%M%	%I%	%E%
 *
 * whole-screen Sun II (not 120) driver for device independent troff
 *
 * Dsun.tool
 * This is the main program for dsun.tool, a window version 
 * of the program dsun written by David Slattengren. 
 *
 * Author: Brian D. Marsh (with much code from dsun)
 * May 30, 1985
 *
 */

 
#include "dsun.tool.hs_h"
#include "icon.h"
				/***************************/
				/** suntools declarations **/
				/***************************/
struct screen my_screen;	/* uninitialized struct to give to */
					/* "win_screennew" call for keyboard */
					/* input while not in window system */

					/* structures to send to initializer */
					/* to turn off the mouse & get input */

	/*****************************************/
	/* Declarations for globals for dsun.tool*/
	/*****************************************/

struct tool 	    *	tool;
struct toolsw       * 	dsun_window;		/* Window for dsun */
int keyboard;					/* file descriptor for keyboard */
struct rect whole_screen = { 0, 0, 800, 750 };


struct pixwin 	    * 	dsun_pw;		/* Pixwin to which output goes */
int dsun_pid;					/* Process number of the child
						 * that produces bit maps.
						 */
struct page * curr_dis_pg, * curr_proc_pg;	/* Pages being displayed and
						 * processed.
						 */
int	curr_dis_pgno, curr_proc_pgno, pg_desired;
int 	offset;
int	io_pending;			/* There is io on the file descriptore */
extern int verbose;			/* Print out debugging statements ? */


extern struct pixrectops mem_ops;
struct pixrect null_bits = {&mem_ops, 0, 0, 1, 0};
struct cursor null_cursor = {0, 0, PIX_DST, &null_bits};
struct inputmask im;

struct	menuitem items[] = {
	MENU_IMAGESTRING,	"Spelling ",	  ROOT_TTY,
	MENU_IMAGESTRING,	"Punctuation",	  ROOT_CRT,
	MENU_IMAGESTRING,	"Exit",		  ROOT_QUIT,
	MENU_IMAGESTRING,	"Comment",        ROOT_REFRESH
};

struct	menu wmgr_rootmenubody = {
	MENU_IMAGESTRING,
	"Root Mgr",
	sizeof(items) / sizeof(struct menuitem),
	items,
	0,
	0
};
struct	menu *wmgr_rootmenu = &wmgr_rootmenubody;

				/*********************/
				/* dsun declarations */
				/*********************/




char	SccsId[]= "%M%	%I%	%E%";

int	nolist	= 0;	/* output page list if > 0 */
extern int output;	/* Are we outputting to the screen or not */
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
int 	crop	= 1;
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

int	outres = RES;	/* resolution that original text was computed in */
int	sunres = RES;	/* resolution assumed for the console */


char *	calloc();
char *	nalloc();
char *	allpanic();
char *	operand();

struct  pixrect * dprect;
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


						/* Start troff processing */

	for (i = 0; i <= NFONTS; fontdes[i++].fnum = -1);
	while (--argc > 0 && **++argv == '-') {
		switch ((*argv)[1]) {
		case 'n':
			crop = 0;	/* For normal processing 
					 * we don't crop.
					 */
			break;
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

	/* Create tool window */
	tool = tool_create("Dsun.Tool",TOOL_NAMESTRIPE | TOOL_BOUNDARYMGR,
				&whole_screen, &icon);


	if (tool == (struct tool *) NULL)
		error(FATAL, "can't create subwindow");

	init_screen(crop);

	if (argc < 1)
		page_control(stdin,0);		/* take input from a pipe */
	else
		while (argc-- > 0) {
			if (strcmp(*argv, "-") == 0)
				fp = stdin;
			else if ((fp = fopen(*argv, "r")) == NULL)
				error(FATAL, "can't open %s", *argv);
			page_control(fp,argc);
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
	struct pixrect * tmp_pr;	/* Temp for outputting different sizes
					 * of the current screen.
					 */

	for (;;) {
/*
 * If input has occurred then we want to handle it as soon as possible
 * since this is supposed to be a real time dsun.
 */
	    if (io_pending){
		curr_proc_pg->temp_loc = ftell(fp);
		curr_proc_pg->v_pos = v_pos;
		curr_proc_pg->h_pos = h_pos;
		curr_proc_pg->font = font;
		curr_proc_pg->size = size;
		return;
	    }


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
			hgoto(k - curr_proc_pg->min_h_pos);
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
			    return;
			curr_proc_pg->done++;

		case 'p':	/* new page */
			fscanf(fp, "%d", &n);
			curr_proc_pg->done++;
			return;

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
		curr_proc_pg->done = 1;
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

	p = (char *) fontbase[i];
	n = fontbase[i]->nwfont & BMASK;
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


/*
 * Only used to cause the parent to die.
 */
leave(n)
{
	kill(0, SIGCHLD);
	exit(0);
}


t_init()	/* initialize device */
{
	h_pos = v_pos = 0;

	setsize(t_size(10));	/* start somewhere */
	setfont(1);

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


/*
 * I don't know what this does so right now, it'll do nothing.
 */
int t_reset(c, fp)
int c;
FILE *fp;
{	
	switch(c){
	case 's':
		c = 1;
		break;
	}
	return c;
}


put1s(s)	/* s is a funny char name */
char *s;
{				/* --- Notice:  BIG KLUDGE --- */
	int i;		/* \^ and \| are special cases that can NOT be */
			/* printed because they have output code == 0 */
	if ((s[0] == '\\' && (s[1] == '^' || s[1] == '|')))
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


char *
nalloc(i, j)
int i, j;
{
	register char *cp;

	cp = calloc(i, j);
#ifdef DEBUGABLE
fprintf(stderr, "allocated %d bytes at %x\n", i * j, cp);
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
    
/*
 * In dsun they had to check whether or not the point would be on the screen
 * or if it should be stored in the off screen buffer.
 * In dsun.tool we couldn't care less since the image is actually being
 * written to a memory pixrect : curr_proc_pg->pg_image.
 */

    pr_put(curr_proc_pg->pg_image, sun_x, sun_y, 1);

    if (output)
	pw_put(dsun_pw, sun_x, sun_y - offset, 1);


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
