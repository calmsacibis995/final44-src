/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pcs.c,v $
 * Revision 2.5  89/04/05  18:16:25  rvb
 * 	Changes for J in debugger by rfr.
 * 	[89/04/05            rvb]
 * 
 * Revision 2.4  89/03/09  21:34:59  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:41:56  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Jan-87  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Conditionalized kdb code under KERNEL and changed pathnames
 *	of include files to be kernel relative in order to make
 *	kdb part of the kernel rather than a separate library.
 *
 * 24-Nov-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Changed to use "SINGLE" and "CONTIN" instead of Sun Unix
 *	constants "PTRACE_CONT" and "PTRACE_SINGLE".
 *	Changed type of runmode to integer.
 *
 * 28-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Continue execution even if pid is 0.
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)pcs.c 1.1 86/02/03 SMI";
#endif
/*
 * adb - process control
 */

#include <sun3/kdb/adb.h>
#include <sun3/kdb/pcs.h>
#include <sys/ptrace.h>

/* breakpoints */
struct	bkpt *bkpthead;

int	loopcnt;
extern addr_t filex;

subpcs(modif)
	int modif;
{
	register int check;
	int execsig;
	int	runmode;
	register struct bkpt *bkptr;
	char *comptr;
	int i, line, hitbp = 0;
	char *m;

	execsig = 0;
	loopcnt = count;
	switch (modif) {


	case 'd':
		bkptr = bkptlookup(dot);
		if (bkptr == 0)
			error("no breakpoint set");
		bkptr->flag = 0;
		return;


	case 'b':
		bkptr = bkptlookup(dot);
		if (bkptr)
			bkptr->flag = 0;
		for (bkptr = bkpthead; bkptr; bkptr = bkptr->nxtbkpt)
			if (bkptr->flag == 0)
				break;
		if (bkptr == 0) {
			bkptr =
			    (struct bkpt *)sbrk(sizeof *bkptr);
			if (bkptr == 0)
				error("bkpt: no memory");
			bkptr->nxtbkpt = bkpthead;
			bkpthead = bkptr;
		}
		bkptr->loc = dot;
		bkptr->initcnt = bkptr->count = count;
		bkptr->flag = BKPTSET;
		check = MAXCOM-1;
		comptr = bkptr->comm;
		(void) rdc(); lp--;
		do
			*comptr++ = readchar();
		while (check-- && lastc != '\n');
		*comptr = 0; lp--;
		if (check)
			return;
		error("bkpt command too long");

	case 'i':
	case 't':
		if (!hadaddress) error("which signal?");
		if ( expv <= 0 || expv >=NSIG )
			error("signal number out of range");
		sigpass[ expv ] = modif == 'i';
		return;


	case 's':
	case 'S':
#ifdef	DEBUG
		printf("subpcs: single-step\n");
#endif	DEBUG
		execsig = getsig(signo);
		sstepmode = STEP_NORM;
		runmode = SINGLE;
		break;

	    case 'p': case 'P':

		runmode = SINGLE;
		execsig = getsig(signo);
		sstepmode = STEP_PRINT;
		break;

	    case 'j': case 'J':

		runmode = SINGLE;
		execsig = getsig(signo);
		sstepmode = isupper(modif) ? STEP_RETURN : STEP_CALLT;
		call_depth = 1;
		icount = 0;
		break;

	case 'c':
		runmode = CONTIN;
		execsig = getsig(signo);
		sstepmode = STEP_NONE;
		break;

	default:
		error("bad modifier");
	}

	if (loopcnt > 0){
#ifdef	DEBUG
		printf("subpcs: runpcs(%d, 0)\n", runmode);
#endif	DEBUG
		runpcs(runmode, 0);
	}
}
