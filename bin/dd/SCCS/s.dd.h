h11226
s 00001/00001/00069
d D 8.3 94/04/02 09:55:23 pendry 7 6
c add 1994 copyright
e
s 00001/00000/00069
d D 8.2 94/01/13 12:10:30 bostic 6 5
c Mike Karels at BSDI's changes for osync, to make output padding work
c correctly (this is not POSIX.2, but POSIX.2 is wrong)
e
s 00002/00002/00067
d D 8.1 93/05/31 14:22:25 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00067
d D 5.4 92/06/02 16:31:46 marc 4 3
c add byte count to stats
e
s 00032/00020/00035
d D 5.3 91/07/29 13:30:46 bostic 3 2
c fix block/unblock, ascii/ebcdic, cbs relationships (extensive)
c check for read/write/seek overflow; move stats into separate structure
c treat odd-length swab errors like truncate errors
e
s 00002/00001/00053
d D 5.2 91/07/27 10:55:18 bostic 2 1
c add Lance Visser to contrib list
e
s 00054/00000/00000
d D 5.1 91/07/26 15:42:36 bostic 1 0
c date and time created 91/07/26 15:42:36 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1991, 1993
E 7
I 7
 * Copyright (c) 1991, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
D 2
 * Keith Muller of the University of California, San Diego.
E 2
I 2
 * Keith Muller of the University of California, San Diego and Lance
 * Visser of Convex Computer Corporation.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* Input/output stream state. */
D 3
struct io_desc {
E 3
I 3
typedef struct {
E 3
	u_char	*db;			/* buffer address */
	u_char	*dbp;			/* current buffer I/O address */
	u_long	dbcnt;			/* current buffer byte count */
	int	dbrcnt;			/* last read byte count */
	u_long	dbsz;			/* buffer size */

#define	ISCHR		0x01		/* character device (warn on short) */
#define	ISPIPE		0x02		/* pipe (not truncatable) */
#define	ISTAPE		0x04		/* tape (not seekable) */
#define	NOREAD		0x08		/* not readable */
	u_int	flags;

	char 	*name;			/* name */
	int	fd;			/* file descriptor */
	u_long	offset;			/* # of blocks to skip */

	u_long	f_stats;		/* # of full blocks processed */
	u_long	p_stats;		/* # of partial blocks processed */
I 3
	u_long	s_stats;		/* # of odd swab blocks */
E 3
	u_long	t_stats;		/* # of truncations */
D 3
};
E 3
I 3
} IO;
E 3

I 3
typedef struct {
	u_long	in_full;		/* # of full input blocks */
	u_long	in_part;		/* # of partial input blocks */
	u_long	out_full;		/* # of full output blocks */
	u_long	out_part;		/* # of partial output blocks */
	u_long	trunc;			/* # of truncated records */
	u_long	swab;			/* # of odd-length swab blocks */
I 4
	u_long	bytes;			/* # of bytes written */
	time_t	start;			/* start time of dd */
E 4
} STAT;

E 3
/* Flags (in ddflags). */
D 3
#define	C_BLOCK		0x00001
#define	C_BS		0x00002
#define	C_CBS		0x00004
#define	C_COUNT		0x00008
#define	C_FILES		0x00010
#define	C_IBS		0x00020
#define	C_IF		0x00040
#define	C_LCASE		0x00080
#define	C_NOERROR	0x00100
#define	C_NOTRUNC	0x00200
#define	C_OBS		0x00400
#define	C_OF		0x00800
#define	C_SEEK		0x01000
#define	C_SKIP		0x02000
#define	C_SWAB		0x04000
#define	C_SYNC		0x08000
#define	C_UCASE		0x10000
#define	C_UNBLOCK	0x20000
E 3
I 3
#define	C_ASCII		0x00001
#define	C_BLOCK		0x00002
#define	C_BS		0x00004
#define	C_CBS		0x00008
#define	C_COUNT		0x00010
#define	C_EBCDIC	0x00020
#define	C_FILES		0x00040
#define	C_IBS		0x00080
#define	C_IF		0x00100
#define	C_LCASE		0x00200
#define	C_NOERROR	0x00400
#define	C_NOTRUNC	0x00800
#define	C_OBS		0x01000
#define	C_OF		0x02000
#define	C_SEEK		0x04000
#define	C_SKIP		0x08000
#define	C_SWAB		0x10000
#define	C_SYNC		0x20000
#define	C_UCASE		0x40000
#define	C_UNBLOCK	0x80000
I 6
#define	C_OSYNC		0x100000
E 6
E 3
E 1
