h57780
s 00009/00002/00226
d D 4.4 91/04/17 17:25:28 bostic 4 3
c new copyright; att/bsd/shared
e
s 00015/00002/00213
d D 4.3 83/09/03 15:19:00 rrh 3 2
c allow a file called '-' on the argument line to stand for stdin, so
c that eqn works like cat
e
s 00003/00001/00212
d D 4.2 83/08/11 20:38:53 sam 2 1
c standardize sccs keyword lines
e
s 00213/00000/00000
d D 4.1 83/02/11 18:28:17 shannon 1 0
c date and time created 83/02/11 18:28:17 by shannon
e
u
U
t
T
I 4
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 2

#include "e.h"
#include "e.def"

#define	SSIZE	400
char	token[SSIZE];
int	sp;
#define	putbak(c)	*ip++ = c;
#define	PUSHBACK	300	/* maximum pushback characters */
char	ibuf[PUSHBACK+SSIZE];	/* pushback buffer for definitions, etc. */
char	*ip	= ibuf;

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
	fclose(curfile);
	linect = 1;
D 3
	if ((curfile=fopen(svargv[ifile], "r")) != NULL)
E 3
I 3
	if (openinfile() == 0)
E 3
		goto loop;
D 3
	error(FATAL, "can't open file %s", svargv[ifile]);
E 3
	return(EOF);
I 3
}
/*
 *	open file indexed by ifile in svargv, return non zero if fail
 */
openinfile()
{
	if (strcmp(svargv[ifile], "-") == 0){
		curfile = stdin;
		return(0);
	} else if ((curfile=fopen(svargv[ifile], "r")) != NULL){
		return(0);
	}
	error(FATAL, "can't open file %s", svargv[ifile]);
	return(1);
E 3
}

pbstr(str)
register char *str;
{
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
	register int c;
	tbl *tp, *lookup();
	extern tbl **keytbl, **deftbl;

  beg:
	while ((c=gtc())==' ' || c=='\n')
		;
	yylval=c;
	switch(c) {

	case EOF:
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
		for (sp=0; (c=gtc())!='"' && c != '\n'; ) {
			if (c == '\\')
				if ((c = gtc()) != '"')
					token[sp++] = '\\';
			token[sp++] = c;
			if (sp>=SSIZE)
				error(FATAL, "quoted string %.20s... too long", token);
		}
		token[sp]='\0';
		yylval = (int) &token[0];
		if (c == '\n')
			error(!FATAL, "missing \" in %.20s", token);
		return(QTEXT);
	}
	if (c==righteq)
		return(EOF);

	putbak(c);
	getstr(token, SSIZE);
	if (dbg)printf(".\tlex token = |%s|\n", token);
	if ((tp = lookup(&deftbl, token, NULL)) != NULL) {
		putbak(' ');
		pbstr(tp->defn);
		putbak(' ');
		if (dbg)
			printf(".\tfound %s|=%s|\n", token, tp->defn);
	}
	else if ((tp = lookup(&keytbl, token, NULL)) == NULL) {
		if(dbg)printf(".\t%s is not a keyword\n", token);
		return(CONTIG);
	}
	else if (tp->defn == (char *) DEFINE || tp->defn == (char *) NDEFINE || tp->defn == (char *) TDEFINE)
		define(tp->defn);
	else if (tp->defn == (char *) DELIM)
		delim();
	else if (tp->defn == (char *) GSIZE)
		globsize();
	else if (tp->defn == (char *) GFONT)
		globfont();
	else if (tp->defn == (char *) INCLUDE)
		include();
	else {
		return((int) tp->defn);
	}
	goto beg;
}

getstr(s, n) char *s; register int n; {
	register int c;
	register char *p;

	p = s;
	while ((c = gtc()) == ' ' || c == '\n')
		;
	if (c == EOF) {
		*s = 0;
		return;
	}
	while (c != ' ' && c != '\t' && c != '\n' && c != '{' && c != '}'
	  && c != '"' && c != '~' && c != '^' && c != righteq) {
		if (c == '\\')
			if ((c = gtc()) != '"')
				*p++ = '\\';
		*p++ = c;
		if (--n <= 0)
			error(FATAL, "token %.20s... too long", s);
		c = gtc();
	}
	if (c=='{' || c=='}' || c=='"' || c=='~' || c=='^' || c=='\t' || c==righteq)
		putbak(c);
	*p = '\0';
	yylval = (int) s;
}

cstr(s, quote, maxs) char *s; int quote; {
	int del, c, i;

	while((del=gtc()) == ' ' || del == '\t' || del == '\n');
	if (quote)
		for (i=0; (c=gtc()) != del && c != EOF;) {
			s[i++] = c;
			if (i >= maxs)
				return(1);	/* disaster */
		}
	else {
		s[0] = del;
		for (i=1; (c=gtc())!=' ' && c!= '\t' && c!='\n' && c!=EOF;) {
			s[i++]=c;
			if (i >= maxs)
				return(1);	/* disaster */
		}
	}
	s[i] = '\0';
	if (c == EOF)
		error(FATAL, "Unexpected end of input at %.20s", s);
	return(0);
}

define(type) int type; {
	char *strsave(), *p1, *p2;
	tbl *lookup();
	extern tbl **deftbl;

	getstr(token, SSIZE);	/* get name */
	if (type != DEFINE) {
		cstr(token, 1, SSIZE);	/* skip the definition too */
		return;
	}
	p1 = strsave(token);
	if (cstr(token, 1, SSIZE))
		error(FATAL, "Unterminated definition at %.20s", token);
	p2 = strsave(token);
	lookup(&deftbl, p1, p2);
	if (dbg)printf(".\tname %s defined as %s\n", p1, p2);
}

char *strsave(s)
char *s;
{
	char *malloc();
	register char *q;

	q = malloc(strlen(s)+1);
	if (q == NULL)
		error(FATAL, "out of space in strsave on %s", s);
	strcpy(q, s);
	return(q);
}

include() {
	error(!FATAL, "Include not yet implemented");
}

delim() {
	yyval = eqnreg = 0;
	if (cstr(token, 0, SSIZE))
		error(FATAL, "Bizarre delimiters at %.20s", token);
	lefteq = token[0];
	righteq = token[1];
	if (lefteq == 'o' && righteq == 'f')
		lefteq = righteq = '\0';
}
E 1
