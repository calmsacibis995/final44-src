h27267
s 00024/00024/00080
d D 2.2 87/04/01 15:18:25 jaap 3 2
c Updates from bwk, see README for details
e
s 00072/00074/00032
d D 2.1 85/07/18 18:10:02 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00106/00000/00000
d D 1.1 85/03/01 15:27:14 jaap 1 0
c date and time created 85/03/01 15:27:14 by jaap
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
E 2
I 2
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
#include "e.h"
E 2
D 3
#include "e.def"
E 3
I 3
#include "y.tab.h"
E 3

D 2
bshiftb(p1, dir, p2) int p1, dir, p2; {
	int shval, diffps, effps, effps2, d1, h1, b1, h2, b2;
E 2
I 2
subsup(p1, p2, p3)
	int p1, p2, p3;
{
	if (p2 != 0 && p3 != 0)
		shift2(p1, p2, p3);
	else if (p2 != 0)
		bshiftb(p1, SUB, p2);
	else if (p3 != 0)
		bshiftb(p1, SUP, p3);
}

I 3
extern float Subbase, Supshift;
extern char *Sub1space, *Sup1space, *Sub2space;
extern char *SS1space, *SS2space;

E 3
bshiftb(p1, dir, p2)
	int p1, dir, p2;
{
	int subps;
	float shval, d1, h1, b1, h2, b2;
E 2
	char *sh1, *sh2;

	yyval = p1;
	h1 = eht[p1];
	b1 = ebase[p1];
	h2 = eht[p2];
	b2 = ebase[p2];
D 2
	effps = EFFPS(ps);
	effps2 = EFFPS(ps+deltaps);
	diffps = deltaps;
E 2
I 2
	subps = ps;
	ps += deltaps;
E 2
	sh1 = sh2 = "";
D 2
	if( dir == SUB ) {
		/* top 1/2m above bottom of main box */
		d1 = VERT( EM(0.5, effps2) );
		shval = - d1 + h2 - b2;
		if( d1+b1 > h2 ) /* move little sub down */
			shval = b1-b2;
		ebase[yyval] = b1 + max(0, h2-b1-d1);
		eht[yyval] = h1 + max(0, h2-b1-d1);
E 2
I 2
	if (dir == SUB) {
		/* base .2m below bottom of main box */
D 3
		shval = b1 + EM(0.2, ps);
E 3
I 3
		shval = b1 + EM(Subbase, ps);
E 3
		ebase[yyval] = shval + b2;
		eht[yyval] = max(h1-b1+shval+b2, h2);
E 2
		if (rfont[p1] == ITAL && lfont[p2] == ROM)
D 3
			sh1 = "\\|";
E 3
I 3
			sh1 = Sub1space;
E 3
D 2
		if (rfont[p2] == ITAL)
			sh2 = "\\|";
E 2
	} else {	/* superscript */
		/* 4/10 up main box */
D 2
		d1 = VERT( EM(0.2, effps) );
E 2
I 2
D 3
		d1 = EM(0.2, subps);
E 3
I 3
		d1 = EM(Subbase, subps);
E 3
E 2
		ebase[yyval] = b1;
D 2
		shval = -VERT( (4 * (h1-b1)) / 10 ) - b2;
		if( VERT(4*(h1-b1)/10) + h2 < h1-b1 )	/* raise little super */
E 2
I 2
D 3
		shval = -(0.4 * (h1-b1)) - b2;
		if (0.4*(h1-b1) + h2 < h1-b1)	/* raise little super */
E 3
I 3
		shval = -(Supshift * (h1-b1)) - b2;
		if (Supshift*(h1-b1) + h2 < h1-b1)	/* raise little super */
E 3
E 2
			shval = -(h1-b1) + h2-b2 - d1;
D 2
		eht[yyval] = h1 + max(0, h2-VERT((6*(h1-b1))/10));
E 2
I 2
D 3
		eht[yyval] = h1 + max(0, h2 - 0.6*(h1-b1));
E 3
I 3
		eht[yyval] = h1 + max(0, h2 - (1-Supshift)*(h1-b1));
E 3
E 2
		if (rfont[p1] == ITAL)
D 3
			sh1 = "\\|";
E 3
I 3
			sh1 = Sup1space;
E 3
D 2
		if (rfont[p2] == ITAL)
			sh2 = "\\|";
E 2
	}
D 2
	if(dbg)printf(".\tb:b shift b: S%d <- S%d vert %d S%d vert %d; b=%d, h=%d\n", 
		yyval, p1, shval, p2, -shval, ebase[yyval], eht[yyval]);
	printf(".as %d \\v'%du'\\s-%d%s\\*(%d\\s+%d%s\\v'%du'\n", 
		yyval, shval, diffps, sh1, p2, diffps, sh2, -shval);
	ps += deltaps;
	if (rfont[p2] == ITAL)
		rfont[p1] = 0;
	else
		rfont[p1] = rfont[p2];
	ofree(p2);
E 2
I 2
	dprintf(".\tS%d <- %d shift %g %d; b=%g, h=%g, ps=%d, subps=%d\n", 
		yyval, p1, shval, p2, ebase[yyval], eht[yyval], ps, subps);
D 3
	sh2 = "\\^";
E 3
I 3
	sh2 = Sub2space;
E 3
	printf(".as %d \\v'%gm'%s%s\\*(%d%s%s\\v'%gm'\n", 
		yyval, REL(shval,ps), DPS(ps,subps), sh1, p2,
		DPS(subps,ps), sh2, REL(-shval,ps));
	rfont[p1] = 0;
	sfree(p2);
E 2
}

D 2
shift(p1) int p1; {
	ps -= deltaps;
	yyval = p1;
	if(dbg)printf(".\tshift: %d;ps=%d\n", yyval, ps);
}

shift2(p1, p2, p3) int p1, p2, p3; {
	int effps, effps2, h1, h2, h3, b1, b2, b3, subsh, d1, d2, supsh;
E 2
I 2
shift2(p1, p2, p3)
	int p1, p2, p3;
{
	int subps;
	float h1, h2, h3, b1, b2, b3, subsh, d1, d2, supsh;
E 2
	int treg;
D 2
	treg = oalloc();
E 2
I 2

	treg = salloc();
E 2
	yyval = p1;
D 2
	if(dbg)printf(".\tshift2 s%d <- %d %d %d\n", yyval, p1, p2, p3);
	effps = EFFPS(ps+deltaps);
	eht[p3] = h3 = VERT( (eht[p3] * effps) / EFFPS(ps) );
	ps += deltaps;
	effps2 = EFFPS(ps+deltaps);
E 2
I 2
	subps = ps;	/* sub and sup at this size */
	ps += deltaps;	/* outer size */
E 2
	h1 = eht[p1]; b1 = ebase[p1];
	h2 = eht[p2]; b2 = ebase[p2];
D 2
	b3 = ebase[p3];
	d1 = VERT( EM(0.5, effps2) );
	subsh = -d1+h2-b2;
	if( d1+b1 > h2 ) /* move little sub down */
		subsh = b1-b2;
	supsh = -VERT( (4*(h1-b1))/10 ) - b3;
	d2 = VERT( EM(0.2, effps) );
	if( VERT(4*(h1-b1)/10)+h3 < h1-b1 )
E 2
I 2
	h3 = eht[p3]; b3 = ebase[p3];
D 3
	subsh = EM(0.2, ps);
E 3
I 3
	subsh = EM(Subbase, ps);
E 3
	if (b1 > b2 + subsh) /* move little sub down */
		subsh += b1;
	eht[yyval] = max(subsh+b2-b1+h1, h2);
D 3
	supsh = -0.4*(h1-b1) - b3;
	d2 = EM(0.2, subps);
	if (h3 < 0.6*(h1-b1))
E 3
I 3
	supsh = -Supshift*(h1-b1) - b3;
	d2 = EM(Subbase, subps);
	if (h3 < (1-Supshift)*(h1-b1))
E 3
E 2
		supsh = -(h1-b1) + (h3-b3) - d2;
D 2
	eht[yyval] = h1 + max(0, h3-VERT( (6*(h1-b1))/10 )) + max(0, h2-b1-d1);
	ebase[yyval] = b1+max(0, h2-b1-d1);
	if (rfont[p1] == ITAL && lfont[p2] == ROM)
		printf(".ds %d \\|\\*(%d\n", p2, p2);
	if (rfont[p2] == ITAL)
		printf(".as %d \\|\n", p2);
	nrwid(p2, effps, p2);
	if (rfont[p1] == ITAL && lfont[p3] == ROM)
		printf(".ds %d \\|\\|\\*(%d\n", p3, p3);
	else
		printf(".ds %d \\|\\*(%d\n", p3, p3);
	nrwid(p3, effps, p3);
E 2
I 2
	ebase[yyval] = subsh + b2 - b1;
D 3
	eht[yyval] = h1 + subsh+b2-b1 + max(0, h3-0.6*(h1-b1));
E 3
I 3
	eht[yyval] = h1 + subsh+b2-b1 + max(0, h3-(1-Supshift)*(h1-b1));
E 3
	dprintf(".\tS%d <- %d sub %d sup %d, ps=%d, subps=%d, h=%g, b=%g\n",
		yyval, p1, p2, p3, ps, subps, eht[yyval], ebase[yyval]);
D 3
	/* if (rfont[p1] == ITAL && lfont[p2] == ROM) */
	/* if (lfont[p2] == ROM) */
		printf(".ds %d \\^\\*(%d\n", p2, p2);
	/* if (rfont[p2] == ITAL)
		printf(".as %d \\^\n", p2); */
E 3
I 3
	printf(".ds %d %s\\*(%d\n", p2, SS1space, p2);
E 3
	nrwid(p2, subps, p2);
D 3
	printf(".ds %d \\^\\*(%d\n", p3, p3);
E 3
I 3
	printf(".ds %d %s\\*(%d\n", p3, SS2space, p3);
E 3
	nrwid(p3, subps, p3);
E 2
	printf(".nr %d \\n(%d\n", treg, p3);
	printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, treg, treg, p2);
D 2
	printf(".as %d \\v'%du'\\s%d\\*(%d\\h'-\\n(%du'\\v'%du'\\\n", 
		p1, subsh, effps, p2, p2, -subsh+supsh);
	printf("\\s%d\\*(%d\\h'-\\n(%du+\\n(%du'\\s%d\\v'%du'\n", 
		effps, p3, p3, treg, effps2, -supsh);
	ps += deltaps;
E 2
I 2
D 3
	printf(".as %d \\v'%gm'%s\\*(%d\\h'-\\n(%du'\\v'%gm'\\\n", 
		p1, REL(subsh,ps), DPS(ps,subps), p2, p2, REL(-subsh+supsh,subps));
	printf("\\*(%d\\h'-\\n(%du+\\n(%du'%s\\v'%gm'\\^\n", 
		p3, p3, treg, DPS(subps,ps), REL(-supsh,ps));
E 3
I 3
	printf(".as %d %s\\v'%gm'\\*(%d\\v'%gm'\\h'-\\n(%du'\\\n", 
		p1, DPS(ps,subps), REL(subsh,subps), p2, REL(-subsh,subps), p2);
	printf("\\v'%gm'\\*(%d\\v'%gm'\\h'-\\n(%du+\\n(%du'%s%s\n", 
		REL(supsh,subps), p3, REL(-supsh,subps), p3, treg, DPS(subps,ps), Sub2space);
E 3
E 2
	if (rfont[p2] == ITAL)
		rfont[yyval] = 0;	/* lie */
D 2
	ofree(p2); ofree(p3); ofree(treg);
E 2
I 2
	sfree(p2); sfree(p3); sfree(treg);
E 2
}
E 1
