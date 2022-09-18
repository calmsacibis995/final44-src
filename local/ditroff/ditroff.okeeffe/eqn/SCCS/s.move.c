h28882
s 00001/00001/00022
d D 2.2 87/04/01 15:18:08 jaap 3 2
c Updates from bwk, see README for details
e
s 00012/00010/00011
d D 2.1 85/07/18 18:09:10 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00021/00000/00000
d D 1.1 85/03/01 15:27:07 jaap 1 0
c date and time created 85/03/01 15:27:07 by jaap
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

D 2
move(dir, amt, p) int dir, amt, p; {
	int a;
E 2
I 2
move(dir, amt, p)
	int dir, amt, p;
{
	float a;
E 2

	yyval = p;
D 2
	a = VERT( EM(amt/100.0, EFFPS(ps)) );
E 2
I 2
	a = EM(amt/100.0, ps);
E 2
	printf(".ds %d ", yyval);
D 2
	if( dir == FWD || dir == BACK )	/* fwd, back */
		printf("\\h'%s%du'\\*(%d\n", (dir==BACK) ? "-" : "", a, p);
E 2
I 2
	if (dir == FWD || dir == BACK)
		printf("\\h'%s%gm'\\*(%d\n", (dir==BACK) ? "-" : "", a, p);
E 2
	else if (dir == UP)
D 2
		printf("\\v'-%du'\\*(%d\\v'%du'\n", a, p, a);
E 2
I 2
		printf("\\v'-%gm'\\*(%d\\v'%gm'\n", a, p, a);
E 2
	else if (dir == DOWN)
D 2
		printf("\\v'%du'\\*(%d\\v'-%du'\n", a, p, a);
	if(dbg)printf(".\tmove %d dir %d amt %d; h=%d b=%d\n", 
E 2
I 2
		printf("\\v'%gm'\\*(%d\\v'-%gm'\n", a, p, a);
	dprintf(".\tmove %d dir %d amt %g; h=%g b=%g\n", 
E 2
		p, dir, a, eht[yyval], ebase[yyval]);
}
E 1
