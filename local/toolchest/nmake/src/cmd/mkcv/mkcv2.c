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
 * old->new makefile converter -- second pass
 *
 * The first pass is a modified (yamh) version
 * of the system V make.  This code has been hacked
 * to work by example.  There are no guarantees that
 * the resulting makefile will run exactly like the
 * old one.  Test the makefile using "make -n" and
 * MANUALLY EDIT THE MAKEFILE AT LEAST ONCE.
 */

#include <ctype.h>
#include <stdio.h>
#include <generic.h>
#include <hash.h>

#if !lint
static char	stamp[] = "@(#)mkcv2 (AT&T Bell Laboratories) 08/30/85a";
#endif

#define DELETE	(char*)0	/* delete path component in edit()	*/
#define KEEP	(char*)1	/* keep path component in edit()	*/

#define SET_STATE	01	/* set state variable in setvar()	*/
#define SET_FILE	02	/* set makefile variable in setvar()	*/

#define MAXBUF	4096		/* maximum work buffer size		*/
#define MAXLEV	256		/* maximum dependency nesting		*/
#define MAXNAME	1024		/* maximum file name component length	*/
#define MAXLINE	72		/* maximum dependency output line size	*/

#define allocate(x)	(x*)calloc(1,sizeof(x))
#define copy(x)		strcpy(malloc((unsigned)(strlen(x)+1)),x)
#define getrule(name)	(struct ruleinfo*)gethash(rultab,(name))
#define putrule(name,r)	puthash(rultab,(name),(GENERIC)(r))
#define getcmd(name)	(struct cmdinfo*)gethash(cmdtab,(name))
#define putcmd(name,c)	puthash(cmdtab,(name),(GENERIC)(c))
#define getvar(name)	(struct varinfo*)gethash(vartab,(name))
#define putvar(name,v)	puthash(vartab,(name),(GENERIC)(v))

struct cmdinfo				/* command info			*/
{
	char		*name;		/* command sequence name	*/
	int		references;	/* number of references		*/
};

struct ruleinfo				/* rule info			*/
{
	char		*name;		/* rule name			*/
	struct ruleinfo	*primary;	/* primary source rule		*/
	struct ruleinfo	*intermediate;	/* intermediate source rule	*/
	struct ruleinfo	*dir;		/* explicit directory		*/
	struct list	*dependencies;	/* dependency list		*/
	struct list	*lastdep;	/* last of dependencies		*/
	struct list	*commands;	/* update commands		*/
	struct list	*lastcmd;	/* last of commands		*/
	struct list	*states;	/* state var deps (names only)	*/
	struct list	*laststate;	/* last of states		*/
	char		*attdeps;	/* attribute dependencies	*/
	int		nstates;	/* number of state var deps	*/
	unsigned int	a_out:1;	/* commands generate a.out	*/
	unsigned int	archive:1;	/* commands generate archive	*/
	unsigned int	attribute:1;	/* rule is an attribute		*/
	unsigned int	checked:1;	/* already cmdcheck()'d		*/
	unsigned int	directory:1;	/* already listed as directory	*/
	unsigned int	doubletarg:1;	/* listed as :: target		*/
	unsigned int	genobj:1;	/* suffix that generates .o	*/
	unsigned int	include:1;	/* -I include directory		*/
	unsigned int	inferred:1;	/* already infer()'d		*/
	unsigned int	listdep:1;	/* listed as : dependency	*/
	unsigned int	listprim:1;	/* primary source listed	*/
	unsigned int	listtarg:1;	/* listed as : target		*/
	unsigned int	mustlist:1;	/* must be listed as target	*/
	unsigned int	object:1;	/* commands generate object	*/ 
	unsigned int	oneline:1;	/* only one command line	*/
	unsigned int	skip:1;		/* skip in dump			*/
	unsigned int	source:1;	/* must exist before first make	*/
	unsigned int	target:1;	/* is an explicit target	*/
};

struct varinfo				/* variable info		*/
{
	char		*name;		/* variable name		*/
	char		*value;		/* variable value		*/
	int		references;	/* number of dependency refs	*/
	unsigned int	file:1;		/* makefile definition		*/
	unsigned int	list:1;		/* defintion should be listed	*/
	unsigned int	listed:1;	/* defintion already listed	*/
	unsigned int	state:1;	/* state variable		*/
};

union info				/* generic list access		*/
{
	struct ruleinfo	*rule;
	char		*string;
	GENERIC		generic;
};

struct list				/* generic list			*/
{
	struct list	*next;		/* next in list			*/
	union info	item;		/* list item			*/
};

#define NIL	(struct list*)0

static TABLE		cmdtab;
static TABLE		rultab;
static TABLE		vartab;

static char		states[MAXBUF];
static char		source_h[MAXBUF];

static char		*firstdel;
static char		*lex_yy_c;
static char		*lex_yy_o;
static char		*y_tab_c;
static char		*y_tab_o;

static int		linetoken;
static int		ncommands;
static int		nincludes;
static int		nobjects;
static int		optimized;
static int		y_tab_h;

static struct
{
	struct ruleinfo	*all;
	struct ruleinfo	*null;
	struct ruleinfo	*readonly;
} special;

static struct varinfo	*lastvar;

static struct list	*dirs;
static struct list	*lastdir;

int			debug;
int			line;

char			*cmdsub();
char			*edit();
char			*gettok();
char			*strcopy();

int			lcomp();
int			strmatch();

long			settok();

char			*setvar();

static struct ruleinfo	*primary();
static struct ruleinfo	*makerule();

static struct varinfo	*makevar();

static int		cmdcollect();
static int		dumpvars();
static int		dumpcmds();

extern int		strlen();
extern int		strncmp();

extern char		*calloc();
extern char		*gets();
extern char		*malloc();
extern char		*strcpy();

/*ARGSUSED*/
main(argc, argv)
int	argc;
char	**argv;
{
	struct ruleinfo		*r, *x;
	register struct list	*p;
	int			more, col;

	while (*++argv && !strcmp(*argv, "-d")) debug--;
	cmdtab = mkhash(511, 0, (GENERIC)0, (GENERIC)0, (GENERIC)0, "commands");
	rultab = mkhash(511, HASH_ALLOCATE, (GENERIC)0, (GENERIC)0, (GENERIC)0, "rules");
	vartab = mkhash(511, HASH_ALLOCATE, (GENERIC)0, (GENERIC)0, (GENERIC)0, "variables");
	printf("/* delete the first 4 lines after the makefile has been tested */\n");
	printf(".MAKEINIT : .WARN.EDIT\n");
	printf(".WARN.EDIT : .MAKE .NOTOUCH { $(:W=untested makefile generated by mkcv) }\n\n");
	r = special.all = makerule(".ALL");
	special.null = makerule("");
	special.readonly = makerule(".READONLY");
	special.readonly->attribute = 1;
	scan(r);
	for (p = makerule(".GENERATE.o")->dependencies; p; p = p->next)
		p->item.rule->genobj = 1;
	infer(r);
	exhash(vartab, dumpvars);
	exhash(rultab, cmdcollect);
	if (*source_h)
	{
		printf("\n");
		if (*source_h) printf(".SOURCE.h :%s\n", source_h);
	}
	if (dirs)
	{
		if (!*source_h) printf("\n");
		col = dumpstring(1, ".SOURCE :");
		for (p = dirs; p; p = p->next)
			col = dumpstring(col, p->item.rule->name);
		printf("\n");
	}
	if (r->dependencies)
	{
		x = getrule("all");
		if (r->dependencies->item.rule == x)
			r->dependencies = x->dependencies;
		more = 0;
		for (p = r->dependencies; p; p = p->next)
		{
			if (p->item.rule->a_out || p->item.rule->archive)
			{
				dumprule(p->item.rule);
				p->item.rule->skip = 1;
			}
			else more = 1;
		}
		if (more) dumprule(r);
	}
	exhash(cmdtab, dumpcmds);
	exit(0);
	/*NOTREACHED*/
}

/*
 * scan the intermediate data from the first pass
 */

scan(root)
struct ruleinfo	*root;
{
	register char			*s;
	register struct list		*p;
	char				*t, *u;
	int				level, targline, first, state;
	char				tmp[MAXBUF], buf[MAXBUF];
	struct ruleinfo			*rulstack[MAXLEV];

	level = line = targline = 0;
	rulstack[0] = root;
	while (gets(tmp))
	{
		line++;
		if (*tmp == '#') continue;
		cvtvar(tmp, buf);
		s = buf;
		error(-4, "%s", s);
		if (!strncmp(s, "setv ", 5))
		{
			s += 5;
			if (!strncmp(s, "CCFLAGS = ", 10))
			{
				error(-5, "%s", s);
				first = 1;
				state = 0;
				s += 10;
				while (t = gettok(s))
				{
					error(-5, "`%s'", t);
					if (!strncmp(t, "-D", 2)) state = 1;
					else if (!strncmp(t, "-I", 2))
					{
						strcat(source_h, " ");
						strcat(source_h, t + 2);
						if (source_h[strlen(source_h) - 1] == '/') source_h[strlen(source_h) - 1] = '\0';
					}
					else if (!strcmp(t, "-O")) optimized = 1;
					else
					{
						if (first)
						{
							printf("CCFLAGS =");
							first = 0;
						}
						printf(" %s", t);
					}
				}
				if (!first)
				{
					if (optimized) printf(" -O");
					printf("\n");
				}
				if (state)
				{
					(void)settok((long)0);
					while (t = gettok(s))
					{
						if (!strncmp(t, "-D", 2))
						{
							if (*states) strcat(states, " ");
							strcat(states, "(");
							for (u = t; *u && *u != '='; u++);
							if (*u == '=') *u++ = '\0';
							else u = "1";
							t = setvar(t + 2, u, SET_STATE);
							strcat(states, t);
							strcat(states, ")");
						}
					}
				}
			}
			else
			{
				printf("%s\n", s);
				if (!strncmp(s, "YACCFLAGS = ", 12) && delete(s, "-d"))
					y_tab_h = 1;
			}
		}
		else if (!strncmp(s, "symb ", 5))
		{
			s += 5;
			for (u = s; *u && *u != ' '; u++);
			if (*u)
			{
				*u++ = '\0';
				while (*u == ' ') u++;
				(void)setvar(s, copy(u), SET_FILE);
			}
		}
		else if (!strncmp(s, "rule ", 5))
		{
			level++;
			rulstack[level] = makerule(s + 5);
		}
		else if (!strncmp(s, "make ", 5))
		{
			p = allocate(struct list);
			if (rulstack[level]->lastdep) rulstack[level]->lastdep->next = p;
			else rulstack[level]->dependencies = p;
			rulstack[level]->lastdep = p;
			rulstack[level]->target = 1;
			level++;
			p->item.rule = rulstack[level] = makerule(s + 5);
			if (level == 1 && !strcmp(s + 5, "all")) printf("\n.MAIN : .CLEAR .ALL\n");
		}
		else if (!level) error(1, "missing make line");
		else if (!strncmp(s, "targ ", 5))
		{
			if (getrule(s + 5) != rulstack[level]) error(1, "invalid targ `%s' nesting", rulstack[level]->name);
			else targline = line;
		}
		else if (!strncmp(s, "done ", 5))
		{
			if (getrule(s + 5) != rulstack[level]) error(1, "invalid done `%s'", rulstack[level]->name);
			else level--;
		}
		else if (!strncmp(s, "file ", 5))
		{
			if (getrule(s + 5) != rulstack[level]) error(1, "invalid file `%s'", rulstack[level]->name);
			else rulstack[level]->source = 1;
		}
		else if (!strncmp(s, "impl ", 5))
		{
			/*
			 * not used yet
			 * the next exec sequence is from this implicit rule
			 */
		}
		else if (!strncmp(s, "exec ", 5))
		{
			if (line != targline + 1) error(1, "missing targ line before commands");
			else
			{
				targline = line;
				p = allocate(struct list);
				if (rulstack[level]->lastcmd) rulstack[level]->lastcmd->next = p;
				else rulstack[level]->commands = p;
				rulstack[level]->lastcmd = p;
				p->item.string = copy(s + 5);
			}
		}
		else error(1, "%s: unknown input from pass1", s);
	}
	if (level) error(1, "not enough done lines");
	line = 0;
}

/*
 * infer some attributes from the intermediate info
 * collect all command sequences for .USE
 */

infer(r)
register struct ruleinfo	*r;
{
	register struct list		*p;
	struct cmdinfo			*cmd;
	char				buf[MAXBUF];

	if (r->inferred) return;
	r->inferred = 1;
	(void)edit(buf, r->name, DELETE, DELETE, DELETE, DELETE, KEEP);
	if (!strcmp(buf, ".o"))
	{
		r->object = 1;
		nobjects++;
		(void)primary(r);
		cmdcheck(r);
		stripdir(r->primary);
	}
	else if (!strcmp(buf, ".a")) r->archive = 1;
	for (p = r->dependencies; p; p = p->next)
	{
		infer(p->item.rule);
		if (!r->archive && !r->object && p->item.rule->object) r->a_out = 1;
		else if (r->object) stripdir(p->item.rule);
	}
	(void)primary(r);
	cmdcheck(r);
	if (r->commands)
	{
		if (!(cmd = getcmd(r->commands->item.string)))
		{
			cmd = allocate(struct cmdinfo);
			(void)putcmd((char*)0, cmd);
		}
		if (cmd->references++ == 1)
		{
			sprintf(buf, ".COMMAND.%02d", ncommands++);
			cmd->name = copy(buf);
		}
	}
}

/*
 * strip off dir from dependency rule name
 */

stripdir(r)
register struct ruleinfo	*r;
{
	register struct ruleinfo	*d;
	struct list			*x;
	char				buf[MAXNAME];

	if (strmatch(r->name, "/usr/include/*.h") ||
	    strmatch(r->name, "/usr/jerq/*.h") ||
	    !strcmp(r->name, "FRC"))
	{
		r->skip = 1;
		return;
	}
	(void)edit(buf, r->name, DELETE, KEEP, DELETE, DELETE, DELETE);
	if (*buf)
	{
		d = makerule(buf);
		if (r->dir && r->dir != d)
			error(1, "%s: more than one explicit directory specified", r->name);
		r->dir = d;
		if (!d->directory)
		{
			d->directory = 1;
			x = allocate(struct list);
			x->item.rule = d;
			if (dirs) lastdir->next = x;
			else dirs = x;
			lastdir = x;
		}
		(void)edit(buf, r->name, DELETE, DELETE, KEEP, KEEP, KEEP);
		r->name = putrule(buf, r);
	}
	else r->dir = special.null;
}

/*
 * determine the primary source for target r
 */

static struct ruleinfo*
primary(r)
register struct ruleinfo	*r;
{
	register struct list		*p, *q;
	register struct ruleinfo	*x;
	char				buf1[MAXBUF], buf2[MAXBUF];

	if (r->primary) return(r->primary);
	if (r->a_out) return(r->primary = special.null);
	(void)edit(buf1, r->name, DELETE, DELETE, KEEP, KEEP, DELETE);
	for (p = r->dependencies; p; p = p->next)
	{
		if (p->item.rule->source || p->item.rule->target)
		{
			(void)edit(buf2, p->item.rule->name, DELETE, DELETE, KEEP, KEEP, DELETE);
			if (!strcmp(buf1, buf2))
			{
				if (strmatch(p->item.rule->name, "*.c"))
				{
					r->object = 1;
					for (q = p->item.rule->dependencies; q; q = q->next)
					{
						/* <<<<< */

	if (strmatch(q->item.rule->name, "*.y"))
	{
		if (!strcmp(buf1, "y.tab"))
		{
			if (y_tab_h)
			{
				(void)edit(buf2, q->item.rule->name, DELETE, KEEP, DELETE, KEEP, ".h");
				if (x = getrule(buf2)) error(1, "%s must be renamed -- the yacc rules generate %s instead of y.tab.h", buf2, buf2);
				else x = makerule(buf2);
				error(-2, "%s  ->  %s", x->name, buf2);
				putrule(buf2, x);
				error(1, "y.tab.h references must be changed to %s", buf2);
			}
			(void)edit(buf2, q->item.rule->name, DELETE, KEEP, DELETE, KEEP, ".o");
			putrule(buf2, r);
			error(-2, "%s  ->  %s", r->name, buf2);
			y_tab_o = r->name = copy(buf2);
			(void)edit(buf2, q->item.rule->name, DELETE, KEEP, DELETE, KEEP, ".c");
			putrule(buf2, p->item.rule);
			error(-2, "%s  ->  %s", p->item.rule->name, buf2);
			y_tab_c = p->item.rule->name = copy(buf2);
		}
		r->intermediate = p->item.rule;

		/*
		 * see if this is a `standard' yacc sequence
		 */

		cmdcheck(r);
		cmdcheck(p->item.rule);
		if (p->item.rule->commands && stdyacc(r, p->item.rule, q->item.rule))
		{
			p->item.rule = q->item.rule;
			r->target = 0;
			return(r->primary = q->item.rule);
		}
	}
	else if (strmatch(q->item.rule->name, "*.l"))
	{
		if (!strcmp(buf1, "lex.yy"))
		{
			(void)edit(buf2, q->item.rule->name, DELETE, KEEP, DELETE, KEEP, ".o");
			putrule(buf2, r);
			error(-2, "%s  ->  %s", r->name, buf2);
			lex_yy_o = r->name = copy(buf2);
			(void)edit(buf2, q->item.rule->name, DELETE, KEEP, DELETE, KEEP, ".c");
			putrule(buf2, p->item.rule);
			error(-2, "%s  ->  %s", p->item.rule->name, buf2);
			lex_yy_c = p->item.rule->name = copy(buf2);
		}
		r->intermediate = p->item.rule;

		/*
		 * see if this is a `standard' lex sequence
		 */

		cmdcheck(r);
		cmdcheck(p->item.rule);
		if (p->item.rule->commands && stdlex(r, p->item.rule, q->item.rule))
		{
			p->item.rule = q->item.rule;
			r->target = 0;
			return(r->primary = q->item.rule);
		}
	}

						/* >>>>> */
					}
				}
				else if (r->object && strmatch(p->item.rule->name, "*.y"))
				{
					r->primary = p->item.rule;
					cmdcheck(r);
					if (r->commands && stdyacc(r, r, p->item.rule))
					{
						r->target = 0;
						r->mustlist = 0;
						r->commands = NIL;
					}
				}
				else if (r->object && strmatch(p->item.rule->name, "*.l"))
				{
					cmdcheck(r);
					if (r->commands && stdlex(r, r, p->item.rule))
					{
						r->target = 0;
						r->mustlist = 0;
						r->commands = NIL;
					}
				}
				return(r->primary = p->item.rule);
			}
		}
		else if ((x = primary(p->item.rule)) != r) return(r->primary = x);
	}
	return(r->primary = r);
}

/*
 * check r for a `standard' yacc sequence
 */

stdyacc(r, i, s)
register struct ruleinfo	*r, *i;
struct ruleinfo			*s;
{
	int		ok;
	struct list	*z;
	char		buf2[MAXBUF], buf3[MAXBUF];

	ok = 1;
	if (i->commands)
	{
		strcpy(buf2, i->commands->item.string);
		if (r == i)
		{
			(void)delete("$(CC)", buf2);
			(void)delete("$(CCFLAGS)", buf2);
			(void)delete("-c", buf2);
			(void)delete("rm", buf2);
			(void)delete("-f", buf2);
			(void)delete("y.tab.o", buf2);
		}
		(void)delete("yacc", buf2);
		(void)delete("$(YACC)", buf2);
		(void)delete("-d", buf2);
		(void)delete("$(YACCFLAGS)", buf2);
		(void)delete(s->name, buf2);
		(void)delete("mv", buf2);
		(void)delete("y.tab.h", buf2);
		(void)delete("y.tab.c", buf2);
		(void)delete("$(>)", buf2);
		(void)delete("$(>).h", buf2);
		(void)delete("$(<)", buf2);
		(void)edit(buf3, s->name, DELETE, DELETE, DELETE, KEEP, ".h");
		(void)delete(buf3, buf2);
		(void)delete(i->name, buf2);
		if (*buf2)
		{
			if (delete(":yyfix", buf2) ||
			    delete("ed", buf2) ||
			    delete("sed", buf2))
			{
				z = allocate(struct list);
				z->item.rule = special.readonly;
				if (r->lastdep) r->lastdep->next = z;
				else r->dependencies = z;
				r->lastdep = z;
			}
			else if (!delete("cmp", buf2)) ok = 0;
		}
	}
	return(ok);
}

/*
 * check r for a `standard' lex sequence
 */

stdlex(r, i, s)
register struct ruleinfo	*r, *i;
struct ruleinfo			*s;
{
	int		ok;
	struct list	*z;
	char		buf2[MAXBUF];

	ok = 1;
	if (i->commands)
	{
		strcpy(buf2, i->commands->item.string);
		if (r == i)
		{
			(void)delete("$(CC)", buf2);
			(void)delete("$(CCFLAGS)", buf2);
			(void)delete("-c", buf2);
			(void)delete("rm", buf2);
			(void)delete("-f", buf2);
			(void)delete("lex.yy.o", buf2);
		}
		(void)delete("lex", buf2);
		(void)delete("$(LEX)", buf2);
		(void)delete("$(LEXFLAGS)", buf2);
		(void)delete(s->name, buf2);
		(void)delete("mv", buf2);
		(void)delete("lex.yy.c", buf2);
		(void)delete("$(>)", buf2);
		(void)delete("$(<)", buf2);
		(void)delete(i->name, buf2);
		if (*buf2)
		{
			if (delete(":yyfix", buf2) ||
			    delete("ed", buf2) ||
			    delete("sed", buf2))
			{
				z = allocate(struct list);
				z->item.rule = special.readonly;
				if (r->lastdep) r->lastdep->next = z;
				else r->dependencies = z;
				r->lastdep = z;
			}
			else ok = 0;
		}
	}
	return(ok);
}

static struct ruleinfo	*curobj;

static int		column;

/*
 * collect and list .o targets with dependencies matching curobj
 */

/*ARGSUSED*/
static int
samedeps(s, r)
char				*s;
register struct ruleinfo	*r;
{
	if (r->object && !r->commands && !r->listtarg && !lcomp(r->dependencies, curobj->dependencies, 0) && !lcomp(r->states, curobj->states, 1))
	{
		r->listtarg = 1;
		column = dumpstring(column, r->name);
	}
	return(0);
}

/*
 * dump the rule info
 */

dumprule(r)
register struct ruleinfo	*r;
{
	register struct list	*p;
	int			col, source, rul;
	struct varinfo		*var;
	char			buf[MAXBUF];

	if (r->listtarg) return;
	rul = rulemust(r);
	if (r->mustlist || rul)
	{
		r->listtarg = 1;
		printf("\n");
		col = dumpstring(1, r->name);
		if (r->object && (r->dependencies || r->states) && !r->commands)
		{
			/*
			 * list all objects with same dependencies
			 */

			curobj = r;
			column = col;
			exhash(rultab, samedeps);
			col = column;
		}
		col = dumpstring(col, ":");
		if (r->a_out || r->archive)
		{
			r->doubletarg = 1;
			source = 1;
			col++;
			printf(":");
		}
		else source = 0;
		clrdeps(r, source);
		if (debug <= -1)
		{
			if (r->a_out) printf("[a.out]");
			if (r->archive) printf("[archive]");
			if (r->object) printf("[object]");
		}
		col = listrules(r, col, source);
		if (source && *states) col = dumpstring(col, states);
		if (r->states)
		{
			for (p = r->states; p; p = p->next)
			{
				if (!r->object || ((var = getvar(p->item.string)) && var->references < nobjects))
				{
					sprintf(buf, "(%s)", p->item.string);
					col = dumpstring(col, buf);
				}
			}
		}
		if (r->mustlist && r->commands)
		{
			printf("\n");
			dumpcmd(r->commands->item.string, "\t");
		}
		else printf("\n");
		for (p = r->dependencies; p; p = p->next)
			dumprule(p->item.rule);
	}
}

/*
 * clear the listdep flag for r's dependencies
 */

clrdeps(r, source)
register struct ruleinfo	*r;
int				source;
{
	register struct list	*p;

	for (p = r->dependencies; p; p = p->next)
	{
		p->item.rule->listdep = 0;
		if (source) primary(p->item.rule)->listdep = 0;
		clrdeps(p->item.rule, source);
	}
}

/*
 * check and translate command lines
 */

cmdcheck(r)
register struct ruleinfo	*r;
{
	register struct list	*p;
	register char		*s, *t;
	struct ruleinfo		*x;
	struct list		*z;
	int			first, all, force;
	char			buf[MAXBUF], tmp[MAXBUF];
	char			tmp1[MAXLINE], tmp2[MAXLINE];

	if (!r) return;
	if (r->checked) return;
	r->checked = 1;
	if (r->skip) return;
	if (!r->dependencies && !r->commands) return;
	force = 0;
	if (r->commands)
	{
		/*
		 * convert symbols in the command lines
		 * and smash all the lines into one
		 */

		r->oneline = 1;
		first = 1;
		s = buf;
		for (p = r->commands; p; p = p->next)
		{
			t = p->item.string;
			if (*t && t[strlen(t)-1] == '\\') t[strlen(t)-1] = '\0';
			else if (first) first = 0;
			else
			{
				r->oneline = 0;
				s = strcopy(s, "\n");
			}
			s = cmdsub(r, t, s);
		}
		if (strmatch(buf, "cd[!a-zA-Z0-9]*") || strmatch(buf, "*[!a-zA-Z0-9]cd[!a-zA-Z0-9]*"))
		{
			error(1, "%s: cd in update command block", r->name);
			s = strcopy(tmp, "( ");
			s = strcopy(s, buf);
			s = strcopy(s, " )");
			strcpy(buf, tmp);
		}
		if (strmatch(buf, "make[!a-zA-Z0-9]*") || strmatch(buf, "*[!a-zA-Z0-9]make[!a-zA-Z0-9]*") || strmatch(buf, "*$(MAKE)*"))
		{
			error(1, "%s: recursive makes must be handled separately", r->name);
			unassign(buf);
		}
		r->commands->item.string = copy(buf);
		r->commands->next = NIL;
		if (!r->object && !r->archive && !r->a_out)
		{
			/*
			 * try one last time to determine the target type
			 */

			strcpy(tmp, buf);
			if (delete("$(CC)", tmp) && delete("-o", tmp) && !delete("-c", tmp)) force = r->a_out = 1;
			else
			{
				strcpy(tmp, buf);
				if (delete("ar", tmp) && (delete("cr", tmp) || delete("r", tmp))) force = r->archive = 1;
			}
		}
	}
	if (r->object)
	{
		if (r->oneline)
		{
			(void)delete("$(CC)", buf);
			(void)delete("$(CCFLAGS)", buf);
			if (optimized) (void)delete("-O", buf);
			(void)delete("$(F77)", buf);
			(void)delete("$(F77FLAGS)", buf);
			(void)delete("$(AS)", buf);
			(void)delete("$(ASFLAGS)", buf);
			(void)delete("-c", buf);
			(void)delete("$(>)", buf);
			if (!*buf)
			{
				r->commands = NIL;
				r->mustlist = force;
				return;
			}
			(void)delete("-R", buf);
			(void)delete("-Wa,-r", buf);
			(void)delete(":rofix", buf);
			if (!*buf)
			{
				z = allocate(struct list);
				z->item.rule = special.readonly;
				if (r->lastdep) r->lastdep->next = z;
				else r->dependencies = z;
				r->lastdep = z;
				r->commands = NIL;
				r->mustlist = 1;
				return;
			}
			strcpy(tmp, buf);
			(void)settok((long)0);
			while (s = gettok(tmp))
			{
				if (!strncmp(s, "-D", 2))
				{
					(void)delete(s, buf);
					(void)delete(s, r->commands->item.string);
					for (t = s; *t && *t != '='; t++);
					if (*t == '=') *t++ = '\0';
					else t = "1";
					s = setvar(s + 2, t, SET_STATE);
					if (!member((GENERIC)s, r->states))
					{
						r->nstates++;
						lastvar->references++;
						p = allocate(struct list);
						p->item.string = s;
						if (r->laststate) r->laststate->next = p;
						else r->states = p;
						r->laststate = p;
					}
				}
				else if (!strncmp(s, "-I", 2))
				{
					(void)delete(s, buf);
					(void)delete(s, r->commands->item.string);
					strcpy(tmp2, s);
					s = tmp2;
					if (s[strlen(s) + 1] == '/') s[strlen(s) + 1] = '\0';
					if (!(x = getrule(s + 2)) || !x->include)
					{
						if (!x) x = makerule(s + 2);
						x->include = 1;
						sprintf(tmp1, ".INCLUDE.%02d", nincludes++);
						x->attdeps = setvar(tmp1, s, SET_STATE);
					}
					p = allocate(struct list);
					p->item.string = x->attdeps;
					if (r->laststate) r->laststate->next = p;
					else r->states = p;
					r->laststate = p;
					r->nstates++;
				}
			}
			if (!*buf)
			{
				r->commands = NIL;
				return;
			}
			error(-1, "cmdcheck object FAIL: `%s'", buf);
		}
		r->mustlist = 1;
		return;
	}
	if (r->a_out)
	{
		if (r->commands)
		{
			linetoken = 1;
			(void)pdelete("-[DIU]*", r->commands->item.string);
			linetoken = 0;
			strcpy(buf, r->commands->item.string);
			if (strmatch(buf, "*$(LEXFLAGS)*"))
				error(1, "%s: LFLAGS used in ld context -- use LDFLAGS instead", r->name);
		}
		if (r->commands)
		{
			all = 1;
			linetoken = 1;
			firstdel = (char*)0;
			for (p = r->dependencies; p; p = p->next)
				if ((p->item.rule->archive || p->item.rule->object) && !delete(p->item.rule->name, buf))
				{
					(void)edit(tmp, p->item.rule->name, DELETE, DELETE, KEEP, "$(<)", KEEP);
					if (!delete(tmp, buf)) all = 0;
				}
			linetoken = 0;
			if (all)
			{
				t = tmp;
				s = buf;
				while (*s)
				{
					if (s == firstdel) t = strcopy(t, "$(*) ");
					*t++ = *s++;
				}
				*t = '\0';
				strcpy(buf, tmp);
				r->commands->item.string = copy(buf);
			}
		}
		if (r->oneline)
		{
			(void)delete("$(CC)", buf);
			(void)delete("$(CCFLAGS)", buf);
			(void)delete("$(LDFLAGS)", buf);
			(void)delete("-o", buf);
			(void)delete("$(<)", buf);
			(void)delete("./$(<)", buf);
			(void)delete("$(<).o", buf);
			(void)delete("$(>)", buf);
			if (all) (void)delete("$(*)", buf);
			(void)delete("*.o", buf);
			if (*buf) error(-1, "cmdcheck a.out ALMOST: `%s'", buf);
			strcpy(tmp, buf);
			(void)settok((long)0);
			while (s = gettok(tmp))
			{
				if (strmatch(s, "*.[ao]"))
				{
					p = allocate(struct list);
					p->item.rule = makerule(s);
					if (r->lastdep) r->lastdep->next = p;
					else r->dependencies = p;
					r->lastdep = p;
					linetoken = 1;
					(void)delete(s, buf);
					linetoken = 0;
				}
				else if (!strncmp(s, "-l", 2));
				else
				{
					error(-1, "cmdcheck a.out FAIL: `%s'", buf);
					r->mustlist = 1;
					return;
				}
			}
			if (*buf) r->attdeps = copy(buf);
			r->commands = NIL;
			r->mustlist = force;
			return;
		}
		r->mustlist = 1;
		return;
	}
	if (r->archive)
	{
		(void)delete("rm", buf);
		(void)delete("-f", buf);
		(void)delete("ar", buf);
		(void)delete("r", buf);
		(void)delete("cr", buf);
		(void)delete("rc", buf);
		(void)delete("ranlib", buf);
		(void)delete("$(<)", buf);
		for (p = r->dependencies; p; p = p->next)
			(void)delete(p->item.rule->name, buf);
		if (*buf) force = 1;
		r->mustlist = force;
		return;
	}
	if (r->oneline)
	{
		if (r->dependencies) (void)edit(buf, r->dependencies->item.rule->name, DELETE, DELETE, DELETE, KEEP, DELETE);
		if (!r->dependencies || !strcmp(r->name, buf))
		{
			(void)delete("$(CC)", buf);
			(void)delete("$(CCFLAGS)", buf);
			(void)delete("$(LDFLAGS)", buf);
			(void)delete("-o $(<)", buf);
			(void)delete("$(<).c", buf);
			error(-3, ".out: `%s'", buf);
			if (!*buf)
			{
				r->mustlist = force;
				return;
			}
		}
	}
	r->mustlist = 1;
}

/*
 * change X=Y args to $(?) for $(MAKE) commands
 */

unassign(buf)
char	*buf;
{
	register char	*s, *t;
	register int	check;
	char		*u;
	int		first;
	long		state;
	struct varinfo	*v;
	char		tmp[MAXBUF];

	state = settok((long)0);
	linetoken = 1;
	check = 0;
	s = buf;
	strcpy(tmp, s);
	while (t = gettok(tmp))
	{
		if (!strcmp(t, "make") || !strcmp(t, "$(MAKE)"))
		{
			t = "$(MAKE) $(-)";
			check = first = 1;
		}
		else if (*t == '\n') check = 0;
		if (check)
		{
			if (!strcmp(t, "$(-)")) continue;
			else if (u = strchr(t, '='))
			{
				*u = '\0';
				v = getvar(t);
				*u = '=';
				if (!v || !v->listed)
				{
					if (first)
					{
						first = 0;
						t = "$(=)";
					}
					else continue;
				}
			}
		}
		if (s > buf && *t != '\n') s = strcopy(s, " ");
		s = strcopy(s, t);
	}
	*s = '\0';
	linetoken = 0;
	(void)settok(state);
}

/*
 * delete substring s from b
 */

delete(s, b)
register char	*s, *b;
{
	register char	*t;
	char		*buf;
	long		state;
	char		tmp[MAXBUF];
	int		found;

	state = settok((long)0);
	strcpy(tmp, b);
	t = buf = b;
	found = 0;
	while (b = gettok(tmp))
	{
		if (strcmp(s, b))
		{
			if (t > buf) t = strcopy(t, " ");
			t = strcopy(t, b);
		}
		else
		{
			found = 1;
			if (!firstdel) firstdel = buf + (b - tmp);
		}
	}
	*t = '\0';
	(void)settok(state);
	return(found);
}

/*
 * delete shell pattern s from b
 */

pdelete(s, b)
register char	*s, *b;
{
	register char	*t;
	char		*buf;
	long		state;
	char		tmp[MAXBUF];
	int		found;

	state = settok((long)0);
	strcpy(tmp, b);
	t = buf = b;
	found = 0;
	while (b = gettok(tmp))
	{
		if (!strmatch(b, s))
		{
			if (t > buf) t = strcopy(t, " ");
			t = strcopy(t, b);
		}
		else
		{
			found = 1;
			if (!firstdel) firstdel = buf + (b - tmp);
		}
	}
	*t = '\0';
	(void)settok(state);
	return(found);
}

/*
 * return 1 if r and its dependencies need to be listed
 */

rulemust(r)
register struct ruleinfo	*r;
{
	register struct list	*p;
	register struct varinfo	*v;
	int			n;

	for (p = r->dependencies; p; p = p->next)
		if (!p->item.rule->source)
			return(1);
	n = 0;
	for (p = r->states; p; p = p->next)
		if ((v = getvar(p->item.string)) && v->references == nobjects)
			n++;
	return(n != r->nstates);
}

/*
 * list rules
 * source==1 is for :: lists
 */

listrules(r, col, source)
struct ruleinfo	*r;
int		col, source;
{
	register struct list		*p;
	register struct ruleinfo	*x;

	for (p = r->dependencies; p; p = p->next)
	{
		if (p->item.rule->skip);
		else if (r == special.all && p->item.rule->doubletarg);
		else if (source && !strcmp(p->item.rule->name, "y.tab.h"));
		else if ((source&03) == 03 && p->item.rule->attribute);
		else if (source && (!p->item.rule->archive || !p->item.rule->target))
		{
			if (!p->item.rule->listdep)
			{
				x = p->item.rule;
				if (!x->listprim)
				{
					x->listprim = 1;
					x = primary(x);
				}
				if (!x->source) col = dumpstring(col, p->item.rule->name);
				else
				{
					if (!x->listdep)
					{
						col = dumpstring(col, x->name);
						x->listdep = 1;
					}
					col = listrules(p->item.rule, col, source|02);
				}
			}
		}
		else if (!p->item.rule->source || !r->object)
			col = dumpstring(col, p->item.rule->name);
	}
	if (r->attdeps) col = dumpstring(col, r->attdeps);
	return(col);
}

/*
 * dump a string keeping track of the right margin
 */

dumpstring(col, s)
int	col;
char	*s;
{
	register int	n;

	n = strlen(s);
	if (col + n >= MAXLINE)
	{
		printf(" \\\n\t\t%s", s);
		col = n + 16;
	}
	else
	{
		if (col <= 1) col = 1;
		else
		{
			printf(" ");
			col++;
		}
		printf("%s", s);
		col += n;
	}
	return(col);
}

/*
 * print a command sequence placing pfx at the beginning of each line
 */

dumpcmd(cmd, pfx)
register char	*cmd, *pfx;
{
	register char	*s;
	register int	c;

	for (s = cmd; *s; s++)
	{
		if (*s == ' ') s++;
		for (cmd = s; *s && *s != '\n'; s++);
		c = *s;
		*s = '\0';
		printf("%s%s\n", pfx, cmd);
		if (!(*s = c)) break;
	}
}

/*
 * copy cmd to buf, checking for $(<) and $(>)
 */

char*
cmdsub(r, cmd, buf)
register struct ruleinfo	*r;
register char			*cmd;
register char			*buf;
{
	char			*target, *source, *inter;
	int			targetz, sourcez, interz, basez, hadspace;
	char			base[MAXNAME];

	target = r->name;
	targetz = strlen(target);
	source = primary(r)->name;
	if (strmatch(source, ".y")) inter = "y.tab.c";
	else if (strmatch(source, ".l")) inter = "lex.yy.c";
	else inter = "";
	if (r->intermediate) source = r->intermediate->name;
	sourcez = !strcmp(source, target) ? 0 : strlen(source);
	interz = strlen(inter);
	(void)edit(base, r->name, DELETE, DELETE, KEEP, KEEP, DELETE);
	basez = strlen(base);
	error(-2, "t=%s s=%s i=%s c=\"%s\"", target, source, inter, cmd);

	/*
	 * change every occurrence of target to $(<)
	 * change every occurrence of source to $(>)
	 * change every occurrence of inter to $(>)
	 */

	hadspace = 1;
	while (*cmd)
	{
		if (*cmd == ' ' || *cmd == '\t')
		{
			if (!hadspace)
			{
				hadspace = 1;
				*buf++ = ' ';
			}
			cmd++;
		}
		else
		{
			hadspace = (*cmd == '\n');
			if (interz && !strncmp(cmd, inter, interz) && !isalnum(cmd[interz]))
			{
				buf = strcopy(buf, "$(>)");
				cmd += interz;
			}
			else if (sourcez && !strncmp(cmd, source, sourcez) && !isalnum(cmd[sourcez]))
			{
				buf = strcopy(buf, "$(>)");
				cmd += sourcez;
			}
			else if (targetz && !strncmp(cmd, target, targetz) && !isalnum(cmd[targetz]))
			{
				buf = strcopy(buf, "$(<)");
				cmd += targetz;
			}
			else if (y_tab_c && !strncmp(cmd, "y.tab.c", 7))
			{
				if (!strcmp(y_tab_c, source))
					buf = strcopy(buf, "$(>)");
				else if (!strcmp(y_tab_c, target))
					buf = strcopy(buf, "$(<)");
				else buf = strcopy(buf, y_tab_c);
				cmd += 7;
			}
			else if (y_tab_o && !strncmp(cmd, "y.tab.o", 7))
			{
				if (!strcmp(y_tab_o, source))
					buf = strcopy(buf, "$(>)");
				else if (!strcmp(y_tab_o, target))
					buf = strcopy(buf, "$(<)");
				else buf = strcopy(buf, y_tab_o);
				cmd += 7;
			}
			else if (lex_yy_c && !strncmp(cmd, "lex.yy.c", 8))
			{
				if (!strcmp(lex_yy_c, source))
					buf = strcopy(buf, "$(>)");
				else if (!strcmp(lex_yy_c, target))
					buf = strcopy(buf, "$(<)");
				else buf = strcopy(buf, lex_yy_c);
				cmd += 8;
			}
			else if (lex_yy_o && !strncmp(cmd, "lex.yy.o", 8))
			{
				if (!strcmp(lex_yy_o, source))
					buf = strcopy(buf, "$(>)");
				else if (!strcmp(lex_yy_o, target))
					buf = strcopy(buf, "$(<)");
				else buf = strcopy(buf, lex_yy_o);
				cmd += 8;
			}
			else if (basez && !strncmp(cmd, base, basez) && !isalnum(cmd[basez]))
			{
				buf = strcopy(buf, "$(<)");
				cmd += basez;
			}
			else *buf++ = *cmd++;
		}
	}
	*buf = '\0';
	return(buf);
}

/*
 * $ converion from s into t
 *
 *	${...}  ->  $(...)
 *	2*k*$   ->  (k+1)*$
 */

cvtvar(s, t)
register char	*s;
register char	*t;
{
	register char	*u;
	register int	lev, n;

	while (*s)
	{
		if ((*t++ = *s++) == '$')
		{
			if (*s == '{')
			{
				*t++ = '(';
				u = t;
				for (lev = 1, s++; *s; s++)
				{
					if ((*t++ = *s) == '{') lev++;
					else if (*s == '}' && !--lev)
					{
						*(t - 1) = '\0';
						makevar(u)->list = 1;
						*(t - 1) = ')';
						s++;
						break;
					}
				}
			}
			else if (*s == '(')
			{
				for (lev = 1, u = s + 1; *u; u++)
				{
					if (*u == '(') lev++;
					else if (*u == ')' && !--lev)
					{
						lev = *u;
						*u = '\0';
						makevar(u)->list = 1;
						*u = lev;
						break;
					}
				}
			}
			else if (*s == '$')
			{
				n = 1;
				while (*s == '$')
				{
					s++;
					n++;
				}
				if (n & 01)
				{
					s--;
					n--;
				}
				for (n /= 2; n > 0; n--) *t++ = '$';
			}
		}
	}
	*t = '\0';
}

/*
 * return old rule pointer if found
 * otherwise make a new rule
 */

static struct ruleinfo*
makerule(name)
char	*name;
{
	struct ruleinfo	*r;

	if (!(r = getrule(name)))
	{
		r = allocate(struct ruleinfo);
		r->name = putrule((char*)0, r);
	}
	return(r);
}

/*
 * return old var pointer if found
 * otherwise make a new var
 */

static struct varinfo*
makevar(name)
char	*name;
{
	struct varinfo	*v;

	if (!(v = getvar(name)))
	{
		v = allocate(struct varinfo);
		v->name = putvar((char*)0, v);
	}
	return(v);
}

#include <errno.h>

extern int	errno;
extern int	sys_nerr;

extern char	*sys_errlist[];

/*
 * error and message formatter
 * lev is the error level
 * lev >= 2 exits
 * lev < 0 is for debug tracing
 */

/*VARARGS2*/
error(lev, fmt, a1, a2, a3, a4, a5, a6, a7, a8)
int	lev;
char	*fmt;
{
	register FILE	*fd;
	int		sys;
	char		*cmd;

	if (lev < debug) return;
	fd = lev ? stderr : stdout;
	cmd = "mkcv";
	sys = 0;
	switch (lev)
	{
	case 0:
		/* information */
		break;
	case 1:
		/* warning */
		fprintf(fd, "%s: (warning) ", cmd);
		break;
	case 2:
		/* error */
		fprintf(fd, "%s: ", cmd);
		sys = debug < 0;
		break;
	default:
		/* debug (<0) or internal error */
#if DEBUG
		if (lev > 128 || lev < -128)
		{
			fprintf(fd, "%s: (%s, line %d) ", cmd, (char*)lev, (int)fmt);
			fmt = (char*)a1;
			a1 = a2;
			a2 = a3;
			a3 = a4;
			a4 = a5;
			a5 = a6;
			a6 = a7;
			a7 = a8;
			sys = 1;
			lev = 3;
		}
		else
#endif
		if (lev >= 0)
		{
			fprintf(fd, "%s: (internal %d) ", cmd, lev);
			sys = 1;
		}
		else
		{
			if (debug < -1) fprintf(fd, "%s: (debug %d) ", cmd, -lev);
			else fprintf(fd, "%s: (debug) ", cmd);
		}
		break;
	}
	if (sys && errno > 0 && errno <= sys_nerr && errno != ENOENT && errno != EBADF)
		fprintf(fd, "[%s] ", sys_errlist[errno]);
	if (line) fprintf(fd, "line %d: ", line);
	if (fmt) fprintf(fd, fmt, a1, a2, a3, a4, a5, a6, a7, a8);
	fprintf(fd, "\n");
	fflush(fd);
	errno = 0;
	if (lev >= 2) exit(lev - 1);
}

static union
{
	long			state;
	struct
	{
		unsigned short	index;
		unsigned short	chr;
	} eos;
} token;

/*
 * generate isspace() separated tokens from a string
 * (char*)0 returned when no tokens remain
 *
 * the original string is restored after all tokens are generated
 * settok() allows simultaneous token generators
 */

char*
gettok(string)
char	*string;
{
	register char	*p, *r;
	register int	quote;

	/*
	 * restore string on each call
	 */

	p = string;
	if (token.state)
	{
		if (!token.eos.chr)
		{
			token.state = 0;
			return((char*)0);
		}
		p += token.eos.index;
		*p = token.eos.chr;
	}

	/*
	 * skip leading space
	 */

	while (isspace(*p) && (!linetoken || *p != '\n')) p++;
	if (!*p)
	{
		token.state = 0;
		return((char*)0);
	}

	/*
	 * find the end of this token
	 * "..." and '...' constants are detected inside tokens
	 */

	if (linetoken && *p == '\n') r = p + 1;
	else
	{
		quote = 0;
		for (r = p; *r; r++)
		{
			if (*r == '"' || *r == '\'')
			{
				if (quote == *r) quote = 0;
				else if (!quote) quote = *r;
			}
			else if (isspace(*r) && !quote) break;
		}
	}

	/*
	 * save state so we can restore string on the next call
	 */

	token.eos.index = r - string;
	token.eos.chr = *r;
	*r = '\0';
	return(p);
}

/*
 * save|restore previous gettok() state
 * settok(0) resets to init state
 */

long
settok(new)
long	new;
{
	long	old;

	old = token.state;
	token.state = new;
	return(old);
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
 * copy t into s, return a pointer to the end of s ('\0')
 */

char*
strcopy(s, t)
register char	*s, *t;
{
	if (!t) return(s);
	while (*s++ = *t++);
	return(--s);
}

/*
 * variable assignment with state variable consistency checks
 */

char*
setvar(s, v, flags)
char	*s, *v;
int	flags;
{
	register struct varinfo	*var;
	int			n;
	char			buf1[MAXBUF], buf2[MAXBUF], buf3[MAXBUF];

	if (var = getvar(s))
	{
		if (var->state || (flags&SET_STATE))
		{
			if (strcmp(var->value, v))
			{
				if (strmatch(v, "\\\"*\\\"") || strmatch(v, "'*'"))
				{
					strcpy(buf3, v + 1);
					v = buf3;
					n = strlen(v);
					v[n-2] = '"';
					v[n-1] = '\0';
				}
				if (*var->value == '"' || *var->value == '\'')
				{
					strcpy(buf1, var->value);
					sprintf(buf2, "'\"$(%s)\"'", s);
					(void)delete(buf2, buf1);
					sprintf(buf2, "\"$(%s)\"", s);
					(void)delete(buf2, buf1);
					if (n = !*buf1)
					{
						sprintf(buf1, "\"%s\"", v);
						v = buf1;
					}
				}
				else n = 0;
				if (!n) error(1, "state variable %s has more than one value", s);
				var->value = copy(v);
			}
		}
		else var->value = v;
	}
	else
	{
		var = allocate(struct varinfo);
		var->value = (flags&SET_STATE) ? copy(v) : v;
		var->name = putvar((char*)0, var);
	}
	if ((flags&SET_STATE)) var->state = 1;
	if ((flags&SET_FILE)) var->file = 1;
	lastvar = var;
	return(var->name);
}

/*
 * dump all marked variable definitions
 */

/*ARGSUSED*/
static int
dumpvars(s, v)
char			*s;
register struct varinfo	*v;
{
	static int	first = 1;

	if (!*v->name || !v->state && (!v->value || !*v->value));
	else if ((v->list || v->state) && !v->listed)
	{
		if (first)
		{
			first = 0;
			printf("\n");
		}
		printf("%s =", v->name);
		if (v->value) printf(" %s", v->value);
		printf("\n");
		v->listed = 1;
		if (v->references == nobjects)
		{
			if (*states) strcat(states, " ");
			strcat(states, "(");
			strcat(states, v->name);
			strcat(states, ")");
		}
	}
	return(0);
}

/*
 * dump the .USE command scripts
 */

static int
dumpcmds(s, cmd)
char			*s;
register struct cmdinfo	*cmd;
{
	if (cmd->references > 1)
	{
		printf("\n%s : .USE\n", cmd->name);
		dumpcmd(s, "\t");
	}
	return(0);
}

/*
 * return 1 if x is in list p
 */

member(x, p)
register GENERIC	x;
register struct list	*p;
{
	for (; p; p = p->next)
		if (p->item.generic == x)
			return(1);
	return(0);
}

/*
 * rule list comparison
 * order forces both list to have same order
 */

lcomp(p, q, order)
register struct list	*p, *q;
int			order;
{
	register int	n;

	if (order)
	{
		while (p && q)
		{
			if (p->item.rule->source)
			{
				p = p->next;
				if (q->item.rule->source) q = q->next;
			}
			else if (q->item.rule->source)
			{
				q = q->next;
				if (p->item.rule->source) p = p->next;
			}
			else
			{
				if (p->item.rule != q->item.rule) return(1);
				p = p->next;
				q = q->next;
			}
		}
		return(p || q);
	}
	else
	{
		for (n = 0; p; p = p->next)
			if (!p->item.rule->source)
			{
				if (!member(p->item.generic, q)) return(1);
				n++;
			}
		for (; q; q = q->next)
			if (!q->item.rule->source)
				n--;
		return(n);
	}
}

/*
 * collect common command sequences and update dependencies
 */

/*ARGSUSED*/
static int
cmdcollect(s, r)
char				*s;
register struct ruleinfo	*r;
{
	register struct list	*p;
	register struct cmdinfo	*cmd;

	if (r->commands)
	{
		if ((cmd = getcmd(r->commands->item.string)) && cmd->references > 1)
		{
			r->commands = NIL;
			r->mustlist = 1;
			p = allocate(struct list);
			p->item.rule = makerule(cmd->name);
			if (r->lastdep) r->lastdep->next = p;
			else r->dependencies = p;
			r->lastdep = p;
			p->item.rule->attribute = 1;
		}
	}
	return(0);
}
