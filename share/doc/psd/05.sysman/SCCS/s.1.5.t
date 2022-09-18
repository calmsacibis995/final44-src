h53363
s 00006/00002/00234
d D 8.6 94/05/29 00:05:10 mckusick 11 10
c cleanup final nits
e
s 00028/00019/00208
d D 8.5 94/05/26 22:30:50 bostic 10 9
c cleanups and edits for accuracy
e
s 00001/00001/00226
d D 8.4 94/05/20 10:48:15 mckusick 9 8
c fix moved cross reference
e
s 00014/00004/00213
d D 8.3 94/05/20 06:06:56 karels 8 7
c touchups and improvements
e
s 00101/00083/00116
d D 8.2 94/05/16 10:09:33 mckusick 7 6
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00197
d D 8.1 93/06/08 18:05:33 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00195
d D 6.4 91/04/17 10:01:56 bostic 5 4
c new copyright; att/bsd/shared
e
s 00003/00003/00195
d D 6.3 86/05/12 01:23:16 karels 4 3
c spelling
e
s 00028/00013/00170
d D 6.2 86/05/12 01:01:02 karels 3 2
c update, correct, rephrase and re-propose
e
s 00001/00002/00182
d D 6.1 86/05/08 12:26:34 mckusick 2 1
c format updates for 4.3BSD
e
s 00184/00000/00000
d D 5.1 86/05/08 00:02:56 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 6
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
D 8
.\" Copyright (c) 1983, 1993
E 8
I 8
.\" Copyright (c) 1983, 1993, 1994
E 8
.\"	The Regents of the University of California.  All rights reserved.
E 6
.\"
.\" %sccs.include.redist.roff%
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 7
.sh Descriptors
E 7
I 7
.Sh 2 Descriptors
.Sh 3 "The reference table
E 7
.PP
D 7
.NH 3
The reference table
.PP
E 7
Each process has access to resources through
\fIdescriptors\fP.  Each descriptor is a handle allowing
D 10
the process to reference objects such as files, devices
E 10
I 10
processes to reference objects such as files, devices
E 10
and communications links.
.PP
Rather than allowing processes direct access to descriptors, the system
introduces a level of indirection, so that descriptors may be shared
between processes.  Each process has a \fIdescriptor reference table\fP,
D 10
containing pointers to the actual descriptors.  The descriptors
themselves thus have multiple references, and are reference counted by the
system.
E 10
I 10
containing pointers to the actual descriptors.
The descriptors themselves therefore may have multiple references,
and are reference counted by the system.
E 10
.PP
D 7
Each process has a fixed size descriptor reference table, where
the size is returned by the \fIgetdtablesize\fP call:
E 7
I 7
Each process has a limited size descriptor reference table, where
D 8
the size is returned by the
E 8
I 8
the current size is returned by the
E 8
.Fn getdtablesize
call:
E 7
.DS
I 7
.Fd getdtablesize 0 "get descriptor table size
E 7
nds = getdtablesize();
result int nds;
.DE
D 7
and guaranteed to be at least 20.  The entries in the descriptor reference
E 7
I 7
D 10
and guaranteed to be at least 20.
E 10
I 10
and guaranteed to be at least 64.
E 10
The maximum number of descriptors is a resource limit (see section
.Xr 1.6.3 ).
The entries in the descriptor reference
E 7
table are referred to by small integers; for example if there
D 11
are 20 slots they are numbered 0 to 19.
E 11
I 11
are 64 slots they are numbered 0 to 63.
E 11
D 7
.NH 3
Descriptor properties
E 7
I 7
.Sh 3 "Descriptor properties
E 7
.PP
Each descriptor has a logical set of properties maintained
by the system and defined by its \fItype\fP.
Each type supports a set of operations;
some operations, such as reading and writing, are common to several
abstractions, while others are unique.
I 8
For those types that support random access, the current file offset
is stored in the descriptor.
E 8
The generic operations applying to many of these types are described
D 7
in section 2.1.  Naming contexts, files and directories are described in
section 2.2.  Section 2.3 describes communications domains and sockets.
Terminals and (structured and unstructured) devices are described
in section 2.4.
.NH 3
Managing descriptor references
.PP
A duplicate of a descriptor reference may be made by doing
E 7
I 7
in section
.Xr 2.1 .
Naming contexts, files and directories are described in section
.Xr 2.2 .
Section
.Xr 2.3
describes communications domains and sockets.
Terminals and (structured and unstructured) devices are described in section
.Xr 2.4 .
.Sh 3 "Managing descriptor references
.LP
A duplicate of a descriptor reference may be made by doing:
E 7
.DS
I 7
.Fd dup 1 "duplicate an existing file descriptor
E 7
new = dup(old);
result int new; int old;
.DE
D 10
returning a copy of descriptor reference \fIold\fP indistinguishable from
the original.  The \fInew\fP chosen by the system will be the
E 10
I 10
returning a copy of descriptor reference \fIold\fP which is
indistinguishable from the original.
The value of \fInew\fP chosen by the system will be the
E 10
smallest unused descriptor reference slot.
A copy of a descriptor reference may be made in a specific slot
D 7
by doing
E 7
I 7
by doing:
E 7
.DS
I 7
.Fd dup2 2 "duplicate an existing file descriptor
E 7
dup2(old, new);
int old, new;
.DE
D 7
The \fIdup2\fP call causes the system to deallocate the descriptor reference
E 7
I 7
The
.Fn dup2
call causes the system to deallocate the descriptor reference
E 7
current occupying slot \fInew\fP, if any, replacing it with a reference
to the same descriptor as old.
D 7
This deallocation is also performed by:
E 7
I 7
D 8
This deallocation is also done by:
E 8
I 8
.LP
Descriptors are deallocated by:
E 8
E 7
.DS
I 7
.Fd close 1 "delete a descriptor
E 7
close(old);
int old;
.DE
D 7
.NH 3
Multiplexing requests
E 7
I 7
.Sh 3 "Multiplexing requests
E 7
.PP
The system provides a
standard way to do
synchronous and asynchronous multiplexing of operations.
D 7
.PP
D 3
Synchronous multiplexing is performed by using the \fIselect\fP call:
E 3
I 3
Synchronous multiplexing is performed by using the \fIselect\fP call
to examine the state of multiple descriptors simultaneously,
E 7
I 7
Synchronous multiplexing is performed by using the
.Fn select
call to examine the state of multiple descriptors simultaneously,
E 7
and to wait for state changes on those descriptors.
Sets of descriptors of interest are specified as bit masks,
as follows:
E 3
.DS
I 3
D 7
#include <sys/types.h>

E 7
I 7
.Fd select 5 "synchronous I/O multiplexing
E 7
E 3
nds = select(nd, in, out, except, tvp);
D 3
result int nds; int nd; result *in, *out, *except;
E 3
I 3
result int nds; int nd; result fd_set *in, *out, *except;
E 3
struct timeval *tvp;
I 3

D 10
FD_ZERO(&fdset);
FD_SET(fd, &fdset);
E 10
FD_CLR(fd, &fdset);
I 10
FD_COPY(&fdset, &fdset2);
E 10
FD_ISSET(fd, &fdset);
D 7
int fs; fs_set fdset;
E 7
I 7
D 10
int fd; fs_set fdset;
E 10
I 10
FD_SET(fd, &fdset);
FD_ZERO(&fdset);
int fd; fs_set fdset, fdset2;
E 10
E 7
E 3
.DE
D 7
The \fIselect\fP call examines the descriptors
specified by the
E 7
I 7
The
.Fn select
call examines the descriptors specified by the
E 7
sets \fIin\fP, \fIout\fP and \fIexcept\fP, replacing
D 3
the specified bit masks by the subsets that select for input,
E 3
I 3
the specified bit masks by the subsets that select true for input,
E 3
output, and exceptional conditions respectively (\fInd\fP
D 3
indicates the size, in bytes, of the bit masks).
E 3
I 3
indicates the number of file descriptors specified by the bit masks).
E 3
If any descriptors meet the following criteria,
then the number of such descriptors is returned in \fInds\fP and the
bit masks are updated.
.if n .ds bu *
.if t .ds bu \(bu
.IP \*(bu
A descriptor selects for input if an input oriented operation
D 7
such as \fIread\fP or \fIreceive\fP is possible, or if a
connection request may be accepted (see section 2.3.1.4).
E 7
I 7
such as
.Fn read
or
.Fn receive
D 10
is possible, or if a connection request may be accepted (see section
E 10
I 10
is possible, or if a connection request may be accepted (see sections
.Xr 2.1.3
and
E 10
.Xr 2.3.1.4 ).
E 7
.IP \*(bu
A descriptor selects for output if an output oriented operation
D 7
such as \fIwrite\fP or \fIsend\fP is possible, or if an operation
E 7
I 7
such as
.Fn write
or
.Fn send
is possible, or if an operation
E 7
that was ``in progress'', such as connection establishment,
D 7
has completed (see section 2.1.3).
E 7
I 7
D 10
has completed (see section
.Xr 2.1.3 ).
E 10
I 10
has completed (see sections
.Xr 2.1.3
and
.Xr 2.3.1.5 ).
E 10
E 7
.IP \*(bu
A descriptor selects for an exceptional condition if a condition
D 3
that would cause a SIGURG signal to be generated exists (see section 1.3.2).
E 3
I 3
D 7
that would cause a SIGURG signal to be generated exists (see section 1.3.2),
E 7
I 7
that would cause a SIGURG signal to be generated exists (see section
.Xr 1.3.2 ),
E 7
or other device-specific events have occurred.
E 3
.LP
I 8
For these tests, an operation is considered to be possible if a call
D 10
to the operation would return without blocking even if the O_NONBLOCK
flag were clear.
E 10
I 10
to the operation would return without blocking (even if the O_NONBLOCK
flag were not set).
E 10
For example, a descriptor would test as ready for reading if a read
call would return immediately with data, an end-of-file indication,
or an error other than EWOULDBLOCK.
.LP
E 8
D 3
If none of the specified conditions is true, the operation blocks for
at most the amount of time specified by \fItvp\fP, or waits for one of the
conditions to arise if \fItvp\fP is given as 0.
E 3
I 3
If none of the specified conditions is true, the operation
waits for one of the conditions to arise,
blocking at most the amount of time specified by \fItvp\fP.
D 7
If \fItvp\fP is given as 0, the \fIselect\fP waits indefinitely.
E 3
.PP
E 7
I 7
D 8
If \fItvp\fP is given as 0, the
E 8
I 8
If \fItvp\fP is given as NULL, the
E 8
.Fn select
waits indefinitely.
.LP
E 7
D 3
Options affecting i/o on a descriptor
E 3
I 3
Options affecting I/O on a descriptor
E 3
may be read and set by the call:
.DS
D 7
._d
E 7
I 7
.Fd fcntl 3 "file control
E 7
D 10
dopt = fcntl(d, cmd, arg)
E 10
I 10
dopt = fcntl(d, cmd, arg);
E 10
result int dopt; int d, cmd, arg;
D 7

/* interesting values for cmd */
#define	F_SETFL	3	/* set descriptor options */
#define	F_GETFL	4	/* get descriptor options */
#define	F_SETOWN	5	/* set descriptor owner (pid/pgrp) */
#define	F_GETOWN	6	/* get descriptor owner (pid/pgrp) */
E 7
.DE
I 7
.DS
.TS
l s
l l.
/* command values */
I 11

E 11
I 10
F_DUPFD	/* return a new descriptor */
E 10
F_GETFD	/* get file descriptor flags */
F_SETFD	/* set file descriptor flags */
F_GETFL	/* get file status flags */
F_SETFL	/* set file status flags */
F_GETOWN	/* get SIGIO/SIGURG proc/pgrp */
F_SETOWN	/* set SIGIO/SIGURG proc/pgrp */
I 10
F_GETLK	/* get blocking lock */
F_SETLK	/* set or clear lock */
F_SETLKW	/* set lock with wait */
E 10
.TE
.DE
I 11
The F_DUPFD \fIcmd\fP provides identical functionality to
.Fn dup2 ;
it is provided solely for POSIX compatibility.
E 11
The F_SETFD \fIcmd\fP can be used to set the close-on-exec
flag for a file descriptor.
E 7
The F_SETFL \fIcmd\fP may be used to set a descriptor in 
D 3
non-blocking i/o mode and/or enable signalling when i/o is
E 3
I 3
D 4
non-blocking I/O mode and/or enable signalling when I/O is
E 4
I 4
D 7
non-blocking I/O mode and/or enable signaling when I/O is
E 4
E 3
possible.  F_SETOWN may be used to specify a process or process
E 7
I 7
non-blocking I/O mode and/or enable signaling when I/O is possible.
F_SETOWN may be used to specify a process or process
E 7
D 3
group to be signalled when using the latter mode of operation.
E 3
I 3
D 4
group to be signalled when using the latter mode of operation
E 4
I 4
group to be signaled when using the latter mode of operation
E 4
or when urgent indications arise.
I 7
The
.Fn fcntl
system call also provides POSIX-compliant byte-range locking on files.
However the semantics of unlocking on every 
.Fn close
D 10
rather than last close makes them almost useless.
Much better semantics, and faster locking are provided
by the
E 10
I 10
rather than last close makes them useless.
Much better semantics and faster locking are provided by the
E 10
.Fn flock
system call (see section
D 9
.Xr 2.2.8 ).
E 9
I 9
.Xr 2.2.7 ).
E 9
The
.Fn fcntl
and
.Fn flock
locks can be used concurrently;
they will serialize against each other properly.
E 7
E 3
.PP
Operations on non-blocking descriptors will
either complete immediately,
D 11
note an error EWOULDBLOCK,
E 11
I 11
return the error EWOULDBLOCK,
E 11
partially complete an input or output operation returning a partial count,
or return an error EINPROGRESS noting that the requested operation is
in progress.
A descriptor which has signalling enabled will cause the specified process
and/or process group
be signaled, with a SIGIO for input, output, or in-progress
operation complete, or
a SIGURG for exceptional conditions.
.PP
For example, when writing to a terminal
using non-blocking output,
D 7
the system will accept only as much data as there is buffer space for
and return; when making a connection on a \fIsocket\fP, the operation may
E 7
I 7
the system will accept only as much data as there is buffer space,
then return.
When making a connection on a \fIsocket\fP, the operation may
E 7
return indicating that the connection establishment is ``in progress''.
D 7
The \fIselect\fP facility can be used to determine when further
E 7
I 7
The
.Fn select
facility can be used to determine when further
E 7
output is possible on the terminal, or when the connection establishment
attempt is complete.
D 7
.NH 3
Descriptor wrapping.\(dg
.PP
.FS
\(dg The facilities described in this section are not included
D 2
in 4.2BSD.
E 2
I 2
in 4.3BSD.
E 2
.FE
A user process may build descriptors of a specified type by
\fIwrapping\fP a communications channel with a system supplied protocol
translator:
.DS
new = wrap(old, proto)
result int new; int old; struct dprop *proto;
.DE
Operations on the descriptor \fIold\fP are then translated by the
D 4
system provided protocol translator into requests on the underyling
E 4
I 4
system provided protocol translator into requests on the underlying
E 4
object \fIold\fP in a way defined by the protocol.
The protocols supported by the kernel may vary from system to system
and are described in the programmers manual.
.PP
Protocols may be based on communications multiplexing or a rights-passing
style of handling multiple requests made on the same object.  For instance,
a protocol for implementing a file abstraction may or may not include
locally generated ``read-ahead'' requests.  A protocol that provides for
read-ahead may provide higher performance but have a more difficult
implementation.
.PP
Another example is the terminal driving facilities.  Normally a terminal
D 3
is associated with a communications line and the terminal type
and standard terminal access protocol is wrapped around a synchronous
E 3
I 3
is associated with a communications line, and the terminal type
and standard terminal access protocol are wrapped around a synchronous
E 3
communications line and given to the user.  If a virtual terminal
is required, the terminal driver can be wrapped around a communications
link, the other end of which is held by a virtual terminal protocol
interpreter.
E 7
E 1
