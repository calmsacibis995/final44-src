h39785
s 00007/00001/00125
d D 5.1 91/04/16 17:49:34 bostic 4 3
c new copyright; att/bsd/shared
e
s 00006/00007/00120
d D 1.3 86/12/04 15:44:51 mckusick 3 2
c edits from Mark Compton
e
s 00002/00002/00125
d D 1.2 86/11/29 09:22:45 mckusick 2 1
c first draft edits
e
s 00127/00000/00000
d D 1.1 86/11/25 23:22:41 mckusick 1 0
c date and time created 86/11/25 23:22:41 by mckusick
e
u
U
t
T
I 1
D 4
.\"	%W%	(Copyright 1986 M. K. McKusick)	%E%
E 4
I 4
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 4
D 2
.SH
E 2
I 2
.NH
E 2
The Role of Research in Maintaining System Vitality
.PP
D 3
Since the AT&T divestiture, UNIX has become the focus of
E 3
I 3
Since the divestiture of AT&T, UNIX has become the focus of
E 3
a massive marketing effort.
To succeed, this effort must convince
potential customers that the product is supported,
that future versions will continue to be developed,
and that these versions will be upwardly
compatible with all past applications.
.PP
AT&T's size alone ensures that it will be around in years to come.
D 3
The fact that the company has allocated a growing number of
research, development,
E 3
I 3
Because the company has allocated increasing research, development,
E 3
and support resources to UNIX over the past 10 years
D 3
provides an assurance of its commitment.
E 3
I 3
it provides an assurance of its commitment.
E 3
Its massive advertising campaign for System V, 
its presence on the /usr/group UNIX standards committee,
and the publication of the \fISystem V Interface Definition\fR
testify to the company's intention
to remain compatible with past systems.
.PP
Although repeal of the law of entropy is a necessary step
along the road to a
viable commercial product, this runs counter to
orderly system evolution.
Be that as it may, AT&T's major UNIX
commercialization effort has succeeded in making the system
available to a much broader audience than was previously possible.
.PP
The freezing of what previously had been
an ever-changing UNIX interface
represented a major departure from the pattern that the
small but highly skilled UNIX community had come to expect.
Most early users had accounts
at sites that had the source to the programs they ran.
Thus, as the system interface evolved to reflect more current technology,
software could be changed to keep pace.
Users simply updated their programs
to account for the new interface, 
recompiled them, and continued to use them as before.
Although this required a large effort,
it allowed the system --
and the tools that ran on it -- to reflect
changes in software technology.
.PP
At the forefront of the technological wave
was AT&T's own Bell Laboratories [Ritchie74].
It was there that the UNIX system was born and nurtured,
and it was there that its evolution was controlled --
up through the release
of the 7th Edition.
Universities also were involved with the
system almost from its inception.
The University of California at
D 3
Berkeley was one of the first participants,
E 3
I 3
Berkeley was among the first participants,
E 3
playing host to several researchers on sabbatical from the Labs.
This cooperation typified the harmony
that was characteristic of the early UNIX community.
Work that was contributed to the Labs by
different members of the community helped
produce a rapidly expanding set of tools and facilities.
.PP
With the release of the 7th Edition, though,
the usefulness of UNIX already had been
clearly established, and other organizations within AT&T began
to handle the public releases of the system. 
These groups took far less input from the community
as they began to freeze the system interface
in preparation for entry into the commercial marketplace.
.PP
As the research community continued to modify the UNIX system,
it found that it needed an organization that could produce releases.
Berkeley quickly stepped into the role.
D 3
Prior to the final public release of UNIX from the Labs, 
E 3
I 3
Before the final public release of UNIX from the Labs, 
E 3
Berkeley's work had been focused on the development of
tools designed to be added to
existing UNIX systems.
After the AT&T freeze, though,
a group of researchers at
the university found that they could easily
expand their role to include the coalescing function
previously provided by the Labs.
Out of this came the first full Berkeley distribution of UNIX
(3.0BSD),
complete with virtual memory --
a first for UNIX users.
The idea was so successful that System V eventually adopted it
six years later.
D 2
.SH 2
E 2
I 2
.NH 2
E 2
Motivations for Change
.PP
At the same time that AT&T was beginning
to put the brakes on further
change in UNIX, local area networks and bitmapped workstations
were just beginning to emerge from
Xerox PARC and other research centers.
Users in the academic and research community realized
that there were no production-quality operating systems
D 3
capable of making use of such hardware.
E 3
I 3
capable of using such hardware.
E 3
They also saw that networking unquestionably would be
an indispensable facility in future systems research.
Though it was not clear that UNIX
was the correct base on which to build a networked system,
it was clear that UNIX offered the most expedient means by which
to build such a system.
.PP
This posed the Berkeley group with an interesting challenge:
how to meet the needs of the community of users
without adding needless complexity to existing applications.
Their efforts were aided by the presence of a large and diverse
local group of users who were teaching introductory programming,
typesetting documents, developing software systems, and
trying to build huge Lisp-based systems capable
of solving differential equations.
In addition, they were able to discuss current problems
and hash out potential solutions at semi-annual
technical conferences run by the Usenix organization.
.PP
The assistance of a steering committee composed of academics,
commercial vendors, DARPA researchers, and people from the Labs
made it possible for
the architecture of a networking-based UNIX system to be developed.
By keeping with the UNIX tradition of integrating work done by
others in preference to writing everything from scratch,
4.2BSD was released less than two years later [Joy83].
E 1
