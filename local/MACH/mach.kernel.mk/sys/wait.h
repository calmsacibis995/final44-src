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
 * $Log:	wait.h,v $
 * Revision 2.6  89/05/30  10:44:37  rvb
 * 	Keyed byte-order dependencies to BYTE_MSF.
 * 	[89/04/20            af]
 * 
 * Revision 2.5  89/03/09  22:11:21  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/25  17:59:26  gm0w
 * 	Got rid of CMUCS conditional. Changed romp to ibmrt
 * 	and got rid of include of cputypes.h.
 * 	[89/02/14            mrt]
 * 
 * Revision 2.3  89/01/23  22:30:21  af
 * 	Added Mips definitions for w_t and w_S.  MIPSEB defines Big
 * 	Endian byte order, MIPSEL Little Endian.
 * 	[89/01/09            af]
 * 
 * Revision 2.2  88/08/24  02:55:25  mwyoung
 * 	Adjusted include file references.
 * 	[88/08/17  02:29:35  mwyoung]
 *
 * 06-Jan-88  Jay Kistler (jjk) at Carnegie Mellon University
 *	Made file reentrant.  Added declarations for __STDC__.
 *
 * 28-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_GENERIC: Defined new WLOGINDEV option bit for wait3().
 *	[ V5.1(F1) ]
 *
 * 14-Dec-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merged romp and 68000 definitions since they were the same.
 *	The real conditional should be dependent on byte ordering.
 *
 * 30-May-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Added 68000 dependent definitions of w_t and w_S very similar to
 *	those for the ROMP.
 *
 * 19-Feb-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Added alternate definitions of w_T and w_S for Sailboat under
 *	switch ROMP.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)wait.h	7.1 (Berkeley) 6/4/86
 */

#ifndef	_SYS_WAIT_H_
#define _SYS_WAIT_H_

/*
 * This file holds definitions relevant to the wait system call.
 * Some of the options here are available only through the ``wait3''
 * entry point; the old entry point with one argument has more fixed
 * semantics, never returning status of unstopped children, hanging until
 * a process terminates if any are outstanding, and never returns
 * detailed information about process resource utilization (<vtimes.h>).
 */

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
#if	BYTE_MSF
		unsigned short  w_PAD16;
		unsigned        w_Retcode:8;    /* exit code if w_termsig==0 */
 		unsigned        w_Coredump:1;   /* core dump indicator */
 		unsigned        w_Termsig:7;    /* termination signal */
#else
		unsigned short	w_Termsig:7;	/* termination signal */
		unsigned short	w_Coredump:1;	/* core dump indicator */
		unsigned short	w_Retcode:8;	/* exit code if w_termsig==0 */
		unsigned short  w_PAD16;
#endif
	} w_T;
	/*
	 * Stopped process status.  Returned
	 * only for traced children unless requested
	 * with the WUNTRACED option bit.
	 */
	struct {
#if	BYTE_MSF
		unsigned short  w_PAD16;
 		unsigned        w_Stopsig:8;    /* signal that stopped us */
 		unsigned        w_Stopval:8;    /* == W_STOPPED if stopped */
#else
		unsigned short	w_Stopval:8;	/* == W_STOPPED if stopped */
		unsigned short	w_Stopsig:8;	/* signal that stopped us */
		unsigned short  w_PAD16;
#endif
	} w_S;
};
#define w_termsig	w_T.w_Termsig
#define w_coredump	w_T.w_Coredump
#define w_retcode	w_T.w_Retcode
#define w_stopval	w_S.w_Stopval
#define w_stopsig	w_S.w_Stopsig


#define WSTOPPED	0177	/* value of s.stopval if process is stopped */

/*
 * Option bits for the second argument of wait3.  WNOHANG causes the
 * wait to not hang if there are no stopped or terminated processes, rather
 * returning an error indication in this case (pid==0).  WUNTRACED
 * indicates that the caller should receive status about untraced children
 * which stop due to signals.  If children are stopped and a wait without
 * this option is done, it is as though they were still running... nothing
 * about them is returned.
 */
#define WNOHANG		1	/* dont hang in wait */
#define WUNTRACED	2	/* tell about stopped, untraced children */
#define WLOGINDEV	0x8000	/* tell about login device for child */


#define WIFSTOPPED(x)	((x).w_stopval == WSTOPPED)
#define WIFSIGNALED(x)	((x).w_stopval != WSTOPPED && (x).w_termsig != 0)
#define WIFEXITED(x)	((x).w_stopval != WSTOPPED && (x).w_termsig == 0)

#if	defined(__STDC__) && !defined(KERNEL)
#include <sys/resource.h>

extern int wait(union wait *);
extern int wait3(union wait *, int, struct rusage *);
#endif	defined(__STDC__) && !defined(KERNEL)

#endif	_SYS_WAIT_H_
