.nr H2 1
.ds RH "Trailer protocols
.NH
\s+2Trailer protocols\s0
.PP
Core to core copies can be expensive.
Consequently, a great deal of effort was spent
in minimizing such operations.  The VAX architecture
provides virtual memory hardware organized in
page units.  To cut down on copy operations, data
is kept in page sized units on page-aligned
boundaries whenever possible.  This allows data
to be moved in memory simply by remapping the page
instead of copying.  The mbuf and network
interface routines perform page table manipulations
where needed, hiding the complexities of the VAX
virtual memory hardware from higher level code. 
.PP
Data enters the system in two ways: from the user,
or from the network (hardware interface).  When data
is copied from the user's address space
into the system it is deposited in pages (if sufficient
data is present to fill an entire page).
This encourages the user to transmit information in
messages which are a multiple of the system page size.
.PP
Unfortunately, performing a similar operation when taking
data from the network is very difficult.
Consider the format of an incoming packet.  A packet
usually contains a local network header followed by
one or more headers used by the high level protocols. 
Finally, the data, if any, follows these headers.  Since
the header information may be variable length, DMA'ing the eventual
data for the user into a page aligned area of
memory is impossible without
a priori knowledge of the format (e.g. supporting
only a single protocol header format).
.PP
To allow variable length header information to
be present and still ensure page alignment of data,
a special local network encapsulation may be used.
This encapsulation, termed a \fItrailer protocol\fP,
places the variable length header information after
the data.  A fixed size local network
header is then prepended to the resultant packet. 
The local network header contains the size of the
data portion, and a new \fItrailer protocol
header\fP, inserted before the variable length
information, contains the size of the variable length
header information.  The following trailer
protocol header is used to store information
regarding the variable length protocol header:
.DS
._f
struct {
	short	protocol;	/* original protocol no. */
	short	length;	/* length of trailer */
};
.DE
.PP
The processing of the trailer protocol is very
simple.  On output, the local network header indicates
a trailer encapsulation is being used.
The protocol identifier also includes an indication
of the number of data pages present (before the trailer
protocol header).  The trailer protocol header is
initialized to contain the actual protocol and
variable length header size, and appended to the data
along with the variable length header information.
.PP
On input, the interface routines identify the
trailer encapsulation
by the protocol type stored in the local network header,
then calculate the number of
pages of data to find the beginning of the trailer. 
The trailing information is copied into a separate
mbuf and linked to the front of the resultant packet.
.PP
Clearly, trailer protocols require cooperation between
source and destination.  In addition, they are normally
cost effective only when sizable packets are used.  The
current scheme works because the local network encapsulation
header is a fixed size, allowing DMA operations
to be performed at a known offset from the first data page
being received.  Should the local network header be
variable length this scheme fails. 
.PP
Statistics collected indicate as much as 200Kb/s
can be gained by using a trailer protocol with
1Kbyte packets.  The average size of the variable
length header was 40 bytes (the size of a
minimal TCP/IP packet header).  If hardware
supports larger sized packets, even greater gains
may be realized.
.ds LH "Final Report
.ds RH References
.bp
