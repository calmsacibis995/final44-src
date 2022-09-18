h51566
s 00001/00001/00094
d D 1.2 88/07/22 17:55:37 bostic 2 1
c ANSI scoping
e
s 00095/00000/00000
d D 1.1 82/12/15 23:18:56 clemc 1 0
c date and time created 82/12/15 23:18:56 by clemc
e
u
U
t
Virgin BTL M4 as sent out in 4.1
T
I 1
/* %W% (Berkeley) %G% */
%{
extern long	evalval;
#define	YYSTYPE	long
%}

%term DIGITS
%left '|'
%left '&'
%right '!'
%nonassoc GT GE LT LE NE EQ
%left '+' '-'
%left '*' '/' '%'
%right POWER
%right UMINUS
%%

s	: e	={ evalval = $1; }
	|	={ evalval = 0; }
	;

e	: e '|' e	={ $$ = ($1!=0 || $3!=0) ? 1 : 0; }
	| e '&' e	={ $$ = ($1!=0 && $3!=0) ? 1 : 0; }
	| '!' e		={ $$ = $2 == 0; }
	| e EQ e	={ $$ = $1 == $3; }
	| e NE e	={ $$ = $1 != $3; }
	| e GT e	={ $$ = $1 > $3; }
	| e GE e	={ $$ = $1 >= $3; }
	| e LT e	={ $$ = $1 < $3; }
	| e LE e	={ $$ = $1 <= $3; }
	| e '+' e	={ $$ = ($1+$3); }
	| e '-' e	={ $$ = ($1-$3); }
	| e '*' e	={ $$ = ($1*$3); }
	| e '/' e	={ $$ = ($1/$3); }
	| e '%' e	={ $$ = ($1%$3); }
	| '(' e ')'	={ $$ = ($2); }
	| e POWER e	={ for ($$=1; $3-->0; $$ *= $1); }	
	| '-' e %prec UMINUS	={ $$ = $2-1; $$ = -$2; }
	| '+' e %prec UMINUS	={ $$ = $2-1; $$ = $2; }
	| DIGITS	={ $$ = evalval; }
	;

%%

I 2
extern char *pe;
E 2
yylex() {
D 2
	extern char *pe;
E 2

	while (*pe==' ' || *pe=='\t' || *pe=='\n')
		pe++;
	switch(*pe) {
	case '\0':
	case '+':
	case '-':
	case '/':
	case '%':
	case '(':
	case ')':
		return(*pe++);
	case '^':
		pe++;
		return(POWER);
	case '*':
		return(peek('*', POWER, '*'));
	case '>':
		return(peek('=', GE, GT));
	case '<':
		return(peek('=', LE, LT));
	case '=':
		return(peek('=', EQ, EQ));
	case '|':
		return(peek('|', '|', '|'));
	case '&':
		return(peek('&', '&', '&'));
	case '!':
		return(peek('=', NE, '!'));
	default:
		evalval = 0;
		while (*pe >= '0' && *pe <= '9')
			evalval = evalval*10 + *pe++ - '0';
		return(DIGITS);
	}
}

peek(c, r1, r2)
{
	if (*++pe != c)
		return(r2);
	++pe;
	return(r1);
}

yyerror(s)
char *s;
{
}
E 1
