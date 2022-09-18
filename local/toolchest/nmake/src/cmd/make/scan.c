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
 * G. S. Fowler
 * AT&T Bell Laboratories
 */

/*
 * makefile lexical scanner
 */

#include "make.h"
#include "gram.h"

#define S_INIT		0	/* initial analyzer state (0!!)	*/
#define S_END		1	/* end of line			*/
#define S_EOF		2	/* end of file			*/
#define S_LINE		3	/* beginning of line		*/
#define S_NAME		4	/* scanning name		*/
#define S_VALUE		5	/* scanning variable value	*/
#define S_COMMAND	6	/* scanning rule commands	*/
#define S_ELLIPSIS	7	/* scanning `...'		*/
#define S_COMMENT	8	/* scanning a comment		*/
#define S_OP1		9	/* scanning op line		*/
#define S_OP2		10	/* scanning first op argument	*/
#define S_OP3		11	/* scanning second op argument	*/

#define MACHINE		for(;;)switch(lexstate){default:{error(INTERNAL,"unknown lexical scanner state %d",lexstate);
#define END		}}
#define NEXT(X)		(lexstate=X)
#if lint
#define STATE(X)	}case X:{
#define LEX(X,Y)	return(X)
#else
#if DEBUG
#define STATE(X)	}break;case X:message(-9,"state = %s","X"+2);{
#define LEX(X,Y)	{message(-9,"token = X%s%s",Y?" = ":null,Y?Y:null);return(X);}
#else
#define STATE(X)	}break;case X:{
#define LEX(X,Y)	return(X)
#endif
#endif

#define ungetchr(c)	(nextchr?(*--nextchr=c):(*(nextchr=buf0+(MAXCMD-1))='\0'))
#define ungetch(c)	(peekch=(c))

static char	*nextchr;		/* next char for getchr()	*/
static char	*nextch;		/* next char for getch()	*/
static char	*lastline;		/* last line from getlin()	*/

static int	peekch;			/* pushback char for getch()	*/

static char	*yyop1;			/* pointer to $< op text	*/
static char	*yyop2;			/* pointer to $> op text	*/

static struct ruleinfo	*yyop;		/* operator rule		*/

static int	quote;			/* quoting state		*/
static int	lexstate;		/* lexical analyzer state	*/

int		yyline;
FILE		*yyinput;
char		*yyfile;
char		*oyyfile;

static int	getchr();
static char	*getlin();
static int	getch();

/*
 * return next lexical item for yyparse()
 */

int
yylex()
{
	register int	c, paren;
	register char	*s, *t, *u;
	struct ruleinfo	*r;
	struct varinfo	*v;
	int		unspace;
	static int	term;

	MACHINE

	STATE(S_INIT)

		term = C_TERMINAL | C_COLEQU;
		switch (c = getchr())
		{

		case '{':
			quote++;
		case ' ':
		case '\t':
			NEXT(S_COMMAND);
			break;
		
		case EOF:
			NEXT(S_EOF);
			break;

		default:
			if (quote)
			{
				ungetchr(c);
				NEXT(S_COMMAND);
			}
			else NEXT(S_LINE);
			break;
		}
	
	STATE(S_END)

		NEXT(S_INIT);
		LEX(';', 0);
	
	STATE(S_EOF)

		NEXT(S_INIT);
		LEX(0, 0);

	STATE(S_LINE)

		if (yyop) NEXT(S_OP1);
		else switch (c)
		{

		case ' ':
		case '\t':
		case '\v':
			c = getchr();
			break;
		
		case '{':
			quote++;
			NEXT(S_COMMAND);
			break;

		case ';':
		case '\n':
			NEXT(S_END);
			break;
		
		case EOF:
			NEXT(S_EOF);
			break;

		default:
			NEXT(S_NAME);
			ungetchr(c);
			LEX(';', 0);
		}

	STATE(S_NAME)

		switch (c = getchr())
		{

		case COMMENT:
			NEXT(S_COMMENT);
			break;

		case ' ':
		case '\t':
		case '\v':
			break;
		
		case '{':
			quote++;
			NEXT(S_END);
			break;

		case ';':
			while ((c = getchr()) != EOF && (ctype[c] & C_SPACE));
			if (c == EOF) NEXT(S_EOF);
			else
			{
				NEXT(S_END);
				ungetchr(c);
				ungetchr('\t');
			}
			break;

		case '\n':
			NEXT(S_END);
			break;

		case EOF:
			NEXT(S_EOF);
			break;

		case ':':
			if (term & C_COLEQU)
			{
				term &= ~C_COLEQU;
				if ((c = getchr()) == '=')
				{
					NEXT(S_VALUE);
					LEX('=', 0);
				}
				else
				{
					ungetchr(c);
					LEX(':', 0);
				}
			}
			/* fall through ... */

		case '=':
			if (term & C_COLEQU)
			{
				term &= ~C_COLEQU;
				NEXT(S_VALUE);
				LEX('=', 0);
			}
			/* fall through ... */

		case '+':
			if (term & C_COLEQU)
			{
				if ((c = getchr()) == '=')
				{
					term &= ~C_COLEQU;
					NEXT(S_VALUE);
					LEX(APPEND, 0);
				}
				else
				{
					ungetchr(c);
					c = '+';
				}
			}
			/* fall through ... */

		default:
			for (paren = quote = 0, s = buf2; c != EOF; c = getchr())
			{
				if (c == '"') quote = !quote;
				else
				{
					if (c == '(') paren++;
					else if (c == ')') paren--;
					else if (c == '\\')
					{
						if (!(ctype[c = getchr()] & term))
							*s++ = '\\';
					}
					else if (!paren && !quote && (ctype[c] & term)) break;
					*s++ = c;
				}
			}
			if (quote) error(2, "unbalanced `\"' in name");
			if (c == EOF) NEXT(S_EOF);
			else ungetchr(c);
			*s = '\0';
			yylval.string = (r = getrule(buf2)) ? r->name : (v = getvar(buf2)) ? v->name : COPY(buf2);
			LEX(NAME, buf2);
		}

	STATE(S_VALUE)

		while (ctype[c = getchr()] & C_SPACE);
		for (s = buf2; c != '\n' && c != EOF; c = getchr())
		{
			if (c == COMMENT && s > buf2 && (ctype[s[-1]] & C_SPACE)) break;
			*s++ = c;
		}
		if (c == EOF) NEXT(S_EOF);
		else if (c == COMMENT) NEXT(S_COMMENT);
		else NEXT(S_END);
		*s = '\0';
		yylval.string = COPY(buf2);
		LEX(VALUE, buf2);

	STATE(S_COMMAND)

		NEXT(S_END);
		if (!quote)
		{
			while ((c = getchr()) != EOF && (ctype[c] & C_SPACE));
			if (c == '{') quote++;
			else ungetchr(c);
		}
		unspace = quote;
		for (s = t = buf2; (c = getchr()) != EOF;)
		{
			*s++ = c;
			if (c == '\n')
			{
				for (u = t; u < s && (ctype[*u] & C_SPACE); u++);
				if (u < s - 3 && !strncmp(u, "...", 3))
				{
					NEXT(S_ELLIPSIS);
					if (t > buf2) t--;
					s = t;
					break;
				}
				if (!quote && !(ctype[c = getchr()] & C_SPACE))
				{
					ungetchr(c);
					s--;
					break;
				}
				t = s;
			}
			else if (quote)
			{
				if (c == '{') quote++;
				else if (c == '}' && !--quote)
				{
					s--;
					break;
				}
			}
		}
		if (c == EOF)
		{
			if (quote < 0) error(2, "%d extra }%s found in command list", -quote, quote == -1 ? null : "'s");
			else if (quote > 0) error(2, "%d more }%s needed to balance command list", quote, quote == 1 ? null : "'s");
			NEXT(S_EOF);
		}
		*s = '\0';

		/*
		 * remove one leading and one trailing blank line
		 */
		
		for (t = buf2; ctype[*t] & C_SPACE; t++);
		if (*t == '\n') t++;
		else t = buf2;
		if (unspace) while (*t && (ctype[*t] & C_SPACE)) t++;
		for (s--; s > t && (ctype[*s] & C_SPACE); s--);
		if (*s == '\n') *s = '\0';
		yylval.string = COPY(t);
		LEX(COMMANDS, t);

	STATE(S_ELLIPSIS)

		NEXT(S_INIT);
		LEX(ELLIPSIS, 0);
	
	STATE(S_COMMENT)

		while ((c = getchr()) != '\n' && c != EOF);
		if (c == EOF) NEXT(S_EOF);
		else NEXT(S_END);
	
	STATE(S_OP1)

		NEXT(S_OP2);
		LEX(';', 0);
	
	STATE(S_OP2)

		NEXT(S_OP3);
		for (s = yyop2 - 2; s > yyop1 && isspace(*(s - 1)); s--);
		*s = '\0';
		yylval.string = COPY(yyop1);
		LEX(VALUE, yylval.string);

	STATE(S_OP3)

		NEXT(S_VALUE);
		nextchr = yyop2;
		yylval.rule = yyop;
		yyop = (struct ruleinfo*)0;
		LEX(OP, yylval.rule->name);

	END
}

/*
 * buffered character input
 */

static int
getchr()
{
	if (!nextchr && !(nextchr = getlin())) return(EOF);
	else if (*nextchr) return(*nextchr++);
	else
	{
		nextchr = (char*)0;
		return('\n');
	}
}

/*
 * read the next line from the current input stream
 * `\<newline>' joins the current and next line, separated by one space
 * `# <line> "<file>"' preprocessor lines are interpreted
 * blank lines are gobbled
 */

static char*
getlin()
{
	register char	*s;
	register int	c, exp, par, quo;
	char		*x;
	int		bra, dol, tst;
	struct ruleinfo	*r;
	static char	file[MAXNAME];
	static int	lastlast = EOF;

 gobble:
	c = getch();
	if (c == '\n' || lastlast == EOF || lastlast == '\n')
	{
		while (c == SALT || c == '\n')
		{
			if (lastlast == '\n') yyline++;
			else lastlast = '\n';
			if (c == SALT)
			{
				while ((c = getch()) != EOF && (ctype[c] & C_SPACE));
				if (isdigit(c))
				{
					register int	n = 0;

					while (isdigit(c))
					{
						n = n * 10 + c - '0';
						c = getch();
					}
					while (c != EOF && (ctype[c] & C_SPACE)) c = getch();
					if (c == '"')
					{
						s = file;
						while ((c = getch()) != '"' && c != '\n' && c != EOF)
							*s++ = c;
						if (c == '"')
						{
							*s = '\0';
							yyline = n - 1;
							if (!*file) yyfile = oyyfile;
							else yyfile = file;

							/*
							 * add to make object dependencies
							 */

							if (!state.builtin && (r = makerule(file)) && r->status == NOTYET)
							{
								r->status = UPDATE;
								r->time = NOTIME;
								state.dependencies = cons((GENERIC)r, state.dependencies);
							}
						}
					}
				}
				while (c != EOF && c != '\n') c = getch();
			}
			c = getch();
		}
	}
	s = x = buf0;
	bra = tst = quote || c == '{';
	dol = par = quo = 0;
	exp = (c == EOF || c == '\n' || (ctype[c] & C_SPACE) || bra) ? -1 : 0;
	while (c != EOF && c != '\n')
	{
		if ((ctype[c] & C_OP1) && exp != -1 && !par && !quo)
		{
			char	op[3];

			if (ctype[op[1] = getch()] & C_OP2)
			{
				op[0] = c;
				op[2] = '\0';
				if (yyop = getrule(op))
				{
					exp = -1;
					yyop1 = buf0;
					*s++ = op[0];
					*s++ = op[1];
					yyop2 = s;
					c = getch();
					continue;
				}
			}
			else (void)ungetch(op[1]);
		}
		switch (c)
		{
		case '\\':
			if ((c = getch()) == '\n')
			{
				yyline++;
				while ((c = getch()) != EOF && (ctype[c] & C_SPACE));
				*s++ = ' ';
				continue;
			}
			else *s++ = '\\';
			break;
		case '/':
			if (!par && !quo)
			{
				/*
				 * eat C style comments
				 */
				
				if ((c = getch()) == '*')
				{
					while ((c = getch()) != EOF)
					{
						if (c == '*')
						{
							if ((c = getch()) == '/') break;
							(void)ungetch(c);
						}
						else if (c == '\n') yyline++;
					}
					c = getch();
					continue;
				}
				else if (c == '/' && (s == buf0 || (ctype[*(s - 1)] & C_SPACE)))
				{
					while ((c = getch()) != EOF && c != '\n');
					continue;
				}
				else
				{
					*s++ = '/';
					continue;
				}
			}
			break;
		case COMMENT:
			if (!par && !quo && (s == buf0 || (ctype[*(s - 1)] & C_SPACE)))
			{
				while ((c = getch()) != EOF && c != '\n');
				continue;
			}
			break;
		case ':':
			if (!par && !quo && !exp && !bra)
			{
				*s++ = c;
				bra = (c = getch()) != '=';
				exp = 1;
				continue;
			}
			break;
		case '+':
			if (!par && !quo && !exp)
			{
				*s++ = c;
				if ((c = getch()) == '=') exp = 1;
				continue;
			}
			break;
		case '=':
			if (!par && !quo && !exp) exp = -1;
			break;
		case '$':
			dol = 1;
			break;
		case '(':
			if (!quo) par++;
			break;
		case ')':
			if (!quo && !--par && !tst && buf0[0] == '$')
			{
				tst = buf0[1] == '$';
				*s++ = c;
				*s = '\0';
				s = x = expand(strcpy(buf1, buf0), buf0);
				if ((c = buf0[0]) == COMMENT) s = buf0;
				else c = getch();
				continue;
			}
			break;
		case '"':
			quo = !quo;
			break;
		case '{':
			if (bra && !par && !quo)
			{
				if (exp == 1 && !quote)
				{
					(void)ungetch(c);
					c = EOF;
					continue;
				}
				quote++;
			}
			break;
		case '}':
			if (bra && !par && !quo)
			{
				quote--;
				if (!quote)
				{
					*s++ = c;
					c = EOF;
					continue;
				}
			}
			break;
		}
		*s++ = c;
		c = getch();
	}
	if (lastlast == '\n') yyline++;
	lastlast = c;
	if (c == EOF && s == buf0) return(lastline = (char*)0);

	/*
	 * remove trailing space
	 */

	while (s > buf0 && (ctype[*(s - 1)] & C_SPACE)) s--;
	if (s <= buf0) goto gobble;
	*s = '\0';

	/*
	 * check for variable expansion
	 */

	if (dol && exp == 1)
	{
		s = buf1;
		if (x > buf0)
		{
			register char	*t;

			for (t = buf0; t < x; *s++ = *t++);
		}
		(void)expand(x, s);
		s = buf1;
	}
	else s = buf0;
#if DEBUG
	message(state.builtin ? -8 : -5, "%s:%d: `%s'", yyfile, yyline, s);
#endif
	if (dol)
	{
		state.checkstate = 1;
		(void)expand(s, s == buf0 ? buf1 : buf0);
		state.checkstate = 0;
	}
	return(lastline = s);
}

/*
 * low level character get for getlin()
 */

static int
getch()
{
	int	c;

	if (peekch)
	{
		c = peekch;
		peekch = '\0';
		return(c);
	}
	else if (yyinput) return(getc(yyinput));
	else if (!nextch) return(EOF);
	else if (*nextch) return(*nextch++);
	else
	{
		nextch = (char*)0;
		return('\n');
	}
}

/*
 * parse string s as if it originated in a file
 */

void
parse(s, name, line)
char	*s, *name;
int	line;
{
	FILE		*oyyinput;
	char		*oyyfile;
	int		oyyline, oreading;
	char		*onextch, *onextchr;
	char		*oyyop1;
	char		*oyyop2;
	struct ruleinfo	*oyyop;
	char		buf[MAXCMD];

	message(-2, "reading %s", name);
	oreading = state.reading;
	state.reading = 0;
	oyyinput = yyinput;
	yyinput = (FILE*)0;
	oyyfile = yyfile;
	yyfile = name;
	oyyline = yyline;
	yyline = line;
	oyyop = yyop;
	yyop = (struct ruleinfo*)0;
	oyyop1 = yyop1;
	oyyop2 = yyop2;
	onextch = nextch;
	nextch = s;
	if (nextchr && lastline)
	{
		nextchr = (char*)0;
		onextchr = lastline;
		(void)strcpy(buf, onextchr);
	}
	else nextchr = onextchr = (char*)0;
	NEXT(S_INIT);
	(void)yyparse();
	yyinput = oyyinput;
	yyfile = oyyfile;
	yyline = oyyline;
	yyop = oyyop;
	yyop1 = oyyop1;
	yyop2 = oyyop2;
	nextch = onextch;
	if (nextchr = onextchr) (void)strcpy(nextchr, buf);
	state.reading = oreading;
	NEXT(S_INIT);
}
