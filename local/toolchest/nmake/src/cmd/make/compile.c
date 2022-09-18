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
 * makefile compiler and loader
 */

#include "make.h"

/*
 * !!!!! INCREMENT VERSION IF ANY OF THE FOLLOWING CHANGE !!!!!
 *
 *	struct headinfo
 *	struct list
 *	struct trailinfo
 *	struct ruleinfo
 *	struct varinfo
 */

#define VERSION		5		/* compiler/loader version	*/

#define align(x)	round(x,(sizeof(struct{char a;union{char *a;double b;}b;})-sizeof(union{char *a;double b;})))
#define normalize(x)	if(x)x=compstring(x)
#define relocate(t,x,o)	if(x)x=(t)((char*)x+o)
#define round(x,y)	(((long)x+(y-1))&~(y-1))

struct headinfo				/* make object file header	*/
{
	long		magic;		/* magic number			*/
	long		version;	/* compiler/loader version	*/
	unsigned int	biton:1;	/* bit field alignment test 1	*/
	unsigned int	bitoff:1;	/* bit field alignment test 2	*/
	short		salign;		/* align(1)			*/
	short		slist;		/* sizeof(struct list)		*/
	short		srule;		/* sizeof(struct ruleinfo)	*/
	short		svar;		/* sizeof(struct varinfo)	*/
};

struct trailinfo			/* make object file trailer	*/
{
	long		magic;		/* magic number			*/
	long		lists;		/* number of compiled lists	*/
	long		rules;		/* number of compiled rules	*/
	long		size;		/* total sizeof object file	*/
	long		variables;	/* number of compiled variables	*/
};

static struct list	*lstptr;	/* normalized list pointer	*/
static struct ruleinfo	*rulptr;	/* normalized rule pointer	*/
static char		*strptr;	/* normalized string pointer	*/

static FILE		*objfd;		/* object file pointer		*/
static FILE		*strfd;		/* string file pointer		*/

static struct trailinfo	trailer;	/* object file trailer		*/

/*
 * recursively mark r and its dependencies for compilation
 */

static void
markcompile(r)
register struct ruleinfo	*r;
{
	register struct list	*p;

	r->compiled = 0;
	r->mark = 1;
	for (p = r->deps; p; p = p->next)
		if (!p->item.rule->mark)
			markcompile(p->item.rule);
	r->mark = 0;
}

/*
 * compile a string and return the normalized string pointer
 */

static char*
compstring(s)
char	*s;
{
	register char	*t = s;
	char		*ptr = strptr;

	do putc(*t, strfd); while (*t++);
	strptr += t - s;
	return(ptr);
}

/*
 * recursively mark dependencies for compilation
 */

/*ARGSUSED*/
static int
compmark(s, r)
char				*s;
register struct ruleinfo	*r;
{
	r->link = (struct ruleinfo*)0;
	if (!r->compiled || (state.compilestate && r->state)) markcompile(r);
	return(0);
}

/*
 * compile an individual rule
 */

static int
comprule(s, r)
char				*s;
register struct ruleinfo	*r;
{
	register struct list	*p;
	struct ruleinfo		x;

	/*
	 * ignore aliases and compile each rule once only
	 */

	if (s != r->name || r->compiled) return(0);
	r->compiled = 1;

	/*
	 * normalize the current rule pointer for dependency list compilation
	 */

	r->link = rulptr++;
	x = *r;
	r = &x;

	/*
	 * make sure the unbound rule name is compiled
	 */

	if (!r->state && r->uname)
	{
		r->name = r->uname;
		r->uname = (char*)0;
	}

	/*
	 * normalize and compile the string pointers
	 */

	normalize(r->name);
	normalize(r->data);
	if (!r->cmdspecial)
	{
		normalize(r->precmds);
		normalize(r->poscmds);
	}

	/*
	 * reset some flags
	 */
	
	r->bound = 0;
	r->mark = 0;
	r->member = 0;
	r->searched = 0;
	r->status = NOTYET;
	r->touch = 0;

	/*
	 * determine the next normalized dependency list pointer
	 */

	if (p = r->deps)
	{
		r->deps = lstptr;
		for (; p; p = p->next)
			lstptr++;
	}

	/*
	 * write the normalized rule
	 */

	if (fwrite((char*)r, sizeof(struct ruleinfo), 1, objfd) != 1)
		error(2, "cannot compile rule `%s'", r->name);
	trailer.rules++;
	return(0);
}

/*
 * compile the dependency list for r
 */

static int
complist(s, r)
char				*s;
register struct ruleinfo	*r;
{
	register struct list	*p;

	/*
	 * ignore aliases and rules not set up by comprule()
	 */

	if (s != r->name || !r->link) return(0);
	for (p = r->deps; p; p = p->next)
	{
		r = p->item.rule;
		while (!(p->item.rule = r->link) || !r->compiled)
		{
			register struct ruleinfo	*x;

			if ((x = getrule(r->name)) && x != r)
			{
				r = x;
#if DEBUG
				error(1, "`%s' has been duplicated", r->name);
#endif
			}
			else error(INTERNAL, "dependency %s of %s not compiled", r->name, s);
		}

		/*
		 * write the normalized list
		 */

		if (fwrite((char*)p, sizeof(struct list), 1, objfd) != 1)
			error(2, "cannot compile dependency list for `%s'", s);
		p->item.rule = r;
		trailer.lists++;
	}
	return(0);
}

/*
 * compile an individual variable
 */

static int
compvar(s, v)
char			*s;
register struct varinfo	*v;
{
	char		*t;
	struct varinfo	x;

	/*
	 * compile each variable only once
	 */

	if (v->compiled || (v->import && !v->frozen)) return(0);
	else v->compiled = 1;

	/*
	 * normalize and compile the string pointers
	 */

	x = *v;
	v = &x;

	/*
	 * check for possible old value
	 */

	if (v->oldvalue)
	{
		t = (char*)gethash(oldtab, v->name);
#if DEBUG
		if (!t) error(INTERNAL, "%s->oldvalue set but not in oldtab", s);
#endif
		if (!v->frozen)
		{
			v->value = t;
			v->oldvalue = 0;
		}
		else if (!strcmp(v->value, t)) v->oldvalue = 0;

		/*
		 * if v->oldvalue is set in load() then the
		 * variable is frozen and the frozen value
		 * is different than the makefile value
		 */
	}
	normalize(v->name);
	normalize(v->value);

	/*
	 * reset some flags
	 */

	v->length = 0;
	v->readonly = 0;

	/*
	 * write the normalized variable
	 */

	if (fwrite((char*)v, sizeof(struct varinfo), 1, objfd) != 1)
		error(2, "cannot compile variable `%s'", s);
	trailer.variables++;
	return(0);
}

/*
 * compile the current rules and variables into objfile
 */

void
compile(objfile)
char	*objfile;
{
	int		fd, n;
	char		*objtmp, *strtmp;
	long		pos;
	struct headinfo	header;

	extern char	*mktemp();

	message(-2, "compiling rules into %s", objfile);

	/*
	 * create the object and temporary string files
	 */

	if (!(objfd = fopen(objtmp = mktemp("makeoXXXXXX"), "w")))
	{
		error(1, "cannot create temporary object file %s", objtmp);
		return;
	}
	if (!(strfd = fopen(strtmp = mktemp("makesXXXXXX"), "w")))
	{
		error(1, "cannot create temporary string file %s", strtmp);
		fclose(objfd);
		unlink(objtmp);
		return;
	}

	/*
	 * initialize the trailer info
	 */

	trailer.magic = MAKEMAGIC;
	trailer.lists = trailer.rules = trailer.variables = 0;

	/*
	 * initialize the normalized pointers
	 */

	lstptr = (struct list*)0;
	lstptr++;
	rulptr = (struct ruleinfo*)0;
	rulptr++;
	strptr = (char*)0;
	strptr++;

	/*
	 * write the header
	 */

	header.magic = MAKEMAGIC;
	header.version = VERSION;
	header.biton = 1;
	header.bitoff = 0;
	header.salign = align(1);
	header.slist = sizeof(struct list);
	header.srule = sizeof(struct ruleinfo);
	header.svar = sizeof(struct varinfo);
	if (fwrite((char*)&header, sizeof(struct headinfo), 1, objfd) != 1)
		error(2, "cannot write header to temporary object file %s", objtmp);

	/*
	 * mark the rules and dependencies for compilation
	 */

	special.attribute->compiled = 0;
	exhash(rultab, compmark);

	/*
	 * compile and write the rules
	 */

	exhash(rultab, comprule);

	/*
	 * compile and write the dependency lists
	 */

	exhash(rultab, complist);

	/*
	 * compile and write the variables
	 */

	if (!state.compilestate) exhash(vartab, compvar);

	/*
	 * append the string file
	 */

	fclose(strfd);
	if (!(fd = open(strtmp, 0)))
		error(2, "cannot read temporary string file %s", strtmp);
	while ((n = read(fd, buf0, MAXCMD)) > 0)
		if (fwrite(buf0, n, 1, objfd) != 1)
			error(2, "cannot append strings to temporary object file %s", objtmp);
	close(fd);

	/*
	 * align and append the trailer
	 */

	for (;;)
	{
		pos = ftell(objfd);
		if (pos == align(pos)) break;
		fputc('\0', objfd);
	}
	trailer.size = pos + sizeof(struct trailinfo);
	if (fwrite((char*)&trailer, sizeof(struct trailinfo), 1, objfd) != 1)
		error(2, "cannot append trailer to temporary object file %s", objtmp);

	/*
	 * clean up
	 */

	fclose(objfd);
	unlink(objfile);
	if (link(objtmp, objfile))
		error(1, "object file %s not recompiled", objfile);
	if (unlink(objtmp))
		error(1, "temporary object file %s not deleted", objtmp);
	if (unlink(strtmp))
		error(1, "temporary string file %s not deleted", strtmp);
}

/*
 * associate one rule with each name
 */

/*ARGSUSED*/
static int
atomize(s, r)
char				*s;
register struct ruleinfo	*r;
{
	register struct list	*p;

	if (r->mark) return(0);
	for (p = r->deps; p; p = p->next)
		if (p->item.rule->mark)
		{
			r = p->item.rule;
			if (!(p->item.rule = getrule(r->name)))
				error(INTERNAL, "cannot load rule `%s'", r->name);
		}
	if (r->immediate && r->deps) immediate(r);
	return(0);
}

/*
 * load compiled rules and variables from objfile
 */

int
load(fd, objfile)
int	fd;
char	*objfile;
{
	register struct ruleinfo	*r;
	register struct varinfo		*v;
	register struct list		*d;
	int				n, recompile;
	struct stat			sbuf;
	unsigned long			lstoff, ruloff, stroff;
	char				*p;
	struct headinfo			*h;
	struct ruleinfo			*oattribute;
	struct trailinfo		*t;
	struct varinfo			*x, *ov;

	message(-2, "loading object file %s", objfile);

	/*
	 * read the object file into memory
	 */

	if (fstat(fd, &sbuf))
	{
		error(1, "cannot stat object file %s", objfile);
		return(0);
	}
	n = sbuf.st_size;
	if (!(p = malloc((unsigned)n)))
	{
		error(1, "cannot allocate %d bytes for object file", n);
		return(0);
	}
	if (read(fd, p, n) != n)
	{
		error(1, "cannot read object file %s", objfile);
		free(p);
		return(0);
	}
	close(fd);

	/*
	 * check the header and trailer info
	 */

	h = (struct headinfo*)p;
	t = (struct trailinfo*)(p + (n - sizeof(struct trailinfo)));
	if (h->magic != MAKEMAGIC || t->magic != MAKEMAGIC || t->size != n)
	{
		error(1, "%s is not a version %d make object file", objfile, VERSION);
		free(p);
		return(0);
	}
	if (h->version != VERSION)
	{
		error(1, "version %d object %s is not compatable with version %d loader", h->version, objfile, VERSION);
		free(p);
		return(0);
	}
	if (!h->biton || h->bitoff ||
		 h->salign != align(1) ||
		 h->slist != sizeof(struct list) ||
		 h->srule != sizeof(struct ruleinfo) ||
		 h->svar != sizeof(struct varinfo))
	{
		error(1, "%s object not compatable with %s", objfile, version);
		free(p);
		return(0);
	}
	oattribute = special.attribute;
#if DEBUG
	message(-4, "lists=%d rules=%d variables=%d", t->lists, t->rules, t->variables);
#endif

	/*
	 * compute pointers to the compiled data
	 */

	r = (struct ruleinfo*)(p + sizeof(struct headinfo));
	d = (struct list*)((char*)r + t->rules * sizeof(struct ruleinfo));
	v = (struct varinfo*)((char*)d + t->lists * sizeof(struct list));

	/*
	 * compute the relocation offsets
	 */

	ruloff = (unsigned long)(r - 1);
	lstoff = (unsigned long)(d - 1);
	stroff = (unsigned long)((char*)v + (t->variables * sizeof(struct varinfo) - 1));

	/*
	 * relocate the variables and check for any frozen
	 * variables that may have changed
	 */

	recompile = 0;
	ov = v;
	for (n = t->variables; n-- > 0; v++)
	{
		relocate(char*, v->name, stroff);
		relocate(char*, v->value, stroff);
		if (!(x = getvar(v->name))) x = v;
		if (v->frozen && (v == x && (v->oldvalue || v->import && *v->value) || strcmp(x->value, v->value)))
		{
			error(1, "frozen %svariable %s changed", v->import ? "environment " : x->readonly ? "command argument " : null, v->name);
			recompile = 1;
		}
		else v->oldvalue = 0;
	}
	if (recompile)
	{
		/*
		 * file must be recompiled if any frozen vars changed
		 */

		free(p);
		return(0);
	}
	v = ov;

	/*
	 * enter the variables
	 */

	vartab->flags &= ~HASH_ALLOCATE;
	for (n = t->variables; n-- > 0; v++)
		if (!(x = getvar(v->name)) || !x->readonly)
			(void)putvar((char*)0, v);
	vartab->flags |= HASH_ALLOCATE;

	/*
	 * relocate the dependency lists
	 */

	for (n = t->lists; n-- > 0; d++)
	{
		if (d->next) d->next = d + 1;
		relocate(struct ruleinfo*, d->item.rule, ruloff);
	}

	/*
	 * relocate and enter the rules
	 */

	rultab->flags &= ~HASH_ALLOCATE;
	for (n = t->rules; n-- > 0; r++)
	{
		register struct ruleinfo	*o;

		relocate(char*, r->name, stroff);
		relocate(char*, r->data, stroff);
		relocate(struct list*, r->deps, lstoff);
		if (!r->cmdspecial)
		{
			relocate(char*, r->precmds, stroff);
			relocate(char*, r->poscmds, stroff);
		}
		if (r->operator)
		{
			ctype[r->name[0]] |= C_OP1;
			ctype[r->name[1]] |= C_OP2;
		}
		if (o = getrule(r->name)) o->mark = 1;
		r->name = putrule((char*)0, r);
		r->link = (struct ruleinfo*)0;
	}
	rultab->flags |= HASH_ALLOCATE;

	/*
	 * associate one rule with each name
	 */
	
	exhash(rultab, atomize);

	/*
	 * readjust the internal rule pointers
	 */

	initrules();

	/*
	 * check for user attribute consistency
	 */

	if (special.attribute->uattributes < oattribute->uattributes && special.attribute->uattributes != UTOOMANY)
	{
		error(1, "%s out of date -- new attributes have been defined", objfile);
		return(0);
	}
	return(1);
}
