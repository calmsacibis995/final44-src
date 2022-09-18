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
 * $Log:	print.c,v $
 * Revision 2.10  89/02/25  20:23:33  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.9  88/12/19  02:54:13  mwyoung
 * 	Fix include file references; remove lint.
 * 	[88/12/19            mwyoung]
 * 	
 * 	Put the 'm' print cases in the common file.
 * 	[88/12/06  01:03:03  mwyoung]
 * 	
 * 	Restore correct stack trace handling for the current thread.
 * 	[88/11/04            mwyoung]
 * 
 * Revision 2.8  88/10/26  05:35:49  mwyoung
 * 	Move 'k' to the machine-independent cases.
 * 	[88/10/26            mwyoung]
 * 
 * Revision 2.7  88/10/25  03:43:04  mwyoung
 * 	Move printing improvements to a machine-independent file.
 * 	[88/10/25            mwyoung]
 * 
 * Revision 2.6  88/10/18  03:39:57  mwyoung
 * 	Revision 2.4.2.3  88/08/24  00:06:07  mwyoung
 * 		Corrected include file references.
 * 		[88/08/22            mwyoung]
 * 	
 * 	Revision 2.4.2.2  88/08/23  23:40:07  mwyoung
 * 		Changed conditional on which command name printing is enabled.
 * 	
 * 	Revision 2.4.2.1  88/08/20  03:15:05  mwyoung
 * 	Separated out print_all_threads() into a routine that should
 * 	be machine-independent.
 * 	Added program name to the task information printed, as long
 * 	as we have it available.
 * 	[88/09/13  23:31:51  mwyoung]
 * 
 * Revision 2.5  88/08/10  10:27:43  rvb
 * Add 'f', 'F' - freeze and 't' 'T' - thaw
 * $L now gives stack trace of every thread.
 * 
 *  5-May-88  David Golub (dbg) at Carnegie-Mellon University
 *	Changed thread times printout to match new thread timer fields.
 *
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University.
 *	Delinted for kernel use.
 *
 *  8-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed $K to print specified thread's stack (<thread>$K).
 *
 *  5-Oct-87  David Golub (dbg) at Carnegie-Mellon University
 *	Changed thread state printout to accommodate new scheduling
 *	state machine.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 27-May-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	sigcode -> kdbsigcode.
 *
 * 15-May-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Have $z go to the mach_db debugger.
 *
 * 14-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Better support for MACH.
 *
 * 31-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Preliminary support for MACH in $l command.
 *
 *  7-Nov-86  David Golub (dbg) at Carnegie-Mellon University
 *	Made $l command print 'W' for swapped-out processes.
 *
 *  8-Jul-86  David Golub (dbg) at Carnegie-Mellon University
 *	Added $k (old format) and $K (new format) to trace only the
 *	kernel stack.
 *
 * 16-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Support for multiple-process debugging
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Flushed the stupid #
 *
 */

/* static	char sccsid[] = "@(#)print.c 4.7 8/14/83"; */

/*
 *
 *	UNIX debugger
 *
 */

#include <mach_db.h>
#include <cpus.h>
#include <vax/kdb/defs.h>
#include <kern/task.h>
#include <kern/thread.h>
#include <kern/kdb_print.h>
#include <sys/proc.h>

extern	label_t	kdb_save;
extern	int	kdb_setjmp_val;

msg		BADMOD;

map		txtmap;
map		datmap;

long		lastframe;
long		callpc;

INT		infile;
INT		outfile;
char		*lp;
long		maxoff;
long		maxpos;
INT		radix;

/* symbol management */
long		localval;

/* breakpoints */
bkpt_t		bkpthead;

REGLIST reglist [] = {
	"p1lr",	P1LR,	&pcb.pcb_p1lr,
	"p1br",	P1BR,	(int *)&pcb.pcb_p1br,
	"p0lr",	P0LR,	&pcb.pcb_p0lr,
	"p0br",	P0BR,	(int *)&pcb.pcb_p0br,
	"ksp",	KSP,	&pcb.pcb_ksp,
	"esp",	ESP,	&pcb.pcb_esp,
	"ssp",	SSP,	&pcb.pcb_ssp,
	"psl",	PSL,	&pcb.pcb_psl,
	"pc",	PC,	&pcb.pcb_pc,
	"usp",	USP,	&pcb.pcb_usp,
	"fp",	FP,	&pcb.pcb_fp,
	"ap",	AP,	&pcb.pcb_ap,
	"r11",	R11,	&pcb.pcb_r11,
	"r10",	R10,	&pcb.pcb_r10,
	"r9",	R9,	&pcb.pcb_r9,
	"r8",	R8,	&pcb.pcb_r8,
	"r7",	R7,	&pcb.pcb_r7,
	"r6",	R6,	&pcb.pcb_r6,
	"r5",	R5,	&pcb.pcb_r5,
	"r4",	R4,	&pcb.pcb_r4,
	"r3",	R3,	&pcb.pcb_r3,
	"r2",	R2,	&pcb.pcb_r2,
	"r1",	R1,	&pcb.pcb_r1,
	"r0",	R0,	&pcb.pcb_r0,
};

char		lastc;

INT		fcor;
string_t		errflg;
INT		signo;
INT		kdbsigcode;


long		dot;
long		var[];
string_t	symfil;
string_t	corfil;
INT		pid;
long		adrval;
INT		adrflg;
long		cntval;
INT		cntflg;

string_t	signals[] = {
	"",
	"hangup",
	"interrupt",
	"quit",
	"illegal instruction",
	"trace/BPT",
	"IOT",
	"EMT",
	"floating exception",
	"killed",
	"bus error",
	"memory fault",
	"bad system call",
	"broken pipe",
	"alarm call",
	"terminated",
	"signal 16",
	"stop (signal)",
	"stop (tty)",
	"continue (signal)",
	"child termination",
	"stop (tty input)",
	"stop (tty output)",
	"input available (signal)",
	"cpu timelimit",
	"file sizelimit",
	"signal 26",
	"signal 27",
	"signal 28",
	"signal 29",
	"signal 30",
	"signal 31",
};

/* general printing routines ($) */

printtrace(modif)
{
	INT		i;
	register bkpt_t	bkptr;
	string_t	comptr;
	register struct nlist *sp;

	if ( cntflg==0 ) {
		cntval = -1;
	}

	switch (modif) {

#if	MACH_DB
	case 'z':
		mdb_init();
		break;

#endif	MACH_DB
	case 'p':
		/*
		 *	pid$p	sets process to pid
		 *	$p	sets process to the one that invoked
		 *		kdb
		 */
		{
			struct proc 	*p;
			extern struct proc *	pfind();

			extern void	kdbgetprocess();

			if (adrflg) {
				p = pfind(dot);
			} else {
				p = pfind(curpid);	/* pid at entry */
			}
			if (p) {
				printf("proc entry at 0x%X\n", p);
				kdbgetprocess(p, &curmap, &curpcb);
				var[varchk('m')] = (long) curmap;
				pid = p->p_pid;
				if (pid == curpid) {
					/*
					 * pcb for entry process is saved
					 * register set
					 */
					curpcb = &pcb;
				}
			} else {
				printf("no such process");
			}
		}
		break;

	KDB_PRINT_CASES


	case 'd':
		if (adrflg) {
			if (adrval<2 || adrval>16) {
				printf("must have 2 <= radix <= 16");
				break;
			}
			printf("radix=%d base ten",radix=adrval);
		}
		break;


	case 'w':
	case 'W':
		maxpos=(adrflg?adrval:MAXPOS);
		break;

	case 's':
	case 'S':
		maxoff=(adrflg?adrval:MAXOFF);
		break;

	case 'v':
	case 'V':
		prints("variables\n");
		for ( i=0;i<=35;i++ ) {
			    if ( var[i] ) {
				printc((i<=9 ? '0' : 'a'-10) + i);
				printf(" = %X\n",var[i]);
			}
		}
		break;


	case 0:
	case '?':
		if ( pid ) {
			printf("pcs id = %d\n",pid);
		} else {
			prints("no process\n");
		}
		sigprint();
		flushbuf();

	case 'r':
	case 'R':
		printregs();
		return;

	case 'c':
	case 'C':
		oldtrace(modif) ;
		break;

	case 'n':
	case 'N':
		newtrace(modif) ;
		break;


		/*print externals*/
	case 'e':
	case 'E':
		for (sp = symtab; sp < esymtab; sp++) {
			if (sp->n_type==(N_DATA|N_EXT) ||
			    sp->n_type==(N_BSS|N_EXT))
				printf("%s:%12t%R\n",
				       sp->n_un.n_name,
				       get((long)sp->n_value,DSP));
		}
		break;

	case 'a':
	case 'A':
		error("No algol 68 on VAX");
		/*NOTREACHED*/

		/*print breakpoints*/
	case 'b':
	case 'B':
		printf("breakpoints\ncount%8tbkpt%24tcommand\n");
		for (bkptr=bkpthead; bkptr; bkptr=bkptr->nxtbkpt)
			if (bkptr->flag) {
				printf("%-8.8d",bkptr->count);
				psymoff(bkptr->loc,ISYM,"%24t");
				comptr=bkptr->comm;
				while ( *comptr ) {
					printc(*comptr++);
				}
			}
		break;

	default:
		error(BADMOD);
	}
}


printregs()
{
	register REGPTR	p;
	long		v;

	for ( p=reglist; p < &reglist[24]; p++ ) {
		v = kcore ? *(int *)((int)p->rkern - (int)&pcb + (int)curpcb)
			: *(long *)(((long)&u)+p->roffs);
		printf("%s%6t%R %16t", p->rname, v);
		valpr(v,(p->roffs==PC?ISYM:DSYM));
		printc(EOR);
	}
	printpc();
}

getreg(regnam)
{
	register REGPTR	p;
	register string_t	regptr;
	char	*olp;

	olp=lp;
	for ( p=reglist; p < &reglist[24]; p++ ) {
		regptr=p->rname;
		if ( (regnam == *regptr++) ) {
			while ( *regptr ) {
				if (readchar() != *regptr++) {
					--regptr;
					break;
				}
			}
			if ( *regptr ) {
				lp=olp;
			} else {
				int i = kcore ? (int)p->rkern - (int)&pcb + (int)curpcb
				    : p->roffs;
				return (i);
			}
		}
	}
	lp=olp;
	return(0);
}

printpc()
{
	psymoff(dot,ISYM,":%16t");
	printins(0,ISP,chkget(dot,ISP));
	printc(EOR);
}

char	*illinames[] = {
	"reserved addressing fault",
	"privileged instruction fault",
	"reserved operand fault"
};

char	*fpenames[] = {
	0,
	"integer overflow trap",
	"integer divide by zero trap",
	"floating overflow trap",
	"floating/decimal divide by zero trap",
	"floating underflow trap",
	"decimal overflow trap",
	"subscript out of range trap",
	"floating overflow fault",
	"floating divide by zero fault",
	"floating undeflow fault"
};

sigprint()
{
	if ( (signo>=0) && (signo<sizeof signals/sizeof signals[0]) ) {
		prints(signals[signo]);
	}
	switch (signo) {

	case SIGFPE:
		if ( (kdbsigcode > 0 &&
		    kdbsigcode < sizeof fpenames / sizeof fpenames[0]) ) {
			prints(" (");
			prints(fpenames[kdbsigcode]);
			prints(")");
		}
		break;

	case SIGILL:
		if ( (kdbsigcode >= 0 &&
		    kdbsigcode < sizeof illinames / sizeof illinames[0]) ) {
			prints(" (");
			prints(illinames[kdbsigcode]);
			prints(")");
		}
		break;
	}
}

print_stack_trace(thread)
	thread_t	thread;
{
	label_t		save_kdb_save;
	struct pcb	*savecurpcb = curpcb;
	int		saveadrflg = adrflg;

	save_kdb_save = kdb_save;

	if (thread != current_thread())
		curpcb = thread->pcb;

	printf("thread 0x%X,  pcb 0x%X, ", thread, curpcb);
	if (!setexit()) {
		printf("W_EVENT ");
		psymoff((long)thread->wait_event, ISYM, "");
		printc(EOR);
		adrflg = 0;
		oldtrace('k');
	} else {
		errflg = 0;
		printf(" FAILED\n");
	}
	adrflg = saveadrflg;

	curpcb = savecurpcb;
	kdb_save = save_kdb_save;
}
