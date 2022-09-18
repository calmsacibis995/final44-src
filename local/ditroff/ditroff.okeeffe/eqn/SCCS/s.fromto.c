h49874
s 00031/00023/00025
d D 2.1 85/07/18 18:07:34 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00048/00000/00000
d D 1.1 85/03/01 15:26:45 jaap 1 0
c date and time created 85/03/01 15:26:45 by jaap
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

D 2
fromto(p1, p2, p3) int p1, p2, p3; {
	int b, h1, b1, pss;
	yyval = oalloc();
E 2
I 2
fromto(p1, p2, p3)
	int p1, p2, p3;
{
	float b, h1, b1, t;
	int subps;

	yyval = salloc();
E 2
	lfont[yyval] = rfont[yyval] = 0;
	h1 = eht[yyval] = eht[p1];
	b1 = ebase[p1];
	b = 0;
D 2
	pss = EFFPS(ps);
	ps += 3;
E 2
I 2
	subps = ps;
	ps += deltaps;
E 2
	nrwid(p1, ps, p1);
	printf(".nr %d \\n(%d\n", yyval, p1);
D 2
	if( p2>0 ) {
		nrwid(p2, pss, p2);
E 2
I 2
	if (p2 > 0) {
		nrwid(p2, subps, p2);
E 2
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, yyval, yyval, p2);
		eht[yyval] += eht[p2];
		b = eht[p2];
	}
D 2
	if( p3>0 ) {
		nrwid(p3, pss, p3);
E 2
I 2
	if (p3 > 0) {
		nrwid(p3, subps, p3);
E 2
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p3, yyval, yyval, p3);
		eht[yyval] += eht[p3];
	}
	printf(".ds %d ", yyval);	/* bottom of middle box */
D 2
	if( p2>0 ) {
		printf("\\v'%du'\\h'\\n(%du-\\n(%du/2u'\\s%d\\*(%d\\s%d", 
			eht[p2]-ebase[p2]+b1, yyval, p2, pss, p2, EFFPS(ps));
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			yyval, p2, -(eht[p2]-ebase[p2]+b1));
E 2
I 2
	if (p2 > 0) {
		t = eht[p2]-ebase[p2]+b1;
		printf("\\v'%gm'\\h'\\n(%du-\\n(%du/2u'%s\\*(%d%s", 
			REL(t,ps), yyval, p2, DPS(ps,subps), p2, DPS(subps,ps));
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%gm'\\\n", 
			yyval, p2, REL(-t,ps));
E 2
	}
	printf("\\h'\\n(%du-\\n(%du/2u'\\*(%d\\h'\\n(%du-\\n(%du/2u'\\\n", 
		yyval, p1, p1, yyval, p1);
D 2
	if( p3>0 ) {
		printf("\\v'%du'\\h'-\\n(%du-\\n(%du/2u'\\s%d\\*(%d\\s%d\\h'\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			-(h1-b1+ebase[p3]), yyval, p3, pss, p3, EFFPS(ps), yyval, p3, (h1-b1+ebase[p3]));
E 2
I 2
	if (p3  >0) {
		t = h1-b1+ebase[p3];
		printf("\\v'%gm'\\h'-\\n(%du-\\n(%du/2u'%s\\*(%d%s\\h'\\n(%du-\\n(%du/2u'\\v'%gm'\\\n", 
			REL(-t,ps), yyval, p3, DPS(ps,subps), p3, DPS(subps,ps), yyval, p3, REL(t,ps));
E 2
	}
	printf("\n");
	ebase[yyval] = b + b1;
D 2
	if(dbg)printf(".\tfrom to: S%d <- %d f %d t %d; h=%d b=%d\n", 
E 2
I 2
	dprintf(".\tS%d <- %d from %d to %d; h=%g b=%g\n", 
E 2
		yyval, p1, p2, p3, eht[yyval], ebase[yyval]);
D 2
	ofree(p1);
	if( p2>0 ) ofree(p2);
	if( p3>0 ) ofree(p3);
E 2
I 2
	sfree(p1);
	if (p2 > 0)
		sfree(p2);
	if (p3 > 0)
		sfree(p3);
E 2
}
E 1
