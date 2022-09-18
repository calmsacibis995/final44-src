h38251
s 00000/00000/00146
d D 8.1 93/07/27 18:59:04 mckusick 20 19
c 4.4BSD snapshot (revision 8.1)
e
s 00004/00008/00142
d D 6.12 93/07/27 17:58:28 mckusick 19 18
c convert from .NH to .Sh to get table of contents
e
s 00001/00001/00149
d D 6.11 93/07/26 17:03:19 mckusick 18 17
c parameterize block counts
e
s 00007/00007/00143
d D 6.10 93/07/20 12:39:24 bostic 17 16
c wordsmithing
e
s 00001/00002/00149
d D 6.9 93/07/20 11:49:16 mckusick 16 15
c final edit pass
e
s 00001/00001/00150
d D 6.8 93/07/15 16:37:18 mckusick 15 14
c diction
e
s 00002/00002/00149
d D 6.7 93/07/15 09:08:53 hibler 14 13
c minor cleanup
e
s 00033/00027/00118
d D 6.6 93/07/12 22:42:50 mckusick 13 12
c nits discovered from reading
e
s 00009/00009/00136
d D 6.5 93/07/12 21:47:09 mckusick 12 11
c get rid of last vestiges on Ux macro
e
s 00014/00017/00131
d D 6.4 93/07/12 20:09:21 mckusick 11 10
c comments from Bostic
e
s 00015/00010/00133
d D 6.3 93/07/09 20:47:43 mckusick 10 9
c typesetting nits
e
s 00017/00022/00126
d D 6.2 93/07/08 22:18:43 hibler 9 8
c hibler whacking: mostly working on the hp300 section
e
s 00034/00258/00114
d D 6.1 93/07/08 00:30:10 mckusick 8 6
c first pass at getting updated for 4.4BSD
e
s 00002/00002/00370
d R 8.1 93/06/08 13:57:52 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00371
d D 1.6 91/05/07 22:43:11 bostic 6 5
c new copyright; att/bsd/shared
e
s 00082/00047/00300
d D 1.5 91/05/06 17:48:48 karels 5 4
c add hcx-9, updates (still only 4.3-tahoe vintage)
e
s 00014/00003/00333
d D 1.4 89/03/07 13:52:09 bostic 4 3
c add Berkeley copyright, networking release
e
s 00001/00001/00335
d D 1.3 88/07/17 09:36:43 karels 3 2
c add keywords
e
s 00137/00137/00199
d D 1.2 88/07/17 09:31:48 karels 2 1
c karels, bostic editing
e
s 00336/00000/00000
d D 1.1 88/06/13 10:54:18 bostic 1 0
c date and time created 88/06/13 10:54:18 by bostic
e
u
U
t
T
I 1
D 2
.\" Copyright (c) 1980 Regents of the University of California.
E 2
I 2
D 4
.\" Copyright (c) 1988 Regents of the University of California.
E 2
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 8
.\" Copyright (c) 1988 The Regents of the University of California.
E 8
I 8
.\" Copyright (c) 1988, 1993 The Regents of the University of California.
E 8
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
E 4
.\"
D 3
.\"	@(#)1.t	6.1 (Berkeley) 5/14/86
E 3
I 3
.\"	%W% (Berkeley) %G%
E 3
.\"
.ds lq ``
.ds rq ''
.ds LH "Installing/Operating \*(4B
.ds RH Introduction
D 8
.ds CF \*(DY
E 8
I 8
.ds CF \*(Dy
E 8
.LP
D 8
.nr H1 1
E 8
.bp
D 8
.LG
.B
.ce
1. INTRODUCTION
.sp 2
.R
.NL
E 8
I 8
D 19
.NH 1
Introduction
E 19
I 19
.Sh 1 "Introduction"
E 19
E 8
.PP
D 2
This document explains how to install the \*(4B release of the Berkeley
E 2
I 2
D 11
This document explains how to install the Berkeley
E 11
I 11
This document explains how to install the \*(4B Berkeley
E 11
E 2
D 5
version of UNIX for the Tahoe on your system.  While this is the first
release from Berkeley for the Tahoe, the version of
E 5
I 5
D 8
version of \*(Ux for the \*(Th on your system.  While this is the first
release from Berkeley for the \*(Th, the version of
E 5
.UX
D 2
distributed by CCI is derived from 4.2BSD.  Consequently, the filesystem
E 2
I 2
distributed by Computer Consoles Inc. (CCI) was derived from 4.2BSD.
Consequently, the filesystem
E 2
format is compatible and it will only be necessary for you to perform
a full bootstrap procedure if you are installing the release on a new
machine.
D 2
The System V UNIX systems distributed by CCI, Sperry and Harris
E 2
I 2
D 5
The System V UNIX systems distributed by CCI, Unisys (Sperry) and Harris
E 5
I 5
The System V \*(Ux systems distributed by CCI, Unisys (Sperry) and Harris
E 5
E 2
are also derived from 4.2BSD, but only the network and filesystem
D 2
remain compatible with 4.2 and 4.3.
E 2
I 2
remain compatible with \*(4B.
E 2
The object file formats are completely different in the System V
releases.
E 8
I 8
D 12
version of \*(Ux on your system.
E 12
I 12
version of UNIX on your system.
E 12
The filesystem format is compatible with \*(Ps
and it will only be necessary for you to do a full bootstrap
procedure if you are installing the release on a new machine.
D 17
The object file formats are completely different in the System V releases.
E 8
Thus, the most straightforward procedure for upgrading a System V
D 2
system is to perform a full bootstrap.  The full bootstrap procecure
E 2
I 2
D 15
system is to perform a full bootstrap.
E 15
I 15
system is to do a full bootstrap.
E 17
I 17
The object file formats are completely different from the System
V release, so the most straightforward procedure for upgrading
a System V system is to do a full bootstrap.
E 17
E 15
.PP
The full bootstrap procedure
E 2
D 8
is outlined in chapter 2; the process includes booting standalone
utilities from tape to format a disk, if necessary, and then copying
a small root filesystem image onto a swap area.  This filesystem is
then booted and used to extract a dump of a standard root filesystem.
Finally, that root filesystem is booted, and the remainder of the system
binaries and sources are read from the archives on the tape(s).
E 8
I 8
D 13
is outlined in chapter 2; the process starts with copying a filesystem
E 13
I 13
is outlined in section 2; the process starts with copying a filesystem
E 13
image onto a new disk.
This filesystem is then booted and used to extract the remainder of the
system binaries and sources from the archives on the tape(s).
E 8
.PP
D 2
The technique for upgrading a 4.2BSD-based system is described
E 2
I 2
D 8
The technique for upgrading a 4.2 or beta-release 4.3BSD system is described
E 8
I 8
The technique for upgrading a \*(Ps system is described
E 8
E 2
D 13
in chapter 3 of this document.
E 13
I 13
in section 3 of this document.
E 13
D 2
As 4.3BSD is upward-compatible with 4.2BSD,
E 2
I 2
D 8
As \*(4B is completely compatible with the beta release,
and sufficiently compatible with the vendor-supplied 4.2BSD releases,
E 2
the upgrade procedure involves extracting a new set of system binaries
E 8
I 8
D 17
The upgrade procedure involves extracting a new set of system binaries
E 17
I 17
The upgrade procedure involves extracting system binaries
E 17
E 8
D 11
onto new root and /usr filesystems.
The sources are then extracted, and local configuration files are merged
D 2
into the new system.
4.2BSD user filesystems may up upgraded in place.
Some 4.2BSD binaries may be used with 4.3BSD in the course of the conversion.
However due to significant incompatibilities between the vendor derived
version of 4.2BSD and the \*(4B release, most binary images will not function
properly.  For such programs it will be necessary, as well as desirable,
to recompile this software after the conversion.  Consult section 3 for
a description of the differences between \*(4B and the previous systems
provided for the Tahoe.
E 2
I 2
into the new system.  User filesystems may be upgraded in place.
E 11
I 11
D 13
onto new root and /usr filesystems and local
E 13
I 13
onto new root and
.Pn /usr
D 17
filesystems and local
E 13
configuration files are merged into the new system.
E 17
I 17
filesystems and merging local
configuration files into the new system.
E 17
User filesystems may be upgraded in place.
E 11
D 8
All 4.3BSD-beta binaries may be used with \*(4B in the course
E 8
I 8
Most \*(Ps binaries may be used with \*(4B in the course
E 8
of the conversion.
It is desirable to recompile local sources after the conversion,
D 8
as the compilers have had many fixes installed.
However, due to significant incompatibilities between
the vendor-derived versions of 4.2BSD and the Berkeley \*(4B release, many
4.2BSD binary images will not function properly.  For such programs it
will be both necessary and desirable to recompile this software after
the conversion.  Consult section 3 for a description of the differences
D 5
between \*(4B and the previous vendor-supplied systems for the Tahoe.
E 5
I 5
between \*(4B and the previous vendor-supplied systems for the \*(Th.
E 8
I 8
D 11
as the compilers have had many fixes installed
and many new system call interfaces have been added.
E 11
I 11
as the new compiler (GCC) provides superior code optimization.
E 11
D 13
Consult section 3 for a description of the differences
between \*(4B and \*(Ps.
E 13
I 13
D 17
Consult section 3.5 for a description of the differences
E 17
I 17
Consult section 3.5 for a description of some of the differences
E 17
between \*(Ps and \*(4B.
E 13
E 8
E 5
E 2
D 19
.NH 2
D 8
Hardware supported
.PP
D 2
This distribution can be booted on a CCI Power 6/32, Harris HCX-7
or Sperry 7000/40
with any disks supported on the VERSABUS disk controllers
sold by these vendors (SMD/E or VDDC).
E 2
I 2
This distribution can be booted on a CCI Power 6/32, Harris HCX-7,
D 5
Unisys (Sperry) 7000/40, or ICL Clan 7 with any disks supported on the VERSAbus
E 5
I 5
Unisys (Sperry) 7000/40, or ICL Clan 7 with any disks supported on the \*(Vs
E 5
disk controllers sold by these vendors (SMD/E or VDDC).
E 2
The new CCI SMD/E controller with working scatter-gather I/O
is supported as well.
In particular, the following drives are supported:
.DS
.TS
l l.
FUJITSU 160M	CDC 9766 300M
FUJITSU 330M	CDC 340M
FUJITSU 2351 Eagle	CDC 515M
I 2
Maxtor 340M
E 2
.TE
.DE
I 5
The distribution can also be booted on a Harris HCX-9
using any disk on the HDC disk controller on the \*(Vm,
although the \*(Vm tapes are not currently supported.
E 5
.PP
D 5
The only tape drives supported by this distribution are the
D 2
ones attached to the Tapemaster tape controller.
E 2
I 2
ones attached to the Ciprico Tapemaster tape controller.
E 5
I 5
The only tape drives supported by this distribution are 9-track tape drives
attached to the Ciprico Tapemaster tape controller.
E 5
E 2
.NH 2
E 8
Distribution format
E 19
I 19
.Sh 2 "Distribution format"
E 19
.PP
The distribution comes in two formats:
.DS
D 2
(3)\0\0 1600bpi 2400' magnetic tapes, or
(1)\0\0 6250bpi 2400' magnetic tape
E 2
I 2
D 8
(3)\0\0 1600bpi  2400'  9-track magnetic tapes, or
(1)\0\0 6250bpi  2400'  9-track magnetic tape
E 8
I 8
(3)\0\0 6250bpi 2400' 9-track magnetic tapes, or
(1)\0\0 8mm Exabyte tape
E 8
E 2
.DE
D 2
Installation from scratch on any machine requires a tape unit. 
If your machine is currently running 4.2BSD and has a network
connection to a 4.2BSD or 4.3BSD machine with a tape drive,
it is a simple matter to install the software from a remote
tape drive.
E 2
I 2
D 8
Installation from scratch on any machine requires a tape unit.  If your
machine is currently running 4.2 or 4.3BSD-beta and has a network connection
to a 4.2 or 4.3BSD machine with a tape drive, it is a simple matter to
install the software from a remote tape drive.
E 8
E 2
.PP
D 2
If you have the facilities, it is a good idea to copy the
E 2
I 2
If you have the facilities, we \fBstrongly\fP recommend copying the
E 2
magnetic tape(s) in the distribution kit to guard against disaster.
D 2
The tapes are 9-track 1600 BPI or 6250 BPI and contain some
1024-byte records followed by many 10240-byte records.
There are interspersed tape marks; end-of-tape is signaled
by a double end-of-file.
.PP
The first file on the tape contains a very small file system
containing preliminary bootstrapping programs.
This is followed by a binary image
of a 2 megabyte ``mini root''
file system.  Following the mini root
file is a full dump of the root file system (see \fIdump\fP\|(8)*).
E 2
I 2
D 13
The tapes contain some 1024-byte records followed by many
10240-byte records.  There are interspersed tape marks;
end-of-tape is signaled by a double end-of-file.  The first file
D 8
on the tape is a very small file system containing
preliminary bootstrapping programs.  This is followed by a binary image
of an approximately 2 megabyte ``mini root'' file system.  Following
the mini root file is a full dump of the root file system
E 8
I 8
D 10
on the tape is a disk image of the root file system.
Following the disk-image root file is a full dump of the root file system
E 8
(see \fIdump\fP\|(8)*).
E 10
I 10
on the tape is a disk image of the root filesystem.
Following the disk-image root file is a full dump of the root filesystem
(see
D 11
.Xr dump (8)*).
E 11
I 11
.Xr dump (8)\**).
E 13
I 13
D 18
The tapes contain 20480-byte records.
E 18
I 18
The tapes contain \*(Bb-byte records.
E 18
There are interspersed tape marks;
end-of-tape is signaled by a double end-of-file.
The first file on the tape is architecture dependent.
Additional files on the tape(s)
contain tape archive images of the system binaries and sources (see
.Xr tar (1)\**).
E 13
E 11
E 10
E 2
.FS
D 2
* References of the form X(Y) mean the subsection named
X in section Y of the 
E 2
I 2
D 11
\ * References of the form \fIX\fP(Y) mean the entry named
\fIX\fP in section Y of the
E 2
.UX
programmer's manual.
E 11
I 11
References of the form \fIX\fP(Y) mean the entry named
\fIX\fP in section Y of the ``UNIX Programmer's Manual''.
E 11
.FE
D 13
Additional files on the tape(s)
D 2
contain tape archive images (see
E 2
I 2
contain tape archive images of the system binaries and sources (see
E 2
D 8
\fItar\fP\|(1)).  See Appendix A for a description of the contents
E 8
I 8
D 10
\fItar\fP\|(1)).  See the tape label for a description of the contents
E 10
I 10
.Xr tar (1)).
E 13
See the tape label for a description of the contents
E 10
E 8
D 11
and format of the tape(s).
E 11
I 11
and format of each individual tape.
E 11
D 8
One file contains software
contributed by the user community; refer to the accompanying
documentation for a description of its contents and an
explanation of how it should be installed.
E 8
D 19
.NH 2
D 8
Hardware terminology
.PP
D 2
This section gives a short discussion of the hardware terminology
E 2
I 2
This section gives a short discussion of hardware terminology
E 2
to help you get your bearings. 
.PP
D 2
The Power 6/32 (and the current HCX-7 machines being shipped) use
a VERSABUS for all i/o peripherals.  The console
processor used for bootstrap and diagnostic purposes
is also located on the VERSABUS.  The
terminology you must familiarize yourself with is necessary
to configure hardware devices on your machine.  The device naming
E 2
I 2
D 5
The Power 6/32 (and most related machines being shipped) use a VERSAbus
for all I/O peripherals.  The console processor used for bootstrap and
diagnostic purposes is also located on the VERSAbus.  The device naming
E 2
conventions described here apply to the console processor; under UNIX
E 5
I 5
The Power 6/32 (and most related machines being shipped) use a \*(Vs
for all I/O peripherals.
The console processor used for bootstrap and
diagnostic purposes is also located on the \*(Vs.
The Harris HCX-9 uses a \*(Vm instead of a \*(Vs; however, the architecture
is completely analogous, and the following discussion applies with the
exception of the name of the bus and the name of the disk controller.
The device naming
conventions described here apply to the console processor; under \*(Ux
E 5
D 2
device naming is simpler as you will soon see.
E 2
I 2
device naming is considerably simpler.
E 2
.PP
D 2
The VERSABUS is a 32-bit bus that supports devices which
E 2
I 2
D 5
The VERSAbus is a 32-bit bus that supports devices which
E 5
I 5
The \*(Vs is a 32-bit bus that supports devices which
E 5
E 2
use 16-bit, 24-bit, or 32-bit addresses (or some combination).
D 2
The type of each address placed on the VERSABUS is indicated
E 2
I 2
D 5
The type of each address placed on the VERSAbus is indicated
E 5
I 5
The type of each address placed on the \*(Vs is indicated
E 5
E 2
by an accompanying \fIaddress modifier\fP.  In addition to the
width of the
D 2
address present on the bus, VERSABUS address modifiers
E 2
I 2
D 5
address present on the bus, VERSAbus address modifiers
E 5
I 5
address present on the bus, \*(Vs address modifiers
E 5
E 2
may be used to indicate the privileges of the requesting
program (.e.g the program is executing in supervisory mode).
D 2
The 6/32's VERSABUS adapter accepts device requests with either
16, 24, or 32-bit address modifiers and interprets the address
E 2
I 2
D 5
The 6/32's VERSAbus adapter accepts device requests with either
E 5
I 5
The 6/32's \*(Vs adapter accepts device requests with either
E 5
16, 24, or 32-bit address modifiers.
16-bit addresses are used to access control registers
D 5
for VERSAbus devices.
24-bit addresses are used to access up to one megabyte of VERSAbus
E 5
I 5
for \*(Vs devices.
24-bit addresses are used to access up to one megabyte of \*(Vs
E 5
local memory or device shared memory
as well as the first 15Mb of main memory.
24-bit addresses are used for DMA by some peripherals,
interpreting the address
E 2
as an absolute physical address in referencing main memory.
D 2
This means that the address space for 16-bit devices overlaps
that of 24-bit devices and both overlap the address space
of 32-bit devices.  Devices which do not support full 32-bit
E 2
I 2
Other devices use 32-bit addressing, allowing them to access all
of main memory.
This means that the address space for 24-bit devices overlaps
that of 32-bit devices.
Devices which do not support full 32-bit
E 2
addressing can be difficult to work with as their limited addressing
D 2
restricts the placement of i/o buffers in main memory.  Unfortunately,
because the VERSABUS has had limited acceptance there are
very few good VERSABUS device controllers available; this has
resulted in several non-VERSABUS devices being attached to the
VERSABUS through bus-adapter cards.  Devices of this sort often
support only 16-bit or 24-bit addressing.
E 2
I 2
restricts the placement of I/O buffers in main memory.  Unfortunately,
D 5
because the VERSAbus has had limited acceptance, there are
very few good VERSAbus device controllers available; this has
resulted in several non-VERSAbus devices being attached to the
VERSAbus through bus-adapter cards.  Devices of this sort often
E 5
I 5
because the \*(Vs has had limited acceptance, there are
very few good \*(Vs device controllers available; this has
resulted in several non-\*(Vs devices being attached to the
\*(Vs through bus-adapter cards.  Devices of this sort often
E 5
support only 20-bit or 24-bit addressing.
E 2
.PP
D 2
From the Tahoe side of the VERSABUS adaptor, when memory management
is enabled, the three address spaces are mapped so as to avoid
overlaps.  Addresses in the range 0xffff0000 to 0xfffffff are
used to access VERSABUS devices which use 16-bit addresses.  References
to this region of the Tahoe address space result in a VERSABUS
E 2
I 2
D 5
From the Tahoe side of the VERSAbus adaptor,
E 5
I 5
From the \*(Th side of the \*(Vs adaptor,
E 5
the three address spaces are mapped so as to avoid
overlaps.  Physical addresses in the range 0xffff0000 to 0xfffffff are
D 5
used to access VERSAbus devices which use 16-bit addresses.  References
to this region of the Tahoe address space result in a VERSAbus
E 5
I 5
used to access \*(Vs devices which use 16-bit addresses.  References
to this region of the \*(Th address space result in a \*(Vs
E 5
E 2
transfer with a 16-bit address generated from the lower order 16
D 2
bits of the memory address and a ``short addressing non-privileged i/o
E 2
I 2
bits of the memory address and a ``short addressing non-privileged I/O
E 2
access'' address modifier (0x10).  Addresses in the range 0xff000000 to
D 2
0xffff0000 are used to access 24-bit VERSABUS devices, generating a 24-bit
E 2
I 2
D 5
0xffff0000 are used to access 24-bit VERSAbus devices, generating a 24-bit
E 5
I 5
0xffff0000 are used to access 24-bit \*(Vs devices, generating a 24-bit
E 5
E 2
address and a ``standard addressing non-privileged data access''
D 2
address modifier (0x01).  Finally, any other address in the
the primary i/o adapter space, 0xf0000000 to 0xff000000, generates
a 32-bit VERSABUS address with an ``extended addressing non-privileged
E 2
I 2
address modifier (0x01).
Within this range, addresses from 0xfff00000 to 0xffff0000 refer
D 5
to VERSAbus local memory used by devices (such as the VIOC)
E 5
I 5
to \*(Vs local memory used by devices (such as the VIOC)
E 5
for shared communication areas.
Finally, any other address in the
the primary I/O adapter space, 0xc0000000 to 0xff000000, generates
D 5
a 32-bit VERSAbus address with an ``extended addressing non-privileged
E 5
I 5
a 32-bit \*(Vs address with an ``extended addressing non-privileged
E 5
E 2
data access'' address modifier (0xf1).  Note, however, that 32-bit
D 2
addresses generated by references to this region result in a VERSABUS
E 2
I 2
D 5
addresses generated by references to this region result in a VERSAbus
E 5
I 5
addresses generated by references to this region result in a \*(Vs
E 5
E 2
address with bits 31-30 set to 0.  Thus, for example, a reference to
D 2
a device located at 0xfe000000 would result in a VERSABUS transfer
E 2
I 2
D 5
a device located at 0xfe000000 would result in a VERSAbus transfer
E 5
I 5
a device located at 0xfe000000 would result in a \*(Vs transfer
E 5
E 2
with the address set to 0x3e000000.  A complete list of the characteristics
of the devices supported in the system may be found in Appendix A.
.PP
D 5
The console processor has a set of names for devices:
E 5
I 5
The console processor on most \*(Vs machines has a set of names for devices:
E 5
.DS
.TS
l l.
FUJITSU 160M disk drives	fsd
FUJITSU 330M disk drives	fuj
D 2
FUJITSU 450M disk drives	egl*
E 2
I 2
FUJITSU 450M disk drives	egl**
E 2
CDC 300M disk drives	smd
CDC 340M disk drives	xfd
CDC 515M disk drives	xsd
I 2
MXD Maxtor 340M disk drives	mxd
E 2
Cipher tape drives	cyp
.TE
.FS
D 2
*\|Eagle drives are currently supported only by the HCX-7 console
processor.
E 2
I 2
**\|Eagle drives are not supported by the console processor on all tahoe
machines.
E 2
.FE
.DE
Devices are fully specified to the console processor with:
.DS
xxx(y,z)
.DE
where \fIxxx\fP is one of the above names (e.g. \fIxfd\fP).
The value \fIy\fP specifies a controller to use and also
the device; it is computed as
.DS
8 * \fIcontroller\fP + \fIdevice\fP
.DE
D 2
Thus, controller 0 (by convention the controller located at VERSABUS
E 2
I 2
D 5
Thus, controller 0 (by convention the controller located at VERSAbus
E 5
I 5
Thus, controller 0 (by convention the controller located at \*(Vs
E 5
E 2
address 0xfff2400), drive 0 would have a \fIy\fP value of 0
while controller 1 (address of 0xfff2800) drive 0 would have a \fIy\fP
D 2
value of 4**.
E 2
I 2
value of 4*.
E 2
.FS
D 2
**\|Note that this means you can not reference drives 5-15 on a
E 2
I 2
*\|Note that this means you can not reference drives 4-15 on a
E 2
controller; as a result we expect the console interface to
change soon.
.FE
The \fIz\fP value is interpreted differently for tapes and disks;
for disks it is a disk block, and for tapes it is a file number
on the tape.
.PP
I 5
The HCX-9 uses different controllers and terminology:
.DS
.TS
l l.
disks on HDC controller	dsk
Xylogics tapes	???
.TE
.DE
Devices are fully specified to the console processor with:
.DS
xxx(x,y,z)
.DE
where \fIxxx\fP is one of the above names (e.g. \fIdsk\fP).
The value \fIy\fP specifies the device unit number.
Thus, controller 0 (by convention the controller located at \*(Vs
address 0xfff2400), drive 0 would have a \fIy\fP value of 0
while controller 1 (address of 0xfff2800) drive 0 would have a \fIy\fP
value of 4*.
The \fIz\fP value is interpreted as on the other systems.
.PP
E 5
The console processor has the notion of a \fIdefault device\fP
to use with file related commands.  The default device is specified
according to the form shown above.  Further, the console processor,
by default, interprets certain system files on the default disk to discover
information about disk drives in the system.  As
.UX
device names are decidedly different from the names used by the
console processor this can lead to serious confusion.  We will
D 2
return to this problem later in \(sc4.2.1; for now you should
E 2
I 2
return to this problem later in section 4; for now you should
E 2
simply be aware of the difference in naming conventions.
.NH 2
E 8
D 5
UNIX device naming
E 5
I 5
D 12
\*(Ux device naming
E 12
I 12
UNIX device naming
E 19
I 19
.Sh 2 "UNIX device naming"
E 19
E 12
E 5
.PP
D 5
UNIX has a set of names for devices which are different
E 5
I 5
D 8
\*(Ux has a set of names for devices which are different
E 5
from the CCI names for the devices, viz.:
.DS
.TS
l l.
D 2
VERSABUS disk drives	dk
E 2
I 2
D 5
VERSAbus disk drives	dk
E 5
I 5
\*(Vs (SMD/E, VDDC) disk drives	dk
\*(Vm (HDC) disk drives	hd
E 5
E 2
Cipher tape drives	cy
.TE
.DE
.PP
D 5
The standalone system, used to bootstrap the full UNIX system,
E 5
I 5
The standalone system, used to bootstrap the full \*(Ux system,
E 8
I 8
D 9
The standalone system, used to boot the full \*(Ux system,
E 8
E 5
D 2
uses device names:
E 2
I 2
uses device names of the form:
E 2
.DS
D 2
xx(y,z)
E 2
I 2
xx(c,d,p)
E 2
.DE
D 2
where \fIxx\fP is either \fBdk\fP, or \fBcy\fP.
The value \fIy\fP
specifies the controller to use and also the device;  it is computed as
.DS
8 * \fIcontroller\fP + \fIdevice\fP
.DE
Thus controller 0 device 0 would have a \fIy\fP value of 0 while
controller 1 device 0 would have a \fIy\fP value of 4.  The \fIz\fP
value is interpreted differently for tapes and disks:
for disks it is a disk \fIpartition\fP (in the range 0-7),
and for tapes it is a file number on the tape.
E 2
I 2
D 8
where \fIxx\fP is the device type, normally \fIdk\fP or \fIcy\fP.  The
value \fIc\fP specifies the controller to use, and \fId\fP specifies
E 8
I 8
where \fIxx\fP is the device type, normally \fI\*(Dk\fP or \fI\*(Mt\fP.
The value \fIc\fP specifies the controller to use, and \fId\fP specifies
E 8
the device.  The \fIp\fP value is interpreted differently for tapes
and disks: for disks it is a disk \fIpartition\fP (in the range 0-7),
and for tapes it is a file number offset on the tape.  Thus, partition
D 8
1 of a ``dk'' type disk drive on controller vd0 at drive 0 would be
``dk(0,0,1)''.  Normally the controller will be controller 0; it
E 8
I 8
1 of a ``\*(Dk'' type disk drive on controller 0 at unit 2 would be
``\*(Dk(0,2,1)''.  Normally the controller will be controller 0; it
E 8
may therefore be omitted from the device specification, and most of
D 8
the examples in this document reflect this.  When not running
standalone, this partition would normally be available as ``/dev/dk0b''.
E 8
I 8
the examples in this document reflect this convention.  When not running
standalone, this partition would normally be available as ``/dev/\*(Dk2b''.
E 8
Here the prefix ``/dev'' is the name of the directory where all
D 8
``special files'' normally live, the ``dk'' serves the obvious purpose,
the ``0'' identifies this as a partition of dk drive number ``0'' and
E 8
I 8
``special files'' normally live, the ``\*(Dk'' serves the obvious purpose,
the ``2'' identifies this as a partition of \*(Dk drive number ``2'' and
E 8
the ``b'' identifies this as the second partition.
E 9
I 9
Device names have a different syntax depending on whether you are talking
D 12
to the standalone system or a running \*(Ux kernel.
E 12
I 12
to the standalone system or a running UNIX kernel.
E 12
The standalone system syntax is currently architecture dependent and is
D 14
described in the various architecture specific sections.
E 14
I 14
described in the various architecture specific sections as applicable.
E 14
D 13
When not running standalone, devices are available via files in
the ``/dev/'' directory.
E 13
I 13
When not running standalone, devices are available via files in the
.Pn /dev/
directory.
E 13
The file name typically encodes the device type, its logical unit and
a partition within that unit.
D 13
For example, ``/dev/sd2b'' refers to the second partition (``b'') of
D 11
SCSI (``sd'') drive number ``2'', while ``/dev/mt0'' refers to 9-track
E 11
I 11
SCSI (``sd'') drive number ``2'', while ``/dev/rmt0'' refers to 9-track
E 11
tape (``mt'') unit ``0''.
E 13
I 13
For example,
.Pn /dev/sd2b
refers to the second partition (``b'') of
SCSI (``sd'') drive number ``2'', while
.Pn /dev/rmt0
D 14
refers to 9-track tape (``mt'') unit ``0''.
E 14
I 14
refers to the raw (``r'') interface of 9-track tape (``mt'') unit ``0''.
E 14
E 13
E 9
E 2
.PP
I 9
The mapping of physical addressing information (e.g. controller, target)
to a logical unit number is dependent on the system configuration.
E 9
D 2
Each UNIX physical disk is divided into 8 logical disk partitions,
each of which may occupy any consecutive cylinder range on the
physical device.  The cylinders occupied
by the 8 partitions for each drive type
are specified initially in section 4 of the programmers manual
and in the disk description file /etc/disktab (c.f.
\fIdisktab\fP(5)).
The partition information and description of the drive geometry
are written in the first sector of each disk
with the \fIdisklabel\|\fP(8) program.
Each partition may be used
for either a raw data area such as a paging area or to store a
UNIX file system.
E 2
I 2
In all simple cases, where only a single controller is present, a drive
D 9
with unit number 0 (determined by its unit plug on the front of the drive)
D 5
will be called unit 0 in its UNIX file name.  This is not, however, strictly
E 5
I 5
will be called unit 0 in its \*(Ux file name.  This is not, however, strictly
E 9
I 9
D 11
with physical unit number 0 (e.g., as determined by its unit plug on the
front of the drive) will be called unit 0 in its \*(Ux file name.
E 11
I 11
with physical unit number 0 (e.g., as determined by its unit
D 13
specification (either unit plug or other selection mechanism)
E 13
I 13
specification, either unit plug or other selection mechanism)
E 13
D 12
will be called unit 0 in its \*(Ux file name.
E 12
I 12
will be called unit 0 in its UNIX file name.
E 12
E 11
This is not, however, strictly
E 9
E 5
necessary, since the system has a level of indirection in this naming.
If there are multiple controllers, the disk unit numbers will normally
be counted sequentially across controllers.  This can be taken
advantage of to make the system less dependent on the interconnect
D 11
topology, and to make reconfiguration after hardware failure extremely
easy.
E 11
I 11
topology, and to make reconfiguration after hardware failure easier.
E 11
.PP
D 5
Each UNIX physical disk is divided into at most 8 logical disk partitions,
E 5
I 5
D 12
Each \*(Ux physical disk is divided into at most 8 logical disk partitions,
E 12
I 12
Each UNIX physical disk is divided into at most 8 logical disk partitions,
E 12
E 5
each of which may occupy any consecutive cylinder range on the physical
device.  The cylinders occupied by the 8 partitions for each drive type
D 13
are specified initially in the disk description file /etc/disktab
E 13
I 13
are specified initially in the disk description file
.Pn /etc/disktab
E 13
D 10
(c.f. \fIdisktab\fP(5)).  The partition information and description of the
E 10
I 10
(c.f.
.Xr disktab (5)).
The partition information and description of the
E 10
D 9
drive geometry are written in the first sector of each disk with the
E 9
I 9
drive geometry are written in one of the first sectors of each disk with the
E 9
D 10
\fIdisklabel\|\fP(8) program.  Each partition may be used for either a
D 5
raw data area such as a paging area or to store a UNIX file system.
E 5
I 5
raw data area such as a paging area or to store a \*(Ux file system.
E 10
I 10
.Xr disklabel (8)
program.  Each partition may be used for either a
D 12
raw data area such as a paging area or to store a \*(Ux filesystem.
E 12
I 12
raw data area such as a paging area or to store a UNIX filesystem.
E 12
E 10
E 5
E 2
It is conventional for the first partition on a disk to be used
D 5
to store a root file system, from which UNIX may be bootstrapped.
E 5
I 5
D 10
to store a root file system, from which \*(Ux may be bootstrapped.
E 10
I 10
D 12
to store a root filesystem, from which \*(Ux may be bootstrapped.
E 12
I 12
to store a root filesystem, from which UNIX may be bootstrapped.
E 12
E 10
E 5
The second partition is traditionally used as a paging area, and the
rest of the disk is divided into spaces for additional ``mounted
D 10
file systems'' by use of one or more additional partitions.
E 10
I 10
filesystems'' by use of one or more additional partitions.
E 10
D 8
.PP
D 2
The disk partitions have names in the standalone system of the form
``dk(y,z)'' with varying \fIy\fP as described above.  Thus partition
1 of a Fujitsu Eagle on controller vd0 at drive 0 would be
``dk(0,1)''.  When not running
standalone, this partition would normally be available as ``/dev/dk0b''.
Here the prefix ``/dev'' is the name of the directory where all
``special files'' normally live, the ``dk'' serves an obvious purpose,
the ``0'' identifies this as a partition of dk drive number ``0''
and the ``b'' identifies this as the second partition.
.PP
In all simple cases, a drive with unit number 0 (in its unit
plug on the front of the drive) will be called unit 0 in its UNIX
file name.  This is not, however, strictly necessary, since the system
has a level of indirection in this naming.
If there are multiple controllers, the disk unit numbers
will normally be counted sequentially across controllers.
This can be taken
advantage of to make the system less dependent on the interconnect
topology, and to make reconfiguration after hardware
failure extremely easy.  We will not discuss that now.
.PP
E 2
Returning to the discussion of the standalone system, we recall
D 2
that tapes also took two integer parameters.  In the normal case
E 2
I 2
that tapes also took three integer parameters.  In the normal case
E 2
D 5
where the Cipher tape drive is unit 0 on the first controller, the
D 2
files on the tape have names ``cy(0,0)'', ``cy(0,1)'', etc.
E 2
I 2
files on the tape have names ``cy(0, 0)'', ``cy(0, 1)'', etc.
E 2
Here ``file'' means a tape file containing a single data stream.
The distribution tape(s) have data structures in the tape
files and though the tape(s) contain only 9 tape files, they contain
several thousand UNIX files.
E 5
I 5
where the Cipher tape drive is unit 0 on the first controller
(the only unit supported by the standalone utilities), the
files on the tape have names ``cy(0,0,0)'' (or just ``cy(0,0)'',
``cy(0,1)'', etc.
Here ``file'' means a tape file containing a single data stream
terminated by a tape mark.*
.FS
* Note that while a tape file consists of a single data stream,
the distribution tape(s) have data structures in these files.
Although the tape(s) contain only a few tape files, they comprise
several thousand \*(Ux files.
.FE
E 8
E 5
D 19
.NH 2
D 5
UNIX devices: block and raw
E 5
I 5
D 12
\*(Ux devices: block and raw
E 12
I 12
UNIX devices: block and raw
E 19
I 19
.Sh 2 "UNIX devices: block and raw"
E 19
E 12
E 5
.PP
D 5
UNIX makes a distinction between ``block'' and ``raw'' (character)
E 5
I 5
D 12
\*(Ux makes a distinction between ``block'' and ``raw'' (character)
E 12
I 12
UNIX makes a distinction between ``block'' and ``raw'' (character)
E 12
E 5
devices.  Each disk has a block device interface where
the system makes the device byte addressable and you can write
a single byte in the middle of the disk.  The system will read
out the data from the disk sector, insert the byte you gave it
and put the modified data back.  The disks with the names
D 2
``/dev/xx0a'', etc are block devices.
E 2
I 2
D 13
``/dev/xx0[a-h]'', etc., are block devices.
E 13
I 13
.Pn /dev/xx0[a-h] ,
etc., are block devices.
E 13
E 2
There are also raw devices available.
D 2
These have names like ``/dev/rxx0a'', the
E 2
I 2
D 13
These have names like ``/dev/rxx0[a-h]'', the
E 2
``r'' here standing for ``raw''.
E 13
I 13
These have names like
.Pn /dev/rxx0[a-h] ,
the ``r'' here standing for ``raw''.
E 13
Raw devices bypass the buffer cache and use DMA directly to/from
the program's I/O buffers;
they are normally restricted to full-sector transfers.
In the bootstrap procedures we
will often suggest using the raw devices, because these tend
to work faster.
Raw devices are used when making new filesystems,
when checking unmounted filesystems,
or for copying quiescent filesystems.
D 10
The block devices are used to mount file systems,
E 10
I 10
D 16
The block devices are used to mount filesystems,
E 10
or when operating on a mounted filesystem such as the root.
E 16
I 16
The block devices are used to mount filesystems.
E 16
.PP
You should be aware that it is sometimes important whether to use
D 13
the character device (for efficiency) or not (because it wouldn't
E 13
I 13
the character device (for efficiency) or not (because it would not
E 13
work, e.g. to write a single byte in the middle of a sector).
D 13
Don't change the instructions by using the wrong type of device
E 13
I 13
Do not change the instructions by using the wrong type of device
E 13
indiscriminately.
E 1
