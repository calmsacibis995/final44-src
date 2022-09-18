h57567
s 00013/00009/00026
d D 2.2 87/04/01 15:18:12 jaap 3 2
c Updates from bwk, see README for details
e
s 00019/00016/00016
d D 2.1 85/07/18 18:09:19 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00032/00000/00000
d D 1.1 85/03/01 15:27:10 jaap 1 0
c date and time created 85/03/01 15:27:10 by jaap
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
boverb(p1, p2) int p1, p2; {
	int h, b, treg, d;
E 2
I 2
boverb(p1, p2)
	int p1, p2;
{
	int treg;
D 3
	float h, b, d;
E 3
I 3
	float h, b, d, d1, d2, d3;
	extern float Overgap, Overwid, Overline;
E 3
E 2

D 2
	treg = oalloc();
E 2
I 2
	treg = salloc();
E 2
	yyval = p1;
D 2
	d = VERT( EM(0.3, ps) );
E 2
I 2
D 3
	d = EM(0.3, ps);
E 3
I 3
	d = EM(Overgap, ps);
E 3
E 2
	h = eht[p1] + eht[p2] + d;
	b = eht[p2] - d;
D 2
	if(dbg)printf(".\tb:bob: S%d <- S%d over S%d; b=%d, h=%d\n", 
E 2
I 2
	dprintf(".\tS%d <- %d over %d; b=%g, h=%g\n", 
E 2
		yyval, p1, p2, b, h);
	nrwid(p1, ps, p1);
	nrwid(p2, ps, p2);
	printf(".nr %d \\n(%d\n", treg, p1);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
D 2
	printf(".nr %d \\n(%d+\\s%d.5m\\s0\n", treg, treg, EFFPS(ps));
	printf(".ds %d \\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d\\\n", 
		yyval, eht[p2]-ebase[p2]-d, treg, p2, p2);
	printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\*(%d\\\n", 
		p2, p1, -(eht[p2]-ebase[p2]+d+ebase[p1]), p1);
	printf("\\h'-\\n(%du-\\n(%du/2u+.1m'\\v'%du'\\l'\\n(%du-.2m'\\h'.1m'\\v'%du'\n", 
		 treg, p1, ebase[p1]+d, treg, d);
E 2
I 2
D 3
	printf(".nr %d \\n(%d+.5m\n", treg, treg);
	printf(".ds %d \\v'%gm'\\h'\\n(%du-\\n(%du/2u'\\*(%d\\\n", 
		yyval, REL(eht[p2]-ebase[p2]-d,ps), treg, p2, p2);
	printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%gm'\\*(%d\\\n", 
		p2, p1, REL(-(eht[p2]-ebase[p2]+d+ebase[p1]),ps), p1);
	printf("\\h'-\\n(%du-\\n(%du/2u+.1m'\\v'%gm'\\l'\\n(%du-.2m'\\h'.1m'\\v'%gm'\n", 
		 treg, p1, REL(ebase[p1]+d,ps), treg, REL(d,ps));
E 3
I 3
	printf(".nr %d \\n(%d+%gm\n", treg, treg, Overwid);
	d2 = eht[p2]-ebase[p2]-d;	/* denom */
	printf(".ds %d \\v'%gm'\\h'\\n(%du-\\n(%du/2u'\\*(%d\\v'%gm'\\\n", 
		yyval, REL(d2,ps), treg, p2, p2, REL(-d2,ps));
	d1 = 2 * d + ebase[p1];		/* num */
	printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%gm'\\*(%d\\v'%gm'\\\n", 
		p2, p1, REL(-d1,ps), p1, REL(d1,ps));
	printf("\\h'-\\n(%du-\\n(%du/2u+%gm'\\v'%gm'\\l'\\n(%du-%gm'\\h'%gm'\\v'%gm'\n", 
		treg, p1, Overline, REL(-d,ps),
		treg, 2*Overline, Overline, REL(d,ps));
E 3
E 2
	ebase[yyval] = b;
	eht[yyval] = h;
	lfont[yyval] = rfont[yyval] = 0;
D 2
	ofree(p2);
	ofree(treg);
E 2
I 2
	sfree(p2);
	sfree(treg);
E 2
}
E 1
