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
 * make file read routines
 */

#include "make.h"

extern char	*ppargv[];

extern int	ppargc;

extern long	lseek();

static void	readfd();
static void	loadcheck();
static void	reread();

/*
 * read a makefile
 */

int
readfile(name)
char		*name;
{
	FILE		*fd;

	if (!strcmp(name, "-"))
	{
		readfd(stdin, "stdin");
		return(1);
	}
	else if (fd = fopen(name, "r"))
	{
		readfd(fd, name);
		fclose(fd);
		return(1);
	}
#if SCCS
	else
	{
		char		fil[MAXNAME];
		char		*argv[5];

		/*
		 * `get' the file if possible
		 */

		(void)edit(fil, name, KEEP, KEEP, "s.", KEEP, KEEP);
		if (!access(fil, 4))
		{
			argv[0] = "get";
			argv[1] = "-p";
			argv[2] = "-s";
			argv[3] = fil;
			argv[4] = (char*)0;
			if (fd = cmdopen(fopen("/dev/null", "r"), argv[0], argv))
			{
				readfd(fd, name);
				cmdclose(fd);
				return(1);
			}
		}
	}
#endif
	return(0);
}

/*
 * read a file given an open file descriptor
 * the file is preprocessed using special.pp
 */

static void
readfd(fd, file)
FILE	*fd;
char	*file;
{
	register char	*s = buf1;
	int		f, o, n, pp;
	time_t		ftime, otime;
	long		magic;
	char		*ppcommand;
	char		*pppath = (char*)0;
	struct ruleinfo	*r;
	struct stat	sbuf;

	/*
	 * NOTE: we pun on r->status and r->time for makefile dependency
	 *	 checking -- cleared up in main by readcheck()
	 *
	 * r->status
	 *
	 *	NOTYET	not read in yet
	 *	UPDATE	being read in
	 *	EXISTS	already read in
	 *
	 * r->time
	 *
	 *	NOTIME	implicitly read
	 */

	r = makerule(file);
	switch (r->status)
	{
	case NOTYET:
		if (state.mainload)
		{
			error(1, "recompiling %s -- %s has been added", state.objectfile, r->name);
			reread();
		}
		r->status = UPDATE;
		state.dependencies = cons((GENERIC)r, state.dependencies);
		break;

	case UPDATE:
		r->status = EXISTS;
		/* fall through ... */

	case EXISTS:
		return;

#if DEBUG
	default:
		error(INTERNAL, "invalid state %d for `%s'", r->status, r->name);
#endif
	}
	if (state.firstfile)
	{
		/*
		 * save the first makefile name
		 */

		(void)setvar("MAKEFILE", COPY(file));

		/*
		 * set up the object and state variable file names
		 */

		(void)edit(buf0, file, DELETE, DELETE, DELETE, KEEP, MAKEOBJECT);
		state.objectfile = COPY(buf0);
		(void)edit(buf0, file, DELETE, DELETE, DELETE, KEEP, MAKESTATE);
		state.statefile = COPY(buf0);
		state.firstfile = 0;

		/*
		 * don't complain about not being in arg list
		 */

		r->time = NOTIME;
	}
	f = fileno(fd);
	pp = 0;
	if (lseek(f, 0L, 0) >= 0)
	{
		/*
		 * check if file is a make object file
		 */
	
		if (read(f, (char*)&magic, sizeof(magic)) == sizeof(magic) && magic == MAKEMAGIC)
		{
			if (lseek(f, 0L, 0) < 0)
				error(INTERNAL, "cannot rewind %s", file);
			fstat(f, &sbuf);
			otime = sbuf.st_mtime;
			if (otime >= state.ptime && (state.builtin || !state.forceread) && load(f, file))
			{
				state.ptime = otime;
				fclose(fd);
				loadcheck(otime, file);
				return;
			}
			error(2, "%s must be recompiled", file);
		}
		if (lseek(f, 0L, 0) < 0)
			error(INTERNAL, "cannot rewind %s", file);
		if (state.builtin || !state.forceread)
		{
			/*
			 * check for object corresponding to file
			 */
	
			(void)edit(buf0, file, DELETE, DELETE, DELETE, KEEP, MAKEOBJECT);
			if ((o = open(buf0, 0)) >= 0)
			{
				fstat(f, &sbuf);
				ftime = sbuf.st_mtime;
				fstat(o, &sbuf);
				otime = sbuf.st_mtime;
				if (otime >= ftime && otime >= state.ptime)
				{
					state.ptime = otime;
					n = load(o, buf0);
					close(o);
					loadcheck(otime, buf0);
					if (n) return;
				}
				else n = 1;
				if (state.builtin) error(1, "reading %s%s",
					file,
					state.forceread ? " -- should be compiled before compiling local makefiles" : null);
				else error(1, "recompiling %s%s%s",
					buf0,
					n ? " -- out of date with " : null,
					n ? otime < ftime ? file : "builtin rules" : null);
			}
		}

		/*
		 * check for explicit preprocessor control
		 */

		ppcommand = "#preprocess";
		*ppcommand = SALT;
		n = strlen(ppcommand);
		if (read(f, buf0, n) == n && !strncmp(buf0, ppcommand, n))
		{
			if (read(f, s, 1) == 1 && *s == '=')
			{
				while (read(f, s, 1) == 1 && *s != '\n') s++;
				*s++ = '\0';
				pppath = buf1;
			}
			if (lseek(f, -1L, 1) < 0)
				error(INTERNAL, "cannot backspace %s", file);
		}
		else if (lseek(f, 0L, 0) < 0)
			error(INTERNAL, "cannot rewind %s", file);
		if (!pppath) pppath = special.pp;
	}
	if (pppath && *pppath)
	{
		(void)edit(buf0, pppath, DELETE, DELETE, KEEP, KEEP, KEEP);
		ppargv[0] = buf0;
		if (strmatch(pppath, "*/cpp"))
		{
#if OLDCPP
			if (strcmp(pppath, "/lib/cpp"))
			{
				/*
				 * assume the new cpp if not /lib/cpp
				 * in this case <default.h> is assumed to be in
				 * the same directory as cpp
				 */

				ppargv[ppargc] = s;
				s = strcopy(strcopy(s, "-N"), file) + 1;
				ppargv[ppargc + 1] = s;
				s = strcopy(s, "-I");
				(void)edit(s, pppath, DELETE, KEEP, DELETE, DELETE, DELETE);
			}
#else
			ppargv[ppargc] = s;
			(void)strcopy(strcopy(s, "-N"), file);
#endif
		}
		message(-2, "preprocessing %s using %s", file, ppargv[0]);
		if (!(fd = cmdopen(fd, pppath, ppargv)))
			error(2, "error in preprocessor %s", pppath);
		pp = 1;
	}
	yyinput = fd;
	oyyfile = yyfile = file;
	yyline = 1;
	message(-2, "reading %s", file);
	state.reading = 1;
	(void)yyparse();
	state.reading = 0;
	yyline = 0;
	if (pp) cmdclose(fd);
	if (!state.builtin && state.exec) state.compile = 1;
	state.forceread = 1;
}

/*
 * check loaded object file dependecies
 */

static void
loadcheck(ftime, file)
time_t	ftime;
char	*file;
{
	register struct ruleinfo	*r;
	register struct list		*p;
	time_t				dtime;
	struct stat			sbuf;

	r = makerule(file);
	for (p = r->deps; p; p = p->next)
	{
		dtime = stat(p->item.rule->name, &sbuf) ? DEFTIME : sbuf.st_mtime;
		if (!dtime || dtime > ftime)
		{
			error(1, "recompiling %s -- out of date with %s", file, p->item.rule->name);
			reread();
		}
		p->item.rule->status = UPDATE;
	}
	state.dependencies = r->deps;
	if (!state.builtin) state.mainload = 1;
}

/*
 * check that all makefile dependencies were specified
 */

void
readcheck()
{
	register struct list		*p;

	for (p = state.dependencies; p; p = p->next)
	{
		if (state.start > state.ptime && p->item.rule->time != NOTIME && p->item.rule->status == NOTYET)
		{
			error(1, "recompiling %s -- %s has been deleted", state.objectfile, p->item.rule->name);
			reread();
		}
		p->item.rule->status = NOTYET;
	}
}

/*
 * punt -- input makefiles inconsistent with object
 * add -R option to original args to force reading and re-exec
 */

static void
reread()
{
	register char	**ap, **op, **newargs;

	if (state.reread) error(INTERNAL, "makefile dependencies cause infinite recursion");
	for (op = args; *op; op++);
	ap = newargs = (char**)malloc(((op - args) + 1) * sizeof(char**));
	for (op = args; *op; *ap++ = *op++);
	*ap++ = "-R";
	*ap = (char*)0;
	execvp(newargs[0], newargs);
	error(2, "cannot exec %s", newargs[0]);
}
