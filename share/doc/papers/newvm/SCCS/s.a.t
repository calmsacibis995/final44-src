h40684
s 00001/00011/00212
d D 5.1 91/04/16 18:41:33 bostic 6 5
c new copyright; att/bsd/shared
e
s 00014/00003/00209
d D 1.5 89/03/10 09:44:13 bostic 5 4
c add Berkeley specific copyright notice
e
s 00001/00001/00211
d D 1.4 86/08/11 19:00:39 mckusick 4 3
c final draft for EUUG
e
s 00012/00012/00200
d D 1.3 86/08/11 18:11:58 mckusick 3 2
c edits from Mike Karels
e
s 00019/00013/00193
d D 1.2 86/08/11 14:49:52 mckusick 2 1
c first round cleanup
e
s 00206/00000/00000
d D 1.1 86/08/11 11:52:01 mckusick 1 0
c first draft
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1983 Regents of the University of California.
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
.sp 2
.ne 2i
.NH
Appendix A \- Virtual Memory Interface
.SH
Mapping pages
.PP
The system supports sharing of data between processes
by allowing pages to be mapped into memory.  These mapped
pages may be \fIshared\fP with other processes or \fIprivate\fP
to the process.
Protection and sharing options are defined in \fI<sys/mman.h>\fP as:
.DS
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
/* protections are chosen from these bits, or-ed together */
#define	PROT_READ	0x04	/* pages can be read */
#define	PROT_WRITE	0x02	/* pages can be written */
#define	PROT_EXEC	0x01	/* pages can be executed */
D 2

E 2
I 2
.DE
D 3
.sp
E 3
.DS
I 3
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 3
E 2
/* flags contain mapping type, sharing type and options */
/* mapping type; choose one */
#define MAP_FILE	0x0001	/* mapped from a file or device */
#define MAP_ANON	0x0002	/* allocated from memory, swap space */
#define MAP_TYPE	0x000f	/* mask for type field */
D 2

E 2
I 2
.DE
D 3
.sp
E 3
.DS
I 3
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 3
E 2
/* sharing types; choose one */
#define	MAP_SHARED	0x0010	/* share changes */
#define	MAP_PRIVATE	0x0000	/* changes are private */
D 2

E 2
I 2
.DE
D 3
.sp
E 3
.DS
I 3
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 3
E 2
/* other flags */
#define MAP_FIXED	0x0020	/* map addr must be exactly as requested */
D 3
#define MAP_NOEXTEND	0x0040	/* for MAP_FILE, don't change file size */
E 3
I 3
#define MAP_INHERIT	0x0040	/* region is retained after exec */
E 3
#define MAP_HASSEMAPHORE	0x0080	/* region may contain semaphores */
D 3
#define MAP_INHERIT	0x0100	/* region is retained after exec */
E 3
.DE
The cpu-dependent size of a page is returned by the
\fIgetpagesize\fP system call:
.DS
pagesize = getpagesize();
result int pagesize;
.DE
D 3
.PP
E 3
I 3
.LP
E 3
The call:
.DS
maddr = mmap(addr, len, prot, flags, fd, pos);
result caddr_t maddr; caddr_t addr; int *len, prot, flags, fd; off_t pos;
.DE
causes the pages starting at \fIaddr\fP and continuing
for at most \fIlen\fP bytes to be mapped from the object represented by
descriptor \fIfd\fP, starting at byte offset \fIpos\fP.
The starting address of the region is returned;
for the convenience of the system,
it may differ from that supplied
unless the MAP_FIXED flag is given,
in which case the exact address will be used or the call will fail.
The actual amount mapped is returned in \fIlen\fP.
The \fIaddr\fP, \fIlen\fP, and \fIpos\fP parameters
must all be multiples of the pagesize.
I 3
D 4
A successful \fImmap\fP will \fImunmap\fP any previous mapping
E 4
I 4
A successful \fImmap\fP will delete any previous mapping
E 4
in the allocated address range.
E 3
The parameter \fIprot\fP specifies the accessibility
of the mapped pages.
The parameter \fIflags\fP specifies
the type of object to be mapped,
mapping options, and
whether modifications made to
this mapped copy of the page
are to be kept \fIprivate\fP, or are to be \fIshared\fP with
other references.
Possible types include MAP_FILE,
mapping a regular file or character-special device memory,
and MAP_ANON, which maps memory not associated with any specific file.
The file descriptor used for creating MAP_ANON regions is used only
for naming, and may be given as \-1 if no name
D 2
is associated with the region\(dd.
E 2
I 2
D 3
is associated with the region\(dg.
E 3
I 3
is associated with the region.\(dg
E 3
E 2
.FS
D 2
\(dd The current design does not allow a process
E 2
I 2
\(dg The current design does not allow a process
E 2
to specify the location of swap space.
In the future we may define an additional mapping type, MAP_SWAP,
in which the file descriptor argument specifies a file
or device to which swapping should be done.
.FE
D 3
The MAP_NOEXTEND flag prevents the mapped file from being extended
despite rounding because of the granularity of mapping.
E 3
I 3
The MAP_INHERIT flag allows a region to be inherited after an \fIexec\fP.
E 3
The MAP_HASSEMAPHORE flag allows special handling for
regions that may contain semaphores.
D 3
The MAP_INHERIT flag allows a region to be inherited after an \fIexec\fP.
E 3
.PP
A facility is provided to synchronize a mapped region with the file
it maps; the call
.DS
msync(addr, len);
caddr_t addr; int len;
.DE
writes any modified pages back to the filesystem and updates
the file modification time.
If \fIlen\fP is 0, all modified pages within the region containing \fIaddr\fP
will be flushed;
if \fIlen\fP is non-zero, only the pages containing \fIaddr\fP and \fIlen\fP
succeeding locations will be examined.
D 3
Any required invalidation of memory caches will also take place at this time.
E 3
I 3
Any required synchronization of memory caches
will also take place at this time.
E 3
Filesystem operations on a file that is mapped for shared modifications
are unpredictable except after an \fImsync\fP.
.PP
A mapping can be removed by the call
.DS
munmap(addr, len);
caddr_t addr; int len;
.DE
D 3
This call deletes the region containing the address range given,
E 3
I 3
This call deletes the mappings for the specified address range,
E 3
D 2
and causes further references to addresses within the region
E 2
I 2
and causes further references to addresses within the range
E 2
to generate invalid memory references.
.SH
Page protection control
.PP
A process can control the protection of pages using the call
.DS
mprotect(addr, len, prot);
caddr_t addr; int len, prot;
.DE
This call changes the specified pages to have protection \fIprot\fP\|.
Not all implementations will guarantee protection on a page basis;
the granularity of protection changes may be as large as an entire region.
.SH
Giving and getting advice
.PP
A process that has knowledge of its memory behavior may
use the \fImadvise\fP call:
.DS
madvise(addr, len, behav);
caddr_t addr; int len, behav;
.DE
\fIBehav\fP describes expected behavior, as given
in \fI<sys/mman.h>\fP:
.DS
.ta \w'#define\ \ 'u +\w'MADV_SEQUENTIAL\ \ 'u +\w'00\ \ \ \ 'u
#define	MADV_NORMAL	0	/* no further special treatment */
#define	MADV_RANDOM	1	/* expect random page references */
#define	MADV_SEQUENTIAL	2	/* expect sequential references */
#define	MADV_WILLNEED	3	/* will need these pages */
#define	MADV_DONTNEED	4	/* don't need these pages */
#define	MADV_SPACEAVAIL	5	/* insure that resources are reserved */
.DE
Finally, a process may obtain information about whether pages are
core resident by using the call
.DS
mincore(addr, len, vec)
caddr_t addr; int len; result char *vec;
.DE
Here the current core residency of the pages is returned
in the character array \fIvec\fP, with a value of 1 meaning
that the page is in-core.
.SH
Synchronization primitives
.PP
Primitives are provided for synchronization using semaphores in shared memory.
Semaphores must lie within a MAP_SHARED region with at least modes
PROT_READ and PROT_WRITE.
The MAP_HASSEMAPHORE flag must have been specified when the region was created.
To acquire a lock a process calls:
.DS
value = mset(sem, wait)
result int value; semaphore *sem; int wait;
.DE
\fIMset\fP indivisibly tests and sets the semaphore \fIsem\fP.
If the the previous value is zero, the process has acquired the lock
and \fImset\fP returns true immediately.
Otherwise, if the \fIwait\fP flag is zero,
failure is returned.
If \fIwait\fP is true and the previous value is non-zero,
D 2
the ``want'' flag is set and the test-and-set is retried;
if the lock is still unavailable \fImset\fP relinquishes the processor
until notified that it should retry.
E 2
I 2
\fImset\fP relinquishes the processor until notified that it should retry.
E 2
.LP
To release a lock a process calls:
.DS
mclear(sem)
semaphore *sem;
.DE
\fIMclear\fP indivisibly tests and clears the semaphore \fIsem\fP.
D 2
If the ``want'' flag is zero in the previous value,
E 2
I 2
If the ``WANT'' flag is zero in the previous value,
E 2
\fImclear\fP returns immediately.
D 2
If the ``want'' flag is non-zero in the previous value,
E 2
I 2
If the ``WANT'' flag is non-zero in the previous value,
E 2
\fImclear\fP arranges for waiting processes to retry before returning.
.PP
Two routines provide services analogous to the kernel
\fIsleep\fP and \fIwakeup\fP functions interpreted in the domain of
shared memory.
D 2
A process may relinquish the processor by calling \fImsleep\fP:
E 2
I 2
A process may relinquish the processor by calling \fImsleep\fP
with a set semaphore:
E 2
.DS
msleep(sem)
semaphore *sem;
.DE
D 2
The process will remain in a sleeping state
E 2
I 2
If the semaphore is still set when it is checked by the kernel,
the process will be put in a sleeping state
E 2
until some other process issues an \fImwakeup\fP for the same semaphore
within the region using the call:
.DS
mwakeup(sem)
semaphore *sem;
.DE
An \fImwakeup\fP may awaken all sleepers on the semaphore,
or may awaken only the next sleeper on a queue.
E 1
