h49974
s 00002/00002/00089
d D 8.1 93/06/08 16:53:01 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00089
d D 6.6 93/06/06 12:21:16 mckusick 7 6
c crude update for 4.4BSD
e
s 00001/00011/00090
d D 6.5 91/04/17 12:06:22 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00087
d D 6.4 89/03/07 10:53:30 bostic 5 4
c install Berkeley specific copyright, for networking release
e
s 00002/00000/00088
d D 6.3 86/06/05 09:53:27 karels 4 3
c formatting glitches
e
s 00031/00021/00057
d D 6.2 86/06/04 23:54:53 karels 3 2
c updates for 4.3
e
s 00000/00000/00078
d D 6.1 86/05/26 13:27:52 mckusick 2 1
c 4.3BSD beta release document
e
s 00078/00000/00000
d D 5.1 86/05/26 13:27:46 mckusick 1 0
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
D 8
.\" Copyright (c) 1983, 1986 The Regents of the University of California.
.\" All rights reserved.
E 8
I 8
.\" Copyright (c) 1983, 1986, 1993
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
.nr H2 1
D 3
.ds RH Acknowledgements
E 3
I 3
.\".ds RH Acknowledgements
I 4
.br
.ne 2i
E 4
E 3
.SH
\s+2Acknowledgements\s0
.PP
The internal structure of the system is patterned
after the Xerox PUP architecture [Boggs79], while in certain
places the Internet
protocol family has had a great deal of influence in the design.
The use of software interrupts for process invocation
is based on similar facilities found in
the VMS operating system.
Many of the
ideas related to protocol modularity, memory management, and network
interfaces are based on Rob Gurwitz's TCP/IP implementation for the 
4.1BSD version of UNIX on the VAX [Gurwitz81].
Greg Chesson explained his use of trailer encapsulations in Datakit,
instigating their use in our system.
D 3
.ds RH References
E 3
I 3
.\".ds RH References
E 3
.nr H2 1
.sp 2
I 3
.ne 2i
E 3
.SH
\s+2References\s0
.LP
.IP [Boggs79] 20
Boggs, D. R., J. F. Shoch, E. A. Taft, and R. M. Metcalfe;
\fIPUP: An Internetwork Architecture\fP.  Report CSL-79-10.
XEROX Palo Alto Research Center, July 1979.
.IP [BBN78] 20
Bolt Beranek and Newman;
D 3
\fISpecification for the Interconnection of Host and IMP\fP.
E 3
I 3
Specification for the Interconnection of Host and IMP.
E 3
BBN Technical Report 1822.  May 1978.
.IP [Cerf78] 20
Cerf, V. G.;  The Catenet Model for Internetworking.
Internet Working Group, IEN 48.  July 1978.
.IP [Clark82] 20
D 3
Clark, D. D.;  Window and Acknowledgement Strategy in TCP. 
Internet Working Group, IEN Draft Clark-2.  March 1982.
E 3
I 3
Clark, D. D.;  Window and Acknowledgement Strategy in TCP, RFC-813.
Network Information Center, SRI International.  July 1982.
E 3
.IP [DEC80] 20
Digital Equipment Corporation;  \fIDECnet DIGITAL Network
Architecture \- General Description\fP.  Order No.
AA-K179A-TK.  October 1980.
.IP [Gurwitz81] 20
Gurwitz, R. F.;  VAX-UNIX Networking Support Project \- Implementation
Description.  Internetwork Working Group, IEN 168.
January 1981.
.IP [ISO81] 20
International Organization for Standardization.
\fIISO Open Systems Interconnection \- Basic Reference Model\fP.
ISO/TC 97/SC 16 N 719.  August 1981.
D 3
.IP [Joy82a] 20
Joy, W.; Cooper, E.; Fabry, R.; Leffler, S.; and McKusick, M.;
\fI4.2BSD System Manual\fP.  Computer Systems Research Group,
Technical Report 5.  University of California, Berkeley.  Draft
of September 1, 1982.
.IP [Postel79] 20
Postel, J., ed.  \fIDOD Standard User Datagram Protocol\fP.
Internet Working Group, IEN 88.  May 1979.
.IP [Postel80a] 20
Postel, J., ed.  \fIDOD Standard Internet Protocol\fP.
Internet Working Group, IEN 128.  January 1980.
.IP [Postel80b] 20
Postel, J., ed.  \fIDOD Standard Transmission Control Protocol\fP.
Internet Working Group, IEN 129.  January 1980.
E 3
I 3
.IP [Joy86] 20
Joy, W.; Fabry, R.; Leffler, S.; McKusick, M.; and Karels, M.;
D 7
Berkeley Software Architecture Manual, 4.3BSD Edition.
\fIUNIX Programmer's Supplementary Documents\fP, Vol. 1 (PS1:6).
E 7
I 7
Berkeley Software Architecture Manual, 4.4BSD Edition.
\fIUNIX Programmer's Supplementary Documents\fP, Vol. 1 (PSD:5).
E 7
Computer Systems Research Group,
University of California, Berkeley.
May, 1986.
.IP [Leffler84] 20
Leffler, S.J. and Karels, M.J.; Trailer Encapsulations, RFC-893.
Network Information Center, SRI International.
April 1984.
.IP [Postel80] 20
Postel, J.  User Datagram Protocol, RFC-768.
Network Information Center, SRI International.  May 1980.
.IP [Postel81a] 20
Postel, J., ed.  Internet Protocol, RFC-791.
Network Information Center, SRI International.  September 1981.
.IP [Postel81b] 20
Postel, J., ed.  Transmission Control Protocol, RFC-793.
Network Information Center, SRI International.  September 1981.
.IP [Postel81c] 20
Postel, J.  Internet Control Message Protocol, RFC-792.
Network Information Center, SRI International.  September 1981.
E 3
.IP [Xerox81] 20
Xerox Corporation.  \fIInternet Transport Protocols\fP. 
Xerox System Integration Standard 028112.  December 1981.
.IP [Zimmermann80] 20
Zimmermann, H.  OSI Reference Model \- The ISO Model of
Architecture for Open Systems Interconnection.
D 3
IEEE Transactions on Communications.  Com-28(4); 425-432.
E 3
I 3
\fIIEEE Transactions on Communications\fP.  Com-28(4); 425-432.
E 3
April 1980.
E 1
