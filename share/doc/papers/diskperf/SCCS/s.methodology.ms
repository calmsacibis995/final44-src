h23110
s 00004/00003/00081
d D 6.2 91/04/16 17:42:06 bostic 3 2
c written by Bob Kridle and Kirk McKusick, add Berkeley copyright
e
s 00000/00000/00084
d D 6.1 86/04/20 15:50:39 mckusick 2 1
c 4.3BSD release document
e
s 00084/00000/00000
d D 5.1 86/04/20 15:25:52 mckusick 1 0
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
.ds RH Methodology
.NH
Methodology
.PP
Our goal was to evaluate the performance of the target peripherals
in an environment as much like our 4.2BSD UNIX systems as possible.
There are two basic approaches to creating this kind of test environment.
These might be termed the \fIindirect\fR and the \fIdirect\fR approach.
The approach used by DEC in producing most of the performance data
on the UDA50/RA81 system under VMS is what we term the indirect
approach.
We chose to use the direct approach.
.PP
The indirect approach used by DEC involves two steps.
First, the environment in which performance is to be evaluated
is parameterized.
In this case, the disk I/O characteristics of VMS were measured
as to the distribution of various sizes of accesses and the proportion
of reads and writes.
This parameterization of
typical
I/O activity was termed a
``vax mix.''
The second stage involves simulating this mixture of I/O activities
with the devices to be tested and noting the total volume of transactions
processed per unit time by each system.
.PP
The problems encountered with this indirect approach often
have to do with the completeness and correctness of the parameterization
of the context environment.
For example, the 
``vax mix''
model constructed for DECs tests uses a random distribution of seeks
to the blocks read or written.
It is not likely that any real system produces a distribution
of disk transfer locations which is truly random and does not
exhibit strong locality characteristics.
.PP
The methodology chosen by us is direct
in the sense that it uses the standard structured file system mechanism present
in the 4.2BSD UNIX operating system to create the sequence of locations
and sizes of reads and writes to the benchmarked equipment.
We simply create, write, and read
files as they would be by user's activities.
The disk space allocation and disk cacheing mechanism built into
UNIX is used to produce the actual device reads and writes as well
as to determine their size and location on the disk.
We measure and compare the rate at which these 
.I
user files
.R
can be written, rewritten, or read.
.PP
The advantage of this approach is the implicit accuracy in
testing in the same environment in which the peripheral
will be used.
Although this system does not account for the I/O produced
by some paging and swapping, in our memory rich environment
these activities account for a relatively small portion
of the total disk activity.
.PP
A more significant disadvantage to the direct approach
is the occasional difficulty we have in accounting for our
measured results.
The apparently straight-forward activity of reading or writing a logical file
on disk can produce a complex mixture of disk traffic.
File I/O is supported by a file management system that
buffers disk traffic through an internal cache,
which allows writes to ba handled asynchronously.
Reads must be done synchronously,
however this restriction is moderated by the use of read-ahead.
Small changes in the performance of the disk controller
subsystem can result in large and unexpected
changes in the file system performance,
as it may change the characteristics of the memory contention
experienced by the processor.
.ds RH Tests
.bp
E 1
