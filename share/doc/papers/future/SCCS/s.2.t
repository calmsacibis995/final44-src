h59857
s 00007/00001/00151
d D 5.1 91/04/16 17:49:34 bostic 6 5
c new copyright; att/bsd/shared
e
s 00006/00009/00146
d D 1.5 86/12/04 18:20:26 mckusick 5 4
c minor edits
e
s 00027/00013/00128
d D 1.4 86/12/04 16:56:02 karels 4 3
c changes
e
s 00078/00073/00063
d D 1.3 86/12/04 15:44:52 mckusick 3 2
c edits from Mark Compton
e
s 00010/00010/00126
d D 1.2 86/11/29 09:22:47 mckusick 2 1
c first draft edits
e
s 00136/00000/00000
d D 1.1 86/11/25 23:22:42 mckusick 1 0
c date and time created 86/11/25 23:22:42 by mckusick
e
u
U
t
T
I 1
D 6
.\"	%W%	(Copyright 1986 M. K. McKusick)	%E%
E 6
I 6
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 6
D 2
.SH
E 2
I 2
.NH
E 2
The Future of UNIX at Berkeley
.PP
The release of 4.3BSD in April of 1986 addressed many of the 
D 3
performance problems and unfinished interfaces that were
E 3
I 3
performance problems and unfinished interfaces
E 3
present in 4.2BSD [Leffler84] [McKusick85].
D 2
We are now embarking on a new development phase to update older
E 2
I 2
D 3
Berkeley is now embarking on a new development phase to update older
E 2
parts of the system to the current state of the art.
E 3
I 3
Berkeley has now embarked on a new development phase to likewise
update other old parts of the system.
E 3
There are three main areas of work.
The first is to rewrite the virtual memory system to take
advantage of current technology and to provide new capabilities
such as mapped files and shared memory.
The second is to provide a standard interface to file systems
D 3
to allow multiple local and remote file systems much the way
multiple networking protocols are supported in 4.3BSD.
D 2
Finally we want to provide more internal flexibility in a
E 2
I 2
Finally there is a need to provide more internal flexibility in a
E 2
way similar to the streams paradigm in System V.
E 3
I 3
so that multiple local and remote file systems can be supported
much as multiple networking protocols are by 4.3BSD.
Finally, there is a need to provide more internal flexibility in a
way similar to the System V Streams paradigm.
E 3
D 2
.SH 2
E 2
I 2
.NH 2
E 2
A New Virtual Memory Implementation
.PP
With the cost per byte of memory approaching that of the cost per byte
D 3
for disks, and with file systems increasingly distant from the host
E 3
I 3
for disks, and with file systems increasingly removed from host
E 3
machines, a new approach to the implementation of virtual memory is
D 2
necessary. In 4.3BSD the swap space is preallocated which limits the
maximum virtual memory that can be supported to the size of the swap
area [Babaoglu79] [Someren84].
E 2
I 2
necessary. In 4.3BSD the swap space is preallocated;
D 3
this preallocation limits the maximum virtual memory that can be
E 3
I 3
this limits the maximum virtual memory that can be
E 3
supported to the size of the swap area [Babaoglu79] [Someren84].
E 2
D 3
The new system should support virtual memory up to the sum of the
sizes of physical memory plus swap space (a system may run with no swap
space if it has no local disk). For systems with a local swap
disk, but remote file systems, it may be useful to use some of the memory
to keep track of the contents of the swap space to avoid multiple fetches
E 3
I 3
The new system should support virtual memory space at least as great as
the sum of sizes of physical memory plus swap space
(a system may run with no swap space if it has no local disk).
For systems that have a local swap
disk, but utilize remote file systems,
using some memory to keep track of the contents of swap space
may be useful to avoid multiple fetches
E 3
of the same data from the file system.
.PP
The new implementation should also add new functionality.  Processes
should be allowed to have large sparse address spaces, to map files
into their address spaces, to map device memory into their address
spaces, and to share memory with other processes. The shared address
space may either be obtained by mapping a file into (possibly
D 3
different) parts of their address space, or by arranging to share
``anonymous memory'' (that is, memory that is zero fill on demand, and
whose contents are lost when the last process unmaps the memory) with
another process as is done in System V.
E 3
I 3
different) parts of the address space, or by arranging for processes to
share ``anonymous memory'' (that is, memory that is zero-fill on demand, and
whose contents are lost when the last process unmaps the memory).
This latter approach was the one adopted by the developers of System V.
E 3
.PP
D 3
One use of shared memory is to provide a high-speed
E 3
I 3
One possible use of shared memory is to provide a high-speed
E 3
Inter-Process Communication (IPC) mechanism between two or more
cooperating processes. To insure the integrity of data structures
in a shared region, processes must be able to use semaphores to
coordinate their access to these shared structures. In System V,
D 3
these semaphores are provided as a set of system calls. Unfortunately,
E 3
I 3
semaphores are provided as a set of system calls. Unfortunately,
E 3
the use of system calls reduces the throughput of the shared memory
D 3
IPC to that of existing IPC mechanisms.  We are proposing a scheme
E 3
I 3
IPC to that of existing IPC mechanisms.
To avoid this bottleneck,
we expect that the next release of BSD will incorporate a scheme
E 3
that places the semaphores in the shared memory segment, so that
D 3
machines that have a test-and-set instruction can handle the usual
uncontested lock and unlock without doing a system call. Only in
the unusual case of trying to lock an already-locked lock or in
releasing a wanted lock will a system call be required.  The
E 3
I 3
machines with a test-and-set instruction will be able to handle the usual
uncontested ``lock'' and ``unlock'' without doing two system calls.
Only in the unusual case of trying to lock an already-locked lock or when
a desired lock is being released will a system call be required.  The
E 3
interface will allow a user-level implementation of the System V semaphore
interface on most machines with a much lower runtime cost [McKusick86].
D 2
.SH 2
E 2
I 2
.NH 2
E 2
D 3
Toward a Compatible Filesystem Interface
E 3
I 3
Toward a Compatible File System Interface
E 3
.PP
D 3
As network or remote filesystems have been implemented for UNIX,
several stylized interfaces between the filesystem implementation
E 3
I 3
As network or remote file systems have been implemented for UNIX,
several stylized interfaces between the file system implementation
E 3
and the rest of the kernel have been developed.
D 3
Among these are Sun Microsystems' Virtual Filesystem interface (VFS)
using vnodes [Sandburg85] [Kleiman86],
E 3
I 3
Among these are Sun Microsystems' Virtual File System interface (VFS)
using \fBvnodes\fP [Sandburg85] [Kleiman86],
E 3
Digital Equipment's Generic File System (GFS) architecture [Rodriguez86],
AT&T's File System Switch (FSS) [Rifkin86],
D 3
the LOCUS distributed filesystem [Walker85],
and Masscomp's extended filesystem [Cole85].
Other remote filesystems have been implemented in research or
university groups for internal use,
notably the network filesystem in the Eighth Edition UNIX
system [Weinberger84] and two different filesystems used at Carnegie-Mellon
E 3
I 3
the LOCUS distributed file system [Walker85],
and Masscomp's extended file system [Cole85].
Other remote file systems have been implemented in research or
university groups for internal use \-
notably the network file system in the Eighth Edition UNIX
system [Weinberger84] and two different file systems used at Carnegie Mellon
E 3
University [Satyanarayanan85].
Numerous other remote file access methods have been devised for use
within individual UNIX processes,
many of them by modifications to the C I/O library
similar to those in the Newcastle Connection [Brownbridge82].
.PP
D 3
Each design attempts to isolate filesystem-dependent details
E 3
I 3
Each design attempts to isolate file system-dependent details
E 3
below a generic interface and to provide a framework within which
D 3
new filesystems may be incorporated.
E 3
I 3
new file systems may be incorporated.
E 3
However, each of these interfaces is different from
D 3
and incompatible with the others.
Each of them addresses somewhat different design goals.
Each was based on a different starting version of UNIX,
targeted a different set of filesystems with varying characteristics,
and uses a different set of primitive operations provided by the filesystem.
E 3
I 3
and is incompatible with the others.
Each addresses somewhat different design goals,
having been based on a different starting version of UNIX,
having targeted a different set of file systems with varying characteristics,
and having selected a different set of file system primitive operations.
E 3
.PP
D 3
We have studied the various filesystem interfaces to determine
their generality, completeness, robustness, efficiency and aesthetics.
As a result of this study, we have developed a proposal for a new
filesystem interface that includes the best features of
the existing implementations.
The proposal adopts the calling convention for name lookup introduced
in 4.3BSD, but is otherwise closely related to Sun's VFS.
A prototype implementation is now being developed at Berkeley.
E 3
I 3
We have studied the various file system interfaces to determine
their generality, completeness, robustness, efficiency, and aesthetics.
Based on this study, we have developed a proposal for a new
file system interface that we believe includes the best features of
each of the existing implementations.
Briefly, the proposal adopts the 4.3BSD calling convention for name lookup,
but otherwise is closely related to Sun's VFS.
A prototype implementation now is being developed.
E 3
This proposal and the rationale underlying its development
have been presented to major software vendors as an early step
D 3
toward convergence on a compatible filesystem interface [Karels86].
E 3
I 3
toward convergence on a compatible file system interface [Karels86].
E 3
D 2
.SH 2
E 2
I 2
.NH 2
E 2
Changes to the Protocol Layering Interface
.PP
D 4
The original work on restructuring the internal kernel interfaces
E 4
I 4
The original work on restructuring the UNIX character I/O system
E 4
to allow flexible configuration of the internal modules by user
processes was done at Bell Laboratories [Ritchie84].
Known as stackable line disciplines, these interfaces allowed a user
D 3
process to open a raw terminal port, then push on desired processing modules
such as one to do line editing.
E 3
I 3
process to open a raw terminal port and then push on appropriate
processing modules (such as one to do line editing).
E 3
D 4
With the advent of networking, an obvious extension was to provide
D 3
processing modules that implemented various protocols such as
the internet protocols TCP and IP or the Xerox protocols SPP and IDP.
E 3
I 3
processing modules capable of implementing various protocols such as
Internet's TCP and IP and Xerox's SPP and IDP.
E 3
By stacking a terminal processing module on top of a stream based
D 3
networking protocol, a user could build a network virtual terminal
without all the delay and expense of using ``telnet'' or ``rlogin''.
E 3
I 3
networking protocol, a user could build a ``network virtual terminal''
without all the delay and expense of using \fBtelnet\fP or \fBrlogin\fP.
E 4
I 4
This model allowed terminal processing modules to be used with
virtual-circuit network modules to create ``network virtual terminals''
by stacking a terminal processing module on top of a
networking protocol.
E 4
E 3
.PP
I 4
The design of the networking facilities for 4.2BSD took
D 5
a very different approach based on the
.B socket
interface.
E 5
I 5
a different approach based on the \fBsocket\fP interface.
E 5
This design allows a single system to support multiple sets of networking
D 5
protocols with stream, datagram and other types of access.
E 5
I 5
protocols with stream, datagram, and other types of access.
E 5
Protocol modules may deal with multiplexing of data from different connections
onto a single transport medium.
.PP
E 4
D 3
A problem with stackable line disciplines is that they
E 3
I 3
A problem with stackable line disciplines though, is that they
E 3
are inherently linear in nature.
D 3
Thus they do not adequately model the fan-in and fan-out
E 3
I 3
Thus, they do not adequately model the fan-in and fan-out
E 3
associated with multiplexing.
D 3
The simple and elegant stackable line discipline implementation was
converted to the full production implementation
of streams in System V Release 3.
In doing the conversion, many of the pragmatic issues such as handling of
D 2
multiplexed connections were handled.
E 2
I 2
multiplexed connections were addressed.
E 2
Unfortunately the complexity of the implementation increased as well.
E 3
I 3
The simple and elegant stackable line discipline implementation
of Eighth Edition UNIX was converted to the full production implementation
of Streams in System V Release 3.
D 4
In doing the conversion, many pragmatic issues \- including the handling of
multiplexed connections \- were addressed.
Unfortunately, the implementation is complexity increased in kind.
E 4
I 4
In doing the conversion, many pragmatic issues were addressed,
including the handling of
multiplexed connections and commercially important protocols.
Unfortunately, the implementation complexity increased enormously.
E 4
E 3
.PP
D 3
Because AT&T will not allow the inclusion of streams without also
changing the interface to comply with the System V interface definition,
we cannot use their implementation of streams in the Berkeley system.
Given that compatibility is impossible, we have complete freedom
to make our choices based solely on technical merits.
Our implementation will appear far more like the simpler
stackable line disciplines than the more complex streams.
E 3
I 3
Because AT&T will not allow others to include Streams unless they
D 4
also change their interface to comply with the System V Interface Definition,
E 4
I 4
also change their interface to comply with the System V Interface Definition
base and Networking Extension,
E 4
we cannot use the Release 3 implementation of Streams in the Berkeley system.
D 4
Given that compatibility thus will be impossible,
E 4
I 4
Given that compatibility thus will be difficult,
E 4
we feel we will have complete freedom to make our
choices based solely on technical merits.
D 5
As a result, our implementation will appear far more like the simpler
D 4
stackable line disciplines than the more complex Streams [Chandler86].
E 4
I 4
stackable line disciplines than the more complex Release 3 Streams [Chandler86].
E 5
I 5
As a result, our implementation will appear far more like the simpler stackable
line disciplines than the more complex Release 3 Streams [Chandler86].
E 5
A socket interface will be used rather than a character device interface,
and demultiplexing will be handled internally by the protocols in the kernel.
D 5
However, like Streams,
the interfaces between kernel protocol modules will follow a uniform
convention.
E 5
I 5
However, like Streams, the interfaces between kernel
protocol modules will follow a uniform convention.
E 5
E 4
E 3
E 1
