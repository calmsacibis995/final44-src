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
 * make state variable routines
 */

#include "make.h"

static int	remake();

static void	getdefine();
static void	checkstate();

/*
 * read state variables from a previous make
 */

void
readstate(file)
char	*file;
{
	register FILE	*fd;

	if (file && (fd = fopen(file, "r")))
	{
		message(-2, "reading state variables from %s", file);
		if (!load(fileno(fd), file))
			error(2, "use -A to accept current state or -S to remake");
		fclose(fd);
	}
}

/*
 * save state variables for the next make
 */

void
savestate(file)
char	*file;
{
	if (file && state.savestate && state.exec && !state.override)
	{
		message(-2, "saving state variables in %s", file);
		state.compilestate = 1;
		compile(file);
		state.compilestate = 0;
		state.savestate = 0;
	}
}

/*
 * bind a rule to a state variable
 * if r is a state variable rule then bind r and
 * return a pointer to the state var
 */

struct ruleinfo*
bindstate(r)
register struct ruleinfo	*r;
{
	register char			*t, *u;
	register struct ruleinfo	*f;

	if (r->bound) return(r);
	else if (r->state)
	{
		/*
		 * determine the current state variable value
		 */

		t = strchr(r->name, '(');
		u = strchr(r->name, ')');
		if (t > r->name)
		{
			/*
			 * variable defined in external file
			 */
			
			*t = '\0';
			sprintf(buf0, "%s", r->name);
			*t = '(';
			if (!(f = bindfile(buf0, 0)))
			{
				checkstate(r, null);
				error(1, "cannot find %s", buf0);
			}
			else if (!f->searched && r->time < f->time) getdefine(f);
		}
		else
		{
			/*
			 * variable defined via make
			 */

			*u = '\0';
			(void)expand(getval(t + 1), buf0);
			*u = ')';
			checkstate(r, buf0);
		}
		r->bound = 1;
		if (state.accept) r->time = OLDTIME;
		return(r);
	}
	else return((struct ruleinfo*)0);
}

/*
 * get the definitions of all state variables in file
 */

static void
getdefine(r)
register struct ruleinfo	*r;
{
	register char		*t, *u, *v;
	register FILE		*fd;
	struct ruleinfo		*s;
	int			n, iflev;
	char			var[MAXNAME];

	if (r->searched);
	else if (fd = fopen(r->name, "r"))
	{
		message(-2, "searching %s for state variable definitions", r->name);

		/*
		 * the definitions are assumed to be of the form
		 *
		 *	^#<SP>*define<SP>*<NAME><SP>*<VALUE>(<COMMENT>|<SP>)*
		 *
		 * where <COMMENT> is a C comment
		 *
		 * other definition styles may be added
		 */

		iflev = 0;
		while (t = fgets(buf0, MAXCMD, fd)) if (*t == SALT)
		{
			while (ctype[*++t] & C_SPACE);
			if (!strncmp(t, "define", 6))
			{
				t += 6;
				while (ctype[*t] & C_SPACE) t++;
				for (u = t; *u && !(ctype[*u] & C_SPACE); u++);
				if (*u) *u++ = '\0';
				while (*u && (ctype[*u] & C_SPACE)) u++;
				sprintf(var, "%s(%s)", r->name, t);
				if ((s = getrule(var)) && !s->bound)
				{
					if (*(v = u)) for (;;)
					{
						u += strlen(u) - 2;
						if (*u != '\\') break;
						if (!fgets(u, MAXCMD - (u - buf0) - 1, fd)) break;
					}
					*++u = '\0';

					/*
					 * remove comments and trailing space
					 */

					for (t = u = v, n = 0; *u; u++)
					{
						if (!n && *u == '/' && *(u+1) == '*')
						{
							u += 2;
							while (*u && (*u++ != '*' || *u != '/'));
						}
						else if ((*v++ = *u) == '"') n = !n;
					}
					for (v--; v >= t && (ctype[*v] & C_SPACE); v--);
					*++v = '\0';
					if (!*t) t = "1";
					checkstate(s, t);
					if (iflev > 0) error(1, "only the first definition of `%s' will be used", s->name);
				}
			}
			else if (!strncmp(t, "if", 2)) iflev++;
			else if (!strncmp(t, "endif", 5)) iflev--;
		}
		fclose(fd);
	}
	else error(1, "cannot read %s", r->name);
	r->searched = 1;
}

/*
 * check if state variable value changed
 * v is the current value
 * the previous value, if defined, has already
 * been placed in r->data by readstate()
 */

static void
checkstate(r, v)
register struct ruleinfo	*r;
register char			*v;
{
	message(-2, "checking state variable %s", r->name);
	if (!r->time || strcmp(r->data, v))
	{
		/*
		 * state var changed
		 */

		message(-2, "state variable %s changed", r->name);
		state.savestate = 1;
		r->data = COPY(v);
		r->time = CURTIME - 1;	/* hack around 1 sec granularity */
	}
}

#if FULLSEARCH

#define MAXPPARGS	32

/*
 * low level for fullsearch()
 */

static void
full(fd, cur)
register FILE			*fd;
register struct ruleinfo	*cur;
{
	register char	*s;
	char		*file;
	struct ruleinfo	*x;

	extern char		*fgets();

	cur->time = CURTIME;
	cur->deps = NIL;
	cur->searched = 1;
	while (fgets(buf0, MAXCMD, fd)) if (*buf0 == SALT)
	{
		(void)settok((long)0);
		if ((s = gettok(buf0+1)) && !strcmp(s, "pragma") &&
		    (s = gettok(buf0)) && !strcmp(s, "info") && (s = gettok(buf0)))
		{
			if (!strcmp(s, "end")) break;
			else if (!strcmp(s, "include"))
			{
				if (s = gettok(buf0))
				{
#if DEBUG
					message(-4, "%cpragma info include %s", SALT, s);
#endif
					cur->deps = cons((GENERIC)makerule(s), cur->deps);
					if (s = gettok(buf0))
					{
						(void)sprintf(buf1, "%s()", s);
						full(fd, makerule(buf1));
					}
					else error(1, "bad `info include' line");
				}
			}
			else if (!strcmp(s, "parameter") || !strcmp(s, "unused"))
			{
				if (s = gettok(buf0))
				{
#if DEBUG
					message(-4, "%cpragma info parameter %s", SALT, s);
#endif
					makerule(s)->parameter = 1;
				}
			}
			else if (!strcmp(s, "reference"))
			{
				if (s = gettok(buf0))
				{
					if (!strcmp(s, "-")) *buf1 = '\0';
					else (void)strcpy(buf1, s);
					if (s = gettok(buf0))
					{
						(void)strcat(strcat(strcat(buf1, "("), s), ")");
						x = makerule(buf1);
						cur->deps = cons((GENERIC)x, cur->deps);
						if (!(s = gettok(buf0))) s = null;
#if DEBUG
						message(-4, "%cpragma info reference %s=\"%s\"", SALT, buf1, s);
#endif
						if (*buf1 != '(') checkstate(x, s);
					}
				}
			}
		}
	}
}

/*
 * use "cpp -P -S -X" to determine detailed file and variable dependencies
 *
 * NOTE:
 *	This dependency scanner is not foolproof, although it
 *	provides more information than finddeps().  It is
 *	possible for an #if construct to cause some dependencies
 *	to be omitted.  #include file structuring hints:
 *
 *	(1)  make separate header files containing only #define's
 *	(2)  place #if's in main files rather than in header files
 */

static struct list*
fullsearch(r)
register struct ruleinfo	*r;
{
	register char		*t;
	register struct list	*p;
	int			c, argc;
	struct ruleinfo		*s;
	char			*file, *pppath;
	FILE			*fd, *ppfd;
	char			nam[MAXNAME];
	char			*argv[MAXPPARGS];

	sprintf(nam, "%s()", unbound(r));
	if ((s = getrule(nam)))
	{
		if (s->searched) return(s->deps);
		if (s->time >= r->time)
		{
			for (p = s->deps; p; p = p->next)
			{
				if (!p->item.rule->state)
				{
					p->item.rule = bind(p->item.rule);
					if (p->item.rule->time >= r->time) break;
				}
			}
			if (!p) return(s->deps);
		}
	}

	/*
	 * search for dependency info using special.pp
	 */

	pppath = special.pp;
	if (!*pppath) error(2, "implicit file scanner not found");
	if (!(fd = fopen(r->name, "r"))) error(2, "cannot open file %s", r->name);
	(void)edit(buf0, pppath, DELETE, DELETE, KEEP, KEEP, KEEP);
	argc = 0;
	argv[argc++] = buf0;
	argv[argc++] = "-P";
	argv[argc++] = "-S";
	argv[argc++] = "-X";
	t = buf1;

	/*
	 * determine proper flags for cpp
	 */

	s = special.target;
	special.target = r->link;
	(void)expand("$(CCFLAGS:N=-[DIU]*)", t);
	special.target = s;
	while (*t)
	{
		argv[argc++] = t;
		while (*t && !isspace(*t)) t++;
		if (*t) *t++ = '\0';
	}
#if OLDCPP
	if (strcmp(pppath, "/lib/cpp"))
	{
		/*
		 * assume the new cpp if not /lib/cpp
		 * in this case <default.h> is assumed to be in
		 * the same directory as cpp
		 */

		argv[argc++] = ++t;
		t = strcopy(t, "-I");
		(void)edit(t, pppath, DELETE, KEEP, DELETE, DELETE, DELETE);
	}
#endif
	argv[argc] = (char*)0;
#if DEBUG
	if (state.debug <= -6)
		for (argc = 0; argv[argc]; argc++)
			error(-6, "search $%d = \"%s\"", argc, argv[argc]);
#endif

	/*
	 * fire up the scanner -- may want something like coshell() here
	 */

	message(-2, "searching %s for dependencies using %s", r->name, argv[0]);
	if (!(ppfd = cmdopen(fd, pppath, argv)))
		error(2, "error in preprocessor %s", pppath);
	(void)sprintf(nam, "%s()", unbound(r));
	s = makerule(nam);
	full(ppfd, s);
	fclose(fd);
	cmdclose(ppfd);
	return(s->deps);
}

#endif

/*
 * return list of r's implicit file dependencies
 * r must be bound to a file which is then searched
 */

struct list*
finddeps(r)
register struct ruleinfo	*r;
{
	register char		*t;
	register struct list	*p;
	int			c, iflev;
	struct ruleinfo		*s;
	FILE			*fd;
	char			*file;
	char			nam[MAXNAME];

	if (!state.implicit) return(NIL);
#if FULLSEARCH
	if (state.fullsearch) return(fullsearch(r));
#endif
	sprintf(nam, "%s()", unbound(r));
	if (!state.accept && (s = getrule(nam)) && (!state.search || s->time == r->time)) return(s->deps);
	if (!state.search) return(NIL);
	if (fd = fopen(r->name, "r"))
	{
		message(-2, "searching %s for implicit dependencies", r->name);

		/*
		 * the implicit dependencies are assumed to be of the form
		 *
		 *	^#<SP>*include<SP>*<DELIM><FILE><DELIM>
		 *
		 * where <DELIM> is " or < (matching >)
		 * other forms may be added
		 */

		iflev = r->dontcare ? 1 : 0;
		p = NIL;
		while (t = fgets(buf1, MAXCMD, fd)) if (*t == SALT)
		{
			while (ctype[*++t] & C_SPACE);
			if (!strncmp(t, "include", 7))
			{
				t += 7;
				while (ctype[*t] & C_SPACE) t++;
				if ((c = *t) == '"' || c == '<')
				{
					if (c == '<') c = '>';
					file = ++t;
					while (*t && *t != c && *t != '\n') t++;
					if (*t == c)
					{
						*t = '\0';
						s = makerule(file);
						p = cons((GENERIC)s, p);
						if (iflev > 0) s->dontcare = 1;
						s->search = 1;
					}
				}
			}
			else if (!strncmp(t, "if", 2)) iflev++;
			else if (!strncmp(t, "endif", 5)) iflev--;
		}
		fclose(fd);
		state.savestate = 1;
		s = makerule(nam);
		s->deps = p;
		s->searched = 1;
		s->time = r->time;
		return(p);
	}
	if (!r->searched)
	{
		r->searched = 1;
		if (!r->dontcare) error(1, "cannot read %s", r->name);
	}
	return(NIL);
}
