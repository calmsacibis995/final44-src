h55124
s 00002/00002/00683
d D 8.1 93/05/31 16:41:59 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00683
d D 5.16 93/05/22 19:06:28 christos 19 18
c Fixed gcc -Wall warnings
e
s 00001/00001/00684
d D 5.15 91/11/06 16:09:36 christos 18 17
c Added support for displaying non-printable characters
e
s 00001/00001/00684
d D 5.14 91/09/06 01:25:50 christos 17 16
c Replaced exp with expr to avoild libm conflict
e
s 00003/00000/00682
d D 5.13 91/07/22 11:47:26 christos 16 15
c  no short strings bug fix
e
s 00006/00006/00676
d D 5.12 91/07/19 17:30:44 christos 15 14
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00000/00676
d D 5.11 91/06/08 17:08:42 christos 14 13
c More prototype fixes, Removed TERMIOS define
e
s 00004/00001/00672
d D 5.10 91/06/08 12:20:17 bostic 13 12
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00016/00017/00657
d D 5.9 91/06/07 20:57:20 christos 12 11
c static function prototypes
e
s 00004/00002/00670
d D 5.8 91/06/07 11:13:22 bostic 11 10
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00475/00400/00197
d D 5.7 91/06/04 13:31:25 bostic 10 9
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/00590
d D 5.6 91/04/04 18:17:38 bostic 9 8
c new copyright; att/bsd/shared
e
s 00001/00001/00595
d D 5.5 91/04/01 17:37:10 bostic 8 7
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00002/00002/00594
d D 5.4 91/03/14 12:29:06 bostic 7 6
c any -> index (use the faster library routine)
e
s 00001/00001/00595
d D 5.3 85/06/23 17:16:39 edward 6 5
c missing savestr() in exp6, from gorlick@trwrb.uucp
e
s 00003/00003/00593
d D 5.2 85/06/06 13:09:49 edward 5 4
c cleaning up after bozos
e
s 00008/00002/00588
d D 5.1 85/06/04 10:57:42 dist 4 3
c Add copyright
e
s 00002/00000/00588
d D 4.3 85/03/19 17:59:05 mckusick 3 2
c check for null pointer reference
e
s 00034/00021/00554
d D 4.2 84/12/13 14:40:08 edward 2 1
c performance
e
s 00575/00000/00000
d D 4.1 80/10/09 12:40:54 bill 1 0
c date and time created 80/10/09 12:40:54 by bill
e
u
U
t
T
I 4
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
D 5
 * All rights reserved.  The Berkeley software License Agreement
E 5
I 5
 * All rights reserved.  The Berkeley Software License Agreement
E 5
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 20
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * %sccs.include.redist.c%
E 9
 */

E 4
I 1
D 2
static	char *sccsid = "%Z%%M% %I% %G%";
E 2
I 2
#ifndef lint
D 4
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 4
I 4
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 5
I 5
D 9
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 9
I 9
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 9
E 5
E 4
E 2

I 13
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
I 16
#ifndef SHORT_STRINGS
#include <string.h>
#endif /* SHORT_STRINGS */
E 16
I 14
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 14
E 13
D 11
#include "sh.h"
E 11
I 11
#include "csh.h"
D 13
#include "dir.h"
E 13
#include "extern.h"
E 11

D 10
/*
 * C shell
 */

E 10
#define IGNORE	1	/* in ignore, it means to ignore value, just parse */
#define NOGLOB	2	/* in ignore, it means not to globone */

#define	ADDOP	1
#define	MULOP	2
#define	EQOP	4
#define	RELOP	8
#define	RESTOP	16
#define	ANYOP	31

#define	EQEQ	1
#define	GTR	2
#define	LSS	4
#define	NOTEQ	6
#define EQMATCH 7
#define NOTEQMATCH 8

I 10
D 12
static int exp1();
static int exp2();
static int exp2a();
static int exp2b();
static int exp2c();
static Char *exp3();
static Char *exp3a();
static Char *exp4();
static Char *exp5();
static Char *exp6();
static void evalav();
static int isa();
static int egetn();
E 12
I 12
static int	exp1	__P((Char ***, bool));
static int	exp2	__P((Char ***, bool));
static int	exp2a	__P((Char ***, bool));
static int	exp2b	__P((Char ***, bool));
static int	exp2c	__P((Char ***, bool));
static Char *	exp3	__P((Char ***, bool));
static Char *	exp3a	__P((Char ***, bool));
static Char *	exp4	__P((Char ***, bool));
static Char *	exp5	__P((Char ***, bool));
static Char *	exp6	__P((Char ***, bool));
static void	evalav	__P((Char **));
static int	isa	__P((Char *, int));
static int	egetn	__P((Char *));
E 12

#ifdef EDEBUG
D 12
static void etracc();
static void etraci();
E 12
I 12
static void	etracc	__P((char *, Char *, Char ***));
static void	etraci	__P((char *, int, Char ***));
E 12
#endif

int
E 10
D 17
exp(vp)
E 17
I 17
expr(vp)
E 17
D 10
	register char ***vp;
E 10
I 10
    register Char ***vp;
E 10
{
D 10

	return (exp0(vp, 0));
E 10
I 10
    return (exp0(vp, 0));
E 10
}

I 10
int
E 10
exp0(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register int p1 = exp1(vp, ignore);
	
E 10
I 10
    register int p1 = exp1(vp, ignore);

E 10
#ifdef EDEBUG
D 10
	etraci("exp0 p1", p1, vp);
E 10
I 10
    etraci("exp0 p1", p1, vp);
E 10
#endif
D 10
	if (**vp && eq(**vp, "||")) {
		register int p2;
E 10
I 10
    if (**vp && eq(**vp, STRor2)) {
	register int p2;
E 10

D 10
		(*vp)++;
		p2 = exp0(vp, (ignore&IGNORE) || p1);
E 10
I 10
	(*vp)++;
	p2 = exp0(vp, (ignore & IGNORE) || p1);
E 10
#ifdef EDEBUG
D 10
		etraci("exp0 p2", p2, vp);
E 10
I 10
	etraci("exp0 p2", p2, vp);
E 10
#endif
D 10
		return (p1 || p2);
	}
	return (p1);
E 10
I 10
	return (p1 || p2);
    }
    return (p1);
E 10
}

I 10
static int
E 10
exp1(vp, ignore)
D 10
	register char ***vp;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register int p1 = exp2(vp, ignore);
E 10
I 10
    register int p1 = exp2(vp, ignore);
E 10

#ifdef EDEBUG
D 10
	etraci("exp1 p1", p1, vp);
E 10
I 10
    etraci("exp1 p1", p1, vp);
E 10
#endif
D 10
	if (**vp && eq(**vp, "&&")) {
		register int p2;
E 10
I 10
    if (**vp && eq(**vp, STRand2)) {
	register int p2;
E 10

D 10
		(*vp)++;
		p2 = exp1(vp, (ignore&IGNORE) || !p1);
E 10
I 10
	(*vp)++;
	p2 = exp1(vp, (ignore & IGNORE) || !p1);
E 10
#ifdef EDEBUG
D 10
		etraci("exp1 p2", p2, vp);
E 10
I 10
	etraci("exp1 p2", p2, vp);
E 10
#endif
D 10
		return (p1 && p2);
	}
	return (p1);
E 10
I 10
	return (p1 && p2);
    }
    return (p1);
E 10
}

I 10
static int
E 10
exp2(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register int p1 = exp2a(vp, ignore);
E 10
I 10
    register int p1 = exp2a(vp, ignore);
E 10

#ifdef EDEBUG
D 10
	etraci("exp3 p1", p1, vp);
E 10
I 10
    etraci("exp3 p1", p1, vp);
E 10
#endif
D 10
	if (**vp && eq(**vp, "|")) {
		register int p2;
E 10
I 10
    if (**vp && eq(**vp, STRor)) {
	register int p2;
E 10

D 10
		(*vp)++;
		p2 = exp2(vp, ignore);
E 10
I 10
	(*vp)++;
	p2 = exp2(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etraci("exp3 p2", p2, vp);
E 10
I 10
	etraci("exp3 p2", p2, vp);
E 10
#endif
D 10
		return (p1 | p2);
	}
	return (p1);
E 10
I 10
	return (p1 | p2);
    }
    return (p1);
E 10
}

I 10
static int
E 10
exp2a(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register int p1 = exp2b(vp, ignore);
E 10
I 10
    register int p1 = exp2b(vp, ignore);
E 10

#ifdef EDEBUG
D 10
	etraci("exp2a p1", p1, vp);
E 10
I 10
    etraci("exp2a p1", p1, vp);
E 10
#endif
D 10
	if (**vp && eq(**vp, "^")) {
		register int p2;
E 10
I 10
    if (**vp && eq(**vp, STRcaret)) {
	register int p2;
E 10

D 10
		(*vp)++;
		p2 = exp2a(vp, ignore);
E 10
I 10
	(*vp)++;
	p2 = exp2a(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etraci("exp2a p2", p2, vp);
E 10
I 10
	etraci("exp2a p2", p2, vp);
E 10
#endif
D 10
		return (p1 ^ p2);
	}
	return (p1);
E 10
I 10
	return (p1 ^ p2);
    }
    return (p1);
E 10
}

I 10
static int
E 10
exp2b(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register int p1 = exp2c(vp, ignore);
E 10
I 10
    register int p1 = exp2c(vp, ignore);
E 10

#ifdef EDEBUG
D 10
	etraci("exp2b p1", p1, vp);
E 10
I 10
    etraci("exp2b p1", p1, vp);
E 10
#endif
D 10
	if (**vp && eq(**vp, "&")) {
		register int p2;
E 10
I 10
    if (**vp && eq(**vp, STRand)) {
	register int p2;
E 10

D 10
		(*vp)++;
		p2 = exp2b(vp, ignore);
E 10
I 10
	(*vp)++;
	p2 = exp2b(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etraci("exp2b p2", p2, vp);
E 10
I 10
	etraci("exp2b p2", p2, vp);
E 10
#endif
D 10
		return (p1 & p2);
	}
	return (p1);
E 10
I 10
	return (p1 & p2);
    }
    return (p1);
E 10
}

I 10
static int
E 10
exp2c(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register char *p1 = exp3(vp, ignore);
	register char *p2;
	register int i;
E 10
I 10
    register Char *p1 = exp3(vp, ignore);
    register Char *p2;
    register int i;
E 10

#ifdef EDEBUG
D 10
	etracc("exp2c p1", p1, vp);
E 10
I 10
    etracc("exp2c p1", p1, vp);
E 10
#endif
D 10
	if (i = isa(**vp, EQOP)) {
		(*vp)++;
		if (i == EQMATCH || i == NOTEQMATCH)
			ignore |= NOGLOB;
		p2 = exp3(vp, ignore);
E 10
I 10
D 19
    if (i = isa(**vp, EQOP)) {
E 19
I 19
    if ((i = isa(**vp, EQOP)) != 0) {
E 19
	(*vp)++;
	if (i == EQMATCH || i == NOTEQMATCH)
	    ignore |= NOGLOB;
	p2 = exp3(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp2c p2", p2, vp);
E 10
I 10
	etracc("exp2c p2", p2, vp);
E 10
#endif
D 10
		if (!(ignore&IGNORE)) switch (i) {
E 10
I 10
	if (!(ignore & IGNORE))
	    switch (i) {
E 10

D 10
		case EQEQ:
			i = eq(p1, p2);
			break;
E 10
I 10
	    case EQEQ:
		i = eq(p1, p2);
		break;
E 10

D 10
		case NOTEQ:
			i = !eq(p1, p2);
			break;
E 10
I 10
	    case NOTEQ:
		i = !eq(p1, p2);
		break;
E 10

D 10
		case EQMATCH:
			i = Gmatch(p1, p2);
			break;
E 10
I 10
	    case EQMATCH:
		i = Gmatch(p1, p2);
		break;
E 10

D 10
		case NOTEQMATCH:
			i = !Gmatch(p1, p2);
			break;
		}
		xfree(p1), xfree(p2);
		return (i);
	}
	i = egetn(p1);
	xfree(p1);
E 10
I 10
	    case NOTEQMATCH:
		i = !Gmatch(p1, p2);
		break;
	    }
	xfree((ptr_t) p1);
	xfree((ptr_t) p2);
E 10
	return (i);
I 10
    }
    i = egetn(p1);
    xfree((ptr_t) p1);
    return (i);
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
exp3(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register char *p1, *p2;
	register int i;
E 10
I 10
    register Char *p1, *p2;
    register int i;
E 10

D 10
	p1 = exp3a(vp, ignore);
E 10
I 10
    p1 = exp3a(vp, ignore);
E 10
#ifdef EDEBUG
D 10
	etracc("exp3 p1", p1, vp);
E 10
I 10
    etracc("exp3 p1", p1, vp);
E 10
#endif
D 10
	if (i = isa(**vp, RELOP)) {
		(*vp)++;
		if (**vp && eq(**vp, "="))
			i |= 1, (*vp)++;
		p2 = exp3(vp, ignore);
E 10
I 10
D 19
    if (i = isa(**vp, RELOP)) {
E 19
I 19
    if ((i = isa(**vp, RELOP)) != 0) {
E 19
	(*vp)++;
	if (**vp && eq(**vp, STRequal))
	    i |= 1, (*vp)++;
	p2 = exp3(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp3 p2", p2, vp);
E 10
I 10
	etracc("exp3 p2", p2, vp);
E 10
#endif
D 10
		if (!(ignore&IGNORE)) switch (i) {
E 10
I 10
	if (!(ignore & IGNORE))
	    switch (i) {
E 10

D 10
		case GTR:
			i = egetn(p1) > egetn(p2);
			break;
E 10
I 10
	    case GTR:
		i = egetn(p1) > egetn(p2);
		break;
E 10

D 10
		case GTR|1:
			i = egetn(p1) >= egetn(p2);
			break;
E 10
I 10
	    case GTR | 1:
		i = egetn(p1) >= egetn(p2);
		break;
E 10

D 10
		case LSS:
			i = egetn(p1) < egetn(p2);
			break;
E 10
I 10
	    case LSS:
		i = egetn(p1) < egetn(p2);
		break;
E 10

D 10
		case LSS|1:
			i = egetn(p1) <= egetn(p2);
			break;
		}
		xfree(p1), xfree(p2);
		return (putn(i));
	}
	return (p1);
E 10
I 10
	    case LSS | 1:
		i = egetn(p1) <= egetn(p2);
		break;
	    }
	xfree((ptr_t) p1);
	xfree((ptr_t) p2);
	return (putn(i));
    }
    return (p1);
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
exp3a(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register char *p1, *p2, *op;
	register int i;
E 10
I 10
    register Char *p1, *p2, *op;
    register int i;
E 10

D 10
	p1 = exp4(vp, ignore);
E 10
I 10
    p1 = exp4(vp, ignore);
E 10
#ifdef EDEBUG
D 10
	etracc("exp3a p1", p1, vp);
E 10
I 10
    etracc("exp3a p1", p1, vp);
E 10
#endif
D 10
	op = **vp;
D 7
	if (op && any(op[0], "<>") && op[0] == op[1]) {
E 7
I 7
	if (op && index("<>", op[0]) && op[0] == op[1]) {
E 7
		(*vp)++;
		p2 = exp3a(vp, ignore);
E 10
I 10
    op = **vp;
    if (op && any("<>", op[0]) && op[0] == op[1]) {
	(*vp)++;
	p2 = exp3a(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp3a p2", p2, vp);
E 10
I 10
	etracc("exp3a p2", p2, vp);
E 10
#endif
D 10
		if (op[0] == '<')
			i = egetn(p1) << egetn(p2);
		else
			i = egetn(p1) >> egetn(p2);
		xfree(p1), xfree(p2);
		return (putn(i));
	}
	return (p1);
E 10
I 10
	if (op[0] == '<')
	    i = egetn(p1) << egetn(p2);
	else
	    i = egetn(p1) >> egetn(p2);
	xfree((ptr_t) p1);
	xfree((ptr_t) p2);
	return (putn(i));
    }
    return (p1);
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
exp4(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register char *p1, *p2;
	register int i = 0;
E 10
I 10
    register Char *p1, *p2;
    register int i = 0;
E 10

D 10
	p1 = exp5(vp, ignore);
E 10
I 10
    p1 = exp5(vp, ignore);
E 10
#ifdef EDEBUG
D 10
	etracc("exp4 p1", p1, vp);
E 10
I 10
    etracc("exp4 p1", p1, vp);
E 10
#endif
D 10
	if (isa(**vp, ADDOP)) {
		register char *op = *(*vp)++;
E 10
I 10
    if (isa(**vp, ADDOP)) {
	register Char *op = *(*vp)++;
E 10

D 10
		p2 = exp4(vp, ignore);
E 10
I 10
	p2 = exp4(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp4 p2", p2, vp);
E 10
I 10
	etracc("exp4 p2", p2, vp);
E 10
#endif
D 10
		if (!(ignore&IGNORE)) switch (op[0]) {
E 10
I 10
	if (!(ignore & IGNORE))
	    switch (op[0]) {
E 10

D 10
		case '+':
			i = egetn(p1) + egetn(p2);
			break;
E 10
I 10
	    case '+':
		i = egetn(p1) + egetn(p2);
		break;
E 10

D 10
		case '-':
			i = egetn(p1) - egetn(p2);
			break;
		}
		xfree(p1), xfree(p2);
		return (putn(i));
	}
	return (p1);
E 10
I 10
	    case '-':
		i = egetn(p1) - egetn(p2);
		break;
	    }
	xfree((ptr_t) p1);
	xfree((ptr_t) p2);
	return (putn(i));
    }
    return (p1);
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
exp5(vp, ignore)
D 10
	register char ***vp;
	bool ignore;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	register char *p1, *p2;
	register int i = 0;
E 10
I 10
    register Char *p1, *p2;
    register int i = 0;
E 10

D 10
	p1 = exp6(vp, ignore);
E 10
I 10
    p1 = exp6(vp, ignore);
E 10
#ifdef EDEBUG
D 10
	etracc("exp5 p1", p1, vp);
E 10
I 10
    etracc("exp5 p1", p1, vp);
E 10
#endif
D 10
	if (isa(**vp, MULOP)) {
		register char *op = *(*vp)++;
E 10
I 10
    if (isa(**vp, MULOP)) {
	register Char *op = *(*vp)++;
E 10

D 10
		p2 = exp5(vp, ignore);
E 10
I 10
	p2 = exp5(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp5 p2", p2, vp);
E 10
I 10
	etracc("exp5 p2", p2, vp);
E 10
#endif
D 10
		if (!(ignore&IGNORE)) switch (op[0]) {
E 10
I 10
	if (!(ignore & IGNORE))
	    switch (op[0]) {
E 10

D 10
		case '*':
			i = egetn(p1) * egetn(p2);
			break;
E 10
I 10
	    case '*':
		i = egetn(p1) * egetn(p2);
		break;
E 10

D 10
		case '/':
			i = egetn(p2);
			if (i == 0)
				error("Divide by 0");
			i = egetn(p1) / i;
			break;
E 10
I 10
	    case '/':
		i = egetn(p2);
		if (i == 0)
		    stderror(ERR_DIV0);
		i = egetn(p1) / i;
		break;
E 10

D 10
		case '%':
			i = egetn(p2);
			if (i == 0)
				error("Mod by 0");
			i = egetn(p1) % i;
			break;
		}
		xfree(p1), xfree(p2);
		return (putn(i));
	}
	return (p1);
E 10
I 10
	    case '%':
		i = egetn(p2);
		if (i == 0)
		    stderror(ERR_MOD0);
		i = egetn(p1) % i;
		break;
	    }
	xfree((ptr_t) p1);
	xfree((ptr_t) p2);
	return (putn(i));
    }
    return (p1);
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
exp6(vp, ignore)
D 10
	register char ***vp;
E 10
I 10
    register Char ***vp;
    bool    ignore;
E 10
{
D 10
	int ccode, i;
	register char *cp, *dp, *ep;
E 10
I 10
    int     ccode, i = 0;
    register Char *cp, *dp, *ep;
E 10

I 3
D 10
	if (**vp == 0)
		bferr("Expression syntax");
E 3
	if (eq(**vp, "!")) {
		(*vp)++;
		cp = exp6(vp, ignore);
E 10
I 10
    if (**vp == 0)
	stderror(ERR_NAME | ERR_EXPRESSION);
    if (eq(**vp, STRbang)) {
	(*vp)++;
	cp = exp6(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp6 ! cp", cp, vp);
E 10
I 10
	etracc("exp6 ! cp", cp, vp);
E 10
#endif
D 10
		i = egetn(cp);
		xfree(cp);
		return (putn(!i));
	}
	if (eq(**vp, "~")) {
		(*vp)++;
		cp = exp6(vp, ignore);
E 10
I 10
	i = egetn(cp);
	xfree((ptr_t) cp);
	return (putn(!i));
    }
    if (eq(**vp, STRtilde)) {
	(*vp)++;
	cp = exp6(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etracc("exp6 ~ cp", cp, vp);
E 10
I 10
	etracc("exp6 ~ cp", cp, vp);
E 10
#endif
D 10
		i = egetn(cp);
		xfree(cp);
		return (putn(~i));
	}
	if (eq(**vp, "(")) {
		(*vp)++;
		ccode = exp0(vp, ignore);
E 10
I 10
	i = egetn(cp);
	xfree((ptr_t) cp);
	return (putn(~i));
    }
    if (eq(**vp, STRLparen)) {
	(*vp)++;
	ccode = exp0(vp, ignore);
E 10
#ifdef EDEBUG
D 10
		etraci("exp6 () ccode", ccode, vp);
E 10
I 10
	etraci("exp6 () ccode", ccode, vp);
E 10
#endif
D 10
		if (*vp == 0 || **vp == 0 || ***vp != ')')
			bferr("Expression syntax");
		(*vp)++;
		return (putn(ccode));
	}
	if (eq(**vp, "{")) {
		register char **v;
		struct command faket;
		char *fakecom[2];
E 10
I 10
	if (*vp == 0 || **vp == 0 || ***vp != ')')
	    stderror(ERR_NAME | ERR_EXPRESSION);
	(*vp)++;
	return (putn(ccode));
    }
    if (eq(**vp, STRLbrace)) {
	register Char **v;
	struct command faket;
	Char   *fakecom[2];
E 10

D 8
		faket.t_dtyp = TCOM;
E 8
I 8
D 10
		faket.t_dtyp = NODE_COMMAND;
E 8
		faket.t_dflg = 0;
		faket.t_dcar = faket.t_dcdr = faket.t_dspr = (struct command *)0;
		faket.t_dcom = fakecom;
		fakecom[0] = "{ ... }";
		fakecom[1] = NOSTR;
		(*vp)++;
		v = *vp;
		for (;;) {
			if (!**vp)
				bferr("Missing }");
			if (eq(*(*vp)++, "}"))
				break;
		}
		if (ignore&IGNORE)
			return ("");
		psavejob();
		if (pfork(&faket, -1) == 0) {
			*--(*vp) = 0;
			evalav(v);
			exitstat();
		}
		pwait();
		prestjob();
E 10
I 10
	faket.t_dtyp = NODE_COMMAND;
	faket.t_dflg = 0;
D 12
	faket.t_dcar = faket.t_dcdr = faket.t_dspr =
	    (struct command *) 0;
E 12
I 12
	faket.t_dcar = faket.t_dcdr = faket.t_dspr = NULL;
E 12
	faket.t_dcom = fakecom;
	fakecom[0] = STRfakecom;
	fakecom[1] = NULL;
	(*vp)++;
	v = *vp;
	for (;;) {
	    if (!**vp)
		stderror(ERR_NAME | ERR_MISSING, '}');
	    if (eq(*(*vp)++, STRRbrace))
		break;
	}
	if (ignore & IGNORE)
	    return (Strsave(STRNULL));
	psavejob();
	if (pfork(&faket, -1) == 0) {
	    *--(*vp) = 0;
	    evalav(v);
	    exitstat();
	}
	pwait();
	prestjob();
E 10
#ifdef EDEBUG
D 10
		etraci("exp6 {} status", egetn(value("status")), vp);
E 10
I 10
	etraci("exp6 {} status", egetn(value(STRstatus)), vp);
E 10
#endif
D 10
		return (putn(egetn(value("status")) == 0));
	}
	if (isa(**vp, ANYOP))
		return ("");
	cp = *(*vp)++;
D 7
	if (*cp == '-' && any(cp[1], "erwxfdzo")) {
E 7
I 7
	if (*cp == '-' && index("erwxfdzo", cp[1])) {
E 7
		struct stat stb;
E 10
I 10
	return (putn(egetn(value(STRstatus)) == 0));
    }
    if (isa(**vp, ANYOP))
	return (Strsave(STRNULL));
    cp = *(*vp)++;
    if (*cp == '-' && any("erwxfdzopls", cp[1])) {
	struct stat stb;
E 10

D 10
		if (isa(**vp, ANYOP))
			bferr("Missing file name");
		dp = *(*vp)++;
		if (ignore&IGNORE)
			return ("");
		ep = globone(dp);
		switch (cp[1]) {
E 10
I 10
	if (cp[2] != '\0')
	    stderror(ERR_NAME | ERR_FILEINQ);
	/*
	 * Detect missing file names by checking for operator in the file name
	 * position.  However, if an operator name appears there, we must make
	 * sure that there's no file by that name (e.g., "/") before announcing
	 * an error.  Even this check isn't quite right, since it doesn't take
	 * globbing into account.
	 */
	if (isa(**vp, ANYOP) && stat(short2str(**vp), &stb))
	    stderror(ERR_NAME | ERR_FILENAME);
E 10

D 10
		case 'r':
			i = !access(ep, 4);
			break;
E 10
I 10
	dp = *(*vp)++;
	if (ignore & IGNORE)
	    return (Strsave(STRNULL));
	ep = globone(dp, G_ERROR);
	switch (cp[1]) {
E 10

D 10
		case 'w':
			i = !access(ep, 2);
			break;
E 10
I 10
	case 'r':
	    i = !access(short2str(ep), R_OK);
	    break;
E 10

D 10
		case 'x':
			i = !access(ep, 1);
			break;
E 10
I 10
	case 'w':
	    i = !access(short2str(ep), W_OK);
	    break;
E 10

D 10
		default:
			if (stat(ep, &stb)) {
				xfree(ep);
				return ("0");
			}
			switch (cp[1]) {
E 10
I 10
	case 'x':
	    i = !access(short2str(ep), X_OK);
	    break;
E 10

D 10
			case 'f':
				i = (stb.st_mode & S_IFMT) == S_IFREG;
				break;
E 10
I 10
	default:
	    if (
#ifdef S_IFLNK
		cp[1] == 'l' ? lstat(short2str(ep), &stb) :
#endif
		stat(short2str(ep), &stb)) {
		xfree((ptr_t) ep);
		return (Strsave(STR0));
	    }
	    switch (cp[1]) {
E 10

D 10
			case 'd':
				i = (stb.st_mode & S_IFMT) == S_IFDIR;
				break;
E 10
I 10
	    case 'f':
		i = S_ISREG(stb.st_mode);
		break;
E 10

D 10
			case 'z':
				i = stb.st_size == 0;
				break;
E 10
I 10
	    case 'd':
		i = S_ISDIR(stb.st_mode);
		break;
E 10

D 10
			case 'e':
				i = 1;
				break;
E 10
I 10
	    case 'p':
#ifdef S_ISFIFO
		i = S_ISFIFO(stb.st_mode);
#else
		i = 0;
#endif
		break;
E 10

D 10
			case 'o':
				i = stb.st_uid == uid;
				break;
			}
		}
#ifdef EDEBUG
		etraci("exp6 -? i", i, vp);
E 10
I 10
	    case 'l':
#ifdef S_ISLNK
		i = S_ISLNK(stb.st_mode);
#else
		i = 0;
E 10
#endif
D 10
		xfree(ep);
		return (putn(i));
E 10
I 10
		break;

	    case 's':
#ifdef S_ISSOCK
		i = S_ISSOCK(stb.st_mode);
#else
		i = 0;
#endif
		break;

	    case 'z':
		i = stb.st_size == 0;
		break;

	    case 'e':
		i = 1;
		break;

	    case 'o':
		i = stb.st_uid == uid;
		break;
	    }
E 10
	}
#ifdef EDEBUG
D 10
	etracc("exp6 default", cp, vp);
E 10
I 10
	etraci("exp6 -? i", i, vp);
E 10
#endif
D 6
	return (ignore&NOGLOB ? cp : globone(cp));
E 6
I 6
D 10
	return (ignore&NOGLOB ? savestr(cp) : globone(cp));
E 10
I 10
	xfree((ptr_t) ep);
	return (putn(i));
    }
#ifdef EDEBUG
    etracc("exp6 default", cp, vp);
#endif
    return (ignore & NOGLOB ? Strsave(cp) : globone(cp, G_ERROR));
E 10
E 6
}

I 10
static void
E 10
evalav(v)
D 10
	register char **v;
E 10
I 10
    register Char **v;
E 10
{
D 10
	struct wordent paraml;
	register struct wordent *hp = &paraml;
	struct command *t;
	register struct wordent *wdp = hp;
	
	set("status", "0");
	hp->prev = hp->next = hp;
	hp->word = "";
	while (*v) {
		register struct wordent *new = (struct wordent *) calloc(1, sizeof *wdp);
E 10
I 10
    struct wordent paraml1;
    register struct wordent *hp = &paraml1;
    struct command *t;
    register struct wordent *wdp = hp;
E 10

D 10
		new->prev = wdp;
		new->next = hp;
		wdp->next = new;
		wdp = new;
		wdp->word = savestr(*v++);
	}
	hp->prev = wdp;
	alias(&paraml);
	t = syntax(paraml.next, &paraml, 0);
	if (err)
		error(err);
	execute(t, -1);
	freelex(&paraml), freesyn(t);
E 10
I 10
    set(STRstatus, Strsave(STR0));
    hp->prev = hp->next = hp;
    hp->word = STRNULL;
    while (*v) {
	register struct wordent *new =
	(struct wordent *) xcalloc(1, sizeof *wdp);

	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	wdp = new;
	wdp->word = Strsave(*v++);
    }
    hp->prev = wdp;
    alias(&paraml1);
    t = syntax(paraml1.next, &paraml1, 0);
    if (seterr)
	stderror(ERR_OLD);
D 11
    execute(t, -1);
E 11
I 11
    execute(t, -1, NULL, NULL);
E 11
    freelex(&paraml1), freesyn(t);
E 10
}

I 10
static int
E 10
isa(cp, what)
D 10
	register char *cp;
	register int what;
E 10
I 10
    register Char *cp;
    register int what;
E 10
{
D 10

	if (cp == 0)
		return ((what & RESTOP) != 0);
	if (cp[1] == 0) {
D 2
		if ((what & ADDOP) && any(cp[0], "+-"))
E 2
I 2
		if (what & ADDOP && (*cp == '+' || *cp == '-'))
E 2
			return (1);
D 2
		if ((what & MULOP) && any(cp[0], "*/%"))
E 2
I 2
		if (what & MULOP && (*cp == '*' || *cp == '/' || *cp == '%'))
E 2
			return (1);
D 2
		if ((what & RESTOP) && any(cp[0], "()!~^"))
E 2
I 2
		if (what & RESTOP && (*cp == '(' || *cp == ')' || *cp == '!' ||
				      *cp == '~' || *cp == '^' || *cp == '"'))
E 2
			return (1);
I 2
	} else if (cp[2] == 0) {
		if (what & RESTOP) {
			if (cp[0] == '|' && cp[1] == '&')
				return (1);
			if (cp[0] == '<' && cp[1] == '<')
				return (1);
			if (cp[0] == '>' && cp[1] == '>')
				return (1);
		}
		if (what & EQOP) {
			if (cp[0] == '=') {
				if (cp[1] == '=')
					return (EQEQ);
				if (cp[1] == '~')
					return (EQMATCH);
			} else if (cp[0] == '!') {
				if (cp[1] == '=')
					return (NOTEQ);
				if (cp[1] == '~')
					return (NOTEQMATCH);
			}
		}
E 10
I 10
    if (cp == 0)
	return ((what & RESTOP) != 0);
    if (cp[1] == 0) {
	if (what & ADDOP && (*cp == '+' || *cp == '-'))
	    return (1);
	if (what & MULOP && (*cp == '*' || *cp == '/' || *cp == '%'))
	    return (1);
	if (what & RESTOP && (*cp == '(' || *cp == ')' || *cp == '!' ||
			      *cp == '~' || *cp == '^' || *cp == '"'))
	    return (1);
    }
    else if (cp[2] == 0) {
	if (what & RESTOP) {
	    if (cp[0] == '|' && cp[1] == '&')
		return (1);
	    if (cp[0] == '<' && cp[1] == '<')
		return (1);
	    if (cp[0] == '>' && cp[1] == '>')
		return (1);
E 10
E 2
	}
D 2
	if ((what & RESTOP) && (any(cp[0], "|&") || eq(cp, "<<") || eq(cp, ">>")))
		return (1);
	if (what & EQOP) {
		if (eq(cp, "=="))
			return (EQEQ);
		if (eq(cp, "!="))
			return (NOTEQ);
		if (eq(cp, "=~"))
			return (EQMATCH);
		if (eq(cp, "!~"))
			return (NOTEQMATCH);
E 2
I 2
D 10
	if (what & RELOP) {
		if (*cp == '<')
			return (LSS);
		if (*cp == '>')
			return (GTR);
E 10
I 10
	if (what & EQOP) {
	    if (cp[0] == '=') {
		if (cp[1] == '=')
		    return (EQEQ);
		if (cp[1] == '~')
		    return (EQMATCH);
	    }
	    else if (cp[0] == '!') {
		if (cp[1] == '=')
		    return (NOTEQ);
		if (cp[1] == '~')
		    return (NOTEQMATCH);
	    }
E 10
E 2
	}
D 2
	if (!(what & RELOP))
		return (0);
	if (*cp == '<')
		return (LSS);
	if (*cp == '>')
		return (GTR);
E 2
D 10
	return (0);
E 10
I 10
    }
    if (what & RELOP) {
	if (*cp == '<')
	    return (LSS);
	if (*cp == '>')
	    return (GTR);
    }
    return (0);
E 10
}

I 10
static int
E 10
egetn(cp)
D 10
	register char *cp;
E 10
I 10
    register Char *cp;
E 10
{
D 10

	if (*cp && *cp != '-' && !digit(*cp))
		bferr("Expression syntax");
	return (getn(cp));
E 10
I 10
    if (*cp && *cp != '-' && !Isdigit(*cp))
	stderror(ERR_NAME | ERR_EXPRESSION);
    return (getn(cp));
E 10
}

/* Phew! */

#ifdef EDEBUG
I 10
static void
E 10
etraci(str, i, vp)
D 10
	char *str;
	int i;
	char ***vp;
E 10
I 10
    char   *str;
    int     i;
    Char ***vp;
E 10
{
D 10

	printf("%s=%d\t", str, i);
	blkpr(*vp);
	printf("\n");
E 10
I 10
D 15
    xprintf("%s=%d\t", str, i);
    blkpr(*vp);
    xprintf("\n");
E 15
I 15
    (void) fprintf(csherr, "%s=%d\t", str, i);
    blkpr(csherr, *vp);
    (void) fprintf(csherr, "\n");
E 15
E 10
}
D 10

E 10
I 10
static void
E 10
etracc(str, cp, vp)
D 10
	char *str, *cp;
	char ***vp;
E 10
I 10
    char   *str;
    Char   *cp;
    Char ***vp;
E 10
{
D 10

	printf("%s=%s\t", str, cp);
	blkpr(*vp);
	printf("\n");
E 10
I 10
D 15
    xprintf("%s=%s\t", str, cp);
    blkpr(*vp);
    xprintf("\n");
E 15
I 15
D 18
    (void) fprintf(csherr, "%s=%s\t", str, cp);
E 18
I 18
    (void) fprintf(csherr, "%s=%s\t", str, vis_str(cp));
E 18
    blkpr(csherr, *vp);
    (void) fprintf(csherr, "\n");
E 15
E 10
}
#endif
E 1
