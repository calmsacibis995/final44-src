h46002
s 00001/00001/00154
d D 8.3 94/03/20 14:35:09 bostic 7 6
c delete UofT; requested change from Henry Spencer <henry@zoo.toronto.edu>
e
s 00005/00006/00150
d D 8.2 94/03/16 12:43:02 bostic 6 5
c alpha3.3
e
s 00002/00002/00154
d D 8.1 93/06/04 12:58:18 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00018/00007/00138
d D 5.4 93/05/21 16:06:56 bostic 4 3
c Henry Spencer's Alpha 3.0 regex release
e
s 00000/00008/00145
d D 5.3 92/09/30 14:30:48 bostic 3 2
c convert to 4BSD style prototypes, includes
e
s 00053/00036/00100
d D 5.2 92/09/30 12:58:07 bostic 2 1
c alpha2.1 release from Henry Spencer
e
s 00136/00000/00000
d D 5.1 92/08/06 11:58:11 bostic 1 0
c date and time created 92/08/06 11:58:11 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1992 Henry Spencer.
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
E 6
I 6
 * Copyright (c) 1992, 1993, 1994 Henry Spencer.
 * Copyright (c) 1992, 1993, 1994
E 6
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
D 7
 * Henry Spencer of the University of Toronto.
E 7
I 7
 * Henry Spencer.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

I 2
/*
 * the outer shell of regexec()
 *
 * This file includes engine.c *twice*, after muchos fiddling with the
 * macros that code uses.  This lets the same code operate on two different
 * representations for state sets.
 */
E 2
#include <sys/types.h>
D 2

E 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
D 2
#include <assert.h>
E 2
#include <limits.h>
I 2
#include <ctype.h>
E 2
#include <regex.h>

#include "utils.h"
#include "regex2.h"

I 4
static int nope = 0;		/* for use in asserts; shuts lint up */

E 4
D 2
/*
 - regexec - interface for matching
 */
int				/* 0 success, REG_NOMATCH failure */
regexec(preg, string, nmatch, pmatch, eflags)
const regex_t *preg;
const char *string;
size_t nmatch;
regmatch_t pmatch[];
int eflags;
{
	register struct re_guts *g = preg->re_g;
	STATIC int smatcher();
	STATIC int lmatcher();
#ifndef NDEBUG
#	define	GOODFLAGS(f)	(f)
#else
#	define	GOODFLAGS(f)	((f)&(REG_NOTBOL|REG_NOTEOL|REG_STARTEND))
#endif

	if (preg->re_magic != MAGIC1 || g->magic != MAGIC2)
		return(REG_BADPAT);
	assert(!(g->iflags&BAD));
	if (g->iflags&BAD)		/* backstop for NDEBUG case */
		return(REG_BADPAT);
	eflags = GOODFLAGS(eflags);	/* xxx should we complain? */

	if (g->nstates <= 32 && !(eflags&REG_LARGE))
		return(smatcher(g, string, nmatch, pmatch, eflags));
	else
		return(lmatcher(g, string, nmatch, pmatch, eflags));
}

E 2
/* macros for manipulating states, small version */
#define	states	long
I 2
#define	states1	states		/* for later use in regexec() decision */
E 2
#define	CLEAR(v)	((v) = 0)
#define	SET0(v, n)	((v) &= ~(1 << (n)))
#define	SET1(v, n)	((v) |= 1 << (n))
#define	ISSET(v, n)	((v) & (1 << (n)))
#define	ASSIGN(d, s)	((d) = (s))
#define	EQ(a, b)	((a) == (b))
#define	STATEVARS	int dummy	/* dummy version */
#define	STATESETUP(m, n)	/* nothing */
#define	STATETEARDOWN(m)	/* nothing */
D 2
#define	SETUP(v)	/* nothing */
E 2
I 2
#define	SETUP(v)	((v) = 0)
E 2
#define	onestate	int
D 4
#define	INIT(o, n)	((o) = 1 << (n))
E 4
I 4
#define	INIT(o, n)	((o) = (unsigned)1 << (n))
E 4
#define	INC(o)	((o) <<= 1)
#define	ISSTATEIN(v, o)	((v) & (o))
/* some abbreviations; note that some of these know variable names! */
/* do "if I'm here, I can also be there" etc without branches */
D 4
#define	FWD(dst, src, n)	((dst) |= ((src)&(here)) << (n))
#define	BACK(dst, src, n)	((dst) |= ((src)&(here)) >> (n))
#define	ISSETBACK(v, n)	((v) & (here >> (n)))
E 4
I 4
#define	FWD(dst, src, n)	((dst) |= ((unsigned)(src)&(here)) << (n))
#define	BACK(dst, src, n)	((dst) |= ((unsigned)(src)&(here)) >> (n))
#define	ISSETBACK(v, n)	((v) & ((unsigned)here >> (n)))
E 4
/* function names */
#define SNAMES			/* engine.c looks after details */

#include "engine.c"

/* now undo things */
#undef	states
#undef	CLEAR
#undef	SET0
#undef	SET1
#undef	ISSET
#undef	ASSIGN
#undef	EQ
#undef	STATEVARS
#undef	STATESETUP
#undef	STATETEARDOWN
#undef	SETUP
#undef	onestate
#undef	INIT
#undef	INC
#undef	ISSTATEIN
#undef	FWD
#undef	BACK
#undef	ISSETBACK
#undef	SNAMES

/* macros for manipulating states, large version */
#define	states	char *
#define	CLEAR(v)	memset(v, 0, m->g->nstates)
#define	SET0(v, n)	((v)[n] = 0)
#define	SET1(v, n)	((v)[n] = 1)
#define	ISSET(v, n)	((v)[n])
#define	ASSIGN(d, s)	memcpy(d, s, m->g->nstates)
#define	EQ(a, b)	(memcmp(a, b, m->g->nstates) == 0)
#define	STATEVARS	int vn; char *space
#define	STATESETUP(m, nv)	{ (m)->space = malloc((nv)*(m)->g->nstates); \
				if ((m)->space == NULL) return(REG_ESPACE); \
				(m)->vn = 0; }
#define	STATETEARDOWN(m)	{ free((m)->space); }
#define	SETUP(v)	((v) = &m->space[m->vn++ * m->g->nstates])
#define	onestate	int
#define	INIT(o, n)	((o) = (n))
#define	INC(o)	((o)++)
#define	ISSTATEIN(v, o)	((v)[o])
/* some abbreviations; note that some of these know variable names! */
/* do "if I'm here, I can also be there" etc without branches */
#define	FWD(dst, src, n)	((dst)[here+(n)] |= (src)[here])
#define	BACK(dst, src, n)	((dst)[here-(n)] |= (src)[here])
#define	ISSETBACK(v, n)	((v)[here - (n)])
/* function names */
#define	LNAMES			/* flag */

#include "engine.c"
I 2

/*
 - regexec - interface for matching
I 4
D 6
 = extern int regexec(const regex_t *preg, const char *string, size_t nmatch, \
 =					regmatch_t pmatch[], int eflags);
E 6
I 6
 = extern int regexec(const regex_t *, const char *, size_t, \
 =					regmatch_t [], int);
E 6
 = #define	REG_NOTBOL	00001
 = #define	REG_NOTEOL	00002
 = #define	REG_STARTEND	00004
 = #define	REG_TRACE	00400	// tracing of execution
 = #define	REG_LARGE	01000	// force large representation
 = #define	REG_BACKR	02000	// force use of backref code
E 4
D 3
 = extern int regexec(const regex_t *preg, const char *string, size_t nmatch, \
 =					regmatch_t pmatch[], int eflags);
 = #define	REG_NOTBOL	00001
 = #define	REG_NOTEOL	00002
 = #define	REG_STARTEND	00004
 = #define	REG_TRACE	00400
 = #define	REG_LARGE	01000
 = #define	REG_BACKR	02000
E 3
 *
 * We put this here so we can exploit knowledge of the state representation
 * when choosing which matcher to call.  Also, by this point the matchers
 * have been prototyped.
 */
int				/* 0 success, REG_NOMATCH failure */
regexec(preg, string, nmatch, pmatch, eflags)
const regex_t *preg;
const char *string;
size_t nmatch;
regmatch_t pmatch[];
int eflags;
{
	register struct re_guts *g = preg->re_g;
#ifdef REDEBUG
#	define	GOODFLAGS(f)	(f)
#else
#	define	GOODFLAGS(f)	((f)&(REG_NOTBOL|REG_NOTEOL|REG_STARTEND))
#endif

	if (preg->re_magic != MAGIC1 || g->magic != MAGIC2)
		return(REG_BADPAT);
	assert(!(g->iflags&BAD));
	if (g->iflags&BAD)		/* backstop for no-debug case */
		return(REG_BADPAT);
D 4
	eflags = GOODFLAGS(eflags);	/* xxx should we complain? */
E 4
I 4
D 6
	if (eflags != GOODFLAGS(eflags))
		return(REG_INVARG);
E 6
I 6
	eflags = GOODFLAGS(eflags);
E 6
E 4

	if (g->nstates <= CHAR_BIT*sizeof(states1) && !(eflags&REG_LARGE))
D 4
		return(smatcher(g, (uchar *)string, nmatch, pmatch, eflags));
E 4
I 4
		return(smatcher(g, (char *)string, nmatch, pmatch, eflags));
E 4
	else
D 4
		return(lmatcher(g, (uchar *)string, nmatch, pmatch, eflags));
E 4
I 4
		return(lmatcher(g, (char *)string, nmatch, pmatch, eflags));
E 4
}
E 2
E 1
