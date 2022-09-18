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
 * Revision 1.4.1.4  90/05/14  13:18:44  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * Revision 1.4.1.3  90/01/08  13:27:12  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4.1.2  89/12/21  17:57:53  rvb
 * 	Revision 1.5  89/12/05  18:07:36  kupfer
 * 	Add debugging output for 'bad modifier'.
 * 
 * Revision 1.4.1.1  89/10/30  11:36:33  rvb
 * 	Revision 1.4  89/10/16  16:24:52  kupfer
 * 	Put back single-step fixes & minor cleanups (lost some formatting changes,
 * 	though).
 * 	 
 * 	Revision 1.3  89/09/21  12:03:52  lance
 * 	X108 checkin
 * 
 * Revision 1.4  89/03/09  20:01:48  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:35:02  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 *  3-Dec-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "single step until matching return" form of ":j".
 *
 *  3-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Continue kernel execution even if pid==0.
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

#include "defs.h"


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

int	runmode;

#include "pcs.h"

/* sub process control */

subpcs(modif)
{
	extern long	expv;
	register INT		check;
	INT		execsig;
	register bkpt_t	bkptr;
	string_t		comptr;
	char	c;
	int	i, shift, dr6, dr7;
	extern int *kdb_regs;
	extern int dotinc;

	execsig=0;
	loopcnt=cntval;

	switch (modif) {

		/* delete breakpoint */
	case 'd':
		if (adrflg) {
			extern int adrval;
			if (_dr0() == adrval)
				i = 0;
			else if (_dr1() == adrval)
				i = 1;
			else if (_dr2() == adrval)
				i = 2;
			else if (_dr3() == adrval)
				i = 3;
			else {
				printf("breakpoint not found\n");
				return;
			}
		} else if (expr(0))
			i = expv;
		else
			i = 0;
		if (i < 0 || i > 3)
			i = 0;
		dr7 = _dr7();
		dr7 &= ~(3 << (i + i));	/* disable debug register i */
		_wdr7(dr7);
		return;
	case 'D':
		if ( (bkptr=scanbkpt(dot)) ) {
			bkptr->flag=0;
			return;
		} else {
			error(NOBKPT);
		}

		/* set breakpoint */
	case 'b':
		if (expr(0))
			i = expv;
		else
			i = 0;
		if (i < 0 || i > 3)
			i = 0;
		dr7 = _dr7();
		dr7 |= 2 << (i + i);	/* enable debug register i */
		shift = (i << 2) + 16;
		dr7 &= ~(0xf << shift);	/* break on instr. exec. */
		_wdr7(dr7);

		switch (i) {		/* write addr into debug register */
		case 0:
			_wdr0(dot);
			break;
		case 1:
			_wdr1(dot);
			break;
		case 2:
			_wdr2(dot);
			break;
		case 3:
			_wdr3(dot);
			break;
		}
		return;
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
		runmode=SINGLE;
		sstepmode = STEP_NORM;
		break;

	case 'p':
	case 'P':
		runmode = SINGLE;
		sstepmode = STEP_PRINT;
		break;

	case 'j':
	case 'J':

		runmode = SINGLE;
		sstepmode = isupper(modif) ? STEP_RETURN : STEP_CALLT;
		call_depth = 1;
		icount = 0;
		break;

		/* continue with optional signal */
	case 'c':
	case 'C':
	case 0:
		runmode=CONTIN;
		sstepmode = STEP_NONE;
		break;

	case 'r':
	case 'R':
		dot = ((int *)kdb_regs[EBP])[1];
		goto bkpttmp;
	case 'S':
		dot += dotinc;
bkpttmp:
		if ( (bkptr=scanbkpt(dot)) ) {
			return;
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
		bkptr->initcnt = bkptr->count = 1;
		bkptr->flag = BKPTTMP;

		runmode=CONTIN;
		sstepmode = STEP_NONE;
		break;

	default:
		printf("don't understand modifier 0%o\n", modif);
		error(BADMOD);
	}
}
