h12044
s 00001/00001/00052
d D 1.4 93/07/27 09:16:21 bostic 4 3
c checkpoint; Mike Karels left this checked out.
e
s 00001/00000/00052
d D 1.3 86/11/13 15:42:47 jaap 3 2
c Fixed lf again (Table too wide gave wrong name)
e
s 00001/00000/00051
d D 1.2 85/10/02 14:40:10 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00051/00000/00000
d D 1.1 85/10/01 18:09:37 jaap 1 0
c date and time created 85/10/01 18:09:37 by jaap
e
u
U
t
T
I 1
D 4
/*	%W% (CWI) %E%	*/
E 4
I 4
/*	@(#)ext.h	1.3 (CWI) 86/11/13	*/
E 4
/*	t..c	4.2	83/10/13	*/

/* t..c : external declarations */

#include <stdio.h>
#include <ctype.h>

extern int nlin, ncol, iline, nclin, nslin, qcol;

I 3
extern char oldname[];
E 3
extern int style[MAXHEAD][MAXCOL];
extern int ctop[MAXHEAD][MAXCOL];
extern char font[MAXHEAD][MAXCOL][2];
extern char csize[MAXHEAD][MAXCOL][4];
extern char vsize[MAXHEAD][MAXCOL][4];
extern char cll[MAXCOL][CLLEN];
extern int stynum[];
extern int F1, F2;
extern int lefline[MAXHEAD][MAXCOL];
extern int fullbot[];
extern char *instead[];
extern int expflg;
extern int ctrflg;
extern int evenflg;
extern int evenup[];
extern int boxflg;
extern int dboxflg;
extern int linsize;
extern int tab;
extern int pr1403;
extern int linsize, delim1, delim2;
extern int allflg;
extern int textflg;
extern int left1flg;
extern int rightl;
extern struct colstr *table[];
extern char *cspace, *cstore;
extern char *exstore, *exlim;
extern int sep[];
extern int used[], lused[], rused[];
extern int linestop[];
extern int leftover;
extern char *last, *ifile;
extern char texname;
extern int texct;
extern char texstr[];
extern int linstart;
extern FILE *tabin;
extern int pr1403;
I 2
extern int dbg;
E 2
extern char *reg();
extern device;
E 1
