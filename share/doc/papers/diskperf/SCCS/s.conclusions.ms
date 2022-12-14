h20158
s 00004/00003/00097
d D 6.2 91/04/16 17:42:05 bostic 3 2
c written by Bob Kridle and Kirk McKusick, add Berkeley copyright
e
s 00006/00006/00094
d D 6.1 86/04/20 15:50:32 mckusick 2 1
c 4.3BSD release document
e
s 00100/00000/00000
d D 5.1 86/04/20 15:25:24 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 3
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 3
I 3
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
E 3
.\"
.\"	%W% (Berkeley) %G%
.\"
.ds RH Conclusions
.NH
Conclusions
.PP
Peak available throughput is only one criterion
in most storage system purchasing decisions.
Most of the VAX UNIX systems we are familiar with
are not I/O bandwidth constrained.
Nevertheless, an adequate disk bandwidth is necessary for
good performance and especially to preserve snappy
response time.
All of the disk systems we tested provide more than
adequate bandwidth for typical VAX UNIX system application.
Perhaps in some I/O-intensive applications such as
image processing, more consideration should be given
to the peak throughput available.
In most situations, we feel that other factors are more
important in making a storage choice between the systems we
tested.
Cost, reliability, availability, and support are some of these
factors.
The maturity of the technology purchased must also be weighed
against the future value and expandability of newer technologies.
.PP
Two important conclusions about storage systems in general
can be drawn from these tests.
The first is that buffering can be effective in smoothing
the the effects of lower bus speeds and bus contention.
Even though the UDA50 is located on the relatively slow
UNIBUS, its performance is similar to controllers located on
the faster processor busses.
However, the SC780 with only one sector of buffering shows that
little buffering is needed if the underlying bus is fast enough.
.PP
Placing more intelligence in the controller seems to hinder UNIX system
performance more than it helps.
Our profiling tests have indicated that UNIX spends about
the same percentage of time in the SC780 driver and the UDA50 driver
(about 10-14%).
Normally UNIX uses a disk sort algorithm that separates reads and
writes into two seek order queues.
The read queue has priority over the write queue,
since reads cause processes to block,
while writes can be done asynchronously.
This is particularly useful when generating large files,
as it allows the disk allocator to read
new disk maps and begin doing new allocations
while the blocks allocated out of the previous map are written to disk.
Because the UDA50 handles all block ordering,
and because it keeps all requests in a single queue,
there is no way to force the longer seek needed to get the next disk map.
This disfunction causes all the writes to be done before the disk map read,
which idles the disk until a new set of blocks can be allocated.
.PP
The additional functionality of the UDA50 controller that allows it
to transfer simultaneously from two drives at once tends to make
the two drive transfer tests run much more effectively.
Tuning for the single drive case works more effectively in the two
drive case than when controllers that cannot handle simultaneous
transfers are used.
.ds RH Acknowledgements
.nr H2 1
D 2
.sp 2
E 2
I 2
.sp 1
E 2
.SH
\s+2Acknowledgements\s0
.PP
We thank Paul Massigilia and Bill Grace
of Digital Equipment Corp for helping us run our
disk tests on their UDA50/RA81.
We also thank Rich Notari and Paul Ritkowski
of Emulex for making their machines available
to us to run our tests of the SC780/Eagles.
Dan McKinster, then of Systems Industries,
arranged to make their equipment available for the tests.
We appreciate the time provided by Bob Gross, Joe Wolf, and
Sam Leffler on their machines to refine our benchmarks.
Finally we thank our sponsors,
the National Science Foundation under grant MCS80-05144,
and the Defense Advance Research Projects Agency (DoD) under
Arpa Order No. 4031 monitored by Naval Electronic System Command under
Contract No. N00039-82-C-0235.
.ds RH References
.nr H2 1
D 2
.sp 2
E 2
I 2
.sp 1
E 2
.SH
\s+2References\s0
.LP
.IP [McKusick83] 20
D 2
McKusick, M., Joy, W., Leffler, S., and Fabry, R.
"A Fast File System for UNIX",
University of California at Berkeley,
Computer Systems Research Group Technical Report #7, 1982.
E 2
I 2
M. McKusick, W. Joy, S. Leffler, R. Fabry,
``A Fast File System for UNIX'',
\fIACM Transactions on Computer Systems 2\fP, 3.
pp 181-197, August 1984.
E 2
.ds RH Appendix A
.bp
E 1
