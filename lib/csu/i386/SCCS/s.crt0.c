h64479
s 00002/00002/00102
d D 8.1 93/06/01 23:56:38 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00005/00088
d D 5.9 93/02/12 17:51:35 bostic 10 9
c add __progname global variable
e
s 00002/00005/00091
d D 5.8 92/07/16 23:26:37 mckusick 9 8
c update for new structure
e
s 00002/00013/00094
d D 5.7 91/07/03 17:47:13 mckusick 8 7
c use atexit instead of defining exit
e
s 00001/00001/00106
d D 5.6 91/05/22 11:08:39 mckusick 7 6
c delete support for prof style profiling
e
s 00003/00003/00104
d D 5.5 91/05/06 20:41:06 bostic 6 5
c new copyright; att/bsd/shared
e
s 00013/00014/00094
d D 5.4 91/04/28 12:19:03 donn 5 3
c Cleanups; take advantage of gcc asm() features.
e
s 00006/00007/00101
d R 5.4 91/04/28 12:13:42 donn 4 3
c Cleanups; take advantage of gcc asm() features.
e
s 00003/00006/00105
d D 5.3 91/04/12 11:41:17 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00010/00108
d D 5.2 90/05/14 15:31:42 william 2 1
c Release 0.1 changes
e
s 00118/00000/00000
d D 5.1 90/04/23 18:06:22 william 1 0
c date and time created 90/04/23 18:06:22 by william
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 3
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * %sccs.include.redist.c%
E 3
I 3
D 6
 * %sccs.include.proprietary.c%
E 6
I 6
 * %sccs.include.redist.c%
E 6
E 3
 */

D 3
#ifndef lint
E 3
I 3
D 6
#if defined(LIBC_SCCS) && !defined(lint)
E 6
I 6
#ifndef lint
E 6
E 3
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif /* not lint */
E 3
I 3
D 6
#endif /* LIBC_SCCS and not lint */
E 6
I 6
#endif /* not lint */
E 6
E 3

D 2

E 2
/*
 *	C start up routine.
 *	Robert Henry, UCB, 20 Oct 81
 *
D 2
 *	We make the following (true) assumptions:
 *	1) The only register variable that we can trust is bp,
E 2
I 2
 *	We make the following (true) assumption:
 *	1) The only register variable that we can trust is ebp,
E 2
 *	which points to the base of the kernel calling frame.
D 2
 *	2) We can allocate as many register variables as we want,
 *	and don't have to save them for anybody.
E 2
 */

I 10
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

E 10
char **environ = (char **)0;
I 10
static char empty[1];
char *__progname = empty;
E 10
static int fd;

D 2
#ifdef notyet
E 2
D 5
asm("#define _start start");
asm("#define _eprol eprol");
asm("	.text");
D 2
asm("	.long 0"); /* first instruction should always be 0 (indir thru 0) */
asm("	.long 0"); /*this means all null pointers return value 0 regardless */
			/* of type */
#endif
E 2
I 2
asm("	.long 0xc000c000");
E 5
I 5
asm(".text");
asm(".long 0xc000c000");

E 5
E 2
extern	unsigned char	etext;
D 5
extern	unsigned char	eprol;
E 5
I 5
extern	unsigned char	eprol asm ("eprol");
extern			start() asm("start");

E 5
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
	register struct kframe *kfp;	/* r10 */
	register char **targv;
	register char **argv;
	extern int errno;
I 8
	extern void _mcleanup();
E 8

#ifdef lint
	kfp = 0;
	initcode = initcode = 0;
D 10
#else not lint
E 10
I 10
#else
E 10
D 5
	asm("	lea	4(%ebp),%ebx");	/* catch it quick */
E 5
I 5
	asm("lea 4(%ebp),%ebx");	/* catch it quick */
E 5
D 10
#endif not lint
E 10
I 10
#endif
E 10
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
D 10
#endif paranoid
E 10
I 10
#endif
E 10

#ifdef MCRT0
I 8
	atexit(_mcleanup);
E 8
	monstartup(&eprol, &etext);
D 10
#endif MCRT0
E 10
I 10
#endif
E 10
	errno = 0;
I 10
	if (argv[0])
		if ((__progname = strrchr(argv[0], '/')) == NULL)
			__progname = argv[0];
		else
			++__progname;
E 10
	exit(main(kfp->kargc, argv, environ));
}
D 5
asm("#undef _start");
asm("#undef _eprol");
E 5
D 8

#ifdef MCRT0
/*ARGSUSED*/
exit(code)
D 5
	register int code;	/* r11 */
E 5
I 5
	register int code;
E 5
{
D 7
	monitor(0);
E 7
I 7
	_mcleanup();
E 7
	_cleanup();
D 5
	asm("	pushl	8(bp)") ;
	asm("	movl $1,%eax");
	asm("	.byte 0x9a; .long 0; .word 0");
E 5
I 5
	asm("pushl 8(%ebp)") ;
	asm("movl $1,%eax");
	asm(".byte 0x9a; .long 0; .word 0");
E 5
}
#endif MCRT0
E 8

#ifdef CRT0
/*
D 9
 * null mcount and moncontrol,
 * just in case some routine is compiled for profiling
E 9
I 9
 * null moncontrol just in case some routine is compiled for profiling
E 9
 */
moncontrol(val)
	int val;
{

}
D 5
asm("	.globl	mcount");
asm("mcount:	ret");
E 5
I 5
D 9
asm(".globl mcount");
asm("mcount: ret");
E 5
#endif CRT0
E 9
I 9
D 10
#endif /* CRT0 */
E 10
I 10
#endif
E 10
E 9
E 1
