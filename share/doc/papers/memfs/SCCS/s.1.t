h10452
s 00007/00001/00359
d D 5.1 91/04/16 18:38:15 bostic 6 5
c new copyright; att/bsd/shared
e
s 00001/00001/00359
d D 1.5 90/04/16 18:39:56 mckusick 5 4
c tell it like it is
e
s 00023/00024/00337
d D 1.4 90/04/16 18:38:47 bostic 4 3
c minor fluff
e
s 00004/00004/00357
d D 1.3 90/04/16 17:48:25 mckusick 3 2
c minor cleanups
e
s 00129/00083/00232
d D 1.2 90/04/16 14:59:14 karels 2 1
c sundry wording/punct. changes; expand pros/cons in futures
e
s 00315/00000/00000
d D 1.1 90/04/13 16:55:33 mckusick 1 0
c date and time created 90/04/13 16:55:33 by mckusick
e
u
U
t
T
I 1
D 6
.\"	%W%	(Copyright 1990 M. K. McKusick)	%E%
E 6
I 6
.\" Copyright (c) 1990 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 6
.nr PS 11
.nr VS 13
.SH
Introduction
.PP
This paper describes the motivation for and implementation of
a memory-based filesystem.
Memory-based filesystems have existed for a long time;
D 2
they have generally been marketed as RAM-disks or sometimes
E 2
I 2
they have generally been marketed as RAM disks or sometimes
E 2
D 4
as software packages that use the general purpose memory on
a machine.
E 4
I 4
as software packages that use the machine's general purpose memory.
E 4
.[
white
.]
.PP
D 2
A RAM-disk is designed to appear like any other disk peripheral
E 2
I 2
A RAM disk is designed to appear like any other disk peripheral
E 2
connected to a machine.
It is normally interfaced to the processor through the I/O bus
and is accessed through a device driver similar or sometimes identical
to the device driver used for a normal magnetic disk.
The device driver sends requests for blocks of data to the device
and the requested data is then DMA'ed to or from the requested block.
Instead of storing its data on a rotating magnetic disk,
D 2
the RAM-disk stores its data in a large array of random access memory
E 2
I 2
the RAM disk stores its data in a large array of random access memory
E 2
or bubble memory.
D 2
Thus, the latency of accessing the RAM-disk is nearly zero
E 2
I 2
Thus, the latency of accessing the RAM disk is nearly zero
E 2
compared to the 15-50 milliseconds of latency incurred when
access rotating magnetic media.
D 2
RAM-disks also have the benefit of being able to transfer data at
E 2
I 2
RAM disks also have the benefit of being able to transfer data at
E 2
the maximum DMA rate of the system,
while disks are typically limited by the rate that the data passes
under the disk head.
.PP
D 2
Software packages simulating RAM-disks operate by allocating
E 2
I 2
Software packages simulating RAM disks operate by allocating
E 2
a fixed partition of the system memory.
The software then provides a device driver interface similar
D 2
to the one described for hardware RAM-disks,
E 2
I 2
to the one described for hardware RAM disks,
E 2
except that it uses memory-to-memory copy instead of DMA to move
D 2
the data between the RAM-disk and the system buffers.
Because the memory used by the RAM-disk is not available for
E 2
I 2
the data between the RAM disk and the system buffers,
or it maps the contents of the RAM disk into the system buffers.
Because the memory used by the RAM disk is not available for
E 2
other purposes, software RAM-disk solutions are used primarily
for machines with limited addressing capabilities such as PC's
that do not have an effective way of using the extra memory anyway.
.PP
D 2
Most RAM-disks lose their contents when the system is powered
E 2
I 2
Most software RAM disks lose their contents when the system is powered
E 2
D 4
down or is rebooted.
E 4
I 4
down or rebooted.
E 4
The contents can be saved by using battery backed-up memory,
D 4
by storing critical filesystem data structure in the filesystem,
E 4
I 4
by storing critical filesystem data structures in the filesystem,
E 4
and by running a consistency check program after each reboot.
D 4
These conditions increase the hardware cost,
E 4
I 4
These conditions increase the hardware cost
E 4
and potentially slow down the speed of the disk.
Thus, RAM-disk filesystems are not typically
designed to survive power failures;
because of their volatility, their usefulness is limited to transient
D 4
or easily recreated information such as would be found in
E 4
I 4
or easily recreated information such as might be found in
E 4
.PN /tmp .
Their primary benefit is that they have higher throughput
than disk based filesystems.
.[
smith
.]
This improved throughput is particularly useful for utilities that
D 4
make heavy use of temporary files such as many compilers.
E 4
I 4
make heavy use of temporary files, such as compilers.
E 4
On fast processors, nearly half of the elapsed time for a compilation
is spent waiting for synchronous operations required for file
creation and deletion.
The use of the memory-based filesystem nearly eliminates this waiting time.
.PP
D 2
Using dedicated memory to exclusively support a RAM-disk
E 2
I 2
Using dedicated memory to exclusively support a RAM disk
E 2
is a poor use of resources.
The overall throughput of the system can be improved
by using the memory where it is getting the highest access rate.
D 2
These needs may shift between supporting virtual address space
and cacheing frequently used disk blocks.
E 2
I 2
These needs may shift between supporting process virtual address spaces
and caching frequently used disk blocks.
E 2
D 4
If the memory is to be dedicated to the filesystem,
E 4
I 4
If the memory is dedicated to the filesystem,
E 4
it is better used in a buffer cache.
The buffer cache permits faster access to the data
because it requires only a single memory-to-memory copy
from the kernel to the user process.
D 2
When it is used in a RAM-disk configuration it requires two
memory-to-memory copies, one from the RAM-disk
E 2
I 2
The use of memory is used in a RAM-disk configuration may require two
memory-to-memory copies, one from the RAM disk
E 2
to the buffer cache,
then another copy from the buffer cache to the user process.
.PP
D 4
The new work being presented in this paper is to build
D 2
a RAM-disk filesystem in pageable memory instead of dedicated memory.
The goal is to provide the speed benefits of a RAM-disk
E 2
I 2
a prototype RAM-disk filesystem in pageable memory instead of dedicated memory.
E 4
I 4
The new work being presented in this paper is building a prototype
RAM-disk filesystem in pageable memory instead of dedicated memory.
E 4
The goal is to provide the speed benefits of a RAM disk
E 2
without paying the performance penalty inherent in dedicating
D 2
part of the physical memory on the machine to the RAM-disk.
E 2
I 2
part of the physical memory on the machine to the RAM disk.
E 2
By building the filesystem in pageable memory,
it competes with other processes for the available memory.
When memory runs short, the paging system pushes its
least-recently-used pages to backing store.
Being pageable also allows the filesystem to be much larger than
would be practical if it were limited by the amount of physical
memory that could be dedicated to that purpose.
We typically operate our
.PN /tmp
with 30 to 60 megabytes of space
which is larger than the amount of memory on the machine.
This configuration allows small files to be accessed quickly,
while still allowing
.PN /tmp
D 2
to be used for big files albeit
at the speed more typical of normal disk based filesystems.
E 2
I 2
D 4
to be used for big files, albeit
at the speed more typical of normal disk-based filesystems.
E 4
I 4
to be used for big files,
although at a speed more typical of normal, disk-based filesystems.
E 4
E 2
.PP
An alternative to building a memory-based filesystem would be to have
a filesystem that never did operations synchronously and never
flushed its dirty buffers to disk.
However, we believe that such a filesystem would either
use a disproportionately large percentage of the buffer
D 2
cache space to the detriment of other disk based filesystems,
or would require the equivalent of the
paging system to push out its dirty pages.
E 2
I 2
D 4
cache space, to the detriment of other disk based filesystems,
or would require the paging system to push out its dirty pages.
E 4
I 4
cache space, to the detriment of other filesystems,
or would require the paging system to flush its dirty pages.
E 4
E 2
Waiting for other filesystems to push dirty pages
subjects them to delays while waiting for the pages to be written.
D 2
We await the results of others trying out this approach.
E 2
I 2
We await the results of others trying this approach.
E 2
.[
Ohta
.]
.SH
Implementation
.PP
D 2
The implementation took less time to write than this paper.
E 2
I 2
The current implementation took less time to write than did this paper.
E 2
It consists of 560 lines of kernel code (1.7K text + data)
and some minor modifications to the program that builds
D 2
disk based filesystems, ``newfs''.
E 2
I 2
disk based filesystems, \fInewfs\fP.
E 2
D 5
The interesting parts of the kernel code for the
E 5
I 5
A condensed version of the kernel code for the
E 5
D 2
memory-based filesystem is reproduced in Appendix 1.
E 2
I 2
memory-based filesystem are reproduced in Appendix 1.
E 2
.PP
D 2
A filesystem is created by invoking ``newfs'' with
E 2
I 2
A filesystem is created by invoking the modified \fInewfs\fP, with
E 2
an option telling it to create a memory-based filesystem.
D 2
It allocates a piece of virtual address space of the requested
E 2
I 2
It allocates a section of virtual address space of the requested
E 2
size and builds a filesystem in the memory
instead of on a disk partition.
D 2
When built, it does a ``mount'' system call specifying a filesystem type of
.SM MFS .
The auxillary data parameter specifies a pointer
E 2
I 2
When built, it does a \fImount\fP system call specifying a filesystem type of
.SM MFS
(Memory File System).
The auxiliary data parameter to the mount call specifies a pointer
E 2
to the base of the memory in which it has built the filesystem.
D 2
(The auxillary data parameter is used by the local filesystem
to specify the block device containing the filesystem.)
E 2
I 2
(The auxiliary data parameter used by the local filesystem, \fIufs\fP,
specifies the block device containing the filesystem.)
E 2
.PP
The mount system call allocates and initializes a mount table
D 2
entry then calls the filesystem specific mount routine.
The filesystem specific routine is responsible for doing
the mount and initializing the filesystem specific
E 2
I 2
D 4
entry, then calls the filesystem-specific mount routine.
E 4
I 4
entry and then calls the filesystem-specific mount routine.
E 4
The filesystem-specific routine is responsible for doing
the mount and initializing the filesystem-specific
E 2
portion of the mount table entry.
D 2
The memory-based filesystem specific mount routine,
E 2
I 2
The memory-based filesystem-specific mount routine,
E 2
.RN mfs_mount ,
is shown in Appendix 1.
D 2
It allocates a block device vnode to represent the memory disk device.
E 2
I 2
It allocates a block-device vnode to represent the memory disk device.
E 2
In the private area of this vnode it stores the base address of
D 2
the filesystem and the process identifier of the ``newfs'' process
E 2
I 2
the filesystem and the process identifier of the \fInewfs\fP process
E 2
for later reference when doing I/O.
It also initializes an I/O list that it
uses to record outstanding I/O requests.
D 2
It can then call the local filesystem mount routine
passing it the special block-device vnode that it has created
instead of the usual disk block-device vnode
that it would normally receive.
The mount proceeds just as an other local mount except that
E 2
I 2
It can then call the \fIufs\fP filesystem mount routine,
passing the special block-device vnode that it has created
instead of the usual disk block-device vnode.
The mount proceeds just as any other local mount, except that
E 2
requests to read from the block device are vectored through
.RN mfs_strategy
(described below) instead of the usual
.RN spec_strategy
D 2
block device.
E 2
I 2
block device I/O function.
E 2
When the mount is completed,
.RN mfs_mount
D 2
does not return as most other filesystem mount types do;
instead it sleeps in the kernel waiting for I/O requests.
E 2
I 2
does not return as most other filesystem mount functions do;
instead it sleeps in the kernel awaiting I/O requests.
E 2
Each time an I/O request is posted for the filesystem,
D 2
a wakeup is issued to the corresponding ``newfs'' process.
E 2
I 2
a wakeup is issued for the corresponding \fInewfs\fP process.
E 2
When awakened, the process checks for requests on its buffer list.
D 2
A read request is serviced by copying data from the piece of the
``newfs'' address space corresponding to the requested disk block
E 2
I 2
A read request is serviced by copying data from the section of the
\fInewfs\fP address space corresponding to the requested disk block
E 2
to the kernel buffer.
D 2
Similarly a write request is serviced by copying data to the piece of the
``newfs'' address space corresponding to the requested disk block
E 2
I 2
Similarly a write request is serviced by copying data to the section of the
\fInewfs\fP address space corresponding to the requested disk block
E 2
from the kernel buffer.
D 2
When all the requests have been serviced, the ``newfs''
E 2
I 2
When all the requests have been serviced, the \fInewfs\fP
E 2
process returns to sleep to await more requests.
.PP
Once mounted,
all operations on files in the memory-based filesystem are handled
D 2
by the local filesystem code until they get to the point where the
filesystem needs to do I/O on the block device.
E 2
I 2
by the \fIufs\fP filesystem code until they get to the point where the
filesystem needs to do I/O on the device.
E 2
Here, the filesystem encounters the second piece of the
memory-based filesystem.
Instead of calling the special-device strategy routine,
it calls the memory-based strategy routine,
.RN mfs_strategy .
Usually,
the request is serviced by linking the buffer onto the
I/O list for the memory-based filesystem
D 2
vnode and sending a wakeup to the ``newfs'' process.
This wakeup results in a context-switch to the ``newfs''
process that does a copyin or copyout as described above.
E 2
I 2
vnode and sending a wakeup to the \fInewfs\fP process.
This wakeup results in a context-switch to the \fInewfs\fP
process, which does a copyin or copyout as described above.
E 2
The strategy routine must be careful to check whether
D 2
the I/O request is coming from the ``newfs'' process itself.
Self requests happen during mount and unmount operations
E 2
I 2
the I/O request is coming from the \fInewfs\fP process itself, however.
Such requests happen during mount and unmount operations,
E 2
when the kernel is reading and writing the superblock.
Here,
.RN mfs_strategy
must do the I/O itself to avoid deadlock.
.PP
The final piece of kernel code to support the
D 4
memory-based filesystem is in the close routine.
After a filesystem is successfully unmounted,
E 4
I 4
memory-based filesystem is the close routine.
After the filesystem has been successfully unmounted,
E 4
the device close routine is called.
For a memory-based filesystem, the device close routine is
.RN mfs_close .
This routine flushes any pending I/O requests,
then sets the I/O list head to a special value
that is recognized by the I/O servicing loop in
.RN mfs_mount
as an indication that the filesystem is unmounted.
The
.RN mfs_mount
D 2
routine exits which in turn causes the ``newfs'' process
to exit resulting in the filesystem vanishing in a cloud of dirty pages.
E 2
I 2
D 4
routine exits which in turn causes the \fInewfs\fP process
to exit, resulting in the vanishing of the filesystem in a cloud of dirty pages.
E 4
I 4
routine exits, in turn causing the \fInewfs\fP process
to exit, resulting in the filesystem vanishing in a cloud of dirty pages.
E 4
E 2
.PP
The paging of the filesystem does not require any additional
code beyond that already in the kernel to support virtual memory.
D 2
The ``newfs'' process competes with other processes on an equal basis
E 2
I 2
The \fInewfs\fP process competes with other processes on an equal basis
E 2
D 4
for the available memory on the machine.
E 4
I 4
for the machine's available memory.
E 4
I 2
Data pages of the filesystem that have not yet been used
are zero-fill-on-demand pages that do not occupy memory,
although they currently allocate space in backing store.
E 2
D 4
If memory is plentiful, the entire contents of the filesystem
E 4
I 4
As long as memory is plentiful, the entire contents of the filesystem
E 4
remain memory resident.
D 2
When memory runs short, the oldest pages of ``newfs'' are
E 2
I 2
D 4
When memory runs short, the oldest pages of \fInewfs\fP are
E 2
pushed to backing store.
E 4
I 4
When memory runs short, the oldest pages of \fInewfs\fP will be
pushed to backing store as part of the normal paging activity.
E 4
The pages that are pushed usually hold the contents of
files that have been created in the memory-based filesystem
D 2
but have not been recently accessed.
E 2
I 2
but have not been recently accessed (or have been deleted).
E 2
.[
leffler
.]
.SH
Performance
.PP
D 2
The performance of the memory-based filesystem is determined by
E 2
I 2
The performance of the current memory-based filesystem is determined by
E 2
the memory-to-memory copy speed of the processor.
Empirically we find that the throughput is about 45% of this
memory-to-memory copy speed.
The basic set of steps for each block written is:
.IP 1)
memory-to-memory copy from the user process doing the write to a kernel buffer
.IP 2)
D 2
context-switch to the ``newfs'' process
E 2
I 2
context-switch to the \fInewfs\fP process
E 2
.IP 3)
D 2
memory-to-memory copy from the kernel buffer to the ``newfs'' address space
E 2
I 2
memory-to-memory copy from the kernel buffer to the \fInewfs\fP address space
E 2
.IP 4)
context switch back to the writing process
.LP
Thus each write requires at least two memory-to-memory copies
accounting for about 90% of the
.SM CPU
time.
The remaining 10% is consumed in the context switches and
the filesystem allocation and block location code.
The actual context switch count is really only about half
of the worst case outlined above because
read-ahead and write-behind allow multiple blocks
to be handled with each context switch.
.PP
D 2
On the six
E 2
I 2
On the six-\c
E 2
.SM "MIPS CCI"
Power 6/32 machine,
the raw reading and writing speed is only about twice that of
D 2
a regular disk based filesystem.
E 2
I 2
a regular disk-based filesystem.
E 2
However, for processes that create and delete many files,
the speedup is considerably greater.
The reason for the speedup is that the filesystem
must do two synchronous operations to create a file,
first writing the allocated inode to disk, then creating the
directory entry.
Deleting a file similarly requires at least two synchronous
operations.
Here, the low latency of the memory-based filesystem is
D 2
noticeable compared to the disk based filesystem
since a synchronous operation can be done with
E 2
I 2
noticeable compared to the disk-based filesystem,
as a synchronous operation can be done with
E 2
just two context switches instead of incurring the disk latency.
.SH
Future Work
.PP
I 2
The most obvious shortcoming of the current implementation
is that filesystem blocks are copied twice, once between the \fInewfs\fP
process' address space and the kernel buffer cache,
and once between the kernel buffer and the requesting process.
These copies are done in different process contexts, necessitating
two context switches per group of I/O requests.
D 3
These problems are due to the current inability of the kernel
E 3
I 3
These problems arise because of the current inability of the kernel
E 3
to do page-in operations
for an address space other than that of the currently-running process,
and the current inconvenience of mapping process-owned pages into the kernel
buffer cache.
Both of these problems are expected to be solved in the next version
of the virtual memory system,
and thus we chose not to address them in the current implementation.
With the new version of the virtual memory system, we expect to use
any part of physical memory as part of the buffer cache,
D 3
even though not all of it will be addressable at once within the kernel.
E 3
I 3
even though it will not be entirely addressable at once within the kernel.
E 3
In that system, the implementation of a memory-based filesystem
that avoids the double copy and context switches will be much easier.
.PP
E 2
D 4
Ideally part of the kernel's address space could reside in pageable memory.
E 4
I 4
Ideally part of the kernel's address space would reside in pageable memory.
E 4
D 2
Once such a facility is available it would be more efficient to
E 2
I 2
Once such a facility is available it would be most efficient to
E 2
build a memory-based filesystem within the kernel.
D 2
Such a filesystem would eliminate at least one of the memory-to-memory
copies in the present system, and would eliminate all the context switches.
E 2
One potential problem with such a scheme is that many kernels
are limited to a small address space (usually a few megabytes).
This restriction limits the size of memory-based
filesystem that such a machine can support.
On such a machine, the kernel can describe a memory-based filesystem
that is larger than its address space and use a ``window''
to map the larger filesystem address space into its limited address space.
The window would maintain a cache of recently accessed pages.
The problem with this scheme is that if the working set of
active pages is greater than the size of the window, then
much time is spent remapping pages and invalidating
translation buffers.
I 2
Alternatively, a separate address space could be constructed for each
memory-based filesystem as in the current implementation,
and the memory-resident pages of that address space could be mapped
exactly as other cached pages are accessed.
E 2
.PP
D 2
The current system uses the existing local filesystem code to manage
the virtual memory comprising the memory-based filesystem.
E 2
I 2
The current system uses the existing local filesystem structures
and code to implement the memory-based filesystem.
D 3
The major advantages of this approach is the sharing of code
E 3
I 3
The major advantages of this approach are the sharing of code
E 3
and the simplicity of the approach.
There are several disadvantages, however.
One is that the size of the filesystem is fixed at mount time.
This means that a fixed number of inodes (files) and data blocks
can be supported.
Currently, this approach requires enough swap space for the entire
filesystem, and prevents expansion and contraction of the filesystem on demand.
The current design also prevents the filesystem from taking advantage
of the memory-resident character of the filesystem.
E 2
It would be interesting to explore other filesystem implementations
that would be less expensive to execute and that would make better
use of the space.
D 2
One problem is that the resulting filesystem would almost
certainly be bigger than the memory-based filesystem described
in this paper.
Unless the performance was significantly improved,
it is unlikely that the larger code size would be worthwhile.
E 2
I 2
For example, the current filesystem structure is optimized for magnetic
disks.
It includes replicated control structures, ``cylinder groups''
with separate allocation maps and control structures,
and data structures that optimize rotational layout of files.
D 3
None of this is useful in a memory-base filesystem (at least when the
E 3
I 3
None of this is useful in a memory-based filesystem (at least when the
E 3
backing store for the filesystem is dynamically allocated and not
contiguous on a single disk type).
On the other hand,
directories could be implemented using dynamically-allocated
memory organized as linked lists or trees rather than as files stored
in ``disk'' blocks.
Allocation and location of pages for file data might use virtual memory
primitives and data structures rather than direct and indirect blocks.
A reimplementation along these lines will be considered when the virtual
memory system in the current system has been replaced.
E 2
.[
$LIST$
.]
E 1
