h27766
s 00001/00001/00055
d D 8.3 94/03/30 14:24:54 bostic 14 13
c sigset_t is unsigned, and sigemptyset should return an int
e
s 00002/00002/00054
d D 8.2 94/01/03 17:56:44 bostic 13 12
c use latest BSDI version of <sys/cdefs.h>, change to __keyword
e
s 00002/00002/00054
d D 8.1 93/06/06 21:58:01 bostic 12 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00049
d R 8.1 93/06/06 11:11:55 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00005/00051
d R 5.7 93/06/06 11:11:29 bostic 10 8
c delete extern declarations of sys_errlist, sys_nerr, sys_signame, and
c sys_siglist; they caused nothing but problems as they invariably clashed with
c declarations by the programs; delete unnecessary externs from ctype.h
e
s 00002/00002/00054
d R 8.1 93/06/02 20:06:45 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00054
d D 5.6 93/05/07 08:47:38 torek 8 6
c make the sys_ arrays all `const char *const []' (for consistency,
c and for compatibility with GNU/Cygnus)
e
s 00002/00002/00054
d R 5.6 93/05/07 08:31:38 bostic 7 6
c GNU put in the extra const, there's no reason to not have it...
e
s 00002/00002/00054
d D 5.5 93/02/03 15:05:48 elan 6 4
c sys_signame and sys_siglist are const's.
e
s 00000/00003/00053
d R 5.5 93/01/13 15:43:21 bostic 5 4
c sigaddset, sigdelset and sigismember have to return -1/EINVAL if the
c signal number is bogus.  Delete them from the include file as macros.
e
s 00007/00006/00049
d D 5.4 91/11/12 10:58:53 bostic 4 3
c List definitions after function declarations, or Reiser cpp gets upset.
e
s 00000/00001/00055
d D 5.3 91/11/11 11:55:52 bostic 3 2
c move the signal(3) prototype back into <sys/signal.h> to make the
c applications happy
e
s 00041/00000/00015
d D 5.2 91/10/23 17:04:41 bostic 2 1
c break sys/signal.h into user level and system level
e
s 00015/00000/00000
d D 5.1 91/08/02 11:48:40 bostic 1 0
c date and time created 91/08/02 11:48:40 by bostic
e
u
U
t
T
I 1
/*-
D 12
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 2
#ifndef _USER_SIGNAL_H
#define _USER_SIGNAL_H

#include <sys/types.h>
#include <sys/cdefs.h>
E 2
#include <sys/signal.h>

#if !defined(_ANSI_SOURCE) && !defined(_POSIX_SOURCE)
D 6
extern char *sys_signame[NSIG];
extern char *sys_siglist[NSIG];
E 6
I 6
D 8
extern char *const sys_signame[NSIG];
extern char *const sys_siglist[NSIG];
E 8
I 8
D 13
extern const char *const sys_signame[NSIG];
extern const char *const sys_siglist[NSIG];
E 13
I 13
extern __const char *__const sys_signame[NSIG];
extern __const char *__const sys_siglist[NSIG];
E 13
E 8
E 6
#endif
I 2

D 4
#define	sigaddset(set, signo)	(*(set) |= 1 << ((signo) - 1), 0)
#define	sigdelset(set, signo)	(*(set) &= ~(1 << ((signo) - 1)), 0)
#define	sigemptyset(set)	(*(set) = 0)
#define	sigfillset(set)		(*(set) = ~(sigset_t)0, 0)
#define	sigismember(set, signo)	((*(set) & (1 << ((signo) - 1))) != 0)

E 4
__BEGIN_DECLS
int	raise __P((int));
D 3
void	(*signal __P((int, void (*) __P((int))))) __P((int));
E 3
#ifndef	_ANSI_SOURCE
int	kill __P((pid_t, int));
int	sigaction __P((int, const struct sigaction *, struct sigaction *));
int	sigaddset __P((sigset_t *, int));
int	sigdelset __P((sigset_t *, int));
int	sigemptyset __P((sigset_t *));
int	sigfillset __P((sigset_t *));
int	sigismember __P((const sigset_t *, int));
int	sigpending __P((sigset_t *));
int	sigprocmask __P((int, const sigset_t *, sigset_t *));
int	sigsuspend __P((const sigset_t *));
#ifndef _POSIX_SOURCE
int	killpg __P((pid_t, int));
int	sigblock __P((int));
int	siginterrupt __P((int, int));
int	sigpause __P((int));
int	sigreturn __P((struct sigcontext *));
int	sigsetmask __P((int));
int	sigstack __P((const struct sigstack *, struct sigstack *));
int	sigvec __P((int, struct sigvec *, struct sigvec *));
void	psignal __P((unsigned int, const char *));
#endif	/* !_POSIX_SOURCE */
#endif	/* !_ANSI_SOURCE */
__END_DECLS
I 4

/* List definitions after function declarations, or Reiser cpp gets upset. */
#define	sigaddset(set, signo)	(*(set) |= 1 << ((signo) - 1), 0)
#define	sigdelset(set, signo)	(*(set) &= ~(1 << ((signo) - 1)), 0)
D 14
#define	sigemptyset(set)	(*(set) = 0)
E 14
I 14
#define	sigemptyset(set)	(*(set) = 0, 0)
E 14
#define	sigfillset(set)		(*(set) = ~(sigset_t)0, 0)
#define	sigismember(set, signo)	((*(set) & (1 << ((signo) - 1))) != 0)
E 4

#endif	/* !_USER_SIGNAL_H */
E 2
E 1
