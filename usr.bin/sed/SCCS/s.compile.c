h20737
s 00014/00006/00739
d D 8.2 95/04/28 15:26:33 bostic 11 10
c End of group (virtual) operators were sometimes dumping core because
c the memory wasn't being properly initialized.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00002/00743
d D 8.1 93/06/06 16:16:03 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00077/00038/00668
d D 5.8 93/04/18 03:41:39 torek 9 8
c fix broken label handling (rewrite label code completely)
e
s 00061/00036/00645
d D 5.7 93/03/07 16:14:34 bostic 8 7
c complain if whitespace after w, r, :, b or t objects, or if a label
c isn't used
e
s 00004/00002/00677
d D 5.6 92/11/02 09:25:32 bostic 7 6
c handle backslash and ampersand correctly; from Diomidis; examples:
c echo '\foo' | sed -e 's/\\/\\e/' -e 's/^/\\\&/'
c echo "foo" | sed -e 's/./\\\&/' produces \foo instead of \&oo.
c echo "foo" | sed -e 's/./\\&/' produces \&oo instead of \foo.
e
s 00007/00006/00672
d D 5.5 92/08/30 12:07:07 bostic 6 5
c don't access entries multiple times; from Diomidis
e
s 00010/00023/00668
d D 5.4 92/08/28 15:29:35 bostic 5 3
c make match (pmatch) a single global structure; change compile_re to
c calculate max nsub; addresses can't set REG_NOSUB because of default RE's
e
s 00002/00000/00691
d R 5.4 92/08/27 14:01:14 bostic 4 3
c fix the process linkages, but was that fd's got closed more than
c once, Diomidis says there were other bad effects as well.
e
s 00072/00059/00619
d D 5.3 92/08/24 21:27:35 bostic 3 2
c make empty RE's work, some minor cleanups, too
e
s 00009/00009/00669
d D 5.2 92/08/24 12:05:47 bostic 2 1
c updated error messages from Diomidis
e
s 00678/00000/00000
d D 5.1 92/08/23 18:25:29 bostic 1 0
c date and time created 92/08/23 18:25:29 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Diomidis Spinellis.
D 10
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis of Imperial College, University of London.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 3
#include  <sys/stat.h>
E 3
I 3
#include <sys/stat.h>
E 3

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "extern.h"

I 9
#define LHSZ	128
#define	LHMASK	(LHSZ - 1)
static struct labhash {
	struct	labhash *lh_next;
	u_int	lh_hash;
	struct	s_command *lh_cmd;
	int	lh_ref;
} *labels[LHSZ];

E 9
static char	 *compile_addr __P((char *, struct s_addr *));
static char	 *compile_delimited __P((char *, char *));
static char	 *compile_flags __P((char *, struct s_subst *));
D 3
static char	 *compile_re __P((char *, regex_t *, int));
static char	 *compile_subst __P((char *, char **, size_t));
E 3
I 3
D 5
static char	 *compile_re __P((char *, regex_t **, int));
E 5
I 5
static char	 *compile_re __P((char *, regex_t **));
E 5
static char	 *compile_subst __P((char *, struct s_subst *));
E 3
static char	 *compile_text __P((void));
static char	 *compile_tr __P((char *, char **));
static struct s_command
		**compile_stream __P((char *, struct s_command **, char *));
D 8
static char	 *duptoeol __P((char *));
E 8
I 8
static char	 *duptoeol __P((char *, char *));
I 9
static void	  enterlabel __P((struct s_command *));
E 9
E 8
static struct s_command
D 9
		 *findlabel __P((struct s_command *, struct s_command *));
D 6
static void	  fixuplabel __P((struct s_command *, struct s_command *));
E 6
I 6
static void	  fixuplabel __P((struct s_command *, struct s_command *,
		  	struct s_command *));
I 8
static void	  uselabel __P((struct s_command *));
E 9
I 9
		 *findlabel __P((char *));
static void	  fixuplabel __P((struct s_command *, struct s_command *));
static void	  uselabel __P((void));
E 9
E 8
E 6

/*
 * Command specification.  This is used to drive the command parser.
 */
struct s_format {
	char code;				/* Command code */
	int naddr;				/* Number of address args */
	enum e_args args;			/* Argument type */
};

static struct s_format cmd_fmts[] = {
	{'{', 2, GROUP},
	{'a', 1, TEXT},
	{'b', 2, BRANCH},
	{'c', 2, TEXT},
	{'d', 2, EMPTY},
	{'D', 2, EMPTY},
	{'g', 2, EMPTY},
	{'G', 2, EMPTY},
	{'h', 2, EMPTY},
	{'H', 2, EMPTY},
	{'i', 1, TEXT},
	{'l', 2, EMPTY},
	{'n', 2, EMPTY},
	{'N', 2, EMPTY},
	{'p', 2, EMPTY},
	{'P', 2, EMPTY},
	{'q', 1, EMPTY},
	{'r', 1, RFILE},
	{'s', 2, SUBST},
	{'t', 2, BRANCH},
	{'w', 2, WFILE},
	{'x', 2, EMPTY},
	{'y', 2, TR},
	{'!', 2, NONSEL},
	{':', 0, LABEL},
	{'#', 0, COMMENT},
	{'=', 1, EMPTY},
	{'\0', 0, COMMENT},
};

D 3
/* The compiled program */
E 3
I 3
D 5
/* Maximum number of parenthesized regular expressions found. */
static int nsub_max;

E 5
/* The compiled program. */
E 3
struct s_command *prog;

/*
 * Compile the program into prog.
D 3
 * Initialise appends
E 3
I 3
 * Initialise appends.
E 3
 */
void
compile()
{
	*compile_stream(NULL, &prog, NULL) = NULL;
D 6
	fixuplabel(prog, prog);
E 6
I 6
D 9
	fixuplabel(prog, prog, NULL);
E 9
I 9
	fixuplabel(prog, NULL);
	uselabel();
E 9
E 6
	appends = xmalloc(sizeof(struct s_appends) * appendnum);
I 5
	match = xmalloc((maxnsub + 1) * sizeof(regmatch_t));
E 5
}

#define EATSPACE() do {							\
	if (p)								\
		while (*p && isascii(*p) && isspace(*p))		\
			p++;						\
	} while (0)

static struct s_command **
compile_stream(terminator, link, p)
	char *terminator;
	struct s_command **link;
	register char *p;
{
	static char lbuf[_POSIX2_LINE_MAX + 1];	/* To save stack */
	struct s_command *cmd, *cmd2;
	struct s_format *fp;
	int naddr;				/* Number of addresses */

	if (p != NULL)
		goto semicolon;
	for (;;) {
		if ((p = cu_fgets(lbuf, sizeof(lbuf))) == NULL) {
			if (terminator != NULL)
				err(COMPILE, "unexpected EOF (pending }'s)");
			return (link);
		}

semicolon:	EATSPACE();
		if (p && (*p == '#' || *p == '\0'))
			continue;
		if (*p == '}') {
			if (terminator == NULL)
				err(COMPILE, "unexpected }");
			return (link);
		}
		*link = cmd = xmalloc(sizeof(struct s_command));
		link = &cmd->next;
D 8
		cmd->nonsel = cmd->inrange = 0;
E 8
I 8
D 9
		cmd->lused = cmd->nonsel = cmd->inrange = 0;
E 9
I 9
		cmd->nonsel = cmd->inrange = 0;
E 9
E 8
		/* First parse the addresses */
		naddr = 0;
D 11
		cmd->a1 = cmd->a2 = NULL;
E 11

/* Valid characters to start an address */
#define	addrchar(c)	(strchr("0123456789/\\$", (c)))
		if (addrchar(*p)) {
			naddr++;
			cmd->a1 = xmalloc(sizeof(struct s_addr));
			p = compile_addr(p, cmd->a1);
			EATSPACE();				/* EXTENSION */
			if (*p == ',') {
D 11
				naddr++;
E 11
				p++;
				EATSPACE();			/* EXTENSION */
I 11
				naddr++;
E 11
				cmd->a2 = xmalloc(sizeof(struct s_addr));
				p = compile_addr(p, cmd->a2);
D 11
			}
		}
E 11
I 11
				EATSPACE();
			} else
				cmd->a2 = 0;
		} else
			cmd->a1 = cmd->a2 = 0;
E 11

nonsel:		/* Now parse the command */
D 11
		EATSPACE();
E 11
		if (!*p)
			err(COMPILE, "command expected");
		cmd->code = *p;
		for (fp = cmd_fmts; fp->code; fp++)
			if (fp->code == *p)
				break;
		if (!fp->code)
			err(COMPILE, "invalid command code %c", *p);
		if (naddr > fp->naddr)
			err(COMPILE,
"command %c expects up to %d address(es), found %d", *p, fp->naddr, naddr);
		switch (fp->args) {
		case NONSEL:			/* ! */
D 11
			cmd->nonsel = ! cmd->nonsel;
E 11
			p++;
I 11
			EATSPACE();
			cmd->nonsel = ! cmd->nonsel;
E 11
			goto nonsel;
		case GROUP:			/* { */
			p++;
			EATSPACE();
			if (!*p)
				p = NULL;
			cmd2 = xmalloc(sizeof(struct s_command));
			cmd2->code = '}';
			*compile_stream("}", &cmd->u.c, p) = cmd2;
			cmd->next = cmd2;
			link = &cmd2->next;
I 11
			/*
			 * Short-circuit command processing, since end of
			 * group is really just a noop.
			 */
			cmd2->nonsel = 1;
			cmd2->a1 = cmd2->a2 = 0;
E 11
			break;
		case EMPTY:		/* d D g G h H l n N p P q x = \0 */
			p++;
			EATSPACE();
			if (*p == ';') {
				p++;
				link = &cmd->next;
				goto semicolon;
			}
			if (*p)
				err(COMPILE,
"extra characters at the end of %c command", cmd->code);
			break;
		case TEXT:			/* a c i */
			p++;
			EATSPACE();
			if (*p != '\\')
				err(COMPILE,
"command %c expects \\ followed by text", cmd->code);
			p++;
			EATSPACE();
			if (*p)
				err(COMPILE,
"extra characters after \\ at the end of %c command", cmd->code);
			cmd->t = compile_text();
			break;
		case COMMENT:			/* \0 # */
			break;
		case WFILE:			/* w */
			p++;
			EATSPACE();
			if (*p == '\0')
				err(COMPILE, "filename expected");
D 8
			cmd->t = duptoeol(p);
E 8
I 8
			cmd->t = duptoeol(p, "w command");
E 8
			if (aflag)
				cmd->u.fd = -1;
			else if ((cmd->u.fd = open(p, 
			    O_WRONLY|O_APPEND|O_CREAT|O_TRUNC,
			    DEFFILEMODE)) == -1)
				err(FATAL, "%s: %s\n", p, strerror(errno));
			break;
		case RFILE:			/* r */
			p++;
			EATSPACE();
			if (*p == '\0')
				err(COMPILE, "filename expected");
			else
D 8
				cmd->t = duptoeol(p);
E 8
I 8
				cmd->t = duptoeol(p, "read command");
E 8
			break;
		case BRANCH:			/* b t */
			p++;
			EATSPACE();
			if (*p == '\0')
				cmd->t = NULL;
			else
D 8
				cmd->t = duptoeol(p);
E 8
I 8
				cmd->t = duptoeol(p, "branch");
E 8
			break;
		case LABEL:			/* : */
			p++;
			EATSPACE();
D 8
			cmd->t = duptoeol(p);
E 8
I 8
			cmd->t = duptoeol(p, "label");
E 8
			if (strlen(p) == 0)
				err(COMPILE, "empty label");
I 9
			enterlabel(cmd);
E 9
			break;
		case SUBST:			/* s */
			p++;
			if (*p == '\0' || *p == '\\')
				err(COMPILE,
"substitute pattern can not be delimited by newline or backslash");
			cmd->u.s = xmalloc(sizeof(struct s_subst));
D 5
			p = compile_re(p, &cmd->u.s->re, 0);
E 5
I 5
			p = compile_re(p, &cmd->u.s->re);
E 5
			if (p == NULL)
D 2
				err(COMPILE, "newline in substitution pattern");
E 2
I 2
				err(COMPILE, "unterminated substitute pattern");
E 2
D 3
			cmd->u.s->pmatch = xmalloc((cmd->u.s->re.re_nsub + 1) *
			    sizeof(regmatch_t));
			p--;
			p = compile_subst(p,
			    &cmd->u.s->new, cmd->u.s->re.re_nsub);
			if (p == NULL)
				err(COMPILE,
"unterminated substitute replace in regular expression");
E 3
I 3
D 5
			if (cmd->u.s->re != NULL &&
			    nsub_max < cmd->u.s->re->re_nsub)
				nsub_max = cmd->u.s->re->re_nsub;
E 5
			--p;
			p = compile_subst(p, cmd->u.s);
E 3
			p = compile_flags(p, cmd->u.s);
			EATSPACE();
			if (*p == ';') {
				p++;
				link = &cmd->next;
				goto semicolon;
			}
			break;
		case TR:			/* y */
			p++;
			p = compile_tr(p, (char **)&cmd->u.y);
			EATSPACE();
			if (*p == ';') {
				p++;
				link = &cmd->next;
				goto semicolon;
			}
			if (*p)
				err(COMPILE,
"extra text at the end of a transform command");
			break;
		}
	}
}

/*
 * Get a delimited string.  P points to the delimeter of the string; d points
 * to a buffer area.  Newline and delimiter escapes are processed; other
 * escapes are ignored.
 *
 * Returns a pointer to the first character after the final delimiter or NULL
 * in the case of a non-terminated string.  The character array d is filled
 * with the processed string.
 */
static char *
compile_delimited(p, d)
	char *p, *d;
{
	char c;

	c = *p++;
	if (c == '\0')
		return (NULL);
	else if (c == '\\')
		err(COMPILE, "\\ can not be used as a string delimiter");
	else if (c == '\n')
		err(COMPILE, "newline can not be used as a string delimiter");
	while (*p) {
		if (*p == '\\' && p[1] == c)
D 3
				p++;
E 3
I 3
			p++;
E 3
		else if (*p == '\\' && p[1] == 'n') {
D 3
				*d++ = '\n';
				p += 2;
				continue;
E 3
I 3
			*d++ = '\n';
			p += 2;
			continue;
E 3
D 7
		} else if (*p == c) {
E 7
I 7
		} else if (*p == '\\' && p[1] == '\\')
			*d++ = *p++;
		else if (*p == c) {
E 7
			*d = '\0';
			return (p + 1);
		}
		*d++ = *p++;
	}
	return (NULL);
}

/*
D 3
 * Get a regular expression.  P points to the delimeter of the regular
 * expression; d points a regexp pointer.  Newline and delimiter escapes
 * are processed; other escapes are ignored.
E 3
I 3
 * Get a regular expression.  P points to the delimiter of the regular
 * expression; repp points to the address of a regexp pointer.  Newline
 * and delimiter escapes are processed; other escapes are ignored.
E 3
 * Returns a pointer to the first character after the final delimiter
D 3
 * or NULL in the case of a non terminated regular expression.
 * The regexp pointer is set to the compiled regular expression.
E 3
I 3
 * or NULL in the case of a non terminated regular expression.  The regexp
 * pointer is set to the compiled regular expression.
E 3
 * Cflags are passed to regcomp.
 */
static char *
D 3
compile_re(p, rep, cflags)
E 3
I 3
D 5
compile_re(p, repp, cflags)
E 5
I 5
compile_re(p, repp)
E 5
E 3
	char *p;
D 3
	regex_t *rep;
E 3
I 3
	regex_t **repp;
E 3
D 5
	int cflags;
E 5
{
	int eval;
	char re[_POSIX2_LINE_MAX + 1];

	p = compile_delimited(p, re);
D 3
	if (p && (eval = regcomp(rep, re, cflags)) != 0)
		err(COMPILE, "RE error: %s", strregerror(eval, rep));
E 3
I 3
	if (p && strlen(re) == 0) {
		*repp = NULL;
		return (p);
	}
	*repp = xmalloc(sizeof(regex_t));
D 5
	if (p && (eval = regcomp(*repp, re, cflags)) != 0)
E 5
I 5
	if (p && (eval = regcomp(*repp, re, 0)) != 0)
E 5
		err(COMPILE, "RE error: %s", strregerror(eval, *repp));
I 5
	if (maxnsub < (*repp)->re_nsub)
		maxnsub = (*repp)->re_nsub;
E 5
E 3
	return (p);
}

/*
 * Compile the substitution string of a regular expression and set res to
 * point to a saved copy of it.  Nsub is the number of parenthesized regular
 * expressions.
 */
static char *
D 3
compile_subst(p, res, nsub)
	char *p, **res;
	size_t nsub;
E 3
I 3
compile_subst(p, s)
	char *p;
	struct s_subst *s;
E 3
{
	static char lbuf[_POSIX2_LINE_MAX + 1];
D 3
	int asize, size;
	char c, *text, *op, *s;
E 3
I 3
	int asize, ref, size;
	char c, *text, *op, *sp;
E 3

	c = *p++;			/* Terminator character */
	if (c == '\0')
		return (NULL);

I 3
	s->maxbref = 0;
	s->linenum = linenum;
E 3
	asize = 2 * _POSIX2_LINE_MAX + 1;
	text = xmalloc(asize);
	size = 0;
	do {
D 3
		op = s = text + size;
E 3
I 3
		op = sp = text + size;
E 3
		for (; *p; p++) {
			if (*p == '\\') {
				p++;
				if (strchr("123456789", *p) != NULL) {
D 3
					*s++ = '\\';
					if (*p - '1' > nsub)
E 3
I 3
					*sp++ = '\\';
					ref = *p - '0';
D 5
					if (s->maxbref < ref)
						s->maxbref = ref;
E 5
					if (s->re != NULL &&
					    ref > s->re->re_nsub)
E 3
						err(COMPILE,
D 3
"\\%c not defined in regular expression (use \\1-\\%d)", *p, nsub + 1);
E 3
I 3
"\\%c not defined in the RE", *p);
I 5
					if (s->maxbref < ref)
						s->maxbref = ref;
E 5
E 3
D 7
				} else if (*p == '&')
E 7
I 7
				} else if (*p == '&' || *p == '\\')
E 7
D 3
					*s++ = '\\';
E 3
I 3
					*sp++ = '\\';
E 3
			} else if (*p == c) {
				p++;
D 3
				*s++ = '\0';
				size += s - op;
				*res = xrealloc(text, size);
E 3
I 3
				*sp++ = '\0';
				size += sp - op;
				s->new = xrealloc(text, size);
E 3
				return (p);
			} else if (*p == '\n') {
				err(COMPILE,
"unescaped newline inside substitute pattern");
D 3
				return (NULL);
E 3
I 3
				/* NOTREACHED */
E 3
			}
D 3
			*s++ = *p;
E 3
I 3
			*sp++ = *p;
E 3
		}
D 3
		size += s - op;
E 3
I 3
		size += sp - op;
E 3
		if (asize - size < _POSIX2_LINE_MAX + 1) {
			asize *= 2;
			text = xmalloc(asize);
		}
	} while (cu_fgets(p = lbuf, sizeof(lbuf)));
D 2
	err(COMPILE, "EOF in substitute pattern");
E 2
I 2
D 3
	err(COMPILE, "unterminated substitute pattern");
E 2
	return (NULL);
E 3
I 3
	err(COMPILE, "unterminated substitute in regular expression");
	/* NOTREACHED */
E 3
}

/*
 * Compile the flags of the s command
 */
static char *
compile_flags(p, s)
	char *p;
	struct s_subst *s;
{
	int gn;			/* True if we have seen g or n */
	char wfile[_POSIX2_LINE_MAX + 1], *q;

	s->n = 1;				/* Default */
	s->p = 0;
	s->wfile = NULL;
	s->wfd = -1;
	for (gn = 0;;) {
		EATSPACE();			/* EXTENSION */
		switch (*p) {
		case 'g':
			if (gn)
D 2
				err(WARNING,
				    "both g and number in substitute flags");
E 2
I 2
				err(COMPILE,
"more than one number or 'g' in substitute flags");
E 2
			gn = 1;
			s->n = 0;
			break;
		case '\0':
		case '\n':
		case ';':
			return (p);
		case 'p':
			s->p = 1;
			break;
		case '1': case '2': case '3':
		case '4': case '5': case '6':
		case '7': case '8': case '9':
			if (gn)
D 2
				err(WARNING,
				    "both g and number in substitute flags");
E 2
I 2
				err(COMPILE,
"more than one number or 'g' in substitute flags");
E 2
			gn = 1;
			/* XXX Check for overflow */
			s->n = (int)strtol(p, &p, 10);
			break;
		case 'w':
			p++;
#ifdef HISTORIC_PRACTICE
			if (*p != ' ') {
				err(WARNING, "space missing before w wfile");
				return (p);
			}
#endif
			EATSPACE();
			q = wfile;
			while (*p) {
				if (*p == '\n')
					break;
				*q++ = *p++;
			}
			*q = '\0';
			if (q == wfile)
D 2
				err(COMPILE, "empty wfile specified");
E 2
I 2
				err(COMPILE, "no wfile specified");
E 2
			s->wfile = strdup(wfile);
			if (!aflag && (s->wfd = open(wfile,
			    O_WRONLY|O_APPEND|O_CREAT|O_TRUNC,
			    DEFFILEMODE)) == -1)
				err(FATAL, "%s: %s\n", wfile, strerror(errno));
			return (p);
		default:
			err(COMPILE,
D 2
			    "bad flag in substitute command: '%c'", p[-1]);
E 2
I 2
			    "bad flag in substitute command: '%c'", *p);
E 2
			break;
		}
		p++;
	}
}

/*
 * Compile a translation set of strings into a lookup table.
 */
static char *
compile_tr(p, transtab)
	char *p;
	char **transtab;
{
	int i;
	char *lt, *op, *np;
	char old[_POSIX2_LINE_MAX + 1];
	char new[_POSIX2_LINE_MAX + 1];

	if (*p == '\0' || *p == '\\')
		err(COMPILE,
"transform pattern can not be delimited by newline or backslash");
	p = compile_delimited(p, old);
	if (p == NULL) {
		err(COMPILE, "unterminated transform source string");
		return (NULL);
	}
	p = compile_delimited(--p, new);
	if (p == NULL) {
		err(COMPILE, "unterminated transform target string");
		return (NULL);
	}
	EATSPACE();
	if (strlen(new) != strlen(old)) {
		err(COMPILE, "transform strings are not the same length");
		return (NULL);
	}
	/* We assume characters are 8 bits */
	lt = xmalloc(UCHAR_MAX);
	for (i = 0; i <= UCHAR_MAX; i++)
		lt[i] = (char)i;
	for (op = old, np = new; *op; op++, np++)
		lt[(u_char)*op] = *np;
	*transtab = lt;
	return (p);
}

/*
 * Compile the text following an a or i command.
 */
static char *
compile_text()
{
	int asize, size;
	char *text, *p, *op, *s;
	char lbuf[_POSIX2_LINE_MAX + 1];

	asize = 2 * _POSIX2_LINE_MAX + 1;
	text = xmalloc(asize);
	size = 0;
	while (cu_fgets(lbuf, sizeof(lbuf))) {
		op = s = text + size;
		p = lbuf;
		EATSPACE();
		for (; *p; p++) {
			if (*p == '\\')
				p++;
			*s++ = *p;
		}
		size += s - op;
		if (p[-2] != '\\') {
			*s = '\0';
			break;
		}
		if (asize - size < _POSIX2_LINE_MAX + 1) {
			asize *= 2;
			text = xmalloc(asize);
		}
	}
	return (xrealloc(text, size + 1));
}

/*
 * Get an address and return a pointer to the first character after
 * it.  Fill the structure pointed to according to the address.
 */
static char *
compile_addr(p, a)
	char *p;
	struct s_addr *a;
{
D 3
	regex_t *re;
E 3
	char *end;

	switch (*p) {
	case '\\':				/* Context address */
D 3
		re = xmalloc(sizeof(regex_t));
		a->u.r = re;
		p = compile_re(p + 1, re, REG_NOSUB);
		if (p == NULL)
			err(COMPILE, "unterminated regular expression");
		a->type = AT_RE;
		return (p);
E 3
I 3
		++p;
		/* FALLTHROUGH */
E 3
	case '/':				/* Context address */
D 3
		re = xmalloc(sizeof(regex_t));
		a->u.r = re;
		p = compile_re(p, a->u.r, REG_NOSUB);
E 3
I 3
D 5
		p = compile_re(p, &a->u.r, REG_NOSUB);
E 5
I 5
		p = compile_re(p, &a->u.r);
E 5
E 3
		if (p == NULL)
			err(COMPILE, "unterminated regular expression");
		a->type = AT_RE;
		return (p);
I 3

E 3
	case '$':				/* Last line */
		a->type = AT_LAST;
		return (p + 1);
						/* Line number */
	case '0': case '1': case '2': case '3': case '4': 
	case '5': case '6': case '7': case '8': case '9':
		a->type = AT_LINE;
		a->u.l = strtol(p, &end, 10);
		return (end);
	default:
		err(COMPILE, "expected context address");
		return (NULL);
	}
}

/*
D 8
 * Return a copy of all the characters up to \n or \0
E 8
I 8
 * duptoeol --
 *	Return a copy of all the characters up to \n or \0.
E 8
 */
static char *
D 8
duptoeol(s)
E 8
I 8
duptoeol(s, ctype)
E 8
	register char *s;
I 8
	char *ctype;
E 8
{
	size_t len;
I 8
	int ws;
E 8
	char *start;

D 8
	for (start = s; *s != '\0' && *s != '\n'; ++s);
E 8
I 8
	ws = 0;
	for (start = s; *s != '\0' && *s != '\n'; ++s)
		ws = isspace(*s);
E 8
	*s = '\0';
I 8
	if (ws)
		err(WARNING, "whitespace after %s", ctype);
E 8
	len = s - start + 1;
	return (memmove(xmalloc(len), start, len));
}

/*
D 8
 * Find the label contained in the command l in the command linked list cp.
 * L is excluded from the search.  Return NULL if not found.
 */
static struct s_command *
findlabel(l, cp)
	struct s_command *l, *cp;
{
	struct s_command *r;

	for (; cp; cp = cp->next)
		if (cp->code == ':' && cp != l && strcmp(l->t, cp->t) == 0)
			return (cp);
		else if (cp->code == '{' && (r = findlabel(l, cp->u.c)))
			return (r);
	return (NULL);
}

/*
 * Convert goto label names to addresses.
 * Detect duplicate labels.
 * Set appendnum to the number of a and r commands in the script.
 * Free the memory used by labels in b and t commands (but not by :)
 * Root is a pointer to the script linked list; cp points to the
 * search start.
E 8
I 8
D 9
 * Convert goto label names to addresses.  Detect unused and duplicate labels.
 * Set appendnum to the number of a and r commands in the script.  Free the
 * memory used by labels in b and t commands (but not by :).  Root is a pointer
 * to the script linked list; cp points to the search start.
E 9
I 9
 * Convert goto label names to addresses, and count a and r commands, in
 * the given subset of the script.  Free the memory used by labels in b
 * and t commands (but not by :).
E 9
 *
E 8
 * TODO: Remove } nodes
 */
static void
D 6
fixuplabel(root, cp)
	struct s_command *root, *cp;
E 6
I 6
D 9
fixuplabel(root, cp, end)
	struct s_command *root, *cp, *end;
E 9
I 9
fixuplabel(cp, end)
	struct s_command *cp, *end;
E 9
E 6
{
D 8
	struct s_command *cp2;
E 8

D 6
	for (; cp; cp = cp->next)
E 6
I 6
	for (; cp != end; cp = cp->next)
E 6
		switch (cp->code) {
I 3
D 9
		case ':':
			if (findlabel(cp, root))
				err(COMPILE2, "duplicate label %s", cp->t);
			break;
E 9
E 3
		case 'a':
		case 'r':
			appendnum++;
			break;
		case 'b':
		case 't':
I 9
			/* Resolve branch target. */
E 9
			if (cp->t == NULL) {
				cp->u.c = NULL;
				break;
			}
D 8
			if ((cp2 = findlabel(cp, root)) == NULL)
E 8
I 8
D 9
			if ((cp->u.c = findlabel(cp, root)) == NULL)
E 9
I 9
			if ((cp->u.c = findlabel(cp->t)) == NULL)
E 9
E 8
D 2
				err(COMPILE2, "unspecified label %s", cp->t);
E 2
I 2
				err(COMPILE2, "undefined label '%s'", cp->t);
I 8
D 9
			cp->u.c->lused = 1;
E 9
E 8
E 2
			free(cp->t);
D 8
			cp->u.c = cp2;
E 8
D 5
			break;
I 3
		case 's':
			if (cp->u.s->re == NULL)
				cp->u.s->pmatch = xmalloc((nsub_max + 1) *
				    sizeof(regmatch_t));
			else
				cp->u.s->pmatch =
				    xmalloc((cp->u.s->re->re_nsub + 1) *
				    sizeof(regmatch_t));
E 5
			break;
E 3
		case '{':
D 6
			fixuplabel(root, cp->u.c);
E 6
I 6
D 9
			fixuplabel(root, cp->u.c, cp->next);
E 9
I 9
			/* Do interior commands. */
			fixuplabel(cp->u.c, cp->next);
E 9
E 6
D 3
			break;
		case ':':
			if (findlabel(cp, root))
				err(COMPILE2, "duplicate label %s", cp->t);
E 3
			break;
		}
I 8
D 9
	uselabel(root);
E 9
}

/*
I 9
 * Associate the given command label for later lookup.
 */
static void
enterlabel(cp)
	struct s_command *cp;
{
	register struct labhash **lhp, *lh;
	register u_char *p;
	register u_int h, c;

	for (h = 0, p = (u_char *)cp->t; (c = *p) != 0; p++)
		h = (h << 5) + h + c;
	lhp = &labels[h & LHMASK];
	for (lh = *lhp; lh != NULL; lh = lh->lh_next)
		if (lh->lh_hash == h && strcmp(cp->t, lh->lh_cmd->t) == 0)
			err(COMPILE2, "duplicate label '%s'", cp->t);
	lh = xmalloc(sizeof *lh);
	lh->lh_next = *lhp;
	lh->lh_hash = h;
	lh->lh_cmd = cp;
	lh->lh_ref = 0;
	*lhp = lh;
}

/*
E 9
 * Find the label contained in the command l in the command linked
 * list cp.  L is excluded from the search.  Return NULL if not found.
 */
static struct s_command *
D 9
findlabel(l, cp)
	struct s_command *l, *cp;
E 9
I 9
findlabel(name)
	char *name;
E 9
{
D 9
	struct s_command *r;
E 9
I 9
	register struct labhash *lh;
	register u_char *p;
	register u_int h, c;
E 9

D 9
	for (; cp; cp = cp->next) {
		if (cp->code == ':' && cp != l && strcmp(l->t, cp->t) == 0)
			return (cp);
		if (cp->code == '{' && (r = findlabel(l, cp->u.c)))
			return (r);
E 9
I 9
	for (h = 0, p = (u_char *)name; (c = *p) != 0; p++)
		h = (h << 5) + h + c;
	for (lh = labels[h & LHMASK]; lh != NULL; lh = lh->lh_next) {
		if (lh->lh_hash == h && strcmp(name, lh->lh_cmd->t) == 0) {
			lh->lh_ref = 1;
			return (lh->lh_cmd);
		}
E 9
	}
	return (NULL);
}

/* 
D 9
 * Find any unused labels.  This is because we want to warn the user if they
 * accidentally put whitespace on a label name causing it be a different label
 * than they intended.
E 9
I 9
 * Warn about any unused labels.  As a side effect, release the label hash
 * table space.
E 9
 */
static void
D 9
uselabel(cp)
	struct s_command *cp;
E 9
I 9
uselabel()
E 9
{
D 9
	for (; cp; cp = cp->next) {
		if (cp->code == ':' && cp->lused == 0)
			err(WARNING, "unused label '%s'", cp->t);
		if (cp->code == '{')
			uselabel(cp->u.c);
E 9
I 9
	register struct labhash *lh, *next;
	register int i;

	for (i = 0; i < LHSZ; i++) {
		for (lh = labels[i]; lh != NULL; lh = next) {
			next = lh->lh_next;
			if (!lh->lh_ref)
				err(WARNING, "unused label '%s'",
				    lh->lh_cmd->t);
			free(lh);
		}
E 9
	}
E 8
}
E 1
