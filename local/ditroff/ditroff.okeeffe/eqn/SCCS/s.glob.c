h04393
s 00004/00009/00039
d D 2.2 87/04/01 15:17:44 jaap 3 2
c Updates from bwk, see README for details
e
s 00033/00033/00015
d D 2.1 85/07/18 18:07:55 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00048/00000/00000
d D 1.1 85/03/01 15:26:53 jaap 1 0
c date and time created 85/03/01 15:26:53 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 2
static char *sccsid = "%M%	(CWI)	%I%	%E%";
#endif
E 2
I 2
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
E 2
#include "e.h"

D 2
int	dbg;	/* debugging print if non-zero */
int	lp[80];	/* stack for things like piles and matrices */
int	ct;	/* pointer to lp */
E 2
I 2
int	dbg;		/* debugging print if non-zero */
int	lp[200];		/* stack for things like piles and matrices */
int	ct;		/* pointer to lp */
E 2
int	used[100];	/* available registers */
D 2
int	ps;	/* default init point size */
E 2
I 2
int	ps;		/* default init point size */
E 2
int	deltaps	= 3;	/* default change in ps */
I 3
int	dps_set = 0;	/* 1 => -p option used */
E 3
int	gsize	= 10;	/* default initial point size */
D 2
int	gfont	= ITAL;	/* italic */
int	ft;	/* default font */
E 2
I 2
int	ft	= '2';
Font	ftstack[10] = { '2', "2" };	/* bottom is global font */
Font	*ftp	= ftstack;
int	szstack[10];	/* non-zero if absolute size set at this level */
int	nszstack = 0;
int	display	= 0;	/* 1=>display, 0=>.EQ/.EN */

E 2
#ifdef	APS
I 2
	char	*typesetter = "aps";	/* name for -T */
E 2
	int	ttype	= DEVAPS;	/* type of typesetter today */
D 2
	int	res	= 723;	/* resolution of typesetter; dflt = 202 */
	int	minsize	= 5;	/* min size it can handle; ditto */
#endif
#ifdef
		/*
		 * with just two possible typesetters, this would be the
		 * approach
		 */
	int	ttype	= DEV202;	/* type of typesetter today */
	int	res	= 972;	/* resolution of typesetter; dflt = 202 */
	int	minsize	= 6;	/* min size it can handle; ditto */
E 2
I 2
	int	res	= 723;		/* resolution of typesetter; dflt = 202 */
	int	minsize	= 5;		/* min size it can handle; ditto */
E 2
#else
I 2
	char	*typesetter = "har";
E 2
	int	ttype	= DEVHAR;	/* type of typesetter today */
D 2
	int	res	= 1445;	/* resolution of typesetter; dflt = har */
	int	minsize	= 4;	/* min size it can handle; ditto */
E 2
I 2
	int	res	= 1445;		/* resolution of typesetter; dflt = har */
	int	minsize	= 4;		/* min size it can handle; ditto */
E 2
#endif
D 2
FILE	*curfile;	/* current input file */
int	ifile;
int	linect;	/* line number in file */
int	eqline;	/* line where eqn started */
int	svargc;
char	**svargv;
int	eht[100];
int	ebase[100];
E 2
I 2
D 3
/*
 *	char	*typesetter = "202";
 *	int	ttype	= DEV202;	/* type of typesetter today
 *	int	res	= 972;		/* resolution of typesetter; dflt = 202
 *	int	minsize	= 5;		/* min size it can handle; ditto
*/
E 3

int	synerr;		/* 1 if syntax err in this eqn */
D 3
float	eht[100];
float	ebase[100];
int	eps[100];
E 3
I 3
float	eht[100];	/* height in ems at gsize */
float	ebase[100];	/* base: where one enters above bottom */
int	eps[100];	/* unused right now */
E 3
E 2
int	lfont[100];
int	rfont[100];
D 2
int	eqnreg;	/* register where final string appears */
int	eqnht;	/* inal height of equation */
E 2
I 2
int	eqnreg;		/* register where final string appears */
float	eqnht;		/* final height of equation */
E 2
int	lefteq	= '\0';	/* left in-line delimiter */
int	righteq	= '\0';	/* right in-line delimiter */
D 2
int	lastchar;	/* last character read by lex */
int	markline	= 0;	/* 1 if this EQ/EN contains mark; 2 if lineup */
E 2
I 2
int	markline = 0;	/* 1 if this EQ/EN contains mark; 2 if lineup */
E 2
E 1
