h27551
s 00004/00003/00063
d D 6.2 91/04/16 17:42:07 bostic 3 2
c written by Bob Kridle and Kirk McKusick, add Berkeley copyright
e
s 00000/00000/00066
d D 6.1 86/04/20 15:50:42 mckusick 2 1
c 4.3BSD release document
e
s 00066/00000/00000
d D 5.1 86/04/20 15:26:01 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 3
I 3
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
E 3
.\"
.\"	%W% (Berkeley) %G%
.\"
.ds RH Motivation
.NH
Motivation
.PP
These benchmarks were performed for several reasons.
Foremost was our desire to obtain guideline to aid
in choosing one the most expensive components of any
VAX UNIX configuration, the disk storage system.
The range of choices in this area has increased dramatically
in the last year.
DEC has become, with the introduction of the UDA50/RA81 system,
cost competitive
in the area of disk storage for the first time.
Emulex's entry into the VAX 11/780 SBI controller
field, the SC780, represented a important choice for us to examine, given
our previous success with their VAX 11/750 SC750 controller and
their UNIBUS controllers.
The Fujitsu 2351A
Winchester disk drive represents the lowest cost-per-byte disk storage
known to us.
In addition, Fujitsu's reputation for reliability was appealing.
The many attractive aspects of these components justified a more
careful examination of their performance aspects under UNIX.
.PP
In addition to the direct motivation of developing an effective
choice of storage systems, we hoped to gain more insight into
VAX UNIX file system and I/O performance in general.
What generic characteristics of I/O subsystems are most
important?
How important is the location of the controller on the SBI/CMI versus
the UNIBUS?
Is extensive buffering in the controller essential or even important?
How much can be gained by putting more of the storage system
management and optimization function in the controller as
DEC does with the UDA50?
.PP
We also wanted to resolve particular speculation about the value of
storage system optimization by a controller in a UNIX
environment.
Is the access optimization as effective as that already provided
by the existing 4.2BSD UNIX device handlers for traditional disks?
VMS disk handlers do no seek optimization.
This gives the UDA50 controller an advantage over other controllers
under VMS which is not likely to be as important to UNIX.
Are there penalties associated with greater intelligence in the controller?
.PP
A third and last reason for evaluating this equipment is comparable
to the proverbial mountain climbers answer when asked why he climbs
a particular mountain,
``It was there.''
In our case the equipment
was there.
We were lucky enough to assemble all the desired disks and controllers
and get them installed on a temporarily idle VAX 11/780.
This got us started collecting data.
Although many of the tests were later rerun on a variety of other systems,
this initial test bed was essential for working out the testing bugs
and getting our feet wet.
.ds RH Equipment
.bp
E 1
