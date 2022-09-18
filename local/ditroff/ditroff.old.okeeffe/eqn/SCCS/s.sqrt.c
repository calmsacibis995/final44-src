h31363
s 00002/00008/00016
d D 1.2 83/08/15 16:28:26 slatteng 2 1
c removed all device-dependent code.  That means anything that was
c optimized for a particular typesetter is gone, and eqn now looks up the
c output device in a device file, like everybody else.
e
s 00024/00000/00000
d D 1.1 83/08/15 10:12:20 slatteng 1 0
c date and time created 83/08/15 10:12:20 by slatteng
e
u
U
t
T
I 1
# include "e.h"

sqrt(p2) int p2; {
	int nps;

	nps = EFFPS(((eht[p2]*9)/10+(res/POINT-1))/(res/POINT));
	yyval = p2;
D 2
	if (ttype == DEVCAT || ttype == DEVAPS)
		eht[yyval] = VERT( EM(1.2, nps) );
	else if (ttype == DEV202)
		eht[yyval] = VERT( EM(1.0, nps) );
E 2
I 2
	eht[yyval] = VERT( EM(1.2, nps) );
E 2
	if(dbg)printf(".\tsqrt: S%d <- S%d;b=%d, h=%d\n", 
		yyval, p2, ebase[yyval], eht[yyval]);
	if (rfont[yyval] == ITAL)
		printf(".as %d \\|\n", yyval);
	nrwid(p2, ps, p2);
	printf(".ds %d \\v'%du'\\s%d", yyval, ebase[p2], nps);	/* proper position for sqrt */
D 2
	if (ttype == DEVCAT || ttype == DEVAPS)
		printf("\\v'-.2m'\\(sr\\l'\\n(%du\\(rn'\\v'.2m'", p2);
	else
		printf("\\(sr\\l'\\n(%du\\(rn'", p2);	/* .95 best for 10; .9 best for 16 */
E 2
I 2
	printf("\\v'-.2m'\\(sr\\l'\\n(%du\\(rn'\\v'.2m'", p2);
E 2
	printf("\\s%d\\v'%du'\\h'-\\n(%du'\\*(%d\n", ps, -ebase[p2], p2, p2);
	lfont[yyval] = ROM;
}
E 1
