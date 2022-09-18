h58827
s 00019/00027/00100
d D 8.9 95/05/14 00:20:43 mckusick 136 135
c replace locking with lock manager calls
e
s 00000/00015/00127
d D 8.8 95/03/30 14:18:50 mckusick 135 134
c ufs_init moves to ufs_vfsops.c
e
s 00003/00008/00139
d D 8.7 94/07/22 15:01:52 mckusick 134 133
c get rid of complaint about inode size
e
s 00004/00021/00143
d D 8.6 94/06/16 17:06:08 mckusick 133 132
c break out reclaim operations (from mycroft)
e
s 00002/00000/00162
d D 8.5 94/06/15 16:26:41 mkm 132 131
c dqinit needs to be ifdef QUOTA
e
s 00005/00000/00157
d D 8.4 94/01/21 17:30:53 bostic 131 130
c add USL's copyright notice
e
s 00005/00006/00152
d D 8.3 93/09/23 16:03:57 bostic 130 129
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00156
d D 8.2 93/09/21 07:21:50 bostic 129 128
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00156
d D 8.1 93/06/11 16:28:56 bostic 128 127
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00154
d D 7.52 92/12/09 19:27:19 mckusick 127 126
c collect lock holder when locking inodes
e
s 00000/00062/00154
d D 7.51 92/11/14 23:20:40 mckusick 126 125
c ufs_iput, ufs_ilock, and ufs_iunlock are gone, replaced with vput,
c ufs_lock, and ufs_unlock respectively
e
s 00058/00000/00158
d D 7.50 92/11/13 16:47:37 mckusick 125 124
c ufs_inactive is back
e
s 00001/00001/00157
d D 7.49 92/07/20 00:31:30 mckusick 124 123
c remque => ufs_ihashrem
e
s 00004/00002/00154
d D 7.48 92/07/03 01:42:42 mckusick 123 122
c add parameter declaration
e
s 00009/00008/00147
d D 7.47 92/06/04 09:49:35 heideman 122 121
c registerized vnodeop ops after vnode interface conversion
e
s 00008/00010/00147
d D 7.46 92/05/15 13:53:34 heideman 121 120
c vnodeop argument macro expansion
e
s 00004/00002/00153
d D 7.45 92/05/14 17:27:07 heideman 120 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 17:02:29 heideman 119 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 16:43:55 heideman 118 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 16:33:51 heideman 117 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 15:52:25 heideman 116 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 15:40:04 heideman 115 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 14:46:07 heideman 114 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 12:48:59 heideman 113 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 11:46:06 heideman 112 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/14 10:26:49 heideman 111 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/13 23:04:57 heideman 110 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/13 18:52:29 heideman 109 107
c vnode interface conversion
e
s 00004/00002/00153
d R 7.45 92/05/13 18:24:34 heideman 108 107
c vnode interface conversion
e
s 00014/00004/00141
d D 7.44 91/12/19 21:46:13 mckusick 107 106
c avoid null proc pointers (as when panicking)
e
s 00024/00011/00121
d D 7.43 91/12/16 17:43:13 mckusick 106 105
c free UFS private data area
e
s 00001/00053/00131
d D 7.42 91/11/05 14:34:45 mckusick 105 104
c reorganization to move ufsmount ops to be vnode ops;
c inactive becomes filesystem specific
e
s 00048/00535/00136
d D 7.41 91/11/01 18:05:18 bostic 104 102
c moved hashing into ufs_ihash.c; deleted FFS specific routines: iget,
c iupdat, itrunc and indirtrunc
e
s 00002/00000/00671
d D 7.40.1.1 91/06/03 20:41:30 mckusick 103 102
c check ufs lock count on exit from syscalls
e
s 00012/00012/00659
d D 7.40 91/05/08 19:40:06 mckusick 102 101
c more precise comments
e
s 00002/00001/00669
d D 7.39 91/04/16 00:12:08 mckusick 101 100
c add proc pointers to appropriate vnode operations
e
s 00008/00011/00662
d D 7.38 91/03/19 10:30:27 karels 100 99
c first cut for new proc & user structs (still need to put in new vnode calling
c convention): get credentials, etc, via proc; u.u_nd, u.u_spare are gone;
c purge user.h; remove ../ufs/ from includes; consolidate *nullops();
c chown/fchmod use proc's credentials, not file's
e
s 00001/00000/00672
d D 7.37 91/02/01 16:29:32 mckusick 99 98
c add POSIX-style byte-level record locking
e
s 00002/00004/00670
d D 7.36 90/12/05 16:09:29 mckusick 98 97
c update for new VM
e
s 00001/00001/00673
d D 7.35 90/08/24 09:39:36 mckusick 97 96
c brealloc => allocbuf
e
s 00001/00000/00673
d D 7.34 90/07/03 00:51:43 trent 96 95
c reincarnated clear of i_rdev when freeing an inode, otherwise it 
c appears inode has zero size but one disk block. (bostic+trent)
e
s 00001/00011/00672
d D 7.33 90/06/28 22:30:34 bostic 95 94
c new copyright notice
e
s 00003/00003/00680
d D 7.32 90/05/04 20:51:20 mckusick 94 93
c mount struct prefixes go from m_ to mnt_ and M_ to MNT_
e
s 00008/00000/00675
d D 7.31 90/05/03 14:41:08 mckusick 93 92
c have to take off the hash list when bread of inode fails
e
s 00026/00062/00649
d D 7.30 90/05/02 19:41:39 mckusick 92 91
c iaccess moves into ufs_access; changes for the new quota implementation
e
s 00010/00000/00701
d D 7.29 90/03/05 18:10:31 mckusick 91 90
c reassign vnode ops for FIFO's
e
s 00005/00010/00696
d D 7.28 90/02/08 13:23:05 mckusick 90 89
c optimization from Noemi Paciorek <noemi@osf.org>
e
s 00001/00002/00705
d D 7.27 90/01/04 22:17:31 mckusick 89 88
c initialize i_diroff; proper association of indirect blocks
e
s 00003/00005/00704
d D 7.26 89/12/30 22:42:12 mckusick 88 87
c i_lastr => v_lastr; v_count => v_usecount
e
s 00009/00000/00700
d D 7.25 89/12/29 10:01:59 mckusick 87 86
c debugging, put in accounting for process id holding and waiting for lock
e
s 00001/00001/00699
d D 7.24 89/12/19 16:25:31 mckusick 86 85
c have to update the correct inode (from mike@cs.utah.edu)
e
s 00035/00026/00665
d D 7.23 89/11/30 23:02:36 mckusick 85 84
c overhaul itrunc; cleanups to inactive; use vprintf
e
s 00001/00002/00690
d D 7.22 89/11/25 15:24:08 mckusick 84 83
c checkalias now sets rdev
e
s 00001/00001/00691
d D 7.21 89/11/22 21:51:24 mckusick 83 82
c syncip takes a waitfor flag
e
s 00004/00002/00688
d D 7.20 89/11/21 22:56:49 mckusick 82 81
c suppress printing of pushes of active inodes
e
s 00001/00002/00689
d D 7.19 89/11/12 10:27:51 mckusick 81 80
c initialize i_flag not i_flags
e
s 00000/00048/00691
d D 7.18 89/11/10 12:26:31 mckusick 80 79
c iflush becomes vflush and moves to vfs_subr.c
e
s 00003/00001/00736
d D 7.17 89/11/03 15:07:48 mckusick 79 77
c lint
e
s 00001/00001/00736
d R 7.17 89/11/03 09:59:42 mckusick 78 77
c lint
e
s 00076/00234/00661
d D 7.16 89/10/29 23:44:35 mckusick 77 76
c device uniqueness and aliasing is now handled at the vnode level;
c bdevvp moves to vfs_subr.c, igrab is replaced by vget
e
s 00146/00205/00749
d D 7.15 89/10/24 19:47:28 mckusick 76 75
c merge inode and nfsnode tables into a single vnode table;
c link together all vnodes associated with a particular mount point
e
s 00002/00002/00952
d D 7.14 89/10/21 15:16:34 mckusick 75 74
c minor cleanups
e
s 00034/00024/00920
d D 7.13 89/10/21 15:13:51 mckusick 74 73
c try to flush all inodes when unmounting; 
c add debugging info to find out what is busy
e
s 00005/00004/00939
d D 7.12 89/08/26 14:12:52 mckusick 73 72
c generalize the buffer pool so that NFS can become a client
e
s 00005/00003/00938
d D 7.11 89/08/10 17:08:30 mckusick 72 71
c purge vnode type when unneeded and returned to the free list so that
c getnewino does not try to delete it from block device list more than once.
e
s 00006/00000/00935
d D 7.10 89/07/16 15:06:29 mckusick 71 70
c detect release of free inodes (from stale file handles) 
c and just put them on the free list
e
s 00003/00003/00932
d D 7.9 89/06/27 19:17:57 mckusick 70 69
c update reference counts on vnodes using VREF
e
s 00011/00000/00924
d D 7.8 89/06/07 16:53:02 mckusick 69 68
c compatibility code to assign a generation number to inodes that have none
e
s 00007/00004/00917
d D 7.7 89/06/06 16:50:00 mckusick 68 67
c put in explicit lock and unlock so that locking can be checked
e
s 00440/00209/00481
d D 7.6 89/05/09 17:22:14 mckusick 67 66
c merge in vnodes
e
s 00008/00008/00682
d D 7.5 87/06/21 15:46:00 mckusick 66 65
c geteblk => malloc for copy of indirect pointers
e
s 00001/00001/00689
d D 7.4 87/06/21 15:30:44 mckusick 65 64
c geteblk => malloc, so m_bufp => m_fs as it should be
e
s 00004/00004/00686
d D 7.3 87/06/05 00:05:35 mckusick 64 63
c change free() to blkfree() to allow for malloc()/free()
e
s 00014/00029/00676
d D 7.2 87/04/02 15:49:19 karels 63 61
c working with pack labels
e
s 00033/00029/00676
d D 7.1.1.1 87/04/02 15:41:14 karels 62 61
c add ifdefs for dev_bsize (almost working)
e
s 00001/00001/00704
d D 7.1 86/06/05 00:12:57 mckusick 61 60
c 4.3BSD release version
e
s 00003/00003/00702
d D 6.19 86/02/23 23:11:12 karels 60 59
c lint
e
s 00003/00004/00702
d D 6.18 86/02/20 15:19:56 karels 59 58
c lint and cleanups from Sam
e
s 00006/00005/00700
d D 6.17 85/09/04 13:32:23 bloom 58 57
c lint cleanup
e
s 00007/00001/00698
d D 6.16 85/06/08 14:51:52 mckusick 57 56
c Add copyright
e
s 00002/00002/00697
d D 6.15 85/03/20 11:14:34 mckusick 56 55
c don't try to truncate inodes on read-only file systems (from sun!shannon)
e
s 00000/00001/00699
d D 6.14 85/03/19 20:49:17 mckusick 55 54
c eliminate extraneous include of conf.h
e
s 00001/00001/00699
d D 6.13 85/03/13 20:15:03 mckusick 54 53
c don't try to truncate inodes on read-only file systems (from sun!shannon)
e
s 00047/00010/00653
d D 6.12 85/02/11 17:11:09 mckusick 53 52
c must zero out unused portion of partial blocks when truncating files
e
s 00011/00011/00652
d D 6.11 84/08/29 20:26:02 bloom 52 51
c Change to includes.  no more ../h
e
s 00001/00001/00662
d D 6.10 84/08/03 20:34:27 mckusick 51 50
c increase size of hash table header to reduce collisions
e
s 00001/00009/00662
d D 6.9 84/07/20 01:13:07 mckusick 50 49
c use new `cacheinval' macro
e
s 00005/00003/00666
d D 6.8 84/07/15 11:54:57 karels 49 48
c iget must lock old inode before dqrele()
e
s 00002/00002/00667
d D 6.7 84/07/04 13:22:34 mckusick 48 47
c save time, use ILOCK and IUNLOCK to avoid call overhead
e
s 00006/00003/00663
d D 6.6 84/07/02 15:22:43 mckusick 47 46
c eliminate unnecessary panic when id's wrap
e
s 00044/00000/00622
d D 6.5 84/06/27 20:40:14 sam 46 45
c convert namei cache to hold soft references to inodes so that 
c . and .. may be placed in the cache
e
s 00001/00003/00621
d D 6.4 84/05/22 11:18:26 karels 45 44
c remove paranoid test; make hashsize a power of two (avoid unsigned
c modulo)
e
s 00004/00008/00620
d D 6.3 84/02/15 21:13:49 karels 44 43
c use ITIME in irele to update times in irele without write to disk
e
s 00005/00000/00623
d D 6.2 84/02/07 17:36:54 karels 43 42
c force iupdate from irele if count still > 0,
c avoiding delayed updates from namei cache
e
s 00000/00000/00623
d D 6.1 83/07/29 06:42:24 sam 42 41
c 4.2 distribution
e
s 00004/00001/00619
d D 4.36 83/06/11 00:49:10 sam 41 40
c update inode time stamps when no work so touch works
e
s 00014/00041/00606
d D 4.35 83/05/21 15:45:12 sam 40 39
c indirtrunc always returns blocks released for use with i_blocks; 
c macro-ized to eliminate DEV_BSHIFT
e
s 00002/00000/00645
d D 4.34 83/03/15 09:50:21 sam 39 38
c botched non-QUOTA code (from kre)
e
s 00001/00001/00644
d D 4.33 83/02/10 16:05:57 sam 38 37
c guard against negative mod parameters
e
s 00131/00140/00514
d D 4.32 83/02/05 17:14:17 sam 37 36
c rewrite itrunc and indirtrunc to work (and handle triple indirect 
c blocks as well)
e
s 00183/00076/00471
d D 4.31 82/11/13 22:52:57 sam 36 35
c merge of 4.1b and 4.1c
e
s 00004/00002/00543
d D 4.30 82/10/23 10:26:56 root 35 34
c missing declaration of size
e
s 00002/00005/00543
d D 4.29 82/10/19 10:32:18 root 34 33
c more lint
e
s 00007/00007/00541
d D 4.28 82/10/17 21:51:22 root 33 32
c more lint
e
s 00004/00003/00544
d D 4.27 82/10/17 20:55:12 root 32 31
c lint
e
s 00003/00004/00544
d D 4.26 82/10/17 14:06:34 root 31 30
c fix lint
e
s 00007/00022/00541
d D 4.25 82/10/10 16:02:38 root 30 29
c move vax header files to their own directory
e
s 00004/00003/00559
d D 4.24 82/09/06 22:57:37 root 29 28
c 
e
s 00010/00007/00552
d D 4.23 82/08/10 17:52:17 sam 28 27
c new fs system calls prior to truncate and rename
e
s 00018/00018/00541
d D 4.22 82/08/03 14:02:38 sam 27 26
c cosmetics
e
s 00007/00017/00552
d D 4.21 82/07/30 10:58:39 sam 26 25
c rewrite of nami + reorganization of wdir
e
s 00005/00156/00564
d D 4.20 82/07/25 23:14:46 root 25 24
c pull maknode and wdir to ufs_nami.c
e
s 00026/00004/00694
d D 4.19 82/07/24 18:12:11 root 24 23
c merge with calder
e
s 00079/00006/00619
d D 4.18 82/07/22 18:46:19 kre 23 22
c disc quotas
e
s 00001/00000/00624
d D 4.17 82/07/03 16:56:57 kre 22 21
c complete fix of 4.15 (clear i_rdev in real inode before
c second iupdate - otherwise all the good work is undone)
c 4.15 is probably not really needed (does no real good).
e
s 00002/00000/00622
d D 4.16 82/07/01 21:07:30 kre 21 20
c replace 2 lines accidentally dropped in 4.13
e
s 00007/00003/00615
d D 4.15 82/07/01 01:17:55 root 20 19
c clear dino on disk in itrunc in all cases
e
s 00007/00028/00611
d D 4.14 82/06/30 06:25:24 kre 19 18
c remove insque/remque asm's in favour of macros
c (it doesn't work without this, register numbers are wrong)
e
s 00186/00044/00453
d D 4.13 82/06/29 23:03:03 kre 18 17
c inode LRU cache added (from Chris Maltby, Sydney Uni)
e
s 00000/00004/00497
d D 4.12 82/06/10 12:40:54 mckusick 17 16
c change iput() to irele() when releasing unlocked inodes
e
s 00017/00006/00484
d D 4.11 82/06/07 23:52:27 mckusick 16 15
c irele() becomes iunlock(); new irele() does iput() for already unlocked inodes
c fixes race condition in adding entries to directories.
e
s 00165/00118/00325
d D 4.10 82/04/19 19:35:35 mckusic 15 14
c merge into new file system
e
s 00001/00001/00442
d D 4.9 82/02/27 14:54:28 wnj 14 13
c symbolic links
e
s 00001/00001/00442
d D 4.8 82/02/15 13:28:23 wnj 13 12
c new multiple-group stuff
e
s 00047/00053/00396
d D 4.7 81/11/08 16:49:04 wnj 12 11
c plock/prele -> ilock/irele
e
s 00001/00002/00448
d D 4.6 81/10/11 13:02:12 wnj 11 10
c first bootable version
e
s 00038/00000/00412
d D 4.5 81/04/28 02:53:14 root 10 9
c plock/prele here now
e
s 00001/00001/00411
d D 4.4 81/03/09 01:47:05 wnj 9 8
c lint and a few minor fixed
e
s 00001/00003/00411
d D 4.3 81/03/06 11:37:13 wnj 8 7
c use tablefull()
e
s 00004/00003/00410
d D 4.2 81/02/26 23:29:19 wnj 7 6
c rid of NINODE
e
s 00000/00000/00413
d D 4.1 80/11/09 17:31:58 bill 6 5
c minor fixups to restart stuff; version 4.1 for distrib
e
s 00037/00004/00376
d D 3.5 80/10/03 10:45:14 bill 5 4
c file system update orderings
e
s 00000/00000/00380
d D 3.4 80/07/08 00:39:06 bill 4 3
c trivial
e
s 00001/00001/00379
d D 3.3 80/06/07 02:45:57 bill 3 2
c %H%->%G%
e
s 00001/00001/00379
d D 3.2 80/04/13 12:37:04 bill 2 1
c IUPDAT
e
s 00380/00000/00000
d D 3.1 80/04/09 16:03:20 bill 1 0
c date and time created 80/04/09 16:03:20 by bill
e
u
U
f b 
t
T
I 1
D 3
/*	%M%	%I%	%H%	*/
E 3
I 3
D 9
/*	%M%	%I%	%G%	*/
E 9
I 9
D 57
/*	%M%	%I%	%E%	*/
E 57
I 57
/*
D 61
 * Copyright (c) 1982 Regents of the University of California.
E 61
I 61
D 67
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 61
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 67
I 67
D 104
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
E 104
I 104
D 128
 * Copyright (c) 1991 Regents of the University of California.
E 104
 * All rights reserved.
E 128
I 128
D 136
 * Copyright (c) 1991, 1993
E 136
I 136
 * Copyright (c) 1991, 1993, 1995
E 136
 *	The Regents of the University of California.  All rights reserved.
I 131
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
E 131
E 128
E 67
 *
I 67
D 95
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
E 95
I 95
 * %sccs.include.redist.c%
E 95
 *
E 67
 *	%W% (Berkeley) %G%
 */
E 57
E 9
E 3

I 15
D 17
/* merged into kernel:	@(#)iget.c 2.2 4/8/82 */

E 17
E 15
D 52
#include "../h/param.h"
#include "../h/systm.h"
#include "../h/mount.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/inode.h"
D 15
#include "../h/ino.h"
#include "../h/filsys.h"
E 15
I 15
#include "../h/fs.h"
E 15
#include "../h/conf.h"
#include "../h/buf.h"
E 52
I 52
D 104
#include "param.h"
#include "systm.h"
#include "mount.h"
D 67
#include "dir.h"
E 67
D 100
#include "user.h"
E 100
I 87
#include "proc.h"
E 87
D 67
#include "inode.h"
#include "fs.h"
E 67
I 67
#include "file.h"
E 67
D 55
#include "conf.h"
E 55
#include "buf.h"
I 58
D 100
#include "cmap.h"
E 100
I 67
#include "vnode.h"
I 92
D 100
#include "../ufs/quota.h"
E 92
#include "../ufs/inode.h"
#include "../ufs/fs.h"
#include "../ufs/ufsmount.h"
E 100
E 67
E 58
E 52
D 30
#include "../h/inline.h"
E 30
I 24
D 27
#ifdef	QUOTA
E 27
I 27
D 92
#ifdef QUOTA
E 27
D 52
#include "../h/quota.h"
E 52
I 52
D 67
#include "quota.h"
E 67
I 67
#include "../ufs/quota.h"
E 67
E 52
#endif
E 92
I 29
D 52
#include "../h/kernel.h"
E 52
I 52
#include "kernel.h"
I 66
#include "malloc.h"
E 104
I 104
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/mount.h>
#include <sys/kernel.h>
I 106
#include <sys/malloc.h>
E 106
E 104
E 66
E 52
E 29
E 24

I 100
D 104
#include "quota.h"
#include "inode.h"
#include "fs.h"
#include "ufsmount.h"
E 104
I 104
#include <ufs/ufs/quota.h>
#include <ufs/ufs/inode.h>
#include <ufs/ufs/ufsmount.h>
#include <ufs/ufs/ufs_extern.h>
E 104

E 100
D 45
#define	INOHSZ	63
E 45
I 45
D 51
#define	INOHSZ	64
E 51
I 51
D 104
#define	INOHSZ	512
E 51
E 45
I 18
#if	((INOHSZ&(INOHSZ-1)) == 0)
#define	INOHASH(dev,ino)	(((dev)+(ino))&(INOHSZ-1))
#else
E 18
D 38
#define	INOHASH(dev,ino)	(((dev)+(ino))%INOHSZ)
E 38
I 38
#define	INOHASH(dev,ino)	(((unsigned)((dev)+(ino)))%INOHSZ)
E 38
D 18
short	inohash[INOHSZ];
short	ifreel;
E 18
I 18
#endif
E 104
I 104
u_long	nextgennumber;		/* Next generation number to assign. */
D 105
int	prtactive;		/* 1 => print out reclaim of active vnodes */
E 105
I 105
int	prtactive = 0;		/* 1 => print out reclaim of active vnodes */
E 105
E 104
E 18

I 67
D 76
#define INSFREE(ip) {\
	if (ifreeh) { \
		*ifreet = (ip); \
		(ip)->i_freeb = ifreet; \
	} else { \
		ifreeh = (ip); \
		(ip)->i_freeb = &ifreeh; \
	} \
	(ip)->i_freef = NULL; \
	ifreet = &(ip)->i_freef; \
}

E 67
I 18
union ihead {				/* inode LRU cache, Chris Maltby */
E 76
I 76
D 104
union ihead {
E 76
	union  ihead *ih_head[2];
	struct inode *ih_chain[2];
} ihead[INOHSZ];

I 82
int prtactive;	/* 1 => print out reclaim of active vnodes */

E 82
D 67
struct inode *ifreeh, **ifreet;
E 67
I 67
D 76
struct inode *ifreeh, **ifreet, *bdevlisth;
E 76
I 76
D 77
struct inode *bdevlisth;
E 76
E 67

E 77
E 18
/*
D 76
 * Initialize hash links for inodes
 * and build inode free list.
E 76
I 76
 * Initialize hash links for inodes.
E 76
 */
E 104
I 104
D 135
int
E 104
D 77
ihinit()
E 77
I 77
ufs_init()
E 77
{
D 104
	register int i;
I 7
D 76
	register struct inode *ip = inode;
I 18
	register union  ihead *ih = ihead;
E 76
I 76
	register union ihead *ih = ihead;
E 104
I 104
D 134
	static int first = 1;
E 134
I 134
	static int done;
E 134
E 104
E 76
E 18
E 7

I 79
D 104
#ifndef lint
E 79
I 76
	if (VN_MAXPRIVATE < sizeof(struct inode))
		panic("ihinit: too small");
I 79
#endif /* not lint */
E 79
E 76
D 18
	ifreel = 0;
D 7
	for (i = 0; i < NINODE - 1; i++)
		inode[i].i_hlink = i+1;
	inode[NINODE - 1].i_hlink = -1;
E 7
I 7
	for (i = 0; i < ninode-1; i++, ip++)
		ip->i_hlink = i+1;
	ip->i_hlink = -1;
E 7
	for (i = 0; i < INOHSZ; i++)
		inohash[i] = -1;
E 18
I 18
	for (i = INOHSZ; --i >= 0; ih++) {
		ih->ih_head[0] = ih;
		ih->ih_head[1] = ih;
	}
I 92
#ifdef QUOTA
	dqinit();
#endif /* QUOTA */
E 92
D 76
	ifreeh = ip;
	ifreet = &ip->i_freef;
	ip->i_freeb = &ifreeh;
	ip->i_forw = ip;
	ip->i_back = ip;
I 67
	ITOV(ip)->v_data = (qaddr_t)ip;
E 67
	for (i = ninode; --i > 0; ) {
		++ip;
		ip->i_forw = ip;
		ip->i_back = ip;
I 67
		ITOV(ip)->v_data = (qaddr_t)ip;
E 67
		*ifreet = ip;
		ip->i_freeb = ifreet;
		ifreet = &ip->i_freef;
	}
	ip->i_freef = NULL;
E 76
E 18
}
E 104
I 104
D 134
	if (!first)
E 134
I 134
	if (done)
E 134
		return (0);
D 134
	first = 0;
E 104

I 18
D 67
#ifdef notdef
E 67
E 18
D 104
/*
I 18
D 67
 * Find an inode if it is incore.
 * This is the equivalent, for inodes,
 * of ``incore'' in bio.c or ``pfind'' in subr.c.
 */
struct inode *
ifind(dev, ino)
	dev_t dev;
	ino_t ino;
{
	register struct inode *ip;
	register union  ihead *ih;

	ih = &ihead[INOHASH(dev, ino)];
	for (ip = ih->ih_chain[0]; ip != (struct inode *)ih; ip = ip->i_forw)
		if (ino==ip->i_number && dev==ip->i_dev)
			return (ip);
	return ((struct inode *)0);
}
#endif notdef

/*
E 18
D 15
 * Find an inode if it is incore.
 * This is the equivalent, for inodes,
 * of ``incore'' in bio.c or ``pfind'' in subr.c.
 */
struct inode *
ifind(dev, ino)
D 12
dev_t dev;
ino_t ino;
E 12
I 12
	dev_t dev;
	ino_t ino;
E 12
{
	register struct inode *ip;

	for (ip = &inode[inohash[INOHASH(dev,ino)]]; ip != &inode[-1];
	    ip = &inode[ip->i_hlink])
		if (ino==ip->i_number && dev==ip->i_dev)
			return (ip);
	return ((struct inode *)0);
}

/*
E 15
 * Look up an inode by device,inumber.
E 67
I 67
D 102
 * Look up an vnode/inode by device,inumber.
E 67
 * If it is in core (in the inode structure),
 * honor the locking protocol.
 * If it is not in core, read it in from the
 * specified device.
D 67
 * If the inode is mounted on, perform
 * the indicated indirection.
E 67
I 67
 * Callers must check for mount points!!
E 67
 * In all cases, a pointer to a locked
 * inode structure is returned.
E 102
I 102
 * Look up a UFS dinode number to find its incore vnode.
 * If it is not in core, read it in from the specified device.
 * If it is in core, wait for the lock bit to clear, then
 * return the inode locked. Detection and handling of mount
 * points must be done by the calling routine.
E 102
D 67
 *
D 8
 * printf warning: no inodes -- if the inode
 *	structure is full
E 8
 * panic: no imt -- if the mounted file
 *	system is not in the mount table.
 *	"cannot happen"
E 67
 */
D 67
struct inode *
D 15
iget(dev, ino)
E 15
I 15
iget(dev, fs, ino)
E 15
D 12
dev_t dev;
ino_t ino;
E 12
I 12
	dev_t dev;
I 15
	register struct fs *fs;
E 67
I 67
iget(xp, ino, ipp)
	struct inode *xp;
E 67
E 15
	ino_t ino;
I 67
	struct inode **ipp;
E 67
E 12
{
D 18
	register struct inode *ip;
E 18
I 18
D 19
	register struct inode *ip;	/* known to be r11 - see "asm" below */
	register union  ihead *ih;	/* known to be r10 - see "asm" below */
E 19
I 19
D 67
	register struct inode *ip;
	register union  ihead *ih;
E 19
E 18
	register struct mount *mp;
	register struct buf *bp;
	register struct dinode *dp;
D 18
	register int slot;
E 18
I 18
	register struct inode *iq;
E 67
I 67
	dev_t dev = xp->i_dev;
	struct mount *mntp = ITOV(xp)->v_mount;
	register struct fs *fs = VFSTOUFS(mntp)->um_fs;
I 77
	extern struct vnodeops ufs_vnodeops, spec_inodeops;
E 77
	register struct inode *ip, *iq;
	register struct vnode *vp;
D 77
	struct inode *nip;
E 77
I 77
	struct vnode *nvp;
E 77
	struct buf *bp;
D 77
	struct dinode tdip, *dp;
E 77
I 77
	struct dinode *dp;
E 77
D 92
	union  ihead *ih;
	int error;
E 92
I 92
	union ihead *ih;
	int i, error;
E 92
E 67
I 47
D 50
	struct inode *xp;
E 50
E 47
E 18

I 47
D 59

E 59
E 47
D 77
loop:
E 77
I 15
D 45
	if (getfs(dev) != fs)
		panic("iget: bad fs");
E 45
E 15
D 18
	slot = INOHASH(dev, ino);
	ip = &inode[inohash[slot]];
	while (ip != &inode[-1]) {
E 18
I 18
	ih = &ihead[INOHASH(dev, ino)];
I 77
loop:
E 77
D 76
	for (ip = ih->ih_chain[0]; ip != (struct inode *)ih; ip = ip->i_forw)
E 18
D 12
		if(ino == ip->i_number && dev == ip->i_dev) {
			if((ip->i_flag&ILOCK) != 0) {
E 12
I 12
		if (ino == ip->i_number && dev == ip->i_dev) {
I 46
			/*
			 * Following is essentially an inline expanded
			 * copy of igrab(), expanded inline for speed,
			 * and so that the test for a mounted on inode
			 * can be deferred until after we are sure that
			 * the inode isn't busy.
			 */
E 46
D 30
			if ((ip->i_flag&ILOCK) != 0) {
E 30
I 30
			if ((ip->i_flag&ILOCKED) != 0) {
E 30
E 12
				ip->i_flag |= IWANT;
				sleep((caddr_t)ip, PINOD);
				goto loop;
			}
D 12
			if((ip->i_flag&IMOUNT) != 0) {
E 12
I 12
D 67
			if ((ip->i_flag&IMOUNT) != 0) {
E 12
D 15
				for(mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
E 15
I 15
				for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
E 15
D 12
				if(mp->m_inodp == ip) {
E 12
I 12
D 18
				if (mp->m_inodp == ip) {
E 12
					dev = mp->m_dev;
I 15
					fs = mp->m_bufp->b_un.b_fs;
E 15
					ino = ROOTINO;
					goto loop;
				}
E 18
I 18
					if(mp->m_inodp == ip) {
						dev = mp->m_dev;
D 65
						fs = mp->m_bufp->b_un.b_fs;
E 65
I 65
						fs = mp->m_fs;
E 65
						ino = ROOTINO;
						goto loop;
					}
E 18
				panic("no imt");
			}
I 18
			if (ip->i_count == 0) {		/* ino on free list */
E 67
I 67
			vp = ITOV(ip);
			if (vp->v_count == 0) {		/* ino on free list */
E 67
				if (iq = ip->i_freef)
					iq->i_freeb = ip->i_freeb;
				else
					ifreet = ip->i_freeb;
				*ip->i_freeb = iq;
				ip->i_freef = NULL;
				ip->i_freeb = NULL;
			}
E 18
D 67
			ip->i_count++;
E 67
D 30
			ip->i_flag |= ILOCK;
E 30
I 30
D 68
			ip->i_flag |= ILOCKED;
E 68
I 68
			ILOCK(ip);
E 68
E 30
D 67
			return(ip);
E 67
I 67
D 70
			vp->v_count++;
E 70
I 70
			VREF(vp);
E 70
			*ipp = ip;
			return(0);
E 76
I 76
	for (ip = ih->ih_chain[0]; ip != (struct inode *)ih; ip = ip->i_forw) {
		if (ino != ip->i_number || dev != ip->i_dev)
			continue;
D 77
		/*
		 * Following is essentially an inline expanded
		 * copy of igrab(), expanded inline for speed,
		 * and so that the test for a mounted on inode
		 * can be deferred until after we are sure that
		 * the inode isn't busy.
		 */
E 77
		if ((ip->i_flag&ILOCKED) != 0) {
			ip->i_flag |= IWANT;
			sleep((caddr_t)ip, PINOD);
			goto loop;
E 76
E 67
		}
I 67
D 76
	if (error = getnewino(dev, ino, &nip)) {
E 76
I 76
D 77
		vp = ITOV(ip);
		if (vp->v_count == 0)		/* ino on free list */
			vget(vp);
		else
			VREF(vp);
		ILOCK(ip);
E 77
I 77
		if (vget(ITOV(ip)))
			goto loop;
E 77
		*ipp = ip;
		return(0);
	}
D 77
	if (error = getnewino(dev, ino, mntp, &nip)) {
E 77
I 77
	/*
	 * Allocate a new inode.
	 */
	if (error = getnewvnode(VT_UFS, mntp, &ufs_vnodeops, &nvp)) {
E 77
E 76
		*ipp = 0;
		return (error);
	}
D 77
	ip = nip;
E 77
I 77
	ip = VTOI(nvp);
	ip->i_vnode = nvp;
	ip->i_flag = 0;
	ip->i_devvp = 0;
D 88
	ip->i_lastr = 0;
E 88
	ip->i_mode = 0;
I 89
	ip->i_diroff = 0;
I 99
	ip->i_lockf = 0;
E 99
E 89
D 81
	ip->i_flags = 0;
E 81
#ifdef QUOTA
D 92
	ip->i_dquot = NODQUOT;
E 92
I 92
	for (i = 0; i < MAXQUOTAS; i++)
		ip->i_dquot[i] = NODQUOT;
E 104
I 104
#ifdef DIAGNOSTIC
D 106
	if (VN_MAXPRIVATE < sizeof(struct inode))
		panic("ufs_init: inode too small");
E 106
I 106
	if ((sizeof(struct inode) - 1) & sizeof(struct inode))
		printf("ufs_init: bad size %d\n", sizeof(struct inode));
E 106
E 104
E 92
#endif
E 134
I 134
	done = 1;
E 134
E 77
D 104
	/*
I 77
	 * Put it onto its hash chain and lock it so that other requests for
	 * this inode will block if they arrive while we are sleeping waiting
	 * for old data structures to be purged or for the contents of the
	 * disk portion of this inode to be read.
	 */
	ip->i_dev = dev;
	ip->i_number = ino;
	insque(ip, ih);
	ILOCK(ip);
	/*
E 77
	 * Read in the disk contents for the inode.
	 */
	if (error = bread(VFSTOUFS(mntp)->um_devvp, fsbtodb(fs, itod(fs, ino)),
D 73
	    (int)fs->fs_bsize, &bp)) {
E 73
I 73
	    (int)fs->fs_bsize, NOCRED, &bp)) {
E 73
		/*
I 93
		 * The inode does not contain anything useful, so it would
		 * be misleading to leave it on its hash chain.
		 * Iput() will take care of putting it back on the free list.
		 */
		remque(ip);
		ip->i_forw = ip;
		ip->i_back = ip;
		/*
E 93
D 76
		 * The inode doesn't contain anything useful, so it would
		 * be misleading to leave it on its hash chain. Iput() will
		 * take care of putting it back on the free list. We also
		 * lose its inumber, just in case.
E 76
I 76
		 * Unlock and discard unneeded inode.
E 76
		 */
D 76
		remque(ip);
		ip->i_forw = ip;
		ip->i_back = ip;
		ip->i_number = 0;
I 72
		ITOV(ip)->v_type = VNON;
E 72
		INSFREE(ip);
E 76
I 68
D 77
		iunlock(ip);
E 68
D 76
		ip->i_flag = 0;
E 76
I 76
		vrele(ITOV(ip));
E 77
I 77
		iput(ip);
E 77
E 76
		brelse(bp);
		*ipp = 0;
D 77
		return(error);
E 77
I 77
		return (error);
E 77
	}
D 77
	/*
	 * Check to see if the new inode represents a block device
	 * for which we already have an inode (either because of
	 * bdevvp() or because of a different inode representing
	 * the same block device). If such an alias exists, put the
	 * just allocated inode back on the free list, and replace
	 * the contents of the existing inode with the contents of
	 * the new inode.
	 */
E 77
	dp = bp->b_un.b_dino;
	dp += itoo(fs, ino);
D 77
	if ((dp->di_mode & IFMT) != IFBLK) {
D 76
		ip->i_ic = dp->di_ic;
E 76
I 76
		ip->i_din = *dp;
E 76
		brelse(bp);
	} else {
again:
		for (iq = bdevlisth; iq; iq = iq->i_devlst) {
D 72
			if (dp->di_rdev != ITOV(iq)->v_rdev)
E 72
I 72
			vp = ITOV(iq);
			if (dp->di_rdev != vp->v_rdev)
E 72
				continue;
			igrab(iq);
D 72
			if (dp->di_rdev != ITOV(iq)->v_rdev) {
E 72
I 72
			if (dp->di_rdev != vp->v_rdev) {
E 72
				iput(iq);
				goto again;
			}
E 77
I 77
	ip->i_din = *dp;
	brelse(bp);
	/*
	 * Initialize the associated vnode
	 */
	vp = ITOV(ip);
	vp->v_type = IFTOVT(ip->i_mode);
I 91
	if (vp->v_type == VFIFO) {
#ifdef FIFO
		extern struct vnodeops fifo_inodeops;
		vp->v_op = &fifo_inodeops;
#else
		iput(ip);
		*ipp = 0;
		return (EOPNOTSUPP);
#endif /* FIFO */
	}
E 91
	if (vp->v_type == VCHR || vp->v_type == VBLK) {
D 84
		vp->v_rdev = ip->i_rdev;
E 84
		vp->v_op = &spec_inodeops;
D 84
		if (nvp = checkalias(vp, mntp)) {
E 84
I 84
		if (nvp = checkalias(vp, ip->i_rdev, mntp)) {
E 84
E 77
			/*
D 76
			 * Discard unneeded inode.
E 76
I 76
D 77
			 * Unlock and discard unneeded inode.
E 77
I 77
			 * Reinitialize aliased inode.
E 77
E 76
			 */
D 76
			remque(ip);
			ip->i_forw = ip;
			ip->i_back = ip;
			ip->i_number = 0;
I 72
			ITOV(ip)->v_type = VNON;
E 72
			INSFREE(ip);
I 68
			iunlock(ip);
E 68
			ip->i_flag = 0;
E 76
I 76
D 77
			vput(ITOV(ip));
E 77
I 77
			vp = nvp;
			iq = VTOI(vp);
			iq->i_vnode = vp;
D 88
			iq->i_lastr = 0;
E 88
D 81
			iq->i_flags = 0;
E 81
I 81
			iq->i_flag = 0;
E 81
			ILOCK(iq);
			iq->i_din = ip->i_din;
			iq->i_dev = dev;
			iq->i_number = ino;
			insque(iq, ih);
E 77
E 76
			/*
D 77
			 * Reinitialize aliased inode.
			 * We must release the buffer that we just read
			 * before doing the iupdat() to avoid a possible
			 * deadlock with updating an inode in the same
			 * disk block.
E 77
I 77
			 * Discard unneeded vnode
E 77
			 */
I 77
			ip->i_mode = 0;
			iput(ip);
E 77
			ip = iq;
D 72
			vp = ITOV(iq);
E 72
D 76
			tdip.di_ic = dp->di_ic;
E 76
I 76
D 77
			vp = ITOV(ip);
			tdip = *dp;
E 76
			brelse(bp);
			error = iupdat(ip, &time, &time, 1);
D 76
			ip->i_ic = tdip.di_ic;
E 76
I 76
			ip->i_din = tdip;
E 76
			remque(ip);
			insque(ip, ih);
			ip->i_dev = dev;
			ip->i_number = ino;
I 76
			insmntque(vp, mntp);
E 76
			if (ip->i_devvp) {
				vrele(ip->i_devvp);
				ip->i_devvp = 0;
			}
			cache_purge(vp);
			break;
E 77
		}
D 77
		if (iq == 0) {
D 76
			ip->i_ic = dp->di_ic;
E 76
I 76
			ip->i_din = *dp;
E 76
			brelse(bp);
			ip->i_devlst = bdevlisth;
			bdevlisth = ip;
		}
E 77
	}
I 77
	if (ino == ROOTINO)
		vp->v_flag |= VROOT;
E 77
	/*
	 * Finish inode initialization.
	 */
	ip->i_fs = fs;
	ip->i_devvp = VFSTOUFS(mntp)->um_devvp;
D 70
	ip->i_devvp->v_count++;
E 70
I 70
	VREF(ip->i_devvp);
E 70
D 77
	/*
	 * Initialize the associated vnode
	 */
	vp = ITOV(ip);
D 76
	vinit(vp, mntp, IFTOVT(ip->i_mode), &ufs_vnodeops);
E 76
I 76
	vp->v_type = IFTOVT(ip->i_mode);
E 76
	if (vp->v_type == VCHR || vp->v_type == VBLK) {
		vp->v_rdev = ip->i_rdev;
		vp->v_op = &blk_vnodeops;
	}
	if (ino == ROOTINO)
		vp->v_flag |= VROOT;
E 77
D 92
#ifdef QUOTA
	if (ip->i_mode != 0)
		ip->i_dquot = inoquota(ip);
#endif
E 92
I 69
	/*
	 * Set up a generation number for this inode if it does not
	 * already have one. This should only happen on old filesystems.
	 */
	if (ip->i_gen == 0) {
		if (++nextgennumber < (u_long)time.tv_sec)
			nextgennumber = time.tv_sec;
		ip->i_gen = nextgennumber;
D 94
		if ((vp->v_mount->m_flag & M_RDONLY) == 0)
E 94
I 94
		if ((vp->v_mount->mnt_flag & MNT_RDONLY) == 0)
E 94
			ip->i_flag |= IMOD;
	}
E 69
	*ipp = ip;
E 104
I 104
	ufs_ihashinit();
I 132
#ifdef QUOTA
E 132
	dqinit();
I 132
#endif
E 132
E 104
	return (0);
}
E 67
D 18
		ip = &inode[ip->i_hlink];
	}
D 12
	if(ifreel < 0) {
E 12
I 12
	if (ifreel < 0) {
E 18
I 18

E 135
I 67
/*
D 77
 * Allocate a new inode.
 *
 * Put it onto its hash chain and lock it so that other requests for
 * this inode will block if they arrive while we are sleeping waiting
 * for old data structures to be purged or for the contents of the disk
 * portion of this inode to be read.
 */
D 76
getnewino(dev, ino, ipp)
E 76
I 76
getnewino(dev, ino, mp, ipp)
E 76
	dev_t dev;
	ino_t ino;
I 76
	struct mount *mp;
E 76
	struct inode **ipp;
{
	union ihead *ih;
D 76
	register struct inode *ip, *iq;
	register struct vnode *vp;
E 76
I 76
	register struct inode *ip;
	struct vnode *vp;
	int error;
E 76

I 76
	if (error = getnewvnode(VT_UFS, mp, &ufs_vnodeops, &vp))
		return (error);
	ip = VTOI(vp);
	ip->i_vnode = vp;
	ip->i_flag = 0;
	ip->i_devvp = 0;
	ip->i_lastr = 0;
	ip->i_mode = 0;
#ifdef QUOTA
	ip->i_dquot = NODQUOT;
#endif
E 76
	/*
D 76
	 * Remove the next inode from the free list.
E 76
I 76
	 * Put the inode on the chain for its new (ino, dev) pair.
E 76
	 */
E 67
D 76
	if ((ip = ifreeh) == NULL) {
E 18
E 12
D 8
		printf("Inode table overflow\n");
E 8
I 8
		tablefull("inode");
E 8
D 67
		u.u_error = ENFILE;
		return(NULL);
E 67
I 67
		*ipp = 0;
		return(ENFILE);
E 67
	}
I 49
D 67
	if (ip->i_count)
E 67
I 67
	vp = ITOV(ip);
	if (vp->v_count)
E 67
		panic("free inode isn't");
E 49
D 18
	ip = &inode[ifreel];
	ifreel = ip->i_hlink;
	ip->i_hlink = inohash[slot];
	inohash[slot] = ip - inode;
E 18
I 18
	if (iq = ip->i_freef)
		iq->i_freeb = &ifreeh;
	ifreeh = iq;
	ip->i_freef = NULL;
	ip->i_freeb = NULL;
	/*
	 * Now to take inode off the hash chain it was on
	 * (initially, or after an iflush, it is on a "hash chain"
D 67
	 * consisting entirely of itself, and pointed to by no-one,
	 * but that doesn't matter), and put it on the chain for
	 * its new (ino, dev) pair
E 67
I 67
	 * consisting entirely of itself, and pointed to by no-one)
	 * and put it on the chain for its new (ino, dev) pair.
E 67
	 */
D 19
#ifndef	UNFAST
	asm("remque	(r11),r0");
	asm("insque	(r11),(r10)");
#else
		/* remque */
	ip->i_back->i_forw = ip->i_forw;
	ip->i_forw->i_back = ip->i_back;
		/* insque */
	ip->i_forw = ih->ih_chain[0];
	ip->i_back = (struct inode *)ih;
	ih->ih_chain[0]->i_back = ip;
	ih->ih_chain[0] = ip;
#endif
E 19
I 19
	remque(ip);
E 76
D 67
	insque(ip, ih);
E 67
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 49
#ifdef QUOTA
E 27
	dqrele(ip->i_dquot);
#endif
E 49
E 23
E 19
E 18
	ip->i_dev = dev;
I 15
D 67
	ip->i_fs = fs;
E 67
E 15
	ip->i_number = ino;
I 46
D 50
	ip->i_id = ++nextinodeid;	/* also used in rename */
	/*
	 * At an absurd rate of 100 calls/second,
D 47
	 * this should occur once every 16 months.
E 47
I 47
	 * this should occur once every 8 months.
E 47
	 */
D 47
	if (nextinodeid == 0)
		panic("iget: wrap");
E 47
I 47
	if (nextinodeid < 0)
		for (nextinodeid = 0, xp = inode; xp < inodeNINODE; xp++)
			xp->i_id = 0;
E 50
I 50
D 67
	cacheinval(ip);
E 67
I 67
	if (dev != NODEV) {
		ih = &ihead[INOHASH(dev, ino)];
		insque(ip, ih);
I 76
	} else {
		ip->i_forw = ip;
		ip->i_back = ip;
E 76
	}
E 67
E 50
E 47
E 46
D 30
	ip->i_flag = ILOCK;
E 30
I 30
D 68
	ip->i_flag = ILOCKED;
E 68
I 68
D 76
	ip->i_flag = 0;
E 76
	ILOCK(ip);
E 68
E 30
D 67
	ip->i_count++;
E 67
D 15
	ip->i_un.i_lastr = 0;
	bp = bread(dev, itod(ino));
E 15
I 15
D 76
	ip->i_lastr = 0;
I 49
D 67
#ifdef QUOTA
	dqrele(ip->i_dquot);
#endif
I 62
#ifdef SECSIZE
	bp = bread(dev, fsbtodb(fs, itod(fs, ino)), (int)fs->fs_bsize,
	    fs->fs_dbsize);
#else SECSIZE
E 62
E 49
D 32
	bp = bread(dev, fsbtodb(fs, itod(fs, ino)), fs->fs_bsize);
E 32
I 32
	bp = bread(dev, fsbtodb(fs, itod(fs, ino)), (int)fs->fs_bsize);
E 67
I 62
#endif SECSIZE
E 62
E 32
E 15
	/*
D 67
	 * Check I/O errors
E 67
I 67
	 * Purge old data structures associated with the inode.
E 67
	 */
D 12
	if((bp->b_flags&B_ERROR) != 0) {
E 12
I 12
D 67
	if ((bp->b_flags&B_ERROR) != 0) {
E 12
		brelse(bp);
I 18
		/*
		 * the inode doesn't contain anything useful, so it would
		 * be misleading to leave it on its hash chain.
		 * 'iput' will take care of putting it back on the free list.
		 */
D 19
#ifndef	UNFAST
		asm("remque	(r11),r0");
#else
		ip->i_back->i_forw = ip->i_forw;
		ip->i_forw->i_back = ip->i_back;
#endif
E 19
I 19
		remque(ip);
E 19
		ip->i_forw = ip;
		ip->i_back = ip;
		/*
		 * we also loose its inumber, just in case (as iput
		 * doesn't do that any more) - but as it isn't on its
		 * hash chain, I doubt if this is really necessary .. kre
		 * (probably the two methods are interchangable)
		 */
		ip->i_number = 0;
I 23
D 27
#ifdef	QUOTA
E 27
I 27
#ifdef QUOTA
E 27
		ip->i_dquot = NODQUOT;
#endif
E 23
E 18
		iput(ip);
		return(NULL);
E 67
I 67
	cache_purge(vp);
	if (ip->i_devvp) {
		vrele(ip->i_devvp);
		ip->i_devvp = 0;
E 67
	}
D 67
	dp = bp->b_un.b_dino;
D 15
	dp += itoo(ino);
	iexpand(ip, dp);
E 15
I 15
	dp += itoo(fs, ino);
	ip->i_ic = dp->di_ic;
E 15
	brelse(bp);
E 67
I 23
D 27
#ifdef	QUOTA
E 27
I 27
#ifdef QUOTA
E 27
D 67
	if (ip->i_mode == 0)
		ip->i_dquot = NODQUOT;
	else
		ip->i_dquot = inoquota(ip);
E 67
I 67
	dqrele(ip->i_dquot);
	ip->i_dquot = NODQUOT;
E 67
#endif
E 23
D 15
	return(ip);
E 15
I 15
D 67
	return (ip);
E 67
I 67
	if (vp->v_type == VBLK) {
		if (bdevlisth == ip) {
			bdevlisth = ip->i_devlst;
		} else {
			for (iq = bdevlisth; iq; iq = iq->i_devlst) {
				if (iq->i_devlst != ip)
					continue;
				iq->i_devlst = ip->i_devlst;
				break;
			}
			if (iq == NULL)
				panic("missing bdev");
		}
	}
E 76
	*ipp = ip;
	return (0);
E 67
I 46
}

/*
 * Convert a pointer to an inode into a reference to an inode.
 *
 * This is basically the internal piece of iget (after the
 * inode pointer is located) but without the test for mounted
 * filesystems.  It is caller's responsibility to check that
 * the inode pointer is valid.
 */
igrab(ip)
	register struct inode *ip;
{
I 67
	register struct vnode *vp = ITOV(ip);

E 67
	while ((ip->i_flag&ILOCKED) != 0) {
		ip->i_flag |= IWANT;
		sleep((caddr_t)ip, PINOD);
	}
D 67
	if (ip->i_count == 0) {		/* ino on free list */
E 67
I 67
D 76
	if (vp->v_count == 0) {		/* ino on free list */
E 67
		register struct inode *iq;

		if (iq = ip->i_freef)
			iq->i_freeb = ip->i_freeb;
		else
			ifreet = ip->i_freeb;
		*ip->i_freeb = iq;
		ip->i_freef = NULL;
		ip->i_freeb = NULL;
	}
D 67
	ip->i_count++;
E 67
I 67
D 70
	vp->v_count++;
E 70
I 70
	VREF(vp);
E 76
I 76
	if (vp->v_count == 0)		/* ino on free list */
		vget(vp);
	else
		VREF(vp);
E 76
E 70
E 67
D 68
	ip->i_flag |= ILOCKED;
E 68
I 68
	ILOCK(ip);
E 68
E 46
E 15
}

I 25
D 26
#ifdef MATISSE
int	badinum = 3197;
#else
E 25
I 24
int	badinum = -1;
I 25
#endif
E 26
E 25
E 24
D 15
iexpand(ip, dp)
D 12
register struct inode *ip;
register struct dinode *dp;
E 12
I 12
	register struct inode *ip;
	register struct dinode *dp;
E 12
{
	register char *p1, *p2;
	register int i;

	ip->i_mode = dp->di_mode;
	ip->i_nlink = dp->di_nlink;
	ip->i_uid = dp->di_uid;
	ip->i_gid = dp->di_gid;
	ip->i_size = dp->di_size;
	p1 = (char *)ip->i_un.i_addr;
	p2 = (char *)dp->di_addr;
	for(i=0; i<NADDR; i++) {
		*p1++ = *p2++;
		*p1++ = *p2++;
		*p1++ = *p2++;
		*p1++ = 0;
	}
}

E 15
/*
I 67
 * Create a vnode for a block device.
 * Used for root filesystem, argdev, and swap areas.
 */
bdevvp(dev, vpp)
	dev_t dev;
	struct vnode **vpp;
{
	register struct inode *ip;
	register struct vnode *vp;
	struct inode *nip;
	int error;

	/*
	 * Check for the existence of an existing vnode.
	 */
again:
	for (ip = bdevlisth; ip; ip = ip->i_devlst) {
		vp = ITOV(ip);
		if (dev != vp->v_rdev)
			continue;
		igrab(ip);
		if (dev != vp->v_rdev) {
			iput(ip);
			goto again;
		}
		IUNLOCK(ip);
		*vpp = vp;
		return (0);
	}
D 76
	if (error = getnewino(NODEV, (ino_t)0, &nip)) {
E 76
I 76
	if (error = getnewino(NODEV, (ino_t)0, (struct mount *)0, &nip)) {
E 76
		*vpp = 0;
		return (error);
	}
	ip = nip;
	ip->i_fs = 0;
	ip->i_devlst = bdevlisth;
	bdevlisth = ip;
	vp = ITOV(ip);
D 76
	vinit(vp, 0, VBLK, &blk_vnodeops);
E 76
I 76
	vp->v_type = VBLK;
	vp->v_op = &blk_vnodeops;
E 76
	vp->v_rdev = dev;
	IUNLOCK(ip);
	*vpp = vp;
	return (0);
}

/*
E 77
E 67
D 76
 * Decrement reference count of
 * an inode structure.
 * On the last reference,
 * write the inode out and if necessary,
 * truncate and deallocate the file.
E 76
I 76
D 126
 * Unlock and decrement the reference count of an inode structure.
E 76
 */
D 104
iput(ip)
E 104
I 104
void
ufs_iput(ip)
E 104
D 12
register struct inode *ip;
E 12
I 12
	register struct inode *ip;
E 12
{
I 16

D 30
	if ((ip->i_flag & ILOCK) == 0)
E 30
I 30
	if ((ip->i_flag & ILOCKED) == 0)
E 30
		panic("iput");
I 24
D 26
/* XXX */
	if (ip->i_number == badinum && (ip->i_mode&IFMT) == IFCHR &&
	    (major(ip->i_dev) != 3 || minor(ip->i_dev) != 2))
		panic("/dev/null");
/* XXX */
E 26
E 24
D 48
	iunlock(ip);
E 48
I 48
	IUNLOCK(ip);
E 48
D 67
	irele(ip);
E 67
I 67
	vrele(ITOV(ip));
E 67
D 105
}

D 67
irele(ip)
	register struct inode *ip;
E 67
I 67
D 76

E 76
I 76
/*
 * Last reference to an inode, write the inode out and if necessary,
 * truncate and deallocate the file.
 */
I 104
int
E 104
E 76
D 101
ufs_inactive(vp)
E 101
I 101
ufs_inactive(vp, p)
E 101
	struct vnode *vp;
I 101
	struct proc *p;
E 101
E 67
{
E 16
D 31
	register int i, x;
	register struct inode *jp;
E 31
I 15
D 67
	int mode;
E 67
I 67
D 104
	register struct inode *ip = VTOI(vp);
D 76
	int mode, error;
E 76
I 76
	int mode, error = 0;
E 104
I 104
	register struct inode *ip;
	struct ufsmount *ump;
	int mode, error;
E 104
E 76
E 67
E 15

I 16
D 17
	if (ip->i_flag & ILOCK)
		panic("irele");
E 17
E 16
D 12
	if(ip->i_count == 1) {
E 12
I 12
D 54
	if (ip->i_count == 1) {
E 54
I 54
D 56
	if (ip->i_count == 1 && ip->i_fs->fs_ronly != 0) {
E 56
I 56
D 67
	if (ip->i_count == 1) {
E 56
E 54
E 12
D 30
		ip->i_flag |= ILOCK;
E 30
I 30
		ip->i_flag |= ILOCKED;
E 30
D 12
		if(ip->i_nlink <= 0) {
E 12
I 12
D 56
		if (ip->i_nlink <= 0) {
E 56
I 56
		if (ip->i_nlink <= 0 && ip->i_fs->fs_ronly == 0) {
E 56
E 12
D 28
			itrunc(ip);
E 28
I 28
D 36
			itrunc(ip, 0);
E 36
I 36
			itrunc(ip, (u_long)0);
E 36
E 28
I 15
			mode = ip->i_mode;
E 15
			ip->i_mode = 0;
I 22
			ip->i_rdev = 0;
E 22
			ip->i_flag |= IUPD|ICHG;
D 15
			ifree(ip->i_dev, ip->i_number);
E 15
I 15
			ifree(ip, ip->i_number, mode);
E 67
I 67
D 75
	if (ITOV(ip)->v_count != 0)
E 75
I 75
D 82
	if (vp->v_count != 0)
E 82
I 82
D 88
	if (prtactive && vp->v_count != 0)
E 88
I 88
	if (prtactive && vp->v_usecount != 0)
E 88
E 82
E 75
D 77
		panic("ufs_inactive: not inactive");
E 77
I 77
D 85
		printf("ufs_inactive: pushing active ino %d dev 0x%x\n",
			ip->i_number, ip->i_dev);
E 85
I 85
		vprint("ufs_inactive: pushing active", vp);
E 85
E 77
I 71
D 104
	/*
	 * Get rid of inodes related to stale file handles.
	 */
E 104
I 104

	/* Get rid of inodes related to stale file handles. */
	ip = VTOI(vp);
E 104
D 77
	if (ip->i_mode == 0)
D 76
		goto freeit;
E 76
I 76
		return (ufs_reclaim(vp));
E 77
I 77
	if (ip->i_mode == 0) {
D 85
		vgone(vp);
E 85
I 85
		if ((vp->v_flag & VXLOCK) == 0)
			vgone(vp);
E 85
		return (0);
	}
I 104

	error = 0;
	ump = VFSTOUFS(vp->v_mount);
E 104
E 77
E 76
E 71
D 68
	ip->i_flag |= ILOCKED;
E 68
I 68
	ILOCK(ip);
E 68
D 75
	if (ip->i_nlink <= 0 && (ITOV(ip)->v_mount->m_flag&M_RDONLY) == 0) {
E 75
I 75
D 94
	if (ip->i_nlink <= 0 && (vp->v_mount->m_flag & M_RDONLY) == 0) {
E 94
I 94
	if (ip->i_nlink <= 0 && (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
E 94
I 92
#ifdef QUOTA
		if (!getinoquota(ip))
D 104
			(void) chkiq(ip, -1, NOCRED, 0);
E 104
I 104
			(void)chkiq(ip, -1, NOCRED, 0);
E 104
#endif
E 92
E 75
D 85
		error = itrunc(ip, (u_long)0);
E 85
I 85
D 104
		error = itrunc(ip, (u_long)0, 0);
E 104
I 104
		error = (ump->um_itrunc)(ip, (u_long)0, 0);
E 104
E 85
		mode = ip->i_mode;
		ip->i_mode = 0;
I 96
		ip->i_rdev = 0;
E 96
D 92
		ip->i_rdev = 0;
E 92
		ip->i_flag |= IUPD|ICHG;
D 104
		ifree(ip, ip->i_number, mode);
E 104
I 104
		(ump->um_ifree)(ip, ip->i_number, mode);
E 104
E 67
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 92
#ifdef QUOTA
E 27
D 36
			chkiq(ip->i_dev, ip, ip->i_uid, 0);
E 36
I 36
D 40
			(void)chkiq(ip->i_dev, ip, ip->i_uid, 0);
E 40
I 40
D 67
			(void) chkiq(ip->i_dev, ip, ip->i_uid, 0);
E 40
E 36
			dqrele(ip->i_dquot);
			ip->i_dquot = NODQUOT;
E 67
I 67
		(void) chkiq(ip->i_dev, ip, ip->i_uid, 0);
		dqrele(ip->i_dquot);
		ip->i_dquot = NODQUOT;
E 67
#endif
E 92
E 23
E 15
D 67
		}
D 2
		iupdat(ip, &time, &time);
E 2
I 2
D 5
		IUPDAT(ip, &time, &time);
E 5
I 5
D 29
		IUPDAT(ip, &time, &time, 0);
E 29
I 29
D 33
		IUPDAT(ip, &time.tv_sec, &time.tv_sec, 0);
E 33
I 33
D 34
		IUPDAT(ip, time, time, 0);
E 34
I 34
		IUPDAT(ip, &time, &time, 0);
E 34
E 33
E 29
E 5
E 2
D 12
		prele(ip);
E 12
I 12
D 16
		irele(ip);
E 16
I 16
D 48
		iunlock(ip);
E 48
I 48
		IUNLOCK(ip);
E 48
E 16
E 12
D 18
		i = INOHASH(ip->i_dev, ip->i_number);
		x = ip - inode;
		if (inohash[i] == x) {
			inohash[i] = ip->i_hlink;
E 18
I 18
		ip->i_flag = 0;
		/*
		 * Put the inode on the end of the free list.
		 * Possibly in some cases it would be better to
		 * put the inode at the head of the free list,
		 * (eg: where i_mode == 0 || i_number == 0)
		 * but I will think about that later .. kre
		 * (i_number is rarely 0 - only after an i/o error in iget,
		 * where i_mode == 0, the inode will probably be wanted
		 * again soon for an ialloc, so possibly we should keep it)
		 */
		if (ifreeh) {
			*ifreet = ip;
			ip->i_freeb = ifreet;
E 18
		} else {
D 18
			for (jp = &inode[inohash[i]]; jp != &inode[-1];
			    jp = &inode[jp->i_hlink])
				if (jp->i_hlink == x) {
					jp->i_hlink = ip->i_hlink;
					goto done;
				}
			panic("iput");
E 18
I 18
			ifreeh = ip;
			ip->i_freeb = &ifreeh;
E 18
		}
D 18
done:
		ip->i_hlink = ifreel;
		ifreel = x;
		ip->i_flag = 0;
		ip->i_number = 0;
E 18
I 18
		ip->i_freef = NULL;
		ifreet = &ip->i_freef;
I 43
D 44
	} else if ((ip->i_flag & (IUPD|IACC|ICHG)) &&
	    ((ip->i_flag & ILOCKED) == 0)) {
		ip->i_flag |= ILOCKED;
		iupdat(ip, &time, &time, 0);
		iunlock(ip);
E 43
E 18
D 16
	} else
D 12
		prele(ip);
E 12
I 12
		irele(ip);
E 16
I 16
	}
E 44
I 44
	} else if (!(ip->i_flag & ILOCKED))
		ITIMES(ip, &time, &time);
E 44
E 16
E 12
	ip->i_count--;
E 67
I 67
	}
D 104
	IUPDAT(ip, &time, &time, 0);
E 104
I 104
	if (ip->i_flag&(IUPD|IACC|ICHG|IMOD))
		(ump->um_iupdat)(ip, &time, &time, 0);
E 104
I 90
	IUNLOCK(ip);
	ip->i_flag = 0;
E 90
D 85
	IUNLOCK(ip);
I 71
D 76
freeit:
E 76
E 71
	ip->i_flag = 0;
E 85
	/*
D 76
	 * Put the inode on the end of the free list.
	 * Possibly in some cases it would be better to
	 * put the inode at the head of the free list,
	 * (eg: where i_mode == 0 || i_number == 0).
E 76
I 76
	 * If we are done with the inode, reclaim it
	 * so that it can be reused immediately.
E 76
	 */
D 76
	INSFREE(ip);
E 76
I 76
D 77
	if (ip->i_mode == 0 && !error)
		return (ufs_reclaim(vp));
E 77
I 77
D 85
	if (vp->v_count == 0 && ip->i_mode == 0)
		vgone(vp);
E 85
I 85
D 88
	if (vp->v_count == 0 && ip->i_mode == 0) {
E 88
I 88
D 90
	if (vp->v_usecount == 0 && ip->i_mode == 0) {
E 88
		vinvalbuf(vp, 0);
		IUNLOCK(ip);
		ip->i_flag = 0;
		if ((vp->v_flag & VXLOCK) == 0)
			vgone(vp);
		return (error);
	}
	IUNLOCK(ip);
	ip->i_flag = 0;
E 90
I 90
D 92
	if (vp->v_usecount == 0 && ip->i_mode == 0 &&
	    (vp->v_flag & VXLOCK) == 0)
E 92
I 92
	if (vp->v_usecount == 0 && ip->i_mode == 0)
E 92
		vgone(vp);
E 90
E 85
E 77
E 76
	return (error);
E 105
E 67
}

/*
E 126
I 125
D 130
 * Last reference to an inode, write the inode out and if necessary,
 * truncate and deallocate the file.
E 130
I 130
 * Last reference to an inode.  If necessary, write or delete it.
E 130
 */
int
ufs_inactive(ap)
	struct vop_inactive_args /* {
		struct vnode *a_vp;
I 136
		struct proc *a_p;
E 136
	} */ *ap;
{
D 136
	register struct vnode *vp = ap->a_vp;
	register struct inode *ip = VTOI(vp);
E 136
I 136
	struct vnode *vp = ap->a_vp;
	struct inode *ip = VTOI(vp);
	struct proc *p = ap->a_p;
E 136
	struct timeval tv;
D 136
	int mode, error;
E 136
I 136
	int mode, error = 0;
E 136
	extern int prtactive;

	if (prtactive && vp->v_usecount != 0)
		vprint("ffs_inactive: pushing active", vp);

D 136
	/* Get rid of inodes related to stale file handles. */
	if (ip->i_mode == 0) {
		if ((vp->v_flag & VXLOCK) == 0)
			vgone(vp);
		return (0);
	}

	error = 0;
#ifdef DIAGNOSTIC
	if (VOP_ISLOCKED(vp))
		panic("ffs_inactive: locked inode");
I 127
	if (curproc)
		ip->i_lockholder = curproc->p_pid;
	else
		ip->i_lockholder = -1;
E 127
#endif
D 130
	ip->i_flag |= ILOCKED;
E 130
I 130
	ip->i_flag |= IN_LOCKED;
E 136
I 136
	/*
	 * Ignore inodes related to stale file handles.
	 */
	if (ip->i_mode == 0)
		goto out;
E 136
E 130
	if (ip->i_nlink <= 0 && (vp->v_mount->mnt_flag & MNT_RDONLY) == 0) {
#ifdef QUOTA
		if (!getinoquota(ip))
			(void)chkiq(ip, -1, NOCRED, 0);
#endif
D 136
		error = VOP_TRUNCATE(vp, (off_t)0, 0, NOCRED, NULL);
E 136
I 136
		error = VOP_TRUNCATE(vp, (off_t)0, 0, NOCRED, p);
E 136
I 130
		ip->i_rdev = 0;
E 130
		mode = ip->i_mode;
		ip->i_mode = 0;
D 130
		ip->i_rdev = 0;
D 129
		ip->i_flag |= IUPD|ICHG;
E 129
I 129
		ip->i_flag |= IUPDATE | ICHANGE;
E 130
I 130
		ip->i_flag |= IN_CHANGE | IN_UPDATE;
E 130
E 129
		VOP_VFREE(vp, ip->i_number, mode);
	}
D 129
	if (ip->i_flag&(IUPD|IACC|ICHG|IMOD)) {
E 129
I 129
D 130
	if (ip->i_flag & (IMODIFIED | IACCESS | IUPDATE | ICHANGE)) {
E 130
I 130
	if (ip->i_flag & (IN_ACCESS | IN_CHANGE | IN_MODIFIED | IN_UPDATE)) {
E 130
E 129
		tv = time;
		VOP_UPDATE(vp, &tv, &tv, 0);
	}
D 136
	VOP_UNLOCK(vp);
E 136
I 136
out:
	VOP_UNLOCK(vp, 0, p);
E 136
	/*
	 * If we are done with the inode, reclaim it
	 * so that it can be reused immediately.
	 */
D 136
	if (vp->v_usecount == 0 && ip->i_mode == 0)
		vgone(vp);
E 136
I 136
	if (ip->i_mode == 0)
		vrecycle(vp, (struct simplelock *)0, p);
E 136
	return (error);
}

/*
E 125
D 76
 * Check accessed and update flags on
 * an inode structure.
 * If any is on, update the inode
 * with the current time.
I 5
 * If waitfor is given, then must insure
 * i/o order so wait for write to complete.
E 76
I 76
 * Reclaim an inode so that it can be used for other purposes.
E 76
E 5
 */
I 104
int
E 104
I 76
D 120
ufs_reclaim(vp)
	register struct vnode *vp;
E 120
I 120
D 123
ufs_reclaim (ap)
	struct vop_reclaim_args *ap;
E 123
I 123
D 133
ufs_reclaim(ap)
	struct vop_reclaim_args /* {
		struct vnode *a_vp;
	} */ *ap;
E 133
I 133
D 136
ufs_reclaim(vp)
	register struct vnode *vp;
E 136
I 136
ufs_reclaim(vp, p)
	struct vnode *vp;
	struct proc *p;
E 136
E 133
E 123
D 121
#define vp (ap->a_vp)
E 121
E 120
{
I 122
D 133
	register struct vnode *vp = ap->a_vp;
E 133
E 122
D 79
	register struct inode *iq, *ip = VTOI(vp);
E 79
I 79
D 104
	register struct inode *ip = VTOI(vp);
E 104
I 104
	register struct inode *ip;
E 104
I 92
D 106
	int i;
E 106
I 106
D 133
	int i, type;
E 133
I 133
	int i;
	extern int prtactive;
E 133
E 106
E 92
E 79

D 82
	if (vp->v_count != 0)
E 82
I 82
D 88
	if (prtactive && vp->v_count != 0)
E 88
I 88
D 121
	if (prtactive && vp->v_usecount != 0)
E 88
E 82
D 77
		panic("ufs_reclaim: active inode");
E 77
I 77
D 85
		printf("ufs_reclaim: pushing active ino %d dev 0x%x\n",
			ip->i_number, ip->i_dev);
E 85
I 85
		vprint("ufs_reclaim: pushing active", vp);
E 121
I 121
D 122
	if (prtactive && ap->a_vp->v_usecount != 0)
		vprint("ufs_reclaim: pushing active", ap->a_vp);
E 122
I 122
	if (prtactive && vp->v_usecount != 0)
		vprint("ufs_reclaim: pushing active", vp);
E 122
E 121
E 85
E 77
	/*
	 * Remove the inode from its hash chain.
	 */
I 104
D 121
	ip = VTOI(vp);
E 121
I 121
D 122
	ip = VTOI(ap->a_vp);
E 122
I 122
	ip = VTOI(vp);
E 122
E 121
E 104
D 124
	remque(ip);
E 124
I 124
	ufs_ihashrem(ip);
E 124
D 106
	ip->i_forw = ip;
	ip->i_back = ip;
E 106
	/*
	 * Purge old data structures associated with the inode.
	 */
D 121
	cache_purge(vp);
E 121
I 121
D 122
	cache_purge(ap->a_vp);
E 122
I 122
	cache_purge(vp);
E 122
E 121
	if (ip->i_devvp) {
		vrele(ip->i_devvp);
		ip->i_devvp = 0;
	}
#ifdef QUOTA
D 92
	dqrele(ip->i_dquot);
	ip->i_dquot = NODQUOT;
E 92
I 92
	for (i = 0; i < MAXQUOTAS; i++) {
		if (ip->i_dquot[i] != NODQUOT) {
D 121
			dqrele(vp, ip->i_dquot[i]);
E 121
I 121
D 122
			dqrele(ap->a_vp, ip->i_dquot[i]);
E 122
I 122
			dqrele(vp, ip->i_dquot[i]);
E 122
E 121
			ip->i_dquot[i] = NODQUOT;
		}
	}
E 92
#endif
D 77
	if (vp->v_type == VBLK) {
		if (bdevlisth == ip) {
			bdevlisth = ip->i_devlst;
		} else {
			for (iq = bdevlisth; iq; iq = iq->i_devlst) {
				if (iq->i_devlst != ip)
					continue;
				iq->i_devlst = ip->i_devlst;
				break;
			}
			if (iq == NULL)
				panic("missing bdev");
		}
	}
	vp->v_type = VNON;
E 77
D 106
	ip->i_flag = 0;
E 106
I 106
D 121
	switch (vp->v_mount->mnt_stat.f_type) {
E 121
I 121
D 122
	switch (ap->a_vp->v_mount->mnt_stat.f_type) {
E 122
I 122
D 133
	switch (vp->v_mount->mnt_stat.f_type) {
E 122
E 121
	case MOUNT_UFS:
		type = M_FFSNODE;
		break;
	case MOUNT_MFS:
		type = M_MFSNODE;
		break;
	case MOUNT_LFS:
		type = M_LFSNODE;
		break;
	default:
		panic("ufs_reclaim: not ufs file");
	}
D 121
	FREE(vp->v_data, type);
	vp->v_data = NULL;
E 121
I 121
D 122
	FREE(ap->a_vp->v_data, type);
	ap->a_vp->v_data = NULL;
E 122
I 122
	FREE(vp->v_data, type);
	vp->v_data = NULL;
E 133
E 122
E 121
E 106
	return (0);
D 126
}
I 120
D 121
#undef vp
E 121
E 120

/*
D 102
 * Check accessed and update flags on an inode structure.
 * If any is on, update the inode with the current time.
 * If waitfor is given, then must ensure I/O order,
 * so wait for write to complete.
E 102
I 102
D 104
 * Update the access, modified, and inode change times as specified
 * by the IACC, IMOD, and ICHG flags respectively. The IUPD flag
 * is used to specify that the inode needs to be updated but that
 * the times have already been set. The access and modified times
 * are taken from the second and third parameters; the inode change
 * time is always taken from the current time. If waitfor is set,
 * then wait for the disk write of the inode to complete.
E 102
 */
E 76
D 5
iupdat(ip, ta, tm)
E 5
I 5
iupdat(ip, ta, tm, waitfor)
E 5
D 12
register struct inode *ip;
time_t *ta, *tm;
I 5
int waitfor;
E 12
I 12
	register struct inode *ip;
D 33
	time_t *ta, *tm;
E 33
I 33
	struct timeval *ta, *tm;
E 33
	int waitfor;
E 12
E 5
{
D 67
	register struct buf *bp;
E 67
I 67
	struct buf *bp;
	struct vnode *vp = ITOV(ip);
E 67
	struct dinode *dp;
D 15
	register char *p1, *p2;
	register int i;
E 15
I 15
D 62
D 63
	register struct fs *fp;
E 63
I 63
	register struct fs *fs;
I 67
	int error;
E 67
E 63
E 62
I 62
	register struct fs *fs;
E 62
E 15

D 12
	if((ip->i_flag&(IUPD|IACC|ICHG)) != 0) {
		if(getfs(ip->i_dev)->s_ronly)
E 12
I 12
D 15
	if ((ip->i_flag&(IUPD|IACC|ICHG)) != 0) {
		if (getfs(ip->i_dev)->s_ronly)
E 15
I 15
D 62
D 63
	fp = ip->i_fs;
E 63
I 63
	fs = ip->i_fs;
E 63
E 62
I 62
	fs = ip->i_fs;
E 62
D 44
	if ((ip->i_flag & (IUPD|IACC|ICHG)) != 0) {
E 44
I 44
D 67
	if ((ip->i_flag & (IUPD|IACC|ICHG|IMOD)) != 0) {
E 44
D 62
D 63
		if (fp->fs_ronly)
E 63
I 63
		if (fs->fs_ronly)
E 63
E 62
I 62
		if (fs->fs_ronly)
E 62
E 15
E 12
			return;
D 15
		bp = bread(ip->i_dev, itod(ip->i_number));
E 15
I 15
D 62
D 63
		bp = bread(ip->i_dev, fsbtodb(fp, itod(fp, ip->i_number)),
D 32
			fp->fs_bsize);
E 32
I 32
			(int)fp->fs_bsize);
E 63
I 63
		bp = bread(ip->i_dev, fsbtodb(fs, itod(fs, ip->i_number)),
			(int)fs->fs_bsize);
E 63
E 62
I 62
#ifdef SECSIZE
		bp = bread(ip->i_dev, fsbtodb(fs, itod(fs, ip->i_number)),
			(int)fs->fs_bsize, fs->fs_dbsize);
#else SECSIZE
		bp = bread(ip->i_dev, fsbtodb(fs, itod(fs, ip->i_number)),
			(int)fs->fs_bsize);
#endif SECSIZE
E 62
E 32
E 15
		if (bp->b_flags & B_ERROR) {
			brelse(bp);
			return;
		}
D 15
		dp = bp->b_un.b_dino;
		dp += itoo(ip->i_number);
		dp->di_mode = ip->i_mode;
		dp->di_nlink = ip->i_nlink;
		dp->di_uid = ip->i_uid;
		dp->di_gid = ip->i_gid;
		dp->di_size = ip->i_size;
		p1 = (char *)dp->di_addr;
		p2 = (char *)ip->i_un.i_addr;
		for(i=0; i<NADDR; i++) {
			*p1++ = *p2++;
			*p1++ = *p2++;
			*p1++ = *p2++;
D 11
			if(*p2++ != 0 && (ip->i_mode&IFMT)!=IFMPC
			   && (ip->i_mode&IFMT)!=IFMPB)
E 11
I 11
D 12
			if(*p2++ != 0)
E 12
I 12
			if (*p2++ != 0)
E 12
E 11
				printf("iaddress > 2^24\n");
		}
E 15
D 12
		if(ip->i_flag&IACC)
E 12
I 12
		if (ip->i_flag&IACC)
E 12
D 15
			dp->di_atime = *ta;
E 15
I 15
D 33
			ip->i_atime = *ta;
E 33
I 33
			ip->i_atime = ta->tv_sec;
E 33
E 15
D 12
		if(ip->i_flag&IUPD)
E 12
I 12
		if (ip->i_flag&IUPD)
E 12
D 15
			dp->di_mtime = *tm;
E 15
I 15
D 33
			ip->i_mtime = *tm;
E 33
I 33
			ip->i_mtime = tm->tv_sec;
E 33
E 15
D 12
		if(ip->i_flag&ICHG)
E 12
I 12
		if (ip->i_flag&ICHG)
E 12
D 15
			dp->di_ctime = time;
E 15
I 15
D 29
			ip->i_ctime = time;
E 29
I 29
			ip->i_ctime = time.tv_sec;
E 29
E 15
D 44
		ip->i_flag &= ~(IUPD|IACC|ICHG);
E 44
I 44
		ip->i_flag &= ~(IUPD|IACC|ICHG|IMOD);
E 44
I 21
D 62
D 63
		dp = bp->b_un.b_dino + itoo(fp, ip->i_number);
E 63
I 63
		dp = bp->b_un.b_dino + itoo(fs, ip->i_number);
E 63
E 62
I 62
		dp = bp->b_un.b_dino + itoo(fs, ip->i_number);
E 62
		dp->di_ic = ip->i_ic;
E 21
I 15
D 18
		dp = bp->b_un.b_dino + itoo(fp, ip->i_number);
		dp->di_ic = ip->i_ic;
E 18
E 15
D 5
		bdwrite(bp);
E 5
I 5
		if (waitfor)
			bwrite(bp);
		else
			bdwrite(bp);
E 67
I 67
	if ((ip->i_flag & (IUPD|IACC|ICHG|IMOD)) == 0)
		return (0);
D 94
	if (vp->v_mount->m_flag & M_RDONLY)
E 94
I 94
	if (vp->v_mount->mnt_flag & MNT_RDONLY)
E 94
		return (0);
	error = bread(ip->i_devvp, fsbtodb(fs, itod(fs, ip->i_number)),
D 73
		(int)fs->fs_bsize, &bp);
E 73
I 73
		(int)fs->fs_bsize, NOCRED, &bp);
E 73
	if (error) {
		brelse(bp);
		return (error);
E 67
E 5
	}
I 67
	if (ip->i_flag&IACC)
		ip->i_atime = ta->tv_sec;
	if (ip->i_flag&IUPD)
		ip->i_mtime = tm->tv_sec;
	if (ip->i_flag&ICHG)
		ip->i_ctime = time.tv_sec;
	ip->i_flag &= ~(IUPD|IACC|ICHG|IMOD);
	dp = bp->b_un.b_dino + itoo(fs, ip->i_number);
D 76
	dp->di_ic = ip->i_ic;
E 76
I 76
	*dp = ip->i_din;
E 76
	if (waitfor) {
		return (bwrite(bp));
	} else {
		bdwrite(bp);
		return (0);
	}
E 67
}

I 37
#define	SINGLE	0	/* index of single indirect block */
#define	DOUBLE	1	/* index of double indirect block */
#define	TRIPLE	2	/* index of triple indirect block */
E 37
/*
D 28
 * Free all the disk blocks associated
 * with the specified inode structure.
 * The blocks of the file are removed
D 25
 * in reverse order. This FILO
 * algorithm will tend to maintain
 * a contiguous free list much longer
 * than FIFO.
E 25
I 25
 * in reverse order.
E 28
I 28
D 76
 * Truncate the inode ip to at most
 * length size.  Free affected disk
 * blocks -- the blocks of the file
 * are removed in reverse order.
E 76
I 76
 * Truncate the inode ip to at most length size.  Free affected disk
 * blocks -- the blocks of the file are removed in reverse order.
E 76
I 37
 *
 * NB: triple indirect blocks are untested.
E 37
E 28
E 25
 */
D 28
itrunc(ip)
E 28
I 28
D 37
itrunc(ip, length)
E 28
D 12
register struct inode *ip;
E 12
I 12
	register struct inode *ip;
E 37
I 37
D 85
itrunc(oip, length)
E 85
I 85
itrunc(oip, length, flags)
E 85
D 53
	struct inode *oip;
E 53
I 53
	register struct inode *oip;
E 53
E 37
I 28
D 36
	register int length;
E 36
I 36
	u_long length;
I 85
	int flags;
E 85
E 36
E 28
E 12
{
D 53
	register i;
E 53
D 34
	dev_t dev;
E 34
D 36
	daddr_t bn;
I 5
	struct inode itmp;
E 36
I 36
	register daddr_t lastblock;
D 37
	daddr_t bn, lastdiblock, lastsiblock;
E 37
I 37
D 59
	daddr_t bn, lastiblock[NIADDR];
E 59
I 59
	daddr_t bn, lbn, lastiblock[NIADDR];
E 59
E 37
E 36
I 15
	register struct fs *fs;
I 36
D 37
	int j;
E 37
I 37
	register struct inode *ip;
I 53
	struct buf *bp;
D 58
	int offset, lbn, osize, size, error, count, level, s;
E 58
I 58
D 59
	int offset, lbn, osize, size, count, level, s;
E 59
I 59
D 62
D 63
	int offset, osize, size, count, level, s;
E 63
I 63
D 67
	int offset, osize, size, count, level;
E 63
E 62
I 62
	int offset, osize, size, count, level;
E 62
E 59
E 58
	long nblocks, blocksreleased = 0;
E 67
I 67
	int offset, osize, size, level;
	long count, nblocks, blocksreleased = 0;
E 67
	register int i;
D 67
	dev_t dev;
E 67
I 67
D 85
	int error, allerror = 0;
E 85
I 85
	int aflags, error, allerror;
E 85
E 67
E 53
	struct inode tip;
D 40
	int level;
E 37
E 36
I 23
D 27
#ifdef	QUOTA
E 27
I 27
#ifdef QUOTA
E 40
E 27
D 36
	register long cnt = 0;
	long tloop();
E 36
I 36
D 53
	long blocksreleased = 0, nblocks;
	long indirtrunc();
E 36
D 40
#endif
E 40
I 40
	int level;
E 53
I 53
D 67
	extern long indirtrunc();
E 67
D 62
D 63
	extern struct cmap *mfind();
E 63
E 62
E 53
E 40
I 26
D 36
	/*
	 * Only plain files, directories and symbolic
	 * links contain blocks.
	 */
	i = ip->i_mode & IFMT;
	if (i != IFREG && i != IFDIR && i != IFLNK)
		return;
E 36
I 36

I 98
	vnode_pager_setsize(ITOV(oip), length);
E 98
E 36
I 28
D 37
	if (ip->i_size <= length)
E 37
I 37
D 41
	if (oip->i_size <= length)
E 41
I 41
	if (oip->i_size <= length) {
		oip->i_flag |= ICHG|IUPD;
D 67
		iupdat(oip, &time, &time, 1);
E 41
E 37
		return;
E 67
I 67
		error = iupdat(oip, &time, &time, 1);
		return (error);
E 67
I 41
	}
E 41
E 28
E 26
E 23
E 15
E 5
D 36

E 36
I 36
D 37
#ifdef notdef
	/* this is superfluous given size check above */
	i = ip->i_mode & IFMT;
	if (i != IFREG && i != IFDIR && i != IFLNK) {
		printf("itrunc: i# %d, size %d\n", ip->i_number, ip->i_size);
		return;
	}
#endif
E 37
E 36
D 12
	if (ip->i_vfdcnt)
		panic("itrunc");
E 12
D 20
	i = ip->i_mode & IFMT;
D 14
	if (i!=IFREG && i!=IFDIR)
E 14
I 14
D 15
	if (i!=IFREG && i!=IFDIR && i!=IFLNK)
E 15
I 15
	if (i != IFREG && i != IFDIR && i != IFLNK)
E 15
E 14
		return;
E 20
I 5
D 15

E 15
	/*
D 36
	 * Clean inode on disk before freeing blocks
	 * to insure no duplicates if system crashes.
E 36
I 36
D 37
	 * Update size of file on disk before
	 * we start freeing blocks.  If we crash
	 * while free'ing blocks below, the file
	 * size will be believed and the blocks
	 * returned to the free list.
	 * After updating the copy on disk we
	 * put the old size back so macros like
	 * blksize will work.
E 37
I 37
	 * Calculate index into inode's block list of
	 * last direct and indirect blocks (if any)
	 * which we want to keep.  Lastblock is -1 when
	 * the file is truncated to 0.
E 37
E 36
	 */
D 36
	itmp = *ip;
D 28
	itmp.i_size = 0;
E 28
I 28
	itmp.i_size = length;
E 28
D 15
	for (i = 0; i < NADDR; i++)
		itmp.i_un.i_addr[i] = 0;
E 15
I 15
	for (i = 0; i < NDADDR; i++)
		itmp.i_db[i] = 0;
	for (i = 0; i < NIADDR; i++)
		itmp.i_ib[i] = 0;
E 15
	itmp.i_flag |= ICHG|IUPD;
D 29
	iupdat(&itmp, &time, &time, 1);
E 29
I 29
D 33
	iupdat(&itmp, &time.tv_sec, &time.tv_sec, 1);
E 33
I 33
D 34
	iupdat(&itmp, time, time, 1);
E 34
I 34
	iupdat(&itmp, &time, &time, 1);
E 34
E 33
E 29
	ip->i_flag &= ~(IUPD|IACC|ICHG);
E 36
I 36
D 37
	j = ip->i_size;
	ip->i_size = length;
	ip->i_flag |= ICHG|IUPD;
	iupdat(ip, &time, &time, 1);
	ip->i_size = j;
E 36

I 20
D 26
	/*
	 * Only plain files, directories and symbolic
	 * links contain blocks.
	 */
	i = ip->i_mode & IFMT;
	if (i != IFREG && i != IFDIR && i != IFLNK)
		return;
E 26
E 20
	/*
D 36
	 * Now return blocks to free list... if machine
	 * crashes, they will be harmless MISSING blocks.
E 36
I 36
	 * Calculate last direct, single indirect and
	 * double indirect block (if any) which we want
	 * to keep.  Lastblock is -1 when the file is
	 * truncated to 0.
E 36
	 */
E 5
D 31
	dev = ip->i_dev;
E 31
D 15
	for(i=NADDR-1; i>=0; i--) {
		bn = ip->i_un.i_addr[i];
E 15
I 15
	fs = ip->i_fs;
E 37
I 37
	fs = oip->i_fs;
E 37
I 36
	lastblock = lblkno(fs, length + fs->fs_bsize - 1) - 1;
D 37
	lastsiblock = lastblock - NDADDR;
	lastdiblock = lastsiblock - NINDIR(fs);
E 37
I 37
	lastiblock[SINGLE] = lastblock - NDADDR;
	lastiblock[DOUBLE] = lastiblock[SINGLE] - NINDIR(fs);
	lastiblock[TRIPLE] = lastiblock[DOUBLE] - NINDIR(fs) * NINDIR(fs);
E 37
D 40
#ifdef QUOTA
	nblocks = fs->fs_bsize / DEV_BSIZE;
#endif
E 40
I 40
	nblocks = btodb(fs->fs_bsize);
E 40
E 36
	/*
D 36
	 * release double indirect block first
E 36
I 36
D 37
	 * Double indirect block first
E 37
I 37
D 53
	 * Update size of file and block pointers
E 53
I 53
	 * Update the size of the file. If the file is not being
	 * truncated to a block boundry, the contents of the
	 * partial block following the end of the file must be
	 * zero'ed in case it ever become accessable again because
	 * of subsequent file growth.
	 */
	osize = oip->i_size;
	offset = blkoff(fs, length);
	if (offset == 0) {
		oip->i_size = length;
	} else {
		lbn = lblkno(fs, length);
D 67
		bn = fsbtodb(fs, bmap(oip, lbn, B_WRITE, offset));
		if (u.u_error || (long)bn < 0)
			return;
E 67
I 67
D 85
		error = balloc(oip, lbn, offset, &bn, B_CLRBUF);
		if (error)
E 85
I 85
		aflags = B_CLRBUF;
		if (flags & IO_SYNC)
			aflags |= B_SYNC;
I 92
#ifdef QUOTA
		if (error = getinoquota(oip))
			return (error);
#endif
E 92
		if (error = balloc(oip, lbn, offset, &bp, aflags))
E 85
			return (error);
D 85
		if ((long)bn < 0)
			panic("itrunc: hole");
E 85
E 67
		oip->i_size = length;
		size = blksize(fs, oip, lbn);
I 85
D 98
		bn = bp->b_blkno;
E 85
D 62
D 63
		count = howmany(size, DEV_BSIZE);
E 63
I 63
		count = howmany(size, CLBYTES);
E 63
E 62
I 62
		count = howmany(size, CLBYTES);
E 62
D 67
		dev = oip->i_dev;
E 67
D 62
D 63
		s = splimp();
		for (i = 0; i < count; i += CLSIZE)
			if (mfind(dev, bn + i))
				munhash(dev, bn + i);
		splx(s);
E 63
I 63
		for (i = 0; i < count; i++)
D 67
			munhash(dev, bn + i * CLBYTES / DEV_BSIZE);
E 63
E 62
I 62
		for (i = 0; i < count; i++)
#ifdef SECSIZE
			munhash(dev, bn + i * CLBYTES / fs->fs_dbsize);
#else SECSIZE
			munhash(dev, bn + i * CLBYTES / DEV_BSIZE);
#endif SECSIZE
E 62
		bp = bread(dev, bn, size);
		if (bp->b_flags & B_ERROR) {
			u.u_error = EIO;
E 67
I 67
			munhash(oip->i_devvp, bn + i * CLBYTES / DEV_BSIZE);
E 98
I 98
		(void) vnode_pager_uncache(ITOV(oip));
E 98
D 73
		error = bread(oip->i_devvp, bn, size, &bp);
E 73
I 73
D 85
		error = bread(oip->i_devvp, bn, size, NOCRED, &bp);
E 73
		if (error) {
E 67
			oip->i_size = osize;
			brelse(bp);
D 67
			return;
E 67
I 67
			return (error);
E 67
		}
E 85
D 59
		bzero(bp->b_un.b_addr + offset, size - offset);
E 59
I 59
		bzero(bp->b_un.b_addr + offset, (unsigned)(size - offset));
E 59
D 85
		bdwrite(bp);
E 85
I 85
D 97
		brealloc(bp, size);
E 97
I 97
		allocbuf(bp, size);
E 97
		if (flags & IO_SYNC)
			bwrite(bp);
		else
			bdwrite(bp);
E 85
	}
	/*
	 * Update file and block pointers
E 53
	 * on disk before we start freeing blocks.
	 * If we crash before free'ing blocks below,
	 * the blocks will be returned to the free list.
	 * lastiblock values are also normalized to -1
	 * for calls to indirtrunc below.
D 53
	 * (? fsck doesn't check validity of pointers in indirect blocks)
E 53
E 37
E 36
	 */
D 36
	bn = ip->i_ib[NIADDR-1];
	if (bn != (daddr_t)0) {
		ip->i_ib[NIADDR - 1] = (daddr_t)0;
E 36
I 36
D 37
	bn = ip->i_ib[NIADDR - 1];
	if (bn != 0) {
		/*
		 * If lastdiblock is negative, it's value
		 * is meaningless; in this case we set it to
		 * -NINDIR(fs) so calculations performed in
		 * indirtrunc come out right.
		 */
		if (lastdiblock < 0)
			lastdiblock -= lastsiblock;
E 36
D 23
		tloop(ip, bn, 1);
E 23
I 23
D 27
#ifdef	QUOTA
E 27
I 27
#ifdef QUOTA
E 27
D 36
		cnt +=
E 36
I 36
		blocksreleased +=
E 36
#endif
D 36
			tloop(ip, bn, 1);
E 36
I 36
			indirtrunc(ip, bn, lastdiblock, 1);
		if (lastdiblock < 0) {
			ip->i_ib[NIADDR - 1] = 0;
			free(ip, bn, (off_t)fs->fs_bsize);
#ifdef QUOTA
			blocksreleased += nblocks;
#endif
E 37
I 37
	tip = *oip;
I 53
	tip.i_size = osize;
E 53
	for (level = TRIPLE; level >= SINGLE; level--)
		if (lastiblock[level] < 0) {
			oip->i_ib[level] = 0;
			lastiblock[level] = -1;
E 37
		}
E 36
E 23
D 37
	}
I 36
	if (lastdiblock >= 0)
		goto done;
E 37
I 37
	for (i = NDADDR - 1; i > lastblock; i--)
		oip->i_db[i] = 0;
D 53
	oip->i_size = length;
E 53
	oip->i_flag |= ICHG|IUPD;
D 53
	iupdat(oip, &time, &time, 1);
	ip = &tip;
E 53
I 53
D 67
	syncip(oip);
E 67
I 67
D 83
	allerror = syncip(oip);
E 83
I 83
D 85
	allerror = syncip(oip, MNT_WAIT);
E 85
I 85
	vinvalbuf(ITOV(oip), (length > 0));
D 86
	allerror = iupdat(ip, &time, &time, MNT_WAIT);
E 86
I 86
	allerror = iupdat(oip, &time, &time, MNT_WAIT);
E 86
E 85
E 83
E 67
E 53

E 37
E 36
	/*
D 36
	 * release single indirect blocks second
E 36
I 36
D 37
	 * Single indirect blocks second.
	 * First, those which can be totally
	 * zapped, then possibly one which
	 * needs to be partially cleared.
E 37
I 37
	 * Indirect blocks first.
E 37
E 36
	 */
I 53
	ip = &tip;
E 53
D 36
	for (i = NIADDR - 2; i >= 0; i--) {
E 36
I 36
D 37
	j = lastsiblock < 0 ? -1 : lastsiblock / NINDIR(fs);
	for (i = NIADDR - 2; i > j; i--) {
E 36
		bn = ip->i_ib[i];
E 37
I 37
	for (level = TRIPLE; level >= SINGLE; level--) {
		bn = ip->i_ib[level];
E 37
D 36
		if (bn != (daddr_t)0) {
			ip->i_ib[i] = (daddr_t)0;
E 36
I 36
		if (bn != 0) {
E 36
D 23
			tloop(ip, bn, 0);
E 23
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 40
E 27
D 36
			cnt +=
E 36
I 36
D 37
			blocksreleased += nblocks +
E 37
I 37
D 67
			blocksreleased +=
E 37
E 36
D 40
#endif
D 36
				tloop(ip, bn, 0);
E 36
I 36
D 37
				indirtrunc(ip, bn, (daddr_t)-1, 0);
			ip->i_ib[i] = 0;
			free(ip, bn, (off_t)fs->fs_bsize);
E 36
E 23
		}
	}
I 36
	if (lastsiblock >= 0) {
		bn = ip->i_ib[j];
		if (bn != 0)
E 37
I 37
				indirtrunc(ip, bn, lastiblock[level], level);
E 40
I 40
			    indirtrunc(ip, bn, lastiblock[level], level);
E 67
I 67
			error = indirtrunc(ip, bn, lastiblock[level], level,
				&count);
			if (error)
				allerror = error;
			blocksreleased += count;
E 67
E 40
			if (lastiblock[level] < 0) {
				ip->i_ib[level] = 0;
D 64
				free(ip, bn, (off_t)fs->fs_bsize);
E 64
I 64
				blkfree(ip, bn, (off_t)fs->fs_bsize);
E 64
E 37
D 40
#ifdef QUOTA
E 40
D 37
			blocksreleased +=
E 37
I 37
				blocksreleased += nblocks;
E 37
D 40
#endif
E 40
D 37
				indirtrunc(ip, bn, lastsiblock, 0);
		goto done;
E 37
I 37
			}
		}
		if (lastiblock[level] >= 0)
			goto done;
E 37
	}
I 37

E 37
E 36
	/*
D 36
	 * finally release direct blocks
E 36
I 36
D 37
	 * All whole direct blocks.
E 37
I 37
	 * All whole direct blocks or frags.
E 37
E 36
	 */
D 36
	for (i = NDADDR - 1; i>=0; i--) {
E 36
I 36
	for (i = NDADDR - 1; i > lastblock; i--) {
D 58
		register int size;
E 58
I 58
D 60
		register int bsize;
E 60
I 60
		register off_t bsize;
E 60
E 58

E 36
I 23
D 34
		register size;

E 34
E 23
		bn = ip->i_db[i];
E 15
D 12
		if(bn == (daddr_t)0)
E 12
I 12
D 36
		if (bn == (daddr_t)0)
E 36
I 36
		if (bn == 0)
E 36
E 12
			continue;
D 15
		ip->i_un.i_addr[i] = (daddr_t)0;
		switch(i) {

		default:
			free(dev, bn);
			break;

		case NADDR-3:
			tloop(dev, bn, 0, 0);
			break;

		case NADDR-2:
			tloop(dev, bn, 1, 0);
			break;

		case NADDR-1:
			tloop(dev, bn, 1, 1);
		}
E 15
I 15
D 36
		ip->i_db[i] = (daddr_t)0;
I 31
#ifndef QUOTA
		fre(ip, bn, (off_t)blksize(fs, ip, i));
#else
E 31
D 23
		fre(ip, bn, (off_t)blksize(fs, ip, i));
E 23
I 23
D 35
		fre(ip, bn, size = (off_t)blksize(fs, ip, i));
D 27
#ifdef	QUOTA
E 27
I 27
D 31
#ifdef QUOTA
E 31
E 27
		cnt += size / DEV_BSIZE;
E 35
I 35
		{ int size;
		  fre(ip, bn, size = (off_t)blksize(fs, ip, i));
		  cnt += size / DEV_BSIZE;
		}
E 36
I 36
		ip->i_db[i] = 0;
D 58
		size = (off_t)blksize(fs, ip, i);
		free(ip, bn, size);
D 40
#ifdef QUOTA
		blocksreleased += size / DEV_BSIZE;
E 36
E 35
#endif
E 40
I 40
		blocksreleased += btodb(size);
E 58
I 58
		bsize = (off_t)blksize(fs, ip, i);
D 64
		free(ip, bn, bsize);
E 64
I 64
		blkfree(ip, bn, bsize);
E 64
		blocksreleased += btodb(bsize);
E 58
E 40
E 23
E 15
	}
I 37
	if (lastblock < 0)
		goto done;

E 37
D 36
	ip->i_size = 0;
E 36
D 5
	ip->i_flag |= ICHG|IUPD;
E 5
I 5
	/*
D 36
	 * Inode was written and flags updated above.
	 * No need to modify flags here.
E 36
I 36
	 * Finally, look for a change in size of the
	 * last direct block; release any frags.
E 36
	 */
I 36
D 37
	if (lastblock >= 0 && ip->i_db[lastblock] != 0) {
E 37
I 37
	bn = ip->i_db[lastblock];
	if (bn != 0) {
D 60
		int oldspace, newspace;
E 60
I 60
		off_t oldspace, newspace;
E 60

E 37
		/*
		 * Calculate amount of space we're giving
		 * back as old block size minus new block size.
		 */
D 37
		i = blksize(fs, ip, lastblock);
E 37
I 37
		oldspace = blksize(fs, ip, lastblock);
E 37
		ip->i_size = length;
D 37
		i = i - blksize(fs, ip, lastblock);
		if (i > 0) {
E 37
I 37
		newspace = blksize(fs, ip, lastblock);
		if (newspace == 0)
			panic("itrunc: newspace");
		if (oldspace - newspace > 0) {
E 37
			/*
			 * Block number of space to be free'd is
			 * the old block # plus the number of frags
			 * required for the storage we're keeping.
			 */
D 37
			bn = ip->i_db[lastblock] +
				numfrags(fs, fs->fs_bsize - i);
			free(ip, bn, i);
E 37
I 37
			bn += numfrags(fs, newspace);
D 64
			free(ip, bn, oldspace - newspace);
E 64
I 64
			blkfree(ip, bn, oldspace - newspace);
E 64
E 37
E 36
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 27
D 36
	(void) chkdq(ip, -cnt, 0);
E 36
I 36
D 37
			blocksreleased += i / DEV_BSIZE;
E 37
I 37
			blocksreleased += (oldspace - newspace) / DEV_BSIZE;
E 37
E 36
#endif
E 40
I 40
			blocksreleased += btodb(oldspace - newspace);
E 40
I 36
		}
	}
done:
D 37
	/*
	 * Finished free'ing blocks, complete
	 * inode update to reflect new length.
	 */
E 37
I 37
/* BEGIN PARANOIA */
	for (level = SINGLE; level <= TRIPLE; level++)
		if (ip->i_ib[level] != oip->i_ib[level])
			panic("itrunc1");
	for (i = 0; i < NDADDR; i++)
		if (ip->i_db[i] != oip->i_db[i])
			panic("itrunc2");
/* END PARANOIA */
I 40
	oip->i_blocks -= blocksreleased;
	if (oip->i_blocks < 0)			/* sanity */
		oip->i_blocks = 0;
	oip->i_flag |= ICHG;
E 40
E 37
#ifdef QUOTA
D 40
	(void) chkdq(ip, -blocksreleased, 0);
E 40
I 40
D 92
	(void) chkdq(oip, -blocksreleased, 0);
E 92
I 92
	if (!getinoquota(oip))
		(void) chkdq(oip, -blocksreleased, NOCRED, 0);
E 92
E 40
#endif
I 67
	return (allerror);
E 67
D 37
	ip->i_size = length;
	ip->i_flag |= ICHG|IUPD;
	iupdat(ip, &time, &time, 1);
E 37
E 36
E 23
E 5
}

I 36
/*
 * Release blocks associated with the inode ip and
 * stored in the indirect block bn.  Blocks are free'd
 * in LIFO order up to (but not including) lastbn.  If
D 37
 * doubleindirect is indicated, this block is a double
 * indirect block and recursive calls to indirtrunc must
 * be used to cleanse single indirect blocks instead of
 * a simple free.
E 37
I 37
 * level is greater than SINGLE, the block is an indirect
 * block and recursive calls to indirtrunc must be used to
 * cleanse other indirect blocks.
 *
 * NB: triple indirect blocks are untested.
E 37
 */
E 36
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 40
E 27
D 67
long
D 40
#endif
E 40
E 23
D 15
tloop(dev, bn, f1, f2)
dev_t dev;
daddr_t bn;
E 15
I 15
D 36
tloop(ip, bn, indflg)
E 36
I 36
D 37
indirtrunc(ip, bn, lastbn, doubleindirect)
E 37
I 37
indirtrunc(ip, bn, lastbn, level)
E 67
I 67
indirtrunc(ip, bn, lastbn, level, countp)
E 67
E 37
E 36
	register struct inode *ip;
D 36
	daddr_t bn;
	int indflg;
E 36
I 36
	daddr_t bn, lastbn;
D 37
	int doubleindirect;
E 37
I 37
	int level;
I 67
	long *countp;
E 67
E 37
E 36
E 15
{
D 36
	register i;
	register struct buf *bp;
E 36
I 36
	register int i;
D 37
	struct buf *bp;
E 37
I 37
D 66
	struct buf *bp, *copy;
E 37
E 36
	register daddr_t *bap;
E 66
I 66
	struct buf *bp;
E 66
I 15
D 37
	register struct fs *fs;
E 37
I 37
	register struct fs *fs = ip->i_fs;
E 37
E 15
D 36
	daddr_t nb;
E 36
I 36
D 66
	daddr_t nb, last;
E 66
I 66
	register daddr_t *bap;
	daddr_t *copy, nb, last;
E 66
I 37
D 67
	long factor;
E 37
E 36
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 40
E 27
D 36
	register long cnt = 0;
E 36
I 36
	int blocksreleased = 0, nblocks;
E 67
I 67
	long blkcount, factor;
	int nblocks, blocksreleased = 0;
	int error, allerror = 0;
E 67
E 36
D 40
#endif
E 40
E 23

D 37
	bp = NULL;
D 15
	for(i=NINDIR-1; i>=0; i--) {
E 15
I 15
	fs = ip->i_fs;
E 37
I 37
	/*
	 * Calculate index in current block of last
	 * block to be kept.  -1 indicates the entire
	 * block so we need not calculate the index.
	 */
	factor = 1;
	for (i = SINGLE; i < level; i++)
		factor *= NINDIR(fs);
E 37
D 36
	for (i = NINDIR(fs) - 1; i >= 0; i--) {
E 36
I 36
	last = lastbn;
D 37
	if (doubleindirect)
		last /= NINDIR(fs);
E 37
I 37
	if (lastbn > 0)
		last /= factor;
E 37
D 40
#ifdef QUOTA
	nblocks = fs->fs_bsize / DEV_BSIZE;
#endif
E 40
I 40
	nblocks = btodb(fs->fs_bsize);
E 40
D 37
	for (i = NINDIR(fs) - 1; i > last; i--) {
E 36
E 15
D 12
		if(bp == NULL) {
E 12
I 12
		if (bp == NULL) {
I 36
			struct buf *copy;
E 37
I 37
	/*
	 * Get buffer of block pointers, zero those 
	 * entries corresponding to blocks to be free'd,
	 * and update on disk copy first.
	 */
D 66
	copy = geteblk((int)fs->fs_bsize);
E 66
I 62
#ifdef SECSIZE
	bp = bread(ip->i_dev, fsbtodb(fs, bn), (int)fs->fs_bsize,
	    fs->fs_dbsize);
#else SECSIZE
E 62
D 67
	bp = bread(ip->i_dev, fsbtodb(fs, bn), (int)fs->fs_bsize);
I 62
#endif SECSIZE
E 62
	if (bp->b_flags&B_ERROR) {
E 67
I 67
D 73
	error = bread(ip->i_devvp, fsbtodb(fs, bn), (int)fs->fs_bsize, &bp);
E 73
I 73
	error = bread(ip->i_devvp, fsbtodb(fs, bn), (int)fs->fs_bsize,
		NOCRED, &bp);
E 73
	if (error) {
E 67
D 66
		brelse(copy);
E 66
		brelse(bp);
D 40
#ifdef QUOTA
E 40
D 67
		return (0);
E 67
I 67
		*countp = 0;
		return (error);
E 67
I 39
D 40
#else
		return;
E 39
#endif
E 40
	}
I 85
D 89
	if ((bp->b_flags & B_CACHE) == 0)
		reassignbuf(bp, ITOV(ip));
E 89
E 85
	bap = bp->b_un.b_daddr;
D 66
	bcopy((caddr_t)bap, (caddr_t)copy->b_un.b_daddr, (u_int)fs->fs_bsize);
E 66
I 66
	MALLOC(copy, daddr_t *, fs->fs_bsize, M_TEMP, M_WAITOK);
	bcopy((caddr_t)bap, (caddr_t)copy, (u_int)fs->fs_bsize);
E 66
	bzero((caddr_t)&bap[last + 1],
	  (u_int)(NINDIR(fs) - (last + 1)) * sizeof (daddr_t));
I 85
	if (last == -1)
		bp->b_flags |= B_INVAL;
E 85
D 67
	bwrite(bp);
E 67
I 67
	error = bwrite(bp);
	if (error)
		allerror = error;
E 67
D 66
	bp = copy, bap = bp->b_un.b_daddr;
E 66
I 66
	bap = copy;
E 66
E 37

D 37
			copy = geteblk((int)fs->fs_bsize);
E 36
E 12
D 15
			bp = bread(dev, bn);
E 15
I 15
D 32
			bp = bread(ip->i_dev, fsbtodb(fs, bn), fs->fs_bsize);
E 32
I 32
			bp = bread(ip->i_dev, fsbtodb(fs, bn),
				(int)fs->fs_bsize);
E 32
E 15
D 36
			if (bp->b_flags & B_ERROR) {
E 36
I 36
			if (bp->b_flags&B_ERROR) {
				brelse(copy);
E 36
				brelse(bp);
D 36
				return;
E 36
I 36
				return (NULL);
E 36
			}
			bap = bp->b_un.b_daddr;
I 36
			/*
			 * Update pointers before freeing blocks.
			 * If we crash before freeing the blocks
			 * they'll be recovered as missing.
			 */
			bcopy((caddr_t)bap, (caddr_t)copy->b_un.b_daddr,
				(u_int)fs->fs_bsize);
			bzero((caddr_t)&bap[last + 1],
			  (u_int)(NINDIR(fs) - (last + 1)) * sizeof (daddr_t));
			bwrite(bp);
			bp = copy, bap = bp->b_un.b_daddr;
E 36
		}
E 37
I 37
	/*
	 * Recursively free totally unused blocks.
	 */
	for (i = NINDIR(fs) - 1; i > last; i--) {
E 37
		nb = bap[i];
D 12
		if(nb == (daddr_t)0)
E 12
I 12
D 36
		if (nb == (daddr_t)0)
E 36
I 36
		if (nb == 0)
E 36
E 12
			continue;
D 12
		if(f1) {
E 12
I 12
D 15
		if (f1) {
E 12
			brelse(bp);
			bp = NULL;
			tloop(dev, nb, f2, 0);
		} else
			free(dev, nb);
E 15
I 15
D 23
		if (indflg)
			tloop(ip, nb, 0);
		else
E 23
I 23
D 36
		if (indflg) {
E 36
I 36
D 37
		if (doubleindirect)
E 37
I 37
D 67
		if (level > SINGLE)
E 37
E 36
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 40
E 27
D 36
			cnt +=
E 36
I 36
			blocksreleased +=
E 36
D 40
#endif
D 36
				tloop(ip, nb, 0);
		} else {
E 23
D 33
			fre(ip, nb, fs->fs_bsize);
E 33
I 33
			fre(ip, nb, (int)fs->fs_bsize);
E 36
I 36
D 37
				indirtrunc(ip, nb, (daddr_t)-1, 0);
E 37
I 37
				indirtrunc(ip, nb, (daddr_t)-1, level - 1);
E 40
I 40
			    indirtrunc(ip, nb, (daddr_t)-1, level - 1);
E 67
I 67
		if (level > SINGLE) {
			error = indirtrunc(ip, nb, (daddr_t)-1, level - 1,
				&blkcount);
			if (error)
				allerror = error;
			blocksreleased += blkcount;
		}
E 67
E 40
E 37
D 60
		free(ip, nb, (int)fs->fs_bsize);
E 60
I 60
D 64
		free(ip, nb, (off_t)fs->fs_bsize);
E 64
I 64
		blkfree(ip, nb, (off_t)fs->fs_bsize);
E 64
E 60
E 36
E 33
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 40
E 27
D 36
			cnt += fs->fs_bsize / DEV_BSIZE;
E 36
I 36
		blocksreleased += nblocks;
E 36
D 40
#endif
E 40
D 36
		}
E 36
E 23
E 15
	}
I 36
D 37
	if (doubleindirect && lastbn >= 0) {
		last = lastbn % NINDIR(fs);
		if (bp == NULL)
			panic("indirtrunc");
E 37
I 37

	/*
	 * Recursively free last partial block.
	 */
	if (level > SINGLE && lastbn >= 0) {
		last = lastbn % factor;
E 37
		nb = bap[i];
D 67
		if (nb != 0)
D 40
#ifdef QUOTA
			blocksreleased +=
#endif
D 37
				indirtrunc(ip, nb, last, 0);
E 37
I 37
				indirtrunc(ip, nb, last, level - 1);
E 40
I 40
			blocksreleased += indirtrunc(ip, nb, last, level - 1);
E 67
I 67
		if (nb != 0) {
			error = indirtrunc(ip, nb, last, level - 1, &blkcount);
			if (error)
				allerror = error;
			blocksreleased += blkcount;
		}
E 67
E 40
E 37
	}
E 36
D 12
	if(bp != NULL)
E 12
I 12
D 37
	if (bp != NULL)
E 12
		brelse(bp);
E 37
I 37
D 66
	brelse(bp);
E 66
I 66
	FREE(copy, M_TEMP);
E 66
E 37
D 15
	free(dev, bn);
E 15
I 15
D 33
	fre(ip, bn, fs->fs_bsize);
E 33
I 33
D 36
	fre(ip, bn, (int)fs->fs_bsize);
E 36
E 33
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 40
#ifdef QUOTA
E 40
E 27
D 36
	cnt += fs->fs_bsize / DEV_BSIZE;
	return(cnt);
E 36
I 36
D 67
	return (blocksreleased);
E 67
I 67
	*countp = blocksreleased;
	return (allerror);
E 67
E 36
D 40
#endif
E 40
E 23
E 15
D 25
}

/*
 * Make a new file.
 */
struct inode *
maknode(mode)
I 15
	int mode;
E 15
{
	register struct inode *ip;
I 15
	ino_t ipref;
E 15

D 15
	ip = ialloc(u.u_pdir->i_dev);
E 15
I 15
	if ((mode & IFMT) == IFDIR)
		ipref = dirpref(u.u_pdir->i_fs);
	else
		ipref = u.u_pdir->i_number;
	ip = ialloc(u.u_pdir, ipref, mode);
E 15
D 12
	if(ip == NULL) {
E 12
I 12
	if (ip == NULL) {
E 12
		iput(u.u_pdir);
		return(NULL);
	}
I 23
#ifdef	QUOTA
	if (ip->i_dquot != NODQUOT)
		panic("maknode: dquot");
#endif
E 23
	ip->i_flag |= IACC|IUPD|ICHG;
D 12
	if((mode&IFMT) == 0)
E 12
I 12
D 15
	if ((mode&IFMT) == 0)
E 15
I 15
	if ((mode & IFMT) == 0)
E 15
E 12
		mode |= IFREG;
	ip->i_mode = mode & ~u.u_cmask;
	ip->i_nlink = 1;
	ip->i_uid = u.u_uid;
D 13
	ip->i_gid = u.u_gid;
E 13
I 13
	ip->i_gid = u.u_pdir->i_gid;
I 23
#ifdef	QUOTA
	ip->i_dquot = inoquota(ip);
#endif
E 23
E 13
I 5

	/*
	 * Make sure inode goes to disk before directory entry.
	 */
	iupdat(ip, &time, &time, 1);
D 15

E 15
E 5
	wdir(ip);
I 15
	if (u.u_error) {
		/*
		 * write error occurred trying to update directory
		 * so must deallocate the inode
		 */
		ip->i_nlink = 0;
		ip->i_flag |= ICHG;
		iput(ip);
		return(NULL);
	}
E 15
	return(ip);
}

/*
 * Write a directory entry with
 * parameters left as side effects
 * to a call to namei.
 */
wdir(ip)
D 12
struct inode *ip;
E 12
I 12
	struct inode *ip;
E 12
{
I 15
	register struct direct *dp, *ndp;
	struct fs *fs;
	struct buf *bp;
	int lbn, bn, base;
	int loc, dsize, spccnt, newsize;
	char *dirbuf;
E 15

	u.u_dent.d_ino = ip->i_number;
D 15
	bcopy((caddr_t)u.u_dbuf, (caddr_t)u.u_dent.d_name, DIRSIZ);
	u.u_count = sizeof(struct direct);
E 15
	u.u_segflg = 1;
D 15
	u.u_base = (caddr_t)&u.u_dent;
	writei(u.u_pdir);
E 15
I 15
	newsize = DIRSIZ(&u.u_dent);
	/*
	 * if u.u_count == 0, a new directory block must be allocated.
	 */
	if (u.u_count == 0) {
		u.u_dent.d_reclen = DIRBLKSIZ;
		u.u_count = newsize;
		u.u_base = (caddr_t)&u.u_dent;
I 24
/*ZZ*/if((u.u_offset&0x1ff))panic("wdir: newblk");
E 24
		writei(u.u_pdir);
		iput(u.u_pdir);
		return;
	}
	/*
	 * must read in an existing directory block
	 * to prepare to place the new entry into it.
	 */
	fs = u.u_pdir->i_fs;
	lbn = lblkno(fs, u.u_offset);
	base = blkoff(fs, u.u_offset);
	bn = fsbtodb(fs, bmap(u.u_pdir, lbn, B_WRITE, base + u.u_count));
	if (u.u_offset + u.u_count > u.u_pdir->i_size)
I 24
/*ZZ*/{if((u.u_offset+u.u_count-1&~0x1ff)!=(u.u_pdir->i_size-1&~0x1ff))
/*ZZ*/  printf("wdir i_size dir %s/%d (of=%d,cnt=%d,psz=%d))\n",
/*ZZ*/       u.u_pdir->i_fs->fs_fsmnt,u.u_pdir->i_number,u.u_offset,
/*ZZ*/       u.u_count,u.u_pdir->i_size);
E 24
		u.u_pdir->i_size = u.u_offset + u.u_count;
I 24
/*ZZ*/}
E 24
	bp = bread(u.u_pdir->i_dev, bn, blksize(fs, u.u_pdir, lbn));
	if (bp->b_flags & B_ERROR) {
		brelse(bp);
		return;
	}
	dirbuf = bp->b_un.b_addr + base;
	dp = (struct direct *)dirbuf;
	dsize = DIRSIZ(dp);
	spccnt = dp->d_reclen - dsize;
	/*
	 * if there is insufficient room to make an entry at this point
	 * namei insures that compacting from u.u_offset for u.u_count
	 * bytes will provide the necessary space.
	 */
	for (loc = dp->d_reclen; loc < u.u_count; ) {
		ndp = (struct direct *)(dirbuf + loc);
		if (dp->d_ino == 0) {
			spccnt += dsize;
		} else {
			dp->d_reclen = dsize;
			dp = (struct direct *)((char *)dp + dsize);
		}
		dsize = DIRSIZ(ndp);
		spccnt += ndp->d_reclen - dsize;
I 24
/*ZZ*/if(spccnt>512)panic("wdir spccnt");
/*ZZ*/if((loc&~0x1ff)!=(loc+ndp->d_reclen-1&~0x1ff))
/*ZZ*/printf("wdir: compact loc %d reclen %d (dir %s/%d)\n",loc,ndp->d_reclen,
/*ZZ*/u.u_pdir->i_fs->fs_fsmnt,u.u_pdir->i_number);
E 24
		loc += ndp->d_reclen;
		bcopy(ndp, dp, dsize);
	}
	/*
	 * Update the pointer fields in the previous entry (if any),
	 * copy in the new entry, and write out the block.
	 */
	if (dp->d_ino == 0) {
		if (spccnt + dsize < newsize)
D 24
			panic("wdir: compact failed");
E 24
I 24
			panic("wdir: compact failed (1)");
/*ZZ*/if(spccnt+dsize>512)panic("wdir: compact screwup");
E 24
		u.u_dent.d_reclen = spccnt + dsize;
	} else {
		if (spccnt < newsize)
D 24
			panic("wdir: compact failed");
E 24
I 24
			panic("wdir: compact failed (2)");
E 24
		u.u_dent.d_reclen = spccnt;
I 24
/*ZZ*/if ((((char *)dp-bp->b_un.b_addr)&0x1ff)+dsize>512) panic("wdir: reclen");
E 24
		dp->d_reclen = dsize;
		dp = (struct direct *)((char *)dp + dsize);
	}
I 24
/*ZZ*/if((((char*)dp-bp->b_un.b_addr)&0x1ff)+u.u_dent.d_reclen>512)panic("wdir: botch");
E 24
	bcopy(&u.u_dent, dp, newsize);
	bwrite(bp);
	u.u_pdir->i_flag |= IUPD|ICHG;
E 15
	iput(u.u_pdir);
E 25
I 18
}

/*
E 104
D 62
D 63
 * remove any inodes in the inode cache belonging to dev
E 63
I 63
D 80
 * Remove any inodes in the inode cache belonging to dev.
E 63
E 62
I 62
 * Remove any inodes in the inode cache belonging to dev.
E 62
 *
 * There should not be any active ones, return error if any are found
D 62
D 63
 * (nb: this is a user error, not a system err)
 *
 * Also, count the references to dev by block devices - this really
 * has nothing to do with the object of the procedure, but as we have
 * to scan the inode table here anyway, we might as well get the
 * extra benefit.
 *
 * this is called from sumount()/sys3.c when dev is being unmounted
E 63
I 63
 * (nb: this is a user error, not a system err).
E 63
E 62
I 62
 * (nb: this is a user error, not a system err).
E 62
 */
I 74
int busyprt = 0;	/* patch to print out busy inodes */

E 74
I 23
D 27
#ifdef	QUOTA
E 27
I 27
#ifdef QUOTA
E 27
D 24
iflush(dev, qi);
E 24
I 24
D 76
iflush(dev, iq)
E 24
	dev_t dev;
E 76
I 76
iflush(mp, iq)
	struct mount *mp;
E 76
D 24
	struct inode *qi;
E 24
I 24
	struct inode *iq;
E 24
#else
E 23
D 76
iflush(dev)
	dev_t dev;
E 76
I 76
iflush(mp)
	struct mount *mp;
E 76
I 23
#endif
E 23
{
I 76
D 77
	register struct vnode *vp;
E 77
I 77
	register struct vnode *vp, *nvp;
E 77
E 76
D 19
	register struct inode *ip;	/* known to be r11 - see 'asm' below */
E 19
I 19
	register struct inode *ip;
I 74
	int busy = 0;
E 74
E 19
D 62
D 63
	register open = 0;
E 63
E 62

D 76
	for (ip = inode; ip < inodeNINODE; ip++) {
E 76
I 76
D 77
	for (vp = mp->m_mounth; vp; vp = vp->v_mountf) {
E 77
I 77
	for (vp = mp->m_mounth; vp; vp = nvp) {
		nvp = vp->v_mountf;
E 77
		ip = VTOI(vp);
E 76
I 23
D 27
#ifdef	QUOTA
E 27
I 27
#ifdef QUOTA
E 27
D 74
		if (ip != iq && ip->i_dev == dev)
E 74
I 74
D 76
		if (ip == iq || ip->i_dev != dev)
E 76
I 76
		if (ip == iq)
E 76
			continue;
E 74
D 76
#else
E 23
D 74
		if (ip->i_dev == dev)
E 74
I 74
		if (ip->i_dev != dev)
			continue;
E 76
E 74
I 23
#endif
E 23
D 67
			if (ip->i_count)
E 67
I 67
D 74
			if (ITOV(ip)->v_count)
E 67
D 62
D 63
				return(-1);
E 63
I 63
				return (EBUSY);
E 63
E 62
I 62
				return (EBUSY);
E 62
			else {
D 19
#ifndef	UNFAST
				asm("remque	(r11),r0");
#else
				ip->i_back->i_forw = ip->i_forw;
				ip->i_forw->i_back = ip->i_back;
#endif
E 19
I 19
				remque(ip);
E 19
				ip->i_forw = ip;
				ip->i_back = ip;
				/*
D 67
				 * as i_count == 0, the inode was on the free
E 67
I 67
				 * as v_count == 0, the inode was on the free
E 67
				 * list already, just leave it there, it will
				 * fall off the bottom eventually. We could
				 * perhaps move it to the head of the free
				 * list, but as umounts are done so
				 * infrequently, we would gain very little,
				 * while making the code bigger.
				 */
E 74
I 74
D 76
		if (ITOV(ip)->v_count) {
E 76
I 76
		if (vp->v_count) {
E 76
			busy++;
			if (!busyprt)
				continue;
			printf("%s %d on dev 0x%x count %d type %d\n",
			    "iflush: busy inode ", ip->i_number, ip->i_dev,
D 76
			    ITOV(ip)->v_count, ITOV(ip)->v_type);
E 76
I 76
			    vp->v_count, vp->v_type);
E 76
			continue;
		}
D 76
		remque(ip);
		ip->i_forw = ip;
		ip->i_back = ip;
E 76
		/*
D 77
		 * As v_count == 0, the inode was on the free list already,
D 76
		 * just leave it there, it will fall off the bottom eventually.
E 76
I 76
		 * so it will fall off the bottom eventually.
E 76
		 * We could perhaps move it to the head of the free list,
		 * but as umounts are done so infrequently, we would gain
		 * very little, while making the code bigger.
E 77
I 77
		 * With v_count == 0, all we need to do is clear out the
		 * vnode data structures and we are done.
E 77
		 */
E 74
I 23
D 27
#ifdef	QUOTA
E 27
I 27
D 76
#ifdef QUOTA
E 27
D 74
				dqrele(ip->i_dquot);
				ip->i_dquot = NODQUOT;
E 74
I 74
		dqrele(ip->i_dquot);
		ip->i_dquot = NODQUOT;
E 74
#endif
I 67
D 74
				if (ip->i_devvp) {
					vrele(ip->i_devvp);
					ip->i_devvp = 0;
				}
E 67
E 23
			}
E 74
I 74
		if (ip->i_devvp) {
			vrele(ip->i_devvp);
			ip->i_devvp = 0;
		}
E 76
I 76
D 77
		ufs_reclaim(vp);
E 77
I 77
		vgone(vp);
E 77
E 76
E 74
D 62
D 63
		else if (ip->i_count && (ip->i_mode&IFMT)==IFBLK &&
		    ip->i_rdev == dev)
			open++;
E 63
E 62
	}
I 74
	if (busy)
		return (EBUSY);
E 74
D 62
D 63
	return (open);
E 63
I 63
	return (0);
E 63
E 62
I 62
	return (0);
E 62
E 18
}
I 10

D 12
#ifdef plock
#undef plock
E 12
I 12
D 30
#ifdef ilock
#undef ilock
E 12
#endif
D 12
#ifdef prele
#undef prele
E 12
I 12
D 16
#ifdef irele
#undef irele
E 16
I 16
#ifdef iunlock
#undef iunlock
E 16
E 12
#endif
E 30
/*
E 80
D 12
 * Lock an inode (should be called ilock).
 * If its already locked,
 * set the WANT bit and sleep.
E 12
I 12
 * Lock an inode. If its already locked, set the WANT bit and sleep.
E 12
 */
D 12
plock(ip)
register struct inode *ip;
E 12
I 12
D 104
ilock(ip)
E 104
I 104
void
ufs_ilock(ip)
E 104
	register struct inode *ip;
E 12
{
I 107
	struct proc *p = curproc;	/* XXX */
E 107

D 12
	while(ip->i_flag&ILOCK) {
E 12
I 12
D 30
	while (ip->i_flag&ILOCK) {
E 12
		ip->i_flag |= IWANT;
		sleep((caddr_t)ip, PINOD);
	}
	ip->i_flag |= ILOCK;
E 30
I 30
D 67
	ILOCK(ip);
E 67
I 67
	while (ip->i_flag & ILOCKED) {
		ip->i_flag |= IWANT;
I 87
D 100
		if (ip->i_spare0 == u.u_procp->p_pid)
E 100
I 100
D 106
		if (ip->i_spare0 == curproc->p_pid)
E 106
I 106
D 107
		if (ip->i_lockholder == curproc->p_pid)
E 106
E 100
			panic("locking against myself");
D 100
		ip->i_spare1 = u.u_procp->p_pid;
E 100
I 100
D 106
		ip->i_spare1 = curproc->p_pid;
E 106
I 106
		ip->i_lockwaiter = curproc->p_pid;
E 107
I 107
#ifdef DIAGNOSTIC
		if (p) {
			if (p->p_pid == ip->i_lockholder)
				panic("locking against myself");
			ip->i_lockwaiter = p->p_pid;
		}
#endif
E 107
E 106
E 100
E 87
		(void) sleep((caddr_t)ip, PINOD);
	}
I 107
#ifdef DIAGNOSTIC
E 107
I 87
D 106
	ip->i_spare1 = 0;
D 100
	ip->i_spare0 = u.u_procp->p_pid;
	u.u_spare[0]++;
E 100
I 100
	ip->i_spare0 = curproc->p_pid;
E 106
I 106
	ip->i_lockwaiter = 0;
D 107
	ip->i_lockholder = curproc->p_pid;
E 107
I 107
	if (p)
		ip->i_lockholder = p->p_pid;
#endif
E 107
E 106
E 100
E 87
	ip->i_flag |= ILOCKED;
I 103
	curproc->p_spare[2]++;
E 103
E 67
E 30
}

/*
D 12
 * Unlock an inode.
 * If WANT bit is on,
 * wakeup.
E 12
I 12
 * Unlock an inode.  If WANT bit is on, wakeup.
E 12
 */
D 12
prele(ip)
register struct inode *ip;
E 12
I 12
D 16
irele(ip)
E 16
I 16
D 104
iunlock(ip)
E 104
I 104
void
ufs_iunlock(ip)
E 104
E 16
	register struct inode *ip;
E 12
{

D 30
	ip->i_flag &= ~ILOCK;
D 12
	if(ip->i_flag&IWANT) {
E 12
I 12
	if (ip->i_flag&IWANT) {
E 12
		ip->i_flag &= ~IWANT;
		wakeup((caddr_t)ip);
	}
E 30
I 30
D 67
	IUNLOCK(ip);
E 67
I 67
	if ((ip->i_flag & ILOCKED) == 0)
D 85
		printf("unlocking unlocked inode %d on dev 0x%x\n",
			ip->i_number, ip->i_dev);
E 85
I 85
D 104
		vprint("iunlock: unlocked inode", ITOV(ip));
E 104
I 104
		vprint("ufs_iunlock: unlocked inode", ITOV(ip));
I 107
#ifdef DIAGNOSTIC
E 107
E 104
I 87
D 106
	ip->i_spare0 = 0;
E 106
I 106
	ip->i_lockholder = 0;
I 107
#endif
E 107
E 106
D 100
	u.u_spare[0]--;
E 100
E 87
E 85
	ip->i_flag &= ~ILOCKED;
I 103
	curproc->p_spare[2]--;
E 103
	if (ip->i_flag&IWANT) {
		ip->i_flag &= ~IWANT;
		wakeup((caddr_t)ip);
	}
E 126
D 92
}

/*
 * Check mode permission on inode pointer. Mode is READ, WRITE or EXEC.
 * The mode is shifted to select the owner/group/other fields. The
 * super user is granted all permissions.
 *
 * NB: Called from vnode op table. It seems this could all be done
 * using vattr's but...
 */
iaccess(ip, mode, cred)
	register struct inode *ip;
	register int mode;
	struct ucred *cred;
{
	register gid_t *gp;
D 76
	register struct vnode *vp = ITOV(ip);
E 76
	int i;

	/*
D 76
	 * If you're the super-user,
	 * you always get access.
E 76
I 76
	 * If you're the super-user, you always get access.
E 76
	 */
	if (cred->cr_uid == 0)
		return (0);
	/*
	 * Access check is based on only one of owner, group, public.
	 * If not owner, then check group. If not a member of the
	 * group, then check public access.
	 */
	if (cred->cr_uid != ip->i_uid) {
		mode >>= 3;
		gp = cred->cr_groups;
		for (i = 0; i < cred->cr_ngroups; i++, gp++)
			if (ip->i_gid == *gp)
				goto found;
		mode >>= 3;
found:
		;
	}
	if ((ip->i_mode & mode) != 0)
		return (0);
	return (EACCES);
E 92
E 67
E 30
}
E 10
E 1
