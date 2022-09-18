h09706
s 00003/00003/00324
d D 4.11 93/05/26 23:35:57 bostic 12 11
c isnumber used by <ctype.h> now
e
s 00017/00001/00310
d D 4.10 93/03/01 12:53:04 torek 11 10
c clean up / prototype varargs function
e
s 00008/00001/00303
d D 4.9 91/04/17 16:54:59 bostic 10 9
c new copyright; att/bsd/shared
e
s 00014/00006/00290
d D 4.8 91/03/01 13:45:20 bostic 9 8
c ANSI
e
s 00002/00001/00294
d D 4.7 90/06/25 14:31:08 bostic 8 7
c new versions from Vern Paxson, for flex
e
s 00008/00003/00287
d D 4.6 87/10/06 22:09:39 bostic 7 5
c '-' means stdin fix; bug report 4.3BSD/bin/86
e
s 00007/00002/00288
d R 4.6 87/10/06 22:08:39 bostic 6 5
c  '-' means stdin fix; bug report 4.3BSD/bin/86
e
s 00010/00008/00280
d D 4.5 87/05/06 19:25:43 bostic 5 4
c bug report 4.3BSD/bin/35
e
s 00001/00001/00287
d D 4.4 84/09/17 08:34:36 ralph 4 3
c watch for NULL pointer.
e
s 00003/00001/00285
d D 4.3 83/08/11 20:09:38 sam 3 2
c standardize keyword lines
e
s 00008/00005/00278
d D 4.2 83/02/09 14:07:08 sam 2 1
c merge from sun
e
s 00283/00000/00000
d D 4.1 82/05/07 19:24:15 mckusick 1 0
c date and time created 82/05/07 19:24:15 by mckusick
e
u
U
t
T
I 10
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 10
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
#ifndef lint
D 5
static char sccsid[] = "%W% %G%";
E 5
I 5
D 7
static char sccsid[] = "@(#)lib.c	4.4 9/17/84";
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
E 7
E 5
D 10
#endif
E 10
I 10
#endif /* not lint */
E 10
E 3

I 11
#ifdef __STDC__
E 11
I 9
#include <stdarg.h>
I 11
#else
#include <varargs.h>
#endif
E 11
E 9
#include "stdio.h"
#include "awk.def"
#include "awk.h"
#include "ctype.h"

I 11
int	error __P((int, const char *, ...));

E 11
I 7
extern FILE	*yyin;	/* lex input file */
I 8
extern char	*lexprog;	/* points to program argument if it exists */
E 8
E 7
FILE	*infile	= NULL;
char	*file;
#define	RECSIZE	(5 * 512)
char	record[RECSIZE];
char	fields[RECSIZE];
I 2
char	EMPTY[] = "";
E 2

#define	MAXFLD	100
int	donefld;	/* 1 = implies rec broken into fields */
int	donerec;	/* 1 = record is valid (no flds have changed) */
int	mustfld;	/* 1 = NF seen, so always break*/

D 2
#define	FINIT	{0, NULL, 0.0, FLD|STR}
E 2
I 2
#define	FINIT	{EMPTY, EMPTY, 0.0, FLD|STR}
E 2
cell fldtab[MAXFLD] = {	/*room for fields */
	{ "$record", record, 0.0, STR|FLD},
D 5
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT
E 5
I 5
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
	FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT, FINIT,
E 5
};
int	maxfld	= 0;	/* last used field */


getrec()
{
	register char *rr;
	extern int svargc;
	extern char **svargv;
	register c, sep;

	dprintf("**RS=%o, **FS=%o\n", **RS, **FS, NULL);
	donefld = 0;
	donerec = 1;
	record[0] = 0;
	while (svargc > 0) {
		dprintf("svargc=%d, *svargv=%s\n", svargc, *svargv, NULL);
		if (infile == NULL) {	/* have to open a new file */
			if (member('=', *svargv)) {	/* it's a var=value argument */
				setclvar(*svargv);
				svargv++;
				svargc--;
				continue;
			}
			*FILENAME = file = *svargv;
			dprintf("opening file %s\n", file, NULL, NULL);
D 7
			if (*file == '-')
				infile = stdin;
E 7
I 7
			if (*file == '-') {
D 8
				if (yyin == stdin)
E 8
I 8
				if (yyin == stdin && ! lexprog)
E 8
					error(FATAL, "standard input already used for reading commands");
				else
					infile = stdin;
			}
E 7
			else if ((infile = fopen(file, "r")) == NULL)
				error(FATAL, "can't open %s", file);
		}
		if ((sep = **RS) == 0)
			sep = '\n';
		for (rr = record; ; ) {
			for (; (c=getc(infile)) != sep && c != EOF; *rr++ = c)
				;
			if (**RS == sep || c == EOF)
				break;
			if ((c = getc(infile)) == '\n' || c == EOF)	/* 2 in a row */
				break;
			*rr++ = '\n';
			*rr++ = c;
		}
		if (rr > record+RECSIZE)
			error(FATAL, "record `%.20s...' too long", record);
		*rr = 0;
		if (mustfld)
			fldbld();
		if (c != EOF || rr > record) {	/* normal record */
			recloc->tval &= ~NUM;
			recloc->tval |= STR;
			++nrloc->fval;
			nrloc->tval &= ~STR;
			nrloc->tval |= NUM;
			return(1);
		}
		/* EOF arrived on this file; set up next */
		if (infile != stdin)
			fclose(infile);
		infile = NULL;
		svargc--;
		svargv++;
	}
	return(0);	/* true end of file */
}

setclvar(s)	/* set var=value from s */
char *s;
{
	char *p;
	cell *q;

	for (p=s; *p != '='; p++)
		;
	*p++ = 0;
	q = setsymtab(s, tostring(p), 0.0, STR, symtab);
	setsval(q, p);
	dprintf("command line set %s to |%s|\n", s, p, NULL);
}

fldbld()
{
	register char *r, *fr, sep;
	int i, j;

	r = record;
	fr = fields;
	i = 0;	/* number of fields accumulated here */
	if ((sep = **FS) == ' ')
		for (i = 0; ; ) {
			while (*r == ' ' || *r == '\t' || *r == '\n')
				r++;
			if (*r == 0)
				break;
			i++;
			if (i >= MAXFLD)
				error(FATAL, "record `%.20s...' has too many fields", record);
			if (!(fldtab[i].tval&FLD))
D 2
				xfree(fldtab[i].sval);
E 2
I 2
				strfree(fldtab[i].sval);
E 2
			fldtab[i].sval = fr;
			fldtab[i].tval = FLD | STR;
			do
				*fr++ = *r++;
			while (*r != ' ' && *r != '\t' && *r != '\n' && *r != '\0');
			*fr++ = 0;
		}
	else if (*r != 0)	/* if 0, it's a null field */
		for (;;) {
			i++;
			if (i >= MAXFLD)
				error(FATAL, "record `%.20s...' has too many fields", record);
			if (!(fldtab[i].tval&FLD))
D 2
				xfree(fldtab[i].sval);
E 2
I 2
				strfree(fldtab[i].sval);
E 2
			fldtab[i].sval = fr;
			fldtab[i].tval = FLD | STR;
			while (*r != sep && *r != '\n' && *r != '\0')	/* \n always a separator */
				*fr++ = *r++;
			*fr++ = 0;
			if (*r++ == 0)
				break;
		}
	*fr = 0;
	for (j=MAXFLD-1; j>i; j--) {	/* clean out junk from previous record */
		if (!(fldtab[j].tval&FLD))
D 2
			xfree(fldtab[j].sval);
E 2
I 2
			strfree(fldtab[j].sval);
E 2
		fldtab[j].tval = STR | FLD;
D 2
		fldtab[j].sval = NULL;
E 2
I 2
		fldtab[j].sval = EMPTY;
E 2
	}
	maxfld = i;
	donefld = 1;
	for(i=1; i<=maxfld; i++)
D 12
		if(isnumber(fldtab[i].sval)) {
E 12
I 12
		if(isanumber(fldtab[i].sval)) {
E 12
			fldtab[i].fval = atof(fldtab[i].sval);
			fldtab[i].tval |= NUM;
		}
	setfval(lookup("NF", symtab, 0), (awkfloat) maxfld);
	if (dbg)
		for (i = 0; i <= maxfld; i++)
			printf("field %d: |%s|\n", i, fldtab[i].sval);
}

recbld()
{
	int i;
	register char *r, *p;

	if (donefld == 0 || donerec == 1)
		return;
	r = record;
	for (i = 1; i <= *NF; i++) {
		p = getsval(&fldtab[i]);
		while (*r++ = *p++)
			;
		*(r-1) = **OFS;
	}
	*(r-1) = '\0';
	dprintf("in recbld FS=%o, recloc=%o\n", **FS, recloc, NULL);
	recloc->tval = STR | FLD;
	dprintf("in recbld FS=%o, recloc=%o\n", **FS, recloc, NULL);
	if (r > record+RECSIZE)
		error(FATAL, "built giant record `%.20s...'", record);
	dprintf("recbld = |%s|\n", record, NULL, NULL);
}

cell *fieldadr(n)
{
	if (n >= MAXFLD)
		error(FATAL, "trying to access field %d", n);
	return(&fldtab[n]);
}

int	errorflag	= 0;

yyerror(s) char *s; {
	fprintf(stderr, "awk: %s near line %d\n", s, lineno);
	errorflag = 2;
}

D 9
error(f, s, a1, a2, a3, a4, a5, a6, a7) {
	fprintf(stderr, "awk: ");
	fprintf(stderr, s, a1, a2, a3, a4, a5, a6, a7);
	fprintf(stderr, "\n");
E 9
I 9
D 11
error(isfatal, fmt)
E 11
I 11
int
#ifdef __STDC__
error(int isfatal, const char *fmt, ...)
#else
error(isfatal, fmt, va_alist)
E 11
	int isfatal;
	char *fmt;
I 11
	va_dcl
#endif
E 11
{
	va_list ap;

I 11
#ifdef __STDC__
E 11
	va_start(ap, fmt);
I 11
#else
	va_start(ap);
#endif
E 11
	(void)fprintf(stderr, "awk: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
E 9
D 4
	if (*NR > 0)
E 4
I 4
	if (NR && *NR > 0)
E 4
D 9
		fprintf(stderr, " record number %g\n", *NR);
	if (f)
E 9
I 9
		(void)fprintf(stderr, " record number %g\n", *NR);
	if (isfatal)
E 9
		exit(2);
}

PUTS(s) char *s; {
	dprintf("%s\n", s, NULL, NULL);
}

#define	MAXEXPON	38	/* maximum exponenet for fp number */

D 12
isnumber(s)
E 12
I 12
isanumber(s)
E 12
register char *s;
{
	register d1, d2;
	int point;
	char *es;

I 2
	if (s == NULL) 
		return (0);
E 2
	d1 = d2 = point = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '\0')
		return(0);	/* empty stuff isn't number */
	if (*s == '+' || *s == '-')
		s++;
	if (!isdigit(*s) && *s != '.')
		return(0);
	if (isdigit(*s)) {
		do {
			d1++;
			s++;
		} while (isdigit(*s));
	}
	if(d1 >= MAXEXPON)
		return(0);	/* too many digits to convert */
	if (*s == '.') {
		point++;
		s++;
	}
	if (isdigit(*s)) {
		d2++;
		do {
			s++;
		} while (isdigit(*s));
	}
	if (!(d1 || point && d2))
		return(0);
	if (*s == 'e' || *s == 'E') {
		s++;
		if (*s == '+' || *s == '-')
			s++;
		if (!isdigit(*s))
			return(0);
		es = s;
		do {
			s++;
		} while (isdigit(*s));
		if (s - es > 2)
			return(0);
		else if (s - es == 2 && 10 * (*es-'0') + *(es+1)-'0' >= MAXEXPON)
			return(0);
	}
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	if (*s == '\0')
		return(1);
	else
		return(0);
}
/*
D 12
isnumber(s) char *s; {return(0);}
E 12
I 12
isanumber(s) char *s; {return(0);}
E 12
*/
E 1
