h29222
s 00003/00001/00110
d D 8.3 94/09/13 12:22:46 mckusick 31 30
c clrimap => usedinomap (to be more descriptive); add SETINO
e
s 00005/00000/00106
d D 8.2 94/01/21 17:05:47 bostic 30 29
c add USL's copyright notice
e
s 00002/00002/00104
d D 8.1 93/06/05 11:12:07 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00045/00105
d D 5.14 92/10/16 16:21:25 bostic 28 27
c ANSI C, convert options handling to getopt(3)
e
s 00003/00006/00147
d D 5.13 92/10/06 00:17:05 mckusick 27 25
c modernize the bit test macros; more intuitive name for pathname lookup
e
s 00002/00005/00148
d R 5.13 92/10/05 23:59:44 mckusick 26 25
c modernize the bit test macros
e
s 00005/00000/00148
d D 5.12 92/08/09 13:57:14 mckusick 25 24
c add FORCE flag for setdirmodes()
e
s 00002/00000/00146
d D 5.11 92/06/30 18:26:38 mckusick 24 23
c more global conversion flags
e
s 00003/00003/00143
d D 5.10 91/11/11 11:39:12 bostic 23 22
c break UFS up into FFS/UFS/LFS/MFS
e
s 00002/00002/00144
d D 5.9 91/07/29 16:16:09 mckusick 22 20
c use RST_DIR in place of DIR (to avoid conflicts with directory
c access routine library)
e
s 00002/00002/00144
d R 5.9 91/07/29 15:59:22 mckusick 21 20
c use RST_DIR in place of DIR (to avoid conflicts with dirirectory
c access routine library
e
s 00001/00011/00145
d D 5.8 90/06/01 16:21:15 bostic 20 19
c new copyright notice
e
s 00001/00011/00155
d D 5.7 90/02/15 13:13:51 mckusick 19 18
c only include directory items that are exported from dirs.c
e
s 00018/00004/00148
d D 5.6 90/02/13 18:39:43 mckusick 18 17
c make DIR typedef explicit, do not depend on dir.h for it
e
s 00001/00002/00151
d D 5.5 89/10/31 23:17:03 mckusick 17 16
c dinode.h replaces vnode.h and inode.h
e
s 00005/00003/00148
d D 5.4 89/07/30 11:00:24 bostic 16 15
c vnodes
e
s 00014/00003/00137
d D 5.3 88/10/24 16:38:31 bostic 15 14
c Berkeley copyright notice
e
s 00001/00000/00139
d D 5.2 88/05/13 14:47:50 mckusick 14 13
c add Nflag to request not to do any writes
e
s 00007/00001/00132
d D 5.1 85/05/28 15:18:40 dist 13 12
c Add copyright
e
s 00001/00000/00132
d D 3.12 85/03/24 18:10:08 mckusick 12 11
c dynamically calculate tape block size unless specified on command line
e
s 00001/00000/00131
d D 3.11 85/02/18 18:28:52 mckusick 11 10
c do not set owner and times on directories that already exist ('i' and 'x' only)
e
s 00003/00000/00128
d D 3.10 85/01/18 22:38:04 mckusick 10 9
c reorganize to split out interactive shell
e
s 00001/00000/00127
d D 3.9 85/01/14 15:38:13 mckusick 9 8
c add 'b' flag to set number of tape records
e
s 00001/00003/00126
d D 3.8 83/08/11 23:06:39 sam 8 7
c standardize sccs keyword lines
e
s 00007/00000/00122
d D 3.7 83/04/19 02:11:42 mckusick 7 6
c add and debug interactive extraction mode
e
s 00001/00000/00121
d D 3.6 83/04/11 18:09:08 mckusick 6 5
c generalize the printing of flags
e
s 00004/00004/00117
d D 3.5 83/03/27 18:33:33 mckusick 5 4
c pass pruning argument back to treescan
e
s 00004/00003/00117
d D 3.4 83/03/23 08:58:18 mckusick 4 3
c use a tempname derived from the inode number instead of from the file name
e
s 00014/00020/00106
d D 3.3 83/01/16 06:04:16 mckusick 3 2
c new incremental restore algorithm
e
s 00004/00003/00122
d D 3.2 83/02/26 18:27:06 mckusick 2 1
c get the tape subsystem working; get "t" command working
e
s 00125/00000/00000
d D 3.1 83/02/18 00:42:39 mckusick 1 0
c date and time created 83/02/18 00:42:39 by mckusick
e
u
U
t
T
I 1
D 8
/* Copyright (c) 1983 Regents of the University of California */

/*	%W%	(Berkeley)	%E%	*/
E 8
I 8
D 13
/*	%M%	%I%	%E%	*/
E 13
I 13
/*
D 15
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
D 29
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
I 30
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 30
E 29
 *
D 20
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
E 20
I 20
 * %sccs.include.redist.c%
E 20
E 15
 *
 *	%W% (Berkeley) %G%
 */
E 13
E 8

I 18
D 23
#include <stdio.h>
E 23
E 18
D 16
#include <stdio.h>
E 16
D 28
#include <sys/param.h>
D 16
#include <sys/inode.h>
#include <sys/fs.h>
E 16
I 16
#include <sys/time.h>
D 17
#include <sys/vnode.h>
E 17
E 16
I 10
D 18
#include <sys/dir.h>
E 18
I 16
D 17
#include <ufs/inode.h>
E 17
I 17
D 23
#include <ufs/dinode.h>
E 17
#include <ufs/fs.h>
E 23
I 23
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
#include <stdio.h>
E 23
D 18
#include <stdio.h>
E 18
I 18
D 19
#define _DIRENT_
#include <ufs/dir.h>
E 19
E 18
E 16
E 10

E 28
/*
 * Flags
 */
extern int	cvtflag;	/* convert from old to new tape format */
I 12
extern int	bflag;		/* set input block size */
E 12
extern int	dflag;		/* print out debugging info */
extern int	hflag;		/* restore heirarchies */
extern int	mflag;		/* restore by name instead of inode number */
I 14
extern int	Nflag;		/* do not write the disk */
E 14
extern int	vflag;		/* print out actions taken */
extern int	yflag;		/* always try to recover from tape errors */
/*
 * Global variables
 */
extern char	*dumpmap; 	/* map of inodes on this dump tape */
D 31
extern char	*clrimap; 	/* map of inodes to be deleted */
E 31
I 31
extern char	*usedinomap; 	/* map of inodes that are in use on this fs */
E 31
extern ino_t	maxino;		/* highest numbered inode in this file system */
extern long	dumpnum;	/* location of the dump on this tape */
extern long	volno;		/* current volume being read */
I 9
extern long	ntrec;		/* number of TP_BSIZE records per tape block */
E 9
D 2
extern time_t	dumptime;	/* time that this dump was made */
E 2
I 2
extern time_t	dumptime;	/* time that this dump begins */
extern time_t	dumpdate;	/* time that this dump was made */
E 2
extern char	command;	/* opration being performed */
I 7
extern FILE	*terminal;	/* file descriptor for the terminal input */
I 24
extern int	oldinofmt;	/* reading tape with old format inodes */
extern int	Bcvt;		/* need byte swapping on inodes and dirs */
E 24
E 7

/*
 * Each file in the file system is described by one of these entries
 */
struct entry {
	char	*e_name;		/* the current name of this entry */
	u_char	e_namlen;		/* length of this name */
	char	e_type;			/* type of this entry, see below */
	short	e_flags;		/* status flags, see below */
	ino_t	e_ino;			/* inode number in previous file sys */
D 3
	char	*e_newname;		/* full pathname of rename in new fs */
E 3
I 3
	long	e_index;		/* unique index (for dumpped table) */
E 3
	struct	entry *e_parent;	/* pointer to parent directory (..) */
	struct	entry *e_sibling;	/* next element in this directory (.) */
	struct	entry *e_links;		/* hard links to this inode */
	struct	entry *e_entries;	/* for directories, their entries */
I 3
	struct	entry *e_next;		/* hash chain list */
E 3
};
/* types */
#define	LEAF 1			/* non-directory entry */
#define NODE 2			/* directory entry */
#define LINK 4			/* synthesized type, stripped by addentry */
/* flags */
D 3
#define REMOVE		0x0001	/* entry to be removed */
#define REMOVED		0x0002	/* entry has been removed */
#define RENAME		0x0004	/* entry to be renamed */
#define TMPNAME		0x0008	/* entry has been given a temporary name */
#define TMPNODE		0x0010	/* entry is a temporary, to be replaced */
#define EXTRACT		0x0020	/* entry is to be extracted from the tape */
#define RENUMBER	0x0040	/* entry is to be assigned a new inode number */
#define CHANGE		0x0080	/* entry is to be deleted and extracted */
#define NEW		0x0100	/* a new entry to be extracted */
#define KEEP		0x0200	/* entry is not to change */
E 3
I 3
#define EXTRACT		0x0001	/* entry is to be replaced from the tape */
#define NEW		0x0002	/* a new entry to be extracted */
#define KEEP		0x0004	/* entry is not to change */
#define REMOVED		0x0010	/* entry has been removed */
#define TMPNAME		0x0020	/* entry has been given a temporary name */
I 11
#define EXISTED		0x0040	/* directory already existed during extract */
I 28

E 28
E 11
E 3
/*
D 28
 * functions defined on entry structs
 */
D 3
extern struct entry **entry;
E 3
extern struct entry *lookupino();
extern struct entry *lookupname();
extern struct entry *lookupparent();
D 3
extern struct entry *pathcheck();
E 3
extern struct entry *addentry();
extern char *myname();
extern char *savename();
I 4
extern char *gentempname();
I 6
extern char *flagvalues();
E 6
E 4
extern ino_t lowerbnd();
extern ino_t upperbnd();
I 10
D 18
extern DIR *rst_opendir();
extern struct direct *rst_readdir();
E 18
E 10
#define NIL ((struct entry *)(0))
D 3
#define lookupino(inum)		(entry[(inum)])
#define addino(inum, np)	(entry[(inum)] = (np))
#define deleteino(inum)		(entry[(inum)] = (struct entry *)NIL)
E 3
/*
E 28
 * Constants associated with entry structs
 */
D 4
#define HARDLINK 1
#define SYMLINK  2
#define TMPCHAR (0x01)
E 4
I 4
#define HARDLINK	1
#define SYMLINK		2
#define TMPHDR		"RSTTMP"
E 4

/*
 * The entry describes the next file available on the tape
 */
struct context {
	char	*name;		/* name of file */
	ino_t	ino;		/* inumber of file */
	struct	dinode *dip;	/* pointer to inode */
	char	action;		/* action being taken on this file */
} curfile;
/* actions */
#define	USING	1	/* extracting from the tape */
#define	SKIP	2	/* skipping */
#define UNKNOWN 3	/* disposition or starting point is unknown */
I 18

/*
 * Definitions for library routines operating on directories.
 */
D 19
typedef struct _dirdesc {
	int	dd_fd;
	long	dd_loc;
	long	dd_size;
	char	dd_buf[DIRBLKSIZ];
} DIR;
extern DIR *opendirfile();
E 19
I 19
D 22
typedef struct dirdesc DIR;
E 19
extern DIR *rst_opendir();
E 22
I 22
typedef struct rstdirdesc RST_DIR;
D 28
extern RST_DIR *rst_opendir();
E 22
extern struct direct *rst_readdir();
D 19
extern long rst_telldir();
extern void rst_seekdir();
E 19
E 18

/*
 * Other exported routines
 */
D 27
extern ino_t psearch();
E 27
I 27
extern ino_t pathsearch();
E 27
I 7
extern ino_t dirlookup();
E 7
D 5
extern void listfile();
extern void addfile();
D 3
extern void markfile();
E 3
I 3
extern void nodeupdates();
E 3
extern void verifyfile();
E 5
I 5
extern long listfile();
I 7
extern long deletefile();
E 7
extern long addfile();
extern long nodeupdates();
extern long verifyfile();
E 5
extern char *rindex();
extern char *index();
D 3
extern void strcat();
extern void strcpy();
extern void mktemp();
E 3
I 3
extern char *strcat();
I 7
extern char *strncat();
E 7
extern char *strcpy();
I 7
extern char *strncpy();
extern char *fgets();
E 7
extern char *mktemp();
extern char *malloc();
extern char *calloc();
I 7
extern char *realloc();
E 7
extern long lseek();
E 28
E 3

/*
I 25
 * Flags to setdirmodes.
 */
#define FORCE	0x0001

/*
E 25
 * Useful macros
 */
D 27
#define	MWORD(m,i) (m[(unsigned)(i-1)/NBBY])
#define	MBIT(i)	(1<<((unsigned)(i-1)%NBBY))
#define	BIS(i,w)	(MWORD(w,i) |=  MBIT(i))
#define	BIC(i,w)	(MWORD(w,i) &= ~MBIT(i))
#define	BIT(i,w)	(MWORD(w,i) & MBIT(i))
E 27
I 27
#define TSTINO(ino, map) \
	(map[(u_int)((ino) - 1) / NBBY] &  (1 << ((u_int)((ino) - 1) % NBBY)))
I 31
#define	SETINO(ino, map) \
	map[(u_int)((ino) - 1) / NBBY] |=  1 << ((u_int)((ino) - 1) % NBBY)
E 31
E 27

#define dprintf		if (dflag) fprintf
#define vprintf		if (vflag) fprintf

D 2
#define GOOD 0
#define FAIL 1
E 2
I 2
#define GOOD 1
#define FAIL 0
E 2
E 1
