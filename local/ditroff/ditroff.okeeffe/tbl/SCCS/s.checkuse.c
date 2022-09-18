h46515
s 00003/00003/00102
d D 1.3 93/07/27 09:16:19 bostic 3 2
c checkpoint; Mike Karels left this checked out.
e
s 00003/00001/00102
d D 1.2 85/10/02 14:36:38 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00103/00000/00000
d D 1.1 85/10/01 18:08:43 jaap 1 0
c date and time created 85/10/01 18:08:43 by jaap
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
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
#endif lint


D 2
 /* tb.c: check which entries exist, also storage allocation */
E 2
I 2
/*
 * check which entries exist, also storage allocation
 */
E 2

#include "defs.h"
#include "ext.h"

checkuse()
{
	register int i, c, k;

	for(c = 0; c < ncol; c++){
		used[c] = lused[c] = rused[c] = 0;
		for(i = 0; i < nlin; i++){
			if(instead[i] || fullbot[i])
				continue;
			k = ctype(i, c);
			if(k == '-' || k == '=')
				continue;
			if((k == 'n' || k == 'a')){
				rused[c] |= real(table[i][c].rcol);
				if(!real(table[i][c].rcol))
					used[c] |= real(table[i][c].col);
				if(table[i][c].rcol)
					lused[c] |= real(table[i][c].col);
			} else
				used[c] |= real(table[i][c].col);
		}
	}
}

real(s)
char *s;
{
	if(s == 0)
		return(0);
	if(!point(s))
		return(1);
	if(*s == 0)
		return(0);
	return(1);
}

D 3
#define MAXVEC 20
E 3
I 3
#define MAXVEC 128
E 3

static int spcount = 0;
extern char *calloc();
static char *spvecs[MAXVEC];

char *
chspace()
{
	register char *pp;

	if(spvecs[spcount])
		return(spvecs[spcount++]);
	if(spcount >= MAXVEC)
		error("Too many characters in table");
	spvecs[spcount++] = pp = calloc(MAXCHS + 200, 1);
	if(pp == (char *) -1 || pp ==  (char *) 0)
		error("no space for characters");
	return(pp);
}

D 3
#define MAXPC 50
E 3
I 3
#define MAXPC 256
E 3

static char *thisvec;
static int tpcount = -1;
static char *tpvecs[MAXPC];

int *
alocv(n)
{
	register int *tp, *q;
	if(tpcount < 0 || thisvec + n > tpvecs[tpcount] + MAXCHS){
		tpcount++;
		if(tpvecs[tpcount] == 0){
			tpvecs[tpcount] = calloc(MAXCHS, 1);
		}
		thisvec = tpvecs[tpcount];
		if(thisvec == (char *) -1)
			error("no space for vectors");
	}
	tp = (int *)thisvec;
	thisvec += n;
	for(q = tp; q < (int *)thisvec; q++)
		*q = 0;
	return(tp);
}

release(){
	extern char *exstore;

	/*
	 * give back unwanted space in some vectors
	 */
	spcount = 0;
	tpcount = -1;
	exstore = 0;
}
E 1
