h24973
s 00001/00001/00284
d D 1.3 93/07/27 09:16:26 bostic 3 2
c checkpoint; Mike Karels left this checked out.
e
s 00032/00044/00253
d D 1.2 85/10/02 14:38:49 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00297/00000/00000
d D 1.1 85/10/01 18:09:17 jaap 1 0
c date and time created 85/10/01 18:09:17 by jaap
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
 /* t5.c: read data for table */
E 2
I 2
/*
 * read data for table
 */
E 2

#include "defs.h"
#include "ext.h"
#include <signal.h>

gettbl(){
	int icol, ch;
	extern interr();
	extern char *chspace();
	extern char *maknew();
	extern int *alocv();
	extern char *gettext();
D 3
	int (*savsign)();
E 3
I 3
	sig_t savsign;
E 3

	cstore = cspace = chspace();
	textflg = 0;
	for(nlin = nslin = 0; gets1(cstore); nlin++){
		stynum[nlin] = nslin;
		if(prefix(".TE", cstore)){
			leftover = 0;
			break;
		}
		if(prefix(".TC", cstore) || prefix(".T&", cstore)){
			readspec();
			nslin++;
		}
		if(nlin >= MAXLIN){
			leftover = (int)cstore;
			break;
		}
		fullbot[nlin] = 0;
		if(cstore[0] == '.' && !isdigit(cstore[1])){
			instead[nlin] = cstore;
			while(*cstore++)
				;
D 2
/*
printf( ".\\\" gettbl continue (cstore[0] == '.', && !isdigit(ctore[1])\n");
*/
E 2
			continue;
		} else
			instead[nlin] = 0;
		if(nodata(nlin)){
			if(ch = oneh(nlin))
				fullbot[nlin] = ch;
#ifdef FIX
	This FIX didn't work, so commented out for the time being,
	problem temporarily solved with signal catching...
D 2
printf(".\\\" FIX nlin = %d\n", nlin);
printf(".\\\" FIXgettbl: alocv %d\n", (ncol + 2) * sizeof(table[0][0]));
E 2
I 2
dprint(".\\\" FIX nlin = %d\n", nlin);
dprint(".\\\" FIXgettbl: alocv %d\n", (ncol + 2) * sizeof(table[0][0]));
E 2
			/*
			 * start of FIX?
			 *
			 * Need to allocate pointers as well, in case
			 * of vertical spanning.
			 * I hope this works
			 */
			table[nlin] = (struct colstr *) alocv((ncol + 2) *
							sizeof(*table[0]));
			/*
			 * Does alocv clears the pointers?
			 */
		{	int tmp;
			for( tmp = 0; tmp < ncol +2; tmp++) {
		table[nlin][tmp].col = "";
		table[nlin][tmp].rcol = (char*)0;
printf(".\\\"FIX table[%d][%d].col: <%s>\n", nlin, tmp, table[nlin][tmp].col);
printf(".\\\"FIX table[%d][%d].rcol: <%s>\n", nlin, tmp, table[nlin][tmp].rcol);
			}
		}
			/*
			 * End of FIX
			 */
#endif FIX
			nlin++;
			nslin++;
			instead[nlin] = (char *) 0;
			fullbot[nlin] = 0;
D 2
printf(".\\\" gettbl continue, due to nodata\n");
E 2
I 2
dprint(".\\\" gettbl continue, due to nodata\n");
E 2
		}
D 2
/*
printf(".\\\"gettbl: alocv %d\n", (ncol + 2) * sizeof(table[0][0]));
*/
E 2
		table[nlin] = (struct colstr *) alocv((ncol + 2) *
							sizeof(*table[0]));
		if(cstore[1] == 0) {
			switch(cstore[0]){

			case '_': 
				fullbot[nlin] = '-';
				continue;
			case '=': 
				fullbot[nlin] = '=';
				continue;
			}
		}
		stynum[nlin] = nslin;
		nslin = min(nslin + 1, nclin - 1);
		for(icol = 0; icol < ncol; icol++){
			table[nlin][icol].col = cstore;
			table[nlin][icol].rcol = (char*)0;
			ch = 1;
			if(strcmp(cstore, "T{") == 0) {
				/*
				 * text follows
				 */
				table[nlin][icol].col =
						gettext(cstore, nlin, icol,
						font[stynum[nlin]][icol],
						csize[stynum[nlin]][icol]);
D 2
/*
printf(".\\\" found T{, gettext returns table[%d][%d].col: <%s>\n",
			nlin, icol, table[nlin][icol]);
*/
E 2
			} else {
				for(; (ch = *cstore) != '\0' && ch != tab; cstore++)
					;
				*cstore++ = '\0';
				switch(ctype(nlin, icol)){
 					/*
					 * numerical or alpha, subcol
					 */
				case 'n': 
					table[nlin][icol].rcol = maknew(table[nlin][icol].col);
					break;
				case 'a': 
					table[nlin][icol].rcol = table[nlin][icol].col;
					table[nlin][icol].col = "";
					break;
				}
D 2
/*
printf(".\\\" gettbl: table[%d][%d].col is <%s>\n", nlin, icol, table[nlin][icol].col);
printf(".\\\" gettbl: table[%d][%d].rcol is <%s>\n", nlin, icol, table[nlin][icol].rcol);
*/
E 2
			}
			while(ctype(nlin, icol + 1) == 's'){
				/*
				 * spanning
				 */
				table[nlin][++icol].col = "";
			}
			if(ch == '\0')
				break;
		}
		while(++icol < ncol + 2){
			table[nlin][icol].col = "";
			table[nlin][icol].rcol = (char*)0;
		}
		while(*cstore != '\0')
			cstore++;
		if(cstore - cspace > MAXCHS)
			cstore = cspace = chspace();
	}
	last = cstore;
I 2
	/*
	 * the next example is weird & legal tbl input.
	 * however, it generates a bus error.
.TS
linesize(24) tab(@);
ct| c cf3
^ | _ _
^ | cf3 cf3
^ | c s.
0,0@0,1@0,2
@1,1@1,2
@2,1@2,2
.TE
	 * This works:
.TS
linesize(24) tab(@);
ct| c cf3
^ | cf3 cf3
^ | c s.
0,0@0,1@0,2
@1,1@1,2
@2,1@2,2
.TE
	 * So it is the vertical spanning of an empty column which
	 * cuases problems
	 */
E 2
	savsign = signal(SIGBUS, interr);
	permute();
	signal(SIGBUS, savsign);
	if(textflg)
		untext();
	return;
}

/*
 * return 1 if no type of column specified for this line
 */
nodata(il){
	int c;

	for(c = 0; c < ncol; c++){
		switch(ctype(il, c)){

		case 'c': 
		case 'n': 
		case 'r': 
		case 'l': 
		case 's': 
		case 'a': 
			return(0);
		}
	}
	return(1);
}

/*
 * returns the type of heading if they are all the same for the table
 * line?
 */
oneh(lin){
	int k, icol;

	k = ctype(lin, 0);
	for(icol = 1; icol < ncol; icol++){
		if(k != ctype(lin, icol))
			return(0);
	}
	return(k);
}

#define SPAN "\\^"

permute(){
	register int irow, jcol, is;
	char *start, *strig;

	for(jcol = 0; jcol < ncol; jcol++){
		for(irow = 1; irow < nlin; irow++){
			if(vspand(irow, jcol, 0)){
				is = prev(irow);
				if(is < 0)
					error("Vertical spanning in first row not allowed");
				start = table[is][jcol].col;
				strig = table[is][jcol].rcol;
D 2
/*
printf(".\\\"Permute -- jcol: %d, irow: %d, is: %d\n", jcol, irow, is);
printf(".\\\"start: <%s> strig: <%s>\n", start, strig);
printf(".\\\"is: %d\n",is);

printf(".\\\"table[(is =)%d][%d].col: <%s>\n", is, jcol, table[is][jcol].col);

printf(".\\\"table[(is =)%d][%d].rcol: <%s>\n", is, jcol, table[is][jcol].rcol);
*/
E 2
				while(irow < nlin && vspand(irow, jcol, 0)){
D 2
/*
printf(".\\\"vspand && irow: %d < nlin: %d\n", irow, nlin);
*/
E 2
					irow++;
				}
				table[--irow][jcol].col = start;
D 2
/*
printf(".\\\"irow: %d\n", irow);
*/
E 2
				table[irow][jcol].rcol = strig;
				while(is < irow){
D 2
/*
printf(".\\\"table[(is =)%d][%d].col: <%s>\n", is, jcol, table[is][jcol].col);
printf(".\\\"table[(is =)%d][%d].rcol: <%s>\n", is, jcol, table[is][jcol].rcol);
*/
E 2
					table[is][jcol].col = SPAN;
					table[is][jcol].rcol = (char*)0;
D 2
/*
printf(".\\\"table[(is =)%d][%d].col becomes: <%s>\n", is, jcol, table[is][jcol].col);
printf(".\\\"table[(is =)%d][%d].rcol becomes: <%s>\n", is, jcol, table[is][jcol].rcol);
*/
E 2
					is = next(is);
D 2
/*
printf(".\\\"is: %d\n",is);
*/
E 2
				}
			}
		}
	}
}

/*
 * return 1 if vertical spanning is row ir, column ij, from position ifrom
 */
vspand(ir, ij, ifform)
{
	if(ir < 0)
		return(0);
	if(ir >= nlin)
		return(0);
	if(instead[ir])
		return(0);
	if(ifform == 0 && ctype(ir, ij) == '^'){
		return(1);
	}
	if(table[ir][ij].rcol != (char*)0)
		return(0);
	if(fullbot[ir])
		return(0);
	return(vspen(table[ir][ij].col));
}

/*
 * return 1 if the string is the same as SPAN
 */
vspen(s)
char   *s;
{
	if(s == 0)
		return(0);
	if(!point(s))
		return(0);
	return(strcmp(s, SPAN) == 0);
}

static
interr()
{
	error("internal tbl error -- function: permute");
}
E 1
