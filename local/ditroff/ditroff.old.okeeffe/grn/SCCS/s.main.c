h64629
s 00008/00000/00731
d D 1.24 86/04/14 09:46:09 slatteng 24 23
c take stipple map out as default and made it an option
e
s 00002/00002/00729
d D 1.23 85/08/05 10:55:08 slatteng 23 22
c fix bug in picture bounds calculations - wasn't initializing correctly
e
s 00001/00003/00730
d D 1.22 85/07/19 12:16:15 slatteng 22 21
c make GREMLIB come from Makefile, not #defined in
e
s 00008/00001/00725
d D 1.21 85/06/24 13:46:08 slatteng 21 20
c added "-" filename capability and getting device from environment
e
s 00034/00000/00692
d D 1.20 84/12/29 22:02:23 opcode 20 19
c SCREENtoINCH now reflects Sun resolution for sungremlinfiles
c Cifplot stipples are used by if not specified with `st cf'
e
s 00037/00002/00655
d D 1.19 84/10/08 15:41:20 ralph 19 18
c update for format of new SUN gremlin files.
e
s 00004/00003/00653
d D 1.18 84/06/22 14:38:36 slatteng 18 17
c fix flyback so it never goes back beyond the start of the picture.
e
s 00027/00005/00629
d D 1.17 84/05/25 15:22:08 slatteng 17 16
c added stipple handling
e
s 00001/00001/00633
d D 1.16 84/04/17 11:58:17 slatteng 16 15
c put blank line AFTER the .GS to start a page AFTER the .GS does the .ne
e
s 00031/00019/00603
d D 1.15 84/03/15 14:24:14 slatteng 15 14
c fix bug of pictures at top of page (starting off with text to force the trap)
c add .GF option for no-motion pictures, change some error reporting
e
s 00004/00002/00618
d D 1.14 84/01/18 14:41:34 slatteng 14 13
c make device directory changeable in makefile, changed some
e
s 00003/00002/00617
d D 1.13 83/11/30 17:27:25 slatteng 13 12
c fixed scaling problem when using width or height
e
s 00150/00138/00469
d D 1.12 83/11/02 12:56:21 slatteng 12 11
c remove most command-line options, add "default" and "pointscale"
e
s 00002/00002/00605
d D 1.11 83/10/13 12:52:55 slatteng 11 10
c .br at end instead of .sp -1 and .br at start
e
s 00002/00002/00605
d D 1.10 83/10/13 11:54:59 slatteng 10 9
c removed .sp -1 at start because diversions didn't work.
e
s 00008/00010/00599
d D 1.9 83/10/07 22:05:20 slatteng 9 8
c fix .sp bug, add -P option and change -F directory handling.
e
s 00004/00010/00605
d D 1.8 83/09/23 10:13:40 slatteng 8 7
c fix "savebounds" bug for setting both ends of bounding points
e
s 00048/00020/00567
d D 1.7 83/09/19 15:30:31 slatteng 7 6
c change number register useage, fix calloc botch in interpret
c routine, fixed initialization bug, and added documentation.
e
s 00054/00051/00533
d D 1.6 83/08/23 13:24:38 slatteng 6 5
c changed option operand figuring... fixed -p bug... etc.
e
s 00001/00001/00583
d D 1.5 83/08/12 15:49:42 slatteng 5 4
c oops - fixed missing )
e
s 00096/00018/00488
d D 1.4 83/08/12 15:40:44 slatteng 4 3
c fixed troff commands at beginning and end of picture, 
c added code to interpret in-GS-GE commands, fixed parameter setting.
e
s 00001/00001/00505
d D 1.3 83/07/22 13:21:11 slatteng 3 2
c fix path for gremlib
e
s 00010/00007/00496
d D 1.2 83/07/22 13:16:52 slatteng 2 1
c make grn try gremlib when it can't find a picture
e
s 00503/00000/00000
d D 1.1 83/07/21 15:26:31 slatteng 1 0
c date and time created 83/07/21 15:26:31 by slatteng
e
u
U
t
T
I 1
D 19
/*	%M%	%I%	(Berkeley) %E%
E 19
I 19
/*	%M%	%I%	(Berkeley)	%E%
E 19
 *
 *	This file contains the main and file system dependent routines
 * for processing gremlin files into troff input.  The program watches
 * input go by to standard output, only interpretting things between .GS
D 12
 * and .GE lines.  Default values may be overridden, as in gprint, on the
D 6
 * command line and are further overridden by commands in the input.
E 6
I 6
 * command line and are further overridden by commands in the input.  A
 * description of the command-line options are listed below.  A space is
 * NOT required for the operand of an option.
E 12
I 12
 * and .GE lines.  Default values (font, size, scale, thickness) may be
 * overridden with a "default" command and are further overridden by
 * commands in the input.  A description of the command-line options are
 * listed below.  A space is NOT required for the operand of an option.
E 12
E 6
 *
 *	command options are:
 *
D 6
 *	-1 #	sets point size 1 to #.  also for -2, -3, -4.  Defaults
 *		are 12, 16, 24, 36.
 *
E 6
D 12
 *	-r ss	sets gremlin's roman font to troff font ss.  Also for -i,
 *		-b and -s for italics, bold, and special fonts.  This does
 *		NOT affect font changes imbedded into strings.  A \fI, for
 *		instance, will get the italics font regardless of what -i
 *		is set to.
E 12
I 12
 *	-L dir	set the library directory to dir.  If a file is not found
 *		in the current directory, it is looked for in dir (default
 *		is /usr/lib/gremlib).
E 12
 *
I 6
D 12
 *	-1 #	sets point size 1 to #.  also for -2, -3, -4.  Defaults
 *		are 12, 16, 24, 36.
 *
E 6
 *	-n #	set narrow line thickness to # pixels.  Also for -m (medium)
D 4
 *		and -t (thick).
E 4
I 4
 *		and -t (thick).  Defaults are 1, 3, and 5 pixels.
E 4
 *
 *	-x #	scale the picture by x (integer or decimal).
 *
E 12
D 6
 *	-Tdev	Prepare output for "dev" printer.  Default is for the varian
E 6
I 6
 *	-T dev	Prepare output for "dev" printer.  Default is for the varian
E 6
D 12
 *		and versatec printers.  Devices acceptable are:  ver, var, ip.
E 12
I 12
 *	-P dev	and versatec printers.  Devices acceptable are:  ver, var, ip.
E 12
 *
D 12
 *	-p	prompt user for fonts, sizes and thicknesses.
I 7
 *
 *
 *		Inside the GS and GE, there are commands similar to command-
 *	    line options listed above.  At most one command may reside on each
 *	    line, and each command is followed by a parameter separated by white
 *	    space.  The commands are as follows, and may be abbreviated down to
 *	    one character (with exception of "scale" down to "sc") and may be
E 12
I 12
 *		Inside the GS and GE, commands are accepted to reconfigure
 *	    the picture.  At most one command may reside on each line, and
 *	    each command is followed by a parameter separated by white space.
 *	    The commands are as follows, and may be abbreviated down to one
D 17
 *	    character (with exception of "scale" down to "sc") and may be
E 12
 *	    upper or lower case.
E 17
I 17
 *	    character (with exception of "scale" and "stipple" down to "sc"
 *	    and "st") and may be upper or lower case.
E 17
 *
I 12
 *			      default  -  make all settings in the current
 *					  .GS/.GE the global defaults.
 *					  Height, width and file are NOT saved.
E 12
 *			   1, 2, 3, 4  -  set size 1, 2, 3, or 4 (followed
I 12
 *					  by an integer point size).
E 12
 *	roman, italics, bold, special  -  set gremlin's fonts to any other
 *					  troff font (one or two characters)
I 17
 *			   stipple, l  -  use a stipple font for polygons.  Arg
 *					  is troff font name.  No Default.  Can
 *					  use only one stipple font per picture.
I 19
 *					  (see below for stipple font index)
E 19
E 17
 *			     scale, x  -  scale is IN ADDITION to the global
D 12
 *					  scale factor from the -x option.
E 12
I 12
 *					  scale factor from the default.
 *			   pointscale  -  turn on scaling point sizes to
 *					  match "scale" commands.  (optional
 *					  operand "off" to turn it off)
E 12
 *		narrow, medium, thick  -  set pixel widths of lines.
 *				 file  -  set the file name to read the
D 12
 *					  gremlin picture from.
E 12
I 12
 *					  gremlin picture from.  If the file
 *					  isn't in the current directory, the
 *					  gremlin library is tried.
E 12
 *			width, height  -  these two commands override any
 *					  scaling factor that is in effect,
 *					  and forces the picture to fit into
 *					  either the height or width specified,
 *					  whichever makes the picture smaller.
 *					  The operand for these two commands is
 *					  a floating-point number in units of
 *					  inches
I 24
 *		        oldstipplemap  -  use the old-style stipple mapping.
 *					  THE FOLLOWING COMMANDS ARE IGNORED
 *					  UNLESS OLDSTIPPLEMAP IS SPECIFIED.
E 24
I 19
 *     l1, l2, l3, l4, l5, l6, l7, l8  -  set association between stipples
 *					  (1 - 8) and the stipple font file
 *					  index.  Valid cifplot indices are
 *					  1 - 32 (although 24 is not defined)
 *					  and valid unigrafix indices are
 *					  1 - 64.  Nonetheless, any number
 *					  between 0 and 255 is accepted since
 *					  new stipple fonts may be added.
 *					  An integer operand is required.
E 19
 *
 *	Troff number registers used:  g1 through g9.  g1 is the width of the
D 9
 *	picture, and g2 is the height.  g2-g6 save information, g8 and g9 are
 *	used for text processing and g7 is reserved.
E 9
I 9
 *	picture, and g2 is the height.  g3, and g4, save information, g8
 *	and g9 are used for text processing and g5-g7 are reserved.
E 9
E 7
 */


I 4
#include <ctype.h>
E 4
#include "gprint.h"
#include "dev.h"

D 4
extern char *malloc();
E 4
I 4
D 7
extern char *calloc();
E 7
I 7
extern char *malloc();
E 7
E 4
extern char *rindex();

/* database imports */

extern HGPrintElt();
extern ELT *DBInit(), *DBRead();
extern POINT *PTInit(), *PTMakePoint();


I 19
D 22
#ifdef SUN
#define GREMLIB		"/usr/local/lib/gremlin/"
#else
E 22
I 22
#ifndef GREMLIB
E 22
E 19
D 6
char *doinput();

E 6
I 2
D 3
#define GREMLIB		"/usr/lib/gremlib/"
E 3
I 3
#define GREMLIB		"/usr/local/gremlib/"
I 19
#endif

I 20
#define SUN_SCALEFACTOR 0.70

E 20
E 19
I 14
#ifndef DEVDIR
E 14
E 3
E 2
D 9
#define DEVDIR		"/usr/lib/font/dev"
#define DEFAULTDEV	"var"
E 9
I 9
#define DEVDIR		"/usr/lib/font"
I 14
#endif
E 14
#define DEFAULTDEV	"va"
I 20
#define DEFSTIPPLE	"cf"
E 20
E 9

#define MAXINLINE	100		/* input line length */
#define DEFTHICK	3		/* default thicknes */
#define DEFSTYLE	SOLID		/* default line style */

I 20
#ifdef oldversion
E 20
#define SCREENtoINCH	0.02		/* scaling factor, screen to inches */
I 20
#endif

double SCREENtoINCH;			/* scaling factor, screen to inches */

E 20
D 12
#define BIG	100000000000.0		/* unweildly large floating number */
E 12
I 12
#define BIG	999999999999.0		/* unweildly large floating number */
E 12

D 12
#define JLEFT		-1		/* justification constants - for the */
#define JCENTER		0		/*    whole picture - where it will */
#define JRIGHT		1		/*    get placed within the line */
E 12

D 12

E 12
D 19
char	SccsId[] = "%M%	%I%	%E%";
E 19
I 19
static char sccsid[] = "%Z% (Berkeley) %G%";
E 19

char	*printer = DEFAULTDEV;	/* device to look up resolution of */
I 12
char	*gremlib = GREMLIB;	/* place to find files after current dir. */
E 12
double	res;			/* that printer's resolution goes here */

int	linethickness;		/* brush styles */
int	linmod;
int	lastx;			/* point registers for printing elements */
int	lasty;
int	lastyline;		/* a line's vertical position is NOT the same */
				/* after that line is over, so for a line of */
				/* drawing commands, vertical spacing is kept */
				/* in lastyline */
D 12
double	scale = SCREENtoINCH;	/* default scale to map gremlin screen to inches
				   (modified by -x command-line option) */
E 12

D 12
		    /* list of prompts for asking user to set default values */
char	*prompt[] = {				  /* used only for -p option */
		"Roman font name? (%s): ",	"Italic font name? (%s): ",
		"Bold font name? (%s): ",	"Special font name? (%s): ",
		"font size 1? (%s): ",		"font size 2? (%s): ",
		"font size 3? (%s): ",		"font size 4? (%s): ",
	};
E 12
I 12
			/* these are the default fonts, sizes, line styles, */
			/*   and thicknesses.  These can be modified from a */
			/*   "default" command and are reset each time the  */
			/*   start of a picture (.GS) is found.		    */
E 12

D 12
			/* these are the default fonts, sizes, */
			/*   line styles, and thicknesses.  These */
			/*   can be modified from command-line */
			/*   options, and are reset each time the */
			/*   start of a picture (.GS) is found. */
E 12
I 12
char *	deffont[] = {  "R", "I", "B", "S"  };
int	defsize[] = {  10, 16, 24, 36  };
int	defthick[STYLES] = {  1, 1, 5, 1, 1, 3  };
I 19
int	defstipple_index[NSTIPPLES] = { 1, 3, 12, 14, 16, 19, 21, 23 };
E 19
int	style[STYLES] = {  DOTTED, DOTDASHED, SOLID, DASHED, SOLID, SOLID  };
double	scale = 1.0;		/* no scaling, default */
int	defpoint = 0;		/* flag for pointsize scaling */
I 17
char *  defstipple = (char *) 0;
E 17
E 12

D 12
char	*defstring[] = {
		"R\0         ", "I\0         ", "B\0         ", "S\0         ",
		"10\0        ", "16\0        ", "24\0        ", "36\0        "
	};
int	defthick[STYLES] = { 1, 1, 5, 1, 1, 3 };	/* defaults... */
int	style[STYLES] = { DOTTED, DOTDASHED, SOLID, DASHED, SOLID, SOLID };
E 12
int	thick[STYLES];	/* thicknesses set by defaults, then by commands */
D 12
char	*tfont[FONTS];	/* fonts originally set to defstring values, then */
char 	*tsize[SIZES];	/*    optionally changed by commands inside grn */
E 12
I 12
char	*tfont[FONTS];	/* fonts originally set to deffont values, then */
int 	tsize[SIZES];	/*    optionally changed by commands inside grn */
I 19
int	stipple_index[NSTIPPLES];	/* stipple font file indices */
E 19
I 17
char *  stipple;
E 17
E 12

I 4
double	xscale;		/* scaling factor from individual pictures */
E 4
D 2
int	cfont;		/* current font */
int	csize;		/* current point size */
E 2
double	troffscale;	/* scaling factor at output time */ 
double	width;		/* user-request maximum width for picture (in inches) */
double	height;		/* user-request height */
I 12
int	pointscale;	/* flag for pointsize scaling */
int	setdefault;	/* flag for a .GS/.GE to remember all settings */
E 12

double	toppoint;		/* remember the picture */
double	bottompoint;		/* bounds in these variables */
double	leftpoint;
double	rightpoint;

int	ytop;			/* these are integer versions of the above */
int	ybottom;		/* so not to convert each time they're used */
int	xleft;
int	xright;

int	linenum = 0;			/* line number of input file */
char	inputline[MAXINLINE];		/* spot to filter through the file */
char	*c1 = inputline;		/* c1, c2, and c3 will be used to */
char	*c2 = inputline + 1;		/* hunt for lines that begin with */
char	*c3 = inputline + 2;		/* ".GS" by looking individually */
char	GScommand[MAXINLINE];		/* put user's ".GS" command line here */
D 14
char	gremlinfile[50];		/* filename to use for a picture */
E 14
I 14
char	gremlinfile[MAXINLINE];		/* filename to use for a picture */
I 19
int	SUNFILE = FALSE;		/* TRUE if SUN gremlin file */
I 24
int	oldstipmap = FALSE;		/* TRUE if old-style stipple mapping */
E 24
E 19
E 14

I 6
char *doinput();
E 6

I 6

E 6
/*----------------------------------------------------------------------------*
 | Routine:	main (argument_count, argument_pointer)
 |
 | Results:	parses the command line, accumulating input file names, then
 |		reads the inputs, passing it directly to output until a ".GS"
 |		line is read.  Main then passes control to "conv" to do the
 |		gremlin file conversions.
D 12
 |
 | Bugs:	a -p option ALWAYS reads standard input.  Even if the input
 |		file is coming in that way.
E 12
 *----------------------------------------------------------------------------*/

main(argc, argv)
int argc;
char **argv;
{
D 21
	register FILE *fp = stdin;
E 21
I 21
	register FILE *fp;
E 21
	register int k;
	register char c;
D 6
	char *file[50], string[50], *arg;
E 6
I 6
D 12
	char *file[50], string[50];
E 6
	float mult;
	int brsh, gfil = 0;
E 12
I 12
	register gfil = 0;
	char *file[50];
E 12

I 6
	char *operand();
I 21
	char *getenv();
E 21
E 6

D 6
	argc--;
	argv++;
	while (argc--) {
	    if (*(arg = *argv++) != '-')
		file[gfil++] = arg;
	    else switch (c = *++arg) {
E 6

I 21
	if (fp = (FILE *) getenv("PRINTER")) printer = (char *) fp;
	if (fp = (FILE *) getenv("TYPESETTER")) printer = (char *) fp;
E 21
I 6
	while (--argc) {
	    if (**++argv != '-')
		file[gfil++] = *argv;
	    else
	      switch (c = (*argv)[1]) {
I 21

		case 0:
			file[gfil++] = NULL;
			break;
E 21

E 6
D 12
		case '1':	/* select sizes */
		case '2':
		case '3':
		case '4':
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
			strcpy(defstring[c + FONTS - '1'], arg);
E 6
I 6
			strcpy(defstring[c + FONTS-'1'], operand(&argc, &argv));
E 6
			break;
		case 'r':	/* select Roman font */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
D 4
			strcpy(string[0], arg);
E 4
I 4
			strcpy(defstring[0], arg);
E 6
I 6
			strcpy(defstring[0], operand(&argc, &argv));
E 6
E 4
			break;
		case 'i':	/* select italics font */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
D 4
			strcpy(string[1], arg);
E 4
I 4
			strcpy(defstring[1], arg);
E 6
I 6
			strcpy(defstring[1], operand(&argc, &argv));
E 6
E 4
			break;
		case 'b':	/* select bold font */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
D 4
			strcpy(string[2], arg);
E 4
I 4
			strcpy(defstring[2], arg);
E 6
I 6
			strcpy(defstring[2], operand(&argc, &argv));
E 6
E 4
			break;
		case 's':	/* select special font */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
D 4
			strcpy(string[3], arg);
E 4
I 4
			strcpy(defstring[3], arg);
E 6
I 6
			strcpy(defstring[3], operand(&argc, &argv));
E 6
E 4
			break;
		case 'n':	/* select narrow brush width */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
			(void) sscanf(arg, "%d", &brsh);
			defthick[0]=defthick[1]=defthick[3]=defthick[4] = brsh;
E 6
I 6
			(void) sscanf(operand(&argc, &argv), "%d", &brsh);
			defthick[0]=defthick[1]=defthick[3]=defthick[4]=brsh;
E 6
			break;
		case 't':	/* select thick brush width */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
			(void) sscanf(arg, "%d", &brsh);
E 6
I 6
			(void) sscanf(operand(&argc, &argv), "%d", &brsh);
E 6
			defthick[2] = brsh;
			break;
		case 'm':	/* select medium brush width */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
			(void) sscanf(arg, "%d", &brsh);
E 6
I 6
			(void) sscanf(operand(&argc, &argv), "%d", &brsh);
E 6
			defthick[5] = brsh;
			break;
		case 'x':	/* select scale */
D 6
			if (*++arg == '\0' && argc--)
			    arg = *argv++;
			sscanf(arg,"%f", &mult);
E 6
I 6
			sscanf(operand(&argc, &argv),"%f", &mult);
E 6
			scale *= mult;
			break;
E 12
I 9
		case 'P':
E 9
		case 'T':	/* final output typesetter name */
D 6
			printer = arg + 1;
E 6
I 6
			printer = operand(&argc, &argv);
E 6
			break;
D 12
		case 'p':	/* prompt for font and size parameters */
			for (k = 0; k < 8; k++) {
D 6
			    fprintf(stderr, prompt[k], string[k]);
E 6
I 6
			    fprintf(stderr, prompt[k], defstring[k]);
E 6
			    gets(string);
D 6
			    if (*string != '\0') strcpy(string[k], string);
E 6
I 6
			    if (*string != '\0') strcpy(defstring[k], string);
E 6
			}
			fprintf(stderr,"narrow brush size? (%d): ",defthick[0]);
			gets(string);
			if (*string != '\0') {
			    sscanf(string, "%d", &brsh);
			    defthick[0] = defthick[1] = defthick[3]
							= defthick[4] = brsh;
			}
			fprintf(stderr,"medium brush size? (%d): ",defthick[5]);
			gets(string);
			if (*string != '\0') {
			    sscanf(string, "%d", &brsh);
			    defthick[5] = brsh;
			}
			fprintf(stderr, "thick brush size? (%d): ",defthick[2]);
			gets(string);
			if (*string != '\0') {
			    sscanf(string, "%d", &brsh);
			    defthick[2] = brsh;
			}
E 12
I 12

		case 'L':	/* set library directory */
			gremlib = operand(&argc, &argv);
E 12
			break;
I 12

E 12
		default:
D 12
			fprintf(stderr, "unknown switch: %c\n", c);
E 12
I 12
			error("unknown switch: %c", c);
E 12
	    }
	}
				/* set the resolution for an output device */
	getres(printer);	/* named in "printer" */

	if (gfil == 0) {	/* no filename, use standard input */
		file[0] = NULL;
		gfil++;
	}
I 6

E 6
	for (k=0; k<gfil; k++) {
		if (file[k] != NULL) {
			if ((fp = fopen(file[k], "r")) == NULL) {
D 12
			    fprintf(stderr, "grn: can't open %s\n", file[k]);
E 12
I 12
			    error("can't open %s", file[k]);
E 12
D 15
			    continue;
E 15
I 15
			    exit(1);
E 15
			}
D 6
			if (k == 0) {
				if ((arg = rindex(file[k], '/')) == NULL)
					arg = file[k];
				else
					arg++;
			}
E 6
		} else {
			fp = stdin;
		}

		while (doinput(fp) != NULL) {
		    if (*c1 == '.' && *c2 == 'G' && *c3 == 'S') {
			conv(fp, linenum);
		    } else {
			fputs(inputline, stdout);
		    }
		}
	}
I 6
}


/*----------------------------------------------------------------------------*
I 12
 | Routine:	error (control_string, args, . . . )
 |
 | Results:	prints ("grn: ", the control_string + args, "\n") to stderr
 *----------------------------------------------------------------------------*/

/* VARARGS1 */
error(s, a1, a2, a3, a4)
char *	s;
{
	fprintf(stderr, "grn: ");
	fprintf(stderr, s, a1, a2, a3, a4);
	fprintf(stderr, "\n");
}


/*----------------------------------------------------------------------------*
E 12
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
D 12
	    fprintf (stderr, "command-line option operand missing.\n");
E 12
I 12
	    error("command-line option operand missing.");
E 12
D 15
	    exit(1);
E 15
I 15
	    exit(8);
E 15
	}
	return(*(++(*argvp)));			/* operand is next word */
E 6
}


/*----------------------------------------------------------------------------*
 | Routine:	getres (device_name)
 |
 | Results:	sets "res" to the resolution of the output device specified
 |		by the string dev.
 *----------------------------------------------------------------------------*/

getres(name)
char *name;
{
	int fin;
	struct dev device;
	char temp[60];

D 9
	sprintf(temp, "%s%s/DESC.out", DEVDIR, name);
E 9
I 9
	sprintf(temp, "%s/dev%s/DESC.out", DEVDIR, name);
E 9
	if ((fin = open(temp, 0)) < 0) {
D 12
	    fprintf(stderr, "can't open tables for %s\n", temp);
E 12
I 12
	    error("can't open tables for %s", temp);
E 12
	    exit(1);
	}
	read(fin, &device, sizeof(struct dev));
	res = (double) device.res;
	close(fin);
}


/*----------------------------------------------------------------------------*
 | Routine:	char  * doinput (file_pointer)
 |
 | Results:	a line of input is read into "inputline".
 |
 | Side Efct:	"linenum" is incremented.
 |
 | Bugs:	lines longer than MAXINLINE are NOT checked, except for 
 |		updating "linenum"
 *----------------------------------------------------------------------------*/

char *doinput(fp)
FILE *fp;
{
D 12
    register char *k;
E 12
I 12
    char *k;
E 12


    if ((k = fgets(inputline, MAXINLINE, fp)) == NULL)
	return k;
    if (index (inputline, '\n'))	/* ++ only if it's a complete line */
	linenum++;
    return (char*) !NULL;
}


/*----------------------------------------------------------------------------*
 | Routine:	initpic ( )
 |
 | Results:	sets all parameters to the normal defaults, possibly overridden
D 12
 |		by the command line flags.  Initilaize the picture variables,
E 12
I 12
 |		by a setdefault command.  Initilaize the picture variables,
E 12
 |		and output the startup commands to troff to begin the picture.
 *----------------------------------------------------------------------------*/

initpic()
{
    register int i;

    for (i = 0; i < STYLES; i++) {	/* line thickness defaults */
	thick[i] = defthick[i];
    }
    for (i = 0; i < FONTS; i++) {	/* font name defaults */
D 12
	tfont[i] = defstring[i];
E 12
I 12
	tfont[i] = deffont[i];
E 12
    }
    for (i = 0; i < SIZES; i++) {	/* font size defaults */
D 12
	tsize[i] = defstring[FONTS + i];
E 12
I 12
	tsize[i] = defsize[i];
E 12
    }
I 19
    for (i = 0; i < NSTIPPLES; i++) {	/* stipple font file default indices */
	stipple_index[i] = defstipple_index[i];
    }
E 19
I 17
    stipple = defstipple;
E 17

    gremlinfile[0] = 0;		/* filename is "null" */
I 12
    setdefault = 0;		/* this is not the default settings (yet) */
E 12

    toppoint = BIG;		/* set the picture bounds out */
D 23
    bottompoint = 0.0;		/* of range so they'll be set */
E 23
I 23
    bottompoint = -BIG;		/* of range so they'll be set */
E 23
    leftpoint = BIG;		/* by "savebounds" on input */
D 23
    rightpoint = 0.0;
E 23
I 23
    rightpoint = -BIG;
E 23

I 12
    pointscale = defpoint;	/* Flag for scaling point sizes default. */
E 12
I 4
    xscale = scale;		/* default scale of individual pictures */
E 4
    width = 0.0;		/* size specifications input by user */
    height = 0.0;

    linethickness = DEFTHICK;	/* brush styles */
    linmod = DEFSTYLE;
}


/*----------------------------------------------------------------------------*
 | Routine:	conv (file_pointer, starting_line)
 |
 | Results:	at this point, we just passed a ".GS" line in the input file.
 |		conv reads the input and calls "interpret" to process commands,
 |		gathering up information until a ".GE" line is found.  It then
 |		calls "HGPrint" to do the translation of the gremlin file to
 |		troff commands.
 *----------------------------------------------------------------------------*/

conv(fp, baseline)
register FILE *fp;
int baseline;
{
D 15
	register FILE *gfp = NULL;
	register int done = 0;
	register ELT *e;
	ELT *PICTURE;
	double temp;
	POINT ptr;
E 15
I 15
	register FILE *gfp = NULL;	/* input file pointer */
	register int done = 0;		/* flag to remember if finished */
	register ELT *e;	/* current element pointer */
	ELT *PICTURE;		/* whole picture data base pointer */
	double temp;		/* temporary calculating area */
	POINT ptr;	/* coordinates of a point to pass to "mov" routine */
	int flyback;	/* flag "want to end up at the top of the picture?" */
E 15


D 4
	strcpy (GScommand, inputline);		/* save ".GS" line for later */
E 4
I 4
	initpic();			/* set defaults, ranges, etc. */
	strcpy (GScommand, inputline);	/* save ".GS" line for later */
E 4
	do {
	    done = (doinput(fp) == NULL);		     /* test for EOF */
D 15
	    done |= (*c1 == '.' && *c2 == 'G' && *c3 == 'E');	 /*  and .GE */
E 15
I 15
	    flyback = *c3 == 'F';			   /* and .GE or .GF */
	    done |= (*c1 == '.' && *c2 == 'G' && (*c3 == 'E' || flyback));
E 15

	    if (done) {
I 12
		if (setdefault) savestate();

E 12
		if (!gremlinfile[0]) {
D 12
		    fprintf(stderr, "grn: at line %d: no picture filename.\n",
								    baseline);
E 12
I 12
D 15
		    if(!setdefault) fprintf(stderr,
			"at line %d: no picture filename.\n", baseline);
E 15
I 15
		    if(!setdefault)
			error("at line %d: no picture filename.\n", baseline);
E 15
E 12
		    return;
		}
		if ((gfp = fopen(gremlinfile, "r")) == NULL) {
D 2
		    fprintf(stderr, "grn: can't open %s\n", gremlinfile);
		    return;
E 2
I 2
D 14
		    char name[100];	/* if the file isn't in the current */
E 14
I 14
		    char name[MAXINLINE]; /* if the file isn't in the current */
E 14
					/* directory, try the gremlin library */
D 12
		    sprintf(name, "%s%s", GREMLIB, gremlinfile);
E 12
I 12
		    sprintf(name, "%s%s", gremlib, gremlinfile);
E 12
		    if ((gfp = fopen(name, "r")) == NULL) {
D 12
			fprintf(stderr, "grn: can't open %s\n", gremlinfile);
E 12
I 12
			error("can't open %s", gremlinfile);
E 12
			return;
		    }
E 2
		}
D 4
		initpic();		/* set defaults, ranges, etc. */

E 4
		PICTURE = DBRead(gfp);			/* read picture file */
		fclose(gfp);
		if (DBNullelt(PICTURE))
D 7
		    return;
					/* if a request is made to make the */
E 7
I 7
		    return;		/* if a request is made to make the */
E 7
					/* picture fit into a specific area, */
					/* set the scale to do that. */
I 20

		SCREENtoINCH = (SUNFILE) ? 0.014 : 0.02;

		if (stipple == (char *) NULL)	/* if user forgot stipple */
		    if (has_polygon(PICTURE))	/* and picture has a polygon */
			stipple = DEFSTIPPLE;	/* then set the default */

E 20
D 7
		temp = (height != 0.0)  ?
			SCREENtoINCH * (bottompoint - toppoint) / height  : BIG;
		troffscale = (width != 0.0)  ?
			SCREENtoINCH * (rightpoint - leftpoint) / width  : BIG;
E 7
I 7
		if ((temp = bottompoint - toppoint) < 0.1) temp = 0.1;
D 13
		temp = (height != 0.0) ? height / temp  : BIG;
E 13
I 13
		temp = (height != 0.0) ? height / (temp * SCREENtoINCH)  : BIG;
E 13
		if ((troffscale = rightpoint - leftpoint) < 0.1) troffscale=0.1;
D 13
		troffscale = (width != 0.0) ? width / troffscale  : BIG;
E 13
I 13
		troffscale = (width != 0.0) ?
				width / (troffscale * SCREENtoINCH)  : BIG;
E 13
E 7
		if (temp == BIG && troffscale == BIG) {
D 4
		    troffscale = scale;
E 4
I 4
		    troffscale = xscale;
E 4
		} else {
		    if (temp < troffscale) troffscale = temp;
I 12
		}				/* here, troffscale is the */
						/* picture's scaling factor */
		if (pointscale) {
		    register int i;		/* do pointscaling here, when */
					     /* scale is known, before output */
I 20

E 20
		    for (i = 0; i < SIZES; i++)
			tsize[i] = (int) (troffscale * (double) tsize[i] + 0.5);
I 20

E 20
E 12
		}
D 12
		troffscale *= res;	/* change to device units from inches */
E 12
I 12
						   /* change to device units */
		troffscale *= SCREENtoINCH * res;	/* from screen units */
E 12

		ytop = toppoint * troffscale;		/* calculate integer */
		ybottom = bottompoint * troffscale;	/* versions of the */
		xleft = leftpoint * troffscale;		/* picture limits */
		xright = rightpoint * troffscale;
					/* save stuff in number registers, */
D 7
					/*   register gw = picture width and */
					/*   register gh = picture height, */
E 7
I 7
					/*   register g1 = picture width and */
					/*   register g2 = picture height, */
E 7
					/*   set vertical spacing, no fill, */
					/*   and break (to make sure picture */
					/*   starts on left), and put out the */
					/*   user's ".GS" line. */
D 4
		printf(".nr g1 \\n(.f\n.nr g2 \\n(.s\n");
		printf(".nr g3 \\n(.v\n.nr g4 \\n(.u\n");
E 4
D 7
		printf(".nr gw %d\n.nr gh %d\n", xright-xleft, ybottom-ytop);
E 7
I 7
D 15
		printf(".nr g1 %d\n.nr g2 %d\n", xright-xleft, ybottom-ytop);
E 7
D 4
		printf("%s.br\n.nf\n.vs 0", GScommand);
E 4
I 4
D 9
		printf(".br\n%s", GScommand);
D 7
		printf(".nr g1 \\n(.f\n.nr g2 \\n(.s\n");
		printf(".nr g3 \\n(.v\n.nr g4 \\n(.u\n.nf\n.vs 0");
E 7
I 7
		printf(".nr g3 \\n(.f\n.nr g4 \\n(.s\n");
		printf(".nr g5 \\n(.v\n.nr g6 \\n(.u\n.nf\n.vs 0");
E 9
I 9
D 10
		printf(".sp -1\n%s.nr g3 \\n(.f\n.nr g4 \\n(.s\n", GScommand);
E 10
I 10
D 11
		printf("%s.nr g3 \\n(.f\n.nr g4 \\n(.s\n", GScommand);
E 11
I 11
		printf(".br\n%s.nr g3 \\n(.f\n.nr g4 \\n(.s\n", GScommand);
E 15
I 15
		printf(
D 16
".br\n\\0\n.sp -1\n.nr g1 %du\n.nr g2 %du\n%s.nr g3 \\n(.f\n.nr g4 \\n(.s\n",
E 16
I 16
".br\n.nr g1 %du\n.nr g2 %du\n%s.nr g3 \\n(.f\n.nr g4 \\n(.s\n\\0\n.sp -1\n",
E 16
			xright-xleft, ybottom-ytop, GScommand);
E 15
E 11
E 10
E 9
E 7
E 4

I 17
		if (stipple) {		/* stipple requested for this picture */
		    printf(".st %s\n", stipple);
		}

E 17
		lastx = xleft;		/* note where we are, (upper left */
		lastyline = lasty = ytop;	/* corner of the picture) */

		e = PICTURE;
D 17
		while (!DBNullelt(e)) {
		    HGPrintElt(e);	/* traverse picture;  print elements */
E 17
I 17
		while (!DBNullelt(e)) {	/* traverse picture;  print elements */
		    HGPrintElt(e, baseline);
E 17
		    e = DBNextElt(e);
		}
D 15
					/* end picture at lower left */
		ptr.x = leftpoint;
		ptr.y = bottompoint;
E 15
I 15
				/* decide where to end picture */
		if (flyback) {		/* end piture at upper left */
		    ptr.x = leftpoint;
		    ptr.y = toppoint;
		} else {		/* end picture at lower left */
		    ptr.x = leftpoint;
		    ptr.y = bottompoint;
		}
E 15
D 2
		tmove(&ptr);
		printf("\\D't %du'\\D's %du'", DEFTHICK, DEFSTYLE);
		cr ();
E 2
I 2
		tmove(&ptr);		/* restore default line parameters, */
E 2
D 15
					/* put out the ".GE" line from user */
					/* then restore everything to the way */
					/* it was before the .GS */
E 15
I 15
					/* restore everything to the way */
					/* it was before the .GS, then put */
					/* out the ".GE" line from user */
D 18
		if (flyback)
		    printf(".sp -1\n");
E 18
I 18
		printf("\\D't %du'\\D's %du'\n", DEFTHICK, DEFSTYLE);
		if (flyback) {		/* make sure we end up at top of */
		    printf(".sp -1\n");		/* picture if "flying back" */
		}
E 18
I 17
		if (stipple) {		/* restore stipple to previous */
		    printf(".st\n");
		}
E 17
E 15
I 2
D 18
		printf("\\D't %du'\\D's %du'\n", DEFTHICK, DEFSTYLE);
E 18
E 2
D 4
		printf("%s.ft \\n(g1\n.ps \\n(g2\n", inputline);
		printf(".vs \\n(g3u\n.if \\n(g4 .fi\n");
E 4
I 4
D 7
		printf(".ft \\n(g1\n.ps \\n(g2\n");
		printf(".vs \\n(g3u\n.if \\n(g4 .fi\n%s", inputline);
E 7
I 7
D 9
		printf(".ft \\n(g3\n.ps \\n(g4\n");
		printf(".vs \\n(g5u\n.if \\n(g6 .fi\n%s", inputline);
E 9
I 9
D 10
		printf(".br\n.ft \\n(g3\n.ps \\n(g4\n%s", inputline);
E 10
I 10
D 11
		printf(".sp -1\n.ft \\n(g3\n.ps \\n(g4\n%s", inputline);
E 11
I 11
		printf(".br\n.ft \\n(g3\n.ps \\n(g4\n%s", inputline);
E 11
E 10
E 9
E 7
E 4
	    } else {
		interpret(inputline);	/* take commands from the input file */
	    }
	} while (!done);
}


/*----------------------------------------------------------------------------*
I 12
 | Routine:	savestate  ( )
 |
 | Results:	all the current  scaling / font size / font name / thickness /
 |		pointscale  settings are saved to be the defaults.  Scaled
 |		point sizes are NOT saved.  The scaling is done each time a
 |		new picture is started.
 |
D 17
 | Side Efct:	defpoint, scale, deffont, defsize and defthick are modified.
E 17
I 17
 | Side Efct:	scale, and def* are modified.
E 17
 *----------------------------------------------------------------------------*/

savestate()
{
    register int i;

    for (i = 0; i < STYLES; i++) {	/* line thickness defaults */
	defthick[i] = thick[i];
    }
    for (i = 0; i < FONTS; i++) {	/* font name defaults */
	deffont[i] = tfont[i];
    }
    for (i = 0; i < SIZES; i++) {	/* font size defaults */
	defsize[i] = tsize[i];
    }
I 19
    for (i = 0; i < NSTIPPLES; i++) {	/* stipple font file default indices */
	defstipple_index[i] = stipple_index[i];
    }
E 19
I 17
    defstipple = stipple;	/* if stipple has been set, it's remembered */
E 17

    scale *= xscale;		/* default scale of individual pictures */
    defpoint = pointscale;	/* flag for scaling pointsizes from x factors */
}


/*----------------------------------------------------------------------------*
E 12
 | Routine:	savebounds (x_coordinate, y_coordinate)
 |
 | Results:	keeps track of the maximum and minimum extent of a picture
 |		in the global variables:  left-, right-, top- and bottompoint.
 |		"savebounds" assumes that the points have been oriented to
 |		the correct direction.  No scaling has taken place, though.
 *----------------------------------------------------------------------------*/

savebounds(x, y)
float x;
float y;
{
D 8
    if (x < leftpoint) {
	leftpoint = x;
    } else if (x > rightpoint) {
	rightpoint = x;
    }
    if (y < toppoint) {
	toppoint = y;
    } else if (y > bottompoint) {
	bottompoint = y;
    }
E 8
I 8
    if (x < leftpoint) leftpoint = x;
    if (x > rightpoint) rightpoint = x;
    if (y < toppoint) toppoint = y;
    if (y > bottompoint) bottompoint = y;
E 8
}


/*----------------------------------------------------------------------------*
 | Routine:	interpret (character_string)
 |
 | Results:	commands are taken from the input string and performed.
D 4
 |		the commands are separated by the endofline or a semicolon.
E 4
I 4
 |		Commands are separated by the endofline, and are of the
 |		format:
 |			string1 string2
E 4
 |
I 4
 |		where string1 is the command and string2 is the argument.
 |
E 4
 | Side Efct:	font and size strings, plus the gremlin file name and the
 |		width and height variables are set by this routine.
 *----------------------------------------------------------------------------*/

interpret (line)
D 4
register char *line;
E 4
I 4
char *line;
E 4
{
D 4
    sscanf(line, "%s", gremlinfile);
E 4
I 4
    char str1[MAXINLINE];
    char str2[MAXINLINE];
    register char *chr;
I 12
    register int i;
    double par;
E 12

I 12
    str2[0] = '\0';
E 12
D 7
    sscanf(line, "%s%s", &str1[0], &str2[0]);
E 7
I 7
    sscanf(line, "%80s%80s", &str1[0], &str2[0]);
E 7
    for (chr = &str1[0]; *chr; chr++)		/* convert command to */
D 5
	if(isupper(*chr) *chr = tolower(*chr);		/* lower case */
E 5
I 5
	if(isupper(*chr)) *chr = tolower(*chr);		/* lower case */
E 5
    switch (str1[0]) {

	case '1':
	case '2':	/* font sizes */
	case '3':
	case '4':
D 7
	    tsize[str1[0] - '1'] = calloc(strlen(str2) + 1);
E 7
I 7
D 12
	    tsize[str1[0] - '1'] = malloc(strlen(str2) + 1);
E 7
	    strcpy(tsize[str1[0] - '1'], str2);
E 12
I 12
	    i = atoi(str2);
	    if (i > 0 && i < 1000)
		tsize[str1[0] - '1'] = i;
	    else
		error("bad font size value at line %d", linenum);
E 12
	    break;

	case 'r':	/* roman */
I 12
	    if(str2[0] < '0') goto nofont;
E 12
D 7
	    tfont[0] = calloc(strlen(str2) + 1);
E 7
I 7
	    tfont[0] = malloc(strlen(str2) + 1);
E 7
	    strcpy(tfont[0], str2);
	    break;

	case 'i':	/* italics */
I 12
	    if(str2[0] < '0') goto nofont;
E 12
D 7
	    tfont[1] = calloc(strlen(str2) + 1);
E 7
I 7
	    tfont[1] = malloc(strlen(str2) + 1);
E 7
	    strcpy(tfont[1], str2);
	    break;

	case 'b':	/* bold */
I 12
	    if(str2[0] < '0') goto nofont;
E 12
D 7
	    tfont[2] = calloc(strlen(str2) + 1);
E 7
I 7
	    tfont[2] = malloc(strlen(str2) + 1);
E 7
	    strcpy(tfont[2], str2);
	    break;

	case 's':	/* special */
D 12
	    if (str1[1] == 'c') goto scalecommand;
E 12
I 12
	    if (str1[1] == 'c') goto scalecommand;	/* or scale */

	    if(str2[0] < '0') {
	nofont:	error("no fontname specified in line %d", linenum);
		break;
	    }
I 17
	    if (str1[1] == 't') goto stipplecommand;	/* or stipple */

E 17
E 12
D 7
	    tfont[3] = calloc(strlen(str2) + 1);
E 7
I 7
	    tfont[3] = malloc(strlen(str2) + 1);
E 7
	    strcpy(tfont[3], str2);
I 17
	    break;

	case 'l':	/* l */
I 19
	    if ((str1[1] < '1') || (str1[1] > '8'))
		goto stipplecommand;

	    /* else set stipple index */
	    i = atoi(str2);
	    if (i >= 0 && i < 256)
		stipple_index[str1[1] - '1'] = i;
	    else
		error("bad stipple index value at line %d", linenum);
	    break;

E 19
	stipplecommand:	/* stipple */
	    stipple = malloc(strlen(str2) + 1);
	    strcpy(stipple, str2);
I 24
	    break;

	case 'o':	/* oldstipplemap */
	    oldstipmap = TRUE;
E 24
E 17
	    break;

	case 't':	/* thick */
	    thick[2] = atoi(str2);
	    break;

	case 'm':	/* medium */
	    thick[5] = atoi(str2);
	    break;

	case 'n':	/* narrow */
	    thick[0] = thick[1] = thick[3] = thick[4] = atoi(str2);
	    break;

	case 'x':	/* x */
	scalecommand:	/* scale */
D 12
	    xscale *= atof(str2);
	    if (xscale < 0.0) xscale = -xscale;
E 12
I 12
	    par = atof(str2);
	    if (par > 0.0)
		xscale *= par;
	    else
		error("illegal scale value on line %d", linenum);
E 12
	    break;

	case 'f':	/* file */
	    strcpy(gremlinfile, str2);
	    break;

	case 'w':	/* width */
	    width = atof(str2);
	    if (width < 0.0) width = -width;
	    break;

	case 'h':	/* height */
	    height = atof(str2);
	    if (height < 0.0) height = -height;
I 12
	    break;

	case 'd':	/* defaults */
	    setdefault = 1;
	    break;

	case 'p':	/* pointscale */
	    if (strcmp("off", str2))
		pointscale = 1;
	    else
		pointscale = 0;
E 12
	    break;

	default: 
I 15
	    error("unknown command, %s, on line %d", str1, linenum);
	    exit(8);
E 15
	    break;
    };
I 20
}


/*
 * return TRUE if picture contains a polygon
 * otherwise FALSE
 */
has_polygon(elist)
register ELT *elist;
{
    while (!DBNullelt(elist)) {
	if (elist->type == POLYGON)
	    return(1);
	elist = DBNextElt(elist);
    }

    return(0);
E 20
E 4
}
E 1
