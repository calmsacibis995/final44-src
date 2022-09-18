h27467
s 00025/00015/00051
d D 2.2 87/04/01 15:17:25 jaap 3 2
c Updates from bwk, see README for details
e
s 00054/00054/00012
d D 2.1 85/07/18 18:06:55 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00066/00000/00000
d D 1.1 85/03/01 15:26:34 jaap 1 0
c date and time created 85/03/01 15:26:34 by jaap
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
# include "e.def"
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

I 3
extern float Dvshift, Dhshift, Dh2shift, Dheight, Barv, Barh;
extern char *Vec, *Dyad, *Hat, *Tilde, *Dot, *Dotdot, *Utilde;

E 3
D 2
diacrit(p1, type) int p1, type; {
	int c, t, effps;
E 2
I 2
diacrit(p1, type)
	int p1, type;
{
	int c, t;
E 2

D 2
	c = oalloc();
	t = oalloc();
	effps = EFFPS(ps);
	nrwid(p1, effps, p1);
	printf(".nr 10 %du\n", VERT(max(eht[p1]-ebase[p1]-EM(1,ps),0)));	/* vertical shift if high */
	printf(".if \\n(ct>1 .nr 10 \\n(10+\\s%d.25m\\s0\n", effps);
	printf(".nr %d \\s%d.1m\\s0\n", t, effps);	/* horiz shift if high */
	printf(".if \\n(ct>1 .nr %d \\s%d.15m\\s0\n", t, effps);
	switch(type) {
		case VEC:
			printf(".ds %d \\v'-.4m'\\s%d\\(->\\s0\\v'.4m'\n", c, max(effps-3, minsize));
			break;
		case DYAD:
			printf(".ds %d \\v'-.4m'\\s%d\\z\\(<-\\(->\\s0\\v'.4m'\n", c, max(effps-3, minsize));
			break;
		case HAT:
			printf(".ds %d ^\n", c);
			break;
		case TILDE:
			printf(".ds %d ~\n", c);
			break;
		case DOT:
			printf(".ds %d \\s%d\\v'-.67m'.\\v'.67m'\\s0\n", c, effps);
			break;
		case DOTDOT:
			printf(".ds %d \\s%d\\v'-.67m'..\\v'.67m\\s0'\n", c, effps);
			break;
		case BAR:
			printf(".ds %d \\s%d\\v'-.68m'\\h'.05m'\\l'\\n(%du-.1m'\\h'.05m'\\v'.68m'\\s0\n",
				c, effps, p1);
			break;
		case UNDER:
			printf(".ds %d \\l'\\n(%du\\(ul'\n", c, p1);
			printf(".nr %d 0\n", t);
			printf(".nr 10 0-%d\n", ebase[p1]);
			printf(".if \\n(ct%%2=1 .nr 10 \\n(10-.25m\n");
			break;
		case UTILDE:
			printf(".ds %d \\v'1.0m'\\s+2~\\s-2\\v'-1.0m'\n", c);
			printf(".nr %d 0\n", t);
			printf(".nr 10 0-%d\n", ebase[p1]);
			printf(".if \\n(ct%%2=1 .nr 10 \\n(10-.25m\n");
			break;
		}
E 2
I 2
	c = salloc();
	t = salloc();
	nrwid(p1, ps, p1);
	printf(".nr 10 %gm\n", max(REL(eht[p1]-ebase[p1]-1,ps), 0));	/* vert shift if high */
D 3
	printf(".if \\n(ct>1 .nr 10 \\n(10+.25m\n");
	printf(".nr %d .025m\n", t);	/* horiz shift if high */
	printf(".if \\n(ct>1 .nr %d .05m\n", t);	/* was .1 and .15 */
E 3
I 3
	if (type == HIGHBAR)
		printf(".nr 10 \\n(10+%gm\n", Dvshift);
	else if (type == LOWBAR)
		printf(".nr 10 0\n");
	else
		printf(".if \\n(ct>1 .nr 10 \\n(10+%gm\n", Dvshift);
	printf(".nr %d %gm\n", t, Dhshift);	/* horiz shift if high */
	printf(".if \\n(ct>1 .nr %d %gm\n", t, Dh2shift);	/* was .1 and .15 */
E 3
	switch (type) {
	case VEC:
D 3
		printf(".ds %d \\v'-.45m'\\s-1\\(->\\s0\\v'.45m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Vec);
E 3
		break;
	case DYAD:
D 3
		printf(".ds %d \\v'-.45m'\\s-1\\z\\(<-\\|\\(->\\s0\\v'.45m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Dyad);
E 3
		break;
	case HAT:
D 3
		printf(".ds %d \\v'-.1m'\\s+1^\\s0\\v'.1m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Hat);
E 3
		break;
	case TILDE:
D 3
		printf(".ds %d \\v'-.1m'\\s+1~\\s0\\v'.1m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Tilde);
E 3
		break;
	case DOT:
D 3
		printf(".ds %d \\v'-.67m'.\\v'.67m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Dot);
E 3
		break;
	case DOTDOT:
D 3
		printf(".ds %d \\v'-.67m'..\\v'.67m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Dotdot);
E 3
		break;
	case BAR:
D 3
		printf(".ds %d \\v'-.68m'\\h'.05m'\\l'\\n(%du-.1m'\\h'.05m'\\v'.68m'\n",
			c, p1);
E 3
I 3
	case LOWBAR:
	case HIGHBAR:
		printf(".ds %d \\v'%gm'\\h'%gm'\\l'\\n(%du-%gm'\\h'%gm'\\v'%gm'\n",
			c, -Barv, Barh, p1, 2*Barh, Barh, Barv);
E 3
		break;
	case UNDER:
		printf(".ds %d \\l'\\n(%du\\(ul'\n", c, p1);
		printf(".nr %d 0\n", t);
		printf(".nr 10 0-.1m-%gm\n", REL(ebase[p1],ps));
		printf(".if \\n(ct%%2=1 .nr 10 0\\n(10-.25m\n");
		break;
	case UTILDE:
D 3
		printf(".ds %d \\v'1.0m'\\s+2~\\s-2\\v'-1.0m'\n", c);
E 3
I 3
		printf(".ds %d %s\n", c, Utilde);
E 3
		printf(".nr %d 0\n", t);
		printf(".nr 10 0-%gm\n", REL(ebase[p1],ps));
D 3
		printf(".if \\n(ct%%2=1 .nr 10 0\\n(10-.25m\n");
E 3
I 3
		printf(".if \\n(ct%%2=1 .nr 10 0\\n(10-%gm\n", Dvshift);
E 3
		break;
	}
E 2
	nrwid(c, ps, c);
	if (lfont[p1] != ITAL)
		printf(".nr %d 0\n", t);
	printf(".as %d \\h'-\\n(%du-\\n(%du/2u+\\n(%du'\\v'0-\\n(10u'\\*(%d", 
		p1, p1, c, t, c);
	printf("\\v'\\n(10u'\\h'-\\n(%du+\\n(%du/2u-\\n(%du'\n", c, p1, t);
D 2
	/* BUG - should go to right end of widest */
E 2
	if (type != UNDER && type != UTILDE)
D 2
		eht[p1] += VERT( EM(0.15, ps) );
	if(dbg)printf(".\tdiacrit: %c over S%d, lf=%c, rf=%c, h=%d,b=%d\n",
E 2
I 2
D 3
		eht[p1] += EM(0.25, ps);	/* was .15 */
E 3
I 3
		eht[p1] += EM(Dheight, ps);	/* was .15 */
E 3
	dprintf(".\tdiacrit: %c over S%d, lf=%c, rf=%c, h=%g, b=%g\n",
E 2
		type, p1, lfont[p1], rfont[p1], eht[p1], ebase[p1]);
D 2
	ofree(c); ofree(t);
E 2
I 2
	sfree(c); sfree(t);
E 2
}
E 1
