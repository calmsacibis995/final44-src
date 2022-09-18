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
 * make support routines
 */

#include "make.h"
#include <signal.h>

/*
 * error and message formatter
 * lev is the error level
 * lev >= 2 exits
 * lev < 0 is for debug tracing
 */

/*VARARGS2*/
void
error(lev, fmt, a1, a2, a3, a4, a5, a6, a7, a8)
int	lev;
char	*fmt;
{
	register FILE	*fd;
	int		i, sys;

	if (lev < state.debug) return;
	fd = lev ? stderr : stdout;
	sys = 0;
	switch (lev)
	{
	case 0:
		/* information */
		break;
	case 1:
		/* warning */
		if (state.silent) return;
		fprintf(fd, "%s: (warning) ", special.command);
		break;
	case 2:
		/* error */
		fprintf(fd, "%s: ", special.command);
		sys = state.debug < 0;
		break;
	default:
		/* debug (<0) or internal error */
#if DEBUG
		if (lev > 128 || lev < -128)
		{
			fprintf(fd, "%s: (%s, line %d) ", special.command, (char*)lev, (int)fmt);
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
			fprintf(fd, "%s: (internal %d) ", special.command, lev);
			sys = 1;
		}
		else
		{
			if (state.debug < -1) fprintf(fd, "%s: (debug %d) ", special.command, -lev);
			else fprintf(fd, "%s: (debug) ", special.command);
			for (i = 0; i < state.level; i++)
				fprintf(fd, "  ");
		}
		break;
	}
	if (sys && errno > 0 && errno <= sys_nerr && errno != ENOENT && errno != EBADF)
		fprintf(fd, "[%s] ", sys_errlist[errno]);
	if (lev > 0 && yyline) fprintf(fd, "%s, line %d: ", yyfile, yyline);
	if (fmt) fprintf(fd, fmt, a1, a2, a3, a4, a5, a6, a7, a8);
	fprintf(fd, "\n");
	fflush(fd);
	errno = 0;
	if (lev >= 2)
	{
		if (state.child)
		{
			kill(getpid(), SIGKILL);
			pause();
		}
		finish(lev - 1);
	}
}

/*
 * called by yyparse()
 */

void
yyerror(s)
char	*s;
{
	error(2, "%s", s);
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
 * check if a rule name is special
 * special names are ignored when checking for the main target
 */

int
isspecial(r)
register struct ruleinfo	*r;
{
	register char	*a;

	if (r->operator || r->state) return(1);
	a = r->name;
	if (!*a) return(1);
	if (strchr(a, '/')) return(0);
	if (*a == '.' || a[strlen(a) - 1] == '.') return(1);
	while (*a) if (*a++ == '.' && *a == '.') return(1);
	return(0);
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
 * generate C_SPACE separated tokens from a string
 * "\n" is returned as a token
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

	while (ctype[*p] & C_SPACE) p++;
	if (!*p)
	{
		token.state = 0;
		return((char*)0);
	}

	/*
	 * find the end of this token
	 */

	if (*p == '\n') r = p + 1;
	else for (r = p; *r && !(ctype[*r] & C_SPACE); r++);

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
 * check if any characters in s have type t
 */

int
any(s, t)
register char	*s;
register int	t;
{
	while (*s)
		if (ctype[*s++] & t)
			return(1);
	return(0);
}

static struct list	*firstpost;	/* first post command in list	*/
static struct list	*lastpost;	/* last post command in list	*/

/*
 * add a command sequence to the post command list
 */

void
addpost(cmd, always)
register char	*cmd;
int		always;
{
	if (cmd)
	{
		state.work = 1;
		(void)expand(cmd, buf1 + 1);
		*buf1 = always ? 'A' : '*';
		cmd = COPY(buf1);
		if (!firstpost) firstpost = lastpost = cons(cmd, NIL);
		else lastpost = lastpost->next = cons(cmd, NIL);
	}
}

/*
 * execute the commands in the post command list
 */

void
dopost()
{
	register struct list	*p;

	if (!state.touch && firstpost)
	{
		message(-2, "executing post commands");
		special.post->make = 0;
		for (p = firstpost, firstpost = NIL; p; p = p->next)
			docmd(special.post, p->item.string + 1, *p->item.string == 'A');
	}
}

/*
 * add a single non-duplicated dependency d to rule r
 */

void
adddep(r, d)
register struct ruleinfo	*r;
struct ruleinfo			*d;
{
	register struct list	*p;

	if (p = r->deps)
	{
		while (p)
		{
			if (d == p->item.rule) return;
			if (!p->next)
			{
				if (state.autocompile) r->compiled = 0;
				p->next = cons((GENERIC)d, NIL);
				break;
			}
			p = p->next;
		}
	}
	else
	{
		if (state.autocompile) r->compiled = 0;
		r->deps = cons((GENERIC)d, NIL);
	}
}

/*
 * append a list q onto the end of list p
 * list p is surgically modified
 */

struct list*
append(p, q)
struct list	*p, *q;
{
	register struct list	*t;

	if (t = p)
	{
		if (q)
		{
			while (t->next) t = t->next;
			t->next = q;
		}
		return(p);
	}
	else return(q);
}

/*
 * add item i onto the front of list p
 * list p is not modified
 */

struct list*
cons(i, p)
GENERIC		i;
struct list	*p;
{
	register struct list	*q;

	q = ALLOCATE(struct list);
	q->next = p;
	q->item.list = (struct list*)i;
	return(q);
}

/*
 * construct and return a copy of list p
 * the items in the list are not copied
 */

struct list*
copy(p)
register struct list	*p;
{
	register struct list	*q, *r;

	if (!p) return(NIL);
	q = r = ALLOCATE(struct list);
	while (p)
	{
		q->item.list = p->item.list;
		if (p = p->next) q = q->next = ALLOCATE(struct list);
	}
	q->next = NIL;
	return(r);
}

/*
 * convert time t to a string for tracing
 * max of 3 simultaneous times
 */

char*
stime(t)
time_t	t;
{
	register char	*s;
	static char	tm1[21], tm2[21], tm3[21];
	static char	*tm;
	extern char	*ctime();

	if (!t) return("not found");
	else if (t == NOTIME) return("not checked");
	else if (t == OLDTIME) return("really old");
	else if (t == OLDTIME + 1) return("very old");
	else
	{
		s = ctime(&t);
		s[24] = '\0';
		if (tm == tm1) tm = tm2;
		else if (tm == tm2) tm = tm3;
		else tm = tm1;
		return(strcpy(tm, s + 4));
	}
}
