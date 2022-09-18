h27576
s 00000/00000/00202
d D 1.4 93/07/27 09:16:27 bostic 4 3
c checkpoint; Mike Karels left this checked out.
e
s 00007/00019/00195
d D 1.3 87/12/01 00:38:57 jaap 3 2
c Andries fixed the linedrawing, at least he says so
e
s 00003/00002/00211
d D 1.2 85/10/02 14:39:40 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00213/00000/00000
d D 1.1 85/10/01 18:09:30 jaap 1 0
c date and time created 85/10/01 18:09:30 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% (CWI) %E%";
E 3
I 3
static char sccsid[] = "@(#)vertlines.c	1.2 (CWI) 85/10/02";
E 3
#endif lint

D 2

 /* tv.c: draw vertical lines */
E 2
I 2
/*
 * draw vertical lines
 */
E 2

#include "defs.h"
#include "ext.h"

drawvert(start, end, c, lwid){
	char *exb = 0, *ext = 0;
	int tp = 0, sl, ln, pos, epb, ept, vm;

	end++;
	vm = 'v';
	/*
	 * note: nr 35 has value of 1m outside of linesize
	 */
	while(instead[end])
		end++;
	for(ln = 0; ln < lwid; ln++){
		epb = ept = 0;
		pos = 2 * ln - lwid + 1;
		if(pos != tp)
			printf("\\h'%dp'", pos - tp);
		tp = pos;
		if(end < nlin){
			if(fullbot[end] || (!instead[end] && allh(end)))
				epb = 2;
			else {
				switch(midbar(end, c)){

				case '-': 
					exb = "1v-.5m";
					break;
				case '=': 
					exb = "1v-.5m";
					epb = 1;
					break;
				}
			}
		}
		if(lwid > 1){
			switch(interh(end, c)){

			case THRU: 
				epb -= 1;
				break;
			case RIGHT: 
				epb += (ln == 0 ? 1 : -1);
				break;
			case LEFT: 
				epb += (ln == 1 ? 1 : -1);
				break;
			}
		}
		if(lwid == 1){
			switch(interh(end, c)){

			case THRU: 
				epb -= 1;
				break;
			case RIGHT: 
			case LEFT: 
				epb += 1;
				break;
			}
		}
		if(start > 0){
			sl = start - 1;
			while(sl >= 0 && instead[sl])
				sl--;
			if(sl >= 0 && (fullbot[sl] || allh(sl)))
				ept = 0;
			else {
				if(sl >= 0){
					switch(midbar(sl, c)){

					case '-': 
						ext = ".5m";
						break;
					case '=': 
						ext = ".5m";
						ept = -1;
						break;
					default: 
						vm = 'm';
						break;
					}
				} else
					ept = -4;
			}
		} else {
			if(start == 0 && allh(0)){
				ept = 0;
				vm = 'm';
			}
		}
		if(lwid > 1){
			switch(interh(start, c)){

			case THRU: 
				ept += 1;
				break;
			case LEFT: 
				ept += (ln == 0 ? 1 : -1);
				break;
			case RIGHT: 
				ept += (ln == 1 ? 1 : -1);
				break;
			}
		} else {
			if(lwid == 1){
				switch(interh(start, c)){

				case THRU: 
					ept += 1;
					break;
				case LEFT: 
				case RIGHT: 
					ept -= 1;
					break;
				}
			}
		}
		if(exb)
			printf("\\v'%s'", exb);
		if(epb)
			printf("\\v'%dp'", epb);
		printf("\\s\\n(%d", LSIZE);
D 3
		if(linsize)
			printf("\\v'-\\n(%dp/6u'", LSIZE);
 		/*
		 * adjustment for T450 nroff boxes
		 *
		 * Changed by JNA, the register #~ will contain in general
		 * the device dependency adjustment for vertical lines
		 */
		printf("\\h'-\\n(#~u'");
		/*
		 * Extra corrections for double lines
		 * Works OK on the HARRIS, probably needed for all devices
		 */
		if(device == HARRIS && ln == 1)
			printf("\\h'-\\n(#~u'");
E 3
I 3
		printf("\\v'-\\n(%dp/6u'", LSIZE);
		printf("\\h'-\\n(#~n/100u'");
E 3
		
		printf("\\L'|\\n(#%cu-%s",
			linestop[start] + 'a' -1, vm == 'v' ? "1v" : "\\n(35u");
		if(ext)
			printf("-(%s)", ext);
		if(exb)
			printf("-(%s)", exb);
		pos = ept - epb;
		if(pos)
			printf("%s%dp", pos >= 0 ? "+" : "", pos);
I 3
		printf("'");
E 3
		/*
		 * the string #d is either "nl" or ".d" depending on diversions;
	   	 * on GCOS not the same
		 */
D 3
		printf("'\\s0\\v'\\n(\\*(#du-\\n(#%cu+%s",
E 3
I 3
		printf("\\h'-\\n(#~n/100u'");
		printf("\\s0\\v'\\n(\\*(#du-\\n(#%cu+%s",
E 3
			linestop[start] + 'a' -1, vm == 'v' ? "1v" : "\\n(35u");
		if(ext)
			printf("+%s", ext);
		if(ept)
			printf("%s%dp", (-ept) > 0 ? "+" : "", (-ept));
		printf("'");
D 3
		if(linsize)
			printf("\\v'\\n(%dp/6u'", LSIZE);
E 3
I 3
		printf("\\v'\\n(%dp/6u'", LSIZE);
E 3
	}
}

midbar(i, c){
	int k;

	k = midbcol(i, c);
	if(k == 0 && c > 0)
		k = midbcol(i, c - 1);
	return(k);
}

midbcol(i, c){
	int ct;

	while((ct = ctype(i, c)) == 's')
		c--;
	if(ct == '-' || ct == '=')
		return(ct);
	if(ct = barent(table[i][c].col))
		return(ct);
	return(0);
}

barent(s)
char *s;
{
	if(s == 0)
		return(1);
	if(!point(s))
		return(1);
	if(s[0] == '\\')
		s++;
	if(s[1] != 0)
		return(0);
	switch(s[0]){

	case '_': 
		return('-');
	case '=': 
		return('=');
	}
	return(0);
}
E 1
