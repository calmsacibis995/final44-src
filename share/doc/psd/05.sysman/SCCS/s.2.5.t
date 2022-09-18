h49003
s 00001/00004/00069
d D 8.6 94/05/29 00:05:17 mckusick 10 9
c cleanup final nits
e
s 00000/00003/00073
d D 8.5 94/05/26 23:02:40 mckusick 9 8
c incorporate comments from Mike Hibler
e
s 00010/00009/00066
d D 8.4 94/05/26 22:31:00 bostic 8 7
c cleanups and edits for accuracy
e
s 00001/00001/00074
d D 8.3 94/05/20 06:07:06 karels 7 6
c touchups and improvements
e
s 00067/00005/00008
d D 8.2 94/05/16 10:09:44 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00011
d D 8.1 93/06/08 18:06:25 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00009
d D 6.3 91/04/17 10:02:04 bostic 4 3
c new copyright; att/bsd/shared
e
s 00003/00002/00009
d D 6.2 86/05/12 01:01:47 karels 3 2
c update, correct, rephrase and re-propose
e
s 00001/00002/00010
d D 6.1 86/05/08 12:27:12 mckusick 2 1
c format updates for 4.3BSD
e
s 00012/00000/00000
d D 5.1 86/05/08 00:03:58 mckusick 1 0
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
D 8
.\" Copyright (c) 1983, 1993
E 8
I 8
.\" Copyright (c) 1983, 1993, 1994
E 8
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
.sh "Process and kernel descriptors
E 6
I 6
.Sh 2 "Process debugging
.Sh 3 "Traditional debugging
.LP
D 7
Debugger traditionally use the
E 7
I 7
Debuggers traditionally use the
E 7
.Fn ptrace
interface:
.DS
.Fd ptrace 4 "process trace
ptrace(request, pid, addr, data);
int request, pid, *addr, data;
.DE
This interface provides a means by which a parent process may
control the execution of a child process,
and examine and change its core image.
Its primary use is for the implementation of breakpoint debugging.
There are four arguments whose interpretation
depends on a request argument.
D 9
Generally, pid is the process ID of the traced process,
which must be a child (no more distant descendant)
of the tracing process.
E 9
A process being traced behaves normally until it
D 8
encounters some signal whether internally generated like
E 8
I 8
encounters a signal (whether internally generated like
E 8
``illegal instruction'' or externally generated
D 8
like ``interrupt.''
E 8
I 8
like ``interrupt'').
E 8
Then the traced process enters a stopped state
and its parent is notified via
.Fn wait .
When the child is in the stopped state,
its core image can be examined and modified using
.Fn ptrace .
D 8
If desired, another ptrace request can then cause
the child either to terminate or to continue,
possibly ignoring the signal.
E 8
I 8
Another ptrace request can then cause the child either to terminate
or to continue, possibly ignoring the signal.
E 8
E 6
.PP
D 6
The status of the facilities in this section is still under discussion.
D 2
The \fIptrace\fP facility of 4.1BSD is provided in 4.2BSD.  Planned
E 2
I 2
D 3
The \fIptrace\fP facility of 4.1BSD is provided in 4.3BSD.  Planned
E 2
enhancements would allow a descriptor based process control facility.
E 3
I 3
The \fIptrace\fP facility of earlier UNIX systems
remains in 4.3BSD.
Planned enhancements would allow a descriptor-based process control facility.
E 6
I 6
A more general interface is also provided in 4.4BSD;
the \fImount_procfs\fP filesystem attaches an instance of
the process name space to the global filesystem name space.
The conventional mount point is \fI/proc\fP.
D 8
The root of the process filesystem contains an entry for each active process.
These processes are visible as a directory whose name is the process' pid.
In addition, the special entry curproc references the current process.
E 8
I 8
The root of the process filesystem contains an entry for each active
process.
These processes are visible as directories named by the process' ID.
In addition, the special entry \fIcurproc\fP references the current
process.
E 8
Each directory contains several files, including a \fIctl\fP file.
The debugger finds (or creates) the process that it wants to
debug and then issues an attach command via the \fIctl\fP file.
Further interaction can then be done with the process through
the other files provided by the \fI/proc\fP filesystem.
D 10
This interface has the benefit of being able to debug
arbitrary processes on the system rather than just processes
started by the debugger.
E 10
.Sh 3 "Kernel tracing
.LP
Another facility for debugging programs is provided by the
.Fn ktrace
interface:
.DS
.Fd ktrace 4 "process tracing
ktrace(tracefile, ops, trpoints, pid);
char *tracefile; int ops, trpoints, pid;
.DE
.Fn Ktrace
does kernel trace logging for the specified processes.
The kernel operations that are traced include system calls,
pathname translations, signal processing, and I/O.
D 10
This facility can be particularly useful for debugging
E 10
I 10
This facility can be particularly useful to debug
E 10
programs for which you do not have the source.
.\"
.\" We currently do not document the vtrace call
.\" .Fd vtrace 2
E 6
E 3
E 1
