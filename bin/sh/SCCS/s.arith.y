h20638
s 00004/00001/00154
d D 8.3 95/05/04 18:02:13 christos 6 5
c merged netbsd changes
e
s 00035/00023/00120
d D 8.2 95/04/27 14:18:10 bostic 5 4
c Don't dump core when evaluating X % 0.
c Simplify lexer by using %prec feature in yacc grammar.
c Implement most of the operators required by POSIX.2.
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00000/00000/00143
d D 8.1 93/05/31 15:29:33 bostic 4 3
c yank to 8.1
e
s 00013/00000/00130
d D 5.2 93/05/31 15:28:50 bostic 3 1
c add copyright notices, SCCS headers, yank to 8.1
e
s 00014/00000/00130
d R 8.1 93/05/31 15:25:23 bostic 2 1
c add copyright notices, SCCS headers, yank to 8.1
e
s 00130/00000/00000
d D 5.1 92/06/23 18:44:56 marc 1 0
c date and time created 92/06/23 18:44:56 by marc
e
u
U
t
T
I 1
D 5
%token ARITH_OR ARITH_AND ARITH_ADD ARITH_SUBT ARITH_MULT ARITH_DIV ARITH_REM ARITH_EQ ARITH_GT ARITH_GEQ ARITH_LT ARITH_LEQ ARITH_NEQ
%token ARITH_NUM ARITH_LPAREN ARITH_RPAREN ARITH_NOT ARITH_UNARYMINUS
E 5
I 5
%token ARITH_NUM ARITH_LPAREN ARITH_RPAREN 
E 5

%left ARITH_OR
%left ARITH_AND
D 5
%left ARITH_EQ ARITH_NEQ
%left ARITH_LT ARITH_GT ARITH_GEQ ARITH_LEQ
%left ARITH_ADD ARITH_SUBT
%left ARITH_MULT ARITH_DIV ARITH_REM
%left ARITH_UNARYMINUS ARITH_NOT
E 5
I 5
%left ARITH_BOR
%left ARITH_BXOR
%left ARITH_BAND
%left ARITH_EQ ARITH_NE
%left ARITH_LT ARITH_GT ARITH_GE ARITH_LE
%left ARITH_LSHIFT ARITH_RSHIFT
%left ARITH_ADD ARITH_SUB
%left ARITH_MUL ARITH_DIV ARITH_REM
%left ARITH_UNARYMINUS ARITH_UNARYPLUS ARITH_NOT ARITH_BNOT
E 5
%%

exp:	expr = {
			return ($1);
		}
	;


expr:	ARITH_LPAREN expr ARITH_RPAREN = { $$ = $2; }
D 5
	| expr ARITH_OR expr   = { $$ = $1 ? $1 : $3 ? $3 : 0; }
	| expr ARITH_AND expr   = { $$ = $1 ? ( $3 ? $3 : 0 ) : 0; }
	| expr ARITH_EQ expr   = { $$ = $1 == $3; }
	| expr ARITH_GT expr   = { $$ = $1 > $3; }
	| expr ARITH_GEQ expr   = { $$ = $1 >= $3; }
	| expr ARITH_LT expr   = { $$ = $1 < $3; }
	| expr ARITH_LEQ expr   = { $$ = $1 <= $3; }
	| expr ARITH_NEQ expr   = { $$ = $1 != $3; }
	| expr ARITH_ADD expr   = { $$ = $1 + $3; }
	| expr ARITH_SUBT expr   = { $$ = $1 - $3; }
	| expr ARITH_MULT expr   = { $$ = $1 * $3; }
	| expr ARITH_DIV expr   = {
E 5
I 5
	| expr ARITH_OR expr	= { $$ = $1 ? $1 : $3 ? $3 : 0; }
	| expr ARITH_AND expr	= { $$ = $1 ? ( $3 ? $3 : 0 ) : 0; }
	| expr ARITH_BOR expr	= { $$ = $1 | $3; }
	| expr ARITH_BXOR expr	= { $$ = $1 ^ $3; }
	| expr ARITH_BAND expr	= { $$ = $1 & $3; }
	| expr ARITH_EQ expr	= { $$ = $1 == $3; }
	| expr ARITH_GT expr	= { $$ = $1 > $3; }
	| expr ARITH_GE expr	= { $$ = $1 >= $3; }
	| expr ARITH_LT expr	= { $$ = $1 < $3; }
	| expr ARITH_LE expr	= { $$ = $1 <= $3; }
	| expr ARITH_NE expr	= { $$ = $1 != $3; }
	| expr ARITH_LSHIFT expr = { $$ = $1 << $3; }
	| expr ARITH_RSHIFT expr = { $$ = $1 >> $3; }
	| expr ARITH_ADD expr	= { $$ = $1 + $3; }
	| expr ARITH_SUB expr	= { $$ = $1 - $3; }
	| expr ARITH_MUL expr	= { $$ = $1 * $3; }
	| expr ARITH_DIV expr	= {
E 5
			if ($3 == 0)
				yyerror("division by zero");
			$$ = $1 / $3; 
			}
D 5
	| expr ARITH_REM expr   = { $$ = $1 % $3; }
E 5
I 5
	| expr ARITH_REM expr   = {
			if ($3 == 0)
				yyerror("division by zero");
			$$ = $1 % $3; 
			}
E 5
	| ARITH_NOT expr	= { $$ = !($2); }
D 5
	| ARITH_UNARYMINUS expr = { $$ = -($2); }
E 5
I 5
	| ARITH_BNOT expr	= { $$ = ~($2); }
	| ARITH_SUB expr %prec ARITH_UNARYMINUS = { $$ = -($2); }
	| ARITH_ADD expr %prec ARITH_UNARYPLUS = { $$ = $2; }
E 5
	| ARITH_NUM
	;
%%
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
E 3

#include "shell.h"
#include "error.h"
#include "output.h"
#include "memalloc.h"

char *arith_buf, *arith_startbuf;

I 6
int
E 6
arith(s)
	char *s; 
{
D 5
	extern arith_wasoper;
E 5
	long result;

D 5
	arith_wasoper = 1;
E 5
	arith_buf = arith_startbuf = s;

	INTOFF;
	result = yyparse();
	arith_lex_reset();	/* reprime lex */
	INTON;

	return (result);
}

I 6
void
E 6
yyerror(s)
	char *s;
{
D 6
	extern yytext, yylval;
E 6

	yyerrok;
	yyclearin;
	arith_lex_reset();	/* reprime lex */
	error("arithmetic expression: %s: \"%s\"", s, arith_startbuf);
}

/*
 *  The exp(1) builtin.
 */
I 6
int
E 6
expcmd(argc, argv)
I 6
	int argc;
E 6
	char **argv;
{
	char *p;
	char *concat;
	char **ap;
	long i;

	if (argc > 1) {
		p = argv[1];
		if (argc > 2) {
			/*
			 * concatenate arguments
			 */
			STARTSTACKSTR(concat);
			ap = argv + 2;
			for (;;) {
				while (*p)
					STPUTC(*p++, concat);
				if ((p = *ap++) == NULL)
					break;
				STPUTC(' ', concat);
			}
			STPUTC('\0', concat);
			p = grabstackstr(concat);
		}
	} else
		p = "";

	i = arith(p);

	out1fmt("%d\n", i);
	return (! i);
}

/*************************/
#ifdef TEST_ARITH
#include <stdio.h>
main(argc, argv)
	char *argv[];
{
	printf("%d\n", exp(argv[1]));
}
error(s)
	char *s;
{
	fprintf(stderr, "exp: %s\n", s);
	exit(1);
}
#endif
E 1
