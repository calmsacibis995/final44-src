.nr H2 1
.ds RH "Protocol/network-interface
.NH
\s+2Protocol/network-interface interface\s0
.PP
The lowest layer in the set of protocols which comprise a
protocol family must interface itself to one or more network
interfaces in order to transmit and receive
packets.  It is assumed that
any routing decisions have been made before handing a packet
to a network interface, in fact this is absolutely necessary
in order to locate any interface at all (unless, of course,
one uses a single ``hardwired'' interface).  There are two
cases to be concerned with, transmission of a packet,
and receipt of a packet; each will be considered separately.
.NH 2
Packet transmission
.PP
Assuming a protocol has a handle on an interface, \fIifp\fP,
a (struct ifnet *),
it transmits a fully formatted packet with the following call,
.DS
error = (*ifp->if_output)(ifp, m, dst)
int error; struct ifnet *ifp; struct mbuf *m; struct sockaddr *dst;
.DE
The output routine for the network interface transmits the packet
\fIm\fP to the \fIdst\fP address, or returns an error indication
(a UNIX error number).  In reality transmission may
not be immediate, or successful; normally the output
routine simply queues the packet on its send queue and primes
an interrupt driven routine to actually transmit the packet.
For unreliable mediums, such as the Ethernet, ``successful''
transmission simply means the packet has been placed on the cable
without a collision.  On the other hand, an 1822 interface guarantees
proper delivery or an error indication for each message transmitted.
The model employed in the networking system attaches no promises
of delivery to the packets handed to a network interface, and thus
corresponds more closely to the Ethernet.  Errors returned by the
output routine are normally trivial in nature (no buffer space, 
address format not handled, etc.).
.NH 2
Packet reception
.PP
Each protocol family must have one or more ``lowest level'' protocols.
These protocols deal with internetwork addressing and are responsible
for the delivery of incoming packets to the proper protocol processing
modules.  In the PUP model [Boggs78] these protocols are termed Level
1 protocols,
in the ISO model, network layer protocols.  In our system each such
protocol module has an input packet queue assigned to it.  Incoming
packets received by a network interface are queued up for the protocol
module and a VAX software interrupt is posted to initiate processing.  
.PP
Three macros are available for queueing and dequeueing packets,
.IP "IF_ENQUEUE(ifq, m)"
.br
This places the packet \fIm\fP at the tail of the queue \fIifq\fP.
.IP "IF_DEQUEUE(ifq, m)"
.br
This places a pointer to the packet at the head of queue \fIifq\fP 
in \fIm\fP.  A zero value will be returned in \fIm\fP if the queue
is empty.
.IP "IF_PREPEND(ifq, m)"
.br
This places the packet \fIm\fP at the head of the queue \fIifq\fP.
.PP
Each queue has a maximum length associated with it as a simple form
of congestion control.  The macro IF_QFULL(ifq) returns 1 if the queue
is filled, in which case the macro IF_DROP(ifq) should be used to
bump a count of the number of packets dropped and the offending
packet dropped.  For example, the following code fragment is commonly
found in a network interface's input routine,
.DS 
._f
if (IF_QFULL(inq)) {
	IF_DROP(inq);
	m_freem(m);
} else
	IF_ENQUEUE(inq, m);
.DE
.ds RH "Gateways and routing
.sp 2
