h14686
s 00002/00002/00036
d D 1.6 85/11/11 13:54:40 slatteng 7 5
c restore size of fontname for compatibility with sys V (yick!)
e
s 00004/00004/00034
d R 1.6 85/06/07 00:26:53 sklower 6 5
c Match sys V rel 2 format since we got object DESC.out stuff from 
c xerox, which was computed according to that format.  No code was supplied, 
c instructions were sent as to wich struct elements to change.  We are still clean!
e
s 00002/00002/00036
d D 1.5 84/04/04 20:47:53 slatteng 5 4
c add stipple number instead of two spares
e
s 00001/00001/00037
d D 1.4 83/08/10 11:53:10 slatteng 4 3
c put fontname at 3 characters, since 2 is max in troff anyway
e
s 00002/00002/00036
d D 1.3 83/08/05 15:56:03 slatteng 3 2
c fix font name length to allow larger font names.
e
s 00001/00001/00037
d D 1.2 83/08/05 15:34:57 slatteng 2 1
c updated dev to be unsigned for filesize - adds needed bit to size
e
s 00038/00000/00000
d D 1.1 83/05/19 18:57:38 slatteng 1 0
c date and time created 83/05/19 18:57:38 by slatteng
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
      unsigned  short filesize;	/* number of bytes in file, */
E 2
				/* excluding dev part */
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
D 5
	short	spare1;		/* in case of expansion */
	short	spare2;
E 5
I 5
	short	nstips;		/* in case of expansion */
	short	spare1;
E 5
};

struct font {		/* characteristics of a font */
	char	nwfont;		/* number of width entries for this font */
	char	specfont;	/* 1 == special font */
	char	ligfont;	/* 1 == ligatures exist on this font */
	char	spare1;		/* unused for now */
D 3
	char	namefont[10];	/* name of this font (e.g., "R" */
	char	intname[10];	/* internal name (=number) on device, in ascii */
E 3
I 3
D 4
	char	namefont[12];	/* name of this font (e.g., "R" */
E 4
I 4
D 7
	char	namefont[3];	/* name of this font (e.g., "R" */
E 4
	char	intname[3];	/* internal name (=number) on device, in ascii */
E 7
I 7
	char	namefont[10];	/* name of this font (e.g., "R" */
	char	intname[10];	/* internal name (=number) on device, in ascii */
E 7
E 3
};

/* ligatures, ORed into ligfont */

#define	LFF	01
#define	LFI	02
#define	LFL	04
#define	LFFI	010
#define	LFFL	020
E 1
