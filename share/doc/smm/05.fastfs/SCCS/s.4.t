h31584
s 00002/00002/00224
d D 8.1 93/06/08 14:06:00 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00225
d D 6.3 91/04/17 12:03:56 bostic 4 3
c new copyright; att/bsd/shared
e
s 00014/00003/00222
d D 6.2 89/03/07 10:56:52 bostic 3 2
c add Berkeley specific copyright notice
e
s 00093/00062/00132
d D 6.1 86/05/14 16:47:09 kjd 2 1
c 4.3BSD beta release document
e
s 00194/00000/00000
d D 5.1 86/05/14 16:46:49 kjd 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 2
.\" Copyright (c) 1980 Regents of the University of California.
E 2
I 2
D 3
.\" Copyright (c) 1986 Regents of the University of California.
E 2
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 3
I 3
D 5
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1986, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
D 4
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
E 4
I 4
.\" %sccs.include.redist.roff%
E 4
E 3
.\"
.\"	%W% (Berkeley) %G%
.\"
.ds RH Performance
.NH 
Performance
.PP
Ultimately, the proof of the effectiveness of the
algorithms described in the previous section
is the long term performance of the new file system.
.PP
D 2
Our empiric studies have shown that the inode layout policy has
E 2
I 2
Our empirical studies have shown that the inode layout policy has
E 2
been effective.
When running the ``list directory'' command on a large directory
D 2
that itself contains many directories,
E 2
I 2
that itself contains many directories (to force the system
to access inodes in multiple cylinder groups),
E 2
the number of disk accesses for inodes is cut by a factor of two.
The improvements are even more dramatic for large directories
containing only files,
disk accesses for inodes being cut by a factor of eight.
This is most encouraging for programs such as spooling daemons that
access many small files,
since these programs tend to flood the
disk request queue on the old file system.
.PP
Table 2 summarizes the measured throughput of the new file system.
Several comments need to be made about the conditions under which these
tests were run.
D 2
The test programs measure the rate that user programs can transfer
E 2
I 2
The test programs measure the rate at which user programs can transfer
E 2
data to or from a file without performing any processing on it.
D 2
These programs must write enough data to insure that buffering in the
E 2
I 2
These programs must read and write enough data to
insure that buffering in the
E 2
operating system does not affect the results.
D 2
They should also be run at least three times in succession;
E 2
I 2
They are also run at least three times in succession;
E 2
the first to get the system into a known state
and the second two to insure that the 
experiment has stabilized and is repeatable.
D 2
The methodology and test results are
E 2
I 2
The tests used and their results are
E 2
discussed in detail in [Kridle83]\(dg.
.FS
D 2
\(dg A UNIX command that is similar to the reading test that we used is,
``cp file /dev/null'', where ``file'' is eight Megabytes long.
E 2
I 2
\(dg A UNIX command that is similar to the reading test that we used is
``cp file /dev/null'', where ``file'' is eight megabytes long.
E 2
.FE
The systems were running multi-user but were otherwise quiescent.
D 2
There was no contention for either the cpu or the disk arm.
E 2
I 2
There was no contention for either the CPU or the disk arm.
E 2
The only difference between the UNIBUS and MASSBUS tests
was the controller.
D 2
All tests used an Ampex Capricorn 330 Megabyte Winchester disk.
E 2
I 2
All tests used an AMPEX Capricorn 330 megabyte Winchester disk.
E 2
As Table 2 shows, all file system test runs were on a VAX 11/750.
All file systems had been in production use for at least
a month before being measured.
I 2
The same number of system calls were performed in all tests;
the basic system call overhead was a negligible portion of
the total running time of the tests.
E 2
.KF
.DS B
.TS
box;
c c|c s s
c c|c c c.
Type of	Processor and	Read
File System	Bus Measured	Speed	Bandwidth	% CPU
_
D 2
old 1024	750/UNIBUS	29 Kbytes/sec	29/1100 3%	11%
new 4096/1024	750/UNIBUS	221 Kbytes/sec	221/1100 20%	43%
new 8192/1024	750/UNIBUS	233 Kbytes/sec	233/1100 21%	29%
new 4096/1024	750/MASSBUS	466 Kbytes/sec	466/1200 39%	73%
new 8192/1024	750/MASSBUS	466 Kbytes/sec	466/1200 39%	54%
E 2
I 2
old 1024	750/UNIBUS	29 Kbytes/sec	29/983 3%	11%
new 4096/1024	750/UNIBUS	221 Kbytes/sec	221/983 22%	43%
new 8192/1024	750/UNIBUS	233 Kbytes/sec	233/983 24%	29%
new 4096/1024	750/MASSBUS	466 Kbytes/sec	466/983 47%	73%
new 8192/1024	750/MASSBUS	466 Kbytes/sec	466/983 47%	54%
E 2
.TE
.ce 1
Table 2a \- Reading rates of the old and new UNIX file systems.
.TS
box;
c c|c s s
c c|c c c.
Type of	Processor and	Write
File System	Bus Measured	Speed	Bandwidth	% CPU
_
D 2
old 1024	750/UNIBUS	48 Kbytes/sec	48/1100 4%	29%
new 4096/1024	750/UNIBUS	142 Kbytes/sec	142/1100 13%	43%
new 8192/1024	750/UNIBUS	215 Kbytes/sec	215/1100 19%	46%
new 4096/1024	750/MASSBUS	323 Kbytes/sec	323/1200 27%	94%
new 8192/1024	750/MASSBUS	466 Kbytes/sec	466/1200 39%	95%
E 2
I 2
old 1024	750/UNIBUS	48 Kbytes/sec	48/983 5%	29%
new 4096/1024	750/UNIBUS	142 Kbytes/sec	142/983 14%	43%
new 8192/1024	750/UNIBUS	215 Kbytes/sec	215/983 22%	46%
new 4096/1024	750/MASSBUS	323 Kbytes/sec	323/983 33%	94%
new 8192/1024	750/MASSBUS	466 Kbytes/sec	466/983 47%	95%
E 2
.TE
.ce 1
Table 2b \- Writing rates of the old and new UNIX file systems.
.DE
.KE
.PP
Unlike the old file system,
the transfer rates for the new file system do not
appear to change over time.
The throughput rate is tied much more strongly to the
amount of free space that is maintained.
D 2
The measurements in Table 2 were based on a file system run
with 10% free space.
Synthetic work loads suggest the performance deteriorates
to about half the throughput rates given in Table 2 when no
free space is maintained.
E 2
I 2
The measurements in Table 2 were based on a file system
with a 10% free space reserve.
Synthetic work loads suggest that throughput deteriorates
to about half the rates given in Table 2 when the file
systems are full.
E 2
.PP
The percentage of bandwidth given in Table 2 is a measure
of the effective utilization of the disk by the file system.
D 2
An upper bound on the transfer rate from the disk is measured
by doing 65536* byte reads from contiguous tracks on the disk.
.FS
* This number, 65536, is the maximal I/O size supported by the
VAX hardware; it is a remnant of the system's PDP-11 ancestry.
.FE
E 2
I 2
An upper bound on the transfer rate from the disk is calculated 
by multiplying the number of bytes on a track by the number
of revolutions of the disk per second.
E 2
The bandwidth is calculated by comparing the data rates
the file system is able to achieve as a percentage of this rate.
Using this metric, the old file system is only
D 2
able to use about 3-4% of the disk bandwidth,
while the new file system uses up to 39%
E 2
I 2
able to use about 3\-5% of the disk bandwidth,
while the new file system uses up to 47%
E 2
of the bandwidth.
.PP
I 2
Both reads and writes are faster in the new system than in the old system.
The biggest factor in this speedup is because of the larger
block size used by the new file system.
The overhead of allocating blocks in the new system is greater
than the overhead of allocating blocks in the old system,
however fewer blocks need to be allocated in the new system
because they are bigger.
The net effect is that the cost per byte allocated is about
the same for both systems.
.PP
E 2
In the new file system, the reading rate is always at least
as fast as the writing rate.
This is to be expected since the kernel must do more work when
allocating blocks than when simply reading them.
Note that the write rates are about the same 
as the read rates in the 8192 byte block file system;
the write rates are slower than the read rates in the 4096 byte block
file system.
The slower write rates occur because
the kernel has to do twice as many disk allocations per second,
D 2
and the processor is unable to keep up with the disk transfer rate.
E 2
I 2
making the processor unable to keep up with the disk transfer rate.
E 2
.PP
In contrast the old file system is about 50%
faster at writing files than reading them.
D 2
This is because the \fIwrite\fR system call is asynchronous and
E 2
I 2
This is because the write system call is asynchronous and
E 2
the kernel can generate disk transfer
requests much faster than they can be serviced,
D 2
hence disk transfers build up in the disk buffer cache.
Because the disk buffer cache is sorted by minimum seek order,
E 2
I 2
hence disk transfers queue up in the disk buffer cache.
Because the disk buffer cache is sorted by minimum seek distance,
E 2
the average seek between the scheduled disk writes is much
D 2
less than they would be if the data blocks are written out
in the order in which they are generated.
E 2
I 2
less than it would be if the data blocks were written out
in the random disk order in which they are generated.
E 2
However when the file is read,
D 2
the \fIread\fR system call is processed synchronously so
E 2
I 2
the read system call is processed synchronously so
E 2
the disk blocks must be retrieved from the disk in the
D 2
order in which they are allocated.
E 2
I 2
non-optimal seek order in which they are requested.
E 2
This forces the disk scheduler to do long
seeks resulting in a lower throughput rate.
.PP
I 2
In the new system the blocks of a file are more optimally
ordered on the disk.
Even though reads are still synchronous, 
the requests are presented to the disk in a much better order.
Even though the writes are still asynchronous,
they are already presented to the disk in minimum seek
order so there is no gain to be had by reordering them.
Hence the disk seek latencies that limited the old file system
have little effect in the new file system.
The cost of allocation is the factor in the new system that 
causes writes to be slower than reads.
.PP
E 2
The performance of the new file system is currently
D 2
limited by a memory to memory copy operation
because it transfers data from the disk into buffers
in the kernel address space and then spends 40% of the processor
cycles copying these buffers to user address space.
If the buffers in both address spaces are properly aligned, 
this transfer can be affected without copying by
E 2
I 2
limited by memory to memory copy operations
required to move data from disk buffers in the
system's address space to data buffers in the user's
address space.  These copy operations account for
about 40% of the time spent performing an input/output operation.
If the buffers in both address spaces were properly aligned, 
this transfer could be performed without copying by
E 2
using the VAX virtual memory management hardware.
D 2
This is especially desirable when large amounts of data
are to be transferred.
We did not implement this because it would change the semantics
of the file system in two major ways;
E 2
I 2
This would be especially desirable when transferring
large amounts of data.
We did not implement this because it would change the
user interface to the file system in two major ways:
E 2
user programs would be required to allocate buffers on page boundaries, 
and data would disappear from buffers after being written.
.PP
Greater disk throughput could be achieved by rewriting the disk drivers
to chain together kernel buffers.
D 2
This would allow files to be allocated to
contiguous disk blocks that could be read
E 2
I 2
This would allow contiguous disk blocks to be read
E 2
in a single disk transaction.
D 2
Most disks contain either 32 or 48 512 byte sectors per track.
The inability to use contiguous disk blocks effectively limits the performance
on these disks to less than fifty percent of the available bandwidth.
Since each track has a multiple of sixteen sectors
it holds exactly two or three 8192 byte file system blocks,
E 2
I 2
Many disks used with UNIX systems contain either
32 or 48 512 byte sectors per track.
Each track holds exactly two or three 8192 byte file system blocks,
E 2
or four or six 4096 byte file system blocks.
D 2
If the the next block for a file cannot be laid out contiguously,
E 2
I 2
The inability to use contiguous disk blocks
effectively limits the performance
on these disks to less than 50% of the available bandwidth.
If the next block for a file cannot be laid out contiguously,
E 2
then the minimum spacing to the next allocatable
block on any platter is between a sixth and a half a revolution.
The implication of this is that the best possible layout without
contiguous blocks uses only half of the bandwidth of any given track.
If each track contains an odd number of sectors, 
then it is possible to resolve the rotational delay to any number of sectors
by finding a block that begins at the desired 
rotational position on another track.
The reason that block chaining has not been implemented is because it
would require rewriting all the disk drivers in the system,
and the current throughput rates are already limited by the
speed of the available processors.
.PP
Currently only one block is allocated to a file at a time.
A technique used by the DEMOS file system
when it finds that a file is growing rapidly,
is to preallocate several blocks at once,
releasing them when the file is closed if they remain unused.
D 2
By batching up the allocation the system can reduce the
E 2
I 2
By batching up allocations, the system can reduce the
E 2
overhead of allocating at each write,
and it can cut down on the number of disk writes needed to
keep the block pointers on the disk
synchronized with the block allocation [Powell79].
I 2
This technique was not included because block allocation 
currently accounts for less than 10% of the time spent in
a write system call and, once again, the
current throughput rates are already limited by the speed
of the available processors.
E 2
.ds RH Functional enhancements
D 2
.bp
E 2
I 2
.sp 2
.ne 1i
E 2
E 1
