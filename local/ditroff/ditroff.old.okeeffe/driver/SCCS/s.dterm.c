h19907
s 00009/00004/01078
d D 1.14 85/02/26 13:50:20 slatteng 16 15
c added makefile-defined font directory
e
s 00020/00003/01062
d D 1.13 84/08/06 17:29:43 slatteng 15 14
c added -a option (and fixed text printing)
e
s 00006/00000/01059
d D 1.12 84/05/17 13:46:08 slatteng 14 12
c add unbordered polygons and ignoreable versatec ('q') polygons
e
s 00005/00000/01059
d R 1.12 84/05/17 13:40:32 slatteng 13 12
c add unbordered polygons and versatec (q) polygons to ignore.
e
s 00019/00006/01040
d D 1.11 84/04/13 16:35:12 slatteng 12 10
c added polygons (no stipple)
e
s 00022/00006/01040
d R 1.11 84/04/13 15:36:10 slatteng 11 10
c add polygons and stipples
e
s 00012/00018/01034
d D 1.10 84/04/05 11:28:07 slatteng 10 9
c put in | for vertical lines, - for horizontal lines.
e
s 00001/00001/01051
d D 1.9 83/12/26 14:56:07 slatteng 9 8
c change font directory to be /usr/local/lib...
e
s 00014/00002/01038
d D 1.8 83/10/22 15:19:52 slatteng 8 7
c add -m option, also add 'P' into output language - allows seeing sorted files
e
s 00002/00002/01038
d D 1.7 83/09/07 13:27:36 slatteng 7 6
c fixed bug in reading in special character table.
e
s 00039/00016/01001
d D 1.6 83/08/23 15:16:17 slatteng 6 5
c use better general option operand grabber
e
s 00021/00011/00996
d D 1.5 83/08/23 13:22:39 slatteng 5 4
c added ^L option, fixed DP calculation, increased size of page buffer
e
s 00071/00031/00936
d D 1.4 83/08/15 17:29:25 slatteng 4 3
c changed special characters to a file read in at startup.
e
s 00005/00002/00962
d D 1.3 83/08/04 13:22:38 slatteng 3 2
c updated the special character table
e
s 00002/00002/00962
d D 1.2 83/07/24 17:22:23 slatteng 2 1
c fixed wide-mode scaling factors
e
s 00964/00000/00000
d D 1.1 83/07/24 12:43:31 slatteng 1 0
c date and time created 83/07/24 12:43:31 by slatteng
e
u
U
t
T
I 1
/* %W%	(Berkeley)	%G%"
 *
 *	Converts ditroff output to text on a terminal.  It is NOT meant to
 *	produce readable output, but is to show one how one's paper is (in
 *	general) formatted - what will go where on which page.
 *
 *	options:
 *
 *	  -hn	set horizontal resolution to n (in characters per inch;
 *		default is 10.0).
 *
 *	  -vn	set vertical resolution (default is 6.0).
 *
 *	  -ln	set maximum output line-length to n (default is 79).
 *
 *	-olist	output page list - as in troff.
 *
 *	  -c	continue at end of page.  Default is to stop at the end
 *		of each page, print "dterm:" and wait for a command.
 *		Type ? to get a list of available commands.
 *
I 8
 *	  -m	print margins.  Default action is to cut printing area down
 *		to only the part of the page with information on it.
 *
I 15
 *	  -a	make the output readable - i.e. print like a "troff -a" with
 *		no character overlap, and one space 'tween words
 *
E 15
E 8
D 6
 *	  -w	sets h = 20, v = 12, l = 131, also sets -c to allow for 
 *		extra-wide printouts on the printer.
E 6
I 6
 *	  -L	put a form feed (^L) at the end of each page
E 6
I 4
 *
I 6
D 8
 *	  -w	sets h = 20, v = 12, l = 131, also sets -c and -L to allow
E 8
I 8
 *	  -w	sets h = 20, v = 12, l = 131, also sets -c, -m and -L to allow
E 8
 *		for extra-wide printouts on the printer.
 *
E 6
 *	-fxxx	get special character definition file "xxx".  Default is
D 16
 *		/usr/lib/font/devter/specfile.
E 16
I 16
 *		FONTDIR/devter/specfile.
E 16
E 4
 */


#include	<stdio.h>
#include	<ctype.h>
#include	<math.h>


#define	FATAL		1
D 5
#define	PGWIDTH		133
#define	PGHEIGHT	110
E 5
I 5
#define	PGWIDTH		266		/* WAY too big - for good measure */
#define	PGHEIGHT	220
E 5
#define LINELEN		78
I 4
D 9
#define SPECFILE	"/usr/lib/font/devter/specfile"
E 9
I 9
D 16
#define SPECFILE	"/usr/local/lib/font/devter/specfile"
E 16
I 16
#define SPECFILE	"devter/specfile"
#ifndef FONTDIR
#define FONTDIR		"/usr/lib/font"
#endif
E 16
E 9
E 4

#define hgoto(n)	hpos = n
#define vgoto(n)	vpos = n
#define hmot(n)		hpos += n
#define vmot(n)		vpos += n

#define	sgn(n)		((n > 0) ? 1 : ((n < 0) ? -1 : 0))
#define	abs(n)		((n) >= 0 ? (n) : -(n))
#define	max(x,y)	((x) > (y) ? (x) : (y))
#define	min(x,y)	((x) < (y) ? (x) : (y))
D 10
#define	arcmove(x,y)	{ hgoto(x); vmot(-vpos-(y)); }
E 10
#define sqr(x)		(long int)(x)*(x)


char	SccsId [] = "%W%	(Berkeley)	%G%";

I 3
D 4
			/* here're the special characters... */
E 3
char *spectab[] ={
	"em", "-", "hy", "-", "en", "-", "ru", "_", "l.", ".", "L.", ".",
D 3
	"br", "|", "vr", "|", "fm", "'", "or", "|",
	0, 0,
E 3
I 3
	"br", "|", "vr", "|", "fm", "'", "or", "|", "ga", "`", "aa", "'",
	"ul", "_", "\\_","_", "pl", "+", "mi", "-", "eq", "=", "ap", "~",
	"sl", "/", "bv", "|",
	0, 0
E 3
};
E 4
I 4
char	**spectab;		/* here go the special characters */
D 16
char	*specfile = SPECFILE;	/* place to look up special characters */
E 16
I 16
char	specfile[100] = FONTDIR;/* place to look up special characters */
E 16
char	*malloc();
I 6
char	*operand();
E 6
E 4

D 4
int 	keepon	= 0;	/* flag:  Do we not stop at the end of each page? */
int	output	= 0;	/* do we do output at all? */
int	nolist	= 0;	/* output page list if > 0 */
int	olist[20];	/* pairs of page numbers */
E 4
I 4
D 5
int 	keepon	= 0;		/* flag:  Don't stop at the end of each page? */
int	output	= 0;		/* do we do output at all? */
int	nolist	= 0;		/* output page list if > 0 */
E 5
I 5
int 	keepon	= 0;	/* flags:  Don't stop at the end of each page? */
int	clearsc = 0;		/* Put out form feed at each page? */
int	output	= 0;		/* Do we do output at all? */
int	nolist	= 0;		/* Output page list if > 0 */
I 8
int	margin	= 0;		/* Print blank margins? */
I 15
int	ascii	= 0;		/* make the output "readable"? */
E 15
E 8
E 5
int	olist[20];		/* pairs of page numbers */
E 4

D 4
float	hscale	= 10.0;	/* characters and lines per inch for output device */
float	vscale	= 6.0;	/*	(defaults are for printer) */
FILE	*fp = stdin;	/* input file pointer */
E 4
I 4
float	hscale	= 10.0;		/* characters and lines per inch for output */
float	vscale	= 6.0;		/*	device (defaults are for printer) */
FILE	*fp = stdin;		/* input file pointer */
E 4

char	pagebuf[PGHEIGHT][PGWIDTH];
int	minh	= PGWIDTH;
int	maxh	= 0;
int	minv	= PGHEIGHT;
int	maxv	= 0;
int	linelen = LINELEN;

int	hpos;		/* horizontal position to be next (left = 0) */
int	vpos;		/* current vertical position (down positive) */

int	np;		/* number of pages seen */
int	npmax;		/* high-water mark of np */
int	pgnum[40];	/* their actual numbers */
long	pgadr[40];	/* their seek addresses */

D 4
int	DP	= 10;	/* step size for drawing */
int	drawdot	= '.';	/* draw with this character */
int	drawsize = 1;	/* shrink by this factor when drawing */
E 4
I 4
int	DP;			/* step size for drawing */
D 10
int	drawdot = '.';		/* draw with this character */
E 10
E 4
D 5
int	maxdots	= 32000;	/* maximum number of dots in an object */
E 5
I 5
int	maxdots	= 3200;		/* maximum number of dots in an object */
E 5



main(argc, argv)
int argc;
char **argv;
{
I 16
	strcat(specfile, "/");
	strcat(specfile, SPECFILE);
E 16
D 6
	argv++;
	while (argc > 1 && **argv == '-') {
	    switch (*(++*argv)) {
E 6
I 6
	while (--argc > 0 && **++argv == '-') {
	    switch ((*argv)[1]) {
E 6
D 4
		case 'l':
E 4
I 4
		case 'f':		/* special character filepath */
D 6
			specfile = ++*argv;
E 6
I 6
D 16
			specfile = operand(&argc, &argv);
E 16
I 16
			strncpy(specfile, operand(&argc, &argv), 100);
E 16
E 6
			break;
		case 'l':		/* output line length */
E 4
D 6
			linelen = atoi(++*argv) - 1;
E 6
I 6
			linelen = atoi(operand(&argc, &argv)) - 1;
E 6
			break;
D 4
		case 'h':
E 4
I 4
		case 'h':		/* horizontal scale (char/inch) */
E 4
D 6
			hscale = atof(++*argv);
E 6
I 6
			hscale = atof(operand(&argc, &argv));
E 6
			break;
D 4
		case 'v':
E 4
I 4
		case 'v':		/* vertical scale (char/inch) */
E 4
D 6
			vscale = atof(++*argv);
E 6
I 6
			vscale = atof(operand(&argc, &argv));
E 6
			break;
D 4
		case 'o':
E 4
I 4
		case 'o':		/* output list */
E 4
D 6
			outlist(++*argv);
E 6
I 6
			outlist(operand(&argc, &argv));
E 6
			break;
D 4
		case 'c':
E 4
I 4
D 5
		case 'c':		/* continue (^L too) at endofpage */
E 5
I 5
		case 'c':		/* continue at endofpage */
E 5
E 4
D 6
			keepon = 1;
E 6
I 6
			keepon = !keepon;
E 6
			break;
I 8
		case 'm':		/* print margins */
			margin = !margin;
			break;
I 15
		case 'a':		/* readable mode */
			ascii = !ascii;
			break;
E 15
E 8
D 4
 		case 'w':
E 4
I 4
D 5
 		case 'w':		/* "wide" format */
E 5
I 5
		case 'L':		/* form feed after each page */
D 6
			clearsc = 1;
E 6
I 6
			clearsc = !clearsc;
E 6
			break;
 		case 'w':		/* "wide" printer format */
E 5
E 4
D 2
			hscale = 20.0;
			vscale = 12.0;
E 2
I 2
			hscale = 16.0;
			vscale = 9.6;
E 2
			linelen = 131;
			keepon = 1;
I 5
			clearsc = 1;
E 5
			break;
	    }
D 6
	    argc--;
	    argv++;
E 6
	}

D 6
	if (argc <= 1)
E 6
I 6
	if (argc < 1)
E 6
		conv(stdin);
	else
D 6
		while (--argc) {
E 6
I 6
		while (argc--) {
E 6
			if (strcmp(*argv, "-") == 0)
				fp = stdin;
			else if ((fp = fopen(*argv, "r")) == NULL)
				error(FATAL, "can't open %s", *argv);
			conv(fp);
			fclose(fp);
			argv++;
		}
	done();
I 6
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
	if ((--*argcp) <= 0) {			/* operand next word */
	    fprintf (stderr, "command-line option operand missing.\n");
	    exit(1);
	}
	return(*(++(*argvp)));			/* no operand */
E 6
}


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
}


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


conv(fp)
register FILE *fp;
{
	register int c;
	int m, n, i, n1, m1;
	char str[100], buf[300];

	while ((c = getc(fp)) != EOF) {
		switch (c) {
		case '\n':	/* when input is text */
		case '\t':
		case ' ':
		case 0:
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
				/* two motion digits plus a character */
D 15
			hmot((c-'0')*10 + getc(fp)-'0');
E 15
I 15
			if (ascii) {
			    hmot((int)hscale);
			    getc(fp);
			} else {
			    hmot((c-'0')*10 + getc(fp)-'0');
			}
E 15
			put1(getc(fp));
			break;

		case 'c':	/* single ascii character */
			put1(getc(fp));
			break;

		case 'C':	/* funny character */
			fscanf(fp, "%s", str);
			put1s(str);
			break;

		case 't':	/* straight text */
			fgets(buf, sizeof(buf), fp);
			t_text(buf);
			break;

		case 'D':	/* draw function */
			fgets(buf, sizeof(buf), fp);
			switch (buf[0]) {
			case 'l':	/* draw a line */
				sscanf(buf+1, "%d %d", &n, &m);
D 12
				drawline(n, m, ".");
E 12
I 12
				drawline(n, m);
E 12
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
I 14
			case 'q':	/* versatec polygon - ignore */
				while (buf[strlen(buf) - 1] != '\n')
				    if (fgets(buf, sizeof(buf), fp) == NULL)
					error(FATAL,"unexpected end of input");
				break;
			case 'P':	/* unbordered */
E 14
I 12
			case 'p':	/* polygon */
				sscanf(buf+1, "%d", &n);
				n = 1;
				while(buf[n++] == ' ');
				while(isdigit(buf[n])) n++;
				drawwig(buf+n, 1);
				break;
E 12
			case 'g':	/* "gremlin" curve */
			case '~':	/* wiggly line */
D 12
				drawwig(buf+1);
E 12
I 12
				drawwig(buf+1, 0);
E 12
				break;
			case 't':	/* thickness - not important */
			case 's':	/* style - not important */
				break;
			default:
				error(FATAL,"unknown drawing command %s\n",buf);
				break;
			}
			break;
I 12
		case 'i':	/* stipple pattern request - ignored */
E 12
		case 's':	/* point size - ignored */
			fscanf(fp, "%d", &n);
			break;

		case 'f':	/* font request - ignored */
			fscanf(fp, "%s", str);
			break;

		case 'H':	/* absolute horizontal motion */
			fscanf(fp, "%d", &n);
			hgoto(n);
			break;

		case 'h':	/* relative horizontal motion */
			fscanf(fp, "%d", &n);
			hmot(n);
			break;

		case 'w':	/* word space */
I 15
			if (ascii) {
			    hmot((int)hscale);
			}
E 15
			break;

		case 'V':	/* absolute vertical motion */
			fscanf(fp, "%d", &n);
			vgoto(n);
			break;

		case 'v':	/* relative vertical motion */
			fscanf(fp, "%d", &n);
			vmot(n);
			break;

		case 'p':	/* new page */
			fscanf(fp, "%d", &n);
			t_page(n);
			break;

I 8
		case 'P':	/* new span (ignored) */
			fscanf(fp, "%d", &n);
			break;

E 8
		case 'n':	/* end of line */
			hpos = 0;
		case '#':	/* comment */
			while (getc(fp) != '\n')
				;
			break;

		case 'x':	/* device control */
			devcntrl(fp);
			break;

		default:
			error(!FATAL, "unknown input character %o %c\n", c, c);
			done();
		}
	}
}


devcntrl(fp)	/* interpret device control functions */
FILE *fp;
{
	int c, n;
	char str[20];

	fscanf(fp, "%s", str);
	switch (str[0]) {	/* crude for now */
	case 'i':	/* initialize */
		t_init(0);
		break;
	case 'r':	/* resolution assumed when prepared */
		fscanf(fp, "%d", &n);
		hscale = (float) n / hscale;
		vscale = (float) n / vscale;
D 4
		break;
E 4
I 4
D 5
		if((DP = n / 10 - 6) < 1) DP = 1;	/* guess the drawing */
		break;					/* resolution */
E 5
I 5
		DP = min (hscale, vscale);	/* guess the drawing */
		DP = max (DP, 1);		/* resolution */
		break;
E 5
E 4
	case 'f':	/* font used */
	case 'T':	/* device name */
	case 't':	/* trailer */
	case 'p':	/* pause -- can restart */
	case 's':	/* stop */
		break;
	}
	while (getc(fp) != '\n')	/* skip rest of input line */
		;
}

		/* error printing routine - first argument is a "fatal" flag */
error(f, s, a1, a2, a3, a4, a5, a6, a7) {
    fprintf(stderr, "dterm: ");
    fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
    fprintf(stderr, "\n");
    if (f) exit(1);
}


t_init(reinit)	/* initialize device */
int reinit;
{
D 4
	int i, j;
E 4
I 4
	register int i;
	register int j;
	register FILE *fp;	/* file to look up special characters */
	register char *charptr;	/* string pointer to step through specials */
	register char *tabptr;	/* string pointer for spectab setting */
	char specials[5000];	/* intermediate input buffer (made bigger */
				/*   than we'll EVER use... */
E 4

I 4

E 4
	fflush(stdout);
	hpos = vpos = 0;
	for (i = 0; i < PGHEIGHT; i++)
		for (j = 0; j < PGWIDTH; j++)
			pagebuf[i][j] = ' ';
	minh = PGWIDTH;
	maxh = 0;
	minv = PGHEIGHT;
	maxv = 0;
I 4

	if (reinit) return;		/* if this is the first time, read */
					/* special character table file. */
	if ((fp = fopen (specfile, "r")) != NULL) {
	    charptr = &specials[0];
D 7
	    for (i = 2; fscanf(fp, "%s", charptr) != EOF; i += 2) {
E 7
I 7
	    for (i = 2; fscanf(fp, "%s", charptr) != EOF; i++) {
E 7
		charptr += strlen(charptr) + 1;
	    }
	    fclose(fp);
	    *charptr++ = '\0';			/* ending strings */
	    *charptr++ = '\0';
						/* allocate table */
	    spectab = (char **) malloc(i * sizeof(char*));
	    spectab[0] = tabptr = malloc(j = (int) (charptr - &specials[0]));

						/* copy whole table */
	    for (charptr = &specials[0]; j--; *tabptr++ = *charptr++);

D 7
	    tabptr = spectab[j];		/* set up pointers to table */
E 7
I 7
	    tabptr = spectab[0];		/* set up pointers to table */
E 7
	    for (j = 0; i--; j++) {
		spectab[j] = tabptr;
		tabptr += strlen(tabptr) + 1;
	    }

	} else {	/* didn't find table - allocate a null one */

	    error (!FATAL, "Can't open special character file: %s", specfile);
	    spectab = (char **) malloc(2 * sizeof(char*));
	    spectab[0] = malloc (2);
	    spectab[1] = spectab[0] + 1;
	    *spectab[0] = '\0';
	    *spectab[1] = '\0';
	}
E 4
}


		/* just got "p#" command.  print the current page and */
t_page(n)	/* do whatever new page functions */
{
	long ftell();
	int c, m, i;
	char buf[100], *bp;

	pgnum[np++] = n;
	pgadr[np] = ftell(fp);
	if (np > npmax)
		npmax = np;
	if (output == 0) {
		output = in_olist(n);
		t_init(1);
		return;
	}

	putpage();
	fflush(stdout);

I 5
	if (clearsc) putchar('');
E 5
	if (keepon) {
D 5
		putchar('');
E 5
		t_init(1);
		return;
	}
  next:
	for (bp = buf; (*bp = readch()); )
		if (*bp++ == '\n')
			break;
	*bp = 0;
	switch (buf[0]) {
	case 0:
		done();
		break;
	case '\n':
		output = in_olist(n);
		t_init(1);
		return;
	case '-':
	case 'p':
		m = atoi(&buf[1]) + 1;
		if (fp == stdin) {
			fputs("you can't; it's not a file\n", stderr);
			break;
		}
		if (np - m <= 0) {
			fputs("too far back\n", stderr);
			break;
		}
		np -= m;
		fseek(fp, pgadr[np], 0);
		output = 1;
		t_init(1);
		return;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		m = atoi(&buf[0]);
		for (i = 0; i < npmax; i++)
			if (m == pgnum[i])
				break;
		if (i >= npmax || fp == stdin) {
			fputs("you can't\n", stderr);
			break;
		}
		np = i + 1;
		fseek(fp, pgadr[np], 0);
		output = 1;
		t_init(1);
		return;
	case 'o':
		outlist(&buf[1]);
		output = 0;
		t_init(1);
		return;
	case '?':
		fputs("p	print this page again\n", stderr);
		fputs("-n	go back n pages\n", stderr);
		fputs("n	print page n (previously printed)\n", stderr);
		fputs("o...	set the -o output list to ...\n", stderr);
		break;
	default:
		fputs("?\n", stderr);
		break;
	}
	goto next;
}

			/* print the contents of the current page.  puts out */
putpage()		/* only the part of the page that's been written on */
D 8
{
E 8
I 8
{			/* unless "margin" is set. */
E 8
	int i, j, k;

	fflush(stdout);
I 8
	if (margin) minv = minh = 0;
E 8
	for (i = minv; i <= maxv; i++) {
		for (k = maxh; pagebuf[i][k] == ' '; k--)
			;
		if (k > minh + linelen)
			k = minh + linelen;
		for (j = minh; j <= k; j++)
			putchar(pagebuf[i][j]);
		putchar('\n');
	}
	fflush(stdout);
}


t_text(s)		/* print string s as text */
char *s;
{
	int c;
	char str[100];

	if (!output)
		return;
	while ((c = *s++) != '\n') {
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
D 15
		hmot(1);
E 15
I 15
		hmot((int)hscale);
E 15
	}
}


put1s(s)	/* s is a funny char name */
char *s;
{
	int i;
	char *p;
D 4
	extern char *spectab[];
E 4
	static char prev[10] = "";
	static int previ;

	if (!output)
		return;
	if (strcmp(s, prev) != 0) {
		previ = -1;
D 4
		for (i = 0; spectab[i] != 0; i += 2)
E 4
I 4
		for (i = 0; *spectab[i] != '\0'; i += 2)
E 4
			if (strcmp(spectab[i], s) == 0) {
				strcpy(prev, s);
				previ = i;
				break;
			}
	}
	if (previ >= 0) {
D 15
		for (p = spectab[previ+1]; *p; p++)
E 15
I 15
		for (hmot((int)-hscale), p = spectab[previ+1]; *p; p++) {
			hmot((int)hscale);
E 15
			store(*p);
I 15
		}
E 15
	} else
D 4
		prev[0] = 0;
E 4
I 4
		prev[0] = '\0';
E 4
}


put1(c)			/* output char c */
int c;
{
	if (!output)
		return;
	store(c);
}


done()
{
	output = 1;
	putpage();
	fflush(stdout);
	exit(0);
}


readch ()
{
	int c;
	static FILE *rcf;
	static nbol;	/* 0 if at beginning of a line */

	if (rcf == NULL) {
		rcf = fopen ("/dev/tty", "r");
		setbuf (rcf, NULL);
	}

	if (!nbol)
		fprintf (stderr, "dterm: ");	/* issue prompt */
	if ((c = getc (rcf)) == EOF)
		return 0;
	nbol = (c != '\n');
	return c;
}


store(c)		/* put 'c' in the page at (hpos, vpos) */
{
	register int i;
	register int j;


	i = hpos / hscale;	/* scale the position to page coordinates */
	j = vpos / vscale;

	if (i >= PGWIDTH) i = PGWIDTH - 1;	/* don't go over the edge */
	else if (i < 0) i = 0;
	if (j >= PGHEIGHT) j = PGHEIGHT - 1;
	else if (j < 0) j = 0;

	pagebuf[j][i] = c;		/* write the character */

	if (i > maxh) maxh = i;		/* update the page bounds */
	if (i < minh) minh = i;
	if (j > maxv) maxv = j;
	if (j < minv) minv = j;
}


D 12
drawline(dx, dy, s)	/* draw line from here to dx, dy using s */
E 12
I 12
drawline(dx, dy)	/* draw line from here to dx, dy using s */
E 12
int dx, dy;
D 12
char *s;
E 12
{
	register int xd;
	register int yd;
	register int i;
	register int numdots;
	int dirmot, perp;
	int motincr, perpincr;
	int ohpos, ovpos;
	float val, slope;
	float incrway;

	ohpos = hpos;
	ovpos = vpos;
	xd = dx / DP;
	yd = dy / DP;
	if (xd == 0) {
		numdots = abs (yd);
		numdots = min(numdots, maxdots);
		motincr = DP * sgn (yd);
I 5
D 10
		put1(drawdot);
E 10
I 10
		put1('|');
E 10
E 5
		for (i = 0; i < numdots; i++) {
			vmot(motincr);
D 10
			put1(drawdot);
E 10
I 10
			put1('|');
E 10
		}
	} else
	if (yd == 0) {
		numdots = abs (xd);
I 5
		numdots = min(numdots, maxdots);
E 5
		motincr = DP * sgn (xd);
I 5
D 10
		put1(drawdot);
E 10
I 10
		put1('-');
E 10
E 5
		for (i = 0; i < numdots; i++) {
			hmot(motincr);
D 10
			put1(drawdot);
E 10
I 10
			put1('-');
E 10
		}
	} else {
	    if (abs (xd) > abs (yd)) {
		val = slope = (float) xd/yd;
		numdots = abs (xd);
D 4
		numdots = min(numdots, maxdots);
E 4
		dirmot = 'h';
		perp = 'v';
		motincr = DP * sgn (xd);
		perpincr = DP * sgn (yd);
	    } else {
		val = slope = (float) yd/xd;
		numdots = abs (yd);
D 4
		numdots = min(numdots, maxdots);
E 4
		dirmot = 'v';
		perp = 'h';
		motincr = DP * sgn (yd);
		perpincr = DP * sgn (xd);
	    }
I 4
	    numdots = min(numdots, maxdots);
E 4
	    incrway = sgn ((int) slope);
I 5
D 10
	    put1(drawdot);
E 10
I 10
	    put1('*');
E 10
E 5
	    for (i = 0; i < numdots; i++) {
		val -= incrway;
		if (dirmot == 'h')
			hmot(motincr);
		else
			vmot(motincr);
		if (val * slope < 0) {
			if (perp == 'h')
				hmot(perpincr);
			else
				vmot(perpincr);
			val += slope;
		}
D 10
		put1(drawdot);
E 10
I 10
		put1('*');
E 10
	    }
	}
	hgoto(ohpos + dx);
	vgoto(ovpos + dy);
}


D 12
drawwig(s)	/* draw wiggly line */
E 12
I 12
drawwig(s, poly)	/* draw wiggly line or polygon, if "poly" set */
E 12
char *s;
I 12
int poly;
E 12
{
	int x[50], y[50], xp, yp, pxp, pyp;
	float t1, t2, t3, w;
	int i, j, numdots, N;
	char temp[50], *p, *getstr();

	p = s;
	for (N = 2; (p=getstr(p,temp)) != NULL && N < sizeof(x)/sizeof(x[0]);) {
		x[N] = atoi(temp);
		p = getstr(p, temp);
		y[N++] = atoi(temp);
	}
I 12
	if (poly) {
		for (i = 2; i < N; i++)
			drawline(x[i], y[i]);
		return;
	}
E 12
	x[0] = x[1] = hpos;
	y[0] = y[1] = vpos;
	for (i = 1; i < N; i++) {
		x[i+1] += x[i];
		y[i+1] += y[i];
	}
	x[N] = x[N-1];
	y[N] = y[N-1];
	pxp = pyp = -9999;
	for (i = 0; i < N-1; i++) {	/* interval */
		numdots = (dist(x[i], y[i], x[i+1], y[i+1])
			     + dist(x[i+1], y[i+1], x[i+2], y[i+2])) / 2;
		numdots /= DP;
		numdots = min(numdots, maxdots);
		for (j = 0; j < numdots; j++) {	/* points within */
			w = (float) j / numdots;
			t1 = 0.5 * w * w;
			w = w - 0.5;
			t2 = 0.75 - w * w;
			w = w - 0.5;
			t3 = 0.5 * w * w;
			xp = t1 * x[i+2] + t2 * x[i+1] + t3 * x[i] + 0.5;
			yp = t1 * y[i+2] + t2 * y[i+1] + t3 * y[i] + 0.5;
			if (xp != pxp || yp != pyp) {
				hgoto(xp);
				vgoto(yp);
D 10
				put1(drawdot);
E 10
I 10
				put1('*');
E 10
				pxp = xp;
				pyp = yp;
			}
		}
	}
}


/* copy next non-blank string from p to temp, update p */

char *getstr(p, temp)
char *p, *temp;
{
	while (*p == ' ' || *p == '\t' || *p == '\n')
		p++;
	if (*p == '\0') {
		temp[0] = 0;
		return(NULL);
	}
	while (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
		*temp++ = *p++;
	*temp = '\0';
	return(p);
}


drawcirc(d)
{
	int xc, yc;

	xc = hpos;
	yc = vpos;
	conicarc(hpos + d/2, -vpos, hpos, -vpos, hpos, -vpos, d/2, d/2);
	hgoto(xc + d);	/* circle goes to right side */
	vgoto(yc);
}


dist(x1, y1, x2, y2)	/* integer distance from x1,y1 to x2,y2 */
{
	float dx, dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return sqrt(dx*dx + dy*dy) + 0.5;
}


drawarc(dx1, dy1, dx2, dy2)
{
	int x0, y0, x2, y2, r;

	x0 = hpos + dx1;	/* center */
	y0 = vpos + dy1;
	x2 = x0 + dx2;	/* "to" */
	y2 = y0 + dy2;
	r = sqrt((float) dx1 * dx1 + (float) dy1 * dy1) + 0.5;
	conicarc(x0, -y0, hpos, -vpos, x2, -y2, r, r);
}


drawellip(a, b)
{
	int xc, yc;

	xc = hpos;
	yc = vpos;
	conicarc(hpos + a/2, -vpos, hpos, -vpos, hpos, -vpos, a/2, b/2);
	hgoto(xc + a);
	vgoto(yc);
}


conicarc(x, y, x0, y0, x1, y1, a, b)
{
		/* based on Bresenham, CACM Feb 77, pp 102-3 by Chris Van Wyk */
		/* capitalized vars are an internal reference frame */
	long dotcount = 0;
	int	xs, ys, xt, yt, Xs, Ys, qs, Xt, Yt, qt,
		M1x, M1y, M2x, M2y, M3x, M3y,
		Q, move, Xc, Yc;
	int ox1, oy1;
	long	delta;
	float	xc, yc;
	float	radius, slope;
	float	xstep, ystep;

	ox1 = x1;
	oy1 = y1;
	if (a != b)	/* an arc of an ellipse; internally, think of circle */
		if (a > b) {
			xstep = (float)a / b;
			ystep = 1;
			radius = b;
		} else {
			xstep = 1;
			ystep = (float)b / a;
			radius = a;
		} 
	else {
	    /* a circular arc; radius computed from center and first point */	
		xstep = ystep = 1;
		radius = sqrt((float)(sqr(x0 - x) + sqr(y0 - y)));
	}

	xc = x0;
	yc = y0;
	/* now, use start and end point locations to figure out
	the angle at which start and end happen; use these
	angles with known radius to figure out where start
	and end should be
	*/
	slope = atan2((double)(y0 - y), (double)(x0 - x) );
	if (slope == 0.0 && x0 < x)
		slope = 3.14159265;
	x0 = x + radius * cos(slope) + 0.5;
	y0 = y + radius * sin(slope) + 0.5;
	slope = atan2((double)(y1 - y), (double)(x1 - x));
	if (slope == 0.0 && x1 < x)
		slope = 3.14159265;
	x1 = x + radius * cos(slope) + 0.5;
	y1 = y + radius * sin(slope) + 0.5;
	/* step 2: translate to zero-centered circle */
	xs = x0 - x;
	ys = y0 - y;
	xt = x1 - x;
	yt = y1 - y;
	/* step 3: normalize to first quadrant */
	if (xs < 0)
		if (ys < 0) {
			Xs = abs(ys);
			Ys = abs(xs);
			qs = 3;
			M1x = 0;
			M1y = -1;
			M2x = 1;
			M2y = -1;
			M3x = 1;
			M3y = 0;
		} else {
			Xs = abs(xs);
			Ys = abs(ys);
			qs = 2;
			M1x = -1;
			M1y = 0;
			M2x = -1;
			M2y = -1;
			M3x = 0;
			M3y = -1;
		} 
	else if (ys < 0) {
		Xs = abs(xs);
		Ys = abs(ys);
		qs = 0;
		M1x = 1;
		M1y = 0;
		M2x = 1;
		M2y = 1;
		M3x = 0;
		M3y = 1;
	} else {
		Xs = abs(ys);
		Ys = abs(xs);
		qs = 1;
		M1x = 0;
		M1y = 1;
		M2x = -1;
		M2y = 1;
		M3x = -1;
		M3y = 0;
	}

	Xc = Xs;
	Yc = Ys;
	if (xt < 0)
		if (yt < 0) {
			Xt = abs(yt);
			Yt = abs(xt);
			qt = 3;
		} else {
			Xt = abs(xt);
			Yt = abs(yt);
			qt = 2;
		} 
	else if (yt < 0) {
		Xt = abs(xt);
		Yt = abs(yt);
		qt = 0;
	} else {
		Xt = abs(yt);
		Yt = abs(xt);
		qt = 1;
	}

		/* step 4: calculate number of quadrant crossings */
	if (((4 + qt - qs) % 4 == 0) && (Xt <= Xs) && (Yt >= Ys))
		Q = 3;
	else
		Q = (4 + qt - qs) % 4 - 1;
		/* step 5: calculate initial decision difference */
	delta = sqr(Xs + 1) + sqr(Ys - 1) - sqr(xs) - sqr(ys);
				/* here begins the work of drawing. */
	while ((Q >= 0) || ((Q > -2) && ((Xt > Xc) && (Yt < Yc)))) {
D 10
		if (dotcount++ % DP == 0)
			putdot((int)xc, (int)yc);
E 10
I 10
		if (dotcount++ % DP == 0) {
			hgoto((int)xc);
			vmot(-vpos-((int)yc));
			put1('*');
		}
E 10
		if (Yc < 0.5) {
			/* reinitialize */
			Xs = Xc = 0;
			Ys = Yc = sqrt((float)(sqr(xs) + sqr(ys)));
			delta = sqr(Xs + 1) + sqr(Ys - 1) - sqr(xs) - sqr(ys);
			Q--;
			M1x = M3x;
			M1y = M3y;
			 {
				int	T;
				T = M2y;
				M2y = M2x;
				M2x = -T;
				T = M3y;
				M3y = M3x;
				M3x = -T;
			}
		} else {
			if (delta <= 0)
				if (2 * delta + 2 * Yc - 1 <= 0)
					move = 1;
				else
					move = 2;
			else if (2 * delta - 2 * Xc - 1 <= 0)
				move = 2;
			else
				move = 3;
			switch (move) {
			case 1:
				Xc++;
				delta += 2 * Xc + 1;
				xc += M1x * xstep;
				yc += M1y * ystep;
				break;
			case 2:
				Xc++;
				Yc--;
				delta += 2 * Xc - 2 * Yc + 2;
				xc += M2x * xstep;
				yc += M2y * ystep;
				break;
			case 3:
				Yc--;
				delta -= 2 * Yc + 1;
				xc += M3x * xstep;
				yc += M3y * ystep;
				break;
			}
		}
	}
D 12
	drawline((int)xc-ox1,(int)yc-oy1,".");
E 12
I 12
	drawline((int)xc-ox1,(int)yc-oy1);
E 12
D 10
}


putdot(x, y)
{
	arcmove(x, y);
	put1(drawdot);
E 10
}
E 1
