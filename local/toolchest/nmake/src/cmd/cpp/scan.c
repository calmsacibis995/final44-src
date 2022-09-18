/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 * C preprocessor #if expression lexical analyzer
 *
 * AT&T Bell Laboratories
 */

#include "cpp.h"
#include "cpy.h"

static int	tobinary();
static int	getarg();

int
yylex()
{
	static char	*op2[] = {"||",  "&&" , ">>", "<<", ">=", "<=", "!=", "=="};
	static int	lex2[] = {OROR, ANDAND,  RS,   LS,   GE,   LE,   NE,   EQ};
	static char	yyname1[MAXPATH], yyname2[MAXPATH];
	register char	*s;
	register int	savc;
	int		lex;
	register char	**p2;

	for (;;)
	{
		newp = skipbl(newp);
		if (*inp == '\n')
		{
			lex = STOP;
			break;
		}
		savc = *newp;
		*newp = '\0';
		if (*inp == '/' && *(inp + 1) == '*')
		{
			/*
			 * found a comment with -C option, still toss here
			 */

			*newp = savc;
			outp = inp = newp;
			continue;
		}

		/*
		 * check for builtin args
		 */
		
		if (skip && *inp == '(' && savc != '"' && savc != '<')
		{
			*newp = savc;
			lex = getarg(yyname2, ')');
			savc = *newp;
			goto ret;
		}
#if DEBUG
		error(-3, "token = `%s'", inp);
#endif

		/*
		 * check 2-char ops
		 */

		for (p2 = op2 + 8; --p2 >= op2;)
			if ((*p2)[0] == *inp && (*p2)[1] == *(inp + 1))
			{
				lex = lex2[ p2 - op2 ];
				goto ret;
			}

		if (*inp != '<' || !skip)
		{
			/*
			 * check 1-char ops
			 */

			s = "+-*/%<>&^|?:!~(),";
			while (*s)
				if (*s++ == *inp)
				{
					lex = *inp;
					goto ret;
				}
		}
		if (*inp >= '0' && *inp <= '9')
		{
			/*
			 * number
			 */

			if (*inp != '0')
				yylval.number = tobinary(inp, 10);
			else if (*(inp + 1) == 'x' || *(inp + 1) == 'X')
				yylval.number = tobinary(inp, 16);
			else
				yylval.number = tobinary(inp, 8);
			lex = NUMBER;
		}
		else if (isid(*inp))
		{
			if (skip) yylval.string = yyname2;
			else
			{
				skip++;
				yylval.string = yyname1;
			}
			if (newp > inp + maxsym)
			{
				char	save;

				save = *(inp + maxsym);
				*(inp + maxsym) = '\0';
				strcpy(yylval.string, inp);
				*(inp + maxsym) = save;
			}
			else strcpy(yylval.string, inp);
			lex = NAME;
		}
		else if (*inp == '\'')
		{
			/*
			 * character constant
			 */

			lex = NUMBER;
			if (*(inp + 1) == '\\')
			{
				/*
				 * escaped
				 */

				if (*(newp - 1) == '\'') *(newp - 1) = '\0';
				switch (*(inp + 2))
				{
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					yylval.number = tobinary(inp + 2, 8);
					break;
				
				case 'a':
					yylval.number = '\07';	/* intermediate */
					break;
				
				case 'b':
					yylval.number = '\b';
					break;
				
				case 'n':
					yylval.number = '\n';
					break;
				
				case 'r':
					yylval.number = '\r';
					break;
				
				case 't':
					yylval.number = '\t';
					break;
				
				case 'v':
					yylval.number = '\v';
					break;
				
				default:
					yylval.number = *(inp + 2);
					break;
				}
			}
			else yylval.number = *(inp + 1);
		}
		else if (*inp == '\\' && *(inp + 1) == '\n')
		{
			*newp = savc;
			continue;
		}
		else if (*inp == '"' && skip)
		{
			yylval.string = ++inp;
			lex = NAME;
			if (*(newp - 1) == '"') *(newp - 1) = '\0';
		}
		else if (*inp == '<' && skip)
		{
			*newp = savc;
			lex = getarg(yyname2, '>');
			savc = *newp;
		}
		else
		{
			*newp = savc;
			yyerror("invalid character");
			continue;
		}
	ret:
		*newp = savc;
		outp = inp = newp;
		break;
	}
	return(lex);
}

static int
tobinary(s, b)
register char	*s;
int		b;
{
	register int	c, n;
	int		t;

	n = 0;
	while (c = *s++)
	{
		switch(c)
		{
		case '0': case '1': case '2': case '3': case '4': 
		case '5': case '6': case '7': case '8': case '9': 
			t = c - '0';
			break;
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': 
			t = (c - 'a') + 10;
			if (b > 10) break;
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': 
			t = (c - 'A') + 10;
			if (b > 10) break;
		default:
			t = -1;
			if (c == 'l' || c == 'L' || c == 'u' || c == 'U')
				if (*s == '\0')
					break;
			yyerror("invalid number");
		}
		if (t < 0) break;
		n = n * b + t;
	}
	return(n);
}

/*
 * get a builtin argument
 */

static int
getarg(buf, end)
char	*buf;
int	end;
{
	register char	*s;

	yylval.string = s = buf;
	if (end == '>') *s++ = WARN;
	for (;;)
	{
		outp = inp = newp;
		newp = cotoken(newp);
		if (*inp == '\n') return(STOP);
		if (*inp == end)
		{
			*s = '\0';
#if DEBUG
			error(-3, "arg = `%s'", buf);
#endif
			return(NAME);
		}
		while (inp < newp) *s++ = *inp++;
	}
}
