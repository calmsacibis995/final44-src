h58120
s 00012/00008/00024
d D 2.2 87/04/01 15:17:41 jaap 3 2
c Updates from bwk, see README for details
e
s 00011/00008/00021
d D 2.1 85/07/18 18:07:47 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00029/00000/00000
d D 1.1 85/03/01 15:26:47 jaap 1 0
c date and time created 85/03/01 15:26:47 by jaap
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
# include "e.def"
E 3
I 3
# include "y.tab.h"
E 3

I 3
extern int Funnyps;
extern float Funnyht, Funnybase;
extern char *Sum, *Union, *Inter, *Prod;

E 3
D 2
funny(n) int n; {
E 2
I 2
funny(n)
	int n;
{
E 2
	char *f;

D 2
	yyval = oalloc();
E 2
I 2
	yyval = salloc();
E 2
	switch(n) {
	case SUM:
D 3
		f = "\\(*S"; break;
E 3
I 3
		f = Sum; break;
E 3
	case UNION:
D 3
		f = "\\(cu"; break;
E 3
I 3
		f = Union; break;
E 3
	case INTER:	/* intersection */
D 3
		f = "\\(ca"; break;
E 3
I 3
		f = Inter; break;
E 3
	case PROD:
D 3
		f = "\\(*P"; break;
E 3
I 3
		f = Prod; break;
E 3
	default:
		error(FATAL, "funny type %d in funny", n);
	}
D 2
	printf(".ds %d \\s%d\\v'.3m'\\s+5%s\\s-5\\v'-.3m'\\s%d\n", yyval, ps, f, ps);
	eht[yyval] = VERT( EM(1.0, ps+5) - EM(0.2, ps) );
	ebase[yyval] = VERT( EM(0.3, ps) );
	if(dbg)printf(".\tfunny: S%d <- %s; h=%d b=%d\n", 
E 2
I 2
D 3
	printf(".ds %d \\v'.3m'\\s+5%s\\s-5\\v'-.3m'\n", yyval, f);
	eht[yyval] = EM(1.0, ps+5) - EM(0.2, ps);
	ebase[yyval] = EM(0.3, ps);
E 3
I 3
	printf(".ds %d %s\n", yyval, f);
	eht[yyval] = EM(1.0, ps+Funnyps) - EM(Funnyht, ps);
	ebase[yyval] = EM(Funnybase, ps);
E 3
	eps[yyval] = ps;
	dprintf(".\tS%d <- %s; h=%g b=%g\n", 
E 2
		yyval, f, eht[yyval], ebase[yyval]);
	lfont[yyval] = rfont[yyval] = ROM;
}
E 1
