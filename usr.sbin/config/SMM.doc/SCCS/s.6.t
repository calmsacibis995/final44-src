h06539
s 00002/00002/00211
d D 8.1 93/06/08 14:01:00 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00507/00208
d D 6.4 93/06/06 12:09:35 mckusick 5 4
c crude update for 4.4BSD
e
s 00004/00003/00711
d D 6.3 91/04/17 11:35:03 bostic 4 3
c new copyright; att/bsd/shared
e
s 00193/00150/00521
d D 6.2 86/06/03 18:05:23 karels 3 2
c 4.3 version
e
s 00000/00000/00671
d D 6.1 86/05/25 16:39:35 mckusick 2 1
c 4.3BSD beta release document
e
s 00671/00000/00000
d D 5.1 86/05/25 16:39:24 mckusick 1 0
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
.ds RH "Adding New Devices
.ds CF July 27, 1983
.LP
.nr H2 0
.nr H1 6
.ds CH "
.bp
.ds CH "\(hy \\n(PN \(hy
.LG
.B
.ce
6. ADDING NEW SYSTEM SOFTWARE
.sp 2
.R
.NL
E 3
I 3
.\".ds RH "Adding New Devices
.ne 2i
.NH
ADDING NEW SYSTEM SOFTWARE
E 3
.PP
This section is not for the novice, it describes
some of the inner workings of the configuration process as
well as the pertinent parts of the system autoconfiguration process.
It is intended to give
those people who intend to install new device drivers and/or
other system facilities sufficient information to do so in the
manner which will allow others to easily share the changes.
.PP
This section is broken into four parts:
.IP \(bu 3
general guidelines to be followed in modifying system code,
.IP \(bu 3
D 3
how to add a device driver to 4.2BSD,
E 3
I 3
D 5
how to add non-standard system facilities to 4.3BSD,
E 5
I 5
how to add non-standard system facilities to 4.4BSD,
E 5
E 3
.IP \(bu 3
D 3
how UNIBUS device drivers are autoconfigured under 4.2BSD on the VAX, and
E 3
I 3
D 5
how to add a device driver to 4.3BSD, and
E 3
.IP \(bu 3
D 3
how to add non-standard system facilities to 4.2BSD.
E 3
I 3
how UNIBUS device drivers are autoconfigured under 4.3BSD on the VAX.
E 5
I 5
how to add a device driver to 4.4BSD, and
E 5
E 3
.NH 2
Modifying system code
.PP
If you wish to make site-specific modifications to the system
it is best to bracket them with
.DS
#ifdef SITENAME
\&...
#endif
.DE
to allow your source to be easily distributed to others, and
also to simplify \fIdiff\fP\|(1) listings.  If you choose not
to use a source code control system (e.g. SCCS, RCS), and
perhaps even if you do, it is
recommended that you save the old code with something
of the form:
.DS
#ifndef SITENAME
\&...
#endif
.DE
We try to isolate our site-dependent code in individual files
which may be configured with pseudo-device specifications.
.PP
D 3
Indicate machine specific code with ``#ifdef vax''.  4.2BSD
has undergone extensive work to make it extremely portable to
machines with similar architectures \- you may someday find
E 3
I 3
Indicate machine-specific code with ``#ifdef vax'' (or other machine,
as appropriate).
D 5
4.2BSD underwent extensive work to make it extremely portable to
E 5
I 5
4.4BSD underwent extensive work to make it extremely portable to
E 5
machines with similar architectures\- you may someday find
E 3
yourself trying to use a single copy of the source code on
multiple machines.
D 5
.PP
Use \fIlint\fP periodically if you make changes to the system.
D 3
The 4.2BSD release has only one line of lint in it.  It
E 3
I 3
The 4.3BSD kernel has only two lines of lint in it.  It
E 3
is very simple to lint the kernel.  Use the LINT configuration
file, designed to pull in as much of the kernel source code as
possible, in the following manner.
.DS
$ cd /sys/conf
$ mkdir ../LINT
$ config LINT
$ cd ../LINT
$ make depend
$ make assym.s
$ make \-k lint > linterrs 2>&1 &
(or for users of \fIcsh\fP\|(1))
% make \-k >& linterrs
.DE
D 3
This takes about 45 minutes on a lightly loaded
E 3
I 3
This takes about an hour on a lightly loaded
E 3
VAX-11/750, but is well worth it.
E 5
.NH 2
D 3
Adding device drivers to 4.2BSD
E 3
I 3
Adding non-standard system facilities
E 3
.PP
D 3
The i/o system and
E 3
I 3
This section considers the work needed to augment 
.IR config 's
data base files for non-standard system facilities.
.I Config
uses a set of files that list the source modules that may be required
when building a system.
The data bases are taken from the directory in which
E 3
.I config
I 3
is run, normally /sys/conf.
Three such files may be used:
.IR files ,
.IR files .machine,
and
.IR files .ident.
The first is common to all systems,
the second contains files unique to a single machine type,
and the third is an optional list of modules for use on a specific machine.
This last file may override specifications in the first two.
The format of the 
.I files
file has grown somewhat complex over time.  Entries are normally of
the form
.IP
.nf
.DT
\fIdir/source.c\fP	\fItype\fP	 \fIoption-list\fP \fImodifiers\fP
.LP
for example,
.IP
.nf
.DT
\fIvaxuba/foo.c\fP	\fBoptional\fP	foo	\fBdevice-driver\fP
.LP
The
.I type
is one of
.B standard
or
.BR optional .
Files marked as standard are included in all system configurations.
Optional file specifications include a list of one or more system
options that together require the inclusion of this module.
The options in the list may be either names of devices that may
be in the configuration file,
or the names of system options that may be defined.
An optional file may be listed multiple times with different options;
if all of the options for any of the entries are satisfied,
the module is included.
.PP
If a file is specified as a
.IR device-driver ,
any special compilation options for device drivers will be invoked.
On the VAX this results in the use of the
.B \-i
option for the C optimizer.  This is required when pointer references
are made to memory locations in the VAX I/O address space.
.PP
Two other optional keywords modify the usage of the file.
.I Config
understands that certain files are used especially for
kernel profiling.  These files are indicated in the
.I files
files with a 
.I profiling-routine
keyword.  For example, the current profiling subroutines
are sequestered off in a separate file with the following
entry:
.IP
.nf
.DT
\fIsys/subr_mcount.c\fP	\fBoptional\fP	\fBprofiling-routine\fP
.fi
.LP
The 
.I profiling-routine
keyword forces
.I config
not to compile the source file with the 
.B \-pg
option.
.PP
The second keyword which can be of use is the
.I config-dependent
keyword.  This causes
.I config
to compile the indicated module with the global configuration
parameters.  This allows certain modules, such as
.I machdep.c
to size system data structures based on the maximum number
of users configured for the system.
.NH 2
D 5
Adding device drivers to 4.3BSD
E 5
I 5
Adding device drivers to 4.4BSD
E 5
.PP
The I/O system and
.I config
E 3
have been designed to easily allow new device support to be added.
D 3
As described in ``Installing and Operating 4.2BSD on the VAX'',
the system source directories are organized as follows:
E 3
I 3
The system source directories are organized as follows:
E 3
.DS
.TS
lw(1.0i) l.
/sys/h	machine independent include files
D 3
/sys/sys	machine independent system source files
E 3
I 3
/sys/sys	machine-independent system source files
E 3
/sys/conf	site configuration files and basic templates
D 3
/sys/net	network independent, but network related code
E 3
I 3
/sys/net	network-protocol-independent, but network-related code
E 3
/sys/netinet	DARPA Internet code
/sys/netimp	IMP support code
D 3
/sys/netpup	PUP-1 support code
/sys/vax	VAX specific mainline code
E 3
I 3
/sys/netns	Xerox NS code
/sys/vax	VAX-specific mainline code
E 3
/sys/vaxif	VAX network interface code
/sys/vaxmba	VAX MASSBUS device drivers and related code
/sys/vaxuba	VAX UNIBUS device drivers and related code
.TE
.DE
.PP
Existing block and character device drivers for the VAX 
reside in ``/sys/vax'', ``/sys/vaxmba'', and ``/sys/vaxuba''.  Network
interface drivers reside in ``/sys/vaxif''.  Any new device
drivers should be placed in the appropriate source code directory
and named so as not to conflict with existing devices.
Normally, definitions for things like device registers are placed in
a separate file in the same directory.  For example, the ``dh''
device driver is named ``dh.c'' and its associated include file is
named ``dhreg.h''.
.PP
Once the source for the device driver has been placed in a directory,
the file ``/sys/conf/files.machine'', and possibly
``/sys/conf/devices.machine'' should be modified.  The 
.I files
D 3
files in the conf directory contain a line for each source or binary-only
E 3
I 3
files in the conf directory contain a line for each C source or binary-only
E 3
file in the system.  Those files which are machine independent are
D 3
located in ``/sys/conf/files'' while machine specific files
are in ``/sys/conf/files.machine''.  The ``devices.machine'' file
E 3
I 3
located in ``/sys/conf/files,'' while machine specific files
are in ``/sys/conf/files.machine.''  The ``devices.machine'' file
E 3
is used to map device names to major block device numbers.  If the device
driver being added provides support for a new disk
you will want to modify this file (the format is obvious).
.PP
D 3
The format of the 
E 3
I 3
In addition to including the driver in the
E 3
.I files
D 3
file has grown somewhat complex over time.  Entries are normally of
the form
.IP
.nf
.DT
\fIvaxuba/foo.c\fP	\fBoptional\fP foo \fBdevice-driver\fP
.LP
where the keyword 
.I optional
indicates that to compile the ``foo''
driver into the system it must be specified in the configuration file.
If instead the driver is specified as 
.IR standard ,
the file
will be loaded no matter what configuration is requested.
This is not normally done with device drivers.  The fact that
the file is specified as a
.I device-driver
results, on the VAX, in the compilation including a
.B \-i
option for the C optimizer.  This is required when pointer references
are made to memory locations in the VAX i/o address space.
.PP
Aside from including the driver in the
.I files
E 3
file, it must also be added to the device configuration tables.  These
are located in ``/sys/vax/conf.c'', or similar for machines other than
the VAX.  If you don't understand what to add to this file, you should
study an entry for an existing driver. 
D 3
Remember that the position in the block
device table specifies what the major block device number is, this is
needed in the ``devices.machine'' file if the device is a disk.
E 3
I 3
Remember that the position in the
device table specifies the major device number.
The block major number is needed in the ``devices.machine'' file
if the device is a disk.
E 3
.PP
With the configuration information in place, your configuration
file appropriately modified, and a system reconfigured and rebooted
you should incorporate the shell commands needed to install the special
files in the file system to the file ``/dev/MAKEDEV'' or
``/dev/MAKEDEV.local''.  This is discussed in the document ``Installing
D 3
and Operating 4.2BSD on the VAX''.
E 3
I 3
D 5
and Operating 4.3BSD on the VAX''.
E 3
.NH 2
Autoconfiguration on the VAX
.PP
D 3
4.2BSD (and 4.1BSD) require all device drivers to conform to a
E 3
I 3
4.3BSD requires all device drivers to conform to a
E 3
set of rules which allow the system to:
.IP 1)
support multiple UNIBUS and MASSBUS adapters,
.IP 2)
support system configuration at boot time, and
.IP 3)
manage resources so as not to crash when devices request
resources which are unavailable.
.LP
In addition, devices such as the RK07 which require
everyone else to get off the UNIBUS when they are running
need cooperation from other DMA devices if they are to work.
Since it is unlikely that you will be writing a device driver
for a MASSBUS device, this section is devoted exclusively to
D 3
describing the i/o system and autoconfiguration process as it
E 3
I 3
describing the I/O system and autoconfiguration process as it
E 3
applies to UNIBUS devices.
.PP
Each UNIBUS on a VAX has a set of resources:
.IP \(bu
D 3
496 map registers which are used to convert from the 18 bit UNIBUS
addresses into the much larger VAX address space.
E 3
I 3
496 map registers which are used to convert from the 18-bit UNIBUS
addresses into the much larger VAX memory address space.
E 3
.IP \(bu
Some number of buffered data paths (3 on an 11/750, 15 on an 11/780, 0
on an 11/730) which are used by high speed devices to transfer
data using fewer bus cycles.
.LP
There is a structure of type \fIstruct uba_hd\fR in the system per UNIBUS 
adapter used to manage these resources.  This structure also contains
a linked list where devices waiting for resources to complete DMA UNIBUS
activity have requests waiting.
.PP
There are three central structures in the writing of drivers for UNIBUS
D 3
controllers; devices which do not do DMA i/o can often use only two
E 3
I 3
controllers; devices which do not do DMA I/O can often use only two
E 3
of these structures.  The structures are \fIstruct uba_ctlr\fR, the
UNIBUS controller structure, \fIstruct uba_device\fR the UNIBUS
device structure, and \fIstruct uba_driver\fR, the UNIBUS driver structure.
The \fIuba_ctlr\fR and \fIuba_device\fR structures are in
one-to-one correspondence with the definitions of controllers and
devices in the system configuration.
Each driver has a \fIstruct uba_driver\fR structure specifying an internal
interface to the rest of the system.
.PP
Thus a specification
.DS
controller sc0 at uba0 csr 0176700 vector upintr
.DE
would cause a \fIstruct uba_ctlr\fR to be declared and initialized in
the file \fIioconf.c\fR for the system configured from this description.
Similarly specifying
.DS
disk up0 at sc0 drive 0
.DE
would declare a related \fIuba_device\fR in the same file.
The \fIup.c\fR driver which implements this driver specifies in
its declarations:
.DS
int     upprobe(), upslave(), upattach(), updgo(), upintr();
struct  uba_ctlr *upminfo[NSC];
struct  uba_device *updinfo[NUP];
u_short upstd[] = { 0776700, 0774400, 0776300, 0 };
struct  uba_driver scdriver =
    { upprobe, upslave, upattach, updgo, upstd, "up", updinfo, "sc", upminfo };
.DE
initializing the \fIuba_driver\fR structure.
The driver will support some number of controllers named \fIsc0\fR, \fIsc1\fR,
etc, and some number of drives named \fIup0\fR, \fIup1\fR, etc. where the
drives may be on any of the controllers (that is there is a single
linear name space for devices, separate from the controllers.)
.PP
We now explain the fields in the various structures.  It may help
D 3
to look at a copy of \fIvaxuba/ubareg.h\fR, \fIh/ubavar.h\fR and drivers
E 3
I 3
to look at a copy of \fIvaxuba/ubareg.h\fR, \fIvaxuba/ubavar.h\fR and drivers
E 3
such as \fIup.c\fR and \fIdz.c\fR while reading the descriptions of
the various structure fields.
.SH
uba_driver structure
.PP
One of these structures exists per driver.  It is initialized in
the driver and contains functions used by the configuration program
and by the UNIBUS resource routines.  The fields of the structure are:
.IP \fBud_probe\fP
D 3
A routine which is given a \fIcaddr_t\fR address as argument and
should cause an interrupt on the device whose control-status register
is at that address in virtual memory.  It may be the case that the
device does not exist, so the probe routine should use delays (via
the DELAY(n) macro which delays for \fIn\fR microseconds) rather than
E 3
I 3
A routine which, given a \fIcaddr_t\fR address as argument,
should attempt to determine that the device is present
at that address in virtual memory,
and should cause an interrupt from the device.
When probing controllers, two additional arguments are supplied:
the controller index, and a pointer to the \fIuba_ctlr\fP structure.
Device probe routines receive a pointer to the \fIuba_device\fP structure
as second argument.
Both of these structures are described below.
Neither is normally used, but devices that must record status or device
type information from the probe routine may require them.
.PP
The autoconfiguration routine attempts to verify that the specified address
responds before calling the probe routine.
However, the device may not actually exist or may be of a different type,
and therefore the probe routine should use delays
(via the DELAY(n) macro which delays for \fIn\fR microseconds) rather than
E 3
waiting for specific events to occur.  The routine must \fBnot\fR
declare its argument as a \fIregister\fR parameter, but \fBmust\fR declare
.DS
register int br, cvec;
.DE
as local variables.  At boot time the system takes special measures
that these variables are ``value-result'' parameters.  The \fIbr\fR
is the IPL of the device when it interrupts, and the \fIcvec\fR
is the interrupt vector address on the UNIBUS.  These registers
are actually filled in in the interrupt handler when an interrupt occurs.
.IP
As an example, here is the \fIup.c\fR
probe routine:
.DS
upprobe(reg)
        caddr_t reg;
{
        register int br, cvec;

#ifdef lint     
D 3
        br = 0; cvec = br; br = cvec;
E 3
I 3
        br = 0; cvec = br; br = cvec; upintr(0);
E 3
#endif
        ((struct updevice *)reg)->upcs1 = UP_IE|UP_RDY;
        DELAY(10);
        ((struct updevice *)reg)->upcs1 = 0;
        return (sizeof (struct updevice));
}
.DE
The definitions for \fIlint\fR serve to indicate to it that the
D 3
\fIbr\fR and \fIcvec\fR variables are value-result.  The statements
here interrupt enable the device and write the ready bit UP_RDY.
E 3
I 3
\fIbr\fR and \fIcvec\fR variables are value-result.
The call to the interrupt routine satisfies lint that the interrupt
handler is used.
The cod here enable interrupts on the device and write the ready bit UP_RDY.
E 3
The 10 microsecond delay insures that the interrupt enable will
not be canceled before the interrupt can be posted.  The return of
``sizeof (struct updevice)'' here indicates that the probe routine
is satisfied that the device is present (the value returned is not
D 3
currently used, but future plans dictate you should return the amount
E 3
I 3
currently used, but future plans dictate that you should return the amount
E 3
of space in the device's register bank).  A probe routine may use
the function ``badaddr'' to see
if certain other addresses are accessible on the UNIBUS (without generating
a machine check), or look at the contents of locations where certain
registers should be.  If the registers contents are not acceptable or
the addresses don't respond, the probe routine can return 0 and the
device will not be considered to be there.
.IP
One other thing to note is that the action of different VAXen when illegal
addresses are accessed on the UNIBUS may differ.  Some of the machines
may generate machine checks and some may cause UNIBUS errors.  Such
considerations are handled by the configuration program and the driver
writer need not be concerned with them.
.IP
It is also possible to write a very simple probe routine for a one-of-a-kind
device if probing is difficult or impossible.  Such a routine would include
statements of the form:
.DS
br = 0x15;
cvec = 0200;
.DE
for instance, to declare that the device ran at UNIBUS br5 and interrupted
D 3
through vector 0200 on the UNIBUS.  The current UDA-50 driver does 
something similar to this because the device is so difficult to force
an interrupt on that it hardly seems worthwhile.
E 3
I 3
through vector 0200 on the UNIBUS.
E 3
.IP \fBud_slave\fP
This routine is called with a \fIuba_device\fR structure (yet to
be described) and the address of the device controller.  It should
determine whether a particular slave device of a controller is
present, returning 1 if it is and 0 if it is not.
As an example here is the slave routine for \fIup.c\fR.
.DS
upslave(ui, reg)
        struct uba_device *ui;
        caddr_t reg;
{
        register struct updevice *upaddr = (struct updevice *)reg;

        upaddr->upcs1 = 0;              /* conservative */
        upaddr->upcs2 = ui->ui_slave;
D 3
        if (upaddr->upcs2&UPCS2_NED) {
                upaddr->upcs1 = UP_DCLR|UP_GO;
E 3
I 3
        if (upaddr->upcs2 & UPCS2_NED) {
                upaddr->upcs1 = UP_DCLR | UP_GO;
E 3
                return (0);
        }
        return (1);
}
.DE
Here the code fetches the slave (disk unit) number from the \fIui_slave\fR
field of the \fIuba_device\fR structure, and sees if the controller
D 3
responds that that is a non-existent driver (NED).  If the drive
E 3
I 3
responds that that is a non-existent driver (NED).  If the drive is not present,
E 3
a drive clear is issued to clean the state of the controller, and 0 is
returned indicating that the slave is not there.  Otherwise a 1 is returned.
.IP \fBud_attach\fP
The attach routine is called after the autoconfigure code and the driver concur
that a peripheral exists attached to a controller.  This is the routine
where internal driver state about the peripheral can be initialized.
Here is the \fIattach\fR routine from the \fIup.c\fR driver:
.DS
.DT
upattach(ui)
        register struct uba_device *ui;
{
        register struct updevice *upaddr;

        if (upwstart == 0) {
                timeout(upwatch, (caddr_t)0, hz);
                upwstart++;
        }
        if (ui->ui_dk >= 0)
                dk_mspw[ui->ui_dk] = .0000020345;
        upip[ui->ui_ctlr][ui->ui_slave] = ui;
        up_softc[ui->ui_ctlr].sc_ndrive++;
	ui->ui_type = upmaptype(ui);
}
.DE
The attach routine here performs a number of functions.  The first
time any drive is attached to the controller it starts the timeout
routine which watches the disk drives to make sure that interrupts
aren't lost.  It also initializes, for devices which have been assigned
\fIiostat\fR numbers (when ui->ui_dk >= 0), the transfer rate of the
device in the array \fIdk_mspw\fR, the fraction of a second it takes
to transfer 16 bit word.  It then initializes an inverting pointer
in the array \fIupip\fR which will be used later to determine, for a
particular \fIup\fR controller and slave number, the corresponding
\fIuba_device\fR.  It increments the count of the number of devices
on this controller, so that search commands can later be avoided
if the count is exactly 1.  It then attempts to decipher the actual
type of drive attached to the controller in a controller-specific
way.  On the EMULEX SC-21 it may ask for the number of tracks on
the device and use this to decide what the drive type is.  The drive
type is used to setup disk partition mapping tables and other
device specific information.
.IP \fBud_dgo\fP
.br
D 3
Is the routine which is called by the UNIBUS resource management
E 3
I 3
This is the routine which is called by the UNIBUS resource management
E 3
routines when an operation is ready to be started (because the required
resources have been allocated).  The routine in \fIup.c\fR is:
.DS
updgo(um)
        struct uba_ctlr *um;
{
        register struct updevice *upaddr = (struct updevice *)um->um_addr;

        upaddr->upba = um->um_ubinfo;
        upaddr->upcs1 = um->um_cmd|((um->um_ubinfo>>8)&0x300);
}
.DE
This routine uses the field \fIum_ubinfo\fR of the \fIuba_ctlr\fR
structure which is where the UNIBUS routines store the UNIBUS
D 3
map allocation information.  In particluar, the low 18 bits of this
E 3
I 3
map allocation information.  In particular, the low 18 bits of this
E 3
word give the UNIBUS address assigned to the transfer.  The assignment
to \fIupba\fR in the go routine places the low 16 bits of the UNIBUS
address in the disk UNIBUS address register.  The next assignment
places the disk operation command and the extended (high 2) address
D 3
bits in the device control-status register, starting the i/o operation.
E 3
I 3
bits in the device control-status register, starting the I/O operation.
E 3
The field \fIum_cmd\fR was initialized with the command to be stuffed
here in the driver code itself before the call to the \fIubago\fR
routine which eventually resulted in the call to \fIupdgo\fR.
.IP \fBud_addr\fP
D 3
Are the conventional addresses for the device control registers in
UNIBUS space.  This information is used by the system
E 3
I 3
This is a zero-terminated list of the conventional addresses
for the device control registers in UNIBUS space.
This information is used by the system
E 3
to look for instances of the device supported by the driver.
When the system probes for the device it first checks for a
control-status register located at the address indicated in
the configuration file (if supplied), then uses the list of
conventional addresses pointed to be \fIud_addr\fP.
.IP \fBud_dname\fP
D 3
Is the name of a \fIdevice\fR supported by this controller; thus the
E 3
I 3
This is the name of a \fIdevice\fR supported by this controller; thus the
E 3
disks on a SC-21 controller are called \fIup0\fR, \fIup1\fR, etc.
That is because this field contains \fIup\fR.
.IP \fBud_dinfo\fP
D 3
Is an array of back pointers to the \fIuba_device\fR structures for
E 3
I 3
This is an array of back pointers to the \fIuba_device\fR structures for
E 3
each device attached to the controller.  Each driver defines a set of
controllers and a set of devices.  The device address space is always
one-dimensional, so that the presence of extra controllers may be
masked away (e.g. by pattern matching) to take advantage of hardware
redundancy.  This field is filled in by the configuration program,
and used by the driver.
.IP \fBud_mname\fP
The name of a controller, e.g. \fIsc\fR for the \fIup.c\fR driver.
The first SC-21 is called \fIsc0\fR, etc.
.IP \fBud_minfo\fP
The backpointer array to the structures for the controllers.
.IP \fBud_xclu\fP
If non-zero specifies that the controller requires exclusive
use of the UNIBUS when it is running.  This is non-zero currently
only for the RK611 controller for the RK07 disks to map around a hardware
problem.  It could also be used if 6250bpi tape drives are to be used
on the UNIBUS to insure that they get the bandwidth that they need
(basically the whole bus).
I 3
.IP \fBud_ubamem\fP
This is an optional entry point to the driver to configure UNIBUS memory
associated with a device.
If this field in the driver structure is null, it is ignored.
Otherwise, it is called before beginning to probe for devices
when configuration of a UNIBUS is begun.
The driver must probe for the existence of its memory,
and is then responsible for allocating the map registers corresponding
to the device memory addresses so that the registers are not used for other
purposes.
The \fBud_ubamem\fP returns 0 on success and \-1 on failure.
A return value of 1 indicates that the memory exists, and that there
is no further configuration required for the device.
E 3
.SH
uba_ctlr structure
.PP
One of these structures exists per-controller.
The fields link the controller to its UNIBUS adapter and contain the
state information about the devices on the controller.  The fields are:
.IP \fBum_driver\fP
A pointer to the \fIstruct uba_device\fR for this driver, which has
fields as defined above.
.IP \fBum_ctlr\fP
The controller number for this controller, e.g. the 0 in \fIsc0\fR.
.IP \fBum_alive\fP
Set to 1 if the controller is considered alive; currently, always set
for any structure encountered during normal operation.  That is, the
driver will have a handle on a \fIuba_ctlr\fR structure only if the
configuration routines set this field to a 1 and entered it into the
driver tables.
.IP \fBum_intr\fP
The interrupt vector routines for this device.  These are generated
by \fIconfig\fP and this field is initialized in the
\fIioconf.c\fR file.
.IP \fBum_hd\fP
.br
A back-pointer to the UNIBUS adapter to which this controller is attached.
.IP \fBum_cmd\fP
A place for the driver to store the command which is to be given to
the device before calling the routine \fIubago\fR with the devices
\fIuba_device\fR structure.  This information is then retrieved when the
device go routine is called and stuffed in the device control status register
D 3
to start the i/o operation.
E 3
I 3
to start the I/O operation.
E 3
.IP \fBum_ubinfo\fP
Information about the UNIBUS resources allocated to the device.  This is
normally only used in device driver go routine (as \fIupdgo\fR above)
and occasionally in exceptional condition handling such as ECC correction.
.IP \fBum_tab\fP
This buffer structure is a place where the driver hangs the device structures
which are ready to transfer.  Each driver allocates a buf structure for each
device (e.g. \fIupdtab\fR in the \fIup.c\fR driver) for this purpose.
You can think of this structure as a device-control-block, and the
buf structures linked to it as the unit-control-blocks.
The code for dealing with this structure is stylized; see the \fIrk.c\fR
or \fIup.c\fR driver for the details.  If the \fIubago\fR routine
is to be used, the structure attached to this \fIbuf\fR structure
must be:
.RS
.IP \(bu 3
A chain of \fIbuf\fR structures for each waiting device on this controller.
.IP \(bu 3
On each waiting \fIbuf\fR structure another \fIbuf\fR structure which is
D 3
the one containing the parameters of the i/o operation.
E 3
I 3
the one containing the parameters of the I/O operation.
E 3
.RE
.SH
uba_device structure
.PP
One of these structures exist for each device attached to a UNIBUS
controller.  Devices which are not attached to controllers or which
perform no buffered data path
D 3
DMA i/o may have only a device structure.  Thus \fIdz\fR
E 3
I 3
DMA I/O may have only a device structure.  Thus \fIdz\fR
E 3
and \fIdh\fR devices have only \fIuba_device\fR structures.
The fields are:
.IP \fBui_driver\fP
A pointer to the \fIstruct uba_driver\fR structure for this device type.
.IP \fBui_unit\fP
The unit number of this device, e.g. 0 in \fBup0\fR, or 1 in \fBdh1\fR.
.IP \fBui_ctlr\fP
.br
The number of the controller on which this device is attached, or \-1
if this device is not on a controller.
.IP \fBui_ubanum\fP
The number of the UNIBUS on which this device is attached.
.IP \fBui_slave\fP
The slave number of this device on the controller which it is attached to,
or \-1 if the device is not a slave.  Thus a disk which was unit 2 on
a SC-21 would have \fIui_slave\fR 2; it might or might not be \fIup2\fR,
that depends on the system configuration specification.
.IP \fBui_intr\fP
.br
The interrupt vector entries for this device, copied into the UNIBUS
interrupt vector at boot time.  The values of these fields are filled
in by \fIconfig\fP to small code segments which it
generates in the file \fIubglue.s\fR.
.IP \fBui_addr\fP
The control-status register address of this device.
.IP \fBui_dk\fP
.br
The iostat number assigned to this device.  Numbers are assigned to
D 3
disks only, and are small positive integers which index the various
E 3
I 3
disks only, and are small nonnegative integers which index the various
E 3
\fIdk_*\fP arrays in <\fIsys/dk.h\fP>.
.IP \fBui_flags\fP
The optional ``flags \fIxxx\fP'' parameter from the configuration
specification was copied to this field, to be interpreted by the driver.
If \fIflags\fP was not specified, then this field will contain a 0.
.IP \fBui_alive\fP
The device is really there.  Presently set to 1 when a device is
determined to be alive, and left 1.
.IP \fBui_type\fP
The device type, to be used by the driver internally.
.IP \fBui_physaddr\fP
The physical memory address of the device control-status register.
D 3
This is used in the device dump routines typically.
E 3
I 3
This is typically used in the device dump routines.
E 3
.IP \fBui_mi\fP
.br
A \fIstruct uba_ctlr\fP pointer to the controller (if any) on which
this device resides.
.IP \fBui_hd\fP
.br
A \fIstruct uba_hd\fP pointer to the UNIBUS on which this device resides.
.SH
UNIBUS resource management routines
.PP
UNIBUS drivers are supported by a collection of utility routines
which manage UNIBUS resources.  If a driver attempts to bypass the
UNIBUS routines, other drivers may not operate properly.
The major routines are: \fIuballoc\fP to allocate UNIBUS resources,
\fIubarelse\fP to release previously allocated resources, and
\fIubago\fP to initiate DMA.  When allocating UNIBUS resources
you may request that you
.IP NEEDBDP
if you need a buffered data path,
.IP HAVEBDP
if you already have a buffered data path and just want new
D 3
mapping registers (and access to the UNIBUS), and
E 3
I 3
mapping registers (and access to the UNIBUS),
E 3
.IP CANTWAIT
D 3
if you are calling (potentially) from interrupt level
E 3
I 3
if you are calling (potentially) from interrupt level, and
.IP NEED16
if the device uses only 16 address bits, and thus requires
map registers from the first 64K of UNIBUS address space.
E 3
.LP
If the presentation here does not answer all the questions
you may have, consult the file /sys/vaxuba/uba.c
.SH
Autoconfiguration requirements
.PP
Basically all you have to do is write a \fIud_probe\fP and a \fIud_attach\fP
routine for the controller.  It suffices to have a \fIud_probe\fP routine
which just initializes \fIbr\fP and \fIcvec\fP, and a \fIud_attach\fP
routine which does nothing.
Making the device fully configurable requires, of course, more work,
but is worth it if you expect the device to be in common usage
and want to share it with others.
.PP
If you managed to create all the needed hooks, then make sure you include
the necessary header files; the ones included by \fIvaxuba/ct.c\fP are nearly
minimal.  Order is important here, don't be surprised at undefined structure
D 3
complaints if you order the includes wrongly.
Finally if you get the device configured in, you can try bootstrapping
E 3
I 3
complaints if you order the includes incorrectly.
Finally, if you get the device configured in, you can try bootstrapping
E 3
and see if configuration messages print out about your device.
It is a good idea to have some messages in the probe routine so that
D 3
you can see that you are getting called and what is going on.
If you do not get called, then you probably have the control-status
register address wrong in your system configuration.  The autoconfigure
code notices that the device doesn't exist in this case and you will never
get called.
E 3
I 3
you can see that it is being called and what is going on.
If it is not called, then you probably have the control-status
register address wrong in the system configuration.  The autoconfigure
code notices that the device doesn't exist in this case,
and the probe will never be called.
E 3
.PP
Assuming that your probe routine works and you manage
to generate an interrupt, then you are basically back to where you
would have been under older versions of UNIX.
Just be sure to use the \fIui_ctlr\fP field of the \fIuba_device\fP
structures to address the device; compiling in funny constants
will make your driver only work on the CPU type you have (780, 750, or 730).
.PP
Other bad things that might happen while you are setting up the configuration
stuff:
.IP \(bu 3
You get ``nexus zero vector'' errors from the system.  This will happen
if you cause a device to interrupt, but take away the interrupt enable
so fast that the UNIBUS adapter cancels the interrupt and confuses
the processor.  The best thing to do it to put a modest delay in the
probe code between the instructions which should cause and interrupt and
the clearing of the interrupt enable.  (You should clear interrupt
enable before you leave the probe routine so the device doesn't interrupt
more and confuse the system while it is configuring other devices.)
.IP \(bu 3
The device refuses to interrupt or interrupts with a ``zero vector''.
This typically indicates a problem with the hardware or, for devices
which emulate other devices, that the emulation is incomplete.  Devices
may fail to present interrupt vectors because they have configuration
switches set wrong, or because they are being accessed in inappropriate ways.
Incomplete emulation can cause ``maintenance mode'' features to not work
properly, and these features are often needed to force device interrupts.
E 5
I 5
and Operating 4.4BSD''.
E 5
D 3
.NH 2
Adding non-standard system facilities
.PP
This section considers the work needed to augment 
.IR config 's
data base files for non-standard system facilities.
.PP
As far as
.I config
is concerned
non-standard facilities may fall into two categories.
.I Config
understands that certain files are used especially for
kernel profiling.  These files are indicated in the
.I files
files with a 
.I profiling-routine
keyword.  For example, the current profiling subroutines
are sequestered off in a separate file with the following
entry:
.IP
.nf
.DT
\fIsys/subr_mcount.c\fP	\fBoptional\fP \fBprofiling-routine\fP
.fi
.LP
The 
.I profiling-routine
keyword forces
.I config
to not compile the source file with the 
.B \-pg
option.
.PP
The second keyword which can be of use is the
.I config-dependent
keyword.  This causes
.I config
to compile the indicated module with the global configuration
parameters.  This allows certain modules, such as
.I machdep.c
to size system data structures based on the maximum number
of users configured for the system.
E 3
E 1
