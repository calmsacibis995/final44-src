h48173
s 00008/00000/00068
d D 8.2 94/07/28 03:38:24 pendry 24 23
c changes for whiteouts and union filesystem
e
s 00002/00002/00066
d D 8.1 93/06/08 17:56:42 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00067
d D 5.20 93/06/08 17:46:44 mckusick 22 20
c add dd_rewind for rewinddir
e
s 00002/00002/00065
d R 8.1 93/06/02 20:05:10 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00017/00064
d D 5.19 92/02/06 17:46:25 mckusick 20 19
c definition of dirent is defined in <sys/dirent.h>
e
s 00001/00001/00080
d D 5.18 91/02/23 18:52:51 donn 19 18
c Adjust the type of scandir's function argument.
e
s 00006/00001/00075
d D 5.17 91/02/22 09:04:33 donn 18 17
c This baby is included by the kernel...  Declare getdirentries() here.
e
s 00017/00025/00059
d D 5.16 91/02/05 17:11:01 bostic 17 16
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00001/00083
d D 5.15 90/11/14 12:00:03 bostic 16 15
c direct -> dirent in a comment
e
s 00002/00002/00082
d D 5.14 90/09/24 13:02:16 bostic 15 14
c scandir now takes struct dirent's, not directs
e
s 00002/00002/00082
d D 5.13 90/06/24 11:44:59 bostic 14 13
c can be `char *' or `void *' according to ANSI C, but the types of
c scandir, qsort and alphasort should agree.
e
s 00001/00001/00083
d D 5.12 90/06/23 16:48:03 bostic 13 12
c typo
e
s 00001/00001/00083
d D 5.11 90/06/23 16:39:21 bostic 12 11
c syntactic sugar
e
s 00001/00001/00083
d D 5.10 90/05/29 19:26:43 bostic 11 10
c C++ wants the prototypes, too
e
s 00032/00035/00052
d D 5.9 90/05/25 17:56:07 bostic 10 9
c make rewinddir a function, closedir returns int; POSIX 1003.1
e
s 00020/00005/00067
d D 5.8 90/03/06 17:04:34 bostic 9 8
c add ANSI C prototypes
e
s 00001/00001/00071
d D 5.7 90/02/05 17:34:04 mckusick 8 7
c allow rewinddir to work in all contexts
e
s 00004/00001/00068
d D 5.6 90/01/30 16:52:59 mckusick 7 6
c set up rewinddir to work correctly
e
s 00000/00018/00069
d D 5.5 89/07/11 18:09:43 mckusick 6 4
c move structure describing telldir magic cookie to telldir.c
e
s 00000/00016/00071
d R 5.5 89/07/11 18:05:23 mckusick 5 4
c move structure describing telldir magic cookie to telldir.c
e
s 00027/00004/00060
d D 5.4 89/07/10 15:14:54 mckusick 4 3
c update to support new directory access routines that use getdirentries
e
s 00006/00001/00058
d D 5.3 89/05/03 17:23:44 mckusick 3 2
c make more POSIX compliant
e
s 00001/00001/00058
d D 5.2 89/01/27 16:49:01 bostic 2 1
c just use max value rather than have machine dependent info here
e
s 00059/00000/00000
d D 5.1 89/01/11 16:42:43 mckusick 1 0
c date and time created 89/01/11 16:42:43 by mckusick
e
u
U
t
T
I 1
D 10
/*
E 10
I 10
/*-
E 10
D 23
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 10
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
 *
 *	%W% (Berkeley) %G%
 */

I 3
D 17
#ifndef _DIRENT_
#define _DIRENT_
E 17
I 17
#ifndef _DIRENT_H_
#define _DIRENT_H_
E 17

E 3
/*
D 10
 * A directory entry has a struct direct at the front of it,
 * containing its inode number, the length of the entry, and the
 * length of the name contained in the entry.  These are followed
 * by the name padded to a 4 byte boundary with null bytes.  All
 * names are guaranteed null terminated.  The maximum length of a
 * name in a directory is MAXNAMLEN.
E 10
I 10
D 16
 * A directory entry has a struct direct at the front of it, containing its
E 16
I 16
D 20
 * A directory entry has a struct dirent at the front of it, containing its
E 16
 * inode number, the length of the entry, and the length of the name
 * contained in the entry.  These are followed by the name padded to a 4
 * byte boundary with null bytes.  All names are guaranteed null terminated.
 * The maximum length of a name in a directory is MAXNAMLEN.
E 20
I 20
 * The kernel defines the format of directory entries returned by 
 * the getdirentries(2) system call.
E 20
E 10
 */
D 10
#define	MAXNAMLEN	255
E 10
D 20

D 10
struct	dirent {
E 10
I 10
struct dirent {
E 10
D 3
	u_long	d_ino;			/* inode number of entry */
E 3
I 3
	u_long	d_fileno;		/* file number of entry */
E 3
	u_short	d_reclen;		/* length of this record */
	u_short	d_namlen;		/* length of string in d_name */
I 10
#ifdef _POSIX_SOURCE
	char	d_name[255 + 1];	/* name must be no longer than this */
#else
#define	MAXNAMLEN	255
E 10
	char	d_name[MAXNAMLEN + 1];	/* name must be no longer than this */
I 10
#endif
E 10
};
E 20
I 20
#include <sys/dirent.h>
E 20
I 3
D 10
#define d_ino d_fileno		/* backward compatibility */
E 10
E 3

D 10
/*
 * Definitions for library routines operating on directories.
 */
E 10
I 10
#ifdef _POSIX_SOURCE
typedef void *	DIR;
#else

#define	d_ino		d_fileno	/* backward compatibility */

/* definitions for library routines operating on directories. */
E 10
D 2
#define DIRBLKSIZ	512
E 2
I 2
#define	DIRBLKSIZ	1024
E 2

I 4
D 6
#define	NDIRHASH	8	/* Num of hash lists, must be a power of 2 */
#define	LOCHASH(i)	((i)&(NDIRHASH-1))

E 6
D 10
/*
 * This structure describes an open directory.
 */
E 10
I 10
/* structure describing an open directory. */
E 10
E 4
typedef struct _dirdesc {
D 4
	int	dd_fd;
	long	dd_loc;
	long	dd_size;
	char	dd_buf[DIRBLKSIZ];
E 4
I 4
	int	dd_fd;		/* file descriptor associated with directory */
	long	dd_loc;		/* offset in current buffer */
	long	dd_size;	/* amount of data returned by getdirentries */
	char	*dd_buf;	/* data buffer */
	int	dd_len;		/* size of data buffer */
	long	dd_seek;	/* magic cookie returned by getdirentries */
I 22
	long	dd_rewind;	/* magic cookie for rewinding */
I 24
	int	dd_flags;	/* flags for readdir */
E 24
E 22
D 6
	long	dd_loccnt;	/* next magic cookie for seekdir */
	struct	ddloc *dd_hash[NDIRHASH];   /* hash list heads for ddlocs */
E 6
E 4
} DIR;

D 10
#define dirfd(dirp)	((dirp)->dd_fd)
E 10
I 10
#define	dirfd(dirp)	((dirp)->dd_fd)
E 10
I 4
D 6

/*
 * One of these structures is malloced to describe the current directory
 * position each time telldir is called. It records the current magic 
 * cookie returned by getdirentries and the offset within the buffer
 * associated with that return value.
 */
struct ddloc {
	struct	ddloc *loc_next;/* next structure in list */
	long	loc_index;	/* key associated with structure */
	long	loc_seek;	/* magic cookie returned by getdirentries */
	long	loc_loc;	/* offset of entry in buffer */
};
E 6
E 4

I 24
/* flags for opendir2 */
#define DTF_HIDEW	0x0001	/* hide whiteout entries */
#define DTF_NODUP	0x0002	/* don't return duplicate names */
#define DTF_REWIND	0x0004	/* rewind after reading union stack */
#define __DTF_READALL	0x0008	/* everything has been read */

E 24
#ifndef NULL
D 10
#define NULL 0
E 10
I 10
#define	NULL	0
E 10
#endif
D 9
extern	DIR *opendir();
extern	struct dirent *readdir();
extern	long telldir();
extern	void seekdir();
D 7
#define rewinddir(dirp)	seekdir((dirp), (long)0)
E 7
extern	void closedir();
E 9
I 9

E 9
I 7
D 10
extern	long _rewinddir;
#define rewinddir(dirp) \
D 8
	_seekdir((dirp), _rewinddir); \
E 8
I 8
	_seekdir((dirp), _rewinddir), \
E 8
	_rewinddir = telldir(dirp)
E 10
I 10
#endif /* _POSIX_SOURCE */
E 10
I 9

I 18
#ifndef KERNEL

E 18
D 11
#ifdef __STDC__
E 11
I 11
D 17
#if __STDC__ || c_plusplus
E 11
extern DIR *opendir(const char *);
extern struct dirent *readdir(DIR *);
I 10
D 13
extern void rewindir(DIR *);
E 13
I 13
extern void rewinddir(DIR *);
E 13
extern int closedir(DIR *);
E 17
I 17
#include <sys/cdefs.h>

__BEGIN_DECLS
DIR *opendir __P((const char *));
struct dirent *readdir __P((DIR *));
void rewinddir __P((DIR *));
int closedir __P((DIR *));
E 17
#ifndef _POSIX_SOURCE
I 24
DIR *__opendir2 __P((const char *, int));
E 24
E 10
D 17
extern long telldir(const DIR *);
extern void seekdir(DIR *, long);
D 10
extern void closedir(DIR *);
E 10
D 12
extern int scandir(const char *, struct direct *(*[]),
E 12
I 12
D 15
extern int scandir(const char *, struct direct ***,
E 12
D 14
    int (* )(struct direct *), int (* )(char *, char *));
extern int alphasort(const struct direct **, const struct direct **);
E 14
I 14
    int (* )(struct direct *), int (* )(void *, void *));
E 15
I 15
extern int scandir(const char *, struct dirent ***,
    int (*)(struct dirent *), int (*)(void *, void *));
E 15
extern int alphasort(const void *, const void *);
E 17
I 17
long telldir __P((const DIR *));
void seekdir __P((DIR *, long));
int scandir __P((const char *, struct dirent ***,
D 19
    int (*)(struct dirent *), int (*)(void *, void *)));
E 19
I 19
    int (*)(struct dirent *), int (*)(const void *, const void *)));
E 19
int alphasort __P((const void *, const void *));
E 17
E 14
I 10
D 18
#endif
E 18
I 18
int getdirentries __P((int, char *, int, long *));
#endif /* not POSIX */
E 18
E 10
D 17
#else
extern DIR *opendir();
extern struct dirent *readdir();
I 10
extern void rewinddir();
extern int closedir();
#ifndef _POSIX_SOURCE
E 10
extern long telldir();
extern void seekdir();
D 10
extern void closedir();
E 10
extern int scandir();
extern int alphasort();
I 10
#endif
E 10
#endif
E 9
E 7
I 3
#endif /* _DIRENT_ */
E 17
I 17
__END_DECLS
I 18

#endif /* !KERNEL */
E 18

#endif /* !_DIRENT_H_ */
E 17
E 3
E 1
