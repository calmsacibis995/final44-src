h35000
s 00002/00002/00112
d D 8.1 93/06/01 23:56:20 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00005/00098
d D 5.8 93/02/12 17:51:26 bostic 8 7
c add __progname global variable
e
s 00002/00005/00101
d D 5.7 92/07/10 17:34:12 mckusick 7 6
c update for new profiling style
e
s 00002/00014/00104
d D 5.6 91/07/03 17:43:47 mckusick 6 5
c use atexit instead of defining exit
e
s 00001/00001/00117
d D 5.5 91/05/21 18:43:50 mckusick 5 4
c delete support for prof style profiling
e
s 00001/00001/00117
d D 5.4 91/05/06 20:39:43 bostic 4 3
c new copyright; att/bsd/shared
e
s 00014/00030/00104
d D 5.3 91/04/28 15:01:54 donn 3 2
c Clean-up for GCC.
e
s 00007/00006/00127
d D 5.2 91/04/12 11:40:07 bostic 2 1
c new copyright; att/bsd/shared
e
s 00133/00000/00000
d D 5.1 90/06/25 23:09:54 bostic 1 0
c date and time created 90/06/25 23:09:54 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1990 The Regents of the University of California.
E 3
I 3
D 9
 * Copyright (c) 1991 The Regents of the University of California.
E 3
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
D 4
 * %sccs.include.proprietary.c%
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */

D 3
#if defined(LIBC_SCCS) && !defined(lint)
E 3
I 3
#ifndef lint
E 3
D 2
static char sccsid[] = "@(#)crt0.c	5.3 (Berkeley) 3/9/86";
#endif LIBC_SCCS and not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif /* LIBC_SCCS and not lint */
E 3
I 3
#endif /* not lint */
E 3
E 2

/*
 *	C start up routine.
 *	Robert Henry, UCB, 20 Oct 81
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

I 8
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

E 8
char **environ = (char **)0;
I 8
static char empty[1];
char *__progname = empty;
E 8
static int fd;

D 3
asm("#define _start start");
asm("#define _eprol eprol");
E 3
I 3
extern	unsigned char	etext;
extern	unsigned char	eprol asm ("eprol");
extern			start() asm("start");
E 3

D 3
#ifdef hp300
asm("#define link .long 0; linkw");	/* Yuk!! */
#endif
E 3
I 3
asm(".text; orb #0,d0");	/* 32 bits of zero at location 0 */
E 3

D 3
extern	unsigned char	etext;
extern	unsigned char	eprol;
E 3
start()
{
	struct kframe {
		int	kargc;
		char	*kargv[1];	/* size depends on kargc */
		char	kargstr[1];	/* size varies */
		char	kenvstr[1];	/* size varies */
	};
	/*
	 *	ALL REGISTER VARIABLES!!!
	 */
D 3
	register int d7;		/* needed for init (this will be
					   a problem with GCC) */
	register struct kframe *kfp;	/* PCC a5 */
E 3
I 3
	register struct kframe *kfp;	/* r10 */
E 3
	register char **targv;
	register char **argv;
	extern int errno;
I 6
	extern void _mcleanup();
E 6

#ifdef lint
	kfp = 0;
	initcode = initcode = 0;
D 8
#else not lint
E 8
I 8
#else
E 8
D 3
#ifdef __GNUC__
E 3
	asm("lea a6@(4),%0" : "=r" (kfp));	/* catch it quick */
D 3
#else
	asm("	lea	a6@(4),a5");	/* catch it quick */
#endif
E 3
D 8
#endif not lint
E 8
I 8
#endif
E 8
	for (argv = targv = &kfp->kargv[0]; *targv++; /* void */)
		/* void */ ;
	if (targv >= (char **)(*argv))
		--targv;
	environ = targv;
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
	do	{
		fd = open("/dev/null", 2);
	} while (fd >= 0 && fd < 3);
	close(fd);
D 8
#endif paranoid
E 8
I 8
#endif
E 8

#ifdef MCRT0
I 6
	atexit(_mcleanup);
E 6
	monstartup(&eprol, &etext);
D 8
#endif MCRT0
E 8
I 8
#endif
E 8
	errno = 0;
I 8
	if (argv[0])
		if ((__progname = strrchr(argv[0], '/')) == NULL)
			__progname = argv[0];
		else
			++__progname;
E 8
	exit(main(kfp->kargc, argv, environ));
}
D 3
asm("#undef link");
asm("#undef _start");
asm("#undef _eprol");
E 3
D 6

#ifdef MCRT0
/*ARGSUSED*/
exit(code)
D 3
	register int code;	/* PCC d7 */
E 3
I 3
	register int code;
E 3
{
D 5
	monitor(0);
E 5
I 5
	_mcleanup();
E 5
	_cleanup();
D 3
#ifdef __GNUC__
E 3
	asm("movl %1,sp@-" : "=m" (*(char *)0) : "r" (code));
D 3
#else
	asm("	movl d7,sp@-");
#endif
	asm("	subql #4,sp");
	asm("	movl #1,d0");
	asm("	trap #0");
E 3
I 3
	asm("subql #4,sp");
	asm("movl #1,d0");
	asm("trap #0");
E 3
}
#endif MCRT0
E 6

#ifdef CRT0
/*
D 7
 * null mcount and moncontrol,
 * just in case some routine is compiled for profiling
E 7
I 7
 * null moncontrol, just in case some routine is compiled for profiling
E 7
 */
moncontrol(val)
	int val;
{

}
D 3
asm("	.globl	mcount");
asm("mcount:	rts");
E 3
I 3
D 7
asm(".globl mcount");
asm("mcount: rts");
E 3
#endif CRT0
E 7
I 7
D 8
#endif /* CRT0 */
E 8
I 8
#endif
E 8
E 7
E 1
