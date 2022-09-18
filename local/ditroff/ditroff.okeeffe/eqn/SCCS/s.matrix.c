h36401
s 00002/00001/00082
d D 2.2 87/04/01 15:18:01 jaap 3 2
c Updates from bwk, see README for details
e
s 00049/00031/00034
d D 2.1 85/07/18 18:08:57 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00065/00000/00000
d D 1.1 85/03/01 15:27:05 jaap 1 0
c date and time created 85/03/01 15:27:05 by jaap
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
#include "e.h"

D 2
column(type, p1) int type, p1; {
	int i;
E 2
I 2
startcol(type)	/* mark start of column in lp[] array */
	int type;
{
	int oct = ct;
E 2

D 2
	lp[p1] = ct - p1 - 1;
	if( dbg ){
E 2
I 2
	lp[ct++] = type;
	lp[ct++] = 0;	/* count, to come */
	lp[ct++] = 0;	/* separation, to come */
	return oct;
}

column(oct, sep)	/* remember end of column that started at lp[oct] */
	int oct, sep;
{
	int i, type;

	lp[oct+1] = ct - oct - 3;
	lp[oct+2] = sep;
	type = lp[oct];
	if (dbg) {
E 2
		printf(".\t%d column of", type);
D 2
		for( i=p1+1; i<ct; i++ )
E 2
I 2
		for (i = oct+3; i < ct; i++ )
E 2
			printf(" S%d", lp[i]);
D 2
		printf(", rows=%d\n",lp[p1]);
E 2
I 2
		printf(", rows=%d, sep=%d\n", lp[oct+1], lp[oct+2]);
E 2
	}
D 2
	lp[ct++] = type;
E 2
}

D 2
matrix(p1) int p1; {
	int nrow, ncol, i, j, k, hb, b, val[100];
E 2
I 2
matrix(oct)	/* matrix is list of columns */
	int oct;
{
	int nrow, ncol, i, j, k, val[100];
	float b, hb;
E 2
	char *space;
I 3
	extern char *Matspace;
E 3

D 2
	space = "\\ \\ ";
	nrow = lp[p1];	/* disaster if rows inconsistent */
E 2
I 2
D 3
	space = "\\ \\ ";	/* between columns of matrix */
E 3
I 3
	space = Matspace;	/* between columns of matrix */
E 3
	nrow = lp[oct+1];	/* disaster if rows inconsistent */
				/* also assumes just columns */
				/* fix when add other things */
E 2
	ncol = 0;
D 2
	for( i=p1; i<ct; i += lp[i]+2 ){
E 2
I 2
	for (i = oct+1; i < ct; i += lp[i]+3 ) {
E 2
		ncol++;
D 2
		if(dbg)printf(".\tcolct=%d\n",lp[i]);
E 2
I 2
		dprintf(".\tcolct=%d\n", lp[i]);
E 2
	}
D 2
	for( k=1; k<=nrow; k++ ) {
E 2
I 2
	for (k=1; k <= nrow; k++) {
E 2
		hb = b = 0;
D 2
		j = p1 + k;
		for( i=0; i<ncol; i++ ) {
E 2
I 2
		j = oct + k + 2;
		for (i=0; i < ncol; i++) {
E 2
			hb = max(hb, eht[lp[j]]-ebase[lp[j]]);
			b = max(b, ebase[lp[j]]);
D 2
			j += nrow + 2;
E 2
I 2
			j += nrow + 3;
E 2
		}
D 2
		if(dbg)printf(".\trow %d: b=%d, hb=%d\n", k, b, hb);
		j = p1 + k;
		for( i=0; i<ncol; i++ ) {
E 2
I 2
		dprintf(".\trow %d: b=%g, hb=%g\n", k, b, hb);
		j = oct + k + 2;
		for (i=0; i<ncol; i++) {
E 2
			ebase[lp[j]] = b;
			eht[lp[j]] = b + hb;
D 2
			j += nrow + 2;
E 2
I 2
			j += nrow + 3;
E 2
		}
	}
D 2
	j = p1;
	for( i=0; i<ncol; i++ ) {
		lpile(lp[j+lp[j]+1], j+1, j+lp[j]+1);
E 2
I 2
	j = oct;
	for (i=0; i<ncol; i++) {
		pile(j);
E 2
		val[i] = yyval;
D 2
		j += nrow + 2;
E 2
I 2
		j += nrow + 3;
E 2
	}
D 2
	yyval = oalloc();
E 2
I 2
	yyval = salloc();
E 2
	eht[yyval] = eht[val[0]];
	ebase[yyval] = ebase[val[0]];
	lfont[yyval] = rfont[yyval] = 0;
D 2
	if(dbg)printf(".\tmatrix S%d: r=%d, c=%d, h=%d, b=%d\n",
E 2
I 2
	dprintf(".\tmatrix S%d: r=%d, c=%d, h=%g, b=%g\n",
E 2
		yyval,nrow,ncol,eht[yyval],ebase[yyval]);
	printf(".ds %d \"", yyval);
	for( i=0; i<ncol; i++ )  {
		printf("\\*(%d%s", val[i], i==ncol-1 ? "" : space);
D 2
		ofree(val[i]);
E 2
I 2
		sfree(val[i]);
E 2
	}
	printf("\n");
D 2
	ct = p1;
E 2
}
E 1
