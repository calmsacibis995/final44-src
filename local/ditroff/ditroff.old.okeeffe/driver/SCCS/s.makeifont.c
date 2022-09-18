h48727
s 00005/00003/00511
d D 1.8 86/03/04 12:54:55 slatteng 10 8
c take out dependencies on default RESolution
e
s 00005/00003/00511
d R 1.8 86/03/04 12:15:14 slatteng 9 8
c take out dependencies on default resolution
e
s 00002/00000/00512
d D 1.7 85/02/26 14:16:06 slatteng 8 7
c added makefile-defnied bit directories
e
s 00005/00002/00507
d D 1.6 85/02/04 12:44:03 slatteng 7 6
c added sccs keywords and exit(0) at end
e
s 00095/00051/00414
d D 1.5 84/02/27 17:08:23 slatteng 6 4
c reorganized options, used "operand" routine, fixed synonym processing
c moved -x and -y options to work anywhere, added -c option.
e
s 00004/00004/00461
d R 1.5 84/02/20 15:47:03 slatteng 5 4
c change -m option to -o
e
s 00043/00047/00422
d D 1.4 83/10/22 15:24:46 slatteng 4 3
c change file input from id's to pointers;  update character mappings; errors...
e
s 00006/00006/00463
d D 1.3 83/09/23 14:21:54 slatteng 3 2
c fixed a few minor problems, cosmetics
e
s 00229/00083/00240
d D 1.2 83/09/14 17:20:40 slatteng 2 1
c put in synonym and replacement features.  Fix character maps.
c also added -l and -n options, fixed \^ and \| calculations.
e
s 00323/00000/00000
d D 1.1 83/08/17 14:38:04 slatteng 1 0
c date and time created 83/08/17 14:38:04 by slatteng
e
u
U
t
T
I 1
D 3
/* Font description file producer:  David Slattengren
E 3
I 3
D 7
/* Font description file producer for imagen fonts:  David Slattengren
E 7
I 7
/*	%M%	(Berkeley)	%I%	%E%
 *
 * Font description file producer for imagen fonts:  David Slattengren
E 7
E 3
 * Taken from vfontinfo by Andy Hertzfeld  4/79
 *
D 2
 *	Use:  mkfnt [-s] [-m] [-p#] [-r#] [-ddirectory] font
E 2
I 2
D 3
 *	Use:  mkfnt [ -nNAME ]  [ -smial ]  [ "-xs1,s2[;s1,s2...]" ]
E 3
I 3
D 6
 *	Use:  mifnt [ -nNAME ]  [ -smial ]  [ "-xs1,s2[;s1,s2...]" ]
E 6
I 6
 *  Use:  makeifont [ -nNAME ]  [ -i -s -a -o -l -c ]  [ "-xs1,s2[;s1,s2...]" ]
E 6
E 3
 *		[ "-ys1,s2[;s1,s2...]" ]  [ -p# ]  [ -r# ]  [ -ddir ]  font
E 2
 *
 *	Mkfnt takes the font named "font" and produces a ditroff description
D 2
 *	file from it.  The -s option tells mkfnt that this is a special font,
 *	and sould substitute special character names for the normal ones.  The
 *	-m option switches to the math font character map.  -m and -s together
 *	will get the math font at the moment.  The
 *	-p# option tells what point size the DESC file has as it's "unitwidth"
 *	argument (default: 36).  The -r# option is the resolution of the device
 *	(default: 240, in units/inch).  The -d option tells where to look for
 *	fonts (default: /usr/src/local/imagen/fonts/raster).
E 2
I 2
 *	file from it.  The -n option takes the 1 or 2 letter troff name to put
D 6
 *	the description (default = XX).  The -s, -m, -i, -a options select a
E 6
I 6
 *	the description (default = XX).  The -s, -o, -i, -a options select a
E 6
 *	different character mapping than for a "roman" font.  s = special;
D 6
 *	m = math;  i = italics;  a = ascii.  The -l option tells if the font
 *	has ligatures.
E 6
I 6
 *	o = math;  i = italics;  a = ascii.  The -l option tells if the font
 *	has ligatures.  The -c option tells makeifont that the font is a
 *	constant width one and sets parameters appropriately.
E 6
 *
 *	Both -x and -y options allow character name mapping.  A semi-colon
 *	separated list of comma-separated character-name pairs follows the
 *	x or y.  Notice that there are no spaces in the -x or -y command.  It
D 3
 *	is also IMPORTANT to enclose these arguments in double quotes to stop
E 3
I 3
 *	is also IMPORTANT to enclose these arguments in single quotes to stop
E 3
 *	the cshell from interpretting the contents.  A -x pair REPLACES the
 *	definition for s1 by s2.  A -y pair creates a synonym for s1 and calls
 *	it s2.  -x and -y MUST be sent after -s, -m, -i, or -a  if one of them
 *	is used.  Some synonyms are defaulted.  To remove a synonym or char-
 *	acter, leave out s2.
 *
 *	The -p# option tells what point size the DESC file has
D 3
 *	as it's "unitwidth" argument (default: 36).  The -r# option is the
E 3
I 3
 *	as it's "unitwidth" argument (default: 40).  The -r# option is the
E 3
 *	resolution of the device (default: 240, in units/inch).  The -d option
 *	tells where to find fonts (default: /usr/src/local/imagen/fonts/raster).
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
#include "rst.h"

char 	sccsid[] = "%W%	(Berkeley)	%G%";

#define PCNTUP		62	/* percent of maximum height for an ascender */
#define PCNTDOWN	73	/* percent of maximum droop for a descender */
I 8
#ifndef BITDIR
E 8
D 6
#define FONTDIR		"/usr/src/local/imagen/fonts/raster"
E 6
I 6
#define BITDIR		"/usr/src/local/imagen/fonts/raster"
I 8
#endif
E 8
E 6
#define POINTSIZE	40	/* this is the "unitwidth" point size */
#define MINSIZE		6	/* the minimum and maximum point size values */
#define MAXSIZE		36	/*    acceptible for use as "unitwidth"s */
#define MINRES		10	/* check up on resolution input by setting */
#define MAXRES		100000	/*    absurdly out-of-range limits on them */
I 2
#define MAXLAST		127	/* highest character code allowed */
#define SYNON		100	/* number of entries in a synonym table. */
				/*    equals twice the number of pairs. */
E 2


unsigned char *idstrings;	/* place for identifying strings */
unsigned char *endstring;	/* points to end of id strings */
double	fixtowdth;		/* "fix" and magnification conversion factor */
glyph_dir g[DIRSIZ];		/* directory of glyph definitions */
preamble p;			/* set of variables for preamble */

int	res = RES;		/* resolution of the device (units/inch) */
I 10
double	fixpix = FIXPIX;	/* conversion factor "fix"es to pixels */
E 10
int	pointsize = POINTSIZE;	/* point size being used for unitwidth */
int	psize;			/* point size of font actually used */
int	psizelist[] = { 40, 36, 28, 24, 22, 20, 18, 16,
			14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 0 };

I 2
char	*fontname = "XX";	/* troff name of font - set on command line */
E 2
D 6
char	*fontdir = FONTDIR;	/* place to look for fonts */
E 6
I 6
char	*fontdir = BITDIR;	/* place to look for fonts */
E 6
char	IName[100];		/* input file name put here */
char	*rdchar ();		/* function makes strings for ascii */
D 4
int	FID = -1;		/* input file number */
E 4
I 4
FILE *	FID = NULL;		/* input file number */
E 4

int	maxdown = 0;		/* size of the most "droopy" character */
int	maxup = 0;		/* size of the tallest character */
int	type;			/* 1, 2, or 3 for type of ascend/descending */
D 2
int	mathf = 0;		/* flag "is this a math font?"; */
int	specialf = 0;		/* flag "is this a special font?";  used to
				   determine which mapping array to look in. */
E 2
I 2
int	ligsf = 0;		/* flag "does this font have ligatures?" */
I 6
int	constant = 0;		/* flag constant width font (spacewidth, etc.)*/
E 6
E 2

				/* following are the character maps for */
				/* ascii code-conversion to printables... */
char	**charmap;
D 2
char *iregular[] = {
E 2
I 2
char	**synonyms;
int	numsyn;
E 2

I 2
char *iregular[] = {
E 2
	"*G", "*D", "*H", "*L", "*C", "*P", "*S", "*U", "*F", "*Q", "*W",
D 2
	"id", "ij", "ga", "aa", "^", "d^", "hc", "\\-", "..", "~", "->",
	"im", "de", "tc", "tl", "hs", "fe", "ae", "oe", "AE", "OE", "/o",
	"!", "\"", "fm", "ft", "%", "&", "'", "(", ")", "*", "+", ",", "-",
E 2
I 2
	"id", "ij", "ga", "aa", "^", "d^", "hc", "rn", "..", "~", "ve",
	"im", "de", "ce", "tl", "ar", "fb", "ae", "oe", "AE", "OE", "o/",
	"!", "\"", "fm", "ft", "%", "&", "'", "(", ")", "*", "+", ",", "hy",
E 2
	".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";",
	"<", "=", ">", "?",
D 2
	"/O", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
E 2
I 2
	"es", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
E 2
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
D 2
	"b\"", "]", "\\_", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h",
E 2
I 2
	"b\"", "]", "\\-", "em", "`", "a", "b", "c", "d", "e", "f", "g", "h",
E 2
	"i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
D 2
	"w", "x", "y", "z", "ff", "fi", "fl", "Fi", "Fl",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
E 2
I 2
	"w", "x", "y", "z", "ff", "fi", "fl", "Fi", "Fl"
E 2
};
I 2
int	nregular = 14;
char *sregular[SYNON] = {
	"A", "*A",	"B", "*B",	"E", "*E",	"H", "*Y",
	"I", "*I",	"K", "*K",	"M", "*M",	"N", "*N",
	"O", "*O",	"P", "*R",	"T", "*T",	"X", "*X",
	"Z", "*Z",	"hy", "-"
};
E 2

D 2
char *ispecial[] = {
E 2
I 2
char *iascii[] = {
	"m.", "da", "*a", "*b", "an", "no", "mo", "*p", "*l", "*g", "*d",
	"is", "+-", "O+", "if", "pd", "sb", "sp", "ca", "cu", "fa", "te",
	"OX", "<>", "<-", "->", "ap", "!=", "<=", ">=", "==", "or", "",
	"!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-",
	".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";",
	"<", "=", ">", "?",
	"@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
D 3
	"\\", "]", "^", "_", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i",
E 3
I 3
	"\\", "]", "^", "em", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i",
E 3
	"j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
	"x", "y", "z", "{", "|", "}", "~", "dm"
};
int	nascii = 2;
char *sascii[SYNON] = {
	"-", "hy",	"-", "\\-"
};
E 2

D 2
	"mi", "m.", "mu", "**", "\\", "de", "+-", "-+", "O+", "O-", "OX", "O/",
	"O.", "di", "ht", "bu", "ut", "==", "ib", "ip", "<=", ">=", "(=", ")=",
	"ap", "~~", "sb", "sp", "!=", "eq", "((", "))", "<-", "->", "ua", "da",
	"<>", "<<", ">>", "~=", "<_", "_>", "Ua", "Da", "><", "uL", "uR", "lR",
	"fm", "if", "mo", "!m", "0/", "ru", "al", ")(", "fa", "te", "no", "~N",
	"~R", "~T", "cr", "", "sl", "A", "B", "C", "D", "E", "F", "G", "H", "I",
E 2
I 2
char *ispecial[] = {
	"mi", "m.", "mu", "**", "\\", "ci", "+-", "-+", "O+", "O-", "OX", "O/",
	"O.", "di", "ht", "bu", "pe", "==", "ib", "ip", "<=", ">=", "(=", ")=",
	"ap", "pt", "sb", "sp", "!=", ".=", "((", "))", "<-", "->", "ua", "da",
	"<>", "<<", ">>", "~=", "lh", "rh", "Ua", "Da", "><", "uL", "uR", "lR",
	"fm", "if", "mo", "!m", "0/", "ul", "al", ")(", "fa", "te", "no", "?0",
	"?1", "?2", "cr", "", "/", "A", "B", "C", "D", "E", "F", "G", "H", "I",
E 2
	"J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W",
	"X", "Y", "Z", "cu", "ca", "c+", "an", "or", "|-", "-|", "lf", "rf",
D 4
	"lc", "rc", "{", "}", "<", ">", "bv", "||", "[[", "]]", "", "", "sr",
E 4
I 4
	"lc", "rc", "{", "}", "<", ">", "br", "||", "[[", "]]", "", "", "sr",
E 4
	"#", "gr", "is", "ux", "dx", "rx", "dm", "sc", "dg", "dd", "pp", "@",
D 2
	"co", "", "$",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
E 2
I 2
	"co", "", "$"
E 2
};
I 2
D 4
int	nspecial = 0;
E 4
I 4
int	nspecial = 2;
E 4
char *sspecial[SYNON] = {
D 4
	"",""
E 4
I 4
	"lh", "La",	"rh", "Ra"
E 4
};
E 2

char *imath[] = {
I 2
D 4
	"", "", "", "", "lf", "rf", "lc", "rc", "", "", "", "",
D 3
	"", "", "/", "", "", "", "", "", "", "", "",
E 3
I 3
	"", "", "", "", "", "", "", "", "", "", "",
E 4
I 4
	"Bl", "Br", "LT", "RT", "LB", "RB", "rt", "rk", "rb", "lt", "lk", "lb",
D 6
	"rc", "lc", "rf", "lf", "bv", "ci", "", "", "", "", "", "",
E 4
E 3
	"", "", "", "", "", "", "", "", "", "", "", "",
D 4
	"", "", "", "", "", "", "", "", "", "", "", "Bl", "Br",
	"", "", "", "", "", "", "", "", "lt", "rt", "lb", "rb",
	"lk", "rk", "", "", "", "", "", "", "", "", "", "", "", "", "",
E 4
	"", "", "", "", "", "", "", "", "", "", "", "",
D 4
	"", "", "", "", "", "", "", "", "", "", "", "", "",
	"LT", "RT", "LB", "RB", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "",
	"", "?0", "", "", "", "", "?1", "?2"
E 4
I 4
	"", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", ""
E 6
I 6
	"rc", "lc", "rf", "lf", "bv", "ci", "^R", "^S", "^T", "^U", "^V", "^W",
	"^X", "^Y", "^Z", "^[", "^\\", "^]", "^^", "^_",
	" ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-",
	".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";",
	"<", "=", ">", "?",
	"@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
	"\\", "]", "^", "em", "`", "a", "b", "c", "d", "e", "f", "g", "h", "i",
	"j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
	"x", "y", "z", "{", "|", "}", "~", "dm"
E 6
E 4
};
int	nmath = 0;
char *smath[SYNON] = {
	"",""
};
E 2

D 2
	"", "ct", "dd", "aa", "ga", "?1", "?2", "?3", "?4", "?5", "co", "rg",
	"tm", "?6", "pp", "fe", "ma", "bu", "bk", "bb", "ci", "sq", "#", "te",
	"rh", "lh", "*a", "*b", "*q", "*d", "*e", "*f", "*g", "*y", "*i", "*c",
	"*k", "*l", "*m", "*n", "*o", "*p", "*r", "*s", "*t", "*h", "*w", "*x",
	"*u", "*z", "*G", "*D", "*F", "*G", "*C", "*L", "*H", "*W", "pl", "mi",
	"mu", "eq", "di", "+-", "de", "fm", "*X", "es", "?7", "pt", "ts", "gr",
	"pd", ">", "<", ">=", "<=", "or", "sl", "\\\\", "ap", "~=", "~~", "==",
	"po", "**", "?8", "{", "}", "br", "sr", "is", "*S", "*P", "sb", "sp",
	"ca", "cu", "ib", "ip", "if", "?9", "ru", "?0", "??", "bs", "b4", "b9",
	"->", "<-", "ua", "da", "!=", "lf", "rf", "lc", "rc", "ul", "bv", "lt",
	"rt", "lb", "rb", "lk", "rk", "no", "fa", "ti",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""
E 2
I 2
char *iitalics[] = {
	"*G", "*D", "*H", "*L", "*C", "*P", "*S", "*U", "*F", "*Q", "*W",
	"*a", "*b", "*g", "*d", "*e", "*z", "*y", "*h", "*i", "*k", "*l",
	"*m", "*n", "*c", "*p", "*r", "*s", "*t", "*u", "*f", "*x", "id",
D 4
	"!", "\"", "el", "?0", "pd", "&", "'", "(", ")", "*", "+", ",", "hy",
E 4
I 4
	"!", "\"", "el", "Fi", "pd", "&", "'", "(", ")", "*", "+", ",", "hy",
E 4
	".", "/", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":", ";",
	"<", "=", ">", "?",
	"id", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[",
D 4
	"", "]", "", "", "`", "a", "b", "c", "d", "e", "f", "g", "h",
E 4
I 4
	"ff", "]", "fi", "fl", "`", "a", "b", "c", "d", "e", "f", "g", "h",
E 4
	"i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
D 4
	"w", "x", "y", "z", "*q", "*w", "?2", "?1", "w-"
E 4
I 4
	"w", "x", "y", "z", "*q", "*w", "?2", "?1", "Fl"
E 4
E 2
};
I 2
int	nitalics = 15;
char *sitalics[SYNON] = {
	"A", "*A",	"B", "*B",	"E", "*E",	"H", "*Y",
	"I", "*I",	"K", "*K",	"M", "*M",	"N", "*N",
	"O", "*O",	"P", "*R",	"T", "*T",	"X", "*X",
	"Z", "*Z",	"o", "*o",	"hy", "-"
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
    register char *ptr;		/* string traveller */
    register char delimit;	/* place for delemiters on command-line */
I 6
    char *replacelist = NULL;	/* list of character-name replacements */
    char *synonymlist = NULL;	/* list of synonym entries */
E 6
    char tostring();		/* function makes string */
    char *nextstring();		/* moves to next string on list */
I 6
    char *operand();		/* reads operands from commandline */
E 6
E 2

D 2
    while (*(*(++argv)) == '-') {		/* do options... */
E 2
I 2
    charmap = iregular;			/* default character map */
    synonyms = sregular;
    numsyn = nregular;
D 6
    while (*(*(++argv)) == '-') {	/* do options... */
E 2
	switch (*(++(*argv))) {
E 6
I 6
    while (--argc > 0 && *(*(++argv)) == '-') {	/* do options... */
	switch ((*argv)[1]) {
E 6

D 2
	  case 's': specialf = 1;		/* special font */
E 2
I 2
	  case 's': charmap = ispecial;		/* special font */
		    synonyms = sspecial;
		    numsyn = nspecial;
E 2
		    break;

D 2
	  case 'm': mathf = 1;			/* math font */
E 2
I 2
D 6
	  case 'm': charmap = imath;		/* math font */
E 6
I 6
	  case 'o': charmap = imath;		/* math font */
E 6
		    synonyms = smath;
		    numsyn = nmath;
E 2
		    break;

I 2
	  case 'i': charmap = iitalics;		/* italics font */
		    synonyms = sitalics;
		    numsyn = nitalics;
		    break;

	  case 'a': charmap = iascii;		/* ascii font */
		    synonyms = sascii;
		    numsyn = nascii;
		    break;

I 6
	  case 'c': constant = 1;		/* constant width font */
		    break;

E 6
	  case 'l': ligsf = 1;			/* ascii font */
		    break;

D 6
	  case 'n': fontname = ++*argv;		/* troff font name */
E 6
I 6
	  case 'n': fontname = operand(&argc, &argv);	/* troff font name */
E 6
		    break;

D 6
	  case 'x': ptr = ++*argv;		/* replacements */
		    while (delimit = tostring(ptr, ',')) {	/* get s1 */
			for (i = 0; i <= MAXLAST; i++)	/* search for match */
			    if (strcmp (charmap[i], ptr) == 0)
				break;
			if (i > MAXLAST) error ("-x option: no match");
			charmap[i] = ptr = nextstring(ptr);	/* replace s1 */
			delimit = tostring(ptr, ';');	/* with string s2 */
			if (delimit) ptr = nextstring(ptr);
		    }
E 6
I 6
	  case 'x': replacelist = operand(&argc, &argv);   /* replacements */
E 6
		    break;

D 6
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
E 6
I 6
	  case 'y': synonymlist = operand(&argc, &argv);	/* synonyms */
E 6
		    break;

E 2
D 6
	  case 'd': fontdir = ++*argv;		/* directory */
E 6
I 6
	  case 'd': fontdir = operand(&argc, &argv);		/* directory */
E 6
		    break;

D 6
	  case 'p': pointsize = atoi(++*argv);	/* point size */
E 6
I 6
	  case 'p': pointsize = atoi(operand(&argc, &argv));	/* point size */
E 6
D 4
		    if (pointsize < MINSIZE || pointsize > MAXSIZE) {
			fprintf(stderr, "Illegal point size: %d\n", pointsize);
			exit(1);
		    }
E 4
I 4
		    if (pointsize < MINSIZE || pointsize > MAXSIZE)
			error("illegal point size: %d", pointsize);
E 4
		    break;

D 6
	  case 'r': res = atoi(++*argv);	/* resolution */
E 6
I 6
	  case 'r': res = atoi(operand(&argc, &argv));	/* resolution */
E 6
D 4
		    if (res < MINRES || res > MAXRES) {
			fprintf(stderr, "Illegal resolution: %d\n", res);
			exit(1);
		    }
E 4
I 4
		    if (res < MINRES || res > MAXRES)
			error("illegal resolution: %d", res);
I 10
		    fixpix = (FIXIN * res);		/* pixels per fix */
E 10
E 4
		    break;

D 4
	   default: fprintf(stderr, "Bad option: %c", **argv);
		    exit(1);
E 4
I 4
	   default: error("bad option: %c", **argv);
E 4
	}
    }
D 2
			/* set character map */
    charmap = mathf ? imath : specialf ? ispecial : iregular;
E 2

D 6
							/* open font file */
E 6
I 6
    if (replacelist != NULL) {
	ptr = replacelist;
	while (delimit = tostring(ptr, ',')) {		/* get s1 */
	    for (i = 0; i <= MAXLAST; i++)		/* search for match */
		if (strcmp (charmap[i], ptr) == 0)
		    break;
	    if (i > MAXLAST) error("-x option: no match");
	    charmap[i] = ptr = nextstring(ptr);		/* replace s1 */
	    delimit = tostring(ptr, ':');		/* with string s2 */
	    if (delimit) ptr = nextstring(ptr);
	}
    }

    if (synonymlist != NULL) {
	ptr = synonymlist;
	while (delimit = tostring(ptr, ',')) {	/* get s1 */
	    synonyms[2 * numsyn] = ptr;		/* set on end of list */
	    ptr = nextstring(ptr);		/* get string s2 */
	    delimit = tostring(ptr, ':');
	    if (*ptr) {				/* if something there */
		synonyms[2 * numsyn++ + 1] = ptr;	/* add to list */
	    } else {				/* otherwise */
		for (i = 0; i < numsyn; i++) {		/* remove from list */
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

    if (argc != 1)					/* open font file */
	error("An RST font filename must be the last option");
E 6
D 4
    for (i = 0; FID < 0 && (psize = psizelist[i]) > 0; i++) {
E 4
I 4
    for (i = 0; FID == NULL && (psize = psizelist[i]) > 0; i++) {
E 4
	sprintf (IName, "%s/%s.r%d", fontdir, *argv, psize);
D 4
	FID = open (IName, 0);
E 4
I 4
	FID = fopen (IName, "r");
E 4
    }
D 4
    if (FID < 0) { 
D 2
	printf ("Can't find %s\n", *argv);
E 2
I 2
	fprintf (stderr, "Can't find %s\n", *argv);
E 2
	exit (8); 
    }
E 4
I 4
    if (FID == NULL)
	error("can't find %s", *argv);
E 4

D 4
    i = read(FID, &filemark[0], FMARK);
    if (strncmp(filemark, "Rast", 4) || i != FMARK)
	    error("Bad File Mark in Font file.");
E 4
I 4
    for (i = 0; i < FMARK; filemark[i++] = getc(FID));
    if (strncmp(filemark, "Rast", 4))
	    error("bad File Mark in Font file.");
E 4

    p.p_size = rd2();
    p.p_version = rd1();
    if (p.p_version)
D 2
	    error("Wrong version of Font file.");
E 2
I 2
D 4
	error("Wrong version of Font file.");
E 4
I 4
	error("wrong version of Font file.");
E 4
E 2
    p.p_glyph = rd3();
    p.p_first = rd2();
    p.p_last = rd2();
I 2
    if (p.p_last > MAXLAST) {
	fprintf(stderr, "truncating from %d to %d\n", p.p_last, MAXLAST);
	p.p_last = MAXLAST;
    }
E 2
    p.p_mag = rd4();
    p.p_desiz = rd4();
    p.p_linesp = rd4();
    p.p_wordsp = rd4();
    p.p_rot = rd2();
    p.p_cadv = rd1();
    p.p_ladv = rd1();
    p.p_id = rd4();
    p.p_res = rd2();
    if (p.p_res != res)
D 4
	    error("Wrong resolution in Font file.");
E 4
I 4
	    error("wrong resolution in Font file.");
E 4

    i = p.p_glyph - 44;
    idstrings = (unsigned char *) malloc (i);
    endstring = idstrings + i;
D 4
    if (read(FID, idstrings, i) != i)
	    error("Bad preamble in Font file.");
E 4
I 4
    while (i--) if (getc(FID) == EOF)
	    error("bad preamble in Font file.");
E 4

    for (i = p.p_first; i <= p.p_last; i++) {
	    g[i].g_height = rd2();
	    g[i].g_width = rd2();
	    g[i].g_up = rd2();
	    g[i].g_left = rd2();
	    g[i].g_pwidth = rd4();
	    g[i].g_bitp = rd3();
    }


D 10
    if ((fixtowdth = FIXPIX * p.p_mag / 1000.0) == 0.0)
	fixtowdth = FIXPIX;
E 10
I 10
    if ((fixtowdth = fixpix * p.p_mag / 1000.0) == 0.0)
	fixtowdth = fixpix;
E 10

D 2
    printf("# Font %s, size %.2f, ", IName, p.p_desiz * FIX);
E 2
I 2
    printf("# Font %s\n# size %.2f, ", IName, p.p_desiz * FIX);
E 2
    printf("first %d, last %d, res %d, ", p.p_first, p.p_last, p.p_res);
D 10
    printf("mag %.2f\n", fixtowdth / FIXPIX);
E 10
I 10
    printf("mag %.2f\n", fixtowdth / fixpix);
E 10

D 2
    printf("spacewidth %d\n", (int) (p.p_wordsp * fixtowdth));
    printf("name XX\ninternalname #\n");
    if (specialf || mathf) {
	printf ("special\n");
    } else {
E 2
I 2
    printf("name %s\n", fontname);
    if (ligsf)
E 2
	printf ("ligatures ff fl fi ffl ffi 0\n");
D 2
    }
E 2
I 2
    if ((i = (pointsize * p.p_wordsp * fixtowdth) / psize) > 127) i = 127;
    printf("spacewidth %d\n", i);
E 2
    printf ("# char	width	u/d	octal\ncharset\n");
D 2
    printf ("\\|	%4d	 0	0\n\\^	%4d	 0	0\n",
 		(int) (p.p_wordsp * fixtowdth) / 2,
 		(int) (p.p_wordsp * fixtowdth) / 4);
E 2
I 2
			/* the octal values for the following characters are */
D 6
			/* purposefully OUT of the range for characters (128) */
E 6
I 6
			/* purposefully OUT of the range of characters (128) */
E 6
D 4
    printf ("\\|	%4d	 0	0200\n\\^	%4d	 0	0200\n",
								i / 3, i / 6);
E 4
I 4
    printf ("\\|	%4d	 0	0%o\n\\^	%4d	 0	0%o\n",
D 6
						i / 3, DIRSIZ, i / 6, DIRSIZ);
E 6
I 6
		(constant ? i : i/3), DIRSIZ, (constant ? 0 : i/6), DIRSIZ);
E 6
E 4

E 2
    for (j = p.p_first; j <= p.p_last; j++) {
	if (g[j].g_bitp != 0) {
	    if (g[j].g_up > maxup) maxup = g[j].g_up;
	    if ((i = g[j].g_height - (g[j].g_up + 1)) > maxdown) maxdown = i;
	}
    }
    if (maxdown == 0) maxdown = 1;

/*******************************************************************************

	`type' is used to determine overhangs (up/down) from percentage of
	the maximum heights and dips.  Ascenders are higher than PCNTUP%
	of the highest, as descenders are more than PCNTDOWN%.
	widths [i = f(width)] are calculated from the definition point
	size (pointsize) and the one from this font (psize).

*******************************************************************************/

D 4
    for (j=0; j<256; j++) {
E 4
I 4
    for (j=0; j<DIRSIZ; j++) {
E 4
	if (g[j].g_bitp != 0) {
	    type = (int) (((g[j].g_up * 100) / maxup) > PCNTUP) * 2 | (int)
	    	((((g[j].g_height - (g[j].g_up+1)) * 100)/maxdown) > PCNTDOWN);
D 2
	    i = pointsize * g[j].g_pwidth * fixtowdth / psize;
	    printf ("%s	%4d	 %d	0%o\n", charmap[j], i, type, j);
E 2
I 2
	    if (*(ptr = charmap[j])) {
		printf ("%s	%4d	 %d	0%o\n", ptr, (int) (pointsize
			* g[j].g_pwidth * fixtowdth / psize), type, j);
		for (i = 0; i < numsyn; i++)
		    if (strcmp (ptr, synonyms[2 * i]) == 0)
			printf ("%s	\"\n", synonyms[2 * i + 1]);
	    }
E 2
	}
D 7
    }
E 7
I 7
    } /* for j */
    exit(0);
E 7
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
	if ((--*argcp) <= 0)			/* no operand */
	    error("command-line option operand missing.");
	return(*(++(*argvp)));			/* operand operand */
E 6
}

I 2

/*----------------------------------------------------------------------------*
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
E 4
I 4
/*VARARGS1*/
error(string, a1, a2, a3, a4)
E 4
char *string;
D 2

E 2
{ 
D 4
    printf("\nmakefont: %s\n",string);
E 4
I 4
    fprintf(stderr, "makefont: ");
    fprintf(stderr, string, a1, a2, a3, a4);
    fprintf(stderr, "\n");
E 4
    exit(8);
}

rd1()
{
D 4
    unsigned char i;
E 4
I 4
    int i;
E 4

D 4
    if(read (FID, &i, 1) != 1) error("File read error");
    return (int) i;
E 4
I 4
    if((i = getc(FID)) == EOF) error("file read error");
    return i;
E 4
}

rd2()
{
    register int i = rd1() << 8;

    return i + rd1();
}

rd3()
{
    register int i = rd2() << 8;

    return i + rd1();
}

rd4()
{
    register int i = rd2() << 16;

    return i + rd2();
}
E 1
