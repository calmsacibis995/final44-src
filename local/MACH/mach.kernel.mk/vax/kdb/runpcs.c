/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	runpcs.c,v $
 * Revision 2.5  89/03/09  22:18:04  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  20:23:42  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.3  88/08/10  10:28:14  rvb
 * 	Define label_t kdb_save and friends.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed more lint.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 27-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	sigcode -> kdbsigcode
 *
 *  3-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "single step until matching return" form of ":j".
 *
 * 6-jan-86	David Golub (dbg)
 *  new commands:
 *	:j single-steps until CALL[S,G] or RET encountered,
 *         printing PC at each stop
 *      :p like :s, but prints PC if count not done yet
 *
 */

/*
 *
 *	UNIX debugger
 *
 */

#undef	DEBUG

/* static	char sccsid[] = "@(#)runpcs.c	1.2	(decvax!reilly)	2/18/84"; */

#include <vax/kdb/defs.h>

extern	map	txtmap;

extern	label_t	kdb_save;
extern	int	kdb_setjmp_val;

char		*lp;
long		sigint;
long		sigqit;

/* breakpoints */
bkpt_t		bkpthead;

REGLIST		reglist[];

char		lastc;

INT		fcor;
INT		fsym;
string_t	errflg;
INT		errno;
INT		signo;
INT		kdbsigcode;

long		dot;
string_t	symfil;
INT		wtflag;
INT		pid;
long		expv;
INT		adrflg;
long		loopcnt;

#include <vax/kdb/pcs.h>



/* service routines for sub process control */

getsig(sig)
{
	return(expr(0) ? expv : sig);
}

long userpc = 1;

runpcs(runmode,execsig)
{
	register bkpt_t	bp;
	if ( adrflg ) {
		userpc=dot;
	}
	    if (execsig == 0)
		printf("kernel: running\n");
#ifdef	DEBUG
		printf("\ncontinue %x %d\n",userpc,execsig);
#endif
		if ( runmode==SINGLE ) {
			delbp(); /* hardware handles single-stepping */
		} else { /* continuing from a breakpoint is hard */
			if ( bp=scanbkpt(userpc) ) {
				execbkpt(bp,execsig);
				execsig=0;
			}
			setbp();
		}
#ifdef	DEBUG
		printf("reset(%d) from runpcs()\n", runmode);
#endif	DEBUG
		reset(runmode);
}

INT execbkptf = 0;

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
		INT		rc;
		register bkpt_t	bp;

		pcb.pcb_psl &= ~PSL_T;
		signo = flag?SIGTRAP:0;
		delbp();
		if (execbkptf) {
			execbkptf = 0;
			runpcs(CONTIN, 1);
		}

		if ( (signo==0) && (bp=scanbkpt(userpc)) ) {
		     /* stopped by BPT instruction */
#ifdef	DEBUG
			printf("\n BPT code; '%s'%o'%o'%d",
			bp->comm,bp->comm[0],EOR,bp->flag);
#endif
			dot=bp->loc;
			if ( bp->flag==BKPTEXEC
			    || ((bp->flag=BKPTEXEC)
			    && bp->comm[0]!=EOR
			    && command(bp->comm,':')
			    && --bp->count) ) {
				loopcnt++;
				execbkpt(bp,execsig);
				execsig=0;
			} else {
				bp->count=bp->initcnt;
				rc=1;
			}
		} else {
			execsig=signo;
			rc=0;
		}
	if (--loopcnt > 0) {
		if (sstepmode == STEP_PRINT){
			printf("%16t");
			printpc();
		}
		runpcs(rc?CONTIN:SINGLE, 1);
	}
	if (sstepmode == STEP_RETURN) {
		/*
		 *	Keep going until matching return
		 */

		int	ins = chkget(dot, ISP) & 0xff;

		if ((ins == I_REI) || ((ins == I_RET) && (--call_depth == 0)))
			printf("%d instructions executed\n", icount);
		else {
			if ((ins == I_CALLS) || (ins == I_CALLG) || (ins == I_RET)) {
				register int i;

				printf("[after %6d]     ", icount);
				for (i = call_depth; --i > 0;)
					printf("  ");
				printpc();
			}
			if ((ins == I_CALLS) || (ins == I_CALLG))
				call_depth++;

			loopcnt++;
			icount++;
			runpcs(SINGLE, 1);
		}
	}
	if (sstepmode == STEP_CALLT){
		/*
		 *	Keep going until CALL or RETURN
		 */

		int	ins = chkget(dot,ISP) & 0xff;

		if ((ins == I_CALLS) || (ins == I_CALLG) || (ins == I_RET) || (ins == I_REI))
			printf("%d instructions executed\n", icount);
		else {
			loopcnt++;
			icount++;
			runpcs(SINGLE, 1);
		}
	}
	sstepmode = STEP_NONE;	/* don't wait for CALL/RET */
	return(rc);
}

#define BPOUT 0
#define BPIN 1
INT bpstate = BPOUT;

execbkpt(bp,execsig)
bkpt_t	bp;
{
#ifdef	DEBUG
	printf("exbkpt: %d\n",bp->count);
#endif
	delbp();
	bp->flag=BKPTSET;
	execbkptf++;
#ifdef	DEBUG
	printf("reset(%d) from execbkpt()\n", SINGLE);
#endif	DEBUG
	reset(SINGLE);
#ifdef	lint
	if (execsig++) panic("");
#endif	lint
}



bkpt_t	scanbkpt(adr)
long adr;
{
	register bkpt_t	bp;
	for ( bp=bkpthead; bp; bp=bp->nxtbkpt ) {
		if ( bp->flag && bp->loc==adr ) {
			break;
		}
	}
	return(bp);
}

delbp()
{
	register long	a;
	register bkpt_t	bp;
	if ( bpstate!=BPOUT ) {
		for ( bp=bkpthead; bp; bp=bp->nxtbkpt ) {
			if ( bp->flag ) {
				a=bp->loc;
				put(a, ISP, (bp->ins&0xff)|(get(a, ISP)&~0xff));
			}
		}
		bpstate=BPOUT;
	}
}

setbp()
{
	register long		a;
	register bkpt_t	bp;

	if ( bpstate!=BPIN ) {
		for ( bp=bkpthead; bp; bp=bp->nxtbkpt ) {
			if ( bp->flag ) {
				a = bp->loc;
				bp->ins = get(a, ISP);
				put(a, ISP, BPT | (bp->ins)&~0xff);
				if ( errno ) {
					prints("cannot set breakpoint: ");
					psymoff(bp->loc,ISYM,"\n");
				}
			}
		}
		bpstate=BPIN;
	}
}

