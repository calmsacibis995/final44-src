h30934
s 00000/00000/00733
d D 8.1 93/06/08 16:54:32 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00731
d D 5.5 93/06/05 16:38:43 bostic 7 6
c new doc.mk; document numbering changes for 4.4BSD
e
s 00002/00000/00731
d D 5.4 91/04/17 12:09:50 bostic 6 5
c new copyright; att/bsd/shared
e
s 00002/00002/00729
d D 5.3 86/05/25 15:52:27 mckusick 5 4
c doc moves from SMM:8 to SMM:21
e
s 00002/00001/00729
d D 5.2 86/05/14 10:46:44 kjd 4 2
c document distributed with 4.3BSD
e
s 00000/00000/00730
d R 6.1 86/05/13 17:57:23 kjd 3 2
c document for 4.3BSD release
e
s 00000/00000/00730
d D 5.1 86/05/13 17:56:59 kjd 2 1
c document distributed with 4.2BSD
e
s 00730/00000/00000
d D 4.1 86/05/13 17:56:34 kjd 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 6
.\" %sccs.include.proprietary.roff%
.\"
E 6
I 1
.\"	%W% (Berkeley) %G%
.\"
D 4
.RP
E 4
I 4
D 5
.EH 'SMM:8-%''A Dial-Up Network of \s-2UNIX\s+2 Systems'
.OH 'Dial-Up Network of \s-2UNIX\s+2 Systems''SMM:8-%'
E 5
I 5
D 7
.EH 'SMM:21-%''A Dial-Up Network of \s-2UNIX\s+2 Systems'
.OH 'Dial-Up Network of \s-2UNIX\s+2 Systems''SMM:21-%'
E 7
I 7
.EH 'SMM:15-%''A Dial-Up Network of \s-2UNIX\s+2 Systems'
.OH 'Dial-Up Network of \s-2UNIX\s+2 Systems''SMM:15-%'
E 7
E 5
E 4
.if n .ls 2
.ds RH Nowitz
.ND "August 18, 1978"
.TL
A Dial-Up Network of
UNIX\s6\uTM\d\s0
Systems
.AU
D. A. Nowitz
.AU
M. E. Lesk
.AI
AT&T Bell Laboratories
Murray Hill, NJ
.AB
.if n .ls 2
A network of over eighty
.UX
computer systems has been established using the
telephone system as its primary communication medium.
The network was designed to meet the growing demands for
software distribution and exchange.
Some advantages of our design are:
.IP -
The startup cost is low.
A system needs only a dial-up port,
but systems with automatic calling units have much more
flexibility.
.IP -
No operating system changes are required to install or use the system.
.IP -
The communication is basically over dial-up lines,
however, hardwired communication lines can be used
to increase speed.
.IP -
The command for sending/receiving files is simple to use.
.sp
Keywords: networks, communications, software distribution, software maintenance
.AE
.NH 
Purpose
.PP
The widespread use of the
.UX
system
.[
ritchie thompson bstj 1978
.]
within Bell Laboratories
has produced problems of software distribution and maintenance.
A conventional mechanism was set up to distribute the operating
system and associated programs from a central site to the
various users.
However this mechanism alone does not meet all software
distribution needs.
Remote sites generate much software and must transmit it to
other sites.
Some
.UX
systems
are themselves central sites for redistribution
of a particular specialized utility,
such as the Switching Control Center System.
Other sites have particular, often long-distance needs for
software exchange; switching research,
for example, is carried on in
New Jersey, Illinois, Ohio, and Colorado.
In addition, general purpose utility programs are written at
all
.UX
system sites.
The
.UX
system is modified
and enhanced by many people in many places and
it would be very constricting to deliver new software in a one-way
stream without any alternative
for the user sites to respond with changes of their own.
.PP
Straightforward software distribution is only part of the problem.
A large project may exceed the capacity of a single computer and
several machines may be used by the one group of people.
It then becomes necessary
for them to pass messages, data and other information back an forth
between computers.
.PP
Several groups with similar problems, both inside and outside of
Bell Laboratories, have constructed networks built of
hardwired connections only.
.[
dolotta mashey 1978 bstj
.]
.[
network unix system chesson
.]
Our network, however, uses both dial-up and hardwired
connections so that service can be provided to as many sites as possible.
.NH
Design Goals
.PP
Although some of our machines are connected directly, others
can only communicate over low-speed dial-up lines.
Since the dial-up lines are often unavailable
and file transfers may take considerable time,
we spool all work and transmit in the background.
We also had to adapt to a community of systems which are independently
operated and resistant to suggestions that they should all
buy particular hardware or install particular operating system
modifications.
Therefore, we make minimal demands on the local sites
in the network.
Our implementation requires no operating system changes;
in fact, the transfer programs look like any other user
entering the system through the normal dial-up login ports,
and obeying all local protection rules.
.PP
We distinguish ``active'' and ``passive'' systems
on the network.
Active systems have an automatic calling unit
or a hardwired line to another system,
and can initiate a connection.
Passive systems do not have the hardware
to initiate a connection.
However, an
active system can be assigned the job of calling passive
systems and executing work found there;
this makes a passive system the functional equivalent of
an active system, except for an additional delay while it waits to be polled.
Also, people frequently log into active systems and
request copying from one passive system to another.
This requires two telephone calls, but even so, it is faster
than mailing tapes.
.PP
Where convenient, we use hardwired communication lines.
These permit much faster transmission and multiplexing
of
the communications link.
Dial-up connections are made at either 300 or 1200 baud;
hardwired connections are asynchronous up to 9600 baud 
and might run even faster on special-purpose communications
hardware.
.[
fraser spider 1974 ieee
.]
.[
fraser channel network datamation 1975
.]
Thus, systems typically join our network first as
passive systems and when
they find the service more important, they acquire
automatic calling units and become active
systems; eventually, they may install high-speed
links to particular machines with which they
handle a great deal of traffic.
At no point, however, must users change their
programs or procedures.
.PP
The basic operation of the network is very simple.
Each participating system has a spool directory,
in which work to be done (files to be moved, or commands to be executed
remotely) is stored.
A standard program,
.I uucico ,
performs all transfers.
This program starts by identifying a particular communication channel
to a remote system with which it will hold a conversation.
.I Uucico
then selects a device and establishes the connection,
logs onto the remote machine
and starts the
.I uucico
program on the remote machine.
Once two of these programs are connected, they first agree on a line protocol,
and then start exchanging work.
Each program in turn, beginning with the calling (active system) program,
transmits everything it needs, and then asks the other what it wants done.
Eventually neither has any more work, and both exit.
.PP
In this way, all services are available from all sites; passive sites,
however, must wait until called.
A variety of protocols may be used; this conforms to the real,
non-standard world.
As long as the caller and called programs have a protocol in common,
they can communicate.
Furthermore, each caller knows the hours when each destination system
should be called.
If a destination is unavailable, the data intended for it
remain in the spool directory until the destination machine can be reached.
.PP
The implementation of this
Bell Laboratories network
between independent sites, all of which
store proprietary programs and data,
illustratives the pervasive need for security
and administrative controls over file access.
Each site, in configuring its programs and system files,
limits and monitors transmission.
In order to access a file a user needs access permission
for the machine that contains the file and access permission
for the file itself.
This is achieved by first requiring the user to use his password
to log into his local machine and then his local
machine logs into the remote machine whose files are to be accessed.
In addition, records are kept identifying all files
that are moved into and out of the local system,
and how the requestor of such accesses identified
himself.
Some sites may arrange
to permit users only
to call up
and request work to be done;
the calling users are then called back
before the work is actually done.
It is then possible to verify
that the request is legitimate from the standpoint of the
target system, as well as the originating system.
Furthermore, because of the call-back,
no site can masquerade as another
even if it knows all the necessary passwords.
.PP
Each machine can optionally maintain a sequence count for
conversations with other machines and require a verification of the
count at the start of each conversation.
Thus, even if call back is not in use, a successful masquerade requires
the calling party to present the correct sequence number.
A would-be impersonator must not just steal the correct phone number,
user name, and password, but also the sequence count, and must call in
sufficiently promptly to precede the next legitimate request from either side.
Even a successful masquerade will be detected on the next correct
conversation.
.NH
Processing
.PP
The user has two commands which set up communications,
.I uucp
to set up file copying,
and
.I uux
to set up command execution where some of the required
resources (system and/or files)
are not on the local machine.
Each of these commands will put work and data files
into the spool directory for execution by
.I uucp
daemons.
Figure 1 shows the major blocks of the file transfer process.
.SH
File Copy
.PP
The
.I uucico
program is used to perform all communications between
the two systems.
It performs the following functions:
.RS
.IP - 3
Scan the spool directory for work.
.IP -
Place a call to a remote system.
.IP -\ \ 
Negotiate a line protocol to be used.
.IP -\ \ 
Start program
.I uucico
on the remote system.
.IP -\ \ 
Execute all requests from both systems.
.IP -\ \ 
Log work requests and work completions.
.RE
.LP
.I Uucico
may be started in several ways;
.RS
.IP a) 5
by a system daemon,
.IP b)
by one of the
.I uucp
or
.I uux
programs,
.IP c)
by a remote system.
.RE
.SH
Scan For Work
.PP
The file names in the spool directory are constructed to allow the
daemon programs
.I "(uucico, uuxqt)"
to determine the files they should look at,
the remote machines they should call
and the order in which the files for a particular
remote machine should be processed.
.SH
Call Remote System
.PP
The call is made using information from several
files which reside in the uucp program directory.
At the start of the call process, a lock is
set on the system being called so that another
call will not be attempted at the same time.
.PP
The system name is found in a
``systems''
file.
The information contained for each system is:
.IP
.RS
.IP [1]
system name,
.IP [2]
times to call the system
(days-of-week and times-of-day),
.IP [3]
device or device type to be used for call,
.IP [4]
line speed,
.IP [5]
phone number,
.IP [6]
login information (multiple fields).
.RE
.PP
The time field is checked against the present time to see
if the call should be made.
The
.I
phone number
.R
may contain abbreviations (e.g. ``nyc'', ``boston'') which get translated into dial
sequences using a
``dial-codes'' file.
This permits the same ``phone number'' to be stored at every site, despite
local variations in telephone services and dialing conventions.
.PP
A ``devices''
file is scanned using fields [3] and [4] from the
``systems''
file to find an available device for the connection.
The program will try all devices which satisfy
[3] and [4] until a connection is made, or no more
devices can be tried.
If a non-multiplexable device is successfully opened, a lock file
is created so that another copy of
.I uucico
will not try to use it.
If the connection is complete, the
.I
login information
.R
is used to log into the remote system.
Then
a command is sent to the remote system
to start the
.I uucico
program.
The conversation between the two
.I uucico
programs begins with a handshake started by the called,
.I SLAVE ,
system.
The
.I SLAVE
sends a message to let the
.I MASTER
know it is ready to receive the system
identification and conversation sequence number.
The response from the
.I MASTER
is
verified by the
.I SLAVE
and if acceptable, protocol selection begins.
.SH
Line Protocol Selection
.PP
The remote system sends a message
.IP "" 12
P\fIproto-list\fR
.LP
where
.I proto-list
is a string of characters, each
representing a line protocol.
The calling program checks the proto-list
for a letter corresponding to an available line
protocol and returns a
.I use-protocol
message.
The
.I use-protocol
message is
.IP "" 12
U\fIcode\fR
.LP
where code is either a one character
protocol letter or a
.I N
which means there is no common protocol.
.PP
Greg Chesson designed and implemented the standard
line protocol used by the uucp transmission program.
Other protocols may be added by individual installations.
.SH
Work Processing
.PP
During processing, one program is the
.I MASTER
and the other is
.I SLAVE .
Initially, the calling program is the
.I MASTER.
These roles may switch one or more times during
the conversation.
.PP
There are four messages used during the
work processing, each specified by the first
character of the message.
They are
.KS
.TS
center;
c l.
S	send a file,
R	receive a file,
C	copy complete,
H	hangup.
.TE
.KE
.LP
The
.I MASTER
will send
.I R
or
.I S
messages until all work from the spool directory is
complete, at which point an
.I H
message will be sent.
The
.I SLAVE
will reply with
\fISY\fR, \fISN\fR, \fIRY\fR, \fIRN\fR, \fIHY\fR, \fIHN\fR,
corresponding to
.I yes
or
.I no
for each request.
.PP
The send and receive replies are
based on permission to access the
requested file/directory.
After each file is copied into the spool directory
of the receiving system,
a copy-complete message is sent by the receiver of the file.
The message
.I CY
will be sent if the
.UX
.I cp
command, used to copy from the spool directory, is successful.
Otherwise, a
.I CN
message is sent.
The requests and results are logged on both systems,
and, if requested, mail is sent to the user reporting completion
(or the user can request status information from the log program at any time).
.PP
The hangup response is determined by the
.I SLAVE
program by a work scan of the spool directory.
If work for the remote system exists in the
.I SLAVE's
spool directory, a
.I HN
message is sent and the programs switch roles.
If no work exists, an
.I HY
response is sent.
.PP
A sample conversation is shown in Figure 2.
.SH
Conversation Termination
.PP
When a
.I HY
message is received by the
.I MASTER
it is echoed back to the
.I SLAVE
and the protocols are turned off.
Each program sends a final "OO" message to the
other.
.NH
Present Uses
.PP
One application of this software is remote mail.
Normally, a
.UX
system user
writes ``mail dan'' to send mail to
user ``dan''.
By writing ``mail usg!dan''
the mail is sent to user 
``dan''
on system ``usg''.
.PP
The primary uses of our network to date have been in software maintenance.
Relatively few of the bytes passed between systems are intended for
people to read.
Instead, new programs (or new versions of programs)
are sent to users, and potential bugs are returned to authors.
Aaron Cohen has implemented a
``stockroom'' which allows remote users to call in and request software.
He keeps a ``stock list'' of available programs, and new bug
fixes and utilities are added regularly.
In this way, users can always obtain the latest version of anything
without bothering the authors of the programs.
Although the stock list is maintained on a particular system,
the items in the stockroom may be warehoused in many places;
typically each program is distributed from the home site of
its author.
Where necessary, uucp does remote-to-remote copies.
.PP
We also routinely retrieve test cases from other systems
to determine whether errors on remote systems are caused
by local misconfigurations or old versions of software,
or whether they are bugs that must be fixed at the home site.
This helps identify errors rapidly.
For one set of test programs maintained by us,
over 70% of the bugs reported from remote sites
were due to old software, and were fixed
merely by distributing the current version.
.PP
Another application of the network for software maintenance
is to compare files on two different machines.
A very useful utility on one machine has been
Doug McIlroy's ``diff'' program
which compares two text files and indicates the differences,
line by line, between them.
.[
hunt mcilroy file
.]
Only lines which are
not identical are printed.
Similarly,
the program ``uudiff''
compares files (or directories) on two machines.
One of these directories may be on a passive system.
The
``uudiff'' program
is set up to work similarly to the inter-system mail, but it is slightly
more complicated.
.PP
To avoid moving large numbers of usually identical
files,  
.I uudiff
computes file checksums
on each side, and only moves files that are different
for detailed comparison.
For large files, this process can be iterated; checksums can be computed
for each line, and only those lines that are different
actually moved.
.PP
The ``uux'' command has
been useful for providing remote output.
There are some machines which do not have hard-copy
devices, but which are connected over 9600 baud
communication lines to machines with printers.
The
.I uux
command allows the formatting of the
printout on the local machine and printing on the
remote machine using standard
.UX
command programs.
.br
.NH
Performance
.PP
Throughput, of course, is primarily dependent on transmission speed.
The table below shows the real throughput of characters
on communication links of different speeds.
These numbers represent actual data transferred;
they do not include bytes used by the line protocol for
data validation such as checksums and messages.
At the higher speeds, contention for the processors on both
ends prevents the network from driving the line full speed.
The range of speeds represents the difference between light and
heavy loads on the two systems.
If desired, operating system modifications can
be installed
that permit full use of even very fast links.
.KS
.TS
center;
c c
n n.
Nominal speed	Characters/sec.
300 baud	27
1200 baud	100-110
9600 baud	200-850
.TE
.KE
In addition to the transfer time, there is some overhead
for making the connection and logging in ranging from
15 seconds to 1 minute.
Even at 300 baud, however, a typical 5,000 byte source program
can be transferred in
four minutes instead of the 2 days that might be required
to mail a tape.
.PP
Traffic between systems is variable.  Between two
closely related systems,
we observed
20 files moved and 5 remote commands executed in a typical day.
A more normal traffic out of a single system would be around
a dozen files per day.
.PP
The total number of sites at present
in the main network is
82, which includes most of the Bell Laboratories
full-size machines
which run the
.UX
operating system.
Geographically, the machines range from Andover, Massachusetts to
Denver, Colorado.
.PP
Uucp has also
been used to set up another network
which connects a group of
systems in operational sites with the home site.
The two networks touch at one
Bell Labs computer.
.NH
Further Goals
.PP
Eventually, we would like to develop a full system of remote software
maintenance.
Conventional maintenance (a support group which mails tapes)
has many well-known disadvantages.
.[
brooks mythical man month 1975
.]
There are distribution errors and delays, resulting in old software
running at remote sites and old bugs continually reappearing.
These difficulties are aggravated when
there are 100 different small systems, instead of a few large ones.
.PP
The availability of file transfer on a network of compatible operating
systems
makes it possible just to send programs directly to the end user who wants them.
This avoids the bottleneck of negotiation and packaging in the central support
group.
The ``stockroom'' serves this function for new utilities
and fixes to old utilities.
However, it is still likely that distributions will not be sent
and installed as often as needed.
Users are justifiably suspicious of the ``latest version'' that has just
arrived; all too often it features the ``latest bug.''
What is needed is to address both problems simultaneously:
.IP 1.
Send distributions whenever programs change.
.IP 2.
Have sufficient quality control so that users will install them.
.LP
To do this, we recommend systematic regression testing both on the
distributing and receiving systems.
Acceptance testing on the receiving systems can be automated and
permits the local system to ensure that its essential work can continue
despite the constant installation of changes sent from elsewhere.
The work of writing the test sequences should be recovered in lower
counseling and distribution costs.
.PP
Some slow-speed network services are also being implemented.
We now have inter-system ``mail'' and ``diff,''
plus the many implied commands represented by ``uux.''
However, we still need inter-system ``write'' (real-time inter-user
communication) and ``who'' (list of people logged in
on different systems).
A slow-speed network of this sort may be very useful
for speeding up counseling and education, even
if not fast enough for the distributed data base
applications that attract many users to networks.
Effective use of remote execution over slow-speed lines, however,
must await the general installation of multiplexable channels so
that long file transfers do not lock out short inquiries.
.NH
Lessons
.PP
The following is a summary of the lessons we learned in
building these programs.
.IP 1.
By starting your network in a way that requires no hardware or major operating system
changes, you can get going quickly.
.IP 2.
Support will follow use.
Since the network existed and was being used, system maintainers
were easily persuaded to help keep it operating, including purchasing
additional hardware to speed traffic.
.IP 3.
Make the network commands look like local commands.
Our users have a resistance to learning anything new:
all the inter-system commands look very similar to
standard
.UX
system
commands so that little training cost
is involved.
.IP 4.
An initial error was not coordinating enough
with existing communications projects: thus, the first
version of this network was restricted to dial-up, since
it did not support the various hardware links between systems.
This has been fixed in the current system.
.SH
Acknowledgements
.PP
We thank G. L. Chesson for his design and implementation
of the packet driver and protocol, and A. S. Cohen, J. Lions,
and P. F. Long for their suggestions and assistance.
.[
$LIST$
.]
E 1
