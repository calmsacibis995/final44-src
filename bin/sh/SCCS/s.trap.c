h28738
s 00016/00011/00335
d D 8.5 95/06/05 12:20:49 christos 9 8
c Instead of special casing SIGKILL, pretend that trap 
c succeeded every time sigaction failed [suggested by mycroft]
e
s 00005/00000/00341
d D 8.4 95/06/05 10:19:52 christos 8 7
c Fake trapping SIGKILL, because we know it will fail.
e
s 00032/00012/00309
d D 8.3 95/05/04 18:00:12 christos 7 6
c 
e
s 00009/00010/00312
d D 8.2 95/04/27 14:47:20 bostic 6 5
c J.T. Conklin's changes for signals mean that we don't need all
c of the random signal crap any longer
e
s 00002/00002/00320
d D 8.1 93/05/31 15:20:46 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00005/00312
d D 5.4 92/07/15 09:10:05 marc 4 3
c jflag -> mflag, is_interactive is not global
e
s 00024/00008/00293
d D 5.3 92/06/23 17:55:33 marc 3 2
c use sigaction to determine state of signal
e
s 00015/00011/00286
d D 5.2 91/04/12 18:30:17 marc 2 1
c restore exit status after a trap.  
e
s 00297/00000/00000
d D 5.1 91/03/07 20:28:01 bostic 1 0
c date and time created 91/03/07 20:28:01 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 7
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

E 7
D 2
/*
 * Routines for dealing with signals.
 */

E 2
#include "shell.h"
#include "main.h"
#include "nodes.h"	/* for other headers */
#include "eval.h"
#include "jobs.h"
I 7
#include "show.h"
E 7
#include "options.h"
#include "syntax.h"
D 6
#include "signames.h"
E 6
#include "output.h"
#include "memalloc.h"
#include "error.h"
#include "trap.h"
#include "mystring.h"
D 7
#include <signal.h>
E 7


/*
 * Sigmode records the current value of the signal handlers for the various
 * modes.  A value of zero means that the current handler is not known.
 * S_HARD_IGN indicates that the signal was ignored on entry to the shell,
 */

#define S_DFL 1			/* default signal handling (SIG_DFL) */
#define S_CATCH 2		/* signal is caught */
#define S_IGN 3			/* signal is ignored (SIG_IGN) */
#define S_HARD_IGN 4		/* signal is ignored permenantly */
I 3
#define S_RESET 5		/* temporary - to reset a hard ignored sig */
E 3


extern char nullstr[1];		/* null string */

D 6
char *trap[MAXSIG+1];		/* trap handler commands */
MKINIT char sigmode[MAXSIG];	/* current value of signal */
char gotsig[MAXSIG];		/* indicates specified signal received */
E 6
I 6
char *trap[NSIG+1];		/* trap handler commands */
MKINIT char sigmode[NSIG];	/* current value of signal */
char gotsig[NSIG];		/* indicates specified signal received */
E 6
D 2
int pendingsigs;		/* indicates some signal received */
E 2
I 2
int pendingsigs;			/* indicates some signal received */
E 2

I 9
static int getsigaction __P((int, sig_t *));

E 9
D 2

E 2
/*
 * The trap builtin.
 */

D 7
trapcmd(argc, argv)  char **argv; {
E 7
I 7
int
trapcmd(argc, argv)
	int argc;
	char **argv; 
{
E 7
	char *action;
	char **ap;
	int signo;

	if (argc <= 1) {
D 6
		for (signo = 0 ; signo <= MAXSIG ; signo++) {
E 6
I 6
		for (signo = 0 ; signo <= NSIG ; signo++) {
E 6
			if (trap[signo] != NULL)
				out1fmt("%d: %s\n", signo, trap[signo]);
		}
		return 0;
	}
	ap = argv + 1;
	if (is_number(*ap))
		action = NULL;
	else
		action = *ap++;
	while (*ap) {
D 6
		if ((signo = number(*ap)) < 0 || signo > MAXSIG)
E 6
I 6
		if ((signo = number(*ap)) < 0 || signo > NSIG)
E 6
			error("%s: bad trap", *ap);
		INTOFF;
		if (action)
			action = savestr(action);
		if (trap[signo])
			ckfree(trap[signo]);
		trap[signo] = action;
		if (signo != 0)
			setsignal(signo);
		INTON;
		ap++;
	}
	return 0;
}



/*
 * Clear traps on a fork.
 */

void
clear_traps() {
	char **tp;

D 6
	for (tp = trap ; tp <= &trap[MAXSIG] ; tp++) {
E 6
I 6
	for (tp = trap ; tp <= &trap[NSIG] ; tp++) {
E 6
		if (*tp && **tp) {	/* trap not NULL or SIG_IGN */
			INTOFF;
			ckfree(*tp);
			*tp = NULL;
			if (tp != &trap[0])
				setsignal(tp - trap);
			INTON;
		}
	}
}



/*
 * Set the signal handler for the specified signal.  The routine figures
 * out what it should be set to.
 */

D 7
int
setsignal(signo) {
E 7
I 7
long
setsignal(signo) 
	int signo;
{
E 7
	int action;
D 7
	sig_t sigact;
E 7
I 7
	sig_t sigact = SIG_DFL;
E 7
	char *t;
	extern void onsig();
I 3
D 9
	extern sig_t getsigaction();
E 9
E 3

	if ((t = trap[signo]) == NULL)
		action = S_DFL;
	else if (*t != '\0')
		action = S_CATCH;
	else
		action = S_IGN;
	if (rootshell && action == S_DFL) {
		switch (signo) {
		case SIGINT:
			if (iflag)
				action = S_CATCH;
			break;
D 2
#ifndef DEBUG
E 2
		case SIGQUIT:
I 2
#ifdef DEBUG
			{
			extern int debug;

			if (debug)
				break;
			}
E 2
#endif
I 2
			/* FALLTHROUGH */
E 2
		case SIGTERM:
			if (iflag)
				action = S_IGN;
			break;
#if JOBS
		case SIGTSTP:
		case SIGTTOU:
D 4
			if (jflag)
E 4
I 4
			if (mflag)
E 4
				action = S_IGN;
			break;
#endif
		}
	}
I 8

D 9
	if (signo == SIGKILL) 
		/* Pretend it worked */
		return 0;

E 9
E 8
	t = &sigmode[signo - 1];
D 3
	if (*t == 0) {	/* current setting unknown */
		/*
		 * There is a race condition here if action is not S_IGN.
		 * A signal can be ignored that shouldn't be.
E 3
I 3
	if (*t == 0) {	
		/* 
		 * current setting unknown 
E 3
		 */
D 3
		if ((int)(sigact = signal(signo, SIG_IGN)) == -1)
			error("Signal system call failed");
E 3
I 3
D 9
		sigact = getsigaction(signo);
E 9
I 9
		if (!getsigaction(signo, &sigact)) {
			/*
			 * Pretend it worked; maybe we should give a warning
			 * here, but other shells don't. We don't alter
			 * sigmode, so that we retry every time.
			 */
			return 0;
		}
E 9
E 3
		if (sigact == SIG_IGN) {
D 3
			*t = S_HARD_IGN;
E 3
I 3
D 4
			if (jflag && (signo == SIGTSTP || 
E 4
I 4
			if (mflag && (signo == SIGTSTP || 
E 4
			     signo == SIGTTIN || signo == SIGTTOU)) {
				*t = S_IGN;	/* don't hard ignore these */
			} else
				*t = S_HARD_IGN;
E 3
		} else {
D 3
			*t = S_IGN;
E 3
I 3
			*t = S_RESET;	/* force to be set */
E 3
		}
	}
	if (*t == S_HARD_IGN || *t == action)
		return 0;
	switch (action) {
D 2
		case S_DFL:	   sigact = SIG_DFL;		break;
		case S_CATCH:	   sigact = onsig;		break;
		case S_IGN:	   sigact = SIG_IGN;		break;
E 2
I 2
		case S_DFL:	sigact = SIG_DFL;	break;
		case S_CATCH:  	sigact = onsig;		break;
		case S_IGN:	sigact = SIG_IGN;	break;
E 2
	}
	*t = action;
D 7
	return (int)signal(signo, sigact);
E 7
I 7
	return (long)signal(signo, sigact);
E 7
}

I 3
/*
 * Return the current setting for sig w/o changing it.
 */
D 9
sig_t
D 7
getsigaction(signo) {
E 7
I 7
getsigaction(signo) 
E 9
I 9
static int
getsigaction(signo, sigact) 
E 9
	int signo;
I 9
	sig_t *sigact;
E 9
{
E 7
	struct sigaction sa;

	if (sigaction(signo, (struct sigaction *)0, &sa) == -1)
D 9
		error("Sigaction system call failed");

D 7
	return sa.sa_handler;
E 7
I 7
	return (sig_t) sa.sa_handler;
E 9
I 9
		return 0;
	*sigact = (sig_t) sa.sa_handler;
	return 1;
E 9
E 7
}
E 3

D 2

E 2
/*
 * Ignore a signal.
 */

void
D 7
ignoresig(signo) {
E 7
I 7
ignoresig(signo) 
	int signo;
{
E 7
	if (sigmode[signo - 1] != S_IGN && sigmode[signo - 1] != S_HARD_IGN) {
		signal(signo, SIG_IGN);
	}
	sigmode[signo - 1] = S_HARD_IGN;
}


#ifdef mkinit
D 6
INCLUDE "signames.h"
E 6
I 6
INCLUDE <signal.h>
E 6
INCLUDE "trap.h"

SHELLPROC {
	char *sm;

	clear_traps();
D 6
	for (sm = sigmode ; sm < sigmode + MAXSIG ; sm++) {
E 6
I 6
	for (sm = sigmode ; sm < sigmode + NSIG ; sm++) {
E 6
		if (*sm == S_IGN)
			*sm = S_HARD_IGN;
	}
}
#endif



/*
 * Signal handler.
 */

void
D 7
onsig(signo) {
E 7
I 7
onsig(signo) 
	int signo;
{
E 7
	signal(signo, onsig);
	if (signo == SIGINT && trap[SIGINT] == NULL) {
		onint();
		return;
	}
	gotsig[signo - 1] = 1;
	pendingsigs++;
}



/*
 * Called to execute a trap.  Perhaps we should avoid entering new trap
 * handlers while we are executing a trap handler.
 */

void
dotrap() {
	int i;
I 2
	int savestatus;
E 2

	for (;;) {
		for (i = 1 ; ; i++) {
			if (gotsig[i - 1])
				break;
D 6
			if (i >= MAXSIG)
E 6
I 6
			if (i >= NSIG)
E 6
				goto done;
		}
		gotsig[i - 1] = 0;
I 2
		savestatus=exitstatus;
E 2
		evalstring(trap[i]);
I 2
		exitstatus=savestatus;
E 2
	}
done:
	pendingsigs = 0;
}



/*
 * Controls whether the shell is interactive or not.
 */

D 4
int is_interactive;
E 4

void
D 7
setinteractive(on) {
E 7
I 7
setinteractive(on)
	int on;
{
E 7
I 4
	static int is_interactive;

E 4
	if (on == is_interactive)
		return;
	setsignal(SIGINT);
	setsignal(SIGQUIT);
	setsignal(SIGTERM);
	is_interactive = on;
}



/*
 * Called to exit the shell.
 */

void
D 7
exitshell(status) {
E 7
I 7
exitshell(status) 
	int status;
{
E 7
	struct jmploc loc1, loc2;
	char *p;

	TRACE(("exitshell(%d) pid=%d\n", status, getpid()));
D 4
	if (setjmp(loc1.loc))  goto l1;
	if (setjmp(loc2.loc))  goto l2;
E 4
I 4
	if (setjmp(loc1.loc)) {
		goto l1;
	}
	if (setjmp(loc2.loc)) {
		goto l2;
	}
E 4
	handler = &loc1;
	if ((p = trap[0]) != NULL && *p != '\0') {
		trap[0] = NULL;
		evalstring(p);
	}
l1:   handler = &loc2;			/* probably unnecessary */
	flushall();
#if JOBS
	setjobctl(0);
#endif
l2:   _exit(status);
}
E 1
