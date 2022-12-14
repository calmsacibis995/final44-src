h32776
s 00045/00004/00011
d D 1.2 89/02/24 14:50:07 karels 2 1
c my additions, Sue's comments
e
s 00015/00000/00000
d D 1.1 89/02/23 18:46:49 mckusick 1 0
c date and time created 89/02/23 18:46:49 by mckusick
e
u
U
t
T
I 1
.\"     %W%     %E%
.LP
\fB\s+4C. Deliverables\fP\s-4
.PP
We are planning to implement prototypes for each of these
outlined areas of work over the period of this proposal.
D 2
We will do an informal release
to interested developers during the proposal period.
E 2
I 2
.LP
1.  We will do an informal (``alpha'') release of the system
to interested developers after the first quarter of the proposal period.
E 2
In particular, the informal release will be made available
to the group at Mt Xinu that is producing a commercially
D 2
supported MACH release.
After incorporating feedback and refinements from the testers,
E 2
I 2
supported MACH release, as well as to collaborators on the OSI networking
project.
The alpha release will include
.IP "   \(bu
a functioning OSI network and transport implementation
.IP "   \(bu
changes to the socket interface and structure to support new features
of the OSI protocols
.IP "   \(bu
major portions of the POSIX interface, including the process group and
job control model, the terminal interface, and signals
.LP
In addition, it is expected that a prototype of the standard filesystem
interface will be completed in time for the alpha release.
.LP
2.  After incorporating feedback and refinements from the testers,
E 2
another release will be made to interested parties
at the end of the proposal period.
I 2
This release will be a stable system that may be used by other researchers,
although it may be known as a ``beta'' or intermediate release.
It will include
.IP "   \(bu
a complete functioning OSI network protocol stack,
including all seven layers, FTAM, and all other applications
made available to Berkeley in time for release
.IP "   \(bu
the final socket interface to support new features
of the OSI protocols
.IP "   \(bu
changes to the network layering and existing protocol implementations
to allow greater caching and pipelining
.IP "   \(bu
a complete, conforming IEEE 1003.1 (POSIX) system interface
.IP "   \(bu
a standard filesystem interface allowing simultaneous operation of
multiple local and remote filesystem types
.PP
If one of the current Network File System implementations being done
outside of Berkeley is made available at least three months before
this release, it will be included in this release as well;
this is expected to occur.
.LP
3.  We will submit a technical report
describing the work done under this proposal.
E 2
.bp
E 1
