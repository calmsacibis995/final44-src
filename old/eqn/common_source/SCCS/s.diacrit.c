h60349
s 00009/00002/00103
d D 4.4 91/04/17 17:25:22 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00001/00102
d D 4.3 83/08/11 20:38:05 sam 3 2
c standardize sccs keyword lines
e
s 00050/00005/00053
d D 4.2 83/02/12 18:03:08 shannon 2 1
c merge eqn and neqn
e
s 00058/00000/00000
d D 4.1 83/02/11 18:27:40 shannon 1 0
c date and time created 83/02/11 18:27:40 by shannon
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
# include "e.def"

diacrit(p1, type) int p1, type; {
D 2
	int c, t, effps;
E 2
I 2
	int c, t;
#ifndef NEQN
	int effps;
#endif NEQN
E 2

	c = oalloc();
	t = oalloc();
I 2
#ifdef NEQN
	nrwid(p1, ps, p1);
	printf(".nr 10 %du\n", max(eht[p1]-ebase[p1]-VERT(2),0));
#else NEQN
E 2
	effps = EFFPS(ps);
	nrwid(p1, effps, p1);
	printf(".nr 10 %du\n", VERT(max(eht[p1]-ebase[p1]-6*ps,0)));	/* vertical shift if high */
	printf(".if \\n(ct>1 .nr 10 \\n(10+\\s%d.25m\\s0\n", effps);
	printf(".nr %d \\s%d.1m\\s0\n", t, effps);	/* horiz shift if high */
	printf(".if \\n(ct>1 .nr %d \\s%d.15m\\s0\n", t, effps);
I 2
#endif NEQN
E 2
	switch(type) {
D 2
		case VEC:
			printf(".ds %d \\v'-.4m'\\s%d\\(->\\s0\\v'.4m'\n", c, max(effps-3, 6));
E 2
I 2
		case VEC:	/* vec */
#ifndef NEQN
			printf(".ds %d \\v'-.4m'\\s%d\\(->\\s0\\v'.4m'\n",
			    c, max(effps-3, 6));
E 2
			break;
D 2
		case DYAD:
			printf(".ds %d \\v'-.4m'\\s%d\\z\\(<-\\(->\\s0\\v'.4m'\n", c, max(effps-3, 6));
E 2
I 2
#endif NEQN
		case DYAD:	/* dyad */
#ifdef NEQN
			printf(".ds %d \\v'-1'_\\v'1'\n", c);
#else NEQN
			printf(".ds %d \\v'-.4m'\\s%d\\z\\(<-\\(->\\s0\\v'.4m'\n",
			    c, max(effps-3, 6));
#endif NEQN
E 2
			break;
		case HAT:
			printf(".ds %d ^\n", c);
			break;
		case TILDE:
			printf(".ds %d ~\n", c);
			break;
		case DOT:
I 2
#ifndef NEQN
E 2
			printf(".ds %d \\s%d\\v'-.67m'.\\v'.67m'\\s0\n", c, effps);
I 2
#else NEQN
			printf(".ds %d \\v'-1'.\\v'1'\n", c);
#endif NEQN
E 2
			break;
		case DOTDOT:
I 2
#ifndef NEQN
E 2
			printf(".ds %d \\s%d\\v'-.67m'..\\v'.67m\\s0'\n", c, effps);
I 2
#else NEQN
			printf(".ds %d \\v'-1'..\\v'1'\n", c);
#endif NEQN
E 2
			break;
		case BAR:
I 2
#ifndef NEQN
E 2
			printf(".ds %d \\s%d\\v'.18m'\\h'.05m'\\l'\\n(%du-.1m\\(rn'\\h'.05m'\\v'-.18m'\\s0\n",
				c, effps, p1);
I 2
#else NEQN
			printf(".ds %d \\v'-1'\\l'\\n(%du'\\v'1'\n", 
				c, p1);
#endif NEQN
E 2
			break;
		case UNDER:
I 2
#ifndef NEQN
E 2
			printf(".ds %d \\l'\\n(%du\\(ul'\n", c, p1);
			printf(".nr %d 0\n", t);
			printf(".nr 10 0-%d\n", ebase[p1]);
I 2
#else NEQN
			printf(".ds %d \\l'\\n(%du'\n", c, p1);
#endif NEQN
E 2
			break;
		}
	nrwid(c, ps, c);
I 2
#ifndef NEQN
E 2
	if (lfont[p1] != ITAL)
		printf(".nr %d 0\n", t);
	printf(".as %d \\h'-\\n(%du-\\n(%du/2u+\\n(%du'\\v'0-\\n(10u'\\*(%d", 
		p1, p1, c, t, c);
	printf("\\v'\\n(10u'\\h'-\\n(%du+\\n(%du/2u-\\n(%du'\n", c, p1, t);
	/* BUG - should go to right end of widest */
I 2
#else NEQN
	printf(".as %d \\h'-\\n(%du-\\n(%du/2u'\\v'0-\\n(10u'\\*(%d", 
		p1, p1, c, c);
	printf("\\v'\\n(10u'\\h'-\\n(%du+\\n(%du/2u'\n", c, p1);
#endif NEQN
#ifndef NEQN
E 2
	if (type != UNDER)
		eht[p1] += VERT( (6*ps*15) / 100);	/* 0.15m */
	if(dbg)printf(".\tdiacrit: %c over S%d, lf=%c, rf=%c, h=%d,b=%d\n",
		type, p1, lfont[p1], rfont[p1], eht[p1], ebase[p1]);
I 2
#else NEQN
	if (type != UNDER)
		eht[p1] += VERT(1);
	if (dbg) printf(".\tdiacrit: %c over S%d, h=%d, b=%d\n", type, p1, eht[p1], ebase[p1]);
#endif NEQN
E 2
	ofree(c); ofree(t);
}
E 1
