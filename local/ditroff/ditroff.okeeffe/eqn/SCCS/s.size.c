h25500
s 00006/00004/00069
d D 2.2 87/04/01 15:18:30 jaap 3 2
c Updates from bwk, see README for details
e
s 00048/00024/00025
d D 2.1 85/07/18 18:10:15 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00049/00000/00000
d D 1.1 85/03/01 15:27:16 jaap 1 0
c date and time created 85/03/01 15:27:16 by jaap
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
I 2
# include <ctype.h>
E 2

setsize(p)	/* set size as found in p */
D 2
char *p;
E 2
I 2
	char *p;
E 2
{
D 2
	if (*p == '+')
E 2
I 2
	nszstack++;
	szstack[nszstack] = 0;		/* assume relative */
	if (*p == '+') {
E 2
		ps += atoi(p+1);
D 2
	else if (*p == '-')
E 2
I 2
		if (szstack[nszstack-1] != 0)	/* propagate absolute size */
			szstack[nszstack] = ps;
	} else if (*p == '-') {
E 2
		ps -= atoi(p+1);
D 2
	else
		ps = atoi(p);
	if(dbg)printf(".\tsetsize %s; ps = %d\n", p, ps);
E 2
I 2
		if (szstack[nszstack-1] != 0)
			szstack[nszstack] = ps;
	} else if (isdigit(*p)) {
I 3
		if (szstack[nszstack-1] == 0)
			printf(".nr %d \\n(.s\n", 99-nszstack);
		else
			printf(".nr %d %d\n", 99-nszstack, ps);
E 3
		szstack[nszstack] = ps = atoi(p);
D 3
		printf(".nr %d \\n(.s\n", 99-nszstack);
E 3
	} else {
		error(!FATAL, "illegal size %s ignored", p);
	}
	dprintf(".\tsetsize %s; ps = %d\n", p, ps);
E 2
}

D 2
size(p1, p2) int p1, p2; {
E 2
I 2
size(p1, p2)
	int p1, p2;
{
E 2
		/* old size in p1, new in ps */
D 2
	int effps, effp1;

E 2
	yyval = p2;
D 2
	if(dbg)printf(".\tb:sb: S%d <- \\s%d S%d \\s%d; b=%d, h=%d\n", 
E 2
I 2
	dprintf(".\tS%d <- \\s%d %d \\s%d; b=%g, h=%g\n", 
E 2
		yyval, ps, p2, p1, ebase[yyval], eht[yyval]);
D 2
	effps = EFFPS(ps);
	effp1 = EFFPS(p1);
	printf(".ds %d \\s%d\\*(%d\\s%d\n", 
		yyval, effps, p2, effp1);
E 2
I 2
	if (szstack[nszstack] != 0) {
D 3
		/* sizes ought to be generated from macro as \s(dd */
		printf(".ds %d \\s%d\\*(%d\\s\\n(%d\n", yyval, ps, p2, 99-nszstack);
E 3
I 3
		printf(".ds %d %s\\*(%d\\s\\n(%d\n", yyval, ABSPS(ps), p2, 99-nszstack);
E 3
	} else
		printf(".ds %d %s\\*(%d%s\n", yyval, DPS(p1,ps), p2, DPS(ps,p1));
	nszstack--;
E 2
	ps = p1;
}

D 2
globsize() {
E 2
I 2
globsize()
{
E 2
	char temp[20];

D 2
	getstr(temp, 20);
	if (temp[0] == '+')
E 2
I 2
	getstr(temp, sizeof(temp));
	if (temp[0] == '+') {
E 2
		gsize += atoi(temp+1);
D 2
	else if (temp[0] == '-')
E 2
I 2
		if (szstack[0] != 0)
			szstack[0] = gsize;
	} else if (temp[0] == '-') {
E 2
		gsize -= atoi(temp+1);
D 2
	else
E 2
I 2
		if (szstack[0] != 0)
			szstack[0] = gsize;
	} else  if (isdigit(temp[0])) {
E 2
		gsize = atoi(temp);
I 2
		szstack[0] = gsize;
		printf(".nr 99 \\n(.s\n");
	} else {
		error(!FATAL, "illegal gsize %s ignored", temp);
	}
E 2
	yyval = eqnreg = 0;
D 2
	setps(gsize);
E 2
	ps = gsize;
D 2
	if (gsize >= 12)	/* sub and sup size change */
E 2
I 2
D 3
	if (gsize < 12)		/* sub and sup size change */
E 3
I 3
	if (gsize < 12 && !dps_set)		/* sub and sup size change */
E 3
		deltaps = gsize / 3;
	else if (gsize < 20)
E 2
		deltaps = gsize / 4;
	else
D 2
		deltaps = gsize / 3;
E 2
I 2
		deltaps = gsize / 5;
E 2
}
E 1
