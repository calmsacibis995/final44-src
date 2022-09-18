h28670
s 00005/00005/00056
d D 2.4 90/11/03 20:41:42 karels 5 4
c changes to allow use of fonts > nfonts (caching font data for fonts
c nfonts+1...NFONTS; other minor cleanups
e
s 00002/00000/00059
d D 2.3 89/08/14 14:09:15 jaap 4 3
c checking stuff in, so charlie will stop sending me mail
e
s 00022/00022/00037
d D 2.2 88/03/04 16:11:41 jaap 3 2
c piring changes
e
s 00023/00004/00036
d D 2.1 85/07/18 14:30:26 jaap 2 1
c Edition 8 Version of troff (May 1985), (Dennis did the caching). 
c Local hacks from jaap.
e
s 00040/00000/00000
d D 1.1 85/07/17 17:55:05 jaap 1 0
c date and time created 85/07/17 17:55:05 by jaap
e
u
U
t
T
I 1
/*
	dev.h: characteristics of a typesetter
*/

struct dev {
D 2
	short	filesize;	/* number of bytes in file, */
E 2
I 2
	unsigned short	filesize;	/* number of bytes in file, */
E 2
				/* excluding dev part */
D 3
	short	res;		/* basic resolution in goobies/inch */
	short	hor;		/* goobies horizontally */
	short	vert;
	short	unitwidth;	/* size at which widths are given, in effect */
	short	nfonts;		/* number of fonts physically available */
	short	nsizes;		/* number of sizes it has */
	short	sizescale;	/* scaling for fractional point sizes */
	short	paperwidth;	/* max line length in units */
	short	paperlength;	/* max paper length in units */
	short	nchtab;		/* number of funny names in chtab */
	short	lchname;	/* length of chname table */
D 2
	short	spare1;		/* in case of expansion */
	short	spare2;
E 2
I 2
	short	spare1;		/* #chars in largest ever font */
	short	spare2;		/* in case of expansion */
E 3
I 3
	unsigned short	res;		/* basic resolution in goobies/inch */
	unsigned short	hor;		/* goobies horizontally */
	unsigned short	vert;
	unsigned short	unitwidth;	/* size at which widths are given, in effect */
	unsigned short	nfonts;		/* number of fonts physically available */
	unsigned short	nsizes;		/* number of sizes it has */
	unsigned short	sizescale;	/* scaling for fractional point sizes */
	unsigned short	paperwidth;	/* max line length in units */
	unsigned short	paperlength;	/* max paper length in units */
	unsigned short	nchtab;		/* number of funny names in chtab */
	unsigned short	lchname;	/* length of chname table */
D 5
	unsigned short	spare1;		/* #chars in largest ever font */
E 5
I 5
	unsigned short	nstip;		/* number of stipples */
E 5
	unsigned short	spare2;		/* in case of expansion */
E 3
E 2
};

D 2
struct font {		/* characteristics of a font */
E 2
I 2
struct Font {		/* characteristics of a font */
E 2
D 3
	char	nwfont;		/* number of width entries for this font */
	char	specfont;	/* 1 == special font */
	char	ligfont;	/* 1 == ligatures exist on this font */
	char	spare1;		/* unused for now */
	char	fonttab;	/* 1 == use extra table for fontnumbers */
	char	slant;		/* if set, slant font by slant degrees */
	char	namefont[10];	/* name of this font (e.g., "R" */
	char	intname[10];	/* internal name (=number) on device, in ascii */
E 3
I 3
	unsigned char	nwfont;		/* number of width entries for this font */
	unsigned char	specfont;	/* 1 == special font */
D 5
	unsigned char	ligfont;	/* 1 == ligatures exist on this font */
E 5
I 5
	unsigned char	ligfont;	/* mask of ligatures on this font */
E 5
	unsigned char	spare1;		/* unused for now */
I 4
D 5
#ifdef 0
E 5
I 5
#ifdef CWI
E 5
E 4
	unsigned char	fonttab;	/* 1 == use extra table for fontnumbers */
	unsigned char	slant;		/* if set, slant font by slant degrees */
I 4
#endif
E 4
	unsigned char	namefont[10];	/* name of this font (e.g., "R" */
	unsigned char	intname[10];	/* internal name (=number) on device, in ascii */
E 3
};

/* ligatures, ORed into ligfont */

#define	LFF	01
#define	LFI	02
#define	LFL	04
#define	LFFI	010
#define	LFFL	020
I 2

I 5
#ifdef CWI
E 5
/*
 * Notes by jaap:
 *
D 5
 * spare1 int struct dev is also known as biggestfont
 *
E 5
D 3
 * in Font struvture is added:
E 3
I 3
 * in Font structure is added:
E 3
 *	fonttab: if set to 1, the Font.out has an extra
 *		  table of shorts which gives the physical font
 *		  on which the chracter lives. Allows mapping of
 *		  "logial fonts" into variuos physical fonts on the
 *		  device. Needed since the Harris f.i. has a weird font
 *		  lay-out. Also makes fonts consisting of weird
 *		  character combinations easier.
 *	slant:	The font can must be slanted to force italics (function
 *		of back-end, necessary for f.i. the Harris, which
 *		doesn't has italics for the sans-serif fonts; these
 *		italics have to be made by slanting)
 */
I 5
#endif
E 5
E 2
E 1
