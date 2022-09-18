h45393
s 00005/00000/00131
d D 8.4 94/01/21 17:30:50 bostic 79 78
c add USL's copyright notice
e
s 00016/00016/00115
d D 8.3 93/09/23 16:00:10 bostic 78 77
c changes for 4.4BSD-Lite requested by USL
e
s 00068/00069/00063
d D 8.2 93/09/21 07:20:40 bostic 77 76
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00130
d D 8.1 93/06/11 16:28:32 bostic 76 75
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00130
d D 7.34 93/05/30 14:49:17 mckusick 75 74
c mv spares to allow for quad alignment of dinode
e
s 00002/00002/00130
d D 7.33 93/05/28 18:48:04 mckusick 74 73
c adjust spares to account for bigger pid's
e
s 00000/00022/00132
d D 7.32 92/11/14 23:18:56 mckusick 73 72
c ILOCK and IUNLOCK are gone, now always use VOP_LOCK and VOP_UNLOCK
e
s 00002/00001/00152
d D 7.31 92/10/22 18:42:36 margo 72 71
c Add exists field to indir structure.  Make logical block a daddr_t.
e
s 00009/00000/00144
d D 7.30 92/10/07 17:00:51 margo 71 70
c Add indir structure.
e
s 00002/00003/00142
d D 7.29 92/07/20 00:30:27 mckusick 70 69
c updated hashing scheme
e
s 00002/00001/00143
d D 7.28 92/06/23 17:24:36 mckusick 69 68
c add i_shortlink name for short symbolic links
e
s 00002/00010/00142
d D 7.27 92/06/20 11:19:47 mckusick 68 67
c eliminate fiction of NOQUAD
e
s 00003/00003/00149
d D 7.26 92/06/19 19:21:27 mckusick 67 66
c timeval => timespec in vattr and dinode
e
s 00001/00001/00151
d D 7.25 92/05/31 22:28:22 mckusick 66 65
c quad's need to be quad aligned
e
s 00003/00004/00149
d D 7.24 92/05/13 15:00:10 mckusick 65 64
c 32-bit dev, inode times are now stroed in timevals
e
s 00012/00003/00141
d D 7.23 92/03/27 15:52:38 mckusick 64 63
c define doff_t for size of directory offsets
e
s 00000/00008/00144
d D 7.22 92/02/06 17:54:51 mckusick 63 62
c move IFMT => VTYPE and VTYPE => IFMT to vnode since stat requires it
e
s 00013/00003/00139
d D 7.21 92/02/04 14:30:54 mckusick 62 61
c move in ufs specific fields from the nameidata structure
e
s 00011/00005/00131
d D 7.20 91/12/19 13:01:18 mckusick 61 60
c select i_size base on _NOQUAD support; update modrev for NFS leases
e
s 00005/00002/00131
d D 7.19 91/12/16 15:27:47 mckusick 60 59
c reorganize for private allocation; make use of spares consistent;
c add modrev for NFS
e
s 00013/00084/00120
d D 7.18 91/11/01 17:55:55 bostic 59 58
c add LFS version 1, UFS/FFS split for LFS version 1;
c move prototypes to ufs_extern.h
e
s 00064/00147/00140
d D 7.17 91/05/08 19:22:04 mckusick 58 57
c new format for prototypes; make comments more precise
e
s 00142/00001/00145
d D 7.16 91/04/16 00:07:52 mckusick 57 56
c add prototypes for UFS vnode operations
e
s 00001/00000/00145
d D 7.15 91/02/01 16:27:55 mckusick 56 55
c add POSIX-style byte-level record locking
e
s 00001/00001/00144
d D 7.14 90/10/24 11:37:56 mckusick 55 54
c typo in comment
e
s 00004/00013/00141
d D 7.13 90/05/10 15:11:12 mckusick 54 53
c define i_size based on BYTE_ORDER
e
s 00001/00002/00153
d D 7.12 90/05/02 19:28:26 mckusick 53 52
c expand i_dquot to handle user and group quotas
e
s 00001/00001/00154
d D 7.11 90/03/05 18:09:22 mckusick 52 51
c iftovt macro needs to change to support FIFO's
e
s 00010/00010/00145
d D 7.10 90/01/02 20:09:52 mckusick 51 50
c more rational order for the flags
e
s 00005/00010/00150
d D 7.9 89/12/30 22:37:28 mckusick 50 49
c i_flag becomes a u_long, i_text is unused, i_lastr => v_lastr;
c i_socket => v_socket, drop two spares to make up for spares in vnode
e
s 00005/00000/00155
d D 7.8 89/12/29 10:11:47 mckusick 49 48
c debugging, ILOCK and IUNLOCK always call ilock and iunlock
e
s 00005/00011/00150
d D 7.7 89/10/29 23:36:20 mckusick 48 47
c delete i_devlst as this is now done at the vnode level;
c other minor cleanups
e
s 00031/00098/00130
d D 7.6 89/10/24 19:36:28 mckusick 47 46
c split out that part of inode.h that is relevant only to the kernel incore info
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
D 76
 * Copyright (c) 1982, 1989 The Regents of the University of California.
 * All rights reserved.
E 76
I 76
 * Copyright (c) 1982, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
I 79
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 79
E 76
E 44
 *
I 44
D 54
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
E 54
I 54
 * %sccs.include.redist.c%
E 54
 *
E 44
 *	%W% (Berkeley) %G%
 */
E 38
E 9
E 6

I 47
D 59
#ifdef KERNEL
#include "../ufs/dinode.h"
#else
#include <ufs/dinode.h>
#endif
E 59
I 59
#include <ufs/ufs/dinode.h>
E 59

E 47
I 17
D 20
/*	inode.h	2.1	3/25/82	*/

E 20
E 17
/*
I 64
D 77
 * Theoretically, directories can be more than 2Gb in length,
 * however, in practice this seems unlikely. So, we define
 * the type doff_t as a long to keep down the cost of doing
 * lookup on a 32-bit machine. If you are porting to a 64-bit
 * architecture, you should make doff_t the same as off_t.
E 77
I 77
 * Theoretically, directories can be more than 2Gb in length, however, in
 * practice this seems unlikely. So, we define the type doff_t as a long
 * to keep down the cost of doing lookup on a 32-bit machine. If you are
 * porting to a 64-bit architecture, you should make doff_t the same as off_t.
E 77
 */
D 77
#define doff_t	long
E 77
I 77
#define	doff_t	long
E 77

/*
E 64
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
D 58
 * The I node is the focus of all file activity in UNIX.
 * There is a unique inode allocated for each active file,
 * each current directory, each mounted-on file, text file, and the root.
 * An inode is 'named' by its dev/inumber pair. (iget/iget.c)
D 17
 * Data, from mode on, is read in from permanent inode on volume.
E 17
I 17
D 47
 * Data in icommon is read in from permanent inode on volume.
E 47
I 47
 * Data in `struct dinode' is read in from permanent inode on volume.
E 58
I 58
 * The inode is used to describe each active (or recently active)
 * file in the UFS filesystem. It is composed of two types of
 * information. The first part is the information that is needed
 * only while the file is active (such as the identity of the file
 * and linkage to speed its lookup). The second part is the 
 * permannent meta-data associated with the file which is read
 * in from the permanent dinode from long term storage when the
 * file becomes active, and is put back when the file is no longer
 * being used.
E 58
E 47
E 17
E 14
 */
D 14

E 14
D 17
#define	NADDR	13
E 17
D 58

E 58
I 17
D 26
#define	NDADDR	8		/* direct addresses in inode */
#define	NIADDR	2		/* indirect addresses in inode */
E 26
I 26
D 47
#define	NDADDR	12		/* direct addresses in inode */
#define	NIADDR	3		/* indirect addresses in inode */
E 26

E 47
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
struct inode {
I 18
D 47
	struct	inode *i_chain[2];	/* must be first */
I 44
	struct	vnode i_vnode;	/* vnode associated with this inode */
E 47
I 47
D 70
	struct	inode *i_chain[2]; /* hash chain, MUST be first */
E 70
I 70
D 77
	struct	inode *i_next;	/* hash chain forward */
	struct	inode **i_prev;	/* hash chain back */
E 70
	struct	vnode *i_vnode;	/* vnode associated with this inode */
E 47
	struct	vnode *i_devvp;	/* vnode for block I/O */
E 44
E 18
E 14
D 20
	char	i_flag;
E 20
I 20
D 47
	u_short	i_flag;
E 47
I 47
D 50
	u_short	i_flag;		/* see below */
E 50
I 50
	u_long	i_flag;		/* see below */
E 50
E 47
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
I 60
D 65
	short	i_pad;
E 65
E 60
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
D 58
	ino_t	i_number;	/* i number, 1-to-1 with device address */
I 33
D 47
	long	i_id;		/* unique identifier */
I 44
	long	i_diroff;	/* offset in dir, where we found last entry */
E 47
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
E 58
I 58
	ino_t	i_number;	/* the identity of the inode */
D 59
	struct	fs *i_fs;	/* filesystem associated with this inode */
E 59
I 59
	union {			/* associated filesystem */
E 77
I 77
	struct	inode *i_next;	/* Hash chain forward. */
	struct	inode **i_prev;	/* Hash chain back. */
	struct	vnode *i_vnode;	/* Vnode associated with this inode. */
	struct	vnode *i_devvp;	/* Vnode for block I/O. */
	u_long	i_flag;		/* I* flags. */
	dev_t	i_dev;		/* Device associated with the inode. */
	ino_t	i_number;	/* The identity of the inode. */
	union {			/* Associated filesystem. */
E 77
		struct	fs *fs;		/* FFS */
		struct	lfs *lfs;	/* LFS */
	} inode_u;
#define	i_fs	inode_u.fs
#define	i_lfs	inode_u.lfs
E 59
E 58
I 19
D 53
	struct	dquot *i_dquot;	/* quota structure controlling this file */
E 53
I 53
D 55
	struct	dquot *i_dquot[MAXQUOTAS]; /* pointer to dquot strauctures */
E 55
I 55
D 77
	struct	dquot *i_dquot[MAXQUOTAS]; /* pointer to dquot structures */
I 56
D 58
	struct	lockf *i_lockf;	/* Head of byte-level lock list */
E 58
I 58
D 66
	struct	lockf *i_lockf;	/* head of byte-level lock list */
E 66
E 58
E 56
E 55
E 53
I 40
D 50
	struct	text *i_text;	/* text entry, if any (should be region) */
E 50
I 44
D 48
	struct	inode *i_devlst;/* list of block device inodes */
E 48
I 47
D 62
	long	i_diroff;	/* offset in dir, where we found last entry */
E 47
	off_t	i_endoff;	/* end of useful stuff in directory */
E 62
I 46
D 48
	long	i_spare[4];
E 48
I 48
D 50
	long	i_spare[5];
E 48
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
D 47
		struct	{
			struct inode  *if_freef;	/* free list forward */
			struct inode **if_freeb;	/* free list back */
		} i_fr;
E 47
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
E 50
I 50
D 60
	long	i_spare0;
	long	i_spare1;
E 60
I 60
D 61
	u_quad	i_modrev;	/* revision level for lease */
E 61
I 61
	u_quad_t i_modrev;	/* revision level for lease */
I 66
	struct	lockf *i_lockf;	/* head of byte-level lock list */
E 66
E 61
	pid_t	i_lockholder;	/* DEBUG: holder of inode lock */
	pid_t	i_lockwaiter;	/* DEBUG: latest blocked for inode lock */
E 77
I 77
	struct	dquot *i_dquot[MAXQUOTAS];	/* Dquot structures. */
	u_quad_t i_modrev;	/* Revision level for lease. */
	struct	lockf *i_lockf;	/* Head of byte-level lock list. */
	pid_t	i_lockholder;	/* DEBUG: holder of inode lock. */
	pid_t	i_lockwaiter;	/* DEBUG: latest blocked for inode lock. */
E 77
D 62
	long	i_spare[16];	/* spares to round up to 256 bytes */
E 62
I 62
	/*
	 * Side effects; used during directory lookup.
	 */
I 74
D 77
	long	i_count;	/* size of free slot in directory */
E 74
D 64
	off_t	i_endoff;	/* end of useful stuff in directory */
	long	i_diroff;	/* offset in dir, where we found last entry */
	long	i_offset;	/* offset of free space in directory */
E 64
I 64
	doff_t	i_endoff;	/* end of useful stuff in directory */
	doff_t	i_diroff;	/* offset in dir, where we found last entry */
	doff_t	i_offset;	/* offset of free space in directory */
E 64
D 74
	long	i_count;	/* size of free slot in directory */
E 74
	ino_t	i_ino;		/* inode number of found directory */
	u_long	i_reclen;	/* size of found directory entry */
I 75
	long	i_spare[11];	/* spares to round up to 128 bytes */
E 77
I 77
	long	i_count;	/* Size of free slot in directory. */
	doff_t	i_endoff;	/* End of useful stuff in directory. */
	doff_t	i_diroff;	/* Offset in dir, where we found last entry. */
	doff_t	i_offset;	/* Offset of free space in directory. */
	ino_t	i_ino;		/* Inode number of found directory. */
	u_long	i_reclen;	/* Size of found directory entry. */
	long	i_spare[11];	/* Spares to round up to 128 bytes. */
E 77
E 75
	/*
D 77
	 * the on-disk dinode itself.
E 77
I 77
	 * The on-disk dinode itself.
E 77
	 */
E 62
E 60
D 53
	long	i_spare2;
E 53
E 50
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
D 47
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
E 47
I 47
D 58
	struct	dinode i_din;	/* the on-disk inode */
E 58
I 58
D 75
	struct	dinode i_din;	/* the on-disk dinode */
I 62
D 74
	long	i_spare[12];	/* spares to round up to 256 bytes */
E 74
I 74
	long	i_spare[11];	/* spares to round up to 256 bytes */
E 75
I 75
D 77
	struct	dinode i_din;	/* 128 bytes of the on-disk dinode */
E 77
I 77
	struct	dinode i_din;	/* 128 bytes of the on-disk dinode. */
E 77
E 75
E 74
E 62
E 58
E 47
E 17
};

I 17
D 47
struct dinode {
	union {
		struct	icommon di_icom;
D 26
		char	di_size[64];
E 26
I 26
		char	di_size[128];
E 26
	} di_un;
};

#define	i_mode		i_ic.ic_mode
#define	i_nlink		i_ic.ic_nlink
#define	i_uid		i_ic.ic_uid
#define	i_gid		i_ic.ic_gid
E 47
I 47
D 77
#define	i_mode		i_din.di_mode
#define	i_nlink		i_din.di_nlink
#define	i_uid		i_din.di_uid
#define	i_gid		i_din.di_gid
E 47
I 27
D 54
/* ugh! -- must be fixed */
D 43
#ifdef vax
E 43
I 43
#if defined(vax) || defined(tahoe)
E 54
I 54
D 61
#if BYTE_ORDER == LITTLE_ENDIAN || defined(tahoe) /* ugh! -- must be fixed */
E 61
I 61
D 68
#ifdef _NOQUAD
#define i_size	i_din.di_qsize.val[_QUAD_LOWWORD]
#else
#define i_size	i_din.di_qsize
#endif
#if defined(tahoe) /* ugh! -- must be fixed */
#undef i_size
E 61
E 54
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
#define	i_size		i_din.di_qsize.val[0]
I 54
D 61
#else /* BYTE_ORDER == BIG_ENDIAN */
#define	i_size		i_din.di_qsize.val[1]
E 61
E 54
E 47
I 27
#endif
E 68
I 68
#define i_size		i_din.di_size
E 77
I 77
#define	i_atime		i_din.di_atime
#define	i_blocks	i_din.di_blocks
#define	i_ctime		i_din.di_ctime
E 77
E 68
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
E 47
I 47
#define	i_db		i_din.di_db
I 77
#define	i_flags		i_din.di_flags
#define	i_gen		i_din.di_gen
#define	i_gid		i_din.di_gid
E 77
#define	i_ib		i_din.di_ib
D 77
#define	i_atime		i_din.di_atime
E 77
I 77
#define	i_mode		i_din.di_mode
E 77
#define	i_mtime		i_din.di_mtime
D 77
#define	i_ctime		i_din.di_ctime
#define i_blocks	i_din.di_blocks
E 77
I 77
#define	i_nlink		i_din.di_nlink
E 77
D 69
#define	i_rdev		i_din.di_db[0]
E 69
I 69
#define	i_rdev		i_din.di_rdev
#define	i_shortlink	i_din.di_shortlink
E 69
D 77
#define i_flags		i_din.di_flags
#define i_gen		i_din.di_gen
E 77
I 77
#define	i_size		i_din.di_size
#define	i_uid		i_din.di_uid
E 77
E 47
E 44
D 50
#define	i_lastr		i_un.if_lastr
D 25
#define	i_socket	is_socket
E 25
I 25
#define	i_socket	i_un.is_socket
E 50
E 25
I 18
D 70
#define	i_forw		i_chain[0]
#define	i_back		i_chain[1]
E 70
D 47
#define	i_freef		i_un.i_fr.if_freef
#define	i_freeb		i_un.i_fr.if_freeb
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

E 47
E 17
D 48
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
D 47
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

E 47
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

E 48
D 44
ino_t	dirpref();
E 26
#endif

E 44
D 77
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
D 51
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
E 51
I 51
#define	ILOCKED		0x0001		/* inode is locked */
#define	IWANT		0x0002		/* some process waiting on lock */
#define	IRENAME		0x0004		/* inode is being renamed */
#define	IUPD		0x0010		/* file has been modified */
#define	IACC		0x0020		/* inode access time to be updated */
#define	ICHG		0x0040		/* inode has been changed */
#define	IMOD		0x0080		/* inode has been modified */
#define	ISHLOCK		0x0100		/* file has shared lock */
#define	IEXLOCK		0x0200		/* file has exclusive lock */
#define	ILWAIT		0x0400		/* someone waiting on file lock */
E 77
I 77
/* These flags are kept in i_flag. */
D 78
#define	IACCESS		0x0001		/* Access time update request. */
#define	ICHANGE		0x0002		/* Inode change time update request. */
#define	IEXLOCK		0x0004		/* File has exclusive lock. */
#define	ILOCKED		0x0008		/* Inode lock. */
#define	ILWAIT		0x0010		/* Process waiting on file lock. */
#define	IMODIFIED	0x0020		/* Inode has been modified. */
#define	IRENAME		0x0040		/* Inode is being renamed. */
#define	ISHLOCK		0x0080		/* File has shared lock. */
#define	IUPDATE		0x0100		/* Modification time update request. */
#define	IWANT		0x0200		/* Inode is wanted by a process. */
E 78
I 78
#define	IN_ACCESS	0x0001		/* Access time update request. */
#define	IN_CHANGE	0x0002		/* Inode change time update request. */
#define	IN_EXLOCK	0x0004		/* File has exclusive lock. */
#define	IN_LOCKED	0x0008		/* Inode lock. */
#define	IN_LWAIT	0x0010		/* Process waiting on file lock. */
#define	IN_MODIFIED	0x0020		/* Inode has been modified. */
#define	IN_RENAME	0x0040		/* Inode is being renamed. */
#define	IN_SHLOCK	0x0080		/* File has shared lock. */
#define	IN_UPDATE	0x0100		/* Modification time update request. */
#define	IN_WANTED	0x0200		/* Inode is wanted by a process. */
E 78
E 77
E 51
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

D 47
/* modes */
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
#define	IFMT		0170000		/* type of file */
#define	IFCHR		0020000		/* character special */
#define	IFDIR		0040000		/* directory */
#define	IFBLK		0060000		/* block special */
#define	IFREG		0100000		/* regular */
#define	IFLNK		0120000		/* symbolic link */
D 24
#define	IFPORTAL	0140000		/* portal */
E 24
I 24
#define	IFSOCK		0140000		/* socket */

E 24
#define	ISUID		04000		/* set user id on execution */
#define	ISGID		02000		/* set group id on execution */
#define	ISVTX		01000		/* save swapped text even after use */
#define	IREAD		0400		/* read, write, execute permissions */
#define	IWRITE		0200
#define	IEXEC		0100
I 21

E 47
I 44
#ifdef KERNEL
I 71
/*
 * Structure used to pass around logical block paths generated by
 * ufs_getlbns and used by truncate and bmap code.
 */
struct indir {
D 72
	long	in_lbn;			/* logical block number */
E 72
I 72
D 77
	daddr_t	in_lbn;			/* logical block number */
E 72
	int	in_off;			/* offset in buffer */
I 72
	int	in_exists;		/* does this block exist yet */
E 77
I 77
	daddr_t	in_lbn;			/* Logical block number. */
	int	in_off;			/* Offset in buffer. */
	int	in_exists;		/* Flag if the block exists. */
E 77
E 72
};

E 71
D 59
/*
 * Convert between inode pointers and vnode pointers
 */
E 59
I 59
/* Convert between inode pointers and vnode pointers. */
E 59
#define VTOI(vp)	((struct inode *)(vp)->v_data)
D 45
#define ITOV(ip)	((struct vnode *)&(ip)->i_vnode)
E 45
I 45
D 47
#define ITOV(ip)	(&(ip)->i_vnode)
E 47
I 47
#define ITOV(ip)	((ip)->i_vnode)
E 47
E 45

D 59
/*
 * Convert between vnode types and inode formats
 */
E 59
I 59
D 63
/* Convert between vnode types and inode formats. */
E 59
extern enum vtype	iftovt_tab[];
extern int		vttoif_tab[];
D 52
#define IFTOVT(mode)	(iftovt_tab[((mode) & IFMT) >> 13])
E 52
I 52
#define IFTOVT(mode)	(iftovt_tab[((mode) & IFMT) >> 12])
E 52
#define VTTOIF(indx)	(vttoif_tab[(int)(indx)])

#define MAKEIMODE(indx, mode)	(int)(VTTOIF(indx) | (mode))
I 48

E 63
D 59
u_long	nextgennumber;		/* next generation number to assign */

extern ino_t	dirpref();
E 48

/*
 * Lock and unlock inodes.
 */
E 59
I 59
D 73
/* Lock and unlock inodes. */
E 59
I 49
#ifdef notdef
E 49
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
I 49
#else
D 59
#define ILOCK(ip)	ilock(ip)
#define IUNLOCK(ip)	iunlock(ip)
E 59
I 59
#define ILOCK(ip)	ufs_ilock(ip)
#define IUNLOCK(ip)	ufs_iunlock(ip)
E 59
#endif
E 49

E 73
D 59
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

E 59
D 77
#define	ITIMES(ip, t1, t2) { \
	if ((ip)->i_flag&(IUPD|IACC|ICHG)) { \
		(ip)->i_flag |= IMOD; \
		if ((ip)->i_flag&IACC) \
D 65
			(ip)->i_atime = (t1)->tv_sec; \
E 65
I 65
D 67
			(ip)->i_atime.tv_sec = (t1)->tv_sec; \
E 67
I 67
			(ip)->i_atime.ts_sec = (t1)->tv_sec; \
E 67
E 65
D 61
		if ((ip)->i_flag&IUPD) \
E 61
I 61
		if ((ip)->i_flag&IUPD) { \
E 61
D 65
			(ip)->i_mtime = (t2)->tv_sec; \
E 65
I 65
D 67
			(ip)->i_mtime.tv_sec = (t2)->tv_sec; \
E 67
I 67
			(ip)->i_mtime.ts_sec = (t2)->tv_sec; \
E 67
E 65
I 61
D 68
			INCRQUAD((ip)->i_modrev); \
E 68
I 68
			(ip)->i_modrev++; \
E 68
		} \
E 61
		if ((ip)->i_flag&ICHG) \
D 65
			(ip)->i_ctime = time.tv_sec; \
E 65
I 65
D 67
			(ip)->i_ctime.tv_sec = time.tv_sec; \
E 67
I 67
			(ip)->i_ctime.ts_sec = time.tv_sec; \
E 67
E 65
		(ip)->i_flag &= ~(IACC|IUPD|ICHG); \
	} \
E 77
I 77
#define	ITIMES(ip, t1, t2) {						\
D 78
	if ((ip)->i_flag & (IUPDATE | IACCESS | ICHANGE)) {		\
		(ip)->i_flag |= IMODIFIED;				\
		if ((ip)->i_flag & IACCESS)				\
E 78
I 78
	if ((ip)->i_flag & (IN_ACCESS | IN_CHANGE | IN_UPDATE)) {	\
		(ip)->i_flag |= IN_MODIFIED;				\
		if ((ip)->i_flag & IN_ACCESS)				\
E 78
			(ip)->i_atime.ts_sec = (t1)->tv_sec;		\
D 78
		if ((ip)->i_flag & IUPDATE) {				\
E 78
I 78
		if ((ip)->i_flag & IN_UPDATE) {				\
E 78
			(ip)->i_mtime.ts_sec = (t2)->tv_sec;		\
			(ip)->i_modrev++;				\
		}							\
D 78
		if ((ip)->i_flag & ICHANGE)				\
E 78
I 78
		if ((ip)->i_flag & IN_CHANGE)				\
E 78
			(ip)->i_ctime.ts_sec = time.tv_sec;		\
D 78
		(ip)->i_flag &= ~(IACCESS | IUPDATE | ICHANGE);		\
E 78
I 78
		(ip)->i_flag &= ~(IN_ACCESS | IN_CHANGE | IN_UPDATE);	\
E 78
	}								\
E 77
}
I 44

D 59
/*
 * This overlays the fid sturcture (see mount.h)
 */
E 59
I 59
/* This overlays the fid structure (see mount.h). */
E 59
struct ufid {
D 47
	u_short	ufid_len;
	ino_t	ufid_ino;
	long	ufid_gen;
E 47
I 47
D 77
	u_short	ufid_len;	/* length of structure */
	u_short	ufid_pad;	/* force long alignment */
	ino_t	ufid_ino;	/* file number (ino) */
	long	ufid_gen;	/* generation number */
E 77
I 77
	u_short	ufid_len;	/* Length of structure. */
	u_short	ufid_pad;	/* Force long alignment. */
	ino_t	ufid_ino;	/* File number (ino). */
	long	ufid_gen;	/* Generation number. */
E 77
E 47
};
D 57
#endif
E 57
I 57
D 59

/*
 * Prototypes for UFS vnode operations
 */
D 58
int	ufs_lookup __P((
		struct vnode *vp,
		struct nameidata *ndp,
		struct proc *p));
int	ufs_create __P((
		struct nameidata *ndp,
		struct vattr *vap,
		struct proc *p));
int	ufs_mknod __P((
		struct nameidata *ndp,
		struct vattr *vap,
		struct ucred *cred,
		struct proc *p));
int	ufs_open __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	ufs_close __P((
		struct vnode *vp,
		int fflag,
		struct ucred *cred,
		struct proc *p));
int	ufs_access __P((
		struct vnode *vp,
		int mode,
		struct ucred *cred,
		struct proc *p));
int	ufs_getattr __P((
		struct vnode *vp,
		struct vattr *vap,
		struct ucred *cred,
		struct proc *p));
int	ufs_setattr __P((
		struct vnode *vp,
		struct vattr *vap,
		struct ucred *cred,
		struct proc *p));
int	ufs_read __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	ufs_write __P((
		struct vnode *vp,
		struct uio *uio,
		int ioflag,
		struct ucred *cred));
int	ufs_ioctl __P((
		struct vnode *vp,
		int command,
		caddr_t data,
		int fflag,
		struct ucred *cred,
		struct proc *p));
int	ufs_select __P((
		struct vnode *vp,
		int which,
		int fflags,
		struct ucred *cred,
		struct proc *p));
int	ufs_mmap __P((
		struct vnode *vp,
		int fflags,
		struct ucred *cred,
		struct proc *p));
int	ufs_fsync __P((
		struct vnode *vp,
		int fflags,
		struct ucred *cred,
		int waitfor,
		struct proc *p));
int	ufs_seek __P((
		struct vnode *vp,
		off_t oldoff,
		off_t newoff,
		struct ucred *cred));
int	ufs_remove __P((
		struct nameidata *ndp,
		struct proc *p));
int	ufs_link __P((
		struct vnode *vp,
		struct nameidata *ndp,
		struct proc *p));
int	ufs_rename __P((
		struct nameidata *fndp,
		struct nameidata *tdnp,
		struct proc *p));
int	ufs_mkdir __P((
		struct nameidata *ndp,
		struct vattr *vap,
		struct proc *p));
int	ufs_rmdir __P((
		struct nameidata *ndp,
		struct proc *p));
int	ufs_symlink __P((
		struct nameidata *ndp,
		struct vattr *vap,
		char *target,
		struct proc *p));
int	ufs_readdir __P((
		struct vnode *vp,
		struct uio *uio,
		struct ucred *cred,
		int *eofflagp));
int	ufs_readlink __P((
		struct vnode *vp,
		struct uio *uio,
		struct ucred *cred));
int	ufs_abortop __P((
		struct nameidata *ndp));
int	ufs_inactive __P((
		struct vnode *vp,
		struct proc *p));
int	ufs_reclaim __P((
		struct vnode *vp));
int	ufs_lock __P((
		struct vnode *vp));
int	ufs_unlock __P((
		struct vnode *vp));
int	ufs_bmap __P((
		struct vnode *vp,
		daddr_t bn,
		struct vnode **vpp,
		daddr_t *bnp));
int	ufs_strategy __P((
		struct buf *bp));
int	ufs_print __P((
		struct vnode *vp));
int	ufs_islocked __P((
		struct vnode *vp));
int	ufs_advlock __P((
		struct vnode *vp,
		caddr_t id,
		int op,
		struct flock *fl,
		int flags));
E 58
I 58
int ufs_lookup __P((struct vnode *vp, struct nameidata *ndp, struct proc *p));
int ufs_create __P((struct nameidata *ndp, struct vattr *vap, struct proc *p));
int ufs_mknod __P((struct nameidata *ndp, struct vattr *vap, struct ucred *cred,
	struct proc *p));
int ufs_open __P((struct vnode *vp, int mode, struct ucred *cred,
	struct proc *p));
int ufs_close __P((struct vnode *vp, int fflag, struct ucred *cred,
	struct proc *p));
int ufs_access __P((struct vnode *vp, int mode, struct ucred *cred,
	struct proc *p));
int ufs_getattr __P((struct vnode *vp, struct vattr *vap, struct ucred *cred,
	struct proc *p));
int ufs_setattr __P((struct vnode *vp, struct vattr *vap, struct ucred *cred,
	struct proc *p));
int ufs_read __P((struct vnode *vp, struct uio *uio, int ioflag,
	struct ucred *cred));
int ufs_write __P((struct vnode *vp, struct uio *uio, int ioflag,
	struct ucred *cred));
int ufs_ioctl __P((struct vnode *vp, int command, caddr_t data, int fflag,
	struct ucred *cred, struct proc *p));
int ufs_select __P((struct vnode *vp, int which, int fflags, struct ucred *cred,
	struct proc *p));
int ufs_mmap __P((struct vnode *vp, int fflags, struct ucred *cred,
	struct proc *p));
int ufs_fsync __P((struct vnode *vp, int fflags, struct ucred *cred,
	int waitfor, struct proc *p));
int ufs_seek __P((struct vnode *vp, off_t oldoff, off_t newoff,
	struct ucred *cred));
int ufs_remove __P((struct nameidata *ndp, struct proc *p));
int ufs_link __P((struct vnode *vp, struct nameidata *ndp, struct proc *p));
int ufs_rename __P((struct nameidata *fndp, struct nameidata *tdnp,
	struct proc *p));
int ufs_mkdir __P((struct nameidata *ndp, struct vattr *vap, struct proc *p));
int ufs_rmdir __P((struct nameidata *ndp, struct proc *p));
int ufs_symlink __P((struct nameidata *ndp, struct vattr *vap, char *target,
	struct proc *p));
int ufs_readdir __P((struct vnode *vp, struct uio *uio, struct ucred *cred,
	int *eofflagp));
int ufs_readlink __P((struct vnode *vp, struct uio *uio, struct ucred *cred));
int ufs_abortop __P((struct nameidata *ndp));
int ufs_inactive __P((struct vnode *vp, struct proc *p));
int ufs_reclaim __P((struct vnode *vp));
int ufs_lock __P((struct vnode *vp));
int ufs_unlock __P((struct vnode *vp));
int ufs_bmap __P((struct vnode *vp, daddr_t bn, struct vnode **vpp,
	daddr_t *bnp));
int ufs_strategy __P((struct buf *bp));
int ufs_print __P((struct vnode *vp));
int ufs_islocked __P((struct vnode *vp));
int ufs_advlock __P((struct vnode *vp, caddr_t id, int op, struct flock *fl,
	int flags));
E 59
E 58
#endif /* KERNEL */
E 57
E 44
D 33

E 33
E 32
E 21
E 17
E 1
