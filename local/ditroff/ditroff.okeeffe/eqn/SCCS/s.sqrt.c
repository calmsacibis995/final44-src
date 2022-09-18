h17649
s 00016/00014/00013
d D 2.1 85/07/18 18:10:23 jaap 3 2
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00003/00003/00024
d D 1.2 85/03/12 01:28:11 jaap 2 1
c Changed device dependent to better programming style
e
s 00027/00000/00000
d D 1.1 85/03/01 15:27:17 jaap 1 0
c date and time created 85/03/01 15:27:17 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 3
static char *sccsid = "%M%	(CWI)	%I%	%E%";
#endif
E 3
I 3
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
E 3
# include "e.h"

D 3
sqrt(p2) int p2; {
E 3
I 3
sqrt(p2)
	int p2;
{
E 3
	int nps;

D 3
	nps = EFFPS(((eht[p2]*9)/10+(res/POINT-1))/(res/POINT));
E 3
I 3
	nps = ps * 0.95 * eht[p2] / EM(1.0,ps) + 0.99;	/* kludgy */
	nps = max(EFFPS(nps), ps);
E 3
	yyval = p2;
D 2
	if (ttype == DEVCAT || ttype == DEVAPS || ttype == DEVHAR) /*jna trying*/
E 2
I 2
	if (ttype != DEV202)
E 2
D 3
		eht[yyval] = VERT( EM(1.2, nps) );
E 3
I 3
		eht[yyval] = EM(1.2, nps);
E 3
D 2
	else if (ttype == DEV202)
E 2
I 2
	else
E 2
D 3
		eht[yyval] = VERT( EM(1.0, nps) );
	if(dbg)printf(".\tsqrt: S%d <- S%d;b=%d, h=%d\n", 
		yyval, p2, ebase[yyval], eht[yyval]);
	if (rfont[yyval] == ITAL)
		printf(".as %d \\|\n", yyval);
E 3
I 3
		eht[yyval] = EM(1.1, nps);
	dprintf(".\tS%d <- sqrt S%d;b=%g, h=%g, nps=%d\n", 
		yyval, p2, ebase[yyval], eht[yyval], nps);
	printf(".as %d \\|\n", yyval);
E 3
	nrwid(p2, ps, p2);
D 3
	printf(".ds %d \\v'%du'\\s%d", yyval, ebase[p2], nps);	/* proper position for sqrt */
E 3
I 3
	printf(".ds %d \\v'%gm'%s", yyval, REL(ebase[p2],ps), DPS(ps,nps));	/* proper position for sqrt */
E 3
D 2
	if (ttype == DEVCAT || ttype == DEVAPS || ttype == DEVHAR) /*jna trying*/
E 2
I 2
	if (ttype != DEV202)
E 2
		printf("\\v'-.2m'\\(sr\\l'\\n(%du\\(rn'\\v'.2m'", p2);
	else
D 3
		printf("\\(sr\\l'\\n(%du\\(rn'", p2);	/* .95 best for 10; .9 best for 16 */
	printf("\\s%d\\v'%du'\\h'-\\n(%du'\\*(%d\n", ps, -ebase[p2], p2, p2);
	lfont[yyval] = ROM;
E 3
I 3
		printf("\\(sr\\l'\\n(%du\\(rn'", p2);
	printf("%s\\v'%gm'\\h'-\\n(%du'\\*(%d\n", DPS(nps,ps), REL(-ebase[p2],ps), p2, p2);
	lfont[yyval] = rfont[yyval] = ROM;
E 3
}
E 1
