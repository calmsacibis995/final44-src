.nr H2 1
.ds RH "Out of band data
.NH
\s+2Out of band data\s0
.PP
Out of band data is a facility peculiar to the stream socket
abstraction defined.  Little agreement appears to exist as
to what its semantics should be.  TCP defines the notion of
``urgent data'' as in-line, while the NBS protocols [Burruss81]
and numerous others provide a fully independent logical
transmission channel along which out of band data is to be
sent.
In addition, the amount of the data which may be sent as an out
of band message varies from protocol to protocol; everything
from 1 bit to 16 bytes or more.
.PP
A stream socket's notion of out of band data has been defined
as the lowest reasonable common denominator (at least reasonable
in our minds);
clearly this is subject to debate.  Out of band data is expected
to be transmitted out of the normal sequencing and flow control
constraints of the data stream.  A minimum of 1 byte of out of
band data and one outstanding out of band message are expected to
be supported by the protocol supporting a stream socket.
It is a protocols perogative to support larger sized messages, or
more than one outstanding out of band message at a time.
.PP
Out of band data is maintained by the protocol and usually not
stored in the socket's send queue.  The PRU_SENDOOB and PRU_RCVOOB
requests to the \fIpr_usrreq\fP routine are used in sending and
receiving data.
.ds RH "Trailer protocols
.sp 2
