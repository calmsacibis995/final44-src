h12532
s 00002/00002/00290
d D 8.1 93/06/08 14:04:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00288
d D 6.3 91/04/17 11:35:48 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00289
d D 6.2 86/07/31 15:00:09 bloom 3 2
c quotachk -> quotacheck
e
s 00003/00002/00288
d D 6.1 86/05/13 15:01:01 mckusick 2 1
c 4.3BSD beta release document
e
s 00290/00000/00000
d D 5.1 86/05/13 15:00:22 mckusick 1 0
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
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
I 2
.EH 'SMM:4-%''Disc Quotas in a \s-2UNIX\s+2 Environment'
.OH 'Disc Quotas in a \s-2UNIX\s+2 Environment''SMM:4-%'
E 2
.ND 5th July, 1983
D 2
.RP
E 2
.TL
D 2
Disc Quotas in a UNIX\s-3\u*\d\s0 Environment.
E 2
I 2
Disc Quotas in a \s-2UNIX\s+2\s-3\u*\d\s0 Environment
E 2
.FS
* UNIX is a trademark of Bell Laboratories.
.FE
.AU
Robert Elz
.AI
Department of Computer Science
University of Melbourne,
Parkville,
Victoria,
Australia.
.AB
.PP
In most computing environments, disc space is not
infinite.
The disc quota system provides a mechanism
to control usage of disc space, on an
individual basis.
.PP
Quotas may be set for each individual user, on any, or
all filesystems.
.PP
The quota system will warn users when they
exceed their allotted limit, but allow some
extra space for current work.
Repeatedly remaining over quota at logout,
will cause a fatal over quota condition eventually.
.PP
The quota system is an optional part of
\s-2VMUNIX\s0 that may be included when the
system is configured.
.AE
.NH 1
Users' view of disc quotas
.PP
To most users, disc quotas will either be of no concern,
or a fact of life that cannot be avoided.
The
\fIquota\fP\|(1)
command will provide information on any disc quotas
that may have been imposed upon a user.
.PP
There are two individual possible quotas that may be
imposed, usually if one is, both will be.
A limit can be set on the amount of space a user
can occupy, and there may be a limit on the number
of files (inodes) he can own.
.PP
.I Quota
provides information on the quotas that have
been set by the system administrators, in each
of these areas, and current usage.
.PP
There are four numbers for each limit, the current
usage, soft limit (quota), hard limit, and number
of remaining login warnings.
The soft limit is the number of 1K blocks (or files)
that the user is expected to remain below.
Each time the user's usage goes past this limit,
he will be warned.
The hard limit cannot be exceeded.
If a user's usage reaches this number, further
requests for space (or attempts to create a file)
will fail with an EDQUOT error, and the first time
this occurs, a message will be written to the user's
terminal.
Only one message will be output, until space occupied
is reduced below the limit, and reaches it again,
in order to avoid continual noise from those
programs that ignore write errors.
.PP
Whenever a user logs in with a usage greater than
his soft limit, he will be warned, and his login
warning count decremented.
When he logs in under quota, the counter is reset
to its maximum value (which is a system configuration
parameter, that is typically 3).
If the warning count should ever reach zero (caused
by three successive logins over quota), the
particular limit that has been exceeded will be treated
as if the hard limit has been reached, and no
more resources will be allocated to the user.
The \fBonly\fP way to reset this condition is
to reduce usage below quota, then log in again.
.NH 2 
Surviving when quota limit is reached
.PP
In most cases, the only way to recover from over
quota conditions, is to abort whatever activity was in progress
on the filesystem that has reached its limit, remove
sufficient files to bring the limit back below quota,
and retry the failed program.
.PP
However, if you are in the editor and a write fails
because of an over quota situation, that is not
a suitable course of action, as it is most likely
that initially attempting to write the file
will have truncated its previous contents, so should
the editor be aborted without correctly writing the
file not only will the recent changes be lost, but
possibly much, or even all, of the data
that previously existed.
.PP
There are several possible safe exits for a user
caught in this situation.
He may use the editor \fB!\fP shell escape command to
examine his file space, and remove surplus files.
Alternatively, using \fIcsh\fP, he may suspend the
editor, remove some files, then resume it.
A third possibility, is to write the file to
some other filesystem (perhaps to a file on /tmp)
where the user's quota has not been exceeded.
Then after rectifying the quota situation,
the file can be moved back to the filesystem
it belongs on.
.NH 1
Administering the quota system
.PP
To set up and establish the disc quota system,
there are several steps necessary to be performed
by the system administrator.
.PP
First, the system must be configured to include
the disc quota sub-system.
This is done by including the line:
.DS
options   QUOTA
.DE
in the system configuration file, then running
\fIconfig\fP\|(8)
followed by a system configuration\s-3\u*\d\s0.
.FS
* See also the document ``Building 4.2BSD UNIX Systems with Config''.
.FE
.PP
Second, a decision as to what filesystems need to have
quotas applied needs to be made.
Usually, only filesystems that house users' home directories,
or other user files, will need to be subjected to
the quota system, though it may also prove useful to
also include \fB/usr\fR.
If possible, \fB/tmp\fP should usually be free of quotas.
.PP
Having decided on which filesystems quotas need to be
set upon, the administrator should then allocate the
available space amongst the competing needs. How this
should be done is (way) beyond the scope of this document.
.PP
Then, the
\fIedquota\fP\|(8)
command can be used to actually set the limits desired upon
each user. Where a number of users are to be given the
same quotas (a common occurrence) the \fB\-p\fP switch
to edquota will allow this to be easily accomplished.
.PP
Once the quotas are set, ready to operate, the system
must be informed to enforce quotas on the desired filesystems.
This is accomplished with the
\fIquotaon\fP\|(8)
command.
.I Quotaon
will either enable quotas for a particular filesystem, or
with the \fB\-a\fP switch, will enable quotas for each
filesystem indicated in \fB/etc/fstab\fP as using quotas.
See
\fIfstab\fP\|(5)
for details.
Most sites using the quota system, will include the
line
.DS C
/etc/quotaon -a
.DE
in \fB/etc/rc.local\fP.
.PP
Should quotas need to be disabled, the
\fIquotaoff\fP(8)
command will do that, however, should the filesystem be
about to be dismounted, the
\fIumount\fP\|(8)
command will disable quotas immediately before the
filesystem is unmounted.
This is actually an effect of the
\fIumount\fP\|(2)
system call, and it guarantees that the quota system
will not be disabled if the umount would fail
because the filesystem is not idle.
.PP
Periodically (certainly after each reboot, and when quotas
are first enabled for a filesystem), the records retained
in the quota file should be checked for consistency with
the actual number of blocks and files allocated to
the user.
The
D 3
\fIquotachk\fP\|(8)
E 3
I 3
\fIquotacheck\fP\|(8)
E 3
command can be used to accomplish this.
It is not necessary to dismount the filesystem, or disable
the quota system to run this command, though on
active filesystems inaccurate results may occur.
This does no real harm in most cases, another run of
D 3
.I quotachk
E 3
I 3
.I quotacheck
E 3
when the filesystem is idle will certainly correct any inaccuracy.
.PP
The super-user may use the
\fIquota\fP\|(1)
command to examine the usage and quotas of any user, and
the
\fIrepquota\fP\|(8)
command may be used to check the usages and limits for
all users on a filesystem.
.NH 1
Some implementation detail.
.PP
Disc quota usage and information is stored in a file on the
filesystem that the quotas are to be applied to.
Conventionally, this file is \fBquotas\fR in the root of
the filesystem.
While this name is not known to the system in any way,
several of the user level utilities "know" it, and
choosing any other name would not be wise.
.PP
The data in the file comprises an array of structures, indexed
by uid, one structure for each user on the system (whether
the user has a quota on this filesystem or not).
If the uid space is sparse, then the file may have holes
in it, which would be lost by copying, so it is best to
avoid this.
.PP
The system is informed of the existence of the quota
file by the
\fIsetquota\fP\|(2)
system call.
It then reads the quota entries for each user currently
active, then for any files open owned by users who
are not currently active.
Each subsequent open of a file on the filesystem, will
be accompanied by a pairing with its quota information.
In most cases this information will be retained in core,
either because the user who owns the file is running some
process, because other files are open owned by the same
user, or because some file (perhaps this one) was recently
accessed.
In memory, the quota information is kept hashed by user-id
and filesystem, and retained in an LRU chain so recently
released data can be easily reclaimed.
Information about those users whose last process has
recently terminated is also retained in this way.
.PP
Each time a block is accessed or released, and each time an inode
is allocated or freed, the quota system gets told
about it, and in the case of allocations, gets the
opportunity to object.
.PP
Measurements have shown
that the quota code uses a very small percentage of the system
cpu time consumed in writing a new block to disc.
.NH 1
Acknowledgments
.PP
The current disc quota system is loosely based upon a very
early scheme implemented at the University of New South
Wales, and Sydney University in the mid 70's. That system
implemented a single combined limit for both files and blocks
on all filesystems.
.PP
A later system was implemented at the University of Melbourne
by the author, but was not kept highly accurately, eg:
chown's (etc) did not affect quotas, nor did i/o to a file
other than one owned by the instigator.
.PP
The current system has been running (with only minor modifications)
since January 82 at Melbourne.
It is actually just a small part of a much broader resource
control scheme, which is capable of controlling almost
anything that is usually uncontrolled in unix. The rest
of this is, as yet, still in a state where it is far too
subject to change to be considered for distribution.
.PP
For the 4.2BSD release, much work has been done to clean
up and sanely incorporate the quota code by Sam Leffler and
Kirk McKusick at The University of California at Berkeley.
E 1
