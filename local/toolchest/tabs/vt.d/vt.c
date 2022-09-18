/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"

#ifndef VT_TERMINFO
#include <termio.h>
#endif VT_TERMINFO

#include <signal.h>

#ifdef TERMCAP
extern char    *UP;
#else
char   *UP;
#endif TERMCAP

char   *DOWN;
char   *BACK;
char   *FORWARD;
char   *HOME;
char   *CLEAR;
char   *CLREST;
char   *CLINE;
char   *BELL;
char   *CURAD;
char   *TMAP;
char   *SMAP;
char   *NOP;
char   *LOPEN;
char   *LDEL;
char   *INSERTC;
char   *INSERTM;
char   *OSERTC;
char   *INSERTP;
char   *DELC;
char   *SSCROLL;
char   *RSCROLL;
char   *CR;
char   *SCREG;
char   *ULINE;
char   *UEND;
int     EOVER;
int     TUNDER;				/* Transparent underline */
int     NESTANDOUT;
char   *SCINIT;
char   *VEXIT;
char   *RELDOWN;
char   *RELUP;
char   *RELFORW;
char   *RELBACK;
int     XBASE;
int     YBASE;
int     SCRWID;
int     SCRNLIN;
int     SCRWRAP;
int     VCOST;
int     SRCADD;
int     MI;
int     IN;
int     DELMODE;

char   *CLDEL;				/* Count line movement for Blit
					   Optimization */
char   *CLSCROLL;
char   *CLOPEN;

char   *KLEADIN;			/* Cursor Pad and Mouse Stuff */
char	*PAD_KEYS[_NKEYS];

char   *CWINDOW;			/* Create a window */

int     JQTYPE;				/* HACK for Blits */

/* DISPLAY MODE PARAMETERS */

int     WRAPON = 0;			/* perform ! processing at EOL */

/* screen display data */

char    ttobuf[BUFSIZ];

int     mline;
int     mcol;

extern int      errno;

/* emacs display definitions */

char    osert = 0;			/* flag indicating insert char mode */
int     acost;				/* cost of absolute positioning */
int     lUP;				/* cost of UP */
int     lDOWN;				/* cost of DOWN */
int     lBAK;				/* cost of BACK */
int     lFORWARD;			/* cost of FORWARD */
int     lCR;

int     scrlin;
int     scrcol;
int     ttywarp;			/* tty warp factor (stty speed) */

/* display data */

char    ttystrings[TTYLEN];

#ifndef VT_TERMINFO

struct sparm    ttydata[] =
{
	"up", (int *) & UP,
	"do", (int *) & DOWN,
	"bc", (int *) & BACK,
	"nd", (int *) & FORWARD,
	"ho", (int *) & HOME,
	"cl", (int *) & CLEAR,
	"cd", (int *) & CLREST,
	"ce", (int *) & CLINE,
	"bl", (int *) & BELL,
	"cm", (int *) & CURAD,
	"tm", (int *) & TMAP,
	"tM", (int *) & SMAP,
	"pc", (int *) & NOP,
	"al", (int *) & LOPEN,
	"dl", (int *) & LDEL,
	"ic", (int *) & INSERTC,
	"im", (int *) & INSERTM,
	"ei", (int *) & OSERTC,
	"ip", (int *) & INSERTP,
	"dc", (int *) & DELC,
	"sf", (int *) & SSCROLL,
	"sr", (int *) & RSCROLL,
	"cr", (int *) & CR,
	"cs", (int *) & SCREG,
	"ul", (int *) & ULINE,
	"ue", (int *) & UEND,
	"eo", (int *) & EOVER,
	"vs", (int *) & SCINIT,
	"ve", (int *) & VEXIT,
	"bx", (int *) & XBASE,
	"by", (int *) & YBASE,
	"co", (int *) & SCRWID,
	"li", (int *) & SCRNLIN,
	"am", (int *) & SCRWRAP,
	"vc", (int *) & VCOST,
	"rc", (int *) & SRCADD,
	"mi", (int *) & MI,
	"in", (int *) & IN,
	"dm", (int *) & DELMODE,

	"ru", (int *) & RELUP,
	"rd", (int *) & RELDOWN,
	"rl", (int *) & RELFORW,
	"rr", (int *) & RELBACK,

	"DL", (int *) & CLDEL,		/* Count line movement stuff */
	"SF", (int *) & CLSCROLL,
	"AL", (int *) & CLOPEN,

	"kh", (int *) & _Key(K_HOME),		/* Cursor Pad and Mouse Stuff */
	"kz", (int *) & _Key(K_BOTTOM),
	"ku", (int *) & _Key(K_UP),
	"kd", (int *) & _Key(K_DOWN),
	"kl", (int *) & _Key(K_LEFT),
	"kr", (int *) & _Key(K_RIGHT),
	"kB", (int *) & _Key(K_BTAB),		/* BACK TAB and Mouse */
	"km", (int *) & _Key(K_MOUSE),
	"kM", (int *) & _Key(K_MOUSE2),

	"CW", (int *) & CWINDOW,	/* Create a Window */

	"JQ", (int *) & JQTYPE,		/* HACK for Blits */
	0, 0,
};

#endif VT_TERMINFO

int     TABSTOP = 8;
CHAR * cmap[NSCRLIN];
int     scrjnk[NSCRLIN];		/* column of last non-white character 
					*/

int     SREGION = 24;
int     ttyerase = '#';
int     ttykill = '@';
int     ttyintr = 0177;			/* Rubout */

int     UPLEFT;
int     UPRIGHT;
int     LORIGHT;
int     LOLEFT;
int     HORIX;
int     VERTX;
