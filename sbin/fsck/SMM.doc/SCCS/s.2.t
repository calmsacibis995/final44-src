h10752
s 00002/00002/00237
d D 8.1 93/06/05 12:52:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00235
d D 4.4 91/04/17 11:36:59 bostic 4 3
c new copyright; att/bsd/shared
e
s 00001/00001/00237
d D 4.3 86/02/01 20:19:01 mckusick 3 2
c changes from Bloom
e
s 00001/00002/00237
d D 4.2 85/07/18 22:42:45 mckusick 2 1
c update to reflect 4.3BSD version of fsck
e
s 00239/00000/00000
d D 4.1 85/06/03 17:25:48 mckusick 1 0
c version distributed with 4.2BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1982 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 5
.\" Copyright (c) 1982 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
.\" Copyright (c) 1982, 1993
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
.ds RH Overview of the file system
.NH
Overview of the file system
.PP
D 2
The file system is discussed in detail in [Mckusick83];
E 2
I 2
The file system is discussed in detail in [Mckusick84];
E 2
this section gives a brief overview.
.NH 2
Superblock
.PP
A file system is described by its
.I "super-block" .
The super-block is built when the file system is created (\c
.I newfs (8))
and never changes.
The super-block
contains the basic parameters of the file system,
such as the number of data blocks it contains
and a count of the maximum number of files.
Because the super-block contains critical data,
.I newfs
replicates it to protect against catastrophic loss.
The
.I "default super block"
always resides at a fixed offset from the beginning
of the file system's disk partition.
The
.I "redundant super blocks"
are not referenced unless a head crash
or other hard disk error causes the default super-block
to be unusable.
The redundant blocks are sprinkled throughout the disk partition.
.PP
Within the file system are files.
Certain files are distinguished as directories and contain collections
of pointers to files that may themselves be directories.
Every file has a descriptor associated with it called an
.I "inode".
The inode contains information describing ownership of the file,
time stamps indicating modification and access times for the file,
and an array of indices pointing to the data blocks for the file.
In this section,
we assume that the first 12 blocks
of the file are directly referenced by values stored
in the inode structure itself\(dg.
.FS
\(dgThe actual number may vary from system to system, but is usually in
the range 5-13.
.FE
The inode structure may also contain references to indirect blocks
containing further data block indices.
In a file system with a 4096 byte block size, a singly indirect
block contains 1024 further block addresses,
a doubly indirect block contains 1024 addresses of further single indirect
blocks,
and a triply indirect block contains 1024 addresses of further doubly indirect
D 3
blocks.
E 3
I 3
blocks (the triple indirect block is never needed in practice).
E 3
.PP
In order to create files with up to
2\(ua32 bytes,
using only two levels of indirection,
the minimum size of a file system block is 4096 bytes.
The size of file system blocks can be any power of two
greater than or equal to 4096.
The block size of the file system is maintained in the super-block,
so it is possible for file systems of different block sizes
to be accessible simultaneously on the same system.
The block size must be decided when
.I newfs
creates the file system;
the block size cannot be subsequently
changed without rebuilding the file system.
.NH 2
Summary information
.PP
Associated with the super block is non replicated
.I "summary information" .
The summary information changes
as the file system is modified.
The summary information contains
the number of blocks, fragments, inodes and directories in the file system.
.NH 2
Cylinder groups
.PP
The file system partitions the disk into one or more areas called
.I "cylinder groups".
A cylinder group is comprised of one or more consecutive
cylinders on a disk.
Each cylinder group includes inode slots for files, a
.I "block map"
describing available blocks in the cylinder group,
and summary information describing the usage of data blocks
within the cylinder group.
A fixed number of inodes is allocated for each cylinder group
when the file system is created.
The current policy is to allocate one inode for each 2048
bytes of disk space;
this is expected to be far more inodes than will ever be needed.
.PP
All the cylinder group bookkeeping information could be
placed at the beginning of each cylinder group.
However if this approach were used,
all the redundant information would be on the top platter.
A single hardware failure that destroyed the top platter
could cause the loss of all copies of the redundant super-blocks.
Thus the cylinder group bookkeeping information
begins at a floating offset from the beginning of the cylinder group.
The offset for
the
.I "i+1" st
cylinder group is about one track further
from the beginning of the cylinder group
than it was for the
.I "i" th
cylinder group.
In this way,
the redundant
information spirals down into the pack;
any single track, cylinder,
or platter can be lost without losing all copies of the super-blocks.
Except for the first cylinder group,
the space between the beginning of the cylinder group
and the beginning of the cylinder group information stores data.
.NH 2
Fragments
.PP
To avoid waste in storing small files,
the file system space allocator divides a single
file system block into one or more
.I "fragments".
The fragmentation of the file system is specified
when the file system is created;
each file system block can be optionally broken into
2, 4, or 8 addressable fragments.
The lower bound on the size of these fragments is constrained
by the disk sector size;
typically 512 bytes is the lower bound on fragment size.
The block map associated with each cylinder group
records the space availability at the fragment level.
Aligned fragments are examined
to determine block availability.
.PP
On a file system with a block size of 4096 bytes
and a fragment size of 1024 bytes,
a file is represented by zero or more 4096 byte blocks of data,
and possibly a single fragmented block.
If a file system block must be fragmented to obtain
space for a small amount of data,
the remainder of the block is made available for allocation
to other files.
For example,
consider an 11000 byte file stored on
a 4096/1024 byte file system.
This file uses two full size blocks and a 3072 byte fragment.
If no fragments with at least 3072 bytes
are available when the file is created,
a full size block is split yielding the necessary 3072 byte
fragment and an unused 1024 byte fragment.
This remaining fragment can be allocated to another file, as needed.
.NH 2
Updates to the file system
.PP
Every working day hundreds of files
are created, modified, and removed.
Every time a file is modified,
the operating system performs a
series of file system updates.
These updates, when written on disk, yield a consistent file system.
The file system stages
all modifications of critical information;
modification can
either be completed or cleanly backed out after a crash.
Knowing the information that is first written to the file system,
deterministic procedures can be developed to
repair a corrupted file system.
To understand this process,
the order that the update
requests were being honored must first be understood.
.PP
When a user program does an operation to change the file system,
such as a 
.I write ,
the data to be written is copied into an internal
.I "in-core"
buffer in the kernel.
Normally, the disk update is handled asynchronously;
the user process is allowed to proceed even though
the data has not yet been written to the disk.
The data,
along with the inode information reflecting the change,
is eventually written out to disk.
The real disk write may not happen until long after the
.I write
system call has returned.
Thus at any given time, the file system,
as it resides on the disk,
lags the state of the file system represented by the in-core information.
.PP
The disk information is updated to reflect the in-core information
when the buffer is required for another use,
when a
.I sync (2)
is done (at 30 second intervals) by
.I "/etc/update" "(8),"
or by manual operator intervention with the
.I sync (8)
command.
If the system is halted without writing out the in-core information,
the file system on the disk will be in an inconsistent state.
.PP
If all updates are done asynchronously, several serious
inconsistencies can arise.
One inconsistency is that a block may be claimed by two inodes.
Such an inconsistency can occur when the system is halted before
the pointer to the block in the old inode has been cleared
in the copy of the old inode on the disk,
and after the pointer to the block in the new inode has been written out
to the copy of the new inode on the disk.
Here,
there is no deterministic method for deciding
which inode should really claim the block.
A similar problem can arise with a multiply claimed inode.
.PP
The problem with asynchronous inode updates
can be avoided by doing all inode deallocations synchronously. 
Consequently,
inodes and indirect blocks are written to the disk synchronously
(\fIi.e.\fP the process blocks until the information is
really written to disk)
when they are being deallocated.
Similarly inodes are kept consistent by synchronously
deleting, adding, or changing directory entries.
.ds RH Fixing corrupted file systems
D 2
.bp
E 2
E 1
