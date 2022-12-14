h18839
s 00002/00002/00560
d D 8.1 93/06/08 14:06:36 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00560
d D 5.3 93/06/08 11:40:54 mckusick 3 2
c update from Rick Macklem
e
s 00083/00143/00479
d D 5.2 93/06/05 16:42:54 mckusick 2 1
c merge together for NFS paper
e
s 00622/00000/00000
d D 5.1 93/05/20 16:19:36 bostic 1 0
c date and time created 93/05/20 16:19:36 by bostic
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1993 The Regents of the University of California.
.\" All rights reserved.
E 4
I 4
.\" Copyright (c) 1993
.\"	The Regents of the University of California.  All rights reserved.
E 4
.\"
I 2
.\" This document is derived from software contributed to Berkeley by
.\" Rick Macklem at The University of Guelph.
.\"
E 2
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" run off as psroff -me
.tp
.sp 2
.(l C
Notes on the 4.4 BSD NFS Implementation
.sp
Rick Macklem
.br
University of Guelph
.sp
ABSTRACT
.)l
E 2
I 2
.sh 1 "NFS Implementation"
E 2
.pp
D 2
The 4.4BSD implementation of the Network File System (NFS)\** is intended to interoperate with
.(f
\**Network File System (NFS) is believed to be a registered trademark of
Sun Microsystems Inc.
.)f
other NFS Version 2 Protocol (RFC1094) implementations but also
allows use of an alternate protocol that is hoped to provide better performance
in certain environments.
This paper will informally discuss these various protocol features and
their use.
There is a brief overview of the implementation followed by several sections
on various problem areas related to NFS and some hints on how to deal with
them.
.sp
.sh 1 "Implementation"
.pp
E 2
The 4.4BSD implementation of NFS and the alternate protocol nicknamed
Not Quite NFS (NQNFS) are kernel resident, but make use of a few system
daemons.
The kernel implementation does not use an RPC library, handling the RPC
request and reply messages directly in \fImbuf\fR data areas. NFS
interfaces to the network using
sockets via. the kernel interface available in
\fIsys/kern/uipc_syscalls.c\fR as \fIsosend(), soreceive(),\fR...
There are connection management routines for support of sockets for connection
oriented protocols and timeout/retransmit support for datagram sockets on
the client side.
D 2
For connection oriented transport protocols, such as TCP/IP, there is one connection
for each client to server mount point that is maintained until a
umount.
E 2
I 2
For connection oriented transport protocols,
such as TCP/IP, there is one connection
for each client to server mount point that is maintained until an umount.
E 2
If the connection breaks, the client will attempt a reconnect with a new
socket.
The client side can operate without any daemons running, but performance
will be improved by running nfsiod daemons that perform read-aheads
and write-behinds.
For the server side to function, the daemons portmap, mountd and
nfsd must be running.
The mountd daemon performs two important functions.
.ip 1)
Upon startup and after a hangup signal, mountd reads the exports
file and pushes the export information for each local file system down
into the kernel via. the mount system call.
.ip 2)
Mountd handles remote mount protocol (RFC1094, Appendix A) requests.
.lp
The nfsd master daemon forks off children that enter the kernel
via. the nfssvc system call. The children normally remain kernel
resident, providing a process context for the NFS RPC servers. The only
D 2
exception to this is when a Kerberos [Steiner88] ticket is received and at that time
E 2
I 2
exception to this is when a Kerberos [Steiner88]
ticket is received and at that time
E 2
the nfsd exits the kernel temporarily to verify the ticket via. the
Kerberos libraries and then returns to the kernel with the results.
(This only happens for Kerberos mount points as described further under
Security.)
Meanwhile, the master nfsd waits to accept new connections from clients
using connection oriented transport protocols and passes the new sockets down
into the kernel.
The client side mount_nfs along with portmap and
mountd are the only parts of the NFS subsystem that make any
use of the Sun RPC library.
.sh 1 "Mount Problems"
.pp
There are several problems that can be encountered at the time of an NFS
mount, ranging from a unresponsive NFS server (crashed, network partitioned
from client, etc.) to various interoperability problems between different
NFS implementations.
.pp
On the server side,
if the 4.4BSD NFS server will be handling any PC clients, mountd will
require the \fB-n\fR option to enable non-root mount request servicing.
Running of a pcnfsd\** daemon will also be necessary.
.(f
\** Pcnfsd is available in source form from Sun Microsystems and many
anonymous ftp sites.
.)f
The server side requires that the daemons
mountd and nfsd be running and that
they be registered with portmap properly.
If problems are encountered,
the safest fix is to kill all the daemons and then restart them in
the order portmap, mountd and nfsd.
Other server side problems are normally caused by problems with the format
D 2
of the exports file, which is covered under Security and in the exports man page.
E 2
I 2
of the exports file, which is covered under
Security and in the exports man page.
E 2
.pp
On the client side, there are several mount options useful for dealing
with server problems.
In cases where a file system is not critical for system operation, the
\fB-b\fR
mount option may be specified so that mount_nfs will go into the
background for a mount attempt on an unresponsive server.
This is useful for mounts specified in
\fIfstab(5)\fR,
so that the system will not get hung while booting doing
\fBmount -a\fR
because a file server is not responsive.
On the other hand, if the file system is critical to system operation, this
option should not be used so that the client will wait for the server to
come up before completing bootstrapping.
There are also three mount options to help deal with interoperability issues
with various non-BSD NFS servers. The
\fB-P\fR
option specifies that the NFS
client use a reserved IP port number to satisfy some servers' security
requirements.\**
.(f
\**Any security benefit of this is highly questionable and as
such the BSD server does not require a client to use a reserved port number.
.)f
The
\fB-c\fR
option stops the NFS client from doing a \fIconnect\fR on the UDP
socket, so that the mount works with servers that send NFS replies from
port numbers other than the standard 2049.\**
.(f
\**The Encore Multimax is known
to require this.
.)f
Finally, the
\fB-g=\fInum\fR
option sets the maximum size of the group list in the credentials passed
to an NFS server in every RPC request. Although RFC1057 specifies a maximum
size of 16 for the group list, some servers can't handle that many.
D 2
If a user, particularly root doing a mount, keeps getting access denied from a file server, try temporarily
E 2
I 2
If a user, particularly root doing a mount,
keeps getting access denied from a file server, try temporarily
E 2
reducing the number of groups that user is in to less than 5
by editing /etc/group. If the user can then access the file system, slowly
increase the number of groups for that user until the limit is found and
D 2
then peg the limit there
with the
E 2
I 2
then peg the limit there with the
E 2
\fB-g=\fInum\fR
option.
D 2
This implies that the server
will only see the first \fInum\fR groups that the user is in, which can cause some
accessibility problems.
E 2
I 2
This implies that the server will only see the first \fInum\fR
groups that the user is in, which can cause some accessibility problems.
E 2
.pp
D 2
For sites that have many NFS servers, amd [Pendry93] is a useful administration tool.
E 2
I 2
For sites that have many NFS servers, amd [Pendry93]
is a useful administration tool.
E 2
It also reduces the number of actual NFS mount points, alleviating problems
with commands such as df(1) that hang when any of the NFS servers is
unreachable.
.sh 1 "Dealing with Hung Servers"
.pp
There are several mount options available to help a client deal with
being hung waiting for response from a crashed or unreachable\** server.
.(f
\**Due to a network partitioning or similar.
.)f
By default, a hard mount will continue to try to contact the server
``forever'' to complete the system call. This type of mount is appropriate
when processes on the client that access files in the file system do not
tolerate file I/O systems calls that return -1 with \fIerrno == EINTR\fR
and/or access to the file system is critical for normal system operation.
.lp
There are two other alternatives:
.ip 1)
D 2
A soft mount (\fB-s\fR option) retries an RPC \fIn\fR times and then the corresponding
E 2
I 2
A soft mount (\fB-s\fR option) retries an RPC \fIn\fR
times and then the corresponding
E 2
system call returns -1 with errno set to EINTR.
For TCP transport, the actual RPC request is not retransmitted, but the
D 2
timeout intervals waiting for a reply from the server are done in the same manner
as UDP for this purpose.
E 2
I 2
timeout intervals waiting for a reply from the server are done
in the same manner as UDP for this purpose.
E 2
The problem with this type of mount is that most applications do not
expect an EINTR error return from file I/O system calls (since it never
occurs for a local file system) and get confused by the error return
from the I/O system call.
The option
\fB-x=\fInum\fR
is used to set the RPC retry limit and if set too low, the error returns
will start occurring whenever the NFS server is slow due to heavy load.
Alternately, a large retry limit can result in a process hung for a long
time, due to a crashed server or network partitioning.
.ip 2)
An interruptible mount (\fB-i\fR option) checks to see if a termination signal
is pending for the process when waiting for server response and if it is,
the I/O system call posts an EINTR. Normally this results in the process
D 2
being terminated by the signal when returning from the system call. This allows you to
``^C'' out of processes that are hung due to unresponsive servers.
E 2
I 2
being terminated by the signal when returning from the system call.
This feature allows you to ``^C'' out of processes that are hung
due to unresponsive servers.
E 2
The problem with this approach is that signals that are caught by
a process are not recognized as termination signals
and the process will remain hung.\**
.(f
\**Unfortunately, there are also some resource allocation situations in the
BSD kernel where the termination signal will be ignored and the process
will not terminate.
.)f
.sh 1 "RPC Transport Issues"
.pp
The NFS Version 2 protocol runs over UDP/IP transport by
D 2
sending each Sun Remote Procedure Call (RFC1057) request/reply message in a single UDP
E 2
I 2
sending each Sun Remote Procedure Call (RFC1057)
request/reply message in a single UDP
E 2
datagram. Since UDP does not guarantee datagram delivery, the
Remote Procedure Call (RPC) layer
times out and retransmits an RPC request if
no RPC reply has been received. Since this round trip timeout (RTO) value 
is for the entire RPC operation, including RPC message transmission to the
server, queuing at the server for an nfsd, performing the RPC and
sending the RPC reply message back to the client, it can be highly variable
for even a moderately loaded NFS server.
As a result, the RTO interval must be a conservation (large) estimate, in
order to avoid extraneous RPC request retransmits.\**
.(f
D 2
\**At best, an extraneous RPC request retransmit increases the load on the server and
at worst can result in damaged files on the server when non-idempotent RPCs
are redone. [Juszczak89]
E 2
I 2
\**At best, an extraneous RPC request retransmit increases
the load on the server and at worst can result in damaged files
on the server when non-idempotent RPCs are redone [Juszczak89].
E 2
.)f
Also, with an 8Kbyte read/write data size
(the default), the read/write reply/request will be an 8+Kbyte UDP datagram
that must normally be fragmented at the IP layer for transmission.\**
.(f
D 2
\**6 IP fragments for an Ethernet, which has an maximum transmission unit of 1500bytes.
E 2
I 2
\**6 IP fragments for an Ethernet,
which has an maximum transmission unit of 1500bytes.
E 2
.)f
D 2
For IP fragments to be successfully reassembled into the IP datagram at the receive end, all
E 2
I 2
For IP fragments to be successfully reassembled into
the IP datagram at the receive end, all
E 2
fragments must be received within a fairly short ``time to live''.
D 2
If one fragment is lost/damaged in transit, the entire RPC must be retransmitted
and redone.
E 2
I 2
If one fragment is lost/damaged in transit,
the entire RPC must be retransmitted and redone.
E 2
This problem can be exaggerated by a network interface on the receiver that
D 3
cannot handle the reception of back to back network packets. [Kent87]
E 3
I 3
cannot handle the reception of back to back network packets. [Kent87a]
E 3
.pp
There are several tuning mount
D 2
options on the client side that can prove useful when trying to alleviate performance
problems related to UDP RPC transport.
E 2
I 2
options on the client side that can prove useful when trying to
alleviate performance problems related to UDP RPC transport.
E 2
The options
\fB-r=\fInum\fR
and
\fB-w=\fInum\fR
specify the maximum read or write data size respectively.
The size \fInum\fR
should be a power of 2 (4K, 2K, 1K) and adjusted downward from the
maximum of 8Kbytes
whenever IP fragmentation is causing problems. The best indicator of
IP fragmentation problems is a significant number of
\fIfragments dropped after timeout\fR
D 2
reported by the \fIip:\fR section of a \fBnetstat -s\fR command on either the client or server.
E 2
I 2
reported by the \fIip:\fR section of a \fBnetstat -s\fR
command on either the client or server.
E 2
Of course, if the fragments are being dropped at the server, it can be
fun figuring out which client(s) are involved.
D 2
The most likely candidates are clients that are not on the same local area network as the
E 2
I 2
The most likely candidates are clients that are not
on the same local area network as the
E 2
server or have network interfaces that do not receive several
back to back network packets properly.
.pp
By default, the 4.4BSD NFS client dynamically estimates the retransmit
timeout interval for the RPC and this appears to work reasonably well for
many environments. However, the
\fB-d\fR
flag can be specified to turn off
the dynamic estimation of retransmit timeout, so that the client will
use a static initial timeout interval.\**
.(f
\**After the first retransmit timeout, the initial interval is backed off
exponentially.
.)f
The
\fB-t=\fInum\fR
option can be used with
\fB-d\fR
to set the initial timeout interval to other than the default of 2 seconds.
The best indicator that dynamic estimation should be turned off would
be a significant number\** in the \fIX Replies\fR field and a
.(f
\**Even 0.1% of the total RPCs is probably significant.
.)f
D 2
large number in the \fIRetries\fR field in the \fIRpc Info:\fR section as reported
E 2
I 2
large number in the \fIRetries\fR field
in the \fIRpc Info:\fR section as reported
E 2
by the \fBnfsstat\fR command.
On the server, there would be significant numbers of \fIInprog\fR recent
request cache hits in the \fIServer Cache Stats:\fR section as reported
by the \fBnfsstat\fR command, when run on the server.
.pp
The tradeoff is that a smaller timeout interval results in a better
average RPC response time, but increases the risk of extraneous retries
that in turn increase server load and the possibility of damaged files
on the server. It is probably best to err on the safe side and use a large
(>= 2sec) fixed timeout if the dynamic retransmit timeout estimation
seems to be causing problems.
.pp
An alternative to all this fiddling is to run NFS over TCP transport instead
D 2
of UDP. Since the 4.4BSD TCP implementation provides reliable delivery with congestion control, it
avoids all of the above problems.
E 2
I 2
of UDP.
Since the 4.4BSD TCP implementation provides reliable
delivery with congestion control, it avoids all of the above problems.
E 2
It also permits the use of read and write data sizes greater than the 8Kbyte
limit for UDP transport.\**
.(f
\**Read/write data sizes greater than 8Kbytes will not normally improve
performance unless the kernel constant MAXBSIZE is increased and the
file system on the server has a block size greater than 8Kbytes.
.)f
NFS over TCP usually delivers comparable to significantly better performance
than NFS over UDP
unless the client or server processor runs at less than 5-10MIPS. For a
slow processor, the extra CPU overhead of using TCP transport will become
significant and TCP transport may only be useful when the client
D 3
to server interconnect traverses congestions gateways.
E 3
I 3
to server interconnect traverses congested gateways.
E 3
The main problem with using TCP transport is that it is only supported
between BSD clients and servers.\**
.(f
\**There are rumors of commercial NFS over TCP implementations on the horizon
and these may well be worth exploring.
.)f
.sh 1 "Other Tuning Tricks"
.pp
D 2
Another mount option that may improve performance over certain network interconnects is
\fB-a=\fInum\fR
E 2
I 2
Another mount option that may improve performance over
certain network interconnects is \fB-a=\fInum\fR
E 2
which sets the number of blocks that the system will
attempt to read-ahead during sequential reading of a file. The default value
of 1 seems to be appropriate for most situations, but a larger value might
achieve better performance for some environments, such as a mount to a server
across a ``high bandwidth * round trip delay'' interconnect.
.pp
For the adventurous, playing with the size of the buffer cache
can also improve performance for some environments that use NFS heavily.
Under some workloads, a buffer cache of 4-6Mbytes can result in significant
performance improvements over 1-2Mbytes, both in client side system call
response time and reduced server RPC load.
D 2
The buffer cache size defaults to 10% of physical memory, but this can
be overridden by specifying the BUFPAGES option in the machine's config file.\**
E 2
I 2
The buffer cache size defaults to 10% of physical memory,
but this can be overridden by specifying the BUFPAGES option
in the machine's config file.\**
E 2
.(f
BUFPAGES is the number of physical machine pages allocated to the buffer cache.
ie. BUFPAGES * NBPG = buffer cache size in bytes
.)f
When increasing the size of BUFPAGES, it is also advisable to increase the
number of buffers NBUF by a corresponding amount.
Note that there is a tradeoff of memory allocated to the buffer cache versus
available for paging, which implies that making the buffer cache larger
will increase paging rate, with possibly disastrous results.
.sh 1 "Security Issues"
.pp
D 2
When a machine is running an NFS server it opens up a great big security
hole. For ordinary NFS, the server receives client credentials in the RPC request as a user id
E 2
I 2
When a machine is running an NFS server it opens up a great big security hole.
For ordinary NFS, the server receives client credentials
in the RPC request as a user id
E 2
and a list of group ids and trusts them to be authentic!
D 2
The only tool available to restrict remote access to file systems with is the exports(5) file,
E 2
I 2
The only tool available to restrict remote access to
file systems with is the exports(5) file,
E 2
so file systems should be exported with great care.
The exports file is read by mountd upon startup and after a hangup signal
is posted for it and then as much of the access specifications as possible are
pushed down into the kernel for use by the nfsd(s).
The trick here is that the kernel information is stored on a per
local file system mount point and client host address basis and cannot refer to
individual directories within the local server file system.
It is best to think of the exports file as referring to the various local
file systems and not just directory paths as mount points.
A local file system may be exported to a specific host, all hosts that
match a subnet mask or all other hosts (the world). The latter is very
dangerous and should only be used for public information. It is also
strongly recommended that file systems exported to ``the world'' be exported
read-only.
For each host or group of hosts, the file system can be exported read-only or
D 2
read/write. You can also define one of three client user id to server credential
E 2
I 2
read/write.
You can also define one of three client user id to server credential
E 2
mappings to help control access.
Root (user id == 0) can be mapped to some default credentials while all other
D 2
user ids are accepted as given. If the default credentials for user id equal zero
E 2
I 2
user ids are accepted as given.
If the default credentials for user id equal zero
E 2
are root, then there is essentially no remapping.
Most NFS file systems are exported this way, most commonly mapping
user id == 0 to the credentials for the user nobody.
Since the client user id and group id list is used unchanged on the server
(except for root), this also implies that
D 2
the user id and group id space must be common between the client and server. (ie. user id N on
the client must refer to the same user on the server)
E 2
I 2
the user id and group id space must be common between the client and server.
(ie. user id N on the client must refer to the same user on the server)
E 2
All user ids can be mapped to a default set of credentials, typically that of
the user nobody. This essentially gives world access to all
users on the corresponding hosts.
.pp
There is also a non-standard BSD
\fB-kerb\fR export option that requires the client provide
a KerberosIV rcmd service ticket to authenticate the user on the server.
If successful, the Kerberos principal is looked up in the server's password
and group databases to get a set of credentials and a map of client userid to
these credentials is then cached.
The use of TCP transport is strongly recommended,
since the scheme depends on the TCP connection to avert replay attempts.
Unfortunately, this option is only usable
D 2
between BSD clients and servers since it is not compatible with other known ``kerberized'' NFS
systems.
E 2
I 2
between BSD clients and servers since it is
not compatible with other known ``kerberized'' NFS systems.
E 2
To enable use of this Kerberos option, both mount_nfs on the client and
nfsd on the server must be rebuilt with the -DKERBEROS option and
linked to KerberosIV libraries.
The file system is then exported to the client(s) with the \fB-kerb\fR option
in the exports file on the server
and the client mount specifies the
\fB-K\fR
and
\fB-T\fR
options.
The
\fB-m=\fIrealm\fR
mount option may be used to specify a Kerberos Realm for the ticket
(it must be the Kerberos Realm of the server) that is other than
the client's local Realm.
To access files in a \fB-kerb\fR mount point, the user must have a valid
TGT for the server's Realm, as provided by kinit or similar.
.pp
As well as the standard NFS Version 2 protocol (RFC1094) implementation, BSD
systems can use a variant of the protocol called Not Quite NFS (NQNFS) that
D 2
supports a variety of protocol extensions. This protocol uses 64bit file offsets
E 2
I 2
supports a variety of protocol extensions.
This protocol uses 64bit file offsets
E 2
and sizes, an \fIaccess rpc\fR, an \fIappend\fR option on the write rpc
and extended file attributes to support 4.4BSD file system functionality
more fully.
D 2
It also makes use of a variant of short term \fIleases\fR [Gray89] with delayed write
client caching, in an effort to provide full cache consistency and better
performance.
E 2
I 2
It also makes use of a variant of short term
\fIleases\fR [Gray89] with delayed write client caching,
in an effort to provide full cache consistency and better performance.
E 2
This protocol is available between 4.4BSD systems only and is used when
the \fB-q\fR mount option is specified.
It can be used with any of the aforementioned options for NFS, such as TCP
transport (\fB-T\fR) and KerberosIV authentication (\fB-K\fR).
Although this protocol is experimental, it is recommended over NFS for
mounts between 4.4BSD systems.\**
.(f
D 2
\**I would appreciate email from anyone who can provide NFS vs. NQNFS performance
measurements, particularly fast clients, many clients or over an internetwork
E 2
I 2
\**I would appreciate email from anyone who can provide
NFS vs. NQNFS performance measurements,
particularly fast clients, many clients or over an internetwork
E 2
connection with a large ``bandwidth * RTT'' product.
.)f
.sh 1 "Monitoring NFS Activity"
.pp
The basic command for monitoring NFS activity on clients and servers is
nfsstat. It reports cumulative statistics of various NFS activities,
such as counts of the various different RPCs and cache hit rates on the client
and server. Of particular interest on the server are the fields in the
\fIServer Cache Stats:\fR section, which gives numbers for RPC retries received
in the first three fields and total RPCs in the fourth. The first three fields
should remain a very small percentage of the total. If not, it
would indicate one or more clients doing retries too aggressively and the fix
D 2
would be to isolate these clients, disable the dynamic RTO estimation on them and
E 2
I 2
would be to isolate these clients,
disable the dynamic RTO estimation on them and
E 2
make their initial timeout interval a conservative (ie. large) value.
.pp
On the client side, the fields in the \fIRpc Info:\fR section are of particular
interest, as they give an overall picture of NFS activity.
The \fITimedOut\fR field is the number of I/O system calls that returned -1
D 2
for ``soft'' mounts and can be reduced by increasing the retry limit or changing
E 2
I 2
for ``soft'' mounts and can be reduced
by increasing the retry limit or changing
E 2
the mount type to ``intr'' or ``hard''.
The \fIInvalid\fR field is a count of trashed RPC replies that are received
and should remain zero.\**
.(f
\**Some NFS implementations run with UDP checksums disabled, so garbage RPC
messages can be received.
.)f
The \fIX Replies\fR field counts the number of repeated RPC replies received
from the server and is a clear indication of a too aggressive RTO estimate.
Unfortunately, a good NFS server implementation will use a ``recent request
cache'' [Juszczak89] that will suppress the extraneous replies.
A large value for \fIRetries\fR indicates a problem, but
it could be any of:
.ip \(bu
a too aggressive RTO estimate
.ip \(bu
an overloaded NFS server
.ip \(bu
IP fragments being dropped (gateway, client or server)
.lp
and requires further investigation.
The \fIRequests\fR field is the total count of RPCs done on all servers.
.pp
The \fBnetstat -s\fR comes in useful during investigation of RPC transport
problems.
D 2
The field \fIfragments dropped after timeout\fR in the \fIip:\fR section indicates IP fragments are
E 2
I 2
The field \fIfragments dropped after timeout\fR in
the \fIip:\fR section indicates IP fragments are
E 2
being lost and a significant number of these occurring indicates that the
use of TCP transport or a smaller read/write data size is in order.
A significant number of \fIbad checksums\fR reported in the \fIudp:\fR
section would suggest network problems of a more generic sort.
(cabling, transceiver or network hardware interface problems or similar)
.pp
There is a RPC activity logging facility for both the client and
server side in the kernel.
When logging is enabled by setting the kernel variable nfsrtton to
one, the logs in the kernel structures nfsrtt (for the client side)
and nfsdrt (for the server side) are updated upon the completion
of each RPC in a circular manner.
The pos element of the structure is the index of the next element
of the log array to be updated.
In other words, elements of the log array from \fIlog\fR[pos] to
\fIlog\fR[pos - 1] are in chronological order.
The include file <sys/nfsrtt.h> should be consulted for details on the
fields in the two log structures.\**
.(f
\**Unfortunately, a monitoring tool that uses these logs is still in the
planning (dreaming) stage.
.)f
.sh 1 "Diskless Client Support"
.pp
The NFS client does include kernel support for diskless/dataless operation
where the root file system and optionally the swap area is remote NFS mounted.
A diskless/dataless client is configured using a version of the
``swapvmunix.c'' file as provided in the directory \fIcontrib/diskless.nfs\fR.
If the swap device == NODEV, it specifies an NFS mounted swap area and should
be configured the same size as set up by diskless_setup when run on the server.
This file must be put in the \fIsys/compile/<machine_name>\fR kernel build
directory after the config command has been run, since config does
not know about specifying NFS root and swap areas.
The kernel variable mountroot must be set to nfs_mountroot instead of
ffs_mountroot and the kernel structure nfs_diskless must be filled in
properly.
There are some primitive system administration tools in the \fIcontrib/diskless.nfs\fR directory to assist in filling in
the nfs_diskless structure and in setting up an NFS server for
diskless/dataless clients.
The tools were designed to provide a bare bones capability, to allow maximum
flexibility when setting up different servers.
.lp
The tools are as follows:
.ip \(bu
diskless_offset.c - This little program reads a ``vmunix'' object file and
writes the file byte offset of the nfs_diskless structure in it to
standard out. It was kept separate because it sometimes has to
be compiled/linked in funny ways depending on the client architecture.
(See the comment at the beginning of it.)
.ip \(bu
diskless_setup.c - This program is run on the server and sets up files for a
given client. It mostly just fills in an nfs_diskless structure and
writes it out to either the "vmunix" file or a separate file called
/var/diskless/setup.<official-hostname>
.ip \(bu
diskless_boot.c - There are two functions in here that may be used
by a bootstrap server such as tftpd to permit sharing of the ``vmunix''
object file for similar clients. This saves disk space on the bootstrap
server and simplify organization, but are not critical for correct operation.
They read the ``vmunix''
file, but optionally fill in the nfs_diskless structure from a
separate "setup.<official-hostname>" file so that there is only
one copy of "vmunix" for all similar (same arch etc.) clients.
These functions use a text file called
/var/diskless/boot.<official-hostname> to control the netboot.
.lp
The basic setup steps are:
.ip \(bu
make a "vmunix" for the client(s) with mountroot() == nfs_mountroot()
and swdevt[0].sw_dev == NODEV if it is to do nfs swapping as well
(See the same swapvmunix.c file)
.ip \(bu
run diskless_offset on the vmunix file to find out the byte offset
of the nfs_diskless structure
.ip \(bu
D 2
Run diskless_setup on the server to set up the server and fill in the nfs_diskless structure
for that client.
The nfs_diskless structure can either be written into the vmunix file (the -x option) or
E 2
I 2
Run diskless_setup on the server to set up the server and fill in the
nfs_diskless structure for that client.
The nfs_diskless structure can either be written into the
vmunix file (the -x option) or
E 2
saved in /var/diskless/setup.<official-hostname>.
.ip \(bu
Set up the bootstrap server. If the nfs_diskless structure was written into
the ``vmunix'' file, any vanilla bootstrap protocol such as bootp/tftp can
be used. If the bootstrap server has been modified to use the functions in
diskless_boot.c, then a
file called /var/diskless/boot.<official-hostname>
must be created.
It is simply a two line text file, where the first line is the pathname
of the correct ``vmunix'' file and the second line has the pathname of
the nfs_diskless structure file and its byte offset in it.
For example:
.br
	/var/diskless/vmunix.pmax
.br
	/var/diskless/setup.rickers.cis.uoguelph.ca 642308
.br
.ip \(bu
Create a /var subtree for each client in an appropriate place on the server,
such as /var/diskless/var/<client-hostname>/...
By using the <client-hostname> to differentiate /var for each host,
/etc/rc can be modified to mount the correct /var from the server.
D 2
.sh 1 "Summary"
.pp
The configuration and tuning of an NFS environment tends to be a bit of a
mystic art, but hopefully this paper along with the man pages and other
reading will be helpful. Good Luck.
.sh 1 "Bibliography"
.ip [Gray89] 16
Cary G. Gray and David R. Cheriton, Leases: An Efficient Fault-Tolerant
Mechanism for Distributed File Cache Consistency, In \fIProc. of the
Twelfth ACM Symposium on Operating Systems Principals\fR, pg. 202-210,
Litchfield Park, AZ, Dec. 1989.
.ip [Juszczak89] 16
Chet Juszczak, Improving the Performance and Correctness of an NFS Server,
In \fIProc. Winter 1989 USENIX Conference\fR, pg. 53-63, San Diego, CA, January 1989.
.ip [Keith90] 16
Bruce E. Keith, Perspectives on NFS File Server Performance Characterization,
In \fIProc. Summer 1990 USENIX Conference\fR, pg. 267-277, Anaheim, CA, June 1990.
.ip [Kent87] 16
Christopher. A. Kent and Jeffrey C. Mogul, \fIFragmentation Considered Harmful\fR, Research Report 87/3,
Digital Equipment Corporation Western Research Laboratory, Dec. 1987.
.ip [Macklem91] 16
Rick Macklem, Lessons Learned Tuning the 4.3BSD Reno Implementation of the
NFS Protocol, In \fIProc. Winter USENIX Conference\fR, pg. 53-64,
Dallas, TX, January 1991.
.ip [Nowicki89] 16
Bill Nowicki, Transport Issues in the Network File System, In
\fIComputer Communication Review\fR, pg. 16-20, Vol. 19, Number 2, April 1989.
.ip [Pendry93] 16
Jan-Simon Pendry, 4.4 BSD Automounter Reference Manual, In
\fIsrc/usr.sbin/amd/doc directory of 4.4 BSD distribution tape\fR.
.ip [Reid90] 16
Jim Reid, N(e)FS: the Protocol is the Problem, In
\fIProc. Summer 1990 UKUUG Conference\fR,
London, England, July 1990.
.ip [Sandberg85] 16
Russel Sandberg, David Goldberg, Steve Kleiman, Dan Walsh, and Bob Lyon,
Design and Implementation of the Sun Network filesystem, In \fIProc. Summer
1985 USENIX Conference\fR, pages 119-130, Portland, OR, June 1985.
.ip [Srinivasan89] 16
V. Srinivasan and Jeffrey C. Mogul, \fISpritely NFS: Implementation and
Performance of Cache-Consistency Protocols\fR, Research Report 89/5,
Digital Equipment Corporation Western Research Laboratory, May 1989.
.ip [Steiner88] 16
Jennifer G. Steiner, Clifford Neuman and Jeffrey I. Schiller,
Kerberos: An Authentication Service for Open Network Systems, In
\fIProc. Winter 1988 USENIX Conference\fR, Dallas, TX, February 1988.
.ip [Stern] 16
Hal Stern, \fIManaging NFS and NIS\fR, O'Reilly and Associates,
ISBN 0-937175-75-7.
.ip [Sun87] 16
Sun Microsystems Inc., \fIXDR: External Data Representation Standard\fR,
RFC1014, Network Information Center, SRI International, June 1987.
.ip [Sun88] 16
Sun Microsystems Inc., \fIRPC: Remote Procedure Call Protocol Specification Version 2\fR,
RFC1057, Network Information Center, SRI International, June 1988.
.ip [Sun89] 16
Sun Microsystems Inc., \fINFS: Network File System Protocol Specification\fR,
RFC1094, Network Information Center, SRI International, March 1989.
E 2
E 1
