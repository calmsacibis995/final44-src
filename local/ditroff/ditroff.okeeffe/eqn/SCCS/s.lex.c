h02027
s 00001/00001/00260
d D 2.2 87/04/01 15:17:50 jaap 3 2
c Updates from bwk, see README for details
e
s 00126/00104/00135
d D 2.1 85/07/18 18:08:13 jaap 2 1
c Edition 8 Version of eqn (May 1985). 
c Local hacks from jaap.
e
s 00239/00000/00000
d D 1.1 85/03/01 15:26:59 jaap 1 0
c date and time created 85/03/01 15:26:59 by jaap
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
D 3
#include "e.def"
E 3
I 3
#include "y.tab.h"
E 3
#include "ctype.h"

#define	SSIZE	400
char	token[SSIZE];
int	sp;
D 2
#define	putbak(c)	*ip++ = c;
#define	PUSHBACK	300	/* maximum pushback characters */
char	ibuf[PUSHBACK+SSIZE];	/* pushback buffer for definitions, etc. */
char	*ip	= ibuf;
E 2

D 2
gtc() {
  loop:
	if (ip > ibuf)
		return(*--ip);	/* already present */
	lastchar = getc(curfile);
	if (lastchar=='\n')
		linect++;
	if (lastchar != EOF)
		return(lastchar);
	if (++ifile > svargc) {
		return(EOF);
	}
	if (curfile != stdin)
		fclose(curfile);
	linect = 1;
	if (strcmp(svargv[ifile], "-") == 0) {
		curfile = stdin;
		goto loop;
	}
	if ((curfile=fopen(svargv[ifile], "r")) != NULL)
		goto loop;
	error(FATAL, "can't open file %s", svargv[ifile]);
	return(EOF);
}

pbstr(str)
register char *str;
E 2
I 2
yylex()
E 2
{
D 2
	register char *p;

	p = str;
	while (*p++);
	--p;
	if (ip >= &ibuf[PUSHBACK])
		error( FATAL, "pushback overflow");
	while (p > str)
		putbak(*--p);
}

yylex() {
E 2
	register int c;
D 2
	tbl *tp, *lookup();
	extern tbl **keytbl, **deftbl;
E 2
I 2
	tbl *tp;
E 2

D 2
  beg:
	while ((c=gtc())==' ' || c=='\n')
E 2
I 2
  begin:
	while ((c=input()) == ' ' || c == '\n')
E 2
		;
D 2
	yylval=c;
	switch(c) {

E 2
I 2
	yylval = c;
	switch (c) {
E 2
	case EOF:
I 2
		error(!FATAL, "unexpected end of input inside equation");
E 2
		return(EOF);
	case '~':
		return(SPACE);
	case '^':
		return(THIN);
	case '\t':
		return(TAB);
	case '{':
		return('{');
	case '}':
		return('}');
	case '"':
D 2
		for (sp=0; (c=gtc())!='"' && c != '\n'; ) {
E 2
I 2
		for (sp = 0; (c=input())!='"' && c != '\n'; ) {
E 2
			if (c == '\\')
D 2
				if ((c = gtc()) != '"')
E 2
I 2
				if ((c = input()) != '"')
E 2
					token[sp++] = '\\';
			token[sp++] = c;
D 2
			if (sp>=SSIZE)
E 2
I 2
			if (sp >= SSIZE)
E 2
				error(FATAL, "quoted string %.20s... too long", token);
		}
D 2
		token[sp]='\0';
E 2
I 2
		token[sp] = '\0';
E 2
		yylval = (int) &token[0];
		if (c == '\n')
			error(!FATAL, "missing \" in %.20s", token);
		return(QTEXT);
	}
D 2
	if (c==righteq)
E 2
I 2
	if (!display && c == righteq)
E 2
		return(EOF);

D 2
	putbak(c);
E 2
I 2
	unput(c);
E 2
	getstr(token, SSIZE);
D 2
	if (dbg)printf(".\tlex token = |%s|\n", token);
	if ((tp = lookup(&deftbl, token, NULL)) != NULL) {
		putbak(' ');
		pbstr(tp->defn);
		putbak(' ');
		if (dbg)
			printf(".\tfound %s|=%s|\n", token, tp->defn);
E 2
I 2
	dprintf(".\tlex token = |%s|\n", token);
	if ((tp = lookup(deftbl, token, NULL)) != NULL) {	/* defined term */
		c = input();
		unput(c);
		if (c == '(')	/* macro with args */
			dodef(tp);
		else {		/* no args */
			unput(' ');
			pbstr(tp->defn);
			dprintf(".\tfound %s|=%s|\n", token, tp->defn);
		}
		goto begin;
E 2
	}
D 2
	else if ((tp = lookup(&keytbl, token, NULL)) == NULL) {
		if(dbg)printf(".\t%s is not a keyword\n", token);
		return(CONTIG);
	}
	else if (tp->defn == (char *) DEFINE || tp->defn == (char *) NDEFINE || tp->defn == (char *) TDEFINE)
E 2
I 2

	if ((tp = lookup(keytbl, token, NULL)) == NULL)	/* not a keyword */
		return CONTIG;

	switch ((int) tp->defn) {		/* some kind of keyword */
	case DEFINE: case TDEFINE: case NDEFINE:
E 2
		define(tp->defn);
D 2
	else if (tp->defn == (char *) DELIM)
E 2
I 2
		break;
	case IFDEF:
		ifdef();
		break;
	case DELIM:
E 2
		delim();
D 2
	else if (tp->defn == (char *) GSIZE)
E 2
I 2
		break;
	case GSIZE:
E 2
		globsize();
D 2
	else if (tp->defn == (char *) GFONT)
E 2
I 2
		break;
	case GFONT:
E 2
		globfont();
D 2
	else if (tp->defn == (char *) INCLUDE)
E 2
I 2
		break;
	case INCLUDE:
E 2
		include();
D 2
	else if (tp->defn == (char *) SPACE)
E 2
I 2
		break;
	case SPACE:
E 2
		space();
D 2
	else {
		return((int) tp->defn);
E 2
I 2
		break;
	case DOTEQ:
			/* .EQ inside equation -- should warn if at bottom level */
		break;
	case DOTEN:
		if (curfile == infile)
			return EOF;
		/* else ignore nested .EN */
		break;
	default:
		return (int) tp->defn;
E 2
	}
D 2
	goto beg;
E 2
I 2
	goto begin;
E 2
}

D 2
getstr(s, n) char *s; register int n; {
E 2
I 2
getstr(s, n)
	char *s;
	register int n;
{
E 2
	register int c;
	register char *p;

	p = s;
D 2
	while ((c = gtc()) == ' ' || c == '\n')
E 2
I 2
	while ((c = input()) == ' ' || c == '\n')
E 2
		;
	if (c == EOF) {
		*s = 0;
		return;
	}
	while (c != ' ' && c != '\t' && c != '\n' && c != '{' && c != '}'
D 2
	  && c != '"' && c != '~' && c != '^' && c != righteq) {
E 2
I 2
	    && c != '"' && c != '~' && c != '^') {
		if (!display && c == righteq)
			break;
		if (c == '(' && p > s) {	/* might be defined(...) */
			*p = '\0';
			if (lookup(deftbl, s, NULL) != NULL)
				break;
		}
E 2
		if (c == '\\')
D 2
			if ((c = gtc()) != '"')
E 2
I 2
			if ((c = input()) != '"')
E 2
				*p++ = '\\';
		*p++ = c;
		if (--n <= 0)
			error(FATAL, "token %.20s... too long", s);
D 2
		c = gtc();
E 2
I 2
		c = input();
E 2
	}
D 2
	if (c=='{' || c=='}' || c=='"' || c=='~' || c=='^' || c=='\t' || c==righteq)
		putbak(c);
E 2
I 2
	unput(c);
E 2
	*p = '\0';
	yylval = (int) s;
}

D 2
cstr(s, quote, maxs) char *s; int quote; {
E 2
I 2
cstr(s, quote, maxs)
	char *s;
	int quote;
{
E 2
	int del, c, i;

	s[0] = 0;
D 2
	while((del=gtc()) == ' ' || del == '\t')
E 2
I 2
	while ((del=input()) == ' ' || del == '\t')
E 2
		;
	if (quote)
D 2
		for (i=0; (c=gtc()) != del && c != EOF;) {
E 2
I 2
		for (i=0; (c=input()) != del && c != EOF;) {
E 2
			s[i++] = c;
			if (i >= maxs)
				return(1);	/* disaster */
		}
	else {
		if (del == '\n')
			return(1);
		s[0] = del;
D 2
		for (i=1; (c=gtc())!=' ' && c!= '\t' && c!='\n' && c!=EOF;) {
			s[i++]=c;
E 2
I 2
		for (i=1; (c=input())!=' ' && c!= '\t' && c!='\n' && c!=EOF;) {
			s[i++] = c;
E 2
			if (i >= maxs)
				return(1);	/* disaster */
		}
	}
	s[i] = '\0';
	if (c == EOF)
		error(FATAL, "Unexpected end of input at %.20s", s);
	return(0);
}

D 2
define(type) int type; {
	char *strsave(), *p1, *p2;
	tbl *lookup();
	extern tbl **deftbl;
E 2
I 2
define(type)
	int type;
{
	char *p1, *p2;
E 2

	getstr(token, SSIZE);	/* get name */
	if (type != DEFINE) {
		cstr(token, 1, SSIZE);	/* skip the definition too */
		return;
	}
	p1 = strsave(token);
	if (cstr(token, 1, SSIZE))
		error(FATAL, "Unterminated definition at %.20s", token);
	p2 = strsave(token);
D 2
	lookup(&deftbl, p1, p2);
	if (dbg)printf(".\tname %s defined as %s\n", p1, p2);
E 2
I 2
	lookup(deftbl, p1, p2);
	dprintf(".\tname %s defined as %s\n", p1, p2);
E 2
}

I 2
ifdef()		/* do body if name is defined */
{
	tbl *tp;
	char name[100], *p;

	getstr(name, sizeof(name));	/* get name */
	cstr(token, 1, SSIZE);		/* and body */
	if ((tp = lookup(deftbl, name, NULL)) != NULL) {	/* found it */
		p = strsave(token);
		pushsrc(Free, p);
		pushsrc(String, p);
	}
}

E 2
char	*spaceval	= NULL;

space()	/* collect line of form "space amt" to replace \x in output */
{
D 2
	char *strsave();

E 2
	getstr(token, SSIZE);
	spaceval = strsave(token);
D 2
	if (dbg) printf(".\tsetting space to %s\n", token);
E 2
I 2
	dprintf(".\tsetting spaceval to %s\n", token);
E 2
}

char *strsave(s)
D 2
char *s;
E 2
I 2
	char *s;
E 2
{
D 2
	char *malloc();
E 2
	register char *q;

	q = malloc(strlen(s)+1);
	if (q == NULL)
		error(FATAL, "out of space in strsave on %s", s);
	strcpy(q, s);
	return(q);
}

D 2
include() {
	error(!FATAL, "Include not yet implemented");
E 2
I 2
include()
{
	char name[100];
	FILE *fin;
	int c;
	extern int errno;

	while ((c = input()) == ' ')
		;
	unput(c);
	cstr(name, c == '"', sizeof(name));	/* gets it quoted or not */
	if ((fin = fopen(name, "r")) == NULL)
		fatal("can't open file %s", name);
	errno = 0;
	curfile++;
	curfile->fin = fin;
	curfile->fname = strsave(name);
	curfile->lineno = 0;
	printf(".lf 1 %s\n", curfile->fname);
	pushsrc(File, curfile);
E 2
}

D 2
delim() {
E 2
I 2
delim()
{
E 2
	yyval = eqnreg = 0;
	if (cstr(token, 0, SSIZE))
		error(FATAL, "Bizarre delimiters");
	lefteq = token[0];
	righteq = token[1];
        if (!isprint(lefteq) || !isprint(righteq))
		error(FATAL, "Bizarre delimiters");
	if (lefteq == 'o' && righteq == 'f')
		lefteq = righteq = '\0';
}
E 1
