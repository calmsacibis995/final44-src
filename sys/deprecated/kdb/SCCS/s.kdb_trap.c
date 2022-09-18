h63343
s 00041/00041/00064
d D 7.8 90/05/03 17:47:17 sklower 8 7
c first crack at torek changes, may need bug fixes
e
s 00007/00001/00098
d D 7.7 90/04/03 22:17:01 karels 7 6
c attempt to make it possible to put breakpoints in printf
e
s 00003/00001/00096
d D 7.6 89/09/02 12:46:06 karels 6 5
c add :k (kill kernel), with panic from trap like other traps
e
s 00011/00005/00086
d D 7.5 86/12/15 20:26:54 sam 5 4
c lint
e
s 00001/00001/00090
d D 7.4 86/11/23 13:36:07 sam 4 3
c move machine dependencies to ../machine/kdbparam.h
e
s 00010/00003/00081
d D 7.3 86/11/20 15:49:00 sam 3 2
c keep trap info around as well as current proc; move printing 
c of this stuff into machine-dependent routine
e
s 00001/00005/00083
d D 7.2 86/11/20 14:45:04 sam 2 1
c never get eof; use mnemonic for error reset
e
s 00088/00000/00000
d D 7.1 86/11/20 12:22:08 sam 1 0
c date and time created 86/11/20 12:22:08 by sam
e
u
U
t
T
I 1
D 5
/*	%M%	%I%	%E%	*/
E 5
I 5
/*
D 6
 * Copyright (c) 1986 Regents of the University of California.
E 6
I 6
 * Copyright (c) 1986, 1989 Regents of the University of California.
E 6
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 5

/*
 * Trap handler - command loop entry point.
 */
#include "../kdb/defs.h"

D 8
char	*NOEOR;
E 8
I 8
char	*kdbNOEOR;
E 8

D 8
int	executing;
char	*lp;
E 8
I 8
int	kdbexecuting;
char	*kdblp;
E 8
D 2
long	maxpos;
E 2

D 8
char	lastc;
E 8
I 8
char	kdblastc;
E 8
D 2
int	eof;
E 2

D 8
ADDR	userpc;
int	lastcom;
E 8
I 8
ADDR	kdbuserpc;
int	kdblastcom;
E 8

D 8
ADDR	maxoff = MAXOFF;
long	maxpos = MAXPOS;
E 8
I 8
ADDR	kdbmaxoff = MAXOFF;
long	kdbmaxpos = MAXPOS;
E 8

D 3
kdb(type, sp, curproc)
	int type, *sp;
E 3
I 3
/*
 * Kdb trap handler; entered on all fatal
 * and/or debugger related traps or faults.
 */
D 7
kdb(type, code, curproc)
E 7
I 7
kdb(type, code, curproc, kstack)
E 7
	int type, code;
E 3
	struct proc *curproc;
I 7
	int kstack;
E 7
{

I 3
D 8
	var[varchk('t')] = type;
	var[varchk('c')] = code;
	var[varchk('p')] = (int)curproc;
I 7
	if (executing)
		delbp();
	executing = 0;
E 8
I 8
	kdbvar[kdbvarchk('t')] = type;
	kdbvar[kdbvarchk('c')] = code;
	kdbvar[kdbvarchk('p')] = (int)curproc;
	if (kdbexecuting)
		kdbdelbp();
	kdbexecuting = 0;
E 8
	if (kstack)
D 8
		printf("(from kernel stack)\n"); /* after delbp() */
E 7
D 5
	printtrap(type, code);
E 5
I 5
	printtrap((long)type, (long)code);
E 5
E 3
	userpc = dot = pcb.pcb_pc;
E 8
I 8
		kdbprintf("(from kernel stack)\n"); /* after delbp() */
	kdbprinttrap((long)type, (long)code);
	kdbuserpc = kdbdot = kdbpcb.pcb_pc;
E 8
D 3
	var[varchk('t')] = (int)sp;
E 3
	switch (setexit()) {

	case SINGLE:
D 4
		pcb.pcb_psl |= TBIT;
E 4
I 4
		setsstep();		/* hardware single step */
E 4
		/* fall thru... */
	case CONTIN:
		return (1);
I 6
	case PANIC:
		return (0);
E 6
	case 0:
D 5
		if (nextpcs(type, 0))
E 5
I 5
D 8
		if (nextpcs(type))
E 5
			printf("breakpoint%16t");
E 8
I 8
		if (kdbnextpcs(type))
			kdbprintf("breakpoint%16t");
E 8
		else
D 8
			printf("stopped at%16t");
		printpc();
E 8
I 8
			kdbprintf("stopped at%16t");
		kdbprintpc();
E 8
		break;
	}
D 8
	if (executing)
		delbp();
	executing = 0;
E 8
I 8
	if (kdbexecuting)
		kdbdelbp();
	kdbexecuting = 0;
E 8
	for (;;) {
D 8
		flushbuf();
		if (errflg) {
			printf("%s\n", errflg);
			errflg = 0;
E 8
I 8
		kdbflushbuf();
		if (kdberrflg) {
			kdbprintf("%s\n", kdberrflg);
			kdberrflg = 0;
E 8
		}
D 8
		if (mkfault) {
			mkfault=0;
			printc('\n');
			printf(DBNAME);
E 8
I 8
		if (kdbmkfault) {
			kdbmkfault=0;
			kdbprintc('\n');
			kdbprintf(DBNAME);
E 8
		}
		kdbwrite("kdb> ", 5);
D 5
		lp=0; rdc(); lp--;
D 2
		if (eof)
			return (1);
E 2
		command(0, lastcom);
E 5
I 5
D 8
		lp=0; (void) rdc(); lp--;
		(void) command((char *)0, lastcom);
E 5
		if (lp && lastc!='\n')
			error(NOEOR);
E 8
I 8
		kdblp=0; (void) kdbrdc(); kdblp--;
		(void) kdbcommand((char *)0, kdblastcom);
		if (kdblp && kdblastc!='\n')
			kdberror(kdbNOEOR);
E 8
	}
}

/*
 * If there has been an error or a fault, take the error.
 */
D 8
chkerr()
E 8
I 8
kdbchkerr()
E 8
{
D 8
	if (errflg || mkfault)
		error(errflg);
E 8
I 8
	if (kdberrflg || kdbmkfault)
		kdberror(kdberrflg);
E 8
}

/*
 * An error occurred; save the message for
 * later printing, and reset to main command loop.
 */
D 8
error(n)
E 8
I 8
kdberror(n)
E 8
	char *n;
{

D 8
	errflg = n;
E 8
I 8
	kdberrflg = n;
E 8
D 2
	reset(1);
E 2
I 2
	reset(ERROR);
E 2
}
E 1
