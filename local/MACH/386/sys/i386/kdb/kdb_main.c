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
 * $Log:	kdb_main.c,v $
 * Revision 1.4.1.10  90/07/10  11:42:02  rvb
 * 	Suppose we don't have a mouse configured ...
 * 	[90/06/18            rvb]
 * 
 * Revision 1.4.1.9  90/05/17  08:21:56  rvb
 * 	Ignore esp case for pc != kernel, for now.  This avoids
 * 	dereferencing sp which was 0 once.
 * 
 * Revision 1.4.1.8  90/05/16  16:54:33  rvb
 * 	one seg.h to many.
 * 	[90/05/16            rvb]
 * 
 * Revision 1.4.1.7  90/05/16  16:42:39  rvb
 * 	Correct ESP value to skip "fluff".
 * 
 * 
 * Revision 1.4.1.6  90/05/14  13:18:26  rvb
 * 	Bring kdb up to Mach 2.5 production quality.
 * 	[90/05/10            rvb]
 * 
 * 	Add play back buf for kdb at end of phys memory.
 * 	[90/05/01            rvb]
 * 
 * 	Support for entering kdb from X;
 * 	[90/04/30            rvb]
 * 
 * Revision 1.4.1.5  90/03/07  13:26:49  rvb
 * 	Print who is entering kdb.
 * 	[90/03/06            rvb]
 * 
 * Revision 1.4.1.4  90/02/01  13:34:06  rvb
 * 	Make sure kdb() sets kdbactive for error recovery within kdb.
 * 	[90/02/01            rvb]
 * 
 * Revision 1.4.1.3  90/01/08  13:27:36  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4.1.2  89/10/30  12:25:47  rvb
 * 	Revision 1.2.1.1  89/10/16  16:24:48  kupfer
 * 	Put back single-step fixes & minor cleanups (lost some formatting changes,
 * 	though).
 * 
 * 	Revision 1.5  89/09/27  16:01:21  rvb
 * 	splall/backall -> sploff/splon
 * 
 * 	Revision 1.4  89/09/21  12:03:49  lance
 * 	X108 checkin
 * 
 * Revision 1.4  89/03/09  20:00:56  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:32:58  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 16-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Support for debugging other processes than the one interrupted.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	defined "<t"
 */

/*
 * adb - main command loop and error/interrupt handling
 */
#include <mouse.h>
#include "defs.h"
#include "pcs.h"
#include <mach/boolean.h>

#include <sys/proc.h>
#include <mach/i386/thread_status.h>

msg		NOEOR;

INT		mkfault;
INT		executing;
INT		infile;
char		*lp;
long		maxoff;
long		maxpos;
long		sigint;
long		sigqit;
INT		wtflag;
string_t		errflg;
long		exitflg;

char		lastc;
INT		eof;

INT		lastcom;
long	maxoff = MAXOFF;
long	maxpos = MAXPOS;

/* 
 * This flag is used to tell the trap handler that kdb is responsible 
 * for the single-step trap in system mode.
 */
boolean_t kdb_singlestep = FALSE;
int kdbtrapok = 0;
int kdbreturn = 1;
int kdbactive = 0;
int step_thru_bpt = 0;
int runmode;

long	dot;
int	jmpbuf[6];		/* should be label_t, later */
int	tregs[20];		/* reg holder if kdb called directly */
int	foreign_regs[20];	/* used by getprocess */
int	*active_regs;
int	*kdb_regs;		/* ptr to registers on stack */

extern int X_kdb_enter_len, X_kdb_exit_len;
extern int X_kdb_enter(),   X_kdb_exit();

X() {X_kdb_enter();}

kdb(type, trapsp)
{
extern int mouse_in_use;

	kdbactive++;
#if	NMOUSE > 0
	if (mouse_in_use && (X_kdb_enter_len || X_kdb_exit_len)) {
#include <i386at/kd.h>
		extern int mouse_in_use, kb_mode;
		static int old_mouse_in_use, old_kb_mode;

		old_mouse_in_use = mouse_in_use;
		old_kb_mode = kb_mode;

		mouse_in_use = 0;
		kb_mode = KB_ASCII;

		X_kdb_enter();
		kdb_main(type, trapsp);
		X_kdb_exit();

		mouse_in_use = old_mouse_in_use;
		kb_mode = old_kb_mode;
	} else
#endif	NMOUSE > 0
		kdb_main(type, trapsp);
	kdbactive--;
}

kdb_main(type, regs)
int		type;
int		*regs;
{
	int dr6;
	extern char peekc;
	extern int dotinc;
	int s;
	extern INT pid;
	struct proc *curproc;
	extern long 	loopcnt;

	s = sploff();		/* ?? rvb */
	/*
	 * Dismiss break point instruction execution via stepping
	 */
	if (step_thru_bpt) {
		step_thru_bpt = 0;
		regs[EFL] &= ~EFL_TF;
		goto bptexit;
	}
	/*
	 * Just keep doing what we're into
	 */
	if (--loopcnt > 0) {
		if (sstepmode == STEP_PRINT){
			printf("%2d:", loopcnt);
			kdb_regs = regs;	/* needed by printpc */
			printpc();
		}
		goto exit;
	}
	/*
	 * Hairy stepping mode
	 */
	if (type == T_SGLSTP && ((dr6 = _dr6()) & DBG_BS)) {
	    if (sstepmode == STEP_RETURN) {
		/*
		 *	Keep going until matching return
		 */
		int	ins1 = chkget(regs[EIP]);
		int	ins = ins1 & 0xff;

		if (ins == 0xff) {
			ins1 &= 0x3800;
			if (ins1 == 0x1000 || ins1 == 0x1800) {
				ins = I_CALL;
			}
		}

		if ((ins == I_REI) || ((ins == I_RET) && (--call_depth <= 0)))
			printf("%d instructions executed\n", icount);
		else {
			if ((ins == I_CALL) || (ins == I_RET)) {
				register int i;
			printf("[after %4d]  ", icount);
				for (i = call_depth; --i > 0;)
					printf("  ");
				kdb_regs = regs;     /* needed by printpc */
				printpc();
			}
			if (ins == I_CALL)
				call_depth++;

			loopcnt++;
			icount++;
			goto exit;
		}
	    }
	    if (sstepmode == STEP_CALLT){
		/*
		 *	Keep going until CALL or RETURN
		 */
		int	ins1 = chkget(regs[EIP]);
		int	ins = ins1 & 0xff;

		if (ins == 0xff) {
			ins1 &= 0x3800;
			if (ins1 == 0x1000 || ins1 == 0x1800) {
				ins = I_CALL;
			}
		}

		if ((ins == I_CALL) || (ins == I_RET) || (ins == I_REI))
			printf("%d instructions executed\n", icount);
		else {
			loopcnt++;
			icount++;
			goto exit;
		}
	    }
	}
	/*
	 *	Prologue for simple command execution
	 */
	if (!regs)
		regs = tregs;
	active_regs = regs;
	curproc = u.u_procp;
	kdbgetprocess(curproc);
	curpid = curproc->p_pid;
	pid    = curpid;

	var[varchk('m')] = (long) curmap;
	var[varchk('p')] = (long) curpcb;
	var[varchk('t')] = (int)regs;

	/*
	 *	Special cases for special commands like
	 *	:s and :b
	 */
	delbp();
	kdb_regs[EFL] &= ~EFL_TF;
	{
#ifdef	USER_BREAKS
		int *sp = (int *) kdb_regs[ESP];
		if ((sp[3]&0xffff) != KCSSEL)
			kdb_regs[ESP] += 7 * sizeof (int);
		else
#endif	USER_BREAKS
			kdb_regs[ESP] += 5 * sizeof (int);
	}
	sstepmode = -1;
	kdb_singlestep = FALSE;

	print_salutation(type);
	/*
	 * 	Command Loop
	 */
	kdbsetjmp(jmpbuf);
	executing = 0;
	eof=0;
	peekc = 0;
	for (;;) {
		flushbuf();
		if (errflg) {
			printf("%s\n", errflg);
			exitflg = (int)errflg;
			errflg = 0;
		}
		if (mkfault) {
			mkfault=0;
			printc('\n');
			prints(DBNAME);
		}
		lp=0; rdc(); lp--;
		if (eof) {
			goto bptexit;
		} else
			exitflg = 0;
		runmode = -1;
		command(0, lastcom);
		switch (runmode) {
		case SINGLE:		/* continue for single step */
single:
			kdb_regs[EFL] |= EFL_TF;
			kdb_singlestep = TRUE;
exit:
			splon(s);
			_wdr6(0);
			return;
		case CONTIN:		/* continue for break point */
		    {
			register bkpt_t	bp;

			if (bp = scanbkpt(kdb_regs[EIP])) {
				step_thru_bpt=1;
				goto single;
			}
bptexit:
			pb(-1);		/* reset playback buffer */
			setbp();
			splon(s);
			_wdr6(0);
			return;
		     }
		}
		if (lp && lastc!='\n')
			error(NOEOR);
	}
}

long
round(a,b)
register long a, b;
{
	register long w;
	w = (a/b)*b;
	if ( a!=w ) {
		w += b;
	}
	return(w);
}

/*
 * If there has been an error or a fault, take the error.
 */
chkerr()
{
	if (errflg || mkfault)
		error(errflg);
}

/*
 * An error occurred; save the message for later printing,
 * close open files, and reset to main command loop.
 */
error(n)
char *n;
{
	errflg = n;
	kdblongjmp(jmpbuf, 1);
}


/*
 *	Return the map and pcb for a process.
 */
kdbgetprocess(p)
	struct proc	*p;
{
	/*
	 *	special case for current process
	 */
	if (!p || p == u.u_procp) {
		curmap = current_task()->map;
		curpcb = current_thread()->pcb;
		kdb_regs = active_regs;
	} else {
		if (p->task)
			curmap = p->task->map;
		else
			panic("kdbgetprocess: no task");
		if (p->thread) {
			extern int foreign_regs[];

			regs2cntxt(kdb_regs, curpcb);
			curpcb = p->thread->pcb;
			kdb_regs = foreign_regs;
/*			cntxt2regs(p->thread->pcb, kdb_regs);*/
		} else
			panic("kdbgetprocess: no pcb");
	}
}

#if	0
		/*
		 * These two routines save/restore the entire pcb.  But
		 * save context does not save all this
		 */
regs2pcb(regs, pcb)
struct i386_saved_state *regs;
struct pcb curpcb;
{
	pcb->pcb_tss.t_cr3	= get_cr3();
	pcb->pcb_tss.t_eip	= regs->eip;
	pcb->pcb_tss.t_eflags	= regs->efl;
	pcb->pcb_tss.t_eax	= regs->eax;
	pcb->pcb_tss.t_ecx	= regs->ecx;
	pcb->pcb_tss.t_edx	= regs->edx;
	pcb->pcb_tss.t_ebx	= regs->ebx;
#if	0
	if (regs->cs & 0x3) {
		/*
		 * user mode - saved esp and ss valid
		 */
		pcb->pcb_tss.t_esp	= regs->uesp;		/* user stack pointer */
		pcb->pcb_tss.t_ss	= regs->ss & 0xffff;	/* user stack segment */
	} else {
		/*
		 * Kernel mode - esp and ss not saved
		 */
		pcb->pcb_tss.t_esp	= (int)&regs->uesp;	/* kernel stack pointer */
		pcb->pcb_tss.t_ss	= KDSSEL;
	}
#endif	0
	pcb->pcb_tss.t_ebp	= regs->ebp;
	pcb->pcb_tss.t_esi	= regs->esi;
	pcb->pcb_tss.t_edi	= regs->edi;
	pcb->pcb_tss.t_es	= regs->es & 0xffff;
	pcb->pcb_tss.t_cs	= regs->cs & 0xffff;
	pcb->pcb_tss.t_ds	= regs->ds & 0xffff;
	pcb->pcb_tss.t_fs	= regs->fs & 0xffff;
	pcb->pcb_tss.t_gs	= regs->gs & 0xffff;
	pcb->pcb_tss.t_ldt	= get_ldt();
}

pcb2regs(pcb, regs)
struct i386_saved_state *regs;
struct pcb curpcb;
{
	regs->eip	= pcb->pcb_tss.t_eip;
	regs->efl	= pcb->pcb_tss.t_eflags;
	regs->eax	= pcb->pcb_tss.t_eax;
	regs->ecx	= pcb->pcb_tss.t_ecx;
	regs->edx	= pcb->pcb_tss.t_edx;
	regs->ebx	= pcb->pcb_tss.t_ebx;

	regs->esp	= pcb->pcb_tss.t_esp;		/* kernel stack pointer ??? */
	regs->ss	= pcb->pcb_tss.t_ss & 0xffff;

	regs->ebp	= pcb->pcb_tss.t_ebp;
	regs->esi	= pcb->pcb_tss.t_esi;
	regs->edi	= pcb->pcb_tss.t_edi;
	regs->es	= pcb->pcb_tss.t_es & 0xffff;
	regs->cs	= pcb->pcb_tss.t_cs & 0xffff;
	regs->ds	= pcb->pcb_tss.t_ds & 0xffff;
	regs->fs	= pcb->pcb_tss.t_fs & 0xffff;
	regs->gs	= pcb->pcb_tss.t_gs & 0xffff;
}
#endif	0

#define	O_EDI	0
#define	O_ESI	1
#define	O_EBX	2
#define	O_EBP	3
#define	O_ESP	4
#define O_EIP	5
#define	O_IPL	6

cntxt2regs(pcb, regs)
struct i386_saved_state *regs;
struct pcb *pcb;
{
	int temp	= chkget(&pcb->pcb_context[O_EIP]);	/* is it in memory */

	regs->eip	= pcb->pcb_context[O_EIP];
	regs->ebx	= pcb->pcb_context[O_EBX];
	regs->esp	= pcb->pcb_context[O_ESP];		/* kernel stack pointer ??? */
	regs->ebp	= pcb->pcb_context[O_EBP];
	regs->esi	= pcb->pcb_context[O_ESI];
	regs->edi	= pcb->pcb_context[O_EDI];
}

regs2cntxt(regs, pcb)
struct i386_saved_state *regs;
struct pcb *pcb;
{
	pcb->pcb_context[O_EIP] = regs->eip;
	pcb->pcb_context[O_EBX] = regs->ebx;
/*	pcb->pcb_context[O_ESP] = regs->esp; */
	pcb->pcb_context[O_EBP] = regs->ebp;
	pcb->pcb_context[O_ESI] = regs->esi;
	pcb->pcb_context[O_EDI] = regs->edi;
}
