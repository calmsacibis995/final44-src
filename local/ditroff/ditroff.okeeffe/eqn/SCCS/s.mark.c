h64946
s 00012/00009/00011
d D 2.1 85/07/18 18:08:52 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00020/00000/00000
d D 1.1 85/03/01 15:27:04 jaap 1 0
c date and time created 85/03/01 15:27:04 by jaap
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
#include "e.h"

D 2
mark(p1) int p1; {
E 2
I 2
mark(p1)
	int p1;
{
E 2
	markline = 1;
D 2
	printf(".ds %d \\k(97\\*(%d\n", p1, p1);
E 2
I 2
	printf(".ds %d \\k(09\\*(%d\n", p1, p1);
E 2
	yyval = p1;
D 2
	if(dbg)printf(".\tmark %d\n", p1);
E 2
I 2
	dprintf(".\tmark %d\n", p1);
E 2
}

D 2
lineup(p1) {
E 2
I 2
lineup(p1)
{
E 2
	markline = 2;
	if (p1 == 0) {
D 2
		yyval = oalloc();
		printf(".ds %d \\h'|\\n(97u'\n", yyval);
E 2
I 2
		yyval = salloc();
		printf(".ds %d \\h'|\\n(09u'\n", yyval);
E 2
	}
D 2
	if(dbg)printf(".\tlineup %d\n", p1);
E 2
I 2
	dprintf(".\tlineup %d\n", p1);
E 2
}
E 1
