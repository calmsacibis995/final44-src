h32463
s 00002/00002/00191
d D 8.1 93/06/08 16:52:37 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00192
d D 6.5 91/04/17 12:06:16 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00189
d D 6.4 89/03/07 10:53:21 bostic 5 4
c install Berkeley specific copyright, for networking release
e
s 00002/00001/00190
d D 6.3 86/06/05 09:52:57 karels 4 3
c formatting glitches
e
s 00038/00042/00153
d D 6.2 86/06/04 23:53:56 karels 3 2
c updates for 4.3
e
s 00000/00000/00195
d D 6.1 86/05/26 13:26:51 mckusick 2 1
c 4.3BSD beta release document
e
s 00195/00000/00000
d D 5.1 86/05/26 13:26:45 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1983 Regents of the University of California.
E 3
I 3
D 5
.\" Copyright (c) 1983,1986 Regents of the University of California.
E 3
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 7
.\" Copyright (c) 1983, 1986 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1983, 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 7
.\"
D 6
.\" Redistribution and use in source and binary forms are permitted
.\" provided that the above copyright notice and this paragraph are
.\" duplicated in all such forms and that any documentation,
.\" advertising materials, and other materials related to such
.\" distribution and use acknowledge that the software was developed
.\" by the University of California, Berkeley.  The name of the
.\" University may not be used to endorse or promote products derived
.\" from this software without specific prior written permission.
.\" THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
.\" IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
.\" WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
.\" %sccs.include.redist.roff%
E 6
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
.nr H2 1
D 3
.ds RH "Gateways and routing
E 3
I 3
.\".ds RH "Gateways and routing
I 4
.br
.ne 2i
E 4
E 3
.NH
\s+2Gateways and routing issues\s0
.PP
The system has been designed with the expectation that it will
be used in an internetwork environment.  The ``canonical''
environment was envisioned to be a collection of local area
networks connected at one or more points through hosts with
multiple network interfaces (one on each local area network),
and possibly a connection to a long haul network (for example,
the ARPANET).  In such an environment, issues of
gatewaying and packet routing become very important.  Certain
of these issues, such as congestion
control, have been handled in a simplistic manner or specifically
not addressed.
Instead, where possible, the network system
attempts to provide simple mechanisms upon which more involved
policies may be implemented.  As some of these problems become
better understood, the solutions developed will be incorporated
into the system.
.PP
This section will describe the facilities provided for packet
routing.  The simplistic mechanisms provided for congestion
control are described in chapter 12.
.NH 2
Routing tables
.PP
The network system maintains a set of routing tables for
selecting a network interface to use in delivering a 
packet to its destination.  These tables are of the form:
.DS
D 3
._f
E 3
I 3
.ta \w'struct   'u +\w'u_long   'u +\w'sockaddr rt_gateway;    'u
E 3
struct rtentry {
	u_long	rt_hash;		/* hash key for lookups */
	struct	sockaddr rt_dst;	/* destination net or host */
	struct	sockaddr rt_gateway;	/* forwarding agent */
	short	rt_flags;		/* see below */
	short	rt_refcnt;		/* no. of references to structure */
	u_long	rt_use;			/* packets sent using route */
	struct	ifnet *rt_ifp;		/* interface to give packet to */
};
.DE
.PP
The routing information is organized in two separate tables, one
for routes to a host and one for routes to a network.  The
distinction between hosts and networks is necessary so
that a single mechanism may be used
for both broadcast and multi-drop type networks, and
also for networks built from point-to-point links (e.g
DECnet [DEC80]).
.PP
Each table is organized as a hashed set of linked lists.
Two 32-bit hash values are calculated by routines defined for
each address family; one based on the destination being
a host, and one assuming the target is the network portion
of the address.  Each hash value is used to
locate a hash chain to search (by taking the value modulo the
hash table size) and the entire 32-bit value is then
used as a key in scanning the list of routes.  Lookups are
applied first to the routing
table for hosts, then to the routing table for networks.
If both lookups fail, a final lookup is made for a ``wildcard''
route (by convention, network 0).
I 3
The first appropriate route discovered is used.
E 3
By doing this, routes to a specific host on a network may be
present as well as routes to the network.  This also allows a
D 3
``fall back'' network route to be defined to an ``smart'' gateway
E 3
I 3
``fall back'' network route to be defined to a ``smart'' gateway
E 3
which may then perform more intelligent routing.
.PP
D 3
Each routing table entry contains a destination (who's at
the other end of the route), a gateway to send the packet
to, and various
flags which indicate the route's status and type (host or
E 3
I 3
Each routing table entry contains a destination (the desired final destination),
a gateway to which to send the packet,
and various flags which indicate the route's status and type (host or
E 3
network).  A count
D 3
of the number of packets sent using the route is kept for
use in deciding between multiple routes to the same destination
(see below), and a count of ``held references'' to the dynamically
allocated structure is maintained to insure memory reclamation
occurs only when the route is not in use.  Finally a pointer to the
E 3
I 3
of the number of packets sent using the route is kept, along
with a count of ``held references'' to the dynamically
allocated structure to insure that memory reclamation
occurs only when the route is not in use.  Finally, a pointer to the
E 3
a network interface is kept; packets sent using
the route should be handed to this interface.
.PP
Routes are typed in two ways: either as host or network, and as
``direct'' or ``indirect''.  The host/network
distinction determines how to compare the \fIrt_dst\fP field
during lookup.  If the route is to a network, only a packet's
destination network is compared to the \fIrt_dst\fP entry stored
in the table.  If the route is to a host, the addresses must
match bit for bit.
.PP
The distinction between ``direct'' and ``indirect'' routes indicates
whether the destination is directly connected to the source.
This is needed when performing local network encapsulation.  If
a packet is destined for a peer at a host or network which is
not directly connected to the source, the internetwork packet
header will
D 3
indicate the address of the eventual destination, while
the local network header will indicate the address of the intervening
E 3
I 3
contain the address of the eventual destination, while
the local network header will address the intervening
E 3
gateway.  Should the destination be directly connected, these addresses
are likely to be identical, or a mapping between the two exists.
D 3
The RTF_GATEWAY flag indicates the route is to an ``indirect''
gateway agent and the local network header should be filled in
from the \fIrt_gateway\fP field instead of \fIrt_dst\fP, or 
from the internetwork destination address.
E 3
I 3
The RTF_GATEWAY flag indicates that the route is to an ``indirect''
gateway agent, and that the local network header should be filled in
from the \fIrt_gateway\fP field instead of
from the final internetwork destination address.
E 3
.PP
D 3
It is assumed multiple routes to the same destination will not
be present unless they are deemed \fIequal\fP in cost (the
current routing policy process never installs multiple routes
to the same destination).
However, should multiple routes to the same destination exist,
a request for a route will return the ``least used'' route
based on the total number of packets sent along this route.
This can result in a ``ping-pong'' effect (alternate packets
taking alternate routes), unless protocols ``hold onto''
routes until they no longer find them useful;  either because
the destination has changed, or because the route is lossy.
E 3
I 3
It is assumed that multiple routes to the same destination will not
be present; only one of multiple routes, that most recently installed,
will be used.
E 3
.PP
Routing redirect control messages are used to dynamically
modify existing routing table entries as well as dynamically
create new routing table entries.  On hosts where exhaustive
routing information is too expensive to maintain (e.g. work
stations), the
combination of wildcard routing entries and routing redirect
messages can be used to provide a simple routing management
scheme without the use of a higher level policy process. 
I 3
Current connections may be rerouted after notification of the protocols
by means of their \fIpr_ctlinput\fP entries.
E 3
Statistics are kept by the routing table routines
on the use of routing redirect messages and their
affect on the routing tables.  These statistics may be viewed using
.IR netstat (1).
.PP
Status information other than routing redirect control messages
may be used in the future, but at present they are ignored.
Likewise, more intelligent ``metrics'' may be used to describe
routes in the future, possibly based on bandwidth and monetary
costs.
.NH 2
Routing table interface
.PP
A protocol accesses the routing tables through
three routines,
one to allocate a route, one to free a route, and one
to process a routing redirect control message.
The routine \fIrtalloc\fP performs route allocation; it is
D 3
called with a pointer to the following structure,
E 3
I 3
called with a pointer to the following structure containing
the desired destination:
E 3
.DS
._f
struct route {
	struct	rtentry *ro_rt;
	struct	sockaddr ro_dst;
};
.DE
The route returned is assumed ``held'' by the caller until
D 3
disposed of with an \fIrtfree\fP call.  Protocols which implement
E 3
I 3
released with an \fIrtfree\fP call.  Protocols which implement
E 3
virtual circuits, such as TCP, hold onto routes for the duration
of the circuit's lifetime, while connection-less protocols,
D 3
such as UDP, currently allocate and free routes on each transmission.
E 3
I 3
such as UDP, allocate and free routes whenever their destination address
changes.
E 3
.PP
The routine \fIrtredirect\fP is called to process a routing redirect
D 3
control message.  It is called with a destination address and 
the new gateway to that destination.  If a non-wildcard route
E 3
I 3
control message.  It is called with a destination address,
the new gateway to that destination, and the source of the redirect.
Redirects are accepted only from the current router for the destination.
If a non-wildcard route
E 3
exists to the destination, the gateway entry in the route is modified 
to point at the new gateway supplied.  Otherwise, a new routing
table entry is inserted reflecting the information supplied.  Routes
D 3
to interfaces and routes to gateways which are not directly accesible
E 3
I 3
to interfaces and routes to gateways which are not directly accessible
E 3
from the host are ignored.
.NH 2
User level routing policies
.PP
Routing policies implemented in user processes manipulate the
kernel routing tables through two \fIioctl\fP calls.  The
commands SIOCADDRT and SIOCDELRT add and delete routing entries,
respectively; the tables are read through the /dev/kmem device.
The decision to place policy decisions in a user process implies
D 3
routing table updates may lag a bit behind the identification of
E 3
I 3
that routing table updates may lag a bit behind the identification of
E 3
new routes, or the failure of existing routes, but this period
of instability is normally very small with proper implementation
of the routing process.  Advisory information, such as ICMP
error messages and IMP diagnostic messages, may be read from
raw sockets (described in the next section).
.PP
D 3
One routing policy process has already been implemented.  The
E 3
I 3
Several routing policy processes have already been implemented.  The
E 3
system standard
``routing daemon'' uses a variant of the Xerox NS Routing Information
D 3
Protocol [Xerox82] to maintain up to date routing tables in our local
E 3
I 3
Protocol [Xerox82] to maintain up-to-date routing tables in our local
E 3
environment.  Interaction with other existing routing protocols,
D 3
such as the Internet GGP (Gateway-Gateway Protocol), may be
E 3
I 3
such as the Internet EGP (Exterior Gateway Protocol), has been
E 3
accomplished using a similar process.
D 3
.ds RH "Raw sockets
.bp
E 3
I 3
D 4
'ne 2i
E 4
E 3
E 1
