h51289
s 00002/00002/00160
d D 8.1 93/06/08 14:00:46 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00003/00159
d D 6.4 93/06/06 12:09:33 mckusick 5 4
c crude update for 4.4BSD
e
s 00004/00003/00158
d D 6.3 91/04/17 11:34:59 bostic 4 3
c new copyright; att/bsd/shared
e
s 00031/00026/00130
d D 6.2 86/06/03 18:04:54 karels 3 2
c 4.3 version
e
s 00000/00000/00156
d D 6.1 86/05/25 16:38:01 mckusick 2 1
c 4.3BSD beta release document
e
s 00156/00000/00000
d D 5.1 86/05/25 16:37:53 mckusick 1 0
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
D 6
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 6
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 3
.ds LH "Building Systems With Config
.ds RH "Configuration File Contents
.ds CF July 27, 1983
.LP
.nr H1 2
.nr H2 0
.ds CH "
.bp
.ds CH "\(hy \\n(PN \(hy
.LG
.B
.ce
2. CONFIGURATION FILE CONTENTS
.sp 2
.R
.NL
E 3
I 3
.\".ds RH "Configuration File Contents
.ne 2i
.NH
CONFIGURATION FILE CONTENTS
E 3
.PP
A system configuration must include at least the following
pieces of information:
.IP \(bu 3
machine type
.IP \(bu 3
cpu type
.IP \(bu 3
system identification
.IP \(bu 3
timezone
.IP \(bu 3
maximum number of users
.IP \(bu 3
location of the root file system
.IP \(bu 3
available hardware
.PP
.I Config
allows multiple system images to be generated from a single
configuration description.  Each system image is configured
for identical hardware, but may have different locations for the root
file system and, possibly, other system devices.
.NH 2
Machine type
.PP
The 
.I "machine type"
D 3
indicates if the system is going to operate on a DEC VAX-11 computer,
or some other machine on which 4.2BSD operates.  The machine type
is used to locate certain data files which are machine specific and,
also, to select rules used in constructing the resultant
E 3
I 3
indicates if the system is going to operate on a DEC VAX-11\(dg computer,
.FS
\(dg DEC, VAX, UNIBUS, MASSBUS and MicroVAX are trademarks of Digital
Equipment Corporation.
.FE
D 5
or some other machine on which 4.3BSD operates.  The machine type
E 5
I 5
or some other machine on which 4.4BSD operates.  The machine type
E 5
is used to locate certain data files which are machine specific, and
also to select rules used in constructing the resultant
E 3
configuration files.
.NH 2
Cpu type
.PP
The
.I "cpu type"
indicates which, of possibly many, cpu's the system is to operate on.
For example, if the system is being configured for a VAX-11, it could
D 3
be running on a VAX-11/780, VAX-11/750, or VAX-11/730.  Specifying
more than one cpu type implies the system should be configured to run
on all the cpu's specified.  For some types of machines this is not
E 3
I 3
be running on a VAX 8600, VAX-11/780, VAX-11/750, VAX-11/730 or MicroVAX II.
(Other VAX cpu types, including the 8650, 785 and 725, are configured using
the cpu designation for compatible machines introduced earlier.)
Specifying
more than one cpu type implies that the system should be configured to run
on any of the cpu's specified.  For some types of machines this is not
E 3
possible and 
.I config
will print a diagnostic indicating such.
.NH 2
System identification
.PP
The
.I "system identification"
is a moniker attached to the system, and often the machine on which the
system is to run.  For example, at Berkeley we have machines named Ernie
(Co-VAX), Kim (No-VAX), and so on.  The system identifier selected is used to
create a global C ``#define'' which may be used to isolate system dependent
pieces of code in the kernel.  For example, Ernie's Varian driver used
to be special cased because its interrupt vectors were wired together.  The
code in the driver which understood how to handle this non-standard hardware
configuration was conditionally compiled in only if the system
was for Ernie.  
.PP
The system identifier ``GENERIC'' is given to a system which
will run on any cpu of a particular machine type; it should not
otherwise be used for a system identifier.
.NH 2
Timezone
.PP
The timezone in which the system is to run is used to define the
information returned by the \fIgettimeofday\fP\|(2)
system call.  This value is specified as the number of hours east
or west of GMT.  Negative numbers indicate a value east of GMT.
The timezone specification may also indicate the
type of daylight savings time rules to be applied.
.NH 2
Maximum number of users
.PP
The system allocates many system data structures at boot time
based on the maximum number of users the system will support.
This number is normally between 8 and 40, depending
on the hardware and expected job mix.  The rules
used to calculate system data structures are discussed in
Appendix D.
.NH 2
Root file system location
.PP
When the system boots it must know the location of
the root of the file system
tree.  This location and the part(s) of the disk(s) to be used
for paging and swapping must be specified in order to create
a complete configuration description.  
.I Config
uses many rules to calculate default locations for these items;
these are described in Appendix B.
.PP
When a generic system is configured, the root file system is left
undefined until the system is booted.  In this case, the root file
system need not be specified, only that the system is a generic system.
.NH 2
Hardware devices
.PP
When the system boots it goes through an
.I autoconfiguration
phase.  During this period, the system searches for all
those hardware devices
which the system builder has indicated might be present.  This probing
sequence requires certain pieces of information such as register
addresses, bus interconnects, etc.  A system's hardware may be configured
in a very flexible manner or be specified without any flexibility
whatsoever.  Most people do not configure hardware devices into the
system unless they are currently present on the machine, expect
them to be present in the near future, or are simply guarding
against a hardware
failure somewhere else at the site (it is often wise to configure in
extra disks in case an emergency requires moving one off a machine which
has hardware problems).
.PP
The specification of hardware devices usually occupies the majority of
the configuration file.  As such, a large portion of this document will
be spent understanding it.  Section 6.3 contains a description of
the autoconfiguration process, as it applies to those planning to
write, or modify existing, device drivers.
.NH 2
D 3
Optional items
E 3
I 3
Pseudo devices
E 3
.PP
I 3
Several system facilities are configured in a manner like that used
for hardware devices although they are not associated with specific hardware.
These system options are configured as
.IR pseudo-devices .
Some pseudo devices allow an optional parameter that sets the limit
on the number of instances of the device that are active simultaneously.
.NH 2
System options
.PP
E 3
Other than the mandatory pieces of information described above, it
D 3
is also possible to include various optional system facilities.  For
example, 4.2BSD can be configured to support binary compatibility for
E 3
I 3
is also possible to include various optional system facilities
or to modify system behavior and/or limits.
D 5
For example, 4.3BSD can be configured to support binary compatibility for
E 3
programs built under 4.1BSD.  Also, optional support is provided
E 5
I 5
For example, 4.4BSD can be configured to support binary compatibility for
programs built under 4.3BSD.  Also, optional support is provided
E 5
for disk quotas and tracing the performance of the virtual memory
subsystem.  Any optional facilities to be configured into
the system are specified in the configuration file.  The resultant
files generated by
.I config
will automatically include the necessary pieces of the system.
E 1
