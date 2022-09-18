h31379
s 00002/00001/00250
d D 8.12 95/05/23 10:10:50 eric 47 46
c make return values in sleep() match prototype
e
s 00001/00001/00250
d D 8.11 95/04/21 09:57:25 eric 46 45
c update copyright notice
e
s 00005/00004/00246
d D 8.10 95/02/23 15:50:53 eric 45 44
c cleanup to make gcc -Winitialized happier
e
s 00002/00002/00248
d D 8.9 94/12/28 07:31:54 eric 44 43
c portability fixes for Amdahl UTS System V 2.1.5
e
s 00006/00005/00244
d D 8.8 94/01/12 06:00:01 eric 43 42
c change prototypes of tick() to match signal handler
e
s 00003/00000/00246
d D 8.7 93/10/21 12:28:16 eric 42 41
c fix errno race condition
e
s 00017/00013/00229
d D 8.6 93/09/29 10:55:30 eric 41 40
c fix some race conditions
e
s 00004/00005/00238
d D 8.5 93/07/26 09:22:04 eric 40 39
c signal and file locking portability changes
e
s 00005/00001/00238
d D 8.4 93/07/21 09:09:02 eric 39 38
c portability for Sony NEWS workstations
e
s 00001/00002/00238
d D 8.3 93/07/19 20:50:15 eric 38 37
c SGI IRIX & ANSI C portability
e
s 00010/00000/00230
d D 8.2 93/07/13 12:58:36 eric 37 36
c many fixes.  primarily fix for seteuid problem in 8.2; also,
c Solaris compatibility fixes; timed out messages problems; messages
c silently discarded if checkcompat returned EX_TEMPFAIL
e
s 00002/00002/00228
d D 8.1 93/06/07 10:29:16 bostic 36 35
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00226
d D 6.4 93/05/30 08:54:15 eric 35 34
c Solaris portability changes
e
s 00001/00000/00225
d D 6.3 93/03/01 06:53:37 eric 34 33
c header file cleanup; primarily #include <unistd.h> in sendmail.h
c and delete duplicate cruft
e
s 00001/00001/00224
d D 6.2 93/02/23 06:31:49 eric 33 32
c overhaul status of SMTP reply codes
e
s 00000/00000/00225
d D 6.1 92/12/21 16:08:44 eric 32 31
c Release 6
e
s 00001/00001/00224
d D 5.11 92/11/14 11:34:26 eric 31 30
c (partially) ANSI-fy it
e
s 00001/00001/00224
d D 5.10 91/03/04 13:43:07 bostic 30 29
c ANSI
e
s 00004/00002/00221
d D 5.9 91/03/02 17:15:13 bostic 29 28
c ANSI
e
s 00001/00011/00222
d D 5.8 90/06/01 19:00:24 bostic 28 27
c new copyright notice
e
s 00000/00010/00233
d D 5.7 89/01/01 17:16:52 bostic 27 26
c remove DEBUG
e
s 00011/00009/00232
d D 5.6 88/06/30 14:58:21 bostic 26 25
c install approved copyright notice
e
s 00016/00010/00225
d D 5.5 88/03/13 19:51:32 bostic 25 24
c add Berkeley specific header
e
s 00001/00001/00234
d D 5.4 85/12/17 23:52:47 eric 24 23
m 
c lint
e
s 00002/00002/00233
d D 5.3 85/09/19 13:36:02 eric 23 22
m 
c lint
e
s 00000/00000/00235
d D 5.2 85/06/08 10:30:56 eric 22 21
m 
c lint for 4.3 release
e
s 00014/00002/00221
d D 5.1 85/06/07 14:29:40 dist 21 20
m 
c Add copyright
e
s 00005/00000/00218
d D 4.4 85/05/15 20:26:38 eric 20 19
m 
c reenable signals in an event that may be called to run the queue; this
c allows hung connections to time out properly during a queue run.  This
c fix provided by Bill Nowicki.
e
s 00002/00001/00216
d D 4.3 84/12/05 23:15:24 eric 19 18
m 
c Try to use flock call (this doesn't work because we don't always have an
c open fd); security and performance fixes from Kirk Smith at Purdue; "a"
c option is now the number of minutes to wait for "@:@" alias; fix bug in
c $[ $] using -t; random cleanup
e
s 00007/00004/00210
d D 4.2 84/03/11 13:38:29 eric 18 17
m 
c fixes from Greg Satz <satz@sri-tsc.ARPA>, mostly for PDP's
e
s 00000/00000/00214
d D 4.1 83/07/25 19:46:23 eric 17 16
m 
c 4.2 release version
e
s 00003/00003/00211
d D 3.15 83/05/21 11:01:45 eric 16 15
m 
c Miscellaneous changes for PDP-11's.
c Always send to a login name before a full name.
e
s 00001/00000/00213
d D 3.14 83/03/26 14:27:20 eric 15 14
m 214
c changes from MRH for USG UNIX 5.0
e
s 00008/00002/00205
d D 3.13 82/11/28 00:20:57 eric 14 13
m 
c Many changes resulting from a complete code readthrough.  Most of these
c fix minor bugs or change the internal structure for clarity, etc.  There
c should be almost no externally visible changes (other than some cleaner
c error message printouts and the like).
e
s 00004/00004/00203
d D 3.12 82/11/24 18:43:55 eric 13 12
m 
c lint it
e
s 00003/00004/00204
d D 3.11 82/09/08 21:19:42 eric 12 11
c try to avoid "Interrupted system call" on wait in deliver and on
c writes; fix returned message to have proper sender; handle extra
c mailer output more cleverly.
e
s 00004/00004/00204
d D 3.10 82/09/05 18:03:30 eric 11 10
c tune debugging
e
s 00006/00010/00202
d D 3.9 82/08/27 16:00:12 eric 10 8
c simplify timeout code; allow multiple simultaneous queue runs so that
c large messages don't freeze things up; fix EINTR problem in sfgets;
c clean up canonname to be really correct; lots of misc. cleanup
e
s 00000/00000/00212
d R 3.9 82/08/27 15:47:44 eric 9 8
c simplify timeout code; allow multiple simultaneous queue runs so that
c large messages don't freeze things up; fix EINTR in sfgets; clean up
c canonname to be really correct; lots of misc. cleanup
e
s 00007/00002/00205
d D 3.8 82/08/27 11:11:17 eric 8 7
c release e_id after fork in daemon code; ignore events scheduled by
c another process
e
s 00006/00004/00201
d D 3.7 82/08/25 16:18:35 eric 7 6
c apply ruleset 4 to rewrite addresses in the body of the message; fix
c a clock.c bug that caused it to lose events; more time cleanup.
e
s 00020/00013/00185
d D 3.6 82/08/24 10:27:17 eric 6 5
c clean up event handling so that events that do longjmp's don't turn
c off all future events.
e
s 00012/00000/00186
d D 3.5 82/08/15 11:55:40 eric 5 4
c don't choke on zero intervals
e
s 00036/00000/00150
d D 3.4 82/08/08 21:15:40 eric 4 3
c make "sleep" work correctly even in the face of other events; clean
c up the queue processing: child queue runs now go away when done.  more
c debugging logging is needed to verify that this works right though.
e
s 00128/00005/00022
d D 3.3 82/08/08 17:02:26 eric 3 2
c more general event mechanism
e
s 00001/00001/00026
d D 3.2 82/08/08 01:02:21 eric 2 1
c change debug level to a debug vector; add levels on logging (and the
c -L flag); change logging to be by message-id; elevate message-id;
c some lint-type cleanup
e
s 00027/00000/00000
d D 3.1 82/07/05 12:23:56 eric 1 0
c date and time created 82/07/05 12:23:56 by eric
e
u
U
f b 
f i 
t
T
I 21
/*
I 26
D 46
 * Copyright (c) 1983 Eric P. Allman
E 46
I 46
 * Copyright (c) 1983, 1995 Eric P. Allman
E 46
E 26
D 25
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 25
I 25
D 36
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 36
I 36
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 36
 *
D 28
 * Redistribution and use in source and binary forms are permitted
D 26
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 26
I 26
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
E 28
I 28
 * %sccs.include.redist.c%
E 28
E 26
 */
E 25

#ifndef lint
D 25
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 25
I 25
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 25

E 21
I 1
# include "sendmail.h"
I 15
D 40
# include <signal.h>
E 40
E 15
D 21

SCCSID(%W%	%Y%	%G%);
E 21

I 35
# ifndef sigmask
#  define sigmask(s)	(1 << ((s) - 1))
# endif

E 35
/*
I 3
**  SETEVENT -- set an event to happen at a specific time.
**
I 14
**	Events are stored in a sorted list for fast processing.
**	An event only applies to the process that set it.
**
E 14
**	Parameters:
**		intvl -- intvl until next event occurs.
**		func -- function to call on event.
**		arg -- argument to func on event.
**
**	Returns:
**		none.
**
**	Side Effects:
**		none.
*/

I 29
D 43
static void tick();
E 43
I 43
static void tick __P((int));
E 43

E 29
EVENT *
setevent(intvl, func, arg)
	time_t intvl;
D 45
	int (*func)();
E 45
I 45
	void (*func)();
E 45
	int arg;
{
	register EVENT **evp;
	register EVENT *ev;
	auto time_t now;
D 29
	extern tick();
E 29

I 5
D 27
# ifdef DEBUG
E 27
	if (intvl <= 0)
	{
D 33
		syserr("setevent: intvl=%ld\n", intvl);
E 33
I 33
		syserr("554 setevent: intvl=%ld\n", intvl);
E 33
D 13
		return;
E 13
I 13
		return (NULL);
E 13
	}
D 27
# endif DEBUG
E 27

I 41
	(void) setsignal(SIGALRM, SIG_IGN);
E 41
E 5
	(void) time(&now);

	/* search event queue for correct position */
	for (evp = &EventQueue; (ev = *evp) != NULL; evp = &ev->ev_link)
	{
		if (ev->ev_time >= now + intvl)
			break;
	}

	/* insert new event */
	ev = (EVENT *) xalloc(sizeof *ev);
	ev->ev_time = now + intvl;
	ev->ev_func = func;
	ev->ev_arg = arg;
I 8
	ev->ev_pid = getpid();
E 8
	ev->ev_link = *evp;
	*evp = ev;

D 10
	/* reschedule next clock tick if appropriate */
	if (ev == EventQueue)
	{
		/* we have a new event */
		(void) signal(SIGALRM, tick);
		(void) alarm(intvl);
	}

E 10
D 27
# ifdef DEBUG
E 27
D 11
	if (tTd(5, 2))
E 11
I 11
	if (tTd(5, 5))
E 11
		printf("setevent: intvl=%ld, for=%ld, func=%x, arg=%d, ev=%x\n",
			intvl, now + intvl, func, arg, ev);
D 27
# endif DEBUG
E 27

I 10
D 43
	tick();
E 43
I 43
	tick(0);
E 43
E 10
	return (ev);
}
/*
**  CLREVENT -- remove an event from the event queue.
**
**	Parameters:
**		ev -- pointer to event to remove.
**
**	Returns:
**		none.
**
**	Side Effects:
**		arranges for event ev to not happen.
*/

I 45
void
E 45
clrevent(ev)
	register EVENT *ev;
{
	register EVENT **evp;

D 27
# ifdef DEBUG
E 27
D 11
	if (tTd(5, 2))
E 11
I 11
	if (tTd(5, 5))
E 11
		printf("clrevent: ev=%x\n", ev);
D 27
# endif DEBUG
E 27
I 5
	if (ev == NULL)
		return;
E 5

	/* find the parent event */
I 6
D 14
	signal(SIGALRM, SIG_IGN);
E 14
I 14
D 40
	(void) signal(SIGALRM, SIG_IGN);
E 40
I 40
	(void) setsignal(SIGALRM, SIG_IGN);
E 40
E 14
E 6
	for (evp = &EventQueue; *evp != NULL; evp = &(*evp)->ev_link)
	{
		if (*evp == ev)
			break;
	}

	/* now remove it */
D 6
	if (*evp == NULL)
	{
		/* hmmmmm.... must have happened. */
		return;
	}

E 6
D 10
	*evp = ev->ev_link;
	free(ev);
E 10
I 10
	if (*evp != NULL)
	{
		*evp = ev->ev_link;
D 13
		free(ev);
E 13
I 13
		free((char *) ev);
E 13
	}
E 10
I 6

	/* restore clocks and pick up anything spare */
D 43
	tick();
E 43
I 43
	tick(0);
E 43
E 6
}
/*
E 3
**  TICK -- take a clock tick
**
D 3
**	Someday this will have to do more complex event scheduling.
E 3
I 3
**	Called by the alarm clock.  This routine runs events as needed.
E 3
**
**	Parameters:
D 43
**		none.
E 43
I 43
**		One that is ignored; for compatibility with signal handlers.
E 43
**
**	Returns:
D 3
**		non-local through TickFrame.
E 3
I 3
**		none.
E 3
**
**	Side Effects:
D 3
**		none.
E 3
I 3
**		calls the next function in EventQueue.
E 3
*/

I 29
D 30
void
E 30
I 30
static void
E 30
E 29
D 43
tick()
E 43
I 43
tick(arg)
	int arg;
E 43
{
I 3
D 7
	auto time_t now;
E 7
I 7
	register time_t now;
E 7
	register EVENT *ev;
I 19
D 23
	int pid = getpid();
E 23
I 23
	int mypid = getpid();
I 42
	int olderrno = errno;
E 42
I 37
#ifdef SIG_UNBLOCK
	sigset_t ss;
#endif
E 37
E 23
E 19

I 4
D 6
	signal(SIGALRM, SIG_IGN);
E 6
I 6
D 14
	signal(SIGALRM, tick);
E 14
I 14
D 40
	(void) signal(SIGALRM, SIG_IGN);
E 40
I 40
	(void) setsignal(SIGALRM, SIG_IGN);
E 40
	(void) alarm(0);
E 14
E 6
E 4
D 7
	(void) time(&now);
E 7
I 7
	now = curtime();
E 7

E 3
D 27
# ifdef DEBUG
E 27
D 2
	if (Debug > 0)
E 2
I 2
D 11
	if (tTd(5, 1))
E 11
I 11
	if (tTd(5, 4))
E 11
E 2
D 3
		printf("tick\n");
E 3
I 3
		printf("tick: now=%ld\n", now);
E 3
D 27
# endif DEBUG
E 27
D 3
	longjmp(TickFrame, 1);
E 3
I 3

D 12
	while (EventQueue != NULL && EventQueue->ev_time <= now)
E 12
I 12
	while ((ev = EventQueue) != NULL &&
D 19
	       (ev->ev_time <= now || ev->ev_pid != getpid()))
E 19
I 19
D 23
	       (ev->ev_time <= now || ev->ev_pid != pid))
E 23
I 23
	       (ev->ev_time <= now || ev->ev_pid != mypid))
E 23
E 19
E 12
	{
I 6
D 18
		int (*f)(), a;
E 18
I 18
D 45
		int (*f)();
E 45
I 45
		void (*f)();
E 45
		int arg;
		int pid;
E 18
I 8
D 12
		int pid;
E 12
E 8

E 6
		/* process the event on the top of the queue */
		ev = EventQueue;
		EventQueue = EventQueue->ev_link;
D 27
# ifdef DEBUG
E 27
D 11
		if (tTd(5, 3))
E 11
I 11
		if (tTd(5, 6))
E 11
D 8
			printf("tick: ev=%x, func=%x, arg=%d\n", ev,
				ev->ev_func, ev->ev_arg);
E 8
I 8
			printf("tick: ev=%x, func=%x, arg=%d, pid=%d\n", ev,
				ev->ev_func, ev->ev_arg, ev->ev_pid);
E 8
D 27
# endif DEBUG
E 27
D 6
		(*ev->ev_func)(ev->ev_arg);
E 6
I 6

		/* we must be careful in here because ev_func may not return */
I 14
D 40
		(void) signal(SIGALRM, tick);
E 40
I 40
D 41
		(void) setsignal(SIGALRM, tick);
E 40
I 37
#ifdef SIG_UNBLOCK
		/* unblock SIGALRM signal */
		sigemptyset(&ss);
		sigaddset(&ss, SIGALRM);
		sigprocmask(SIG_UNBLOCK, &ss, NULL);
#else
E 37
I 20
#ifdef SIGVTALRM
		/* reset 4.2bsd signal mask to allow future alarms */
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGALRM));
D 31
#endif SIGVTALRM
E 31
I 31
#endif /* SIGVTALRM */
I 37
#endif /* SIG_UNBLOCK */
E 37
E 31

E 41
E 20
E 14
		f = ev->ev_func;
D 18
		a = ev->ev_arg;
E 18
I 18
		arg = ev->ev_arg;
		pid = ev->ev_pid;
E 18
I 8
D 12
		pid = ev->ev_pid;
E 12
E 8
E 6
D 13
		free(ev);
E 13
I 13
		free((char *) ev);
E 13
I 8
D 12
		if (pid != getpid())
E 12
I 12
D 18
		if (ev->ev_pid != getpid())
E 18
I 18
		if (pid != getpid())
E 18
E 12
			continue;
E 8
I 6
		if (EventQueue != NULL)
		{
			if (EventQueue->ev_time > now)
D 16
				(void) alarm(EventQueue->ev_time - now);
E 16
I 16
				(void) alarm((unsigned) (EventQueue->ev_time - now));
E 16
			else
D 7
				(void) alarm(1);
E 7
I 7
				(void) alarm(3);
E 7
		}
I 41

		/* restore signals so that we can take ticks while in ev_func */
		(void) setsignal(SIGALRM, tick);
#ifdef SIG_UNBLOCK
		/* unblock SIGALRM signal */
		sigemptyset(&ss);
		sigaddset(&ss, SIGALRM);
		sigprocmask(SIG_UNBLOCK, &ss, NULL);
#else
D 44
#ifdef SIGVTALRM
E 44
I 44
#if HASSIGSETMASK
E 44
		/* reset 4.2bsd signal mask to allow future alarms */
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGALRM));
D 44
#endif /* SIGVTALRM */
E 44
I 44
#endif /* HASSIGSETMASK */
E 44
#endif /* SIG_UNBLOCK */

		/* call ev_func */
I 42
		errno = olderrno;
E 42
E 41
D 18
		(*f)(a);
E 18
I 18
		(*f)(arg);
E 18
		(void) alarm(0);
E 6
D 7
		(void) time(&now);
E 7
I 7
		now = curtime();
E 7
	}
I 14
D 40
	(void) signal(SIGALRM, tick);
E 40
I 40
	(void) setsignal(SIGALRM, tick);
E 40
E 14
I 7
	if (EventQueue != NULL)
D 16
		(void) alarm(EventQueue->ev_time - now);
E 16
I 16
		(void) alarm((unsigned) (EventQueue->ev_time - now));
I 42
	errno = olderrno;
E 42
E 16
E 7
D 6

	/* schedule the next clock tick */
	signal(SIGALRM, tick);
	if (EventQueue != NULL)
		(void) alarm(EventQueue->ev_time - now);
E 6
I 4
}
/*
**  SLEEP -- a version of sleep that works with this stuff
**
**	Because sleep uses the alarm facility, I must reimplement
**	it here.
**
**	Parameters:
**		intvl -- time to sleep.
**
**	Returns:
**		none.
**
**	Side Effects:
**		waits for intvl time.  However, other events can
**		be run during that interval.
*/

static bool	SleepDone;
I 38
D 45
static int	endsleep();
E 45
I 45
static void	endsleep();
E 45
E 38

I 34
D 39
unsigned int
E 39
I 39
#ifndef SLEEP_T
# define SLEEP_T	unsigned int
#endif

SLEEP_T
E 39
E 34
sleep(intvl)
D 24
	int intvl;
E 24
I 24
	unsigned int intvl;
E 24
{
D 29
	extern endsleep();
E 29
I 29
D 38
	static int endsleep();
E 29

E 38
I 5
	if (intvl == 0)
D 47
		return;
E 47
I 47
		return (SLEEP_T) 0;
E 47
E 5
	SleepDone = FALSE;
D 13
	setevent(intvl, endsleep, 0);
E 13
I 13
D 16
	(void) setevent(intvl, endsleep, 0);
E 16
I 16
	(void) setevent((time_t) intvl, endsleep, 0);
E 16
E 13
	while (!SleepDone)
		pause();
I 47
	return (SLEEP_T) 0;
E 47
}

D 45
static
E 45
I 45
static void
E 45
endsleep()
{
	SleepDone = TRUE;
E 4
E 3
}
E 1
