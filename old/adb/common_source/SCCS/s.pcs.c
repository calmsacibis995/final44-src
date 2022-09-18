h10954
s 00008/00001/00478
d D 5.6 91/04/04 18:01:57 bostic 6 5
c new copyright; att/bsd/shared
e
s 00008/00010/00471
d D 5.5 89/04/09 16:16:17 torek 5 4
c fix :r breakpoint-skipping code; simplify; comment
e
s 00010/00003/00471
d D 5.4 89/02/04 23:24:35 torek 4 3
c mr-frog reminded me: need to invalidate ptrace cache
c when subprocess runs.  how did I ever forget?
e
s 00012/00016/00462
d D 5.3 89/01/17 17:46:17 torek 3 2
c simplify: starting new process is like restarting old,
c since setup() fishes out the start PC; junk the `new process' flag.
c Fix starting with single step: exect() works only on VAX, execve()
c works everywhere.
e
s 00000/00001/00478
d D 5.2 89/01/17 15:07:13 torek 2 1
c :s on new process should not decrement run count
e
s 00479/00000/00000
d D 5.1 89/01/16 20:24:47 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 6
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 6
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif
E 6
I 6
#endif /* not lint */
E 6

/*
 * adb - subprocess control
 */

#include "defs.h"
#include "bkpt.h"
#include <machine/reg.h>	/* for getpc() *//* XXX */
#include <sys/file.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

extern char NOBKPT[];
extern char SZBKPT[];
extern char EXBKPT[];
extern char NOPCS[];
extern char BADMOD[];
extern char NOFORK[];
extern char ENDPCS[];
extern char BADWAIT[];

struct bkpt *bkpthead;		/* head of breakpoint list */

static long runcount;		/* number of times to loop past breakpoints */

/* bpstate remembers whether we have installed the breakpoints */
static enum { BPOUT, BPIN } bpstate;

char	*malloc();

/* run modes */
#define	CONTINUOUS	0
#define	SINGLESTEP	1
D 3
#define	NEW		2	/* starting new process, no pc to set */
E 3

/* sub process control */

subpcs(modif)
	int modif;
{
	register int check;
D 3
	int execsig = 0, runmode;
E 3
	register struct bkpt *bp;
I 3
	int execsig, runmode;
E 3
	char *comptr;

	switch (modif) {

	case 'd':
		/* delete breakpoint */
		if ((bp = scanbkpt(dot)) == NULL)
			error(NOBKPT);
		bp->state = BKPT_FREE;
		return;

	case 'D':
		/* delete all breapoints */
		for (bp = bkpthead; bp != NULL; bp = bp->next)
			bp->state = BKPT_FREE;
		return;

	case 'b':
	case 'B':
		/* set breakpoint */
D 5
		if ((bp = scanbkpt(dot)) != NULL)
			bp->state = BKPT_FREE;
		else {
E 5
I 5
		if ((bp = scanbkpt(dot)) == NULL) {
			/* find a free one, or make one */
E 5
			for (bp = bkpthead; bp != NULL; bp = bp->next)
				if (bp->state == BKPT_FREE)
					break;
			if (bp == NULL) {
				bp = (struct bkpt *)malloc(sizeof *bp);
				if (bp == NULL)
					error(EXBKPT);
				bp->next = bkpthead;
				bkpthead = bp;
			}
		}
		bp->loc = dot;
		bp->initcnt = bp->count = ecount;
		bp->state = BKPT_SET;
		check = MAX_BKPTCOM - 1;
		comptr = bp->comm;
		(void) rdc();
		unreadc();
		do {
			*comptr++ = readchar();
		} while (check-- && lastc != '\n');
		*comptr = 0;
		unreadc();
		if (check == 0)
			error(SZBKPT);
		return;

	case 'k':
	case 'K':
		/* kill process */
		if (pid == 0)
			error(NOPCS);
		adbprintf("%d: killed", pid);
		endpcs();
		return;

	case 'r':
	case 'R':
		/* run program */
		endpcs();
		setup();
		runcount = ecount;
D 3
		runmode = CONTINUOUS | NEW;
E 3
I 3
		runmode = CONTINUOUS;
E 3
		execsig = 0;
D 5
		if (gavedot) {
			if (scanbkpt(dot) == NULL)
				runcount++;
		} else {
			if (scanbkpt(entrypc()) == NULL)
				runcount++;
		}
E 5
I 5
		/* if starting at a breakpoint, run over it */
		if (scanbkpt(gavedot ? dot : entrypc()) != NULL)
			runcount++;
E 5
		break;

	case 's':
	case 'S':
		/* single step, with optional signal */
		runcount = ecount;
		if (pid) {
			runmode = SINGLESTEP;
			execsig = oexpr() ? expv : signo;
		} else {
			setup();
D 3
			runmode = SINGLESTEP | NEW;
E 3
I 3
			runmode = SINGLESTEP;
E 3
D 2
			runcount--;
E 2
			execsig = 0;
I 3
			runcount--;
E 3
		}
		break;

	case 'c':
	case 'C':
	case 0:
		/* continue with optional signal */
		runcount = ecount;
		if (pid == 0)
			error(NOPCS);
		runmode = CONTINUOUS;
		execsig = oexpr() ? expv : signo;
		break;

	default:
		error(BADMOD);
I 3
		/* NOTREACHED */
E 3
	}

D 3
	if (runcount > 0 && runpcs(runmode & ~NEW, execsig, runmode & NEW))
E 3
I 3
	if (runcount > 0 && runpcs(runmode, execsig))
E 3
		adbprintf("breakpoint%16t");
	else
		adbprintf("stopped at%16t");
	delbp();
	printpc();
}

/*
 * Print all breakpoints.
 */
printbkpts()
{
	register struct bkpt *b;

	adbprintf("breakpoints\ncount%8tbkpt%24tcommand\n");
	for (b = bkpthead; b != NULL; b = b->next) {
		if (b->state != BKPT_FREE) {
			adbprintf("%-8.8D", b->count);
			psymoff("%R", b->loc, SP_INSTR, maxoff, "%24t");
			prints(b->comm);
		}
	}
}

/*
 * Remove (restore to original instruction(s)) all breakpoints.
 */
delbp()
{
	register struct bkpt *b;

	if (bpstate != BPOUT) {
		for (b = bkpthead; b != NULL; b = b->next)
			if (b->state != BKPT_FREE && clr_bpt(b))
				bperr(b, "clear");
		bpstate = BPOUT;
	}
}

/*
 * Insert all breakpoints.
 */
setbp()
{
	register struct bkpt *b;

	if (bpstate != BPIN) {
		for (b = bkpthead; b != NULL; b = b->next)
			if (b->state != BKPT_FREE && set_bpt(b))
				bperr(b, "set");
		bpstate = BPIN;
	}
}

static
bperr(b, how)
	struct bkpt *b;
	char *how;
{

	adbprintf("cannot %s breakpoint: ", how);
	psymoff("%R", b->loc, SP_INSTR, maxoff, "\n");
}

/*
D 4
 * ... return true iff stopped due to breakpoint
E 4
I 4
 * Run subprocess for a while.
 * Return true iff stopped due to breakpoint.
E 4
 */
int
D 3
runpcs(runmode, execsig, newproc)
	int runmode, execsig, newproc;
E 3
I 3
runpcs(runmode, execsig)
	int runmode, execsig;
E 3
{
	register struct bkpt *bkpt;
	int rc;

	/* always set pc, so that expr>pc works too */
D 3
	setpc(gavedot ? dot : newproc ? entrypc() : getpc());
E 3
I 3
	setpc(gavedot ? dot : getpc());
E 3
	adbprintf("%s: running\n", symfile.name);
	while (--runcount >= 0) {
D 3
#ifdef DEBUG
		adbprintf("\n%s @ %X sig %D\n",
			newproc ? "start" : "continue",
			getpc(), execsig);		/* XXX */
#endif
E 3
		/* BEGIN XXX (machine dependent?, delete ptrace, etc) */
		if (runmode == SINGLESTEP)
			delbp();	/* hardware handles single-stepping */
		else {	/* continuing from a breakpoint is hard */
D 3
			if (!newproc && (bkpt = scanbkpt(getpc())) != NULL) {
E 3
I 3
			if ((bkpt = scanbkpt(getpc())) != NULL) {
E 3
				execbkpt(bkpt, execsig);
				execsig = 0;
			}
			setbp();
		}
		(void) ptrace(runmode == CONTINUOUS ? PT_CONTINUE : PT_STEP,
D 3
			pid, (int *)(newproc ? 1 : getpc()), execsig);
E 3
I 3
			pid, (int *)getpc(), execsig);
E 3
		/* END XXX */
I 4

		/* paranoia, SP_DATA usually sufficient, but this is easy */
		cacheinval(SP_INSTR | SP_DATA);

E 4
		bpwait();
		checkerr();
		execsig = 0;
		delbp();
		readregs();

		if (signo != 0 || (bkpt = scanbkpt(getpc())) == NULL) {
			execsig = signo;
			rc = 0;
			continue;
		}
		/* stopped by BPT instruction */
#ifdef DEBUG
		adbprintf("\n BPT code: comm=%s%8tstate=%d",
		    bkpt->comm, bkpt->state);
#endif
		dot = bkpt->loc;
		switch (bkpt->state) {
			char *p;

		case BKPT_SET:
			bkpt->state = BKPT_TRIPPED;
			if (*bkpt->comm == '\n')
				break;
			p = lp;
			command(bkpt->comm, ':');
			lp = p;
			if (gavedot && edot == 0) /* maybe dot==0 ??? */
				break;
			if (--bkpt->count == 0)
				break;
			/* FALLTHROUGH */

		case BKPT_TRIPPED:
			execbkpt(bkpt, execsig);
			execsig = 0;
			runcount++;
			continue;

		default:
			panic("runpcs");
			/* NOTREACHED */
		}
		bkpt->count = bkpt->initcnt;
		rc = 1;
	}
	return (rc);
}

endpcs()
{
	register struct bkpt *bp;

	if (pid) {
		(void) ptrace(PT_KILL, pid, (int *)0, 0);	/* XXX */
		pid = 0;
		for (bp = bkpthead; bp != NULL; bp = bp->next)
			if (bp->state != BKPT_FREE)
				bp->state = BKPT_SET;
	}
	bpstate = BPOUT;
}

#ifdef VFORK
nullsig()
{

}
#endif

setup()
{

I 4
	cacheinval(SP_INSTR | SP_DATA);	/* paranoia */
E 4
	(void) close(symfile.fd);
	symfile.fd = -1;
#ifndef VFORK
#define vfork fork
#endif
	if ((pid = vfork()) == 0) {
		(void) ptrace(PT_TRACE_ME, 0, (int *)0, 0);	/* XXX */
#ifdef VFORK
		(void) signal(SIGTRAP, nullsig);
#endif
		(void) signal(SIGINT, sigint);
		(void) signal(SIGQUIT, sigquit);
		doexec();
		exit(0);
D 4
	} else if (pid == -1)
E 4
I 4
	} else if (pid == -1) {
		pid = 0;
E 4
		error(NOFORK);
D 4
	else {
E 4
I 4
	} else {
E 4
		bpwait();
		readregs();
		symfile.fd = open(symfile.name, wtflag);
		if (errflag) {
			adbprintf("%s: cannot execute\n", symfile.name);
			endpcs();
			error((char *)0);
		}
	}
	bpstate = BPOUT;
}

I 5
/*
 * Single step over a location containing a breakpoint.
 */
E 5
execbkpt(bp, execsig)
	struct bkpt *bp;
	int execsig;
{

#ifdef DEBUG
	adbprintf("exbkpt: %d\n", bp->count);
#endif
	delbp();
	(void) ptrace(PT_STEP, pid, (int *)bp->loc, execsig);	/* XXX */
	bp->state = BKPT_SET;
	bpwait();
	checkerr();
	readregs();
}

static char separators[] = "<> \t\n";

doexec()
{
	register char *p, **ap;
	register int c;
	char *argl[LINELEN / 2 + 1];
	char args[LINELEN];
	extern char **environ;
	char *index();

	ap = argl;
	p = args;
	*ap++ = symfile.name;
	do {
		switch (c = rdc()) {

		case '\n':
			break;

		case '<':
			setfile(0, O_RDONLY, 0, p, "open");
			break;

		case '>':
			setfile(1, O_CREAT|O_WRONLY, 0666, p, "create");
			break;

		default:
			*ap = p;
			while (index(separators, c) == NULL) {
				*p++ = c;
				c = readchar();
			}
			*p++ = '\0';
			ap++;
		}
	} while (c != '\n');
	unreadc();
	*ap++ = 0;
D 3
	exect(symfile.name, argl, environ);
E 3
I 3
	execve(symfile.name, argl, environ);
E 3
	perror(symfile.name);
}

static int
setfile(fd, flags, mode, namebuf, err)
	int fd, flags, mode;
	char *namebuf, *err;
{
	register char *p = namebuf;
	register int c = rdc();

	while (index(separators, c) == NULL) {
		*p++ = c;
		c = readchar();
	}
	*p = 0;
	(void) close(fd);
	if (open(namebuf, flags, mode) < 0) {
		adbprintf("%s: cannot %s\n", namebuf, err);
		_exit(0);
		/* NOTREACHED */
	}
}

struct bkpt *
scanbkpt(a)
	register addr_t a;
{
	register struct bkpt *bp;

	for (bp = bkpthead; bp != NULL; bp = bp->next)
		if (bp->state != BKPT_FREE && bp->loc == a)
			break;
	return (bp);
}

bpwait()
{
	register int w;
	union wait status;

	(void) signal(SIGINT, SIG_IGN);
	while ((w = wait(&status)) != pid && w != -1)
		 /* void */ ;
	(void) signal(SIGINT, intcatch);
	if (w == -1) {
		pid = 0;
		errflag = BADWAIT;
	} else if (!WIFSTOPPED(status)) {
		sigcode = 0;
		if ((signo = status.w_termsig) != 0)
			sigprint();
		if (status.w_coredump) {
			prints(" - core dumped");
			(void) close(corefile.fd);
			setcore();
		}
		pid = 0;
		bpstate = BPOUT;
		errflag = ENDPCS;
	} else {
		signo = status.w_stopsig;
		sigcode = ptrace(PT_READ_U, pid,
				 &((struct user *)0)->u_code, 0); /* XXX */
		if (signo != SIGTRAP)
			sigprint();
		else
			signo = 0;
		flushbuf();
	}
}
E 1
