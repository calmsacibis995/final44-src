h46889
s 00001/00001/00137
d D 5.1 91/04/17 09:42:18 bostic 5 4
c new copyright; att/bsd/shared
e
s 00004/00003/00134
d D 1.4 90/10/14 11:55:37 bostic 4 3
c replace copyright with Berkeley specific copyright notice
e
s 00012/00012/00125
d D 1.3 89/06/07 15:41:45 mckusick 3 2
c minor cleanups to send off to Computer
e
s 00018/00005/00119
d D 1.2 85/08/11 16:16:40 cabrera 2 1
c my first pass
e
s 00124/00000/00000
d D 1.1 85/07/27 19:43:10 mckusick 1 0
c date and time created 85/07/27 19:43:10 by mckusick
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1985 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
.\" Copyright (c) 1985 The Regents of the University of California.
.\" All rights reserved.
.\"
D 5
.\" %sccs.include.redist.roff%
E 5
I 5
.\" %sccs.include.redist.man%
E 5
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
.ds RH Conclusions
.NH
Conclusions
.PP
4.2BSD, while functionally superior to 4.1BSD, lacked much of the
performance tuning required of a good system.  We found that
the distributed system spent 10-20% more time in the kernel than
D 2
4.1.  This added overhead combined with problems with several
E 2
I 2
4.1BSD.  This added overhead combined with problems with several
E 2
user programs severely limited the overall performance of the
system in a general timesharing environment.
.PP
D 2
Changes made to the system since the 4.2 distribution have
E 2
I 2
Changes made to the system since the 4.2BSD distribution have
E 2
eliminated most of the
added system overhead by replacing old algorithms
or introducing additional cacheing schemes.  
The combined caches added to the name translation process
reduce the average cost of translating a pathname to an inode by more than 50%.
These changes reduce the percentage of time spent running
in the system by nearly 9%.
.PP
The use of silo input on terminal ports only when necessary
has allowed the system to avoid a large amount of software interrupt
processing.  Observations show that the system is forced to
field about 25% fewer interrupts than before.
.PP
The kernel
changes, combined with many bug fixes, make the system much more
D 2
responsive in a general timesharing environment.  The system now appears
capable of supporting loads at least as large as supported under
4.1 while providing all the new interprocess communication, networking,
E 2
I 2
responsive in a general timesharing environment.
The 4.3BSD Berkeley UNIX system now appears
capable of supporting loads at least as large as those supported under
4.1BSD while providing all the new interprocess communication, networking,
E 2
and file system facilities.  
.nr H2 1
.ds RH Acknowledgements
.SH
\s+2Acknowledgements\s0
.PP
We would like to thank Robert Elz for sharing his ideas and 
his code for cacheing system wide names and searching the process table.
We thank Alan Smith for initially suggesting the use of a
capability based cache.
We also acknowledge
George Goble who dropped many of our changes
into his production system and reported back fixes to the
disasters that they caused.
The buffer cache read-ahead trace package was based
on a program written by Jim Lawson.  Ralph Campbell
implemented several of the C library changes.  The original
version of the Internet daemon was written by Bill Joy.
In addition,
we would like to thank the many other people that contributed
ideas, information, and work while the system was undergoing change.
.ds RH References
.nr H2 1
.sp 2
.SH
\s+2References\s-2
.LP
I 3
.IP [Cabrera84] 20
Luis Felipe Cabrera, Eduard Hunter, Michael J. Karels, and David Mosher,
``A User-Process Oriented Performance Study of Ethernet Networking Under
Berkeley UNIX 4.2BSD,''
Research Report No. UCB/CSD 84/217, University of California,
Berkeley, December 1984.
.IP [Cabrera85] 20
Luis Felipe Cabrera, Michael J. Karels, and David Mosher,
``The Impact of Buffer Management on Networking Software Performance
in Berkeley UNIX 4.2BSD: A Case Study,''
Proceedings of the Summer Usenix Conference, Portland, Oregon,
June 1985, pp. 507-517.
E 3
.IP [GADS85] 20
GADS (Gateway Algorithms and Data Structures Task Force),
``Toward an Internet Standard for Subnetting,'' RFC-940,
Network Information Center, SRI International,
April 1985.
.IP [Joy80] 20
Joy, William,
``Comments on the performance of UNIX on the VAX'',
Computer System Research Group, U.C. Berkeley. 
April 1980.
.IP [Kashtan80] 20
Kashtan, David L.,
``UNIX and VMS, Some Performance Comparisons'',
SRI International.  February 1980.
.IP [Lankford84] 20
Jeffrey Lankford,
``UNIX System V and 4BSD Performance,''
\fIProceedings of the Salt Lake City Usenix Conference\fP,
pp 228-236, June 1984.
.IP [Leffler84] 20
Sam Leffler, Mike Karels, and M. Kirk McKusick,
``Measuring and Improving the Performance of 4.2BSD,''
\fIProceedings of the Salt Lake City Usenix Conference\fP,
pp 237-252, June 1984.
.IP [McKusick85]
M. Kirk McKusick, Mike Karels, and Samual Leffler,
``Performance Improvements and Functional Enhancements in 4.3BSD''
\fIProceedings of the Portland Usenix Conference\fP,
pp 519-531, June 1985.
.IP [Mockapetris83] 20
Paul Mockapetris, ``Domain Names \- Implementation and Schedule,''
Network Information Center, SRI International,
RFC-883,
November 1983.
.IP [Mogul84] 20
Jeffrey Mogul, ``Broadcasting Internet Datagrams,'' RFC-919,
Network Information Center, SRI International,
October 1984.
.IP [Mosher80] 20
Mosher, David,
``UNIX Performance, an Introspection'',
Presented at the Boulder, Colorado Usenix Conference, January 1980.
Copies of the paper are available from
Computer System Research Group, U.C. Berkeley. 
.IP [Nagle84] 20
John Nagle, ``Congestion Control in IP/TCP Internetworks,'' RFC-896,
Network Information Center, SRI International,
January 1984.
.IP [Ritchie74] 20
Ritchie, D. M. and Thompson, K.,
``The UNIX Time-Sharing System'',
CACM 17, 7. July 1974. pp 365-375
.IP [Shannon83] 20
Shannon, W.,
private communication,
July 1983
.IP [Walsh84] 20
Robert Walsh and Robert Gurwitz,
``Converting BBN TCP/IP to 4.2BSD,''
\fIProceedings of the Salt Lake City Usenix Conference\fP,
pp 52-61, June 1984.
I 2
D 3
.IP [Cabrera84] 20
Luis Felipe Cabrera, Eduard Hunter, Michael J. Karels, and David Mosher,
``A User-Process Oriented Performance Study of Ethernet Networking Under
Berkeley UNIX 4.2BSD,''
Research Report No. UCB/CSD 84/217, University of California,
Berkeley, December 1984.
.IP [Cabrera85] 20
Luis Felipe Cabrera, Michael J. Karels, and David Mosher,
``The Impact of Buffer Management on Networking Software Performance
in Berkeley UNIX 4.2BSD: A Case Study,''
Proceedings of the Summer Usenix Conference, Portland, Oregon,
June 1985, pp. 507-517.
E 3
E 2
E 1
