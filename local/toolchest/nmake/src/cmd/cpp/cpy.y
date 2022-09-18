/*
 * C preprocessor #if expression grammar
 *
 * AT&T Bell Laboratories
 */

%union
{
	int	number;
	char	*string;
}

%term	NAME NUMBER STOP
%term	EQ NE LE GE LS RS
%term	ANDAND OROR

%type	<number>	expr term NUMBER
%type	<string>	NAME

%left	','
%right	'='
%right	'?' ':'
%left	OROR
%left	ANDAND
%left	'|' '^'
%left	'&'
%binary	EQ NE
%binary	'<' '>' LE GE
%left	LS RS
%left	'+' '-'
%left	'*' '/' '%'
%right	'!' '~' UMINUS
%left	'(' '.'

%%

%{

#include "cpp.h"

extern int	search();

%}

expression	:	expr STOP
		{
			return($1);
		}
		;

expr		:	'(' expr ')'
		{
			$$ = $2;
		}
		|	expr '*' expr
		{
			$$ = $1 * $3;
		}
		|	expr '/' expr
		{
			$$ = $1 / $3;
		}
		|	expr '%' expr
		{
			$$ = $1 % $3;
		}
		|	expr '+' expr
		{
			$$ = $1 + $3;
		}
		|	expr '-' expr
		{
			$$ = $1 - $3;
		}
		|	expr LS expr
		{
			$$ = $1 << $3;
		}
		|	expr RS expr
		{
			$$ = $1 >> $3;
		}
		|	expr '<' expr
		{
			$$ = $1 < $3;
		}
		|	expr '>' expr
		{
			$$ = $1 > $3;
		}
		|	expr LE expr
		{
			$$ = $1 <= $3;
		}
		|	expr GE expr
		{
			$$ = $1 >= $3;
		}
		|	expr EQ expr
		{
			$$ = $1 == $3;
		}
		|	expr NE expr
		{
			$$ = $1 != $3;
		}
		|	expr '&' expr
		{
			$$ = $1 & $3;
		}
		|	expr '^' expr
		{
			$$ = $1 ^ $3;
		}
		|	expr '|' expr
		{
			$$ = $1 | $3;
		}
		|	expr ANDAND expr
		{
			$$ = $1 && $3;
		}
		|	expr OROR expr
		{
			$$ = $1 || $3;
		}
		|	expr '?' expr ':' expr
		{
			$$ = $1 ? $3 : $5;
		}
		|	expr ',' expr
		{
			$$ = $3;
		}
		|	term
		{
			$$ = $1;
		}
		;

term		:	'-' term	%prec UMINUS
		{
			$$ = -$2;
		}
		|	'!' term
		{
			$$ = !$2;
		}
		|	'~' term
		{
			$$ = ~$2;
		}
		|	NAME '(' NAME ')'
		{
			$$ = special($1, $3);
		}
		|	NAME NAME
		{
			$$ = special($1, $2);
		}
		|	NAME
		{
#if SCAN
			if (scan) (void)lookup($1, DEFINED);
#endif
			$$ = 0;
			skip--;
		}
		|	NUMBER
		{
			$$ = $1;
		}
		;

%%

/*
 * determine special function and predicate values
 */

special(fun, arg)
register char	*fun;
register char	*arg;
#if DEBUG
{
	int	ret;

	ret = spec0(fun, arg);
	error(-3, "%s(%s): %s", fun, arg, ret ? "true" : "false");
	return(ret);
}

spec0(fun, arg)
register char	*fun;
register char	*arg;
#endif
{
	int	markfun, markarg;
	char	buf[MAXSYMNMLEN];

	skip--;

	/*
	 * the first char of NAME is WARN if it was a <...> string
	 */

	if ((int)*fun == WARN)
	{
		markfun = 1;
		fun++;
	}
	else markfun = 0;
	if ((int)*arg == WARN)
	{
		markarg = 1;
		arg++;
	}
	else markarg = 0;

	/*
	 * #assert predicates take precedence over builtins
	 */

	strcpy(buf, fun);
	strcat(buf, "(");
	strcat(buf, arg);
	strcat(buf, ")");
	if (lookup(buf, FIND)->value) return(1);
	else if (!strcmp(fun, "defined"))
	{
		crossinfo("R", arg, xline);
		return(lookup(arg, DEFINED)->value ? 1 : 0);
	}
	else if (!strcmp(fun, "exists"))
	{
		int	fd;

		if ((fd = search(arg, markarg)) >= 0)
		{
			close(fd);
			return(1);
		}
		else return(0);
	}
	else if (!strcmp(fun, "identifiers")) return(identifiers(arg));
	else if (!strcmp(fun, "sizeof"))
	{
#if IF_SIZEOF
		/*
		 * only the basic types
		 * this does not work in cross-compilation envrionments
		 * and probably should not be supported here
		 */

		if (!strncmp(arg, "unsigned", 8))
		{
			arg += 8;
			while (isblank(*arg)) arg++;
			if (!*arg) return(sizeof(unsigned));
		}
		if (!strcmp(arg, "char")) return(sizeof(char));
		else if (!strcmp(arg, "short")) return(sizeof(short));
		else if (!strcmp(arg, "int")) return(sizeof(int));
		else if (!strcmp(arg, "long")) return(sizeof(long));
		else if (!strcmp(arg, "float")) return(sizeof(float));
		else if (!strcmp(arg, "double")) return(sizeof(double));
		else if (*arg && arg[strlen(arg)-1] == '*') return(sizeof(char*));
		else error(1, "%s(%s): only basic types are recognized", fun, arg);
#else
		yyerror("sizeof not valid");
#endif
	}
	return(0);
}

#include <ar.h>

/*
 * search file for null terminated identifier strings
 * NOTE: the first `_' is always ignored
 */

identifiers(arg)
char	*arg;
{
	register char	*s;
	register FILE	*fd;
	register int	c;
	int		need, found, min;
	unsigned long	size;
	char		**sp;
	char		*strptr[20];
	char		strbuf[MAXBUF];

	need = 0;
	size = ~0;
	for (s = arg, sp = strptr; *s && sp < strptr + sizeof(strptr); s++)
		if (*s == ',')
		{
			*s = '\0';
			*sp++ = *(s + 1) == '_' ? s + 2 : s + 1;
			need++;
		}
	if (!need) return(0);
	*sp = (char*)0;
	for (min = 0, sp = strptr; *sp; sp++)
		if ((c = strlen(*sp)) < min || !min)
			min = c;
	if (!(fd = fopen(arg, "r"))) return(0);

#if defined(ARMAG) && defined(SARMAG) && defined(ARFMAG)
	/*
	 * if fd is an archive with a symbol directory then
	 * only search the symbol directory
	 */

	if (fread(strbuf, SARMAG, 1, fd) == 1 && !strncmp(strbuf, ARMAG, SARMAG))
	{
		struct ar_hdr	ar;

		if (fread((char*)&ar, sizeof(ar), 1, fd) == 1)
		{
			size = atol(ar.ar_size);
#if DEBUG
			error(-3, "%s is an archive with a symbol directory size of %lu\n", arg, size);
#endif
		}
		else fseek(fd, 0L, 0);
	}
	else fseek(fd, 0L, 0);
#endif

	found = 0;
	s = strbuf;
	while (size-- > 0 && (c = getc(fd)) != EOF)
	{
		if (isident(c)) *s++ = c;
		else if (c == '\0' && s >= strbuf + min)
		{
			*s = '\0';
			s = strbuf;
			while (*s == '_') s++;
			if (*s)
			{
#if DEBUG
				error(-4, "test identifier \"%s\"", s);
#endif
				for (sp = strptr; *sp; sp++)
					if (!strcmp(*sp, s))
					{
#if DEBUG
						error(-3, "found \"%s\" in %s", s, arg);
#endif
						found++;
						*sp = "";
						break;
					}
				if (found == need) break;
			}
			s = strbuf;
		}
		else s = strbuf;
	}
	fclose(fd);
#if DEBUG
	error(-3, "%d identifier%s found in %s", found, found == 1 ? "" : "s", arg);
#endif
	return(found);
}
