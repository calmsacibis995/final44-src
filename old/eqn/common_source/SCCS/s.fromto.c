h23152
s 00009/00002/00051
d D 4.4 91/04/17 17:25:24 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00001/00050
d D 4.3 83/08/11 20:38:19 sam 3 2
c standardize sccs keyword lines
e
s 00004/00000/00047
d D 4.2 83/02/12 18:03:25 shannon 2 1
c merge eqn and neqn
e
s 00047/00000/00000
d D 4.1 83/02/11 18:28:01 shannon 1 0
c date and time created 83/02/11 18:28:01 by shannon
e
u
U
t
T
I 4
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 3

# include "e.h"

fromto(p1, p2, p3) int p1, p2, p3; {
	int b, h1, b1, pss;
	yyval = oalloc();
	lfont[yyval] = rfont[yyval] = 0;
	h1 = eht[yyval] = eht[p1];
	b1 = ebase[p1];
	b = 0;
	pss = EFFPS(ps);
	ps += 3;
	nrwid(p1, ps, p1);
	printf(".nr %d \\n(%d\n", yyval, p1);
	if( p2>0 ) {
		nrwid(p2, pss, p2);
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p2, yyval, yyval, p2);
		eht[yyval] += eht[p2];
		b = eht[p2];
	}
	if( p3>0 ) {
		nrwid(p3, pss, p3);
		printf(".if \\n(%d>\\n(%d .nr %d \\n(%d\n", p3, yyval, yyval, p3);
		eht[yyval] += eht[p3];
	}
	printf(".ds %d ", yyval);	/* bottom of middle box */
	if( p2>0 ) {
		printf("\\v'%du'\\h'\\n(%du-\\n(%du/2u'\\s%d\\*(%d\\s%d", 
			eht[p2]-ebase[p2]+b1, yyval, p2, pss, p2, EFFPS(ps));
		printf("\\h'-\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			yyval, p2, -(eht[p2]-ebase[p2]+b1));
	}
I 2
#ifndef NEQN
E 2
	printf("\\h'\\n(%du-\\n(%du/2u'\\*(%d\\h'\\n(%du-\\n(%du/2u'\\\n", 
I 2
#else NEQN
	printf("\\h'\\n(%du-\\n(%du/2u'\\*(%d\\h'\\n(%du-\\n(%du+2u/2u'\\\n", 
#endif NEQN
E 2
		yyval, p1, p1, yyval, p1);
	if( p3>0 ) {
		printf("\\v'%du'\\h'-\\n(%du-\\n(%du/2u'\\s%d\\*(%d\\s%d\\h'\\n(%du-\\n(%du/2u'\\v'%du'\\\n", 
			-(h1-b1+ebase[p3]), yyval, p3, pss, p3, EFFPS(ps), yyval, p3, (h1-b1+ebase[p3]));
	}
	printf("\n");
	ebase[yyval] = b + b1;
	if(dbg)printf(".\tfrom to: S%d <- %d f %d t %d; h=%d b=%d\n", 
		yyval, p1, p2, p3, eht[yyval], ebase[yyval]);
	ofree(p1);
	if( p2>0 ) ofree(p2);
	if( p3>0 ) ofree(p3);
}
E 1
