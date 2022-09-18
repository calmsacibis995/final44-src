h59601
s 00019/00018/00134
d D 8.4 94/05/26 22:30:56 bostic 8 7
c cleanups and edits for accuracy
e
s 00010/00004/00142
d D 8.3 94/05/20 06:06:59 karels 7 6
c touchups and improvements
e
s 00066/00032/00080
d D 8.2 94/05/16 10:09:41 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00110
d D 8.1 93/06/08 18:05:55 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00108
d D 6.3 91/04/17 10:02:00 bostic 4 3
c new copyright; att/bsd/shared
e
s 00008/00007/00103
d D 6.2 86/05/12 01:01:18 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00110
d D 6.1 86/05/08 12:26:54 mckusick 2 1
c format updates for 4.3BSD
e
s 00111/00000/00000
d D 5.1 86/05/08 00:03:24 mckusick 1 0
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
.sh "Generic operations
E 6
I 6
.Sh 2 "Generic operations
E 6
.PP
D 6
.PP
E 6
Many system abstractions support the
D 6
operations \fIread\fP, \fIwrite\fP and \fIioctl\fP.  We describe
the basics of these common primitives here.
E 6
I 6
D 8
operations
E 8
.Fn read ,
.Fn write ,
and
D 8
.Fn ioctl .
E 8
I 8
.Fn ioctl
operations.
E 8
We describe the basics of these common primitives here.
E 6
Similarly, the mechanisms whereby normally synchronous operations
may occur in a non-blocking or asynchronous fashion are
common to all system-defined abstractions and are described here.
D 6
.NH 3
Read and write
E 6
I 6
.Sh 3 "Read and write
E 6
.PP
D 6
The \fIread\fP and \fIwrite\fP system calls can be applied
to communications channels, files, terminals and devices.
E 6
I 6
The
.Fn read
and
.Fn write
system calls can be applied to communications channels,
files, terminals and devices.
E 6
They have the form:
.DS
I 6
.Fd read 3 "read input
E 6
cc = read(fd, buf, nbytes);
D 8
result int cc; int fd; result caddr_t buf; int nbytes;
E 8
I 8
result ssize_t cc; int fd; result void *buf; size_t nbytes;
E 8
D 6

E 6
I 6
.DE
.DS
.Fd write 3 "write output
E 6
cc = write(fd, buf, nbytes);
D 8
result int cc; int fd; caddr_t buf; int nbytes;
E 8
I 8
result ssize_t cc; int fd; void *buf; size_t nbytes;
E 8
.DE
D 6
The \fIread\fP call transfers as much data as possible from the
E 6
I 6
The
.Fn read
call transfers as much data as possible from the
E 6
object defined by \fIfd\fP to the buffer at address \fIbuf\fP of
size \fInbytes\fP.  The number of bytes transferred is
returned in \fIcc\fP, which is \-1 if a return occurred before
any data was transferred because of an error or use of non-blocking
operations.
I 7
A return value of 0 is used to indicate an end-of-file condition.
E 7
.PP
D 6
The \fIwrite\fP call transfers data from the buffer to the
E 6
I 6
The
.Fn write
call transfers data from the buffer to the
E 6
object defined by \fIfd\fP.  Depending on the type of \fIfd\fP,
D 6
it is possible that the \fIwrite\fP call will accept some portion
E 6
I 6
it is possible that the
.Fn write
D 8
call will accept some portion
E 6
of the provided bytes; the user should resubmit the other bytes
in a later request in this case.
E 8
I 8
call will accept only a portion of the provided bytes;
the user should resubmit the other bytes in a later request.
E 8
Error returns because of interrupted or otherwise incomplete operations
D 7
are possible.
E 7
I 7
D 8
are possible, in which case no data have been transferred.
E 8
I 8
are possible, in which case no data will have been transferred.
E 8
E 7
.PP
D 8
Scattering of data on input or gathering of data for output
E 8
I 8
Scattering of data on input, or gathering of data for output
E 8
is also possible using an array of input/output vector descriptors.
D 3
The type for the descriptors is defined in <sys/uio.h> as:
E 3
I 3
The type for the descriptors is defined in \fI<sys/uio.h>\fP as:
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
struct iovec {
D 7
	caddr_t	iov_msg;	/* base of a component */
E 7
I 7
D 8
	caddr_t	iov_base;	/* base of a component */
E 7
	int	iov_len;	/* length of a component */
E 8
I 8
	char	*iov_base;	/* base of a component */
	size_t	iov_len;	/* length of a component */
E 8
};
I 6
.TE
I 8
.DE
E 8
I 7
.LP
The \fIiov_base\fP field should be treated as if its type were
``void *'' as POSIX and other versions of the structure may use
that type.
Thus, pointer arithmetic should not use this value without a cast.
E 7
E 6
D 8
.DE
E 8
I 8
.LP
E 8
D 6
The calls using an array of descriptors are:
E 6
I 6
The calls using an array of \fIiovec\fP structures are:
E 6
.DS
I 6
.Fd readv 3 "read gathered input
E 6
cc = readv(fd, iov, iovlen);
D 8
result int cc; int fd; struct iovec *iov; int iovlen;
E 8
I 8
result ssize_t cc; int fd; struct iovec *iov; int iovlen;
E 8
D 6

E 6
I 6
.DE
.DS
.Fd writev 3 "write scattered output
E 6
cc = writev(fd, iov, iovlen);
D 8
result int cc; int fd; struct iovec *iov; int iovlen;
E 8
I 8
result ssize_t cc; int fd; struct iovec *iov; int iovlen;
E 8
.DE
Here \fIiovlen\fP is the count of elements in the \fIiov\fP array.
D 6
.NH 3
Input/output control
.PP
Control operations on an object are performed by the \fIioctl\fP
E 6
I 6
.Sh 3 "Input/output control
.LP
Control operations on an object are performed by the
.Fn ioctl
E 6
operation:
.DS
I 6
.Fd ioctl 3 "control device
E 6
ioctl(fd, request, buffer);
D 8
int fd, request; caddr_t buffer;
E 8
I 8
int fd; u_long request; caddr_t buffer;
E 8
.DE
This operation causes the specified \fIrequest\fP to be performed
on the object \fIfd\fP.  The \fIrequest\fP parameter specifies
whether the argument buffer is to be read, written, read and written,
D 8
or is not needed, and also the size of the buffer, as well as the
E 8
I 8
or is not used, and also the size of the buffer, as well as the
E 8
request.
Different descriptor types and subtypes within descriptor types
D 6
may use distinct \fIioctl\fP requests.  For example,
E 6
I 6
may use distinct
.Fn ioctl
requests. For example,
E 6
operations on terminals control flushing of input and output
queues and setting of terminal parameters; operations on
disks cause formatting operations to occur; operations on tapes
control tape positioning.
D 6
.PP
E 6
D 3
The names for basic control operations are defined in <sys/ioctl.h>.
E 3
I 3
D 8
The names for basic control operations are defined in \fI<sys/ioctl.h>\fP.
E 8
I 8
The names for basic control operations are defined by \fI<sys/ioctl.h>\fP,
or more specifically by files it includes.
E 8
E 3
D 6
.NH 3
Non-blocking and asynchronous operations
E 6
I 6
.Sh 3 "Non-blocking and asynchronous operations
E 6
.PP
A process that wishes to do non-blocking operations on one of
its descriptors sets the descriptor in non-blocking mode as
D 6
described in section 1.5.4.  Thereafter the \fIread\fP call will
return a specific EWOULDBLOCK error indication if there is no data to be
\fIread\fP.  The process may
D 3
\fIdselect\fP the associated descriptor to determine when a read is
E 3
I 3
\fIselect\fP the associated descriptor to determine when a read is
E 3
possible.
E 6
I 6
described in section
.Xr 1.5.4 .
Thereafter the
.Fn read
call will return a specific EWOULDBLOCK error indication
if there is no data to be
.Fn read .
The process may
.Fn select
the associated descriptor to determine when a read is possible.
E 6
.PP
Output attempted when a descriptor can accept less than is requested
will either accept some of the provided data, returning a shorter than normal
length, or return an error indicating that the operation would block.
D 6
More output can be performed as soon as a \fIselect\fP call indicates
E 6
I 6
More output can be performed as soon as a
.Fn select
call indicates
E 6
D 7
the object is writeable.
E 7
I 7
the object is writable.
E 7
.PP
Operations other than data input or output
may be performed on a descriptor in a non-blocking fashion.
These operations will return with a characteristic error indicating
that they are in progress
D 3
if they cannot return immediately.  The descriptor
E 3
I 3
if they cannot complete immediately.  The descriptor
E 3
D 6
may then be \fIselect\fPed for \fIwrite\fP to find out
D 3
when the operation can be retried.  When \fIselect\fP indicates
the descriptor is writeable, a respecification of the original
operation will return the result of the operation.
E 3
I 3
when the operation has been completed.  When \fIselect\fP indicates
the descriptor is writeable, the operation has completed.
E 6
I 6
may then be
.Fn select 'ed
for
.Fn write
to find out when the operation has been completed.
When
.Fn select
D 7
indicates the descriptor is writeable, the operation has completed.
E 7
I 7
indicates the descriptor is writable, the operation has completed.
E 7
E 6
Depending on the nature of the descriptor and the operation,
additional activity may be started or the new state may be tested.
E 3
E 1
