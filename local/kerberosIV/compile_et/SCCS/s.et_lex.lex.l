h25819
s 00009/00003/00020
d D 5.2 90/06/19 19:08:14 bostic 2 1
c yylineno wasn't ever documented, and causes slow lexers;
c Rules which match newlines now explicitly update the line count.
c I changed the [ \t] rule to [ \t]+ because they're semantically
c equivalent (for this rule set) and the latter is faster, since it
c matches multiple whitespace all in one shot.  I also changed the
c semantics of strings slightly: a newline is no longer legal inside
c a string. -- from Vern Paxson
e
s 00023/00000/00000
d D 5.1 90/06/19 19:04:43 bostic 1 0
c date and time created 90/06/19 19:04:43 by bostic
e
u
U
t
T
I 1
D 2
PC	[^\"]
E 2
I 2
%{
extern int yylineno;
int yylineno = 1;
%}

PC	[^\"\n]
E 2
AN	[A-Z_a-z0-9]
%%

error_table	return ERROR_TABLE;
et		return ERROR_TABLE;
error_code	return ERROR_CODE_ENTRY;
ec		return ERROR_CODE_ENTRY;
end		return END;

D 2
[\t\n ]		;
E 2
I 2
[\t ]+		;
\n		++yylineno;
E 2

\"{PC}*\"	{ register char *p; yylval.dynstr = ds(yytext+1);
		  if (p=rindex(yylval.dynstr, '"')) *p='\0';
		  return QUOTED_STRING;
		}

{AN}*	{ yylval.dynstr = ds(yytext); return STRING; }

D 2
#.*\n		;
E 2
I 2
#.*\n		++yylineno;
E 2

.		{ return (*yytext); }
%%
E 1
