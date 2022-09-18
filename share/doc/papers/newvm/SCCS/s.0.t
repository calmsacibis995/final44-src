h16677
s 00001/00011/00059
d D 5.1 91/04/16 18:41:31 bostic 5 4
c new copyright; att/bsd/shared
e
s 00014/00003/00056
d D 1.4 89/03/10 09:44:07 bostic 4 3
c add Berkeley specific copyright notice
e
s 00007/00007/00052
d D 1.3 86/08/11 18:11:44 mckusick 3 2
c edits from Mike Karels
e
s 00002/00001/00057
d D 1.2 86/08/11 14:49:39 mckusick 2 1
c first round cleanup
e
s 00058/00000/00000
d D 1.1 86/08/11 11:51:36 mckusick 1 0
c first draft
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
.\"
D 5
.\" Redistribution and use in source and binary forms are permitted
.\" provided that the above copyright notice and this paragraph are
.\" duplicated in all such forms and that any documentation,
.\" advertising materials, and other materials related to such
.\" distribution and use acknowledge that the software was developed
.\" by the University of California, Berkeley.  The name of the
.\" University may not be used to endorse or promote products derived
.\" from this software without specific prior written permission.
.\" THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
.\" IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
.\" WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 5
I 5
.\" %sccs.include.redist.man%
E 5
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
I 2
.rm CM
E 2
.TL
A New Virtual Memory Implementation for Berkeley
.UX
.AU
Marshall Kirk McKusick
Michael J. Karels
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, California  94720
.AB
With the cost per byte of memory approaching that of the cost per byte
for disks, and with file systems increasingly distant from the host
machines, a new approach to the implementation of virtual memory is
necessary. Rather than preallocating swap space which limits the
maximum virtual memory that can be supported to the size of the swap
area, the system should support virtual memory up to the sum of the
sizes of physical memory plus swap space. For systems with a local swap
disk, but remote file systems, it may be useful to use some of the memory
to keep track of the contents of the swap space to avoid multiple fetches
of the same data from the file system.
.PP
The new implementation should also add new functionality.  Processes
D 3
should be allowed to have a large sparse address space, to map files
into their address space, to map device memory into their address
space, and to share memory with other processes. The shared address
E 3
I 3
should be allowed to have large sparse address spaces, to map files
into their address spaces, to map device memory into their address
spaces, and to share memory with other processes. The shared address
E 3
space may either be obtained by mapping a file into (possibly
different) parts of their address space, or by arranging to share
D 2
`anonymous memory' (that is memory that is zero fill on demand, and
E 2
I 2
D 3
``anonymous memory'' (that is memory that is zero fill on demand, and
E 3
I 3
``anonymous memory'' (that is, memory that is zero fill on demand, and
E 3
E 2
whose contents are lost when the last process unmaps the memory) with
another process as is done in System V.
.PP
D 3
One use of shared memory is to provide a high speed
E 3
I 3
One use of shared memory is to provide a high-speed
E 3
Inter-Process Communication (IPC) mechanism between two or more
cooperating processes. To insure the integrity of data structures
in a shared region, processes must be able to use semaphores to
coordinate their access to these shared structures. In System V,
these semaphores are provided as a set of system calls. Unfortunately,
the use of system calls reduces the throughput of the shared memory
IPC to that of existing IPC mechanisms.  We are proposing a scheme
that places the semaphores in the shared memory segment, so that
machines that have a test-and-set instruction can handle the usual
uncontested lock and unlock without doing a system call. Only in
D 3
the unusual case of trying to lock an already locked lock or in
E 3
I 3
the unusual case of trying to lock an already-locked lock or in
E 3
releasing a wanted lock will a system call be required.  The
D 3
interface will allow a user level implementation of the System V
E 3
I 3
interface will allow a user-level implementation of the System V
E 3
semaphore interface on most machines with a much lower runtime cost.
.AE
.LP
.bp
E 1
