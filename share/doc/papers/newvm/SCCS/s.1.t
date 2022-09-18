h53510
s 00001/00011/00350
d D 5.1 91/04/16 18:41:32 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00347
d D 1.5 89/03/10 09:44:08 bostic 5 4
c add Berkeley specific copyright notice
e
s 00005/00005/00345
d D 1.4 86/08/11 19:00:27 mckusick 4 3
c final draft for EUUG
e
s 00037/00039/00313
d D 1.3 86/08/11 18:11:47 mckusick 3 2
c edits from Mike Karels
e
s 00038/00020/00314
d D 1.2 86/08/11 14:49:42 mckusick 2 1
c first round cleanup
e
s 00334/00000/00000
d D 1.1 86/08/11 11:51:42 mckusick 1 0
c first draft
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1986 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
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
.\" %sccs.include.redist.man%
E 6
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
.NH
Motivations for a New Virtual Memory System
.PP
The virtual memory system distributed with Berkeley UNIX has served
its design goals admirably well over the ten years of its existence.
However the relentless advance of technology has begun to render it
obsolete.
This section of the paper describes the current design,
points out the current technological trends,
and attempts to define the new design considerations that should
be taken into account in a new virtual memory design.
.SH
D 4
Implementation of 4.3BSD Virtual Memory
E 4
I 4
Implementation of 4.3BSD virtual memory
E 4
.PP
All Berkeley Software Distributions through 4.3BSD
D 3
have used the same  virtual memory design.
All processes whether active or sleeping have some amount of
E 3
I 3
have used the same virtual memory design.
All processes, whether active or sleeping, have some amount of
E 3
virtual address space associated with them.
This virtual address space
D 3
is the combination of the amount of address space that they initially
started with plus any stack and heap requests that they have made.
E 3
I 3
is the combination of the amount of address space with which they initially
started plus any stack or heap expansions that they have made.
E 3
All requests for address space are allocated from available swap space
at the time that they are first made;
if there is insufficient swap space left to honor the allocation,
the system call requesting the address space fails synchronously.
Thus, the limit to available virtual memory is established by the
amount of swap space allocated to the system.
D 3
Although processes logically allocate contiguous areas of swap space,
the actual allocation is done in (possibly) discontinuous blocks.
E 3
.PP
Memory pages are used in a sort of shell game to contain the
D 2
contents of recent accessed addresses.
E 2
I 2
D 3
contents of recent accessed locations.
E 2
As processes first touch an address
E 3
I 3
contents of recently accessed locations.
As a process first references a location
E 3
a new page is allocated and filled either with initialized data or
zeros (for new stack and break pages).
As the supply of free pages begins to run out, dirty pages are
D 2
pushed to previously allocated swap space so that they can be reused
E 2
I 2
pushed to the previously allocated swap space so that they can be reused
E 2
to contain newly faulted pages.
If a previously accessed page that has been pushed to swap is once
D 2
again touched, a free page is reallocated and filled from the swap area.
E 2
I 2
D 3
again touched, a free page is reallocated and filled from the swap area
E 3
I 3
again used, a free page is reallocated and filled from the swap area
E 3
[Babaoglu79], [Someren84].
E 2
.SH
D 2
Design Assumptions
E 2
I 2
D 4
Design Assumptions for 4.3BSD Virtual Memory
E 4
I 4
Design assumptions for 4.3BSD virtual memory
E 4
E 2
.PP
D 3
The design criterion for the current virtual memory implementation
E 3
I 3
The design criteria for the current virtual memory implementation
E 3
D 2
were made in 1978.
E 2
I 2
were made in 1979.
E 2
At that time the cost of memory was about a thousand times greater per
byte than magnetic disks.
Most machines were used as centralized time sharing machines.
These machines had far more disk storage than they had memory
and given the cost tradeoff between memory and disk storage,
wanted to make maximal use of the memory even at the cost of
wasting some of the disk space or generating extra disk I/O.
.PP
The primary motivation for virtual memory was to allow the
system to run individual programs whose address space exceeded
the memory capacity of the machine.
Thus the virtual memory capability allowed programs to be run that
D 2
could not have been run in the swap based systems.
E 2
I 2
could not have been run on a swap based system.
E 2
Equally important in the large central timesharing environment
was the ability to allow the sum of the memory requirements of
all active processes to exceed the amount of physical memory on
the machine.
The expected mode of operation for which the system was tuned
was to have the sum of active virtual memory be one and a half
to two times the physical memory on the machine.
.PP
D 3
At the time that the virtual memory system was designed most
machines ran with little or no networking.
E 3
I 3
At the time that the virtual memory system was designed,
most machines ran with little or no networking.
E 3
D 2
Thus all the file systems were contained on disks that were
E 2
I 2
All the file systems were contained on disks that were
E 2
directly connected to the machine.
Similarly all the disk space devoted to swap space was also
directly connected.
Thus the speed and latency with which file systems could be accessed
were roughly equivalent to the speed and latency with which swap
space could be accessed.
Given the high cost of memory there was little incentive to have
the kernel keep track of the contents of the swap area once a process
exited since it could almost as easily and quickly be reread from the
file system.
.SH
D 4
New Influences
E 4
I 4
New influences
E 4
.PP
In the ten years since the current virtual memory system was designed,
D 2
several technological advances have occurred.
E 2
I 2
many technological advances have occurred.
E 2
One effect of the technological revolution is that the
micro-processor has become powerful enough to allow users to have their
own personal workstations.
Thus the computing environment is moving away from a purely centralized
time sharing model to an environment in which users have a
computer on their desk.
This workstation is linked through a network to a centralized
D 3
pool of machines that provide file, compute, and spooling services.
E 3
I 3
pool of machines that provide filing, computing, and spooling services.
E 3
The workstations tend to have a large quantity of memory, 
but little or no disk space.
Because users do not want to be bothered with backing up their disks,
and because of the difficulty of having a centralized administration
backing up hundreds of small disks, these local disks are typically 
used only for temporary storage and as swap space.
Long term storage is managed by the central file server.
.PP
Another major technical advance has been in all levels of storage capacity.
In the last ten years we have experienced a factor of four decrease in the
cost per byte of disk storage.
In this same period of time the cost per byte of memory has dropped
by a factor of a hundred!
Thus the cost per byte of memory compared to the cost per byte of disk is
approaching a difference of only about a factor of ten.
The effect of this change is that the way in which a machine is used
is beginning to change dramatically.
As the amount of physical memory on machines increases and the number of
users per machine decreases, the expected
mode of operation is changing from that of supporting more active virtual 
memory than physical memory to that of having a surplus of memory that can
be used for other purposes.
.PP
Because many machines will have more physical memory than they do swap
space (with diskless workstations as an extreme example!),
it is no longer reasonable to limit the maximum virtual memory
to the amount of swap space as is done in the current design.
Consequently, the new design will allow the maximum virtual memory
to be the sum of physical memory plus swap space.
For machines with no swap space, the maximum virtual memory will
be governed by the amount of physical memory.
.PP
Another effect of the current technology is that the latency and overhead
associated with accessing the file system is considerably higher
since the access must be be over the network
D 3
rather than to a locally attached disk.
E 3
I 3
rather than to a locally-attached disk.
E 3
One use of the surplus memory would be to
maintain a cache of recently used files;
repeated uses of these files would require at most a verification from
the file server that the data was up to date.
D 3
Under the current design, file cacheing is done by the buffer pool
E 3
I 3
Under the current design, file caching is done by the buffer pool,
E 3
while the free memory is maintained in a separate pool.
The new design should have only a single memory pool so that any
free memory can be used to cache recently accessed files.
.PP
Another portion of the memory will be used to keep track of the contents
D 2
of the blocks on swap space analogously to the way that memory pages are
handled.
E 2
I 2
D 3
of the blocks on the locally attached swap space analogously
E 3
I 3
of the blocks on any locally-attached swap space analogously
E 3
to the way that memory pages are handled.
E 2
D 3
Thus inactive swap blocks can also be used to cache less recently used
E 3
I 3
Thus inactive swap blocks can also be used to cache less-recently-used
E 3
file data.
Since the swap disk is locally attached, it can be much more quickly
accessed than a remotely located file system.
This design allows the user to simply allocate their entire local disk
to swap space, thus allowing the system to decide what files should
be cached to maximize its usefulness.
This design has two major benefits.
It relieves the user of deciding what files
should be kept in a small local file system.
It also insures that all modified files are migrated back to the
D 3
file server in a timely fashion thus eliminating the need to dump
E 3
I 3
file server in a timely fashion, thus eliminating the need to dump
E 3
the local disk or push the files manually.
.NH
User Interface
.PP
This section outlines our new virtual memory interface as it is
currently envisioned.
The details of the system call interface are contained in Appendix A.
.SH
Regions
.PP
D 3
The virtual memory interface is designed to support both large sparse
address spaces as well as small densely used address spaces.
In this context, small is an address space roughly the
E 3
I 3
The virtual memory interface is designed to support both large,
sparse address spaces as well as small, densely-used address spaces.
In this context, ``small'' is an address space roughly the
E 3
size of the physical memory on the machine, 
D 3
while large may extend up the the maximum addressability of the machine.
E 3
I 3
while ``large'' may extend up to the maximum addressability of the machine.
E 3
A process may divide its address space up into a number of regions.
Initially a process begins with four regions; 
D 3
a read-only region with its text, a private fill-on-demand region
for its initialized data, a private zero-fill-on-demand region
for its uninitialized data and heap, and a zero-fill-on-demand
region for its stack.
E 3
I 3
a shared read-only fill-on-demand region with its text,
a private fill-on-demand region for its initialized data,
a private zero-fill-on-demand region for its uninitialized data and heap,
and a private zero-fill-on-demand region for its stack.
E 3
In addition to these regions, a process may allocate new ones.
The regions may not overlap and the system may impose an alignment
constraint, but the size of the region should not be limited
D 2
beyond the constraints of the size of the address space.
E 2
I 2
beyond the constraints of the size of the virtual address space.
E 2
.PP
Each new region may be mapped either as private or shared.
When it is privately mapped, changes to the contents of the region
D 3
are not reflected to other process that map the same region.
Regions may be mapped read-only or as read-write.
E 3
I 3
are not reflected to any other process that map the same region.
Regions may be mapped read-only or read-write.
E 3
As an example, a shared library would be implemented as two regions;
a shared read-only region for the text, and a private read-write
region for the global variables associated with the library.
.PP
A region may be allocated with one of several allocation strategies.
It may map some memory hardware on the machine such as a frame buffer.
Since the hardware is responsible for storing the data,
such regions must be exclusive use if they are privately mapped.
.PP
D 2
A region can map a part or all of a file.
E 2
I 2
A region can map all or part of a file.
E 2
As the pages are first accessed, the region is filled in with the
appropriate part of the file.
If the region is mapped read-write and shared, changes to the
contents of the region are reflected back into the contents of the file.
If the region is read-write but private,
changes to the region are copied to a private page that is not
visible to other processes mapping the file,
and these modified pages are not reflected back to the file.
.PP
The final type of region is ``anonymous memory''.
Uninitialed data uses such a region, privately mapped;
it is zero-fill-on-demand and its contents are abandoned
when the last reference is dropped.
Unlike a region that is mapped from a file,
D 3
the contents of an anonymous region will never be read or written
from or to a disk unless memory is short and part of the region
E 3
I 3
the contents of an anonymous region will never be read from or
written to a disk unless memory is short and part of the region
E 3
must be paged to a swap area.
If one of these regions is mapped shared,
then all processes see the changes in the region.
This difference has important performance considerations;
the overhead of reading, flushing, and possibly allocating a file
is much higher than simply zeroing memory.
.PP
If several processes wish to share a region,
then they must have some way of rendezvousing.
D 3
For a mapped file this is easy,
E 3
I 3
For a mapped file this is easy;
E 3
D 2
the name of the file is used as the common name.
E 2
I 2
the name of the file is used as the rendezvous point.
E 2
However, processes may not need the semantics of mapped files
nor be willing to pay the overhead associated with them.
For anonymous memory they must use some other rendezvous point.
Our current interface allows processes to associate a
D 3
descriptor with a region which it may then pass to other
processes that wishes to attach to the region.
E 3
I 3
descriptor with a region, which it may then pass to other
processes that wish to attach to the region.
E 3
Such a descriptor may be bound into the UNIX file system
name space so that other processes can find it just as
D 3
they would do with a mapped file.
E 3
I 3
they would with a mapped file.
E 3
.SH
D 4
Shared memory as high speed IPC
E 4
I 4
Shared memory as high speed interprocess communication
E 4
.PP
D 2
A primary use envisioned for shared memory is to
E 2
I 2
The primary use envisioned for shared memory is to
E 2
D 4
provide a high speed interprocess communication mechanism 
E 4
I 4
provide a high speed interprocess communication (IPC) mechanism
E 4
between cooperating processes.
Existing IPC mechanisms (\fIi.e.\fP pipes, sockets, or streams)
require a system call to hand off a set
of data destined for another process, and another system call
by the recipient process to receive the data.
Even if the data can be transferred by remapping the data pages
to avoid a memory to memory copy, the overhead of doing the system
calls limits the throughput of all but the largest transfers.
D 3
Shared memory by contrast allows processes to share data at any
E 3
I 3
Shared memory, by contrast, allows processes to share data at any
E 3
level of granularity without system intervention.
.PP
D 3
However, to maintain all but the simplist of data structures,
E 3
I 3
However, to maintain all but the simplest of data structures,
E 3
the processes must serialize their modifications to shared
data structures if they are to avoid corrupting them.
This serialization is typically done with semaphores.
D 2
Unfortunately, the implementation of semaphores is typically
E 2
I 2
Unfortunately, most implementations of semaphores are
E 2
done with system calls. 
Thus processes are once again limited by the need to do two
system calls per transaction, one to lock the semaphore, the
second to release it.
The net effect is that the shared memory model provides little if 
any improvement in interprocess bandwidth.
.PP
To achieve a significant improvement in interprocess bandwidth
requires a large decrease in the number of system calls needed to
achieve the interaction.
In profiling applications that use
serialization locks such as the UNIX kernel,
one typically finds that most locks are not contested.
Thus if one can find a way to avoid doing a system call in the case
in which a lock is not contested,
one would expect to be able to dramatically reduce the number
of system calls needed to achieve serialization.
.PP
In our design, cooperating processes manage their semaphores
in their own address space.
In the typical case, a process executes an atomic test-and-set instruction
to acquire a lock, finds it free, and thus is able to get it.
Only in the (rare) case where the lock is already set does the process
need to do a system call to wait for the lock to clear.
When a process is finished with a lock, 
it can clear the lock itself.
Only if the ``WANT'' flag for the lock has been set is
it necessary for the process to do a system call to cause the other
process(es) to be awakened.
.PP
Another issue that must be considered is portability.
Some computers require access to special hardware to implement
atomic interprocessor test-and-set. 
For such machines the setting and clearing of locks would
all have to be done with system calls;
applications could still use the same interface without change,
though they would tend to run slowly.
.PP
The other issue of compatibility is with System V's semaphore
implementation.
Since the System V interface has been in existence for several years,
and applications have been built that depend on this interface,
it is important that this interface also be available.
Although the interface is based on system calls for both setting and
clearing locks,
the same interface can be obtained using our interface without
system calls in most cases.
.PP
This implementation can be achieved as follows.
System V allows entire sets of semaphores to be set concurrently.
If any of the locks are unavailable, the process is put to sleep
until they all become available.
Under our paradigm, a single additional semaphore is defined
that serializes access to the set of semaphores being simulated.
Once obtained in the usual way, the set of semaphores can be
inspected to see if the desired ones are available.
If they are available, they are set, the guardian semaphore
is released and the process proceeds.
If one or more of the requested set is not available,
D 2
the guardian semaphore is released and the process selects one of the
E 2
I 2
the guardian semaphore is released and the process selects an
E 2
D 3
unavailable to semaphores to wait for.
E 3
I 3
unavailable semaphores for which to wait.
E 3
On being reawakened, the whole selection process must be repeated.
.PP
In all the above examples, there appears to be a race condition.
Between the time that the process finds that a semaphore is locked,
and the time that it manages to call the system to sleep on the
semaphore another process may unlock the semaphore and issue a wakeup call.
Luckily the race can be avoided.
The insight that is critical is that the process and the kernel agree
on the physical byte of memory that is being used for the semaphore.
D 3
The system call to put a process to sleep takes a pointer to the
E 3
I 3
The system call to put a process to sleep takes a pointer
E 3
to the desired semaphore as its argument so that once inside
D 2
the kernel it can repeat the test-and-set. If the lock has cleared
E 2
I 2
the kernel, the kernel can repeat the test-and-set.
If the lock has cleared
E 2
(and possibly the wakeup issued) between the time that the process
D 3
did the test-and-set and eventually got into the sleep request system call
E 3
I 3
did the test-and-set and eventually got into the sleep request system call,
E 3
D 2
then the processor immediately resumes the process rather than putting
E 2
I 2
then the kernel immediately resumes the process rather than putting
E 2
it to sleep.
D 2
Thus the only problem to solve is how the processor interlocks between testing
a semaphore and going to sleep that we already know how to deal with.
E 2
I 2
Thus the only problem to solve is how the kernel interlocks between testing
a semaphore and going to sleep;
this problem has already been solved on existing systems.
.NH
References
.sp
.IP [Babaoglu79] 20
Babaoglu, O., and Joy, W.,
``Data Structures Added in the Berkeley Virtual Memory Extensions
to the UNIX Operating System''
Computer Systems Research Group, Dept of EECS, University of California,
Berkeley, CA 94720, USA, November 1979.
.IP [Someren84] 20
Someren, J. van,
``Paging in Berkeley UNIX'',
Laboratorium voor schakeltechniek en techneik v.d. 
informatieverwerkende machines,
Codenummer 051560-44(1984)01, February 1984.
E 2
E 1
