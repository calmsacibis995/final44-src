h46374
s 00004/00002/01419
d D 8.7 95/05/16 19:58:37 christos 18 17
c Fixed ${#} which was incorrectly parsed as ${#var}
e
s 00097/00051/01324
d D 8.6 95/05/04 18:00:06 christos 17 16
c 
e
s 00028/00006/01347
d D 8.5 95/04/28 17:16:13 bostic 16 15
c add the documented in the manual but not implemented variable
c expansions.
c From: Christos Zoulas <christos@deshaw.com>
e
s 00003/00003/01350
d D 8.4 95/04/28 10:24:02 bostic 15 14
c prettiness police
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00008/00000/01345
d D 8.3 95/04/27 15:19:11 bostic 14 13
c This patch fixes some broken behavior with empty commands in sh,
c e.g. ";<CR>", ">foo;<CR>", "(>foo)" are now correct
c From: Charles Hannum <mycroft@sun-lamp.cs.berkeley.edu>
e
s 00028/00020/01317
d D 8.2 95/04/27 14:15:47 bostic 13 12
c When a "&" is encountered in a list, all the prior commands 
c are grouped together and backgrounded, instead of only the previous
c and-or construct being backgrounded.  Typing "sleep 1; sleep 10 &" executes
c the equivalent (roughly) of "{ sleep 1; sleep 10; } &".
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/01335
d D 8.1 93/05/31 15:20:20 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00065/00020/01272
d D 5.11 93/05/24 15:40:03 marc 11 10
c fixes to support old style handling of ` ` (quoting), and "for var do"
e
s 00008/00002/01284
d D 5.10 93/04/20 04:05:26 torek 10 9
c allow "for i do echo $i; done"
e
s 00006/00001/01280
d D 5.9 93/04/20 03:53:35 marc 9 8
c checkin by torek before fixing `for i do'
e
s 00002/00000/01279
d D 5.8 93/03/02 17:43:23 marc 8 7
c make feeble attempt at compatability with old (broken) sh ` ` behavior 
c per ~bugs/4.4BSD-alpha/bin/2
e
s 00001/00001/01278
d D 5.7 92/06/23 18:38:49 marc 7 6
c histedit.h ==> myhistedit.h to avoid naming conflict
e
s 00067/00085/01212
d D 5.6 92/06/23 18:06:40 marc 6 5
c editing and aliases.  remove ATTY
e
s 00070/00006/01227
d D 5.5 92/04/30 15:11:16 marc 5 4
c add arithmetic
e
s 00014/00001/01219
d D 5.4 92/04/16 14:33:21 marc 4 3
c add ! keyword
e
s 00076/00081/01144
d D 5.3 91/04/12 18:24:48 marc 3 2
c check for keywords in more places for compat with original shell. also, ansi Cdecls
e
s 00012/00010/01213
d D 5.2 91/03/13 19:23:13 marc 2 1
c wrong source
e
s 01223/00000/00000
d D 5.1 91/03/07 20:27:53 bostic 1 0
c date and time created 91/03/07 20:27:53 by bostic
e
u
U
t
T
I 1
/*-
D 12
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 17
#include <stdlib.h>

E 17
#include "shell.h"
#include "parser.h"
#include "nodes.h"
#include "expand.h"	/* defines rmescapes() */
#include "redir.h"	/* defines copyfd() */
#include "syntax.h"
#include "options.h"
#include "input.h"
#include "output.h"
#include "var.h"
#include "error.h"
#include "memalloc.h"
#include "mystring.h"
I 6
#include "alias.h"
I 17
#include "show.h"
#ifndef NO_HISTORY
E 17
D 7
#include "histedit.h"
E 7
I 7
#include "myhistedit.h"
I 17
#endif
E 17
E 7
E 6

D 17

E 17
/*
 * Shell command parser.
 */

#define EOFMARKLEN 79

/* values returned by readtoken */
#include "token.def"



struct heredoc {
	struct heredoc *next;	/* next here document in list */
	union node *here;		/* redirection node */
	char *eofmark;		/* string indicating end of input */
	int striptabs;		/* if set, strip leading tabs */
};



struct heredoc *heredoclist;	/* list of here documents to read */
int parsebackquote;		/* nonzero if we are inside backquotes */
int doprompt;			/* if set, prompt the user */
int needprompt;			/* true if interactive and at start of line */
int lasttoken;			/* last token read */
MKINIT int tokpushback;		/* last token pushed back */
char *wordtext;			/* text of last word returned by readtoken */
I 3
D 6
int checkkwd;               /* 1 == check for kwds, 2 == also eat newlines */
E 6
I 6
MKINIT int checkkwd;            /* 1 == check for kwds, 2 == also eat newlines */
E 6
E 3
struct nodelist *backquotelist;
union node *redirnode;
struct heredoc *heredoc;
int quoteflag;			/* set if (part of) last token was quoted */
int startlinno;			/* line # where last token started */


#define GDB_HACK 1 /* avoid local declarations which gdb can't handle */
#ifdef GDB_HACK
static const char argvars[5] = {CTLVAR, VSNORMAL|VSQUOTE, '@', '=', '\0'};
static const char types[] = "}-+?=";
#endif


D 3
#ifdef __STDC__
STATIC union node *list(int);
STATIC union node *andor(void);
STATIC union node *pipeline(void);
STATIC union node *command(void);
STATIC union node *simplecmd(void);
STATIC void parsefname(void);
STATIC void parseheredoc(void);
STATIC void checkkwd(void);
STATIC int readtoken(void);
STATIC int readtoken1(int, char const *, char *, int);
STATIC void attyline(void);
STATIC int noexpand(char *);
STATIC void synexpect(int);
STATIC void synerror(char *);
#else
STATIC union node *list();
STATIC union node *andor();
STATIC union node *pipeline();
STATIC union node *command();
STATIC union node *simplecmd();
STATIC void parsefname();
STATIC void parseheredoc();
STATIC void checkkwd();
STATIC int readtoken();
STATIC int readtoken1();
STATIC void attyline();
STATIC int noexpand();
STATIC void synexpect();
STATIC void synerror();
#endif
E 3
I 3
STATIC union node *list __P((int));
STATIC union node *andor __P((void));
STATIC union node *pipeline __P((void));
STATIC union node *command __P((void));
D 11
STATIC union node *simplecmd __P((void));
E 11
I 11
STATIC union node *simplecmd __P((union node **, union node *));
I 17
STATIC union node *makename __P((void));
E 17
E 11
STATIC void parsefname __P((void));
STATIC void parseheredoc __P((void));
I 17
STATIC int peektoken __P((void));
E 17
STATIC int readtoken __P((void));
I 17
STATIC int xxreadtoken __P((void));
E 17
STATIC int readtoken1 __P((int, char const *, char *, int));
D 17
STATIC void attyline __P((void));
E 17
STATIC int noexpand __P((char *));
STATIC void synexpect __P((int));
STATIC void synerror __P((char *));
I 6
D 17
STATIC void setprompt __P((int));
E 17
I 17
STATIC void setprompt __P((int)); 
E 17
E 6
E 3

I 17

E 17
D 6
#if ATTY
D 3
#ifdef __STDC__
STATIC void putprompt(char *);
#else
STATIC void putprompt();
#endif
E 3
I 3
STATIC void putprompt __P((char *));
E 3
#else /* not ATTY */
#define putprompt(s)	out2str(s)
#endif




E 6
/*
 * Read and parse a command.  Returns NEOF on end of file.  (NULL is a
 * valid parse tree indicating a blank line.)
 */

union node *
D 17
parsecmd(interact) {
E 17
I 17
parsecmd(interact) 
	int interact;
{
E 17
	int t;

	doprompt = interact;
	if (doprompt)
D 6
		putprompt(ps1val());
E 6
I 6
		setprompt(1);
	else
		setprompt(0);
E 6
	needprompt = 0;
D 6
	if ((t = readtoken()) == TEOF)
E 6
I 6
	t = readtoken();
	if (t == TEOF)
E 6
		return NEOF;
	if (t == TNL)
		return NULL;
	tokpushback++;
	return list(1);
}


STATIC union node *
D 17
list(nlflag) {
E 17
I 17
list(nlflag) 
	int nlflag;
{
E 17
	union node *n1, *n2, *n3;
I 13
	int tok;
E 13

D 3
	checkkwd();
	if (nlflag == 0 && tokendlist[lasttoken])
E 3
I 3
	checkkwd = 2;
	if (nlflag == 0 && tokendlist[peektoken()])
E 3
		return NULL;
D 13
	n1 = andor();
E 13
I 13
	n1 = NULL;
E 13
	for (;;) {
D 13
		switch (readtoken()) {
		case TBACKGND:
			if (n1->type == NCMD || n1->type == NPIPE) {
				n1->ncmd.backgnd = 1;
			} else if (n1->type == NREDIR) {
				n1->type = NBACKGND;
E 13
I 13
		n2 = andor();
		tok = readtoken();
		if (tok == TBACKGND) {
			if (n2->type == NCMD || n2->type == NPIPE) {
				n2->ncmd.backgnd = 1;
			} else if (n2->type == NREDIR) {
				n2->type = NBACKGND;
E 13
			} else {
				n3 = (union node *)stalloc(sizeof (struct nredir));
				n3->type = NBACKGND;
D 13
				n3->nredir.n = n1;
E 13
I 13
				n3->nredir.n = n2;
E 13
				n3->nredir.redirect = NULL;
D 13
				n1 = n3;
E 13
I 13
				n2 = n3;
E 13
			}
D 13
			goto tsemi;
		case TNL:
			tokpushback++;
E 13
I 13
		}
		if (n1 == NULL) {
			n1 = n2;
		}
		else {
			n3 = (union node *)stalloc(sizeof (struct nbinary));
			n3->type = NSEMI;
			n3->nbinary.ch1 = n1;
			n3->nbinary.ch2 = n2;
			n1 = n3;
		}
		switch (tok) {
		case TBACKGND:
		case TSEMI:
			tok = readtoken();
E 13
			/* fall through */
D 13
tsemi:	    case TSEMI:
			if (readtoken() == TNL) {
E 13
I 13
		case TNL:
			if (tok == TNL) {
E 13
				parseheredoc();
				if (nlflag)
					return n1;
			} else {
				tokpushback++;
			}
D 3
			checkkwd();
			if (tokendlist[lasttoken])
E 3
I 3
			checkkwd = 2;
			if (tokendlist[peektoken()])
E 3
				return n1;
D 13
			n2 = andor();
			n3 = (union node *)stalloc(sizeof (struct nbinary));
			n3->type = NSEMI;
			n3->nbinary.ch1 = n1;
			n3->nbinary.ch2 = n2;
			n1 = n3;
E 13
			break;
		case TEOF:
			if (heredoclist)
				parseheredoc();
			else
				pungetc();		/* push back EOF on input */
			return n1;
		default:
			if (nlflag)
				synexpect(-1);
			tokpushback++;
			return n1;
		}
	}
}



STATIC union node *
andor() {
	union node *n1, *n2, *n3;
	int t;

	n1 = pipeline();
	for (;;) {
		if ((t = readtoken()) == TAND) {
			t = NAND;
		} else if (t == TOR) {
			t = NOR;
		} else {
			tokpushback++;
			return n1;
		}
		n2 = pipeline();
		n3 = (union node *)stalloc(sizeof (struct nbinary));
		n3->type = t;
		n3->nbinary.ch1 = n1;
		n3->nbinary.ch2 = n2;
		n1 = n3;
	}
}



STATIC union node *
pipeline() {
D 4
	union node *n1, *pipenode;
E 4
I 4
	union node *n1, *pipenode, *notnode;
E 4
	struct nodelist *lp, *prev;
I 4
	int negate = 0;
E 4

I 4
	TRACE(("pipeline: entered\n"));
	while (readtoken() == TNOT) {
		TRACE(("pipeline: TNOT recognized\n"));
		negate = !negate;
	}
	tokpushback++;
E 4
	n1 = command();
	if (readtoken() == TPIPE) {
		pipenode = (union node *)stalloc(sizeof (struct npipe));
		pipenode->type = NPIPE;
		pipenode->npipe.backgnd = 0;
		lp = (struct nodelist *)stalloc(sizeof (struct nodelist));
		pipenode->npipe.cmdlist = lp;
		lp->n = n1;
		do {
			prev = lp;
			lp = (struct nodelist *)stalloc(sizeof (struct nodelist));
			lp->n = command();
			prev->next = lp;
		} while (readtoken() == TPIPE);
		lp->next = NULL;
		n1 = pipenode;
	}
	tokpushback++;
I 4
	if (negate) {
		notnode = (union node *)stalloc(sizeof (struct nnot));
		notnode->type = NNOT;
		notnode->nnot.com = n1;
		n1 = notnode;
	}
E 4
	return n1;
}



STATIC union node *
command() {
	union node *n1, *n2;
	union node *ap, **app;
	union node *cp, **cpp;
	union node *redir, **rpp;
	int t;

D 3
	checkkwd();
E 3
I 3
	checkkwd = 2;
I 11
D 17
	redir = 0;
E 17
I 17
	redir = NULL;
	n1 = NULL;
E 17
	rpp = &redir;
	/* Check for redirection which may precede command */
	while (readtoken() == TREDIR) {
		*rpp = n2 = redirnode;
		rpp = &n2->nfile.next;
		parsefname();
	}
	tokpushback++;

E 11
E 3
	switch (readtoken()) {
	case TIF:
		n1 = (union node *)stalloc(sizeof (struct nif));
		n1->type = NIF;
		n1->nif.test = list(0);
		if (readtoken() != TTHEN)
			synexpect(TTHEN);
		n1->nif.ifpart = list(0);
		n2 = n1;
		while (readtoken() == TELIF) {
			n2->nif.elsepart = (union node *)stalloc(sizeof (struct nif));
			n2 = n2->nif.elsepart;
			n2->type = NIF;
			n2->nif.test = list(0);
			if (readtoken() != TTHEN)
				synexpect(TTHEN);
			n2->nif.ifpart = list(0);
		}
		if (lasttoken == TELSE)
			n2->nif.elsepart = list(0);
		else {
			n2->nif.elsepart = NULL;
			tokpushback++;
		}
		if (readtoken() != TFI)
			synexpect(TFI);
I 2
D 3
		checkkwd();
E 3
I 3
		checkkwd = 1;
E 3
E 2
		break;
	case TWHILE:
D 3
	case TUNTIL:
E 3
I 3
	case TUNTIL: {
		int got;
E 3
		n1 = (union node *)stalloc(sizeof (struct nbinary));
		n1->type = (lasttoken == TWHILE)? NWHILE : NUNTIL;
		n1->nbinary.ch1 = list(0);
D 3
		if (readtoken() != TDO)
E 3
I 3
		if ((got=readtoken()) != TDO) {
TRACE(("expecting DO got %s %s\n", tokname[got], got == TWORD ? wordtext : ""));
E 3
			synexpect(TDO);
I 3
		}
E 3
		n1->nbinary.ch2 = list(0);
		if (readtoken() != TDONE)
			synexpect(TDONE);
I 2
D 3
		checkkwd();
E 3
I 3
		checkkwd = 1;
E 3
E 2
		break;
I 3
	}
E 3
	case TFOR:
		if (readtoken() != TWORD || quoteflag || ! goodname(wordtext))
			synerror("Bad for loop variable");
		n1 = (union node *)stalloc(sizeof (struct nfor));
		n1->type = NFOR;
		n1->nfor.var = wordtext;
		if (readtoken() == TWORD && ! quoteflag && equal(wordtext, "in")) {
			app = &ap;
			while (readtoken() == TWORD) {
				n2 = (union node *)stalloc(sizeof (struct narg));
				n2->type = NARG;
				n2->narg.text = wordtext;
				n2->narg.backquote = backquotelist;
				*app = n2;
				app = &n2->narg.next;
			}
			*app = NULL;
			n1->nfor.args = ap;
I 10
			if (lasttoken != TNL && lasttoken != TSEMI)
				synexpect(-1);
E 10
		} else {
#ifndef GDB_HACK
			static const char argvars[5] = {CTLVAR, VSNORMAL|VSQUOTE,
								   '@', '=', '\0'};
#endif
			n2 = (union node *)stalloc(sizeof (struct narg));
			n2->type = NARG;
			n2->narg.text = (char *)argvars;
			n2->narg.backquote = NULL;
			n2->narg.next = NULL;
			n1->nfor.args = n2;
I 10
			/*
			 * Newline or semicolon here is optional (but note
			 * that the original Bourne shell only allowed NL).
			 */
			if (lasttoken != TNL && lasttoken != TSEMI)
				tokpushback++;
E 10
		}
D 10
		if (lasttoken != TNL && lasttoken != TSEMI)
			synexpect(-1);
E 10
D 3
		checkkwd();
E 3
I 3
		checkkwd = 2;
E 3
		if ((t = readtoken()) == TDO)
			t = TDONE;
		else if (t == TBEGIN)
			t = TEND;
		else
			synexpect(-1);
		n1->nfor.body = list(0);
		if (readtoken() != t)
			synexpect(t);
I 2
D 3
		checkkwd();
E 3
I 3
		checkkwd = 1;
E 3
E 2
		break;
	case TCASE:
		n1 = (union node *)stalloc(sizeof (struct ncase));
		n1->type = NCASE;
		if (readtoken() != TWORD)
			synexpect(TWORD);
		n1->ncase.expr = n2 = (union node *)stalloc(sizeof (struct narg));
		n2->type = NARG;
		n2->narg.text = wordtext;
		n2->narg.backquote = backquotelist;
		n2->narg.next = NULL;
		while (readtoken() == TNL);
		if (lasttoken != TWORD || ! equal(wordtext, "in"))
			synerror("expecting \"in\"");
		cpp = &n1->ncase.cases;
D 3
		while (checkkwd(), readtoken() == TWORD) {
E 3
I 3
D 17
		while (checkkwd = 2, readtoken() == TWORD) {
E 17
I 17
		checkkwd = 2, readtoken();
		do {
E 17
E 3
			*cpp = cp = (union node *)stalloc(sizeof (struct nclist));
			cp->type = NCLIST;
			app = &cp->nclist.pattern;
			for (;;) {
				*app = ap = (union node *)stalloc(sizeof (struct narg));
				ap->type = NARG;
				ap->narg.text = wordtext;
				ap->narg.backquote = backquotelist;
D 17
				if (readtoken() != TPIPE)
E 17
I 17
				if (checkkwd = 2, readtoken() != TPIPE)
E 17
					break;
				app = &ap->narg.next;
D 17
				if (readtoken() != TWORD)
					synexpect(TWORD);
E 17
I 17
				readtoken();
E 17
			}
			ap->narg.next = NULL;
			if (lasttoken != TRP)
				synexpect(TRP);
			cp->nclist.body = list(0);
D 17
			if ((t = readtoken()) == TESAC)
				tokpushback++;
			else if (t != TENDCASE)
				synexpect(TENDCASE);
E 17
I 17

			checkkwd = 2;
			if ((t = readtoken()) != TESAC) {
				if (t != TENDCASE)
					synexpect(TENDCASE);
				else
					checkkwd = 2, readtoken();
			}
E 17
			cpp = &cp->nclist.next;
D 17
		}
E 17
I 17
		} while(lasttoken != TESAC);
E 17
		*cpp = NULL;
D 17
		if (lasttoken != TESAC)
			synexpect(TESAC);
E 17
I 2
D 3
		checkkwd();
E 3
I 3
		checkkwd = 1;
E 3
E 2
		break;
	case TLP:
		n1 = (union node *)stalloc(sizeof (struct nredir));
		n1->type = NSUBSHELL;
		n1->nredir.n = list(0);
		n1->nredir.redirect = NULL;
		if (readtoken() != TRP)
			synexpect(TRP);
I 2
D 3
		checkkwd();
E 3
I 3
		checkkwd = 1;
E 3
E 2
		break;
	case TBEGIN:
		n1 = list(0);
		if (readtoken() != TEND)
			synexpect(TEND);
I 2
D 3
		checkkwd();
E 3
I 3
		checkkwd = 1;
E 3
E 2
		break;
I 11
	/* Handle an empty command like other simple commands.  */
I 14
	case TSEMI:
		/*
		 * An empty command before a ; doesn't make much sense, and
		 * should certainly be disallowed in the case of `if ;'.
		 */
		if (!redir)
			synexpect(-1);
E 14
	case TNL:
I 17
	case TEOF:
E 17
E 11
	case TWORD:
I 14
	case TRP:
E 14
D 11
	case TREDIR:
E 11
		tokpushback++;
D 11
		return simplecmd();
E 11
I 11
		return simplecmd(rpp, redir);
E 11
	default:
		synexpect(-1);
	}

	/* Now check for redirection which may follow command */
D 11
	rpp = &redir;
E 11
	while (readtoken() == TREDIR) {
		*rpp = n2 = redirnode;
		rpp = &n2->nfile.next;
		parsefname();
	}
	tokpushback++;
	*rpp = NULL;
	if (redir) {
		if (n1->type != NSUBSHELL) {
			n2 = (union node *)stalloc(sizeof (struct nredir));
			n2->type = NREDIR;
			n2->nredir.n = n1;
			n1 = n2;
		}
		n1->nredir.redirect = redir;
	}
	return n1;
}


STATIC union node *
D 11
simplecmd() {
E 11
I 11
simplecmd(rpp, redir) 
	union node **rpp, *redir;
	{
E 11
	union node *args, **app;
D 11
	union node *redir, **rpp;
E 11
I 11
	union node **orig_rpp = rpp;
E 11
	union node *n;

I 11
	/* If we don't have any redirections already, then we must reset */
	/* rpp to be the address of the local redir variable.  */
	if (redir == 0)
		rpp = &redir;

E 11
	args = NULL;
	app = &args;
D 11
	rpp = &redir;
E 11
I 11
	/* 
	 * We save the incoming value, because we need this for shell
	 * functions.  There can not be a redirect or an argument between
	 * the function name and the open parenthesis.  
	 */
	orig_rpp = rpp;

E 11
	for (;;) {
		if (readtoken() == TWORD) {
			n = (union node *)stalloc(sizeof (struct narg));
			n->type = NARG;
			n->narg.text = wordtext;
			n->narg.backquote = backquotelist;
			*app = n;
			app = &n->narg.next;
		} else if (lasttoken == TREDIR) {
			*rpp = n = redirnode;
			rpp = &n->nfile.next;
			parsefname();	/* read name of redirection file */
		} else if (lasttoken == TLP && app == &args->narg.next
D 11
					    && rpp == &redir) {
E 11
I 11
					    && rpp == orig_rpp) {
E 11
			/* We have a function */
			if (readtoken() != TRP)
				synexpect(TRP);
I 2
#ifdef notdef
E 2
			if (! goodname(n->narg.text))
				synerror("Bad function name");
I 2
#endif
E 2
			n->type = NDEFUN;
			n->narg.next = command();
			return n;
		} else {
			tokpushback++;
			break;
		}
	}
	*app = NULL;
	*rpp = NULL;
	n = (union node *)stalloc(sizeof (struct ncmd));
	n->type = NCMD;
	n->ncmd.backgnd = 0;
	n->ncmd.args = args;
	n->ncmd.redirect = redir;
	return n;
}

I 17
STATIC union node *
makename() {
	union node *n;
E 17

I 17
	n = (union node *)stalloc(sizeof (struct narg));
	n->type = NARG;
	n->narg.next = NULL;
	n->narg.text = wordtext;
	n->narg.backquote = backquotelist;
	return n;
}

void fixredir(n, text, err)
	union node *n;
	const char *text;
	int err;
	{
	TRACE(("Fix redir %s %d\n", text, err));
	if (!err)
		n->ndup.vname = NULL;

	if (is_digit(text[0]) && text[1] == '\0')
		n->ndup.dupfd = digit_val(text[0]);
	else if (text[0] == '-' && text[1] == '\0')
		n->ndup.dupfd = -1;
	else {
		
		if (err)
			synerror("Bad fd number");
		else
			n->ndup.vname = makename();
	}
}


E 17
STATIC void
parsefname() {
	union node *n = redirnode;

	if (readtoken() != TWORD)
		synexpect(-1);
	if (n->type == NHERE) {
		struct heredoc *here = heredoc;
		struct heredoc *p;
		int i;

		if (quoteflag == 0)
			n->type = NXHERE;
		TRACE(("Here document %d\n", n->type));
		if (here->striptabs) {
			while (*wordtext == '\t')
				wordtext++;
		}
		if (! noexpand(wordtext) || (i = strlen(wordtext)) == 0 || i > EOFMARKLEN)
			synerror("Illegal eof marker for << redirection");
		rmescapes(wordtext);
		here->eofmark = wordtext;
		here->next = NULL;
		if (heredoclist == NULL)
			heredoclist = here;
		else {
			for (p = heredoclist ; p->next ; p = p->next);
			p->next = here;
		}
	} else if (n->type == NTOFD || n->type == NFROMFD) {
D 17
		if (is_digit(wordtext[0]))
			n->ndup.dupfd = digit_val(wordtext[0]);
		else if (wordtext[0] == '-')
			n->ndup.dupfd = -1;
		else
			goto bad;
		if (wordtext[1] != '\0') {
bad:
			synerror("Bad fd number");
		}
E 17
I 17
		fixredir(n, wordtext, 0);
E 17
	} else {
D 17
		n->nfile.fname = (union node *)stalloc(sizeof (struct narg));
		n = n->nfile.fname;
		n->type = NARG;
		n->narg.next = NULL;
		n->narg.text = wordtext;
		n->narg.backquote = backquotelist;
E 17
I 17
		n->nfile.fname = makename();
E 17
	}
}


/*
 * Input any here documents.
 */

STATIC void
parseheredoc() {
	struct heredoc *here;
	union node *n;

	while (heredoclist) {
		here = heredoclist;
		heredoclist = here->next;
		if (needprompt) {
D 6
			putprompt(ps2val());
E 6
I 6
			setprompt(2);
E 6
			needprompt = 0;
		}
		readtoken1(pgetc(), here->here->type == NHERE? SQSYNTAX : DQSYNTAX,
				here->eofmark, here->striptabs);
		n = (union node *)stalloc(sizeof (struct narg));
		n->narg.type = NARG;
		n->narg.next = NULL;
		n->narg.text = wordtext;
		n->narg.backquote = backquotelist;
		here->here->nhere.doc = n;
	}
}

D 3


/*
 * This routine is called to tell readtoken that we are at the beginning
 * of a command, so newlines should be ignored and keywords should be
 * checked for.  We munge things here rather than setting a flag for
 * readtoken.
 */

STATIC void
checkkwd() {
	register char *const *pp;
E 3
I 3
STATIC int
peektoken() {
E 3
	int t;

D 2
	while ((t = readtoken()) == TNL);
E 2
I 2
D 3
	while ((t = readtoken()) == TNL)
		parseheredoc();
E 2
	if (t == TWORD && quoteflag == 0) {
		for (pp = parsekwd ; *pp ; pp++) {
			if (**pp == *wordtext && equal(*pp, wordtext)) {
				lasttoken = pp - parsekwd + KWDOFFSET;
				break;
			}
		}
	}
E 3
I 3
	t = readtoken();
E 3
	tokpushback++;
I 3
	return (t);
E 3
}

D 3


E 3
STATIC int xxreadtoken();

STATIC int
readtoken() {
	int t;
I 6
	int savecheckkwd = checkkwd;
	struct alias *ap;
E 6
I 3
#ifdef DEBUG
	int alreadyseen = tokpushback;
#endif
	
I 6
	top:
E 6
	t = xxreadtoken();
E 3

D 3
	if (tokpushback) {
		return xxreadtoken();
	} else {
		t = xxreadtoken();
		TRACE(("token %s %s\n", tokname[t], t == TWORD ? wordtext : ""));
D 2
		if (vflag)
			outfmt(out2, "%s %s\n", tokname[t], 
				t == TWORD ? wordtext : "");
E 2
		return t;
E 3
I 3
	if (checkkwd) {
		/*
		 * eat newlines
		 */
		if (checkkwd == 2) {
			checkkwd = 0;
			while (t == TNL) {
				parseheredoc();
				t = xxreadtoken();
			}
		} else
			checkkwd = 0;
		/*
D 6
		 * check for keywords
E 6
I 6
		 * check for keywords and aliases
E 6
		 */
D 17
		if (t == TWORD && !quoteflag) {
D 6
			register char **pp;
E 6
I 6
			register char * const *pp, *s;
E 17
I 17
		if (t == TWORD && !quoteflag) 
		{
			register char * const *pp;
E 17
E 6

D 11
			for (pp = parsekwd; *pp; pp++) {
E 11
I 11
			for (pp = (char **)parsekwd; *pp; pp++) {
E 11
D 17
				if (**pp == *wordtext && equal(*pp, wordtext)) {
E 17
I 17
				if (**pp == *wordtext && equal(*pp, wordtext)) 
				{
E 17
					lasttoken = t = pp - parsekwd + KWDOFFSET;
					TRACE(("keyword %s recognized\n", tokname[t]));
D 6
					break;
E 6
I 6
					goto out;
E 6
				}
			}
I 6
D 17
			if (ap = lookupalias(wordtext, 1)) {
E 17
I 17
			if ((ap = lookupalias(wordtext, 1)) != NULL) {
E 17
				pushstring(ap->val, strlen(ap->val), ap);
				checkkwd = savecheckkwd;
				goto top;
			}
E 6
		}
I 6
out:
		checkkwd = 0;
E 6
E 3
	}
I 3
#ifdef DEBUG
	if (!alreadyseen)
	    TRACE(("token %s %s\n", tokname[t], t == TWORD ? wordtext : ""));
	else
	    TRACE(("reread token %s %s\n", tokname[t], t == TWORD ? wordtext : ""));
#endif
	return (t);
E 3
}


/*
 * Read the next input token.
 * If the token is a word, we set backquotelist to the list of cmds in
 *	backquotes.  We set quoteflag to true if any part of the word was
 *	quoted.
 * If the token is TREDIR, then we set redirnode to a structure containing
 *	the redirection.
 * In all cases, the variable startlinno is set to the number of the line
 *	on which the token starts.
 *
 * [Change comment:  here documents and internal procedures]
 * [Readtoken shouldn't have any arguments.  Perhaps we should make the
 *  word parsing code into a separate routine.  In this case, readtoken
 *  doesn't need to have any internal procedures, but parseword does.
 *  We could also make parseoperator in essence the main routine, and
 *  have parseword (readtoken1?) handle both words and redirection.]
 */

#define RETURN(token)	return lasttoken = token

STATIC int
xxreadtoken() {
	register c;

	if (tokpushback) {
		tokpushback = 0;
		return lasttoken;
	}
	if (needprompt) {
D 6
		putprompt(ps2val());
E 6
I 6
		setprompt(2);
E 6
		needprompt = 0;
	}
	startlinno = plinno;
	for (;;) {	/* until token or start of word found */
		c = pgetc_macro();
		if (c == ' ' || c == '\t')
			continue;		/* quick check for white space first */
		switch (c) {
		case ' ': case '\t':
			continue;
		case '#':
			while ((c = pgetc()) != '\n' && c != PEOF);
			pungetc();
			continue;
		case '\\':
			if (pgetc() == '\n') {
				startlinno = ++plinno;
				if (doprompt)
D 6
					putprompt(ps2val());
E 6
I 6
					setprompt(2);
				else
					setprompt(0);
E 6
				continue;
			}
			pungetc();
			goto breakloop;
		case '\n':
			plinno++;
			needprompt = doprompt;
			RETURN(TNL);
		case PEOF:
			RETURN(TEOF);
		case '&':
			if (pgetc() == '&')
				RETURN(TAND);
			pungetc();
			RETURN(TBACKGND);
		case '|':
			if (pgetc() == '|')
				RETURN(TOR);
			pungetc();
			RETURN(TPIPE);
		case ';':
			if (pgetc() == ';')
				RETURN(TENDCASE);
			pungetc();
			RETURN(TSEMI);
		case '(':
			RETURN(TLP);
		case ')':
			RETURN(TRP);
		default:
			goto breakloop;
		}
	}
breakloop:
	return readtoken1(c, BASESYNTAX, (char *)NULL, 0);
#undef RETURN
}



/*
 * If eofmark is NULL, read a word or a redirection symbol.  If eofmark
 * is not NULL, read a here document.  In the latter case, eofmark is the
 * word which marks the end of the document and striptabs is true if
 * leading tabs should be stripped from the document.  The argument firstc
 * is the first character of the input token or document.
 *
 * Because C does not have internal subroutines, I have simulated them
 * using goto's to implement the subroutine linkage.  The following macros
 * will run code that appears at the end of readtoken1.
 */

#define CHECKEND()	{goto checkend; checkend_return:;}
#define PARSEREDIR()	{goto parseredir; parseredir_return:;}
#define PARSESUB()	{goto parsesub; parsesub_return:;}
#define PARSEBACKQOLD()	{oldstyle = 1; goto parsebackq; parsebackq_oldreturn:;}
#define PARSEBACKQNEW()	{oldstyle = 0; goto parsebackq; parsebackq_newreturn:;}
I 5
#define	PARSEARITH()	{goto parsearith; parsearith_return:;}
E 5

STATIC int
readtoken1(firstc, syntax, eofmark, striptabs)
	int firstc;
	char const *syntax;
	char *eofmark;
	int striptabs;
	{
D 17
	register c = firstc;
	register char *out;
E 17
I 17
	int c = firstc;
	char *out;
E 17
	int len;
	char line[EOFMARKLEN + 1];
	struct nodelist *bqlist;
	int quotef;
	int dblquote;
D 5
	int varnest;
E 5
I 5
	int varnest;	/* levels of variables expansion */
	int arinest;	/* levels of arithmetic expansion */
	int parenlevel;	/* levels of parens in arithmetic */
E 5
	int oldstyle;
I 5
	char const *prevsyntax;	/* syntax before arithmetic */
I 17
#if __GNUC__
	/* Avoid longjmp clobbering */
	(void) &out;
	(void) &quotef;
	(void) &dblquote;
	(void) &varnest;
	(void) &arinest;
	(void) &parenlevel;
	(void) &oldstyle;
	(void) &prevsyntax;
	(void) &syntax;
#endif
E 17
E 5

	startlinno = plinno;
	dblquote = 0;
	if (syntax == DQSYNTAX)
		dblquote = 1;
	quotef = 0;
	bqlist = NULL;
	varnest = 0;
I 5
	arinest = 0;
	parenlevel = 0;

E 5
	STARTSTACKSTR(out);
	loop: {	/* for each line, until end of word */
#if ATTY
		if (c == '\034' && doprompt
		 && attyset() && ! equal(termval(), "emacs")) {
			attyline();
			if (syntax == BASESYNTAX)
				return readtoken();
			c = pgetc();
			goto loop;
		}
#endif
		CHECKEND();	/* set c to PEOF if at end of here document */
		for (;;) {	/* until end of line or end of word */
			CHECKSTRSPACE(3, out);	/* permit 3 calls to USTPUTC */
I 8
D 9
			if (parsebackquote && c == '\\')
E 9
I 9
D 17
			if (parsebackquote && c == '\\') {
E 9
				c = pgetc();	/* XXX - compat with old /bin/sh */
I 9
				if (c != '\\' && c != '`' && c != '$') {
					pungetc();
					c = '\\';
				}
			}
E 17
E 9
E 8
			switch(syntax[c]) {
			case CNL:	/* '\n' */
				if (syntax == BASESYNTAX)
					goto endword;	/* exit outer loop */
				USTPUTC(c, out);
				plinno++;
D 6
				if (doprompt) {
					putprompt(ps2val());
				}
E 6
I 6
				if (doprompt)
					setprompt(2);
				else
					setprompt(0);
E 6
				c = pgetc();
				goto loop;		/* continue outer loop */
			case CWORD:
				USTPUTC(c, out);
				break;
			case CCTL:
				if (eofmark == NULL || dblquote)
					USTPUTC(CTLESC, out);
				USTPUTC(c, out);
				break;
			case CBACK:	/* backslash */
				c = pgetc();
				if (c == PEOF) {
					USTPUTC('\\', out);
					pungetc();
				} else if (c == '\n') {
					if (doprompt)
D 6
						putprompt(ps2val());
E 6
I 6
						setprompt(2);
					else
						setprompt(0);
E 6
				} else {
					if (dblquote && c != '\\' && c != '`' && c != '$'
							 && (c != '"' || eofmark != NULL))
						USTPUTC('\\', out);
					if (SQSYNTAX[c] == CCTL)
						USTPUTC(CTLESC, out);
					USTPUTC(c, out);
					quotef++;
				}
				break;
			case CSQUOTE:
				syntax = SQSYNTAX;
				break;
			case CDQUOTE:
				syntax = DQSYNTAX;
				dblquote = 1;
				break;
			case CENDQUOTE:
				if (eofmark) {
					USTPUTC(c, out);
				} else {
D 5
					syntax = BASESYNTAX;
E 5
I 5
					if (arinest)
						syntax = ARISYNTAX;
					else
						syntax = BASESYNTAX;
E 5
					quotef++;
					dblquote = 0;
				}
				break;
			case CVAR:	/* '$' */
				PARSESUB();		/* parse substitution */
				break;
			case CENDVAR:	/* '}' */
				if (varnest > 0) {
					varnest--;
					USTPUTC(CTLENDVAR, out);
				} else {
					USTPUTC(c, out);
				}
				break;
I 5
			case CLP:	/* '(' in arithmetic */
				parenlevel++;
				USTPUTC(c, out);
				break;
			case CRP:	/* ')' in arithmetic */
				if (parenlevel > 0) {
					USTPUTC(c, out);
					--parenlevel;
				} else {
					if (pgetc() == ')') {
						if (--arinest == 0) {
							USTPUTC(CTLENDARI, out);
							syntax = prevsyntax;
						} else
							USTPUTC(')', out);
					} else {
						/* 
						 * unbalanced parens
						 *  (don't 2nd guess - no error)
						 */
						pungetc();
						USTPUTC(')', out);
					}
				}
				break;
E 5
			case CBQUOTE:	/* '`' */
D 11
				if (parsebackquote && syntax == BASESYNTAX) {
					if (out == stackblock())
						return lasttoken = TENDBQUOTE;
					else
						goto endword;	/* exit outer loop */
				}
E 11
				PARSEBACKQOLD();
				break;
			case CEOF:
				goto endword;		/* exit outer loop */
			default:
				if (varnest == 0)
					goto endword;	/* exit outer loop */
				USTPUTC(c, out);
			}
			c = pgetc_macro();
		}
	}
endword:
I 5
	if (syntax == ARISYNTAX)
		synerror("Missing '))'");
E 5
D 11
	if (syntax != BASESYNTAX && eofmark == NULL)
E 11
I 11
	if (syntax != BASESYNTAX && ! parsebackquote && eofmark == NULL)
E 11
		synerror("Unterminated quoted string");
	if (varnest != 0) {
		startlinno = plinno;
		synerror("Missing '}'");
	}
	USTPUTC('\0', out);
	len = out - stackblock();
	out = stackblock();
	if (eofmark == NULL) {
		if ((c == '>' || c == '<')
		 && quotef == 0
		 && len <= 2
		 && (*out == '\0' || is_digit(*out))) {
			PARSEREDIR();
			return lasttoken = TREDIR;
		} else {
			pungetc();
		}
	}
	quoteflag = quotef;
	backquotelist = bqlist;
	grabstackblock(len);
	wordtext = out;
	return lasttoken = TWORD;
/* end of readtoken routine */



/*
 * Check to see whether we are at the end of the here document.  When this
 * is called, c is set to the first character of the next input line.  If
 * we are at the end of the here document, this routine sets the c to PEOF.
 */

checkend: {
	if (eofmark) {
		if (striptabs) {
			while (c == '\t')
				c = pgetc();
		}
		if (c == *eofmark) {
			if (pfgets(line, sizeof line) != NULL) {
				register char *p, *q;

				p = line;
				for (q = eofmark + 1 ; *q && *p == *q ; p++, q++);
				if (*p == '\n' && *q == '\0') {
					c = PEOF;
					plinno++;
					needprompt = doprompt;
				} else {
D 6
					ppushback(line, strlen(line));
E 6
I 6
					pushstring(line, strlen(line), NULL);
E 6
				}
			}
		}
	}
	goto checkend_return;
}


/*
 * Parse a redirection operator.  The variable "out" points to a string
 * specifying the fd to be redirected.  The variable "c" contains the
 * first character of the redirection operator.
 */

parseredir: {
	char fd = *out;
	union node *np;

	np = (union node *)stalloc(sizeof (struct nfile));
	if (c == '>') {
		np->nfile.fd = 1;
		c = pgetc();
		if (c == '>')
			np->type = NAPPEND;
		else if (c == '&')
			np->type = NTOFD;
		else {
			np->type = NTO;
			pungetc();
		}
	} else {	/* c == '<' */
		np->nfile.fd = 0;
		c = pgetc();
		if (c == '<') {
			if (sizeof (struct nfile) != sizeof (struct nhere)) {
				np = (union node *)stalloc(sizeof (struct nhere));
				np->nfile.fd = 0;
			}
			np->type = NHERE;
			heredoc = (struct heredoc *)stalloc(sizeof (struct heredoc));
			heredoc->here = np;
			if ((c = pgetc()) == '-') {
				heredoc->striptabs = 1;
			} else {
				heredoc->striptabs = 0;
				pungetc();
			}
		} else if (c == '&')
			np->type = NFROMFD;
		else {
			np->type = NFROM;
			pungetc();
		}
	}
	if (fd != '\0')
		np->nfile.fd = digit_val(fd);
	redirnode = np;
	goto parseredir_return;
}


/*
 * Parse a substitution.  At this point, we have read the dollar sign
 * and nothing else.
 */

parsesub: {
	int subtype;
	int typeloc;
	int flags;
	char *p;
#ifndef GDB_HACK
	static const char types[] = "}-+?=";
#endif

	c = pgetc();
D 2
	if (c == ' ' || c == '\t' || c == '\n' || c == PEOF
#ifndef STRICT_VARCHECKING	/* make this an option? */
	    || (c != '(' && c != '{' && !is_name(c) && !is_special(c))
#endif
	) {
E 2
I 2
	if (c != '(' && c != '{' && !is_name(c) && !is_special(c)) {
E 2
		USTPUTC('$', out);
		pungetc();
D 5
	} else if (c == '(') {	/* $(command) */
		PARSEBACKQNEW();
E 5
I 5
	} else if (c == '(') {	/* $(command) or $((arith)) */
		if (pgetc() == '(') {
			PARSEARITH();
		} else {
			pungetc();
			PARSEBACKQNEW();
		}
E 5
	} else {
		USTPUTC(CTLVAR, out);
		typeloc = out - stackblock();
		USTPUTC(VSNORMAL, out);
		subtype = VSNORMAL;
		if (c == '{') {
			c = pgetc();
D 16
			subtype = 0;
E 16
I 16
			if (c == '#') {
D 18
				subtype = VSLENGTH;
				c = pgetc();
E 18
I 18
				if ((c = pgetc()) == '}')
					c = '#';
				else
					subtype = VSLENGTH;
E 18
			}
			else
				subtype = 0;
E 16
		}
		if (is_name(c)) {
			do {
				STPUTC(c, out);
				c = pgetc();
			} while (is_in_name(c));
		} else {
			if (! is_special(c))
D 2
badsub:			synerror("Bad substitution");
E 2
I 2
badsub:				synerror("Bad substitution");
E 2
			USTPUTC(c, out);
			c = pgetc();
		}
		STPUTC('=', out);
		flags = 0;
		if (subtype == 0) {
D 16
			if (c == ':') {
E 16
I 16
			switch (c) {
			case ':':
E 16
				flags = VSNUL;
				c = pgetc();
I 16
				/*FALLTHROUGH*/
			default:
				p = strchr(types, c);
				if (p == NULL)
					goto badsub;
				subtype = p - types + VSNORMAL;
				break;
			case '%':
			case '#': 
				{
					int cc = c;
					subtype = c == '#' ? VSTRIMLEFT :
							     VSTRIMRIGHT;
					c = pgetc();
					if (c == cc)
						subtype++;
					else
						pungetc();
					break;
				}
E 16
			}
D 16
			p = strchr(types, c);
			if (p == NULL)
				goto badsub;
			subtype = p - types + VSNORMAL;
E 16
		} else {
			pungetc();
		}
D 5
		if (dblquote)
E 5
I 5
		if (dblquote || arinest)
E 5
			flags |= VSQUOTE;
		*(stackblock() + typeloc) = subtype | flags;
		if (subtype != VSNORMAL)
			varnest++;
	}
	goto parsesub_return;
}


/*
 * Called to parse command substitutions.  Newstyle is set if the command
 * is enclosed inside $(...); nlpp is a pointer to the head of the linked
 * list of commands (passed by reference), and savelen is the number of
 * characters on the top of the stack which must be preserved.
 */

parsebackq: {
	struct nodelist **nlpp;
	int savepbq;
	union node *n;
	char *volatile str;
	struct jmploc jmploc;
	struct jmploc *volatile savehandler;
	int savelen;
D 11
	int t;
E 11

	savepbq = parsebackquote;
	if (setjmp(jmploc.loc)) {
		if (str)
			ckfree(str);
		parsebackquote = 0;
		handler = savehandler;
D 6
		longjmp(handler, 1);
E 6
I 6
		longjmp(handler->loc, 1);
E 6
	}
	INTOFF;
	str = NULL;
	savelen = out - stackblock();
	if (savelen > 0) {
		str = ckmalloc(savelen);
D 15
		bcopy(stackblock(), str, savelen);
E 15
I 15
D 17
		memmove(str, stackblock(), savelen);
E 17
I 17
		memcpy(str, stackblock(), savelen);
E 17
E 15
	}
	savehandler = handler;
	handler = &jmploc;
	INTON;
I 11
        if (oldstyle) {
                /* We must read until the closing backquote, giving special
                   treatment to some slashes, and then push the string and
                   reread it as input, interpreting it normally.  */
                register char *out;
                register c;
                int savelen;
                char *str;
 
                STARTSTACKSTR(out);
                while ((c = pgetc ()) != '`') {
                       if (c == '\\') {
                                c = pgetc ();
                                if (c != '\\' && c != '`' && c != '$'
                                    && (!dblquote || c != '"'))
                                        STPUTC('\\', out);
                       }
                       STPUTC(c, out);
                }
                STPUTC('\0', out);
                savelen = out - stackblock();
                if (savelen > 0) {
                        str = ckmalloc(savelen);
D 15
                        bcopy(stackblock(), str, savelen);
E 15
I 15
D 17
                        memmove(str, stackblock(), savelen);
E 17
I 17
                        memcpy(str, stackblock(), savelen);
			setinputstring(str, 1);
E 17
E 15
                }
D 17
                setinputstring(str, 1);
E 17
        }
E 11
	nlpp = &bqlist;
	while (*nlpp)
		nlpp = &(*nlpp)->next;
	*nlpp = (struct nodelist *)stalloc(sizeof (struct nodelist));
	(*nlpp)->next = NULL;
	parsebackquote = oldstyle;
	n = list(0);
D 11
	t = oldstyle? TENDBQUOTE : TRP;
	if (readtoken() != t)
		synexpect(t);
E 11
I 11
        if (!oldstyle && (readtoken() != TRP))
                synexpect(TRP);
E 11
	(*nlpp)->n = n;
I 11
        /* Start reading from old file again.  */
        if (oldstyle)
                popfile();
E 11
	while (stackblocksize() <= savelen)
		growstackblock();
	STARTSTACKSTR(out);
	if (str) {
D 15
		bcopy(str, out, savelen);
E 15
I 15
D 17
		memmove(out, str, savelen);
E 17
I 17
		memcpy(out, str, savelen);
E 17
E 15
		STADJUST(savelen, out);
		INTOFF;
		ckfree(str);
		str = NULL;
		INTON;
	}
	parsebackquote = savepbq;
	handler = savehandler;
D 5
	USTPUTC(CTLBACKQ + dblquote, out);
E 5
I 5
	if (arinest || dblquote)
		USTPUTC(CTLBACKQ | CTLQUOTE, out);
	else
		USTPUTC(CTLBACKQ, out);
E 5
	if (oldstyle)
		goto parsebackq_oldreturn;
	else
		goto parsebackq_newreturn;
I 5
}

/*
 * Parse an arithmetic expansion (indicate start of one and set state)
 */
parsearith: {

	if (++arinest == 1) {
		prevsyntax = syntax;
		syntax = ARISYNTAX;
		USTPUTC(CTLARI, out);
	} else {
		/*
		 * we collapse embedded arithmetic expansion to
		 * parenthesis, which should be equivalent
		 */
		USTPUTC('(', out);
	}
	goto parsearith_return;
E 5
}

} /* end of readtoken */



#ifdef mkinit
RESET {
	tokpushback = 0;
I 6
	checkkwd = 0;
E 6
}
#endif

D 6

#if ATTY
E 6
/*
D 6
 * Called to process a command generated by atty.  We execute the line,
 * and catch any errors that occur so they don't propagate outside of
 * this routine.
 */

STATIC void
attyline() {
	char line[256];
	struct stackmark smark;
	struct jmploc jmploc;
	struct jmploc *volatile savehandler;

	if (pfgets(line, sizeof line) == NULL)
		return;				/* "can't happen" */
	if (setjmp(jmploc.loc)) {
		if (exception == EXERROR)
			out2str("\033]D\n");
		handler = savehandler;
		longjmp(handler, 1);
	}
	savehandler = handler;
	handler = &jmploc;
	setstackmark(&smark);
	evalstring(line);
	popstackmark(&smark);
	handler = savehandler;
	doprompt = 1;
}


/*
 * Output a prompt for atty.  We output the prompt as part of the
 * appropriate escape sequence.  
 */

STATIC void
putprompt(s)
	char *s;
	{
	register char *p;

	if (attyset() && ! equal(termval(), "emacs")) {
		if (strchr(s, '\7'))
			out2c('\7');
		out2str("\033]P1;");
		for (p = s ; *p ; p++) {
			if ((unsigned)(*p - ' ') <= '~' - ' ')
				out2c(*p);
		}
		out2c('\n');
	} else {
		out2str(s);
	}
}
#endif



/*
E 6
 * Returns true if the text contains nothing to expand (no dollar signs
 * or backquotes).
 */

STATIC int
noexpand(text)
	char *text;
	{
	register char *p;
	register char c;

	p = text;
	while ((c = *p++) != '\0') {
		if (c == CTLESC)
			p++;
		else if (BASESYNTAX[c] == CCTL)
			return 0;
	}
	return 1;
}


/*
 * Return true if the argument is a legal variable name (a letter or
 * underscore followed by zero or more letters, underscores, and digits).
 */

int
goodname(name)
	char *name;
	{
	register char *p;

	p = name;
	if (! is_name(*p))
		return 0;
	while (*++p) {
		if (! is_in_name(*p))
			return 0;
	}
	return 1;
}


/*
 * Called when an unexpected token is read during the parse.  The argument
 * is the token that is expected, or -1 if more than one type of token can
 * occur at this point.
 */

STATIC void
D 17
synexpect(token) {
E 17
I 17
synexpect(token) 
	int token;
{
E 17
	char msg[64];

	if (token >= 0) {
		fmtstr(msg, 64, "%s unexpected (expecting %s)",
			tokname[lasttoken], tokname[token]);
	} else {
		fmtstr(msg, 64, "%s unexpected", tokname[lasttoken]);
	}
	synerror(msg);
}


STATIC void
synerror(msg)
	char *msg;
	{
	if (commandname)
		outfmt(&errout, "%s: %d: ", commandname, startlinno);
	outfmt(&errout, "Syntax error: %s\n", msg);
	error((char *)NULL);
I 6
}

STATIC void
setprompt(which)
	int which;
	{
	whichprompt = which;

I 17
#ifndef NO_HISTORY
E 17
	if (!el)
I 17
#endif
E 17
		out2str(getprompt(NULL));
}

/*
 * called by editline -- any expansions to the prompt
 *    should be added here.
 */
char *
getprompt(unused)
	void *unused;
	{
	switch (whichprompt) {
	case 0:
		return "";
	case 1:
		return ps1val();
	case 2:
		return ps2val();
	default:
		return "<internal prompt error>";
	}
E 6
}
E 1
