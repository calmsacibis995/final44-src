h31179
s 00007/00001/00113
d D 5.1 91/04/17 09:26:51 bostic 8 7
c new copyright; att/bsd/shared
e
s 00005/00002/00109
d D 1.7 89/02/24 17:35:17 karels 7 6
c minor changes
e
s 00014/00012/00097
d D 1.6 89/02/23 23:51:50 mckusick 6 5
c comments from John Quarterman
e
s 00001/00001/00108
d D 1.5 89/02/23 23:33:07 mckusick 5 4
c comments from Linda Branigan
e
s 00005/00005/00104
d D 1.4 89/02/23 23:27:09 mckusick 4 3
c editing pass after Keith
e
s 00045/00054/00064
d D 1.3 89/02/23 23:07:50 bostic 3 2
c minor editing
e
s 00042/00005/00076
d D 1.2 89/02/19 15:56:05 mckusick 2 1
c first pass at editing
e
s 00081/00000/00000
d D 1.1 89/02/18 19:24:03 mckusick 1 0
c date and time created 89/02/18 19:24:03 by mckusick
e
u
U
t
T
I 1
D 8
.\"	%W%	(Copyright 1989 M. K. McKusick)	%E%
E 8
I 8
.\" Copyright (c) 1989 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 8
.NH
System Development
.PP
The first phase of each Berkeley system is its development.
D 2
We maintain a continuously evolving list of projects that we would
E 2
I 2
.SM CSRG
D 3
maintains a continuously evolving list of projects that they would
E 2
like to see integrated into the system.
Some additions are prompted by emerging ideas from the
D 2
research world such as the availability of new technology.
E 2
I 2
research world, such as the availability of new technology.
E 2
A typical project would be to incorporate support for the
D 2
new technology into \*(b3.
E 2
I 2
new technology into
.SM BSD .
E 2
Other additions are suggested from the commercial world such
as the introduction of new standards like
.SM POSIX .
The resulting project would be to make the
.SM BSD
system compliant with the standard.
E 3
I 3
maintains a continuously evolving list of projects that are candidates
for integration into the system.
Some of these are prompted by emerging ideas from the research world,
such as the availability of a new technology, while other additions
are suggested by the commercial world, such as the introduction of
new standards like
.SM POSIX ,
and still other projects are emergency responses to situations like
the Internet Worm.
E 3
.PP
D 3
The projects are listed in order of importance.
Those at the top of the list are selected for inclusion
in the next release.
For each project, a determination is made of the best way to
get it done.
Usually there is at least a prototype available from
some group outside
E 3
I 3
These projects are ordered based on the perceived benefit of the
D 4
project as opposed to its difficulty, and some number of them are
selected for inclusion in each new release.
Usually there is a prototype available from a group outside of
E 4
I 4
project as opposed to its difficulty;
the most important are selected for inclusion in each new release.
D 7
Usually there is a prototype available from a group outside
E 7
I 7
Often there is a prototype available from a group outside
E 7
E 4
E 3
.SM CSRG .
D 3
If possible, the prototype is obtained to use as a starting base
E 3
I 3
D 6
If possible, this prototype is obtained to use as a starting base
E 6
I 6
Because of the limited staff at
.SM CSRG ,
this prototype is obtained to use as a starting base
E 6
E 3
for integration into the
.SM BSD
system.
D 3
Only if the code is unavailable and if the project is
not too large is it developed in-house.
E 3
I 3
D 7
Only if no prototype is available is the project architected in-house.
E 7
I 7
Only if no prototype is available is the project begun in-house.
In either case, the design of the facility is forced to conform to the
.SM CSRG
style.
E 7
E 3
.PP
D 3
Unlike larger development groups, the staff of
E 3
I 3
Unlike other development groups, the staff of
E 3
.SM CSRG
D 3
specializes by projects rather than by particular levels
E 3
I 3
specializes by projects rather than by particular parts
E 3
D 2
of the system.
Thus, a staff person will be responsible for all aspects of a project.
E 2
I 2
of the system;
a staff person will be responsible for all aspects of a project.
E 2
This responsibility starts at the associated kernel device drivers;
D 3
it proceeds up through the top of the kernel,
E 3
I 3
it proceeds up through the rest of the kernel,
E 3
through the C library and system utility programs,
D 3
ending at the programs that the user interacts with directly.
Each staff person is also responsible for the documentation and manual pages.
Projects proceed in parallel,
E 3
I 3
ending at the user application layer.
This staff person is also responsible for related documentation,
including manual pages.
Many projects proceed in parallel,
E 3
interacting with other projects as their paths cross.
I 2
.PP
I 6
All source code, documentation, and auxiliary files are kept
under a source code control system.
During development,
this control system is critical for notifying people
when they are colliding with other ongoing projects.
Even more important, however,
is the audit trail maintained by the control system that
is critical to the release engineering phase of the project
described in the next section.
.PP
E 6
Much of the development of
.SM BSD
is done by personnel that are located at other institutions.
D 3
Many of these people not only have copies of the release
E 3
I 3
Many of these people not only have interim copies of the release
E 3
running on their own machines,
D 3
but also have login accounts on the development
E 3
I 3
but also have user accounts on the main development
E 3
machine at Berkeley.
Such users are commonly found logged in at Berkeley over the
D 3
.SM ARPA
Internet, or sometimes via telephone dialup, from places far away,
such as Massachusetts, Utah, Maryland, Texas,
and Illinois, and from closer places, such as
E 3
I 3
Internet, or sometimes via telephone dialup, from places as far away
as Massachusetts or Maryland, as well as from closer places, such as
E 3
Stanford.
For the \*(b3 release,
D 3
certain accounts and users had permission to modify the master copy of the
E 3
I 3
certain users had permission to modify the master copy of the
E 3
system source directly.
People given access to the master sources
are carefully screened beforehand,
but are not closely supervised.
Their work is checked at the end of the beta-test period by
.SM CSRG
personnel who back out inappropriate changes.
D 3
Several facilities, such as the
E 3
I 3
Several facilities, including the
E 3
Fortran and C compilers,
D 3
as well as important system programs, such as
.NM telnet
E 3
I 3
as well as important system programs, for example,
.PN telnet
E 3
and
D 3
.NM ftp ,
include significant contributions from people who did not work for
E 3
I 3
.PN ftp ,
include significant contributions from people who did not work
directly for
E 3
.SM CSRG .
One important exception to this approach is that changes to the kernel
D 3
are made by only
E 3
I 3
are made only by
E 3
.SM CSRG
D 3
personnel, although the changes often are suggested by the larger community.
E 3
I 3
personnel, although the changes are often suggested by the larger community.
E 3
E 2
.PP
D 6
All source code, documentation, and auxiliary files are kept
under a source code control system.
During development,
D 3
the source code control system is critical to notifying people
when they are colliding with other changes.
Even more important however,
is the audit trail maintained by the source code control system that
E 3
I 3
this control system is critical for notifying people
when they are colliding with other ongoing projects.
Even more important, however,
D 4
is the audit trail maintained by the control system which
E 4
I 4
is the audit trail maintained by the control system that
E 4
E 3
is critical to the release engineering phase of the project
described in the next section.
.PP
E 6
D 3
As projects reach completion, new projects are started.
E 3
The development phase continues until
.SM CSRG
decides that it is appropriate to make a release.
D 3
The decision to halt development and switch to release mode
E 3
I 3
The decision to halt development and transition to release mode
E 3
is driven by several factors.
D 3
The most important is that enough projects have been completed
to make the system decidedly superior to the previously released
E 3
I 3
D 4
The most important is that sufficient projects have been completed
E 4
I 4
The most important is that enough projects have been completed
E 4
to make the system significantly superior to the previously released
E 3
version of the system.
For example,
\*(b3 was released primarily because of the need for
the improved networking capabilities and the markedly
improved system performance.
D 3
Secondly is the issue of timing.
E 3
I 3
Of secondary importance is the issue of timing.
E 3
If the releases are too infrequent, then
.SM CSRG
D 3
gets inundated with requests for interim releases.
E 3
I 3
will be inundated with requests for interim releases.
E 3
Conversely,
if systems are released too frequently,
the integration cost for many vendors will be too high,
D 3
and they will tend to ignore the releases.
E 3
I 3
causing them to ignore the releases.
E 3
Finally,
the process of release engineering is long and tedious.
D 5
Frequent releases slows the rate of development and
E 5
I 5
Frequent releases slow the rate of development and
E 5
D 6
causes undue tedium to the staff.
E 6
I 6
cause undue tedium to the staff.
E 6
E 1
