h51849
s 00002/00001/00051
d D 1.3 84/07/23 18:08:47 slatteng 4 2
c makd minimum granularity of vertical movement a parameter read for DESC file
e
s 00002/00001/00051
d R 1.3 84/07/23 18:02:25 slatteng 3 2
c made minimum granularity of vertical movement a parameter read from DESC file
e
s 00001/00004/00051
d D 1.2 83/08/15 16:28:03 slatteng 2 1
c removed all device-dependent code.  That means anything that was
c optimized for a particular typesetter is gone, and eqn now looks up the
c output device in a device file, like everybody else.
e
s 00055/00000/00000
d D 1.1 83/08/15 10:12:12 slatteng 1 0
c date and time created 83/08/15 10:12:12 by slatteng
e
u
U
t
T
I 1
#include <stdio.h>


#define	FATAL	1
#define	ROM	'1'
#define	ITAL	'2'
#define	BLD	'3'

D 4
#define	VERT(n)	((((n)+1)/3)*3)
E 4
I 4
#define	VERT(n)	((((n)+(minvert>>1))/minvert)*minvert)
E 4
#define	EFFPS(p)	((p) >= minsize ? (p) : minsize)
#define	POINT	72
#define	EM(m, ps)	(int)((((float)(m)*(ps) * res) / POINT))

extern int	dbg;
extern int	ct;
extern int	lp[];
extern int	used[];	/* available registers */
extern int	ps;	/* dflt init pt size */
extern int	deltaps;	/* default change in ps */
extern int	gsize;	/* global size */
extern int	gfont;	/* global font */
extern int	ft;	/* dflt font */

I 2
extern char	*device;	/* name of output device */
E 2
extern int	res;	/* resolution of output device */
extern int	minsize;	/* min size it can print */
I 4
extern int	minvert;	/* min size it can move vertically */
E 4
D 2
extern int	ttype;		/* actual type of typesetter: */
#define	DEVCAT	1
#define	DEV202	2
#define	DEVAPS	3
E 2

extern FILE	*curfile;	/* current input file */
extern int	ifile;	/* input file number */
extern int	linect;	/* line number in current file */
extern int	eqline;	/* line where eqn started */
extern int	svargc;
extern char	**svargv;
extern int	eht[];
extern int	ebase[];
extern int	lfont[];
extern int	rfont[];
extern int	yyval;
extern int	*yypv;
extern int	yylval;
extern int	eqnreg, eqnht;
extern int	lefteq, righteq;
extern int	lastchar;	/* last character read by lex */
extern int	markline;	/* 1 if this EQ/EN contains mark or lineup */

typedef struct s_tbl {
	char	*name;
	char	*defn;
	struct s_tbl *next;
} tbl;

extern	char	*spaceval;	/* use in place of normal \x (for pic) */
E 1
