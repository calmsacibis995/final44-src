h35376
s 00045/00045/00113
d D 7.4 90/05/03 17:47:19 sklower 4 3
c first crack at torek changes, may need bug fixes
e
s 00017/00014/00141
d D 7.3 86/12/15 20:26:52 sam 3 2
c lint
e
s 00011/00011/00144
d D 7.2 86/11/23 13:36:05 sam 2 1
c move machine dependencies to ../machine/kdbparam.h
e
s 00155/00000/00000
d D 7.1 86/11/20 12:22:07 sam 1 0
c date and time created 86/11/20 12:22:07 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 3

#include "../kdb/defs.h"

D 4
char	*lp;
E 4
I 4
char	*kdblp;
E 4

/* breakpoints */
D 4
BKPTR	bkpthead;
E 4
I 4
BKPTR	kdbbkpthead;
E 4

D 4
char	lastc;
E 4
I 4
char	kdblastc;
E 4

D 4
long	dot;
int	adrflg;
long	loopcnt;
ADDR	userpc = 1;
E 4
I 4
long	kdbdot;
int	kdbadrflg;
long	kdbloopcnt;
ADDR	kdbuserpc = 1;
E 4

D 4
runpcs(runmode, execsig)
E 4
I 4
kdbrunpcs(runmode, execsig)
E 4
{
	register BKPTR bkpt;

D 4
	if (adrflg)
		userpc = dot;
E 4
I 4
	if (kdbadrflg)
		kdbuserpc = kdbdot;
E 4
	if (execsig == 0)
D 4
		printf("kdb: running\n");
E 4
I 4
		kdbprintf("kdb: running\n");
E 4
	if (runmode==SINGLE) {
		/*
		 * To single step, delete the
		 * breakpoints and invoke the
		 * hardware single step in the
		 * main loop.
		 */
D 4
		delbp();
E 4
I 4
		kdbdelbp();
E 4
		reset(SINGLE);
	}
	/*
	 * If we're currently at a breakpoint,
	 * restore the instruction and single
	 * step before continuing.  Otherwise,
	 * we can just set our breakpoints and
	 * continue.
	 */
D 4
	if (bkpt = scanbkpt(userpc)) {
D 3
		execbkpt(bkpt, execsig);
E 3
I 3
		execbkpt(bkpt);
E 4
I 4
	if (bkpt = kdbscanbkpt(kdbuserpc)) {
		kdbexecbkpt(bkpt);
E 4
E 3
		/*NOTREACHED*/
	}
D 4
	setbp();
E 4
I 4
	kdbsetbp();
E 4
	reset(CONTIN);
}

D 4
static	int execbkptf;
E 4
I 4
static	int kdbexecbkptf;
E 4

/*
 * Continue execution after a trap.
 *
 * If tracetrap is nonzero, we've entered here because of a
 * trace trap.  If we're skipping a breakpoint (execbkptf),
 * or this is the next iteration of a breakpoint, continue.
 * If this is the next iteration of a single step, do the
 * next step.  Otherwise return 1 if we stopped because
 * of a breakpoint,
 */
D 3
nextpcs(tracetrap, execsig)
	int tracetrap, execsig;
E 3
I 3
D 4
nextpcs(tracetrap)
E 4
I 4
kdbnextpcs(tracetrap)
E 4
	int tracetrap;
E 3
{
	register BKPTR bkpt;
	short rc;

D 2
	pcb.pcb_psl &= ~TBIT;
E 2
I 2
	clrsstep();			/* clear hardware single step */
E 2
D 4
	delbp();
	if (execbkptf) {
		execbkptf = 0;
		runpcs(CONTIN, 1);
E 4
I 4
	kdbdelbp();
	if (kdbexecbkptf) {
		kdbexecbkptf = 0;
		kdbrunpcs(CONTIN, 1);
E 4
		/*NOTREACHED*/
	}
D 4
	if (!tracetrap && (bkpt = scanbkpt(userpc))) {
E 4
I 4
	if (!tracetrap && (bkpt = kdbscanbkpt(kdbuserpc))) {
E 4
		/*
		 * Stopped at a breakpoint,
		 * execute any command.
		 */
D 4
		dot = bkpt->loc;
E 4
I 4
		kdbdot = bkpt->loc;
E 4
		if (bkpt->flag == BKPTEXEC ||
		    ((bkpt->flag = BKPTEXEC) && bkpt->comm[0] != EOR &&
D 4
		    command(bkpt->comm, ':') && --bkpt->count)) {
			loopcnt++;
D 3
			execbkpt(bkpt, execsig);
			execsig = 0;
E 3
I 3
			execbkpt(bkpt);
E 4
I 4
		    kdbcommand(bkpt->comm, ':') && --bkpt->count)) {
			kdbloopcnt++;
			kdbexecbkpt(bkpt);
E 4
E 3
		} else {
			bkpt->count = bkpt->initcnt;
			rc = 1;
		}
D 3
	} else {
		execsig = 0;
E 3
I 3
	} else
E 3
		rc = 0;
D 3
	}
E 3
D 4
	if (--loopcnt > 0)
		runpcs(rc ? CONTIN : SINGLE, 1);
E 4
I 4
	if (--kdbloopcnt > 0)
		kdbrunpcs(rc ? CONTIN : SINGLE, 1);
E 4
	return (rc);
}

#define BPOUT 0
#define BPIN 1
D 4
static	int bpstate = BPOUT;
E 4
I 4
static	int kdbbpstate = BPOUT;
E 4

D 3
execbkpt(bkptr,execsig)
E 3
I 3
D 4
execbkpt(bkptr)
E 4
I 4
kdbexecbkpt(bkptr)
E 4
E 3
	BKPTR	bkptr;
{

D 4
	delbp();
E 4
I 4
	kdbdelbp();
E 4
D 2
	bkptr->flag=BKPTSET;
E 2
I 2
	bkptr->flag = BKPTSET;
E 2
D 4
	execbkptf++;
E 4
I 4
	kdbexecbkptf++;
E 4
	reset(SINGLE);
}

BKPTR
D 4
scanbkpt(addr)
E 4
I 4
kdbscanbkpt(addr)
E 4
	ADDR addr;
{
	register BKPTR	bkptr;

D 2
	for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
		if (bkptr->flag && bkptr->loc==addr)
E 2
I 2
D 4
	for (bkptr = bkpthead; bkptr; bkptr = bkptr->nxtbkpt)
E 4
I 4
	for (bkptr = kdbbkpthead; bkptr; bkptr = bkptr->nxtbkpt)
E 4
		if (bkptr->flag && bkptr->loc == addr)
E 2
			break;
	return (bkptr);
}

D 4
delbp()
E 4
I 4
kdbdelbp()
E 4
{
D 3
	register ADDR a;
E 3
I 3
	register off_t a;
E 3
	register BKPTR bkptr;

D 2
	if (bpstate==BPOUT)
E 2
I 2
D 4
	if (bpstate == BPOUT)
E 4
I 4
	if (kdbbpstate == BPOUT)
E 4
E 2
		return;
D 2
	for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
E 2
I 2
D 4
	for (bkptr = bkpthead; bkptr; bkptr = bkptr->nxtbkpt)
E 4
I 4
	for (bkptr = kdbbkpthead; bkptr; bkptr = bkptr->nxtbkpt)
E 4
E 2
		if (bkptr->flag) {
D 2
			a=bkptr->loc;
E 2
I 2
			a = bkptr->loc;
E 2
D 3
			put(a, ISP, bkptr->ins);
E 3
I 3
D 4
			put((off_t)a, ISP, (long)bkptr->ins);
E 4
I 4
			kdbput((off_t)a, ISP, (long)bkptr->ins);
E 4
E 3
		}
D 2
	bpstate=BPOUT;
E 2
I 2
D 4
	bpstate = BPOUT;
E 4
I 4
	kdbbpstate = BPOUT;
E 4
E 2
}

D 4
setbp()
E 4
I 4
kdbsetbp()
E 4
{
D 3
	register ADDR a;
E 3
I 3
	register off_t a;
E 3
	register BKPTR bkptr;

D 2
	if (bpstate==BPIN)
E 2
I 2
D 4
	if (bpstate == BPIN)
E 4
I 4
	if (kdbbpstate == BPIN)
E 4
E 2
		return;
D 2
	for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
E 2
I 2
D 4
	for (bkptr = bkpthead; bkptr; bkptr = bkptr->nxtbkpt)
E 4
I 4
	for (bkptr = kdbbkpthead; bkptr; bkptr = bkptr->nxtbkpt)
E 4
E 2
		if (bkptr->flag) {
			a = bkptr->loc;
D 4
			bkptr->ins = get(a, ISP);
D 3
			put(a, ISP, SETBP(bkptr->ins));
E 3
I 3
			put(a, ISP, (long)SETBP(bkptr->ins));
E 4
I 4
			bkptr->ins = kdbget(a, ISP);
			kdbput(a, ISP, (long)SETBP(bkptr->ins));
E 4
E 3
		}
D 2
	bpstate=BPIN;
E 2
I 2
D 4
	bpstate = BPIN;
E 4
I 4
	kdbbpstate = BPIN;
E 4
E 2
}
E 1
