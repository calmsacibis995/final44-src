h00636
s 00002/00009/00950
d D 8.2 95/04/29 13:09:03 christos 28 27
c Fixes from Chris Demetriou and Charles Hannum 
e
s 00002/00002/00957
d D 8.1 93/05/31 16:41:47 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00957
d D 5.21 93/05/27 05:06:46 christos 26 25
c changed _Q,_Q1 to _QF,_QB to avoid conflict with new <ctype.h>
e
s 00007/00007/00952
d D 5.20 93/05/22 19:06:24 christos 25 24
c Fixed gcc -Wall warnings
e
s 00002/00002/00957
d D 5.19 92/05/15 00:14:49 christos 24 23
c Fixed $< for NLS characters
e
s 00002/00002/00957
d D 5.18 91/11/06 16:09:32 christos 23 22
c Added support for displaying non-printable characters
e
s 00140/00014/00819
d D 5.17 91/11/04 18:24:50 christos 22 21
c Added :a modifier and $foo:s
e
s 00003/00002/00830
d D 5.16 91/10/28 21:27:54 leres 21 20
c Fix gcc "bodyless for/while" warnings.
e
s 00032/00017/00800
d D 5.15 91/07/22 11:47:12 christos 20 19
c support for multiple : modifiers
e
s 00002/00001/00815
d D 5.14 91/07/19 17:30:36 christos 19 18
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00000/00810
d D 5.13 91/06/08 17:08:38 christos 18 17
c More prototype fixes, Removed TERMIOS define
e
s 00006/00000/00804
d D 5.12 91/06/08 12:20:13 bostic 17 16
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00011/00011/00793
d D 5.11 91/06/07 20:57:15 christos 16 15
c static function prototypes
e
s 00002/00001/00802
d D 5.10 91/06/07 11:13:18 bostic 15 14
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00629/00526/00174
d D 5.9 91/06/04 13:31:20 bostic 14 13
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00005/00004/00695
d D 5.8 91/04/04 18:17:35 bostic 13 12
c new copyright; att/bsd/shared
e
s 00002/00002/00697
d D 5.7 91/03/14 12:28:55 bostic 12 11
c lost the SCCS id's...
e
s 00006/00009/00693
d D 5.6 91/03/14 12:28:08 bostic 11 10
c use the library globbing routines instead of rolling our own 
c any -> index (use the faster library routine)
e
s 00002/00000/00700
d D 5.5 88/01/15 03:33:27 edward 10 9
c fixed labuf overflow (caused by, for example, very long variable expansions)
e
s 00004/00008/00696
d D 5.4 86/12/18 22:49:08 bostic 9 8
c allow EOF to end tagged input
e
s 00000/00001/00704
d D 5.3 86/03/29 07:37:29 lepreau 8 7
c Minor speedups & cleanups:
c replace letter() et al with ctype-like cmap macros and expand cmap to short
c for new LET and DIG bits; use bzero in private calloc; make btell a macro.
e
s 00003/00003/00702
d D 5.2 85/06/06 13:10:48 edward 7 6
c cleaning up after bozos
e
s 00008/00002/00697
d D 5.1 85/06/04 10:56:25 dist 6 5
c Add copyright
e
s 00033/00034/00666
d D 4.5 84/12/13 14:41:38 edward 5 4
c performance
e
s 00003/00003/00697
d D 4.4 83/05/03 19:27:44 sam 4 3
c recover from corrupted SCCS file
e
s 00007/00007/00693
d D 4.3 82/05/07 18:19:03 mckusick 3 2
c update to new fs
e
s 00001/00001/00699
d D 4.2 81/05/03 19:51:12 root 2 1
c fix ${TERM} leaving extra }
e
s 00700/00000/00000
d D 4.1 80/10/09 12:40:36 bill 1 0
c date and time created 80/10/09 12:40:36 by bill
e
u
U
t
T
I 6
D 13
/*
 * Copyright (c) 1980 Regents of the University of California.
D 7
 * All rights reserved.  The Berkeley software License Agreement
E 7
I 7
 * All rights reserved.  The Berkeley Software License Agreement
E 7
 * specifies the terms and conditions for redistribution.
E 13
I 13
/*-
D 27
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * %sccs.include.redist.c%
E 13
 */

E 6
I 1
D 5
static	char *sccsid = "%Z%%M% %I% %G%";
E 5
I 5
#ifndef lint
D 6
static	char *sccsid = "%W% (Berkeley) %G%";
#endif
E 6
I 6
D 7
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 7
I 7
D 11
static char *sccsid = "%W% (Berkeley) %G%";
E 11
I 11
D 12
static char *sccsid = "@(#)sh.dol.c	5.5 (Berkeley) 1/15/88";
E 11
#endif
E 12
I 12
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 12
E 7
E 6
E 5

I 17
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 18
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 18
E 17
D 15
#include "sh.h"
E 15
I 15
#include "csh.h"
#include "extern.h"
E 15
I 5
D 8
#include "sh.char.h"
E 8
E 5

/*
D 14
 * C shell
 */

/*
E 14
 * These routines perform variable substitution and quoting via ' and ".
 * To this point these constructs have been preserved in the divided
 * input words.  Here we expand variables and turn quoting via ' and " into
 * QUOTE bits on characters (which prevent further interpretation).
 * If the `:q' modifier was applied during history expansion, then
D 5
 * some QUOTEing may have occurred already, so we dont "scan(,&trim)" here.
E 5
I 5
 * some QUOTEing may have occurred already, so we dont "trim()" here.
E 5
 */

D 14
int	Dpeekc, Dpeekrd;		/* Peeks for DgetC and Dreadc */
char	*Dcp, **Dvp;			/* Input vector for Dreadc */
E 14
I 14
static int Dpeekc, Dpeekrd;	/* Peeks for DgetC and Dreadc */
static Char *Dcp, **Dvp;	/* Input vector for Dreadc */
E 14

#define	DEOF	-1

#define	unDgetC(c)	Dpeekc = c

D 5
char	*QUOTES = "\\'`\"";
E 5
I 5
D 26
#define QUOTES		(_Q|_Q1|_ESC)	/* \ ' " ` */
E 26
I 26
#define QUOTES		(_QF|_QB|_ESC)	/* \ ' " ` */
E 26
E 5

/*
 * The following variables give the information about the current
 * $ expansion, recording the current word position, the remaining
 * words within this expansion, the count of remaining words, and the
 * information about any : modifier which is being applied.
 */
I 20
#define MAXWLEN (BUFSIZ - 4)
#define MAXMOD MAXWLEN		/* This cannot overflow	*/
E 20
D 14
char	*dolp;			/* Remaining chars from this word */
char	**dolnxt;		/* Further words */
int	dolcnt;			/* Count of further words */
char	dolmod;			/* : modifier character */
int	dolmcnt;		/* :gx -> 10000, else 1 */
E 14
I 14
static Char *dolp;		/* Remaining chars from this word */
static Char **dolnxt;		/* Further words */
static int dolcnt;		/* Count of further words */
D 20
static Char dolmod;		/* : modifier character */
E 20
I 20
static Char dolmod[MAXMOD];	/* : modifier character */
static int dolnmod;		/* Number of modifiers */
E 20
static int dolmcnt;		/* :gx -> 10000, else 1 */
I 22
static int dolwcnt;		/* :wx -> 10000, else 1 */
E 22
E 14

I 14
D 16
static void Dfix2();
static Char *Dpack();
static int Dword();
static void dolerror();
static int DgetC();
static void Dgetdol();
static void fixDolMod();
static void setDolp();
static void unDredc();
static int Dredc();
static void Dtestq();
E 16
I 16
static void	 Dfix2 __P((Char **));
D 21
static Char 	*Dpack __P((Char *, Char *));
E 21
I 21
static Char	*Dpack __P((Char *, Char *));
E 21
static int	 Dword __P((void));
static void	 dolerror __P((Char *));
static int	 DgetC __P((int));
static void	 Dgetdol __P((void));
static void	 fixDolMod __P((void));
static void	 setDolp __P((Char *));
static void	 unDredc __P((int));
static int	 Dredc __P((void));
static void	 Dtestq __P((int));
E 16


E 14
D 5
int	Dtest();		/* Test for \ " ` or ' */

E 5
/*
 * Fix up the $ expansions and quotations in the
 * argument list to command t.
 */
I 14
void
E 14
Dfix(t)
D 14
	register struct command *t;
E 14
I 14
    register struct command *t;
E 14
{
I 5
D 14
	register char **pp;
	register char *p;
E 14
I 14
    register Char **pp;
    register Char *p;
E 14
E 5

D 14
	if (noexec)
E 14
I 14
    if (noexec)
	return;
    /* Note that t_dcom isn't trimmed thus !...:q's aren't lost */
D 25
    for (pp = t->t_dcom; p = *pp++;)
E 25
I 25
    for (pp = t->t_dcom; (p = *pp++) != NULL;)
E 25
	for (; *p; p++) {
	    if (cmap(*p, _DOL | QUOTES)) {	/* $, \, ', ", ` */
		Dfix2(t->t_dcom);	/* found one */
		blkfree(t->t_dcom);
		t->t_dcom = gargv;
		gargv = 0;
E 14
		return;
D 5
	gflag = 0, rscan(t->t_dcom, Dtest);
	if (gflag == 0)
		return;
	Dfix2(t->t_dcom);
	blkfree(t->t_dcom), t->t_dcom = gargv, gargv = 0;
E 5
I 5
D 14
	/* Note that t_dcom isn't trimmed thus !...:q's aren't lost */
	for (pp = t->t_dcom; p = *pp++;)
		while (*p)
			if (cmap(*p++, _DOL|QUOTES)) {	/* $, \, ', ", ` */
				Dfix2(t->t_dcom);	/* found one */
				blkfree(t->t_dcom);
				t->t_dcom = gargv;
				gargv = 0;
				return;
			}
E 14
I 14
	    }
	}
E 14
E 5
}

/*
 * $ substitute one word, for i/o redirection
 */
D 14
char *
E 14
I 14
Char   *
E 14
Dfix1(cp)
D 14
	register char *cp;
E 14
I 14
    register Char *cp;
E 14
{
D 14
	char *Dv[2];
E 14
I 14
    Char   *Dv[2];
E 14

D 14
	if (noexec)
		return (0);
	Dv[0] = cp; Dv[1] = NOSTR;
	Dfix2(Dv);
	if (gargc != 1) {
		setname(cp);
		bferr("Ambiguous");
	}
	cp = savestr(gargv[0]);
	blkfree(gargv), gargv = 0;
	return (cp);
E 14
I 14
    if (noexec)
	return (0);
    Dv[0] = cp;
    Dv[1] = NULL;
    Dfix2(Dv);
    if (gargc != 1) {
D 23
	setname(short2str(cp));
E 23
I 23
	setname(vis_str(cp));
E 23
	stderror(ERR_NAME | ERR_AMBIG);
    }
    cp = Strsave(gargv[0]);
    blkfree(gargv), gargv = 0;
    return (cp);
E 14
}

/*
 * Subroutine to do actual fixing after state initialization.
 */
I 14
static void
E 14
Dfix2(v)
D 14
	char **v;
E 14
I 14
    Char  **v;
E 14
{
D 11
	char *agargv[GAVSIZ];

	ginit(agargv);			/* Initialize glob's area pointers */
E 11
I 11
D 14
	ginit();			/* Initialize glob's area pointers */
E 11
	Dvp = v; Dcp = "";		/* Setup input vector for Dreadc */
	unDgetC(0); unDredc(0);		/* Clear out any old peeks (at error) */
	dolp = 0; dolcnt = 0;		/* Clear out residual $ expands (...) */
	while (Dword())
		continue;
E 14
I 14
    ginit();			/* Initialize glob's area pointers */
    Dvp = v;
    Dcp = STRNULL;		/* Setup input vector for Dreadc */
    unDgetC(0);
    unDredc(0);			/* Clear out any old peeks (at error) */
    dolp = 0;
    dolcnt = 0;			/* Clear out residual $ expands (...) */
    while (Dword())
	continue;
E 14
D 11
	gargv = copyblk(gargv);
E 11
}

I 14
D 20
#define MAXWLEN (BUFSIZ - 4)
E 20
E 14
/*
I 14
 * Pack up more characters in this word
 */
static Char *
Dpack(wbuf, wp)
    Char   *wbuf, *wp;
{
    register int c;
    register int i = MAXWLEN - (wp - wbuf);

    for (;;) {
	c = DgetC(DODOL);
	if (c == '\\') {
	    c = DgetC(0);
	    if (c == DEOF) {
		unDredc(c);
		*wp = 0;
		Gcat(STRNULL, wbuf);
		return (NULL);
	    }
	    if (c == '\n')
		c = ' ';
	    else
		c |= QUOTE;
	}
	if (c == DEOF) {
	    unDredc(c);
	    *wp = 0;
	    Gcat(STRNULL, wbuf);
	    return (NULL);
	}
D 26
	if (cmap(c, _SP | _NL | _Q | _Q1)) {	/* sp \t\n'"` */
E 26
I 26
	if (cmap(c, _SP | _NL | _QF | _QB)) {	/* sp \t\n'"` */
E 26
	    unDgetC(c);
	    if (cmap(c, QUOTES))
		return (wp);
	    *wp++ = 0;
	    Gcat(STRNULL, wbuf);
	    return (NULL);
	}
	if (--i <= 0)
	    stderror(ERR_WTOOLONG);
	*wp++ = c;
    }
}

/*
E 14
 * Get a word.  This routine is analogous to the routine
 * word() in sh.lex.c for the main lexical input.  One difference
 * here is that we don't get a newline to terminate our expansion.
 * Rather, DgetC will return a DEOF when we hit the end-of-input.
 */
I 14
static int
E 14
Dword()
{
D 14
	register int c, c1;
	char wbuf[BUFSIZ];
	register char *wp = wbuf;
	register int i = BUFSIZ - 4;
	register bool dolflg;
	bool sofar = 0;
E 14
I 14
    register int c, c1;
    Char    wbuf[BUFSIZ];
    register Char *wp = wbuf;
    register int i = MAXWLEN;
    register bool dolflg;
    bool    sofar = 0, done = 0;
E 14

D 14
loop:
E 14
I 14
    while (!done) {
	done = 1;
E 14
	c = DgetC(DODOL);
	switch (c) {

	case DEOF:
D 14
deof:
		if (sofar == 0)
			return (0);
		/* finish this word and catch the code above the next time */
		unDredc(c);
		/* fall into ... */
E 14
I 14
	    if (sofar == 0)
		return (0);
	    /* finish this word and catch the code above the next time */
	    unDredc(c);
	    /* fall into ... */
E 14

	case '\n':
D 14
		*wp = 0;
		goto ret;
E 14
I 14
	    *wp = 0;
	    Gcat(STRNULL, wbuf);
	    return (1);
E 14

	case ' ':
	case '\t':
D 14
		goto loop;
E 14
I 14
	    done = 0;
	    break;
E 14

	case '`':
D 14
		/* We preserve ` quotations which are done yet later */
		*wp++ = c, --i;
E 14
I 14
	    /* We preserve ` quotations which are done yet later */
	    *wp++ = c, --i;
E 14
	case '\'':
	case '"':
D 14
		/*
		 * Note that DgetC never returns a QUOTES character
		 * from an expansion, so only true input quotes will
		 * get us here or out.
		 */
		c1 = c;
		dolflg = c1 == '"' ? DODOL : 0;
		for (;;) {
			c = DgetC(dolflg);
			if (c == c1)
				break;
			if (c == '\n' || c == DEOF)
				error("Unmatched %c", c1);
			if ((c & (QUOTE|TRIM)) == ('\n' | QUOTE))
				--wp, ++i;
			if (--i <= 0)
				goto toochars;
			switch (c1) {
E 14
I 14
	    /*
	     * Note that DgetC never returns a QUOTES character from an
	     * expansion, so only true input quotes will get us here or out.
	     */
	    c1 = c;
	    dolflg = c1 == '"' ? DODOL : 0;
	    for (;;) {
		c = DgetC(dolflg);
		if (c == c1)
		    break;
		if (c == '\n' || c == DEOF)
		    stderror(ERR_UNMATCHED, c1);
		if ((c & (QUOTE | TRIM)) == ('\n' | QUOTE))
		    --wp, ++i;
		if (--i <= 0)
		    stderror(ERR_WTOOLONG);
		switch (c1) {
E 14

D 14
			case '"':
				/*
				 * Leave any `s alone for later.
				 * Other chars are all quoted, thus `...`
				 * can tell it was within "...".
				 */
				*wp++ = c == '`' ? '`' : c | QUOTE;
				break;
E 14
I 14
		case '"':
		    /*
		     * Leave any `s alone for later. Other chars are all
		     * quoted, thus `...` can tell it was within "...".
		     */
		    *wp++ = c == '`' ? '`' : c | QUOTE;
		    break;
E 14

D 14
			case '\'':
				/* Prevent all further interpretation */
				*wp++ = c | QUOTE;
				break;
E 14
I 14
		case '\'':
		    /* Prevent all further interpretation */
		    *wp++ = c | QUOTE;
		    break;
E 14

D 14
			case '`':
				/* Leave all text alone for later */
				*wp++ = c;
				break;
			}
E 14
I 14
		case '`':
		    /* Leave all text alone for later */
		    *wp++ = c;
		    break;
I 22

		default:
		    break;
E 22
E 14
		}
D 14
		if (c1 == '`')
			*wp++ = '`', --i;
		goto pack;		/* continue the word */
E 14
I 14
	    }
	    if (c1 == '`')
D 22
		*wp++ = '`', --i;
E 22
I 22
		*wp++ = '`' /* i--; eliminated */;
E 22
	    sofar = 1;
	    if ((wp = Dpack(wbuf, wp)) == NULL)
		return (1);
	    else {
		i = MAXWLEN - (wp - wbuf);
		done = 0;
	    }
	    break;
E 14

	case '\\':
D 14
		c = DgetC(0);		/* No $ subst! */
		if (c == '\n' || c == DEOF)
			goto loop;
		c |= QUOTE;
E 14
I 14
	    c = DgetC(0);	/* No $ subst! */
	    if (c == '\n' || c == DEOF) {
		done = 0;
E 14
		break;
I 14
	    }
	    c |= QUOTE;
	    break;
I 22

	default:
	    break;
E 22
E 14
	}
D 14
	unDgetC(c);
pack:
	sofar = 1;
	/* pack up more characters in this word */
	for (;;) {
		c = DgetC(DODOL);
		if (c == '\\') {
			c = DgetC(0);
			if (c == DEOF)
				goto deof;
			if (c == '\n')
				c = ' ';
			else
				c |= QUOTE;
		}
		if (c == DEOF)
			goto deof;
D 5
		if (any(c, " '`\"\t\n")) {
E 5
I 5
		if (cmap(c, _SP|_NL|_Q|_Q1)) {		/* sp \t\n'"` */
E 5
			unDgetC(c);
D 5
			if (any(c, QUOTES))
E 5
I 5
			if (cmap(c, QUOTES))
E 5
				goto loop;
			*wp++ = 0;
			goto ret;
		}
		if (--i <= 0)
toochars:
			error("Word too long");
		*wp++ = c;
E 14
I 14
	if (done) {
	    unDgetC(c);
	    sofar = 1;
	    if ((wp = Dpack(wbuf, wp)) == NULL)
		return (1);
	    else {
		i = MAXWLEN - (wp - wbuf);
		done = 0;
	    }
E 14
	}
D 14
ret:
	Gcat("", wbuf);
	return (1);
E 14
I 14
    }
    /* Really NOTREACHED */
    return (0);
E 14
}

I 14

E 14
/*
 * Get a character, performing $ substitution unless flag is 0.
D 4
 * Any QUOTES character which is ret}vned from a $ expansion is
 * QUOTEd s/ that it will not be recognized above.
E 4
I 4
 * Any QUOTES character which is returned from a $ expansion is
 * QUOTEd so that it will not be recognized above.
E 4
 */
I 14
static int
E 14
DgetC(flag)
D 14
	register int flag;
E 14
I 14
    register int flag;
E 14
{
D 14
	register int c;
E 14
I 14
    register int c;
E 14

top:
D 14
	if (c = Dpeekc) {
D 4
		Dpedkc = 0;
E 4
I 4
		Dpeekc = 0;
E 4
		return (c);
E 14
I 14
D 25
    if (c = Dpeekc) {
E 25
I 25
    if ((c = Dpeekc) != '\0') {
E 25
	Dpeekc = 0;
	return (c);
    }
    if (lap) {
	c = *lap++ & (QUOTE | TRIM);
	if (c == 0) {
	    lap = 0;
	    goto top;
E 14
	}
D 14
	if (lap) {
		c = *lap++ & (QUOTE|TRIM);
		if (c == 0) {
			lap = 0;
			goto top;
		}
E 14
quotspec:
D 5
		if (any(c, QUOTES))
E 5
I 5
D 14
		if (cmap(c, QUOTES))
E 5
			return (c | QUOTE);
		return (c);
	}
	if (dolp) {
		if (c = *dolp++ & (QUOTE|TRIM))
			goto quotspec;
		if (dolcnt > 0) {
			setDolp(*dolnxt++);
			--dolcnt;
			return (' ');
		}
		dolp = 0;
	}
E 14
I 14
	if (cmap(c, QUOTES))
	    return (c | QUOTE);
	return (c);
    }
    if (dolp) {
D 25
	if (c = *dolp++ & (QUOTE | TRIM))
E 25
I 25
	if ((c = *dolp++ & (QUOTE | TRIM)) != '\0')
E 25
	    goto quotspec;
E 14
	if (dolcnt > 0) {
D 14
		setDolp(*dolnxt++);
		--dolcnt;
		goto top;
E 14
I 14
	    setDolp(*dolnxt++);
	    --dolcnt;
	    return (' ');
E 14
	}
D 14
	c = Dredc();
	if (c == '$' && flag) {
		Dgetdol();
		goto top;
	}
	return (c);
E 14
I 14
	dolp = 0;
    }
    if (dolcnt > 0) {
	setDolp(*dolnxt++);
	--dolcnt;
	goto top;
    }
    c = Dredc();
    if (c == '$' && flag) {
	Dgetdol();
	goto top;
    }
    return (c);
E 14
}

D 14
char	*nulvec[] = { 0 };
struct	varent nulargv = { nulvec, "argv", 0 };
E 14
I 14
static Char *nulvec[] = {0};
D 25
static struct varent nulargv = {nulvec, STRargv, 0};
E 25
I 25
static struct varent nulargv = {nulvec, STRargv, { NULL, NULL, NULL }, 0};
E 25
E 14

I 14
static void
dolerror(s)
    Char   *s;
{
D 23
    setname(short2str(s));
E 23
I 23
    setname(vis_str(s));
E 23
    stderror(ERR_NAME | ERR_RANGE);
}

E 14
/*
 * Handle the multitudinous $ expansion forms.
 * Ugh.
 */
I 14
static void
E 14
Dgetdol()
{
D 14
	register char *np;
	register struct varent *vp;
	char name[20];
	int c, sc;
	int subscr = 0, lwb = 1, upb = 0;
D 3
	bool dimen = 0, isset = 0;
E 3
I 3
	bool dimen = 0, bitset = 0;
E 3
	char wbuf[BUFSIZ];
E 14
I 14
    register Char *np;
    register struct varent *vp = NULL;
    Char    name[4 * MAXVARLEN + 1];
    int     c, sc;
    int     subscr = 0, lwb = 1, upb = 0;
    bool    dimen = 0, bitset = 0;
    char    tnp;
    Char    wbuf[BUFSIZ];
I 22
    static Char *dolbang = NULL;
E 22
E 14

D 14
	dolmod = dolmcnt = 0;
	c = sc = DgetC(0);
	if (c == '{')
		c = DgetC(0);		/* sc is { to take } later */
	if ((c & TRIM) == '#')
		dimen++, c = DgetC(0);		/* $# takes dimension */
	else if (c == '?')
D 3
		isset++, c = DgetC(0);		/* $? tests existence */
E 3
I 3
		bitset++, c = DgetC(0);		/* $? tests existence */
E 3
	switch (c) {
	
	case '$':
D 3
		if (dimen || isset)
E 3
I 3
		if (dimen || bitset)
E 3
			goto syntax;		/* No $?$, $#$ */
		setDolp(doldol);
		goto eatbrac;
E 14
I 14
D 20
    dolmod = dolmcnt = 0;
E 20
I 20
D 22
    dolnmod = dolmcnt = 0;
E 22
I 22
    dolnmod = dolmcnt = dolwcnt = 0;
E 22
E 20
    c = sc = DgetC(0);
    if (c == '{')
	c = DgetC(0);		/* sc is { to take } later */
    if ((c & TRIM) == '#')
	dimen++, c = DgetC(0);	/* $# takes dimension */
    else if (c == '?')
	bitset++, c = DgetC(0);	/* $? tests existence */
    switch (c) {
E 14

I 22
    case '!':
	if (dimen || bitset)
	    stderror(ERR_SYNTAX);
	if (backpid != 0) {
	    if (dolbang) 
		xfree((ptr_t) dolbang);
	    setDolp(dolbang = putn(backpid));
	}
	goto eatbrac;

E 22
D 14
	case '<'|QUOTE:
D 3
		if (dimen || isset)
E 3
I 3
		if (dimen || bitset)
E 3
			goto syntax;		/* No $?<, $#< */
		for (np = wbuf; read(OLDSTD, np, 1) == 1; np++) {
			if (np >= &wbuf[BUFSIZ-1])
				error("$< line too long");
			if (*np <= 0 || *np == '\n')
				break;
		}
		*np = 0;
		/*
		 * KLUDGE: dolmod is set here because it will
		 * cause setDolp to call domod and thus to copy wbuf.
		 * Otherwise setDolp would use it directly. If we saved
		 * it ourselves, no one would know when to free it.
		 * The actual function of the 'q' causes filename
		 * expansion not to be done on the interpolated value.
		 */
		dolmod = 'q';
		dolmcnt = 10000;
		setDolp(wbuf);
		goto eatbrac;
E 14
I 14
    case '$':
	if (dimen || bitset)
	    stderror(ERR_SYNTAX);
	setDolp(doldol);
	goto eatbrac;
E 14

D 14
	case DEOF:
	case '\n':
		goto syntax;

	case '*':
D 5
		strcpy(name, "argv");
E 5
I 5
		(void) strcpy(name, "argv");
E 5
		vp = adrof("argv");
		subscr = -1;			/* Prevent eating [...] */
E 14
I 14
    case '<' | QUOTE:
	if (bitset)
	    stderror(ERR_NOTALLOWED, "$?<");
	if (dimen)
	    stderror(ERR_NOTALLOWED, "$?#");
	for (np = wbuf; read(OLDSTD, &tnp, 1) == 1; np++) {
D 24
	    *np = tnp;
E 24
I 24
	    *np = (unsigned char) tnp;
E 24
	    if (np >= &wbuf[BUFSIZ - 1])
		stderror(ERR_LTOOLONG);
D 24
	    if (SIGN_EXTEND_CHAR(tnp) <= 0 || tnp == '\n')
E 24
I 24
	    if (tnp == '\n')
E 24
E 14
		break;
I 14
	}
	*np = 0;
	/*
	 * KLUDGE: dolmod is set here because it will cause setDolp to call
	 * domod and thus to copy wbuf. Otherwise setDolp would use it
	 * directly. If we saved it ourselves, no one would know when to free
	 * it. The actual function of the 'q' causes filename expansion not to
	 * be done on the interpolated value.
	 */
D 20
	dolmod = 'q';
E 20
I 20
	dolmod[dolnmod++] = 'q';
E 20
	dolmcnt = 10000;
	setDolp(wbuf);
	goto eatbrac;
E 14

D 14
	default:
		np = name;
		if (digit(c)) {
			if (dimen)
				goto syntax;	/* No $#1, e.g. */
			subscr = 0;
			do {
				subscr = subscr * 10 + c - '0';
				c = DgetC(0);
			} while (digit(c));
			unDredc(c);
			if (subscr < 0)
				goto oob;
			if (subscr == 0) {
D 3
				if (isset) {
E 3
I 3
				if (bitset) {
E 3
					dolp = file ? "1" : "0";
					goto eatbrac;
				}
				if (file == 0)
					error("No file for $0");
				setDolp(file);
				goto eatbrac;
			}
D 3
			if (isset)
E 3
I 3
			if (bitset)
E 3
				goto syntax;
			vp = adrof("argv");
			if (vp == 0) {
				vp = &nulargv;
				goto eatmod;
			}
			break;
E 14
I 14
    case DEOF:
    case '\n':
	stderror(ERR_SYNTAX);
	/* NOTREACHED */
	break;

    case '*':
	(void) Strcpy(name, STRargv);
	vp = adrof(STRargv);
	subscr = -1;		/* Prevent eating [...] */
	break;

    default:
	np = name;
	if (Isdigit(c)) {
	    if (dimen)
		stderror(ERR_NOTALLOWED, "$#<num>");
	    subscr = 0;
	    do {
		subscr = subscr * 10 + c - '0';
		c = DgetC(0);
	    } while (Isdigit(c));
	    unDredc(c);
	    if (subscr < 0) {
		dolerror(vp->v_name);
		return;
	    }
	    if (subscr == 0) {
		if (bitset) {
		    dolp = ffile ? STR1 : STR0;
		    goto eatbrac;
E 14
		}
D 14
		if (!alnum(c))
			goto syntax;
		for (;;) {
			*np++ = c;
			c = DgetC(0);
			if (!alnum(c))
				break;
			if (np >= &name[sizeof name - 2])
syntax:
				error("Variable syntax");
		}
		*np++ = 0;
		unDredc(c);
		vp = adrof(name);
	}
D 3
	if (isset) {
E 3
I 3
	if (bitset) {
E 3
		dolp = (vp || getenv(name)) ? "1" : "0";
E 14
I 14
		if (ffile == 0)
		    stderror(ERR_DOLZERO);
		fixDolMod();
		setDolp(ffile);
E 14
		goto eatbrac;
I 14
	    }
	    if (bitset)
		stderror(ERR_DOLQUEST);
	    vp = adrof(STRargv);
	    if (vp == 0) {
		vp = &nulargv;
		goto eatmod;
	    }
	    break;
E 14
	}
D 14
	if (vp == 0) {
		np = getenv(name);
		if (np) {
			addla(np);
D 2
			return;
E 2
I 2
			goto eatbrac;
E 2
		}
		udvar(name);
		/*NOTREACHED*/
E 14
I 14
	if (!alnum(c))
	    stderror(ERR_VARALNUM);
	for (;;) {
	    *np++ = c;
	    c = DgetC(0);
	    if (!alnum(c))
		break;
	    if (np >= &name[MAXVARLEN])
		stderror(ERR_VARTOOLONG);
E 14
	}
D 14
	c = DgetC(0);
	upb = blklen(vp->vec);
	if (dimen == 0 && subscr == 0 && c == '[') {
		np = name;
		for (;;) {
			c = DgetC(DODOL);	/* Allow $ expand within [ ] */
			if (c == ']')
				break;
			if (c == '\n' || c == DEOF)
				goto syntax;
			if (np >= &name[sizeof name - 2])
				goto syntax;
			*np++ = c;
		}
		*np = 0, np = name;
		if (dolp || dolcnt)		/* $ exp must end before ] */
			goto syntax;
		if (!*np)
			goto syntax;
		if (digit(*np)) {
			register int i = 0;
E 14
I 14
	*np++ = 0;
	unDredc(c);
	vp = adrof(name);
    }
    if (bitset) {
	dolp = (vp || getenv(short2str(name))) ? STR1 : STR0;
	goto eatbrac;
    }
    if (vp == 0) {
	np = str2short(getenv(short2str(name)));
	if (np) {
	    fixDolMod();
	    setDolp(np);
	    goto eatbrac;
	}
	udvar(name);
	/* NOTREACHED */
    }
    c = DgetC(0);
    upb = blklen(vp->vec);
    if (dimen == 0 && subscr == 0 && c == '[') {
	np = name;
	for (;;) {
	    c = DgetC(DODOL);	/* Allow $ expand within [ ] */
	    if (c == ']')
		break;
	    if (c == '\n' || c == DEOF)
		stderror(ERR_INCBR);
	    if (np >= &name[sizeof(name) / sizeof(Char) - 2])
		stderror(ERR_VARTOOLONG);
	    *np++ = c;
	}
	*np = 0, np = name;
	if (dolp || dolcnt)	/* $ exp must end before ] */
	    stderror(ERR_EXPORD);
	if (!*np)
	    stderror(ERR_SYNTAX);
	if (Isdigit(*np)) {
	    int     i;
E 14

D 14
			while (digit(*np))
				i = i * 10 + *np++ - '0';
D 11
			if ((i < 0 || i > upb) && !any(*np, "-*")) {
E 11
I 11
			if ((i < 0 || i > upb) && !index("-*", *np)) {
E 11
oob:
D 5
				setname(vp->name);
E 5
I 5
				setname(vp->v_name);
E 5
				error("Subscript out of range");
			}
			lwb = i;
			if (!*np)
				upb = lwb, np = "*";
		}
		if (*np == '*')
			np++;
		else if (*np != '-')
			goto syntax;
		else {
			register int i = upb;
E 14
I 14
D 21
	    for (i = 0; Isdigit(*np); i = i * 10 + *np++ - '0');
E 21
I 21
	    for (i = 0; Isdigit(*np); i = i * 10 + *np++ - '0')
		continue;
E 21
	    if ((i < 0 || i > upb) && !any("-*", *np)) {
		dolerror(vp->v_name);
		return;
	    }
	    lwb = i;
	    if (!*np)
		upb = lwb, np = STRstar;
	}
	if (*np == '*')
	    np++;
	else if (*np != '-')
	    stderror(ERR_MISSING, '-');
	else {
	    register int i = upb;
E 14

D 14
			np++;
			if (digit(*np)) {
				i = 0;
				while (digit(*np))
					i = i * 10 + *np++ - '0';
				if (i < 0 || i > upb)
					goto oob;
			}
			if (i < lwb)
				upb = lwb - 1;
			else
				upb = i;
E 14
I 14
	    np++;
	    if (Isdigit(*np)) {
		i = 0;
		while (Isdigit(*np))
		    i = i * 10 + *np++ - '0';
		if (i < 0 || i > upb) {
		    dolerror(vp->v_name);
		    return;
E 14
		}
D 14
		if (lwb == 0) {
			if (upb != 0)
				goto oob;
			upb = -1;
		}
		if (*np)
			goto syntax;
	} else {
		if (subscr > 0)
			if (subscr > upb)
				lwb = 1, upb = 0;
			else
				lwb = upb = subscr;
		unDredc(c);
E 14
I 14
	    }
	    if (i < lwb)
		upb = lwb - 1;
	    else
		upb = i;
E 14
	}
D 14
	if (dimen) {
		char *cp = putn(upb - lwb + 1);
E 14
I 14
	if (lwb == 0) {
	    if (upb != 0) {
		dolerror(vp->v_name);
		return;
	    }
	    upb = -1;
	}
	if (*np)
	    stderror(ERR_SYNTAX);
    }
    else {
	if (subscr > 0)
	    if (subscr > upb)
		lwb = 1, upb = 0;
	    else
		lwb = upb = subscr;
	unDredc(c);
    }
    if (dimen) {
	Char   *cp = putn(upb - lwb + 1);
E 14

D 14
		addla(cp);
		xfree(cp);
	} else {
E 14
I 14
	addla(cp);
	xfree((ptr_t) cp);
    }
    else {
E 14
eatmod:
D 14
		c = DgetC(0);
		if (c == ':') {
			c = DgetC(0), dolmcnt = 1;
			if (c == 'g')
				c = DgetC(0), dolmcnt = 10000;
D 11
			if (!any(c, "htrqxe"))
E 11
I 11
			if (!index("htrqxe", c))
E 11
				error("Bad : mod in $");
			dolmod = c;
			if (c == 'q')
				dolmcnt = 10000;
		} else
			unDredc(c);
		dolnxt = &vp->vec[lwb - 1];
		dolcnt = upb - lwb + 1;
	}
E 14
I 14
	fixDolMod();
	dolnxt = &vp->vec[lwb - 1];
	dolcnt = upb - lwb + 1;
    }
E 14
eatbrac:
D 14
	if (sc == '{') {
		c = Dredc();
		if (c != '}')
			goto syntax;
	}
E 14
I 14
    if (sc == '{') {
	c = Dredc();
	if (c != '}')
	    stderror(ERR_MISSING, '}');
    }
E 14
}

I 14
static void
fixDolMod()
{
    register int c;

    c = DgetC(0);
    if (c == ':') {
D 20
	c = DgetC(0), dolmcnt = 1;
	if (c == 'g')
	    c = DgetC(0), dolmcnt = 10000;
	if (!any("htrqxe", c))
	    stderror(ERR_BADMOD, c);
	dolmod = c;
	if (c == 'q')
	    dolmcnt = 10000;
E 20
I 20
	do {
D 22
	    c = DgetC(0), dolmcnt = 1;
	    if (c == 'g')
		c = DgetC(0), dolmcnt = 10000;
	    if (!any("htrqxe", c))
E 22
I 22
	    c = DgetC(0), dolmcnt = 1, dolwcnt = 1;
	    if (c == 'g' || c == 'a') {
		if (c == 'g')
		    dolmcnt = 10000;
		else
		    dolwcnt = 10000;
		c = DgetC(0);
	    }
	    if ((c == 'g' && dolmcnt != 10000) || 
		(c == 'a' && dolwcnt != 10000)) {
		if (c == 'g')
		    dolmcnt = 10000;
		else
		    dolwcnt = 10000;
		c = DgetC(0); 
	    }

	    if (c == 's') {	/* [eichin:19910926.0755EST] */
		int delimcnt = 2;
		int delim = DgetC(0);
		dolmod[dolnmod++] = c;
		dolmod[dolnmod++] = delim;
		
		if (!delim || letter(delim)
		    || Isdigit(delim) || any(" \t\n", delim)) {
		    seterror(ERR_BADSUBST);
		    break;
		}	
		while ((c = DgetC(0)) != (-1)) {
		    dolmod[dolnmod++] = c;
		    if(c == delim) delimcnt--;
		    if(!delimcnt) break;
		}
		if(delimcnt) {
		    seterror(ERR_BADSUBST);
		    break;
		}
		continue;
	    }
	    if (!any("htrqxes", c))
E 22
		stderror(ERR_BADMOD, c);
	    dolmod[dolnmod++] = c;
	    if (c == 'q')
		dolmcnt = 10000;
	}
	while ((c = DgetC(0)) == ':');
	unDredc(c);
E 20
    }
    else
	unDredc(c);
}

static void
E 14
setDolp(cp)
D 14
	register char *cp;
E 14
I 14
    register Char *cp;
E 14
{
D 14
	register char *dp;
E 14
I 14
    register Char *dp;
I 20
    int i;
E 20
E 14

D 14
	if (dolmod == 0 || dolmcnt == 0) {
		dolp = cp;
		return;
	}
	dp = domod(cp, dolmod);
	if (dp) {
		dolmcnt--;
		addla(dp);
		xfree(dp);
	} else
		addla(cp);
	dolp = "";
I 10
	if (err)
		error(err);
E 14
I 14
D 20
    if (dolmod == 0 || dolmcnt == 0) {
E 20
I 20
    if (dolnmod == 0 || dolmcnt == 0) {
E 20
	dolp = cp;
	return;
    }
D 20
    dp = domod(cp, dolmod);
E 20
I 20
    dp = cp = Strsave(cp);
D 22
    for (i = 0; i < dolnmod; i++)
	if ((dp = domod(cp, dolmod[i]))) {
	    xfree((ptr_t) cp);
	    cp = dp;
	    dolmcnt--;
	}
	else {
E 22
I 22
    for (i = 0; i < dolnmod; i++) {
	/* handle s// [eichin:19910926.0510EST] */
	if(dolmod[i] == 's') {
	    int delim;
	    Char *lhsub, *rhsub, *np;
	    size_t lhlen = 0, rhlen = 0;
	    int didmod = 0;
		
	    delim = dolmod[++i];
	    if (!delim || letter(delim)
		|| Isdigit(delim) || any(" \t\n", delim)) {
		seterror(ERR_BADSUBST);
		break;
	    }
	    lhsub = &dolmod[++i];
	    while(dolmod[i] != delim && dolmod[++i]) {
		lhlen++;
	    }
	    dolmod[i] = 0;
	    rhsub = &dolmod[++i];
	    while(dolmod[i] != delim && dolmod[++i]) {
		rhlen++;
	    }
	    dolmod[i] = 0;

	    do {
		dp = Strstr(cp, lhsub);
		if (dp) {
		    np = (Char *) xmalloc((size_t)
					  ((Strlen(cp) + 1 - lhlen + rhlen) *
					  sizeof(Char)));
		    (void) Strncpy(np, cp, dp - cp);
		    (void) Strcpy(np + (dp - cp), rhsub);
		    (void) Strcpy(np + (dp - cp) + rhlen, dp + lhlen);

		    xfree((ptr_t) cp);
		    dp = cp = np;
		    didmod = 1;
		} else {
		    /* should this do a seterror? */
		    break;
		}
	    }
	    while (dolwcnt == 10000);
	    /*
	     * restore dolmod for additional words
	     */
	    dolmod[i] = rhsub[-1] = delim;
	    if (didmod)
		dolmcnt--;
	    else
		break;
        } else {
	    int didmod = 0;

	    do {
		if ((dp = domod(cp, dolmod[i]))) {
		    didmod = 1;
		    if (Strcmp(cp, dp) == 0) {
			xfree((ptr_t) cp);
			cp = dp;
			break;
		    }
		    else {
			xfree((ptr_t) cp);
			cp = dp;
		    }
		}
		else
		    break;
	    }
	    while (dolwcnt == 10000);
E 22
	    dp = cp;
D 22
	    break;
E 22
I 22
	    if (didmod)
		dolmcnt--;
	    else
		break;
E 22
	}
I 22
    }
E 22

E 20
    if (dp) {
D 20
	dolmcnt--;
E 20
	addla(dp);
	xfree((ptr_t) dp);
    }
I 22
    else
	addla(cp);

E 22
D 20
    else
	addla(cp);
E 20
    dolp = STRNULL;
    if (seterr)
	stderror(ERR_OLD);
E 14
E 10
}

I 14
static void
E 14
unDredc(c)
D 14
	int c;
E 14
I 14
    int     c;
E 14
{

D 14
	Dpeekrd = c;
E 14
I 14
    Dpeekrd = c;
E 14
}

I 14
static int
E 14
Dredc()
{
D 14
	register int c;
E 14
I 14
    register int c;
E 14

D 14
	if (c = Dpeekrd) {
		Dpeekrd = 0;
		return (c);
	}
	if (Dcp && (c = *Dcp++))
		return (c&(QUOTE|TRIM));
	if (*Dvp == 0) {
		Dcp = 0;
		return (DEOF);
	}
	Dcp = *Dvp++;
	return (' ');
E 14
I 14
D 25
    if (c = Dpeekrd) {
E 25
I 25
    if ((c = Dpeekrd) != '\0') {
E 25
	Dpeekrd = 0;
	return (c);
    }
    if (Dcp && (c = *Dcp++))
	return (c & (QUOTE | TRIM));
    if (*Dvp == 0) {
	Dcp = 0;
	return (DEOF);
    }
    Dcp = *Dvp++;
    return (' ');
E 14
}

I 14
static void
E 14
D 5
Dtest(c)
	register int c;
{

	/* Note that c isn't trimmed thus !...:q's aren't lost */
	if (any(c, "$\\'`\""))
		gflag = 1;
}

E 5
Dtestq(c)
D 14
	register int c;
E 14
I 14
    register int c;
E 14
{

D 5
	if (any(c, "\\'`\""))
E 5
I 5
D 14
	if (cmap(c, QUOTES))
E 5
		gflag = 1;
E 14
I 14
    if (cmap(c, QUOTES))
	gflag = 1;
E 14
}

/*
 * Form a shell temporary file (in unit 0) from the words
D 9
 * of the shell input up to a line the same as "term".
E 9
I 9
 * of the shell input up to EOF or a line the same as "term".
E 9
 * Unit 0 should have been closed before this call.
 */
I 14
void
I 19
/*ARGSUSED*/
E 19
E 14
heredoc(term)
D 14
	char *term;
E 14
I 14
D 19
    Char   *term;
E 19
I 19
    Char *term;
E 19
E 14
{
D 14
	register int c;
	char *Dv[2];
	char obuf[BUFSIZ], lbuf[BUFSIZ], mbuf[BUFSIZ];
	int ocnt, lcnt, mcnt;
	register char *lbp, *obp, *mbp;
	char **vp;
	bool quoted;
E 14
I 14
    register int c;
    Char   *Dv[2];
    Char    obuf[BUFSIZ], lbuf[BUFSIZ], mbuf[BUFSIZ];
    int     ocnt, lcnt, mcnt;
    register Char *lbp, *obp, *mbp;
    Char  **vp;
    bool    quoted;
    char   *tmp;
E 14

D 14
	if (creat(shtemp, 0600) < 0)
		Perror(shtemp);
D 5
	close(0);
E 5
I 5
	(void) close(0);
E 5
	if (open(shtemp, 2) < 0) {
		int oerrno = errno;
E 14
I 14
D 28
    if (creat(tmp = short2str(shtemp), 0600) < 0)
E 28
I 28
    tmp = short2str(shtemp);
    if (open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0600) < 0)
E 28
	stderror(ERR_SYSTEM, tmp, strerror(errno));
D 28
    (void) close(0);
    if (open(tmp, O_RDWR) < 0) {
	int     oerrno = errno;
E 14

D 5
		unlink(shtemp);
E 5
I 5
D 14
		(void) unlink(shtemp);
E 5
		errno = oerrno;
		Perror(shtemp);
	}
D 5
	unlink(shtemp);			/* 0 0 inode! */
E 5
I 5
	(void) unlink(shtemp);			/* 0 0 inode! */
E 5
	Dv[0] = term; Dv[1] = NOSTR; gflag = 0;
D 5
	scan(Dv, trim); rscan(Dv, Dtestq); quoted = gflag;
E 5
I 5
	trim(Dv); rscan(Dv, Dtestq); quoted = gflag;
E 5
	ocnt = BUFSIZ; obp = obuf;
E 14
I 14
	(void) unlink(tmp);
	errno = oerrno;
	stderror(ERR_SYSTEM, tmp, strerror(errno));
    }
E 28
    (void) unlink(tmp);		/* 0 0 inode! */
    Dv[0] = term;
    Dv[1] = NULL;
    gflag = 0;
    trim(Dv);
    rscan(Dv, Dtestq);
    quoted = gflag;
    ocnt = BUFSIZ;
    obp = obuf;
    for (;;) {
	/*
	 * Read up a line
	 */
	lbp = lbuf;
	lcnt = BUFSIZ - 4;
E 14
	for (;;) {
D 14
		/*
		 * Read up a line
		 */
		lbp = lbuf; lcnt = BUFSIZ - 4;
		for (;;) {
			c = readc(1);		/* 1 -> Want EOF returns */
D 9
			if (c < 0) {
				setname(term);
				bferr("<< terminator not found");
			}
			if (c == '\n')
E 9
I 9
			if (c < 0 || c == '\n')
E 9
				break;
			if (c &= TRIM) {
				*lbp++ = c;
				if (--lcnt < 0) {
					setname("<<");
					error("Line overflow");
				} 
			}
E 14
I 14
	    c = readc(1);	/* 1 -> Want EOF returns */
	    if (c < 0 || c == '\n')
		break;
D 25
	    if (c &= TRIM) {
E 25
I 25
	    if ((c &= TRIM) != '\0') {
E 25
		*lbp++ = c;
		if (--lcnt < 0) {
		    setname("<<");
		    stderror(ERR_NAME | ERR_OVERFLOW);
E 14
		}
D 14
		*lbp = 0;
E 14
I 14
	    }
	}
	*lbp = 0;
E 14

D 14
		/*
D 9
		 * Compare to terminator -- before expansion
E 9
I 9
		 * Check for EOF or compare to terminator -- before expansion
E 9
		 */
D 9
		if (eq(lbuf, term)) {
E 9
I 9
		if (c < 0 || eq(lbuf, term)) {
E 9
D 5
			write(0, obuf, BUFSIZ - ocnt);
			lseek(0, 0l, 0);
E 5
I 5
			(void) write(0, obuf, BUFSIZ - ocnt);
			(void) lseek(0, (off_t)0, 0);
E 5
			return;
		}
E 14
I 14
	/*
	 * Check for EOF or compare to terminator -- before expansion
	 */
	if (c < 0 || eq(lbuf, term)) {
	    (void) write(0, short2str(obuf), (size_t) (BUFSIZ - ocnt));
	    (void) lseek(0, 0l, L_SET);
	    return;
	}
E 14

D 14
		/*
		 * If term was quoted or -n just pass it on
		 */
		if (quoted || noexec) {
			*lbp++ = '\n'; *lbp = 0;
			for (lbp = lbuf; c = *lbp++;) {
				*obp++ = c;
				if (--ocnt == 0) {
D 5
					write(0, obuf, BUFSIZ);
E 5
I 5
					(void) write(0, obuf, BUFSIZ);
E 5
					obp = obuf; ocnt = BUFSIZ;
				}
			}
			continue;
E 14
I 14
	/*
	 * If term was quoted or -n just pass it on
	 */
	if (quoted || noexec) {
	    *lbp++ = '\n';
	    *lbp = 0;
D 25
	    for (lbp = lbuf; c = *lbp++;) {
E 25
I 25
	    for (lbp = lbuf; (c = *lbp++) != '\0';) {
E 25
		*obp++ = c;
		if (--ocnt == 0) {
		    (void) write(0, short2str(obuf), BUFSIZ);
		    obp = obuf;
		    ocnt = BUFSIZ;
E 14
		}
I 14
	    }
	    continue;
	}
E 14

D 14
		/*
		 * Term wasn't quoted so variable and then command
		 * expand the input line
		 */
		Dcp = lbuf; Dvp = Dv + 1; mbp = mbuf; mcnt = BUFSIZ - 4;
		for (;;) {
			c = DgetC(DODOL);
			if (c == DEOF)
				break;
			if ((c &= TRIM) == 0)
				continue;
			/* \ quotes \ $ ` here */
			if (c =='\\') {
				c = DgetC(0);
D 11
				if (!any(c, "$\\`"))
E 11
I 11
				if (!index("$\\`", c))
E 11
					unDgetC(c | QUOTE), c = '\\';
				else
					c |= QUOTE;
			}
			*mbp++ = c;
			if (--mcnt == 0) {
				setname("<<");
				bferr("Line overflow");
			}
		}
		*mbp++ = 0;
E 14
I 14
	/*
	 * Term wasn't quoted so variable and then command expand the input
	 * line
	 */
	Dcp = lbuf;
	Dvp = Dv + 1;
	mbp = mbuf;
	mcnt = BUFSIZ - 4;
	for (;;) {
	    c = DgetC(DODOL);
	    if (c == DEOF)
		break;
	    if ((c &= TRIM) == 0)
		continue;
	    /* \ quotes \ $ ` here */
	    if (c == '\\') {
		c = DgetC(0);
		if (!any("$\\`", c))
		    unDgetC(c | QUOTE), c = '\\';
		else
		    c |= QUOTE;
	    }
	    *mbp++ = c;
	    if (--mcnt == 0) {
		setname("<<");
		stderror(ERR_NAME | ERR_OVERFLOW);
	    }
	}
	*mbp++ = 0;
E 14

D 14
		/*
		 * If any ` in line do command substitution
		 */
		mbp = mbuf;
D 11
		if (any('`', mbp)) {
E 11
I 11
		if (index(mbp, '`')) {
E 11
			/*
			 * 1 arg to dobackp causes substitution to be literal.
			 * Words are broken only at newlines so that all blanks
			 * and tabs are preserved.  Blank lines (null words)
			 * are not discarded.
			 */
			vp = dobackp(mbuf, 1);
		} else
			/* Setup trivial vector similar to return of dobackp */
			Dv[0] = mbp, Dv[1] = NOSTR, vp = Dv;
E 14
I 14
	/*
	 * If any ` in line do command substitution
	 */
	mbp = mbuf;
	if (any(short2str(mbp), '`')) {
	    /*
	     * 1 arg to dobackp causes substitution to be literal. Words are
	     * broken only at newlines so that all blanks and tabs are
	     * preserved.  Blank lines (null words) are not discarded.
	     */
	    vp = dobackp(mbuf, 1);
	}
	else
	    /* Setup trivial vector similar to return of dobackp */
	    Dv[0] = mbp, Dv[1] = NULL, vp = Dv;
E 14

D 14
		/*
		 * Resurrect the words from the command substitution
		 * each separated by a newline.  Note that the last
		 * newline of a command substitution will have been
		 * discarded, but we put a newline after the last word
		 * because this represents the newline after the last
		 * input line!
		 */
		for (; *vp; vp++) {
			for (mbp = *vp; *mbp; mbp++) {
				*obp++ = *mbp & TRIM;
				if (--ocnt == 0) {
D 5
					write(0, obuf, BUFSIZ);
E 5
I 5
					(void) write(0, obuf, BUFSIZ);
E 5
					obp = obuf; ocnt = BUFSIZ;
				}
			}
			*obp++ = '\n';
			if (--ocnt == 0) {
D 5
				write(0, obuf, BUFSIZ);
E 5
I 5
				(void) write(0, obuf, BUFSIZ);
E 5
				obp = obuf; ocnt = BUFSIZ;
			}
E 14
I 14
	/*
	 * Resurrect the words from the command substitution each separated by
	 * a newline.  Note that the last newline of a command substitution
	 * will have been discarded, but we put a newline after the last word
	 * because this represents the newline after the last input line!
	 */
	for (; *vp; vp++) {
	    for (mbp = *vp; *mbp; mbp++) {
		*obp++ = *mbp & TRIM;
		if (--ocnt == 0) {
		    (void) write(0, short2str(obuf), BUFSIZ);
		    obp = obuf;
		    ocnt = BUFSIZ;
E 14
		}
D 14
		if (pargv)
			blkfree(pargv), pargv = 0;
E 14
I 14
	    }
	    *obp++ = '\n';
	    if (--ocnt == 0) {
		(void) write(0, short2str(obuf), BUFSIZ);
		obp = obuf;
		ocnt = BUFSIZ;
	    }
E 14
	}
I 14
	if (pargv)
	    blkfree(pargv), pargv = 0;
    }
E 14
}
E 1
