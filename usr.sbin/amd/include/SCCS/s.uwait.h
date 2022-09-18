h04579
s 00002/00002/00055
d D 8.1 93/06/06 11:58:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 5.4 92/02/09 08:44:36 pendry 4 3
c merge in new release
e
s 00003/00002/00054
d D 5.3 91/05/12 16:00:45 pendry 3 2
c checkpoint for network tape
e
s 00002/00002/00054
d D 5.2 91/03/17 13:41:06 pendry 2 1
c from amd5.3 alpha11
e
s 00056/00000/00000
d D 5.1 90/07/19 15:39:27 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: uwait.h,v 5.2 90/06/23 22:20:31 jsp Rel $
E 2
I 2
D 3
 * $Id: uwait.h,v 5.2.1.1 90/10/21 22:30:35 jsp Exp $
E 2
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: uwait.h,v 5.2.1.2 91/05/07 22:19:23 jsp Alpha $
E 4
I 4
 * $Id: uwait.h,v 5.2.2.1 1992/02/09 15:10:01 jsp beta $
E 4
 *
E 3
 */

D 2
#if defined(mc68k) || defined(mc68000) || defined(mc68020) || defined(sparc) || defined(hp9000s300)
E 2
I 2
#if defined(mc68k) || defined(mc68000) || defined(mc68020) || defined(sparc) || defined(hp9000s300) || defined(hp9000s800)
E 2
#define BITS_BIGENDIAN
#endif
#if defined(vax) || defined(i386)
#define BITS_LITTLENDIAN
#endif
#if !defined BITS_BIGENDIAN && !defined BITS_LITTLENDIAN
 #error Do not know my byte ordering
#endif

/*
 * Structure of the information in the first word returned by both
 * wait and wait3.  If w_stopval==WSTOPPED, then the second structure
 * describes the information returned, else the first.  See WUNTRACED below.
 */
union wait	{
	int	w_status;		/* used in syscall */
	/*
	 * Terminated process status.
	 */
	struct {
#ifdef BITS_LITTLENDIAN
		unsigned short	w_Termsig:7;	/* termination signal */
		unsigned short	w_Coredump:1;	/* core dump indicator */
		unsigned short	w_Retcode:8;	/* exit code if w_termsig==0 */
#endif
#ifdef BITS_BIGENDIAN
		unsigned short	w_Fill1:16;	/* high 16 bits unused */
		unsigned short	w_Retcode:8;	/* exit code if w_termsig==0 */
		unsigned short	w_Coredump:1;	/* core dump indicator */
		unsigned short	w_Termsig:7;	/* termination signal */
#endif
	} w_U;
};
#define	w_termsig	w_U.w_Termsig
#define w_coredump	w_U.w_Coredump
#define w_retcode	w_U.w_Retcode

#define WIFSIGNALED(x)	((x).w_termsig != 0)
#define WIFEXITED(x)	((x).w_termsig == 0)
E 1
