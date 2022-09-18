h53550
s 00002/00002/00086
d D 8.1 93/06/08 14:01:19 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00013/00084
d D 6.4 93/06/06 12:09:37 mckusick 4 3
c crude update for 4.4BSD
e
s 00004/00003/00093
d D 6.3 91/04/17 11:35:08 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00095
d D 6.2 86/06/03 20:57:57 mckusick 2 1
c eliminate widow
e
s 00096/00000/00000
d D 6.1 86/06/03 18:07:01 karels 1 0
c 4.3 version
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 3
I 3
D 5
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1983, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 3
.\"
.\"	%W% (Berkeley) %G%
.\"
.\".ds RH "Network configuration options
.bp
.LG
.B
.ce
APPENDIX E. NETWORK CONFIGURATION OPTIONS
.sp
.R
.NL
.PP
D 2
For the most part, the network support in the kernel is self-configuring
E 2
I 2
The network support in the kernel is self-configuring
E 2
according to the protocol support options (INET and NS) and the network
hardware discovered during autoconfiguration.
There are several changes that may be made to customize network behavior
due to local restrictions.
Within the Internet protocol routines, the following options
set in the system configuration file are supported:
.IP \fBGATEWAY\fP
.br
The machine is to be used as a gateway.
This option currently makes only minor changes.
First, the size of the network routing hash table is increased.
Secondly, machines that have only a single hardware network interface
will not forward IP packets; without this option, they will also refrain
from sending any error indication to the source of unforwardable packets.
Gateways with only a single interface are assumed to have missing
or broken interfaces, and will return ICMP unreachable errors to hosts
sending them packets to be forwarded.
.IP \fBTCP_COMPAT_42\fP
.br
This option forces the system to limit its initial TCP sequence numbers
to positive numbers.
D 4
Without this option, 4.3BSD systems may have problems with TCP connections
E 4
I 4
Without this option, 4.4BSD systems may have problems with TCP connections
E 4
to 4.2BSD systems that connect but never transfer data.
D 4
The problem is a bug in the 4.2BSD TCP; this option should be used
during the period of conversion to 4.3BSD.
E 4
I 4
The problem is a bug in the 4.2BSD TCP.
E 4
.IP \fBIPFORWARDING\fP
.br
D 4
Normally, 4.3BSD machines with multiple network interfaces
E 4
I 4
Normally, 4.4BSD machines with multiple network interfaces
E 4
will forward IP packets received that should be resent to another host.
If the line ``options IPFORWARDING="0"'' is in the system configuration
file, IP packet forwarding will be disabled.
.IP \fBIPSENDREDIRECTS\fP
.br
D 4
When forwarding IP packets, 4.3BSD IP will note when a packet is forwarded
E 4
I 4
When forwarding IP packets, 4.4BSD IP will note when a packet is forwarded
E 4
using the same interface on which it arrived.
When this is noted, if the source machine is on the directly-attached
network, an ICMP redirect is sent to the source host.
If the packet was forwarded using a route to a host or to a subnet,
a host redirect is sent, otherwise a network redirect is sent.
The generation of redirects may be inhibited with the configuration
option ``options IPSENDREDIRECTS="0".''
.br
.IP \fBSUBNETSARELOCAL\fP
TCP calculates a maximum segment size to use for each connection,
and sends no datagrams larger than that size.
This size will be no larger than that supported on the outgoing
interface.
Furthermore, if the destination is not on the local network,
the size will be no larger than 576 bytes.
For this test, other subnets of a directly-connected subnetted
network are considered to be local unless the line
``options SUBNETSARELOCAL="0"'' is used in the system configuration file.
D 4
.IP \fBCOMPAT_42\fP
.br
This option, intended as a catchall for 4.2BSD compatibility options,
has only a single function thus far.
It disables the checking of UDP input packet checksums.
As the calculation of UDP packet checksums was incorrect in 4.2BSD,
this option allows a 4.3BSD system to receive UDP packets from
a 4.2BSD system.
E 4
.LP
The following options are supported by the Xerox NS protocols:
.IP \fBNSIP\fP
.br
This option allows NS IDP datagrams to be encapsulated in Internet IP
packets for transmission to a collaborating NSIP host.
This may be used to pass IDP packets through IP-only link layer networks.
See
.IR nsip (4P)
for details.
.IP \fBTHREEWAYSHAKE\fP
.br
The NS Sequenced Packet Protocol does not require a three-way handshake
before considering a connection to be in the established state.
(A three-way handshake consists of a connection request, an acknowledgement
of the request along with a symmetrical opening indication,
and then an acknowledgement of the reciprocal opening packet.)
This option forces a three-way handshake before data may be transmitted
on Sequenced Packet sockets.
E 1
