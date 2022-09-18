h29161
s 00002/00002/00060
d D 8.1 93/06/06 14:03:17 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00061
d D 5.10 92/06/18 17:51:44 bostic 10 9
c stat structure changes for quad/POSIX times
e
s 00003/00001/00059
d D 5.9 92/02/19 12:40:49 bostic 9 8
c don't skip first two chars unless "./"
e
s 00025/00018/00035
d D 5.8 91/12/11 17:56:17 bostic 8 7
c version 2; add cksum, make keywords flexible, new output format
e
s 00014/00012/00039
d D 5.7 90/05/25 16:50:49 bostic 7 6
c add modification time keyword
e
s 00004/00003/00047
d D 5.6 90/05/25 12:54:07 bostic 6 5
c add FIFO support
e
s 00024/00029/00026
d D 5.5 90/05/25 12:19:29 bostic 5 4
c fold INFO and ENTRY structures together into NODE structure
e
s 00008/00007/00047
d D 5.4 90/05/25 10:43:30 bostic 4 3
c implement the magic characters in specification file names
e
s 00022/00026/00032
d D 5.3 90/05/25 10:29:58 bostic 3 2
c integrate fts(3), don't need lots of this stuff
e
s 00006/00013/00052
d D 5.2 90/05/22 12:58:43 bostic 2 1
c rearrange and make the world static
e
s 00065/00000/00000
d D 5.1 89/09/04 16:24:54 bostic 1 0
c date and time created 89/09/04 16:24:54 by bostic
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1989 The Regents of the University of California.
E 2
I 2
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
E 2
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */
I 2

#include <string.h>
#include <stdlib.h>
E 2

I 8
#define	KEYDEFAULT \
	(F_GID | F_MODE | F_NLINK | F_SIZE | F_SLINK | F_TIME | F_UID)

#define	MISMATCHEXIT	2

E 8
D 3
typedef struct _id {
	struct _id *next;
	u_int id;
	u_long cnt;
} ID;

E 3
D 5
typedef struct _info {
E 5
I 5
typedef struct _node {
	struct _node	*parent, *child;	/* up, down */
	struct _node	*prev, *next;		/* left, right */
	off_t	st_size;			/* size */
I 7
D 10
	time_t	st_mtime;			/* last modification time */
E 10
I 10
	struct timespec	st_mtimespec;		/* last modification time */
E 10
E 7
	u_long	cksum;				/* check sum */
	char	*slink;				/* symbolic link reference */
D 8
	uid_t	st_uid;				/* owner */
	gid_t	st_gid;				/* group */
E 8
I 8
	uid_t	st_uid;				/* uid */
	gid_t	st_gid;				/* gid */
E 8
#define	MBITS	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
	mode_t	st_mode;			/* mode */
	nlink_t	st_nlink;			/* link count */

E 5
D 3
#define	F_CKSUM	0x001				/* check sum */
#define	F_DMODE	0x002				/* directory mode */
#define	F_FMODE	0x004				/* directory mode */
#define	F_GROUP	0x008				/* group */
#define	F_MODE	0x010				/* directory mode */
#define	F_NLINK	0x020				/* number of links */
#define	F_OWNER	0x040				/* owner */
#define	F_SIZE	0x080				/* size */
#define	F_SLINK	0x100				/* link count */
#define	F_TYPE	0x200				/* file type */
	u_int	flags;				/* items set */

E 3
D 8
#define	F_BLOCK	0x001				/* block special */
#define	F_CHAR	0x002				/* char special */
#define	F_DIR	0x004				/* directory */
D 6
#define	F_FILE	0x008				/* regular file */
#define	F_LINK	0x010				/* symbolic link */
#define	F_SOCK	0x020				/* socket */
E 6
I 6
#define	F_FIFO	0x008				/* fifo */
#define	F_FILE	0x010				/* regular file */
#define	F_LINK	0x020				/* symbolic link */
#define	F_SOCK	0x040				/* socket */
E 6
D 3
	u_int	type;				/* file type */
E 3
I 3
D 5
#define	F_NONE	0x040				/* unknown */
E 5
	u_short	type;				/* file type */
E 3

E 8
I 3
D 7
#define	F_CKSUM	0x001				/* check sum */
D 5
#define	F_GROUP	0x002				/* group */
#define	F_IGN	0x004				/* ignore */
#define	F_MODE	0x008				/* mode */
#define	F_NLINK	0x010				/* number of links */
#define	F_OWNER	0x020				/* owner */
#define	F_SIZE	0x040				/* size */
#define	F_SLINK	0x080				/* link count */
#define	F_TYPE	0x100				/* file type */
E 5
I 5
#define	F_DONE	0x002				/* directory done */
#define	F_GROUP	0x004				/* group */
#define	F_IGN	0x008				/* ignore */
#define	F_MAGIC	0x010				/* name has magic chars */
#define	F_MODE	0x020				/* mode */
#define	F_NLINK	0x040				/* number of links */
#define	F_OWNER	0x080				/* owner */
#define	F_SIZE	0x100				/* size */
#define	F_SLINK	0x200				/* link count */
#define	F_TYPE	0x400				/* file type */
#define	F_VISIT	0x800				/* file visited */
E 7
I 7
#define	F_CKSUM	0x0001				/* check sum */
#define	F_DONE	0x0002				/* directory done */
D 8
#define	F_GROUP	0x0004				/* group */
#define	F_IGN	0x0008				/* ignore */
#define	F_MAGIC	0x0010				/* name has magic chars */
#define	F_MODE	0x0020				/* mode */
#define	F_NLINK	0x0040				/* number of links */
#define	F_OWNER	0x0080				/* owner */
E 8
I 8
#define	F_GID	0x0004				/* gid */
#define	F_GNAME	0x0008				/* group name */
#define	F_IGN	0x0010				/* ignore */
#define	F_MAGIC	0x0020				/* name has magic chars */
#define	F_MODE	0x0040				/* mode */
#define	F_NLINK	0x0080				/* number of links */
E 8
#define	F_SIZE	0x0100				/* size */
#define	F_SLINK	0x0200				/* link count */
#define	F_TIME	0x0400				/* modification time */
#define	F_TYPE	0x0800				/* file type */
D 8
#define	F_VISIT	0x1000				/* file visited */
E 8
I 8
#define	F_UID	0x1000				/* uid */
#define	F_UNAME	0x2000				/* user name */
#define	F_VISIT	0x4000				/* file visited */
E 8
E 7
E 5
	u_short	flags;				/* items set */
I 8

#define	F_BLOCK	0x001				/* block special */
#define	F_CHAR	0x002				/* char special */
#define	F_DIR	0x004				/* directory */
#define	F_FIFO	0x008				/* fifo */
#define	F_FILE	0x010				/* regular file */
#define	F_LINK	0x020				/* symbolic link */
#define	F_SOCK	0x040				/* socket */
	u_char	type;				/* file type */
E 8

D 4
	off_t	st_size;
E 4
I 4
D 5
	off_t	st_size;			/* size */
E 4
	u_long	cksum;				/* check sum */
E 3
D 4
	uid_t	st_uid;
	gid_t	st_gid;
E 4
I 4
	uid_t	st_uid;				/* owner */
	gid_t	st_gid;				/* group */
E 4
D 3
	off_t	st_size;
E 3
I 3
#define	MBITS	(S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO)
E 3
D 4
	mode_t	st_mode;
	nlink_t	st_nlink;
E 4
I 4
	mode_t	st_mode;			/* mode */
	nlink_t	st_nlink;			/* link count */
E 4
D 3
	u_long	cksum;				/* check sum */
E 3
	char	*slink;				/* symbolic link reference */
} INFO;

typedef struct _entry {
D 3
	struct _entry	*next, *child, *parent;	/* tree links */
E 3
I 3
	struct _entry	*child, *parent;	/* up, down */
	struct _entry	*next, *prev;		/* left, right */
E 3
	INFO	info;				/* node info structure */
#define	F_DONE	0x01				/* directory done */
D 3
#define	F_IGN	0x02				/* ignore this node on down */
#define	F_VISIT	0x04				/* visited this node */
	u_int	flags;				/* flags */
E 3
I 3
D 4
#define	F_VISIT	0x02				/* visited this node */
E 4
I 4
#define	F_MAGIC	0x02				/* name has magic chars */
#define	F_VISIT	0x04				/* visited this node */
E 4
	u_char	flags;				/* flags */
E 5
E 3
D 4
	char	*name;				/* node name */
E 4
I 4
	char	name[1];			/* file name (must be last) */
E 4
D 3
	int	nlen;				/* name length */
E 3
D 5
} ENTRY;
E 5
I 5
} NODE;
E 5
I 3

D 9
#define	RP(p)	(p->fts_path + 2)
E 9
I 9
#define	RP(p)	\
	((p)->fts_path[0] == '.' && (p)->fts_path[1] == '/' ? \
	    (p)->fts_path + 2 : (p)->fts_path)
E 9
E 3
E 1
