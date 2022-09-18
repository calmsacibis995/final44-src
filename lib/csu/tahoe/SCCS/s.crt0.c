h56723
s 00002/00002/00100
d D 8.1 93/06/01 23:58:17 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00003/00088
d D 5.5 93/02/12 17:51:50 bostic 5 4
c add __progname global variable
e
s 00001/00007/00090
d D 5.4 92/07/16 23:38:15 mckusick 4 3
c update for new profiling method
e
s 00001/00001/00096
d D 5.3 91/05/22 11:21:46 mckusick 3 2
c delete support for prof style profiling
e
s 00001/00001/00096
d D 5.2 91/05/06 20:43:12 bostic 2 1
c new copyright; att/bsd/shared
e
s 00097/00000/00000
d D 5.1 91/05/03 12:23:27 donn 1 0
c date and time created 91/05/03 12:23:27 by donn
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 2
 * %sccs.include.proprietary.c%
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 *	C start up routine.
 *	Robert Henry, UCB, 20 Oct 81
 *
 *	We make the following (true) assumptions:
 *	1) When the kernel calls start, it does a jump to location 2,
 *	and thus avoids the register save mask.  We are NOT called
 *	with a calls!
 *	2) The only register variable that we can trust is sp,
 *	which points to the base of the kernel calling frame.
 */

I 5
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

E 5
char **environ = (char **)0;
I 5
static char empty[1];
char *__progname = empty;
E 5
static int fd;

extern	unsigned char	etext;
extern	unsigned char	eprol asm ("eprol");
extern			start() asm("start");

/*
 * Some kluges: store sp at entry in environ, and
 * install 16 bits of 0 at location 0 (a zero register save mask).
 * These two hacks remove limits on the use of local
 * and register variables in start().
 * The reason for using 'moval (sp),...' is that 'movl sp,...' generates
 * a privileged instruction trap (argh).
 * XXX 'addl3 $start,$2,r0; jmp (r0)' should be replaced with
 * XXX 'jbr start+2' when we convert over to gas.
 */
asm(".text; .word 0; moval (sp),_environ; addl3 $start,$2,r0; jmp (r0)");

start()
{
	struct kframe {
		int	kargc;
		char	*kargv[1];	/* size depends on kargc */
		char	kargstr[1];	/* size varies */
		char	kenvstr[1];	/* size varies */
	};
	register struct kframe *kfp;
	register char **targv;
	register char **argv;
	extern int errno;

	kfp = (struct kframe *) environ;
	for (argv = targv = &kfp->kargv[0]; *targv++; /* void */)
		/* void */ ;
	if (targv >= (char **)(*argv))
		--targv;
	environ = targv;
asm("eprol:");

#ifdef MCRT0
	monstartup(&eprol, &etext);
D 5
#endif MCRT0
E 5
I 5
#endif
E 5
	errno = 0;
I 5
	if (argv[0])
		if ((__progname = strrchr(argv[0], '/')) == NULL)
			__progname = argv[0];
		else
			++__progname;
E 5
	exit(main(kfp->kargc, argv, environ));
}

#ifdef MCRT0
/*ARGSUSED*/
exit(code)
	register int code;
{
D 3
	monitor(0);
E 3
I 3
	_mcleanup();
E 3
	_cleanup();
	_exit(code);
}
D 5
#endif MCRT0
E 5
I 5
#endif
E 5

#ifdef CRT0
/*
D 4
 * null mcount and moncontrol,
 * just in case some routine is compiled for profiling
E 4
I 4
 * null moncontrol, just in case some routine is compiled for profiling
E 4
 */
moncontrol(val)
	int val;
D 4
{

}

mcount()
E 4
{

}
D 5
#endif CRT0
E 5
I 5
#endif
E 5
E 1
