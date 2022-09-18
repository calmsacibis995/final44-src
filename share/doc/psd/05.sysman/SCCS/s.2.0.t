h13090
s 00011/00011/00046
d D 8.4 94/05/26 22:30:56 bostic 8 7
c cleanups and edits for accuracy
e
s 00004/00001/00053
d D 8.3 94/05/20 06:06:58 karels 7 6
c touchups and improvements
e
s 00011/00014/00043
d D 8.2 94/05/16 10:09:41 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00055
d D 8.1 93/06/08 18:05:47 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00053
d D 6.3 91/04/17 10:02:00 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00054
d D 6.2 86/05/12 01:01:15 karels 3 2
c update, correct, rephrase and re-propose
e
s 00001/00002/00055
d D 6.1 86/05/08 12:26:48 mckusick 2 1
c format updates for 4.3BSD
e
s 00057/00000/00000
d D 5.1 86/05/08 00:03:17 mckusick 1 0
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
.ds ss 1
.sh "System facilities
This section discusses the system facilities that
are not considered part of the kernel.
.PP
E 6
I 6
.Sh 1 "System facilities
.LP
E 6
The system abstractions described are:
.IP "Directory contexts
.br
D 6
A directory context is a position in the UNIX file system name
space.  Operations on files and other named objects in a file system are
E 6
I 6
A directory context is a position in the filesystem name
space.  Operations on files and other named objects in a filesystem are
E 6
always specified relative to such a context.
.IP "Files
.br
D 8
Files are used to store uninterpreted sequence of bytes on which
random access \fIreads\fP and \fIwrites\fP may occur.
D 3
Pages from files may also be mapped into process address space.
A directory may be read as a file\(dg.
E 3
I 3
D 6
Pages from files may also be mapped into process address space.\(dg
A directory may be read as a file.
E 3
.FS
D 2
\(dg Support for mapping files is not included in the 4.2 release.
E 2
I 2
\(dg Support for mapping files is not included in the 4.3 release.
E 2
.FE
E 6
I 6
Pages from files may also be mapped into process address space.
E 8
I 8
Files are used to store uninterpreted sequences of bytes,
which may be \fIread\fP and \fIwritten\fP randomly.
Pages from files may also be mapped into the process address space.
E 8
D 7
A directory may be read as a file,
E 7
I 7
A directory may be read as a file if permitted by the underlying
storage facility,
E 7
though it is usually accessed using
.Fn getdirentries
(see section
.Xr 2.2.3.1 ).
I 7
D 8
(Local filesystems permit directories to be read, although most
NFS implementations do not allow reading of directories.)
E 8
I 8
(Local filesystems permit directories to be read,
although most NFS implementations do not allow reading of directories.)
E 8
E 7
E 6
.IP "Communications domains
.br
A communications domain represents
an interprocess communications environment, such as the communications
D 6
facilities of the UNIX system,
E 6
I 6
facilities of the 4.4BSD system,
E 6
communications in the INTERNET, or the resource sharing protocols
and access rights of a resource sharing system on a local network.
.IP "Sockets
.br
A socket is an endpoint of communication and the focal
point for IPC in a communications domain.  Sockets may be created in pairs,
or given names and used to rendezvous with other sockets
in a communications domain, accepting connections from these
sockets or exchanging messages with them.  These operations model
a labeled or unlabeled communications graph, and can be used in a
wide variety of communications domains.  Sockets can have different
\fItypes\fP\| to provide different semantics of communication,
increasing the flexibility of the model.
.IP "Terminals and other devices
.br
D 8
Devices include
terminals, providing input editing and interrupt generation
and output flow control and editing, magnetic tapes,
disks and other peripherals.  They often support the generic
\fIread\fP and \fIwrite\fP operations as well as a number of \fIioctl\fP\|s.
E 8
I 8
Devices include terminals (providing input editing, interrupt
generation, output flow control, and editing), magnetic tapes,
disks, and other peripherals.
They normally support the generic
\fIread\fP and \fIwrite\fP operations as well as a number of \fIioctl\fP\|'s.
E 8
.IP "Processes
.br
Process descriptors provide facilities for control and debugging of
other processes.
D 6
.ds ss 2
E 6
E 1
