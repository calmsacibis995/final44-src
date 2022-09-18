h11767
s 00001/00001/00073
d D 1.4 93/07/27 09:16:21 bostic 4 3
c checkpoint; Mike Karels left this checked out.
e
s 00001/00000/00073
d D 1.3 86/11/13 15:42:32 jaap 3 2
c Fixed lf again (Table too wide gave wrong name)
e
s 00002/00000/00071
d D 1.2 85/10/02 14:36:52 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00071/00000/00000
d D 1.1 85/10/01 18:08:54 jaap 1 0
c date and time created 85/10/01 18:08:54 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 4
static char sccsid[] = "%W% (CWI) %E%";
E 4
I 4
static char sccsid[] = "@(#)globals.c	1.3 (CWI) 86/11/13";
E 4
#endif lint


 /* t0.c: storage allocation */
#
#include "defs.h"
#include <stdio.h>

I 3
char oldname[BUFSIZ];	/* for .lf kludge */
E 3
int expflg = 0;
int ctrflg = 0;
int boxflg = 0;
int dboxflg = 0;
int tab = '\t';
int linsize;		/* Pointsize of lines to draw */
int delim1, delim2;	/* eqn delimiters (for n specification) */
int evenup[MAXCOL];	/* Equal width column */
int evenflg;
int F1 = 0;		/* First ``funny'' field delimiter */
int F2 = 0;		/* Second ``funny'' spanning indicator */
int allflg = 0;
int leftover = 0;
int textflg = 0;
int left1flg = 0;	/* Line left of first (output) column */
int rightl = 0;		/* Line right of last (output) column */
char *cstore, *cspace;
char *last;
struct colstr *table[MAXLIN];

/*
 * Next arrays describe the real table. Could be put in a structure in
 * future
 */
int style[MAXHEAD][MAXCOL];	/* Style of column (l, a, etc.) */
int ctop[MAXHEAD][MAXCOL];
char font[MAXHEAD][MAXCOL][2];	/* fontstyle of column */
char csize[MAXHEAD][MAXCOL][4];	/* pointsize of column */
char vsize[MAXHEAD][MAXCOL][4];	/* Vertical spacing (text blocks only */
int lefline[MAXHEAD][MAXCOL];	/* line left of specified columns */
char cll[MAXCOL][CLLEN];	/* minimum colwumn width wanted */
int sep[MAXCOL];		/* Separation between columns in n's */

int stynum[MAXLIN+1];
int nslin;
int nclin;			/* # of columns in specification part */
int fullbot[MAXLIN];
char *instead[MAXLIN];
int used[MAXCOL], lused[MAXCOL], rused[MAXCOL];
int linestop[MAXLIN];
int nlin;
int ncol;
int qcol;		/* quantity of output columns (bwk) */
int iline = 1;			/* input line counter */
char *ifile = "Input";		/* input file name */
/*
 * current name of the diversion for textblocks
 */
char texname = 'a';
int texct = 0;			/* index in texstr */
/*
 * possible names of diversions
 */
char texstr[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWYXZ0123456789";
int linstart;
char *exstore, *exlim;
FILE *tabin  /*= stdin */;
int pr1403;

I 2
int dbg;			/* debug flag */

E 2
/* Device dependencies */
int device = HARRIS;
E 1
