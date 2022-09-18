h42560
s 00002/00002/00044
d D 8.1 93/05/31 14:45:56 bostic 19 18
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00045
d D 5.18 92/06/28 15:43:47 bostic 18 17
c make display line up if block/char devices displayed with other
c files.  (Jan-Simon has *way* too much free time...)
e
s 00008/00008/00037
d D 5.17 92/06/02 15:55:31 bostic 17 16
c values handed to printf(3) as field widths are really ints
e
s 00022/00010/00023
d D 5.16 92/03/13 17:09:08 elan 16 15
c calculate all of the field sizes dynamically
e
s 00002/00001/00031
d D 5.15 92/03/01 16:52:55 bostic 15 14
c replace -k with the BLOCKSIZE environmental variable
e
s 00003/00018/00029
d D 5.14 92/01/29 16:21:59 elan 14 13
c Deleted LS struct, and got rid of stat(2) struct field overloading 
c of st_spare1 and st_spare2 fields.
e
s 00009/00002/00038
d D 5.13 91/12/12 16:36:49 mckusick 13 12
c add -o option to list file flags
e
s 00001/00001/00039
d D 5.12 91/10/28 15:45:24 bostic 12 11
c It's a brave new ANSI world!
e
s 00001/00000/00039
d D 5.11 90/07/22 12:56:33 bostic 11 10
c there needs to be a way to get the hour/minute of a file that's more
c than six months old.  And ls(1) needs more options anyway.
e
s 00003/00001/00036
d D 5.10 90/04/08 17:41:46 bostic 10 9
c get redist notice from /usr/share/misc
e
s 00001/00013/00036
d D 5.9 90/04/06 16:59:38 bostic 9 8
c move copyright notice into /usr/share
e
s 00001/00000/00048
d D 5.8 89/08/22 12:26:43 bostic 8 7
c default sizes are in 512-byte blocks; add -k flag for kilobytes
e
s 00001/00000/00047
d D 5.7 89/06/27 18:02:25 bostic 7 6
c make `total' line, directory name, and preceding newline right
e
s 00009/00000/00038
d D 5.6 89/06/26 12:45:51 bostic 6 5
c print totals for -s flag, as well as -l
e
s 00001/00000/00037
d D 5.5 89/06/25 09:40:12 bostic 5 4
c add length field to ls structure
e
s 00000/00001/00037
d D 5.4 89/06/25 08:16:04 bostic 4 3
c remove f_firsttime
e
s 00006/00016/00032
d D 5.3 89/06/24 19:23:12 bostic 3 2
c only extern ones print.c needs
e
s 00003/00000/00045
d D 5.2 89/06/24 18:57:47 bostic 2 1
c fix copyright notice
e
s 00045/00000/00000
d D 5.1 89/06/24 18:19:55 bostic 1 0
c date and time created 89/06/24 18:19:55 by bostic
e
u
U
t
T
I 1
/*
D 19
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 19
I 19
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 19
 *
I 2
 * This code is derived from software contributed to Berkeley by
 * Michael Fischbein.
D 9
 *
E 2
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
 *
E 9
I 9
D 10
%copyright%
E 10
I 10
 *
D 12
%sccs.include.redist.c%
E 12
I 12
 * %sccs.include.redist.c%
E 12
 *
E 10
E 9
 *	%W% (Berkeley) %G%
 */

D 14
typedef struct _lsstruct {
	char *name;			/* file name */
I 5
	int len;			/* file name length */
E 5
	struct stat lstat;		/* lstat(2) for file */
} LS;

E 14
I 6
D 16
/*
I 13
 * Specify maximum width of flags output. Determined from flags_from_fid
 * routine in print.c
 */
D 14
#define FLAGSWIDTH 10

/*
E 13
 * overload -- we probably have to save blocks and/or maxlen with the lstat
 * array, so tabdir() stuffs it into unused fields in the first stat structure.
 * If there's ever a type larger than u_long, fix this.  Any calls to qsort
 * must save and restore the values.
 */
D 13
#define	st_btotal	st_flags
#define	st_maxlen	st_gen
E 13
I 13
#define	st_btotal	st_spare1
#define	st_maxlen	st_spare2
E 13

E 6
D 3
/* flags */
extern int f_listdot;		/* list files beginning with . */
extern int f_listalldot;	/* list . and .. as well */
extern int f_modtime;		/* use time of last change for time */
E 3
I 3
extern int errno;
E 14
I 14
#define FLAGSWIDTH	10
	
E 16
#define NO_PRINT	1
E 14

I 15
D 16
extern int blocksize;		/* block size units */
E 16
I 16
extern long blocksize;		/* block size units */
E 16

E 15
E 3
extern int f_accesstime;	/* use time of last access */
D 3
extern int f_statustime;	/* use time of last mode change */
extern int f_singlecol;		/* use single column output */
extern int f_listdir;		/* list actual directory, not contents */
extern int f_specialdir;	/* force operands to be directories */
extern int f_type;		/* add type character for non-regular files */
E 3
I 3
D 4
extern int f_firsttime;		/* to control recursion */
E 4
E 3
D 16
extern int f_group;		/* show group ownership of a file */
E 16
I 13
extern int f_flags;		/* show flags associated with a file */
E 13
extern int f_inode;		/* print inode */
I 8
D 15
extern int f_kblocks;		/* print size in kilobytes */
E 15
E 8
extern int f_longform;		/* long listing format */
I 11
extern int f_sectime;		/* print the real time for all files */
E 11
D 3
extern int f_nonprint;		/* show unprintables as ? */
extern int f_reversesort;	/* reverse whatever sort is used */
extern int f_recursive;		/* ls subdirectories also */
E 3
I 3
D 16
extern int f_singlecol;		/* use single column output */
E 16
E 3
extern int f_size;		/* list size in short listing */
D 3
extern int f_timesort;		/* sort by time vice name */
extern int f_firsttime;		/* to control recursion */

extern int errno;
E 3
I 3
extern int f_statustime;	/* use time of last mode change */
I 7
D 16
extern int f_total;		/* if precede with "total" line */
E 16
E 7
extern int f_type;		/* add type character for non-regular files */
I 16

typedef struct {
	FTSENT *list;
I 17
	u_long btotal;
I 18
	int bcfile;
E 18
E 17
	int entries;
	int maxlen;
D 17
	u_long btotal;
	u_long s_block;
	u_long s_inode;
	u_long s_nlink;
	u_long s_size;
	u_long s_user;
	u_long s_group;
	u_long s_flags;
E 17
I 17
	int s_block;
	int s_flags;
	int s_group;
	int s_inode;
	int s_nlink;
	int s_size;
	int s_user;
E 17
} DISPLAY;

typedef struct {
	char *user;
	char *group;
	char *flags;
	char data[1];
} NAMES;
E 16
E 3
E 1
