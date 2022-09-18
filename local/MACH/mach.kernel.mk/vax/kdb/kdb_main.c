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
 * Revision 2.5  89/02/25  20:22:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  88/08/10  10:26:44  rvb
 * 	Define label_t kdb_save for setjmp/longjmp.
 * 
 * 15-Apr-88  David Golub (dbg) at Carnegie-Mellon University
 *	MACH: take task and thread pointers as parameters, instead of
 *	proc pointer.  Some MACH tasks don't have corresponding
 *	processes.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	De-linted.
 *
 * 16-May-86  David Golub (dbg) at Carnegie-Mellon University
 *	Support for debugging other processes than the one interrupted.
 *
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	defined "<t"
 *
 */

/*
 * adb - main command loop and error/interrupt handling
 */

#include <vax/kdb/defs.h>
#include <sys/proc.h>

extern	label_t	kdb_save;
extern	int	kdb_setjmp_val;

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
long		maxfile;
string_t	errflg;
long		exitflg;

char		lastc;
INT		eof;

INT		lastcom;

long	maxoff = MAXOFF;
long	maxpos = MAXPOS;
long	dot;

kdb(type, trapsp, cur_thread)
int		type;
int		*trapsp;
thread_t	cur_thread;
{

	mkioptab();
	{
		extern long userpc;
		extern INT pid;

		userpc = dot = pcb.pcb_pc;
		if (cur_thread) {
			register task_t	cur_task;
			register int	proc_index;
			/*
			 *	Get the map for the current thread
			 */
			cur_task = cur_thread->task;
			curmap = cur_task->map;
			curpcb = cur_thread->pcb;
			proc_index = cur_task->proc_index;
			if (proc_index != 0) {
			    curpid = proc[proc_index].p_pid;
			}
			else {
			    curpid = 1;	/* fake it */
			}
		     /*	kdbgetprocess(curproc, &curmap, &curpcb); */
		     /*	curpid = curproc->p_pid; */
			var[varchk('m')] = (long) curmap;
		} else {
			/*
			 *	if there's no process...
			 */
			curmap = NULL;	/* take our chances */
			curpid = 1;	/* fake */
		}
		/*
		 *	But the pcb is the saved set of registers
		 */
		curpcb = &pcb;
		pid    = curpid;
		var[varchk('t')] = (int)trapsp;
	}
	wtflag = 1;
	kcore = 1;
	flushbuf();
#ifdef	DEBUG
	{
		extern long loopcnt;
		printf("loop=%d\n", loopcnt);
	}
#endif	DEBUG
	switch (setexit())
	{
	case SINGLE:
#ifdef	DEBUG
		printf("S ");
#endif	DEBUG
		pcb.pcb_psl |= PSL_T;
		/* fall through */
	case CONTIN:
#ifdef	DEBUG
		printf("CONT=>\n");
#endif	DEBUG
		return(1);
	case 0:
#ifdef	DEBUG
		printf("nextpcs(%d)\n", type);
#endif	DEBUG
		if ( nextpcs(type, 0) ) {
			printf("breakpoint%16t");
		} else {
			printf("stopped at%16t");
		}
		printpc();
	}
	if (executing)
		delbp();
	executing = 0;
	for (;;) {
extern int sstepmode;
		sstepmode = -1;
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
		lp=0;
		rdc();
		lp--;
		if (eof) {
			return(1);
		} else
			exitflg = 0;
		command(0, lastcom);
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
	iclose(0, 1);
	oclose();
	reset(1);
}

	/*
	 * KERNEL setexit/reset become setjmp/longjmp of
	 * the label below.
	 */
	label_t	kdb_save;
	int	kdb_setjmp_val;
