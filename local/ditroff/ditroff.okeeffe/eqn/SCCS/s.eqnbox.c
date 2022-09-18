h31640
s 00002/00001/00027
d D 2.2 87/04/01 15:17:34 jaap 3 2
c Updates from bwk, see README for details
e
s 00010/00010/00018
d D 2.1 85/07/18 18:07:18 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00028/00000/00000
d D 1.1 85/03/01 15:26:41 jaap 1 0
c date and time created 85/03/01 15:26:41 by jaap
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
eqnbox(p1, p2, lu) {
	int b, h;
E 2
I 2
eqnbox(p1, p2, lu)
{
	float b, h;
E 2
	char *sh;
I 3
	extern char *IRspace;
E 3

	yyval = p1;
	b = max(ebase[p1], ebase[p2]);
	eht[yyval] = h = b + max(eht[p1]-ebase[p1], 
		eht[p2]-ebase[p2]);
	ebase[yyval] = b;
D 2
	if(dbg)printf(".\te:eb: S%d <- S%d S%d; b=%d, h=%d\n", 
		yyval, p1, p2, b, h);
E 2
I 2
	dprintf(".\tS%d <- %d %d; b=%g, h=%g\n", yyval, p1, p2, b, h);
E 2
	if (rfont[p1] == ITAL && lfont[p2] == ROM)
D 2
		sh = "\\|";
E 2
I 2
D 3
		sh = "\\^";	/* was \| */
E 3
I 3
		sh = IRspace;	/* was \| */
E 3
E 2
	else
		sh = "";
	if (lu) {
D 2
		printf(".nr %d \\w'\\s%d\\*(%d%s'\n", p1, ps, p1, sh);
		printf(".ds %d \\h'|\\n(97u-\\n(%du'\\*(%d\n", p1, p1, p1);
E 2
I 2
		printf(".nr %d \\w'\\*(%d%s'\n", p1, p1, sh);
		printf(".ds %d \\h'|\\n(09u-\\n(%du'\\*(%d\n", p1, p1, p1);
E 2
	}
	printf(".as %d \"%s\\*(%d\n", yyval, sh, p2);
	rfont[p1] = rfont[p2];
D 2
	ofree(p2);
E 2
I 2
	sfree(p2);
E 2
}
E 1
