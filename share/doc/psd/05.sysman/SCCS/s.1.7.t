h32708
s 00016/00014/00146
d D 8.4 94/05/26 22:30:55 bostic 9 8
c cleanups and edits for accuracy
e
s 00012/00005/00148
d D 8.3 94/05/20 06:06:58 karels 8 7
c touchups and improvements
e
s 00114/00035/00039
d D 8.2 94/05/16 10:09:40 mckusick 7 6
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00072
d D 8.1 93/06/08 18:05:42 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00070
d D 6.4 91/04/17 10:01:59 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00072
d D 6.3 86/05/12 01:23:25 karels 4 3
c spelling
e
s 00001/00001/00072
d D 6.2 86/05/12 01:01:12 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00073
d D 6.1 86/05/08 12:26:45 mckusick 2 1
c format updates for 4.3BSD
e
s 00074/00000/00000
d D 5.1 86/05/08 00:03:11 mckusick 1 0
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
.sh "System operation support
.PP
E 7
I 7
.Sh 2 "System operation support
.LP
E 7
Unless noted otherwise,
the calls in this section are permitted only to a privileged user.
D 7
.NH 3
Bootstrap operations
E 7
I 7
.Sh 3 "Monitoring system operation
E 7
.PP
D 7
The call
E 7
I 7
The
.Fn sysctl
function allows any process to retrieve system information
and allows processes with appropriate privileges to set system configurations.
E 7
.DS
D 7
mount(blkdev, dir, ronly);
char *blkdev, *dir; int ronly;
E 7
I 7
.Fd sysctl 6 "get or set system information
D 9
sysctl(name, namelen, oldp, oldlenp, newp, newlen)
E 9
I 9
sysctl(name, namelen, oldp, oldlenp, newp, newlen);
E 9
int *name; u_int namelen; result void *oldp; result size_t *oldlenp;
void *newp; size_t newlen;
E 7
.DE
D 7
extends the UNIX name space.  The \fImount\fP call specifies
a block device \fIblkdev\fP containing a UNIX file system
to be made available starting at \fIdir\fP.  If \fIronly\fP is
set then the file system is read-only; writes to the file system
will not be permitted and access times will not be updated
when files are referenced.
\fIDir\fP is normally a name in the root directory.
E 7
I 7
The information available from
.Fn sysctl
consists of integers, strings, and tables.
.Fn Sysctl
returns a consistent snapshot of the data requested.
Consistency is obtained by locking the destination
buffer into memory so that the data may be copied out without blocking.
Calls to
.Fn sysctl
are serialized to avoid deadlock.
E 7
.PP
D 7
The call
.DS
swapon(blkdev, size);
char *blkdev; int size;
.DE
specifies a device to be made available for paging and swapping.
E 7
I 7
D 8
The state is described using a ``Management Information Base'' (MIB)
E 8
I 8
The object to be interrogated or set is named
using a ``Management Information Base'' (MIB)
E 8
style name, listed in \fIname\fP,
which is a \fInamelen\fP length array of integers.
I 8
This name is from a hierarchical name space,
with the most significant component in the first element of the array.
It is analogous to a file pathname, but with integers as components
rather than slash-separated strings.
E 8
E 7
.PP
D 7
.NH 3
Shutdown operations
E 7
I 7
The information is copied into the buffer specified by \fIoldp\fP.
The size of the buffer is given by the location specified by \fIoldlenp\fP
before the call,
D 9
and that location gives the amount of data copied after a successful call.
E 9
I 9
and that location is filled in with the amount of data copied after
a successful call.
E 9
If the amount of data available is greater
than the size of the buffer supplied,
the call supplies as much data as fits in the buffer provided
D 9
and returns with the error code ENOMEM.
E 9
I 9
and returns an error.
E 9
E 7
.PP
D 7
The call
E 7
I 7
To set a new value, \fInewp\fP
is set to point to a buffer of length \fInewlen\fP
from which the requested value is to be taken.
If a new value is not to be set, \fInewp\fP
should be set to NULL and \fInewlen\fP set to 0.
.PP
D 8
The top level names are defined with a CTL_ prefix in \fI<sys/sysctl.h>\fP,
E 8
I 8
The top level names (those used in the first element of the \fIname\fP array)
are defined with a CTL_ prefix in \fI<sys/sysctl.h>\fP,
E 8
and are as follows.
The next and subsequent levels down are found
in the include files listed here:
E 7
.DS
D 7
unmount(dir);
char *dir;
E 7
I 7
.TS
l l l.
Name	Next Level Names	Description
I 9
_
E 9
CTL\_DEBUG	sys/sysctl.h	Debugging
CTL\_FS	sys/sysctl.h	Filesystem
CTL\_HW	sys/sysctl.h	Generic CPU, I/O
CTL\_KERN	sys/sysctl.h	High kernel limits
CTL\_MACHDEP	sys/sysctl.h	Machine dependent
CTL\_NET	sys/socket.h	Networking
CTL\_USER	sys/sysctl.h	User-level
CTL\_VM	vm/vm_param.h	Virtual memory
.TE
E 7
.DE
D 7
unmounts the file system mounted on \fIdir\fP.
This call will succeed only if the file system is
not currently being used.
.PP
The call
E 7
I 7
.Sh 3 "Bootstrap operations
.LP
The call:
.DS
.Fd mount 4 "mount a filesystem
mount(type, dir, flags, data);
int type; char *dir; int flags; caddr_t data;
.DE
extends the name space. The
.Fn mount
call grafts a filesystem object onto the system file tree
at the point specified in \fIdir\fP.
D 8
The argument data describes the filesystem object to be mounted.
The argument type tells the kernel how to interpret data.
E 8
I 8
The argument \fItype\fP specifies the type of filesystem to be mounted.
The argument \fIdata\fP describes the filesystem object to be mounted
according to the \fItype\fP.
E 8
The contents of the filesystem become available through the
new mount point \fIdir\fP.
D 9
Any files in \fIdir\fP at the time of a successful mount
are swept under the carpet so to speak,
and are unavailable until the filesystem is unmounted.
The \fIflags\fP specifies generic properties,
E 9
I 9
Any files in or below \fIdir\fP at the time of a successful mount
disappear from the name space until the filesystem is unmounted.
The \fIflags\fP value specifies generic properties,
E 9
such as a request to mount the filesystem read-only.
.LP
D 9
Information about all the mounted filesystems can be obtained with the call:
E 9
I 9
Information about all mounted filesystems can be obtained with the call:
E 9
.DS
.Fd getfsstat 3 "get list of all mounted filesystems
D 9
getfsstat(buf, bufsize, flags)
E 9
I 9
getfsstat(buf, bufsize, flags);
E 9
result struct statfs *buf; long bufsize, int flags;
.DE
.LP
The call:
.DS
.Fd swapon 1 "add a swap device for interleaved paging/swapping
swapon(blkdev);
char *blkdev;
.DE
specifies a device to be made available for paging and swapping.
.Sh 3 "Shutdown operations
.LP
The call:
E 7
.DS
I 7
.Fd unmount 2 "dismount a filesystem
unmount(dir, flags);
char *dir; int flags;
.DE
unmounts the filesystem mounted on \fIdir\fP.
This call will succeed only if the filesystem is
not currently being used or if the MNT_FORCE flag is specified.
.LP
The call:
.DS
.Fd sync 0 "force completion of pending disk writes (flush cache)
E 7
sync();
.DE
D 9
schedules input/output to clean all system buffer caches.
E 9
I 9
schedules I/O to flush all modified disk blocks resident in the kernel.
E 9
D 4
(This call does not require priveleged status.)
E 4
I 4
(This call does not require privileged status.)
E 4
D 7
.PP
The call
E 7
I 7
Files can be selectively flushed to disk using the
.Fn fsync
call (see section
.Xr 2.2.6 ).
.LP
The call:
E 7
.DS
I 7
.Fd reboot 1 "reboot system or halt processor
E 7
D 9
reboot(how)
E 9
I 9
reboot(how);
E 9
int how;
.DE
causes a machine halt or reboot.  The call may request a reboot
by specifying \fIhow\fP as RB_AUTOBOOT, or that the machine be halted
D 3
with RB_HALT.  These constants are defined in <sys/reboot.h>.
E 3
I 3
D 9
with RB_HALT.  These constants are defined in \fI<sys/reboot.h>\fP.
E 9
I 9
with RB_HALT, among other options.
These constants are defined in \fI<sys/reboot.h>\fP.
E 9
E 3
D 7
.NH 3
Accounting
E 7
I 7
.Sh 3 "Accounting
E 7
.PP
The system optionally keeps an accounting record in a file
for each process that exits on the system.
The format of this record is beyond the scope of this document.
D 7
The accounting may be enabled to a file \fIname\fP by doing
E 7
I 7
The accounting may be enabled to a file \fIname\fP by doing:
E 7
.DS
I 7
.Fd acct 1 "enable or disable process accounting
E 7
acct(path);
char *path;
.DE
D 9
If \fIpath\fP is null, then accounting is disabled.  Otherwise,
the named file becomes the accounting file.
E 9
I 9
If \fIpath\fP is NULL, then accounting is disabled.
Otherwise, the named file becomes the accounting file.
E 9
E 1
