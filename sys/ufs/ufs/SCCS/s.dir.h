h14700
s 00008/00000/00121
d D 8.5 95/04/27 11:46:56 mckusick 26 25
c move in definition of doff_t and MAXDIRSIZE
e
s 00001/00000/00120
d D 8.4 94/08/10 23:54:05 pendry 25 24
c add whiteout type
e
s 00028/00029/00092
d D 8.3 94/07/08 23:07:12 mckusick 24 23
c changes for 64-bit machines (from bostic)
e
s 00005/00000/00116
d D 8.2 94/01/21 17:30:49 bostic 23 22
c add USL's copyright notice
e
s 00002/00002/00114
d D 8.1 93/06/11 16:28:28 bostic 22 21
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00114
d D 7.12 92/07/06 14:57:28 mckusick 21 20
c add names (OLDDIRFMT, NEWDIRFMT) for first argument to DIRSIZ
e
s 00048/00006/00066
d D 7.11 92/07/02 17:21:41 mckusick 20 19
c add d_type fields in directories
e
s 00003/00003/00069
d D 7.10 91/03/25 17:28:22 bostic 19 18
c _DIR_ => _DIR_H
e
s 00001/00011/00071
d D 7.9 90/06/28 22:29:32 bostic 18 17
c new copyright notice
e
s 00000/00038/00082
d D 7.8 90/02/15 13:07:55 mckusick 17 16
c get rid of things having to do with libc directory access routines
e
s 00005/00002/00115
d D 7.7 90/01/30 16:56:01 mckusick 16 15
c update for rewinddir
e
s 00007/00002/00110
d D 7.6 89/05/09 17:12:17 mckusick 15 14
c check for multiple includes; change for POSIX compliance
e
s 00002/00002/00110
d D 7.5 89/02/21 12:25:00 marc 14 13
c put back last version - undo dependency on syslimits.h
e
s 00002/00002/00110
d D 7.4 89/02/16 14:10:02 bostic 13 12
c add syslimits.h for POSIX 1003.1; included by include/limits.h
e
s 00040/00026/00072
d D 7.3 89/01/11 17:00:44 mckusick 12 11
c break out non-kernel stuff to <dirent.h>;
c move compatibility code to the end and mark as going away
e
s 00003/00000/00095
d D 7.2 86/12/22 11:40:58 bostic 11 10
c bug report 4.1BSD/sys/31
e
s 00001/00001/00094
d D 7.1 86/06/04 23:21:09 mckusick 10 9
c 4.3BSD release version
e
s 00007/00001/00088
d D 6.2 85/06/08 14:55:38 mckusick 9 8
c Add copyright
e
s 00000/00000/00089
d D 6.1 83/07/29 06:11:59 sam 8 7
c 4.2 distribution
e
s 00026/00001/00063
d D 4.5 82/11/13 23:08:02 sam 7 6
c merge 4.1b and 4.1c
e
s 00049/00040/00015
d D 4.4 82/10/09 19:01:18 root 6 5
c better comments
e
s 00052/00007/00003
d D 4.3 82/04/19 19:26:48 mckusic 5 4
c merge in the new file system
e
s 00001/00001/00009
d D 4.2 81/02/19 21:39:59 wnj 4 3
c %G%->%E%
e
s 00000/00000/00010
d D 4.1 80/11/09 17:00:48 bill 3 2
c stamp for 4bsd
e
s 00001/00001/00009
d D 3.2 80/06/07 02:57:06 bill 2 1
c %H%->%G%
e
s 00010/00000/00000
d D 3.1 80/04/09 16:23:45 bill 1 0
c date and time created 80/04/09 16:23:45 by bill
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
D 9
/*	%M%	%I%	%E%	*/
E 9
I 9
/*
D 10
 * Copyright (c) 1982 Regents of the University of California.
E 10
I 10
D 12
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 12
I 12
D 22
 * Copyright (c) 1982, 1986, 1989 The Regents of the University of California.
 * All rights reserved.
E 22
I 22
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 23
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 23
E 22
E 12
 *
I 12
D 18
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
D 15
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 15
I 15
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 18
I 18
 * %sccs.include.redist.c%
E 18
E 15
 *
E 12
 *	%W% (Berkeley) %G%
 */
E 9
E 4
E 2

I 15
D 19
#ifndef _DIR_
#define	_DIR_
E 19
I 19
#ifndef _DIR_H_
#define	_DIR_H_
E 19

E 15
D 5
#ifndef	DIRSIZ
#define	DIRSIZ	14
#endif
struct	direct
{
	ino_t	d_ino;
	char	d_name[DIRSIZ];
E 5
I 5
D 6
/* @(#)ndir.h 4.4 3/30/82 */

E 6
/*
I 26
 * Theoretically, directories can be more than 2Gb in length, however, in
 * practice this seems unlikely. So, we define the type doff_t as a 32-bit
 * quantity to keep down the cost of doing lookup on a 32-bit machine.
 */
#define	doff_t		int32_t
#define MAXDIRSIZE	(0x7fffffff)

/*
E 26
D 6
 * This sets the "page size" for directories.
 * Requirements are DEV_BSIZE <= DIRBLKSIZ <= MINBSIZE with
 * DIRBLKSIZ a power of two.
 * Dennis Ritchie feels that directory pages should be atomic
 * operations to the disk, so we use DEV_BSIZE.
E 6
I 6
 * A directory consists of some number of blocks of DIRBLKSIZ
 * bytes, where DIRBLKSIZ is chosen such that it can be transferred
 * to disk in a single atomic operation (e.g. 512 bytes on most machines).
 *
 * Each DIRBLKSIZ byte block contains some number of directory entry
 * structures, which are of variable length.  Each directory entry has
 * a struct direct at the front of it, containing its inode number,
 * the length of the entry, and the length of the name contained in
 * the entry.  These are followed by the name padded to a 4 byte boundary
 * with null bytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN.
 *
D 20
 * The macro DIRSIZ(dp) gives the amount of space required to represent
E 20
I 20
 * The macro DIRSIZ(fmt, dp) gives the amount of space required to represent
E 20
 * a directory entry.  Free space in a directory is represented by
D 20
 * entries which have dp->d_reclen > DIRSIZ(dp).  All DIRBLKSIZ bytes
E 20
I 20
 * entries which have dp->d_reclen > DIRSIZ(fmt, dp).  All DIRBLKSIZ bytes
E 20
 * in a directory block are claimed by the directory entries.  This
 * usually results in the last entry in a directory having a large
 * dp->d_reclen.  When entries are deleted from a directory, the
 * space is returned to the previous entry in the same directory
 * block by increasing its dp->d_reclen.  If the first entry of
 * a directory block is free, then its dp->d_ino is set to 0.
 * Entries other than the first in a directory do not normally have
 * dp->d_ino set to 0.
E 6
 */
I 7
D 12
/* so user programs can just include dir.h */
#if !defined(KERNEL) && !defined(DEV_BSIZE)
#define	DEV_BSIZE	512
#endif
E 12
E 7
D 6
#define DIRBLKSIZ DEV_BSIZE
E 6
I 6
D 13
#define DIRBLKSIZ	DEV_BSIZE
#define	MAXNAMLEN	255
E 13
I 13
D 14
#define	DIRBLKSIZ	DEV_BSIZE
#define	MAXNAMLEN	NAME_MAX
E 14
I 14
#define DIRBLKSIZ	DEV_BSIZE
#define	MAXNAMLEN	255
E 14
E 13
E 6

D 6
/*
 * This limits the directory name length. Its main constraint
 * is that it appears twice in the user structure. (u. area)
 */
#define MAXNAMLEN 255

E 6
struct	direct {
D 6
	u_long	d_ino;
	short	d_reclen;
	short	d_namlen;
	char	d_name[MAXNAMLEN + 1];
	/* typically shorter */
E 6
I 6
D 24
	u_long	d_ino;			/* inode number of entry */
	u_short	d_reclen;		/* length of this record */
D 20
	u_short	d_namlen;		/* length of string in d_name */
E 20
I 20
	u_char	d_type; 		/* file type, see below */
	u_char	d_namlen;		/* length of string in d_name */
E 20
D 15
	char	d_name[MAXNAMLEN + 1];	/* name must be no longer than this */
E 15
I 15
	char	d_name[MAXNAMLEN + 1];	/* name with length <= MAXNAMLEN */
E 24
I 24
	u_int32_t d_ino;		/* inode number of entry */
	u_int16_t d_reclen;		/* length of this record */
	u_int8_t  d_type; 		/* file type, see below */
	u_int8_t  d_namlen;		/* length of string in d_name */
	char	  d_name[MAXNAMLEN + 1];/* name with length <= MAXNAMLEN */
E 24
E 15
E 6
E 5
};
I 5

D 6
struct _dirdesc {
	int	dd_fd;
	long	dd_loc;
	long	dd_size;
	char	dd_buf[DIRBLKSIZ];
};

E 6
/*
I 20
 * File types
 */
#define	DT_UNKNOWN	 0
#define	DT_FIFO		 1
#define	DT_CHR		 2
#define	DT_DIR		 4
#define	DT_BLK		 6
#define	DT_REG		 8
#define	DT_LNK		10
#define	DT_SOCK		12
I 25
#define	DT_WHT		14
E 25

/*
 * Convert between stat structure types and directory types.
 */
#define	IFTODT(mode)	(((mode) & 0170000) >> 12)
#define	DTTOIF(dirtype)	((dirtype) << 12)

/*
E 20
D 6
 * useful macros.
E 6
I 6
 * The DIRSIZ macro gives the minimum record length which will hold
 * the directory entry.  This requires the amount of space in struct direct
 * without the d_name field, plus enough space for the name with a terminating
 * null byte (dp->d_namlen+1), rounded up to a 4 byte boundary.
E 6
 */
D 17
#undef DIRSIZ
E 17
D 20
#define DIRSIZ(dp) \
E 20
I 20
#if (BYTE_ORDER == LITTLE_ENDIAN)
#define DIRSIZ(oldfmt, dp) \
    ((oldfmt) ? \
D 24
    ((sizeof (struct direct) - (MAXNAMLEN+1)) + (((dp)->d_type+1 + 3) &~ 3)) : \
    ((sizeof (struct direct) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3)))
E 24
I 24
    ((sizeof(struct direct) - (MAXNAMLEN+1)) + (((dp)->d_type+1 + 3) &~ 3)) : \
    ((sizeof(struct direct) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3)))
E 24
#else
#define DIRSIZ(oldfmt, dp) \
E 20
D 6
    ((sizeof(struct direct) - MAXNAMLEN + (dp)->d_namlen + sizeof(ino_t) - 1) &\
    ~(sizeof(ino_t) - 1))
typedef	struct _dirdesc DIR;
#ifndef	NULL
#define	NULL	0
#endif
E 6
I 6
D 24
    ((sizeof (struct direct) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))
E 24
I 24
    ((sizeof(struct direct) - (MAXNAMLEN+1)) + (((dp)->d_namlen+1 + 3) &~ 3))
E 24
I 20
#endif
I 21
#define OLDDIRFMT	1
#define NEWDIRFMT	0
E 21
E 20
E 6

I 12
D 17
#ifdef KERNEL
E 17
/*
D 24
 * Template for manipulating directories.
 * Should use struct direct's, but the name field
 * is MAXNAMLEN - 1, and this just won't do.
E 24
I 24
 * Template for manipulating directories.  Should use struct direct's,
 * but the name field is MAXNAMLEN - 1, and this just won't do.
E 24
 */
struct dirtemplate {
D 24
	u_long	dot_ino;
	short	dot_reclen;
D 20
	short	dot_namlen;
E 20
I 20
	u_char	dot_type;
	u_char	dot_namlen;
E 20
	char	dot_name[4];		/* must be multiple of 4 */
	u_long	dotdot_ino;
	short	dotdot_reclen;
D 20
	short	dotdot_namlen;
E 20
I 20
	u_char	dotdot_type;
	u_char	dotdot_namlen;
	char	dotdot_name[4];		/* ditto */
E 24
I 24
	u_int32_t	dot_ino;
	int16_t		dot_reclen;
	u_int8_t	dot_type;
	u_int8_t	dot_namlen;
	char		dot_name[4];	/* must be multiple of 4 */
	u_int32_t	dotdot_ino;
	int16_t		dotdot_reclen;
	u_int8_t	dotdot_type;
	u_int8_t	dotdot_namlen;
	char		dotdot_name[4];	/* ditto */
E 24
};

/*
 * This is the old format of directories, sanz type element.
 */
struct odirtemplate {
D 24
	u_long	dot_ino;
	short	dot_reclen;
	u_short	dot_namlen;
	char	dot_name[4];		/* must be multiple of 4 */
	u_long	dotdot_ino;
	short	dotdot_reclen;
	u_short	dotdot_namlen;
E 20
	char	dotdot_name[4];		/* ditto */
E 24
I 24
	u_int32_t	dot_ino;
	int16_t		dot_reclen;
	u_int16_t	dot_namlen;
	char		dot_name[4];	/* must be multiple of 4 */
	u_int32_t	dotdot_ino;
	int16_t		dotdot_reclen;
	u_int16_t	dotdot_namlen;
	char		dotdot_name[4];	/* ditto */
E 24
};
D 17
#endif

/*
 * The following information should be obtained from <dirent.h>
 * and is provided solely (and temporarily) for backward compatibility.
 */
E 12
I 6
#ifndef KERNEL
I 15
#define d_fileno d_ino		/* compatibility with POSIX */
E 15
I 12
#ifndef DEV_BSIZE
D 16
#define	DEV_BSIZE	512
E 16
I 16
#define	DEV_BSIZE	1024
E 16
#endif
E 12
E 6
/*
D 6
 * functions defined on directories
E 6
I 6
 * Definitions for library routines operating on directories.
E 6
 */
D 6
extern DIR *opendir();
extern struct direct *readdir();
extern long telldir();
extern void seekdir();
#define rewinddir(dirp)	seekdir((dirp), 0)
extern void closedir();
E 6
I 6
typedef struct _dirdesc {
	int	dd_fd;
	long	dd_loc;
	long	dd_size;
	char	dd_buf[DIRBLKSIZ];
} DIR;
I 11

#define dirfd(dirp)	((dirp)->dd_fd)

E 11
I 7
#ifndef NULL
#define NULL 0
#endif
E 7
extern	DIR *opendir();
extern	struct direct *readdir();
extern	long telldir();
extern	void seekdir();
D 16
#define rewinddir(dirp)	seekdir((dirp), (long)0)
E 16
extern	void closedir();
I 16
extern	long _rewinddir;
#define rewinddir(dirp) \
	_seekdir((dirp), _rewinddir); \
	_rewinddir = telldir(dirp)
E 16
D 7
#endif KERNEL
E 7
I 7
D 12
#endif

#ifdef KERNEL
/*
 * Template for manipulating directories.
 * Should use struct direct's, but the name field
 * is MAXNAMLEN - 1, and this just won't do.
 */
struct dirtemplate {
	u_long	dot_ino;
	short	dot_reclen;
	short	dot_namlen;
	char	dot_name[4];		/* must be multiple of 4 */
	u_long	dotdot_ino;
	short	dotdot_reclen;
	short	dotdot_namlen;
	char	dotdot_name[4];		/* ditto */
};
#endif
E 12
I 12
#endif /* not KERNEL */
E 17
I 15
D 19
#endif /* _DIR_ */
E 19
I 19
#endif /* !_DIR_H_ */
E 19
E 15
E 12
E 7
E 6
E 5
E 1
