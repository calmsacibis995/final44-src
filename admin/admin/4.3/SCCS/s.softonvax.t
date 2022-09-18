h09079
s 00018/00019/00202
d D 5.5 86/04/11 19:59:13 karels 5 4
c corrections
e
s 00003/00002/00218
d D 5.4 86/04/10 16:19:52 anne 4 3
c 
e
s 00012/00007/00208
d D 5.3 86/04/10 14:12:51 mckusick 3 2
c edits from karels
e
s 00009/00008/00206
d D 5.2 86/04/05 00:50:34 mckusick 2 1
c first pass edit
e
s 00214/00000/00000
d D 5.1 86/04/04 19:33:32 mckusick 1 0
c first draft
e
u
U
t
T
I 1
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
.\"
.\"	%W% (Berkeley) %G%
.\"
.LG
.B
.ce
Berkeley Software for UNIX\(dg on the VAX\(dd
.br
.sp
.ce
4.3BSD version of April 1986
.R
.NL
.sp .75i
.PP
.FS
\(dg\s-2UNIX\s0, \s-2UNIX/32V\s0, \s-2UNIX\s0 System III, and \s-2UNIX\s0
D 5
System V are trademarks of Western Electric.
E 5
I 5
System V are trademarks of AT&T Bell Laboratories.
E 5
.FE
.FS
D 3
\(dd\s-2VAX\s0 and \s-2PDP\s0 are trademarks of Digital Equipment Corporation.
E 3
I 3
D 5
\(dd\s-2VAX, PDP, UNIBUS\s0, and \s-2MASSBUS\s0 are
E 5
I 5
\(dd\s-2VAX, UNIBUS, MASSBUS\s0, and \s-2DECwriter\s0 are
E 5
trademarks of Digital Equipment Corporation.
E 3
.FE
.PP
A new version of the \s-2UNIX\s0 system for the \s-2VAX\s0 family of computers
is available from the Computer Systems Research Group
of the University of California at Berkeley.
This is an updated package of software for \s-2UNIX/32V\s0\(dg
D 5
licensees, and includes a bug fixed and performance tuned kernel for the
\s-2VAX\s0 as well as many other programs.
E 5
I 5
licensees, and includes a kernel for the
\s-2VAX\s0 with many bug fixes and improved performance
as well as many other programs.
E 5
This document highlights the differences between
D 5
the August, 1983 distribution known as 4.2BSD
E 5
I 5
the September, 1983 distribution known as 4.2BSD
E 5
and the April, 1986 release known as 4.3BSD.
A more detailed explanation of the differences is contained
in the documents ``Changes to the Kernel in 4.3BSD'',
and ``Bug Fixes and Changes in 4.3BSD''.
This document also summarizes the hardware supported by the distribution.
.PP
The new release may be used in two ways:
as a bootstrap system for new hardware
(or to bootstrap systems that were previously
running 3BSD, 4.0BSD, 4.1BSD, or \s-2UNIX/32V\s0),
D 5
or to update a system running the 4.2BSD release of August, 1983.
E 5
I 5
or to update a system running 4.2BSD.
E 5
Hardware configurations supported for booting are described below and in the
D 2
document ``Installing and operating 4.2BSD''.
E 2
I 2
document ``Installing and Operating 4.2BSD''.
E 2
The things most notable for sites that are updating
4.3BSD to this new release are:
.IP 1)
D 5
The performance of the system has been improved to be at least as
E 5
I 5
The performance of the system as a whole has been improved to be at least as
E 5
good as that of 4.1BSD, and in many instances is better.
.IP 2)
The system now provides full support for the Xerox Network System
network communication protocols.
D 5
This support has been integrated into the system to allow the
development and concurrent use of other communication protocols.
Hardware support and addressing have been isolated from the
protocols to allow sharing between varying network architectures.
E 5
I 5
Most of the remaining Internet dependencies in shared kernel code
have been removed or generalized.
E 5
.IP 3)
D 5
A new internet name server has been added to allow sites to
E 5
I 5
A new Internet name domain server has been added to allow sites to
E 5
administer their name space locally and export it to the rest of the net.
.IP 4)
The C and Fortran 77 compilers have been modified so that they
can generate single precision floating point operations.
The Fortran 77 compiler and associated I/O library have undergone
extensive changes to improve reliability and performance.
.IP 5)
The symbolic debugger, \fIdbx\fP, has been dramatically improved.
\fIDbx\fP works on C, Pascal and Fortran 77 programs.
.IP 6)
D 3
Support has been added for the VAX\(dg 8600 and 8650 processors.
E 3
I 3
Support has been added for the VAX 8600 and 8650 processors
with MASSBUS and UNIBUS peripherals, but not CI peripherals.
E 3
.IP 7)
Many bug fixes have been made.
.SH
System support in 4.3BSD
.PP
As distributed the kernel supports process sizes
with a program size of up to 6 megabytes.
The hard limit on the size of data and stack has been raised to
roughly 17 megabytes with a soft limit of 6 megabytes.
D 3
The soft limit nay be increased up to
E 3
I 3
The soft limit may be increased up to
E 3
D 2
the hard limit with the csh limit command.
E 2
I 2
the hard limit with the \fIcsh limit\fP command.
E 2
These numbers can be increased up to 64 megabytes per process
D 3
on systems willing to dedicate increased
E 3
I 3
segment on systems willing to dedicate increased
E 3
disk space for paging the process image.
.PP
D 2
The system now associates the number of rows and columns
E 2
I 2
The system now maintains the number of rows and columns
E 2
associated with each terminal or window on the system.
If these parameters are changed, all processes associated 
with the terminal or window receive a ``window size change'' signal.
Several utilities including \fIrlogin\fP and \fIvi\fP
have been modified to catch and respond to this signal.
.SH
Major new utilities in 4.3BSD
.PP
This section describes some of the additional user-level software
available with this distribution; we describe only software that is
not part of the 4.2BSD distribution.
Full documentation and source for this (and all supplied)
software is made available with the distribution.
.PP
The B language from the Center for Mathematical Research in Amsterdam
has been added as user contributed software.
This augments the existing set of languages already present on 4.2BSD
including C, Fortran 77, Pascal, Franz Lisp, APL, ICON, and FP.
.PP
There are two new screen based editors in 4.3BSD.
D 5
In addition to the venerable modefull editor \fIvi\fP,
E 5
I 5
In addition to the venerable modeful editor \fIvi\fP,
E 5
are added two modeless editors.
The first is GNU \fIemacs\fP, full of functionality but somewhat big and slow.
D 2
the other is \fIjove\fP from BRL, a mean and lean editor in the same tradition.
E 2
I 2
D 3
The other is \fIjove\fP from BRL,
a mean and lean editor in the army tradition.
E 3
I 3
The other is \fIjove\fP from Jonathan Payne,
a mean and lean editor in the modeless tradition.
E 3
E 2
.PP
An alternative to \fIMail\fP is now available in the fourth rewrite
D 2
of the Rand mail handler \fImh\fP.
E 2
I 2
D 5
of the Rand mail handler, \fImh\fP.
E 5
I 5
of the Rand mail handler, \fImh\fP (version 6.3 with Berkeley modifications).
E 5
E 2
For those users that spend half their day reading mail,
this mail handler backed by an 8650 is up to the job.
.SH
Hardware support in 4.3BSD
.PP
The system runs on VAX-11/725, VAX-11/730, VAX-11/750, VAX-11/780,
VAX-11/785, VAX-8600, and VAX-8650 processors and supports
the standard DEC mass storage peripherals: RM03, RM05
RP06, RP07, RA60, RA80, RA81, RM80, RL02, and
RK07 disks; TS11, TU80, TE16, TU45, TU77, TU78, and TU81 tapes.
DEC standard bad block
handling is supported on all the DEC disk drives
except the RL02.
.PP
The EMULEX SC21-V and SC31 UNIBUS
storage module disk controllers are supported with AMPEX 9300 and CDC 9766
300 Megabyte disk drives, AMPEX Capricorn 330 Megabyte Winchester disk drives,
FUJITSU 160 Megabyte Winchester drives.
In addition, the SC31 supports FUJITSU Eagle 404 Megabyte Winchester drives. 
The EMULEX SC750 (emulating the DEC RH750 MASSBUS interface) and the
SC780 and SC7000 disk controllers (emulating the DEC RH780 MASSBUS interface)
are supported with the CDC 9775, 9766, and 9730 disk drives,
AMPEX 9300 and Capricorn disk drives,
and the FUJITSU Eagle 404 Megabyte Winchester disk drive.
Bad blocking support is provided on all disks attached to an EMULEX
UNIBUS or MASSBUS controller.
The EMULEX TC-11 tape controller
D 5
(that emulates a TM-11 DEC UNIBUS controller),
E 5
I 5
(that emulates a TM11 DEC UNIBUS controller),
E 5
the EMULEX TC-7000 tape controller
(that emulates a TU77 DEC MASSBUS controller),
and System Industries Model 9700 tape drive
(that emulates a DEC TU45 controller on the UNIBUS) are supported. 
.PP
To bootstrap the system, a supported disk and
tape drive are needed.  To maintain all the system
sources and binary programs, at least 120 Megabytes
of disk storage is required.
.PP
For terminal interfaces,
D 3
the standard DEC DZ-11 and DMF-32 terminal interfaces are supported.
E 3
I 3
D 5
the standard DEC DZ-11, DMZ-32, DHU-11, and DMF-32 terminal
E 5
I 5
the standard DEC DZ11, DMZ32, DHU11, and DMF32 terminal
E 5
interfaces are supported.
E 3
D 5
In addition, DH-11 emulators such as
E 5
I 5
In addition, DH11 emulators such as
E 5
the ABLE DH/DM (that replaces the ABLE DMAX) and EMULEX CS-11 are supported.
The system also provides support for standard line printer
D 5
interfaces emulating the DEC LP-11 or the parallel port of the DMF-32.
Support for serial printers such as a DECWRITER-III and printer-plotters
E 5
I 5
interfaces emulting the DEC LP11 or the parallel port of the DMF32.
Support for serial printers such as a DECwriter-III and printer-plotters
E 5
D 4
such as made by BENSON/VARIAN or VERSATEC is available with standard drivers.
E 4
I 4
such as those made by BENSON/VARIAN or VERSATEC is 
available with standard drivers.
E 4
.PP
This release supports any number
of any of the devices described above.
The devices may be placed arbitrarily on any
available MASSBUS and UNIBUS interfaces.
D 4
For the 8600 and the 8650 adapters may be on either of the SBIA's.
E 4
I 4
For the 8600 and the 8650, adapters may be on either of the SBIA's.
E 4
The system configures at boot time,
locating available devices,
using a system configuration compiled into the kernel.
The configuration description contains all the information
about the topology of the machine and the addresses at which the various
devices are located.
It is possible (and desirable) to write the description using
``pattern matching'' to only partially specify some of the interconnects.
I 3
The bootstrap passes the identity of the load device to the kernel,
which will use it as the root file system.
E 3
.PP
The system configuration program sizes system data structures based on
a specification of the maximum number of active users to be present on the
system.  To build a system for a larger or smaller workload you only need
change this single constant.  The system also initializes the parameters
to the paging system and sizes its file system buffer cache based
on the amount of available memory.
.PP
The system supports access to the 11/780 and 11/785 console floppy disk,
the 8600 and 8650 RL02 console disk drive, and
the 11/725, 11/730, and 11/750 TU58 console cassette tape.
However, reliable access to the 11/750 TU58 cassette
interface is possible only on a totally quiescent system.
.SH
What this distribution does not contain
.PP
Two new system facilities that had been planned for the 4.2BSD
D 2
release were dropped in order that the current system might
E 2
I 2
release were dropped in order that the 4.2BSD system might
E 2
be distributed at the earliest possible time.
We mention them here mostly to point out that they have still not
been added to this system:
.IP 1)
Enhanced memory management support.  This being the support of
large address space processes, sharing of memory between processes, and
D 2
mapping disk file to and from a process' address space.
E 2
I 2
mapping disk files to and from a process' address space.
E 2
.IP 2)
Portals and wrapping.  These two notions are part of the original
interprocess communication design.  Their implementation required
extensive reorganization to the system.
.PP
Also planned, but still not available is remote file system support.
At the time of the release, no single remote file system scheme
fully addressed the wide spectrum of semantic correctness and
reasonable performance.
Like networking, we do not expect that any single remote
D 2
file system will ever solve all needs,
E 2
I 2
file system will ever solve all needs.
E 2
Consequently we are working to design a framework that will
support the full range of remote file system protocols
just as we did with multiple network protocol support.
E 1
