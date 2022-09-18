h12730
s 00004/00001/00062
d D 8.2 95/01/09 18:16:12 cgd 14 13
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00061
d D 8.1 93/06/02 19:54:14 bostic 13 12
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00061
d D 7.8 93/06/02 19:24:19 mckusick 12 11
c add prototypes for mlock and munlock
e
s 00019/00019/00042
d D 7.7 92/06/23 17:06:48 mckusick 11 10
c renumber constants to match Sun's naming and numbering scheme;
c eliminate MAP_FILE (make it the default as Sun does)
e
s 00004/00004/00057
d D 7.6 92/03/30 08:47:20 bostic 10 9
c fix spelling MAP_HASSEMPHORE -> MAP_HASSEMAPHORE
e
s 00001/00001/00060
d D 7.5 91/06/27 15:02:47 bostic 9 8
c mmap returns a caddr_t
e
s 00014/00000/00047
d D 7.4 91/02/22 10:31:35 donn 8 7
c Prototype declarations.  Currently we're using 'int' lengths; these ought
c to be size_t, I suppose, but we can fix that later.
e
s 00003/00004/00044
d D 7.3 91/02/15 14:30:36 bostic 7 6
c add Berkeley specific copyright notice
e
s 00038/00013/00010
d D 7.2 90/12/05 15:28:56 mckusick 6 5
c update for new VM
e
s 00001/00001/00022
d D 7.1 86/06/04 23:25:02 mckusick 5 4
c 4.3BSD release version
e
s 00007/00001/00016
d D 6.2 85/06/08 15:01:36 mckusick 4 3
c Add copyright
e
s 00000/00000/00017
d D 6.1 83/07/29 06:13:08 sam 3 2
c 4.2 distribution
e
s 00001/00009/00016
d D 4.2 82/09/04 09:28:46 root 2 1
c drop PAGESIZE as a constant
e
s 00025/00000/00000
d D 4.1 82/09/04 09:28:08 root 1 0
c date and time created 82/09/04 09:28:08 by root
e
u
U
t
T
I 1
D 2
/*	mman.h	5.1	82/07/17	*/

#if vax
#define	PAGESIZE	1024
#endif

#if sun
#define	PAGESIZE	2048
#endif
E 2
I 2
D 4
/*	%M%	%I%	%E%	*/
E 4
I 4
D 7
/*
D 5
 * Copyright (c) 1982 Regents of the University of California.
E 5
I 5
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 5
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 13
 * Copyright (c) 1982, 1986 The Regents of the University of California.
 * All rights reserved.
E 13
I 13
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 13
E 7
 *
I 6
 * %sccs.include.redist.c%
 *
E 6
 *	%W% (Berkeley) %G%
 */
E 4
E 2

D 6
/* protections are chosen from these bits, or-ed together */
#define	PROT_READ	0x1		/* pages can be read */
#define	PROT_WRITE	0x2		/* pages can be written */
#define	PROT_EXEC	0x4		/* pages can be executed */
E 6
I 6
/*
 * Protections are chosen from these bits, or-ed together
 */
I 14
#define	PROT_NONE	0x00	/* no permissions */
E 14
D 11
#define	PROT_READ	0x04	/* pages can be read */
E 11
I 11
#define	PROT_READ	0x01	/* pages can be read */
E 11
#define	PROT_WRITE	0x02	/* pages can be written */
D 11
#define	PROT_EXEC	0x01	/* pages can be executed */
E 11
I 11
#define	PROT_EXEC	0x04	/* pages can be executed */
E 11
E 6

D 6
/* sharing types: choose either SHARED or PRIVATE */
#define	MAP_SHARED	1		/* share changes */
#define	MAP_PRIVATE	2		/* changes are private */
E 6
I 6
/*
D 11
 * Flags contain mapping type, sharing type and options.
 * Mapping type; choose one
E 11
I 11
 * Flags contain sharing type and options.
 * Sharing types; choose one.
E 11
 */
D 11
#define	MAP_FILE	0x0001	/* mapped from a file or device */
#define	MAP_ANON	0x0002	/* allocated from memory, swap space */
#define	MAP_TYPE	0x000f	/* mask for type field */
E 11
I 11
#define	MAP_SHARED	0x0001	/* share changes */
#define	MAP_PRIVATE	0x0002	/* changes are private */
#define	MAP_COPY	0x0004	/* "copy" region at mmap time */
E 11
E 6

D 6
/* advice to madvise */
#define	MADV_NORMAL	0		/* no further special treatment */
#define	MADV_RANDOM	1		/* expect random page references */
#define	MADV_SEQUENTIAL	2		/* expect sequential page references */
#define	MADV_WILLNEED	3		/* will need these pages */
#define	MADV_DONTNEED	4		/* dont need these pages */
E 6
I 6
/*
D 11
 * Sharing types; choose one
E 11
I 11
 * Other flags
E 11
 */
D 11
#define	MAP_COPY	0x0020	/* "copy" region at mmap time */
#define	MAP_SHARED	0x0010	/* share changes */
#define	MAP_PRIVATE	0x0000	/* changes are private */
E 11
I 11
#define	MAP_FIXED	 0x0010	/* map addr must be exactly as requested */
#define	MAP_RENAME	 0x0020	/* Sun: rename private pages to file */
#define	MAP_NORESERVE	 0x0040	/* Sun: don't reserve needed swap area */
#define	MAP_INHERIT	 0x0080	/* region is retained after exec */
#define	MAP_NOEXTEND	 0x0100	/* for MAP_FILE, don't change file size */
#define	MAP_HASSEMAPHORE 0x0200	/* region may contain semaphores */
E 11

/*
D 11
 * Other flags
E 11
I 11
D 14
 * Mapping type; default is map from file.
E 14
I 14
 * Mapping type
E 14
E 11
 */
I 14
#define	MAP_FILE	0x0000	/* map from file (default) */
E 14
D 10
#define	MAP_FIXED	0x0100	/* map addr must be exactly as requested */
#define	MAP_NOEXTEND	0x0200	/* for MAP_FILE, don't change file size */
#define	MAP_HASSEMPHORE	0x0400	/* region may contain semaphores */
#define	MAP_INHERIT	0x0800	/* region is retained after exec */
E 10
I 10
D 11
#define	MAP_FIXED	 0x0100	/* map addr must be exactly as requested */
#define	MAP_NOEXTEND	 0x0200	/* for MAP_FILE, don't change file size */
#define	MAP_HASSEMAPHORE 0x0400	/* region may contain semaphores */
#define	MAP_INHERIT	 0x0800	/* region is retained after exec */
E 11
I 11
#define	MAP_ANON	0x1000	/* allocated from memory, swap space */
E 11
E 10

/*
 * Advice to madvise
 */
#define	MADV_NORMAL	0	/* no further special treatment */
#define	MADV_RANDOM	1	/* expect random page references */
#define	MADV_SEQUENTIAL	2	/* expect sequential page references */
#define	MADV_WILLNEED	3	/* will need these pages */
#define	MADV_DONTNEED	4	/* dont need these pages */
I 8

#ifndef KERNEL

#include <sys/cdefs.h>

__BEGIN_DECLS
/* Some of these int's should probably be size_t's */
D 9
int	mmap __P((caddr_t, int, int, int, int, off_t));
E 9
I 9
caddr_t	mmap __P((caddr_t, size_t, int, int, int, off_t));
E 9
D 11
int	mprotect __P((caddr_t, int, int));
int	munmap __P((caddr_t, int));
int	msync __P((caddr_t, int));
E 11
I 11
int	mprotect __P((caddr_t, size_t, int));
int	munmap __P((caddr_t, size_t));
int	msync __P((caddr_t, size_t));
I 12
int	mlock __P((caddr_t, size_t));
int	munlock __P((caddr_t, size_t));
I 14
int	madvise __P((caddr_t, size_t, int));
E 14
E 12
E 11
__END_DECLS

#endif /* !KERNEL */
E 8
E 6
E 1
