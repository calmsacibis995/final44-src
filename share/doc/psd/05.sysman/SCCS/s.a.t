h25102
s 00074/00198/00011
d D 8.2 94/05/16 10:09:36 mckusick 9 8
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00214
d D 8.1 93/06/08 18:06:30 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00212
d D 6.6 91/04/17 10:02:05 bostic 7 6
c new copyright; att/bsd/shared
e
s 00002/00002/00213
d D 6.5 86/05/12 10:51:27 karels 6 5
c msleep stays, but after mset; caveat about mixed use
e
s 00004/00004/00211
d D 6.4 86/05/12 01:24:12 karels 5 4
c spelling
e
s 00001/00001/00214
d D 6.3 86/05/12 01:01:50 karels 4 3
c update, correct, rephrase and re-propose
e
s 00002/00002/00213
d D 6.2 86/05/08 17:50:53 mckusick 3 2
c typesetting glitches
e
s 00004/00003/00211
d D 6.1 86/05/08 12:24:56 mckusick 2 1
c update virtual memory design
e
s 00214/00000/00000
d D 5.1 86/05/08 00:04:04 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 7
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 7
I 7
D 8
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 8
I 8
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 8
.\"
.\" %sccs.include.redist.roff%
E 7
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 9
.ds RH Summary of facilities
E 9
I 9
.de L0
.nr l1 0
.nr l2 0
.nr l3 0
.nr l4 0
..
.de L1
.nr l1 +1
.nr l2 0
.nr l3 0
.nr l4 0
.sp 0.5
\\n(l1	\fB\\$1\fP
..
.de L2
.nr l2 +1
.nr l3 0
.nr l4 0
.sp 0.25
\\n(l1.\\n(l2	\fB\\$1\fP
..
.de L3
..
.de L4
..
.de Nm
.br
 		\\$1	\\$3
..
E 9
.bp
D 9
.SH
\s+2I.  Summary of facilities\s0
.PP
.de h
E 9
I 9
.Sh 1 "Summary of facilities
.sp 1
.ta \w'8.8\ \ 'u +0.25i +\w'gettimeofday\ \ 'u
.so Toc
.pn 2
.bp
.de L0
.nr l1 0
.nr l2 0
.nr l3 0
.nr l4 0
E 9
.br
D 9
.if n .ne 8
\fB\\$1 \\$2\fP
E 9
I 9
 		\fB\\$1\fP	\\$2
..
.de L1
.nr l1 +1
.nr l2 0
.nr l3 0
.nr l4 0
.sp 0.5
 	\\n(l1	\fB\\$1\fP	\\$2
..
.de L2
.nr l2 +1
.nr l3 0
.nr l4 0
.sp 0.25
 	\\n(l1.\\n(l2	\fB\\$1\fP	\\$2
..
.de L3
.nr l3 +1
.nr l4 0
E 9
.br
I 9
 	\\n(l1.\\n(l2.\\n(l3	\\$1	\\$2
E 9
..
D 9
.nr H1 0
.NH
Kernel primitives
.LP
.h 1.1. "Process naming and protection
.in +5
.TS
lw(1.6i) aw(3i).
sethostid	set UNIX host id
gethostid	get UNIX host id
sethostname	set UNIX host name
gethostname	get UNIX host name
getpid	get process id
fork	create new process
exit	terminate a process
execve	execute a different process
getuid	get user id
geteuid	get effective user id
setreuid	set real and effective user id's
getgid	get accounting group id
getegid	get effective accounting group id
getgroups	get access group set
setregid	set real and effective group id's
setgroups	set access group set
getpgrp	get process group
setpgrp	set process group
.TE
.in -5
.h 1.2 "Memory management
.in +5
.TS
lw(1.6i) aw(3i).
D 4
<mman.h>	memory management definitions
E 4
I 4
<sys/mman.h>	memory management definitions
E 4
sbrk	change data section size
sstk\(dg	change stack section size
.FS
D 2
\(dg Not supported in 4.2BSD.
E 2
I 2
\(dg Not supported in 4.3BSD.
E 2
.FE
getpagesize	get memory page size
mmap\(dg	map pages of memory
D 5
mremap\(dg	remap pages in memory
E 5
I 5
msync\(dg	flush modified mapped pages to filesystem
E 5
munmap\(dg	unmap memory
mprotect\(dg	change protection of pages
madvise\(dg	give memory management advice
mincore\(dg	determine core residency of pages
I 2
D 5
msleep\(dg	sleep on a lock
mwakeup\(dg	wakeup process sleeping on a lock
E 5
I 5
D 6
.\"msleep\(dg	sleep on a lock
.\"mwakeup\(dg	wakeup process sleeping on a lock
E 6
I 6
msleep\(dg	sleep on a lock
mwakeup\(dg	wakeup process sleeping on a lock
E 6
E 5
E 2
.TE
.in -5
.h 1.3 "Signals
.in +5
.TS
lw(1.6i) aw(3i).
<signal.h>	signal definitions
sigvec	set handler for signal
kill	send signal to process
killpgrp	send signal to process group
sigblock	block set of signals
sigsetmask	restore set of blocked signals
sigpause	wait for signals
sigstack	set software stack for signals
.TE
.in -5
.h 1.4 "Timing and statistics
.in +5
.TS
lw(1.6i) aw(3i).
<sys/time.h>	time-related definitions
gettimeofday	get current time and timezone
settimeofday	set current time and timezone
getitimer	read an interval timer
setitimer	get and set an interval timer
profil	profile process
.TE
.in -5
.h 1.5 "Descriptors
.in +5
.TS
lw(1.6i) aw(3i).
getdtablesize	descriptor reference table size
dup	duplicate descriptor
dup2	duplicate to specified index
close	close descriptor
select	multiplex input/output
fcntl	control descriptor options
wrap\(dg	wrap descriptor with protocol
.FS
D 2
\(dg Not supported in 4.2BSD.
E 2
I 2
\(dg Not supported in 4.3BSD.
E 2
.FE
.TE
.in -5
.h 1.6 "Resource controls
.in +5
.TS
lw(1.6i) aw(3i).
<sys/resource.h>	resource-related definitions
getpriority	get process priority
setpriority	set process priority
getrusage	get resource usage
getrlimit	get resource limitations
setrlimit	set resource limitations
.TE
.in -5
.h 1.7 "System operation support
.in +5
.TS
lw(1.6i) aw(3i).
mount	mount a device file system
swapon	add a swap device
umount	umount a file system
sync	flush system caches
reboot	reboot a machine
acct	specify accounting file
.TE
.in -5
.NH
System facilities
.LP
.h 2.1 "Generic operations
.in +5
.TS
lw(1.6i) aw(3i).
read	read data
write	write data
<sys/uio.h>	scatter-gather related definitions
readv	scattered data input
writev	gathered data output
<sys/ioctl.h>	standard control operations
ioctl	device control operation
.TE
.in -5
.h 2.2 "File system
.PP
Operations marked with a * exist in two forms: as shown,
operating on a file name, and operating on a file descriptor,
when the name is preceded with a ``f''.
.in +5
.TS
lw(1.6i) aw(3i).
<sys/file.h>	file system definitions
chdir	change directory
chroot	change root directory
mkdir	make a directory
rmdir	remove a directory
open	open a new or existing file
mknod	make a special file
portal\(dg	make a portal entry
unlink	remove a link
stat*	return status for a file	
lstat	returned status of link
chown*	change owner
chmod*	change mode
utimes	change access/modify times
link	make a hard link
symlink	make a symbolic link
readlink	read contents of symbolic link
rename	change name of file
lseek	reposition within file
truncate*	truncate file
access	determine accessibility
flock	lock a file
.TE
.in -5
.h 2.3 "Communications
.in +5
.TS
lw(1.6i) aw(3i).
<sys/socket.h>	standard definitions
socket	create socket
bind	bind socket to name
getsockname	get socket name
D 5
listen	allow queueing of connections
E 5
I 5
listen	allow queuing of connections
E 5
accept	accept a connection
connect	connect to peer socket
socketpair	create pair of connected sockets
sendto	send data to named socket
send	send data to connected socket
recvfrom	receive data on unconnected socket
recv	receive data on connected socket
sendmsg	send gathered data and/or rights
recvmsg	receive scattered data and/or rights
shutdown	partially close full-duplex connection
getsockopt	get socket option
setsockopt	set socket option
.TE
.in -5
D 3
.h 2.5 "Terminals, block and character devices
E 3
I 3
.h 2.4 "Terminals, block and character devices
E 3
.in +5
D 6
.TS
lw(1.6i) aw(3i).
.TE
E 6
.in -5
D 3
.h 2.4 "Processes and kernel hooks
E 3
I 3
.h 2.5 "Processes and kernel hooks
E 3
D 6
.in +5
.TS
lw(1.6i) aw(3i).
.TE
E 6
.in -5
E 9
I 9
.de L4
.nr l4 +1
.br
 	\\n(l1.\\n(l2.\\n(l3.\\n(l4	\\$1	\\$2
..
.de Nm
..
.ce 1
\s+4\fBContents\fP\s0
.sp 2
.ta \w'8.8.8.88\ \ 'uR +\w'\ \ \ 'u 6iR
.so Toc
.sy mv toc Toc
E 9
E 1
