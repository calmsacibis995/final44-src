h09970
s 00003/00001/00080
d D 1.2 85/10/02 14:36:42 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00081/00000/00000
d D 1.1 85/10/01 18:08:47 jaap 1 0
c date and time created 85/10/01 18:08:47 by jaap
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
 /* tc.c: find character not in table to delimit fields */
E 2
I 2
/* 
 * find character not in table to delimit fields
 */
E 2

#include "defs.h"
#include "ext.h"

/*
 * choose funny characters to delimit fields
 */

/*
 * strings to pick the characters from
 */
static char *funny1 = {"\002\003\005\006\007!%&#/?,:;<=>@`^~_{}+-*ABCDEFGHIJKMNOPQRSTUVWXYZabcdefgjkoqrstwxyz"};
static char *funny2 = {"\002\003\005\006\007:_~^`@;,<=>#%&!/?{}+-*ABCDEFGHIJKMNOPQRSTUVWXZabcdefgjkoqrstuwxyz"};

choochar(){
	int had[128], ilin, icol, k;
	char *s;

	for(icol = 0; icol < 128; icol++)
		had[icol] = 0;
	F1 = F2 = 0;
	for(ilin = 0; ilin < nlin; ilin++){
		if(instead[ilin])
			continue;
		if(fullbot[ilin])
			continue;
		for(icol = 0; icol < ncol; icol++){
			k = ctype(ilin, icol);
			if(k == 0 || k == '-' || k == '=')
				continue;
			s = table[ilin][icol].col;
			if(point(s))
				while(*s)
					had[*s++] = 1;
			s = table[ilin][icol].rcol;
			if(point(s))
				while(*s)
					had[*s++] = 1;
		}
	}
	/*
	 * choose first funny character
	 */
	for(s = funny1; *s; s++){
		if(had[*s] == 0){
			F1 = *s;
			had[F1] = 1;
			break;
		}
	}
	/*
	 * choose second funny character
	 */
	for(s = funny2; *s; s++){
		if(had[*s] == 0){
			F2 = *s;
			break;
		}
	}
	if(F1 == 0 || F2 == 0)
		error("couldn't find characters to use for delimiters");
	return;
}

/*
 * Very Ugly!!
 * if s is not a character, we decide it is a pointer, so return true
 * 
 * (Need to check or we can replace it with
#define point	((s) >= 128 || (s) < 0)
 * or even isascii)
 */
point(s){
	return(s >= 128 || s < 0);
}
E 1
