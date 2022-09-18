h16138
s 00010/00006/00025
d D 2.2 87/04/01 15:17:47 jaap 3 2
c Updates from bwk, see README for details
e
s 00016/00018/00015
d D 2.1 85/07/18 18:08:04 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00033/00000/00000
d D 1.1 85/03/01 15:26:56 jaap 1 0
c date and time created 85/03/01 15:26:56 by jaap
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
# include "e.h"
# include "e.def"
E 2
I 2
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
#include "e.h"
D 3
#include "e.def"
E 3
I 3
#include "y.tab.h"
E 3
E 2

I 3
extern int Intps;
extern float Intht, Intbase, Int1h, Int1v, Int2h, Int2v;
extern char *Integral;

E 3
D 2
integral(p, p1, p2) {
E 2
I 2
integral(p, p1, p2)
{
E 2
	if (p1 != 0)
D 2
		printf(".ds %d \\h'-0.4m'\\v'0.4m'\\*(%d\\v'-0.4m'\n", p1, p1);
E 2
I 2
D 3
		printf(".ds %d \\h'-0.4m'\\v'0.2m'\\*(%d\\v'-0.2m'\n", p1, p1);
E 3
I 3
		printf(".ds %d \\h'%gm'\\v'%gm'\\*(%d\\v'%gm'\n", p1, -Int1h, Int1v, p1, -Int1v);
E 3
E 2
	if (p2 != 0)
D 2
		printf(".ds %d \\v'-0.3m'\\*(%d\\v'0.3m'\n", p2, p2);
E 2
I 2
D 3
		printf(".ds %d \\v'-0.1m'\\^\\*(%d\\v'0.1m'\n", p2, p2);
E 3
I 3
		printf(".ds %d \\v'%gm'\\h'%gm'\\*(%d\\v'%gm'\n", p2, -Int2v, Int2h, p2, Int2v);
E 3
E 2
	if (p1 != 0 && p2 != 0)
		shift2(p, p1, p2);
	else if (p1 != 0)
		bshiftb(p, SUB, p1);
	else if (p2 != 0)
		bshiftb(p, SUP, p2);
D 2
	if(dbg)printf(".\tintegral: S%d; h=%d b=%d\n", 
		p, eht[p], ebase[p]);
E 2
I 2
	dprintf(".\tintegral: S%d; h=%g b=%g\n", p, eht[p], ebase[p]);
E 2
	lfont[p] = ROM;
}

D 2
setintegral() {
	char *f;

	yyval = oalloc();
	f = "\\(is";
	printf(".ds %d \\s%d\\v'.1m'\\s+4%s\\s-4\\v'-.1m'\\s%d\n", 
		yyval, ps, f, ps);
	eht[yyval] = VERT( EM(1.15, ps+4) );
	ebase[yyval] = VERT( EM(0.3, ps) );
E 2
I 2
setintegral()
{
	yyval = salloc();
D 3
	printf(".ds %d \\v'.1m'\\s+4\\(is\\s-4\\v'-.1m'\n", yyval);
	eht[yyval] = EM(1.15, ps+4);
	ebase[yyval] = EM(0.3, ps);
E 3
I 3
	printf(".ds %d %s\n", yyval, Integral);
	eht[yyval] = EM(Intht, ps+Intps);
	ebase[yyval] = EM(Intbase, ps);
E 3
	eps[yyval] = ps;
E 2
	lfont[yyval] = rfont[yyval] = ROM;
}
E 1
