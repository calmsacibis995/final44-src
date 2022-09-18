h44502
s 00002/00002/00314
d D 8.2 95/04/28 14:11:17 bostic 11 10
c We lost when dealing with mappings with unequal ranges, for example
c 'tr A-Z N-ZA-M', because we didn't skip over the terminating character
c of the range when processing it.  This works when the ranges line up
c since they map terminating character to terminating character correctly,
c but fails when one range maps into two, or with other odd combinations.
c From: Chris Torek <torek@BSDI.COM>
e
s 00002/00002/00314
d D 8.1 93/06/06 16:38:09 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00314
d D 5.9 93/03/04 16:46:36 bostic 9 8
c revision 5.8 broke tr, this fix handles blah, blah, blah
c test case #3: echo 'foo' | obj/tr 'fo' '\aX'
e
s 00006/00004/00308
d D 5.8 93/03/02 16:39:54 bostic 8 7
c revision 5.7 broke tr, this fix handles both problems (I think)
c test case #1: echo 'a b c d   e f g' | obj/tr -s '\011\040' '\012'
c test case #2: echo 'a b c' | obj/tr '\40a' YZ
e
s 00002/00002/00310
d D 5.7 93/01/31 09:42:25 bostic 7 6
c It looks to me like the net-2 tr loses bytes in argument strings
c following octal escapes which take up fewer than the full 3 characters.
c from Donn Seeley at BSDI
e
s 00009/00011/00303
d D 5.6 92/01/16 18:11:00 bostic 6 5
c fix '[a]' usage: test is /tr '[a-z]' '[A-Z]' < /etc/motd
c use strstr instead of strpbrk
e
s 00002/00001/00312
d D 5.5 91/11/21 12:25:40 bostic 5 4
c have to check for EOS, though, or will overrun the string
e
s 00001/00001/00312
d D 5.4 91/11/21 12:15:26 bostic 4 3
c have to increment on octal string; bug case was fo tr '\003' '\002',
c occurrences of '3' in the string would get changed to '2'
e
s 00020/00026/00293
d D 5.3 91/10/27 10:38:21 bostic 3 2
c various bug fixes, don't restrict class usage at all on the grounds
c that you can't get it right.  Hal Jesperson agrees that this is correct,
c it's not clear from the POSIX draft.
e
s 00003/00003/00316
d D 5.2 91/10/24 19:01:55 bostic 2 1
c backslash changes messed up simple octal charactes
e
s 00319/00000/00000
d D 5.1 91/10/24 17:48:50 bostic 1 0
c POSIX 1003.2/D11.2 version
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/cdefs.h>
#include <sys/types.h>
I 8

E 8
#include <errno.h>
D 8
#include <stdio.h>
E 8
#include <stddef.h>
I 8
#include <stdio.h>
E 8
#include <stdlib.h>
#include <string.h>
I 8

E 8
#include "extern.h"

static int	backslash __P((STR *));
static int	bracket __P((STR *));
static int	c_class __P((const void *, const void *));
static void	genclass __P((STR *));
static void	genequiv __P((STR *));
static int	genrange __P((STR *));
static void	genseq __P((STR *));

int
next(s)
	register STR *s;
{
	register int ch;

	switch (s->state) {
	case EOS:
		return (0);
	case INFINITE:
		return (1);
	case NORMAL:
D 2
		switch (ch = *s->str++) {
E 2
I 2
		switch (ch = *s->str) {
E 2
		case '\0':
D 2
			--s->str;
E 2
			s->state = EOS;
			return (0);
		case '\\':
			s->lastch = backslash(s);
			break;
		case '[':
			if (bracket(s))
				return (next(s));
			/* FALLTHROUGH */
		default:
I 2
			++s->str;
E 2
			s->lastch = ch;
			break;
		}

		/* We can start a range at any time. */
		if (s->str[0] == '-' && genrange(s))
			return (next(s));
		return (1);
	case RANGE:
		if (s->cnt-- == 0) {
			s->state = NORMAL;
			return (next(s));
		}
		++s->lastch;
		return (1);
	case SEQUENCE:
		if (s->cnt-- == 0) {
			s->state = NORMAL;
			return (next(s));
		}
		return (1);
	case SET:
D 3
	case ULSET:
E 3
		if ((s->lastch = s->set[s->cnt++]) == OOBCH) {
			s->state = NORMAL;
			return (next(s));
		}
		return (1);
	}
	/* NOTREACHED */
}

static int
bracket(s)
	register STR *s;
{
	register char *p;

D 2
	switch (*s->str) {
E 2
I 2
D 6
	switch (*++s->str) {
E 6
I 6
	switch (s->str[1]) {
E 6
E 2
	case ':':				/* "[:class:]" */
D 6
		if ((p = strpbrk(s->str + 1, ":]")) == NULL)
E 6
I 6
		if ((p = strstr(s->str + 2, ":]")) == NULL)
E 6
			return (0);
D 6
		if (p[0] != ':' || p[1] != ']')
			return (0);
E 6
		*p = '\0';
D 6
		++s->str;
E 6
I 6
		s->str += 2;
E 6
		genclass(s);
		s->str = p + 2;
		return (1);
	case '=':				/* "[=equiv=]" */
D 6
		if ((p = strpbrk(s->str + 1, "=]")) == NULL)
E 6
I 6
		if ((p = strstr(s->str + 2, "=]")) == NULL)
E 6
			return (0);
D 6
		if (p[0] != '=' || p[1] != ']')
			return (0);
E 6
I 6
		s->str += 2;
E 6
		genequiv(s);
		return (1);
D 6
	default:				/* "[\###*]" or "[#*]" */
		if ((p = strpbrk(s->str + 1, "*]")) == NULL)
E 6
I 6
	default:				/* "[\###*n]" or "[#*n]" */
		if ((p = strpbrk(s->str + 2, "*]")) == NULL)
E 6
			return (0);
		if (p[0] != '*' || index(p, ']') == NULL)
			return (0);
I 6
		s->str += 1;
E 6
		genseq(s);
		return (1);
	}
	/* NOTREACHED */
}

int isalnum __P((int)),
    isalpha __P((int)),
    isblank __P((int)),
    isspace __P((int)),
    iscntrl __P((int)),
    isdigit __P((int)),
    isgraph __P((int)),
    islower __P((int)),
    isprint __P((int)),
    ispunct __P((int)),
    isupper __P((int)),
    isxdigit __P((int));

typedef struct {
	char *name;
	int (*func) __P((int));
D 3
	u_int type;
E 3
	int *set;
} CLASS;

static CLASS classes[] = {
D 3
	{ "alnum",  isalnum,  T_CLASS, },
	{ "alpha",  isalpha,  T_CLASS, },
	{ "blank",  isblank,  T_CLASS, },
	{ "cntrl",  iscntrl,  T_CLASS, },
	{ "digit",  isdigit,  T_CLASS, },
	{ "graph",  isgraph,  T_CLASS, },
	{ "lower",  islower,  T_UL, },
	{ "print",  isupper,  T_CLASS, },
	{ "punct",  ispunct,  T_CLASS, },
	{ "space",  isspace,  T_CLASS, },
	{ "upper",  isupper,  T_UL, },
	{ "xdigit", isxdigit, T_CLASS, },
E 3
I 3
	{ "alnum",  isalnum,  },
	{ "alpha",  isalpha,  },
	{ "blank",  isblank,  },
	{ "cntrl",  iscntrl,  },
	{ "digit",  isdigit,  },
	{ "graph",  isgraph,  },
	{ "lower",  islower,  },
	{ "print",  isupper,  },
	{ "punct",  ispunct,  },
	{ "space",  isspace,  },
	{ "upper",  isupper,  },
	{ "xdigit", isxdigit, },
E 3
};

static void
genclass(s)
	STR *s;
{
	register int cnt, (*func) __P((int));
	CLASS *cp, tmp;
	int *p;

	tmp.name = s->str;
	if ((cp = (CLASS *)bsearch(&tmp, classes, sizeof(classes) /
	    sizeof(CLASS), sizeof(CLASS), c_class)) == NULL)
		err("unknown class %s", s->str);
D 3
	if (!(cp->type | s->type))
		err("class %s illegally used");
E 3

	if ((cp->set = p = malloc((NCHARS + 1) * sizeof(int))) == NULL)
		err("%s", strerror(errno));
D 3
	bzero(p, NCHARS);
E 3
I 3
	bzero(p, (NCHARS + 1) * sizeof(int));
E 3
	for (cnt = 0, func = cp->func; cnt < NCHARS; ++cnt)
		if ((func)(cnt))
			*p++ = cnt;
	*p = OOBCH;

	s->cnt = 0;
D 3
	s->state = cp->type & T_UL ? ULSET : SET;
E 3
I 3
	s->state = SET;
E 3
	s->set = cp->set;
}

static int
c_class(a, b)
	const void *a, *b;
{
	return (strcmp(((CLASS *)a)->name, ((CLASS *)b)->name));
}

/*
 * English doesn't have any equivalence classes, so for now
 * we just syntax check and grab the character.
 */
static void
genequiv(s)
	STR *s;
{
D 3
	static int val[2] = { 0, OOBCH };

E 3
D 6
	if (*++s->str == '\\') {
E 6
I 6
	if (*s->str == '\\') {
E 6
D 3
		val[0] = backslash(s);
E 3
I 3
		s->equiv[0] = backslash(s);
E 3
		if (*s->str != '=')
			err("misplaced equivalence equals sign");
	} else {
D 3
		val[0] = s->str[0];
E 3
I 3
		s->equiv[0] = s->str[0];
E 3
		if (s->str[1] != '=')
			err("misplaced equivalence equals sign");
	}
	s->str += 2;
	s->cnt = 0;
	s->state = SET;
D 3
	s->set = val;
E 3
I 3
	s->set = s->equiv;
E 3
}

static int
genrange(s)
	STR *s;
{
	int stopval;
	char *savestart;

	savestart = s->str;
D 11
	stopval = *++s->str == '\\' ? backslash(s) : *s->str;
	if (stopval < s->lastch) {
E 11
I 11
	stopval = *++s->str == '\\' ? backslash(s) : *s->str++;
	if (stopval < (u_char)s->lastch) {
E 11
		s->str = savestart;
		return (0);
	}
	s->cnt = stopval - s->lastch + 1;
	s->state = RANGE;
	--s->lastch;
	return (1);
}

static void
genseq(s)
	STR *s;
{
	char *ep;

D 3
	if (!(s->type & T_SEQ))
		err("sequences only valid in string1");
E 3
I 3
	if (s->which == STRING1)
		err("sequences only valid in string2");
E 3

	if (*s->str == '\\')
		s->lastch = backslash(s);
	else
		s->lastch = *s->str++;
	if (*s->str != '*')
		err("misplaced sequence asterisk");

	switch (*++s->str) {
	case '\\':
		s->cnt = backslash(s);
		break;
	case ']':
		s->cnt = 0;
		++s->str;
		break;
	default:
		if (isdigit(*s->str)) {
			s->cnt = strtol(s->str, &ep, 0);
			if (*ep == ']') {
				s->str = ep + 1;
				break;
			}
		}
		err("illegal sequence count");
		/* NOTREACHED */
	}

	s->state = s->cnt ? SEQUENCE : INFINITE;
}

D 3
/* Use the #defines here, DON'T use them above. */
E 3
I 3
/* Use the #defines isXXX() here, DON'T use them above. */
E 3
#include <ctype.h>

/*
 * Translate \??? into a character.  Up to 3 octal digits, if no digits either
 * an escape code or a literal character.
 */
static int
backslash(s)
	register STR *s;
{
	register int ch, cnt, val;

	for (cnt = val = 0;;) {
		ch = *++s->str;
		if (!isascii(ch) || !isdigit(ch))
			break;
		val = val * 8 + ch - '0';
D 8
		if (++cnt == 3)
E 8
I 8
		if (++cnt == 3) {
			++s->str;
E 8
			break;
I 8
		}
E 8
	}
I 4
D 5
	++s->str;
E 5
I 5
D 7
	if (ch != '\0')
		++s->str;
E 7
E 5
E 4
	if (cnt)
		return (val);
I 9
	if (ch != '\0')
		++s->str;
E 9
I 7
D 8
	if (ch != '\0')
		++s->str;
E 8
E 7
D 4
	++s->str;
E 4
	switch (ch) {
		case 'a':			/* escape characters */
			return ('\7');
		case 'b':
			return ('\b');
		case 'f':
			return ('\f');
		case 'n':
			return ('\n');
		case 'r':
			return ('\r');
		case 't':
			return ('\t');
		case 'v':
			return ('\13');
		case '\0':			/*  \" -> \ */
			s->state = EOS;
			return ('\\');
		default:			/* \x" -> x */
			return (ch);
	}
}
E 1
