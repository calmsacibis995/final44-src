%{

/*
 * G. S. Fowler
 * AT&T Bell Laboratories
 */

/*
 * makefile grammar
 */

#include "make.h"

%}

%term	APPEND COMMANDS ELLIPSIS NAME OP VALUE

%union
{
	struct ruleinfo	*rule;
	struct list	*list;
	char		*string;
}

%type	<rule>		rule, targets, OP
%type	<list>		dependencies, deplist
%type	<string>	COMMANDS, NAME, VALUE, precmds, poscmds

%%

%{

struct parseinfo			/* parser state info		*/
{
	unsigned char	archive;	/* .ARCHIVE			*/
	unsigned char	attribute;	/* .ATTRIBUTE			*/
	unsigned char	clear;		/* .CLEAR			*/
	unsigned char	current;	/* .CURRENT			*/
	unsigned char	dollar;		/* $				*/
	unsigned char	dontcare;	/* .DONTCARE			*/
	unsigned char	foreground;	/* .FOREGROUND			*/
	unsigned char	implicit;	/* .IMPLICIT			*/
	unsigned char	insert;		/* .INSERT			*/
	unsigned char	make;		/* .MAKE			*/
	unsigned char	notouch;	/* .NOTOUCH			*/
	unsigned char	null;		/* .NULL			*/
	unsigned char	operator;	/* .OPERATOR			*/
	unsigned char	parameter;	/* .PARAMETER			*/
	unsigned char	post;		/* .POST			*/
	unsigned char	search;		/* .SEARCH			*/
	unsigned char	state;		/* at least one state var dep	*/
	unsigned char	use;		/* .USE				*/

	unsigned char	uattributes;	/* user attributes		*/
};

static struct parseinfo	ps;		/* parser state info		*/

static struct ruleinfo	*firstrule;	/* first rule in list		*/
static struct ruleinfo	*lastrule;	/* last rule in list		*/

static struct list	*firstdep;	/* first dependency in list	*/
static struct list	*lastdep;	/* last dependency in list	*/

%}

file		:	file item
		|	/* empty */
		;

item		:	end
		|	NAME '=' VALUE end
		{
			vartab->flags &= ~HASH_ALLOCATE;
			(void)setvar($1, $3);
			vartab->flags |= HASH_ALLOCATE;
		}
		|	NAME APPEND VALUE end
		{
			char		*v;
			struct varinfo	*x;
			unsigned int	readonly;

			v = (x = getvar($1)) ? x->value : null;
			if (strlen(v) + strlen($3) >= MAXCMD) error(1, "cannot append to variable %s", $1);
			else
			{
				free($3);
				(void)strcopy(strcopy(strcopy(buf0, v), " "), $3);
				if (x)
				{
					readonly = x->readonly;
					x->readonly = 0;
				}
				vartab->flags &= ~HASH_ALLOCATE;
				(void)setvar($1, COPY(buf0));
				vartab->flags |= HASH_ALLOCATE;
				if (x) x->readonly = readonly;
			}
		}
		|	VALUE OP VALUE end precmds poscmds
		{
			register struct ruleinfo	*r, *otarget;
			static struct ruleinfo		*tmp;

			if (!(r = tmp))
			{
				r = tmp = ALLOCATE(struct ruleinfo);
				r->time = OLDTIME;
				r->deps = cons((GENERIC)ALLOCATE(struct ruleinfo), NIL);
				r->deps->item.rule->time = r->time + 1;
			}
			otarget = special.target;
			special.target = r;
			r->link = $2;
			r->name = $1;
			r->precmds = $5;
			r->poscmds = $6;
			r->deps->item.rule->name = $3;
			docmd($2, $2->precmds, $2->prealways);
			free($1);
			free($3);
			if ($5) free($5);
			if ($6) free($6);
			special.target = otarget;
			yyclearin;
		}
		|	targets dependencies end precmds poscmds
		{
			register struct ruleinfo	*r, *t;
			register struct list		*p, *q;

			r = $1;
			if (*r->name == '*')
			{
				struct ruleinfo	*n;
				char		nam[MAXFIX];

				/*
				 * convert "*.o : *.c x" to ".c.o : x"
				 */

				n = (struct ruleinfo*)0;
				t = r;
				q = NIL;
				while (t)
				{
					if (*t->name != '*') error(1, "invalid pattern match rule `%s'", t->name);
					if (*(t->name + 1)) adddep(special.suffixes, makerule(t->name + 1));
					for (p = $2; p; p = p->next)
					{
						if (*p->item.rule->name == '*')
						{
							/*
							 * suffix
							 */

							(void)strcpy(nam, p->item.rule->name + 1);
							if (*(p->item.rule->name + 1))
								adddep(special.suffixes, makerule(p->item.rule->name + 1));
						}
						else if (*p->item.rule->name && p->item.rule->name[strlen(p->item.rule->name)-1] == '*')
						{
							/*
							 * prefix
							 */

							(void)strcpy(nam, p->item.rule->name);
							nam[strlen(nam - 1)] = '\0';
							if (*nam) adddep(special.prefixes, makerule(nam));
						}
						else
						{
							/*
							 * implicit dependency
							 */

							if (!t->link) q = append(q, cons((GENERIC)p->item.rule, NIL));
							continue;
						}
						(void)strcat(nam, t->name + 1);
						r = makerule(nam);
						r->link = n;
						n = r;
					}
					r = t;
					t = t->link;
					r->link = (struct ruleinfo*)0;
				}
				$2 = q;
				r = n;
			}
			else if (!special.main->deps && !state.builtin && !ps.operator && !isspecial(r))
			{
				special.main->deps = cons(r, NIL);
				special.main->compiled = 0;
			}
			while (r)
			{
				if (ps.clear)
				{
					r->deps = NIL;
					r->precmds = (char*)0;
					r->poscmds = (char*)0;
					r->attribute = 0;
					r->current = 0;
					r->dontcare = 0;
					r->dynamic = 0;
					r->foreground = 0;
					r->implicit = 0;
					r->make = 0;
					r->notouch = 0;
					r->null = 0;
					r->parameter = 0;
					r->post = 0;
					r->search = 0;
					r->statedeps = 0;
					r->use = 0;
					r->uattributes = 0;
				}
				p = r->link ? copy($2) : $2;
				r->deps = ps.insert ? append(p, r->deps) : append(r->deps, p);

				/*
				 * remove duplicate dependencies
				 * NOTE: r->mark is 0 in steady state
				 */

				for (p = r->deps, q = NIL; p; p = p->next)
				{
					if (p->item.rule->mark)
					{
#if DEBUG
						if (!q) error(INTERNAL, "stray mark on `%s'", p->item.rule->name);
#endif
						q->next = p->next;
					}
					else
					{
						p->item.rule->mark = 1;
						q = p;
					}
				}
				for (p = r->deps; p; p = p->next)
					p->item.rule->mark = 0;

				/*
				 * check command lists
				 */

				if ($4)
				{
					if (r->precmds && !isspecial(r))
						error(1, "multiple pre-commands for `%s'", r->name);
					r->precmds = $4;
					r->prealways = strmatch($4, "*$(MAKE)*");
				}
				if ($5)
				{
					if (r->poscmds && !isspecial(r))
						error(1, "multiple post-commands for `%s'", r->name);
					r->poscmds = $5;
					r->posalways = strmatch($5, "*$(MAKE)*");
				}
				if (ps.archive) r->archive = 1;
				if (ps.attribute)
				{
					r->attribute = 1;
					if (special.attribute->uattributes == UTOOMANY)
						error(1, "%s: too many user attributes", r->name);
					else
					{
						r->uattributes = special.attribute->uattributes;
						if (!(special.attribute->uattributes <<= 1))
							special.attribute->uattributes = UTOOMANY;
					}
				}
				if (ps.current) r->current = 1;
				if (ps.dollar || strchr(r->name, '$')) r->dynamic = 1;
				if (ps.dontcare) r->dontcare = 1;
				if (ps.foreground) r->foreground = 1;
				if (ps.implicit) r->implicit = 1;
				if (ps.make) r->make = 1;
				if (ps.notouch) r->notouch = 1;
				if (ps.null) r->null = 1;
				if (ps.operator)
				{
					register char	*s = r->name;

					r->operator = 1;
					if (strlen(s) == 2)
					{
						ctype[s[0]] |= C_OP1;
						ctype[s[1]] |= C_OP2;
					}
					else error(1, "operator `%s' must be two characters long", s);
				}
				if (ps.parameter) r->parameter = 1;
				if (ps.post) r->post = 1;
				if (ps.search) r->search = 1;
				if (ps.state) r->statedeps = 1;
				if (ps.use) r->use = 1;
				r->uattributes |= ps.uattributes;
				r->target = 1;
				if (r->immediate) immediate(r);
				if (state.autocompile) r->compiled = 0;
				t = r;
				r = r->link;
				t->link = (struct ruleinfo*)0;
			}
		}
		|	error
		;

targets		:	rule
		{
			$$ = firstrule = lastrule = $1;
			lastrule->link = (struct ruleinfo*)0;
		}
		|	targets rule
		{
			if ($2->link || $2 == lastrule)
				error(1, "`%s' appears more than once in the same target list", $2->name);
			else lastrule = lastrule->link = $2;
			$$ = firstrule;
		}
		;

rule		:	NAME
		{
			rultab->flags &= ~HASH_ALLOCATE;
			$$ = makerule($1);
			rultab->flags |= HASH_ALLOCATE;
		}
		;

dependencies	:	':' deplist
		{
		 	$$ = $2;
		}
		;

deplist		:	/* empty */
		{
			clearstate(ps);
			$$ = firstdep = lastdep = NIL;
		}
		|	deplist rule
		{
			if ($2->attribute)
			{
				if ($2 == special.archive) ps.archive = 1;
				else if ($2 == special.attribute) ps.attribute = 1;
				else if ($2 == special.clear) ps.clear = 1;
				else if ($2 == special.current) ps.current = 1;
				else if ($2 == special.dontcare) ps.dontcare = 1;
				else if ($2 == special.foreground) ps.foreground = 1;
				else if ($2 == special.implicit) ps.implicit = 1;
				else if ($2 == special.insert) ps.insert = 1;
				else if ($2 == special.make) ps.make = 1;
				else if ($2 == special.notouch) ps.notouch = 1;
				else if ($2 == special.null) ps.null = 1;
				else if ($2 == special.operator) ps.operator = 1;
				else if ($2 == special.parameter) ps.parameter = 1;
				else if ($2 == special.post) ps.post = 1;
				else if ($2 == special.search) ps.search = 1;
				else if ($2 == special.use) ps.use = 1;
				else if ($2->uattributes) ps.uattributes |= $2->uattributes;
			}
			else
			{
				if (!ps.dollar && strchr($2->name, '$')) ps.dollar = 1;
				if ($2->state) ps.state = 1;
				if (!firstdep) firstdep = lastdep = cons((GENERIC)$2, NIL);
				else lastdep = lastdep->next = cons((GENERIC)$2, NIL);
			}
			$$ = firstdep;
		}
		;

precmds		:	COMMANDS
		{
			$$ = $1;
		}
		|	/* empty */
		{
			$$ = (char*)0;
		}
		;

poscmds		:	ELLIPSIS COMMANDS
		{
			$$ = $2;
		}
		|	/* empty */
		{
			$$ = (char*)0;
		}
		;

end		:	';'
		|	'\n'
		;
