h35360
s 00014/00002/00962
d D 8.9 95/06/08 19:50:22 christos 19 18
c Obey PATH=newpath command
e
s 00002/00002/00962
d D 8.8 95/05/19 11:03:09 christos 18 17
c $ ); echo $? echoed 0,all other shells echo 2. 
c Now we set the exitstatus to 2 for all EXERROR errors. 
c Also I changed the exitstatus to 1 when a command is not found 
c to comply with historical practice.
e
s 00011/00002/00953
d D 8.7 95/05/14 22:37:32 christos 17 16
c fixed bug 
c false
e
s 00005/00007/00950
d D 8.6 95/05/13 23:54:16 christos 16 15
c Fix new bug where if exitstatus was not correct if condition 
c failed
e
s 00012/00008/00945
d D 8.5 95/05/11 16:55:39 christos 15 14
c fixed so that existatus is preserved in x=`false`
e
s 00094/00053/00859
d D 8.4 95/05/04 17:59:38 christos 14 13
c 
e
s 00001/00001/00911
d D 8.3 95/04/27 14:20:47 bostic 13 12
c POSIX.2 says that a successful variable assignment should set the status
c variable ($?) to 0.
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00005/00000/00907
d D 8.2 95/04/27 13:47:04 bostic 12 11
c The POSIX.2 requirement that "false" (among others) be found before
c $PATH processing basically requires it to be a builtin.
c From: "J.T. Conklin" <jtc@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00905
d D 8.1 93/05/31 15:30:51 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00029/00904
d D 5.9 93/05/31 15:30:46 bostic 10 8
c fix the copyright/SCCS notice
e
s 00002/00002/00931
d R 8.1 93/05/31 15:18:48 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00929
d D 5.8 92/07/31 14:55:52 marc 8 7
c fix null indirection
e
s 00008/00007/00921
d D 5.7 92/07/15 10:24:18 marc 7 6
c history support, new options
e
s 00001/00000/00927
d D 5.6 92/06/23 17:54:26 marc 6 5
c editing
e
s 00036/00008/00891
d D 5.5 92/04/30 15:07:52 marc 5 4
c add support for tilde expansion
e
s 00005/00000/00894
d D 5.4 92/04/16 14:32:14 marc 4 3
c add ! keyword
e
s 00007/00001/00887
d D 5.3 91/04/12 18:26:00 marc 3 2
c fix IF exit status
e
s 00025/00044/00863
d D 5.2 91/03/13 17:45:08 marc 2 1
c wrong source
e
s 00907/00000/00000
d D 5.1 91/03/07 20:27:24 bostic 1 0
c date and time created 91/03/07 20:27:24 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
E 10
I 10
D 11
 * Copyright (c) 1993 The Regents of the University of California.
E 10
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
D 5
 * %sccs.include.redist.c%
E 5
I 5
D 10
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 5
 */

#ifndef lint
D 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
I 5
D 10
static char sccsid[] = "@(#)eval.c	5.4 (Berkeley) 4/16/92";
E 10
I 10
static char sccsid[] = "%W% (Berkeley) %G%";
E 10
E 5
#endif /* not lint */

I 14
#include <signal.h>
#include <unistd.h>

E 14
/*
 * Evaluate a command.
 */

#include "shell.h"
#include "nodes.h"
#include "syntax.h"
#include "expand.h"
#include "parser.h"
#include "jobs.h"
#include "eval.h"
#include "builtins.h"
#include "options.h"
#include "exec.h"
#include "redir.h"
#include "input.h"
#include "output.h"
#include "trap.h"
#include "var.h"
#include "memalloc.h"
#include "error.h"
I 14
#include "show.h"
E 14
#include "mystring.h"
I 14
#ifndef NO_HISTORY
E 14
I 7
#include "myhistedit.h"
E 7
D 14
#include <signal.h>
E 14
I 14
#endif
E 14


/* flags in argument to evaltree */
#define EV_EXIT 01		/* exit after evaluating tree */
#define EV_TESTED 02		/* exit status is checked; ignore -e flag */
#define EV_BACKCMD 04		/* command executing within back quotes */


/* reasons for skipping commands (see comment on breakcmd routine) */
#define SKIPBREAK 1
#define SKIPCONT 2
#define SKIPFUNC 3

MKINIT int evalskip;		/* set if we are skipping commands */
STATIC int skipcount;		/* number of levels to skip */
MKINIT int loopnest;		/* current loop nesting level */
int funcnest;			/* depth of function calls */


char *commandname;
struct strlist *cmdenviron;
int exitstatus;			/* exit status of last command */
I 17
int oexitstatus;		/* saved exit status */
E 17


D 14
#ifdef __STDC__
STATIC void evalloop(union node *);
STATIC void evalfor(union node *);
STATIC void evalcase(union node *, int);
STATIC void evalsubshell(union node *, int);
STATIC void expredir(union node *);
STATIC void evalpipe(union node *);
STATIC void evalcommand(union node *, int, struct backcmd *);
STATIC void prehash(union node *);
#else
STATIC void evalloop();
STATIC void evalfor();
STATIC void evalcase();
STATIC void evalsubshell();
STATIC void expredir();
STATIC void evalpipe();
STATIC void evalcommand();
STATIC void prehash();
#endif
E 14
I 14
STATIC void evalloop __P((union node *));
STATIC void evalfor __P((union node *));
STATIC void evalcase __P((union node *, int));
STATIC void evalsubshell __P((union node *, int));
STATIC void expredir __P((union node *));
STATIC void evalpipe __P((union node *));
STATIC void evalcommand __P((union node *, int, struct backcmd *));
STATIC void prehash __P((union node *));
E 14


D 14

E 14
/*
 * Called to reset things after an exception.
 */

#ifdef mkinit
INCLUDE "eval.h"

RESET {
	evalskip = 0;
	loopnest = 0;
	funcnest = 0;
}

SHELLPROC {
	exitstatus = 0;
}
#endif



/*
D 2
 * The eval builtin.  Do you want clean, straight-forward semantics for
 * your eval command?  If so, read on....
E 2
I 2
 * The eval commmand.
E 2
 */

I 14
int
E 14
D 2
#ifdef ELIGANT
evalcmd(argc, argv)  char **argv; {
	char **ap;
E 2
I 2
evalcmd(argc, argv)  
I 14
	int argc;
E 14
	char **argv; 
{
        char *p;
        char *concat;
        char **ap;
E 2

D 2
	for (ap = argv + 1 ; *ap ; ap++) {
		evalstring(*ap);
	}
	return exitstatus;
}
#else

/*
 * If, on the other hand, you prefer downright bogus semantics in the
 * name of compatibility, here it is...
 */

evalcmd(argc, argv)  char **argv; {
	char **ap;
	char *p, *q;

	if (argc <= 1) {
		p = nullstr;
	} else if (argc == 2) {
		p = argv[1];
	} else {
		STARTSTACKSTR(p);
		ap = argv + 1;
		for (;;) {
			q = *ap++;
			while (*q) {
				STPUTC(*q++, p);
			}
			if (*ap == NULL)
				break;
			STPUTC(' ', p);
		}
		STPUTC('\0', p);
		p = grabstackstr(p);
	}
	evalstring(p);
	return exitstatus;
E 2
I 2
        if (argc > 1) {
                p = argv[1];
                if (argc > 2) {
                        STARTSTACKSTR(concat);
                        ap = argv + 2;
                        for (;;) {
                                while (*p)
                                        STPUTC(*p++, concat);
                                if ((p = *ap++) == NULL)
                                        break;
                                STPUTC(' ', concat);
                        }
                        STPUTC('\0', concat);
                        p = grabstackstr(concat);
                }
                evalstring(p);
        }
        return exitstatus;
E 2
}
D 2
#endif

E 2


/*
 * Execute a command or commands contained in a string.
 */

void
evalstring(s)
	char *s;
	{
	union node *n;
	struct stackmark smark;

	setstackmark(&smark);
	setinputstring(s, 1);
	while ((n = parsecmd(0)) != NEOF) {
		evaltree(n, 0);
		popstackmark(&smark);
	}
	popfile();
	popstackmark(&smark);
}



/*
 * Evaluate a parse tree.  The value is left in the global variable
 * exitstatus.
 */

void
evaltree(n, flags)
	union node *n;
D 14
	{
E 14
I 14
	int flags;
{
E 14
	if (n == NULL) {
		TRACE(("evaltree(NULL) called\n"));
D 7
		return;
E 7
I 7
		exitstatus = 0;
		goto out;
E 7
	}
I 14
#ifndef NO_HISTORY
E 14
I 7
	displayhist = 1;	/* show history substitutions done with fc */
E 7
D 14
	TRACE(("evaltree(0x%x: %d) called\n", (int)n, n->type));
E 14
I 14
#endif
	TRACE(("evaltree(0x%lx: %d) called\n", (long)n, n->type));
E 14
	switch (n->type) {
	case NSEMI:
		evaltree(n->nbinary.ch1, 0);
		if (evalskip)
			goto out;
		evaltree(n->nbinary.ch2, flags);
		break;
	case NAND:
		evaltree(n->nbinary.ch1, EV_TESTED);
		if (evalskip || exitstatus != 0)
			goto out;
		evaltree(n->nbinary.ch2, flags);
		break;
	case NOR:
		evaltree(n->nbinary.ch1, EV_TESTED);
		if (evalskip || exitstatus == 0)
			goto out;
		evaltree(n->nbinary.ch2, flags);
		break;
	case NREDIR:
		expredir(n->nredir.redirect);
		redirect(n->nredir.redirect, REDIR_PUSH);
		evaltree(n->nredir.n, flags);
		popredir();
		break;
	case NSUBSHELL:
		evalsubshell(n, flags);
		break;
	case NBACKGND:
		evalsubshell(n, flags);
		break;
D 3
	case NIF:
E 3
I 3
	case NIF: {
D 16
		int status = 0; 
E 16
I 16
		int status; 
E 16

E 3
		evaltree(n->nif.test, EV_TESTED);
I 16
		status = exitstatus;
		exitstatus = 0;
E 16
		if (evalskip)
			goto out;
D 16
		if (exitstatus == 0) {
E 16
I 16
		if (status == 0)
E 16
			evaltree(n->nif.ifpart, flags);
I 3
D 16
			status = exitstatus;
E 3
		} else if (n->nif.elsepart) {
E 16
I 16
		else if (n->nif.elsepart)
E 16
			evaltree(n->nif.elsepart, flags);
I 3
D 16
			status = exitstatus;
E 3
		}
I 3
		exitstatus = status;
E 16
E 3
		break;
I 3
	}
E 3
	case NWHILE:
	case NUNTIL:
		evalloop(n);
		break;
	case NFOR:
		evalfor(n);
		break;
	case NCASE:
		evalcase(n, flags);
		break;
	case NDEFUN:
		defun(n->narg.text, n->narg.next);
		exitstatus = 0;
		break;
I 4
	case NNOT:
		evaltree(n->nnot.com, EV_TESTED);
		exitstatus = !exitstatus;
		break;

E 4
	case NPIPE:
		evalpipe(n);
		break;
	case NCMD:
		evalcommand(n, flags, (struct backcmd *)NULL);
		break;
	default:
		out1fmt("Node type = %d\n", n->type);
		flushout(&output);
		break;
	}
out:
	if (pendingsigs)
		dotrap();
	if ((flags & EV_EXIT) || (eflag && exitstatus && !(flags & EV_TESTED)))
		exitshell(exitstatus);
}


STATIC void
evalloop(n)
	union node *n;
D 15
	{
E 15
I 15
{
E 15
	int status;

	loopnest++;
	status = 0;
	for (;;) {
		evaltree(n->nbinary.ch1, EV_TESTED);
		if (evalskip) {
skipping:	  if (evalskip == SKIPCONT && --skipcount <= 0) {
				evalskip = 0;
				continue;
			}
			if (evalskip == SKIPBREAK && --skipcount <= 0)
				evalskip = 0;
			break;
		}
		if (n->type == NWHILE) {
			if (exitstatus != 0)
				break;
		} else {
			if (exitstatus == 0)
				break;
		}
		evaltree(n->nbinary.ch2, 0);
		status = exitstatus;
		if (evalskip)
			goto skipping;
	}
	loopnest--;
	exitstatus = status;
}



STATIC void
evalfor(n)
D 15
	union node *n;
	{
E 15
I 15
    union node *n;
{
E 15
	struct arglist arglist;
	union node *argp;
	struct strlist *sp;
	struct stackmark smark;

	setstackmark(&smark);
	arglist.lastp = &arglist.list;
	for (argp = n->nfor.args ; argp ; argp = argp->narg.next) {
I 17
		oexitstatus = exitstatus;
E 17
D 5
		expandarg(argp, &arglist, 1);
E 5
I 5
		expandarg(argp, &arglist, EXP_FULL | EXP_TILDE);
E 5
		if (evalskip)
			goto out;
	}
	*arglist.lastp = NULL;

	exitstatus = 0;
	loopnest++;
	for (sp = arglist.list ; sp ; sp = sp->next) {
		setvar(n->nfor.var, sp->text, 0);
		evaltree(n->nfor.body, 0);
		if (evalskip) {
			if (evalskip == SKIPCONT && --skipcount <= 0) {
				evalskip = 0;
				continue;
			}
			if (evalskip == SKIPBREAK && --skipcount <= 0)
				evalskip = 0;
			break;
		}
	}
	loopnest--;
out:
	popstackmark(&smark);
}



STATIC void
evalcase(n, flags)
	union node *n;
D 14
	{
E 14
I 14
	int flags;
{
E 14
	union node *cp;
	union node *patp;
	struct arglist arglist;
	struct stackmark smark;

	setstackmark(&smark);
	arglist.lastp = &arglist.list;
I 17
	oexitstatus = exitstatus;
E 17
D 5
	expandarg(n->ncase.expr, &arglist, 0);
E 5
I 5
	expandarg(n->ncase.expr, &arglist, EXP_TILDE);
E 5
	for (cp = n->ncase.cases ; cp && evalskip == 0 ; cp = cp->nclist.next) {
		for (patp = cp->nclist.pattern ; patp ; patp = patp->narg.next) {
			if (casematch(patp, arglist.list->text)) {
				if (evalskip == 0) {
					evaltree(cp->nclist.body, flags);
				}
				goto out;
			}
		}
	}
out:
	popstackmark(&smark);
}



/*
 * Kick off a subshell to evaluate a tree.
 */

STATIC void
evalsubshell(n, flags)
	union node *n;
D 14
	{
E 14
I 14
	int flags;
{
E 14
	struct job *jp;
	int backgnd = (n->type == NBACKGND);

	expredir(n->nredir.redirect);
	jp = makejob(n, 1);
	if (forkshell(jp, n, backgnd) == 0) {
		if (backgnd)
			flags &=~ EV_TESTED;
		redirect(n->nredir.redirect, 0);
		evaltree(n->nredir.n, flags | EV_EXIT);	/* never returns */
	}
	if (! backgnd) {
		INTOFF;
		exitstatus = waitforjob(jp);
		INTON;
	}
}



/*
 * Compute the names of the files in a redirection list.
 */

STATIC void
expredir(n)
	union node *n;
D 15
	{
E 15
I 15
{
E 15
	register union node *redir;

	for (redir = n ; redir ; redir = redir->nfile.next) {
D 14
		if (redir->type == NFROM
		 || redir->type == NTO
		 || redir->type == NAPPEND) {
			struct arglist fn;
			fn.lastp = &fn.list;
E 14
I 14
		struct arglist fn;
		fn.lastp = &fn.list;
I 17
		oexitstatus = exitstatus;
E 17
		switch (redir->type) {
		case NFROM:
		case NTO:
		case NAPPEND:
E 14
D 5
			expandarg(redir->nfile.fname, &fn, 0);
E 5
I 5
			expandarg(redir->nfile.fname, &fn, EXP_TILDE | EXP_REDIR);
E 5
			redir->nfile.expfname = fn.list->text;
I 14
			break;
		case NFROMFD:
		case NTOFD:
			if (redir->ndup.vname) {
				expandarg(redir->ndup.vname, &fn, EXP_FULL | EXP_TILDE);
				fixredir(redir, fn.list->text, 1);
			}
			break;
E 14
		}
	}
}



/*
 * Evaluate a pipeline.  All the processes in the pipeline are children
 * of the process creating the pipeline.  (This differs from some versions
 * of the shell, which make the last process in a pipeline the parent
 * of all the rest.)
 */

STATIC void
evalpipe(n)
	union node *n;
D 15
	{
E 15
I 15
{
E 15
	struct job *jp;
	struct nodelist *lp;
	int pipelen;
	int prevfd;
	int pip[2];

D 14
	TRACE(("evalpipe(0x%x) called\n", (int)n));
E 14
I 14
	TRACE(("evalpipe(0x%lx) called\n", (long)n));
E 14
	pipelen = 0;
	for (lp = n->npipe.cmdlist ; lp ; lp = lp->next)
		pipelen++;
	INTOFF;
	jp = makejob(n, pipelen);
	prevfd = -1;
	for (lp = n->npipe.cmdlist ; lp ; lp = lp->next) {
		prehash(lp->n);
		pip[1] = -1;
		if (lp->next) {
			if (pipe(pip) < 0) {
				close(prevfd);
				error("Pipe call failed");
			}
		}
		if (forkshell(jp, lp->n, n->npipe.backgnd) == 0) {
			INTON;
			if (prevfd > 0) {
				close(0);
				copyfd(prevfd, 0);
				close(prevfd);
			}
			if (pip[1] >= 0) {
				close(pip[0]);
				if (pip[1] != 1) {
					close(1);
					copyfd(pip[1], 1);
					close(pip[1]);
				}
			}
			evaltree(lp->n, EV_EXIT);
		}
		if (prevfd >= 0)
			close(prevfd);
		prevfd = pip[0];
		close(pip[1]);
	}
	INTON;
	if (n->npipe.backgnd == 0) {
		INTOFF;
		exitstatus = waitforjob(jp);
		TRACE(("evalpipe:  job done exit status %d\n", exitstatus));
		INTON;
	}
}



/*
 * Execute a command inside back quotes.  If it's a builtin command, we
 * want to save its output in a block obtained from malloc.  Otherwise
 * we fork off a subprocess and get the output of the command via a pipe.
 * Should be called with interrupts off.
 */

void
evalbackcmd(n, result)
	union node *n;
	struct backcmd *result;
D 15
	{
E 15
I 15
{
E 15
	int pip[2];
	struct job *jp;
	struct stackmark smark;		/* unnecessary */

	setstackmark(&smark);
	result->fd = -1;
	result->buf = NULL;
	result->nleft = 0;
	result->jp = NULL;
I 8
D 17
	exitstatus = 0;
	if (n == NULL)
E 17
I 17
	if (n == NULL) {
		exitstatus = 0;
E 17
		goto out;
I 17
	}
E 17
E 8
	if (n->type == NCMD) {
I 17
		exitstatus = oexitstatus;
E 17
		evalcommand(n, EV_BACKCMD, result);
	} else {
I 17
		exitstatus = 0;
E 17
		if (pipe(pip) < 0)
			error("Pipe call failed");
		jp = makejob(n, 1);
		if (forkshell(jp, n, FORK_NOJOB) == 0) {
			FORCEINTON;
			close(pip[0]);
			if (pip[1] != 1) {
				close(1);
				copyfd(pip[1], 1);
				close(pip[1]);
			}
			evaltree(n, EV_EXIT);
		}
		close(pip[1]);
		result->fd = pip[0];
		result->jp = jp;
	}
I 8
out:
E 8
	popstackmark(&smark);
	TRACE(("evalbackcmd done: fd=%d buf=0x%x nleft=%d jp=0x%x\n",
		result->fd, result->buf, result->nleft, result->jp));
}



/*
 * Execute a simple command.
 */

STATIC void
evalcommand(cmd, flags, backcmd)
	union node *cmd;
I 14
	int flags;
E 14
	struct backcmd *backcmd;
D 14
	{
E 14
I 14
{
E 14
	struct stackmark smark;
	union node *argp;
	struct arglist arglist;
	struct arglist varlist;
	char **argv;
	int argc;
	char **envp;
	int varflag;
	struct strlist *sp;
D 14
	register char *p;
E 14
	int mode;
	int pip[2];
	struct cmdentry cmdentry;
	struct job *jp;
	struct jmploc jmploc;
	struct jmploc *volatile savehandler;
	char *volatile savecmdname;
	volatile struct shparam saveparam;
	struct localvar *volatile savelocalvars;
	volatile int e;
	char *lastarg;
I 14
#if __GNUC__
	/* Avoid longjmp clobbering */
	(void) &argv;
	(void) &argc;
	(void) &lastarg;
	(void) &flags;
#endif
E 14

	/* First expand the arguments. */
D 14
	TRACE(("evalcommand(0x%x, %d) called\n", (int)cmd, flags));
E 14
I 14
	TRACE(("evalcommand(0x%lx, %d) called\n", (long)cmd, flags));
E 14
	setstackmark(&smark);
	arglist.lastp = &arglist.list;
	varlist.lastp = &varlist.list;
	varflag = 1;
I 17
	oexitstatus = exitstatus;
	exitstatus = 0;
E 17
	for (argp = cmd->ncmd.args ; argp ; argp = argp->narg.next) {
D 14
		p = argp->narg.text;
E 14
I 14
		char *p = argp->narg.text;
E 14
		if (varflag && is_name(*p)) {
			do {
				p++;
			} while (is_in_name(*p));
			if (*p == '=') {
D 5
				expandarg(argp, &varlist, 0);
E 5
I 5
				expandarg(argp, &varlist, EXP_VARTILDE);
E 5
				continue;
			}
		}
D 5
		expandarg(argp, &arglist, 1);
E 5
I 5
		expandarg(argp, &arglist, EXP_FULL | EXP_TILDE);
E 5
		varflag = 0;
	}
	*arglist.lastp = NULL;
	*varlist.lastp = NULL;
	expredir(cmd->ncmd.redirect);
	argc = 0;
	for (sp = arglist.list ; sp ; sp = sp->next)
		argc++;
	argv = stalloc(sizeof (char *) * (argc + 1));
I 7

E 7
D 5
	for (sp = arglist.list ; sp ; sp = sp->next)
E 5
I 5
	for (sp = arglist.list ; sp ; sp = sp->next) {
		TRACE(("evalcommand arg: %s\n", sp->text));
E 5
		*argv++ = sp->text;
I 5
	}
E 5
	*argv = NULL;
	lastarg = NULL;
	if (iflag && funcnest == 0 && argc > 0)
		lastarg = argv[-1];
	argv -= argc;

	/* Print the command if xflag is set. */
	if (xflag) {
		outc('+', &errout);
		for (sp = varlist.list ; sp ; sp = sp->next) {
			outc(' ', &errout);
			out2str(sp->text);
		}
		for (sp = arglist.list ; sp ; sp = sp->next) {
			outc(' ', &errout);
			out2str(sp->text);
		}
		outc('\n', &errout);
		flushout(&errout);
	}

	/* Now locate the command. */
	if (argc == 0) {
		cmdentry.cmdtype = CMDBUILTIN;
		cmdentry.u.index = BLTINCMD;
	} else {
D 19
		find_command(argv[0], &cmdentry, 1);
E 19
I 19
		static const char PATH[] = "PATH=";
		char *path = pathval();

		/*
		 * Modify the command lookup path, if a PATH= assignment
		 * is present
		 */
		for (sp = varlist.list ; sp ; sp = sp->next)
			if (strncmp(sp->text, PATH, sizeof(PATH) - 1) == 0)
				path = sp->text + sizeof(PATH) - 1;

		find_command(argv[0], &cmdentry, 1, path);
E 19
		if (cmdentry.cmdtype == CMDUNKNOWN) {	/* command not found */
D 18
			exitstatus = 2;
E 18
I 18
			exitstatus = 1;
E 18
			flushout(&errout);
			return;
		}
		/* implement the bltin builtin here */
		if (cmdentry.cmdtype == CMDBUILTIN && cmdentry.u.index == BLTINCMD) {
			for (;;) {
				argv++;
				if (--argc == 0)
					break;
				if ((cmdentry.u.index = find_builtin(*argv)) < 0) {
					outfmt(&errout, "%s: not found\n", *argv);
D 18
					exitstatus = 2;
E 18
I 18
					exitstatus = 1;
E 18
					flushout(&errout);
					return;
				}
				if (cmdentry.u.index != BLTINCMD)
					break;
			}
		}
	}

	/* Fork off a child process if necessary. */
	if (cmd->ncmd.backgnd
D 14
	 || cmdentry.cmdtype == CMDNORMAL && (flags & EV_EXIT) == 0
	 || (flags & EV_BACKCMD) != 0
E 14
I 14
	 || (cmdentry.cmdtype == CMDNORMAL && (flags & EV_EXIT) == 0)
	 || ((flags & EV_BACKCMD) != 0
E 14
	    && (cmdentry.cmdtype != CMDBUILTIN
		 || cmdentry.u.index == DOTCMD
D 14
		 || cmdentry.u.index == EVALCMD)) {
E 14
I 14
		 || cmdentry.u.index == EVALCMD))) {
E 14
		jp = makejob(cmd, 1);
		mode = cmd->ncmd.backgnd;
		if (flags & EV_BACKCMD) {
			mode = FORK_NOJOB;
			if (pipe(pip) < 0)
				error("Pipe call failed");
		}
		if (forkshell(jp, cmd, mode) != 0)
			goto parent;	/* at end of routine */
		if (flags & EV_BACKCMD) {
			FORCEINTON;
			close(pip[0]);
			if (pip[1] != 1) {
				close(1);
				copyfd(pip[1], 1);
				close(pip[1]);
			}
		}
		flags |= EV_EXIT;
	}

	/* This is the child process if a fork occurred. */
	/* Execute the command. */
	if (cmdentry.cmdtype == CMDFUNCTION) {
		trputs("Shell function:  ");  trargs(argv);
		redirect(cmd->ncmd.redirect, REDIR_PUSH);
		saveparam = shellparam;
		shellparam.malloc = 0;
		shellparam.nparam = argc - 1;
		shellparam.p = argv + 1;
		shellparam.optnext = NULL;
		INTOFF;
		savelocalvars = localvars;
		localvars = NULL;
		INTON;
		if (setjmp(jmploc.loc)) {
			if (exception == EXSHELLPROC)
				freeparam((struct shparam *)&saveparam);
			else {
				freeparam(&shellparam);
				shellparam = saveparam;
			}
			poplocalvars();
			localvars = savelocalvars;
			handler = savehandler;
			longjmp(handler->loc, 1);
		}
		savehandler = handler;
		handler = &jmploc;
		for (sp = varlist.list ; sp ; sp = sp->next)
			mklocal(sp->text);
		funcnest++;
		evaltree(cmdentry.u.func, 0);
		funcnest--;
		INTOFF;
		poplocalvars();
		localvars = savelocalvars;
		freeparam(&shellparam);
		shellparam = saveparam;
		handler = savehandler;
		popredir();
		INTON;
		if (evalskip == SKIPFUNC) {
			evalskip = 0;
			skipcount = 0;
		}
		if (flags & EV_EXIT)
			exitshell(exitstatus);
	} else if (cmdentry.cmdtype == CMDBUILTIN) {
		trputs("builtin command:  ");  trargs(argv);
		mode = (cmdentry.u.index == EXECCMD)? 0 : REDIR_PUSH;
		if (flags == EV_BACKCMD) {
			memout.nleft = 0;
			memout.nextc = memout.buf;
			memout.bufsize = 64;
			mode |= REDIR_BACKQ;
		}
		redirect(cmd->ncmd.redirect, mode);
		savecmdname = commandname;
		cmdenviron = varlist.list;
		e = -1;
		if (setjmp(jmploc.loc)) {
			e = exception;
			exitstatus = (e == EXINT)? SIGINT+128 : 2;
			goto cmddone;
		}
		savehandler = handler;
		handler = &jmploc;
		commandname = argv[0];
		argptr = argv + 1;
		optptr = NULL;			/* initialize nextopt */
		exitstatus = (*builtinfunc[cmdentry.u.index])(argc, argv);
		flushall();
cmddone:
		out1 = &output;
		out2 = &errout;
		freestdout();
		if (e != EXSHELLPROC) {
			commandname = savecmdname;
			if (flags & EV_EXIT) {
				exitshell(exitstatus);
			}
		}
		handler = savehandler;
		if (e != -1) {
			if (e != EXERROR || cmdentry.u.index == BLTINCMD
					       || cmdentry.u.index == DOTCMD
					       || cmdentry.u.index == EVALCMD
I 14
#ifndef NO_HISTORY
E 14
I 7
					       || cmdentry.u.index == HISTCMD
I 14
#endif
E 14
E 7
					       || cmdentry.u.index == EXECCMD)
				exraise(e);
			FORCEINTON;
		}
		if (cmdentry.u.index != EXECCMD)
			popredir();
		if (flags == EV_BACKCMD) {
			backcmd->buf = memout.buf;
			backcmd->nleft = memout.nextc - memout.buf;
			memout.buf = NULL;
		}
	} else {
		trputs("normal command:  ");  trargs(argv);
		clearredir();
		redirect(cmd->ncmd.redirect, 0);
D 14
		if (varlist.list) {
			p = stalloc(strlen(pathval()) + 1);
			scopy(pathval(), p);
		} else {
			p = pathval();
		}
E 14
		for (sp = varlist.list ; sp ; sp = sp->next)
			setvareq(sp->text, VEXPORT|VSTACK);
		envp = environment();
D 14
		shellexec(argv, envp, p, cmdentry.u.index);
E 14
I 14
		shellexec(argv, envp, pathval(), cmdentry.u.index);
E 14
		/*NOTREACHED*/
	}
	goto out;

parent:	/* parent process gets here (if we forked) */
	if (mode == 0) {	/* argument to fork */
		INTOFF;
		exitstatus = waitforjob(jp);
		INTON;
	} else if (mode == 2) {
		backcmd->fd = pip[0];
		close(pip[1]);
		backcmd->jp = jp;
	}

out:
	if (lastarg)
		setvar("_", lastarg, 0);
	popstackmark(&smark);
}



/*
 * Search for a command.  This is called before we fork so that the
 * location of the command will be available in the parent as well as
 * the child.  The check for "goodname" is an overly conservative
 * check that the name will not be subject to expansion.
 */

STATIC void
prehash(n)
	union node *n;
D 15
	{
E 15
I 15
{
E 15
	struct cmdentry entry;

D 14
	if (n->type == NCMD && goodname(n->ncmd.args->narg.text))
		find_command(n->ncmd.args->narg.text, &entry, 0);
E 14
I 14
	if (n->type == NCMD && n->ncmd.args)
		if (goodname(n->ncmd.args->narg.text))
D 19
			find_command(n->ncmd.args->narg.text, &entry, 0);
E 19
I 19
			find_command(n->ncmd.args->narg.text, &entry, 0,
				     pathval());
E 19
E 14
}



/*
 * Builtin commands.  Builtin commands whose functions are closely
 * tied to evaluation are implemented here.
 */

/*
 * No command given, or a bltin command with no arguments.  Set the
 * specified variables.
 */

D 14
bltincmd(argc, argv)  char **argv; {
E 14
I 14
int
bltincmd(argc, argv)
	int argc;
	char **argv; 
{
E 14
	listsetvar(cmdenviron);
D 13
	return exitstatus;
E 13
I 13
D 15
	return 0;
E 15
I 15
	/* 
	 * Preserve exitstatus of a previous possible redirection
	 * as POSIX mandates 
	 */
	return exitstatus;
E 15
E 13
}


/*
 * Handle break and continue commands.  Break, continue, and return are
 * all handled by setting the evalskip flag.  The evaluation routines
 * above all check this flag, and if it is set they start skipping
 * commands rather than executing them.  The variable skipcount is
 * the number of loops to break/continue, or the number of function
 * levels to return.  (The latter is always 1.)  It should probably
 * be an error to break out of more loops than exist, but it isn't
 * in the standard shell so we don't make it one here.
 */

D 14
breakcmd(argc, argv)  char **argv; {
E 14
I 14
int
breakcmd(argc, argv)
	int argc;
	char **argv; 
{
E 14
	int n;

	n = 1;
	if (argc > 1)
		n = number(argv[1]);
	if (n > loopnest)
		n = loopnest;
	if (n > 0) {
		evalskip = (**argv == 'c')? SKIPCONT : SKIPBREAK;
		skipcount = n;
	}
	return 0;
}


/*
 * The return command.
 */

D 14
returncmd(argc, argv)  char **argv; {
E 14
I 14
int
returncmd(argc, argv) 
	int argc;
	char **argv; 
{
E 14
	int ret;

	ret = exitstatus;
	if (argc > 1)
		ret = number(argv[1]);
	if (funcnest) {
		evalskip = SKIPFUNC;
		skipcount = 1;
	}
	return ret;
}


I 12
D 14
falsecmd(argc, argv) char **argv; {
E 14
I 14
int
falsecmd(argc, argv) 
	int argc;
	char **argv; 
{
E 14
	return 1;
}


E 12
D 14
truecmd(argc, argv)  char **argv; {
E 14
I 14
int
truecmd(argc, argv)  
	int argc;
	char **argv; 
{
E 14
	return 0;
}


D 14
execcmd(argc, argv)  char **argv; {
E 14
I 14
int
execcmd(argc, argv) 
	int argc;
	char **argv; 
{
E 14
	if (argc > 1) {
I 14
		struct strlist *sp;

E 14
		iflag = 0;		/* exit on error */
D 7
		setinteractive(0);
I 6
		histedit();
E 6
#if JOBS
		jflag = 0;
		setjobctl(0);
#endif
E 7
I 7
		mflag = 0;
		optschanged();
I 14
		for (sp = cmdenviron; sp ; sp = sp->next)
			setvareq(sp->text, VEXPORT|VSTACK);
E 14
E 7
		shellexec(argv + 1, environment(), pathval(), 0);

	}
	return 0;
}
E 1
