h59108
s 00001/00004/00105
d D 1.2 83/08/15 16:28:21 slatteng 2 1
c removed all device-dependent code.  That means anything that was
c optimized for a particular typesetter is gone, and eqn now looks up the
c output device in a device file, like everybody else.
e
s 00109/00000/00000
d D 1.1 83/08/15 10:12:18 slatteng 1 0
c date and time created 83/08/15 10:12:18 by slatteng
e
u
U
t
T
I 1
# include "e.h"

paren(leftc, p1, rightc) int p1, leftc, rightc; {
	int n, m, h1, j, b1, v;
	h1 = eht[p1]; b1 = ebase[p1];
	yyval = p1;
	lfont[yyval] = rfont[yyval] = 0;
	n = (h1 + EM(1.0, EFFPS(ps)) - 1) / EM(1.0, EFFPS(ps));
	if( n<2 ) n = 1;
	m = n-2;
	if (leftc=='{' || rightc == '}') {
		n = n%2 ? n : ++n;
		if( n<3 ) n=3;
		m = n-3;
	}
	eht[yyval] = VERT( EM(n, ps) );
	ebase[yyval] = b1 + (eht[yyval]-h1)/2;
	v = b1 - h1/2 + VERT( EM(0.4, ps) );
	v = 0;	/* BUG??? */
	printf(".ds %d \\|\\v'%du'", yyval, v);
	switch( leftc ) {
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
	printf("\\v'%du'\\*(%d", -v, p1);
	if( rightc ) {
D 2
		if (ttype == DEV202)
			printf("\\v'%du'", v);
		else
			printf("\\|\\v'%du'", v);
E 2
I 2
		printf("\\|\\v'%du'", v);
E 2
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
	}
	printf("\n");
	if(dbg)printf(".\tcurly: h=%d b=%d n=%d v=%d l=%c, r=%c\n", 
		eht[yyval], ebase[yyval], n, v, leftc, rightc);
}

brack(m, t, c, b) int m; char *t, *c, *b; {
	int j;
	printf("\\b'%s", t);
	for( j=0; j<m; j++)
		printf("%s", c);
	printf("%s'", b);
}
E 1
