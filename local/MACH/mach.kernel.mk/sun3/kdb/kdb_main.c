/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	kdb_main.c,v $
 * Revision 2.4  89/03/09  21:34:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:40:55  gm0w
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
 *
 *  5-Sep-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Converted into kernel debugger, "kdb".
 *
 */
#ifndef	lint
static	char sccsid[] = "@(#)main.c 1.1 86/02/03 SMI";
#endif
/*
 * adb - main command loop and error/interrupt handling
 */

#include <sun3/kdb/adb.h>
#include <sun3/kdb/fpascii.h>
#include <sys/proc.h>
int	exitflg;
int	debugging = 0;

int	eof;

kdb(type, trapsp, curproc)
	int		type;
	int		*trapsp;
	struct proc	*curproc;
{

#ifdef	vax
	mkioptab();
#else
	mc68881 = MC68881Present() ;	/* 68881 present? */
#endif
	{
	    extern addr_t userpc;
	    extern int pid;

	    userpc = dot = pcb.pcb_regs.r_pc;
	    if (curproc) {
		
		/*
	     	 *	Get the map for the current process
		 */
		kdbgetprocess(curproc, &curmap, &curpcb);
		curpid = curproc->p_pid;
		var[varchk('m')] = (int)curmap;
	    }
	    else {
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
	maxoff = 0x100000;
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
		pcb.pcb_regs.r_sr |= PSL_T;
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
		if (nextpcs(type, 0))
		    printf("breakpoint%16t");
		else
		    printf("stopped at%16t");
		printpc();
	}
	if (executing)
		delbp();
	executing = 0;
	for (;;) {
		flushbuf();
		if (errflg) {
			printf("%s\n", errflg);
			exitflg = 1;
			errflg = 0;
		}
		if (interrupted) {
			interrupted = 0;
			prints("\nDBNAME\n");
		}
		lp = 0; (void) rdc(); lp--;
		if (eof) {
			return(1);
		} else
			exitflg = 0;
		(void) command((char *)0, lastcom);
		if (lp && lastc!='\n')
			error("newline expected");
	}
}


round(a, b)
	int a, b;
{
	register int w;

	w = (a / b) * b;
	if (a != w)
		w += b;
	return (w);
}

chkerr()
{

	if (errflg || interrupted)
		error(errflg);
}

error(n)
	char *n;
{

	errflg = n;
	reset(1);
}


shell()
{
}
