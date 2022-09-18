h41357
s 00006/00007/00142
d D 8.5 94/05/29 00:05:09 mckusick 9 8
c cleanup final nits
e
s 00008/00008/00141
d D 8.4 94/05/26 22:30:49 bostic 8 7
c cleanups and edits for accuracy
e
s 00008/00003/00141
d D 8.3 94/05/20 06:06:55 karels 7 6
c touchups and improvements
e
s 00061/00028/00083
d D 8.2 94/05/16 10:09:33 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00109
d D 8.1 93/06/08 18:05:28 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00107
d D 6.3 91/04/17 10:01:55 bostic 4 3
c new copyright; att/bsd/shared
e
s 00007/00002/00103
d D 6.2 86/05/12 01:00:58 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00105
d D 6.1 86/05/08 12:26:30 mckusick 2 1
c format updates for 4.3BSD
e
s 00106/00000/00000
d D 5.1 86/05/08 00:02:50 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 5
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
D 7
.\" Copyright (c) 1983, 1993
E 7
I 7
.\" Copyright (c) 1983, 1993, 1994
E 7
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 6
.sh "Timers
.NH 3
Real time
E 6
I 6
.Sh 2 "Timers
.Sh 3 "Real time
E 6
.PP
D 7
The system's notion of the current Greenwich time and the current time
E 7
I 7
D 8
The system's notion of the current time in Coordinated Universal Time
E 8
I 8
The system's notion of the current time is in Coordinated Universal Time
E 8
(UTC, previously GMT) and the current time
E 7
D 8
zone is set and returned by the call by the calls:
E 8
I 8
zone is set and returned by the calls:
E 8
.DS
D 6
#include <sys/time.h>

E 6
I 6
.Fd settimeofday 2 "set date and time
E 6
D 8
settimeofday(tvp, tzp);
E 8
I 8
settimeofday(tp, tzp);
E 8
struct timeval *tp;
struct timezone *tzp;
D 6

E 6
I 6
.DE
.DS
.Fd gettimeofday 2 "get date and time
E 6
gettimeofday(tp, tzp);
result struct timeval *tp;
result struct timezone *tzp;
.DE
D 3
where the structures are defined in <sys/time.h> as:
E 3
I 3
where the structures are defined in \fI<sys/time.h>\fP as:
E 3
.DS
D 6
._f
E 6
I 6
.TS
l s s s
l l l l.
E 6
struct timeval {
	long	tv_sec;	/* seconds since Jan 1, 1970 */
	long	tv_usec;	/* and microseconds */
};
D 6

E 6
I 6
.T&
l s s s
l l l l.
E 6
struct timezone {
	int	tz_minuteswest;	/* of Greenwich */
	int	tz_dsttime;	/* type of dst correction to apply */
};
I 6
.TE
E 6
.DE
I 7
D 9
This timezone information is present only for historical reasons
E 9
I 9
The timezone information is present only for historical reasons
E 9
and is unused by the current system.
.LP
E 7
I 3
The precision of the system clock is hardware dependent.
E 3
Earlier versions of UNIX contained only a 1-second resolution version
of this call, which remains as a library routine:
.DS
D 8
time(tvsec)
result long *tvsec;
E 8
I 8
time(tvsec);
result time_t *tvsec;
E 8
.DE
D 6
returning only the tv_sec field from the \fIgettimeofday\fP call.
.NH 3
Interval time
.PP
E 6
I 6
returning only the tv_sec field from the
.Fn gettimeofday
call.
.LP
The
.Fn adjtime
D 7
system calls allows for small changes in time without abrupt changes:
E 7
I 7
system calls allows for small changes in time without abrupt changes
by skewing the rate at which time advances:
E 7
.DS
.Fd adjtime 2 "synchronization of the system clock
adjtime(delta, olddelta);
struct timeval *delta; result struct timeval *olddelta;
.DE
.Sh 3 "Interval time
.LP
E 6
The system provides each process with three interval timers,
D 3
defined in <sys/time.h>:
E 3
I 3
defined in \fI<sys/time.h>\fP:
E 3
.DS
D 6
._d
#define	ITIMER_REAL	0	/* real time intervals */
#define	ITIMER_VIRTUAL	1	/* virtual time intervals */
#define	ITIMER_PROF	2	/* user and system virtual time */
E 6
I 6
.TS
l l.
ITIMER_REAL	/* real time intervals */
ITIMER_VIRTUAL	/* virtual time intervals */
ITIMER_PROF	/* user and system virtual time */
.TE
E 6
.DE
The ITIMER_REAL timer decrements
in real time.  It could be used by a library routine to
maintain a wakeup service queue.  A SIGALRM signal is delivered
when this timer expires.
.PP
The ITIMER_VIRTUAL timer decrements in process virtual time.
It runs only when the process is executing.  A SIGVTALRM signal
is delivered when it expires.
.PP
The ITIMER_PROF timer decrements both in process virtual time and when
the system is running on behalf of the process.
It is designed to be used by processes to statistically profile
their execution.
A SIGPROF signal is delivered when it expires.
D 6
.PP
E 6
I 6
.LP
E 6
A timer value is defined by the \fIitimerval\fP structure:
.DS
D 6
._f
E 6
I 6
.TS
l s s s
l l l l.
E 6
struct itimerval {
	struct	timeval it_interval;	/* timer interval */
	struct	timeval it_value;	/* current value */
};
I 6
.TE
E 6
.DE
and a timer is set or read by the call:
.DS
D 6
getitimer(which, value);
int which; result struct itimerval *value;

E 6
I 6
.Fd setitimer 3 "set value of interval timer
E 6
setitimer(which, value, ovalue);
int which; struct itimerval *value; result struct itimerval *ovalue;
.DE
D 6
The third argument to \fIsetitimer\fP specifies an optional structure
E 6
I 6
.DS
.Fd getitimer 2 "get value of interval timer
getitimer(which, value);
int which; result struct itimerval *value;
.DE
The \fIit_value\fP specifies the time until the next signal;
D 8
the \fIit_interval\fP specified a new interval that should
E 8
I 8
the \fIit_interval\fP specifies a new interval that should
E 8
be loaded into the timer on each expiration.
The third argument to
.Fn setitimer
specifies an optional structure
E 6
to receive the previous contents of the interval timer.
D 8
A timer can be disabled by specifying a timer value of 0.
E 8
I 8
A timer can be disabled by setting \fIit_value\fP and \fIit_interval\fP to 0.
E 8
.PP
The system rounds argument timer intervals to be not less than the
resolution of its clock.  This clock resolution can be determined
by loading a very small value into a timer and reading the timer back to
see what value resulted.
.PP
D 6
The \fIalarm\fP system call of earlier versions of UNIX is provided
E 6
I 6
The
.Fn alarm
system call of earlier versions of UNIX is provided
E 6
D 9
as a library routine using the ITIMER_REAL timer.  The process
profiling facilities of earlier versions of UNIX
remain because
it is not always possible to guarantee
the automatic restart of system calls after 
receipt of a signal.
E 9
I 9
as a library routine using the ITIMER_REAL timer.
.PP
The process profiling facilities of earlier versions of UNIX
remain because it is not always possible to guarantee
the automatic restart of system calls after receipt of a signal.
E 9
I 3
D 6
The \fIprofil\fP call arranges for the kernel to begin gathering
E 6
I 6
The
.Fn profil
call arranges for the kernel to begin gathering
E 6
execution statistics for a process:
E 3
.DS
D 6
profil(buf, bufsize, offset, scale);
result char *buf; int bufsize, offset, scale;
E 6
I 6
.Fd profil 4 "control process profiling
profil(samples, size, offset, scale);
result char *samples; int size, offset, scale;
E 6
.DE
I 3
D 6
This begins sampling of the program counter, with statistics maintained
in the user-provided buffer.
E 6
I 6
D 8
This call begins sampling of the program counter,
E 8
I 8
This call begins sampling the program counter,
E 8
with statistics maintained in the user-provided buffer.
E 6
E 3
E 1
