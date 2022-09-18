h35355
s 00001/00001/00096
d D 8.9 95/03/29 20:54:17 mckusick 71 70
c di_blocks needs to be unsigned so conversion to 64-bit size works (from karels)
e
s 00014/00008/00083
d D 8.8 95/03/21 00:34:38 mckusick 70 68
c daddr_t => ufs_daddr_t; timespecs go to explicit width fields
e
s 00013/00007/00084
d R 8.8 95/03/21 00:29:19 mckusick 69 68
c daddr_t => ufs_daddr_t; timespecs go to explicit width fields
e
s 00001/00001/00090
d D 8.7 95/01/02 23:40:37 mckusick 68 67
c quad => int64_t
e
s 00001/00000/00090
d D 8.6 94/09/13 11:37:53 mckusick 67 66
c add whiteout type
e
s 00008/00000/00082
d D 8.5 94/08/10 23:54:39 pendry 66 65
c add whiteout inode number
e
s 00011/00011/00071
d D 8.4 94/07/08 23:17:33 mckusick 65 64
c changes for 64-bit machines (from bostic)
e
s 00005/00000/00077
d D 8.3 94/01/21 17:30:48 bostic 64 63
c add USL's copyright notice
e
s 00037/00036/00040
d D 8.2 93/09/21 07:20:39 bostic 63 62
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00074
d D 8.1 93/06/11 16:28:24 bostic 62 61
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00075
d D 7.20 93/03/03 17:52:54 bostic 61 60
c it's used now, it's also a u_long
e
s 00001/00001/00075
d D 7.19 92/11/02 17:11:02 mckusick 60 59
c increase the size of MAXSYMLINKLEN to include indirect block pointers
e
s 00007/00002/00069
d D 7.18 92/06/24 14:26:02 mckusick 59 58
c union for storing inode number in on-disk inode
e
s 00009/00000/00062
d D 7.17 92/06/23 17:24:07 mckusick 58 57
c add provision for short symbolic links
e
s 00001/00012/00061
d D 7.16 92/06/20 11:19:50 mckusick 57 56
c eliminate fiction of NOQUAD
e
s 00003/00003/00070
d D 7.15 92/06/18 18:15:31 mckusick 56 55
c timeval => timespec
e
s 00016/00017/00057
d D 7.14 92/05/13 14:57:07 mckusick 55 54
c new 64-bit file sizes, 32-bit uid, gid, and dev's
e
s 00009/00008/00065
d D 7.13 91/12/19 13:00:33 mckusick 54 53
c select di_size based on _NOQUAD support
e
s 00008/00000/00065
d D 7.12 91/11/11 11:27:23 bostic 53 52
c move ROOTINO here, so applications don't have to include ufsmount.h
e
s 00005/00000/00060
d D 7.11 91/11/01 17:54:41 bostic 52 51
c don't assume unless BYTE_ORDER is defined
e
s 00013/00012/00047
d D 7.10 91/05/08 19:26:43 mckusick 51 50
c make comments more precise
e
s 00001/00011/00058
d D 7.9 90/06/28 22:29:27 bostic 50 49
c new copyright notice
e
s 00003/00004/00066
d D 7.8 90/05/15 16:58:38 mckusick 49 48
c file size is unsigned
e
s 00001/00000/00069
d D 7.7 90/03/05 18:09:39 mckusick 48 47
c add FIFO type
e
s 00023/00182/00046
d D 7.6 89/10/24 19:35:29 mckusick 47 46
c split out that part of inode.h that is relevant to the disk node
e
s 00001/00000/00227
d D 7.5 89/07/03 23:43:20 mckusick 46 45
c add spare fields for future use
e
s 00005/00001/00222
d D 7.4 89/06/07 16:43:56 mckusick 45 44
c implementation of generation numbers
e
s 00065/00040/00158
d D 7.3 89/05/09 16:00:34 mckusick 44 43
c merge in vnodes
e
s 00003/00003/00195
d D 7.2 86/10/13 20:59:51 karels 43 42
c merge in tahoe system
e
s 00001/00001/00197
d D 7.1 86/06/04 23:23:42 mckusick 42 41
c 4.3BSD release version
e
s 00000/00001/00198
d D 6.11 85/11/26 12:37:52 karels 41 40
c now can use XTRC again instead of IXMOD
e
s 00001/00000/00198
d D 6.10 85/11/09 16:38:07 karels 40 39
c keep pointer to text in inode, avoiding linear search (later will be pointer
c to region(s) mapping the file)
e
s 00002/00002/00196
d D 6.9 85/10/28 15:04:03 karels 39 38
c use proper types for uids, gids
e
s 00007/00001/00191
d D 6.8 85/06/08 14:59:10 mckusick 38 37
c Add copyright
e
s 00001/00005/00191
d D 6.7 85/01/10 23:40:51 mckusick 37 36
c simplify (and fix) cacheinval macro
e
s 00001/00000/00195
d D 6.6 84/12/20 15:42:17 karels 36 35
c add IXMOD for now (for text modified with ptrace)
e
s 00001/00000/00194
d D 6.5 84/07/26 22:30:52 mckusick 35 34
c add IRENAME to prevent reentrant rename for same directory
e
s 00014/00000/00180
d D 6.4 84/07/20 01:11:25 mckusick 34 33
c add macro `cacheinval' to purge stale entries in the inode table
e
s 00002/00001/00178
d D 6.3 84/06/27 20:46:43 sam 33 32
c add unique id for namei cache -- allows . and .. to be held in cache
e
s 00016/00001/00163
d D 6.2 84/02/15 21:12:46 karels 32 31
c add IMOD flag, allowing update of times in in-core inode
c without immediate write to disk
e
s 00000/00000/00164
d D 6.1 83/07/29 06:12:39 sam 31 30
c 4.2 distribution
e
s 00000/00006/00164
d D 4.24 83/07/01 02:24:53 root 30 29
c purge #if sun's
e
s 00004/00001/00166
d D 4.23 83/05/21 15:59:50 sam 29 28
c i_blocks (from kre)
e
s 00001/00001/00166
d D 4.22 83/02/10 16:10:57 sam 28 27
c fix comment
e
s 00011/00000/00156
d D 4.21 82/12/17 12:10:58 sam 27 26
c sun merge
e
s 00025/00015/00131
d D 4.20 82/11/13 23:08:21 sam 26 25
c merge 4.1b and 4.1c
e
s 00001/00001/00145
d D 4.19 82/10/31 17:54:45 root 25 24
c i_socket is i_un.is_socket; i_un was missing
e
s 00002/00001/00144
d D 4.18 82/10/31 15:56:09 root 24 23
c s/PORTAL/SOCK/
e
s 00000/00001/00145
d D 4.17 82/10/20 02:10:06 root 23 22
c lint
e
s 00003/00003/00143
d D 4.16 82/10/20 01:16:06 root 22 21
c lint
e
s 00022/00001/00124
d D 4.15 82/10/10 17:12:31 root 21 20
c header file cleanup while moving vax files to their own directory
e
s 00013/00010/00112
d D 4.14 82/08/10 17:53:08 sam 20 19
c file locking and new open 
e
s 00002/00002/00120
d D 4.13 82/07/16 16:47:15 kre 19 18
c removed hlink (no longer used); added dquot (disc quota pointer);
c changed count from char to u_short (> 255 refs possible).
e
s 00009/00000/00113
d D 4.12 82/06/29 23:01:07 kre 18 17
c inode cache added (Chris Maltby, Sydney Uni originated this)
e
s 00074/00042/00039
d D 4.11 82/04/19 19:26:55 mckusic 17 16
c merge in the new file system
e
s 00001/00002/00080
d D 4.10 82/02/27 14:56:13 wnj 16 15
c symbolic links
e
s 00019/00012/00063
d D 4.9 81/11/14 16:50:58 wnj 15 14
c just before overlay of ip
e
s 00012/00023/00063
d D 4.8 81/11/08 16:44:25 wnj 14 13
c remove vfdcnt, IPIPE and IFPORT
e
s 00000/00017/00086
d D 4.7 81/10/17 16:14:12 wnj 13 12
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00007/00000/00096
d D 4.6 81/06/15 18:07:34 root 12 11
c port id overlay
e
s 00002/00002/00094
d D 4.5 81/03/09 00:27:01 wnj 11 10
c lint
e
s 00002/00001/00094
d D 4.4 81/02/27 00:02:02 wnj 10 9
c move to pointer base to allow dyn allocation
e
s 00001/00001/00094
d D 4.3 81/02/19 21:40:47 wnj 9 8
c %G%->%E%
e
s 00001/00001/00094
d D 4.2 81/01/27 15:42:35 wnj 8 7
c reduce NINDEX to 6 to save a lot of space
e
s 00000/00000/00095
d D 4.1 80/11/09 17:01:05 bill 7 6
c stamp for 4bsd
e
s 00001/00001/00094
d D 3.6 80/06/07 02:58:01 bill 6 5
c %H%->%G%
e
s 00001/00001/00094
d D 3.5 80/06/04 14:59:28 bill 5 4
c repair from cosmetics
e
s 00001/00001/00094
d D 3.4 80/06/04 13:45:43 bill 4 3
c reformat
e
s 00010/00006/00085
d D 3.3 80/04/30 17:19:50 bill 3 2
c macros to get around new c compiler
e
s 00001/00000/00090
d D 3.2 80/04/11 10:17:46 bill 2 1
c add IPIPE bit for sake of writei
e
s 00090/00000/00000
d D 3.1 80/04/09 16:24:06 bill 1 0
c date and time created 80/04/09 16:24:06 by bill
e
u
U
t
T
I 1
D 6
/*	%M%	%I%	%H%	*/
E 6
I 6
D 9
/*	%M%	%I%	%G%	*/
E 9
I 9
D 38
/*	%M%	%I%	%E%	*/
E 38
I 38
/*
D 42
 * Copyright (c) 1982 Regents of the University of California.
E 42
I 42
D 43
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 43
I 43
D 44
 * Copyright (c) 1982 Regents of the University of California.
E 43
E 42
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 44
I 44
D 62
 * Copyright (c) 1982, 1989 The Regents of the University of California.
 * All rights reserved.
E 62
I 62
 * Copyright (c) 1982, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 64
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 64
E 62
E 44
 *
I 44
D 50
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
E 50
I 50
 * %sccs.include.redist.c%
E 50
 *
E 44
 *	%W% (Berkeley) %G%
 */
E 38
E 9
E 6

I 17
D 20
/*	inode.h	2.1	3/25/82	*/

E 20
E 17
/*
I 53
 * The root inode is the root of the file system.  Inode 0 can't be used for
 * normal purposes and historically bad blocks were linked to inode 1, thus
 * the root inode is 2.  (Inode 1 is no longer used for this purpose, however
 * numerous dump tapes make this assumption, so we are stuck with it).
 */
#define	ROOTINO	((ino_t)2)

/*
I 66
 * The Whiteout inode# is a dummy non-zero inode number which will
 * never be allocated to a real file.  It is used as a place holder
 * in the directory entry which has been tagged as a DT_W entry.
 * See the comments about ROOTINO above.
 */
#define	WINO	((ino_t)1)

/*
E 66
E 53
D 14
 * The I node is the focus of all
 * file activity in unix. There is a unique
 * inode allocated for each active file,
 * each current directory, each mounted-on
 * file, text file, and the root. An inode is 'named'
 * by its dev/inumber pair. (iget/iget.c)
 * Data, from mode on, is read in
 * from permanent inode on volume.
E 14
I 14
D 47
 * The I node is the focus of all file activity in UNIX.
 * There is a unique inode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 * An inode is 'named' by its dev/inumber pair. (iget/iget.c)
D 17
 * Data, from mode on, is read in from permanent inode on volume.
E 17
I 17
 * Data in icommon is read in from permanent inode on volume.
E 47
I 47
D 51
 * This structure defines the on-disk format of an inode.
E 51
I 51
 * A dinode contains all the meta-data associated with a UFS file.
D 70
 * This structure defines the on-disk format of a dinode.
E 70
I 70
 * This structure defines the on-disk format of a dinode. Since
 * this structure describes an on-disk structure, all its fields
 * are defined by types with precise widths.
E 70
E 51
E 47
E 17
E 14
 */
D 14

E 14
D 17
#define	NADDR	13
E 17

I 70
typedef int32_t ufs_daddr_t;
E 70
I 17
D 26
#define	NDADDR	8		/* direct addresses in inode */
#define	NIADDR	2		/* indirect addresses in inode */
E 26
I 26
D 63
#define	NDADDR	12		/* direct addresses in inode */
#define	NIADDR	3		/* indirect addresses in inode */
E 63
I 63
#define	NDADDR	12			/* Direct addresses in inode. */
#define	NIADDR	3			/* Indirect addresses in inode. */
E 63
E 26

E 17
D 8
#define	NINDEX		15
E 8
I 8
D 13
#define	NINDEX		6
E 8
struct group
{
	short	g_state;
	char	g_index;
	char	g_rot;
	struct	group	*g_group;
	struct	inode	*g_inode;
	struct	file	*g_file;
	short	g_rotmask;
	short	g_datq;
	struct	chan *g_chans[NINDEX];
};
E 13
D 14
struct	inode
{
E 14
I 14
D 47
struct inode {
I 18
	struct	inode *i_chain[2];	/* must be first */
I 44
	struct	vnode i_vnode;	/* vnode associated with this inode */
	struct	vnode *i_devvp;	/* vnode for block I/O */
E 44
E 18
E 14
D 20
	char	i_flag;
E 20
I 20
	u_short	i_flag;
E 20
D 19
	char	i_count;	/* reference count */
E 19
I 19
D 44
	u_short	i_count;	/* reference count */
E 44
E 19
	dev_t	i_dev;		/* device where inode resides */
I 20
D 26
	u_short	i_rdlockc;	/* count of locked readers on inode */
	u_short	i_wrlockc;	/* count of locked writers on inode */
E 26
I 26
D 44
	u_short	i_shlockc;	/* count of shared locks on inode */
	u_short	i_exlockc;	/* count of exclusive locks on inode */
E 44
E 26
E 20
	ino_t	i_number;	/* i number, 1-to-1 with device address */
I 33
	long	i_id;		/* unique identifier */
I 44
	long	i_diroff;	/* offset in dir, where we found last entry */
E 44
E 33
D 14
	unsigned short i_mode;
E 14
I 14
D 17
/* begin read from disk */
	u_short	i_mode;
E 14
	short	i_nlink;	/* directory entries */
	short	i_uid;		/* owner */
	short	i_gid;		/* group of owner */
	off_t	i_size;		/* size of file */
E 17
I 17
D 19
	long	i_hlink;	/* link in hash chain (iget/iput/ifind) */
E 19
	struct	fs *i_fs;	/* file sys associated with this inode */
I 19
	struct	dquot *i_dquot;	/* quota structure controlling this file */
I 40
	struct	text *i_text;	/* text entry, if any (should be region) */
I 44
	struct	inode *i_devlst;/* list of block device inodes */
	off_t	i_endoff;	/* end of useful stuff in directory */
I 46
	long	i_spare[4];
E 46
E 44
E 40
E 19
E 17
	union {
D 15
		struct {
D 3
			daddr_t	i_addr[NADDR];	/* if normal file/directory */
			daddr_t	i_lastr;	/* last logical block read (for read-ahead) */
		};
E 3
I 3
			daddr_t	I_addr[NADDR];	/* if normal file/directory */
D 4
			daddr_t	I_lastr;	/* last logical block read (for read-ahead) */
E 4
I 4
D 5
			daddr_t	I_last bnor;	/* last read (for read-ahead) */
E 5
I 5
D 14
			daddr_t	I_lastr;	/* last read (for read-ahead) */
E 14
I 14
			daddr_t	I_lastr;	/* last read (read-ahead) */
E 15
I 15
D 17
		struct i_f {
			daddr_t	if_addr[NADDR];	/* if normal file/directory */
			daddr_t	if_lastr;	/* last read (read-ahead) */
E 15
E 14
E 5
E 4
		} i_f;
D 15
#define	i_addr	i_f.I_addr
#define	i_lastr	i_f.I_lastr
E 3
		struct {
D 3
			daddr_t	i_rdev;		/* i_addr[0] */
			struct	group i_group;	/* multiplexor group file */
		};
E 3
I 3
			daddr_t	I_rdev;		/* i_addr[0] */
E 15
I 15
		struct i_d {
			daddr_t	id_rdev;	/* i_addr[0] */
E 15
D 13
			struct	group I_group;	/* multiplexor group file */
E 13
		} i_d;
D 15
#define	i_rdev	i_d.I_rdev
E 15
I 15
		struct i_s {
			struct	socket *is_socket;
		} i_s;
#define	i_addr		i_f.if_addr
#define	i_lastr		i_f.if_lastr
#define	i_rdev		i_d.id_rdev
#define	i_socket	i_s.is_socket
E 17
I 17
		daddr_t	if_lastr;	/* last read (read-ahead) */
		struct	socket *is_socket;
I 18
		struct	{
			struct inode  *if_freef;	/* free list forward */
			struct inode **if_freeb;	/* free list back */
		} i_fr;
E 18
E 17
E 15
D 13
#define	i_group	i_d.I_group
E 13
I 12
D 14
		struct {
			daddr_t	I_port0;	/* low 16 bits of portid */
			daddr_t	I_port1;	/* high 16 bits of portid */
		} i_p;
#define	i_port0	i_p.I_port0
#define	i_port1	i_p.I_port1
E 14
E 12
E 3
	} i_un;
D 14
	short	i_vfdcnt;	/* number of fd's vreading this inode */
E 14
I 14
D 17
/* end read from disk */
	short	i_XXXXXX;	/* ### */
/* SHOULD USE POINTERS, NOT INDICES, FOR HAS CHAIN */
E 14
	short	i_hlink;	/* link in hash chain (iget/iput/ifind) */
E 17
I 17
	struct 	icommon
	{
		u_short	ic_mode;	/*  0: mode and type of file */
		short	ic_nlink;	/*  2: number of links to file */
D 39
		short	ic_uid;		/*  4: owner's user id */
		short	ic_gid;		/*  6: owner's group id */
E 39
I 39
		uid_t	ic_uid;		/*  4: owner's user id */
		gid_t	ic_gid;		/*  6: owner's group id */
E 39
D 26
		off_t	ic_size;	/*  8: number of bytes in file */
		daddr_t	ic_db[NDADDR];	/* 12: disk block addresses */
		daddr_t	ic_ib[NIADDR];	/* 44: indirect blocks */
		time_t	ic_atime;	/* 52: time last accessed */
		time_t	ic_mtime;	/* 56: time last modified */
		time_t	ic_ctime;	/* 60: time created */
E 26
I 26
		quad	ic_size;	/*  8: number of bytes in file */
		time_t	ic_atime;	/* 16: time last accessed */
		long	ic_atspare;
		time_t	ic_mtime;	/* 24: time last modified */
		long	ic_mtspare;
D 28
		time_t	ic_ctime;	/* 32: time created */
E 28
I 28
		time_t	ic_ctime;	/* 32: last time inode changed */
E 28
		long	ic_ctspare;
		daddr_t	ic_db[NDADDR];	/* 40: disk block addresses */
		daddr_t	ic_ib[NIADDR];	/* 88: indirect blocks */
		long	ic_flags;	/* 100: status, currently unused */
D 29
		long	ic_spare[6];	/* 104: reserved, currently unused */
E 29
I 29
		long	ic_blocks;	/* 104: blocks actually held */
D 44
		long	ic_spare[5];	/* 108: reserved, currently unused */
E 44
I 44
		long	ic_gen;		/* 108: generation number */
		long	ic_spare[4];	/* 112: reserved, currently unused */
E 44
E 29
E 26
	} i_ic;
E 17
};

E 47
I 17
struct dinode {
D 47
	union {
		struct	icommon di_icom;
D 26
		char	di_size[64];
E 26
I 26
		char	di_size[128];
E 26
	} di_un;
E 47
I 47
D 55
	u_short	di_mode;	/*  0: mode and type of file */
	short	di_nlink;	/*  2: number of links to file */
	uid_t	di_uid;		/*  4: owner's user id */
	gid_t	di_gid;		/*  6: owner's group id */
D 49
	quad	di_qsize;	/*  8: number of bytes in file */
E 49
I 49
D 54
	u_quad	di_qsize;	/*  8: number of bytes in file */
E 54
I 54
	u_quad_t di_qsize;	/*  8: number of bytes in file */
E 54
E 49
	time_t	di_atime;	/* 16: time last accessed */
	long	di_atspare;
	time_t	di_mtime;	/* 24: time last modified */
	long	di_mtspare;
	time_t	di_ctime;	/* 32: last time inode changed */
	long	di_ctspare;
	daddr_t	di_db[NDADDR];	/* 40: disk block addresses */
	daddr_t	di_ib[NIADDR];	/* 88: indirect blocks */
	long	di_flags;	/* 100: status, currently unused */
	long	di_blocks;	/* 104: blocks actually held */
	long	di_gen;		/* 108: generation number */
	long	di_spare[4];	/* 112: reserved, currently unused */
E 55
I 55
D 63
	u_short		di_mode;	/*   0: mode and type of file */
	short		di_nlink;	/*   2: number of links to file */
E 63
I 63
D 65
	u_short		di_mode;	/*   0: IFMT and permissions. */
	short		di_nlink;	/*   2: File link count. */
E 65
I 65
	u_int16_t	di_mode;	/*   0: IFMT, permissions; see below. */
	int16_t		di_nlink;	/*   2: File link count. */
E 65
E 63
D 59
	u_short		di_ouid;	/*   4: old owner's user id */
	u_short		di_ogid;	/*   6: old owner's group id */
E 59
I 59
	union {
D 63
		u_short	oldids[2];	/*   4: ffs: old user and group ids */
		ino_t	inumber;	/*   4: lfs: inode number */
E 63
I 63
D 65
		u_short	oldids[2];	/*   4: Ffs: old user and group ids. */
		ino_t	inumber;	/*   4: Lfs: inode number. */
E 65
I 65
		u_int16_t oldids[2];	/*   4: Ffs: old user and group ids. */
D 70
		ino_t	  inumber;	/*   4: Lfs: inode number. */
E 70
I 70
		int32_t	  inumber;	/*   4: Lfs: inode number. */
E 70
E 65
E 63
	} di_u;
E 59
D 57
	u_quad_t	di_qsize;	/*   8: number of bytes in file */
E 57
I 57
D 63
	u_quad_t	di_size;	/*   8: number of bytes in file */
E 57
D 56
	struct timeval	di_atime;	/*  16: time last accessed */
	struct timeval	di_mtime;	/*  24: time last modified */
	struct timeval	di_ctime;	/*  32: last time inode changed */
E 56
I 56
	struct timespec	di_atime;	/*  16: time last accessed */
	struct timespec	di_mtime;	/*  24: time last modified */
	struct timespec	di_ctime;	/*  32: last time inode changed */
E 56
	daddr_t		di_db[NDADDR];	/*  40: disk block addresses */
	daddr_t		di_ib[NIADDR];	/*  88: indirect blocks */
D 61
	long		di_flags;	/* 100: status, currently unused */
E 61
I 61
	u_long		di_flags;	/* 100: status flags */
E 61
	long		di_blocks;	/* 104: blocks actually held */
	long		di_gen;		/* 108: generation number */
	u_long		di_uid;		/* 112: owner's user id */
	u_long		di_gid;		/* 116: owner's group id */
	long		di_spare[2];	/* 120: reserved, currently unused */
E 63
I 63
D 68
	u_quad_t	di_size;	/*   8: File byte count. */
E 68
I 68
	u_int64_t	di_size;	/*   8: File byte count. */
E 68
D 70
	struct timespec	di_atime;	/*  16: Last access time. */
	struct timespec	di_mtime;	/*  24: Last modified time. */
	struct timespec	di_ctime;	/*  32: Last inode change time. */
	daddr_t		di_db[NDADDR];	/*  40: Direct disk blocks. */
	daddr_t		di_ib[NIADDR];	/*  88: Indirect disk blocks. */
E 70
I 70
	int32_t		di_atime;	/*  16: Last access time. */
	int32_t		di_atimensec;	/*  20: Last access time. */
	int32_t		di_mtime;	/*  24: Last modified time. */
	int32_t		di_mtimensec;	/*  28: Last modified time. */
	int32_t		di_ctime;	/*  32: Last inode change time. */
	int32_t		di_ctimensec;	/*  36: Last inode change time. */
	ufs_daddr_t	di_db[NDADDR];	/*  40: Direct disk blocks. */
	ufs_daddr_t	di_ib[NIADDR];	/*  88: Indirect disk blocks. */
E 70
D 65
	u_long		di_flags;	/* 100: Status flags (chflags). */
	long		di_blocks;	/* 104: Blocks actually held. */
	long		di_gen;		/* 108: Generation number. */
	u_long		di_uid;		/* 112: File owner. */
	u_long		di_gid;		/* 116: File group. */
	long		di_spare[2];	/* 120: Reserved; currently unused */
E 65
I 65
	u_int32_t	di_flags;	/* 100: Status flags (chflags). */
D 71
	int32_t		di_blocks;	/* 104: Blocks actually held. */
E 71
I 71
	u_int32_t	di_blocks;	/* 104: Blocks actually held. */
E 71
	int32_t		di_gen;		/* 108: Generation number. */
	u_int32_t	di_uid;		/* 112: File owner. */
	u_int32_t	di_gid;		/* 116: File group. */
	int32_t		di_spare[2];	/* 120: Reserved; currently unused */
E 65
E 63
E 55
E 47
};
D 57

I 52
D 54
#ifdef BYTE_ORDER
E 52
D 47
#define	i_mode		i_ic.ic_mode
#define	i_nlink		i_ic.ic_nlink
#define	i_uid		i_ic.ic_uid
#define	i_gid		i_ic.ic_gid
E 47
I 27
D 49
/* ugh! -- must be fixed */
D 43
#ifdef vax
E 43
I 43
#if defined(vax) || defined(tahoe)
E 49
I 49
#if BYTE_ORDER == LITTLE_ENDIAN || defined(tahoe) /* ugh! -- must be fixed */
E 49
E 43
E 27
D 26
#define	i_size		i_ic.ic_size
E 26
I 26
D 47
#define	i_size		i_ic.ic_size.val[0]
E 47
I 47
#define	di_size		di_qsize.val[0]
D 49
#else
E 49
I 49
#else /* BYTE_ORDER == BIG_ENDIAN */
E 49
#define	di_size		di_qsize.val[1]
E 47
I 27
#endif
E 54
I 54
#ifdef _NOQUAD
#define di_size	di_qsize.val[_QUAD_LOWWORD]
E 54
I 52
#else
D 54
#define	di_size		BYTE_ORDER_UNDEFINED
E 54
I 54
#define di_size	di_qsize
#endif

#if defined(tahoe) /* ugh! -- must be fixed */
#undef di_size
#define	di_size		di_qsize.val[0]
E 54
#endif
E 57

I 58
/*
 * The di_db fields may be overlaid with other information for
 * file types that do not have associated disk storage. Block
 * and character devices overlay the first data block with their
 * dev_t value. Short symbolic links place their path in the
 * di_db area.
 */
I 59
D 63
#define	di_ouid		di_u.oldids[0]
#define	di_ogid		di_u.oldids[1]
E 63
#define	di_inumber	di_u.inumber
I 63
#define	di_ogid		di_u.oldids[1]
#define	di_ouid		di_u.oldids[0]
E 63
E 59
E 58
E 52
D 30
#ifdef sun
#define	i_size		i_ic.ic_size.val[1]
#endif
E 30
E 27
E 26
D 47
#define	i_db		i_ic.ic_db
#define	i_ib		i_ic.ic_ib
#define	i_atime		i_ic.ic_atime
#define	i_mtime		i_ic.ic_mtime
#define	i_ctime		i_ic.ic_ctime
I 29
#define i_blocks	i_ic.ic_blocks
E 29
#define	i_rdev		i_ic.ic_db[0]
I 45
#define i_flags		i_ic.ic_flags
E 45
I 44
#define i_gen		i_ic.ic_gen
E 44
#define	i_lastr		i_un.if_lastr
D 25
#define	i_socket	is_socket
E 25
I 25
#define	i_socket	i_un.is_socket
E 25
I 18
#define	i_forw		i_chain[0]
#define	i_back		i_chain[1]
#define	i_freef		i_un.i_fr.if_freef
#define	i_freeb		i_un.i_fr.if_freeb
E 47
I 47
#define	di_rdev		di_db[0]
I 58
D 63
#define di_shortlink	di_db
E 63
I 63
#define	di_shortlink	di_db
E 63
D 60
#define	MAXSYMLINKLEN	(NDADDR * sizeof(daddr_t))
E 60
I 60
D 70
#define	MAXSYMLINKLEN	((NDADDR + NIADDR) * sizeof(daddr_t))
E 70
I 70
#define	MAXSYMLINKLEN	((NDADDR + NIADDR) * sizeof(ufs_daddr_t))
E 70
E 60
E 58
E 47
E 18

D 47
#define di_ic		di_un.di_icom
#define	di_mode		di_ic.ic_mode
#define	di_nlink	di_ic.ic_nlink
#define	di_uid		di_ic.ic_uid
#define	di_gid		di_ic.ic_gid
I 27
D 43
#ifdef vax
E 43
I 43
#if defined(vax) || defined(tahoe)
E 43
E 27
D 26
#define	di_size		di_ic.ic_size
E 26
I 26
#define	di_size		di_ic.ic_size.val[0]
I 27
D 30
#endif
#ifdef sun
#define	di_size		di_ic.ic_size.val[1]
E 30
#endif
E 27
E 26
#define	di_db		di_ic.ic_db
#define	di_ib		di_ic.ic_ib
#define	di_atime	di_ic.ic_atime
#define	di_mtime	di_ic.ic_mtime
#define	di_ctime	di_ic.ic_ctime
#define	di_rdev		di_ic.ic_db[0]
I 29
#define	di_blocks	di_ic.ic_blocks
I 45
#define	di_flags	di_ic.ic_flags
E 45
I 44
#define	di_gen		di_ic.ic_gen
E 44
E 29

E 17
#ifdef KERNEL
I 34
D 44
/*
 * Invalidate an inode. Used by the namei cache to detect stale
 * information. At an absurd rate of 100 calls/second, the inode
 * table invalidation should only occur once every 16 months.
 */
#define cacheinval(ip)	\
D 37
{ \
	struct inode *xp; \
E 37
	(ip)->i_id = ++nextinodeid; \
	if (nextinodeid == 0) \
D 37
		for (nextinodeid = 0, xp = inode; xp < inodeNINODE; xp++) \
			xp->i_id = 0; \
}
E 37
I 37
		cacheinvalall();
E 37

E 44
E 34
D 10
extern	struct inode inode[];	/* The inode table itself */
E 10
I 10
D 11
extern	struct inode *inode, *inodeNINODE;/* The inode table itself */
extern	int ninode;
E 11
I 11
D 17
struct	inode *inode, *inodeNINODE;
int	ninode;
E 17
I 17
D 22
extern	struct inode *inode;		/* The inode table itself */
extern	struct inode *inodeNINODE;	/* The end of the inode table */
extern	int ninode;			/* number of slots in the table */
E 22
I 22
struct inode *inode;		/* the inode table itself */
struct inode *inodeNINODE;	/* the end of the inode table */
int	ninode;			/* number of slots in the table */
I 33
D 44
long	nextinodeid;		/* unique id generator */
E 44
E 33
E 22
E 17
E 11
E 10

I 45
u_long	nextgennumber;		/* next generation number to assign */

E 45
D 17
struct	inode *rootdir;		/* pointer to inode of root directory */
E 17
I 17
D 44
struct	inode *rootdir;			/* pointer to inode of root directory */
E 44
I 44
extern struct vnodeops ufs_vnodeops;	/* vnode operations for ufs */
extern struct vnodeops blk_vnodeops;	/* vnode operations for blk devices */
E 44
E 17
D 14
struct	inode *mpxip;		/* mpx virtual inode */
E 14

D 44
struct	inode *ialloc();
D 23
struct	inode *ifind();
E 23
struct	inode *iget();
I 26
#ifdef notdef
struct	inode *ifind();
E 44
I 44
extern ino_t	dirpref();
E 44
#endif
E 26
D 44
struct	inode *owner();
struct	inode *maknode();
struct	inode *namei();
E 44
I 26

D 44
ino_t	dirpref();
E 26
#endif

E 44
/* flags */
D 20
#define	ILOCK	01		/* inode is locked */
#define	IUPD	02		/* file has been modified */
#define	IACC	04		/* inode access time to be updated */
#define	IMOUNT	010		/* inode is mounted on */
#define	IWANT	020		/* some process waiting on lock */
#define	ITEXT	040		/* inode is pure text prototype */
#define	ICHG	0100		/* inode has been changed */
E 20
I 20
D 21
#define	ILOCK		0x1		/* inode is locked */
E 21
I 21
#define	ILOCKED		0x1		/* inode is locked */
E 21
#define	IUPD		0x2		/* file has been modified */
#define	IACC		0x4		/* inode access time to be updated */
D 44
#define	IMOUNT		0x8		/* inode is mounted on */
#define	IWANT		0x10		/* some process waiting on lock */
#define	ITEXT		0x20		/* inode is pure text prototype */
#define	ICHG		0x40		/* inode has been changed */
D 26
#define	IRDLOCK		0x80		/* file is read locked */
#define	IWRLOCK		0x100		/* file is write locked */
E 26
I 26
#define	ISHLOCK		0x80		/* file has shared lock */
#define	IEXLOCK		0x100		/* file has exclusive lock */
E 26
#define	ILWAIT		0x200		/* someone waiting on file lock */
I 32
#define	IMOD		0x400		/* inode has been modified */
I 35
#define	IRENAME		0x800		/* inode is being renamed */
E 44
I 44
#define	IWANT		0x8		/* some process waiting on lock */
#define	ICHG		0x10		/* inode has been changed */
#define	ISHLOCK		0x20		/* file has shared lock */
#define	IEXLOCK		0x40		/* file has exclusive lock */
#define	ILWAIT		0x80		/* someone waiting on file lock */
#define	IMOD		0x100		/* inode has been modified */
#define	IRENAME		0x200		/* inode is being renamed */
E 44
I 36
D 41
#define	IXMOD		0x8000		/* inode is text, but impure (XXX) */
E 41
E 36
E 35
E 32
E 20
I 2
D 14
#define	IPIPE	0200		/* inode is a pipe */
E 14
E 2

/* modes */
E 47
I 47
D 63
/* file modes */
E 47
D 17
#define	IFMT	0170000		/* type of file */
D 15
#define		IFDIR	0040000	/* directory */
#define		IFCHR	0020000	/* character special */
#define		IFBLK	0060000	/* block special */
#define		IFREG	0100000	/* regular */
E 15
I 15
#define		IFCHR		0020000		/* character special */
#define		IFDIR		0040000		/* directory */
#define		IFBLK		0060000		/* block special */
#define		IFREG		0100000		/* regular */
D 16
#define		IFSYMREG	0110000		/* regular symbolic link */
#define		IFSYMDIR	0130000		/* directory symbolic link */
E 16
I 16
#define		IFLNK		0120000		/* symbolic link */
E 16
#define		IFPORTAL	0140000		/* portal */
E 15
I 12
D 14
#define		IFPORT	0010000	/* named port */
E 14
E 12
D 13
#define		IFMPC	0030000	/* multiplexed char special */
#define		IFMPB	0070000	/* multiplexed block special */
E 13
#define	ISUID	04000		/* set user id on execution */
#define	ISGID	02000		/* set group id on execution */
#define	ISVTX	01000		/* save swapped text even after use */
#define	IREAD	0400		/* read, write, execute permissions */
#define	IWRITE	0200
#define	IEXEC	0100
E 17
I 17
D 51
#define	IFMT		0170000		/* type of file */
E 51
I 51
#define	IFMT		0170000		/* mask of file type */
E 51
I 48
#define	IFIFO		0010000		/* named pipe (fifo) */
E 48
D 51
#define	IFCHR		0020000		/* character special */
E 51
I 51
#define	IFCHR		0020000		/* character special device */
E 51
#define	IFDIR		0040000		/* directory */
D 51
#define	IFBLK		0060000		/* block special */
#define	IFREG		0100000		/* regular */
E 51
I 51
#define	IFBLK		0060000		/* block special device */
#define	IFREG		0100000		/* regular file */
E 51
#define	IFLNK		0120000		/* symbolic link */
D 24
#define	IFPORTAL	0140000		/* portal */
E 24
I 24
D 51
#define	IFSOCK		0140000		/* socket */
E 51
I 51
#define	IFSOCK		0140000		/* UNIX domain socket */
E 63
I 63
D 65
/* File modes. */
E 65
I 65
/* File permissions. */
E 65
#define	IEXEC		0000100		/* Executable. */
#define	IWRITE		0000200		/* Writeable. */
#define	IREAD		0000400		/* Readable. */
#define	ISVTX		0001000		/* Sticky bit. */
#define	ISGID		0002000		/* Set-gid. */
#define	ISUID		0004000		/* Set-uid. */
E 63
E 51

E 24
D 51
#define	ISUID		04000		/* set user id on execution */
#define	ISGID		02000		/* set group id on execution */
#define	ISVTX		01000		/* save swapped text even after use */
#define	IREAD		0400		/* read, write, execute permissions */
#define	IWRITE		0200
#define	IEXEC		0100
E 51
I 51
D 63
#define	ISUID		04000		/* set user identifier when exec'ing */
#define	ISGID		02000		/* set group identifier when exec'ing */
#define	ISVTX		01000		/* save execution information on exit */
#define	IREAD		0400		/* read permission */
#define	IWRITE		0200		/* write permission */
#define	IEXEC		0100		/* execute permission */
E 63
I 63
/* File types. */
#define	IFMT		0170000		/* Mask of file type. */
#define	IFIFO		0010000		/* Named pipe (fifo). */
#define	IFCHR		0020000		/* Character device. */
#define	IFDIR		0040000		/* Directory file. */
#define	IFBLK		0060000		/* Block device. */
#define	IFREG		0100000		/* Regular file. */
#define	IFLNK		0120000		/* Symbolic link. */
#define	IFSOCK		0140000		/* UNIX domain socket. */
I 67
#define	IFWHT		0160000		/* Whiteout. */
E 67
E 63
E 51
I 21
D 47

I 44
#ifdef KERNEL
/*
 * Convert between inode pointers and vnode pointers
 */
#define VTOI(vp)	((struct inode *)(vp)->v_data)
D 45
#define ITOV(ip)	((struct vnode *)&(ip)->i_vnode)
E 45
I 45
#define ITOV(ip)	(&(ip)->i_vnode)
E 45

/*
 * Convert between vnode types and inode formats
 */
extern enum vtype	iftovt_tab[];
extern int		vttoif_tab[];
#define IFTOVT(mode)	(iftovt_tab[((mode) & IFMT) >> 13])
#define VTTOIF(indx)	(vttoif_tab[(int)(indx)])

#define MAKEIMODE(indx, mode)	(int)(VTTOIF(indx) | (mode))

/*
 * Lock and unlock inodes.
 */
E 44
#define	ILOCK(ip) { \
	while ((ip)->i_flag & ILOCKED) { \
		(ip)->i_flag |= IWANT; \
D 44
		sleep((caddr_t)(ip), PINOD); \
E 44
I 44
		(void) sleep((caddr_t)(ip), PINOD); \
E 44
	} \
	(ip)->i_flag |= ILOCKED; \
}

#define	IUNLOCK(ip) { \
	(ip)->i_flag &= ~ILOCKED; \
	if ((ip)->i_flag&IWANT) { \
		(ip)->i_flag &= ~IWANT; \
		wakeup((caddr_t)(ip)); \
	} \
}

#define	IUPDAT(ip, t1, t2, waitfor) { \
D 32
	if (ip->i_flag&(IUPD|IACC|ICHG)) \
E 32
I 32
	if (ip->i_flag&(IUPD|IACC|ICHG|IMOD)) \
E 32
D 44
		iupdat(ip, t1, t2, waitfor); \
E 44
I 44
		(void) iupdat(ip, t1, t2, waitfor); \
E 44
}
I 32

#define	ITIMES(ip, t1, t2) { \
	if ((ip)->i_flag&(IUPD|IACC|ICHG)) { \
		(ip)->i_flag |= IMOD; \
		if ((ip)->i_flag&IACC) \
			(ip)->i_atime = (t1)->tv_sec; \
		if ((ip)->i_flag&IUPD) \
			(ip)->i_mtime = (t2)->tv_sec; \
		if ((ip)->i_flag&ICHG) \
			(ip)->i_ctime = time.tv_sec; \
		(ip)->i_flag &= ~(IACC|IUPD|ICHG); \
	} \
}
I 44

/*
 * This overlays the fid sturcture (see mount.h)
 */
struct ufid {
	u_short	ufid_len;
	ino_t	ufid_ino;
	long	ufid_gen;
};
#endif
E 47
E 44
D 33

E 33
E 32
E 21
E 17
E 1
