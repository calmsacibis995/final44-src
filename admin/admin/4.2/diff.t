.ds lq ``
.ds rq ''
.ND
.TL
A 4.1a User's Guide to 4.1c
.br
Last Revised: January 17, 1983
.AU
Sam Leffler
.AI
Computer Systems Research Group
Department of Electrical Engineering and Computer Sciences
University of California, Berkeley
Berkeley, California 94720
(415) 642-7780
.AB
4.1c is an intermediate version of 4.2BSD UNIX for the VAX. 
The system contains many of the facilities to be included
in the 4.2BSD release of UNIX for the VAX, but is incomplete
with respect to the 4.2BSD System Manual.  This note
describes the major changes to the system which are visible
to its users.  These changes are described relative to the
earlier 4.1a intermediate version currently running on most
VAX computers on campus.  No attempt is made to describe the
changes to the UNIX operating system; the interested reader
is referred to the source code and/or local knowledgeable person.
.AE
.ds PF
.SH
Introduction
.PP
4.1c is a major step forward from the 4.1a version of UNIX.
It includes
major revisions to the interprocess communication facilities,
a totally new file system organization, many new system calls
and library routines,
and a few new user level programs which may be of interest to
the everyday user of the system.  In addition, the organization
of the user and system source code has been
totally redone to simplify the location and recompilation
of user programs, as well as increase portability of the operating
system to machines other than the VAX (e.g. 68000's).
.PP
A great deal of effort has been expended to make 4.1c upwards
compatible with 4.1BSD UNIX to avoid requiring
recompilation of user programs and to simplify the bootstrapping
of existing application programs such as language processors. 
However, while it is possible to run existing 4.1 binary images,
it is \fBstrongly\fP
recommended that any programs which perform significant amounts
of input/output be recompiled with the new version of the standard
i/o library to take full advantage of the optimal buffering
policies used (see section 5.2 for more information regarding
these policies).*
.FS
* If at all feasible, it is recommended that all programs (no
matter whether they perform significant i/o or not) be recompiled
to purge old system calls.  Otherwise, these programs may not be
useable in the future when/if the operating system is configured
without 4.1 compatibility.  Also, in certain cases, emulation
of old system calls is more expensive than direct use of the
source code compatible new calls (i.e. \fIioctl\fP(2)).
.FE
Programs which use the 4.1a interprocess 
communication facilities will have to be modified as the revised
system calls are not upwards compatible.  Further, programs which
read directories without the aid of the directory compatibility
package (\fIreaddir\fP(3), et. al.) will also have to be modified as
the format of directories has changed.
.PP
The remainder of this document is broken up into 7 sections.  Changes
to system related data structures which may affect users are described in
section 1.  Section 2 discusses those system calls which are new,
those which have been changed from 4.1a, and those calls which are
considered defunct and should be purged from programs (and avoided
when coding new ones).  Section 3 describes changes to library routines
which are of interest to users.  Section 4 considers the new source
code organization and its impact on users that include files from
these directories.  Section 5 discusses the new file system and
details the new facilities which users should be familiar with.
Section 6 covers user programs which have changed, or which are
new to 4.1c.  Finally, section 7 compares the current state of
the system to the 4.2BSD System Manual and mentions those
facilities which are planned for the 4.2BSD release, but which are
not currently present in 4.1c.
.bp
.NH
System data structure changes
.PP
System facilities in 4.1c are intended to be upwards compatible with
those of 4.1BSD.  In particular, wherever a system call's syntax and/or
semantics
have changed the old entry point in the system call table has been
retained and a new entry point has been defined.  
In certain cases where the parameters to a system call may be used
to decide whether the call is old or new, the system attempts to
map old style parameters to new ones before performing the operation.
An example of the dual entry point technique is the \fIstat\fP
system call, while an example of parameter interpretation is the
\fIioctl\fP call.  However, in certain cases the definition of a
\*(lqsystem type\*(rq has changed and programs which depended on
the earlier type definition may be affected.  This section covers
those types which have changed and which the programmer should be
aware of.
.PP
System time is now kept more accurately.  In both old and new versions
of the system, the time of day is calculated from a simulated line
clock.  The old line clock operated at a 1/60th of a second frequency,
while 4.1c uses a 10 millisecond frequency (1/100th of a second). 
This has been
done to avoid roundoff error and should only affect those programs
that interpret kernel data structures or the process profiling
information obtained through the \fIprof\fP(2) system call.
.PP
A process identifier is now officially a 32-bit quantity.  In
many programs a process pid was stored in a C \fIshort\fP because
it was known to be in the range 0 to 32000.  While pid's in 4.1c
are still restricted to be in this range, the expected
development of distributed applications indicates the high order
16 bits may soon be used to resolve process identities
in a multi host environment.
.PP
The handling of groups has been changed from that of 4.1a.  A
user may now be in a small set of groups (currently 8), each of which
is indicated
by a 32 bit integer value.  In 4.1a, group identifiers were restricted
to be in the range 0 to 255, and a user could be in up to 256 groups
simultaneously.  This change should not affect users unless their
programs explicitly depended on group identifiers being able to fit
in a single byte.
.PP
The structure returned by a \fIstat\fP or \fIfstat\fP
system call is larger.  This is due to inode numbers growing
from 16 to 32 bits and because several new items have been
added to the structure.  The size change should not be directly
visible to users unless programs declare
explicitly sized buffers for receiving the \fIstat\fP information.
The recommended practice is to include the standard header file
<sys/stat.h> and use the \fIstat\fP structure definition.
.PP
A number of new error numbers have been added to the system.
If user programs perform direct indexing into the system error
message array without bounds checking the index, havoc is likely.
Relinking such programs will avoid this pitfall, or, better yet,
one should use the
standard system error printing routine \fIperror\fP(3).
.PP
One major incompatibility with 4.1a (and 4.1BSD) is the
definition of a directory entry.  In previous incarnations
of the system directory entries were fixed size allowing
programs to index into directories and sequentially
scan directories with little regard for directory entry
interpretation.  In 4.1c directory entries are variable
length and thus incompatible.  The recommended practice is
to use the library routines \fIopendir\fP, \fIreaddir\fP,
\fIseekdir\fP, \fItelldir\fP, and \fIclosedir\fP
described in section 3 of the manual.
.PP
File names can be significantly longer.  Data structures
designed to hold them should be sized with MAXPATHLEN (for
the largest possible path name) or MAXNAMLEN (for the largest
possible file name).
.bp
.NH
System calls
.PP
To fully take advantage of 4.1c, and 4.2BSD, users should
familiarize themselves with the new system calls available.
Many of these calls provide facilities not previously available
in UNIX, or provide enhanced facilities which supersede previous
mechanisms.  The following sections describe the new system
calls, those which have been changed from 4.1a, and those
calls which are now considered \*(lqdefunct\*(rq.  Where
pertinent, elaboration is included; in all cases section 2 of
the manual should be consulted.
.NH 2
New system calls
.PP
Table 1 summarizes the new system calls included in 4.1c.  These
calls break down roughly into three categories: interprocess
communication, file system operations, and timing related
operations.
.KF
.DS B
.TS
box;
l | l | l
l | l | l.
Name	Type of Call	Synopsis
_
bind	ipc	bind a name to a socket
fchown	file system	change file's owner given a file descriptor
fchmod	file system	change file's protection given a file descriptor
f\&lock	file system	apply or remove an advisory lock
fsync	file system	sync a file descriptor
ftruncate	file system	truncate file given a file descriptor
getgroups	access control	get group access list
gethostid	misc	get unique identifier of host
getitimer	timing	get value of interval timer
getpagesize	misc	get system page size
getpriority	scheduling	get program scheduling priority
getrlimit	resources	control max system resource consumption
getrusage	resources	get information about resource utilization
gettimeofday	timing	get date and time
listen	ipc	listen on a socket for connections
mkdir	file system	make a directory
readv	i/o	read data into scattered locations of memory
recv	ipc	receive a message on a connected socket
recvfrom	ipc	receive data on a (posssibly unconnected) socket
rename	file system	change the name of a file
rmdir	file system	remove a directory
sendto	ipc	send data on a (possibly unconnected) socket
setgroups	access control	set group access list
sethostid	misc	set unique identifier of host
setitimer	timing	set value of interval timer
setpriority	scheduling	set program scheduling priority
setregid	access control	set real and effective group id's
setreuid	access control	set real and effective user id's
setrlimit	resources	set max system resource consumption
settimeofday	timing	set date and time
truncate	file system	truncate a file to a specific size
writev	i/o	gather scattered data for writing
.TE
.DE
.ce
Table 1. New system calls.
.KE
.NH 3
Interprocess communication
.PP
The new interprocess communication primitives differ from those
available in 4.1a mainly in that they support both on-machine and
off-machine communication.  That is, sockets may now be created
in the \*(lqUNIX communications domain\*(rq, where before sockets were 
usually created in the \*(lqInternet communications domain\*(rq.
Processes communicating through sockets in the UNIX domain are
restricted to be on a single machine (currently), and
are named with UNIX pathnames.  Full Internet support is still
present, but a different procedure is now required to access the
TCP and UDP protocols.  Where before a TCP connection could be
initiated with the calls,
.DS
s = socket(SOCK_STREAM, 0, &myaddress, options);
connect(s, &peeraddress);
.DE
now the following sequence of operations is required,
.DS
s = socket(AF_INET, SOCK_STREAM, 0, 0);
bind(s, &myaddress, sizeof (myaddress), 0);
connect(s, &peeraddress, sizeof (peeraddress), 0);
.DE
On the receiving end the expected sequence of operations
for a server process is of the form:
.DS
.ta 5n 10n 15n 20n 25n 30n 35n 40n 45n 50n 55n 60n 65n 70n 75n 80n
s = socket(AF_INET, SOCK_STREAM, 0, 0);
bind(s, &myaddress, sizeof (myaddress), 0);
listen(s, 5);
for (;;) {
	int hisaddrlen = sizeof (hisaddress), snew;

	snew = accept(s, &hisaddress, &hisaddrlen, 0);
	if (fork() == 0) {
		close(s);
		doit(snew);
		exit(0);
	}
	close(snew);
}
.DE
The listen call indicates incoming connection requests are
to be allowed and queued for acceptance.  The second parameter
indicates a maximum backlog of unaccepted connections.
.NH 3
File system
.PP
In the area of new file system calls the most notable additions
are calls to create and remove directories, a new open call,
and calls to apply advisory locks on files as well as supporting
calls for use with the locking mechanism.
.PP
To make a directory the mkdir call may be used,
.DS
mkdir(name, mode);
.DE
while to remove a directory one may use rmdir,
.DS
rmdir(name);
.DE
A directory must be empty in order for it to be removed.
.PP
The advisory locking facilities allow cooperating processes to
place advisory locks of a \*(lqshared\*(rq or \*(lqexclusive\*(rq
nature on a file.  Locks may be applied at open time, or at
some time afterwards with the f\&lock call,
.DS
f\&lock(fd, operation);
.DE
To increase the usefullness of locks, three new calls
which take a file descriptor instead of a file name have been
added.  These calls, fchown, fchmod, and ftruncate may be
used in conjunction with the locking facilities to perform
consistent operations on critical shared files.
.PP
A truncate call which trims a file
to a specific size is new; this call is mostly intended for use by
Fortran.  The rename system call performs an \*(lqatomic\*(rq
file renaming operation of the form:
.DS
unlink(target)
link(source, target);
unlink(source);
.DE
Rename works both with plain files and directories, but only
when both source and target are on the same file system. 
Further, rename has the important
property that the target is always guaranteed to exist, even
if the system crashes in the middle of the operation.  This
makes rename especially useful for renaming critical temporary
files.  Lastly, an experimental call, fsync, has been added.
Fsync performs a \*(lqsync\*(rq operation on a file descriptor;
guaranteeing the caller that the on-disk representation of a
file is consistent with that present in-core.
.NH 2
Changed system calls.
.PP
Table 2 summarizes those system calls which have changed
from 4.1a.  Of these the most notable is
the open call which now takes three parameters.  The second parameter
to open is now a bit mask of flags, as defined in <file.h>.  A
third parameter, used when creating a file, indicates the mode
of the created file.
.KF
.DS B
.TS
box;
l | l | l
l | l | l.
Name	Type of call	What is different
_
accept	ipc	calling convention
connect	ipc	calling convention
fstat	file system	structure returned is larger
open	file system	3 parameters; subsumes creat system call
select	ipc	calling convention
send	ipc	calling convention
socket	ipc	calling convention
stat	file system	structure returned is larger
ioctl	misc	new commands; commands defined differently
wait	misc	returns struct rusage instead of vtimes
.TE
.DE
.ce
Table 2. Changed system calls.
.KE
.PP
The majority of the changed calls are related to interprocess
communication and represent a more stable design and implementation. 
The interprocess communication facilities now incorporate the
notion of a \*(lqcommunications domain\*(rq in which processes
communicate through sockets.  Naming of sockets is now specified
with variable length byte strings, necessitating many changes to
the calling conventions of system calls.  Connection establishment
in the client-server model is more robust with the addition of
a queue of unaccepted connection requests at the server end.  This
allows multiple pending connection requests to be maintained by
the system, where before connection establishment was totally
serial and prone to failure when the server's system was heavily
loaded.  The select system call interface fully reflects the 4.2 System 
Manual definition taking three bit masks; one each for readable
descriptors, writable descriptors, and those descriptors for which
an urgent condition is pending, and a time out in milliseconds.
The timeout value may be set to 0 if the select call is simply
a \*(lqpoll\*(rq, or the parameter may be specified as a null (zero)
pointer if the select call is to block indefinitely.
.PP
Sending and receiving of data on sockets is now performed with
a collection of calls, where before only a single send and receive
call were available.  The new calls were added to cut down on
the number of parameters supplied in the cases where defaults
were obvious from the state of the socket (e.g. the socket is
in a connected state, so the only destination can be the connected
peer).
.PP
The ioctl call has been modified to simplify the internal
system implementation.  The command argument now specifies
the size and type of the third parameter.  In addition, many
old commands have been superseded by new ones, or are designated
as defunct.
.PP
The stat and fstat calls now return a larger structure.  This
larger structure contains space for extended time stamps on
inodes (not currently implemented), 32-bit inode numbers, an
optimal blocking factor for input/output, and space for
future expansion. 
.PP
The wait system call variant known as wait3 now returns a
struct rusage structure instead of the old vtimes structure.
This structure is identical to that returned by the new getrusage
call and includes several new fields which may be of interest
to programmers trying to collect statistics about the performance
of programs.
.NH 2
Defunct system calls
.PP
The addition of many new facilities has obviated the need for
certain old system calls.  Table 3 indicates those which have
been superseded by new facilities.  System calls present in the
4.1 release
have been maintained for binary compatibility, while those introduced
in the 4.1a version of the system have been deleted.  It is
intended that the calls indicated here will eventually be purged
from the system.  Consequently it is recommended that users 
modify programs which use the old calls so that they will not
be forced at some future time to deal with the complete abolition
of these routines.
.KF
.DS B
.TS
box;
l | l | l
l | l | l.
Name	Type of call	Replacing system call
_
alarm	timing	setitimer
creat	file system	open
ftime	timing	gettimeofday
getgrps	access control	getgroups
gtty	misc	ioctl
setgid	access control	setregid
setgrps	access control	setgroups
setuid	access control	setreuid
stime	timing	settimeofday
stty	misc	ioctl
time	timing	gettimeofday
vlimit	resources	getrlimit and setrlimit
vtimes	timing	getrusage
.TE
.DE
.ce
Table 3.  Defunct system calls.
.KE
.PP
The setgrps and getgrps calls were introduced in 4.1a and are
now permanently replaced by setgroups and getgroups.
.PP
The alarm system call is superseded by the new interval timer
facilities which provide much higher resolution and automatic
reload capability.
.PP
The creat system call is replaced by the new three parameter
open call.  A compatibilty routine which replaces the old
system call is of the form:
.DS
.ta 5n 10n 15n 20n 25n 30n 35n 40n 45n 50n 55n 60n 65n 70n 75n 80n
creat(file, mode)
{
	return (open(file, FCREATE\&|\&FWRONLY\&|\&FTRUNCATE, mode));
}
.DE
.PP
The higher resolution time facilities require a different
interface which has been provided by the gettimeofday and
settimeofday calls.  Time is now available in microseconds
which the interval timer calls, getitimer and setitimer, also support.
A routine which provides the time interface is included in the library for
backwards compatibility.
.PP
Setuid and setgid have been slightly generalized to setreuid
and setregid to allow the super user to set the real and effective
user and group identifiers separately.  This eliminates the need
for many programs to fork a subshell solely for the purpose of
simulating a clients protection domain.
.PP
Stty and gtty have been simulated for some time as specific
ioctl calls.  In 4.1c the system call entry points have been
eliminated entirely.
.PP
The vlimit call has been superseded by the getrlimit and setrlimit
calls which provide more flexibility.  Similarly, the vtimes
call has been replaced by getrusage.
.bp
.NH
Library routines
.NH 2
Names and services
.PP
The standard C runtime library has been extended with a number
of routines for dealing with network-related databases and Internet
addresses.  Routines are available for querying the files describing:
.DS
.ta \w'Internet protocols:   'u
Internet hosts:	/etc/hosts,
Internet networks:	/etc/networks,
Internet protocols:	/etc/protocols, and
Internet services:	/etc/services.
.DE
.PP
The manual pages \fIgethostent\fP(3N), \fIgetnetent\fP(3N),
\fIgetprotoent\fP(3N),
and \fIgetservent\fP(3N) describe the available routines;  the 
file <netdb.h> must be included whenever using these routines.
The routines gethostbyname() and gethostbyaddr()
replace the old routines rhost() and raddr(), respectively.
.NH 2
Internet addresses
.PP
A collection of routines, described in \fIinet\fP(3N), are available
for manipulating Internet addresses as character strings or numbers.
The Internet standard \*(lqdot notation\*(rq is understood by
network programs such as telnet and ftp.  This notation expresses
the 32-bit
Internet address as a 4-tuple of base 256 numbers, in network
standard order.  Thus, for example, the address of ucb-arpa,
physical and logical host 0 on IMP 78, is expressed as 10.0.0.78,
while the address of ucbmonet, host 7 on network 46 is expressed
46.0.0.7.  For more information regarding Internet addresses refer
to \fIinet\fP(3N) and the Internet protocol handbook.
.NH 2
Assembly language assist routines
.PP
A number of routines commonly found in programs which use the interprocess
communication facilities have been added to the standard C run-time
library.  These routines, mainly just C interfaces to specialized VAX
machine instructions, are summarized in Table 4.
.KF
.DS B
.TS
box;
l | l
l | l.
Call	Synopsis
_
bcmp(s1, s2, n)	compare byte-strings; 0 if same, not 0 otherwise
bcopy(s1, s2, n)	copy n bytes from s1 to s2
bzero(base, n)	zero-fill n bytes starting at base
ffs(longword)	find first bit set in 32-bit longword, origin 1
htonl(val)	convert 32-bit quantity from VAX to network byte order
htons(val)	convert 16-bit quantity from VAX to network byte order
insque(head, elem)	insert elem into queue pointed to by head
ntohl(val)	convert 32-bit quantity from network to VAX byte order
ntohs(val)	convert 16-bit quantity from network to VAX byte order
remque(elem)	remove elem from a queue
.TE
.DE
.ce
Table 4.  New C run-time routines.
.KE
.PP
The bcmp, bcopy, and bzero routines manipulate byte strings of a
known size.  Ffs is just the \*(lqfind first set\*(rq instruction of
the VAX, while the insque and remque instructions also just use the
VAX machine instructions.  The htonl, htons, ntohl, and ntohs routines
often are used when dealing with information which is presented in non-VAX byte
order, for instance Internet addresses.  One particularly important
application is in interpreting Internet port numbers as returned by
the getservbyname() routine:
.DS
.ta 5n 10n 15n 20n 25n 30n 35n 40n 45n 50n 55n 60n 65n 70n 75n 80n
#include <sys/types.h>
#include <netdb.h>
printserverport(servicename)
	char *servicename;
{
	struct servent *sp = getservbyname(servicename, 0);

	printf("%s service at port %d, in Internet format %d\n",
		servicename, ntohs((u_short)sp->s_port), sp->s_port);
}
.DE
.NH 2
Libjobs
.PP
The job control library, /usr/lib/libjobs.a, has been extensively
modified.  Any programs which normally use routines from this library
should be relinked.  As noted previously, the wait3 variant of
the wait system call now returns an rusage structure instead of a 
vtimes structure; consult \fIgetrusage\fP(2) for information regarding
the new data structure returned.
.bp
.NH
Source code organization
.PP
The directory layout for user and system source code has been
extensively reorganized in an effort to simplify location as
well as separate machine dependent portions of the system.  The
addition of symbolic links has also aided in specifying well-known
locations in the file system where people may find files, even if
the actual location does not directly correspond (due to file system
space constraints).  The following sections describe the file system
hierarchy as it relates to locating source code
and attempts to pinpoint the location of various files of interest
to the everyday user.
.NH 2
System source code
.PP
The source code for the operating system is found in /sys (normally
a symbolic link to a place in another file system).  Source code is
organized into many directories as shown in Table 5.
.KF
.DS B
.TS
box;
l | l
l | l.
Directory	Contents
_
cassette	files for the TU58 boot cassette
conf	configuration files for \fIconfig\fP(8)
dist	miscellaneous stuff for making up distributions
floppy	files for the RX01 boot floppy
h	machine independent header files
machine	symbolic link to target machine (e.g. /sys/vax)
mdec	low level bootstrap programs
net	common parts of all network code
netimp	hardware independent IMP common code
netinet	DARPA Internet code
netpup	Xerox PUP-I code (grot)
stand	standalone programs and device drivers for the VAX
sys	machine independent parts of the system
tp	distribution binary images
vax	VAX-specific parts of the basic system
vaxif	VAX network interfaces
vaxmba	VAX MASSBUS device drivers
vaxuba	VAX UNIBUS device drivers
.TE
.DE
.ce
Table 5.  System source directory structure.
.KE
.PP
On machines other than the VAX many directories are identical
(e.g. sys), while others are simply replaced.  Include files have
been reorganized substantially to remove machine-dependent files
from the standard system include directory; this is almost certain
to force trivial editing of device drivers.
.NH 2
User source code
.PP
The user source code has been reorganized to reflect the eventual
directory in which the code is to be installed.  In many instances,
however, facilities are comprised of several components, residing
in several directories; the final arbiter of source code location
is the \fIwhereis\fP(1) command.
.PP
All user source code is rooted at the directory /usr/src.  Subdirectories
are named to reflect the eventual target of the command.  For example,
/usr/src/bin contains all source code for programs which reside in /bin.
Programs which reside in /usr/bin are located in /usr/src/usr.bin, while
files placed in /usr/lib are in /usr/src/usr.lib.  A \fImake\fP(1) file
should be present in all directories and those commands located in
subdirectories of /usr/src/* are automatically invoked from the immediate
parent to allow a user to enter /usr/src, type \*(lqmake\*(rq and have
the entire collection of user source code rebuilt.  All make files
adhere to the following conventions:
.IP "make all"
.br
rebuilds all binary images,
.IP "make install"
.br
installs programs created with a previous \*(lqmake all\*(rq command
in the destination directory; if any data files are required these
should also be copied to the destination directory;  the \fIinstall\fP(1)
command is expected to be used in these operations
.IP "make clean"
.br
removes all relocatable binaries and executables, as well as any temporary
files one might normally expect to find (e.g. errs, a.out, x.c, foo)
.PP
On a VAX-11/750 one may expect the following commands
to take approximately 12 hours of real time:
.DS
% cd /usr/src
% make clean
  ...
% make -k
% make install
.DE
Our development machines have been known to do something
like this periodically
(through \fIcron\fP(8)) to insure all installed binary images
faithfully reflect the source code present on the machine.
.NH 2
Include files
.PP
The directory /usr/include has been changed a bit with the advent
of symbolic links and the reorganization of the system source code.
The directory /usr/include/sys is now a symbolic link to /sys/h
to insure the include files used are always the most up to date,
as well as easing problems of moving the system source code.
Several other symbolic links have been added to allow user programs
to locate system related, but machine-dependent files.  The symbolic
links /usr/include/vax, /usr/include/vaxmba, etc. allow programs
to include files from the system directory as <vax/foo.h>, for example.
Finally, certain include files which the system requires for recompilation,
but which previously resided in /usr/include have been replaced by
symbolic links to allow a system to be rebuilt independent of the
/usr file system;  an example of such a file is errno.h.
.bp
.NH
New file system organization
.PP
One of the most significant changes to the system is in the area
of the file system.  A totally new scheme is now being used
in placing information on disks with the results indicating
throughput increases up to an order of magnitude or more.  In
addition, many new user visible facilities have been added to
the system such as symbolic links (present in 4.1a) and extended
file names (up to 255 characters).  This section discusses those
parts of the new file system organization pertinent to users.
.NH 2
Data structures and constants
.PP
The directory format has changed from 4.1a to sustain the extended
length file names.  A directory entry is now variable length and
should be accessed through the \fIopendir\fP(3), \fIreaddir\fP(3),
etc. directory package.  4.1 compatible versions of these
routines are available, to insure applications developed under 4.1c
are still portable to other systems.  To sequentially scan a
directory the sequence of steps shown in Figure 1 (or similar)
is expected.
.KF
.DS
.ta 5n 10n 15n 20n 25n 30n 35n 40n 45n 50n 55n 60n 65n 70n 75n 80n
#include <dir.h>
scan(name)
	char *name;
{
	DIR *fd;
	struct direct *dp;

	fd = opendir(name);
	if (fd == NULL) {
		perror(name);
		return;
	}
	while ((dp = readdir(fd) != NULL) {
		if (dp->d_ino == 0)
			continue;
		if (strcmp(dp->d_name, ".") == 0 ||
		    strcmp(dp->d_name, "..") == 0)
			continue;
		....
	}
	closedir(dp);
}
.DE
.ce
Figure 1.  Scanning a directory with readdir.
.KE
.PP
\fIScandir\fP(3) may be used to read and sort a directory
automatically;
consult the manual pages for more detailed information regarding
these routines.
.PP
A file name is now restricted to be at most MAXNAMLEN (255)
characters, and a full path name is restricted to at most MAXPATHLEN
(1024) characters (defined in <sys/param.h>).  The restriction on
the maximum size of a path name was introduced to allow programs to
defined static arrays of a consistent (and sane) size.
.NH 2
File system parameters
.PP
In addition to the new organization, file systems are also
heavily parameterized.
Each file system is defined to have a primary \*(lqblock size\*(rq and
a \*(lqfragment size\*(rq.  Files are comprised of some number of
full sized blocks of data and zero or more fragments of fragment size.
For example, on a file system with a 4 kilobyte block size and a
1 kilobyte fragment size, a 9.5 kilobyte file contains 2 full sized
blocks and 2 fragments.  The larger block size was added to increase
bandwidth to the disk (by cutting down on the number of input/output
transactions required), while the fragments were included to
minimize wasted space.  The result of this parameterization is that
programs which perform significant file system input/output must now
be cognizant of the underlying file system block size if they intend to
optimize their performance.  The standard i/o library used by most
programs already does this by interpreting a new field returned
by the \fIfstat\fP(2) system call.  This field, st_blksize, contains
the \*(lqoptimal\*(rq blocking factor for performing input/output
on a file descriptor.  For those descriptors associated with files
in the file system, this is just the primary block size of the underlying
file system (for pipes and sockets this is the optimal messages size
as supported by the underlying communications protocols).
.PP
The new file system organization attempts to place data on disks in
an \*(lqoptimal\*(rq fashion.  Here optimal includes
locality of reference (i.e. co-locating data blocks for the
same file), and various hardware specific parameters such as the
rotational speed of the disk and the interrupt service time of the
processor.  These layout policies tend to break down as the file system
becomes totally full, consequently the definition of a \fIfull\fP
file system has been changed slightly.  Under 4.1c a parameter in
the super block of the file system indicates a minimal free space
threshold.  When the file system reaches this threshold it is treated
as full and only the super user is allowed to allocated more disk blocks.
By default this threshold is set at 10%, though system administrators
may choose to alter this value to reflect local requirements.  Running
a file system at 100% physical capacity forces the layout policies into
an essentially random allocation policy (almost what was present under
4.1), while a file system running at 100% logical capacity (i.e.
100% physical capacity minus the free space threshold) still performs
\*(lqoptimal\*(rq layout.  The \fIdf\fP(1) program now indicates
both the physical
size of a file system and the capacity of a file system (possibly 
different).
.bp
.NH
New user programs
.PP
While the majority of 4.1c is concerned with modifications to the
operating system, a number of new user programs are available, as well
as some worthwhile enhancements to existing programs.
.PP
The mail delivery system is totally new with the old delivermail
replaced by the new sendmail.  Sendmail speaks the Internet standard
SMTP protocol, performs a multitude of functions, and in general
is a significant improvement over delivermail.  Accompanying sendmail
is a program to scan the local mail queue, mailq.  One of the most notable
results of sendmail running on a 4.1c machine is that all mail
receipients may now be specified in the Internet standard 
\*(lquser@host.domain\*(rq syntax.  For on-campus use this means
the old style Berknet \*(lqmachine:user\*(rq syntax may be replaced
by \*(lquser@machine\*(rq.  Supporting documentation for sendmail
and it's impact on users is in preparation.
.PP
A new source level debugger for C is included in 4.1c: dbx.  The
debugger understands line numbers, structures, local variables and
more.  In order for it to operate at peak efficiency programs should
be compiled with the \-g option (to generate the copious symbol
table information).  Dbx is intended to totally replace \fIsdb\fP(1),
so it is highly recommended that users get in and try it (a gripe
command is included as part of the debugger command set for those
with something [un]kind to say).
.PP
A successor to the \fIrstat\fP(1X) command, \fInetstat\fP(1), exists.
The major difference here is that network addresses are displayed
symbolically and memory allocation statistics are broken down 
according to their usage within the system.  Refer to the manual
page for more information.
.PP
Tar has been changed to handle symbolic links more knowledgeably.
By default tar will not follow symbolic links so the idiom,
.DS
% tar cf \- . | (cd /foo; tar xf \-)
.DE
will exactly duplicate a directory hierarchy, including symbolic
links.  To force following of symbolic links the \*(lqh\*(rq
flag has been added.  Also, tar takes a \*(lqB\*(rq flag to
force input and output blocking in 20 blocks per record.  This
is useful for connecting two tar's through a network connection.
.PP
The mv command has been extensively reworked to use the new
\fIrename\fP(2) system call.  One can now move directories
and plain files all at once and the restriction on \*(lq..\*(rq
not being part of a pathname has been eliminated.
.PP
Make has been enhanced slightly, by adding a predefined macro,
MFLAGS, which contains the command arguments.  This allows
hierarchies of make files to be more easily constructed as
parameters such as \-k, \-i, and \-t will be propagated.
.PP
The latest version of Mail includes the notion of mail folders
(a la the Rand MH system), as well as facilities to suppress
all those ugly noise lines in your incoming mail.  Refer to
the revised user manual for details.
.PP
The remote login program has been cleaned up some.  The current
terminal control characters are used in interpreting escape sequences.
Only three escapes are now present: ~<suspend-character> for stopping
\*(lqboth sides\*(rq of a remote login, ~<delayed-suspend-character>
for stopping the reading side, but letting the remote side continue
transmitting output to the terminal, and ~. for exiting;
all other escape sequences are transmitted directly without
complaint.  A long outstanding bug which allowed processes
from a previous login session to \*(lqshare\*(rq the terminal
with the current session has been fixed on the server end.
.PP
Many other programs have been modified to use the new system
calls such as: cp, mkdir, rmdir, rm, restor, and passwd.  In
most cases the changes were done to increase the speed with
which they do their work.
.bp
.NH
How close is 4.1c to 4.2?
.PP
There are three major parts of 4.2 which are not included in
the 4.1c version of the system.  These are:
.IP "1)"
Memory management facilities to allow sharing memory
between processes and map files to/from memory.
.IP "2)"
A new signal package which more closely resembles the semantics
of hardware interrupts.
.IP "3)"
Transparent remote file access.
.PP
In addition to the above, certain areas such as the
interprocess communication and networking facilities are
still under development.
The aim of \*(lqreleasing\*(rq 4.1c has been to get users
the most important enhancements to the systems at the earliest
possible time, while not providing them with a system which
will be hopelessly incompatible with the eventual 4.2 distribution.
To this end, system calls and library routines included in 4.1c
have identical calling conventions to those envisioned in 4.2
wherever possible.
Users developing applications under 4.1c should find their
programs directly transportable to 4.2 with little, if any,
change.
