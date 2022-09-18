h41278
s 00000/00003/00079
d D 1.2 85/10/02 14:38:32 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00082/00000/00000
d D 1.1 85/10/01 18:09:12 jaap 1 0
c date and time created 85/10/01 18:09:12 by jaap
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

 /* tm.c: split numerical fields */

E 2
#include "defs.h"
#include "ext.h"

/*
 * Make two numerical fields
 */
char *
maknew(str)
char *str;
{
	extern char *chspace();
	int dpoint, c;
	register char *p, *q, *ba;
	
	p = str;
	for(ba = 0; c = *str; str++){
		if(c == '\\' && *(str + 1) == '&')
			ba = str;
	}
	str = p;
	if(ba == 0){
		for(dpoint = 0; *str; str++){
			if(*str == '.' && !ineqn(str, p)
				       && (str > p && isdigit(*(str - 1)) ||
							isdigit(*(str + 1))))
				dpoint = (int) str;
		}
		if(dpoint == 0){
			for(; str > p; str--){
				if(isdigit(*(str - 1)) && !ineqn (str, p))
					break;
			}
		}
		if(!dpoint && p == str)
			/*
			 * not numerical, don't split
			 */
			return(0);
		if(dpoint)
			str = (char *)dpoint;
	} else
		str = ba;
	p = str;
	if(exstore == 0 || exstore > exlim){
		exstore = chspace();
		exlim = exstore + MAXCHS;
	}
	q = exstore;
	while(*exstore++ = *str++)
		;
	*p = 0;
	return(q);
}

/*
 * True, if s is in a eqn within p
 */
ineqn(s, p)
char *s, *p;
{
	int ineq = 0, c;

	while(c = *p){
		if(s == p)
			return(ineq);
		p++;
		if((ineq == 0) && (c == delim1)){
			ineq = 1;
		} else {
			if((ineq == 1) && (c == delim2))
				ineq = 0;
		}
	}
	return(0);
}
E 1
