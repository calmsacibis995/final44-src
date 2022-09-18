h02705
s 00006/00002/00816
d D 8.2 95/03/22 14:12:30 christos 26 25
c Changes from Charles Hannum (mycroft@netbsd.org) to use POSIX signals
e
s 00002/00002/00816
d D 8.1 93/05/31 16:42:58 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00810
d D 5.20 93/05/22 19:06:49 christos 24 23
c Fixed gcc -Wall warnings
e
s 00002/00002/00816
d D 5.19 93/03/30 13:55:45 christos 23 22
c Changed the -21... to 0x80... to avoid integer overflow warnings
e
s 00004/00002/00814
d D 5.18 92/05/15 00:09:04 christos 22 21
c su path warning and got rid of the last printf(string);
e
s 00001/00001/00815
d D 5.17 91/11/06 16:09:55 christos 21 20
c Added support for displaying non-printable characters
e
s 00004/00003/00812
d D 5.16 91/10/28 21:28:10 leres 20 19
c Fix gcc "bodyless for/while" warnings.
e
s 00002/00002/00813
d D 5.15 91/09/06 01:25:49 christos 19 18
c Replaced exp with expr to avoild libm conflict
e
s 00003/00000/00812
d D 5.14 91/07/22 11:47:49 christos 18 17
c no short strings bug fix
e
s 00026/00017/00786
d D 5.13 91/07/19 17:31:27 christos 17 16
c stdio based version; brace glob fix; builtin prototypes
e
s 00001/00001/00802
d D 5.12 91/06/14 14:35:52 christos 16 15
c setNS needed to save the argument to set(). Otherwise we would free memory we did not allocate
e
s 00006/00000/00797
d D 5.11 91/06/08 17:09:06 christos 15 14
c More prototype fixes, Removed TERMIOS define
e
s 00003/00001/00794
d D 5.10 91/06/08 12:20:38 bostic 14 13
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00001/00001/00794
d D 5.9 91/06/07 21:05:48 christos 13 12
c prototype typo fixes
e
s 00014/00011/00781
d D 5.8 91/06/07 20:57:41 christos 12 11
c static function prototypes
e
s 00002/00001/00790
d D 5.7 91/06/07 11:13:43 bostic 11 10
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00610/00521/00181
d D 5.6 91/06/04 13:32:00 bostic 10 9
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/00697
d D 5.5 91/04/04 18:17:58 bostic 9 8
c new copyright; att/bsd/shared
e
s 00005/00005/00696
d D 5.4 91/03/14 12:33:38 bostic 8 7
c any -> index (use the faster library routine) 
c use the library globbing routines instead of rolling our own
e
s 00004/00004/00697
d D 5.3 88/05/19 15:39:07 bostic 7 6
c install C version of _doprnt
e
s 00003/00003/00698
d D 5.2 85/06/06 13:10:29 edward 6 5
c cleaning up after bozos
e
s 00008/00002/00693
d D 5.1 85/06/04 11:08:01 dist 5 4
c Add copyright
e
s 00260/00120/00435
d D 4.4 84/12/13 14:41:09 edward 4 3
c performance
e
s 00001/00001/00554
d D 4.3 84/08/31 09:31:40 ralph 3 2
c use new signal calls instead of compatibility routines.
e
s 00003/00003/00552
d D 4.2 83/11/02 14:51:58 layer 2 1
c don't allow "@ 1 = 1", but do allow "@ t1 = 1"
e
s 00555/00000/00000
d D 4.1 80/10/09 12:41:53 bill 1 0
c date and time created 80/10/09 12:41:53 by bill
e
u
U
t
T
I 5
D 9
/*
 * Copyright (c) 1980 Regents of the University of California.
D 6
 * All rights reserved.  The Berkeley software License Agreement
E 6
I 6
 * All rights reserved.  The Berkeley Software License Agreement
E 6
 * specifies the terms and conditions for redistribution.
E 9
I 9
/*-
D 25
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
 * %sccs.include.redist.c%
E 9
 */

E 5
I 1
D 4
static	char *sccsid = "%Z%%M% %I% %G%";
E 4
I 4
#ifndef lint
D 5
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 5
I 5
D 6
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 6
I 6
D 8
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 8
E 6
E 5
E 4

I 14
#include <sys/types.h>
#include <stdlib.h>
I 18
#ifndef SHORT_STRINGS
#include <string.h>
#endif /* SHORT_STRINGS */
E 18
I 15
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 15
E 14
D 11
#include "sh.h"
E 11
I 11
#include "csh.h"
#include "extern.h"
E 11

I 10
D 12
static Char *getinx();
static void asx();
static struct varent *getvx();
static Char *xset();
static Char *operate();
static void putn1();
static struct varent *madrof();
static void unsetv1();
static void exportpath();
static void balance();
E 12
I 12
static Char	*getinx __P((Char *, int *));
static void	 asx __P((Char *, int, Char *));
D 20
static struct varent 
E 20
I 20
static struct varent
E 20
D 13
		*getvx __P((char *, int));
E 13
I 13
		*getvx __P((Char *, int));
E 13
static Char	*xset __P((Char *, Char ***));
static Char	*operate __P((int, Char *, Char *));
static void	 putn1 __P((int));
D 20
static struct varent 
E 20
I 20
static struct varent
E 20
		*madrof __P((Char *, struct varent *));
static void	 unsetv1 __P((struct varent *));
static void	 exportpath __P((Char **));
static void	 balance __P((struct varent *, int, int));
E 12


E 10
/*
 * C Shell
 */

I 10
void
E 10
D 17
doset(v)
D 10
	register char **v;
E 10
I 10
    register Char **v;
E 17
I 17
/*ARGSUSED*/
doset(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register char *p;
	char *vp, op;
	char **vecp;
	bool hadsub;
	int subscr;
E 10
I 10
    register Char *p;
    Char   *vp, op;
    Char  **vecp;
    bool    hadsub;
    int     subscr;
E 10

D 10
	v++;
	p = *v++;
	if (p == 0) {
		prvars();
		return;
E 10
I 10
    v++;
    p = *v++;
    if (p == 0) {
	prvars();
	return;
    }
    do {
	hadsub = 0;
	vp = p;
	if (letter(*p))
	    for (; alnum(*p); p++)
		continue;
	if (vp == p || !letter(*vp))
	    stderror(ERR_NAME | ERR_VARBEGIN);
	if ((p - vp) > MAXVARLEN) {
	    stderror(ERR_NAME | ERR_VARTOOLONG);
	    return;
E 10
	}
D 10
	do {
		hadsub = 0;
		for (vp = p; alnum(*p); p++)
			continue;
D 2
		if (vp == p)
E 2
I 2
		if (vp == p || !letter(*vp))
E 2
			goto setsyn;
		if (*p == '[') {
			hadsub++;
			p = getinx(p, &subscr);
		}
		if (op = *p) {
			*p++ = 0;
			if (*p == 0 && *v && **v == '(')
				p = *v++;
		} else if (*v && eq(*v, "=")) {
			op = '=', v++;
			if (*v)
				p = *v++;
		}
		if (op && op != '=')
setsyn:
			bferr("Syntax error");
		if (eq(p, "(")) {
			register char **e = v;
E 10
I 10
	if (*p == '[') {
	    hadsub++;
	    p = getinx(p, &subscr);
	}
D 24
	if (op = *p) {
E 24
I 24
	if ((op = *p) != '\0') {
E 24
	    *p++ = 0;
	    if (*p == 0 && *v && **v == '(')
		p = *v++;
	}
	else if (*v && eq(*v, STRequal)) {
	    op = '=', v++;
	    if (*v)
		p = *v++;
	}
	if (op && op != '=')
	    stderror(ERR_NAME | ERR_SYNTAX);
	if (eq(p, STRLparen)) {
	    register Char **e = v;
E 10

D 10
			if (hadsub)
				goto setsyn;
			for (;;) {
				if (!*e)
					bferr("Missing )");
				if (**e == ')')
					break;
				e++;
			}
			p = *e;
			*e = 0;
			vecp = saveblk(v);
			set1(vp, vecp, &shvhed);
			*e = p;
			v = e + 1;
		} else if (hadsub)
			asx(vp, subscr, savestr(p));
		else
			set(vp, savestr(p));
		if (eq(vp, "path")) {
			exportpath(adrof("path")->vec);
			dohash();
		} else if (eq(vp, "histchars")) {
			register char *p = value("histchars");
E 10
I 10
	    if (hadsub)
		stderror(ERR_NAME | ERR_SYNTAX);
	    for (;;) {
		if (!*e)
		    stderror(ERR_NAME | ERR_MISSING, ')');
		if (**e == ')')
		    break;
		e++;
	    }
	    p = *e;
	    *e = 0;
	    vecp = saveblk(v);
	    set1(vp, vecp, &shvhed);
	    *e = p;
	    v = e + 1;
	}
	else if (hadsub)
	    asx(vp, subscr, Strsave(p));
	else
	    set(vp, Strsave(p));
	if (eq(vp, STRpath)) {
	    exportpath(adrof(STRpath)->vec);
D 17
	    dohash();
E 17
I 17
	    dohash(NULL, NULL);
E 17
	}
	else if (eq(vp, STRhistchars)) {
	    register Char *pn = value(STRhistchars);
E 10

D 10
			HIST = *p++;
			HISTSUB = *p;
		} else if (eq(vp, "user"))
			setenv("USER", value(vp));
		else if (eq(vp, "term"))
			setenv("TERM", value(vp));
		else if (eq(vp, "home"))
			setenv("HOME", value(vp));
E 10
I 10
	    HIST = *pn++;
	    HISTSUB = *pn;
	}
	else if (eq(vp, STRuser)) {
	    Setenv(STRUSER, value(vp));
	    Setenv(STRLOGNAME, value(vp));
	}
	else if (eq(vp, STRwordchars)) {
	    word_chars = value(vp);
	}
	else if (eq(vp, STRterm))
	    Setenv(STRTERM, value(vp));
	else if (eq(vp, STRhome)) {
	    register Char *cp;

	    cp = Strsave(value(vp));	/* get the old value back */

	    /*
	     * convert to cononical pathname (possibly resolving symlinks)
	     */
	    cp = dcanon(cp, cp);

	    set(vp, Strsave(cp));	/* have to save the new val */

	    /* and now mirror home with HOME */
	    Setenv(STRHOME, cp);
	    /* fix directory stack for new tilde home */
	    dtilde();
	    xfree((ptr_t) cp);
	}
E 10
I 4
#ifdef FILEC
D 10
		else if (eq(vp, "filec"))
			filec = 1;
E 10
I 10
	else if (eq(vp, STRfilec))
	    filec = 1;
E 10
#endif
E 4
D 10
	} while (p = *v++);
E 10
I 10
D 24
    } while (p = *v++);
E 24
I 24
    } while ((p = *v++) != NULL);
E 24
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
getinx(cp, ip)
D 10
	register char *cp;
	register int *ip;
E 10
I 10
    register Char *cp;
    register int *ip;
E 10
{

D 10
	*ip = 0;
	*cp++ = 0;
	while (*cp && digit(*cp))
		*ip = *ip * 10 + *cp++ - '0';
	if (*cp++ != ']')
		bferr("Subscript error");
	return (cp);
E 10
I 10
    *ip = 0;
    *cp++ = 0;
    while (*cp && Isdigit(*cp))
	*ip = *ip * 10 + *cp++ - '0';
    if (*cp++ != ']')
	stderror(ERR_NAME | ERR_SUBSCRIPT);
    return (cp);
E 10
}

I 10
static void
E 10
asx(vp, subscr, p)
D 10
	char *vp;
	int subscr;
	char *p;
E 10
I 10
    Char   *vp;
    int     subscr;
    Char   *p;
E 10
{
D 10
	register struct varent *v = getvx(vp, subscr);
E 10
I 10
    register struct varent *v = getvx(vp, subscr);
E 10

D 10
	xfree(v->vec[subscr - 1]);
	v->vec[subscr - 1] = globone(p);
E 10
I 10
    xfree((ptr_t) v->vec[subscr - 1]);
    v->vec[subscr - 1] = globone(p, G_APPEND);
E 10
}

D 10
struct varent *
E 10
I 10
static struct varent *
E 10
getvx(vp, subscr)
I 4
D 10
	char *vp;
E 10
I 10
    Char   *vp;
    int     subscr;
E 10
E 4
{
D 10
	register struct varent *v = adrof(vp);
E 10
I 10
    register struct varent *v = adrof(vp);
E 10

D 10
	if (v == 0)
		udvar(vp);
	if (subscr < 1 || subscr > blklen(v->vec))
		bferr("Subscript out of range");
	return (v);
E 10
I 10
    if (v == 0)
	udvar(vp);
    if (subscr < 1 || subscr > blklen(v->vec))
	stderror(ERR_NAME | ERR_RANGE);
    return (v);
E 10
}

D 10
char	plusplus[2] = { '1', 0 };

E 10
I 10
void
E 10
D 4

E 4
D 17
dolet(v)
D 10
	char **v;
E 10
I 10
    Char  **v;
E 17
I 17
/*ARGSUSED*/
dolet(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register char *p;
	char *vp, c, op;
	bool hadsub;
	int subscr;
E 10
I 10
    register Char *p;
    Char   *vp, c, op;
    bool    hadsub;
    int     subscr;
E 10

D 10
	v++;
	p = *v++;
	if (p == 0) {
		prvars();
		return;
E 10
I 10
    v++;
    p = *v++;
    if (p == 0) {
	prvars();
	return;
    }
    do {
	hadsub = 0;
	vp = p;
	if (letter(*p))
	    for (; alnum(*p); p++)
		continue;
	if (vp == p || !letter(*vp))
	    stderror(ERR_NAME | ERR_VARBEGIN);
	if ((p - vp) > MAXVARLEN)
	    stderror(ERR_NAME | ERR_VARTOOLONG);
	if (*p == '[') {
	    hadsub++;
	    p = getinx(p, &subscr);
E 10
	}
D 10
	do {
		hadsub = 0;
D 2
		for (vp = p; letter(*p); p++)
E 2
I 2
		for (vp = p; alnum(*p); p++)
E 2
			continue;
D 2
		if (vp == p)
E 2
I 2
		if (vp == p || !letter(*vp))
E 2
			goto letsyn;
		if (*p == '[') {
			hadsub++;
			p = getinx(p, &subscr);
		}
		if (*p == 0 && *v)
			p = *v++;
		if (op = *p)
			*p++ = 0;
		else
			goto letsyn;
		vp = savestr(vp);
		if (op == '=') {
			c = '=';
			p = xset(p, &v);
		} else {
			c = *p++;
D 8
			if (any(c, "+-")) {
E 8
I 8
			if (index("+-", c)) {
E 8
				if (c != op || *p)
					goto letsyn;
				p = plusplus;
			} else {
D 8
				if (any(op, "<>")) {
E 8
I 8
				if (index("<>", op)) {
E 8
					if (c != op)
						goto letsyn;
					c = *p++;
letsyn:
					bferr("Syntax error");
				}
				if (c != '=')
					goto letsyn;
				p = xset(p, &v);
			}
		}
		if (op == '=')
			if (hadsub)
				asx(vp, subscr, p);
			else
				set(vp, p);
		else
			if (hadsub)
#ifndef V6
				/* avoid bug in vax CC */
				{
					struct varent *gv = getvx(vp, subscr);
E 10
I 10
	if (*p == 0 && *v)
	    p = *v++;
D 24
	if (op = *p)
E 24
I 24
	if ((op = *p) != '\0')
E 24
	    *p++ = 0;
	else
	    stderror(ERR_NAME | ERR_ASSIGN);
E 10

D 10
					asx(vp, subscr, operate(op, gv->vec[subscr - 1], p));
				}
#else
				asx(vp, subscr, operate(op, getvx(vp, subscr)->vec[subscr - 1], p));
#endif
			else
				set(vp, operate(op, value(vp), p));
D 4
		if (strcmp(vp, "path") == 0)
E 4
I 4
		if (eq(vp, "path")) {
			exportpath(adrof("path")->vec);
E 4
			dohash();
E 10
I 10
	if (*p == '\0' && *v == NULL)
	    stderror(ERR_NAME | ERR_ASSIGN);

	vp = Strsave(vp);
	if (op == '=') {
	    c = '=';
	    p = xset(p, &v);
	}
	else {
	    c = *p++;
	    if (any("+-", c)) {
		if (c != op || *p)
		    stderror(ERR_NAME | ERR_UNKNOWNOP);
		p = Strsave(STR1);
	    }
	    else {
		if (any("<>", op)) {
		    if (c != op)
			stderror(ERR_NAME | ERR_UNKNOWNOP);
		    c = *p++;
		    stderror(ERR_NAME | ERR_SYNTAX);
E 10
D 4
		xfree(vp);
E 4
I 4
		}
D 10
		XFREE(vp)
E 10
E 4
		if (c != '=')
D 4
			xfree(p);
E 4
I 4
D 10
			XFREE(p)
E 4
	} while (p = *v++);
E 10
I 10
		    stderror(ERR_NAME | ERR_UNKNOWNOP);
		p = xset(p, &v);
	    }
	}
	if (op == '=')
	    if (hadsub)
		asx(vp, subscr, p);
	    else
		set(vp, p);
	else if (hadsub) {
	    struct varent *gv = getvx(vp, subscr);

	    asx(vp, subscr, operate(op, gv->vec[subscr - 1], p));
	}
	else
	    set(vp, operate(op, value(vp), p));
	if (eq(vp, STRpath)) {
	    exportpath(adrof(STRpath)->vec);
D 17
	    dohash();
E 17
I 17
	    dohash(NULL, NULL);
E 17
	}
	xfree((ptr_t) vp);
	if (c != '=')
	    xfree((ptr_t) p);
D 24
    } while (p = *v++);
E 24
I 24
    } while ((p = *v++) != NULL);
E 24
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
xset(cp, vp)
D 10
	char *cp, ***vp;
E 10
I 10
    Char   *cp, ***vp;
E 10
{
D 10
	register char *dp;
E 10
I 10
    register Char *dp;
E 10

D 10
	if (*cp) {
		dp = savestr(cp);
		--(*vp);
		xfree(**vp);
		**vp = dp;
	}
	return (putn(exp(vp)));
E 10
I 10
    if (*cp) {
	dp = Strsave(cp);
	--(*vp);
	xfree((ptr_t) ** vp);
	**vp = dp;
    }
D 19
    return (putn(exp(vp)));
E 19
I 19
    return (putn(expr(vp)));
E 19
E 10
}

D 10
char *
E 10
I 10
static Char *
E 10
operate(op, vp, p)
D 10
	char op, *vp, *p;
E 10
I 10
D 12
    Char    op, *vp, *p;
E 12
I 12
    int    op;
    Char  *vp, *p;
E 12
E 10
{
D 10
	char opr[2];
	char *vec[5];
	register char **v = vec;
	char **vecp = v;
	register int i;
E 10
I 10
    Char    opr[2];
    Char   *vec[5];
    register Char **v = vec;
    Char  **vecp = v;
    register int i;
E 10

D 10
	if (op != '=') {
		if (*vp)
			*v++ = vp;
		opr[0] = op;
		opr[1] = 0;
		*v++ = opr;
		if (op == '<' || op == '>')
			*v++ = opr;
	}
	*v++ = p;
	*v++ = 0;
	i = exp(&vecp);
	if (*vecp)
		bferr("Expression syntax");
	return (putn(i));
E 10
I 10
    if (op != '=') {
	if (*vp)
	    *v++ = vp;
	opr[0] = op;
	opr[1] = 0;
	*v++ = opr;
	if (op == '<' || op == '>')
	    *v++ = opr;
    }
    *v++ = p;
    *v++ = 0;
D 19
    i = exp(&vecp);
E 19
I 19
    i = expr(&vecp);
E 19
    if (*vecp)
	stderror(ERR_NAME | ERR_EXPRESSION);
    return (putn(i));
E 10
}

D 4
onlyread(cp)
	char *cp;
{
	extern char end[];

	return (cp < end);
}

xfree(cp)
	char *cp;
{
	extern char end[];

	if (cp >= end && cp < (char *) &cp)
D 3
		cfree(cp);
E 3
I 3
		free(cp);
E 3
}

char *
savestr(s)
	register char *s;
{
	register char *n;

	if (s == 0)
		s = "";
	strcpy(n = calloc(1, strlen(s) + 1), s);
	return (n);
}

E 4
D 10
static	char *putp;
 
char *
E 10
I 10
static Char *putp;

Char   *
E 10
putn(n)
D 10
	register int n;
E 10
I 10
    register int n;
E 10
{
D 10
	static char number[15];
E 10
I 10
    int     num;
    static Char number[15];
E 10

D 10
	putp = number;
	if (n < 0) {
		n = -n;
		*putp++ = '-';
	}
	if (sizeof (int) == 2 && n == -32768) {
		*putp++ = '3';
		n = 2768;
E 10
I 10
    putp = number;
    if (n < 0) {
	n = -n;
	*putp++ = '-';
    }
    num = 2;			/* confuse lint */
D 23
    if (sizeof(int) == num && n == -32768) {
E 23
I 23
    if (sizeof(int) == num && ((unsigned int) n) == 0x8000) {
E 23
	*putp++ = '3';
	n = 2768;
E 10
#ifdef pdp11
D 10
	}
E 10
I 10
    }
E 10
#else
D 10
	} else if (sizeof (int) == 4 && n == -2147483648) {
		*putp++ = '2';
		n = 147483648;
E 10
I 10
    }
    else {
	num = 4;		/* confuse lint */
D 23
	if (sizeof(int) == num && n == -2147483648) {
E 23
I 23
	if (sizeof(int) == num && ((unsigned int) n) == 0x80000000) {
E 23
	    *putp++ = '2';
	    n = 147483648;
E 10
	}
I 10
    }
E 10
#endif
D 10
	putn1(n);
	*putp = 0;
	return (savestr(number));
E 10
I 10
    putn1(n);
    *putp = 0;
    return (Strsave(number));
E 10
}

I 10
static void
E 10
putn1(n)
D 10
	register int n;
E 10
I 10
    register int n;
E 10
{
D 10
	if (n > 9)
		putn1(n / 10);
	*putp++ = n % 10 + '0';
E 10
I 10
    if (n > 9)
	putn1(n / 10);
    *putp++ = n % 10 + '0';
E 10
}

I 10
int
E 10
getn(cp)
D 10
	register char *cp;
E 10
I 10
    register Char *cp;
E 10
{
D 10
	register int n;
	int sign;
E 10
I 10
    register int n;
    int     sign;
E 10

D 10
	sign = 0;
	if (cp[0] == '+' && cp[1])
		cp++;
	if (*cp == '-') {
		sign++;
		cp++;
		if (!digit(*cp))
			goto badnum;
	}
	n = 0;
	while (digit(*cp))
		n = n * 10 + *cp++ - '0';
	if (*cp)
		goto badnum;
	return (sign ? -n : n);
badnum:
	bferr("Badly formed number");
	return (0);
E 10
I 10
    sign = 0;
    if (cp[0] == '+' && cp[1])
	cp++;
    if (*cp == '-') {
	sign++;
	cp++;
	if (!Isdigit(*cp))
	    stderror(ERR_NAME | ERR_BADNUM);
    }
    n = 0;
    while (Isdigit(*cp))
	n = n * 10 + *cp++ - '0';
    if (*cp)
	stderror(ERR_NAME | ERR_BADNUM);
    return (sign ? -n : n);
E 10
}

D 10
char *
E 10
I 10
Char   *
E 10
D 4
value(var)
	char *var;
{

	return (value1(var, &shvhed));
}

char *
E 4
value1(var, head)
D 10
	char *var;
	struct varent *head;
E 10
I 10
    Char   *var;
    struct varent *head;
E 10
{
D 10
	register struct varent *vp;
E 10
I 10
    register struct varent *vp;
E 10

D 10
	vp = adrof1(var, head);
	return (vp == 0 || vp->vec[0] == 0 ? "" : vp->vec[0]);
E 10
I 10
    vp = adrof1(var, head);
    return (vp == 0 || vp->vec[0] == 0 ? STRNULL : vp->vec[0]);
E 10
}

D 4
static	struct varent *shprev;

E 4
D 10
struct varent *
E 10
I 10
static struct varent *
E 10
D 4
adrof(var)
	char *var;
{

	return (adrof1(var, &shvhed));
}

struct varent *
madrof(pat, head)
E 4
I 4
madrof(pat, vp)
E 4
D 10
	char *pat;
D 4
	struct varent *head;
{
E 4
	register struct varent *vp;
E 10
I 10
    Char   *pat;
    register struct varent *vp;
E 10
I 4
{
D 10
	register struct varent *vp1;
E 10
I 10
    register struct varent *vp1;
E 10
E 4

D 4
	shprev = head;
	for (vp = shprev->link; vp != 0; vp = vp->link) {
		if (Gmatch(vp->name, pat))
			return (vp);
		shprev = vp;
E 4
I 4
D 10
	for (; vp; vp = vp->v_right) {
		if (vp->v_left && (vp1 = madrof(pat, vp->v_left)))
			return vp1;
		if (Gmatch(vp->v_name, pat))
			return vp;
E 4
	}
D 4
	return (0);
E 4
I 4
	return vp;
E 10
I 10
    for (; vp; vp = vp->v_right) {
	if (vp->v_left && (vp1 = madrof(pat, vp->v_left)))
	    return vp1;
	if (Gmatch(vp->v_name, pat))
	    return vp;
    }
    return vp;
E 10
E 4
}

struct varent *
D 4
adrof1(var, head)
	char *var;
	struct varent *head;
E 4
I 4
adrof1(name, v)
D 10
	register char *name;
	register struct varent *v;
E 10
I 10
    register Char *name;
    register struct varent *v;
E 10
E 4
{
D 4
	register struct varent *vp;
	int cmp;
E 4
I 4
D 10
	register cmp;
E 10
I 10
    register cmp;
E 10
E 4

D 4
	shprev = head;
	for (vp = shprev->link; vp != 0; vp = vp->link) {
		cmp = strcmp(vp->name, var);
		if (cmp == 0)
			return (vp);
		else if (cmp > 0)
			return (0);
		shprev = vp;
	}
	return (0);
E 4
I 4
D 10
	v = v->v_left;
	while (v && ((cmp = *name - *v->v_name) ||
		     (cmp = strcmp(name, v->v_name))))
		if (cmp < 0)
			v = v->v_left;
		else
			v = v->v_right;
	return v;
E 10
I 10
    v = v->v_left;
    while (v && ((cmp = *name - *v->v_name) ||
		 (cmp = Strcmp(name, v->v_name))))
	if (cmp < 0)
	    v = v->v_left;
	else
	    v = v->v_right;
    return v;
E 10
E 4
}

/*
 * The caller is responsible for putting value in a safe place
 */
I 10
void
E 10
D 4
set(var, value)
	char *var, *value;
E 4
I 4
set(var, val)
D 10
	char *var, *val;
E 10
I 10
    Char   *var, *val;
E 10
E 4
{
D 4
	register char **vec = (char **) calloc(2, sizeof (char **));
E 4
I 4
D 10
	register char **vec = (char **) xalloc(2 * sizeof (char **));
E 10
I 10
    register Char **vec = (Char **) xmalloc((size_t) (2 * sizeof(Char **)));
E 10
E 4

D 4
	vec[0] = onlyread(value) ? savestr(value) : value;
E 4
I 4
D 10
	vec[0] = onlyread(val) ? savestr(val) : val;
	vec[1] = 0;
E 4
	set1(var, vec, &shvhed);
E 10
I 10
    vec[0] = val;
    vec[1] = 0;
    set1(var, vec, &shvhed);
E 10
}

I 10
void
E 10
set1(var, vec, head)
D 10
	char *var, **vec;
	struct varent *head;
E 10
I 10
    Char   *var, **vec;
    struct varent *head;
E 10
{
D 4

E 4
D 10
	register char **oldv = vec;
E 10
I 10
    register Char **oldv = vec;
E 10

D 4
	gflag = 0; rscan(oldv, tglob);
E 4
I 4
D 10
	gflag = 0; tglob(oldv);
E 4
	if (gflag) {
D 8
		vec = glob(oldv);
E 8
I 8
		vec = globall(oldv);
E 8
		if (vec == 0) {
			bferr("No match");
			blkfree(oldv);
			return;
		}
		blkfree(oldv);
		gargv = 0;
E 10
I 10
    gflag = 0;
    tglob(oldv);
    if (gflag) {
	vec = globall(oldv);
	if (vec == 0) {
	    blkfree(oldv);
	    stderror(ERR_NAME | ERR_NOMATCH);
	    return;
E 10
	}
D 10
	setq(var, vec, head);
E 10
I 10
	blkfree(oldv);
	gargv = 0;
    }
    setq(var, vec, head);
E 10
}

I 10

void
E 10
D 4
setq(var, vec, head)
	char *var, **vec;
	struct varent *head;
E 4
I 4
setq(name, vec, p)
D 10
	char *name, **vec;
	register struct varent *p;
E 10
I 10
    Char   *name, **vec;
    register struct varent *p;
E 10
E 4
{
D 4
	register struct varent *vp;
E 4
I 4
D 10
	register struct varent *c;
	register f;
E 10
I 10
    register struct varent *c;
    register f;
E 10
E 4

D 4
	vp = adrof1(var, head);
	if (vp == 0) {
		vp = (struct varent *) calloc(1, sizeof *vp);
		vp->name = savestr(var);
		vp->link = shprev->link;
		shprev->link = vp;
E 4
I 4
D 10
	f = 0;			/* tree hangs off the header's left link */
	while (c = p->v_link[f]) {
		if ((f = *name - *c->v_name) == 0 &&
		    (f = strcmp(name, c->v_name)) == 0) {
			blkfree(c->vec);
			goto found;
		}
		p = c;
		f = f > 0;
E 10
I 10
    f = 0;			/* tree hangs off the header's left link */
D 24
    while (c = p->v_link[f]) {
E 24
I 24
    while ((c = p->v_link[f]) != NULL) {
E 24
	if ((f = *name - *c->v_name) == 0 &&
	    (f = Strcmp(name, c->v_name)) == 0) {
	    blkfree(c->vec);
	    goto found;
E 10
E 4
	}
D 4
	if (vp->vec)
		blkfree(vp->vec);
	scan(vec, trim);
	vp->vec = vec;
E 4
I 4
D 10
	p->v_link[f] = c = (struct varent *)xalloc(sizeof (struct varent));
	c->v_name = savestr(name);
	c->v_bal = 0;
	c->v_left = c->v_right = 0;
	c->v_parent = p;
	balance(p, f, 0);
E 10
I 10
	p = c;
	f = f > 0;
    }
    p->v_link[f] = c = (struct varent *) xmalloc((size_t) sizeof(struct varent));
    c->v_name = Strsave(name);
    c->v_bal = 0;
    c->v_left = c->v_right = 0;
    c->v_parent = p;
    balance(p, f, 0);
E 10
found:
D 10
	trim(c->vec = vec);
E 10
I 10
    trim(c->vec = vec);
E 10
E 4
}

I 10
void
E 10
D 17
unset(v)
D 4
	register char *v[];
E 4
I 4
D 10
	char *v[];
E 10
I 10
    Char   *v[];
E 17
I 17
/*ARGSUSED*/
unset(v, t)
    Char **v;
    struct command *t;
E 17
E 10
E 4
{
D 10

	unset1(v, &shvhed);
	if (adrof("histchars") == 0) {
		HIST = '!';
		HISTSUB = '^';
	}
E 10
I 10
    unset1(v, &shvhed);
E 10
I 4
#ifdef FILEC
D 10
	if (adrof("filec") == 0)
		filec = 0;
E 10
I 10
    if (adrof(STRfilec) == 0)
	filec = 0;
E 10
#endif
I 10
    if (adrof(STRhistchars) == 0) {
	HIST = '!';
	HISTSUB = '^';
    }
    if (adrof(STRwordchars) == 0)
	word_chars = STR_WORD_CHARS;
E 10
E 4
}

I 10
void
E 10
unset1(v, head)
D 10
	register char *v[];
	struct varent *head;
E 10
I 10
    register Char *v[];
    struct varent *head;
E 10
{
D 4
	register char *var;
E 4
D 10
	register struct varent *vp;
	register int cnt;
E 10
I 10
    register struct varent *vp;
    register int cnt;
E 10

D 4
	v++;
	while (var = *v++) {
E 4
I 4
D 10
	while (*++v) {
E 4
		cnt = 0;
D 4
		while (vp = madrof(var, head))
			unsetv1(vp->name, head), cnt++;
E 4
I 4
		while (vp = madrof(*v, head->v_left))
			unsetv1(vp), cnt++;
E 4
		if (cnt == 0)
D 4
			setname(var);
E 4
I 4
			setname(*v);
E 4
	}
E 10
I 10
    while (*++v) {
	cnt = 0;
D 24
	while (vp = madrof(*v, head->v_left))
E 24
I 24
	while ((vp = madrof(*v, head->v_left)) != NULL)
E 24
	    unsetv1(vp), cnt++;
	if (cnt == 0)
D 21
	    setname(short2str(*v));
E 21
I 21
	    setname(vis_str(*v));
E 21
    }
E 10
}

I 10
void
E 10
unsetv(var)
D 10
	char *var;
E 10
I 10
    Char   *var;
E 10
{
I 4
D 10
	register struct varent *vp;
E 10
I 10
    register struct varent *vp;
E 10
E 4

D 4
	unsetv1(var, &shvhed);
E 4
I 4
D 10
	if ((vp = adrof1(var, &shvhed)) == 0)
		udvar(var);
	unsetv1(vp);
E 10
I 10
    if ((vp = adrof1(var, &shvhed)) == 0)
	udvar(var);
    unsetv1(vp);
E 10
E 4
}

I 10
static void
E 10
D 4
unsetv1(var, head)
	char *var;
	struct varent *head;
E 4
I 4
unsetv1(p)
D 10
	register struct varent *p;
E 10
I 10
    register struct varent *p;
E 10
E 4
{
D 4
	register struct varent *vp;
E 4
I 4
D 10
	register struct varent *c, *pp;
	register f;
E 10
I 10
    register struct varent *c, *pp;
    register f;
E 10
E 4

D 4
	vp = adrof1(var, head);
	if (vp == 0)
		udvar(var);
	vp = shprev->link;
	shprev->link = vp->link;
	blkfree(vp->vec);
	xfree(vp->name);
	xfree((char *)vp);
E 4
I 4
D 10
	/*
	 * Free associated memory first to avoid complications.
	 */
	blkfree(p->vec);
	XFREE(p->v_name);
	/*
	 * If p is missing one child, then we can move the other
	 * into where p is.  Otherwise, we find the predecessor
	 * of p, which is guaranteed to have no right child, copy
	 * it into p, and move it's left child into it.
	 */
	if (p->v_right == 0)
		c = p->v_left;
	else if (p->v_left == 0)
		c = p->v_right;
	else {
		for (c = p->v_left; c->v_right; c = c->v_right)
			;
		p->v_name = c->v_name;
		p->vec = c->vec;
		p = c;
		c = p->v_left;
	}
	/*
	 * Move c into where p is.
	 */
	pp = p->v_parent;
	f = pp->v_right == p;
	if (pp->v_link[f] = c)
		c->v_parent = pp;
	/*
	 * Free the deleted node, and rebalance.
	 */
	XFREE((char *)p);
	balance(pp, f, 1);
E 10
I 10
    /*
     * Free associated memory first to avoid complications.
     */
    blkfree(p->vec);
    xfree((ptr_t) p->v_name);
    /*
     * If p is missing one child, then we can move the other into where p is.
     * Otherwise, we find the predecessor of p, which is guaranteed to have no
     * right child, copy it into p, and move it's left child into it.
     */
    if (p->v_right == 0)
	c = p->v_left;
    else if (p->v_left == 0)
	c = p->v_right;
    else {
D 20
	for (c = p->v_left; c->v_right; c = c->v_right);
E 20
I 20
	for (c = p->v_left; c->v_right; c = c->v_right)
	    continue;
E 20
	p->v_name = c->v_name;
	p->vec = c->vec;
	p = c;
	c = p->v_left;
    }
    /*
     * Move c into where p is.
     */
    pp = p->v_parent;
    f = pp->v_right == p;
D 24
    if (pp->v_link[f] = c)
E 24
I 24
    if ((pp->v_link[f] = c) != NULL)
E 24
	c->v_parent = pp;
    /*
     * Free the deleted node, and rebalance.
     */
    xfree((ptr_t) p);
    balance(pp, f, 1);
E 10
E 4
}

I 10
void
E 10
setNS(cp)
D 10
	char *cp;
E 10
I 10
    Char   *cp;
E 10
{
D 10

	set(cp, "");
E 10
I 10
D 16
    set(cp, STRNULL);
E 16
I 16
    set(cp, Strsave(STRNULL));
E 16
E 10
}

I 10
void
E 10
D 17
shift(v)
D 10
	register char **v;
E 10
I 10
    register Char **v;
E 17
I 17
/*ARGSUSED*/
shift(v, t)
    Char **v;
    struct command *t;
E 17
E 10
{
D 10
	register struct varent *argv;
	register char *name;
E 10
I 10
    register struct varent *argv;
    register Char *name;
E 10

D 10
	v++;
	name = *v;
	if (name == 0)
		name = "argv";
	else
D 4
		strip(name);
E 4
I 4
		(void) strip(name);
E 4
	argv = adrof(name);
	if (argv == 0)
		udvar(name);
	if (argv->vec[0] == 0)
		bferr("No more words");
	lshift(argv->vec, 1);
E 10
I 10
    v++;
    name = *v;
    if (name == 0)
	name = STRargv;
    else
	(void) strip(name);
    argv = adrof(name);
    if (argv == 0)
	udvar(name);
    if (argv->vec[0] == 0)
	stderror(ERR_NAME | ERR_NOMORE);
    lshift(argv->vec, 1);
E 10
}

I 10
static void
E 10
exportpath(val)
D 10
char **val;
E 10
I 10
    Char  **val;
E 10
{
D 10
	char exppath[BUFSIZ];
E 10
I 10
    Char    exppath[BUFSIZ];
E 10
D 4
	register char *dir;
E 4

D 10
	exppath[0] = 0;
	if (val)
		while (*val) {
			if (strlen(*val) + strlen(exppath) + 2 > BUFSIZ) {
				printf("Warning: ridiculously long PATH truncated\n");
				break;
			}
D 4
			strcat(exppath, *val++);
E 4
I 4
			(void) strcat(exppath, *val++);
E 4
			if (*val == 0 || eq(*val, ")"))
				break;
D 4
			strcat(exppath, ":");
E 4
I 4
			(void) strcat(exppath, ":");
E 4
		}
	setenv("PATH", exppath);
E 10
I 10
    exppath[0] = 0;
    if (val)
	while (*val) {
	    if (Strlen(*val) + Strlen(exppath) + 2 > BUFSIZ) {
D 17
		xprintf("Warning: ridiculously long PATH truncated\n");
E 17
I 17
		(void) fprintf(csherr,
			       "Warning: ridiculously long PATH truncated\n");
E 17
		break;
	    }
I 22
	    if ((**val != '/' || **val == '\0') && (euid == 0 || uid == 0)) 
		    (void) fprintf(csherr,
		    "Warning: exported path contains relative components.\n");
E 22
	    (void) Strcat(exppath, *val++);
	    if (*val == 0 || eq(*val, STRRparen))
		break;
	    (void) Strcat(exppath, STRcolon);
	}
    Setenv(STRPATH, exppath);
E 10
I 4
}

D 10
	/* macros to do single rotations on node p */
E 10
I 10
#ifndef lint
 /*
  * Lint thinks these have null effect
  */
 /* macros to do single rotations on node p */
E 10
#define rright(p) (\
	t = (p)->v_left,\
	(t)->v_parent = (p)->v_parent,\
	((p)->v_left = t->v_right) ? (t->v_right->v_parent = (p)) : 0,\
	(t->v_right = (p))->v_parent = t,\
	(p) = t)
#define rleft(p) (\
	t = (p)->v_right,\
	(t)->v_parent = (p)->v_parent,\
	((p)->v_right = t->v_left) ? (t->v_left->v_parent = (p)) : 0,\
	(t->v_left = (p))->v_parent = t,\
	(p) = t)
I 10
#else
struct varent *
rleft(p)
    struct varent *p;
{
    return (p);
}
struct varent *
rright(p)
    struct varent *p;
{
    return (p);
}
E 10

I 10
#endif				/* ! lint */


E 10
/*
 * Rebalance a tree, starting at p and up.
 * F == 0 means we've come from p's left child.
 * D == 1 means we've just done a delete, otherwise an insert.
 */
I 10
static void
E 10
balance(p, f, d)
D 10
	register struct varent *p;
	register f;
E 10
I 10
    register struct varent *p;
    register int f, d;
E 10
{
D 10
	register struct varent *pp;
	register struct varent *t;		/* used by the rotate macros */
	register ff;
E 10
I 10
    register struct varent *pp;
E 10

D 10
	/*
	 * Ok, from here on, p is the node we're operating on;
	 * pp is it's parent; f is the branch of p from which we have come;
	 * ff is the branch of pp which is p.
	 */
	for (; pp = p->v_parent; p = pp, f = ff) {
		ff = pp->v_right == p;
		if (f ^ d) {		/* right heavy */
			switch (p->v_bal) {
			case -1:		/* was left heavy */
				p->v_bal = 0;
				break;
			case 0:			/* was balanced */
				p->v_bal = 1;
				break;
			case 1:			/* was already right heavy */
				switch (p->v_right->v_bal) {
				case 1:			/* sigle rotate */
					pp->v_link[ff] = rleft(p);
					p->v_left->v_bal = 0;
					p->v_bal = 0;
					break;
				case 0:			/* single rotate */
					pp->v_link[ff] = rleft(p);
					p->v_left->v_bal = 1;
					p->v_bal = -1;
					break;
				case -1:		/* double rotate */
					rright(p->v_right);
					pp->v_link[ff] = rleft(p);
					p->v_left->v_bal =
						p->v_bal < 1 ? 0 : -1;
					p->v_right->v_bal =
						p->v_bal > -1 ? 0 : 1;
					p->v_bal = 0;
					break;
				}
				break;
			}
		} else {		/* left heavy */
			switch (p->v_bal) {
			case 1:			/* was right heavy */
				p->v_bal = 0;
				break;
			case 0:			/* was balanced */
				p->v_bal = -1;
				break;
			case -1:		/* was already left heavy */
				switch (p->v_left->v_bal) {
				case -1:		/* single rotate */
					pp->v_link[ff] = rright(p);
					p->v_right->v_bal = 0;
					p->v_bal = 0;
					break;
				case 0:			/* signle rotate */
					pp->v_link[ff] = rright(p);
					p->v_right->v_bal = -1;
					p->v_bal = 1;
					break;
				case 1:			/* double rotate */
					rleft(p->v_left);
					pp->v_link[ff] = rright(p);
					p->v_left->v_bal =
						p->v_bal < 1 ? 0 : -1;
					p->v_right->v_bal =
						p->v_bal > -1 ? 0 : 1;
					p->v_bal = 0;
					break;
				}
				break;
			}
E 10
I 10
#ifndef lint
    register struct varent *t;	/* used by the rotate macros */

#endif
    register ff;

    /*
     * Ok, from here on, p is the node we're operating on; pp is it's parent; f
     * is the branch of p from which we have come; ff is the branch of pp which
     * is p.
     */
D 24
    for (; pp = p->v_parent; p = pp, f = ff) {
E 24
I 24
    for (; (pp = p->v_parent) != NULL; p = pp, f = ff) {
E 24
	ff = pp->v_right == p;
	if (f ^ d) {		/* right heavy */
	    switch (p->v_bal) {
	    case -1:		/* was left heavy */
		p->v_bal = 0;
		break;
	    case 0:		/* was balanced */
		p->v_bal = 1;
		break;
	    case 1:		/* was already right heavy */
		switch (p->v_right->v_bal) {
		case 1:	/* sigle rotate */
		    pp->v_link[ff] = rleft(p);
		    p->v_left->v_bal = 0;
		    p->v_bal = 0;
		    break;
		case 0:	/* single rotate */
		    pp->v_link[ff] = rleft(p);
		    p->v_left->v_bal = 1;
		    p->v_bal = -1;
		    break;
		case -1:	/* double rotate */
		    (void) rright(p->v_right);
		    pp->v_link[ff] = rleft(p);
		    p->v_left->v_bal =
			p->v_bal < 1 ? 0 : -1;
		    p->v_right->v_bal =
			p->v_bal > -1 ? 0 : 1;
		    p->v_bal = 0;
		    break;
E 10
		}
D 10
		/*
		 * If from insert, then we terminate when p is balanced.
		 * If from delete, then we terminate when p is unbalanced.
		 */
		if ((p->v_bal == 0) ^ d)
			break;
E 10
I 10
		break;
	    }
E 10
	}
I 10
	else {			/* left heavy */
	    switch (p->v_bal) {
	    case 1:		/* was right heavy */
		p->v_bal = 0;
		break;
	    case 0:		/* was balanced */
		p->v_bal = -1;
		break;
	    case -1:		/* was already left heavy */
		switch (p->v_left->v_bal) {
		case -1:	/* single rotate */
		    pp->v_link[ff] = rright(p);
		    p->v_right->v_bal = 0;
		    p->v_bal = 0;
		    break;
		case 0:	/* signle rotate */
		    pp->v_link[ff] = rright(p);
		    p->v_right->v_bal = -1;
		    p->v_bal = 1;
		    break;
		case 1:	/* double rotate */
		    (void) rleft(p->v_left);
		    pp->v_link[ff] = rright(p);
		    p->v_left->v_bal =
			p->v_bal < 1 ? 0 : -1;
		    p->v_right->v_bal =
			p->v_bal > -1 ? 0 : 1;
		    p->v_bal = 0;
		    break;
		}
		break;
	    }
	}
	/*
	 * If from insert, then we terminate when p is balanced. If from
	 * delete, then we terminate when p is unbalanced.
	 */
	if ((p->v_bal == 0) ^ d)
	    break;
    }
E 10
}

I 10
void
E 10
plist(p)
D 10
	register struct varent *p;
E 10
I 10
    register struct varent *p;
E 10
{
D 10
	register struct varent *c;
	register len;
E 10
I 10
    register struct varent *c;
    register len;
I 26
    sigset_t sigset;
E 26
E 10

D 10
	if (setintr)
		(void) sigsetmask(sigblock(0) & ~ sigmask(SIGINT));
	for (;;) {
		while (p->v_left)
			p = p->v_left;
	x:
		if (p->v_parent == 0)		/* is it the header? */
			return;
		len = blklen(p->vec);
		printf(p->v_name);
D 7
		putchar('\t');
E 7
I 7
		cshputchar('\t');
E 7
		if (len != 1)
D 7
			putchar('(');
E 7
I 7
			cshputchar('(');
E 7
		blkpr(p->vec);
		if (len != 1)
D 7
			putchar(')');
		putchar('\n');
E 7
I 7
			cshputchar(')');
		cshputchar('\n');
E 7
		if (p->v_right) {
			p = p->v_right;
			continue;
		}
		do {
			c = p;
			p = p->v_parent;
		} while (p->v_right == c);
		goto x;
E 10
I 10
D 26
    if (setintr)
D 14
	(void) sigsetmask(sigblock((sigmask_t) 0) & ~sigmask(SIGINT));
E 14
I 14
	(void) sigsetmask(sigblock((sigset_t) 0) & ~sigmask(SIGINT));
E 26
I 26
    if (setintr) {
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_UNBLOCK, &sigset, NULL);
    }
E 26
E 14

    for (;;) {
	while (p->v_left)
	    p = p->v_left;
x:
	if (p->v_parent == 0)	/* is it the header? */
	    return;
	len = blklen(p->vec);
D 17
	xprintf(short2str(p->v_name));
	xputchar('\t');
E 17
I 17
D 22
	(void) fprintf(cshout, short2str(p->v_name));
	(void) fputc('\t', cshout);
E 22
I 22
	(void) fprintf(cshout, "%s\t", short2str(p->v_name));
E 22
E 17
	if (len != 1)
D 17
	    xputchar('(');
	blkpr(p->vec);
E 17
I 17
	    (void) fputc('(', cshout);
	blkpr(cshout, p->vec);
E 17
	if (len != 1)
D 17
	    xputchar(')');
	xputchar('\n');
E 17
I 17
	    (void) fputc(')', cshout);
	(void) fputc('\n', cshout);
E 17
	if (p->v_right) {
	    p = p->v_right;
	    continue;
E 10
	}
I 10
	do {
	    c = p;
	    p = p->v_parent;
	} while (p->v_right == c);
	goto x;
    }
E 10
E 4
}
E 1
