/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	runpcs.c,v $
 * Revision 2.6  89/04/05  18:16:47  rvb
 * 	Changes for J in debugger by rfr.
 * 	[89/04/05            rvb]
 * 
 * Revision 2.5  89/03/09  21:35:32  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  19:42:32  gm0w
 * 	Changes for cleanup.
 * 
 * 08-Feb-88  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Removed else leg of KERNEL conditionals and fixed 
 *	includes as part of kernel cleanup.
 *
 * 29-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Define pcfudge as int to make gcc happy.
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
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)runpcs.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif


/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

/*
 * adb - subprocess running routines
 */

#include <sun3/kdb/adb.h>
#include <sun3/kdb/pcs.h>
#include <sun3/reg.h>
#include <sun3/kdb/fpascii.h>

struct	bkpt *bkpthead;
extern debugging;

int	loopcnt;

#ifdef	vax
#define SZBPT 1
#ifndef	lint
	extern	bpt;
	asm(".globl _bpt; _bpt: bpt");
#else
	int	bpt;
#endif
#endif
#ifdef	mc68000
#define SZBPT 2
#define PCFUDGE (-2)
#ifndef	lint
	extern	bpt;
	asm("		.globl _bpt ");
	asm("		.even	    ");
	    asm("_bpt:	trap   #15   ");
#else
	int	bpt;
#endif
#endif

getsig(sig)
	int sig;
{

	return (expr(0) ? expv : sig);
}

addr_t userpc;
int pcfudge = 0;	/* how much to fudge the PC by after hitting a breakpoint */

runpcs(runmode, execsig)
	int	runmode;
	int execsig;
{
	int rc = 0;
	register struct bkpt *bkpt;

	if (hadaddress)
		userpc = dot;
	if (execsig  == 0)
		printf("kernel: running\n");
#ifdef	DEBUG
	printf("\ncontinue %x %d\n", userpc, execsig);
#endif	DEBUG
		if (runmode==SINGLE)
			delbp();
		else {
			/*
			 *	Need to fudge PC if we hit a 
			 *	breakpoint after continuing
			 */
			if (runmode == CONTIN){
#ifdef	DEBUG
				printf("runpcs: setting pcfudge to %d\n", PCFUDGE);
#endif	DEBUG
				pcfudge = PCFUDGE;
			}
			if (bkpt = bkptlookup(userpc)) {
				execbkpt(bkpt, execsig);
				execsig = 0;
			}
			setbp();
		}

#ifdef	DEBUG
		printf("reset(%d) from runpcs()\n", runmode);
#endif	DEBUG
		reset(runmode);
}

int execbkptf = 0;

/*
 * determines whether to stop, and what to print if so
 * flag:	1 if entered by trace trap
 * execsig:	(seems not to be used by kernel debugger)
 *
 * exits:
 *	skipping breakpoint (execbkptf != 0):
 *		runpcs(CONTIN)
 *      next iteration of breakpoint:
 *		runpcs(CONTIN)
 *	next iteration of single-step:
 *		runpcs(SINGLE)
 *
 *	stopped by breakpoint:
 *		returns 1
 *	stopped by single-step, or
 *		by CALL/RET:
 *		returns 0
 *
 *	normal return MUST reset sstepmode!
 */

nextpcs(flag, execsig)
{
	int			rc;
	register struct bkpt	*bkpt;

	curpcb->pcb_regs.r_sr &= ~SR_TRACE;
	signo = flag?SIGTRAP:0;
	/*
	 *	Fudge the PC if we hit a breakpoint
	 */
#ifdef	DEBUG
		printf("nextpcs: signo = %d, pcfudge = %d\n", signo, pcfudge);
#endif	DEBUG
	if (signo == 0 && pcfudge){
		userpc = readreg(REG_PC);
#ifdef	DEBUG
		printf("nextpcs: fudging PC 0x%x by %d\n", userpc, pcfudge);
#endif	DEBUG
		userpc += pcfudge;
		pc_cheat(userpc);
		pcfudge = 0;
	}
	delbp();
	if (execbkptf)
	{
	    execbkptf = 0;
	    runpcs(CONTIN, 1);
	}

	if (signo == 0 && (bkpt = bkptlookup(userpc))) {
		dot = bkpt->loc;
		if (
		      (bkpt->comm[0] == '\n' || /* HACK HERE */
		      command(bkpt->comm, ':')) && --bkpt->count) {
			loopcnt++;
			execbkpt(bkpt, execsig);
			execsig = 0;
		} else {
			bkpt->count = bkpt->initcnt;
			rc = 1;
		}
	} else {
		execsig = signo;
		rc = 0;
	}
	if (interrupted) return(rc);

        if (--loopcnt > 0) {
		if (sstepmode == STEP_PRINT){
			printf("%16t");
			printpc();
		}
#ifdef	DEBUG
		printf("nextpcs: runpcs(%d, 1)\n",
			rc?CONTIN:SINGLE);
#endif	DEBUG
		runpcs(rc?CONTIN:SINGLE, 1);
	}
	if (sstepmode == STEP_RETURN) {
		/*
		 *	Keep going until matching return
		 */

		int 	ins = (chkget(dot,ISP) >> 16) & 0xffff;

		if ((ins == I_RTS) && (--call_depth == 0))
			printf("%d instructions executed\n", icount);
		else {
			if ((ins & M_JSR) == I_JSR || (ins & M_BSR) == I_BSR ||
				    ins == I_RTS) {
				register int i;

				printf("[after %6d]     ", icount);
				for (i = call_depth; --i > 0;)
					printf("  ");
				printpc();
			}
			if ((ins & M_JSR) == I_JSR || (ins & M_BSR) == I_BSR)
				call_depth++;

			loopcnt++;
			icount++;
			runpcs(SINGLE, 1);
		}
	}
	if (sstepmode == STEP_CALLT){
		/* keep going until CALL or RETURN */
		int	ins;

		ins = (chkget(dot,ISP) >> 16) & 0xffff;
		if ((ins & M_JSR) == I_JSR || (ins & M_BSR) == I_BSR ||
		    ins == I_RTS) {
			printf("%d instructions executed\n", icount);
		}
		else {
			loopcnt++;
			icount++;
			runpcs(SINGLE, 1);
		}
	}
	sstepmode = STEP_NONE;	/* don't wait for CALL/RET */
	return (rc);
}

#define BPOUT	0
#define BPIN	1

int	bpstate = BPOUT;

execbkpt(bp, execsig)
	struct bkpt *bp;
	int execsig;
{
#ifdef	DEBUG
	printf("exbkpt: %d\n", bp->count);
#endif	DEBUG
	delbp();
	bp->flag = BKPTSET;
	execbkptf++;
#ifdef	DEBUG
	printf("reset(%d) from execbkpt()\n", SINGLE);
#endif	DEBUG
	reset(SINGLE);
}


struct bkpt *
bkptlookup(addr)
	addr_t addr;
{
	register struct bkpt *bp;

	for (bp = bkpthead; bp; bp = bp->nxtbkpt)
		if (bp->flag && bp->loc == addr)
			break;
	return (bp);
}

delbp()
{
	register struct bkpt *bp;

	if (bpstate == BPOUT)
		return;
	for (bp = bkpthead; bp; bp = bp->nxtbkpt)
		if (bp->flag)
		{
			register addr_t	a = bp->loc;

			put(a, ISP, (bp->ins&~0xffff)|(get(a, ISP)&0xffff));
		}
	bpstate = BPOUT;
}

setbp()
{
	register struct bkpt *bp;

	if (bpstate == BPIN)
		return;
	for (bp = bkpthead; bp; bp = bp->nxtbkpt)
		if (bp->flag) {
			register addr_t	a;

			a = bp->loc;
			bp->ins = get(a, ISP);
			put(a, ISP, (I_BPT << 16) | (bp->ins)&0xffff);
#ifdef	DEBUG
			if (debugging >=2)
				prints("set breakpoint\n");
#endif	DEBUG
		}
	bpstate = BPIN;
}


#ifdef	VFORK
nullsig()
{

}
#endif
