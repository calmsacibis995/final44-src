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
 * make variable expansion routines
 */

#include "make.h"

struct editinfo				/* expand/edit state info	*/
{
	unsigned char	bol;		/* ^ found in substitute	*/
	unsigned char	edit;		/* file components to be edited	*/
	unsigned char	eol;		/* $ found in substitute	*/
	unsigned char	expand;		/* expand var values		*/
	unsigned char	first;		/* editing first component	*/
	unsigned char	natt;		/* negate attribute match sense	*/
	unsigned char	npat;		/* negate pattern match sense	*/
	unsigned char	substitute;	/* substitute components	*/
};

static struct editinfo	ed;		/* edit state			*/

static char	*expand0();
static char	*expand1();
static char	*cross();
static char	*format();
static char	*substitute();
static char	*subed();
static char	*type();
static char	*quote();

static int	attributes();
static int	generate();

static void	stresc();

/*
 * expand `$(symbol)' from a into b
 * a pointer to the end of b (after expansion) is returned
 * the symbol name is expanded before the value is determined
 * editing is done on each blank separated component of the symbol value
 * $$(symbol) expands to $(symbol) -- one $ gobbled each time
 *
 * symbol expansion forms:
 *
 *	$(s)		simple expansion (multiple character name)
 *	$(s:A=a[|b])	list of rules with user attribute a [or b ...]
 *	$(s:E=<msg>)	print error message and exit
 *	$(s:F=<fmt>)	format components according to <fmt>
 *	$(s:G=<suf>)	expand components that generate suffix <suf> files
 *	$(s:N[!]=<pat>)	expand components [not] matching shell pattern <pat>
 *	$(s:T=<typ>[r])	expand components matching rule type <typ>
 *	$(s:V)		do not expand value
 *	$(s:W=<msg>)	print warning message
 *	$(s:X=<sym>)	form cross product of components of s and <sym>
 *	$(s:f)		include or modify file name components
 *	$(s:e:)		edit components using e (see below)
 *
 * edit forms:
 *
 *	:/old/new/:	globally change old to new in each component
 *	:c:		only substitute file name component c
 *	:c=new:		substitute file name component with new
 *
 * type components:
 *
 *	A	archive
 *	B	tokenize and remove multiple space chars
 *	D	definition of state variable: -Dx[=y]
 *	E	alternate definition of state variable: x=[y]
 *	F	file
 *	N	null expanded value (no binding)
 *	O	other
 *	S	state variable
 *	T	explicit target
 *	V	non-null expanded value (no binding)
 *	*	any
 *
 * type forms:
 *
 *	$(s:T=t?ret)	ret if true else null
 *	$(s:T=t[!]=pat)	match type and [not] pat
 *
 * format forms:
 *
 *	L	convert to lower case
 *	U	convert to upper case
 *
 * file name components:
 *
 *	M	machine		upto and including the last '!'
 *				null if no '!'
 *	D	directory	up to and including the last '/'
 *				null if no '/'
 *	P	prefix		up to and including the first '.'
 *				null if only one '.'
 *	B	base		up to but not including last '.'
 *				null if '..' with only two '.' and '.' not first
 *	S	suffix		from the last '.' to the end
 *				null if no '.'
 *
 * a component (MDPBS) is deleted if the corresponding char is omitted
 * a component (MDPBS) is retained if the corresponding char is specified
 * a component (MDPBS) is changed if the corresponding char is followed
 *	by '=' and a replacement value
 *
 * if '=' is specified then a ':' separates the value from the next
 *	file name component specification
 */

char*
expand(a, b)
register char	*a, *b;
{
	register char	*s, *ed;
	int		p, hadstate, nsyms;
	char		sym[MAXNAME];
	static int	level = 0;

	if (level++ > 32) error(2, "recursive symbol definition `%-.32s%s'", a, strlen(a) > 32 ? "..." : null);
	if (a) while (*a)
	{
		if (*a != '$') *b++ = *a++;
		else if (*++a == '(')
		{
			a++;
			nsyms = 1;
			s = sym;
			ed = (char*)0;
			for (p = 1, hadstate = 0; *a; a++)
			{
				if (*a == '\\')
				{
					if (ed && a[1] == ')' || !ed && (ctype[a[1]] & C_SYMBOL)) *s++ = *++a;
					else if (a[1])
					{
						*s++ = *a++;
						*s++ = *a;
					}
				}
				else if (*a == '(')
				{
					*s++ = *a;
					p++;
					hadstate = a[-1] != '$';
				}
				else if (*a == ')')
				{
					if (!--p) break;
					else *s++ = *a;
				}
				else if (*a == ':' && p == 1 && !ed)
				{
					*s++ = '\0';
					ed = s;
				}
				else if (*a == '|' && p == 1 && !ed)
				{
					*s++ = '\0';
					nsyms++;
				}
				else *s++ = *a;
			}
			*s = '\0';
			if (*a) a++;
			for (s = sym;;)
			{
				register char	*t;

				if (!state.checkstate)
				{
					t = b;
					b = expand0(b, s, ed);
					if (b > t) break;
				}
				else if (hadstate) (void)makerule(s);
				if (nsyms-- <= 1) break;
				while (*s++);
			}
		}
		else if (*a == '$')
		{
			for (s = a; *s == '$'; s++);
			if (*s != '(') *b++ = '$';
			while (a < s) *b++ = *a++;
		}
		else if (*a == '\\' && a[1] == '(')
		{
			*b++ = '$';
			*b++ = '(';
			a += 2;
		}
		else *b++ = '$';
	}
	*b = '\0';
	level--;
	return(b);
}

/*
 * low level for expand()
 */

static char*
expand0(b, s, p)
char		*b, *p;
register char	*s;
{
	char		sym[MAXNAME];

	if (*s == '"' && s[1] && s[strlen(s) - 1] == '"')
	{
		s++;
		s[strlen(s) - 1] = '\0';
		stresc(s);
	}
	else
	{
		if (strchr(s, '$'))
		{
			(void)expand(s, sym);
			s = sym;
		}
		s = getval(s);
	}
	if (p) return(expand1(b, s, p));
	else if (*s) return(expand(s, b));
	else return(b);
}

/*
 * low level for expand0()
 * matching and editing are done here
 */

static char*
expand1(b, v, p)
register char	*b, *v, *p;
{
	register char	*s;
	char		*att, *fmt, *old, *new, *val, *gen, *pat, *typ, *crx;
	char		*mac, *dir, *pre, *bas, *suf;
	char		*ob;
	int		part, negate, oyyline;
	char		buf[MAXCMD];
	char		edbuf[MAXNAME], typbuf[MAXNAME];
	struct editinfo	oed;

	oed = ed;
	clearstate(ed);
	ed.expand = 1;
	att = fmt = gen = pat = typ = crx = (char*)0;
	(void)expand(p, edbuf);
	p = edbuf;
	mac = dir = pre = bas = suf = DELETE;
	while (part = *p++)
	{
		negate = 0;
		if (isupper(part)) part = tolower(part);
		if (part == 'c' || part == '/')
		{
			if (part == 'c' && *p) part = *p++;
			for (old = s = p; *p && *p != part; p++)
			{
				if (*p == '\\') *s++ = *++p;
				else if (*p == '^' && p == s) ed.bol = 1;
				else if (*p == '$' && (!p[1] || p[1] == part)) ed.eol = 1;
				else *s++ = *p;
			}
			if (*p == part) p++;
			*s = '\0';
			for (new = s = p; *p && *p != part; p++)
			{
				if (*p == '\\') *s++ = *++p;
				else *s++ = *p;
			}
			if (*p == part) p++;
			*s = '\0';
			part = 'c';
		}
		else if (*p == '=' || (*p == '!' && *(p + 1) == '='))
		{
			if (*p == '!')
			{
				negate = 1;
				p++;
			}
			for (val = s = ++p; *p && *p != ':'; p++)
			{
				if (*p == '\\') *s++ = *++p;
				else *s++ = *p;
			}
			if (*p) p++;
			*s = '\0';
		}
		else val = KEEP;
		switch (part)
		{
		case 'a':
			if (val == KEEP || val == DELETE)
				error(1, "attribute component requires value in symbol substitution");
			else
			{
				att = val;
				ed.natt = negate;
			}
			break;
		case 'b':
			ed.edit = 1;
			bas = val;
			break;
		case 'c':
			ed.substitute = 1;
			break;
		case 'd':
			ed.edit = 1;
			dir = val;
			break;
		case 'e':
		case 'w':
			oyyline = yyline;
			yyline = 0;
			error(part == 'e' ? 2 : 1, "%s", val);
			yyline = oyyline;
			break;
		case 'f':
			fmt = val;
			break;
		case 'g':
			gen = val;
			break;
		case 'm':
			ed.edit = 1;
			mac = val;
			break;
		case 'n':
			if (val == KEEP || val == DELETE)
				error(1, "name component requires value in symbol substitution");
			else
			{
				pat = val;
				ed.npat = negate;
			}
			break;
		case 'p':
			ed.edit = 1;
			pre = val;
			break;
		case 's':
			ed.edit = 1;
			suf = val;
			break;
		case 't':
			if (val == KEEP || val == DELETE) val = "*";
			else typ = val;
			break;
		case 'v':
			ed.expand = 0;
			break;
		case 'x':
			if (val == KEEP || val == DELETE)
				error(1, "cross-product component requires value in symbol substitution");
			else crx = val;
			break;
		default:
			error(1, "unknown expansion operator `%c'", part);
			break;
		}
		if (*p == ':') p++;
	}
	if (crx) v = cross(buf, v, getval(crx));
	else if (ed.expand)
	{
		(void)expand(v, buf);
		v = buf;
	}
	p = b;
	if (ed.substitute && !ed.bol && !ed.edit && !ed.eol && !att && !fmt && !pat && !typ && !strcmp(old, " "))
		b = substitute(b, v, old, new);
	else if (!ed.edit && !ed.substitute && !att && !fmt && !gen && !pat && !typ)
		b = strcopy(b, v);
	else for (ed.first = 1;; ed.first = 0)
	{
		if (!(s = gettok(v)))
		{
			if (!ed.first) break;
			s = null;
		}
		if (gen && !generate(s, gen));
		else if (pat && (strmatch(s, pat) == ed.npat));
		else if (att && (attributes(s, att) == ed.natt));
		else if (typ && (!(s = type(s, typ, typbuf)) || typ[1] == '=' && !strmatch(s, typ + 2) || typ[1] == '!' && typ[2] == '=' && strmatch(s, typ + 3)));
		else
		{
			if (b > p && !isspace(b[-1]) && *s != '\n') *b++ = ' ';
			ob = b;
			if (ed.substitute)
			{
				if (ed.edit) b = subed(b, s, old, new, mac, dir, pre, bas, suf);
				else b = substitute(b, s, old, new);
			}
			else if (ed.edit) b = edit(b, s, mac, dir, pre, bas, suf);
			else b = strcopy(b, s);
			if (fmt) b = format(ob, b, fmt);
		}
	}
	ed = oed;
	return(b);
}

/*
 * expand cross product of v and w into b
 */

static char*
cross(b, v, w)
char	*b, *v, *w;
{
	register char	*s, *t, *u, *x;
	long		tokstate;
	char		tmp1[MAXCMD], *tmp2 = tmp1 + MAXCMD / 2;

	if (ed.expand)
	{
		(void)expand(v, tmp1);
		v = tmp1;
	}
	u = b;
	x = w;
	while (s = gettok(v))
	{
		tokstate = settok((long)0);
		if (ed.expand)
		{
			(void)expand(w, tmp2);
			x = tmp2;
		}
		while (t = gettok(x))
		{
			if (u > b) *u++ = ' ';
			u = strcopy(u, s);
			u = strcopy(u, t);
		}
		(void)settok(tokstate);
	}
	*u = '\0';
	return(b);
}

/*
 * format the component from a to b in place
 * a pointer to the new end of a is returned
 */

static char*
format(a, b, fmt)
register char	*a, *b, *fmt;
{
	register char	*s, *t;
	char		tmp1[MAXFIX];
	char		tmp2[MAXCMD];

	while (*fmt)
	{
		switch (*fmt)
		{
		case '%':
			for (t = tmp1; *fmt && (!islower(*fmt) || *fmt == 'l'); *t++ = *fmt++);
			*t++ = *fmt ? *fmt : 's';
			*t = '\0';
			*b = '\0';
			switch (*(t - 1))
			{
			case 's':
				(void)strcpy(tmp2, a);
				(void)sprintf(a, tmp1, tmp2);
				break;
			case 'd':
			case 'o':
			case 'x':
			case 'u':
				(void)sprintf(a, tmp1, atoi(a));
				break;
			default:
				error(1, "invalid format conversion `%c'", *(t - 1));
				break;
			}
			b = a + strlen(a);
			break;
		case 'l':
		case 'L':
			for (s = a; s < b; s++)
				if (isupper(*s)) *s = tolower(*s);
			break;
		case 'u':
		case 'U':
			for (s = a; s < b; s++)
				if (islower(*s)) *s = toupper(*s);
			break;
		}
		if (*fmt) fmt++;
	}
	return(b);
}

/*
 * edit a single (expanded) file name s into b
 * a pointer to the end of b (after editing) is returned
 *
 * each file component (described above) is modified as follows:
 *
 *	KEEP		component is kept unchanged
 *	DELETE		component is deleted
 *	<string>	component is changed to <string>
 */

char*
edit(b, s, mac, dir, pre, bas, suf)
register char	*b, *s;
char		*mac, *dir, *pre, *bas, *suf;
{
	register char	*p, *q;
	char		*ob;

	if (!*s)
	{
		*b = '\0';
		return(b);
	}
	ob = b;
	q = mac;
	if (q != DELETE && q != KEEP && (!*q || !strcmp(q, "!"))) q = DELETE;
	if (p = strrchr(s, '!'))
	{
		if (q == KEEP) while (s <= p) *b++ = *s++;
		else s = ++p;
	}
	if (q != DELETE && q != KEEP)
	{
		while (*q) *b++ = *q++;
		if (b > ob && *(b-1) != '!') *b++ = '!';
	}
	q = dir;
	if (q != DELETE && q != KEEP && (!*q || !strcmp(q, "."))) q = DELETE;
	if (p = strrchr(s, '/'))
	{
		if (q == KEEP) while (s <= p) *b++ = *s++;
		else s = ++p;
	}
	if (q != DELETE && q != KEEP)
	{
		while (*q) *b++ = *q++;
		if (b > ob && *(b-1) != '/') *b++ = '/';
	}
	q = pre;
	if ((p = strchr(s, '.')) && p < strrchr(s, '.'))
	{
		if (q == KEEP) while (s <= p) *b++ = *s++;
		else s = ++p;
	}
	if (q != DELETE && q != KEEP) while (*q) *b++ = *q++;
	q = bas;

#if DOT_BASE
	/*
	 * treat the name ".xxx" as a base component
	 */ 

	if ((*s == '.' && !(p = strrchr(s + 1, '.'))) || !(p = strrchr(s, '.')))
		p = s + strlen(s);
#else
	/*
	 * treat the name ".xxx" as a suffix component
	 * this is probably the more efficient interpretation
	 * because of the proliferation of .[A-Z]* rules
	 */ 

	if (!(p = strrchr(s, '.'))) p = s + strlen(s);
#endif

	if (q == KEEP) while (s < p) *b++ = *s++;
	else s = p;
	if (q != DELETE && q != KEEP) while (*q) *b++ = *q++;
	q = suf;
	if (*p && q == KEEP) while (*s) *b++ = *s++;
	else if (q != DELETE && q != KEEP) while (*q) *b++ = *q++;
	if (b > ob + 1 && *(b-1) == '/') b--;
	*b = '\0';
	return(b);
}

/*
 * substitute a single (expanded) name s into b
 * a pointer to the end of b (after editing) is returned
 */

static char*
substitute(b, s, old, new)
register char	*b, *s;
char		*old, *new;
{
	register int	n;

	n = strlen(old);
	if (!n && !ed.bol && !ed.eol)
	{
		register char	*t;

		for (t = new; *t; t++)
			if (*t == '\\')
			{
				if (*++t != '&') *b++ = '\\';
				*b++ = *t;
			}
			else if (*t == '&') b = strcopy(b, s);
			else *b++ = *t;
	}
	else
	{
		while (*s)
		{
			if (!strncmp(s, old, n) && (!ed.eol || !s[n]))
			{
				s += n;
				b = strcopy(b, new);
			}
			else *b++ = *s++;
			if (ed.bol) break;
		}
		if (*s) b = strcopy(b, s);
		else if (ed.eol && !n) b = strcopy(b, new);
	}
	return(b);
}

/*
 * combinitaion substitute() and edit()
 */

static char*
subed(b, s, old, new, mac, dir, pre, bas, suf)
char	*b, *s, *old, *new, *mac, *dir, *pre, *bas, *suf;
{
	char	tmp[MAXCMD];

	(void)substitute(tmp, s, old, new);
	return(edit(b, tmp, mac, dir, pre, bas, suf));
}

/*
 * bind and check the type of s using type char in p
 * place expanded result in buf
 */

static char*
type(s, p, buf)
char		*s;
register char	*p;
char		*buf;
{
	register struct ruleinfo	*r;
	char				*ret;
	int				tst;
	static char comment[]		= { COMMENT, '\0' };

	if (isupper(*p)) *p = tolower(*p);
	if (*p == 'b') return(s);
	ret = *(p + 1) == '?' ? p + 2 : (char*)0;
	if (*p == 'n' || *p == 'v') return((*s == '\0') == (*p == 'n') ? (ret ? ret : null) : (ret ? null : comment));
	r = bind(makerule(s));
	if (r->state) tst = 's';
	else if (r->time) tst = 'f';
	else tst = 'o';
	if (*p == tst || *p == '*' || *p == 'a' && r->archive || *p == 't' && r->target) return(ret ? ret : r->name);
	else if (*p == 'd')
	{
		char	*equ, *quo, *val;

		if (tst != 's' || *r->name != '(' || !r->data || !*r->data) return((char*)0);
		if (*r->data == '-' && !isdigit(*(r->data + 1))) return(r->data);
		if (strcmp(r->data, "1"))
		{
			equ = "=";
			val = r->data;
			quo = quote(val);
		}
		else equ = quo = val = null;
		if (s = strchr(r->name, ')')) *s = '\0';
		sprintf(buf, "-D%s%s%s%s%s", r->name + 1, equ, quo, val, quo);
		if (s) *s = ')';
		return(buf);
	}
	else if (*p == 'e')
	{
		char	*quo, *val;

		if (tst != 's' || *r->name != '(') return((char*)0);
		if (!(val = r->data)) val = null;
		quo = quote(val);
		if (s = strchr(r->name, ')')) *s = '\0';
		sprintf(buf, "%s=%s%s%s", r->name + 1, quo, val, quo);
		if (s) *s = ')';
		return(buf);
	}
	else return((char*)0);
}

/*
 * return 1 if s has any user attribute in att
 */

static int
attributes(s, att)
char		*s;
register char	*att;
{
	register char			*t;
	register struct ruleinfo	*a;
	int				c;
	unsigned long			uatt;

	if ((a = getrule(s)) && (uatt = a->uattributes)) for (;;)
	{
		if (t = strchr(att, '|'))
		{
			c = *t;
			*t = '\0';
		}
		if ((a = getrule(att)) && (a->uattributes & uatt)) return(1);
		if (!t) break;
		*t++ = c;
		att = t;
	}
	return(0);
}

/*
 * check if name generates a file with suffix suf
 */

static int
generate(name, suf)
char	*name, *suf;
{
	struct ruleinfo	*r;
	char		tmp[MAXFIX];

	(void)edit(tmp, name, DELETE, DELETE, DELETE, DELETE, KEEP);
	if (!strcmp(tmp, suf)) return(1);
	(void)strcat(tmp, suf);
	if ((r = getrule(tmp)) && r->precmds) return(1);
	return(0);
}

/*
 * do dynamic `$' expansion of rule r's dependencies
 * the dependency list is permanently modified
 */

void
dynamic(r)
register struct ruleinfo	*r;
{
	register char		*s, *u;
	register struct list	*p, *q, *t;
	struct ruleinfo		*otarget;
	char			buf[MAXCMD];

	otarget = special.target;
	special.target = r;

	/*
	 * expand the dependency names
	 */

	for (p = r->deps, q = NIL; p; p = p->next)
		if (strchr(p->item.rule->name, '$'))
		{
			(void)expand(p->item.rule->name, buf);
			while (s = gettok(buf))
			{
				if (*s == '"' && *(u = s + strlen(s) - 1) == '"')
					*s++ = *u = '\0';
				t = cons((GENERIC)makerule(s), NIL);
				if (q) q->next = t;
				else r->deps = t;
				q = t; 
			}
			if (q) q->next = p->next;
			else r->deps = p->next;
		}
		else q = p;

	/*
	 * expand the target name
	 */

	if (strchr(r->name, '$'))
	{
		(void)expand(r->name, buf);
		if (s = gettok(buf))
		{
			if (*s == '"' && *(u = s + strlen(s) - 1) == '"')
				*s++ = *u = '\0';
			r->name = putrule(s, r);
			while (s = gettok(buf))
			{
				register char			*t;
				register struct ruleinfo	*x;

				x = makerule(s);
				t = x->name;
#if CC_BUG_FIXED	/* 8th edition -O bug : "addressing a register" */
				*x = *r;
#else
				{
					struct ruleinfo *x0 = x;
					*x0 = *r;
				}
#endif
				x->name = t;
				x->deps = copy(x->deps);
			}
		}
		else r->name = putrule(null, r);
	}
	r->dynamic = 0;
	special.target = otarget;
}

/*
 * return shell quoting char for string s
 */

static char*
quote(s)
char	*s;
{
	if (!state.exec && !state.oldfile) return(null);
	if (strchr(s, '\'')) return("\"");
	if (any(s, C_SHELL)) return("'");
	return(null);
}

/*
 * return the value of a variable given its name
 * the internal automatic variables are (lazily) expanded here
 */

char*
getval(s)
register char	*s;
{
	register struct list		*p;
	register struct ruleinfo	*r;
	struct varinfo			*v;
	int				c, n, dir;
	char				*quo;

	extern char			*ppargv[];
	extern int			ppargc;

	if (strchr("+-%<>*&@#=?", *s) && *s)
	{
		if ((dir = *s) == '+') s++;
		for (c = *s, n = -1; *s == c; s++, n++);
		if (*s) r = getrule(s);
		else r = special.target;
		if (!r) r = special.internal;
		if (dir == '+') while (n-- > 0 && r->deps) r = r->deps->item.rule;
		else while (n-- > 0 && r->link) r = r->link;
		switch (c)
		{

		case '-': /* option flags */
			if (*s)
			{
				if (any(s, C_FLAG)) return("1");
				else return(null);
			}
			else if (state.oldfile) return(null);
			else
			{
				s = strcopy(buf2, *(flags + 1) ? flags : null);
				for (c = 1; c < ppargc; c++)
				{
					s = strcopy(s, " ");
					s = strcopy(s, ppargv[c]);
				}
				return(buf2);
			}
		
		case '?': /* unused args */
		case '=': /* X=Y args */
			c = (c == '?') ? ARG_USED : 0;
			s = buf2;
			for (n = 1; args[n]; n++)
				if ((!c && strchr(args[n], '=')) || (c && !(argf[n] & c)))
				{
					if (s > buf2) s = strcopy(s, " ");
					quo = quote(args[n]);
					s = strcopy(s, quo);
					s = strcopy(s, args[n]);
					s = strcopy(s, quo);
					argf[n] |= c;
				}
			*s = '\0';
			return(buf2);

		case '%': /* target data */
			if (r->data) return(r->data);
			else return(null);

		case '<': /* target name */
			return(r->name);

		case '*': /* all target (file) dependencies */
		case '&': /* all target (file&state) dependencies */
			if (r == special.target && special.explicit)
				r->deps->next = special.explicit;
		case '>': /* updated target (file) dependencies */
			s = buf2;
			for (p = r->deps; p; p = p->next)
				if (!p->item.rule->notouch &&
				    !p->item.rule->post &&
				    !p->item.rule->use &&
				    (!p->item.rule->state || c == '&') &&
				    (c != '>' ||
				     p->item.rule->time > r->time ||
				     r->archive && !p->item.rule->member))
				{
					if (s > buf2) s = strcopy(s, " ");
					else if (!p->next) return(p->item.rule->name);
					s = strcopy(s, p->item.rule->name);
				}
			*s = '\0';
			if (r == special.target && special.explicit)
				r->deps->next = NIL;
			return(buf2);
		
		case '@':	/* target pre-commands */
			if (r->precmds) return(r->precmds);
			else return(null);
		
		case '#':	/* target post-commands */
			if (r->poscmds) return(r->poscmds);
			else return(null);

		default:
#if DEBUG
			error(INTERNAL, "%c: bad automatic variable switch()", c);
#else
			return(null);
#endif
		}
	}
	else if (strchr(s, '('))
	{
		if (!(r = getrule(s)) || !(r = bindstate(r)) || !r->data) return(null);
		else return(r->data);
	}
	else if (v = getvar(s))
	{
		if (state.reading && !state.checkstate && !state.builtin && *s != '.')
		{
			v->compiled = 0;
			v->frozen = 1;
		}
		return(v->value);
	}
	if (state.reading && !state.checkstate && *s != '.' && (v = setvar(s, null))) v->frozen = 1;
	return(null);
}

/*
 * set the value of a variable
 */

struct varinfo*
setvar(s, v)
char	*s, *v;
{
	register char		*t;
	register struct varinfo	*p;
	register int		n;

	/*
	 * check for valid variable names
	 */

	for (t = s; *t; t++)
		if (!(ctype[*t] & C_VARIABLE))
		{
			error(1, "variable name \"%s\" is invalid", s);
			return((struct varinfo*)0);
		}
	
	/*
	 * check for a previous definition
	 */

	v = v ? v : null;
	if (!(p = getvar(s)))
	{
		p = ALLOCATE(struct varinfo);
		p->name = putvar((char*)0, p);
	}
	else if (state.oldfile && !state.builtin && p->readonly)
		printf("setv %s = %s\n", p->name, v);

	/*
	 * check the variable attributes
	 */

	if (state.made || state.readonly || !p->readonly)
	{
		if (p->value && !p->import && !state.import)
		{
			/*
			 * check if the old value space can be reclaimed
			 */

			if (!p->length) p->length = strlen(p->value);
			n = strlen(v);
			if (n <= p->length)
			{
				(void)strcpy(p->value, v);
				free(v);
				v = p->value;
			}
			else
			{
				free(p->value);
				p->length = n;
			}
		}
		p->value = v;
		p->import = state.import;
		if (state.readonly) p->readonly = 1;
		else p->compiled = 0;
		if (state.vardump && !p->import)
			error(0, "%s = %s%s%s%s", s, v,
				p->readonly ? " [readonly]" : null,
				p->oldvalue ? " [oldvalue]" : null,
				p->frozen ? " [frozen]" : null);
	}
	else if (state.autocompile && p->readonly)
	{
		/*
		 * save old value for makefile compiler
		 */

		p->oldvalue = 1;
		(void)puthash(oldtab, p->name, v);
	}
	return(p);
}

/*
 * read the environment and set internal variables with setvar()
 */

void
readenv()
{
	register char	**e;
	register char	*p;

	state.import = 1;
	for (e = environ; *e; e++)
		if ((p = strchr(*e, '=')) && p[1])
		{
			*p++ = '\0';
			(void)setvar(*e, p);
			*--p = '=';
		}
	state.import = 0;
}

/*
 * convert \x character constants in place
 */

static void
stresc(s)
register char	*s;
{
	register char	*t;
	register int	n;

	t = s;
	while (*s)
	{
		if (*s == '\\' && *++s)
		{
			switch (*s++)
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
				n = *(s - 1) - '0';
				if (isdigit(*s))
				{
					n = (n << 3) + *s++ - '0';
					if (isdigit(*s)) n = (n << 3) + *s++ - '0';
				}
				break;
			case 'a':
				n = '\07';
				break;
			case 'b':
				n = '\b';
				break;
			case 'n':
				n = '\n';
				break;
			case 'r':
				n = '\r';
				break;
			case 't':
				n = '\t';
				break;
			case 'v':
				n = '\v';
				break;
			default:
				n = *(s - 1);
				break;
			}
			*t++ = n;
		}
		else *t++ = *s++;
	}
	*t = '\0';
}
