h36839
s 00003/00000/00055
d D 8.3 95/05/04 18:02:55 christos 6 5
c merged netbsd changes
e
s 00023/00028/00032
d D 8.2 95/04/27 14:18:11 bostic 5 4
c Don't dump core when evaluating X % 0.
c Simplify lexer by using %prec feature in yacc grammar.
c Implement most of the operators required by POSIX.2.
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00000/00000/00060
d D 8.1 93/05/31 15:29:34 bostic 4 3
c yank to 8.1
e
s 00015/00000/00045
d D 5.2 93/05/31 15:28:51 bostic 3 1
c add copyright notices, SCCS headers, yank to 8.1
e
s 00014/00000/00045
d R 8.1 93/05/31 15:25:24 bostic 2 1
c add copyright notices, SCCS headers, yank to 8.1
e
s 00045/00000/00000
d D 5.1 92/06/23 18:44:57 marc 1 0
c date and time created 92/06/23 18:44:57 by marc
e
u
U
t
T
I 1
%{
I 3
/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 6
#include <unistd.h>
E 6
E 3
#include "y.tab.h"
I 6
#include "error.h"
E 6
I 3

E 3
extern yylval;
extern char *arith_buf, *arith_startbuf;
D 5
int arith_wasoper;
E 5
#undef YY_INPUT
#define YY_INPUT(buf,result,max) \
	result = (*buf = *arith_buf++) ? 1 : YY_NULL;
%}

%%
[ \t\n]	{ ; }
D 5
[0-9]+	{ arith_wasoper = 0; yylval = atol(yytext); return(ARITH_NUM); }
"("	{ arith_wasoper = 1; return(ARITH_LPAREN); }
")"	{ arith_wasoper = 0; return(ARITH_RPAREN); }
"||"	{ arith_wasoper = 1; return(ARITH_OR); }
"&&"	{ arith_wasoper = 1; return(ARITH_AND); }
"=="	{ arith_wasoper = 1; return(ARITH_EQ); }
">"	{ arith_wasoper = 1; return(ARITH_GT); }
">="	{ arith_wasoper = 1; return(ARITH_GEQ); }
"<"	{ arith_wasoper = 1; return(ARITH_LT); }
"<="	{ arith_wasoper = 1; return(ARITH_LEQ); }
"!="	{ arith_wasoper = 1; return(ARITH_NEQ); }
"*"	{ arith_wasoper = 1; return(ARITH_MULT); }
"/"	{ arith_wasoper = 1; return(ARITH_DIV); }
"%"	{ arith_wasoper = 1; return(ARITH_REM); }
"+"	{ if (!arith_wasoper) {	/* ignore unary plus */
		arith_wasoper = 1; 
		return(ARITH_ADD);
	 } 
	}	
"-"	{ if (arith_wasoper) {
		return(ARITH_UNARYMINUS);
	  } else {
		arith_wasoper = 1;
		return(ARITH_SUBT);
	  }
	}
"!"	{ arith_wasoper = 1; return(ARITH_NOT); }
E 5
I 5
[0-9]+	{ yylval = atol(yytext); return(ARITH_NUM); }
"("	{ return(ARITH_LPAREN); }
")"	{ return(ARITH_RPAREN); }
"||"	{ return(ARITH_OR); }
"&&"	{ return(ARITH_AND); }
"|"	{ return(ARITH_BOR); }
"^"	{ return(ARITH_BXOR); }
"&"	{ return(ARITH_BAND); }
"=="	{ return(ARITH_EQ); }
"!="	{ return(ARITH_NE); }
">"	{ return(ARITH_GT); }
">="	{ return(ARITH_GE); }
"<"	{ return(ARITH_LT); }
"<="	{ return(ARITH_LE); }
"<<"	{ return(ARITH_LSHIFT); }
">>"	{ return(ARITH_RSHIFT); }
"*"	{ return(ARITH_MUL); }
"/"	{ return(ARITH_DIV); }
"%"	{ return(ARITH_REM); }
"+"	{ return(ARITH_ADD); } 
"-"	{ return(ARITH_SUB); }
"~"	{ return(ARITH_BNOT); }
"!"	{ return(ARITH_NOT); }
E 5
.	{ error("arith: syntax error: \"%s\"\n", arith_startbuf); }
%%

I 6
void
E 6
arith_lex_reset() {
	YY_NEW_FILE;
}
E 1
