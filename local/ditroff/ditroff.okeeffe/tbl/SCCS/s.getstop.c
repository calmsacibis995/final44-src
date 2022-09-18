h09163
s 00003/00001/00103
d D 1.2 85/10/02 14:36:47 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00104/00000/00000
d D 1.1 85/10/01 18:08:49 jaap 1 0
c date and time created 85/10/01 18:08:49 by jaap
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
 /* tu.c: draws horizontal lines */
E 2
I 2
/*
 * find the start points for the line drawing routines
 */
E 2

#include "defs.h"
#include "ext.h"

getstop()
{
	register int i, c, k;
	int junk, stopp;

	stopp = 1;
	for(i = 0; i < MAXLIN; i++)
		linestop[i] = 0;
	for(i = 0; i < nlin; i++){
		for(c = 0; c < ncol; c++){
			k = left(i, c, &junk);
			if(k >= 0 && linestop[k] == 0)
				linestop[k] = ++stopp;
		}
	}
	if(boxflg || allflg || dboxflg)
		linestop[0] = 1;
}

/*
 * returns -1 if no line to left
 * returns number of line where it starts
 * stores into lwid the kind of line
 */
left(i, c, lwidp)
int i, c;
int *lwidp;
{
	register int kind, li, lj;

	*lwidp = 0;
	kind = lefdata(i, c);
	if(kind == 0)
		return(-1);
	if(i + 1 < nlin){
		if(lefdata(next (i), c) == kind)
			return(-1);
	}
	while(i >= 0 && lefdata(i, c) == kind)
		i = prev(li = i);
	if(prev(li) == -1)
		li = 0;
	*lwidp = kind;
	for(lj = i + 1; lj < li; lj++){
		if(instead[lj] && strcmp(instead[lj], ".TH") == 0)
			return(li);
	}
	for(i = i + 1; i < li; i++){
		if(fullbot[i])
			li = i;
	}
	return(li);
}

lefdata(i, c)
{
	register int ck;

	if(i >= nlin)
		i = nlin - 1;
	if(ctype(i, c) == 's'){
		for(ck = c; ctype(i, ck) == 's'; ck--)
			;
		if(thish(i, ck) == 0)
			return(0);
	}
	i = stynum[i];
	i = lefline[i][c];
	if(i > 0)
		return(i);
	if(dboxflg && c == 0)
		return(2);
	if(allflg)
		return(1);
	if(boxflg && c == 0)
		return(1);
	return(0);
}

next(i)
{
	while(i + 1 < nlin){
		i++;
		if(!fullbot[i] && !instead[i])
			break;
	}
	return(i);
}

prev(i){
	while(--i >= 0 && (fullbot[i] || instead[i]))
		;
	return(i);
}
E 1
