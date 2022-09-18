h15138
s 00002/00002/01236
d D 1.8 90/12/31 18:18:48 karels 8 7
c oops, tabs need to be relative to start of line
e
s 00011/00013/01227
d D 1.7 90/12/14 12:18:01 karels 7 6
c make compile with gcc; don't let tabs space backwards; wider tabs
c if proportional
e
s 00006/00002/01234
d D 1.6 90/03/22 14:02:12 karels 6 5
c fix for wrapping last line on page
e
s 00014/00009/01222
d D 1.5 90/03/19 10:42:22 karels 5 4
c yow! can't define fonts in a different order than before!
e
s 00083/00047/01148
d D 1.4 90/03/18 19:07:25 karels 4 3
c wrap lines that are too long; parameterize font sizes;
c add -s header ala ^Hheader for gaudy; bigger font for gaudy by default
e
s 00919/00826/00276
d D 1.3 90/02/21 20:24:01 karels 3 2
c from lbl (van/leres): user headers, etc
e
s 00007/00005/01095
d D 1.2 88/01/08 11:54:21 karels 2 1
c -q is quiet (again); -Q toggles; don't spool "" with -p and no -q!
e
s 01100/00000/00000
d D 1.1 88/01/08 11:13:04 karels 1 0
c date and time created 88/01/08 11:13:04 by karels
e
u
U
t
T
I 1
#ifndef lint
static char Notice[] = "Copyright (c) 1985 Adobe Systems Incorporated";
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
D 3
static char *RCSID="$Header: enscript.c,v 2.1 85/11/24 11:48:55 shore Rel $";
E 3
I 3
static char *RCSID = "$Header: enscript.c,v 1.7 89/03/12 01:31:55 van Exp $";

E 3
#endif
D 3
/* enscript.c
E 3
I 3
/*
 * enscript.c 
E 3
 *
D 3
 * Copyright (c) 1985 Adobe Systems Incorporated
E 3
I 3
 * Copyright (c) 1985 Adobe Systems Incorporated 
E 3
 *
D 3
 * inspired by Gosling's cz
 * there have been major overhauls, but the input language is the same:
 * 	new widths format
 *	generate PostScript (much easier than Press)
 *	new and renamed switches (to match 4.2bsd lpr spooler)
 *	obeys PostScript comment conventions
 *	doesn't worry so much about fonts (everything is scalable and
 *	rotatable, use PS font names, no face properties)
E 3
I 3
 * inspired by Gosling's cz there have been major overhauls, but the input
 * language is the same: new widths format generate PostScript (much easier
 * than Press) new and renamed switches (to match 4.2bsd lpr spooler) obeys
 * PostScript comment conventions doesn't worry so much about fonts
 * (everything is scalable and rotatable, use PS font names, no face
 * properties) 
E 3
 *
D 3
 * enscript generates POSTSCRIPT print files of a special kind
 * the coordinate system is in 20ths of a point. (1440 per inch)
E 3
I 3
 * enscript generates POSTSCRIPT print files of a special kind the coordinate
 * system is in 20ths of a point. (1440 per inch) 
E 3
 *
D 3
 * Edit History:
 * Andrew Shore: Mon Nov 18 14:05:05 1985
 * End Edit History.
E 3
I 3
 * Edit History: Andrew Shore: Mon Nov 18 14:05:05 1985 End Edit History. 
E 3
 *
D 3
 * RCSLOG:
 * $Log:	enscript.c,v $
 * Revision 2.1  85/11/24  11:48:55  shore
 * Product Release 2.0
E 3
I 3
 * RCSLOG: $Log:	enscript.c,v $
 * Revision 1.7  89/03/12  01:31:55  van
 * we have to escape special chars in title strings.
E 3
 * 
D 3
 * Revision 1.3  85/11/20  00:10:01  shore
 * Added System V support (input options and spooling)
 * margins/linecount reworked (Dataproducts)
 * incompatible options changes, getopt!
 * Guy Riddle's Gaudy mode and other changes
 * output spooling messages, pages, copies
E 3
I 3
 * Revision 1.6  89/03/10  00:30:39  van
 * might as well let the user change everything.
E 3
 * 
D 3
 * Revision 1.2  85/05/14  11:22:14  shore
 * *** empty log message ***
E 3
I 3
 * Revision 1.5  89/03/09  23:19:17  van
 * gcc lint.
E 3
 * 
I 3
 * Revision 1.4  89/03/09  23:08:50  van
 * let user set the fonts used in 'gaudy' mode
 * 
 * Revision 1.3  88/03/06  17:23:58  leres
 * Fix logic bug; only spool output if that's want we want.
 * 
 * Revision 1.2  86/07/03  00:06:31  van
 * reformatted.  removed SYSV ifdefs.
 *  Revision 1.1  86/07/03  00:03:12  van Initial
 * revision 
E 3
 *
I 3
 * Revision 2.1  85/11/24  11:48:55  shore Product Release 2.0 
 *
 * Revision 1.3  85/11/20  00:10:01  shore Added System V support (input options
 * and spooling) margins/linecount reworked (Dataproducts) incompatible
 * options changes, getopt! Guy Riddle's Gaudy mode and other changes output
 * spooling messages, pages, copies 
 *
 * Revision 1.2  85/05/14  11:22:14  shore *** empty log message *** 
 *
 *
E 3
 */

#define POSTSCRIPTPRINTER "PostScript"

#define BODYROMAN "Courier"
D 4
#define HEADFONT "Courier-Bold"
E 4
I 4
#define BODYSZ	  10
#define HEADFONT  "Courier-Bold"
#define HEADSZ	  10
#define GHEADFONT "Helvetica-Bold"
#define GHEADSZ	  14
E 4
I 3
#define SHEADFONT "Times-Bold"
I 4
#define SHEADSZ	  12
E 4
#define PGNUMFONT "Helvetica-Bold"
D 4
#define DATEFONT "Times-Bold"
E 4
I 4
#define PGNUMSZ   24
#define DATEFONT  "Times-Bold"
#define DATESZ    12
E 4
E 3

#ifdef DEBUG
#define debugp(x) {fprintf x ; VOIDC fflush(stderr);}
#else
#define debugp(x)
#endif

#define UperInch (1440L)
#define PtsPerInch 72
#define UperPt 20

/* virtual page is 8 x 10.5 inches (for Toshiba compat) */
#define PageWidth ((long) UperInch*8)
#define PageLength ((long)((UperInch*21)/2))

D 3
/*#define PageLength ((long) ((long) (UperInch*(8*11-3)))/8) */
/*#define PageWidth  ((long) ((long) (UperInch*(8*17-3)))/8) */
E 3
I 3
/* #define PageLength ((long) ((long) (UperInch*(8*11-3)))/8) */
/* #define PageWidth  ((long) ((long) (UperInch*(8*17-3)))/8) */
E 3

/* true page is 8.5 x 11 inches */
#define TruePageWidth  (UperInch*17/2)
#define TruePageLength ((long)(UperInch*11))

#include <stdio.h>
#include <ctype.h>
#include <pwd.h>
D 3
#ifdef SYSV
struct passwd *getpwuid();
#include <string.h>
#include <time.h>
#else
E 3
#include <strings.h>
#include <sys/time.h>
D 3
#endif
E 3
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "transcript.h"

D 3
#ifdef SYSV
#define LPR "lp"
#else
E 3
#define LPR "lpr"
D 3
#endif
E 3

D 3
#define MAXBAD 20	/* number of bad chars to pass before complaint */
E 3
I 3
#define MAXBAD 20		/* number of bad chars to pass before
				 * complaint */
E 3

private struct stat S;

I 3
extern double atof();
E 3
extern char *optarg;		/* getopt current opt char */
extern int optind;		/* getopt argv index */

D 3
private VOID int1();
E 3
I 3
private VOID int1 ();
private FlushShow();
E 3

#define FSIZEMAX 256		/* number of chars per font */

/* the layout of a font information block */
D 7
private struct font {
E 7
I 7
struct font {
E 7
D 3
    char    name[100];		/* PostScript font name */
    int     dsize;		/* size */
    int     Xwid[FSIZEMAX];	/* X widths for each character */
E 3
I 3
	char    name[100];	/* PostScript font name */
	int     dsize;		/* size */
	int     Xwid[FSIZEMAX];	/* X widths for each character */
E 3
};

D 3
private struct font fonts[16];		/* 16 possible fonts at one time */
private int nf = 0;			/* number of fonts known about */
E 3
I 3
private struct font fonts[16];	/* 16 possible fonts at one time */
private int nf = 0;		/* number of fonts known about */
E 3

D 8
private int TabWidth = TruePageWidth / 10;	/* width of a tab */
E 8
I 8
private int TabWidth;		/* width of a tab */
E 8
D 3
private int BSWidth;				/* width of a backspace */
E 3
I 3
private int BSWidth;		/* width of a backspace */
E 3

private long UperLine = UperInch / 7;
private long UperHLine = UperInch / 7;

private char *prog;		/* program name argv[0] */
private char *libdir;		/* place for prolog and widths files */
private char *tempdir;		/* place for temp file */
private char TempName[100];	/* name of temporary PostScript file */
private char OutName[256] = "";	/* filename for disk output */
private int PipeOut = FALSE;	/* output to stdout (-p -) */
private int ListOmitted = FALSE;/* list omitted chars on the tty */
D 4
private int BeQuiet = TRUE;	/* suppress stderr info messages */
E 4
I 4
private int BeQuiet = FALSE;	/* suppress stderr error messages */
private int Verbose = FALSE;	/* silly informational messages */
E 4
private int Gaudy = FALSE;	/* pretty bars along the top */
private int LPTsimulate = FALSE;/* an lpt should be simulated */
private int Lines = 0;		/* max lines per page */
private int LinesLeft = 66;	/* lines left on page when in LPT mode */
private int LineMax = 64;	/* ? */
D 7
private int col;		/* column number on current line */
E 7
private int SeenText = TRUE;	/* true if seen some text on this page */
private int OutOnly = FALSE;	/* PS file only wanted */
private int Rotated = FALSE;	/* pages to be rotated landscape */
private int PreFeed = FALSE;	/* prefeed should be enabled */
private int TwoColumn = FALSE;	/* two-column mode */
private int FirstCol = TRUE;	/* we're printing column 1 */
private int NoTitle = FALSE;	/* title line is suppressed */
private int Cvted = FALSE;	/* converted a file to PS format */

D 3
private int IgnoreGarbage = FALSE;/* garbage should be ignored */
E 3
I 3
private int IgnoreGarbage = FALSE;	/* garbage should be ignored */
E 3
D 4
private int SeenFile = FALSE;	/* a file has been processed */
E 4
private int SeenFont = FALSE;	/* we've seen a font request */
I 4
private int SeenFile = FALSE;	/* a file has been processed */
E 4
D 3
private int ScannedFonts = FALSE;/* we've scanned the font file */
E 3
I 3
private int ScannedFonts = FALSE;	/* we've scanned the font file */
E 3
private char *FileName = 0;	/* name of file currently being PSed */
private char *FileDate = 0;	/* last mod date of file being PSed */
private char DateStr[27];	/* thanks, but no thanks ctime! */
D 3
private int spoolNoBurst = FALSE;/* no break page flag for spooler */
E 3
I 3
private int spoolNoBurst = FALSE;	/* no break page flag for spooler */
E 3

D 3
#ifdef SYSV
private char *spoolTitle = NULL;
#endif
E 3
#ifdef BSD
private char *spoolJobClass = NULL;
private char *spoolJobName = NULL;
I 3

E 3
#endif
private char *PrinterName = NULL;
private int spoolNotify = 0;
private char *spoolCopies = "1";

private char tempstr[256];	/* various path names */

private int CurFont;		/* current Font */
D 3
private int fontindex[26];	/* table of fonts, indexed by font
				   designator ('a' to 'z') */
E 3
I 3
private int fontindex[26];	/* table of fonts, indexed by font designator
				 * ('a' to 'z') */

E 3
/* indexes for default fonts */

#define Roman fontindex['r'-'a']
#define HeaderFont fontindex['h'-'a']
I 3
#define SHeaderFont fontindex['i'-'a']
#define DateFont fontindex['j'-'a']
#define PgNumFont fontindex['k'-'a']
E 3

private long cX, cY;		/* current page positions */
private long dX, dY;		/* desired page positions */
private long lX, lY;		/* page positions of the start of the line */
private long crX, crY;		/* X and Y increments to apply to CR's */
private long maxX;		/* maximum x coord on line */
private long minY;		/* minimum y coord on page */
I 3
private long Xoffset;		/* amount to offset left margin */
E 3

#define None	0
#define RelX	1
#define	RelY	2
#define RelXY	3
#define AbsX	4
#define AbsY	8
#define AbsXY	12

private int movepending;	/* moveto pending coords on stack */
private int showpending;	/* number of characters waiting to be shown */
D 3
private int pagepending;	/* start on next page when have something to print */
private char *UsersHeader = NULL;/* user specified heading */
E 3
I 3
private int pagepending;	/* start on next page when have something to
				 * print */
private char *UsersHeader = NULL;	/* user specified heading */
E 3
private char *Header = NULL;	/* generated header (usually FileName) */
I 4
private char *Header2 = NULL;	/* second header line for Gaudy */
E 4
private int Page = 0;		/* current page number */
private int TotalPages = 0;	/* total number of pages printed */
private int TruncChars = 0;	/* number of characters truncated */
D 3
private int UndefChars = 0;	/* number of characters skipped because
				   they weren't defined in some font */
private int BadChars   = 0;	/* number of bad characters seen so far */
E 3
I 3
private int UndefChars = 0;	/* number of characters skipped because they
				 * weren't defined in some font */
private int BadChars = 0;	/* number of bad characters seen so far */
E 3
private FILE *OutFile = NULL;	/* output ps file */


/* decode a fontname string - e.g. Courier10 Helvetica-Bold12 */
D 3
private decodefont(name, f)
register char *name;
register struct font *f; {
    register char *d, *p;
E 3
I 3
private 
decodefont (name, f)
	register char *name;
	register struct font *f;
{
	register char *d, *p;
E 3

D 3
    SeenFont = TRUE;
    p = name;
    d = f->name;
    f->dsize = 0;
    while (isascii(*p) && (isalpha(*p) || (*p == '-'))) {*d++ = *p++;}
    *d++ = '\0';
    while (isascii(*p) && isdigit(*p)) {
	f->dsize = f->dsize * 10 + *p++ - '0';
    }
    if (*p || !f->dsize || !f->name[0]) {
	fprintf(stderr, "%s: poorly formed font name & size: \"%s\"\n",
		prog, name);
	exit (1);
    }
E 3
I 3
D 4
	SeenFont = TRUE;
E 4
	p = name;
	d = f->name;
	f->dsize = 0;
	while (isascii (*p) && (isalpha (*p) || (*p == '-'))) {
		*d++ = *p++;
	}
	*d++ = '\0';
	while (isascii (*p) && isdigit (*p)) {
		f->dsize = f->dsize * 10 + *p++ - '0';
	}
	if (*p || !f->dsize || !f->name[0]) {
		fprintf (stderr, "%s: poorly formed font name & size: \"%s\"\n",
			 prog, name);
		exit (1);
	}
E 3
}
D 3

E 3
I 3


E 3
#define NOTDEF 0x8000
#define ForAllFonts(p) for(p = &fonts[nf-1]; p >= &fonts[0]; p--)


D 3
/* Scan the font metrics directory looking for entries that match the
 * entries in ``fonts''.  For entries
 * that are found the data in the font description is filled in,
 * if any are missing, it dies horribly.
E 3
I 3
/*
 * Scan the font metrics directory looking for entries that match the entries
 * in ``fonts''.  For entries that are found the data in the font description
 * is filled in, if any are missing, it dies horribly. 
E 3
 */
D 3
private VOID ScanFont() {
    register struct font   *f;
    register FILE *FontData;		/* afm file */
    char *c;
    int ccode, cwidth, inChars;
    char FontFile[512];		/* afm file name */
    char afmbuf[BUFSIZ];
#ifdef SYSV
    char shortname[15];
#endif
E 3
I 3
private VOID ScanFont ()
{
	register struct font *f;
	register FILE *FontData;/* afm file */
	char   *c;
	int     ccode, cwidth, inChars;
	char    FontFile[512];	/* afm file name */
	char    afmbuf[BUFSIZ];
E 3

D 3
    if (!SeenFont) {
	if (Lines == 0) Lines = 64;
	if (Rotated && TwoColumn) fonts[Roman].dsize = 7;
    }
E 3

D 3
    /* loop through fonts, find and read metric entry in dir */
    ForAllFonts (f) {
	VOIDC mstrcat(FontFile, libdir, "/", sizeof FontFile);
#ifdef SYSV
	VOIDC mapname(f->name,shortname);
	VOIDC mstrcat(FontFile, FontFile, shortname, sizeof FontFile);
#else
	VOIDC mstrcat(FontFile, FontFile, f->name, sizeof FontFile);
#endif
	VOIDC mstrcat(FontFile, FontFile, ".afm", sizeof FontFile);
	if ((FontData = fopen(FontFile,"r")) == NULL){
	    fprintf(stderr,"%s: can't open font metrics file %s\n",
	    	prog,FontFile);
	    exit(1);
E 3
I 3
	if (!SeenFont) {
		if (Lines == 0)
			Lines = 64;
		if (Rotated && TwoColumn)
			fonts[Roman].dsize = 7;
E 3
	}
D 3
	/* read the .afm file to get the widths */
	for (ccode = 0; ccode < FSIZEMAX; ccode++) f->Xwid[ccode] = NOTDEF;
E 3
I 3
	/* loop through fonts, find and read metric entry in dir */
	ForAllFonts (f) {
		VOIDC   mstrcat (FontFile, libdir, "/", sizeof FontFile);
E 3

D 3
	inChars = 0;
	while(fgets(afmbuf, sizeof afmbuf, FontData) != NULL) {
	    /* strip off newline */
	    if ((c = INDEX(afmbuf, '\n')) == 0) {
		fprintf(stderr, "%s: AFM file %s line too long %s\n",
			prog, FontFile, afmbuf);
		exit(1);
	    }
	    *c = '\0';
	    if (*afmbuf == '\0') continue;
	    if (strcmp(afmbuf, "StartCharMetrics") == 0) {
		inChars++;
		continue;
	    }
	    if (strcmp(afmbuf, "EndCharMetrics") == 0) break;
	    if (inChars == 1) {
		if (sscanf(afmbuf, "C %d ; WX %d ;",&ccode,&cwidth) != 2) {
		    fprintf(stderr,"%s: trouble with AFM file %s\n",
		    	prog,FontFile);
		    exit(1);
E 3
I 3
		VOIDC   mstrcat (FontFile, FontFile, f->name, sizeof FontFile);

		VOIDC   mstrcat (FontFile, FontFile, ".afm", sizeof FontFile);

		if ((FontData = fopen (FontFile, "r")) == NULL) {
			fprintf (stderr, "%s: can't open font metrics file %s\n",
				 prog, FontFile);
			exit (1);
		}
		/* read the .afm file to get the widths */
		for (ccode = 0; ccode < FSIZEMAX; ccode++)
			f->Xwid[ccode] = NOTDEF;

		inChars = 0;
		while (fgets (afmbuf, sizeof afmbuf, FontData) != NULL) {
			/* strip off newline */
			if ((c = INDEX (afmbuf, '\n')) == 0) {
				fprintf (stderr, "%s: AFM file %s line too long %s\n",
					 prog, FontFile, afmbuf);
				exit (1);
			}
			*c = '\0';
			if (*afmbuf == '\0')
				continue;
			if (strcmp (afmbuf, "StartCharMetrics") == 0) {
				inChars++;
				continue;
			}
			if (strcmp (afmbuf, "EndCharMetrics") == 0)
				break;
			if (inChars == 1) {
				if (sscanf (afmbuf, "C %d ; WX %d ;", &ccode, &cwidth) != 2) {
					fprintf (stderr, "%s: trouble with AFM file %s\n",
						 prog, FontFile);
					exit (1);
				}
				/* get out once we see an unencoded char */
				if (ccode == -1)
					break;
				if (ccode > 255)
					continue;
				f->Xwid[ccode] =
					(short) (((long) cwidth * (long) f->dsize * (long) UperPt)
						 / 1000L);
				continue;
			}
E 3
		}
D 3
		/* get out once we see an unencoded char */
		if (ccode == -1) break;
		if (ccode > 255) continue;
		f->Xwid[ccode] =
		    (short)(((long) cwidth * (long) f->dsize * (long) UperPt)
		    	/ 1000L);
		continue;
	    }
E 3
I 3
		VOIDC   fclose (FontData);
E 3
	}
D 3
    VOIDC fclose(FontData);
    }
E 3

D 3
    TabWidth = fonts[Roman].Xwid['0'] * 8; /* 8 * figure width */
    BSWidth = fonts[Roman].Xwid[' ']; /* space width */ 
E 3
I 3
D 7
	TabWidth = fonts[Roman].Xwid['0'] * 8;	/* 8 * figure width */
E 7
I 7
	/*
	 * Tab width is problematical for proportionally-spaced fonts.
	 * Attempt to make tabs wide enough that things hand-tabulated
	 * for monospaced fonts still fit in columns.
	 */
	if (fonts[Roman].Xwid['0'] == fonts[Roman].Xwid['M'])
		TabWidth = fonts[Roman].Xwid['0'] * 8;	/* 8 * figure width */
	else
		TabWidth = fonts[Roman].Xwid['0'] * 10;	/* 10 * figure width */
E 7
	BSWidth = fonts[Roman].Xwid[' '];	/* space width */
E 3

D 3
    UperLine = (fonts[Roman].dsize + 1) * UperPt;
E 3
I 3
	UperLine = (fonts[Roman].dsize + 1) * UperPt;
E 3

D 3
    if (LPTsimulate) {
	UperHLine = UperLine;
	Lines = LineMax = 66;
    }
    else {
	UperHLine = (fonts[HeaderFont].dsize + 1) * UperPt;
    }
E 3
I 3
	if (LPTsimulate) {
		UperHLine = UperLine;
		Lines = LineMax = 66;
	} else {
		UperHLine = (fonts[HeaderFont].dsize + 1) * UperPt;
	}
E 3

D 3
    crX = 0;
    crY = -UperLine;
E 3
I 3
	crX = 0;
	crY = -UperLine;
E 3

}


D 3
/* Return a font number for the font with the indicated name
 * and size.  Adds info to the font list for the eventual search.
E 3
I 3
/*
 * Return a font number for the font with the indicated name and size.  Adds
 * info to the font list for the eventual search. 
E 3
 */
D 3
private int DefineFont(name, size)
char *name; {
    register struct font   *p;
    p = &fonts[nf];
    VOIDC strcpy(p->name, name);
    p->dsize = size;
    return (nf++);
E 3
I 3
private int 
DefineFont (name, size)
	char   *name;
{
	register struct font *p;

	p = &fonts[nf];
	VOIDC   strcpy (p->name, name);

	p->dsize = size;
	return (nf++);
E 3
}

I 5
ResetFont(indx, name, size)
	char   *name;
{
	register struct font *p;
E 5

I 5
	p = &fonts[indx];
	VOIDC   strcpy (p->name, name);
	p->dsize = size;
}

E 5
/* dump the fonts to the PS file for setup */
D 3
private VOID DumpFonts() {
    register struct font *f;
E 3
I 3
private VOID 
DumpFonts ()
{
	register struct font *f;
E 3

D 3
    ForAllFonts(f) {
        fprintf(OutFile,"%d %d /%s\n",f-&fonts[0],f->dsize*UperPt,f->name);
    }
    fprintf(OutFile, "%d SetUpFonts\n", nf);
E 3
I 3
	ForAllFonts (f) {
		fprintf (OutFile, "%d %d /%s\n", f - &fonts[0], f->dsize * UperPt, f->name);
	}
	fprintf (OutFile, "%d SetUpFonts\n", nf);
E 3
}

D 3

E 3
/* add a shown character to the PS file */
D 3
private VOID OUTputc(c)
register int c; {
    if (!showpending) {putc('(', OutFile); showpending = TRUE;}
    if (c == '\\' || c=='(' || c == ')') putc('\\', OutFile);
    if ((c > 0176) || (c < 040)) {
	putc('\\',OutFile);
	putc((c >> 6) +'0',OutFile);
	putc(((c >> 3) & 07)+'0', OutFile);
	putc((c & 07)+'0',OutFile);
    }
    else putc(c, OutFile);
E 3
I 3
private VOID 
OUTputc (c)
	register int c;
{
	if (!showpending) {
		putc ('(', OutFile);
		showpending = TRUE;
	}
	if (c == '\\' || c == '(' || c == ')')
		putc ('\\', OutFile);
	if ((c > 0176) || (c < 040)) {
		putc ('\\', OutFile);
		putc ((c >> 6) + '0', OutFile);
		putc (((c >> 3) & 07) + '0', OutFile);
		putc ((c & 07) + '0', OutFile);
	} else
		putc (c, OutFile);
E 3
}

I 3
/* put a correctly escaped string to the PS file */
private VOID
OUTstr(s)
	register char *s;
{
	if (!showpending) {
		putc ('(', OutFile);
		showpending = TRUE;
	}
	while (*s)
		OUTputc(*s++);

	putc(')', OutFile);
	showpending = FALSE;
}

E 3
/* Set the current font */
D 3
private VOID SetFont(f)
int f; {
    FlushShow();
    CurFont = f;
    fprintf(OutFile, "%d F\n",f);
E 3
I 3
private VOID 
SetFont (f)
	int     f;
{
	FlushShow ();
	CurFont = f;
	fprintf (OutFile, "%d F\n", f);
E 3
}

D 3
/* put a character onto the page at the desired X and Y positions.
 * If the current position doesn't agree with the desired position, put out
 * movement directives.  Leave the current position updated
 * to account for the character.
E 3
I 3
/*
 * put a character onto the page at the desired X and Y positions. If the
 * current position doesn't agree with the desired position, put out movement
 * directives.  Leave the current position updated to account for the
 * character. 
E 3
 */
D 3
private VOID ShowChar(c)
register int c; {
    register struct font   *f;
    register long nX, nY;
    static level = 0;
E 3
I 3
private VOID 
ShowChar (c)
	register int c;
{
	register struct font *f;
	register long nX, nY;
	static  level = 0;
I 4
D 6
	VOID PageEject();
E 6
I 6
	VOID PageEject(), InitPage();
E 6
E 4
E 3

D 3
    level++;
    f = &fonts[CurFont];
E 3
I 3
	level++;
	f = &fonts[CurFont];
E 3

D 3
    if (f->Xwid[c] == NOTDEF) {
	UndefChars++;
	if(ListOmitted)
	    fprintf(stderr, "%s: \\%03o not found in font %s\n",
	    	prog,c,f->name);
	if(level<=1){
	    ShowChar('\\');
	    ShowChar((c>>6)+'0');
	    ShowChar(((c>>3)&07)+'0');
	    ShowChar((c&07)+'0');
	    col += 3;
E 3
I 3
	if (f->Xwid[c] == NOTDEF) {
		UndefChars++;
		if (ListOmitted)
			fprintf (stderr, "%s: \\%03o not found in font %s\n",
				 prog, c, f->name);
		if (level <= 1) {
			ShowChar ('\\');
			ShowChar ((c >> 6) + '0');
			ShowChar (((c >> 3) & 07) + '0');
			ShowChar ((c & 07) + '0');
D 7
			col += 3;
E 7
		}
		level--;
		return;
E 3
	}
D 3
	level--;
	return;
    }
    nX = dX + f->Xwid[c]; /* resulting position after showing this char */
    nY = dY;
E 3
I 3
	nX = dX + f->Xwid[c];	/* resulting position after showing this char */
	nY = dY;
E 3

D 3
    if (c != ' ' || ((cX == dX) && (cY == dY))) {
	if(nX <= maxX) {
	    if (cX != dX) {
	       if (cY != dY) {
		  FlushShow();
		  /* absolute x, relative y */
		  fprintf(OutFile,"%ld %ld",dX, dY);
		  movepending = AbsXY;
		  }
	       else {
		  FlushShow();
		  fprintf(OutFile,"%ld",dX-cX); /* relative x */
		  movepending = RelX;
		  }
	    }
	    else if (cY != dY) {
		FlushShow();
		fprintf(OutFile,"%ld",dY-cY); /* relative y */
		movepending = RelY;
		}
	    OUTputc (c);
	    showpending = TRUE;
	    cX = nX;
	    cY = nY;
E 3
I 3
	if (c != ' ' || ((cX == dX) && (cY == dY))) {
D 4
		if (nX <= maxX) {
			if (cX != dX) {
				if (cY != dY) {
					FlushShow ();
					/* absolute x, relative y */
					fprintf (OutFile, "%ld %ld", dX, dY);
					movepending = AbsXY;
				} else {
					FlushShow ();
					fprintf (OutFile, "%ld", dX - cX);	/* relative x */
					movepending = RelX;
				}
			} else if (cY != dY) {
E 4
I 4
		/*
		 * If character doesn't fit on this line
		 * (and we're not at left margin), simulate newline
		 * and then call ourselves recursively.
		 */
		if (nX > maxX && dX > lX) {
			SeenText = TRUE;
			dY = lY = lY + crY;
			dX = lX = lX + crX;
D 6
			if ((dY < minY) || (--LinesLeft <= 0))
E 6
I 6
			if ((dY < minY) || (--LinesLeft <= 0)) {
E 6
				PageEject ();
I 6
				if (pagepending)
					InitPage ();
			}
E 6
D 7
			col = 1;
E 7
			ShowChar(c);
I 6
D 7
			col++;
E 7
E 6
			level--;
			return;
		}
		if (cX != dX) {
			if (cY != dY) {
E 4
				FlushShow ();
D 4
				fprintf (OutFile, "%ld", dY - cY);	/* relative y */
				movepending = RelY;
E 4
I 4
				/* absolute x, relative y */
				fprintf (OutFile, "%ld %ld", dX, dY);
				movepending = AbsXY;
			} else {
				FlushShow ();
				fprintf (OutFile, "%ld", dX - cX);	/* relative x */
				movepending = RelX;
E 4
			}
D 4
			OUTputc (c);
			showpending = TRUE;
			cX = nX;
			cY = nY;
		} else
			TruncChars++;
E 4
I 4
		} else if (cY != dY) {
			FlushShow ();
			fprintf (OutFile, "%ld", dY - cY);	/* relative y */
			movepending = RelY;
		}
		OUTputc (c);
		showpending = TRUE;
		cX = nX;
		cY = nY;
E 4
E 3
	}
D 3
	else TruncChars++;
    }
    dX = nX;
    dY = nY;
E 3
I 3
	dX = nX;
	dY = nY;
E 3

D 3
    level--;
E 3
I 3
	level--;
E 3
}

/* put out a shown string to the PS file */
D 3
private VOID ShowStr(s)
register char *s; {
    while (*s) {
	if (*s >= 040) ShowChar (*s);
	s++;
    }
E 3
I 3
private VOID 
ShowStr (s)
	register char *s;
{
	while (*s) {
		if (*s >= 040)
			ShowChar (*s);
		s++;
	}
E 3
}

/* flush pending show */
D 3
private FlushShow() {
    if (showpending) {
       putc(')',OutFile);
	switch (movepending) {
	    case RelX:
		putc('X',OutFile);
		break;
	    case RelY:
	    	putc('Y',OutFile);
		break;
	    case AbsXY:
	    	putc('B',OutFile);
		break;
	    case None:
	    	putc('S',OutFile);
	    	break;
E 3
I 3
private 
FlushShow ()
{
	if (showpending) {
		putc (')', OutFile);
		switch (movepending) {
		case RelX:
			putc ('X', OutFile);
			break;
		case RelY:
			putc ('Y', OutFile);
			break;
		case AbsXY:
			putc ('B', OutFile);
			break;
		case None:
			putc ('S', OutFile);
			break;
		}
		putc ('\n', OutFile);
		movepending = None;
		showpending = FALSE;
E 3
	}
D 3
	putc('\n',OutFile);
	movepending = None;
	showpending = FALSE;
    }
E 3
}

/* put out a page heading to the PS file */
D 3
private VOID InitPage() {
    char header[200];
    register int OldFont = CurFont;
E 3
I 3
private VOID 
InitPage ()
{
	char    header[200];
	register int OldFont = CurFont;
E 3

D 3
    TotalPages++;
    fprintf(OutFile, "%%%%Page: ? %d\n", TotalPages);
    fprintf(OutFile, "StartPage\n");
    SeenText = FALSE;
    cX = cY = -1;
    showpending = pagepending = FALSE;
    FirstCol = TRUE;
    if (Rotated) {
        fprintf(OutFile, "Landscape\n");
	lX = dX = UperInch / 4;
	lY = dY = PageLength - (UperHLine * 3) / 2;
	maxX = TruePageLength;
/*	minY = (PageLength - TruePageWidth) + 3*UperLine+480; */
	minY = (TruePageLength-TruePageWidth)+(TruePageWidth-PageWidth)/2;
    }
    else {
	lX = dX = TwoColumn ? (UperInch * 0.3) : ((UperInch * 5)/8);
	lY = dY = PageLength - UperHLine;
	maxX = TruePageWidth;
	minY = (UperInch/4);	/* 0.25 inches */
    }
    movepending = None;
    cX = dX; cY = dY;

    if (!NoTitle) {
	if (Gaudy) {
	    fprintf(OutFile, "(%s)(%s)[%s](%d)Gaudy\n",
		UsersHeader, Header, FileDate, ++Page);
	    cX = cY = 0; /* force moveto here */
E 3
I 3
	TotalPages++;
	fprintf (OutFile, "%%%%Page: ? %d\n", TotalPages);
	fprintf (OutFile, "StartPage\n");
	SeenText = FALSE;
	cX = cY = -1;
	showpending = pagepending = FALSE;
	FirstCol = TRUE;
	if (Rotated) {
		fprintf (OutFile, "Landscape\n");
		lX = dX = UperInch / 4 + Xoffset;
		lY = dY = PageLength - (UperHLine * 3) / 2;
		maxX = TruePageLength;
		/* minY = (PageLength - TruePageWidth) + 3*UperLine+480; */
		minY = (TruePageLength - TruePageWidth) + (TruePageWidth - PageWidth) / 2;
	} else {
		lX = dX = Xoffset +
			   (TwoColumn? (UperInch * 0.3) : ((UperInch * 5) / 8));
		lY = dY = PageLength - UperHLine;
		maxX = TruePageWidth;
		minY = (UperInch / 4);	/* 0.25 inches */
E 3
	}
D 3
	else {
	    SetFont(HeaderFont);
	    fprintf(OutFile, "%ld %ld ", cX, cY);
	    movepending = AbsXY;
	    if (UsersHeader) {
		if (*UsersHeader == 0) {
		    fprintf(OutFile,"()B\n");
		    movepending = None;
		    showpending = FALSE;
E 3
I 3
	movepending = None;
	cX = dX;
	cY = dY;

	if (!NoTitle) {
		if (Gaudy) {
			OUTstr(UsersHeader);
D 4
			OUTstr(Header);
E 4
I 4
			if (Header2)
			    OUTstr(Header2);
			else
			    OUTstr(Header);
E 4
			fprintf (OutFile, "[%s](%d)Gaudy\n", FileDate, ++Page);
			cX = cY = 0;	/* force moveto here */
		} else {
			SetFont (HeaderFont);
			fprintf (OutFile, "%ld %ld ", cX, cY);
			movepending = AbsXY;
			if (UsersHeader) {
				if (*UsersHeader == 0) {
					fprintf (OutFile, "()B\n");
					movepending = None;
					showpending = FALSE;
				} else
					ShowStr (UsersHeader);
			} else {
				VOIDC sprintf (header, "%s        %s        %d",
					       Header? Header : "              ", FileDate, ++Page);

				ShowStr (header);
			}
			FlushShow ();
E 3
		}
D 3
		else ShowStr(UsersHeader);
	    }
	    else {
		VOIDC sprintf(header, "%s        %s        %d",
			Header ? Header : "              ", FileDate, ++Page);
		ShowStr(header);
	    }
	    FlushShow();
E 3
I 3
		dX = lX = lX + crX * 2;
		dY = lY = lY + crY * 2;
	} else {
		/* fake it to force a moveto */
		cX = cY = 0;
E 3
	}
D 3
	dX = lX = lX + crX * 2;
	dY = lY = lY + crY * 2;
    }
    else {
	/* fake it to force a moveto */
	cX = cY = 0;
    }
    if (TwoColumn) maxX = maxX/2 - BSWidth;
    else maxX -= ((long) (UperInch * 0.3));
    LineMax = (lY - minY) / (-crY);
    if ((Lines <= 0) || (Lines > LineMax)) Lines = LinesLeft = LineMax;
    else LinesLeft = Lines;
    SetFont(OldFont);
E 3
I 3
	if (TwoColumn)
		maxX = maxX / 2 - BSWidth;
	else
		maxX -= ((long) (UperInch * 0.3));
	LineMax = (lY - minY) / (-crY);
	if ((Lines <= 0) || (Lines > LineMax))
		Lines = LinesLeft = LineMax;
	else
		LinesLeft = Lines;
	SetFont (OldFont);
E 3
}

D 3
private VOID ClosePage() {
    FlushShow();
    if (!pagepending) fprintf(OutFile,"EndPage\n");
    pagepending = TRUE;
E 3
I 3
private VOID 
ClosePage ()
{
	FlushShow ();
	if (!pagepending)
		fprintf (OutFile, "EndPage\n");
	pagepending = TRUE;
E 3
}

/* skip to a new page */
D 3
private VOID PageEject() {
    if (TwoColumn && FirstCol) {
	FirstCol = FALSE;
	if (Rotated) {
	    lY = dY = PageLength - (UperHLine * 3) / 2;
	    lX = dX = TruePageLength / 2;
	    maxX = TruePageLength - UperInch * 0.3;
	}
	else {
	    lY = dY = PageLength - UperHLine;
	    lX = dX = TruePageWidth / 2;
	    maxX = TruePageWidth - UperInch * 0.3;
	}
	if (!NoTitle) {
	    dX = lX = lX + crX * 2;
	    dY = lY = lY + crY * 2;
	}
    }
    else ClosePage();
    LinesLeft = Lines;
    SeenText = FALSE;
E 3
I 3
private VOID 
PageEject ()
{
	if (TwoColumn && FirstCol) {
		FirstCol = FALSE;
		if (Rotated) {
			lY = dY = PageLength - (UperHLine * 3) / 2;
			lX = dX = Xoffset + TruePageLength / 2;
			maxX = TruePageLength - UperInch * 0.3;
		} else {
			lY = dY = PageLength - UperHLine;
			lX = dX = Xoffset + TruePageWidth / 2;
			maxX = TruePageWidth - UperInch * 0.3;
		}
		if (!NoTitle) {
			dX = lX = lX + crX * 2;
			dY = lY = lY + crY * 2;
		}
	} else
		ClosePage ();
	LinesLeft = Lines;
	SeenText = FALSE;
E 3
}

D 3
private VOID CommentHeader() {
    long clock;
    struct passwd *pswd;
    char hostname[40];
    /* copy the file, prepending a new comment header */
    fprintf(OutFile,"%%!%s\n",COMMENTVERSION);
    fprintf(OutFile,"%%%%Creator: ");
    pswd = getpwuid((int) getuid());
    VOIDC gethostname(hostname, (int) sizeof hostname);
    fprintf(OutFile,"%s:%s (%s)\n", hostname, pswd->pw_name, pswd->pw_gecos);
    fprintf(OutFile,"%%%%Title: %s\n",(FileName?FileName:"stdin"));
    fprintf(OutFile,"%%%%CreationDate: %s",(VOIDC time(&clock),ctime(&clock)));
E 3
I 3
private VOID 
CommentHeader ()
{
	long    clock;
	struct passwd *pswd;
	char    hostname[40];

	/* copy the file, prepending a new comment header */
	fprintf (OutFile, "%%!%s\n", COMMENTVERSION);
	fprintf (OutFile, "%%%%Creator: ");
	pswd = getpwuid ((int) getuid ());
	VOIDC   gethostname (hostname, (int) sizeof hostname);

	fprintf (OutFile, "%s:%s (%s)\n", hostname, pswd->pw_name, pswd->pw_gecos);
	fprintf (OutFile, "%%%%Title: %s\n", (FileName ? FileName : "stdin"));
	fprintf (OutFile, "%%%%CreationDate: %s", (VOIDC time (&clock), ctime (&clock)));
E 3
}

/* Copy the standard input file to the PS file */
D 3
private VOID CopyFile() {
    register int c;
E 3
I 3
private VOID 
CopyFile ()
{
	register int c;
E 3

D 3
    col = 1;
    if (OutFile == 0) {
	if (OutOnly) {
	   OutFile = PipeOut ? stdout : fopen(OutName,"w");
E 3
I 3
D 7
	col = 1;
E 7
	if (OutFile == 0) {
		if (OutOnly) {
			OutFile = PipeOut ? stdout : fopen (OutName, "w");
		} else {
			VOIDC   mktemp (mstrcat (TempName, tempdir,
				            ENSCRIPTTEMP, sizeof TempName));
			VOIDC   strcpy (OutName, TempName);

			VOIDC   umask (077);

			OutFile = fopen (TempName, "w");
		}
E 3
	}
D 3
	else {
	    VOIDC mktemp(mstrcat(TempName,tempdir,
	    	ENSCRIPTTEMP,sizeof TempName));
	    VOIDC strcpy(OutName,TempName);
#ifdef SYSV
	    VOIDC umask(0);
#else
	    VOIDC umask(077);
#endif
	    OutFile = fopen(TempName, "w");
E 3
I 3
	if (OutFile == NULL) {
		fprintf (stderr, "%s: can't create PS file %s\n", prog, TempName);
		exit (1);
E 3
	}
D 3
    }
    if (OutFile == NULL) {
	fprintf(stderr, "%s: can't create PS file %s\n",prog,TempName);
	exit(1);
    }
    if (!ScannedFonts) {
	ScannedFonts = TRUE;
	ScanFont();
    }
    if (!Cvted) {
	CommentHeader();
	if (nf) {
	    register struct font *f;
	    fprintf(OutFile,"%%%%DocumentFonts:");
 	    ForAllFonts(f) {
		fprintf(OutFile," %s",f->name);
	    }
	    if(Gaudy) {
		fprintf(OutFile, " Times-Roman Times-Bold Helvetica-Bold");
	    }
	    fprintf(OutFile,"\n");
E 3
I 3
	if (!ScannedFonts) {
		ScannedFonts = TRUE;
		ScanFont ();
E 3
	}
D 3
	/* copy in fixed prolog */
	if (copyfile(mstrcat(tempstr,libdir,ENSCRIPTPRO,sizeof tempstr),
		OutFile)) {
	    fprintf(stderr,"%s: trouble copying prolog file\n",prog);
	    exit(1);
	}
	fprintf(OutFile,"StartEnscriptDoc %% end fixed prolog\n");
	DumpFonts();
	if(Gaudy)
		fprintf(OutFile, "%s %s InitGaudy\n",
		    Rotated ? "10.55" : "8.0", TwoColumn ? "true" : "false");
	if (PreFeed) {
	    fprintf(OutFile,"true DoPreFeed\n");
	}
	fprintf(OutFile,"%%%%EndProlog\n");
    }
    Cvted = TRUE;
E 3
I 3
	if (!Cvted) {
		CommentHeader ();
		if (nf) {
			register struct font *f;
E 3

D 3
    Page = 0;
    BadChars = 0;		/* give each file a clean slate */
    pagepending = TRUE;
    while ((c = getchar ()) != EOF)
	if ((c > 0177 || c < 0) && (!IgnoreGarbage)) {
	    if (BadChars++ > MAXBAD) {/* allow some kruft but not much */
	      fprintf(stderr,"%s: \"%s\" not a text file? Try -g.\n",
		    prog, FileName ? FileName : "(stdin)");
		    if (!PipeOut) VOIDC unlink(OutName);
	      exit(1);
	    }
E 3
I 3
			fprintf (OutFile, "%%%%DocumentFonts:");
			ForAllFonts (f) {
				fprintf (OutFile, " %s", f->name);
			}
			fprintf (OutFile, "\n");
		}
		/* copy in fixed prolog */
		if (copyfile (mstrcat (tempstr, libdir, ENSCRIPTPRO, sizeof tempstr),
			      OutFile)) {
			fprintf (stderr, "%s: trouble copying prolog file\n", prog);
			exit (1);
		}
		fprintf (OutFile, "StartEnscriptDoc %% end fixed prolog\n");
		DumpFonts ();
		if (Gaudy)
			fprintf (OutFile, "%s %s InitGaudy\n",
				 Rotated ? "10.55" : "8.0", TwoColumn ? "true" : "false");
		if (PreFeed) {
			fprintf (OutFile, "true DoPreFeed\n");
		}
		fprintf (OutFile, "%%%%EndProlog\n");
E 3
	}
D 3
	else
	    if (c >= ' ') {
		if (pagepending) InitPage();
		ShowChar (c);
		col++;
	    }
	    else switch (c) {
		case 010: /* backspace */
		    dX -= BSWidth;
		    break;
		case 015: /* carriage return ^M */
		    dY = lY;
		    dX = lX;
		    break;
		case 012: /* linefeed ^J */
		    if (pagepending) InitPage();
		    if (dX != lX || dY != lY || !LPTsimulate || SeenText){
			SeenText = TRUE;
			dY = lY = lY + crY;
			dX = lX = lX + crX;
		    }
		    else 
			LinesLeft = LineMax;
		    if ((dY < minY) || (--LinesLeft <= 0)) PageEject();
		    col = 1;
		    break;
		case 033: /* escape */
		    switch (c = getchar ()) {
			case '7': /* backup one line */
			    dY = lY = lY - crY;
			    dX = lX = lX - crX;
			    break;
			case '8':  /* backup 1/2 line */
			    dY -= crY / 2;
			    dX -= crX / 2;
			    break;
			case '9':  /* forward 1/2 linefeed */
			    dY += crY / 2;
			    dX += crX / 2;
			    break;
			case 'F': /* font setting */
			    c = getchar ();
			    if ('a' <= c && c <= 'z')
				if (fontindex[c - 'a'] >= 0)
				    SetFont (fontindex[c - 'a']);
				else {
				    fprintf(stderr,"%s: font '%c' not defined\n",
					prog, c);
				    exit(1);
				}
			    else {
				fprintf(stderr,"%s: bad font code in file: '%c'\n",
				    prog, c);
				exit(1);
			    }
			    break;
			case 'D': /* date string */
				VOIDC gets(DateStr);
				FileDate = DateStr;
E 3
I 3
	Cvted = TRUE;

	Page = 0;
	BadChars = 0;		/* give each file a clean slate */
	pagepending = TRUE;
	while ((c = getchar ()) != EOF)
		if ((c > 0177 || c < 0) && (!IgnoreGarbage)) {
			if (BadChars++ > MAXBAD) {	/* allow some kruft but
							 * not much */
				fprintf (stderr, "%s: \"%s\" not a text file? Try -g.\n",
				     prog, FileName ? FileName : "(stdin)");
				if (!PipeOut)
					VOIDC   unlink (OutName);

				exit (1);
			}
		} else if (c >= ' ') {
			if (pagepending)
				InitPage ();
			ShowChar (c);
D 7
			col++;
E 7
		} else
			switch (c) {
			case 010:	/* backspace */
				dX -= BSWidth;
E 3
				break;
D 3
			case 'U': /* new "user's" heading */
			    {
				static char header[100];
				VOIDC gets(header);
				UsersHeader = header;
E 3
I 3
			case 015:	/* carriage return ^M */
				dY = lY;
				dX = lX;
E 3
				break;
D 3
			    }
			case 'H': /* new heading */
			    {
				static char header[100];
E 3
I 3
			case 012:	/* linefeed ^J */
				if (pagepending)
					InitPage ();
				if (dX != lX || dY != lY || !LPTsimulate || SeenText) {
					SeenText = TRUE;
					dY = lY = lY + crY;
					dX = lX = lX + crX;
				} else
					LinesLeft = LineMax;
				if ((dY < minY) || (--LinesLeft <= 0))
					PageEject ();
D 7
				col = 1;
E 7
				break;
			case 033:	/* escape */
				switch (c = getchar ()) {
				case '7':	/* backup one line */
					dY = lY = lY - crY;
					dX = lX = lX - crX;
					break;
				case '8':	/* backup 1/2 line */
					dY -= crY / 2;
					dX -= crX / 2;
					break;
				case '9':	/* forward 1/2 linefeed */
					dY += crY / 2;
					dX += crX / 2;
					break;
				case 'F':	/* font setting */
					c = getchar ();
					if ('a' <= c && c <= 'z')
						if (fontindex[c - 'a'] >= 0)
							SetFont (fontindex[c - 'a']);
						else {
							fprintf (stderr, "%s: font '%c' not defined\n",
								 prog, c);
							exit (1);
						}
					else {
						fprintf (stderr, "%s: bad font code in file: '%c'\n",
							 prog, c);
						exit (1);
					}
					break;
				case 'D':	/* date string */
					VOIDC fgets (DateStr, sizeof(DateStr), stdin);
					FileDate = DateStr;
					break;
				case 'U':	/* new "user's" heading */
					{
						static char header[100];
						VOIDC   fgets (header, sizeof(header), stdin);
E 3

D 3
				VOIDC gets(header);
				ClosePage();
				Header = header;
				Page = 0;
E 3
I 3
						UsersHeader = header;
						break;
					}
				case 'H':	/* new heading */
					{
						static char header[100];

						VOIDC   fgets (header, sizeof(header), stdin);

						ClosePage ();
D 4
						Header = header;
E 4
I 4
						Header2 = header;
E 4
						Page = 0;
						break;
					}
				}
E 3
				break;
D 3
			    }
		    }
		    break;
		case '%': /* included PostScript line */
		    {	char psline[200];
			VOIDC gets(psline);
			fprintf(OutFile, "%s\n", psline);
			break;
		    }
		case 014: /* form feed ^L */
		    PageEject ();
		    col = 1;
		    break;
		case 011: /* tab ^I */
		    if (pagepending) InitPage();
		    col = (col - 1) / 8 * 8 + 9;
		    dX = lX + (col - 1) / 8 * TabWidth;
		    break;
		default: /* other control character, take your chances */
		    if (pagepending) InitPage();
		    ShowChar(c);
		    col++;
	    }
    ClosePage();
E 3
I 3
			case '%':	/* included PostScript line */
				{
					char    psline[200];
					VOIDC   fgets (psline, sizeof(psline), stdin);

					fprintf (OutFile, "%s\n", psline);
					break;
				}
			case 014:	/* form feed ^L */
				PageEject ();
D 7
				col = 1;
E 7
				break;
			case 011:	/* tab ^I */
				if (pagepending)
					InitPage ();
D 7
				col = (col - 1) / 8 * 8 + 9;
				dX = lX + (col - 1) / 8 * TabWidth;
E 7
I 7
D 8
				dX += TabWidth - (dX % TabWidth);
E 8
I 8
				dX += TabWidth - ((dX - lX) % TabWidth);
E 8
E 7
				break;
			default:	/* other control character, take your
					 * chances */
				if (pagepending)
					InitPage ();
				ShowChar (c);
D 7
				col++;
E 7
			}
	ClosePage ();
E 3
}


/*
D 3
 * close the PS file
E 3
I 3
 * close the PS file 
E 3
 */
D 3
private VOID ClosePS() {
    fprintf(OutFile,"%%%%Trailer\n");
    if (PreFeed) {
	fprintf(OutFile,"false DoPreFeed\n");
    }
    fprintf(OutFile,"EndEnscriptDoc\nEnscriptJob restore\n");
E 3
I 3
private VOID 
ClosePS ()
{
	fprintf (OutFile, "%%%%Trailer\n");
	if (PreFeed) {
		fprintf (OutFile, "false DoPreFeed\n");
	}
	fprintf (OutFile, "EndEnscriptDoc\nEnscriptJob restore\n");
E 3
}


D 3
private VOID SetTime(tval)
long tval; {
    struct tm *tp;
E 3
I 3
private VOID 
SetTime (tval)
	long    tval;
{
	struct tm *tp;
E 3

D 3
    if (Gaudy) {
	tp = localtime(&tval);
	VOIDC sprintf(DateStr, "(%02d/%02d/%02d)(%02d:%02d:%02d)",
		tp->tm_year, tp->tm_mon+1, tp->tm_mday,
		tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
    else {
	VOIDC strcpy(DateStr, ctime(&tval));
	DateStr[24] = '\0'; /* get rid of newline */
    }
E 3
I 3
	if (Gaudy) {
		tp = localtime (&tval);
		VOIDC   sprintf (DateStr, "(%02d/%02d/%02d)(%02d:%02d:%02d)",
			           tp->tm_year, tp->tm_mon + 1, tp->tm_mday,
			               tp->tm_hour, tp->tm_min, tp->tm_sec);
	} else {
		VOIDC   strcpy (DateStr, ctime (&tval));
E 3

D 3
    FileDate = DateStr;
E 3
I 3
		DateStr[24] = '\0';	/* get rid of newline */
	}

	FileDate = DateStr;
E 3
}


D 3

#ifdef SYSV
D 2
#define ARGS "12gGBlL:oqrRkKmf:F:b:p:t:d:n:w:h"
E 2
I 2
#define ARGS "12gGBlL:oqQrRkKmf:F:b:p:t:d:n:w:h"
E 2
#else
D 2
#define ARGS "12gGBlL:oqrRkKf:F:b:p:J:C:P:#:mh"
E 2
I 2
#define ARGS "12gGBlL:oqQrRkKf:F:b:p:J:C:P:#:mh"
E 2
#endif
E 3

D 3
private VOID ParseArgs(ac, av)
int ac;
char **av; {
    int argp;
E 3

D 3
    while ((argp = getopt(ac, av, ARGS)) != EOF) {
	debugp((stderr,"option: %c\n",argp));
	switch (argp) {
	    case '1': TwoColumn = FALSE; break;
	    case '2': TwoColumn = TRUE; break;
	    case 'G':
		Gaudy = TRUE;
		if (UsersHeader == NULL) UsersHeader = "";
		if (Header == NULL) Header = "";
		break;
	    case 'g': IgnoreGarbage = TRUE; break;
	    case 'B': NoTitle = TRUE; break;
	    case 'l': LPTsimulate = TRUE; NoTitle = TRUE; Lines = 66; break;
	    case 'L': Lines = atoi(optarg); break;
	    case 'o': ListOmitted = TRUE; break;
D 2
	    case 'q': BeQuiet = !BeQuiet; break;
E 2
I 2
	    case 'q': BeQuiet = TRUE; break;
	    case 'Q': BeQuiet = !BeQuiet; break;
E 2
	    case 'r': Rotated = TRUE; break;
	    case 'R': Rotated = FALSE; break;
	    case 'k': PreFeed = TRUE; break;
	    case 'K': PreFeed = FALSE; break;
	    case 'f': {
		register char font = 'r';
		int *whichfont;
E 3
I 3
D 4
#define ARGS "12gGBlL:oqrRkKf:F:b:p:J:C:P:#:mhO:"
E 4
I 4
#define ARGS "12gGBlL:oqrRkKf:F:b:p:J:C:P:#:mhO:s:v"
E 4
E 3

D 3
	        if (*optarg == '-') {
		    font = *++optarg;
		    optarg++;
E 3
I 3
private VOID ParseArgs (ac, av)
	int     ac;
	char  **av;
{
	int     argp;

	while ((argp = getopt (ac, av, ARGS)) != EOF) {
		debugp ((stderr, "option: %c\n", argp));
		switch (argp) {
		case '1':
			TwoColumn = FALSE;
			break;
		case '2':
			TwoColumn = TRUE;
			break;
		case 'G':
			Gaudy = TRUE;
			if (UsersHeader == NULL)
				UsersHeader = "";
			if (Header == NULL)
				Header = "";
I 5
			/* warning: fonts must be defined in this order! */
			ResetFont(HeaderFont, GHEADFONT, GHEADSZ);
			if (SHeaderFont == -1)
				SHeaderFont = DefineFont(SHEADFONT, SHEADSZ);
E 5
D 4
			SHeaderFont = DefineFont(SHEADFONT, 12);
			DateFont = DefineFont(DATEFONT, 12);
			PgNumFont = DefineFont(PGNUMFONT, 24);
E 4
I 4
			DateFont = DefineFont(DATEFONT, DATESZ);
			PgNumFont = DefineFont(PGNUMFONT, PGNUMSZ);
E 4
			break;
		case 'g':
			IgnoreGarbage = TRUE;
			break;
		case 'B':
			NoTitle = TRUE;
			break;
		case 'l':
			LPTsimulate = TRUE;
			NoTitle = TRUE;
			Lines = 66;
			break;
		case 'L':
			Lines = atoi (optarg);
			break;
		case 'o':
			ListOmitted = TRUE;
			break;
		case 'q':
			BeQuiet = TRUE;
			break;
		case 'r':
			Rotated = TRUE;
			break;
		case 'R':
			Rotated = FALSE;
			break;
		case 'k':
			PreFeed = TRUE;
			break;
		case 'K':
			PreFeed = FALSE;
			break;
		case 'f':{
				register char font = 'r';
				int    *whichfont;

				if (*optarg == '-') {
					font = *++optarg;
					optarg++;
				}
				if ((font < 'a') || ('z' < font)) {
					fprintf (stderr,
						 "%s: '%c' isn't a valid font designator.\n",
						 prog, font);
					exit (1);
				}
				whichfont = &fontindex[font - 'a'];
				if (*whichfont < 0)
					*whichfont = nf++;
				decodefont (optarg, &fonts[*whichfont]);
I 4
				if (font == 'r')
					SeenFont++;
E 4
			}
			break;
		case 'F':
I 4
			if (HeaderFont == -1)
				HeaderFont = nf++;
E 4
			decodefont (optarg, &fonts[HeaderFont]);
			break;
		case 'b':
			UsersHeader = optarg;
			break;
I 4
		case 's':
			Header2 = optarg;
			break;
E 4
		case 'p':
			OutOnly = TRUE;
			VOIDC   strcpy (OutName, optarg);

			if (strcmp (OutName, "-") == 0)
				PipeOut = TRUE;
			break;
		case 'h':
			spoolNoBurst = TRUE;
			break;
			/* BSD lpr options processing */
		case 'm':
			spoolNotify = argp;
			break;
		case '#':
			spoolCopies = optarg;
			break;
		case 'C':
			spoolJobClass = optarg;
			break;
		case 'J':
			spoolJobName = optarg;
			break;
		case 'P':
			PrinterName = optarg;
			break;
		case '?':
			/* bad option */
			break;
		case 'O':
			Xoffset = atof(optarg) * (double)UperInch;
			if (Xoffset < 0)
				Xoffset = 0;
			break;
I 4
		case 'v':
			Verbose = TRUE;
			break;
E 4
		default:
			break;
E 3
		}
D 3
		if ((font < 'a') || ('z' < font)) {
		    fprintf(stderr,
			"%s: '%c' isn't a valid font designator.\n",
			prog, font);
		    exit(1);
		}
		whichfont = &fontindex[font - 'a'];
		if (*whichfont < 0)
		    *whichfont = nf++;
		decodefont (optarg, &fonts[*whichfont]);
	        }
		break;
	    case 'F':
		decodefont (optarg, &fonts[HeaderFont]);
		break;
	    case 'b':
	        UsersHeader = optarg;
		break;
	    case 'p':
		OutOnly = TRUE;
		VOIDC strcpy(OutName,optarg);
		if (strcmp(OutName,"-") == 0) PipeOut = TRUE;
		break;
	    case 'h': spoolNoBurst = TRUE; break;
#ifdef SYSV
	/* SYS V lp options processing */
	    case 'm': case 'w':
	    	spoolNotify = argp; break;
	    case 'n': spoolCopies = optarg; break;
	    case 'd': PrinterName = optarg; break;
	    case 't': spoolTitle = optarg; break;
#else
	/* BSD lpr options processing */
	    case 'm': spoolNotify = argp; break;
	    case '#': spoolCopies = optarg; break;
	    case 'C': spoolJobClass = optarg; break;
	    case 'J': spoolJobName = optarg; break;
	    case 'P': PrinterName = optarg; break;
#endif
	    case '?':
	        /* bad option */
		break;
	    default:
	    	break;
E 3
	}
D 3
    }
E 3
}


/* addarg is used to construct an argv for the spooler */
D 3
private VOID addarg(argv, argstr, argc)
char **argv;
char *argstr;
register int *argc; {
    register char *p = (char *) malloc((unsigned) (strlen(argstr) + 1));
    VOIDC strcpy(p, argstr);
    argv[(*argc)++] = p;
    argv[*argc] = '\0';
E 3
I 3
private VOID 
addarg (argv, argstr, argc)
	char  **argv;
	char   *argstr;
	register int *argc;
{
	register char *p = (char *) malloc ((unsigned) (strlen (argstr) + 1));
	VOIDC   strcpy (p, argstr);

	argv[(*argc)++] = p;
	argv[*argc] = '\0';
E 3
}

D 3
    
private VOID SpoolIt() {
    char temparg[200];
    char *argstr[200];
    int nargs = 0;
#ifdef SYSV
    int cpid, wpid;
#endif
E 3

D 3
    addarg(argstr, LPR, &nargs);
#ifdef SYSV
    addarg(argstr, "-c", &nargs);
E 3
I 3
private VOID 
SpoolIt ()
{
	char    temparg[200];
	char   *argstr[200];
	int     nargs = 0;
E 3

D 3
    if ((PrinterName == NULL) && ((PrinterName = envget("LPDEST")) == NULL)) {
	PrinterName = POSTSCRIPTPRINTER;
    }
    VOIDC sprintf(temparg,"-d%s",PrinterName);
    addarg(argstr, temparg, &nargs);
    if (!BeQuiet) fprintf(stderr,"spooled to %s\n",PrinterName);
E 3

D 3
    if (spoolNotify) {
	VOIDC sprintf(temparg,"-%c",spoolNotify);
	addarg(argstr, temparg, &nargs);
    }
    if (atoi(spoolCopies) > 1) {
	VOIDC sprintf(temparg,"-n%s",spoolCopies);
	addarg(argstr, temparg, &nargs);
    }
    if (BeQuiet) {
	addarg(argstr, "-s", &nargs);
    }
    if (spoolTitle) {
	VOIDC sprintf(temparg,"-t%s",spoolTitle);
    }
    else {
	VOIDC sprintf(temparg, "-t%s", (FileName == NULL) ? "stdin" : FileName);
    }
    if (spoolNoBurst) {
	addarg(argstr,"-o-h",&nargs);
    }
    addarg(argstr, temparg, &nargs);
E 3
I 3
	addarg (argstr, LPR, &nargs);
	/* BSD spooler */
	if (atoi (spoolCopies) > 1) {
		VOIDC   sprintf (temparg, "-#%s", spoolCopies);
E 3

D 3
#else
    /* BSD spooler */
    if (atoi(spoolCopies) > 1) {
	VOIDC sprintf(temparg,"-#%s",spoolCopies);
	addarg(argstr, temparg, &nargs);
    }
    if ((PrinterName == NULL) && ((PrinterName = envget("PRINTER")) == NULL)){
	PrinterName = POSTSCRIPTPRINTER;
    }
    VOIDC sprintf(temparg,"-P%s",PrinterName);
    addarg(argstr, temparg, &nargs);
    if (!BeQuiet) fprintf(stderr,"spooled to %s\n",PrinterName);
E 3
I 3
		addarg (argstr, temparg, &nargs);
	}
	if ((PrinterName == NULL) && ((PrinterName = envget ("PRINTER")) == NULL)) {
		PrinterName = POSTSCRIPTPRINTER;
	}
	VOIDC   sprintf (temparg, "-P%s", PrinterName);
E 3

D 3
    if (spoolJobClass) {
	addarg(argstr, "-C", &nargs);
	addarg(argstr, spoolJobClass, &nargs);
    }
    addarg(argstr, "-J", &nargs);
    if (spoolJobName) {
	addarg(argstr, spoolJobName, &nargs);
    }
    else {
	if (!FileName) addarg(argstr, "stdin", &nargs);
	else addarg(argstr, FileName, &nargs);
    }
    if (spoolNotify) {
	addarg(argstr, "-m", &nargs);
    }
    if (spoolNoBurst) {
	addarg(argstr, "-h", &nargs);
    }
E 3
I 3
	addarg (argstr, temparg, &nargs);
D 4
	if (!BeQuiet)
		fprintf (stderr, "spooled to %s\n", PrinterName);
E 4
E 3

D 3
    /* remove the temporary file after spooling */
    addarg(argstr, "-r", &nargs); /* should we use a symbolic link too? */
#endif
    addarg(argstr, TempName, &nargs);
E 3
I 3
	if (spoolJobClass) {
		addarg (argstr, "-C", &nargs);
		addarg (argstr, spoolJobClass, &nargs);
	}
	addarg (argstr, "-J", &nargs);
	if (spoolJobName) {
		addarg (argstr, spoolJobName, &nargs);
	} else {
		if (!FileName)
			addarg (argstr, "stdin", &nargs);
		else
			addarg (argstr, FileName, &nargs);
	}
	if (spoolNotify) {
		addarg (argstr, "-m", &nargs);
	}
	if (spoolNoBurst) {
		addarg (argstr, "-h", &nargs);
	}
	/* remove the temporary file after spooling */
	addarg (argstr, "-r", &nargs);	/* should we use a symbolic link too? */
	addarg (argstr, TempName, &nargs);
E 3

#ifdef DEBUG
D 3
    { int i;
    fprintf(stderr,"called spooler with: ");
    for (i = 0; i < nargs ; i++) fprintf(stderr,"(%s)",argstr[i]);
    fprintf(stderr,"\n");
    }
#endif
E 3
I 3
	{
		int     i;
E 3

D 3
#ifdef SYSV
    if ((cpid = fork()) < 0) {pexit2(prog,"can't fork spooler",1);}
    else if (cpid) {
	while (wpid = wait((int *) 0) > 0) {if (wpid == cpid) break;}
	VOIDC unlink(TempName);
    }
    else {
	execvp(LPR, argstr);
	pexit2(prog,"can't exec spooler",1);
    }
#else
    execvp(LPR, argstr);
    pexit2(prog,"can't exec spooler",1);
E 3
I 3
		fprintf (stderr, "called spooler with: ");
		for (i = 0; i < nargs; i++)
			fprintf (stderr, "(%s)", argstr[i]);
		fprintf (stderr, "\n");
	}
E 3
#endif
I 3

	execvp (LPR, argstr);
	pexit2 (prog, "can't exec spooler", 1);
E 3
}


private char *eargv[60];
private int eargc = 1;


D 3
main(argc, argv)
int argc;
char  **argv; {
    register char *p;		/* pointer to "ENSCRIPT" in env */
E 3
I 3
main (argc, argv)
	int     argc;
	char  **argv;
{
	register char *p;	/* pointer to "ENSCRIPT" in env */
E 3

D 3
    prog = *argv;		/* argv[0] is program name */
E 3
I 3
	prog = *argv;		/* argv[0] is program name */
E 3

D 3
    debugp((stderr,"PL %ld PW %ld TPL %ld TPW %ld\n",PageLength,PageWidth,TruePageLength,TruePageWidth));
E 3
I 3
	debugp ((stderr, "PL %ld PW %ld TPL %ld TPW %ld\n", PageLength, PageWidth, TruePageLength, TruePageWidth));
E 3

D 3
    if (signal(SIGINT, int1) == SIG_IGN) {
	VOIDC signal(SIGINT, SIG_IGN);
	VOIDC signal(SIGQUIT, SIG_IGN);
	VOIDC signal(SIGHUP, SIG_IGN);
	VOIDC signal(SIGTERM, SIG_IGN);
    }
    else {
	VOIDC signal(SIGQUIT, int1);
	VOIDC signal(SIGHUP, int1);
	VOIDC signal(SIGTERM, int1);
    }
E 3
I 3
	if (signal (SIGINT, int1) == SIG_IGN) {
		VOIDC   signal (SIGINT, SIG_IGN);
		VOIDC   signal (SIGQUIT, SIG_IGN);
		VOIDC   signal (SIGHUP, SIG_IGN);
		VOIDC   signal (SIGTERM, SIG_IGN);
	} else {
		VOIDC   signal (SIGQUIT, int1);
		VOIDC   signal (SIGHUP, int1);
		VOIDC   signal (SIGTERM, int1);
	}
E 3

D 3
    {	register int    i;
	for (i = 0; i < 26; i++)
	    fontindex[i] = -1;
    }
E 3
I 3
	{
		register int i;
E 3

D 3
    if ((libdir = envget("PSLIBDIR")) == NULL) libdir = LibDir;
    if ((tempdir = envget("PSTEMPDIR")) == NULL) tempdir = TempDir;
E 3
I 3
		for (i = 0; i < 26; i++)
			fontindex[i] = -1;
	}
E 3

D 3
    Roman = CurFont = DefineFont (BODYROMAN, 10);
    HeaderFont = DefineFont (HEADFONT, 10);
E 3
I 3
	if ((libdir = envget ("PSLIBDIR")) == NULL)
		libdir = LibDir;
	if ((tempdir = envget ("PSTEMPDIR")) == NULL)
		tempdir = TempDir;
E 3

D 3
    /* process args in environment variable ENSCRIPT */
    if (p = envget("ENSCRIPT")) {
	while (1) {
	    register char quote = ' ';
	    while (*p == ' ') p++;
	    if ((*p == '"') || (*p == '\'')) quote = *p++;
	    eargv[eargc++] = p;
	    while ((*p != quote) && (*p != '\0')) p++;
	    if (*p == '\0') break;
	    *p++ = '\0';
E 3
I 3
D 4
	Roman = CurFont = DefineFont (BODYROMAN, 10);
	HeaderFont = DefineFont (HEADFONT, 10);
E 4
I 4
	Roman = CurFont = DefineFont (BODYROMAN, BODYSZ);
I 5
	HeaderFont = DefineFont (HEADFONT, HEADSZ);
E 5
E 4

	/* process args in environment variable ENSCRIPT */
	if (p = envget ("ENSCRIPT")) {
		while (1) {
			register char quote = ' ';

			while (*p == ' ')
				p++;
			if ((*p == '"') || (*p == '\''))
				quote = *p++;
			eargv[eargc++] = p;
			while ((*p != quote) && (*p != '\0'))
				p++;
			if (*p == '\0')
				break;
			*p++ = '\0';
		}
		ParseArgs (eargc, eargv);
		if (eargc != optind) {
			fprintf (stderr, "%s: bad environment variable ENSCRIPT \"%s\"\n",
				 prog, envget ("ENSCRIPT"));
			exit (1);
		}
E 3
	}
D 3
	ParseArgs(eargc, eargv);
	if (eargc != optind) {
	    fprintf(stderr,"%s: bad environment variable ENSCRIPT \"%s\"\n",
	    	prog, envget("ENSCRIPT"));
	    exit(1);
	}
    }
E 3
I 3
	/* process the command line arguments */
	optind = 1;		/* reset getopt global */
	ParseArgs (argc, argv);
I 4
D 5
	if (!Gaudy) {
		if (HeaderFont == -1)
			HeaderFont = DefineFont (HEADFONT, HEADSZ);
	} else {
		if (HeaderFont == -1)
			HeaderFont = DefineFont (GHEADFONT, GHEADSZ);
		if (SHeaderFont == -1)
			SHeaderFont = DefineFont(SHEADFONT, SHEADSZ);
	}
E 5
E 4
E 3

D 3
    /* process the command line arguments */
    optind = 1; /* reset getopt global */
    ParseArgs(argc, argv);
E 3
I 3
	/* process non-option args */
	for (; optind < argc; optind++) {
		FileName = Header = argv[optind];
		if (freopen (FileName, "r", stdin) == NULL) {
			fprintf (stderr, "%s: can't open %s\n", prog, FileName);
			exit (1);
		}
		VOIDC   fstat (fileno (stdin), &S);
E 3

D 3
    /* process non-option args */
    for (; optind < argc ; optind++) {
	FileName = Header = argv[optind];
	if (freopen (FileName, "r", stdin) == NULL) {
	    fprintf(stderr, "%s: can't open %s\n", prog, FileName);
	    exit (1);
E 3
I 3
		SetTime (S.st_mtime);
		CopyFile ();
		VOIDC   fclose (stdin);

		SeenFile = TRUE;
E 3
	}
D 3
	VOIDC fstat(fileno (stdin), &S);
	SetTime(S.st_mtime);
	CopyFile();
	VOIDC fclose(stdin);
	SeenFile = TRUE;
    }
    if (!SeenFile) {
	FileName = Header = Gaudy ? "" : 0;
	VOIDC fstat(fileno (stdin), &S);
E 3
I 3
	if (!SeenFile) {
		FileName = Header = Gaudy ? "" : 0;
		VOIDC   fstat (fileno (stdin), &S);
E 3

D 3
	if ((S.st_mode & S_IFMT) == S_IFREG)
	    SetTime(S.st_mtime);
	else
	    SetTime(time((long *)0));
	CopyFile();
    }
E 3
I 3
		if ((S.st_mode & S_IFMT) == S_IFREG)
			SetTime (S.st_mtime);
		else
			SetTime (time ((long *) 0));
		CopyFile ();
	}
	if (Cvted) {
		ClosePS ();
		VOIDC   fclose (OutFile);
E 3

D 3
    if (Cvted) {
	ClosePS();
	VOIDC fclose(OutFile);
	OutFile = 0;
    }
    if (TruncChars && !BeQuiet)
	fprintf(stderr,"%s: %d characters omitted because of long lines.\n",
		prog, TruncChars);
    if (UndefChars && !BeQuiet)
	fprintf(stderr,"%s: %d characters omitted because of incomplete fonts.\n",
		prog, UndefChars);
    if (!BeQuiet && (TotalPages > 0)) {
	fprintf(stderr,"[ %d page%s * %s cop%s ] ",
		TotalPages, TotalPages > 1 ? "s" : "",
		spoolCopies, atoi(spoolCopies) > 1 ? "ies" : "y" );
    }
    if (Cvted) {
D 2
	if (OutOnly && !BeQuiet) {
	    fprintf(stderr,"left in %s\n", OutName);
E 2
I 2
	if (OutOnly) {
	    if (!BeQuiet) 
		fprintf(stderr,"left in %s\n", OutName);
E 3
I 3
		OutFile = 0;
E 3
E 2
	}
D 3
	else {
	    SpoolIt(); /* does an exec */
E 3
I 3
	if (TruncChars && !BeQuiet)
		fprintf (stderr, "%s: %d characters omitted because of long lines.\n",
			 prog, TruncChars);
	if (UndefChars && !BeQuiet)
		fprintf (stderr, "%s: %d characters omitted because of incomplete fonts.\n",
			 prog, UndefChars);
D 4
	if (!BeQuiet && (TotalPages > 0)) {
		fprintf (stderr, "[ %d page%s * %s cop%s ] ",
			 TotalPages, TotalPages > 1 ? "s" : "",
			 spoolCopies, atoi (spoolCopies) > 1 ? "ies" : "y");
E 4
I 4
	if (Verbose && (TotalPages > 0)) {
	    fprintf(stderr,"[ %d page%s * %s cop%s ]\n",
		    TotalPages, TotalPages > 1 ? "s" : "",
		    spoolCopies, atoi(spoolCopies) > 1 ? "ies" : "y" );
E 4
E 3
	}
D 3
    }
E 3
I 3
D 4
	if (Cvted) {
		if (!BeQuiet) {
			fprintf (stderr, "left in %s\n", OutName);
		}
		if (!OutOnly) {
			SpoolIt ();	/* does an exec */
		}
E 4
I 4
	if (Cvted && !OutOnly) {
		SpoolIt ();	/* does an exec */
E 4
	}
E 3
}


/* signal catcher */
D 3
private VOID int1() {
    if ((!PipeOut) && (OutName != NULL) && (*OutName != '\0')) {
	VOIDC unlink(OutName);
    }
    exit(1);
E 3
I 3
private VOID 
int1 ()
{
	if ((!PipeOut) && (OutName != NULL) && (*OutName != '\0')) {
		VOIDC   unlink (OutName);
	}
	exit (1);
E 3
}
E 1
