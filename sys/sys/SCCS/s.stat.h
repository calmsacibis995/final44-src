h25090
s 00003/00003/00179
d D 8.12 95/06/16 13:16:02 mckusick 44 43
c make consistent with time.h
e
s 00011/00000/00171
d D 8.11 95/05/03 22:14:17 mckusick 43 42
c POSIX compliance (from karels)
e
s 00002/00002/00169
d D 8.10 95/01/09 18:16:22 cgd 42 41
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00169
d D 8.9 94/08/17 22:02:55 mckusick 41 40
c wrong check value for FIFO
e
s 00004/00000/00167
d D 8.8 94/08/10 23:19:51 pendry 40 39
c add whiteout type; add opaque directory flag
e
s 00026/00026/00141
d D 8.7 94/07/10 23:09:51 bostic 39 38
c changes for 64-bit machines
e
s 00005/00004/00162
d D 8.6 94/03/08 11:09:06 bostic 38 37
c Mike's changes so that S_ISFIFO and S_ISSOCK return true for both
c FIFO's and sockets
e
s 00005/00000/00161
d D 8.5 94/01/21 17:25:19 bostic 37 36
c add USL's copyright notice
e
s 00003/00003/00158
d D 8.4 94/01/04 16:16:49 bostic 36 35
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00006/00000/00155
d D 8.3 94/01/04 15:51:18 bostic 35 34
c clean up for POSIX 1003.1 standard
e
s 00004/00000/00151
d D 8.2 93/09/05 09:42:51 bostic 34 33
c add ACCESSPERMS, ALLPERMS; Cleanups for 4.4BSD-Lite
e
s 00002/00002/00149
d D 8.1 93/06/02 19:55:29 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00002/00147
d D 7.20 93/05/10 15:01:20 mckusick 32 31
c make definitions of user and super-user changeable flags
e
s 00011/00008/00138
d D 7.19 93/03/04 15:49:14 bostic 31 30
c rename file flags to UF_* and SF_*, minimize name space problems
e
s 00008/00007/00138
d D 7.18 93/03/04 09:53:23 bostic 30 29
c I messed up the #ifdef's for _POSIX_SOURCE
e
s 00018/00016/00127
d D 7.17 93/03/03 17:56:29 bostic 29 28
c prototype chflags/fchflags, minor reorganization
e
s 00009/00001/00134
d D 7.16 93/02/28 23:24:29 mckusick 28 27
c add IMMUTABLE AND APPENDONLY
e
s 00009/00009/00126
d D 7.15 93/02/10 20:24:15 bostic 27 26
c u_short, u_long aren't POSIX, so may not be typedef'd
e
s 00014/00026/00121
d D 7.14 92/05/31 21:18:58 mckusick 26 25
c qstat becomes the default; return timespec rather than timeval
e
s 00041/00008/00106
d D 7.13 92/05/13 14:43:45 mckusick 25 24
c new stat structure reflecting 64-bit file sizes, 32-bit uid, gid, and dev's
e
s 00012/00000/00102
d D 7.12 91/12/12 16:05:24 mckusick 24 23
c add file flags definitions
e
s 00001/00000/00101
d D 7.11 91/03/03 16:28:07 donn 23 22
c Put the fchmod() declarationwith the chmod() declaration.
e
s 00003/00000/00098
d D 7.10 91/02/22 11:20:43 donn 22 21
c One more prototype declaration.
e
s 00010/00015/00088
d D 7.9 91/02/05 17:03:41 bostic 21 20
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00004/00001/00099
d D 7.8 91/01/17 15:56:46 bostic 20 19
c add #define for 0666
e
s 00002/00000/00098
d D 7.7 90/10/31 11:17:14 bostic 19 18
c don't include function prototypes in the kernel
e
s 00001/00001/00097
d D 7.6 90/05/29 19:29:52 bostic 18 17
c C++ needs prototypes, too
e
s 00018/00012/00080
d D 7.5 90/05/27 11:38:29 bostic 17 16
c function prototypes for POSIX 1003.1
e
s 00082/00035/00010
d D 7.4 90/03/14 17:06:59 bostic 16 15
c redo for/from POSIX 1003.1; add Berkeley specific copyright notice
e
s 00002/00000/00043
d D 7.3 89/08/16 18:38:51 mckusick 15 14
c add S_BLKSIZE defining size of blocks in stat structure
e
s 00002/00001/00041
d D 7.2 89/06/06 17:50:06 mckusick 14 13
c last two spares defined as flags and generation number
e
s 00001/00001/00041
d D 7.1 86/06/04 23:28:23 mckusick 13 12
c 4.3BSD release version
e
s 00002/00002/00040
d D 6.3 85/10/28 15:04:34 karels 12 11
c use proper types for uids, gids
e
s 00007/00001/00035
d D 6.2 85/06/08 15:08:32 mckusick 11 10
c Add copyright
e
s 00000/00000/00036
d D 6.1 83/07/29 06:14:10 sam 10 9
c 4.2 distribution
e
s 00002/00001/00034
d D 4.7 83/05/21 16:02:03 sam 9 8
c i_blocks (from kre)
e
s 00004/00000/00031
d D 4.6 82/12/23 14:34:04 sam 8 7
c put some space in there for time changes and such
e
s 00001/00000/00030
d D 4.5 82/11/13 23:08:47 sam 7 6
c merge 4.1b and 4.1c
e
s 00001/00000/00029
d D 4.4 82/04/19 19:27:08 mckusic 6 5
c merge in the new file system
e
s 00001/00002/00028
d D 4.3 82/02/27 14:56:17 wnj 5 4
c symbolic links
e
s 00001/00001/00029
d D 4.2 81/02/19 21:42:14 wnj 4 3
c %G%->%E%
e
s 00000/00000/00030
d D 4.1 80/11/09 17:01:42 bill 3 2
c stamp for 4bsd
e
s 00001/00001/00029
d D 3.2 80/06/07 03:00:46 bill 2 1
c %H%->%G%
e
s 00030/00000/00000
d D 3.1 80/04/09 16:25:22 bill 1 0
c date and time created 80/04/09 16:25:22 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 4
/*	%M%	%I%	%G%	*/
E 4
I 4
D 11
/*	%M%	%I%	%E%	*/
E 11
I 11
D 17
/*
E 17
I 17
/*-
E 17
D 13
 * Copyright (c) 1982 Regents of the University of California.
E 13
I 13
D 16
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 13
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 16
I 16
D 33
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 37
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 37
E 33
E 16
 *
I 16
D 17
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 17
I 17
 * %sccs.include.redist.c%
E 17
 *
E 16
 *	%W% (Berkeley) %G%
 */
E 11
E 4
E 2

I 35
D 36
#ifndef _STAT_H_
#define	_STAT_H_
E 36
I 36
#ifndef _SYS_STAT_H_
#define	_SYS_STAT_H_
E 36

E 35
I 25
D 26
#ifdef KERNEL
struct ostat
#else
E 26
#include <sys/time.h>
E 25
D 16
struct	stat
E 16
I 16
D 26
struct stat
I 25
#endif
E 25
E 16
{
E 26
I 26

I 35
#ifndef _POSIX_SOURCE
E 35
struct ostat {
E 26
I 25
D 27
	u_short	st_dev;			/* inode's device */
E 27
I 27
D 39
	unsigned short	st_dev;		/* inode's device */
E 27
	ino_t	st_ino;			/* inode's number */
	mode_t	st_mode;		/* inode protection mode */
	nlink_t	st_nlink;		/* number of hard links */
D 27
	u_short	st_uid;			/* user ID of the file's owner */
	u_short	st_gid;			/* group ID of the file's group */
	u_short	st_rdev;		/* device type */
E 27
I 27
	unsigned short	st_uid;		/* user ID of the file's owner */
	unsigned short	st_gid;		/* group ID of the file's group */
	unsigned short	st_rdev;	/* device type */
E 27
	long	st_size;		/* file size, in bytes */
E 39
I 39
	u_int16_t st_dev;		/* inode's device */
	ino_t	  st_ino;		/* inode's number */
	mode_t	  st_mode;		/* inode protection mode */
	nlink_t	  st_nlink;		/* number of hard links */
	u_int16_t st_uid;		/* user ID of the file's owner */
	u_int16_t st_gid;		/* group ID of the file's group */
	u_int16_t st_rdev;		/* device type */
	int32_t	  st_size;		/* file size, in bytes */
E 39
D 26
	struct	timeval st_atimeval;	/* time of last access */
	struct	timeval st_mtimeval;	/* time of last data modification */
	struct	timeval st_ctimeval;	/* time of last file status change */
E 26
I 26
	struct	timespec st_atimespec;	/* time of last access */
	struct	timespec st_mtimespec;	/* time of last data modification */
	struct	timespec st_ctimespec;	/* time of last file status change */
E 26
D 39
	long	st_blksize;		/* optimal blocksize for I/O */
	long	st_blocks;		/* blocks allocated for file */
D 27
	u_long	st_flags;		/* user defined flags for file */
	u_long	st_gen;			/* file generation number */
E 27
I 27
	unsigned long	st_flags;	/* user defined flags for file */
	unsigned long	st_gen;		/* file generation number */
E 39
I 39
	int32_t	  st_blksize;		/* optimal blocksize for I/O */
	int32_t	  st_blocks;		/* blocks allocated for file */
	u_int32_t st_flags;		/* user defined flags for file */
	u_int32_t st_gen;		/* file generation number */
E 39
E 27
};
I 35
#endif /* !_POSIX_SOURCE */
E 35

D 26
#ifdef KERNEL
struct stat
#else
struct qstat
#endif
{
E 26
I 26
struct stat {
E 26
E 25
D 16
	dev_t	st_dev;
	ino_t	st_ino;
	unsigned short st_mode;
	short	st_nlink;
D 12
	short	st_uid;
	short	st_gid;
E 12
I 12
	uid_t	st_uid;
	gid_t	st_gid;
E 12
	dev_t	st_rdev;
	off_t	st_size;
	time_t	st_atime;
I 8
	int	st_spare1;
E 8
	time_t	st_mtime;
I 8
	int	st_spare2;
E 8
	time_t	st_ctime;
I 8
	int	st_spare3;
E 8
I 6
	long	st_blksize;
I 8
D 9
	long	st_spare4[3];
E 9
I 9
	long	st_blocks;
D 14
	long	st_spare4[2];
E 14
I 14
	u_long	st_flags;
	u_long	st_gen;
E 16
I 16
D 39
	dev_t	st_dev;			/* inode's device */
	ino_t	st_ino;			/* inode's number */
	mode_t	st_mode;		/* inode protection mode */
	nlink_t	st_nlink;		/* number of hard links */
	uid_t	st_uid;			/* user ID of the file's owner */
	gid_t	st_gid;			/* group ID of the file's group */
	dev_t	st_rdev;		/* device type */
E 39
I 39
	dev_t	  st_dev;		/* inode's device */
	ino_t	  st_ino;		/* inode's number */
	mode_t	  st_mode;		/* inode protection mode */
	nlink_t	  st_nlink;		/* number of hard links */
	uid_t	  st_uid;		/* user ID of the file's owner */
	gid_t	  st_gid;		/* group ID of the file's group */
	dev_t	  st_rdev;		/* device type */
I 43
#ifndef _POSIX_SOURCE
E 43
E 39
I 25
D 26
	struct	timeval st_atimeval;	/* time of last access */
	struct	timeval st_mtimeval;	/* time of last data modification */
	struct	timeval st_ctimeval;	/* time of last file status change */
E 26
I 26
	struct	timespec st_atimespec;	/* time of last access */
	struct	timespec st_mtimespec;	/* time of last data modification */
	struct	timespec st_ctimespec;	/* time of last file status change */
I 43
#else
	time_t	  st_atime;		/* time of last access */
D 44
	int32_t	  st_atimensec;		/* nsec of last access */
E 44
I 44
	long	  st_atimensec;		/* nsec of last access */
E 44
	time_t	  st_mtime;		/* time of last data modification */
D 44
	int32_t	  st_mtimensec;		/* nsec of last data modification */
E 44
I 44
	long	  st_mtimensec;		/* nsec of last data modification */
E 44
	time_t	  st_ctime;		/* time of last file status change */
D 44
	int32_t	  st_ctimensec;		/* nsec of last file status change */
E 44
I 44
	long	  st_ctimensec;		/* nsec of last file status change */
E 44
#endif
E 43
E 26
E 25
D 39
	off_t	st_size;		/* file size, in bytes */
D 25
	time_t	st_atime;		/* time of last access */
	long	st_spare1;
	time_t	st_mtime;		/* time of last data modification */
	long	st_spare2;
	time_t	st_ctime;		/* time of last file status change */
	long	st_spare3;
	long	st_blksize;		/* optimal blocksize for I/O */
	long	st_blocks;		/* blocks allocated for file */
E 25
I 25
	quad_t	st_blocks;		/* blocks allocated for file */
D 27
	u_long	st_blksize;		/* optimal blocksize for I/O */
E 25
	u_long	st_flags;		/* user defined flags for file */
	u_long	st_gen;			/* file generation number */
E 27
I 27
	unsigned long	st_blksize;	/* optimal blocksize for I/O */
	unsigned long	st_flags;	/* user defined flags for file */
	unsigned long	st_gen;		/* file generation number */
E 27
I 25
D 26
	long	st_spare[4];
E 26
I 26
	long	st_lspare;
	quad_t	st_qspare[2];
E 39
I 39
	off_t	  st_size;		/* file size, in bytes */
D 42
	quad_t	  st_blocks;		/* blocks allocated for file */
E 42
I 42
	int64_t	  st_blocks;		/* blocks allocated for file */
E 42
	u_int32_t st_blksize;		/* optimal blocksize for I/O */
	u_int32_t st_flags;		/* user defined flags for file */
	u_int32_t st_gen;		/* file generation number */
	int32_t	  st_lspare;
D 42
	quad_t	  st_qspare[2];
E 42
I 42
	int64_t	  st_qspare[2];
E 42
E 39
E 26
E 25
E 16
E 14
E 9
E 8
E 6
};
I 43
#ifndef _POSIX_SOURCE
E 43
I 25
D 26
#define st_atime st_atimeval.tv_sec
#define st_mtime st_mtimeval.tv_sec
#define st_ctime st_ctimeval.tv_sec
E 26
I 26
#define st_atime st_atimespec.ts_sec
#define st_mtime st_mtimespec.ts_sec
#define st_ctime st_ctimespec.ts_sec
I 43
#endif
E 43
E 26
E 25

D 16
#define	S_IFMT	0170000		/* type of file */
#define		S_IFDIR	0040000	/* directory */
#define		S_IFCHR	0020000	/* character special */
#define		S_IFBLK	0060000	/* block special */
#define		S_IFREG	0100000	/* regular */
D 5
#define		S_IFMPC	0030000	/* multiplexed char special */
#define		S_IFMPB	0070000	/* multiplexed block special */
E 5
I 5
#define		S_IFLNK	0120000	/* symbolic link */
I 7
#define		S_IFSOCK 0140000/* socket */
E 7
E 5
#define	S_ISUID	0004000		/* set user id on execution */
#define	S_ISGID	0002000		/* set group id on execution */
#define	S_ISVTX	0001000		/* save swapped text even after use */
#define	S_IREAD	0000400		/* read permission, owner */
#define	S_IWRITE 0000200	/* write permission, owner */
#define	S_IEXEC	0000100		/* execute/search permission, owner */
E 16
I 16
#define	S_ISUID	0004000			/* set user id on execution */
#define	S_ISGID	0002000			/* set group id on execution */
#ifndef _POSIX_SOURCE
#define	S_ISTXT	0001000			/* sticky bit */
#endif
E 16
I 15

I 16
#define	S_IRWXU	0000700			/* RWX mask for owner */
#define	S_IRUSR	0000400			/* R for owner */
#define	S_IWUSR	0000200			/* W for owner */
#define	S_IXUSR	0000100			/* X for owner */

#ifndef _POSIX_SOURCE
#define	S_IREAD		S_IRUSR
#define	S_IWRITE	S_IWUSR
#define	S_IEXEC		S_IXUSR
#endif

#define	S_IRWXG	0000070			/* RWX mask for group */
#define	S_IRGRP	0000040			/* R for group */
#define	S_IWGRP	0000020			/* W for group */
#define	S_IXGRP	0000010			/* X for group */

#define	S_IRWXO	0000007			/* RWX mask for other */
#define	S_IROTH	0000004			/* R for other */
#define	S_IWOTH	0000002			/* W for other */
#define	S_IXOTH	0000001			/* X for other */

I 29
D 30
					/* 0666 */
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

E 30
E 29
#ifndef _POSIX_SOURCE
D 30
#define	S_IFMT	 0170000		/* type of file */
E 30
I 30
#define	S_IFMT	 0170000		/* type of file mask */
E 30
#define	S_IFIFO	 0010000		/* named pipe (fifo) */
#define	S_IFCHR	 0020000		/* character special */
#define	S_IFDIR	 0040000		/* directory */
#define	S_IFBLK	 0060000		/* block special */
#define	S_IFREG	 0100000		/* regular */
#define	S_IFLNK	 0120000		/* symbolic link */
#define	S_IFSOCK 0140000		/* socket */
I 40
#define	S_IFWHT  0160000		/* whiteout */
E 40
D 30

E 30
#define	S_ISVTX	 0001000		/* save swapped text even after use */
I 30
#endif
E 30

E 16
D 20
#define S_BLKSIZE	512	/* block size used in the stat struct */
E 20
I 20
D 30
#define S_BLKSIZE	512		/* block size used in the stat struct */

E 30
D 29
					/* 0666 */
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
E 29
I 29
#define	S_ISDIR(m)	((m & 0170000) == 0040000)	/* directory */
#define	S_ISCHR(m)	((m & 0170000) == 0020000)	/* char special */
#define	S_ISBLK(m)	((m & 0170000) == 0060000)	/* block special */
#define	S_ISREG(m)	((m & 0170000) == 0100000)	/* regular file */
D 38
#define	S_ISFIFO(m)	((m & 0170000) == 0010000)	/* fifo */
E 38
I 38
D 41
#define	S_ISFIFO(m)	((m & 0170000) == 0100000 || \
E 41
I 41
#define	S_ISFIFO(m)	((m & 0170000) == 0010000 || \
E 41
			 (m & 0170000) == 0140000)	/* fifo or socket */
E 38
#ifndef _POSIX_SOURCE
#define	S_ISLNK(m)	((m & 0170000) == 0120000)	/* symbolic link */
D 38
#define	S_ISSOCK(m)	((m & 0170000) == 0140000)	/* socket */
E 38
I 38
D 41
#define	S_ISSOCK(m)	((m & 0170000) == 0100000 || \
E 41
I 41
#define	S_ISSOCK(m)	((m & 0170000) == 0010000 || \
E 41
			 (m & 0170000) == 0140000)	/* fifo or socket */
I 40
#define	S_ISWHT(m)	((m & 0170000) == 0160000)	/* whiteout */
E 40
E 38
#endif
I 30

#ifndef _POSIX_SOURCE
I 34
D 38
							/* 0777 */
#define	ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)
E 38
I 38
#define	ACCESSPERMS	(S_IRWXU|S_IRWXG|S_IRWXO)	/* 0777 */
E 38
							/* 7777 */
#define	ALLPERMS	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
E 34
							/* 0666 */
#define	DEFFILEMODE	(S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

#define S_BLKSIZE	512		/* block size used in the stat struct */
E 30
E 29
I 24

/*
 * Definitions of flags stored in file flags word.
 *
D 29
 * Low 16-bits owner setable.
E 29
I 29
D 32
 * Low 16-bits: super-user and owner settable.
E 32
I 32
 * Super-user and owner changeable flags.
E 32
E 29
 */
I 32
#define	UF_SETTABLE	0x0000ffff	/* mask of owner changeable flags */
E 32
D 31
#define	NODUMP		0x00000001	/* do not dump file */
D 28
#define	IMMUTABLE	0x00000002	/* file may not be changed */
E 28
I 28
#define	USR_IMMUTABLE	0x00000002	/* file may not be changed */
#define	USR_APPEND	0x00000004	/* writes to file may only append */
E 31
I 31
#define	UF_NODUMP	0x00000001	/* do not dump file */
#define	UF_IMMUTABLE	0x00000002	/* file may not be changed */
#define	UF_APPEND	0x00000004	/* writes to file may only append */
I 40
#define UF_OPAQUE	0x00000008	/* directory is opaque wrt. union */
E 40
E 31
E 28
/*
D 29
 * High 16-bits only super-user setable.
E 29
I 29
D 32
 * High 16-bits: super-user settable.
E 32
I 32
 * Super-user changeable flags.
E 32
E 29
 */
I 32
#define	SF_SETTABLE	0xffff0000	/* mask of superuser changeable flags */
E 32
D 31
#define	ARCHIVED	0x00010000	/* file is archived */
I 28
#define	SYS_IMMUTABLE	0x00020000	/* file may not be changed */
#define	SYS_APPEND	0x00040000	/* writes to file may only append */
E 31
I 31
#define	SF_ARCHIVED	0x00010000	/* file is archived */
#define	SF_IMMUTABLE	0x00020000	/* file may not be changed */
#define	SF_APPEND	0x00040000	/* writes to file may only append */

#ifdef KERNEL
E 31
/*
 * Shorthand abbreviations of above.
 */
I 40
#define	OPAQUE		(UF_OPAQUE)
E 40
D 31
#define	IMMUTABLE	(USR_IMMUTABLE | SYS_IMMUTABLE)
#define	APPEND		(USR_APPEND | SYS_APPEND)
E 31
I 31
#define	APPEND		(UF_APPEND | SF_APPEND)
#define	IMMUTABLE	(UF_IMMUTABLE | SF_IMMUTABLE)
#endif
E 31
E 28
E 24
E 20
I 16
#endif

D 29
#define	S_ISDIR(m)	((m & 0170000) == 0040000)	/* directory */
#define	S_ISCHR(m)	((m & 0170000) == 0020000)	/* char special */
#define	S_ISBLK(m)	((m & 0170000) == 0060000)	/* block special */
#define	S_ISREG(m)	((m & 0170000) == 0100000)	/* regular file */
#define	S_ISFIFO(m)	((m & 0170000) == 0010000)	/* fifo */
#ifndef _POSIX_SOURCE
#define	S_ISLNK(m)	((m & 0170000) == 0120000)	/* symbolic link */
#define	S_ISSOCK(m)	((m & 0170000) == 0140000)	/* socket */
I 17
#endif

E 29
I 19
#ifndef KERNEL
E 19
D 18
#ifdef __STDC__
E 18
I 18
D 21
#if __STDC__ || c_plusplus
E 18
mode_t umask(mode_t);
int mkdir(const char *, mode_t);
int mkfifo(const char *, mode_t);
int stat(const char *, struct stat *);
int fstat(int, struct stat *);
int chmod(const char *, mode_t);
#else
mode_t umask();
int mkdir();
int mkfifo();
int stat();
int fstat();
int chmod();
I 19
#endif
E 21
I 21
#include <sys/cdefs.h>

__BEGIN_DECLS
D 29
mode_t	umask __P((mode_t));
E 29
int	chmod __P((const char *, mode_t));
int	fstat __P((int, struct stat *));
int	mkdir __P((const char *, mode_t));
int	mkfifo __P((const char *, mode_t));
int	stat __P((const char *, struct stat *));
I 29
mode_t	umask __P((mode_t));
E 29
I 22
#ifndef _POSIX_SOURCE
I 29
int	chflags __P((const char *, u_long));
int	fchflags __P((int, u_long));
E 29
I 23
int	fchmod __P((int, mode_t));
E 23
int	lstat __P((const char *, struct stat *));
I 25
D 26
/* temporarily */
int	lqstat __P((const char *, struct qstat *));
int	fqstat __P((int, struct qstat *));
int	qstat __P((const char *, struct qstat *));
E 26
E 25
D 29
#endif /* not POSIX */
E 29
I 29
#endif
E 29
E 22
__END_DECLS
E 21
E 19
E 17
#endif
I 35
D 36
#endif /* !_STAT_H_ */
E 36
I 36
#endif /* !_SYS_STAT_H_ */
E 36
E 35
E 16
E 15
E 1
