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
 * $Log:	pcs.c,v $
 * Revision 2.4  89/03/09  22:17:51  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:23:20  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 *  3-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "single step until matching return" form of ":j".
 *
 *  3-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Continue kernel execution even if pid==0.
 *
 *  6-Jan-86  David Golub (dbg) at Carnegie-Mellon University
 *	new commands:
 *	:j single-steps until CALL[S,G] or RET encountered,
 *         printing PC at each stop
 *      :p like :s, but prints PC if count not done yet
 *
 */

/* static	char sccsid[] = "@(#)pcs.c	4.2 8/11/83"; */

/*
 *
 *	UNIX debugger
 *
 */

#include <vax/kdb/defs.h>


msg		NOBKPT;
msg		SZBKPT;
msg		EXBKPT;
msg		BADMOD;

/* breakpoints */
bkpt_t		bkpthead;

char		*lp;
char		lastc;

INT		signo;
long		dot;
INT		pid;
long		cntval;
long		loopcnt;

long		entrypt;
INT		adrflg;

#include <vax/kdb/pcs.h>

/* sub process control */

subpcs(modif)
{
	register INT		check;
	INT		execsig,runmode;
	register bkpt_t	bkptr;
	string_t		comptr;
	execsig=0;
	loopcnt=cntval;

	switch (modif) {

		/* delete breakpoint */
	case 'd':
	case 'D':
		if ( (bkptr=scanbkpt(dot)) ) {
			bkptr->flag=0;
			return;
		} else {
			error(NOBKPT);
		}

		/* set breakpoint */
	case 'b':
	case 'B':
		if ( (bkptr=scanbkpt(dot)) ) {
			bkptr->flag=0;
		}
		for ( bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt ) {
			if ( bkptr->flag == 0 ) {
				break;
			}
		}
		if ( bkptr==0 ) {
			if ( (bkptr=(bkpt_t)sbrk(sizeof *bkptr)) == (bkpt_t)-1 )
				{
					error(SZBKPT);
				} else {
					bkptr->nxtbkpt=bkpthead;
					bkpthead=bkptr;
				}
		}
		bkptr->loc = dot;
		bkptr->initcnt = bkptr->count = cntval;
		bkptr->flag = BKPTSET;
		check=MAXCOM-1;
		comptr=bkptr->comm;
		rdc();
		lp--;
		do {
			*comptr++ = readchar();
		}
		while( check-- && lastc!=EOR ) ;
		*comptr=0;
		lp--;
		if ( check ) {
			return;
		} else {
			error(EXBKPT);
		}


		/* single step */
	case 's':
	case 'S':
			runmode=SINGLE;
			execsig=getsig(signo);
			sstepmode = STEP_NORM;
		break;

	case 'p':
	case 'P':

		runmode = SINGLE;
		execsig = getsig(signo);
		sstepmode = STEP_PRINT;
		break;

	case 'j':
	case 'J':

		runmode = SINGLE;
		execsig = getsig(signo);
		sstepmode = isupper(modif) ? STEP_RETURN : STEP_CALLT;
		call_depth = 1;
		icount = 0;
		break;

		/* continue with optional signal */
	case 'c':
	case 'C':
	case 0:
		runmode=CONTIN;
		execsig=getsig(signo);
		sstepmode = STEP_NONE;
		break;

	default:
		error(BADMOD);
	}

	if ( loopcnt>0 ) {
		runpcs(runmode,0);
	}
#ifdef	lint
	runpcs(runmode, execsig);	/* reference execsig */
#endif	lint
}
