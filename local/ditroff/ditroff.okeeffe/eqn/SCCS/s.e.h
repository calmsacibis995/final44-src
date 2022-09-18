h25978
s 00002/00002/00095
d D 2.3 87/04/01 15:17:30 jaap 5 4
c Updates from bwk, see README for details
e
s 00001/00000/00096
d D 2.2 86/04/09 22:25:57 jaap 4 3
c added PostScript resolution (DEVPSC)
e
s 00060/00022/00036
d D 2.1 85/07/18 18:07:07 jaap 3 2
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00001/00000/00057
d D 1.2 85/03/12 01:24:59 jaap 2 1
c eqn now knows about the versatec
e
s 00057/00000/00000
d D 1.1 85/03/01 15:26:38 jaap 1 0
c date and time created 85/03/01 15:26:38 by jaap
e
u
U
t
T
I 1
D 3
/*	%M%	(CWI)	%I%	%E%	*/
E 3
#include <stdio.h>

I 3
#define	dprintf		if (dbg) printf
#define	max(x,y)	(((x) >= (y)) ? (x) : (y))
E 3

#define	FATAL	1
#define	ROM	'1'
#define	ITAL	'2'
#define	BLD	'3'

D 3
#define	VERT(n)	((((n)+1)/3)*3)
#define	EFFPS(p)	((p) >= minsize ? (p) : minsize)
#define	POINT	72
#define	EM(m, ps)	(int)((((float)(m)*(ps) * res) / POINT))
E 3
I 3
#define	DEFGAP	-999	/* default gap in piles */
E 3

extern int	dbg;
extern int	ct;
extern int	lp[];
D 3
extern int	used[];	/* available registers */
extern int	ps;	/* dflt init pt size */
E 3
I 3
extern int	used[];		/* available registers */
extern int	ps;		/* dflt init pt size */
E 3
extern int	deltaps;	/* default change in ps */
I 5
extern int	dps_set;	/* 1 => -p option used */
E 5
D 3
extern int	gsize;	/* global size */
extern int	gfont;	/* global font */
extern int	ft;	/* dflt font */
E 3
I 3
extern int	gsize;		/* global size */
extern int	ft;		/* default font */
extern int	display;	/* 1 => inline, 0 => .EQ/.EN */
extern int	synerr;		/* 1 if syntax error in this eqn */
E 3

D 3
extern int	res;	/* resolution of output device */
E 3
I 3
extern char	*typesetter;	/* typesetter name for -T... */
D 5
extern int	res;		/* resolution of output device */
E 5
E 3
extern int	minsize;	/* min size it can print */
extern int	ttype;		/* actual type of typesetter: */
I 3

E 3
#define	DEVCAT	1
#define	DEV202	2
#define	DEVAPS	3
#define DEVHAR	4
I 2
#define DEVVER	5
I 4
#define DEVPSC	6
E 4
E 2

D 3
extern FILE	*curfile;	/* current input file */
extern int	ifile;	/* input file number */
extern int	linect;	/* line number in current file */
extern int	eqline;	/* line where eqn started */
extern int	svargc;
extern char	**svargv;
extern int	eht[];
extern int	ebase[];
E 3
I 3
extern float	eht[];
extern float	ebase[];
extern int	eps[];
E 3
extern int	lfont[];
extern int	rfont[];
extern int	yyval;
D 3
extern int	*yypv;
E 3
extern int	yylval;
D 3
extern int	eqnreg, eqnht;
E 3
I 3
extern int	eqnreg;
extern float	eqnht;
E 3
extern int	lefteq, righteq;
D 3
extern int	lastchar;	/* last character read by lex */
E 3
extern int	markline;	/* 1 if this EQ/EN contains mark or lineup */

typedef struct s_tbl {
	char	*name;
	char	*defn;
	struct s_tbl *next;
} tbl;

extern	char	*spaceval;	/* use in place of normal \x (for pic) */
I 3

#define	String	01
#define	Macro	02
#define	File	04
#define	Char	010
#define	Free	040

typedef struct infile {
	FILE	*fin;
	char	*fname;
	int	lineno;
} Infile;

typedef struct {	/* input source */
	int	type;	/* Macro, String, File */
	char	*sp;	/* if String or Macro */
} Src;

extern	Src	src[], *srcp;	/* input source stack */

#define	MAXARGS	20
typedef struct {	/* argument stack */
	char	*argstk[MAXARGS];	/* pointers to args */
	char	*argval;	/* points to space containing args */
} Arg;

typedef struct {	/* font number and name */
	int	ft;
	char	name[10];
} Font;

extern	Font	ftstack[];
extern	Font	*ftp;

extern	int	szstack[];
extern	int	nszstack;

extern	Infile	infile[10];
extern	Infile	*curfile;
extern	char	*grow(), *malloc(), *realloc(), *strsave();
D 5
extern	char	*DPS();
E 5
I 5
extern	char	*DPS(), *ABSPS();
E 5
extern	double	EM(), REL();
extern	tbl	*lookup(), *keytbl[], *deftbl[], *restbl[];
E 3
E 1
