h01310
s 00002/00001/00119
d D 2.2 87/04/01 15:18:15 jaap 3 2
c Updates from bwk, see README for details
e
s 00083/00075/00037
d D 2.1 85/07/18 18:09:27 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00112/00000/00000
d D 1.1 85/03/01 15:27:11 jaap 1 0
c date and time created 85/03/01 15:27:11 by jaap
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
paren(leftc, p1, rightc) int p1, leftc, rightc; {
	int n, m, h1, j, b1, v;
	h1 = eht[p1]; b1 = ebase[p1];
E 2
I 2
paren(leftc, p1, rightc)
	int p1, leftc, rightc;
{
	int n, m, j;
	float h1, b1, v;
I 3
	extern float Parenbase;
E 3

	h1 = eht[p1];
	b1 = ebase[p1];
E 2
	yyval = p1;
	lfont[yyval] = rfont[yyval] = 0;
D 2
	n = (h1 + EM(1.0, EFFPS(ps)) - 1) / EM(1.0, EFFPS(ps));
	if( n<2 ) n = 1;
	m = n-2;
	if (leftc=='{' || rightc == '}') {
E 2
I 2
	n = REL(h1,ps) + 0.99;	/* ceiling */
	if (n < 2)
		n = 1;
	m = n - 2;
	if (leftc == '{' || rightc == '}') {
E 2
		n = n%2 ? n : ++n;
D 2
		if( n<3 ) n=3;
E 2
I 2
		if (n < 3)
			n = 3;
E 2
		m = n-3;
	}
D 2
	eht[yyval] = VERT( EM(n, ps) );
	ebase[yyval] = b1 + (eht[yyval]-h1)/2;
	v = b1 - h1/2 + VERT( EM(0.4, ps) );
	v = 0;	/* BUG??? */
	printf(".ds %d \\|\\v'%du'", yyval, v);
	switch( leftc ) {
		case 'n':	/* nothing */
		case '\0':
			break;
E 2
I 2
	eht[yyval] = EM((float) n, ps);
D 3
	ebase[yyval] = eht[yyval]/2 - EM(0.4, ps);
E 3
I 3
	ebase[yyval] = eht[yyval]/2 - EM(Parenbase, ps);
E 3
	/* v = REL(-ebase[yyval] + (eht[yyval]-h1)/2 + b1, ps); */
	v = 0;	/* in other words, don't shift it at all */
	printf(".ds %d \\|", yyval);
	switch (leftc) {
	case 'n':	/* nothing */
	case '\0':
		break;
	case 'f':	/* floor */
		if (n <= 1)
			printf("\\(lf");
		else
			brack(m, "\\(bv", "\\(bv", "\\(lf");
		break;
	case 'c':	/* ceiling */
		if (n <= 1)
			printf("\\(lc");
		else
			brack(m, "\\(lc", "\\(bv", "\\(bv");
		break;
	case '{':
		printf("\\b'\\(lt");
		for(j = 0; j < m; j += 2) printf("\\(bv");
		printf("\\(lk");
		for(j = 0; j < m; j += 2) printf("\\(bv");
		printf("\\(lb'");
		break;
	case '(':
		brack(m, "\\(lt", "\\(bv", "\\(lb");
		break;
	case '[':
		brack(m, "\\(lc", "\\(bv", "\\(lf");
		break;
	case '|':
		brack(m, "|", "|", "|");
		break;
	default:
		brack(m, (char *) &leftc, (char *) &leftc, (char *) &leftc);
		break;
	}
	if (v)
		printf("\\v'%gm'\\*(%d\\v'%gm'", -v, p1, v);
	else
		printf("\\*(%d", p1);
	if (rightc) {
		switch (rightc) {
E 2
		case 'f':	/* floor */
			if (n <= 1)
D 2
				printf("\\(lf");
E 2
I 2
				printf("\\(rf");
E 2
			else
D 2
				brack(m, "\\(bv", "\\(bv", "\\(lf");
E 2
I 2
				brack(m, "\\(bv", "\\(bv", "\\(rf");
E 2
			break;
		case 'c':	/* ceiling */
			if (n <= 1)
D 2
				printf("\\(lc");
E 2
I 2
				printf("\\(rc");
E 2
			else
D 2
				brack(m, "\\(lc", "\\(bv", "\\(bv");
E 2
I 2
				brack(m, "\\(rc", "\\(bv", "\\(bv");
E 2
			break;
D 2
		case '{':
			printf("\\b'\\(lt");
E 2
I 2
		case '}':
			printf("\\b'\\(rt");
E 2
			for(j = 0; j < m; j += 2) printf("\\(bv");
D 2
			printf("\\(lk");
E 2
I 2
			printf("\\(rk");
E 2
			for(j = 0; j < m; j += 2) printf("\\(bv");
D 2
			printf("\\(lb'");
E 2
I 2
			printf("\\(rb'");
E 2
			break;
D 2
		case '(':
			brack(m, "\\(lt", "\\(bv", "\\(lb");
E 2
I 2
		case ']':
			brack(m, "\\(rc", "\\(bv", "\\(rf");
E 2
			break;
D 2
		case '[':
			brack(m, "\\(lc", "\\(bv", "\\(lf");
E 2
I 2
		case ')':
			brack(m, "\\(rt", "\\(bv", "\\(rb");
E 2
			break;
		case '|':
			brack(m, "|", "|", "|");
			break;
		default:
D 2
			brack(m, (char *) &leftc, (char *) &leftc, (char *) &leftc);
E 2
I 2
			brack(m, (char *) &rightc, (char *) &rightc, (char *) &rightc);
E 2
			break;
		}
D 2
	printf("\\v'%du'\\*(%d", -v, p1);
	if( rightc ) {
		if (ttype == DEV202)
			printf("\\v'%du'", v);
		else
			printf("\\|\\v'%du'", v);
		switch( rightc ) {
			case 'f':	/* floor */
				if (n <= 1)
					printf("\\(rf");
				else
					brack(m, "\\(bv", "\\(bv", "\\(rf");
				break;
			case 'c':	/* ceiling */
				if (n <= 1)
					printf("\\(rc");
				else
					brack(m, "\\(rc", "\\(bv", "\\(bv");
				break;
			case '}':
				printf("\\b'\\(rt");
				for(j = 0; j< m; j += 2)printf("\\(bv");
				printf("\\(rk");
				for(j = 0; j< m; j += 2) printf("\\(bv");
				printf("\\(rb'");
				break;
			case ']':
				brack(m, "\\(rc", "\\(bv", "\\(rf");
				break;
			case ')':
				brack(m, "\\(rt", "\\(bv", "\\(rb");
				break;
			case '|':
				brack(m, "|", "|", "|");
				break;
			default:
				brack(m, (char *) &rightc, (char *) &rightc, (char *) &rightc);
				break;
		}
		printf("\\v'%du'", -v);
E 2
	}
	printf("\n");
D 2
	if(dbg)printf(".\tcurly: h=%d b=%d n=%d v=%d l=%c, r=%c\n", 
E 2
I 2
	dprintf(".\tcurly: h=%g b=%g n=%d v=%g l=%c, r=%c\n", 
E 2
		eht[yyval], ebase[yyval], n, v, leftc, rightc);
}

D 2
brack(m, t, c, b) int m; char *t, *c, *b; {
E 2
I 2
brack(m, t, c, b)
	int m;
	char *t, *c, *b;
{
E 2
	int j;
	printf("\\b'%s", t);
D 2
	for( j=0; j<m; j++)
E 2
I 2
	for( j=0; j < m; j++)
E 2
		printf("%s", c);
	printf("%s'", b);
}
E 1
