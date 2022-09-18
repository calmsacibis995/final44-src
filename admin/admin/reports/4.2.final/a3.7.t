.nr H2 1
.ds RH "Socket/protocol interface
.NH
\s+2Socket/protocol interface\s0
.PP
The interface between the socket routines and the communication
protocols is through the \fIpr_usrreq\fP routine defined in the
protocol switch table.  The following requests to a protocol
module are possible:
.DS
._d
#define	PRU_ATTACH	0	/* attach protocol */
#define	PRU_DETACH	1	/* detach protocol */
#define	PRU_BIND	2	/* bind socket to address */
#define	PRU_LISTEN	3	/* listen for connection */
#define	PRU_CONNECT	4	/* establish connection to peer */
#define	PRU_ACCEPT	5	/* accept connection from peer */
#define	PRU_DISCONNECT	6	/* disconnect from peer */
#define	PRU_SHUTDOWN	7	/* won't send any more data */
#define	PRU_RCVD	8	/* have taken data; more room now */
#define	PRU_SEND	9	/* send this data */
#define	PRU_ABORT	10	/* abort (fast DISCONNECT, DETATCH) */
#define	PRU_CONTROL	11	/* control operations on protocol */
#define	PRU_SENSE	12	/* return status into m */
#define	PRU_RCVOOB	13	/* retrieve out of band data */
#define	PRU_SENDOOB	14	/* send out of band data */
#define	PRU_SOCKADDR	15	/* fetch socket's address */
#define	PRU_PEERADDR	16	/* fetch peer's address */
#define	PRU_CONNECT2	17	/* connect two sockets */
/* begin for protocols internal use */
#define	PRU_FASTTIMO	18	/* 200ms timeout */
#define	PRU_SLOWTIMO	19	/* 500ms timeout */
#define	PRU_PROTORCV	20	/* receive from below */
#define	PRU_PROTOSEND	21	/* send to below */
.DE
A call on the user request routine is of the form,
.DS
._f
error = (*protosw[].pr_usrreq)(up, req, m, addr, rights);
int error; struct socket *up; int req; struct mbuf *m, *rights; caddr_t addr;
.DE
The mbuf chain, \fIm\fP, and the address are optional parameters.
The \fIrights\fP parameter is an optional pointer to an mbuf
chain containing user specified capabilities (see the \fIsendmsg\fP
and \fIrecvmsg\fP system calls).  The protocol is responsible for
disposal of both mbuf chains.  A non-zero return value gives a
UNIX error number which should be passed to higher level software.
The following paragraphs describe each
of the requests possible.
.IP PRU_ATTACH
.br
When a protocol is bound to a socket (with the \fIsocket\fP
system call) the protocol module is called with this
request.  It is the responsibility of the protocol module to
allocate any resources necessary.
The ``attach'' request
will always precede any of the other requests, and should not
occur more than once.
.IP PRU_DETACH
.br
This is the antithesis of the attach request, and is used
at the time a socket is deleted.  The protocol module may
deallocate any resources assigned to the socket.
.IP PRU_BIND
.br
When a socket is initially created it has no address bound
to it.  This request indicates an address should be bound to
an existing socket.  The protocol module must verify the
requested address is valid and available for use.
.IP PRU_LISTEN
.br
The ``listen'' request indicates the user wishes to listen
for incoming connection requests on the associated socket.
The protocol module should perform any state changes needed
to carry out this request (if possible).  A ``listen'' request
always precedes a request to accept a connection.
.IP PRU_CONNECT
.br
The ``connect'' request indicates the user wants to a establish
an association.  The \fIaddr\fP parameter supplied describes
the peer to be connected to.  The effect of a connect request
may vary depending on the protocol.  Virtual circuit protocols,
such as TCP [Postel80b], use this request to initiate establishment of a
TCP connection.  Datagram protocols, such as UDP [Postel79], simply
record the peer's address in a private data structure and use
it to tag all outgoing packets.  There are no restrictions
on how many times a connect request may be used after an attach.
If a protocol supports the notion of \fImulti-casting\fP, it
is possible to use multiple connects to establish a multi-cast
group.  Alternatively, an association may be broken by a
PRU_DISCONNECT request, and a new association created with a
subsequent connect request; all without destroying and creating
a new socket.
.IP PRU_ACCEPT
.br
Following a successful PRU_LISTEN request and the arrival
of one or more connections, this request is made to
indicate the user
has accepted the first connection on the queue of
pending connections.  The protocol module should fill
in the supplied address buffer with the address of the
connected party.
.IP PRU_DISCONNECT
.br
Eliminate an association created with a PRU_CONNECT request.
.IP PRU_SHUTDOWN
.br
This call is used to indicate no more data will be sent and/or
received (the \fIaddr\fP parameter indicates the direction of
the shutdown, as encoded in the \fIsoshutdown\fP system call).
The protocol may, at its discretion, deallocate any data
structures related to the shutdown.
.IP PRU_RCVD
.br
This request is made only if the protocol entry in the protocol
switch table includes the PR_WANTRCVD flag.
When a user removes data from the receive queue this request
will be sent to the protocol module.  It may be used to trigger
acknowledgements, refresh windowing information, initiate
data transfer, etc.
.IP PRU_SEND
.br
Each user request to send data is translated into one or more
PRU_SEND requests (a protocol may indicate a single user
send request must be translated into a single PRU_SEND request by
specifying the PR_ATOMIC flag in its protocol description).
The data to be sent is presented to the protocol as a list of
mbufs and an address is, optionally, supplied in the \fIaddr\fP
parameter.  The protocol is responsible for preserving the data
in the socket's send queue if it is not able to send it immediately,
or if it may need it at some later time (e.g. for retransmission).
.IP PRU_ABORT
.br
This request indicates an abnormal termination of service.  The
protocol should delete any existing association(s).
.IP PRU_CONTROL
.br
The ``control'' request is generated when a user performs a
UNIX \fIioctl\fP system call on a socket (and the ioctl is not
intercepted by the socket routines).  It allows protocol-specific
operations to be provided outside the scope of the common socket
interface.  The \fIaddr\fP parameter contains a pointer to a static
kernel data area where relevant information may be obtained or returned.
The \fIm\fP parameter contains the actual \fIioctl\fP request code
(note the non-standard calling convention).
.IP PRU_SENSE
.br
The ``sense'' request is generated when the user makes an \fIfstat\fP
system call on a socket; it requests status of the associated socket. 
There currently is no common format for the status returned. 
Information which might be returned includes per-connection statistics,
protocol state, resources currently in use by the connection, the
optimal transfer size for the connection (based on windowing information
and maximum packet size).  The \fIaddr\fP parameter contains a pointer
to a static kernel data area where the status buffer should be placed.
.IP PRU_RCVOOB
.br
Any ``out-of-band'' data presently available is to be returned.  An
mbuf is passed in to the protocol module and the protocol
should either place
data in the mbuf or attach new mbufs to the one supplied if there is
insufficient space in the single mbuf.
.IP PRU_SENDOOB
.br
Like PRU_SEND, but for out-of-band data.
.IP PRU_SOCKADDR
.br
The local address of the socket is returned, if any is currently
bound to the it.  The address format (protocol specific) is returned
in the \fIaddr\fP parameter.
.IP PRU_PEERADDR
.br
The address of the peer to which the socket is connected is returned.
The socket must be in a SS_ISCONNECTED state for this request to
be made to the protocol.  The address format (protocol specific) is
returned in the \fIaddr\fP parameter.
.IP PRU_CONNECT2
.br
The protocol module is supplied two sockets and requested to
establish a connection between the two without binding any
addresses, if possible.  This call is used in implementing
the
.IR socketpair (2)
system call.
.PP
The following requests are used internally by the protocol modules
and are never generated by the socket routines.  In certain instances,
they are handed to the \fIpr_usrreq\fP routine solely for convenience
in tracing a protocol's operation (e.g. PRU_SLOWTIMO).
.IP PRU_FASTTIMO
.br
A ``fast timeout'' has occured.  This request is made when a timeout
occurs in the protocol's \fIpr_fastimo\fP routine.  The \fIaddr\fP
parameter indicates which timer expired.
.IP PRU_SLOWTIMO
.br
A ``slow timeout'' has occured.  This request is made when a timeout
occurs in the protocol's \fIpr_slowtimo\fP routine.  The \fIaddr\fP
parameter indicates which timer expired.
.IP PRU_PROTORCV
.br
This request is used in the protocol-protocol interface, not by the
routines.  It requests reception of data destined for the protocol and
not the user.  No protocols currently use this facility.
.IP PRU_PROTOSEND
.br
This request allows a protocol to send data destined for another
protocol module, not a user.  The details of how data is marked
``addressed to protocol'' instead of ``addressed to user'' are
left to the protocol modules.  No protocols currently use this facility.
.ds RH "Protocol/protocol interface
.sp 2
