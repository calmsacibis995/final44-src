h58107
s 00025/00023/00055
d D 2.2 87/04/01 15:18:21 jaap 3 2
c Updates from bwk, see README for details
e
s 00051/00038/00027
d D 2.1 85/07/18 18:09:45 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00065/00000/00000
d D 1.1 85/03/01 15:27:13 jaap 1 0
c date and time created 85/03/01 15:27:13 by jaap
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
D 3
#include "e.def"
E 3
I 3
#include "y.tab.h"
E 3
E 2

D 2
lpile(type, p1, p2) int type, p1, p2; {
	int bi, hi, i, gap, h, b, nlist, nlist2, mid;
	yyval = oalloc();
	gap = VERT( EM(0.4, ps) );	/* 0.4 m between blocks */
	if( type=='-' ) gap = 0;
E 2
I 2
pile(oct)
	int oct;
{
	int i, nlist, nlist2, mid;
D 3
	float bi, hi, h, b, gap;
E 3
I 3
	float bi, hi, h, b, gap, sb;
	extern float Pilegap, Pilebase;
E 3
	int type, p1, p2;

	yyval = salloc();
	type = lp[oct];
	p1 = oct + 3;		/* first entry */
	p2 = p1 + lp[oct+1];	/* 1 after last */
	gap = lp[oct+2];
	if (gap != DEFGAP)
		gap = EM(gap/100.0, ps);
	else if (type == COL)
		gap = 0;
	else
D 3
		gap = EM(0.4, ps);	/* 0.4 m between LCOL, etc. */
E 3
I 3
		gap = EM(Pilegap, ps);	/* 0.4 m between LCOL, etc. */
E 3
E 2
	nlist = p2 - p1;
	nlist2 = (nlist+1)/2;
D 2
	mid = p1 + nlist2 -1;
E 2
I 2
	mid = p1 + nlist2 - 1;
E 2
	h = 0;
D 2
	for( i=p1; i<p2; i++ )
E 2
I 2
	for (i = p1; i < p2; i++)
E 2
		h += eht[lp[i]];
	eht[yyval] = h + (nlist-1)*gap;
	b = 0;
D 2
	for( i=p2-1; i>mid; i-- )
E 2
I 2
	for (i = p2-1; i > mid; i--)
E 2
		b += eht[lp[i]] + gap;
	ebase[yyval] = (nlist%2) ? b + ebase[lp[mid]]
D 2
			: b - VERT( EM(0.5, ps) ) - gap;
	if(dbg) {
		printf(".\tS%d <- %c pile of:", yyval, type);
		for( i=p1; i<p2; i++)
E 2
I 2
D 3
			: b - EM(0.5, ps) - gap;
E 3
I 3
			: b - EM(Pilebase, ps) - gap;
E 3
	if (dbg) {
		printf(".\tS%d <- %d pile of:", yyval, type);
		for (i = p1; i < p2; i++)
E 2
			printf(" S%d", lp[i]);
D 2
		printf(";h=%d b=%d\n", eht[yyval], ebase[yyval]);
E 2
I 2
		printf("; h=%g b=%g\n", eht[yyval], ebase[yyval]);
E 2
	}
	nrwid(lp[p1], ps, lp[p1]);
	printf(".nr %d \\n(%d\n", yyval, lp[p1]);
D 2
	for( i = p1+1; i<p2; i++ ) {
E 2
I 2
	for (i = p1+1; i < p2; i++) {
E 2
		nrwid(lp[i], ps, lp[i]);
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", 
			lp[i], yyval, yyval, lp[i]);
	}
D 2
	printf(".ds %d \\v'%du'\\h'%du*\\n(%du'\\\n", yyval, ebase[yyval], 
		type=='R' ? 1 : 0, yyval);
	for(i = p2-1; i >=p1; i--) {
E 2
I 2
	printf(".ds %d \\v'%gm'\\h'%du*\\n(%du'\\\n", yyval, REL(ebase[yyval],ps), 
		type==RCOL ? 1 : 0, yyval);
I 3
	sb = 0;		/* sum of box hts */
E 3
	for (i = p2-1; i >= p1; i--) {
E 2
D 3
		hi = eht[lp[i]]; 
		bi = ebase[lp[i]];
D 2
	switch(type) {

	case 'L':
		printf("\\v'%du'\\*(%d\\h'-\\n(%du'\\v'0-%du'\\\n", 
			-bi, lp[i], lp[i], hi-bi+gap);
E 2
I 2
	switch (type) {
	case LCOL:
		printf("\\v'%gm'\\*(%d\\h'-\\n(%du'\\v'0-%gm'\\\n", 
			REL(-bi,ps), lp[i], lp[i], REL(hi-bi+gap,ps));
E 2
		continue;
D 2
	case 'R':
		printf("\\v'%du'\\h'-\\n(%du'\\*(%d\\v'0-%du'\\\n", 
			-bi, lp[i], lp[i], hi-bi+gap);
E 2
I 2
	case RCOL:
		printf("\\v'%gm'\\h'-\\n(%du'\\*(%d\\v'0-%gm'\\\n", 
			REL(-bi,ps), lp[i], lp[i], REL(hi-bi+gap,ps));
E 2
		continue;
D 2
	case 'C':
	case '-':
		printf("\\v'%du'\\h'\\n(%du-\\n(%du/2u'\\*(%d", 
			-bi, yyval, lp[i], lp[i]);
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'0-%du'\\\n", 
			yyval, lp[i], hi-bi+gap);
E 2
I 2
	case CCOL:
	case COL:
		printf("\\v'%gm'\\h'\\n(%du-\\n(%du/2u'\\*(%d", 
			REL(-bi,ps), yyval, lp[i], lp[i]);
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'0-%gm'\\\n", 
			yyval, lp[i], REL(hi-bi+gap,ps));
E 2
		continue;
E 3
I 3
		bi = sb + ebase[lp[i]];
		switch (type) {
		case LCOL:
			printf("\\v'%gm'\\*(%d\\h'-\\n(%du'\\v'%gm'\\\n", 
				REL(-bi,ps), lp[i], lp[i], REL(bi,ps));
			break;
		case RCOL:
			printf("\\v'%gm'\\h'-\\n(%du'\\*(%d\\v'%gm'\\\n", 
				REL(-bi,ps), lp[i], lp[i], REL(bi,ps));
			break;
		case CCOL:
		case COL:
			printf("\\v'%gm'\\h'\\n(%du-\\n(%du/2u'\\*(%d", 
				REL(-bi,ps), yyval, lp[i], lp[i]);
			printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%gm'\\\n", 
				yyval, lp[i], REL(bi,ps));
			break;
E 3
		}
I 3
		sb += eht[lp[i]] + gap;
E 3
	}
D 2
	printf("\\v'%du'\\h'%du*\\n(%du'\n", eht[yyval]-ebase[yyval]+gap, 
		type!='R' ? 1 : 0, yyval);
	for( i=p1; i<p2; i++ )
		ofree(lp[i]);
E 2
I 2
D 3
	printf("\\v'%gm'\\h'%du*\\n(%du'\n", REL(eht[yyval]-ebase[yyval]+gap,ps), 
E 3
I 3
	printf("\\v'%gm'\\h'%du*\\n(%du'\n", REL(-ebase[yyval],ps), 
E 3
		type!=RCOL ? 1 : 0, yyval);
	for (i = p1; i < p2; i++)
		sfree(lp[i]);
E 2
	lfont[yyval] = rfont[yyval] = 0;
}
E 1
