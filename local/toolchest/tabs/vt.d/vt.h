/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *	Header file for the vt part of Tabs - originally based
 *	on Warren Montgomery's EMACS
 *
 */

#ifdef TERMCAP
#define puts putpad
#endif

#ifndef MXTRA
#define MXTRA 8
#endif

#define NSCRLIN 75			/* max screen lines */
#define NSCRCOL 132			/* max screen columns */

/* character type table */

#define PLAIN	0
#define CONTRL	1
#define TAB	2
#define BACKSP	3
#define UL	4

/* Video and plain parts - circa curses */
#define VT_VIDEO	0377600		/* A_ATTRIBUTES	from curses 	     */
#define VT_CHAR		0177
#define VT_AREA		040		/* turns on Area_Atrribute */
#define VT_UNDER	0000400		/* A_UNDERLINE from curses	     */
#define VT_BLINK	0002000		/* A_BLINK from curses		     */
#define VT_REVV		0001000		/* A_REVERSE from curses	     */
#define VT_HALF		0004000		/* A_DIM from curses		     */
#define VT_BOLD		0010000		/* A_BOLD from curses		     */
#define VT_INVISIBLE	0020000		/* A_INVISIBLE from curses	     */
#define VT_ALTCHAR	0100000		/* A_ALTCHARSET from curses	     */

/* Insert/delete parameters */

#define LNOMOD	0
#define LNOWID	0
#define ILOOK	5
#define DLOOK	5
#define lINSC	5
#define lDELC	5

/* Ioctl defines for cp_stty() */

#define STTYRAW		1
#define STTYNORM	0

/* character definitions */

#define CTL(x)		('x' & 037)
#define META		0200
#define MTA(mtach)	('mtach' | 0200)
#define ESC		033
#define VTNEWLINE	037
#define RUB		0177

#define EOL		'\n'

#define TTYLEN		512		/* total area for tty data strings */
#define CFILL		30
#define NBAUD		16		/* number of baud rates */
#define FNLEN		128		/* buffer size for getname */
#define EOM		'\337'		/* End of line marker - cflush */

extern char    *UP;			/* cursor up line */
extern char    *DOWN;
extern char    *BACK;
extern char    *FORWARD;
extern char    *HOME;
extern char    *CLEAR;
extern char    *CLREST;
extern char    *CLINE;
extern char    *BELL;
extern char    *CURAD;
extern char    *TMAP;
extern char    *SMAP;
extern char    *NOP;
extern char    *LOPEN;
extern char    *LDEL;
extern char    *INSERTC;
extern char    *INSERTM;
extern char    *OSERTC;
extern char    *INSERTP;
extern char    *DELC;
extern char    *SSCROLL;
extern char    *RSCROLL;
extern char    *CR;
extern char    *SCREG;
extern char    *ULINE;
extern char    *UEND;
extern int      EOVER;
extern int      TUNDER;			/* Transparent underline */
extern int      NESTANDOUT;
extern char    *SCINIT;
extern char    *VEXIT;
extern char    *RELDOWN;
extern char    *RELUP;
extern char    *RELFORW;
extern char    *RELBACK;
extern int      XBASE;
extern int      YBASE;
extern int      SCRWID;
extern int      SCRNLIN;
extern int      SCRWRAP;
extern int      VCOST;
extern int      SRCADD;
extern int      MI;
extern int      IN;
extern int      DELMODE;

extern char    *CLDEL;
extern char    *CLSCROLL;
extern char    *CLOPEN;

extern char    *KLEADIN;		/* Cursor Pad and Mouse Stuff */
#define	_NKEYS	27
extern char    *PAD_KEYS[_NKEYS];
#define	_Key(x)	PAD_KEYS[ x & 037 ]

/* Returns for cursor pad and mouse */
#define K_HOME		0200
#define K_UP		0201
#define K_DOWN		0202
#define K_RIGHT		0203
#define K_LEFT		0204
#define K_F0		0205
#define K_F1		0206
#define K_F2		0207
#define K_F3		0210
#define K_F4		0211
#define K_F5		0212
#define K_F6		0213
#define K_F7		0214
#define K_F8		0215
#define K_F9		0216
#define K_FA		0217
#define K_BOTTOM	0220
#define K_BTAB		0221
#define K_MOUSE		0222
#define K_MOUSE2	0223
#define K_FTAB		0224
#define K_TAB		0225
#define K_NULL		0226
#define K_ESC		0227
#define K_HELP		0230
#define K_EOL		0231
#define K_EOF		0232

extern char    *CWINDOW;		/* Create a window */

extern int      JQTYPE;			/* HACK for Blits */


/* DISPLAY MODE PARAMETERS */

extern int      WRAPON;			/* perform ! processing at EOL */


/* screen display data */

extern char     ttobuf[BUFSIZ];

extern char     ptype[];

extern int      mline;
extern int      mcol;
extern int      errno;


/* emacs display definitions */

extern char     osert;			/* flag indicating insert char mode */
extern int      acost;			/* cost of absolute positioning */
extern int      lUP;			/* cost of UP */
extern int      lDOWN;			/* cost of DOWN */
extern int      lBAK;			/* cost of BACK */
extern int      lFORWARD;		/* cost of FORWARD */
extern int      lCR;

extern int      scrlin;
extern int      scrcol;
extern int      ttywarp;		/* tty warp factor (stty speed) */


/* display data */

extern char     ttystrings[TTYLEN];

#ifndef VT_TERMINFO

struct sparm
{
	char   *t_pname;
	int    *t_padd;
};

extern struct sparm     ttydata[];

#endif VT_TERMINFO

extern int      TABSTOP;

#ifdef FAST_STRUCTS

typedef struct _atom
{
#ifdef u3b
unsigned        attribute:              9;
unsigned        letter:                 7;
#else
 /* Assume DEC products */
unsigned        letter:                 7;
unsigned        attribute:              9;
#endif
}  bits16;

#endif FAST_STRUCTS

#ifdef OLD_CHAR

typedef union
{
	short   short_int;
	char    parts[2];
#ifdef FAST_STRUCTS
	bits16 bits;
#endif FAST_STRUCTS
} CHAR;

#else /* New CHAR definition */

typedef unsigned short int	CHAR;

#endif OLD_CHAR


#define P_LETTER	0
#define P_ATTRIBUTE	1

extern  CHAR * cmap[NSCRLIN];
extern int      scrjnk[NSCRLIN];	/* column of last non-white char */

extern int      SREGION;
extern int      ttyerase;
extern int      ttykill;
extern int      ttyintr;		/* Rubout */
extern int      ttywarp;

extern int      UPLEFT;
extern int      UPRIGHT;
extern int      LORIGHT;
extern int      LOLEFT;
extern int      HORIX;
extern int      VERTX;

/* function definitions */

extern char    *cpy_ret ();
extern char    *nscan ();
