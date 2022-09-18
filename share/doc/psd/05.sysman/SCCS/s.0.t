h10166
s 00047/00017/00098
d D 8.3 94/05/26 22:30:46 bostic 13 12
c cleanups and edits for accuracy
e
s 00034/00185/00081
d D 8.2 94/05/16 10:09:30 mckusick 12 11
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00264
d D 8.1 93/06/08 18:04:53 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00262
d D 6.9 93/06/05 17:36:40 mckusick 10 9
c its 4.4BSD now
e
s 00002/00002/00264
d D 6.8 93/06/05 15:49:06 bostic 9 8
c new doc.mk; document numbering changes for 4.4BSD
e
s 00004/00003/00262
d D 6.7 91/04/17 10:01:50 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00001/00264
d D 6.6 86/05/13 16:20:02 mckusick 7 6
c fix those macros
e
s 00075/00075/00190
d D 6.5 86/05/12 11:59:19 mckusick 6 5
c format
e
s 00001/00001/00264
d D 6.4 86/05/12 01:23:09 karels 5 4
c spelling
e
s 00005/00004/00260
d D 6.3 86/05/12 01:00:31 karels 4 3
c update, correct, rephrase and re-propose
e
s 00006/00001/00258
d D 6.2 86/05/08 17:50:48 mckusick 3 2
c typesetting glitches
e
s 00009/00026/00250
d D 6.1 86/05/08 12:24:39 mckusick 2 1
c update virtual memory design
e
s 00276/00000/00000
d D 5.1 86/05/08 00:02:03 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 8
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 8
I 8
D 11
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 11
I 11
D 13
.\" Copyright (c) 1983, 1993
E 13
I 13
.\" Copyright (c) 1983, 1993, 1994
E 13
.\"	The Regents of the University of California.  All rights reserved.
E 11
.\"
.\" %sccs.include.redist.roff%
E 8
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
I 2
D 4
.EH 'PS1:6-%''4.3BSD Architecture Manual'
.OH '4.3BSD Architecture Manual''PS1:6-%'
E 4
E 2
.if n .ND
.TL
D 2
4.2BSD System Manual
.sp
Revised July, 1983
E 2
I 2
Berkeley Software Architecture Manual
I 3
.br
E 3
D 10
4.3BSD Edition
E 10
I 10
4.4BSD Edition
E 10
E 2
.AU
D 2
William Joy, Eric Cooper, Robert Fabry,
.br
Samuel Leffler, Kirk McKusick and David Mosher
E 2
I 2
D 3
William Joy, Samuel Leffler, M. Kirk McKusick, Michael Karels
E 3
I 3
D 12
William Joy, Robert Fabry,
E 12
I 12
M. Kirk McKusick, Michael Karels
E 12
.AU
D 12
Samuel Leffler, M. Kirk McKusick,
E 12
I 12
Samuel Leffler, William Joy
E 12
.AU
D 12
Michael Karels
E 12
I 12
Robert Fabry
E 12
E 3
E 2
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, CA  94720
I 4
D 9
.EH 'PS1:6-%''4.3BSD Architecture Manual'
.OH '4.3BSD Architecture Manual''PS1:6-%'
E 9
I 9
D 10
.EH 'PSD:5-%''4.3BSD Architecture Manual'
.OH '4.3BSD Architecture Manual''PSD:5-%'
E 10
I 10
.EH 'PSD:5-%''4.4BSD Architecture Manual'
.OH '4.4BSD Architecture Manual''PSD:5-%'
E 10
E 9
E 4
D 2

(415) 642-7780
E 2
.AB
D 12
.FS
* UNIX is a trademark of Bell Laboratories.
.FE
This document summarizes the facilities
D 2
provided by the 4.2BSD version of the UNIX operating system.
E 2
I 2
D 4
provided by the 4.3BSD version of the UNIX operating system.
E 4
I 4
D 10
provided by the 4.3BSD version of the UNIX\|* operating system.
E 10
I 10
provided by the 4.4BSD version of the UNIX\|* operating system.
E 12
I 12
This document summarizes the system calls
provided by the 4.4BSD operating system.
E 12
E 10
E 4
E 2
D 13
It does not attempt to act as a tutorial for use of the system
E 13
I 13
It does not attempt to act as a tutorial for use of the system,
E 13
nor does it attempt to explain or justify the design of the
system facilities.
It gives neither motivation nor implementation details,
in favor of brevity.
.PP
The first section describes the basic kernel functions
D 12
provided to a UNIX process: process naming and protection,
E 12
I 12
provided to a process: process naming and protection,
E 12
memory management, software interrupts,
D 12
object references (descriptors), time and statistics functions,
E 12
I 12
time and statistics functions,
object references (descriptors),
E 12
and resource controls.
These facilities, as well as facilities for
bootstrap, shutdown and process accounting,
are provided solely by the kernel.
.PP
The second section describes the standard system
abstractions for
D 12
files and file systems,
E 12
I 12
files and filesystems,
E 12
communication,
terminal handling,
and process control and debugging.
These facilities are implemented by the operating system or by
network server processes.
.AE
.LP
D 2
.de PT
.lt \\n(LLu
.pc %
.nr PN \\n%
.tl '\\*(LH'\\*(CH'\\*(RH'
.lt \\n(.lu
..
.af PN i
.ds LH 4.2BSD System Manual
.ds RH Contents
.bp 1
.if t .ds CF -- September 1, 1982 --
.if t .ds LF CSRG TR/5
.if t .ds RF "Joy, et. al.
E 2
I 2
D 12
.bp
E 2
.ft B
.br
.sv 2
.ce
TABLE OF CONTENTS
.ft R
E 12
I 12
.bp +3
.sy echo -n >toc
.de Sh
.sy echo >>toc '.L\\$1 "\\$2" \\n%'
.ie \\$1=0 \{\
\fB\\$2\fP
.\}
.el \{\
.NH \\$1
\\$2
E 12
.LP
D 12
.sp 1
.nf
.B "Introduction."
.LP
.if t .sp .5v
.nf
.B "0. Notation and types"
.LP
.if t .sp .5v
.nf
.B "1. Kernel primitives"
.LP
.if t .sp .5v
.nf
.nf
\fB1.1.  Processes and protection\fP
D 6
\0\0\0.1.  Host and process identifiers
\0\0\0.2.  Process creation and termination
\0\0\0.3.  User and group ids
\0\0\0.4.  Process groups
E 6
I 6
1.1.1.  Host and process identifiers
1.1.2.  Process creation and termination
1.1.3.  User and group ids
1.1.4.  Process groups
E 6
.LP
.nf
\fB1.2.  Memory management\fP
D 6
\0\0\0.1.  Text, data and stack
\0\0\0.2.  Mapping pages
\0\0\0.3.  Page protection control
\0\0\0.4.  Giving and getting advice
I 2
\0\0\0.5.  Protection primitives
E 6
I 6
1.2.1.  Text, data and stack
1.2.2.  Mapping pages
1.2.3.  Page protection control
1.2.4.  Giving and getting advice
1.2.5.  Protection primitives
E 6
E 2
.LP
.if t .sp .5v
.nf
\fB1.3.  Signals\fP
D 6
\0\0\0.1.  Overview
\0\0\0.2.  Signal types
\0\0\0.3.  Signal handlers
\0\0\0.4.  Sending signals
\0\0\0.5.  Protecting critical sections
\0\0\0.6.  Signal stacks
E 6
I 6
1.3.1.  Overview
1.3.2.  Signal types
1.3.3.  Signal handlers
1.3.4.  Sending signals
1.3.5.  Protecting critical sections
1.3.6.  Signal stacks
E 6
.LP
.if t .sp .5v
.nf
\fB1.4.  Timing and statistics\fP
D 6
\0\0\0.1.  Real time
\0\0\0.2.  Interval time
E 6
I 6
1.4.1.  Real time
1.4.2.  Interval time
E 6
.LP
.if t .sp .5v
.nf
\fB1.5.  Descriptors\fP
D 6
\0\0\0.1.  The reference table
\0\0\0.2.  Descriptor properties
\0\0\0.3.  Managing descriptor references
\0\0\0.4.  Multiplexing requests
\0\0\0.5.  Descriptor wrapping
E 6
I 6
1.5.1.  The reference table
1.5.2.  Descriptor properties
1.5.3.  Managing descriptor references
1.5.4.  Multiplexing requests
1.5.5.  Descriptor wrapping
E 6
.LP
.if t .sp .5v
.nf
\fB1.6.  Resource controls\fP
D 6
\0\0\0.1.  Process priorities
\0\0\0.2.  Resource utilization
\0\0\0.3.  Resource limits
E 6
I 6
1.6.1.  Process priorities
1.6.2.  Resource utilization
1.6.3.  Resource limits
E 6
.LP
.if t .sp .5v
.nf
\fB1.7.  System operation support\fP
D 6
\0\0\0.1.   Bootstrap operations
\0\0\0.2.   Shutdown operations
\0\0\0.3.   Accounting
E 6
I 6
1.7.1.   Bootstrap operations
1.7.2.   Shutdown operations
1.7.3.   Accounting
E 6
.bp
.LP
.if t .sp .5v
.sp 1
.nf
\fB2.  System facilities\fP
.LP
.if t .sp .5v
.nf
\fB2.1.   Generic operations\fP
D 6
\0\0\0.1.   Read and write
\0\0\0.2.   Input/output control
\0\0\0.3.   Non-blocking and asynchronous operations
E 6
I 6
2.1.1.   Read and write
2.1.2.   Input/output control
2.1.3.   Non-blocking and asynchronous operations
E 6
.LP
.if t .sp .5v
.nf
\fB2.2.  File system\fP
D 6
\0\0\0.1   Overview
\0\0\0.2.  Naming
\0\0\0.3.  Creation and removal
\0\0\0.3.1.  Directory creation and removal
\0\0\0.3.2.  File creation
\0\0\0.3.3.  Creating references to devices
\0\0\0.3.4.  Portal creation
\0\0\0.3.6.  File, device, and portal removal
\0\0\0.4.  Reading and modifying file attributes
\0\0\0.5.  Links and renaming
\0\0\0.6.  Extension and truncation
\0\0\0.7.  Checking accessibility
\0\0\0.8.  Locking
\0\0\0.9.  Disc quotas
E 6
I 6
2.2.1   Overview
2.2.2.  Naming
2.2.3.  Creation and removal
2.2.3.1.  Directory creation and removal
2.2.3.2.  File creation
2.2.3.3.  Creating references to devices
2.2.3.4.  Portal creation
2.2.3.6.  File, device, and portal removal
2.2.4.  Reading and modifying file attributes
2.2.5.  Links and renaming
2.2.6.  Extension and truncation
2.2.7.  Checking accessibility
2.2.8.  Locking
2.2.9.  Disc quotas
E 6
.LP
.if t .sp .5v
.nf
D 5
\fB2.3.  Inteprocess communication\fP
E 5
I 5
\fB2.3.  Interprocess communication\fP
E 5
D 6
\0\0\0.1.   Interprocess communication primitives
\0\0\0.1.1.\0   Communication domains
\0\0\0.1.2.\0   Socket types and protocols
\0\0\0.1.3.\0   Socket creation, naming and service establishment
\0\0\0.1.4.\0   Accepting connections
\0\0\0.1.5.\0   Making connections
\0\0\0.1.6.\0   Sending and receiving data
\0\0\0.1.7.\0   Scatter/gather and exchanging access rights
\0\0\0.1.8.\0   Using read and write with sockets
\0\0\0.1.9.\0   Shutting down halves of full-duplex connections
\0\0\0.1.10.\0  Socket and protocol options
\0\0\0.2.   UNIX domain
\0\0\0.2.1.    Types of sockets
\0\0\0.2.2.    Naming
\0\0\0.2.3.    Access rights transmission
\0\0\0.3.   INTERNET domain
\0\0\0.3.1.    Socket types and protocols
\0\0\0.3.2.    Socket naming
\0\0\0.3.3.    Access rights transmission
\0\0\0.3.4.    Raw access
E 6
I 6
2.3.1.   Interprocess communication primitives
2.3.1.1.\0   Communication domains
2.3.1.2.\0   Socket types and protocols
2.3.1.3.\0   Socket creation, naming and service establishment
2.3.1.4.\0   Accepting connections
2.3.1.5.\0   Making connections
2.3.1.6.\0   Sending and receiving data
2.3.1.7.\0   Scatter/gather and exchanging access rights
2.3.1.8.\0   Using read and write with sockets
2.3.1.9.\0   Shutting down halves of full-duplex connections
2.3.1.10.\0  Socket and protocol options
2.3.2.   UNIX domain
2.3.2.1.    Types of sockets
2.3.2.2.    Naming
2.3.2.3.    Access rights transmission
2.3.3.   INTERNET domain
2.3.3.1.    Socket types and protocols
2.3.3.2.    Socket naming
2.3.3.3.    Access rights transmission
2.3.3.4.    Raw access
E 6
.LP
.if t .sp .5v
.nf
\fB2.4.  Terminals and devices\fP
D 6
\0\0\0.1.   Terminals
\0\0\0.1.1.    Terminal input
\0\0\0.1.1.1     Input modes
\0\0\0.1.1.2     Interrupt characters
\0\0\0.1.1.3     Line editing
\0\0\0.1.2.    Terminal output
\0\0\0.1.3.    Terminal control operations
\0\0\0.1.4.    Terminal hardware support
\0\0\0.2.   Structured devices
\0\0\0.3.   Unstructured devices
E 6
I 6
2.4.1.   Terminals
2.4.1.1.    Terminal input
2.4.1.1.1     Input modes
2.4.1.1.2     Interrupt characters
2.4.1.1.3     Line editing
2.4.1.2.    Terminal output
2.4.1.3.    Terminal control operations
2.4.1.4.    Terminal hardware support
2.4.2.   Structured devices
2.4.3.   Unstructured devices
E 6
.LP
.if t .sp .5v
.nf
\fB2.5.  Process control and debugging\fP
.LP
.if t .sp .5v
.nf
\fBI.  Summary of facilities\fP
.LP
D 2
.af PN 1
E 2
.de sh
.ds RH \\$1
.bp
.NH \\*(ss
\s+2\\$1\s0
.PP
.PP
E 12
I 12
.\}
E 12
..
D 2
.bp 1
E 2
I 2
D 12
.bp
E 2
D 7
.nr ss 1
E 7
I 7
.ds ss 1
E 7
.de _d
.if t .ta .6i 2.1i 2.6i
.\" 2.94 went to 2.6, 3.64 to 3.30
.if n .ta .84i 2.6i 3.30i
E 12
I 12
.de Fn
\fI\\$1\fP\\$2
E 12
..
D 12
.de _f
.if t .ta .5i 1.25i 2.5i 3.5i
.\" 3.5i went to 3.8i
.if n .ta .7i 1.75i 3.8i 4.8i
E 12
I 12
.de Xr
\\$1\\$2
E 12
..
D 12
.nr H1 -1
.sh "Notation and types
E 12
I 12
.de Fd
.sy echo >>toc '.Nm \\$1 \\$2 "\\$3'
..
.Sh 0 "Notation and Types
E 12
.PP
The notation used to describe system calls is a variant of a
D 13
C language call, consisting of a prototype call followed by
declaration of parameters and results.
E 13
I 13
C language function call, consisting of a prototype call followed by
the declaration of parameters and results.
E 13
An additional keyword \fBresult\fP, not part of the normal C language,
is used to indicate which of the declared entities receive results.
As an example, consider the \fIread\fP call, as described in
D 12
section 2.1:
E 12
I 12
section
.Xr 2.1.1 :
E 12
.DS
cc = read(fd, buf, nbytes);
D 13
result int cc; int fd; result char *buf; int nbytes;
E 13
I 13
result ssize_t cc; int fd; result void *buf; size_t nbytes;
E 13
.DE
The first line shows how the \fIread\fP routine is called, with
three parameters.
D 13
As shown on the second line \fIcc\fP is an integer and \fIread\fP also
returns information in the parameter \fIbuf\fP.
E 13
I 13
As shown on the second line,
the return value \fIcc\fP is a size_t and \fIread\fP
also returns information in the parameter \fIbuf\fP.
E 13
.PP
D 13
Description of all error conditions arising from each system call
D 12
is not provided here; they appear in the programmer's manual.
E 12
I 12
is not provided here; they appear in section
E 13
I 13
The descriptions of error conditions arising from each system call
are not provided here; they appear in section
E 13
.Xr 2
D 13
of the programmer's reference manual.
E 13
I 13
of the Programmer's Reference Manual.
E 13
E 12
In particular, when accessed from the C language,
many calls return a characteristic \-1 value
when an error occurs, returning the error code in the global variable
\fIerrno\fP.
Other languages may present errors in different ways.
.PP
D 4
A number of system standard types are defined in the include file <sys/types.h>
E 4
I 4
D 13
A number of system standard types are defined in the include file
E 13
I 13
A number of system standard types are defined by the include file
E 13
.I <sys/types.h>
E 4
and used in the specifications here and in many C programs.
D 13
These include \fBcaddr_t\fP giving a memory address (typically as
a character pointer), 
D 12
\fBoff_t\fP giving a file offset (typically as a long integer),
E 12
I 12
\fBoff_t\fP giving a file offset (typically as a 64-bit integer),
E 12
and a set of unsigned types \fBu_char\fP, \fBu_short\fP, \fBu_int\fP
and \fBu_long\fP, shorthand names for \fBunsigned char\fP, \fBunsigned
short\fP, etc.
E 13
I 13
.sp
.ft C
.TS
l l l.
Type	Value
_
caddr_t	char *	/* a memory address */
clock_t	unsigned long	/* count of CLK_TCK's */
gid_t	unsigned long	/* group ID */
int16_t	short	/* 16-bit integer */
int32_t	int	/* 32-bit integer */
int64_t	long long	/* 64-bit integer */
int8_t	signed char	/* 8-bit integer */
mode_t	unsigned short	/* file permissions */
off_t	quad_t	/* file offset */
pid_t	long	/* process ID */
qaddr_t	quad_t *
quad_t	long long
size_t	unsigned int	/* count of bytes */
ssize_t	int	/* signed size_t */
time_t	long	/* seconds since the Epoch */
u_char	unsigned char
u_int	unsigned int
u_int16_t	unsigned short	/* unsigned 16-bit integer */
u_int32_t	unsigned int	/* unsigned 32-bit integer */
u_int64_t	unsigned long long	/* unsigned 64-bit integer */
u_int8_t	unsigned char	/* unsigned 8-bit integer */
u_long	unsigned long
u_quad_t	unsigned long long
u_short	unsigned short
uid_t	unsigned long	/* user ID */
uint	unsigned int	/* System V compatibility */
ushort	unsigned short	/* System V compatibility */
.TE
.ft R
E 13
E 1
