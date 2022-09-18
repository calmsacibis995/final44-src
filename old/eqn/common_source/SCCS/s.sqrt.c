h59267
s 00001/00001/00041
d D 4.5 93/03/01 13:07:59 torek 5 4
c sqrt => eqsqrt (name reserved as external sym in ANSI C, caught by gcc2)
e
s 00009/00002/00033
d D 4.4 91/04/17 17:25:36 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00001/00032
d D 4.3 83/08/11 20:39:47 sam 3 2
c standardize sccs keyword lines
e
s 00014/00000/00019
d D 4.2 83/02/12 18:04:10 shannon 2 1
c merge eqn and neqn
e
s 00019/00000/00000
d D 4.1 83/02/11 18:28:50 shannon 1 0
c date and time created 83/02/11 18:28:50 by shannon
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

D 5
sqrt(p2) int p2; {
E 5
I 5
eqsqrt(p2) int p2; {
E 5
I 2
#ifndef NEQN
E 2
	int nps;
I 2

E 2
	nps = EFFPS(((eht[p2]*9)/10+5)/6);
I 2
#endif NEQN
E 2
	yyval = p2;
I 2
#ifndef NEQN
E 2
	eht[yyval] = VERT( (nps*6*12)/10 );
	if(dbg)printf(".\tsqrt: S%d <- S%d;b=%d, h=%d\n", 
		yyval, p2, ebase[yyval], eht[yyval]);
	if (rfont[yyval] == ITAL)
		printf(".as %d \\|\n", yyval);
I 2
#endif NEQN
E 2
	nrwid(p2, ps, p2);
I 2
#ifndef NEQN
E 2
	printf(".ds %d \\v'%du'\\s%d\\v'-.2m'\\(sr\\l'\\n(%du\\(rn'\\v'.2m'\\s%d", 
		yyval, ebase[p2], nps, p2, ps);
	printf("\\v'%du'\\h'-\\n(%du'\\*(%d\n", -ebase[p2], p2, p2);
	lfont[yyval] = ROM;
I 2
#else NEQN
	printf(".ds %d \\v'%du'\\e\\L'%du'\\l'\\n(%du'",
		p2, ebase[p2], -eht[p2], p2);
	printf("\\v'%du'\\h'-\\n(%du'\\*(%d\n", eht[p2]-ebase[p2], p2, p2);
	eht[p2] += VERT(1);
	if(dbg)printf(".\tsqrt: S%d <- S%d;b=%d, h=%d\n", 
		p2, p2, ebase[p2], eht[p2]);
#endif NEQN
E 2
}
E 1
