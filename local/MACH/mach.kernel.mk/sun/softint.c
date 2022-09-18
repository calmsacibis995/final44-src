/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	softint.c,v $
 * Revision 2.2  89/07/11  13:55:22  jjc
 * 	Moved from sun3/softint.c to sun/softint.c, since it is used by both 
 * 	[89/07/06  12:39:33  jjc]
 * 
 *	the Sun 3 and 4.
 * 
 * Revision 2.4  89/03/09  21:38:12  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:47:20  gm0w
 * 	Added new copyright, fixed includes, and removed else leg
 * 	of CMU and MACH conditionals as part of kernel cleanup.
 * 	[89/02/10            jjc]
 * 
 * 29-Mar-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Change types.h to param.h so that the spl macro's are defined.
 *
 */

#ifndef	lint
static	char sccsid[] = "@(#)kern_softint.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */
#include <sys/param.h>

/*
 * Handle software interrupts through 'softcall' mechanism
 */

typedef int (*func_t)();

#define NSOFTCALLS	50

struct softcall {
	func_t	sc_func;		/* function to call */
	caddr_t	sc_arg;			/* arg to pass to func */
	struct softcall *sc_next;	/* next in list */
} softcalls[NSOFTCALLS];

struct softcall *softhead, *softtail, *softfree;

/*
 * Call function func with argument arg
 * at some later time at software interrupt priority
 */
softcall(func, arg)
	register func_t func;
	register caddr_t arg;
{
	register struct softcall *sc;
	static int first = 1;
	int s;

	s = spl6();
	if (first) {
		for (sc = softcalls; sc < &softcalls[NSOFTCALLS]; sc++) {
			sc->sc_next = softfree;
			softfree = sc;
		}
		first = 0;
	}
	/* coalesce identical softcalls */
	for (sc = softhead; sc != 0; sc = sc->sc_next)
		if (sc->sc_func == func && sc->sc_arg == arg)
			goto out;
	if ((sc = softfree) == 0)
		panic("too many softcalls");
	softfree = sc->sc_next;
	sc->sc_func = func;
	sc->sc_arg = arg;
	sc->sc_next = 0;
	if (softhead) {
		softtail->sc_next = sc;
		softtail = sc;
	} else {
		softhead = softtail = sc;
		siron();
	}
out:
	(void) splx(s);
}

/*
 * Called to process software interrupts
 * take one off queue, call it, repeat
 * Note queue may change during call
 */
softint()
{
	register func_t func;
	register caddr_t arg;
	register struct softcall *sc;
	int s;

	for (;;) {
		s = spl6();
		if (sc = softhead) {
			func = sc->sc_func;
			arg = sc->sc_arg;
			softhead = sc->sc_next;
			sc->sc_next = softfree;
			softfree = sc;
		}
		(void) splx(s);
		if (sc == 0)
			return;
		(*func)(arg);
	}
}
