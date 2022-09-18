h42763
s 00002/00002/00670
d D 8.1 93/05/31 16:42:37 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00671
d D 5.13 93/05/22 19:06:44 christos 15 14
c Fixed gcc -Wall warnings
e
s 00004/00004/00668
d D 5.12 91/07/19 17:31:14 christos 14 13
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00000/00666
d D 5.11 91/06/08 17:08:56 christos 13 12
c More prototype fixes, Removed TERMIOS define
e
s 00003/00000/00663
d D 5.10 91/06/08 12:20:29 bostic 12 11
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00017/00010/00646
d D 5.9 91/06/07 20:57:35 christos 11 10
c static function prototypes
e
s 00002/00001/00654
d D 5.8 91/06/07 11:13:37 bostic 10 9
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00485/00468/00170
d D 5.7 91/06/04 13:31:50 bostic 9 8
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00631
d D 5.6 91/04/04 18:17:52 bostic 8 7
c new copyright; att/bsd/shared
e
s 00043/00039/00594
d D 5.5 91/04/01 17:37:17 bostic 7 6
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00005/00005/00628
d D 5.4 91/03/14 12:32:29 bostic 6 5
c any -> index (use the faster library routine)
e
s 00003/00001/00630
d D 5.3 86/05/13 01:04:32 lepreau 5 4
c fix so "cmd && cmd2 &" (or ||) does not hang the tty. From elsie!ado
e
s 00003/00003/00628
d D 5.2 85/06/06 13:10:12 edward 4 3
c cleaning up after bozos
e
s 00008/00002/00623
d D 5.1 85/06/04 11:06:10 dist 3 2
c Add copyright
e
s 00014/00011/00611
d D 4.2 84/12/13 14:40:42 edward 2 1
c performance
e
s 00622/00000/00000
d D 4.1 80/10/09 12:41:27 bill 1 0
c date and time created 80/10/09 12:41:27 by bill
e
u
U
t
T
I 3
D 8
/*
 * Copyright (c) 1980 Regents of the University of California.
D 4
 * All rights reserved.  The Berkeley software License Agreement
E 4
I 4
 * All rights reserved.  The Berkeley Software License Agreement
E 4
 * specifies the terms and conditions for redistribution.
E 8
I 8
/*-
D 16
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
 * %sccs.include.redist.c%
E 8
 */

E 3
I 1
D 2
static	char *sccsid = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
D 3
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
D 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 4
I 4
D 8
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
E 4
E 3
E 2

I 12
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
I 13
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 13
E 12
D 10
#include "sh.h"
E 10
I 10
#include "csh.h"
#include "extern.h"
E 10

D 9
/*
 * C shell
 */
E 9
I 9
D 11
static void asyntax();
static void asyn0();
static void asyn3();
static struct wordent *freenod();
static struct command *syn0();
static struct command *syn1();
static struct command *syn1a();
static struct command *syn1b();
static struct command *syn2();
static struct command *syn3();
E 11
I 11
static void	 asyntax __P((struct wordent *, struct wordent *));
static void	 asyn0 __P((struct wordent *, struct wordent *));
static void	 asyn3 __P((struct wordent *, struct wordent *));
static struct wordent 
		*freenod __P((struct wordent *, struct wordent *));
static struct command 
		*syn0 __P((struct wordent *, struct wordent *, int));
static struct command 
		*syn1 __P((struct wordent *, struct wordent *, int));
static struct command 
		*syn1a __P((struct wordent *, struct wordent *, int));
static struct command 
		*syn1b __P((struct wordent *, struct wordent *, int));
static struct command 
		*syn2 __P((struct wordent *, struct wordent *, int));
static struct command 
		*syn3 __P((struct wordent *, struct wordent *, int));
E 11
E 9

I 9
#define ALEFT	21		/* max of 20 alias expansions	 */
#define HLEFT	11		/* max of 10 history expansions	 */
E 9
/*
 * Perform aliasing on the word list lex
 * Do a (very rudimentary) parse to separate into commands.
 * If word 0 of a command has an alias, do it.
 * Repeat a maximum of 20 times.
 */
I 9
static int aleft;
extern int hleft;
void
E 9
alias(lex)
D 9
	register struct wordent *lex;
E 9
I 9
    register struct wordent *lex;
E 9
{
D 9
	int aleft = 21;
	jmp_buf osetexit;
E 9
I 9
    jmp_buf osetexit;
E 9

D 9
	getexit(osetexit);
D 7
	setexit();
E 7
I 7
	(void)setjmp(reslab);
E 7
	if (haderr) {
		resexit(osetexit);
D 7
		reset();
E 7
I 7
		longjmp(reslab, 0);
E 7
	}
	if (--aleft == 0)
		error("Alias loop");
	asyntax(lex->next, lex);
E 9
I 9
    aleft = ALEFT;
    hleft = HLEFT;
    getexit(osetexit);
    (void) setexit();
    if (haderr) {
E 9
	resexit(osetexit);
I 9
	reset();
    }
    if (--aleft == 0)
	stderror(ERR_ALIASLOOP);
    asyntax(lex->next, lex);
    resexit(osetexit);
E 9
}

I 9
static void
E 9
asyntax(p1, p2)
D 9
	register struct wordent *p1, *p2;
E 9
I 9
    register struct wordent *p1, *p2;
E 9
{
D 9

	while (p1 != p2)
D 6
		if (any(p1->word[0], ";&\n"))
E 6
I 6
		if (index(";&\n", p1->word[0]))
E 6
			p1 = p1->next;
		else {
			asyn0(p1, p2);
			return;
		}
E 9
I 9
    while (p1 != p2)
	if (any(";&\n", p1->word[0]))
	    p1 = p1->next;
	else {
	    asyn0(p1, p2);
	    return;
	}
E 9
}

I 9
static void
E 9
asyn0(p1, p2)
D 9
	struct wordent *p1;
	register struct wordent *p2;
E 9
I 9
    struct wordent *p1;
    register struct wordent *p2;
E 9
{
D 9
	register struct wordent *p;
	register int l = 0;
E 9
I 9
    register struct wordent *p;
    register int l = 0;
E 9

D 9
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			l++;
			continue;
E 9
I 9
	case '(':
	    l++;
	    continue;
E 9

D 9
		case ')':
			l--;
			if (l < 0)
				error("Too many )'s");
			continue;
E 9
I 9
	case ')':
	    l--;
	    if (l < 0)
		stderror(ERR_TOOMANYRP);
	    continue;
E 9

D 9
		case '>':
			if (p->next != p2 && eq(p->next->word, "&"))
				p = p->next;
			continue;
E 9
I 9
	case '>':
	    if (p->next != p2 && eq(p->next->word, STRand))
		p = p->next;
	    continue;
E 9

D 9
		case '&':
		case '|':
		case ';':
		case '\n':
			if (l != 0)
				continue;
			asyn3(p1, p);
			asyntax(p->next, p2);
			return;
		}
	if (l == 0)
		asyn3(p1, p2);
E 9
I 9
	case '&':
	case '|':
	case ';':
	case '\n':
	    if (l != 0)
		continue;
	    asyn3(p1, p);
	    asyntax(p->next, p2);
	    return;
	}
    if (l == 0)
	asyn3(p1, p2);
E 9
}

I 9
static void
E 9
asyn3(p1, p2)
D 9
	struct wordent *p1;
	register struct wordent *p2;
E 9
I 9
    struct wordent *p1;
    register struct wordent *p2;
E 9
{
D 9
	register struct varent *ap;
	struct wordent alout;
	register bool redid;
E 9
I 9
    register struct varent *ap;
    struct wordent alout;
    register bool redid;
E 9

D 9
	if (p1 == p2)
E 9
I 9
    if (p1 == p2)
	return;
    if (p1->word[0] == '(') {
	for (p2 = p2->prev; p2->word[0] != ')'; p2 = p2->prev)
	    if (p2 == p1)
E 9
		return;
D 9
	if (p1->word[0] == '(') {
		for (p2 = p2->prev; p2->word[0] != ')'; p2 = p2->prev)
			if (p2 == p1)
				return;
		if (p2 == p1->next)
			return;
		asyn0(p1->next, p2);
		return;
	}
	ap = adrof1(p1->word, &aliases);
	if (ap == 0)
		return;
	alhistp = p1->prev;
	alhistt = p2;
	alvec = ap->vec;
	redid = lex(&alout);
	alhistp = alhistt = 0;
	alvec = 0;
	if (err) {
		freelex(&alout);
		error(err);
	}
	if (p1->word[0] && eq(p1->word, alout.next->word)) {
		char *cp = alout.next->word;
E 9
I 9
	if (p2 == p1->next)
	    return;
	asyn0(p1->next, p2);
	return;
    }
    ap = adrof1(p1->word, &aliases);
    if (ap == 0)
	return;
    alhistp = p1->prev;
    alhistt = p2;
    alvec = ap->vec;
    redid = lex(&alout);
    alhistp = alhistt = 0;
    alvec = 0;
    if (seterr) {
	freelex(&alout);
	stderror(ERR_OLD);
    }
    if (p1->word[0] && eq(p1->word, alout.next->word)) {
	Char   *cp = alout.next->word;
E 9

D 9
		alout.next->word = strspl("\200", cp);
D 2
		xfree(cp);
E 2
I 2
		XFREE(cp)
E 2
	}
	p1 = freenod(p1, redid ? p2 : p1->next);
	if (alout.next != &alout) {
		p1->next->prev = alout.prev->prev;
		alout.prev->prev->next = p1->next;
		alout.next->prev = p1;
		p1->next = alout.next;
D 2
		xfree(alout.prev->word);
		xfree((char *)(alout.prev));
E 2
I 2
		XFREE(alout.prev->word)
		XFREE((char *)alout.prev)
E 2
	}
D 7
	reset();		/* throw! */
E 7
I 7
	longjmp(reslab, 0);		/* throw! */
E 9
I 9
	alout.next->word = Strspl(STRQNULL, cp);
	xfree((ptr_t) cp);
    }
    p1 = freenod(p1, redid ? p2 : p1->next);
    if (alout.next != &alout) {
	p1->next->prev = alout.prev->prev;
	alout.prev->prev->next = p1->next;
	alout.next->prev = p1;
	p1->next = alout.next;
	xfree((ptr_t) alout.prev->word);
	xfree((ptr_t) (alout.prev));
    }
    reset();			/* throw! */
E 9
E 7
}

D 9
struct wordent *
E 9
I 9
static struct wordent *
E 9
freenod(p1, p2)
D 9
	register struct wordent *p1, *p2;
E 9
I 9
    register struct wordent *p1, *p2;
E 9
{
D 9
	register struct wordent *retp = p1->prev;
E 9
I 9
    register struct wordent *retp = p1->prev;
E 9

D 9
	while (p1 != p2) {
D 2
		xfree(p1->word);
E 2
I 2
		XFREE(p1->word)
E 2
		p1 = p1->next;
D 2
		xfree((char *)(p1->prev));
E 2
I 2
		XFREE((char *)p1->prev)
E 2
	}
	retp->next = p2;
	p2->prev = retp;
	return (retp);
E 9
I 9
    while (p1 != p2) {
	xfree((ptr_t) p1->word);
	p1 = p1->next;
	xfree((ptr_t) (p1->prev));
    }
    retp->next = p2;
    p2->prev = retp;
    return (retp);
E 9
}

#define	PHERE	1
#define	PIN	2
#define	POUT	4
D 14
#define	PDIAG	8
E 14
I 14
#define	PERR	8
E 14

/*
 * syntax
 *	empty
 *	syn0
 */
struct command *
syntax(p1, p2, flags)
D 9
	register struct wordent *p1, *p2;
	int flags;
E 9
I 9
    register struct wordent *p1, *p2;
    int     flags;
E 9
{

D 9
	while (p1 != p2)
D 6
		if (any(p1->word[0], ";&\n"))
E 6
I 6
		if (index(";&\n", p1->word[0]))
E 6
			p1 = p1->next;
		else
			return (syn0(p1, p2, flags));
	return (0);
E 9
I 9
    while (p1 != p2)
	if (any(";&\n", p1->word[0]))
	    p1 = p1->next;
	else
	    return (syn0(p1, p2, flags));
    return (0);
E 9
}

/*
 * syn0
 *	syn1
 *	syn1 & syntax
 */
D 9
struct command *
E 9
I 9
static struct command *
E 9
syn0(p1, p2, flags)
D 9
	struct wordent *p1, *p2;
	int flags;
E 9
I 9
    struct wordent *p1, *p2;
    int     flags;
E 9
{
D 9
	register struct wordent *p;
	register struct command *t, *t1;
	int l;
E 9
I 9
    register struct wordent *p;
    register struct command *t, *t1;
    int     l;
E 9

D 9
	l = 0;
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    l = 0;
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			l++;
			continue;
E 9
I 9
	case '(':
	    l++;
	    continue;
E 9

D 9
		case ')':
			l--;
			if (l < 0)
				seterr("Too many )'s");
			continue;
E 9
I 9
	case ')':
	    l--;
	    if (l < 0)
		seterror(ERR_TOOMANYRP);
	    continue;
E 9

D 9
		case '|':
			if (p->word[1] == '|')
				continue;
			/* fall into ... */
E 9
I 9
	case '|':
	    if (p->word[1] == '|')
		continue;
	    /* fall into ... */
E 9

D 9
		case '>':
			if (p->next != p2 && eq(p->next->word, "&"))
				p = p->next;
			continue;
E 9
I 9
	case '>':
	    if (p->next != p2 && eq(p->next->word, STRand))
		p = p->next;
	    continue;
E 9

D 9
		case '&':
			if (l != 0)
				break;
			if (p->word[1] == '&')
				continue;
			t1 = syn1(p1, p, flags);
D 5
			if (t1->t_dtyp == TLST) {
E 5
I 5
D 7
    			if (t1->t_dtyp == TLST ||
    			    t1->t_dtyp == TAND ||
    			    t1->t_dtyp == TOR) {
E 7
I 7
    			if (t1->t_dtyp == NODE_LIST ||
    			    t1->t_dtyp == NODE_AND ||
    			    t1->t_dtyp == NODE_OR) {
E 7
E 5
				t = (struct command *) calloc(1, sizeof (*t));
D 7
				t->t_dtyp = TPAR;
				t->t_dflg = FAND|FINT;
E 7
I 7
				t->t_dtyp = NODE_PAREN;
				t->t_dflg = F_AMPERSAND|F_NOINTERRUPT;
E 7
				t->t_dspr = t1;
				t1 = t;
			} else
D 7
				t1->t_dflg |= FAND|FINT;
E 7
I 7
				t1->t_dflg |= F_AMPERSAND|F_NOINTERRUPT;
E 7
			t = (struct command *) calloc(1, sizeof (*t));
D 7
			t->t_dtyp = TLST;
E 7
I 7
			t->t_dtyp = NODE_LIST;
E 7
			t->t_dflg = 0;
			t->t_dcar = t1;
			t->t_dcdr = syntax(p, p2, flags);
			return(t);
		}
	if (l == 0)
		return (syn1(p1, p2, flags));
	seterr("Too many ('s");
	return (0);
E 9
I 9
	case '&':
	    if (l != 0)
		break;
	    if (p->word[1] == '&')
		continue;
	    t1 = syn1(p1, p, flags);
	    if (t1->t_dtyp == NODE_LIST ||
		t1->t_dtyp == NODE_AND ||
		t1->t_dtyp == NODE_OR) {
		t = (struct command *) xcalloc(1, sizeof(*t));
		t->t_dtyp = NODE_PAREN;
		t->t_dflg = F_AMPERSAND | F_NOINTERRUPT;
		t->t_dspr = t1;
		t1 = t;
	    }
	    else
		t1->t_dflg |= F_AMPERSAND | F_NOINTERRUPT;
	    t = (struct command *) xcalloc(1, sizeof(*t));
	    t->t_dtyp = NODE_LIST;
	    t->t_dflg = 0;
	    t->t_dcar = t1;
	    t->t_dcdr = syntax(p, p2, flags);
	    return (t);
	}
    if (l == 0)
	return (syn1(p1, p2, flags));
    seterror(ERR_TOOMANYLP);
    return (0);
E 9
}

/*
 * syn1
 *	syn1a
 *	syn1a ; syntax
 */
D 9
struct command *
E 9
I 9
static struct command *
E 9
syn1(p1, p2, flags)
D 9
	struct wordent *p1, *p2;
	int flags;
E 9
I 9
    struct wordent *p1, *p2;
    int     flags;
E 9
{
D 9
	register struct wordent *p;
	register struct command *t;
	int l;
E 9
I 9
    register struct wordent *p;
    register struct command *t;
    int     l;
E 9

D 9
	l = 0;
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    l = 0;
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			l++;
			continue;
E 9
I 9
	case '(':
	    l++;
	    continue;
E 9

D 9
		case ')':
			l--;
			continue;
E 9
I 9
	case ')':
	    l--;
	    continue;
E 9

D 9
		case ';':
		case '\n':
			if (l != 0)
				break;
			t = (struct command *) calloc(1, sizeof (*t));
D 7
			t->t_dtyp = TLST;
E 7
I 7
			t->t_dtyp = NODE_LIST;
E 7
			t->t_dcar = syn1a(p1, p, flags);
			t->t_dcdr = syntax(p->next, p2, flags);
			if (t->t_dcdr == 0)
				t->t_dcdr = t->t_dcar, t->t_dcar = 0;
			return (t);
		}
	return (syn1a(p1, p2, flags));
E 9
I 9
	case ';':
	case '\n':
	    if (l != 0)
		break;
	    t = (struct command *) xcalloc(1, sizeof(*t));
	    t->t_dtyp = NODE_LIST;
	    t->t_dcar = syn1a(p1, p, flags);
	    t->t_dcdr = syntax(p->next, p2, flags);
	    if (t->t_dcdr == 0)
		t->t_dcdr = t->t_dcar, t->t_dcar = 0;
	    return (t);
	}
    return (syn1a(p1, p2, flags));
E 9
}

/*
 * syn1a
 *	syn1b
 *	syn1b || syn1a
 */
D 9
struct command *
E 9
I 9
static struct command *
E 9
syn1a(p1, p2, flags)
D 9
	struct wordent *p1, *p2;
	int flags;
E 9
I 9
    struct wordent *p1, *p2;
    int     flags;
E 9
{
D 9
	register struct wordent *p;
	register struct command *t;
	register int l = 0;
E 9
I 9
    register struct wordent *p;
    register struct command *t;
    register int l = 0;
E 9

D 9
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			l++;
			continue;
E 9
I 9
	case '(':
	    l++;
	    continue;
E 9

D 9
		case ')':
			l--;
			continue;
E 9
I 9
	case ')':
	    l--;
	    continue;
E 9

D 9
		case '|':
			if (p->word[1] != '|')
				continue;
			if (l == 0) {
				t = (struct command *) calloc(1, sizeof (*t));
D 7
				t->t_dtyp = TOR;
E 7
I 7
				t->t_dtyp = NODE_OR;
E 7
				t->t_dcar = syn1b(p1, p, flags);
				t->t_dcdr = syn1a(p->next, p2, flags);
				t->t_dflg = 0;
				return (t);
			}
			continue;
		}
	return (syn1b(p1, p2, flags));
E 9
I 9
	case '|':
	    if (p->word[1] != '|')
		continue;
	    if (l == 0) {
		t = (struct command *) xcalloc(1, sizeof(*t));
		t->t_dtyp = NODE_OR;
		t->t_dcar = syn1b(p1, p, flags);
		t->t_dcdr = syn1a(p->next, p2, flags);
		t->t_dflg = 0;
		return (t);
	    }
	    continue;
	}
    return (syn1b(p1, p2, flags));
E 9
}

/*
 * syn1b
 *	syn2
 *	syn2 && syn1b
 */
D 9
struct command *
E 9
I 9
static struct command *
E 9
syn1b(p1, p2, flags)
D 9
	struct wordent *p1, *p2;
	int flags;
E 9
I 9
    struct wordent *p1, *p2;
    int     flags;
E 9
{
D 9
	register struct wordent *p;
	register struct command *t;
	register int l = 0;
E 9
I 9
    register struct wordent *p;
    register struct command *t;
    register int l = 0;
E 9

D 9
	l = 0;
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			l++;
			continue;
E 9
I 9
	case '(':
	    l++;
	    continue;
E 9

D 9
		case ')':
			l--;
			continue;
E 9
I 9
	case ')':
	    l--;
	    continue;
E 9

D 9
		case '&':
			if (p->word[1] == '&' && l == 0) {
				t = (struct command *) calloc(1, sizeof (*t));
D 7
				t->t_dtyp = TAND;
E 7
I 7
				t->t_dtyp = NODE_AND;
E 7
				t->t_dcar = syn2(p1, p, flags);
				t->t_dcdr = syn1b(p->next, p2, flags);
				t->t_dflg = 0;
				return (t);
			}
			continue;
		}
	return (syn2(p1, p2, flags));
E 9
I 9
	case '&':
	    if (p->word[1] == '&' && l == 0) {
		t = (struct command *) xcalloc(1, sizeof(*t));
		t->t_dtyp = NODE_AND;
		t->t_dcar = syn2(p1, p, flags);
		t->t_dcdr = syn1b(p->next, p2, flags);
		t->t_dflg = 0;
		return (t);
	    }
	    continue;
	}
    return (syn2(p1, p2, flags));
E 9
}

/*
 * syn2
 *	syn3
 *	syn3 | syn2
 *	syn3 |& syn2
 */
D 9
struct command *
E 9
I 9
static struct command *
E 9
syn2(p1, p2, flags)
D 9
	struct wordent *p1, *p2;
	int flags;
E 9
I 9
    struct wordent *p1, *p2;
    int     flags;
E 9
{
D 9
	register struct wordent *p, *pn;
	register struct command *t;
	register int l = 0;
	int f;
E 9
I 9
    register struct wordent *p, *pn;
    register struct command *t;
    register int l = 0;
    int     f;
E 9

D 9
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			l++;
			continue;
E 9
I 9
	case '(':
	    l++;
	    continue;
E 9

D 9
		case ')':
			l--;
			continue;
E 9
I 9
	case ')':
	    l--;
	    continue;
E 9

D 9
		case '|':
			if (l != 0)
				continue;
			t = (struct command *) calloc(1, sizeof (*t));
			f = flags | POUT;
			pn = p->next;
			if (pn != p2 && pn->word[0] == '&') {
				f |= PDIAG;
D 7
				t->t_dflg |= FDIAG;
E 7
I 7
				t->t_dflg |= F_STDERR;
E 7
			}
D 7
			t->t_dtyp = TFIL;
E 7
I 7
			t->t_dtyp = NODE_PIPE;
E 7
			t->t_dcar = syn3(p1, p, f);
			if (pn != p2 && pn->word[0] == '&')
				p = pn;
			t->t_dcdr = syn2(p->next, p2, flags | PIN);
			return (t);
		}
	return (syn3(p1, p2, flags));
E 9
I 9
	case '|':
	    if (l != 0)
		continue;
	    t = (struct command *) xcalloc(1, sizeof(*t));
	    f = flags | POUT;
	    pn = p->next;
	    if (pn != p2 && pn->word[0] == '&') {
D 14
		f |= PDIAG;
E 14
I 14
		f |= PERR;
E 14
		t->t_dflg |= F_STDERR;
	    }
	    t->t_dtyp = NODE_PIPE;
	    t->t_dcar = syn3(p1, p, f);
	    if (pn != p2 && pn->word[0] == '&')
		p = pn;
	    t->t_dcdr = syn2(p->next, p2, flags | PIN);
	    return (t);
	}
    return (syn3(p1, p2, flags));
E 9
}

D 9
char	*RELPAR =	"<>()";
E 9
I 9
static char RELPAR[] = {'<', '>', '(', ')', '\0'};
E 9

/*
 * syn3
 *	( syn0 ) [ < in  ] [ > out ]
 *	word word* [ < in ] [ > out ]
 *	KEYWORD ( word* ) word* [ < in ] [ > out ]
 *
 *	KEYWORD = (@ exit foreach if set switch test while)
 */
D 9
struct command *
E 9
I 9
static struct command *
E 9
syn3(p1, p2, flags)
D 9
	struct wordent *p1, *p2;
	int flags;
E 9
I 9
    struct wordent *p1, *p2;
    int     flags;
E 9
{
D 9
	register struct wordent *p;
	struct wordent *lp, *rp;
	register struct command *t;
	register int l;
	char **av;
	int n, c;
	bool specp = 0;
E 9
I 9
    register struct wordent *p;
    struct wordent *lp, *rp;
    register struct command *t;
    register int l;
    Char  **av;
    int     n, c;
    bool    specp = 0;
E 9

D 9
	if (p1 != p2) {
		p = p1;
E 9
I 9
    if (p1 != p2) {
	p = p1;
E 9
again:
D 9
		switch (srchx(p->word)) {
E 9
I 9
	switch (srchx(p->word)) {
E 9

D 7
		case ZELSE:
E 7
I 7
D 9
		case T_ELSE:
E 7
			p = p->next;
			if (p != p2)
				goto again;
			break;
E 9
I 9
	case T_ELSE:
	    p = p->next;
	    if (p != p2)
		goto again;
	    break;
E 9

D 7
		case ZEXIT:
		case ZFOREACH:
		case ZIF:
		case ZLET:
		case ZSET:
		case ZSWITCH:
		case ZWHILE:
E 7
I 7
D 9
		case T_EXIT:
		case T_FOREACH:
		case T_IF:
		case T_LET:
		case T_SET:
		case T_SWITCH:
		case T_WHILE:
E 7
			specp = 1;
			break;
		}
E 9
I 9
	case T_EXIT:
	case T_FOREACH:
	case T_IF:
	case T_LET:
	case T_SET:
	case T_SWITCH:
	case T_WHILE:
	    specp = 1;
	    break;
E 9
	}
D 9
	n = 0;
	l = 0;
	for (p = p1; p != p2; p = p->next)
		switch (p->word[0]) {
E 9
I 9
    }
    n = 0;
    l = 0;
    for (p = p1; p != p2; p = p->next)
	switch (p->word[0]) {
E 9

D 9
		case '(':
			if (specp)
				n++;
			l++;
			continue;
E 9
I 9
	case '(':
	    if (specp)
		n++;
	    l++;
	    continue;
E 9

D 9
		case ')':
			if (specp)
				n++;
			l--;
			continue;
E 9
I 9
	case ')':
	    if (specp)
		n++;
	    l--;
	    continue;
E 9

D 9
		case '>':
		case '<':
			if (l != 0) {
				if (specp)
					n++;
				continue;
			}
			if (p->next == p2)
				continue;
D 6
			if (any(p->next->word[0], RELPAR))
E 6
I 6
			if (index(RELPAR, p->next->word[0]))
E 6
				continue;
			n--;
			continue;
E 9
I 9
	case '>':
	case '<':
	    if (l != 0) {
		if (specp)
		    n++;
		continue;
	    }
	    if (p->next == p2)
		continue;
	    if (any(RELPAR, p->next->word[0]))
		continue;
	    n--;
	    continue;
E 9

D 9
		default:
			if (!specp && l != 0)
				continue;
			n++;
			continue;
		}
	if (n < 0)
		n = 0;
	t = (struct command *) calloc(1, sizeof (*t));
D 2
	av = (char **) calloc(n + 1, sizeof (char **));
E 2
I 2
	av = (char **) calloc((unsigned) (n + 1), sizeof (char **));
E 2
	t->t_dcom = av;
E 9
I 9
	default:
	    if (!specp && l != 0)
		continue;
	    n++;
	    continue;
	}
    if (n < 0)
E 9
	n = 0;
D 9
	if (p2->word[0] == ')')
D 7
		t->t_dflg = FPAR;
E 7
I 7
		t->t_dflg = F_NOFORK;
E 7
	lp = 0;
	rp = 0;
	l = 0;
	for (p = p1; p != p2; p = p->next) {
		c = p->word[0];
		switch (c) {
E 9
I 9
    t = (struct command *) xcalloc(1, sizeof(*t));
    av = (Char **) xcalloc((size_t) (n + 1), sizeof(Char **));
    t->t_dcom = av;
    n = 0;
    if (p2->word[0] == ')')
	t->t_dflg = F_NOFORK;
    lp = 0;
    rp = 0;
    l = 0;
    for (p = p1; p != p2; p = p->next) {
	c = p->word[0];
	switch (c) {
E 9

D 9
		case '(':
			if (l == 0) {
				if (lp != 0 && !specp)
					seterr("Badly placed (");
				lp = p->next;
			}
			l++;
			goto savep;
E 9
I 9
	case '(':
	    if (l == 0) {
		if (lp != 0 && !specp)
		    seterror(ERR_BADPLP);
		lp = p->next;
	    }
	    l++;
	    goto savep;
E 9

D 9
		case ')':
			l--;
			if (l == 0)
				rp = p;
			goto savep;
E 9
I 9
	case ')':
	    l--;
	    if (l == 0)
		rp = p;
	    goto savep;
E 9

D 9
		case '>':
			if (l != 0)
				goto savep;
			if (p->word[1] == '>')
D 7
				t->t_dflg |= FCAT;
E 7
I 7
				t->t_dflg |= F_APPEND;
E 7
			if (p->next != p2 && eq(p->next->word, "&")) {
D 7
				t->t_dflg |= FDIAG, p = p->next;
E 7
I 7
				t->t_dflg |= F_STDERR;
				p = p->next;
E 7
				if (flags & (POUT|PDIAG))
					goto badout;
			}
D 7
			if (p->next != p2 && eq(p->next->word, "!"))
				t->t_dflg |= FANY, p = p->next;
E 7
I 7
			if (p->next != p2 && eq(p->next->word, "!")) {
				t->t_dflg |= F_OVERWRITE;
				p = p->next;
			}
E 7
			if (p->next == p2) {
missfile:
				seterr("Missing name for redirect");
				continue;
			}
			p = p->next;
D 6
			if (any(p->word[0], RELPAR))
E 6
I 6
			if (index(RELPAR, p->word[0]))
E 6
				goto missfile;
			if ((flags & POUT) && (flags & PDIAG) == 0 || t->t_drit)
badout:
				seterr("Ambiguous output redirect");
			else
				t->t_drit = savestr(p->word);
			continue;
E 9
I 9
	case '>':
	    if (l != 0)
		goto savep;
	    if (p->word[1] == '>')
		t->t_dflg |= F_APPEND;
	    if (p->next != p2 && eq(p->next->word, STRand)) {
		t->t_dflg |= F_STDERR, p = p->next;
D 14
		if (flags & (POUT | PDIAG)) {
E 14
I 14
		if (flags & (POUT | PERR)) {
E 14
		    seterror(ERR_OUTRED);
		    continue;
		}
	    }
	    if (p->next != p2 && eq(p->next->word, STRbang))
		t->t_dflg |= F_OVERWRITE, p = p->next;
	    if (p->next == p2) {
		seterror(ERR_MISRED);
		continue;
	    }
	    p = p->next;
	    if (any(RELPAR, p->word[0])) {
		seterror(ERR_MISRED);
		continue;
	    }
D 14
	    if ((flags & POUT) && (flags & PDIAG) == 0 || t->t_drit)
E 14
I 14
D 15
	    if ((flags & POUT) && (flags & PERR) == 0 || t->t_drit)
E 15
I 15
	    if ((flags & POUT) && ((flags & PERR) == 0 || t->t_drit))
E 15
E 14
		seterror(ERR_OUTRED);
	    else
		t->t_drit = Strsave(p->word);
	    continue;
E 9

D 9
		case '<':
			if (l != 0)
				goto savep;
			if (p->word[1] == '<')
D 7
				t->t_dflg |= FHERE;
E 7
I 7
				t->t_dflg |= F_READ;
E 7
			if (p->next == p2)
				goto missfile;
			p = p->next;
D 6
			if (any(p->word[0], RELPAR))
E 6
I 6
			if (index(RELPAR, p->word[0]))
E 6
				goto missfile;
D 7
			if ((flags & PHERE) && (t->t_dflg & FHERE))
E 7
I 7
			if ((flags & PHERE) && (t->t_dflg & F_READ))
E 7
				seterr("Can't << within ()'s");
			else if ((flags & PIN) || t->t_dlef)
				seterr("Ambiguous input redirect");
			else
				t->t_dlef = savestr(p->word);
			continue;
E 9
I 9
	case '<':
	    if (l != 0)
		goto savep;
	    if (p->word[1] == '<')
		t->t_dflg |= F_READ;
	    if (p->next == p2) {
		seterror(ERR_MISRED);
		continue;
	    }
	    p = p->next;
	    if (any(RELPAR, p->word[0])) {
		seterror(ERR_MISRED);
		continue;
	    }
	    if ((flags & PHERE) && (t->t_dflg & F_READ))
		seterror(ERR_REDPAR);
	    else if ((flags & PIN) || t->t_dlef)
		seterror(ERR_INRED);
	    else
		t->t_dlef = Strsave(p->word);
	    continue;
E 9

D 9
savep:
			if (!specp)
				continue;
		default:
			if (l != 0 && !specp)
				continue;
			if (err == 0)
				av[n] = savestr(p->word);
			n++;
			continue;
		}
E 9
I 9
    savep:
	    if (!specp)
		continue;
	default:
	    if (l != 0 && !specp)
		continue;
	    if (seterr == 0)
		av[n] = Strsave(p->word);
	    n++;
	    continue;
E 9
	}
D 9
	if (lp != 0 && !specp) {
		if (n != 0)
			seterr("Badly placed ()'s");
D 7
		t->t_dtyp = TPAR;
E 7
I 7
		t->t_dtyp = NODE_PAREN;
E 7
		t->t_dspr = syn0(lp, rp, PHERE);
	} else {
		if (n == 0)
			seterr("Invalid null command");
D 7
		t->t_dtyp = TCOM;
E 7
I 7
		t->t_dtyp = NODE_COMMAND;
E 7
	}
	return (t);
E 9
I 9
    }
    if (lp != 0 && !specp) {
	if (n != 0)
	    seterror(ERR_BADPLPS);
	t->t_dtyp = NODE_PAREN;
	t->t_dspr = syn0(lp, rp, PHERE);
    }
    else {
	if (n == 0)
	    seterror(ERR_NULLCOM);
	t->t_dtyp = NODE_COMMAND;
    }
    return (t);
E 9
}

I 9
void
E 9
freesyn(t)
D 9
	register struct command *t;
E 9
I 9
    register struct command *t;
E 9
{
D 9
	register char **v;
E 9
I 9
    register Char **v;
E 9

D 9
	if (t == 0)
		return;
	switch (t->t_dtyp) {
E 9
I 9
    if (t == 0)
	return;
    switch (t->t_dtyp) {
E 9

D 7
	case TCOM:
E 7
I 7
D 9
	case NODE_COMMAND:
E 7
		for (v = t->t_dcom; *v; v++)
D 2
			xfree(*v);
		xfree((char *)(t->t_dcom));
E 2
I 2
			XFREE(*v)
		XFREE((char *)t->t_dcom)
E 2
		goto lr;
E 9
I 9
    case NODE_COMMAND:
	for (v = t->t_dcom; *v; v++)
	    xfree((ptr_t) * v);
	xfree((ptr_t) (t->t_dcom));
	xfree((ptr_t) t->t_dlef);
	xfree((ptr_t) t->t_drit);
	break;
    case NODE_PAREN:
	freesyn(t->t_dspr);
	xfree((ptr_t) t->t_dlef);
	xfree((ptr_t) t->t_drit);
	break;
E 9

D 7
	case TPAR:
E 7
I 7
D 9
	case NODE_PAREN:
E 7
		freesyn(t->t_dspr);
		/* fall into ... */

lr:
D 2
		xfree(t->t_dlef), xfree(t->t_drit);
E 2
I 2
		XFREE(t->t_dlef)
		XFREE(t->t_drit)
E 2
		break;

D 7
	case TAND:
	case TOR:
	case TFIL:
	case TLST:
		freesyn(t->t_dcar), freesyn(t->t_dcdr);
E 7
I 7
	case NODE_AND:
	case NODE_OR:
	case NODE_PIPE:
	case NODE_LIST:
		freesyn(t->t_dcar);
		freesyn(t->t_dcdr);
E 7
		break;
	}
D 2
	xfree((char *)t);
E 2
I 2
	XFREE((char *)t)
E 9
I 9
    case NODE_AND:
    case NODE_OR:
    case NODE_PIPE:
    case NODE_LIST:
	freesyn(t->t_dcar), freesyn(t->t_dcdr);
	break;
    }
    xfree((ptr_t) t);
E 9
E 2
}
E 1
