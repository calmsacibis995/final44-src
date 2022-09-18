h39959
s 00012/00007/00118
d D 1.2 85/10/02 14:39:29 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00125/00000/00000
d D 1.1 85/10/01 18:09:24 jaap 1 0
c date and time created 85/10/01 18:09:24 by jaap
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% (CWI) %E%";
#endif lint


D 2
 /* tt.c: subroutines for drawing horizontal lines */
E 2
I 2
/*
 * variuos subroutines for f.i drawing horizontal lines
 *
 * We could stuff more routines in this file which are used in various modules
 * of tbl, like reg in misc.c etc. We leave this for later.
 */
E 2

#include "defs.h"
#include "ext.h"

ctype(il, ic)
{

	if(instead[il])
		return(0);
	if(fullbot[il])
		return(0);
	il = stynum[il];
	return(style[il][ic]);
}

fspan(i, c)
{

	c++;
	return(c < ncol && ctype (i, c) == 's');
}

lspan(i, c)
{
D 2
	int k;
E 2
I 2
	register int k;
E 2

	if(ctype(i, c) != 's')
		return(0);
	c++;
	if(c < ncol && ctype(i, c) == 's')
		return(0);
	for(k = 0; ctype(i, --c) == 's'; k++)
		;
	return(k);
}

ctspan(i, c)
{
D 2
	int k;
E 2
I 2
	register int k;
E 2

	c++;
	for(k = 1; c < ncol && ctype(i, c) == 's'; k++)
		c++;
	return(k);
}

tohcol(ic)
{
	if(ic == 0)
		printf("\\h'|0'");
	else
		printf("\\h'(|\\n(%2su+|\\n(%2su)/2u'", reg(ic, CLEFT),
							reg(ic - 1, CRIGHT));
}

/*
 * Return true if every element in line i is horizontal
 * Also at least one must be horizontal
 */
allh(i)
{
D 2
	int c, one, k;
E 2
I 2
	register int c, one, k;
E 2

	if(fullbot[i])
		return(1);
	for(one = c = 0; c < ncol; c++){
		k = thish(i, c);
		if(k == 0)
			return(0);
		if(k == 1)
			continue;
		one = 1;
	}
	return(one);
}

thish(i, c)
{
D 2
	int t;
	char *s;
	struct colstr *pc;
E 2
I 2
	register int t;
	register char *s;
	register struct colstr *pc;
E 2

	if(c < 0)
		return(0);
	if(i < 0)
		return(0);
	t = ctype(i, c);
	if(t == '_' || t == '-')
		return('-');
	if(t == '=')
		return('=');
	if(t == '^')
		return(1);
	if(fullbot[i])
		return(fullbot[i]);
	if(t == 's')
		return(thish (i, c - 1));
	if(t == 0)
		return(1);
	pc = &table[i][c];
	s = (t == 'a' ? pc -> rcol : pc -> col);
	if(s == 0 || (point(s) && *s == 0))
		return(1);
	if(vspen(s))
		return(1);
	if(t = barent(s))
		return(t);
	return(0);
}


prefix(small, big)
char *small, *big;
{
	register int c;
	while ((c= *small++) == *big++)
		if (c==0) return(1);
	return(c==0);
}
E 1
