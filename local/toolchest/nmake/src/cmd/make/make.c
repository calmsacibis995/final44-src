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
 * make target proof algorithm
 */

#include "make.h"

static struct ruleinfo	*changed;

static int		make0();
static void		update();
static int		move();
static int		isintdep();
static int		invalidate();

/*
 * top level make initialization
 *
 * r->status determines the status of each rule:
 *
 *	NOTYET	nothing done yet
 *	UPDATE	rule in process of being updated
 *	MAKING	rule update commands being executed
 *	EXISTS	rule has already been made
 *	FAILED	rule make failed
 */

void
make(r)
register struct ruleinfo	*r;
{
	time_t	ttarget;

	state.work = 0;
	if (make0((struct ruleinfo*)0, r, &ttarget))
	{
		if (r->precmds)
			error(1, "`%s' not made because of errors", r->name);
	}
	else if (state.question)
		exit(state.work ? -1 : 0);
	else if (!state.work && (r->precmds || !r->target))
		error(0, "`%s' is up to date", r->name);
	if (state.nomade) state.made = state.nomade = 0;
	else state.made = 1;
}

/*
 * basic algorithm after top level initialization
 */

static int
make0(parent, r, ttarget)
struct ruleinfo			*parent;
register struct ruleinfo	*r;
time_t				*ttarget;
{
	register struct list		*p, *s;
	register struct ruleinfo	*r1;
	time_t				t, tdeps, otime, tsrc;
	char				fix[MAXFIX];
	char				nam[MAXNAME];
	int				errors, fixrule;
	struct ruleinfo			*r2, *otarget, *exact, *post, *lastpost;
	struct list			*odeps;

	/*
	 * check if rule has been or is in the process of being made
	 */

	message(-1, "make(%s)", r->name);
	errors = 0;
	state.level++;
	if (r->status != NOTYET)
	{
		if (r->status == MAKING) (void)complete(NIL, r);
		if (!r->notouch)
		{
			message(-1, "time(%s) = %s", r->name, stime(r->time));
			state.level--;
			*ttarget = r->time;
			if (state.oldfile && !r->make && !r->notouch && !r->state)
			{
				printf("make %s\n", r->name);
				printf("done %s\n", r->name);
			}
			return(r->status == FAILED);
		}
	}
	r->link = parent;
	r = bind(r);
	otarget = special.target;
	special.target = r;
	if (r->dynamic) dynamic(r);
	tdeps = tsrc = 0;
	post = exact = (struct ruleinfo*)0;
	fixrule = 0;
	otime = r->time;

	/*
	 * r->deps may be surgically appended 
	 * odeps is used to restore the end of the
	 * original r->deps before make0() exits
	 */

	for (odeps = NIL, p = r->deps; p; p = p->next)
		if (!p->next)
		{
			odeps = p;
			break;
		}
	r->status = UPDATE;
	message(-1, "time(%s) = %s", r->name, stime(r->time));
	if (state.oldfile && !r->make && !r->notouch && !r->state)
	{
		printf("make %s\n", r->name);
		if (r->archive) printf("arch %s\n", r->name);
	}

	/*
	 * check for file changes since the last make
	 * the changes take a few forms:
	 *
	 *	o  the file has state var deps and the modify
	 *	   time has changed since the last make
	 *
	 *	o  the file is from a different directory than
	 *	   the last make -- this is checked by using
	 *	   the modify time of the file which may fail
	 *	   (low probability) if the two source files
	 *	   in question have both the same (base) name
	 *	   and the same modify time -- using modify
	 *	   times avoids saving the (dev,ino) numbers
	 *	   for each file
	 *
	 * notice that this technique detects when an old source
	 * file is reinstated and forces updating just as if
	 * the file had been touched
	 */

	if (!r->state)
	{
		sprintf(nam, "%s()", unbound(r));
		if ((r1 = getrule(nam)) || r->statedeps || r->search || r->time)
		{
			if (!r1) r1 = makerule(nam);
			if (r1->search) r->statedeps = 1;
			if (r->time != r1->time)
			{
				if (state.accept)
				{
					state.savestate = 1;
					r1->time = r->time;
				}
				else if (r->statedeps)
				{
					if (r1->search) message(-2, "%s previously invalidated", unbound(r));
					else message(-2, "state variables may have changed");
					tdeps = CURTIME;
				}
				else if (r->search)
				{
					if (r1->time > r->time)
					{
						error(1, "%s source has changed", unbound(r));

						/*
						 * invalidate internal targets that depend on r
						 */

						changed = r;
						exhash(rultab, invalidate);
					}
					tsrc = CURTIME;
					exact = r1;
				}
			}
		}
	}

	/*
	 * check global (insert) dependencies
	 */

	if (r->null) *fix = '\0';
	else (void)edit(fix, r->name, DELETE, DELETE, DELETE, DELETE, KEEP);
	if (*fix || r->null)
	{
		sprintf(nam, ".GLOBAL%s", fix);
		if ((r1 = getrule(nam)) && r1->deps)
		{
			p = copy(r1->deps);
			if (r1->dynamic)
			{
				r1->link = r;
				dynamic(r1);
				r1->link = (struct ruleinfo*)0;
				r1->dynamic = 1;
			}
			r->deps = append(r1->deps, r->deps);
			r1->deps = p;
		}
	}

	/*
	 * check explicit dependencies
	 */

	message(-2, "check explicit dependencies");
	for (p = r->deps; p; p = p->next)
	{
		if (p->item.rule->post)
		{
			if (!post) post = lastpost = p->item.rule;
			else lastpost = lastpost->link = p->item.rule;
			lastpost->link = (struct ruleinfo*)0;
		}
		else if (p->item.rule->use)
		{
			r1 = p->item.rule;
			s = copy(r1->deps);
			if (r1->dynamic)
			{
				r1->link = r;
				dynamic(r1);
				r1->link = (struct ruleinfo*)0;
				r1->dynamic = 1;
			}
			r->deps = append(r->deps, r1->deps);
			r1->deps = s;
			r->precmds = r1->precmds;
			r->poscmds = r1->poscmds;
			r->uattributes |= r1->uattributes;
			if (r1->current) r->current = 1;
			if (r1->foreground) r->foreground = 1;
			if (r1->implicit) r->implicit = 1;
			if (r1->make) r->make = 1;
		}
		else
		{
			errors += make0(r, p->item.rule, &t);
			if (tdeps < t) tdeps = t;
		}
	}

	/*
	 * check implicit suffix dependencies
	 */

	if (special.suffixes->deps && !r->state)
	{
		message(-2, "check implicit dependencies");
		if (*fix || !odeps || r->implicit)
		{
			for (s = special.suffixes->deps; s; s = s->next)
			{
				sprintf(nam, "%s%s", s->item.rule->name, fix);
				if ((r1 = getrule(nam)) && r1->target)
				{
#if DEBUG
					message(-6, "implicit suffix rule: %s", r1->name);
#endif
					(void)edit(nam, r->name, DELETE, DELETE, DELETE, KEEP, s->item.rule->name);
					r2 = bindfile(nam, 0);
					if (r2 && (r2->time || r2->target))
					{
						fixrule = 1;
						errors += make0(r, r2, &t);
						if (tdeps < t) tdeps = t;

						/*
						 * check dependencies from the implicit rule
						 */

						for (p = r1->deps; p; p = p->next)
						{
							if (p->item.rule->post)
							{
								if (!post) post = lastpost = p->item.rule;
								else lastpost = lastpost->link = p->item.rule;
								lastpost->link = (struct ruleinfo*)0;
							}
							else if (!p->item.rule->use)
							{
								r->deps = append(r->deps, cons((GENERIC)p->item.rule, NIL));
								errors += make0(r, p->item.rule, &t);
								if (tdeps < t) tdeps = t;
							}
						}
						if (r->time < tdeps)
							errors += dofix(r, r1, r2, POST|SUFFIX|(*fix?CURRENT:0));
						break;
					}
				}
			}
			if (!s && r->implicit && !state.override)
				error(2, "cannot find source for `%s'", r->name);
		}
	}
	else *fix = '\0';

	/*
	 * determine the update rule if no implicit rule applied
	 */

	r1 = (struct ruleinfo*)0;
	if (!fixrule)
	{
		if (r->precmds) r1 = r;
		else if ((!r->archive && r->null && (r1 = getrule(fix)) && r1->precmds) ||
			 (r->archive && r->target && (r1 = getrule(".a")) && r1->precmds) ||
			 ((r1 = getrule(".DEFAULT")) && r1->precmds))
		{
			/*
			 * check dependencies from the update rule
			 */

			for (p = r1->deps; p; p = p->next)
			{
				if (p->item.rule->post)
				{
					if (!post) post = lastpost = p->item.rule;
					else lastpost = lastpost->link = p->item.rule;
					lastpost->link = (struct ruleinfo*)0;
				}
				else if (!p->item.rule->use)
				{
					r->deps = append(r->deps, cons((GENERIC)p->item.rule, NIL));
					errors += make0(r, p->item.rule, &t);
					if (tdeps < t) tdeps = t;
				}
			}
		}
	}

	/*
	 * make sure all dependencies have completed
	 */

	errors += complete(r->deps, (struct ruleinfo*)0);

	/*
	 * do the explicit commands
	 */

	message(-2, "errs=%d, targ=%s, deps=%s", errors, stime(r->time), stime(tdeps));
	if (!errors && (r->time < tdeps || !r->time))
	{
		if (r1)
		{
			update(r, (struct ruleinfo*)0, r1, CURRENT|POST|SUFFIX);
			r->time = CURTIME;
		}
		else if (!r->dontcare)
		{
			if (!r->target || fixrule)
			{
				error(state.keepgoing ? 1 : 2, "don't know how to make `%s'", r->name);
				errors++;
			}
			r->time = CURTIME;
		}
	}
	else
	{
		if (r->status == UPDATE)
		{
			if (state.oldfile && !r->state) printf("file %s\n", r->name);
			if (r->search)
			{
				/*
				 * check implicit file dependencies
				 */
	
				message(-2, "check implicit file dependencies");
				for (p = finddeps(r); p; p = p->next)
				{
					errors += make0(r, p->item.rule, &t);
					if (tdeps < t) tdeps = t;
				}
				if (!r->link->search)
				{
					sprintf(nam, "%s()", unbound(r->link));
					r1 = makerule(nam);
					if (!r1->search)
					{
						r1->deps = cons(r, NIL);
						r1->search = 1;
						r->link->statedeps = 1;
					}
				}
			}
			if (tdeps < tsrc) tdeps = tsrc;
			if (r->time < tdeps) r->time = tdeps;
		}
		if (r->status != MAKING) r->status = errors ? FAILED : EXISTS;
	}
	if (r->notouch) r->time = DEFTIME;
	else if (r->parameter) r->time = OLDTIME;
	else if (state.force) r->time = CURTIME;
	if (r->state && r->time != otime) state.savestate = 1;
	if (exact)
	{
		state.savestate = 1;
		exact->time = otime;
	}
	message(-1, "time(%s) = %s", r->name, stime(r->time));

	/*
	 * check explicit post dependencies
	 */

	if (post)
	{
		/*
		 * a notouch post command is only executed if the
		 * target has been updated
		 */

		message(-2, "check explicit post dependencies");
		for (; r1 = post; post = r1->link)
			if (!r1->notouch || r->time != otime)
				errors += make0(r, r1, &t);
	}

	/*
	 * restore the original dependencies for compile()
	 */

	if (odeps) odeps->next = NIL;

	/*
	 * restore previous target and return
	 */

	special.target = otarget;
	state.level--;
	*ttarget = (parent && parent->archive && !r->member && !r->state) ? CURTIME : r->time;
	r->link = (struct ruleinfo*)0;
	if (state.oldfile && !r->make && !r->notouch && !r->state) printf("done %s\n", r->name);
	return(errors);
}

/*
 * common code for prefix and suffix command updates
 */

int
dofix(r, r1, r2, flags)
register struct ruleinfo	*r;
struct ruleinfo			*r1, *r2;
int				flags;
{
	int		errors = 0;
	time_t		otime;
	struct list	tmp;

	if (flags&CURRENT) r->current = 1;
	if ((flags&SUFFIX) || !state.touch)
	{
		special.explicit = r->deps;
		r->deps = &tmp;
		tmp.item.rule = r2;
		tmp.next = NIL;
		otime = r2->time;
		r2->time = CURTIME;
		errors += complete(r->deps, (struct ruleinfo*)0);
		update(r, r2, r1, flags);
		r->deps = special.explicit;
		r2->time = otime;
		special.explicit = NIL;
	}
	r->bound = 1;
	r->time = CURTIME;
	return(errors);
}

/*
 * execute update commands
 * r is the target (possibly with explicit update commands)
 * r1 is the primary source
 * r2 is the implicit update command rule
 */

static void
update(r, r1, r2, flags)
register struct ruleinfo	*r, *r1, *r2;
int				flags;
{
	char	fix[MAXNAME];
	int	oforeground;

	if (state.override)
	{
		/*
		 * save explicit target generation for non-override runs
		 */

		if (r == r2 && r->time) return;
	}
	else if (r->precmds) r2 = r;
	if (!r->current)
	{
		if (r->target && (r->precmds || r->null)) r->current = 1;
		else if (!(flags&SUFFIX))
		{
			register struct ruleinfo	*x;

			(void)edit(fix, r->name, DELETE, DELETE, KEEP, DELETE, DELETE);
			if ((x = getrule(fix)) && x->current) r->current = 1;
		}
	}
	if (r->current && r->uname && !r->state) r->name = r->uname;
	if (!r->time) flags |= POST;
	message(-1, "executing `%s' commands", r2->name);
	oforeground = state.foreground;
	if (r->foreground || r2->foreground) state.foreground = 1;
	if (!r->current || !state.move || !move(r, r1, r2)) docmd(r2, r2->precmds, r2->prealways);
	if (flags&POST) addpost(r2->poscmds, r2->posalways);
	state.foreground = oforeground;
}

/*
 * move target to primary source directory
 */

static int
move(r, r1, r2)
register struct ruleinfo	*r, *r1, *r2;
{
	int	moved;
	char	buf[MAXCMD];
	char	dir[MAXNAME], nam[MAXNAME];

	moved = 0;
	if (r1 && !r->link->archive)
	{
		/*
		 * don't move targets with explicit directories
		 */

		(void)edit(dir, r->name, DELETE, KEEP, DELETE, DELETE, DELETE);
		if (!*dir)
		{
			(void)edit(dir, r1->name, DELETE, KEEP, DELETE, DELETE, DELETE);
			if (*dir)
			{
				sprintf(buf, "%s\n$(MV) %s %s", r2->precmds, r->name, dir);
				(void)edit(nam, r->name, KEEP, dir, KEEP, KEEP, KEEP);
				r->name = putrule(nam, r);
				docmd(r2, buf, r2->prealways);
				moved = 1;
			}
		}
	}
	return(moved);
}

/*
 * return 1 if d is an internal dependency of r
 */

static int
isintdep(r, d)
register struct ruleinfo	*r, *d;
{
	register struct ruleinfo	*x;
	register struct list		*p;
	char				nam[MAXNAME];

	for (p = r->deps; p; p = p->next)
	{
		if (p->item.rule == d) return(1);
		sprintf(nam, "%s()", p->item.rule->name);
		if ((x = getrule(nam)) && isintdep(x, d)) return(1);
	}
	return(0);
}

/*
 * invalidate internal targets that depend on changed
 */

/*ARGSUSED*/
static int
invalidate(s, r)
char				*s;
register struct ruleinfo	*r;
{
	if (r->state && r->search && r->time && isintdep(r, changed))
	{
		message(-2, "invalidate(%s)", r->name);
		r->time = DEFTIME;
		state.savestate = 1;
	}
	return(0);
}
