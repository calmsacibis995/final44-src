h25677
s 00002/00002/00109
d D 8.1 93/06/01 23:58:56 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00005/00095
d D 5.12 93/02/12 17:51:54 bostic 21 20
c add __progname global variable
e
s 00001/00004/00099
d D 5.11 92/07/16 23:45:15 mckusick 20 19
c new profiling methods
e
s 00002/00011/00101
d D 5.10 91/07/03 17:46:03 mckusick 19 18
c use atexit instead of defining exit
e
s 00001/00001/00111
d D 5.9 91/05/27 14:57:38 mckusick 18 17
c delete support for prof style profiling
e
s 00003/00003/00109
d D 5.8 91/05/06 20:44:52 bostic 17 16
c new copyright; att/bsd/shared
e
s 00000/00006/00112
d D 5.7 91/05/03 10:18:55 donn 16 15
c Adjust the comment header.
e
s 00016/00014/00102
d D 5.6 91/05/03 00:31:59 donn 15 14
c Convert for gcc.  (1) Take advantage of GCC symbol renaming features.
c (2) Add a hack to permit local and register variables in start(), so that we
c don't depend on miracles from the compiler.
e
s 00006/00005/00110
d D 5.5 91/04/12 11:53:25 bostic 14 13
c new copyright; att/bsd/shared
e
s 00001/00002/00114
d D 5.4 88/01/18 11:25:22 mckusick 13 12
c use _exit instead of asm's (4.3BSD/lib/16)
e
s 00002/00002/00114
d D 5.3 86/03/09 21:08:06 donn 12 9
c added LIBC_SCCS condition for sccs ids
e
s 00003/00003/00113
d R 5.3 86/03/09 21:01:44 donn 11 9
c added LIBC_SCCS condition for sccs ids
e
s 00001/00000/00116
d R 5.3 86/02/04 17:57:27 karels 10 9
c add call to _stdio_init
e
s 00019/00000/00097
d D 5.2 85/10/21 19:34:19 mckusick 9 8
c add paranoid check for missing file descriptors 0, 1, and 2
e
s 00009/00001/00088
d D 5.1 85/05/30 14:54:35 dist 8 7
c Add copyright
e
s 00007/00001/00082
d D 4.6 83/03/30 17:21:44 peter 7 6
c add null moncontrol() if not compiled for profiling
e
s 00025/00001/00058
d D 4.5 82/12/04 16:16:06 mckusick 6 5
c break out "monitor" into separate file for jkf
e
s 00003/00002/00056
d D 4.4 82/05/19 10:06:18 rrh 5 4
c old versions; put these to bed
e
s 00001/00000/00057
d D 4.3 82/01/13 14:39:07 mckusic 4 3
c make mcount a global
e
s 00002/00007/00055
d D 4.2 82/01/05 15:18:17 mckusic 3 2
c change _start to start
e
s 00000/00000/00062
d D 4.1 81/11/29 23:32:33 mckusic 2 1
c renumber to version 4
e
s 00062/00000/00000
d D 1.1 81/11/29 16:43:24 mckusick 1 0
c date and time created 81/11/29 16:43:24 by mckusick
e
u
U
t
T
I 1
D 8
static	char *sccsid = "%W% (Berkeley) %G%";
E 8
I 8
D 14
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 22
 * Copyright (c) 1982 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1982, 1993
 *	The Regents of the University of California.  All rights reserved.
E 22
 *
D 17
 * %sccs.include.proprietary.c%
E 17
I 17
 * %sccs.include.redist.c%
E 17
E 14
 */

D 12
#ifndef lint
E 12
I 12
D 17
#if defined(LIBC_SCCS) && !defined(lint)
E 17
I 17
#ifndef lint
E 17
E 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 12
#endif not lint
E 12
I 12
D 14
#endif LIBC_SCCS and not lint
E 14
I 14
D 17
#endif /* LIBC_SCCS and not lint */
E 17
I 17
#endif /* not lint */
E 17
E 14
E 12
E 8

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
D 16
 *	3) We can allocate as many register variables as we want,
 *	and don't have to save them for anybody.
 *	4) Because of the ways that asm's work, we can't have
 *	any automatic variables allocated on the stack, because
 *	we must catch the value of sp before any automatics are
 *	allocated.
E 16
 */

I 21
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

E 21
D 6
char **environ;
E 6
I 6
char **environ = (char **)0;
I 21
static char empty[1];
char *__progname = empty;
E 21
I 9
static int fd;
E 9
E 6

I 3
D 15
asm("#define _start start");
I 6
asm("#define _eprol eprol");
E 15
extern	unsigned char	etext;
D 15
extern	unsigned char	eprol;
E 15
I 15
extern	unsigned char	eprol asm ("eprol");
extern			start() asm("start");

/*
 * Two kluges: store sp at entry in environ, and
 * install 16 bits of 0 at location 0 (a zero register save mask).
 * These two hacks remove limits on the use of local
 * and register variables in start().
 */
asm(".text; .word 0; movl sp,_environ; jbr start+2");

E 15
E 6
E 3
start()
{
	struct kframe {
		int	kargc;
		char	*kargv[1];	/* size depends on kargc */
		char	kargstr[1];	/* size varies */
		char	kenvstr[1];	/* size varies */
	};
D 15
	/*
	 *	ALL REGISTER VARIABLES!!!
	 */
D 5
	register struct kframe *kfp;	/* r11 */
E 5
I 5
	register int r11;		/* needed for init */
	register struct kframe *kfp;	/* r10 */
E 15
I 15
	register struct kframe *kfp;
E 15
E 5
	register char **targv;
	register char **argv;
I 9
	extern int errno;
I 19
	extern void _mcleanup();
E 19
E 9

#ifdef lint
	kfp = 0;
I 6
	initcode = initcode = 0;
E 6
D 21
#else not lint
E 21
I 21
#else
E 21
D 5
	asm("	movl	sp,r11");	/* catch it quick */
E 5
I 5
D 15
	asm("	movl	sp,r10");	/* catch it quick */
E 15
I 15
	kfp = (struct kframe *) environ;
E 15
E 5
D 21
#endif not lint
E 21
I 21
#endif
E 21
	for (argv = targv = &kfp->kargv[0]; *targv++; /* void */)
		/* void */ ;
	if (targv >= (char **)(*argv))
		--targv;
	environ = targv;
I 6
asm("eprol:");
I 9

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
D 21
#endif paranoid
E 21
I 21
#endif
E 21

E 9
#ifdef MCRT0
I 19
	atexit(_mcleanup);
E 19
	monstartup(&eprol, &etext);
D 21
#endif MCRT0
E 21
I 21
#endif
E 21
I 9
	errno = 0;
I 21
	if (argv[0])
		if ((__progname = strrchr(argv[0], '/')) == NULL)
			__progname = argv[0];
		else
			++__progname;
E 21
E 9
E 6
	exit(main(kfp->kargc, argv, environ));
}
I 6
D 15
asm("#undef _start");
asm("#undef _eprol");
E 15
E 6
D 19

I 6
#ifdef MCRT0
/*ARGSUSED*/
exit(code)
D 15
	register int code;	/* r11 */
E 15
I 15
	register int code;
E 15
{
D 18
	monitor(0);
E 18
I 18
	_mcleanup();
E 18
	_cleanup();
D 13
	asm("	movl r11,r0");
	asm("	chmk $1");
E 13
I 13
	_exit(code);
E 13
}
#endif MCRT0
E 19

#ifdef CRT0
E 6
/*
D 7
 * null mcount, just in case some routine is compiled for profiling
E 7
I 7
D 20
 * null mcount and moncontrol,
 * just in case some routine is compiled for profiling
E 20
I 20
 * null moncontrol, just in case some routine is compiled for profiling
E 20
E 7
 */
I 7
moncontrol(val)
	int val;
{

}
E 7
I 4
D 15
asm("	.globl	mcount");
E 4
D 3
asm("#define _mcount mcount");
mcount()
{
	asm("	forgot to run ex script on gcrt0.s" );
	asm( "	rsb" );
	asm( "#undef _mcount");
}
E 3
I 3
asm("mcount:	rsb");
E 15
I 15
D 20
asm(".globl mcount");
asm("mcount: rsb");
E 20
E 15
I 6
D 21
#endif CRT0
E 21
I 21
#endif
E 21
E 6
E 3
E 1
