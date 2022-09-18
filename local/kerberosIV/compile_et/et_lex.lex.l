%{
#include <sys/cdefs.h>

int yylex __P((void));
int yylook __P((void));
int yyback __P((int *, int));
int yyinput __P((void));
int yyoutput __P((int));
#ifndef FLEX_SCANNER
int yyunput __P((int));
#endif

extern int yylineno;
#ifdef bsdi
int yylineno = 1;
#endif
%}

PC	[^\"\n]
AN	[A-Z_a-z0-9]
%%

error_table	return ERROR_TABLE;
et		return ERROR_TABLE;
error_code	return ERROR_CODE_ENTRY;
ec		return ERROR_CODE_ENTRY;
end		return END;

[\t ]+		;
\n		++yylineno;

\"{PC}*\"	{ register char *p; yylval.dynstr = ds(yytext+1);
		  if (p=rindex(yylval.dynstr, '"')) *p='\0';
		  return QUOTED_STRING;
		}

{AN}*	{ yylval.dynstr = ds(yytext); return STRING; }

#.*\n		++yylineno;

.		{ return (*yytext); }
%%
