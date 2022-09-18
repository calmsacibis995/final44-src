h61866
s 00002/00002/00138
d D 8.1 93/06/08 16:52:31 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00139
d D 6.6 91/04/17 12:06:14 bostic 7 6
c new copyright; att/bsd/shared
e
s 00014/00003/00136
d D 6.5 89/03/07 10:53:17 bostic 6 5
c install Berkeley specific copyright, for networking release
e
s 00001/00001/00138
d D 6.4 86/06/05 10:05:36 karels 5 4
c screwup
e
s 00002/00001/00137
d D 6.3 86/06/05 09:52:42 karels 4 3
c formatting glitches
e
s 00053/00033/00085
d D 6.2 86/06/04 23:53:45 karels 3 2
c updates for 4.3
e
s 00000/00000/00118
d D 6.1 86/05/26 13:26:24 mckusick 2 1
c 4.3BSD beta release document
e
s 00118/00000/00000
d D 5.1 86/05/26 13:26:17 mckusick 1 0
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
D 6
.\" Copyright (c) 1983,1986 Regents of the University of California.
E 3
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 6
I 6
D 8
.\" Copyright (c) 1983, 1986 The Regents of the University of California.
.\" All rights reserved.
E 8
I 8
.\" Copyright (c) 1983, 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 8
.\"
D 7
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
E 7
I 7
.\" %sccs.include.redist.roff%
E 7
E 6
.\"
.\"	%W% (Berkeley) %G%
.\"
.nr H2 1
D 3
.ds RH "Protocol/protocol interface
E 3
I 3
.\".ds RH "Protocol/protocol interface
I 4
.br
.ne 2i
E 4
E 3
.NH
\s+2Protocol/protocol interface\s0
.PP
The interface between protocol modules is through the \fIpr_usrreq\fP,
\fIpr_input\fP, \fIpr_output\fP, \fIpr_ctlinput\fP, and
\fIpr_ctloutput\fP routines.  The calling conventions for all
but the \fIpr_usrreq\fP routine are expected to be specific to
the protocol
modules and are not guaranteed to be consistent across protocol
families.  We
will examine the conventions used for some of the Internet
protocols in this section as an example.
.NH 2
pr_output
.PP
The Internet protocol UDP uses the convention,
.DS
error = udp_output(inp, m);
int error; struct inpcb *inp; struct mbuf *m;
.DE
D 3
where the \fIinp\fP, ``\fIin\fPternet
\fIp\fProtocol \fIc\fPontrol \fIb\fPlock'',
E 3
I 3
where the \fIinp\fP, ``\fIin\fP\^ternet
\fIp\fP\^rotocol \fIc\fP\^ontrol \fIb\fP\^lock'',
E 3
passed between modules conveys per connection state information, and
the mbuf chain contains the data to be sent.  UDP
performs consistency checks, appends its header, calculates a
D 3
checksum, etc. before passing the packet on to the IP module:
E 3
I 3
checksum, etc. before passing the packet on.
UDP is based on the Internet Protocol, IP [Postel81a], as its transport.
UDP passes a packet to the IP module for output as follows:
E 3
.DS
D 3
error = ip_output(m, opt, ro, allowbroadcast);
int error; struct mbuf *m, *opt; struct route *ro; int allowbroadcast;
E 3
I 3
error = ip_output(m, opt, ro, flags);
int error; struct mbuf *m, *opt; struct route *ro; int flags;
E 3
.DE
.PP
The call to IP's output routine is more complicated than that for
UDP, as befits the additional work the IP module must do.
The \fIm\fP parameter is the data to be sent, and the \fIopt\fP
parameter is an optional list of IP options which should
be placed in the IP packet header.  The \fIro\fP parameter is
is used in making routing decisions (and passing them back to the
D 3
caller).  The
final parameter, \fIallowbroadcast\fP is a flag indicating if the
user is allowed to transmit a broadcast packet.  This may
E 3
I 3
caller for use in subsequent calls).  The
final parameter, \fIflags\fP contains flags indicating whether the
user is allowed to transmit a broadcast packet
and if routing is to be performed.  The broadcast flag may
E 3
be inconsequential if the underlying hardware does not support the
notion of broadcasting.
.PP
All output routines return 0 on success and a UNIX error number
D 3
if a failure occured which could be immediately detected
E 3
I 3
if a failure occurred which could be detected immediately
E 3
(no buffer space available, no route to destination, etc.).
.NH 2
pr_input
.PP
Both UDP and TCP use the following calling convention,
.DS
D 3
(void) (*protosw[].pr_input)(m);
struct mbuf *m;
E 3
I 3
(void) (*protosw[].pr_input)(m, ifp);
struct mbuf *m; struct ifnet *ifp;
E 3
.DE
Each mbuf list passed is a single packet to be processed by
the protocol module.
I 3
The interface from which the packet was received is passed as the second
parameter.
E 3
.PP
The IP input routine is a VAX software interrupt level routine,
and so is not called with any parameters.  It instead communicates
with network interfaces through a queue, \fIipintrq\fP, which is
identical in structure to the queues used by the network interfaces
for storing packets awaiting transmission.
I 3
The software interrupt is enabled by the network interfaces
when they place input data on the input queue.
E 3
.NH 2
pr_ctlinput
.PP
This routine is used to convey ``control'' information to a
protocol module (i.e. information which might be passed to the
D 3
user, but is not data).  This routine, and the \fIpr_ctloutput\fP
routine, have not been extensively developed, and thus suffer
from a ``clumsiness'' that can only be improved as more demands
are placed on it.
E 3
I 3
user, but is not data).
E 3
.PP
The common calling convention for this routine is,
.DS
D 3
(void) (*protosw[].pr_ctlinput)(req, info);
int req; caddr_t info;
E 3
I 3
(void) (*protosw[].pr_ctlinput)(req, addr);
int req; struct sockaddr *addr;
E 3
.DE
The \fIreq\fP parameter is one of the following,
.DS
D 3
.if t .ta .6i 2.6i 3.1i
.if n .ta .84i 3.1i 3.80i
E 3
I 3
D 5
.ta \w'#define  'u '\w'PRC_UNREACH_NEEDFRAG   'u +8n
E 5
I 5
.ta \w'#define  'u +\w'PRC_UNREACH_NEEDFRAG   'u +8n
E 5
E 3
#define	PRC_IFDOWN	0	/* interface transition */
#define	PRC_ROUTEDEAD	1	/* select new route if possible */
#define	PRC_QUENCH	4	/* some said to slow down */
I 3
#define	PRC_MSGSIZE	5	/* message size forced drop */
E 3
#define	PRC_HOSTDEAD	6	/* normally from IMP */
#define	PRC_HOSTUNREACH	7	/* ditto */
#define	PRC_UNREACH_NET	8	/* no route to network */
#define	PRC_UNREACH_HOST	9	/* no route to host */
#define	PRC_UNREACH_PROTOCOL	10	/* dst says bad protocol */
#define	PRC_UNREACH_PORT	11	/* bad port # */
D 3
#define	PRC_MSGSIZE	12	/* message size forced drop */
#define	PRC_REDIRECT_NET	13	/* net routing redirect */
#define	PRC_REDIRECT_HOST	14	/* host routing redirect */
#define	PRC_TIMXCEED_INTRANS	17	/* packet lifetime expired in transit */
#define	PRC_TIMXCEED_REASS	18	/* lifetime expired on reass q */
#define	PRC_PARAMPROB	19	/* header incorrect */
E 3
I 3
#define	PRC_UNREACH_NEEDFRAG	12	/* IP_DF caused drop */
#define	PRC_UNREACH_SRCFAIL	13	/* source route failed */
#define	PRC_REDIRECT_NET	14	/* net routing redirect */
#define	PRC_REDIRECT_HOST	15	/* host routing redirect */
#define	PRC_REDIRECT_TOSNET	14	/* redirect for type of service & net */
#define	PRC_REDIRECT_TOSHOST	15	/* redirect for tos & host */
#define	PRC_TIMXCEED_INTRANS	18	/* packet lifetime expired in transit */
#define	PRC_TIMXCEED_REASS	19	/* lifetime expired on reass q */
#define	PRC_PARAMPROB	20	/* header incorrect */
E 3
.DE
D 3
while the \fIinfo\fP parameter is a ``catchall'' value which
is request dependent.  Many of the requests have obviously been
derived from ICMP (the Internet Control Message Protocol),
E 3
I 3
while the \fIaddr\fP parameter is the address to which the condition applies.
Many of the requests have obviously been
derived from ICMP (the Internet Control Message Protocol [Postel81c]),
E 3
and from error messages defined in the 1822 host/IMP convention
[BBN78].  Mapping tables exist to convert
control requests to UNIX error codes which are delivered
to a user.
.NH 2
pr_ctloutput
.PP
D 3
This routine is not currently used by any protocol modules.
.ds RH "Protocol/network-interface
.bp
E 3
I 3
This is the routine that implements per-socket options at the protocol
level for \fIgetsockopt\fP and \fIsetsockopt\fP.
The calling convention is,
.DS
error = (*protosw[].pr_ctloutput)(op, so, level, optname, mp);
int op; struct socket *so; int level, optname; struct mbuf **mp;
.DE
where \fIop\fP is one of PRCO_SETOPT or PRCO_GETOPT,
\fIso\fP is the socket from whence the call originated,
and \fIlevel\fP and \fIoptname\fP are the protocol level and option name
supplied by the user.
The results of a PRCO_GETOPT call are returned in an mbuf whose address
is placed in \fImp\fP before return.
On a PRCO_SETOPT call, \fImp\fP contains the address of an mbuf
containing the option data; the mbuf should be freed before return.
D 4
'ne 2i
E 4
E 3
E 1
