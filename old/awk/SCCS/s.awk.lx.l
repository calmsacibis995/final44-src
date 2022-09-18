h41307
s 00003/00003/00217
d D 4.6 94/01/28 09:41:15 vern 6 5
c moved sccsid inside %{...%}
e
s 00010/00001/00210
d D 4.5 91/04/17 16:54:57 bostic 5 4
c new copyright; att/bsd/shared
e
s 00094/00094/00117
d D 4.4 90/06/25 14:31:05 bostic 4 3
c new versions from Vern Paxson, for flex
e
s 00041/00005/00170
d D 4.3 84/12/08 15:07:36 sam 3 2
c add -l flag to force printing of lexical tokens
e
s 00002/00002/00173
d D 4.2 83/02/09 14:07:04 sam 2 1
c merge from sun
e
s 00175/00000/00000
d D 4.1 82/05/07 19:23:52 mckusick 1 0
c date and time created 82/05/07 19:23:52 by mckusick
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

I 6
%X str chc reg comment

%{
E 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

D 4
%Start A str chc sc reg comment
E 4
I 4
D 6
%X str chc reg comment
E 4

%{
E 6
I 4
#include	<string.h>
E 4
#include	"awk.h"
#include	"awk.def"
D 4
#undef	input	/* defeat lex */
E 4
extern int	yylval;
extern int	mustfld;
I 3
extern int	ldbg;
I 4
extern char	*lexprog;
E 4
E 3

I 4
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size)				\
{								\
	if ( lexprog )						\
		{						\
		result = strlen( lexprog );			\
		if ( result > max_size )			\
			{					\
			result = max_size;			\
			strncpy( buf, lexprog, result );	\
			}					\
		else						\
			strcpy( buf, lexprog );			\
		lexprog += result;				\
		}						\
	else							\
		result = read( fileno(yyin), buf, max_size );	\
}

E 4
int	lineno	= 1;
D 3
#ifdef	DEBUG
#	define	RETURN(x)	{if (dbg) ptoken(x); return(x); }
#else
#	define	RETURN(x)	return(x)
#endif
E 3
I 3
#define	RETURN(x)	{if (ldbg) ptoken(x); return(x); }
E 3
D 4
#define	CADD	cbuf[clen++]=yytext[0]; if(clen>=CBUFLEN-1) {yyerror("string too long", cbuf); BEGIN A;}
E 4
I 4
#define	CADD	cbuf[clen++]=yytext[0]; if(clen>=CBUFLEN-1) {yyerror("string too long", cbuf); BEGIN INITIAL;}
E 4
#define	CBUFLEN	150
char	cbuf[CBUFLEN];
int	clen, cflag;
%}

A	[a-zA-Z_]
B	[a-zA-Z0-9_]
D	[0-9]
WS	[ \t]

%%
D 4
	switch (yybgin-yysvec-1) {	/* witchcraft */
	case 0:
		BEGIN A;
		break;
	case sc:
		BEGIN A;
E 4
I 4
	static int sc_flag = 0;

	if ( sc_flag ) {
		BEGIN INITIAL;
		sc_flag = 0;
E 4
		RETURN('}');
	}

D 4
<A>^\n		lineno++;
<A>^{WS}*#.*\n	lineno++;	/* strip comment lines */
<A>{WS}		;
<A,reg>"\\"\n	lineno++;
<A>"||"		RETURN(BOR);
<A>BEGIN	RETURN(XBEGIN);
<A>END		RETURN(XEND);
<A>PROGEND	RETURN(EOF);
<A>"&&"		RETURN(AND);
<A>"!"		RETURN(NOT);
<A>"!="		{ yylval = NE; RETURN(RELOP); }
<A>"~"		{ yylval = MATCH; RETURN(MATCHOP); }
<A>"!~"		{ yylval = NOTMATCH; RETURN(MATCHOP); }
<A>"<"		{ yylval = LT; RETURN(RELOP); }
<A>"<="		{ yylval = LE; RETURN(RELOP); }
<A>"=="		{ yylval = EQ; RETURN(RELOP); }
<A>">="		{ yylval = GE; RETURN(RELOP); }
<A>">"		{ yylval = GT; RETURN(RELOP); }
<A>">>"		{ yylval = APPEND; RETURN(RELOP); }
<A>"++"		{ yylval = INCR; RETURN(INCR); }
<A>"--"		{ yylval = DECR; RETURN(DECR); }
<A>"+="		{ yylval = ADDEQ; RETURN(ASGNOP); }
<A>"-="		{ yylval = SUBEQ; RETURN(ASGNOP); }
<A>"*="		{ yylval = MULTEQ; RETURN(ASGNOP); }
<A>"/="		{ yylval = DIVEQ; RETURN(ASGNOP); }
<A>"%="		{ yylval = MODEQ; RETURN(ASGNOP); }
<A>"="		{ yylval = ASSIGN; RETURN(ASGNOP); }
E 4
I 4
^\n		lineno++;
^{WS}*#.*\n	lineno++;	/* strip comment lines */
{WS}		;
<INITIAL,reg>"\\"\n	lineno++;
"||"		RETURN(BOR);
BEGIN	RETURN(XBEGIN);
END		RETURN(XEND);
PROGEND	RETURN(EOF);
"&&"		RETURN(AND);
"!"		RETURN(NOT);
"!="		{ yylval = NE; RETURN(RELOP); }
"~"		{ yylval = MATCH; RETURN(MATCHOP); }
"!~"		{ yylval = NOTMATCH; RETURN(MATCHOP); }
"<"		{ yylval = LT; RETURN(RELOP); }
"<="		{ yylval = LE; RETURN(RELOP); }
"=="		{ yylval = EQ; RETURN(RELOP); }
">="		{ yylval = GE; RETURN(RELOP); }
">"		{ yylval = GT; RETURN(RELOP); }
">>"		{ yylval = APPEND; RETURN(RELOP); }
"++"		{ yylval = INCR; RETURN(INCR); }
"--"		{ yylval = DECR; RETURN(DECR); }
"+="		{ yylval = ADDEQ; RETURN(ASGNOP); }
"-="		{ yylval = SUBEQ; RETURN(ASGNOP); }
"*="		{ yylval = MULTEQ; RETURN(ASGNOP); }
"/="		{ yylval = DIVEQ; RETURN(ASGNOP); }
"%="		{ yylval = MODEQ; RETURN(ASGNOP); }
"="		{ yylval = ASSIGN; RETURN(ASGNOP); }
E 4

D 4
<A>"$"{D}+	{	if (atoi(yytext+1)==0) {
E 4
I 4
"$"{D}+	{	if (atoi(yytext+1)==0) {
E 4
				yylval = (hack)lookup("$record", symtab, 0);
				RETURN(STRING);
			} else {
				yylval = fieldadr(atoi(yytext+1));
				RETURN(FIELD);
			}
		}
D 4
<A>"$"{WS}*	{ RETURN(INDIRECT); }
D 2
<A>NF		{ mustfld=1; yylval = (hack)setsymtab(yytext, NULL, 0.0, NUM, symtab); RETURN(VAR); }
E 2
I 2
<A>NF		{ mustfld=1; yylval = (hack)setsymtab(yytext, EMPTY, 0.0, NUM, symtab); RETURN(VAR); }
E 2
<A>({D}+("."?){D}*|"."{D}+)((e|E)("+"|-)?{D}+)?	{
E 4
I 4
"$"{WS}*	{ RETURN(INDIRECT); }
NF		{ mustfld=1; yylval = (hack)setsymtab(yytext, EMPTY, 0.0, NUM, symtab); RETURN(VAR); }
({D}+("."?){D}*|"."{D}+)((e|E)("+"|-)?{D}+)?	{
E 4
D 2
		yylval = (hack)setsymtab(yytext, NULL, atof(yytext), CON|NUM, symtab); RETURN(NUMBER); }
E 2
I 2
		yylval = (hack)setsymtab(yytext, EMPTY, atof(yytext), CON|NUM, symtab); RETURN(NUMBER); }
E 2
D 4
<A>"}"{WS}*\n	{ BEGIN sc; lineno++; RETURN(';'); }
<A>"}"		{ BEGIN sc; RETURN(';'); }
<A>;\n		{ lineno++; RETURN(';'); }
<A>\n		{ lineno++; RETURN(NL); }
<A>while	RETURN(WHILE);
<A>for		RETURN(FOR);
<A>if		RETURN(IF);
<A>else		RETURN(ELSE);
<A>next		RETURN(NEXT);
<A>exit		RETURN(EXIT);
<A>break	RETURN(BREAK);
<A>continue	RETURN(CONTINUE);
<A>print	{ yylval = PRINT; RETURN(PRINT); }
<A>printf	{ yylval = PRINTF; RETURN(PRINTF); }
<A>sprintf	{ yylval = SPRINTF; RETURN(SPRINTF); }
<A>split	{ yylval = SPLIT; RETURN(SPLIT); }
<A>substr	RETURN(SUBSTR);
<A>index	RETURN(INDEX);
<A>in		RETURN(IN);
<A>getline	RETURN(GETLINE);
<A>length	{ yylval = FLENGTH; RETURN(FNCN); }
<A>log		{ yylval = FLOG; RETURN(FNCN); }
<A>int		{ yylval = FINT; RETURN(FNCN); }
<A>exp		{ yylval = FEXP; RETURN(FNCN); }
<A>sqrt		{ yylval = FSQRT; RETURN(FNCN); }
<A>{A}{B}*	{ yylval = (hack)setsymtab(yytext, tostring(""), 0.0, STR|NUM, symtab); RETURN(VAR); }
<A>\"		{ BEGIN str; clen=0; }
E 4
I 4
"}"{WS}*\n	{ sc_flag = 1; lineno++; RETURN(';'); }
"}"		{ sc_flag = 1; RETURN(';'); }
;\n		{ lineno++; RETURN(';'); }
\n		{ lineno++; RETURN(NL); }
while	RETURN(WHILE);
for		RETURN(FOR);
if		RETURN(IF);
else		RETURN(ELSE);
next		RETURN(NEXT);
exit		RETURN(EXIT);
break	RETURN(BREAK);
continue	RETURN(CONTINUE);
print	{ yylval = PRINT; RETURN(PRINT); }
printf	{ yylval = PRINTF; RETURN(PRINTF); }
sprintf	{ yylval = SPRINTF; RETURN(SPRINTF); }
split	{ yylval = SPLIT; RETURN(SPLIT); }
substr	RETURN(SUBSTR);
index	RETURN(INDEX);
in		RETURN(IN);
getline	RETURN(GETLINE);
length	{ yylval = FLENGTH; RETURN(FNCN); }
log		{ yylval = FLOG; RETURN(FNCN); }
int		{ yylval = FINT; RETURN(FNCN); }
exp		{ yylval = FEXP; RETURN(FNCN); }
sqrt		{ yylval = FSQRT; RETURN(FNCN); }
{A}{B}*	{ yylval = (hack)setsymtab(yytext, tostring(""), 0.0, STR|NUM, symtab); RETURN(VAR); }
\"		{ BEGIN str; clen=0; }
E 4

D 4
<A>#		{ BEGIN comment; }
<comment>\n	{ BEGIN A; lineno++; RETURN(NL); }
E 4
I 4
#		{ BEGIN comment; }
<comment>\n	{ BEGIN INITIAL; lineno++; RETURN(NL); }
E 4
<comment>.	;

D 4
<A>.		{ yylval = yytext[0]; RETURN(yytext[0]); }
E 4
I 4
.		{ yylval = yytext[0]; RETURN(yytext[0]); }
E 4

<reg>"["	{ BEGIN chc; clen=0; cflag=0; }
<reg>"[^"	{ BEGIN chc; clen=0; cflag=1; }

<reg>"?"	RETURN(QUEST);
<reg>"+"	RETURN(PLUS);
<reg>"*"	RETURN(STAR);
<reg>"|"	RETURN(OR);
<reg>"."	RETURN(DOT);
<reg>"("	RETURN('(');
<reg>")"	RETURN(')');
<reg>"^"	RETURN('^');
<reg>"$"	RETURN('$');
<reg>\\{D}{D}{D}	{ sscanf(yytext+1, "%o", &yylval); RETURN(CHAR); }
<reg>\\.	{	if (yytext[1]=='n') yylval = '\n';
			else if (yytext[1] == 't') yylval = '\t';
			else yylval = yytext[1];
			RETURN(CHAR);
		}
D 4
<reg>"/"	{ BEGIN A; unput('/'); }
<reg>\n		{ yyerror("newline in regular expression"); lineno++; BEGIN A; }
E 4
I 4
<reg>"/"	{ BEGIN INITIAL; unput('/'); }
<reg>\n		{ yyerror("newline in regular expression"); lineno++; BEGIN INITIAL; }
E 4
<reg>.		{ yylval = yytext[0]; RETURN(CHAR); }

D 4
<str>\"		{ char *s; BEGIN A; cbuf[clen]=0; s = tostring(cbuf);
E 4
I 4
<str>\"		{ char *s; BEGIN INITIAL; cbuf[clen]=0; s = tostring(cbuf);
E 4
		cbuf[clen] = ' '; cbuf[++clen] = 0;
		yylval = (hack)setsymtab(cbuf, s, 0.0, CON|STR, symtab); RETURN(STRING); }
D 4
<str>\n		{ yyerror("newline in string"); lineno++; BEGIN A; }
E 4
I 4
<str>\n		{ yyerror("newline in string"); lineno++; BEGIN INITIAL; }
E 4
<str>"\\\""	{ cbuf[clen++]='"'; }
<str,chc>"\\"n	{ cbuf[clen++]='\n'; }
<str,chc>"\\"t	{ cbuf[clen++]='\t'; }
<str,chc>"\\\\"	{ cbuf[clen++]='\\'; }
<str>.		{ CADD; }

<chc>"\\""]"	{ cbuf[clen++]=']'; }
<chc>"]"	{ BEGIN reg; cbuf[clen]=0; yylval = (hack)tostring(cbuf);
		if (cflag==0) { RETURN(CCL); }
		else { RETURN(NCCL); } }
D 4
<chc>\n		{ yyerror("newline in character class"); lineno++; BEGIN A; }
E 4
I 4
<chc>\n		{ yyerror("newline in character class"); lineno++; BEGIN INITIAL; }
E 4
<chc>.		{ CADD; }

%%

D 4
input()
{
	register c;
	extern char *lexprog;

	if (yysptr > yysbuf)
		c = U(*--yysptr);
	else if (yyin == NULL)
		c = *lexprog++;
	else
		c = getc(yyin);
	if (c == '\n')
		yylineno++;
	else if (c == EOF)
		c = 0;
	return(c);
}

E 4
startreg()
{
	BEGIN reg;
I 3
}

ptoken(n)
{
	extern struct tok {
		char *tnm;
		int yval;
	} tok[];
D 4
	extern char yytext[];
E 4
	extern int yylval;

	printf("lex:");
	if (n < 128) {
		printf(" %c\n",n);
		return;
	}
	if (n <= 256 || n >= LASTTOKEN) {
		printf("? %o\n",n);
		return;
	}
	printf(" %s",tok[n-257].tnm);
	switch (n) {

	case RELOP:
	case MATCHOP:
	case ASGNOP:
	case STRING:
	case FIELD:
	case VAR:
	case NUMBER:
	case FNCN:
		printf(" (%s)", yytext);
		break;

	case CHAR:
		printf(" (%o)", yylval);
		break;
	}
	putchar('\n');
E 3
}
E 1
