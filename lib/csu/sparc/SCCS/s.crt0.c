h12912
s 00002/00002/00091
d D 8.1 93/06/01 23:58:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00012/00003/00081
d D 5.2 93/02/12 17:51:43 bostic 2 1
c add __progname global variable
e
s 00084/00000/00000
d D 5.1 92/06/25 06:43:45 torek 1 0
c date and time created 92/06/25 06:43:45 by torek
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 *	C start up routine.
 */

I 2
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

E 2
char **environ = (char **)0;
I 2
static char empty[1];
char *__progname = empty;
E 2

extern unsigned char etext[];
extern volatile void start() asm("start0");
extern unsigned char eprol[] asm("eprol");
extern void _mcleanup(void);
D 2
volatile void exit(int);
E 2

volatile void
start(void)
{
	struct kframe {
		int	regarea[16];	/* space for %i and %o variables */
		int	kargc;		/* argument count */
		char	*kargv[1];	/* actual size depends on kargc */
	};
	register struct kframe *sp asm("%sp");
	register int argc;
	register char **argv, **envp;
	extern int errno;

asm(".globl start");
asm("start:");
	argc = sp->kargc;
	argv = &sp->kargv[0];
	environ = envp = &argv[argc + 1];
	sp = (struct kframe *)((int)sp - 16);
asm("eprol:");

#ifdef paranoid
	/*
	 * The standard I/O library assumes that file descriptors 0, 1, and 2
	 * are open. If one of these descriptors is closed prior to the start 
	 * of the process, I/O gets very confused. To avoid this problem, we
	 * insure that the first three file descriptors are open before calling
	 * main(). Normally this is undefined, as it adds two unnecessary
	 * system calls.
	 */
    {
	register int fd;
	do {
		fd = open("/dev/null", 2);
	} while (fd >= 0 && fd < 3);
	close(fd);
    }
#endif

#ifdef MCRT0
	monstartup(eprol, etext);
	atexit(_mcleanup);
	errno = 0;
#endif
I 2
	if (argv[0])
		if ((__progname = strrchr(argv[0], '/')) == NULL)
			__progname = argv[0];
		else
			++__progname;
E 2
	exit(main(argc, argv, envp));
D 2
	/* NOTREACHED */
E 2
}

#ifdef CRT0
/*
 * null mcount and moncontrol,
 * just in case some routine is compiled for profiling
 */
asm(".globl mcount");
asm(".globl _moncontrol");
asm("mcount: _moncontrol: retl; nop");
D 2
#endif CRT0
E 2
I 2
#endif
E 2
E 1
