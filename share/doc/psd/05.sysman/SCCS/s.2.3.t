h14654
s 00001/00000/00467
d D 8.6 94/06/01 18:16:32 ah 11 10
c page breaks for the 4.4BSD manuals
e
s 00001/00001/00466
d D 8.5 94/05/29 00:05:14 mckusick 10 9
c cleanup final nits
e
s 00007/00006/00460
d D 8.4 94/05/26 22:30:53 bostic 9 8
c cleanups and edits for accuracy
e
s 00029/00019/00437
d D 8.3 94/05/20 06:07:01 karels 8 7
c touchups and improvements
e
s 00195/00125/00261
d D 8.2 94/05/16 10:09:38 mckusick 7 6
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00384
d D 8.1 93/06/08 18:06:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00382
d D 6.4 91/04/17 10:02:02 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00384
d D 6.3 86/05/12 01:23:56 karels 4 3
c spelling
e
s 00085/00045/00300
d D 6.2 86/05/12 01:01:32 karels 3 2
c update, correct, rephrase and re-propose
e
s 00005/00005/00340
d D 6.1 86/05/08 12:25:52 mckusick 2 1
c update footnote to reflect NS
e
s 00345/00000/00000
d D 5.1 86/05/08 00:03:42 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 6
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
D 8
.\" Copyright (c) 1983, 1993
E 8
I 8
.\" Copyright (c) 1983, 1993, 1994
E 8
.\"	The Regents of the University of California.  All rights reserved.
E 6
.\"
.\" %sccs.include.redist.roff%
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 7
.sh "Interprocess communications
.NH 3
Interprocess communication primitives
.NH 4
Communication domains
E 7
I 7
.Sh 2 "Interprocess communications
.Sh 3 "Interprocess communication primitives
.Sh 4 "Communication domains
E 7
.PP
The system provides access to an extensible set of 
D 8
communication \fIdomains\fP.  A communication domain
E 8
I 8
communication \fIdomains\fP.  A communication domain (or protocol family)
E 8
is identified by a manifest constant defined in the
D 3
file <sys/socket.h>.
E 3
I 3
file \fI<sys/socket.h>\fP.
E 3
D 7
Important standard domains supported by the system are the ``unix''
D 3
domain, AF_UNIX, for communication within the system, and the ``internet''
domain for communication in the DARPA internet, AF_INET.  Other domains can
be added to the system.
E 3
I 3
domain, AF_UNIX, for communication within the system, the ``Internet''
domain for communication in the DARPA Internet, AF_INET,
and the ``NS'' domain, AF_NS, for communication
E 7
I 7
D 8
Important standard domains supported by the system are the ``UNIX''
domain (AF_UNIX) for communication within the system, the ``Internet''
domain (AF_INET) for communication in the DARPA Internet,
the ISO family of protocols (AF_ISO and AF_CCITT) for providing
E 8
I 8
Important standard domains supported by the system are the local (``UNIX'')
domain (PF_LOCAL or PF_UNIX) for communication within the system,
the ``Internet'' domain (PF_INET) for communication in the DARPA Internet,
the ISO family of protocols (PF_ISO and PF_CCITT) for providing
E 8
a check-off box on the list of your system capabilities,
D 8
and the ``NS'' domain (AF_NS) for communication
E 8
I 8
and the ``NS'' domain (PF_NS) for communication
E 8
E 7
using the Xerox Network Systems protocols.
Other domains can be added to the system.
E 3
D 7
.NH 4
Socket types and protocols
E 7
I 7
.Sh 4 "Socket types and protocols
E 7
.PP
Within a domain, communication takes place between communication endpoints
known as \fIsockets\fP.  Each socket has the potential to exchange
D 3
information with other sockets within the domain.
E 3
I 3
information with other sockets of an appropriate type within the domain.
E 3
.PP
Each socket has an associated
abstract type, which describes the semantics of communication using that
socket.  Properties such as reliability, ordering, and prevention
of duplication of messages are determined by the type.
D 3
The basic set of socket types is defined in <sys/socket.h>:
E 3
I 3
The basic set of socket types is defined in \fI<sys/socket.h>\fP:
E 3
.DS
D 7
/* Standard socket types */
._d
#define	SOCK_DGRAM	1	/* datagram */
#define	SOCK_STREAM	2	/* virtual circuit */
#define	SOCK_RAW	3	/* raw socket */
#define	SOCK_RDM	4	/* reliably-delivered message */
#define	SOCK_SEQPACKET	5	/* sequenced packets */
E 7
I 7
.TS
l s
l l.
Standard socket types
I 9
_
E 9
SOCK_DGRAM	/* datagram */
SOCK_STREAM	/* virtual circuit */
SOCK_RAW	/* raw socket */
SOCK_RDM	/* reliably-delivered message */
SOCK_SEQPACKET	/* sequenced packets */
.TE
E 7
.DE
The SOCK_DGRAM type models the semantics of datagrams in network communication:
messages may be lost or duplicated and may arrive out-of-order.
I 3
A datagram socket may send messages to and receive messages from multiple
peers.
E 3
The SOCK_RDM type models the semantics of reliable datagrams: messages
arrive unduplicated and in-order, the sender is notified if
messages are lost.
D 7
The \fIsend\fP and \fIreceive\fP operations (described below)
generate reliable/unreliable datagrams.
E 7
I 7
The
.Fn send
and
.Fn receive
operations (described below)
generate reliable or unreliable datagrams.
E 7
The SOCK_STREAM type models connection-based virtual circuits: two-way
byte streams with no record boundaries.
I 3
Connection setup is required before data communication may begin.
E 3
The SOCK_SEQPACKET type models a connection-based,
D 8
full-duplex, reliable, sequenced packet exchange;
E 8
I 8
full-duplex, reliable, exchange preserving message boundaries;
E 8
the sender is notified if messages are lost, and messages are never
duplicated or presented out-of-order.
Users of the last two abstractions may use the facilities for
out-of-band transmission to send out-of-band data.
.PP
SOCK_RAW is used for unprocessed access to internal network layers
and interfaces; it has no specific semantics.
D 7
.PP
E 7
D 3
Other socket types can be defined.\(dg
.FS
D 2
\(dg 4.2BSD does not support the SOCK_RDM and SOCK_SEQPACKET types.
E 2
I 2
\(dg 4.3BSD does not support the SOCK_RDM and SOCK_SEQPACKET types
in the INET family; it does not support SOCK_RDM in the NS family.
E 2
.FE
E 3
I 3
Other socket types can be defined.
E 3
.PP
D 3
Each socket may have a concrete \fIprotocol\fP associated with it.
E 3
I 3
Each socket may have a specific \fIprotocol\fP associated with it.
E 3
This protocol is used within the domain to provide the semantics
required by the socket type.
D 3
For example, within the ``internet'' domain, the SOCK_DGRAM type may be
E 3
I 3
Not all socket types are supported by each domain;
support depends on the existence and the implementation
of a suitable protocol within the domain.
For example, within the ``Internet'' domain, the SOCK_DGRAM type may be
E 3
implemented by the UDP user datagram protocol, and the SOCK_STREAM
type may be implemented by the TCP transmission control protocol, while
no standard protocols to provide SOCK_RDM or SOCK_SEQPACKET sockets exist.
D 7
.NH 4
Socket creation, naming and service establishment
E 7
I 7
.Sh 4 "Socket creation, naming and service establishment
E 7
.PP
Sockets may be \fIconnected\fP or \fIunconnected\fP.  An unconnected
D 7
socket descriptor is obtained by the \fIsocket\fP call:
E 7
I 7
socket descriptor is obtained by the
.Fn socket
call:
E 7
.DS
I 7
.Fd socket 3 "create an endpoint for communication
E 7
s = socket(domain, type, protocol);
result int s; int domain, type, protocol;
.DE
I 3
The socket domain and type are as described above,
and are specified using the definitions from \fI<sys/socket.h>\fP.
The protocol may be given as 0, meaning any suitable protocol.
One of several possible protocols may be selected using identifiers
D 7
obtained from a library routine, \fIgetprotobyname\fP.
E 7
I 7
obtained from a library routine,
.Fn getprotobyname .
E 7
E 3
.PP
D 3
An unconnected socket descriptor may yield a connected socket descriptor
E 3
I 3
An unconnected socket descriptor of a connection-oriented type
may yield a connected socket descriptor
E 3
in one of two ways: either by actively connecting to another socket,
or by becoming associated with a name in the communications domain and
\fIaccepting\fP a connection from another socket.
I 3
Datagram sockets need not establish connections before use.
E 3
.PP
D 3
To accept connections, a socket must first have a binding
to a name within the communications domain.  Such a binding
is established by a \fIbind\fP call:
E 3
I 3
To accept connections or to receive datagrams,
a socket must first have a binding
to a name (or address) within the communications domain.
D 7
Such a binding may be established by a \fIbind\fP call:
E 7
I 7
Such a binding may be established by a
.Fn bind
call:
E 7
E 3
.DS
I 7
.Fd bind 3 "bind a name to a socket
E 7
bind(s, name, namelen);
D 3
int s; char *name; int namelen;
E 3
I 3
int s; struct sockaddr *name; int namelen;
E 3
.DE
D 3
A socket's bound name may be retrieved with a \fIgetsockname\fP call:
E 3
I 3
Datagram sockets may have default bindings established when first
sending data if not explicitly bound earlier.
In either case,
D 7
a socket's bound name may be retrieved with a \fIgetsockname\fP call:
E 7
I 7
a socket's bound name may be retrieved with a
.Fn getsockname
call:
E 7
E 3
.DS
I 7
.Fd getsockname 3 "get socket name
E 7
getsockname(s, name, namelen);
D 3
int s; result caddr_t name; result int *namelen;
E 3
I 3
int s; result struct sockaddr *name; result int *namelen;
E 3
.DE
D 7
while the peer's name can be retrieved with \fIgetpeername\fP:
E 7
I 7
while the peer's name can be retrieved with
.Fn getpeername :
E 7
.DS
I 7
.Fd getpeername 3 "get name of connected peer
E 7
getpeername(s, name, namelen);
D 3
int s; result caddr_t name; result int *namelen;
E 3
I 3
int s; result struct sockaddr *name; result int *namelen;
E 3
.DE
Domains may support sockets with several names.
D 7
.NH 4
Accepting connections
.PP
E 7
I 7
.Sh 4 "Accepting connections
.LP
E 7
D 3
Once a binding is made, it is possible to \fIlisten\fP for
connections:
E 3
I 3
Once a binding is made to a connection-oriented socket,
D 7
it is possible to \fIlisten\fP for connections:
E 7
I 7
it is possible to
.Fn listen
for connections:
E 7
E 3
.DS
I 7
.Fd listen 2 "listen for connections on a socket
E 7
listen(s, backlog);
int s, backlog;
.DE
The \fIbacklog\fP specifies the maximum count of connections
that can be simultaneously queued awaiting acceptance.
D 7
.PP
An \fIaccept\fP call:
E 7
I 7
.LP
An
.Fn accept
call:
E 7
.DS
I 7
.Fd accept 3 "accept a connection on a socket
E 7
t = accept(s, name, anamelen);
D 3
result int t; int s; result caddr_t name; result int *anamelen;
E 3
I 3
result int t; int s; result struct sockaddr *name; result int *anamelen;
E 3
.DE
returns a descriptor for a new, connected, socket
from the queue of pending connections on \fIs\fP.
I 3
If no new connections are queued for acceptance,
D 7
the call will wait for a connection unless non-blocking I/O has been enabled.
E 3
.NH 4
Making connections
.PP
An active connection to a named socket is made by the \fIconnect\fP call:
E 7
I 7
the call will wait for a connection unless
non-blocking I/O has been enabled (see section
.Xr 1.5.4 ).
.Sh 4 "Making connections
.LP
An active connection to a named socket is made by the
.Fn connect
call:
E 7
.DS
I 7
.Fd connect 3 "initiate a connection on a socket
E 7
connect(s, name, namelen);
D 3
int s; caddr_t name; int namelen;
E 3
I 3
int s; struct sockaddr *name; int namelen;
E 3
.DE
I 3
Although datagram sockets do not establish connections,
D 7
the \fIconnect\fP call may be used with such sockets
E 7
I 7
the
.Fn connect
call may be used with such sockets
E 7
to create an \fIassociation\fP with the foreign address.
D 7
The address is recorded for use in future \fIsend\fP calls,
which then need not supply destination addresses.
E 7
I 7
The address is recorded for use in future
.Fn send
calls, which then need not supply destination addresses.
E 7
Datagrams will be received only from that peer,
and asynchronous error reports may be received.
E 3
.PP
It is also possible to create connected pairs of sockets without
using the domain's name space to rendezvous; this is done with the
D 7
\fIsocketpair\fP call\(dg:
E 7
I 7
.Fn socketpair
call\(dg:
E 7
.FS
D 2
\(dg 4.2BSD supports \fIsocketpair\fP creation only in the ``unix''
E 2
I 2
D 7
\(dg 4.3BSD supports \fIsocketpair\fP creation only in the ``unix''
E 2
communication domain.
E 7
I 7
\(dg 4.4BSD supports
.Fn socketpair
D 8
creation only in the ``UNIX'' communication domain.
E 8
I 8
creation only in the PF_LOCAL communication domain.
E 8
E 7
.FE
.DS
I 7
.Fd socketpair 4 "create a pair of connected sockets
E 7
D 3
socketpair(d, type, protocol, sv);
int d, type, protocol; result int sv[2];
E 3
I 3
socketpair(domain, type, protocol, sv);
int domain, type, protocol; result int sv[2];
E 3
.DE
Here the returned \fIsv\fP descriptors correspond to those obtained with
D 7
\fIaccept\fP and \fIconnect\fP.
.PP
The call
E 7
I 7
.Fn accept
and
.Fn connect .
.LP
The call:
E 7
.DS
I 7
.Fd pipe 1 "create descriptor pair for interprocess communication
E 7
D 9
pipe(pv)
E 9
I 9
pipe(pv);
E 9
result int pv[2];
.DE
D 8
creates a pair of SOCK_STREAM sockets in the UNIX domain,
E 8
I 8
creates a pair of SOCK_STREAM sockets in the PF_LOCAL domain,
E 8
D 4
with pv[0] only writeable and pv[1] only readable.
E 4
I 4
with pv[0] only writable and pv[1] only readable.
E 4
D 7
.NH 4
Sending and receiving data
.PP
E 7
I 7
.Sh 4 "Sending and receiving data
.LP
E 7
Messages may be sent from a socket by:
.DS
D 7
cc = sendto(s, buf, len, flags, to, tolen);
result int cc; int s; caddr_t buf; int len, flags; caddr_t to; int tolen;
E 7
I 7
.Fd sendto 6 "send a message from a socket
cc = sendto(s, msg, len, flags, to, tolen);
result int cc; int s; void *msg; size_t len;
int flags; struct sockaddr *to; int tolen;
E 7
.DE
if the socket is not connected or:
.DS
D 7
cc = send(s, buf, len, flags);
result int cc; int s; caddr_t buf; int len, flags;
E 7
I 7
.Fd send 4 "send a message from a socket
cc = send(s, msg, len, flags);
result int cc; int s; void *msg; size_t len; int flags;
E 7
.DE
if the socket is connected.
The corresponding receive primitives are:
.DS
I 7
.Fd recvfrom 6 "receive a message from a socket
E 7
msglen = recvfrom(s, buf, len, flags, from, fromlenaddr);
D 7
result int msglen; int s; result caddr_t buf; int len, flags;
result caddr_t from; result int *fromlenaddr;
E 7
I 7
result int msglen; int s; result void *buf; size_t len; int flags;
result struct sockaddr *from; result int *fromlenaddr;
E 7
.DE
D 7
and
E 7
I 7
and:
E 7
.DS
I 7
.Fd recv 4 "receive a message from a socket
E 7
msglen = recv(s, buf, len, flags);
D 7
result int msglen; int s; result caddr_t buf; int len, flags;
E 7
I 7
result int msglen; int s; result void *buf; size_t len; int flags;
E 7
.DE
.PP
In the unconnected case,
the parameters \fIto\fP and \fItolen\fP
specify the destination or source of the message, while
the \fIfrom\fP parameter stores the source of the message,
and \fI*fromlenaddr\fP initially gives the size of the \fIfrom\fP
buffer and is updated to reflect the true length of the \fIfrom\fP
address.
.PP
All calls cause the message to be received in or sent from
the message buffer of length \fIlen\fP bytes, starting at address \fIbuf\fP.
The \fIflags\fP specify
D 7
peeking at a message without reading it or sending or receiving
high-priority out-of-band messages, as follows:
E 7
I 7
peeking at a message without reading it, sending or receiving
high-priority out-of-band messages, or other
special requests as follows:
E 7
.DS
D 7
._d
#define	MSG_PEEK	0x1	/* peek at incoming message */
#define	MSG_OOB	0x2	/* process out-of-band data */
E 7
I 7
.TS
l l.
MSG_OOB	/* process out-of-band data */
MSG_PEEK	/* peek at incoming message */
MSG_DONTROUTE	/* send without using routing tables */
MSG_EOR	/* data completes record */
MSG_TRUNC	/* data discarded before delivery */
MSG_CTRUNC	/* control data lost before delivery */
MSG_WAITALL	/* wait for full request or error */
MSG_DONTWAIT	/* this message should be nonblocking */
.TE
E 7
.DE
D 7
.NH 4
Scatter/gather and exchanging access rights
E 7
I 7
.Sh 4 "Scatter/gather and exchanging access rights
E 7
.PP
D 7
It is possible scatter and gather data and to exchange access rights
E 7
I 7
It is possible to scatter and gather data and to exchange access rights
E 7
with messages.  When either of these operations is involved,
the number of parameters to the call becomes large.
D 3
Thus the system defines a message header structure, in <sys/socket.h>,
E 3
I 3
D 7
Thus the system defines a message header structure, in \fI<sys/socket.h>\fP,
E 7
I 7
Thus, the system defines a message header structure, in \fI<sys/socket.h>\fP,
E 7
E 3
which can be
used to conveniently contain the parameters to the calls:
.DS
D 7
.if t .ta .5i 1.25i 2i 2.7i
.if n ._f
E 7
I 7
.TS
l s s s
l l l l.
E 7
struct msghdr {
D 7
	caddr_t	msg_name;		/* optional address */
	int	msg_namelen;	/* size of address */
	struct	iov *msg_iov;	/* scatter/gather array */
	int	msg_iovlen;		/* # elements in msg_iov */
	caddr_t	msg_accrights;	/* access rights sent/received */
	int	msg_accrightslen;	/* size of msg_accrights */
E 7
I 7
	caddr_t	msg_name;	/* optional address */
	u_int	msg_namelen;	/* size of address */
	struct	iovec *msg_iov;	/* scatter/gather array */
	u_int	msg_iovlen;	/* # elements in msg_iov */
	caddr_t	msg_control;	/* ancillary data */
	u_int	msg_controllen;	/* ancillary data buffer len */
	int	msg_flags;	/* flags on received message */
E 7
};
I 7
.TE
E 7
.DE
Here \fImsg_name\fP and \fImsg_namelen\fP specify the source or destination
address if the socket is unconnected; \fImsg_name\fP may be given as
a null pointer if no names are desired or required.
The \fImsg_iov\fP and \fImsg_iovlen\fP describe the scatter/gather
D 7
locations, as described in section 2.1.3.
E 7
I 7
locations, as described in section
.Xr 2.1.1 .
The data in the \fImsg_control\fP buffer is composed of
an array of variable length messages
used for additional information with or about a datagram
not expressible by flags.  The format is a sequence
D 8
of message elements headed by cmsghdr structures:
E 8
I 8
of message elements headed by \fIcmsghdr\fP structures:
E 8
.DS
.TS
l s s s
l l l l.
struct cmsghdr {
	u_int	cmsg_len;	/* data byte count, including hdr */
	int	cmsg_level;	/* originating protocol */
	int	cmsg_type;	/* protocol-specific type */
D 10
	u_char	cmsg_data[];	/* variable length type specific data */
E 10
I 10
	u_char	cmsg_data[\|];	/* variable length type specific data */
E 10
};
.TE
.DE
I 8
The following macros are provided for use with the \fImsg_control\fP buffer:
.DS
.TS
l l.
CMSG_FIRSTHDR(mhdr)	/* given msghdr, return first cmsghdr */
CMSG_NXTHDR(mhdr, cmsg)	/* given msghdr and cmsghdr, return next cmsghdr */
CMSG_DATA(cmsg)	/* given cmsghdr, return associated data pointer */
.TE
.DE
E 8
E 7
Access rights to be sent along with the message are specified
D 7
in \fImsg_accrights\fP, which has length \fImsg_accrightslen\fP.
In the ``unix'' domain these are an array of integer descriptors,
E 7
I 7
in one of these
D 8
\fIcmsghdr\fP structures, with type SCM_RIGHTS.
In the ``UNIX'' domain these are an array of integer descriptors,
E 7
taken from the sending process and duplicated in the receiver.
E 8
I 8
\fIcmsghdr\fP structures, with level SOL_SOCKET and type SCM_RIGHTS.
In the PF_LOCAL domain these are an array of integer descriptors,
copied from the sending process and duplicated in the receiver.
I 11
.ne 1i
E 11
E 8
D 7
.PP
This structure is used in the operations \fIsendmsg\fP and \fIrecvmsg\fP:
E 7
I 7
.LP
This structure is used in the operations
.Fn sendmsg
and
.Fn recvmsg :
E 7
.DS
I 7
.Fd sendmsg 3 "send a message from a socket
E 7
sendmsg(s, msg, flags);
int s; struct msghdr *msg; int flags;
D 7

E 7
I 7
.DE
.DS
.Fd recvmsg 3 "receive a message from a socket
E 7
msglen = recvmsg(s, msg, flags);
result int msglen; int s; result struct msghdr *msg; int flags;
.DE
D 7
.NH 4
Using read and write with sockets
E 7
I 7
.Sh 4 "Using read and write with sockets
E 7
.PP
D 7
The normal UNIX \fIread\fP and \fIwrite\fP calls may be
applied to connected sockets and translated into \fIsend\fP and \fIreceive\fP
E 7
I 7
The normal
.Fn read
and
.Fn write
calls may be applied to connected sockets and translated into
.Fn send
and
.Fn receive
E 7
calls from or to a single area of memory and discarding any rights
received.  A process may operate on a virtual circuit socket, a terminal
or a file with blocking or non-blocking input/output
operations without distinguishing the descriptor type.
D 7
.NH 4
Shutting down halves of full-duplex connections
E 7
I 7
.Sh 4 "Shutting down halves of full-duplex connections
E 7
.PP
A process that has a full-duplex socket such as a virtual circuit
and no longer wishes to read from or write to this socket can
give the call:
.DS
I 7
.Fd shutdown 2 "shut down part of a full-duplex connection
E 7
shutdown(s, direction);
int s, direction;
.DE
where \fIdirection\fP is 0 to not read further, 1 to not
write further, or 2 to completely shut the connection down.
I 3
If the underlying protocol supports unidirectional or bidirectional shutdown,
this indication will be passed to the peer.
For example, a shutdown for writing might produce an end-of-file
condition at the remote end.
E 3
D 7
.NH 4
Socket and protocol options
E 7
I 7
.Sh 4 "Socket and protocol options
E 7
.PP
Sockets, and their underlying communication protocols, may
support \fIoptions\fP.  These options may be used to manipulate
D 3
implementation specific or non-standard facilities. 
E 3
I 3
implementation- or protocol-specific facilities. 
E 3
D 7
The \fIgetsockopt\fP
and \fIsetsockopt\fP calls are used to control options:
E 7
I 7
The
.Fn getsockopt
and
.Fn setsockopt
calls are used to control options:
E 7
.DS
I 7
.Fd getsockopt 5 "get options on socket
E 7
D 9
getsockopt(s, level, optname, optval, optlen)
E 9
I 9
getsockopt(s, level, optname, optval, optlen);
E 9
D 7
int s, level, optname; result caddr_t optval; result int *optlen;

E 7
I 7
int s, level, optname; result void *optval; result int *optlen;
.DE
.DS
.Fd setsockopt 5 "set options on socket
E 7
D 9
setsockopt(s, level, optname, optval, optlen)
E 9
I 9
setsockopt(s, level, optname, optval, optlen);
E 9
D 7
int s, level, optname; caddr_t optval; int optlen;
E 7
I 7
int s, level, optname; void *optval; int optlen;
E 7
.DE
The option \fIoptname\fP is interpreted at the indicated
protocol \fIlevel\fP for socket \fIs\fP.  If a value is specified
with \fIoptval\fP and \fIoptlen\fP, it is interpreted by
the software operating at the specified \fIlevel\fP.  The \fIlevel\fP
SOL_SOCKET is reserved to indicate options maintained
by the socket facilities.  Other \fIlevel\fP values indicate
a particular protocol which is to act on the option request;
D 8
these values are normally interpreted as a ``protocol number''.
D 7
.NH 3
UNIX domain
E 7
I 7
.Sh 3 "UNIX domain
E 8
I 8
these values are normally interpreted as a ``protocol number''
within the protocol family.
.Sh 3 "PF_LOCAL domain
E 8
E 7
.PP
D 8
This section describes briefly the properties of the UNIX communications
domain.
E 8
I 8
This section describes briefly the properties of the PF_LOCAL (``UNIX'')
communications domain.
E 8
D 7
.NH 4
Types of sockets
E 7
I 7
.Sh 4 "Types of sockets
E 7
.PP
D 8
In the UNIX domain,
E 8
I 8
In the local domain,
E 8
the SOCK_STREAM abstraction provides pipe-like
facilities, while SOCK_DGRAM provides (usually)
reliable message-style communications.
D 7
.NH 4
Naming
E 7
I 7
.Sh 4 "Naming
E 7
.PP
D 7
Socket names are strings and may appear in the UNIX file
system name space through portals\(dg.
.FS
D 2
\(dg The 4.2BSD implementation of the UNIX domain embeds
E 2
I 2
\(dg The 4.3BSD implementation of the UNIX domain embeds
E 2
D 3
bound sockets in the UNIX file system name space; this
is a side effect of the implementation.
E 3
I 3
bound sockets in the UNIX file system name space;
this may change in future releases.
E 3
.FE
.NH 4
Access rights transmission
E 7
I 7
Socket names are strings and may appear in the filesystem
name space.
.Sh 4 "Access rights transmission
E 7
.PP
D 7
The ability to pass UNIX descriptors with messages in this domain
E 7
I 7
The ability to pass descriptors with messages in this domain
E 7
allows migration of service within the system and allows
user processes to be used in building system facilities.
D 7
.NH 3
INTERNET domain
E 7
I 7
.Sh 3 "INTERNET domain
E 7
.PP
D 3
This section describes briefly how the INTERNET domain is
E 3
I 3
This section describes briefly how the Internet domain is
E 3
mapped to the model described in this section.  More
information will be found in the document describing the
D 2
network implementation in 4.2BSD.
E 2
I 2
D 7
network implementation in 4.3BSD.
E 2
.NH 4
Socket types and protocols
E 7
I 7
network implementation in 4.4BSD (SMM:18).
.Sh 4 "Socket types and protocols
E 7
.PP
D 3
SOCK_STREAM is supported by the INTERNET TCP protocol;
SOCK_DGRAM by the UDP protocol.  The SOCK_SEQPACKET
has no direct INTERNET family analogue; a protocol
E 3
I 3
SOCK_STREAM is supported by the Internet TCP protocol;
SOCK_DGRAM by the UDP protocol.
Each is layered atop the transport-level Internet Protocol (IP).
The Internet Control Message Protocol is implemented atop/beside IP
and is accessible via a raw socket.
The SOCK_SEQPACKET
has no direct Internet family analogue; a protocol
E 3
based on one from the XEROX NS family and layered on
top of IP could be implemented to fill this gap.
D 7
.NH 4
Socket naming
E 7
I 7
.Sh 4 "Socket naming
E 7
.PP
D 3
Sockets in the INTERNET domain have names composed of the 32 bit
internet address, and a 16 bit port number.
E 3
I 3
D 7
Sockets in the Internet domain have names composed of the 32 bit
Internet address, and a 16 bit port number.
E 7
I 7
D 9
Sockets in the Internet domain have names composed of the 32-bit
Internet address, and a 16-bit port number.
E 9
I 9
Sockets in the Internet domain have names composed of a 32-bit
Internet address and a 16-bit port number.
E 9
E 7
E 3
Options may be used to
D 3
provide source routing for the address, security options,
or additional address for subnets of INTERNET for which the basic 32 bit
addresses are insufficient.
E 3
I 3
provide IP source routing or security options.
The 32-bit address is composed of network and host parts;
the network part is variable in size and is frequency encoded.
The host part may optionally be interpreted as a subnet field
D 9
plus the host on subnet; this is is enabled by setting a network address
E 9
I 9
plus the host on the subnet; this is is enabled by setting a network address
E 9
mask at boot time.
E 3
D 7
.NH 4
Access rights transmission
E 7
I 7
.Sh 4 "Access rights transmission
E 7
.PP
D 3
No access rights transmission facilities are provided in the INTERNET domain.
E 3
I 3
No access rights transmission facilities are provided in the Internet domain.
E 3
D 7
.NH 4
Raw access
E 7
I 7
.Sh 4 "Raw access
E 7
.PP
D 3
The INTERNET domain allows the super-user access to the raw facilities
of the various network interfaces and the various internal layers
of the protocol implementation.  This allows administrative and debugging
functions to occur.  These interfaces are modeled as SOCK_RAW sockets.
E 3
I 3
The Internet domain allows the super-user access to the raw facilities
of IP.
These interfaces are modeled as SOCK_RAW sockets.
Each raw socket is associated with one IP protocol number,
and receives all traffic received for that protocol.
D 7
This allows administrative and debugging
E 7
I 7
This approach allows administrative and debugging
E 7
functions to occur,
and enables user-level implementations of special-purpose protocols
such as inter-gateway routing protocols.
E 3
E 1
