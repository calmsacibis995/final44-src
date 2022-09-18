h24051
s 00001/00000/00132
d D 8.5 94/06/01 18:16:34 ah 9 8
c page breaks for the 4.4BSD manuals
e
s 00003/00003/00129
d D 8.4 94/05/26 22:30:54 bostic 8 7
c cleanups and edits for accuracy
e
s 00006/00003/00126
d D 8.3 94/05/20 06:06:57 karels 7 6
c touchups and improvements
e
s 00067/00047/00062
d D 8.2 94/05/16 10:09:39 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00107
d D 8.1 93/06/08 18:05:38 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00105
d D 6.3 91/04/17 10:01:58 bostic 4 3
c new copyright; att/bsd/shared
e
s 00006/00006/00102
d D 6.2 86/05/12 01:01:09 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00108
d D 6.1 86/05/08 12:26:41 mckusick 2 1
c format updates for 4.3BSD
e
s 00109/00000/00000
d D 5.1 86/05/08 00:03:04 mckusick 1 0
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
.sh "Resource controls
.NH 3
Process priorities
E 6
I 6
.Sh 2 "Resource controls
.Sh 3 "Process priorities
E 6
.PP
The system gives CPU scheduling priority to processes that have not used
CPU time recently.  This tends to favor interactive processes and
processes that execute only for short periods.
D 7
It is possible to determine the priority currently
E 7
I 7
The instantaneous scheduling priority is a function of CPU usage
and a settable priority value used in adjusting the instantaneous
priority with CPU usage or inactivity.
It is possible to determine the settable priority factor currently
E 7
D 6
assigned to a process, process group, or the processes of a specified user,
E 6
I 6
assigned to a process (PRIO_PROCESS),
process group (PRIO_PGRP),
or the processes of a specified user (PRIO_USER),
E 6
or to alter this priority using the calls:
.DS
D 6
._d
#define	PRIO_PROCESS	0	/* process */
#define	PRIO_PGRP	1	/* process group */
#define	PRIO_USER	2	/* user id */

E 6
I 6
.Fd getpriority 2 "get program scheduling priority
E 6
prio = getpriority(which, who);
result int prio; int which, who;
D 6

E 6
I 6
.DE
.DS
.Fd setpriority 3 "set program scheduling priority
E 6
setpriority(which, who, prio);
int which, who, prio;
.DE
The value \fIprio\fP is in the range \-20 to 20.
The default priority is 0; lower priorities cause more
favorable execution.
D 6
The \fIgetpriority\fP call returns the highest priority (lowest numerical value)
E 6
I 6
The
.Fn getpriority
call returns the highest priority (lowest numerical value)
E 6
enjoyed by any of the specified processes.
D 6
The \fIsetpriority\fP call sets the priorities of all of the
E 6
I 6
The
.Fn setpriority
call sets the priorities of all the
E 6
specified processes to the specified value.
Only the super-user may lower priorities.
D 6
.NH 3
Resource utilization
E 6
I 6
.Sh 3 "Resource utilization
E 6
.PP
D 6
The resources used by a process are returned by a \fIgetrusage\fP call,
D 3
returning information in a structure defined in <sys/resource.h>:
E 3
I 3
returning information in a structure defined in \fI<sys/resource.h>\fP:
E 6
I 6
The
.Fn getrusage
call returns information describing the resources utilized by the
current process (RUSAGE_SELF),
D 7
or all its terminated child processes (RUSAGE_CHILDREN):
E 7
I 7
or all its terminated descendent processes (RUSAGE_CHILDREN):
E 7
E 6
E 3
.DS
D 6
._d
#define	RUSAGE_SELF	0		/* usage by this process */
#define	RUSAGE_CHILDREN	-1		/* usage by all children */

E 6
I 6
.Fd getrusage 2 "get information about resource utilization
E 6
D 8
getrusage(who, rusage)
E 8
I 8
getrusage(who, rusage);
E 8
int who; result struct rusage *rusage;
D 6

._f
E 6
I 6
.DE
The information is returned in a structure defined in \fI<sys/resource.h>\fP:
.DS
.TS
l s s s
l l l l.
E 6
struct rusage {
	struct	timeval ru_utime;	/* user time used */
	struct	timeval ru_stime;	/* system time used */
	int	ru_maxrss;	/* maximum core resident set size: kbytes */
	int	ru_ixrss;	/* integral shared memory size (kbytes*sec) */
D 3
	int	ru_idrss;	/* unshared data " */
	int	ru_isrss;	/* unshared stack " */
E 3
I 3
	int	ru_idrss;	/* unshared data memory size */
	int	ru_isrss;	/* unshared stack memory size */
E 3
	int	ru_minflt;	/* page-reclaims */
	int	ru_majflt;	/* page faults */
	int	ru_nswap;	/* swaps */
	int	ru_inblock;	/* block input operations */
D 3
	int	ru_oublock;	/* block output " */
E 3
I 3
	int	ru_oublock;	/* block output operations */
E 3
	int	ru_msgsnd;	/* messages sent */
	int	ru_msgrcv;	/* messages received */
	int	ru_nsignals;	/* signals received */
	int	ru_nvcsw;	/* voluntary context switches */
D 3
	int	ru_nivcsw;	/* involuntary " */
E 3
I 3
	int	ru_nivcsw;	/* involuntary context switches */
E 3
};
I 6
.TE
E 6
.DE
D 6
The \fIwho\fP parameter specifies whose resource usage is to be returned.
The resources used by the current process, or by all
the terminated children of the current process may be requested.
.NH 3
Resource limits
E 6
I 6
.Sh 3 "Resource limits
E 6
.PP
The resources of a process for which limits are controlled by the
D 3
kernel are defined in <sys/resource.h>, and controlled by the
E 3
I 3
kernel are defined in \fI<sys/resource.h>\fP, and controlled by the
E 3
D 6
\fIgetrlimit\fP and \fIsetrlimit\fP calls:
E 6
I 6
.Fn getrlimit
and
.Fn setrlimit
calls:
E 6
.DS
D 6
._d
#define	RLIMIT_CPU	0	/* cpu time in milliseconds */
#define	RLIMIT_FSIZE	1	/* maximum file size */
#define	RLIMIT_DATA	2	/* maximum data segment size */
#define	RLIMIT_STACK	3	/* maximum stack segment size */
#define	RLIMIT_CORE	4	/* maximum core file size */
#define	RLIMIT_RSS	5	/* maximum resident set size */

#define	RLIM_NLIMITS	6

#define	RLIM_INFINITY	0x7f\&f\&f\&f\&f\&f\&f

._f
struct rlimit {
	int	rlim_cur;	/* current (soft) limit */
	int	rlim_max;	/* hard limit */
};

E 6
I 6
.Fd getrlimit 2 "get maximum system resource consumption
E 6
D 8
getrlimit(resource, rlp)
E 8
I 8
getrlimit(resource, rlp);
E 8
int resource; result struct rlimit *rlp;
D 6

E 6
I 6
.DE
.DS
.Fd setrlimit 2 "set maximum system resource consumption
E 6
D 8
setrlimit(resource, rlp)
E 8
I 8
setrlimit(resource, rlp);
E 8
int resource; struct rlimit *rlp;
.DE
I 6
The resources that may currently be controlled include:
.DS
.TS
l l.
RLIMIT_CPU	/* cpu time in milliseconds */
RLIMIT_FSIZE	/* maximum file size */
RLIMIT_DATA	/* data size */
RLIMIT_STACK	/* stack size */
RLIMIT_CORE	/* core file size */
RLIMIT_RSS	/* resident set size */
RLIMIT_MEMLOCK	/* locked-in-memory address space */
RLIMIT_NPROC	/* number of processes */
RLIMIT_NOFILE	/* number of open files */
.TE
.DE
I 9
.ne 1i
E 9
Each limit has a current value and a maximum defined
by the \fIrlimit\fP structure:
.DS
.TS
l s s s
l l l l.
struct rlimit {
	quad_t	rlim_cur;	/* current (soft) limit */
	quad_t	rlim_max;	/* hard limit */
};
.TE
.DE
E 6
.PP
Only the super-user can raise the maximum limits.
Other users may only
alter \fIrlim_cur\fP within the range from 0 to \fIrlim_max\fP
or (irreversibly) lower \fIrlim_max\fP.
I 6
To remove a limit on a resource,
the value is set to RLIM_INFINITY.
E 6
E 1
