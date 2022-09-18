.LG
.B
.ce
Berkeley Software for UNIX\(dg on the VAX\(dd
.br
.sp
.ce
4.2BSD version of August 1983
.R
.NL
.sp .75i
.PP
.FS
\(dg\s-2UNIX\s0, \s-2UNIX/32V\s0, \s-2UNIX\s0 System III, and \s-2UNIX\s0
System V are trademarks of Western Electric.
.FE
.FS
\(dd\s-2VAX\s0 and \s-2PDP\s0 are trademarks of Digital Equipment Corporation.
.FE
.PP
A new version of the \s-2UNIX\s0 system for the \s-2VAX\s0 family of computers
is available from the Computer Systems Research Group
of the University of California at Berkeley.
This is an updated package of software for \s-2UNIX/32V\s0\(dg
licensees, and includes a refined version of the paging kernel for the
\s-2VAX\s0 as well as a large number of other programs.  This document
describes the major differences between standard \s-2UNIX/32V\s0 as distributed
by Western Electric and the August, 1983 distribution known as 4.2BSD.
.PP
The new release may be used in two ways: as a bootstrap system for new hardware
(or to bootstrap systems which were previously
running 3BSD, 4.0BSD, or \s-2UNIX/32V\s0),
or to update a system running the 4.1BSD release of June, 1981.
Hardware configurations supported for booting are described below and in the
document ``Installing and operating 4.2BSD''.
The things most notable for sites which are updating
4.1BSD to this new release are:
.IP 1)
A new file system organization which can provide a 10 fold gain
in file system throughput.
.IP 2)
Support for the DARPA standard TCP/IP communication protocols and
higher level application protocols such as FTP, TELNET, and SMTP.
.IP 3)
New interprocess communication facilities which replace the old
multiplexed files and which are integrated with the networking support.
.IP 4)
Additional hardware support, including bad sector handling of UNIBUS
storage modules, a second UNIBUS adaptor on the VAX-11/750, and 64K
chip memory controllers on the VAX-11/780.
.IP 5)
Software contributed by the user community, including the \s-2APL\s0
and \s-2RCS\s0 (Revision Control System) tools developed at Purdue, the
\s-2MH\s0 (Mail Handling) system developed at the Rand Coporation,
and the \s-2ICON\s0 programming environment developed at the
University of Arizona.
.IP 5)
Many bug fixes.
.br
.ne 10
.sp 4
.LG
.LG
.ce
.B "System facilities"
.NL
.SH
Hardware support
.PP
The system runs on VAX-11/730, VAX-11/750, and VAX-11/780
processors and supports
the standard DEC mass storage peripherals: RM03, RM05
RP06, RP07, RA60, RA80, RA81, RM80, RL02, RA80, and
RK07 disks; TS11, TU80, TE16, TU45, TU77, and TU78 tapes.
DEC standard bad block
handling is supported on all the DEC disk drives
except the RL02.
.PP
The EMULEX SC21-V UNIBUS
storage module disk controller is supported with AMPEX 9300 and CDC 9766
300 Megabyte disk drives, AMPEX Capricorn 330 Megabyte Winchester disk drives,
and FUJITSU 160 Megabyte Winchester drives. 
The EMULEX SC750 and SC780 disk controllers, which emulate the DEC
RH750 and RH780 MASSBUS interfaces, are supported with 
the CDC 9775, 9766, and 9730 disk drives, AMPEX 9300 and Capricorn disk
drives, and the FUJITSU Eagle 404 Megabyte Winchester disk drive.
Bad blocking support is provided on all disks attached to an EMULEX
UNIBUS or MASSBUS controller.
The EMULEX TC-11 tape controller
(which emulates a TM-11 DEC UNIBUS controller)
and System Industries Model 9700 tape drive (which emulates 
a DEC TU45 controller on the UNIBUS) are
supported. 
.PP
To bootstrap the system, a supported disk and
tape drive are needed.  To maintain all the system
sources and binary programs, at least 80 Megabytes
of disk storage is required.  The support for RK07
only systems provided in 4.1BSD has been discontinued.
.PP
For terminal interfaces, in addition
to the standard DEC (non-DMA) DZ-11 and (DMA) DMF-32 terminal interfaces,
(DMA) DH-11 emulators are supported for terminal support, such as
the ABLE DH/DM (which replaces the ABLE DMAX) and EMULEX CS-11.
The system also provides support for standard line printer
interfaces emulating the DEC LP-11 and the use of 1200 baud terminals
such as a DECWRITER-III acting as a slow speed printer.  Printer-plotters
such as made by BENSON/VARIAN or VERSATEC are also supported with standard
drivers.
.PP
This release supports any number
of any of the devices described above.
The devices may be placed arbitrarily on any
available MASSBUS and UNIBUS interfaces.  The system configures at boot
time, locating available devices, using a system configuration compiled
into the kernel.  The configuration description contains all the information
about the topology of the machine and the addresses at which the various
devices are located.  It is possible (and desirable) to write the description
using ``pattern matching'' to only partially specify some of the interconnects.
.PP
The system configuration program sizes system data structures based on
a specification of the maximum number of active users to be present on the
system.  To build a system for a larger or smaller workload you only need
change this single constant.  The system also initializes the parameters
to the paging system and sizes its file system buffer cache based
on the amount of available memory.
.PP
The system supports access to the 11/780 console floppy disk and
11/750 and 11/730 TU58 console cassette tape.  However, reliable
access to the 11/750 TU58 cassette
interface is possible only on a totally quiescent system.
.PP
For further information on device support and recommendations
for configuration of VAX systems to run UNIX see
``Hints on configuring a VAX to run UNIX''
by Bob Kridle and Sam Leffler.
.SH
System reliability and performance
.PP
The system reboots automatically after hardware
and software failures, running an automatic procedure that recovers
from normal minor disk inconsistencies.  If hardware or software failures
cause unexpected problems on the disks, then an interactive semi-automatic
repair program can be used to fix up the disks.
.PP
The system is fully and transparently demand paged.
As distributed it will support individual
process sizes up to 6 Megabytes each of data and stack area and
6 Megabytes of program.
These numbers can be increased on systems
willing to dedicate increased
disk space for paging the process image.
.PP
The default loader format is load-on-demand, and
allows large processes to start quickly.  A \fIvfork\fR system call
allows a large process to execute other processes without copying its
data space.
.PP
The system performance has been enhanced in a number of ways.
Relative to \s-2UNIX/32V\s0, the
basic system overheads have been reduced by tightening up the system
code and improving system data structures.  Disk throughput has
been substantially increased by increasing the logical block size
on the disks.  The block size may vary from file system to file system,
but normally is 4096 or 8192 bytes*.
File system performance is also increased, beyond that normally
obtained with \s-2UNIX/32V\s0 or earlier Berkeley releases,
by localizing file system information and placing file system
and user data in rotationally optimal locations on the disk.
A description of the new file system organization is provided
in the manual and supplementary papers in Volume 2C of the
UNIX Programmer's Manual.
.FS
\(dg Systems currently running \s-2UNIX\s0 convert to the new format
by saving files with the tape archiver or file system dump programs
and reading them into the new system.
Because of the format changes in the file system and because some of the
changes described here required recompilation of all programs, a bootstrap
tape and all programs are distributed.
.FE
System algorithms such as the swapping and file system caching algorithms
have also been improved to increase system performance.
.SH
What this distribution does not contain
.PP
A number of new system facilities had been planned for the 4.2BSD
release, but were dropped in order that the current system might
be distributed at the earliest possible time.
We mention them here mostly to point out that they are not in this system:
.IP 1)
Enhanced memory management support.  This being the support of very
large address space processes, sharing of memory between processes, and
mapping disk file to and from a process' address space.
.IP 2)
Portals and wrapping.  These two notions are part of the original
interprocess communication design.  Their implementation required
extensive reorganization to the system.
.SH
.ne 10
.sp 4
.LG
.LG
.ce
User Software
.NL
.sp
.PP
The following sections describe some of the
additional user-level software
available with this distribution; we describe only software which is
not part of the \s-2UNIX/32V\s0 distribution.
Full documentation and source for this (and all supplied)
software is made available with the distribution.
.SH
Languages for the VAX
.PP
Interpreters for \s-2APL\s0, \s-2LISP\s0, \s-2ICON\s0,
and both an interpreter and compiler for Pascal.
The \s-2APL\s0 and \s-2ICON\s0 systems were developed at
Purdue University and the University of Arizona, respectively, and
are part of the ``user contributed software''
portion of the 4.2BSD distribution.
The \s-2LISP\s0 system, known as ``Franz Lisp'', is written in C and
\s-2LISP\s0, includes both an interpreter and a compiler,
and is compatible with a large subset of \s-2MACLISP\s0.
The Pascal system is the instructional system that has been distributed
previously for \s-2PDP\-11's\s0.  The language implemented is
standard Pascal.  The implementation
features excellent diagnostics, and allows
separate compilation and use of C and FORTRAN procedures
with full type checking.
.SH
A display editor
.PP
The tape includes the display editor,
.I vi,
(vee-eye) that runs on over 100 different intelligent and unintelligent
display terminals.
This editor uses a terminal description data base; a library
of routines for writing terminal independent programs using
this data base is also supplied.
The editor has a mnemonic command set that is easy to learn and remember,
and deals with the hierarchical structure of documents in a natural way.
Editor users are protected against loss of work if the system crashes,
and against casual mistakes by a general
.I undo
facility as well as visual feedback.
The editor is usable even on low speed lines and dumb terminals.
.SH
Command and mail processing programs
.PP
The tape also includes a new command processor
.I csh
that caters to interactive users by providing a history mechanism so
that recently given
commands can be easily repeated.  The shell also
has a powerful macro-like aliasing facility that can be used to
tailor a friendly, personalized, command environment.
A new interactive mail processing command
supports items such as subject and carbon copy fields, and
distribution lists, and makes it convenient to deal with
large volumes of mail.
.SH
Job control facilities
.PP
The system supports the multiplexing of terminals between jobs.
It is no longer necessary to decide in advance that a job is to be
run in the foreground or background; running jobs may be moved from
the foreground to the background and vice-versa, and mechanisms exist
in the C shell 
.I csh
for arbitrating the terminal between the active jobs.
.SH
Debugger support
.PP
A new symbolic debugger
.I dbx
is included in the distribution.  Dbx can be used to debug
C, and FORTRAN 77 programs.
The assembler has been rewritten and the C compiler
modified to reduce the overhead of using a symbolic debugger.
.SH
Other software
.PP
Also included are several other useful packages including
programs to simulate the phototypesetter on 200 bpi dot-matrix plotters
(these programs were moved from the \s-2PDP\-11\s0 to the \s-2VAX\s0 and
many fonts available on the Arpanet have been converted
to the required format),
a bulletin board program, routines for data compression,
and a new, flexible macro package for 
.I nroff
and
.I troff
called
.I \-me.
