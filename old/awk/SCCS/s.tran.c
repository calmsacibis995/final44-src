h17867
s 00001/00001/00260
d D 4.7 93/05/26 23:35:59 bostic 7 6
c isnumber used by <ctype.h> now
e
s 00009/00002/00252
d D 4.6 91/04/17 16:55:04 bostic 6 5
c new copyright; att/bsd/shared
e
s 00002/00002/00252
d D 4.5 87/10/22 10:03:11 bostic 5 4
c ANSI C; sprintf now returns an int.
e
s 00002/00002/00252
d D 4.4 83/12/09 11:49:36 ralph 4 3
c fix from Bill Shannon.
e
s 00003/00001/00251
d D 4.3 83/08/11 20:10:29 sam 3 2
c standardize keyword lines
e
s 00019/00012/00233
d D 4.2 83/02/09 14:07:30 sam 2 1
c merge from sun
e
s 00245/00000/00000
d D 4.1 82/05/07 19:25:16 mckusick 1 0
c date and time created 82/05/07 19:25:16 by mckusick
e
u
U
t
T
I 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 6
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
#ifndef lint
D 6
static char sccsid[] = "%W% %G%";
#endif
E 6
I 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6
E 3

#include "stdio.h"
#include "awk.def"
#include "awk.h"

cell *symtab[MAXSYM];	/* symbol table pointers */

char	**FS;	/* initial field sep */
char	**RS;	/* initial record sep */
char	**OFS;	/* output field sep */
char	**ORS;	/* output record sep */
char	**OFMT;	/*output format for numbers*/
awkfloat *NF;	/* number of fields in current record */
awkfloat *NR;	/* number of current record */
char	**FILENAME;	/* current filename argument */

cell	*recloc;	/* location of record */
cell	*nrloc;		/* NR */
cell	*nfloc;		/* NF */

syminit()
{
	setsymtab("0", tostring("0"), 0.0, NUM|STR|CON|FLD, symtab);
	/* this one is used for if(x)... tests: */
	setsymtab("$zero&null", tostring(""), 0.0, NUM|STR|CON|FLD, symtab);
	recloc = setsymtab("$record", record, 0.0, STR|FLD, symtab);
	dprintf("recloc %o lookup %o\n", recloc, lookup("$record", symtab, 0), NULL);
	FS = &setsymtab("FS", tostring(" "), 0.0, STR|FLD, symtab)->sval;
	RS = &setsymtab("RS", tostring("\n"), 0.0, STR|FLD, symtab)->sval;
	OFS = &setsymtab("OFS", tostring(" "), 0.0, STR|FLD, symtab)->sval;
	ORS = &setsymtab("ORS", tostring("\n"), 0.0, STR|FLD, symtab)->sval;
	OFMT = &setsymtab("OFMT", tostring("%.6g"), 0.0, STR|FLD, symtab)->sval;
D 2
	FILENAME = &setsymtab("FILENAME", NULL, 0.0, STR|FLD, symtab)->sval;
	nfloc = setsymtab("NF", NULL, 0.0, NUM, symtab);
E 2
I 2
	FILENAME = &setsymtab("FILENAME", EMPTY, 0.0, STR|FLD, symtab)->sval;
	nfloc = setsymtab("NF", EMPTY, 0.0, NUM, symtab);
E 2
	NF = &nfloc->fval;
D 2
	nrloc = setsymtab("NR", NULL, 0.0, NUM, symtab);
E 2
I 2
	nrloc = setsymtab("NR", EMPTY, 0.0, NUM, symtab);
E 2
	NR = &nrloc->fval;
}

cell **makesymtab()
{
	int i;
	cell **cp;

	cp = (cell **) malloc(MAXSYM * sizeof(cell *));
	if (cp == NULL)
		error(FATAL, "out of space in makesymtab");
	for (i = 0; i < MAXSYM; i++)
		cp[i] = 0;
	return(cp);
}

freesymtab(ap)	/* free symbol table */
cell *ap;
{
	cell *cp, **tp;
	int i;

	if (!(ap->tval & ARR))
		return;
	tp = (cell **) ap->sval;
	for (i = 0; i < MAXSYM; i++) {
		for (cp = tp[i]; cp != NULL; cp = cp->nextval) {
D 2
			xfree(cp->nval);
			xfree(cp->sval);
E 2
I 2
			strfree(cp->nval);
			strfree(cp->sval);
E 2
			free(cp);
		}
	}
	xfree(tp);
}

cell *setsymtab(n, s, f, t, tab)
char *n, *s;
awkfloat f;
unsigned t;
cell **tab;
{
	register h;
	register cell *p;
	cell *lookup();

	if (n != NULL && (p = lookup(n, tab, 0)) != NULL) {
D 2
		xfree(s);
E 2
I 2
		if (s != EMPTY ) xfree(s); /* careful here */
E 2
		dprintf("setsymtab found %o: %s", p, p->nval, NULL);
		dprintf(" %s %g %o\n", p->sval, p->fval, p->tval);
		return(p);
	}
	p = (cell *) malloc(sizeof(cell));
	if (p == NULL)
		error(FATAL, "symbol table overflow at %s", n);
	p->nval = tostring(n);
	p->sval = s;
	p->fval = f;
	p->tval = t;
	h = hash(n);
	p->nextval = tab[h];
	tab[h] = p;
	dprintf("setsymtab set %o: %s", p, p->nval, NULL);
	dprintf(" %s %g %o\n", p->sval, p->fval, p->tval);
	return(p);
}

hash(s)	/* form hash value for string s */
register unsigned char *s;
{
	register int hashval;

	for (hashval = 0; *s != '\0'; )
		hashval += *s++;
	return(hashval % MAXSYM);
}

cell *lookup(s, tab, flag)	/* look for s in tab, flag must match*/
register char *s;
cell **tab;
{
	register cell *p;

	for (p = tab[hash(s)]; p != NULL; p = p->nextval)
		if (strcmp(s, p->nval) == 0 &&
			(flag == 0 || flag == p->tval))
			return(p);	/* found it */
	return(NULL);	/* not found */
}

awkfloat setfval(vp, f)
register cell *vp;
awkfloat f;
{
	dprintf("setfval: %o %g\n", vp, f, NULL);
	checkval(vp);
	if (vp == recloc)
		error(FATAL, "can't set $0");
	vp->tval &= ~STR;	/* mark string invalid */
	vp->tval |= NUM;	/* mark number ok */
D 4
	if ((vp->tval & FLD) && vp->nval == 0)
E 4
I 4
	if ((vp->tval & FLD) && isnull(vp->nval))
E 4
		donerec = 0;
	return(vp->fval = f);
}

char *setsval(vp, s)
register cell *vp;
char *s;
{
	dprintf("setsval: %o %s\n", vp, s, NULL);
	checkval(vp);
	if (vp == recloc)
		error(FATAL, "can't set $0");
	vp->tval &= ~NUM;
	vp->tval |= STR;
D 4
	if ((vp->tval & FLD) && vp->nval == 0)
E 4
I 4
	if ((vp->tval & FLD) && isnull(vp->nval))
E 4
		donerec = 0;
	if (!(vp->tval&FLD))
D 2
		xfree(vp->sval);
E 2
I 2
		strfree(vp->sval);
E 2
	vp->tval &= ~FLD;
	return(vp->sval = tostring(s));
}

awkfloat getfval(vp)
register cell *vp;
{

	if (vp->sval == record && donerec == 0)
		recbld();
	dprintf("getfval: %o", vp, NULL, NULL);
	checkval(vp);
	if ((vp->tval & NUM) == 0) {
		/* the problem is to make non-numeric things */
		/* have unlikely numeric variables, so that */
		/* $1 == $2 comparisons sort of make sense when */
		/* one or the other is numeric */
D 7
		if (isnumber(vp->sval)) {
E 7
I 7
		if (isanumber(vp->sval)) {
E 7
			vp->fval = atof(vp->sval);
			if (!(vp->tval & CON))	/* don't change type of a constant */
				vp->tval |= NUM;
		}
		else
			vp->fval = 0.0;	/* not a very good idea */
	}
	dprintf("  %g\n", vp->fval, NULL, NULL);
	return(vp->fval);
}

char *getsval(vp)
register cell *vp;
{
	char s[100];

	if (vp->sval == record && donerec == 0)
		recbld();
	dprintf("getsval: %o", vp, NULL, NULL);
	checkval(vp);
	if ((vp->tval & STR) == 0) {
		if (!(vp->tval&FLD))
D 2
			xfree(vp->sval);
E 2
I 2
			strfree(vp->sval);
E 2
		if ((long)vp->fval==vp->fval)
D 5
			sprintf(s, "%.20g", vp->fval);
E 5
I 5
			(void)sprintf(s, "%.20g", vp->fval);
E 5
		else
D 5
			sprintf(s, *OFMT, vp->fval);
E 5
I 5
			(void)sprintf(s, *OFMT, vp->fval);
E 5
		vp->sval = tostring(s);
		vp->tval &= ~FLD;
		vp->tval |= STR;
	}
	dprintf("  %s\n", vp->sval, NULL, NULL);
	return(vp->sval);
}

checkval(vp)
register cell *vp;
{
	if (vp->tval & ARR)
		error(FATAL, "illegal reference to array %s", vp->nval);
	if ((vp->tval & (NUM | STR)) == 0)
		error(FATAL, "funny variable %o: %s %s %g %o", vp, vp->nval,
			vp->sval, vp->fval, vp->tval);
}

char *tostring(s)
register char *s;
{
	register char *p;

D 2
	p = malloc(strlen(s)+1);
	if (p == NULL)
		error(FATAL, "out of space in tostring on %s", s);
	strcpy(p, s);
E 2
I 2
	if (s==NULL){
		p = malloc(1);
		if (p == NULL)
			error(FATAL, "out of space in tostring on %s", s);
		*p = '\0';
	} else {
		p = malloc(strlen(s)+1);
		if (p == NULL)
			error(FATAL, "out of space in tostring on %s", s);
		strcpy(p, s);
	}
E 2
	return(p);
}
#ifndef yfree
yfree(a) char *a;
{
	printf("%o\n", a);
	free(a);
}
#endif
#ifdef malloc
#undef malloc
char *ymalloc(u) unsigned u;
{	char *p;
	p = malloc(u);
	printf("%o %o\n", u, p);
	return(p);
}
#endif
E 1
