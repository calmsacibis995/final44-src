h51784
s 00005/00001/00075
d D 4.5 91/04/18 18:17:29 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00000/00074
d D 4.4 88/07/22 16:35:30 bostic 4 3
c ANSIfication
e
s 00001/00000/00073
d D 4.3 85/09/14 16:25:14 bloom 3 2
c lint fixes
e
s 00001/00001/00072
d D 4.2 83/10/13 13:44:19 mosher 2 1
c MAXHEAD increased to 100 allow for really big tables - dm
e
s 00073/00000/00000
d D 4.1 83/02/12 19:06:13 shannon 1 0
c date and time created 83/02/12 19:06:13 by shannon
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */
E 5

/* t..c : external declarations */

# include "stdio.h"
# include "ctype.h"

# define MAXLIN 200
D 2
# define MAXHEAD 30
E 2
I 2
# define MAXHEAD 100
E 2
# define MAXCOL 20
# define MAXCHS 2000
# define MAXRPT 100
# define CLLEN 10
# define SHORTLINE 4
extern int nlin, ncol, iline, nclin, nslin;
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
struct colstr {char *col, *rcol;};
I 4
/* FIXME: kludge for seeing if somebody stuffed a char into col or rcol. */
# define tx(a) ((int)(a)>0 && (int)(a)<128)
E 4
extern struct colstr *table[];
extern char *cspace, *cstore;
I 3
extern char *chspace();
E 3
extern char *exstore, *exlim;
extern int sep[];
extern int used[], lused[], rused[];
extern int linestop[];
extern int leftover;
extern char *last, *ifile;
extern int texname;
extern int texct, texmax;
extern char texstr[];
extern int linstart;


extern FILE *tabin, *tabout;
# define CRIGHT 80
# define CLEFT 40
# define CMID 60
# define S1 31
# define S2 32
# define TMP 38
# define SF 35
# define SL 34
# define LSIZE 33
# define SIND 37
# define SVS 36
/* this refers to the relative position of lines */
# define LEFT 1
# define RIGHT 2
# define THRU 3
# define TOP 1
# define BOT 2
E 1
