h11073
s 00007/00001/00036
d D 5.1 91/04/17 09:26:50 bostic 7 6
c new copyright; att/bsd/shared
e
s 00004/00004/00033
d D 1.6 89/02/24 17:35:15 karels 6 5
c minor changes
e
s 00005/00002/00032
d D 1.5 89/02/23 23:51:48 mckusick 5 4
c comments from John Quarterman
e
s 00001/00001/00033
d D 1.4 89/02/23 23:27:08 mckusick 4 3
c editing pass after Keith
e
s 00015/00016/00019
d D 1.3 89/02/23 23:07:48 bostic 3 2
c minor editing
e
s 00003/00076/00032
d D 1.2 89/02/19 15:56:03 mckusick 2 1
c first pass at editing
e
s 00108/00000/00000
d D 1.1 89/02/18 19:24:02 mckusick 1 0
c date and time created 89/02/18 19:24:02 by mckusick
e
u
U
t
T
I 1
D 7
.\"	%W%	(Copyright 1989 M. K. McKusick)	%E%
E 7
I 7
.\" Copyright (c) 1989 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 7
.NH
Introduction
.PP
D 3
.SM CSRG
E 3
I 3
D 6
The Computer Systems Research Group
.SM (CSRG)
E 6
I 6
The Computer Systems Research Group (\c
.SM CSRG )
E 6
E 3
has always been a small group of software developers.
D 3
This resource limitation requires careful software-engineering management.
Careful coordination is needed not only of
E 3
I 3
This resource limitation requires careful software-engineering management
as well as careful coordination of both
E 3
.SM CSRG
D 3
personnel, but also of members of the general community who
E 3
I 3
personnel and the members of the general community who
E 3
contribute to the development of the system.
.PP
D 3
Releases from Berkeley tend to alternate between
those that introduce major new facilities and those that introduce
bug fixes and efficiency improvements.
This alternation allows timely releases,
while providing for refinement and correction of the new facilities
and the elimination of performance problems produced by the new facilities.
The timely followup of releases that include new facilities
reflects the importance
E 3
I 3
Releases from Berkeley alternate between those that introduce
major new facilities and those that provide bug fixes and efficiency
improvements.
This alternation allows timely releases, while providing for refinement,
tuning, and correction of the new facilities.
The timely followup of ``cleanup'' releases reflects the importance
E 3
.SM CSRG
D 3
places on providing a reliable and robust system on which its
E 3
I 3
D 4
places on providing a reliable and robust system upon which its
E 4
I 4
places on providing a reliable and robust system on which its
E 4
E 3
user community can depend.
.PP
D 2
Developments from
.SM CSRG
are released in three steps: alpha, beta, and final.
Alpha and beta releases are not true distributions\(emthey
are test systems.
Alpha releases are normally available to only a few sites, most of those
within the University.
More sites get beta releases, but they do not get them directly;
a tree structure is imposed to allow bug reports, fixes, and new software
to be collected, evaluated, and checked for redundancies
by first-level sites before forwarding to
.SM CSRG .
For example,
\*(b3 beta ran at more than 100 sites, but there were only about
15 primary beta sites.
The beta-test tree allowed the developers at
.SM CSRG
to concentrate on actual development rather than sifting through details
from every beta-test site.
.PP
Many of the primary beta-test personnel not only had copies of the release
running on their own machines, but also had login accounts on the development
machine at Berkeley.
Such users were commonly found logged in at Berkeley over the
.SM ARPA
Internet, or sometimes via telephone dialup, from places far away,
such as Massachusetts, Utah, Maryland, Texas,
and Illinois, and from closer places, such as
Stanford.
For the \*(b3 release,
certain accounts and users had permission to modify the master copy of the
system source directly.
Several facilities, such as the
Fortran and C compilers,
as well as important system programs, such as
.NM telnet
and
.NM ftp ,
include significant contributions from people who did not work for
.SM CSRG .
One important exception to this approach was that changes to the kernel
were made by only
.SM CSRG
personnel, although the changes often were suggested by the larger community.
.PP
People given access to the master sources
were carefully screened beforehand, but were not
closely supervised.
Their work was checked at the end of the beta-test period by
.SM CSRG
personnel, who did a complete comparison of the source of the previous
release with the current master sources\(emfor example, of \*(b3
with 4.2\s-1BSD\s+1.
Facilities deemed inappropriate, such as new options to
the directory-listing command or a changed return value for the
.RN fseek
library routine, were removed from the source before final distribution.
.PP
E 2
I 2
D 3
The development of
E 2
.SM BSD
E 3
I 3
D 6
The development of the Berkeley Software Distribution
.SM (BSD)
E 6
I 6
The development of the Berkeley Software Distribution (\c
.SM BSD )
E 6
E 3
D 2
releases have usually included
a pair of documents detailing
changes to every user-level command
.[
Bug Fixes and Changes
.]
and to every kernel source file.
.[
Changes to the Kernel
.]
These documents are delivered with the final distribution.
A user can look up any command by name and see immediately
what has changed,
and a developer can similarly look up any kernel
file by name and get a summary of that file's changes.
.PP
This process illustrates an \fIadvantage\fP of having a few
E 2
I 2
illustrates an \fIadvantage\fP of having a few
E 2
principal developers:
D 3
The developers all know the whole system thoroughly enough
E 3
I 3
the developers all understand the entire system thoroughly enough
E 3
to be able to coordinate their own work with
that of other people to produce a coherent final system.
Companies with large development organizations find
this result difficult to duplicate.
D 5
This paper describes in more detail the process by which
D 2
the release engineering is managed.
E 2
I 2
the development effort is managed.
E 5
I 5
This paper describes the process by which
the development effort for \*(b3 was managed.
.[
design and implementation
.]
E 5
E 2
E 1
