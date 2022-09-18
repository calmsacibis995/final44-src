/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef lint
static char sccsid[] = "@(#)crt0.c	5.1 (Berkeley) 5/30/85";
#endif not lint

/*
 *      C start up routine.
 *      Robert Henry, UCB, 20 Oct 81
 *      J.Christensen IBM, 10 Jan 84 adapted to Workstation Unix
 *
 *	We make the following (true) assumptions:
 *	1) when the kernel calls start, it does a jump to location 2,
 *	and thus avoids the register save mask.  We are NOT called
 *	with a calls!  see sys1.c:setregs().
 *	2) The only register variable that we can trust is sp,
 *	which points to the base of the kernel calling frame.
 *	Do NOT believe the documentation in exec(2) regarding the
 *	values of fp and ap.
 *	3) We can allocate as many register variables as we want,
 *	and don't have to save them for anybody.
 *	4) Because of the ways that asm's work, we can't have
 *	any automatic variables allocated on the stack, because
 *	we must catch the value of sp before any automatics are
 *	allocated.
 */

/*
 * HISTORY:
 * $Log:	crt0.c,v $
 * Revision 2.2  93/01/24  14:15:57  danner
 * 	Renamed from crt0.cc to crt0.c as we do not need a special rule
 * 	since we are now using gcc 2.3.2. Also dumped romp code.
 * 	Added some extra asm magic to get function names correct
 * 	[93/01/16            mrt]
 * 
 * Revision 2.5  91/07/31  18:31:48  dbg
 * 	Fixes for ANSI C and GCC inline assembler.
 * 	[91/07/30  17:31:03  dbg]
 * 
 * Revision 2.4  90/11/05  14:36:24  rpd
 * 	Removed the definition of exit.
 * 	[90/10/30            rpd]
 * 
 * Revision 2.3  90/06/02  15:13:26  rpd
 * 	Converted to new IPC.
 * 	[90/03/26  23:29:13  rpd]
 * 
 * Revision 2.2  90/01/19  14:36:41  rwd
 * 	cthread_init_routine returns new stack to run on.
 * 	[89/12/13            rwd]
 * 
 * 	Changed '_exit' to 'task_terminate(task_self())' for stand-alone
 * 	MACH use.
 * 	[88/08/31            dbg]
 * 
 * 	Added call to _cthread_init_routine if loaded with cthreads
 * 	library.  Also, use _cthread_exit_routine if present.
 * 	[87/07/09            mbj]
 * 
 */

char **environ = (char **)0;

extern	unsigned char	eprol __asm__ ("eprol");
int	errno;
extern	unsigned char	etext;
extern	exit();

int	(*mach_init_routine)();
int	(*_cthread_init_routine)();
int	(*_cthread_exit_routine)();

struct kframe {
	int	kargc;
	char	*kargv[1];	/* size depends on kargc */
	char	kargstr[1];	/* size varies */
	char	kenvstr[1];	/* size varies */
};

extern start () __asm__ ("start");

start ()
{
	/*
	 *	ALL REGISTER VARIABLES!!!
	 */
	register int r11;	/* for init - not used otherwise - WEW */
	register struct kframe *kfp;	/* r10 */
	register char **targv;
	register char **argv;

#ifdef lint
	kfp = 0;
	initcode = initcode = 0;
#endif	lint

#ifndef	lint
#ifdef	__GNUC__
	__asm__("movl sp,%0" : "=g" (kfp));
#else
	asm("	movl	sp,r10");	/* catch it quick */
#endif
#endif	lint

	for (argv = targv = &kfp->kargv[0]; *targv++; /* void */)
		/* void */ ;
	if (targv >= (char **)(*argv))
		--targv;
	environ = targv;

	if (mach_init_routine)
		(void) mach_init_routine();

__asm__("eprol:");
 
#ifdef MCRT0
	monstartup(&eprol, &etext);
#endif MCRT0
	if (_cthread_init_routine) {
	    register int new_sp;
	    
	    new_sp = (*_cthread_init_routine)();
	    if (new_sp) {
#ifdef	__GNUC__
		asm("movl %0,sp" : : "g" (new_sp));
#else
		asm("movl	r0,sp");
#endif
	    }
	}
	(* (_cthread_exit_routine ? _cthread_exit_routine : exit))
		(main( kfp->kargc, argv, targv ));
}
asm("#undef _start");
asm("#undef _eprol");


#ifdef MCRT0
/*ARGSUSED*/
exit(code)
	register int code;	/* r11 */
{
	monitor(0);
	_cleanup();
	_exit(code);
}
#endif MCRT0

#ifdef CRT0
/*
 * null mcount and moncontrol,
 * just in case some routine is compiled for profiling
 */
moncontrol(val)
	int val;
{
}
asm("	.globl	mcount");
asm("mcount:	rsb");
#endif CRT0
