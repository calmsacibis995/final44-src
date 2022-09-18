h57078
s 00001/00001/01612
d D 8.2 95/04/29 13:09:00 christos 40 39
c Fixes from Chris Demetriou and Charles Hannum 
e
s 00002/00002/01611
d D 8.1 93/05/31 16:42:28 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/01609
d D 5.29 93/05/27 05:06:38 christos 38 37
c changed _Q,_Q1 to _QF,_QB to avoid conflict with new <ctype.h>
e
s 00011/00011/01602
d D 5.28 93/05/22 19:06:38 christos 37 36
c Fixed gcc -Wall warnings
e
s 00004/00004/01609
d D 5.27 93/03/30 13:55:04 christos 36 35
c Changed f_seek to a union of off_t and Char* to avoid a ggc warning
e
s 00003/00003/01610
d D 5.26 91/11/06 16:09:46 christos 35 34
c Added support for displaying non-printable characters
e
s 00082/00015/01531
d D 5.25 91/11/04 18:24:52 christos 34 33
c Added :a modifier and $foo:s
e
s 00011/00010/01535
d D 5.24 91/10/28 21:28:03 leres 33 32
c Fix gcc "bodyless for/while" warnings.
e
s 00001/00001/01544
d D 5.23 91/09/15 18:00:30 christos 32 31
c added $ to the list of history chars to keep
e
s 00001/00001/01544
d D 5.22 91/09/09 16:46:50 christos 31 30
c Don't expand ! followed by \ (_ESC)
e
s 00005/00000/01540
d D 5.21 91/09/02 16:52:04 christos 30 29
c Clear aliases and evals on error in btoeof
e
s 00056/00028/01484
d D 5.20 91/08/30 21:23:46 christos 29 28
c Bugfix for loops in aliases.
e
s 00002/00002/01510
d D 5.19 91/08/25 17:16:01 christos 28 27
c fixed core dump with multi-line aliases
e
s 00113/00104/01399
d D 5.18 91/07/22 11:47:40 christos 27 26
c support for multiple : modifiers
e
s 00008/00006/01495
d D 5.17 91/07/19 17:31:08 christos 26 25
c stdio based version; brace glob fix; builtin prototypes
e
s 00006/00009/01495
d D 5.16 91/06/08 17:08:52 christos 25 24
c More prototype fixes, Removed TERMIOS define
e
s 00011/00005/01493
d D 5.15 91/06/08 12:20:26 bostic 24 23
c include file pass, csh.h no longer include every .h in the system
c rename sigmast_t to sigset_t to match signal.h; minor pointer cleanups
e
s 00019/00015/01479
d D 5.14 91/06/07 20:57:30 christos 23 22
c static function prototypes
e
s 00004/00012/01490
d D 5.13 91/06/07 11:13:33 bostic 22 21
c rename all the files (they weren't going to diff anyway)
c add function prototypes for extern functions, decls.h -> extern.h
c delete btell function, VFORK #define, lots of other minor cleanups
e
s 00004/00014/01498
d D 5.12 91/06/05 16:33:10 christos 21 20
c Removed -DTELL V6 compatibility flag
e
s 01214/01049/00298
d D 5.11 91/06/04 13:31:41 bostic 20 19
c new version from Christos -- 8-bit clean, lots of bug fixes
c massive changes, including a pass of indent.
e
s 00007/00006/01340
d D 5.10 91/04/04 18:17:48 bostic 19 18
c new copyright; att/bsd/shared
e
s 00003/00003/01343
d D 5.9 91/04/01 17:37:16 bostic 18 17
c setexit -> setjmp, reset -> longjmp, isdir() -> S_ISDIR, ANSI
c Prof. Graham requested semantic changes to #defines in sh.h, removing the
c last vestiges of the PWB/V6 shell
e
s 00009/00009/01337
d D 5.8 91/03/14 12:32:07 bostic 17 16
c copy -> bcopy (more than vax and tahoe now) 
c any -> index (use the faster library routine)
e
s 00009/00000/01337
d D 5.7 88/09/27 00:19:16 edward 16 15
c added check for Hnum < 0 in findev(), to catch bogus entries added
c alias expansion
e
s 00001/00001/01336
d D 5.6 88/05/19 15:38:54 bostic 15 14
c install C version of _doprnt
e
s 00002/00002/01335
d D 5.5 88/01/15 03:33:29 edward 14 13
c fixed labuf overflow (caused by, for example, very long variable expansions)
e
s 00002/00001/01335
d D 5.4 86/03/29 07:37:41 lepreau 13 12
c Minor speedups & cleanups:
c replace letter() et al with ctype-like cmap macros and expand cmap to short
c for new LET and DIG bits; use bzero in private calloc; make btell a macro.
e
s 00003/00003/01333
d D 5.3 85/06/06 13:11:27 edward 12 11
c cleaning up after bozos
e
s 00002/00001/01334
d D 5.2 85/06/06 12:53:50 edward 11 10
c prlex(): don't print trailing space
e
s 00008/00002/01327
d D 5.1 85/06/04 11:03:18 dist 10 9
c Add copyright
e
s 00001/00001/01328
d D 4.9 85/03/19 18:18:26 mckusick 9 8
c check for reference through null pointer
e
s 00012/00004/01317
d D 4.8 85/01/30 12:12:52 edward 8 7
c turn off NBIO when read gets EWOULDBLOCK
e
s 00168/00173/01153
d D 4.7 84/12/13 14:42:24 edward 7 6
c performance
e
s 00003/00004/01323
d D 4.6 84/11/21 11:26:27 ralph 6 5
c turn \newline into space as per documentation.
e
s 00001/00001/01326
d D 4.5 84/09/02 16:58:21 sam 5 4
c argh -- missing #
e
s 00022/00023/01305
d D 4.4 84/09/02 16:51:07 sam 4 3
c I can't stand it, if layer's gonna put this crap in the source code, 
c the least he can do is reformat it to conform to the rest of the code
e
s 00033/00001/01295
d D 4.3 83/11/02 14:53:42 layer 3 2
c mods for filename completion (ifdef'd in with FILEC)
e
s 00001/00001/01295
d D 4.2 83/02/09 14:17:44 sam 2 1
c cleanups from sun
e
s 01296/00000/00000
d D 4.1 80/10/09 12:41:16 bill 1 0
c date and time created 80/10/09 12:41:16 by bill
e
u
U
t
T
I 10
D 19
/*
 * Copyright (c) 1980 Regents of the University of California.
D 12
 * All rights reserved.  The Berkeley software License Agreement
E 12
I 12
 * All rights reserved.  The Berkeley Software License Agreement
E 12
 * specifies the terms and conditions for redistribution.
E 19
I 19
/*-
D 39
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 39
I 39
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
 * %sccs.include.redist.c%
E 19
 */

E 10
I 4
#ifndef lint
E 4
I 1
D 7
static	char *sccsid = "%Z%%M% %I% %G%";
E 7
I 7
D 10
static	char *sccsid = "%W% (Berkeley) %G%";
E 7
I 4
D 5
endif
E 5
I 5
#endif
E 10
I 10
D 12
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint
E 12
I 12
D 19
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 19
I 19
static char sccsid[] = "%W% (Berkeley) %G%";
I 24
#endif /* not lint */
E 24
D 20
#endif /* not lint */
E 20
E 19
E 12
E 10
E 5
E 4

I 20
D 24
#endif				/* not lint */

E 24
I 24
#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
I 25
#if __STDC__
# include <stdarg.h>
#else
# include <varargs.h>
#endif

E 25
E 24
E 20
D 22
#include "sh.h"
E 22
I 22
#include "csh.h"
#include "extern.h"
E 22
I 7
D 13
#include "sh.char.h"
E 13
I 8
D 20
#include <sgtty.h>
E 20
E 8
E 7

/*
D 20
 * C shell
 */

/*
E 20
 * These lexical routines read input and form lists of words.
 * There is some involved processing here, because of the complications
 * of input buffering, and especially because of history substitution.
 */

D 20
char	*word();
E 20
I 20
D 23
static Char *word();
static int getC1();
static void getdol();
static void getexcl();
static struct Hist *findev();
static void setexclp();
static int bgetc();
static void bfree();
static struct wordent *gethent();
static int matchs();
static int getsel();
static struct wordent *getsub();
static Char *subword();
static struct wordent *dosub();
E 23
I 23
static Char	*word __P((void));
static int	 getC1 __P((int));
static void	 getdol __P((void));
static void	 getexcl __P((int));
D 33
static struct Hist 
E 33
I 33
static struct Hist
E 33
		*findev __P((Char *, bool));
static void	 setexclp __P((Char *));
static int	 bgetc __P((void));
static void	 bfree __P((void));
D 33
static struct wordent 
E 33
I 33
static struct wordent
E 33
		*gethent __P((int));
static int	 matchs __P((Char *, Char *));
static int	 getsel __P((int *, int *, int));
D 33
static struct wordent 
E 33
I 33
static struct wordent
E 33
		*getsub __P((struct wordent *));
D 33
static Char 	*subword __P((Char *, int, bool *));
static struct wordent 
E 33
I 33
static Char	*subword __P((Char *, int, bool *));
static struct wordent
E 33
		*dosub __P((int, struct wordent *, bool));
E 23
E 20

/*
D 20
 * Peekc is a peek characer for getC, peekread for readc.
E 20
I 20
 * Peekc is a peek character for getC, peekread for readc.
E 20
 * There is a subtlety here in many places... history routines
 * will read ahead and then insert stuff into the input stream.
 * If they push back a character then they must push it behind
 * the text substituted by the history substitution.  On the other
 * hand in several places we need 2 peek characters.  To make this
 * all work, the history routines read with getC, and make use both
 * of ungetC and unreadc.  The key observation is that the state
 * of getC at the call of a history reference is such that calls
 * to getC from the history routines will always yield calls of
 * readc, unless this peeking is involved.  That is to say that during
 * getexcl the variables lap, exclp, and exclnxt are all zero.
 *
 * Getdol invokes history substitution, hence the extra peek, peekd,
 * which it can ungetD to be before history substitutions.
 */
D 20
char	peekc, peekd;
char	peekread;
E 20
I 20
static Char peekc = 0, peekd = 0;
static Char peekread = 0;
E 20

D 20
char	*exclp;			/* (Tail of) current word from ! subst */
struct	wordent *exclnxt;	/* The rest of the ! subst words */
int	exclc;			/* Count of remainig words in ! subst */
char	*alvecp;		/* "Globp" for alias resubstitution */
E 20
I 20
/* (Tail of) current word from ! subst */
D 24
static Char *exclp = (Char *) 0;
E 24
I 24
static Char *exclp = NULL;
E 24
E 20

I 20
/* The rest of the ! subst words */
D 24
static struct wordent *exclnxt = (struct wordent *) 0;
E 24
I 24
static struct wordent *exclnxt = NULL;
E 24

/* Count of remaining words in ! subst */
static int exclc = 0;

/* "Globp" for alias resubstitution */
D 24
static Char *alvecp = (Char *) 0;
E 24
I 24
D 34
static Char *alvecp = NULL;
E 34
I 34
Char *alvecp = NULL;
E 34
I 29
int aret = F_SEEK;
E 29
E 24

E 20
/*
I 20
 * Labuf implements a general buffer for lookahead during lexical operations.
 * Text which is to be placed in the input stream can be stuck here.
 * We stick parsed ahead $ constructs during initial input,
 * process id's from `$$', and modified variable values (from qualifiers
 * during expansion in sh.dol.c) here.
 */
static Char labuf[BUFSIZ];

/*
E 20
 * Lex returns to its caller not only a wordlist (as a "var" parameter)
 * but also whether a history substitution occurred.  This is used in
 * the main (process) routine to determine whether to echo, and also
 * when called by the alias routine to determine whether to keep the
 * argument list.
 */
D 20
bool	hadhist;
E 20
I 20
static bool hadhist = 0;
E 20

I 7
D 20
char getCtmp;
E 20
I 20
/*
 * Avoid alias expansion recursion via \!#
 */
int     hleft;

static Char getCtmp;

E 20
#define getC(f)		((getCtmp = peekc) ? (peekc = 0, getCtmp) : getC1(f))
E 7
#define	ungetC(c)	peekc = c
#define	ungetD(c)	peekd = c

I 20
int
E 20
lex(hp)
D 20
	register struct wordent *hp;
E 20
I 20
    register struct wordent *hp;
E 20
{
D 20
	register struct wordent *wdp;
	int c;
E 20
I 20
    register struct wordent *wdp;
    int     c;
E 20

D 20
	lineloc = btell();
	hp->next = hp->prev = hp;
	hp->word = "";
	alvecp = 0, hadhist = 0;
	do
		c = readc(0);
	while (c == ' ' || c == '\t');
	if (c == HISTSUB && intty)
		/* ^lef^rit	from tty is short !:s^lef^rit */
		getexcl(c);
	else
		unreadc(c);
	wdp = hp;
	/*
	 * The following loop is written so that the links needed
	 * by freelex will be ready and rarin to go even if it is
	 * interrupted.
	 */
	do {
D 7
		register struct wordent *new = (struct wordent *) calloc(1, sizeof *wdp);
E 7
I 7
		register struct wordent *new = (struct wordent *) xalloc(sizeof *wdp);
E 20
I 20
D 22
    lineloc = btell();
E 22
I 22
D 29
    lineloc = fseekp;
E 29
I 29
    btell(&lineloc);
E 29
E 22
    hp->next = hp->prev = hp;
    hp->word = STRNULL;
D 29
    alvecp = 0, hadhist = 0;
E 29
I 29
    hadhist = 0;
E 29
    do
	c = readc(0);
    while (c == ' ' || c == '\t');
    if (c == HISTSUB && intty)
	/* ^lef^rit	from tty is short !:s^lef^rit */
	getexcl(c);
    else
	unreadc(c);
    wdp = hp;
    /*
     * The following loop is written so that the links needed by freelex will
     * be ready and rarin to go even if it is interrupted.
     */
    do {
	register struct wordent *new;
E 20
E 7

I 7
D 20
		new->word = 0;
E 7
		new->prev = wdp;
		new->next = hp;
		wdp->next = new;
		wdp = new;
		wdp->word = word();
	} while (wdp->word[0] != '\n');
	hp->prev = wdp;
	return (hadhist);
E 20
I 20
	new = (struct wordent *) xmalloc((size_t) sizeof(*wdp));
	new->word = 0;
	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	wdp = new;
	wdp->word = word();
    } while (wdp->word[0] != '\n');
    hp->prev = wdp;
    return (hadhist);
E 20
}

I 20
void
E 20
D 26
prlex(sp0)
E 26
I 26
prlex(fp, sp0)
    FILE *fp;
E 26
D 20
	struct wordent *sp0;
E 20
I 20
    struct wordent *sp0;
E 20
{
D 20
	register struct wordent *sp = sp0->next;
E 20
I 20
    register struct wordent *sp = sp0->next;
E 20

D 20
	for (;;) {
		printf("%s", sp->word);
		sp = sp->next;
		if (sp == sp0)
			break;
D 11
		printf(" ");
E 11
I 11
		if (sp->word[0] != '\n')
D 15
			putchar(' ');
E 15
I 15
			cshputchar(' ');
E 15
E 11
	}
E 20
I 20
    for (;;) {
D 26
	xprintf("%s", short2str(sp->word));
E 26
I 26
D 35
	(void) fprintf(fp, "%s", short2str(sp->word));
E 35
I 35
	(void) fprintf(fp, "%s", vis_str(sp->word));
E 35
E 26
	sp = sp->next;
	if (sp == sp0)
	    break;
	if (sp->word[0] != '\n')
D 26
	    xputchar(' ');
E 26
I 26
	    (void) fputc(' ', fp);
E 26
    }
E 20
}

I 20
void
E 20
copylex(hp, fp)
D 20
	register struct wordent *hp;
D 7
	struct wordent *fp;
E 7
I 7
	register struct wordent *fp;
E 20
I 20
    register struct wordent *hp;
    register struct wordent *fp;
E 20
E 7
{
D 20
	register struct wordent *wdp;
E 20
I 20
    register struct wordent *wdp;
E 20

D 20
	wdp = hp;
	fp = fp->next;
	do {
D 7
		register struct wordent *new = (struct wordent *) calloc(1, sizeof *wdp);
E 7
I 7
		register struct wordent *new = (struct wordent *) xalloc(sizeof *wdp);
E 20
I 20
    wdp = hp;
    fp = fp->next;
    do {
	register struct wordent *new;
E 20
E 7

D 20
		new->prev = wdp;
		new->next = hp;
		wdp->next = new;
		wdp = new;
		wdp->word = savestr(fp->word);
		fp = fp->next;
	} while (wdp->word[0] != '\n');
	hp->prev = wdp;
E 20
I 20
	new = (struct wordent *) xmalloc((size_t) sizeof(*wdp));
	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	wdp = new;
	wdp->word = Strsave(fp->word);
	fp = fp->next;
    } while (wdp->word[0] != '\n');
    hp->prev = wdp;
E 20
}

I 20
void
E 20
freelex(vp)
D 20
	register struct wordent *vp;
E 20
I 20
    register struct wordent *vp;
E 20
{
D 20
	register struct wordent *fp;
E 20
I 20
    register struct wordent *fp;
E 20

D 20
	while (vp->next != vp) {
		fp = vp->next;
		vp->next = fp->next;
D 7
		xfree(fp->word);
		xfree((char *)fp);
E 7
I 7
		XFREE(fp->word)
		XFREE((char *)fp)
E 7
	}
	vp->prev = vp;
E 20
I 20
    while (vp->next != vp) {
	fp = vp->next;
	vp->next = fp->next;
	xfree((ptr_t) fp->word);
	xfree((ptr_t) fp);
    }
    vp->prev = vp;
E 20
}

D 7
char	*WORDMETA =	"# '`\"\t;&<>()|\n";

E 7
D 20
char *
E 20
I 20
static Char *
E 20
word()
{
D 20
	register char c, c1;
	register char *wp;
	char wbuf[BUFSIZ];
	register bool dolflg;
	register int i;
E 20
I 20
    register Char c, c1;
    register Char *wp;
    Char    wbuf[BUFSIZ];
    register bool dolflg;
    register int i;
E 20

D 20
	wp = wbuf;
	i = BUFSIZ - 4;
E 20
I 20
    wp = wbuf;
    i = BUFSIZ - 4;
E 20
loop:
D 7
	c = getC(DOALL);
	switch (c) {
E 7
I 7
D 20
	while ((c = getC(DOALL)) == ' ' || c == '\t')
		;
	if (cmap(c, _META|_ESC))
		switch (c) {
		case '&':
		case '|':
		case '<':
		case '>':
			*wp++ = c;
			c1 = getC(DOALL);
			if (c1 == c)
				*wp++ = c1;
			else
				ungetC(c1);
			goto ret;
E 20
I 20
D 33
    while ((c = getC(DOALL)) == ' ' || c == '\t');
E 33
I 33
    while ((c = getC(DOALL)) == ' ' || c == '\t')
	continue;
E 33
    if (cmap(c, _META | _ESC))
	switch (c) {
	case '&':
	case '|':
	case '<':
	case '>':
	    *wp++ = c;
	    c1 = getC(DOALL);
	    if (c1 == c)
		*wp++ = c1;
	    else
		ungetC(c1);
	    goto ret;
E 20
E 7

D 7
	case ' ':
	case '\t':
		goto loop;

	case '`':
	case '\'':
	case '"':
		*wp++ = c, --i, c1 = c;
		dolflg = c == '"' ? DOALL : DOEXCL;
		for (;;) {
			c = getC(dolflg);
			if (c == c1)
E 7
I 7
D 20
		case '#':
			if (intty)
E 7
				break;
D 7
			if (c == '\n') {
				seterrc("Unmatched ", c1);
				ungetC(c);
				goto ret;
			}
			if (c == '\\') {
E 7
I 7
			c = 0;
			do {
				c1 = c;
E 7
				c = getC(0);
D 7
				if (c == HIST)
					c |= QUOTE;
D 6
				else {
					if (c == '\n' && c1 != '`')
						c |= QUOTE;
E 6
I 6
				else if (c == '\n')
					c = ' ';
				else
E 6
					ungetC(c), c = '\\';
D 6
				}
E 6
			}
			if (--i <= 0)
				goto toochars;
			*wp++ = c;
		}
		*wp++ = c, --i;
		goto pack;
E 7
I 7
			} while (c != '\n');
			if (c1 == '\\')
				goto loop;
			/* fall into ... */
E 20
I 20
	case '#':
	    if (intty)
		break;
	    c = 0;
	    do {
		c1 = c;
		c = getC(0);
	    } while (c != '\n');
	    if (c1 == '\\')
		goto loop;
	    /* fall into ... */
E 20
E 7

D 7
	case '&':
	case '|':
	case '<':
	case '>':
		*wp++ = c;
		c1 = getC(DOALL);
		if (c1 == c)
			*wp++ = c1;
		else
			ungetC(c1);
		goto ret;

	case '#':
		if (intty)
			break;
		if (wp != wbuf) {
			ungetC(c);
E 7
I 7
D 20
		case ';':
		case '(':
		case ')':
		case '\n':
			*wp++ = c;
E 7
			goto ret;
E 20
I 20
	case ';':
	case '(':
	case ')':
	case '\n':
	    *wp++ = c;
	    goto ret;
E 20
D 7
		}
		c = 0;
		do {
			c1 = c;
			c = getC(0);
		} while (c != '\n');
		if (c1 == '\\')
			goto loop;
		/* fall into ... */
E 7

D 7
	case ';':
	case '(':
	case ')':
	case '\n':
		*wp++ = c;
		goto ret;

casebksl:
	case '\\':
		c = getC(0);
		if (c == '\n') {
			if (onelflg == 1)
				onelflg = 2;
			goto loop;
		}
		if (c != HIST)
			*wp++ = '\\', --i;
		c |= QUOTE;
		break;
	}
	ungetC(c);
pack:
	for (;;) {
		c = getC(DOALL);
		if (c == '\\') {
E 7
I 7
D 20
		case '\\':
E 7
			c = getC(0);
			if (c == '\n') {
				if (onelflg == 1)
					onelflg = 2;
D 7
				goto ret;
E 7
I 7
				goto loop;
E 7
			}
			if (c != HIST)
				*wp++ = '\\', --i;
E 20
I 20
	case '\\':
	    c = getC(0);
	    if (c == '\n') {
		if (onelflg == 1)
		    onelflg = 2;
		goto loop;
	    }
	    if (c != HIST)
		*wp++ = '\\', --i;
	    c |= QUOTE;
	}
    c1 = 0;
    dolflg = DOALL;
    for (;;) {
	if (c1) {
	    if (c == c1) {
		c1 = 0;
		dolflg = DOALL;
	    }
	    else if (c == '\\') {
		c = getC(0);
		if (c == HIST)
		    c |= QUOTE;
		else {
		    if (c == '\n')
			/*
			 * if (c1 == '`') c = ' '; else
			 */
E 20
			c |= QUOTE;
I 20
		    ungetC(c);
		    c = '\\';
E 20
		}
D 7
		if (any(c, WORDMETA + intty)) {
			ungetC(c);
			if (any(c, "\"'`"))
				goto loop;
			goto ret;
E 7
I 7
D 20
	c1 = 0;
	dolflg = DOALL;
	for (;;) {
		if (c1) {
			if (c == c1) {
				c1 = 0;
				dolflg = DOALL;
			} else if (c == '\\') {
				c = getC(0);
				if (c == HIST)
					c |= QUOTE;
				else {
					if (c == '\n')
						/*
						if (c1 == '`')
							c = ' ';
						else
						*/
							c |= QUOTE;
					ungetC(c);
					c = '\\';
				}
			} else if (c == '\n') {
				seterrc("Unmatched ", c1);
				ungetC(c);
				break;
			}
		} else if (cmap(c, _META|_Q|_Q1|_ESC)) {
			if (c == '\\') {
				c = getC(0);
				if (c == '\n') {
					if (onelflg == 1)
						onelflg = 2;
					break;
				}
				if (c != HIST)
					*wp++ = '\\', --i;
				c |= QUOTE;
			} else if (cmap(c, _Q|_Q1)) {		/* '"` */
				c1 = c;
				dolflg = c == '"' ? DOALL : DOEXCL;
			} else if (c != '#' || !intty) {
				ungetC(c);
				break;
			}
E 20
I 20
	    }
	    else if (c == '\n') {
		seterror(ERR_UNMATCHED, c1);
		ungetC(c);
		break;
	    }
	}
D 38
	else if (cmap(c, _META | _Q | _Q1 | _ESC)) {
E 38
I 38
	else if (cmap(c, _META | _QF | _QB | _ESC)) {
E 38
	    if (c == '\\') {
		c = getC(0);
		if (c == '\n') {
		    if (onelflg == 1)
			onelflg = 2;
		    break;
E 20
E 7
		}
D 7
		if (--i <= 0)
			goto toochars;
		*wp++ = c;
E 7
I 7
D 20
		if (--i > 0) {
			*wp++ = c;
			c = getC(dolflg);
		} else {
			seterr("Word too long");
			wp = &wbuf[1];
			break;
		}
E 20
I 20
		if (c != HIST)
		    *wp++ = '\\', --i;
		c |= QUOTE;
	    }
D 38
	    else if (cmap(c, _Q | _Q1)) {	/* '"` */
E 38
I 38
	    else if (cmap(c, _QF | _QB)) {	/* '"` */
E 38
		c1 = c;
		dolflg = c == '"' ? DOALL : DOEXCL;
	    }
	    else if (c != '#' || !intty) {
		ungetC(c);
		break;
	    }
E 20
E 7
	}
I 20
	if (--i > 0) {
	    *wp++ = c;
	    c = getC(dolflg);
	}
	else {
	    seterror(ERR_WTOOLONG);
	    wp = &wbuf[1];
	    break;
	}
    }
E 20
D 7
toochars:
	seterr("Word too long");
	wp = &wbuf[1];
E 7
ret:
D 20
	*wp = 0;
	return (savestr(wbuf));
E 20
I 20
    *wp = 0;
    return (Strsave(wbuf));
E 20
}

I 20
static int
E 20
D 7
getC(flag)
E 7
I 7
getC1(flag)
E 7
D 20
	register int flag;
E 20
I 20
    register int flag;
E 20
{
D 20
	register char c;
E 20
I 20
    register Char c;
E 20

D 20
top:
E 20
I 20
    while (1) {
E 20
D 37
	if (c = peekc) {
E 37
I 37
	if ((c = peekc) != '\0') {
E 37
D 20
		peekc = 0;
		return (c);
E 20
I 20
	    peekc = 0;
	    return (c);
E 20
	}
	if (lap) {
D 7
		c = *lap++;
		if (c == 0) {
E 7
I 7
D 20
		if ((c = *lap++) == 0)
E 7
			lap = 0;
D 7
			goto top;
E 7
I 7
		else {
			if (cmap(c, _META|_Q|_Q1))
				c |= QUOTE;
			return (c);
E 7
		}
E 20
I 20
	    if ((c = *lap++) == 0)
		lap = 0;
	    else {
D 38
		if (cmap(c, _META | _Q | _Q1))
E 38
I 38
		if (cmap(c, _META | _QF | _QB))
E 38
		    c |= QUOTE;
		return (c);
	    }
E 20
D 7
		if (any(c, WORDMETA + intty))
			c |= QUOTE;
		return (c);
E 7
	}
D 37
	if (c = peekd) {
E 37
I 37
	if ((c = peekd) != '\0') {
E 37
D 20
		peekd = 0;
		return (c);
E 20
I 20
	    peekd = 0;
	    return (c);
E 20
	}
	if (exclp) {
D 20
		if (c = *exclp++)
			return (c);
		if (exclnxt && --exclc >= 0) {
			exclnxt = exclnxt->next;
			setexclp(exclnxt->word);
			return (' ');
		}
		exclp = 0;
		exclnxt = 0;
E 20
I 20
D 37
	    if (c = *exclp++)
E 37
I 37
	    if ((c = *exclp++) != '\0')
E 37
		return (c);
	    if (exclnxt && --exclc >= 0) {
		exclnxt = exclnxt->next;
		setexclp(exclnxt->word);
		return (' ');
	    }
	    exclp = 0;
	    exclnxt = 0;
E 20
	}
	if (exclnxt) {
D 20
		exclnxt = exclnxt->next;
		if (--exclc < 0)
			exclnxt = 0;
		else
			setexclp(exclnxt->word);
		goto top;
E 20
I 20
	    exclnxt = exclnxt->next;
	    if (--exclc < 0)
		exclnxt = 0;
	    else
		setexclp(exclnxt->word);
	    continue;
E 20
	}
	c = readc(0);
	if (c == '$' && (flag & DODOL)) {
D 20
		getdol();
		goto top;
E 20
I 20
	    getdol();
	    continue;
E 20
	}
	if (c == HIST && (flag & DOEXCL)) {
D 20
		getexcl(0);
		goto top;
E 20
I 20
	    getexcl(0);
	    continue;
E 20
	}
D 20
	return (c);
E 20
I 20
	break;
    }
    return (c);
E 20
}

I 20
static void
E 20
getdol()
{
D 20
	register char *np;
	char name[40];
	register int c;
	int sc;
	bool special = 0;
E 20
I 20
    register Char *np, *ep;
    Char    name[4 * MAXVARLEN + 1];
    register int c;
    int     sc;
    bool    special = 0, toolong;
E 20

D 20
	np = name, *np++ = '$';
	c = sc = getC(DOEXCL);
D 17
	if (any(c, "\t \n")) {
E 17
I 17
	if (index("\t \n", c)) {
E 17
		ungetD(c);
		ungetC('$' | QUOTE);
		return;
	}
	if (c == '{')
		*np++ = c, c = getC(DOEXCL);
	if (c == '#' || c == '?')
		special++, *np++ = c, c = getC(DOEXCL);
	*np++ = c;
	switch (c) {
	
	case '<':
	case '$':
		if (special)
			goto vsyn;
		goto ret;
E 20
I 20
    np = name, *np++ = '$';
    c = sc = getC(DOEXCL);
    if (any("\t \n", c)) {
	ungetD(c);
	ungetC('$' | QUOTE);
	return;
    }
    if (c == '{')
	*np++ = c, c = getC(DOEXCL);
    if (c == '#' || c == '?')
	special++, *np++ = c, c = getC(DOEXCL);
    *np++ = c;
    switch (c) {
E 20

D 20
	case '\n':
		ungetD(c);
		np--;
		goto vsyn;
E 20
I 20
    case '<':
    case '$':
I 34
    case '!':
E 34
	if (special)
	    seterror(ERR_SPDOLLT);
	*np = 0;
	addla(name);
	return;
E 20

D 20
	case '*':
		if (special)
			goto vsyn;
		goto ret;
E 20
I 20
    case '\n':
	ungetD(c);
	np--;
	seterror(ERR_NEWLINE);
	*np = 0;
	addla(name);
	return;
E 20

D 20
	default:
		if (digit(c)) {
/*
 * let $?0 pass for now
			if (special)
				goto vsyn;
*/
			while (digit(c = getC(DOEXCL))) {
				if (np < &name[sizeof name / 2])
					*np++ = c;
			}
		} else if (letter(c))
			while (letter(c = getC(DOEXCL))) {
				if (np < &name[sizeof name / 2])
					*np++ = c;
			}
E 20
I 20
    case '*':
	if (special)
	    seterror(ERR_SPSTAR);
	*np = 0;
	addla(name);
	return;

    default:
	toolong = 0;
	if (Isdigit(c)) {
#ifdef notdef
	    /* let $?0 pass for now */
	    if (special) {
		seterror(ERR_DIGIT);
		*np = 0;
		addla(name);
		return;
	    }
#endif
	    /* we know that np < &name[4] */
	    ep = &np[MAXVARLEN];
D 37
	    while (c = getC(DOEXCL)) {
E 37
I 37
	    while ((c = getC(DOEXCL)) != '\0'){
E 37
		if (!Isdigit(c))
		    break;
		if (np < ep)
		    *np++ = c;
E 20
		else
D 20
			goto vsyn;
E 20
I 20
		    toolong = 1;
	    }
E 20
	}
D 20
	if (c == '[') {
		*np++ = c;
		do {
			c = getC(DOEXCL);
			if (c == '\n') {
				ungetD(c);
				np--;
				goto vsyn;
			}
			if (np >= &name[sizeof name - 8])
				goto vsyn;
			*np++ = c;
		} while (c != ']');
		c = getC(DOEXCL);
E 20
I 20
	else if (letter(c)) {
	    /* we know that np < &name[4] */
	    ep = &np[MAXVARLEN];
	    toolong = 0;
D 37
	    while (c = getC(DOEXCL)) {
E 37
I 37
	    while ((c = getC(DOEXCL)) != '\0') {
E 37
		/* Bugfix for ${v123x} from Chris Torek, DAS DEC-90. */
		if (!letter(c) && !Isdigit(c))
		    break;
		if (np < ep)
		    *np++ = c;
		else
		    toolong = 1;
	    }
E 20
	}
D 20
	if (c == ':') {
		*np++ = c, c = getC(DOEXCL);
		if (c == 'g')
			*np++ = c, c = getC(DOEXCL);
		*np++ = c;
D 17
		if (!any(c, "htrqxe"))
E 17
I 17
		if (!index("htrqxe", c))
E 17
			goto vsyn;
	} else
E 20
I 20
	else {
	    *np = 0;
	    seterror(ERR_VARILL);
	    addla(name);
	    return;
	}
	if (toolong) {
	    seterror(ERR_VARTOOLONG);
	    *np = 0;
	    addla(name);
	    return;
	}
	break;
    }
    if (c == '[') {
	*np++ = c;
	/*
	 * Name up to here is a max of MAXVARLEN + 8.
	 */
	ep = &np[2 * MAXVARLEN + 8];
	do {
	    /*
	     * Michael Greim: Allow $ expansion to take place in selector
	     * expressions. (limits the number of characters returned)
	     */
	    c = getC(DOEXCL | DODOL);
	    if (c == '\n') {
E 20
		ungetD(c);
D 20
	if (sc == '{') {
		c = getC(DOEXCL);
		if (c != '}') {
			ungetC(c);
			goto vsyn;
		}
E 20
I 20
		np--;
		seterror(ERR_NLINDEX);
		*np = 0;
		addla(name);
		return;
	    }
	    if (np < ep)
E 20
		*np++ = c;
I 20
	} while (c != ']');
	*np = '\0';
	if (np >= ep) {
	    seterror(ERR_SELOVFL);
	    addla(name);
	    return;
E 20
	}
D 20
ret:
	*np = 0;
	addla(name);
	return;
E 20
I 20
	c = getC(DOEXCL);
    }
    /*
     * Name up to here is a max of 2 * MAXVARLEN + 8.
     */
    if (c == ':') {
	/*
	 * if the :g modifier is followed by a newline, then error right away!
	 * -strike
	 */
E 20

D 20
vsyn:
	seterr("Variable syntax");
	goto ret;
E 20
I 20
D 34
	int     gmodflag = 0;
E 34
I 34
	int     gmodflag = 0, amodflag = 0;
E 34

D 27
	*np++ = c, c = getC(DOEXCL);
	if (c == 'g')
	    gmodflag++, *np++ = c, c = getC(DOEXCL);
	*np++ = c;
	if (!any("htrqxe", c)) {
	    if (gmodflag && c == '\n')
		stderror(ERR_VARSYN);	/* strike */
	    seterror(ERR_VARMOD, c);
	    *np = 0;
	    addla(name);
	    return;
E 27
I 27
	do {
	    *np++ = c, c = getC(DOEXCL);
D 34
	    if (c == 'g')
		gmodflag++, *np++ = c, c = getC(DOEXCL);
E 34
I 34
	    if (c == 'g' || c == 'a') {
		if (c == 'g')
		    gmodflag++;
		else
		    amodflag++;
		*np++ = c; c = getC(DOEXCL);
	    }
	    if ((c == 'g' && !gmodflag) || (c == 'a' && !amodflag)) {
		if (c == 'g')
		    gmodflag++;
		else
		    amodflag++;
		*np++ = c; c = getC(DOEXCL);
	    }
E 34
	    *np++ = c;
D 34
	    if (!any("htrqxe", c)) {
		if (gmodflag && c == '\n')
E 34
I 34
	    /* scan s// [eichin:19910926.0512EST] */
	    if (c == 's') {
		int delimcnt = 2;
		int delim = getC(0);
		*np++ = delim;
		
		if (!delim || letter(delim)
		    || Isdigit(delim) || any(" \t\n", delim)) {
		    seterror(ERR_BADSUBST);
		    break;
		}	
		while ((c = getC(0)) != (-1)) {
		    *np++ = c;
		    if(c == delim) delimcnt--;
		    if(!delimcnt) break;
		}
		if(delimcnt) {
		    seterror(ERR_BADSUBST);
		    break;
		}
		c = 's';
	    }
	    if (!any("htrqxes", c)) {
		if ((amodflag || gmodflag) && c == '\n')
E 34
		    stderror(ERR_VARSYN);	/* strike */
		seterror(ERR_VARMOD, c);
		*np = 0;
		addla(name);
		return;
	    }
E 27
	}
I 27
	while ((c = getC(DOEXCL)) == ':');
	ungetD(c);
E 27
    }
    else
	ungetD(c);
    if (sc == '{') {
	c = getC(DOEXCL);
	if (c != '}') {
	    ungetD(c);
	    seterror(ERR_MISSING, '}');
	    *np = 0;
	    addla(name);
	    return;
	}
	*np++ = c;
    }
    *np = 0;
    addla(name);
    return;
E 20
}

I 20
void
E 20
addla(cp)
D 20
	char *cp;
E 20
I 20
    Char   *cp;
E 20
{
D 20
	char buf[BUFSIZ];
E 20
I 20
    Char    buf[BUFSIZ];
E 20

D 14
	if (lap != 0 && strlen(cp) + strlen(lap) >= sizeof (labuf) - 4) {
		seterr("Expansion buf ovflo");
E 14
I 14
D 20
	if (strlen(cp) + (lap ? strlen(lap) : 0) >= sizeof (labuf) - 4) {
		seterr("Expansion buffer overflow");
E 14
		return;
	}
	if (lap)
D 7
		strcpy(buf, lap);
	strcpy(labuf, cp);
E 7
I 7
		(void) strcpy(buf, lap);
	(void) strcpy(labuf, cp);
E 7
	if (lap)
D 7
		strcat(labuf, buf);
E 7
I 7
		(void) strcat(labuf, buf);
E 7
	lap = labuf;
E 20
I 20
    if (Strlen(cp) + (lap ? Strlen(lap) : 0) >=
	(sizeof(labuf) - 4) / sizeof(Char)) {
	seterror(ERR_EXPOVFL);
	return;
    }
    if (lap)
	(void) Strcpy(buf, lap);
    (void) Strcpy(labuf, cp);
    if (lap)
	(void) Strcat(labuf, buf);
    lap = labuf;
E 20
}

D 20
char	lhsb[32];
char	slhs[32];
char	rhsb[64];
int	quesarg;
E 20
I 20
static Char lhsb[32];
static Char slhs[32];
static Char rhsb[64];
static int quesarg;
E 20

I 20
static void
E 20
getexcl(sc)
D 20
	char sc;
E 20
I 20
D 23
    Char    sc;
E 23
I 23
    int    sc;
E 23
E 20
{
D 20
	register struct wordent *hp, *ip;
	int left, right, dol;
	register int c;
E 20
I 20
    register struct wordent *hp, *ip;
    int     left, right, dol;
    register int c;
E 20

D 20
	if (sc == 0) {
		sc = getC(0);
		if (sc != '{') {
			ungetC(sc);
			sc = 0;
		}
E 20
I 20
    if (sc == 0) {
	sc = getC(0);
	if (sc != '{') {
	    ungetC(sc);
	    sc = 0;
E 20
	}
D 20
	quesarg = -1;
	lastev = eventno;
	hp = gethent(sc);
	if (hp == 0)
		return;
	hadhist = 1;
	dol = 0;
	if (hp == alhistp)
		for (ip = hp->next->next; ip != alhistt; ip = ip->next)
			dol++;
	else
		for (ip = hp->next->next; ip != hp->prev; ip = ip->next)
			dol++;
	left = 0, right = dol;
	if (sc == HISTSUB) {
		ungetC('s'), unreadc(HISTSUB), c = ':';
		goto subst;
	}
E 20
I 20
    }
    quesarg = -1;
    lastev = eventno;
    hp = gethent(sc);
    if (hp == 0)
	return;
    hadhist = 1;
    dol = 0;
    if (hp == alhistp)
	for (ip = hp->next->next; ip != alhistt; ip = ip->next)
	    dol++;
    else
	for (ip = hp->next->next; ip != hp->prev; ip = ip->next)
	    dol++;
    left = 0, right = dol;
    if (sc == HISTSUB) {
	ungetC('s'), unreadc(HISTSUB), c = ':';
	goto subst;
    }
    c = getC(0);
    if (!any(":^$*-%", c))
	goto subst;
    left = right = -1;
    if (c == ':') {
E 20
	c = getC(0);
D 17
	if (!any(c, ":^$*-%"))
E 17
I 17
D 20
	if (!index(":^$*-%", c))
E 17
		goto subst;
	left = right = -1;
	if (c == ':') {
		c = getC(0);
		unreadc(c);
		if (letter(c) || c == '&') {
			c = ':';
			left = 0, right = dol;
			goto subst;
		}
	} else
		ungetC(c);
E 20
I 20
	unreadc(c);
	if (letter(c) || c == '&') {
	    c = ':';
	    left = 0, right = dol;
	    goto subst;
	}
    }
    else
	ungetC(c);
    if (!getsel(&left, &right, dol))
	return;
    c = getC(0);
    if (c == '*')
	ungetC(c), c = '-';
    if (c == '-') {
E 20
	if (!getsel(&left, &right, dol))
D 20
		return;
E 20
I 20
	    return;
E 20
	c = getC(0);
D 20
	if (c == '*')
		ungetC(c), c = '-';
	if (c == '-') {
		if (!getsel(&left, &right, dol))
			return;
		c = getC(0);
	}
E 20
I 20
    }
E 20
subst:
D 20
	exclc = right - left + 1;
	while (--left >= 0)
		hp = hp->next;
	if (sc == HISTSUB || c == ':') {
		do {
			hp = getsub(hp);
			c = getC(0);
		} while (c == ':');
	}
	unreadc(c);
	if (sc == '{') {
		c = getC(0);
		if (c != '}')
			seterr("Bad ! form");
	}
	exclnxt = hp;
E 20
I 20
    exclc = right - left + 1;
    while (--left >= 0)
	hp = hp->next;
    if (sc == HISTSUB || c == ':') {
	do {
	    hp = getsub(hp);
	    c = getC(0);
	} while (c == ':');
    }
    unreadc(c);
    if (sc == '{') {
	c = getC(0);
	if (c != '}')
	    seterror(ERR_BADBANG);
    }
    exclnxt = hp;
E 20
}

D 20
struct wordent *
E 20
I 20
static struct wordent *
E 20
getsub(en)
D 20
	struct wordent *en;
E 20
I 20
    struct wordent *en;
E 20
{
D 20
	register char *cp;
	int delim;
	register int c;
	int sc;
	bool global = 0;
	char orhsb[sizeof rhsb];
E 20
I 20
    register Char *cp;
    int     delim;
    register int c;
    int     sc;
D 34
    bool global = 0;
E 34
I 34
    bool global;
E 34
    Char    orhsb[sizeof(rhsb) / sizeof(Char)];
E 20

D 20
	exclnxt = 0;
	sc = c = getC(0);
	if (c == 'g')
		global++, c = getC(0);
	switch (c) {
E 20
I 20
D 27
    exclnxt = 0;
    sc = c = getC(0);
    if (c == 'g')
	global ++, sc = c = getC(0);
E 27
I 27
    do {
	exclnxt = 0;
I 34
	global = 0;
E 34
	sc = c = getC(0);
D 34
	if (c == 'g')
	    global++, sc = c = getC(0);
E 34
I 34
	if (c == 'g' || c == 'a') {
	    global |= (c == 'g') ? 1 : 2;
	    sc = c = getC(0);
	}
	if (((c =='g') && !(global & 1)) || ((c == 'a') && !(global & 2))) {
	    global |= (c == 'g') ? 1 : 2;
	    sc = c = getC(0);
	}
E 34
E 27
E 20

D 20
	case 'p':
		justpr++;
		goto ret;
E 20
I 20
D 27
    switch (c) {
    case 'p':
	justpr++;
	return (en);
E 27
I 27
	switch (c) {
	case 'p':
	    justpr++;
	    return (en);
E 27
E 20

D 20
	case 'x':
	case 'q':
		global++;
		/* fall into ... */
E 20
I 20
D 27
    case 'x':
    case 'q':
	global ++;
E 27
I 27
	case 'x':
	case 'q':
D 34
	    global++;
E 34
I 34
	    global |= 1;
E 34
E 27
E 20

D 20
	case 'h':
	case 'r':
	case 't':
	case 'e':
		break;
E 20
I 20
D 27
	/* fall into ... */
E 27
I 27
	    /* fall into ... */
E 27
E 20

D 20
	case '&':
		if (slhs[0] == 0) {
			seterr("No prev sub");
			goto ret;
		}
D 7
		strcpy(lhsb, slhs);
E 7
I 7
		(void) strcpy(lhsb, slhs);
E 7
		break;
E 20
I 20
D 27
    case 'h':
    case 'r':
    case 't':
    case 'e':
	break;
E 27
I 27
	case 'h':
	case 'r':
	case 't':
	case 'e':
	    break;
E 27
E 20

D 20
/*
	case '~':
		if (lhsb[0] == 0)
			goto badlhs;
		break;
*/
E 20
I 20
D 27
    case '&':
	if (slhs[0] == 0) {
	    seterror(ERR_NOSUBST);
	    return (en);
	}
	(void) Strcpy(lhsb, slhs);
	break;
E 27
I 27
	case '&':
	    if (slhs[0] == 0) {
		seterror(ERR_NOSUBST);
		return (en);
	    }
	    (void) Strcpy(lhsb, slhs);
	    break;
E 27
E 20

D 20
	case 's':
		delim = getC(0);
D 17
		if (letter(delim) || digit(delim) || any(delim, " \t\n")) {
E 17
I 17
		if (letter(delim) || digit(delim) || index(" \t\n", delim)) {
E 17
			unreadc(delim);
bads:
			lhsb[0] = 0;
			seterr("Bad substitute");
			goto ret;
		}
		cp = lhsb;
		for (;;) {
			c = getC(0);
			if (c == '\n') {
				unreadc(c);
D 7
				goto bads;
E 7
I 7
				break;
E 7
			}
			if (c == delim)
				break;
			if (cp > &lhsb[sizeof lhsb - 2])
				goto bads;
			if (c == '\\') {
				c = getC(0);
				if (c != delim && c != '\\')
					*cp++ = '\\';
			}
			*cp++ = c;
		}
		if (cp != lhsb)
			*cp++ = 0;
		else if (lhsb[0] == 0) {
/*badlhs:*/
			seterr("No prev lhs");
			goto ret;
		}
		cp = rhsb;
D 7
		strcpy(orhsb, cp);
E 7
I 7
		(void) strcpy(orhsb, cp);
E 7
		for (;;) {
			c = getC(0);
			if (c == '\n') {
				unreadc(c);
				break;
			}
			if (c == delim)
				break;
/*
			if (c == '~') {
				if (&cp[strlen(orhsb)] > &rhsb[sizeof rhsb - 2])
					goto toorhs;
D 7
				strcpy(cp, orhsb);
E 7
I 7
				(void) strcpy(cp, orhsb);
E 7
				cp = strend(cp);
				continue;
			}
*/
			if (cp > &rhsb[sizeof rhsb - 2]) {
/*toorhs:*/
				seterr("Rhs too long");
				goto ret;
			}
			if (c == '\\') {
				c = getC(0);
				if (c != delim /* && c != '~' */)
					*cp++ = '\\';
			}
			*cp++ = c;
		}
		*cp++ = 0;
		break;
E 20
I 20
#ifdef notdef
D 27
    case '~':
	if (lhsb[0] == 0)
	    goto badlhs;
	break;
E 27
I 27
	case '~':
	    if (lhsb[0] == 0)
		goto badlhs;
	    break;
E 27
#endif
E 20

D 20
	default:
		if (c == '\n')
			unreadc(c);
		seterrc("Bad ! modifier: ", c);
		goto ret;
E 20
I 20
D 27
    case 's':
	delim = getC(0);
	if (letter(delim) || Isdigit(delim) || any(" \t\n", delim)) {
	    unreadc(delim);
	    lhsb[0] = 0;
	    seterror(ERR_BADSUBST);
	    return (en);
E 20
	}
D 7
	strcpy(slhs, lhsb);
E 7
I 7
D 20
	(void) strcpy(slhs, lhsb);
E 7
	if (exclc)
		en = dosub(sc, en, global);
ret:
E 20
I 20
	cp = lhsb;
	for (;;) {
	    c = getC(0);
	    if (c == '\n') {
		unreadc(c);
		break;
	    }
	    if (c == delim)
		break;
	    if (cp > &lhsb[sizeof(lhsb) / sizeof(Char) - 2]) {
E 27
I 27
	case 's':
	    delim = getC(0);
	    if (letter(delim) || Isdigit(delim) || any(" \t\n", delim)) {
		unreadc(delim);
E 27
		lhsb[0] = 0;
		seterror(ERR_BADSUBST);
		return (en);
	    }
D 27
	    if (c == '\\') {
E 27
I 27
	    cp = lhsb;
	    for (;;) {
E 27
		c = getC(0);
D 27
		if (c != delim && c != '\\')
		    *cp++ = '\\';
E 27
I 27
		if (c == '\n') {
		    unreadc(c);
		    break;
		}
		if (c == delim)
		    break;
		if (cp > &lhsb[sizeof(lhsb) / sizeof(Char) - 2]) {
		    lhsb[0] = 0;
		    seterror(ERR_BADSUBST);
		    return (en);
		}
		if (c == '\\') {
		    c = getC(0);
		    if (c != delim && c != '\\')
			*cp++ = '\\';
		}
		*cp++ = c;
E 27
	    }
D 27
	    *cp++ = c;
	}
	if (cp != lhsb)
	    *cp++ = 0;
	else if (lhsb[0] == 0) {
	    seterror(ERR_LHS);
	    return (en);
	}
	cp = rhsb;
	(void) Strcpy(orhsb, cp);
	for (;;) {
	    c = getC(0);
	    if (c == '\n') {
		unreadc(c);
		break;
E 27
I 27
	    if (cp != lhsb)
		*cp++ = 0;
	    else if (lhsb[0] == 0) {
		seterror(ERR_LHS);
		return (en);
E 27
	    }
D 27
	    if (c == delim)
		break;
E 27
I 27
	    cp = rhsb;
	    (void) Strcpy(orhsb, cp);
	    for (;;) {
		c = getC(0);
		if (c == '\n') {
		    unreadc(c);
		    break;
		}
		if (c == delim)
		    break;
E 27
#ifdef notdef
D 27
	    if (c == '~') {
		if (&cp[Strlen(orhsb)] > &rhsb[sizeof(rhsb) / sizeof(Char) - 2])
		    goto toorhs;
		(void) Strcpy(cp, orhsb);
		cp = Strend(cp);
		continue;
	    }
E 27
I 27
		if (c == '~') {
D 33
		    if (&cp[Strlen(orhsb)] > &rhsb[sizeof(rhsb) / 
E 33
I 33
		    if (&cp[Strlen(orhsb)] > &rhsb[sizeof(rhsb) /
E 33
						   sizeof(Char) - 2])
			goto toorhs;
		    (void) Strcpy(cp, orhsb);
		    cp = Strend(cp);
		    continue;
		}
E 27
#endif
D 27
	    if (cp > &rhsb[sizeof(rhsb) / sizeof(Char) - 2]) {
		seterror(ERR_RHSLONG);
		return (en);
E 27
I 27
		if (cp > &rhsb[sizeof(rhsb) / sizeof(Char) - 2]) {
		    seterror(ERR_RHSLONG);
		    return (en);
		}
		if (c == '\\') {
		    c = getC(0);
		    if (c != delim /* && c != '~' */ )
			*cp++ = '\\';
		}
		*cp++ = c;
E 27
	    }
D 27
	    if (c == '\\') {
		c = getC(0);
		if (c != delim /* && c != '~' */ )
		    *cp++ = '\\';
	    }
	    *cp++ = c;
	}
	*cp++ = 0;
	break;
E 27
I 27
	    *cp++ = 0;
	    break;
E 27

D 27
    default:
	if (c == '\n')
	    unreadc(c);
	seterror(ERR_BADBANGMOD, c);
E 20
	return (en);
E 27
I 27
	default:
	    if (c == '\n')
		unreadc(c);
	    seterror(ERR_BADBANGMOD, c);
	    return (en);
	}
	(void) Strcpy(slhs, lhsb);
	if (exclc)
	    en = dosub(sc, en, global);
E 27
I 20
    }
D 27
    (void) Strcpy(slhs, lhsb);
    if (exclc)
	en = dosub(sc, en, global);
E 27
I 27
    while ((c = getC(0)) == ':');
    unreadc(c);
E 27
    return (en);
E 20
}

D 20
struct wordent *
E 20
I 20
static struct wordent *
E 20
dosub(sc, en, global)
D 20
	int sc;
	struct wordent *en;
	bool global;
E 20
I 20
    int     sc;
    struct wordent *en;
    bool global;
E 20
{
D 20
	struct wordent lex;
	bool didsub = 0;
	struct wordent *hp = &lex;
	register struct wordent *wdp;
	register int i = exclc;
E 20
I 20
    struct wordent lexi;
D 34
    bool    didsub = 0;
E 34
I 34
    bool    didsub = 0, didone = 0;
E 34
    struct wordent *hp = &lexi;
    register struct wordent *wdp;
    register int i = exclc;
E 20

D 20
	wdp = hp;
	while (--i >= 0) {
		register struct wordent *new = (struct wordent *) calloc(1, sizeof *wdp);
E 20
I 20
    wdp = hp;
    while (--i >= 0) {
D 34
	register struct wordent *new;
E 34
I 34
	register struct wordent *new = 
		(struct wordent *) xcalloc(1, sizeof *wdp);
E 34
E 20

D 20
		new->prev = wdp;
		new->next = hp;
		wdp->next = new;
		wdp = new;
		en = en->next;
		wdp->word = global || didsub == 0 ?
		    subword(en->word, sc, &didsub) : savestr(en->word);
	}
	if (didsub == 0)
		seterr("Modifier failed");
	hp->prev = wdp;
	return (&enthist(-1000, &lex, 0)->Hlex);
E 20
I 20
D 34
	new = (struct wordent *) xcalloc(1, sizeof *wdp);
E 34
	new->word = 0;
	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	wdp = new;
	en = en->next;
D 34
	wdp->word = (en->word && (global ||didsub == 0)) ?
	    subword(en->word, sc, &didsub) : Strsave(en->word);
E 34
I 34
	if (en->word) {
	    Char *tword, *otword;

	    if ((global & 1) || didsub == 0) {
		tword = subword(en->word, sc, &didone);
		if (didone)
		    didsub = 1;
		if (global & 2) {
		    while (didone && tword != STRNULL) {
			otword = tword;
			tword = subword(otword, sc, &didone);
			if (Strcmp(tword, otword) == 0) {
			    xfree((ptr_t) otword);
			    break;
			}
			else
			    xfree((ptr_t) otword);
		    }
		}
	    }
	    else
		tword = Strsave(en->word);
	    wdp->word = tword;
	}
E 34
    }
    if (didsub == 0)
	seterror(ERR_MODFAIL);
    hp->prev = wdp;
    return (&enthist(-1000, &lexi, 0)->Hlex);
E 20
}

D 20
char *
E 20
I 20
static Char *
E 20
subword(cp, type, adid)
D 20
	char *cp;
	int type;
	bool *adid;
E 20
I 20
    Char   *cp;
    int     type;
    bool   *adid;
E 20
{
D 20
	char wbuf[BUFSIZ];
	register char *wp, *mp, *np;
	register int i;
E 20
I 20
    Char    wbuf[BUFSIZ];
    register Char *wp, *mp, *np;
    register int i;
E 20

I 34
    *adid = 0;
E 34
D 20
	switch (type) {
E 20
I 20
    switch (type) {
E 20

D 20
	case 'r':
I 7
	case 'e':
E 7
	case 'h':
	case 't':
	case 'q':
	case 'x':
		wp = domod(cp, type);
		if (wp == 0)
			return (savestr(cp));
		*adid = 1;
		return (wp);
E 20
I 20
    case 'r':
    case 'e':
    case 'h':
    case 't':
    case 'q':
    case 'x':
	wp = domod(cp, type);
	if (wp == 0)
	    return (Strsave(cp));
	*adid = 1;
	return (wp);
E 20

D 20
	default:
		wp = wbuf;
		i = BUFSIZ - 4;
		for (mp = cp; *mp; mp++)
			if (matchs(mp, lhsb)) {
				for (np = cp; np < mp;)
					*wp++ = *np++, --i;
				for (np = rhsb; *np; np++) switch (*np) {
E 20
I 20
    default:
	wp = wbuf;
	i = BUFSIZ - 4;
	for (mp = cp; *mp; mp++)
	    if (matchs(mp, lhsb)) {
		for (np = cp; np < mp;)
		    *wp++ = *np++, --i;
		for (np = rhsb; *np; np++)
		    switch (*np) {
E 20

D 20
				case '\\':
					if (np[1] == '&')
						np++;
					/* fall into ... */
E 20
I 20
		    case '\\':
			if (np[1] == '&')
			    np++;
			/* fall into ... */
E 20

D 20
				default:
					if (--i < 0)
						goto ovflo;
					*wp++ = *np;
					continue;
E 20
I 20
		    default:
			if (--i < 0) {
			    seterror(ERR_SUBOVFL);
			    return (STRNULL);
			}
			*wp++ = *np;
			continue;
E 20

D 20
				case '&':
					i -= strlen(lhsb);
					if (i < 0)
						goto ovflo;
					*wp = 0;
D 7
					strcat(wp, lhsb);
E 7
I 7
					(void) strcat(wp, lhsb);
E 7
					wp = strend(wp);
					continue;
				}
				mp += strlen(lhsb);
				i -= strlen(mp);
				if (i < 0) {
ovflo:
					seterr("Subst buf ovflo");
					return ("");
				}
				*wp = 0;
D 7
				strcat(wp, mp);
E 7
I 7
				(void) strcat(wp, mp);
E 7
				*adid = 1;
				return (savestr(wbuf));
E 20
I 20
		    case '&':
			i -= Strlen(lhsb);
			if (i < 0) {
			    seterror(ERR_SUBOVFL);
			    return (STRNULL);
E 20
			}
D 20
		return (savestr(cp));
	}
E 20
I 20
			*wp = 0;
			(void) Strcat(wp, lhsb);
			wp = Strend(wp);
			continue;
		    }
		mp += Strlen(lhsb);
		i -= Strlen(mp);
		if (i < 0) {
		    seterror(ERR_SUBOVFL);
		    return (STRNULL);
		}
		*wp = 0;
		(void) Strcat(wp, mp);
		*adid = 1;
		return (Strsave(wbuf));
	    }
	return (Strsave(cp));
    }
E 20
}

D 20
char *
E 20
I 20
Char   *
E 20
domod(cp, type)
D 20
	char *cp;
	int type;
E 20
I 20
    Char   *cp;
    int     type;
E 20
{
D 20
	register char *wp, *xp;
	register int c;
E 20
I 20
    register Char *wp, *xp;
    register int c;
E 20

D 20
	switch (type) {
E 20
I 20
    switch (type) {
E 20

D 20
	case 'x':
	case 'q':
		wp = savestr(cp);
		for (xp = wp; c = *xp; xp++)
			if ((c != ' ' && c != '\t') || type == 'q')
				*xp |= QUOTE;
		return (wp);
E 20
I 20
    case 'x':
    case 'q':
	wp = Strsave(cp);
D 37
	for (xp = wp; c = *xp; xp++)
E 37
I 37
	for (xp = wp; (c = *xp) != '\0'; xp++)
E 37
	    if ((c != ' ' && c != '\t') || type == 'q')
		*xp |= QUOTE;
	return (wp);
E 20

D 20
	case 'h':
	case 't':
D 7
		if (!any('/', cp))	/* what if :h :t are both the same? */
			return (0);
E 7
I 7
D 17
		if (!any('/', cp))
E 17
I 17
		if (!index(cp, '/'))
E 17
			return (type == 't' ? savestr(cp) : 0);
E 7
		wp = strend(cp);
		while (*--wp != '/')
			continue;
		if (type == 'h')
D 7
take:
E 7
			xp = savestr(cp), xp[wp - cp] = 0;
E 20
I 20
    case 'h':
    case 't':
	if (!any(short2str(cp), '/'))
	    return (type == 't' ? Strsave(cp) : 0);
	wp = Strend(cp);
	while (*--wp != '/')
	    continue;
	if (type == 'h')
	    xp = Strsave(cp), xp[wp - cp] = 0;
	else
	    xp = Strsave(wp + 1);
	return (xp);

    case 'e':
    case 'r':
	wp = Strend(cp);
	for (wp--; wp >= cp && *wp != '/'; wp--)
	    if (*wp == '.') {
		if (type == 'e')
		    xp = Strsave(wp + 1);
E 20
		else
D 20
			xp = savestr(wp + 1);
E 20
I 20
		    xp = Strsave(cp), xp[wp - cp] = 0;
E 20
		return (xp);
D 20

	case 'e':
	case 'r':
		wp = strend(cp);
		for (wp--; wp >= cp && *wp != '/'; wp--)
			if (*wp == '.') {
				if (type == 'e')
					xp = savestr(wp + 1);
				else
					xp = savestr(cp), xp[wp - cp] = 0;
				return (xp);
			}
		return (savestr(type == 'e' ? "" : cp));
	}
	return (0);
E 20
I 20
	    }
	return (Strsave(type == 'e' ? STRNULL : cp));
I 34
    default:
	break;
E 34
    }
    return (0);
E 20
}

I 20
static int
E 20
matchs(str, pat)
D 20
	register char *str, *pat;
E 20
I 20
    register Char *str, *pat;
E 20
{
D 20

	while (*str && *pat && *str == *pat)
		str++, pat++;
	return (*pat == 0);
E 20
I 20
    while (*str && *pat && *str == *pat)
	str++, pat++;
    return (*pat == 0);
E 20
}

I 20
static int
E 20
getsel(al, ar, dol)
D 20
	register int *al, *ar;
	int dol;
E 20
I 20
    register int *al, *ar;
    int     dol;
E 20
{
D 20
	register int c = getC(0);
	register int i;
	bool first = *al < 0;
E 20
I 20
    register int c = getC(0);
    register int i;
    bool    first = *al < 0;
E 20

D 20
	switch (c) {
E 20
I 20
    switch (c) {
E 20

D 20
	case '%':
		if (quesarg == -1)
			goto bad;
		if (*al < 0)
			*al = quesarg;
		*ar = quesarg;
		break;
E 20
I 20
    case '%':
	if (quesarg == -1) {
	    seterror(ERR_BADBANGARG);
	    return (0);
	}
	if (*al < 0)
	    *al = quesarg;
	*ar = quesarg;
	break;
E 20

D 20
	case '-':
		if (*al < 0) {
			*al = 0;
			*ar = dol - 1;
			unreadc(c);
		}
		return (1);
E 20
I 20
    case '-':
	if (*al < 0) {
	    *al = 0;
	    *ar = dol - 1;
	    unreadc(c);
	}
	return (1);
E 20

D 20
	case '^':
		if (*al < 0)
			*al = 1;
		*ar = 1;
		break;
E 20
I 20
    case '^':
	if (*al < 0)
	    *al = 1;
	*ar = 1;
	break;
E 20

D 20
	case '$':
		if (*al < 0)
			*al = dol;
		*ar = dol;
		break;
E 20
I 20
    case '$':
	if (*al < 0)
	    *al = dol;
	*ar = dol;
	break;
E 20

D 20
	case '*':
		if (*al < 0)
			*al = 1;
		*ar = dol;
		if (*ar < *al) {
			*ar = 0;
			*al = 1;
			return (1);
		}
		break;

	default:
		if (digit(c)) {
			i = 0;
			while (digit(c)) {
				i = i * 10 + c - '0';
				c = getC(0);
			}
			if (i < 0)
				i = dol + 1;
			if (*al < 0)
				*al = i;
			*ar = i;
		} else
			if (*al < 0)
				*al = 0, *ar = dol;
			else
				*ar = dol - 1;
		unreadc(c);
		break;
E 20
I 20
    case '*':
	if (*al < 0)
	    *al = 1;
	*ar = dol;
	if (*ar < *al) {
	    *ar = 0;
	    *al = 1;
	    return (1);
E 20
	}
D 20
	if (first) {
E 20
I 20
	break;

    default:
	if (Isdigit(c)) {
	    i = 0;
	    while (Isdigit(c)) {
		i = i * 10 + c - '0';
E 20
		c = getC(0);
D 20
		unreadc(c);
D 17
		if (any(c, "-$*"))
E 17
I 17
		if (index("-$*", c))
E 17
			return (1);
E 20
I 20
	    }
	    if (i < 0)
		i = dol + 1;
	    if (*al < 0)
		*al = i;
	    *ar = i;
E 20
	}
D 20
	if (*al > *ar || *ar > dol) {
bad:
		seterr("Bad ! arg selector");
		return (0);
	}
	return (1);
E 20
I 20
	else if (*al < 0)
	    *al = 0, *ar = dol;
	else
	    *ar = dol - 1;
	unreadc(c);
	break;
    }
    if (first) {
	c = getC(0);
	unreadc(c);
	if (any("-$*", c))
	    return (1);
    }
    if (*al > *ar || *ar > dol) {
	seterror(ERR_BADBANGARG);
	return (0);
    }
    return (1);
E 20

}

D 20
struct wordent *
E 20
I 20
static struct wordent *
E 20
gethent(sc)
D 20
	int sc;
E 20
I 20
    int     sc;
E 20
{
D 20
	register struct Hist *hp;
	register char *np;
	register int c;
	int event;
	bool back = 0;
E 20
I 20
    register struct Hist *hp;
    register Char *np;
    register int c;
    int     event;
    bool    back = 0;
E 20

D 20
	c = sc == HISTSUB ? HIST : getC(0);
	if (c == HIST) {
		if (alhistp)
			return (alhistp);
		event = eventno;
		goto skip;
	}
E 20
I 20
    c = sc == HISTSUB ? HIST : getC(0);
    if (c == HIST) {
	if (alhistp)
	    return (alhistp);
	event = eventno;
    }
    else
E 20
	switch (c) {

	case ':':
	case '^':
	case '$':
	case '*':
	case '%':
D 20
		ungetC(c);
		if (lastev == eventno && alhistp)
			return (alhistp);
		event = lastev;
		break;
E 20
I 20
	    ungetC(c);
	    if (lastev == eventno && alhistp)
		return (alhistp);
	    event = lastev;
	    break;
E 20

I 20
	case '#':		/* !# is command being typed in (mrh) */
	    if (--hleft == 0) {
		seterror(ERR_HISTLOOP);
		return (0);
	    }
	    else
		return (&paraml);
	    /* NOTREACHED */

E 20
	case '-':
D 20
		back = 1;
		c = getC(0);
		goto number;
E 20
I 20
	    back = 1;
	    c = getC(0);
	    /* FALLSTHROUGH */
E 20

D 20
	case '#':			/* !# is command being typed in (mrh) */
		return(&paraml);

E 20
	default:
D 17
		if (any(c, "(=~")) {
E 17
I 17
D 20
		if (index("(=~", c)) {
E 17
			unreadc(c);
			ungetC(HIST);
			return (0);
		}
		if (digit(c))
			goto number;
		np = lhsb;
D 17
		while (!any(c, ": \t\\\n}")) {
E 17
I 17
		while (!index(": \t\\\n}", c)) {
E 17
			if (np < &lhsb[sizeof lhsb - 2])
				*np++ = c;
			c = getC(0);
		}
E 20
I 20
	    if (any("(=~", c)) {
E 20
		unreadc(c);
D 20
		if (np == lhsb) {
			ungetC(HIST);
			return (0);
		}
		*np++ = 0;
		hp = findev(lhsb, 0);
		if (hp)
			lastev = hp->Hnum;
		return (&hp->Hlex);
E 20
I 20
		ungetC(HIST);
		return (0);
	    }
	    np = lhsb;
	    event = 0;
D 28
	    while (!any(": \t\\\n}", c)) {
E 28
I 28
D 29
	    while (!any(": \t\\\n}'\"", c)) {
E 29
I 29
D 31
	    while (!cmap(c, _META | _Q | _Q1) && !any("{}:", c)) {
E 31
I 31
D 32
	    while (!cmap(c, _ESC | _META | _Q | _Q1) && !any("{}:", c)) {
E 32
I 32
D 38
	    while (!cmap(c, _ESC | _META | _Q | _Q1) && !any("${}:", c)) {
E 38
I 38
	    while (!cmap(c, _ESC | _META | _QF | _QB) && !any("${}:", c)) {
E 38
E 32
E 31
E 29
E 28
		if (event != -1 && Isdigit(c))
		    event = event * 10 + c - '0';
		else
		    event = -1;
		if (np < &lhsb[sizeof(lhsb) / sizeof(Char) - 2])
		    *np++ = c;
		c = getC(0);
	    }
	    unreadc(c);
	    if (np == lhsb) {
		ungetC(HIST);
		return (0);
	    }
	    *np++ = 0;
	    if (event != -1) {
		/*
		 * History had only digits
		 */
		if (back)
		    event = eventno + (alhistp == 0) - (event ? event : 0);
		break;
	    }
	    hp = findev(lhsb, 0);
	    if (hp)
		lastev = hp->Hnum;
	    return (&hp->Hlex);
E 20

	case '?':
D 20
		np = lhsb;
		for (;;) {
			c = getC(0);
			if (c == '\n') {
				unreadc(c);
				break;
			}
			if (c == '?')
				break;
			if (np < &lhsb[sizeof lhsb - 2])
				*np++ = c;
E 20
I 20
	    np = lhsb;
	    for (;;) {
		c = getC(0);
		if (c == '\n') {
		    unreadc(c);
		    break;
E 20
		}
D 20
		if (np == lhsb) {
			if (lhsb[0] == 0) {
				seterr("No prev search");
				return (0);
			}
		} else
			*np++ = 0;
		hp = findev(lhsb, 1);
		if (hp)
			lastev = hp->Hnum;
		return (&hp->Hlex);

	number:
		event = 0;
		while (digit(c)) {
			event = event * 10 + c - '0';
			c = getC(0);
E 20
I 20
		if (c == '?')
		    break;
		if (np < &lhsb[sizeof(lhsb) / sizeof(Char) - 2])
		    *np++ = c;
	    }
	    if (np == lhsb) {
		if (lhsb[0] == 0) {
		    seterror(ERR_NOSEARCH);
		    return (0);
E 20
		}
D 20
		if (back)
			event = eventno + (alhistp == 0) - (event ? event : 0);
		unreadc(c);
		break;
E 20
I 20
	    }
	    else
		*np++ = 0;
	    hp = findev(lhsb, 1);
	    if (hp)
		lastev = hp->Hnum;
	    return (&hp->Hlex);
E 20
	}
D 20
skip:
	for (hp = Histlist.Hnext; hp; hp = hp->Hnext)
		if (hp->Hnum == event) {
			hp->Href = eventno;
			lastev = hp->Hnum;
			return (&hp->Hlex);
		}
	np = putn(event);
	noev(np);
	return (0);
E 20
I 20

    for (hp = Histlist.Hnext; hp; hp = hp->Hnext)
	if (hp->Hnum == event) {
	    hp->Href = eventno;
	    lastev = hp->Hnum;
	    return (&hp->Hlex);
	}
    np = putn(event);
D 35
    seterror(ERR_NOEVENT, short2str(np));
E 35
I 35
    seterror(ERR_NOEVENT, vis_str(np));
E 35
    return (0);
E 20
}

D 20
struct Hist *
E 20
I 20
static struct Hist *
E 20
findev(cp, anyarg)
D 20
	char *cp;
	bool anyarg;
E 20
I 20
    Char   *cp;
    bool    anyarg;
E 20
{
D 20
	register struct Hist *hp;
E 20
I 20
    register struct Hist *hp;
E 20

D 7
	for (hp = Histlist.Hnext; hp; hp = hp->Hnext)
		if (matchev(hp, cp, anyarg))
			return (hp);
E 7
I 7
D 20
	for (hp = Histlist.Hnext; hp; hp = hp->Hnext) {
		char *dp;
		register char *p, *q;
		register struct wordent *lp = hp->Hlex.next;
		int argno = 0;
E 20
I 20
    for (hp = Histlist.Hnext; hp; hp = hp->Hnext) {
	Char   *dp;
	register Char *p, *q;
	register struct wordent *lp = hp->Hlex.next;
	int     argno = 0;
E 20

I 16
D 20
		/*
		 * The entries added by alias substitution don't
		 * have a newline but do have a negative event number.
		 * Savehist() trims off these entries, but it happens
		 * before alias expansion, too early to delete those
		 * from the previous command.
		 */
		if (hp->Hnum < 0)
			continue;
E 16
		if (lp->word[0] == '\n')
			continue;
		if (!anyarg) {
			p = cp;
			q = lp->word;
			do
				if (!*p)
					return (hp);
			while (*p++ == *q++);
			continue;
		}
		do {
			for (dp = lp->word; *dp; dp++) {
				p = cp;
				q = dp;
				do
					if (!*p) {
						quesarg = argno;
						return (hp);
					}
				while (*p++ == *q++);
			}
			lp = lp->next;
			argno++;
		} while (lp->word[0] != '\n');
E 20
I 20
	/*
	 * The entries added by alias substitution don't have a newline but do
	 * have a negative event number. Savehist() trims off these entries,
	 * but it happens before alias expansion, too early to delete those
	 * from the previous command.
	 */
	if (hp->Hnum < 0)
	    continue;
	if (lp->word[0] == '\n')
	    continue;
	if (!anyarg) {
	    p = cp;
	    q = lp->word;
	    do
		if (!*p)
		    return (hp);
	    while (*p++ == *q++);
	    continue;
E 20
	}
E 7
D 20
	noev(cp);
	return (0);
E 20
I 20
	do {
	    for (dp = lp->word; *dp; dp++) {
		p = cp;
		q = dp;
		do
		    if (!*p) {
			quesarg = argno;
			return (hp);
		    }
		while (*p++ == *q++);
	    }
	    lp = lp->next;
	    argno++;
	} while (lp->word[0] != '\n');
    }
D 35
    seterror(ERR_NOEVENT, short2str(cp));
E 35
I 35
    seterror(ERR_NOEVENT, vis_str(cp));
E 35
    return (0);
E 20
}

D 20
noev(cp)
	char *cp;
{
E 20

D 20
	seterr2(cp, ": Event not found");
}

E 20
I 20
static void
E 20
D 7
matchev(hp, cp, anyarg)
	register struct Hist *hp;
	char *cp;
	bool anyarg;
{
	register char *dp;
	struct wordent *lp = &hp->Hlex;
	int argno = 0;

	for (;;) {
		lp = lp->next;
		if (lp->word[0] == '\n')
			return (0);
		for (dp = lp->word; *dp; dp++) {
			if (matchs(dp, cp)) {
				if (anyarg)
					quesarg = argno;
				return (1);
			}
			if (!anyarg)
				return (0);
		}
		argno++;
	}
}

E 7
setexclp(cp)
D 20
	register char *cp;
E 20
I 20
    register Char *cp;
E 20
{
D 20

D 9
	if (cp[0] == '\n')
E 9
I 9
	if (cp && cp[0] == '\n')
E 9
		return;
	exclp = cp;
E 20
I 20
    if (cp && cp[0] == '\n')
	return;
    exclp = cp;
E 20
}

I 20
void
E 20
unreadc(c)
D 20
	char c;
E 20
I 20
D 22
    Char    c;
E 22
I 22
    int    c;
E 22
E 20
{
D 20

	peekread = c;
E 20
I 20
    peekread = c;
E 20
}

I 20
int
E 20
readc(wanteof)
D 20
	bool wanteof;
E 20
I 20
    bool    wanteof;
E 20
{
D 20
	register int c;
	static sincereal;
E 20
I 20
    register int c;
    static  sincereal;
E 20

I 29
    aret = F_SEEK;
E 29
D 20
	if (c = peekread) {
		peekread = 0;
		return (c);
	}
E 20
I 20
D 37
    if (c = peekread) {
E 37
I 37
    if ((c = peekread) != '\0') {
E 37
	peekread = 0;
	return (c);
    }
E 20
top:
I 29
    aret = F_SEEK;
E 29
D 20
	if (alvecp) {
		if (c = *alvecp++)
			return (c);
		if (*alvec) {
			alvecp = *alvec++;
			return (' ');
		}
E 20
I 20
    if (alvecp) {
D 29
	if (c = *alvecp++)
E 29
I 29
	aret = A_SEEK;
D 33
	if (c = *alvecp++) 
E 33
I 33
D 37
	if (c = *alvecp++)
E 37
I 37
	if ((c = *alvecp++) != '\0')
E 37
E 33
E 29
	    return (c);
D 28
	if (*alvec) {
E 28
I 28
	if (alvec && *alvec) {
E 28
D 29
	    alvecp = *alvec++;
	    return (' ');
E 29
I 29
		alvecp = *alvec++;
		return (' ');
E 29
E 20
	}
I 29
	else {
	    aret = F_SEEK;
	    alvecp = NULL;
	    return('\n');
	}
E 29
D 20
	if (alvec) {
		if (alvecp = *alvec) {
			alvec++;
			goto top;
		}
		/* Infinite source! */
		return ('\n');
E 20
I 20
    }
    if (alvec) {
D 37
	if (alvecp = *alvec) {
E 37
I 37
	if ((alvecp = *alvec) != '\0') {
E 37
	    alvec++;
	    goto top;
E 20
	}
D 20
	if (evalp) {
		if (c = *evalp++)
			return (c);
		if (*evalvec) {
			evalp = *evalvec++;
			return (' ');
		}
		evalp = 0;
E 20
I 20
	/* Infinite source! */
	return ('\n');
    }
    if (evalp) {
I 29
	aret = E_SEEK;
E 29
D 37
	if (c = *evalp++)
E 37
I 37
	if ((c = *evalp++) != '\0')
E 37
	    return (c);
D 29
	if (*evalvec) {
E 29
I 29
	if (evalvec && *evalvec) {
E 29
	    evalp = *evalvec++;
	    return (' ');
E 20
	}
I 29
	aret = F_SEEK;
E 29
D 20
	if (evalvec) {
		if (evalvec == (char **)1) {
			doneinp = 1;
D 18
			reset();
E 18
I 18
			longjmp(reslab, 0);
E 18
		}
		if (evalp = *evalvec) {
			evalvec++;
			goto top;
		}
		evalvec = (char **)1;
E 20
I 20
	evalp = 0;
    }
    if (evalvec) {
	if (evalvec == (Char **) 1) {
	    doneinp = 1;
	    reset();
	}
D 37
	if (evalp = *evalvec) {
E 37
I 37
	if ((evalp = *evalvec) != '\0') {
E 37
	    evalvec++;
	    goto top;
	}
	evalvec = (Char **) 1;
	return ('\n');
    }
    do {
	if (arginp == (Char *) 1 || onelflg == 1) {
	    if (wanteof)
		return (-1);
	    exitstat();
	}
	if (arginp) {
	    if ((c = *arginp++) == 0) {
		arginp = (Char *) 1;
E 20
		return ('\n');
I 20
	    }
	    return (c);
E 20
	}
D 20
	do {
		if (arginp == (char *) 1 || onelflg == 1) {
			if (wanteof)
				return (-1);
			exitstat();
		}
		if (arginp) {
			if ((c = *arginp++) == 0) {
				arginp = (char *) 1;
				return ('\n');
			}
			return (c);
		}
E 20
reread:
D 20
		c = bgetc();
		if (c < 0) {
D 8
#include <sgtty.h>
E 8
			struct sgttyb tty;
E 20
I 20
	c = bgetc();
	if (c < 0) {
D 25
#ifdef TERMIOS
E 25
	    struct termios tty;
D 25
#else
	    struct sgttyb tty;
#endif
E 25
	    if (wanteof)
		return (-1);
	    /* was isatty but raw with ignoreeof yields problems */
D 25
#ifdef TERMIOS
E 25
	    if (tcgetattr(SHIN, &tty) == 0 && (tty.c_lflag & ICANON))
D 25
#else
	    if (ioctl(SHIN, TIOCGETP, (ioctl_t) & tty) == 0 &&
		(tty.sg_flags & RAW) == 0)
#endif
E 25
	    {
		/* was 'short' for FILEC */
		int     ctpgrp;
E 20

D 20
			if (wanteof)
				return (-1);
			/* was isatty but raw with ignoreeof yields problems */
D 7
			if (ioctl(SHIN, TIOCGETP, &tty)==0 && (tty.sg_flags & RAW) == 0) {
E 7
I 7
			if (ioctl(SHIN, TIOCGETP, (char *)&tty) == 0 &&
			    (tty.sg_flags & RAW) == 0) {
E 7
I 3
				/* was 'short' for FILEC */
E 3
D 2
				short ctpgrp;
E 2
I 2
				int ctpgrp;
E 2

				if (++sincereal > 25)
					goto oops;
				if (tpgrp != -1 &&
D 7
				    ioctl(FSHTTY, TIOCGPGRP, &ctpgrp) == 0 &&
E 7
I 7
				    ioctl(FSHTTY, TIOCGPGRP, (char *)&ctpgrp) == 0 &&
E 7
				    tpgrp != ctpgrp) {
D 7
					ioctl(FSHTTY, TIOCSPGRP, &tpgrp);
					killpg(ctpgrp, SIGHUP);
E 7
I 7
					(void) ioctl(FSHTTY, TIOCSPGRP,
						(char *)&tpgrp);
					(void) killpg(ctpgrp, SIGHUP);
E 7
printf("Reset tty pgrp from %d to %d\n", ctpgrp, tpgrp);
					goto reread;
				}
				if (adrof("ignoreeof")) {
					if (loginsh)
						printf("\nUse \"logout\" to logout.\n");
					else
						printf("\nUse \"exit\" to leave csh.\n");
D 18
					reset();
E 18
I 18
					longjmp(reslab, 0);
E 18
				}
				if (chkstop == 0)
					panystop(1);
			}
oops:
			doneinp = 1;
D 18
			reset();
E 18
I 18
			longjmp(reslab, 0);
E 20
I 20
		if (++sincereal > 25)
		    goto oops;
		if (tpgrp != -1 &&
		    (ctpgrp = tcgetpgrp(FSHTTY)) != -1 &&
		    tpgrp != ctpgrp) {
		    (void) tcsetpgrp(FSHTTY, tpgrp);
		    (void) killpg((pid_t) ctpgrp, SIGHUP);
D 26
		    xprintf("Reset tty pgrp from %d to %d\n", ctpgrp, tpgrp);
E 26
I 26
D 33
		    (void) fprintf(csherr, "Reset tty pgrp from %d to %d\n", 
E 33
I 33
		    (void) fprintf(csherr, "Reset tty pgrp from %d to %d\n",
E 33
				   ctpgrp, tpgrp);
E 26
		    goto reread;
E 20
E 18
		}
D 20
		sincereal = 0;
		if (c == '\n' && onelflg)
			onelflg--;
	} while (c == 0);
	return (c);
E 20
I 20
		if (adrof(STRignoreeof)) {
		    if (loginsh)
D 26
			xprintf("\nUse \"logout\" to logout.\n");
E 26
I 26
			(void) fprintf(csherr,"\nUse \"logout\" to logout.\n");
E 26
		    else
D 26
			xprintf("\nUse \"exit\" to leave csh.\n");
E 26
I 26
			(void) fprintf(csherr,"\nUse \"exit\" to leave csh.\n");
E 26
		    reset();
		}
		if (chkstop == 0)
		    panystop(1);
	    }
    oops:
	    doneinp = 1;
	    reset();
	}
	sincereal = 0;
	if (c == '\n' && onelflg)
	    onelflg--;
    } while (c == 0);
    return (c);
E 20
}

I 20
static int
E 20
bgetc()
{
D 20
	register int buf, off, c;
E 20
I 20
    register int buf, off, c;

E 20
I 3
#ifdef FILEC
D 20
	char ttyline[BUFSIZ];
	register int numleft = 0, roomleft;
E 20
I 20
    register int numleft = 0, roomleft;
    Char    ttyline[BUFSIZ];
E 20
D 4
#endif FILEC
E 4
I 4
#endif
I 20
    char    tbuf[BUFSIZ + 1];
E 20
E 4
E 3

D 21
#ifdef TELL
E 21
D 20
	if (cantell) {
		if (fseekp < fbobp || fseekp > feobp) {
			fbobp = feobp = fseekp;
D 7
			lseek(SHIN, fseekp, 0);
E 7
I 7
			(void) lseek(SHIN, fseekp, 0);
E 7
		}
		if (fseekp == feobp) {
			fbobp = feobp;
			do
				c = read(SHIN, fbuf[0], BUFSIZ);
			while (c < 0 && errno == EINTR);
			if (c <= 0)
				return (-1);
			feobp += c;
		}
		c = fbuf[0][fseekp - fbobp];
		fseekp++;
		return (c);
E 20
I 20
    if (cantell) {
	if (fseekp < fbobp || fseekp > feobp) {
	    fbobp = feobp = fseekp;
	    (void) lseek(SHIN, fseekp, L_SET);
E 20
	}
I 20
	if (fseekp == feobp) {
	    int     i;

	    fbobp = feobp;
	    do
		c = read(SHIN, tbuf, BUFSIZ);
	    while (c < 0 && errno == EINTR);
	    if (c <= 0)
		return (-1);
	    for (i = 0; i < c; i++)
		fbuf[0][i] = (unsigned char) tbuf[i];
	    feobp += c;
	}
	c = fbuf[0][fseekp - fbobp];
	fseekp++;
	return (c);
    }
E 20
D 21
#endif
E 21
I 20

E 20
again:
D 20
	buf = (int) fseekp / BUFSIZ;
	if (buf >= fblocks) {
D 7
		register char **nfbuf = (char **) calloc(fblocks+2, sizeof (char **));
E 7
I 7
		register char **nfbuf =
			(char **) calloc((unsigned) (fblocks + 2),
				sizeof (char **));
E 20
I 20
    buf = (int) fseekp / BUFSIZ;
    if (buf >= fblocks) {
	register Char **nfbuf =
	(Char **) xcalloc((size_t) (fblocks + 2),
			  sizeof(Char **));
E 20
E 7

D 20
		if (fbuf) {
D 7
			blkcpy(nfbuf, fbuf);
E 7
I 7
			(void) blkcpy(nfbuf, fbuf);
E 7
			xfree((char *)fbuf);
		}
		fbuf = nfbuf;
		fbuf[fblocks] = calloc(BUFSIZ, sizeof (char));
		fblocks++;
		goto again;
E 20
I 20
	if (fbuf) {
	    (void) blkcpy(nfbuf, fbuf);
	    xfree((ptr_t) fbuf);
E 20
	}
D 20
	if (fseekp >= feobp) {
		buf = (int) feobp / BUFSIZ;
		off = (int) feobp % BUFSIZ;
I 3
D 7
#ifdef FILEC
		roomleft = BUFSIZ - off;
D 4
#endif FILEC
E 4
I 4
#endif
E 4
E 3
		do
E 7
D 3
			c = read(SHIN, fbuf[buf] + off, BUFSIZ - off);
E 3
I 3
#ifndef FILEC
I 7
D 8
		do
E 8
I 8
		for (;;) {
E 8
E 7
D 4
		    c = read(SHIN, fbuf[buf] + off, BUFSIZ - off);
#else FILEC
		    if (intty)			/* then use tenex routine */
		    {
			c = numleft ? numleft : tenex(ttyline, BUFSIZ);
			if (c > roomleft)	/* No room in this buffer? */
			{
			    /* start with fresh buffer */
			    feobp = fseekp = fblocks * BUFSIZ;
			    numleft = c;
			    goto again;
			}
			if (c > 0)
			    copy (fbuf[buf] + off, ttyline, c);
			numleft = 0;
		    }
		    else
			c = read(SHIN, fbuf[buf] + off, roomleft);
#endif FILEC
E 4
I 4
			c = read(SHIN, fbuf[buf] + off, BUFSIZ - off);
#else
D 7
			if (intty) {
E 7
I 7
		roomleft = BUFSIZ - off;
D 8
		do
E 8
I 8
		for (;;) {
E 8
			if (filec && intty) {
E 7
				c = numleft ? numleft : tenex(ttyline, BUFSIZ);
				if (c > roomleft) {
					/* start with fresh buffer */
					feobp = fseekp = fblocks * BUFSIZ;
					numleft = c;
					goto again;
				}
				if (c > 0)
D 17
					copy(fbuf[buf] + off, ttyline, c);
E 17
I 17
					bcopy(ttyline, fbuf[buf] + off, c);
E 17
				numleft = 0;
			} else
				c = read(SHIN, fbuf[buf] + off, roomleft);
E 20
I 20
	fbuf = nfbuf;
	fbuf[fblocks] = (Char *) xcalloc(BUFSIZ, sizeof(Char));
	fblocks++;
	if (!intty)
	    goto again;
    }
    if (fseekp >= feobp) {
	buf = (int) feobp / BUFSIZ;
	off = (int) feobp % BUFSIZ;
	roomleft = BUFSIZ - off;

#ifdef FILEC
	roomleft = BUFSIZ - off;
	for (;;) {
	    if (filec && intty) {
		c = numleft ? numleft : tenex(ttyline, BUFSIZ);
		if (c > roomleft) {
		    /* start with fresh buffer */
		    feobp = fseekp = fblocks * BUFSIZ;
		    numleft = c;
		    goto again;
		}
		if (c > 0)
D 40
		    bcopy(ttyline, fbuf[buf] + off, c * sizeof(Char));
E 40
I 40
		    memmove(fbuf[buf] + off, ttyline, c * sizeof(Char));
E 40
		numleft = 0;
	    }
	    else {
E 20
#endif
E 4
E 3
D 8
		while (c < 0 && errno == EINTR);
E 8
I 8
D 20
			if (c >= 0)
				break;
			if (errno == EWOULDBLOCK) {
				int off = 0;
E 20
I 20
		c = read(SHIN, tbuf, roomleft);
		if (c > 0) {
		    int     i;
		    Char   *ptr = fbuf[buf] + off;
E 20

D 20
				(void) ioctl(SHIN, FIONBIO, (char *)&off);
			} else if (errno != EINTR)
				break;
E 20
I 20
		    for (i = 0; i < c; i++)
			ptr[i] = (unsigned char) tbuf[i];
E 20
		}
E 8
D 20
		if (c <= 0)
			return (-1);
		feobp += c;
E 20
I 20
#ifdef FILEC
	    }
#endif
	    if (c >= 0)
		break;
	    if (errno == EWOULDBLOCK) {
		int     off = 0;

		(void) ioctl(SHIN, FIONBIO, (ioctl_t) & off);
	    }
	    else if (errno != EINTR)
		break;
	}
	if (c <= 0)
	    return (-1);
	feobp += c;
E 20
I 3
#ifndef FILEC
E 3
D 20
		goto again;
E 20
I 20
	goto again;
E 20
I 3
D 4
#else FILEC
E 4
I 4
#else
E 4
D 7
		if (!intty)
		    goto again;
E 7
I 7
D 20
		if (filec && !intty)
			goto again;
E 20
I 20
	if (filec && !intty)
	    goto again;
E 20
E 7
D 4
#endif FILEC
E 4
I 4
#endif
E 4
E 3
D 20
	}
	c = fbuf[buf][(int) fseekp % BUFSIZ];
	fseekp++;
	return (c);
E 20
I 20
    }
    c = fbuf[buf][(int) fseekp % BUFSIZ];
    fseekp++;
    return (c);
E 20
}

I 20
static void
E 20
bfree()
{
D 20
	register int sb, i;
E 20
I 20
    register int sb, i;
E 20

D 21
#ifdef TELL
E 21
D 20
	if (cantell)
		return;
E 20
I 20
    if (cantell)
	return;
E 20
D 21
#endif
E 21
D 20
	if (whyles)
		return;
	sb = (int) (fseekp - 1) / BUFSIZ;
	if (sb > 0) {
		for (i = 0; i < sb; i++)
			xfree(fbuf[i]);
D 7
		blkcpy(fbuf, &fbuf[sb]);
E 7
I 7
		(void) blkcpy(fbuf, &fbuf[sb]);
E 7
		fseekp -= BUFSIZ * sb;
		feobp -= BUFSIZ * sb;
		fblocks -= sb;
	}
E 20
I 20
    if (whyles)
	return;
    sb = (int) (fseekp - 1) / BUFSIZ;
    if (sb > 0) {
	for (i = 0; i < sb; i++)
	    xfree((ptr_t) fbuf[i]);
	(void) blkcpy(fbuf, &fbuf[sb]);
	fseekp -= BUFSIZ * sb;
	feobp -= BUFSIZ * sb;
	fblocks -= sb;
    }
E 20
}

I 20
void
E 20
bseek(l)
D 7
	long l;
E 7
I 7
D 20
	off_t l;
E 20
I 20
D 29
    off_t   l;

E 29
I 29
    struct Ain   *l;
E 29
E 20
E 7
{
I 29
    switch (aret = l->type) {
    case E_SEEK:
	evalvec = l->a_seek;
D 36
	evalp = (Char *) l->f_seek;
E 36
I 36
	evalp = l->c_seek;
E 36
	return;
    case A_SEEK:
	alvec = l->a_seek;
D 36
	alvecp = (Char *) l->f_seek;
E 36
I 36
	alvecp = l->c_seek;
E 36
	return;
D 33
    case F_SEEK:	
E 33
I 33
    case F_SEEK:
E 33
	fseekp = l->f_seek;
	return;
    default:
	(void) fprintf(csherr, "Bad seek type %d\n", aret);
	abort();
    }
}
E 29
D 20
	register struct whyle *wp;
E 20
I 20
D 21
#ifdef notdef
    register struct whyle *wp;
E 21
E 20

D 20
	fseekp = l;
E 20
I 20
D 21
#endif

E 21
D 29
    fseekp = l;
E 20
D 21
#ifdef TELL
E 21
D 20
	if (!cantell) {
E 20
I 20
    if (!cantell) {
I 21
#ifdef notdef
	register struct whyle *wp;
E 21
E 20
#endif
I 21

E 21
D 20
		if (!whyles)
			return;
		for (wp = whyles; wp->w_next; wp = wp->w_next)
			continue;
		if (wp->w_start > l)
			l = wp->w_start;
E 20
I 20
	if (!whyles)
	    return;
#ifdef notdef
	/*
	 * Christos: I don't understand this? both wp and l are local. What is
	 * this used for? I suspect the author meant fseek = wp->w_start
I 21
	 * This seek/tell stuff needs to be re-written...
E 21
	 */
	for (wp = whyles; wp->w_next; wp = wp->w_next)
	    continue;
	if (wp->w_start > l)
	    l = wp->w_start;
#endif
E 29
I 29
void
btell(l)
    struct Ain *l;
{
    switch (l->type = aret) {
    case E_SEEK:
	l->a_seek = evalvec;
D 36
	l->f_seek = (off_t) evalp;
E 36
I 36
	l->c_seek = evalp;
E 36
	return;
    case A_SEEK:
	l->a_seek = alvec;
D 36
	l->f_seek = (off_t) alvecp;
E 36
I 36
	l->c_seek = alvecp;
E 36
	return;
    case F_SEEK:
	l->f_seek = fseekp;
	l->a_seek = NULL;
	return;
    default:
	(void) fprintf(csherr, "Bad seek type %d\n", aret);
	abort();
E 29
E 20
D 21
#ifdef TELL
E 21
D 20
	}
E 20
I 20
    }
E 20
D 21
#endif
E 21
}
D 22

/* any similarity to bell telephone is purely accidental */
I 13
#ifndef btell
E 13
D 7
long
E 7
I 7
off_t
E 7
btell()
{
D 20

	return (fseekp);
E 20
I 20
    return (fseekp);
E 20
}
I 13
#endif
E 22
E 13

I 20
void
E 20
btoeof()
{
D 20

D 7
	lseek(SHIN, 0l, 2);
E 7
I 7
	(void) lseek(SHIN, (off_t)0, 2);
E 7
	fseekp = feobp;
	wfree();
	bfree();
E 20
I 20
    (void) lseek(SHIN, (off_t) 0, L_XTND);
I 30
    aret = F_SEEK;
E 30
    fseekp = feobp;
I 30
    alvec = NULL;
    alvecp = NULL;
    evalvec = NULL;
    evalp = NULL;
E 30
    wfree();
    bfree();
E 20
}

D 21
#ifdef TELL
E 21
I 20
void
E 20
settell()
{
D 20

	cantell = 0;
	if (arginp || onelflg || intty)
		return;
D 7
	if (lseek(SHIN, 0l, 1) < 0 || errno == ESPIPE)
E 7
I 7
	if (lseek(SHIN, (off_t)0, 1) < 0 || errno == ESPIPE)
E 7
		return;
	fbuf = (char **) calloc(2, sizeof (char **));
	fblocks = 1;
	fbuf[0] = calloc(BUFSIZ, sizeof (char));
D 7
	fseekp = fbobp = feobp = tell(SHIN);
E 7
I 7
	fseekp = fbobp = feobp = lseek(SHIN, (off_t)0, 1);
E 7
	cantell = 1;
E 20
I 20
    cantell = 0;
    if (arginp || onelflg || intty)
	return;
    if (lseek(SHIN, (off_t) 0, L_INCR) < 0 || errno == ESPIPE)
	return;
    fbuf = (Char **) xcalloc(2, sizeof(Char **));
    fblocks = 1;
    fbuf[0] = (Char *) xcalloc(BUFSIZ, sizeof(Char));
    fseekp = fbobp = feobp = lseek(SHIN, (off_t) 0, L_INCR);
    cantell = 1;
E 20
}
I 20
D 21

E 20
#endif
E 21
E 1
