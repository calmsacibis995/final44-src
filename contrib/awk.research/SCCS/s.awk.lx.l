h10913
s 00054/00048/00236
d D 8.2 94/01/04 12:01:23 bostic 2 1
c Vern Paxson's changes to make Research Awk run with flex on 4.4BSD
e
s 00284/00000/00000
d D 8.1 94/01/04 11:07:41 bostic 1 0
c date and time created 94/01/04 11:07:41 by bostic
e
u
U
t
T
I 1
%Start A str sc reg comment

%{
/****************************************************************
Copyright (C) AT&T 1993
All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name of AT&T or any of its entities
not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

AT&T DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
IN NO EVENT SHALL AT&T OR ANY OF ITS ENTITIES BE LIABLE FOR ANY
SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
THIS SOFTWARE.
****************************************************************/

D 2
/* some of this depends on behavior of lex that
   may not be preserved in other implementations of lex.
*/

#undef	input	/* defeat lex */
#undef	unput

E 2
#include <stdlib.h>
#include <string.h>
#include "awk.h"
#include "y.tab.h"

extern YYSTYPE	yylval;
extern int	infunc;

int	lineno	= 1;
int	bracecnt = 0;
int	brackcnt  = 0;
int	parencnt = 0;
#define DEBUG
#ifdef	DEBUG
#	define	RET(x)	{if(dbg)printf("lex %s [%s]\n", tokname(x), yytext); return(x); }
#else
#	define	RET(x)	return(x)
#endif

#define	CADD	cbuf[clen++] = yytext[0]; \
		if (clen >= CBUFLEN-1) { \
			ERROR "string/reg expr %.30s... too long", cbuf SYNTAX; \
			BEGIN A; \
		}

uchar	cbuf[CBUFLEN];
uchar	*s;
int	clen, cflag;
I 2

/* some of this depends on behavior of lex that
   may not be preserved in other implementations of lex.
*/

static	int	my_input( YY_CHAR *buf, int max_size );

#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) result = my_input(buf, max_size);

#undef YY_USER_INIT
#define YY_USER_INIT init_input_source();
E 2
%}

A	[a-zA-Z_]
B	[a-zA-Z0-9_]
D	[0-9]
O	[0-7]
H	[0-9a-fA-F]
WS	[ \t]

%%
D 2
	switch (yybgin-yysvec-1) {	/* witchcraft */
E 2
I 2
	switch ((yy_start - 1) / 2) {	/* witchcraft */
E 2
	case 0:
		BEGIN A;
		break;
	case sc:
		BEGIN A;
		RET('}');
	}

<A>\n		{ lineno++; RET(NL); }
<A>#.*		{ ; }	/* strip comments */
<A>{WS}+	{ ; }
<A>;		{ RET(';'); }

<A>"\\"\n	{ lineno++; }
<A>BEGIN	{ RET(XBEGIN); }
<A>END		{ RET(XEND); }
<A>func(tion)?	{ if (infunc) ERROR "illegal nested function" SYNTAX; RET(FUNC); }
<A>return	{ if (!infunc) ERROR "return not in function" SYNTAX; RET(RETURN); }
<A>"&&"		{ RET(AND); }
<A>"||"		{ RET(BOR); }
<A>"!"		{ RET(NOT); }
<A>"!="		{ yylval.i = NE; RET(NE); }
<A>"~"		{ yylval.i = MATCH; RET(MATCHOP); }
<A>"!~"		{ yylval.i = NOTMATCH; RET(MATCHOP); }
<A>"<"		{ yylval.i = LT; RET(LT); }
<A>"<="		{ yylval.i = LE; RET(LE); }
<A>"=="		{ yylval.i = EQ; RET(EQ); }
<A>">="		{ yylval.i = GE; RET(GE); }
<A>">"		{ yylval.i = GT; RET(GT); }
<A>">>"		{ yylval.i = APPEND; RET(APPEND); }
<A>"++"		{ yylval.i = INCR; RET(INCR); }
<A>"--"		{ yylval.i = DECR; RET(DECR); }
<A>"+="		{ yylval.i = ADDEQ; RET(ASGNOP); }
<A>"-="		{ yylval.i = SUBEQ; RET(ASGNOP); }
<A>"*="		{ yylval.i = MULTEQ; RET(ASGNOP); }
<A>"/="		{ yylval.i = DIVEQ; RET(ASGNOP); }
<A>"%="		{ yylval.i = MODEQ; RET(ASGNOP); }
<A>"^="		{ yylval.i = POWEQ; RET(ASGNOP); }
<A>"**="	{ yylval.i = POWEQ; RET(ASGNOP); }
<A>"="		{ yylval.i = ASSIGN; RET(ASGNOP); }
<A>"**"		{ RET(POWER); }
<A>"^"		{ RET(POWER); }

<A>"$"{D}+	{ yylval.cp = fieldadr(atoi(yytext+1)); RET(FIELD); }
<A>"$NF"	{ unputstr("(NF)"); return(INDIRECT); }
D 2
<A>"$"{A}{B}*	{ int c, n;
		  c = input(); unput(c);
		  if (c == '(' || c == '[' || infunc && (n=isarg(yytext+1)) >= 0) {
			unputstr(yytext+1);
E 2
I 2
<A>"$"{A}{B}*	{
		  int c;
		  char *yytext_copy = strdup(yytext);
		  c = input(); unput(c);	/* look for '(' or '[' */
		  if (c == '(' || c == '[' ||
		      infunc && isarg(yytext_copy+1) >= 0) {
			  unputstr(yytext_copy+1);
			  free(yytext_copy);
E 2
			return(INDIRECT);
		  } else {
D 2
			yylval.cp = setsymtab(yytext+1,"",0.0,STR|NUM,symtab);
E 2
I 2
			  yylval.cp =
				setsymtab(yytext_copy+1,"",0.0,STR|NUM,symtab);
			  free(yytext_copy);
E 2
			RET(IVAR);
		  }
		}
<A>"$"		{ RET(INDIRECT); }
<A>NF		{ yylval.cp = setsymtab(yytext, "", 0.0, NUM, symtab); RET(VARNF); }

<A>({D}+("."?){D}*|"."{D}+)((e|E)("+"|-)?{D}+)?	{
		  yylval.cp = setsymtab(yytext, tostring(yytext), atof(yytext), CON|NUM, symtab);
		/* should this also have STR set? */
		  RET(NUMBER); }

<A>while	{ RET(WHILE); }
<A>for		{ RET(FOR); }
<A>do		{ RET(DO); }
<A>if		{ RET(IF); }
<A>else		{ RET(ELSE); }
<A>next		{ RET(NEXT); }
<A>exit		{ RET(EXIT); }
<A>break	{ RET(BREAK); }
<A>continue	{ RET(CONTINUE); }
<A>print	{ yylval.i = PRINT; RET(PRINT); }
<A>printf	{ yylval.i = PRINTF; RET(PRINTF); }
<A>sprintf	{ yylval.i = SPRINTF; RET(SPRINTF); }
<A>split	{ yylval.i = SPLIT; RET(SPLIT); }
<A>substr	{ RET(SUBSTR); }
<A>sub		{ yylval.i = SUB; RET(SUB); }
<A>gsub		{ yylval.i = GSUB; RET(GSUB); }
<A>index	{ RET(INDEX); }
<A>match	{ RET(MATCHFCN); }
<A>in		{ RET(IN); }
<A>getline	{ RET(GETLINE); }
<A>close	{ RET(CLOSE); }
<A>delete	{ RET(DELETE); }
<A>length	{ yylval.i = FLENGTH; RET(BLTIN); }
<A>log		{ yylval.i = FLOG; RET(BLTIN); }
<A>int		{ yylval.i = FINT; RET(BLTIN); }
<A>exp		{ yylval.i = FEXP; RET(BLTIN); }
<A>sqrt		{ yylval.i = FSQRT; RET(BLTIN); }
<A>sin		{ yylval.i = FSIN; RET(BLTIN); }
<A>cos		{ yylval.i = FCOS; RET(BLTIN); }
<A>atan2	{ yylval.i = FATAN; RET(BLTIN); }
<A>system	{ yylval.i = FSYSTEM; RET(BLTIN); }
<A>rand		{ yylval.i = FRAND; RET(BLTIN); }
<A>srand	{ yylval.i = FSRAND; RET(BLTIN); }
<A>toupper	{ yylval.i = FTOUPPER; RET(BLTIN); }
<A>tolower	{ yylval.i = FTOLOWER; RET(BLTIN); }
<A>fflush	{ yylval.i = FFLUSH; RET(BLTIN); }

<A>{A}{B}*	{ int n, c;
I 2
		  char *yytext_copy = strdup(yytext);
E 2
		  c = input(); unput(c);	/* look for '(' */
D 2
		  if (c != '(' && infunc && (n=isarg(yytext)) >= 0) {
E 2
I 2
		  if (c != '(' && infunc && (n=isarg(yytext_copy)) >= 0) {
E 2
			yylval.i = n;
I 2
			free(yytext_copy);
E 2
			RET(ARG);
		  } else {
D 2
			yylval.cp = setsymtab(yytext,"",0.0,STR|NUM,symtab);
E 2
I 2
			yylval.cp =
				setsymtab(yytext_copy,"",0.0,STR|NUM,symtab);
			free(yytext_copy);
E 2
			if (c == '(') {
				RET(CALL);
			} else {
				RET(VAR);
			}
		  }
		}
I 2

E 2
<A>\"		{ BEGIN str; clen = 0; }

<A>"}"		{ if (--bracecnt < 0) ERROR "extra }" SYNTAX; BEGIN sc; RET(';'); }
<A>"]"		{ if (--brackcnt < 0) ERROR "extra ]" SYNTAX; RET(']'); }
<A>")"		{ if (--parencnt < 0) ERROR "extra )" SYNTAX; RET(')'); }

<A>.		{ if (yytext[0] == '{') bracecnt++;
		  else if (yytext[0] == '[') brackcnt++;
		  else if (yytext[0] == '(') parencnt++;
		  RET(yylval.i = yytext[0]); /* everything else */ }

<reg>\\.	{ cbuf[clen++] = '\\'; cbuf[clen++] = yytext[1]; }
<reg>\n		{ ERROR "newline in regular expression %.10s...", cbuf SYNTAX; lineno++; BEGIN A; }
<reg>"/"	{ BEGIN A;
		  cbuf[clen] = 0;
		  yylval.s = tostring(cbuf);
		  unput('/');
		  RET(REGEXPR); }
<reg>.		{ CADD; }

<str>\"		{ BEGIN A;
		  cbuf[clen] = 0; s = tostring(cbuf);
		  cbuf[clen] = ' '; cbuf[++clen] = 0;
		  yylval.cp = setsymtab(cbuf, s, 0.0, CON|STR, symtab);
		  RET(STRING); }
<str>\n		{ ERROR "newline in string %.10s...", cbuf SYNTAX; lineno++; BEGIN A; }
<str>"\\\""	{ cbuf[clen++] = '"'; }
<str>"\\"n	{ cbuf[clen++] = '\n'; }
<str>"\\"t	{ cbuf[clen++] = '\t'; }
<str>"\\"f	{ cbuf[clen++] = '\f'; }
<str>"\\"r	{ cbuf[clen++] = '\r'; }
<str>"\\"b	{ cbuf[clen++] = '\b'; }
<str>"\\"v	{ cbuf[clen++] = '\v'; }	/* these ANSIisms may not be known by */
<str>"\\"a	{ cbuf[clen++] = '\007'; }	/* your compiler. hence 007 for bell */
<str>"\\\\"	{ cbuf[clen++] = '\\'; }
<str>"\\"({O}{O}{O}|{O}{O}|{O}) { int n;
		  sscanf(yytext+1, "%o", &n); cbuf[clen++] = n; }
<str>"\\"x({H}+) { int n;	/* ANSI permits any number! */
		  sscanf(yytext+2, "%x", &n); cbuf[clen++] = n; }
<str>"\\".	{ cbuf[clen++] = yytext[1]; }
<str>.		{ CADD; }

%%

void startreg(void)	/* start parsing a regular expression */
{
	BEGIN reg;
	clen = 0;
}

D 2
/* input() and unput() are transcriptions of the standard lex
   macros for input and output with additions for error message
   printing.  God help us all if someone changes how lex works.
*/

uchar	ebuf[300];
uchar	*ep = ebuf;

input(void)	/* get next lexical input character */
E 2
I 2
static int my_input( YY_CHAR *buf, int max_size )
E 2
{
D 2
	register int c;
E 2
	extern uchar *lexprog;

D 2
	if (yysptr > yysbuf)
		c = U(*--yysptr);
	else if (lexprog != NULL) {	/* awk '...' */
		if (c = *lexprog)
			lexprog++;
	} else				/* awk -f ... */
		c = pgetc();
	if (c == '\n')
		yylineno++;
	else if (c == EOF)
		c = 0;
	if (ep >= ebuf + sizeof ebuf)
		ep = ebuf;
	return *ep++ = c;
E 2
I 2
	if ( lexprog ) {		/* awk '...' */
		int num_chars = strlen( lexprog );
		if ( num_chars > max_size )
			{
			num_chars = max_size;
			strncpy( buf, lexprog, num_chars );
E 2
}
I 2
		else
			strcpy( buf, lexprog );
		lexprog += num_chars;
		return num_chars;
E 2

D 2
void unput(int c)	/* put lexical character back on input */
{
	yytchar = c;
	if (yytchar == '\n')
		yylineno--;
	*yysptr++ = yytchar;
	if (--ep < ebuf)
		ep = ebuf + sizeof(ebuf) - 1;
E 2
I 2
	} else {			/* awk -f ... */
		int c = pgetc();
		if (c == EOF)
			return 0;
		buf[0] = c;
		return 1;
E 2
}
I 2
}
E 2

D 2

E 2
void unputstr(char *s)	/* put a string back on input */
{
	int i;

	for (i = strlen(s)-1; i >= 0; i--)
		unput(s[i]);
I 2
}

int lex_input()
{
	return input();
E 2
}
E 1
