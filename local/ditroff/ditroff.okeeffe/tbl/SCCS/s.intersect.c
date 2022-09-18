h41386
s 00003/00001/00073
d D 1.2 85/10/02 14:37:11 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00074/00000/00000
d D 1.1 85/10/01 18:09:02 jaap 1 0
c date and time created 85/10/01 18:09:02 by jaap
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
 /* ti.c: classify line intersections */
E 2
I 2
/*
 * classify line intersections
 */
E 2

#include "defs.h"
#include "ext.h"

/*
 * determine local environment for intersections
 */
interv(i, c){
	register int ku, kl;

	if(c >= ncol || c == 0){
		if(dboxflg){
			if(i == 0)
				return(BOT);
			if(i >= nlin)
				return(TOP);
			return(THRU);
		}
		if(c >= ncol)
			return(0);
	}
	ku = i > 0 ? lefdata(i - 1, c) : 0;
	if(i + 1 >= nlin)
		kl = 0;
	else
		kl = lefdata(allh (i) ? i + 1 : i, c);
	if(ku == 2 && kl == 2)
		return(THRU);
	if(ku == 2)
		return(TOP);
	if(kl == BOT)
		return(2);
	return(0);
}

interh(i, c){
	register int kl, kr;

	if(fullbot[i] == '=' || (dboxflg && (i == 0 || i >= nlin - 1))){
		if(c == ncol)
			return(LEFT);
		if(c == 0)
			return(RIGHT);
		return(THRU);
	}
	if(i >= nlin)
		return(0);
	kl = c > 0 ? thish(i, c - 1) : 0;
	if(kl <= 1 && i > 0 && allh(up1 (i)))
		kl = c > 0 ? thish(up1 (i), c - 1) : 0;
	kr = thish(i, c);
	if(kr <= 1 && i > 0 && allh(up1 (i)))
		kr = c > 0 ? thish(up1 (i), c) : 0;
	if(kl == '=' && kr == '=')
		return(THRU);
	if(kl == '=')
		return(LEFT);
	if(kr == '=')
		return(RIGHT);
	return(0);
}

up1(i){
	i--;
	while(instead[i] && i > 0)
		i--;
	return(i);
}
E 1
