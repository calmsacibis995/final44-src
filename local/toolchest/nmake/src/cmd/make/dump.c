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
 * make dump and trace routines
 */

#include "make.h"

/*
 * print a command sequence placing pfx at the beginning of each line
 */

void
dumpcmd(fd, cmd, pfx)
FILE		*fd;
register char	*cmd, *pfx;
{
	register char	*s;
	register int	c;

	if (state.oldfile)
	{
		fprintf(fd, "exec ");
		for (s = cmd; *s; s++)
		{
			if (*s == '\n') fprintf(fd, "; ");
			else fputc(*s, fd);
			if (*s == '<' && *(s + 1) == '<')
				error(1, "%s: here documents not supported in old makefiles", special.target->name);
		}
		fputc('\n', fd);
	}
	else
	{
		for (s = cmd; *s; s++)
		{
			for (cmd = s; *s && *s != '\n'; s++);
			c = *s;
			*s = '\0';
			fprintf(fd, "%s%s\n", pfx, cmd);
			if (!(*s = c)) break;
		}
	}
	fflush(fd);
}

/*
 * print a single variable and its value
 */

static int
dumpvar(s, v)
char		*s;
struct varinfo	*v;
{
	if (!v->import && (!state.list || *v->name != '.'))
	{
		printf("%s = %s", s, v->value);
		if (!state.list)
		{
			if (v->frozen) printf(" [frozen]");
			if (v->import) printf(" [import]");
			if (v->oldvalue) printf(" [oldvalue]");
			if (v->readonly) printf(" [readonly]");
		}
		printf("\n");
		fflush(stdout);
	}
	return(0);
}

/*
 * print a rule name in re-readable form
 */

static void
dumpname(s, sep)
register char	*s;
char		*sep;
{
	register char	*t;
	register int	paren;
	int		quote;

	for (t = s, paren = 0; *t && (paren || !(ctype[*t] & (C_COLEQU|C_OP1|C_SPACE|C_TERMINAL))); t++)
		if (*t == '(') paren++;
		else if (*t == ')') paren--;
	if (quote = (*t || t == s)) putchar('"');
	for (; *s; s++)
	{
		if (*s == '$') putchar(*s);
		putchar(*s);
	}
	if (quote) putchar('"');
	printf("%s", sep);
}

/*
 * print a single rule and its attributes
 */

int
dumprule(s, r)
char				*s;
register struct ruleinfo	*r;
{
	register struct list		*p;
	register struct ruleinfo	*a;

	if (state.list && ((r->attribute && !r->uattributes) || !r->target || r->name != s)) return(0);
	putchar('\n');
	dumpname(r->state || !state.list ? s : unbound(r), null);
	printf(" : ");
	if (!r->attribute && r->uattributes)
	{
		for (a = special.attribute->link; a; a = a->link)
			if (r->uattributes & a->uattributes)
				printf("%s ", a->name);
	}
	if (!state.list)
	{
		printf("%s ", stime(r->time));
		if (r->archive) printf("[archive] ");
		if (r->member) printf("[archive member] ");
		if (r->state) printf("[state variable] ");
		if (r->compiled) printf("[compiled] ");
		if (r->attribute)
		{
			if (r->uattributes) printf("[uattributes=0x%08x] ", r->uattributes);
			else printf("[attribute] ");
		}
		if (r->current) printf("[current] ");
		if (r->dontcare) printf("[don't care] ");
		if (r->foreground) printf("[foreground] ");
		if (r->immediate) printf("[immediate] ");
		if (r->make) printf("[make] ");
		if (r->notouch) printf("[notouch] ");
		if (r->null) printf("[null] ");
		if (r->operator) printf("[operator] ");
		if (r->parameter) printf("[parameter] ");
		if (r->post) printf("[post] ");
		if (r->search) printf("[search] ");
		if (r->statedeps) printf("[state dependencies] ");
		if (r->use) printf("[use] ");
		if (!r->bound) printf("[unbound] ");
		else switch (r->status)
		{
		case NOTYET:
			printf("[not checked]");
			break;
		case UPDATE:
			printf("[updating]");
			break;
		case MAKING:
			printf("[making]");
			break;
		case EXISTS:
			printf("[done]");
			break;
		case FAILED:
			printf("[error]");
			break;
#if DEBUG
		default:
			printf("[unknown %d]", r->status);
			break;
#endif
		}
		putchar('\n');
	}
	else
	{
		if (r->attribute && r->uattributes) printf("%s ", special.attribute->name);
		if (r->foreground) printf("%s ", special.foreground->name);
		if (r->make) printf("%s ", special.make->name);
		if (r->archive) printf("%s ", special.archive->name);
		if (r->current) printf("%s ", special.current->name);
		if (r->search) printf("%s ", special.search->name);
		if (r->notouch) printf("%s ", special.notouch->name);
		if (r->null) printf("%s ", special.null->name);
		if (r->operator) printf("%s ", special.operator->name);
		if (r->parameter) printf("%s ", special.parameter->name);
		if (r->post) printf("%s ", special.post->name);
		if (r->use) printf("%s ", special.use->name);
	}
	if (p = r->deps)
	{
		if (!state.list) printf(" dependencies: ");
		for (; p; p = p->next)
			dumpname(p->item.rule->state ? p->item.rule->name : unbound(p->item.rule), " ");
		putchar('\n');
	}
	else if (state.list) putchar('\n');
	if (r->cmdspecial)
	{
		if (!state.list)
			printf(" special: 0x%06x 0x%06x\n", (unsigned long)r->precmds, (unsigned long)r->poscmds);
	}
	else if (state.list && r->precmds && !*r->precmds && (!r->poscmds || !*r->poscmds))
		printf("\t{ }");
	else
	{
		if (r->precmds)
		{
			if (!state.list)
				printf(" commands%s:\n", r->prealways?" [always]":null);
			dumpcmd(stdout, r->precmds, "\t");
		}
		if (r->poscmds)
		{
			if (!state.list)
				printf(" post commands%s:\n", r->posalways?" [always]":null);
			else if (*r->poscmds) printf("\t...\n");
			dumpcmd(stdout, r->poscmds, "\t");
		}
		if (!state.list && r->state && r->data) printf(" state: %s\n", r->data);
	}
	fflush(stdout);
	return(0);
}

/*
 * dump of internal data and dependencies
 */

void
dump(hash)
int	hash;
{
	if (state.vardump || state.ruledump) state.list = 0;
	if (hash) dumphash((TABLE)0);
	if (state.list) printf("/* %s */\n\n", version);
	if (state.list || state.vardump)
	{
		printf("\n/* Variables */\n\n");
		exhash(vartab, dumpvar);
	}
	if (state.list || state.ruledump)
	{
		printf("\n/* Rules */\n");
		exhash(rultab, dumprule);
	}
	fflush(stdout);
}
