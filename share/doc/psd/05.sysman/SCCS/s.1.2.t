h34230
s 00001/00001/00333
d D 8.9 94/05/29 00:05:11 mckusick 22 21
c cleanup final nits
e
s 00004/00005/00330
d D 8.8 94/05/28 11:53:23 mckusick 21 20
c Mike Hibler sez, this time for sure!
e
s 00004/00002/00331
d D 8.7 94/05/26 23:02:37 mckusick 20 19
c incorporate comments from Mike Hibler
e
s 00035/00029/00298
d D 8.6 94/05/26 22:30:51 bostic 19 18
c cleanups and edits for accuracy
e
s 00015/00007/00312
d D 8.5 94/05/21 15:47:18 hibler 18 17
c corrections to mmap description, more notes about unimplemented calls
e
s 00015/00015/00304
d D 8.4 94/05/20 10:48:49 mckusick 17 16
c more updates based on input from Mike
e
s 00011/00007/00308
d D 8.3 94/05/20 06:06:53 karels 16 15
c touchups and improvements
e
s 00170/00101/00145
d D 8.2 94/05/16 10:09:35 mckusick 15 14
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00244
d D 8.1 93/06/08 18:05:14 bostic 14 13
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00242
d D 6.11 91/04/17 10:01:53 bostic 13 12
c new copyright; att/bsd/shared
e
s 00010/00001/00235
d D 6.10 86/08/25 15:05:18 mckusick 12 11
c update from discussions with shannon
e
s 00032/00026/00204
d D 6.9 86/08/15 16:01:30 mckusick 11 9
c update VM spec from discussions with Sun
e
s 00022/00019/00211
d R 6.9 86/08/11 15:16:58 mckusick 10 9
c update interface per discussion with Sun
e
s 00002/00002/00228
d D 6.8 86/05/14 14:04:10 karels 9 8
c tabs
e
s 00013/00004/00217
d D 6.7 86/05/12 11:32:56 mckusick 8 7
c leave toe-hold for MAP_SWAP; add ADV_SPACEAVAIL to reserve space
e
s 00022/00028/00199
d D 6.6 86/05/12 10:51:17 karels 7 6
c msleep stays, but after mset; caveat about mixed use
e
s 00001/00000/00226
d D 6.5 86/05/12 09:08:08 karels 6 5
c missing .DE
e
s 00084/00049/00142
d D 6.4 86/05/12 01:00:45 karels 5 4
c update, correct, rephrase and re-propose
e
s 00008/00007/00183
d D 6.3 86/05/10 16:35:55 mckusick 4 3
c add MAP_HASSEMAPHORE option
e
s 00026/00027/00164
d D 6.2 86/05/08 17:50:29 mckusick 3 2
c comments from the readers
e
s 00072/00012/00119
d D 6.1 86/05/08 12:24:47 mckusick 2 1
c update virtual memory design
e
s 00131/00000/00000
d D 5.1 86/05/08 00:02:35 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 13
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 13
I 13
D 14
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 14
I 14
D 16
.\" Copyright (c) 1983, 1993
E 16
I 16
.\" Copyright (c) 1983, 1993, 1994
E 16
.\"	The Regents of the University of California.  All rights reserved.
E 14
.\"
.\" %sccs.include.redist.roff%
E 13
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 15
.sh "Memory management\(dg
.NH 3
Text, data and stack
E 15
I 15
.Sh 2 "Memory management
.Sh 3 "Text, data, and stack
E 15
.PP
D 15
.FS
\(dg This section represents the interface planned for later
releases of the system.  Of the calls described in this section,
D 2
only \fIsbrk\fP and \fIgetpagesize\fP are included in 4.2BSD.
E 2
I 2
only \fIsbrk\fP and \fIgetpagesize\fP are included in 4.3BSD.
E 2
.FE
E 15
Each process begins execution with three logical areas of memory
D 15
called text, data and stack.  
E 15
I 15
called text, data, and stack.  
E 15
D 19
The text area is read-only and shared, while the data and stack
areas are private to the process.  Both the data and stack areas may
D 15
be extended and contracted on program request.  The call
E 15
I 15
be extended and contracted on program request.  The call:
E 19
I 19
The text area is read-only and shared,
while the data and stack areas are writable and private to the process.
Both the data and stack areas may be extended and contracted on program
request.
The call:
E 19
E 15
.DS
I 15
.Fd brk 1 "set data section size
brk(addr);
caddr_t addr;
.DE
sets the end of the data segment to the specified address.
More conveniently, the end can be extended by \fIincr\fP bytes,
and the base of the new area returned with the call:
.DS
.Fd sbrk 1 "change data section size
E 15
addr = sbrk(incr);
result caddr_t addr; int incr;
.DE
D 15
changes the size of the data area by \fIincr\fP bytes and
returns the new end of the data area, while
E 15
I 15
D 19
Application programs usually use the library routines
.Fn malloc ,
E 19
I 19
Application programs normally use the library routines
.Fn malloc
E 19
and
D 19
.Fn free
that provide a more convenient interface to
.Fn brk ,
E 19
I 19
.Fn free ,
which provide a more convenient interface than
.Fn brk
E 19
and
.Fn sbrk .
.LP
D 17
The call:
E 15
.DS
I 15
.Fd sstk 1 "change stack size
E 15
addr = sstk(incr);
result caddr_t addr; int incr;
.DE
changes the size of the stack area.
D 15
The stack area is also automatically extended as needed.
On the VAX the text and data areas are adjacent in the P0 region,
while the stack section is in the P1 region, and grows downward.
.NH 3
Mapping pages
E 15
I 15
This call is not typically used as
the stack area is also automatically extended as needed.
E 17
I 17
There is no call for extending the stack,
as it is automatically extended as needed.
E 17
.Sh 3 "Mapping pages
E 15
.PP
The system supports sharing of data between processes
by allowing pages to be mapped into memory.  These mapped
pages may be \fIshared\fP with other processes or \fIprivate\fP
to the process.
D 5
Protection and sharing options are defined in <mman.h> as:
E 5
I 5
Protection and sharing options are defined in \fI<sys/mman.h>\fP as:
E 5
.DS
D 9
._d
E 9
I 9
D 11
.ta \w'#define\ \ 'u +\w'MAP_HASSEMPHORE\ \ 'u +\w'0x0080\ \ 'u
E 11
I 11
D 15
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 11
E 9
/* protections are chosen from these bits, or-ed together */
D 3
#define	PROT_READ	0x4	/* pages can be read */
#define	PROT_WRITE	0x2	/* pages can be written */
#define	PROT_EXEC	0x1	/* pages can be executed */
E 3
I 3
#define	PROT_READ	0x04	/* pages can be read */
#define	PROT_WRITE	0x02	/* pages can be written */
#define	PROT_EXEC	0x01	/* pages can be executed */
E 15
I 15
.TS
l s
l l.
D 19
Protections are chosen from these bits, or-ed together
E 19
I 19
Protections are chosen from these bits, or-ed together:

E 19
PROT_READ	/* pages can be read */
PROT_WRITE	/* pages can be written */
PROT_EXEC	/* pages can be executed */
.TE
E 15
E 3
D 11

E 11
I 11
.DE
.DS
D 15
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 11
I 5
/* flags contain mapping type, sharing type and options */
E 5
I 2
/* mapping type; choose one */
D 3
#define MAP_FILE	0x0001	/* mapped from a file */
#define MAP_SWAP	0x0002	/* mapped to swap space */
#define MAP_MEMORY	0x0004	/* mapped to device memory */
E 3
I 3
D 5
#define MAP_FILE	0x01	/* mapped from a file */
#define MAP_SWAP	0x02	/* mapped from swap space */
D 4
#define MAP_MEMORY	0x04	/* mapped from device memory */
E 4
I 4
#define MAP_MEMORY	0x03	/* mapped from device memory */
E 5
I 5
#define MAP_FILE	0x0001	/* mapped from a file or device */
#define MAP_ANON	0x0002	/* allocated from memory, swap space */
#define MAP_TYPE	0x000f	/* mask for type field */
E 15
I 15
.TS
l s
l l.
D 19
Flags contain sharing type and options. Sharing options, choose one
E 19
I 19
Flags contain sharing type and options.  Sharing options, choose one:

E 19
MAP_SHARED	/* share changes */
MAP_PRIVATE	/* changes are private */
D 18
MAP_COPY	/* ``copy'' region at mmap time */
E 18
D 17
MAP_ANON	/* allocated from virtual memory; \fIfd\fP ignored */
E 17
.TE
E 15
E 5
E 4
E 3
D 11

E 11
I 11
.DE
.DS
D 15
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 11
E 2
D 3
/* sharing types; choose either SHARED or PRIVATE */
D 2
#define	MAP_SHARED	1	/* share changes */
#define	MAP_PRIVATE	2	/* changes are private */
E 2
I 2
#define	MAP_SHARED	0x0010	/* share changes */
#define	MAP_PRIVATE	0x0020	/* changes are private */
E 3
I 3
/* sharing types; choose one */
D 4
#define	MAP_SHARED	0x10	/* share changes */
#define	MAP_PRIVATE	0x20	/* changes are private */
E 4
I 4
D 5
#define	MAP_SHARED	0x04	/* share changes */
#define	MAP_PRIVATE	0x00	/* changes are private */
E 5
I 5
#define	MAP_SHARED	0x0010	/* share changes */
#define	MAP_PRIVATE	0x0000	/* changes are private */
E 15
I 15
.TS
l s
l l.
D 18
Other flags
E 18
I 18
D 19
Other flags \(dg
E 19
I 19
Option flags\(dg:

E 19
E 18
I 17
MAP_ANON	/* allocated from virtual memory; \fIfd\fP ignored */
E 17
MAP_FIXED	/* map addr must be exactly as requested */
MAP_NORESERVE	/* don't reserve needed swap area */
MAP_INHERIT	/* region is retained after exec */
MAP_HASSEMAPHORE	/* region may contain semaphores */
D 19
MAP_RENAME	/* Sun: rename private pages to file */
E 19
.TE
E 15
E 5
E 4
E 3
D 11

E 11
I 11
.DE
I 18
.FS
D 19
\(dg Currently only MAP_ANON and MAP_FIXED are implemented.
E 19
I 19
\(dg In 4.4BSD, only MAP_ANON and MAP_FIXED are implemented.
E 19
.FE
E 18
D 15
.DS
.ta \w'#define\ \ 'u +\w'MAP_HASSEMAPHORE\ \ 'u +\w'0x0080\ \ 'u
E 11
D 3
/* other options */
#define MAP_FIXED	0x0040	/* map segment must be allocated at addr */
#define MAP_EXTEND	0x0080	/* for MAP_FILE, the file may be extended */
E 3
I 3
/* other flags */
D 4
#define MAP_FIXED	0x40	/* map region must be allocated at addr */
#define MAP_EXTEND	0x80	/* for MAP_FILE, the file may be extended */
E 4
I 4
D 5
#define MAP_FIXED	0x10	/* map region must be allocated at addr */
#define MAP_EXTEND	0x20	/* for MAP_FILE, the file may be extended */
#define MAP_HASSEMPHORE	0x40	/* region may contain semaphores */
E 5
I 5
#define MAP_FIXED	0x0020	/* map addr must be exactly as requested */
D 11
#define MAP_NOEXTEND	0x0040	/* for MAP_FILE, don't change file size */
#define MAP_HASSEMPHORE	0x0080	/* region may contain semaphores */
#define MAP_INHERIT	0x0100	/* region is retained after exec */
E 11
I 11
#define MAP_INHERIT	0x0040	/* region is retained after exec */
#define MAP_HASSEMAPHORE	0x0080	/* region may contain semaphores */
I 12
#define MAP_NOPREALLOC	0x0100	/* do not preallocate space */
E 12
E 11
E 5
E 4
E 3
E 2
.DE
E 15
D 19
The cpu-dependent size of a page is returned by the
E 19
I 19
The size of a page is cpu-dependent, and is returned by the
E 19
D 15
\fIgetpagesize\fP system call:
E 15
I 15
.Fn sysctl
interface described in section
.Xr 1.7.1 .
D 19
For convenience and backward compatibility, the
E 19
I 19
The
E 19
.Fn getpagesize
D 19
library routine is provided:
E 19
I 19
library routine is provided for convenience and backward compatibility:
E 19
E 15
.DS
I 15
.Fd getpagesize 0 "get system page size
E 15
pagesize = getpagesize();
result int pagesize;
.DE
D 11
.PP
E 11
I 11
.LP
E 11
The call:
.DS
I 15
.Fd mmap 6 "map files or devices into memory
E 15
D 2
mmap(addr, len, prot, share, fd, pos);
caddr_t addr; int len, prot, share, fd; off_t pos;
E 2
I 2
D 3
caddr_t
maddr = mmap(addr, len, prot, share, fd, pos);
result caddr_t maddr; caddr_t addr; int *len, prot, share, fd; off_t pos;
E 3
I 3
maddr = mmap(addr, len, prot, flags, fd, pos);
D 15
result caddr_t maddr; caddr_t addr; int *len, prot, flags, fd; off_t pos;
E 15
I 15
result caddr_t maddr; caddr_t addr; size_t len; int prot, flags, fd; off_t pos;
E 15
E 3
E 2
.DE
causes the pages starting at \fIaddr\fP and continuing
D 2
for \fIlen\fP bytes to be mapped from the object represented by
descriptor \fIfd\fP, at absolute position \fIpos\fP.  The parameter
\fIshare\fP specifies whether modifications made to this mapped copy
of the page, are to be kept \fIprivate\fP, or are to be \fIshared\fP with
E 2
I 2
for at most \fIlen\fP bytes to be mapped from the object represented by
D 3
descriptor \fIfd\fP, at absolute position \fIpos\fP.
E 3
I 3
descriptor \fIfd\fP, starting at byte offset \fIpos\fP.
I 16
If \fIaddr\fP is NULL, the system picks an unused address for the region.
E 16
E 3
D 5
The starting address of the region is returned.
E 5
I 5
The starting address of the region is returned;
for the convenience of the system,
D 11
it may be different than that supplied
E 11
I 11
it may differ from that supplied
E 11
unless the MAP_FIXED flag is given,
in which case the exact address will be used or the call will fail.
E 5
D 3
The actual amount mapped is returned in len.
The parameter \fIshare\fP specifies whether modifications made to
E 3
I 3
D 15
The actual amount mapped is returned in \fIlen\fP.
E 15
D 5
The parameter \fIflags\fP specifies whether modifications made to
E 3
this mapped copy of the page,
are to be kept \fIprivate\fP, or are to be \fIshared\fP with
E 2
other references.
The parameter \fIprot\fP specifies the accessibility
of the mapped pages.
E 5
D 18
The \fIaddr\fP, \fIlen\fP, and \fIpos\fP parameters
must all be multiples of the pagesize.
E 18
I 18
D 19
The \fIaddr\fP and \fIpos\fP parameters
must be multiples of the pagesize,
\fIlen\fP will be rounded by the system as necessary.
E 19
I 19
The \fIaddr\fP parameter
must be a multiple of the pagesize (if MAP_FIXED is given).
D 20
If \fIpos\fP and \fIlen\fP are not a multiple of pagesize,
they will be rounded by the system as necessary;
E 20
I 20
D 21
The \fIpos\fP parameter must specify a file offset that is
a multiple of the pagesize.
If \fIlen\fP is not a multiple of pagesize,
it will be rounded up to a multiple of pagesize by the system;
E 20
the rounding may cause the mapped region to extend past the specified range.
E 21
I 21
If \fIpos\fP and \fIlen\fP are not a multiple of pagesize,
they will be rounded (down and up respectively)
to a page boundary by the system;
the rounding will cause the mapped region to extend past the specified range.
E 21
E 19
E 18
I 11
D 12
A successful \fImmap\fP will \fImunmap\fP any previous mapping
E 12
I 12
D 15
A successful \fImmap\fP will delete any previous mapping
E 15
I 15
A successful
.Fn mmap
will delete any previous mapping
E 15
E 12
in the allocated address range.
E 11
I 5
The parameter \fIprot\fP specifies the accessibility
of the mapped pages.
The parameter \fIflags\fP specifies
the type of object to be mapped,
mapping options, and
whether modifications made to
this mapped copy of the page
are to be kept \fIprivate\fP, or are to be \fIshared\fP with
other references.
D 15
Possible types include MAP_FILE,
mapping a regular file or character-special device memory,
E 15
I 15
D 18
Possible types include MAP_SHARED, MAP_PRIVATE, or MAP_COPY that
E 18
I 18
Possible types include MAP_SHARED or MAP_PRIVATE that
E 18
map a regular file or character-special device memory,
E 15
and MAP_ANON, which maps memory not associated with any specific file.
D 15
The file descriptor used for creating MAP_ANON regions is used only
D 8
for naming, and may be given as -1 if no name is associated with the region.
E 8
I 8
for naming, and may be given as \-1 if no name
D 11
is associated with the region\(dd.
E 11
I 11
is associated with the region.\(dd
E 11
.FS
\(dd The current design does not allow a process
to specify the location of swap space.
In the future we may define an additional mapping type, MAP_SWAP,
in which the file descriptor argument specifies a file
or device to which swapping should be done.
.FE
E 8
D 11
The MAP_NOEXTEND flag prevents the mapped file from being extended
despite rounding due to the granularity of mapping.
E 11
I 11
The MAP_INHERIT flag allows a region to be inherited after an \fIexec\fP.
E 15
I 15
D 18
The file descriptor used when creating MAP_ANON regions is ignored.
E 18
I 18
The file descriptor used when creating MAP_ANON regions is not used
D 22
and should be -1.
E 22
I 22
and should be \-1.
E 22
E 18
The MAP_INHERIT flag allows a region to be inherited after an
.Fn execve .
E 15
E 11
D 8
Other flags allow special handling for regions that may contain semaphores
or that may be inherited after an \fIexec\fP.
E 8
I 8
The MAP_HASSEMAPHORE flag allows special handling for
regions that may contain semaphores.
I 12
D 15
The MAP_NOPREALLOC flag allows processes to allocate regions whose
E 15
I 15
The MAP_NORESERVE flag allows processes to allocate regions whose
E 15
virtual address space, if fully allocated,
would exceed the available memory plus swap resources.
Such regions may get a SIGSEGV signal if they page fault and resources
are not available to service their request;
D 15
typically they would free up some resources via \fIunmap\fP so that
when they return from the signal the page
E 15
I 15
typically they would free up some resources via
D 16
.Fn unmap
E 16
I 16
.Fn munmap
E 16
so that when they return from the signal the page
E 15
D 16
fault could be successfully completed.
E 16
I 16
fault could be completed successfully.
E 16
E 12
D 11
The MAP_INHERIT flag allows a region to be inherited after an \fIexec\fP.
E 11
E 8
E 5
D 15
.PP
E 15
I 15
.LP
E 15
D 5
A process can move pages within its own memory by using the
.I mremap
call:
E 5
I 5
A facility is provided to synchronize a mapped region with the file
D 15
it maps; the call
E 15
I 15
it maps; the call:
E 15
E 5
.DS
I 15
.Fd msync 2 "synchronize a mapped region
E 15
D 3
mremap(addr, len, prot, share, fromaddr);
caddr_t addr; int len, prot, share; caddr_t fromaddr;
E 3
I 3
D 5
mremap(addr, len, prot, flags, fromaddr);
caddr_t addr; int len, prot, flags; caddr_t fromaddr;
E 3
.DE
This call maps the pages starting at \fIfromaddr\fP to the address specified
by \fIaddr\fP.
E 5
I 5
msync(addr, len);
D 15
caddr_t addr; int len;
E 15
I 15
caddr_t addr; size_t len;
E 15
I 6
.DE
E 6
D 16
writes any modified pages back to the filesystem and updates
E 16
I 16
causes any modified pages in the specified region to be synchronized
with their source and other mappings.
If necessary, it writes any modified pages back to the filesystem, and updates
E 16
the file modification time.
If \fIlen\fP is 0, all modified pages within the region containing \fIaddr\fP
will be flushed;
D 16
if \fIlen\fP is non-zero, only the pages containing \fIaddr\fP and \fIlen\fP
E 16
I 16
this usage is provisional, and may be withdrawn.
If \fIlen\fP is non-zero, only the pages containing \fIaddr\fP and \fIlen\fP
E 16
succeeding locations will be examined.
D 11
Any required invalidation of memory caches will also take place at this time.
I 7
Filesystem operations on a file which is mapped for shared modifications
E 11
I 11
Any required synchronization of memory caches
will also take place at this time.
I 19
.LP
E 19
Filesystem operations on a file that is mapped for shared modifications
E 11
D 15
are unpredictable except after an \fImsync\fP.
E 7
E 5
.PP
E 15
I 15
D 16
are unpredictable except after an
E 16
I 16
are currently unpredictable except after an
E 16
.Fn msync .
.LP
E 15
A mapping can be removed by the call
.DS
I 15
.Fd munmap 2 "remove a mapping
E 15
D 5
munmap(addr, len);
caddr_t addr; int len;
E 5
I 5
D 11
munmap(addr);
caddr_t addr;
E 11
I 11
munmap(addr, len);
D 15
caddr_t addr; int len;
E 15
I 15
caddr_t addr; size_t len;
E 15
E 11
E 5
.DE
D 2
This causes further references to these pages to refer to private
pages initialized to zero.
E 2
I 2
D 5
This call causes further references to these pages
E 5
I 5
D 11
This call deletes the region containing the address given,
and causes further references to addresses within the region
E 11
I 11
This call deletes the mappings for the specified address range,
and causes further references to addresses within the range
E 11
E 5
to generate invalid memory references.
D 3
If the segment is mapped MAP_FILE with mode PROT_WRITE,
E 3
I 3
D 5
If the region is mapped MAP_FILE with mode PROT_WRITE,
E 3
the file is truncated to the length specified by \fIlen\fP.
E 5
E 2
D 15
.NH 3
Page protection control
.PP
A process can control the protection of pages using the call
E 15
I 15
.Sh 3 "Page protection control
.LP
A process can control the protection of pages using the call:
E 15
.DS
I 15
.Fd mprotect 3 "control the protection of pages
E 15
mprotect(addr, len, prot);
D 15
caddr_t addr; int len, prot;
E 15
I 15
caddr_t addr; size_t len; int prot;
E 15
.DE
This call changes the specified pages to have protection \fIprot\fP\|.
I 5
Not all implementations will guarantee protection on a page basis;
the granularity of protection changes may be as large as an entire region.
E 5
D 15
.NH 3
Giving and getting advice
.PP
E 15
I 15
.Sh 3 "Giving and getting advice
.LP
E 15
A process that has knowledge of its memory behavior may
D 15
use the \fImadvise\fP call:
E 15
I 15
use the
D 17
.Fn madvise
E 17
I 17
.Fn madvise \(dg
E 17
call:
I 17
.FS
\(dg The entry point for this system call is defined,
but is not implemented,
so currently always returns with the error ``Operation not supported.''
.FE
E 17
E 15
.DS
I 15
.Fd madvise 3 "give advise about use of memory
E 15
madvise(addr, len, behav);
D 15
caddr_t addr; int len, behav;
E 15
I 15
caddr_t addr; size_t len; int behav;
E 15
.DE
\fIBehav\fP describes expected behavior, as given
D 7
in <mman.h>:
E 7
I 7
in \fI<sys/mman.h>\fP:
E 7
.DS
D 9
._d
E 9
I 9
D 15
.ta \w'#define\ \ 'u +\w'MADV_SEQUENTIAL\ \ 'u +\w'00\ \ \ \ 'u
E 9
#define	MADV_NORMAL	0	/* no further special treatment */
#define	MADV_RANDOM	1	/* expect random page references */
#define	MADV_SEQUENTIAL	2	/* expect sequential references */
#define	MADV_WILLNEED	3	/* will need these pages */
#define	MADV_DONTNEED	4	/* don't need these pages */
I 8
#define	MADV_SPACEAVAIL	5	/* insure that resources are reserved */
E 15
I 15
.TS
l l.
MADV_NORMAL	/* no further special treatment */
MADV_RANDOM	/* expect random page references */
MADV_SEQUENTIAL	/* expect sequential references */
MADV_WILLNEED	/* will need these pages */
MADV_DONTNEED	/* don't need these pages */
D 16
MADV_SPACEAVAIL	/* insure that resources are reserved */
E 16
I 16
D 19
MADV_SPACEAVAIL	/* ensure that resources are reserved */
E 19
E 16
.TE
E 15
E 8
.DE
D 15
Finally, a process may obtain information about whether pages are
core resident by using the call
E 15
I 15
D 17
A process may obtain information about whether pages are
core resident by using the call:
E 17
I 17
The
.Fn mincore \(dg
function allows a process to obtain information
about whether pages are memory resident:
E 17
E 15
.DS
I 15
.Fd mincore 3 "get advise about use of memory
E 15
D 19
mincore(addr, len, vec)
caddr_t addr; int len; result char *vec;
E 19
I 19
mincore(addr, len, vec);
caddr_t addr; size_t len; result char *vec;
E 19
.DE
D 17
Here the current core residency of the pages is returned
E 17
I 17
Here the current memory residency of the pages is returned
E 17
in the character array \fIvec\fP, with a value of 1 meaning
D 17
that the page is in-core.
E 17
I 17
that the page is in-memory.
E 17
I 2
D 15
.NH 3
Synchronization primitives
.PP
E 15
I 15
.Fn Mincore
provides only transient information about page residency.
Real-time processes that need guaranteed residence over time
can use the call:
.DS
.Fd mlock  2 "lock physical pages in memory
mlock(addr, len);
caddr_t addr; size_t len;
.DE
This call locks the pages for the specified address range into memory
(paging them in if necessary)
ensuring that further references to addresses within the range
will never generate page faults.
The amount of memory that may be locked is controlled by a resource limit,
see section
.Xr 1.6.3 .
When the memory is no longer critical it can be unlocked using:
.DS
.Fd munlock  2 "unlock physical pages in memory
munlock(addr, len);
caddr_t addr; size_t len;
.DE
After the
.Fn munlock
call, the pages in the specified address range are still accessible
D 19
but may be paged out if memory is short and they are not accessed.
E 19
I 19
but may be paged out if memory is needed and they are not accessed.
E 19
.Sh 3 "Synchronization primitives
E 15
I 5
D 7
.if \n(sw=0 .ig sw
E 5
Two routines provide services analogous to the kernel
D 3
sleep and wakeup functions interpreted in the domain of
E 3
I 3
\fIsleep\fP and \fIwakeup\fP functions interpreted in the domain of
E 3
shared memory.
D 3
A process may relinquish the processor by calling msleep:
E 3
I 3
A process may relinquish the processor by calling \fImsleep\fP:
E 3
.DS
D 5
msleep(addr)
caddr_t addr;
E 5
I 5
msleep(sem)
semaphore *sem;
E 5
.DE
D 3
Addr must lie within a MAP_SHARED segment with at least modes
E 3
I 3
D 5
\fIAddr\fP must lie within a MAP_SHARED region with at least modes
E 5
I 5
\fISem\fP must lie within a MAP_SHARED region with at least modes
E 5
E 3
PROT_READ and PROT_WRITE.
I 4
The MAP_HASSEMAPHORE flag must have been specified when the region was created.
E 4
The process will remain in a sleeping state
D 5
until some other process issues an \fImwakeup\fP for the same byte
E 5
I 5
until some other process issues an \fImwakeup\fP for the same semaphore
E 5
D 4
within the region (possibly from a different virtual address)
using the call:
E 4
I 4
within the region using the call:
E 4
.DS
D 5
mwakeup(addr)
caddr_t addr;
E 5
I 5
mwakeup(sem)
semaphore *sem;
E 5
.DE
I 5
An \fImwakeup\fP may awaken all sleepers on the semaphore,
or may awaken only the next sleeper on a queue.
E 5
.PP
To avoid system calls for the usual case of an uncontested lock,
D 5
library routines are provided to acquire and release locks.
E 5
I 5
routines are provided to acquire and release locks.
.sw
.if \n(sw .ig sw
E 7
D 18
Primitives are provided for synchronization using semaphores in shared memory.
E 18
I 18
Primitives are provided for synchronization using semaphores
in shared memory.\(dd
.FS
\(dd All currently unimplemented, no entry points exists.
.FE
E 18
I 15
These primitives are expected to be superseded by the semaphore
D 19
interface being specified by the POSIX Pthread standard.
E 19
I 19
interface being specified by the POSIX 1003 Pthread standard.
E 19
They are provided as an efficient interim solution.
Application programmers are encouraged to use the Pthread interface
when it becomes available.
.PP
E 15
Semaphores must lie within a MAP_SHARED region with at least modes
PROT_READ and PROT_WRITE.
The MAP_HASSEMAPHORE flag must have been specified when the region was created.
D 7
.sw
E 7
E 5
To acquire a lock a process calls:
.DS
I 15
.Fd mset 2 "acquire and set a semaphore
E 15
D 5
mset(addr)
caddr_t addr;
E 5
I 5
D 19
value = mset(sem, wait)
E 19
I 19
value = mset(sem, wait);
E 19
result int value; semaphore *sem; int wait;
E 5
.DE
D 3
\fIMset\fP indivisibly tests and sets the memory location addr.
E 3
I 3
D 5
\fIMset\fP indivisibly tests and sets the memory location \fIaddr\fP.
E 5
I 5
D 15
\fIMset\fP indivisibly tests and sets the semaphore \fIsem\fP.
E 5
E 3
If the the previous value is zero, the process has acquired the lock
D 5
and \fImset\fP returns immediately.
If the previous value is non-zero, the ``want'' bit is set and
the test-and-set is retried;
if the lock is still unavailable \fImset\fP calls \fImsleep\fP and tries again.
E 5
I 5
and \fImset\fP returns true immediately.
E 15
I 15
.Fn Mset
indivisibly tests and sets the semaphore \fIsem\fP.
D 19
If the the previous value is zero, the process has acquired the lock and
E 19
I 19
If the previous value is zero, the process has acquired the lock and
E 19
.Fn mset
returns true immediately.
E 15
Otherwise, if the \fIwait\fP flag is zero,
failure is returned.
If \fIwait\fP is true and the previous value is non-zero,
D 11
the ``want'' flag is set and the test-and-set is retried;
if the lock is still unavailable \fImset\fP relinquishes the processor
until notified that it should retry.
E 11
I 11
D 15
\fImset\fP relinquishes the processor until notified that it should retry.
E 15
I 15
.Fn mset
relinquishes the processor until notified that it should retry.
E 15
E 11
E 5
D 3
.PP
E 3
I 3
.LP
E 3
To release a lock a process calls:
.DS
I 15
.Fd mclear 2 "release a semaphore and awaken waiting processes
E 15
D 5
mclear(addr)
caddr_t addr;
E 5
I 5
D 19
mclear(sem)
E 19
I 19
mclear(sem);
E 19
semaphore *sem;
E 5
.DE
D 3
\fIMclear\fP indivisibly tests and clears the memory location addr.
E 3
I 3
D 5
\fIMclear\fP indivisibly tests and clears the memory location \fIaddr\fP.
E 3
If the ``want'' bit is zero in the previous value,
E 5
I 5
D 15
\fIMclear\fP indivisibly tests and clears the semaphore \fIsem\fP.
E 15
I 15
.Fn Mclear
indivisibly tests and clears the semaphore \fIsem\fP.
E 15
D 11
If the ``want'' flag is zero in the previous value,
E 11
I 11
If the ``WANT'' flag is zero in the previous value,
E 11
E 5
D 15
\fImclear\fP returns immediately.
E 15
I 15
.Fn mclear
returns immediately.
E 15
D 5
If the ``want'' bit is non-zero in the previous value,
\fImclear\fP calls \fImwakeup\fP before returning.
E 5
I 5
D 11
If the ``want'' flag is non-zero in the previous value,
E 11
I 11
If the ``WANT'' flag is non-zero in the previous value,
E 11
D 15
\fImclear\fP arranges for waiting processes to retry before returning.
E 15
I 15
.Fn mclear
arranges for waiting processes to retry before returning.
E 15
I 7
.PP
Two routines provide services analogous to the kernel
D 15
\fIsleep\fP and \fIwakeup\fP functions interpreted in the domain of
shared memory.
D 11
A process may relinquish the processor by calling \fImsleep\fP:
E 11
I 11
A process may relinquish the processor by calling \fImsleep\fP
E 15
I 15
.Fn sleep
and
.Fn wakeup
functions interpreted in the domain of shared memory.
A process may relinquish the processor by calling
.Fn msleep
E 15
with a set semaphore:
E 11
.DS
I 15
.Fd msleep 1 "wait for a semaphore
E 15
D 19
msleep(sem)
E 19
I 19
msleep(sem);
E 19
semaphore *sem;
.DE
D 11
The process will remain in a sleeping state
E 11
I 11
If the semaphore is still set when it is checked by the kernel,
the process will be put in a sleeping state
E 11
D 15
until some other process issues an \fImwakeup\fP for the same semaphore
within the region using the call:
E 15
I 15
until some other process issues an
.Fn mwakeup
for the same semaphore within the region using the call:
E 15
.DS
I 15
.Fd mwakeup 1 "awaken process(es) sleeping on a semaphore
E 15
D 19
mwakeup(sem)
E 19
I 19
mwakeup(sem);
E 19
semaphore *sem;
.DE
D 15
An \fImwakeup\fP may awaken all sleepers on the semaphore,
E 15
I 15
An
.Fn mwakeup
may awaken all sleepers on the semaphore,
E 15
or may awaken only the next sleeper on a queue.
D 8
.PP
E 8
E 7
E 5
E 2
E 1
