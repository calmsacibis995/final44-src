h62291
s 00002/00002/00128
d D 8.2 94/07/10 22:59:11 bostic 24 23
c fix comment
e
s 00002/00002/00128
d D 8.1 93/06/02 19:57:07 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00002/00130
d D 7.19 93/05/07 14:53:21 mckusick 22 21
c endian.h now protects itself
e
s 00001/00001/00131
d D 7.18 92/07/09 12:42:24 mckusick 21 20
c fix comment
e
s 00016/00013/00116
d D 7.17 91/06/19 16:12:57 karels 20 19
c bit fields need to use ints; make the ifdefs consistent
e
s 00002/00000/00127
d D 7.16 91/02/23 18:40:00 donn 19 18
c Add a forward declaration of struct rusage.
e
s 00003/00001/00124
d D 7.15 91/02/23 14:27:17 donn 18 17
c wait3 and wait4 aren't POSIX functions.
e
s 00008/00011/00117
d D 7.14 91/02/05 17:03:31 bostic 17 16
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00127
d D 7.13 90/10/31 11:17:11 bostic 16 15
c don't include function prototypes in the kernel
e
s 00001/00000/00127
d D 7.12 90/10/23 23:31:28 mckusick 15 14
c need types.h
e
s 00002/00000/00125
d D 7.11 90/10/22 10:01:58 bostic 14 13
c kernel has wait functions that don't return pid's.
e
s 00012/00000/00113
d D 7.10 90/10/12 08:23:16 bostic 13 12
c add function prototypes
e
s 00001/00011/00112
d D 7.9 90/06/28 22:02:13 bostic 12 11
c new copyright notice
e
s 00014/00018/00109
d D 7.8 90/02/22 15:57:33 karels 11 10
c I think it's posix now!
e
s 00052/00053/00075
d D 7.7 89/08/26 16:34:35 karels 10 9
c deprecate union wait, rearrange for posix
e
s 00019/00001/00109
d D 7.6 89/08/26 16:33:08 karels 9 8
c first cut at _POSIX_SOURCE
e
s 00041/00015/00069
d D 7.5 89/04/08 15:56:09 karels 8 7
c add posix macros, update for wait4.  (still need to hack _posix_source_)
e
s 00001/00001/00083
d D 7.4 88/01/27 17:14:27 karels 7 6
c no endian
e
s 00004/00004/00080
d D 7.3 88/01/07 11:33:45 karels 6 5
c rename endians
e
s 00018/00000/00066
d D 7.2 86/10/13 23:01:42 karels 5 4
c byteorder dependency
e
s 00001/00001/00065
d D 7.1 86/06/04 23:33:19 mckusick 4 3
c 4.3BSD release version
e
s 00007/00001/00059
d D 6.2 85/06/08 15:15:04 mckusick 3 2
c Add copyright
e
s 00000/00000/00060
d D 6.1 83/07/29 06:15:28 sam 2 1
c 4.2 distribution
e
s 00060/00000/00000
d D 4.1 83/02/10 21:42:09 sam 1 0
c date and time created 83/02/10 21:42:09 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
D 4
 * Copyright (c) 1982 Regents of the University of California.
E 4
I 4
D 8
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 4
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 23
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
D 24
 * Copyright (c) 1982, 1986, 1989, 1993
E 24
I 24
 * Copyright (c) 1982, 1986, 1989, 1993, 1994
E 24
 *	The Regents of the University of California.  All rights reserved.
E 23
E 8
 *
I 8
D 12
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 12
I 12
 * %sccs.include.redist.c%
E 12
 *
E 8
 *	%W% (Berkeley) %G%
 */
E 3

/*
D 8
 * This file holds definitions relevent to the wait system call.
 * Some of the options here are available only through the ``wait3''
 * entry point; the old entry point with one argument has more fixed
 * semantics, never returning status of unstopped children, hanging until
 * a process terminates if any are outstanding, and never returns
 * detailed information about process resource utilization (<vtimes.h>).
E 8
I 8
 * This file holds definitions relevent to the wait4 system call
 * and the alternate interfaces that use it (wait, wait3, waitpid).
E 8
 */

I 9
D 10
#ifndef _POSIX_SOURCE

E 9
I 5
D 7
#ifndef ENDIAN
E 7
I 7
#ifndef BYTE_ORDER
E 7
D 6
#include <machine/machparam.h>
E 6
I 6
#include <machine/endian.h>
E 10
I 10
/*
 * Macros to test the exit status returned by wait
 * and extract the relevant values.
 */
#ifdef _POSIX_SOURCE
D 11
#define	_WSTATUS(x)	((x) & 0377)	/* 0, _WSTOPPED, or signal */
E 11
I 11
#define	_W_INT(i)	(i)
E 11
#else
D 11
#define	_W_INT(x)	(*(int *)(x))	/* convert union wait to int */
#define	_WSTATUS(x)	(_W_INT(x) & 0177)
E 11
I 11
#define	_W_INT(w)	(*(int *)&(w))	/* convert union wait to int */
#define	WCOREFLAG	0200
E 11
E 10
E 6
#endif

I 11
#define	_WSTATUS(x)	(_W_INT(x) & 0177)
E 11
I 10
#define	_WSTOPPED	0177		/* _WSTATUS if process is stopped */
#define WIFSTOPPED(x)	(_WSTATUS(x) == _WSTOPPED)
I 11
#define WSTOPSIG(x)	(_W_INT(x) >> 8)
E 11
#define WIFSIGNALED(x)	(_WSTATUS(x) != _WSTOPPED && _WSTATUS(x) != 0)
#define WTERMSIG(x)	(_WSTATUS(x))
#define WIFEXITED(x)	(_WSTATUS(x) == 0)
D 11

#ifdef _POSIX_SOURCE
#define WSTOPSIG(x)	((x) >> 8)
#define WEXITSTATUS(x)	((x) >> 8)

#else /* _POSIX_SOURCE */
#define WSTOPSIG(x)	(_W_INT(x) >> 8)
#define WCOREDUMP(x)	(_W_INT(x) & 0200)
E 11
#define WEXITSTATUS(x)	(_W_INT(x) >> 8)
D 11
#endif /* _POSIX_SOURCE */
E 11
I 11
#ifndef _POSIX_SOURCE
#define WCOREDUMP(x)	(_W_INT(x) & WCOREFLAG)
E 11

I 11
#define	W_EXITCODE(ret, sig)	((ret) << 8 | (sig))
#define	W_STOPCODE(sig)		((sig) << 8 | _WSTOPPED)
#endif

E 11
E 10
E 5
/*
I 10
D 21
 * Option bits for the second argument of wait4.  WNOHANG causes the
E 21
I 21
 * Option bits for the third argument of wait4.  WNOHANG causes the
E 21
 * wait to not hang if there are no stopped or terminated processes, rather
 * returning an error indication in this case (pid==0).  WUNTRACED
 * indicates that the caller should receive status about untraced children
 * which stop due to signals.  If children are stopped and a wait without
 * this option is done, it is as though they were still running... nothing
D 11
 * about them is returned.   By default, a blocking wait call will be
 * aborted by receipt of a signal that is caught (POSIX); the option
 * WSIGRESTART causes the call to restart instead of failing with error EINTR.
E 11
I 11
 * about them is returned.
E 11
 */
D 24
#define WNOHANG		1	/* dont hang in wait */
E 24
I 24
#define WNOHANG		1	/* don't hang in wait */
E 24
#define WUNTRACED	2	/* tell about stopped, untraced children */

D 11
#ifndef _POSIX_SOURCE		/* extensions/compat follow: */
/* additional option bit for wait4: */
#define WSIGRESTART	4	/* restart wait if signal is received */
E 11
I 11
#ifndef _POSIX_SOURCE
/* POSIX extensions and 4.2/4.3 compatability: */
E 11

/*
E 10
D 8
 * Structure of the information in the first word returned by both
 * wait and wait3.  If w_stopval==WSTOPPED, then the second structure
 * describes the information returned, else the first.  See WUNTRACED below.
E 8
I 8
 * Tokens for special values of the "pid" parameter to wait4.
E 8
 */
D 8
union wait	{
E 8
I 8
D 10
#define	WAIT_ANY	(-1)		/* any process */
#define	WAIT_MYPGRP	0		/* any process in my process group */
E 10
I 10
#define	WAIT_ANY	(-1)	/* any process */
#define	WAIT_MYPGRP	0	/* any process in my process group */
E 10

I 10
D 22
#ifndef BYTE_ORDER
E 22
#include <machine/endian.h>
D 22
#endif
E 22

E 10
/*
I 10
 * Deprecated:
E 10
 * Structure of the information in the status word returned by wait4.
 * If w_stopval==WSTOPPED, then the second structure describes
D 10
 * the information returned, else the first.  See WUNTRACED below.
E 10
I 10
 * the information returned, else the first.
E 10
 */
union wait {
E 8
	int	w_status;		/* used in syscall */
	/*
	 * Terminated process status.
	 */
	struct {
I 5
D 6
#if ENDIAN == LITTLE
E 6
I 6
#if BYTE_ORDER == LITTLE_ENDIAN 
E 6
E 5
D 20
		unsigned short	w_Termsig:7;	/* termination signal */
		unsigned short	w_Coredump:1;	/* core dump indicator */
		unsigned short	w_Retcode:8;	/* exit code if w_termsig==0 */
E 20
I 20
		unsigned int	w_Termsig:7,	/* termination signal */
				w_Coredump:1,	/* core dump indicator */
				w_Retcode:8,	/* exit code if w_termsig==0 */
				w_Filler:16;	/* upper bits filler */
E 20
I 5
#endif
D 6
#if ENDIAN == BIG
E 6
I 6
#if BYTE_ORDER == BIG_ENDIAN 
E 6
D 20
		unsigned short	w_Filler;	/* upper bits filler */
		unsigned char	w_Retcode;	/* exit code if w_termsig==0 */
		unsigned char	w_Coredump:1;	/* core dump indicator */
		unsigned char	w_Termsig:7;	/* termination signal */
E 20
I 20
		unsigned int	w_Filler:16,	/* upper bits filler */
				w_Retcode:8,	/* exit code if w_termsig==0 */
				w_Coredump:1,	/* core dump indicator */
				w_Termsig:7;	/* termination signal */
E 20
#endif
E 5
	} w_T;
	/*
	 * Stopped process status.  Returned
	 * only for traced children unless requested
	 * with the WUNTRACED option bit.
	 */
	struct {
I 5
D 6
#if ENDIAN == LITTLE
E 6
I 6
#if BYTE_ORDER == LITTLE_ENDIAN 
E 6
E 5
D 20
		unsigned short	w_Stopval:8;	/* == W_STOPPED if stopped */
		unsigned short	w_Stopsig:8;	/* signal that stopped us */
I 5
#else
		unsigned short	w_Filler;	/* upper bits filler */
		unsigned char	w_Stopsig;	/* signal that stopped us */
		unsigned char	w_Stopval;	/* == W_STOPPED if stopped */
E 20
I 20
		unsigned int	w_Stopval:8,	/* == W_STOPPED if stopped */
				w_Stopsig:8,	/* signal that stopped us */
				w_Filler:16;	/* upper bits filler */
#endif
#if BYTE_ORDER == BIG_ENDIAN 
		unsigned int	w_Filler:16,	/* upper bits filler */
				w_Stopsig:8,	/* signal that stopped us */
				w_Stopval:8;	/* == W_STOPPED if stopped */
E 20
#endif
E 5
	} w_S;
};
#define	w_termsig	w_T.w_Termsig
#define w_coredump	w_T.w_Coredump
#define w_retcode	w_T.w_Retcode
#define w_stopval	w_S.w_Stopval
#define w_stopsig	w_S.w_Stopsig

D 10

#define	WSTOPPED	0177	/* value of s.stopval if process is stopped */
I 9
#endif /* _POSIX_SOURCE */
E 9

/*
D 8
 * Option bits for the second argument of wait3.  WNOHANG causes the
E 8
I 8
 * Option bits for the second argument of wait4.  WNOHANG causes the
E 8
 * wait to not hang if there are no stopped or terminated processes, rather
 * returning an error indication in this case (pid==0).  WUNTRACED
 * indicates that the caller should receive status about untraced children
 * which stop due to signals.  If children are stopped and a wait without
 * this option is done, it is as though they were still running... nothing
D 8
 * about them is returned.
E 8
I 8
 * about them is returned.   By default, a blocking wait call will be
 * aborted by receipt of a signal that is caught (POSIX); the option
 * WSIGRESTART causes the call to restart instead of failing with error EINTR.
E 8
 */
#define WNOHANG		1	/* dont hang in wait */
#define WUNTRACED	2	/* tell about stopped, untraced children */
I 9
#ifndef _POSIX_SOURCE
E 9
I 8
#define WSIGRESTART	4	/* restart wait if signal is received */
I 9
#endif /* _POSIX_SOURCE */
E 9
E 8

I 8
/*
 * Macros to test the exit status returned by wait
 * and extract the relevant values.
 */
I 9
#ifndef _POSIX_SOURCE
E 9
E 8
#define WIFSTOPPED(x)	((x).w_stopval == WSTOPPED)
I 8
#define WSTOPSIG(x)	((x).w_stopsig)

E 8
#define WIFSIGNALED(x)	((x).w_stopval != WSTOPPED && (x).w_termsig != 0)
I 8
#define WTERMSIG(x)	((x).w_termsig)
#define WCOREDUMP(x)	((x).w_coredump)

E 8
D 9
#define WIFEXITED(x)	((x).w_stopval != WSTOPPED && (x).w_termsig == 0)
E 9
I 9
#define WIFEXITED(x)	((x).w_termsig == 0)
E 9
I 8
#define WEXITSTATUS(x)	((x).w_retcode)
I 9

#else /* _POSIX_SOURCE */

#define WIFSTOPPED(x)	(((x) & 0377) == 0177)
#define WSTOPSIG(x)	((x) >> 8)

#define WIFSIGNALED(x)	(((x) & 0377 != 0177 && ((x) & 0377) != 0)
#define WTERMSIG(x)	((x) & 0177)

#define WIFEXITED(x)	(((x) & 0377) == 0)
#define WEXITSTATUS(x)	((x) >> 8)
E 10
I 10
#define	WSTOPPED	_WSTOPPED
E 10
#endif /* _POSIX_SOURCE */
I 13

I 14
#ifndef KERNEL
I 15
D 16
#include <sys/types.h>
E 16
E 15
E 14
D 17
#if __STDC__ || c_plusplus
E 17
I 16
#include <sys/types.h>
E 16
D 17
pid_t wait(int *);
pid_t waitpid(pid_t, int *, int);
pid_t wait3(int *, int, struct rusage *);
pid_t wait4(pid_t, int *, int, struct rusage *);
#else
pid_t wait();
pid_t waitpid();
pid_t wait3();
pid_t wait4();
I 14
#endif
E 17
I 17
#include <sys/cdefs.h>

__BEGIN_DECLS
I 19
struct rusage;	/* forward declaration */

E 19
pid_t	wait __P((int *));
I 18
pid_t	waitpid __P((pid_t, int *, int));
#ifndef _POSIX_SOURCE
E 18
pid_t	wait3 __P((int *, int, struct rusage *));
pid_t	wait4 __P((pid_t, int *, int, struct rusage *));
D 18
pid_t	waitpid __P((pid_t, int *, int));
E 18
I 18
#endif
E 18
__END_DECLS
E 17
E 14
#endif
E 13
E 9
E 8
E 1
