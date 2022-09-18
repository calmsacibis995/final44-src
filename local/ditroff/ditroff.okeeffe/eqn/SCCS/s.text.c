h44460
s 00004/00004/00250
d D 2.2 87/04/01 15:18:34 jaap 3 2
c Updates from bwk, see README for details
e
s 00149/00075/00105
d D 2.1 85/07/18 18:10:28 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00180/00000/00000
d D 1.1 85/03/01 15:27:19 jaap 1 0
c date and time created 85/03/01 15:27:19 by jaap
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
# include "e.h"
# include "e.def"
# include "ctype.h"
E 2
I 2
static char sccsid[] = "%W% (CWI) %E%";
#endif lint
#include "e.h"
D 3
#include "e.def"
E 3
I 3
#include "y.tab.h"
E 3
#include <ctype.h>
E 2

D 2
int	csp;
int	psp;
E 2
#define	CSSIZE	400
D 2
char	cs[420];
E 2
I 2
char	cs[CSSIZE+20];	/* text string converted into this */
char	*csp;		/* next spot in cs[] */
char	*psp;		/* next character in input token */
E 2

D 2
int	lf, rf;	/* temporary spots for left and right fonts */
E 2
I 2
int	lf, rf;		/* temporary spots for left and right fonts */
int	lastft;		/* last \f added */
int	nextft;		/* next \f to be added */
E 2

D 2
text(t,p1) int t; char *p1; {
E 2
I 2
text(t, p1)	/* convert text string p1 of type t */
	int t;
	char *p1;
{
E 2
	int c;
	char *p;
D 2
	tbl *tp, *lookup();
	extern tbl *restbl;
E 2
I 2
	tbl *tp;
E 2

D 2
	yyval = oalloc();
E 2
I 2
	yyval = salloc();
E 2
	ebase[yyval] = 0;
D 2
	eht[yyval] = VERT( EM(1.0, EFFPS(ps)) );	/* ht in machine units */
E 2
I 2
	eht[yyval] = EM(1.0, ps);	/* ht in ems of orig size */
	eps[yyval] = ps;
E 2
	lfont[yyval] = rfont[yyval] = ROM;
D 2
	if (t == QTEXT)
		p = p1;
	else if ( t == SPACE )
E 2
I 2
	if (t == QTEXT) {
		for (p = p1; *p; p++)	/* scan for embedded \f's */
			if (*p == '\\' && *(p+1) == 'f')
				break;
		if (*p)		/* if found \f, leave it alone and hope */
			p = p1;
		else {
			sprintf(cs, "\\f%s%s\\fP", ftp->name, p1);
			p = cs;
		}
	} else if (t == SPACE)
E 2
		p = "\\ ";
D 2
	else if ( t == THIN )
E 2
I 2
	else if (t == THIN)
E 2
		p = "\\|";
D 2
	else if ( t == TAB )
E 2
I 2
	else if (t == TAB)
E 2
		p = "\\t";
D 2
	else if ((tp = lookup(&restbl, p1, NULL)) != NULL) {
E 2
I 2
	else if ((tp = lookup(restbl, p1, NULL)) != NULL) {
E 2
		p = tp->defn;
	} else {
		lf = rf = 0;
D 2
		for (csp=psp=0; (c=p1[psp++])!='\0';) {
E 2
I 2
		/* sprintf(cs, "\\f%s", ftp->name); */
		lastft = 0;
		csp = cs;
		for (psp = p1; (c = *psp++) != '\0'; ) {
			nextft = ft;
E 2
			rf = trans(c, p1);
			if (lf == 0)
				lf = rf;	/* save first */
D 2
			if (csp>CSSIZE)
E 2
I 2
			if (csp-cs > CSSIZE)
E 2
				error(FATAL,"converted token %.25s... too long",p1);
		}
D 2
		cs[csp] = '\0';
E 2
I 2
		sadd("\\fP");
		*csp = '\0';
E 2
		p = cs;
		lfont[yyval] = lf;
		rfont[yyval] = rf;
	}
D 2
	if(dbg)printf(".\t%dtext: S%d <- %s; b=%d,h=%d,lf=%c,rf=%c\n",
		t, yyval, p, ebase[yyval], eht[yyval], lfont[yyval], rfont[yyval]);
E 2
I 2
	dprintf(".\t%dtext: S%d <- %s; b=%g,h=%g,lf=%c,rf=%c,ps=%d\n",
		t, yyval, p, ebase[yyval], eht[yyval], lfont[yyval], rfont[yyval], ps);
E 2
	printf(".ds %d \"%s\n", yyval, p);
}

D 2
trans(c,p1) int c; char *p1; {
E 2
I 2
trans(c, p1)
	int c;
	char *p1;
{
E 2
	int f;
I 2

E 2
	f = ROM;
D 2
	switch( c) {
E 2
I 2
	switch (c) {
E 2
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
D 2
	case ':': case ';': case '!': case '%':
	case '(': case '[': case ')': case ']':
	case ',':
E 2
I 2
	case ':': case ';': case '!': case '%': case '?':
	case '(': case '[': case ']':
E 2
		if (rf == ITAL)
			shim();
D 2
		roman(c); break;
E 2
I 2
		roman(c);
		break;
	case ')':
		if (rf == ITAL)
			halfshim();
		roman(c);
		break;
	case ',':
		roman(c);
		halfshim();
		f = rf;
		break;
E 2
	case '.':
		if (rf == ROM)
			roman(c);
		else
D 2
			cs[csp++] = c;
E 2
I 2
			cadd(c);
E 2
		f = rf;
		break;
	case '|':
		if (rf == ITAL && ttype != DEV202)
			shim();
D 2
		shim(); roman(c); shim(); break;
E 2
I 2
		shim(); roman(c); shim();
		break;
E 2
	case '=':
		if (rf == ITAL)
			shim();
		name4('e','q');
		break;
	case '+':
		if (rf == ITAL)
			shim();
D 2
		name4('p', 'l');
E 2
I 2
		name4('p','l');
E 2
		break;
	case '>': case '<':
		if (rf == ITAL)
			shim();
D 2
		if (p1[psp]=='=') {	/* look ahead for == <= >= */
E 2
I 2
		if (*psp == '=') {	/* look ahead for == <= >= */
E 2
			name4(c,'=');
			psp++;
		} else {
D 2
			cs[csp++] = c;  
E 2
I 2
			cadd(c);  
E 2
		}
		break;
	case '-':
		if (rf == ITAL)
			shim();
D 2
		if (p1[psp]=='>') {
			name4('-','>'); psp++;
E 2
I 2
		if (*psp == '>') {
			name4('-','>');
			halfshim();
			psp++;
E 2
		} else {
			name4('m','i');
		}
		break;
	case '/':
D 3
		if (rf == ITAL)
			shim();
		name4('s','l');
E 3
I 3
		halfshim();
		cadd('/');
		halfshim();
E 3
		break;
	case '~': case ' ':
D 2
		shim(); shim(); break;
E 2
I 2
		shim(); shim();
		break;
E 2
	case '^':
D 2
		shim(); break;
	case '\\':	/* troff - pass 2 or 3 more chars */
E 2
I 2
		shim();
		break;
	case '\\':	/* troff - pass only \(xx without comment */
E 2
		if (rf == ITAL)
			shim();
D 2
		cs[csp++] = c; cs[csp++] = c = p1[psp++]; cs[csp++] = p1[psp++];
		if (c=='(') cs[csp++] = p1[psp++];
		if (c=='*' && cs[csp-1] == '(') {
			cs[csp++] = p1[psp++];
			cs[csp++] = p1[psp++];
		}
E 2
I 2
		cadd('\\');
		cadd(c = *psp++);
		if (c == '(' && *psp && *(psp+1)) {
			cadd(*psp++);
			cadd(*psp++);
		} else
			fprintf(stderr, "eqn warning: unquoted troff command \\%c, line %d, file %s\n",
				c, curfile->lineno, curfile->fname);
E 2
		break;
	case '\'':
D 2
		cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = rf==ITAL ? ITAL : ROM;
E 2
		name4('f','m');
D 2
		cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = 'P';
		f = rf==ITAL ? ITAL : ROM;
E 2
		break;

	case 'f':
		if (ft == ITAL) {
D 2
			if (psp == 1 || !isalnum(p1[psp-2])) {
				cs[csp++] = '\\';
				cs[csp++] = '^';
			}
			cs[csp++] = 'f';
			if (!isalpha(p1[psp])) {	/* add \| after f except in text */
				cs[csp++] = '\\';
				cs[csp++] = '|';
			}
E 2
I 2
			if (psp == p1+1 || !isalnum(*(psp-2)))
				halfshim();
			cadd('f');
			if (!isalpha(*psp) && *psp != '\0')	/* add \| except in text */
				shim();
E 2
			f = ITAL;
		}
		else
D 2
			cs[csp++] = 'f';
E 2
I 2
			cadd('f');
E 2
		break;
	case 'j':
		if (ft == ITAL) {
D 2
			cs[csp++] = '\\'; cs[csp++] = '^';
			cs[csp++] = 'j';
E 2
I 2
			sadd("\\^j");
E 2
			f = ITAL;
		}
		else
D 2
			cs[csp++] = 'j';
E 2
I 2
			cadd('j');
E 2
		break;
	default:
D 2
		cs[csp++] = c;
E 2
I 2
		cadd(c);
E 2
		f = ft==ITAL ? ITAL : ROM;
		break;
	}
	return(f);
}

D 2
shim() {
	cs[csp++] = '\\'; cs[csp++] = '|';
E 2
I 2
shim()	/* add a \| space */
{
	sadd("\\|");
E 2
}

D 2
roman(c) int c; {
	cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = (ft==ITAL) ? ROM : ft;
	cs[csp++] = c;
	cs[csp++] = '\\'; cs[csp++] = 'f'; cs[csp++] = 'P';
E 2
I 2
halfshim()	/* add a \^ space */
{
	sadd("\\^");
E 2
}

D 2
name4(c1,c2) int c1,c2; {
	cs[csp++] = '\\';
	cs[csp++] = '(';
	cs[csp++] = c1;
	cs[csp++] = c2;
E 2
I 2
roman(c)	/* add char c in "roman" font */
	int c;
{
	nextft = ROM;
	cadd(c);
}

name4(c1,c2)
	int c1, c2;
{
	sadd("\\(");
	cadd(c1);
	cadd(c2);
}

sadd(s)		/* add string s to cs */
	char *s;
{
	while (*s)
		cadd(*s++);
}

cadd(c)		/* add char c to end of cs */
	int c;
{
	char *p;

	if (lastft != nextft) {
		if (lastft != 0) {
			*csp++ = '\\';
			*csp++ = 'f';
			*csp++ = 'P';
		}
		*csp++ = '\\';
		*csp++ = 'f';
		if (ftp == ftstack) {	/* bottom level */
			if (ftp->ft == ITAL)	/* usual case */
				*csp++ = nextft;
			else		/* gfont set, use it */
				for (p = ftp->name; *csp = *p++; )
					csp++;
		} else {	/* inside some kind of font ... */
			for (p = ftp->name; *csp = *p++; )
				csp++;
		}
		lastft = nextft;
	}
	*csp++ = c;
E 2
}
E 1
