h12396
s 00017/00008/00430
d D 1.6 85/05/03 12:51:28 slatteng 7 6
c added capability for specifying which point size to use for a particular font
e
s 00002/00000/00436
d D 1.5 85/02/26 14:16:28 slatteng 6 5
c added makefile-defnied bit directories
e
s 00005/00002/00431
d D 1.4 85/02/04 12:44:20 slatteng 5 4
c added sccs keywords and exit(0) at end
e
s 00129/00081/00304
d D 1.3 84/02/27 17:10:31 slatteng 4 2
c fix operands, added -c, fixed error reports, fixed -x & -y, etc...
e
s 00004/00004/00381
d R 1.3 84/02/20 15:43:52 slatteng 3 2
c change -t option to -o
e
s 00204/00032/00181
d D 1.2 83/09/23 14:20:49 slatteng 2 1
c revamped for lots of options, etc
e
s 00213/00000/00000
d D 1.1 83/08/17 14:38:06 slatteng 1 0
c date and time created 83/08/17 14:38:06 by slatteng
e
u
U
t
T
I 1
D 2
/* Font description file producer:  David Slattengren
E 2
I 2
D 5
/* Font description file producer for versatec fonts:  David Slattengren
E 5
I 5
/*	%M%	(Berkeley)	%E%	%I%
 *
 * Font description file producer for versatec fonts:  David Slattengren
E 5
E 2
 * Taken from vfontinfo by Andy Hertzfeld  4/79
 *
D 2
 *	Use:  mkfnt [-s] [-p#] [-r#] [-ddirectory] font
E 2
I 2
D 4
 *	Use:  mvfnt [ -nNAME ]  [ -s -a -t -l -p# -r# -f# -ddir ]
E 4
I 4
 *	Use:  makevfont [ -nNAME ]  [ -s -a -o -l -c -p# -r# -f# -ddir ]
E 4
 *		[ "-xs1,s2[;s1,s2...]" ]  [ "-ys1,s2[;s1,s2...]" ]  font
E 2
 *
D 4
 *	Mkfnt takes the font named "font" and produces a ditroff description
E 4
I 4
D 7
 *	Makefont takes the font named "font" and produces a ditroff description
E 4
D 2
 *	file from it.  The -s option tells mkfnt that this is a special font,
 *	and sould substitute special character names for the normal ones.  The
 *	-p# option tells what point size the DESC file has as it's "unitwidth"
 *	argument (default: 36).  The -r# option is the resolution of the device
 *	(default: 200, in units/inch).  The -d option tells where to look for
 *	fonts (default: /usr/lib/vfont).
E 2
I 2
 *	file from it.  The -n option takes the 1 or 2 letter troff name to put
E 7
I 7
 *	Makefont takes the font named "font" (with or without pointsize
 *	extension on the filename) and produces a ditroff description file
 *	from it.  The -n option takes the 1 or 2 letter troff name to put
E 7
 *	the description (default = XX).  The -f option takes an integer per-
D 4
 *	centage factor to multiply widths by.  The -s, -t and -a options select
E 4
I 4
 *	centage factor to multiply widths by.  The -s, -o and -a options select
E 4
 *	a different character mapping than for a "roman" font.  s = special;
D 4
 *	t = otimespec; a = ascii.  The -l option says the font has ligatures.
E 4
I 4
 *	o = otimespecal; a = ascii.  The -l option indicates it has ligatures.
 *	The -c option tells makevfont that the font is constant width and
 *	will set parameters appropriately.
E 4
 *
D 4
 *	Both -x and -y options allow character name mapping.  A semi-colon
 *	separated list of comma-separated character-name pairs follows the
 *	x or y.  Notice that there are no spaces in the -x or -y command.  It
 *	is also IMPORTANT to enclose these arguments in single quotes to stop
 *	the cshell from interpretting the contents.  A -x pair REPLACES the
 *	definition for s1 by s2.  A -y pair creates a synonym for s1 and calls
 *	it s2.  -x and -y MUST be sent after -s, -m, -i, or -a  if one of them
 *	is used.  Some synonyms are defaulted.  To remove a synonym or char-
 *	acter, leave out s2.
E 4
I 4
 *	Both -x and -y options allow character name mapping.  A colon separated
 *	list of comma-separated character-name pairs follows the x or y.
 *	Notice that there are no spaces in the -x or -y command.  A -x pair
 *	REPLACES the definition for s1 by s2.  A -y pair creates a synonym for
 *	s1 and calls it s2.  -x and -y MUST be sent after -s, -m, -i, or -a
 *	if one of them is used.  Some synonyms are defaulted.  To remove a
 *	synonym or character, leave out s2.
E 4
 *
D 4
 *	The -p# option tells what point size the DESC file has
 *	as it's "unitwidth" argument (default: 36).  The -r# option is the
 *	resolution of the device (default: 200, in units/inch).  The -d option
 *	tells where to find fonts (default: /usr/lib/vfont).
E 4
I 4
 *	The -p# option tells what point size the DESC file has as it's
 *	"unitwidth" argument (default: 36).  The -r# option is the resolution
 *	of the device (default: 200, in units/inch).  The -d option tells
 *	where to find fonts (default: /usr/lib/vfont).
E 4
E 2
 */

/*
 *  Here's an ascii character set, just in case you need it:

     | 00 nul| 01 soh| 02 stx| 03 etx| 04 eot| 05 enq| 06 ack| 07 bel|
     | 08 bs | 09 ht | 0a nl | 0b vt | 0c np | 0d cr | 0e so | 0f si |
     | 10 dle| 11 dc1| 12 dc2| 13 dc3| 14 dc4| 15 nak| 16 syn| 17 etb|
     | 18 can| 19 em | 1a sub| 1b esc| 1c fs | 1d gs | 1e rs | 1f us |
     | 20 sp | 21  ! | 22  " | 23  # | 24  $ | 25  % | 26  & | 27  ' |
     | 28  ( | 29  ) | 2a  * | 2b  + | 2c  , | 2d  - | 2e  . | 2f  / |
     | 30  0 | 31  1 | 32  2 | 33  3 | 34  4 | 35  5 | 36  6 | 37  7 |
     | 38  8 | 39  9 | 3a  : | 3b  ; | 3c  < | 3d  = | 3e  > | 3f  ? |
     | 40  @ | 41  A | 42  B | 43  C | 44  D | 45  E | 46  F | 47  G |
     | 48  H | 49  I | 4a  J | 4b  K | 4c  L | 4d  M | 4e  N | 4f  O |
     | 50  P | 51  Q | 52  R | 53  S | 54  T | 55  U | 56  V | 57  W |
     | 58  X | 59  Y | 5a  Z | 5b  [ | 5c  \ | 5d  ] | 5e  ^ | 5f  _ |
     | 60  ` | 61  a | 62  b | 63  c | 64  d | 65  e | 66  f | 67  g |
     | 68  h | 69  i | 6a  j | 6b  k | 6c  l | 6d  m | 6e  n | 6f  o |
     | 70  p | 71  q | 72  r | 73  s | 74  t | 75  u | 76  v | 77  w |
     | 78  x | 79  y | 7a  z | 7b  { | 7c  | | 7d  } | 7e  ~ | 7f del|

 *
 */

#include <stdio.h>
#include <ctype.h>
#include <vfont.h>
I 7
#include <strings.h>
E 7

char 	sccsid[] = "%W%	(Berkeley)	%G%";

#define MAGICN		0436	/* font file magic number */
#define PCNTUP		62	/* percent of maximum height for an ascender */
#define PCNTDOWN	73	/* percent of maximum droop for a descender */
I 6
#ifndef BITDIR
E 6
D 4
#define FONTDIR		"/usr/lib/vfont"
E 4
I 4
#define BITDIR		"/usr/lib/vfont"
I 6
#endif
E 6
E 4
D 2
#define IMDIR		"."
E 2
#define POINTSIZE	36	/* this is the "unitwidth" point size */
#define MINSIZE		6	/* the minimum and maximum point size values */
#define MAXSIZE		36	/*    acceptible for use as "unitwidth"s */
#define RESOLUTION	200	/* resolution of versatec (dots/inch) */
#define MINRES		10	/* check up on resolution input by setting */
#define MAXRES		100000	/*    absurdly out-of-range limits on them */
#define APOINT		72	/* 1/APOINT inches = 1 point */
I 2
#define SYNON		100	/* 2 * pairs allowed in synonym table */
E 2

I 2

E 2
struct header	FontHeader;
struct dispatch	disptable[256];

int	res = RESOLUTION;	/* resolution of the device (units/inch) */
int	pointsize = POINTSIZE;	/* point size being used for unitwidth */
I 2
int	factor = 100;		/* percent for magnifying (shrinking) widths */
E 2
int	psize;			/* point size of font actually used */
D 2
int	psizelist[] = { 36, 28, 24, 22, 20, 18, 16,
			14, 12, 11, 10, 9, 8, 7, 6, 0 };
E 2
I 2
int	psizelist[] = { 36,24,22,20,18,16,14,28,12,11,10,9,8,7,6,0 };
E 2

I 2
char	*fontname = "XX";	/* troff font name - set on command line */
E 2
D 4
char	*fontdir = FONTDIR;	/* place to look for fonts */
E 4
I 4
char	*fontdir = BITDIR;	/* place to look for fonts */
E 4
char	IName[100];		/* input file name put here */
char	*rdchar ();		/* function makes strings for ascii */
int	FID = -1;		/* input file number */

int	maxdown = 0;		/* size of the most "droopy" character */
int	maxup = 0;		/* size of the tallest character */
int	type;			/* 1, 2, or 3 for type of ascend/descending */
I 4
int	nullchar = -1;		/* finds non-existant character in the font */
E 4
D 2
int	specialf = 0;		/* flag "is this a special font?";  used to
				   determine which mapping array to look in. */
E 2
I 2
int	ligsf = 0;		/* flag "does this font have ligatures?" */
I 4
int	constant = 0;		/* flag constant width font (spacewidth, etc.)*/
E 4
E 2

				/* following are the character maps for */
				/* ascii code-conversion to printables... */
char	**charmap;
I 2
char	**synonyms;
int	numsyn;

E 2
char *vregular[] = {

D 2
	"", "fi", "fl", "ff", "\\-", "ru", "em", "bu", "sq", "Fi", "Fl", "de",
E 2
I 2
	"??", "fi", "fl", "ff", "\\-", "ru", "em", "bu", "sq", "Fi", "Fl", "de",
E 2
	"dg", "fm", "co", "rg", "ct", "14", "12", "34", "^T", "^U", "^V", "^W",
D 2
	"^X", "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_", " ", "!", "\"", "#",
E 2
I 2
	"^X", "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_", "", "!", "\"", "#",
E 2
	"$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1",
	"2", "3", "4", "5", "6", "7", "8", "9", ":", ";", "<", "=", ">", "?",
	"@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
	"\\", "]", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i",
	"j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
D 2
	"x", "y", "z", "{", "|", "}", "~"

E 2
I 2
	"x", "y", "z", "{", "|", "}", "~", "^?",
	(char *) 0
E 2
};
I 2
int nregular = 2;
char *sregular[SYNON] = {
	"-", "hy",	"_", "\\_"
};

E 2
char *vspecial[] = {

D 2
	"", "if", "ip", "pt", "rh", "cu", "rn", "bs", "+-", "<=", ">=", "sr",
E 2
I 2
	"??", "if", "ip", "pt", "rh", "cu", "rn", "bs", "+-", "<=", ">=", "sr",
E 2
	"ts", "is", "sl", "bv", "lf", "rf", "lc", "rc", "lt", "lb", "rt", "rb",
D 2
	"lk", "rk", "sb", "sp", "ca", "no", "lh", "mo", " ", "!", "\"", "#",
E 2
I 2
	"lk", "rk", "sb", "sp", "ca", "no", "lh", "mo", "", "!", "\"", "#",
E 2
	"$", "%", "&", "aa", "gr", ")", "mu", "pl", ",", "mi", ".", "di", "==",
	"~=", "ap", "!=", "<-", "->", "ua", "da", "sc", "**", ":", ";", "<",
	"eq", ">", "?", "@", "*A", "*B", "*G", "*D", "*E", "*Z", "*Y", "*H",
	"*I", "*K", "*L", "*M", "*N", "*C", "*O", "*P", "*R", "*S", "*T", "*U",
	"*F", "*X", "*Q", "*W", "dd", "br", "ib", "\\", "ci", "^", "ul", "ga",
	"*a", "*b", "*g", "*d", "*e", "*z", "*y", "*h", "*i", "*k", "*l", "*m",
	"*n", "*c", "*o", "*p", "*r", "*s", "*t", "*u", "es", "*x", "*q", "*w",
D 2
	"pd", "*f", "{", "|", "}", "~"
E 2
I 2
	"pd", "*f", "{", "|", "}", "~", "^?",
	(char *) 0
E 2
};
I 2
int nspecial = 0;
char *sspecial[SYNON] = {
	"",""
};
E 2

I 2
char *vtimes[] = {
E 2

I 2
	"??", "if", "ip", "pt", "rh", "cu", "rn", "bs", "+-", "<=", ">=", "mi",
	"**", "pl", "eq", "gr", "lt", "lk", "lb", "rt", "rk", "rb", "ap", "mo",
	"br", "rk", "sb", "sp", "ca", "no", "~=", "mo", "", "da", "no", "ua",
	"sc", "dd", "if", "pd", "sb", "sp", "mu", "+-", "ca", "cu", "<-", "di",
	"->",
	"!=", "sr", "<=", ">=", "==", "or", "is", "bv", "lc", "rc", "lf", "rf",
	"~=", "_", "ib", "ul", "rn", "ip", "*G", "*D", "*E", "*F", "*G", "*H",
	"*I", "??", "*L", "*L", "*N", "*C", "*O", "*P", "*H", "*S", "*S", "*U",
	"*U", "*X", "*W", "*C", "*Q", "br", "ib", "ga", "aa", "^", "ul", "ga",
	"*a", "*b", "*g", "*d", "*e", "*z", "*y", "*h", "*i", "*k", "*l", "*m",
	"*n", "*c", "*o", "*p", "*r", "*s", "*t", "*u", "es", "*x", "*q", "*w",
	"pd", "*f", "{", "|", "}", "~", "^?",
	(char *) 0
};
int ntimes = 0;
char *stimes[SYNON] = {
	"",""
};


char *vascii[] = {
D 4
	"bx", "da", "*a", "*b", "an", "no", "mo", "*p", "*l", "*g", "*d",
E 4
I 4
	"", "da", "*a", "*b", "an", "no", "mo", "*p", "*l", "*g", "*d",
E 4
	"ua", "+-", "O+", "if", "pd", "sb", "sp", "ca", "cu", "fa", "te",
	"OX", "<>", "<-", "->", "!=", "ap", "<=", ">=", "==", "or", "",
	"!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-",
	".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";",
	"<", "=", ">", "?",
	"@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
	"\\", "]", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i",
	"j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
D 4
	"x", "y", "z", "{", "|", "}", "~", "^?",
E 4
I 4
	"x", "y", "z", "{", "|", "}", "~", "??",
E 4
	(char *)0
};
int	nascii = 3;
char *sascii[SYNON] = {
	"-", "hy",	"-", "\\-",	"_", "\\_"
};


E 2
main (argc, argv)
int argc;
char **argv;
{
D 2
    register i, j;
E 2
I 2
    register int i;		/* two indexes */
    register int j;
    register char *ptr;		/* string traveler */
    register char delimit;	/* place for delimiters on command line */
I 4
    char *replacelist = NULL;	/* string of character name replacements */
    char *synonymlist = NULL;	/* string of synonym entries */
E 4
    char tostring();		/* function makes a string */
    char *nextstring();		/* moves to next string on list */
I 4
    char *operand();
E 4
E 2

I 2

    charmap = vregular;			/* default character map */
    synonyms = sregular;
    numsyn = nregular;
E 2
D 4
    while (*(*(++argv)) == '-') {		/* do options... */
	switch (*(++(*argv))) {
E 4
I 4
    while (--argc > 0 && *(*(++argv)) == '-') {		/* do options... */
	switch ((*argv)[1]) {
E 4

D 2
	  case 's': specialf = 1;		/* special font */
E 2
I 2
	  case 's': charmap = vspecial;		/* special font */
		    synonyms = sspecial;
		    numsyn = nspecial;
E 2
		    break;
D 2
	    
E 2
I 2

D 4
	  case 't': charmap = vtimes;		/* times special font */
E 4
I 4
	  case 'o': charmap = vtimes;		/* times special font */
E 4
		    synonyms = stimes;
		    numsyn = ntimes;
		    break;

	  case 'a': charmap = vascii;		/* ascii font */
		    synonyms = sascii;
		    numsyn = nascii;
		    break;

I 4
	  case 'c': constant = 1;		/* constant width font */
		    break;

E 4
	  case 'l': ligsf = 1;			/* ascii font */
		    break;

D 4
	  case 'n': fontname = ++*argv;		/* troff font name */
E 4
I 4
	  case 'n': fontname = operand(&argc, &argv);	/* troff font name */
E 4
		    break;

D 4
	  case 'x': ptr = ++*argv;		/* replacements */
		    while (delimit = tostring(ptr, ',')) {	/* get s1 */
			for (i = 0; charmap[i] != 0; i++) /* search for match */
			    if (strcmp (charmap[i], ptr) == 0)
				break;
			if (!charmap[i]) error ("-x option: no match");
			charmap[i] = ptr = nextstring(ptr);	/* replace s1 */
			delimit = tostring(ptr, ';');	/* with string s2 */
			if (delimit) ptr = nextstring(ptr);
		    }
E 4
I 4
	  case 'x': replacelist = operand(&argc, &argv);   /* replacements */
E 4
		    break;

D 4
	  case 'y': ptr = ++*argv;		/* synonyms */
		    while (delimit = tostring(ptr, ',')) {	/* get s1 */
			synonyms[2 * numsyn] = ptr;	/* set on end of list */
			ptr = nextstring(ptr);		/* get string s2 */
			delimit = tostring(ptr, ';');
			if (*ptr) {			/* if something there */
			    synonyms[2 * numsyn++ + 1] = ptr;  /* add to list */
			} else {			/* otherwise remove */
			    for (i = 0; i < numsyn; i++)	/* from list */
				if (strcmp (synonyms[2 * i], ptr) == 0)
				    *synonyms[2 * i] = '\0';
			}
			if (delimit) ptr = nextstring(ptr);
			if (numsyn > SYNON) error ("out of synonym space");
		    }
E 4
I 4
	  case 'y': synonymlist = operand(&argc, &argv);	/* synonyms */
E 4
		    break;

E 2
D 4
	  case 'd': fontdir = ++*argv;		/* directory */
E 4
I 4
	  case 'd': fontdir = operand(&argc, &argv);	/* directory */
E 4
		    break;

D 4
	  case 'p': pointsize = atoi(++*argv);	/* point size */
		    if (pointsize < MINSIZE || pointsize > MAXSIZE) {
			fprintf(stderr, "Illegal point size: %d\n", pointsize);
			exit(1);
		    }
E 4
I 4
	  case 'p': pointsize = atoi(operand(&argc, &argv));	/* point size */
		    if (pointsize < MINSIZE || pointsize > MAXSIZE)
			error("Illegal point size: %d", pointsize);
E 4
		    break;

I 2
D 4
	  case 'f': if ((factor = atoi(++*argv)) < 1 || factor > 1000) {
			fprintf(stderr, "Illegal factor: %d\n", factor);
			exit(1);
		    }
E 4
I 4
	  case 'f': factor = atoi(operand(&argc, &argv));    /*  % reduction */
		    if (factor < 1 || factor > 1000)
			error("Illegal factor: %d", factor);
E 4
		    break;

E 2
D 4
	  case 'r': res = atoi(++*argv);	/* resolution */
		    if (res < MINRES || res > MAXRES) {
			fprintf(stderr, "Illegal resolution: %d\n", res);
			exit(1);
		    }
E 4
I 4
	  case 'r': res = atoi(operand(&argc, &argv));	/* resolution */
		    if (res < MINRES || res > MAXRES)
			error("Illegal resolution: %d", res);
E 4
		    break;

D 4
	   default: fprintf(stderr, "Bad option: %c", **argv);
		    exit(1);
E 4
I 4
	   default: error("Bad option: %c", **argv);
E 4
	}
    }
I 4
				/* do character name replacements */
    if (replacelist != NULL) {
	ptr = replacelist;
	while (delimit = tostring(ptr, ',')) {		/* get s1 */
	    for (i = 0; charmap[i] != 0; i++)		/* search for match */
		if (strcmp (charmap[i], ptr) == 0)
		    break;
	    if (!charmap[i]) error("-x option: no match");
	    charmap[i] = ptr = nextstring(ptr);		/* replace s1 */
	    delimit = tostring(ptr, ':');		/* with string s2 */
	    if (delimit) ptr = nextstring(ptr);
	}
    }
				/* do the synonym list */
    if (synonymlist != NULL) {
	ptr = synonymlist;
	while (delimit = tostring(ptr, ',')) {	/* get s1 */
	    synonyms[2 * numsyn] = ptr;		/* set on end of list */
	    ptr = nextstring(ptr);		/* get string s2 */
	    delimit = tostring(ptr, ':');
	    if (*ptr) {				 /* if something there */
		synonyms[2 * numsyn++ + 1] = ptr;	/* add to list */
	    } else {				   /* otherwise remove */
		for (i = 0; i < numsyn; i++) {		  /* from list */
		    if (!strcmp(synonyms[2*i],synonyms[2*numsyn])) {
			numsyn--;
			for (j = i--; j < numsyn; j++) {
			    synonyms[2 * j] = synonyms[2 * (j+1)];
			    synonyms[2*j + 1] = synonyms[2*j + 3];
			}
		    }
		}
	    }
	    if (delimit) ptr = nextstring(ptr);
	    if (numsyn > SYNON) error("out of synonym space");
	}
    }
E 4
D 2
			/* set character map */
    charmap = specialf ? vspecial : vregular;
E 2

D 4
							/* open font file */
E 4
I 4
    if (argc != 1)					/* open font file */
	error("A vfont filename must be the last operand.");
E 4
D 7
    for (i = 0; FID < 0 && (psize = psizelist[i]) > 0; i++) {
	sprintf (IName, "%s/%s.%d", fontdir, *argv, psize);
E 7
I 7
    if (ptr = rindex(*argv, '.')) ptr++;
    if (ptr && *ptr <= '9' && *ptr >= '0') {
	psize = atoi(ptr);
	if (psize < MINSIZE || psize > MAXSIZE)
	    error("point size of file \"%s\" out of range", *argv);
	sprintf (IName, "%s/%s", fontdir, *argv);
E 7
	FID = open (IName, 0);
I 7
    } else {
	for (i = 0; FID < 0 && (psize = psizelist[i]) > 0; i++) {
	    sprintf (IName, "%s/%s.%d", fontdir, *argv, psize);
	    FID = open (IName, 0);
	}
E 7
    }
D 7
    if (FID < 0) { 
	printf ("Can't find %s\n", *argv);
	exit (8); 
    }
E 7
I 7
    if (FID < 0)
	error ("Can't open %s", *argv);
E 7

D 4

E 4
I 4
						/* read font width table */
E 4
    if (read (FID, &FontHeader, sizeof FontHeader) != sizeof FontHeader)
D 4
	error ("Bad header in Font file.");
E 4
I 4
	error("Bad header in Font file.");
E 4
    if (read (FID, &disptable[0], sizeof disptable) != sizeof disptable)
D 4
	error ("Bad dispatch table in Font file");
E 4
I 4
	error("Bad dispatch table in Font file");
E 4
    if (FontHeader.magic != MAGICN)
	printf ("Magic number %o wrong\n", FontHeader.magic);


    printf ("# Font %s, ", IName);			/* head off the file */
    printf ("max width %d, max height %d\n",
		FontHeader.maxx, FontHeader.maxy);
D 2
    printf ("name %s\ninternalname #\n", *argv);
    if (specialf) {
	printf ("special\n");
    } else {
E 2
I 2
    printf ("name %s\n", fontname);
    if (ligsf)
E 2
	printf ("ligatures ff fl fi ffl ffi 0\n");
D 2
    }
E 2
D 4
    printf ("# char	width	u/d	octal\ncharset\n");
    printf ("\\|	%4d	 0	0\n\\^	%4d	 0	0\n",
		(res * pointsize / APOINT + 4) / 6,
		(res * pointsize / APOINT + 7) / 12);
E 4

I 2
				/* pass 1 - set up maximums for ups and downs */
E 2
D 4
    for (j=0; j<256; j++) {
E 4
I 4
    for (j=0; j<256; j++) {	/* and find out constant width if requested */
E 4
	if (disptable[j].nbytes != 0) {
	    if (disptable[j].up > maxup) maxup = disptable[j].up;
	    if (disptable[j].down > maxdown) maxdown = disptable[j].down;
D 4
	}
E 4
I 4
	    if (constant && disptable[j].width) constant = disptable[j].width;
	} else			/* find a non-existant character to put \| in */
	    if (nullchar < 0) nullchar = j;
E 4
    }
    if (maxdown == 0) maxdown = 1;

I 4
    if (constant) {
	constant = (factor * (pointsize * constant + psize/2) / psize) / 100;
	printf ("spacewidth %d\n", constant);
    }
    printf ("# char	width	u/d	octal\ncharset\n");
    if (nullchar >= 0) {
	printf ("\\|	%4d	 0	0%o\n\\^	%4d	 0	0%o\n",
		constant ? constant : (res*pointsize / APOINT + 4)/6, nullchar,
		constant ? 0 : (res * pointsize / APOINT + 7) / 12, nullchar);
    }

E 4
/*******************************************************************************

	`type' is used to determine overhangs (up/down) from percentage of
	the maximum heights and dips.  Ascenders are higher than PCNTUP%
	of the highest, as descenders are more than PCNTDOWN%.
	widths [i = f(width)] are calculated from the definition point
	size (pointsize) and the one from this font (psize).

*******************************************************************************/

    for (j=0; j<256; j++) {
	if (disptable[j].nbytes != 0) {
	    type = (int) (((disptable[j].up * 100) / maxup) > PCNTUP) * 2 |
		    (int) (((disptable[j].down * 100) / maxdown) > PCNTDOWN);
D 2
	    i = ((pointsize * disptable[j].width) + psize / 2) / psize;
	    printf ("%s	%4d	 %d	0%o\n", charmap[j], i, type, j);
E 2
I 2
	    if (*(ptr = charmap[j])) {
		printf ("%s	%4d	 %d	0%o\n", ptr, (factor *
			(pointsize * disptable[j].width + psize/2) / psize)/100,
			type, j);
		for (i = 0; i < numsyn; i++)
		    if (strcmp (ptr, synonyms[2 * i]) == 0)
			printf ("%s	\"\n", synonyms[2 * i + 1]);
	    }
E 2
	}
D 5
    }
E 5
I 5
    } /* for j */
    exit(0);
E 5
}
I 2


/*----------------------------------------------------------------------------*
I 4
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
	    error("command-line option operand missing.");
	return(*(++(*argvp)));			/* operand next word */
}


/*----------------------------------------------------------------------------*
E 4
 | Routine:	char  tostring (pointer, delimitter)
 |
 | Results:	checks string pointed to by pointer and turns it into a
 |		string at 'delimitter' by replacing it with '\0'.  If the
 |		end of the string is found first, '\0' is returned; otherwise
 |		the delimitter found there is returned.
 |
 *----------------------------------------------------------------------------*/

char tostring(p, d)
register char *p;
register char d;
{
    while (*p && *p != d) p++;
    d = *p;
    *p = '\0';
    return d;
}


/*----------------------------------------------------------------------------*
 | Routine:	char  * nextstring (pointer)
 |
 | Results:	returns address of next string after one pointed to by
 |		pointer.  The next string is after the '\0' byte.
 |
 *----------------------------------------------------------------------------*/

char *nextstring(p)
register char *p;
{
    while (*(p++));
    return p;
}

E 2

D 4
error(string)
char *string;

E 4
I 4
error(s, a1, a2, a3, a4, a5)
char *s;
E 4
{ 
D 4
    printf("\nmakefont: %s\n",string);
E 4
I 4
    fprintf(stderr, "makefont: ");
    fprintf(stderr, s, a1, a2, a3, a4);
    fprintf(stderr, "\n");
E 4
    exit(8);
}
E 1
