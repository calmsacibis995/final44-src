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
 * Revision 1.4.1.3  90/05/17  08:22:03  rvb
 * 	Don't print temp breakpoints.
 * 	[90/05/16            rvb]
 * 
 * Revision 1.4.1.2  90/05/14  13:18:57  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * Revision 1.4.1.1  90/01/08  13:27:02  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4  89/03/09  20:02:07  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:35:46  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
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

#undef	DEBUG

/*
 *
 *	UNIX debugger
 *
 */

#include "defs.h"

extern	map	txtmap;

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

print_salutation(type)
{
	register bkpt_t	bp;
	int dr6;
	extern int dotinc;
	extern int *kdb_regs;

	switch (type) {
	case T_SGLSTP:
		dr6 = _dr6();
		kdb_regs[EFL] |= EFL_RF;
		if (!(dr6 & DBG_BS)) {	
			int i;
			for (i = 0; i < 4; i++)
				if (dr6 & (1 << i)) {
					printf("Break(#%d, %X) [%s]: bp = %X, cr3 = %X\n", 
						i, kdb_regs, u.u_comm, kdb_regs[EBP], get_cr3());
					break;
				}
			if (i == 4) 
				printf("SGLSTP(?, %X) [%s]: bp = %X, cr3 = %X\n", 
					kdb_regs, u.u_comm, kdb_regs[EBP], get_cr3());
		}
		break;
	case T_BPTFLT:
		/* look for int 3 break point */
		kdb_regs[EIP]--;		/* so we can retry bpt'd instruction */
		if (bp=scanbkpt(kdb_regs[EIP])) {
			if (bp->flag & BKPTTMP) {
				bp->flag = 0;
				break;
			}
			printf("Break Point(%X) [%s]: bp = %X, cr3 = %X\n", 
				kdb_regs, u.u_comm, kdb_regs[EBP], get_cr3());
			bp->count=bp->initcnt;
		} else {
			printf("Stray Breakpoint Instruction(%X) [%s]: bp = %X, cr3 = %X\n", 
				kdb_regs, u.u_comm, kdb_regs[EBP], get_cr3());
			kdb_regs[EIP]++;		/* skip it */
		}
		break;
	case 0:
		printf("KBD(%X) [%s]: fp = %X, cr3 = %X\n", 
			kdb_regs, u.u_comm, &type-2, get_cr3());
		break;
	default:
	    {
	 	extern char *trap_type[];
		extern int TRAP_TYPES;
		extern char *kdberrflg;
		register int code = kdb_regs[EFL-2];

		printf("Kdb kernel trap [%s]: ", u.u_comm);
		if ((unsigned)type >= TRAP_TYPES)
			printf("type %d", type);
		else
			printf("%s", trap_type[type]);
		printf(" trap, code=%X\n", code);
	    }
	}
	dot = kdb_regs[EIP];
	dotinc = 0;
	psymoff(dot, ISYM, ":");
	printins(0, ISP, chkget(dot, ISP));
}

#define BPOUT 0
#define BPIN 1
INT bpstate = BPOUT;

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
				put(a, (bp->ins&0xff)|(get(a)&~0xff));
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
				bp->ins = get(a);
				put(a, BPT | (bp->ins)&~0xff);
				if ( errno ) {
					prints("cannot set breakpoint: ");
					psymoff(bp->loc,ISYM,"\n");
				}
			}
		}
		bpstate=BPIN;
	}
}
