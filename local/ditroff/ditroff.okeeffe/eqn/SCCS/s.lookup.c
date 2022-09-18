h24550
s 00003/00001/00224
d D 2.2 87/04/01 15:17:55 jaap 3 2
c Updates from bwk, see README for details
e
s 00088/00085/00137
d D 2.1 85/07/18 18:08:31 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00222/00000/00000
d D 1.1 85/03/01 15:27:02 jaap 1 0
c date and time created 85/03/01 15:27:02 by jaap
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
# include "e.h"
D 3
#include "e.def"
E 3
I 3
#include "y.tab.h"
E 3

#define	TBLSIZE	100

tbl	*keytbl[TBLSIZE];	/* key words */
tbl	*restbl[TBLSIZE];	/* reserved words */
tbl	*deftbl[TBLSIZE];	/* user-defined names */

struct {
	char	*key;
	int	keyval;
} keyword[]	={
D 2
	"sub", 	SUB, 
	"sup", 	SUP, 
	".EN", 	EOF, 
E 2
I 2
	"sub", 		SUB, 
	"sup", 		SUP, 
	".EN", 		DOTEN,
	".EQ",		DOTEQ, 
E 2
	"from", 	FROM, 
D 2
	"to", 	TO, 
	"sum", 	SUM, 
	"hat", 	HAT, 
	"vec", VEC, 
	"dyad", DYAD, 
	"dot", 	DOT, 
E 2
I 2
	"to", 		TO, 
	"sum", 		SUM, 
	"hat", 		HAT, 
	"vec", 		VEC, 
	"dyad", 	DYAD, 
	"dot", 		DOT, 
E 2
	"dotdot", 	DOTDOT, 
D 2
	"bar", 	BAR, 
E 2
I 2
	"bar", 		BAR, 
I 3
	"lowbar",	LOWBAR,
	"highbar",	HIGHBAR,
E 3
E 2
	"tilde", 	TILDE, 
	"utilde", 	UTILDE, 
	"under", 	UNDER, 
	"prod", 	PROD, 
D 2
	"int", 	INT, 
E 2
I 2
	"int", 		INT, 
E 2
	"integral", 	INT, 
	"union", 	UNION, 
	"inter", 	INTER, 
D 2
	"pile", 	PILE, 
	"lpile", 	LPILE, 
	"cpile", 	CPILE, 
	"rpile", 	RPILE, 
E 2
I 2
	"matrix", 	MATRIX, 
	"col", 		COL, 
	"lcol", 	LCOL, 
	"ccol", 	CCOL, 
	"rcol", 	RCOL, 
	"pile", 	COL,	/* synonyms ... */ 
	"lpile", 	LCOL, 
	"cpile", 	CCOL, 
	"rpile", 	RCOL, 
E 2
	"over", 	OVER, 
	"sqrt", 	SQRT, 
	"above", 	ABOVE, 
	"size", 	SIZE, 
	"font", 	FONT, 
D 2
	"fat", FAT, 
E 2
I 2
	"fat", 		FAT, 
E 2
	"roman", 	ROMAN, 
	"italic", 	ITALIC, 
	"bold", 	BOLD, 
	"left", 	LEFT, 
	"right", 	RIGHT, 
	"delim", 	DELIM, 
	"define", 	DEFINE, 

#ifdef	NEQN	/* make ndefine synonym for define, tdefine a no-op */

	"tdefine",	TDEFINE,
	"ndefine",	DEFINE,

#else		/* tdefine = define, ndefine = no-op */

	"tdefine", 	DEFINE, 
	"ndefine", 	NDEFINE, 

#endif

I 2
	"ifdef",	IFDEF,
E 2
	"gsize", 	GSIZE, 
	".gsize", 	GSIZE, 
	"gfont", 	GFONT, 
	"include", 	INCLUDE, 
I 2
	"copy", 	INCLUDE, 
E 2
	"space",	SPACE,
D 2
	"up", 	UP, 
E 2
I 2
	"up", 		UP, 
E 2
	"down", 	DOWN, 
D 2
	"fwd", 	FWD, 
E 2
I 2
	"fwd", 		FWD, 
E 2
	"back", 	BACK, 
	"mark", 	MARK, 
	"lineup", 	LINEUP, 
D 2
	"matrix", 	MATRIX, 
	"col", 	COL, 
	"lcol", 	LCOL, 
	"ccol", 	CCOL, 
	"rcol", 	RCOL, 
E 2
	0, 	0
};

struct {
	char	*res;
	char	*resval;
} resword[]	={
D 2
	">=",	"\\(>=",
	"<=",	"\\(<=",
	"==",	"\\(==",
	"!=",	"\\(!=",
	"+-",	"\\(+-",
	"->",	"\\(->",
	"<-",	"\\(<-",
	"inf",	"\\(if",
E 2
I 2
	">=",		"\\(>=",
	"<=",		"\\(<=",
	"==",		"\\(==",
	"!=",		"\\(!=",
	"+-",		"\\(+-",
	"->",		"\\(->",
	"<-",		"\\(<-",
	"inf",		"\\(if",
E 2
	"infinity",	"\\(if",
	"partial",	"\\(pd",
D 2
	"half",	"\\f1\\(12\\fP",
E 2
I 2
	"half",		"\\f1\\(12\\fP",
E 2
	"prime",	"\\f1\\(fm\\fP",
	"dollar",	"\\f1$\\fP",
	"nothing",	"",
	"times",	"\\(mu",
D 2
	"del",	"\\(gr",
	"grad",	"\\(gr",
E 2
I 2
	"del",		"\\(gr",
	"grad",		"\\(gr",

E 2
#ifdef	NEQN
D 2
	"<<",	"<<",
	">>",	">>",
E 2
I 2
	"<<",		"<<",
	">>",		">>",
E 2
	"approx",	"~\b\\d~\\u",
D 2
	"cdot",	"\\v'-.5'.\\v'.5'",
	"...",	"...",
E 2
I 2
	"cdot",		"\\v'-.5'.\\v'.5'",
	"...",		"...",
E 2
	",...,",	",...,",
#else
D 2
	"<<",	"<\\h'-.3m'<",
	">>",	">\\h'-.3m'>",
E 2
I 2
	"<<",		"<\\h'-.3m'<",
	">>",		">\\h'-.3m'>",
E 2
	"approx",	"\\v'-.2m'\\z\\(ap\\v'.25m'\\(ap\\v'-.05m'",
D 2
	"cdot",	"\\v'-.3m'.\\v'.3m'",
	"...",	"\\v'-.3m'\\ .\\ .\\ .\\ \\v'.3m'",
	",...,",	",\\ .\\ .\\ .\\ ,\\|",
E 2
I 2
	"cdot",		"\\v'-.3m'.\\v'.3m'",
	"...",		"\\v'-.3m'\\ .\\ .\\ .\\ \\v'.3m'",
	",...,",	"\\f1,\\fP\\ .\\ .\\ .\\ \\f1,\\fP\\|",
E 2
#endif

	"alpha",	"\\(*a",
D 2
	"beta",	"\\(*b",
E 2
I 2
	"beta",		"\\(*b",
E 2
	"gamma",	"\\(*g",
	"GAMMA",	"\\(*G",
	"delta",	"\\(*d",
	"DELTA",	"\\(*D",
	"epsilon",	"\\(*e",
	"EPSILON",	"\\f1E\\fP",
	"omega",	"\\(*w",
	"OMEGA",	"\\(*W",
	"lambda",	"\\(*l",
	"LAMBDA",	"\\(*L",
D 2
	"mu",	"\\(*m",
	"nu",	"\\(*n",
E 2
I 2
	"mu",		"\\(*m",
	"nu",		"\\(*n",
E 2
	"theta",	"\\(*h",
	"THETA",	"\\(*H",
D 2
	"phi",	"\\(*f",
	"PHI",	"\\(*F",
	"pi",	"\\(*p",
	"PI",	"\\(*P",
E 2
I 2
	"phi",		"\\(*f",
	"PHI",		"\\(*F",
	"pi",		"\\(*p",
	"PI",		"\\(*P",
E 2
	"sigma",	"\\(*s",
	"SIGMA",	"\\(*S",
D 2
	"xi",	"\\(*c",
	"XI",	"\\(*C",
	"zeta",	"\\(*z",
	"iota",	"\\(*i",
	"eta",	"\\(*y",
E 2
I 2
	"xi",		"\\(*c",
	"XI",		"\\(*C",
	"zeta",		"\\(*z",
	"iota",		"\\(*i",
	"eta",		"\\(*y",
E 2
	"kappa",	"\\(*k",
D 2
	"rho",	"\\(*r",
	"tau",	"\\(*t",
E 2
I 2
	"rho",		"\\(*r",
	"tau",		"\\(*t",
E 2
	"omicron",	"\\(*o",
	"upsilon",	"\\(*u",
	"UPSILON",	"\\(*U",
D 2
	"psi",	"\\(*q",
	"PSI",	"\\(*Q",
	"chi",	"\\(*x",
	"and",	"\\f1and\\fP",
	"for",	"\\f1for\\fP",
	"if",	"\\f1if\\fP",
	"Re",	"\\f1Re\\fP",
	"Im",	"\\f1Im\\fP",
	"sin",	"\\f1sin\\fP",
	"cos",	"\\f1cos\\fP",
	"tan",	"\\f1tan\\fP",
	"arc",	"\\f1arc\\fP",
	"sinh",	"\\f1sinh\\fP",
	"coth",	"\\f1coth\\fP",
	"tanh",	"\\f1tanh\\fP",
	"cosh",	"\\f1cosh\\fP",
	"lim",	"\\f1lim\\fP",
	"log",	"\\f1log\\fP",
	"max",	"\\f1max\\fP",
	"min",	"\\f1min\\fP",
	"ln",	"\\f1ln\\fP",
	"exp",	"\\f1exp\\fP",
	"det",	"\\f1det\\fP",
E 2
I 2
	"psi",		"\\(*q",
	"PSI",		"\\(*Q",
	"chi",		"\\(*x",
	"and",		"\\f1and\\fP",
	"for",		"\\f1for\\fP",
	"if",		"\\f1if\\fP",
	"Re",		"\\f1Re\\fP",
	"Im",		"\\f1Im\\fP",
	"sin",		"\\f1sin\\fP",
	"cos",		"\\f1cos\\fP",
	"tan",		"\\f1tan\\fP",
	"arc",		"\\f1arc\\fP",
	"sinh",		"\\f1sinh\\fP",
	"coth",		"\\f1coth\\fP",
	"tanh",		"\\f1tanh\\fP",
	"cosh",		"\\f1cosh\\fP",
	"lim",		"\\f1lim\\fP",
	"log",		"\\f1log\\fP",
	"max",		"\\f1max\\fP",
	"min",		"\\f1min\\fP",
	"ln",		"\\f1ln\\fP",
	"exp",		"\\f1exp\\fP",
	"det",		"\\f1det\\fP",
E 2
	0,	0
};

tbl *lookup(tblp, name, defn)	/* find name in tbl. if defn non-null, install */
D 2
tbl **tblp;
char *name, *defn;
E 2
I 2
	tbl **tblp;
	char *name, *defn;
E 2
{
	register tbl *p;
	register int h;
	register char *s = name;
D 2
	char *malloc();
E 2

	for (h = 0; *s != '\0'; )
		h += *s++;
	h %= TBLSIZE;

	for (p = tblp[h]; p != NULL; p = p->next)
		if (strcmp(name, p->name) == 0) {	/* found it */
			if (defn != NULL)
				p->defn = defn;
			return(p);
		}
	/* didn't find it */
	if (defn == NULL)
		return(NULL);
	p = (tbl *) malloc(sizeof (tbl));
	if (p == NULL)
		error(FATAL, "out of space in lookup");
	p->name = name;
	p->defn = defn;
	p->next = tblp[h];
	tblp[h] = p;
	return(p);
}

init_tbl()	/* initialize all tables */
{
	int i;

	for (i = 0; keyword[i].key != NULL; i++)
		lookup(keytbl, keyword[i].key, keyword[i].keyval);
	for (i = 0; resword[i].res != NULL; i++)
		lookup(restbl, resword[i].res, resword[i].resval);
}
E 1
