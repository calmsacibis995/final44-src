h41051
s 00001/00002/00381
d D 8.2 94/06/01 18:44:06 ah 9 8
c page breaks for the 4.4BSD manuals
e
s 00002/00002/00381
d D 8.1 93/06/08 18:37:45 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00376
d D 5.2 93/05/14 17:51:51 andrew 7 6
c 4.4 updates
e
s 00001/00011/00381
d D 5.1 91/04/17 10:20:53 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00378
d D 1.5 89/03/07 10:59:33 bostic 5 4
c add Berkeley specific copyright, for networking release
e
s 00011/00050/00370
d D 1.4 86/05/02 17:40:19 karels 4 3
c corrections
e
s 00002/00000/00418
d D 1.3 86/04/30 12:28:28 karels 3 2
c newer stuff from phil
e
s 00192/00086/00226
d D 1.2 86/04/30 11:21:50 karels 2 1
c updates for 4.3 from lapsley
e
s 00312/00000/00000
d D 1.1 86/04/30 11:18:59 karels 1 0
c 4.2BSD version
e
u
U
t
T
I 2
D 5
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 7
.\" Copyright (c) 1986 The Regents of the University of California.
E 7
I 7
D 8
.\" Copyright (c) 1986, 1993 The Regents of the University of California.
E 7
.\" All rights reserved.
E 8
I 8
.\" Copyright (c) 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 8
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
E 2
I 1
D 4
.ds RH "Network Library Routines
E 4
I 4
.\".ds RH "Network Library Routines
E 4
D 9
.bp
E 9
.nr H1 3
.nr H2 0
D 9
.bp
E 9
.LG
I 9
.sp 2
E 9
.B
.ce
3. NETWORK LIBRARY ROUTINES
.sp 2
.R
.NL
.PP
The discussion in section 2 indicated the possible need to
locate and construct network addresses when using the
interprocess communication facilities in a distributed
environment.  To aid in this task a number of routines
have been added to the standard C run-time library.
In this section we will consider the new routines provided
D 2
to manipulate network addresses.  While the 4.2BSD networking
facilities support only the DARPA standard Internet protocols,
these routines have been designed with flexibility in mind.
As more communication protocols become available, we hope
the same user interface will be maintained in accessing
network-related address data bases.  The only difference
should be the values returned to the user.  Since these
values are normally supplied the system, users should
not need to be directly aware of the communication protocol
and/or naming conventions in use.
E 2
I 2
D 7
to manipulate network addresses.  While the 4.3BSD networking
facilities support both the DARPA standard Internet protocols
and the Xerox NS protocols, most of the routines presented
E 7
I 7
to manipulate network addresses.  While the 4.4BSD networking
facilities support the Internet protocols
and the Xerox NS protocols,
most of the routines presented
E 7
in this section do not apply to the NS domain.  Unless otherwise
stated, it should be assumed that the routines presented in this
section do not apply to the NS domain.
E 2
.PP
Locating a service on a remote host requires many levels of
mapping before client and server may
communicate.  A service is assigned a name which is intended
for human consumption; e.g. \*(lqthe \fIlogin server\fP on host
monet\*(rq.
This name, and the name of the peer host, must then be translated
into network \fIaddresses\fP which are not necessarily suitable
for human consumption.  Finally, the address must then used in locating
a physical \fIlocation\fP and \fIroute\fP to the service.  The
D 2
specifics of these three mappings is likely to vary between
E 2
I 2
specifics of these three mappings are likely to vary between
E 2
network architectures.  For instance, it is desirable for a network
D 2
to not require hosts
E 2
I 2
to not require hosts to
E 2
be named in such a way that their physical location is known by
the client host.  Instead, underlying services in the network
may discover the actual location of the host at the time a client
host wishes to communicate.  This ability to have hosts named in
a location independent manner may induce overhead in connection
establishment, as a discovery process must take place,
but allows a host to be physically mobile without requiring it to
notify its clientele of its current location.
.PP
Standard routines are provided for: mapping host names 
to network addresses, network names to network numbers, 
protocol names to protocol numbers, and service names
to port numbers and the appropriate protocol to
use in communicating with the server process.  The
file <\fInetdb.h\fP> must be included when using any of these
routines.
.NH 2
Host names
.PP
D 2
A host name to address mapping is represented by
E 2
I 2
An Internet host name to address mapping is represented by
E 2
the \fIhostent\fP structure:
.DS
D 2
.DT
E 2
I 2
.if t .ta 0.6i 1.1i 2.6i
E 2
struct	hostent {
	char	*h_name;	/* official name of host */
	char	**h_aliases;	/* alias list */
D 2
	int	h_addrtype;	/* host address type */
E 2
I 2
	int	h_addrtype;	/* host address type (e.g., AF_INET) */
E 2
	int	h_length;	/* length of address */
D 2
	char	*h_addr;	/* address */
E 2
I 2
	char	**h_addr_list;	/* list of addresses, null terminated */
E 2
};
I 2

#define	h_addr	h_addr_list[0] 	/* first address, network byte order */
E 2
.DE
D 2
The official name of the host and its public aliases are
returned, along with a variable length address and address
type.  The routine \fIgethostbyname\fP(3N) takes a host name
E 2
I 2
The routine \fIgethostbyname\fP(3N) takes an Internet host name
E 2
and returns a \fIhostent\fP structure,
while the routine \fIgethostbyaddr\fP(3N)
D 2
maps host addresses into a \fIhostent\fP structure.  It is possible
E 2
I 2
maps Internet host addresses into a \fIhostent\fP structure.
.PP
The official name of the host and its public aliases are
returned by these routines,
along with the address type (family) and a null terminated list of
variable length address.  This list of addresses is
required because it is possible
E 2
for a host to have many addresses, all having the same name.
D 2
\fIGethostybyname\fP returns the first matching entry in the data
base file \fI/etc/hosts\fP; if this is unsuitable, the lower level
E 2
I 2
The \fIh_addr\fP definition is provided for backward compatibility,
and is defined to be the first address in the list of addresses
in the \fIhostent\fP structure.
.PP
The database for these calls is provided either by the
D 4
file \fI/etc/hosts\fP, or by use of a nameserver.  If the data
returned by \fIgethostbyname\fP are unsuitable, the lower level
E 2
routine \fIgethostent\fP(3N) may be used.  For example, to
obtain a \fIhostent\fP structure for a
host on a particular network the following routine might be
used (for simplicity, only Internet addresses are considered):
.DS
.if t .ta .5i 1.0i 1.5i 2.0i
.\" 3.5i went to 3.8i
.if n .ta .7i 1.4i 2.1i 2.8i 3.5i 4.2i
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
 ...
struct hostent *
gethostbynameandnet(name, net)
	char *name;
	int net;
{
	register struct hostent *hp;
	register char **cp;

	sethostent(0);
	while ((hp = gethostent()) != NULL) {
		if (hp->h_addrtype != AF_INET)
			continue;
		if (strcmp(name, hp->h_name)) {
			for (cp = hp->h_aliases; cp && *cp != NULL; cp++)
				if (strcmp(name, *cp) == 0)
					goto found;
			continue;
		}
	found:
		if (in_netof(*(struct in_addr *)hp->h_addr)) == net)
			break;
	}
	endhostent(0);
	return (hp);
}
.DE
(\fIin_netof\fP(3N) is a standard routine which returns
the network portion of an Internet address.)
I 2
\fIGethostent\fP can be used only
by systems which use the \fI/etc/hosts\fP database; systems
using nameservers cannot execute such a call.
E 4
I 4
file \fI/etc/hosts\fP (\fIhosts\fP\|(5)),
or by use of a nameserver, \fInamed\fP\|(8).
Because of the differences in these databases and their access protocols,
the information returned may differ.
When using the host table version of \fIgethostbyname\fP,
only one address will be returned, but all listed aliases will be included.
The nameserver version may return alternate addresses,
but will not provide any aliases other than one given as argument.
E 4
.PP
Unlike Internet names, NS names are always mapped into host
addresses by the use of a standard NS \fIClearinghouse service\fP,
a distributed name and authentication server.  The algorithms
for mapping NS names to addresses via a Clearinghouse are
rather complicated, and the routines are not part of the
standard libraries.  The user-contributed Courier (Xerox
remote procedure call protocol) compiler contains routines
to accomplish this mapping; see the documentation and
examples provided therein for more information.  It is
expected that almost all software that has to communicate
using NS will need to use the facilities of
the Courier compiler.
.PP
D 4
A NS host address is represented by the following:
E 4
I 4
An NS host address is represented by the following:
E 4
.DS
union ns_host {
	u_char	c_host[6];
	u_short	s_host[3];
};

union ns_net {
	u_char	c_net[4];
	u_short	s_net[2];
};

struct ns_addr {
	union ns_net	x_net;
	union ns_host	x_host;
	u_short	x_port;
};
.DE
The following code fragment inserts a known NS address into
a \fIns_addr\fP:
.DS
#include <sys/types.h>
#include <sys/socket.h>
#include <netns/ns.h>
 ...
u_long netnum;
struct sockaddr_ns dst;
 ...
bzero((char *)&dst, sizeof(dst));

/*
 * There is no convenient way to assign a long
 * integer to a ``union ns_net'' at present; in
 * the future, something will hopefully be provided,
 * but this is the portable way to go for now.
I 3
 * The network number below is the one for the NS net
 * that the desired host (gyre) is on.
E 3
 */
netnum = htonl(2266);
dst.sns_addr.x_net = *(union ns_net *) &netnum;
dst.sns_family = AF_NS;

/*
 * host 2.7.1.0.2a.18 == "gyre:Computer Science:UofMaryland"
 */
dst.sns_addr.x_host.c_host[0] = 0x02;
dst.sns_addr.x_host.c_host[1] = 0x07;
dst.sns_addr.x_host.c_host[2] = 0x01;
dst.sns_addr.x_host.c_host[3] = 0x00;
dst.sns_addr.x_host.c_host[4] = 0x2a;
dst.sns_addr.x_host.c_host[5] = 0x18;
dst.sns_addr.x_port = htons(75);
.DE
E 2
.NH 2
Network names
.PP
As for host names, routines for mapping network names to numbers,
and back, are provided.  These routines return a \fInetent\fP
structure:
.DS
.DT
/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct	netent {
	char	*n_name;	/* official name of net */
	char	**n_aliases;	/* alias list */
	int	n_addrtype;	/* net address type */
D 2
	int	n_net;	/* network # */
E 2
I 2
	int	n_net;	/* network number, host byte order */
E 2
};
.DE
The routines \fIgetnetbyname\fP(3N), \fIgetnetbynumber\fP(3N),
and \fIgetnetent\fP(3N) are the network counterparts to the
D 2
host routines described above.
E 2
I 2
host routines described above.  The routines extract their
information from \fI/etc/networks\fP.
.PP
NS network numbers are determined either by asking your local
Xerox Network Administrator (and hardcoding the information
into your code), or by querying the Clearinghouse for addresses.
The internetwork router is the only process
that needs to manipulate network numbers on a regular basis; if
a process wishes to communicate with a machine, it should ask the
Clearinghouse for that machine's address (which will include
the net number).
E 2
.NH 2
Protocol names
.PP
D 2
For protocols the \fIprotoent\fP structure defines the
E 2
I 2
For protocols, which are defined in \fI/etc/protocols\fP,
the \fIprotoent\fP structure defines the
E 2
protocol-name mapping
used with the routines \fIgetprotobyname\fP(3N),
\fIgetprotobynumber\fP(3N),
and \fIgetprotoent\fP(3N):
.DS
.DT
struct	protoent {
	char	*p_name;	/* official protocol name */
	char	**p_aliases;	/* alias list */
D 2
	int	p_proto;	/* protocol # */
E 2
I 2
	int	p_proto;	/* protocol number */
E 2
};
.DE
I 2
.PP
In the NS domain, protocols are indicated by the "client type"
field of a IDP header.  No protocol database exists; see section
5 for more information.
E 2
.NH 2
Service names
.PP
Information regarding services is a bit more complicated.  A service
is expected to reside at a specific \*(lqport\*(rq and employ
a particular communication protocol.  This view is consistent with
the Internet domain, but inconsistent with other network architectures.
D 2
Further, a service may reside on multiple ports or support multiple
protocols.  If either of these occurs, the higher level library routines
E 2
I 2
Further, a service may reside on multiple ports.
If this occurs, the higher level library routines
E 2
D 4
will have to be bypassed in favor of homegrown routines similar in
spirit to the \*(lqgethostbynameandnet\*(rq routine described above.
E 4
I 4
will have to be bypassed or extended.
E 4
I 2
Services available are contained in the file \fI/etc/services\fP.
E 2
A service mapping is described by the \fIservent\fP structure,
.DS
.DT
struct	servent {
	char	*s_name;	/* official service name */
	char	**s_aliases;	/* alias list */
D 2
	int	s_port;	/* port # */
E 2
I 2
	int	s_port;	/* port number, network byte order */
E 2
	char	*s_proto;	/* protocol to use */
};
.DE
The routine \fIgetservbyname\fP(3N) maps service
names to a servent structure by specifying a service name and,
optionally, a qualifying protocol.  Thus the call
.DS
D 2
sp = getservbyname("telnet", (char *)0);
E 2
I 2
sp = getservbyname("telnet", (char *) 0);
E 2
.DE
returns the service specification for a telnet server using
any protocol, while the call
.DS
sp = getservbyname("telnet", "tcp");
.DE
returns only that telnet server which uses the TCP protocol.
The routines \fIgetservbyport\fP(3N) and \fIgetservent\fP(3N) are
also provided.  The \fIgetservbyport\fP routine has an interface similar
to that provided by \fIgetservbyname\fP; an optional protocol name may
be specified to qualify lookups.
I 2
.PP
In the NS domain, services are handled by a central dispatcher
provided as part of the Courier remote procedure call facilities.
Again, the reader is referred to the Courier compiler documentation
and to the Xerox standard*
.FS
* \fICourier: The Remote Procedure Call Protocol\fP, XSIS 038112.
.FE
for further details.
E 2
.NH 2
Miscellaneous
.PP
D 2
With the support routines described above, an application program
E 2
I 2
With the support routines described above, an Internet application program
E 2
should rarely have to deal directly
with addresses.  This allows
services to be developed as much as possible in a network independent
fashion.  It is clear, however, that purging all network dependencies
is very difficult.  So long as the user is required to supply network
addresses when naming services and sockets there will always some
network dependency in a program.  For example, the normal
code included in client programs, such as the remote login program,
is of the form shown in Figure 1.
D 2
.KF
.DS
.if t .ta .5i 1.0i 1.5i 2.0i
.if n .ta .7i 1.4i 2.1i 2.8i
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
 ...
main(argc, argv)
	char *argv[];
{
	struct sockaddr_in sin;
	struct servent *sp;
	struct hostent *hp;
	int s;
	...
	sp = getservbyname("login", "tcp");
	if (sp == NULL) {
		fprintf(stderr, "rlogin: tcp/login: unknown service\en");
		exit(1);
	}
	hp = gethostbyname(argv[1]);
	if (hp == NULL) {
		fprintf(stderr, "rlogin: %s: unknown host\en", argv[1]);
		exit(2);
	}
	bzero((char *)&sin, sizeof (sin));
	bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
	sin.sin_family = hp->h_addrtype;
	sin.sin_port = sp->s_port;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("rlogin: socket");
		exit(3);
	}
	...
	if (connect(s, (char *)&sin, sizeof (sin)) < 0) {
		perror("rlogin: connect");
		exit(5);
	}
	...
}
.DE
.ce
Figure 1.  Remote login client code.
.KE
E 2
(This example will be considered in more detail in section 4.)
.PP
If we wanted to make the remote login program independent of the 
Internet protocols and addressing scheme we would be forced to add
a layer of routines which masked the network dependent aspects from
the mainstream login code.  For the current facilities available in
D 2
the system this does not appear to be worthwhile.  Perhaps when the
system is adapted to different network architectures the utilities
will be reorganized more cleanly.
E 2
I 2
the system this does not appear to be worthwhile.
E 2
.PP
Aside from the address-related data base routines, there are several
other routines available in the run-time library which are of interest
to users.  These are intended mostly to simplify manipulation of 
names and addresses.  Table 1 summarizes the routines
for manipulating variable length byte strings and handling byte
swapping of network addresses and values.
.KF
.DS B
.TS
box;
l | l
l | l.
Call	Synopsis
_
bcmp(s1, s2, n)	compare byte-strings; 0 if same, not 0 otherwise
bcopy(s1, s2, n)	copy n bytes from s1 to s2
bzero(base, n)	zero-fill n bytes starting at base
htonl(val)	convert 32-bit quantity from host to network byte order
htons(val)	convert 16-bit quantity from host to network byte order
ntohl(val)	convert 32-bit quantity from network to host byte order
ntohs(val)	convert 16-bit quantity from network to host byte order
.TE
.DE
.ce
Table 1.  C run-time routines.
.KE
.PP
The byte swapping routines are provided because the operating
D 2
system expects addresses to be supplied in network order.  On a
VAX, or machine with similar architecture, this
is usually reversed.  Consequently,
E 2
I 2
D 7
system expects addresses to be supplied in network order.  On
some architectures, such as the VAX,
E 7
I 7
system expects addresses to be supplied in network order (aka ``big-endian'' order).  On
``little-endian'' architectures, such as Intel x86 and VAX,
E 7
host byte ordering is different than
network byte ordering.  Consequently,
E 2
programs are sometimes required to byte swap quantities.  The
library routines which return network addresses provide them
in network order so that they may simply be copied into the structures
provided to the system.  This implies users should encounter the
byte swapping problem only when \fIinterpreting\fP network addresses.
For example, if an Internet port is to be printed out the following
code would be required:
.DS
printf("port number %d\en", ntohs(sp->s_port));
.DE
D 2
On machines other than the VAX these routines are defined as null
E 2
I 2
On machines where unneeded these routines are defined as null
E 2
macros.
I 2
.DS
.if t .ta .5i 1.0i 1.5i 2.0i
.if n .ta .7i 1.4i 2.1i 2.8i
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
 ...
main(argc, argv)
	int argc;
	char *argv[];
{
	struct sockaddr_in server;
	struct servent *sp;
	struct hostent *hp;
	int s;
	...
	sp = getservbyname("login", "tcp");
	if (sp == NULL) {
		fprintf(stderr, "rlogin: tcp/login: unknown service\en");
		exit(1);
	}
	hp = gethostbyname(argv[1]);
	if (hp == NULL) {
		fprintf(stderr, "rlogin: %s: unknown host\en", argv[1]);
		exit(2);
	}
	bzero((char *)&server, sizeof (server));
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = sp->s_port;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("rlogin: socket");
		exit(3);
	}
	...
	/* Connect does the bind() for us */

	if (connect(s, (char *)&server, sizeof (server)) < 0) {
		perror("rlogin: connect");
		exit(5);
	}
	...
}
.DE
.ce
Figure 1.  Remote login client code.
E 2
E 1
