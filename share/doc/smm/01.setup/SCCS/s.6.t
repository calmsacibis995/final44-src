h15196
s 00014/00002/00635
d D 8.2 94/06/01 19:46:49 ah 18 17
c page breaks for 4.4BSD manuals
e
s 00000/00000/00637
d D 8.1 93/07/27 18:58:57 mckusick 17 16
c 4.4BSD snapshot (revision 8.1)
e
s 00062/00056/00575
d D 6.14 93/07/27 18:16:28 mckusick 16 15
c convert from .NH to .Sh to get table of contents; add .PX request;
c typesetting and grammar changes from Keith's addition;
c discuss changes needed for shadow /sys/compile
e
s 00143/00088/00488
d D 6.13 93/07/26 10:57:30 bostic 15 14
c rework section on rebuilding system software to reflect new make(1)
e
s 00004/00003/00572
d D 6.12 93/07/21 18:40:46 mckusick 14 13
c formatting nits
e
s 00031/00016/00544
d D 6.11 93/07/20 16:22:22 bostic 13 12
c fix system build info
e
s 00001/00001/00559
d D 6.10 93/07/20 12:21:24 mckusick 12 11
c final edit pass
e
s 00003/00003/00557
d D 6.9 93/07/15 16:57:05 mckusick 11 10
c diction
e
s 00008/00011/00552
d D 6.8 93/07/12 22:42:41 mckusick 10 9
c nits discovered from reading
e
s 00002/00011/00561
d D 6.7 93/07/12 21:37:36 mckusick 9 8
c fix header
e
s 00200/00248/00372
d D 6.6 93/07/09 20:48:15 mckusick 8 6
c first pass at getting updated for 4.4BSD
e
s 00002/00002/00618
d R 8.1 93/06/08 13:57:02 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00618
d D 6.5 91/04/17 11:33:01 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00616
d D 6.4 89/03/07 13:20:39 bostic 5 4
c add Berkeley specific copyright, networking release
e
s 00118/00084/00501
d D 6.3 88/07/17 09:34:12 karels 4 3
c merge vax and tahoe versions
e
s 00001/00002/00584
d D 6.2 86/05/14 09:42:37 mckusick 3 2
c /usr/adm/shutdownlog disappears into the past
e
s 00091/00071/00495
d D 6.1 86/05/14 09:37:45 mckusick 2 1
c 4.3BSD release document
e
s 00566/00000/00000
d D 5.1 86/05/14 09:37:36 mckusick 1 0
c broken out of 0.t for 4.2BSD document
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1980 Regents of the University of California.
E 4
I 4
D 5
.\" Copyright (c) 1980,1986,1988 Regents of the University of California.
E 4
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 6
.\" Copyright (c) 1980, 1986, 1988 Regents of the University of California.
E 6
I 6
D 8
.\" Copyright (c) 1980, 1986, 1988 The Regents of the University of California.
E 8
I 8
.\" Copyright (c) 1980, 1986, 1988, 1993 The Regents of the University of California.
E 8
E 6
.\" All rights reserved.
.\"
D 6
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
E 6
I 6
.\" %sccs.include.redist.roff%
E 6
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
D 8
.de IR
\fI\\$1\fP\|\\$2
..
E 8
D 2
.ds LH "Installing/Operating 4.2BSD
E 2
I 2
.ds LH "Installing/Operating \*(4B
E 2
D 9
.nr H1 6
.nr H2 0
.ds RH "System Operation
E 9
D 8
.ds CF \*(DY
E 8
I 8
.ds CF \*(Dy
E 8
D 9
.bp
.LG
.B
.ce
6. SYSTEM OPERATION
.sp 2
.R
.NL
E 9
I 9
D 16
.NH 1
System Operation
E 16
I 16
.Sh 1 "System operation"
E 16
E 9
.PP
D 4
This section describes procedures used to operate a VAX UNIX system.
E 4
I 4
This section describes procedures used to operate a \*(4B UNIX system.
E 4
Procedures described here are used periodically, to reboot the system,
analyze error messages from devices, do disk backups, monitor
system performance, recompile system software and control local changes.
D 16
.NH 2
Bootstrap and shutdown procedures
E 16
I 16
.Sh 2 "Bootstrap and shutdown procedures"
E 16
.PP
In a normal reboot, the system checks the disks and comes up multi-user
without intervention at the console.
Such a reboot
can be stopped (after it prints the date) with a ^C (interrupt).
This will leave the system in single-user mode, with only the console
terminal active.
I 10
(If the console has been marked ``insecure'' in
.Pn /etc/ttys
you must enter the root password to bring the machine to single-user mode.)
E 10
I 2
It is also possible to allow the filesystem checks to complete
D 4
and then to return to single-user mode by signaling \fIfsck\fP
with a QUIT signal (^\).
E 4
I 4
D 8
and then to return to single-user mode by signaling \fIfsck\fP(8)
E 8
I 8
and then to return to single-user mode by signaling
.Xr fsck (8)
E 8
D 12
with a QUIT signal (^\\).
E 12
I 12
with a QUIT signal (^\|\e).
E 12
D 8
.if \n(Th \{\
E 8
E 4
E 2
.PP
D 8
If booting from the console command level is needed, then the command
.DS
D 4
\fB>>>\fP B
E 4
I 4
\fB#>\fP\|fb
E 4
.DE
will boot from the default device.
D 2
On an 11/780 (11/730) the default device is determined by a ``DEPOSIT''
command stored on the floppy (cassette) in the file ``DEFBOO.CMD'';
E 2
I 2
D 4
On an 8650, 8600, 11/785, 11/780, or 11/730 the default device is
E 4
I 4
.PP
You can boot a system up single user by doing
.DS
\fB#>\fP\fI\|p23 2.\fP\fB#>\fP\fIy.\fP\fB#>\fP\fI\|fb\fP
.DE
.PP
Other possibilities are:
.DS
\fB#>\fP\fI\|p23 3.\fP\fB#>\fP\fIy.\fP\fB#>\fP\fI\|fb\fP
.DE
to do a full bootstrap, or
.DS
\fB#>\fP\fI\|p23 3.\fP\fB#>\fP\fIy.\fP\fB#>\fP\fI\|fr /boot\fP
.DE
to run the bootstrap without performing self-tests and
reloading microcode; it can be used after a full bootstrap has been done
once.
.\}
.if \n(Vx \{\
.PP
If booting from the console command level is needed, then the command
.DS
\fB>>>\fP\fIB\fP
.DE
will boot from the default device.
On an 8600, 8200, 11/780, or 11/730 the default device is
E 4
determined by a ``DEPOSIT''
command stored on the console boot device in the file ``DEFBOO.CMD''
D 4
(``DEFBOO.COM'' on an 8650 or 8600);
E 4
I 4
(``DEFBOO.COM'' on an 8600);
E 4
E 2
on an 11/750 the default device is determined by the setting of a switch
on the front panel.
.PP
D 2
You can boot a system up single user on a 780 or 730 by doing
E 2
I 2
You can boot a system up single user
D 4
on an 8650, 8600, 785, 780, or 730 by doing
E 4
I 4
on an 8600, 780, or 730 by doing
E 4
E 2
.DS
D 4
\fB>>>\fP B \fIXX\fP\|S
E 4
I 4
\fB>>>\fP\fIB xxS\fP
E 4
.DE
D 4
where \fIXX\fP is one of HP, HK, UP, RA, or RB for a 730.
E 4
I 4
where \fIxx\fP is one of HP, HK, UP, RA, or RB.
E 4
The corresponding command on an 11/750 is
.DS
D 2
\fB>>>\fP B/1
E 2
I 2
D 4
\fB>>>\fP B/2
E 4
I 4
\fB>>>\fP\fIB/2\fP
E 4
E 2
.DE
I 4
On an 8200, use
.DS
\fB>>>\fP\fIB/R5:800\fP
(node and memory test values)
\fBBOOT58>\fP \fI@\fPXX\fISBOO.CMD\fP
.DE
E 4
.PP
For second vendor storage modules on the
UNIBUS or MASSBUS of an 11/750 you will need to
have a boot prom.  Most vendors will sell you
such proms for their controllers; contact your vendor
if you don't have one.
.PP
Other possibilities are:
.DS
D 4
\fB>>>\fP B ANY
E 4
I 4
\fB>>>\fP\fIB ANY\fP
E 4
.DE
D 4
or, on a 750
E 4
I 4
or, on an 8200,
E 4
.DS
D 4
\fB>>>\fP B/3
E 4
I 4
\fB>>>\fP\fIB/R5:800\fP
\fBBOOT58>\fP\fI@ANYBOO.CMD\fP
E 4
.DE
I 4
or, on an 11/750
.DS
\fB>>>\fP\fIB/3\fP
.DE
.\}
E 4
These commands boot and ask for the name of the system to be booted.
They can be used after building a new test system to give the
D 4
boot program the name of the test version of the system.
E 4
I 4
boot program the name of the test version of the system.*
.FS
* Additional bootflags are used when a system is configured with
the kernel debugger; consult \fIkdb\fP(4) for details.
.FE
E 4
.PP
E 8
To bring the system up to a multi-user configuration from the single-user
D 2
status after, e.g., a ``B HPS'' on an 11/780, ``B RBS'' on a 730,
or a ``B/1'' on an
E 2
I 2
D 4
status after, e.g., a ``B HPS'' on an 8650, 8600, 11/785 or 11/780, ``B RBS''
on a 11/730, or a ``B/2'' on an
E 2
11/750 all you have to do is hit ^D on the console.  The system
E 4
I 4
status,
all you have to do is hit ^D on the console.  The system
E 4
D 8
will then execute /etc/rc,
a multi-user restart script (and /etc/rc.local),
E 8
I 8
will then execute
.Pn /etc/rc ,
a multi-user restart script (and
.Pn /etc/rc.local ),
E 8
and come up on the terminals listed as
D 8
active in the file /etc/ttys.
E 8
I 8
active in the file
.Pn /etc/ttys .
E 8
See
D 8
\fIinit\fP\|(8)
E 8
I 8
.Xr init (8)
E 8
and
D 4
\fIttys\fP\|(5).
E 4
I 4
D 8
\fIttys\fP\|(5) for more details.
E 4
Note, however, that this does not cause a file system check to be performed.
E 8
I 8
.Xr ttys (5) for more details.
D 16
Note, however, that this does not cause a filesystem check to be performed.
E 16
I 16
Note, however, that this does not cause a filesystem check to be done.
E 16
E 8
Unless the system was taken down cleanly, you should run
``fsck \-p'' or force a reboot with
D 8
\fIreboot\fP\|(8)
E 8
I 8
.Xr reboot (8)
E 8
to have the disks checked.
I 18
.ne 1i
E 18
.PP
To take the system down to a single user state you can use
.DS
D 4
\fB#\fP kill 1
E 4
I 4
\fB#\fP \fIkill 1\fP
E 4
.DE
or use the
D 8
\fIshutdown\fP\|(8)
E 8
I 8
.Xr shutdown (8)
E 8
D 4
command (which is much more polite, if there are other users logged in.)
when you are up multi-user.
E 4
I 4
command (which is much more polite, if there are other users logged in)
when you are running multi-user.
E 4
Either command will kill all processes and give you a shell on the console,
D 8
as if you had just booted.  File systems remain mounted after the
E 8
I 8
as if you had just booted.  Filesystems remain mounted after the
E 8
system is taken single-user.  If you wish to come up multi-user again, you
should do this by:
.DS
D 4
\fB#\fP cd /
\fB#\fP /etc/umount -a
\fB#\fP ^D
E 4
I 4
\fB#\fP \fIcd /\fP
D 8
\fB#\fP \fI/etc/umount -a\fP
E 8
I 8
\fB#\fP \fI/sbin/umount -a\fP
E 8
\fB#\fP \fI^D\fP
E 4
.DE
.PP
Each system shutdown, crash, processor halt and reboot
D 3
is recorded in the file /usr/adm/shutdownlog
E 3
I 3
is recorded in the system log
E 3
D 4
with the cause.
E 4
I 4
with its cause.
E 4
D 16
.NH 2
Device errors and diagnostics
E 16
I 16
.Sh 2 "Device errors and diagnostics"
E 16
.PP
D 2
When errors occur on peripherals or in the system, the system
prints a warning diagnostic on the console.  These messages are collected
regularly and written into a system error log file
/usr/adm/messages.
E 2
I 2
When serious errors occur on peripherals or in the system, the system
prints a warning diagnostic on the console.
These messages are collected
by the system error logging process
D 8
.IR syslogd (8)
E 8
I 8
.Xr syslogd (8)
E 8
and written into a system error log file
D 8
\fI/usr/adm/messages\fP.
Less serious errors are sent directly to \fIsyslogd\fP,
E 8
I 8
.Pn /var/log/messages .
Less serious errors are sent directly to
.Xr syslogd ,
E 8
which may log them on the console.
The error priorities that are logged and the locations to which they are logged
D 8
are controlled by \fI/etc/syslog.conf\fP.  See
.IR syslogd (8)
E 8
I 8
are controlled by
.Pn /etc/syslog.conf .
See
.Xr syslogd (8)
E 8
D 4
for details.
E 4
I 4
for further details.
E 4
E 2
.PP
Error messages printed by the devices in the system are described with the
drivers for the devices in section 4 of the programmer's manual.
D 2
If errors occur indicating hardware problems, you should contact
E 2
I 2
If errors occur suggesting hardware problems, you should contact
E 2
your hardware support group or field service.  It is a good idea to
examine the error log file regularly
D 2
(e.g. with ``tail \-r /usr/adm/messages'').
E 2
I 2
D 4
(e.g. with ``tail \-r \fI/usr/adm/messages\fP'').
E 4
I 4
D 8
(e.g. with the command \fItail \-r /usr/adm/messages\fP).
E 8
I 8
(e.g. with the command \fItail \-r /var/log/messages\fP).
E 8
E 4
E 2
D 16
.NH 2
D 8
File system checks, backups and disaster recovery
E 8
I 8
Filesystem checks, backups and disaster recovery
E 16
I 16
.Sh 2 "Filesystem checks, backups, and disaster recovery"
E 16
E 8
.PP
Periodically (say every week or so in the absence of any problems)
and always (usually automatically) after a crash,
D 8
all the file systems should be checked for consistency
E 8
I 8
all the filesystems should be checked for consistency
E 8
by
D 8
\fIfsck\fP\|(1).
E 8
I 8
.Xr fsck (1).
E 8
The procedures of
D 8
\fIreboot\fP\|(8)
should be used to get the system to a state where a file system
E 8
I 8
.Xr reboot (8)
should be used to get the system to a state where a filesystem
E 8
D 16
check can be performed manually or automatically.
E 16
I 16
check can be done manually or automatically.
E 16
.PP
D 8
Dumping of the file systems should be done regularly,
E 8
I 8
Dumping of the filesystems should be done regularly,
E 8
since once the system is going it is easy to
become complacent.
Complete and incremental dumps are easily done with
D 8
\fIdump\fP\|(8).
E 8
I 8
.Xr dump (8).
E 8
You should arrange to do a towers-of-hanoi dump sequence; we tune
ours so that almost all files are dumped on two tapes and kept for at
least a week in most every case.  We take full dumps every month (and keep
these indefinitely).
Operators can execute ``dump w'' at login that will tell them what needs
to be dumped
D 8
(based on the /etc/fstab
E 8
I 8
(based on the
.Pn /etc/fstab
E 8
information).
Be sure to create a group
.B operator
D 8
in the file /etc/group
E 8
I 8
in the file
.Pn /etc/group
E 8
so that dump can notify logged-in operators when it needs help.
.PP
More precisely, we have three sets of dump tapes: 10 daily tapes,
5 weekly sets of 2 tapes, and fresh sets of three tapes monthly.
We do daily dumps circularly on the daily tapes with sequence
`3 2 5 4 7 6 9 8 9 9 9 ...'.
Each weekly is a level 1 and the daily dump sequence level
restarts after each weekly dump.
Full dumps are level 0 and the daily sequence restarts after each full dump
also.
.PP
Thus a typical dump sequence would be:
.br
.ne 6
I 2
D 10
.KS
E 10
E 2
.TS
center;
c c c c c
n n n l l.
tape name	level number	date	opr	size
_
D 8
FULL	0	Nov 24, 1979	jkf	137K
D1	3	Nov 28, 1979	jkf	29K
D2	2	Nov 29, 1979	rrh	34K
D3	5	Nov 30, 1979	rrh	19K
D4	4	Dec 1, 1979	rrh	22K
W1	1	Dec 2, 1979	etc	40K
D5	3	Dec 4, 1979	rrh	15K
D6	2	Dec 5, 1979	jkf	25K
D7	5	Dec 6, 1979	jkf	15K
D8	4	Dec 7, 1979	rrh	19K
W2	1	Dec 9, 1979	etc	118K
D9	3	Dec 11, 1979	rrh	15K
D10	2	Dec 12, 1979	rrh	26K
D1	5	Dec 15, 1979	rrh	14K
W3	1	Dec 17, 1979	etc	71K
D2	3	Dec 18, 1979	etc	13K
FULL	0	Dec 22, 1979	etc	135K
E 8
I 8
FULL	0	Nov 24, 1992	operator	137K
D1	3	Nov 28, 1992	operator	29K
D2	2	Nov 29, 1992	operator	34K
D3	5	Nov 30, 1992	operator	19K
D4	4	Dec 1, 1992	operator	22K
W1	1	Dec 2, 1992	operator	40K
D5	3	Dec 4, 1992	operator	15K
D6	2	Dec 5, 1992	operator	25K
D7	5	Dec 6, 1992	operator	15K
D8	4	Dec 7, 1992	operator	19K
W2	1	Dec 9, 1992	operator	118K
D9	3	Dec 11, 1992	operator	15K
D10	2	Dec 12, 1992	operator	26K
D1	5	Dec 15, 1992	operator	14K
W3	1	Dec 17, 1992	operator	71K
D2	3	Dec 18, 1992	operator	13K
FULL	0	Dec 22, 1992	operator	135K
E 8
.TE
D 2
We do weekly's often enough that daily's always fit on one tape and
never get to the sequence of 9's in the daily level numbers.
E 2
I 2
D 10
.KE
E 10
We do weekly dumps often enough that daily dumps always fit on one tape.
E 2
.PP
Dumping of files by name is best done by
D 8
\fItar\fP\|(1)
E 8
I 8
.Xr tar (1)
E 8
but the amount of data that can be moved in this way is limited
to a single tape.
Finally if there are enough drives entire
disks can be copied with
D 8
\fIdd\fP\|(1)
E 8
I 8
.Xr dd (1)
E 8
using the raw special files and an appropriate
blocking factor; the number of sectors per track is usually
D 2
a good value to use, consult /etc/disktab.
E 2
I 2
D 8
a good value to use, consult \fI/etc/disktab\fP.
E 8
I 8
a good value to use, consult
.Pn /etc/disktab .
E 8
E 2
.PP
D 8
It is desirable that full dumps of the root file system be
E 8
I 8
It is desirable that full dumps of the root filesystem be
E 8
made regularly.
This is especially true when only one disk is available.
Then, if the
D 8
root file system is damaged by a hardware or software failure, you
E 8
I 8
root filesystem is damaged by a hardware or software failure, you
E 8
can rebuild a workable disk doing a restore in the
D 8
same way that the initial root file system was created.
E 8
I 8
same way that the initial root filesystem was created.
E 8
.PP
Exhaustion of user-file space is certain to occur
now and then; disk quotas may be imposed, or if you
D 4
prefer a less facist approach, try using the programs
E 4
I 4
prefer a less fascist approach, try using the programs
E 4
D 8
\fIdu\fP\|(1),
D 4
\fIdf\fP\|(1),
E 4
I 4
\fIdf\fP\|(1), and
E 4
\fIquot\fP\|(8),
E 8
I 8
.Xr du (1),
.Xr df (1),
and
.Xr quot (8),
E 8
combined with threatening
messages of the day, and personal letters.
D 16
.NH 2
D 2
Moving filesystem data
E 2
I 2
D 8
Moving file system data
E 8
I 8
Moving filesystem data
E 16
I 16
.Sh 2 "Moving filesystem data"
E 16
E 8
E 2
.PP
D 4
If you have the equipment,
E 4
I 4
If you have the resources,
E 4
D 8
the best way to move a file system
E 8
I 8
the best way to move a filesystem
E 8
D 4
is to dump it to magtape using
\fIdump\fP\|(8),
use
\fInewfs\fP\|(8)
to create the new file system,
and restore the tape, using \fIrestore\fP\|(8).
If for some reason you don't want to use magtape,
dump accepts an argument telling where to put the dump;
you might use another disk.
E 4
I 4
is to dump it to a spare disk partition, or magtape, using
D 8
\fIdump\fP\|(8), use \fInewfs\fP\|(8) to create the new file system,
and restore the file system using \fIrestore\fP\|(8).
E 4
D 2
The restore program uses an ``in-place'' algorithm which
E 2
I 2
Filesystems may also be moved by piping the output of \fIdump\fP
to \fIrestore\fP.
The \fIrestore\fP program uses an ``in-place'' algorithm that
E 2
allows file system dumps to be restored without concern for the
original size of the file system.  Further, portions of a
D 2
file system may be selectively restored in a manner similar
E 2
I 2
file system may be selectively restored using a method similar
E 8
I 8
.Xr dump (8),
use
.Xr newfs (8)
to create the new filesystem,
and restore the filesystem using
.Xr restore (8).
Filesystems may also be moved by piping the output of
.Xr dump
to
.Xr restore .
The
.Xr restore
program uses an ``in-place'' algorithm that
allows filesystem dumps to be restored without concern for the
original size of the filesystem.  Further, portions of a
filesystem may be selectively restored using a method similar
E 8
E 2
to the tape archive program.
.PP
D 8
If you have to merge a file system into another, existing one,
the best bet is to
use \fItar\fP\|(1).
If you must shrink a file system, the best bet is to dump
the original and restore it onto the new file system.
E 8
I 8
If you have to merge a filesystem into another, existing one,
the best bet is to use
.Xr tar (1).
If you must shrink a filesystem, the best bet is to dump
the original and restore it onto the new filesystem.
E 8
If you
D 8
are playing with the root file system and only have one drive,
E 8
I 8
are playing with the root filesystem and only have one drive,
E 8
the procedure is more complicated.
I 2
If the only drive is a Winchester disk, this procedure may not be used
without overwriting the existing root or another partition.
E 2
What you do is the following:
.IP 1.
D 4
GET A SECOND PACK!!!!
E 4
I 4
GET A SECOND PACK, OR USE ANOTHER DISK DRIVE!!!!
E 4
.IP 2.
D 8
Dump the root file system to tape using
\fIdump\fP\|(8).
E 8
I 8
Dump the root filesystem to tape using
.Xr dump (8).
E 8
.IP 3.
D 4
Bring the system down and mount the new pack.
E 4
I 4
Bring the system down.
E 4
.IP 4.
I 4
Mount the new pack in the correct disk drive, if
using removable media.
.IP 5.
E 4
Load the distribution tape and install the new
D 8
root file system as you did when first installing the system.
E 8
I 8
root filesystem as you did when first installing the system.
E 8
D 4
.IP 5.
E 4
Boot normally
D 8
using the newly created disk file system.
E 8
I 8
using the newly created disk filesystem.
E 8
.PP
Note that if you change the disk partition tables or add new disk
drivers they should also be added to the standalone system in
D 2
/sys/stand and the default disk partition tables in /etc/disktab
E 2
I 2
D 4
\fI/sys/stand\fP and the default disk partition tables in \fI/etc/disktab\fP
E 4
I 4
D 8
\fI/sys/\*(mCstand\fP,
and the default disk partition tables in \fI/etc/disktab\fP
E 8
I 8
.Pn /sys/<architecture>/stand ,
and the default disk partition tables in
.Pn /etc/disktab
E 8
E 4
E 2
should be modified.
D 16
.NH 2
Monitoring System Performance
E 16
I 16
.Sh 2 "Monitoring system performance"
E 16
.PP
The
D 2
.I vmstat
E 2
I 2
D 8
.I systat
E 8
I 8
.Xr systat
E 8
E 2
program provided with the system is designed to be an aid to monitoring
D 2
systemwide activity.  Together with the
\fIps\fP\|(1)
command (as in ``ps av''), it can be used to investigate systemwide
virtual memory activity.
By running
.I vmstat
E 2
I 2
systemwide activity.  The default ``pigs'' mode shows a dynamic ``ps''.
By running in the ``vmstat'' mode
E 2
when the system is active you can judge the system activity in several
dimensions: job distribution, virtual memory load, paging and swapping
D 2
activity, disk and cpu utilization.
E 2
I 2
activity, device interrupts, and disk and cpu utilization.
E 2
Ideally, there should be few blocked (b) jobs,
there should be little paging or swapping activity, there should
be available bandwidth on the disk devices (most single arms peak
D 2
out at 30-35 tps in practice), and the user cpu utilization (us) should
be high (above 60%).
E 2
I 2
out at 20-30 tps in practice), and the user cpu utilization (us) should
be high (above 50%).
E 2
.PP
If the system is busy, then the count of active jobs may be large,
and several of these jobs may often be blocked (b).  If the virtual
memory is active, then the paging demon will be running (sr will
be non-zero).  It is healthy for the paging demon to free pages when
the virtual memory gets active; it is triggered by the amount of free
memory dropping below a threshold and increases its pace as free memory
goes to zero.
.PP
D 2
If you run
.I vmstat
when the system is busy (a ``vmstat 1'' gives all the
numbers computed by the system), you can find
E 2
I 2
If you run in the ``vmstat'' mode
when the system is busy, you can find
E 2
imbalances by noting abnormal job distributions.  If many
processes are blocked (b), then the disk subsystem
D 2
is overloaded or imbalanced.  If you have a several non-dma
E 2
I 2
is overloaded or imbalanced.  If you have several non-dma
E 2
devices or open teletype lines that are ``ringing'', or user programs
that are doing high-speed non-buffered input/output, then the system
time may go high (60-70% or higher).
It is often possible to pin down the cause of high system time by
looking to see if there is excessive context switching (cs), interrupt
D 2
activity (in) or system call activity (sy).  Cumulatively on one of
our large machines we average about 60 context switches and interrupts
per second and about 90 system calls per second.
E 2
I 2
activity (in) and per-device interrupt counts,
or system call activity (sy).  Cumulatively on one of
D 8
our large machines we average about 60-100 context switches and interrupts
per second and about 70-120 system calls per second.
E 8
I 8
our large machines we average about 60-200 context switches and interrupts
per second and about 50-500 system calls per second.
E 8
E 2
.PP
If the system is heavily loaded, or if you have little memory
D 2
for your load (1M is little in most any case), then the system
E 2
I 2
for your load (2M is little in most any case), then the system
E 2
may be forced to swap.  This is likely to be accompanied by a noticeable
reduction in system performance and pregnant pauses when interactive
jobs such as editors swap out.
If you expect to be in a memory-poor environment
for an extended period you might consider administratively
limiting system load.
D 16
.NH 2
Recompiling and reinstalling system software
E 16
I 16
.Sh 2 "Recompiling and reinstalling system software"
E 16
.PP
D 15
It is easy to regenerate the system, and it is a good
idea to try rebuilding pieces of the system to build confidence
in the procedures.
The system consists of two major parts:
the kernel itself (/sys) and the user programs
(/usr/src and subdirectories).
D 8
The major part of this is /usr/src.
E 8
I 8
The major part of this is
E 15
I 15
It is easy to regenerate either the entire system or a single utility,
and it is a good idea to try rebuilding pieces of the system to build
confidence in the procedures.
D 16
.PP
E 16
I 16
.LP
E 16
In general, there are six well-known targets supported by
D 16
all of the makefiles on the system:
.IP \(bu
all
This is the default target, the same as if no target is specified.
E 16
I 16
all the makefiles on the system:
.IP all 9
This entry is the default target, the same as if no target is specified.
E 16
This target builds the kernel, binary or library, as well as its
associated manual pages.
This target \fBdoes not\fP build the dependency files.
Some of the utilities require that a \fImake depend\fP be done before
a \fImake all\fP can succeed.
D 16
.IP \(bu
depend
E 16
I 16
.IP depend
E 16
Build the include file dependency file, ``.depend'', which is
read by
.Xr make .
See
.Xr mkdep (1)
for further details.
D 16
.IP \(bu
install
E 16
I 16
.IP install
E 16
Install the kernel, binary or library, as well as its associated
manual pages.
See
.Xr install (1)
for further details.
D 16
.IP \(bu
clean
E 16
I 16
.IP clean
E 16
Remove the kernel, binary or library, as well as any object files
created when building it.
D 16
.IP \(bu
cleandir
E 16
I 16
.IP cleandir
E 16
The same as clean, except that the dependency files and formatted
manual pages are removed as well.
D 16
.IP \(bu
obj
E 16
I 16
.IP obj
E 16
Build a shadow directory structure in the area referenced by
.Pn /usr/obj
and create a symbolic link in the current source directory to
referenced it, named ``obj''.
D 16
Once this shadow structure has been created, all of the files
created by
E 16
I 16
Once this shadow structure has been created, all the files created by
E 16
.Xr make
will live in the shadow structure, and
.Pn /usr/src
may be mounted read-only by multiple machines.
Doing a \fImake obj\fP in
.Pn /usr/src
will build the shadow directory structure for everything on the
D 16
system except for the contributed, deprecated and kernel software.
E 16
I 16
system except for the contributed, old, and kernel software.
E 16
.PP
The system consists of three major parts:
the kernel itself, found in
.Pn /usr/src/sys ,
the libraries , found in
.Pn /usr/src/lib ,
and the user programs (the rest of
.Pn /usr/src ).
.PP
Deprecated software, found in
.Pn /usr/src/old ,
D 16
often has old style makefiles, as well as not compiling under \*(4B
at all.
E 16
I 16
often has old style makefiles;
some of it does not compile under \*(4B at all.
E 16
.PP
Contributed software, found in
.Pn /usr/src/contrib ,
D 16
usually doesn't support the ``cleandir'', ``depend'', or ``obj'' targets.
E 16
I 16
usually does not support the ``cleandir'', ``depend'', or ``obj'' targets.
E 16
.PP
D 16
The kernel doesn't support the ``obj'' shadow structure.
E 16
I 16
The kernel does not support the ``obj'' shadow structure.
E 16
All kernels are compiled in subdirectories of
D 16
.Pn /usr/src/compile .
E 16
I 16
.Pn /usr/src/sys/compile
which is usually abbreviated as
.Pn /sys/compile .
E 16
If you want to mount your source tree read-only,
D 16
.Pn /usr/src/compile
will have to be on a separate file system from
E 16
I 16
.Pn /usr/src/sys/compile
will have to be on a separate filesystem from
E 16
E 15
.Pn /usr/src .
I 16
Separation from
.Pn /usr/src
can be done by making
.Pn /usr/src/sys/compile
a symbolic link that references
.Pn /usr/obj/sys/compile .
If it is a symbolic link, the \fIS\fP variable in the kernel
Makefile must be changed from
.Pn \&../..
to the absolute pathname needed to locate the kernel sources, usually
.Pn /usr/src/sys .
The symbolic link created by
.Xr config (8)
for
.Pn machine
must also be manually changed to an absolute pathname.
Finally, the
.Pn /usr/src/sys/libkern/obj
directory must be located in
.Pn /usr/obj/sys/libkern .
E 16
E 8
.PP
D 8
The three major libraries are the C library in /usr/src/lib/libc
and the \s-2FORTRAN\s0 libraries /usr/src/usr.lib/libI77 and
/usr/src/usr.lib/libF77.  In each
case the library is remade by changing into the corresponding directory
and doing
E 8
I 8
D 15
The major library is the C library in
.Pn /usr/src/lib/libc .
The library is remade by changing into the
.Pn libc
directory and doing
E 15
I 15
Each of the standard utilities and libraries may be built and
installed by changing directories into the correct location and
doing:
E 15
E 8
.DS
D 4
\fB#\fP make
E 4
I 4
\fB#\fP \fImake\fP
E 4
D 15
.DE
and then installed by
.DS
E 15
D 4
\fB#\fP make install
E 4
I 4
\fB#\fP \fImake install\fP
E 4
.DE
D 15
Similar to the system,
E 15
I 15
Note, if system include files have changed between compiles,
.Xr make
D 16
will not perform the correct dependency checks if the dependency
E 16
I 16
will not do the correct dependency checks if the dependency
E 16
files have not been built using the ``depend'' target.
.PP
The entire library and utility suite for the system may be recompiled
from scratch by changing directory to
.Pn /usr/src
and doing:
E 15
.DS
D 4
\fB#\fP make clean
E 4
I 4
D 15
\fB#\fP \fImake clean\fP
E 15
I 15
\fB#\fP \fImake build\fP
E 15
E 4
.DE
D 15
cleans up.
E 15
I 15
This target installs the system include files, cleans the source
tree, builds and installs the libraries, and builds and installs
the system utilities.
E 15
.PP
D 15
The source for all other libraries is kept in subdirectories of
D 8
/usr/src/usr.lib; each has a makefile and can be recompiled by the above
E 8
I 8
/usr/src/lib; each has a makefile and can be recompiled by the above
E 8
recipe.
.PP
D 8
If you look at /usr/src/Makefile, you will see that
you can recompile the entire system source with one command.
E 8
I 8
If you look at
.Pn /usr/src/Makefile ,
you will see that you can recompile the entire system source with one command.
E 8
To recompile a specific program, find
D 8
out where the source resides with the \fIwhereis\fP\|(1)
E 8
I 8
out where the source resides with the
E 15
I 15
To recompile a specific program, first determine where the binary
resides with the
E 15
.Xr whereis (1)
E 8
D 15
command, then change to that directory and remake it
D 4
with the makefile present in the directory.
E 4
I 4
with the Makefile present in the directory.
E 4
For instance, to recompile ``date'', 
all one has to do is
E 15
I 15
command, then change to the corresponding source directory and build
it with the Makefile in the directory.
D 16
For instance, to recompile ``passwd'', 
E 16
I 16
For instance, to recompile ``passwd'',
E 16
all one has to do is:
E 15
.DS
D 4
\fB#\fP whereis date
\fBdate: /usr/src/bin/date.c /bin/date /usr/man/man1/date.1\fP
\fB#\fP cd /usr/src/bin
\fB#\fP make date
E 4
I 4
D 15
\fB#\fP \fIwhereis date\fP
D 8
\fBdate: /usr/src/bin/date.c /bin/date\fP
\fB#\fP \fIcd /usr/src/bin\fP
E 8
I 8
\fBdate: /bin/date\fP
\fB#\fP \fIcd /usr/src/bin/date\fP
E 8
\fB#\fP \fImake date\fP
E 15
I 15
\fB#\fP \fIwhereis passwd\fP
\fB/usr/bin/passwd\fP
\fB#\fP \fIcd /usr/src/usr.bin/passwd\fP
\fB#\fP \fImake\fP
\fB#\fP \fImake install\fP
E 15
E 4
.DE
D 15
this will create an unstripped version of the binary of ``date''
in the current directory.  To install the binary image, use the
install command as in
.DS
D 4
\fB#\fP install \-s date /bin/date
E 4
I 4
\fB#\fP \fIinstall \-s date -o bin -g bin -m 755 /bin/date\fP
E 4
.DE
The \-s option will insure the installed version of date has
its symbol table stripped.  The install command should be used
D 13
instead of mv or cp as it understands how to install programs
E 13
I 13
instead of
.Xr mv (1)
or
D 14
.Xr cp (1) as it understands how to install programs
E 14
I 14
.Xr cp (1)
as it understands how to install programs
E 14
E 13
even when the program is currently in use.
E 15
I 15
this will compile and install the
.Xr passwd
utility.
E 15
.PP
D 13
If you wish to recompile and install all programs in a particular
target area you can override the default target by doing:
E 13
I 13
If you wish to recompile and install all programs into a particular
target area you can override the default path prefix by doing:
E 13
.DS
D 4
\fB#\fP make
\fB#\fP make DESTDIR=\fIpathname\fP install
E 4
I 4
\fB#\fP \fImake\fP
\fB#\fP \fImake DESTDIR=\fPpathname \fIinstall\fP
E 4
.DE
I 15
Similarly, the mode, owner, group, and other characteristics of
the installed object can be modified by changing other default
make variables.
See
.Xr make (1),
.Pn /usr/src/share/mk/bsd.README ,
and the ``.mk'' scripts in the
.Pn /usr/share/mk
directory for more information.
E 15
.PP
D 13
To regenerate all the system source you can do
E 13
I 13
D 15
To regenerate all the system binaries you can do
E 15
I 15
If you modify the C library or system include files, to change a
system call for example, and want to rebuild and install everything,
you have to be a little careful.
D 16
You must insure that the include files are installed before anything
E 16
I 16
You must ensure that the include files are installed before anything
E 16
is compiled, and that the libraries are installed before the remainder
of the source, otherwise the loaded images will not contain the new
routine from the library.
If include files have been modified, the following commands should
be done first:
E 15
E 13
.DS
D 4
\fB#\fP cd /usr/src
\fB#\fP make
E 4
I 4
D 15
\fB#\fP \fIcd /usr/src\fP
D 13
\fB#\fP \fImake clean; make depend; make\fP
E 13
I 13
\fB#\fP \fImake clean depend all\fP
E 15
I 15
\fB#\fP \fIcd /usr/src/include\fP
\fB#\fP \fImake install\fP
E 15
E 13
E 4
.DE
D 15
.PP
I 13
The additional target
E 15
I 15
Then, if, for example, C library files have been modified, the
following commands should be executed:
E 15
D 18
.DS
E 18
I 18
.sp
.in
E 18
D 14
\fB#\fP \fImake cleandir\P
E 14
I 14
D 15
\fB#\fP \fImake cleandir\fP
E 14
.DE
not only removes the binaries and objects, but the dependency
files and the formatted manual pages as well.
The command \fImake depend\fP regenerates the dependency files,
and the next make which builds the binary will also rebuild the
formatted manual pages.
.PP
E 13
If you modify the C library, say to change a system call,
and want to rebuild and install everything from scratch you
have to be a little careful.
D 2
You must insure the libraries are installed before the
E 2
I 2
You must insure that the libraries are installed before the
E 2
remainder of the source, otherwise the loaded images will not
D 13
contain the new routine from the library.  The following
D 2
steps are recommended.
E 2
I 2
sequence will accomplish this.
E 13
I 13
contain the new routine from the library.
D 14
The following sequence will accomplish this.
E 14
I 14
The following sequence will accomplish this task.
E 14
E 13
E 2
.DS
E 15
I 13
\fB#\fP \fIcd /usr/src/lib/libc\fP
I 18
.br
E 18
D 15
\fB#\fP \fImake clean depend install\fP
E 15
I 15
\fB#\fP \fImake depend\fP
I 18
.br
E 18
\fB#\fP \fImake\fP
I 18
.br
E 18
\fB#\fP \fImake install\fP
I 18
.ne 1i
.in +2
E 18
E 15
E 13
D 4
\fB#\fP cd /usr/src
D 2
\fB#\fP cd lib; make install
\fB#\fP cd ..
\fB#\fP make usr.lib
\fB#\fP cd usr.lib; make install
\fB#\fP cd ..
\fB#\fP make bin etc usr.bin ucb games local
\fB#\fP for i in bin etc usr.bin ucb games local; do (cd $i; make install); done
E 2
I 2
\fB#\fP make clean
\fB#\fP make build
\fB#\fP make installsrc
E 4
I 4
\fB#\fP \fIcd /usr/src\fP
I 18
.br
E 18
D 13
\fB#\fP \fImake clean\fP
\fB#\fP \fImake depend\fP
\fB#\fP \fImake build\fP
\fB#\fP \fImake installsrc\fP
E 13
I 13
D 15
\fB#\fP \fImake clean depend install\fP
E 15
I 15
\fB#\fP \fImake depend\fP
I 18
.br
E 18
\fB#\fP \fImake\fP
I 18
.br
E 18
\fB#\fP \fImake install\fP
E 15
E 13
E 4
E 2
D 18
.DE
E 18
I 18
.br
.in 0
.sp
E 18
D 2
This will take about 12 hours on a reasonably configured 11/750.
E 2
I 2
D 4
The first \fImake\fP removes any existing binaries in the source trees
to insure that everything is reloaded.
The next \fImake\fP compiles and installs the libraries and compilers,
then compiles the remainder of the sources.
The final line installs all of the commands not installed in the first phase.
This will take about 18 hours on a reasonably configured 11/750.
E 4
I 4
D 15
The \fImake clean\fP removes any existing binary or object files in the source
trees to insure that everything will be recompiled and reloaded.  The \fImake
D 8
depend\fP recreates all of the dependencies.  See \fImkdep\fP(1) for
further details. The \fImake build\fP compiles and installs the libraries
E 8
I 8
D 11
depend\fP recreates all of the dependencies.  See
E 11
I 11
depend\fP recreates all the dependencies.  See
E 11
.Xr mkdep (1)
D 13
for further details. The \fImake build\fP compiles and installs the libraries
E 8
and compilers, then recompiles the libraries and compilers and the remainder
D 11
of the sources.  The \fImake installsrc\fP installs all of the commands not
E 11
I 11
of the sources.  The \fImake installsrc\fP installs all the commands not
E 11
installed as part of the \fImake build\fP.
D 8
.if \n(Th \{\
This will take approximately 10
hours on a reasonably configured Tahoe.
.\}
E 8
I 8
The build will take several hours on a reasonably configured machine.
E 13
I 13
for further details.
.PP
Alternatively, the command \fImake build\fP in the
.Pn /usr/src/
directory will install the include files, and then build and
install the libraries, and then build and install the system binaries
and manual pages.
E 15
I 15
Alternatively, the \fImake build\fP command described above will
accomplish the same tasks.
E 15
This takes several hours on a reasonably configured machine.
E 13
E 8
E 4
E 2
D 16
.NH 2
Making local modifications
E 16
I 16
.Sh 2 "Making local modifications"
E 16
.PP
D 4
To keep track of changes to system source we migrate changed
versions of commands in /usr/src/bin, /usr/src/usr.bin, and /usr/src/ucb
in through the directory /usr/src/new
and out of the original directory into /usr/src/old for
a time before removing them.
I 2
(/usr/new is also used by default for the programs that constitute
the contributed software portion of the distribution.)
E 4
E 2
D 8
Locally written commands that aren't distributed are kept in /usr/src/local
and their binaries are kept in /usr/local.  This allows /usr/bin, /usr/ucb,
and /bin to correspond to the distribution tape (and to the manuals that
E 8
I 8
D 15
Locally written commands that aren't distributed are kept in
.Pn /usr/src/local
E 15
I 15
The source for locally written commands is normally stored in
.Pn /usr/src/local ,
E 15
and their binaries are kept in
.Pn /usr/local/bin .
This isolation of local binaries allows
.Pn /usr/bin ,
and
.Pn /bin
to correspond to the distribution tape (and to the manuals that
E 8
D 4
people can buy).  People wishing to use /usr/local commands are made
aware that they aren't in the base manual.  As manual updates incorporate
these commands they are moved to /usr/ucb.
.PP
D 2
A directory /usr/junk to throw garbage into, as well as binary directories
/usr/old and /usr/new are useful.  The man command supports manual
directories such as /usr/man/manj for junk and /usr/man/manl for local
E 2
I 2
A directory, /usr/junk, to throw garbage into, as well as binary directories,
/usr/old and /usr/new, are useful.  The man command supports manual
directories such as /usr/man/mano for old and /usr/man/manl for local
E 2
to make this or something similar practical.
E 4
I 4
D 15
people can buy).  People using local commands should be made aware that
they aren't in the base manual.  Manual pages for local commands should be
D 8
installed in /usr/src/local/man and installed in /usr/local/man/cat[1-8].
The \fIman\fP(1) command automatically finds manual pages placed in
/usr/local/man/cat[1-8] to facilitate this practice.
E 8
I 8
installed in
E 15
I 15
people can buy).
D 16
People using local commands should be made aware that they aren't
E 16
I 16
People using local commands should be made aware that they are not
E 16
in the base manual.
Manual pages for local commands should be installed in
E 15
.Pn /usr/local/man/cat[1-8].
The
.Xr man (1)
command automatically finds manual pages placed in
D 11
/usr/local/man/cat[1-8] to facilitate this practice (see
E 11
I 11
/usr/local/man/cat[1-8] to encourage this practice (see
E 11
.Xr man.conf (5)).
E 8
E 4
D 16
.NH 2
Accounting
E 16
I 16
.Sh 2 "Accounting"
E 16
.PP
UNIX optionally records two kinds of accounting information:
connect time accounting and process resource accounting.  The connect
D 2
time accounting information is stored in the file /usr/adm/wtmp, which
E 2
I 2
D 8
time accounting information is stored in the file \fI/usr/adm/wtmp\fP, which
E 2
is summarized by the program
.IR ac (8).
E 8
I 8
time accounting information is stored in the file
.Pn /var/log/wtmp ,
which is summarized by the program
.Xr ac (8).
E 8
D 2
The process time accounting information is stored in the file /usr/adm/acct,
and analyzed and summarized by the program
E 2
I 2
The process time accounting information is stored in the file
D 8
\fI/usr/adm/acct\fP after it is enabled by
.IR accton (8),
E 8
I 8
.Pn /var/account/acct
after it is enabled by
.Xr accton (8),
E 8
and is analyzed and summarized by the program
E 2
D 8
.IR sa (8).
E 8
I 8
.Xr sa (8).
E 8
.PP
D 2
If you need to implement recharge for computing time, you can implement
E 2
I 2
If you need to recharge for computing time, you can develop
E 2
procedures based on the information provided by these commands.
A convenient way to do this is to give commands to the clock daemon
D 2
/etc/cron
E 2
I 2
D 8
.I /etc/cron
E 2
to be executed every day at a specified time.  This is done by adding
D 2
lines to /usr/adm/crontab; see
E 2
I 2
lines to \fI/usr/adm/crontab\fP; see
E 2
.IR cron (8)
E 8
I 8
.Pn /usr/sbin/cron
to be executed every day at a specified time.
This is done by adding lines to
.Pn /etc/crontab.local ;
see
.Xr cron (8)
E 8
for details.
D 16
.NH 2
Resource control
E 16
I 16
.Sh 2 "Resource control"
E 16
.PP
D 2
Resource control in the current version of UNIX is fairly
elaborate compared to most UNIX systems.  The disc quota
E 2
I 2
Resource control in the current version of UNIX is more
elaborate than in most UNIX systems.  The disk quota
E 2
facilities developed at the University of Melbourne have
been incorporated in the system and allow control over the
D 2
number of files and amount of disc space each user may use
E 2
I 2
D 8
number of files and amount of disk space each user may use
E 2
on each file system.  In addition, the resources consumed
E 8
I 8
number of files and amount of disk space each user and/or group may use
on each filesystem.  In addition, the resources consumed
E 8
by any single process can be limited by the mechanisms of
D 8
\fIsetrlimit\fP\|(2).  As distributed, the latter mechanism
E 8
I 8
.Xr setrlimit (2).
As distributed, the latter mechanism
E 8
is voluntary, though sites may choose to modify the login
D 2
mechanism to impose limits not covered with disc quotas.
E 2
I 2
mechanism to impose limits not covered with disk quotas.
E 2
.PP
D 2
To utilize the disc quota facilities, the system must be
E 2
I 2
To use the disk quota facilities, the system must be
E 2
D 8
configured with ``options QUOTA''.  File systems may then
E 8
I 8
configured with ``options QUOTA''.  Filesystems may then
E 8
be placed under the quota mechanism by creating a null file
D 8
.I quotas
at the root of the file system, running
.IR quotacheck (8),
D 2
and modifying /etc/fstab to indicate the file system is read-write
with disc quotas (a ``rq'' type field).  The
E 2
I 2
and modifying \fI/etc/fstab\fP to show that the file system is read-write
with disk quotas (an ``rq'' type field).  The
E 2
.IR quotaon (8)
E 8
I 8
.Pn quota.user
and/or
.Pn quota.group
at the root of the filesystem, running
.Xr quotacheck (8),
and modifying
.Pn /etc/fstab
to show that the filesystem is to run
with disk quotas (options userquota and/or groupquota).
The
.Xr quotaon (8)
E 8
program may then be run to enable quotas.
.PP
Individual quotas are applied by using the quota editor
D 8
.IR edquota (8).
E 8
I 8
.Xr edquota (8).
E 8
Users may view their quotas (but not those of other users) with the
D 8
.IR quota (1)
E 8
I 8
.Xr quota (1)
E 8
D 16
program.  The 
E 16
I 16
program. The
E 16
D 8
.IR repquota (8)
E 8
I 8
.Xr repquota (8)
E 8
program may be used to summarize the quotas and current
D 8
space usage on a particular file system or file systems.
E 8
I 8
space usage on a particular filesystem or filesystems.
E 8
.PP
D 8
Quotas are enforced with 
.I soft
and
.I hard
limits.  When a user first reaches a soft limit on a resource, a
message is generated on his/her terminal.  If the user fails to
lower the resource usage below the soft limit the next time
they log in to the system the
.I login
program will generate a warning about excessive usage.  Should
three login sessions go by with the soft limit breached the
system then treats the soft limit as a
.I hard
limit and disallows any allocations until enough space is
reclaimed to bring the user back below the soft limit.  Hard
limits are enforced strictly resulting in errors when a user
tries to create or write a file.  Each time a hard limit is
exceeded the system will generate a message on the user's 
terminal.
E 8
I 8
Quotas are enforced with \fIsoft\fP and \fIhard\fP limits.
When a user and/or group first reaches a soft limit on a resource, a
message is generated on their terminal.  If the user and/or group fails to
lower the resource usage below the soft limit
for longer than the time limit established for that filesystem
(default seven days) the system then treats the soft limit as a
\fIhard\fP limit and disallows any allocations until enough space is
reclaimed to bring the user and/or group back below the soft limit.
Hard limits are enforced strictly resulting in errors when a user
and/or group tries to create or write a file.  Each time a hard limit is
exceeded the system will generate a message on the user's terminal.
E 8
.PP
D 8
Consult the auxiliary document, ``Disc Quotas in a UNIX Environment''
E 8
I 8
Consult the auxiliary document, ``Disc Quotas in a UNIX Environment'' (SMM:4)
E 8
and the appropriate manual entries for more information.
D 16
.NH 2
Network troubleshooting
E 16
I 16
.Sh 2 "Network troubleshooting"
E 16
.PP
If you have anything more than a trivial network configuration,
from time to time you are bound to run into problems.  Before
blaming the software, first check your network connections.  On
networks such as the Ethernet a
loose cable tap or misplaced power cable can result in severely
D 8
deteriorated service.  The \fInetstat\fP\|(1) program may be of
aid in tracking down hardware malfunctions.  In particular, look
D 2
at the \-i and \-s options in the manual page.
E 2
I 2
at the \fB\-i\fP and \fB\-s\fP options in the manual page.
E 8
I 8
deteriorated service.  The
.Xr netstat (1)
program may be of aid in tracking down hardware malfunctions.
In particular, look at the \fB\-i\fP and \fB\-s\fP options in the manual page.
E 8
E 2
.PP
Should you believe a communication protocol problem exists,
consult the protocol specifications and attempt to isolate the
problem in a packet trace.  The SO_DEBUG option may be supplied
before establishing a connection on a socket, in which case the
system will trace all traffic and internal actions (such as timers
D 8
expiring) in a circular trace buffer.  This buffer may then
D 2
be printed out with the \fItrpt\fP\|(8C) program.  Most all the
servers distributed with the system accept a \-d option forcing
E 2
I 2
be printed out with the \fItrpt\fP\|(8C) program.  Most of the
servers distributed with the system accept a \fB\-d\fP option forcing
E 2
all sockets to be created with debugging turned on.  Consult the
appropriate manual pages for more information.
E 8
I 8
expiring) in a circular trace buffer.
This buffer may then be printed out with the
.Xr trpt (8)
program.
Most of the servers distributed with the system
accept a \fB\-d\fP option forcing
all sockets to be created with debugging turned on.
Consult the appropriate manual pages for more information.
E 8
D 16
.NH 2
D 2
Files which need periodic attention
E 2
I 2
Files that need periodic attention
E 16
I 16
.Sh 2 "Files that need periodic attention"
E 16
E 2
.PP
We conclude the discussion of system operations by listing
D 4
the files that require periodic attention or are system specific
E 4
I 4
the files that require periodic attention or are system specific:
E 4
D 10
.de BP
.IP \fB\\$1\fP
.br
..
E 10
.TS
center;
D 10
lb a.
E 10
I 10
lfC l.
E 10
/etc/fstab	how disk partitions are used
D 4
/etc/disktab	disk partition sizes
E 4
I 4
/etc/disktab	default disk partition sizes/labels
E 4
D 10
/etc/printcap	printer data base
E 10
I 10
/etc/printcap	printer database
E 10
/etc/gettytab	terminal type definitions
/etc/remote	names and phone numbers of remote machines for \fItip\fP(1)
/etc/group	group memberships
/etc/motd	message of the day
D 8
/etc/passwd	password file; each account has a line
E 8
I 8
/etc/master.passwd	password file; each account has a line
E 8
/etc/rc.local	local system restart script; runs reboot; starts daemons
I 2
/etc/inetd.conf	local internet servers
E 2
D 8
/etc/hosts	host name data base
E 8
I 8
D 10
/etc/hosts	local host name data base
E 8
/etc/networks	network name data base
/etc/services	network services data base
E 10
I 10
/etc/hosts	local host name database
/etc/networks	network name database
/etc/services	network services database
E 10
/etc/hosts.equiv	hosts under same administrative control
D 2
/etc/securetty	restricted list of ttys where root can log in
E 2
I 2
/etc/syslog.conf	error log configuration for \fIsyslogd\fP\|(8)
E 2
/etc/ttys	enables/disables ports
D 2
/etc/ttytype	terminal types connected to ports
E 2
D 8
/usr/lib/crontab	commands that are run periodically
/usr/lib/aliases	mail forwarding and distribution groups
/usr/adm/acct	raw process account data
/usr/adm/messages	system error log
D 3
/usr/adm/shutdownlog	log of system reboots
E 3
/usr/adm/wtmp	login session accounting
E 8
I 8
/etc/crontab	commands that are run periodically
/etc/crontab.local	local commands that are run periodically
/etc/aliases	mail forwarding and distribution groups
/var/account/acct	raw process account data
/var/log/messages	system error log
/var/log/wtmp	login session accounting
E 8
.TE
I 16
.pn 2
.bp
.PX
E 16
E 1
