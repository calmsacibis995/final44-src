h31932
s 00007/00001/00357
d D 5.1 91/04/17 09:26:52 bostic 8 7
c new copyright; att/bsd/shared
e
s 00016/00013/00342
d D 1.7 89/02/24 17:35:18 karels 7 6
c minor changes
e
s 00011/00007/00344
d D 1.6 89/02/23 23:51:51 mckusick 6 5
c comments from John Quarterman
e
s 00005/00005/00346
d D 1.5 89/02/23 23:33:09 mckusick 5 4
c comments from Linda Branigan
e
s 00013/00013/00338
d D 1.4 89/02/23 23:27:11 mckusick 4 3
c editing pass after Keith
e
s 00090/00086/00261
d D 1.3 89/02/23 23:07:52 bostic 3 2
c minor editing
e
s 00082/00036/00265
d D 1.2 89/02/19 15:56:07 mckusick 2 1
c first pass at editing
e
s 00301/00000/00000
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
System Release
.PP
D 3
Once the decision has been made to finish development
E 3
I 3
Once the decision has been made to halt development
E 3
and begin release engineering,
D 3
the currently unfinished projects are evaluated.
The evaluation involves figuring how much time the project
will require to complete,
and how important the outcome of the project is to
the upcoming release.
Projects that are not selected for completion are mothballed
so that they can be restarted in the future.
The remaining unfinished projects are
brought to an orderly completion.
E 3
I 3
all currently unfinished projects are evaluated.
This evaluation involves computing the time required to complete
the project as opposed to how important the project is to the
upcoming release.
D 6
Projects that are not selected for completion are ``snap-shotted''
and backed-out for completion in a future release; the remaining
unfinished projects are brought to orderly completion.
E 6
I 6
Projects that are not selected for completion are
removed from the distribution branch of the source code control system
and saved on branch deltas so they can be retrieved,
completed, and merged into a future release;
the remaining unfinished projects are brought to orderly completion.
E 6
E 3
I 2
.PP
Developments from
.SM CSRG
are released in three steps: alpha, beta, and final.
Alpha and beta releases are not true distributions\(emthey
are test systems.
Alpha releases are normally available to only a few sites,
D 3
mostly those that are working directly with
E 3
I 3
usually those working closely with
E 3
.SM CSRG .
D 3
More sites get beta releases,
E 3
I 3
D 4
A much larger number of sites are given beta releases,
E 4
I 4
More sites are given beta releases,
E 4
E 3
as the system is closer to completion,
D 3
so needs wider testing to find more obscure problems.
For example,
\*(b3 beta ran at more than 100 sites, but there were only about
15 alpha sites.
E 3
I 3
and needs wider testing to find more obscure problems.
D 4
For example, \*(b3 alpha was distributed to approximately fifteen
E 4
I 4
For example, \*(b3 alpha was distributed to about fifteen
E 4
sites, while \*(b3 beta ran at more than a hundred.
E 3
E 2
.NH 2
D 5
The Alpha Distribution
E 5
I 5
Alpha Distribution Development
E 5
.PP
D 3
The first step is to evaluate the existing state of the system
and to initially decide which software should be included in the release.
The decision process includes not only deciding what needs to be
added, but also what older software should be retired from the
E 3
I 3
The first step in creating an alpha distribution is to evaluate the
existing state of the system and to decide what software should be
included in the release.
This decision process includes not only deciding what software should
be added, but also what obsolete software ought to be retired from the
E 3
distribution.
The new software includes the successful projects that have been
completed at
.SM CSRG
D 3
as well as an evaluation of the vast quantity of contributed
software that has been offered during the development period.
E 3
I 3
and elsewhere, as well as some portion of the vast quantity of
contributed software that has been offered during the development
period.
E 3
.PP
D 3
Once an initial list has been defined,
E 3
I 3
Once an initial list has been created,
E 3
a prototype filesystem corresponding to the distribution
D 3
is constructed, typically called
E 3
I 3
is constructed, typically named
E 3
.PN /nbsd .
D 3
This prototype will eventually turn into the master for the
E 3
I 3
This prototype will eventually turn into the master source tree for the
E 3
final distribution.
During the period that the alpha distribution is being created,
.PN /nbsd
D 2
is mounted read/write, and is highly fluid.
E 2
I 2
is mounted read-write, and is highly fluid.
E 2
Programs are created and deleted,
D 3
new versions are dropped in,
E 3
I 3
old versions of programs are completely replaced,
E 3
and the correspondence between the sources and binaries
is only loosely tracked.
People outside
.SM CSRG
D 6
that are helping with the distribution are free to
E 6
I 6
who are helping with the distribution are free to
E 6
D 3
change their related parts of the distribution.
E 3
I 3
change their parts of the distribution at will.
E 3
.PP
During this period the newly forming distribution is
checked for interoperability.
For example,
in \*(b3 the output of context differences from
.PN diff
was changed to merge overlapping sections.
Unfortunately, this change broke the
.PN patch
D 3
program that could no longer interpret the new diff output.
Since both changes had originated outside Berkeley,
E 3
I 3
program which could no longer interpret the output of
.PN diff .
Since the change to
.PN diff
and the
.PN patch
program had originated outside Berkeley,
E 3
.SM CSRG
D 2
had to coordinate the authors of these two programs
to get them to work together harmoniously.
E 2
I 2
D 3
had to get the authors of these two programs
E 3
I 3
D 4
had to coordinate the efforts of the respective authors in order
E 4
I 4
had to coordinate the efforts of the respective authors
E 4
E 3
to make the programs work together harmoniously.
E 2
.PP
D 2
Once we are satisfied with the state of the sources,
E 2
I 2
D 3
Once the state of the sources has stabilized,
E 3
I 3
Once the sources have stabilized,
E 3
E 2
D 7
an attempt is made to build the entire source tree.
E 7
I 7
an attempt is made to compile the entire source tree.
E 7
D 3
Often this turns up errors because of changed header files,
E 3
I 3
D 4
Often this exposes errors due to changed header files,
E 4
I 4
Often this exposes errors caused by changed header files,
E 4
E 3
or use of obsoleted C library interfaces.
If the incompatibilities affect too many programs,
or require excessive amounts of change in the programs
that are affected,
D 3
the incompatibility is backed out, or a way to provide
backward compatibility is found.
E 3
I 3
D 7
the incompatibility is backed out or some backward
compatible interface is provided.
E 7
I 7
the incompatibility is backed out or some backward-compatible
interface is provided.
E 7
E 3
The incompatibilities that are found and left in are noted
in a list that is later incorporated into the release notes.
D 3
Thus, users moving to the new system can anticipate problems
E 3
I 3
Thus, users upgrading to the new system can anticipate problems
E 3
in their own software that will require change.
.PP
D 3
Once the source code completely compiles,
E 3
I 3
D 4
Once the source tree completely compiles,
E 4
I 4
Once the source tree compiles completely,
E 4
E 3
it is installed and becomes the running system that
.SM CSRG
D 3
uses on the main development machine.
E 3
I 3
uses on its main development machine.
E 3
Once in day-to-day use,
D 3
other interoperability problems become apparent,
E 3
I 3
D 4
other interoperability problems are made apparent
E 4
I 4
other interoperability problems become apparent
E 4
E 3
and are resolved.
D 3
When a complete system can be built
and the known problems are resolved,
an alpha distribution tape is made
E 3
I 3
When all known problems have been resolved, and the system has been
stable for some period of time, an alpha distribution tape is made
E 3
from the contents of
.PN /nbsd .
.PP
I 2
The alpha distribution is sent out to a small set of test sites.
D 3
These test sites are selected to have a
sophisticated user population that can not only find bugs,
but can also determine the cause and find a fix to the problem.
These sites are mostly composed of the groups
that are involved in contributing software to the distribution.
E 3
I 3
These test sites are selected as having a
sophisticated user population, not only capable of finding bugs,
but also of determining their cause and developing a fix for the problem.
These sites are usually composed of groups that are contributing
software to the distribution or groups that have a particular expertise
with some portion of the system.
E 3
.NH 2
D 5
The Beta Distribution
E 5
I 5
Beta Distribution Development
E 5
.PP
E 2
D 3
After the alpha tape is made,
the distribution filesystem is changed over to read-only.
E 3
I 3
D 4
After the alpha tape is created
E 4
I 4
After the alpha tape is created,
E 4
the distribution filesystem is mounted read-only.
E 3
Further changes are requested in a change log rather than
D 3
being made directly on the distribution itself.
The change requests are inspected and run by a
E 3
I 3
being made directly to the distribution.
The change requests are inspected and implemented by a
E 3
.SM CSRG
staff person, followed by a compilation of the affected
programs to ensure that they still build correctly.
D 2
Notably, once the alpha tape has been cut,
E 2
I 2
Once the alpha tape has been cut,
E 2
changes to the distribution are no longer made by people outside
.SM CSRG .
.PP
D 2
The alpha distribution is sent out to a select set of test sites.
These test sites are selected to have a
sophisticated user population that can not only find bugs,
but can also determine the cause and find a fix to the problem.
These sites are mostly composed of the groups
that are involved in contributing software to the distribution.
.NH 2
The Beta Distribution
.PP
E 2
D 3
As the alpha sites install and begin running the alpha tape,
E 3
I 3
As the alpha sites install and begin running the alpha distribution,
E 3
they monitor the problems that they encounter.
For minor bugs, they typically report back the bug along with
a suggested fix.
Since many of the alpha sites are selected from among the people
working closely with
.SM CSRG ,
they often have accounts on, and access to, the primary
.SM CSRG
development machine.
Thus, they are able to directly install the fix themselves,
D 2
and simply notify us when they have fixed the problem.
E 2
I 2
and simply notify
.SM CSRG
when they have fixed the problem.
E 2
After verifying the fix, the affected files are added to
the list to be updated on
.PN /nbsd .
.PP
D 2
The more important task of the beta sites is to test out the
E 2
I 2
The more important task of the alpha sites is to test out the
E 2
new facilities that have been added to the system.
D 3
The alpha sites often manage to find major design flaws
E 3
I 3
The alpha sites often find major design flaws
E 3
or operational shortcomings of the facilities.
When such problems are found,
the person in charge of that facility is responsible
for resolving the problem.
D 3
Often this requires rearchitecting and reimplementing
E 3
I 3
D 7
Occasionally this requires rearchitecting and reimplementing
E 7
I 7
Occasionally this requires redesigning and reimplementing
E 7
E 3
parts of the affected facility.
For example,
in 4.2\s-1BSD\s+1,
D 7
the alpha release of the networking did not have connection queueing.
This shortcoming prevented the networking from handling many
E 7
I 7
the alpha release of the networking system did not have connection queueing.
This shortcoming prevented the network from handling many
E 7
connections to a single server.
The result was that the networking interface had to be
D 2
rearchitected to allow connection queueing.
E 2
I 2
D 3
rearchitected to provide connection queueing.
E 3
I 3
redesigned to provide this functionality.
E 3
E 2
.PP
The alpha sites are also responsible for ferreting out interoperability
D 3
problems with the different utilities.
E 3
I 3
problems between different utilities.
E 3
D 2
The sites are selected with different types of user populations so
that the utilities will be exercised in ways that differ
E 2
I 2
The user populations of the test sites differ from the user population at
.SM CSRG ,
D 3
so the utilities are exercised in ways that differ
E 3
I 3
D 7
and as a result the utilities are exercised in ways that differ
E 7
I 7
and, as a result, the utilities are exercised in ways that differ
E 7
E 3
E 2
from the ways that they are used at
.SM CSRG .
These differences in usage patterns turn up problems that
D 3
do not show up in our initial test environment.
E 3
I 3
do not occur in our initial test environment.
E 3
.PP
The alpha sites frequently redistribute the alpha tape to several
D 7
of their own alpha sites.
E 7
I 7
of their own alpha sites that are particularly interested
in parts of the new system.
E 7
These additional sites are responsible for reporting
problems back to the site from which they received the distribution,
not to
.SM CSRG .
Often these redistribution sites are less sophisticated than the
direct alpha sites, so their reports need to be filtered
D 3
to avoid spurious and voluminous reports.
E 3
I 3
to avoid spurious, or site dependent, bug reports.
E 3
The direct alpha sites sift through the reports to find those that
are relevant, and usually verify the suggested fix if one is given,
or develop a fix if none is provided.
D 2
The tree structured testing process ensures that the small group
of people at
E 2
I 2
D 3
The tree structured testing process allows
E 3
I 3
This hierarchical testing process forces
E 3
bug reports, fixes, and new software
D 3
to be collected, evaluated, and checked for redundancies
by first-level sites before forwarding to
.SM CSRG .
The alpha-test tree allows the developers at
E 3
I 3
to be collected, evaluated, and checked for inaccuracies
by first-level sites before being forwarded to
.SM CSRG ,
allowing the developers at
E 3
E 2
.SM CSRG
D 2
are not swamped by an overwhelming influx of reports.
Instead, they can concentrate on tracking the changes being made
to the system to ensure as high a level of consistency as possible.
E 2
I 2
to concentrate on tracking the changes being made to the system
D 3
rather than sifting through details from every alpha-test site.
E 3
I 3
rather than sifting through information (often voluminous) from every
alpha-test site.
E 3
E 2
.PP
Once the major problems have been attended to,
the focus turns to getting the documentation synchronized
with the code that is being shipped.
The manual pages need to be checked to be sure that
D 3
they accurately reflect the changes to the programs that
E 3
I 3
they accurately reflect any changes to the programs that
E 3
they describe.
Usually the manual pages are kept up to date as
the program they describe evolves.
However, the supporting documents frequently do not get changed,
D 3
and must be editted to bring them up to date.
E 3
I 3
and must be edited to bring them up to date.
E 3
During this review, the need for other documents becomes evident.
D 3
For example,
during this phase of \*(b3 we decided that it would be desirable
E 3
I 3
For example, it was
during this phase of \*(b3 that it was decided
E 3
D 4
to have a tutorial document on how to use the socket
E 4
I 4
to add a tutorial document on how to use the socket
E 4
interprocess communication primitives.
.PP
D 3
A final task during this period is to contact the people that
E 3
I 3
Another task during this period is to contact the people that
E 3
have contributed complete software packages
(such as
.PN RCS
or
.PN MH )
D 2
in the past to see if they wish to
E 2
I 2
in previous releases to see if they wish to
E 2
make any revisions to their software.
D 6
For those that do,
E 6
I 6
For those who do,
E 6
the new software has to be obtained,
D 3
and checked out to verify that it compiles and runs
E 3
I 3
and tested to verify that it compiles and runs
E 3
correctly on the system to be released.
Again, this integration and testing can often be done by the
D 3
contributors themselves by logging into the master machine
across the network.
E 3
I 3
contributors themselves by logging directly into the master machine.
E 3
.PP
After the stream of bug reports has slowed down
to a reasonable level,
D 2
we begin a carefully review of all the changes to the
E 2
I 2
.SM CSRG
D 5
begins a carefully review of all the changes to the
E 5
I 5
begins a careful review of all the changes to the
E 5
E 2
system since the previous release.
The review is done by running a recursive
.PN diff
D 2
of the entire source tree.
E 2
I 2
of the entire source tree\(emhere, of
.PN /nbsd
with 4.2\s-1BSD\s+1.
E 2
All the changes are checked to ensure that they are reasonable,
and have been properly documented.
The process often turns up questionable changes.
When such a questionable change is found,
the source code control system log is examined to find
out who made the change and what their explanation was
for the change.
If the log does not resolve the problem,
D 3
the person responsible for the change is asked to explain
E 3
I 3
the person responsible for the change is asked for an explanation
E 3
D 4
what they were trying to accomplish.
E 4
I 4
of what they were trying to accomplish.
E 4
If the reason is not compelling,
the change is backed out.
I 2
Facilities deemed inappropriate in \*(b3 included new options to
the directory-listing command and a changed return value for the
.RN fseek
library routine;
the changes were removed from the source before final distribution.
E 2
Although this process is long and tedious,
D 2
it forces us to get a picture of the entire set of
changes to the system into out head.
E 2
I 2
D 3
it forces the developers to get a picture of the entire set of
E 3
I 3
D 7
it forces the developers to create a coherent picture of the entire set of
E 7
I 7
it forces the developers to obtain a coherent picture of the entire set of
E 7
E 3
changes to the system.
E 2
This exercise often turns up inconsistencies that would
otherwise never be found.
.PP
I 2
The outcome of the comparison results in
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
D 4
file by name and get a summary of that file's changes.
E 4
I 4
file by name and get a summary of the changes to that file.
E 4
.PP
E 2
Having completed the review of the entire system,
D 2
we begin the preparation of the beta distribution.
E 2
I 2
the preparation of the beta distribution is started.
E 2
Unlike the alpha distribution, where pieces of the system
may be unfinished and the documentation incomplete,
the beta distribution is put together as if it were
going to be the final distribution.
All known problems are fixed, and any remaining development
is completed.
Once the beta tape has been prepared,
no further changes are permitted to
.PN /nbsd
D 2
without careful review as spurious changes made after the system has been
.PN diff 'ed
E 2
I 2
without careful review,
as spurious changes made after the system has been
.PN diff ed
E 2
are unlikely to be caught.
.NH 2
D 5
The Final Distribution
E 5
I 5
Final Distribution Development
E 5
.PP
D 4
The beta distribution goes to a larger set of sites than the
E 4
I 4
The beta distribution goes to more sites than the
E 4
D 3
alpha distribution for two main reasons.
D 2
First, since it closer to the final release more sites are willing
E 2
I 2
First, since it closer to the final release, more sites are willing
E 3
I 3
alpha distribution for three main reasons.
First, as it is closer to the final release, more sites are willing
E 3
E 2
to run it in a production environment without fear of catastrophic failures.
D 3
Second, more commercial sites with
E 3
I 3
Second, more commercial sites delivering
E 3
D 7
.SM BSD
E 7
I 7
.SM BSD -\c
E 7
derived systems are interested in getting a preview of the
upcoming changes in preparation for merging them into their
own systems.
D 3
Because the beta tape has fewer problems,
it is beneficial to cast a wider net in the hopes of
E 3
I 3
Finally, because the beta tape has fewer problems,
D 4
it is beneficial to offer it to a larger number of systems in hopes of
E 4
I 4
it is beneficial to offer it to more sites in hopes of
E 4
E 3
finding as many of the remaining problems as possible.
Also, by handing the system out to less sophisticated sites,
issues that would be ignored by the users of the alpha sites
D 4
will be brought to our attention.
E 4
I 4
become apparent.
E 4
.PP
The anticipation is that the beta tape will not require
extensive changes to either the programs or the documentation.
Most of the work involves sifting through the reported bugs
to find those that are relevant and devising the minimal
reasonable set of changes to fix them.
After throughly testing the fix, it is listed in the update log for
.PN /nbsd .
D 6
One person's responsibility is to do the update of
E 6
I 6
One person at
.SM CSRG
is responsible for doing the update of
E 6
.PN /nbsd
D 6
and to ensure that everything affected by the change is rebuilt and tested.
E 6
I 6
and ensuring that everything affected by the change is rebuilt and tested.
E 6
Thus, a change to a C library routine requires that the entire
system be rebuilt.
.PP
D 5
During this period the documentation is all printed out and proofread.
E 5
I 5
D 7
During this period, the documentation is all printed out and proofread.
E 7
I 7
During this period, the documentation is all printed and proofread.
E 7
E 5
As minor changes are made to the manual pages and documentation,
the affected pages must be reprinted.
.PP
D 3
The final step in the release process is to preen the distribution tree
E 3
I 3
The final step in the release process is to check the distribution tree
E 3
to ensure that it is in a consistent state.
D 3
This preening includes checking that every file and directory
E 3
I 3
D 7
This includes verifying that every file and directory
E 7
I 7
This step includes verification that every file and directory
E 7
E 3
on the distribution has the proper owner, group, and modes.
All source files must be checked to be sure that they have
D 3
appropriate source code control system headers.
Any unwanted error or temporary files must be removed.
E 3
I 3
appropriate copyright notices and source code control system headers.
Any extraneous files must be removed.
E 3
D 2
Finally we have to ensure that the installed binaries correspond
E 2
I 2
Finally, the installed binaries must be checked to ensure that they correspond
E 2
exactly to the sources and libraries that are on the distribution.
.PP
D 2
This is a formidable task given that there are over 20,000 files on
E 2
I 2
This checking is a formidable task given that there are over 20,000 files on
E 2
a typical distribution.
Much of the checking can be done by a set of programs set to scan
over the distribution tree.
D 2
Unfortunately the exception list is long, and requires
E 2
I 2
Unfortunately, the exception list is long, and requires
E 2
D 3
hours of tedious hand checking.
E 3
I 3
D 7
hours of tedious hand checking; this has caused CSRG to develop even
E 7
I 7
hours of tedious hand checking; this has caused
.SM CSRG
to develop even
E 7
more comprehensive validation programs for use in our next release.
E 3
.PP
Once the final set of checks has been run,
the master tape can be made, and the official distribution started.
As for the staff of
.SM CSRG ,
we usually take a brief vacation before plunging back into
D 3
a new development phase, doing all the things that we have
been unable to change during the release engineering period.
E 3
I 3
a new development phase.
E 3
E 1
